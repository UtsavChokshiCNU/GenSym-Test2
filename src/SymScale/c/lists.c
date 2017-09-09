/* lists.c
 * Input file:  lists.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "lists.h"


static Object Qlist_structure;     /* list-structure */

/* RECLAIM-LIST-STRUCTURE-VALUE */
Object reclaim_list_structure_value(g2_list_structure_qm,g2_list)
    Object g2_list_structure_qm, g2_list;
{
    x_note_fn_call(143,0);
    if (SIMPLE_VECTOR_P(g2_list_structure_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_list_structure_qm)) == 
	    (SI_Long)6L && EQ(ISVREF(g2_list_structure_qm,(SI_Long)4L),
	    G2_list_structure_marker)) {
	if (CONSP(g2_list_structure_qm)) {
	    reclaim_slot_value_tree_1(g2_list_structure_qm);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(g2_list,Qlist_structure);
	    SVREF(g2_list,FIX((SI_Long)20L)) = Nil;
	}
	else
	    delete_g2_list(g2_list);
    }
    return VALUES_1(Nil);
}

static Object Qinsert_duplicate_elements_qm;  /* insert-duplicate-elements? */

/* PUT-INSERT-DUPLICATE-ELEMENTS? */
Object put_insert_duplicate_elements_qm(g2_list,new_value,initializing_qm)
    Object g2_list, new_value, initializing_qm;
{
    x_note_fn_call(143,1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_list,Qinsert_duplicate_elements_qm);
    SVREF(g2_list,FIX((SI_Long)22L)) = new_value;
    if ( !TRUEP(initializing_qm) &&  !TRUEP(new_value) &&  
	    !TRUEP(g2_list_empty_p(g2_list)))
	remove_g2_list_duplicate_elements(g2_list);
    return VALUES_1(new_value);
}

static Object Qlist_is_permanent;  /* list-is-permanent */

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-LIST */
Object deactivate_subclass_of_entity_for_g2_list(g2_list)
    Object g2_list;
{
    x_note_fn_call(143,2);
    if (ISVREF(g2_list,(SI_Long)20L) &&  !TRUEP(Warmbooting_qm) &&  
	    !TRUEP(get_lookup_slot_value(g2_list,Qlist_is_permanent)))
	return delete_g2_list(g2_list);
    else
	return VALUES_1(Nil);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-LIST */
Object activate_subclass_of_entity_for_g2_list(g2_list)
    Object g2_list;
{
    Object svref_new_value;

    x_note_fn_call(143,3);
    if ( !TRUEP(ISVREF(g2_list,(SI_Long)20L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(g2_list,Qlist_structure);
	svref_new_value = create_empty_g2_list_structure();
	return VALUES_1(SVREF(g2_list,FIX((SI_Long)20L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

static Object Qquantity;           /* quantity */

static Object Qlist_type;          /* list-type */

/* PUT-LIST-TYPE */
Object put_list_type(g2_list,new_value,initializing_qm)
    Object g2_list, new_value, initializing_qm;
{
    x_note_fn_call(143,4);
    if (EQ(new_value,Qquantity))
	new_value = Qnumber;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_list,Qlist_type);
    SVREF(g2_list,FIX((SI_Long)21L)) = new_value;
    if ( !TRUEP(initializing_qm) &&  !TRUEP(g2_list_empty_p(g2_list)))
	validate_and_fix_g2_item_list_elements(g2_list);
    return VALUES_1(new_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_g2_list_conses, Qavailable_g2_list_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_g2_list_conses_tail, Qavailable_g2_list_conses_tail);

Object Available_g2_list_conses_vector = UNBOUND;

Object Available_g2_list_conses_tail_vector = UNBOUND;

Object G2_list_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(G2_list_cons_counter, Qg2_list_cons_counter);

/* OUTSTANDING-G2-LIST-CONSES */
Object outstanding_g2_list_conses()
{
    Object temp;

    x_note_fn_call(143,5);
    temp = FIXNUM_MINUS(G2_list_cons_counter,length(Available_g2_list_conses));
    return VALUES_1(temp);
}

/* G2-LIST-CONS-MEMORY-USAGE */
Object g2_list_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(143,6);
    temp = FIXNUM_TIMES(G2_list_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-G2-LIST-CONS-POOL */
Object replenish_g2_list_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(143,7);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qg2_list_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_g2_list_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_g2_list_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_g2_list_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = G2_list_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qg2_list;            /* g2-list */

/* G2-LIST-CONS-1 */
Object g2_list_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(143,8);
    new_cons = ISVREF(Available_g2_list_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_g2_list_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_g2_list_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_g2_list_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qg2_list);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-G2-LIST-LIST-POOL */
Object replenish_g2_list_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(143,9);
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
    if (ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_g2_list_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_g2_list_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_g2_list_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qg2_list_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-G2-LIST-LIST-1 */
Object make_g2_list_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(143,10);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_g2_list_conses_vector,
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
	replenish_g2_list_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_g2_list_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qg2_list);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_g2_list_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_g2_list_conses_tail_vector;
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

/* G2-LIST-LIST-2 */
Object g2_list_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(143,11);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_g2_list_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qg2_list);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_g2_list_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_g2_list_conses_tail_vector;
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

/* G2-LIST-LIST-3 */
Object g2_list_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(143,12);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_g2_list_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qg2_list);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_g2_list_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_g2_list_conses_tail_vector;
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

/* G2-LIST-LIST-4 */
Object g2_list_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(143,13);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_g2_list_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qg2_list);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_g2_list_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_g2_list_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_g2_list_conses_tail_vector;
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

/* G2-LIST-LIST-TRACE-HOOK */
Object g2_list_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(143,14);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-G2-LIST-CONSES-1 */
Object copy_tree_using_g2_list_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(143,15);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_g2_list_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_g2_list_cons_pool();
	temp_1 = copy_tree_using_g2_list_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2_list);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_g2_list_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_g2_list_cons_pool();
	temp_1 = copy_tree_using_g2_list_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2_list);
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

/* COPY-LIST-USING-G2-LIST-CONSES-1 */
Object copy_list_using_g2_list_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(143,16);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_g2_list_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_g2_list_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2_list);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_g2_list_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_g2_list_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_g2_list_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_g2_list_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qg2_list);
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

/* RECLAIM-G2-LIST-CONS-1 */
Object reclaim_g2_list_cons_1(g2_list_cons)
    Object g2_list_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(143,17);
    inline_note_reclaim_cons(g2_list_cons,Qg2_list);
    if (ISVREF(Available_g2_list_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_g2_list_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = g2_list_cons;
	temp = Available_g2_list_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = g2_list_cons;
    }
    else {
	temp = Available_g2_list_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = g2_list_cons;
	temp = Available_g2_list_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = g2_list_cons;
    }
    M_CDR(g2_list_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-G2-LIST-LIST-1 */
Object reclaim_g2_list_list_1(g2_list_list)
    Object g2_list_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(143,18);
    if (g2_list_list) {
	last_1 = g2_list_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qg2_list);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qg2_list);
	if (ISVREF(Available_g2_list_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_g2_list_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = g2_list_list;
	    temp = Available_g2_list_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_g2_list_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = g2_list_list;
	    temp = Available_g2_list_conses_tail_vector;
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

/* RECLAIM-G2-LIST-LIST*-1 */
Object reclaim_g2_list_list_star_1(g2_list_list)
    Object g2_list_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(143,19);
    if (CONSP(g2_list_list)) {
	temp = last(g2_list_list,_);
	M_CDR(temp) = Nil;
	if (g2_list_list) {
	    last_1 = g2_list_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qg2_list);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qg2_list);
	    if (ISVREF(Available_g2_list_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_g2_list_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = g2_list_list;
		temp = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_g2_list_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = g2_list_list;
		temp = Available_g2_list_conses_tail_vector;
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

/* RECLAIM-G2-LIST-TREE-1 */
Object reclaim_g2_list_tree_1(tree)
    Object tree;
{
    Object e, e2, g2_list_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(143,20);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_g2_list_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		g2_list_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(g2_list_cons,Qg2_list);
		if (EQ(g2_list_cons,e))
		    goto end_1;
		else if ( !TRUEP(g2_list_cons))
		    goto end_1;
		else
		    g2_list_cons = CDR(g2_list_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_g2_list_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_g2_list_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_g2_list_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_g2_list_conses_tail_vector;
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

/* DELETE-G2-LIST-ELEMENT-1 */
Object delete_g2_list_element_1(element,g2_list_list)
    Object element, g2_list_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(143,21);
    if (g2_list_list) {
	if (EQ(element,M_CAR(g2_list_list))) {
	    temp = CDR(g2_list_list);
	    inline_note_reclaim_cons(g2_list_list,Qg2_list);
	    if (ISVREF(Available_g2_list_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_g2_list_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = g2_list_list;
		temp_1 = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = g2_list_list;
	    }
	    else {
		temp_1 = Available_g2_list_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = g2_list_list;
		temp_1 = Available_g2_list_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = g2_list_list;
	    }
	    M_CDR(g2_list_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = g2_list_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qg2_list);
		if (ISVREF(Available_g2_list_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_g2_list_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_g2_list_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_g2_list_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_g2_list_conses_tail_vector;
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
	    temp = g2_list_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-G2-LIST-CONS-1 */
Object delete_g2_list_cons_1(g2_list_cons,g2_list_list)
    Object g2_list_cons, g2_list_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(143,22);
    if (EQ(g2_list_cons,g2_list_list))
	temp = CDR(g2_list_list);
    else {
	l_trailer_qm = Nil;
	l = g2_list_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,g2_list_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = g2_list_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_g2_list_cons_1(g2_list_cons);
    return VALUES_1(temp);
}

/* ADD-TO-LIST-ELEMENTS-FOR-ITEM */
Object add_to_list_elements_for_item(item,g2_list_element_structure)
    Object item, g2_list_element_structure;
{
    Object new_value, old_value, temp;

    x_note_fn_call(143,23);
    new_value = g2_list_cons_1(g2_list_element_structure,Nil);
    old_value = Nil;
  next_loop:
    old_value = ISVREF(item,(SI_Long)13L);
    M_CDR(new_value) = old_value;
    if (CAS_SVREF(item,(SI_Long)13L,old_value,new_value))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp = new_value;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* DELETE-FROM-LIST-ELEMENTS-FOR-ITEM */
Object delete_from_list_elements_for_item varargs_1(int, n)
{
    Object item, g2_list_element_structure;
    Object remove_all_element_instances_qm, element_list;
    Object first_element_deleted_qm, old_value, new_value, temp, svref_arg_2;
    Object element_sub_list, element, reclaim_cons;
    Declare_varargs_nonrelocating;

    x_note_fn_call(143,24);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    g2_list_element_structure = REQUIRED_ARG_nonrelocating();
    remove_all_element_instances_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    element_list = ISVREF(item,(SI_Long)13L);
    first_element_deleted_qm = Nil;
    if (element_list) {
	if (EQ(FIRST(element_list),g2_list_element_structure)) {
	    old_value = Nil;
	    new_value = Nil;
	  next_loop:
	    old_value = ISVREF(item,(SI_Long)13L);
	    if ( !TRUEP(old_value))
		goto end_loop;
	    new_value = M_CDR(old_value);
	    if (CAS_SVREF(item,(SI_Long)13L,old_value,new_value))
		goto end_loop;
	    goto next_loop;
	  end_loop:
	    if (old_value) {
		inline_note_reclaim_cons(old_value,Qg2_list);
		if (ISVREF(Available_g2_list_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_g2_list_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = old_value;
		    temp = Available_g2_list_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = old_value;
		}
		else {
		    temp = Available_g2_list_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = old_value;
		    temp = Available_g2_list_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = old_value;
		}
		M_CDR(old_value) = Nil;
	    }
	    goto end_1;
	  end_1:;
	    first_element_deleted_qm = T;
	}
	if (remove_all_element_instances_qm ||  
		!TRUEP(first_element_deleted_qm)) {
	    element_sub_list = element_list;
	    element = Nil;
	  next_loop_1:
	    if ( !TRUEP(element_sub_list))
		goto end_loop_1;
	    element = SECOND(element_sub_list);
	    if ( !TRUEP(CDR(element_sub_list)))
		goto end_loop_1;
	    if (EQ(element,g2_list_element_structure)) {
		reclaim_cons = CDR(element_sub_list);
		temp = CDDR(element_sub_list);
		M_CDR(element_sub_list) = temp;
		reclaim_g2_list_cons_1(reclaim_cons);
		if ( !TRUEP(remove_all_element_instances_qm))
		    goto end_2;
	    }
	    element_sub_list = M_CDR(element_sub_list);
	    goto next_loop_1;
	  end_loop_1:
	  end_2:;
	}
    }
    return VALUES_1(ISVREF(item,(SI_Long)13L));
}

/* G2-LIST-EMPTY-P */
Object g2_list_empty_p(g2_list)
    Object g2_list;
{
    Object g2_list_structure_qm, temp;

    x_note_fn_call(143,25);
    g2_list_structure_qm = ISVREF(g2_list,(SI_Long)20L);
    temp =  !TRUEP(g2_list_structure_qm) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(g2_list_structure_next(ISVREF(g2_list_structure_qm,
		(SI_Long)2L),g2_list_structure_qm)) ? T : Nil;
    return VALUES_1(temp);
}

/* G2-LIST-LENGTH */
Object g2_list_length(g2_list)
    Object g2_list;
{
    Object g2_list_structure, list_1, next_list_element, element, temp;
    SI_Long ab_loopvar_;

    x_note_fn_call(143,26);
    if ((SI_Long)0L != (IFIX(ISVREF(g2_list,(SI_Long)5L)) & (SI_Long)1L)) {
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	list_1 = g2_list_structure;
	next_list_element = Nil;
	element = Nil;
	ab_loopvar_ = (SI_Long)0L;
	next_list_element = g2_list_structure_next(ISVREF(list_1,
		(SI_Long)2L),list_1);
      next_loop:
	if ( !TRUEP(next_list_element))
	    goto end_loop;
	element = next_list_element;
	next_list_element = g2_list_structure_next(next_list_element,list_1);
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = FIX(ab_loopvar_);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = FIX((SI_Long)0L);
    return VALUES_1(temp);
}

/* G2-LIST-MEMBER-P */
Object g2_list_member_p(item_or_evaluation_value,g2_list)
    Object item_or_evaluation_value, g2_list;
{
    Object temp;

    x_note_fn_call(143,27);
    temp =  ! !(INLINE_DOUBLE_FLOAT_VECTOR_P(item_or_evaluation_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) == 
	    (SI_Long)1L && 
	    exceptional_float_p(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(item_or_evaluation_value,
	    (SI_Long)0L))) ? 
	    TRUEP(find_exceptional_float_in_g2_list(item_or_evaluation_value,
	    g2_list)) : 
	    TRUEP(find_g2_list_element_structure(item_or_evaluation_value,
	    g2_list,Nil,T))) ? T : Nil;
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qlist_size;          /* list-size */

/* CLEAR-G2-LIST */
Object clear_g2_list(g2_list)
    Object g2_list;
{
    Object g2_list_structure, initialized_g2_list_cleared_qm;
    Object open_continuations, continuation, ab_loop_list_, list_1;
    Object next_list_element, element_structure, item_or_value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, x2, item_list, item, first_cons;
    Object last_cons, current_cons, next_cons;
    char temp;

    x_note_fn_call(143,28);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(g2_list);
    g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
    initialized_g2_list_cleared_qm = Nil;
    open_continuations = ISVREF(g2_list,(SI_Long)23L);
    if (open_continuations) {
	continuation = Nil;
	ab_loop_list_ = open_continuations;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	continuation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	M_SECOND(continuation) = Nil;
	goto next_loop;
      end_loop:;
	reclaim_eval_list_function(open_continuations);
	ISVREF(g2_list,(SI_Long)23L) = Nil;
    }
    if (g2_list_structure) {
	list_1 = g2_list_structure;
	next_list_element = Nil;
	element_structure = Nil;
	item_or_value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	next_list_element = g2_list_structure_next(ISVREF(list_1,
		(SI_Long)2L),list_1);
      next_loop_1:
	if ( !TRUEP(next_list_element))
	    goto end_loop_1;
	element_structure = next_list_element;
	next_list_element = g2_list_structure_next(next_list_element,list_1);
	item_or_value = ISVREF(element_structure,(SI_Long)4L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    SVREF(element_structure,FIX((SI_Long)4L)) = Nil;
	    ab_loopvar__2 = g2_list_cons_1(item_or_value,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_1;
      end_loop_1:
	item_list = ab_loopvar_;
	goto end_1;
	item_list = Qnil;
      end_1:;
	item = Nil;
	ab_loop_list_ = item_list;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	first_cons = Nil;
	last_cons = Nil;
	current_cons = ISVREF(item,(SI_Long)13L);
	element_structure = Nil;
	next_cons = Nil;
      next_loop_3:
	if ( !TRUEP(current_cons))
	    goto end_loop_3;
	element_structure = CAR(current_cons);
	next_cons = CDR(current_cons);
	if (ISVREF(element_structure,(SI_Long)4L)) {
	    last_cons = current_cons;
	    if ( !TRUEP(first_cons))
		first_cons = current_cons;
	}
	else {
	    if (last_cons)
		M_CDR(last_cons) = next_cons;
	    else
		first_cons = next_cons;
	    reclaim_g2_list_cons_1(current_cons);
	}
	current_cons = next_cons;
	goto next_loop_3;
      end_loop_3:
	ISVREF(item,(SI_Long)13L) = first_cons;
	goto next_loop_2;
      end_loop_2:;
	reclaim_g2_list_list_1(item_list);
	g2_list_structure_clear(g2_list_structure);
	initialized_g2_list_cleared_qm = T;
    }
    ISVREF(g2_list,(SI_Long)24L) = FIX((SI_Long)0L);
    update_representations_of_slot_value(2,g2_list,Qlist_size);
    return VALUES_1(initialized_g2_list_cleared_qm);
}

/* DELETE-G2-LIST */
Object delete_g2_list(g2_list)
    Object g2_list;
{
    Object g2_list_element, temp, svref_arg_2, temp_1;

    x_note_fn_call(143,29);
    if (clear_g2_list(g2_list)) {
	g2_list_element = ISVREF(g2_list,(SI_Long)20L);
	inline_note_reclaim_cons(g2_list_element,Nil);
	temp = ISVREF(Chain_of_available_g2_list_elements_vector,
		IFIX(Current_thread_index));
	SVREF(g2_list_element,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_g2_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = g2_list_element;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(g2_list,Qlist_structure);
	SVREF(g2_list,FIX((SI_Long)20L)) = Nil;
	ISVREF(g2_list,(SI_Long)24L) = FIX((SI_Long)0L);
	temp_1 = update_representations_of_slot_value(2,g2_list,Qlist_size);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* FIND-G2-LIST-ELEMENT-STRUCTURE */
Object find_g2_list_element_structure(item_or_evaluation_value,g2_list,
	    search_begins_at_element_structure_qm,
	    item_search_memq_test_returns_any_position_qm)
    Object item_or_evaluation_value, g2_list;
    Object search_begins_at_element_structure_qm;
    Object item_search_memq_test_returns_any_position_qm;
{
    Object search_g2_list_qm, element_qm, x2, first_element_location_qm;
    Object element_structure, ab_loop_list_, temp_1, g2_list_structure;
    Object element_value;
    char temp;

    x_note_fn_call(143,30);
    search_g2_list_qm = T;
    element_qm = Nil;
    if (g2_list_empty_p(g2_list))
	search_g2_list_qm = Nil;
    else {
	temp = TRUEP(search_begins_at_element_structure_qm);
	if (temp);
	else {
	    if (SIMPLE_VECTOR_P(item_or_evaluation_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(item_or_evaluation_value,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_evaluation_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	}
	if (temp);
	else {
	    first_element_location_qm = Nil;
	    element_structure = Nil;
	    ab_loop_list_ = ISVREF(item_or_evaluation_value,(SI_Long)13L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    element_structure = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (element_qm ||  !TRUEP(search_g2_list_qm))
		goto end_loop;
	    if (EQ(ISVREF(element_structure,(SI_Long)5L),g2_list)) {
		if ( !TRUEP(first_element_location_qm)) {
		    first_element_location_qm = element_structure;
		    if (item_search_memq_test_returns_any_position_qm) {
			element_qm = first_element_location_qm;
			search_g2_list_qm = Nil;
		    }
		}
		else {
		    search_g2_list_qm = T;
		    goto end_1;
		}
	    }
	    goto next_loop;
	  end_loop:
	    element_qm = first_element_location_qm;
	    search_g2_list_qm = Nil;
	  end_1:;
	}
    }
    if ( !TRUEP(search_g2_list_qm))
	temp_1 = element_qm;
    else {
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	if (g2_list_structure) {
	    element_structure = search_begins_at_element_structure_qm;
	    if (element_structure);
	    else
		element_structure = 
			g2_list_structure_next(ISVREF(g2_list_structure,
			(SI_Long)2L),g2_list_structure);
	    element_value = Nil;
	  next_loop_1:
	    if ( !TRUEP(element_structure) || element_qm)
		goto end_loop_1;
	    element_value = ISVREF(element_structure,(SI_Long)4L);
	    if (SIMPLE_VECTOR_P(element_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(element_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(element_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (EQ(item_or_evaluation_value,element_value))
		    element_qm = element_structure;
	    }
	    else if (evaluation_value_eq(item_or_evaluation_value,
		    element_value))
		element_qm = element_structure;
	    element_structure = g2_list_structure_next(element_structure,
		    g2_list_structure);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = element_qm;
	    goto end_2;
	    temp_1 = Qnil;
	  end_2:;
	}
	else
	    temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

static Object string_constant;     /* "The position given for a list is ~a, but it must be an integer." */

/* FIND-G2-LIST-ELEMENT-STRUCTURE-AT-POSITION */
Object find_g2_list_element_structure_at_position(g2_list,position_1)
    Object g2_list, position_1;
{
    Object g2_list_structure, element_qm, top_of_stack, message_1, list_1;
    Object next_list_element, element_structure, ab_loop_iter_flag_;
    SI_Long index_1;

    x_note_fn_call(143,31);
    g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
    element_qm = Nil;
    if ( !FIXNUMP(position_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant,
		position_1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (g2_list_structure && FIXNUM_GT(g2_list_length(g2_list),position_1)) {
	list_1 = g2_list_structure;
	next_list_element = Nil;
	element_structure = Nil;
	index_1 = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
	next_list_element = g2_list_structure_next(ISVREF(list_1,
		(SI_Long)2L),list_1);
      next_loop:
	if ( !TRUEP(next_list_element))
	    goto end_loop;
	element_structure = next_list_element;
	next_list_element = g2_list_structure_next(next_list_element,list_1);
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 + (SI_Long)1L;
	if (index_1 > IFIX(position_1))
	    goto end_loop;
	if (element_qm)
	    goto end_loop;
	if (index_1 == IFIX(position_1))
	    element_qm = element_structure;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(element_qm);
}

/* FIND-EXCEPTIONAL-FLOAT-IN-G2-LIST */
Object find_exceptional_float_in_g2_list(evaluation_float,g2_list)
    Object evaluation_float, g2_list;
{
    Object search_g2_list_qm, element_qm, exceptional_float_byte_1;
    Object exceptional_float_byte_2, exceptional_float_byte_3;
    Object exceptional_float_byte_4, temp, g2_list_structure, list_1;
    Object next_list_element, element_structure, element_value, float_value;
    Object test_float_byte_1, test_float_byte_2, test_float_byte_3;
    Object test_float_byte_4;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(143,32);
    search_g2_list_qm = T;
    element_qm = Nil;
    exceptional_float_byte_1 = Nil;
    exceptional_float_byte_2 = Nil;
    exceptional_float_byte_3 = Nil;
    exceptional_float_byte_4 = Nil;
    if (g2_list_empty_p(g2_list)) {
	search_g2_list_qm = Nil;
	temp = search_g2_list_qm;
    }
    else if ( !(INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_float) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_float)) == 
	    (SI_Long)1L && 
	    exceptional_float_p(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_float,
	    (SI_Long)0L))))) {
	search_g2_list_qm = Nil;
	temp = search_g2_list_qm;
    }
    else {
	g2ext_foreign_partition_float(DFLOAT_ISAREF_1(evaluation_float,
		(SI_Long)0L),
		UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	MVS_4(result,exceptional_float_byte_1,exceptional_float_byte_2,
		exceptional_float_byte_3,exceptional_float_byte_4);
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	if (g2_list_structure) {
	    list_1 = g2_list_structure;
	    next_list_element = Nil;
	    element_structure = Nil;
	    element_value = Nil;
	    float_value = Nil;
	    next_list_element = g2_list_structure_next(ISVREF(list_1,
		    (SI_Long)2L),list_1);
	  next_loop:
	    if ( !TRUEP(next_list_element))
		goto end_loop;
	    element_structure = next_list_element;
	    next_list_element = g2_list_structure_next(next_list_element,
		    list_1);
	    element_value = ISVREF(element_structure,(SI_Long)4L);
	    if (element_qm)
		goto end_loop;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(element_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_value)) == 
		    (SI_Long)1L) {
		float_value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(element_value,
			(SI_Long)0L));
		if (exceptional_float_p(float_value)) {
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_value);
		    g2ext_foreign_partition_float(temp_1,
			    UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
		    b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
		    b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
		    b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
		    b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
		    result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
		    MVS_4(result,test_float_byte_1,test_float_byte_2,
			    test_float_byte_3,test_float_byte_4);
		    if (FIXNUM_EQ(exceptional_float_byte_1,
			    test_float_byte_1) && 
			    FIXNUM_EQ(exceptional_float_byte_2,
			    test_float_byte_2) && 
			    FIXNUM_EQ(exceptional_float_byte_3,
			    test_float_byte_3) && 
			    FIXNUM_EQ(exceptional_float_byte_4,
			    test_float_byte_4))
			element_qm = element_structure;
		}
	    }
	    goto next_loop;
	  end_loop:
	    temp = element_qm;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* G2-LIST-OR-ARRAY-ELEMENT-OK-P */
Object g2_list_or_array_element_ok_p(item_or_evaluation_value,
	    g2_list_or_array_element_type_1)
    Object item_or_evaluation_value, g2_list_or_array_element_type_1;
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(143,33);
    if (SIMPLE_VECTOR_P(item_or_evaluation_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item_or_evaluation_value,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_evaluation_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? 
	    item_ok_for_g2_list_or_array_p(item_or_evaluation_value,
	    g2_list_or_array_element_type_1) : 
	    datum_ok_for_g2_list_or_array_p(item_or_evaluation_value,
	    g2_list_or_array_element_type_1);
    return VALUES_1(temp_1);
}

static Object Qitem_or_datum;      /* item-or-datum */

/* ITEM-OK-FOR-G2-LIST-OR-ARRAY-P */
Object item_ok_for_g2_list_or_array_p(item,g2_list_or_array_element_type_1)
    Object item, g2_list_or_array_element_type_1;
{
    Object element_type, temp, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(143,34);
    element_type = 
	    type_specification_for_user_or_datum_type(g2_list_or_array_element_type_1);
    if (element_type);
    else
	element_type = g2_list_or_array_element_type_1;
    if (EQ(element_type,Qitem_or_datum))
	temp = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)16L);
    else if (CONSP(g2_list_or_array_element_type_1))
	temp = Nil;
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(g2_list_or_array_element_type_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
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
		temp = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qdatum;              /* datum */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

/* DATUM-OK-FOR-G2-LIST-OR-ARRAY-P */
Object datum_ok_for_g2_list_or_array_p(evaluation_value,
	    g2_list_or_array_element_type_1)
    Object evaluation_value, g2_list_or_array_element_type_1;
{
    Object datum_element_type_specification_qm, gensymed_symbol, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(143,35);
    datum_element_type_specification_qm = 
	    type_specification_for_user_or_datum_type(g2_list_or_array_element_type_1);
    if (EQ(datum_element_type_specification_qm,Qitem_or_datum))
	datum_element_type_specification_qm = Qdatum;
    if (datum_element_type_specification_qm) {
	gensymed_symbol = evaluation_value;
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
    temp_2 = temp ? evaluation_value_of_type_p(evaluation_value,
	    datum_element_type_specification_qm) : Nil;
    return VALUES_1(temp_2);
}

static Object Qtext;               /* text */

/* G2-LIST-OR-ARRAY-ELEMENT-TYPE */
Object g2_list_or_array_element_type(g2_list_or_array)
    Object g2_list_or_array;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(143,36);
    gensymed_symbol = ISVREF(g2_list_or_array,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Integer_list_class_description,
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
    if (temp)
	temp_1 = Qinteger;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_list_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	if (temp)
	    temp_1 = Qfloat;
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Quantity_list_class_description,(SI_Long)18L));
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
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
	    if (temp)
		temp_1 = Qnumber;
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_list_class_description,(SI_Long)18L));
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
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Text_array_class_description,
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
		if (temp)
		    temp_1 = Qtext;
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Truth_value_list_class_description,
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
		    if (temp);
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Truth_value_array_class_description,
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
		    if (temp)
			temp_1 = Qtruth_value;
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Symbol_list_class_description,
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
			if (temp);
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Symbol_array_class_description,
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
			if (temp)
			    temp_1 = Qsymbol;
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Item_list_class_description,
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
			    if (temp);
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Item_array_class_description,
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
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    if (temp)
				temp_1 = Type_specification_for_item;
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Value_list_class_description,
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
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
				if (temp);
				else {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(Value_array_class_description,
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
					temp = (SI_Long)0L < gensymed_symbol_1;
				    }
				    else
					temp = TRUEP(Nil);
				}
				if (temp)
				    temp_1 = Qdatum;
				else {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(G2_list_class_description,
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
					temp = (SI_Long)0L < gensymed_symbol_1;
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp);
				    else {
					sub_class_bit_vector = 
						ISVREF(gensymed_symbol,
						(SI_Long)19L);
					superior_class_bit_number = 
						IFIX(ISVREF(G2_array_class_description,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
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
					    temp = (SI_Long)0L < 
						    gensymed_symbol_1;
					}
					else
					    temp = TRUEP(Nil);
				    }
				    if (temp)
					temp_1 = Qitem_or_datum;
				    else
					temp_1 = Nil;
				}
			    }
			}
		    }
		}
	    }
	}
    }
    return VALUES_1(temp_1);
}

static Object Qinteger_list;       /* integer-list */

static Object Qinteger_array;      /* integer-array */

static Object Qfloat_list;         /* float-list */

static Object Qfloat_array;        /* float-array */

static Object Qquantity_list;      /* quantity-list */

static Object Qquantity_array;     /* quantity-array */

static Object Qtext_list;          /* text-list */

static Object Qtext_array;         /* text-array */

static Object Qtruth_value_list;   /* truth-value-list */

static Object Qtruth_value_array;  /* truth-value-array */

static Object Qsymbol_list;        /* symbol-list */

static Object Qsymbol_array;       /* symbol-array */

static Object Qitem_list;          /* item-list */

static Object Qitem_array;         /* item-array */

static Object list_constant;       /* # */

static Object Qvalue_list;         /* value-list */

static Object Qvalue_array;        /* value-array */

static Object Qg2_array;           /* g2-array */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* G2-LIST-OR-ARRAY-CLASS-ELEMENT-TYPE */
Object g2_list_or_array_class_element_type(class_name,system_class_only_p_qm)
    Object class_name, system_class_only_p_qm;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(143,37);
    if (system_class_only_p_qm) {
	if (EQ(class_name,Qinteger_list) || EQ(class_name,Qinteger_array))
	    temp = Qinteger;
	else if (EQ(class_name,Qfloat_list) || EQ(class_name,Qfloat_array))
	    temp = Qfloat;
	else if (EQ(class_name,Qquantity_list) || EQ(class_name,
		Qquantity_array))
	    temp = Qnumber;
	else if (EQ(class_name,Qtext_list) || EQ(class_name,Qtext_array))
	    temp = Qtext;
	else if (EQ(class_name,Qtruth_value_list) || EQ(class_name,
		Qtruth_value_array))
	    temp = Qtruth_value;
	else if (EQ(class_name,Qsymbol_list) || EQ(class_name,Qsymbol_array))
	    temp = Qsymbol;
	else if (EQ(class_name,Qitem_list) || EQ(class_name,Qitem_array))
	    temp = list_constant;
	else if (EQ(class_name,Qvalue_list) || EQ(class_name,Qvalue_array))
	    temp = Qdatum;
	else if (EQ(class_name,Qg2_list) || EQ(class_name,Qg2_array))
	    temp = Qitem_or_datum;
	else
	    temp = Nil;
    }
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
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
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_list_class_description,(SI_Long)18L));
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
	if (temp_2);
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
	  next_loop_12:
	    if (level < ab_loop_bind_)
		goto end_loop_12;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_13:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_14:
	    if ( !TRUEP(marked))
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_14;
	  end_loop_13:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	  next_loop_15:
	    if (level < ab_loop_bind_)
		goto end_loop_15;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_16:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_17:
	    if ( !TRUEP(marked))
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_17;
	  end_loop_16:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_19:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_20;
	      end_loop_19:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_22:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_23;
	      end_loop_22:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
	}
	if (temp_2)
	    temp = Qinteger;
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
	  next_loop_24:
	    if (level < ab_loop_bind_)
		goto end_loop_24;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_25:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_26:
	    if ( !TRUEP(marked))
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
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
	  next_loop_27:
	    if (level < ab_loop_bind_)
		goto end_loop_27;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_28:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_29:
	    if ( !TRUEP(marked))
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_32:
		if ( !TRUEP(marked))
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_35:
		if ( !TRUEP(marked))
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_list_class_description,
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
	    if (temp_2);
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
	      next_loop_36:
		if (level < ab_loop_bind_)
		    goto end_loop_36;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_37:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_38:
		if ( !TRUEP(marked))
		    goto end_loop_37;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_38;
	      end_loop_37:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	      next_loop_39:
		if (level < ab_loop_bind_)
		    goto end_loop_39;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_40:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_41:
		if ( !TRUEP(marked))
		    goto end_loop_40;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_41;
	      end_loop_40:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_43:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_44:
		    if ( !TRUEP(marked))
			goto end_loop_43;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_44;
		  end_loop_43:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  next_loop_45:
		    if (level < ab_loop_bind_)
			goto end_loop_45;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_46:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_47:
		    if ( !TRUEP(marked))
			goto end_loop_46;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_47;
		  end_loop_46:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    IFIX(ISVREF(Float_array_class_description,
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
	    if (temp_2)
		temp = Qfloat;
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
	      next_loop_48:
		if (level < ab_loop_bind_)
		    goto end_loop_48;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_49:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_50:
		if ( !TRUEP(marked))
		    goto end_loop_49;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_50;
	      end_loop_49:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	      next_loop_51:
		if (level < ab_loop_bind_)
		    goto end_loop_51;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_52:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_53:
		if ( !TRUEP(marked))
		    goto end_loop_52;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_53;
	      end_loop_52:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_55:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_56:
		    if ( !TRUEP(marked))
			goto end_loop_55;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_56;
		  end_loop_55:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  next_loop_57:
		    if (level < ab_loop_bind_)
			goto end_loop_57;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_58:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_59:
		    if ( !TRUEP(marked))
			goto end_loop_58;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_59;
		  end_loop_58:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    IFIX(ISVREF(Quantity_list_class_description,
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
		if (temp_2);
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
		  next_loop_60:
		    if (level < ab_loop_bind_)
			goto end_loop_60;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_61:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_62:
		    if ( !TRUEP(marked))
			goto end_loop_61;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_62;
		  end_loop_61:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_21;
		    goto next_loop_61;
		  end_loop_62:
		  end_21:
		    level = level - (SI_Long)1L;
		    goto next_loop_60;
		  end_loop_60:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
				gensymed_symbol,temp,gensymed_symbol_1);
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
		  next_loop_63:
		    if (level < ab_loop_bind_)
			goto end_loop_63;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_64:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_65:
		    if ( !TRUEP(marked))
			goto end_loop_64;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_65;
		  end_loop_64:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_22;
		    goto next_loop_64;
		  end_loop_65:
		  end_22:
		    level = level - (SI_Long)1L;
		    goto next_loop_63;
		  end_loop_63:;
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
		      next_loop_66:
			if (level < ab_loop_bind_)
			    goto end_loop_66;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_67:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_68:
			if ( !TRUEP(marked))
			    goto end_loop_67;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_68;
		      end_loop_67:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_23;
			goto next_loop_67;
		      end_loop_68:
		      end_23:
			level = level - (SI_Long)1L;
			goto next_loop_66;
		      end_loop_66:;
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
		      next_loop_69:
			if (level < ab_loop_bind_)
			    goto end_loop_69;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_70:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_71:
			if ( !TRUEP(marked))
			    goto end_loop_70;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_71;
		      end_loop_70:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_24;
			goto next_loop_70;
		      end_loop_71:
		      end_24:
			level = level - (SI_Long)1L;
			goto next_loop_69;
		      end_loop_69:;
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
				IFIX(ISVREF(Quantity_array_class_description,
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
			    temp_2 = (SI_Long)0L < gensymed_symbol_3;
			}
			else
			    temp_2 = TRUEP(Nil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
		if (temp_2)
		    temp = Qnumber;
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
		  next_loop_72:
		    if (level < ab_loop_bind_)
			goto end_loop_72;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_73:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_74:
		    if ( !TRUEP(marked))
			goto end_loop_73;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_74;
		  end_loop_73:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_25;
		    goto next_loop_73;
		  end_loop_74:
		  end_25:
		    level = level - (SI_Long)1L;
		    goto next_loop_72;
		  end_loop_72:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
				gensymed_symbol,temp,gensymed_symbol_1);
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
		  next_loop_75:
		    if (level < ab_loop_bind_)
			goto end_loop_75;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_76:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_77:
		    if ( !TRUEP(marked))
			goto end_loop_76;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_77;
		  end_loop_76:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_26;
		    goto next_loop_76;
		  end_loop_77:
		  end_26:
		    level = level - (SI_Long)1L;
		    goto next_loop_75;
		  end_loop_75:;
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
		      next_loop_78:
			if (level < ab_loop_bind_)
			    goto end_loop_78;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_79:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_80:
			if ( !TRUEP(marked))
			    goto end_loop_79;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_80;
		      end_loop_79:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_27;
			goto next_loop_79;
		      end_loop_80:
		      end_27:
			level = level - (SI_Long)1L;
			goto next_loop_78;
		      end_loop_78:;
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
		      next_loop_81:
			if (level < ab_loop_bind_)
			    goto end_loop_81;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_82:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_83:
			if ( !TRUEP(marked))
			    goto end_loop_82;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_83;
		      end_loop_82:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_28;
			goto next_loop_82;
		      end_loop_83:
		      end_28:
			level = level - (SI_Long)1L;
			goto next_loop_81;
		      end_loop_81:;
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
				IFIX(ISVREF(Text_list_class_description,
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
			    temp_2 = (SI_Long)0L < gensymed_symbol_3;
			}
			else
			    temp_2 = TRUEP(Nil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2);
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
		      next_loop_84:
			if (level < ab_loop_bind_)
			    goto end_loop_84;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_85:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_86:
			if ( !TRUEP(marked))
			    goto end_loop_85;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_86;
		      end_loop_85:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_29;
			goto next_loop_85;
		      end_loop_86:
		      end_29:
			level = level - (SI_Long)1L;
			goto next_loop_84;
		      end_loop_84:;
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
				    gensymed_symbol,temp,gensymed_symbol_1);
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
		      next_loop_87:
			if (level < ab_loop_bind_)
			    goto end_loop_87;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_88:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_89:
			if ( !TRUEP(marked))
			    goto end_loop_88;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_89;
		      end_loop_88:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_30;
			goto next_loop_88;
		      end_loop_89:
		      end_30:
			level = level - (SI_Long)1L;
			goto next_loop_87;
		      end_loop_87:;
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
			  next_loop_90:
			    if (level < ab_loop_bind_)
				goto end_loop_90;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_91:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_92:
			    if ( !TRUEP(marked))
				goto end_loop_91;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_92;
			  end_loop_91:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_31;
			    goto next_loop_91;
			  end_loop_92:
			  end_31:
			    level = level - (SI_Long)1L;
			    goto next_loop_90;
			  end_loop_90:;
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
			  next_loop_93:
			    if (level < ab_loop_bind_)
				goto end_loop_93;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_94:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_95:
			    if ( !TRUEP(marked))
				goto end_loop_94;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_95;
			  end_loop_94:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_32;
			    goto next_loop_94;
			  end_loop_95:
			  end_32:
			    level = level - (SI_Long)1L;
			    goto next_loop_93;
			  end_loop_93:;
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
				    IFIX(ISVREF(Text_array_class_description,
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
				temp_2 = (SI_Long)0L < gensymed_symbol_3;
			    }
			    else
				temp_2 = TRUEP(Nil);
			}
			else
			    temp_2 = TRUEP(Nil);
		    }
		    if (temp_2)
			temp = Qtext;
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
		      next_loop_96:
			if (level < ab_loop_bind_)
			    goto end_loop_96;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_97:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_98:
			if ( !TRUEP(marked))
			    goto end_loop_97;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_98;
		      end_loop_97:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_33;
			goto next_loop_97;
		      end_loop_98:
		      end_33:
			level = level - (SI_Long)1L;
			goto next_loop_96;
		      end_loop_96:;
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
				    gensymed_symbol,temp,gensymed_symbol_1);
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
		      next_loop_99:
			if (level < ab_loop_bind_)
			    goto end_loop_99;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_100:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_101:
			if ( !TRUEP(marked))
			    goto end_loop_100;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_101;
		      end_loop_100:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_34;
			goto next_loop_100;
		      end_loop_101:
		      end_34:
			level = level - (SI_Long)1L;
			goto next_loop_99;
		      end_loop_99:;
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
			  next_loop_102:
			    if (level < ab_loop_bind_)
				goto end_loop_102;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_103:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_104:
			    if ( !TRUEP(marked))
				goto end_loop_103;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_104;
			  end_loop_103:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_35;
			    goto next_loop_103;
			  end_loop_104:
			  end_35:
			    level = level - (SI_Long)1L;
			    goto next_loop_102;
			  end_loop_102:;
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
			  next_loop_105:
			    if (level < ab_loop_bind_)
				goto end_loop_105;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_106:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_107:
			    if ( !TRUEP(marked))
				goto end_loop_106;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_107;
			  end_loop_106:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_36;
			    goto next_loop_106;
			  end_loop_107:
			  end_36:
			    level = level - (SI_Long)1L;
			    goto next_loop_105;
			  end_loop_105:;
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
				    IFIX(ISVREF(Truth_value_list_class_description,
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
				temp_2 = (SI_Long)0L < gensymed_symbol_3;
			    }
			    else
				temp_2 = TRUEP(Nil);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2);
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
			  next_loop_108:
			    if (level < ab_loop_bind_)
				goto end_loop_108;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_109:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_110:
			    if ( !TRUEP(marked))
				goto end_loop_109;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_110;
			  end_loop_109:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_37;
			    goto next_loop_109;
			  end_loop_110:
			  end_37:
			    level = level - (SI_Long)1L;
			    goto next_loop_108;
			  end_loop_108:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = class_name;
				temp_1 = Symbol_properties_table;
				temp = 
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
					gensymed_symbol,temp,
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
			  next_loop_111:
			    if (level < ab_loop_bind_)
				goto end_loop_111;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_112:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_113:
			    if ( !TRUEP(marked))
				goto end_loop_112;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_113;
			  end_loop_112:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_38;
			    goto next_loop_112;
			  end_loop_113:
			  end_38:
			    level = level - (SI_Long)1L;
			    goto next_loop_111;
			  end_loop_111:;
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
			      next_loop_114:
				if (level < ab_loop_bind_)
				    goto end_loop_114;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_115:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_116:
				if ( !TRUEP(marked))
				    goto end_loop_115;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_116;
			      end_loop_115:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_39;
				goto next_loop_115;
			      end_loop_116:
			      end_39:
				level = level - (SI_Long)1L;
				goto next_loop_114;
			      end_loop_114:;
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
			      next_loop_117:
				if (level < ab_loop_bind_)
				    goto end_loop_117;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_118:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_119:
				if ( !TRUEP(marked))
				    goto end_loop_118;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_119;
			      end_loop_118:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_40;
				goto next_loop_118;
			      end_loop_119:
			      end_40:
				level = level - (SI_Long)1L;
				goto next_loop_117;
			      end_loop_117:;
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
					IFIX(ISVREF(Truth_value_array_class_description,
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
			if (temp_2)
			    temp = Qtruth_value;
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
			  next_loop_120:
			    if (level < ab_loop_bind_)
				goto end_loop_120;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_121:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_122:
			    if ( !TRUEP(marked))
				goto end_loop_121;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_122;
			  end_loop_121:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_41;
			    goto next_loop_121;
			  end_loop_122:
			  end_41:
			    level = level - (SI_Long)1L;
			    goto next_loop_120;
			  end_loop_120:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = class_name;
				temp_1 = Symbol_properties_table;
				temp = 
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
					gensymed_symbol,temp,
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
			  next_loop_123:
			    if (level < ab_loop_bind_)
				goto end_loop_123;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_124:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_125:
			    if ( !TRUEP(marked))
				goto end_loop_124;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_125;
			  end_loop_124:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_42;
			    goto next_loop_124;
			  end_loop_125:
			  end_42:
			    level = level - (SI_Long)1L;
			    goto next_loop_123;
			  end_loop_123:;
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
			      next_loop_126:
				if (level < ab_loop_bind_)
				    goto end_loop_126;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_127:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_128:
				if ( !TRUEP(marked))
				    goto end_loop_127;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_128;
			      end_loop_127:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_43;
				goto next_loop_127;
			      end_loop_128:
			      end_43:
				level = level - (SI_Long)1L;
				goto next_loop_126;
			      end_loop_126:;
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
			      next_loop_129:
				if (level < ab_loop_bind_)
				    goto end_loop_129;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_130:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_131:
				if ( !TRUEP(marked))
				    goto end_loop_130;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_131;
			      end_loop_130:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_44;
				goto next_loop_130;
			      end_loop_131:
			      end_44:
				level = level - (SI_Long)1L;
				goto next_loop_129;
			      end_loop_129:;
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
					IFIX(ISVREF(Symbol_list_class_description,
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
			    if (temp_2);
			    else {
				skip_list = CDR(Symbol_properties_table);
				key_value = class_name;
				key_hash_value = 
					SXHASH_SYMBOL_1(class_name) & 
					IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_132:
				if (level < ab_loop_bind_)
				    goto end_loop_132;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_133:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_134:
				if ( !TRUEP(marked))
				    goto end_loop_133;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_134;
			      end_loop_133:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_45;
				goto next_loop_133;
			      end_loop_134:
			      end_45:
				level = level - (SI_Long)1L;
				goto next_loop_132;
			      end_loop_132:;
				gensymed_symbol = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if ( !TRUEP(gensymed_symbol)) {
				    gensymed_symbol = class_name;
				    temp_1 = Symbol_properties_table;
				    temp = 
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
					    gensymed_symbol,temp,
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
			      next_loop_135:
				if (level < ab_loop_bind_)
				    goto end_loop_135;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_136:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_137:
				if ( !TRUEP(marked))
				    goto end_loop_136;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_137;
			      end_loop_136:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_46;
				goto next_loop_136;
			      end_loop_137:
			      end_46:
				level = level - (SI_Long)1L;
				goto next_loop_135;
			      end_loop_135:;
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
				  next_loop_138:
				    if (level < ab_loop_bind_)
					goto end_loop_138;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_139:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_140:
				    if ( !TRUEP(marked))
					goto end_loop_139;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_140;
				  end_loop_139:
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
					goto end_47;
				    goto next_loop_139;
				  end_loop_140:
				  end_47:
				    level = level - (SI_Long)1L;
				    goto next_loop_138;
				  end_loop_138:;
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
				  next_loop_141:
				    if (level < ab_loop_bind_)
					goto end_loop_141;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_142:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_143:
				    if ( !TRUEP(marked))
					goto end_loop_142;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_143;
				  end_loop_142:
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
					goto end_48;
				    goto next_loop_142;
				  end_loop_143:
				  end_48:
				    level = level - (SI_Long)1L;
				    goto next_loop_141;
				  end_loop_141:;
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
					    IFIX(ISVREF(Symbol_array_class_description,
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
			    if (temp_2)
				temp = Qsymbol;
			    else {
				skip_list = CDR(Symbol_properties_table);
				key_value = class_name;
				key_hash_value = 
					SXHASH_SYMBOL_1(class_name) & 
					IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_144:
				if (level < ab_loop_bind_)
				    goto end_loop_144;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_145:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_146:
				if ( !TRUEP(marked))
				    goto end_loop_145;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_146;
			      end_loop_145:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_49;
				goto next_loop_145;
			      end_loop_146:
			      end_49:
				level = level - (SI_Long)1L;
				goto next_loop_144;
			      end_loop_144:;
				gensymed_symbol = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if ( !TRUEP(gensymed_symbol)) {
				    gensymed_symbol = class_name;
				    temp_1 = Symbol_properties_table;
				    temp = 
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
					    gensymed_symbol,temp,
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
			      next_loop_147:
				if (level < ab_loop_bind_)
				    goto end_loop_147;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_148:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
			      next_loop_149:
				if ( !TRUEP(marked))
				    goto end_loop_148;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp);
				MVS_2(result,succ,marked);
				goto next_loop_149;
			      end_loop_148:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_50;
				goto next_loop_148;
			      end_loop_149:
			      end_50:
				level = level - (SI_Long)1L;
				goto next_loop_147;
			      end_loop_147:;
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
				  next_loop_150:
				    if (level < ab_loop_bind_)
					goto end_loop_150;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_151:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_152:
				    if ( !TRUEP(marked))
					goto end_loop_151;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_152;
				  end_loop_151:
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
					goto end_51;
				    goto next_loop_151;
				  end_loop_152:
				  end_51:
				    level = level - (SI_Long)1L;
				    goto next_loop_150;
				  end_loop_150:;
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
				  next_loop_153:
				    if (level < ab_loop_bind_)
					goto end_loop_153;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_154:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_155:
				    if ( !TRUEP(marked))
					goto end_loop_154;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_155;
				  end_loop_154:
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
					goto end_52;
				    goto next_loop_154;
				  end_loop_155:
				  end_52:
				    level = level - (SI_Long)1L;
				    goto next_loop_153;
				  end_loop_153:;
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
					    IFIX(ISVREF(Item_list_class_description,
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
				if (temp_2);
				else {
				    skip_list = CDR(Symbol_properties_table);
				    key_value = class_name;
				    key_hash_value = 
					    SXHASH_SYMBOL_1(class_name) & 
					    IFIX(Most_positive_fixnum);
				    bottom_level = (SI_Long)0L;
				    marked = Nil;
				    pred = M_CAR(skip_list);
				    curr = Nil;
				    succ = Nil;
				    level = (SI_Long)31L;
				    ab_loop_bind_ = bottom_level;
				  next_loop_156:
				    if (level < ab_loop_bind_)
					goto end_loop_156;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_157:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_158:
				    if ( !TRUEP(marked))
					goto end_loop_157;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_158;
				  end_loop_157:
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
					goto end_53;
				    goto next_loop_157;
				  end_loop_158:
				  end_53:
				    level = level - (SI_Long)1L;
				    goto next_loop_156;
				  end_loop_156:;
				    gensymed_symbol = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
					    Nil) : Nil;
				    if ( !TRUEP(gensymed_symbol)) {
					gensymed_symbol = class_name;
					temp_1 = Symbol_properties_table;
					temp = 
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
					    SVREF(svref_arg_1,svref_arg_2) 
						    = svref_new_value;
					    if ( 
						    !TRUEP(ISVREF(Available_lookup_conses_vector,
						    IFIX(Current_thread_index)))) 
							{
						svref_arg_1 = 
							Available_lookup_conses_tail_vector;
						svref_arg_2 = 
							Current_thread_index;
						SVREF(svref_arg_1,
							svref_arg_2) = Nil;
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
					    SVREF(svref_arg_1,svref_arg_2) 
						    = svref_new_value;
					    if ( 
						    !TRUEP(ISVREF(Available_lookup_conses_vector,
						    IFIX(Current_thread_index)))) 
							{
						svref_arg_1 = 
							Available_lookup_conses_tail_vector;
						svref_arg_2 = 
							Current_thread_index;
						SVREF(svref_arg_1,
							svref_arg_2) = Nil;
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
						FIX((SI_Long)31L),Qeq,Nil,
						T,gensymed_symbol,temp,
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
				  next_loop_159:
				    if (level < ab_loop_bind_)
					goto end_loop_159;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_160:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_161:
				    if ( !TRUEP(marked))
					goto end_loop_160;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_161;
				  end_loop_160:
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
					goto end_54;
				    goto next_loop_160;
				  end_loop_161:
				  end_54:
				    level = level - (SI_Long)1L;
				    goto next_loop_159;
				  end_loop_159:;
				    kb_properties = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
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
				      next_loop_162:
					if (level < ab_loop_bind_)
					    goto end_loop_162;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_163:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_164:
					if ( !TRUEP(marked))
					    goto end_loop_163;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_164;
				      end_loop_163:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_55;
					goto next_loop_163;
				      end_loop_164:
				      end_55:
					level = level - (SI_Long)1L;
					goto next_loop_162;
				      end_loop_162:;
					kb_specific_value = 
						IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
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
				      next_loop_165:
					if (level < ab_loop_bind_)
					    goto end_loop_165;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_166:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_167:
					if ( !TRUEP(marked))
					    goto end_loop_166;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_167;
				      end_loop_166:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_56;
					goto next_loop_166;
				      end_loop_167:
				      end_56:
					level = level - (SI_Long)1L;
					goto next_loop_165;
				      end_loop_165:;
					resulting_value = IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
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
						IFIX(ISVREF(Item_array_class_description,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
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
				if (temp_2)
				    temp = list_constant;
				else {
				    skip_list = CDR(Symbol_properties_table);
				    key_value = class_name;
				    key_hash_value = 
					    SXHASH_SYMBOL_1(class_name) & 
					    IFIX(Most_positive_fixnum);
				    bottom_level = (SI_Long)0L;
				    marked = Nil;
				    pred = M_CAR(skip_list);
				    curr = Nil;
				    succ = Nil;
				    level = (SI_Long)31L;
				    ab_loop_bind_ = bottom_level;
				  next_loop_168:
				    if (level < ab_loop_bind_)
					goto end_loop_168;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_169:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_170:
				    if ( !TRUEP(marked))
					goto end_loop_169;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_170;
				  end_loop_169:
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
					goto end_57;
				    goto next_loop_169;
				  end_loop_170:
				  end_57:
				    level = level - (SI_Long)1L;
				    goto next_loop_168;
				  end_loop_168:;
				    gensymed_symbol = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
					    Nil) : Nil;
				    if ( !TRUEP(gensymed_symbol)) {
					gensymed_symbol = class_name;
					temp_1 = Symbol_properties_table;
					temp = 
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
					    SVREF(svref_arg_1,svref_arg_2) 
						    = svref_new_value;
					    if ( 
						    !TRUEP(ISVREF(Available_lookup_conses_vector,
						    IFIX(Current_thread_index)))) 
							{
						svref_arg_1 = 
							Available_lookup_conses_tail_vector;
						svref_arg_2 = 
							Current_thread_index;
						SVREF(svref_arg_1,
							svref_arg_2) = Nil;
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
					    SVREF(svref_arg_1,svref_arg_2) 
						    = svref_new_value;
					    if ( 
						    !TRUEP(ISVREF(Available_lookup_conses_vector,
						    IFIX(Current_thread_index)))) 
							{
						svref_arg_1 = 
							Available_lookup_conses_tail_vector;
						svref_arg_2 = 
							Current_thread_index;
						SVREF(svref_arg_1,
							svref_arg_2) = Nil;
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
						FIX((SI_Long)31L),Qeq,Nil,
						T,gensymed_symbol,temp,
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
				  next_loop_171:
				    if (level < ab_loop_bind_)
					goto end_loop_171;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_172:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				  next_loop_173:
				    if ( !TRUEP(marked))
					goto end_loop_172;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_173;
				  end_loop_172:
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
					goto end_58;
				    goto next_loop_172;
				  end_loop_173:
				  end_58:
				    level = level - (SI_Long)1L;
				    goto next_loop_171;
				  end_loop_171:;
				    kb_properties = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
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
				      next_loop_174:
					if (level < ab_loop_bind_)
					    goto end_loop_174;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_175:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_176:
					if ( !TRUEP(marked))
					    goto end_loop_175;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_176;
				      end_loop_175:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_59;
					goto next_loop_175;
				      end_loop_176:
				      end_59:
					level = level - (SI_Long)1L;
					goto next_loop_174;
				      end_loop_174:;
					kb_specific_value = 
						IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
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
				      next_loop_177:
					if (level < ab_loop_bind_)
					    goto end_loop_177;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_178:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_179:
					if ( !TRUEP(marked))
					    goto end_loop_178;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_179;
				      end_loop_178:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_60;
					goto next_loop_178;
				      end_loop_179:
				      end_60:
					level = level - (SI_Long)1L;
					goto next_loop_177;
				      end_loop_177:;
					resulting_value = IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
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
						IFIX(ISVREF(Value_list_class_description,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
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
				    if (temp_2);
				    else {
					skip_list = 
						CDR(Symbol_properties_table);
					key_value = class_name;
					key_hash_value = 
						SXHASH_SYMBOL_1(class_name) 
						& IFIX(Most_positive_fixnum);
					bottom_level = (SI_Long)0L;
					marked = Nil;
					pred = M_CAR(skip_list);
					curr = Nil;
					succ = Nil;
					level = (SI_Long)31L;
					ab_loop_bind_ = bottom_level;
				      next_loop_180:
					if (level < ab_loop_bind_)
					    goto end_loop_180;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_181:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_182:
					if ( !TRUEP(marked))
					    goto end_loop_181;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_182;
				      end_loop_181:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_61;
					goto next_loop_181;
				      end_loop_182:
				      end_61:
					level = level - (SI_Long)1L;
					goto next_loop_180;
				      end_loop_180:;
					gensymed_symbol = IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
						ISVREF(curr,(SI_Long)3L) : 
						Nil) : Nil;
					if ( !TRUEP(gensymed_symbol)) {
					    gensymed_symbol = class_name;
					    temp_1 = Symbol_properties_table;
					    temp = 
						    FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
						    & 
						    IFIX(Most_positive_fixnum));
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
						svref_arg_2 = 
							Current_thread_index;
						svref_new_value = 
							M_CDR(new_cons);
						SVREF(svref_arg_1,
							svref_arg_2) = 
							svref_new_value;
						if ( 
							!TRUEP(ISVREF(Available_lookup_conses_vector,
							IFIX(Current_thread_index)))) 
							    {
						    svref_arg_1 = 
							    Available_lookup_conses_tail_vector;
						    svref_arg_2 = 
							    Current_thread_index;
						    SVREF(svref_arg_1,
							    svref_arg_2) = Nil;
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
						svref_arg_2 = 
							Current_thread_index;
						svref_new_value = 
							M_CDR(new_cons);
						SVREF(svref_arg_1,
							svref_arg_2) = 
							svref_new_value;
						if ( 
							!TRUEP(ISVREF(Available_lookup_conses_vector,
							IFIX(Current_thread_index)))) 
							    {
						    svref_arg_1 = 
							    Available_lookup_conses_tail_vector;
						    svref_arg_2 = 
							    Current_thread_index;
						    SVREF(svref_arg_1,
							    svref_arg_2) = Nil;
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
						    FIX((SI_Long)31L),Qeq,
						    Nil,T,gensymed_symbol,
						    temp,gensymed_symbol_1);
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
				      next_loop_183:
					if (level < ab_loop_bind_)
					    goto end_loop_183;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_184:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_185:
					if ( !TRUEP(marked))
					    goto end_loop_184;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_185;
				      end_loop_184:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_62;
					goto next_loop_184;
				      end_loop_185:
				      end_62:
					level = level - (SI_Long)1L;
					goto next_loop_183;
				      end_loop_183:;
					kb_properties = IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
						ISVREF(curr,(SI_Long)3L) : 
						Nil) : Nil;
					if (kb_properties);
					else
					    kb_properties = Nil;
					if (kb_properties) {
					    skip_list = CDR(kb_properties);
					    key_value = 
						    Class_description_gkbprop;
					    key_hash_value = 
						    SXHASH_SYMBOL_1(Class_description_gkbprop) 
						    & 
						    IFIX(Most_positive_fixnum);
					    bottom_level = (SI_Long)0L;
					    marked = Nil;
					    pred = M_CAR(skip_list);
					    curr = Nil;
					    succ = Nil;
					    level = (SI_Long)31L;
					    ab_loop_bind_ = bottom_level;
					  next_loop_186:
					    if (level < ab_loop_bind_)
						goto end_loop_186;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					  next_loop_187:
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					  next_loop_188:
					    if ( !TRUEP(marked))
						goto end_loop_187;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					    goto next_loop_188;
					  end_loop_187:
					    entry_hash = ISVREF(curr,
						    (SI_Long)1L);
					    if (IFIX(entry_hash) < 
						    key_hash_value || 
						    IFIX(entry_hash) == 
						    key_hash_value &&  
						    !EQ(key_value,
						    ISVREF(curr,
							(SI_Long)2L))) {
						pred = curr;
						curr = succ;
					    }
					    else
						goto end_63;
					    goto next_loop_187;
					  end_loop_188:
					  end_63:
					    level = level - (SI_Long)1L;
					    goto next_loop_186;
					  end_loop_186:;
					    kb_specific_value = 
						    IFIX(ISVREF(curr,
						    (SI_Long)1L)) == 
						    key_hash_value ? 
						    (EQ(key_value,
						    ISVREF(curr,
						    (SI_Long)2L)) ? 
						    ISVREF(curr,
						    (SI_Long)3L) : Nil) : Nil;
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
					    resulting_value = 
						    kb_specific_value;
					else {
					    skip_list = CDR(global_properties);
					    key_value = 
						    Class_description_gkbprop;
					    key_hash_value = 
						    SXHASH_SYMBOL_1(Class_description_gkbprop) 
						    & 
						    IFIX(Most_positive_fixnum);
					    bottom_level = (SI_Long)0L;
					    marked = Nil;
					    pred = M_CAR(skip_list);
					    curr = Nil;
					    succ = Nil;
					    level = (SI_Long)31L;
					    ab_loop_bind_ = bottom_level;
					  next_loop_189:
					    if (level < ab_loop_bind_)
						goto end_loop_189;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					  next_loop_190:
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					  next_loop_191:
					    if ( !TRUEP(marked))
						goto end_loop_190;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					    goto next_loop_191;
					  end_loop_190:
					    entry_hash = ISVREF(curr,
						    (SI_Long)1L);
					    if (IFIX(entry_hash) < 
						    key_hash_value || 
						    IFIX(entry_hash) == 
						    key_hash_value &&  
						    !EQ(key_value,
						    ISVREF(curr,
							(SI_Long)2L))) {
						pred = curr;
						curr = succ;
					    }
					    else
						goto end_64;
					    goto next_loop_190;
					  end_loop_191:
					  end_64:
					    level = level - (SI_Long)1L;
					    goto next_loop_189;
					  end_loop_189:;
					    resulting_value = 
						    IFIX(ISVREF(curr,
						    (SI_Long)1L)) == 
						    key_hash_value ? 
						    (EQ(key_value,
						    ISVREF(curr,
						    (SI_Long)2L)) ? 
						    ISVREF(curr,
						    (SI_Long)3L) : Nil) : Nil;
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
						    IFIX(ISVREF(Value_array_class_description,
						    (SI_Long)18L));
					    sub_class_vector_index = 
						    superior_class_bit_number 
						    >>  -  - (SI_Long)3L;
					    if (sub_class_vector_index < 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							{
						gensymed_symbol_3 = 
							UBYTE_8_ISAREF_1(sub_class_bit_vector,
							sub_class_vector_index);
						gensymed_symbol_4 = 
							(SI_Long)1L;
						gensymed_symbol_5 = 
							superior_class_bit_number 
							& (SI_Long)7L;
						gensymed_symbol_4 = 
							gensymed_symbol_4 
							<< gensymed_symbol_5;
						gensymed_symbol_3 = 
							gensymed_symbol_3 
							& gensymed_symbol_4;
						temp_2 = (SI_Long)0L < 
							gensymed_symbol_3;
					    }
					    else
						temp_2 = TRUEP(Nil);
					}
					else
					    temp_2 = TRUEP(Nil);
				    }
				    if (temp_2)
					temp = Qdatum;
				    else {
					skip_list = 
						CDR(Symbol_properties_table);
					key_value = class_name;
					key_hash_value = 
						SXHASH_SYMBOL_1(class_name) 
						& IFIX(Most_positive_fixnum);
					bottom_level = (SI_Long)0L;
					marked = Nil;
					pred = M_CAR(skip_list);
					curr = Nil;
					succ = Nil;
					level = (SI_Long)31L;
					ab_loop_bind_ = bottom_level;
				      next_loop_192:
					if (level < ab_loop_bind_)
					    goto end_loop_192;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_193:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_194:
					if ( !TRUEP(marked))
					    goto end_loop_193;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_194;
				      end_loop_193:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_65;
					goto next_loop_193;
				      end_loop_194:
				      end_65:
					level = level - (SI_Long)1L;
					goto next_loop_192;
				      end_loop_192:;
					gensymed_symbol = IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
						ISVREF(curr,(SI_Long)3L) : 
						Nil) : Nil;
					if ( !TRUEP(gensymed_symbol)) {
					    gensymed_symbol = class_name;
					    temp_1 = Symbol_properties_table;
					    temp = 
						    FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
						    & 
						    IFIX(Most_positive_fixnum));
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
						svref_arg_2 = 
							Current_thread_index;
						svref_new_value = 
							M_CDR(new_cons);
						SVREF(svref_arg_1,
							svref_arg_2) = 
							svref_new_value;
						if ( 
							!TRUEP(ISVREF(Available_lookup_conses_vector,
							IFIX(Current_thread_index)))) 
							    {
						    svref_arg_1 = 
							    Available_lookup_conses_tail_vector;
						    svref_arg_2 = 
							    Current_thread_index;
						    SVREF(svref_arg_1,
							    svref_arg_2) = Nil;
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
						svref_arg_2 = 
							Current_thread_index;
						svref_new_value = 
							M_CDR(new_cons);
						SVREF(svref_arg_1,
							svref_arg_2) = 
							svref_new_value;
						if ( 
							!TRUEP(ISVREF(Available_lookup_conses_vector,
							IFIX(Current_thread_index)))) 
							    {
						    svref_arg_1 = 
							    Available_lookup_conses_tail_vector;
						    svref_arg_2 = 
							    Current_thread_index;
						    SVREF(svref_arg_1,
							    svref_arg_2) = Nil;
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
						    FIX((SI_Long)31L),Qeq,
						    Nil,T,gensymed_symbol,
						    temp,gensymed_symbol_1);
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
				      next_loop_195:
					if (level < ab_loop_bind_)
					    goto end_loop_195;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_196:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
				      next_loop_197:
					if ( !TRUEP(marked))
					    goto end_loop_196;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_1 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_1,temp);
					MVS_2(result,succ,marked);
					goto next_loop_197;
				      end_loop_196:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
					    pred = curr;
					    curr = succ;
					}
					else
					    goto end_66;
					goto next_loop_196;
				      end_loop_197:
				      end_66:
					level = level - (SI_Long)1L;
					goto next_loop_195;
				      end_loop_195:;
					kb_properties = IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
						ISVREF(curr,(SI_Long)3L) : 
						Nil) : Nil;
					if (kb_properties);
					else
					    kb_properties = Nil;
					if (kb_properties) {
					    skip_list = CDR(kb_properties);
					    key_value = 
						    Class_description_gkbprop;
					    key_hash_value = 
						    SXHASH_SYMBOL_1(Class_description_gkbprop) 
						    & 
						    IFIX(Most_positive_fixnum);
					    bottom_level = (SI_Long)0L;
					    marked = Nil;
					    pred = M_CAR(skip_list);
					    curr = Nil;
					    succ = Nil;
					    level = (SI_Long)31L;
					    ab_loop_bind_ = bottom_level;
					  next_loop_198:
					    if (level < ab_loop_bind_)
						goto end_loop_198;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					  next_loop_199:
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					  next_loop_200:
					    if ( !TRUEP(marked))
						goto end_loop_199;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					    goto next_loop_200;
					  end_loop_199:
					    entry_hash = ISVREF(curr,
						    (SI_Long)1L);
					    if (IFIX(entry_hash) < 
						    key_hash_value || 
						    IFIX(entry_hash) == 
						    key_hash_value &&  
						    !EQ(key_value,
						    ISVREF(curr,
							(SI_Long)2L))) {
						pred = curr;
						curr = succ;
					    }
					    else
						goto end_67;
					    goto next_loop_199;
					  end_loop_200:
					  end_67:
					    level = level - (SI_Long)1L;
					    goto next_loop_198;
					  end_loop_198:;
					    kb_specific_value = 
						    IFIX(ISVREF(curr,
						    (SI_Long)1L)) == 
						    key_hash_value ? 
						    (EQ(key_value,
						    ISVREF(curr,
						    (SI_Long)2L)) ? 
						    ISVREF(curr,
						    (SI_Long)3L) : Nil) : Nil;
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
					    resulting_value = 
						    kb_specific_value;
					else {
					    skip_list = CDR(global_properties);
					    key_value = 
						    Class_description_gkbprop;
					    key_hash_value = 
						    SXHASH_SYMBOL_1(Class_description_gkbprop) 
						    & 
						    IFIX(Most_positive_fixnum);
					    bottom_level = (SI_Long)0L;
					    marked = Nil;
					    pred = M_CAR(skip_list);
					    curr = Nil;
					    succ = Nil;
					    level = (SI_Long)31L;
					    ab_loop_bind_ = bottom_level;
					  next_loop_201:
					    if (level < ab_loop_bind_)
						goto end_loop_201;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					  next_loop_202:
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					  next_loop_203:
					    if ( !TRUEP(marked))
						goto end_loop_202;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					    goto next_loop_203;
					  end_loop_202:
					    entry_hash = ISVREF(curr,
						    (SI_Long)1L);
					    if (IFIX(entry_hash) < 
						    key_hash_value || 
						    IFIX(entry_hash) == 
						    key_hash_value &&  
						    !EQ(key_value,
						    ISVREF(curr,
							(SI_Long)2L))) {
						pred = curr;
						curr = succ;
					    }
					    else
						goto end_68;
					    goto next_loop_202;
					  end_loop_203:
					  end_68:
					    level = level - (SI_Long)1L;
					    goto next_loop_201;
					  end_loop_201:;
					    resulting_value = 
						    IFIX(ISVREF(curr,
						    (SI_Long)1L)) == 
						    key_hash_value ? 
						    (EQ(key_value,
						    ISVREF(curr,
						    (SI_Long)2L)) ? 
						    ISVREF(curr,
						    (SI_Long)3L) : Nil) : Nil;
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
						    IFIX(ISVREF(G2_list_class_description,
						    (SI_Long)18L));
					    sub_class_vector_index = 
						    superior_class_bit_number 
						    >>  -  - (SI_Long)3L;
					    if (sub_class_vector_index < 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							{
						gensymed_symbol_3 = 
							UBYTE_8_ISAREF_1(sub_class_bit_vector,
							sub_class_vector_index);
						gensymed_symbol_4 = 
							(SI_Long)1L;
						gensymed_symbol_5 = 
							superior_class_bit_number 
							& (SI_Long)7L;
						gensymed_symbol_4 = 
							gensymed_symbol_4 
							<< gensymed_symbol_5;
						gensymed_symbol_3 = 
							gensymed_symbol_3 
							& gensymed_symbol_4;
						temp_2 = (SI_Long)0L < 
							gensymed_symbol_3;
					    }
					    else
						temp_2 = TRUEP(Nil);
					}
					else
					    temp_2 = TRUEP(Nil);
					if (temp_2);
					else {
					    skip_list = 
						    CDR(Symbol_properties_table);
					    key_value = class_name;
					    key_hash_value = 
						    SXHASH_SYMBOL_1(class_name) 
						    & 
						    IFIX(Most_positive_fixnum);
					    bottom_level = (SI_Long)0L;
					    marked = Nil;
					    pred = M_CAR(skip_list);
					    curr = Nil;
					    succ = Nil;
					    level = (SI_Long)31L;
					    ab_loop_bind_ = bottom_level;
					  next_loop_204:
					    if (level < ab_loop_bind_)
						goto end_loop_204;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					  next_loop_205:
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					  next_loop_206:
					    if ( !TRUEP(marked))
						goto end_loop_205;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					    goto next_loop_206;
					  end_loop_205:
					    entry_hash = ISVREF(curr,
						    (SI_Long)1L);
					    if (IFIX(entry_hash) < 
						    key_hash_value || 
						    IFIX(entry_hash) == 
						    key_hash_value &&  
						    !EQ(key_value,
						    ISVREF(curr,
							(SI_Long)2L))) {
						pred = curr;
						curr = succ;
					    }
					    else
						goto end_69;
					    goto next_loop_205;
					  end_loop_206:
					  end_69:
					    level = level - (SI_Long)1L;
					    goto next_loop_204;
					  end_loop_204:;
					    gensymed_symbol = 
						    IFIX(ISVREF(curr,
						    (SI_Long)1L)) == 
						    key_hash_value ? 
						    (EQ(key_value,
						    ISVREF(curr,
						    (SI_Long)2L)) ? 
						    ISVREF(curr,
						    (SI_Long)3L) : Nil) : Nil;
					    if ( !TRUEP(gensymed_symbol)) {
						gensymed_symbol = class_name;
						temp_1 = 
							Symbol_properties_table;
						temp = 
							FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
							& 
							IFIX(Most_positive_fixnum));
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
						    svref_arg_2 = 
							    Current_thread_index;
						    svref_new_value = 
							    M_CDR(new_cons);
						    SVREF(svref_arg_1,
							    svref_arg_2) = 
							    svref_new_value;
						    if ( 
							    !TRUEP(ISVREF(Available_lookup_conses_vector,
							    IFIX(Current_thread_index)))) 
								{
							svref_arg_1 = 
								Available_lookup_conses_tail_vector;
							svref_arg_2 = 
								Current_thread_index;
							SVREF(svref_arg_1,
								svref_arg_2) 
								= Nil;
						    }
						    gensymed_symbol_1 = 
							    new_cons;
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
						    svref_arg_2 = 
							    Current_thread_index;
						    svref_new_value = 
							    M_CDR(new_cons);
						    SVREF(svref_arg_1,
							    svref_arg_2) = 
							    svref_new_value;
						    if ( 
							    !TRUEP(ISVREF(Available_lookup_conses_vector,
							    IFIX(Current_thread_index)))) 
								{
							svref_arg_1 = 
								Available_lookup_conses_tail_vector;
							svref_arg_2 = 
								Current_thread_index;
							SVREF(svref_arg_1,
								svref_arg_2) 
								= Nil;
						    }
						    gensymed_symbol_2 = 
							    new_cons;
						}
						else
						    gensymed_symbol_2 = Nil;
						if ( !TRUEP(gensymed_symbol_2))
						    gensymed_symbol_2 = 
							    replenish_lookup_cons_pool();
						M_CAR(gensymed_symbol_2) = 
							head;
						M_CDR(gensymed_symbol_2) = 
							tail;
						inline_note_allocate_cons(gensymed_symbol_2,
							Qlookup);
						M_CDR(gensymed_symbol_1) = 
							gensymed_symbol_2;
						inline_note_allocate_cons(gensymed_symbol_1,
							Qlookup);
						gensymed_symbol = 
							set_skip_list_entry(temp_1,
							FIX((SI_Long)31L),
							Qeq,Nil,T,
							gensymed_symbol,
							temp,
							gensymed_symbol_1);
					    }
					    global_properties = 
						    gensymed_symbol;
					    skip_list = CDR(global_properties);
					    key_value = 
						    Current_kb_specific_property_list_property_name;
					    key_hash_value = 
						    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
						    & 
						    IFIX(Most_positive_fixnum);
					    bottom_level = (SI_Long)0L;
					    marked = Nil;
					    pred = M_CAR(skip_list);
					    curr = Nil;
					    succ = Nil;
					    level = (SI_Long)31L;
					    ab_loop_bind_ = bottom_level;
					  next_loop_207:
					    if (level < ab_loop_bind_)
						goto end_loop_207;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					  next_loop_208:
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					  next_loop_209:
					    if ( !TRUEP(marked))
						goto end_loop_208;
					    curr = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						    (SI_Long)0L),level));
					    reference = ISVREF(ISVREF(curr,
						    (SI_Long)0L),level);
					    temp_1 = 
						    ATOMIC_REF_OBJECT(reference);
					    temp = (SI_Long)355L == 
						    ATOMIC_REF_STAMP(reference) 
						    ? T : Nil;
					    result = VALUES_2(temp_1,temp);
					    MVS_2(result,succ,marked);
					    goto next_loop_209;
					  end_loop_208:
					    entry_hash = ISVREF(curr,
						    (SI_Long)1L);
					    if (IFIX(entry_hash) < 
						    key_hash_value || 
						    IFIX(entry_hash) == 
						    key_hash_value &&  
						    !EQ(key_value,
						    ISVREF(curr,
							(SI_Long)2L))) {
						pred = curr;
						curr = succ;
					    }
					    else
						goto end_70;
					    goto next_loop_208;
					  end_loop_209:
					  end_70:
					    level = level - (SI_Long)1L;
					    goto next_loop_207;
					  end_loop_207:;
					    kb_properties = 
						    IFIX(ISVREF(curr,
						    (SI_Long)1L)) == 
						    key_hash_value ? 
						    (EQ(key_value,
						    ISVREF(curr,
						    (SI_Long)2L)) ? 
						    ISVREF(curr,
						    (SI_Long)3L) : Nil) : Nil;
					    if (kb_properties);
					    else
						kb_properties = Nil;
					    if (kb_properties) {
						skip_list = CDR(kb_properties);
						key_value = 
							Class_description_gkbprop;
						key_hash_value = 
							SXHASH_SYMBOL_1(Class_description_gkbprop) 
							& 
							IFIX(Most_positive_fixnum);
						bottom_level = (SI_Long)0L;
						marked = Nil;
						pred = M_CAR(skip_list);
						curr = Nil;
						succ = Nil;
						level = (SI_Long)31L;
						ab_loop_bind_ = bottom_level;
					      next_loop_210:
						if (level < ab_loop_bind_)
						    goto end_loop_210;
						curr = 
							ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							(SI_Long)0L),level));
					      next_loop_211:
						reference = 
							ISVREF(ISVREF(curr,
							(SI_Long)0L),level);
						temp_1 = 
							ATOMIC_REF_OBJECT(reference);
						temp = (SI_Long)355L == 
							ATOMIC_REF_STAMP(reference) 
							? T : Nil;
						result = VALUES_2(temp_1,temp);
						MVS_2(result,succ,marked);
					      next_loop_212:
						if ( !TRUEP(marked))
						    goto end_loop_211;
						curr = 
							ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							(SI_Long)0L),level));
						reference = 
							ISVREF(ISVREF(curr,
							(SI_Long)0L),level);
						temp_1 = 
							ATOMIC_REF_OBJECT(reference);
						temp = (SI_Long)355L == 
							ATOMIC_REF_STAMP(reference) 
							? T : Nil;
						result = VALUES_2(temp_1,temp);
						MVS_2(result,succ,marked);
						goto next_loop_212;
					      end_loop_211:
						entry_hash = ISVREF(curr,
							(SI_Long)1L);
						if (IFIX(entry_hash) < 
							key_hash_value || 
							IFIX(entry_hash) 
							== key_hash_value 
							&&  !EQ(key_value,
							ISVREF(curr,
							(SI_Long)2L))) {
						    pred = curr;
						    curr = succ;
						}
						else
						    goto end_71;
						goto next_loop_211;
					      end_loop_212:
					      end_71:
						level = level - (SI_Long)1L;
						goto next_loop_210;
					      end_loop_210:;
						kb_specific_value = 
							IFIX(ISVREF(curr,
							(SI_Long)1L)) == 
							key_hash_value ? 
							(EQ(key_value,
							ISVREF(curr,
							(SI_Long)2L)) ? 
							ISVREF(curr,
							(SI_Long)3L) : 
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
						resulting_value = 
							kb_specific_value;
					    else {
						skip_list = 
							CDR(global_properties);
						key_value = 
							Class_description_gkbprop;
						key_hash_value = 
							SXHASH_SYMBOL_1(Class_description_gkbprop) 
							& 
							IFIX(Most_positive_fixnum);
						bottom_level = (SI_Long)0L;
						marked = Nil;
						pred = M_CAR(skip_list);
						curr = Nil;
						succ = Nil;
						level = (SI_Long)31L;
						ab_loop_bind_ = bottom_level;
					      next_loop_213:
						if (level < ab_loop_bind_)
						    goto end_loop_213;
						curr = 
							ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							(SI_Long)0L),level));
					      next_loop_214:
						reference = 
							ISVREF(ISVREF(curr,
							(SI_Long)0L),level);
						temp_1 = 
							ATOMIC_REF_OBJECT(reference);
						temp = (SI_Long)355L == 
							ATOMIC_REF_STAMP(reference) 
							? T : Nil;
						result = VALUES_2(temp_1,temp);
						MVS_2(result,succ,marked);
					      next_loop_215:
						if ( !TRUEP(marked))
						    goto end_loop_214;
						curr = 
							ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							(SI_Long)0L),level));
						reference = 
							ISVREF(ISVREF(curr,
							(SI_Long)0L),level);
						temp_1 = 
							ATOMIC_REF_OBJECT(reference);
						temp = (SI_Long)355L == 
							ATOMIC_REF_STAMP(reference) 
							? T : Nil;
						result = VALUES_2(temp_1,temp);
						MVS_2(result,succ,marked);
						goto next_loop_215;
					      end_loop_214:
						entry_hash = ISVREF(curr,
							(SI_Long)1L);
						if (IFIX(entry_hash) < 
							key_hash_value || 
							IFIX(entry_hash) 
							== key_hash_value 
							&&  !EQ(key_value,
							ISVREF(curr,
							(SI_Long)2L))) {
						    pred = curr;
						    curr = succ;
						}
						else
						    goto end_72;
						goto next_loop_214;
					      end_loop_215:
					      end_72:
						level = level - (SI_Long)1L;
						goto next_loop_213;
					      end_loop_213:;
						resulting_value = 
							IFIX(ISVREF(curr,
							(SI_Long)1L)) == 
							key_hash_value ? 
							(EQ(key_value,
							ISVREF(curr,
							(SI_Long)2L)) ? 
							ISVREF(curr,
							(SI_Long)3L) : 
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
						superior_class_bit_number 
							= 
							IFIX(ISVREF(G2_array_class_description,
							(SI_Long)18L));
						sub_class_vector_index = 
							superior_class_bit_number 
							>>  -  - (SI_Long)3L;
						if (sub_class_vector_index 
							< 
							IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							    {
						    gensymed_symbol_3 = 
							    UBYTE_8_ISAREF_1(sub_class_bit_vector,
							    sub_class_vector_index);
						    gensymed_symbol_4 = 
							    (SI_Long)1L;
						    gensymed_symbol_5 = 
							    superior_class_bit_number 
							    & (SI_Long)7L;
						    gensymed_symbol_4 = 
							    gensymed_symbol_4 
							    << 
							    gensymed_symbol_5;
						    gensymed_symbol_3 = 
							    gensymed_symbol_3 
							    & 
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
					if (temp_2)
					    temp = Qitem_or_datum;
					else
					    temp = Nil;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    return VALUES_1(temp);
}

static Object Qitem;               /* item */

/* G2-LIST-OR-ARRAY-CLASS-FOR-ELEMENT-TYPE */
Object g2_list_or_array_class_for_element_type(element_type,g2_array_p_qm)
    Object element_type, g2_array_p_qm;
{
    Object temp;

    x_note_fn_call(143,38);
    if (g2_array_p_qm) {
	if (EQ(element_type,Qinteger))
	    temp = Qinteger_array;
	else if (EQ(element_type,Qfloat))
	    temp = Qfloat_array;
	else if (EQ(element_type,Qnumber) || EQ(element_type,Qquantity))
	    temp = Qquantity_array;
	else if (EQ(element_type,Qtext))
	    temp = Qtext_array;
	else if (EQ(element_type,Qtruth_value))
	    temp = Qtruth_value_array;
	else if (EQ(element_type,Qsymbol))
	    temp = Qsymbol_array;
	else if (EQ(element_type,Qitem))
	    temp = Qitem_array;
	else if (EQ(element_type,Qdatum))
	    temp = Qvalue_array;
	else if (EQ(element_type,Qitem_or_datum))
	    temp = Qg2_array;
	else
	    temp =  !TRUEP(valid_datum_type_specification_p(element_type)) 
		    ? Qitem_array : Qg2_array;
    }
    else if (EQ(element_type,Qinteger))
	temp = Qinteger_list;
    else if (EQ(element_type,Qfloat))
	temp = Qfloat_list;
    else if (EQ(element_type,Qnumber) || EQ(element_type,Qquantity))
	temp = Qquantity_list;
    else if (EQ(element_type,Qtext))
	temp = Qtext_list;
    else if (EQ(element_type,Qtruth_value))
	temp = Qtruth_value_list;
    else if (EQ(element_type,Qsymbol))
	temp = Qsymbol_list;
    else if (EQ(element_type,Qitem))
	temp = Qitem_list;
    else if (EQ(element_type,Qdatum))
	temp = Qvalue_list;
    else if (EQ(element_type,Qitem_or_datum))
	temp = Qg2_list;
    else
	temp =  !TRUEP(valid_datum_type_specification_p(element_type)) ? 
		Qitem_list : Qg2_list;
    return VALUES_1(temp);
}

/* G2-LIST-OR-ARRAY-ELEMENT-TYPE-MAY-CONTAIN-ITEM-P */
Object g2_list_or_array_element_type_may_contain_item_p(element_type)
    Object element_type;
{
    Object temp;

    x_note_fn_call(143,39);
    temp =  !TRUEP(symbolic_type_specification_subtype_p(element_type,
	    Qdatum)) ? T : Nil;
    return VALUES_1(temp);
}

/* G2-LIST-OR-ARRAY-TYPE-OK-P */
Object g2_list_or_array_type_ok_p(required_element_type,list_type,
	    subtype_of_list_type_ok_p_qm)
    Object required_element_type, list_type, subtype_of_list_type_ok_p_qm;
{
    Object temp;

    x_note_fn_call(143,40);
    temp = EQ(required_element_type,list_type) ? T : Nil;
    if (temp);
    else
	temp = 
		required_datum_type_ok_for_g2_list_or_array_p(required_element_type,
		list_type,subtype_of_list_type_ok_p_qm);
    if (temp);
    else
	temp = 
		required_item_type_ok_for_g2_list_or_array_p(required_element_type,
		list_type,subtype_of_list_type_ok_p_qm);
    return VALUES_1(temp);
}

/* REQUIRED-DATUM-TYPE-OK-FOR-G2-LIST-OR-ARRAY-P */
Object required_datum_type_ok_for_g2_list_or_array_p(required_datum_type,
	    g2_list_element_type,subtype_of_element_type_ok_p_qm)
    Object required_datum_type, g2_list_element_type;
    Object subtype_of_element_type_ok_p_qm;
{
    Object temp;

    x_note_fn_call(143,41);
    temp = g2_list_or_array_datum_subtype_p(g2_list_element_type,
	    required_datum_type);
    if (temp);
    else
	temp = subtype_of_element_type_ok_p_qm ? 
		g2_list_or_array_datum_subtype_p(required_datum_type,
		g2_list_element_type) : Qnil;
    return VALUES_1(temp);
}

/* REQUIRED-ITEM-TYPE-OK-FOR-G2-LIST-OR-ARRAY-P */
Object required_item_type_ok_for_g2_list_or_array_p(required_item_type,
	    g2_list_element_type,subtype_of_element_type_ok_p_qm)
    Object required_item_type, g2_list_element_type;
    Object subtype_of_element_type_ok_p_qm;
{
    Object temp;

    x_note_fn_call(143,42);
    temp = EQ(required_item_type,g2_list_element_type) ? T : Nil;
    if (temp);
    else
	temp = g2_list_or_array_item_subtype_p(g2_list_element_type,
		required_item_type);
    if (temp);
    else
	temp = subtype_of_element_type_ok_p_qm ? 
		g2_list_or_array_item_subtype_p(required_item_type,
		g2_list_element_type) : Qnil;
    return VALUES_1(temp);
}

/* G2-LIST-OR-ARRAY-DATUM-SUBTYPE-P */
Object g2_list_or_array_datum_subtype_p(datum_type,superior_datum_type)
    Object datum_type, superior_datum_type;
{
    Object internal_datum_type_qm, internal_superior_datum_type_qm, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(143,43);
    PUSH_SPECIAL_WITH_SYMBOL(Datum_type,Qdatum_type,datum_type,0);
      internal_datum_type_qm = 
	      type_specification_for_user_or_datum_type(Datum_type);
      internal_superior_datum_type_qm = 
	      type_specification_for_user_or_datum_type(superior_datum_type);
      if (internal_datum_type_qm && internal_superior_datum_type_qm) {
	  temp = EQ(internal_datum_type_qm,
		  internal_superior_datum_type_qm) ? T : Nil;
	  if (temp);
	  else
	      temp = type_specification_subtype_p(internal_datum_type_qm,
		      internal_superior_datum_type_qm);
      }
      else
	  temp = Nil;
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* G2-LIST-OR-ARRAY-ITEM-SUBTYPE-P */
Object g2_list_or_array_item_subtype_p(item_type,superior_item_type)
    Object item_type, superior_item_type;
{
    Object internal_datum_type_qm, internal_item_type_qm;
    Object internal_superior_datum_type_qm, internal_superior_item_type_qm;
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(143,44);
    internal_datum_type_qm = 
	    type_specification_for_user_or_datum_type(item_type);
    if ( !TRUEP(internal_datum_type_qm))
	internal_item_type_qm = item_type;
    else if (EQ(internal_datum_type_qm,Qitem_or_datum))
	internal_item_type_qm = Qitem_or_datum;
    else
	internal_item_type_qm = Nil;
    internal_superior_datum_type_qm = 
	    type_specification_for_user_or_datum_type(superior_item_type);
    if ( !TRUEP(internal_superior_datum_type_qm))
	internal_superior_item_type_qm = superior_item_type;
    else if (EQ(internal_superior_datum_type_qm,Qitem_or_datum))
	internal_superior_item_type_qm = Qitem_or_datum;
    else
	internal_superior_item_type_qm = Nil;
    if ( !TRUEP(internal_item_type_qm) ||  
	    !TRUEP(internal_superior_item_type_qm))
	temp = Nil;
    else if (EQ(internal_item_type_qm,internal_superior_item_type_qm))
	temp = T;
    else if (EQ(internal_item_type_qm,Qitem_or_datum))
	temp = Nil;
    else if (EQ(internal_superior_item_type_qm,Qitem_or_datum)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = internal_item_type_qm;
	key_hash_value = SXHASH_SYMBOL_1(internal_item_type_qm) & 
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
	    gensymed_symbol = internal_item_type_qm;
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
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
	temp = gensymed_symbol ? ISVREF(gensymed_symbol,(SI_Long)16L) : Qnil;
    }
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(internal_item_type_qm,
		Class_description_gkbprop);
	temp = gensymed_symbol ? 
		memq_function(internal_superior_item_type_qm,
		ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
    }
    return VALUES_1(temp);
}

static Object Qframe_denotation;   /* frame-denotation */

/* CONVERT-PERMANENT-LIST-STRUCTURE-FOR-SAVING */
Object convert_permanent_list_structure_for_saving(g2_list)
    Object g2_list;
{
    Object current_module_being_saved_qm, ab_loopvar_, ab_loopvar__1;
    Object list_element, list_element_to_save_qm, ab_loopvar__2, ab_loopvar__3;
    Object ab_loopvar__4, x2, frame_denotation_to_save_qm, temp_1;
    char temp;

    x_note_fn_call(143,45);
    if (get_lookup_slot_value(g2_list,Qlist_is_permanent) || 
	    ISVREF(Current_kb_save,(SI_Long)3L)) {
	current_module_being_saved_qm = ISVREF(Current_kb_save,(SI_Long)37L);
	ab_loopvar_ = ISVREF(g2_list,(SI_Long)20L);
	ab_loopvar__1 = Nil;
	list_element = Nil;
	list_element_to_save_qm = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
	ab_loopvar__1 = ab_loopvar_ ? 
		g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		ab_loopvar_) : Nil;
      next_loop:
	if ( !TRUEP(ab_loopvar__1))
	    goto end_loop;
	list_element = ISVREF(ab_loopvar__1,(SI_Long)4L);
	ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	if (SIMPLE_VECTOR_P(list_element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(list_element)) > 
		(SI_Long)2L &&  !EQ(ISVREF(list_element,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(list_element,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if ((SI_Long)0L != (IFIX(ISVREF(list_element,(SI_Long)4L)) & 
		    (SI_Long)1L) || ISVREF(Current_saving_context,
		    (SI_Long)3L) && (SI_Long)0L != 
		    (IFIX(ISVREF(list_element,(SI_Long)5L)) & 
		    (SI_Long)262144L)) {
		if (EQ(get_module_block_is_in(list_element),
			current_module_being_saved_qm) ||  
			!TRUEP(current_module_being_saved_qm))
		    frame_denotation_to_save_qm = list_element;
		else {
		    frame_denotation_to_save_qm = 
			    copy_for_slot_value(get_primary_name_for_frame_if_any(list_element));
		    if (frame_denotation_to_save_qm);
		    else
			frame_denotation_to_save_qm = item_uuid(list_element);
		}
		if (SIMPLE_VECTOR_P(frame_denotation_to_save_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_denotation_to_save_qm)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(frame_denotation_to_save_qm,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(frame_denotation_to_save_qm,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    list_element_to_save_qm = frame_denotation_to_save_qm;
		else if (frame_denotation_to_save_qm)
		    list_element_to_save_qm = 
			    slot_value_list_2(Qframe_denotation,
			    frame_denotation_to_save_qm);
		else
		    list_element_to_save_qm = Nil;
	    }
	    else
		list_element_to_save_qm = Nil;
	}
	else
	    list_element_to_save_qm = SIMPLE_VECTOR_P(list_element) && 
		    EQ(ISVREF(list_element,(SI_Long)1L),
		    Qavailable_frame_vector) ? Nil : 
		    copy_for_slot_value(list_element);
	if (list_element_to_save_qm) {
	    ab_loopvar__4 = slot_value_cons_1(list_element_to_save_qm,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	}
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar__2;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CONVERT-SAVED-LIST-VALUES-TO-G2-LIST-STRUCTURE */
Object convert_saved_list_values_to_g2_list_structure()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_list;
    Object saved_list_values, svref_new_value, value, ab_loop_list_;
    Object value_to_set_qm, x2;
    char temp;
    Declare_special(1);

    x_note_fn_call(143,46);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    g2_list = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      saved_list_values = Nil;
      ab_loopvar_ = collect_subclasses(Qg2_list);
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
      g2_list = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      saved_list_values = ISVREF(g2_list,(SI_Long)20L);
      if (saved_list_values && LISTP(saved_list_values)) {
	  if (Warmbooting_qm) {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(g2_list,Qlist_structure);
	      SVREF(g2_list,FIX((SI_Long)20L)) = Nil;
	      reclaim_slot_value(saved_list_values);
	  }
	  else {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(g2_list,Qlist_structure);
	      svref_new_value = create_empty_g2_list_structure();
	      SVREF(g2_list,FIX((SI_Long)20L)) = svref_new_value;
	      value = Nil;
	      ab_loop_list_ = saved_list_values;
	      value_to_set_qm = Nil;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      value = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (CONSP(value) && EQ(M_CAR(value),Qframe_denotation))
		  value_to_set_qm = find_frame_for_denotation(2,
			  SECOND(value),Qblock);
	      else {
		  if (SIMPLE_VECTOR_P(value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(value,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      value_to_set_qm = value;
		  else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			  (SI_Long)1L),Qavailable_frame_vector))
		      value_to_set_qm = Nil;
		  else
		      value_to_set_qm = copy_for_slot_value(value);
	      }
	      g2_list_insert_at_end(3,value_to_set_qm,g2_list,T);
	      goto next_loop_2;
	    end_loop_2:
	      reclaim_slot_value(saved_list_values);
	  }
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* G2-LIST-ELEMENTS */
Object g2_list_elements varargs_1(int, n)
{
    Object g2_list;
    Object copy_value_elements_qm, ab_loopvar_, ab_loopvar__1, element_value;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, gensymed_symbol;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_1;
    Object temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(143,47);
    INIT_ARGS_nonrelocating();
    g2_list = REQUIRED_ARG_nonrelocating();
    copy_value_elements_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (copy_value_elements_qm) {
	ab_loopvar_ = ISVREF(g2_list,(SI_Long)20L);
	ab_loopvar__1 = Nil;
	element_value = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
	ab_loopvar__1 = ab_loopvar_ ? 
		g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		ab_loopvar_) : Nil;
      next_loop:
	if ( !TRUEP(ab_loopvar__1))
	    goto end_loop;
	element_value = ISVREF(ab_loopvar__1,(SI_Long)4L);
	ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	gensymed_symbol = element_value;
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
	      next_loop_1:
		if (level < ab_loop_bind_)
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_2:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_3:
		if ( !TRUEP(marked))
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_3;
	      end_loop_2:
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
	      end_loop_3:
	      end_1:
		level = level - (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
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
	ab_loopvar__4 = g2_list_cons_1(temp ? (FIXNUMP(element_value) || 
		element_value && SYMBOLP(element_value) ? element_value : 
		copy_evaluation_value_1(element_value)) : element_value,Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar__2);
	return VALUES_1(Qnil);
    }
    else {
	ab_loopvar_ = ISVREF(g2_list,(SI_Long)20L);
	ab_loopvar__1 = Nil;
	element_value = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
	ab_loopvar__1 = ab_loopvar_ ? 
		g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		ab_loopvar_) : Nil;
      next_loop_4:
	if ( !TRUEP(ab_loopvar__1))
	    goto end_loop_4;
	element_value = ISVREF(ab_loopvar__1,(SI_Long)4L);
	ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	ab_loopvar__4 = g2_list_cons_1(element_value,Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	goto next_loop_4;
      end_loop_4:
	return VALUES_1(ab_loopvar__2);
	return VALUES_1(Qnil);
    }
}

/* G2-LIST-FIRST */
Object g2_list_first(g2_list,element_type_qm,return_element_structure_qm)
    Object g2_list, element_type_qm, return_element_structure_qm;
{
    Object temp;

    x_note_fn_call(143,48);
    temp = nth_g2_list_element(FIX((SI_Long)0L),g2_list,element_type_qm,
	    return_element_structure_qm);
    return VALUES_1(temp);
}

/* G2-LIST-SECOND */
Object g2_list_second(g2_list,element_type_qm,return_element_structure_qm)
    Object g2_list, element_type_qm, return_element_structure_qm;
{
    Object temp;

    x_note_fn_call(143,49);
    temp = nth_g2_list_element(FIX((SI_Long)1L),g2_list,element_type_qm,
	    return_element_structure_qm);
    return VALUES_1(temp);
}

/* G2-LIST-LAST */
Object g2_list_last(g2_list,element_type_qm,return_element_structure_qm)
    Object g2_list, element_type_qm, return_element_structure_qm;
{
    Object temp;

    x_note_fn_call(143,50);
    temp = nth_from_end_g2_list_element(FIX((SI_Long)0L),g2_list,
	    element_type_qm,return_element_structure_qm);
    return VALUES_1(temp);
}

/* G2-LIST-NEXT-TO-LAST */
Object g2_list_next_to_last(g2_list,element_type_qm,
	    return_element_structure_qm)
    Object g2_list, element_type_qm, return_element_structure_qm;
{
    Object temp;

    x_note_fn_call(143,51);
    temp = nth_from_end_g2_list_element(FIX((SI_Long)1L),g2_list,
	    element_type_qm,return_element_structure_qm);
    return VALUES_1(temp);
}

/* NTH-G2-LIST-ITEM-OR-EVALUATION-VALUE */
Object nth_g2_list_item_or_evaluation_value(nth_1,g2_list,
	    copy_evaluation_value_element_qm)
    Object nth_1, g2_list, copy_evaluation_value_element_qm;
{
    Object ab_loopvar_, ab_loopvar__1, element_value, element_count;
    Object ab_loop_iter_flag_, gensymed_symbol, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(143,52);
    ab_loopvar_ = ISVREF(g2_list,(SI_Long)20L);
    ab_loopvar__1 = Nil;
    element_value = Nil;
    element_count = FIX((SI_Long)0L);
    ab_loop_iter_flag_ = T;
    ab_loopvar__1 = ab_loopvar_ ? 
	    g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
	    ab_loopvar_) : Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar__1))
	goto end_loop;
    element_value = ISVREF(ab_loopvar__1,(SI_Long)4L);
    ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
    if ( !TRUEP(ab_loop_iter_flag_))
	element_count = FIXNUM_ADD1(element_count);
    if (FIXNUM_EQ(element_count,nth_1)) {
	if (copy_evaluation_value_element_qm) {
	    gensymed_symbol = element_value;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
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
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
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
		    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_2:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_3:
		    if ( !TRUEP(marked))
			goto end_loop_2;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_3;
		  end_loop_2:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	}
	else
	    temp = TRUEP(Nil);
	temp_2 = temp ? (FIXNUMP(element_value) || element_value && 
		SYMBOLP(element_value) ? element_value : 
		copy_evaluation_value_1(element_value)) : element_value;
	goto end_2;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    temp_2 = Nil;
    goto end_2;
    temp_2 = Qnil;
  end_2:;
    return VALUES_1(temp_2);
}

/* NTH-G2-LIST-ELEMENT */
Object nth_g2_list_element(nth_1,g2_list,element_type_qm,
	    return_element_structure_qm)
    Object nth_1, g2_list, element_type_qm, return_element_structure_qm;
{
    Object g2_list_structure, list_1, next_list_element, element_structure;
    Object element_count, ab_loop_iter_flag_, element_value, temp;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(143,53);
    if (g2_list_empty_p(g2_list))
	return VALUES_1(Nil);
    if ( !TRUEP(element_type_qm)) {
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	list_1 = g2_list_structure;
	next_list_element = Nil;
	element_structure = Nil;
	element_count = FIX((SI_Long)0L);
	ab_loop_iter_flag_ = T;
	next_list_element = g2_list_structure_next(ISVREF(list_1,
		(SI_Long)2L),list_1);
      next_loop:
	if ( !TRUEP(next_list_element))
	    goto end_loop;
	element_structure = next_list_element;
	next_list_element = g2_list_structure_next(next_list_element,list_1);
	if ( !TRUEP(ab_loop_iter_flag_))
	    element_count = FIXNUM_ADD1(element_count);
	if (FIXNUM_EQ(element_count,nth_1)) {
	    element_value = ISVREF(element_structure,(SI_Long)4L);
	    if (return_element_structure_qm)
		temp = element_structure;
	    else {
		gensymed_symbol = element_value;
		temp_1 = FIXNUMP(gensymed_symbol);
		if (temp_1);
		else
		    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp_1);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp_1 = EQ(gensymed_symbol,Qtruth_value);
		    if (temp_1);
		    else
			temp_1 = EQ(gensymed_symbol,Qiteration_state);
		    if (temp_1);
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
		      next_loop_1:
			if (level < ab_loop_bind_)
			    goto end_loop_1;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_2:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
		      next_loop_3:
			if ( !TRUEP(marked))
			    goto end_loop_2;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
			goto next_loop_3;
		      end_loop_2:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? (FIXNUMP(element_value) || element_value 
			&& SYMBOLP(element_value) ? element_value : 
			copy_evaluation_value_1(element_value)) : 
			element_value;
	    }
	    goto end_2;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	temp = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else {
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	list_1 = g2_list_structure;
	next_list_element = Nil;
	element_structure = Nil;
	element_value = Nil;
	element_count = FIX((SI_Long)0L);
	next_list_element = g2_list_structure_next(ISVREF(list_1,
		(SI_Long)2L),list_1);
      next_loop_4:
	if ( !TRUEP(next_list_element))
	    goto end_loop_4;
	element_structure = next_list_element;
	next_list_element = g2_list_structure_next(next_list_element,list_1);
	element_value = ISVREF(element_structure,(SI_Long)4L);
	if (g2_list_or_array_element_ok_p(element_value,element_type_qm)) {
	    if (FIXNUM_EQ(element_count,nth_1)) {
		if (return_element_structure_qm)
		    temp = element_structure;
		else {
		    gensymed_symbol = element_value;
		    temp_1 = FIXNUMP(gensymed_symbol);
		    if (temp_1);
		    else
			temp_1 = 
				INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
				!= (SI_Long)0L ? 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				== (SI_Long)1L : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
				(SI_Long)0L ? 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				== (SI_Long)1L : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = gensymed_symbol ? 
				SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = 
				INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
				!= (SI_Long)0L;
		    if (temp_1);
		    else if (CONSP(gensymed_symbol)) {
			gensymed_symbol = M_CDR(gensymed_symbol);
			temp_1 = EQ(gensymed_symbol,Qtruth_value);
			if (temp_1);
			else
			    temp_1 = EQ(gensymed_symbol,Qiteration_state);
			if (temp_1);
			else if (SYMBOLP(gensymed_symbol)) {
			    skip_list = CDR(Defined_evaluation_value_types);
			    key_value = gensymed_symbol;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(gensymed_symbol) & 
				    IFIX(Most_positive_fixnum);
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_6:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_2 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_2,temp);
			    MVS_2(result,succ,marked);
			  next_loop_7:
			    if ( !TRUEP(marked))
				goto end_loop_6;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_2 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_2,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_7;
			  end_loop_6:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				    key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				    TRUEP(Nil)) : TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp = temp_1 ? (FIXNUMP(element_value) || 
			    element_value && SYMBOLP(element_value) ? 
			    element_value : 
			    copy_evaluation_value_1(element_value)) : 
			    element_value;
		}
		goto end_4;
	    }
	    else
		element_count = FIXNUM_ADD1(element_count);
	}
	goto next_loop_4;
      end_loop_4:
	temp = Nil;
	goto end_4;
	temp = Qnil;
      end_4:;
    }
    return VALUES_1(temp);
}

/* NTH-FROM-END-G2-LIST-ELEMENT */
Object nth_from_end_g2_list_element(nth_1,g2_list,element_type_qm,
	    return_element_structure_qm)
    Object nth_1, g2_list, element_type_qm, return_element_structure_qm;
{
    Object g2_list_structure, list_1, next_list_element, element;
    Object element_value, element_count, ab_loop_iter_flag_, temp;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(143,54);
    if (g2_list_empty_p(g2_list))
	return VALUES_1(Nil);
    if ( !TRUEP(element_type_qm)) {
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	list_1 = g2_list_structure;
	next_list_element = Nil;
	element = Nil;
	element_value = Nil;
	element_count = FIX((SI_Long)0L);
	ab_loop_iter_flag_ = T;
	next_list_element = g2_list_structure_previous(ISVREF(list_1,
		(SI_Long)3L),list_1);
      next_loop:
	if ( !TRUEP(next_list_element))
	    goto end_loop;
	element = next_list_element;
	next_list_element = g2_list_structure_previous(next_list_element,
		list_1);
	element_value = ISVREF(element,(SI_Long)4L);
	if ( !TRUEP(ab_loop_iter_flag_))
	    element_count = FIXNUM_ADD1(element_count);
	if (FIXNUM_EQ(element_count,nth_1)) {
	    if (return_element_structure_qm)
		temp = element;
	    else {
		gensymed_symbol = element_value;
		temp_1 = FIXNUMP(gensymed_symbol);
		if (temp_1);
		else
		    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp_1);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp_1 = EQ(gensymed_symbol,Qtruth_value);
		    if (temp_1);
		    else
			temp_1 = EQ(gensymed_symbol,Qiteration_state);
		    if (temp_1);
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
		      next_loop_1:
			if (level < ab_loop_bind_)
			    goto end_loop_1;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_2:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
		      next_loop_3:
			if ( !TRUEP(marked))
			    goto end_loop_2;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
			goto next_loop_3;
		      end_loop_2:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? (FIXNUMP(element_value) || element_value 
			&& SYMBOLP(element_value) ? element_value : 
			copy_evaluation_value_1(element_value)) : 
			element_value;
	    }
	    goto end_2;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	temp = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else {
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	list_1 = g2_list_structure;
	next_list_element = Nil;
	element = Nil;
	element_value = Nil;
	element_count = FIX((SI_Long)0L);
	next_list_element = g2_list_structure_previous(ISVREF(list_1,
		(SI_Long)3L),list_1);
      next_loop_4:
	if ( !TRUEP(next_list_element))
	    goto end_loop_4;
	element = next_list_element;
	next_list_element = g2_list_structure_previous(next_list_element,
		list_1);
	element_value = ISVREF(element,(SI_Long)4L);
	if (g2_list_or_array_element_ok_p(element_value,element_type_qm)) {
	    if (FIXNUM_EQ(element_count,nth_1)) {
		if (return_element_structure_qm)
		    temp = element;
		else {
		    gensymed_symbol = element_value;
		    temp_1 = FIXNUMP(gensymed_symbol);
		    if (temp_1);
		    else
			temp_1 = 
				INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
				!= (SI_Long)0L ? 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				== (SI_Long)1L : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
				(SI_Long)0L ? 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				== (SI_Long)1L : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = gensymed_symbol ? 
				SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = 
				INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
				!= (SI_Long)0L;
		    if (temp_1);
		    else if (CONSP(gensymed_symbol)) {
			gensymed_symbol = M_CDR(gensymed_symbol);
			temp_1 = EQ(gensymed_symbol,Qtruth_value);
			if (temp_1);
			else
			    temp_1 = EQ(gensymed_symbol,Qiteration_state);
			if (temp_1);
			else if (SYMBOLP(gensymed_symbol)) {
			    skip_list = CDR(Defined_evaluation_value_types);
			    key_value = gensymed_symbol;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(gensymed_symbol) & 
				    IFIX(Most_positive_fixnum);
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_6:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_2 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_2,temp);
			    MVS_2(result,succ,marked);
			  next_loop_7:
			    if ( !TRUEP(marked))
				goto end_loop_6;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_2 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_2,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_7;
			  end_loop_6:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				    key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				    TRUEP(Nil)) : TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp = temp_1 ? (FIXNUMP(element_value) || 
			    element_value && SYMBOLP(element_value) ? 
			    element_value : 
			    copy_evaluation_value_1(element_value)) : 
			    element_value;
		}
		goto end_4;
	    }
	    else
		element_count = FIXNUM_ADD1(element_count);
	}
	goto next_loop_4;
      end_loop_4:
	temp = Nil;
	goto end_4;
	temp = Qnil;
      end_4:;
    }
    return VALUES_1(temp);
}

/* G2-LIST-INSERT-AT-BEGINNING */
Object g2_list_insert_at_beginning(item_or_evaluation_value,g2_list)
    Object item_or_evaluation_value, g2_list;
{
    Object success_qm, new_element_structure, x2;
    char temp;

    x_note_fn_call(143,55);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(g2_list);
    success_qm = Nil;
    new_element_structure = Nil;
    if ( !( !TRUEP(ISVREF(g2_list,(SI_Long)22L)) && 
	    g2_list_member_p(item_or_evaluation_value,g2_list))) {
	success_qm = T;
	new_element_structure = g2_list_structure_push_left(ISVREF(g2_list,
		(SI_Long)20L),item_or_evaluation_value,g2_list);
	atomic_incff_svslot(g2_list,FIX((SI_Long)24L),FIX((SI_Long)1L));
	update_representations_of_slot_value(2,g2_list,Qlist_size);
	if (SIMPLE_VECTOR_P(item_or_evaluation_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item_or_evaluation_value,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_evaluation_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    add_to_list_elements_for_item(item_or_evaluation_value,
		    new_element_structure);
    }
    return VALUES_1(success_qm);
}

static Object string_constant_1;   /* "~NF is not initialized yet -- start G2 first" */

/* G2-LIST-INSERT-AT-END */
Object g2_list_insert_at_end varargs_1(int, n)
{
    Object item_or_evaluation_value, g2_list;
    Object override_any_test_for_duplicates_p_qm, success_qm;
    Object new_element_structure, top_of_stack, message_1, x2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(143,56);
    INIT_ARGS_nonrelocating();
    item_or_evaluation_value = REQUIRED_ARG_nonrelocating();
    g2_list = REQUIRED_ARG_nonrelocating();
    override_any_test_for_duplicates_p_qm = OPTIONAL_ARG_P_nonrelocating() 
	    ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(g2_list);
    success_qm = Nil;
    new_element_structure = Nil;
    if ( !TRUEP(ISVREF(g2_list,(SI_Long)20L))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_1,
		g2_list);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !( !TRUEP(override_any_test_for_duplicates_p_qm) &&  
	    !TRUEP(ISVREF(g2_list,(SI_Long)22L)) && 
	    g2_list_member_p(item_or_evaluation_value,g2_list))) {
	success_qm = T;
	new_element_structure = 
		g2_list_structure_push_right(ISVREF(g2_list,(SI_Long)20L),
		item_or_evaluation_value,g2_list);
	atomic_incff_svslot(g2_list,FIX((SI_Long)24L),FIX((SI_Long)1L));
	update_representations_of_slot_value(2,g2_list,Qlist_size);
	if (SIMPLE_VECTOR_P(item_or_evaluation_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item_or_evaluation_value,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_evaluation_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    add_to_list_elements_for_item(item_or_evaluation_value,
		    new_element_structure);
    }
    return VALUES_1(success_qm);
}

/* G2-LIST-STRUCTURE-INSERT-ELEMENT-BEFORE */
Object g2_list_structure_insert_element_before(thing,cursor,outer_list)
    Object thing, cursor, outer_list;
{
    Object g2_list_structure, node, backoff_limit, reference, reference_1;
    Object temp, node_1, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object prev, svref_new_value, temp_1, next;
    Declare_special(1);

    x_note_fn_call(143,57);
    g2_list_structure = ISVREF(outer_list,(SI_Long)20L);
    if (EQ(cursor,ISVREF(g2_list_structure,(SI_Long)2L)))
	return g2_list_structure_insert_element_after(thing,cursor,outer_list);
    node = create_list_element(thing,outer_list);
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop:
      if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L)))
	  cursor = g2_list_structure_next(cursor,g2_list_structure);
      reference = ISVREF(cursor,(SI_Long)3L);
      reference_1 = reference;
      temp = ATOMIC_REF_OBJECT(reference_1);
      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
      node_1 = temp;
      gensymed_symbol = Nil;
    next_loop_1:
      gensymed_symbol = node_1;
      if ( !TRUEP(gensymed_symbol))
	  goto end_1;
    next_loop_2:
      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	  goto end_2;
      goto next_loop_2;
    end_loop:
    end_2:
      if (EQ(gensymed_symbol,node_1))
	  goto end_1;
      else
	  release_list_node(gensymed_symbol);
      goto next_loop_1;
    end_loop_1:
    end_1:;
      prev = node_1;
      svref_new_value = MAKE_ATOMIC_REF(prev,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
      svref_new_value = MAKE_ATOMIC_REF(cursor,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
      temp = prev;
      temp_1 = MAKE_ATOMIC_REF(cursor,(SI_Long)0L);
      if (CAS_SVREF(temp,(SI_Long)2L,temp_1,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	  gensymed_symbol = Nil;
	next_loop_3:
	  gensymed_symbol = node;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_3;
	next_loop_4:
	  gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	      goto end_4;
	  goto next_loop_4;
	end_loop_2:
	end_4:
	  if (EQ(gensymed_symbol,node))
	      goto end_3;
	  else
	      release_list_node(gensymed_symbol);
	  goto next_loop_3;
	end_loop_3:
	end_3:;
	  goto end_loop_4;
      }
      temp = ISVREF(prev,(SI_Long)2L);
      if ( !EQ(temp,MAKE_ATOMIC_REF(cursor,(SI_Long)0L)))
	  prev = help_insert_list_node(prev,cursor);
      release_list_node(prev);
      back_off();
      goto next_loop;
    end_loop_4:
      next = cursor;
      node = help_insert_list_node(node,next);
      release_list_node(node);
      temp = node;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* G2-LIST-STRUCTURE-INSERT-ELEMENT-AFTER */
Object g2_list_structure_insert_element_after(thing,cursor,outer_list)
    Object thing, cursor, outer_list;
{
    Object g2_list_structure, node, next, backoff_limit, reference;
    Object reference_1, temp, node_1, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(143,58);
    g2_list_structure = ISVREF(outer_list,(SI_Long)20L);
    if (EQ(cursor,ISVREF(g2_list_structure,(SI_Long)2L))) {
	result = g2_list_structure_insert_element_before(thing,cursor,
		outer_list);
	goto end_g2_list_structure_insert_element_after;
    }
    node = create_list_element(thing,outer_list);
    next = Nil;
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop:
      reference = ISVREF(cursor,(SI_Long)2L);
      reference_1 = reference;
      temp = ATOMIC_REF_OBJECT(reference_1);
      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
      node_1 = temp;
      gensymed_symbol = Nil;
    next_loop_1:
      gensymed_symbol = node_1;
      if ( !TRUEP(gensymed_symbol))
	  goto end_1;
    next_loop_2:
      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	  goto end_2;
      goto next_loop_2;
    end_loop:
    end_2:
      if (EQ(gensymed_symbol,node_1))
	  goto end_1;
      else
	  release_list_node(gensymed_symbol);
      goto next_loop_1;
    end_loop_1:
    end_1:;
      next = node_1;
      svref_new_value = MAKE_ATOMIC_REF(cursor,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
      svref_new_value = MAKE_ATOMIC_REF(next,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
      temp = MAKE_ATOMIC_REF(next,(SI_Long)0L);
      if (CAS_SVREF(cursor,(SI_Long)2L,temp,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	  gensymed_symbol = Nil;
	next_loop_3:
	  gensymed_symbol = node;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_3;
	next_loop_4:
	  gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	      goto end_4;
	  goto next_loop_4;
	end_loop_2:
	end_4:
	  if (EQ(gensymed_symbol,node))
	      goto end_3;
	  else
	      release_list_node(gensymed_symbol);
	  goto next_loop_3;
	end_loop_3:
	end_3:;
	  goto end_loop_4;
      }
      release_list_node(next);
      if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L))) {
	  release_list_node(node);
	  result = g2_list_structure_insert_element_before(thing,cursor,
		  outer_list);
	  POP_SPECIAL();
	  goto end_g2_list_structure_insert_element_after;
      }
      back_off();
      goto next_loop;
    end_loop_4:
      gensymed_symbol = Nil;
    next_loop_5:
      gensymed_symbol = cursor;
      if ( !TRUEP(gensymed_symbol))
	  goto end_5;
    next_loop_6:
      gensymed_symbol_1 = ISVREF(cursor,(SI_Long)1L);
      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
      if (CAS_SVREF(cursor,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	  goto end_6;
      goto next_loop_6;
    end_loop_5:
    end_6:
      if (EQ(gensymed_symbol,cursor))
	  goto end_5;
      else
	  release_list_node(gensymed_symbol);
      goto next_loop_5;
    end_loop_6:
    end_5:;
      node = help_insert_list_node(node,next);
      release_list_node(node);
      release_list_node(next);
      temp = node;
    POP_SPECIAL();
    result = VALUES_1(temp);
  end_g2_list_structure_insert_element_after:
    return result;
}

/* G2-LIST-INSERT-BEFORE */
Object g2_list_insert_before(item_or_evaluation_value,
	    before_item_or_evaluation_value,g2_list,before_item_is_an_index_qm)
    Object item_or_evaluation_value, before_item_or_evaluation_value, g2_list;
    Object before_item_is_an_index_qm;
{
    Object before_element_structure_qm, new_element_structure, success_flag;
    Object x2;
    char temp;

    x_note_fn_call(143,59);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(g2_list);
    before_element_structure_qm = before_item_is_an_index_qm ? 
	    find_g2_list_element_structure_at_position(g2_list,
	    before_item_or_evaluation_value) : 
	    find_g2_list_element_structure(before_item_or_evaluation_value,
	    g2_list,Nil,Nil);
    new_element_structure = Nil;
    success_flag = FIX((SI_Long)1L);
    if ( !TRUEP(before_element_structure_qm))
	success_flag = FIX((SI_Long)-1L);
    else if ( !TRUEP(ISVREF(g2_list,(SI_Long)22L)) && 
	    g2_list_member_p(item_or_evaluation_value,g2_list))
	success_flag = FIX((SI_Long)-2L);
    else {
	new_element_structure = 
		g2_list_structure_insert_element_before(item_or_evaluation_value,
		before_element_structure_qm,g2_list);
	atomic_incff_svslot(g2_list,FIX((SI_Long)24L),FIX((SI_Long)1L));
	update_representations_of_slot_value(2,g2_list,Qlist_size);
	if (SIMPLE_VECTOR_P(item_or_evaluation_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item_or_evaluation_value,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_evaluation_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    add_to_list_elements_for_item(item_or_evaluation_value,
		    new_element_structure);
    }
    return VALUES_1(success_flag);
}

/* G2-LIST-INSERT-AFTER */
Object g2_list_insert_after(item_or_evaluation_value,
	    after_item_or_evaluation_value,g2_list,after_item_is_an_index_qm)
    Object item_or_evaluation_value, after_item_or_evaluation_value, g2_list;
    Object after_item_is_an_index_qm;
{
    Object after_element_structure_qm, new_element_structure, success_flag;
    Object svref_new_value, x2;
    char temp;

    x_note_fn_call(143,60);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(g2_list);
    after_element_structure_qm = after_item_is_an_index_qm ? 
	    find_g2_list_element_structure_at_position(g2_list,
	    after_item_or_evaluation_value) : 
	    find_g2_list_element_structure(after_item_or_evaluation_value,
	    g2_list,Nil,Nil);
    new_element_structure = Nil;
    success_flag = FIX((SI_Long)1L);
    if ( !TRUEP(after_element_structure_qm))
	success_flag = FIX((SI_Long)-1L);
    else if ( !TRUEP(ISVREF(g2_list,(SI_Long)22L)) && 
	    g2_list_member_p(item_or_evaluation_value,g2_list))
	success_flag = FIX((SI_Long)-2L);
    else {
	new_element_structure = 
		g2_list_structure_insert_element_after(item_or_evaluation_value,
		after_element_structure_qm,g2_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(g2_list,(SI_Long)24L));
	ISVREF(g2_list,(SI_Long)24L) = svref_new_value;
	update_representations_of_slot_value(2,g2_list,Qlist_size);
	if (SIMPLE_VECTOR_P(item_or_evaluation_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item_or_evaluation_value,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_evaluation_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    add_to_list_elements_for_item(item_or_evaluation_value,
		    new_element_structure);
    }
    return VALUES_1(success_flag);
}

/* REMOVE-G2-LIST-ELEMENT-STRUCTURE */
Object remove_g2_list_element_structure(element_structure,g2_list,
	    update_list_elements_for_item_qm,
	    note_runtime_change_for_g2_list_qm,
	    reclaim_element_value_if_necessary_qm)
    Object element_structure, g2_list, update_list_elements_for_item_qm;
    Object note_runtime_change_for_g2_list_qm;
    Object reclaim_element_value_if_necessary_qm;
{
    Object list_structure, continuation, ab_loop_list_, list_next_element_qm;
    Object second_new_value, element_value, x2, thing;
    char temp;

    x_note_fn_call(143,61);
    list_structure = ISVREF(g2_list,(SI_Long)20L);
    continuation = Nil;
    ab_loop_list_ = ISVREF(g2_list,(SI_Long)23L);
    list_next_element_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    continuation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    list_next_element_qm = g2_list_structure_next(element_structure,
	    list_structure);
    if (EQ(element_structure,SECOND(continuation))) {
	second_new_value =  !TRUEP(list_next_element_qm) ? 
		eval_cons_1(g2_list,Nil) : list_next_element_qm;
	M_SECOND(continuation) = second_new_value;
    }
    goto next_loop;
  end_loop:;
    element_value = ISVREF(element_structure,(SI_Long)4L);
    if (update_list_elements_for_item_qm) {
	if (SIMPLE_VECTOR_P(element_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(element_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(element_value,(SI_Long)1L);
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
	delete_from_list_elements_for_item(2,element_value,element_structure);
    if (reclaim_element_value_if_necessary_qm) {
	thing = ISVREF(element_structure,(SI_Long)4L);
	if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	    reclaim_if_evaluation_value_1(thing);
	g2_list_structure_delete(1,element_structure);
    }
    else
	g2_list_structure_delete(1,element_structure);
    atomic_incff_svslot(g2_list,FIX((SI_Long)24L),FIX( - (SI_Long)1L));
    update_representations_of_slot_value(2,g2_list,Qlist_size);
    if (note_runtime_change_for_g2_list_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(g2_list);
    }
    return VALUES_1(Nil);
}

static Object Qelement_position;   /* element-position */

/* G2-LIST-REMOVE */
Object g2_list_remove(item_or_evaluation_value,element_qm,g2_list)
    Object item_or_evaluation_value, element_qm, g2_list;
{
    Object element_structure_qm, element_found_qm;

    x_note_fn_call(143,62);
    element_structure_qm = Nil;
    element_found_qm = Nil;
    if ( !TRUEP(g2_list_empty_p(g2_list))) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(item_or_evaluation_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value)) 
		== (SI_Long)1L && 
		exceptional_float_p(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(item_or_evaluation_value,
		(SI_Long)0L))))
	    element_structure_qm = 
		    find_exceptional_float_in_g2_list(item_or_evaluation_value,
		    g2_list);
	else if (EQ(element_qm,Qelement_position))
	    element_structure_qm = 
		    find_g2_list_element_structure_at_position(g2_list,
		    item_or_evaluation_value);
	else if (element_qm)
	    element_structure_qm = 
		    find_g2_list_element_structure(item_or_evaluation_value,
		    g2_list,Nil,Nil);
	else
	    element_structure_qm = 
		    find_g2_list_element_structure(item_or_evaluation_value,
		    g2_list,Nil,Nil);
    }
    element_found_qm =  ! !TRUEP(element_structure_qm) ? T : Nil;
    if (element_found_qm)
	remove_g2_list_element_structure(element_structure_qm,g2_list,T,T,T);
    return VALUES_1(element_found_qm);
}

/* G2-LIST-REMOVE-FIRST */
Object g2_list_remove_first varargs_1(int, n)
{
    Object g2_list;
    Object required_element_type_qm, element_structure_qm;
    char element_found_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(143,63);
    INIT_ARGS_nonrelocating();
    g2_list = REQUIRED_ARG_nonrelocating();
    required_element_type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    element_structure_qm =  !TRUEP(g2_list_empty_p(g2_list)) ? 
	    g2_list_first(g2_list,required_element_type_qm,T) : Qnil;
    element_found_qm =  ! !TRUEP(element_structure_qm);
    if (element_found_qm)
	remove_g2_list_element_structure(element_structure_qm,g2_list,T,T,T);
    return VALUES_1(element_found_qm ? T : Nil);
}

/* POP-G2-LIST */
Object pop_g2_list(g2_list)
    Object g2_list;
{
    Object element_structure_qm, element_value_qm;

    x_note_fn_call(143,64);
    element_structure_qm =  !TRUEP(g2_list_empty_p(g2_list)) ? 
	    g2_list_first(g2_list,Nil,T) : Qnil;
    element_value_qm = element_structure_qm ? ISVREF(element_structure_qm,
	    (SI_Long)4L) : Qnil;
    if (element_value_qm)
	remove_g2_list_element_structure(element_structure_qm,g2_list,T,T,Nil);
    return VALUES_1(element_value_qm);
}

/* G2-LIST-REMOVE-LAST */
Object g2_list_remove_last varargs_1(int, n)
{
    Object g2_list;
    Object required_element_type_qm, element_structure_qm;
    char element_found_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(143,65);
    INIT_ARGS_nonrelocating();
    g2_list = REQUIRED_ARG_nonrelocating();
    required_element_type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    element_structure_qm =  !TRUEP(g2_list_empty_p(g2_list)) ? 
	    g2_list_last(g2_list,required_element_type_qm,T) : Qnil;
    element_found_qm =  ! !TRUEP(element_structure_qm);
    if (element_found_qm)
	remove_g2_list_element_structure(element_structure_qm,g2_list,T,T,T);
    return VALUES_1(element_found_qm ? T : Nil);
}

/* REMOVE-ELEMENT-FROM-ALL-G2-LISTS */
Object remove_element_from_all_g2_lists(item,deactivating_item_qm)
    Object item, deactivating_item_qm;
{
    Object x2, element_list, element_structure, ab_loop_list_, g2_list, temp_1;
    char temp;

    x_note_fn_call(143,66);
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
    if (temp) {
	element_list = ISVREF(item,(SI_Long)13L);
	element_structure = Nil;
	ab_loop_list_ = element_list;
	g2_list = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2_list = ISVREF(element_structure,(SI_Long)5L);
	if ( !(deactivating_item_qm && (Warmbooting_qm || 
		get_lookup_slot_value(g2_list,Qlist_is_permanent))))
	    remove_g2_list_element_structure(element_structure,g2_list,T,T,T);
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* VALIDATE-ALL-ITEM-LISTS */
Object validate_all_item_lists(class_qm,old_class_qm)
    Object class_qm, old_class_qm;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item_list;
    Object list_element_type, gensymed_symbol;
    char temp;
    Declare_special(1);

    x_note_fn_call(143,67);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item_list = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      list_element_type = Nil;
      ab_loopvar_ = collect_subclasses(Qitem_list);
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
      item_list = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      list_element_type = ISVREF(item_list,(SI_Long)21L);
      if ( !EQ(list_element_type,Qitem)) {
	  temp =  !TRUEP(class_qm) ?  !TRUEP(old_class_qm) : TRUEP(Qnil);
	  if (temp);
	  else if (class_qm) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(list_element_type,
		      Class_description_gkbprop);
	      temp = gensymed_symbol ? TRUEP(memq_function(class_qm,
		      ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else if (old_class_qm) {
	      temp = EQ(list_element_type,old_class_qm);
	      if (temp);
	      else {
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(list_element_type,
			  Class_description_gkbprop);
		  temp = gensymed_symbol ? 
			  TRUEP(memq_function(old_class_qm,
			  ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	      }
	  }
	  else
	      temp = TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  validate_and_fix_g2_item_list_elements(item_list);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* VALIDATE-AND-FIX-G2-ITEM-LIST-ELEMENTS */
Object validate_and_fix_g2_item_list_elements(item_list)
    Object item_list;
{
    Object list_element_type, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, ab_loopvar_;
    Object ab_loopvar__1, item_element, removal_list_qm, item_to_remove;
    Object ab_loop_list_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(143,68);
    list_element_type = ISVREF(item_list,(SI_Long)21L);
    if ( !EQ(list_element_type,Qitem)) {
	if (SYMBOLP(list_element_type)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = list_element_type;
	    key_hash_value = SXHASH_SYMBOL_1(list_element_type) & 
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
		gensymed_symbol = list_element_type;
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
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
	if ( !temp_2)
	    clear_g2_list(item_list);
	else {
	    ab_loopvar_ = ISVREF(item_list,(SI_Long)20L);
	    ab_loopvar__1 = Nil;
	    item_element = Nil;
	    removal_list_qm = Nil;
	    ab_loopvar__1 = ab_loopvar_ ? 
		    g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		    ab_loopvar_) : Nil;
	  next_loop_12:
	    if ( !TRUEP(ab_loopvar__1))
		goto end_loop_12;
	    item_element = ISVREF(ab_loopvar__1,(SI_Long)4L);
	    ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	    if ( !TRUEP(item_ok_for_g2_list_or_array_p(item_element,
		    list_element_type)))
		removal_list_qm =  !TRUEP(removal_list_qm) ? 
			g2_list_cons_1(item_element,Nil) : 
			g2_list_cons_1(item_element,removal_list_qm);
	    goto next_loop_12;
	  end_loop_12:
	    item_to_remove = Nil;
	    ab_loop_list_ = removal_list_qm;
	  next_loop_13:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_13;
	    item_to_remove = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    g2_list_remove(item_to_remove,Nil,item_list);
	    goto next_loop_13;
	  end_loop_13:;
	    if (removal_list_qm)
		reclaim_g2_list_list_1(removal_list_qm);
	}
    }
    return VALUES_1(Nil);
}

/* REMOVE-G2-LIST-DUPLICATE-ELEMENTS */
Object remove_g2_list_duplicate_elements(g2_list)
    Object g2_list;
{
    Object element_type, item_element_type_qm, g2_list_structure;
    Object element_structure, next_element_structure, element_value;
    Object remove_element_qm, x2, element_structure_for_item, ab_loop_list_;
    Object duplicate_element_structure_qm;
    char item_or_value_element_type_qm, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(143,69);
    if ( !TRUEP(g2_list_empty_p(g2_list))) {
	element_type = ISVREF(g2_list,(SI_Long)21L);
	item_or_value_element_type_qm = EQ(element_type,Qitem_or_datum);
	item_element_type_qm = 
		g2_list_or_array_element_type_may_contain_item_p(element_type) 
		? ( !item_or_value_element_type_qm ? T : Nil) : Qnil;
	g2_list_structure = ISVREF(g2_list,(SI_Long)20L);
	element_structure = 
		g2_list_structure_next(ISVREF(g2_list_structure,
		(SI_Long)2L),g2_list_structure);
	next_element_structure = Nil;
	element_value = Nil;
	remove_element_qm = Nil;
      next_loop:
	next_element_structure = g2_list_structure_next(element_structure,
		g2_list_structure);
	element_value = ISVREF(element_structure,(SI_Long)4L);
	remove_element_qm = Nil;
	if ( !TRUEP(next_element_structure))
	    goto end_loop;
	temp = TRUEP(item_element_type_qm);
	if (temp);
	else if (item_or_value_element_type_qm) {
	    if (SIMPLE_VECTOR_P(element_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(element_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(element_value,(SI_Long)1L);
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
	    element_structure_for_item = Nil;
	    ab_loop_list_ = ISVREF(element_value,(SI_Long)13L);
	    duplicate_element_structure_qm = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    element_structure_for_item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    duplicate_element_structure_qm =  
		    !EQ(element_structure_for_item,element_structure) && 
		    EQ(ISVREF(element_structure_for_item,(SI_Long)5L),
		    g2_list) ? element_structure_for_item : Nil;
	    if (duplicate_element_structure_qm)
		goto end_loop_1;
	    goto next_loop_1;
	  end_loop_1:
	    remove_element_qm = duplicate_element_structure_qm;
	    goto end_1;
	    remove_element_qm = Qnil;
	  end_1:;
	}
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		remove_element_qm = 
			find_g2_list_element_structure(element_value,
			g2_list,next_element_structure,Nil);
	    POP_LOCAL_ALLOCATION(0,0);
	}
	if (remove_element_qm)
	    remove_g2_list_element_structure(element_structure,g2_list,T,T,T);
	element_structure = next_element_structure;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* READ-G2-LIST-OR-ARRAY-ELEMENT-FOR-KB */
Object read_g2_list_or_array_element_for_kb(element_type,g2_array_p_qm)
    Object element_type, g2_array_p_qm;
{
    Object temp, gensymed_symbol;

    x_note_fn_call(143,70);
    if ( !EQ(element_type,Qtruth_value))
	temp = read_element_for_kb(Nil);
    else if (g2_array_p_qm)
	temp = read_element_for_kb(Nil);
    else {
	gensymed_symbol = read_element_for_kb(Nil);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    temp = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    temp = Evaluation_false_value;
	else
	    temp = eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    return VALUES_1(temp);
}

/* WRITE-G2-LIST-OR-ARRAY-ELEMENT-FOR-KB */
Object write_g2_list_or_array_element_for_kb(element,element_type)
    Object element, element_type;
{
    Object x2;
    char temp;

    x_note_fn_call(143,71);
    if (SIMPLE_VECTOR_P(element) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L &&  
	    !EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(element,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if ((SI_Long)0L != (IFIX(ISVREF(element,(SI_Long)4L)) & 
		(SI_Long)1L) || ISVREF(Current_saving_context,(SI_Long)3L) 
		&& (SI_Long)0L != (IFIX(ISVREF(element,(SI_Long)5L)) & 
		(SI_Long)262144L))
	    write_element_for_kb(element);
	else
	    write_element_for_kb(Nil);
    }
    else if (CONSP(element) && EQ(M_CDR(element),Qtruth_value) && 
	    EQ(element_type,Qtruth_value))
	write_element_for_kb(M_CAR(element));
    else
	write_evaluation_value_for_kb(element);
    return VALUES_1(Nil);
}

/* WRITE-G2-LIST-DATA-FOR-KB */
Object write_g2_list_data_for_kb(g2_list)
    Object g2_list;
{
    Object list_length_1, element_type, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, element_value, temp;

    x_note_fn_call(143,72);
    if ((SI_Long)0L != (IFIX(ISVREF(g2_list,(SI_Long)5L)) & (SI_Long)1L)) {
	list_length_1 = g2_list_length(g2_list);
	element_type = g2_list_or_array_element_type(g2_list);
	if (IFIX(list_length_1) > (SI_Long)0L) {
	    if ( !TRUEP(Left_braket_written_qm)) {
		write_char_for_kb(CHR('['));
		Left_braket_written_qm = T;
	    }
	    write_char_for_kb(CHR('L'));
	    write_fixnum_for_kb(list_length_1);
	    gensymed_symbol = g2_list;
	    ab_loopvar_ = ISVREF(gensymed_symbol,(SI_Long)20L);
	    ab_loopvar__1 = Nil;
	    element_value = Nil;
	    ab_loopvar__1 = ab_loopvar_ ? 
		    g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		    ab_loopvar_) : Nil;
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1))
		goto end_loop;
	    element_value = ISVREF(ab_loopvar__1,(SI_Long)4L);
	    ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	    write_g2_list_or_array_element_for_kb(element_value,element_type);
	    goto next_loop;
	  end_loop:
	    temp = Nil;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* READ-LIST-DATA */
Object read_list_data(g2_list)
    Object g2_list;
{
    Object squirreled_list, element_type, temp;
    SI_Long ab_loop_repeat_;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(143,73);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	squirreled_list = Nil;
	element_type = g2_list_or_array_element_type(g2_list);
	ab_loop_repeat_ = IFIX(read_element_for_kb(Nil));
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	temp = read_g2_list_or_array_element_for_kb(element_type,Nil);
	squirreled_list = gensym_cons_1(temp,squirreled_list);
	goto next_loop;
      end_loop:
	temp = squirreled_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* UNSQUIRREL-LIST-DATA */
Object unsquirrel_list_data(g2_list,squirreled_list)
    Object g2_list, squirreled_list;
{
    Object item_or_evaluation_value, ab_loop_list_, temp;

    x_note_fn_call(143,74);
    item_or_evaluation_value = Nil;
    ab_loop_list_ = squirreled_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item_or_evaluation_value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_list_insert_at_beginning(SIMPLE_VECTOR_P(item_or_evaluation_value) 
	    && EQ(ISVREF(item_or_evaluation_value,(SI_Long)1L),
	    Qavailable_frame_vector) ? Nil : item_or_evaluation_value,g2_list);
    goto next_loop;
  end_loop:;
    temp = reclaim_gensym_list_1(squirreled_list);
    return VALUES_1(temp);
}

/* REVERSE-LIST-USING-DRAGGING-CONSES */
Object reverse_list_using_dragging_conses(list_1)
    Object list_1;
{
    Object reversed_list, l;

    x_note_fn_call(143,75);
    reversed_list = Nil;
    l = list_1;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    reversed_list = dragging_cons_1(CAR(l),reversed_list);
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(reversed_list);
    return VALUES_1(Qnil);
}

static Object string_constant_2;   /* "Cannot transfer items to the mouse of ~NF: it's not a connected G2-window instance!" */

static Object string_constant_3;   /* "Cannot transfer items to non-KB workspaces!" */

static Object string_constant_4;   /* "Cannot transfer items to proprietary workspaces!" */

static Object string_constant_5;   /* "Objects are not transferrable" */

static Object Qparent_frame;       /* parent-frame */

static Object string_constant_6;   /* "Cannot transfer ~NF because it is an attribute of ~NF." */

static Object string_constant_7;   /* "Cannot transfer ~NF because it is a kb-workspace.  The make ~
				    *                   subworkspace action can be used to give a transient ~
				    *                   kb-workspace a new superior object."
				    */

static Object string_constant_8;   /* "Cannot transfer ~NF because it is a ~a." */

static Object string_constant_9;   /* "Cannot transfer ~NF to the workspace ~NF because ~NF is superior to ~
				    *           this workspace."
				    */

static Object string_constant_10;  /* "Cannot transfer ~NF to the workspace ~NF.  ~NF is a dependent item ~
				    *                          containing a compiled attribute and ~NF is not dependent."
				    */

/* PREFLIGHT-CHECK-DRAGGING-LIST-OF-BLOCKS-FOR-TRANSFER */
Object preflight_check_dragging_list_of_blocks_for_transfer varargs_1(int, n)
{
    Object objects_being_transferred, to_workspace_qm;
    Object g2_window_for_mouse_qm, sub_class_bit_vector, top_of_stack;
    Object message_1, block, ab_loop_list_, invalid_item_for_transfer_qm;
    Object temp_1, x2, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(143,76);
    INIT_ARGS_nonrelocating();
    objects_being_transferred = REQUIRED_ARG_nonrelocating();
    to_workspace_qm = REQUIRED_ARG_nonrelocating();
    g2_window_for_mouse_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (g2_window_for_mouse_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(g2_window_for_mouse_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	if (temp);
	else
	    temp =  !TRUEP(ISVREF(g2_window_for_mouse_qm,(SI_Long)20L));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	reclaim_dragging_list_1(objects_being_transferred);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_2,
		g2_window_for_mouse_qm);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	if (to_workspace_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(to_workspace_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Non_kb_workspace_class_description,
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
	    reclaim_dragging_list_1(objects_being_transferred);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_3);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if (to_workspace_qm && in_order_p(to_workspace_qm) &&  
		!EQ(get_workspace_if_any(CAR(objects_being_transferred)),
		to_workspace_qm)) {
	    reclaim_dragging_list_1(objects_being_transferred);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_4);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if ( !TRUEP(blocks_transferable_p(objects_being_transferred))) {
	    reclaim_dragging_list_1(objects_being_transferred);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_5);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    block = Nil;
    ab_loop_list_ = objects_being_transferred;
    invalid_item_for_transfer_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = TRUEP(get_lookup_slot_value_given_default(block,Qparent_frame,Nil));
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
    invalid_item_for_transfer_qm =  ! !temp ? T : Nil;
    if (invalid_item_for_transfer_qm) {
	if (get_lookup_slot_value_given_default(block,Qparent_frame,Nil)) {
	    reclaim_dragging_list_1(objects_being_transferred);
	    top_of_stack = Cached_top_of_stack;
	    temp_1 = block;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_6,temp_1,
		    get_lookup_slot_value_given_default(block,
		    Qparent_frame,Nil));
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    if (SIMPLE_VECTOR_P(block) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(block,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(block,(SI_Long)1L);
		gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
			(SI_Long)18L));
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		reclaim_dragging_list_1(objects_being_transferred);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_7,block);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else {
		reclaim_dragging_list_1(objects_being_transferred);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_8,block,ISVREF(ISVREF(block,
			(SI_Long)1L),(SI_Long)1L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	}
    }
    else if (to_workspace_qm && ancestor_p(block,to_workspace_qm)) {
	reclaim_dragging_list_1(objects_being_transferred);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_9,
		block,to_workspace_qm,block);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (to_workspace_qm && block_can_be_dependent_p(block) && 
	    item_currently_contains_compiled_value(block) &&  
	    !TRUEP(block_can_be_dependent_p(to_workspace_qm))) {
	reclaim_dragging_list_1(objects_being_transferred);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_10,
		block,to_workspace_qm,block,to_workspace_qm);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_duplicates_check_hash_table_hash_vector_50021_vectors, Qavailable_duplicates_check_hash_table_hash_vector_50021_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_duplicates_check_hash_table_hash_vector_50021_vectors, Qcount_of_duplicates_check_hash_table_hash_vector_50021_vectors);

Object Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector = UNBOUND;

/* DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR-50021-VECTOR-MEMORY-USAGE */
Object duplicates_check_hash_table_hash_vector_50021_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(143,77);
    temp = Count_of_duplicates_check_hash_table_hash_vector_50021_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)50021L)));
    return VALUES_1(temp);
}

/* OUT-DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR-50021-VECTORS */
Object out_duplicates_check_hash_table_hash_vector_50021_vectors()
{
    Object temp;

    x_note_fn_call(143,78);
    temp = 
	    FIXNUM_MINUS(Count_of_duplicates_check_hash_table_hash_vector_50021_vectors,
	    length(Available_duplicates_check_hash_table_hash_vector_50021_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR-50021-VECTOR-INTERNAL */
Object make_permanent_duplicates_check_hash_table_hash_vector_50021_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(143,79);
    atomic_incff_symval(Qcount_of_duplicates_check_hash_table_hash_vector_50021_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)50021L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR */
Object make_duplicates_check_hash_table_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(143,80);
    if (ISVREF(Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = 
		make_permanent_duplicates_check_hash_table_hash_vector_50021_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR */
Object reclaim_duplicates_check_hash_table_hash_vector(duplicates_check_hash_table_hash_vector_50021_vector)
    Object duplicates_check_hash_table_hash_vector_50021_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(143,81);
    svref_arg_1 = 
	    Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = 
	    duplicates_check_hash_table_hash_vector_50021_vector;
    temp = 
	    ISVREF(Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-DUPLICATES-CHECK-HASH-TABLE-TREE-FOR-HASH-LEAVES */
Object reclaim_duplicates_check_hash_table_tree_for_hash_leaves(duplicates_check_hash_table_tree_for_hash_binary_tree)
    Object duplicates_check_hash_table_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, temp, svref_arg_2, last_1, next_qm, temp_1;

    x_note_fn_call(143,82);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(duplicates_check_hash_table_tree_for_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = 
	    ISVREF(duplicates_check_hash_table_tree_for_hash_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(duplicates_check_hash_table_tree_for_hash_binary_tree,
	    (SI_Long)2L);
    alist = ISVREF(duplicates_check_hash_table_tree_for_hash_binary_tree,
	    (SI_Long)3L);
    reclaim_binary_tree_element_1(duplicates_check_hash_table_tree_for_hash_binary_tree);
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
	reclaim_duplicates_check_hash_table_tree_for_hash_leaves(less_than_branch_qm);
	duplicates_check_hash_table_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp_1 = less_than_branch_qm;
	if (temp_1);
	else
	    temp_1 = greater_than_branch_qm;
	duplicates_check_hash_table_tree_for_hash_binary_tree = temp_1;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-DUPLICATES-CHECK-HASH-TABLE-TREE */
Object clear_duplicates_check_hash_table_tree(duplicates_check_hash_table_tree_for_hash_binary_tree)
    Object duplicates_check_hash_table_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(143,83);
    element_qm = CDR(duplicates_check_hash_table_tree_for_hash_binary_tree);
    if (element_qm) {
	reclaim_duplicates_check_hash_table_tree_for_hash_leaves(element_qm);
	M_CDR(duplicates_check_hash_table_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(duplicates_check_hash_table_tree_for_hash_binary_tree);
}

static Object Qduplicates_check_hash_table_tree_for_hash;  /* duplicates-check-hash-table-tree-for-hash */

/* MAKE-DUPLICATES-CHECK-HASH-TABLE */
Object make_duplicates_check_hash_table()
{
    Object new_vector, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(143,84);
    new_vector = make_duplicates_check_hash_table_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)50021L)
	goto end_loop;
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
    M_CAR(gensymed_symbol) = Qduplicates_check_hash_table_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-DUPLICATES-CHECK-HASH-TABLE */
Object flatten_duplicates_check_hash_table(duplicates_check_hash_table_hash_table)
    Object duplicates_check_hash_table_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(143,85);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)50021L)
	goto end_loop;
    subtree = ISVREF(duplicates_check_hash_table_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-DUPLICATES-CHECK-HASH-TABLE */
Object clear_duplicates_check_hash_table(duplicates_check_hash_table_hash_table)
    Object duplicates_check_hash_table_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(143,86);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)50021L)
	goto end_loop;
    clear_duplicates_check_hash_table_tree(ISVREF(duplicates_check_hash_table_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-DUPLICATES-CHECK-HASH-TABLE */
Object reclaim_duplicates_check_hash_table(duplicates_check_hash_table_hash_table)
    Object duplicates_check_hash_table_hash_table;
{
    Object duplicates_check_hash_table_tree_for_hash_binary_tree, element_qm;
    Object temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(143,87);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)50021L)
	goto end_loop;
    duplicates_check_hash_table_tree_for_hash_binary_tree = 
	    ISVREF(duplicates_check_hash_table_hash_table,index_1);
    element_qm = M_CDR(duplicates_check_hash_table_tree_for_hash_binary_tree);
    if (element_qm)
	reclaim_duplicates_check_hash_table_tree_for_hash_leaves(element_qm);
    inline_note_reclaim_cons(duplicates_check_hash_table_tree_for_hash_binary_tree,
	    Qlookup);
    if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = duplicates_check_hash_table_tree_for_hash_binary_tree;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		duplicates_check_hash_table_tree_for_hash_binary_tree;
    }
    else {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		duplicates_check_hash_table_tree_for_hash_binary_tree;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		duplicates_check_hash_table_tree_for_hash_binary_tree;
    }
    M_CDR(duplicates_check_hash_table_tree_for_hash_binary_tree) = Nil;
    ISVREF(duplicates_check_hash_table_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_duplicates_check_hash_table_hash_vector(duplicates_check_hash_table_hash_table);
    return VALUES_1(temp_1);
}

static Object string_constant_11;  /* "The item list is empty." */

static Object string_constant_12;  /* "All members of the list must be items, ~NF is not an item." */

static Object string_constant_13;  /* "All items in the list must be on a workspace. ~NF is not on one." */

static Object string_constant_14;  /* "All items in the list must be on the same workspace. ~
				    *                     ~NF is not on ~NF."
				    */

/* GET-BLOCKS-VALID-FOR-GROUP-OPERATION */
Object get_blocks_valid_for_group_operation(g2_list_or_sequence)
    Object g2_list_or_sequence;
{
    Object objects_being_collected, from_workspace;
    Object list_contents_sequence_reclaimable_p, list_contents, top_of_stack;
    Object message_1, gensymed_symbol, held_vector, item, workspace_of_item_qm;
    Object elt_1, validated_elt, x2, symbol, property_name, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector;
    SI_Long next_index, length_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, temp_3;
    char temp;
    Object result;

    x_note_fn_call(143,88);
    objects_being_collected = Nil;
    from_workspace = Nil;
    list_contents_sequence_reclaimable_p = Nil;
    list_contents = Nil;
    clear_duplicates_check_hash_table(Duplicates_check_hash);
    if (CONSP(g2_list_or_sequence) && EQ(M_CDR(g2_list_or_sequence),Qsequence))
	list_contents = g2_list_or_sequence;
    else {
	list_contents_sequence_reclaimable_p = T;
	list_contents = get_list_contents_as_sequence(g2_list_or_sequence);
    }
    if (IFIX(FIXNUM_SUB1(ISVREF(M_CAR(list_contents),(SI_Long)1L))) == 
	    (SI_Long)0L) {
	if (list_contents_sequence_reclaimable_p)
	    reclaim_evaluation_value(list_contents);
	if (objects_being_collected)
	    reclaim_dragging_list_1(objects_being_collected);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_11);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    gensymed_symbol = list_contents;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    item = Nil;
    workspace_of_item_qm = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    item = validated_elt;
    workspace_of_item_qm = Nil;
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
    if ( !(temp ? TRUEP(ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)16L)) : 
	    TRUEP(Nil))) {
	if (list_contents_sequence_reclaimable_p)
	    reclaim_evaluation_value(list_contents);
	if (objects_being_collected)
	    reclaim_dragging_list_1(objects_being_collected);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_12,item);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    gensymed_symbol = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    workspace_of_item_qm = gensymed_symbol;
    if ( !TRUEP(workspace_of_item_qm)) {
	if (list_contents_sequence_reclaimable_p)
	    reclaim_evaluation_value(list_contents);
	if (objects_being_collected)
	    reclaim_dragging_list_1(objects_being_collected);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_13,item);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    symbol = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    property_name = Class_description_gkbprop;
    skip_list = CDR(Symbol_properties_table);
    key_value = symbol;
    key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
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
	gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	    temp = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	if (from_workspace) {
	    if ( !EQ(from_workspace,workspace_of_item_qm)) {
		if (list_contents_sequence_reclaimable_p)
		    reclaim_evaluation_value(list_contents);
		if (objects_being_collected)
		    reclaim_dragging_list_1(objects_being_collected);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_14,item,from_workspace);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	}
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    from_workspace = gensymed_symbol;
	}
	gensymed_symbol_3 = IFIX(sxhashw(item));
	temp_2 = Duplicates_check_hash;
	temp_3 = gensymed_symbol_3 % (SI_Long)50021L;
	temp_2 = SVREF(temp_2,FIX(temp_3));
	gensymed_symbol = CDR(temp_2);
	gensymed_symbol_1 = item;
	gensymed_symbol_4 = (SI_Long)0L;
      next_loop_13:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_13;
	gensymed_symbol_4 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_3 < gensymed_symbol_4)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_3 > gensymed_symbol_4)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_2 = Nil;
	  next_loop_14:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_14;
	    gensymed_symbol_2 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQUAL(gensymed_symbol_1,gensymed_symbol_2)) {
		temp = TRUEP(M_CDR(M_CAR(gensymed_symbol)));
		goto end_5;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_14;
	  end_loop_14:
	    temp = TRUEP(Qnil);
	  end_5:;
	    goto end_6;
	}
	goto next_loop_13;
      end_loop_13:
	temp = TRUEP(Qnil);
      end_6:;
	if ( !temp) {
	    gensymed_symbol_3 = IFIX(sxhashw(item));
	    temp_2 = Duplicates_check_hash;
	    temp_3 = gensymed_symbol_3 % (SI_Long)50021L;
	    set_balanced_binary_tree_entry(SVREF(temp_2,FIX(temp_3)),
		    Qequal,Nil,T,item,FIX(gensymed_symbol_3),T);
	    objects_being_collected = dragging_cons_1(item,
		    objects_being_collected);
	}
    }
    goto next_loop;
  end_loop:;
    if (list_contents_sequence_reclaimable_p)
	reclaim_evaluation_value(list_contents);
    return VALUES_2(objects_being_collected,from_workspace);
}

/* DELETE-EXTERNAL-CONNECTIONS-OF-BLOCKS */
Object delete_external_connections_of_blocks(blocks)
    Object blocks;
{
    Object junction_blocks_not_to_be_deleted, frame_serial_number, block;
    Object ab_loop_list_, gensymed_symbol, xa, ya, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object block_at_other_end, temp_1, ab_less_than_branch_qm_;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(2);

    x_note_fn_call(143,89);
    junction_blocks_not_to_be_deleted = blocks;
    PUSH_SPECIAL_WITH_SYMBOL(Junction_blocks_not_to_be_deleted,Qjunction_blocks_not_to_be_deleted,junction_blocks_not_to_be_deleted,
	    1);
      frame_serial_number = 
	      copy_frame_serial_number(Current_frame_serial_number);
      block = Nil;
      ab_loop_list_ = blocks;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      gensymed_symbol = ISVREF(block,(SI_Long)3L);
      temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
	      Qavailable_frame_vector) : TRUEP(Qnil);
      if (temp);
      else
	  temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		  (SI_Long)-1L : TRUEP(Nil);
      if (temp);
      else if (FIXNUMP(frame_serial_number))
	  temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_serial_number,
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
      if ( !temp) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
	    block_at_other_end = Nil;
	    gensymed_symbol = CDR(ab_skip_list_form_);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
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
	  next_loop_1:
	  next_loop_2:
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
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_1;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_1:;
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
		    ab_connection_)
		goto end_1;
	    goto next_loop_2;
	  end_loop_2:
	  end_1:
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    connection = ab_connection_;
	    block_at_other_end = 
		    get_block_at_other_end_of_connection(connection,block);
	    if ( !TRUEP(memq_function(block_at_other_end,blocks))) {
		sub_class_bit_vector = ISVREF(ISVREF(block_at_other_end,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		delete_connection_to_stub(connection);
	    goto next_loop_1;
	  end_loop_3:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop:
      reclaim_frame_serial_number(frame_serial_number);
      temp_1 = Qnil;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

static Object Qjust_erase;         /* just-erase */

/* G2-TRANSFER-LIST-CONTENTS */
Object g2_transfer_list_contents varargs_1(int, n)
{
    Object object_list, to_workspace_or_window, x_offset, y_offset;
    Object delete_external_connections_p, objects_being_transferred;
    Object from_workspace, temp, sub_class_bit_vector, temp_2, to_workspace;
    Object block, ab_loop_list_, scope_conses, ab_node_stack_;
    Object ab_current_node_, gensymed_symbol_3, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object other_end, ab_less_than_branch_qm_;
    Object dragging_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__1, ab_loop_it_;
    Object saved_position_or_next_lower_thing, reversed_blocks;
    Object transfer_in_progress;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(143,90);
    INIT_ARGS_nonrelocating();
    object_list = REQUIRED_ARG_nonrelocating();
    to_workspace_or_window = REQUIRED_ARG_nonrelocating();
    x_offset = REQUIRED_ARG_nonrelocating();
    y_offset = REQUIRED_ARG_nonrelocating();
    delete_external_connections_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = get_blocks_valid_for_group_operation(object_list);
    MVS_2(result,objects_being_transferred,from_workspace);
    if (delete_external_connections_p && 
	    evaluation_truth_value_true_p(delete_external_connections_p))
	delete_external_connections_of_blocks(objects_being_transferred);
    temp = objects_being_transferred;
    sub_class_bit_vector = ISVREF(ISVREF(to_workspace_or_window,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
	temp_1 = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp_1 = TRUEP(Nil);
    temp_2 = temp_1 ? to_workspace_or_window : Nil;
    sub_class_bit_vector = ISVREF(ISVREF(to_workspace_or_window,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_window_class_description,
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
	temp_1 = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp_1 = TRUEP(Nil);
    preflight_check_dragging_list_of_blocks_for_transfer(3,temp,temp_2,
	    temp_1 ? to_workspace_or_window : Nil);
    sub_class_bit_vector = ISVREF(ISVREF(to_workspace_or_window,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_window_class_description,
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
	temp_1 = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	transfer_items_to_mouse_of_window(2,objects_being_transferred,
		to_workspace_or_window);
    else {
	to_workspace = to_workspace_or_window;
	block = Nil;
	ab_loop_list_ = objects_being_transferred;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol_3;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  other_end = Nil;
	  gensymed_symbol_3 = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol_3)) {
	      temp = M_CAR(gensymed_symbol_3);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol_3);
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
	next_loop_1:
	next_loop_2:
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
		next_loop_3:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_1;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_3;
		end_loop_1:;
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
	  goto next_loop_2;
	end_loop_2:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_3;
	  connection = ab_connection_;
	  other_end = get_block_at_other_end_of_connection(connection,block);
	  sub_class_bit_vector = ISVREF(ISVREF(other_end,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	      dragging_modify_macro_using_test_arg_1 = other_end;
	      car_1 = dragging_modify_macro_using_test_arg_1;
	      cdr_1 = objects_being_transferred;
	      key_result = car_1;
	      x_element = Nil;
	      ab_loop_list__1 = cdr_1;
	      ab_loop_it_ = Nil;
	    next_loop_4:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_4;
	      x_element = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_2;
	      }
	      goto next_loop_4;
	    end_loop_4:
	      temp_1 = TRUEP(Qnil);
	    end_2:;
	      objects_being_transferred = temp_1 ? cdr_1 : 
		      dragging_cons_1(car_1,cdr_1);
	  }
	  goto next_loop_1;
	end_loop_3:;
	POP_SPECIAL();
	goto next_loop;
      end_loop:;
	saved_position_or_next_lower_thing = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Saved_position_or_next_lower_thing,Qsaved_position_or_next_lower_thing,saved_position_or_next_lower_thing,
		1);
	  shift_blocks_with_their_external_connections(6,
		  objects_being_transferred,Nil,Qjust_erase,from_workspace,
		  FIX((SI_Long)0L),FIX((SI_Long)0L));
	  reversed_blocks = 
		  reverse_list_using_dragging_conses(objects_being_transferred);
	  transfer_in_progress = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Transfer_in_progress,Qtransfer_in_progress,transfer_in_progress,
		  0);
	    block = Nil;
	    ab_loop_list_ = reversed_blocks;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    transfer_workspace_subblock(block,from_workspace,to_workspace);
	    goto next_loop_5;
	  end_loop_5:;
	    reclaim_dragging_list_1(reversed_blocks);
	  POP_SPECIAL();
	  shift_blocks_with_their_external_connections(8,
		  objects_being_transferred,Nil,Nil,to_workspace,x_offset,
		  FIXNUM_NEGATE(y_offset), !EQ(to_workspace,
		  from_workspace) ? T : Nil,T);
	  if (G2_has_v5_mode_windows_p) {
	      block = Nil;
	      ab_loop_list_ = objects_being_transferred;
	    next_loop_6:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_6;
	      block = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      send_ws_representations_item_insert_as_subblock(block,
		      to_workspace,Saved_position_or_next_lower_thing);
	      goto next_loop_6;
	    end_loop_6:;
	  }
	  block = Nil;
	  ab_loop_list_ = objects_being_transferred;
	next_loop_7:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_7;
	  block = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (to_workspace &&  !EQ(from_workspace,to_workspace) && 
		  ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L))
	      update_subscriptions_for_add_item_to_workspace(to_workspace,
		      block);
	  goto next_loop_7;
	end_loop_7:;
	POP_SPECIAL();
    }
    return reclaim_dragging_list_1(objects_being_transferred);
}

/* G2-MOVE-LIST-CONTENTS */
Object g2_move_list_contents varargs_1(int, n)
{
    Object object_list, delta_x, delta_y;
    Object g2_window_for_mouse_or_false, objects_being_moved, from_workspace;
    Object x2, gensymed_symbol, sub_class_bit_vector, g2_window_for_mouse_qm;
    Object image_plane_qm, block, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(143,91);
    INIT_ARGS_nonrelocating();
    object_list = REQUIRED_ARG_nonrelocating();
    delta_x = REQUIRED_ARG_nonrelocating();
    delta_y = REQUIRED_ARG_nonrelocating();
    g2_window_for_mouse_or_false = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = get_blocks_valid_for_group_operation(object_list);
    MVS_2(result,objects_being_moved,from_workspace);
    if (SIMPLE_VECTOR_P(g2_window_for_mouse_or_false) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window_for_mouse_or_false)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(g2_window_for_mouse_or_false,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window_for_mouse_or_false,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    g2_window_for_mouse_qm = temp ? g2_window_for_mouse_or_false : Nil;
    image_plane_qm = g2_window_for_mouse_qm ? 
	    map_to_image_plane(from_workspace,g2_window_for_mouse_qm) : Nil;
    if (g2_window_for_mouse_qm) {
	if ( !TRUEP(image_plane_qm)) {
	    reclaim_dragging_list_1(objects_being_moved);
	    map_to_image_plane_or_stack_error(from_workspace,
		    g2_window_for_mouse_qm);
	}
	move_items_to_mouse_of_window(objects_being_moved,
		g2_window_for_mouse_qm,image_plane_qm);
    }
    else {
	move_blocks_with_their_external_connections(objects_being_moved,
		from_workspace,delta_x,FIXNUM_NEGATE(delta_y));
	if (G2_has_v5_mode_windows_p) {
	    block = Nil;
	    ab_loop_list_ = objects_being_moved;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    send_ws_representations_item_moved(block,delta_x,delta_y);
	    goto next_loop;
	  end_loop:;
	}
    }
    return reclaim_dragging_list_1(objects_being_moved);
}

/* G2-CLONE-LIST-CONTENTS */
Object g2_clone_list_contents(object_list,to_workspace_or_window,delta_x,
	    delta_y)
    Object object_list, to_workspace_or_window, delta_x, delta_y;
{
    Object temp, objects_being_cloned, cloned_objects, item_list_for_user;
    Object saved_position_or_next_lower_thing, block, ab_loop_list_;
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, other_end, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, dragging_modify_macro_using_test_arg_1, car_1;
    Object cdr_1, key_result, x_element, ab_loop_list__1, ab_loop_it_;
    Object new_block, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object plist_of_blocks_and_corresponding_clones, cloned_block, temp_2;
    Object new_list, workspace, transfer_in_progress;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(143,92);
    temp = get_blocks_valid_for_group_operation(object_list);
    objects_being_cloned = temp;
    cloned_objects = Nil;
    item_list_for_user = Nil;
    saved_position_or_next_lower_thing = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Saved_position_or_next_lower_thing,Qsaved_position_or_next_lower_thing,saved_position_or_next_lower_thing,
	    1);
      block = Nil;
      ab_loop_list_ = objects_being_cloned;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      scope_conses = Scope_conses;
      ab_node_stack_ = Nil;
      ab_current_node_ = Nil;
      gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
	other_end = Nil;
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
      next_loop_1:
      next_loop_2:
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
	      next_loop_3:
		ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
		if ( !TRUEP(ab_less_than_branch_qm_))
		    goto end_loop_1;
		ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		ab_current_node_ = ab_less_than_branch_qm_;
		goto next_loop_3;
	      end_loop_1:;
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
	goto next_loop_2;
      end_loop_2:
      end_1:
	if ( !TRUEP(ab_current_node_))
	    goto end_loop_3;
	connection = ab_connection_;
	other_end = get_block_at_other_end_of_connection(connection,block);
	sub_class_bit_vector = ISVREF(ISVREF(other_end,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	if (temp_1) {
	    dragging_modify_macro_using_test_arg_1 = other_end;
	    car_1 = dragging_modify_macro_using_test_arg_1;
	    cdr_1 = objects_being_cloned;
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list__1 = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_4;
	    x_element = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_4;
	  end_loop_4:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    objects_being_cloned = temp_1 ? cdr_1 : dragging_cons_1(car_1,
		    cdr_1);
	}
	goto next_loop_1;
      end_loop_3:;
      POP_SPECIAL();
      goto next_loop;
    end_loop:;
      block = Nil;
      ab_loop_list_ = objects_being_cloned;
      new_block = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop_5:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_5;
      block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      new_block = clone_frame(2,block,objects_being_cloned);
      set_neither_permanent_nor_transient_and_propagate(new_block,Nil);
      cloned_objects = dragging_cons_1(new_block,cloned_objects);
      ab_loopvar__2 = dragging_list_2(block,new_block);
      if (ab_loopvar__2) {
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = last(ab_loopvar__2,_);
      }
      goto next_loop_5;
    end_loop_5:
      plist_of_blocks_and_corresponding_clones = ab_loopvar_;
      goto end_3;
      plist_of_blocks_and_corresponding_clones = Qnil;
    end_3:;
      block = Nil;
      cloned_block = Nil;
      ab_loop_list_ = plist_of_blocks_and_corresponding_clones;
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_6;
    next_loop_6:
      block = CAR(ab_loop_list_);
      temp = CDR(ab_loop_list_);
      cloned_block = CAR(temp);
      clone_connections_for_block(block,cloned_block,
	      plist_of_blocks_and_corresponding_clones);
      ab_loop_list_ = CDDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_6;
      goto next_loop_6;
    end_loop_6:;
      reclaim_dragging_list_1(plist_of_blocks_and_corresponding_clones);
      temp = cloned_objects;
      sub_class_bit_vector = ISVREF(ISVREF(to_workspace_or_window,
	      (SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      temp_2 = temp_1 ? to_workspace_or_window : Nil;
      sub_class_bit_vector = ISVREF(ISVREF(to_workspace_or_window,
	      (SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(G2_window_class_description,
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      preflight_check_dragging_list_of_blocks_for_transfer(3,temp,temp_2,
	      temp_1 ? to_workspace_or_window : Nil);
      new_list = Nil;
      cloned_block = Nil;
      ab_loop_list_ = cloned_objects;
    next_loop_7:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_7;
      cloned_block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      dragging_modify_macro_using_test_arg_1 = cloned_block;
      car_1 = dragging_modify_macro_using_test_arg_1;
      cdr_1 = new_list;
      key_result = car_1;
      x_element = Nil;
      ab_loop_list__1 = cdr_1;
      ab_loop_it_ = Nil;
    next_loop_8:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_8;
      x_element = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
      if (ab_loop_it_) {
	  temp_1 = TRUEP(ab_loop_it_);
	  goto end_4;
      }
      goto next_loop_8;
    end_loop_8:
      temp_1 = TRUEP(Qnil);
    end_4:;
      new_list = temp_1 ? cdr_1 : dragging_cons_1(car_1,cdr_1);
      scope_conses = Scope_conses;
      ab_node_stack_ = Nil;
      ab_current_node_ = Nil;
      gensymed_symbol = ACCESS_ONCE(ISVREF(cloned_block,(SI_Long)14L));
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
	other_end = Nil;
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
      next_loop_9:
      next_loop_10:
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
	      next_loop_11:
		ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
		if ( !TRUEP(ab_less_than_branch_qm_))
		    goto end_loop_9;
		ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		ab_current_node_ = ab_less_than_branch_qm_;
		goto next_loop_11;
	      end_loop_9:;
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
	    goto end_5;
	goto next_loop_10;
      end_loop_10:
      end_5:
	if ( !TRUEP(ab_current_node_))
	    goto end_loop_11;
	connection = ab_connection_;
	other_end = get_block_at_other_end_of_connection(connection,
		cloned_block);
	sub_class_bit_vector = ISVREF(ISVREF(other_end,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	if (temp_1) {
	    dragging_modify_macro_using_test_arg_1 = other_end;
	    car_1 = dragging_modify_macro_using_test_arg_1;
	    cdr_1 = new_list;
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list__1 = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_12:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_12;
	    x_element = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_6;
	    }
	    goto next_loop_12;
	  end_loop_12:
	    temp_1 = TRUEP(Qnil);
	  end_6:;
	    new_list = temp_1 ? cdr_1 : dragging_cons_1(car_1,cdr_1);
	}
	goto next_loop_9;
      end_loop_11:;
      POP_SPECIAL();
      goto next_loop_7;
    end_loop_7:
      reclaim_dragging_list_1(cloned_objects);
      cloned_objects = new_list;
      sub_class_bit_vector = ISVREF(ISVREF(to_workspace_or_window,
	      (SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(G2_window_class_description,
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  transfer_items_to_mouse_of_window(2,cloned_objects,
		  to_workspace_or_window);
      else {
	  workspace = to_workspace_or_window;
	  transfer_in_progress = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Transfer_in_progress,Qtransfer_in_progress,transfer_in_progress,
		  0);
	    block = Nil;
	    ab_loop_list_ = cloned_objects;
	  next_loop_13:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_13;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    transfer_workspace_subblock(block,Nil,workspace);
	    goto next_loop_13;
	  end_loop_13:;
	  POP_SPECIAL();
	  shift_blocks_with_their_external_connections(8,cloned_objects,
		  Nil,Nil,workspace,delta_x,FIXNUM_NEGATE(delta_y),T,T);
	  if (G2_has_v5_mode_windows_p) {
	      block = Nil;
	      ab_loop_list_ = cloned_objects;
	    next_loop_14:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_14;
	      block = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      send_ws_representations_item_insert_as_subblock(block,
		      workspace,Saved_position_or_next_lower_thing);
	      goto next_loop_14;
	    end_loop_14:;
	  }
	  reclaim_dragging_list_1(objects_being_cloned);
      }
      item_list_for_user = make_transient_item(Qitem_list);
      cloned_objects = nreverse(cloned_objects);
      block = Nil;
      ab_loop_list_ = cloned_objects;
    next_loop_15:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_15;
      block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  g2_list_insert_at_beginning(block,item_list_for_user);
      goto next_loop_15;
    end_loop_15:;
      reclaim_dragging_list_1(cloned_objects);
      result = VALUES_1(item_list_for_user);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Align_selection_command_operations, Qalign_selection_command_operations);

static Object string_constant_15;  /* "The symbol ~a is not a valid alignment operation ~
				    *                   name. It must be one of the symbols ~L,|."
				    */

/* G2-ALIGN-LIST-CONTENTS */
Object g2_align_list_contents(object_list,operation)
    Object object_list, operation;
{
    Object temp, objects_being_aligned, top_of_stack, message_1;

    x_note_fn_call(143,93);
    temp = get_blocks_valid_for_group_operation(object_list);
    objects_being_aligned = temp;
    if (memq_function(operation,Align_selection_command_operations)) {
	align_blocks(objects_being_aligned,operation);
	return reclaim_dragging_list_1(objects_being_aligned);
    }
    else {
	reclaim_dragging_list_1(objects_being_aligned);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_15,
		operation,Align_selection_command_operations);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Distribute_selection_command_operations, Qdistribute_selection_command_operations);

static Object string_constant_16;  /* "The symbol ~a is not a valid operation name for distribute. ~
				    *                   It must be one of the symbols ~L,|."
				    */

/* G2-DISTRIBUTE-LIST-CONTENTS */
Object g2_distribute_list_contents(objects,operation)
    Object objects, operation;
{
    Object temp, valid_objects, top_of_stack, message_1;

    x_note_fn_call(143,94);
    temp = get_blocks_valid_for_group_operation(objects);
    valid_objects = temp;
    if (memq_function(operation,Distribute_selection_command_operations))
	distribute_blocks(valid_objects,operation);
    else {
	reclaim_dragging_list_1(valid_objects);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_16,
		operation,Distribute_selection_command_operations);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (CONSP(objects) && EQ(M_CDR(objects),Qsequence))
	reclaim_evaluation_sequence(objects);
    return VALUES_1(Nil);
}

static Object string_constant_17;  /* "Arguments must be workspace, integer, integer, integer, integer, item-list" */

/* G2-ITEMS-IN-AREA */
Object g2_items_in_area(workspace,left,top,right,bottom,item_list)
    Object workspace, left, top, right, bottom, item_list;
{
    Object objects, sub_class_bit_vector, x2, top_of_stack, message_1, block;
    Object ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(143,95);
    objects = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
	if (SIMPLE_VECTOR_P(item_list) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_list)) > (SI_Long)2L 
		&&  !EQ(ISVREF(item_list,(SI_Long)1L),
		    Qavailable_frame_vector)) {
	    x2 = ISVREF(item_list,(SI_Long)1L);
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
	sub_class_bit_vector = ISVREF(ISVREF(item_list,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Item_list_class_description,(SI_Long)18L));
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
    if ( !((((temp ? INTEGERP(left) : TRUEP(Nil)) ? INTEGERP(top) : 
	    TRUEP(Nil)) ? INTEGERP(right) : TRUEP(Nil)) ? INTEGERP(bottom) 
	    : TRUEP(Nil))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_17);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    bottom = FIXNUM_NEGATE(bottom);
    top = FIXNUM_NEGATE(top);
    objects = list_blocks_within_area_of_workspace(workspace,left,top,
	    right,bottom,Nil,Nil);
    block = Nil;
    ab_loop_list_ = objects;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_list_insert_at_end(2,block,item_list);
    goto next_loop;
  end_loop:;
    return reclaim_dragging_list_1(objects);
}

void lists_INIT()
{
    Object temp, temp_1, temp_2, gensymed_symbol;
    Object Qg2_items_in_area, Qfunction_keeps_procedure_environment_valid_qm;
    Object AB_package, Qg2_distribute_list_contents, list_constant_7;
    Object Qvertically, Qhorizontally, Qg2_align_list_contents;
    Object Qg2_clone_list_contents, Qg2_move_list_contents;
    Object Qg2_transfer_list_contents;
    Object Qout_duplicates_check_hash_table_hash_vector_50021_vectors;
    Object Qduplicates_check_hash_table_hash_vector_50021_vector_memory_usage;
    Object string_constant_57, Qutilities2;
    Object Qconvert_saved_list_values_to_g2_list_structure, Qab_class;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_56;
    Object Qg2_list_cons_memory_usage, Qoutstanding_g2_list_conses;
    Object Qutilities1, list_constant_6, Qg2_list_cons_counter_vector;
    Object Qmake_thread_array, Kfuncall, list_constant_5;
    Object Qavailable_g2_list_conses_tail_vector;
    Object Qavailable_g2_list_conses_vector, string_constant_55;
    Object list_constant_4, string_constant_54, string_constant_53;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object Qslot_putter, Qput_list_type, string_constant_49, list_constant_3;
    Object string_constant_48, string_constant_47, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object list_constant_2, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object Qclasses_which_define, Qactivate_subclass_of_entity;
    Object Qactivate_subclass_of_entity_for_g2_list;
    Object Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_g2_list;
    Object Qput_insert_duplicate_elements_qm, Qallow_duplicate_elements;
    Object Qelement_type, Qslot_value_reclaimer, Qreclaim_list_structure_value;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object list_constant_1, Qcreate_icon_description, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, Qobject;

    x_note_fn_call(143,96);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_1 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qg2_list,list_constant_1);
    string_constant_18 = 
	    STATIC_STRING("1n1m8v831Zy1l8t1m83-Cy530hyThe original parts document showed the following attributes for g2-list: reconcile.\n<ul>\n<LI>element-");
    string_constant_19 = 
	    STATIC_STRING("type: symbol, ; class of element\n<LI>allow-duplicate-elements\?: boolean, <!--from insert-duplicate-elements, -->\n<LI>permanent\?:");
    string_constant_20 = 
	    STATIC_STRING(" boolean,\n<LI>list-structure: \?\?\?, \n<LI>list-open-continuations: \?\?\?\n</ul>");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_21 = 
	    STATIC_STRING("1r4z8r835fy835fy831Zy831Zy00001r1l8o1l8l1m8p835fy1l83Cy1l83Uy1l83Ny1l83Fy000004z8r83*6y83*6y831Zy831Zy083=Ky001p1l8o1m8p83-Xy1l8");
    string_constant_22 = 
	    STATIC_STRING("l1l83Cy1l83Fy000004z8r8375y8375y831Zy831Zy08k001o1l8o1l8l1l8z1m8p83Ky000004z8r839Jy839Jy831Zy831Zy00001o1l8l1l8z1m8p83Ky1l83Cy00");
    string_constant_23 = 
	    STATIC_STRING("0004z8r8u8u831Zy831Zy01p8w9k3uy3uy1s1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mzz1m3fyz1n83Oy1mz3Gy1m3fy3Gy1n83Oy1mz3Ly1m3fy3Ly1n83Oy");
    string_constant_24 = 
	    STATIC_STRING("1mz3Qy1m3fy3Qy1n83Oy1mz3Vy1m3fy3Vy1n83Oy1mz3ay1m3fy3ay1n83Oy1mz3fy1m3fy3fy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class ");
    string_constant_25 = 
	    STATIC_STRING("definition000004z8r83U6y83U6y831Zy831Zy00001n1l8o1l8l1l83Hy000004z8r83U8y83U8y831Zy831Zy0k001p1l8o1m8p83Sy1l8l1l83Hy1l83Fy00000");
    string_constant_26 = 
	    STATIC_STRING("1t8q1p831Zy1l83-Oy1m8v831Zy8t1m83-Cy530hyThe original parts document showed the following attributes for g2-list: reconcile.\n<ul");
    string_constant_27 = 
	    STATIC_STRING(">\n<LI>element-type: symbol, ; class of element\n<LI>allow-duplicate-elements\?: boolean, <!--from insert-duplicate-elements, -->\n<");
    string_constant_28 = 
	    STATIC_STRING("LI>permanent\?: boolean,\n<LI>list-structure: \?\?\?, \n<LI>list-open-continuations: \?\?\?\n</ul>1t835fy08o8l1m8p835fy83Cy83Uy83Ny83Fy1r8");
    string_constant_29 = 
	    STATIC_STRING("3*6y83=Ky8o1m8p83-Xy8l83Cy83Fy1q8375y8k8o8l8z1m8p83Ky1q839Jy08l8z1m8p83Ky83Cy1m8u1p8w9k3uy3uy1s1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n8");
    string_constant_30 = 
	    STATIC_STRING("3Oy1mzz1m3fyz1n83Oy1mz3Gy1m3fy3Gy1n83Oy1mz3Ly1m3fy3Ly1n83Oy1mz3Qy1m3fy3Qy1n83Oy1mz3Vy1m3fy3Vy1n83Oy1mz3ay1m3fy3ay1n83Oy1mz3fy1m3");
    string_constant_31 = 
	    STATIC_STRING("fy3fy1p83U6y08o8l83Hy1r83U8yk8o1m8p83Sy8l83Hy83Fy");
    temp = regenerate_optimized_constant(LIST_3(string_constant_18,
	    string_constant_19,string_constant_20));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qg2_list,list_constant_1,Nil,temp,Nil,
	    temp_1,list_constant_1,regenerate_optimized_constant(list(6,
	    string_constant_26,string_constant_27,string_constant_28,
	    string_constant_29,string_constant_30,string_constant_31)),Nil);
    G2_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_list,
	    Class_description_gkbprop);
    Qlist_structure = STATIC_SYMBOL("LIST-STRUCTURE",AB_package);
    Qreclaim_list_structure_value = 
	    STATIC_SYMBOL("RECLAIM-LIST-STRUCTURE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_list_structure_value,
	    STATIC_FUNCTION(reclaim_list_structure_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qlist_structure,
	    SYMBOL_FUNCTION(Qreclaim_list_structure_value),
	    Qslot_value_reclaimer);
    Qlist_type = STATIC_SYMBOL("LIST-TYPE",AB_package);
    Qelement_type = STATIC_SYMBOL("ELEMENT-TYPE",AB_package);
    alias_slot_name(3,Qlist_type,Qelement_type,Qg2_list);
    Qinsert_duplicate_elements_qm = 
	    STATIC_SYMBOL("INSERT-DUPLICATE-ELEMENTS\?",AB_package);
    Qallow_duplicate_elements = STATIC_SYMBOL("ALLOW-DUPLICATE-ELEMENTS",
	    AB_package);
    alias_slot_name(3,Qinsert_duplicate_elements_qm,
	    Qallow_duplicate_elements,Qg2_list);
    Qput_insert_duplicate_elements_qm = 
	    STATIC_SYMBOL("PUT-INSERT-DUPLICATE-ELEMENTS\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_insert_duplicate_elements_qm,
	    STATIC_FUNCTION(put_insert_duplicate_elements_qm,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qinsert_duplicate_elements_qm,
	    SYMBOL_FUNCTION(Qput_insert_duplicate_elements_qm),Qslot_putter);
    Qlist_is_permanent = STATIC_SYMBOL("LIST-IS-PERMANENT",AB_package);
    Qdeactivate_subclass_of_entity_for_g2_list = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_g2_list,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_g2_list,NIL,
	    FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_g2_list);
    set_get(Qg2_list,Qdeactivate_subclass_of_entity,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_list,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qactivate_subclass_of_entity_for_g2_list = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_g2_list,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_g2_list,NIL,
	    FALSE,1,1));
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_g2_list);
    set_get(Qg2_list,Qactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_list,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qitem_list = STATIC_SYMBOL("ITEM-LIST",AB_package);
    list_constant_2 = STATIC_CONS(Qg2_list,Qnil);
    check_if_superior_classes_are_defined(Qitem_list,list_constant_2);
    string_constant_32 = STATIC_STRING("1l1m8v834Gy");
    string_constant_33 = 
	    STATIC_STRING("1l4z8r83*6y83*6y834Gy834Gy083Ry001q1l8l1l83Fy1l8z1l8o1m8p83-Xy1l83Cy00000");
    string_constant_34 = 
	    STATIC_STRING("1n8q1n834Gy1l831Zy1m8v834Gy1o83*6y83Ry83Fy8z");
    temp = regenerate_optimized_constant(string_constant_32);
    temp_1 = regenerate_optimized_constant(string_constant_33);
    add_class_to_environment(9,Qitem_list,list_constant_2,Nil,temp,Nil,
	    temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_34),Nil);
    Item_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qitem_list,
	    Class_description_gkbprop);
    Qvalue_list = STATIC_SYMBOL("VALUE-LIST",AB_package);
    check_if_superior_classes_are_defined(Qvalue_list,list_constant_2);
    string_constant_35 = STATIC_STRING("1l1m8v831Qy");
    string_constant_36 = 
	    STATIC_STRING("1l4z8r83*6y83*6y831Qy831Qy083=oy001p1l8l1l8o1m8p83-Xy1l83Cy1l83Fy00000");
    string_constant_37 = 
	    STATIC_STRING("1n8q1n831Qy1l831Zy1m8v831Qy1m83*6y83=oy");
    temp = regenerate_optimized_constant(string_constant_35);
    temp_1 = regenerate_optimized_constant(string_constant_36);
    add_class_to_environment(9,Qvalue_list,list_constant_2,Nil,temp,Nil,
	    temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_37),Nil);
    Value_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qvalue_list,
	    Class_description_gkbprop);
    Qsymbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    list_constant_3 = STATIC_CONS(Qvalue_list,Qnil);
    check_if_superior_classes_are_defined(Qsymbol_list,list_constant_3);
    string_constant_38 = STATIC_STRING("1l1m8v831ky");
    string_constant_39 = 
	    STATIC_STRING("1l4z8r83*6y83*6y831ky831ky083-2y001p1l8l1l8o1m8p83-Xy1l83Cy1l83Fy00000");
    string_constant_40 = 
	    STATIC_STRING("1n8q1n831ky1l831Qy1m8v831ky1m83*6y83-2y");
    temp = regenerate_optimized_constant(string_constant_38);
    temp_1 = regenerate_optimized_constant(string_constant_39);
    add_class_to_environment(9,Qsymbol_list,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_40),Nil);
    Symbol_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qsymbol_list,
	    Class_description_gkbprop);
    Qtext_list = STATIC_SYMBOL("TEXT-LIST",AB_package);
    check_if_superior_classes_are_defined(Qtext_list,list_constant_3);
    string_constant_41 = STATIC_STRING("1l1m8v83ABy");
    string_constant_42 = 
	    STATIC_STRING("1l4z8r83*6y83*6y83ABy83ABy083Gy001p1l8l1l8o1m8p83-Xy1l83Cy1l83Fy00000");
    string_constant_43 = 
	    STATIC_STRING("1n8q1n83ABy1l831Qy1m8v83ABy1m83*6y83Gy");
    temp = regenerate_optimized_constant(string_constant_41);
    temp_1 = regenerate_optimized_constant(string_constant_42);
    add_class_to_environment(9,Qtext_list,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_43),Nil);
    Text_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtext_list,
	    Class_description_gkbprop);
    Qtruth_value_list = STATIC_SYMBOL("TRUTH-VALUE-LIST",AB_package);
    check_if_superior_classes_are_defined(Qtruth_value_list,list_constant_3);
    string_constant_44 = STATIC_STRING("1l1m8v831my");
    string_constant_45 = 
	    STATIC_STRING("1l4z8r83*6y83*6y831my831my083-hy001p1l8l1l8o1m8p83-Xy1l83Cy1l83Fy00000");
    string_constant_46 = 
	    STATIC_STRING("1n8q1n831my1l831Qy1m8v831my1m83*6y83-hy");
    temp = regenerate_optimized_constant(string_constant_44);
    temp_1 = regenerate_optimized_constant(string_constant_45);
    add_class_to_environment(9,Qtruth_value_list,list_constant_3,Nil,temp,
	    Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_46),Nil);
    Truth_value_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtruth_value_list,
	    Class_description_gkbprop);
    Qquantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    check_if_superior_classes_are_defined(Qquantity_list,list_constant_3);
    string_constant_47 = STATIC_STRING("1l1m8v830Qy");
    string_constant_48 = 
	    STATIC_STRING("1l4z8r83*6y83*6y830Qy830Qy083-Hy001p1l8l1l8o1m8p83-Xy1l83Cy1l83Fy00000");
    string_constant_49 = 
	    STATIC_STRING("1n8q1n830Qy1l831Qy1m8v830Qy1m83*6y83-Hy");
    temp = regenerate_optimized_constant(string_constant_47);
    temp_1 = regenerate_optimized_constant(string_constant_48);
    add_class_to_environment(9,Qquantity_list,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_49),Nil);
    Quantity_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qquantity_list,
	    Class_description_gkbprop);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qput_list_type = STATIC_SYMBOL("PUT-LIST-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_list_type,STATIC_FUNCTION(put_list_type,NIL,
	    FALSE,3,3));
    mutate_global_property(Qlist_type,SYMBOL_FUNCTION(Qput_list_type),
	    Qslot_putter);
    Qfloat_list = STATIC_SYMBOL("FLOAT-LIST",AB_package);
    list_constant_4 = STATIC_CONS(Qquantity_list,Qnil);
    check_if_superior_classes_are_defined(Qfloat_list,list_constant_4);
    string_constant_50 = STATIC_STRING("1l1m8v831Xy");
    string_constant_51 = 
	    STATIC_STRING("1l4z8r83*6y83*6y831Xy831Xy09k001p1l8l1l8o1m8p83-Xy1l83Cy1l83Fy00000");
    string_constant_52 = STATIC_STRING("1n8q1n831Xy1l830Qy1m8v831Xy1m83*6y9k");
    temp = regenerate_optimized_constant(string_constant_50);
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    temp_1 = regenerate_optimized_constant(string_constant_51);
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    add_class_to_environment(9,Qfloat_list,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_52),Nil);
    Float_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qfloat_list,
	    Class_description_gkbprop);
    Qinteger_list = STATIC_SYMBOL("INTEGER-LIST",AB_package);
    check_if_superior_classes_are_defined(Qinteger_list,list_constant_4);
    string_constant_53 = STATIC_STRING("1l1m8v831dy");
    string_constant_54 = 
	    STATIC_STRING("1l4z8r83*6y83*6y831dy831dy083Sy001p1l8l1l8o1m8p83-Xy1l83Cy1l83Fy00000");
    string_constant_55 = 
	    STATIC_STRING("1n8q1n831dy1l830Qy1m8v831dy1m83*6y83Sy");
    temp = regenerate_optimized_constant(string_constant_53);
    temp_1 = regenerate_optimized_constant(string_constant_54);
    add_class_to_environment(9,Qinteger_list,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_55),Nil);
    Integer_list_class_description = 
	    lookup_global_or_kb_specific_property_value(Qinteger_list,
	    Class_description_gkbprop);
    Qavailable_g2_list_conses = STATIC_SYMBOL("AVAILABLE-G2-LIST-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_g2_list_conses,
	    Available_g2_list_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_g2_list_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_g2_list_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-G2-LIST-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_g2_list_conses_tail,
	    Available_g2_list_conses_tail);
    record_system_variable(Qavailable_g2_list_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_g2_list_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-G2-LIST-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_g2_list_conses_vector,
	    Available_g2_list_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_g2_list_conses_vector,Qutilities1,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qavailable_g2_list_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-G2-LIST-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_g2_list_conses_tail_vector,
	    Available_g2_list_conses_tail_vector);
    record_system_variable(Qavailable_g2_list_conses_tail_vector,
	    Qutilities1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qg2_list_cons_counter_vector = 
	    STATIC_SYMBOL("G2-LIST-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_list_cons_counter_vector,
	    G2_list_cons_counter_vector);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qg2_list_cons_counter_vector,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qg2_list_cons_counter = STATIC_SYMBOL("G2-LIST-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_list_cons_counter,G2_list_cons_counter);
    record_system_variable(Qg2_list_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_g2_list_conses = 
	    STATIC_SYMBOL("OUTSTANDING-G2-LIST-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_g2_list_conses,
	    STATIC_FUNCTION(outstanding_g2_list_conses,NIL,FALSE,0,0));
    Qg2_list_cons_memory_usage = STATIC_SYMBOL("G2-LIST-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_list_cons_memory_usage,
	    STATIC_FUNCTION(g2_list_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_56 = STATIC_STRING("1q83-VKy9k83-VJy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_g2_list_conses);
    push_optimized_constant(Qg2_list_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_56));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlist_size = STATIC_SYMBOL("LIST-SIZE",AB_package);
    string_constant = 
	    STATIC_STRING("The position given for a list is ~a, but it must be an integer.");
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qquantity_array = STATIC_SYMBOL("QUANTITY-ARRAY",AB_package);
    Qtext_array = STATIC_SYMBOL("TEXT-ARRAY",AB_package);
    Qtruth_value_array = STATIC_SYMBOL("TRUTH-VALUE-ARRAY",AB_package);
    Qsymbol_array = STATIC_SYMBOL("SYMBOL-ARRAY",AB_package);
    Qitem_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    Qvalue_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qframe_denotation = STATIC_SYMBOL("FRAME-DENOTATION",AB_package);
    Qconvert_saved_list_values_to_g2_list_structure = 
	    STATIC_SYMBOL("CONVERT-SAVED-LIST-VALUES-TO-G2-LIST-STRUCTURE",
	    AB_package);
    temp_2 = adjoin(2,Qconvert_saved_list_values_to_g2_list_structure,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_2;
    temp_2 = adjoin(2,Qconvert_saved_list_values_to_g2_list_structure,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_2;
    SET_SYMBOL_FUNCTION(Qconvert_saved_list_values_to_g2_list_structure,
	    STATIC_FUNCTION(convert_saved_list_values_to_g2_list_structure,
	    NIL,FALSE,0,0));
    string_constant_1 = 
	    STATIC_STRING("~NF is not initialized yet -- start G2 first");
    Qelement_position = STATIC_SYMBOL("ELEMENT-POSITION",AB_package);
    string_constant_2 = 
	    STATIC_STRING("Cannot transfer items to the mouse of ~NF: it\'s not a connected G2-window instance!");
    string_constant_3 = 
	    STATIC_STRING("Cannot transfer items to non-KB workspaces!");
    string_constant_4 = 
	    STATIC_STRING("Cannot transfer items to proprietary workspaces!");
    string_constant_5 = STATIC_STRING("Objects are not transferrable");
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    string_constant_6 = 
	    STATIC_STRING("Cannot transfer ~NF because it is an attribute of ~NF.");
    string_constant_7 = 
	    string_append2(STATIC_STRING("Cannot transfer ~NF because it is a kb-workspace.  The make ~\n                  subworkspace action can be used to give a transient ~\n                  kb-workspace a new supe"),
	    STATIC_STRING("rior object."));
    string_constant_8 = 
	    STATIC_STRING("Cannot transfer ~NF because it is a ~a.");
    string_constant_9 = 
	    STATIC_STRING("Cannot transfer ~NF to the workspace ~NF because ~NF is superior to ~\n          this workspace.");
    string_constant_10 = 
	    STATIC_STRING("Cannot transfer ~NF to the workspace ~NF.  ~NF is a dependent item ~\n                         containing a compiled attribute and ~NF is not dependent.");
    Qavailable_duplicates_check_hash_table_hash_vector_50021_vectors = 
	    STATIC_SYMBOL("AVAILABLE-DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR-50021-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_duplicates_check_hash_table_hash_vector_50021_vectors,
	    Available_duplicates_check_hash_table_hash_vector_50021_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_duplicates_check_hash_table_hash_vector_50021_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_duplicates_check_hash_table_hash_vector_50021_vectors = 
	    STATIC_SYMBOL("COUNT-OF-DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR-50021-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_duplicates_check_hash_table_hash_vector_50021_vectors,
	    Count_of_duplicates_check_hash_table_hash_vector_50021_vectors);
    record_system_variable(Qcount_of_duplicates_check_hash_table_hash_vector_50021_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector 
	    == UNBOUND)
	Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector 
		= make_thread_array(Nil);
    Qout_duplicates_check_hash_table_hash_vector_50021_vectors = 
	    STATIC_SYMBOL("OUT-DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR-50021-VECTORS",
	    AB_package);
    Qduplicates_check_hash_table_hash_vector_50021_vector_memory_usage = 
	    STATIC_SYMBOL("DUPLICATES-CHECK-HASH-TABLE-HASH-VECTOR-50021-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_57 = STATIC_STRING("1q83-S*y83*9y83-Ooy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_duplicates_check_hash_table_hash_vector_50021_vectors);
    push_optimized_constant(Qduplicates_check_hash_table_hash_vector_50021_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_57));
    SET_SYMBOL_FUNCTION(Qduplicates_check_hash_table_hash_vector_50021_vector_memory_usage,
	    STATIC_FUNCTION(duplicates_check_hash_table_hash_vector_50021_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_duplicates_check_hash_table_hash_vector_50021_vectors,
	    STATIC_FUNCTION(out_duplicates_check_hash_table_hash_vector_50021_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qduplicates_check_hash_table_tree_for_hash = 
	    STATIC_SYMBOL("DUPLICATES-CHECK-HASH-TABLE-TREE-FOR-HASH",
	    AB_package);
    if (Duplicates_check_hash == UNBOUND)
	Duplicates_check_hash = make_duplicates_check_hash_table();
    string_constant_11 = STATIC_STRING("The item list is empty.");
    string_constant_12 = 
	    STATIC_STRING("All members of the list must be items, ~NF is not an item.");
    string_constant_13 = 
	    STATIC_STRING("All items in the list must be on a workspace. ~NF is not on one.");
    string_constant_14 = 
	    STATIC_STRING("All items in the list must be on the same workspace. ~\n                    ~NF is not on ~NF.");
    Qg2_transfer_list_contents = STATIC_SYMBOL("G2-TRANSFER-LIST-CONTENTS",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_transfer_list_contents,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qjust_erase = STATIC_SYMBOL("JUST-ERASE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_transfer_list_contents,
	    STATIC_FUNCTION(g2_transfer_list_contents,NIL,TRUE,4,5));
    Qg2_move_list_contents = STATIC_SYMBOL("G2-MOVE-LIST-CONTENTS",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_move_list_contents,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_move_list_contents,
	    STATIC_FUNCTION(g2_move_list_contents,NIL,TRUE,3,4));
    Qg2_clone_list_contents = STATIC_SYMBOL("G2-CLONE-LIST-CONTENTS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_clone_list_contents,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_clone_list_contents,
	    STATIC_FUNCTION(g2_clone_list_contents,NIL,FALSE,4,4));
    Qg2_align_list_contents = STATIC_SYMBOL("G2-ALIGN-LIST-CONTENTS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_align_list_contents,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_15 = 
	    STATIC_STRING("The symbol ~a is not a valid alignment operation ~\n                  name. It must be one of the symbols ~L,|.");
    SET_SYMBOL_FUNCTION(Qg2_align_list_contents,
	    STATIC_FUNCTION(g2_align_list_contents,NIL,FALSE,2,2));
    Qhorizontally = STATIC_SYMBOL("HORIZONTALLY",AB_package);
    Qvertically = STATIC_SYMBOL("VERTICALLY",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qhorizontally,Qvertically);
    if (Distribute_selection_command_operations == UNBOUND)
	Distribute_selection_command_operations = list_constant_7;
    Qg2_distribute_list_contents = 
	    STATIC_SYMBOL("G2-DISTRIBUTE-LIST-CONTENTS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_distribute_list_contents,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_16 = 
	    STATIC_STRING("The symbol ~a is not a valid operation name for distribute. ~\n                  It must be one of the symbols ~L,|.");
    SET_SYMBOL_FUNCTION(Qg2_distribute_list_contents,
	    STATIC_FUNCTION(g2_distribute_list_contents,NIL,FALSE,2,2));
    Qg2_items_in_area = STATIC_SYMBOL("G2-ITEMS-IN-AREA",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_items_in_area,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_17 = 
	    STATIC_STRING("Arguments must be workspace, integer, integer, integer, integer, item-list");
    SET_SYMBOL_FUNCTION(Qg2_items_in_area,STATIC_FUNCTION(g2_items_in_area,
	    NIL,FALSE,6,6));
}
