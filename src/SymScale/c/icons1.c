/* icons1.c
 * Input file:  icons1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "icons1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_icon_editor_conses, Qavailable_icon_editor_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_icon_editor_conses_tail, Qavailable_icon_editor_conses_tail);

Object Available_icon_editor_conses_vector = UNBOUND;

Object Available_icon_editor_conses_tail_vector = UNBOUND;

Object Icon_editor_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_cons_counter, Qicon_editor_cons_counter);

/* OUTSTANDING-ICON-EDITOR-CONSES */
Object outstanding_icon_editor_conses()
{
    Object temp;

    x_note_fn_call(232,0);
    temp = FIXNUM_MINUS(Icon_editor_cons_counter,
	    length(Available_icon_editor_conses));
    return VALUES_1(temp);
}

/* ICON-EDITOR-CONS-MEMORY-USAGE */
Object icon_editor_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(232,1);
    temp = FIXNUM_TIMES(Icon_editor_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-ICON-EDITOR-CONS-POOL */
Object replenish_icon_editor_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(232,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qicon_editor_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icon_editor_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icon_editor_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_icon_editor_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Icon_editor_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qicon_editor;        /* icon-editor */

/* ICON-EDITOR-CONS-1 */
Object icon_editor_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(232,3);
    new_cons = ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_icon_editor_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icon_editor_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_icon_editor_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-ICON-EDITOR-LIST-POOL */
Object replenish_icon_editor_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(232,4);
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
    if (ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icon_editor_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icon_editor_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_icon_editor_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qicon_editor_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-ICON-EDITOR-LIST-1 */
Object make_icon_editor_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(232,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_icon_editor_conses_vector,
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
	replenish_icon_editor_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_icon_editor_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_icon_editor_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icon_editor_conses_tail_vector;
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

/* ICON-EDITOR-LIST-2 */
Object icon_editor_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icon_editor_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicon_editor);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icon_editor_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icon_editor_conses_tail_vector;
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

/* ICON-EDITOR-LIST-3 */
Object icon_editor_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icon_editor_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicon_editor);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icon_editor_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icon_editor_conses_tail_vector;
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

/* ICON-EDITOR-LIST-4 */
Object icon_editor_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icon_editor_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicon_editor);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icon_editor_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icon_editor_conses_tail_vector;
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

/* ICON-EDITOR-LIST-TRACE-HOOK */
Object icon_editor_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(232,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-ICON-EDITOR-CONSES-1 */
Object copy_tree_using_icon_editor_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(232,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icon_editor_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icon_editor_cons_pool();
	temp_1 = copy_tree_using_icon_editor_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icon_editor_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icon_editor_cons_pool();
	temp_1 = 
		copy_tree_using_icon_editor_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
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

/* COPY-LIST-USING-ICON-EDITOR-CONSES-1 */
Object copy_list_using_icon_editor_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(232,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icon_editor_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icon_editor_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icon_editor_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icon_editor_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
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

/* RECLAIM-ICON-EDITOR-CONS-1 */
Object reclaim_icon_editor_cons_1(icon_editor_cons)
    Object icon_editor_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(232,12);
    inline_note_reclaim_cons(icon_editor_cons,Qicon_editor);
    if (ISVREF(Available_icon_editor_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_icon_editor_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = icon_editor_cons;
	temp = Available_icon_editor_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icon_editor_cons;
    }
    else {
	temp = Available_icon_editor_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icon_editor_cons;
	temp = Available_icon_editor_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icon_editor_cons;
    }
    M_CDR(icon_editor_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ICON-EDITOR-LIST-1 */
Object reclaim_icon_editor_list_1(icon_editor_list)
    Object icon_editor_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(232,13);
    if (icon_editor_list) {
	last_1 = icon_editor_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qicon_editor);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qicon_editor);
	if (ISVREF(Available_icon_editor_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_icon_editor_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = icon_editor_list;
	    temp = Available_icon_editor_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_icon_editor_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = icon_editor_list;
	    temp = Available_icon_editor_conses_tail_vector;
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

/* RECLAIM-ICON-EDITOR-LIST*-1 */
Object reclaim_icon_editor_list_star_1(icon_editor_list)
    Object icon_editor_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(232,14);
    if (CONSP(icon_editor_list)) {
	temp = last(icon_editor_list,_);
	M_CDR(temp) = Nil;
	if (icon_editor_list) {
	    last_1 = icon_editor_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qicon_editor);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qicon_editor);
	    if (ISVREF(Available_icon_editor_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icon_editor_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = icon_editor_list;
		temp = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_icon_editor_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = icon_editor_list;
		temp = Available_icon_editor_conses_tail_vector;
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

/* RECLAIM-ICON-EDITOR-TREE-1 */
Object reclaim_icon_editor_tree_1(tree)
    Object tree;
{
    Object e, e2, icon_editor_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(232,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_icon_editor_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		icon_editor_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(icon_editor_cons,Qicon_editor);
		if (EQ(icon_editor_cons,e))
		    goto end_1;
		else if ( !TRUEP(icon_editor_cons))
		    goto end_1;
		else
		    icon_editor_cons = CDR(icon_editor_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_icon_editor_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icon_editor_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_icon_editor_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_icon_editor_conses_tail_vector;
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

/* DELETE-ICON-EDITOR-ELEMENT-1 */
Object delete_icon_editor_element_1(element,icon_editor_list)
    Object element, icon_editor_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(232,16);
    if (icon_editor_list) {
	if (EQ(element,M_CAR(icon_editor_list))) {
	    temp = CDR(icon_editor_list);
	    inline_note_reclaim_cons(icon_editor_list,Qicon_editor);
	    if (ISVREF(Available_icon_editor_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_icon_editor_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = icon_editor_list;
		temp_1 = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icon_editor_list;
	    }
	    else {
		temp_1 = Available_icon_editor_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icon_editor_list;
		temp_1 = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icon_editor_list;
	    }
	    M_CDR(icon_editor_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = icon_editor_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qicon_editor);
		if (ISVREF(Available_icon_editor_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_icon_editor_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_icon_editor_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_icon_editor_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_icon_editor_conses_tail_vector;
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
	    temp = icon_editor_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-ICON-EDITOR-CONS-1 */
Object delete_icon_editor_cons_1(icon_editor_cons,icon_editor_list)
    Object icon_editor_cons, icon_editor_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(232,17);
    if (EQ(icon_editor_cons,icon_editor_list))
	temp = CDR(icon_editor_list);
    else {
	l_trailer_qm = Nil;
	l = icon_editor_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,icon_editor_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = icon_editor_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_icon_editor_cons_1(icon_editor_cons);
    return VALUES_1(temp);
}

/* COPY-TREE-INCLUDING-LEAVES-USING-ICON-EDITOR-CONSES */
Object copy_tree_including_leaves_using_icon_editor_conses(tree_qm)
    Object tree_qm;
{
    Object temp, new_list, last_new_cons, current_copy_position, cdr_new_value;

    x_note_fn_call(232,18);
    if (text_string_p(tree_qm))
	temp = copy_text_string(tree_qm);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(tree_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tree_qm)) == (SI_Long)1L)
	temp = copy_managed_float(tree_qm);
    else if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	temp = 
		copy_tree_including_leaves_using_icon_editor_conses(CAR(tree_qm));
	new_list = icon_editor_cons_1(temp,CDR(tree_qm));
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	temp = 
		copy_tree_including_leaves_using_icon_editor_conses(CAR(current_copy_position));
	cdr_new_value = icon_editor_cons_1(temp,CDR(current_copy_position));
	M_CDR(last_new_cons) = cdr_new_value;
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

/* REVERSE-USING-ICON-EDITOR-CONSES */
Object reverse_using_icon_editor_conses(list_1)
    Object list_1;
{
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object reversed_list, element, ab_loop_list_;

    x_note_fn_call(232,19);
    if (list_1) {
	new_cons = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_icon_editor_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icon_editor_cons_pool();
	temp = CAR(list_1);
	M_CAR(gensymed_symbol) = temp;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
	reversed_list = gensymed_symbol;
	element = Nil;
	ab_loop_list_ = CDR(list_1);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_cons = ISVREF(Available_icon_editor_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_icon_editor_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icon_editor_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_icon_editor_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icon_editor_cons_pool();
	M_CAR(gensymed_symbol) = element;
	M_CDR(gensymed_symbol) = reversed_list;
	inline_note_allocate_cons(gensymed_symbol,Qicon_editor);
	reversed_list = gensymed_symbol;
	goto next_loop;
      end_loop:
	return VALUES_1(reversed_list);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_layer_box = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_layer_boxs, Qchain_of_available_layer_boxs);

DEFINE_VARIABLE_WITH_SYMBOL(Layer_box_count, Qlayer_box_count);

Object Chain_of_available_layer_boxs_vector = UNBOUND;

/* LAYER-BOX-STRUCTURE-MEMORY-USAGE */
Object layer_box_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,20);
    temp = Layer_box_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)21L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LAYER-BOX-COUNT */
Object outstanding_layer_box_count()
{
    Object def_structure_layer_box_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,21);
    gensymed_symbol = IFIX(Layer_box_count);
    def_structure_layer_box_variable = Chain_of_available_layer_boxs;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_layer_box_variable))
	goto end_loop;
    def_structure_layer_box_variable = 
	    ISVREF(def_structure_layer_box_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LAYER-BOX-1 */
Object reclaim_layer_box_1(layer_box)
    Object layer_box;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(232,22);
    inline_note_reclaim_cons(layer_box,Nil);
    structure_being_reclaimed = layer_box;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(layer_box,(SI_Long)4L));
      SVREF(layer_box,FIX((SI_Long)4L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_layer_boxs_vector,
	    IFIX(Current_thread_index));
    SVREF(layer_box,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_layer_boxs_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = layer_box;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LAYER-BOX */
Object reclaim_structure_for_layer_box(layer_box)
    Object layer_box;
{
    x_note_fn_call(232,23);
    return reclaim_layer_box_1(layer_box);
}

static Object Qg2_defstruct_structure_name_layer_box_g2_struct;  /* g2-defstruct-structure-name::layer-box-g2-struct */

/* MAKE-PERMANENT-LAYER-BOX-STRUCTURE-INTERNAL */
Object make_permanent_layer_box_structure_internal()
{
    Object def_structure_layer_box_variable, defstruct_g2_layer_box_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,24);
    def_structure_layer_box_variable = Nil;
    atomic_incff_symval(Qlayer_box_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_layer_box_variable = Nil;
	gensymed_symbol = (SI_Long)21L;
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
	defstruct_g2_layer_box_variable = the_array;
	SVREF(defstruct_g2_layer_box_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_layer_box_g2_struct;
	def_structure_layer_box_variable = defstruct_g2_layer_box_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_layer_box_variable);
}

/* MAKE-LAYER-BOX-1 */
Object make_layer_box_1(layer_box_border_icon,layer_box_text_for_label,
	    layer_box_layer_icon,layer_box_reference_serial_number)
    Object layer_box_border_icon, layer_box_text_for_label;
    Object layer_box_layer_icon, layer_box_reference_serial_number;
{
    Object def_structure_layer_box_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,25);
    def_structure_layer_box_variable = 
	    ISVREF(Chain_of_available_layer_boxs_vector,
	    IFIX(Current_thread_index));
    if (def_structure_layer_box_variable) {
	svref_arg_1 = Chain_of_available_layer_boxs_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_layer_box_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_layer_box_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_layer_box_g2_struct;
    }
    else
	def_structure_layer_box_variable = 
		make_permanent_layer_box_structure_internal();
    inline_note_allocate_cons(def_structure_layer_box_variable,Nil);
    SVREF(def_structure_layer_box_variable,FIX((SI_Long)1L)) = 
	    layer_box_border_icon;
    SVREF(def_structure_layer_box_variable,FIX((SI_Long)2L)) = 
	    layer_box_text_for_label;
    SVREF(def_structure_layer_box_variable,FIX((SI_Long)3L)) = 
	    layer_box_layer_icon;
    SVREF(def_structure_layer_box_variable,FIX((SI_Long)4L)) = 
	    layer_box_reference_serial_number;
    ISVREF(def_structure_layer_box_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    ISVREF(def_structure_layer_box_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_layer_box_variable);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* DELETE-LAYER-BOX */
Object delete_layer_box(layer_box)
    Object layer_box;
{
    Object serial_number, icon, x2, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(232,26);
    serial_number = ISVREF(layer_box,(SI_Long)4L);
    icon = Nil;
    icon = ISVREF(layer_box,(SI_Long)3L);
    if (SIMPLE_VECTOR_P(icon) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icon)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(icon,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(icon,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(icon,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(icon) ? EQ(ISVREF(icon,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	delete_frame(icon);
    icon = ISVREF(layer_box,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(icon) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icon)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(icon,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(icon,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(icon,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(icon) ? EQ(ISVREF(icon,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	delete_frame(icon);
    icon = ISVREF(layer_box,(SI_Long)2L);
    if (SIMPLE_VECTOR_P(icon) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icon)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(icon,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(icon,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(icon,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(icon) ? EQ(ISVREF(icon,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	delete_frame(icon);
    return reclaim_layer_box_1(layer_box);
}

Object The_type_description_of_icon_editor_translator = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_editor_translators, Qchain_of_available_icon_editor_translators);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_translator_count, Qicon_editor_translator_count);

Object Chain_of_available_icon_editor_translators_vector = UNBOUND;

/* ICON-EDITOR-TRANSLATOR-STRUCTURE-MEMORY-USAGE */
Object icon_editor_translator_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,27);
    temp = Icon_editor_translator_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-EDITOR-TRANSLATOR-COUNT */
Object outstanding_icon_editor_translator_count()
{
    Object def_structure_icon_editor_translator_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,28);
    gensymed_symbol = IFIX(Icon_editor_translator_count);
    def_structure_icon_editor_translator_variable = 
	    Chain_of_available_icon_editor_translators;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_editor_translator_variable))
	goto end_loop;
    def_structure_icon_editor_translator_variable = 
	    ISVREF(def_structure_icon_editor_translator_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-EDITOR-TRANSLATOR-1 */
Object reclaim_icon_editor_translator_1(icon_editor_translator)
    Object icon_editor_translator;
{
    Object temp, svref_arg_2;

    x_note_fn_call(232,29);
    inline_note_reclaim_cons(icon_editor_translator,Nil);
    temp = ISVREF(Chain_of_available_icon_editor_translators_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_editor_translator,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_editor_translators_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_editor_translator;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-EDITOR-TRANSLATOR */
Object reclaim_structure_for_icon_editor_translator(icon_editor_translator)
    Object icon_editor_translator;
{
    x_note_fn_call(232,30);
    return reclaim_icon_editor_translator_1(icon_editor_translator);
}

static Object Qg2_defstruct_structure_name_icon_editor_translator_g2_struct;  /* g2-defstruct-structure-name::icon-editor-translator-g2-struct */

/* MAKE-PERMANENT-ICON-EDITOR-TRANSLATOR-STRUCTURE-INTERNAL */
Object make_permanent_icon_editor_translator_structure_internal()
{
    Object def_structure_icon_editor_translator_variable;
    Object defstruct_g2_icon_editor_translator_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,31);
    def_structure_icon_editor_translator_variable = Nil;
    atomic_incff_symval(Qicon_editor_translator_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_editor_translator_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_icon_editor_translator_variable = the_array;
	SVREF(defstruct_g2_icon_editor_translator_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_translator_g2_struct;
	def_structure_icon_editor_translator_variable = 
		defstruct_g2_icon_editor_translator_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_editor_translator_variable);
}

/* MAKE-ICON-EDITOR-TRANSLATOR-1 */
Object make_icon_editor_translator_1()
{
    Object def_structure_icon_editor_translator_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(232,32);
    def_structure_icon_editor_translator_variable = 
	    ISVREF(Chain_of_available_icon_editor_translators_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_editor_translator_variable) {
	svref_arg_1 = Chain_of_available_icon_editor_translators_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_icon_editor_translator_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_editor_translator_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_translator_g2_struct;
    }
    else
	def_structure_icon_editor_translator_variable = 
		make_permanent_icon_editor_translator_structure_internal();
    inline_note_allocate_cons(def_structure_icon_editor_translator_variable,
	    Nil);
    ISVREF(def_structure_icon_editor_translator_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_icon_editor_translator_variable,FIX((SI_Long)2L)) 
	    = Nil;
    return VALUES_1(def_structure_icon_editor_translator_variable);
}

Object The_type_description_of_icon_editor_engine = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_editor_engines, Qchain_of_available_icon_editor_engines);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_engine_count, Qicon_editor_engine_count);

Object Chain_of_available_icon_editor_engines_vector = UNBOUND;

/* ICON-EDITOR-ENGINE-STRUCTURE-MEMORY-USAGE */
Object icon_editor_engine_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,33);
    temp = Icon_editor_engine_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)18L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-EDITOR-ENGINE-COUNT */
Object outstanding_icon_editor_engine_count()
{
    Object def_structure_icon_editor_engine_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,34);
    gensymed_symbol = IFIX(Icon_editor_engine_count);
    def_structure_icon_editor_engine_variable = 
	    Chain_of_available_icon_editor_engines;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_editor_engine_variable))
	goto end_loop;
    def_structure_icon_editor_engine_variable = 
	    ISVREF(def_structure_icon_editor_engine_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-EDITOR-ENGINE-1 */
Object reclaim_icon_editor_engine_1(icon_editor_engine)
    Object icon_editor_engine;
{
    Object temp, svref_arg_2;

    x_note_fn_call(232,35);
    inline_note_reclaim_cons(icon_editor_engine,Nil);
    temp = ISVREF(Chain_of_available_icon_editor_engines_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_editor_engine,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_editor_engines_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_editor_engine;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-EDITOR-ENGINE */
Object reclaim_structure_for_icon_editor_engine(icon_editor_engine)
    Object icon_editor_engine;
{
    x_note_fn_call(232,36);
    return reclaim_icon_editor_engine_1(icon_editor_engine);
}

static Object Qg2_defstruct_structure_name_icon_editor_engine_g2_struct;  /* g2-defstruct-structure-name::icon-editor-engine-g2-struct */

/* MAKE-PERMANENT-ICON-EDITOR-ENGINE-STRUCTURE-INTERNAL */
Object make_permanent_icon_editor_engine_structure_internal()
{
    Object def_structure_icon_editor_engine_variable;
    Object defstruct_g2_icon_editor_engine_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,37);
    def_structure_icon_editor_engine_variable = Nil;
    atomic_incff_symval(Qicon_editor_engine_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_editor_engine_variable = Nil;
	gensymed_symbol = (SI_Long)18L;
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
	defstruct_g2_icon_editor_engine_variable = the_array;
	SVREF(defstruct_g2_icon_editor_engine_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_engine_g2_struct;
	def_structure_icon_editor_engine_variable = 
		defstruct_g2_icon_editor_engine_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_editor_engine_variable);
}

static Object Qforeground;         /* foreground */

/* MAKE-ICON-EDITOR-ENGINE-1 */
Object make_icon_editor_engine_1()
{
    Object def_structure_icon_editor_engine_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,38);
    def_structure_icon_editor_engine_variable = 
	    ISVREF(Chain_of_available_icon_editor_engines_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_editor_engine_variable) {
	svref_arg_1 = Chain_of_available_icon_editor_engines_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icon_editor_engine_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_icon_editor_engine_g2_struct;
    }
    else
	def_structure_icon_editor_engine_variable = 
		make_permanent_icon_editor_engine_structure_internal();
    inline_note_allocate_cons(def_structure_icon_editor_engine_variable,Nil);
    ISVREF(def_structure_icon_editor_engine_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_engine_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)4L)) = Nil;
    ISVREF(def_structure_icon_editor_engine_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_icon_editor_engine_variable,(SI_Long)7L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_engine_variable,(SI_Long)8L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_engine_variable,(SI_Long)9L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)11L)) = 
	    Qforeground;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)13L)) = 
	    Qforeground;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_icon_editor_engine_variable,FIX((SI_Long)17L)) = Nil;
    return VALUES_1(def_structure_icon_editor_engine_variable);
}

Object The_type_description_of_icon_editor_view_pad = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_editor_view_pads, Qchain_of_available_icon_editor_view_pads);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_view_pad_count, Qicon_editor_view_pad_count);

Object Chain_of_available_icon_editor_view_pads_vector = UNBOUND;

/* ICON-EDITOR-VIEW-PAD-STRUCTURE-MEMORY-USAGE */
Object icon_editor_view_pad_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,39);
    temp = Icon_editor_view_pad_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)22L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-EDITOR-VIEW-PAD-COUNT */
Object outstanding_icon_editor_view_pad_count()
{
    Object def_structure_icon_editor_view_pad_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,40);
    gensymed_symbol = IFIX(Icon_editor_view_pad_count);
    def_structure_icon_editor_view_pad_variable = 
	    Chain_of_available_icon_editor_view_pads;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_editor_view_pad_variable))
	goto end_loop;
    def_structure_icon_editor_view_pad_variable = 
	    ISVREF(def_structure_icon_editor_view_pad_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-EDITOR-VIEW-PAD-1 */
Object reclaim_icon_editor_view_pad_1(icon_editor_view_pad)
    Object icon_editor_view_pad;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(232,41);
    inline_note_reclaim_cons(icon_editor_view_pad,Nil);
    structure_being_reclaimed = icon_editor_view_pad;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(icon_editor_view_pad,(SI_Long)4L));
      SVREF(icon_editor_view_pad,FIX((SI_Long)4L)) = Nil;
      reclaim_frame_serial_number(ISVREF(icon_editor_view_pad,(SI_Long)14L));
      SVREF(icon_editor_view_pad,FIX((SI_Long)14L)) = Nil;
      reclaim_frame_serial_number(ISVREF(icon_editor_view_pad,(SI_Long)17L));
      SVREF(icon_editor_view_pad,FIX((SI_Long)17L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icon_editor_view_pads_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_editor_view_pad,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_editor_view_pads_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_editor_view_pad;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-EDITOR-VIEW-PAD */
Object reclaim_structure_for_icon_editor_view_pad(icon_editor_view_pad)
    Object icon_editor_view_pad;
{
    x_note_fn_call(232,42);
    return reclaim_icon_editor_view_pad_1(icon_editor_view_pad);
}

static Object Qg2_defstruct_structure_name_icon_editor_view_pad_g2_struct;  /* g2-defstruct-structure-name::icon-editor-view-pad-g2-struct */

/* MAKE-PERMANENT-ICON-EDITOR-VIEW-PAD-STRUCTURE-INTERNAL */
Object make_permanent_icon_editor_view_pad_structure_internal()
{
    Object def_structure_icon_editor_view_pad_variable;
    Object defstruct_g2_icon_editor_view_pad_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,43);
    def_structure_icon_editor_view_pad_variable = Nil;
    atomic_incff_symval(Qicon_editor_view_pad_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_editor_view_pad_variable = Nil;
	gensymed_symbol = (SI_Long)22L;
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
	defstruct_g2_icon_editor_view_pad_variable = the_array;
	SVREF(defstruct_g2_icon_editor_view_pad_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_icon_editor_view_pad_g2_struct;
	def_structure_icon_editor_view_pad_variable = 
		defstruct_g2_icon_editor_view_pad_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_editor_view_pad_variable);
}

/* MAKE-ICON-EDITOR-VIEW-PAD-1 */
Object make_icon_editor_view_pad_1(icon_editor_view_pad_x_in_workspace,
	    icon_editor_view_pad_y_in_workspace,
	    icon_editor_view_pad_bounding_box,
	    icon_editor_view_pad_reference_serial_number)
    Object icon_editor_view_pad_x_in_workspace;
    Object icon_editor_view_pad_y_in_workspace;
    Object icon_editor_view_pad_bounding_box;
    Object icon_editor_view_pad_reference_serial_number;
{
    Object def_structure_icon_editor_view_pad_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(232,44);
    def_structure_icon_editor_view_pad_variable = 
	    ISVREF(Chain_of_available_icon_editor_view_pads_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_editor_view_pad_variable) {
	svref_arg_1 = Chain_of_available_icon_editor_view_pads_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_icon_editor_view_pad_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_editor_view_pad_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_view_pad_g2_struct;
    }
    else
	def_structure_icon_editor_view_pad_variable = 
		make_permanent_icon_editor_view_pad_structure_internal();
    inline_note_allocate_cons(def_structure_icon_editor_view_pad_variable,Nil);
    SVREF(def_structure_icon_editor_view_pad_variable,FIX((SI_Long)1L)) = 
	    icon_editor_view_pad_x_in_workspace;
    SVREF(def_structure_icon_editor_view_pad_variable,FIX((SI_Long)2L)) = 
	    icon_editor_view_pad_y_in_workspace;
    SVREF(def_structure_icon_editor_view_pad_variable,FIX((SI_Long)3L)) = 
	    icon_editor_view_pad_bounding_box;
    SVREF(def_structure_icon_editor_view_pad_variable,FIX((SI_Long)4L)) = 
	    icon_editor_view_pad_reference_serial_number;
    ISVREF(def_structure_icon_editor_view_pad_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_view_pad_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_icon_editor_view_pad_variable,FIX((SI_Long)10L)) = 
	    FIX((SI_Long)4096L);
    SVREF(def_structure_icon_editor_view_pad_variable,FIX((SI_Long)11L)) = 
	    FIX((SI_Long)4096L);
    ISVREF(def_structure_icon_editor_view_pad_variable,(SI_Long)14L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_icon_editor_view_pad_variable,FIX((SI_Long)17L)) = Nil;
    return VALUES_1(def_structure_icon_editor_view_pad_variable);
}

/* DELETE-VIEW-PAD-MARKER-STACK */
Object delete_view_pad_marker_stack(marker_stack)
    Object marker_stack;
{
    Object frame_and_serial_number_pair, ab_loop_list_, gensymed_symbol, x, y;
    Object xa, ya;
    char temp;

    x_note_fn_call(232,45);
    frame_and_serial_number_pair = Nil;
    ab_loop_list_ = marker_stack;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame_and_serial_number_pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(CAR(frame_and_serial_number_pair),(SI_Long)3L);
    x = CAR(frame_and_serial_number_pair);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = CDR(frame_and_serial_number_pair);
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
	delete_frame(CAR(frame_and_serial_number_pair));
    reclaim_frame_serial_number(CDR(frame_and_serial_number_pair));
    reclaim_icon_editor_cons_1(frame_and_serial_number_pair);
    goto next_loop;
  end_loop:
    reclaim_icon_editor_list_1(marker_stack);
    return VALUES_1(Qnil);
}

/* DELETE-ICON-EDITOR-VIEW-PAD-ICON-FOR-CURRENT-LAYER */
Object delete_icon_editor_view_pad_icon_for_current_layer(view_pad)
    Object view_pad;
{
    Object xored_iconic_entity_qm, iconic_entity_qm, serial_number;
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(232,46);
    xored_iconic_entity_qm = ISVREF(view_pad,(SI_Long)15L);
    iconic_entity_qm = ISVREF(view_pad,(SI_Long)16L);
    serial_number = ISVREF(view_pad,(SI_Long)17L);
    if (xored_iconic_entity_qm) {
	gensymed_symbol = ISVREF(xored_iconic_entity_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(xored_iconic_entity_qm) ? 
		EQ(ISVREF(xored_iconic_entity_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp) {
	    delete_frame(xored_iconic_entity_qm);
	    SVREF(view_pad,FIX((SI_Long)15L)) = Nil;
	}
    }
    if (iconic_entity_qm) {
	gensymed_symbol = ISVREF(iconic_entity_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(iconic_entity_qm) ? 
		EQ(ISVREF(iconic_entity_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp) {
	    delete_frame(iconic_entity_qm);
	    return VALUES_1(SVREF(view_pad,FIX((SI_Long)16L)) = Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_icon_editor_layers_pad = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_editor_layers_pads, Qchain_of_available_icon_editor_layers_pads);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_layers_pad_count, Qicon_editor_layers_pad_count);

Object Chain_of_available_icon_editor_layers_pads_vector = UNBOUND;

/* ICON-EDITOR-LAYERS-PAD-STRUCTURE-MEMORY-USAGE */
Object icon_editor_layers_pad_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,47);
    temp = Icon_editor_layers_pad_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)17L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-EDITOR-LAYERS-PAD-COUNT */
Object outstanding_icon_editor_layers_pad_count()
{
    Object def_structure_icon_editor_layers_pad_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,48);
    gensymed_symbol = IFIX(Icon_editor_layers_pad_count);
    def_structure_icon_editor_layers_pad_variable = 
	    Chain_of_available_icon_editor_layers_pads;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_editor_layers_pad_variable))
	goto end_loop;
    def_structure_icon_editor_layers_pad_variable = 
	    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-EDITOR-LAYERS-PAD-1 */
Object reclaim_icon_editor_layers_pad_1(icon_editor_layers_pad)
    Object icon_editor_layers_pad;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(232,49);
    inline_note_reclaim_cons(icon_editor_layers_pad,Nil);
    structure_being_reclaimed = icon_editor_layers_pad;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(icon_editor_layers_pad,(SI_Long)4L));
      SVREF(icon_editor_layers_pad,FIX((SI_Long)4L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icon_editor_layers_pads_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_editor_layers_pad,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_editor_layers_pads_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_editor_layers_pad;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-EDITOR-LAYERS-PAD */
Object reclaim_structure_for_icon_editor_layers_pad(icon_editor_layers_pad)
    Object icon_editor_layers_pad;
{
    x_note_fn_call(232,50);
    return reclaim_icon_editor_layers_pad_1(icon_editor_layers_pad);
}

static Object Qg2_defstruct_structure_name_icon_editor_layers_pad_g2_struct;  /* g2-defstruct-structure-name::icon-editor-layers-pad-g2-struct */

/* MAKE-PERMANENT-ICON-EDITOR-LAYERS-PAD-STRUCTURE-INTERNAL */
Object make_permanent_icon_editor_layers_pad_structure_internal()
{
    Object def_structure_icon_editor_layers_pad_variable;
    Object defstruct_g2_icon_editor_layers_pad_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,51);
    def_structure_icon_editor_layers_pad_variable = Nil;
    atomic_incff_symval(Qicon_editor_layers_pad_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_editor_layers_pad_variable = Nil;
	gensymed_symbol = (SI_Long)17L;
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
	defstruct_g2_icon_editor_layers_pad_variable = the_array;
	SVREF(defstruct_g2_icon_editor_layers_pad_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_layers_pad_g2_struct;
	def_structure_icon_editor_layers_pad_variable = 
		defstruct_g2_icon_editor_layers_pad_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_editor_layers_pad_variable);
}

/* MAKE-ICON-EDITOR-LAYERS-PAD-1 */
Object make_icon_editor_layers_pad_1(icon_editor_layers_pad_x_in_workspace,
	    icon_editor_layers_pad_y_in_workspace,
	    icon_editor_layers_pad_bounding_box,
	    icon_editor_layers_pad_bounding_box_serial_number)
    Object icon_editor_layers_pad_x_in_workspace;
    Object icon_editor_layers_pad_y_in_workspace;
    Object icon_editor_layers_pad_bounding_box;
    Object icon_editor_layers_pad_bounding_box_serial_number;
{
    Object def_structure_icon_editor_layers_pad_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(232,52);
    def_structure_icon_editor_layers_pad_variable = 
	    ISVREF(Chain_of_available_icon_editor_layers_pads_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_editor_layers_pad_variable) {
	svref_arg_1 = Chain_of_available_icon_editor_layers_pads_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_icon_editor_layers_pad_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_editor_layers_pad_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_layers_pad_g2_struct;
    }
    else
	def_structure_icon_editor_layers_pad_variable = 
		make_permanent_icon_editor_layers_pad_structure_internal();
    inline_note_allocate_cons(def_structure_icon_editor_layers_pad_variable,
	    Nil);
    SVREF(def_structure_icon_editor_layers_pad_variable,FIX((SI_Long)1L)) 
	    = icon_editor_layers_pad_x_in_workspace;
    SVREF(def_structure_icon_editor_layers_pad_variable,FIX((SI_Long)2L)) 
	    = icon_editor_layers_pad_y_in_workspace;
    SVREF(def_structure_icon_editor_layers_pad_variable,FIX((SI_Long)3L)) 
	    = icon_editor_layers_pad_bounding_box;
    SVREF(def_structure_icon_editor_layers_pad_variable,FIX((SI_Long)4L)) 
	    = icon_editor_layers_pad_bounding_box_serial_number;
    SVREF(def_structure_icon_editor_layers_pad_variable,FIX((SI_Long)8L)) 
	    = FIX((SI_Long)4096L);
    SVREF(def_structure_icon_editor_layers_pad_variable,FIX((SI_Long)9L)) 
	    = FIX((SI_Long)4096L);
    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)10L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)11L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)12L) = 
	    FIX((SI_Long)5L);
    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)13L) = 
	    FIX((SI_Long)9999999L);
    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)14L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)15L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_editor_layers_pad_variable,(SI_Long)16L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_icon_editor_layers_pad_variable);
}

Object The_type_description_of_icon_editor_button = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_editor_buttons, Qchain_of_available_icon_editor_buttons);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_button_count, Qicon_editor_button_count);

Object Chain_of_available_icon_editor_buttons_vector = UNBOUND;

/* ICON-EDITOR-BUTTON-STRUCTURE-MEMORY-USAGE */
Object icon_editor_button_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,53);
    temp = Icon_editor_button_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-EDITOR-BUTTON-COUNT */
Object outstanding_icon_editor_button_count()
{
    Object def_structure_icon_editor_button_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,54);
    gensymed_symbol = IFIX(Icon_editor_button_count);
    def_structure_icon_editor_button_variable = 
	    Chain_of_available_icon_editor_buttons;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_editor_button_variable))
	goto end_loop;
    def_structure_icon_editor_button_variable = 
	    ISVREF(def_structure_icon_editor_button_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-EDITOR-BUTTON-1 */
Object reclaim_icon_editor_button_1(icon_editor_button)
    Object icon_editor_button;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(232,55);
    inline_note_reclaim_cons(icon_editor_button,Nil);
    structure_being_reclaimed = icon_editor_button;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(icon_editor_button,(SI_Long)6L));
      SVREF(icon_editor_button,FIX((SI_Long)6L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icon_editor_buttons_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_editor_button,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_editor_buttons_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_editor_button;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-EDITOR-BUTTON */
Object reclaim_structure_for_icon_editor_button(icon_editor_button)
    Object icon_editor_button;
{
    x_note_fn_call(232,56);
    return reclaim_icon_editor_button_1(icon_editor_button);
}

static Object Qg2_defstruct_structure_name_icon_editor_button_g2_struct;  /* g2-defstruct-structure-name::icon-editor-button-g2-struct */

/* MAKE-PERMANENT-ICON-EDITOR-BUTTON-STRUCTURE-INTERNAL */
Object make_permanent_icon_editor_button_structure_internal()
{
    Object def_structure_icon_editor_button_variable;
    Object defstruct_g2_icon_editor_button_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,57);
    def_structure_icon_editor_button_variable = Nil;
    atomic_incff_symval(Qicon_editor_button_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_editor_button_variable = Nil;
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
	defstruct_g2_icon_editor_button_variable = the_array;
	SVREF(defstruct_g2_icon_editor_button_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_button_g2_struct;
	def_structure_icon_editor_button_variable = 
		defstruct_g2_icon_editor_button_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_editor_button_variable);
}

/* MAKE-ICON-EDITOR-BUTTON-1 */
Object make_icon_editor_button_1(icon_editor_button_x_in_workspace,
	    icon_editor_button_y_in_workspace,icon_editor_button_width,
	    icon_editor_button_height,icon_editor_button_frame,
	    icon_editor_button_frame_serial_number)
    Object icon_editor_button_x_in_workspace;
    Object icon_editor_button_y_in_workspace, icon_editor_button_width;
    Object icon_editor_button_height, icon_editor_button_frame;
    Object icon_editor_button_frame_serial_number;
{
    Object def_structure_icon_editor_button_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,58);
    def_structure_icon_editor_button_variable = 
	    ISVREF(Chain_of_available_icon_editor_buttons_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_editor_button_variable) {
	svref_arg_1 = Chain_of_available_icon_editor_buttons_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icon_editor_button_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_editor_button_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_icon_editor_button_g2_struct;
    }
    else
	def_structure_icon_editor_button_variable = 
		make_permanent_icon_editor_button_structure_internal();
    inline_note_allocate_cons(def_structure_icon_editor_button_variable,Nil);
    SVREF(def_structure_icon_editor_button_variable,FIX((SI_Long)1L)) = 
	    icon_editor_button_x_in_workspace;
    SVREF(def_structure_icon_editor_button_variable,FIX((SI_Long)2L)) = 
	    icon_editor_button_y_in_workspace;
    SVREF(def_structure_icon_editor_button_variable,FIX((SI_Long)3L)) = 
	    icon_editor_button_width;
    SVREF(def_structure_icon_editor_button_variable,FIX((SI_Long)4L)) = 
	    icon_editor_button_height;
    SVREF(def_structure_icon_editor_button_variable,FIX((SI_Long)5L)) = 
	    icon_editor_button_frame;
    SVREF(def_structure_icon_editor_button_variable,FIX((SI_Long)6L)) = 
	    icon_editor_button_frame_serial_number;
    return VALUES_1(def_structure_icon_editor_button_variable);
}

static Object Qbutton_label;       /* button-label */

static Object Qbig_icon_editor_text_button;  /* big-icon-editor-text-button */

static Object Qsmall_icon_editor_text_button;  /* small-icon-editor-text-button */

/* CREATE-ICON-EDITOR-BUTTON */
Object create_icon_editor_button(x_in_workspace_init,y_in_workspace_init,
	    button_text_or_type)
    Object x_in_workspace_init, y_in_workspace_init, button_text_or_type;
{
    Object symbol_id_for_button, temp, current_localization_purpose_qm;
    Object translated_button_text_qm, temp_1, button_frame, gensymed_symbol;
    SI_Long x_in_workspace, y_in_workspace, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(232,59);
    SAVE_STACK();
    x_in_workspace = IFIX(x_in_workspace_init);
    y_in_workspace = IFIX(y_in_workspace_init);
    if (text_string_p(button_text_or_type)) {
	symbol_id_for_button = intern_text_string(1,
		string_upcasew(button_text_or_type));
	LOCK(Localization_context);
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = Current_localization_purpose_qm;
	    if (temp);
	    else
		temp = Qbutton_label;
	    current_localization_purpose_qm = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
		    0);
	      temp = translation_for_symbol_qm(1,symbol_id_for_button);
	    POP_SPECIAL();
	    SAVE_VALUES(VALUES_1(temp));
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Localization_context);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	translated_button_text_qm = result;
	temp_1 = x_in_workspace == (SI_Long)0L ? 
		Qbig_icon_editor_text_button : Qsmall_icon_editor_text_button;
	temp = translated_button_text_qm ? 
		copy_text_string(translated_button_text_qm) : Nil;
	if (temp);
	else
	    temp = copy_text_string(button_text_or_type);
	button_frame = make_button(2,temp_1,temp);
    }
    else
	button_frame = make_button(1,button_text_or_type);
    gensymed_symbol = ISVREF(button_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(button_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(button_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(button_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    result = make_icon_editor_button_1(FIX(x_in_workspace),
	    FIX(y_in_workspace),temp_1,temp,button_frame,
	    copy_frame_serial_number(Current_frame_serial_number));
    RESTORE_STACK();
    return result;
}

/* DELETE-ICON-EDITOR-BUTTON */
Object delete_icon_editor_button(icon_editor_button)
    Object icon_editor_button;
{
    Object button_frame, gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(232,60);
    button_frame = ISVREF(icon_editor_button,(SI_Long)5L);
    gensymed_symbol = ISVREF(button_frame,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(button_frame) ? EQ(ISVREF(button_frame,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(icon_editor_button,(SI_Long)6L);
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
	delete_frame(button_frame);
    return reclaim_icon_editor_button_1(icon_editor_button);
}

/* RECLAIM-ICON-EDITOR-TABLE-INFO-FRAME-ICON-EDITOR-VALUE */
Object reclaim_icon_editor_table_info_frame_icon_editor_value(frame,
	    icon_editor)
    Object frame, icon_editor;
{
    x_note_fn_call(232,61);
    return VALUES_1(Nil);
}

static Object Knil;                /* :nil */

static Object Qnone;               /* none */

/* WRITE-REGION?-FROM-SLOT */
Object write_region_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(232,62);
    return twrite_symbol(1,value &&  !EQ(value,Knil) ? value : Qnone);
}

/* WRITE-COLOR-OR-METACOLOR-FROM-SLOT */
Object write_color_or_metacolor_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(232,63);
    return twrite_color(value);
}

static Object string_constant;     /* "(~a, ~a)" */

/* WRITE-ICON-EDITOR-TABLE-INFO-FRAME-X-Y-POSITION-FROM-SLOT */
Object write_icon_editor_table_info_frame_x_y_position_from_slot(value,frame)
    Object value, frame;
{
    x_note_fn_call(232,64);
    return tformat(3,string_constant,ISVREF(frame,(SI_Long)27L),
	    ISVREF(frame,(SI_Long)28L));
}

/* RECLAIM-ICON-EDITOR-TABLE-INFO-FRAME-INFO-VALUE */
Object reclaim_icon_editor_table_info_frame_info_value(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(232,65);
    reclaim_icon_editor_slot_value(value);
    return VALUES_1(Nil);
}

Object The_type_description_of_icon_editor_table = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_editor_tables, Qchain_of_available_icon_editor_tables);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_table_count, Qicon_editor_table_count);

Object Chain_of_available_icon_editor_tables_vector = UNBOUND;

/* ICON-EDITOR-TABLE-STRUCTURE-MEMORY-USAGE */
Object icon_editor_table_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,66);
    temp = Icon_editor_table_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-EDITOR-TABLE-COUNT */
Object outstanding_icon_editor_table_count()
{
    Object def_structure_icon_editor_table_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,67);
    gensymed_symbol = IFIX(Icon_editor_table_count);
    def_structure_icon_editor_table_variable = 
	    Chain_of_available_icon_editor_tables;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_editor_table_variable))
	goto end_loop;
    def_structure_icon_editor_table_variable = 
	    ISVREF(def_structure_icon_editor_table_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-EDITOR-TABLE-1 */
Object reclaim_icon_editor_table_1(icon_editor_table)
    Object icon_editor_table;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(232,68);
    inline_note_reclaim_cons(icon_editor_table,Nil);
    structure_being_reclaimed = icon_editor_table;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(icon_editor_table,(SI_Long)7L));
      SVREF(icon_editor_table,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icon_editor_tables_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_editor_table,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_editor_tables_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_editor_table;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-EDITOR-TABLE */
Object reclaim_structure_for_icon_editor_table(icon_editor_table)
    Object icon_editor_table;
{
    x_note_fn_call(232,69);
    return reclaim_icon_editor_table_1(icon_editor_table);
}

static Object Qg2_defstruct_structure_name_icon_editor_table_g2_struct;  /* g2-defstruct-structure-name::icon-editor-table-g2-struct */

/* MAKE-PERMANENT-ICON-EDITOR-TABLE-STRUCTURE-INTERNAL */
Object make_permanent_icon_editor_table_structure_internal()
{
    Object def_structure_icon_editor_table_variable;
    Object defstruct_g2_icon_editor_table_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,70);
    def_structure_icon_editor_table_variable = Nil;
    atomic_incff_symval(Qicon_editor_table_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_editor_table_variable = Nil;
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
	defstruct_g2_icon_editor_table_variable = the_array;
	SVREF(defstruct_g2_icon_editor_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_table_g2_struct;
	def_structure_icon_editor_table_variable = 
		defstruct_g2_icon_editor_table_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_editor_table_variable);
}

/* MAKE-ICON-EDITOR-TABLE-1 */
Object make_icon_editor_table_1(icon_editor_table_x_in_workspace,
	    icon_editor_table_y_in_workspace,icon_editor_table_width,
	    icon_editor_table_height,icon_editor_table_info_frame,
	    icon_editor_table_display_frame,
	    icon_editor_table_reference_serial_number,
	    icon_editor_table_display_slot_names)
    Object icon_editor_table_x_in_workspace, icon_editor_table_y_in_workspace;
    Object icon_editor_table_width, icon_editor_table_height;
    Object icon_editor_table_info_frame, icon_editor_table_display_frame;
    Object icon_editor_table_reference_serial_number;
    Object icon_editor_table_display_slot_names;
{
    Object def_structure_icon_editor_table_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,71);
    def_structure_icon_editor_table_variable = 
	    ISVREF(Chain_of_available_icon_editor_tables_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_editor_table_variable) {
	svref_arg_1 = Chain_of_available_icon_editor_tables_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icon_editor_table_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_table_g2_struct;
    }
    else
	def_structure_icon_editor_table_variable = 
		make_permanent_icon_editor_table_structure_internal();
    inline_note_allocate_cons(def_structure_icon_editor_table_variable,Nil);
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)1L)) = 
	    icon_editor_table_x_in_workspace;
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)2L)) = 
	    icon_editor_table_y_in_workspace;
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)3L)) = 
	    icon_editor_table_width;
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)4L)) = 
	    icon_editor_table_height;
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)5L)) = 
	    icon_editor_table_info_frame;
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)6L)) = 
	    icon_editor_table_display_frame;
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)7L)) = 
	    icon_editor_table_reference_serial_number;
    SVREF(def_structure_icon_editor_table_variable,FIX((SI_Long)8L)) = 
	    icon_editor_table_display_slot_names;
    return VALUES_1(def_structure_icon_editor_table_variable);
}

static Object Qicon_editor_table_info_frame;  /* icon-editor-table-info-frame */

static Object Qicon_editor_table_info_frame_global_stipple;  /* icon-editor-table-info-frame-global-stipple */

static Object Qicon_editor_table_info_frame_stipple;  /* icon-editor-table-info-frame-stipple */

static Object Qicon_editor_table_info_frame_main_image;  /* icon-editor-table-info-frame-main-image */

static Object Qicon_editor_table_info_frame_text;  /* icon-editor-table-info-frame-text */

static Object Qsmall_class_format;  /* small-class-format */

static Object Qsmall_attribute_value_format;  /* small-attribute-value-format */

static Object Qsmall_attribute_description_format;  /* small-attribute-description-format */

/* CREATE-ICON-EDITOR-TABLE */
Object create_icon_editor_table(x_in_workspace_init,y_in_workspace_init,
	    display_slot_name_or_names,use_small_fonts_qm)
    Object x_in_workspace_init, y_in_workspace_init;
    Object display_slot_name_or_names, use_small_fonts_qm;
{
    Object display_slot_names, info_frame, display_frame, gensymed_symbol;
    Object temp, temp_1;
    SI_Long x_in_workspace, y_in_workspace, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;

    x_note_fn_call(232,72);
    x_in_workspace = IFIX(x_in_workspace_init);
    y_in_workspace = IFIX(y_in_workspace_init);
    display_slot_names = SYMBOLP(display_slot_name_or_names) ? 
	    icon_editor_cons_1(display_slot_name_or_names,Nil) : 
	    display_slot_name_or_names;
    info_frame = make_frame(Qicon_editor_table_info_frame);
    ISVREF(info_frame,(SI_Long)20L) = FIX((SI_Long)0L);
    ISVREF(info_frame,(SI_Long)21L) = Nil;
    set_non_savable_lookup_slot_value(info_frame,
	    Qicon_editor_table_info_frame_global_stipple,Nil);
    set_non_savable_lookup_slot_value(info_frame,
	    Qicon_editor_table_info_frame_stipple,Nil);
    set_non_savable_lookup_slot_value(info_frame,
	    Qicon_editor_table_info_frame_main_image,Nil);
    set_non_savable_lookup_slot_value(info_frame,
	    Qicon_editor_table_info_frame_text,Nil);
    ISVREF(info_frame,(SI_Long)22L) = Qforeground;
    ISVREF(info_frame,(SI_Long)24L) = Qforeground;
    ISVREF(info_frame,(SI_Long)23L) = Nil;
    ISVREF(info_frame,(SI_Long)25L) = FIX((SI_Long)100L);
    ISVREF(info_frame,(SI_Long)26L) = FIX((SI_Long)100L);
    display_frame = make_attributes_table(6,info_frame,Nil,
	    use_small_fonts_qm ? Qsmall_class_format : Nil,
	    use_small_fonts_qm ? Qsmall_attribute_value_format : Nil,
	    use_small_fonts_qm ? Qsmall_attribute_description_format : Nil,
	    display_slot_names);
    gensymed_symbol = ISVREF(display_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(display_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(display_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(display_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    return make_icon_editor_table_1(FIX(x_in_workspace),
	    FIX(y_in_workspace),temp,temp_1,info_frame,display_frame,
	    copy_frame_serial_number(Current_frame_serial_number),
	    display_slot_names);
}

/* DELETE-ICON-EDITOR-TABLE */
Object delete_icon_editor_table(icon_editor_table)
    Object icon_editor_table;
{
    Object info_frame, display_frame, reference_serial_number, gensymed_symbol;
    Object xa, ya;
    char temp;

    x_note_fn_call(232,73);
    info_frame = ISVREF(icon_editor_table,(SI_Long)5L);
    display_frame = ISVREF(icon_editor_table,(SI_Long)6L);
    reference_serial_number = ISVREF(icon_editor_table,(SI_Long)7L);
    gensymed_symbol = ISVREF(info_frame,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(info_frame) ? EQ(ISVREF(info_frame,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp)
	delete_frame(info_frame);
    gensymed_symbol = ISVREF(display_frame,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(display_frame) ? EQ(ISVREF(display_frame,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp)
	delete_frame(info_frame);
    reclaim_icon_editor_list_1(ISVREF(icon_editor_table,(SI_Long)8L));
    return reclaim_icon_editor_table_1(icon_editor_table);
}

Object The_type_description_of_icon_editor = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_editors, Qchain_of_available_icon_editors);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_count, Qicon_editor_count);

Object Chain_of_available_icon_editors_vector = UNBOUND;

/* ICON-EDITOR-STRUCTURE-MEMORY-USAGE */
Object icon_editor_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(232,74);
    temp = Icon_editor_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)28L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-EDITOR-COUNT */
Object outstanding_icon_editor_count()
{
    Object def_structure_icon_editor_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,75);
    gensymed_symbol = IFIX(Icon_editor_count);
    def_structure_icon_editor_variable = Chain_of_available_icon_editors;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_editor_variable))
	goto end_loop;
    def_structure_icon_editor_variable = 
	    ISVREF(def_structure_icon_editor_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-EDITOR-1 */
Object reclaim_icon_editor_1(icon_editor)
    Object icon_editor;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(232,76);
    inline_note_reclaim_cons(icon_editor,Nil);
    structure_being_reclaimed = icon_editor;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(icon_editor,(SI_Long)1L));
      SVREF(icon_editor,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(icon_editor,(SI_Long)2L));
      SVREF(icon_editor,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icon_editors_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_editor,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_editors_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_editor;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-EDITOR */
Object reclaim_structure_for_icon_editor(icon_editor)
    Object icon_editor;
{
    x_note_fn_call(232,77);
    return reclaim_icon_editor_1(icon_editor);
}

static Object Qg2_defstruct_structure_name_icon_editor_g2_struct;  /* g2-defstruct-structure-name::icon-editor-g2-struct */

/* MAKE-PERMANENT-ICON-EDITOR-STRUCTURE-INTERNAL */
Object make_permanent_icon_editor_structure_internal()
{
    Object def_structure_icon_editor_variable;
    Object defstruct_g2_icon_editor_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(232,78);
    def_structure_icon_editor_variable = Nil;
    atomic_incff_symval(Qicon_editor_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_editor_variable = Nil;
	gensymed_symbol = (SI_Long)28L;
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
	defstruct_g2_icon_editor_variable = the_array;
	SVREF(defstruct_g2_icon_editor_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_g2_struct;
	SVREF(defstruct_g2_icon_editor_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_icon_editor_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_icon_editor_variable = defstruct_g2_icon_editor_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_editor_variable);
}

/* MAKE-ICON-EDITOR-1 */
Object make_icon_editor_1(icon_editor_class_definition,
	    icon_editor_workspace,icon_editor_reference_serial_number)
    Object icon_editor_class_definition, icon_editor_workspace;
    Object icon_editor_reference_serial_number;
{
    Object def_structure_icon_editor_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(232,79);
    def_structure_icon_editor_variable = 
	    ISVREF(Chain_of_available_icon_editors_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_editor_variable) {
	temp = Chain_of_available_icon_editors_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icon_editor_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_editor_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_editor_g2_struct;
    }
    else
	def_structure_icon_editor_variable = 
		make_permanent_icon_editor_structure_internal();
    inline_note_allocate_cons(def_structure_icon_editor_variable,Nil);
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)3L)) = 
	    icon_editor_class_definition;
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)4L)) = 
	    icon_editor_workspace;
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)5L)) = 
	    icon_editor_reference_serial_number;
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)2L)) = temp;
    temp = make_icon_editor_translator_1();
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)10L)) = temp;
    temp = make_icon_editor_engine_1();
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)11L)) = temp;
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)25L)) = T;
    SVREF(def_structure_icon_editor_variable,FIX((SI_Long)26L)) = Nil;
    return VALUES_1(def_structure_icon_editor_variable);
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-ICON-EDITOR */
Object clean_up_workstation_context_for_icon_editor(icon_editor)
    Object icon_editor;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(232,80);
    cleanup_icon_editor(icon_editor);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_icon_editor,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = icon_editor;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-ICON-EDITOR */
Object valid_workstation_context_p_for_icon_editor(icon_editor)
    Object icon_editor;
{
    Object gensymed_symbol, gensymed_symbol_1, x, y, xa, ya;
    char temp;

    x_note_fn_call(232,81);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_icon_editor,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = icon_editor;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1)) {
	gensymed_symbol = ISVREF(ISVREF(icon_editor,(SI_Long)4L),(SI_Long)3L);
	x = ISVREF(icon_editor,(SI_Long)4L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icon_editor,(SI_Long)5L);
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
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(ISVREF(icon_editor,(SI_Long)3L),(SI_Long)3L);
	x = ISVREF(icon_editor,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icon_editor,(SI_Long)5L);
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
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	return VALUES_1( !temp ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-ICON-EDITOR-MAIN-COLOR-MENU */
Object delete_icon_editor_main_color_menu(icon_editor)
    Object icon_editor;
{
    Object gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(232,82);
    if (ISVREF(icon_editor,(SI_Long)26L)) {
	gensymed_symbol = ISVREF(ISVREF(icon_editor,(SI_Long)26L),(SI_Long)3L);
	x = ISVREF(icon_editor,(SI_Long)26L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icon_editor,(SI_Long)27L);
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
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	if ( !temp) {
	    delete_frame(ISVREF(icon_editor,(SI_Long)26L));
	    return VALUES_1(SVREF(icon_editor,FIX((SI_Long)26L)) = Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdefault_slot_constant;  /* default-slot-constant */

/* RECLAIM-ICON-EDITOR-SLOT-VALUE */
Object reclaim_icon_editor_slot_value(value_to_reclaim)
    Object value_to_reclaim;
{
    Object car_1, cdr_1, l, x, cdr_arg;
    char temp;

    x_note_fn_call(232,83);
    if (CONSP(value_to_reclaim)) {
	temp = EQ(value_to_reclaim,No_value);
	if (temp);
	else if ( !(INLINE_DOUBLE_FLOAT_VECTOR_P(value_to_reclaim) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_to_reclaim)) == 
		(SI_Long)1L)) {
	    car_1 = M_CAR(value_to_reclaim);
	    cdr_1 = M_CDR(value_to_reclaim);
	    temp = (slot_value_number_p(car_1) || text_string_p(car_1) || 
		    STRINGP(car_1)) && CONSP(cdr_1) ? EQ(M_CDR(cdr_1),
		    Qdefault_slot_constant) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    l = value_to_reclaim;
	    x = Nil;
	  next_loop:
	    x = CAR(l);
	    if ( !SYMBOLP(x)) {
		if ( !NUMBERP(x))
		    reclaim_icon_editor_slot_value(x);
	    }
	    l = CDR(l);
	    if (ATOM(l) || EQ(l,No_value))
		goto end_loop;
	    goto next_loop;
	  end_loop:
	    if (l) {
		reclaim_icon_editor_slot_value(l);
		cdr_arg = last(value_to_reclaim,_);
		M_CDR(cdr_arg) = Nil;
	    }
	    reclaim_icon_editor_list_1(value_to_reclaim);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (SIMPLE_VECTOR_P(value_to_reclaim) && 
	    EQ(ISVREF(value_to_reclaim,(SI_Long)0L),
	    Qg2_defstruct_structure_name_layer_box_g2_struct))
	return delete_layer_box(value_to_reclaim);
    else if (text_string_p(value_to_reclaim))
	return reclaim_text_string(value_to_reclaim);
    else if (INTEGERP(value_to_reclaim))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

/* GET-COLOR-OF-REGION-IN-ICON-EDITOR */
Object get_color_of_region_in_icon_editor(icon_editor,region)
    Object icon_editor, region;
{
    Object region_and_name_alist, label_and_name_pair_qm;

    x_note_fn_call(232,84);
    region_and_name_alist = ISVREF(icon_editor,(SI_Long)6L);
    label_and_name_pair_qm = assq_function(region,region_and_name_alist);
    if (label_and_name_pair_qm)
	return VALUES_1(CDR(label_and_name_pair_qm));
    else
	return VALUES_1(Nil);
}

/* SET-COLOR-OF-REGION-IN-ICON-EDITOR */
Object set_color_of_region_in_icon_editor(icon_editor,region,color_qm)
    Object icon_editor, region, color_qm;
{
    Object region_and_name_alist, label_and_name_pair_qm, temp;
    Object region_and_name, tail_qm, rest_of_alist;

    x_note_fn_call(232,85);
    region_and_name_alist = ISVREF(icon_editor,(SI_Long)6L);
    label_and_name_pair_qm = assq_function(region,region_and_name_alist);
    if (color_qm) {
	if (label_and_name_pair_qm)
	    return VALUES_1(M_CDR(label_and_name_pair_qm) = color_qm);
	else {
	    temp = icon_editor_cons_1(icon_editor_cons_1(region,color_qm),
		    region_and_name_alist);
	    return VALUES_1(SVREF(icon_editor,FIX((SI_Long)6L)) = temp);
	}
    }
    else if (label_and_name_pair_qm) {
	if ( !TRUEP(assq_function(region,ISVREF(ISVREF(icon_editor,
		(SI_Long)11L),(SI_Long)3L)))) {
	    region_and_name = Nil;
	    tail_qm = Nil;
	    rest_of_alist = region_and_name_alist;
	  next_loop:
	    if ( !TRUEP(rest_of_alist))
		goto end_loop;
	    region_and_name = CAR(rest_of_alist);
	    if (EQ(CAR(region_and_name),region)) {
		if (tail_qm) {
		    temp = CDR(rest_of_alist);
		    M_CDR(tail_qm) = temp;
		}
		else {
		    temp = CDR(rest_of_alist);
		    SVREF(icon_editor,FIX((SI_Long)6L)) = temp;
		}
		reclaim_icon_editor_cons_1(region_and_name);
		reclaim_icon_editor_cons_1(rest_of_alist);
		return VALUES_1(Nil);
	    }
	    tail_qm = rest_of_alist;
	    rest_of_alist = M_CDR(rest_of_alist);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-OR-CREATE-COLOR-OF-REGION-IN-ICON-EDITOR */
Object get_or_create_color_of_region_in_icon_editor(icon_editor,region,
	    color_if_have_to_create_qm)
    Object icon_editor, region, color_if_have_to_create_qm;
{
    Object region_and_name_alist, label_and_name_pair_qm, svref_new_value;

    x_note_fn_call(232,86);
    region_and_name_alist = ISVREF(icon_editor,(SI_Long)6L);
    label_and_name_pair_qm = assq_function(region,region_and_name_alist);
    if (label_and_name_pair_qm)
	return VALUES_1(CDR(label_and_name_pair_qm));
    else {
	svref_new_value = icon_editor_cons_1(icon_editor_cons_1(region,
		color_if_have_to_create_qm),region_and_name_alist);
	SVREF(icon_editor,FIX((SI_Long)6L)) = svref_new_value;
	return VALUES_1(color_if_have_to_create_qm);
    }
}

static Object Qimage;              /* image */

/* IMAGE-OF-LAYER? */
Object image_of_layer_qm(layer)
    Object layer;
{
    Object drawing_element, temp, ab_loop_list_;

    x_note_fn_call(232,87);
    drawing_element = Nil;
    temp = CDDR(layer);
    ab_loop_list_ = CAR(temp);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qimage))
	return VALUES_1(drawing_element);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qtext;               /* text */

/* TEXT-OF-LAYER? */
Object text_of_layer_qm(layer)
    Object layer;
{
    Object drawing_element, temp, ab_loop_list_;

    x_note_fn_call(232,88);
    drawing_element = Nil;
    temp = CDDR(layer);
    ab_loop_list_ = CAR(temp);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qtext))
	return VALUES_1(drawing_element);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qstippled_area;      /* stippled-area */

/* STIPPLE-OF-LAYER? */
Object stipple_of_layer_qm(layer)
    Object layer;
{
    Object drawing_element, temp, ab_loop_list_;

    x_note_fn_call(232,89);
    drawing_element = Nil;
    temp = CDDR(layer);
    ab_loop_list_ = CAR(temp);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qstippled_area))
	return VALUES_1(drawing_element);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DECOMPOSE-POLYGON-USING-SLOT-VALUE-CONSES */
Object decompose_polygon_using_slot_value_conses(polygon)
    Object polygon;
{
    Object gensymed_symbol, gensymed_symbol_1, current_edit_state, svref_arg_1;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(232,90);
    SAVE_STACK();
    if (simple_polygon_p(polygon)) {
	gensymed_symbol = Current_edit_state;
	if (Generate_source_annotation_info) {
	    gensymed_symbol_1 = Current_edit_state ? 
		    get_current_sexp_annotation_hash() : Nil;
	    if (gensymed_symbol_1);
	    else
		gensymed_symbol_1 = make_sexp_annotation_hash();
	}
	else
	    gensymed_symbol_1 = Nil;
	current_edit_state = make_edit_state_1();
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		0);
	  svref_arg_1 = Current_edit_state;
	  SVREF(svref_arg_1,FIX((SI_Long)90L)) = gensymed_symbol_1;
	  SAVE_VALUES(copy_tree_using_slot_value_conses_1(decompose_polygon(1,
		  polygon)));
	  if (gensymed_symbol) {
	      svref_arg_1 = Current_edit_state;
	      SVREF(svref_arg_1,FIX((SI_Long)90L)) = Nil;
	  }
	  reclaim_edit_state_1(Current_edit_state);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* DECOMPOSE-POLYGON-USING-ICON-EDITOR-CONSES */
Object decompose_polygon_using_icon_editor_conses(polygon)
    Object polygon;
{
    Object gensymed_symbol, gensymed_symbol_1, current_edit_state, svref_arg_1;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(232,91);
    SAVE_STACK();
    if (simple_polygon_p(polygon)) {
	gensymed_symbol = Current_edit_state;
	if (Generate_source_annotation_info) {
	    gensymed_symbol_1 = Current_edit_state ? 
		    get_current_sexp_annotation_hash() : Nil;
	    if (gensymed_symbol_1);
	    else
		gensymed_symbol_1 = make_sexp_annotation_hash();
	}
	else
	    gensymed_symbol_1 = Nil;
	current_edit_state = make_edit_state_1();
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		0);
	  svref_arg_1 = Current_edit_state;
	  SVREF(svref_arg_1,FIX((SI_Long)90L)) = gensymed_symbol_1;
	  SAVE_VALUES(copy_tree_using_icon_editor_conses_1(decompose_polygon(1,
		  polygon)));
	  if (gensymed_symbol) {
	      svref_arg_1 = Current_edit_state;
	      SVREF(svref_arg_1,FIX((SI_Long)90L)) = Nil;
	  }
	  reclaim_edit_state_1(Current_edit_state);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* SCALED-SLOT-VALUE-POINT */
Object scaled_slot_value_point(x_in_target,y_in_target,x_scale_of_target,
	    y_scale_of_target)
    Object x_in_target, y_in_target, x_scale_of_target, y_scale_of_target;
{
    Object temp, temp_1;
    SI_Long unshifted_result;

    x_note_fn_call(232,92);
    if (IFIX(x_scale_of_target) == (SI_Long)4096L)
	temp = x_in_target;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    x_scale_of_target) && FIXNUM_LT(x_scale_of_target,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_in_target) 
	    && FIXNUM_LT(x_in_target,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale_of_target,
		x_in_target)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(x_scale_of_target,x_in_target);
    if (IFIX(y_scale_of_target) == (SI_Long)4096L)
	temp_1 = y_in_target;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    y_scale_of_target) && FIXNUM_LT(y_scale_of_target,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_in_target) 
	    && FIXNUM_LT(y_in_target,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale_of_target,
		y_in_target)) + (SI_Long)2048L;
	temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_1 = scalef_function(y_scale_of_target,y_in_target);
    return slot_value_list_2(temp,temp_1);
}

/* SCALED-ICON-EDITOR-POINT */
Object scaled_icon_editor_point(x_in_workspace,y_in_workspace,
	    x_scale_of_target,y_scale_of_target)
    Object x_in_workspace, y_in_workspace, x_scale_of_target;
    Object y_scale_of_target;
{
    Object temp, temp_2;
    SI_Long temp_1;

    x_note_fn_call(232,93);
    if (IFIX(x_scale_of_target) == (SI_Long)4096L)
	temp = x_in_workspace;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    x_in_workspace) && FIXNUM_LT(x_in_workspace,
	    Isqrt_of_most_positive_fixnum)))
	temp = inverse_scalef_function(x_scale_of_target,x_in_workspace);
    else if (IFIX(x_in_workspace) >= (SI_Long)0L)
	temp = FIX(((IFIX(x_in_workspace) << (SI_Long)12L) + 
		(IFIX(x_scale_of_target) >>  -  - (SI_Long)1L)) / 
		IFIX(x_scale_of_target));
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(x_in_workspace)) << (SI_Long)12L) + 
		(IFIX(x_scale_of_target) >>  -  - (SI_Long)1L)) / 
		IFIX(x_scale_of_target);
	temp = FIXNUM_NEGATE(FIX(temp_1));
    }
    if (IFIX(y_scale_of_target) == (SI_Long)4096L)
	temp_2 = y_in_workspace;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    y_in_workspace) && FIXNUM_LT(y_in_workspace,
	    Isqrt_of_most_positive_fixnum)))
	temp_2 = inverse_scalef_function(y_scale_of_target,y_in_workspace);
    else if (IFIX(y_in_workspace) >= (SI_Long)0L)
	temp_2 = FIX(((IFIX(y_in_workspace) << (SI_Long)12L) + 
		(IFIX(y_scale_of_target) >>  -  - (SI_Long)1L)) / 
		IFIX(y_scale_of_target));
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(y_in_workspace)) << (SI_Long)12L) + 
		(IFIX(y_scale_of_target) >>  -  - (SI_Long)1L)) / 
		IFIX(y_scale_of_target);
	temp_2 = FIXNUM_NEGATE(FIX(temp_1));
    }
    return icon_editor_list_2(temp,temp_2);
}

static Object string_constant_1;   /* "undefined-string" */

static Object Qfilled_polygon;     /* filled-polygon */

static Object Qarc;                /* arc */

/* COPY-DRAWING-ELEMENT-WITH-ICON-EDITOR-CONSES */
Object copy_drawing_element_with_icon_editor_conses(drawing_element,
	    x_scale_of_target,y_scale_of_target)
    Object drawing_element, x_scale_of_target, y_scale_of_target;
{
    Object temp, name, unevaled_origin, origin, evaled_text_string;
    Object the_whole_string, font, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, stipple, point_1, point_2, temp_1, temp_2, points;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, point;
    Object ab_loop_list__1, ab_loopvar__3, ab_loopvar__4, x, thing, cdr_thing;
    Object car_thing, cadr_thing;
    char temp_3;

    x_note_fn_call(232,94);
    if (ATOM(drawing_element))
	return VALUES_1(drawing_element);
    else {
	temp = CAR(drawing_element);
	if (EQ(temp,Qimage)) {
	    name = SECOND(drawing_element);
	    unevaled_origin = THIRD(drawing_element);
	    if ( !TRUEP(unevaled_origin))
		origin = Nil;
	    else if (Nil) {
		temp = FIXNUMP(FIRST(unevaled_origin)) ? 
			FIRST(unevaled_origin) : 
			simple_eval_for_icon(FIRST(unevaled_origin));
		origin = icon_editor_list_2(temp,
			FIXNUMP(SECOND(unevaled_origin)) ? 
			SECOND(unevaled_origin) : 
			simple_eval_for_icon(SECOND(unevaled_origin)));
	    }
	    else
		origin = copy_tree_using_icon_editor_conses_1(unevaled_origin);
	    if (IFIX(x_scale_of_target) == (SI_Long)4096L && 
		    IFIX(y_scale_of_target) == (SI_Long)4096L) {
		if (origin)
		    return icon_editor_list_3(Qimage,name,origin);
		else
		    return icon_editor_list_2(Qimage,name);
	    }
	    else
		return icon_editor_list_4(Qimage,name,origin ? origin : 
			icon_editor_list_2(FIX((SI_Long)0L),
			FIX((SI_Long)0L)),
			icon_editor_list_2(x_scale_of_target,
			y_scale_of_target));
	}
	else if (EQ(temp,Qtext)) {
	    if (Nil) {
		evaled_text_string = 
			simple_eval_for_icon(SECOND(drawing_element));
		the_whole_string = SYMBOLP(evaled_text_string) ? 
			stringw(string_constant_1) : 
			copy_text_string(evaled_text_string);
	    }
	    else {
		temp = SECOND(drawing_element);
		if (SYMBOLP(temp))
		    the_whole_string = SECOND(drawing_element);
		else
		    the_whole_string = 
			    copy_text_string(SECOND(drawing_element));
	    }
	    unevaled_origin = THIRD(drawing_element);
	    if (Nil) {
		temp = FIXNUMP(FIRST(unevaled_origin)) ? 
			FIRST(unevaled_origin) : 
			simple_eval_for_icon(FIRST(unevaled_origin));
		origin = icon_editor_list_2(temp,
			FIXNUMP(SECOND(unevaled_origin)) ? 
			SECOND(unevaled_origin) : 
			simple_eval_for_icon(SECOND(unevaled_origin)));
	    }
	    else
		origin = copy_tree_using_icon_editor_conses_1(unevaled_origin);
	    font = Nil ? simple_eval_for_icon(FOURTH(drawing_element)) : 
		    FOURTH(drawing_element);
	    if ( !TRUEP(x_scale_of_target) ||  !TRUEP(y_scale_of_target) 
		    || IFIX(x_scale_of_target) == (SI_Long)4096L && 
		    IFIX(y_scale_of_target) == (SI_Long)4096L)
		return icon_editor_list_4(Qtext,the_whole_string,origin,
			copy_list_using_icon_editor_conses_1(font));
	    else {
		gensymed_symbol = make_icon_editor_list_1(FIX((SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = Qtext;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = the_whole_string;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = origin;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = copy_list_using_icon_editor_conses_1(font);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = icon_editor_list_2(x_scale_of_target,
			y_scale_of_target);
		M_CAR(gensymed_symbol_1) = car_new_value;
		return VALUES_1(gensymed_symbol);
	    }
	}
	else if (EQ(temp,Qstippled_area)) {
	    if (Nil) {
		stipple = SECOND(drawing_element);
		point_1 = THIRD(drawing_element);
		point_2 = FOURTH(drawing_element);
		temp_1 = icon_editor_list_2(Qstippled_area,stipple);
		if (point_1) {
		    temp = FIXNUMP(FIRST(point_1)) ? FIRST(point_1) : 
			    simple_eval_for_icon(FIRST(point_1));
		    temp_2 = icon_editor_list_2(temp,
			    FIXNUMP(SECOND(point_1)) ? SECOND(point_1) : 
			    simple_eval_for_icon(SECOND(point_1)));
		    temp = FIXNUMP(FIRST(point_2)) ? FIRST(point_2) : 
			    simple_eval_for_icon(FIRST(point_2));
		    temp = icon_editor_list_2(temp_2,
			    icon_editor_list_2(temp,
			    FIXNUMP(SECOND(point_2)) ? SECOND(point_2) : 
			    simple_eval_for_icon(SECOND(point_2))));
		}
		else
		    temp = Nil;
		return VALUES_1(nconc2(temp_1,temp));
	    }
	    else
		return copy_tree_using_icon_editor_conses_1(drawing_element);
	}
	else if (EQ(temp,Qfilled_polygon)) {
	    if (Nil) {
		temp_1 = CAR(drawing_element);
		points = Nil;
		ab_loop_list_ = CDR(drawing_element);
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		points = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		point = Nil;
		ab_loop_list__1 = points;
		ab_loopvar__2 = Nil;
		ab_loopvar__3 = Nil;
		ab_loopvar__4 = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		point = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		temp = FIXNUMP(FIRST(point)) ? FIRST(point) : 
			simple_eval_for_icon(FIRST(point));
		ab_loopvar__4 = 
			icon_editor_cons_1(scaled_icon_editor_point(temp,
			FIXNUMP(SECOND(point)) ? SECOND(point) : 
			simple_eval_for_icon(SECOND(point)),
			x_scale_of_target,y_scale_of_target),Nil);
		if (ab_loopvar__3)
		    M_CDR(ab_loopvar__3) = ab_loopvar__4;
		else
		    ab_loopvar__2 = ab_loopvar__4;
		ab_loopvar__3 = ab_loopvar__4;
		goto next_loop_1;
	      end_loop_1:
		temp = ab_loopvar__2;
		goto end_1;
		temp = Qnil;
	      end_1:;
		ab_loopvar__2 = icon_editor_cons_1(temp,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop;
	      end_loop:
		temp = ab_loopvar_;
		goto end_2;
		temp = Qnil;
	      end_2:;
		return icon_editor_cons_1(temp_1,temp);
	    }
	    else
		return copy_tree_using_icon_editor_conses_1(drawing_element);
	}
	else {
	    x = Nil;
	    ab_loop_list_ = drawing_element;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    x = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (CONSP(x) && EQ(M_CAR(x),Qarc)) {
		temp = M_CDR(x);
		temp_3 = CONSP(temp);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3 ?  !TRUEP(M_CDR(M_CDR(x))) : TRUEP(Nil)) {
		thing = M_CAR(M_CDR(x));
		if (CONSP(thing)) {
		    temp = CDR(thing);
		    temp_3 = CONSP(temp);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 = temp_3 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3 ? TRUEP(Nil) : TRUEP(Nil)) {
		x = CADR(x);
		temp = FIXNUMP(FIRST(x)) ? FIRST(x) : 
			simple_eval_for_icon(FIRST(x));
		temp = icon_editor_list_2(Qarc,
			scaled_icon_editor_point(temp,FIXNUMP(SECOND(x)) ? 
			SECOND(x) : simple_eval_for_icon(SECOND(x)),
			x_scale_of_target,y_scale_of_target));
	    }
	    else {
		if (CONSP(x)) {
		    temp = M_CDR(x);
		    temp_3 = CONSP(temp);
		}
		else
		    temp_3 = TRUEP(Nil);
		if (((temp_3 ?  !TRUEP(M_CDR(M_CDR(x))) : TRUEP(Nil)) ? 
			FIXNUMP(M_CAR(x)) : TRUEP(Nil)) ? 
			FIXNUMP(M_CAR(M_CDR(x))) : TRUEP(Nil)) {
		    temp = FIXNUMP(FIRST(x)) ? FIRST(x) : 
			    simple_eval_for_icon(FIRST(x));
		    temp = scaled_icon_editor_point(temp,
			    FIXNUMP(SECOND(x)) ? SECOND(x) : 
			    simple_eval_for_icon(SECOND(x)),
			    x_scale_of_target,y_scale_of_target);
		}
		else {
		    cdr_thing = Nil;
		    car_thing = Nil;
		    cadr_thing = Nil;
		    if (CONSP(x)) {
			cdr_thing = M_CDR(x);
			temp_3 = TRUEP(cdr_thing);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if ((temp_3 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
			    !TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
			car_thing = M_CAR(x);
			temp_3 = TRUEP(car_thing);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (temp_3) {
			cadr_thing = M_CAR(cdr_thing);
			temp_3 = TRUEP(cadr_thing);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (((temp_3 ?  !FIXNUMP(car_thing) ||  
			    !FIXNUMP(cadr_thing) : TRUEP(Nil)) ? 
			    CONSP(car_thing) && EQ(M_CAR(car_thing),Qplus) 
			    || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),
			    Qplus) || SYMBOLP(car_thing) || 
			    SYMBOLP(cadr_thing) : TRUEP(Nil)) ? TRUEP(Nil) 
			    : TRUEP(Nil)) {
			temp = FIXNUMP(FIRST(x)) ? FIRST(x) : 
				simple_eval_for_icon(FIRST(x));
			temp = scaled_icon_editor_point(temp,
				FIXNUMP(SECOND(x)) ? SECOND(x) : 
				simple_eval_for_icon(SECOND(x)),
				x_scale_of_target,y_scale_of_target);
		    }
		    else
			temp = copy_tree_using_icon_editor_conses_1(x);
		}
	    }
	    ab_loopvar__2 = icon_editor_cons_1(temp,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_2;
	  end_loop_2:
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
    }
}

/* COPY-DRAWING-ELEMENT-WITH-SLOT-VALUE-CONSES */
Object copy_drawing_element_with_slot_value_conses(drawing_element,
	    x_scale_of_target,y_scale_of_target,eval_power_points_p)
    Object drawing_element, x_scale_of_target, y_scale_of_target;
    Object eval_power_points_p;
{
    Object temp, name, unevaled_origin, origin, evaled_text_string;
    Object the_whole_string, font, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, stipple, point_1, point_2, temp_1, temp_2, points;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, point;
    Object ab_loop_list__1, ab_loopvar__3, ab_loopvar__4, x, thing, cdr_thing;
    Object car_thing, cadr_thing;
    char temp_3;

    x_note_fn_call(232,95);
    if (ATOM(drawing_element))
	return VALUES_1(drawing_element);
    else {
	temp = CAR(drawing_element);
	if (EQ(temp,Qimage)) {
	    name = SECOND(drawing_element);
	    unevaled_origin = THIRD(drawing_element);
	    if ( !TRUEP(unevaled_origin))
		origin = Nil;
	    else if (eval_power_points_p) {
		temp = FIXNUMP(FIRST(unevaled_origin)) ? 
			FIRST(unevaled_origin) : 
			simple_eval_for_icon(FIRST(unevaled_origin));
		origin = slot_value_list_2(temp,
			FIXNUMP(SECOND(unevaled_origin)) ? 
			SECOND(unevaled_origin) : 
			simple_eval_for_icon(SECOND(unevaled_origin)));
	    }
	    else
		origin = copy_tree_using_slot_value_conses_1(unevaled_origin);
	    if (IFIX(x_scale_of_target) == (SI_Long)4096L && 
		    IFIX(y_scale_of_target) == (SI_Long)4096L) {
		if (origin)
		    return slot_value_list_3(Qimage,name,origin);
		else
		    return slot_value_list_2(Qimage,name);
	    }
	    else
		return slot_value_list_4(Qimage,name,origin ? origin : 
			slot_value_list_2(FIX((SI_Long)0L),
			FIX((SI_Long)0L)),
			slot_value_list_2(x_scale_of_target,
			y_scale_of_target));
	}
	else if (EQ(temp,Qtext)) {
	    if (eval_power_points_p) {
		evaled_text_string = 
			simple_eval_for_icon(SECOND(drawing_element));
		the_whole_string = SYMBOLP(evaled_text_string) ? 
			stringw(string_constant_1) : 
			copy_text_string(evaled_text_string);
	    }
	    else {
		temp = SECOND(drawing_element);
		if (SYMBOLP(temp))
		    the_whole_string = SECOND(drawing_element);
		else
		    the_whole_string = 
			    copy_text_string(SECOND(drawing_element));
	    }
	    unevaled_origin = THIRD(drawing_element);
	    if (eval_power_points_p) {
		temp = FIXNUMP(FIRST(unevaled_origin)) ? 
			FIRST(unevaled_origin) : 
			simple_eval_for_icon(FIRST(unevaled_origin));
		origin = slot_value_list_2(temp,
			FIXNUMP(SECOND(unevaled_origin)) ? 
			SECOND(unevaled_origin) : 
			simple_eval_for_icon(SECOND(unevaled_origin)));
	    }
	    else
		origin = copy_tree_using_slot_value_conses_1(unevaled_origin);
	    font = eval_power_points_p ? 
		    simple_eval_for_icon(FOURTH(drawing_element)) : 
		    FOURTH(drawing_element);
	    if ( !TRUEP(x_scale_of_target) ||  !TRUEP(y_scale_of_target) 
		    || IFIX(x_scale_of_target) == (SI_Long)4096L && 
		    IFIX(y_scale_of_target) == (SI_Long)4096L)
		return slot_value_list_4(Qtext,the_whole_string,origin,
			copy_list_using_slot_value_conses_1(font));
	    else {
		gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = Qtext;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = the_whole_string;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = origin;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = copy_list_using_slot_value_conses_1(font);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = slot_value_list_2(x_scale_of_target,
			y_scale_of_target);
		M_CAR(gensymed_symbol_1) = car_new_value;
		return VALUES_1(gensymed_symbol);
	    }
	}
	else if (EQ(temp,Qstippled_area)) {
	    if (eval_power_points_p) {
		stipple = SECOND(drawing_element);
		point_1 = THIRD(drawing_element);
		point_2 = FOURTH(drawing_element);
		temp_1 = slot_value_list_2(Qstippled_area,stipple);
		if (point_1) {
		    temp = FIXNUMP(FIRST(point_1)) ? FIRST(point_1) : 
			    simple_eval_for_icon(FIRST(point_1));
		    temp_2 = slot_value_list_2(temp,
			    FIXNUMP(SECOND(point_1)) ? SECOND(point_1) : 
			    simple_eval_for_icon(SECOND(point_1)));
		    temp = FIXNUMP(FIRST(point_2)) ? FIRST(point_2) : 
			    simple_eval_for_icon(FIRST(point_2));
		    temp = slot_value_list_2(temp_2,slot_value_list_2(temp,
			    FIXNUMP(SECOND(point_2)) ? SECOND(point_2) : 
			    simple_eval_for_icon(SECOND(point_2))));
		}
		else
		    temp = Nil;
		return VALUES_1(nconc2(temp_1,temp));
	    }
	    else
		return copy_tree_using_slot_value_conses_1(drawing_element);
	}
	else if (EQ(temp,Qfilled_polygon)) {
	    if (eval_power_points_p) {
		temp_1 = CAR(drawing_element);
		points = Nil;
		ab_loop_list_ = CDR(drawing_element);
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		points = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		point = Nil;
		ab_loop_list__1 = points;
		ab_loopvar__2 = Nil;
		ab_loopvar__3 = Nil;
		ab_loopvar__4 = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		point = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		temp = FIXNUMP(FIRST(point)) ? FIRST(point) : 
			simple_eval_for_icon(FIRST(point));
		ab_loopvar__4 = 
			slot_value_cons_1(scaled_slot_value_point(temp,
			FIXNUMP(SECOND(point)) ? SECOND(point) : 
			simple_eval_for_icon(SECOND(point)),
			x_scale_of_target,y_scale_of_target),Nil);
		if (ab_loopvar__3)
		    M_CDR(ab_loopvar__3) = ab_loopvar__4;
		else
		    ab_loopvar__2 = ab_loopvar__4;
		ab_loopvar__3 = ab_loopvar__4;
		goto next_loop_1;
	      end_loop_1:
		temp = ab_loopvar__2;
		goto end_1;
		temp = Qnil;
	      end_1:;
		ab_loopvar__2 = slot_value_cons_1(temp,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop;
	      end_loop:
		temp = ab_loopvar_;
		goto end_2;
		temp = Qnil;
	      end_2:;
		return slot_value_cons_1(temp_1,temp);
	    }
	    else
		return copy_tree_using_slot_value_conses_1(drawing_element);
	}
	else {
	    x = Nil;
	    ab_loop_list_ = drawing_element;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    x = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (CONSP(x) && EQ(M_CAR(x),Qarc)) {
		temp = M_CDR(x);
		temp_3 = CONSP(temp);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3 ?  !TRUEP(M_CDR(M_CDR(x))) : TRUEP(Nil)) {
		thing = M_CAR(M_CDR(x));
		if (CONSP(thing)) {
		    temp = CDR(thing);
		    temp_3 = CONSP(temp);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 = temp_3 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3 ? TRUEP(eval_power_points_p) : TRUEP(Nil)) {
		x = CADR(x);
		temp = FIXNUMP(FIRST(x)) ? FIRST(x) : 
			simple_eval_for_icon(FIRST(x));
		temp = slot_value_list_2(Qarc,scaled_slot_value_point(temp,
			FIXNUMP(SECOND(x)) ? SECOND(x) : 
			simple_eval_for_icon(SECOND(x)),x_scale_of_target,
			y_scale_of_target));
	    }
	    else {
		if (CONSP(x)) {
		    temp = M_CDR(x);
		    temp_3 = CONSP(temp);
		}
		else
		    temp_3 = TRUEP(Nil);
		if (((temp_3 ?  !TRUEP(M_CDR(M_CDR(x))) : TRUEP(Nil)) ? 
			FIXNUMP(M_CAR(x)) : TRUEP(Nil)) ? 
			FIXNUMP(M_CAR(M_CDR(x))) : TRUEP(Nil)) {
		    temp = FIXNUMP(FIRST(x)) ? FIRST(x) : 
			    simple_eval_for_icon(FIRST(x));
		    temp = scaled_slot_value_point(temp,FIXNUMP(SECOND(x)) 
			    ? SECOND(x) : simple_eval_for_icon(SECOND(x)),
			    x_scale_of_target,y_scale_of_target);
		}
		else {
		    cdr_thing = Nil;
		    car_thing = Nil;
		    cadr_thing = Nil;
		    if (CONSP(x)) {
			cdr_thing = M_CDR(x);
			temp_3 = TRUEP(cdr_thing);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if ((temp_3 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
			    !TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
			car_thing = M_CAR(x);
			temp_3 = TRUEP(car_thing);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (temp_3) {
			cadr_thing = M_CAR(cdr_thing);
			temp_3 = TRUEP(cadr_thing);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (((temp_3 ?  !FIXNUMP(car_thing) ||  
			    !FIXNUMP(cadr_thing) : TRUEP(Nil)) ? 
			    CONSP(car_thing) && EQ(M_CAR(car_thing),Qplus) 
			    || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),
			    Qplus) || SYMBOLP(car_thing) || 
			    SYMBOLP(cadr_thing) : TRUEP(Nil)) ? 
			    TRUEP(eval_power_points_p) : TRUEP(Nil)) {
			temp = FIXNUMP(FIRST(x)) ? FIRST(x) : 
				simple_eval_for_icon(FIRST(x));
			temp = scaled_slot_value_point(temp,
				FIXNUMP(SECOND(x)) ? SECOND(x) : 
				simple_eval_for_icon(SECOND(x)),
				x_scale_of_target,y_scale_of_target);
		    }
		    else
			temp = copy_tree_using_slot_value_conses_1(x);
		}
	    }
	    ab_loopvar__2 = slot_value_cons_1(temp,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_2;
	  end_loop_2:
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
    }
}

static Object Qpolychrome;         /* polychrome */

static Object list_constant;       /* # */

static Object Qlines_old;          /* lines-old */

static Object Qlines;              /* lines */

/* CONVERT-LINE-DRAWING-DESCRIPTION-TO-LIST-OF-LAYERS */
Object convert_line_drawing_description_to_list_of_layers(line_drawing_description,
	    x_scale,y_scale)
    Object line_drawing_description, x_scale, y_scale;
{
    Object list_of_layers, tail_of_list_of_layers, region_and_name_alist;
    Object current_label, current_layer_elements;
    Object tail_of_current_layer_elements, drawing_element_or_label;
    Object ab_loop_list_, gensymed_symbol, temp, list_of_points_so_far;
    Object tail_of_list_of_points_so_far, point_or_arc;
    Object rest_of_drawing_element, point, point_for_arc, temp_1, temp_2;
    Object next_point_or_arc, next_x_qm, next_y_qm, scaled_point;
    SI_Long last_x_in_workspace, last_y_in_workspace;

    x_note_fn_call(232,96);
    list_of_layers = Nil;
    tail_of_list_of_layers = Nil;
    region_and_name_alist = Nil;
    current_label = Qforeground;
    current_layer_elements = Nil;
    tail_of_current_layer_elements = Nil;
    drawing_element_or_label = Nil;
    ab_loop_list_ = FIXNUMP(CAR(line_drawing_description)) ? 
	    CDDR(line_drawing_description) : line_drawing_description;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element_or_label = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SYMBOLP(drawing_element_or_label)) {
	if (current_layer_elements) {
	    gensymed_symbol = icon_editor_list_4(current_label,Nil,
		    current_layer_elements,tail_of_current_layer_elements);
	    gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	    if (list_of_layers) {
		if ( !TRUEP(tail_of_list_of_layers))
		    tail_of_list_of_layers = last(list_of_layers,_);
		M_CDR(tail_of_list_of_layers) = gensymed_symbol;
	    }
	    else
		list_of_layers = gensymed_symbol;
	    tail_of_list_of_layers = gensymed_symbol;
	    current_layer_elements = Nil;
	    tail_of_current_layer_elements = Nil;
	}
	current_label = drawing_element_or_label;
    }
    else {
	temp = CAR(drawing_element_or_label);
	if (EQ(temp,Qpolychrome))
	    region_and_name_alist = 
		    copy_tree_using_icon_editor_conses_1(CDR(drawing_element_or_label));
	else if (member_eql(temp,list_constant)) {
	    gensymed_symbol = 
		    copy_drawing_element_with_icon_editor_conses(drawing_element_or_label,
		    x_scale,y_scale);
	    gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	    if (current_layer_elements) {
		if ( !TRUEP(tail_of_current_layer_elements))
		    tail_of_current_layer_elements = 
			    last(current_layer_elements,_);
		M_CDR(tail_of_current_layer_elements) = gensymed_symbol;
	    }
	    else
		current_layer_elements = gensymed_symbol;
	    tail_of_current_layer_elements = gensymed_symbol;
	}
	else if (EQ(temp,Qlines_old)) {
	    last_x_in_workspace = (SI_Long)0L;
	    last_y_in_workspace = (SI_Long)0L;
	    list_of_points_so_far = Nil;
	    tail_of_list_of_points_so_far = Nil;
	    point_or_arc = Nil;
	    rest_of_drawing_element = CDR(drawing_element_or_label);
	  next_loop_1:
	    if ( !TRUEP(rest_of_drawing_element))
		goto end_loop_1;
	    point_or_arc = CAR(rest_of_drawing_element);
	    if (EQ(CAR(point_or_arc),Qarc)) {
		if (CDR(list_of_points_so_far)) {
		    gensymed_symbol = icon_editor_cons_1(Qlines,
			    list_of_points_so_far);
		    gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		    if (current_layer_elements) {
			if ( !TRUEP(tail_of_current_layer_elements))
			    tail_of_current_layer_elements = 
				    last(current_layer_elements,_);
			M_CDR(tail_of_current_layer_elements) = 
				gensymed_symbol;
		    }
		    else
			current_layer_elements = gensymed_symbol;
		    tail_of_current_layer_elements = gensymed_symbol;
		}
		else
		    reclaim_icon_editor_slot_value(list_of_points_so_far);
		list_of_points_so_far = Nil;
		tail_of_list_of_points_so_far = Nil;
		point = SECOND(point_or_arc);
		point_for_arc = scaled_icon_editor_point(CAR(point),
			SECOND(point),x_scale,y_scale);
		temp_1 = icon_editor_list_2(FIX(last_x_in_workspace),
			FIX(last_y_in_workspace));
		temp_2 = icon_editor_list_2(Qarc,point_for_arc);
		next_point_or_arc = SECOND(rest_of_drawing_element);
		next_x_qm = FIRST(next_point_or_arc);
		next_y_qm = SECOND(next_point_or_arc);
		temp = FIXNUMP(next_x_qm) ? next_x_qm : FIX((SI_Long)0L);
		gensymed_symbol = icon_editor_list_4(Qlines,temp_1,temp_2,
			scaled_icon_editor_point(temp,FIXNUMP(next_y_qm) ? 
			next_y_qm : FIX((SI_Long)0L),x_scale,y_scale));
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (current_layer_elements) {
		    if ( !TRUEP(tail_of_current_layer_elements))
			tail_of_current_layer_elements = 
				last(current_layer_elements,_);
		    M_CDR(tail_of_current_layer_elements) = gensymed_symbol;
		}
		else
		    current_layer_elements = gensymed_symbol;
		tail_of_current_layer_elements = gensymed_symbol;
		last_x_in_workspace = IFIX(FIRST(point_for_arc));
		last_y_in_workspace = IFIX(SECOND(point_for_arc));
	    }
	    else {
		scaled_point = scaled_icon_editor_point(CAR(point_or_arc),
			SECOND(point_or_arc),x_scale,y_scale);
		last_x_in_workspace = IFIX(FIRST(scaled_point));
		last_y_in_workspace = IFIX(SECOND(scaled_point));
		gensymed_symbol = scaled_point;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (list_of_points_so_far) {
		    if ( !TRUEP(tail_of_list_of_points_so_far))
			tail_of_list_of_points_so_far = 
				last(list_of_points_so_far,_);
		    M_CDR(tail_of_list_of_points_so_far) = gensymed_symbol;
		}
		else
		    list_of_points_so_far = gensymed_symbol;
		tail_of_list_of_points_so_far = gensymed_symbol;
	    }
	    rest_of_drawing_element = M_CDR(rest_of_drawing_element);
	    goto next_loop_1;
	  end_loop_1:
	    if (CDR(list_of_points_so_far)) {
		gensymed_symbol = icon_editor_cons_1(Qlines,
			list_of_points_so_far);
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (current_layer_elements) {
		    if ( !TRUEP(tail_of_current_layer_elements))
			tail_of_current_layer_elements = 
				last(current_layer_elements,_);
		    M_CDR(tail_of_current_layer_elements) = gensymed_symbol;
		}
		else
		    current_layer_elements = gensymed_symbol;
		tail_of_current_layer_elements = gensymed_symbol;
	    }
	    else
		reclaim_icon_editor_slot_value(list_of_points_so_far);
	}
    }
    goto next_loop;
  end_loop:
    if (current_layer_elements) {
	gensymed_symbol = icon_editor_list_4(current_label,Nil,
		current_layer_elements,tail_of_current_layer_elements);
	gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	if (list_of_layers) {
	    if ( !TRUEP(tail_of_list_of_layers))
		tail_of_list_of_layers = last(list_of_layers,_);
	    M_CDR(tail_of_list_of_layers) = gensymed_symbol;
	}
	else
	    list_of_layers = gensymed_symbol;
	tail_of_list_of_layers = gensymed_symbol;
    }
    return VALUES_2(list_of_layers,region_and_name_alist);
}

/* ADD-VARIABLE-SPEC-LIST-TO-LINE-DRAWING-DESCRIPTION */
Object add_variable_spec_list_to_line_drawing_description(description_without_size_and_variables,
	    variable_spec_list)
    Object description_without_size_and_variables, variable_spec_list;
{
    Object rest_line_drawing_description, front_element, ab_loop_it_, temp;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, cdr_new_value;

    x_note_fn_call(232,97);
    rest_line_drawing_description = description_without_size_and_variables;
    front_element = Nil;
    ab_loop_it_ = Nil;
    temp = CAR(description_without_size_and_variables);
    if (EQ(CAR(temp),Qpolychrome)) {
	slot_value_push_modify_macro_arg = 
		copy_for_slot_value(variable_spec_list);
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDR(description_without_size_and_variables);
	cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	M_CDR(description_without_size_and_variables) = cdr_new_value;
	return VALUES_1(T);
    }
  next_loop:
    if ( !TRUEP(rest_line_drawing_description))
	goto end_loop;
    front_element = CAR(rest_line_drawing_description);
    if (CONSP(front_element) && EQ(CAR(front_element),Qpolychrome)) {
	slot_value_push_modify_macro_arg = 
		copy_for_slot_value(variable_spec_list);
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDR(rest_line_drawing_description);
	cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	M_CDR(rest_line_drawing_description) = cdr_new_value;
	return VALUES_1(T);
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    rest_line_drawing_description = M_CDR(rest_line_drawing_description);
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* ADD-BACKGROUND-LAYER-TO-LINE-DRAWING-DESCRIPTION */
Object add_background_layer_to_line_drawing_description(description_without_size_and_variables,
	    background_layer_info)
    Object description_without_size_and_variables, background_layer_info;
{
    Object rest_line_drawing_description, front_element, ab_loop_it_, temp;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, cdr_new_value;

    x_note_fn_call(232,98);
    rest_line_drawing_description = description_without_size_and_variables;
    front_element = Nil;
    ab_loop_it_ = Nil;
    temp = CAR(description_without_size_and_variables);
    if (EQ(CAR(temp),Qpolychrome)) {
	slot_value_push_modify_macro_arg = background_layer_info;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDR(description_without_size_and_variables);
	cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	M_CDR(description_without_size_and_variables) = cdr_new_value;
	return VALUES_1(T);
    }
  next_loop:
    if ( !TRUEP(rest_line_drawing_description))
	goto end_loop;
    front_element = CAR(rest_line_drawing_description);
    if (CONSP(front_element) && EQ(CAR(front_element),Qpolychrome)) {
	slot_value_push_modify_macro_arg = background_layer_info;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDR(rest_line_drawing_description);
	cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	M_CDR(rest_line_drawing_description) = cdr_new_value;
	return VALUES_1(T);
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    rest_line_drawing_description = M_CDR(rest_line_drawing_description);
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

static Object Qlight_stipple;      /* light-stipple */

static Object Qmedium_stipple;     /* medium-stipple */

static Object Qdark_stipple;       /* dark-stipple */

static Object Qlight_texture;      /* light-texture */

static Object Qmedium_texture;     /* medium-texture */

static Object Qdark_texture;       /* dark-texture */

static Object Qstipple;            /* stipple */

static Object Qbackground_layer;   /* background-layer */

/* CONVERT-LIST-OF-LAYERS-TO-LINE-DRAWING-DESCRIPTION */
Object convert_list_of_layers_to_line_drawing_description(list_of_layers,
	    region_and_name_alist,variable_spec_list,background_layer,
	    scaled_icon_width,scaled_icon_height,x_scale_init,y_scale_init,
	    omit_size_p,eval_power_points_p,stipple_spec)
    Object list_of_layers, region_and_name_alist, variable_spec_list;
    Object background_layer, scaled_icon_width, scaled_icon_height;
    Object x_scale_init, y_scale_init, omit_size_p, eval_power_points_p;
    Object stipple_spec;
{
    Object line_drawing_description, tail_of_line_drawing_description;
    Object filtered_alist, tail_of_filtered_alist_qm, background_layer_info;
    Object icon_width, temp, icon_height, stipple_header_qm;
    Object drawing_elements_of_layer, current_label, color_qm, current_layer;
    Object ab_loop_list_, temp_2, gensymed_symbol, drawing_element;
    Object ab_loop_list__1, current_icon_untransformed_width;
    Object current_icon_untransformed_height, current_icon_variables_plist;
    Object current_icon_variables_override_plist, description_without_size;
    SI_Long x_scale, y_scale, temp_1;
    char temp_3;
    Declare_special(4);

    x_note_fn_call(232,99);
    x_scale = IFIX(x_scale_init);
    y_scale = IFIX(y_scale_init);
    line_drawing_description = Nil;
    tail_of_line_drawing_description = Nil;
    filtered_alist = Nil;
    tail_of_filtered_alist_qm = Nil;
    background_layer_info = Nil;
    if (x_scale == (SI_Long)4096L)
	icon_width = scaled_icon_width;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    scaled_icon_width) && FIXNUM_LT(scaled_icon_width,
	    Isqrt_of_most_positive_fixnum)))
	icon_width = inverse_scalef_function(FIX(x_scale),scaled_icon_width);
    else if (IFIX(scaled_icon_width) >= (SI_Long)0L) {
	temp = FIX(((IFIX(scaled_icon_width) << (SI_Long)12L) + (x_scale 
		>>  -  - (SI_Long)1L)) / x_scale);
	icon_width = temp;
    }
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(scaled_icon_width)) << (SI_Long)12L) 
		+ (x_scale >>  -  - (SI_Long)1L)) / x_scale;
	temp = FIXNUM_NEGATE(FIX(temp_1));
	icon_width = temp;
    }
    if (y_scale == (SI_Long)4096L)
	icon_height = scaled_icon_height;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    scaled_icon_height) && FIXNUM_LT(scaled_icon_height,
	    Isqrt_of_most_positive_fixnum)))
	icon_height = inverse_scalef_function(FIX(y_scale),scaled_icon_height);
    else if (IFIX(scaled_icon_height) >= (SI_Long)0L) {
	temp = FIX(((IFIX(scaled_icon_height) << (SI_Long)12L) + (y_scale 
		>>  -  - (SI_Long)1L)) / y_scale);
	icon_height = temp;
    }
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(scaled_icon_height)) << 
		(SI_Long)12L) + (y_scale >>  -  - (SI_Long)1L)) / y_scale;
	temp = FIXNUM_NEGATE(FIX(temp_1));
	icon_height = temp;
    }
    stipple_header_qm = EQ(stipple_spec,Qlight_stipple) || EQ(stipple_spec,
	    Qmedium_stipple) || EQ(stipple_spec,Qdark_stipple) || 
	    EQ(stipple_spec,Qlight_texture) || EQ(stipple_spec,
	    Qmedium_texture) || EQ(stipple_spec,Qdark_texture) ? 
	    slot_value_list_2(Qstipple,stipple_spec) : Nil;
    drawing_elements_of_layer = Nil;
    current_label = Nil;
    color_qm = Nil;
    current_layer = Nil;
    ab_loop_list_ = list_of_layers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    current_layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    current_label = FIRST(current_layer);
    if (EQ(current_label,Qforeground))
	color_qm = Qforeground;
    else {
	temp = assq_function(current_label,region_and_name_alist);
	color_qm = CDR(temp);
    }
    temp = CDDR(current_layer);
    drawing_elements_of_layer = copy_list_using_gensym_conses_1(CAR(temp));
    if (drawing_elements_of_layer) {
	drawing_elements_of_layer = 
		partially_sort_drawing_elements_stippled_areas_first(drawing_elements_of_layer);
	if ( !TRUEP(assq_function(current_label,filtered_alist))) {
	    if (color_or_metacolor_p(current_label)) {
		temp_2 = current_label;
		temp = color_qm;
		if (temp);
		else
		    temp = current_label;
		filtered_alist = 
			slot_value_cons_1(slot_value_cons_1(temp_2,temp),
			filtered_alist);
		if ( !TRUEP(tail_of_filtered_alist_qm))
		    tail_of_filtered_alist_qm = filtered_alist;
	    }
	    else {
		temp_2 = current_label;
		temp = color_qm;
		if (temp);
		else
		    temp = current_label;
		gensymed_symbol = slot_value_cons_1(temp_2,temp);
		gensymed_symbol = slot_value_cons_1(gensymed_symbol,Nil);
		if (filtered_alist) {
		    if ( !TRUEP(tail_of_filtered_alist_qm))
			tail_of_filtered_alist_qm = last(filtered_alist,_);
		    M_CDR(tail_of_filtered_alist_qm) = gensymed_symbol;
		}
		else
		    filtered_alist = gensymed_symbol;
		tail_of_filtered_alist_qm = gensymed_symbol;
	    }
	}
	gensymed_symbol = FIRST(current_layer);
	gensymed_symbol = slot_value_cons_1(gensymed_symbol,Nil);
	if (line_drawing_description) {
	    if ( !TRUEP(tail_of_line_drawing_description))
		tail_of_line_drawing_description = 
			last(line_drawing_description,_);
	    M_CDR(tail_of_line_drawing_description) = gensymed_symbol;
	}
	else
	    line_drawing_description = gensymed_symbol;
	tail_of_line_drawing_description = gensymed_symbol;
	drawing_element = Nil;
	ab_loop_list__1 = drawing_elements_of_layer;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	drawing_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	current_icon_untransformed_width = icon_width;
	PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
		3);
	  current_icon_untransformed_height = icon_height;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
		  2);
	    current_icon_variables_plist = CDR(variable_spec_list);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
		    1);
	      current_icon_variables_override_plist = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
		      0);
		gensymed_symbol = 
			copy_drawing_element_with_slot_value_conses(drawing_element,
			FIX(x_scale),FIX(y_scale),eval_power_points_p);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	gensymed_symbol = slot_value_cons_1(gensymed_symbol,Nil);
	if (line_drawing_description) {
	    if ( !TRUEP(tail_of_line_drawing_description))
		tail_of_line_drawing_description = 
			last(line_drawing_description,_);
	    M_CDR(tail_of_line_drawing_description) = gensymed_symbol;
	}
	else
	    line_drawing_description = gensymed_symbol;
	tail_of_line_drawing_description = gensymed_symbol;
	goto next_loop_1;
      end_loop_1:;
	reclaim_gensym_list_1(drawing_elements_of_layer);
    }
    goto next_loop;
  end_loop:;
    if (stipple_header_qm)
	line_drawing_description = slot_value_cons_1(stipple_header_qm,
		line_drawing_description);
    if (EQ(CAR(line_drawing_description),Qforeground)) {
	temp_3 =  !TRUEP(region_and_name_alist);
	if (temp_3);
	else if ( !TRUEP(CDR(filtered_alist))) {
	    temp = CAR(filtered_alist);
	    temp_3 = EQ(CAR(temp),Qforeground);
	}
	else
	    temp_3 = TRUEP(Nil);
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	temp = CDR(line_drawing_description);
	reclaim_slot_value_cons_1(line_drawing_description);
	reclaim_slot_value_tree_1(filtered_alist);
	description_without_size = temp;
    }
    else
	description_without_size = 
		slot_value_cons_1(slot_value_cons_1(Qpolychrome,
		filtered_alist),line_drawing_description);
    background_layer_info = copy_for_slot_value(background_layer);
    background_layer_info = background_layer_info ? 
	    slot_value_list_2(Qbackground_layer,background_layer_info) : 
	    slot_value_cons_1(Qbackground_layer,Nil);
    if ( 
	    !TRUEP(add_background_layer_to_line_drawing_description(description_without_size,
	    background_layer_info)))
	description_without_size = slot_value_cons_1(background_layer_info,
		description_without_size);
    if ( 
	    !TRUEP(add_variable_spec_list_to_line_drawing_description(description_without_size,
	    variable_spec_list)))
	description_without_size = 
		slot_value_cons_1(copy_for_slot_value(variable_spec_list),
		description_without_size);
    if (omit_size_p)
	return VALUES_1(description_without_size);
    else
	return slot_value_cons_1(scaled_icon_width,
		slot_value_cons_1(scaled_icon_height,
		description_without_size));
}

/* PARTIALLY-SORT-DRAWING-ELEMENTS-STIPPLED-AREAS-FIRST */
Object partially_sort_drawing_elements_stippled_areas_first(drawing_elements)
    Object drawing_elements;
{
    Object removed, prev_elts, elts, element, cdr_new_value;
    char temp;

    x_note_fn_call(232,100);
    removed = Nil;
  next_loop:
    prev_elts = Nil;
    elts = drawing_elements;
    element = Nil;
  next_loop_1:
    if ( !TRUEP(elts))
	goto end_loop;
    element = CAR(elts);
    if (CONSP(element) && EQ(CAR(element),Qstippled_area)) {
	removed = nconc2(removed,elts);
	if (prev_elts) {
	    cdr_new_value = CDR(elts);
	    M_CDR(prev_elts) = cdr_new_value;
	}
	else
	    drawing_elements = CDR(elts);
	M_CDR(elts) = Nil;
	temp = TRUEP(T);
	goto end_1;
    }
    prev_elts = elts;
    elts = M_CDR(elts);
    goto next_loop_1;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp)
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(nconc2(removed,drawing_elements));
    return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qtexttured_area;     /* texttured-area */

static Object Qoutline;            /* outline */

static Object Qcircle;             /* circle */

static Object Qfilled_circle;      /* filled-circle */

/* CONVERT-TO-FILLED-DRAWING-ELEMENTS */
Object convert_to_filled_drawing_elements(outlined_drawing_elements)
    Object outlined_drawing_elements;
{
    Object drawing_element, ab_loop_list_, ab_loop_it_;
    Object filled_drawing_elements, tail_of_filled_drawing_elements, temp_1;
    Object gensymed_symbol, list_of_points, decomposed_polygon_qm;
    char temp;

    x_note_fn_call(232,101);
    drawing_element = Nil;
    ab_loop_list_ = outlined_drawing_elements;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = memq_function(CAR(drawing_element),list_constant_1);
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	filled_drawing_elements = Nil;
	tail_of_filled_drawing_elements = Nil;
	drawing_element = Nil;
	ab_loop_list_ = outlined_drawing_elements;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	drawing_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = CAR(drawing_element);
	if (member_eql(temp_1,list_constant_2))
	    gensymed_symbol = 
		    copy_tree_using_icon_editor_conses_1(drawing_element);
	else if (EQ(temp_1,Qtext))
	    gensymed_symbol = 
		    copy_drawing_element_with_icon_editor_conses(drawing_element,
		    Nil,Nil);
	else if (EQ(temp_1,Qstippled_area))
	    gensymed_symbol = 
		    copy_drawing_element_with_icon_editor_conses(drawing_element,
		    Nil,Nil);
	else if (EQ(temp_1,Qtexttured_area))
	    gensymed_symbol = 
		    copy_drawing_element_with_icon_editor_conses(drawing_element,
		    Nil,Nil);
	else if (EQ(temp_1,Qoutline)) {
	    list_of_points = 
		    copy_tree_using_icon_editor_conses_1(CDR(drawing_element));
	    decomposed_polygon_qm = Nil;
	    if ( !TRUEP(clockwise_polygon_p(list_of_points)))
		list_of_points = nreverse(list_of_points);
	    if (CDDR(drawing_element)) {
		decomposed_polygon_qm = 
			decompose_polygon_using_icon_editor_conses(list_of_points);
		temp = TRUEP(decomposed_polygon_qm);
	    }
	    else
		temp = TRUEP(Nil);
	    gensymed_symbol = temp ? icon_editor_cons_1(Qfilled_polygon,
		    icon_editor_cons_1(list_of_points,
		    decomposed_polygon_qm)) : 
		    icon_editor_cons_1(CAR(drawing_element),list_of_points);
	}
	else if (EQ(temp_1,Qcircle)) {
	    M_CAR(drawing_element) = Qfilled_circle;
	    temp_1 = copy_tree_using_icon_editor_conses_1(drawing_element);
	    M_CAR(drawing_element) = Qcircle;
	    gensymed_symbol = temp_1;
	}
	else
	    gensymed_symbol = Qnil;
	gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	if (filled_drawing_elements) {
	    if ( !TRUEP(tail_of_filled_drawing_elements))
		tail_of_filled_drawing_elements = 
			last(filled_drawing_elements,_);
	    M_CDR(tail_of_filled_drawing_elements) = gensymed_symbol;
	}
	else
	    filled_drawing_elements = gensymed_symbol;
	tail_of_filled_drawing_elements = gensymed_symbol;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(filled_drawing_elements);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object Qsolid_rectangle;    /* solid-rectangle */

/* CONVERT-TO-OUTLINED-DRAWING-ELEMENTS */
Object convert_to_outlined_drawing_elements(filled_drawing_elements)
    Object filled_drawing_elements;
{
    Object drawing_element, ab_loop_list_, ab_loop_it_;
    Object outlined_drawing_elements, tail_of_outlined_drawing_elements;
    Object temp_1, gensymed_symbol, point_1, point_2, x0, y0_1, x1, y1_1;
    Object gensymed_symbol_1, car_new_value;
    char temp;

    x_note_fn_call(232,102);
    drawing_element = Nil;
    ab_loop_list_ = filled_drawing_elements;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = memq_function(CAR(drawing_element),list_constant_3);
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	outlined_drawing_elements = Nil;
	tail_of_outlined_drawing_elements = Nil;
	drawing_element = Nil;
	ab_loop_list_ = filled_drawing_elements;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	drawing_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = CAR(drawing_element);
	if (member_eql(temp_1,list_constant_4))
	    gensymed_symbol = 
		    copy_tree_using_icon_editor_conses_1(drawing_element);
	else if (EQ(temp_1,Qtext))
	    gensymed_symbol = 
		    copy_drawing_element_with_icon_editor_conses(drawing_element,
		    Nil,Nil);
	else if (EQ(temp_1,Qstippled_area))
	    gensymed_symbol = 
		    copy_drawing_element_with_icon_editor_conses(drawing_element,
		    Nil,Nil);
	else if (EQ(temp_1,Qsolid_rectangle)) {
	    point_1 = SECOND(drawing_element);
	    point_2 = THIRD(drawing_element);
	    x0 = FIRST(point_1);
	    y0_1 = SECOND(point_1);
	    x1 = FIRST(point_2);
	    y1_1 = SECOND(point_2);
	    gensymed_symbol = make_icon_editor_list_1(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qoutline;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = 
		    icon_editor_list_2(copy_tree_using_icon_editor_conses_1(x0),
		    copy_tree_using_icon_editor_conses_1(y0_1));
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = 
		    icon_editor_list_2(copy_tree_using_icon_editor_conses_1(x0),
		    copy_tree_using_icon_editor_conses_1(y1_1));
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = 
		    icon_editor_list_2(copy_tree_using_icon_editor_conses_1(x1),
		    copy_tree_using_icon_editor_conses_1(y1_1));
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = 
		    icon_editor_list_2(copy_tree_using_icon_editor_conses_1(x1),
		    copy_tree_using_icon_editor_conses_1(y0_1));
	    M_CAR(gensymed_symbol_1) = car_new_value;
	}
	else if (EQ(temp_1,Qfilled_polygon))
	    gensymed_symbol = icon_editor_cons_1(Qoutline,
		    copy_tree_using_icon_editor_conses_1(SECOND(drawing_element)));
	else if (EQ(temp_1,Qfilled_circle)) {
	    M_CAR(drawing_element) = Qcircle;
	    temp_1 = copy_tree_using_icon_editor_conses_1(drawing_element);
	    M_CAR(drawing_element) = Qfilled_circle;
	    gensymed_symbol = temp_1;
	}
	else
	    gensymed_symbol = Qnil;
	gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	if (outlined_drawing_elements) {
	    if ( !TRUEP(tail_of_outlined_drawing_elements))
		tail_of_outlined_drawing_elements = 
			last(outlined_drawing_elements,_);
	    M_CDR(tail_of_outlined_drawing_elements) = gensymed_symbol;
	}
	else
	    outlined_drawing_elements = gensymed_symbol;
	tail_of_outlined_drawing_elements = gensymed_symbol;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(outlined_drawing_elements);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-INFIX-TO-PREFIX */
Object convert_infix_to_prefix(infix_variables)
    Object infix_variables;
{
    Object initial_minus_p, result_1, rest_variables, operation, variable;
    Object ab_loop_list_, temp;

    x_note_fn_call(232,103);
    initial_minus_p = Nil;
    if ( !TRUEP(SECOND(infix_variables)))
	result_1 = CAR(infix_variables);
    else if ( !TRUEP(THIRD(infix_variables)))
	result_1 = copy_for_slot_value(infix_variables);
    else if (EQ(SECOND(infix_variables),Qminus))
	result_1 = slot_value_list_3(Qplus,CAR(infix_variables),
		slot_value_list_2(Qminus,THIRD(infix_variables)));
    else if (EQ(CAR(infix_variables),Qminus) && EQ(THIRD(infix_variables),
	    Qplus)) {
	initial_minus_p = T;
	result_1 = slot_value_list_3(Qplus,slot_value_list_2(Qminus,
		SECOND(infix_variables)),FOURTH(infix_variables));
    }
    else if (EQ(CAR(infix_variables),Qminus)) {
	initial_minus_p = T;
	result_1 = slot_value_list_3(Qplus,slot_value_list_2(Qminus,
		SECOND(infix_variables)),slot_value_list_2(Qminus,
		FOURTH(infix_variables)));
    }
    else
	result_1 = slot_value_list_3(SECOND(infix_variables),
		CAR(infix_variables),THIRD(infix_variables));
    rest_variables = initial_minus_p ? CDDDDR(infix_variables) : 
	    CDDDR(infix_variables);
    operation = Nil;
    variable = Nil;
    ab_loop_list_ = rest_variables;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    operation = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    variable = CAR(temp);
    if (EQ(operation,Qplus))
	result_1 = slot_value_list_3(Qplus,result_1,variable);
    else if (EQ(operation,Qminus))
	result_1 = slot_value_list_3(Qplus,result_1,
		slot_value_list_2(Qminus,variable));
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* SIMPLIFY-POINT-EXPRESSION */
Object simplify_point_expression(point_expression)
    Object point_expression;
{
    Object resolved_constants, infix_variables, prefix_variables;

    x_note_fn_call(232,104);
    resolved_constants = resolve_constants(point_expression);
    infix_variables = extract_constants(point_expression);
    prefix_variables = convert_infix_to_prefix(infix_variables);
    reclaim_slot_value(infix_variables);
    if (prefix_variables &&  !EQ(resolved_constants,FIX((SI_Long)0L)))
	return slot_value_list_3(Qplus,prefix_variables,resolved_constants);
    else if (prefix_variables)
	return VALUES_1(prefix_variables);
    else
	return VALUES_1(resolved_constants);
}

/* INCFF-POWER-POINT */
Object incff_power_point(power_point,x_offset,y_offset)
    Object power_point, x_offset, y_offset;
{
    Object point_x, point_y, temp, incff_1_arg;

    x_note_fn_call(232,105);
    point_x = CAR(power_point);
    point_y = SECOND(power_point);
    if (SYMBOLP(point_x) || CONSP(point_x)) {
	temp = simplify_point_expression(slot_value_list_3(Qplus,point_x,
		x_offset));
	M_FIRST(power_point) = temp;
	reclaim_slot_value(point_x);
    }
    else {
	incff_1_arg = x_offset;
	temp = FIXNUM_ADD(CAR(power_point),incff_1_arg);
	M_CAR(power_point) = temp;
    }
    if (SYMBOLP(point_y) || CONSP(point_y)) {
	temp = simplify_point_expression(slot_value_list_3(Qplus,point_y,
		y_offset));
	M_SECOND(power_point) = temp;
	return reclaim_slot_value(point_y);
    }
    else {
	incff_1_arg = y_offset;
	temp = FIXNUM_ADD(SECOND(power_point),incff_1_arg);
	return VALUES_1(M_SECOND(power_point) = temp);
    }
}

/* SHIFT-POINTS-IN-PLACE */
Object shift_points_in_place(list_of_points,x_offset,y_offset)
    Object list_of_points, x_offset, y_offset;
{
    Object point_or_arc, ab_loop_list_, temp, thing, cdr_thing, car_thing;
    Object cadr_thing, temp_2;
    char temp_1;

    x_note_fn_call(232,106);
    point_or_arc = Nil;
    ab_loop_list_ = list_of_points;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    point_or_arc = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(point_or_arc) && EQ(M_CAR(point_or_arc),Qarc)) {
	temp = M_CDR(point_or_arc);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(point_or_arc))) : TRUEP(Nil)) {
	thing = M_CAR(M_CDR(point_or_arc));
	if (CONSP(thing)) {
	    temp = CDR(thing);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	shift_points_in_place(CDR(point_or_arc),x_offset,y_offset);
    else {
	cdr_thing = Nil;
	car_thing = Nil;
	cadr_thing = Nil;
	if (CONSP(point_or_arc)) {
	    cdr_thing = M_CDR(point_or_arc);
	    temp_1 = TRUEP(cdr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
		!TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
	    car_thing = M_CAR(point_or_arc);
	    temp_1 = TRUEP(car_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    cadr_thing = M_CAR(cdr_thing);
	    temp_1 = TRUEP(cadr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ?  !FIXNUMP(car_thing) ||  !FIXNUMP(cadr_thing) : 
		TRUEP(Nil)) ? CONSP(car_thing) && EQ(M_CAR(car_thing),
		Qplus) || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),Qplus) 
		|| SYMBOLP(car_thing) || SYMBOLP(cadr_thing) : TRUEP(Nil))
	    incff_power_point(point_or_arc,x_offset,y_offset);
	else {
	    if (CONSP(point_or_arc)) {
		temp = M_CDR(point_or_arc);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (((temp_1 ?  !TRUEP(M_CDR(M_CDR(point_or_arc))) : 
		    TRUEP(Nil)) ? FIXNUMP(M_CAR(point_or_arc)) : 
		    TRUEP(Nil)) ? FIXNUMP(M_CAR(M_CDR(point_or_arc))) : 
		    TRUEP(Nil)) {
		temp_2 = FIXNUM_ADD(FIRST(point_or_arc),x_offset);
		M_FIRST(point_or_arc) = temp_2;
		temp_2 = FIXNUM_ADD(SECOND(point_or_arc),y_offset);
		M_SECOND(point_or_arc) = temp_2;
	    }
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_5;     /* # */

/* SHIFT-DRAWING-ELEMENTS-IN-PLACE */
Object shift_drawing_elements_in_place(list_of_drawing_elements,x_offset,
	    y_offset)
    Object list_of_drawing_elements, x_offset, y_offset;
{
    Object drawing_element, ab_loop_list_, temp, point_qm, cdr_thing;
    Object car_thing, cadr_thing, incff_1_arg, temp_2, point, triangle;
    Object ab_loop_list__1;
    char temp_1;

    x_note_fn_call(232,107);
    drawing_element = Nil;
    ab_loop_list_ = list_of_drawing_elements;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CAR(drawing_element);
    if (member_eql(temp,list_constant_5))
	shift_points_in_place(CDR(drawing_element),x_offset,y_offset);
    else if (EQ(temp,Qimage)) {
	point_qm = THIRD(drawing_element);
	if ( !TRUEP(point_qm))
	    drawing_element = nconc2(drawing_element,
		    icon_editor_cons_1(icon_editor_list_2(x_offset,
		    y_offset),Nil));
	else {
	    cdr_thing = Nil;
	    car_thing = Nil;
	    cadr_thing = Nil;
	    if (CONSP(point_qm)) {
		cdr_thing = M_CDR(point_qm);
		temp_1 = TRUEP(cdr_thing);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ((temp_1 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
		    !TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
		car_thing = M_CAR(point_qm);
		temp_1 = TRUEP(car_thing);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		cadr_thing = M_CAR(cdr_thing);
		temp_1 = TRUEP(cadr_thing);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ((temp_1 ?  !FIXNUMP(car_thing) ||  !FIXNUMP(cadr_thing) : 
		    TRUEP(Nil)) ? CONSP(car_thing) && EQ(M_CAR(car_thing),
		    Qplus) || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),
		    Qplus) || SYMBOLP(car_thing) || SYMBOLP(cadr_thing) : 
		    TRUEP(Nil))
		incff_power_point(point_qm,x_offset,y_offset);
	    else {
		if (CONSP(point_qm)) {
		    temp = M_CDR(point_qm);
		    temp_1 = CONSP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (((temp_1 ?  !TRUEP(M_CDR(M_CDR(point_qm))) : 
			TRUEP(Nil)) ? FIXNUMP(M_CAR(point_qm)) : 
			TRUEP(Nil)) ? FIXNUMP(M_CAR(M_CDR(point_qm))) : 
			TRUEP(Nil)) {
		    incff_1_arg = x_offset;
		    temp_2 = FIXNUM_ADD(FIRST(point_qm),incff_1_arg);
		    M_FIRST(point_qm) = temp_2;
		    incff_1_arg = y_offset;
		    temp_2 = FIXNUM_ADD(SECOND(point_qm),incff_1_arg);
		    M_SECOND(point_qm) = temp_2;
		}
	    }
	}
    }
    else if (EQ(temp,Qtext)) {
	point = THIRD(drawing_element);
	cdr_thing = Nil;
	car_thing = Nil;
	cadr_thing = Nil;
	if (CONSP(point)) {
	    cdr_thing = M_CDR(point);
	    temp_1 = TRUEP(cdr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
		!TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
	    car_thing = M_CAR(point);
	    temp_1 = TRUEP(car_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    cadr_thing = M_CAR(cdr_thing);
	    temp_1 = TRUEP(cadr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ?  !FIXNUMP(car_thing) ||  !FIXNUMP(cadr_thing) : 
		TRUEP(Nil)) ? CONSP(car_thing) && EQ(M_CAR(car_thing),
		Qplus) || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),Qplus) 
		|| SYMBOLP(car_thing) || SYMBOLP(cadr_thing) : TRUEP(Nil))
	    incff_power_point(point,x_offset,y_offset);
	else {
	    incff_1_arg = x_offset;
	    temp_2 = FIXNUM_ADD(FIRST(point),incff_1_arg);
	    M_FIRST(point) = temp_2;
	    incff_1_arg = y_offset;
	    temp_2 = FIXNUM_ADD(SECOND(point),incff_1_arg);
	    M_SECOND(point) = temp_2;
	}
    }
    else if (EQ(temp,Qfilled_polygon)) {
	shift_points_in_place(SECOND(drawing_element),x_offset,y_offset);
	triangle = Nil;
	ab_loop_list__1 = CDDR(drawing_element);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	triangle = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	shift_points_in_place(triangle,x_offset,y_offset);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CHANGE-STIPPLE-OF-CURRENT-LAYER */
Object change_stipple_of_current_layer(icon_editor_engine,new_stipple)
    Object icon_editor_engine, new_stipple;
{
    Object layer, temp, sublist, drawing_element, old_stipple_place;
    Object old_stipple, new_drawing_element, drawing_elements, gensymed_symbol;
    Object temp_1, car_new_value;

    x_note_fn_call(232,108);
    layer = ISVREF(icon_editor_engine,(SI_Long)6L);
    temp = CDDR(layer);
    sublist = CAR(temp);
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    drawing_element = CAR(sublist);
    if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qstippled_area)) {
	old_stipple_place = sublist;
	goto end_1;
    }
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:
    old_stipple_place = Qnil;
  end_1:;
    old_stipple = CAR(old_stipple_place);
    if (EQUAL(old_stipple,new_stipple))
	return VALUES_1(Nil);
    else if ( !TRUEP(old_stipple)) {
	new_drawing_element = 
		copy_drawing_element_with_icon_editor_conses(new_stipple,
		Nil,Nil);
	layer = ISVREF(icon_editor_engine,(SI_Long)6L);
	temp = CDDR(layer);
	drawing_elements = CAR(temp);
	reclaim_icon_editor_slot_value(SECOND(layer));
	M_SECOND(layer) = Nil;
	gensymed_symbol = new_drawing_element;
	gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	if (drawing_elements) {
	    temp = CDDDR(layer);
	    if ( !TRUEP(CAR(temp))) {
		temp_1 = CDDDR(layer);
		car_new_value = last(drawing_elements,_);
		M_CAR(temp_1) = car_new_value;
	    }
	    temp = CDDDR(layer);
	    temp_1 = CAR(temp);
	    M_CDR(temp_1) = gensymed_symbol;
	}
	else
	    drawing_elements = gensymed_symbol;
	temp_1 = CDDDR(layer);
	M_CAR(temp_1) = gensymed_symbol;
	temp_1 = CDDR(layer);
	M_CAR(temp_1) = drawing_elements;
	return VALUES_1(T);
    }
    else if (new_stipple) {
	temp_1 = copy_drawing_element_with_icon_editor_conses(new_stipple,
		Nil,Nil);
	M_CAR(old_stipple_place) = temp_1;
	reclaim_icon_editor_slot_value(old_stipple);
	return VALUES_1(T);
    }
    else {
	temp_1 = CDDR(layer);
	temp = CDDR(layer);
	car_new_value = delete_icon_editor_element_1(old_stipple,CAR(temp));
	M_CAR(temp_1) = car_new_value;
	temp_1 = CDDDR(layer);
	temp = CDDR(layer);
	car_new_value = last(CAR(temp),_);
	M_CAR(temp_1) = car_new_value;
	return VALUES_1(T);
    }
}

/* REGISTER-SYMBOL-CORRESPONDING-TO-STRING-FOR-BUTTON-INTERNATIONALIZATION */
Object register_symbol_corresponding_to_string_for_button_internationalization(string_1)
    Object string_1;
{
    Object symbol;

    x_note_fn_call(232,109);
    symbol = intern(string_upcase(1,string_1),_);
    return register_button_label_for_internationalization(symbol);
}

void icons1_INIT()
{
    Object temp, reclaim_structure_for_layer_box_1;
    Object reclaim_structure_for_icon_editor_translator_1;
    Object reclaim_structure_for_icon_editor_engine_1;
    Object reclaim_structure_for_icon_editor_view_pad_1;
    Object reclaim_structure_for_icon_editor_layers_pad_1;
    Object reclaim_structure_for_icon_editor_button_1, temp_1;
    Object reclaim_structure_for_icon_editor_table_1;
    Object reclaim_structure_for_icon_editor_1;
    Object clean_up_workstation_context_for_icon_editor_1;
    Object valid_workstation_context_p_for_icon_editor_1;
    Object list_constant_12, Qpoint, list_constant_11, AB_package;
    Object Qicon_editor_workspace, string_constant_33, list_constant_10;
    Object string_constant_32, string_constant_15, Qtemporary_workspace;
    Object Qvalid_workstation_context_p, Qclean_up_workstation_context;
    Object list_constant_9, Qtop_level, Qicon_editor_keymap;
    Object Qselection_style_of_workstation_context_type;
    Object Qtop_level_with_mouse_tracking_is_selection_style;
    Object Qreclaim_structure, Qoutstanding_icon_editor_count;
    Object Qicon_editor_structure_memory_usage, Qutilities2;
    Object string_constant_31, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_30, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qicon_editor_table;
    Object Qoutstanding_icon_editor_table_count;
    Object Qicon_editor_table_structure_memory_usage, string_constant_29;
    Object string_constant_28, Qslot_value_reclaimer;
    Object Qreclaim_icon_editor_table_info_frame_info_value;
    Object Qicon_editor_table_info_frame_info, Qslot_value_writer;
    Object Qwrite_icon_editor_table_info_frame_x_y_position_from_slot;
    Object Qicon_editor_table_info_frame_x_y_position;
    Object Qwrite_color_or_metacolor_from_slot, Qcolor_or_metacolor;
    Object Qwrite_region_qm_from_slot, Qregion_qm, Qx_y, Qy;
    Object Qicon_editor_table_info_frame_y_position, Qx;
    Object Qicon_editor_table_info_frame_x_position, Qheight;
    Object Qicon_editor_table_info_frame_icon_height, Qwidth;
    Object Qicon_editor_table_info_frame_icon_width, Qoutline_color;
    Object Qicon_editor_table_info_frame_outline_color, Qoutline_region;
    Object Qicon_editor_table_info_frame_outline_region, Qcolor;
    Object Qicon_editor_table_info_frame_main_color, Qregion;
    Object Qicon_editor_table_info_frame_main_region;
    Object Qreclaim_icon_editor_table_info_frame_icon_editor_value;
    Object Qicon_editor_table_info_frame_icon_editor, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object list_constant_8, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16, Qentity;
    Object Qicon_editor_button, Qoutstanding_icon_editor_button_count;
    Object Qicon_editor_button_structure_memory_usage, string_constant_14;
    Object string_constant_13, Qicon_editor_layers_pad;
    Object Qoutstanding_icon_editor_layers_pad_count;
    Object Qicon_editor_layers_pad_structure_memory_usage, string_constant_12;
    Object string_constant_11, Qicon_editor_view_pad;
    Object Qoutstanding_icon_editor_view_pad_count;
    Object Qicon_editor_view_pad_structure_memory_usage, string_constant_10;
    Object string_constant_9, Qicon_editor_engine;
    Object Qoutstanding_icon_editor_engine_count;
    Object Qicon_editor_engine_structure_memory_usage, string_constant_8;
    Object string_constant_7, Qicon_editor_translator;
    Object Qoutstanding_icon_editor_translator_count;
    Object Qicon_editor_translator_structure_memory_usage, string_constant_6;
    Object string_constant_5, Qlayer_box, Qoutstanding_layer_box_count;
    Object Qlayer_box_structure_memory_usage, string_constant_4;
    Object string_constant_3, string_constant_2;
    Object Qicon_editor_cons_memory_usage, Qoutstanding_icon_editor_conses;
    Object Qutilities1, list_constant_7, Qicon_editor_cons_counter_vector;
    Object Qmake_thread_array, Kfuncall, list_constant_6;
    Object Qavailable_icon_editor_conses_tail_vector;
    Object Qavailable_icon_editor_conses_vector;

    x_note_fn_call(232,110);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_icon_editor_conses = 
	    STATIC_SYMBOL("AVAILABLE-ICON-EDITOR-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icon_editor_conses,
	    Available_icon_editor_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_icon_editor_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_icon_editor_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-ICON-EDITOR-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icon_editor_conses_tail,
	    Available_icon_editor_conses_tail);
    record_system_variable(Qavailable_icon_editor_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_icon_editor_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICON-EDITOR-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icon_editor_conses_vector,
	    Available_icon_editor_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_icon_editor_conses_vector,
	    Qutilities1,list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qavailable_icon_editor_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICON-EDITOR-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icon_editor_conses_tail_vector,
	    Available_icon_editor_conses_tail_vector);
    record_system_variable(Qavailable_icon_editor_conses_tail_vector,
	    Qutilities1,list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_cons_counter_vector = 
	    STATIC_SYMBOL("ICON-EDITOR-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_cons_counter_vector,
	    Icon_editor_cons_counter_vector);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qicon_editor_cons_counter_vector,Qutilities1,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_cons_counter = STATIC_SYMBOL("ICON-EDITOR-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_cons_counter,
	    Icon_editor_cons_counter);
    record_system_variable(Qicon_editor_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_icon_editor_conses = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_conses,
	    STATIC_FUNCTION(outstanding_icon_editor_conses,NIL,FALSE,0,0));
    Qicon_editor_cons_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qicon_editor_cons_memory_usage,
	    STATIC_FUNCTION(icon_editor_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_2 = STATIC_STRING("1q83-YWy9k83-YVy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_icon_editor_conses);
    push_optimized_constant(Qicon_editor_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_2));
    Qicon_editor = STATIC_SYMBOL("ICON-EDITOR",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_layer_box_g2_struct = 
	    STATIC_SYMBOL("LAYER-BOX-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlayer_box = STATIC_SYMBOL("LAYER-BOX",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_layer_box_g2_struct,
	    Qlayer_box,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qlayer_box,
	    Qg2_defstruct_structure_name_layer_box_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_layer_box == UNBOUND)
	The_type_description_of_layer_box = Nil;
    string_constant_3 = 
	    STATIC_STRING("43Dy8m83kSy1n83kSy8n8k1l8n0000001l1n8y83-4jy1o83-1ty83-1wy83-1uy83-1vyk3Hyk0k0");
    temp = The_type_description_of_layer_box;
    The_type_description_of_layer_box = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_3));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_layer_box_g2_struct,
	    The_type_description_of_layer_box,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qlayer_box,The_type_description_of_layer_box,
	    Qtype_description_of_type);
    Qoutstanding_layer_box_count = 
	    STATIC_SYMBOL("OUTSTANDING-LAYER-BOX-COUNT",AB_package);
    Qlayer_box_structure_memory_usage = 
	    STATIC_SYMBOL("LAYER-BOX-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_4 = STATIC_STRING("1q83kSy8s83-cGy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_layer_box_count);
    push_optimized_constant(Qlayer_box_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_4));
    Qchain_of_available_layer_boxs = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LAYER-BOXS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_layer_boxs,
	    Chain_of_available_layer_boxs);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_layer_boxs,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qlayer_box_count = STATIC_SYMBOL("LAYER-BOX-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlayer_box_count,Layer_box_count);
    record_system_variable(Qlayer_box_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_layer_boxs_vector == UNBOUND)
	Chain_of_available_layer_boxs_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlayer_box_structure_memory_usage,
	    STATIC_FUNCTION(layer_box_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_layer_box_count,
	    STATIC_FUNCTION(outstanding_layer_box_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_layer_box_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_layer_box,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qlayer_box,
	    reclaim_structure_for_layer_box_1);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_icon_editor_translator_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-TRANSLATOR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicon_editor_translator = STATIC_SYMBOL("ICON-EDITOR-TRANSLATOR",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_translator_g2_struct,
	    Qicon_editor_translator,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicon_editor_translator,
	    Qg2_defstruct_structure_name_icon_editor_translator_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_editor_translator == UNBOUND)
	The_type_description_of_icon_editor_translator = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8m83iey1n83iey8n8k1l8n0000001l1n8y83-4Ly0kok0k0");
    temp = The_type_description_of_icon_editor_translator;
    The_type_description_of_icon_editor_translator = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_5));
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_translator_g2_struct,
	    The_type_description_of_icon_editor_translator,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicon_editor_translator,
	    The_type_description_of_icon_editor_translator,
	    Qtype_description_of_type);
    Qoutstanding_icon_editor_translator_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-TRANSLATOR-COUNT",
	    AB_package);
    Qicon_editor_translator_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-TRANSLATOR-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_6 = STATIC_STRING("1q83iey8s83-Yby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_editor_translator_count);
    push_optimized_constant(Qicon_editor_translator_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qchain_of_available_icon_editor_translators = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-EDITOR-TRANSLATORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_editor_translators,
	    Chain_of_available_icon_editor_translators);
    record_system_variable(Qchain_of_available_icon_editor_translators,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_translator_count = 
	    STATIC_SYMBOL("ICON-EDITOR-TRANSLATOR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_translator_count,
	    Icon_editor_translator_count);
    record_system_variable(Qicon_editor_translator_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_editor_translators_vector == UNBOUND)
	Chain_of_available_icon_editor_translators_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_editor_translator_structure_memory_usage,
	    STATIC_FUNCTION(icon_editor_translator_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_translator_count,
	    STATIC_FUNCTION(outstanding_icon_editor_translator_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_icon_editor_translator_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_editor_translator,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qicon_editor_translator,
	    reclaim_structure_for_icon_editor_translator_1);
    Qg2_defstruct_structure_name_icon_editor_engine_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-ENGINE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicon_editor_engine = STATIC_SYMBOL("ICON-EDITOR-ENGINE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_engine_g2_struct,
	    Qicon_editor_engine,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicon_editor_engine,
	    Qg2_defstruct_structure_name_icon_editor_engine_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_editor_engine == UNBOUND)
	The_type_description_of_icon_editor_engine = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8m83iby1n83iby8n8k1l8n0000001l1n8y83-4Iy0k3Eyk0k0");
    temp = The_type_description_of_icon_editor_engine;
    The_type_description_of_icon_editor_engine = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_7));
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_engine_g2_struct,
	    The_type_description_of_icon_editor_engine,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicon_editor_engine,
	    The_type_description_of_icon_editor_engine,
	    Qtype_description_of_type);
    Qoutstanding_icon_editor_engine_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-ENGINE-COUNT",AB_package);
    Qicon_editor_engine_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-ENGINE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_8 = STATIC_STRING("1q83iby8s83-YYy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_editor_engine_count);
    push_optimized_constant(Qicon_editor_engine_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qchain_of_available_icon_editor_engines = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-EDITOR-ENGINES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_editor_engines,
	    Chain_of_available_icon_editor_engines);
    record_system_variable(Qchain_of_available_icon_editor_engines,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_engine_count = STATIC_SYMBOL("ICON-EDITOR-ENGINE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_engine_count,
	    Icon_editor_engine_count);
    record_system_variable(Qicon_editor_engine_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_editor_engines_vector == UNBOUND)
	Chain_of_available_icon_editor_engines_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_editor_engine_structure_memory_usage,
	    STATIC_FUNCTION(icon_editor_engine_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_engine_count,
	    STATIC_FUNCTION(outstanding_icon_editor_engine_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_icon_editor_engine_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_editor_engine,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicon_editor_engine,
	    reclaim_structure_for_icon_editor_engine_1);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qg2_defstruct_structure_name_icon_editor_view_pad_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-VIEW-PAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicon_editor_view_pad = STATIC_SYMBOL("ICON-EDITOR-VIEW-PAD",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_view_pad_g2_struct,
	    Qicon_editor_view_pad,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicon_editor_view_pad,
	    Qg2_defstruct_structure_name_icon_editor_view_pad_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_editor_view_pad == UNBOUND)
	The_type_description_of_icon_editor_view_pad = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8m83ify1n83ify8n8k1l8n0000001l1n8y83-4My1o83-*my83-*ny83-*ky83-*lyk3Iyk0k0");
    temp = The_type_description_of_icon_editor_view_pad;
    The_type_description_of_icon_editor_view_pad = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_9));
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_view_pad_g2_struct,
	    The_type_description_of_icon_editor_view_pad,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicon_editor_view_pad,
	    The_type_description_of_icon_editor_view_pad,
	    Qtype_description_of_type);
    Qoutstanding_icon_editor_view_pad_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-VIEW-PAD-COUNT",AB_package);
    Qicon_editor_view_pad_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-VIEW-PAD-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_10 = STATIC_STRING("1q83ify8s83-Ycy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_editor_view_pad_count);
    push_optimized_constant(Qicon_editor_view_pad_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qchain_of_available_icon_editor_view_pads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-EDITOR-VIEW-PADS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_editor_view_pads,
	    Chain_of_available_icon_editor_view_pads);
    record_system_variable(Qchain_of_available_icon_editor_view_pads,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_view_pad_count = 
	    STATIC_SYMBOL("ICON-EDITOR-VIEW-PAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_view_pad_count,
	    Icon_editor_view_pad_count);
    record_system_variable(Qicon_editor_view_pad_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_editor_view_pads_vector == UNBOUND)
	Chain_of_available_icon_editor_view_pads_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_editor_view_pad_structure_memory_usage,
	    STATIC_FUNCTION(icon_editor_view_pad_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_view_pad_count,
	    STATIC_FUNCTION(outstanding_icon_editor_view_pad_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_icon_editor_view_pad_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_editor_view_pad,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qicon_editor_view_pad,
	    reclaim_structure_for_icon_editor_view_pad_1);
    Qg2_defstruct_structure_name_icon_editor_layers_pad_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-LAYERS-PAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicon_editor_layers_pad = STATIC_SYMBOL("ICON-EDITOR-LAYERS-PAD",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_layers_pad_g2_struct,
	    Qicon_editor_layers_pad,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicon_editor_layers_pad,
	    Qg2_defstruct_structure_name_icon_editor_layers_pad_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_editor_layers_pad == UNBOUND)
	The_type_description_of_icon_editor_layers_pad = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8m83icy1n83icy8n8k1l8n0000001l1n8y83-4Jy1o83-*Zy83-*ay83-*Xy83-*Yyk3Dyk0k0");
    temp = The_type_description_of_icon_editor_layers_pad;
    The_type_description_of_icon_editor_layers_pad = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_11));
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_layers_pad_g2_struct,
	    The_type_description_of_icon_editor_layers_pad,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicon_editor_layers_pad,
	    The_type_description_of_icon_editor_layers_pad,
	    Qtype_description_of_type);
    Qoutstanding_icon_editor_layers_pad_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-LAYERS-PAD-COUNT",
	    AB_package);
    Qicon_editor_layers_pad_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-LAYERS-PAD-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_12 = STATIC_STRING("1q83icy8s83-YZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_editor_layers_pad_count);
    push_optimized_constant(Qicon_editor_layers_pad_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    Qchain_of_available_icon_editor_layers_pads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-EDITOR-LAYERS-PADS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_editor_layers_pads,
	    Chain_of_available_icon_editor_layers_pads);
    record_system_variable(Qchain_of_available_icon_editor_layers_pads,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_layers_pad_count = 
	    STATIC_SYMBOL("ICON-EDITOR-LAYERS-PAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_layers_pad_count,
	    Icon_editor_layers_pad_count);
    record_system_variable(Qicon_editor_layers_pad_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_editor_layers_pads_vector == UNBOUND)
	Chain_of_available_icon_editor_layers_pads_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_editor_layers_pad_structure_memory_usage,
	    STATIC_FUNCTION(icon_editor_layers_pad_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_layers_pad_count,
	    STATIC_FUNCTION(outstanding_icon_editor_layers_pad_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_icon_editor_layers_pad_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_editor_layers_pad,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qicon_editor_layers_pad,
	    reclaim_structure_for_icon_editor_layers_pad_1);
    Qg2_defstruct_structure_name_icon_editor_button_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-BUTTON-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicon_editor_button = STATIC_SYMBOL("ICON-EDITOR-BUTTON",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_button_g2_struct,
	    Qicon_editor_button,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicon_editor_button,
	    Qg2_defstruct_structure_name_icon_editor_button_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_editor_button == UNBOUND)
	The_type_description_of_icon_editor_button = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m837+y1n837+y8n8k1l8n0000001l1n8y83-4Hy1q83-*Uy83-*Vy83-*Ty83-*Sy83-*Qy83-*Rykrk0k0");
    temp = The_type_description_of_icon_editor_button;
    The_type_description_of_icon_editor_button = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_button_g2_struct,
	    The_type_description_of_icon_editor_button,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicon_editor_button,
	    The_type_description_of_icon_editor_button,
	    Qtype_description_of_type);
    Qoutstanding_icon_editor_button_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-BUTTON-COUNT",AB_package);
    Qicon_editor_button_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-BUTTON-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_14 = STATIC_STRING("1q837+y8s83-YUy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_editor_button_count);
    push_optimized_constant(Qicon_editor_button_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_icon_editor_buttons = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-EDITOR-BUTTONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_editor_buttons,
	    Chain_of_available_icon_editor_buttons);
    record_system_variable(Qchain_of_available_icon_editor_buttons,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_button_count = STATIC_SYMBOL("ICON-EDITOR-BUTTON-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_button_count,
	    Icon_editor_button_count);
    record_system_variable(Qicon_editor_button_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_editor_buttons_vector == UNBOUND)
	Chain_of_available_icon_editor_buttons_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_editor_button_structure_memory_usage,
	    STATIC_FUNCTION(icon_editor_button_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_button_count,
	    STATIC_FUNCTION(outstanding_icon_editor_button_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_icon_editor_button_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_editor_button,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicon_editor_button,
	    reclaim_structure_for_icon_editor_button_1);
    Qbutton_label = STATIC_SYMBOL("BUTTON-LABEL",AB_package);
    Qbig_icon_editor_text_button = 
	    STATIC_SYMBOL("BIG-ICON-EDITOR-TEXT-BUTTON",AB_package);
    Qsmall_icon_editor_text_button = 
	    STATIC_SYMBOL("SMALL-ICON-EDITOR-TEXT-BUTTON",AB_package);
    Qicon_editor_table_info_frame = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_8 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qicon_editor_table_info_frame,
	    list_constant_8);
    string_constant_15 = STATIC_STRING("0");
    string_constant_16 = 
	    STATIC_STRING("1z4z8r83Rky83Rky8393y8393y00001q1l8l1l83Hy1l8o1m8p83Rky1l83-3y1l83Fy000004z8r83Rny83Rny8393y8393y00001o1l8l1l83Hy1l8o1m8p83Efy00");
    string_constant_17 = 
	    STATIC_STRING("0004z8r83Rly83Rly8393y8393y083Ty001o1l8l1l83Hy1l8o1m8p83*uy000004z8r83Rpy83Rpy8393y8393y00001o1l8l1l83Hy1l8o1m8p83Efy000004z8r83");
    string_constant_18 = 
	    STATIC_STRING("Roy83Roy8393y8393y083Ty001o1l8l1l83Hy1l8o1m8p83*uy000004z8r83Rjy83Rjy8393y8393y0k001o1l8l1l83Hy1l8o1m8p83-ey000004z8r83Riy83Riy8");
    string_constant_19 = 
	    STATIC_STRING("393y8393y0k001o1l8l1l83Hy1l8o1m8p83-ey000004z8r83Rsy83Rsy8393y8393y0k001p1l8l1l83Hy1l8o1m8p83Sy1l83Fy000004z8r83Ruy83Ruy8393y839");
    string_constant_20 = 
	    STATIC_STRING("3y0k001p1l8l1l83Hy1l8o1m8p83Sy1l83Fy000004z8r83Rty83Rty8393y8393y0k001q1l8l1l83Hy1l8o1m8p83Rty1l83-3y1l83Fy000004z8r83Rgy83Rgy83");
    string_constant_21 = 
	    STATIC_STRING("93y8393y00001o1l8l1l83Hy1l83Ey1m8p83CXy000004z8r83Rqy83Rqy8393y8393y00001o1l8l1l83Hy1l83Ey1m8p83FDy000004z8r83Rmy83Rmy8393y8393y");
    string_constant_22 = 
	    STATIC_STRING("00001o1l8l1l83Hy1l83Ey1m8p83Coy000004z8r83Rry83Rry8393y8393y00001o1l8l1l83Hy1l83Ey1m8p83FMy000004z8r83Rhy83Rhy8393y8393y00001n1l");
    string_constant_23 = STATIC_STRING("8l1l83Hy1l83Ey00000");
    string_constant_24 = 
	    STATIC_STRING("13Dy8q1m8393y1l83-+y1s83Rky08l83Hy8o1m8p83Rky83-3y83Fy1q83Rny08l83Hy8o1m8p83Efy1q83Rly83Ty8l83Hy8o1m8p83*uy1q83Rpy08l83Hy8o1m8p8");
    string_constant_25 = 
	    STATIC_STRING("3Efy1q83Roy83Ty8l83Hy8o1m8p83*uy1q83Rjyk8l83Hy8o1m8p83-ey1q83Riyk8l83Hy8o1m8p83-ey1r83Rsyk8l83Hy8o1m8p83Sy83Fy1r83Ruyk8l83Hy8o1m");
    string_constant_26 = 
	    STATIC_STRING("8p83Sy83Fy1s83Rtyk8l83Hy8o1m8p83Rty83-3y83Fy1q83Rgy08l83Hy83Ey1m8p83CXy1q83Rqy08l83Hy83Ey1m8p83FDy1q83Rmy08l83Hy83Ey1m8p83Coy1q8");
    string_constant_27 = 
	    STATIC_STRING("3Rry08l83Hy83Ey1m8p83FMy1p83Rhy08l83Hy83Ey");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(list(8,string_constant_16,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20,string_constant_21,string_constant_22,
	    string_constant_23));
    add_class_to_environment(9,Qicon_editor_table_info_frame,
	    list_constant_8,Nil,temp,Nil,temp_1,list_constant_8,
	    regenerate_optimized_constant(LIST_4(string_constant_24,
	    string_constant_25,string_constant_26,string_constant_27)),Nil);
    Icon_editor_table_info_frame_class_description = 
	    lookup_global_or_kb_specific_property_value(Qicon_editor_table_info_frame,
	    Class_description_gkbprop);
    Qicon_editor_table_info_frame_icon_editor = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-EDITOR",
	    AB_package);
    Qreclaim_icon_editor_table_info_frame_icon_editor_value = 
	    STATIC_SYMBOL("RECLAIM-ICON-EDITOR-TABLE-INFO-FRAME-ICON-EDITOR-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icon_editor_table_info_frame_icon_editor_value,
	    STATIC_FUNCTION(reclaim_icon_editor_table_info_frame_icon_editor_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qicon_editor_table_info_frame_icon_editor,
	    SYMBOL_FUNCTION(Qreclaim_icon_editor_table_info_frame_icon_editor_value),
	    Qslot_value_reclaimer);
    Qicon_editor_table_info_frame_main_region = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-REGION",
	    AB_package);
    Qregion = STATIC_SYMBOL("REGION",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_main_region,Qregion,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_main_color = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-COLOR",
	    AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_main_color,Qcolor,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_outline_region = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-OUTLINE-REGION",
	    AB_package);
    Qoutline_region = STATIC_SYMBOL("OUTLINE-REGION",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_outline_region,
	    Qoutline_region,Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_outline_color = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-OUTLINE-COLOR",
	    AB_package);
    Qoutline_color = STATIC_SYMBOL("OUTLINE-COLOR",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_outline_color,
	    Qoutline_color,Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_icon_width = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-WIDTH",
	    AB_package);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_icon_width,Qwidth,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_icon_height = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-HEIGHT",
	    AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_icon_height,Qheight,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_global_stipple = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-GLOBAL-STIPPLE",
	    AB_package);
    Qstipple = STATIC_SYMBOL("STIPPLE",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_global_stipple,
	    Qstipple,Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_x_position = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-X-POSITION",
	    AB_package);
    Qx = STATIC_SYMBOL("X",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_x_position,Qx,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_y_position = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-Y-POSITION",
	    AB_package);
    Qy = STATIC_SYMBOL("Y",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_y_position,Qy,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_x_y_position = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-X-Y-POSITION",
	    AB_package);
    Qx_y = STATIC_SYMBOL("X-Y",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_x_y_position,Qx_y,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_stipple = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-STIPPLE",AB_package);
    Qstippled_area = STATIC_SYMBOL("STIPPLED-AREA",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_stipple,Qstippled_area,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_main_image = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-IMAGE",
	    AB_package);
    Qimage = STATIC_SYMBOL("IMAGE",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_main_image,Qimage,
	    Qicon_editor_table_info_frame);
    Qicon_editor_table_info_frame_text = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-TEXT",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    alias_slot_name(3,Qicon_editor_table_info_frame_text,Qtext,
	    Qicon_editor_table_info_frame);
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qregion_qm = STATIC_SYMBOL("REGION\?",AB_package);
    Qwrite_region_qm_from_slot = STATIC_SYMBOL("WRITE-REGION\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_region_qm_from_slot,
	    STATIC_FUNCTION(write_region_qm_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qregion_qm,
	    SYMBOL_FUNCTION(Qwrite_region_qm_from_slot),Qslot_value_writer);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    Qwrite_color_or_metacolor_from_slot = 
	    STATIC_SYMBOL("WRITE-COLOR-OR-METACOLOR-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_color_or_metacolor_from_slot,
	    STATIC_FUNCTION(write_color_or_metacolor_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qcolor_or_metacolor,
	    SYMBOL_FUNCTION(Qwrite_color_or_metacolor_from_slot),
	    Qslot_value_writer);
    string_constant = STATIC_STRING("(~a, ~a)");
    Qwrite_icon_editor_table_info_frame_x_y_position_from_slot = 
	    STATIC_SYMBOL("WRITE-ICON-EDITOR-TABLE-INFO-FRAME-X-Y-POSITION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icon_editor_table_info_frame_x_y_position_from_slot,
	    STATIC_FUNCTION(write_icon_editor_table_info_frame_x_y_position_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qicon_editor_table_info_frame_x_y_position,
	    SYMBOL_FUNCTION(Qwrite_icon_editor_table_info_frame_x_y_position_from_slot),
	    Qslot_value_writer);
    Qicon_editor_table_info_frame_info = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-INFO",AB_package);
    Qreclaim_icon_editor_table_info_frame_info_value = 
	    STATIC_SYMBOL("RECLAIM-ICON-EDITOR-TABLE-INFO-FRAME-INFO-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icon_editor_table_info_frame_info_value,
	    STATIC_FUNCTION(reclaim_icon_editor_table_info_frame_info_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qicon_editor_table_info_frame_info,
	    SYMBOL_FUNCTION(Qreclaim_icon_editor_table_info_frame_info_value),
	    Qslot_value_reclaimer);
    Qg2_defstruct_structure_name_icon_editor_table_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicon_editor_table = STATIC_SYMBOL("ICON-EDITOR-TABLE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_table_g2_struct,
	    Qicon_editor_table,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicon_editor_table,
	    Qg2_defstruct_structure_name_icon_editor_table_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_editor_table == UNBOUND)
	The_type_description_of_icon_editor_table = Nil;
    string_constant_28 = 
	    STATIC_STRING("43Dy8m83idy1n83idy8n8k1l8n0000001l1n8y83-4Ky1s83-*iy83-*jy83-*hy83-*ey8393y83-*cy83-*gy83-*dyktk0k0");
    temp = The_type_description_of_icon_editor_table;
    The_type_description_of_icon_editor_table = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_28));
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_table_g2_struct,
	    The_type_description_of_icon_editor_table,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicon_editor_table,
	    The_type_description_of_icon_editor_table,
	    Qtype_description_of_type);
    Qoutstanding_icon_editor_table_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-TABLE-COUNT",AB_package);
    Qicon_editor_table_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_29 = STATIC_STRING("1q83idy8s83-Yay09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_editor_table_count);
    push_optimized_constant(Qicon_editor_table_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qchain_of_available_icon_editor_tables = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-EDITOR-TABLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_editor_tables,
	    Chain_of_available_icon_editor_tables);
    record_system_variable(Qchain_of_available_icon_editor_tables,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_table_count = STATIC_SYMBOL("ICON-EDITOR-TABLE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_table_count,
	    Icon_editor_table_count);
    record_system_variable(Qicon_editor_table_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_editor_tables_vector == UNBOUND)
	Chain_of_available_icon_editor_tables_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_editor_table_structure_memory_usage,
	    STATIC_FUNCTION(icon_editor_table_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_table_count,
	    STATIC_FUNCTION(outstanding_icon_editor_table_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_icon_editor_table_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_editor_table,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicon_editor_table,
	    reclaim_structure_for_icon_editor_table_1);
    Qsmall_class_format = STATIC_SYMBOL("SMALL-CLASS-FORMAT",AB_package);
    Qsmall_attribute_value_format = 
	    STATIC_SYMBOL("SMALL-ATTRIBUTE-VALUE-FORMAT",AB_package);
    Qsmall_attribute_description_format = 
	    STATIC_SYMBOL("SMALL-ATTRIBUTE-DESCRIPTION-FORMAT",AB_package);
    Qg2_defstruct_structure_name_icon_editor_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_g2_struct,
	    Qicon_editor,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicon_editor,
	    Qg2_defstruct_structure_name_icon_editor_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_editor == UNBOUND)
	The_type_description_of_icon_editor = Nil;
    string_constant_30 = 
	    STATIC_STRING("43Dy8m83iay1o83iay83-Sy8n8k1l83-Sy0000001m1n8y83-4Gy1n83-*Wy8394y83-*by1m8x83-Syk3Oyk0k0");
    temp = The_type_description_of_icon_editor;
    The_type_description_of_icon_editor = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_30));
    mutate_global_property(Qg2_defstruct_structure_name_icon_editor_g2_struct,
	    The_type_description_of_icon_editor,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicon_editor,
	    The_type_description_of_icon_editor,Qtype_description_of_type);
    Qoutstanding_icon_editor_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-EDITOR-COUNT",AB_package);
    Qicon_editor_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-EDITOR-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_31 = STATIC_STRING("1q83iay8s83-YXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_editor_count);
    push_optimized_constant(Qicon_editor_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_31));
    Qchain_of_available_icon_editors = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-EDITORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_editors,
	    Chain_of_available_icon_editors);
    record_system_variable(Qchain_of_available_icon_editors,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_editor_count = STATIC_SYMBOL("ICON-EDITOR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_editor_count,Icon_editor_count);
    record_system_variable(Qicon_editor_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_editors_vector == UNBOUND)
	Chain_of_available_icon_editors_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_editor_structure_memory_usage,
	    STATIC_FUNCTION(icon_editor_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_editor_count,
	    STATIC_FUNCTION(outstanding_icon_editor_count,NIL,FALSE,0,0));
    reclaim_structure_for_icon_editor_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_editor,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicon_editor,
	    reclaim_structure_for_icon_editor_1);
    Qtop_level_with_mouse_tracking_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-MOUSE-TRACKING-IS-SELECTION-STYLE",
	    AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qicon_editor,
	    Qtop_level_with_mouse_tracking_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    Qicon_editor_keymap = STATIC_SYMBOL("ICON-EDITOR-KEYMAP",AB_package);
    list_constant_9 = STATIC_CONS(Qicon_editor_keymap,Qnil);
    make_context_description(Qicon_editor,Qtop_level,Qnil,list_constant_9);
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    clean_up_workstation_context_for_icon_editor_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_icon_editor,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qicon_editor,clean_up_workstation_context_for_icon_editor_1);
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    valid_workstation_context_p_for_icon_editor_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_icon_editor,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qicon_editor,valid_workstation_context_p_for_icon_editor_1);
    Qicon_editor_workspace = STATIC_SYMBOL("ICON-EDITOR-WORKSPACE",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    list_constant_10 = STATIC_CONS(Qtemporary_workspace,Qnil);
    check_if_superior_classes_are_defined(Qicon_editor_workspace,
	    list_constant_10);
    string_constant_32 = 
	    STATIC_STRING("1l4z8r83*Ly83*Ly8394y8394y0u001n1l8l1l8o1m8p83*7y00000");
    string_constant_33 = STATIC_STRING("1n8q1m8394y1l8318y1m83*Lyu");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(string_constant_32);
    add_class_to_environment(9,Qicon_editor_workspace,list_constant_10,Nil,
	    temp,Nil,temp_1,list_constant_10,
	    regenerate_optimized_constant(string_constant_33),Nil);
    Icon_editor_workspace_class_description = 
	    lookup_global_or_kb_specific_property_value(Qicon_editor_workspace,
	    Class_description_gkbprop);
    Qdefault_slot_constant = STATIC_SYMBOL("DEFAULT-SLOT-CONSTANT",AB_package);
    string_constant_1 = STATIC_STRING("undefined-string");
    Qfilled_polygon = STATIC_SYMBOL("FILLED-POLYGON",AB_package);
    Qarc = STATIC_SYMBOL("ARC",AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    Qpoint = STATIC_SYMBOL("POINT",AB_package);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    Qfilled_circle = STATIC_SYMBOL("FILLED-CIRCLE",AB_package);
    list_constant = STATIC_LIST((SI_Long)10L,Qpoint,Qoutline,Qcircle,
	    Qsolid_rectangle,Qlines,Qfilled_circle,Qfilled_polygon,Qimage,
	    Qtext,Qstippled_area);
    Qlines_old = STATIC_SYMBOL("LINES-OLD",AB_package);
    Qlight_stipple = STATIC_SYMBOL("LIGHT-STIPPLE",AB_package);
    Qmedium_stipple = STATIC_SYMBOL("MEDIUM-STIPPLE",AB_package);
    Qdark_stipple = STATIC_SYMBOL("DARK-STIPPLE",AB_package);
    Qlight_texture = STATIC_SYMBOL("LIGHT-TEXTURE",AB_package);
    Qmedium_texture = STATIC_SYMBOL("MEDIUM-TEXTURE",AB_package);
    Qdark_texture = STATIC_SYMBOL("DARK-TEXTURE",AB_package);
    Qbackground_layer = STATIC_SYMBOL("BACKGROUND-LAYER",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qoutline,Qcircle);
    list_constant_2 = STATIC_LIST((SI_Long)6L,Qpoint,Qlines,
	    Qsolid_rectangle,Qfilled_polygon,Qfilled_circle,Qimage);
    Qtexttured_area = STATIC_SYMBOL("TEXTTURED-AREA",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qsolid_rectangle,
	    Qfilled_polygon,Qfilled_circle);
    list_constant_11 = STATIC_CONS(Qimage,Qnil);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)5L,Qpoint,Qlines,Qoutline,
	    Qcircle,list_constant_11);
    list_constant_12 = STATIC_CONS(Qfilled_circle,Qnil);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)6L,Qpoint,Qlines,Qoutline,
	    Qcircle,Qsolid_rectangle,list_constant_12);
}
