/* utlts0.c
 * Input file:  utilities0.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts0.h"


Object G2int_managed_float_unique_marker = UNBOUND;

Object G2int_strange_cons = UNBOUND;

Object G2int_debugging_consing = UNBOUND;

Object G2int_cons_pool_conses_to_make_at_a_time = UNBOUND;

Object G2int_all_cons_pools = UNBOUND;

Object G2int_available_gensym_conses = UNBOUND;

Object G2int_available_gensym_conses_tail = UNBOUND;

Object G2int_gensym_cons_counter = UNBOUND;

/* OUTSTANDING-GENSYM-CONSES */
Object g2int_outstanding_gensym_conses()
{
    Object temp;

    x_note_fn_call(20,0);
    temp = FIXNUM_MINUS(G2int_gensym_cons_counter,
	    length(G2int_available_gensym_conses));
    return VALUES_1(temp);
}

/* GENSYM-CONS-MEMORY-USAGE */
Object g2int_gensym_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(20,1);
    temp = FIXNUM_TIMES(G2int_gensym_cons_counter,ltimes(FIX((SI_Long)2L),
	    G2int_bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-GENSYM-CONS-POOL */
Object g2int_replenish_gensym_cons_pool()
{
    Object gensymed_symbol, new_conses, incff_1_arg;
    Object gensym_cons_counter_new_value;
    XDeclare_area(1);

    x_note_fn_call(20,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,
		G2int_cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    incff_1_arg = G2int_cons_pool_conses_to_make_at_a_time;
    gensym_cons_counter_new_value = FIXNUM_ADD(G2int_gensym_cons_counter,
	    incff_1_arg);
    G2int_gensym_cons_counter = gensym_cons_counter_new_value;
    if (G2int_available_gensym_conses)
	G2int_available_gensym_conses = nconc2(CDR(new_conses),
		G2int_available_gensym_conses);
    else {
	G2int_available_gensym_conses = CDR(new_conses);
	G2int_available_gensym_conses_tail = last(new_conses,_);
    }
    return VALUES_1(new_conses);
}

static Object Qg2int_gensym;       /* gensym */

/* GENSYM-CONS-1 */
Object g2int_gensym_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, gensymed_symbol;

    x_note_fn_call(20,3);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-GENSYM-LIST-POOL */
Object g2int_replenish_gensym_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses;
    SI_Long conses_needed, temp, new_conses_count, incff_1_arg;
    SI_Long gensym_cons_counter_new_value;
    XDeclare_area(1);

    x_note_fn_call(20,4);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(G2int_cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(G2int_cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (G2int_available_gensym_conses)
	G2int_available_gensym_conses = nconc2(new_conses,
		G2int_available_gensym_conses);
    else
	G2int_available_gensym_conses = new_conses;
    incff_1_arg = new_conses_count;
    gensym_cons_counter_new_value = IFIX(G2int_gensym_cons_counter) + 
	    incff_1_arg;
    G2int_gensym_cons_counter = FIX(gensym_cons_counter_new_value);
    return VALUES_1(Nil);
}

/* MAKE-GENSYM-LIST-1 */
Object g2int_make_gensym_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(20,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = G2int_available_gensym_conses;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end;
	gensymed_symbol_1 = Qnil;
      end:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	g2int_replenish_gensym_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = G2int_available_gensym_conses;
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = G2int_available_gensym_conses;
	G2int_available_gensym_conses = CDR(gensymed_symbol_1);
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GENSYM-LIST-2 */
Object g2int_gensym_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;

    x_note_fn_call(20,6);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = CDR(G2int_available_gensym_conses);
    if (gensymed_symbol)
	goto end_loop;
    g2int_replenish_gensym_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = G2int_available_gensym_conses;
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qg2int_gensym);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = G2int_available_gensym_conses;
    G2int_available_gensym_conses = CDR(gensymed_symbol);
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end;
    gensymed_symbol = Qnil;
  end:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* GENSYM-LIST-3 */
Object g2int_gensym_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1;

    x_note_fn_call(20,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = CDR(G2int_available_gensym_conses);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    g2int_replenish_gensym_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = G2int_available_gensym_conses;
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qg2int_gensym);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = G2int_available_gensym_conses;
    G2int_available_gensym_conses = CDR(gensymed_symbol);
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end;
    gensymed_symbol = Qnil;
  end:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* GENSYM-LIST-4 */
Object g2int_gensym_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1;

    x_note_fn_call(20,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = CDR(G2int_available_gensym_conses);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    g2int_replenish_gensym_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = G2int_available_gensym_conses;
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qg2int_gensym);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = G2int_available_gensym_conses;
    G2int_available_gensym_conses = CDR(gensymed_symbol);
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end;
    gensymed_symbol = Qnil;
  end:;
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

/* GENSYM-LIST-TRACE-HOOK */
Object g2int_gensym_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(20,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-GENSYM-CONSES-1 */
Object g2int_copy_tree_using_gensym_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, gensymed_symbol, temp_1, new_list, last_new_cons;
    Object current_copy_position;

    x_note_fn_call(20,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = G2int_available_gensym_conses;
	if (new_cons) {
	    G2int_available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = g2int_replenish_gensym_cons_pool();
	temp_1 = g2int_copy_tree_using_gensym_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = G2int_available_gensym_conses;
	if (new_cons) {
	    G2int_available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = g2int_replenish_gensym_cons_pool();
	temp_1 = 
		g2int_copy_tree_using_gensym_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end;
	temp = Qnil;
      end:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-GENSYM-CONSES-1 */
Object g2int_copy_list_using_gensym_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, gensymed_symbol, temp_1, new_list, last_new_cons;
    Object current_copy_position;

    x_note_fn_call(20,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = G2int_available_gensym_conses;
	if (new_cons) {
	    G2int_available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = g2int_replenish_gensym_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = G2int_available_gensym_conses;
	if (new_cons) {
	    G2int_available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = g2int_replenish_gensym_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end;
	temp = Qnil;
      end:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-GENSYM-CONS-1 */
Object g2int_reclaim_gensym_cons_1(gensym_cons)
    Object gensym_cons;
{
    Object cdr_new_value;

    x_note_fn_call(20,12);
    inline_note_reclaim_cons(gensym_cons,Qg2int_gensym);
    cdr_new_value = G2int_available_gensym_conses;
    M_CDR(gensym_cons) = cdr_new_value;
    G2int_available_gensym_conses = gensym_cons;
    return VALUES_1(Nil);
}

/* RECLAIM-GENSYM-LIST-1 */
Object g2int_reclaim_gensym_list_1(gensym_list)
    Object gensym_list;
{
    Object last_1, next_qm, cdr_new_value, temp;

    x_note_fn_call(20,13);
    if (gensym_list) {
	last_1 = gensym_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	G2int_available_gensym_conses = gensym_list;
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* RECLAIM-GENSYM-LIST*-1 */
Object g2int_reclaim_gensym_liststar_1(gensym_list)
    Object gensym_list;
{
    Object temp, last_1, next_qm, temp_1;

    x_note_fn_call(20,14);
    if (CONSP(gensym_list)) {
	temp = last(gensym_list,_);
	M_CDR(temp) = Nil;
	if (gensym_list) {
	    last_1 = gensym_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qg2int_gensym);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(last_1) = temp;
	    G2int_available_gensym_conses = gensym_list;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-GENSYM-TREE-1 */
Object g2int_reclaim_gensym_tree_1(tree)
    Object tree;
{
    Object e, e2, gensym_cons, cdr_new_value, temp;

    x_note_fn_call(20,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	g2int_reclaim_gensym_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		gensym_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(gensym_cons,Qg2int_gensym);
		if (EQ(gensym_cons,e))
		    goto end;
		else if ( !TRUEP(gensym_cons))
		    goto end;
		else
		    gensym_cons = CDR(gensym_cons);
		goto next_loop_1;
	      end_loop:
	      end:;
	    }
	    cdr_new_value = G2int_available_gensym_conses;
	    M_CDR(e) = cdr_new_value;
	    G2int_available_gensym_conses = tree;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp = Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-GENSYM-ELEMENT-1 */
Object g2int_delete_gensym_element_1(element,gensym_list)
    Object element, gensym_list;
{
    Object temp, cdr_new_value, l_trailer_qm, l;

    x_note_fn_call(20,16);
    if (gensym_list) {
	if (EQ(element,M_CAR(gensym_list))) {
	    temp = CDR(gensym_list);
	    inline_note_reclaim_cons(gensym_list,Qg2int_gensym);
	    cdr_new_value = G2int_available_gensym_conses;
	    M_CDR(gensym_list) = cdr_new_value;
	    G2int_available_gensym_conses = gensym_list;
	}
	else {
	    l_trailer_qm = Nil;
	    l = gensym_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		cdr_new_value = M_CDR(l);
		M_CDR(l_trailer_qm) = cdr_new_value;
		inline_note_reclaim_cons(l,Qg2int_gensym);
		cdr_new_value = G2int_available_gensym_conses;
		M_CDR(l) = cdr_new_value;
		G2int_available_gensym_conses = l;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = gensym_list;
	    goto end;
	    temp = Qnil;
	  end:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-GENSYM-CONS-1 */
Object g2int_delete_gensym_cons_1(gensym_cons,gensym_list)
    Object gensym_cons, gensym_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(20,17);
    if (EQ(gensym_cons,gensym_list))
	temp = CDR(gensym_list);
    else {
	l_trailer_qm = Nil;
	l = gensym_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,gensym_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = gensym_list;
	    goto end;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end:;
    }
    g2int_reclaim_gensym_cons_1(gensym_cons);
    return VALUES_1(temp);
}

/* GENSYM-CONS-FUNCTION */
Object g2int_gensym_cons_function(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, gensymed_symbol;

    x_note_fn_call(20,18);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    return VALUES_1(gensymed_symbol);
}

/* COPY-TREE-USING-GENSYM-CONSES-FUNCTION */
Object g2int_copy_tree_using_gensym_conses_function(tree_qm)
    Object tree_qm;
{
    Object temp;

    x_note_fn_call(20,19);
    temp = g2int_copy_tree_using_gensym_conses_1(tree_qm);
    return VALUES_1(temp);
}

/* RECLAIM-GENSYM-LIST-FUNCTION */
Object g2int_reclaim_gensym_list_function(list_1)
    Object list_1;
{
    Object last_1, next_qm, cdr_new_value, temp;

    x_note_fn_call(20,20);
    if (list_1) {
	last_1 = list_1;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	G2int_available_gensym_conses = list_1;
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* RECLAIM-GENSYM-TREE-FUNCTION */
Object g2int_reclaim_gensym_tree_function(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(20,21);
    temp = g2int_reclaim_gensym_tree_1(tree);
    return VALUES_1(temp);
}

/* REVERSE-LIST-USING-GENSYM-CONSES */
Object g2int_reverse_list_using_gensym_conses(list_1)
    Object list_1;
{
    Object reversed_list, l, temp;

    x_note_fn_call(20,22);
    reversed_list = Nil;
    l = list_1;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    reversed_list = g2int_gensym_cons_1(CAR(l),reversed_list);
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    temp = reversed_list;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* RECLAIM-GENSYM-LIST-IF-LIST */
Object g2int_reclaim_gensym_list_if_list(atom_or_gensym_list)
    Object atom_or_gensym_list;
{
    x_note_fn_call(20,23);
    if (CONSP(atom_or_gensym_list))
	g2int_reclaim_gensym_list_1(atom_or_gensym_list);
    return VALUES_1(Nil);
}

Object G2int_scope_conses = UNBOUND;

/* SCOPE-CONS */
Object g2int_scope_cons(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object cons_holder, cons_to_give, next_cons_holder_qm;

    x_note_fn_call(20,24);
    cons_holder = G2int_scope_conses;
    cons_to_give = M_CAR(cons_holder);
    next_cons_holder_qm = M_CDR(cons_holder);
    if ( !TRUEP(next_cons_holder_qm)) {
	next_cons_holder_qm = g2int_gensym_cons_1(g2int_gensym_cons_1(Nil,
		Nil),Nil);
	M_CDR(cons_holder) = next_cons_holder_qm;
    }
    G2int_scope_conses = next_cons_holder_qm;
    M_CAR(cons_to_give) = car_1;
    M_CDR(cons_to_give) = cdr_1;
    return VALUES_1(cons_to_give);
}

/* MAKE-SCOPE-LIST */
Object g2int_make_scope_list(count_1)
    Object count_1;
{
    Object next_cons, ab_loop_iter_flag_, temp;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(20,25);
    if (IFIX(count_1) > (SI_Long)0L) {
	ab_loop_repeat_ = IFIX(count_1);
	next_cons = g2int_scope_cons(Nil,Nil);
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    next_cons = g2int_scope_cons(Nil,next_cons);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	temp = next_cons;
	goto end;
	temp = Qnil;
      end:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* COPY-LIST-USING-SCOPE-CONSES */
Object g2int_copy_list_using_scope_conses(list_to_copy)
    Object list_to_copy;
{
    Object element, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(20,26);
    element = Nil;
    ab_loop_list_ = list_to_copy;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = g2int_scope_cons(element,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* SORT-LIST */
Object g2int_sort_list(list_1,predicate,key)
    Object list_1, predicate, key;
{
    x_note_fn_call(20,27);
    return g2int_sort_list_1(list_1,length(list_1),predicate,key);
}

/* SORT-LIST-1 */
Object g2int_sort_list_1(l,n_init,predicate,key)
    Object l, n_init, predicate, key;
{
    Object l_tail, l2, l1, temp;
    SI_Long n_1, half_n;
    char temp_1;

    x_note_fn_call(20,28);
    n_1 = IFIX(n_init);
    if (n_1 > (SI_Long)1L) {
	half_n = n_1 >>  -  - (SI_Long)1L;
	l_tail = nthcdr(FIX(half_n - (SI_Long)1L),l);
	l2 = g2int_sort_list_1(CDR(l_tail),FIX(n_1 - half_n),predicate,key);
	M_CDR(l_tail) = Nil;
	l1 = g2int_sort_list_1(l,FIX(half_n),predicate,key);
	l = Nil;
      next_loop:
	if (key) {
	    temp = FUNCALL_1(key,CAR(l2));
	    temp_1 =  !TRUEP(FUNCALL_2(predicate,temp,FUNCALL_1(key,CAR(l1))));
	}
	else
	    temp_1 =  !TRUEP(FUNCALL_2(predicate,CAR(l2),CAR(l1)));
	if (temp_1) {
	    if ( !TRUEP(l)) {
		l = l1;
		l_tail = l;
	    }
	    else
		l_tail = M_CDR(l_tail) = l1;
	    l1 = CDR(l1);
	    if ( !TRUEP(l1))
		temp_1 = TRUEP(M_CDR(l_tail) = l2);
	    else
		temp_1 = TRUEP(Nil);
	}
	else {
	    if ( !TRUEP(l)) {
		l = l2;
		l_tail = l;
	    }
	    else
		l_tail = M_CDR(l_tail) = l2;
	    l2 = CDR(l2);
	    if ( !TRUEP(l2))
		temp_1 = TRUEP(M_CDR(l_tail) = l1);
	    else
		temp_1 = TRUEP(Nil);
	}
	if (temp_1)
	    goto end_loop;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(l);
}

/* LIST-PREFIX-P */
Object g2int_list_prefix_p(list_a,list_b)
    Object list_a, list_b;
{
    Object element, ab_loop_list_, temp, list_b_old_value, temp_1;
    char temp_2;

    x_note_fn_call(20,29);
    element = Nil;
    ab_loop_list_ = list_a;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (list_b) {
	temp = element;
	list_b_old_value = list_b;
	temp_1 = FIRST(list_b_old_value);
	list_b = REST(list_b_old_value);
	temp_2 = EQ(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2)
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* ALLOCATE-INITIAL-MANAGED-SIMPLE-VECTOR-POOL-ARRAY */
Object g2int_allocate_initial_managed_simple_vector_pool_array(initial_element)
    Object initial_element;
{
    x_note_fn_call(20,30);
    return make_array(3,
	    FIXNUM_ADD1(G2int_maximum_managed_simple_vector_size),
	    Kinitial_element,initial_element);
}

Object G2int_vector_of_simple_vector_pools = UNBOUND;

Object G2int_simple_vector_pool_counts = UNBOUND;

Object G2int_vector_of_oversized_simple_vector_pools = UNBOUND;

Object G2int_oversized_simple_vector_pool_counts = UNBOUND;

Object G2int_created_simple_vector_pool_vectors = UNBOUND;

/* OUTSTANDING-SIMPLE-VECTOR-POOL-VECTORS */
Object g2int_outstanding_simple_vector_pool_vectors()
{
    Object vector_1;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(20,31);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(G2int_maximum_managed_simple_vector_size))
	goto end_loop;
    vector_1 = ISVREF(G2int_vector_of_simple_vector_pools,index_1);
  next_loop_1:
    if ( !TRUEP(vector_1))
	goto end_loop_1;
    vectors_in_pools = vectors_in_pools + (SI_Long)1L;
    vector_1 = ISVREF(vector_1,(SI_Long)0L);
    goto next_loop_1;
  end_loop_1:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    index_1 = (SI_Long)1L;
  next_loop_2:
    if (index_1 > IFIX(G2int_maximum_managed_simple_vector_size))
	goto end_loop_2;
    vector_1 = ISVREF(G2int_vector_of_oversized_simple_vector_pools,index_1);
  next_loop_3:
    if ( !TRUEP(vector_1))
	goto end_loop_3;
    vectors_in_pools = vectors_in_pools + (SI_Long)1L;
    vector_1 = ISVREF(vector_1,(SI_Long)0L);
    goto next_loop_3;
  end_loop_3:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:;
    return VALUES_1(FIX(IFIX(G2int_created_simple_vector_pool_vectors) - 
	    vectors_in_pools));
}

Object G2int_simple_vector_pool_memory_usage = UNBOUND;

/* SVP-MEMORY-USAGE */
Object g2int_svp_memory_usage()
{
    x_note_fn_call(20,32);
    return VALUES_1(G2int_simple_vector_pool_memory_usage);
}

Object G2int_replenished_simple_vector_size_limit = UNBOUND;

Object G2int_replenished_simple_vectors_to_make_at_a_time = UNBOUND;

/* ALLOCATE-MANAGED-SIMPLE-VECTOR */
Object g2int_allocate_managed_simple_vector(length_init)
    Object length_init;
{
    Object local_vector_of_simple_vector_pools;
    Object local_simple_vector_pool_counts, available_vector_qm, temp, a;
    Object vectors_made_so_far, new_vector, incff_1_arg, temp_1;
    SI_Long length_1, index_1, ab_loop_repeat_;
    XDeclare_area(1);

    x_note_fn_call(20,33);
    length_1 = IFIX(length_init);
    local_vector_of_simple_vector_pools = G2int_vector_of_simple_vector_pools;
    local_simple_vector_pool_counts = G2int_simple_vector_pool_counts;
    index_1 = length_1;
    available_vector_qm = Nil;
    if (length_1 > IFIX(G2int_maximum_managed_simple_vector_size)) {
	if ((length_1 & (SI_Long)1023L) != (SI_Long)0L)
	    length_1 = (length_1 & (SI_Long)-1024L) + (SI_Long)1024L;
	local_vector_of_simple_vector_pools = 
		G2int_vector_of_oversized_simple_vector_pools;
	local_simple_vector_pool_counts = 
		G2int_oversized_simple_vector_pool_counts;
	index_1 = length_1 >>  -  - (SI_Long)10L;
    }
    available_vector_qm = ISVREF(local_vector_of_simple_vector_pools,index_1);
    if (available_vector_qm) {
	temp = ISVREF(available_vector_qm,(SI_Long)0L);
	ISVREF(local_vector_of_simple_vector_pools,index_1) = temp;
	a = available_vector_qm;
    }
    else
	a = Nil;
    if ( !TRUEP(a)) {
	if (length_1 <= IFIX(G2int_replenished_simple_vector_size_limit)) {
	    if (PUSH_AREA(Dynamic_area,0)) {
		vectors_made_so_far = Nil;
		ab_loop_repeat_ = 
			IFIX(FIXNUM_SUB1(G2int_replenished_simple_vectors_to_make_at_a_time));
		new_vector = Nil;
	      next_loop:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		new_vector = make_array(1,FIX(length_1));
		SVREF(new_vector,FIX((SI_Long)0L)) = vectors_made_so_far;
		vectors_made_so_far = new_vector;
		goto next_loop;
	      end_loop:
		ISVREF(local_vector_of_simple_vector_pools,index_1) = 
			vectors_made_so_far;
		incff_1_arg = 
			G2int_replenished_simple_vectors_to_make_at_a_time;
		temp = FIXNUM_ADD(G2int_created_simple_vector_pool_vectors,
			incff_1_arg);
		G2int_created_simple_vector_pool_vectors = temp;
		incff_1_arg = 
			G2int_replenished_simple_vectors_to_make_at_a_time;
		temp = FIXNUM_ADD(ISVREF(local_simple_vector_pool_counts,
			index_1),incff_1_arg);
		ISVREF(local_simple_vector_pool_counts,index_1) = temp;
		temp_1 = G2int_replenished_simple_vectors_to_make_at_a_time;
		incff_1_arg = FIXNUM_TIMES(temp_1,
			g2int_bytes_per_simple_vector(FIX(length_1)));
		temp = FIXNUM_ADD(G2int_simple_vector_pool_memory_usage,
			incff_1_arg);
		G2int_simple_vector_pool_memory_usage = temp;
		a = make_array(1,FIX(length_1));
	    }
	    POP_AREA(0);
	}
	else {
	    temp = FIXNUM_ADD1(G2int_created_simple_vector_pool_vectors);
	    G2int_created_simple_vector_pool_vectors = temp;
	    temp = FIXNUM_ADD1(ISVREF(local_simple_vector_pool_counts,
		    index_1));
	    ISVREF(local_simple_vector_pool_counts,index_1) = temp;
	    incff_1_arg = g2int_bytes_per_simple_vector(FIX(length_1));
	    temp = FIXNUM_ADD(G2int_simple_vector_pool_memory_usage,
		    incff_1_arg);
	    G2int_simple_vector_pool_memory_usage = temp;
	    if (PUSH_AREA(Dynamic_area,0))
		a = make_array(1,FIX(length_1));
	    POP_AREA(0);
	}
    }
    inline_note_allocate_cons(a,Nil);
    return VALUES_1(a);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-FOR-ARRAY */
Object g2int_allocate_managed_simple_vector_for_array(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(20,34);
    temp = g2int_allocate_managed_simple_vector(length_1);
    return VALUES_1(temp);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-FOR-FLOAT-ARRAY */
Object g2int_allocate_managed_simple_vector_for_float_array(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(20,35);
    temp = g2int_allocate_managed_simple_vector(length_1);
    return VALUES_1(temp);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-FOR-SKIP-LIST */
Object g2int_allocate_managed_simple_vector_for_skip_list(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(20,36);
    temp = g2int_allocate_managed_simple_vector(length_1);
    return VALUES_1(temp);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR */
Object g2int_reclaim_managed_simple_vector(managed_simple_vector)
    Object managed_simple_vector;
{
    Object temp;
    SI_Long length_1, index_1;

    x_note_fn_call(20,37);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_simple_vector));
    inline_note_reclaim_cons(managed_simple_vector,Nil);
    if (length_1 > IFIX(G2int_maximum_managed_simple_vector_size)) {
	index_1 = length_1 >>  -  - (SI_Long)10L;
	temp = ISVREF(G2int_vector_of_oversized_simple_vector_pools,index_1);
	SVREF(managed_simple_vector,FIX((SI_Long)0L)) = temp;
	temp = G2int_vector_of_oversized_simple_vector_pools;
	ISVREF(temp,index_1) = managed_simple_vector;
    }
    else {
	temp = ISVREF(G2int_vector_of_simple_vector_pools,length_1);
	SVREF(managed_simple_vector,FIX((SI_Long)0L)) = temp;
	temp = G2int_vector_of_simple_vector_pools;
	ISVREF(temp,length_1) = managed_simple_vector;
    }
    return VALUES_1(Nil);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR-FOR-ARRAY */
Object g2int_reclaim_managed_simple_vector_for_array(managed_simple_vector)
    Object managed_simple_vector;
{
    Object temp;

    x_note_fn_call(20,38);
    temp = g2int_reclaim_managed_simple_vector(managed_simple_vector);
    return VALUES_1(temp);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR-FOR-FLOAT-ARRAY */
Object g2int_reclaim_managed_simple_vector_for_float_array(managed_simple_vector)
    Object managed_simple_vector;
{
    Object temp;

    x_note_fn_call(20,39);
    temp = g2int_reclaim_managed_simple_vector(managed_simple_vector);
    return VALUES_1(temp);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR-FOR-SKIP-LIST */
Object g2int_reclaim_managed_simple_vector_for_skip_list(managed_simple_vector)
    Object managed_simple_vector;
{
    Object temp;

    x_note_fn_call(20,40);
    temp = g2int_reclaim_managed_simple_vector(managed_simple_vector);
    return VALUES_1(temp);
}

/* FILL-MANAGED-SIMPLE-VECTOR */
Object g2int_fill_managed_simple_vector(managed_simple_vector,value,
	    start_init,end_init)
    Object managed_simple_vector, value, start_init, end_init;
{
    SI_Long start, end, i, ab_loop_bind_;

    x_note_fn_call(20,41);
    start = IFIX(start_init);
    end = IFIX(end_init);
    i = start;
    ab_loop_bind_ = end;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ISVREF(managed_simple_vector,i) = value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* MAKE-PARTIAL-BUFFER-INFO */
Object g2int_make_partial_buffer_info(max_size,grouping_factor,pool_offset,
	    group_shift)
    Object max_size, grouping_factor, pool_offset, group_shift;
{
    Object array;

    x_note_fn_call(20,42);
    array = make_array(1,FIX((SI_Long)4L));
    SVREF(array,FIX((SI_Long)0L)) = max_size;
    SVREF(array,FIX((SI_Long)1L)) = grouping_factor;
    SVREF(array,FIX((SI_Long)2L)) = pool_offset;
    SVREF(array,FIX((SI_Long)3L)) = group_shift;
    return VALUES_1(array);
}

Object G2int_managed_array_allocation_schemes = UNBOUND;

/* BUFFER-SIZE-FOR-PARTIAL-BUFFER */
Object g2int_buffer_size_for_partial_buffer(needed_size_init,
	    allocation_schemes)
    Object needed_size_init, allocation_schemes;
{
    Object allocation_scheme, ab_loop_list_, temp;
    SI_Long needed_size;

    x_note_fn_call(20,43);
    needed_size = IFIX(needed_size_init);
    if ((SI_Long)0L == needed_size)
	needed_size = (SI_Long)1L;
    allocation_scheme = Nil;
    ab_loop_list_ = allocation_schemes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    allocation_scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (needed_size <= IFIX(ISVREF(allocation_scheme,(SI_Long)0L))) {
	temp = FIX((needed_size - (SI_Long)1L | 
		IFIX(FIXNUM_SUB1(ISVREF(allocation_scheme,(SI_Long)1L)))) 
		+ (SI_Long)1L);
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = FIX(needed_size);
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* BUFFER-SIZE-AND-POOL-FOR-PARTIAL-BUFFER */
Object g2int_buffer_size_and_pool_for_partial_buffer(needed_size,
	    allocation_schemes)
    Object needed_size, allocation_schemes;
{
    Object allocation_scheme, ab_loop_list_, temp, temp_1;
    SI_Long maximum_scheme_size;

    x_note_fn_call(20,44);
    if ((SI_Long)0L == IFIX(needed_size))
	needed_size = FIX((SI_Long)1L);
    allocation_scheme = Nil;
    ab_loop_list_ = allocation_schemes;
    maximum_scheme_size = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    allocation_scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    maximum_scheme_size = IFIX(ISVREF(allocation_scheme,(SI_Long)0L));
    if (IFIX(needed_size) <= maximum_scheme_size) {
	temp = FIXNUM_ADD1(FIXNUM_LOGIOR(FIXNUM_SUB1(needed_size),
		FIXNUM_SUB1(ISVREF(allocation_scheme,(SI_Long)1L))));
	temp_1 = FIX(IFIX(ISVREF(allocation_scheme,(SI_Long)2L)) + 
		(IFIX(FIXNUM_SUB1(needed_size)) >> 
		IFIX(FIXNUM_NEGATE(FIXNUM_NEGATE(ISVREF(allocation_scheme,
		(SI_Long)3L))))));
	return VALUES_2(temp,temp_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_2(needed_size,FIX((SI_Long)0L));
    return VALUES_1(Qnil);
}

/* PARTIAL-BUFFER-POOL-INDEX-GIVEN-LENGTH */
Object g2int_partial_buffer_pool_index_given_length(vector_length_init,
	    array_allocation_schemes)
    Object vector_length_init, array_allocation_schemes;
{
    Object scheme, ab_loop_list_, temp;
    SI_Long vector_length, maximum_scheme_size;

    x_note_fn_call(20,45);
    vector_length = IFIX(vector_length_init);
    scheme = Nil;
    ab_loop_list_ = array_allocation_schemes;
    maximum_scheme_size = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    maximum_scheme_size = IFIX(ISVREF(scheme,(SI_Long)0L));
    if (vector_length <= maximum_scheme_size) {
	temp = FIX(IFIX(ISVREF(scheme,(SI_Long)2L)) + (vector_length - 
		(SI_Long)1L >> 
		IFIX(FIXNUM_NEGATE(FIXNUM_NEGATE(ISVREF(scheme,
		(SI_Long)3L))))));
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = FIX((SI_Long)0L);
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* GENSYM-LIST-MAXIMUM-BUFFER-SIZES */
Object g2int_gensym_list_maximum_buffer_sizes(allocation_schemes)
    Object allocation_schemes;
{
    Object maximum_sizes, scheme, ab_loop_list_, temp;
    SI_Long size_so_far, scheme_size, grouping_factor, next_size;

    x_note_fn_call(20,46);
    size_so_far = (SI_Long)0L;
    maximum_sizes = g2int_gensym_cons_1(FIX((SI_Long)0L),Nil);
    scheme = Nil;
    ab_loop_list_ = allocation_schemes;
    scheme_size = (SI_Long)0L;
    grouping_factor = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    scheme_size = IFIX(ISVREF(scheme,(SI_Long)0L));
    grouping_factor = IFIX(ISVREF(scheme,(SI_Long)1L));
    next_size = (SI_Long)0L;
  next_loop_1:
    next_size = size_so_far + grouping_factor;
    if ( !(next_size <= scheme_size))
	goto end_loop_1;
    size_so_far = next_size;
    maximum_sizes = g2int_gensym_cons_1(FIX(size_so_far),maximum_sizes);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    temp = nreverse(maximum_sizes);
    return VALUES_1(temp);
}

Object G2int_managed_array_unique_marker = UNBOUND;

Object G2int_maximum_managed_array_size = UNBOUND;

Object G2int_maximum_in_place_array_size = UNBOUND;

/* ALLOCATE-MANAGED-ARRAY */
Object g2int_allocate_managed_array varargs_1(int, n)
{
    Object length_init;
    Object dont_initialize, make_exactly, spine_vector, svref_new_value;
    SI_Long length_1, temp, full_size_buffers, size_of_partial_buffer;
    SI_Long total_buffers, full_buffer_index, ab_loop_bind_, svref_arg_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(20,47);
    INIT_ARGS_nonrelocating();
    length_init = REQUIRED_ARG_nonrelocating();
    length_1 = IFIX(length_init);
    dont_initialize = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    make_exactly = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    spine_vector = Nil;
    if (length_1 <= IFIX(G2int_maximum_in_place_array_size))
	spine_vector = 
		g2int_allocate_managed_simple_vector_for_array(make_exactly 
		? FIX(length_1 + IFIX(G2int_managed_array_index_offset)) : 
		g2int_buffer_size_for_partial_buffer(FIX(length_1 + 
		IFIX(G2int_managed_array_index_offset)),
		G2int_managed_array_allocation_schemes));
    else {
	temp = length_1 / IFIX(G2int_maximum_managed_array_buffer_size);
	full_size_buffers = temp;
	temp = length_1 % IFIX(G2int_maximum_managed_array_buffer_size);
	size_of_partial_buffer = temp;
	total_buffers = size_of_partial_buffer > (SI_Long)0L ? 
		full_size_buffers + (SI_Long)1L : full_size_buffers;
	spine_vector = 
		g2int_allocate_managed_simple_vector_for_array(make_exactly 
		? FIX(total_buffers + 
		IFIX(G2int_managed_array_index_offset)) : 
		g2int_buffer_size_for_partial_buffer(FIX(total_buffers + 
		IFIX(G2int_managed_array_index_offset)),
		G2int_managed_array_allocation_schemes));
	full_buffer_index = (SI_Long)0L;
	ab_loop_bind_ = full_size_buffers;
      next_loop:
	if (full_buffer_index >= ab_loop_bind_)
	    goto end_loop;
	svref_arg_2 = full_buffer_index + (SI_Long)2L;
	svref_new_value = 
		g2int_allocate_managed_simple_vector_for_array(G2int_maximum_managed_array_buffer_size);
	ISVREF(spine_vector,svref_arg_2) = svref_new_value;
	full_buffer_index = full_buffer_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	if (size_of_partial_buffer > (SI_Long)0L) {
	    svref_arg_2 = total_buffers - (SI_Long)1L + (SI_Long)2L;
	    svref_new_value = 
		    g2int_allocate_managed_simple_vector_for_array(make_exactly 
		    ? FIX(size_of_partial_buffer) : 
		    g2int_buffer_size_for_partial_buffer(FIX(size_of_partial_buffer),
		    G2int_managed_array_allocation_schemes));
	    ISVREF(spine_vector,svref_arg_2) = svref_new_value;
	}
    }
    svref_new_value = G2int_managed_array_unique_marker;
    SVREF(spine_vector,FIX((SI_Long)0L)) = svref_new_value;
    ISVREF(spine_vector,(SI_Long)1L) = FIX(length_1);
    if ( !TRUEP(dont_initialize))
	g2int_fill_managed_array(spine_vector,Nil);
    return VALUES_1(spine_vector);
}

/* RECLAIM-MANAGED-ARRAY */
Object g2int_reclaim_managed_array(managed_array)
    Object managed_array;
{
    SI_Long buffer_index, temp, ab_loop_bind_;

    x_note_fn_call(20,48);
    if (FIXNUM_GT(ISVREF(managed_array,(SI_Long)1L),
	    G2int_maximum_in_place_array_size)) {
	buffer_index = (SI_Long)0L;
	temp = IFIX(FIXNUM_ADD(ISVREF(managed_array,(SI_Long)1L),
		FIXNUM_SUB1(G2int_maximum_managed_array_buffer_size))) / 
		IFIX(G2int_maximum_managed_array_buffer_size);
	ab_loop_bind_ = temp;
      next_loop:
	if (buffer_index >= ab_loop_bind_)
	    goto end_loop;
	g2int_reclaim_managed_simple_vector_for_array(ISVREF(managed_array,
		buffer_index + (SI_Long)2L));
	buffer_index = buffer_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    SVREF(managed_array,FIX((SI_Long)0L)) = Nil;
    g2int_reclaim_managed_simple_vector_for_array(managed_array);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-MANAGED-ARRAY */
Object g2int_reclaim_if_managed_array(managed_array_qm)
    Object managed_array_qm;
{
    x_note_fn_call(20,49);
    if (SIMPLE_VECTOR_P(managed_array_qm) && EQ(ISVREF(managed_array_qm,
	    (SI_Long)0L),G2int_managed_array_unique_marker))
	return g2int_reclaim_managed_array(managed_array_qm);
    else
	return VALUES_1(Nil);
}

/* GSI-ALLOCATE-MANAGED-ARRAY */
Object g2int_gsi_allocate_managed_array(requested_length)
    Object requested_length;
{
    Object modified_requested_length, vector_1, actual_length, svref_arg_2;

    x_note_fn_call(20,50);
    if (FIXNUM_GT(requested_length,G2int_maximum_managed_array_buffer_size))
	modified_requested_length = FIXNUM_ADD1(requested_length);
    else if (IFIX(requested_length) == (SI_Long)0L)
	modified_requested_length = 
		FIXNUM_ADD1(G2int_maximum_managed_array_buffer_size);
    else
	modified_requested_length = requested_length;
    vector_1 = g2int_allocate_managed_simple_vector(modified_requested_length);
    actual_length = length(vector_1);
    if (FIXNUM_GT(actual_length,G2int_maximum_managed_array_buffer_size)) {
	svref_arg_2 = FIXNUM_SUB1(actual_length);
	SVREF(vector_1,svref_arg_2) = requested_length;
    }
    return VALUES_1(vector_1);
}

/* GSI-MANAGED-ARRAY-LENGTH */
Object g2int_gsi_managed_array_length(gsi_managed_array)
    Object gsi_managed_array;
{
    Object actual_length, temp;

    x_note_fn_call(20,51);
    actual_length = length(gsi_managed_array);
    temp = FIXNUM_GT(actual_length,
	    G2int_maximum_managed_array_buffer_size) ? 
	    ISVREF(gsi_managed_array,IFIX(FIXNUM_SUB1(actual_length))) : 
	    actual_length;
    return VALUES_1(temp);
}

/* GSI-RECLAIM-MANAGED-ARRAY */
Object g2int_gsi_reclaim_managed_array(managed_array)
    Object managed_array;
{
    x_note_fn_call(20,52);
    g2int_reclaim_managed_simple_vector(managed_array);
    return VALUES_1(Nil);
}

/* COPY-SIMPLE-VECTOR-PORTION-FUNCTION */
Object g2int_copy_simple_vector_portion_function(source_simple_vector,
	    source_index,element_count,destination_simple_vector,
	    destination_index)
    Object source_simple_vector, source_index, element_count;
    Object destination_simple_vector, destination_index;
{
    Object gensymed_symbol, gensymed_symbol_3, svref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;

    x_note_fn_call(20,53);
    gensymed_symbol = source_simple_vector;
    gensymed_symbol_1 = IFIX(source_index);
    gensymed_symbol_2 = gensymed_symbol_1 + IFIX(element_count);
    gensymed_symbol_3 = destination_simple_vector;
    gensymed_symbol_4 = IFIX(destination_index);
  next_loop:
    if ( !(gensymed_symbol_1 < gensymed_symbol_2))
	goto end_loop;
    svref_new_value = ISVREF(gensymed_symbol,gensymed_symbol_1);
    ISVREF(gensymed_symbol_3,gensymed_symbol_4) = svref_new_value;
    gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
    gensymed_symbol_4 = gensymed_symbol_4 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ADJUST-MANAGED-ARRAY */
Object g2int_adjust_managed_array varargs_1(int, n)
{
    Object managed_array, new_length;
    Object dont_copy, dont_initialize, old_full_buffers, old_remainder;
    Object old_total_buffers;
    SI_Long old_length, rounded_new_length, temp, new_full_buffers;
    SI_Long new_remainder, new_total_buffers, index_1, ab_loop_bind_;
    char temp_1;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(20,54);
    INIT_ARGS_nonrelocating();
    managed_array = REQUIRED_ARG_nonrelocating();
    new_length = REQUIRED_ARG_nonrelocating();
    dont_copy = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    dont_initialize = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    old_length = IFIX(ISVREF(managed_array,(SI_Long)1L));
    rounded_new_length = (SI_Long)0L;
    if (IFIX(new_length) == old_length)
	return VALUES_1(managed_array);
    if (old_length > IFIX(G2int_maximum_in_place_array_size) && 
	    FIXNUM_GT(new_length,G2int_maximum_in_place_array_size)) {
	result = g2int_chestnut_floorf_function(FIX(old_length),
		G2int_maximum_managed_array_buffer_size);
	MVS_2(result,old_full_buffers,old_remainder);
	temp = IFIX(new_length) / 
		IFIX(G2int_maximum_managed_array_buffer_size);
	new_full_buffers = temp;
	temp = IFIX(new_length) % 
		IFIX(G2int_maximum_managed_array_buffer_size);
	new_remainder = temp;
	old_total_buffers = IFIX(old_remainder) > (SI_Long)0L ? 
		FIXNUM_ADD1(old_full_buffers) : old_full_buffers;
	new_total_buffers = new_remainder > (SI_Long)0L ? new_full_buffers 
		+ (SI_Long)1L : new_full_buffers;
	if (new_total_buffers == IFIX(old_total_buffers)) {
	    g2int_adjust_final_buffer_of_managed_array(managed_array,
		    dont_copy,dont_initialize,FIX(new_total_buffers),
		    IFIX(old_remainder) == (SI_Long)0L ? 
		    G2int_maximum_managed_array_buffer_size : 
		    old_remainder,new_remainder == (SI_Long)0L ? 
		    G2int_maximum_managed_array_buffer_size : 
		    FIX(new_remainder));
	    SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
	}
	else if (new_total_buffers > IFIX(old_total_buffers))
	    managed_array = g2int_grow_managed_array(managed_array,
		    dont_copy,dont_initialize,old_full_buffers,
		    old_remainder,old_total_buffers,new_length,
		    FIX(new_full_buffers),FIX(new_remainder),
		    FIX(new_total_buffers));
	else
	    managed_array = g2int_shrink_managed_array(managed_array,
		    dont_copy,old_total_buffers,new_length,
		    FIX(new_full_buffers),FIX(new_remainder),
		    FIX(new_total_buffers));
    }
    else {
	if (old_length <= IFIX(G2int_maximum_in_place_array_size) && 
		FIXNUM_LE(new_length,G2int_maximum_in_place_array_size)) {
	    rounded_new_length = 
		    IFIX(g2int_buffer_size_for_partial_buffer(FIXNUM_ADD(new_length,
		    G2int_managed_array_index_offset),
		    G2int_managed_array_allocation_schemes));
	    temp_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_array)) == 
		    rounded_new_length;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
	    if (IFIX(new_length) > old_length &&  !TRUEP(dont_initialize)) {
		index_1 = IFIX(G2int_managed_array_index_offset) + old_length;
		ab_loop_bind_ = 
			IFIX(FIXNUM_ADD(G2int_managed_array_index_offset,
			new_length));
	      next_loop:
		if (index_1 >= ab_loop_bind_)
		    goto end_loop;
		ISVREF(managed_array,index_1) = Nil;
		index_1 = index_1 + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else if (IFIX(new_length) > old_length)
	    managed_array = g2int_grow_managed_array(managed_array,
		    dont_copy,dont_initialize,Nil,Nil,Nil,new_length,Nil,
		    Nil,Nil);
	else
	    managed_array = g2int_shrink_managed_array(managed_array,
		    dont_copy,Nil,new_length,Nil,Nil,Nil);
    }
    return VALUES_1(managed_array);
}

/* ADJUST-FINAL-BUFFER-OF-MANAGED-ARRAY */
Object g2int_adjust_final_buffer_of_managed_array(managed_array,dont_copy,
	    dont_initialize,total_buffers,old_final_buffer_length,
	    new_final_buffer_length)
    Object managed_array, dont_copy, dont_initialize, total_buffers;
    Object old_final_buffer_length, new_final_buffer_length;
{
    Object old_buffer, old_actual_buffer_length, new_actual_buffer_length;
    Object new_buffer;
    SI_Long svref_arg_2, index_1, ab_loop_bind_;

    x_note_fn_call(20,55);
    old_buffer = ISVREF(managed_array,IFIX(FIXNUM_SUB1(total_buffers)) + 
	    (SI_Long)2L);
    old_actual_buffer_length = length(old_buffer);
    new_actual_buffer_length = 
	    g2int_buffer_size_for_partial_buffer(new_final_buffer_length,
	    G2int_managed_array_allocation_schemes);
    if (FIXNUM_NE(new_actual_buffer_length,old_actual_buffer_length)) {
	new_buffer = 
		g2int_allocate_managed_simple_vector(new_actual_buffer_length);
	if ( !TRUEP(dont_copy))
	    g2int_copy_simple_vector_portion_function(old_buffer,
		    FIX((SI_Long)0L),FIXNUM_MIN(new_final_buffer_length,
		    old_final_buffer_length),new_buffer,FIX((SI_Long)0L));
	svref_arg_2 = IFIX(FIXNUM_SUB1(total_buffers)) + (SI_Long)2L;
	ISVREF(managed_array,svref_arg_2) = new_buffer;
	g2int_reclaim_managed_simple_vector(old_buffer);
	old_buffer = new_buffer;
    }
    if ( !TRUEP(dont_initialize) && FIXNUM_GT(new_final_buffer_length,
	    old_final_buffer_length)) {
	index_1 = IFIX(old_final_buffer_length);
	ab_loop_bind_ = IFIX(new_final_buffer_length);
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(old_buffer,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GROW-MANAGED-ARRAY */
Object g2int_grow_managed_array(managed_array,dont_copy,dont_initialize,
	    old_full_buffers,old_remainder,old_total_buffers,new_length,
	    new_full_buffers,new_remainder,new_total_buffers)
    Object managed_array, dont_copy, dont_initialize, old_full_buffers;
    Object old_remainder, old_total_buffers, new_length, new_full_buffers;
    Object new_remainder, new_total_buffers;
{
    Object old_managed_array, new_spine_length, new_spine, svref_new_value;
    Object new_buffer;
    SI_Long spine_index, ab_loop_bind_, buffer_index, svref_arg_2;

    x_note_fn_call(20,56);
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    G2int_maximum_in_place_array_size)) {
	old_managed_array = managed_array;
	managed_array = g2int_allocate_managed_array(1,new_length);
	g2int_copy_managed_array_portion(old_managed_array,
		FIX((SI_Long)0L),ISVREF(old_managed_array,(SI_Long)1L),
		managed_array,FIX((SI_Long)0L));
	g2int_reclaim_managed_array(old_managed_array);
    }
    else {
	if (FIXNUM_NE(old_full_buffers,old_total_buffers))
	    g2int_adjust_final_buffer_of_managed_array(managed_array,
		    dont_copy,dont_initialize,old_total_buffers,
		    old_remainder,G2int_maximum_managed_array_buffer_size);
	new_spine_length = 
		g2int_buffer_size_for_partial_buffer(FIX(IFIX(new_total_buffers) 
		+ (SI_Long)2L),G2int_managed_array_allocation_schemes);
	if (FIXNUM_NE(length(managed_array),new_spine_length)) {
	    new_spine = 
		    g2int_allocate_managed_simple_vector_for_array(new_spine_length);
	    g2int_copy_simple_vector_portion_function(managed_array,
		    FIX((SI_Long)2L),old_total_buffers,new_spine,
		    FIX((SI_Long)2L));
	    SVREF(managed_array,FIX((SI_Long)0L)) = Nil;
	    g2int_reclaim_managed_simple_vector_for_array(managed_array);
	    svref_new_value = G2int_managed_array_unique_marker;
	    SVREF(new_spine,FIX((SI_Long)0L)) = svref_new_value;
	    managed_array = new_spine;
	}
	SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
	spine_index = IFIX(old_total_buffers);
	ab_loop_bind_ = IFIX(new_full_buffers);
	new_buffer = Nil;
      next_loop:
	if (spine_index >= ab_loop_bind_)
	    goto end_loop;
	new_buffer = 
		g2int_allocate_managed_simple_vector_for_array(G2int_maximum_managed_array_buffer_size);
	if ( !TRUEP(dont_initialize)) {
	    buffer_index = (SI_Long)0L;
	  next_loop_1:
	    if (buffer_index >= IFIX(G2int_maximum_managed_array_buffer_size))
		goto end_loop_1;
	    ISVREF(new_buffer,buffer_index) = Nil;
	    buffer_index = buffer_index + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	svref_arg_2 = spine_index + (SI_Long)2L;
	ISVREF(managed_array,svref_arg_2) = new_buffer;
	spine_index = spine_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	if (FIXNUM_NE(new_full_buffers,new_total_buffers)) {
	    new_buffer = 
		    g2int_allocate_managed_simple_vector(g2int_buffer_size_for_partial_buffer(new_remainder,
		    G2int_managed_array_allocation_schemes));
	    if ( !TRUEP(dont_initialize)) {
		buffer_index = (SI_Long)0L;
		ab_loop_bind_ = IFIX(new_remainder);
	      next_loop_2:
		if (buffer_index >= ab_loop_bind_)
		    goto end_loop_2;
		ISVREF(new_buffer,buffer_index) = Nil;
		buffer_index = buffer_index + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
	    }
	    svref_arg_2 = IFIX(FIXNUM_SUB1(new_total_buffers)) + (SI_Long)2L;
	    ISVREF(managed_array,svref_arg_2) = new_buffer;
	}
    }
    return VALUES_1(managed_array);
}

/* SHRINK-MANAGED-ARRAY */
Object g2int_shrink_managed_array(managed_array,dont_copy,
	    old_total_buffers,new_length,new_full_buffers,new_remainder,
	    new_total_buffers)
    Object managed_array, dont_copy, old_total_buffers, new_length;
    Object new_full_buffers, new_remainder, new_total_buffers;
{
    Object old_managed_array, new_spine_length, new_spine, svref_new_value;
    SI_Long buffer_index, ab_loop_bind_;

    x_note_fn_call(20,57);
    if (FIXNUM_LE(new_length,G2int_maximum_in_place_array_size)) {
	old_managed_array = managed_array;
	managed_array = g2int_allocate_managed_array(1,new_length);
	g2int_copy_managed_array_portion(old_managed_array,
		FIX((SI_Long)0L),ISVREF(managed_array,(SI_Long)1L),
		managed_array,FIX((SI_Long)0L));
	g2int_reclaim_managed_array(old_managed_array);
    }
    else {
	buffer_index = IFIX(new_total_buffers);
	ab_loop_bind_ = IFIX(old_total_buffers);
      next_loop:
	if (buffer_index >= ab_loop_bind_)
	    goto end_loop;
	g2int_reclaim_managed_simple_vector_for_array(ISVREF(managed_array,
		buffer_index + (SI_Long)2L));
	buffer_index = buffer_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	if (FIXNUM_NE(new_full_buffers,new_total_buffers))
	    g2int_adjust_final_buffer_of_managed_array(managed_array,
		    dont_copy,T,new_total_buffers,
		    G2int_maximum_managed_array_buffer_size,new_remainder);
	new_spine_length = 
		g2int_buffer_size_for_partial_buffer(FIX(IFIX(new_total_buffers) 
		+ (SI_Long)2L),G2int_managed_array_allocation_schemes);
	if (FIXNUM_NE(new_spine_length,length(managed_array))) {
	    new_spine = 
		    g2int_allocate_managed_simple_vector_for_array(new_spine_length);
	    g2int_copy_simple_vector_portion_function(managed_array,
		    FIX((SI_Long)2L),new_total_buffers,new_spine,
		    FIX((SI_Long)2L));
	    SVREF(managed_array,FIX((SI_Long)0L)) = Nil;
	    g2int_reclaim_managed_simple_vector(managed_array);
	    svref_new_value = G2int_managed_array_unique_marker;
	    SVREF(new_spine,FIX((SI_Long)0L)) = svref_new_value;
	    managed_array = new_spine;
	}
	SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
    }
    return VALUES_1(managed_array);
}

/* SHRINK-OR-DELETE-MANAGED-ARRAY-NULL-ELEMENTS */
Object g2int_shrink_or_delete_managed_array_null_elements(managed_array)
    Object managed_array;
{
    SI_Long array_length, index_1, new_length;

    x_note_fn_call(20,58);
    array_length = IFIX(ISVREF(managed_array,(SI_Long)1L));
    index_1 = array_length - (SI_Long)1L;
  next_loop:
    if (index_1 < (SI_Long)0L)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    G2int_maximum_in_place_array_size) ? 
	    TRUEP(ISVREF(managed_array,index_1 + 
	    IFIX(G2int_managed_array_index_offset))) : 
	    TRUEP(ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L))) {
	new_length = index_1 + (SI_Long)1L;
	if (new_length == array_length)
	    return VALUES_1(managed_array);
	else
	    return g2int_adjust_managed_array(2,managed_array,FIX(new_length));
    }
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:
    g2int_reclaim_managed_array(managed_array);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* COPY-FROM-SIMPLE-VECTOR-INTO-MANAGED-ARRAY */
Object g2int_copy_from_simple_vector_into_managed_array(simple_vector,
	    vector_index_init,count_init,managed_array,array_index_init)
    Object simple_vector, vector_index_init, count_init, managed_array;
    Object array_index_init;
{
    Object temp, temp_1;
    SI_Long vector_index, count_1, array_index, buffer_index;
    SI_Long managed_buffer_number, elements_to_copy, temp_2, decff_1_arg;
    SI_Long incff_1_arg;
    Object result;

    x_note_fn_call(20,59);
    vector_index = IFIX(vector_index_init);
    count_1 = IFIX(count_init);
    array_index = IFIX(array_index_init);
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    G2int_maximum_in_place_array_size))
	return g2int_copy_simple_vector_portion_function(simple_vector,
		FIX(vector_index),FIX(count_1),managed_array,
		FIX(array_index + IFIX(G2int_managed_array_index_offset)));
    else {
	result = g2int_chestnut_floorf_function(FIX(array_index),
		G2int_maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	buffer_index = IFIX(temp_1);
	managed_buffer_number = IFIX(temp);
	elements_to_copy = (SI_Long)0L;
      next_loop:
	if ( !(count_1 > (SI_Long)0L))
	    goto end_loop;
	temp_2 = IFIX(G2int_maximum_managed_array_buffer_size) - buffer_index;
	elements_to_copy = MIN(temp_2,count_1);
	g2int_copy_simple_vector_portion_function(simple_vector,
		FIX(vector_index),FIX(elements_to_copy),
		ISVREF(managed_array,managed_buffer_number + (SI_Long)2L),
		FIX(buffer_index));
	decff_1_arg = elements_to_copy;
	count_1 = count_1 - decff_1_arg;
	incff_1_arg = elements_to_copy;
	vector_index = vector_index + incff_1_arg;
	managed_buffer_number = managed_buffer_number + (SI_Long)1L;
	buffer_index = (SI_Long)0L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COPY-FROM-MANAGED-ARRAY-INTO-SIMPLE-VECTOR */
Object g2int_copy_from_managed_array_into_simple_vector(managed_array,
	    array_index_init,count_init,simple_vector,vector_index_init)
    Object managed_array, array_index_init, count_init, simple_vector;
    Object vector_index_init;
{
    Object temp, temp_1;
    SI_Long array_index, count_1, vector_index, buffer_index;
    SI_Long managed_buffer_number, elements_to_copy, temp_2, decff_1_arg;
    SI_Long incff_1_arg;
    Object result;

    x_note_fn_call(20,60);
    array_index = IFIX(array_index_init);
    count_1 = IFIX(count_init);
    vector_index = IFIX(vector_index_init);
    if (FIXNUM_LT(SVREF(managed_array,FIX((SI_Long)1L)),
	    G2int_maximum_in_place_array_size))
	return g2int_copy_simple_vector_portion_function(managed_array,
		FIX(array_index + IFIX(G2int_managed_array_index_offset)),
		FIX(count_1),simple_vector,FIX(vector_index));
    else {
	result = g2int_chestnut_floorf_function(FIX(array_index),
		G2int_maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	buffer_index = IFIX(temp_1);
	managed_buffer_number = IFIX(temp);
	elements_to_copy = (SI_Long)0L;
      next_loop:
	if ( !(count_1 > (SI_Long)0L))
	    goto end_loop;
	temp_2 = IFIX(G2int_maximum_managed_array_buffer_size) - buffer_index;
	elements_to_copy = MIN(temp_2,count_1);
	g2int_copy_simple_vector_portion_function(ISVREF(managed_array,
		managed_buffer_number + (SI_Long)2L),FIX(buffer_index),
		FIX(elements_to_copy),simple_vector,FIX(vector_index));
	decff_1_arg = elements_to_copy;
	count_1 = count_1 - decff_1_arg;
	incff_1_arg = elements_to_copy;
	vector_index = vector_index + incff_1_arg;
	managed_buffer_number = managed_buffer_number + (SI_Long)1L;
	buffer_index = (SI_Long)0L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COPY-MANAGED-ARRAY-PORTION */
Object g2int_copy_managed_array_portion(source_array,source_index_init,
	    element_count_init,destination_array,destination_index_init)
    Object source_array, source_index_init, element_count_init;
    Object destination_array, destination_index_init;
{
    Object temp, temp_1, ab_loop_iter_flag_;
    SI_Long source_index, element_count, destination_index;
    SI_Long source_buffer_index, source_buffer_number, temp_2;
    SI_Long elements_to_copy, decff_1_arg, incff_1_arg;
    Object result;

    x_note_fn_call(20,61);
    source_index = IFIX(source_index_init);
    element_count = IFIX(element_count_init);
    destination_index = IFIX(destination_index_init);
    if (element_count > (SI_Long)0L) {
	result = g2int_chestnut_floorf_function(FIX(source_index),
		G2int_maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	source_buffer_index = IFIX(temp_1);
	source_buffer_number = IFIX(temp);
	if (FIXNUM_LE(SVREF(source_array,FIX((SI_Long)1L)),
		G2int_maximum_in_place_array_size))
	    return g2int_copy_from_simple_vector_into_managed_array(source_array,
		    FIX(source_index + 
		    IFIX(G2int_managed_array_index_offset)),
		    FIX(element_count),destination_array,
		    FIX(destination_index));
	else {
	    temp_2 = IFIX(G2int_maximum_managed_array_buffer_size) - 
		    source_buffer_index;
	    elements_to_copy = MIN(temp_2,element_count);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !(element_count > (SI_Long)0L))
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		temp_2 = IFIX(G2int_maximum_managed_array_buffer_size);
		elements_to_copy = MIN(temp_2,element_count);
	    }
	    g2int_copy_from_simple_vector_into_managed_array(ISVREF(source_array,
		    source_buffer_number + (SI_Long)2L),
		    FIX(source_buffer_index),FIX(elements_to_copy),
		    destination_array,FIX(destination_index));
	    decff_1_arg = elements_to_copy;
	    element_count = element_count - decff_1_arg;
	    incff_1_arg = elements_to_copy;
	    destination_index = destination_index + incff_1_arg;
	    source_buffer_number = source_buffer_number + (SI_Long)1L;
	    source_buffer_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* FILL-MANAGED-ARRAY */
Object g2int_fill_managed_array(managed_array,thing)
    Object managed_array, thing;
{
    Object temp, temp_1, full_buffer, last_buffer;
    SI_Long length_1, index_1, ab_loop_bind_, partial_buffer, full_buffers;
    SI_Long buffer_index;
    Object result;

    x_note_fn_call(20,62);
    length_1 = IFIX(SVREF(managed_array,FIX((SI_Long)1L)));
    if (length_1 <= IFIX(G2int_maximum_in_place_array_size)) {
	index_1 = IFIX(G2int_managed_array_index_offset);
	ab_loop_bind_ = length_1 + IFIX(G2int_managed_array_index_offset);
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(managed_array,index_1) = thing;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	result = g2int_chestnut_floorf_function(FIX(length_1),
		G2int_maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	partial_buffer = IFIX(temp_1);
	full_buffers = IFIX(temp);
	buffer_index = (SI_Long)0L;
	ab_loop_bind_ = full_buffers;
	full_buffer = Nil;
      next_loop_1:
	if (buffer_index >= ab_loop_bind_)
	    goto end_loop_1;
	full_buffer = ISVREF(managed_array,buffer_index + (SI_Long)2L);
	index_1 = (SI_Long)0L;
      next_loop_2:
	if (index_1 >= IFIX(G2int_maximum_managed_array_buffer_size))
	    goto end_loop_2;
	ISVREF(full_buffer,index_1) = thing;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	buffer_index = buffer_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	if (partial_buffer != (SI_Long)0L) {
	    last_buffer = ISVREF(managed_array,full_buffers + (SI_Long)2L);
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = partial_buffer;
	  next_loop_3:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop_3;
	    ISVREF(last_buffer,index_1) = thing;
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	}
	return VALUES_1(managed_array);
    }
}

/* ROTATE-MANAGED-ARRAY */
Object g2int_rotate_managed_array(managed_array,index_to_rotate)
    Object managed_array, index_to_rotate;
{
    Object new_array_or_vector, svref_new_value, ab_loop_iter_flag_;
    SI_Long length_1, high_shift_size, copy_index, ab_loop_bind_, from_index;
    SI_Long to_index, buffer_index, temp, svref_arg_2;

    x_note_fn_call(20,63);
    if (IFIX(index_to_rotate) != (SI_Long)0L) {
	length_1 = IFIX(ISVREF(managed_array,(SI_Long)1L));
	new_array_or_vector = Nil;
	high_shift_size = length_1 - IFIX(index_to_rotate);
	if (length_1 <= IFIX(G2int_maximum_in_place_array_size)) {
	    new_array_or_vector = 
		    g2int_allocate_managed_simple_vector(index_to_rotate);
	    copy_index = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(index_to_rotate);
	  next_loop:
	    if (copy_index >= ab_loop_bind_)
		goto end_loop;
	    svref_new_value = ISVREF(managed_array,copy_index + 
		    IFIX(G2int_managed_array_index_offset));
	    ISVREF(new_array_or_vector,copy_index) = svref_new_value;
	    copy_index = copy_index + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    from_index = IFIX(FIXNUM_ADD(index_to_rotate,
		    G2int_managed_array_index_offset));
	    ab_loop_bind_ = length_1 + IFIX(G2int_managed_array_index_offset);
	    to_index = IFIX(G2int_managed_array_index_offset);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if (from_index >= ab_loop_bind_)
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_iter_flag_))
		to_index = to_index + (SI_Long)1L;
	    svref_new_value = ISVREF(managed_array,from_index);
	    ISVREF(managed_array,to_index) = svref_new_value;
	    ab_loop_iter_flag_ = Nil;
	    from_index = from_index + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    to_index = high_shift_size + 
		    IFIX(G2int_managed_array_index_offset);
	    ab_loop_bind_ = length_1 + IFIX(G2int_managed_array_index_offset);
	    from_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = T;
	  next_loop_2:
	    if (to_index >= ab_loop_bind_)
		goto end_loop_2;
	    if ( !TRUEP(ab_loop_iter_flag_))
		from_index = from_index + (SI_Long)1L;
	    svref_new_value = ISVREF(new_array_or_vector,from_index);
	    ISVREF(managed_array,to_index) = svref_new_value;
	    ab_loop_iter_flag_ = Nil;
	    to_index = to_index + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:;
	    g2int_reclaim_managed_simple_vector_for_array(new_array_or_vector);
	}
	else {
	    new_array_or_vector = g2int_allocate_managed_array(1,
		    FIX(length_1));
	    g2int_copy_managed_array_portion(managed_array,index_to_rotate,
		    FIX(high_shift_size),new_array_or_vector,FIX((SI_Long)0L));
	    g2int_copy_managed_array_portion(managed_array,
		    FIX((SI_Long)0L),index_to_rotate,new_array_or_vector,
		    FIX(high_shift_size));
	    buffer_index = (SI_Long)0L;
	    temp = (length_1 + 
		    IFIX(FIXNUM_SUB1(G2int_maximum_managed_array_buffer_size))) 
		    / IFIX(G2int_maximum_managed_array_buffer_size);
	    ab_loop_bind_ = temp;
	  next_loop_3:
	    if (buffer_index >= ab_loop_bind_)
		goto end_loop_3;
	    g2int_reclaim_managed_simple_vector_for_array(ISVREF(managed_array,
		    buffer_index + (SI_Long)2L));
	    svref_arg_2 = buffer_index + (SI_Long)2L;
	    svref_new_value = ISVREF(new_array_or_vector,buffer_index + 
		    (SI_Long)2L);
	    ISVREF(managed_array,svref_arg_2) = svref_new_value;
	    buffer_index = buffer_index + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	    g2int_reclaim_managed_simple_vector_for_array(new_array_or_vector);
	}
    }
    return VALUES_1(managed_array);
}

/* INSERT-INTO-MANAGED-ARRAY */
Object g2int_insert_into_managed_array(managed_array,position_1,new_element)
    Object managed_array, position_1, new_element;
{
    Object temp, svref_new_value;
    SI_Long length_1, index_1, ab_loop_bind_, svref_arg_2, gensymed_symbol;

    x_note_fn_call(20,64);
    length_1 = IFIX(SVREF(managed_array,FIX((SI_Long)1L)));
    managed_array = g2int_adjust_managed_array(2,managed_array,
	    FIX(length_1 + (SI_Long)1L));
    index_1 = length_1;
    ab_loop_bind_ = IFIX(FIXNUM_ADD1(position_1));
  next_loop:
    if (index_1 < ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    G2int_maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(G2int_managed_array_index_offset);
	gensymed_symbol = index_1 - (SI_Long)1L;
	temp = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		G2int_maximum_in_place_array_size) ? ISVREF(managed_array,
		gensymed_symbol + IFIX(G2int_managed_array_index_offset)) :
		 ISVREF(ISVREF(managed_array,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	ISVREF(managed_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	gensymed_symbol = index_1 - (SI_Long)1L;
	svref_new_value = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		G2int_maximum_in_place_array_size) ? ISVREF(managed_array,
		gensymed_symbol + IFIX(G2int_managed_array_index_offset)) :
		 ISVREF(ISVREF(managed_array,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    G2int_maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(position_1,G2int_managed_array_index_offset);
	SVREF(managed_array,temp) = new_element;
    }
    else {
	temp = ISVREF(managed_array,(IFIX(position_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(position_1) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = new_element;
    }
    return VALUES_1(managed_array);
}

/* DELETE-MANAGED-ARRAY-ELEMENT */
Object g2int_delete_managed_array_element(managed_array,position_1)
    Object managed_array, position_1;
{
    Object temp, svref_new_value;
    SI_Long length_1, index_1, ab_loop_bind_, gensymed_symbol, svref_arg_2;

    x_note_fn_call(20,65);
    length_1 = IFIX(SVREF(managed_array,FIX((SI_Long)1L)));
    index_1 = IFIX(FIXNUM_ADD1(position_1));
    ab_loop_bind_ = length_1;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = index_1 - (SI_Long)1L;
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    G2int_maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(G2int_managed_array_index_offset);
	temp = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		G2int_maximum_in_place_array_size) ? ISVREF(managed_array,
		index_1 + IFIX(G2int_managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	ISVREF(managed_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_array,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	svref_new_value = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		G2int_maximum_in_place_array_size) ? ISVREF(managed_array,
		index_1 + IFIX(G2int_managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return g2int_adjust_managed_array(2,managed_array,FIX(length_1 - 
	    (SI_Long)1L));
}

Object G2int_maximum_byte_vector_length = UNBOUND;

Object G2int_byte_vector_allocation_schemes = UNBOUND;

/* MAKE-BYTE-VECTOR-POOLS */
Object g2int_make_byte_vector_pools(initial_elt)
    Object initial_elt;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(20,66);
    if (PUSH_AREA(Dynamic_area,0))
	result = make_array(3,
		FIXNUM_ADD1(g2int_partial_buffer_pool_index_given_length(G2int_maximum_byte_vector_length,
		G2int_byte_vector_allocation_schemes)),Kinitial_element,
		initial_elt);
    POP_AREA(0);
    return result;
}

Object G2int_byte_vector_pools = UNBOUND;

Object G2int_byte_vector_pool_counts = UNBOUND;

Object G2int_allocated_byte_vectors = UNBOUND;

/* OUTSTANDING-BYTE-VECTORS */
Object g2int_outstanding_byte_vectors()
{
    Object decff_1_arg;
    SI_Long outstanding, pool_index, ab_loop_bind_;

    x_note_fn_call(20,67);
    outstanding = IFIX(G2int_allocated_byte_vectors);
    pool_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(G2int_byte_vector_pools));
  next_loop:
    if (pool_index >= ab_loop_bind_)
	goto end_loop;
    decff_1_arg = length(ISVREF(G2int_byte_vector_pools,pool_index));
    outstanding = outstanding - IFIX(decff_1_arg);
    pool_index = pool_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(outstanding));
    return VALUES_1(Qnil);
}

Object G2int_bytes_in_allocated_byte_vectors = UNBOUND;

/* BYTE-VECTOR-MEMORY-USAGE */
Object g2int_byte_vector_memory_usage()
{
    x_note_fn_call(20,68);
    return VALUES_1(G2int_bytes_in_allocated_byte_vectors);
}

static Object list_constant;       /* # */

/* ALLOCATE-BYTE-VECTOR */
Object g2int_allocate_byte_vector(required_size)
    Object required_size;
{
    Object temp, pool_index, pool_list, vector_1, temp_1, svref_new_value;
    Object incff_1_arg;
    SI_Long rounded_up_length;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(20,69);
    if (FIXNUM_GT(required_size,G2int_maximum_byte_vector_length))
	error((SI_Long)3L,
		"Attempted to make a byte vector ~a elements long.  Maximum is ~a.",
		required_size,G2int_maximum_byte_vector_length);
    result = g2int_buffer_size_and_pool_for_partial_buffer(required_size,
	    G2int_byte_vector_allocation_schemes);
    MVS_2(result,temp,pool_index);
    rounded_up_length = IFIX(temp);
    pool_list = ISVREF(G2int_byte_vector_pools,IFIX(pool_index));
    if (pool_list) {
	vector_1 = CAR(pool_list);
	temp_1 = G2int_byte_vector_pools;
	svref_new_value = CDR(pool_list);
	SVREF(temp_1,pool_index) = svref_new_value;
	inline_note_reclaim_cons(pool_list,Qg2int_gensym);
	temp_1 = G2int_available_gensym_conses;
	M_CDR(pool_list) = temp_1;
	G2int_available_gensym_conses = pool_list;
	return VALUES_1(vector_1);
    }
    else {
	temp_1 = FIXNUM_ADD1(G2int_allocated_byte_vectors);
	G2int_allocated_byte_vectors = temp_1;
	incff_1_arg = 
		g2int_bytes_per_unsigned_byte_8_simple_array(FIX(rounded_up_length));
	temp_1 = FIXNUM_ADD(G2int_bytes_in_allocated_byte_vectors,incff_1_arg);
	G2int_bytes_in_allocated_byte_vectors = temp_1;
	if (pool_index) {
	    temp_1 = G2int_byte_vector_pool_counts;
	    svref_new_value = FIXNUM_ADD1(ISVREF(temp_1,IFIX(pool_index)));
	    SVREF(temp_1,pool_index) = svref_new_value;
	}
	if (PUSH_AREA(Dynamic_area,0))
	    result = make_array(3,FIX(rounded_up_length),Kelement_type,
		    list_constant);
	POP_AREA(0);
	return result;
    }
}

/* RECLAIM-BYTE-VECTOR */
Object g2int_reclaim_byte_vector(byte_vector)
    Object byte_vector;
{
    Object svref_arg_1, svref_new_value;
    SI_Long array_length, pool_index;

    x_note_fn_call(20,70);
    array_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(byte_vector));
    pool_index = 
	    IFIX(g2int_partial_buffer_pool_index_given_length(FIX(array_length),
	    G2int_byte_vector_allocation_schemes));
    svref_arg_1 = G2int_byte_vector_pools;
    svref_new_value = g2int_gensym_cons_1(byte_vector,
	    ISVREF(G2int_byte_vector_pools,pool_index));
    ISVREF(svref_arg_1,pool_index) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_maximum_byte_vector_16_length = UNBOUND;

Object G2int_maximum_wide_string_length = UNBOUND;

Object G2int_byte_vector_16_allocation_schemes = UNBOUND;

/* MAKE-BYTE-VECTOR-16-POOLS */
Object g2int_make_byte_vector_16_pools(initial_elt)
    Object initial_elt;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(20,71);
    if (PUSH_AREA(Dynamic_area,0))
	result = make_array(3,
		FIXNUM_ADD1(g2int_partial_buffer_pool_index_given_length(G2int_maximum_byte_vector_16_length,
		G2int_byte_vector_16_allocation_schemes)),Kinitial_element,
		initial_elt);
    POP_AREA(0);
    return result;
}

Object G2int_byte_vector_16_pools = UNBOUND;

Object G2int_byte_vector_16_pool_counts = UNBOUND;

Object G2int_allocated_byte_vector_16_vectors = UNBOUND;

/* OUTSTANDING-BYTE-VECTOR-16-VECTORS */
Object g2int_outstanding_byte_vector_16_vectors()
{
    Object decff_1_arg;
    SI_Long outstanding, pool_index, ab_loop_bind_;

    x_note_fn_call(20,72);
    outstanding = IFIX(G2int_allocated_byte_vector_16_vectors);
    pool_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(G2int_byte_vector_16_pools));
  next_loop:
    if (pool_index >= ab_loop_bind_)
	goto end_loop;
    decff_1_arg = length(ISVREF(G2int_byte_vector_16_pools,pool_index));
    outstanding = outstanding - IFIX(decff_1_arg);
    pool_index = pool_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(outstanding));
    return VALUES_1(Qnil);
}

Object G2int_bytes_in_allocated_byte_vector_16_vectors = UNBOUND;

/* BYTE-VECTOR-16-MEMORY-USAGE */
Object g2int_byte_vector_16_memory_usage()
{
    x_note_fn_call(20,73);
    return VALUES_1(G2int_bytes_in_allocated_byte_vector_16_vectors);
}

Object G2int_free_malloced_arrays = UNBOUND;

Object G2int_largest_non_malloced_byte_vector_16_pool_index = UNBOUND;

Object G2int_byte_vector_16_pool_number_to_malloc = UNBOUND;

/* SET-MALLOCED-BYTE-VECTOR-16-THRESHHOLD */
Object g2int_set_malloced_byte_vector_16_threshhold(length_1)
    Object length_1;
{
    Object rounded_up_length, pool_index;
    Object result;

    x_note_fn_call(20,74);
    if (IFIX(length_1) == (SI_Long)-1L) {
	G2int_byte_vector_16_pool_number_to_malloc = FIX((SI_Long)-1L);
	return VALUES_1(G2int_byte_vector_16_pool_number_to_malloc);
    }
    else {
	result = g2int_buffer_size_and_pool_for_partial_buffer(length_1,
		G2int_byte_vector_16_allocation_schemes);
	MVS_2(result,rounded_up_length,pool_index);
	if (FIXNUM_GT(pool_index,
		G2int_largest_non_malloced_byte_vector_16_pool_index))
	    G2int_byte_vector_16_pool_number_to_malloc = pool_index;
	return VALUES_1(rounded_up_length);
    }
}

/* FREE-MALLOCED-BYTE-VECTOR-16S */
Object free_malloced_byte_vector_16s()
{
    Object array_list, array, ab_loop_list_, svref_arg_1;
    SI_Long pool_index, ab_loop_bind_;

    x_note_fn_call(20,75);
    if (IFIX(G2int_byte_vector_16_pool_number_to_malloc) >= (SI_Long)0L) {
	pool_index = IFIX(G2int_byte_vector_16_pool_number_to_malloc);
	ab_loop_bind_ = IFIX(length(G2int_byte_vector_16_pools));
      next_loop:
	if (pool_index >= ab_loop_bind_)
	    goto end_loop;
	array_list = ISVREF(G2int_byte_vector_16_pools,pool_index);
	array = Nil;
	ab_loop_list_ = array_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	array = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	free_malloced_byte_vector_16(array);
	goto next_loop_1;
      end_loop_1:;
	g2int_reclaim_gensym_list_1(array_list);
	svref_arg_1 = G2int_byte_vector_16_pools;
	ISVREF(svref_arg_1,pool_index) = Nil;
	pool_index = pool_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

/* ALLOCATE-BYTE-VECTOR-16 */
Object g2int_allocate_byte_vector_16(required_size)
    Object required_size;
{
    Object temp, temp_1, pool_list, vector_1, temp_3, svref_new_value, bv16;
    Object incff_1_arg;
    SI_Long pool_index, rounded_up_length, temp_2, length_1;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(20,76);
    result = g2int_buffer_size_and_pool_for_partial_buffer(required_size,
	    G2int_byte_vector_16_allocation_schemes);
    MVS_2(result,temp,temp_1);
    pool_index = IFIX(temp_1);
    rounded_up_length = IFIX(temp);
    if (IFIX(G2int_byte_vector_16_pool_number_to_malloc) == (SI_Long)-1L 
	    || pool_index < IFIX(G2int_byte_vector_16_pool_number_to_malloc)) {
	temp_2 = IFIX(G2int_largest_non_malloced_byte_vector_16_pool_index);
	G2int_largest_non_malloced_byte_vector_16_pool_index = 
		FIX(MAX(temp_2,pool_index));
    }
    pool_list = ISVREF(G2int_byte_vector_16_pools,pool_index);
    if (pool_list) {
	vector_1 = M_CAR(pool_list);
	temp_3 = G2int_byte_vector_16_pools;
	svref_new_value = M_CDR(pool_list);
	ISVREF(temp_3,pool_index) = svref_new_value;
	inline_note_reclaim_cons(pool_list,Qg2int_gensym);
	temp_3 = G2int_available_gensym_conses;
	M_CDR(pool_list) = temp_3;
	G2int_available_gensym_conses = pool_list;
	bv16 = vector_1;
    }
    else {
	length_1 = rounded_up_length;
	temp_3 = FIXNUM_ADD1(G2int_allocated_byte_vector_16_vectors);
	G2int_allocated_byte_vector_16_vectors = temp_3;
	temp_3 = G2int_byte_vector_16_pool_counts;
	svref_new_value = FIXNUM_ADD1(ISVREF(temp_3,pool_index));
	ISVREF(temp_3,pool_index) = svref_new_value;
	incff_1_arg = 
		g2int_bytes_per_unsigned_byte_16_simple_array(FIX(length_1));
	temp_3 = 
		FIXNUM_ADD(G2int_bytes_in_allocated_byte_vector_16_vectors,
		incff_1_arg);
	G2int_bytes_in_allocated_byte_vector_16_vectors = temp_3;
	if (IFIX(G2int_byte_vector_16_pool_number_to_malloc) == 
		(SI_Long)-1L || pool_index < 
		IFIX(G2int_byte_vector_16_pool_number_to_malloc)) {
	    if (PUSH_AREA(Dynamic_area,0))
		bv16 = make_array(3,FIX(length_1),Kelement_type,
			list_constant_1);
	    POP_AREA(0);
	}
	else
	    bv16 = g2rtl_make_malloced_array(length_1);
    }
    inline_note_allocate_cons(bv16,Nil);
    return VALUES_1(bv16);
}

/* RETURN-BYTE-VECTOR-16-TO-POOL */
Object g2int_return_byte_vector_16_to_pool(byte_vector_16)
    Object byte_vector_16;
{
    Object svref_arg_1, svref_new_value;
    SI_Long pool_index;

    x_note_fn_call(20,77);
    pool_index = 
	    IFIX(g2int_partial_buffer_pool_index_given_length(SIMPLE_ARRAY_ANY_1_LENGTH(byte_vector_16),
	    G2int_byte_vector_16_allocation_schemes));
    svref_arg_1 = G2int_byte_vector_16_pools;
    svref_new_value = g2int_gensym_cons_1(byte_vector_16,
	    ISVREF(G2int_byte_vector_16_pools,pool_index));
    ISVREF(svref_arg_1,pool_index) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-BYTE-VECTOR-16 */
Object g2int_reclaim_byte_vector_16(byte_vector_16)
    Object byte_vector_16;
{
    Object temp;

    x_note_fn_call(20,78);
    inline_note_reclaim_cons(byte_vector_16,Nil);
    temp = G2int_free_malloced_arrays ? 
	    free_malloced_byte_vector_16(byte_vector_16) : 
	    g2int_return_byte_vector_16_to_pool(byte_vector_16);
    return VALUES_1(temp);
}

/* FREE-MALLOCED-BYTE-VECTOR-16 */
Object free_malloced_byte_vector_16(byte_vector_16)
    Object byte_vector_16;
{
    Object rounded_up_length, pool_index, temp, svref_new_value, decff_1_arg;
    Object result;

    x_note_fn_call(20,79);
    if (IFIX(G2int_byte_vector_16_pool_number_to_malloc) == (SI_Long)-1L)
	return g2int_return_byte_vector_16_to_pool(byte_vector_16);
    result = g2int_buffer_size_and_pool_for_partial_buffer(length(byte_vector_16),
	    G2int_byte_vector_16_allocation_schemes);
    MVS_2(result,rounded_up_length,pool_index);
    if (FIXNUM_LT(pool_index,G2int_byte_vector_16_pool_number_to_malloc))
	g2int_return_byte_vector_16_to_pool(byte_vector_16);
    else {
	temp = G2int_byte_vector_16_pool_counts;
	svref_new_value = FIXNUM_SUB1(ISVREF(temp,IFIX(pool_index)));
	SVREF(temp,pool_index) = svref_new_value;
	temp = FIXNUM_SUB1(G2int_allocated_byte_vector_16_vectors);
	G2int_allocated_byte_vector_16_vectors = temp;
	decff_1_arg = 
		g2int_bytes_per_unsigned_byte_16_simple_array(rounded_up_length);
	temp = 
		FIXNUM_MINUS(G2int_bytes_in_allocated_byte_vector_16_vectors,
		decff_1_arg);
	G2int_bytes_in_allocated_byte_vector_16_vectors = temp;
	g2rtl_free_malloced_array_internal(byte_vector_16);
    }
    return VALUES_1(T);
}

/* COPY-BYTE-VECTOR-16-PORTION-CAREFULLY */
Object g2int_copy_byte_vector_16_portion_carefully(source_vector_16,
	    source_elt_index_init,target_vector_16,target_elt_index_init,
	    element_count_init)
    Object source_vector_16, source_elt_index_init, target_vector_16;
    Object target_elt_index_init, element_count_init;
{
    Object ab_loop_iter_flag_;
    SI_Long source_elt_index, target_elt_index, element_count, source_index;
    SI_Long ab_loop_bind_, target_index, aref_new_value;

    x_note_fn_call(20,80);
    source_elt_index = IFIX(source_elt_index_init);
    target_elt_index = IFIX(target_elt_index_init);
    element_count = IFIX(element_count_init);
    if (EQ(source_vector_16,target_vector_16) && source_elt_index < 
	    target_elt_index) {
	source_index = source_elt_index + element_count - (SI_Long)1L;
	ab_loop_bind_ = source_elt_index;
	target_index = target_elt_index + element_count - (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if (source_index < ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    target_index = target_index - (SI_Long)1L;
	aref_new_value = UBYTE_16_ISAREF_1(source_vector_16,source_index);
	UBYTE_16_ISASET_1(target_vector_16,target_index,aref_new_value);
	ab_loop_iter_flag_ = Nil;
	source_index = source_index - (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	source_index = source_elt_index;
	ab_loop_bind_ = source_elt_index + element_count;
	target_index = target_elt_index;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (source_index >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    target_index = target_index + (SI_Long)1L;
	aref_new_value = UBYTE_16_ISAREF_1(source_vector_16,source_index);
	UBYTE_16_ISASET_1(target_vector_16,target_index,aref_new_value);
	ab_loop_iter_flag_ = Nil;
	source_index = source_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

/* PLISTP */
Object g2int_plistp(thing)
    Object thing;
{
    Object temp, p, ab_loop_list_;
    char temp_1;

    x_note_fn_call(20,81);
    if (LISTP(thing)) {
	temp = last(thing,_);
	temp_1 =  !TRUEP(CDR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !EQ(Nil,FIXNUM_EVENP(length(thing)) ? T : Nil) : 
		TRUEP(Nil)) {
	p = Nil;
	ab_loop_list_ = thing;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	p = CAR(ab_loop_list_);
	if ( !(p && SYMBOLP(p)))
	    return VALUES_1(Nil);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CAR-OR-ATOM */
Object g2int_car_or_atom(thing)
    Object thing;
{
    x_note_fn_call(20,82);
    if (CONSP(thing))
	return VALUES_1(CAR(thing));
    else
	return VALUES_1(thing);
}

/* CDR-OR-ATOM */
Object g2int_cdr_or_atom(thing)
    Object thing;
{
    x_note_fn_call(20,83);
    if (CONSP(thing))
	return VALUES_1(CDR(thing));
    else
	return VALUES_1(Nil);
}

/* ALIST-TO-PLIST */
Object g2int_alist_to_plist(alist)
    Object alist;
{
    Object l, cdr_l, result_1, cons_cell, indicator, value, temp;

    x_note_fn_call(20,84);
    l = alist;
    cdr_l = Nil;
    result_1 = l;
    cons_cell = Nil;
    indicator = Nil;
    value = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    cdr_l = M_CDR(l);
    cons_cell = M_CAR(l);
    indicator = M_CAR(cons_cell);
    value = M_CDR(cons_cell);
    M_CDR(l) = cons_cell;
    M_CDR(cons_cell) = cdr_l;
    M_FIRST(l) = indicator;
    M_SECOND(l) = value;
    l = cdr_l;
    goto next_loop;
  end_loop:
    temp = result_1;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

void utilities0_INIT()
{
    Object temp, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7;
    Object temp_8, temp_9, temp_10, temp_11, temp_12, temp_13, temp_14;
    Object temp_15, temp_16, temp_17, temp_18, temp_19, temp_20, temp_21;
    Object Qg2int_utilities0, Qg2int_bytes_in_allocated_byte_vector_16_vectors;
    Object AB_package, Qg2int_allocated_byte_vector_16_vectors;
    Object list_constant_9, Qg2int_byte_vector_16_pool_counts, list_constant_6;
    Object Qg2int_make_byte_vector_16_pools, Kfuncall, list_constant_8;
    Object Qg2int_byte_vector_16_pools, list_constant_4;
    Object Qg2int_bytes_in_allocated_byte_vectors;
    Object Qg2int_allocated_byte_vectors, list_constant_7;
    Object Qg2int_byte_vector_pool_counts, Qg2int_make_byte_vector_pools;
    Object list_constant_5, Qg2int_byte_vector_pools;
    Object Qg2int_maximum_in_place_array_size;
    Object Qg2int_maximum_managed_array_size, Qg2int_managed_array;
    Object Qg2int_simple_vector_pool_memory_usage;
    Object Qg2int_created_simple_vector_pool_vectors, list_constant_3;
    Object Qg2int_oversized_simple_vector_pool_counts, list_constant_2;
    Object Qg2int_vector_of_oversized_simple_vector_pools;
    Object Qg2int_simple_vector_pool_counts;
    Object Qg2int_allocate_initial_managed_simple_vector_pool_array;
    Object Qg2int_vector_of_simple_vector_pools;
    Object Qg2int_maximum_managed_simple_vector_size;
    Object Qg2int_gensym_cons_counter, Qg2int_available_gensym_conses_tail;
    Object Qg2int_available_gensym_conses, Qg2int_strange_cons;
    Object string_constant;

    x_note_fn_call(20,85);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("MANAGED-FLOAT-MARKER");
    if (G2int_managed_float_unique_marker == UNBOUND)
	G2int_managed_float_unique_marker = make_symbol(string_constant);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_strange_cons = STATIC_SYMBOL("STRANGE-CONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_strange_cons,G2int_strange_cons);
    if (G2int_strange_cons == UNBOUND)
	G2int_strange_cons = LIST_1(Qg2int_strange_cons);
    if (G2int_debugging_consing == UNBOUND)
	G2int_debugging_consing = Nil;
    if (G2int_cons_pool_conses_to_make_at_a_time == UNBOUND)
	G2int_cons_pool_conses_to_make_at_a_time = FIX((SI_Long)1024L);
    if (G2int_all_cons_pools == UNBOUND)
	G2int_all_cons_pools = Nil;
    Qg2int_available_gensym_conses = 
	    STATIC_SYMBOL("AVAILABLE-GENSYM-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_available_gensym_conses,
	    G2int_available_gensym_conses);
    Qg2int_utilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    g2int_record_system_variable(Qg2int_available_gensym_conses,
	    Qg2int_utilities0,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_available_gensym_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-GENSYM-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_available_gensym_conses_tail,
	    G2int_available_gensym_conses_tail);
    g2int_record_system_variable(Qg2int_available_gensym_conses_tail,
	    Qg2int_utilities0,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym_cons_counter = STATIC_SYMBOL("GENSYM-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_cons_counter,
	    G2int_gensym_cons_counter);
    g2int_record_system_variable(Qg2int_gensym_cons_counter,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_gensym,STATIC_FUNCTION(g2int_gensym,NIL,
	    TRUE,0,1));
    if (G2int_scope_conses == UNBOUND)
	G2int_scope_conses = LIST_1(LIST_1(Nil));
    Qg2int_maximum_managed_simple_vector_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-SIMPLE-VECTOR-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_managed_simple_vector_size,
	    FIX((SI_Long)1024L));
    Qg2int_vector_of_simple_vector_pools = 
	    STATIC_SYMBOL("VECTOR-OF-SIMPLE-VECTOR-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_vector_of_simple_vector_pools,
	    G2int_vector_of_simple_vector_pools);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_allocate_initial_managed_simple_vector_pool_array = 
	    STATIC_SYMBOL("ALLOCATE-INITIAL-MANAGED-SIMPLE-VECTOR-POOL-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_allocate_initial_managed_simple_vector_pool_array,
	    STATIC_FUNCTION(g2int_allocate_initial_managed_simple_vector_pool_array,
	    NIL,FALSE,1,1));
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qg2int_allocate_initial_managed_simple_vector_pool_array,Qnil);
    g2int_record_system_variable(Qg2int_vector_of_simple_vector_pools,
	    Qg2int_utilities0,list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qg2int_simple_vector_pool_counts = 
	    STATIC_SYMBOL("SIMPLE-VECTOR-POOL-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_simple_vector_pool_counts,
	    G2int_simple_vector_pool_counts);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qg2int_allocate_initial_managed_simple_vector_pool_array,
	    FIX((SI_Long)0L));
    g2int_record_system_variable(Qg2int_simple_vector_pool_counts,
	    Qg2int_utilities0,list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qg2int_vector_of_oversized_simple_vector_pools = 
	    STATIC_SYMBOL("VECTOR-OF-OVERSIZED-SIMPLE-VECTOR-POOLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_vector_of_oversized_simple_vector_pools,
	    G2int_vector_of_oversized_simple_vector_pools);
    g2int_record_system_variable(Qg2int_vector_of_oversized_simple_vector_pools,
	    Qg2int_utilities0,list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Qg2int_oversized_simple_vector_pool_counts = 
	    STATIC_SYMBOL("OVERSIZED-SIMPLE-VECTOR-POOL-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_oversized_simple_vector_pool_counts,
	    G2int_oversized_simple_vector_pool_counts);
    g2int_record_system_variable(Qg2int_oversized_simple_vector_pool_counts,
	    Qg2int_utilities0,list_constant_3,Qnil,Qnil,Qnil,Qnil);
    Qg2int_created_simple_vector_pool_vectors = 
	    STATIC_SYMBOL("CREATED-SIMPLE-VECTOR-POOL-VECTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_created_simple_vector_pool_vectors,
	    G2int_created_simple_vector_pool_vectors);
    g2int_record_system_variable(Qg2int_created_simple_vector_pool_vectors,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_simple_vector_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-VECTOR-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_simple_vector_pool_memory_usage,
	    G2int_simple_vector_pool_memory_usage);
    g2int_record_system_variable(Qg2int_simple_vector_pool_memory_usage,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    G2int_replenished_simple_vector_size_limit = FIX((SI_Long)10L);
    G2int_replenished_simple_vectors_to_make_at_a_time = FIX((SI_Long)10L);
    temp = g2int_make_partial_buffer_info(FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)0L));
    temp_1 = g2int_make_partial_buffer_info(FIX((SI_Long)32L),
	    FIX((SI_Long)4L),FIX((SI_Long)0L),FIX((SI_Long)2L));
    temp_2 = g2int_make_partial_buffer_info(FIX((SI_Long)64L),
	    FIX((SI_Long)8L),FIX((SI_Long)5L),FIX((SI_Long)3L));
    temp_3 = g2int_make_partial_buffer_info(FIX((SI_Long)128L),
	    FIX((SI_Long)16L),FIX((SI_Long)9L),FIX((SI_Long)4L));
    temp_4 = g2int_make_partial_buffer_info(FIX((SI_Long)256L),
	    FIX((SI_Long)32L),FIX((SI_Long)13L),FIX((SI_Long)5L));
    temp_5 = g2int_make_partial_buffer_info(FIX((SI_Long)512L),
	    FIX((SI_Long)64L),FIX((SI_Long)17L),FIX((SI_Long)6L));
    G2int_managed_array_allocation_schemes = list(7,temp,temp_1,temp_2,
	    temp_3,temp_4,temp_5,
	    g2int_make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)128L),FIX((SI_Long)21L),FIX((SI_Long)7L)));
    Qg2int_managed_array = STATIC_SYMBOL("MANAGED-ARRAY",AB_package);
    if (G2int_managed_array_unique_marker == UNBOUND)
	G2int_managed_array_unique_marker = CONS(Qg2int_managed_array,Nil);
    Qg2int_maximum_managed_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_maximum_managed_array_size,
	    G2int_maximum_managed_array_size);
    SET_SYMBOL_VALUE(Qg2int_maximum_managed_array_size,
	    FIX((IFIX(G2int_maximum_managed_array_buffer_size) - 
	    (SI_Long)2L) * IFIX(G2int_maximum_managed_array_buffer_size)));
    Qg2int_maximum_in_place_array_size = 
	    STATIC_SYMBOL("MAXIMUM-IN-PLACE-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_maximum_in_place_array_size,
	    G2int_maximum_in_place_array_size);
    SET_SYMBOL_VALUE(Qg2int_maximum_in_place_array_size,
	    FIX(IFIX(G2int_maximum_managed_array_buffer_size) - (SI_Long)2L));
    G2int_maximum_byte_vector_length = FIX((SI_Long)131072L);
    temp_6 = g2int_make_partial_buffer_info(FIX((SI_Long)128L),
	    FIX((SI_Long)16L),FIX((SI_Long)0L),FIX((SI_Long)4L));
    temp_7 = g2int_make_partial_buffer_info(FIX((SI_Long)256L),
	    FIX((SI_Long)32L),FIX((SI_Long)5L),FIX((SI_Long)5L));
    temp_8 = g2int_make_partial_buffer_info(FIX((SI_Long)512L),
	    FIX((SI_Long)64L),FIX((SI_Long)9L),FIX((SI_Long)6L));
    temp_9 = g2int_make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)128L),FIX((SI_Long)13L),FIX((SI_Long)7L));
    temp = g2int_make_partial_buffer_info(FIX((SI_Long)2048L),
	    FIX((SI_Long)256L),FIX((SI_Long)17L),FIX((SI_Long)8L));
    temp_1 = g2int_make_partial_buffer_info(FIX((SI_Long)4096L),
	    FIX((SI_Long)512L),FIX((SI_Long)21L),FIX((SI_Long)9L));
    temp_2 = g2int_make_partial_buffer_info(FIX((SI_Long)8192L),
	    FIX((SI_Long)1024L),FIX((SI_Long)25L),FIX((SI_Long)10L));
    temp_3 = g2int_make_partial_buffer_info(FIX((SI_Long)16384L),
	    FIX((SI_Long)2048L),FIX((SI_Long)29L),FIX((SI_Long)11L));
    temp_4 = g2int_make_partial_buffer_info(FIX((SI_Long)32768L),
	    FIX((SI_Long)4096L),FIX((SI_Long)33L),FIX((SI_Long)12L));
    temp_5 = g2int_make_partial_buffer_info(FIX((SI_Long)65536L),
	    FIX((SI_Long)8192L),FIX((SI_Long)37L),FIX((SI_Long)13L));
    G2int_byte_vector_allocation_schemes = list(11,temp_6,temp_7,temp_8,
	    temp_9,temp,temp_1,temp_2,temp_3,temp_4,temp_5,
	    g2int_make_partial_buffer_info(FIX((SI_Long)131072L),
	    FIX((SI_Long)16384L),FIX((SI_Long)41L),FIX((SI_Long)14L)));
    Qg2int_byte_vector_pools = STATIC_SYMBOL("BYTE-VECTOR-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_byte_vector_pools,
	    G2int_byte_vector_pools);
    Qg2int_make_byte_vector_pools = STATIC_SYMBOL("MAKE-BYTE-VECTOR-POOLS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_byte_vector_pools,
	    STATIC_FUNCTION(g2int_make_byte_vector_pools,NIL,FALSE,1,1));
    list_constant_4 = STATIC_CONS(Qnil,Qnil);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qg2int_make_byte_vector_pools,list_constant_4);
    g2int_record_system_variable(Qg2int_byte_vector_pools,
	    Qg2int_utilities0,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qg2int_byte_vector_pool_counts = 
	    STATIC_SYMBOL("BYTE-VECTOR-POOL-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_byte_vector_pool_counts,
	    G2int_byte_vector_pool_counts);
    list_constant_6 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qg2int_make_byte_vector_pools,list_constant_6);
    g2int_record_system_variable(Qg2int_byte_vector_pool_counts,
	    Qg2int_utilities0,list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qg2int_allocated_byte_vectors = STATIC_SYMBOL("ALLOCATED-BYTE-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_allocated_byte_vectors,
	    G2int_allocated_byte_vectors);
    g2int_record_system_variable(Qg2int_allocated_byte_vectors,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_bytes_in_allocated_byte_vectors = 
	    STATIC_SYMBOL("BYTES-IN-ALLOCATED-BYTE-VECTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_bytes_in_allocated_byte_vectors,
	    G2int_bytes_in_allocated_byte_vectors);
    g2int_record_system_variable(Qg2int_bytes_in_allocated_byte_vectors,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    G2int_maximum_byte_vector_16_length = FIX((SI_Long)268435456L);
    G2int_maximum_wide_string_length = 
	    FIXNUM_MINUS(G2int_maximum_byte_vector_16_length,
	    G2int_extra_wide_string_bv16_elements);
    temp_10 = g2int_make_partial_buffer_info(FIX((SI_Long)64L),
	    FIX((SI_Long)8L),FIX((SI_Long)0L),FIX((SI_Long)3L));
    temp_11 = g2int_make_partial_buffer_info(FIX((SI_Long)128L),
	    FIX((SI_Long)16L),FIX((SI_Long)5L),FIX((SI_Long)4L));
    temp_12 = g2int_make_partial_buffer_info(FIX((SI_Long)256L),
	    FIX((SI_Long)32L),FIX((SI_Long)9L),FIX((SI_Long)5L));
    temp_13 = g2int_make_partial_buffer_info(FIX((SI_Long)512L),
	    FIX((SI_Long)64L),FIX((SI_Long)13L),FIX((SI_Long)6L));
    temp_14 = g2int_make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)128L),FIX((SI_Long)17L),FIX((SI_Long)7L));
    temp_15 = g2int_make_partial_buffer_info(FIX((SI_Long)2048L),
	    FIX((SI_Long)256L),FIX((SI_Long)21L),FIX((SI_Long)8L));
    temp_16 = g2int_make_partial_buffer_info(FIX((SI_Long)4096L),
	    FIX((SI_Long)512L),FIX((SI_Long)25L),FIX((SI_Long)9L));
    temp_17 = g2int_make_partial_buffer_info(FIX((SI_Long)8192L),
	    FIX((SI_Long)1024L),FIX((SI_Long)29L),FIX((SI_Long)10L));
    temp_18 = g2int_make_partial_buffer_info(FIX((SI_Long)16384L),
	    FIX((SI_Long)2048L),FIX((SI_Long)33L),FIX((SI_Long)11L));
    temp_19 = g2int_make_partial_buffer_info(FIX((SI_Long)32768L),
	    FIX((SI_Long)4096L),FIX((SI_Long)37L),FIX((SI_Long)12L));
    temp_20 = g2int_make_partial_buffer_info(FIX((SI_Long)65536L),
	    FIX((SI_Long)8192L),FIX((SI_Long)41L),FIX((SI_Long)13L));
    temp_21 = g2int_make_partial_buffer_info(FIX((SI_Long)131072L),
	    FIX((SI_Long)16384L),FIX((SI_Long)45L),FIX((SI_Long)14L));
    temp_6 = g2int_make_partial_buffer_info(FIX((SI_Long)262144L),
	    FIX((SI_Long)32768L),FIX((SI_Long)49L),FIX((SI_Long)15L));
    temp_7 = g2int_make_partial_buffer_info(FIX((SI_Long)524288L),
	    FIX((SI_Long)65536L),FIX((SI_Long)53L),FIX((SI_Long)16L));
    temp_8 = g2int_make_partial_buffer_info(FIX((SI_Long)1048576L),
	    FIX((SI_Long)131072L),FIX((SI_Long)57L),FIX((SI_Long)17L));
    temp_9 = g2int_make_partial_buffer_info(FIX((SI_Long)2097152L),
	    FIX((SI_Long)262144L),FIX((SI_Long)61L),FIX((SI_Long)18L));
    temp = g2int_make_partial_buffer_info(FIX((SI_Long)4194304L),
	    FIX((SI_Long)524288L),FIX((SI_Long)65L),FIX((SI_Long)19L));
    temp_1 = g2int_make_partial_buffer_info(FIX((SI_Long)8388608L),
	    FIX((SI_Long)1048576L),FIX((SI_Long)69L),FIX((SI_Long)20L));
    temp_2 = g2int_make_partial_buffer_info(FIX((SI_Long)16777216L),
	    FIX((SI_Long)2097152L),FIX((SI_Long)73L),FIX((SI_Long)21L));
    temp_3 = g2int_make_partial_buffer_info(FIX((SI_Long)33554432L),
	    FIX((SI_Long)4194304L),FIX((SI_Long)77L),FIX((SI_Long)22L));
    temp_4 = g2int_make_partial_buffer_info(FIX((SI_Long)67108864L),
	    FIX((SI_Long)8388608L),FIX((SI_Long)81L),FIX((SI_Long)23L));
    temp_5 = g2int_make_partial_buffer_info(FIX((SI_Long)134217728L),
	    FIX((SI_Long)16777216L),FIX((SI_Long)85L),FIX((SI_Long)24L));
    G2int_byte_vector_16_allocation_schemes = list(23,temp_10,temp_11,
	    temp_12,temp_13,temp_14,temp_15,temp_16,temp_17,temp_18,
	    temp_19,temp_20,temp_21,temp_6,temp_7,temp_8,temp_9,temp,
	    temp_1,temp_2,temp_3,temp_4,temp_5,
	    g2int_make_partial_buffer_info(FIX((SI_Long)268435456L),
	    FIX((SI_Long)33554432L),FIX((SI_Long)89L),FIX((SI_Long)25L)));
    Qg2int_byte_vector_16_pools = STATIC_SYMBOL("BYTE-VECTOR-16-POOLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_byte_vector_16_pools,
	    G2int_byte_vector_16_pools);
    Qg2int_make_byte_vector_16_pools = 
	    STATIC_SYMBOL("MAKE-BYTE-VECTOR-16-POOLS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_byte_vector_16_pools,
	    STATIC_FUNCTION(g2int_make_byte_vector_16_pools,NIL,FALSE,1,1));
    list_constant_8 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qg2int_make_byte_vector_16_pools,list_constant_4);
    g2int_record_system_variable(Qg2int_byte_vector_16_pools,
	    Qg2int_utilities0,list_constant_8,Qnil,Qt,Qnil,Qnil);
    Qg2int_byte_vector_16_pool_counts = 
	    STATIC_SYMBOL("BYTE-VECTOR-16-POOL-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_byte_vector_16_pool_counts,
	    G2int_byte_vector_16_pool_counts);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qg2int_make_byte_vector_16_pools,list_constant_6);
    g2int_record_system_variable(Qg2int_byte_vector_16_pool_counts,
	    Qg2int_utilities0,list_constant_9,Qnil,Qt,Qnil,Qnil);
    Qg2int_allocated_byte_vector_16_vectors = 
	    STATIC_SYMBOL("ALLOCATED-BYTE-VECTOR-16-VECTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_allocated_byte_vector_16_vectors,
	    G2int_allocated_byte_vector_16_vectors);
    g2int_record_system_variable(Qg2int_allocated_byte_vector_16_vectors,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_bytes_in_allocated_byte_vector_16_vectors = 
	    STATIC_SYMBOL("BYTES-IN-ALLOCATED-BYTE-VECTOR-16-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_bytes_in_allocated_byte_vector_16_vectors,
	    G2int_bytes_in_allocated_byte_vector_16_vectors);
    g2int_record_system_variable(Qg2int_bytes_in_allocated_byte_vector_16_vectors,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (G2int_free_malloced_arrays == UNBOUND)
	G2int_free_malloced_arrays = T;
    if (G2int_largest_non_malloced_byte_vector_16_pool_index == UNBOUND)
	G2int_largest_non_malloced_byte_vector_16_pool_index = 
		FIX((SI_Long)-1L);
    if (G2int_byte_vector_16_pool_number_to_malloc == UNBOUND)
	G2int_byte_vector_16_pool_number_to_malloc = FIX((SI_Long)-1L);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
}
