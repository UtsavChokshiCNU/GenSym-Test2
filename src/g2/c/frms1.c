/* frms1.c
 * Input file:  frames1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms1.h"


Object Available_class_description_conses = UNBOUND;

Object Available_class_description_conses_tail = UNBOUND;

Object Class_description_cons_counter = UNBOUND;

/* OUTSTANDING-CLASS-DESCRIPTION-CONSES */
Object outstanding_class_description_conses()
{
    Object temp;

    x_note_fn_call(80,0);
    temp = FIXNUM_MINUS(Class_description_cons_counter,
	    length(Available_class_description_conses));
    return VALUES_1(temp);
}

/* CLASS-DESCRIPTION-CONS-MEMORY-USAGE */
Object class_description_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(80,1);
    temp = FIXNUM_TIMES(Class_description_cons_counter,
	    ltimes(FIX((SI_Long)2L),Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-CLASS-DESCRIPTION-CONS-POOL */
Object replenish_class_description_cons_pool()
{
    Object gensymed_symbol, new_conses, incff_1_arg;
    Object class_description_cons_counter_new_value;
    XDeclare_area(1);

    x_note_fn_call(80,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    incff_1_arg = Cons_pool_conses_to_make_at_a_time;
    class_description_cons_counter_new_value = 
	    FIXNUM_ADD(Class_description_cons_counter,incff_1_arg);
    Class_description_cons_counter = class_description_cons_counter_new_value;
    if (Available_class_description_conses)
	Available_class_description_conses = nconc2(CDR(new_conses),
		Available_class_description_conses);
    else {
	Available_class_description_conses = CDR(new_conses);
	Available_class_description_conses_tail = last(new_conses,_);
    }
    return VALUES_1(new_conses);
}

static Object Qclass_description;  /* class-description */

/* CLASS-DESCRIPTION-CONS-1 */
Object class_description_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, gensymed_symbol;

    x_note_fn_call(80,3);
    new_cons = Available_class_description_conses;
    if (new_cons) {
	Available_class_description_conses = M_CDR(new_cons);
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
    Object gensymed_symbol, new_conses;
    SI_Long conses_needed, temp, new_conses_count, incff_1_arg;
    SI_Long class_description_cons_counter_new_value;
    XDeclare_area(1);

    x_note_fn_call(80,4);
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
    if (Available_class_description_conses)
	Available_class_description_conses = nconc2(new_conses,
		Available_class_description_conses);
    else
	Available_class_description_conses = new_conses;
    incff_1_arg = new_conses_count;
    class_description_cons_counter_new_value = 
	    IFIX(Class_description_cons_counter) + incff_1_arg;
    Class_description_cons_counter = 
	    FIX(class_description_cons_counter_new_value);
    return VALUES_1(Nil);
}

/* MAKE-CLASS-DESCRIPTION-LIST-1 */
Object make_class_description_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(80,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = Available_class_description_conses;
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
	    gensymed_symbol = Available_class_description_conses;
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qclass_description);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = Available_class_description_conses;
	Available_class_description_conses = CDR(gensymed_symbol_1);
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
    Object gensymed_symbol, gensymed_symbol_1, temp;

    x_note_fn_call(80,6);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = CDR(Available_class_description_conses);
    if (gensymed_symbol)
	goto end_loop;
    replenish_class_description_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = Available_class_description_conses;
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qclass_description);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = Available_class_description_conses;
    Available_class_description_conses = CDR(gensymed_symbol);
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
    Object gensymed_symbol, temp, gensymed_symbol_1;

    x_note_fn_call(80,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = CDR(Available_class_description_conses);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_class_description_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = Available_class_description_conses;
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qclass_description);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = Available_class_description_conses;
    Available_class_description_conses = CDR(gensymed_symbol);
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
    Object gensymed_symbol, temp, gensymed_symbol_1;

    x_note_fn_call(80,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = CDR(Available_class_description_conses);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_class_description_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = Available_class_description_conses;
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qclass_description);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = Available_class_description_conses;
    Available_class_description_conses = CDR(gensymed_symbol);
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
    x_note_fn_call(80,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-CLASS-DESCRIPTION-CONSES-1 */
Object copy_tree_using_class_description_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, gensymed_symbol, temp_1, new_list, last_new_cons;
    Object current_copy_position;

    x_note_fn_call(80,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = Available_class_description_conses;
	if (new_cons) {
	    Available_class_description_conses = M_CDR(new_cons);
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
	new_cons = Available_class_description_conses;
	if (new_cons) {
	    Available_class_description_conses = M_CDR(new_cons);
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
    Object temp, new_cons, gensymed_symbol, temp_1, new_list, last_new_cons;
    Object current_copy_position;

    x_note_fn_call(80,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = Available_class_description_conses;
	if (new_cons) {
	    Available_class_description_conses = M_CDR(new_cons);
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
	new_cons = Available_class_description_conses;
	if (new_cons) {
	    Available_class_description_conses = M_CDR(new_cons);
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
    Object cdr_new_value;

    x_note_fn_call(80,12);
    inline_note_reclaim_cons(class_description_cons,Qclass_description);
    cdr_new_value = Available_class_description_conses;
    M_CDR(class_description_cons) = cdr_new_value;
    Available_class_description_conses = class_description_cons;
    return VALUES_1(Nil);
}

/* RECLAIM-CLASS-DESCRIPTION-LIST-1 */
Object reclaim_class_description_list_1(class_description_list)
    Object class_description_list;
{
    Object last_1, next_qm, cdr_new_value, temp;

    x_note_fn_call(80,13);
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
	cdr_new_value = Available_class_description_conses;
	M_CDR(last_1) = cdr_new_value;
	Available_class_description_conses = class_description_list;
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* RECLAIM-CLASS-DESCRIPTION-LIST*-1 */
Object reclaim_class_description_list_star_1(class_description_list)
    Object class_description_list;
{
    Object temp, last_1, next_qm, temp_1;

    x_note_fn_call(80,14);
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
	    temp = Available_class_description_conses;
	    M_CDR(last_1) = temp;
	    Available_class_description_conses = class_description_list;
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
    Object e, e2, class_description_cons, cdr_new_value, temp;

    x_note_fn_call(80,15);
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
	    cdr_new_value = Available_class_description_conses;
	    M_CDR(e) = cdr_new_value;
	    Available_class_description_conses = tree;
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

/* DELETE-CLASS-DESCRIPTION-ELEMENT-1 */
Object delete_class_description_element_1(element,class_description_list)
    Object element, class_description_list;
{
    Object temp, cdr_new_value, l_trailer_qm, l;

    x_note_fn_call(80,16);
    if (class_description_list) {
	if (EQ(element,M_CAR(class_description_list))) {
	    temp = CDR(class_description_list);
	    inline_note_reclaim_cons(class_description_list,
		    Qclass_description);
	    cdr_new_value = Available_class_description_conses;
	    M_CDR(class_description_list) = cdr_new_value;
	    Available_class_description_conses = class_description_list;
	}
	else {
	    l_trailer_qm = Nil;
	    l = class_description_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		cdr_new_value = M_CDR(l);
		M_CDR(l_trailer_qm) = cdr_new_value;
		inline_note_reclaim_cons(l,Qclass_description);
		cdr_new_value = Available_class_description_conses;
		M_CDR(l) = cdr_new_value;
		Available_class_description_conses = l;
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

    x_note_fn_call(80,17);
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

Object No_value = UNBOUND;

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
    x_note_fn_call(80,18);
    return reclaim_class_description_list_1(list_1);
}

Object Direct_superior_classes_gkbprop = UNBOUND;

/* COPY-LIST-USING-CLASS-DESCRIPTION-CONSES-FUNCTION */
Object copy_list_using_class_description_conses_function(list_1)
    Object list_1;
{
    x_note_fn_call(80,19);
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

    x_note_fn_call(80,20);
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

    x_note_fn_call(80,21);
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

    x_note_fn_call(80,22);
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

Object Chain_of_available_slot_descriptions = UNBOUND;

Object Slot_description_count = UNBOUND;

/* SLOT-DESCRIPTION-STRUCTURE-MEMORY-USAGE */
Object slot_description_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,23);
    temp = Slot_description_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SLOT-DESCRIPTION-COUNT */
Object outstanding_slot_description_count()
{
    Object def_structure_slot_description_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,24);
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
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(80,25);
    inline_note_reclaim_cons(slot_description,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = slot_description;
    reclaim_class_description_tree_1(ISVREF(slot_description,(SI_Long)5L));
    SVREF(slot_description,FIX((SI_Long)5L)) = Nil;
    reclaim_class_description_tree_1(ISVREF(slot_description,(SI_Long)9L));
    SVREF(slot_description,FIX((SI_Long)9L)) = Nil;
    reclaim_if_evaluator_slot_info(ISVREF(slot_description,(SI_Long)10L));
    SVREF(slot_description,FIX((SI_Long)10L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_slot_descriptions;
    SVREF(slot_description,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_slot_descriptions = slot_description;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SLOT-DESCRIPTION */
Object reclaim_structure_for_slot_description(slot_description)
    Object slot_description;
{
    x_note_fn_call(80,26);
    return reclaim_slot_description_1(slot_description);
}

static Object Qg2_defstruct_structure_name_slot_description_g2_struct;  /* g2-defstruct-structure-name::slot-description-g2-struct */

/* MAKE-PERMANENT-SLOT-DESCRIPTION-STRUCTURE-INTERNAL */
Object make_permanent_slot_description_structure_internal()
{
    Object def_structure_slot_description_variable;
    Object slot_description_count_new_value;
    Object defstruct_g2_slot_description_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,27);
    def_structure_slot_description_variable = Nil;
    slot_description_count_new_value = FIXNUM_ADD1(Slot_description_count);
    Slot_description_count = slot_description_count_new_value;
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
    Object def_structure_slot_description_variable;

    x_note_fn_call(80,28);
    def_structure_slot_description_variable = 
	    Chain_of_available_slot_descriptions;
    if (def_structure_slot_description_variable) {
	Chain_of_available_slot_descriptions = 
		ISVREF(def_structure_slot_description_variable,(SI_Long)0L);
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

static Object Qab_gensym;          /* gensym */

/* RECLAIM-SLOT-HASH-LEAVES */
Object reclaim_slot_hash_leaves(slot_hash_binary_tree)
    Object slot_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, cdr_new_value, last_1, next_qm, temp;

    x_note_fn_call(80,29);
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
    inline_note_reclaim_cons(alist_entry,Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(alist_entry) = cdr_new_value;
    Available_gensym_conses = alist_entry;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qab_gensym);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	Available_gensym_conses = alist;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	reclaim_slot_hash_leaves(less_than_branch_qm);
	slot_hash_binary_tree = greater_than_branch_qm;
    }
    else {
	temp = less_than_branch_qm;
	if (temp);
	else
	    temp = greater_than_branch_qm;
	slot_hash_binary_tree = temp;
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

    x_note_fn_call(80,30);
    element_qm = CDR(slot_hash_binary_tree);
    if (element_qm) {
	reclaim_slot_hash_leaves(element_qm);
	M_CDR(slot_hash_binary_tree) = Nil;
    }
    return VALUES_1(slot_hash_binary_tree);
}

Object Any_cached_evaluator_slot_info_p = UNBOUND;

Object The_type_description_of_evaluator_slot_info = UNBOUND;

Object Chain_of_available_evaluator_slot_infos = UNBOUND;

Object Evaluator_slot_info_count = UNBOUND;

/* EVALUATOR-SLOT-INFO-STRUCTURE-MEMORY-USAGE */
Object evaluator_slot_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,31);
    temp = Evaluator_slot_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EVALUATOR-SLOT-INFO-COUNT */
Object outstanding_evaluator_slot_info_count()
{
    Object def_structure_evaluator_slot_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,32);
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
    Object svref_new_value;

    x_note_fn_call(80,33);
    inline_note_reclaim_cons(evaluator_slot_info,Nil);
    svref_new_value = Chain_of_available_evaluator_slot_infos;
    SVREF(evaluator_slot_info,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_evaluator_slot_infos = evaluator_slot_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EVALUATOR-SLOT-INFO */
Object reclaim_structure_for_evaluator_slot_info(evaluator_slot_info)
    Object evaluator_slot_info;
{
    x_note_fn_call(80,34);
    return reclaim_evaluator_slot_info_1(evaluator_slot_info);
}

static Object Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct;  /* g2-defstruct-structure-name::evaluator-slot-info-g2-struct */

/* MAKE-PERMANENT-EVALUATOR-SLOT-INFO-STRUCTURE-INTERNAL */
Object make_permanent_evaluator_slot_info_structure_internal()
{
    Object def_structure_evaluator_slot_info_variable;
    Object evaluator_slot_info_count_new_value;
    Object defstruct_g2_evaluator_slot_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,35);
    def_structure_evaluator_slot_info_variable = Nil;
    evaluator_slot_info_count_new_value = 
	    FIXNUM_ADD1(Evaluator_slot_info_count);
    Evaluator_slot_info_count = evaluator_slot_info_count_new_value;
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
    Object def_structure_evaluator_slot_info_variable;

    x_note_fn_call(80,36);
    def_structure_evaluator_slot_info_variable = 
	    Chain_of_available_evaluator_slot_infos;
    if (def_structure_evaluator_slot_info_variable) {
	Chain_of_available_evaluator_slot_infos = 
		ISVREF(def_structure_evaluator_slot_info_variable,(SI_Long)0L);
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
    x_note_fn_call(80,37);
    if (evaluator_slot_info_qm)
	return reclaim_evaluator_slot_info_1(evaluator_slot_info_qm);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_class_description = UNBOUND;

Object Chain_of_available_class_descriptions = UNBOUND;

Object Class_description_count = UNBOUND;

/* CLASS-DESCRIPTION-STRUCTURE-MEMORY-USAGE */
Object class_description_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,38);
    temp = Class_description_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)25L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CLASS-DESCRIPTION-COUNT */
Object outstanding_class_description_count()
{
    Object def_structure_class_description_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,39);
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
    Object old_structure_being_reclaimed, slot_hash_binary_tree, element_qm;
    Object temp;

    x_note_fn_call(80,40);
    inline_note_reclaim_cons(class_description,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = class_description;
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
    inline_note_reclaim_cons(slot_hash_binary_tree,Qab_gensym);
    temp = Available_gensym_conses;
    M_CDR(slot_hash_binary_tree) = temp;
    Available_gensym_conses = slot_hash_binary_tree;
    SVREF(class_description,FIX((SI_Long)9L)) = Nil;
    reclaim_class_description_tree_1(ISVREF(class_description,(SI_Long)12L));
    SVREF(class_description,FIX((SI_Long)12L)) = Nil;
    reclaim_byte_vector(ISVREF(class_description,(SI_Long)19L));
    SVREF(class_description,FIX((SI_Long)19L)) = Nil;
    reclaim_class_export_information_if_any(ISVREF(class_description,
	    (SI_Long)21L));
    SVREF(class_description,FIX((SI_Long)21L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    temp = Chain_of_available_class_descriptions;
    SVREF(class_description,FIX((SI_Long)0L)) = temp;
    Chain_of_available_class_descriptions = class_description;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLASS-DESCRIPTION */
Object reclaim_structure_for_class_description(class_description)
    Object class_description;
{
    x_note_fn_call(80,41);
    return reclaim_class_description_1(class_description);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* MAKE-PERMANENT-CLASS-DESCRIPTION-STRUCTURE-INTERNAL */
Object make_permanent_class_description_structure_internal()
{
    Object def_structure_class_description_variable;
    Object class_description_count_new_value;
    Object defstruct_g2_class_description_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,42);
    def_structure_class_description_variable = Nil;
    class_description_count_new_value = FIXNUM_ADD1(Class_description_count);
    Class_description_count = class_description_count_new_value;
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
    Object def_structure_class_description_variable;

    x_note_fn_call(80,43);
    def_structure_class_description_variable = 
	    Chain_of_available_class_descriptions;
    if (def_structure_class_description_variable) {
	Chain_of_available_class_descriptions = 
		ISVREF(def_structure_class_description_variable,(SI_Long)0L);
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
    x_note_fn_call(80,44);
    return VALUES_1(SVREF(class_description,FIX((SI_Long)2L)) = 
	    class_inheritance_path);
}

/* CLASS-FEATURES-FUNCTION */
Object class_features_function(class_description,class_features)
    Object class_description, class_features;
{
    x_note_fn_call(80,45);
    return VALUES_1(SVREF(class_description,FIX((SI_Long)12L)) = 
	    class_features);
}

/* SLOT-DESCRIPTIONS-FUNCTION */
Object slot_descriptions_function(class_description,slot_descriptions)
    Object class_description, slot_descriptions;
{
    x_note_fn_call(80,46);
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

    x_note_fn_call(80,47);
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

    x_note_fn_call(80,48);
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons, global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(80,49);
    if (SYMBOLP(x)) {
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = x;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(x) & IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    gensymed_symbol = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	gensymed_symbol = Qnil;
      end_2:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = x;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
	gensymed_symbol_2 = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_3:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_3;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_properties = M_CDR(M_CAR(gensymed_symbol));
		goto end_3;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	    kb_properties = Qnil;
	  end_3:;
	    goto end_4;
	}
	goto next_loop_2;
      end_loop_2:
	kb_properties = Qnil;
      end_4:;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    gensymed_symbol = CDR(kb_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_4:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_4;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_5:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_5;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_5;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_5;
	      end_loop_5:
		kb_specific_value = Qnil;
	      end_5:;
		goto end_6;
	    }
	    goto next_loop_4;
	  end_loop_4:
	    kb_specific_value = Qnil;
	  end_6:;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_6:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_6;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_7:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_7;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    resulting_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_7;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_7;
	      end_loop_7:
		resulting_value = Qnil;
	      end_7:;
		goto end_8;
	    }
	    goto next_loop_6;
	  end_loop_6:
	    resulting_value = Qnil;
	  end_8:;
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

    x_note_fn_call(80,50);
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

    x_note_fn_call(80,51);
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

    x_note_fn_call(80,52);
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

    x_note_fn_call(80,53);
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

    x_note_fn_call(80,54);
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

Object Loading_kb_p = UNBOUND;

static Object Kfuncall;            /* :funcall */

/* SLOT-INIT-FORM-NEEDS-EVALUATION? */
Object slot_init_form_needs_evaluation_qm(slot_init_form)
    Object slot_init_form;
{
    x_note_fn_call(80,55);
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
    x_note_fn_call(80,56);
    return VALUES_1(Nil);
}

Object Class_is_undergoing_inheritance_change_qm = UNBOUND;

/* UNIQUE-SLOT-NAME-EQ */
Object unique_slot_name_eq(x,slot_description)
    Object x, slot_description;
{
    x_note_fn_call(80,57);
    return VALUES_1(EQ(x,ISVREF(slot_description,(SI_Long)1L)) ? T : Nil);
}

/* GET-SLOT-DESCRIPTION-OF-CLASS-DESCRIPTION-FUNCTION */
Object get_slot_description_of_class_description_function(slot_name,
	    class_description,qualifying_class_qm)
    Object slot_name, class_description, qualifying_class_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons, global_properties, kb_properties, kb_specific_value;
    Object resulting_value, qualifying_class_description_qm;
    Object qualifying_class_full_hash_table_class, path_class_description;
    Object existing_class_description_path_arg, class_description_arg, class_1;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object class_name, slot_description_qm, unique_slot_name_key_qm;
    Object slot_description_to_return_qm, gathered_slot_descriptions_qm;
    Object full_hash_table_class, last_1, next_qm, cdr_new_value, unique_name;
    Object gathered_slot_description, gathered_slot_description_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(80,58);
    if ( !TRUEP(class_description))
	return VALUES_1(Nil);
    if (Class_is_undergoing_inheritance_change_qm)
	return get_slot_description(3,slot_name,ISVREF(class_description,
		(SI_Long)6L),qualifying_class_qm);
    if (qualifying_class_qm) {
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = qualifying_class_qm;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(qualifying_class_qm) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    gensymed_symbol = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	gensymed_symbol = Qnil;
      end_2:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = qualifying_class_qm;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
	gensymed_symbol_2 = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_3:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_3;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_properties = M_CDR(M_CAR(gensymed_symbol));
		goto end_3;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	    kb_properties = Qnil;
	  end_3:;
	    goto end_4;
	}
	goto next_loop_2;
      end_loop_2:
	kb_properties = Qnil;
      end_4:;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    gensymed_symbol = CDR(kb_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_4:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_4;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_5:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_5;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_5;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_5;
	      end_loop_5:
		kb_specific_value = Qnil;
	      end_5:;
		goto end_6;
	    }
	    goto next_loop_4;
	  end_loop_4:
	    kb_specific_value = Qnil;
	  end_6:;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_6:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_6;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_7:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_7;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    resulting_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_7;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_7;
	      end_loop_7:
		resulting_value = Qnil;
	      end_7:;
		goto end_8;
	    }
	    goto next_loop_6;
	  end_loop_6:
	    resulting_value = Qnil;
	  end_8:;
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
	      next_loop_8:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_8;
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
		goto next_loop_8;
	      end_loop_8:
		goto end_9;
		ab_loopvar_ = Qnil;
	      end_9:;
		ab_loop_list_ = SVREF(class_description_arg,
			FIX((SI_Long)3L)) = ab_loopvar_;
	    }
	    else
		ab_loop_list_ = existing_class_description_path_arg;
	    class_name = Nil;
	    slot_description_qm = Nil;
	  next_loop_9:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_9;
	    path_class_description = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    class_name = ISVREF(path_class_description,(SI_Long)1L);
	    temp_1 = ISVREF(path_class_description,(SI_Long)9L);
	    gensymed_symbol = CDR(temp_1);
	    gensymed_symbol_1 = slot_name;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(slot_name) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_10:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_10;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_11:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_11;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    slot_description_qm = M_CDR(M_CAR(gensymed_symbol));
		    goto end_10;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_11;
	      end_loop_11:
		slot_description_qm = Qnil;
	      end_10:;
		goto end_11;
	    }
	    goto next_loop_10;
	  end_loop_10:
	    slot_description_qm = Qnil;
	  end_11:;
	    if (EQ(class_name,qualifying_class_full_hash_table_class)) {
		unique_slot_name_key_qm = slot_description_qm ? 
			ISVREF(slot_description_qm,(SI_Long)1L) : Nil;
		goto end_12;
	    }
	    else if (slot_description_qm && (EQ(ISVREF(slot_description_qm,
		    (SI_Long)3L),class_name) ||  
		    !TRUEP(ISVREF(slot_description_qm,(SI_Long)8L)) || 
		    EQ(slot_name,ISVREF(slot_description_qm,(SI_Long)1L)))) {
		unique_slot_name_key_qm = ISVREF(slot_description_qm,
			(SI_Long)1L);
		goto end_12;
	    }
	    goto next_loop_9;
	  end_loop_9:
	    unique_slot_name_key_qm = Qnil;
	  end_12:;
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
		    goto end_13;
		    ab_loopvar_ = Qnil;
		  end_13:;
		    ab_loop_list_ = SVREF(class_description_arg,
			    FIX((SI_Long)3L)) = ab_loopvar_;
		}
		else
		    ab_loop_list_ = existing_class_description_path_arg;
		slot_description_qm = Nil;
	      next_loop_13:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_13;
		path_class_description = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		temp_1 = ISVREF(path_class_description,(SI_Long)9L);
		gensymed_symbol = CDR(temp_1);
		gensymed_symbol_1 = unique_slot_name_key_qm;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(unique_slot_name_key_qm) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_14:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_14;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_15:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_15;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			slot_description_qm = M_CDR(M_CAR(gensymed_symbol));
			goto end_14;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_15;
		  end_loop_15:
		    slot_description_qm = Qnil;
		  end_14:;
		    goto end_15;
		}
		goto next_loop_14;
	      end_loop_14:
		slot_description_qm = Qnil;
	      end_15:;
		if (slot_description_qm) {
		    slot_description_to_return_qm = slot_description_qm;
		    goto end_16;
		}
		goto next_loop_13;
	      end_loop_13:
		slot_description_to_return_qm = Qnil;
	      end_16:;
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
	    goto end_17;
	    ab_loopvar_ = Qnil;
	  end_17:;
	    ab_loop_list_ = SVREF(class_description_arg,FIX((SI_Long)3L)) 
		    = ab_loopvar_;
	}
	else
	    ab_loop_list_ = existing_class_description_path_arg;
	class_name = Nil;
	slot_description_qm = Nil;
      next_loop_17:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_17;
	path_class_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_name = ISVREF(path_class_description,(SI_Long)1L);
	temp_1 = ISVREF(path_class_description,(SI_Long)9L);
	gensymed_symbol = CDR(temp_1);
	gensymed_symbol_1 = slot_name;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(slot_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_18:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_18;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_19:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_19;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		slot_description_qm = M_CDR(M_CAR(gensymed_symbol));
		goto end_18;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_19;
	  end_loop_19:
	    slot_description_qm = Qnil;
	  end_18:;
	    goto end_19;
	}
	goto next_loop_18;
      end_loop_18:
	slot_description_qm = Qnil;
      end_19:;
	if (EQ(class_name,full_hash_table_class) &&  
		!TRUEP(slot_description_qm)) {
	    slot_description_to_return_qm = Nil;
	    goto end_20;
	}
	else if (slot_description_qm) {
	    if (EQ(slot_name,ISVREF(slot_description_qm,(SI_Long)1L)) ||  
		    !TRUEP(ISVREF(slot_description_qm,(SI_Long)8L))) {
		if (gathered_slot_descriptions_qm) {
		    last_1 = gathered_slot_descriptions_qm;
		    next_qm = Nil;
		  next_loop_20:
		    next_qm = M_CDR(last_1);
		    if ( !TRUEP(next_qm))
			goto end_loop_20;
		    inline_note_reclaim_cons(last_1,Qab_gensym);
		    last_1 = next_qm;
		    goto next_loop_20;
		  end_loop_20:
		    inline_note_reclaim_cons(last_1,Qab_gensym);
		    cdr_new_value = Available_gensym_conses;
		    M_CDR(last_1) = cdr_new_value;
		    Available_gensym_conses = gathered_slot_descriptions_qm;
		}
		gathered_slot_descriptions_qm = Nil;
		slot_description_to_return_qm = slot_description_qm;
		goto end_20;
	    }
	    else if (EQ(class_name,full_hash_table_class) || 
		    EQ(ISVREF(slot_description_qm,(SI_Long)3L),class_name)) {
		gathered_slot_descriptions_qm = 
			nreverse(gathered_slot_descriptions_qm);
		unique_name = ISVREF(slot_description_qm,(SI_Long)1L);
		gathered_slot_description = Nil;
		ab_loop_list_ = gathered_slot_descriptions_qm;
	      next_loop_21:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_21;
		gathered_slot_description = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (EQ(ISVREF(gathered_slot_description,(SI_Long)1L),
			unique_name)) {
		    gathered_slot_description_qm = gathered_slot_description;
		    goto end_21;
		}
		goto next_loop_21;
	      end_loop_21:
		gathered_slot_description_qm = Qnil;
	      end_21:;
		if (gathered_slot_description_qm) {
		    if (gathered_slot_descriptions_qm) {
			last_1 = gathered_slot_descriptions_qm;
			next_qm = Nil;
		      next_loop_22:
			next_qm = M_CDR(last_1);
			if ( !TRUEP(next_qm))
			    goto end_loop_22;
			inline_note_reclaim_cons(last_1,Qab_gensym);
			last_1 = next_qm;
			goto next_loop_22;
		      end_loop_22:
			inline_note_reclaim_cons(last_1,Qab_gensym);
			cdr_new_value = Available_gensym_conses;
			M_CDR(last_1) = cdr_new_value;
			Available_gensym_conses = 
				gathered_slot_descriptions_qm;
		    }
		    slot_description_to_return_qm = 
			    gathered_slot_description_qm;
		    goto end_20;
		}
		else {
		    if (gathered_slot_descriptions_qm) {
			last_1 = gathered_slot_descriptions_qm;
			next_qm = Nil;
		      next_loop_23:
			next_qm = M_CDR(last_1);
			if ( !TRUEP(next_qm))
			    goto end_loop_23;
			inline_note_reclaim_cons(last_1,Qab_gensym);
			last_1 = next_qm;
			goto next_loop_23;
		      end_loop_23:
			inline_note_reclaim_cons(last_1,Qab_gensym);
			cdr_new_value = Available_gensym_conses;
			M_CDR(last_1) = cdr_new_value;
			Available_gensym_conses = 
				gathered_slot_descriptions_qm;
		    }
		    slot_description_to_return_qm = slot_description_qm;
		    goto end_20;
		}
	    }
	    else {
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol) = slot_description_qm;
		M_CDR(gensymed_symbol) = gathered_slot_descriptions_qm;
		inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
		gathered_slot_descriptions_qm = gensymed_symbol;
	    }
	}
	goto next_loop_17;
      end_loop_17:
	if (gathered_slot_descriptions_qm) {
	    last_1 = gathered_slot_descriptions_qm;
	    next_qm = Nil;
	  next_loop_24:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_24;
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    last_1 = next_qm;
	    goto next_loop_24;
	  end_loop_24:
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    cdr_new_value = Available_gensym_conses;
	    M_CDR(last_1) = cdr_new_value;
	    Available_gensym_conses = gathered_slot_descriptions_qm;
	}
	slot_description_to_return_qm = Nil;
	goto end_20;
	slot_description_to_return_qm = Qnil;
      end_20:;
	return VALUES_1(slot_description_to_return_qm);
    }
    return VALUES_1(temp_1);
}

/* GET-SLOT-DESCRIPTION-FROM-CLASS */
Object get_slot_description_from_class varargs_1(int, n)
{
    Object class_1, unique_or_pretty_slot_name;
    Object class_if_specific_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_4, temp, temp_1, new_cons, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    Declare_varargs_nonrelocating;

    x_note_fn_call(80,59);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    unique_or_pretty_slot_name = REQUIRED_ARG_nonrelocating();
    class_if_specific_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = CDR(Symbol_properties_table);
    gensymed_symbol_1 = class_1;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    gensymed_symbol = Qnil;
  end_2:;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_1;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,T,
		gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    gensymed_symbol = CDR(global_properties);
    gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
    gensymed_symbol_2 = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop_2:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_2;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    kb_properties = M_CDR(M_CAR(gensymed_symbol));
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	kb_properties = Qnil;
      end_3:;
	goto end_4;
    }
    goto next_loop_2;
  end_loop_2:
    kb_properties = Qnil;
  end_4:;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	gensymed_symbol = CDR(kb_properties);
	gensymed_symbol_1 = Class_description_gkbprop;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_4:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_4;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_5:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_5;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		goto end_5;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_5;
	  end_loop_5:
	    kb_specific_value = Qnil;
	  end_5:;
	    goto end_6;
	}
	goto next_loop_4;
      end_loop_4:
	kb_specific_value = Qnil;
      end_6:;
	if (kb_specific_value);
	else
	    kb_specific_value = No_specific_property_value;
    }
    else
	kb_specific_value = No_specific_property_value;
    if ( !EQ(kb_specific_value,No_specific_property_value))
	resulting_value = kb_specific_value;
    else {
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Class_description_gkbprop;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_6:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_6;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_7:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_7;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		resulting_value = M_CDR(M_CAR(gensymed_symbol));
		goto end_7;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_7;
	  end_loop_7:
	    resulting_value = Qnil;
	  end_7:;
	    goto end_8;
	}
	goto next_loop_6;
      end_loop_6:
	resulting_value = Qnil;
      end_8:;
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

    x_note_fn_call(80,60);
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

    x_note_fn_call(80,61);
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

    x_note_fn_call(80,62);
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
    Object class_description_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_4, temp, temp_1, new_cons, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;

    x_note_fn_call(80,63);
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
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = defining_class;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(defining_class) & 
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
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:
	    gensymed_symbol = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_2:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = defining_class;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
	gensymed_symbol_2 = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_4:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_4;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_properties = M_CDR(M_CAR(gensymed_symbol));
		goto end_3;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_4;
	  end_loop_4:
	    kb_properties = Qnil;
	  end_3:;
	    goto end_4;
	}
	goto next_loop_3;
      end_loop_3:
	kb_properties = Qnil;
      end_4:;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    gensymed_symbol = CDR(kb_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_5:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_5;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_6:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_6;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_5;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_6;
	      end_loop_6:
		kb_specific_value = Qnil;
	      end_5:;
		goto end_6;
	    }
	    goto next_loop_5;
	  end_loop_5:
	    kb_specific_value = Qnil;
	  end_6:;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_7:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_7;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_8:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_8;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    resulting_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_7;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_8;
	      end_loop_8:
		resulting_value = Qnil;
	      end_7:;
		goto end_8;
	    }
	    goto next_loop_7;
	  end_loop_7:
	    resulting_value = Qnil;
	  end_8:;
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

    x_note_fn_call(80,64);
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
    Object new_cons, gensymed_symbol, hash_table, slot_description;
    Object ab_loop_list_, unique_slot_name, defining_class;
    Object differs_from_superior_slot_description_qm, superior;
    Object ab_loop_list__1, superior_slot_description_qm, gensymed_symbol_1;
    Object gensymed_symbol_4, temp, temp_1, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, pretty_slot_name;
    Object existing_pretty_name_slot_description_qm, class_inheritance_path_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;

    x_note_fn_call(80,65);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qslot_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = superior;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(superior) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_3:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_3;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	    gensymed_symbol = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop_2;
      end_loop_2:
	gensymed_symbol = Qnil;
      end_2:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superior;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
	gensymed_symbol_2 = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_4:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_4;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_5:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_5;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_properties = M_CDR(M_CAR(gensymed_symbol));
		goto end_3;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_5;
	  end_loop_5:
	    kb_properties = Qnil;
	  end_3:;
	    goto end_4;
	}
	goto next_loop_4;
      end_loop_4:
	kb_properties = Qnil;
      end_4:;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    gensymed_symbol = CDR(kb_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_6:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_6;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_7:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_7;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_5;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_7;
	      end_loop_7:
		kb_specific_value = Qnil;
	      end_5:;
		goto end_6;
	    }
	    goto next_loop_6;
	  end_loop_6:
	    kb_specific_value = Qnil;
	  end_6:;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_8:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_8;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_9:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_9;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    resulting_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_7;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_9;
	      end_loop_9:
		resulting_value = Qnil;
	      end_7:;
		goto end_8;
	    }
	    goto next_loop_8;
	  end_loop_8:
	    resulting_value = Qnil;
	  end_8:;
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
	    goto end_9;
	}
	else {
	    differs_from_superior_slot_description_qm = T;
	    goto end_9;
	}
	differs_from_superior_slot_description_qm = Qnil;
      end_9:;
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
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(pretty_slot_name) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_10:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_10;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_11:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_11;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    existing_pretty_name_slot_description_qm = 
			    M_CDR(M_CAR(gensymed_symbol));
		    goto end_10;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_11;
	      end_loop_11:
		existing_pretty_name_slot_description_qm = Qnil;
	      end_10:;
		goto end_11;
	    }
	    goto next_loop_10;
	  end_loop_10:
	    existing_pretty_name_slot_description_qm = Qnil;
	  end_11:;
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
    Object new_cons, gensymed_symbol, hash_table, slot_description;
    Object ab_loop_list_, temp, pretty_slot_name, gensymed_symbol_1;
    Object gensymed_symbol_4, current_slot_value_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(80,66);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qslot_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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
    x_note_fn_call(80,67);
    return reclaim_gensym_list_1(list_1);
}

Object Class_bit_numbers_pool = UNBOUND;

/* NORMALIZE-FEATURES */
Object normalize_features(features)
    Object features;
{
    Object feature, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(80,68);
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

    x_note_fn_call(80,69);
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

    x_note_fn_call(80,70);
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

    x_note_fn_call(80,71);
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

static Object Qdrawing_parameters;  /* drawing-parameters */

static Object Qpreviously_put_in_attribute_tables;  /* previously-put-in-attribute-tables */

/* ATTRIBUTE-PREVIOUSLY-PUT-IN-ATTRIBUTE-TABLES-P */
Object attribute_previously_put_in_attribute_tables_p varargs_1(int, n)
{
    Object attribute;
    Object class_qm, slot_name_or_alias, class_or_frame_qm;
    Object unaliased_attribute, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_4, temp, temp_1, new_cons, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object slot_description_qm, ab_loop_list_;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    Declare_varargs_nonrelocating;

    x_note_fn_call(80,72);
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
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = unaliased_attribute;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(unaliased_attribute) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    gensymed_symbol = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	gensymed_symbol = Qnil;
      end_2:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = unaliased_attribute;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
	gensymed_symbol_2 = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_3:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_3;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_properties = M_CDR(M_CAR(gensymed_symbol));
		goto end_3;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	    kb_properties = Qnil;
	  end_3:;
	    goto end_4;
	}
	goto next_loop_2;
      end_loop_2:
	kb_properties = Qnil;
      end_4:;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    gensymed_symbol = CDR(kb_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_4:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_4;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_5:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_5;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_5;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_5;
	      end_loop_5:
		kb_specific_value = Qnil;
	      end_5:;
		goto end_6;
	    }
	    goto next_loop_4;
	  end_loop_4:
	    kb_specific_value = Qnil;
	  end_6:;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_6:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_6;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_7:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_7;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    resulting_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_7;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_7;
	      end_loop_7:
		resulting_value = Qnil;
	      end_7:;
		goto end_8;
	    }
	    goto next_loop_6;
	  end_loop_6:
	    resulting_value = Qnil;
	  end_8:;
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
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = Qclass_definition;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(Qclass_definition) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_8:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_8;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_9:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_9;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_9;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_9;
	  end_loop_9:
	    gensymed_symbol = Qnil;
	  end_9:;
	    goto end_10;
	}
	goto next_loop_8;
      end_loop_8:
	gensymed_symbol = Qnil;
      end_10:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = Qclass_definition;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
	gensymed_symbol_2 = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_10:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_10;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_11:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_11;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_properties = M_CDR(M_CAR(gensymed_symbol));
		goto end_11;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_11;
	  end_loop_11:
	    kb_properties = Qnil;
	  end_11:;
	    goto end_12;
	}
	goto next_loop_10;
      end_loop_10:
	kb_properties = Qnil;
      end_12:;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    gensymed_symbol = CDR(kb_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_12:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_12;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_13:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_13;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_13;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_13;
	      end_loop_13:
		kb_specific_value = Qnil;
	      end_13:;
		goto end_14;
	    }
	    goto next_loop_12;
	  end_loop_12:
	    kb_specific_value = Qnil;
	  end_14:;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = Class_description_gkbprop;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_14:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_14;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_15:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_15;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    resulting_value = M_CDR(M_CAR(gensymed_symbol));
		    goto end_15;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_15;
	      end_loop_15:
		resulting_value = Qnil;
	      end_15:;
		goto end_16;
	    }
	    goto next_loop_14;
	  end_loop_14:
	    resulting_value = Qnil;
	  end_16:;
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
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = Qobject_definition;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qobject_definition) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_16:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_16;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_17:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_17;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_17;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_17;
	      end_loop_17:
		gensymed_symbol = Qnil;
	      end_17:;
		goto end_18;
	    }
	    goto next_loop_16;
	  end_loop_16:
	    gensymed_symbol = Qnil;
	  end_18:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qobject_definition;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,
			Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_18:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_18;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_19:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_19;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_19;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_19;
	      end_loop_19:
		kb_properties = Qnil;
	      end_19:;
		goto end_20;
	    }
	    goto next_loop_18;
	  end_loop_18:
	    kb_properties = Qnil;
	  end_20:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_20:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_20;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_21:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_21;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_21;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_21;
		  end_loop_21:
		    kb_specific_value = Qnil;
		  end_21:;
		    goto end_22;
		}
		goto next_loop_20;
	      end_loop_20:
		kb_specific_value = Qnil;
	      end_22:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_22:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_22;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_23:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_23;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_23;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_23;
		  end_loop_23:
		    resulting_value = Qnil;
		  end_23:;
		    goto end_24;
		}
		goto next_loop_22;
	      end_loop_22:
		resulting_value = Qnil;
	      end_24:;
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
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = Qblock;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qblock) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_24:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_24;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_25:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_25;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_25;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_25;
	      end_loop_25:
		gensymed_symbol = Qnil;
	      end_25:;
		goto end_26;
	    }
	    goto next_loop_24;
	  end_loop_24:
	    gensymed_symbol = Qnil;
	  end_26:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qblock;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,
			Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_26:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_26;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_27:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_27;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_27;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_27;
	      end_loop_27:
		kb_properties = Qnil;
	      end_27:;
		goto end_28;
	    }
	    goto next_loop_26;
	  end_loop_26:
	    kb_properties = Qnil;
	  end_28:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_28:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_28;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_29:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_29;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_29;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_29;
		  end_loop_29:
		    kb_specific_value = Qnil;
		  end_29:;
		    goto end_30;
		}
		goto next_loop_28;
	      end_loop_28:
		kb_specific_value = Qnil;
	      end_30:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_30:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_30;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_31:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_31;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_31;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_31;
		  end_loop_31:
		    resulting_value = Qnil;
		  end_31:;
		    goto end_32;
		}
		goto next_loop_30;
	      end_loop_30:
		resulting_value = Qnil;
	      end_32:;
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
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = Qdrawing_parameters;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qdrawing_parameters) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_32:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_32;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_33:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_33;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_33;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_33;
	      end_loop_33:
		gensymed_symbol = Qnil;
	      end_33:;
		goto end_34;
	    }
	    goto next_loop_32;
	  end_loop_32:
	    gensymed_symbol = Qnil;
	  end_34:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qdrawing_parameters;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,
			Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_34:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_34;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_35:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_35;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_35;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_35;
	      end_loop_35:
		kb_properties = Qnil;
	      end_35:;
		goto end_36;
	    }
	    goto next_loop_34;
	  end_loop_34:
	    kb_properties = Qnil;
	  end_36:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_36:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_36;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_37:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_37;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_37;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_37;
		  end_loop_37:
		    kb_specific_value = Qnil;
		  end_37:;
		    goto end_38;
		}
		goto next_loop_36;
	      end_loop_36:
		kb_specific_value = Qnil;
	      end_38:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_38:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_38;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_39:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_39;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_39;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_39;
		  end_loop_39:
		    resulting_value = Qnil;
		  end_39:;
		    goto end_40;
		}
		goto next_loop_38;
	      end_loop_38:
		resulting_value = Qnil;
	      end_40:;
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
      next_loop_40:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_40;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		Qpreviously_put_in_attribute_tables))
	    return VALUES_1(gensymed_symbol);
	goto next_loop_40;
      end_loop_40:
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

    x_note_fn_call(80,73);
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

    x_note_fn_call(80,74);
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

    x_note_fn_call(80,75);
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

    x_note_fn_call(80,76);
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

    x_note_fn_call(80,77);
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

    x_note_fn_call(80,78);
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons, global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description, svref_new_value;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(80,79);
    gensymed_symbol = CDR(Symbol_properties_table);
    gensymed_symbol_1 = class_1;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    gensymed_symbol = Qnil;
  end_2:;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_1;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,T,
		gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    gensymed_symbol = CDR(global_properties);
    gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
    gensymed_symbol_2 = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop_2:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_2;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    kb_properties = M_CDR(M_CAR(gensymed_symbol));
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	kb_properties = Qnil;
      end_3:;
	goto end_4;
    }
    goto next_loop_2;
  end_loop_2:
    kb_properties = Qnil;
  end_4:;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	gensymed_symbol = CDR(kb_properties);
	gensymed_symbol_1 = Class_description_gkbprop;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_4:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_4;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_5:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_5;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		goto end_5;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_5;
	  end_loop_5:
	    kb_specific_value = Qnil;
	  end_5:;
	    goto end_6;
	}
	goto next_loop_4;
      end_loop_4:
	kb_specific_value = Qnil;
      end_6:;
	if (kb_specific_value);
	else
	    kb_specific_value = No_specific_property_value;
    }
    else
	kb_specific_value = No_specific_property_value;
    if ( !EQ(kb_specific_value,No_specific_property_value))
	resulting_value = kb_specific_value;
    else {
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Class_description_gkbprop;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_6:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_6;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_7:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_7;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		resulting_value = M_CDR(M_CAR(gensymed_symbol));
		goto end_7;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_7;
	  end_loop_7:
	    resulting_value = Qnil;
	  end_7:;
	    goto end_8;
	}
	goto next_loop_6;
      end_loop_6:
	resulting_value = Qnil;
      end_8:;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    slot_description = 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    gensymed_symbol,Nil);
    reclaim_slot_value(ISVREF(slot_description,(SI_Long)6L));
    svref_new_value = copy_for_slot_value(new_value);
    return VALUES_1(SVREF(slot_description,FIX((SI_Long)6L)) = 
	    svref_new_value);
}

void frames1_INIT()
{
    Object temp, reclaim_structure_for_slot_description_1;
    Object reclaim_structure_for_evaluator_slot_info_1;
    Object reclaim_structure_for_class_description_1;
    Object Qclass_slot_description_updater, AB_package, Qslot_putter;
    Object list_constant_5, Qlocal_name_or_names, Qformat_override;
    Object Qattribute_export_comment, Qnote_slot_changes, Qselect_changes;
    Object Qdo_not_clone, Qedit_only, Qnot_user_editable, Qclass_slot;
    Object Quser_overridable, Qdo_not_put_in_attribute_tables_if_null;
    Object list_constant_4, list_constant_3, list_constant_2;
    Object Qdo_not_put_in_attribute_tables;
    Object Qdo_not_identify_in_attribute_tables, Qclass_of_optional_subframe;
    Object Qdo_not_save, Qsave, Qno_accessor, Qnot_ent, Qnot_nupec, Qnupec;
    Object list_constant_1, Qnot_normally_transient, Qclass_export_comment;
    Object Qonly_compatible_with, Qdisjoint_from, Qhas_indexed_attributes;
    Object Qattribute_displays, Qstubs, Qfoundation_class;
    Object Qnot_solely_instantiable, Qnot_user_instantiable;
    Object Qdo_not_put_in_menus, Qdefine_predicate;
    Object Qreclaim_frame_list_function, Qframes1, Qclass_bit_numbers_pool;
    Object Qslot_category, Qreclaim_structure;
    Object Qoutstanding_class_description_count;
    Object Qclass_description_structure_memory_usage, Qutilities2;
    Object Qclass_description_count, Qchain_of_available_class_descriptions;
    Object string_constant_9, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_8, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qevaluator_slot_info;
    Object Qoutstanding_evaluator_slot_info_count;
    Object Qevaluator_slot_info_structure_memory_usage;
    Object Qevaluator_slot_info_count;
    Object Qchain_of_available_evaluator_slot_infos, string_constant_7;
    Object string_constant_6, Qslot_description;
    Object Qoutstanding_slot_description_count;
    Object Qslot_description_structure_memory_usage, Qslot_description_count;
    Object Qchain_of_available_slot_descriptions, string_constant_5;
    Object string_constant_4, Qdefinition_state, Qinferior_classes;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_class_description_list_function;
    Object Qfunction_to_copy_global_value_for_this_property_name;
    Object Qcopy_list_using_class_description_conses_function;
    Object Qdirect_superior_classes, Qold_class_description;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qcopy_class_description, Qold_slot_name_assignment;
    Object Qslot_name_assignment, Qclasses_which_define, Qclass_methods;
    Object Qno_value, string_constant_3, Qclass_description_cons_memory_usage;
    Object Qoutstanding_class_description_conses;
    Object Qclass_description_cons_counter;
    Object Qavailable_class_description_conses_tail;
    Object Qavailable_class_description_conses;

    x_note_fn_call(80,80);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_class_description_conses = 
	    STATIC_SYMBOL("AVAILABLE-CLASS-DESCRIPTION-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_class_description_conses,
	    Available_class_description_conses);
    Qframes1 = STATIC_SYMBOL("FRAMES1",AB_package);
    record_system_variable(Qavailable_class_description_conses,Qframes1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_class_description_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-CLASS-DESCRIPTION-CONSES-TAIL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_class_description_conses_tail,
	    Available_class_description_conses_tail);
    record_system_variable(Qavailable_class_description_conses_tail,
	    Qframes1,Nil,Qnil,Qt,Qnil,Qnil);
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
    string_constant_3 = STATIC_STRING("1q83-MVy9k83-MUy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_class_description_conses);
    push_optimized_constant(Qclass_description_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
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
    string_constant_4 = 
	    STATIC_STRING("43Dy8m83nKy1n83nKy8n8k1l8n0000001l1n8y83-5vy0kzk0k0");
    temp = The_type_description_of_slot_description;
    The_type_description_of_slot_description = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_4));
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
    string_constant_5 = STATIC_STRING("1q83nKy8s83-ohy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_slot_description_count);
    push_optimized_constant(Qslot_description_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
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
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
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
    string_constant_6 = 
	    STATIC_STRING("43Dy8m83hDy1n83hDy8n8k1l8n0000000ksk0k0");
    temp = The_type_description_of_evaluator_slot_info;
    The_type_description_of_evaluator_slot_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
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
    string_constant_7 = STATIC_STRING("1q83hDy8s83-Spy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_evaluator_slot_info_count);
    push_optimized_constant(Qevaluator_slot_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
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
    string_constant_8 = 
	    STATIC_STRING("43Dy8m836fy1n836fy8n8k1l8n0000001l1n8y83-3Cy0k3Lyk0k0");
    temp = The_type_description_of_class_description;
    The_type_description_of_class_description = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
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
    string_constant_9 = STATIC_STRING("1q836fy8s83-MWy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_class_description_count);
    push_optimized_constant(Qclass_description_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
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
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
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
    list_constant_1 = STATIC_LIST((SI_Long)12L,Qdefine_predicate,
	    Qdo_not_put_in_menus,Qnot_user_instantiable,
	    Qnot_solely_instantiable,Qfoundation_class,Qstubs,
	    Qattribute_displays,Qhas_indexed_attributes,Qdisjoint_from,
	    Qonly_compatible_with,Qclass_export_comment,
	    Qnot_normally_transient);
    Global_class_features = list_constant_1;
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
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qdo_not_put_in_attribute_tables,Qnupec);
    Qnot_nupec = STATIC_SYMBOL("NOT-NUPEC",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,
	    Qdo_not_put_in_attribute_tables,Qnot_nupec);
    Qnot_ent = STATIC_SYMBOL("NOT-ENT",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,
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
    list_constant_5 = STATIC_LIST((SI_Long)26L,Qlookup_slot,Qvector_slot,
	    Qno_accessor,Qtype,Qsave,Qdo_not_save,Qsystem,
	    Qclass_of_optional_subframe,
	    Qdo_not_identify_in_attribute_tables,
	    Qdo_not_put_in_attribute_tables,list_constant_2,
	    list_constant_3,list_constant_4,
	    Qdo_not_put_in_attribute_tables_if_null,Quser_overridable,
	    Qclass_slot,Qnot_user_editable,Qedit_only,Qdo_not_clone,
	    Qselect_changes,Qnote_slot_changes,
	    Qpreviously_put_in_attribute_tables,Qattribute_export_comment,
	    Qnamelike_slot,Qformat_override,Qlocal_name_or_names);
    Global_slot_features = list_constant_5;
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
