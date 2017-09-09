/* cmptls.c
 * Input file:  comp-utils.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cmptls.h"


DEFINE_VARIABLE_WITH_SYMBOL(Always_recompile_on_load, Qalways_recompile_on_load);

/* COMPILATIONS-UP-TO-DATE-P */
Object compilations_up_to_date_p(item_qm)
    Object item_qm;
{
    x_note_fn_call(139,0);
    if (IFIX(Kb_flags) >= (SI_Long)267L &&  !TRUEP(Recompile_on_next_load))
	return VALUES_1( !TRUEP(Always_recompile_on_load) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* CACHED-PARSES-UP-TO-DATE-P */
Object cached_parses_up_to_date_p(item_qm)
    Object item_qm;
{
    x_note_fn_call(139,1);
    return VALUES_1(IFIX(Kb_flags) >= (SI_Long)265L ? T : Nil);
}

Object Required_domain_types_of_role_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Working_on_lexical_computation_of_frame, Qworking_on_lexical_computation_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Variables_that_did_not_have_values, Qvariables_that_did_not_have_values);

DEFINE_VARIABLE_WITH_SYMBOL(Available_compiler_conses, Qavailable_compiler_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_compiler_conses_tail, Qavailable_compiler_conses_tail);

Object Available_compiler_conses_vector = UNBOUND;

Object Available_compiler_conses_tail_vector = UNBOUND;

Object Compiler_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Compiler_cons_counter, Qcompiler_cons_counter);

/* OUTSTANDING-COMPILER-CONSES */
Object outstanding_compiler_conses()
{
    Object temp;

    x_note_fn_call(139,2);
    temp = FIXNUM_MINUS(Compiler_cons_counter,
	    length(Available_compiler_conses));
    return VALUES_1(temp);
}

/* COMPILER-CONS-MEMORY-USAGE */
Object compiler_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(139,3);
    temp = FIXNUM_TIMES(Compiler_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-COMPILER-CONS-POOL */
Object replenish_compiler_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(139,4);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qcompiler_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_compiler_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_compiler_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_compiler_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Compiler_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qcompiler;           /* compiler */

/* COMPILER-CONS-1 */
Object compiler_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(139,5);
    new_cons = ISVREF(Available_compiler_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_compiler_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_compiler_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_compiler_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qcompiler);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-COMPILER-LIST-POOL */
Object replenish_compiler_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(139,6);
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
    if (ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_compiler_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_compiler_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_compiler_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qcompiler_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-COMPILER-LIST-1 */
Object make_compiler_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(139,7);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_compiler_conses_vector,
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
	replenish_compiler_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_compiler_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qcompiler);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_compiler_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_compiler_conses_tail_vector;
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

/* COMPILER-LIST-2 */
Object compiler_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_compiler_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qcompiler);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_compiler_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_compiler_conses_tail_vector;
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

/* COMPILER-LIST-3 */
Object compiler_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,9);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_compiler_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qcompiler);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_compiler_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_compiler_conses_tail_vector;
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

/* COMPILER-LIST-4 */
Object compiler_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,10);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_compiler_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qcompiler);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_compiler_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_compiler_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_compiler_conses_tail_vector;
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

/* COMPILER-LIST-TRACE-HOOK */
Object compiler_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(139,11);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-COMPILER-CONSES-1 */
Object copy_tree_using_compiler_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(139,12);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_compiler_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_compiler_cons_pool();
	temp_1 = copy_tree_using_compiler_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qcompiler);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_compiler_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_compiler_cons_pool();
	temp_1 = copy_tree_using_compiler_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qcompiler);
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

/* COPY-LIST-USING-COMPILER-CONSES-1 */
Object copy_list_using_compiler_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(139,13);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_compiler_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_compiler_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qcompiler);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_compiler_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_compiler_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_compiler_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_compiler_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qcompiler);
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

/* RECLAIM-COMPILER-CONS-1 */
Object reclaim_compiler_cons_1(compiler_cons)
    Object compiler_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(139,14);
    inline_note_reclaim_cons(compiler_cons,Qcompiler);
    if (ISVREF(Available_compiler_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_compiler_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = compiler_cons;
	temp = Available_compiler_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = compiler_cons;
    }
    else {
	temp = Available_compiler_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = compiler_cons;
	temp = Available_compiler_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = compiler_cons;
    }
    M_CDR(compiler_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-COMPILER-LIST-1 */
Object reclaim_compiler_list_1(compiler_list)
    Object compiler_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(139,15);
    if (compiler_list) {
	last_1 = compiler_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qcompiler);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qcompiler);
	if (ISVREF(Available_compiler_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_compiler_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = compiler_list;
	    temp = Available_compiler_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_compiler_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = compiler_list;
	    temp = Available_compiler_conses_tail_vector;
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

/* RECLAIM-COMPILER-LIST*-1 */
Object reclaim_compiler_list_star_1(compiler_list)
    Object compiler_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(139,16);
    if (CONSP(compiler_list)) {
	temp = last(compiler_list,_);
	M_CDR(temp) = Nil;
	if (compiler_list) {
	    last_1 = compiler_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qcompiler);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qcompiler);
	    if (ISVREF(Available_compiler_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_compiler_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = compiler_list;
		temp = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_compiler_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = compiler_list;
		temp = Available_compiler_conses_tail_vector;
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

/* RECLAIM-COMPILER-TREE-1 */
Object reclaim_compiler_tree_1(tree)
    Object tree;
{
    Object e, e2, compiler_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(139,17);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_compiler_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		compiler_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(compiler_cons,Qcompiler);
		if (EQ(compiler_cons,e))
		    goto end_1;
		else if ( !TRUEP(compiler_cons))
		    goto end_1;
		else
		    compiler_cons = CDR(compiler_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_compiler_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_compiler_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_compiler_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_compiler_conses_tail_vector;
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

/* DELETE-COMPILER-ELEMENT-1 */
Object delete_compiler_element_1(element,compiler_list)
    Object element, compiler_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(139,18);
    if (compiler_list) {
	if (EQ(element,M_CAR(compiler_list))) {
	    temp = CDR(compiler_list);
	    inline_note_reclaim_cons(compiler_list,Qcompiler);
	    if (ISVREF(Available_compiler_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_compiler_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = compiler_list;
		temp_1 = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = compiler_list;
	    }
	    else {
		temp_1 = Available_compiler_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = compiler_list;
		temp_1 = Available_compiler_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = compiler_list;
	    }
	    M_CDR(compiler_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = compiler_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qcompiler);
		if (ISVREF(Available_compiler_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_compiler_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_compiler_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_compiler_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_compiler_conses_tail_vector;
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
	    temp = compiler_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-COMPILER-CONS-1 */
Object delete_compiler_cons_1(compiler_cons,compiler_list)
    Object compiler_cons, compiler_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(139,19);
    if (EQ(compiler_cons,compiler_list))
	temp = CDR(compiler_list);
    else {
	l_trailer_qm = Nil;
	l = compiler_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,compiler_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = compiler_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_compiler_cons_1(compiler_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiler_warnings, Qcompiler_warnings);

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* COMPILER-WARNING */
Object compiler_warning varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(139,20);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      twrite_compiler_message_header();
	      tformat(7,control_string,arg1,arg2,arg3,arg4,arg5,arg6);
	      candidate_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    a_string = Nil;
    ab_loop_list_ = Compiler_warnings;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    a_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_eq_w(a_string,candidate_string)) {
	temp = TRUEP(T);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	reclaim_text_string(candidate_string);
	return VALUES_1(Nil);
    }
    else {
	Compiler_warnings = phrase_cons(candidate_string,Compiler_warnings);
	return VALUES_1(Nil);
    }
}

static Object array_constant;      /* # */

/* COMPILER-DEPENDENCE-WARNING */
Object compiler_dependence_warning varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(139,21);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      twrite_compiler_message_header();
	      tformat(7,control_string,arg1,arg2,arg3,arg4,arg5,arg6);
	      twrite_beginning_of_wide_string(array_constant,
		      FIX((SI_Long)87L));
	      candidate_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    a_string = Nil;
    ab_loop_list_ = Compiler_warnings;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    a_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_eq_w(a_string,candidate_string)) {
	temp = TRUEP(T);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	reclaim_text_string(candidate_string);
	return VALUES_1(Nil);
    }
    else {
	Compiler_warnings = phrase_cons(candidate_string,Compiler_warnings);
	return VALUES_1(Nil);
    }
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* TWRITE-COMPILER-MESSAGE-HEADER */
Object twrite_compiler_message_header()
{
    Object x2, gensymed_symbol, sub_class_bit_vector, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object statement_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(139,22);
    if (Current_computation_component_particulars) {
	if (SIMPLE_VECTOR_P(Current_computation_frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) 
		> (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
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
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)5L));
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
		  denote_component_of_block(1,Nil);
		  statement_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	twrite_character(FIX((SI_Long)34L));
	if (FIXNUM_LT(text_string_length(statement_string),
		Compiler_header_statement_length_limit))
	    twrite_general_string(statement_string);
	else {
	    index_1 = (SI_Long)0L;
	  next_loop:
	    if (index_1 >= IFIX(Compiler_header_statement_length_limit))
		goto end_loop;
	    twrite_character(FIX(UBYTE_16_ISAREF_1(statement_string,index_1)));
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)3L));
	}
	twrite_character(FIX((SI_Long)34L));
	reclaim_text_string(statement_string);
	return twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)2L));
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiler_errors, Qcompiler_errors);

/* COMPILER-ERROR */
Object compiler_error varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(139,23);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      twrite_compiler_message_header();
	      tformat(7,control_string,arg1,arg2,arg3,arg4,arg5,arg6);
	      candidate_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    a_string = Nil;
    ab_loop_list_ = Compiler_errors;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    a_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_eq_w(a_string,candidate_string)) {
	temp = TRUEP(T);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	reclaim_text_string(candidate_string);
	return VALUES_1(Nil);
    }
    else {
	Compiler_errors = phrase_cons(candidate_string,Compiler_errors);
	return VALUES_1(Nil);
    }
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* COMPILER-BUG */
Object compiler_bug varargs_1(int, n)
{
    Object section_name, control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(139,24);
    INIT_ARGS_nonrelocating();
    section_name = REQUIRED_ARG_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      twrite_compiler_message_header();
	      twrite_beginning_of_wide_string(array_constant_4,
		      FIX((SI_Long)43L));
	      twrite_general_string(section_name);
	      twrite_beginning_of_wide_string(array_constant_5,
		      FIX((SI_Long)3L));
	      tformat(7,control_string,arg1,arg2,arg3,arg4,arg5,arg6);
	      twrite_beginning_of_wide_string(array_constant_6,
		      FIX((SI_Long)57L));
	      twrite_beginning_of_wide_string(array_constant_7,
		      FIX((SI_Long)42L));
	      candidate_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    a_string = Nil;
    ab_loop_list_ = Compiler_errors;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    a_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_eq_w(a_string,candidate_string)) {
	temp = TRUEP(T);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	reclaim_text_string(candidate_string);
	return VALUES_1(Nil);
    }
    else {
	Compiler_errors = phrase_cons(candidate_string,Compiler_errors);
	return VALUES_1(Nil);
    }
}

static Object Qprocedure_compiler_warnings;  /* procedure-compiler-warnings */

static Object Qprocedure_compiler_errors;  /* procedure-compiler-errors */

/* REMOVE-COMPILER-ERROR-AND-WARNING-FRAME-NOTES */
Object remove_compiler_error_and_warning_frame_notes()
{
    Object block, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(139,25);
    block = Current_computation_frame;
    delete_frame_note_if_any(Qcompiler_warnings,block);
    delete_frame_note_if_any(Qcompiler_errors,block);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
    if (temp) {
	delete_frame_note_if_any(Qprocedure_compiler_warnings,block);
	return delete_frame_note_if_any(Qprocedure_compiler_errors,block);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-COMPILER-ERROR-AND-WARNING-FRAME-NOTES */
Object add_compiler_error_and_warning_frame_notes()
{
    Object temp;

    x_note_fn_call(139,26);
    if (Compiler_warnings) {
	temp = Current_computation_frame;
	add_frame_note(5,Qcompiler_warnings,temp,
		nreverse(copy_list_using_slot_value_conses_1(Compiler_warnings)),
		T,Nil);
	Compiler_warnings = Nil;
    }
    if (Compiler_errors) {
	temp = Current_computation_frame;
	add_frame_note(5,Qcompiler_errors,temp,
		nreverse(copy_list_using_slot_value_conses_1(Compiler_errors)),
		T,Nil);
	Compiler_errors = Nil;
	return VALUES_1(Compiler_errors);
    }
    else
	return VALUES_1(Nil);
}

/* COMPILER-ERRORS? */
Object compiler_errors_qm(frame)
    Object frame;
{
    x_note_fn_call(139,27);
    return memq_function(Qcompiler_errors,ISVREF(frame,(SI_Long)8L));
}

/* CLEAR-COMPILER-ERRORS */
Object clear_compiler_errors()
{
    Object string_1, ab_loop_list_;

    x_note_fn_call(139,28);
    string_1 = Nil;
    ab_loop_list_ = Compiler_errors;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_text_string(string_1);
    goto next_loop;
  end_loop:;
    Compiler_errors = Nil;
    return VALUES_1(Compiler_errors);
}

static Object string_constant;     /* "the compiler reported the following warning: ~a" */

static Object string_constant_1;   /* "the compiler reported the following warnings: " */

static Object array_constant_8;    /* # */

static Object string_constant_2;   /* "(~a) ~a" */

/* WRITE-COMPILER-WARNINGS-NOTE */
Object write_compiler_warnings_note(warning_strings,gensymed_symbol)
    Object warning_strings, gensymed_symbol;
{
    Object temp, warning, ab_loop_list_, ab_loop_iter_flag_, incff_1_arg;
    Object frame_note_index_skip_new_value;
    SI_Long warning_index;

    x_note_fn_call(139,29);
    if ( !TRUEP(CDR(warning_strings)))
	temp = tformat(2,string_constant,CAR(warning_strings));
    else {
	warning = Nil;
	ab_loop_list_ = warning_strings;
	warning_index = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
	tformat(1,string_constant_1);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	warning = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    warning_index = warning_index + (SI_Long)1L;
	if ( !(warning_index == (SI_Long)0L))
	    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)2L));
	tformat(3,string_constant_2,FIX(IFIX(Frame_note_index) + 
		warning_index),warning);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	incff_1_arg = length(CDR(warning_strings));
	frame_note_index_skip_new_value = FIXNUM_ADD(Frame_note_index_skip,
		incff_1_arg);
	Frame_note_index_skip = frame_note_index_skip_new_value;
	temp = Qnil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* "the compiler reported the following error: ~a" */

static Object string_constant_4;   /* "the compiler reported the following errors: " */

/* WRITE-COMPILER-ERRORS-NOTE */
Object write_compiler_errors_note(error_strings,gensymed_symbol)
    Object error_strings, gensymed_symbol;
{
    Object temp, error_1, ab_loop_list_, ab_loop_iter_flag_, incff_1_arg;
    Object frame_note_index_skip_new_value;
    SI_Long error_index;

    x_note_fn_call(139,30);
    if ( !TRUEP(CDR(error_strings)))
	temp = tformat(2,string_constant_3,CAR(error_strings));
    else {
	error_1 = Nil;
	ab_loop_list_ = error_strings;
	error_index = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
	tformat(1,string_constant_4);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	error_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    error_index = error_index + (SI_Long)1L;
	if ( !(error_index == (SI_Long)0L))
	    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)2L));
	tformat(3,string_constant_2,FIX(IFIX(Frame_note_index) + 
		error_index),error_1);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	incff_1_arg = length(CDR(error_strings));
	frame_note_index_skip_new_value = FIXNUM_ADD(Frame_note_index_skip,
		incff_1_arg);
	Frame_note_index_skip = frame_note_index_skip_new_value;
	temp = Qnil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Goto_tags_in_compilation, Qgoto_tags_in_compilation);

DEFINE_VARIABLE_WITH_SYMBOL(Lexically_visible_goto_tags, Qlexically_visible_goto_tags);

DEFINE_VARIABLE_WITH_SYMBOL(Compiler_free_references, Qcompiler_free_references);

DEFINE_VARIABLE_WITH_SYMBOL(Collecting_free_references, Qcollecting_free_references);

DEFINE_VARIABLE_WITH_SYMBOL(Code_body_entries_in_compilation, Qcode_body_entries_in_compilation);

DEFINE_VARIABLE_WITH_SYMBOL(Lexically_visible_code_bodies, Qlexically_visible_code_bodies);

Object The_type_description_of_goto_tag_entry = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_goto_tag_entrys, Qchain_of_available_goto_tag_entrys);

DEFINE_VARIABLE_WITH_SYMBOL(Goto_tag_entry_count, Qgoto_tag_entry_count);

Object Chain_of_available_goto_tag_entrys_vector = UNBOUND;

/* GOTO-TAG-ENTRY-STRUCTURE-MEMORY-USAGE */
Object goto_tag_entry_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,31);
    temp = Goto_tag_entry_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GOTO-TAG-ENTRY-COUNT */
Object outstanding_goto_tag_entry_count()
{
    Object def_structure_goto_tag_entry_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,32);
    gensymed_symbol = IFIX(Goto_tag_entry_count);
    def_structure_goto_tag_entry_variable = Chain_of_available_goto_tag_entrys;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_goto_tag_entry_variable))
	goto end_loop;
    def_structure_goto_tag_entry_variable = 
	    ISVREF(def_structure_goto_tag_entry_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GOTO-TAG-ENTRY-1 */
Object reclaim_goto_tag_entry_1(goto_tag_entry)
    Object goto_tag_entry;
{
    Object temp, svref_arg_2;

    x_note_fn_call(139,33);
    inline_note_reclaim_cons(goto_tag_entry,Nil);
    temp = ISVREF(Chain_of_available_goto_tag_entrys_vector,
	    IFIX(Current_thread_index));
    SVREF(goto_tag_entry,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_goto_tag_entrys_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = goto_tag_entry;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GOTO-TAG-ENTRY */
Object reclaim_structure_for_goto_tag_entry(goto_tag_entry)
    Object goto_tag_entry;
{
    x_note_fn_call(139,34);
    return reclaim_goto_tag_entry_1(goto_tag_entry);
}

static Object Qg2_defstruct_structure_name_goto_tag_entry_g2_struct;  /* g2-defstruct-structure-name::goto-tag-entry-g2-struct */

/* MAKE-PERMANENT-GOTO-TAG-ENTRY-STRUCTURE-INTERNAL */
Object make_permanent_goto_tag_entry_structure_internal()
{
    Object def_structure_goto_tag_entry_variable;
    Object defstruct_g2_goto_tag_entry_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,35);
    def_structure_goto_tag_entry_variable = Nil;
    atomic_incff_symval(Qgoto_tag_entry_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_goto_tag_entry_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_goto_tag_entry_variable = the_array;
	SVREF(defstruct_g2_goto_tag_entry_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_goto_tag_entry_g2_struct;
	def_structure_goto_tag_entry_variable = 
		defstruct_g2_goto_tag_entry_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_goto_tag_entry_variable);
}

/* MAKE-GOTO-TAG-ENTRY-1 */
Object make_goto_tag_entry_1(goto_tag_name,goto_tag_code_body_entry)
    Object goto_tag_name, goto_tag_code_body_entry;
{
    Object def_structure_goto_tag_entry_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,36);
    def_structure_goto_tag_entry_variable = 
	    ISVREF(Chain_of_available_goto_tag_entrys_vector,
	    IFIX(Current_thread_index));
    if (def_structure_goto_tag_entry_variable) {
	svref_arg_1 = Chain_of_available_goto_tag_entrys_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_goto_tag_entry_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_goto_tag_entry_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_goto_tag_entry_g2_struct;
    }
    else
	def_structure_goto_tag_entry_variable = 
		make_permanent_goto_tag_entry_structure_internal();
    inline_note_allocate_cons(def_structure_goto_tag_entry_variable,Nil);
    SVREF(def_structure_goto_tag_entry_variable,FIX((SI_Long)1L)) = 
	    goto_tag_name;
    SVREF(def_structure_goto_tag_entry_variable,FIX((SI_Long)2L)) = 
	    goto_tag_code_body_entry;
    SVREF(def_structure_goto_tag_entry_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_goto_tag_entry_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_goto_tag_entry_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_goto_tag_entry_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_goto_tag_entry_variable);
}

Object The_type_description_of_compiler_code_body_entry = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_compiler_code_body_entrys, Qchain_of_available_compiler_code_body_entrys);

DEFINE_VARIABLE_WITH_SYMBOL(Compiler_code_body_entry_count, Qcompiler_code_body_entry_count);

Object Chain_of_available_compiler_code_body_entrys_vector = UNBOUND;

/* COMPILER-CODE-BODY-ENTRY-STRUCTURE-MEMORY-USAGE */
Object compiler_code_body_entry_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,37);
    temp = Compiler_code_body_entry_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-COMPILER-CODE-BODY-ENTRY-COUNT */
Object outstanding_compiler_code_body_entry_count()
{
    Object def_structure_compiler_code_body_entry_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,38);
    gensymed_symbol = IFIX(Compiler_code_body_entry_count);
    def_structure_compiler_code_body_entry_variable = 
	    Chain_of_available_compiler_code_body_entrys;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_compiler_code_body_entry_variable))
	goto end_loop;
    def_structure_compiler_code_body_entry_variable = 
	    ISVREF(def_structure_compiler_code_body_entry_variable,
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

/* RECLAIM-COMPILER-CODE-BODY-ENTRY-1 */
Object reclaim_compiler_code_body_entry_1(compiler_code_body_entry)
    Object compiler_code_body_entry;
{
    Object temp, svref_arg_2;

    x_note_fn_call(139,39);
    inline_note_reclaim_cons(compiler_code_body_entry,Nil);
    temp = ISVREF(Chain_of_available_compiler_code_body_entrys_vector,
	    IFIX(Current_thread_index));
    SVREF(compiler_code_body_entry,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_compiler_code_body_entrys_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = compiler_code_body_entry;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-COMPILER-CODE-BODY-ENTRY */
Object reclaim_structure_for_compiler_code_body_entry(compiler_code_body_entry)
    Object compiler_code_body_entry;
{
    x_note_fn_call(139,40);
    return reclaim_compiler_code_body_entry_1(compiler_code_body_entry);
}

static Object Qg2_defstruct_structure_name_compiler_code_body_entry_g2_struct;  /* g2-defstruct-structure-name::compiler-code-body-entry-g2-struct */

/* MAKE-PERMANENT-COMPILER-CODE-BODY-ENTRY-STRUCTURE-INTERNAL */
Object make_permanent_compiler_code_body_entry_structure_internal()
{
    Object def_structure_compiler_code_body_entry_variable;
    Object defstruct_g2_compiler_code_body_entry_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,41);
    def_structure_compiler_code_body_entry_variable = Nil;
    atomic_incff_symval(Qcompiler_code_body_entry_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_compiler_code_body_entry_variable = Nil;
	gensymed_symbol = (SI_Long)12L;
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
	defstruct_g2_compiler_code_body_entry_variable = the_array;
	SVREF(defstruct_g2_compiler_code_body_entry_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_compiler_code_body_entry_g2_struct;
	def_structure_compiler_code_body_entry_variable = 
		defstruct_g2_compiler_code_body_entry_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_compiler_code_body_entry_variable);
}

/* MAKE-COMPILER-CODE-BODY-ENTRY-1 */
Object make_compiler_code_body_entry_1(compiler_code_body_environment_description,
	    compiler_code_body_surrounding_body_number_qm)
    Object compiler_code_body_environment_description;
    Object compiler_code_body_surrounding_body_number_qm;
{
    Object def_structure_compiler_code_body_entry_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(139,42);
    def_structure_compiler_code_body_entry_variable = 
	    ISVREF(Chain_of_available_compiler_code_body_entrys_vector,
	    IFIX(Current_thread_index));
    if (def_structure_compiler_code_body_entry_variable) {
	svref_arg_1 = Chain_of_available_compiler_code_body_entrys_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_compiler_code_body_entry_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_compiler_code_body_entry_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_compiler_code_body_entry_g2_struct;
    }
    else
	def_structure_compiler_code_body_entry_variable = 
		make_permanent_compiler_code_body_entry_structure_internal();
    inline_note_allocate_cons(def_structure_compiler_code_body_entry_variable,
	    Nil);
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)3L)) = compiler_code_body_environment_description;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)4L)) = compiler_code_body_surrounding_body_number_qm;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_compiler_code_body_entry_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_compiler_code_body_entry_variable,
	    FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_compiler_code_body_entry_variable);
}

Object Maximum_code_body_count = UNBOUND;

static Object string_constant_5;   /* "nested code body establishment" */

static Object string_constant_6;   /* "Attempting to create multiple code bodies within ~NF, when they ~
				    *        can only exist within procedures."
				    */

static Object string_constant_7;   /* "The maximum number of code bodies within a single procedure, ~a, ~
				    *        has been exceeded.  Code bodies are generated by do in parallel ~
				    *        and on error statements.  You must reduce the number of do in
				    *        parallel and on error statements for this procedure to compile."
				    */

/* CHECK-FOR-NEW-CODE-BODY-ERRORS */
Object check_for_new_code_body_errors()
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(139,43);
    if (CDR(Code_body_entries_in_compilation)) {
	sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	compiler_bug(3,string_constant_5,string_constant_6,
		Current_computation_frame);
    if (FIXNUM_GE(length(Code_body_entries_in_compilation),
	    Maximum_code_body_count))
	compiler_error(2,string_constant_7,Maximum_code_body_count);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Code_body, Qcode_body);

/* GENERATE-LIST-OF-LEXICALLY-VISIBLE-CODE-BODIES */
Object generate_list_of_lexically_visible_code_bodies(compiler_code_body_entry)
    Object compiler_code_body_entry;
{
    Object code_body, surrounding_code_body_number_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;
    Declare_special(1);

    x_note_fn_call(139,44);
    code_body = compiler_code_body_entry;
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      surrounding_code_body_number_qm = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      surrounding_code_body_number_qm = ISVREF(Code_body,(SI_Long)4L);
      ab_loopvar__2 = phrase_cons(Code_body,Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      if ( !TRUEP(surrounding_code_body_number_qm))
	  goto end_loop;
      Code_body = nth(surrounding_code_body_number_qm,
	      Code_body_entries_in_compilation);
      goto next_loop;
    end_loop:
      temp = ab_loopvar_;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* EMIT-ALREADY-CONSED-INSTRUCTION */
Object emit_already_consed_instruction(instruction)
    Object instruction;
{
    Object body, modify_macro_for_phrase_push_arg, svref_new_value;

    x_note_fn_call(139,45);
    body = CAR(Lexically_visible_code_bodies);
    modify_macro_for_phrase_push_arg = instruction;
    svref_new_value = phrase_cons_with_args_reversed(ISVREF(body,
	    (SI_Long)1L),modify_macro_for_phrase_push_arg);
    SVREF(body,FIX((SI_Long)1L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object The_type_description_of_pseudo_instruction_stream = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_pseudo_instruction_streams, Qchain_of_available_pseudo_instruction_streams);

DEFINE_VARIABLE_WITH_SYMBOL(Pseudo_instruction_stream_count, Qpseudo_instruction_stream_count);

Object Chain_of_available_pseudo_instruction_streams_vector = UNBOUND;

/* PSEUDO-INSTRUCTION-STREAM-STRUCTURE-MEMORY-USAGE */
Object pseudo_instruction_stream_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,46);
    temp = Pseudo_instruction_stream_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PSEUDO-INSTRUCTION-STREAM-COUNT */
Object outstanding_pseudo_instruction_stream_count()
{
    Object def_structure_pseudo_instruction_stream_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,47);
    gensymed_symbol = IFIX(Pseudo_instruction_stream_count);
    def_structure_pseudo_instruction_stream_variable = 
	    Chain_of_available_pseudo_instruction_streams;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_pseudo_instruction_stream_variable))
	goto end_loop;
    def_structure_pseudo_instruction_stream_variable = 
	    ISVREF(def_structure_pseudo_instruction_stream_variable,
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

/* RECLAIM-PSEUDO-INSTRUCTION-STREAM-1 */
Object reclaim_pseudo_instruction_stream_1(pseudo_instruction_stream)
    Object pseudo_instruction_stream;
{
    Object temp, svref_arg_2;

    x_note_fn_call(139,48);
    inline_note_reclaim_cons(pseudo_instruction_stream,Nil);
    temp = ISVREF(Chain_of_available_pseudo_instruction_streams_vector,
	    IFIX(Current_thread_index));
    SVREF(pseudo_instruction_stream,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_pseudo_instruction_streams_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = pseudo_instruction_stream;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PSEUDO-INSTRUCTION-STREAM */
Object reclaim_structure_for_pseudo_instruction_stream(pseudo_instruction_stream)
    Object pseudo_instruction_stream;
{
    x_note_fn_call(139,49);
    return reclaim_pseudo_instruction_stream_1(pseudo_instruction_stream);
}

static Object Qg2_defstruct_structure_name_pseudo_instruction_stream_g2_struct;  /* g2-defstruct-structure-name::pseudo-instruction-stream-g2-struct */

/* MAKE-PERMANENT-PSEUDO-INSTRUCTION-STREAM-STRUCTURE-INTERNAL */
Object make_permanent_pseudo_instruction_stream_structure_internal()
{
    Object def_structure_pseudo_instruction_stream_variable;
    Object defstruct_g2_pseudo_instruction_stream_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,50);
    def_structure_pseudo_instruction_stream_variable = Nil;
    atomic_incff_symval(Qpseudo_instruction_stream_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_pseudo_instruction_stream_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_pseudo_instruction_stream_variable = the_array;
	SVREF(defstruct_g2_pseudo_instruction_stream_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pseudo_instruction_stream_g2_struct;
	def_structure_pseudo_instruction_stream_variable = 
		defstruct_g2_pseudo_instruction_stream_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_pseudo_instruction_stream_variable);
}

/* MAKE-PSEUDO-INSTRUCTION-STREAM-1 */
Object make_pseudo_instruction_stream_1()
{
    Object def_structure_pseudo_instruction_stream_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(139,51);
    def_structure_pseudo_instruction_stream_variable = 
	    ISVREF(Chain_of_available_pseudo_instruction_streams_vector,
	    IFIX(Current_thread_index));
    if (def_structure_pseudo_instruction_stream_variable) {
	svref_arg_1 = Chain_of_available_pseudo_instruction_streams_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_pseudo_instruction_stream_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_pseudo_instruction_stream_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pseudo_instruction_stream_g2_struct;
    }
    else
	def_structure_pseudo_instruction_stream_variable = 
		make_permanent_pseudo_instruction_stream_structure_internal();
    inline_note_allocate_cons(def_structure_pseudo_instruction_stream_variable,
	    Nil);
    SVREF(def_structure_pseudo_instruction_stream_variable,
	    FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_pseudo_instruction_stream_variable);
}

/* MERGE-PSEUDO-INSTRUCTION-STREAM */
Object merge_pseudo_instruction_stream(pseudo_instruction_stream)
    Object pseudo_instruction_stream;
{
    Object body, svref_new_value;

    x_note_fn_call(139,52);
    body = CAR(Lexically_visible_code_bodies);
    svref_new_value = nconc2(ISVREF(pseudo_instruction_stream,(SI_Long)1L),
	    ISVREF(body,(SI_Long)1L));
    SVREF(body,FIX((SI_Long)1L)) = svref_new_value;
    reclaim_pseudo_instruction_stream_1(pseudo_instruction_stream);
    return VALUES_1(Nil);
}

/* MERGE-PSEUDO-INSTRUCTION-STREAMS */
Object merge_pseudo_instruction_streams(target_stream,consumed_stream)
    Object target_stream, consumed_stream;
{
    Object svref_new_value;

    x_note_fn_call(139,53);
    svref_new_value = nconc2(ISVREF(consumed_stream,(SI_Long)1L),
	    ISVREF(target_stream,(SI_Long)1L));
    SVREF(target_stream,FIX((SI_Long)1L)) = svref_new_value;
    reclaim_pseudo_instruction_stream_1(consumed_stream);
    return VALUES_1(Nil);
}

/* EMIT-ALREADY-CONSED-INSTRUCTION-TO-STREAM */
Object emit_already_consed_instruction_to_stream(stream,instruction)
    Object stream, instruction;
{
    Object modify_macro_for_phrase_push_arg, svref_new_value;

    x_note_fn_call(139,54);
    modify_macro_for_phrase_push_arg = instruction;
    svref_new_value = phrase_cons_with_args_reversed(ISVREF(stream,
	    (SI_Long)1L),modify_macro_for_phrase_push_arg);
    SVREF(stream,FIX((SI_Long)1L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object string_constant_8;   /* "The tag ~a is declared more than once in this procedure." */

/* RECORD-NEW-GOTO-TAG */
Object record_new_goto_tag(tag_name)
    Object tag_name;
{
    Object entry, ab_loop_list_, ab_loop_it_, temp, new_entry;
    char temp_1;

    x_note_fn_call(139,55);
    entry = Nil;
    ab_loop_list_ = Lexically_visible_goto_tags;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(entry,(SI_Long)1L);
    ab_loop_it_ = EQL(temp,tag_name) ? T : Nil;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = TRUEP(Qnil);
  end_1:;
    if (temp_1)
	return compiler_error(2,string_constant_8,tag_name);
    else {
	temp = mangle_tag_in_context(tag_name);
	new_entry = make_goto_tag_entry_1(temp,
		CAR(Lexically_visible_code_bodies));
	Lexically_visible_goto_tags = phrase_cons(new_entry,
		Lexically_visible_goto_tags);
	Goto_tags_in_compilation = phrase_cons(new_entry,
		Goto_tags_in_compilation);
	return VALUES_1(Goto_tags_in_compilation);
    }
}

static Object string_constant_9;   /* "Illegal branch attempt to tag ~a.  Branches may not be ~
				    *                     performed into the bodies of iteration statements, into IN ~
				    *                     PARALLEL statements, or into the bodies of ON ERROR ~
				    *                     statements."
				    */

static Object string_constant_10;  /* "Illegal branch to the tag ~a, which is not defined." */

/* JUMP-DEPTH-FOR-TAG? */
Object jump_depth_for_tag_qm(tag_name)
    Object tag_name;
{
    Object entry, ab_loop_list_, temp, tag_entry_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ab_loop_it_, candidate_string, a_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(5);

    x_note_fn_call(139,56);
    entry = Nil;
    ab_loop_list_ = Lexically_visible_goto_tags;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(entry,(SI_Long)1L);
    if (EQL(temp,tag_name)) {
	tag_entry_qm = entry;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    tag_entry_qm = Qnil;
  end_1:;
    if ( !TRUEP(tag_entry_qm)) {
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
		  twrite_compiler_message_header();
		  entry = Nil;
		  ab_loop_list_ = Goto_tags_in_compilation;
		  ab_loop_it_ = Nil;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  entry = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  temp = ISVREF(entry,(SI_Long)1L);
		  ab_loop_it_ = EQL(temp,tag_name) ? T : Nil;
		  if (ab_loop_it_) {
		      temp_1 = TRUEP(ab_loop_it_);
		      goto end_2;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp_1 = TRUEP(Qnil);
		end_2:;
		  if (temp_1)
		      tformat(2,string_constant_9,tag_name);
		  else
		      tformat(2,string_constant_10,tag_name);
		  candidate_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	a_string = Nil;
	ab_loop_list_ = Compiler_errors;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	a_string = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (string_eq_w(a_string,candidate_string)) {
	    temp_1 = TRUEP(T);
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	temp_1 = TRUEP(Qnil);
      end_3:;
	if (temp_1)
	    reclaim_text_string(candidate_string);
	else
	    Compiler_errors = phrase_cons(candidate_string,Compiler_errors);
	return VALUES_1(Nil);
    }
    else if (EQ(CAR(Lexically_visible_code_bodies),ISVREF(tag_entry_qm,
	    (SI_Long)2L))) {
	SVREF(tag_entry_qm,FIX((SI_Long)3L)) = T;
	return VALUES_1(Nil);
    }
    else {
	SVREF(tag_entry_qm,FIX((SI_Long)4L)) = T;
	return position(2,ISVREF(tag_entry_qm,(SI_Long)2L),
		Lexically_visible_code_bodies);
    }
}

Object Goto_tag_recorder_prop = UNBOUND;

static Object Qgoto_tag_recorder;  /* goto-tag-recorder */

/* RECORD-GOTO-TAGS */
Object record_goto_tags(statement)
    Object statement;
{
    Object gensymed_symbol, recorder_qm, gensymed_symbol_1;

    x_note_fn_call(139,57);
    gensymed_symbol = CAR(statement);
    recorder_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qgoto_tag_recorder);
    if (recorder_qm) {
	gensymed_symbol = recorder_qm;
	gensymed_symbol_1 = statement;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(New_goto_tag_counter, Qnew_goto_tag_counter);

/* GENERATE-NEW-GOTO-TAG */
Object generate_new_goto_tag()
{
    Object new_goto_tag_counter_new_value, new_tag;

    x_note_fn_call(139,58);
    new_goto_tag_counter_new_value = FIXNUM_SUB1(New_goto_tag_counter);
    New_goto_tag_counter = new_goto_tag_counter_new_value;
    new_tag = New_goto_tag_counter;
    record_new_goto_tag(new_tag);
    return VALUES_1(new_tag);
}

Object Cached_attribute_cons_marker = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_item_being_analyzed, Qcompiled_item_being_analyzed);

static Object Qname;               /* name */

static Object Qcached_name;        /* cached-name */

static Object Qstable_name;        /* stable-name */

static Object Qname_of_class_instance;  /* name-of-class-instance */

static Object Qname_of_type;       /* name-of-type */

static Object Qstable_name_of_class_instance;  /* stable-name-of-class-instance */

static Object Qab_class;           /* class */

static Object Qstable_subclass;    /* stable-subclass */

static Object Qstable_hierarchy;   /* stable-hierarchy */

static Object Qstable_not_subclass;  /* stable-not-subclass */

static Object Qattribute;          /* attribute */

static Object Qattribute_of_class;  /* attribute-of-class */

static Object Qclass_qualified_attribute_of_class;  /* class-qualified-attribute-of-class */

static Object Qclass_qualified_method;  /* class-qualified-method */

static Object Qcached_attribute;   /* cached-attribute */

static Object Qprocedure_call;     /* procedure-call */

static Object Qremote_procedure_call;  /* remote-procedure-call */

static Object Qstable_procedure_call;  /* stable-procedure-call */

static Object Qstable_remote_procedure_call;  /* stable-remote-procedure-call */

static Object Qstable_compile_time_selected_method;  /* stable-compile-time-selected-method */

static Object Qfunction_call;      /* function-call */

/* ANALYZE-SINGLE-FREE-REFERENCE-FOR-CONSISTENCY */
Object analyze_single_free_reference_for_consistency(type,reference)
    Object type, reference;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, class_1, subclass;
    Object non_subclass, attribute, class_qualifier, domain_class_qm, method;
    Object attribute_name, item_name_qm, class_name_qm, constant_vector_index;
    Object class_specific_attribute_class_qm, name, arg_types, return_types;
    Object selected_class, method_name, first_arg_class;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(139,59);
    if (EQ(type,Qname)) {
	if (SIMPLE_VECTOR_P(Compiled_item_being_analyzed) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Compiled_item_being_analyzed)) 
		> (SI_Long)2L &&  !EQ(ISVREF(Compiled_item_being_analyzed,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(Compiled_item_being_analyzed,(SI_Long)1L);
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
		    IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
	if (temp ? 
		EQ(procedure_method_name_function(Compiled_item_being_analyzed),
		reference) : TRUEP(Nil))
	    return check_for_valid_method(reference);
	else
	    return check_for_undefined_instance_name(reference);
    }
    else if (EQ(type,Qcached_name))
	return check_for_cached_name_undefined_instance(M_CAR(reference),
		M_CDR(reference));
    else if (EQ(type,Qstable_name))
	return check_for_unstable_instance_name(reference);
    else if (EQ(type,Qname_of_class_instance))
	return check_undefined_instances_of_class(M_CAR(reference),
		M_CDR(reference));
    else if (EQ(type,Qname_of_type))
	return check_undefined_instances_of_type(M_CAR(reference),
		M_CDR(reference));
    else if (EQ(type,Qstable_name_of_class_instance))
	return check_for_unstable_instance_name_of_class(CAR(reference),
		CDR(reference));
    else if (EQ(type,Qab_class))
	return check_for_undefined_class(reference);
    else if (EQ(type,Qstable_subclass)) {
	class_1 = CAR(reference);
	subclass = CDR(reference);
	return check_for_unstable_class_and_subclass(class_1,subclass);
    }
    else if (EQ(type,Qstable_hierarchy))
	return VALUES_1(Nil);
    else if (EQ(type,Qinline))
	return check_for_invalid_inlining(reference);
    else if (EQ(type,Qstable_not_subclass)) {
	class_1 = CAR(reference);
	non_subclass = CDR(reference);
	return check_for_unstable_class_and_non_subclass(class_1,non_subclass);
    }
    else if (EQ(type,Qattribute))
	return check_for_undefined_attribute(reference);
    else if (EQ(type,Qattribute_of_class)) {
	if (M_CDR(reference))
	    return check_for_undefined_attribute_of_class(M_CAR(reference),
		    M_CDR(reference));
	else
	    return check_for_undefined_attribute(M_CAR(reference));
    }
    else if (EQ(type,Qclass_qualified_attribute_of_class)) {
	attribute = FIRST(reference);
	class_qualifier = SECOND(reference);
	domain_class_qm = THIRD(reference);
	if (domain_class_qm)
	    return check_for_undefined_class_qualified_attribute_of_class(attribute,
		    class_qualifier,domain_class_qm);
	else
	    return check_for_undefined_class_qualified_attribute(attribute,
		    class_qualifier);
    }
    else if (EQ(type,Qclass_qualified_method)) {
	method = FIRST(reference);
	class_qualifier = SECOND(reference);
	return check_for_undefined_class_qualified_method(method,
		class_qualifier);
    }
    else if (EQ(type,Qcached_attribute)) {
	gensymed_symbol = reference;
	attribute_name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	item_name_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	class_name_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	constant_vector_index = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	class_specific_attribute_class_qm = CAR(gensymed_symbol);
	return check_for_cached_attribute(attribute_name,item_name_qm,
		class_name_qm,class_specific_attribute_class_qm,
		constant_vector_index);
    }
    else if (EQ(type,Qprocedure_call) || EQ(type,Qremote_procedure_call)) {
	gensymed_symbol = reference;
	name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	arg_types = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	return_types = CAR(gensymed_symbol);
	return check_for_valid_procedure_call(type,name,arg_types,
		return_types,Nil,Nil);
    }
    else if (EQ(type,Qstable_procedure_call) || EQ(type,
	    Qstable_remote_procedure_call)) {
	gensymed_symbol = reference;
	name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	arg_types = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	return_types = CAR(gensymed_symbol);
	return check_for_valid_stable_procedure_call(type,name,arg_types,
		return_types);
    }
    else if (EQ(type,Qstable_compile_time_selected_method)) {
	gensymed_symbol = reference;
	selected_class = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	method_name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	first_arg_class = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	arg_types = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	return_types = CAR(gensymed_symbol);
	return check_for_valid_stable_compile_time_selected_method(selected_class,
		method_name,first_arg_class,arg_types,return_types);
    }
    else if (EQ(type,Qfunction_call)) {
	gensymed_symbol = reference;
	name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	arg_types = CAR(gensymed_symbol);
	return check_for_valid_function_call(name,arg_types);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_free_reference_recording, Qinhibit_free_reference_recording);

static Object string_constant_11;  /* "free reference recorder" */

static Object string_constant_12;  /* "A reference of type ~a was badly formed: reference = ~a" */

static Object Qitem;               /* item */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* RECORD-FREE-REFERENCE */
Object record_free_reference(type_of_reference,reference)
    Object type_of_reference, reference;
{
    Object transform_again_qm, temp, skip_list, key_value, marked, pred, curr;
    Object succ, reference_1, temp_2, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, type;
    Object ab_loop_list_, class_1, name, arg_count, md5, entry;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(139,60);
    if ( !TRUEP(Inhibit_free_reference_recording)) {
	transform_again_qm = Nil;
      next_loop:
	transform_again_qm = Nil;
	if (EQ(type_of_reference,Qname) || EQ(type_of_reference,
		    Qstable_name)) {
	    if ( !(reference && SYMBOLP(reference))) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qname_of_class_instance) || 
		EQ(type_of_reference,Qstable_name_of_class_instance)) {
	    if (CONSP(reference)) {
		temp = M_CAR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = M_CDR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	    if (EQ(M_CDR(reference),Qitem)) {
		if (EQ(type_of_reference,Qstable_name_of_class_instance))
		    type_of_reference = Qstable_name;
		else
		    type_of_reference = Qname;
		reference = M_CAR(reference);
		transform_again_qm = T;
	    }
	}
	else if (EQ(type_of_reference,Qname_of_type)) {
	    if (CONSP(reference)) {
		temp = M_CAR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !(temp_1 ? 
		    TRUEP(valid_type_specification_p(M_CDR(reference))) : 
		    TRUEP(Nil))) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	    if (class_type_specification_p(M_CDR(reference))) {
		type_of_reference = Qname_of_class_instance;
		reference = phrase_cons(M_CAR(reference),
			type_specification_class_function(M_CDR(reference)));
		transform_again_qm = T;
	    }
	}
	else if (EQ(type_of_reference,Qcached_name)) {
	    if (CONSP(reference)) {
		temp = M_CAR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !(temp_1 ? FIXNUMP(M_CDR(reference)) : TRUEP(Nil))) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qab_class)) {
	    if ( !(reference && SYMBOLP(reference))) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	    if (lookup_global_or_kb_specific_property_value(reference,
		    Class_description_gkbprop)) {
		temp = 
			lookup_global_or_kb_specific_property_value(reference,
			Class_definition_gkbprop);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		skip_list = CDR(Symbol_properties_table);
		key_value = reference;
		key_hash_value = SXHASH_SYMBOL_1(reference) & 
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
		    goto end_loop;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_2:
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference_1);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_3:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference_1);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_3;
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
		goto next_loop_2;
	      end_loop_2:
	      end_1:
		level = level - (SI_Long)1L;
		goto next_loop_1;
	      end_loop:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = reference;
		    temp_2 = Symbol_properties_table;
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
		    gensymed_symbol = set_skip_list_entry(temp_2,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
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
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_5:
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference_1);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_6:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference_1);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_6;
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
		goto next_loop_5;
	      end_loop_5:
	      end_2:
		level = level - (SI_Long)1L;
		goto next_loop_4;
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
		  next_loop_7:
		    if (level < ab_loop_bind_)
			goto end_loop_6;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_8:
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference_1);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_9:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference_1);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_9;
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
		    goto next_loop_8;
		  end_loop_8:
		  end_3:
		    level = level - (SI_Long)1L;
		    goto next_loop_7;
		  end_loop_6:;
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
		  next_loop_10:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_11:
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference_1);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_12:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference_1);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_12;
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
		    goto next_loop_11;
		  end_loop_11:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_10;
		  end_loop_9:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp_1 = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
			(SI_Long)16L)) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return VALUES_1(Nil);
	}
	else if (EQ(type_of_reference,Qattribute_of_class)) {
	    if (CONSP(reference)) {
		if (M_CAR(reference)) {
		    temp = M_CAR(reference);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = M_CDR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	    if ( !TRUEP(M_CDR(reference)) || EQ(M_CDR(reference),Qitem)) {
		type_of_reference = Qattribute;
		reference = M_CAR(reference);
		transform_again_qm = T;
	    }
	}
	else if (EQ(type_of_reference,Qclass_qualified_attribute_of_class)) {
	    if (LISTP(reference)) {
		if (FIRST(reference)) {
		    temp = FIRST(reference);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		if (SECOND(reference)) {
		    temp = SECOND(reference);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		if (THIRD(reference)) {
		    temp = THIRD(reference);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qclass_qualified_method)) {
	    if (LISTP(reference)) {
		if (FIRST(reference)) {
		    temp = FIRST(reference);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		if (SECOND(reference)) {
		    temp = SECOND(reference);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qattribute)) {
	    if ( !(reference && SYMBOLP(reference))) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qcached_attribute)) {
	    if (reference && LISTP(reference)) {
		if (FIRST(reference)) {
		    temp = FIRST(reference);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = SECOND(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = THIRD(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = FOURTH(reference);
		temp_1 = NUMBERP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = FIFTH(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !(temp_1 ? EQ(SIXTH(reference),
		    Cached_attribute_cons_marker) : TRUEP(Nil))) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qprocedure_call) || 
		EQ(type_of_reference,Qremote_procedure_call) || 
		EQ(type_of_reference,Qstable_procedure_call) || 
		EQ(type_of_reference,Qstable_remote_procedure_call)) {
	    if (CONSP(reference)) {
		temp = M_CAR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = M_CDR(reference);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = SECOND(reference);
		temp_1 = LISTP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		type = Nil;
		ab_loop_list_ = SECOND(reference);
	      next_loop_13:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_12;
		type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(valid_type_specification_p(type))) {
		    temp_1 = TRUEP(Nil);
		    goto end_5;
		}
		goto next_loop_13;
	      end_loop_12:
		temp_1 = TRUEP(T);
		goto end_5;
		temp_1 = TRUEP(Qnil);
	      end_5:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = CDDR(reference);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = THIRD(reference);
		temp_1 = LISTP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		type = Nil;
		ab_loop_list_ = THIRD(reference);
	      next_loop_14:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_13;
		type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(valid_type_specification_p(type))) {
		    temp_1 = TRUEP(Nil);
		    goto end_6;
		}
		goto next_loop_14;
	      end_loop_13:
		temp_1 = TRUEP(T);
		goto end_6;
		temp_1 = TRUEP(Qnil);
	      end_6:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qstable_compile_time_selected_method)) {
	    if (LISTP(reference)) {
		temp = FIRST(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = SECOND(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = THIRD(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		type = Nil;
		ab_loop_list_ = FOURTH(reference);
	      next_loop_15:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_14;
		type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(valid_type_specification_p(type))) {
		    temp_1 = TRUEP(Nil);
		    goto end_7;
		}
		goto next_loop_15;
	      end_loop_14:
		temp_1 = TRUEP(T);
		goto end_7;
		temp_1 = TRUEP(Qnil);
	      end_7:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		type = Nil;
		ab_loop_list_ = FIFTH(reference);
	      next_loop_16:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_15;
		type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(valid_type_specification_p(type))) {
		    temp_1 = TRUEP(Nil);
		    goto end_8;
		}
		goto next_loop_16;
	      end_loop_15:
		temp_1 = TRUEP(T);
		goto end_8;
		temp_1 = TRUEP(Qnil);
	      end_8:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qfunction_call)) {
	    if (CONSP(reference)) {
		temp = M_CAR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = M_CDR(reference);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = SECOND(reference);
		temp_1 = LISTP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		type = Nil;
		ab_loop_list_ = SECOND(reference);
	      next_loop_17:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_16;
		type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(valid_type_specification_p(type))) {
		    temp_1 = TRUEP(Nil);
		    goto end_9;
		}
		goto next_loop_17;
	      end_loop_16:
		temp_1 = TRUEP(T);
		goto end_9;
		temp_1 = TRUEP(Qnil);
	      end_9:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qstable_subclass) || 
		EQ(type_of_reference,Qstable_not_subclass)) {
	    if (CONSP(reference)) {
		temp = M_CAR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = M_CDR(reference);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(type_of_reference,Qstable_hierarchy)) {
	    compiler_bug(4,string_constant_11,string_constant_12,
		    type_of_reference,reference);
	    return VALUES_1(Nil);
	}
	else if (EQ(type_of_reference,Qinline)) {
	    if (CONSP(reference)) {
		gensymed_symbol = reference;
		class_1 = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		name = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		arg_count = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		md5 = CAR(gensymed_symbol);
		temp_1 = SYMBOLP(class_1) && SYMBOLP(name) && 
			FIXNUMP(arg_count) ? 
			INLINE_UNSIGNED_BYTE_16_VECTOR_P(md5) != 
			(SI_Long)0L : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		compiler_bug(4,string_constant_11,string_constant_12,
			type_of_reference,reference);
		return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
	if ( !TRUEP(transform_again_qm))
	    goto end_loop_17;
	goto next_loop;
      end_loop_17:;
	entry = Nil;
	ab_loop_list_ = Compiler_free_references;
      next_loop_18:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_18;
	entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(type_of_reference,M_CAR(entry)) && equalw(reference,
		M_CDR(entry)))
	    return VALUES_1(Nil);
	goto next_loop_18;
      end_loop_18:;
	Compiler_free_references = 
		phrase_cons(phrase_cons(type_of_reference,reference),
		Compiler_free_references);
    }
    return VALUES_1(Nil);
}

/* INSTALL-FREE-REFERENCES-IN-BYTE-CODE-BODY */
Object install_free_references_in_byte_code_body(byte_code_body,
	    free_references)
    Object byte_code_body, free_references;
{
    Object new_vector_qm, free_references_count, reference_type;
    Object reference_value, ab_loop_list_, length_1, ab_loop_iter_flag_;
    Object ab_loop_desetq_, svref_new_value;
    SI_Long requested_length, index_1, svref_arg_2, i, ab_loop_bind_;

    x_note_fn_call(139,61);
    reclaim_if_simple_vector_of_slot_values(ISVREF(byte_code_body,
	    (SI_Long)7L));
    new_vector_qm = Nil;
    free_references_count = length(free_references);
    requested_length = IFIX(free_references_count) * (SI_Long)2L;
    if (IFIX(free_references_count) > (SI_Long)0L) {
	new_vector_qm = allocate_managed_simple_vector(FIX(requested_length));
	reference_type = Nil;
	reference_value = Nil;
	ab_loop_list_ = free_references;
	length_1 = SIMPLE_ARRAY_ANY_1_LENGTH(new_vector_qm);
	index_1 = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	reference_type = CAR(ab_loop_desetq_);
	reference_value = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 + (SI_Long)2L;
	svref_new_value = copy_for_slot_value(reference_type);
	ISVREF(new_vector_qm,index_1) = svref_new_value;
	svref_arg_2 = index_1 + (SI_Long)1L;
	svref_new_value = copy_for_slot_value(reference_value);
	ISVREF(new_vector_qm,svref_arg_2) = svref_new_value;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (requested_length < IFIX(length_1)) {
	    i = index_1 + (SI_Long)2L;
	    ab_loop_bind_ = IFIX(length_1);
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    ISVREF(new_vector_qm,i) = Nil;
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
    }
    SVREF(byte_code_body,FIX((SI_Long)7L)) = new_vector_qm;
    return VALUES_1(Nil);
}

static Object string_constant_13;  /* "~(~a: ~a~)" */

static Object string_constant_14;  /* "~(~a: ~a of class ~a~)" */

static Object string_constant_15;  /* "~(~a: ~a of type ~NT~)" */

static Object string_constant_16;  /* "~(~a: ~a, constant: ~a~)" */

static Object string_constant_17;  /* "item" */

static Object string_constant_18;  /* "~(~a: ~a of ~a~)" */

static Object string_constant_19;  /* "~(~a: ~NQ of ~a~)" */

static Object string_constant_20;  /* "~(, from class: ~a~)" */

static Object string_constant_21;  /* "~(, constant: ~a~)" */

static Object string_constant_22;  /* "~(~a: ~a ~)" */

static Object array_constant_9;    /* # */

static Object string_constant_23;  /* "~(~a: call to ~a for first argument ~a selected ~a::~a~)" */

static Object string_constant_24;  /* "~(~a: superior class ~a, subclass ~a~)" */

static Object string_constant_25;  /* "~(unused ~a: ~a~)" */

/* TWRITE-SINGLE-FREE-REFERENCE-FOR-CONSISTENCY */
Object twrite_single_free_reference_for_consistency(type,reference)
    Object type, reference;
{
    Object temp, temp_1, temp_2, gensymed_symbol, selected_class, method_name;
    Object first_arg_class, arg_types, return_types;

    x_note_fn_call(139,62);
    if (EQ(type,Qname) || EQ(type,Qstable_name))
	return tformat(3,string_constant_13,type,reference);
    else if (EQ(type,Qname_of_class_instance) || EQ(type,
	    Qstable_name_of_class_instance))
	return tformat(4,string_constant_14,type,CAR(reference),
		CDR(reference));
    else if (EQ(type,Qname_of_type))
	return tformat(4,string_constant_15,type,CAR(reference),
		CDR(reference));
    else if (EQ(type,Qcached_name))
	return tformat(4,string_constant_16,type,CAR(reference),
		CDR(reference));
    else if (EQ(type,Qab_class))
	return tformat(3,string_constant_13,type,reference);
    else if (EQ(type,Qattribute_of_class)) {
	temp = CAR(reference);
	temp_1 = CDR(reference);
	if (temp_1);
	else
	    temp_1 = string_constant_17;
	return tformat(4,string_constant_18,type,temp,temp_1);
    }
    else if (EQ(type,Qclass_qualified_attribute_of_class)) {
	temp_2 = FIRST(reference);
	temp = SECOND(reference);
	temp_1 = THIRD(reference);
	if (temp_1);
	else
	    temp_1 = string_constant_17;
	return tformat(5,string_constant_19,type,temp_2,temp,temp_1);
    }
    else if (EQ(type,Qattribute))
	return tformat(3,string_constant_13,type,reference);
    else if (EQ(type,Qcached_attribute)) {
	temp_1 = FIRST(reference);
	temp = SECOND(reference);
	if (temp);
	else
	    temp = THIRD(reference);
	if (temp);
	else
	    temp = string_constant_17;
	tformat(4,string_constant_18,type,temp_1,temp);
	if (fifth(reference))
	    tformat(2,string_constant_20,FIFTH(reference));
	if (FOURTH(reference))
	    return tformat(2,string_constant_21,FOURTH(reference));
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(type,Qprocedure_call) || EQ(type,Qremote_procedure_call) 
	    || EQ(type,Qstable_procedure_call) || EQ(type,
	    Qstable_remote_procedure_call)) {
	tformat(3,string_constant_22,type,CAR(reference));
	write_list_of_type_specifications(SECOND(reference));
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)3L));
	return write_list_of_type_specifications(THIRD(reference));
    }
    else if (EQ(type,Qstable_compile_time_selected_method)) {
	gensymed_symbol = reference;
	selected_class = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	method_name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	first_arg_class = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	arg_types = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	return_types = CAR(gensymed_symbol);
	tformat(6,string_constant_23,type,method_name,first_arg_class,
		selected_class,method_name);
	write_list_of_type_specifications(arg_types);
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)3L));
	return write_list_of_type_specifications(return_types);
    }
    else if (EQ(type,Qfunction_call)) {
	tformat(3,string_constant_22,type,CAR(reference));
	return write_list_of_type_specifications(SECOND(reference));
    }
    else if (EQ(type,Qstable_subclass) || EQ(type,Qstable_not_subclass))
	return tformat(4,string_constant_24,type,CAR(reference),
		CDR(reference));
    else if (EQ(type,Qinline))
	return tformat(3,string_constant_13,type,reference);
    else if (EQ(type,Qstable_hierarchy))
	return tformat(3,string_constant_13,type,reference);
    else
	return tformat(3,string_constant_25,type,reference);
}

static Object array_constant_10;   /* # */

/* WRITE-LIST-OF-TYPE-SPECIFICATIONS */
Object write_list_of_type_specifications(types)
    Object types;
{
    Object temp, aref_arg_2, first_time, type, ab_loop_list_;

    x_note_fn_call(139,63);
    if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
	    Total_length_of_current_wide_string))
	extend_current_wide_string(Fill_pointer_for_current_wide_string);
    temp = Current_wide_string;
    aref_arg_2 = Fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)40L);
    temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
    Fill_pointer_for_current_wide_string = temp;
    first_time = T;
    type = Nil;
    ab_loop_list_ = types;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(first_time))
	twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)2L));
    write_type_specification(type);
    first_time = Nil;
    goto next_loop;
  end_loop:;
    if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
	    Total_length_of_current_wide_string))
	extend_current_wide_string(Fill_pointer_for_current_wide_string);
    temp = Current_wide_string;
    aref_arg_2 = Fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)41L);
    temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
    Fill_pointer_for_current_wide_string = temp;
    return VALUES_1(Fill_pointer_for_current_wide_string);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qvariable_or_parameter;  /* variable-or-parameter */

static Object list_constant_2;     /* # */

/* REDUNDANT-PARAMETER-FREE-REFERENCE? */
Object redundant_parameter_free_reference_qm(ref,ref_list)
    Object ref, ref_list;
{
    Object result_qm, list_of_free_reference_types, gensymed_symbol, ref_kind;
    Object free_ref, ref_name_qm, ref_type_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object sub_class_bit_vector, test_ref, ab_loop_list_, test_ref_name_qm;
    Object test_ref_type_qm, test_kind, test_free_ref;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(139,64);
    if (CONSP(ref)) {
	result_qm = Nil;
	list_of_free_reference_types = list_constant;
	gensymed_symbol = ref;
	ref_kind = CAR(gensymed_symbol);
	free_ref = CDR(gensymed_symbol);
	ref_name_qm = Nil;
	ref_type_qm = Nil;
	if (memq_function(ref_kind,list_of_free_reference_types) && 
		LISTP(free_ref) && M_CDR(free_ref)) {
	    ref_name_qm = M_CAR(free_ref);
	    ref_type_qm = M_CDR(free_ref);
	}
	if (ref_name_qm && ref_type_qm) {
	    if (SYMBOLP(ref_type_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = ref_type_qm;
		key_hash_value = SXHASH_SYMBOL_1(ref_type_qm) & 
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
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = ref_type_qm;
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
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
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
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_2 = TRUEP(resulting_value);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		skip_list = CDR(Symbol_properties_table);
		key_value = ref_type_qm;
		key_hash_value = SXHASH_SYMBOL_1(ref_type_qm) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_13:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_14:
		if ( !TRUEP(marked))
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_14;
	      end_loop_13:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = ref_type_qm;
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
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_16:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_17:
		if ( !TRUEP(marked))
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_17;
	      end_loop_16:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		  next_loop_18:
		    if (level < ab_loop_bind_)
			goto end_loop_18;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_19:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_20:
		    if ( !TRUEP(marked))
			goto end_loop_19;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
		  next_loop_21:
		    if (level < ab_loop_bind_)
			goto end_loop_21;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_22:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_23:
		    if ( !TRUEP(marked))
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Parameter_class_description,
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
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2);
	    else
		temp_2 = valid_type_specification_p(ref_type_qm) ? 
			TRUEP(type_specification_subtype_p(ref_type_qm,
			list_constant_1)) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    test_ref = Nil;
	    ab_loop_list_ = ref_list;
	    test_ref_name_qm = Nil;
	    test_ref_type_qm = Nil;
	  next_loop_24:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_24;
	    test_ref = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    test_ref_name_qm = Nil;
	    test_ref_type_qm = Nil;
	    if (result_qm)
		goto end_loop_24;
	    if (CONSP(test_ref) &&  !EQ(test_ref,ref)) {
		gensymed_symbol = test_ref;
		test_kind = CAR(gensymed_symbol);
		test_free_ref = CDR(gensymed_symbol);
		if (memq_function(test_kind,list_of_free_reference_types) 
			&& LISTP(test_free_ref) && M_CDR(test_free_ref)) {
		    test_ref_name_qm = M_CAR(test_free_ref);
		    test_ref_type_qm = M_CDR(test_free_ref);
		    if (test_ref_name_qm && test_ref_type_qm && 
			    EQ(test_ref_name_qm,ref_name_qm)) {
			temp_2 = EQ(test_ref_type_qm,Qvariable_or_parameter);
			if (temp_2);
			else {
			    if (SYMBOLP(test_ref_type_qm)) {
				skip_list = CDR(Symbol_properties_table);
				key_value = test_ref_type_qm;
				key_hash_value = 
					SXHASH_SYMBOL_1(test_ref_type_qm) 
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
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_26:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_27:
				if ( !TRUEP(marked))
				    goto end_loop_26;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_27;
			      end_loop_26:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_9;
				goto next_loop_26;
			      end_loop_27:
			      end_9:
				level = level - (SI_Long)1L;
				goto next_loop_25;
			      end_loop_25:;
				gensymed_symbol = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if ( !TRUEP(gensymed_symbol)) {
				    gensymed_symbol = test_ref_type_qm;
				    temp = Symbol_properties_table;
				    temp_1 = 
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
					    set_skip_list_entry(temp,
					    FIX((SI_Long)31L),Qeq,Nil,T,
					    gensymed_symbol,temp_1,
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
			      next_loop_28:
				if (level < ab_loop_bind_)
				    goto end_loop_28;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_29:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_30:
				if ( !TRUEP(marked))
				    goto end_loop_29;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_30;
			      end_loop_29:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_10;
				goto next_loop_29;
			      end_loop_30:
			      end_10:
				level = level - (SI_Long)1L;
				goto next_loop_28;
			      end_loop_28:;
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
				  next_loop_31:
				    if (level < ab_loop_bind_)
					goto end_loop_31;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_32:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				  next_loop_33:
				    if ( !TRUEP(marked))
					goto end_loop_32;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				    goto next_loop_33;
				  end_loop_32:
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
					goto end_11;
				    goto next_loop_32;
				  end_loop_33:
				  end_11:
				    level = level - (SI_Long)1L;
				    goto next_loop_31;
				  end_loop_31:;
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
				  next_loop_34:
				    if (level < ab_loop_bind_)
					goto end_loop_34;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_35:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				  next_loop_36:
				    if ( !TRUEP(marked))
					goto end_loop_35;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				    goto next_loop_36;
				  end_loop_35:
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
					goto end_12;
				    goto next_loop_35;
				  end_loop_36:
				  end_12:
				    level = level - (SI_Long)1L;
				    goto next_loop_34;
				  end_loop_34:;
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
				temp_2 = TRUEP(resulting_value);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2) {
				skip_list = CDR(Symbol_properties_table);
				key_value = test_ref_type_qm;
				key_hash_value = 
					SXHASH_SYMBOL_1(test_ref_type_qm) 
					& IFIX(Most_positive_fixnum);
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
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_38:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_39:
				if ( !TRUEP(marked))
				    goto end_loop_38;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_39;
			      end_loop_38:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_13;
				goto next_loop_38;
			      end_loop_39:
			      end_13:
				level = level - (SI_Long)1L;
				goto next_loop_37;
			      end_loop_37:;
				gensymed_symbol = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if ( !TRUEP(gensymed_symbol)) {
				    gensymed_symbol = test_ref_type_qm;
				    temp = Symbol_properties_table;
				    temp_1 = 
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
					    set_skip_list_entry(temp,
					    FIX((SI_Long)31L),Qeq,Nil,T,
					    gensymed_symbol,temp_1,
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
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_41:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_42:
				if ( !TRUEP(marked))
				    goto end_loop_41;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_42;
			      end_loop_41:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_14;
				goto next_loop_41;
			      end_loop_42:
			      end_14:
				level = level - (SI_Long)1L;
				goto next_loop_40;
			      end_loop_40:;
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
				  next_loop_43:
				    if (level < ab_loop_bind_)
					goto end_loop_43;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_44:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				  next_loop_45:
				    if ( !TRUEP(marked))
					goto end_loop_44;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				    goto next_loop_45;
				  end_loop_44:
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
					goto end_15;
				    goto next_loop_44;
				  end_loop_45:
				  end_15:
				    level = level - (SI_Long)1L;
				    goto next_loop_43;
				  end_loop_43:;
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
				  next_loop_46:
				    if (level < ab_loop_bind_)
					goto end_loop_46;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_47:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				  next_loop_48:
				    if ( !TRUEP(marked))
					goto end_loop_47;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp = ATOMIC_REF_OBJECT(reference);
				    temp_1 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp,temp_1);
				    MVS_2(result,succ,marked);
				    goto next_loop_48;
				  end_loop_47:
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
					goto end_16;
				    goto next_loop_47;
				  end_loop_48:
				  end_16:
				    level = level - (SI_Long)1L;
				    goto next_loop_46;
				  end_loop_46:;
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
					    IFIX(ISVREF(Variable_or_parameter_class_description,
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
					temp_2 = (SI_Long)0L < 
						gensymed_symbol_3;
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
			if (temp_2);
			else
			    temp_2 = 
				    valid_type_specification_p(test_ref_type_qm) 
				    ? 
				    TRUEP(type_specification_subtype_p(test_ref_type_qm,
				    list_constant_2)) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2)
			result_qm = T;
		}
	    }
	    goto next_loop_24;
	  end_loop_24:;
	}
	temp_1 = result_qm;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Next_stack_frame_var_location, Qnext_stack_frame_var_location);

DEFINE_VARIABLE_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm, Qoutermost_stack_frame_var_binding_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm, Qstack_frame_vars_ok_in_procedure_qm);

static Object string_constant_26;  /* "~a~a~a~a" */

static Object string_constant_27;  /* "Too many stack frame variables have been emitted from this compiled " */

static Object string_constant_28;  /* "item.  This item must be simplified to have fewer than 256 stack frame " */

static Object string_constant_29;  /* "variables, for example by making smaller expressions or by reducing the " */

static Object string_constant_30;  /* "size of a function, to be able to compile." */

static Object Qstack_frame_var;    /* stack-frame-var */

/* GENERATE-NEW-STACK-FRAME-VAR-SPOT */
Object generate_new_stack_frame_var_spot(type)
    Object type;
{
    Object sub_class_bit_vector, temp_1;
    Object next_stack_frame_var_location_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(139,65);
    if ( !TRUEP(Stack_frame_vars_ok_in_procedure_qm) && 
	    Current_computation_frame) {
	sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
    if (temp)
	return generate_new_variable_spot(1,type);
    else {
	if (IFIX(Next_stack_frame_var_location) > (SI_Long)255L)
	    compiler_error(5,string_constant_26,string_constant_27,
		    string_constant_28,string_constant_29,string_constant_30);
	temp_1 = phrase_list_3(Qstack_frame_var,
		Next_stack_frame_var_location,type);
	next_stack_frame_var_location_new_value = 
		FIXNUM_ADD1(Next_stack_frame_var_location);
	Next_stack_frame_var_location = 
		next_stack_frame_var_location_new_value;
	return VALUES_1(temp_1);
    }
}

static Object string_constant_31;  /* "stack argument registration" */

static Object string_constant_32;  /* "The argument number ~a was less than zero, the minimum." */

static Object string_constant_33;  /* "The maximum number of arguments for a function is 256, attempting ~
				    *             to allocate ~a."
				    */

static Object Qstack_arg;          /* stack-arg */

/* GENERATE-NEW-STACK-ARG-VAR-SPOT */
Object generate_new_stack_arg_var_spot(argument_number,type_specification)
    Object argument_number, type_specification;
{
    x_note_fn_call(139,66);
    if (IFIX(argument_number) < (SI_Long)0L) {
	compiler_bug(3,string_constant_31,string_constant_32,argument_number);
	argument_number = FIX((SI_Long)0L);
    }
    else if (IFIX(argument_number) >= (SI_Long)256L) {
	compiler_error(2,string_constant_33,argument_number);
	argument_number = FIX((SI_Long)255L);
    }
    return phrase_list_3(Qstack_arg,argument_number,type_specification);
}

static Object Qvar_spot;           /* var-spot */

static Object list_constant_3;     /* # */

/* VALID-VAR-SPOT-P */
Object valid_var_spot_p(thing)
    Object thing;
{
    Object type_of_var_spot, second_cons_qm, car_of_second, temp_1;
    char temp;

    x_note_fn_call(139,67);
    if (CONSP(thing)) {
	type_of_var_spot = M_CAR(thing);
	second_cons_qm = M_CDR(thing);
	if (CONSP(second_cons_qm)) {
	    car_of_second = M_CAR(second_cons_qm);
	    temp = FIXNUMP(car_of_second) && IFIX(car_of_second) >= 
		    (SI_Long)0L ? EQ(type_of_var_spot,Qvar_spot) && 
		    FIXNUM_LE(car_of_second,Maximum_var_spot_index) || 
		    memq_function(type_of_var_spot,list_constant_3) && 
		    IFIX(car_of_second) <= (SI_Long)255L : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 =  !TRUEP(M_CDR(second_cons_qm)) ? T : Nil;
	    if (temp_1)
		return VALUES_1(temp_1);
	    else {
		temp_1 = M_CDR(second_cons_qm);
		if (CONSP(temp_1) && 
			valid_type_specification_p(SECOND(second_cons_qm)))
		    return VALUES_1( !TRUEP(M_CDR(M_CDR(second_cons_qm))) ?
			     T : Nil);
		else
		    return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* VALID-VAR-SPOT-INDEX-P */
Object valid_var_spot_index_p(thing)
    Object thing;
{
    x_note_fn_call(139,68);
    if (FIXNUMP(thing)) {
	if ((SI_Long)0L <= IFIX(thing))
	    return VALUES_1(FIXNUM_LE(thing,Maximum_var_spot_index) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_34;  /* "type fetcher" */

static Object string_constant_35;  /* "Invalid var-spot ~a given to var-spot-type." */

/* VAR-SPOT-TYPE */
Object var_spot_type(var_spot,code_body_entry_stack)
    Object var_spot, code_body_entry_stack;
{
    Object temp, code_body_entry, ab_loop_list_, environment_description_qm;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(139,69);
    temp = CAR(var_spot);
    if (EQ(temp,Qstack_frame_var) || EQ(temp,Qstack_arg))
	return VALUES_1(THIRD(var_spot));
    else if (EQ(temp,Qvar_spot)) {
	code_body_entry = Nil;
	ab_loop_list_ = code_body_entry_stack;
	ab_loop_repeat_ = IFIX(SECOND(var_spot)) >>  -  - (SI_Long)10L;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	code_body_entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	goto next_loop;
      end_loop:
	environment_description_qm = code_body_entry ? 
		ISVREF(code_body_entry,(SI_Long)3L) : Nil;
	temp = nth(FIX(IFIX(SECOND(var_spot)) & (SI_Long)1023L),
		environment_description_qm);
	return getfq_function_no_default(CDR(temp),Ktype);
	return VALUES_1(Qnil);
    }
    else
	return compiler_bug(3,string_constant_34,string_constant_35,var_spot);
}

Object The_type_description_of_inlining_data_holder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_inlining_data_holders, Qchain_of_available_inlining_data_holders);

DEFINE_VARIABLE_WITH_SYMBOL(Inlining_data_holder_count, Qinlining_data_holder_count);

Object Chain_of_available_inlining_data_holders_vector = UNBOUND;

/* INLINING-DATA-HOLDER-STRUCTURE-MEMORY-USAGE */
Object inlining_data_holder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,70);
    temp = Inlining_data_holder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INLINING-DATA-HOLDER-COUNT */
Object outstanding_inlining_data_holder_count()
{
    Object def_structure_inlining_data_holder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,71);
    gensymed_symbol = IFIX(Inlining_data_holder_count);
    def_structure_inlining_data_holder_variable = 
	    Chain_of_available_inlining_data_holders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_inlining_data_holder_variable))
	goto end_loop;
    def_structure_inlining_data_holder_variable = 
	    ISVREF(def_structure_inlining_data_holder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-INLINING-DATA-HOLDER-1 */
Object reclaim_inlining_data_holder_1(inlining_data_holder)
    Object inlining_data_holder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(139,72);
    inline_note_reclaim_cons(inlining_data_holder,Nil);
    temp = ISVREF(Chain_of_available_inlining_data_holders_vector,
	    IFIX(Current_thread_index));
    SVREF(inlining_data_holder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_inlining_data_holders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = inlining_data_holder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INLINING-DATA-HOLDER */
Object reclaim_structure_for_inlining_data_holder(inlining_data_holder)
    Object inlining_data_holder;
{
    x_note_fn_call(139,73);
    return reclaim_inlining_data_holder_1(inlining_data_holder);
}

static Object Qg2_defstruct_structure_name_inlining_data_holder_g2_struct;  /* g2-defstruct-structure-name::inlining-data-holder-g2-struct */

/* MAKE-PERMANENT-INLINING-DATA-HOLDER-STRUCTURE-INTERNAL */
Object make_permanent_inlining_data_holder_structure_internal()
{
    Object def_structure_inlining_data_holder_variable;
    Object defstruct_g2_inlining_data_holder_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,74);
    def_structure_inlining_data_holder_variable = Nil;
    atomic_incff_symval(Qinlining_data_holder_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_inlining_data_holder_variable = Nil;
	gensymed_symbol = (SI_Long)12L;
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
	defstruct_g2_inlining_data_holder_variable = the_array;
	SVREF(defstruct_g2_inlining_data_holder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_inlining_data_holder_g2_struct;
	def_structure_inlining_data_holder_variable = 
		defstruct_g2_inlining_data_holder_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_inlining_data_holder_variable);
}

/* MAKE-INLINING-DATA-HOLDER-1 */
Object make_inlining_data_holder_1()
{
    Object def_structure_inlining_data_holder_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(139,75);
    def_structure_inlining_data_holder_variable = 
	    ISVREF(Chain_of_available_inlining_data_holders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_inlining_data_holder_variable) {
	svref_arg_1 = Chain_of_available_inlining_data_holders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_inlining_data_holder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_inlining_data_holder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_inlining_data_holder_g2_struct;
    }
    else
	def_structure_inlining_data_holder_variable = 
		make_permanent_inlining_data_holder_structure_internal();
    inline_note_allocate_cons(def_structure_inlining_data_holder_variable,Nil);
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)9L)) = T;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_inlining_data_holder_variable,FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_inlining_data_holder_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inlining_data, Qinlining_data);

/* CLEAR-INLINING-DATA */
Object clear_inlining_data()
{
    Object svref_arg_1;

    x_note_fn_call(139,76);
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Nil;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Nil;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = Nil;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = Nil;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = Nil;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = Nil;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = T;
    svref_arg_1 = Inlining_data;
    SVREF(svref_arg_1,FIX((SI_Long)10L)) = Nil;
    svref_arg_1 = Inlining_data;
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)11L)) = Nil);
}

/* ADJUST-NESTING-OF-INLINING-DATA-RECEIVED-VALUE-COMPILATIONS */
Object adjust_nesting_of_inlining_data_received_value_compilations(amount)
    Object amount;
{
    Object var_spot, ab_loop_list_, current_var_spot_index;
    SI_Long second_new_value;

    x_note_fn_call(139,77);
    var_spot = Nil;
    ab_loop_list_ = inlining_data_recieved_value_compilations_qm();
    current_var_spot_index = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var_spot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    current_var_spot_index = SECOND(var_spot);
    second_new_value = ((IFIX(current_var_spot_index) >>  -  - 
	    (SI_Long)10L) + IFIX(amount) << (SI_Long)10L) + 
	    (IFIX(current_var_spot_index) & (SI_Long)1023L);
    M_SECOND(var_spot) = FIX(second_new_value);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* OPTIMIZABLE-IN-CONTEXT? */
Object optimizable_in_context_qm()
{
    x_note_fn_call(139,78);
    if (ISVREF(Inlining_data,(SI_Long)9L))
	return block_is_optimizable_p(Current_computation_frame);
    else
	return VALUES_1(Nil);
}

/* GET-INLINE-CALL-NUMBER */
Object get_inline_call_number(context_item)
    Object context_item;
{
    Object context_assoc_qm;

    x_note_fn_call(139,79);
    context_assoc_qm = assq_function(context_item,ISVREF(Inlining_data,
	    (SI_Long)8L));
    if (context_assoc_qm)
	return VALUES_1(M_CDR(context_assoc_qm));
    else
	return VALUES_1(Nil);
}

/* VARIABLE-SPOT-AND-DESCRIPTION-FOR-LOCAL-NAME */
Object variable_spot_and_description_for_local_name(possible_local_name)
    Object possible_local_name;
{
    Object code_body_entry, ab_loop_list_, environment;
    Object ignore_inlining_environment_qm, ab_loop_iter_flag_, temp;
    Object description, ab_loop_list__1;
    SI_Long nesting_index, local_index;

    x_note_fn_call(139,80);
    code_body_entry = Nil;
    ab_loop_list_ = Lexically_visible_code_bodies;
    nesting_index = (SI_Long)0L;
    environment = Nil;
    ignore_inlining_environment_qm = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    code_body_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	nesting_index = nesting_index + (SI_Long)1L;
    environment = ISVREF(code_body_entry,(SI_Long)3L);
    temp =  !TRUEP(ISVREF(Inlining_data,(SI_Long)1L)) ? T : Nil;
    if (temp);
    else {
	temp = ISVREF(Inlining_data,(SI_Long)11L);
	temp =  !EQ(code_body_entry,CAR(temp)) ? T : Nil;
    }
    ignore_inlining_environment_qm = temp;
    local_index = (SI_Long)0L;
    description = Nil;
    ab_loop_list__1 = environment;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    description = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(possible_local_name,CAR(description)) && 
	    (ignore_inlining_environment_qm || 
	    environment_index_ok_in_this_context_qm(FIX(local_index)))) {
	temp = phrase_list_2(Qvar_spot,FIX((nesting_index << (SI_Long)10L) 
		+ local_index));
	return VALUES_2(temp,description);
    }
    local_index = local_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_36;  /* "variable spot generator" */

static Object string_constant_37;  /* "Invalid type ~a given to generate-new-variable-spot." */

/* GENERATE-NEW-VARIABLE-SPOT */
Object generate_new_variable_spot varargs_1(int, n)
{
    Object type_qm;
    Object name_qm, code_body_entry;
    Declare_varargs_nonrelocating;

    x_note_fn_call(139,81);
    INIT_ARGS_nonrelocating();
    type_qm = REQUIRED_ARG_nonrelocating();
    name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    code_body_entry = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : CAR(Lexically_visible_code_bodies);
    END_ARGS_nonrelocating();
    if (type_qm &&  !TRUEP(valid_type_specification_p(type_qm)))
	compiler_bug(3,string_constant_36,string_constant_37,type_qm);
    if (class_type_specification_p(type_qm)) {
	record_free_reference(Qab_class,
		type_specification_class_function(type_qm));
	return phrase_list_3(Qvar_spot,
		generate_new_index_in_code_body(type_qm,name_qm,
		code_body_entry,Lexically_visible_code_bodies),type_qm);
    }
    else if (type_qm)
	return phrase_list_3(Qvar_spot,
		generate_new_index_in_code_body(type_qm,name_qm,
		code_body_entry,Lexically_visible_code_bodies),type_qm);
    else
	return phrase_list_2(Qvar_spot,
		generate_new_index_in_code_body(type_qm,name_qm,
		code_body_entry,Lexically_visible_code_bodies));
}

static Object string_constant_38;  /* "variable index generator" */

static Object string_constant_39;  /* "Attempted to generate a new variable in a null code body environment." */

static Object string_constant_40;  /* "The maximum number of local variables, ~a, has been ~
				    *              exceeded.  You must reduce the number of local variables, the ~
				    *              complexity of the expressions, or the overall number of ~
				    *              expressions and statements in this item."
				    */

static Object string_constant_41;  /* "The maximum number of nestings with a procedure, ~a, has been ~
				    *              exceeded.  You must reduce the depth of do in parallel and on ~
				    *              error nesting within this procedure."
				    */

/* GENERATE-NEW-INDEX-IN-CODE-BODY */
Object generate_new_index_in_code_body(type_qm,name_qm,code_body_entry,
	    code_body_stack)
    Object type_qm, name_qm, code_body_entry, code_body_stack;
{
    Object code_body_in_stack, ab_loop_list_, ab_loop_iter_flag_;
    Object new_description, old_environment, local_index, svref_new_value;
    SI_Long nesting_index;

    x_note_fn_call(139,82);
    if ( !TRUEP(code_body_stack))
	compiler_bug(2,string_constant_38,string_constant_39);
    code_body_in_stack = Nil;
    ab_loop_list_ = code_body_stack;
    nesting_index = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    code_body_in_stack = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	nesting_index = nesting_index + (SI_Long)1L;
    if (EQ(code_body_entry,code_body_in_stack)) {
	new_description = type_qm ? phrase_list_3(name_qm,Ktype,type_qm) : 
		phrase_cons(name_qm,Nil);
	old_environment = ISVREF(code_body_entry,(SI_Long)3L);
	local_index = length(old_environment);
	svref_new_value = nconc2(old_environment,
		phrase_cons(new_description,Nil));
	SVREF(code_body_entry,FIX((SI_Long)3L)) = svref_new_value;
	if (FIXNUM_GT(local_index,Maximum_var_spot_local_index))
	    compiler_error(2,string_constant_40,Maximum_var_spot_local_index);
	if (nesting_index > IFIX(Maximum_var_spot_nesting))
	    compiler_error(2,string_constant_41,Maximum_var_spot_nesting);
	return VALUES_1(FIX((nesting_index << (SI_Long)10L) + 
		IFIX(local_index)));
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* AVAILABLE-VAR-SPOT-COUNT */
Object available_var_spot_count()
{
    Object temp;

    x_note_fn_call(139,83);
    temp = FIXNUM_MINUS(Maximum_var_spot_local_index,
	    length(ISVREF(CAR(Lexically_visible_code_bodies),(SI_Long)3L)));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Missing_local_names_already_reported, Qmissing_local_names_already_reported);

DEFINE_VARIABLE_WITH_SYMBOL(Duplicate_local_names_already_reported, Qduplicate_local_names_already_reported);

static Object string_constant_42;  /* "the local name ~a is undefined" */

/* PROCEDURE-COMPILER-MISSING-LOCAL-NAME-ERROR */
Object procedure_compiler_missing_local_name_error(local_name)
    Object local_name;
{
    x_note_fn_call(139,84);
    if ( !TRUEP(memq_function(local_name,
	    Missing_local_names_already_reported))) {
	compiler_error(2,string_constant_42,local_name);
	Missing_local_names_already_reported = phrase_cons(local_name,
		Missing_local_names_already_reported);
	return VALUES_1(Missing_local_names_already_reported);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_43;  /* "the local name ~a is defined more than once" */

/* PROCEDURE-COMPILER-DUPLICATE-LOCAL-NAME-ERROR */
Object procedure_compiler_duplicate_local_name_error(local_name)
    Object local_name;
{
    x_note_fn_call(139,85);
    if ( !TRUEP(memq_function(local_name,
	    Duplicate_local_names_already_reported))) {
	compiler_error(2,string_constant_43,local_name);
	Duplicate_local_names_already_reported = phrase_cons(local_name,
		Duplicate_local_names_already_reported);
	return VALUES_1(Duplicate_local_names_already_reported);
    }
    else
	return VALUES_1(Nil);
}

Object Maximum_stack_instruction_vector_length = UNBOUND;

Object The_type_description_of_byte_code_stream = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_byte_code_streams, Qchain_of_available_byte_code_streams);

DEFINE_VARIABLE_WITH_SYMBOL(Byte_code_stream_count, Qbyte_code_stream_count);

Object Chain_of_available_byte_code_streams_vector = UNBOUND;

/* BYTE-CODE-STREAM-STRUCTURE-MEMORY-USAGE */
Object byte_code_stream_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,86);
    temp = Byte_code_stream_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BYTE-CODE-STREAM-COUNT */
Object outstanding_byte_code_stream_count()
{
    Object def_structure_byte_code_stream_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,87);
    gensymed_symbol = IFIX(Byte_code_stream_count);
    def_structure_byte_code_stream_variable = 
	    Chain_of_available_byte_code_streams;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_byte_code_stream_variable))
	goto end_loop;
    def_structure_byte_code_stream_variable = 
	    ISVREF(def_structure_byte_code_stream_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BYTE-CODE-STREAM-1 */
Object reclaim_byte_code_stream_1(byte_code_stream)
    Object byte_code_stream;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(139,88);
    inline_note_reclaim_cons(byte_code_stream,Nil);
    structure_being_reclaimed = byte_code_stream;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_compiler_tree_1(ISVREF(byte_code_stream,(SI_Long)2L));
      SVREF(byte_code_stream,FIX((SI_Long)2L)) = Nil;
      reclaim_compiler_tree_1(ISVREF(byte_code_stream,(SI_Long)3L));
      SVREF(byte_code_stream,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_byte_code_streams_vector,
	    IFIX(Current_thread_index));
    SVREF(byte_code_stream,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_byte_code_streams_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = byte_code_stream;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BYTE-CODE-STREAM */
Object reclaim_structure_for_byte_code_stream(byte_code_stream)
    Object byte_code_stream;
{
    x_note_fn_call(139,89);
    return reclaim_byte_code_stream_1(byte_code_stream);
}

static Object Qg2_defstruct_structure_name_byte_code_stream_g2_struct;  /* g2-defstruct-structure-name::byte-code-stream-g2-struct */

/* MAKE-PERMANENT-BYTE-CODE-STREAM-STRUCTURE-INTERNAL */
Object make_permanent_byte_code_stream_structure_internal()
{
    Object def_structure_byte_code_stream_variable;
    Object defstruct_g2_byte_code_stream_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,90);
    def_structure_byte_code_stream_variable = Nil;
    atomic_incff_symval(Qbyte_code_stream_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_byte_code_stream_variable = Nil;
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
	defstruct_g2_byte_code_stream_variable = the_array;
	SVREF(defstruct_g2_byte_code_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_byte_code_stream_g2_struct;
	def_structure_byte_code_stream_variable = 
		defstruct_g2_byte_code_stream_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_byte_code_stream_variable);
}

/* MAKE-BYTE-CODE-STREAM-1 */
Object make_byte_code_stream_1()
{
    Object def_structure_byte_code_stream_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,91);
    def_structure_byte_code_stream_variable = 
	    ISVREF(Chain_of_available_byte_code_streams_vector,
	    IFIX(Current_thread_index));
    if (def_structure_byte_code_stream_variable) {
	svref_arg_1 = Chain_of_available_byte_code_streams_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_byte_code_stream_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_byte_code_stream_g2_struct;
    }
    else
	def_structure_byte_code_stream_variable = 
		make_permanent_byte_code_stream_structure_internal();
    inline_note_allocate_cons(def_structure_byte_code_stream_variable,Nil);
    ISVREF(def_structure_byte_code_stream_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_byte_code_stream_variable,FIX((SI_Long)8L)) = Nil;
    return VALUES_1(def_structure_byte_code_stream_variable);
}

/* MAKE-INFERIOR-BYTE-CODE-STREAM */
Object make_inferior_byte_code_stream(superior_byte_code_stream)
    Object superior_byte_code_stream;
{
    Object new_stream;

    x_note_fn_call(139,92);
    new_stream = make_byte_code_stream_1();
    SVREF(new_stream,FIX((SI_Long)5L)) = superior_byte_code_stream;
    return VALUES_1(new_stream);
}

/* MAKE-BYTE-CODE-STREAM-GIVEN-BASE-STREAM */
Object make_byte_code_stream_given_base_stream(base_byte_code_stream)
    Object base_byte_code_stream;
{
    Object new_stream;

    x_note_fn_call(139,93);
    new_stream = make_byte_code_stream_1();
    SVREF(new_stream,FIX((SI_Long)6L)) = base_byte_code_stream;
    return VALUES_1(new_stream);
}

/* MERGE-BYTE-CODE-STREAMS */
Object merge_byte_code_streams(superior,inferior)
    Object superior, inferior;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(139,94);
    incff_1_arg = ISVREF(inferior,(SI_Long)1L);
    svref_new_value = FIXNUM_ADD(ISVREF(superior,(SI_Long)1L),incff_1_arg);
    SVREF(superior,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = nconc2(ISVREF(inferior,(SI_Long)2L),ISVREF(superior,
	    (SI_Long)2L));
    SVREF(superior,FIX((SI_Long)2L)) = svref_new_value;
    SVREF(inferior,FIX((SI_Long)2L)) = Nil;
    reclaim_byte_code_stream_1(inferior);
    return VALUES_1(Nil);
}

static Object string_constant_44;  /* "byte code emitter" */

static Object string_constant_45;  /* "Non-byte ~a emitted into byte-codes." */

static Object string_constant_46;  /* "The byte codes in the instruction vector have exceeded the ~
				    *               maximum, ~a.  There are too many statements and expressions in ~
				    *               this source code."
				    */

/* WRITE-BYTE-CODE-TO-STREAM */
Object write_byte_code_to_stream(byte_code_stream,byte_1)
    Object byte_code_stream, byte_1;
{
    Object current_address, svref_new_value;

    x_note_fn_call(139,95);
    if ( !(FIXNUMP(byte_1) && IFIX(byte_1) >= (SI_Long)0L && IFIX(byte_1) 
	    < (SI_Long)256L)) {
	compiler_bug(3,string_constant_44,string_constant_45,byte_1);
	byte_1 = FIX((SI_Long)0L);
    }
    current_address = ISVREF(byte_code_stream,(SI_Long)1L);
    if (Compiler_errors);
    else if (FIXNUM_GE(current_address,Maximum_byte_vector_length))
	compiler_error(2,string_constant_46,Maximum_byte_vector_length);
    else {
	svref_new_value = compiler_cons_1(byte_1,ISVREF(byte_code_stream,
		(SI_Long)2L));
	SVREF(byte_code_stream,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = FIXNUM_ADD1(current_address);
	SVREF(byte_code_stream,FIX((SI_Long)1L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qjump_tag;           /* jump-tag */

static Object Qtag;                /* tag */

/* REGISTER-TAG-IN-BYTE-CODE-STREAM */
Object register_tag_in_byte_code_stream varargs_1(int, n)
{
    Object byte_code_stream, tag;
    Object jump_tag_qm, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(139,96);
    INIT_ARGS_nonrelocating();
    byte_code_stream = REQUIRED_ARG_nonrelocating();
    tag = REQUIRED_ARG_nonrelocating();
    jump_tag_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Compiler_errors)) {
	svref_new_value = compiler_cons_1(compiler_cons_1(jump_tag_qm ? 
		Qjump_tag : Qtag,tag),ISVREF(byte_code_stream,(SI_Long)2L));
	SVREF(byte_code_stream,FIX((SI_Long)2L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qaddress_resolution_point;  /* address-resolution-point */

/* REGISTER-BYTE-CODE-TAG-RESOLUTION-POINT */
Object register_byte_code_tag_resolution_point(byte_code_stream,tags)
    Object byte_code_stream, tags;
{
    Object svref_new_value;

    x_note_fn_call(139,97);
    svref_new_value = 
	    compiler_cons_1(compiler_cons_1(Qaddress_resolution_point,
	    tags),ISVREF(byte_code_stream,(SI_Long)2L));
    SVREF(byte_code_stream,FIX((SI_Long)2L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* REGISTER-BYTE-CODE-TAG-RESOLUTION-ADDRESS */
Object register_byte_code_tag_resolution_address(byte_code_stream,tags,address)
    Object byte_code_stream, tags, address;
{
    Object svref_new_value;

    x_note_fn_call(139,98);
    svref_new_value = compiler_cons_1(compiler_cons_1(address,
	    copy_tree_using_compiler_conses_1(tags)),
	    ISVREF(byte_code_stream,(SI_Long)3L));
    SVREF(byte_code_stream,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object string_constant_47;  /* "byte code stream vector reader" */

static Object string_constant_48;  /* "Unrecognized entry ~a in byte-code-stream-bytes." */

/* READ-BYTE-CODE-STREAM-VECTOR */
Object read_byte_code_stream_vector(byte_code_stream)
    Object byte_code_stream;
{
    Object vector_1, byte_or_tag, ab_loop_list_, temp;
    SI_Long bytes, length_1, index_1, index_to_zero, ab_loop_bind_;

    x_note_fn_call(139,99);
    bytes = IFIX(ISVREF(byte_code_stream,(SI_Long)1L));
    vector_1 = allocate_byte_vector(FIX(bytes));
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
    index_1 = bytes;
    byte_or_tag = Nil;
    ab_loop_list_ = ISVREF(byte_code_stream,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    byte_or_tag = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(byte_or_tag)) {
	temp = M_CAR(byte_or_tag);
	if (EQ(temp,Qtag) || EQ(temp,Qjump_tag))
	    register_goto_tag_address(M_CDR(byte_or_tag),FIX(index_1),
		    EQ(M_CAR(byte_or_tag),Qjump_tag) ? T : Nil);
	else if (EQ(temp,Qaddress_resolution_point))
	    register_byte_code_tag_resolution_address(byte_code_stream,
		    M_CDR(byte_or_tag),FIX(index_1));
	else
	    compiler_bug(3,string_constant_47,string_constant_48,byte_or_tag);
    }
    else if (FIXNUMP(byte_or_tag)) {
	index_1 = index_1 - (SI_Long)1L;
	UBYTE_8_ISASET_1(vector_1,index_1,IFIX(byte_or_tag));
    }
    else
	compiler_bug(3,string_constant_47,string_constant_48,byte_or_tag);
    goto next_loop;
  end_loop:
    index_to_zero = bytes;
    ab_loop_bind_ = length_1;
  next_loop_1:
    if (index_to_zero >= ab_loop_bind_)
	goto end_loop_1;
    UBYTE_8_ISASET_1(vector_1,index_to_zero,(SI_Long)0L);
    index_to_zero = index_to_zero + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(vector_1);
    return VALUES_1(Qnil);
}

Object Maximum_constant_vector_length = UNBOUND;

static Object string_constant_49;  /* "The maximum allowed number of constants, ~a, has been exceeded ~
				    *              while registering ~NE.    You must reduce the size or complexity ~
				    *              of the expressions and statements in this item."
				    */

/* REGISTER-CONSTANT-IN-BYTE-CODE-STREAM */
Object register_constant_in_byte_code_stream(byte_code_stream,evaluation_value)
    Object byte_code_stream, evaluation_value;
{
    Object temp, old_constants, result_index, constant, ab_loop_list_;
    Object constant_fold_qm, svref_new_value;
    SI_Long index_1;
    Declare_special(1);

    x_note_fn_call(139,100);
    if (ISVREF(byte_code_stream,(SI_Long)5L))
	temp = 
		register_constant_in_byte_code_stream(ISVREF(byte_code_stream,
		(SI_Long)5L),evaluation_value);
    else if (ISVREF(byte_code_stream,(SI_Long)6L))
	temp = 
		register_constant_in_byte_code_stream(ISVREF(byte_code_stream,
		(SI_Long)6L),evaluation_value);
    else {
	old_constants = ISVREF(byte_code_stream,(SI_Long)4L);
	result_index = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Result_index,Qresult_index,result_index,0);
	  index_1 = (SI_Long)0L;
	  constant = Nil;
	  ab_loop_list_ = old_constants;
	  constant_fold_qm = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  constant = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  constant_fold_qm = evaluation_value_p_function(constant) ? 
		  evaluation_values_can_be_constant_folded_p(constant,
		  evaluation_value) : Qnil;
	  if (constant_fold_qm) {
	      Result_index = FIX(index_1);
	      goto end_1;
	  }
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  svref_new_value = nconc2(old_constants,
		  slot_value_cons_1(copy_for_slot_value(evaluation_value),
		  Nil));
	  SVREF(byte_code_stream,FIX((SI_Long)4L)) = svref_new_value;
	  Result_index = FIX(index_1);
	end_1:;
	  if (FIXNUM_GE(Result_index,Maximum_constant_vector_length))
	      compiler_error(3,string_constant_49,
		      Maximum_constant_vector_length,evaluation_value);
	  reclaim_evaluation_value(evaluation_value);
	  temp = Result_index;
	POP_SPECIAL();
    }
    return VALUES_1(temp);
}

static Object string_constant_50;  /* "The maximum allowed number of constants, ~a, has been ~
				    *                      exceeded while registering an internal constant.  You must ~
				    *                      reduce the size or complexity of the expressions and ~
				    *                      statements in this item."
				    */

/* REGISTER-INTERNAL-CONSTANT-IN-BYTE-CODE-STREAM */
Object register_internal_constant_in_byte_code_stream(byte_code_stream,
	    internal_constant)
    Object byte_code_stream, internal_constant;
{
    Object old_constants, constant, ab_loop_list_, constant_fold_qm;
    Object svref_new_value;
    SI_Long index_1;

    x_note_fn_call(139,101);
    if (ISVREF(byte_code_stream,(SI_Long)5L))
	return register_internal_constant_in_byte_code_stream(ISVREF(byte_code_stream,
		(SI_Long)5L),internal_constant);
    else if (ISVREF(byte_code_stream,(SI_Long)6L))
	return register_internal_constant_in_byte_code_stream(ISVREF(byte_code_stream,
		(SI_Long)6L),internal_constant);
    else {
	old_constants = ISVREF(byte_code_stream,(SI_Long)4L);
	index_1 = (SI_Long)0L;
	constant = Nil;
	ab_loop_list_ = old_constants;
	constant_fold_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	constant = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	constant_fold_qm = constant_fold_internal_constants_p(constant,
		internal_constant);
	if (constant_fold_qm)
	    return VALUES_1(FIX(index_1));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	svref_new_value = nconc2(old_constants,
		slot_value_cons_1(copy_for_slot_value(internal_constant),Nil));
	SVREF(byte_code_stream,FIX((SI_Long)4L)) = svref_new_value;
	if (index_1 >= IFIX(Maximum_constant_vector_length))
	    compiler_error(2,string_constant_50,
		    Maximum_constant_vector_length);
	return VALUES_1(FIX(index_1));
	return VALUES_1(Qnil);
    }
}

/* CONSTANT-FOLD-INTERNAL-CONSTANTS-P */
Object constant_fold_internal_constants_p(constant_1,constant_2)
    Object constant_1, constant_2;
{
    x_note_fn_call(139,102);
    if (CONSP(constant_1)) {
	if (CONSP(constant_2) && 
		constant_fold_internal_constants_p(M_CAR(constant_1),
		M_CAR(constant_2)))
	    return constant_fold_internal_constants_p(M_CDR(constant_1),
		    M_CDR(constant_2));
	else
	    return VALUES_1(Nil);
    }
    else if (SYMBOLP(constant_1))
	return VALUES_1(EQ(constant_1,constant_2) ? T : Nil);
    else if (FIXNUMP(constant_1)) {
	if (FIXNUMP(constant_2))
	    return VALUES_1(FIXNUM_EQ(constant_1,constant_2) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* MAKE-PROCEDURE-BYTE-CODE-CONSTANTS */
Object make_procedure_byte_code_constants(byte_code_stream)
    Object byte_code_stream;
{
    Object annotation_info_qm, constants, count_1, constant_vector, constant;
    Object ab_loop_list_, ab_loop_iter_flag_;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(139,103);
    annotation_info_qm = ISVREF(byte_code_stream,(SI_Long)8L);
    if (annotation_info_qm)
	register_internal_constant_in_byte_code_stream(byte_code_stream,
		phrase_cons(Special_annotation_lookup_structure_marker,
		compress_annotation_info_for_saving(nreverse(annotation_info_qm))));
    constants = ISVREF(byte_code_stream,(SI_Long)4L);
    count_1 = length(constants);
    if (constants) {
	constant_vector = allocate_managed_simple_vector(count_1);
	constant = Nil;
	ab_loop_list_ = constants;
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(count_1));
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	constant = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 + (SI_Long)1L;
	if (index_1 > ab_loop_bind_)
	    goto end_loop;
	ISVREF(constant_vector,index_1) = constant;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	reclaim_slot_value_list_1(constants);
	SVREF(byte_code_stream,FIX((SI_Long)4L)) = Nil;
	return VALUES_1(constant_vector);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COALESCE-LOOKUP-STRUCTURES */
Object coalesce_lookup_structures varargs_1(int, n)
{
    Object lookup_structure_entry_qm, byte_code_stream;
    Object recursive_p, base_stream_qm, temp, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(139,104);
    INIT_ARGS_nonrelocating();
    lookup_structure_entry_qm = REQUIRED_ARG_nonrelocating();
    byte_code_stream = REQUIRED_ARG_nonrelocating();
    recursive_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (lookup_structure_entry_qm) {
	base_stream_qm = ISVREF(byte_code_stream,(SI_Long)6L);
	if (base_stream_qm) {
	    coalesce_lookup_structures(3,lookup_structure_entry_qm,
		    base_stream_qm,T);
	    return VALUES_1(SVREF(byte_code_stream,FIX((SI_Long)8L)) = Nil);
	}
	else {
	    temp = nreverse(lookup_structure_entry_qm);
	    svref_new_value = phrase_cons(temp,recursive_p ? 
		    ISVREF(byte_code_stream,(SI_Long)8L) : Qnil);
	    return VALUES_1(SVREF(byte_code_stream,FIX((SI_Long)8L)) = 
		    svref_new_value);
	}
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_stack_conses, Qavailable_stack_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_stack_conses_tail, Qavailable_stack_conses_tail);

Object Available_stack_conses_vector = UNBOUND;

Object Available_stack_conses_tail_vector = UNBOUND;

Object Stack_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Stack_cons_counter, Qstack_cons_counter);

/* OUTSTANDING-STACK-CONSES */
Object outstanding_stack_conses()
{
    Object temp;

    x_note_fn_call(139,105);
    temp = FIXNUM_MINUS(Stack_cons_counter,length(Available_stack_conses));
    return VALUES_1(temp);
}

/* STACK-CONS-MEMORY-USAGE */
Object stack_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(139,106);
    temp = FIXNUM_TIMES(Stack_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-STACK-CONS-POOL */
Object replenish_stack_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(139,107);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qstack_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Stack_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qstack;              /* stack */

/* STACK-CONS-1 */
Object stack_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(139,108);
    new_cons = ISVREF(Available_stack_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qstack);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-STACK-LIST-POOL */
Object replenish_stack_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(139,109);
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
    if (ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qstack_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-STACK-LIST-1 */
Object make_stack_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(139,110);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_stack_conses_vector,
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
	replenish_stack_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_stack_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qstack);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_stack_conses_tail_vector;
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

/* STACK-LIST-2 */
Object stack_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,111);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_stack_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstack);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_stack_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_stack_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_stack_conses_tail_vector;
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

/* STACK-LIST-3 */
Object stack_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,112);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_stack_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstack);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_stack_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_stack_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_stack_conses_tail_vector;
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

/* STACK-LIST-4 */
Object stack_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,113);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_stack_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstack);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_stack_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_stack_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_stack_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_stack_conses_tail_vector;
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

/* STACK-LIST-TRACE-HOOK */
Object stack_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(139,114);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-STACK-CONSES-1 */
Object copy_tree_using_stack_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(139,115);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_cons_pool();
	temp_1 = copy_tree_using_stack_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_cons_pool();
	temp_1 = copy_tree_using_stack_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack);
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

/* COPY-LIST-USING-STACK-CONSES-1 */
Object copy_list_using_stack_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(139,116);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack);
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

/* RECLAIM-STACK-CONS-1 */
Object reclaim_stack_cons_1(stack_cons)
    Object stack_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(139,117);
    inline_note_reclaim_cons(stack_cons,Qstack);
    if (ISVREF(Available_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_stack_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = stack_cons;
	temp = Available_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = stack_cons;
    }
    else {
	temp = Available_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = stack_cons;
	temp = Available_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = stack_cons;
    }
    M_CDR(stack_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-STACK-LIST-1 */
Object reclaim_stack_list_1(stack_list)
    Object stack_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(139,118);
    if (stack_list) {
	last_1 = stack_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qstack);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qstack);
	if (ISVREF(Available_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = stack_list;
	    temp = Available_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = stack_list;
	    temp = Available_stack_conses_tail_vector;
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

/* RECLAIM-STACK-LIST*-1 */
Object reclaim_stack_list_star_1(stack_list)
    Object stack_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(139,119);
    if (CONSP(stack_list)) {
	temp = last(stack_list,_);
	M_CDR(temp) = Nil;
	if (stack_list) {
	    last_1 = stack_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qstack);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qstack);
	    if (ISVREF(Available_stack_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_stack_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = stack_list;
		temp = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = stack_list;
		temp = Available_stack_conses_tail_vector;
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

/* RECLAIM-STACK-TREE-1 */
Object reclaim_stack_tree_1(tree)
    Object tree;
{
    Object e, e2, stack_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(139,120);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_stack_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		stack_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(stack_cons,Qstack);
		if (EQ(stack_cons,e))
		    goto end_1;
		else if ( !TRUEP(stack_cons))
		    goto end_1;
		else
		    stack_cons = CDR(stack_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_stack_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_stack_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_stack_conses_tail_vector;
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

/* DELETE-STACK-ELEMENT-1 */
Object delete_stack_element_1(element,stack_list)
    Object element, stack_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(139,121);
    if (stack_list) {
	if (EQ(element,M_CAR(stack_list))) {
	    temp = CDR(stack_list);
	    inline_note_reclaim_cons(stack_list,Qstack);
	    if (ISVREF(Available_stack_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_stack_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = stack_list;
		temp_1 = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = stack_list;
	    }
	    else {
		temp_1 = Available_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = stack_list;
		temp_1 = Available_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = stack_list;
	    }
	    M_CDR(stack_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = stack_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qstack);
		if (ISVREF(Available_stack_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_stack_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_stack_conses_tail_vector;
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
	    temp = stack_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-STACK-CONS-1 */
Object delete_stack_cons_1(stack_cons,stack_list)
    Object stack_cons, stack_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(139,122);
    if (EQ(stack_cons,stack_list))
	temp = CDR(stack_list);
    else {
	l_trailer_qm = Nil;
	l = stack_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,stack_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = stack_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_stack_cons_1(stack_cons);
    return VALUES_1(temp);
}

Object Stack_evaluators_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(In_line_evaluator_array, Qin_line_evaluator_array);

DEFINE_VARIABLE_WITH_SYMBOL(Funcalled_evaluator_array, Qfuncalled_evaluator_array);

DEFINE_VARIABLE_WITH_SYMBOL(Funcalled_evaluator_functions, Qfuncalled_evaluator_functions);

DEFINE_VARIABLE_WITH_SYMBOL(Funcalled_evaluator_dispatch_type, Qfuncalled_evaluator_dispatch_type);

Object The_type_description_of_stack_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_stack_nodes, Qchain_of_available_stack_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Stack_node_count, Qstack_node_count);

Object Chain_of_available_stack_nodes_vector = UNBOUND;

/* STACK-NODE-STRUCTURE-MEMORY-USAGE */
Object stack_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,123);
    temp = Stack_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-STACK-NODE-COUNT */
Object outstanding_stack_node_count()
{
    Object def_structure_stack_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,124);
    gensymed_symbol = IFIX(Stack_node_count);
    def_structure_stack_node_variable = Chain_of_available_stack_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_stack_node_variable))
	goto end_loop;
    def_structure_stack_node_variable = 
	    ISVREF(def_structure_stack_node_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-STACK-NODE-1 */
Object reclaim_stack_node_1(stack_node)
    Object stack_node;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(139,125);
    inline_note_reclaim_cons(stack_node,Nil);
    structure_being_reclaimed = stack_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_stack_list_1(ISVREF(stack_node,(SI_Long)2L));
      SVREF(stack_node,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_stack_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(stack_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_stack_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = stack_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-STACK-NODE */
Object reclaim_structure_for_stack_node(stack_node)
    Object stack_node;
{
    x_note_fn_call(139,126);
    return reclaim_stack_node_1(stack_node);
}

static Object Qg2_defstruct_structure_name_stack_node_g2_struct;  /* g2-defstruct-structure-name::stack-node-g2-struct */

/* MAKE-PERMANENT-STACK-NODE-STRUCTURE-INTERNAL */
Object make_permanent_stack_node_structure_internal()
{
    Object def_structure_stack_node_variable, defstruct_g2_stack_node_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,127);
    def_structure_stack_node_variable = Nil;
    atomic_incff_symval(Qstack_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_stack_node_variable = Nil;
	gensymed_symbol = (SI_Long)12L;
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
	defstruct_g2_stack_node_variable = the_array;
	SVREF(defstruct_g2_stack_node_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_stack_node_g2_struct;
	def_structure_stack_node_variable = defstruct_g2_stack_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_stack_node_variable);
}

/* MAKE-STACK-NODE-1-1 */
Object make_stack_node_1_1(stack_node_operation,
	    stack_node_evaluator_descriptions)
    Object stack_node_operation, stack_node_evaluator_descriptions;
{
    Object def_structure_stack_node_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(139,128);
    def_structure_stack_node_variable = 
	    ISVREF(Chain_of_available_stack_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_stack_node_variable) {
	svref_arg_1 = Chain_of_available_stack_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_stack_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_stack_node_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_stack_node_g2_struct;
    }
    else
	def_structure_stack_node_variable = 
		make_permanent_stack_node_structure_internal();
    inline_note_allocate_cons(def_structure_stack_node_variable,Nil);
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)1L)) = 
	    stack_node_operation;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)3L)) = 
	    stack_node_evaluator_descriptions;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)8L)) = Nil;
    ISVREF(def_structure_stack_node_variable,(SI_Long)9L) = FIX((SI_Long)0L);
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_stack_node_variable,FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_stack_node_variable);
}

Object The_type_description_of_stack_node_instruction = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_stack_node_instructions, Qchain_of_available_stack_node_instructions);

DEFINE_VARIABLE_WITH_SYMBOL(Stack_node_instruction_count, Qstack_node_instruction_count);

Object Chain_of_available_stack_node_instructions_vector = UNBOUND;

/* STACK-NODE-INSTRUCTION-STRUCTURE-MEMORY-USAGE */
Object stack_node_instruction_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,129);
    temp = Stack_node_instruction_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-STACK-NODE-INSTRUCTION-COUNT */
Object outstanding_stack_node_instruction_count()
{
    Object def_structure_stack_node_instruction_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,130);
    gensymed_symbol = IFIX(Stack_node_instruction_count);
    def_structure_stack_node_instruction_variable = 
	    Chain_of_available_stack_node_instructions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_stack_node_instruction_variable))
	goto end_loop;
    def_structure_stack_node_instruction_variable = 
	    ISVREF(def_structure_stack_node_instruction_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-STACK-NODE-INSTRUCTION-1-1 */
Object reclaim_stack_node_instruction_1_1(stack_node_instruction)
    Object stack_node_instruction;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(139,131);
    inline_note_reclaim_cons(stack_node_instruction,Nil);
    structure_being_reclaimed = stack_node_instruction;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_stack_list_1(ISVREF(stack_node_instruction,(SI_Long)2L));
      SVREF(stack_node_instruction,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_stack_node_instructions_vector,
	    IFIX(Current_thread_index));
    SVREF(stack_node_instruction,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_stack_node_instructions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = stack_node_instruction;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-STACK-NODE-INSTRUCTION */
Object reclaim_structure_for_stack_node_instruction(stack_node_instruction)
    Object stack_node_instruction;
{
    x_note_fn_call(139,132);
    return reclaim_stack_node_instruction_1_1(stack_node_instruction);
}

static Object Qg2_defstruct_structure_name_stack_node_instruction_g2_struct;  /* g2-defstruct-structure-name::stack-node-instruction-g2-struct */

/* MAKE-PERMANENT-STACK-NODE-INSTRUCTION-STRUCTURE-INTERNAL */
Object make_permanent_stack_node_instruction_structure_internal()
{
    Object def_structure_stack_node_instruction_variable;
    Object defstruct_g2_stack_node_instruction_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,133);
    def_structure_stack_node_instruction_variable = Nil;
    atomic_incff_symval(Qstack_node_instruction_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_stack_node_instruction_variable = Nil;
	gensymed_symbol_1 = (SI_Long)14L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_stack_node_instruction_variable = the_array;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_stack_node_instruction_g2_struct;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_stack_node_instruction_variable,
		FIX((SI_Long)11L)) = Nil;
	def_structure_stack_node_instruction_variable = 
		defstruct_g2_stack_node_instruction_variable;
	SVREF(def_structure_stack_node_instruction_variable,
		FIX((SI_Long)3L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_stack_node_instructions_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_stack_node_instruction_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_stack_node_instructions_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_stack_node_instruction_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_stack_node_instruction_variable);
}

/* MAKE-STACK-NODE-INSTRUCTION-1-1 */
Object make_stack_node_instruction_1_1(stack_node_operation,
	    stack_node_instruction_extra_info)
    Object stack_node_operation, stack_node_instruction_extra_info;
{
    Object def_structure_stack_node_instruction_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(139,134);
    def_structure_stack_node_instruction_variable = 
	    ISVREF(Chain_of_available_stack_node_instructions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_stack_node_instruction_variable) {
	svref_arg_1 = Chain_of_available_stack_node_instructions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_stack_node_instruction_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_stack_node_instruction_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_stack_node_instruction_g2_struct;
    }
    else
	def_structure_stack_node_instruction_variable = 
		make_permanent_stack_node_instruction_structure_internal();
    inline_note_allocate_cons(def_structure_stack_node_instruction_variable,
	    Nil);
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)1L)) 
	    = stack_node_operation;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)12L)) 
	    = stack_node_instruction_extra_info;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)2L)) 
	    = Nil;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)4L)) 
	    = Nil;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)5L)) 
	    = Nil;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)6L)) 
	    = Nil;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)7L)) 
	    = Nil;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)8L)) 
	    = Nil;
    ISVREF(def_structure_stack_node_instruction_variable,(SI_Long)9L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)10L)) 
	    = Nil;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)11L)) 
	    = Nil;
    SVREF(def_structure_stack_node_instruction_variable,FIX((SI_Long)13L)) 
	    = Nil;
    return VALUES_1(def_structure_stack_node_instruction_variable);
}

/* RECLAIM-STACK-LIST-OF-NODES */
Object reclaim_stack_list_of_nodes(stack_list_of_stack_nodes)
    Object stack_list_of_stack_nodes;
{
    Object stack_node, ab_loop_list_;

    x_note_fn_call(139,135);
    if (stack_list_of_stack_nodes) {
	stack_node = Nil;
	ab_loop_list_ = stack_list_of_stack_nodes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	stack_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(stack_node) && EQ(ISVREF(stack_node,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_stack_node_g2_struct))
	    reclaim_stack_node_1(stack_node);
	else if (SIMPLE_VECTOR_P(stack_node) && EQ(ISVREF(stack_node,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_stack_node_instruction_g2_struct))
	    reclaim_stack_node_instruction(stack_node);
	else
	    error((SI_Long)1L,"Can\'t reclaim.");
	goto next_loop;
      end_loop:;
	reclaim_stack_list_1(stack_list_of_stack_nodes);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Stack_nodes_to_reclaim, Qstack_nodes_to_reclaim);

static Object Qname_reference;     /* name-reference */

static Object Qpush_cached_item;   /* push-cached-item */

static Object Qensure_type;        /* ensure-type */

static Object list_constant_4;     /* # */

/* INDIRECTLY-DENOTED-ITEM-P */
Object indirectly_denoted_item_p(stack_node_tree)
    Object stack_node_tree;
{
    Object operation;

    x_note_fn_call(139,136);
    if (SIMPLE_VECTOR_P(stack_node_tree) && EQ(ISVREF(stack_node_tree,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct)) {
	operation = ISVREF(stack_node_tree,(SI_Long)1L);
	if (EQ(operation,Qname_reference))
	    return VALUES_1(Nil);
	else if (EQ(operation,Qpush_cached_item))
	    return VALUES_1(Nil);
	else if (EQ(operation,Qensure_type)) {
	    if (type_specifications_could_intersect_p(ISVREF(stack_node_tree,
		    (SI_Long)5L),list_constant_4))
		return indirectly_denoted_item_p(M_CAR(ISVREF(stack_node_tree,
			(SI_Long)2L)));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* DEPENDENT-COMPILATION-P */
Object dependent_compilation_p varargs_1(int, n)
{
    Object frame, x2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(139,137);
    INIT_ARGS_nonrelocating();
    frame = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Current_computation_frame;
    END_ARGS_nonrelocating();
    if (Collecting_free_references) {
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return block_can_be_dependent_p(frame);
    else
	return VALUES_1(Nil);
}

static Object Qclass_definition;   /* class-definition */

/* STABLE-CLASS-P */
Object stable_class_p varargs_1(int, n)
{
    Object class_1;
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, definition_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(139,138);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop)) {
	temp = lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop);
	temp = CONSP(temp) ? T : Nil;
    }
    else
	temp = Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	if (SYMBOLP(class_1)) {
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
	    temp_2 = TRUEP(resulting_value);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    definition_qm = 
		    get_instance_with_name_if_any(Qclass_definition,class_1);
	    if (definition_qm &&  !TRUEP(block_is_unstable_p(definition_qm)))
		return VALUES_1((SI_Long)0L != (IFIX(ISVREF(definition_qm,
			(SI_Long)4L)) & (SI_Long)1L) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object list_constant_5;     /* # */

static Object Qprocedure;          /* procedure */

/* STABLE-DENOTED-PROCEDURE-P */
Object stable_denoted_procedure_p varargs_1(int, n)
{
    Object stack_node_tree;
    Object observer_frame_qm, denoted_name_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(139,139);
    INIT_ARGS_nonrelocating();
    stack_node_tree = REQUIRED_ARG_nonrelocating();
    observer_frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Current_computation_frame;
    END_ARGS_nonrelocating();
    denoted_name_qm = denoted_name_of_type_p(stack_node_tree,list_constant_5);
    if (denoted_name_qm)
	return stable_name_of_class_p(denoted_name_qm,Qprocedure,
		observer_frame_qm);
    else
	return VALUES_1(Nil);
}

/* DENOTED-NAME-OF-TYPE-P */
Object denoted_name_of_type_p(stack_node_tree,type_specification)
    Object stack_node_tree, type_specification;
{
    Object operation;

    x_note_fn_call(139,140);
    if (SIMPLE_VECTOR_P(stack_node_tree) && EQ(ISVREF(stack_node_tree,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct)) {
	operation = ISVREF(stack_node_tree,(SI_Long)1L);
	if (EQ(operation,Qname_reference))
	    return VALUES_1(ISVREF(stack_node_tree,(SI_Long)12L));
	else if (EQ(operation,Qpush_cached_item))
	    return VALUES_1(ISVREF(stack_node_tree,(SI_Long)12L));
	else if (EQ(operation,Qensure_type)) {
	    if (type_specifications_could_intersect_p(ISVREF(stack_node_tree,
		    (SI_Long)5L),type_specification))
		return denoted_name_of_type_p(M_CAR(ISVREF(stack_node_tree,
			(SI_Long)2L)),type_specification);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* STABLE-NAME-P */
Object stable_name_p varargs_1(int, n)
{
    Object name;
    Object observer_frame_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(139,141);
    INIT_ARGS_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    observer_frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Current_computation_frame;
    END_ARGS_nonrelocating();
    return stable_name_of_class_p(name,Qitem,observer_frame_qm);
}

/* STABLE-NAME-OF-CLASS-P */
Object stable_name_of_class_p(name,class_1,observer_frame)
    Object name, class_1, observer_frame;
{
    Object frame_qm, frame_class_qm, name_or_names_qm, sub_class_bit_vector;
    Object temp_1, frame_class_definition_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(139,142);
    frame_qm = get_instance_with_name_if_any(class_1,name);
    frame_class_qm = frame_qm ? ISVREF(ISVREF(frame_qm,(SI_Long)1L),
	    (SI_Long)1L) : Qnil;
    if (frame_qm && frame_class_qm) {
	name_or_names_qm = lookup_kb_specific_property_value(name,
		Frame_or_frames_with_this_name_kbprop);
	temp = SYMBOLP(name_or_names_qm);
	if (temp);
	else
	    temp =  !(CONSP(name_or_names_qm) && CDR(name_or_names_qm));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(frame_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Method_declaration_class_description,
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp ? EQ(frame_qm,observer_frame) ||  
	    !TRUEP(block_is_unstable_p(frame_qm)) && (SI_Long)0L != 
	    (IFIX(ISVREF(frame_qm,(SI_Long)4L)) & (SI_Long)1L) : TRUEP(Nil)) {
	if (lookup_global_or_kb_specific_property_value(frame_class_qm,
		Class_description_gkbprop)) {
	    temp_1 = 
		    lookup_global_or_kb_specific_property_value(frame_class_qm,
		    Class_definition_gkbprop);
	    temp = CONSP(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else {
	    frame_class_definition_qm = 
		    get_instance_with_name_if_any(Qclass_definition,
		    frame_class_qm);
	    temp = frame_class_definition_qm ?  
		    !TRUEP(block_is_unstable_p(frame_class_definition_qm)) 
		    && (SI_Long)0L != 
		    (IFIX(ISVREF(frame_class_definition_qm,(SI_Long)4L)) & 
		    (SI_Long)1L) : TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(frame_qm);
    else
	return VALUES_1(Nil);
}

static Object Kinner_block_not_inlineable;  /* :inner-block-not-inlineable */

static Object Kcross_module_violation;  /* :cross-module-violation */

/* INNER-BLOCK-CANT-BE-INLINED-IN-OUTER-BLOCK? */
Object inner_block_cant_be_inlined_in_outer_block_qm(inner,outer)
    Object inner, outer;
{
    Object temp;

    x_note_fn_call(139,143);
    if ( !TRUEP(block_can_be_inlined_p(inner)))
	temp = Kinner_block_not_inlineable;
    else {
	temp = get_module_block_is_in(inner);
	if ( !EQ(temp,get_module_block_is_in(outer)))
	    temp = Kcross_module_violation;
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm, Qcompiled_item_being_analyzed_started_out_incomplete_qm);

static Object Qitem_depends_on_modified_stable_item;  /* item-depends-on-modified-stable-item */

static Object Qincomplete;         /* incomplete */

/* NOTE-INVALID-STABLE-FREE-REFERENCE */
Object note_invalid_stable_free_reference(compiled_item_with_reference,name)
    Object compiled_item_with_reference, name;
{
    x_note_fn_call(139,144);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(compiled_item_with_reference,Nil);
    add_to_frame_note_particulars_list_if_necessary(name,
	    Qitem_depends_on_modified_stable_item,
	    Compiled_item_being_analyzed);
    update_frame_status(compiled_item_with_reference,Qincomplete,Nil);
    if ( !(Compiled_item_being_analyzed_started_out_incomplete_qm &&  
	    !TRUEP(Compiling_incomplete_items_after_analyze_p)))
	return record_item_made_incomplete_if_appropriate(compiled_item_with_reference);
    else
	return VALUES_1(Nil);
}

static Object Qitem_depends_on_unstable_heirarchy;  /* item-depends-on-unstable-heirarchy */

/* NOTE-INVALID-STABLE-HIERARCHY */
Object note_invalid_stable_hierarchy(frame_with_invalid_assumption,
	    stability_particulars)
    Object frame_with_invalid_assumption, stability_particulars;
{
    x_note_fn_call(139,145);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame_with_invalid_assumption,Nil);
    add_to_frame_note_particulars_list_if_necessary(stability_particulars,
	    Qitem_depends_on_unstable_heirarchy,Compiled_item_being_analyzed);
    update_frame_status(frame_with_invalid_assumption,Qincomplete,Nil);
    if ( !(Compiled_item_being_analyzed_started_out_incomplete_qm &&  
	    !TRUEP(Compiling_incomplete_items_after_analyze_p)))
	return record_item_made_incomplete_if_appropriate(frame_with_invalid_assumption);
    else
	return VALUES_1(Nil);
}

static Object Qitem_depends_on_invalid_inlining;  /* item-depends-on-invalid-inlining */

/* NOTE-INVALID-INLINING */
Object note_invalid_inlining(frame_with_invalid_assumption,
	    stability_particulars)
    Object frame_with_invalid_assumption, stability_particulars;
{
    x_note_fn_call(139,146);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame_with_invalid_assumption,Nil);
    add_to_frame_note_particulars_list_if_necessary(stability_particulars,
	    Qitem_depends_on_invalid_inlining,Compiled_item_being_analyzed);
    update_frame_status(frame_with_invalid_assumption,Qincomplete,Nil);
    if ( !TRUEP(Compiled_item_being_analyzed_started_out_incomplete_qm))
	return record_item_made_incomplete_if_appropriate(frame_with_invalid_assumption);
    else
	return VALUES_1(Nil);
}

static Object Qitem_no_longer_dependent;  /* item-no-longer-dependent */

/* NOTE-INDEPENDENT-ITEM-IN-STABLE-FREE-REFERENCE */
Object note_independent_item_in_stable_free_reference(compiled_item_with_reference)
    Object compiled_item_with_reference;
{
    x_note_fn_call(139,147);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(compiled_item_with_reference,Nil);
    add_frame_note(2,Qitem_no_longer_dependent,Compiled_item_being_analyzed);
    update_frame_status(compiled_item_with_reference,Qincomplete,Nil);
    if ( !TRUEP(Compiled_item_being_analyzed_started_out_incomplete_qm))
	return record_item_made_incomplete_if_appropriate(compiled_item_with_reference);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Delete_as_item_referring_to_name_qm, Qdelete_as_item_referring_to_name_qm);

/* CHECK-FOR-UNSTABLE-INSTANCE-NAME */
Object check_for_unstable_instance_name(name)
    Object name;
{
    x_note_fn_call(139,148);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	if ( !TRUEP(block_can_be_dependent_p(Compiled_item_being_analyzed)))
	    return note_independent_item_in_stable_free_reference(Compiled_item_being_analyzed);
	else if ( !TRUEP(stable_name_p(2,name,Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    name);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-UNSTABLE-INSTANCE-NAME-OF-CLASS */
Object check_for_unstable_instance_name_of_class(name,class_1)
    Object name, class_1;
{
    x_note_fn_call(139,149);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	if ( !TRUEP(block_can_be_dependent_p(Compiled_item_being_analyzed)))
	    return note_independent_item_in_stable_free_reference(Compiled_item_being_analyzed);
	else if ( !TRUEP(stable_class_p(2,class_1,
		Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    class_1);
	else if ( !TRUEP(stable_name_of_class_p(name,class_1,
		Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    name);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-UNSTABLE-CLASS-AND-SUBCLASS */
Object check_for_unstable_class_and_subclass(class_1,subclass)
    Object class_1, subclass;
{
    Object gensymed_symbol;

    x_note_fn_call(139,150);
    add_or_delete_as_item_referring_to_name(class_1);
    add_or_delete_as_item_referring_to_name(subclass);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	if ( !TRUEP(block_can_be_dependent_p(Compiled_item_being_analyzed)))
	    return note_independent_item_in_stable_free_reference(Compiled_item_being_analyzed);
	else if ( !TRUEP(stable_class_p(2,class_1,
		Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    class_1);
	else if ( !TRUEP(stable_class_p(2,subclass,
		Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    subclass);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(subclass,
		    Class_description_gkbprop);
	    if ( !(gensymed_symbol ? TRUEP(memq_function(class_1,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil))) {
		note_invalid_stable_free_reference(Compiled_item_being_analyzed,
			class_1);
		return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
			subclass);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

static Object Qmd5_identifier_qm;  /* md5-identifier? */

/* CHECK-FOR-INVALID-INLINING */
Object check_for_invalid_inlining(reference)
    Object reference;
{
    Object gensymed_symbol, class_qm, method_or_procedure_name, arg_count;
    Object md5_id, class_description_qm, found_method_or_error_text;
    Object focus_procedure_qm, reason_for_inlining_failure_qm, focus_md5_qm;
    Object inlining_failure_reason_qm;
    char temp;

    x_note_fn_call(139,151);
    gensymed_symbol = reference;
    class_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    method_or_procedure_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg_count = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    md5_id = CAR(gensymed_symbol);
    add_or_delete_as_item_referring_to_name(method_or_procedure_name);
    if (class_qm)
	add_or_delete_as_item_referring_to_name(class_qm);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	if (class_qm) {
	    class_description_qm = 
		    lookup_global_or_kb_specific_property_value(class_qm,
		    Class_description_gkbprop);
	    found_method_or_error_text = class_description_qm ? 
		    get_specific_method(method_or_procedure_name,
		    class_description_qm,arg_count,Nil,Nil,Nil) : 
		    array_constant_11;
	    focus_procedure_qm = text_string_p(found_method_or_error_text) 
		    ? Nil : found_method_or_error_text;
	}
	else
	    focus_procedure_qm = get_instance_with_name_if_any(Qprocedure,
		    method_or_procedure_name);
	reason_for_inlining_failure_qm = Nil;
	temp =  !TRUEP(focus_procedure_qm);
	if (temp);
	else {
	    focus_md5_qm = get_slot_value_function(focus_procedure_qm,
		    Qmd5_identifier_qm,Nil);
	    if (focus_md5_qm && string_eq_w(md5_id,focus_md5_qm)) {
		inlining_failure_reason_qm = 
			inner_block_cant_be_inlined_in_outer_block_qm(focus_procedure_qm,
			Compiled_item_being_analyzed);
		reason_for_inlining_failure_qm = 
			EQ(inlining_failure_reason_qm,
			Kcross_module_violation) && Reading_kb_p ? Nil : 
			inlining_failure_reason_qm;
		temp =  !TRUEP(reason_for_inlining_failure_qm);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	}
	if (temp)
	    return note_invalid_inlining(Compiled_item_being_analyzed,
		    slot_value_list_4(class_qm,method_or_procedure_name,
		    arg_count,reason_for_inlining_failure_qm));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-UNSTABLE-CLASS-AND-NON-SUBCLASS */
Object check_for_unstable_class_and_non_subclass(class_1,non_subclass)
    Object class_1, non_subclass;
{
    Object gensymed_symbol;

    x_note_fn_call(139,152);
    add_or_delete_as_item_referring_to_name(class_1);
    add_or_delete_as_item_referring_to_name(non_subclass);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	if ( !TRUEP(block_can_be_dependent_p(Compiled_item_being_analyzed)))
	    return note_independent_item_in_stable_free_reference(Compiled_item_being_analyzed);
	else if ( !TRUEP(stable_class_p(2,class_1,
		Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    class_1);
	else if ( !TRUEP(stable_class_p(2,non_subclass,
		Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    non_subclass);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(non_subclass,
		    Class_description_gkbprop);
	    if (gensymed_symbol ? TRUEP(memq_function(class_1,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) {
		note_invalid_stable_free_reference(Compiled_item_being_analyzed,
			class_1);
		return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
			non_subclass);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-VALID-STABLE-PROCEDURE-CALL */
Object check_for_valid_stable_procedure_call(type_of_call,name,arg_types,
	    return_types)
    Object type_of_call, name, arg_types, return_types;
{
    Object valid_stable_procedure_call_qm;

    x_note_fn_call(139,153);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	if ( !TRUEP(block_can_be_dependent_p(Compiled_item_being_analyzed)))
	    return note_independent_item_in_stable_free_reference(Compiled_item_being_analyzed);
	else if ( !TRUEP(stable_name_p(2,name,Compiled_item_being_analyzed)))
	    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
		    name);
	else {
	    valid_stable_procedure_call_qm = 
		    check_for_valid_procedure_call(type_of_call,name,
		    arg_types,return_types,T,Nil);
	    if ( !TRUEP(valid_stable_procedure_call_qm))
		return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
			name);
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* DESTABILIZING-OPERATION-RESTRICTED-FOR-ITEM-P */
Object destabilizing_operation_restricted_for_item_p(item)
    Object item;
{
    x_note_fn_call(139,154);
    if ( !TRUEP(block_is_unstable_p(item)))
	return VALUES_1((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
		(SI_Long)1L) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* DESTABILIZING-ITEM-DELETION-P */
Object destabilizing_item_deletion_p(item)
    Object item;
{
    Object sub_class_bit_vector, class_name_qm, scope_conses, ab_loopvar_;
    Object subclass, subclass_definition, ab_loop_it_, temp_1, subworkspace;
    Object ab_loop_list_, gensymed_symbol_3, ab_queue_form_;
    Object ab_next_queue_element_, subblock;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(139,155);
    if (destabilizing_operation_restricted_for_item_p(item))
	return VALUES_1(item);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	    class_name_qm = ISVREF(item,(SI_Long)20L);
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar_ = class_name_qm;
	    subclass = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      subclass_definition = Nil;
	      ab_loop_it_ = Nil;
	      ab_loopvar_ = collect_subclasses(ab_loopvar_);
	    next_loop:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop;
	      temp_1 = M_CAR(ab_loopvar_);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      subclass = temp_1;
	      subclass_definition = 
		      lookup_global_or_kb_specific_property_value(subclass,
		      Class_definition_gkbprop);
	      ab_loop_it_ = 
		      destabilizing_operation_restricted_for_item_p(subclass_definition) 
		      ? subclass_definition : Qnil;
	      if (ab_loop_it_) {
		  temp_1 = ab_loop_it_;
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = Qnil;
	    end_1:;
	    POP_SPECIAL();
	}
	else
	    temp_1 = Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	    if (temp ? TRUEP(ISVREF(item,(SI_Long)18L)) : TRUEP(Nil)) {
		subworkspace = Nil;
		ab_loop_list_ = ISVREF(item,(SI_Long)18L);
		ab_loop_it_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		subworkspace = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol_3 = ACCESS_ONCE(ISVREF(subworkspace,
			(SI_Long)14L));
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) 
			: Nil;
		ab_queue_form_ = gensymed_symbol_3;
		ab_next_queue_element_ = Nil;
		subblock = Nil;
		ab_loop_it_ = Nil;
		if (ab_queue_form_)
		    ab_next_queue_element_ = 
			    constant_queue_next(ISVREF(ab_queue_form_,
			    (SI_Long)2L),ab_queue_form_);
	      next_loop_2:
		if ( !TRUEP(ab_next_queue_element_))
		    goto end_loop_2;
		subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
		ab_next_queue_element_ = 
			constant_queue_next(ab_next_queue_element_,
			ab_queue_form_);
		ab_loop_it_ = ISVREF(ISVREF(subblock,(SI_Long)1L),
			(SI_Long)16L) ? 
			destabilizing_item_deletion_p(subblock) : Qnil;
		if (ab_loop_it_)
		    goto end_2;
		goto next_loop_2;
	      end_loop_2:
		ab_loop_it_ = Qnil;
	      end_2:;
		if (ab_loop_it_) {
		    temp_1 = ab_loop_it_;
		    goto end_3;
		}
		goto next_loop_1;
	      end_loop_1:
		temp_1 = Qnil;
	      end_3:;
	    }
	    else
		temp_1 = Nil;
	    if (temp_1)
		return VALUES_1(temp_1);
	    else
		return VALUES_1(Nil);
	}
    }
}

static Object Qprocedure_definition;  /* procedure-definition */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object Qname_of_defined_class;  /* name-of-defined-class */

static Object Qdirect_superiors_of_defined_class;  /* direct-superiors-of-defined-class */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* DESTABILIZING-SLOT-P */
Object destabilizing_slot_p(frame,slot_description)
    Object frame, slot_description;
{
    Object slot_name, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(139,156);
    slot_name = ISVREF(slot_description,(SI_Long)2L);
    gensymed_symbol = ISVREF(frame,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp)
	return VALUES_1(EQ(slot_name,Qprocedure_definition) ? T : Nil);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Remote_procedure_declaration_class_description,
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
	if (temp)
	    return VALUES_1(EQ(slot_name,Qbox_translation_and_text) ? T : Nil);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Definition_class_description,(SI_Long)18L));
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
		if (EQ(slot_name,Qname_of_defined_class))
		    return VALUES_1( ! 
			    !TRUEP(get_slot_value_function(frame,
			    Qname_of_defined_class,Nil)) ? T : Nil);
		else if (EQ(slot_name,Qdirect_superiors_of_defined_class))
		    return VALUES_1( ! !(get_slot_value_function(frame,
			    Qname_of_defined_class,Nil) && 
			    get_slot_value_function(frame,
			    Qdirect_superiors_of_defined_class,Nil)) ? T : 
			    Nil);
		else
		    return VALUES_1(Qnil);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		    if (EQ(slot_name,Qname_or_names_for_frame))
			return VALUES_1( ! 
				!TRUEP(get_slot_value_function(frame,
				Qname_or_names_for_frame,Nil)) ? T : Nil);
		    else
			return VALUES_1(Nil);
		}
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
}

/* RESTRICT-DESTABILIZATION-P */
Object restrict_destabilization_p(frame,slot_description)
    Object frame, slot_description;
{
    x_note_fn_call(139,157);
    if (destabilizing_slot_p(frame,slot_description))
	return destabilizing_operation_restricted_for_item_p(frame);
    else
	return VALUES_1(Nil);
}

/* HANDLE-DEPENDENT-OR-STABLE-STATUS-CHANGE-FOR-ITEM */
Object handle_dependent_or_stable_status_change_for_item(item)
    Object item;
{
    Object name_or_names_qm, name_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, temp;
    char permanent_p_qm;

    x_note_fn_call(139,158);
    permanent_p_qm = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)1L);
    name_or_names_qm = get_lookup_slot_value_given_default(item,
	    Qname_or_names_for_frame,Nil);
    name_qm = CONSP(name_or_names_qm) ? CAR(name_or_names_qm) : 
	    name_or_names_qm;
    if (name_qm && permanent_p_qm)
	analyze_compiled_items_for_consistency(name_qm);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_1 = item;
    gensymed_symbol_2 = Nil;
    gensymed_symbol_3 = Nil;
    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3);
    return VALUES_1(temp);
}

/* HANDLE-STABLE-HIERARCHY-OR-INLINE-STATUS-CHANGE-FOR-ITEM */
Object handle_stable_hierarchy_or_inline_status_change_for_item varargs_1(int, n)
{
    Object item;
    Object inline_only_qm, x2, method_name_qm, method_class_qm;
    Object gensymed_symbol, sub_class_bit_vector, gensymed_symbol_4;
    Object gensymed_symbol_5, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp, permanent_p_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(139,159);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    inline_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SYMBOLP(item))
	return analyze_compiled_items_for_consistency(item);
    else {
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
	    permanent_p_qm = (SI_Long)0L != (IFIX(ISVREF(item,
		    (SI_Long)4L)) & (SI_Long)1L);
	    method_name_qm = Nil;
	    method_class_qm = Nil;
	    if (permanent_p_qm) {
		if (SIMPLE_VECTOR_P(item) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(item,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Method_class_description,
			    (SI_Long)18L));
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
		    method_name_qm = procedure_method_name_function(item);
		    analyze_compiled_items_for_consistency(method_name_qm);
		    if ( !TRUEP(inline_only_qm)) {
			method_class_qm = 
				procedure_method_class_function(item);
			analyze_compiled_items_for_consistency(method_class_qm);
		    }
		}
		else {
		    if (SIMPLE_VECTOR_P(item) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(item,(SI_Long)1L);
			gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				EQ(ISVREF(x2,(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? x2 : Qnil;
		    }
		    else
			gensymed_symbol = Nil;
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Method_declaration_class_description,
				(SI_Long)18L));
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
		    if (temp) {
			method_name_qm = 
				get_lookup_slot_value_given_default(item,
				Qname_or_names_for_frame,Nil);
			if (CONSP(method_name_qm))
			    method_name_qm = CAR(method_name_qm);
			analyze_compiled_items_for_consistency(method_name_qm);
		    }
		    else {
			if (SIMPLE_VECTOR_P(item) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
				(SI_Long)2L &&  !EQ(ISVREF(item,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(item,(SI_Long)1L);
			    gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				    EQ(ISVREF(x2,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? x2 : Qnil;
			}
			else
			    gensymed_symbol = Nil;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Function_definition_class_description,
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
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    if (get_slot_value_function(item,
				    Qname_or_names_for_frame,Nil)) {
				method_name_qm = 
					get_slot_value_function(item,
					Qname_or_names_for_frame,Nil);
				if (CONSP(method_name_qm)) {
				    method_name_qm = CAR(method_name_qm);
				    analyze_compiled_items_for_consistency(method_name_qm);
				}
			    }
			}
			else;
		    }
		}
	    }
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_4 = item;
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    return inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
	else
	    return VALUES_1(Qt);
    }
}

Object Stack_special_form_converter_prop = UNBOUND;

Object Preferred_instruction_chooser_prop = UNBOUND;

Object Stack_node_instruction_emitter_prop = UNBOUND;

Object Stack_node_instruction_reclaimer_prop = UNBOUND;

Object Stack_node_instruction_extra_info_copier_prop = UNBOUND;

static Object Qstack_node_instruction_reclaimer;  /* stack-node-instruction-reclaimer */

/* RECLAIM-STACK-NODE-INSTRUCTION */
Object reclaim_stack_node_instruction(stack_node_instruction)
    Object stack_node_instruction;
{
    Object gensymed_symbol, reclaimer_qm, gensymed_symbol_1;

    x_note_fn_call(139,160);
    gensymed_symbol = ISVREF(stack_node_instruction,(SI_Long)1L);
    reclaimer_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qstack_node_instruction_reclaimer);
    if (reclaimer_qm) {
	gensymed_symbol = reclaimer_qm;
	gensymed_symbol_1 = ISVREF(stack_node_instruction,(SI_Long)12L);
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	SVREF(stack_node_instruction,FIX((SI_Long)12L)) = Nil;
    }
    reclaim_stack_node_instruction_1_1(stack_node_instruction);
    return VALUES_1(Nil);
}

static Object Qstack_node_instruction_extra_info_copier;  /* stack-node-instruction-extra-info-copier */

/* COPY-STACK-NODE-INSTRUCTION-EXTRA-INFO */
Object copy_stack_node_instruction_extra_info(a_stack_node_instruction)
    Object a_stack_node_instruction;
{
    Object gensymed_symbol, copier_qm, temp;

    x_note_fn_call(139,161);
    gensymed_symbol = ISVREF(a_stack_node_instruction,(SI_Long)1L);
    copier_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qstack_node_instruction_extra_info_copier);
    temp = copier_qm ? inline_funcall_1(copier_qm,
	    a_stack_node_instruction) : ISVREF(a_stack_node_instruction,
	    (SI_Long)12L);
    return VALUES_1(temp);
}

Object Expiration_special_form_operator_p_prop = UNBOUND;

Object Expiration_source_operator_p_prop = UNBOUND;

Object Procedure_statement_writer_prop = UNBOUND;

Object Procedure_statement_compiler_prop = UNBOUND;

Object Action_compiler_prop = UNBOUND;

Object Action_method_compiler_prop = UNBOUND;

Object Pseudo_instruction_byte_code_emitter_prop = UNBOUND;

/* CREATE-PSEUDO-INSTRUCTION-PROPERTY-LIST */
Object create_pseudo_instruction_property_list()
{
    Object a;

    x_note_fn_call(139,162);
    a = allocate_managed_simple_vector(FIX((SI_Long)1L));
    SVREF(a,FIX((SI_Long)0L)) = Nil;
    return VALUES_1(a);
}

/* RECLAIM-CREATE-PSEUDO-INSTRUCTION-PROPERTY-LIST */
Object reclaim_create_pseudo_instruction_property_list(headed_plist)
    Object headed_plist;
{
    x_note_fn_call(139,163);
    return reclaim_managed_simple_vector(headed_plist);
}

/* SET-PSEUDO-INSTRUCTION-PROPERTY */
Object set_pseudo_instruction_property(headed_plist,key,value)
    Object headed_plist, key, value;
{
    Object tail_qm, svref_new_value;

    x_note_fn_call(139,164);
    tail_qm = memq_function(key,ISVREF(headed_plist,(SI_Long)0L));
    if (tail_qm)
	return VALUES_1(M_CADR(tail_qm) = value);
    else {
	svref_new_value = phrase_cons(key,phrase_cons(value,
		ISVREF(headed_plist,(SI_Long)0L)));
	return VALUES_1(SVREF(headed_plist,FIX((SI_Long)0L)) = 
		svref_new_value);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_activity, Qcurrent_computation_activity);

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

/* WRITE-ACTIVITY-GIVEN-INDEX */
Object write_activity_given_index(frame_qm,component_particulars_qm,
	    activity_index)
    Object frame_qm, component_particulars_qm, activity_index;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(139,165);
    if (FIXNUM_PLUSP(activity_index) && FIXNUM_LT(activity_index,
	    SIMPLE_ARRAY_ANY_1_LENGTH(Registered_activities_array)))
	twrite_general_string(ISVREF(Registered_activities_array,
		IFIX(activity_index)));
    else if ( !TRUEP(frame_qm))
	twrite_general_string(ISVREF(Registered_activities_array,(SI_Long)0L));
    else {
	gensymed_symbol = ISVREF(frame_qm,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
	if (temp)
	    twrite_beginning_of_wide_string(array_constant_12,
		    FIX((SI_Long)15L));
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	    if (temp)
		twrite_beginning_of_wide_string(array_constant_13,
			FIX((SI_Long)18L));
	    else {
		twrite_beginning_of_wide_string(array_constant_14,
			FIX((SI_Long)10L));
		if (component_particulars_qm)
		    denote_component_of_block(3,Nil,
			    component_particulars_qm,frame_qm);
		else
		    denote_component_of_block(3,T,component_particulars_qm,
			    frame_qm);
	    }
	}
    }
    return VALUES_1(Nil);
}

/* ACTIVITY-GIVEN-INDEX */
Object activity_given_index(frame_qm,component_particulars_qm,activity_index)
    Object frame_qm, component_particulars_qm, activity_index;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(139,166);
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
	      write_activity_given_index(frame_qm,component_particulars_qm,
		      activity_index);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* ADD-ACTIVITY-TRANSLATION-TO-CODE-STREAM */
Object add_activity_translation_to_code_stream(byte_code_stream,
	    counter_address,activity_number)
    Object byte_code_stream, counter_address, activity_number;
{
    Object svref_new_value;

    x_note_fn_call(139,167);
    if (ISVREF(byte_code_stream,(SI_Long)7L))
	nconc2(ISVREF(byte_code_stream,(SI_Long)7L),
		slot_value_cons_1(slot_value_list_2(counter_address,
		activity_number),Nil));
    else {
	svref_new_value = 
		slot_value_cons_1(slot_value_list_2(counter_address,
		activity_number),Nil);
	SVREF(byte_code_stream,FIX((SI_Long)7L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* FIND-ACTIVITY */
Object find_activity(byte_code_body,program_counter)
    Object byte_code_body, program_counter;
{
    Object index_1, activity, ab_loop_list_, current_activity_qm;
    Object last_activity_qm, ab_loop_desetq_, temp;

    x_note_fn_call(139,168);
    index_1 = Nil;
    activity = Nil;
    ab_loop_list_ = ISVREF(byte_code_body,(SI_Long)5L);
    current_activity_qm = Nil;
    last_activity_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    index_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    activity = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (NUM_GT(index_1,program_counter))
	current_activity_qm = last_activity_qm;
    last_activity_qm = activity;
    goto next_loop;
  end_loop:
    if ( !TRUEP(current_activity_qm))
	current_activity_qm = last_activity_qm;
    return VALUES_1(ISVREF(Registered_activities_array,
	    IFIX(current_activity_qm)));
    return VALUES_1(Qnil);
}

/* PRINT-ACTIVITY-LIST */
Object print_activity_list(activity_list)
    Object activity_list;
{
    Object index_1, activity, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(139,169);
    index_1 = Nil;
    activity = Nil;
    ab_loop_list_ = activity_list;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    index_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    activity = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    format((SI_Long)4L,T,"~% pc: ~a;~a",index_1,
	    ISVREF(Registered_activities_array,IFIX(activity)));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PRINT-ACTIVITIES-IN-BYTE-CODE-BODY */
Object print_activities_in_byte_code_body(byte_code_body)
    Object byte_code_body;
{
    x_note_fn_call(139,170);
    return print_activity_list(ISVREF(byte_code_body,(SI_Long)5L));
}

static Object string_constant_51;  /* " at program counter ~a " */

/* WRITE-ACTIVITY-GIVEN-PC-AND-BYTE-CODE-BODY */
Object write_activity_given_pc_and_byte_code_body(byte_code_body,pc)
    Object byte_code_body, pc;
{
    x_note_fn_call(139,171);
    twrite_general_string(find_activity(byte_code_body,pc));
    tformat(2,string_constant_51,pc);
    return VALUES_1(Nil);
}

Object The_type_description_of_computation_instance = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_computation_instances, Qchain_of_available_computation_instances);

DEFINE_VARIABLE_WITH_SYMBOL(Computation_instance_count, Qcomputation_instance_count);

Object Chain_of_available_computation_instances_vector = UNBOUND;

/* COMPUTATION-INSTANCE-STRUCTURE-MEMORY-USAGE */
Object computation_instance_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(139,172);
    temp = Computation_instance_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-COMPUTATION-INSTANCE-COUNT */
Object outstanding_computation_instance_count()
{
    Object def_structure_computation_instance_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(139,173);
    gensymed_symbol = IFIX(Computation_instance_count);
    def_structure_computation_instance_variable = 
	    Chain_of_available_computation_instances;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_computation_instance_variable))
	goto end_loop;
    def_structure_computation_instance_variable = 
	    ISVREF(def_structure_computation_instance_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-COMPUTATION-INSTANCE-1 */
Object reclaim_computation_instance_1(computation_instance)
    Object computation_instance;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(139,174);
    inline_note_reclaim_cons(computation_instance,Nil);
    structure_being_reclaimed = computation_instance;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(computation_instance,(SI_Long)7L);
      if (CAS_SVREF(computation_instance,(SI_Long)7L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_1;
      }
      goto next_loop;
    end_loop:
    end_1:;
      SVREF(computation_instance,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_computation_instances_vector,
	    IFIX(Current_thread_index));
    SVREF(computation_instance,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_computation_instances_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = computation_instance;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-COMPUTATION-INSTANCE */
Object reclaim_structure_for_computation_instance(computation_instance)
    Object computation_instance;
{
    x_note_fn_call(139,175);
    return reclaim_computation_instance_1(computation_instance);
}

static Object Qg2_defstruct_structure_name_computation_instance_g2_struct;  /* g2-defstruct-structure-name::computation-instance-g2-struct */

/* MAKE-PERMANENT-COMPUTATION-INSTANCE-STRUCTURE-INTERNAL */
Object make_permanent_computation_instance_structure_internal()
{
    Object def_structure_computation_instance_variable;
    Object defstruct_g2_computation_instance_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(139,176);
    def_structure_computation_instance_variable = Nil;
    atomic_incff_symval(Qcomputation_instance_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_computation_instance_variable = Nil;
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
	defstruct_g2_computation_instance_variable = the_array;
	SVREF(defstruct_g2_computation_instance_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_computation_instance_g2_struct;
	def_structure_computation_instance_variable = 
		defstruct_g2_computation_instance_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_computation_instance_variable);
}

/* MAKE-COMPUTATION-INSTANCE-1 */
Object make_computation_instance_1()
{
    Object def_structure_computation_instance_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(139,177);
    def_structure_computation_instance_variable = 
	    ISVREF(Chain_of_available_computation_instances_vector,
	    IFIX(Current_thread_index));
    if (def_structure_computation_instance_variable) {
	svref_arg_1 = Chain_of_available_computation_instances_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_computation_instance_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_computation_instance_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_computation_instance_g2_struct;
    }
    else
	def_structure_computation_instance_variable = 
		make_permanent_computation_instance_structure_internal();
    inline_note_allocate_cons(def_structure_computation_instance_variable,Nil);
    SVREF(def_structure_computation_instance_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_computation_instance_variable);
}

/* INVOCATION-STACK-PROGRAM-COUNTER-FUNCTION */
Object invocation_stack_program_counter_function(ci)
    Object ci;
{
    Object temp;

    x_note_fn_call(139,178);
    temp = ISVREF(ci,(SI_Long)3L);
    return VALUES_1(temp);
}

/* RUNNABLE-P-FUNCTION */
Object runnable_p_function(block)
    Object block;
{
    Object temp;

    x_note_fn_call(139,179);
    temp = ISVREF(block,(SI_Long)8L);
    if ( !TRUEP(CAR(temp))) {
	temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)1L) ? T : Nil;
	if (temp);
	else
	    temp =  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		    (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)16777216L) 
		    ? ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) 
		    & (SI_Long)8192L)) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant_52;  /* "disabled" */

static Object string_constant_53;  /* "not active" */

static Object string_constant_54;  /* "inside a breakpoint" */

static Object string_constant_55;  /* "in an unknown state" */

/* REASON-NOT-RUNNABLE */
Object reason_not_runnable(block)
    Object block;
{
    Object temp;

    x_note_fn_call(139,180);
    temp = ISVREF(block,(SI_Long)8L);
    temp = CAR(temp);
    if (temp)
	return VALUES_1(temp);
    else if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)8192L))
	return VALUES_1(string_constant_52);
    else if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)1L)))
	return VALUES_1(string_constant_53);
    else if (Inside_breakpoint_p)
	return VALUES_1(string_constant_54);
    else
	return VALUES_1(string_constant_55);
}

void comp_utils_INIT()
{
    Object named_dynamic_extent_description, write_compiler_warnings_note_1;
    Object write_compiler_errors_note_1, temp;
    Object reclaim_structure_for_goto_tag_entry_1;
    Object reclaim_structure_for_compiler_code_body_entry_1;
    Object reclaim_structure_for_pseudo_instruction_stream_1;
    Object reclaim_structure_for_inlining_data_holder_1;
    Object reclaim_structure_for_byte_code_stream_1, gensymed_symbol;
    Object the_array, reclaim_structure_for_stack_node_1;
    Object reclaim_structure_for_stack_node_instruction_1;
    Object reclaim_structure_for_computation_instance_1;
    SI_Long i, ab_loop_bind_;
    Object Qgeneric_method_lambda_list, list_constant_10;
    Object Qnote_may_refer_to_inactive_items_change, AB_package;
    Object Qnote_runs_while_inactive_change, Qkb_frame, Qcomputation_instance;
    Object Qreclaim_structure, Qoutstanding_computation_instance_count;
    Object Qcomputation_instance_structure_memory_usage, Qutilities2;
    Object string_constant_142, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_141, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_8;
    Object array_constant_15, string_constant_140, string_constant_139;
    Object string_constant_138, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object string_constant_129, string_constant_128, string_constant_127;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object string_constant_123, string_constant_122, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_118;
    Object string_constant_117, string_constant_116, string_constant_115;
    Object string_constant_114, string_constant_113, string_constant_112;
    Object string_constant_111, string_constant_110, string_constant_109;
    Object string_constant_108, string_constant_107, string_constant_106;
    Object string_constant_105, string_constant_104, string_constant_103;
    Object string_constant_102, string_constant_101, string_constant_100;
    Object string_constant_99, string_constant_98, string_constant_97;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object string_constant_93, string_constant_92, string_constant_91;
    Object string_constant_90, string_constant_89, string_constant_88;
    Object string_constant_87, string_constant_86, string_constant_85;
    Object string_constant_84, string_constant_83, string_constant_82;
    Object string_constant_81, string_constant_80, string_constant_79;
    Object string_constant_78, string_constant_77, string_constant_76;
    Object string_constant_75, string_constant_74, string_constant_73;
    Object Qcomp_utils, Qpseudo_instruction_byte_code_emitter;
    Object Qaction_method_compiler, Qaction_compiler;
    Object Qprocedure_statement_compiler, Qprocedure_statement_writer;
    Object Qexpiration_source_operator_p, Qexpiration_special_form_operator_p;
    Object Qstack_node_instruction_emitter, Qpreferred_instruction_chooser;
    Object Qstack_special_form_converter, Qstack_node_instruction;
    Object Qoutstanding_stack_node_instruction_count;
    Object Qstack_node_instruction_structure_memory_usage, string_constant_72;
    Object string_constant_71, Qstack_node, Qoutstanding_stack_node_count;
    Object Qstack_node_structure_memory_usage, string_constant_70;
    Object string_constant_69, Qmaximum_number_of_funcalled_evaluators;
    Object Qbase_in_line_evaluator_number;
    Object Qmaximum_number_of_in_line_evaluators;
    Object Qmaximum_number_of_extended_inline_evaluators;
    Object Qdispatch_instruction_number, Qstack_evaluators, string_constant_68;
    Object Qstack_cons_memory_usage, Qoutstanding_stack_conses, Qstack_utils;
    Object list_constant_7, Qstack_cons_counter_vector, list_constant_6;
    Object Qavailable_stack_conses_tail_vector, Qavailable_stack_conses_vector;
    Object Qbyte_code_stream, Qoutstanding_byte_code_stream_count;
    Object Qbyte_code_stream_structure_memory_usage, string_constant_67;
    Object string_constant_66, Qinlining_data_holder;
    Object Qoutstanding_inlining_data_holder_count;
    Object Qinlining_data_holder_structure_memory_usage, string_constant_65;
    Object string_constant_64, Qbits_in_var_spot_nesting;
    Object Qmaximum_var_spot_nesting, Qbits_in_var_spot_local_index;
    Object Qmaximum_var_spot_local_index, Qbits_in_var_spot_index;
    Object Qmaximum_var_spot_index, list_constant_9, Qab_or, Qparameter;
    Object Qstable_name_of_type, QCACHED_ATTRIBUTE_NAME;
    Object Qcached_attribute_cons_marker, Qpseudo_instruction_stream;
    Object Qoutstanding_pseudo_instruction_stream_count;
    Object Qpseudo_instruction_stream_structure_memory_usage;
    Object string_constant_63, string_constant_62, Qcompiler_code_body_entry;
    Object Qoutstanding_compiler_code_body_entry_count;
    Object Qcompiler_code_body_entry_structure_memory_usage;
    Object string_constant_61, string_constant_60, Qgoto_tag_entry;
    Object Qoutstanding_goto_tag_entry_count;
    Object Qgoto_tag_entry_structure_memory_usage, string_constant_59;
    Object string_constant_58, Qframe_note_writer_1;
    Object Qcompiler_header_statement_length_limit, string_constant_57;
    Object Qcompiler_cons_memory_usage, Qoutstanding_compiler_conses;
    Object Qutilities1, Qcompiler_cons_counter_vector, Qmake_thread_array;
    Object Kfuncall, Qavailable_compiler_conses_tail_vector;
    Object Qavailable_compiler_conses_vector;
    Object Qnamed_dynamic_extent_description, string_constant_56;
    Object Qrequired_domain_types_of_role;

    x_note_fn_call(139,181);
    SET_PACKAGE("AB");
    if (Always_recompile_on_load == UNBOUND)
	Always_recompile_on_load = Nil;
    if (Recompile_on_next_load == UNBOUND)
	Recompile_on_next_load = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qrequired_domain_types_of_role = 
	    STATIC_SYMBOL("REQUIRED-DOMAIN-TYPES-OF-ROLE",AB_package);
    Required_domain_types_of_role_prop = Qrequired_domain_types_of_role;
    string_constant_56 = 
	    STATIC_STRING("WORKING-ON-LEXICAL-COMPUTATION-OF-FRAME");
    if (Working_on_lexical_computation_of_frame == UNBOUND)
	Working_on_lexical_computation_of_frame = make_recursive_lock(2,
		Kname,string_constant_56);
    Qworking_on_lexical_computation_of_frame = 
	    STATIC_SYMBOL("WORKING-ON-LEXICAL-COMPUTATION-OF-FRAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworking_on_lexical_computation_of_frame,
	    Working_on_lexical_computation_of_frame);
    Qcomp_utils = STATIC_SYMBOL("COMP-UTILS",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qworking_on_lexical_computation_of_frame,
	    Qcomp_utils,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qworking_on_lexical_computation_of_frame,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    record_system_variable(Qcurrent_computation_frame,Qcomp_utils,Nil,Qnil,
	    Qt,Qnil,Qnil);
    if (Current_computation_component_particulars == UNBOUND)
	Current_computation_component_particulars = Nil;
    Qcurrent_computation_instance = 
	    STATIC_SYMBOL("CURRENT-COMPUTATION-INSTANCE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_computation_instance,
	    Current_computation_instance);
    record_system_variable(Qcurrent_computation_instance,Qcomp_utils,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qvariables_that_did_not_have_values = 
	    STATIC_SYMBOL("*VARIABLES-THAT-DID-NOT-HAVE-VALUES*",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvariables_that_did_not_have_values,
	    Variables_that_did_not_have_values);
    record_system_variable(Qvariables_that_did_not_have_values,Qcomp_utils,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qavailable_compiler_conses = STATIC_SYMBOL("AVAILABLE-COMPILER-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_compiler_conses,
	    Available_compiler_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_compiler_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_compiler_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-COMPILER-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_compiler_conses_tail,
	    Available_compiler_conses_tail);
    record_system_variable(Qavailable_compiler_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_compiler_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-COMPILER-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_compiler_conses_vector,
	    Available_compiler_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_compiler_conses_vector,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qavailable_compiler_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-COMPILER-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_compiler_conses_tail_vector,
	    Available_compiler_conses_tail_vector);
    record_system_variable(Qavailable_compiler_conses_tail_vector,
	    Qutilities1,list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qcompiler_cons_counter_vector = 
	    STATIC_SYMBOL("COMPILER-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiler_cons_counter_vector,
	    Compiler_cons_counter_vector);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qcompiler_cons_counter_vector,Qutilities1,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qcompiler_cons_counter = STATIC_SYMBOL("COMPILER-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiler_cons_counter,Compiler_cons_counter);
    record_system_variable(Qcompiler_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_compiler_conses = 
	    STATIC_SYMBOL("OUTSTANDING-COMPILER-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_compiler_conses,
	    STATIC_FUNCTION(outstanding_compiler_conses,NIL,FALSE,0,0));
    Qcompiler_cons_memory_usage = 
	    STATIC_SYMBOL("COMPILER-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qcompiler_cons_memory_usage,
	    STATIC_FUNCTION(compiler_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_57 = STATIC_STRING("1q83-NTy9k83-NSy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_compiler_conses);
    push_optimized_constant(Qcompiler_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_57));
    Qcompiler = STATIC_SYMBOL("COMPILER",AB_package);
    if (Compiler_warnings == UNBOUND)
	Compiler_warnings = Nil;
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)96L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)35L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)37L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)42L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)43L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)45L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)46L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)48L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)49L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)50L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)51L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)52L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)53L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)54L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)55L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)56L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)57L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)58L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)59L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)60L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)61L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)62L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)63L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)64L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)65L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)66L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)67L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)68L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)69L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)70L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)71L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)72L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)73L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)74L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)75L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)76L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)77L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)78L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)79L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)80L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)81L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)82L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)83L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)84L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)85L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)86L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)94L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)95L,(SI_Long)57344L);
    Qcompiler_header_statement_length_limit = 
	    STATIC_SYMBOL("COMPILER-HEADER-STATEMENT-LENGTH-LIMIT",AB_package);
    SET_SYMBOL_VALUE(Qcompiler_header_statement_length_limit,
	    FIX((SI_Long)40L));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_1 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    if (Compiler_errors == UNBOUND)
	Compiler_errors = Nil;
    array_constant_4 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)35L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)38L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)39L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)41L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)46L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)47L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)35L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)37L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)40L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)41L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)42L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)44L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)45L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)46L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)47L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)48L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)49L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)50L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)51L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)52L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)55L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)62L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)63L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)41L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)57344L);
    Qcompiler_warnings = STATIC_SYMBOL("COMPILER-WARNINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiler_warnings,Compiler_warnings);
    Qcompiler_errors = STATIC_SYMBOL("COMPILER-ERRORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiler_errors,Compiler_errors);
    Qprocedure_compiler_warnings = 
	    STATIC_SYMBOL("PROCEDURE-COMPILER-WARNINGS",AB_package);
    Qprocedure_compiler_errors = STATIC_SYMBOL("PROCEDURE-COMPILER-ERRORS",
	    AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant = 
	    STATIC_STRING("the compiler reported the following warning: ~a");
    string_constant_1 = 
	    STATIC_STRING("the compiler reported the following warnings: ");
    array_constant_8 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING("(~a) ~a");
    write_compiler_warnings_note_1 = 
	    STATIC_FUNCTION(write_compiler_warnings_note,NIL,FALSE,2,2);
    mutate_global_property(Qcompiler_warnings,
	    write_compiler_warnings_note_1,Qframe_note_writer_1);
    string_constant_3 = 
	    STATIC_STRING("the compiler reported the following error: ~a");
    string_constant_4 = 
	    STATIC_STRING("the compiler reported the following errors: ");
    write_compiler_errors_note_1 = 
	    STATIC_FUNCTION(write_compiler_errors_note,NIL,FALSE,2,2);
    mutate_global_property(Qcompiler_errors,write_compiler_errors_note_1,
	    Qframe_note_writer_1);
    if (Goto_tags_in_compilation == UNBOUND)
	Goto_tags_in_compilation = Nil;
    if (Lexically_visible_goto_tags == UNBOUND)
	Lexically_visible_goto_tags = Nil;
    if (Compiler_free_references == UNBOUND)
	Compiler_free_references = Nil;
    if (Collecting_free_references == UNBOUND)
	Collecting_free_references = Nil;
    if (Code_body_entries_in_compilation == UNBOUND)
	Code_body_entries_in_compilation = Nil;
    if (Lexically_visible_code_bodies == UNBOUND)
	Lexically_visible_code_bodies = Nil;
    Qg2_defstruct_structure_name_goto_tag_entry_g2_struct = 
	    STATIC_SYMBOL("GOTO-TAG-ENTRY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgoto_tag_entry = STATIC_SYMBOL("GOTO-TAG-ENTRY",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_goto_tag_entry_g2_struct,
	    Qgoto_tag_entry,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgoto_tag_entry,
	    Qg2_defstruct_structure_name_goto_tag_entry_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_goto_tag_entry == UNBOUND)
	The_type_description_of_goto_tag_entry = Nil;
    string_constant_58 = 
	    STATIC_STRING("43Dy8m83i4y1n83i4y8n8k1l8n0000001l1n8y83-41y1m83--Ey83--Dykrk0k0");
    temp = The_type_description_of_goto_tag_entry;
    The_type_description_of_goto_tag_entry = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_58));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_goto_tag_entry_g2_struct,
	    The_type_description_of_goto_tag_entry,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgoto_tag_entry,
	    The_type_description_of_goto_tag_entry,Qtype_description_of_type);
    Qoutstanding_goto_tag_entry_count = 
	    STATIC_SYMBOL("OUTSTANDING-GOTO-TAG-ENTRY-COUNT",AB_package);
    Qgoto_tag_entry_structure_memory_usage = 
	    STATIC_SYMBOL("GOTO-TAG-ENTRY-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_59 = STATIC_STRING("1q83i4y8s83-X+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_goto_tag_entry_count);
    push_optimized_constant(Qgoto_tag_entry_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_59));
    Qchain_of_available_goto_tag_entrys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GOTO-TAG-ENTRYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_goto_tag_entrys,
	    Chain_of_available_goto_tag_entrys);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_goto_tag_entrys,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qgoto_tag_entry_count = STATIC_SYMBOL("GOTO-TAG-ENTRY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgoto_tag_entry_count,Goto_tag_entry_count);
    record_system_variable(Qgoto_tag_entry_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_goto_tag_entrys_vector == UNBOUND)
	Chain_of_available_goto_tag_entrys_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgoto_tag_entry_structure_memory_usage,
	    STATIC_FUNCTION(goto_tag_entry_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_goto_tag_entry_count,
	    STATIC_FUNCTION(outstanding_goto_tag_entry_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_goto_tag_entry_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_goto_tag_entry,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qgoto_tag_entry,
	    reclaim_structure_for_goto_tag_entry_1);
    Qg2_defstruct_structure_name_compiler_code_body_entry_g2_struct = 
	    STATIC_SYMBOL("COMPILER-CODE-BODY-ENTRY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcompiler_code_body_entry = STATIC_SYMBOL("COMPILER-CODE-BODY-ENTRY",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_compiler_code_body_entry_g2_struct,
	    Qcompiler_code_body_entry,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcompiler_code_body_entry,
	    Qg2_defstruct_structure_name_compiler_code_body_entry_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_compiler_code_body_entry == UNBOUND)
	The_type_description_of_compiler_code_body_entry = Nil;
    string_constant_60 = 
	    STATIC_STRING("43Dy8m83g3y1n83g3y8n8k1l8n0000001l1n8y83-3Fy1m83sSy83sTykwk0k0");
    temp = The_type_description_of_compiler_code_body_entry;
    The_type_description_of_compiler_code_body_entry = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_60));
    mutate_global_property(Qg2_defstruct_structure_name_compiler_code_body_entry_g2_struct,
	    The_type_description_of_compiler_code_body_entry,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcompiler_code_body_entry,
	    The_type_description_of_compiler_code_body_entry,
	    Qtype_description_of_type);
    Qoutstanding_compiler_code_body_entry_count = 
	    STATIC_SYMBOL("OUTSTANDING-COMPILER-CODE-BODY-ENTRY-COUNT",
	    AB_package);
    Qcompiler_code_body_entry_structure_memory_usage = 
	    STATIC_SYMBOL("COMPILER-CODE-BODY-ENTRY-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_61 = STATIC_STRING("1q83g3y8s83-NRy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_compiler_code_body_entry_count);
    push_optimized_constant(Qcompiler_code_body_entry_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_61));
    Qchain_of_available_compiler_code_body_entrys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-COMPILER-CODE-BODY-ENTRYS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_compiler_code_body_entrys,
	    Chain_of_available_compiler_code_body_entrys);
    record_system_variable(Qchain_of_available_compiler_code_body_entrys,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcompiler_code_body_entry_count = 
	    STATIC_SYMBOL("COMPILER-CODE-BODY-ENTRY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiler_code_body_entry_count,
	    Compiler_code_body_entry_count);
    record_system_variable(Qcompiler_code_body_entry_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_compiler_code_body_entrys_vector == UNBOUND)
	Chain_of_available_compiler_code_body_entrys_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcompiler_code_body_entry_structure_memory_usage,
	    STATIC_FUNCTION(compiler_code_body_entry_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_compiler_code_body_entry_count,
	    STATIC_FUNCTION(outstanding_compiler_code_body_entry_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_compiler_code_body_entry_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_compiler_code_body_entry,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcompiler_code_body_entry,
	    reclaim_structure_for_compiler_code_body_entry_1);
    Maximum_code_body_count = FIX((SI_Long)256L);
    string_constant_5 = STATIC_STRING("nested code body establishment");
    string_constant_6 = 
	    STATIC_STRING("Attempting to create multiple code bodies within ~NF, when they ~\n       can only exist within procedures.");
    string_constant_7 = 
	    string_append2(STATIC_STRING("The maximum number of code bodies within a single procedure, ~a, ~\n       has been exceeded.  Code bodies are generated by do in parallel ~\n       and on error statements.  Yo"),
	    STATIC_STRING("u must reduce the number of do in\n       parallel and on error statements for this procedure to compile."));
    Qcode_body = STATIC_SYMBOL("CODE-BODY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcode_body,Code_body);
    Qg2_defstruct_structure_name_pseudo_instruction_stream_g2_struct = 
	    STATIC_SYMBOL("PSEUDO-INSTRUCTION-STREAM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpseudo_instruction_stream = STATIC_SYMBOL("PSEUDO-INSTRUCTION-STREAM",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_pseudo_instruction_stream_g2_struct,
	    Qpseudo_instruction_stream,Qab_name_of_unique_structure_type);
    mutate_global_property(Qpseudo_instruction_stream,
	    Qg2_defstruct_structure_name_pseudo_instruction_stream_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_pseudo_instruction_stream == UNBOUND)
	The_type_description_of_pseudo_instruction_stream = Nil;
    string_constant_62 = 
	    STATIC_STRING("43Dy8m83lqy1n83lqy8n8k1l8n0000000kmk0k0");
    temp = The_type_description_of_pseudo_instruction_stream;
    The_type_description_of_pseudo_instruction_stream = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_62));
    mutate_global_property(Qg2_defstruct_structure_name_pseudo_instruction_stream_g2_struct,
	    The_type_description_of_pseudo_instruction_stream,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qpseudo_instruction_stream,
	    The_type_description_of_pseudo_instruction_stream,
	    Qtype_description_of_type);
    Qoutstanding_pseudo_instruction_stream_count = 
	    STATIC_SYMBOL("OUTSTANDING-PSEUDO-INSTRUCTION-STREAM-COUNT",
	    AB_package);
    Qpseudo_instruction_stream_structure_memory_usage = 
	    STATIC_SYMBOL("PSEUDO-INSTRUCTION-STREAM-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_63 = STATIC_STRING("1q83lqy8s83-kgy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_pseudo_instruction_stream_count);
    push_optimized_constant(Qpseudo_instruction_stream_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_63));
    Qchain_of_available_pseudo_instruction_streams = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PSEUDO-INSTRUCTION-STREAMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_pseudo_instruction_streams,
	    Chain_of_available_pseudo_instruction_streams);
    record_system_variable(Qchain_of_available_pseudo_instruction_streams,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qpseudo_instruction_stream_count = 
	    STATIC_SYMBOL("PSEUDO-INSTRUCTION-STREAM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpseudo_instruction_stream_count,
	    Pseudo_instruction_stream_count);
    record_system_variable(Qpseudo_instruction_stream_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_pseudo_instruction_streams_vector == UNBOUND)
	Chain_of_available_pseudo_instruction_streams_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qpseudo_instruction_stream_structure_memory_usage,
	    STATIC_FUNCTION(pseudo_instruction_stream_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_pseudo_instruction_stream_count,
	    STATIC_FUNCTION(outstanding_pseudo_instruction_stream_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_pseudo_instruction_stream_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_pseudo_instruction_stream,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qpseudo_instruction_stream,
	    reclaim_structure_for_pseudo_instruction_stream_1);
    string_constant_8 = 
	    STATIC_STRING("The tag ~a is declared more than once in this procedure.");
    string_constant_9 = 
	    string_append2(STATIC_STRING("Illegal branch attempt to tag ~a.  Branches may not be ~\n                    performed into the bodies of iteration statements, into IN ~\n                    PARALLEL statemen"),
	    STATIC_STRING("ts, or into the bodies of ON ERROR ~\n                    statements."));
    string_constant_10 = 
	    STATIC_STRING("Illegal branch to the tag ~a, which is not defined.");
    Qgoto_tag_recorder = STATIC_SYMBOL("GOTO-TAG-RECORDER",AB_package);
    Goto_tag_recorder_prop = Qgoto_tag_recorder;
    if (New_goto_tag_counter == UNBOUND)
	New_goto_tag_counter = FIX((SI_Long)-1L);
    Qcached_attribute_cons_marker = 
	    STATIC_SYMBOL("CACHED-ATTRIBUTE-CONS-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_attribute_cons_marker,
	    Cached_attribute_cons_marker);
    QCACHED_ATTRIBUTE_NAME = STATIC_SYMBOL("cached-attribute-name",AB_package);
    SET_SYMBOL_VALUE(Qcached_attribute_cons_marker,QCACHED_ATTRIBUTE_NAME);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qcached_name = STATIC_SYMBOL("CACHED-NAME",AB_package);
    Qstable_name = STATIC_SYMBOL("STABLE-NAME",AB_package);
    Qname_of_class_instance = STATIC_SYMBOL("NAME-OF-CLASS-INSTANCE",
	    AB_package);
    Qname_of_type = STATIC_SYMBOL("NAME-OF-TYPE",AB_package);
    Qstable_name_of_class_instance = 
	    STATIC_SYMBOL("STABLE-NAME-OF-CLASS-INSTANCE",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qstable_subclass = STATIC_SYMBOL("STABLE-SUBCLASS",AB_package);
    Qstable_hierarchy = STATIC_SYMBOL("STABLE-HIERARCHY",AB_package);
    Qstable_not_subclass = STATIC_SYMBOL("STABLE-NOT-SUBCLASS",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qattribute_of_class = STATIC_SYMBOL("ATTRIBUTE-OF-CLASS",AB_package);
    Qclass_qualified_attribute_of_class = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-ATTRIBUTE-OF-CLASS",AB_package);
    Qclass_qualified_method = STATIC_SYMBOL("CLASS-QUALIFIED-METHOD",
	    AB_package);
    Qcached_attribute = STATIC_SYMBOL("CACHED-ATTRIBUTE",AB_package);
    Qprocedure_call = STATIC_SYMBOL("PROCEDURE-CALL",AB_package);
    Qremote_procedure_call = STATIC_SYMBOL("REMOTE-PROCEDURE-CALL",AB_package);
    Qstable_procedure_call = STATIC_SYMBOL("STABLE-PROCEDURE-CALL",AB_package);
    Qstable_remote_procedure_call = 
	    STATIC_SYMBOL("STABLE-REMOTE-PROCEDURE-CALL",AB_package);
    Qstable_compile_time_selected_method = 
	    STATIC_SYMBOL("STABLE-COMPILE-TIME-SELECTED-METHOD",AB_package);
    Qfunction_call = STATIC_SYMBOL("FUNCTION-CALL",AB_package);
    if (Inhibit_free_reference_recording == UNBOUND)
	Inhibit_free_reference_recording = Nil;
    string_constant_11 = STATIC_STRING("free reference recorder");
    string_constant_12 = 
	    STATIC_STRING("A reference of type ~a was badly formed: reference = ~a");
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    string_constant_13 = STATIC_STRING("~(~a: ~a~)");
    string_constant_14 = STATIC_STRING("~(~a: ~a of class ~a~)");
    string_constant_15 = STATIC_STRING("~(~a: ~a of type ~NT~)");
    string_constant_16 = STATIC_STRING("~(~a: ~a, constant: ~a~)");
    string_constant_17 = STATIC_STRING("item");
    string_constant_18 = STATIC_STRING("~(~a: ~a of ~a~)");
    string_constant_19 = STATIC_STRING("~(~a: ~NQ of ~a~)");
    string_constant_20 = STATIC_STRING("~(, from class: ~a~)");
    string_constant_21 = STATIC_STRING("~(, constant: ~a~)");
    string_constant_22 = STATIC_STRING("~(~a: ~a ~)");
    array_constant_9 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    string_constant_23 = 
	    STATIC_STRING("~(~a: call to ~a for first argument ~a selected ~a::~a~)");
    string_constant_24 = 
	    STATIC_STRING("~(~a: superior class ~a, subclass ~a~)");
    string_constant_25 = STATIC_STRING("~(unused ~a: ~a~)");
    array_constant_10 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qstable_name_of_type = STATIC_SYMBOL("STABLE-NAME-OF-TYPE",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,Qname_of_type,
	    Qstable_name_of_type,Qname_of_class_instance,
	    Qstable_name_of_class_instance);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qab_class,Qparameter);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qab_class,Qvariable);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,
	    list_constant_9);
    Qnext_stack_frame_var_location = 
	    STATIC_SYMBOL("NEXT-STACK-FRAME-VAR-LOCATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnext_stack_frame_var_location,
	    Next_stack_frame_var_location);
    record_system_variable(Qnext_stack_frame_var_location,Qcomp_utils,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qoutermost_stack_frame_var_binding_qm = 
	    STATIC_SYMBOL("OUTERMOST-STACK-FRAME-VAR-BINDING\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoutermost_stack_frame_var_binding_qm,
	    Outermost_stack_frame_var_binding_qm);
    record_system_variable(Qoutermost_stack_frame_var_binding_qm,
	    Qcomp_utils,Nil,Qnil,Qnil,Qnil,Qnil);
    Qstack_frame_vars_ok_in_procedure_qm = 
	    STATIC_SYMBOL("STACK-FRAME-VARS-OK-IN-PROCEDURE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_frame_vars_ok_in_procedure_qm,
	    Stack_frame_vars_ok_in_procedure_qm);
    record_system_variable(Qstack_frame_vars_ok_in_procedure_qm,
	    Qcomp_utils,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_26 = STATIC_STRING("~a~a~a~a");
    string_constant_27 = 
	    STATIC_STRING("Too many stack frame variables have been emitted from this compiled ");
    string_constant_28 = 
	    STATIC_STRING("item.  This item must be simplified to have fewer than 256 stack frame ");
    string_constant_29 = 
	    STATIC_STRING("variables, for example by making smaller expressions or by reducing the ");
    string_constant_30 = 
	    STATIC_STRING("size of a function, to be able to compile.");
    Qstack_frame_var = STATIC_SYMBOL("STACK-FRAME-VAR",AB_package);
    string_constant_31 = STATIC_STRING("stack argument registration");
    string_constant_32 = 
	    STATIC_STRING("The argument number ~a was less than zero, the minimum.");
    string_constant_33 = 
	    STATIC_STRING("The maximum number of arguments for a function is 256, attempting ~\n            to allocate ~a.");
    Qstack_arg = STATIC_SYMBOL("STACK-ARG",AB_package);
    Qmaximum_var_spot_index = STATIC_SYMBOL("MAXIMUM-VAR-SPOT-INDEX",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_var_spot_index,FIX((SI_Long)65535L));
    Qbits_in_var_spot_index = STATIC_SYMBOL("BITS-IN-VAR-SPOT-INDEX",
	    AB_package);
    SET_SYMBOL_VALUE(Qbits_in_var_spot_index,FIX((SI_Long)16L));
    Qmaximum_var_spot_local_index = 
	    STATIC_SYMBOL("MAXIMUM-VAR-SPOT-LOCAL-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_var_spot_local_index,FIX((SI_Long)1023L));
    Qbits_in_var_spot_local_index = 
	    STATIC_SYMBOL("BITS-IN-VAR-SPOT-LOCAL-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qbits_in_var_spot_local_index,FIX((SI_Long)10L));
    Qmaximum_var_spot_nesting = STATIC_SYMBOL("MAXIMUM-VAR-SPOT-NESTING",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_var_spot_nesting,FIX((SI_Long)63L));
    Qbits_in_var_spot_nesting = STATIC_SYMBOL("BITS-IN-VAR-SPOT-NESTING",
	    AB_package);
    SET_SYMBOL_VALUE(Qbits_in_var_spot_nesting,FIX((SI_Long)6L));
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qstack_frame_var,Qstack_arg);
    string_constant_34 = STATIC_STRING("type fetcher");
    string_constant_35 = 
	    STATIC_STRING("Invalid var-spot ~a given to var-spot-type.");
    Qg2_defstruct_structure_name_inlining_data_holder_g2_struct = 
	    STATIC_SYMBOL("INLINING-DATA-HOLDER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinlining_data_holder = STATIC_SYMBOL("INLINING-DATA-HOLDER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_inlining_data_holder_g2_struct,
	    Qinlining_data_holder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qinlining_data_holder,
	    Qg2_defstruct_structure_name_inlining_data_holder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_inlining_data_holder == UNBOUND)
	The_type_description_of_inlining_data_holder = Nil;
    string_constant_64 = 
	    STATIC_STRING("43Dy8m83j1y1n83j1y8n8k1l8n0000000kwk0k0");
    temp = The_type_description_of_inlining_data_holder;
    The_type_description_of_inlining_data_holder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_64));
    mutate_global_property(Qg2_defstruct_structure_name_inlining_data_holder_g2_struct,
	    The_type_description_of_inlining_data_holder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qinlining_data_holder,
	    The_type_description_of_inlining_data_holder,
	    Qtype_description_of_type);
    Qoutstanding_inlining_data_holder_count = 
	    STATIC_SYMBOL("OUTSTANDING-INLINING-DATA-HOLDER-COUNT",AB_package);
    Qinlining_data_holder_structure_memory_usage = 
	    STATIC_SYMBOL("INLINING-DATA-HOLDER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_65 = STATIC_STRING("1q83j1y8s83-a0y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_inlining_data_holder_count);
    push_optimized_constant(Qinlining_data_holder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_65));
    Qchain_of_available_inlining_data_holders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INLINING-DATA-HOLDERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_inlining_data_holders,
	    Chain_of_available_inlining_data_holders);
    record_system_variable(Qchain_of_available_inlining_data_holders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qinlining_data_holder_count = 
	    STATIC_SYMBOL("INLINING-DATA-HOLDER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinlining_data_holder_count,
	    Inlining_data_holder_count);
    record_system_variable(Qinlining_data_holder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_inlining_data_holders_vector == UNBOUND)
	Chain_of_available_inlining_data_holders_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qinlining_data_holder_structure_memory_usage,
	    STATIC_FUNCTION(inlining_data_holder_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_inlining_data_holder_count,
	    STATIC_FUNCTION(outstanding_inlining_data_holder_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_inlining_data_holder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_inlining_data_holder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qinlining_data_holder,
	    reclaim_structure_for_inlining_data_holder_1);
    if (Inlining_data == UNBOUND)
	Inlining_data = make_inlining_data_holder_1();
    string_constant_36 = STATIC_STRING("variable spot generator");
    string_constant_37 = 
	    STATIC_STRING("Invalid type ~a given to generate-new-variable-spot.");
    string_constant_38 = STATIC_STRING("variable index generator");
    string_constant_39 = 
	    STATIC_STRING("Attempted to generate a new variable in a null code body environment.");
    string_constant_40 = 
	    string_append2(STATIC_STRING("The maximum number of local variables, ~a, has been ~\n             exceeded.  You must reduce the number of local variables, the ~\n             complexity of the expressions, "),
	    STATIC_STRING("or the overall number of ~\n             expressions and statements in this item."));
    string_constant_41 = 
	    string_append2(STATIC_STRING("The maximum number of nestings with a procedure, ~a, has been ~\n             exceeded.  You must reduce the depth of do in parallel and on ~\n             error nesting within "),
	    STATIC_STRING("this procedure."));
    if (Missing_local_names_already_reported == UNBOUND)
	Missing_local_names_already_reported = Nil;
    if (Duplicate_local_names_already_reported == UNBOUND)
	Duplicate_local_names_already_reported = Nil;
    string_constant_42 = STATIC_STRING("the local name ~a is undefined");
    string_constant_43 = 
	    STATIC_STRING("the local name ~a is defined more than once");
    Maximum_stack_instruction_vector_length = FIX((SI_Long)16384L);
    Qg2_defstruct_structure_name_byte_code_stream_g2_struct = 
	    STATIC_SYMBOL("BYTE-CODE-STREAM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbyte_code_stream = STATIC_SYMBOL("BYTE-CODE-STREAM",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_byte_code_stream_g2_struct,
	    Qbyte_code_stream,Qab_name_of_unique_structure_type);
    mutate_global_property(Qbyte_code_stream,
	    Qg2_defstruct_structure_name_byte_code_stream_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_byte_code_stream == UNBOUND)
	The_type_description_of_byte_code_stream = Nil;
    string_constant_66 = 
	    STATIC_STRING("43Dy8m83fWy1n83fWy8n8k1l8n0000000ktk0k0");
    temp = The_type_description_of_byte_code_stream;
    The_type_description_of_byte_code_stream = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_66));
    mutate_global_property(Qg2_defstruct_structure_name_byte_code_stream_g2_struct,
	    The_type_description_of_byte_code_stream,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qbyte_code_stream,
	    The_type_description_of_byte_code_stream,
	    Qtype_description_of_type);
    Qoutstanding_byte_code_stream_count = 
	    STATIC_SYMBOL("OUTSTANDING-BYTE-CODE-STREAM-COUNT",AB_package);
    Qbyte_code_stream_structure_memory_usage = 
	    STATIC_SYMBOL("BYTE-CODE-STREAM-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_67 = STATIC_STRING("1q83fWy8s83-LAy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_byte_code_stream_count);
    push_optimized_constant(Qbyte_code_stream_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_67));
    Qchain_of_available_byte_code_streams = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BYTE-CODE-STREAMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_byte_code_streams,
	    Chain_of_available_byte_code_streams);
    record_system_variable(Qchain_of_available_byte_code_streams,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qbyte_code_stream_count = STATIC_SYMBOL("BYTE-CODE-STREAM-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_code_stream_count,Byte_code_stream_count);
    record_system_variable(Qbyte_code_stream_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_byte_code_streams_vector == UNBOUND)
	Chain_of_available_byte_code_streams_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbyte_code_stream_structure_memory_usage,
	    STATIC_FUNCTION(byte_code_stream_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_byte_code_stream_count,
	    STATIC_FUNCTION(outstanding_byte_code_stream_count,NIL,FALSE,0,0));
    reclaim_structure_for_byte_code_stream_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_byte_code_stream,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qbyte_code_stream,
	    reclaim_structure_for_byte_code_stream_1);
    string_constant_44 = STATIC_STRING("byte code emitter");
    string_constant_45 = STATIC_STRING("Non-byte ~a emitted into byte-codes.");
    string_constant_46 = 
	    STATIC_STRING("The byte codes in the instruction vector have exceeded the ~\n              maximum, ~a.  There are too many statements and expressions in ~\n              this source code.");
    Qjump_tag = STATIC_SYMBOL("JUMP-TAG",AB_package);
    Qtag = STATIC_SYMBOL("TAG",AB_package);
    Qaddress_resolution_point = STATIC_SYMBOL("ADDRESS-RESOLUTION-POINT",
	    AB_package);
    string_constant_47 = STATIC_STRING("byte code stream vector reader");
    string_constant_48 = 
	    STATIC_STRING("Unrecognized entry ~a in byte-code-stream-bytes.");
    Maximum_constant_vector_length = Maximum_managed_simple_vector_size;
    string_constant_49 = 
	    string_append2(STATIC_STRING("The maximum allowed number of constants, ~a, has been exceeded ~\n             while registering ~NE.    You must reduce the size or complexity ~\n             of the expression"),
	    STATIC_STRING("s and statements in this item."));
    string_constant_50 = 
	    string_append2(STATIC_STRING("The maximum allowed number of constants, ~a, has been ~\n                     exceeded while registering an internal constant.  You must ~\n                     reduce the size "),
	    STATIC_STRING("or complexity of the expressions and ~\n                     statements in this item."));
    Qavailable_stack_conses = STATIC_SYMBOL("AVAILABLE-STACK-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_conses,Available_stack_conses);
    Qstack_utils = STATIC_SYMBOL("STACK-UTILS",AB_package);
    record_system_variable(Qavailable_stack_conses,Qstack_utils,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_stack_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-STACK-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_conses_tail,
	    Available_stack_conses_tail);
    record_system_variable(Qavailable_stack_conses_tail,Qstack_utils,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_stack_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-STACK-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_conses_vector,
	    Available_stack_conses_vector);
    record_system_variable(Qavailable_stack_conses_vector,Qstack_utils,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qavailable_stack_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-STACK-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_conses_tail_vector,
	    Available_stack_conses_tail_vector);
    record_system_variable(Qavailable_stack_conses_tail_vector,
	    Qstack_utils,list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qstack_cons_counter_vector = STATIC_SYMBOL("STACK-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_cons_counter_vector,
	    Stack_cons_counter_vector);
    record_system_variable(Qstack_cons_counter_vector,Qstack_utils,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qstack_cons_counter = STATIC_SYMBOL("STACK-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_cons_counter,Stack_cons_counter);
    record_system_variable(Qstack_cons_counter,Qstack_utils,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_stack_conses = STATIC_SYMBOL("OUTSTANDING-STACK-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_stack_conses,
	    STATIC_FUNCTION(outstanding_stack_conses,NIL,FALSE,0,0));
    Qstack_cons_memory_usage = STATIC_SYMBOL("STACK-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qstack_cons_memory_usage,
	    STATIC_FUNCTION(stack_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_68 = STATIC_STRING("1q83-qay9k83-qZy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_stack_conses);
    push_optimized_constant(Qstack_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_68));
    Qstack = STATIC_SYMBOL("STACK",AB_package);
    Qstack_evaluators = STATIC_SYMBOL("STACK-EVALUATORS",AB_package);
    Stack_evaluators_prop = Qstack_evaluators;
    Qdispatch_instruction_number = 
	    STATIC_SYMBOL("DISPATCH-INSTRUCTION-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qdispatch_instruction_number,FIX((SI_Long)255L));
    Qmaximum_number_of_extended_inline_evaluators = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-EXTENDED-INLINE-EVALUATORS",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_extended_inline_evaluators,
	    FIX((SI_Long)250L));
    Qmaximum_number_of_in_line_evaluators = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-IN-LINE-EVALUATORS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_in_line_evaluators,FIX((SI_Long)106L));
    Qbase_in_line_evaluator_number = 
	    STATIC_SYMBOL("BASE-IN-LINE-EVALUATOR-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qbase_in_line_evaluator_number,FIX((SI_Long)150L));
    Qmaximum_number_of_funcalled_evaluators = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-FUNCALLED-EVALUATORS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_funcalled_evaluators,
	    FIX((SI_Long)200L));
    if (In_line_evaluator_array == UNBOUND) {
	gensymed_symbol = FIXNUM_ADD(Maximum_number_of_in_line_evaluators,
		Maximum_number_of_extended_inline_evaluators);
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
	In_line_evaluator_array = the_array;
    }
    if (Funcalled_evaluator_array == UNBOUND) {
	gensymed_symbol = Maximum_number_of_funcalled_evaluators;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	Funcalled_evaluator_array = the_array;
    }
    if (Funcalled_evaluator_functions == UNBOUND) {
	gensymed_symbol = Maximum_number_of_funcalled_evaluators;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	Funcalled_evaluator_functions = the_array;
    }
    if (Funcalled_evaluator_dispatch_type == UNBOUND) {
	gensymed_symbol = Maximum_number_of_funcalled_evaluators;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop_3:
	if (i >= ab_loop_bind_)
	    goto end_loop_3;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	Funcalled_evaluator_dispatch_type = the_array;
    }
    Qg2_defstruct_structure_name_stack_node_g2_struct = 
	    STATIC_SYMBOL("STACK-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstack_node = STATIC_SYMBOL("STACK-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_stack_node_g2_struct,
	    Qstack_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qstack_node,
	    Qg2_defstruct_structure_name_stack_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_stack_node == UNBOUND)
	The_type_description_of_stack_node = Nil;
    string_constant_69 = 
	    STATIC_STRING("43Dy8m83FAy1n83FAy8n8k1l8n0000001m1n8y83-5wy1m83aoy83-Day1m83=0y83Y5ykwk0k0");
    temp = The_type_description_of_stack_node;
    The_type_description_of_stack_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_69));
    mutate_global_property(Qg2_defstruct_structure_name_stack_node_g2_struct,
	    The_type_description_of_stack_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qstack_node,The_type_description_of_stack_node,
	    Qtype_description_of_type);
    Qoutstanding_stack_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-STACK-NODE-COUNT",AB_package);
    Qstack_node_structure_memory_usage = 
	    STATIC_SYMBOL("STACK-NODE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_70 = STATIC_STRING("1q83FAy8s83-qby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_stack_node_count);
    push_optimized_constant(Qstack_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_70));
    Qchain_of_available_stack_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-STACK-NODES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_stack_nodes,
	    Chain_of_available_stack_nodes);
    record_system_variable(Qchain_of_available_stack_nodes,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qstack_node_count = STATIC_SYMBOL("STACK-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_node_count,Stack_node_count);
    record_system_variable(Qstack_node_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_stack_nodes_vector == UNBOUND)
	Chain_of_available_stack_nodes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qstack_node_structure_memory_usage,
	    STATIC_FUNCTION(stack_node_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_stack_node_count,
	    STATIC_FUNCTION(outstanding_stack_node_count,NIL,FALSE,0,0));
    reclaim_structure_for_stack_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_stack_node,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qstack_node,
	    reclaim_structure_for_stack_node_1);
    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstack_node_instruction = STATIC_SYMBOL("STACK-NODE-INSTRUCTION",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_stack_node_instruction_g2_struct,
	    Qstack_node_instruction,Qab_name_of_unique_structure_type);
    mutate_global_property(Qstack_node_instruction,
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_stack_node_instruction == UNBOUND)
	The_type_description_of_stack_node_instruction = Nil;
    string_constant_71 = 
	    STATIC_STRING("43Dy8m83nNy1o83nNy83FAy8n8k1l83FAy0000001o1n8y83-5xy1m83aoy83-Dby1m8x83FAy1m83=0y83Y5y1m83My83-B6ykyk0k0");
    temp = The_type_description_of_stack_node_instruction;
    The_type_description_of_stack_node_instruction = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_71));
    mutate_global_property(Qg2_defstruct_structure_name_stack_node_instruction_g2_struct,
	    The_type_description_of_stack_node_instruction,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qstack_node_instruction,
	    The_type_description_of_stack_node_instruction,
	    Qtype_description_of_type);
    Qoutstanding_stack_node_instruction_count = 
	    STATIC_SYMBOL("OUTSTANDING-STACK-NODE-INSTRUCTION-COUNT",
	    AB_package);
    Qstack_node_instruction_structure_memory_usage = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_72 = STATIC_STRING("1q83nNy8s83-qcy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_stack_node_instruction_count);
    push_optimized_constant(Qstack_node_instruction_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_72));
    Qchain_of_available_stack_node_instructions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-STACK-NODE-INSTRUCTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_stack_node_instructions,
	    Chain_of_available_stack_node_instructions);
    record_system_variable(Qchain_of_available_stack_node_instructions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qstack_node_instruction_count = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_node_instruction_count,
	    Stack_node_instruction_count);
    record_system_variable(Qstack_node_instruction_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_stack_node_instructions_vector == UNBOUND)
	Chain_of_available_stack_node_instructions_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qstack_node_instruction_structure_memory_usage,
	    STATIC_FUNCTION(stack_node_instruction_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_stack_node_instruction_count,
	    STATIC_FUNCTION(outstanding_stack_node_instruction_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_stack_node_instruction_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_stack_node_instruction,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qstack_node_instruction,
	    reclaim_structure_for_stack_node_instruction_1);
    Qname_reference = STATIC_SYMBOL("NAME-REFERENCE",AB_package);
    Qpush_cached_item = STATIC_SYMBOL("PUSH-CACHED-ITEM",AB_package);
    Qensure_type = STATIC_SYMBOL("ENSURE-TYPE",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qab_class,Qprocedure);
    Kinner_block_not_inlineable = 
	    STATIC_SYMBOL("INNER-BLOCK-NOT-INLINEABLE",Pkeyword);
    Kcross_module_violation = STATIC_SYMBOL("CROSS-MODULE-VIOLATION",Pkeyword);
    if (Compiled_item_being_analyzed_started_out_incomplete_qm == UNBOUND)
	Compiled_item_being_analyzed_started_out_incomplete_qm = Nil;
    Qitem_depends_on_modified_stable_item = 
	    STATIC_SYMBOL("ITEM-DEPENDS-ON-MODIFIED-STABLE-ITEM",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qitem_depends_on_unstable_heirarchy = 
	    STATIC_SYMBOL("ITEM-DEPENDS-ON-UNSTABLE-HEIRARCHY",AB_package);
    Qitem_depends_on_invalid_inlining = 
	    STATIC_SYMBOL("ITEM-DEPENDS-ON-INVALID-INLINING",AB_package);
    Qitem_no_longer_dependent = STATIC_SYMBOL("ITEM-NO-LONGER-DEPENDENT",
	    AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)57344L);
    Qmd5_identifier_qm = STATIC_SYMBOL("MD5-IDENTIFIER\?",AB_package);
    Qprocedure_definition = STATIC_SYMBOL("PROCEDURE-DEFINITION",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qname_of_defined_class = STATIC_SYMBOL("NAME-OF-DEFINED-CLASS",AB_package);
    Qdirect_superiors_of_defined_class = 
	    STATIC_SYMBOL("DIRECT-SUPERIORS-OF-DEFINED-CLASS",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qstack_special_form_converter = 
	    STATIC_SYMBOL("STACK-SPECIAL-FORM-CONVERTER",AB_package);
    Stack_special_form_converter_prop = Qstack_special_form_converter;
    Qpreferred_instruction_chooser = 
	    STATIC_SYMBOL("PREFERRED-INSTRUCTION-CHOOSER",AB_package);
    Preferred_instruction_chooser_prop = Qpreferred_instruction_chooser;
    Qstack_node_instruction_emitter = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-EMITTER",AB_package);
    Stack_node_instruction_emitter_prop = Qstack_node_instruction_emitter;
    Qstack_node_instruction_reclaimer = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-RECLAIMER",AB_package);
    Stack_node_instruction_reclaimer_prop = Qstack_node_instruction_reclaimer;
    Qstack_node_instruction_extra_info_copier = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-EXTRA-INFO-COPIER",
	    AB_package);
    Stack_node_instruction_extra_info_copier_prop = 
	    Qstack_node_instruction_extra_info_copier;
    Qexpiration_special_form_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SPECIAL-FORM-OPERATOR-P",AB_package);
    Expiration_special_form_operator_p_prop = 
	    Qexpiration_special_form_operator_p;
    Qexpiration_source_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SOURCE-OPERATOR-P",AB_package);
    Expiration_source_operator_p_prop = Qexpiration_source_operator_p;
    Qprocedure_statement_writer = 
	    STATIC_SYMBOL("PROCEDURE-STATEMENT-WRITER",AB_package);
    Procedure_statement_writer_prop = Qprocedure_statement_writer;
    Qprocedure_statement_compiler = 
	    STATIC_SYMBOL("PROCEDURE-STATEMENT-COMPILER",AB_package);
    Procedure_statement_compiler_prop = Qprocedure_statement_compiler;
    Qaction_compiler = STATIC_SYMBOL("ACTION-COMPILER",AB_package);
    Action_compiler_prop = Qaction_compiler;
    Qaction_method_compiler = STATIC_SYMBOL("ACTION-METHOD-COMPILER",
	    AB_package);
    Action_method_compiler_prop = Qaction_method_compiler;
    Qpseudo_instruction_byte_code_emitter = 
	    STATIC_SYMBOL("PSEUDO-INSTRUCTION-BYTE-CODE-EMITTER",AB_package);
    Pseudo_instruction_byte_code_emitter_prop = 
	    Qpseudo_instruction_byte_code_emitter;
    Qcurrent_computation_activity = 
	    STATIC_SYMBOL("CURRENT-COMPUTATION-ACTIVITY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_computation_activity,
	    Current_computation_activity);
    record_system_variable(Qcurrent_computation_activity,Qcomp_utils,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    array_constant_15 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)68L));
    string_constant_73 = STATIC_STRING("default");
    string_constant_74 = STATIC_STRING("assign local variable statement");
    string_constant_75 = STATIC_STRING("return statement");
    string_constant_76 = STATIC_STRING("if-then statement");
    string_constant_77 = STATIC_STRING("if-then-else statement");
    string_constant_78 = STATIC_STRING("case statement");
    string_constant_79 = STATIC_STRING("repeat statement");
    string_constant_80 = STATIC_STRING("exit if statement");
    string_constant_81 = STATIC_STRING("for statement");
    string_constant_82 = STATIC_STRING("for in parallel statement");
    string_constant_83 = 
	    STATIC_STRING("for in parallel until one completes statement");
    string_constant_84 = STATIC_STRING("call statement");
    string_constant_85 = STATIC_STRING("system call statement");
    string_constant_86 = STATIC_STRING("allow other processing statement");
    string_constant_87 = STATIC_STRING("collect data statement");
    string_constant_88 = STATIC_STRING("do in parallel statement");
    string_constant_89 = 
	    STATIC_STRING("do in parallel until one completes statement");
    string_constant_90 = STATIC_STRING("wait for interval statement");
    string_constant_91 = STATIC_STRING("wait until statement");
    string_constant_92 = STATIC_STRING("wait until event statement");
    string_constant_93 = STATIC_STRING("on error statement");
    string_constant_94 = STATIC_STRING("signal error statement");
    string_constant_95 = STATIC_STRING("start rpc action");
    string_constant_96 = STATIC_STRING("start action");
    string_constant_97 = STATIC_STRING("conclude action");
    string_constant_98 = STATIC_STRING("conclude has no current value action");
    string_constant_99 = STATIC_STRING("conclude has no value action");
    string_constant_100 = STATIC_STRING("move action");
    string_constant_101 = STATIC_STRING("rotate action");
    string_constant_102 = STATIC_STRING("focus action");
    string_constant_103 = STATIC_STRING("invoke action");
    string_constant_104 = STATIC_STRING("change color action");
    string_constant_105 = STATIC_STRING("show action");
    string_constant_106 = STATIC_STRING("hide action");
    string_constant_107 = STATIC_STRING("activate action");
    string_constant_108 = STATIC_STRING("deactivate action");
    string_constant_109 = STATIC_STRING("halt action");
    string_constant_110 = STATIC_STRING("set action");
    string_constant_111 = STATIC_STRING("inform action");
    string_constant_112 = STATIC_STRING("conclude relation action");
    string_constant_113 = STATIC_STRING("conclude not related action");
    string_constant_114 = STATIC_STRING("create action");
    string_constant_115 = STATIC_STRING("delete action");
    string_constant_116 = STATIC_STRING("transfer action");
    string_constant_117 = STATIC_STRING("change action");
    string_constant_118 = STATIC_STRING("change text action");
    string_constant_119 = STATIC_STRING("change array or list element action");
    string_constant_120 = STATIC_STRING("insert action");
    string_constant_121 = STATIC_STRING("remove action");
    string_constant_122 = STATIC_STRING("nupec synchronize action");
    string_constant_123 = STATIC_STRING("create explanation action");
    string_constant_124 = STATIC_STRING("update action");
    string_constant_125 = STATIC_STRING("create connection action");
    string_constant_126 = STATIC_STRING("abort action");
    string_constant_127 = STATIC_STRING("shut down G2 action");
    string_constant_128 = STATIC_STRING("reset kb action");
    string_constant_129 = STATIC_STRING("pause kb action");
    string_constant_130 = STATIC_STRING("create by cloning action");
    string_constant_131 = STATIC_STRING("make permanent action");
    string_constant_132 = STATIC_STRING("make transient action");
    string_constant_133 = STATIC_STRING("make subworkspace action");
    string_constant_134 = STATIC_STRING("print action");
    string_constant_135 = STATIC_STRING("start kb action");
    string_constant_136 = STATIC_STRING("resume kb action");
    string_constant_137 = STATIC_STRING("begin rule actions");
    string_constant_138 = STATIC_STRING("call next method statement");
    string_constant_139 = STATIC_STRING("call action");
    string_constant_140 = STATIC_STRING("call rpc action");
    ISASET_1(array_constant_15,(SI_Long)0L,string_constant_73);
    ISASET_1(array_constant_15,(SI_Long)1L,string_constant_74);
    ISASET_1(array_constant_15,(SI_Long)2L,string_constant_75);
    ISASET_1(array_constant_15,(SI_Long)3L,string_constant_76);
    ISASET_1(array_constant_15,(SI_Long)4L,string_constant_77);
    ISASET_1(array_constant_15,(SI_Long)5L,string_constant_78);
    ISASET_1(array_constant_15,(SI_Long)6L,string_constant_79);
    ISASET_1(array_constant_15,(SI_Long)7L,string_constant_80);
    ISASET_1(array_constant_15,(SI_Long)8L,string_constant_81);
    ISASET_1(array_constant_15,(SI_Long)9L,string_constant_82);
    ISASET_1(array_constant_15,(SI_Long)10L,string_constant_83);
    ISASET_1(array_constant_15,(SI_Long)11L,string_constant_84);
    ISASET_1(array_constant_15,(SI_Long)12L,string_constant_85);
    ISASET_1(array_constant_15,(SI_Long)13L,string_constant_86);
    ISASET_1(array_constant_15,(SI_Long)14L,string_constant_87);
    ISASET_1(array_constant_15,(SI_Long)15L,string_constant_88);
    ISASET_1(array_constant_15,(SI_Long)16L,string_constant_89);
    ISASET_1(array_constant_15,(SI_Long)17L,string_constant_90);
    ISASET_1(array_constant_15,(SI_Long)18L,string_constant_91);
    ISASET_1(array_constant_15,(SI_Long)19L,string_constant_92);
    ISASET_1(array_constant_15,(SI_Long)20L,string_constant_93);
    ISASET_1(array_constant_15,(SI_Long)21L,string_constant_94);
    ISASET_1(array_constant_15,(SI_Long)22L,string_constant_95);
    ISASET_1(array_constant_15,(SI_Long)23L,string_constant_96);
    ISASET_1(array_constant_15,(SI_Long)24L,string_constant_97);
    ISASET_1(array_constant_15,(SI_Long)25L,string_constant_98);
    ISASET_1(array_constant_15,(SI_Long)26L,string_constant_99);
    ISASET_1(array_constant_15,(SI_Long)27L,string_constant_100);
    ISASET_1(array_constant_15,(SI_Long)28L,string_constant_101);
    ISASET_1(array_constant_15,(SI_Long)29L,string_constant_102);
    ISASET_1(array_constant_15,(SI_Long)30L,string_constant_103);
    ISASET_1(array_constant_15,(SI_Long)31L,string_constant_104);
    ISASET_1(array_constant_15,(SI_Long)32L,string_constant_105);
    ISASET_1(array_constant_15,(SI_Long)33L,string_constant_106);
    ISASET_1(array_constant_15,(SI_Long)34L,string_constant_107);
    ISASET_1(array_constant_15,(SI_Long)35L,string_constant_108);
    ISASET_1(array_constant_15,(SI_Long)36L,string_constant_109);
    ISASET_1(array_constant_15,(SI_Long)37L,string_constant_110);
    ISASET_1(array_constant_15,(SI_Long)38L,string_constant_111);
    ISASET_1(array_constant_15,(SI_Long)39L,string_constant_112);
    ISASET_1(array_constant_15,(SI_Long)40L,string_constant_113);
    ISASET_1(array_constant_15,(SI_Long)41L,string_constant_114);
    ISASET_1(array_constant_15,(SI_Long)42L,string_constant_115);
    ISASET_1(array_constant_15,(SI_Long)43L,string_constant_116);
    ISASET_1(array_constant_15,(SI_Long)44L,string_constant_117);
    ISASET_1(array_constant_15,(SI_Long)45L,string_constant_118);
    ISASET_1(array_constant_15,(SI_Long)46L,string_constant_119);
    ISASET_1(array_constant_15,(SI_Long)47L,string_constant_120);
    ISASET_1(array_constant_15,(SI_Long)48L,string_constant_121);
    ISASET_1(array_constant_15,(SI_Long)49L,string_constant_122);
    ISASET_1(array_constant_15,(SI_Long)50L,string_constant_123);
    ISASET_1(array_constant_15,(SI_Long)51L,string_constant_124);
    ISASET_1(array_constant_15,(SI_Long)52L,string_constant_125);
    ISASET_1(array_constant_15,(SI_Long)53L,string_constant_126);
    ISASET_1(array_constant_15,(SI_Long)54L,string_constant_127);
    ISASET_1(array_constant_15,(SI_Long)55L,string_constant_128);
    ISASET_1(array_constant_15,(SI_Long)56L,string_constant_129);
    ISASET_1(array_constant_15,(SI_Long)57L,string_constant_130);
    ISASET_1(array_constant_15,(SI_Long)58L,string_constant_131);
    ISASET_1(array_constant_15,(SI_Long)59L,string_constant_132);
    ISASET_1(array_constant_15,(SI_Long)60L,string_constant_133);
    ISASET_1(array_constant_15,(SI_Long)61L,string_constant_134);
    ISASET_1(array_constant_15,(SI_Long)62L,string_constant_135);
    ISASET_1(array_constant_15,(SI_Long)63L,string_constant_136);
    ISASET_1(array_constant_15,(SI_Long)64L,string_constant_137);
    ISASET_1(array_constant_15,(SI_Long)65L,string_constant_138);
    ISASET_1(array_constant_15,(SI_Long)66L,string_constant_139);
    ISASET_1(array_constant_15,(SI_Long)67L,string_constant_140);
    Registered_activities_array = array_constant_15;
    array_constant_12 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)57344L);
    string_constant_51 = STATIC_STRING(" at program counter ~a ");
    Qg2_defstruct_structure_name_computation_instance_g2_struct = 
	    STATIC_SYMBOL("COMPUTATION-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcomputation_instance = STATIC_SYMBOL("COMPUTATION-INSTANCE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_computation_instance_g2_struct,
	    Qcomputation_instance,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcomputation_instance,
	    Qg2_defstruct_structure_name_computation_instance_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_computation_instance == UNBOUND)
	The_type_description_of_computation_instance = Nil;
    string_constant_141 = 
	    STATIC_STRING("43Dy8m830Ey1n830Ey8n8k1l8n0000000ksk0k0");
    temp = The_type_description_of_computation_instance;
    The_type_description_of_computation_instance = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_141));
    mutate_global_property(Qg2_defstruct_structure_name_computation_instance_g2_struct,
	    The_type_description_of_computation_instance,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcomputation_instance,
	    The_type_description_of_computation_instance,
	    Qtype_description_of_type);
    Qoutstanding_computation_instance_count = 
	    STATIC_SYMBOL("OUTSTANDING-COMPUTATION-INSTANCE-COUNT",AB_package);
    Qcomputation_instance_structure_memory_usage = 
	    STATIC_SYMBOL("COMPUTATION-INSTANCE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_142 = STATIC_STRING("1q830Ey8s83-Nay09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_computation_instance_count);
    push_optimized_constant(Qcomputation_instance_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_142));
    Qchain_of_available_computation_instances = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-COMPUTATION-INSTANCES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_computation_instances,
	    Chain_of_available_computation_instances);
    record_system_variable(Qchain_of_available_computation_instances,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcomputation_instance_count = 
	    STATIC_SYMBOL("COMPUTATION-INSTANCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcomputation_instance_count,
	    Computation_instance_count);
    record_system_variable(Qcomputation_instance_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_computation_instances_vector == UNBOUND)
	Chain_of_available_computation_instances_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcomputation_instance_structure_memory_usage,
	    STATIC_FUNCTION(computation_instance_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_computation_instance_count,
	    STATIC_FUNCTION(outstanding_computation_instance_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_computation_instance_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_computation_instance,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcomputation_instance,
	    reclaim_structure_for_computation_instance_1);
    string_constant_52 = STATIC_STRING("disabled");
    string_constant_53 = STATIC_STRING("not active");
    string_constant_54 = STATIC_STRING("inside a breakpoint");
    string_constant_55 = STATIC_STRING("in an unknown state");
    Qnote_runs_while_inactive_change = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE",AB_package);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    list_constant_10 = STATIC_CONS(Qkb_frame,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qnote_runs_while_inactive_change,
	    list_constant_10,Qgeneric_method_lambda_list);
    Qnote_may_refer_to_inactive_items_change = 
	    STATIC_SYMBOL("NOTE-MAY-REFER-TO-INACTIVE-ITEMS-CHANGE",
	    AB_package);
    mutate_global_property(Qnote_may_refer_to_inactive_items_change,
	    list_constant_10,Qgeneric_method_lambda_list);
}
