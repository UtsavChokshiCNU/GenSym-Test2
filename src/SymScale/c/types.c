/* types.c
 * Input file:  types.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "types.h"


Object The_type_description_of_g2_list_element = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_g2_list_elements, Qchain_of_available_g2_list_elements);

DEFINE_VARIABLE_WITH_SYMBOL(G2_list_element_count, Qg2_list_element_count);

Object Chain_of_available_g2_list_elements_vector = UNBOUND;

/* G2-LIST-ELEMENT-STRUCTURE-MEMORY-USAGE */
Object g2_list_element_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,0);
    temp = G2_list_element_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-G2-LIST-ELEMENT-COUNT */
Object outstanding_g2_list_element_count()
{
    Object def_structure_g2_list_element_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,1);
    gensymed_symbol = IFIX(G2_list_element_count);
    def_structure_g2_list_element_variable = 
	    Chain_of_available_g2_list_elements;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_g2_list_element_variable))
	goto end_loop;
    def_structure_g2_list_element_variable = 
	    ISVREF(def_structure_g2_list_element_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-G2-LIST-ELEMENT-1 */
Object reclaim_g2_list_element_1(g2_list_element)
    Object g2_list_element;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,2);
    inline_note_reclaim_cons(g2_list_element,Nil);
    temp = ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(g2_list_element,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_g2_list_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = g2_list_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-G2-LIST-ELEMENT */
Object reclaim_structure_for_g2_list_element(g2_list_element)
    Object g2_list_element;
{
    x_note_fn_call(80,3);
    return reclaim_g2_list_element_1(g2_list_element);
}

/* MAKE-PERMANENT-G2-LIST-ELEMENT-STRUCTURE-INTERNAL */
Object make_permanent_g2_list_element_structure_internal()
{
    Object def_structure_g2_list_element_variable;
    Object defstruct_g2_g2_list_element_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,4);
    def_structure_g2_list_element_variable = Nil;
    atomic_incff_symval(Qg2_list_element_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_g2_list_element_variable = Nil;
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
	defstruct_g2_g2_list_element_variable = the_array;
	SVREF(defstruct_g2_g2_list_element_variable,FIX((SI_Long)0L)) = Nil;
	SVREF(defstruct_g2_g2_list_element_variable,FIX((SI_Long)1L)) = Nil;
	def_structure_g2_list_element_variable = 
		defstruct_g2_g2_list_element_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_g2_list_element_variable);
}

/* MAKE-G2-LIST-ELEMENT-1 */
Object make_g2_list_element_1(list_next_element,list_previous_element,
	    list_element_value,list_frame)
    Object list_next_element, list_previous_element, list_element_value;
    Object list_frame;
{
    Object def_structure_g2_list_element_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(80,5);
    def_structure_g2_list_element_variable = 
	    ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_g2_list_element_variable) {
	svref_arg_1 = Chain_of_available_g2_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_g2_list_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_g2_list_element_variable = 
		make_permanent_g2_list_element_structure_internal();
    inline_note_allocate_cons(def_structure_g2_list_element_variable,Nil);
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)2L)) = 
	    list_next_element;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)3L)) = 
	    list_previous_element;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)4L)) = 
	    list_element_value;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)5L)) = 
	    list_frame;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_g2_list_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    return VALUES_1(def_structure_g2_list_element_variable);
}

Object G2_list_structure_marker = UNBOUND;

/* READ-LIST-NODE */
Object read_list_node(reference)
    Object reference;
{
    Object reference_1, temp, temp_1, node, mark, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;
    Object result;

    x_note_fn_call(80,6);
    reference_1 = reference;
    temp = ATOMIC_REF_OBJECT(reference_1);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,node,mark);
    if ( !TRUEP(mark)) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = node;
	if ( !TRUEP(gensymed_symbol)) {
	    temp_1 = Nil;
	    goto end_1;
	}
      next_loop_1:
	gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	    goto end_2;
	goto next_loop_1;
      end_loop:
      end_2:
	if (EQ(gensymed_symbol,node)) {
	    temp_1 = gensymed_symbol;
	    goto end_1;
	}
	else
	    release_list_node(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CREATE-LIST-ELEMENT */
Object create_list_element(thing,outer_list)
    Object thing, outer_list;
{
    Object def_structure_g2_list_element_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value, node, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;

    x_note_fn_call(80,7);
    def_structure_g2_list_element_variable = 
	    ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_g2_list_element_variable) {
	svref_arg_1 = Chain_of_available_g2_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_g2_list_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_g2_list_element_variable = 
		make_permanent_g2_list_element_structure_internal();
    inline_note_allocate_cons(def_structure_g2_list_element_variable,Nil);
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)5L)) = 
	    outer_list;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_g2_list_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    node = def_structure_g2_list_element_variable;
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = node;
    if ( !TRUEP(gensymed_symbol)) {
	node = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,node)) {
	node = gensymed_symbol;
	goto end_1;
    }
    else
	release_list_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    node = Qnil;
  end_1:;
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop_2:
    gensymed_symbol = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_1 = FIXNUM_SUB1(gensymed_symbol);
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop_2;
    goto next_loop_2;
  end_loop_2:;
    SVREF(node,FIX((SI_Long)4L)) = thing;
    return VALUES_1(node);
}

/* RELEASE-LIST-NODE */
Object release_list_node(node)
    Object node;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, temp_1, temp_2;
    Object svref_arg_2;

    x_note_fn_call(80,8);
    if ( !TRUEP(node))
	return VALUES_1(Nil);
    temp = FIX((SI_Long)0L);
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop:
    gensymed_symbol = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_1 = FIX(IFIX(gensymed_symbol) - (SI_Long)2L);
    if ((SI_Long)0L == IFIX(gensymed_symbol_1))
	gensymed_symbol_1 = FIX((SI_Long)1L);
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp_1 = FIX(IFIX(FIXNUM_MINUS(gensymed_symbol,gensymed_symbol_1)) & 
	    (SI_Long)1L);
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    if (NUM_EQ(temp,temp_1))
	return VALUES_1(Nil);
    release_list_reference(node);
    inline_note_reclaim_cons(node,Nil);
    temp_2 = ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(node,FIX((SI_Long)0L)) = temp_2;
    temp_2 = Chain_of_available_g2_list_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp_2,svref_arg_2) = node;
    return VALUES_1(Nil);
}

Object G2_list_structure_head_marker = UNBOUND;

Object G2_list_structure_tail_marker = UNBOUND;

/* RELEASE-LIST-REFERENCE */
Object release_list_reference(node)
    Object node;
{
    x_note_fn_call(80,9);
    release_list_node(ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)3L)));
    return release_list_node(ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)2L)));
}

/* CREATE-EMPTY-G2-LIST-STRUCTURE */
Object create_empty_g2_list_structure()
{
    Object def_structure_g2_list_element_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value, new_list, head, tail, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(80,10);
    def_structure_g2_list_element_variable = 
	    ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_g2_list_element_variable) {
	svref_arg_1 = Chain_of_available_g2_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_g2_list_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_g2_list_element_variable = 
		make_permanent_g2_list_element_structure_internal();
    inline_note_allocate_cons(def_structure_g2_list_element_variable,Nil);
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)4L)) = 
	    G2_list_structure_marker;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_g2_list_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    new_list = def_structure_g2_list_element_variable;
    def_structure_g2_list_element_variable = 
	    ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_g2_list_element_variable) {
	svref_arg_1 = Chain_of_available_g2_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_g2_list_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_g2_list_element_variable = 
		make_permanent_g2_list_element_structure_internal();
    inline_note_allocate_cons(def_structure_g2_list_element_variable,Nil);
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)4L)) = 
	    G2_list_structure_head_marker;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_g2_list_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    head = def_structure_g2_list_element_variable;
    def_structure_g2_list_element_variable = 
	    ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_g2_list_element_variable) {
	svref_arg_1 = Chain_of_available_g2_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_g2_list_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_g2_list_element_variable = 
		make_permanent_g2_list_element_structure_internal();
    inline_note_allocate_cons(def_structure_g2_list_element_variable,Nil);
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)4L)) = 
	    G2_list_structure_tail_marker;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_g2_list_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_g2_list_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    tail = def_structure_g2_list_element_variable;
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = head;
    if ( !TRUEP(gensymed_symbol)) {
	head = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(head,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(head,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,head)) {
	head = gensymed_symbol;
	goto end_1;
    }
    else
	release_list_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    head = Qnil;
  end_1:;
    gensymed_symbol = Nil;
  next_loop_2:
    gensymed_symbol = tail;
    if ( !TRUEP(gensymed_symbol)) {
	tail = Nil;
	goto end_3;
    }
  next_loop_3:
    gensymed_symbol_1 = ISVREF(tail,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(tail,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_4;
    goto next_loop_3;
  end_loop_2:
  end_4:
    if (EQ(gensymed_symbol,tail)) {
	tail = gensymed_symbol;
	goto end_3;
    }
    else
	release_list_node(gensymed_symbol);
    goto next_loop_2;
  end_loop_3:
    tail = Qnil;
  end_3:;
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop_4:
    gensymed_symbol = ISVREF(head,(SI_Long)1L);
    gensymed_symbol_1 = FIXNUM_SUB1(gensymed_symbol);
    if (CAS_SVREF(head,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop_4;
    goto next_loop_4;
  end_loop_4:;
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop_5:
    gensymed_symbol = ISVREF(tail,(SI_Long)1L);
    gensymed_symbol_1 = FIXNUM_SUB1(gensymed_symbol);
    if (CAS_SVREF(tail,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop_5;
    goto next_loop_5;
  end_loop_5:;
    SVREF(new_list,FIX((SI_Long)2L)) = head;
    SVREF(new_list,FIX((SI_Long)3L)) = tail;
    initialize_g2_list_structure(new_list);
    return VALUES_1(new_list);
}

/* RECLAIM-EMPTY-G2-LIST-STRUCTURE */
Object reclaim_empty_g2_list_structure(g2_list_structure)
    Object g2_list_structure;
{
    Object head, tail, temp, svref_arg_2;

    x_note_fn_call(80,11);
    head = ISVREF(g2_list_structure,(SI_Long)2L);
    tail = ISVREF(g2_list_structure,(SI_Long)3L);
    inline_note_reclaim_cons(head,Nil);
    temp = ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(head,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_g2_list_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = head;
    inline_note_reclaim_cons(tail,Nil);
    temp = ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(tail,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_g2_list_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = tail;
    inline_note_reclaim_cons(g2_list_structure,Nil);
    temp = ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(g2_list_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_g2_list_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = g2_list_structure;
    return VALUES_1(Nil);
}

/* INITIALIZE-G2-LIST-STRUCTURE */
Object initialize_g2_list_structure(g2_list_structure)
    Object g2_list_structure;
{
    Object head, tail, svref_new_value;

    x_note_fn_call(80,12);
    head = ISVREF(g2_list_structure,(SI_Long)2L);
    tail = ISVREF(g2_list_structure,(SI_Long)3L);
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    SVREF(head,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = MAKE_ATOMIC_REF(Nil,(SI_Long)0L);
    SVREF(head,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = MAKE_ATOMIC_REF(Nil,(SI_Long)0L);
    SVREF(tail,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = MAKE_ATOMIC_REF(head,(SI_Long)0L);
    return VALUES_1(SVREF(tail,FIX((SI_Long)3L)) = svref_new_value);
}

/* HELP-DELETE-LIST-NODE */
Object help_delete_list_node(node)
    Object node;
{
    Object link1, temp_1, lastlink_deleted_qm, reference, reference_1, node_1;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, prev, next;
    Object backoff_limit, next2, prev2, temp_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(80,13);
    link1 = Nil;
  next_loop:
    link1 = ISVREF(node,(SI_Long)3L);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(link1);
    if (temp);
    else {
	temp_1 = link1;
	temp = TRUEP(CAS_SVREF(node,(SI_Long)3L,temp_1,
		MAKE_ATOMIC_REF(ATOMIC_REF_OBJECT(link1),(SI_Long)355L)));
    }
    if (temp)
	goto end_loop;
    goto next_loop;
  end_loop:;
    lastlink_deleted_qm = T;
    reference = ISVREF(node,(SI_Long)3L);
    reference_1 = reference;
    temp_1 = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node_1 = temp_1;
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
  end_loop_1:
  end_2:
    if (EQ(gensymed_symbol,node_1))
	goto end_1;
    else
	release_list_node(gensymed_symbol);
    goto next_loop_1;
  end_loop_2:
  end_1:;
    prev = node_1;
    reference = ISVREF(node,(SI_Long)2L);
    reference_1 = reference;
    temp_1 = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node_1 = temp_1;
    gensymed_symbol = Nil;
  next_loop_3:
    gensymed_symbol = node_1;
    if ( !TRUEP(gensymed_symbol))
	goto end_3;
  next_loop_4:
    gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_4;
    goto next_loop_4;
  end_loop_3:
  end_4:
    if (EQ(gensymed_symbol,node_1))
	goto end_3;
    else
	release_list_node(gensymed_symbol);
    goto next_loop_3;
  end_loop_4:
  end_3:;
    next = node_1;
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_5:
      if (EQ(prev,next))
	  goto end_loop_5;
      if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(next,(SI_Long)2L))) {
	  reference = ISVREF(next,(SI_Long)2L);
	  reference_1 = reference;
	  temp_1 = ATOMIC_REF_OBJECT(reference_1);
	  (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	  node_1 = temp_1;
	  gensymed_symbol = Nil;
	next_loop_6:
	  gensymed_symbol = node_1;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_5;
	next_loop_7:
	  gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		  gensymed_symbol_2))
	      goto end_6;
	  goto next_loop_7;
	end_loop_6:
	end_6:
	  if (EQ(gensymed_symbol,node_1))
	      goto end_5;
	  else
	      release_list_node(gensymed_symbol);
	  goto next_loop_6;
	end_loop_7:
	end_5:;
	  next2 = node_1;
	  release_list_node(next);
	  next = next2;
      }
      else {
	  prev2 = read_list_node(ISVREF(prev,(SI_Long)2L));
	  if ( !TRUEP(prev2)) {
	      if ( !TRUEP(lastlink_deleted_qm)) {
		  help_delete_list_node(prev);
		  lastlink_deleted_qm = T;
	      }
	      reference = ISVREF(prev,(SI_Long)3L);
	      reference_1 = reference;
	      temp_1 = ATOMIC_REF_OBJECT(reference_1);
	      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	      node_1 = temp_1;
	      gensymed_symbol = Nil;
	    next_loop_8:
	      gensymed_symbol = node_1;
	      if ( !TRUEP(gensymed_symbol))
		  goto end_7;
	    next_loop_9:
	      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_8;
	      goto next_loop_9;
	    end_loop_8:
	    end_8:
	      if (EQ(gensymed_symbol,node_1))
		  goto end_7;
	      else
		  release_list_node(gensymed_symbol);
	      goto next_loop_8;
	    end_loop_9:
	    end_7:;
	      prev2 = node_1;
	      release_list_node(prev);
	      prev = prev2;
	  }
	  else if ( !EQ(prev2,node)) {
	      lastlink_deleted_qm = Nil;
	      release_list_node(prev);
	      prev = prev2;
	  }
	  else {
	      release_list_node(prev2);
	      temp_1 = prev;
	      temp_2 = MAKE_ATOMIC_REF(node,(SI_Long)0L);
	      if (CAS_SVREF(temp_1,(SI_Long)2L,temp_2,MAKE_ATOMIC_REF(next,
		      (SI_Long)0L))) {
		  gensymed_symbol = Nil;
		next_loop_10:
		  gensymed_symbol = next;
		  if ( !TRUEP(gensymed_symbol))
		      goto end_9;
		next_loop_11:
		  gensymed_symbol_1 = ISVREF(next,(SI_Long)1L);
		  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
		  if (CAS_SVREF(next,(SI_Long)1L,gensymed_symbol_1,
			  gensymed_symbol_2))
		      goto end_10;
		  goto next_loop_11;
		end_loop_10:
		end_10:
		  if (EQ(gensymed_symbol,next))
		      goto end_9;
		  else
		      release_list_node(gensymed_symbol);
		  goto next_loop_10;
		end_loop_11:
		end_9:;
		  release_list_node(node);
		  goto end_loop_5;
	      }
	      back_off();
	  }
      }
      goto next_loop_5;
    end_loop_5:
      release_list_node(prev);
      release_list_node(next);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HELP-INSERT-LIST-NODE */
Object help_insert_list_node(prev,node)
    Object prev, node;
{
    Object backoff_limit, lastlink_deleted_qm, prev2, reference, reference_1;
    Object temp, node_1, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object link1;
    Declare_special(1);

    x_note_fn_call(80,14);
    backoff_limit = Backoff_min_delay;
    lastlink_deleted_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
      prev2 = Nil;
    next_loop:
      prev2 = read_list_node(ISVREF(prev,(SI_Long)2L));
      if ( !TRUEP(prev2)) {
	  if ( !TRUEP(lastlink_deleted_qm)) {
	      help_delete_list_node(prev);
	      lastlink_deleted_qm = T;
	  }
	  reference = ISVREF(prev,(SI_Long)3L);
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
	  if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		  gensymed_symbol_2))
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
	  prev2 = node_1;
	  release_list_node(prev);
	  prev = prev2;
      }
      else {
	  link1 = ISVREF(node,(SI_Long)3L);
	  if ((SI_Long)355L == ATOMIC_REF_STAMP(link1)) {
	      release_list_node(prev2);
	      temp = prev;
	      goto end_3;
	  }
	  if ( !EQ(prev2,node)) {
	      lastlink_deleted_qm = Nil;
	      release_list_node(prev);
	      prev = prev2;
	  }
	  else {
	      release_list_node(prev2);
	      if (CAS_SVREF(node,(SI_Long)3L,link1,MAKE_ATOMIC_REF(prev,
		      (SI_Long)0L))) {
		  gensymed_symbol = Nil;
		next_loop_3:
		  gensymed_symbol = prev;
		  if ( !TRUEP(gensymed_symbol))
		      goto end_4;
		next_loop_4:
		  gensymed_symbol_1 = ISVREF(prev,(SI_Long)1L);
		  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
		  if (CAS_SVREF(prev,(SI_Long)1L,gensymed_symbol_1,
			  gensymed_symbol_2))
		      goto end_5;
		  goto next_loop_4;
		end_loop_2:
		end_5:
		  if (EQ(gensymed_symbol,prev))
		      goto end_4;
		  else
		      release_list_node(gensymed_symbol);
		  goto next_loop_3;
		end_loop_3:
		end_4:;
		  release_list_node(ATOMIC_REF_OBJECT(link1));
		  if ( !((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(prev,
			  (SI_Long)3L)))) {
		      temp = prev;
		      goto end_3;
		  }
	      }
	      back_off();
	  }
      }
      goto next_loop;
    end_loop_4:
      temp = Qnil;
    end_3:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* REMOVE-LIST-CROSS-REFERENCE */
Object remove_list_cross_reference(node)
    Object node;
{
    Object prev, reference, reference_1, temp, node_1, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, prev2, svref_new_value, next;
    Object next2;

    x_note_fn_call(80,15);
    prev = Nil;
  next_loop:
    prev = ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)3L));
    if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(prev,(SI_Long)2L))) {
	reference = ISVREF(prev,(SI_Long)3L);
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
	prev2 = node_1;
	svref_new_value = MAKE_ATOMIC_REF(prev2,(SI_Long)355L);
	SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
	release_list_node(prev);
    }
    else {
	next = ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)2L));
	if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(next,(SI_Long)2L))) {
	    reference = ISVREF(next,(SI_Long)2L);
	    reference_1 = reference;
	    temp = ATOMIC_REF_OBJECT(reference_1);
	    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	    node_1 = temp;
	    gensymed_symbol = Nil;
	  next_loop_3:
	    gensymed_symbol = node_1;
	    if ( !TRUEP(gensymed_symbol))
		goto end_3;
	  next_loop_4:
	    gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	    if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		    gensymed_symbol_2))
		goto end_4;
	    goto next_loop_4;
	  end_loop_2:
	  end_4:
	    if (EQ(gensymed_symbol,node_1))
		goto end_3;
	    else
		release_list_node(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	  end_3:;
	    next2 = node_1;
	    svref_new_value = MAKE_ATOMIC_REF(next2,(SI_Long)355L);
	    SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	    release_list_node(next);
	}
	else
	    goto end_loop_4;
    }
    goto next_loop;
  end_loop_4:;
    return VALUES_1(Nil);
}

/* G2-LIST-STRUCTURE-NEXT */
Object g2_list_structure_next(cursor,g2_list_structure)
    Object cursor, g2_list_structure;
{
    Object tail, temp, reference, reference_1, node, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, next;
    char d, temp_1;

    x_note_fn_call(80,16);
    tail = ISVREF(g2_list_structure,(SI_Long)3L);
  next_loop:
    if (EQ(cursor,tail)) {
	temp = Nil;
	goto end_1;
    }
    reference = ISVREF(cursor,(SI_Long)2L);
    reference_1 = reference;
    temp = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node = temp;
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = node;
    if ( !TRUEP(gensymed_symbol))
	goto end_2;
  next_loop_2:
    gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_3;
    goto next_loop_2;
  end_loop:
  end_3:
    if (EQ(gensymed_symbol,node))
	goto end_2;
    else
	release_list_node(gensymed_symbol);
    goto next_loop_1;
  end_loop_1:
  end_2:;
    next = node;
    d = (SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(next,(SI_Long)2L));
    if (d) {
	temp = ISVREF(cursor,(SI_Long)2L);
	temp_1 =  !EQ(temp,MAKE_ATOMIC_REF(next,(SI_Long)355L));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if (EQ(next,ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)2L))))
	    help_delete_list_node(next);
	release_list_node(next);
    }
    else {
	release_list_node(next);
	cursor = next;
	if ( !d &&  !EQ(next,tail)) {
	    temp = cursor;
	    goto end_1;
	}
    }
    goto next_loop;
  end_loop_2:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* G2-LIST-STRUCTURE-PREVIOUS */
Object g2_list_structure_previous(cursor,g2_list_structure)
    Object cursor, g2_list_structure;
{
    Object head, temp, reference, reference_1, node, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, prev;

    x_note_fn_call(80,17);
    head = ISVREF(g2_list_structure,(SI_Long)2L);
  next_loop:
    if (EQ(cursor,head)) {
	temp = Nil;
	goto end_1;
    }
    reference = ISVREF(cursor,(SI_Long)3L);
    reference_1 = reference;
    temp = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node = temp;
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = node;
    if ( !TRUEP(gensymed_symbol))
	goto end_2;
  next_loop_2:
    gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_3;
    goto next_loop_2;
  end_loop:
  end_3:
    if (EQ(gensymed_symbol,node))
	goto end_2;
    else
	release_list_node(gensymed_symbol);
    goto next_loop_1;
  end_loop_1:
  end_2:;
    prev = node;
    temp = ISVREF(prev,(SI_Long)2L);
    if (EQ(temp,MAKE_ATOMIC_REF(cursor,(SI_Long)0L)) &&  !((SI_Long)355L 
	    == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L)))) {
	release_list_node(prev);
	cursor = prev;
	if ( !EQ(prev,head)) {
	    temp = cursor;
	    goto end_1;
	}
    }
    else if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L)))
	cursor = g2_list_structure_next(cursor,g2_list_structure);
    else {
	prev = help_insert_list_node(prev,cursor);
	release_list_node(prev);
    }
    goto next_loop;
  end_loop_2:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* G2-LIST-STRUCTURE-PUSH-COMMON */
Object g2_list_structure_push_common(node,next)
    Object node, next;
{
    Object backoff_limit, link1, temp_1, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, prev2;
    char temp;
    Declare_special(1);

    x_note_fn_call(80,18);
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
      link1 = Nil;
    next_loop:
      link1 = ISVREF(next,(SI_Long)3L);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(link1);
      if (temp);
      else {
	  temp_1 = ISVREF(node,(SI_Long)2L);
	  temp =  !EQ(temp_1,MAKE_ATOMIC_REF(next,(SI_Long)0L));
      }
      if (temp)
	  goto end_loop;
      temp_1 = link1;
      if (CAS_SVREF(next,(SI_Long)3L,temp_1,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	  gensymed_symbol = Nil;
	next_loop_1:
	  gensymed_symbol = node;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_1;
	next_loop_2:
	  gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	      goto end_2;
	  goto next_loop_2;
	end_loop_1:
	end_2:
	  if (EQ(gensymed_symbol,node))
	      goto end_1;
	  else
	      release_list_node(gensymed_symbol);
	  goto next_loop_1;
	end_loop_2:
	end_1:;
	  release_list_node(ATOMIC_REF_OBJECT(link1));
	  if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(node,(SI_Long)3L))) {
	      gensymed_symbol = Nil;
	    next_loop_3:
	      gensymed_symbol = node;
	      if ( !TRUEP(gensymed_symbol)) {
		  prev2 = Nil;
		  goto end_3;
	      }
	    next_loop_4:
	      gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_4;
	      goto next_loop_4;
	    end_loop_3:
	    end_4:
	      if (EQ(gensymed_symbol,node)) {
		  prev2 = gensymed_symbol;
		  goto end_3;
	      }
	      else
		  release_list_node(gensymed_symbol);
	      goto next_loop_3;
	    end_loop_4:
	      prev2 = Qnil;
	    end_3:;
	      prev2 = help_insert_list_node(prev2,next);
	      release_list_node(prev2);
	  }
	  goto end_loop;
      }
      back_off();
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    release_list_node(next);
    release_list_node(node);
    return VALUES_1(Nil);
}

/* G2-LIST-STRUCTURE-PUSH-RIGHT */
Object g2_list_structure_push_right(g2_list_structure,thing,outer_list)
    Object g2_list_structure, thing, outer_list;
{
    Object node, gensymed_symbol, next, gensymed_symbol_1, gensymed_symbol_2;
    Object prev, backoff_limit, temp, svref_new_value, temp_1;
    Declare_special(1);

    x_note_fn_call(80,19);
    node = create_list_element(thing,outer_list);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(g2_list_structure,(SI_Long)3L);
    if ( !TRUEP(gensymed_symbol)) {
	next = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(ISVREF(g2_list_structure,(SI_Long)3L),
	    (SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(ISVREF(g2_list_structure,(SI_Long)3L),(SI_Long)1L,
	    gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,ISVREF(g2_list_structure,(SI_Long)3L))) {
	next = gensymed_symbol;
	goto end_1;
    }
    else
	release_list_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    next = Qnil;
  end_1:;
    prev = read_list_node(ISVREF(next,(SI_Long)3L));
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_2:
      temp = ISVREF(prev,(SI_Long)2L);
      if ( !EQ(temp,MAKE_ATOMIC_REF(next,(SI_Long)0L)))
	  prev = help_insert_list_node(prev,next);
      else {
	  svref_new_value = MAKE_ATOMIC_REF(prev,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
	  svref_new_value = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	  temp = prev;
	  temp_1 = MAKE_ATOMIC_REF(next,(SI_Long)0L);
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
	      if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
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
	  back_off();
      }
      goto next_loop_2;
    end_loop_4:
      g2_list_structure_push_common(node,next);
      temp = node;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* G2-LIST-STRUCTURE-PUSH-LEFT */
Object g2_list_structure_push_left(g2_list_structure,thing,outer_list)
    Object g2_list_structure, thing, outer_list;
{
    Object node, gensymed_symbol, prev, gensymed_symbol_1, gensymed_symbol_2;
    Object next, backoff_limit, temp, svref_new_value;
    Declare_special(1);

    x_note_fn_call(80,20);
    node = create_list_element(thing,outer_list);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(g2_list_structure,(SI_Long)2L);
    if ( !TRUEP(gensymed_symbol)) {
	prev = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(ISVREF(g2_list_structure,(SI_Long)2L),
	    (SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(ISVREF(g2_list_structure,(SI_Long)2L),(SI_Long)1L,
	    gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,ISVREF(g2_list_structure,(SI_Long)2L))) {
	prev = gensymed_symbol;
	goto end_1;
    }
    else
	release_list_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    prev = Qnil;
  end_1:;
    next = read_queue_node(ISVREF(prev,(SI_Long)2L));
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_2:
      temp = ISVREF(prev,(SI_Long)2L);
      if ( !EQ(temp,MAKE_ATOMIC_REF(next,(SI_Long)0L))) {
	  release_list_node(next);
	  next = read_list_node(ISVREF(prev,(SI_Long)2L));
      }
      else {
	  svref_new_value = MAKE_ATOMIC_REF(prev,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
	  svref_new_value = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	  temp = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  if (CAS_SVREF(prev,(SI_Long)2L,temp,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	      gensymed_symbol = Nil;
	    next_loop_3:
	      gensymed_symbol = node;
	      if ( !TRUEP(gensymed_symbol))
		  goto end_3;
	    next_loop_4:
	      gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
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
	  back_off();
      }
      goto next_loop_2;
    end_loop_4:
      g2_list_structure_push_common(node,next);
      temp = node;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* G2-LIST-STRUCTURE-DELETE */
Object g2_list_structure_delete varargs_1(int, n)
{
    Object cursor;
    Object g2_list_structure, link1, temp, gensymed_symbol, prev;
    Object gensymed_symbol_1, gensymed_symbol_2, value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(80,21);
    INIT_ARGS_nonrelocating();
    cursor = REQUIRED_ARG_nonrelocating();
    g2_list_structure = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (g2_list_structure && (EQ(cursor,ISVREF(g2_list_structure,
	    (SI_Long)2L)) || EQ(cursor,ISVREF(g2_list_structure,(SI_Long)3L))))
	return VALUES_2(Nil,Nil);
    link1 = Nil;
  next_loop:
    link1 = ISVREF(cursor,(SI_Long)2L);
    if ((SI_Long)355L == ATOMIC_REF_STAMP(link1))
	return VALUES_2(Nil,Nil);
    temp = link1;
    if (CAS_SVREF(cursor,(SI_Long)2L,temp,
	    MAKE_ATOMIC_REF(ATOMIC_REF_OBJECT(link1),(SI_Long)355L))) {
	help_delete_list_node(cursor);
	gensymed_symbol = Nil;
      next_loop_1:
	gensymed_symbol = ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)3L));
	if ( !TRUEP(gensymed_symbol)) {
	    prev = Nil;
	    goto end_1;
	}
      next_loop_2:
	gensymed_symbol_1 = ISVREF(ATOMIC_REF_OBJECT(ISVREF(cursor,
		(SI_Long)3L)),(SI_Long)1L);
	gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	if (CAS_SVREF(ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)3L)),
		(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	    goto end_2;
	goto next_loop_2;
      end_loop:
      end_2:
	temp = gensymed_symbol;
	if (EQ(temp,ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)3L)))) {
	    prev = gensymed_symbol;
	    goto end_1;
	}
	else
	    release_list_node(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	prev = Qnil;
      end_1:;
	temp = prev;
	prev = help_insert_list_node(temp,ATOMIC_REF_OBJECT(link1));
	release_list_node(prev);
	value = ISVREF(cursor,(SI_Long)4L);
	remove_list_cross_reference(cursor);
	return VALUES_2(value,T);
    }
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* G2-LIST-STRUCTURE-CLEAR */
Object g2_list_structure_clear(g2_list_structure)
    Object g2_list_structure;
{
    Object next_element_structure, element_structure, temp, svref_arg_2;

    x_note_fn_call(80,22);
    next_element_structure = Nil;
    element_structure = g2_list_structure_next(ISVREF(g2_list_structure,
	    (SI_Long)2L),g2_list_structure);
  next_loop:
    if ( !TRUEP(element_structure))
	goto end_loop;
    next_element_structure = g2_list_structure_next(element_structure,
	    g2_list_structure);
    reclaim_if_evaluation_value_function(ISVREF(element_structure,
	    (SI_Long)4L));
    inline_note_reclaim_cons(element_structure,Nil);
    temp = ISVREF(Chain_of_available_g2_list_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(element_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_g2_list_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = element_structure;
    element_structure = next_element_structure;
    goto next_loop;
  end_loop:;
    initialize_g2_list_structure(g2_list_structure);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_eval_conses, Qavailable_eval_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_eval_conses_tail, Qavailable_eval_conses_tail);

Object Available_eval_conses_vector = UNBOUND;

Object Available_eval_conses_tail_vector = UNBOUND;

Object Eval_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Eval_cons_counter, Qeval_cons_counter);

/* OUTSTANDING-EVAL-CONSES */
Object outstanding_eval_conses()
{
    Object temp;

    x_note_fn_call(80,23);
    temp = FIXNUM_MINUS(Eval_cons_counter,length(Available_eval_conses));
    return VALUES_1(temp);
}

/* EVAL-CONS-MEMORY-USAGE */
Object eval_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(80,24);
    temp = FIXNUM_TIMES(Eval_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-EVAL-CONS-POOL */
Object replenish_eval_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(80,25);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qeval_cons_counter,Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Eval_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

/* EVAL-CONS-1 */
Object eval_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(80,26);
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_eval_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qeval);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-EVAL-LIST-POOL */
Object replenish_eval_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(80,27);
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
    if (ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qeval_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-EVAL-LIST-1 */
Object make_eval_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(80,28);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_eval_conses_vector,
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
	replenish_eval_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qeval);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
	svref_arg_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_eval_conses_tail_vector;
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

/* EVAL-LIST-2 */
Object eval_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(80,29);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_eval_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qeval);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_eval_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_eval_conses_tail_vector;
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

/* EVAL-LIST-3 */
Object eval_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(80,30);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_eval_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qeval);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_eval_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_eval_conses_tail_vector;
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

/* EVAL-LIST-4 */
Object eval_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(80,31);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_eval_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qeval);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_eval_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_eval_conses_tail_vector;
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

/* EVAL-LIST-TRACE-HOOK */
Object eval_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(80,32);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-EVAL-CONSES-1 */
Object copy_tree_using_eval_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(80,33);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
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
	temp_1 = copy_tree_using_eval_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
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
	temp_1 = copy_tree_using_eval_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
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

/* COPY-LIST-USING-EVAL-CONSES-1 */
Object copy_list_using_eval_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(80,34);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
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
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
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
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
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

/* RECLAIM-EVAL-CONS-1 */
Object reclaim_eval_cons_1(eval_cons)
    Object eval_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,35);
    inline_note_reclaim_cons(eval_cons,Qeval);
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = eval_cons;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = eval_cons;
    }
    else {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = eval_cons;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = eval_cons;
    }
    M_CDR(eval_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-EVAL-LIST-1 */
Object reclaim_eval_list_1(eval_list)
    Object eval_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(80,36);
    if (eval_list) {
	last_1 = eval_list;
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
	    M_CDR(temp) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list;
	    temp = Available_eval_conses_tail_vector;
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

/* RECLAIM-EVAL-LIST*-1 */
Object reclaim_eval_list_star_1(eval_list)
    Object eval_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(80,37);
    if (CONSP(eval_list)) {
	temp = last(eval_list,_);
	M_CDR(temp) = Nil;
	if (eval_list) {
	    last_1 = eval_list;
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
		M_CDR(temp) = eval_list;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = eval_list;
		temp = Available_eval_conses_tail_vector;
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

/* RECLAIM-EVAL-TREE-1 */
Object reclaim_eval_tree_1(tree)
    Object tree;
{
    Object e, e2, eval_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(80,38);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_eval_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		eval_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(eval_cons,Qeval);
		if (EQ(eval_cons,e))
		    goto end_1;
		else if ( !TRUEP(eval_cons))
		    goto end_1;
		else
		    eval_cons = CDR(eval_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_eval_conses_tail_vector;
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

/* DELETE-EVAL-ELEMENT-1 */
Object delete_eval_element_1(element,eval_list)
    Object element, eval_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(80,39);
    if (eval_list) {
	if (EQ(element,M_CAR(eval_list))) {
	    temp = CDR(eval_list);
	    inline_note_reclaim_cons(eval_list,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = eval_list;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = eval_list;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = eval_list;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = eval_list;
	    }
	    M_CDR(eval_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = eval_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_eval_conses_tail_vector;
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
	    temp = eval_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-EVAL-CONS-1 */
Object delete_eval_cons_1(eval_cons,eval_list)
    Object eval_cons, eval_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(80,40);
    if (EQ(eval_cons,eval_list))
	temp = CDR(eval_list);
    else {
	l_trailer_qm = Nil;
	l = eval_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,eval_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = eval_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_eval_cons_1(eval_cons);
    return VALUES_1(temp);
}

/* RECLAIM-EVAL-CONS-FUNCTION */
Object reclaim_eval_cons_function(cons_1)
    Object cons_1;
{
    x_note_fn_call(80,41);
    return reclaim_eval_cons_1(cons_1);
}

/* RECLAIM-EVAL-LIST-FUNCTION */
Object reclaim_eval_list_function(list_1)
    Object list_1;
{
    Object last_1, next_qm, temp, svref_arg_2;

    x_note_fn_call(80,42);
    if (list_1) {
	last_1 = list_1;
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
	    M_CDR(temp) = list_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = list_1;
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

/* RECLAIM-EVAL-ALIST */
Object reclaim_eval_alist(alist)
    Object alist;
{
    Object trailer, cons_1, eval_cons, temp, svref_arg_2;

    x_note_fn_call(80,43);
    if (alist) {
	trailer = Nil;
	cons_1 = alist;
      next_loop:
	if ( !TRUEP(cons_1))
	    goto end_loop;
	reclaim_eval_cons_1(M_CAR(cons_1));
	trailer = cons_1;
	cons_1 = M_CDR(cons_1);
	goto next_loop;
      end_loop:
	if (alist &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = alist;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,trailer))
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
	    M_CDR(temp) = alist;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = alist;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	M_CDR(trailer) = Nil;
    }
    return VALUES_1(Nil);
}

Object Numeric_data_type_gkbprop = UNBOUND;

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-EVALUATION-TYPES-SKIP-LIST-SENTINEL */
Object make_evaluation_types_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(80,44);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* RECLAIM-EVALUATION-TYPES-NODES */
Object reclaim_evaluation_types_nodes(evaluation_types_skip_list,tail)
    Object evaluation_types_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(80,45);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(evaluation_types_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(evaluation_types_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(evaluation_types_skip_list,(SI_Long)2L);
    entry = ISVREF(evaluation_types_skip_list,(SI_Long)3L);
    reclaim_skip_list_element(evaluation_types_skip_list);
    evaluation_types_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-EVALUATION-TYPES-SKIP-LIST */
Object clear_evaluation_types_skip_list(evaluation_types_skip_list)
    Object evaluation_types_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(80,46);
    head = M_CAR(M_CDR(evaluation_types_skip_list));
    tail = M_CDR(M_CDR(evaluation_types_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_evaluation_types_nodes(element_qm,tail);
    return VALUES_1(evaluation_types_skip_list);
}

DEFINE_VARIABLE_WITH_SYMBOL(Defined_evaluation_value_types, Qdefined_evaluation_value_types);

DEFINE_VARIABLE_WITH_SYMBOL(Defined_evaluation_datum_types, Qdefined_evaluation_datum_types);

Object Type_specification_of_defined_evaluation_type_prop = UNBOUND;

Object Defined_evaluation_type_reclaimer_prop = UNBOUND;

Object Defined_evaluation_type_copier_prop = UNBOUND;

Object Defined_evaluation_type_deep_copier_prop = UNBOUND;

Object Defined_evaluation_type_validator_prop = UNBOUND;

Object Defined_evaluation_type_comparitor_prop = UNBOUND;

Object Defined_evaluation_type_eq_prop = UNBOUND;

Object Defined_evaluation_type_writer_prop = UNBOUND;

Object Evaluation_true_value = UNBOUND;

Object Evaluation_false_value = UNBOUND;

static Object Qtruth_value;        /* truth-value */

/* MAKE-EVALUATION-TRUTH-VALUE-FUNCTION */
Object make_evaluation_truth_value_function(fixnum_truth_value)
    Object fixnum_truth_value;
{
    Object temp;

    x_note_fn_call(80,47);
    if (FIXNUM_EQ(fixnum_truth_value,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(fixnum_truth_value,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(fixnum_truth_value,Qtruth_value);
    return VALUES_1(temp);
}

/* EVALUATION-TRUTH-VALUE-VALUE-FUNCTION */
Object evaluation_truth_value_value_function(evaluation_truth_value)
    Object evaluation_truth_value;
{
    x_note_fn_call(80,48);
    return VALUES_1(M_CAR(evaluation_truth_value));
}

/* COPY-EVALUATION-TRUTH-VALUE-FUNCTION */
Object copy_evaluation_truth_value_function(evaluation_truth_value)
    Object evaluation_truth_value;
{
    x_note_fn_call(80,49);
    if (EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value))
	return VALUES_1(evaluation_truth_value);
    else
	return eval_cons_1(M_CAR(evaluation_truth_value),Qtruth_value);
}

/* EVALUATION-TRUTH-VALUE-IS-TRUE-P */
Object evaluation_truth_value_is_true_p(evaluation_truth_value)
    Object evaluation_truth_value;
{
    Object temp;

    x_note_fn_call(80,50);
    temp = M_CAR(evaluation_truth_value);
    return VALUES_1(FIXNUM_GE(temp,truth_threshold_parameter_function()) ? 
	    T : Nil);
}

/* EVALUATION-VALUE-IS-TRUE-P */
Object evaluation_value_is_true_p(evaluation_value)
    Object evaluation_value;
{
    x_note_fn_call(80,51);
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),Qtruth_value))
	return evaluation_truth_value_is_true_p(evaluation_value);
    else
	return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* MAKE-EVALUATION-FLOAT-FROM-EVALUATION-INTEGER */
Object make_evaluation_float_from_evaluation_integer(evaluation_integer)
    Object evaluation_integer;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    SI_Long fixnum;
    double aref_new_value;

    x_note_fn_call(80,52);
    fixnum = IFIX(evaluation_integer);
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
    aref_new_value = (double)fixnum;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* RECLAIM-EVALUATION-FLOAT-FUNCTION */
Object reclaim_evaluation_float_function(evaluation_float)
    Object evaluation_float;
{
    x_note_fn_call(80,53);
    reclaim_managed_simple_float_array_of_length_1(evaluation_float);
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-FLOAT-FROM-PHRASE-FLOAT */
Object copy_evaluation_float_from_phrase_float(phrase_float)
    Object phrase_float;
{
    Object new_evaluation_float, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,54);
    new_evaluation_float = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
	aref_new_value = DFLOAT_ISAREF_1(phrase_float,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	new_evaluation_float = new_float;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(new_evaluation_float);
}

/* MAKE-EVALUATION-LONG */
Object make_evaluation_long(integer)
    Object integer;
{
    Object new_long, temp;
    SI_int64 aref_new_value, long_1, zero, long_value;

    x_note_fn_call(80,55);
    if (INLINE_LONG_P(integer) != (SI_Long)0L) {
	new_long = allocate_managed_long_box();
	aref_new_value = INTEGER_TO_INT64(integer);
	set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	temp = new_long;
    }
    else {
	long_1 = INTEGER_TO_INT64(integer);
	zero = (SI_int64)(SI_Long)0L;
	temp = add(INT64_TO_INTEGER(long_1),INT64_TO_INTEGER(zero));
	long_value = INTEGER_TO_INT64(temp);
	new_long = allocate_managed_long_box();
	set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(long_value));
	temp = new_long;
    }
    return VALUES_1(temp);
}

/* RECLAIM-EVALUATION-LONG-FUNCTION */
Object reclaim_evaluation_long_function(evaluation_long)
    Object evaluation_long;
{
    x_note_fn_call(80,56);
    reclaim_managed_simple_long_array_of_length_1(evaluation_long);
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-LONG-FROM-PHRASE-LONG */
Object copy_evaluation_long_from_phrase_long(phrase_long)
    Object phrase_long;
{
    Object new_evaluation_long;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,57);
    new_evaluation_long = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	new_evaluation_long = make_evaluation_long(aref1(phrase_long,
		FIX((SI_Long)0L)));
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(new_evaluation_long);
}

static Object float_constant;      /* 0.0 */

/* MAKE-EVALUATION-FLOAT-FROM-EVALUATION-LONG */
Object make_evaluation_float_from_evaluation_long varargs_1(int, n)
{
    Object evaluation_long;
    Object reclaim_argument_qm, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, temp_2;
    double aref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(80,58);
    INIT_ARGS_nonrelocating();
    evaluation_long = REQUIRED_ARG_nonrelocating();
    reclaim_argument_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
    temp_2 = lfloat(aref1(evaluation_long,FIX((SI_Long)0L)),float_constant);
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    temp_2 = new_float;
    if (reclaim_argument_qm)
	reclaim_managed_simple_long_array_of_length_1(evaluation_long);
    return VALUES_1(temp_2);
}

/* DIV-LONG */
Object div_long(evaluation_long_1,evaluation_long_2)
    Object evaluation_long_1, evaluation_long_2;
{
    Object temp;
    SI_int64 long_1, long_2, aref_new_value;

    x_note_fn_call(80,59);
    temp = aref1(evaluation_long_1,FIX((SI_Long)0L));
    long_1 = INTEGER_TO_INT64(temp);
    temp = aref1(evaluation_long_2,FIX((SI_Long)0L));
    long_2 = INTEGER_TO_INT64(temp);
    temp = divide(INT64_TO_INTEGER(long_1),INT64_TO_INTEGER(long_2));
    aref_new_value = INTEGER_TO_INT64(temp);
    set_aref1(evaluation_long_1,FIX((SI_Long)0L),
	    INT64_TO_INTEGER(aref_new_value));
    return VALUES_1(evaluation_long_1);
}

/* MAKE-EVALUATION-QUANTITY */
Object make_evaluation_quantity(lisp_number)
    Object lisp_number;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(80,60);
    if (FIXNUMP(lisp_number))
	temp = lisp_number;
    else if (INLINE_LONG_P(lisp_number) != (SI_Long)0L)
	temp = make_evaluation_long(lisp_number);
    else {
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(lisp_number);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    return VALUES_1(temp);
}

/* RECLAIM-EVALUATION-QUANTITY */
Object reclaim_evaluation_quantity(evaluation_quantity)
    Object evaluation_quantity;
{
    x_note_fn_call(80,61);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(evaluation_quantity);
    else if (INLINE_LONG_VECTOR_P(evaluation_quantity) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_long_array_of_length_1(evaluation_quantity);
    else;
    return VALUES_1(Nil);
}

/* EVALUATION-QUANTITY-VALUE */
Object evaluation_quantity_value(evaluation_quantity)
    Object evaluation_quantity;
{
    Object temp;

    x_note_fn_call(80,62);
    if (FIXNUMP(evaluation_quantity))
	temp = evaluation_quantity;
    else if (INLINE_LONG_VECTOR_P(evaluation_quantity) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity)) == 
	    (SI_Long)1L)
	temp = aref1(evaluation_quantity,FIX((SI_Long)0L));
    else
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_quantity,
		(SI_Long)0L));
    return VALUES_1(temp);
}

/* EVALUATION-QUANTITY-= */
Object evaluation_quantity_eq(evaluation_quantity_1,evaluation_quantity_2)
    Object evaluation_quantity_1, evaluation_quantity_2;
{
    Object temp, evaluation_long_1, evaluation_long_2;
    SI_int64 long_value_1, long_value_2;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,63);
    if (FIXNUMP(evaluation_quantity_1) && FIXNUMP(evaluation_quantity_2))
	temp = FIXNUM_EQ(evaluation_quantity_1,evaluation_quantity_2) ? T :
		 Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
	    (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_2) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(evaluation_quantity_1))
	    arg = (double)IFIX(evaluation_quantity_1);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_1,
		    FIX((SI_Long)0L)));
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg = DFLOAT_ISAREF_1(evaluation_quantity_1,(SI_Long)0L);
	if (FIXNUMP(evaluation_quantity_2))
	    arg_1 = (double)IFIX(evaluation_quantity_2);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_2,
		    FIX((SI_Long)0L)));
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg_1 = DFLOAT_ISAREF_1(evaluation_quantity_2,(SI_Long)0L);
	temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else {
	evaluation_long_1 = FIXNUMP(evaluation_quantity_1) ? 
		make_evaluation_long(evaluation_quantity_1) : 
		evaluation_quantity_1;
	evaluation_long_2 = FIXNUMP(evaluation_quantity_2) ? 
		make_evaluation_long(evaluation_quantity_2) : 
		evaluation_quantity_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = aref1(evaluation_long_1,FIX((SI_Long)0L));
	    long_value_1 = INTEGER_TO_INT64(temp);
	    temp = aref1(evaluation_long_2,FIX((SI_Long)0L));
	    long_value_2 = INTEGER_TO_INT64(temp);
	    temp = NUM_EQ(INT64_TO_INTEGER(long_value_1),
		    INT64_TO_INTEGER(long_value_2)) ? T : Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (FIXNUMP(evaluation_quantity_1))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_1);
	if (FIXNUMP(evaluation_quantity_2))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_2);
    }
    return VALUES_1(temp);
}

/* EVALUATION-QUANTITY-/= */
Object evaluation_quantity_sl_eq(evaluation_quantity_1,evaluation_quantity_2)
    Object evaluation_quantity_1, evaluation_quantity_2;
{
    Object temp, evaluation_long_1, evaluation_long_2;
    SI_int64 long_value_1, long_value_2;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,64);
    if (FIXNUMP(evaluation_quantity_1) && FIXNUMP(evaluation_quantity_2))
	temp = FIXNUM_NE(evaluation_quantity_1,evaluation_quantity_2) ? T :
		 Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
	    (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_2) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(evaluation_quantity_1))
	    arg = (double)IFIX(evaluation_quantity_1);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_1,
		    FIX((SI_Long)0L)));
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg = DFLOAT_ISAREF_1(evaluation_quantity_1,(SI_Long)0L);
	if (FIXNUMP(evaluation_quantity_2))
	    arg_1 = (double)IFIX(evaluation_quantity_2);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_2,
		    FIX((SI_Long)0L)));
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg_1 = DFLOAT_ISAREF_1(evaluation_quantity_2,(SI_Long)0L);
	temp =  !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) ? T : Nil;
    }
    else {
	evaluation_long_1 = FIXNUMP(evaluation_quantity_1) ? 
		make_evaluation_long(evaluation_quantity_1) : 
		evaluation_quantity_1;
	evaluation_long_2 = FIXNUMP(evaluation_quantity_2) ? 
		make_evaluation_long(evaluation_quantity_2) : 
		evaluation_quantity_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = aref1(evaluation_long_1,FIX((SI_Long)0L));
	    long_value_1 = INTEGER_TO_INT64(temp);
	    temp = aref1(evaluation_long_2,FIX((SI_Long)0L));
	    long_value_2 = INTEGER_TO_INT64(temp);
	    temp = NUM_NE(INT64_TO_INTEGER(long_value_1),
		    INT64_TO_INTEGER(long_value_2)) ? T : Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (FIXNUMP(evaluation_quantity_1))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_1);
	if (FIXNUMP(evaluation_quantity_2))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_2);
    }
    return VALUES_1(temp);
}

/* EVALUATION-QUANTITY-< */
Object evaluation_quantity_lt(evaluation_quantity_1,evaluation_quantity_2)
    Object evaluation_quantity_1, evaluation_quantity_2;
{
    Object temp, evaluation_long_1, evaluation_long_2;
    SI_int64 long_value_1, long_value_2;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,65);
    if (FIXNUMP(evaluation_quantity_1) && FIXNUMP(evaluation_quantity_2))
	temp = FIXNUM_LT(evaluation_quantity_1,evaluation_quantity_2) ? T :
		 Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
	    (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_2) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(evaluation_quantity_1))
	    arg = (double)IFIX(evaluation_quantity_1);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_1,
		    FIX((SI_Long)0L)));
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg = DFLOAT_ISAREF_1(evaluation_quantity_1,(SI_Long)0L);
	if (FIXNUMP(evaluation_quantity_2))
	    arg_1 = (double)IFIX(evaluation_quantity_2);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_2,
		    FIX((SI_Long)0L)));
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg_1 = DFLOAT_ISAREF_1(evaluation_quantity_2,(SI_Long)0L);
	temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else {
	evaluation_long_1 = FIXNUMP(evaluation_quantity_1) ? 
		make_evaluation_long(evaluation_quantity_1) : 
		evaluation_quantity_1;
	evaluation_long_2 = FIXNUMP(evaluation_quantity_2) ? 
		make_evaluation_long(evaluation_quantity_2) : 
		evaluation_quantity_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = aref1(evaluation_long_1,FIX((SI_Long)0L));
	    long_value_1 = INTEGER_TO_INT64(temp);
	    temp = aref1(evaluation_long_2,FIX((SI_Long)0L));
	    long_value_2 = INTEGER_TO_INT64(temp);
	    temp = NUM_LT(INT64_TO_INTEGER(long_value_1),
		    INT64_TO_INTEGER(long_value_2)) ? T : Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (FIXNUMP(evaluation_quantity_1))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_1);
	if (FIXNUMP(evaluation_quantity_2))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_2);
    }
    return VALUES_1(temp);
}

/* EVALUATION-QUANTITY->= */
Object evaluation_quantity_gt_eq(evaluation_quantity_1,evaluation_quantity_2)
    Object evaluation_quantity_1, evaluation_quantity_2;
{
    Object temp, evaluation_long_1, evaluation_long_2;
    SI_int64 long_value_1, long_value_2;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,66);
    if (FIXNUMP(evaluation_quantity_1) && FIXNUMP(evaluation_quantity_2))
	temp = FIXNUM_GE(evaluation_quantity_1,evaluation_quantity_2) ? T :
		 Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
	    (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_2) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(evaluation_quantity_1))
	    arg = (double)IFIX(evaluation_quantity_1);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_1,
		    FIX((SI_Long)0L)));
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg = DFLOAT_ISAREF_1(evaluation_quantity_1,(SI_Long)0L);
	if (FIXNUMP(evaluation_quantity_2))
	    arg_1 = (double)IFIX(evaluation_quantity_2);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_2,
		    FIX((SI_Long)0L)));
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg_1 = DFLOAT_ISAREF_1(evaluation_quantity_2,(SI_Long)0L);
	temp = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else {
	evaluation_long_1 = FIXNUMP(evaluation_quantity_1) ? 
		make_evaluation_long(evaluation_quantity_1) : 
		evaluation_quantity_1;
	evaluation_long_2 = FIXNUMP(evaluation_quantity_2) ? 
		make_evaluation_long(evaluation_quantity_2) : 
		evaluation_quantity_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = aref1(evaluation_long_1,FIX((SI_Long)0L));
	    long_value_1 = INTEGER_TO_INT64(temp);
	    temp = aref1(evaluation_long_2,FIX((SI_Long)0L));
	    long_value_2 = INTEGER_TO_INT64(temp);
	    temp = NUM_GE(INT64_TO_INTEGER(long_value_1),
		    INT64_TO_INTEGER(long_value_2)) ? T : Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (FIXNUMP(evaluation_quantity_1))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_1);
	if (FIXNUMP(evaluation_quantity_2))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_2);
    }
    return VALUES_1(temp);
}

/* EVALUATION-QUANTITY-> */
Object evaluation_quantity_gt(evaluation_quantity_1,evaluation_quantity_2)
    Object evaluation_quantity_1, evaluation_quantity_2;
{
    Object temp, evaluation_long_1, evaluation_long_2;
    SI_int64 long_value_1, long_value_2;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,67);
    if (FIXNUMP(evaluation_quantity_1) && FIXNUMP(evaluation_quantity_2))
	temp = FIXNUM_GT(evaluation_quantity_1,evaluation_quantity_2) ? T :
		 Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
	    (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_2) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(evaluation_quantity_1))
	    arg = (double)IFIX(evaluation_quantity_1);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_1,
		    FIX((SI_Long)0L)));
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg = DFLOAT_ISAREF_1(evaluation_quantity_1,(SI_Long)0L);
	if (FIXNUMP(evaluation_quantity_2))
	    arg_1 = (double)IFIX(evaluation_quantity_2);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_2,
		    FIX((SI_Long)0L)));
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg_1 = DFLOAT_ISAREF_1(evaluation_quantity_2,(SI_Long)0L);
	temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else {
	evaluation_long_1 = FIXNUMP(evaluation_quantity_1) ? 
		make_evaluation_long(evaluation_quantity_1) : 
		evaluation_quantity_1;
	evaluation_long_2 = FIXNUMP(evaluation_quantity_2) ? 
		make_evaluation_long(evaluation_quantity_2) : 
		evaluation_quantity_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = aref1(evaluation_long_1,FIX((SI_Long)0L));
	    long_value_1 = INTEGER_TO_INT64(temp);
	    temp = aref1(evaluation_long_2,FIX((SI_Long)0L));
	    long_value_2 = INTEGER_TO_INT64(temp);
	    temp = NUM_GT(INT64_TO_INTEGER(long_value_1),
		    INT64_TO_INTEGER(long_value_2)) ? T : Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (FIXNUMP(evaluation_quantity_1))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_1);
	if (FIXNUMP(evaluation_quantity_2))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_2);
    }
    return VALUES_1(temp);
}

/* EVALUATION-QUANTITY-<= */
Object evaluation_quantity_lt_eq(evaluation_quantity_1,evaluation_quantity_2)
    Object evaluation_quantity_1, evaluation_quantity_2;
{
    Object temp, evaluation_long_1, evaluation_long_2;
    SI_int64 long_value_1, long_value_2;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(80,68);
    if (FIXNUMP(evaluation_quantity_1) && FIXNUMP(evaluation_quantity_2))
	temp = FIXNUM_LE(evaluation_quantity_1,evaluation_quantity_2) ? T :
		 Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
	    (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_2) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(evaluation_quantity_1))
	    arg = (double)IFIX(evaluation_quantity_1);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_1)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_1,
		    FIX((SI_Long)0L)));
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg = DFLOAT_ISAREF_1(evaluation_quantity_1,(SI_Long)0L);
	if (FIXNUMP(evaluation_quantity_2))
	    arg_1 = (double)IFIX(evaluation_quantity_2);
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_2)) == 
		(SI_Long)1L) {
	    temp = convert_g2longint_to_double(aref1(evaluation_quantity_2,
		    FIX((SI_Long)0L)));
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    arg_1 = DFLOAT_ISAREF_1(evaluation_quantity_2,(SI_Long)0L);
	temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else {
	evaluation_long_1 = FIXNUMP(evaluation_quantity_1) ? 
		make_evaluation_long(evaluation_quantity_1) : 
		evaluation_quantity_1;
	evaluation_long_2 = FIXNUMP(evaluation_quantity_2) ? 
		make_evaluation_long(evaluation_quantity_2) : 
		evaluation_quantity_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = aref1(evaluation_long_1,FIX((SI_Long)0L));
	    long_value_1 = INTEGER_TO_INT64(temp);
	    temp = aref1(evaluation_long_2,FIX((SI_Long)0L));
	    long_value_2 = INTEGER_TO_INT64(temp);
	    temp = NUM_LE(INT64_TO_INTEGER(long_value_1),
		    INT64_TO_INTEGER(long_value_2)) ? T : Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (FIXNUMP(evaluation_quantity_1))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_1);
	if (FIXNUMP(evaluation_quantity_2))
	    reclaim_managed_simple_long_array_of_length_1(evaluation_long_2);
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Test_removal_of_unsigned_vector_16, Qtest_removal_of_unsigned_vector_16);

static Object Qunknown;            /* unknown */

static Object string_constant;     /* "TEST_REMOVAL_OF_UNSIGNED_VECTOR_16" */

static Object Qunsigned_vector_16;  /* unsigned-vector-16 */

/* MAYBE-MAKE-EVALUATION-UNSIGNED-VECTOR-16 */
Object maybe_make_evaluation_unsigned_vector_16(x)
    Object x;
{
    Object string_qm, temp;

    x_note_fn_call(80,69);
    if (EQ(Test_removal_of_unsigned_vector_16,Qunknown)) {
	string_qm = get_gensym_environment_variable(string_constant);
	if (string_qm) {
	    reclaim_text_string(string_qm);
	    Test_removal_of_unsigned_vector_16 = T;
	}
	else
	    Test_removal_of_unsigned_vector_16 = Nil;
    }
    temp = Test_removal_of_unsigned_vector_16 ? x : eval_cons_1(x,
	    Qunsigned_vector_16);
    return VALUES_1(temp);
}

/* RECLAIM-EVALUATION-UNSIGNED-VECTOR-16 */
Object reclaim_evaluation_unsigned_vector_16(unsigned_vector_16)
    Object unsigned_vector_16;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,70);
    reclaim_text_string(M_CAR(unsigned_vector_16));
    if (unsigned_vector_16) {
	inline_note_reclaim_cons(unsigned_vector_16,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = unsigned_vector_16;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = unsigned_vector_16;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = unsigned_vector_16;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = unsigned_vector_16;
	}
	M_CDR(unsigned_vector_16) = Nil;
    }
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-UNSIGNED-VECTOR-16 */
Object copy_evaluation_unsigned_vector_16(unsigned_vector_16)
    Object unsigned_vector_16;
{
    Object temp;

    x_note_fn_call(80,71);
    temp = 
	    maybe_make_evaluation_unsigned_vector_16(copy_wide_string(M_CAR(unsigned_vector_16)));
    return VALUES_1(temp);
}

/* EVALUATION-UNSIGNED-VECTOR-16-EQL */
Object evaluation_unsigned_vector_16_eql(unsigned_vector_16_1,
	    unsigned_vector_16_2)
    Object unsigned_vector_16_1, unsigned_vector_16_2;
{
    Object temp;

    x_note_fn_call(80,72);
    temp = EQ(unsigned_vector_16_1,unsigned_vector_16_2) ? T : Nil;
    if (temp);
    else
	temp = string_eq_w(M_CAR(unsigned_vector_16_1),
		M_CAR(unsigned_vector_16_2));
    return VALUES_1(temp);
}

/* EVALUATION-UNSIGNED-VECTOR-16-= */
Object evaluation_unsigned_vector_16_eq(unsigned_vector_16_1,
	    unsigned_vector_16_2)
    Object unsigned_vector_16_1, unsigned_vector_16_2;
{
    Object temp;

    x_note_fn_call(80,73);
    temp = EQ(unsigned_vector_16_1,unsigned_vector_16_2) ? T : Nil;
    if (temp);
    else
	temp = string_eq_w(M_CAR(unsigned_vector_16_1),
		M_CAR(unsigned_vector_16_2));
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qtext;               /* text */

/* WRITE-EVALUATION-UNSIGNED-VECTOR-16 */
Object write_evaluation_unsigned_vector_16(unsigned_vector_16)
    Object unsigned_vector_16;
{
    x_note_fn_call(80,74);
    print_constant(3,M_CAR(unsigned_vector_16),Qtext,T);
    return VALUES_1(Nil);
}

/* RECLAIM-EVALUATION-MEMBER */
Object reclaim_evaluation_member(member_1)
    Object member_1;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,75);
    if ( !(FIXNUMP(member_1) || SYMBOLP(member_1)))
	reclaim_evaluation_value(member_1);
    if (member_1) {
	inline_note_reclaim_cons(member_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = member_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = member_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = member_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = member_1;
	}
	M_CDR(member_1) = Nil;
    }
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-MEMBER */
Object copy_evaluation_member(member_1)
    Object member_1;
{
    Object temp;

    x_note_fn_call(80,76);
    temp = FIXNUMP(member_1) || SYMBOLP(member_1) ? member_1 : 
	    FIXNUMP(member_1) || member_1 && SYMBOLP(member_1) ? member_1 :
	     copy_evaluation_value_1(member_1);
    return VALUES_1(temp);
}

/* EVALUATION-MEMBER-EQL */
Object evaluation_member_eql(member_1,member_2)
    Object member_1, member_2;
{
    Object temp;

    x_note_fn_call(80,77);
    temp = EQ(member_1,member_2) ? T : Nil;
    if (temp);
    else
	temp = evaluation_value_eql(2,member_1,member_2);
    return VALUES_1(temp);
}

/* EVALUATION-MEMBER-= */
Object evaluation_member_eq(member_1,member_2)
    Object member_1, member_2;
{
    Object temp;

    x_note_fn_call(80,78);
    temp = EQ(member_1,member_2) ? T : Nil;
    if (temp);
    else
	temp = evaluation_value_eq(member_1,member_2);
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-EVALUATION-MEMBER */
Object write_evaluation_member(member_1)
    Object member_1;
{
    x_note_fn_call(80,79);
    write_evaluation_value(1,member_1);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Datum_type, Qdatum_type);

/* MEMBER-TYPE-SPECIFICATION-INTERSECTS-DATUM-TYPE-P */
Object member_type_specification_intersects_datum_type_p(member_type,
	    datum_type)
    Object member_type, datum_type;
{
    Object elt_1, ab_loop_list_, elt_type, ab_loop_it_, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(80,80);
    PUSH_SPECIAL_WITH_SYMBOL(Datum_type,Qdatum_type,datum_type,0);
      elt_1 = Nil;
      ab_loop_list_ = CDR(member_type);
      elt_type = Nil;
      ab_loop_it_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      elt_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      elt_type = evaluation_value_type(elt_1);
      ab_loop_it_ = type_specifications_could_intersect_in_kb_p(elt_type,
	      Datum_type);
      if (ab_loop_it_) {
	  temp = ab_loop_it_;
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      temp = Qnil;
    end_1:;
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* MEMBER-TYPE-SPECIFICATIONS-COULD-INTERSECT-P */
Object member_type_specifications_could_intersect_p(member_type_1,
	    member_type_2)
    Object member_type_1, member_type_2;
{
    Object elt_1, ab_loop_list_, ab_loop_it_, elt_2, ab_loop_list__1, temp;

    x_note_fn_call(80,81);
    elt_1 = Nil;
    ab_loop_list_ = CDR(member_type_1);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elt_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    elt_2 = Nil;
    ab_loop_list__1 = CDR(member_type_2);
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    elt_2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = EQ(elt_1,elt_2) ? T : Nil;
    if (temp);
    else
	temp = evaluation_value_eql(2,elt_1,elt_2);
    ab_loop_it_ = temp;
    if (ab_loop_it_)
	goto end_1;
    goto next_loop_1;
  end_loop_1:
    ab_loop_it_ = Qnil;
  end_1:;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

/* MEMBER-TYPE-SPECIFICATION-SUBTYPE-OF-SYMBOLIC-TYPE-P */
Object member_type_specification_subtype_of_symbolic_type_p(member_type,
	    datum_type)
    Object member_type, datum_type;
{
    Object elt_1, ab_loop_list_, elt_type, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(80,82);
    PUSH_SPECIAL_WITH_SYMBOL(Datum_type,Qdatum_type,datum_type,0);
      elt_1 = Nil;
      ab_loop_list_ = CDR(member_type);
      elt_type = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      elt_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      elt_type = evaluation_value_type(elt_1);
      if ( !(EQ(elt_type,Datum_type) || 
	      symbolic_type_specification_subtype_p(elt_type,Datum_type))) {
	  temp = Nil;
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      temp = T;
      goto end_1;
      temp = Qnil;
    end_1:;
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* MEMBER-TYPE-SPECIFICATION-SUBTYPE-P */
Object member_type_specification_subtype_p(member_type_1,member_type_2)
    Object member_type_1, member_type_2;
{
    Object elt_1, ab_loop_list_, elt_2, ab_loop_list__1, ab_loop_it_, temp;
    char temp_1;

    x_note_fn_call(80,83);
    elt_1 = Nil;
    ab_loop_list_ = CDR(member_type_1);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elt_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    elt_2 = Nil;
    ab_loop_list__1 = CDR(member_type_2);
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    elt_2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = EQ(elt_1,elt_2) ? T : Nil;
    if (temp);
    else
	temp = evaluation_value_eql(2,elt_1,elt_2);
    ab_loop_it_ = temp;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp_1 = TRUEP(Qnil);
  end_1:;
    if ( !temp_1) {
	temp = Nil;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = T;
    goto end_2;
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

/* MEMBER-TYPE-SPECIFICATION-NOT-SUBTYPE-OF-SYMBOLIC-TYPE-P */
Object member_type_specification_not_subtype_of_symbolic_type_p(member_type,
	    datum_type)
    Object member_type, datum_type;
{
    Object elt_1, ab_loop_list_, elt_type, ab_loop_it_, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(80,84);
    PUSH_SPECIAL_WITH_SYMBOL(Datum_type,Qdatum_type,datum_type,0);
      elt_1 = Nil;
      ab_loop_list_ = CDR(member_type);
      elt_type = Nil;
      ab_loop_it_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      elt_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      elt_type = evaluation_value_type(elt_1);
      ab_loop_it_ =  !(EQ(elt_type,Datum_type) || 
	      symbolic_type_specification_subtype_p(elt_type,Datum_type)) ?
	       T : Nil;
      if (ab_loop_it_) {
	  temp = ab_loop_it_;
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      temp = Qnil;
    end_1:;
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* MEMBER-TYPE-SPECIFICATION-NOT-SUBTYPE-P */
Object member_type_specification_not_subtype_p(member_type_1,member_type_2)
    Object member_type_1, member_type_2;
{
    Object elt_1, ab_loop_list_, ab_loop_it_, elt_2, ab_loop_list__1, temp;

    x_note_fn_call(80,85);
    elt_1 = Nil;
    ab_loop_list_ = CDR(member_type_1);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elt_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    elt_2 = Nil;
    ab_loop_list__1 = CDR(member_type_2);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    elt_2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(elt_1,elt_2) || evaluation_value_eql(2,elt_1,elt_2)) {
	ab_loop_it_ = Nil;
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    ab_loop_it_ = T;
    goto end_1;
    ab_loop_it_ = Qnil;
  end_1:;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

Object The_type_description_of_uuid_block = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_uuid_blocks, Qchain_of_available_uuid_blocks);

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_block_count, Quuid_block_count);

Object Chain_of_available_uuid_blocks_vector = UNBOUND;

/* UUID-BLOCK-STRUCTURE-MEMORY-USAGE */
Object uuid_block_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,86);
    temp = Uuid_block_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UUID-BLOCK-COUNT */
Object outstanding_uuid_block_count()
{
    Object def_structure_uuid_block_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,87);
    gensymed_symbol = IFIX(Uuid_block_count);
    def_structure_uuid_block_variable = Chain_of_available_uuid_blocks;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_uuid_block_variable))
	goto end_loop;
    def_structure_uuid_block_variable = 
	    ISVREF(def_structure_uuid_block_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UUID-BLOCK-INTERNAL-1 */
Object reclaim_uuid_block_internal_1(uuid_block)
    Object uuid_block;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(80,88);
    inline_note_reclaim_cons(uuid_block,Nil);
    structure_being_reclaimed = uuid_block;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_uuid_block_item_reference_table(ISVREF(uuid_block,(SI_Long)3L));
      SVREF(uuid_block,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_uuid_blocks_vector,
	    IFIX(Current_thread_index));
    SVREF(uuid_block,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_uuid_blocks_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = uuid_block;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UUID-BLOCK */
Object reclaim_structure_for_uuid_block(uuid_block)
    Object uuid_block;
{
    x_note_fn_call(80,89);
    return reclaim_uuid_block_internal_1(uuid_block);
}

static Object Qg2_defstruct_structure_name_uuid_block_g2_struct;  /* g2-defstruct-structure-name::uuid-block-g2-struct */

/* MAKE-PERMANENT-UUID-BLOCK-STRUCTURE-INTERNAL */
Object make_permanent_uuid_block_structure_internal()
{
    Object def_structure_uuid_block_variable, defstruct_g2_uuid_block_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,90);
    def_structure_uuid_block_variable = Nil;
    atomic_incff_symval(Quuid_block_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_uuid_block_variable = Nil;
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
	defstruct_g2_uuid_block_variable = the_array;
	SVREF(defstruct_g2_uuid_block_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_uuid_block_g2_struct;
	def_structure_uuid_block_variable = defstruct_g2_uuid_block_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_uuid_block_variable);
}

/* MAKE-UUID-BLOCK-1 */
Object make_uuid_block_1(uuid_block_uuid,uuid_block_item_reference_table)
    Object uuid_block_uuid, uuid_block_item_reference_table;
{
    Object def_structure_uuid_block_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(80,91);
    def_structure_uuid_block_variable = 
	    ISVREF(Chain_of_available_uuid_blocks_vector,
	    IFIX(Current_thread_index));
    if (def_structure_uuid_block_variable) {
	svref_arg_1 = Chain_of_available_uuid_blocks_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_uuid_block_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_uuid_block_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_uuid_block_g2_struct;
    }
    else
	def_structure_uuid_block_variable = 
		make_permanent_uuid_block_structure_internal();
    inline_note_allocate_cons(def_structure_uuid_block_variable,Nil);
    SVREF(def_structure_uuid_block_variable,FIX((SI_Long)2L)) = 
	    uuid_block_uuid;
    SVREF(def_structure_uuid_block_variable,FIX((SI_Long)3L)) = 
	    uuid_block_item_reference_table;
    ISVREF(def_structure_uuid_block_variable,(SI_Long)1L) = FIX((SI_Long)1L);
    return VALUES_1(def_structure_uuid_block_variable);
}

/* COPY-UUID-BLOCK */
Object copy_uuid_block(uuid_block)
    Object uuid_block;
{
    Object svref_new_value;

    x_note_fn_call(80,92);
    svref_new_value = FIXNUM_ADD1(ISVREF(uuid_block,(SI_Long)1L));
    SVREF(uuid_block,FIX((SI_Long)1L)) = svref_new_value;
    return VALUES_1(uuid_block);
}

/* RECLAIM-UUID-BLOCK-ITEM-REFERENCE-TABLE */
Object reclaim_uuid_block_item_reference_table(table)
    Object table;
{
    x_note_fn_call(80,93);
    if (CONSP(table))
	reclaim_eval_list_1(table);
    else if (SIMPLE_VECTOR_P(table))
	reclaim_managed_simple_vector(table);
    return VALUES_1(Nil);
}

/* MAKE-UUID-BLOCK-HASH-SKIP-LIST-SENTINEL */
Object make_uuid_block_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(80,94);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* MUTATE-UUID-BLOCK-HASH-SKIP-LIST-ENTRY */
Object mutate_uuid_block_hash_skip_list_entry(node,new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(80,95);
    uuid_block_hash_key_reclaimer(ISVREF(node,(SI_Long)2L));
    uuid_block_hash_entry_reclaimer(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_uuid_block_hash_skip_list_entry = UNBOUND;

static Object Quuid_eq;            /* uuid= */

/* CLEAR-UUID-BLOCK-HASH-SKIP-LIST */
Object clear_uuid_block_hash_skip_list(uuid_block_hash_skip_list)
    Object uuid_block_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_key, old_entry;
    Object result;

    x_note_fn_call(80,96);
    head = M_CAR(M_CDR(uuid_block_hash_skip_list));
    tail = M_CDR(M_CDR(uuid_block_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Quuid_eq),temp,
	    uuid_block_hash_skip_list,FIX((SI_Long)31L),sxhashw(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	uuid_block_hash_key_reclaimer(old_key);
    if (old_entry)
	uuid_block_hash_entry_reclaimer(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(uuid_block_hash_skip_list);
}

static Object Quuid_block_hash;    /* uuid-block-hash */

static Object Qlookup;             /* lookup */

/* MAKE-UUID-BLOCK-HASH-FUNCTION */
Object make_uuid_block_hash_function()
{
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,97);
    tail = make_uuid_block_hash_skip_list_sentinel(Most_positive_fixnum,Nil);
    head = make_uuid_block_hash_skip_list_sentinel(Most_negative_fixnum,tail);
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
    M_CAR(gensymed_symbol) = Quuid_block_hash;
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
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    return VALUES_1(gensymed_symbol);
}

/* RECLAIM-UUID-BLOCK-HASH-TABLE */
Object reclaim_uuid_block_hash_table(table)
    Object table;
{
    Object head, tail, element_qm, key_qm, temp, old_key, old_entry, last_1;
    Object next_qm, temp_1, svref_arg_2;
    Object result;

    x_note_fn_call(80,98);
    head = M_CAR(M_CDR(table));
    tail = M_CDR(M_CDR(table));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Quuid_eq),temp,table,
	    FIX((SI_Long)31L),sxhashw(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	uuid_block_hash_key_reclaimer(old_key);
    if (old_entry)
	uuid_block_hash_entry_reclaimer(old_entry);
    goto next_loop;
  end_loop:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(table) = Nil;
    M_CADR(table) = Nil;
    M_CAR(table) = Nil;
    if (table) {
	last_1 = table;
	next_qm = Nil;
      next_loop_1:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_1;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_1;
      end_loop_1:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = table;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = table;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    return VALUES_1(Nil);
}

/* UUID-BLOCK-HASH-KEY-RECLAIMER */
Object uuid_block_hash_key_reclaimer(uuid)
    Object uuid;
{
    x_note_fn_call(80,99);
    reclaim_wide_string(uuid);
    return VALUES_1(Nil);
}

/* UUID-BLOCK-HASH-ENTRY-RECLAIMER */
Object uuid_block_hash_entry_reclaimer(uuid_block)
    Object uuid_block;
{
    x_note_fn_call(80,100);
    reclaim_uuid_block_internal_1(uuid_block);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_block_hash_table, Quuid_block_hash_table);

/* RECLAIM-UUID-BLOCK */
Object reclaim_uuid_block(uuid_block)
    Object uuid_block;
{
    Object svref_new_value, gensymed_symbol, temp, old_key, old_entry;
    Object result;

    x_note_fn_call(80,101);
    svref_new_value = FIXNUM_SUB1(ISVREF(uuid_block,(SI_Long)1L));
    SVREF(uuid_block,FIX((SI_Long)1L)) = svref_new_value;
    if (IFIX(ISVREF(uuid_block,(SI_Long)1L)) == (SI_Long)0L) {
	gensymed_symbol = ISVREF(uuid_block,(SI_Long)2L);
	temp = Uuid_block_hash_table;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Quuid_eq),
		gensymed_symbol,temp,FIX((SI_Long)31L),
		sxhashw(gensymed_symbol));
	MVS_2(result,old_key,old_entry);
	if (old_key)
	    uuid_block_hash_key_reclaimer(old_key);
	if (old_entry)
	    uuid_block_hash_entry_reclaimer(old_entry);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_hash_block_table_for_merge_kb, Quuid_hash_block_table_for_merge_kb);

static Object Qitem_reference;     /* item-reference */

/* ALLOCATE-EVALUATION-ITEM-REFERENCE */
Object allocate_evaluation_item_reference(uuid_block,uuid_offset,
	    referenced_item)
    Object uuid_block, uuid_offset, referenced_item;
{
    Object held_vector, new_item_reference, svref_new_value;

    x_note_fn_call(80,102);
    held_vector = allocate_managed_simple_vector(FIX((SI_Long)4L));
    new_item_reference = eval_cons_1(held_vector,Qitem_reference);
    ISVREF(held_vector,(SI_Long)0L) = FIX((SI_Long)0L);
    svref_new_value = uuid_block ? copy_uuid_block(uuid_block) : Nil;
    SVREF(held_vector,FIX((SI_Long)1L)) = svref_new_value;
    SVREF(held_vector,FIX((SI_Long)2L)) = uuid_offset;
    SVREF(held_vector,FIX((SI_Long)3L)) = referenced_item;
    return VALUES_1(new_item_reference);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* GET-REFERENCE-TO-ITEM-IF-ITEM-FUNCTION */
Object get_reference_to_item_if_item_function(item_or_value)
    Object item_or_value;
{
    Object item_or_value_1, x2;
    char temp;

    x_note_fn_call(80,103);
    item_or_value_1 = item_or_value;
    if (SIMPLE_VECTOR_P(item_or_value_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return get_reference_to_item(item_or_value_1);
    else
	return VALUES_1(item_or_value_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Lazy_assignment_of_uuids, Qlazy_assignment_of_uuids);

/* GET-ITEM-REFERENCE-FOR-NEW-UUID */
Object get_item_reference_for_new_uuid()
{
    Object item_reference, temp, uuid;

    x_note_fn_call(80,104);
    if (Lazy_assignment_of_uuids) {
	item_reference = allocate_evaluation_item_reference(Nil,Nil,Nil);
	atomic_incff_svslot(M_CAR(item_reference),FIX((SI_Long)0L),
		FIX((SI_Long)1L));
	temp = item_reference;
    }
    else {
	uuid = make_uuid();
	temp = get_item_reference_for_uuid(uuid,T,T);
	reclaim_wide_string(uuid);
    }
    return VALUES_1(temp);
}

/* GET-BLOCK-AND-OFFSET-FOR-ITEM-REFERENCE */
Object get_block_and_offset_for_item_reference(vector_1)
    Object vector_1;
{
    Object uuid;

    x_note_fn_call(80,105);
    uuid = make_uuid();
    get_item_reference_for_uuid(uuid,vector_1,Nil);
    reclaim_wide_string(uuid);
    return VALUES_1(Nil);
}

/* VALID-UUID-P */
Object valid_uuid_p(str)
    Object str;
{
    Object temp;
    SI_Long length_1;

    x_note_fn_call(80,106);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(str) != (SI_Long)0L) {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(str));
	temp = FIXNUM_EQ(FIX(UBYTE_16_ISAREF_1(str,length_1 - (SI_Long)2L) 
		+ ((UBYTE_16_ISAREF_1(str,length_1 - (SI_Long)1L) & 
		(SI_Long)8191L) << (SI_Long)16L)),Uuid_string_length) ? T :
		 Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-ITEM-REFERENCE-FOR-UUID */
Object get_item_reference_for_uuid(uuid,create_p,need_copy_p)
    Object uuid, create_p, need_copy_p;
{
    Object uuid_block_key, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, uuid_block;
    Object item_reference_table, item_reference_qm, table_item_reference;
    Object ab_loop_list_, held_vector, temp_2, actual_uuid_block_key;
    Object gensymed_symbol, temp_3, eval_push_modify_macro_arg, car_1, cdr_1;
    Object table, offset;
    SI_Long uuid_least_16_bits, uuid_offset, uuid_block_least_16_bits;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, index_1;
    Object result;

    x_note_fn_call(80,107);
    if (CONSP(uuid) && EQ(M_CDR(uuid),Qitem_reference))
	return VALUES_1(uuid);
    if ( !TRUEP(valid_uuid_p(uuid)))
	return VALUES_1(Nil);
    uuid_block_key = uuid;
    uuid_least_16_bits = UBYTE_16_ISAREF_1(uuid,(SI_Long)0L);
    uuid_offset = uuid_least_16_bits & IFIX(Uuid_offset_mask);
    uuid_block_least_16_bits = uuid_least_16_bits &  ~IFIX(Uuid_offset_mask);
    UBYTE_16_ISASET_1(uuid_block_key,(SI_Long)0L,uuid_block_least_16_bits);
    skip_list = CDR(Uuid_block_hash_table);
    key_value = uuid_block_key;
    key_hash_value = IFIX(sxhashw(uuid_block_key));
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
	    key_hash_value &&  !TRUEP(uuid_eq(key_value,ISVREF(curr,
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
    uuid_block = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (uuid_eq(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    item_reference_table = uuid_block ? ISVREF(uuid_block,(SI_Long)3L) : Nil;
    item_reference_qm = Nil;
    if ( !TRUEP(item_reference_table));
    else if (CONSP(item_reference_table)) {
	table_item_reference = Nil;
	ab_loop_list_ = item_reference_table;
	held_vector = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	table_item_reference = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	held_vector = M_CAR(table_item_reference);
	if (uuid_offset == IFIX(ISVREF(held_vector,(SI_Long)2L))) {
	    item_reference_qm = table_item_reference;
	    goto end_2;
	}
	goto next_loop_3;
      end_loop_3:
      end_2:;
    }
    else if (SIMPLE_VECTOR_P(item_reference_table))
	item_reference_qm = ISVREF(item_reference_table,uuid_offset);
    if ( !TRUEP(item_reference_qm) && create_p) {
	if (VECTORP(create_p)) {
	    temp_2 = uuid_block ? copy_uuid_block(uuid_block) : Nil;
	    SVREF(create_p,FIX((SI_Long)1L)) = temp_2;
	    ISVREF(create_p,(SI_Long)2L) = FIX(uuid_offset);
	    item_reference_qm = 
		    get_reference_to_item_no_copy(ISVREF(create_p,
		    (SI_Long)3L));
	}
	else
	    item_reference_qm = 
		    allocate_evaluation_item_reference(uuid_block,
		    FIX(uuid_offset),Nil);
	if ( !TRUEP(item_reference_table)) {
	    if (uuid_block) {
		temp_2 = eval_cons_1(item_reference_qm,Nil);
		SVREF(uuid_block,FIX((SI_Long)3L)) = temp_2;
	    }
	    else {
		actual_uuid_block_key = copy_wide_string(uuid_block_key);
		uuid_block = make_uuid_block_1(actual_uuid_block_key,
			eval_cons_1(item_reference_qm,Nil));
		temp_2 = M_CAR(item_reference_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = uuid_block;
		gensymed_symbol = actual_uuid_block_key;
		temp_1 = Uuid_block_hash_table;
		temp = Fp_mutate_uuid_block_hash_skip_list_entry;
		temp_3 = sxhashw(gensymed_symbol);
		set_skip_list_entry(temp_1,FIX((SI_Long)31L),Quuid_eq,temp,
			T,gensymed_symbol,temp_3,uuid_block);
	    }
	}
	else if (CONSP(item_reference_table)) {
	    if (FIXNUM_LT(length(item_reference_table),
		    Item_reference_table_list_length_limit)) {
		eval_push_modify_macro_arg = item_reference_qm;
		car_1 = eval_push_modify_macro_arg;
		cdr_1 = ISVREF(uuid_block,(SI_Long)3L);
		temp_2 = eval_cons_1(car_1,cdr_1);
		SVREF(uuid_block,FIX((SI_Long)3L)) = temp_2;
	    }
	    else {
		table = allocate_managed_simple_vector(Uuid_block_table_size);
		index_1 = (SI_Long)0L;
	      next_loop_4:
		if (index_1 >= IFIX(Uuid_block_table_size))
		    goto end_loop_4;
		ISVREF(table,index_1) = Nil;
		index_1 = index_1 + (SI_Long)1L;
		goto next_loop_4;
	      end_loop_4:;
		table_item_reference = Nil;
		ab_loop_list_ = item_reference_table;
		held_vector = Nil;
		offset = Nil;
	      next_loop_5:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
		table_item_reference = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		held_vector = M_CAR(table_item_reference);
		offset = ISVREF(held_vector,(SI_Long)2L);
		SVREF(table,offset) = table_item_reference;
		goto next_loop_5;
	      end_loop_5:;
		reclaim_eval_list_1(item_reference_table);
		ISVREF(table,uuid_offset) = item_reference_qm;
		SVREF(uuid_block,FIX((SI_Long)3L)) = table;
	    }
	}
	else if (SIMPLE_VECTOR_P(item_reference_table))
	    ISVREF(item_reference_table,uuid_offset) = item_reference_qm;
    }
    UBYTE_16_ISASET_1(uuid,(SI_Long)0L,uuid_least_16_bits);
    if (item_reference_qm && need_copy_p)
	atomic_incff_svslot(M_CAR(item_reference_qm),FIX((SI_Long)0L),
		FIX((SI_Long)1L));
    return VALUES_1(item_reference_qm);
}

/* EVALUATION-ITEM-REFERENCE-UUID */
Object evaluation_item_reference_uuid(item_reference)
    Object item_reference;
{
    Object held_vector, vector_1, uuid_block, uuid_offset, uuid_string;
    SI_Long aref_new_value;

    x_note_fn_call(80,108);
    held_vector = M_CAR(item_reference);
    vector_1 = held_vector;
    if ( !TRUEP(ISVREF(vector_1,(SI_Long)1L))) {
	if (ISVREF(vector_1,(SI_Long)3L))
	    get_block_and_offset_for_item_reference(vector_1);
    }
    uuid_block = ISVREF(vector_1,(SI_Long)1L);
    if (uuid_block);
    else
	return VALUES_1(Nil);
    uuid_offset = ISVREF(held_vector,(SI_Long)2L);
    uuid_string = copy_wide_string(ISVREF(uuid_block,(SI_Long)2L));
    aref_new_value = UBYTE_16_ISAREF_1(uuid_string,(SI_Long)0L) | 
	    IFIX(uuid_offset);
    UBYTE_16_ISASET_1(uuid_string,(SI_Long)0L,aref_new_value);
    return VALUES_1(uuid_string);
}

/* HASH-ITEM-REFERENCE */
Object hash_item_reference(item_reference)
    Object item_reference;
{
    Object held_vector, vector_1, uuid_block_qm, uuid_offset_qm;
    Object uuid_string_qm, temp_1;
    SI_Long temp;

    x_note_fn_call(80,109);
    held_vector = M_CAR(item_reference);
    vector_1 = held_vector;
    if ( !TRUEP(ISVREF(vector_1,(SI_Long)1L))) {
	if (ISVREF(vector_1,(SI_Long)3L))
	    get_block_and_offset_for_item_reference(vector_1);
    }
    uuid_block_qm = ISVREF(vector_1,(SI_Long)1L);
    uuid_offset_qm = ISVREF(held_vector,(SI_Long)2L);
    uuid_string_qm = uuid_block_qm ? ISVREF(uuid_block_qm,(SI_Long)2L) : Nil;
    if (uuid_offset_qm && uuid_string_qm) {
	temp = IFIX(sxhashw(uuid_string_qm));
	temp_1 = FIX(IFIX(uuid_offset_qm) + (temp >>  -  - (SI_Long)1L));
    }
    else
	temp_1 = FIX((SI_Long)0L);
    return VALUES_1(temp_1);
}

/* RECLAIM-EVALUATION-ITEM-REFERENCE */
Object reclaim_evaluation_item_reference(item_reference)
    Object item_reference;
{
    Object held_vector, uuid_block, item_reference_table, uuid_offset, temp;
    Object svref_arg_2;
    SI_Long ref_count, svref_new_value;

    x_note_fn_call(80,110);
    held_vector = M_CAR(item_reference);
    ref_count = IFIX(ISVREF(held_vector,(SI_Long)0L));
    if (ref_count == (SI_Long)1L) {
	uuid_block = ISVREF(held_vector,(SI_Long)1L);
	item_reference_table = uuid_block ? ISVREF(uuid_block,(SI_Long)3L) 
		: Nil;
	uuid_offset = ISVREF(held_vector,(SI_Long)2L);
	if (CONSP(item_reference_table)) {
	    temp = delete_eval_element_1(item_reference,item_reference_table);
	    SVREF(uuid_block,FIX((SI_Long)3L)) = temp;
	}
	else if (SIMPLE_VECTOR_P(item_reference_table))
	    SVREF(item_reference_table,uuid_offset) = Nil;
	if (uuid_block) {
	    reclaim_uuid_block(uuid_block);
	    SVREF(held_vector,FIX((SI_Long)1L)) = Nil;
	}
	reclaim_managed_simple_vector(held_vector);
    }
    else if (ref_count < (SI_Long)1L)
	error((SI_Long)2L,
		"Item-Reference reference count zero or below in ~a.",
		item_reference);
    else {
	svref_new_value = ref_count - (SI_Long)1L;
	ISVREF(held_vector,(SI_Long)0L) = FIX(svref_new_value);
	item_reference = Nil;
    }
    if (item_reference) {
	inline_note_reclaim_cons(item_reference,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = item_reference;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item_reference;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item_reference;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item_reference;
	}
	M_CDR(item_reference) = Nil;
    }
    return VALUES_1(Nil);
}

/* RECLAIM-IF-EVALUATION-ITEM-REFERENCE */
Object reclaim_if_evaluation_item_reference(item_reference_qm)
    Object item_reference_qm;
{
    x_note_fn_call(80,111);
    if (CONSP(item_reference_qm) && EQ(M_CDR(item_reference_qm),
	    Qitem_reference))
	return reclaim_evaluation_item_reference(item_reference_qm);
    else
	return VALUES_1(Nil);
}

/* COPY-EVALUATION-ITEM-REFERENCE */
Object copy_evaluation_item_reference(item_reference)
    Object item_reference;
{
    Object held_vector;

    x_note_fn_call(80,112);
    held_vector = M_CAR(item_reference);
    atomic_incff_svslot(held_vector,FIX((SI_Long)0L),FIX((SI_Long)1L));
    return VALUES_1(item_reference);
}

/* EVALUATION-ITEM-REFERENCE-EQL */
Object evaluation_item_reference_eql(item_reference_1,item_reference_2)
    Object item_reference_1, item_reference_2;
{
    Object temp;

    x_note_fn_call(80,113);
    temp = EQ(item_reference_1,item_reference_2) ? T : Nil;
    return VALUES_1(temp);
}

/* EVALUATION-ITEM-REFERENCE-= */
Object evaluation_item_reference_eq(item_reference_1,item_reference_2)
    Object item_reference_1, item_reference_2;
{
    x_note_fn_call(80,114);
    GENSYM_RETURN_ONE(EQ(item_reference_1,item_reference_2) ? T : Nil);
    return VALUES_1(Nil);
}

static Object string_constant_1;   /* "item-reference (" */

static Object string_constant_2;   /* ")" */

/* WRITE-EVALUATION-ITEM-REFERENCE */
Object write_evaluation_item_reference(item_reference)
    Object item_reference;
{
    Object uuid_qm;

    x_note_fn_call(80,115);
    tformat(1,string_constant_1);
    uuid_qm = evaluation_item_reference_uuid(item_reference);
    if (uuid_qm) {
	twrite_uuid_printed_representation_as_string(uuid_qm);
	reclaim_wide_string(uuid_qm);
    }
    tformat(1,string_constant_2);
    return VALUES_1(Nil);
}

/* ITEM-REFERENCE-TYPE-SPECIFICATION-P */
Object item_reference_type_specification_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(80,116);
    temp = CONSP(thing) ? (EQ(M_CAR(thing),Qitem_reference) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* GET-ITEM-OR-ITEM-LIST-FOR-UUID */
Object get_item_or_item_list_for_uuid(uuid)
    Object uuid;
{
    Object item_reference_qm, temp;

    x_note_fn_call(80,117);
    item_reference_qm = get_item_reference_for_uuid(uuid,Nil,Nil);
    temp = item_reference_qm ? ISVREF(M_CAR(item_reference_qm),
	    (SI_Long)3L) : Nil;
    return VALUES_1(temp);
}

static Object Qitem;               /* item */

/* THE-ITEM-HAVING-UUID */
Object the_item_having_uuid(class_qm,denotation)
    Object class_qm, denotation;
{
    Object item_or_item_list, item_qm, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(80,118);
    item_or_item_list = valid_uuid_p(denotation) ? 
	    get_item_or_item_list_for_uuid(denotation) : 
	    get_instance_from_uuid_representation(denotation);
    item_qm = CONSP(item_or_item_list) ? M_CAR(item_or_item_list) : 
	    item_or_item_list;
    if (item_qm) {
	temp =  !TRUEP(class_qm);
	if (temp);
	else if (EQ(class_qm,Qitem))
	    temp = TRUEP(ISVREF(ISVREF(item_qm,(SI_Long)1L),(SI_Long)16L));
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_qm,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item_qm,(SI_Long)1L),
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
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(item_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Collecting_denotation_errors_p, Qcollecting_denotation_errors_p);

DEFINE_VARIABLE_WITH_SYMBOL(Denotation_error_list, Qdenotation_error_list);

static Object Qthe_item_having_uuid;  /* the-item-having-uuid */

/* FIND-FRAME-FOR-DENOTATION */
Object find_frame_for_denotation varargs_1(int, n)
{
    Object denotation;
    Object class_1, x2, temp_1, sub_frame_qm, thing;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(80,119);
    INIT_ARGS_nonrelocating();
    denotation = REQUIRED_ARG_nonrelocating();
    class_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SIMPLE_VECTOR_P(denotation) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(denotation)) > (SI_Long)2L &&  
	    !EQ(ISVREF(denotation,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(denotation,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = denotation;
    else if (SYMBOLP(denotation))
	temp_1 = get_instance_with_name_if_any(class_1,denotation);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(denotation) != (SI_Long)0L)
	temp_1 = the_item_having_uuid(Qitem,denotation);
    else {
	if (CONSP(denotation) && EQ(M_CAR(denotation),Qthe)) {
	    temp_1 = SECOND(denotation);
	    temp = SYMBOLP(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_frame_qm = find_frame_for_denotation(2,THIRD(denotation),Nil);
	    temp_1 = sub_frame_qm ? 
		    frame_or_evaluation_value_user_attribute_value(sub_frame_qm,
		    SECOND(denotation),Nil) : Nil;
	}
	else {
	    if (CONSP(denotation) && EQ(M_CAR(denotation),
		    Qthe_item_having_uuid)) {
		thing = THIRD(denotation);
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		temp_1 = the_item_having_uuid(SECOND(denotation),
			THIRD(denotation));
	    else
		temp_1 = Nil;
	}
    }
    if (temp_1)
	return VALUES_1(temp_1);
    else if (Collecting_denotation_errors_p) {
	Denotation_error_list = phrase_cons(denotation,Denotation_error_list);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* C-UUID-EQ */
Object c_uuid_eq(uuid1,uuid2)
    Object uuid1, uuid2;
{
    Object temp;

    x_note_fn_call(80,120);
    temp = FIX(g2ext_uuid_eq(UBYTE_16_SARRAY_TO_USHORT_PTR(uuid1),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(uuid2)));
    return VALUES_1(temp);
}

/* UUID= */
Object uuid_eq(uuid1,uuid2)
    Object uuid1, uuid2;
{
    x_note_fn_call(80,121);
    return VALUES_1(IFIX(c_uuid_eq(uuid1,uuid2)) == (SI_Long)0L ? T : Nil);
}

/* UUID< */
Object uuid_lt(uuid1,uuid2)
    Object uuid1, uuid2;
{
    SI_Long c1, c2;

    x_note_fn_call(80,122);
    c1 = (SI_Long)0L;
    c2 = (SI_Long)0L;
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)3L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)3L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)2L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)2L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)1L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)1L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)0L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)0L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)4L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)4L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)5L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)5L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)6L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)6L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    c1 = UBYTE_16_ISAREF_1(uuid1,(SI_Long)7L);
    c2 = UBYTE_16_ISAREF_1(uuid2,(SI_Long)7L);
    if ( !(c1 == c2))
	return VALUES_1(c1 < c2 ? T : Nil);
    return VALUES_1(Nil);
}

/* ALLOCATE-NEW-NONCE-INTERNAL */
Object allocate_new_nonce_internal()
{
    Object always_use_current_time_for_uuid;
    Declare_special(1);
    Object result;

    x_note_fn_call(80,123);
    always_use_current_time_for_uuid = T;
    PUSH_SPECIAL_WITH_SYMBOL(Always_use_current_time_for_uuid,Qalways_use_current_time_for_uuid,always_use_current_time_for_uuid,
	    0);
      result = make_uuid();
    POP_SPECIAL();
    return result;
}

static Object string_constant_3;   /* "UUID" */

/* CONVERT-UUID-REPRESENTATION-TO-INTERNAL */
Object convert_uuid_representation_to_internal(representation_string)
    Object representation_string;
{
    x_note_fn_call(80,124);
    return convert_binary_string_representation_to_internal(representation_string,
	    Uuid_string_length,string_constant_3);
}

static Object string_constant_4;   /* "illegal character (~c) in a ~a string" */

static Object string_constant_5;   /* "a ~a string must be ~d hex digits, but this has ~d" */

static Object string_constant_6;   /* "a ~a string must have a total number of hex digits that is a multiple of four" */

/* CONVERT-BINARY-STRING-REPRESENTATION-TO-INTERNAL */
Object convert_binary_string_representation_to_internal(representation_string,
	    required_string_length_qm,use_for_warnings)
    Object representation_string, required_string_length_qm, use_for_warnings;
{
    Object character_1, value_of_hex_digit_qm, temp, hex_digit_count;
    Object wide_string_bv16, wide_string_bv16_1, wide_string;
    Object hex_digit_position, wide_string_position;
    SI_Long i, ab_loop_bind_, ab_loopvar_, string_length, bv16_length, temp_1;
    SI_Long aref_new_value, length_1, j;

    x_note_fn_call(80,125);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(representation_string));
    character_1 = Nil;
    value_of_hex_digit_qm = Nil;
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(representation_string,i));
    value_of_hex_digit_qm = digit_char_pw_function(character_1,
	    FIX((SI_Long)16L));
    if ( !TRUEP(value_of_hex_digit_qm) &&  
	    !TRUEP(horizontal_space_p(character_1))) {
	temp = tformat_text_string(3,string_constant_4,character_1,
		use_for_warnings);
	return VALUES_2(Nil,temp);
    }
    if (value_of_hex_digit_qm)
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    hex_digit_count = FIX(ab_loopvar_);
    goto end_1;
    hex_digit_count = Qnil;
  end_1:;
    string_length = IFIX(hex_digit_count) >>  -  - (SI_Long)2L;
    if (required_string_length_qm &&  !(IFIX(required_string_length_qm) == 
	    string_length && (SI_Long)0L == ((SI_Long)3L & 
	    IFIX(hex_digit_count)))) {
	temp = tformat_text_string(4,string_constant_5,use_for_warnings,
		FIX(IFIX(required_string_length_qm) << (SI_Long)2L),
		FIX(string_length));
	return VALUES_2(Nil,temp);
    }
    else if ( !((SI_Long)0L == ((SI_Long)3L & IFIX(hex_digit_count)))) {
	temp = tformat_text_string(2,string_constant_6,use_for_warnings);
	return VALUES_2(Nil,temp);
    }
    else {
	wide_string_bv16 = allocate_byte_vector_16(FIX(string_length + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp_1 = bv16_length - (SI_Long)2L;
	aref_new_value = string_length & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	temp_1 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | string_length >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,string_length,(SI_Long)0L);
	wide_string_bv16_1 = wide_string_bv16;
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16_1));
	length_1 = UBYTE_16_ISAREF_1(wide_string_bv16_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16_1,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	UBYTE_16_ISASET_1(wide_string_bv16_1,length_1,(SI_Long)1L);
	wide_string = wide_string_bv16_1;
    }
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(wide_string));
  next_loop_1:
    if (j >= ab_loop_bind_)
	goto end_loop_1;
    UBYTE_16_ISASET_1(wide_string,j,(SI_Long)0L);
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    hex_digit_position = FIX((SI_Long)12L);
    wide_string_position = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(representation_string));
    character_1 = Nil;
    value_of_hex_digit_qm = Nil;
  next_loop_2:
    if (i >= ab_loop_bind_)
	goto end_loop_2;
    character_1 = FIX(UBYTE_16_ISAREF_1(representation_string,i));
    value_of_hex_digit_qm = digit_char_pw_function(character_1,
	    FIX((SI_Long)16L));
    if (value_of_hex_digit_qm) {
	temp_1 = UBYTE_16_ISAREF_1(wide_string,IFIX(wide_string_position)) 
		+ IFIX(ash(value_of_hex_digit_qm,hex_digit_position));
	UBYTE_16_ISASET_1(wide_string,IFIX(wide_string_position),temp_1);
	if (IFIX(hex_digit_position) == (SI_Long)0L) {
	    hex_digit_position = FIX((SI_Long)12L);
	    wide_string_position = FIXNUM_ADD1(wide_string_position);
	}
	else {
	    temp_1 = IFIX(hex_digit_position) - (SI_Long)4L;
	    hex_digit_position = FIX(temp_1);
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:;
    return VALUES_1(wide_string);
}

/* TWRITE-UUID-PRINTED-REPRESENTATION-AS-STRING */
Object twrite_uuid_printed_representation_as_string(uuid)
    Object uuid;
{
    Object string_to_reclaim;

    x_note_fn_call(80,126);
    if (CONSP(uuid) && EQ(M_CDR(uuid),Qitem_reference)) {
	uuid = evaluation_item_reference_uuid(uuid);
	string_to_reclaim = uuid;
    }
    else
	string_to_reclaim = Nil;
    if (uuid) {
	twrite_character(FIX((SI_Long)34L));
	twrite_uuid_printed_representation(uuid);
	twrite_character(FIX((SI_Long)34L));
	if (string_to_reclaim)
	    reclaim_wide_string(string_to_reclaim);
    }
    return VALUES_1(Nil);
}

/* EQ-ITEM-HASH-TABLE-RECLAIMER */
Object eq_item_hash_table_reclaimer(item_reference_qm)
    Object item_reference_qm;
{
    x_note_fn_call(80,127);
    if (CONSP(item_reference_qm) && EQ(M_CDR(item_reference_qm),
	    Qitem_reference))
	return reclaim_evaluation_item_reference(item_reference_qm);
    else
	return VALUES_1(Nil);
}

static Object Qeq_item_hash_table_reclaimer;  /* eq-item-hash-table-reclaimer */

/* MAKE-EQ-ITEM-HASH-TABLE */
Object make_eq_item_hash_table(size)
    Object size;
{
    x_note_fn_call(80,128);
    return make_eq_hash_table(size,
	    SYMBOL_FUNCTION(Qeq_item_hash_table_reclaimer),
	    SYMBOL_FUNCTION(Qeq_item_hash_table_reclaimer));
}

/* RECLAIM-EQ-ITEM-HASH-TABLE */
Object reclaim_eq_item_hash_table(table)
    Object table;
{
    x_note_fn_call(80,129);
    return reclaim_eq_hash_table(table);
}

/* EQ-ITEM-GETHASH */
Object eq_item_gethash(table,key_object,default_value_qm)
    Object table, key_object, default_value_qm;
{
    Object x2, result_reference, item, temp_1;
    char temp;

    x_note_fn_call(80,130);
    if (SIMPLE_VECTOR_P(key_object) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(key_object)) > (SI_Long)2L &&  
	    !EQ(ISVREF(key_object,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(key_object,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    result_reference = eq_gethash(table,temp ? uuid_function(key_object) : 
	    key_object,default_value_qm);
    if (CONSP(result_reference) && EQ(M_CDR(result_reference),
		Qitem_reference)) {
	item = ISVREF(M_CAR(result_reference),(SI_Long)3L);
	temp_1 = item;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    eq_remhash(table,key_object);
	    return VALUES_1(default_value_qm);
	}
    }
    else
	return VALUES_1(result_reference);
}

Object Bogus_value_for_default = UNBOUND;

/* EQ-ITEM-PUTHASH */
Object eq_item_puthash(table,key_object,value_object)
    Object table, key_object, value_object;
{
    Object x2, key_is_item_p, item_or_value, internal_key, temp_1;
    Object key_is_old_item;
    char temp;

    x_note_fn_call(80,131);
    if (SIMPLE_VECTOR_P(key_object) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(key_object)) > (SI_Long)2L &&  
	    !EQ(ISVREF(key_object,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(key_object,(SI_Long)1L);
	key_is_item_p = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	key_is_item_p = Nil;
    item_or_value = key_object;
    if (SIMPLE_VECTOR_P(item_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    internal_key = temp ? get_reference_to_item(item_or_value) : item_or_value;
    if (key_is_item_p) {
	temp_1 = eq_gethash(table,key_object,Bogus_value_for_default);
	key_is_old_item =  !EQ(temp_1,Bogus_value_for_default) ? T : Nil;
    }
    else
	key_is_old_item = Nil;
    item_or_value = value_object;
    if (SIMPLE_VECTOR_P(item_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    eq_puthash(table,internal_key,temp ? 
	    get_reference_to_item(item_or_value) : item_or_value);
    if (key_is_old_item)
	return reclaim_if_evaluation_value_function(internal_key);
    else
	return VALUES_1(Nil);
}

/* EQ-ITEM-REMHASH */
Object eq_item_remhash(table,key_object)
    Object table, key_object;
{
    Object item_or_value, x2, temp_1;
    char temp;

    x_note_fn_call(80,132);
    item_or_value = key_object;
    if (SIMPLE_VECTOR_P(item_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = eq_remhash(table,temp ? get_reference_to_item(item_or_value) :
	     item_or_value);
    return VALUES_1(temp_1);
}

/* ALLOCATE-EVALUATION-SEQUENCE */
Object allocate_evaluation_sequence(eval_list_of_contents)
    Object eval_list_of_contents;
{
    Object held_vector, new_sequence, temp, new_value, ab_loop_list_;
    Object item_or_value, x2, svref_new_value;
    SI_Long length_1, index_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(80,133);
    length_1 = IFIX(length(eval_list_of_contents));
    held_vector = allocate_managed_array(1,FIX(length_1 + (SI_Long)1L));
    new_sequence = eval_cons_1(held_vector,Qsequence);
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(held_vector,(SI_Long)2L) = FIX((SI_Long)1L);
    else {
	temp = ISVREF(held_vector,(SI_Long)2L);
	ISVREF(temp,(SI_Long)0L) = FIX((SI_Long)1L);
    }
    index_1 = (SI_Long)1L;
    new_value = Nil;
    ab_loop_list_ = eval_list_of_contents;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    new_value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	item_or_value = new_value;
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	item_or_value = new_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_eval_list_1(eval_list_of_contents);
    return VALUES_1(new_sequence);
}

/* OBTAIN-MUTABLE-EVALUATION-SEQUENCE-COPY */
Object obtain_mutable_evaluation_sequence_copy(sequence)
    Object sequence;
{
    Object temp, length_1, new_sequence;

    x_note_fn_call(80,134);
    if ((FIXNUM_LE(ISVREF(M_CAR(sequence),(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(M_CAR(sequence),
	    (SI_Long)0L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(M_CAR(sequence),(SI_Long)2L),(SI_Long)0L))) 
	    == (SI_Long)1L)
	temp = sequence;
    else {
	length_1 = FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L));
	new_sequence = allocate_empty_evaluation_sequence(length_1);
	copy_evaluation_sequence_elements(sequence,FIX((SI_Long)0L),
		length_1,new_sequence,FIX((SI_Long)0L));
	reclaim_evaluation_sequence(sequence);
	temp = new_sequence;
    }
    return VALUES_1(temp);
}

/* ALLOCATE-NEW-EVALUATION-SEQUENCE-FROM-SIMPLE-VECTOR */
Object allocate_new_evaluation_sequence_from_simple_vector(simple_vector,
	    first_element_index_init,count_init)
    Object simple_vector, first_element_index_init, count_init;
{
    Object held_vector, temp, ab_loop_iter_flag_, item_or_value, x2;
    Object svref_new_value, temp_2;
    SI_Long first_element_index, count_1, source_index, n_1, ab_loop_bind_;
    SI_Long dest_index, svref_arg_2;
    char temp_1;

    x_note_fn_call(80,135);
    first_element_index = IFIX(first_element_index_init);
    count_1 = IFIX(count_init);
    held_vector = allocate_managed_array(1,FIX(count_1 + (SI_Long)1L));
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(held_vector,(SI_Long)2L) = FIX((SI_Long)1L);
    else {
	temp = ISVREF(held_vector,(SI_Long)2L);
	ISVREF(temp,(SI_Long)0L) = FIX((SI_Long)1L);
    }
    source_index = first_element_index;
    n_1 = (SI_Long)0L;
    ab_loop_bind_ = count_1;
    dest_index = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (n_1 >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	dest_index = dest_index + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = dest_index + IFIX(Managed_array_index_offset);
	item_or_value = ISVREF(simple_vector,source_index);
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(dest_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = dest_index & (SI_Long)1023L;
	item_or_value = ISVREF(simple_vector,source_index);
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    ab_loop_iter_flag_ = Nil;
    source_index = source_index + (SI_Long)1L;
    n_1 = n_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_2 = eval_cons_1(held_vector,Qsequence);
    return VALUES_1(temp_2);
}

/* RECLAIM-EVALUATION-SEQUENCE */
Object reclaim_evaluation_sequence(sequence)
    Object sequence;
{
    Object held_array, temp, svref_arg_2;
    SI_Long ref_count, index_1, ab_loop_bind_, svref_new_value;

    x_note_fn_call(80,136);
    held_array = M_CAR(sequence);
    ref_count = FIXNUM_LE(ISVREF(held_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(held_array,
	    (SI_Long)0L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(held_array,(SI_Long)2L),(SI_Long)0L));
    if (ref_count == (SI_Long)1L) {
	index_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(ISVREF(held_array,(SI_Long)1L));
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(held_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(held_array,index_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_array,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),index_1 & (SI_Long)1023L));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	reclaim_managed_array(held_array);
    }
    else if (ref_count < (SI_Long)1L)
	error((SI_Long)2L,"Sequence reference count zero or below in ~a.",
		sequence);
    else {
	svref_new_value = ref_count - (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(held_array,(SI_Long)1L),
		Maximum_in_place_array_size))
	    ISVREF(held_array,(SI_Long)2L) = FIX(svref_new_value);
	else {
	    temp = ISVREF(held_array,(SI_Long)2L);
	    ISVREF(temp,(SI_Long)0L) = FIX(svref_new_value);
	}
    }
    if (sequence) {
	inline_note_reclaim_cons(sequence,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = sequence;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = sequence;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = sequence;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = sequence;
	}
	M_CDR(sequence) = Nil;
    }
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-SEQUENCE */
Object copy_evaluation_sequence(sequence)
    Object sequence;
{
    Object held_vector, svref_arg_1, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;

    x_note_fn_call(80,137);
    held_vector = M_CAR(sequence);
    gensymed_symbol = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(held_vector,
	    (SI_Long)0L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(held_vector,(SI_Long)2L),(SI_Long)0L));
    gensymed_symbol_1 = (SI_Long)1L;
    svref_new_value = gensymed_symbol + gensymed_symbol_1;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(held_vector,(SI_Long)2L) = FIX(svref_new_value);
    else {
	svref_arg_1 = ISVREF(held_vector,(SI_Long)2L);
	ISVREF(svref_arg_1,(SI_Long)0L) = FIX(svref_new_value);
    }
    temp = eval_cons_1(held_vector,Qsequence);
    return VALUES_1(temp);
}

/* DEEP-COPY-EVALUATION-SEQUENCE */
Object deep_copy_evaluation_sequence(sequence)
    Object sequence;
{
    Object length_1, new_sequence;

    x_note_fn_call(80,138);
    length_1 = FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L));
    new_sequence = allocate_empty_evaluation_sequence(length_1);
    deep_copy_evaluation_sequence_elements(sequence,FIX((SI_Long)0L),
	    length_1,new_sequence,FIX((SI_Long)0L));
    return VALUES_1(new_sequence);
}

/* G2-GET-POSITION-OF-ELEMENT-IN-SEQUENCE */
Object g2_get_position_of_element_in_sequence(element,sequence)
    Object element, sequence;
{
    Object gensymed_symbol, held_vector, item_or_value, index_1;
    Object ab_loop_iter_flag_, elt_1, validated_elt, index_to_return_qm;
    SI_Long next_index, length_1;

    x_note_fn_call(80,139);
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    item_or_value = Nil;
    index_1 = FIX((SI_Long)0L);
    ab_loop_iter_flag_ = T;
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
    item_or_value = validated_elt;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = FIXNUM_ADD1(index_1);
    if (item_or_value_eql_p(item_or_value,element)) {
	index_to_return_qm = index_1;
	goto end_1;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    index_to_return_qm = Qnil;
  end_1:;
    reclaim_if_evaluation_value_function(element);
    reclaim_evaluation_sequence(sequence);
    if (index_to_return_qm)
	return VALUES_1(index_to_return_qm);
    else
	return VALUES_1(FIX((SI_Long)-1L));
}

/* EVALUATION-SEQUENCE-AREF */
Object evaluation_sequence_aref(evaluation_sequence,element_init)
    Object evaluation_sequence, element_init;
{
    Object gensymed_symbol, value, temp;
    SI_Long element, length_1, gensymed_symbol_1;

    x_note_fn_call(80,140);
    element = IFIX(element_init);
    length_1 = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_sequence),
	    (SI_Long)1L)));
    if (element >= (SI_Long)0L && element < length_1) {
	gensymed_symbol = M_CAR(evaluation_sequence);
	gensymed_symbol_1 = element + (SI_Long)1L;
	value = FIXNUM_LE(ISVREF(M_CAR(evaluation_sequence),(SI_Long)1L),
		Maximum_in_place_array_size) ? 
		ISVREF(M_CAR(evaluation_sequence),gensymed_symbol_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	temp = value ? validate_item_or_evaluation_value(value,Nil,Nil) : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* ALLOCATE-EMPTY-EVALUATION-SEQUENCE */
Object allocate_empty_evaluation_sequence(length_1)
    Object length_1;
{
    Object new_vector, svref_arg_1, temp;

    x_note_fn_call(80,141);
    new_vector = allocate_managed_array(1,FIXNUM_ADD1(length_1));
    if (FIXNUM_LE(ISVREF(new_vector,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(new_vector,(SI_Long)2L) = FIX((SI_Long)1L);
    else {
	svref_arg_1 = ISVREF(new_vector,(SI_Long)2L);
	ISVREF(svref_arg_1,(SI_Long)0L) = FIX((SI_Long)1L);
    }
    temp = eval_cons_1(new_vector,Qsequence);
    return VALUES_1(temp);
}

/* COPY-EVALUATION-SEQUENCE-ELEMENTS */
Object copy_evaluation_sequence_elements(source_sequence,source_start_init,
	    source_count_init,destination_sequence,destination_start_init)
    Object source_sequence, source_start_init, source_count_init;
    Object destination_sequence, destination_start_init;
{
    Object source_array, dest_array, ab_loop_iter_flag_, thing, temp;
    Object svref_new_value;
    SI_Long source_start, source_count, destination_start, source_index;
    SI_Long ab_loop_bind_, dest_index, svref_arg_2;

    x_note_fn_call(80,142);
    source_start = IFIX(source_start_init);
    source_count = IFIX(source_count_init);
    destination_start = IFIX(destination_start_init);
    source_array = M_CAR(source_sequence);
    dest_array = M_CAR(destination_sequence);
    source_index = source_start + (SI_Long)1L;
    ab_loop_bind_ = source_start + (SI_Long)1L + source_count;
    dest_index = destination_start + (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (source_index >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	dest_index = dest_index + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(dest_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = dest_index + IFIX(Managed_array_index_offset);
	thing = FIXNUM_LE(ISVREF(source_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(source_array,
		source_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(source_array,(source_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),source_index & (SI_Long)1023L);
	temp = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
	ISVREF(dest_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(dest_array,(dest_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = dest_index & (SI_Long)1023L;
	thing = FIXNUM_LE(ISVREF(source_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(source_array,
		source_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(source_array,(source_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),source_index & (SI_Long)1023L);
	svref_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    ab_loop_iter_flag_ = Nil;
    source_index = source_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* DEEP-COPY-EVALUATION-SEQUENCE-ELEMENTS */
Object deep_copy_evaluation_sequence_elements(source_sequence,
	    source_start_init,source_count_init,destination_sequence,
	    destination_start_init)
    Object source_sequence, source_start_init, source_count_init;
    Object destination_sequence, destination_start_init;
{
    Object source_array, dest_array, ab_loop_iter_flag_, thing, temp;
    Object svref_new_value;
    SI_Long source_start, source_count, destination_start, source_index;
    SI_Long ab_loop_bind_, dest_index, svref_arg_2;

    x_note_fn_call(80,143);
    source_start = IFIX(source_start_init);
    source_count = IFIX(source_count_init);
    destination_start = IFIX(destination_start_init);
    source_array = M_CAR(source_sequence);
    dest_array = M_CAR(destination_sequence);
    source_index = source_start + (SI_Long)1L;
    ab_loop_bind_ = source_start + (SI_Long)1L + source_count;
    dest_index = destination_start + (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (source_index >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	dest_index = dest_index + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(dest_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = dest_index + IFIX(Managed_array_index_offset);
	thing = FIXNUM_LE(ISVREF(source_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(source_array,
		source_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(source_array,(source_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),source_index & (SI_Long)1023L);
	temp = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		deep_copy_if_evaluation_value_1(thing);
	ISVREF(dest_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(dest_array,(dest_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = dest_index & (SI_Long)1023L;
	thing = FIXNUM_LE(ISVREF(source_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(source_array,
		source_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(source_array,(source_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),source_index & (SI_Long)1023L);
	svref_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		deep_copy_if_evaluation_value_1(thing);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    ab_loop_iter_flag_ = Nil;
    source_index = source_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* EVALUATION-SEQUENCE-INSERT-AT-BEGINNING */
Object evaluation_sequence_insert_at_beginning(sequence,new_element)
    Object sequence, new_element;
{
    Object managed_array, temp, svref_new_value, item_or_value, x2, temp_2;
    Object length_2, new_sequence, gensymed_symbol_1;
    SI_Long length_1, index_1, ab_loop_bind_, svref_arg_2, gensymed_symbol;
    char temp_1;

    x_note_fn_call(80,144);
    if ((FIXNUM_LE(ISVREF(M_CAR(sequence),(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(M_CAR(sequence),
	    (SI_Long)0L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(M_CAR(sequence),(SI_Long)2L),(SI_Long)0L))) 
	    == (SI_Long)1L) {
	managed_array = M_CAR(sequence);
	length_1 = IFIX(ISVREF(managed_array,(SI_Long)1L));
	managed_array = adjust_managed_array(4,managed_array,FIX(length_1 
		+ (SI_Long)1L),Nil,T);
	index_1 = length_1;
	ab_loop_bind_ = (SI_Long)1L;
      next_loop:
	if (index_1 <= ab_loop_bind_)
	    goto end_loop;
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    gensymed_symbol = index_1 - (SI_Long)1L;
	    temp = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(managed_array,
		    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(managed_array,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L);
	    ISVREF(managed_array,svref_arg_2) = temp;
	}
	else {
	    temp = ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    gensymed_symbol = index_1 - (SI_Long)1L;
	    svref_new_value = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(managed_array,
		    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(managed_array,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L);
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	index_1 = index_1 - (SI_Long)1L;
	goto next_loop;
      end_loop:;
	gensymed_symbol = (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	    item_or_value = new_element;
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    ISVREF(managed_array,svref_arg_2) = temp;
	}
	else {
	    temp = ISVREF(managed_array,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	    item_or_value = new_element;
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	M_CAR(sequence) = managed_array;
	temp_2 = sequence;
    }
    else {
	length_2 = FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L));
	new_sequence = 
		allocate_empty_evaluation_sequence(FIXNUM_ADD1(length_2));
	copy_evaluation_sequence_elements(sequence,FIX((SI_Long)0L),
		length_2,new_sequence,FIX((SI_Long)1L));
	gensymed_symbol_1 = M_CAR(new_sequence);
	gensymed_symbol = (SI_Long)0L + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = M_CAR(new_sequence);
	    svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	    item_or_value = new_element;
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	else {
	    temp = ISVREF(gensymed_symbol_1,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	    item_or_value = new_element;
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	reclaim_evaluation_sequence(sequence);
	temp_2 = new_sequence;
    }
    return VALUES_1(temp_2);
}

/* EVALUATION-SEQUENCE-INSERT-AT-END */
Object evaluation_sequence_insert_at_end(sequence,new_element)
    Object sequence, new_element;
{
    Object managed_array, item_or_value, x2, temp_1, temp_2, temp_3, length_2;
    Object new_sequence, gensymed_symbol, gensymed_symbol_1, svref_new_value;
    SI_Long length_1, svref_arg_2;
    char temp;

    x_note_fn_call(80,145);
    if ((FIXNUM_LE(ISVREF(M_CAR(sequence),(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(M_CAR(sequence),
	    (SI_Long)0L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(M_CAR(sequence),(SI_Long)2L),(SI_Long)0L))) 
	    == (SI_Long)1L) {
	managed_array = M_CAR(sequence);
	length_1 = IFIX(ISVREF(managed_array,(SI_Long)1L));
	managed_array = adjust_managed_array(4,managed_array,FIX(length_1 
		+ (SI_Long)1L),Nil,T);
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = length_1 + IFIX(Managed_array_index_offset);
	    item_or_value = new_element;
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
	    temp_1 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    ISVREF(managed_array,svref_arg_2) = temp_1;
	}
	else {
	    temp_1 = ISVREF(managed_array,(length_1 >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    svref_arg_2 = length_1 & (SI_Long)1023L;
	    item_or_value = new_element;
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
	    temp_2 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    ISVREF(temp_1,svref_arg_2) = temp_2;
	}
	M_CAR(sequence) = managed_array;
	temp_3 = sequence;
    }
    else {
	length_2 = FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L));
	new_sequence = 
		allocate_empty_evaluation_sequence(FIXNUM_ADD1(length_2));
	copy_evaluation_sequence_elements(sequence,FIX((SI_Long)0L),
		length_2,new_sequence,FIX((SI_Long)0L));
	gensymed_symbol = M_CAR(new_sequence);
	gensymed_symbol_1 = FIXNUM_ADD1(length_2);
	if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = M_CAR(new_sequence);
	    temp_2 = FIXNUM_ADD(gensymed_symbol_1,Managed_array_index_offset);
	    item_or_value = new_element;
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
	    svref_new_value = temp ? get_reference_to_item(item_or_value) :
		     item_or_value;
	    SVREF(temp_1,temp_2) = svref_new_value;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) >>  - 
		     - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(gensymed_symbol_1) & (SI_Long)1023L;
	    item_or_value = new_element;
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
	    temp_2 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    ISVREF(temp_1,svref_arg_2) = temp_2;
	}
	reclaim_evaluation_sequence(sequence);
	temp_3 = new_sequence;
    }
    return VALUES_1(temp_3);
}

/* EVALUATION-SEQUENCE-REMOVE-ELEMENT-AT-INDEX */
Object evaluation_sequence_remove_element_at_index(sequence,index_to_remove)
    Object sequence, index_to_remove;
{
    Object gensymed_symbol, held_vector, element, new_elts, ab_loopvar_;
    Object ab_loopvar__1, elt_1, validated_elt, temp;
    SI_Long remove_1, index_1, next_index, length_1;

    x_note_fn_call(80,146);
    remove_1 = IFIX(index_to_remove);
    index_1 = (SI_Long)0L;
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    new_elts = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
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
    element = validated_elt;
    if ( !(index_1 == remove_1)) {
	ab_loopvar__1 = eval_cons_1(FIXNUMP(element) || element && 
		SYMBOLP(element) || SIMPLE_VECTOR_P(element) ? element : 
		copy_if_evaluation_value_1(element),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    new_elts = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if ( !((SI_Long)-1L < remove_1 && remove_1 < index_1)) {
	reclaim_eval_list_of_item_or_datum(new_elts);
	temp = Nil;
	goto end_1;
    }
    else {
	reclaim_evaluation_sequence(sequence);
	temp = allocate_evaluation_sequence(new_elts);
	goto end_1;
    }
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SEARCH-FOR-SEQUENCE-ELEMENT-FROM-BACK */
Object search_for_sequence_element_from_back(evaluation_sequence,
	    type_spec_qm,nth_1)
    Object evaluation_sequence, type_spec_qm, nth_1;
{
    Object held_vector, value, item_or_value, temp;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(80,147);
    held_vector = M_CAR(evaluation_sequence);
    index_1 = IFIX(FIXNUM_SUB1(ISVREF(held_vector,(SI_Long)1L)));
    ab_loop_bind_ = (SI_Long)1L;
    value = Nil;
  next_loop:
    if (index_1 < ab_loop_bind_)
	goto end_loop;
    item_or_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L);
    value = CONSP(item_or_value) && EQ(M_CDR(item_or_value),
	    Qitem_reference) ? ISVREF(M_CAR(item_or_value),(SI_Long)3L) : 
	    item_or_value;
    if (value && ( !TRUEP(type_spec_qm) || type_specification_type_p(value,
	    type_spec_qm))) {
	if (IFIX(nth_1) == (SI_Long)0L) {
	    temp = value;
	    goto end_1;
	}
	else
	    nth_1 = FIXNUM_SUB1(nth_1);
    }
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* NREVERSE-EVALUATION-SEQUENCE */
Object nreverse_evaluation_sequence(evaluation_sequence)
    Object evaluation_sequence;
{
    Object managed_array, sequence_length, midpoint, bottom_index, top_index;
    Object bottom_element, temp_1, svref_new_value, temp_2;
    SI_Long temp, svref_arg_2;

    x_note_fn_call(80,148);
    managed_array = M_CAR(evaluation_sequence);
    sequence_length = FIXNUM_SUB1(ISVREF(managed_array,(SI_Long)1L));
    temp = IFIX(sequence_length) / (SI_Long)2L;
    midpoint = FIXNUM_ADD1(FIX(temp));
    bottom_index = FIXNUM_SUB1(midpoint);
    top_index = ((SI_Long)1L & IFIX(sequence_length)) == (SI_Long)1L ? 
	    FIXNUM_ADD1(midpoint) : midpoint;
    bottom_element = Nil;
  next_loop:
    if ( !(IFIX(bottom_index) >= (SI_Long)1L))
	goto end_loop;
    bottom_element = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array,
	    IFIX(FIXNUM_ADD(bottom_index,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_array,(IFIX(bottom_index) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(bottom_index) & (SI_Long)1023L);
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp_1 = FIXNUM_ADD(bottom_index,Managed_array_index_offset);
	svref_new_value = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		IFIX(FIXNUM_ADD(top_index,Managed_array_index_offset))) : 
		ISVREF(ISVREF(managed_array,(IFIX(top_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(top_index) & (SI_Long)1023L);
	SVREF(managed_array,temp_1) = svref_new_value;
    }
    else {
	temp_1 = ISVREF(managed_array,(IFIX(bottom_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(bottom_index) & (SI_Long)1023L;
	svref_new_value = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		IFIX(FIXNUM_ADD(top_index,Managed_array_index_offset))) : 
		ISVREF(ISVREF(managed_array,(IFIX(top_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(top_index) & (SI_Long)1023L);
	ISVREF(temp_1,svref_arg_2) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp_1 = FIXNUM_ADD(top_index,Managed_array_index_offset);
	SVREF(managed_array,temp_1) = bottom_element;
    }
    else {
	temp_1 = ISVREF(managed_array,(IFIX(top_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(top_index) & (SI_Long)1023L;
	ISVREF(temp_1,svref_arg_2) = bottom_element;
    }
    top_index = FIXNUM_ADD1(top_index);
    bottom_index = FIXNUM_SUB1(bottom_index);
    goto next_loop;
  end_loop:
    temp_2 = evaluation_sequence;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    return VALUES_1(temp_2);
}

/* EVALUATION-SEQUENCE-EQL */
Object evaluation_sequence_eql(sequence_1,sequence_2)
    Object sequence_1, sequence_2;
{
    Object temp, es1, es2, length1, length2, gensymed_symbol, held_vector;
    Object value1, gensymed_symbol_1, held_vector_1, value2, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1, next_index_1, length_2;

    x_note_fn_call(80,149);
    temp = EQ(sequence_1,sequence_2) ? T : Nil;
    if (temp);
    else {
	es1 = sequence_1;
	es2 = sequence_2;
	length1 = FIXNUM_SUB1(ISVREF(M_CAR(es1),(SI_Long)1L));
	length2 = FIXNUM_SUB1(ISVREF(M_CAR(es2),(SI_Long)1L));
	if (FIXNUM_EQ(length1,length2)) {
	    gensymed_symbol = es1;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    value1 = Nil;
	    gensymed_symbol_1 = es2;
	    held_vector_1 = Nil;
	    next_index_1 = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    value2 = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    held_vector_1 = M_CAR(gensymed_symbol_1);
	    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
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
	    value1 = validated_elt;
	    if (next_index_1 >= length_2)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    next_index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_1 & 
		    (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index_1 = next_index_1 + (SI_Long)1L;
	    value2 = validated_elt;
	    if ( !TRUEP(item_or_value_eql(value1,value2))) {
		temp = Nil;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = T;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* EVALUATION-SEQUENCE-= */
Object evaluation_sequence_eq(sequence_1,sequence_2)
    Object sequence_1, sequence_2;
{
    Object temp, es1, es2, length1, length2, gensymed_symbol, held_vector;
    Object value1, gensymed_symbol_1, held_vector_1, value2, elt_1;
    Object validated_elt, x2;
    SI_Long next_index, length_1, next_index_1, length_2;
    char temp_1;

    x_note_fn_call(80,150);
    temp = EQ(sequence_1,sequence_2) ? T : Nil;
    if (temp);
    else {
	es1 = sequence_1;
	es2 = sequence_2;
	length1 = FIXNUM_SUB1(ISVREF(M_CAR(es1),(SI_Long)1L));
	length2 = FIXNUM_SUB1(ISVREF(M_CAR(es2),(SI_Long)1L));
	if (FIXNUM_EQ(length1,length2)) {
	    gensymed_symbol = es1;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    value1 = Nil;
	    gensymed_symbol_1 = es2;
	    held_vector_1 = Nil;
	    next_index_1 = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    value2 = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    held_vector_1 = M_CAR(gensymed_symbol_1);
	    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
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
	    value1 = validated_elt;
	    if (next_index_1 >= length_2)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    next_index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_1 & 
		    (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index_1 = next_index_1 + (SI_Long)1L;
	    value2 = validated_elt;
	    if (SIMPLE_VECTOR_P(value1) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value1)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value1,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(value1,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else if (SIMPLE_VECTOR_P(value2) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value2)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value2,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(value2,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !(temp_1 ? EQ(value1,value2) : 
		    TRUEP(evaluation_value_eq(value1,value2)))) {
		temp = Nil;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = T;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Evaluation_value_indentation_depth, Qevaluation_value_indentation_depth);

DEFINE_VARIABLE_WITH_SYMBOL(Evaluation_value_writing_target_length_qm, Qevaluation_value_writing_target_length_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Indent_sequences_and_structures_p, Qindent_sequences_and_structures_p);

DEFINE_VARIABLE_WITH_SYMBOL(Leave_text_representation_as_a_single_line_qm, Qleave_text_representation_as_a_single_line_qm);

static Object string_constant_7;   /* "sequence (" */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object string_constant_8;   /* ",~%" */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* WRITE-EVALUATION-SEQUENCE */
Object write_evaluation_sequence(sequence)
    Object sequence;
{
    Object evaluation_value_indentation_depth, first_1, gensymed_symbol;
    Object held_vector, elt_1, elt_2, validated_elt, temp;
    SI_Long next_index, length_1, ab_loop_repeat_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(80,151);
    tformat(1,string_constant_7);
    evaluation_value_indentation_depth = 
	    FIXNUM_ADD1(Evaluation_value_indentation_depth);
    PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_indentation_depth,Qevaluation_value_indentation_depth,evaluation_value_indentation_depth,
	    0);
      first_1 = T;
      gensymed_symbol = sequence;
      held_vector = Nil;
      next_index = (SI_Long)1L;
      length_1 = (SI_Long)0L;
      elt_1 = Nil;
      held_vector = M_CAR(gensymed_symbol);
      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    next_loop:
      if (next_index >= length_1)
	  goto end_loop;
      elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(held_vector,next_index 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(held_vector,(next_index >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),next_index & (SI_Long)1023L);
      validated_elt = elt_2 ? validate_item_or_evaluation_value(elt_2,Nil,
	      Nil) : Nil;
      next_index = next_index + (SI_Long)1L;
      elt_1 = validated_elt;
      if (Evaluation_value_writing_target_length_qm) {
	  temp = twriting_accumulated_length();
	  temp_1 = FIXNUM_GT(temp,Evaluation_value_writing_target_length_qm);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  if ( !TRUEP(first_1))
	      twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
	  twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)3L));
	  goto end_loop;
      }
      else {
	  if ( !TRUEP(first_1)) {
	      Leave_text_representation_as_a_single_line_qm = Nil;
	      if (Indent_sequences_and_structures_p) {
		  tformat(1,string_constant_8);
		  ab_loop_repeat_ = IFIX(Evaluation_value_indentation_depth);
		next_loop_1:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_1;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  twrite_beginning_of_wide_string(array_constant_2,
			  FIX((SI_Long)2L));
		  goto next_loop_1;
		end_loop_1:;
	      }
	  }
	  if (SYMBOLP(elt_1) && elt_1)
	      twrite_beginning_of_wide_string(array_constant_3,
		      FIX((SI_Long)11L));
	  write_block_or_evaluation_value(1,elt_1);
      }
      first_1 = Nil;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    twrite_character(FIX((SI_Long)41L));
    return VALUES_1(Nil);
}

/* FAST-SEQUENCE-TYPE-SPECIFICATION-P */
Object fast_sequence_type_specification_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(80,152);
    temp = CONSP(thing) ? (EQ(M_CAR(thing),Qsequence) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* SEQUENCE-TYPE-SPECIFICATION-P */
Object sequence_type_specification_p(thing)
    Object thing;
{
    Object temp, low_bound_qm, high_bound_qm;

    x_note_fn_call(80,153);
    if (CONSP(thing) && EQ(M_CAR(thing),Qsequence)) {
	temp =  !TRUEP(M_CDR(thing)) ? T : Nil;
	if (temp);
	else if (valid_type_specification_p(CADR(thing))) {
	    low_bound_qm = CADDR(thing);
	    high_bound_qm = CADDDR(thing);
	    temp =  !TRUEP(low_bound_qm) ? T : Nil;
	    if (temp);
	    else if (FIXNUMP(low_bound_qm) && IFIX(low_bound_qm) >= 
		    (SI_Long)0L) {
		temp =  !TRUEP(high_bound_qm) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUMP(high_bound_qm) ? 
			    (FIXNUM_GE(high_bound_qm,low_bound_qm) ? T : 
			    Nil) : Qnil;
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

static Object list_constant;       /* # */

/* SEQUENCE-TYPE-SPECIFICATION-SUBTYPE-IN-KB-P */
Object sequence_type_specification_subtype_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object superior_low_bound_qm, superior_high_bound_qm, low_bound_qm, temp_1;
    Object high_bound_qm;
    char temp;

    x_note_fn_call(80,154);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p || superior_type_has_details_p) {
	if ( !TRUEP(type_has_details_p))
	    type = list_constant;
	if ( !TRUEP(superior_type_has_details_p))
	    superior_type = list_constant;
	if (type_specification_subtype_in_kb_p(CADR(type),
		    CADR(superior_type))) {
	    superior_low_bound_qm = CADDR(superior_type);
	    superior_high_bound_qm = CADDDR(superior_type);
	    temp =  !TRUEP(superior_low_bound_qm);
	    if (temp);
	    else {
		low_bound_qm = CADDR(type);
		temp =  !TRUEP(low_bound_qm) ? IFIX(superior_low_bound_qm) 
			== (SI_Long)0L : FIXNUM_GE(low_bound_qm,
			superior_low_bound_qm);
	    }
	    if (temp) {
		temp_1 =  !TRUEP(superior_high_bound_qm) ? T : Nil;
		if (temp_1);
		else {
		    high_bound_qm = CADDDR(type);
		    temp_1 =  !TRUEP(high_bound_qm) ? 
			    (FIXNUM_EQ(superior_high_bound_qm,
			    Most_positive_fixnum) ? T : Nil) : 
			    FIXNUM_LE(high_bound_qm,
			    superior_high_bound_qm) ? T : Nil;
		}
	    }
	    else
		temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = T;
    return VALUES_1(temp_1);
}

/* SEQUENCE-TYPE-SPECIFICATIONS-COULD-INTERSECT-IN-KB-P */
Object sequence_type_specifications_could_intersect_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p, superior_low_bound;
    Object superior_high_bound, low_bound, high_bound, temp;

    x_note_fn_call(80,155);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p || superior_type_has_details_p) {
	if ( !TRUEP(type_has_details_p))
	    type = list_constant;
	if ( !TRUEP(superior_type_has_details_p))
	    superior_type = list_constant;
	if (type_specifications_could_intersect_in_kb_p(CADR(type),
		CADR(superior_type))) {
	    superior_low_bound = CADDR(superior_type);
	    if (superior_low_bound);
	    else
		superior_low_bound = FIX((SI_Long)0L);
	    superior_high_bound = CADDDR(superior_type);
	    if (superior_high_bound);
	    else
		superior_high_bound = Most_positive_fixnum;
	    low_bound = CADDR(type);
	    if (low_bound);
	    else
		low_bound = FIX((SI_Long)0L);
	    high_bound = CADDDR(type);
	    if (high_bound);
	    else
		high_bound = Most_positive_fixnum;
	    temp = FIXNUM_LE(superior_low_bound,high_bound) ? 
		    (FIXNUM_LE(high_bound,superior_high_bound) ? T : Nil) :
		     Qnil;
	    if (temp);
	    else
		temp = FIXNUM_LE(superior_low_bound,low_bound) ? 
			(FIXNUM_LE(low_bound,superior_high_bound) ? T : 
			Nil) : Qnil;
	}
	else
	    temp = Nil;
    }
    else
	temp = T;
    return VALUES_1(temp);
}

/* SEQUENCE-TYPE-SPECIFICATION-NOT-SUBTYPE-IN-KB-P */
Object sequence_type_specification_not_subtype_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p, temp;
    Object superior_low_bound, superior_high_bound, low_bound, high_bound;

    x_note_fn_call(80,156);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p || superior_type_has_details_p) {
	if ( !TRUEP(type_has_details_p))
	    type = list_constant;
	if ( !TRUEP(superior_type_has_details_p))
	    superior_type = list_constant;
	temp = type_specification_not_subtype_in_kb_p(CADR(type),
		CADR(superior_type));
	if (temp);
	else {
	    superior_low_bound = CADDR(superior_type);
	    if (superior_low_bound);
	    else
		superior_low_bound = FIX((SI_Long)0L);
	    superior_high_bound = CADDDR(superior_type);
	    if (superior_high_bound);
	    else
		superior_high_bound = Most_positive_fixnum;
	    low_bound = CADDR(type);
	    if (low_bound);
	    else
		low_bound = FIX((SI_Long)0L);
	    high_bound = CADDDR(type);
	    if (high_bound);
	    else
		high_bound = Most_positive_fixnum;
	    temp =  !(FIXNUM_LE(superior_low_bound,low_bound) && 
		    FIXNUM_LE(low_bound,high_bound) && 
		    FIXNUM_LE(high_bound,superior_high_bound)) ? T : Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DETAILED-EVALUATION-SEQUENCE-TYPE-P */
Object detailed_evaluation_sequence_type_p(sequence,type_specification)
    Object sequence, type_specification;
{
    Object element_type_specification, low_bound_qm, high_bound_qm, length_qm;
    Object gensymed_symbol, held_vector, element, elt_1, validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(80,157);
    element_type_specification = CADR(type_specification);
    low_bound_qm = CADDR(type_specification);
    high_bound_qm = low_bound_qm ? CADDDR(type_specification) : Qnil;
    length_qm = low_bound_qm ? FIXNUM_SUB1(ISVREF(M_CAR(sequence),
	    (SI_Long)1L)) : Qnil;
    if (( !TRUEP(low_bound_qm) || FIXNUM_LE(low_bound_qm,length_qm)) && ( 
	    !TRUEP(high_bound_qm) || FIXNUM_LT(length_qm,high_bound_qm))) {
	gensymed_symbol = sequence;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
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
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	if ( !TRUEP(type_specification_type_p(element,
		element_type_specification))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qab_structure;       /* structure */

/* ALLOCATE-EVALUATION-STRUCTURE */
Object allocate_evaluation_structure(eval_cons_property_list)
    Object eval_cons_property_list;
{
    Object held_vector, temp, key, value, ab_loop_list_, temp_1, item_or_value;
    Object x2, svref_new_value;
    SI_Long gensymed_symbol, svref_arg_2, index_1;
    char temp_2;

    x_note_fn_call(80,158);
    held_vector = allocate_managed_array(1,
	    FIXNUM_ADD1(length(eval_cons_property_list)));
    gensymed_symbol = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	ISVREF(held_vector,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    index_1 = (SI_Long)1L;
    key = Nil;
    value = Nil;
    ab_loop_list_ = eval_cons_property_list;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    key = CAR(ab_loop_list_);
    temp_1 = CDR(ab_loop_list_);
    value = CAR(temp_1);
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	ISVREF(held_vector,svref_arg_2) = key;
    }
    else {
	temp = ISVREF(held_vector,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = key;
    }
    gensymed_symbol = index_1 + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	item_or_value = value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	item_or_value = value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    index_1 = index_1 + (SI_Long)2L;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    reclaim_eval_list_1(eval_cons_property_list);
    temp_1 = eval_cons_1(held_vector,Qab_structure);
    return VALUES_1(temp_1);
}

/* ALLOCATE-EVALUATION-STRUCTURE-FROM-VECTOR */
Object allocate_evaluation_structure_from_vector(simple_vector,
	    first_key_index,key_count_times_two)
    Object simple_vector, first_key_index, key_count_times_two;
{
    Object held_vector, temp, ab_loop_iter_flag_, svref_new_value;
    Object item_or_value, x2, temp_2;
    SI_Long gensymed_symbol, svref_arg_2, source_index, n_1, ab_loop_bind_;
    SI_Long dest_index;
    char temp_1;

    x_note_fn_call(80,159);
    held_vector = allocate_managed_array(1,FIXNUM_ADD1(key_count_times_two));
    gensymed_symbol = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	ISVREF(held_vector,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    source_index = IFIX(first_key_index);
    n_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(key_count_times_two);
    dest_index = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (n_1 >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	dest_index = dest_index + (SI_Long)2L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = dest_index + IFIX(Managed_array_index_offset);
	temp = ISVREF(simple_vector,source_index);
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(dest_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = dest_index & (SI_Long)1023L;
	svref_new_value = ISVREF(simple_vector,source_index);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    gensymed_symbol = dest_index + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	item_or_value = ISVREF(simple_vector,source_index + (SI_Long)1L);
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	item_or_value = ISVREF(simple_vector,source_index + (SI_Long)1L);
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    ab_loop_iter_flag_ = Nil;
    source_index = source_index + (SI_Long)2L;
    n_1 = n_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:;
    temp_2 = eval_cons_1(held_vector,Qab_structure);
    return VALUES_1(temp_2);
}

/* MAKE-UNIQUE-EVALUATION-STRUCTURE-COPY-1 */
Object make_unique_evaluation_structure_copy_1(old_held_vector)
    Object old_held_vector;
{
    Object vector_length, held_vector, old_attribute_value, temp;
    Object svref_new_value, temp_1;
    SI_Long i, ab_loop_bind_, gensymed_symbol, svref_arg_2;

    x_note_fn_call(80,160);
    vector_length = ISVREF(old_held_vector,(SI_Long)1L);
    held_vector = allocate_managed_array(1,vector_length);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(vector_length);
    old_attribute_value = Nil;
    gensymed_symbol = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	ISVREF(held_vector,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = i + (SI_Long)1L;
    old_attribute_value = FIXNUM_LE(ISVREF(old_held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(old_held_vector,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(old_held_vector,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	temp = FIXNUM_LE(ISVREF(old_held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(old_held_vector,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(old_held_vector,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	svref_new_value = FIXNUM_LE(ISVREF(old_held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(old_held_vector,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(old_held_vector,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    gensymed_symbol = i + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	temp = FIXNUMP(old_attribute_value) || old_attribute_value && 
		SYMBOLP(old_attribute_value) || 
		SIMPLE_VECTOR_P(old_attribute_value) ? old_attribute_value 
		: copy_if_evaluation_value_1(old_attribute_value);
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	svref_new_value = FIXNUMP(old_attribute_value) || 
		old_attribute_value && SYMBOLP(old_attribute_value) || 
		SIMPLE_VECTOR_P(old_attribute_value) ? old_attribute_value 
		: copy_if_evaluation_value_1(old_attribute_value);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)2L;
    goto next_loop;
  end_loop:;
    temp_1 = eval_cons_1(held_vector,Qab_structure);
    return VALUES_1(temp_1);
}

/* MAKE-UNIQUE-EVALUATION-STRUCTURE-DEEP-COPY-1 */
Object make_unique_evaluation_structure_deep_copy_1(old_held_vector)
    Object old_held_vector;
{
    Object vector_length, held_vector, old_attribute_value, temp;
    Object svref_new_value, temp_1;
    SI_Long i, ab_loop_bind_, gensymed_symbol, svref_arg_2;

    x_note_fn_call(80,161);
    vector_length = ISVREF(old_held_vector,(SI_Long)1L);
    held_vector = allocate_managed_array(1,vector_length);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(vector_length);
    old_attribute_value = Nil;
    gensymed_symbol = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	ISVREF(held_vector,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = i + (SI_Long)1L;
    old_attribute_value = FIXNUM_LE(ISVREF(old_held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(old_held_vector,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(old_held_vector,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	temp = FIXNUM_LE(ISVREF(old_held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(old_held_vector,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(old_held_vector,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	svref_new_value = FIXNUM_LE(ISVREF(old_held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(old_held_vector,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(old_held_vector,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    gensymed_symbol = i + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	temp = FIXNUMP(old_attribute_value) || old_attribute_value && 
		SYMBOLP(old_attribute_value) || 
		SIMPLE_VECTOR_P(old_attribute_value) ? old_attribute_value 
		: deep_copy_if_evaluation_value_1(old_attribute_value);
	ISVREF(held_vector,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(held_vector,(gensymed_symbol >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	svref_new_value = FIXNUMP(old_attribute_value) || 
		old_attribute_value && SYMBOLP(old_attribute_value) || 
		SIMPLE_VECTOR_P(old_attribute_value) ? old_attribute_value 
		: deep_copy_if_evaluation_value_1(old_attribute_value);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)2L;
    goto next_loop;
  end_loop:;
    temp_1 = eval_cons_1(held_vector,Qab_structure);
    return VALUES_1(temp_1);
}

/* RECLAIM-EVALUATION-STRUCTURE */
Object reclaim_evaluation_structure(structure)
    Object structure;
{
    Object held_vector, ref_count, temp, temp_1;
    SI_Long gensymed_symbol, index_1, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(80,162);
    held_vector = M_CAR(structure);
    gensymed_symbol = (SI_Long)0L;
    ref_count = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (IFIX(ref_count) == (SI_Long)1L) {
	index_1 = (SI_Long)1L + (SI_Long)1L;
	ab_loop_bind_ = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(held_vector,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(held_vector,index_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(index_1 >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L),index_1 & (SI_Long)1023L));
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	reclaim_managed_array(held_vector);
    }
    else {
	gensymed_symbol = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	    temp = FIXNUM_SUB1(ref_count);
	    ISVREF(held_vector,svref_arg_2) = temp;
	}
	else {
	    temp = ISVREF(held_vector,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	    temp_1 = FIXNUM_SUB1(ref_count);
	    ISVREF(temp,svref_arg_2) = temp_1;
	}
    }
    if (structure) {
	inline_note_reclaim_cons(structure,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = structure;
	    temp = Available_eval_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = structure;
	}
	else {
	    temp = Available_eval_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = structure;
	    temp = Available_eval_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = structure;
	}
	M_CDR(structure) = Nil;
    }
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-STRUCTURE */
Object copy_evaluation_structure(structure)
    Object structure;
{
    Object held_vector, svref_arg_1, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;

    x_note_fn_call(80,163);
    held_vector = M_CAR(structure);
    gensymed_symbol = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(held_vector,
	    (SI_Long)0L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(held_vector,(SI_Long)2L),(SI_Long)0L));
    gensymed_symbol_1 = (SI_Long)1L;
    svref_new_value = gensymed_symbol + gensymed_symbol_1;
    if (FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(held_vector,(SI_Long)2L) = FIX(svref_new_value);
    else {
	svref_arg_1 = ISVREF(held_vector,(SI_Long)2L);
	ISVREF(svref_arg_1,(SI_Long)0L) = FIX(svref_new_value);
    }
    temp = eval_cons_1(held_vector,Qab_structure);
    return VALUES_1(temp);
}

/* DEEP-COPY-EVALUATION-STRUCTURE */
Object deep_copy_evaluation_structure(structure)
    Object structure;
{
    Object temp;

    x_note_fn_call(80,164);
    temp = make_unique_evaluation_structure_deep_copy_1(M_CAR(structure));
    return VALUES_1(temp);
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* WRITE-EVALUATION-STRUCTURE */
Object write_evaluation_structure(structure)
    Object structure;
{
    Object evaluation_value_indentation_depth, first_1, gensymed_symbol;
    Object held_vector, name, attribute_value, value, temp;
    SI_Long next_index, length_1, gensymed_symbol_1, ab_loop_repeat_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(80,165);
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)11L));
    evaluation_value_indentation_depth = 
	    FIXNUM_ADD1(Evaluation_value_indentation_depth);
    PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_indentation_depth,Qevaluation_value_indentation_depth,evaluation_value_indentation_depth,
	    0);
      first_1 = T;
      gensymed_symbol = structure;
      held_vector = Nil;
      next_index = (SI_Long)1L;
      length_1 = (SI_Long)0L;
      name = Nil;
      attribute_value = Nil;
      value = Nil;
      held_vector = M_CAR(gensymed_symbol);
      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    next_loop:
      if (next_index >= length_1)
	  goto end_loop;
      name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(held_vector,next_index 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(held_vector,(next_index >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),next_index & (SI_Long)1023L);
      gensymed_symbol_1 = next_index + (SI_Long)1L;
      attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(held_vector,
	      gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
      value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
      next_index = next_index + (SI_Long)2L;
      if (Evaluation_value_writing_target_length_qm) {
	  temp = twriting_accumulated_length();
	  temp_1 = FIXNUM_GT(temp,Evaluation_value_writing_target_length_qm);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  if ( !TRUEP(first_1))
	      twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
	  twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)3L));
	  goto end_loop;
      }
      else {
	  if ( !TRUEP(first_1)) {
	      Leave_text_representation_as_a_single_line_qm = Nil;
	      if (Indent_sequences_and_structures_p) {
		  tformat(1,string_constant_8);
		  ab_loop_repeat_ = IFIX(Evaluation_value_indentation_depth);
		next_loop_1:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_1;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  twrite_beginning_of_wide_string(array_constant_2,
			  FIX((SI_Long)2L));
		  goto next_loop_1;
		end_loop_1:;
	      }
	  }
	  write_evaluation_value(1,name);
	  twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)2L));
	  if (value && SYMBOLP(value))
	      twrite_beginning_of_wide_string(array_constant_3,
		      FIX((SI_Long)11L));
	  write_block_or_evaluation_value(1,value);
      }
      first_1 = Nil;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    twrite_character(FIX((SI_Long)41L));
    return VALUES_1(Nil);
}

/* COMPARE-STRUCTURE-CONTENTS */
Object compare_structure_contents(structure1,structure2,use_eql_qm)
    Object structure1, structure2, use_eql_qm;
{
    Object temp, gensymed_symbol, held_vector, key1, attribute_value, val1;
    Object gensymed_symbol_1, held_vector_1, key2, val2, x2, held_vector_2;
    Object key3, val3;
    SI_Long next_index, length_1, next_index_1, length_2, gensymed_symbol_2;
    SI_Long next_index_2, length_3;
    char temp_1;

    x_note_fn_call(80,166);
    temp = EQ(structure1,structure2) ? T : Nil;
    if (temp);
    else if (FIXNUM_EQ(ISVREF(M_CAR(structure1),(SI_Long)1L),
	    ISVREF(M_CAR(structure2),(SI_Long)1L))) {
	gensymed_symbol = structure1;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	key1 = Nil;
	attribute_value = Nil;
	val1 = Nil;
	gensymed_symbol_1 = structure2;
	held_vector_1 = Nil;
	next_index_1 = (SI_Long)1L;
	length_2 = (SI_Long)0L;
	key2 = Nil;
	attribute_value = Nil;
	val2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	held_vector_1 = M_CAR(gensymed_symbol_1);
	length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	key1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_2 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_2 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		(SI_Long)1023L);
	val1 = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	if (next_index_1 >= length_2)
	    goto end_loop;
	key2 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		next_index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index_1 & (SI_Long)1023L);
	gensymed_symbol_2 = next_index_1 + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		gensymed_symbol_2 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector_1,(gensymed_symbol_2 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		(SI_Long)1023L);
	val2 = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index_1 = next_index_1 + (SI_Long)2L;
	if (EQ(key1,key2)) {
	    if (SIMPLE_VECTOR_P(val1) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(val1)) > (SI_Long)2L && 
		     !EQ(ISVREF(val1,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(val1,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else if (SIMPLE_VECTOR_P(val2) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(val2)) > (SI_Long)2L && 
		     !EQ(ISVREF(val2,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(val2,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? EQ(val1,val2) : use_eql_qm ? 
		    TRUEP(evaluation_value_eql(2,val1,val2)) : 
		    TRUEP(evaluation_value_eq(val1,val2));
	}
	else {
	    gensymed_symbol = structure2;
	    held_vector_2 = Nil;
	    next_index_2 = (SI_Long)1L;
	    length_3 = (SI_Long)0L;
	    key3 = Nil;
	    attribute_value = Nil;
	    val3 = Nil;
	    held_vector_2 = M_CAR(gensymed_symbol);
	    length_3 = IFIX(ISVREF(held_vector_2,(SI_Long)1L));
	  next_loop_1:
	    if (next_index_2 >= length_3)
		goto end_loop_1;
	    key3 = FIXNUM_LE(ISVREF(held_vector_2,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_2,
		    next_index_2 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_2,(next_index_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_2 & 
		    (SI_Long)1023L);
	    gensymed_symbol_2 = next_index_2 + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector_2,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_2,
		    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector_2,(gensymed_symbol_2 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		    (SI_Long)1023L);
	    val3 = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index_2 = next_index_2 + (SI_Long)2L;
	    if (EQ(key1,key3)) {
		if (SIMPLE_VECTOR_P(val1) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(val1)) > 
			(SI_Long)2L &&  !EQ(ISVREF(val1,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(val1,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1);
		else if (SIMPLE_VECTOR_P(val3) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(val3)) > 
			(SI_Long)2L &&  !EQ(ISVREF(val3,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(val3,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_1 = temp_1 ? EQ(val1,val3) : use_eql_qm ? 
			TRUEP(evaluation_value_eql(2,val1,val3)) : 
			TRUEP(evaluation_value_eq(val1,val3));
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	}
	if ( !temp_1) {
	    temp = Nil;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EVALUATION-STRUCTURE-EQL */
Object evaluation_structure_eql(structure_1,structure_2)
    Object structure_1, structure_2;
{
    Object temp;

    x_note_fn_call(80,167);
    temp = compare_structure_contents(structure_1,structure_2,T);
    return VALUES_1(temp);
}

/* EVALUATION-STRUCTURE-= */
Object evaluation_structure_eq(structure_1,structure_2)
    Object structure_1, structure_2;
{
    x_note_fn_call(80,168);
    GENSYM_RETURN_ONE(compare_structure_contents(structure_1,structure_2,Nil));
    return VALUES_1(Nil);
}

/* STRUCTURE-SLOT-1 */
Object structure_slot_1(estructure,name,default_1)
    Object estructure, name, default_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long gensymed_symbol_2, ab_loop_bind_;

    x_note_fn_call(80,169);
    gensymed_symbol = estructure;
    gensymed_symbol_1 = name;
    gensymed_symbol_2 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(ISVREF(gensymed_symbol,(SI_Long)1L));
  next_loop:
    if (gensymed_symbol_2 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(gensymed_symbol,
	    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_2 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
	    (SI_Long)1023L),gensymed_symbol_1)) {
	gensymed_symbol_1 = FIX(gensymed_symbol_2 + (SI_Long)1L);
	goto end_1;
    }
    gensymed_symbol_2 = gensymed_symbol_2 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = Qnil;
  end_1:;
    temp = gensymed_symbol_1 ? 
	    validate_item_or_evaluation_value(FIXNUM_LE(ISVREF(gensymed_symbol,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(gensymed_symbol,IFIX(FIXNUM_ADD(gensymed_symbol_1,
	    Managed_array_index_offset))) : ISVREF(ISVREF(gensymed_symbol,
	    (IFIX(gensymed_symbol_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(gensymed_symbol_1) & (SI_Long)1023L),Nil,Nil) : default_1;
    return VALUES_1(temp);
}

/* ESTRUCTURE-SLOT */
Object estructure_slot(estructure,name,default_1)
    Object estructure, name, default_1;
{
    Object temp;

    x_note_fn_call(80,170);
    temp = structure_slot_1(M_CAR(estructure),name,default_1);
    return VALUES_1(temp);
}

/* SET-EVALUATION-STRUCTURE-SLOT */
Object set_evaluation_structure_slot(estructure,name,new_value)
    Object estructure, name, new_value;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_3;
    Object item_or_value, x2, gensymed_symbol_4, svref_arg_1, temp_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_5, ab_loop_bind_, value_index;
    SI_Long svref_arg_2;
    char temp;

    x_note_fn_call(80,171);
    gensymed_symbol = estructure;
    gensymed_symbol_1 = M_CAR(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)1L));
    gensymed_symbol_3 = name;
    item_or_value = new_value;
    if (SIMPLE_VECTOR_P(item_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    gensymed_symbol_4 = temp ? get_reference_to_item(item_or_value) : 
	    item_or_value;
    gensymed_symbol_5 = (SI_Long)1L;
    ab_loop_bind_ = gensymed_symbol_2;
  next_loop:
    if (gensymed_symbol_5 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_1,
	    gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(gensymed_symbol_1,(gensymed_symbol_5 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
	    (SI_Long)1023L),gensymed_symbol_3)) {
	value_index = gensymed_symbol_5 + (SI_Long)1L;
	reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_1,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(gensymed_symbol_1,value_index + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_1,(value_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),value_index & (SI_Long)1023L));
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_1,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_1,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = value_index & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	temp_1 = gensymed_symbol_4;
	goto end_1;
    }
    gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = adjust_managed_array(2,gensymed_symbol_1,
	    FIX(gensymed_symbol_2 + (SI_Long)2L));
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_2 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol_1,svref_arg_2) = gensymed_symbol_3;
    }
    else {
	svref_arg_1 = ISVREF(gensymed_symbol_1,(gensymed_symbol_2 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
    }
    gensymed_symbol_2 = gensymed_symbol_2 + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_2 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol_1,svref_arg_2) = gensymed_symbol_4;
    }
    else {
	svref_arg_1 = ISVREF(gensymed_symbol_1,(gensymed_symbol_2 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
    }
    temp_1 = gensymed_symbol_4;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* REMOVE-EVALUATION-STRUCTURE-ATTRIBUTE */
Object remove_evaluation_structure_attribute(structure,symbol)
    Object structure, symbol;
{
    Object attribute_found_qm, held_vector, attribute, new_attributes;
    Object ab_loopvar_, ab_loopvar__1, temp_1, value_cons, thing;
    Object car_new_value;
    SI_Long length_1, index_1, ab_loop_bind_, gensymed_symbol;
    char temp;

    x_note_fn_call(80,172);
    attribute_found_qm = Nil;
    held_vector = M_CAR(structure);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = length_1;
    attribute = Nil;
    new_attributes = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    attribute = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L);
    if (EQ(symbol,attribute)) {
	attribute_found_qm = T;
	temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(T);
    if (temp) {
	temp_1 = attribute;
	gensymed_symbol = index_1 + (SI_Long)1L;
	ab_loopvar__1 = eval_list_2(temp_1,FIXNUM_LE(ISVREF(held_vector,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(held_vector,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L));
	if (ab_loopvar__1) {
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		new_attributes = ab_loopvar__1;
	    ab_loopvar_ = last(ab_loopvar__1,_);
	}
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    if (attribute_found_qm) {
	value_cons = CDR(new_attributes);
      next_loop_1:
	if ( !TRUEP(value_cons))
	    goto end_loop_1;
	thing = M_CAR(value_cons);
	car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
	M_CAR(value_cons) = car_new_value;
	value_cons = CDDR(value_cons);
	goto next_loop_1;
      end_loop_1:;
	temp_1 = allocate_evaluation_structure(new_attributes);
	goto end_1;
    }
    else {
	reclaim_eval_list_1(new_attributes);
	temp_1 = Nil;
	goto end_1;
    }
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_number_of_slots_in_structure_type, Qmaximum_number_of_slots_in_structure_type);

/* STRUCTURE-TYPE-SPECIFICATION-P */
Object structure_type_specification_p(thing)
    Object thing;
{
    Object temp, slot_names_and_types, minimum_contents, slot_spec;
    Object ab_loop_list_, ab_loop_iter_flag_;
    SI_Long i;
    char temp_1;

    x_note_fn_call(80,173);
    if (CONSP(thing) && EQ(M_CAR(thing),Qab_structure)) {
	temp =  !TRUEP(M_CDR(thing)) ? T : Nil;
	if (temp);
	else {
	    slot_names_and_types = M_CAR(M_CDR(thing));
	    minimum_contents = CADDR(thing);
	    if (CONSP(slot_names_and_types)) {
		slot_spec = Nil;
		ab_loop_list_ = slot_names_and_types;
		i = (SI_Long)0L;
		ab_loop_iter_flag_ = T;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		slot_spec = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_))
		    i = i + (SI_Long)1L;
		if ( !(i < IFIX(Maximum_number_of_slots_in_structure_type) 
			&& valid_structure_slot_specification_p(slot_spec))) {
		    temp_1 = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(T);
		goto end_1;
		temp_1 = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp =  !TRUEP(minimum_contents) ? T : Nil;
		if (temp);
		else
		    temp = 
			    boolean_composition_over_symbols_p(minimum_contents);
	    }
	    else
		temp = Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* VALID-STRUCTURE-SLOT-SPECIFICATION-P */
Object valid_structure_slot_specification_p(slot_spec)
    Object slot_spec;
{
    Object temp, tail;
    char temp_1;

    x_note_fn_call(80,174);
    if (CONSP(slot_spec)) {
	temp = CAR(slot_spec);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	tail = M_CDR(slot_spec);
	temp = CONSP(tail) &&  !TRUEP(M_CDR(tail)) ? 
		valid_type_specification_p(M_CAR(tail)) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Boolean_composition_over_symbols_allows_top_level_symbols_p, Qboolean_composition_over_symbols_allows_top_level_symbols_p);

static Object list_constant_1;     /* # */

/* BOOLEAN-COMPOSITION-OVER-SYMBOLS-P */
Object boolean_composition_over_symbols_p(exp_1)
    Object exp_1;
{
    Object boolean_composition_over_symbols_allows_top_level_symbols_p;
    Object sub_exp, ab_loop_list_, temp;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(80,175);
    if (CONSP(exp_1)) {
	boolean_composition_over_symbols_allows_top_level_symbols_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Boolean_composition_over_symbols_allows_top_level_symbols_p,Qboolean_composition_over_symbols_allows_top_level_symbols_p,boolean_composition_over_symbols_allows_top_level_symbols_p,
		0);
	  if (memq_function(M_CAR(exp_1),list_constant_1)) {
	      sub_exp = Nil;
	      ab_loop_list_ = M_CDR(exp_1);
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      sub_exp = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(boolean_composition_over_symbols_p(sub_exp))) {
		  temp = Nil;
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp = T;
	      goto end_1;
	      temp = Qnil;
	    end_1:;
	  }
	  else
	      temp = Nil;
	  if (temp);
	  else {
	      if (EQ(M_CAR(exp_1),Qnot)) {
		  temp = M_CDR(exp_1);
		  temp_1 = CONSP(temp);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = (temp_1 ? 
		      TRUEP(boolean_composition_over_symbols_p(M_CAR(M_CDR(exp_1)))) 
		      : TRUEP(Nil)) ? ( !TRUEP(M_CDR(M_CDR(exp_1))) ? T : 
		      Nil) : Nil;
	  }
	POP_SPECIAL();
    }
    else if (exp_1 && SYMBOLP(exp_1))
	temp = Boolean_composition_over_symbols_allows_top_level_symbols_p;
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qab_or;              /* or */

/* SLOT-NAME-LIST-MEETS-MINIMUM-STRUCTURE-REQUIREMENTS-P */
Object slot_name_list_meets_minimum_structure_requirements_p(minimum_contents,
	    slot_names)
    Object minimum_contents, slot_names;
{
    Object temp, sub_exp, ab_loop_list_, ab_loop_it_, gensymed_symbol;

    x_note_fn_call(80,176);
    if (CONSP(minimum_contents)) {
	temp = CAR(minimum_contents);
	if (EQ(temp,Qand)) {
	    sub_exp = Nil;
	    ab_loop_list_ = CDR(minimum_contents);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    sub_exp = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( 
		    !TRUEP(slot_name_list_meets_minimum_structure_requirements_p(sub_exp,
		    slot_names))) {
		temp = Nil;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = T;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else if (EQ(temp,Qab_or)) {
	    sub_exp = Nil;
	    ab_loop_list_ = CDR(minimum_contents);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    sub_exp = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = 
		    slot_name_list_meets_minimum_structure_requirements_p(sub_exp,
		    slot_names);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_2:;
	}
	else if (EQ(temp,Qnot))
	    temp =  
		    !TRUEP(slot_name_list_meets_minimum_structure_requirements_p(CADR(minimum_contents),
		    slot_names)) ? T : Nil;
	else
	    temp = Qnil;
    }
    else if (SYMBOLP(minimum_contents)) {
	gensymed_symbol = slot_names;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	if (EQ(M_CAR(gensymed_symbol),minimum_contents)) {
	    temp = gensymed_symbol;
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_2;
      end_loop_2:
	temp = Qnil;
      end_3:;
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* STRUCTURE-TYPE-SPECIFICATION-SUBTYPE-IN-KB-P */
Object structure_type_specification_subtype_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object minimum_contents_of_superior, slot_list_of_type;
    Object slot_list_of_superior_type, slot_type_cache, ok_p;
    Object type_specification, slot_list, minimum_contents, tuple, slot_name;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, name, cache_entry_qm, temp_1, type_spec_of_slot;
    Object type_spec_of_slot_in_superior_qm, new_cached_type_test;
    SI_Long len, i, ab_loop_bind_, j, ab_loop_bind__1;
    char temp;

    x_note_fn_call(80,177);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (superior_type_has_details_p) {
	if (type_has_details_p) {
	    minimum_contents_of_superior = CADDR(superior_type);
	    slot_list_of_type = M_CAR(M_CDR(type));
	    slot_list_of_superior_type = M_CAR(M_CDR(superior_type));
	    slot_type_cache = Nil;
	    ok_p = T;
	    type_specification = type;
	    slot_list = M_CAR(M_CDR(type_specification));
	    minimum_contents = CADDR(type_specification);
	    len = IFIX(length(slot_list));
	    i = (SI_Long)0L;
	    ab_loop_bind_ = (SI_Long)1L << len;
	    tuple = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    j = (SI_Long)0L;
	    ab_loop_bind__1 = len;
	    slot_name = Nil;
	    ab_loop_list_ = slot_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if (j > ab_loop_bind__1)
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    slot_name = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ((SI_Long)0L != ((SI_Long)1L << j & i)) {
		ab_loopvar__2 = gensym_cons_1(slot_name,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    j = j + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    tuple = ab_loopvar_;
	    goto end_1;
	    tuple = Qnil;
	  end_1:;
	    if ( !TRUEP(minimum_contents) || 
		    slot_name_list_meets_minimum_structure_requirements_p(minimum_contents,
		    tuple)) {
		if ( !TRUEP(minimum_contents_of_superior) || 
			slot_name_list_meets_minimum_structure_requirements_p(minimum_contents_of_superior,
			tuple)) {
		    name = Nil;
		    ab_loop_list_ = tuple;
		    cache_entry_qm = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    name = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    cache_entry_qm = assq_function(name,slot_type_cache);
		    if (cache_entry_qm)
			temp = TRUEP(CDR(cache_entry_qm));
		    else {
			temp_1 = assq_function(name,slot_list_of_type);
			type_spec_of_slot = CADR(temp_1);
			temp_1 = assq_function(name,
				slot_list_of_superior_type);
			type_spec_of_slot_in_superior_qm = CADR(temp_1);
			new_cached_type_test =  
				!TRUEP(type_spec_of_slot_in_superior_qm) ? 
				T : Nil;
			if (new_cached_type_test);
			else
			    new_cached_type_test = 
				    type_specification_subtype_in_kb_p(type_spec_of_slot,
				    type_spec_of_slot_in_superior_qm);
			slot_type_cache = gensym_cons_1(gensym_cons_1(name,
				new_cached_type_test),slot_type_cache);
			temp = TRUEP(new_cached_type_test);
		    }
		    if ( !temp) {
			temp = TRUEP(Nil);
			goto end_2;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp = TRUEP(T);
		    goto end_2;
		    temp = TRUEP(Qnil);
		  end_2:;
		}
		else
		    temp = TRUEP(Nil);
		if ( !temp) {
		    ok_p = Nil;
		    goto end_test_loop;
		}
	    }
	    reclaim_gensym_list_1(tuple);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	  end_test_loop:
	    temp_1 = ok_p;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = T;
    return VALUES_1(temp_1);
}

static Object list_constant_2;     /* # */

/* MAKE-AUGMENTED-STRUCTURE-TYPE-SPECIFICATION */
Object make_augmented_structure_type_specification(structure_type_specification,
	    other_strcture_type_specification)
    Object structure_type_specification, other_strcture_type_specification;
{
    Object new_type_specification, original_slot_list, name, type;
    Object ab_loop_list_, ab_loop_desetq_, temp, gensym_push_modify_macro_arg;
    Object car_1, cdr_1, cadr_new_value;

    x_note_fn_call(80,178);
    new_type_specification = 
	    copy_tree_using_gensym_conses_1(structure_type_specification);
    original_slot_list = M_CAR(M_CDR(structure_type_specification));
    name = Nil;
    type = Nil;
    ab_loop_list_ = M_CAR(M_CDR(other_strcture_type_specification));
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    type = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(assq_function(name,original_slot_list))) {
	gensym_push_modify_macro_arg = gensym_list_2(name,
		copy_tree_using_gensym_conses_1(list_constant_2));
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = CADR(new_type_specification);
	cadr_new_value = gensym_cons_1(car_1,cdr_1);
	M_CADR(new_type_specification) = cadr_new_value;
    }
    goto next_loop;
  end_loop:
    temp = new_type_specification;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* STRUCTURE-TYPE-SPECIFICATIONS-COULD-INTERSECT-IN-KB-P */
Object structure_type_specifications_could_intersect_in_kb_p(type,
	    superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object minimum_contents_of_superior, augmented_type;
    Object augmented_superior_type, slot_list_of_type;
    Object slot_list_of_superior_type, slot_type_cache, ok_p;
    Object type_specification, slot_list, minimum_contents, tuple, slot_name;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, name, cache_entry_qm, temp_1, type_spec_of_slot;
    Object type_spec_of_slot_in_superior, new_cached_type_test;
    SI_Long len, i, ab_loop_bind_, j, ab_loop_bind__1;
    char temp;

    x_note_fn_call(80,179);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p && superior_type_has_details_p) {
	minimum_contents_of_superior = CADDR(superior_type);
	augmented_type = make_augmented_structure_type_specification(type,
		superior_type);
	augmented_superior_type = 
		make_augmented_structure_type_specification(superior_type,
		type);
	slot_list_of_type = M_CAR(M_CDR(augmented_type));
	slot_list_of_superior_type = M_CAR(M_CDR(augmented_superior_type));
	slot_type_cache = Nil;
	ok_p = Nil;
	type_specification = augmented_type;
	slot_list = M_CAR(M_CDR(type_specification));
	minimum_contents = CADDR(type_specification);
	len = IFIX(length(slot_list));
	i = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)1L << len;
	tuple = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	j = (SI_Long)0L;
	ab_loop_bind__1 = len;
	slot_name = Nil;
	ab_loop_list_ = slot_list;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if (j > ab_loop_bind__1)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	slot_name = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ((SI_Long)0L != ((SI_Long)1L << j & i)) {
	    ab_loopvar__2 = gensym_cons_1(slot_name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	j = j + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	tuple = ab_loopvar_;
	goto end_1;
	tuple = Qnil;
      end_1:;
	if ( !TRUEP(minimum_contents) || 
		slot_name_list_meets_minimum_structure_requirements_p(minimum_contents,
		tuple)) {
	    if ( !TRUEP(minimum_contents_of_superior) || 
		    slot_name_list_meets_minimum_structure_requirements_p(minimum_contents_of_superior,
		    tuple)) {
		name = Nil;
		ab_loop_list_ = tuple;
		cache_entry_qm = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		name = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		cache_entry_qm = assq_function(name,slot_type_cache);
		if (cache_entry_qm)
		    temp = TRUEP(CDR(cache_entry_qm));
		else {
		    temp_1 = assq_function(name,slot_list_of_type);
		    type_spec_of_slot = CADR(temp_1);
		    temp_1 = assq_function(name,slot_list_of_superior_type);
		    type_spec_of_slot_in_superior = CADR(temp_1);
		    new_cached_type_test = 
			    type_specifications_could_intersect_in_kb_p(type_spec_of_slot,
			    type_spec_of_slot_in_superior);
		    slot_type_cache = gensym_cons_1(gensym_cons_1(name,
			    new_cached_type_test),slot_type_cache);
		    temp = TRUEP(new_cached_type_test);
		}
		if ( !temp) {
		    temp = TRUEP(Nil);
		    goto end_2;
		}
		goto next_loop_2;
	      end_loop_2:
		temp = TRUEP(T);
		goto end_2;
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		ok_p = T;
		goto end_test_loop;
	    }
	}
	reclaim_gensym_list_1(tuple);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
      end_test_loop:
	reclaim_gensym_tree_1(augmented_type);
	reclaim_gensym_tree_1(augmented_superior_type);
	temp_1 = ok_p;
    }
    else
	temp_1 = T;
    return VALUES_1(temp_1);
}

/* STRUCTURE-TYPE-SPECIFICATION-NOT-SUBTYPE-IN-KB-P */
Object structure_type_specification_not_subtype_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object minimum_contents_of_superior, slot_list_of_type;
    Object slot_list_of_superior_type, slot_type_cache, not_subtype_p;
    Object type_specification, slot_list, minimum_contents, tuple, slot_name;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, name, cache_entry_qm, ab_loop_it_, temp;
    Object type_spec_of_slot, type_spec_of_slot_in_superior_qm;
    Object new_cached_type_test;
    SI_Long len, i, ab_loop_bind_, j, ab_loop_bind__1;
    char temp_1;

    x_note_fn_call(80,180);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p) {
	if (superior_type_has_details_p) {
	    minimum_contents_of_superior = CADDR(superior_type);
	    slot_list_of_type = M_CAR(M_CDR(type));
	    slot_list_of_superior_type = M_CAR(M_CDR(superior_type));
	    slot_type_cache = Nil;
	    not_subtype_p = Nil;
	    type_specification = type;
	    slot_list = M_CAR(M_CDR(type_specification));
	    minimum_contents = CADDR(type_specification);
	    len = IFIX(length(slot_list));
	    i = (SI_Long)0L;
	    ab_loop_bind_ = (SI_Long)1L << len;
	    tuple = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    j = (SI_Long)0L;
	    ab_loop_bind__1 = len;
	    slot_name = Nil;
	    ab_loop_list_ = slot_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if (j > ab_loop_bind__1)
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    slot_name = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ((SI_Long)0L != ((SI_Long)1L << j & i)) {
		ab_loopvar__2 = gensym_cons_1(slot_name,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    j = j + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    tuple = ab_loopvar_;
	    goto end_1;
	    tuple = Qnil;
	  end_1:;
	    if ( !TRUEP(minimum_contents) || 
		    slot_name_list_meets_minimum_structure_requirements_p(minimum_contents,
		    tuple)) {
		if ( !TRUEP(minimum_contents_of_superior) || 
			slot_name_list_meets_minimum_structure_requirements_p(minimum_contents_of_superior,
			tuple)) {
		    name = Nil;
		    ab_loop_list_ = tuple;
		    cache_entry_qm = Nil;
		    ab_loop_it_ = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    name = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    cache_entry_qm = assq_function(name,slot_type_cache);
		    if (cache_entry_qm)
			ab_loop_it_ = CDR(cache_entry_qm);
		    else {
			temp = assq_function(name,slot_list_of_type);
			type_spec_of_slot = CADR(temp);
			temp = assq_function(name,slot_list_of_superior_type);
			type_spec_of_slot_in_superior_qm = CADR(temp);
			new_cached_type_test = 
				type_spec_of_slot_in_superior_qm ? 
				type_specification_not_subtype_in_kb_p(type_spec_of_slot,
				type_spec_of_slot_in_superior_qm) : Qnil;
			slot_type_cache = gensym_cons_1(gensym_cons_1(name,
				new_cached_type_test),slot_type_cache);
			ab_loop_it_ = new_cached_type_test;
		    }
		    if (ab_loop_it_) {
			temp_1 = TRUEP(ab_loop_it_);
			goto end_2;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp_1 = TRUEP(Qnil);
		  end_2:;
		    temp_1 = temp_1 ? TRUEP(T) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(T);
		if (temp_1) {
		    not_subtype_p = T;
		    goto end_test_loop;
		}
	    }
	    reclaim_gensym_list_1(tuple);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	  end_test_loop:
	    temp = not_subtype_p;
	}
	else
	    temp = Nil;
    }
    else if (superior_type_has_details_p)
	temp = T;
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DETAILED-EVALUATION-STRUCTURE-TYPE-P */
Object detailed_evaluation_structure_type_p(structure,type_specification)
    Object structure, type_specification;
{
    Object slot_specifications, minimum_contents, gensymed_symbol, held_vector;
    Object name, attribute_value, value, slot_specification_qm, temp_1;
    SI_Long next_index, length_1, gensymed_symbol_1;
    char temp;

    x_note_fn_call(80,181);
    slot_specifications = M_CAR(M_CDR(type_specification));
    minimum_contents = CADDR(type_specification);
    gensymed_symbol = structure;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    name = Nil;
    attribute_value = Nil;
    value = Nil;
    slot_specification_qm = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    slot_specification_qm = assq_function(name,slot_specifications);
    if ( !(slot_specification_qm && type_specification_type_p(value,
	    CADR(slot_specification_qm)))) {
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
	temp_1 =  !TRUEP(minimum_contents) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = eval_minimum_structure_contents(minimum_contents,
		    structure);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* EVAL-MINIMUM-STRUCTURE-CONTENTS */
Object eval_minimum_structure_contents(boolean_expression,structure)
    Object boolean_expression, structure;
{
    Object temp, conjunct, ab_loop_list_, disjunct, ab_loop_it_;

    x_note_fn_call(80,182);
    if (CONSP(boolean_expression)) {
	temp = M_CAR(boolean_expression);
	if (EQ(temp,Qand)) {
	    conjunct = Nil;
	    ab_loop_list_ = M_CDR(boolean_expression);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    conjunct = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(eval_minimum_structure_contents(conjunct,structure))) {
		temp = Nil;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = T;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else if (EQ(temp,Qab_or)) {
	    disjunct = Nil;
	    ab_loop_list_ = M_CDR(boolean_expression);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    disjunct = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = eval_minimum_structure_contents(disjunct,structure);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_2:;
	}
	else if (EQ(temp,Qnot))
	    temp =  
		    !TRUEP(eval_minimum_structure_contents(CADR(boolean_expression),
		    structure)) ? T : Nil;
	else
	    temp = Qnil;
    }
    else if (SYMBOLP(boolean_expression))
	temp = estructure_slot(structure,boolean_expression,Nil);
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* AGGREGATE-VALUE-TYPE-SPECIFICATION-P */
Object aggregate_value_type_specification_p(type_specification)
    Object type_specification;
{
    Object type_name, temp;

    x_note_fn_call(80,183);
    if (CONSP(type_specification)) {
	type_name = M_CAR(type_specification);
	temp = EQ(type_name,Qab_structure) ? T : Nil;
	if (temp);
	else
	    temp = EQ(type_name,Qsequence) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* AGGREGATE-EVALUATION-VALUE-P */
Object aggregate_evaluation_value_p(thing)
    Object thing;
{
    Object thing_1, cdr_1, temp_1;
    char temp;

    x_note_fn_call(80,184);
    if (CONSP(thing)) {
	thing_1 = M_CAR(thing);
	temp = SIMPLE_VECTOR_P(thing_1) ? EQ(ISVREF(thing_1,(SI_Long)0L),
		Managed_array_unique_marker) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	cdr_1 = M_CDR(thing);
	temp_1 = EQ(cdr_1,Qab_structure) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = EQ(cdr_1,Qsequence) ? T : Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qlong;               /* long */

static Object Qboolean;            /* boolean */

/* MAKE-EVALUATION-VALUE-1 */
Object make_evaluation_value_1(value,type)
    Object value, type;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    double aref_new_value;

    x_note_fn_call(80,185);
    if (EQ(type,Qfloat)) {
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
    }
    else if (EQ(type,Qinteger))
	temp_2 = value;
    else if (EQ(type,Qlong))
	temp_2 = make_evaluation_long(value);
    else if (EQ(type,Qnumber))
	temp_2 = make_evaluation_quantity(value);
    else if (EQ(type,Qtruth_value) || EQ(type,Qboolean)) {
	if (FIXNUM_EQ(value,Truth))
	    temp_2 = Evaluation_true_value;
	else if (FIXNUM_EQ(value,Falsity))
	    temp_2 = Evaluation_false_value;
	else
	    temp_2 = eval_cons_1(value,Qtruth_value);
    }
    else if (EQ(type,Qsymbol))
	temp_2 = value;
    else if (EQ(type,Qtext))
	temp_2 = copy_as_wide_string(value);
    else
	temp_2 = EQ(type,Qnumber) || EQ(type,Qinteger) || EQ(type,Qfloat) 
		|| EQ(type,Qlong) || 
		lookup_global_or_kb_specific_property_value(type,
		Numeric_data_type_gkbprop) ? 
		make_evaluation_quantity(value) : value;
    return VALUES_1(temp_2);
}

/* MAKE-EVALUATION-VALUE-FROM-LISP-VALUE */
Object make_evaluation_value_from_lisp_value(value)
    Object value;
{
    Object temp, item_or_value, x2, amf_available_array_cons_qm, amf_array;
    Object temp_2, temp_3, amf_result, new_float, gensymed_symbol;
    char temp_1;
    double aref_new_value;

    x_note_fn_call(80,186);
    if (CONSP(value) && EQ(M_CDR(value),Qsequence))
	temp = value;
    else if (CONSP(value) && EQ(M_CDR(value),Qab_structure))
	temp = value;
    else if (CONSP(value) && EQ(M_CDR(value),Qitem_reference)) {
	item_or_value = value;
	temp = CONSP(item_or_value) && EQ(M_CDR(item_or_value),
		Qitem_reference) ? ISVREF(M_CAR(item_or_value),
		(SI_Long)3L) : item_or_value;
    }
    else {
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		!EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = value;
	else if (FIXNUMP(value))
	    temp = value;
	else if ( !TRUEP(value))
	    temp = Evaluation_false_value;
	else if (EQ(value,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(value))
	    temp = value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_float(value);
	else if (FLOATP(value)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_long(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L)
	    temp = make_evaluation_long(value);
	else if (text_string_p(value))
	    temp = copy_as_wide_string(value);
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    gensymed_symbol = M_CAR(value);
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
		    type_of(value));
    }
    return VALUES_1(temp);
}

/* MAKE-EVALUATION-VALUE-RECLAIMING-ARGUMENT */
Object make_evaluation_value_reclaiming_argument(value,type_of_value)
    Object value, type_of_value;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(80,187);
    if (EQ(type_of_value,Qnumber))
	temp = make_evaluation_quantity(value);
    else if (EQ(type_of_value,Qfloat)) {
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    else if (EQ(type_of_value,Qlong))
	temp = make_evaluation_long(value);
    else if (EQ(type_of_value,Qinteger))
	temp = value;
    else if (EQ(type_of_value,Qsymbol))
	temp = value;
    else if (EQ(type_of_value,Qtruth_value) || EQ(type_of_value,Qboolean)) {
	if (FIXNUM_EQ(value,Truth))
	    temp = Evaluation_true_value;
	else if (FIXNUM_EQ(value,Falsity))
	    temp = Evaluation_false_value;
	else
	    temp = eval_cons_1(value,Qtruth_value);
    }
    else if (EQ(type_of_value,Qtext))
	temp = value;
    else
	temp = error((SI_Long)2L,
		"Invalid type ~a given to make-evaluation-value.",
		type_of_value);
    return VALUES_1(temp);
}

static Object Qiteration_state;    /* iteration-state */

static Object Qdefined_evaluation_type_reclaimer;  /* defined-evaluation-type-reclaimer */

/* RECLAIM-EVALUATION-VALUE */
Object reclaim_evaluation_value(evaluation_value)
    Object evaluation_value;
{
    Object cdr_1, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp, temp_1, entry_hash, gensymed_symbol, gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,188);
    if (CONSP(evaluation_value)) {
	cdr_1 = M_CDR(evaluation_value);
	if (EQ(cdr_1,Qtruth_value)) {
	    if ( !(EQ(evaluation_value,Evaluation_true_value) || 
		    EQ(evaluation_value,Evaluation_false_value)))
		reclaim_eval_cons_1(evaluation_value);
	}
	else if (EQ(cdr_1,Qiteration_state))
	    reclaim_evaluation_iteration_state(evaluation_value);
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = get_property_value_function(3,
			get_symbol_properties_function(cdr_1),
			Qdefined_evaluation_type_reclaimer,Nil);
		gensymed_symbol_1 = evaluation_value;
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(evaluation_value);
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L)
	reclaim_managed_simple_long_array_of_length_1(evaluation_value);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value) != (SI_Long)0L)
	reclaim_text_string(evaluation_value);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-EVALUATION-VALUE-FUNCTION */
Object reclaim_if_evaluation_value_function(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(80,189);
    temp =  !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)) ?
	     reclaim_if_evaluation_value_1(thing) : Nil;
    return VALUES_1(temp);
}

/* RECLAIM-IF-EVALUATION-VALUE-1 */
Object reclaim_if_evaluation_value_1(thing)
    Object thing;
{
    Object cdr_1, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp, temp_1, entry_hash, gensymed_symbol, gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,190);
    if (CONSP(thing)) {
	cdr_1 = M_CDR(thing);
	if (EQ(cdr_1,Qtruth_value)) {
	    if ( !(EQ(thing,Evaluation_true_value) || EQ(thing,
		    Evaluation_false_value)))
		reclaim_eval_cons_1(thing);
	}
	else if (EQ(cdr_1,Qiteration_state))
	    reclaim_evaluation_iteration_state(thing);
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = get_property_value_function(3,
			get_symbol_properties_function(cdr_1),
			Qdefined_evaluation_type_reclaimer,Nil);
		gensymed_symbol_1 = thing;
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(thing);
    else if (INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
	reclaim_managed_simple_long_array_of_length_1(thing);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_text_string(thing);
    return VALUES_1(Nil);
}

/* RECLAIM-EVAL-LIST-OF-ITEM-OR-DATUM */
Object reclaim_eval_list_of_item_or_datum(list_1)
    Object list_1;
{
    Object trailer, cons_1, thing, eval_cons, temp, svref_arg_2;

    x_note_fn_call(80,191);
    if (list_1) {
	trailer = Nil;
	cons_1 = list_1;
      next_loop:
	if ( !TRUEP(cons_1))
	    goto end_loop;
	thing = M_CAR(cons_1);
	if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	    reclaim_if_evaluation_value_1(thing);
	trailer = cons_1;
	cons_1 = M_CDR(cons_1);
	goto next_loop;
      end_loop:
	if (list_1 &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = list_1;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,trailer))
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
	    M_CDR(temp) = list_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = list_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	M_CDR(trailer) = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qdefined_evaluation_type_copier;  /* defined-evaluation-type-copier */

/* COPY-EVALUATION-VALUE-1 */
Object copy_evaluation_value_1(evaluation_value)
    Object evaluation_value;
{
    Object cdr_1, temp, car_arg, car_new_value, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, entry_hash, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,192);
    if (CONSP(evaluation_value)) {
	cdr_1 = M_CDR(evaluation_value);
	if (EQ(cdr_1,Qtruth_value))
	    temp = EQ(evaluation_value,Evaluation_true_value) || 
		    EQ(evaluation_value,Evaluation_false_value) ? 
		    evaluation_value : eval_cons_1(M_CAR(evaluation_value),
		    Qtruth_value);
	else if (EQ(cdr_1,Qiteration_state)) {
	    car_arg = M_CAR(evaluation_value);
	    car_new_value = FIXNUM_ADD1(M_CAR(car_arg));
	    M_CAR(car_arg) = car_new_value;
	    temp = evaluation_value;
	}
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = get_property_value_function(3,
			get_symbol_properties_function(cdr_1),
			Qdefined_evaluation_type_copier,Nil);
		gensymed_symbol_1 = evaluation_value;
		temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	    else
		temp = Qnil;
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L)
	temp = copy_managed_float(evaluation_value);
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L)
	temp = copy_managed_long(evaluation_value);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value) != (SI_Long)0L)
	temp = copy_wide_string(evaluation_value);
    else
	temp = evaluation_value;
    return VALUES_1(temp);
}

static Object Qdefined_evaluation_type_deep_copier;  /* defined-evaluation-type-deep-copier */

/* DEEP-COPY-EVALUATION-VALUE-1 */
Object deep_copy_evaluation_value_1(evaluation_value)
    Object evaluation_value;
{
    Object cdr_1, temp, car_arg, car_new_value, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, entry_hash, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,193);
    if (CONSP(evaluation_value)) {
	cdr_1 = M_CDR(evaluation_value);
	if (EQ(cdr_1,Qtruth_value))
	    temp = EQ(evaluation_value,Evaluation_true_value) || 
		    EQ(evaluation_value,Evaluation_false_value) ? 
		    evaluation_value : eval_cons_1(M_CAR(evaluation_value),
		    Qtruth_value);
	else if (EQ(cdr_1,Qiteration_state)) {
	    car_arg = M_CAR(evaluation_value);
	    car_new_value = FIXNUM_ADD1(M_CAR(car_arg));
	    M_CAR(car_arg) = car_new_value;
	    temp = evaluation_value;
	}
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = get_property_value_function(3,
			get_symbol_properties_function(cdr_1),
			Qdefined_evaluation_type_deep_copier,Nil);
		if (gensymed_symbol);
		else
		    gensymed_symbol = get_property_value_function(3,
			    get_symbol_properties_function(cdr_1),
			    Qdefined_evaluation_type_copier,Nil);
		gensymed_symbol_1 = evaluation_value;
		temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	    else
		temp = Qnil;
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L)
	temp = copy_managed_float(evaluation_value);
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L)
	temp = copy_managed_long(evaluation_value);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value) != (SI_Long)0L)
	temp = copy_wide_string(evaluation_value);
    else
	temp = evaluation_value;
    return VALUES_1(temp);
}

/* COPY-IF-EVALUATION-VALUE-1 */
Object copy_if_evaluation_value_1(thing)
    Object thing;
{
    Object cdr_1, temp, car_arg, car_new_value, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, entry_hash, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,194);
    if (CONSP(thing)) {
	cdr_1 = M_CDR(thing);
	if (EQ(cdr_1,Qtruth_value))
	    temp = EQ(thing,Evaluation_true_value) || EQ(thing,
		    Evaluation_false_value) ? thing : 
		    eval_cons_1(M_CAR(thing),Qtruth_value);
	else if (EQ(cdr_1,Qiteration_state)) {
	    car_arg = M_CAR(thing);
	    car_new_value = FIXNUM_ADD1(M_CAR(car_arg));
	    M_CAR(car_arg) = car_new_value;
	    temp = thing;
	}
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = get_property_value_function(3,
			get_symbol_properties_function(cdr_1),
			Qdefined_evaluation_type_copier,Nil);
		gensymed_symbol_1 = thing;
		temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	    else
		temp = thing;
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
	temp = copy_managed_float(thing);
    else if (INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
	temp = copy_managed_long(thing);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	temp = copy_wide_string(thing);
    else
	temp = thing;
    return VALUES_1(temp);
}

/* DEEP-COPY-IF-EVALUATION-VALUE-1 */
Object deep_copy_if_evaluation_value_1(thing)
    Object thing;
{
    Object cdr_1, temp, car_arg, car_new_value, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, entry_hash, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,195);
    if (CONSP(thing)) {
	cdr_1 = M_CDR(thing);
	if (EQ(cdr_1,Qtruth_value))
	    temp = EQ(thing,Evaluation_true_value) || EQ(thing,
		    Evaluation_false_value) ? thing : 
		    eval_cons_1(M_CAR(thing),Qtruth_value);
	else if (EQ(cdr_1,Qiteration_state)) {
	    car_arg = M_CAR(thing);
	    car_new_value = FIXNUM_ADD1(M_CAR(car_arg));
	    M_CAR(car_arg) = car_new_value;
	    temp = thing;
	}
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = get_property_value_function(3,
			get_symbol_properties_function(cdr_1),
			Qdefined_evaluation_type_deep_copier,Nil);
		if (gensymed_symbol);
		else
		    gensymed_symbol = get_property_value_function(3,
			    get_symbol_properties_function(cdr_1),
			    Qdefined_evaluation_type_copier,Nil);
		gensymed_symbol_1 = thing;
		temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	    else
		temp = thing;
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
	temp = copy_managed_float(thing);
    else if (INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
	temp = copy_managed_long(thing);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	temp = copy_wide_string(thing);
    else
	temp = thing;
    return VALUES_1(temp);
}

/* EVALUATION-VALUE-VALUE */
Object evaluation_value_value(evaluation_value)
    Object evaluation_value;
{
    Object cdr_1, temp, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,196);
    if (CONSP(evaluation_value)) {
	cdr_1 = M_CDR(evaluation_value);
	if (EQ(cdr_1,Qtruth_value))
	    temp = M_CAR(evaluation_value);
	else if (EQ(cdr_1,Qiteration_state))
	    temp = M_CDR(M_CAR(evaluation_value));
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		temp = M_CAR(evaluation_value);
	    else
		temp = Qnil;
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_value,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L)
	temp = aref1(evaluation_value,FIX((SI_Long)0L));
    else
	temp = evaluation_value;
    return VALUES_1(temp);
}

static Object list_constant_3;     /* # */

static Object Qtype_specification_of_defined_evaluation_type;  /* type-specification-of-defined-evaluation-type */

/* EVALUATION-VALUE-TYPE */
Object evaluation_value_type(evaluation_value)
    Object evaluation_value;
{
    Object temp, cdr_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(80,197);
    if (FIXNUMP(evaluation_value))
	temp = Qinteger;
    else if (CONSP(evaluation_value)) {
	cdr_1 = M_CDR(evaluation_value);
	if (EQ(cdr_1,Qtruth_value))
	    temp = Qtruth_value;
	else if (EQ(cdr_1,Qiteration_state))
	    temp = list_constant_3;
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		temp = get_property_value_function(3,
			get_symbol_properties_function(cdr_1),
			Qtype_specification_of_defined_evaluation_type,Nil);
	    else
		temp = Qnil;
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L)
	temp = Qfloat;
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L)
	temp = Qlong;
    else if (evaluation_value && SYMBOLP(evaluation_value))
	temp = Qsymbol;
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value) != (SI_Long)0L)
	temp = Qtext;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* EVALUATION-VALUE-P-FUNCTION */
Object evaluation_value_p_function(evaluation_value)
    Object evaluation_value;
{
    Object gensymed_symbol, temp, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(80,198);
    gensymed_symbol = evaluation_value;
    temp = FIXNUMP(gensymed_symbol) ? T : Nil;
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
    if (temp);
    else
	temp = gensymed_symbol ? (SYMBOLP(gensymed_symbol) ? T : Nil) : Qnil;
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? T : Nil;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value) ? T : Nil;
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state) ? T : Nil;
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
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		    (SI_Long)3L) : Nil) : Nil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* ITEM-OR-VALUE-EQUALP */
Object item_or_value_equalp(item_or_value_1,item_or_value_2)
    Object item_or_value_1, item_or_value_2;
{
    Object temp, x2;
    char temp_1;

    x_note_fn_call(80,199);
    temp = EQ(item_or_value_1,item_or_value_2) ? T : Nil;
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(item_or_value_1) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value_1,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value_1,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp =  !temp_1 ? evaluation_value_eq(item_or_value_1,
		item_or_value_2) : Nil;
    }
    return VALUES_1(temp);
}

static Object Qdefined_evaluation_type_eq;  /* defined-evaluation-type-= */

/* EVALUATION-VALUE-= */
Object evaluation_value_eq(evaluation_value_1,evaluation_value_2)
    Object evaluation_value_1, evaluation_value_2;
{
    Object temp, gensymed_symbol, type_of_value_1, gensymed_symbol_1;
    Object gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(80,200);
    if ( !TRUEP(evaluation_value_1))
	temp =  !TRUEP(evaluation_value_2) ? T : Nil;
    else if ( !TRUEP(evaluation_value_2))
	temp = Nil;
    else if (FIXNUMP(evaluation_value_1) || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_1)) == 
	    (SI_Long)1L || INLINE_LONG_VECTOR_P(evaluation_value_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_1)) == (SI_Long)1L)
	temp = FIXNUMP(evaluation_value_2) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_2)) == 
		(SI_Long)1L || INLINE_LONG_VECTOR_P(evaluation_value_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_2)) == 
		(SI_Long)1L ? evaluation_quantity_eq(evaluation_value_1,
		evaluation_value_2) : Qnil;
    else if (evaluation_value_1 && SYMBOLP(evaluation_value_1))
	temp = evaluation_value_2 && SYMBOLP(evaluation_value_2) ? 
		(EQ(evaluation_value_1,evaluation_value_2) ? T : Nil) : Qnil;
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_1) != 
	    (SI_Long)0L)
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_2) != 
		(SI_Long)0L ? string_equalw(evaluation_value_1,
		evaluation_value_2) : Qnil;
    else if (CONSP(evaluation_value_1) && EQ(M_CDR(evaluation_value_1),
	    Qtruth_value))
	temp = CONSP(evaluation_value_2) && EQ(M_CDR(evaluation_value_2),
		Qtruth_value) ? (FIXNUM_EQ(M_CAR(evaluation_value_1),
		M_CAR(evaluation_value_2)) ? T : Nil) : Qnil;
    else if (CONSP(evaluation_value_1) && EQ(M_CDR(evaluation_value_1),
	    Qiteration_state))
	temp = Nil;
    else {
	if (CONSP(evaluation_value_1)) {
	    gensymed_symbol = evaluation_value_1;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
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
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = TRUEP(memq_function(gensymed_symbol,
			    Defined_evaluation_datum_types));
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    type_of_value_1 = get_property_value_function(3,
		    get_symbol_properties_function(M_CDR(evaluation_value_1)),
		    Qtype_specification_of_defined_evaluation_type,Nil);
	    if (type_specification_type_p(evaluation_value_2,
			type_of_value_1)) {
		gensymed_symbol = get_property_value_function(3,
			get_symbol_properties_function(M_CAR(type_of_value_1)),
			Qdefined_evaluation_type_eq,Nil);
		gensymed_symbol_1 = evaluation_value_1;
		gensymed_symbol_2 = evaluation_value_2;
		temp = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* EVALUATION-VALUES-CAN-BE-CONSTANT-FOLDED-P */
Object evaluation_values_can_be_constant_folded_p(evaluation_value_1,
	    evaluation_value_2)
    Object evaluation_value_1, evaluation_value_2;
{
    Object temp;

    x_note_fn_call(80,201);
    temp = evaluation_value_eql(3,evaluation_value_1,evaluation_value_2,T);
    return VALUES_1(temp);
}

/* ITEM-OR-VALUE-EQL */
Object item_or_value_eql(item_or_value_1,item_or_value_2)
    Object item_or_value_1, item_or_value_2;
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(80,202);
    if (SIMPLE_VECTOR_P(item_or_value_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = EQ(item_or_value_1,item_or_value_2) ? T : Nil;
    else {
	if (SIMPLE_VECTOR_P(item_or_value_2) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_2)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value_2,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value_2,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_1 =  !temp ? evaluation_value_eql(2,item_or_value_1,
		item_or_value_2) : Nil;
    }
    return VALUES_1(temp_1);
}

static Object Qdefined_evaluation_type_comparitor;  /* defined-evaluation-type-comparitor */

/* EVALUATION-VALUE-EQL */
Object evaluation_value_eql varargs_1(int, n)
{
    Object evaluation_value_1, evaluation_value_2;
    Object is_case_sensitive_p, temp, cdr_1, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, entry_hash, comparitor_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    double arg, arg_1;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(80,203);
    INIT_ARGS_nonrelocating();
    evaluation_value_1 = REQUIRED_ARG_nonrelocating();
    evaluation_value_2 = REQUIRED_ARG_nonrelocating();
    is_case_sensitive_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = EQ(evaluation_value_1,evaluation_value_2) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (CONSP(evaluation_value_1)) {
	cdr_1 = M_CDR(evaluation_value_1);
	if (EQ(cdr_1,Qtruth_value)) {
	    if (CONSP(evaluation_value_2) && EQ(M_CDR(evaluation_value_2),
		    Qtruth_value))
		return VALUES_1(FIXNUM_EQ(M_CAR(evaluation_value_1),
			M_CAR(evaluation_value_2)) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(cdr_1,Qiteration_state))
	    return VALUES_1(Nil);
	else {
	    if (SYMBOLP(cdr_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = cdr_1;
		key_hash_value = SXHASH_SYMBOL_1(cdr_1) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		if (CONSP(evaluation_value_2) && EQ(cdr_1,
			M_CDR(evaluation_value_2))) {
		    comparitor_qm = get_property_value_function(3,
			    get_symbol_properties_function(cdr_1),
			    Qdefined_evaluation_type_comparitor,Nil);
		    if (comparitor_qm)
			return VALUES_1(inline_funcall_2(comparitor_qm,
				evaluation_value_1,evaluation_value_2));
		    else
			return VALUES_1(Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value_1) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_1)) == 
		(SI_Long)1L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_2)) == 
		(SI_Long)1L) {
	    arg = DFLOAT_ISAREF_1(evaluation_value_1,(SI_Long)0L);
	    arg_1 = DFLOAT_ISAREF_1(evaluation_value_2,(SI_Long)0L);
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg))
		return VALUES_1( !inline_nanp_for_comparison(arg_1) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_1) != 
	    (SI_Long)0L) {
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_2) != 
		(SI_Long)0L) {
	    if (is_case_sensitive_p)
		return string_eq_w(evaluation_value_1,evaluation_value_2);
	    else
		return string_equalw(evaluation_value_1,evaluation_value_2);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (evaluation_value_1 && SYMBOLP(evaluation_value_1))
	return VALUES_1(EQ(evaluation_value_1,evaluation_value_2) ? T : Nil);
    else if (FIXNUMP(evaluation_value_1)) {
	if (FIXNUMP(evaluation_value_2))
	    return VALUES_1(FIXNUM_EQ(evaluation_value_1,
		    evaluation_value_2) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (INLINE_LONG_VECTOR_P(evaluation_value_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_1)) == 
		(SI_Long)1L) {
	if (INLINE_LONG_VECTOR_P(evaluation_value_2) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_2)) == 
		(SI_Long)1L) {
	    temp_1 = aref1(evaluation_value_1,FIX((SI_Long)0L));
	    temp = aref1(evaluation_value_2,FIX((SI_Long)0L));
	    return VALUES_1(NUM_EQ(temp_1,temp) ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* EVALUATION-VALUE-EQUAL-P */
Object evaluation_value_equal_p(evaluation_value_1,evaluation_value_2)
    Object evaluation_value_1, evaluation_value_2;
{
    Object temp;

    x_note_fn_call(80,204);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_1) != 
	    (SI_Long)0L ? 
	    (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_2) != 
	    (SI_Long)0L ? string_equalw(evaluation_value_1,
	    evaluation_value_2) : Qnil) : evaluation_value_eql(2,
	    evaluation_value_1,evaluation_value_2);
    return VALUES_1(temp);
}

/* MAKE-TEMPORARY-CONSTANT-FROM-EVALUATION-VALUE */
Object make_temporary_constant_from_evaluation_value(evaluation_value)
    Object evaluation_value;
{
    Object temp;

    x_note_fn_call(80,205);
    temp = 
	    make_temporary_constant_copying_managed_value_no_expiration(CONSP(evaluation_value) 
	    && EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    M_CAR(evaluation_value) : evaluation_value,
	    evaluation_value_type(evaluation_value));
    return VALUES_1(temp);
}

/* TRANSFORM-EVALUATION-VALUE-INTO-TEMPORARY-CONSTANT */
Object transform_evaluation_value_into_temporary_constant(evaluation_value)
    Object evaluation_value;
{
    Object type, managed_value, temp;

    x_note_fn_call(80,206);
    type = evaluation_value_type(evaluation_value);
    managed_value = evaluation_value;
    if (EQ(type,Qboolean)) {
	managed_value = M_CAR(evaluation_value);
	type = Qtruth_value;
    }
    else if (EQ(type,Qtruth_value)) {
	managed_value = M_CAR(evaluation_value);
	if ( !(EQ(evaluation_value,Evaluation_true_value) || 
		EQ(evaluation_value,Evaluation_false_value)))
	    reclaim_eval_cons_1(evaluation_value);
    }
    temp = 
	    make_temporary_constant_given_managed_value_no_expiration(managed_value,
	    type);
    return VALUES_1(temp);
}

/* TRANSFORM-TEMPORARY-CONSTANT-INTO-EVALUATION-VALUE */
Object transform_temporary_constant_into_evaluation_value(temporary_constant)
    Object temporary_constant;
{
    Object managed_value, type;

    x_note_fn_call(80,207);
    managed_value = ISVREF(temporary_constant,(SI_Long)1L);
    type = ISVREF(temporary_constant,(SI_Long)2L);
    SVREF(temporary_constant,FIX((SI_Long)1L)) = Nil;
    reclaim_temporary_constant_1(temporary_constant);
    if (EQ(type,Qtruth_value) || EQ(type,Qboolean)) {
	if (FIXNUM_EQ(managed_value,Truth))
	    managed_value = Evaluation_true_value;
	else if (FIXNUM_EQ(managed_value,Falsity))
	    managed_value = Evaluation_false_value;
	else
	    managed_value = eval_cons_1(managed_value,Qtruth_value);
    }
    return VALUES_1(managed_value);
}

/* MAKE-EVALUATION-VALUE-FROM-TEMPORARY-CONSTANT */
Object make_evaluation_value_from_temporary_constant(temporary_constant)
    Object temporary_constant;
{
    Object type, gensymed_symbol, temp, evaluation_value;

    x_note_fn_call(80,208);
    type = ISVREF(temporary_constant,(SI_Long)2L);
    if (EQ(type,Qtruth_value) || EQ(type,Qboolean)) {
	gensymed_symbol = ISVREF(temporary_constant,(SI_Long)1L);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    temp = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    temp = Evaluation_false_value;
	else
	    temp = eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else {
	evaluation_value = ISVREF(temporary_constant,(SI_Long)1L);
	temp = FIXNUMP(evaluation_value) || evaluation_value && 
		SYMBOLP(evaluation_value) ? evaluation_value : 
		copy_evaluation_value_1(evaluation_value);
    }
    return VALUES_1(temp);
}

/* MAKE-EVALUATION-VALUE-LIST-FROM-TEMPORARY-CONSTANT-LIST */
Object make_evaluation_value_list_from_temporary_constant_list(list_1)
    Object list_1;
{
    Object temporary_constant, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(80,209);
    temporary_constant = Nil;
    ab_loop_list_ = list_1;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temporary_constant = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    eval_cons_1(make_evaluation_value_from_temporary_constant(temporary_constant),
	    Nil);
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
    return VALUES_1(temp);
}

/* RECLAIM-EVALUATION-OBSOLETE-DATUM */
Object reclaim_evaluation_obsolete_datum(obsolete_datum)
    Object obsolete_datum;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,210);
    reclaim_evaluation_value(M_CAR(obsolete_datum));
    if (obsolete_datum) {
	inline_note_reclaim_cons(obsolete_datum,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = obsolete_datum;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = obsolete_datum;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = obsolete_datum;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = obsolete_datum;
	}
	M_CDR(obsolete_datum) = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qobsolete_datum;     /* obsolete-datum */

/* COPY-EVALUATION-OBSOLETE-DATUM */
Object copy_evaluation_obsolete_datum(obsolete_datum)
    Object obsolete_datum;
{
    Object evaluation_value, temp;

    x_note_fn_call(80,211);
    evaluation_value = M_CAR(obsolete_datum);
    temp = eval_cons_1(FIXNUMP(evaluation_value) || evaluation_value && 
	    SYMBOLP(evaluation_value) ? evaluation_value : 
	    copy_evaluation_value_1(evaluation_value),Qobsolete_datum);
    return VALUES_1(temp);
}

/* DEEP-COPY-EVALUATION-OBSOLETE-DATUM */
Object deep_copy_evaluation_obsolete_datum(obsolete_datum)
    Object obsolete_datum;
{
    Object evaluation_value, temp;

    x_note_fn_call(80,212);
    evaluation_value = M_CAR(obsolete_datum);
    temp = eval_cons_1(FIXNUMP(evaluation_value) || evaluation_value && 
	    SYMBOLP(evaluation_value) ? evaluation_value : 
	    deep_copy_evaluation_value_1(evaluation_value),Qobsolete_datum);
    return VALUES_1(temp);
}

/* EVALUATION-OBSOLETE-DATUM-EQL */
Object evaluation_obsolete_datum_eql(obsolete_datum_1,obsolete_datum_2)
    Object obsolete_datum_1, obsolete_datum_2;
{
    Object temp;

    x_note_fn_call(80,213);
    temp = evaluation_value_eql(2,M_CAR(obsolete_datum_1),
	    M_CAR(obsolete_datum_2));
    return VALUES_1(temp);
}

static Object Qevaluation_value;   /* evaluation-value */

static Object list_constant_4;     /* # */

/* EVALUATION-VALUE-TYPE-SPECIFICATION-P */
Object evaluation_value_type_specification_p(thing)
    Object thing;
{
    Object temp, gensymed_symbol, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(80,214);
    temp = EQ(thing,Qevaluation_value) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (CONSP(thing)) {
	temp = iteration_state_type_specification_p(thing);
	if (temp)
	    return VALUES_1(temp);
	else {
	    gensymed_symbol = M_CAR(thing);
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
	    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil)) {
		temp =  !TRUEP(M_CDR(thing)) ? T : Nil;
		if (temp)
		    return VALUES_1(temp);
		else
		    return memq_function(M_CAR(thing),list_constant_4);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

Object Type_specification_simple_expansion_prop = UNBOUND;

Object Type_specification_explicit_complex_type_prop = UNBOUND;

static Object Qtype_specification_explicit_complex_type;  /* type-specification-explicit-complex-type */

/* DEFINE-TYPE-SPECIFICATION-EXPLICIT-COMPLEX-TYPE */
Object define_type_specification_explicit_complex_type(new_name,complex_type)
    Object new_name, complex_type;
{
    x_note_fn_call(80,215);
    set_property_value_function(get_symbol_properties_function(new_name),
	    Qtype_specification_explicit_complex_type,complex_type);
    return VALUES_1(new_name);
}

Object Type_symbols_subtype_alist = UNBOUND;

/* SYMBOLIC-TYPE-SPECIFICATION-P */
Object symbolic_type_specification_p(thing)
    Object thing;
{
    Object gensymed_symbol, ab_loop_list_;
    char temp;

    x_note_fn_call(80,216);
    gensymed_symbol = Nil;
    ab_loop_list_ = Type_symbols_subtype_alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),thing)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    return VALUES_1( ! !temp ? T : Nil);
}

/* SYMBOLIC-TYPE-SPECIFICATION-SUBTYPE-P */
Object symbolic_type_specification_subtype_p(type,superior_type)
    Object type, superior_type;
{
    Object temp, gensymed_symbol, ab_loop_list_;

    x_note_fn_call(80,217);
    temp = EQ(type,superior_type) ? T : Nil;
    if (temp);
    else {
	gensymed_symbol = Nil;
	ab_loop_list_ = Type_symbols_subtype_alist;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),superior_type)) {
	    temp = gensymed_symbol;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
	gensymed_symbol = CDR(temp);
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	if (EQ(M_CAR(gensymed_symbol),type)) {
	    temp = gensymed_symbol;
	    goto end_2;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_2:;
    }
    return VALUES_1(temp);
}

Object Type_specification_for_item = UNBOUND;

static Object Qab_class;           /* class */

/* MAKE-CLASS-TYPE-SPECIFICATION */
Object make_class_type_specification(class_name)
    Object class_name;
{
    Object temp;

    x_note_fn_call(80,218);
    temp = EQ(class_name,Qitem) ? Type_specification_for_item : 
	    phrase_list_2(Qab_class,class_name);
    return VALUES_1(temp);
}

Object Type_specification_for_iteration_state = UNBOUND;

/* MAKE-TYPE-SPECIFICATION-FOR-ITERATION-STATE */
Object make_type_specification_for_iteration_state()
{
    x_note_fn_call(80,219);
    return VALUES_1(Type_specification_for_iteration_state);
}

Object Type_specification_for_unknown = UNBOUND;

/* MAKE-TYPE-SPECIFICATION-FOR-UNKNOWN */
Object make_type_specification_for_unknown()
{
    x_note_fn_call(80,220);
    return VALUES_1(Type_specification_for_unknown);
}

Object Type_specification_for_no_item = UNBOUND;

/* MAKE-TYPE-SPECIFICATION-FOR-NO-ITEM */
Object make_type_specification_for_no_item()
{
    x_note_fn_call(80,221);
    return VALUES_1(Type_specification_for_no_item);
}

static Object list_constant_5;     /* # */

/* MAKE-TYPE-SPECIFICATION-FOR-NO-ITEM-IMPLIES-UNKNOWN */
Object make_type_specification_for_no_item_implies_unknown()
{
    x_note_fn_call(80,222);
    return VALUES_1(list_constant_5);
}

/* VALID-CLASS-TYPE-SPECIFICATION-P */
Object valid_class_type_specification_p(thing)
    Object thing;
{
    Object class_cons_qm, class_qm, temp;

    x_note_fn_call(80,223);
    if (CONSP(thing) && EQ(M_CAR(thing),Qab_class)) {
	class_cons_qm = M_CDR(thing);
	if (CONSP(class_cons_qm) &&  !TRUEP(M_CDR(class_cons_qm))) {
	    class_qm = M_CAR(class_cons_qm);
	    temp = class_qm ? (SYMBOLP(class_qm) ? T : Nil) : Qnil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* CLASS-TYPE-SPECIFICATION-P */
Object class_type_specification_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(80,224);
    temp = CONSP(type_specification) ? (EQ(M_CAR(type_specification),
	    Qab_class) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* ITERATION-STATE-TYPE-SPECIFICATION-P */
Object iteration_state_type_specification_p(type_specification)
    Object type_specification;
{
    x_note_fn_call(80,225);
    return VALUES_1(CONSP(type_specification) && 
	    EQ(M_CAR(type_specification),Qiteration_state) ? ( 
	    !TRUEP(M_CDR(type_specification)) ? T : Nil) : Qnil);
}

static Object Qunknown_datum;      /* unknown-datum */

/* UNKNOWN-TYPE-SPECIFICATION-P */
Object unknown_type_specification_p(type_specification)
    Object type_specification;
{
    x_note_fn_call(80,226);
    return VALUES_1(CONSP(type_specification) && 
	    EQ(M_CAR(type_specification),Qunknown_datum) ? ( 
	    !TRUEP(M_CDR(type_specification)) ? T : Nil) : Qnil);
}

static Object Qno_item;            /* no-item */

/* NO-ITEM-TYPE-SPECIFICATION-P */
Object no_item_type_specification_p(type_specification)
    Object type_specification;
{
    x_note_fn_call(80,227);
    return VALUES_1(CONSP(type_specification) && 
	    EQ(M_CAR(type_specification),Qno_item) ? ( 
	    !TRUEP(M_CDR(type_specification)) ? T : Nil) : Qnil);
}

static Object Qno_item_implies_unknown;  /* no-item-implies-unknown */

/* NO-ITEM-IMPLIES-UNKNOWN-TYPE-SPECIFICATION-P */
Object no_item_implies_unknown_type_specification_p(type_specification)
    Object type_specification;
{
    x_note_fn_call(80,228);
    return VALUES_1(CONSP(type_specification) && 
	    EQ(M_CAR(type_specification),Qno_item_implies_unknown) ? ( 
	    !TRUEP(M_CDR(type_specification)) ? T : Nil) : Qnil);
}

/* TYPE-SPECIFICATION-CLASS-FUNCTION */
Object type_specification_class_function(class_type_specification)
    Object class_type_specification;
{
    x_note_fn_call(80,229);
    return VALUES_1(M_CAR(M_CDR(class_type_specification)));
}

static Object Qdatum;              /* datum */

/* DATUM-TYPE-SPECIFICATION-P */
Object datum_type_specification_p(type)
    Object type;
{
    Object temp;

    x_note_fn_call(80,230);
    temp = type_specification_subtype_in_kb_p(type,Qdatum);
    return VALUES_1(temp);
}

/* VALID-DATUM-TYPE-SPECIFICATION-P */
Object valid_datum_type_specification_p(type)
    Object type;
{
    Object temp;

    x_note_fn_call(80,231);
    temp = valid_type_specification_p(type) ? 
	    type_specification_subtype_in_kb_p(type,Qdatum) : Qnil;
    return VALUES_1(temp);
}

static Object Qnamed;              /* named */

/* FAST-NAMED-TYPE-SPECIFICATION-P */
Object fast_named_type_specification_p(type)
    Object type;
{
    Object temp;

    x_note_fn_call(80,232);
    temp = CONSP(type) ? (EQ(CAR(type),Qnamed) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

static Object Qtype_specification_simple_expansion;  /* type-specification-simple-expansion */

/* NAMED-TYPE-SPECIFICATION-P */
Object named_type_specification_p(type)
    Object type;
{
    Object type_name, temp;

    x_note_fn_call(80,233);
    if (CONSP(type) && EQ(CAR(type),Qnamed)) {
	type_name = CADR(type);
	temp = get_property_value_function(3,
		get_symbol_properties_function(type_name),
		Qtype_specification_explicit_complex_type,Nil);
	if (temp);
	else
	    temp = get_property_value_function(3,
		    get_symbol_properties_function(type_name),
		    Qtype_specification_simple_expansion,Nil);
	temp = valid_type_specification_p(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EXPAND-NAMED-TYPE */
Object expand_named_type(type)
    Object type;
{
    Object type_name, temp;

    x_note_fn_call(80,234);
    if (CONSP(type) && EQ(CAR(type),Qnamed)) {
	type_name = CADR(type);
	temp = get_property_value_function(3,
		get_symbol_properties_function(type_name),
		Qtype_specification_explicit_complex_type,Nil);
	if (temp);
	else
	    temp = get_property_value_function(3,
		    get_symbol_properties_function(type_name),
		    Qtype_specification_simple_expansion,Nil);
    }
    else
	temp = type;
    return VALUES_1(temp);
}

/* VALID-TYPE-SPECIFICATION-P */
Object valid_type_specification_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(80,235);
    if (SYMBOLP(thing))
	temp = symbolic_type_specification_p(thing);
    else if (CONSP(thing)) {
	temp = CAR(thing);
	if (EQ(temp,Qab_or))
	    temp = union_type_specification_p(thing);
	else if (EQ(temp,Qab_class))
	    temp = valid_class_type_specification_p(thing);
	else if (EQ(temp,Qno_item))
	    temp = no_item_type_specification_p(thing);
	else if (EQ(temp,Qno_item_implies_unknown))
	    temp = no_item_implies_unknown_type_specification_p(thing);
	else if (EQ(temp,Qand))
	    temp = intersection_type_specification_p(thing);
	else if (EQ(temp,Qnot))
	    temp = negation_type_specification_p(thing);
	else if (EQ(temp,Qsatisfies))
	    temp = filtered_type_specification_p(thing);
	else if (EQ(temp,Qmember))
	    temp = member_type_specification_p(thing);
	else if (EQ(temp,Qab_structure))
	    temp = structure_type_specification_p(thing);
	else if (EQ(temp,Qsequence))
	    temp = sequence_type_specification_p(thing);
	else if (EQ(temp,Qnamed))
	    temp = named_type_specification_p(thing);
	else if (EQ(temp,Qunknown_datum))
	    temp = unknown_type_specification_p(thing);
	else
	    temp = evaluation_value_type_specification_p(thing);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FAST-UNION-TYPE-SPECIFICATION-P */
Object fast_union_type_specification_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(80,236);
    temp = CONSP(type_specification) ? (EQ(M_CAR(type_specification),
	    Qab_or) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* UNION-TYPE-SPECIFICATION-P */
Object union_type_specification_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(80,237);
    temp = CONSP(type_specification) && EQ(M_CAR(type_specification),
	    Qab_or) ? 
	    valid_type_specification_list_p(M_CDR(type_specification)) : Qnil;
    return VALUES_1(temp);
}

/* VALID-TYPE-SPECIFICATION-LIST-P */
Object valid_type_specification_list_p(thing)
    Object thing;
{
    Object result_1, type_cons, temp;

    x_note_fn_call(80,238);
    result_1 = T;
    type_cons = thing;
  next_loop:
    if ( !TRUEP(type_cons))
	goto end_loop;
    result_1 = CONSP(type_cons) ? 
	    valid_type_specification_p(M_CAR(type_cons)) : Qnil;
    if ( !TRUEP(result_1))
	goto end_loop;
    type_cons = M_CDR(type_cons);
    goto next_loop;
  end_loop:
    temp = result_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FAST-INTERSECTION-TYPE-SPECIFICATION-P */
Object fast_intersection_type_specification_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(80,239);
    temp = CONSP(type_specification) ? (EQ(M_CAR(type_specification),Qand) 
	    ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* INTERSECTION-TYPE-SPECIFICATION-P */
Object intersection_type_specification_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(80,240);
    temp = CONSP(type_specification) && EQ(M_CAR(type_specification),Qand) 
	    ? valid_type_specification_list_p(M_CDR(type_specification)) : 
	    Qnil;
    return VALUES_1(temp);
}

/* FAST-NEGATION-TYPE-SPECIFICATION-P */
Object fast_negation_type_specification_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(80,241);
    temp = CONSP(type_specification) ? (EQ(M_CAR(type_specification),Qnot) 
	    ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* NEGATION-TYPE-SPECIFICATION-P */
Object negation_type_specification_p(type_specification)
    Object type_specification;
{
    Object type_cons_qm, temp;

    x_note_fn_call(80,242);
    if (CONSP(type_specification) && EQ(M_CAR(type_specification),Qnot)) {
	type_cons_qm = M_CDR(type_specification);
	temp = CONSP(type_cons_qm) && 
		valid_type_specification_p(M_CAR(type_cons_qm)) ? ( 
		!TRUEP(M_CDR(type_cons_qm)) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DIFFERENCE-TYPE-SPECIFICATION-IN-KB-P */
Object difference_type_specification_in_kb_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(80,243);
    temp = CONSP(type_specification) && EQ(M_CAR(type_specification),Qand) 
	    && valid_type_specification_list_p(M_CDR(type_specification)) 
	    && IFIX(length(type_specification)) == (SI_Long)3L && 
	    negation_type_specification_p(M_CAR(M_CDR(M_CDR(type_specification)))) 
	    ? 
	    type_specification_subtype_in_kb_p(M_CAR(M_CDR(M_CAR(M_CDR(M_CDR(type_specification))))),
	    M_CAR(M_CDR(type_specification))) : Qnil;
    return VALUES_1(temp);
}

/* FILTERED-TYPE-SPECIFICATION-P */
Object filtered_type_specification_p(type_specification)
    Object type_specification;
{
    Object predicate_cons_qm, temp;
    char temp_1;

    x_note_fn_call(80,244);
    if (CONSP(type_specification) && EQ(M_CAR(type_specification),
		Qsatisfies)) {
	predicate_cons_qm = M_CDR(type_specification);
	if (CONSP(predicate_cons_qm)) {
	    temp = M_CAR(predicate_cons_qm);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = (temp_1 ? TRUEP(fboundp(M_CAR(predicate_cons_qm))) : 
		TRUEP(Nil)) ? ( !TRUEP(M_CDR(predicate_cons_qm)) ? T : 
		Nil) : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* MEMBER-TYPE-SPECIFICATION-P */
Object member_type_specification_p(type_specification)
    Object type_specification;
{
    Object elt_1, ab_loop_list_, gensymed_symbol, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(80,245);
    if (CONSP(type_specification) && EQ(M_CAR(type_specification),Qmember)) {
	elt_1 = Nil;
	ab_loop_list_ = M_CDR(type_specification);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	elt_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = elt_1;
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
	if ( !temp) {
	    temp_2 = Nil;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	temp_2 = T;
	goto end_2;
	temp_2 = Qnil;
      end_2:;
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* TYPE-SPECIFICATIONS-COULD-INTERSECT-IN-KB-P */
Object type_specifications_could_intersect_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object temp;

    x_note_fn_call(80,246);
    temp = type_specifications_could_intersect_in_kb_p_1(type,superior_type);
    return VALUES_1(temp);
}

static Object Qitem_or_datum;      /* item-or-datum */

/* TYPE-SPECIFICATIONS-COULD-INTERSECT-IN-KB-P-1 */
Object type_specifications_could_intersect_in_kb_p_1(type,superior_type)
    Object type, superior_type;
{
    Object temp, subtype, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(80,247);
    temp = EQUAL(type,superior_type) ? T : Nil;
    if (temp);
    else if (union_type_specification_p(superior_type)) {
	subtype = Nil;
	ab_loop_list_ = M_CDR(superior_type);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subtype = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = type_specifications_could_intersect_in_kb_p_1(type,
		subtype);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else if (intersection_type_specification_p(superior_type)) {
	subtype = Nil;
	ab_loop_list_ = M_CDR(superior_type);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	subtype = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(type_specifications_could_intersect_in_kb_p_1(type,
		subtype))) {
	    temp = Nil;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = T;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else if (negation_type_specification_p(superior_type))
	temp =  !TRUEP(type_specification_subtype_in_kb_p(type,
		M_CAR(M_CDR(superior_type)))) ? T : Nil;
    else if (class_type_specification_p(superior_type))
	temp = class_type_specification_p(type) ? 
		class_type_specifications_could_intersect_in_kb_p(superior_type,
		type) : Qnil;
    else if (aggregate_value_type_specification_p(superior_type)) {
	temp = EQ(type,Qdatum) ? T : Nil;
	if (temp);
	else
	    temp = EQ(type,Qitem_or_datum) ? T : Nil;
	if (temp);
	else
	    temp = EQ(type,Qevaluation_value) ? T : Nil;
	if (temp);
	else
	    temp = CONSP(type) && EQ(M_CAR(type),Qab_structure) && 
		    CONSP(superior_type) && EQ(M_CAR(superior_type),
		    Qab_structure) ? 
		    structure_type_specifications_could_intersect_in_kb_p(type,
		    superior_type) : Qnil;
	if (temp);
	else
	    temp = fast_sequence_type_specification_p(type) && 
		    fast_sequence_type_specification_p(superior_type) ? 
		    sequence_type_specifications_could_intersect_in_kb_p(type,
		    superior_type) : Qnil;
    }
    else if (member_type_specification_p(superior_type)) {
	temp = EQ(type,Qitem_or_datum) ? T : Nil;
	if (temp);
	else
	    temp = EQ(type,Qevaluation_value) ? T : Nil;
	if (temp);
	else
	    temp = EQ(type,Qdatum) ? T : Nil;
	if (temp);
	else
	    temp = member_type_specification_p(type) ? 
		    member_type_specifications_could_intersect_p(superior_type,
		    type) : Qnil;
	if (temp);
	else
	    temp = type_specification_subtype_in_kb_p(type,Qdatum) ? 
		    member_type_specification_intersects_datum_type_p(superior_type,
		    type) : Qnil;
    }
    else if (SYMBOLP(superior_type)) {
	if (SYMBOLP(type)) {
	    temp = symbolic_type_specification_subtype_p(type,superior_type);
	    if (temp);
	    else
		temp = symbolic_type_specification_subtype_p(superior_type,
			type);
	}
	else
	    temp = Nil;
	if (temp);
	else if (EQ(superior_type,Qitem_or_datum)) {
	    temp = class_type_specification_p(type);
	    if (temp);
	    else
		temp = aggregate_value_type_specification_p(type);
	}
	else
	    temp = Nil;
	if (temp);
	else
	    temp = EQ(superior_type,Qevaluation_value) && CONSP(type) ? 
		    evaluation_value_type_specification_p(type) : Qnil;
	if (temp);
	else
	    temp = EQ(superior_type,Qdatum) ? 
		    aggregate_value_type_specification_p(type) : Qnil;
    }
    else
	temp = Qnil;
    if (temp);
    else if (union_type_specification_p(type)) {
	subtype = Nil;
	ab_loop_list_ = M_CDR(type);
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	subtype = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = 
		type_specifications_could_intersect_in_kb_p_1(subtype,
		superior_type);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	temp = Qnil;
      end_3:;
    }
    else if (intersection_type_specification_p(type)) {
	subtype = Nil;
	ab_loop_list_ = M_CDR(type);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	subtype = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(type_specifications_could_intersect_in_kb_p_1(subtype,
		superior_type))) {
	    temp = Nil;
	    goto end_4;
	}
	goto next_loop_3;
      end_loop_3:
	temp = T;
	goto end_4;
	temp = Qnil;
      end_4:;
    }
    else if (negation_type_specification_p(type))
	temp =  !TRUEP(type_specification_subtype_in_kb_p(superior_type,
		M_CAR(M_CDR(type)))) ? T : Nil;
    else if (member_type_specification_p(type)) {
	temp = EQ(superior_type,Qitem_or_datum) ? T : Nil;
	if (temp);
	else
	    temp = EQ(superior_type,Qevaluation_value) ? T : Nil;
	if (temp);
	else
	    temp = EQ(superior_type,Qdatum) ? T : Nil;
	if (temp);
	else
	    temp = member_type_specification_p(superior_type) ? 
		    member_type_specifications_could_intersect_p(superior_type,
		    type) : Qnil;
	if (temp);
	else
	    temp = type_specification_subtype_in_kb_p(type,Qdatum) ? 
		    member_type_specification_intersects_datum_type_p(type,
		    superior_type) : Qnil;
    }
    else if (SYMBOLP(type)) {
	temp = EQ(type,Qitem_or_datum) ? 
		class_type_specification_p(superior_type) : Qnil;
	if (temp);
	else
	    temp = EQ(type,Qevaluation_value) && CONSP(superior_type) ? 
		    evaluation_value_type_specification_p(superior_type) : 
		    Qnil;
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* CLASS-TYPE-SPECIFICATIONS-COULD-INTERSECT-IN-KB-P */
Object class_type_specifications_could_intersect_in_kb_p(class1,class2)
    Object class1, class2;
{
    Object temp;

    x_note_fn_call(80,248);
    temp =  !TRUEP(type_specification_not_subtype_in_kb_p(class1,class2)) ?
	     T : Nil;
    if (temp);
    else
	temp =  !TRUEP(type_specification_not_subtype_in_kb_p(class2,
		class1)) ? T : Nil;
    return VALUES_1(temp);
}

static Object Qplace_reference;    /* place-reference */

static Object Qaction_cache;       /* action-cache */

static Object Qcolor_or_metacolor;  /* color-or-metacolor */

/* TYPE-SPECIFICATION-TYPE-P */
Object type_specification_type_p(thing,type)
    Object thing, type;
{
    Object temp, value, x2, gensymed_symbol, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, entry_hash;
    Object aggregate_type_name_of_value, aggregate_type_name, elt_1;
    Object ab_loop_list_, ab_loop_it_, gensymed_symbol_1, sub_class_bit_vector;
    Object union_type, intersection_type, function_symbol, type_name;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_2;
    Object result;

    x_note_fn_call(80,249);
    if (CONSP(thing) && EQ(M_CDR(thing),Qitem_reference))
	temp = type_specification_type_p(ISVREF(M_CAR(thing),(SI_Long)3L),
		type);
    else if (ATOM(type)) {
	if (EQ(type,Qnumber)) {
	    temp = FIXNUMP(thing) ? T : Nil;
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L ?
			 (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
			(SI_Long)1L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
			(SI_Long)1L ? T : Nil) : Qnil;
	}
	else if (EQ(type,Qinteger))
	    temp = FIXNUMP(thing) ? T : Nil;
	else if (EQ(type,Qlong))
	    temp = INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L 
		    ? T : Nil) : Qnil;
	else if (EQ(type,Qfloat))
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L 
		    ? T : Nil) : Qnil;
	else if (EQ(type,Qsymbol))
	    temp = thing ? (SYMBOLP(thing) ? T : Nil) : Qnil;
	else if (EQ(type,Qboolean)) {
	    if (CONSP(thing) && EQ(M_CDR(thing),Qtruth_value)) {
		value = M_CAR(thing);
		temp = EQ(value,Truth) ? T : Nil;
		if (temp);
		else
		    temp = EQ(value,Falsity) ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else if (EQ(type,Qtruth_value))
	    temp = CONSP(thing) ? (EQ(M_CDR(thing),Qtruth_value) ? T : 
		    Nil) : Qnil;
	else if (EQ(type,Qtext))
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ?
		     T : Nil;
	else if (EQ(type,Qitem_or_datum)) {
	    if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    temp = gensymed_symbol ? ISVREF(gensymed_symbol,(SI_Long)16L) :
		     Qnil;
	    if (temp);
	    else {
		gensymed_symbol = thing;
		temp = FIXNUMP(gensymed_symbol) ? T : Nil;
		if (temp);
		else
		    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L ? T : Nil) : Qnil;
		if (temp);
		else
		    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L ? T : Nil) : Qnil;
		if (temp);
		else
		    temp = gensymed_symbol ? (SYMBOLP(gensymed_symbol) ? T 
			    : Nil) : Qnil;
		if (temp);
		else
		    temp = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? T : Nil;
		if (temp);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp = EQ(gensymed_symbol,Qtruth_value) ? T : Nil;
		    if (temp);
		    else
			temp = memq_function(gensymed_symbol,
				Defined_evaluation_datum_types);
		}
		else
		    temp = Nil;
	    }
	}
	else if (EQ(type,Qdatum)) {
	    gensymed_symbol = thing;
	    temp = FIXNUMP(gensymed_symbol) ? T : Nil;
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = gensymed_symbol ? (SYMBOLP(gensymed_symbol) ? T : 
			Nil) : Qnil;
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L ? T : Nil;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value) ? T : Nil;
		if (temp);
		else
		    temp = memq_function(gensymed_symbol,
			    Defined_evaluation_datum_types);
	    }
	    else
		temp = Nil;
	}
	else if (EQ(type,Qevaluation_value)) {
	    gensymed_symbol = thing;
	    temp = FIXNUMP(gensymed_symbol) ? T : Nil;
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = gensymed_symbol ? (SYMBOLP(gensymed_symbol) ? T : 
			Nil) : Qnil;
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L ? T : Nil;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value) ? T : Nil;
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state) ? T : Nil;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		}
		else
		    temp = Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    else {
	temp = M_CAR(type);
	if (EQ(temp,Qsequence) || EQ(temp,Qab_structure)) {
	    if (CONSP(thing)) {
		aggregate_type_name_of_value = M_CDR(thing);
		aggregate_type_name = M_CAR(type);
		if (EQ(aggregate_type_name_of_value,aggregate_type_name)) {
		    temp =  !TRUEP(M_CDR(type)) ? T : Nil;
		    if (temp);
		    else
			temp = EQ(aggregate_type_name,Qab_structure) ? 
				detailed_evaluation_structure_type_p(thing,
				type) : 
				detailed_evaluation_sequence_type_p(thing,
				type);
		}
		else
		    temp = Nil;
	    }
	    else
		temp = Nil;
	}
	else if (EQ(temp,Qmember)) {
	    gensymed_symbol = thing;
	    temp_2 = FIXNUMP(gensymed_symbol);
	    if (temp_2);
	    else
		temp_2 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_2);
	    else
		temp_2 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_2);
	    else
		temp_2 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_2);
	    else
		temp_2 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_2);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_2 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_2);
		else
		    temp_2 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_2);
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
		  next_loop_3:
		    if (level < ab_loop_bind_)
			goto end_loop_3;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_4:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_5:
		    if ( !TRUEP(marked))
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
		    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		elt_1 = Nil;
		ab_loop_list_ = CDR(type);
		ab_loop_it_ = Nil;
	      next_loop_6:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_6;
		elt_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loop_it_ = evaluation_value_eql(2,elt_1,thing);
		if (ab_loop_it_) {
		    temp = ab_loop_it_;
		    goto end_3;
		}
		goto next_loop_6;
	      end_loop_6:
		temp = Qnil;
	      end_3:;
	    }
	    else
		temp = Nil;
	}
	else if (EQ(temp,Qab_class)) {
	    if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(M_CAR(M_CDR(type)),
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
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
	}
	else if (EQ(temp,Qab_or)) {
	    union_type = Nil;
	    ab_loop_list_ = M_CDR(type);
	    ab_loop_it_ = Nil;
	  next_loop_7:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_7;
	    union_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specification_type_p(thing,union_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_4;
	    }
	    goto next_loop_7;
	  end_loop_7:
	    temp = Qnil;
	  end_4:;
	}
	else if (EQ(temp,Qplace_reference) || EQ(temp,Qaction_cache) || 
		EQ(temp,Qobsolete_datum))
	    temp = CONSP(thing) ? (EQ(M_CAR(type),M_CDR(thing)) ? T : Nil) 
		    : Qnil;
	else if (EQ(temp,Qand)) {
	    intersection_type = Nil;
	    ab_loop_list_ = CDR(type);
	  next_loop_8:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_8;
	    intersection_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_type_p(thing,intersection_type))) {
		temp = Nil;
		goto end_5;
	    }
	    goto next_loop_8;
	  end_loop_8:
	    temp = T;
	    goto end_5;
	    temp = Qnil;
	  end_5:;
	}
	else if (EQ(temp,Qnot))
	    temp =  !TRUEP(type_specification_type_p(thing,
		    M_CAR(M_CDR(type)))) ? T : Nil;
	else if (EQ(temp,Qno_item))
	    temp =  !TRUEP(thing) ? T : Nil;
	else if (EQ(temp,Qno_item_implies_unknown))
	    temp = Nil;
	else if (EQ(temp,Qsatisfies)) {
	    function_symbol = M_CAR(M_CDR(type));
	    if (fboundp(function_symbol)) {
		temp = SYMBOL_FUNCTION(function_symbol);
		temp = FUNCALL_1(temp,thing);
	    }
	    else
		temp = Nil;
	}
	else if (EQ(temp,Qnamed)) {
	    temp = CADR(type);
	    if (SYMBOLP(temp) && EQ(CADR(type),Qcolor_or_metacolor))
		temp =  !EQ(color_or_metacolor_p(thing),Nil) ? T : Nil;
	    else {
		type_name = CADR(type);
		temp = get_property_value_function(3,
			get_symbol_properties_function(type_name),
			Qtype_specification_explicit_complex_type,Nil);
		if (temp);
		else
		    temp = get_property_value_function(3,
			    get_symbol_properties_function(type_name),
			    Qtype_specification_simple_expansion,Nil);
		temp = type_specification_type_p(thing,temp);
	    }
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-SUBTYPE-IN-KB-P */
Object type_specification_subtype_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object temp, subtype, ab_loop_list_, intersection_type, ab_loop_it_;
    Object superior_class, class_1, gensymed_symbol, union_type;

    x_note_fn_call(80,250);
    temp = EQUAL(type,superior_type) ? T : Nil;
    if (temp);
    else if (union_type_specification_p(type)) {
	subtype = Nil;
	ab_loop_list_ = CDR(type);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subtype = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(type_specification_subtype_in_kb_p(subtype,
		    superior_type))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else if (difference_type_specification_in_kb_p(type))
	temp = type_specification_subtype_in_kb_p(M_CAR(M_CDR(type)),
		superior_type);
    else if (intersection_type_specification_p(type)) {
	intersection_type = Nil;
	ab_loop_list_ = CDR(type);
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	intersection_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = type_specification_subtype_in_kb_p(intersection_type,
		superior_type);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_2:;
    }
    else if (negation_type_specification_p(type))
	temp = negation_type_specification_p(superior_type) ? 
		type_specification_subtype_in_kb_p(SECOND(superior_type),
		SECOND(type)) : Qnil;
    else
	temp = Qnil;
    if (temp);
    else if (SYMBOLP(superior_type)) {
	temp = SYMBOLP(type) ? symbolic_type_specification_subtype_p(type,
		superior_type) : Qnil;
	if (temp);
	else
	    temp = member_type_specification_p(type) ? 
		    member_type_specification_subtype_of_symbolic_type_p(type,
		    superior_type) : Qnil;
	if (temp);
	else if (EQ(superior_type,Qitem_or_datum)) {
	    temp = class_type_specification_p(type);
	    if (temp);
	    else
		temp = aggregate_value_type_specification_p(type);
	}
	else
	    temp = Nil;
	if (temp);
	else
	    temp = EQ(superior_type,Qdatum) ? 
		    aggregate_value_type_specification_p(type) : Qnil;
	if (temp);
	else
	    temp = EQ(superior_type,Qevaluation_value) && CONSP(type) ? 
		    evaluation_value_type_specification_p(type) : Qnil;
    }
    else if (aggregate_value_type_specification_p(superior_type)) {
	if (aggregate_value_type_specification_p(type)) {
	    temp = CONSP(type) && EQ(M_CAR(type),Qab_structure) && 
		    CONSP(superior_type) && EQ(M_CAR(superior_type),
		    Qab_structure) ? 
		    structure_type_specification_subtype_in_kb_p(type,
		    superior_type) : Qnil;
	    if (temp);
	    else
		temp = fast_sequence_type_specification_p(type) && 
			fast_sequence_type_specification_p(superior_type) ?
			 sequence_type_specification_subtype_in_kb_p(type,
			superior_type) : Qnil;
	}
	else
	    temp = Nil;
    }
    else if (member_type_specification_p(superior_type))
	temp = member_type_specification_p(type) ? 
		member_type_specification_subtype_p(type,superior_type) : Qnil;
    else if (class_type_specification_p(superior_type)) {
	superior_class = M_CAR(M_CDR(superior_type));
	if (class_type_specification_p(type)) {
	    class_1 = M_CAR(M_CDR(type));
	    temp = EQ(superior_class,Qitem) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(superior_class,class_1) ? T : Nil;
	    if (temp);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_1,
			Class_description_gkbprop);
		temp =  ! !(gensymed_symbol ? 
			TRUEP(memq_function(superior_class,
			ISVREF(gensymed_symbol,(SI_Long)2L))) : 
			TRUEP(Nil)) ? T : Nil;
	    }
	}
	else
	    temp = Nil;
    }
    else if (union_type_specification_p(superior_type)) {
	union_type = Nil;
	ab_loop_list_ = CDR(superior_type);
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	union_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = type_specification_subtype_in_kb_p(type,union_type);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	temp = Qnil;
      end_3:;
    }
    else if (intersection_type_specification_p(superior_type)) {
	intersection_type = Nil;
	ab_loop_list_ = CDR(superior_type);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	intersection_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(type_specification_subtype_in_kb_p(type,
		intersection_type))) {
	    temp = Nil;
	    goto end_4;
	}
	goto next_loop_3;
      end_loop_3:
	temp = T;
	goto end_4;
	temp = Qnil;
      end_4:;
    }
    else if (negation_type_specification_p(superior_type))
	temp =  !TRUEP(type_specifications_could_intersect_in_kb_p(type,
		SECOND(superior_type))) ? T : Nil;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-NOT-SUBTYPE-IN-KB-P */
Object type_specification_not_subtype_in_kb_p(type,superior_type)
    Object type, superior_type;
{
    Object intersection_type, ab_loop_list_, ab_loop_it_, temp, subtype;
    Object superior_class, inferior_class, gensymed_symbol;
    char temp_1;

    x_note_fn_call(80,251);
    if ( !EQUAL(type,superior_type)) {
	if (intersection_type_specification_p(superior_type)) {
	    intersection_type = Nil;
	    ab_loop_list_ = CDR(superior_type);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    intersection_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specification_not_subtype_in_kb_p(type,
		    intersection_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	}
	else if (union_type_specification_p(superior_type)) {
	    subtype = Nil;
	    ab_loop_list_ = CDR(superior_type);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_not_subtype_in_kb_p(type,
			subtype))) {
		temp = Nil;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = T;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	}
	else if (negation_type_specification_p(superior_type)) {
	    temp = type_specification_subtype_in_kb_p(type,
		    SECOND(superior_type));
	    if (temp);
	    else
		temp = 
			type_specification_subtype_in_kb_p(SECOND(superior_type),
			type);
	}
	else
	    temp = Qnil;
	if (temp);
	else if (difference_type_specification_in_kb_p(type))
	    temp = 
		    type_specification_not_subtype_in_kb_p(M_CAR(M_CDR(type)),
		    superior_type);
	else if (intersection_type_specification_p(type)) {
	    intersection_type = Nil;
	    ab_loop_list_ = CDR(type);
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    intersection_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = 
		    type_specification_not_subtype_in_kb_p(intersection_type,
		    superior_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_3;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = Qnil;
	  end_3:;
	}
	else if (union_type_specification_p(type)) {
	    subtype = Nil;
	    ab_loop_list_ = CDR(type);
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_not_subtype_in_kb_p(subtype,
		    superior_type))) {
		temp = Nil;
		goto end_4;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    temp = T;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
	else if (negation_type_specification_p(type)) {
	    temp = type_specification_subtype_in_kb_p(SECOND(type),
		    superior_type);
	    if (temp);
	    else
		temp = type_specification_subtype_in_kb_p(superior_type,
			SECOND(type));
	}
	else
	    temp = Qnil;
	if (temp);
	else if (filtered_type_specification_p(superior_type) || 
		filtered_type_specification_p(type) || 
		intersection_type_specification_p(type) || 
		union_type_specification_p(type) || 
		negation_type_specification_p(type))
	    temp = Nil;
	else if (SYMBOLP(superior_type)) {
	    if (SYMBOLP(type))
		temp =  !TRUEP(symbolic_type_specification_subtype_p(type,
			superior_type)) ? T : Nil;
	    else if (aggregate_value_type_specification_p(type))
		temp =  !(EQ(superior_type,Qdatum) || EQ(superior_type,
			Qitem_or_datum) || EQ(superior_type,
			Qevaluation_value)) ? T : Nil;
	    else if (member_type_specification_p(type))
		temp = 
			member_type_specification_not_subtype_of_symbolic_type_p(type,
			superior_type);
	    else {
		temp =  !TRUEP(class_type_specification_p(type)) ? T : Nil;
		if (temp);
		else
		    temp = EQ(superior_type,Qevaluation_value) ? ( 
			    !TRUEP(type_specification_subtype_in_kb_p(type,
			    superior_type)) ? T : Nil) :  
			    !EQ(superior_type,Qitem_or_datum) ? T : Nil;
	    }
	}
	else if (member_type_specification_p(superior_type))
	    temp = member_type_specification_p(type) ? 
		    member_type_specification_not_subtype_p(type,
		    superior_type) : T;
	else if (aggregate_value_type_specification_p(superior_type)) {
	    if (aggregate_value_type_specification_p(type)) {
		if (CONSP(type) && EQ(M_CAR(type),Qab_structure) && 
			CONSP(superior_type) && EQ(M_CAR(superior_type),
			Qab_structure))
		    temp = 
			    structure_type_specification_not_subtype_in_kb_p(type,
			    superior_type);
		else if (fast_sequence_type_specification_p(type) && 
			fast_sequence_type_specification_p(superior_type))
		    temp = 
			    sequence_type_specification_not_subtype_in_kb_p(type,
			    superior_type);
		else
		    temp = T;
	    }
	    else
		temp = T;
	}
	else if (evaluation_value_type_specification_p(superior_type) || 
		unknown_type_specification_p(superior_type) || 
		no_item_type_specification_p(superior_type) || 
		no_item_implies_unknown_type_specification_p(superior_type))
	    temp =  !TRUEP(type_specification_subtype_in_kb_p(type,
		    superior_type)) ? T : Nil;
	else if (class_type_specification_p(superior_type)) {
	    temp =  !TRUEP(class_type_specification_p(type)) ? T : Nil;
	    if (temp);
	    else {
		superior_class = M_CAR(M_CDR(superior_type));
		inferior_class = M_CAR(M_CDR(type));
		if (EQ(inferior_class,superior_class))
		    temp = Nil;
		else {
		    if (lookup_global_or_kb_specific_property_value(superior_class,
			    Class_description_gkbprop)) {
			temp = 
				lookup_global_or_kb_specific_property_value(superior_class,
				Class_definition_gkbprop);
			temp_1 = CONSP(temp);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			if (lookup_global_or_kb_specific_property_value(inferior_class,
				Class_description_gkbprop)) {
			    temp = 
				    lookup_global_or_kb_specific_property_value(inferior_class,
				    Class_definition_gkbprop);
			    temp_1 = CONSP(temp);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(inferior_class,
				Class_description_gkbprop);
			temp =  !(gensymed_symbol ? 
				TRUEP(memq_function(superior_class,
				ISVREF(gensymed_symbol,(SI_Long)2L))) : 
				TRUEP(Nil)) ? T : Nil;
		    }
		    else
			temp = Nil;
		}
	    }
	}
	else
	    temp = Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

/* CLASS-IN-ATTRIBUTE-CONFORMS-TO-TYPE-P */
Object class_in_attribute_conforms_to_type_p varargs_1(int, n)
{
    Object slot_description, class_1;
    Object suppress_warning_messages_qm, slot_init_form_of_override_qm;
    Object slot_type_specification, type_specification_class;
    Object class_for_instantiation, temp, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_1, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(80,252);
    INIT_ARGS_nonrelocating();
    slot_description = REQUIRED_ARG_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    suppress_warning_messages_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_init_form_of_override_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    slot_type_specification = ISVREF(slot_description,(SI_Long)5L);
    if (class_type_specification_p(slot_type_specification)) {
	type_specification_class = 
		type_specification_class_function(slot_type_specification);
	if (slot_init_form_of_override_qm)
	    class_for_instantiation = THIRD(slot_init_form_of_override_qm);
	else {
	    temp = ISVREF(slot_description,(SI_Long)6L);
	    class_for_instantiation = THIRD(temp);
	}
	if (SYMBOLP(class_for_instantiation)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_for_instantiation;
	    key_hash_value = SXHASH_SYMBOL_1(class_for_instantiation) & 
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
		gensymed_symbol = class_for_instantiation;
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
	if ( !temp_2) {
	    if ( !TRUEP(suppress_warning_messages_qm))
		class_instantiation_warning_not_defined(class_for_instantiation,
			slot_description,class_1);
	    return VALUES_1(Nil);
	}
	else {
	    if (SYMBOLP(type_specification_class)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = type_specification_class;
		key_hash_value = SXHASH_SYMBOL_1(type_specification_class) 
			& IFIX(Most_positive_fixnum);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_14:
		if ( !TRUEP(marked))
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		    gensymed_symbol = type_specification_class;
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
	      next_loop_15:
		if (level < ab_loop_bind_)
		    goto end_loop_15;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_16:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_17:
		if ( !TRUEP(marked))
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_20:
		    if ( !TRUEP(marked))
			goto end_loop_19;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_23:
		    if ( !TRUEP(marked))
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
		temp_2 = TRUEP(resulting_value);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_for_instantiation,
			Class_description_gkbprop);
		if (gensymed_symbol ? 
			TRUEP(memq_function(type_specification_class,
			ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil))
		    return VALUES_1(T);
		else {
		    if ( !TRUEP(suppress_warning_messages_qm))
			class_instantiation_warning_incompatible_class(class_for_instantiation,
				slot_description,class_1,
				type_specification_class);
		    return VALUES_1(Nil);
		}
	    }
	    else {
		if ( !TRUEP(suppress_warning_messages_qm))
		    class_instantiation_warning_undefined_type_specification_class(class_for_instantiation,
			    slot_description,class_1,type_specification_class);
		return VALUES_1(Nil);
	    }
	}
    }
    else
	return VALUES_1(T);
}

DEFINE_VARIABLE_WITH_SYMBOL(Internal_g2_element_types_that_can_contain_datum, Qinternal_g2_element_types_that_can_contain_datum);

DEFINE_VARIABLE_WITH_SYMBOL(G2_element_types_that_can_contain_datum, Qg2_element_types_that_can_contain_datum);

/* CATEGORY-IS-NOT-G2-ELEMENT-DATUM-TYPE */
Object category_is_not_g2_element_datum_type(category_symbol)
    Object category_symbol;
{
    x_note_fn_call(80,253);
    if ( !TRUEP(memq_function(category_symbol,
	    G2_element_types_that_can_contain_datum)))
	return VALUES_1(category_symbol);
    else
	return VALUES_1(Bad_phrase);
}

/* NON-NEGATIVE-FIXNUM-P */
Object non_negative_fixnum_p(x)
    Object x;
{
    x_note_fn_call(80,254);
    if (FIXNUMP(x))
	return VALUES_1(IFIX(x) >= (SI_Long)0L ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object Qdefined_evaluation_type_writer;  /* defined-evaluation-type-writer */

/* WRITE-EVALUATION-VALUE */
Object write_evaluation_value varargs_1(int, n)
{
    Object evaluation_value;
    Object beautifully_qm, possible_type_name, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(80,255);
    INIT_ARGS_nonrelocating();
    evaluation_value = REQUIRED_ARG_nonrelocating();
    beautifully_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(evaluation_value))
	return twrite_beginning_of_wide_string(array_constant_6,
		FIX((SI_Long)4L));
    else if (FIXNUMP(evaluation_value))
	return print_constant(3,evaluation_value,Qnumber,beautifully_qm);
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    result = print_constant(3,aref1(evaluation_value,
		    FIX((SI_Long)0L)),Qnumber,beautifully_qm);
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    result = print_constant(3,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_value,
		    (SI_Long)0L)),Qnumber,beautifully_qm);
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qtruth_value))
	return print_constant(3,M_CAR(evaluation_value),Qtruth_value,
		beautifully_qm);
    else if (evaluation_value && SYMBOLP(evaluation_value))
	return print_constant(3,evaluation_value,Qsymbol,beautifully_qm);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value) != (SI_Long)0L)
	return print_constant(3,evaluation_value,Qtext,beautifully_qm);
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qiteration_state))
	return twrite_beginning_of_wide_string(array_constant_7,
		FIX((SI_Long)18L));
    else {
	if (CONSP(evaluation_value)) {
	    possible_type_name = M_CDR(evaluation_value);
	    if (SYMBOLP(possible_type_name)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = possible_type_name;
		key_hash_value = SXHASH_SYMBOL_1(possible_type_name) & 
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    gensymed_symbol = get_property_value_function(3,
		    get_symbol_properties_function(M_CDR(evaluation_value)),
		    Qdefined_evaluation_type_writer,Nil);
	    gensymed_symbol_1 = evaluation_value;
	    return VALUES_1(inline_funcall_1(gensymed_symbol,
		    gensymed_symbol_1));
	}
	else
	    return VALUES_1(Nil);
    }
}

/* WRITE-BLOCK-OR-EVALUATION-VALUE */
Object write_block_or_evaluation_value varargs_1(int, n)
{
    Object block_or_evaluation_value;
    Object beautifully_qm, x2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(80,256);
    INIT_ARGS_nonrelocating();
    block_or_evaluation_value = REQUIRED_ARG_nonrelocating();
    beautifully_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SIMPLE_VECTOR_P(block_or_evaluation_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_evaluation_value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(block_or_evaluation_value,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(block_or_evaluation_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return write_evaluation_value(2,block_or_evaluation_value,
		beautifully_qm);
    else if (In_text_for_item_or_value_p)
	return twrite_designation_for_item(block_or_evaluation_value);
    else
	return twrite(get_or_make_up_designation_for_block(block_or_evaluation_value));
}

Object Star_singular_of_numeric_data_type_star_kbprop = UNBOUND;

static Object array_constant_8;    /* # */

static Object Qseconds;            /* seconds */

static Object Qtime_stamp;         /* time-stamp */

static Object array_constant_9;    /* # */

static Object Qcm;                 /* \, */

static Object string_constant_9;   /* "none" */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object string_constant_10;  /* "-." */

static Object string_constant_11;  /* "." */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

static Object string_constant_12;  /* "" */

static Object string_constant_13;  /* "~a..." */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object Qf;                  /* f */

static Object array_constant_18;   /* # */

static Object Qc;                  /* c */

static Object array_constant_19;   /* # */

static Object list_constant_6;     /* # */

static Object Qwide_string;        /* wide-string */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

/* PRINT-CONSTANT */
Object print_constant varargs_1(int, n)
{
    Object constant_value, constant_type;
    Object beautifully_qm, subsecond_qm, temp_1, second_1, minute, hour, date;
    Object month, year, write_symbols_parsably_qm, length_of_string;
    Object small_g2_text, write_strings_parsably_qm, value_to_print, temp_3;
    Object schar_arg_2, schar_new_value, write_symbols_in_lower_case_qm;
    SI_Long minimum_string_length, length_1, thing;
    char temp_2, negative_qm;
    double unix_time, temp, seconds_remainder, arg, arg_1;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(80,257);
    INIT_ARGS_nonrelocating();
    constant_value = REQUIRED_ARG_nonrelocating();
    constant_type = REQUIRED_ARG_nonrelocating();
    beautifully_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(constant_type))
	return twrite_beginning_of_wide_string(array_constant_8,
		FIX((SI_Long)8L));
    else if (EQ(constant_type,Qseconds))
	return print_relative_time(constant_value);
    else if (EQ(constant_type,Qtime_stamp)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    subsecond_qm = Nil;
	    if (FIXNUMP(constant_value))
		unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) 
			+ (double)IFIX(constant_value);
	    else if (FLOATP(constant_value)) {
		subsecond_qm = T;
		temp = DOUBLE_FLOAT_TO_DOUBLE(constant_value);
		unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) 
			+ temp;
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(constant_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant_value)) == 
		    (SI_Long)1L) {
		subsecond_qm = T;
		unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) 
			+ DFLOAT_ISAREF_1(constant_value,(SI_Long)0L);
	    }
	    else if (INTEGERP(constant_value)) {
		temp_1 = lfloat(constant_value,float_constant);
		temp = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
		unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) 
			+ temp;
	    }
	    else
		unix_time = 0.0;
	    seconds_remainder = subsecond_qm ? unix_time - 
		    inline_ffloor_1(unix_time) : 0.0;
	    arg = unix_time;
	    arg_1 = -2.147483648E+9;
	    temp_2 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp_2);
	    else {
		arg = unix_time;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(N_2_to_31_plus_62_years);
		temp_2 = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) 
			?  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp_2)
		result = twrite_beginning_of_wide_string(array_constant_9,
			FIX((SI_Long)26L));
	    else {
		result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(unix_time));
		MVS_6(result,second_1,minute,hour,date,month,year);
		result = print_decoded_time(subsecond_qm ? 
			DOUBLE_TO_DOUBLE_FLOAT(seconds_remainder + 
			(double)IFIX(second_1)) : second_1,minute,hour,
			date,month,year);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (EQ(constant_type,Qsymbol)) {
	write_symbols_parsably_qm =  !TRUEP(beautifully_qm) ? T : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		0);
	  if (constant_value && ATOM(constant_value))
	      result = twrite(constant_value);
	  else
	      result = write_symbol_list(4,constant_value,Qcm,Qand,
		      string_constant_9);
	POP_SPECIAL();
	return result;
    }
    else if (EQ(constant_type,Qtruth_value)) {
	if (IFIX(constant_value) == (SI_Long)1000L)
	    return twrite_beginning_of_wide_string(array_constant_10,
		    FIX((SI_Long)4L));
	else if (IFIX(constant_value) == (SI_Long)-1000L)
	    return twrite_beginning_of_wide_string(array_constant_11,
		    FIX((SI_Long)5L));
	else {
	    negative_qm = IFIX(constant_value) < (SI_Long)0L;
	    twrite(negative_qm ? string_constant_10 : string_constant_11);
	    if (negative_qm)
		constant_value = FIXNUM_NEGATE(constant_value);
	    if (IFIX(constant_value) < (SI_Long)10L)
		twrite_beginning_of_wide_string(array_constant_12,
			FIX((SI_Long)2L));
	    else if (IFIX(constant_value) < (SI_Long)100L)
		twrite_beginning_of_wide_string(array_constant_13,
			FIX((SI_Long)1L));
	    twrite_positive_fixnum(constant_value);
	    return twrite_beginning_of_wide_string(array_constant_14,
		    FIX((SI_Long)5L));
	}
    }
    else if (EQ(constant_type,Qtext)) {
	minimum_string_length = (SI_Long)10L;
	length_of_string = lengthw(constant_value);
	if (Evaluation_value_writing_target_length_qm) {
	    temp_1 = FIXNUM_ADD(length_of_string,
		    twriting_accumulated_length());
	    temp_2 = FIXNUM_GT(temp_1,
		    Evaluation_value_writing_target_length_qm);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? IFIX(length_of_string) > minimum_string_length : 
		TRUEP(Nil)) {
	    if (In_text_for_item_or_value_p) {
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(constant_value) != 
			(SI_Long)0L) {
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant_value));
		    temp_2 = (SI_Long)1L == 
			    UBYTE_16_ISAREF_1(constant_value,
			    UBYTE_16_ISAREF_1(constant_value,length_1 - 
			    (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(constant_value,length_1 - 
			    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    small_g2_text = temp_2 ? copy_text_string(string_constant_12) :
		     copy_partial_wide_string(constant_value,
		    FIX(minimum_string_length));
	    write_strings_parsably_qm =  !TRUEP(beautifully_qm) ? T : Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      tformat(2,string_constant_13,small_g2_text);
	      result = reclaim_text_string(small_g2_text);
	    POP_SPECIAL();
	    return result;
	}
	else {
	    if (In_text_for_item_or_value_p) {
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(constant_value) != 
			(SI_Long)0L) {
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant_value));
		    temp_2 = (SI_Long)1L == 
			    UBYTE_16_ISAREF_1(constant_value,
			    UBYTE_16_ISAREF_1(constant_value,length_1 - 
			    (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(constant_value,length_1 - 
			    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		write_strings_parsably_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
			0);
		  twrite_beginning_of_wide_string(array_constant_15,
			  FIX((SI_Long)19L));
		  twrite_binary_string_printed_representation(constant_value);
		  result = twrite_beginning_of_wide_string(array_constant_16,
			  FIX((SI_Long)1L));
		POP_SPECIAL();
		return result;
	    }
	    else {
		write_strings_parsably_qm =  !TRUEP(beautifully_qm) ? T : Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
			0);
		  result = twrite_general_string(constant_value);
		POP_SPECIAL();
		return result;
	    }
	}
    }
    else if (EQ(constant_type,Qnumber) || EQ(constant_type,Qinteger) || 
	    EQ(constant_type,Qfloat) || EQ(constant_type,Qlong) || 
	    lookup_global_or_kb_specific_property_value(constant_type,
	    Numeric_data_type_gkbprop)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(constant_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant_value)) == 
		    (SI_Long)1L)
		value_to_print = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(constant_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(constant_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant_value)) == 
		    (SI_Long)1L)
		value_to_print = aref1(constant_value,FIX((SI_Long)0L));
	    else
		value_to_print = constant_value;
	    twrite(value_to_print);
	    if (EQ(constant_type,Qlong))
		twrite_beginning_of_wide_string(array_constant_17,
			FIX((SI_Long)1L));
	    if (EQ(constant_type,Qf))
		result = twrite_beginning_of_wide_string(array_constant_18,
			FIX((SI_Long)2L));
	    else if (EQ(constant_type,Qc))
		result = twrite_beginning_of_wide_string(array_constant_19,
			FIX((SI_Long)2L));
	    else {
		temp_1 = memq_function(constant_type,list_constant_6);
		if (temp_1)
		    result = VALUES_1(temp_1);
		else {
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
			temp_3 = Current_gensym_string;
			schar_arg_2 = Fill_pointer_for_current_gensym_string;
			thing = (SI_Long)32L;
			schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) 
				? CHAR_CODE(FIX(thing)) : FIX(thing));
			SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
			temp_3 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_3;
		    }
		    write_symbols_in_lower_case_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    1);
		      write_symbols_parsably_qm =  !TRUEP(beautifully_qm) ?
			       T : Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			      0);
			temp_1 = FIXNUMP(value_to_print) && 
				IFIX(value_to_print) == (SI_Long)1L ? 
				lookup_kb_specific_property_value(constant_type,
				Star_singular_of_numeric_data_type_star_kbprop) 
				: Nil;
			if (temp_1);
			else
			    temp_1 = constant_type;
			result = twrite(temp_1);
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else {
	temp_1 =  !TRUEP(valid_type_specification_p(constant_type)) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else if (type_specification_subtype_in_kb_p(constant_type,
		list_constant_7))
	    return write_evaluation_sequence(constant_value);
	else if (type_specification_subtype_in_kb_p(constant_type,
		list_constant_8))
	    return write_evaluation_structure(constant_value);
	else
	    return VALUES_1(Qnil);
    }
}

static Object array_constant_20;   /* # */

static Object array_constant_21;   /* # */

static Object array_constant_22;   /* # */

static Object string_constant_14;  /* "a thing which satisfies the predicate ~a" */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

static Object array_constant_27;   /* # */

static Object array_constant_28;   /* # */

static Object string_constant_15;  /* "~NV, " */

static Object string_constant_16;  /* "~NV, or " */

static Object string_constant_17;  /* "~NV or " */

static Object string_constant_18;  /* "~NV" */

/* WRITE-TYPE-SPECIFICATION */
Object write_type_specification(type_specification)
    Object type_specification;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object type, defined_types, ab_loopvar_, ab_loopvar__1;
    Object ab_less_than_branch_qm_, possible_type_name, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object more_than_two_p, elt_tail, elt_1, type_name;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(80,258);
    if (SYMBOLP(type_specification)) {
	if (EQ(type_specification,Qitem_or_datum))
	    twrite_beginning_of_wide_string(array_constant_20,
		    FIX((SI_Long)13L));
	else if (EQ(type_specification,Qdatum))
	    twrite_beginning_of_wide_string(array_constant_21,
		    FIX((SI_Long)5L));
	else if (EQ(type_specification,Qevaluation_value)) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = Defined_evaluation_value_types;
	    ab_binary_tree_form_ = Defined_evaluation_value_types;
	    gensymed_symbol = CDR(Defined_evaluation_value_types);
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
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    type = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      defined_types = Nil;
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
	    next_loop:
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
		    next_loop_1:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_1;
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
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_1;
	      type = M_CDR(ab_entry_cons_);
	      ab_loopvar__1 = eval_cons_1(get_property_value_function(3,
		      get_symbol_properties_function(type),
		      Qtype_specification_of_defined_evaluation_type,Nil),Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  defined_types = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	      goto next_loop;
	    end_loop_1:
	      defined_types = nconc2(eval_list_2(Qdatum,list_constant_3),
		      defined_types);
	      write_combined_type_specification(Qab_or,defined_types);
	      reclaim_eval_list_1(defined_types);
	    POP_SPECIAL();
	}
	else
	    twrite_data_type(type_specification);
    }
    else if (union_type_specification_p(type_specification) || 
	    intersection_type_specification_p(type_specification))
	write_combined_type_specification(CAR(type_specification),
		CDR(type_specification));
    else if (negation_type_specification_p(type_specification)) {
	twrite_beginning_of_wide_string(array_constant_22,FIX((SI_Long)16L));
	write_type_specification(SECOND(type_specification));
    }
    else if (filtered_type_specification_p(type_specification))
	tformat(2,string_constant_14,SECOND(type_specification));
    else if (iteration_state_type_specification_p(type_specification))
	twrite_beginning_of_wide_string(array_constant_23,FIX((SI_Long)15L));
    else if (unknown_type_specification_p(type_specification))
	twrite_beginning_of_wide_string(array_constant_24,FIX((SI_Long)7L));
    else if (no_item_type_specification_p(type_specification))
	twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)4L));
    else if (no_item_implies_unknown_type_specification_p(type_specification))
	twrite_beginning_of_wide_string(array_constant_25,FIX((SI_Long)35L));
    else if (class_type_specification_p(type_specification)) {
	twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)6L));
	twrite_symbol(1,M_CAR(M_CDR(type_specification)));
    }
    else if (aggregate_value_type_specification_p(type_specification)) {
	if (CONSP(type_specification) && EQ(M_CAR(type_specification),
		Qab_structure))
	    write_structure_type_specification(type_specification);
	else
	    write_sequence_type_specification(type_specification);
    }
    else {
	if (evaluation_value_type_specification_p(type_specification) && 
		CONSP(type_specification)) {
	    possible_type_name = M_CAR(type_specification);
	    if (SYMBOLP(possible_type_name)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = possible_type_name;
		key_hash_value = SXHASH_SYMBOL_1(possible_type_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_2:
		if (level < ab_loop_bind_)
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_3:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_4:
		if ( !TRUEP(marked))
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_4;
	      end_loop_3:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_1;
		goto next_loop_3;
	      end_loop_4:
	      end_1:
		level = level - (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
		temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (EQ(M_CAR(type_specification),Qplace_reference))
		twrite_beginning_of_wide_string(array_constant_27,
			FIX((SI_Long)64L));
	    else
		twrite_symbol(1,CAR(type_specification));
	}
	else if (member_type_specification_p(type_specification)) {
	    twrite_beginning_of_wide_string(array_constant_28,
		    FIX((SI_Long)7L));
	    temp = CDR(type_specification);
	    more_than_two_p = CDDR(temp);
	    elt_tail = CDR(type_specification);
	    elt_1 = Nil;
	  next_loop_5:
	    if ( !TRUEP(elt_tail))
		goto end_loop_5;
	    elt_1 = CAR(elt_tail);
	    if (CDDR(elt_tail))
		tformat(2,string_constant_15,elt_1);
	    else if (CDR(elt_tail)) {
		if (more_than_two_p)
		    tformat(2,string_constant_16,elt_1);
		else
		    tformat(2,string_constant_17,elt_1);
	    }
	    else
		tformat(2,string_constant_18,elt_1);
	    elt_tail = M_CDR(elt_tail);
	    goto next_loop_5;
	  end_loop_5:;
	}
	else if (named_type_specification_p(type_specification)) {
	    type_name = CADR(type_specification);
	    temp = get_property_value_function(3,
		    get_symbol_properties_function(type_name),
		    Qtype_specification_explicit_complex_type,Nil);
	    if (temp);
	    else
		temp = get_property_value_function(3,
			get_symbol_properties_function(type_name),
			Qtype_specification_simple_expansion,Nil);
	    write_type_specification(temp);
	}
	else
	    twrite(type_specification);
    }
    return VALUES_1(Nil);
}

static Object array_constant_29;   /* # */

static Object string_constant_19;  /* " with at least ~D, and less than ~D elements of type " */

static Object string_constant_20;  /* " with at least ~D element~a of type " */

static Object string_constant_21;  /* "s" */

static Object string_constant_22;  /* " with elements of type " */

/* WRITE-SEQUENCE-TYPE-SPECIFICATION */
Object write_sequence_type_specification(type_specification)
    Object type_specification;
{
    Object low_bound_qm, high_bound_qm, temp;

    x_note_fn_call(80,259);
    twrite_beginning_of_wide_string(array_constant_29,FIX((SI_Long)8L));
    if (M_CDR(type_specification)) {
	low_bound_qm = CADDR(type_specification);
	high_bound_qm = low_bound_qm ? CADDDR(type_specification) : Qnil;
	if (high_bound_qm)
	    tformat(3,string_constant_19,low_bound_qm,high_bound_qm);
	else if (low_bound_qm)
	    tformat(3,string_constant_20,low_bound_qm,IFIX(low_bound_qm) 
		    != (SI_Long)1L ? string_constant_21 : string_constant_12);
	else
	    tformat(1,string_constant_22);
	temp = write_type_specification(CADR(type_specification));
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object array_constant_30;   /* # */

static Object array_constant_31;   /* # */

static Object string_constant_23;  /* "~(~a~): ~NT" */

static Object array_constant_32;   /* # */

static Object array_constant_33;   /* # */

static Object array_constant_34;   /* # */

static Object array_constant_35;   /* # */

/* WRITE-STRUCTURE-TYPE-SPECIFICATION */
Object write_structure_type_specification(type_specification)
    Object type_specification;
{
    Object tail, slot_name, slot_type_specification, ab_loop_list_, temp;
    Object minimum_contents_qm;

    x_note_fn_call(80,260);
    twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)9L));
    if (M_CDR(type_specification)) {
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)19L));
	tail = M_CAR(M_CDR(type_specification));
	slot_name = Nil;
	slot_type_specification = Nil;
	ab_loop_list_ = tail;
      next_loop:
	if ( !TRUEP(tail))
	    goto end_loop;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	temp = CAR(ab_loop_list_);
	slot_name = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	slot_type_specification = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	tformat(3,string_constant_23,slot_name,slot_type_specification);
	if (CDDR(tail))
	    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
	else if (CDR(tail))
	    twrite_beginning_of_wide_string(array_constant_32,
		    FIX((SI_Long)6L));
	tail = M_CDR(tail);
	goto next_loop;
      end_loop:;
	twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)1L));
	minimum_contents_qm = CADDR(type_specification);
	if (minimum_contents_qm) {
	    twrite_beginning_of_wide_string(array_constant_34,
		    FIX((SI_Long)8L));
	    twrite_minimum_structure_contents(minimum_contents_qm,T);
	    temp = twrite_beginning_of_wide_string(array_constant_35,
		    FIX((SI_Long)16L));
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object array_constant_36;   /* # */

static Object string_constant_24;  /* " ~a " */

static Object array_constant_37;   /* # */

/* TWRITE-MINIMUM-STRUCTURE-CONTENTS */
Object twrite_minimum_structure_contents(boolean_expression,top_level_p)
    Object boolean_expression, top_level_p;
{
    Object operator_1, temp, sub_expression, ab_loop_list_;

    x_note_fn_call(80,261);
    if (CONSP(boolean_expression)) {
	operator_1 = M_CAR(boolean_expression);
	if (EQ(operator_1,Qand) || EQ(operator_1,Qab_or)) {
	    if ( !TRUEP(CDDR(boolean_expression)))
		temp = 
			twrite_minimum_structure_contents(CADR(boolean_expression),
			top_level_p);
	    else {
		if ( !TRUEP(top_level_p))
		    twrite_beginning_of_wide_string(array_constant_36,
			    FIX((SI_Long)1L));
		twrite_minimum_structure_contents(CADR(boolean_expression),
			Nil);
		sub_expression = Nil;
		ab_loop_list_ = CDDR(boolean_expression);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		sub_expression = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		tformat(2,string_constant_24,operator_1);
		twrite_minimum_structure_contents(sub_expression,Nil);
		goto next_loop;
	      end_loop:;
		temp =  !TRUEP(top_level_p) ? 
			twrite_beginning_of_wide_string(array_constant_33,
			FIX((SI_Long)1L)) : Nil;
	    }
	}
	else if (EQ(operator_1,Qnot)) {
	    twrite_beginning_of_wide_string(array_constant_37,
		    FIX((SI_Long)4L));
	    temp = 
		    twrite_minimum_structure_contents(CADR(boolean_expression),
		    Nil);
	}
	else
	    temp = Qnil;
    }
    else if (boolean_expression)
	temp = twrite_symbol(1,boolean_expression);
    else
	temp = Qnil;
    return VALUES_1(temp);
}

static Object array_constant_38;   /* # */

static Object array_constant_39;   /* # */

static Object array_constant_40;   /* # */

static Object array_constant_41;   /* # */

static Object array_constant_42;   /* # */

static Object array_constant_43;   /* # */

static Object array_constant_44;   /* # */

static Object Qpure_number;        /* pure-number */

static Object array_constant_45;   /* # */

/* TWRITE-DATA-TYPE */
Object twrite_data_type(data_type)
    Object data_type;
{
    x_note_fn_call(80,262);
    if (CONSP(data_type) && EQ(CAR(data_type),Qab_class))
	return twrite_symbol(1,SECOND(data_type));
    else if ( !SYMBOLP(data_type))
	return twrite(data_type);
    else if (EQ(data_type,Qdatum))
	return twrite_beginning_of_wide_string(array_constant_21,
		FIX((SI_Long)5L));
    else if (EQ(data_type,Qnumber))
	return twrite_beginning_of_wide_string(array_constant_38,
		FIX((SI_Long)8L));
    else if (EQ(data_type,Qinteger))
	return twrite_beginning_of_wide_string(array_constant_39,
		FIX((SI_Long)7L));
    else if (EQ(data_type,Qlong))
	return twrite_beginning_of_wide_string(array_constant_40,
		FIX((SI_Long)4L));
    else if (EQ(data_type,Qfloat))
	return twrite_beginning_of_wide_string(array_constant_41,
		FIX((SI_Long)5L));
    else if (EQ(data_type,Qseconds))
	return twrite_beginning_of_wide_string(array_constant_42,
		FIX((SI_Long)8L));
    else if (EQ(data_type,Qtime_stamp))
	return twrite_beginning_of_wide_string(array_constant_43,
		FIX((SI_Long)10L));
    else if (EQ(data_type,Qtruth_value))
	return twrite_beginning_of_wide_string(array_constant_44,
		FIX((SI_Long)11L));
    else if (EQ(data_type,Qpure_number))
	return twrite_beginning_of_wide_string(array_constant_45,
		FIX((SI_Long)11L));
    else if (data_type)
	return twrite_symbol(1,data_type);
    else
	return twrite(string_constant_9);
}

static Object string_constant_25;  /* ", ~(~a~) " */

static Object string_constant_26;  /* " ~(~a~) " */

/* WRITE-COMBINED-TYPE-SPECIFICATION */
Object write_combined_type_specification(combiner,types)
    Object combiner, types;
{
    Object types_count, type, ab_loop_list_;
    SI_Long count_1;

    x_note_fn_call(80,263);
    types_count = length(types);
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),types_count) && 
	    FIXNUM_LE(types_count,FIX((SI_Long)127L)))) {
	count_1 = (SI_Long)1L;
	type = Nil;
	ab_loop_list_ = types;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (count_1 == IFIX(types_count))
	    tformat(2,string_constant_25,combiner);
	else if (count_1 != (SI_Long)1L)
	    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
	write_type_specification(type);
	count_1 = count_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else
	switch (INTEGER_TO_CHAR(types_count)) {
	  case 0:
	    break;
	  case 1:
	    write_type_specification(FIRST(types));
	    break;
	  case 2:
	    write_type_specification(FIRST(types));
	    tformat(2,string_constant_26,combiner);
	    write_type_specification(SECOND(types));
	    break;
	  default:
	    count_1 = (SI_Long)1L;
	    type = Nil;
	    ab_loop_list_ = types;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (count_1 == IFIX(types_count))
		tformat(2,string_constant_25,combiner);
	    else if (count_1 != (SI_Long)1L)
		twrite_beginning_of_wide_string(array_constant,
			FIX((SI_Long)2L));
	    write_type_specification(type);
	    count_1 = count_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    break;
	}
    return VALUES_1(Nil);
}

/* EVALUATION-VALUE-HASH */
Object evaluation_value_hash(evaluation_value)
    Object evaluation_value;
{
    Object wide_string_bv16, wide_string_bv16_1, buffer;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;

    x_note_fn_call(80,264);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Ev_hash_buffer_size) + 
	    (SI_Long)3L));
    fill_wide_string_1(wide_string_bv16,FIX((SI_Long)48L),FIX((SI_Long)0L),
	    Ev_hash_buffer_size);
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Ev_hash_buffer_size) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(Ev_hash_buffer_size),(SI_Long)0L);
    wide_string_bv16_1 = wide_string_bv16;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16_1));
    length_1 = UBYTE_16_ISAREF_1(wide_string_bv16_1,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16_1,length_1 
	    - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    UBYTE_16_ISASET_1(wide_string_bv16_1,length_1,(SI_Long)1L);
    buffer = wide_string_bv16_1;
    UBYTE_16_ISASET_1(buffer,(SI_Long)0L,IFIX(Ev_hash_version));
    evaluation_value_hash_1(evaluation_value,buffer,FIX((SI_Long)1L));
    return VALUES_1(buffer);
}

static Object Qsymbol_name_wide_string;  /* symbol-name-wide-string */

/* EVALUATION-VALUE-HASH-1 */
Object evaluation_value_hash_1(evaluation_value,buffer,index_1)
    Object evaluation_value, buffer, index_1;
{
    Object text_string, gensymed_symbol, list_1, temp, cdr_1, held_vector;
    Object element, elt_1, validated_elt, k, attribute_value, v, byte0, byte1;
    Object byte2, byte3;
    SI_Long current_value, new_value, i, length_1, ab_loop_bind_, next_index;
    SI_Long length_2, gensymed_symbol_1, b0, b1, b2, b3;
    Object result;

    x_note_fn_call(80,265);
    if ( !TRUEP(evaluation_value)) {
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(Ev_hash_null_code);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
    }
    else if (FIXNUMP(evaluation_value)) {
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(Ev_hash_integer_code);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(evaluation_value) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(evaluation_value) >>  -  - 
		(SI_Long)16L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(evaluation_value) >>  -  - 
		(SI_Long)32L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(evaluation_value) >>  -  - 
		(SI_Long)48L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
    }
    else if (evaluation_value && SYMBOLP(evaluation_value) || 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value) != 
		(SI_Long)0L) {
	text_string = Nil;
	if (evaluation_value && SYMBOLP(evaluation_value)) {
	    current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	    new_value = current_value ^ IFIX(Ev_hash_symbol_code);
	    UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	    if (IFIX(index_1) == (SI_Long)8L)
		index_1 = FIX((SI_Long)0L);
	    else
		index_1 = FIXNUM_ADD1(index_1);
	    gensymed_symbol = evaluation_value;
	    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
	  next_loop:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qsymbol_name_wide_string))
		goto end_loop;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop;
	  end_loop:
	    temp = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	    if (temp);
	    else
		temp = mutate_global_property(gensymed_symbol,
			make_symbol_name_wide_string(gensymed_symbol),
			Qsymbol_name_wide_string);
	    text_string = temp;
	}
	else {
	    current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	    new_value = current_value ^ IFIX(Ev_hash_text_code);
	    UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	    if (IFIX(index_1) == (SI_Long)8L)
		index_1 = FIX((SI_Long)0L);
	    else
		index_1 = FIXNUM_ADD1(index_1);
	    text_string = evaluation_value;
	}
	i = (SI_Long)0L;
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
	ab_loop_bind_ = UBYTE_16_ISAREF_1(text_string,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(text_string,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ UBYTE_16_ISAREF_1(text_string,i);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else if (CONSP(evaluation_value)) {
	cdr_1 = M_CDR(evaluation_value);
	if (EQ(cdr_1,Qsequence)) {
	    current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	    new_value = current_value ^ IFIX(Ev_hash_sequence_code);
	    UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	    if (IFIX(index_1) == (SI_Long)8L)
		index_1 = FIX((SI_Long)0L);
	    else
		index_1 = FIXNUM_ADD1(index_1);
	    gensymed_symbol = evaluation_value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    element = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_2:
	    if (next_index >= length_2)
		goto end_loop_2;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    element = validated_elt;
	    index_1 = evaluation_value_hash_1(element,buffer,index_1);
	    goto next_loop_2;
	  end_loop_2:;
	}
	else if (EQ(cdr_1,Qab_structure)) {
	    current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	    new_value = current_value ^ IFIX(Ev_hash_structure_code);
	    UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	    if (IFIX(index_1) == (SI_Long)8L)
		index_1 = FIX((SI_Long)0L);
	    else
		index_1 = FIXNUM_ADD1(index_1);
	    gensymed_symbol = evaluation_value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    k = Nil;
	    attribute_value = Nil;
	    v = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_2)
		goto end_loop_3;
	    k = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    v = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    index_1 = evaluation_value_hash_1(k,buffer,index_1);
	    index_1 = evaluation_value_hash_1(v,buffer,index_1);
	    goto next_loop_3;
	  end_loop_3:;
	}
	else if (EQ(cdr_1,Qtruth_value)) {
	    current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	    new_value = current_value ^ IFIX(Ev_hash_truth_value_code);
	    UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	    if (IFIX(index_1) == (SI_Long)8L)
		index_1 = FIX((SI_Long)0L);
	    else
		index_1 = FIXNUM_ADD1(index_1);
	    current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	    new_value = current_value ^ (SI_Long)1000L + 
		    IFIX(M_CAR(evaluation_value));
	    UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	    if (IFIX(index_1) == (SI_Long)8L)
		index_1 = FIX((SI_Long)0L);
	    else
		index_1 = FIXNUM_ADD1(index_1);
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L) {
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(Ev_hash_float_code);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	g2ext_foreign_partition_float(DFLOAT_ISAREF_1(evaluation_value,
		(SI_Long)0L),
		UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	MVS_4(result,byte0,byte1,byte2,byte3);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte0);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte1);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte2);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte3);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
    }
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L) {
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(Ev_hash_long_code);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	temp = aref1(evaluation_value,FIX((SI_Long)0L));
	g2ext_foreign_partition_long(INTEGER_TO_INT64(temp),
		UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_long_union));
	b0 = UBYTE_16_ISAREF_1(Partition_long_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(Partition_long_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(Partition_long_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(Partition_long_union,(SI_Long)3L);
	result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	MVS_4(result,byte0,byte1,byte2,byte3);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte0);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte1);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte2);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
	current_value = UBYTE_16_ISAREF_1(buffer,IFIX(index_1));
	new_value = current_value ^ IFIX(byte3);
	UBYTE_16_ISASET_1(buffer,IFIX(index_1),new_value);
	if (IFIX(index_1) == (SI_Long)8L)
	    index_1 = FIX((SI_Long)0L);
	else
	    index_1 = FIXNUM_ADD1(index_1);
    }
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qiteration_state));
    return VALUES_1(index_1);
}

/* CONVERT-TYPE-OR-UNIT-OF-MEASURE-TO-TYPE */
Object convert_type_or_unit_of_measure_to_type(unit_of_measure_or_type)
    Object unit_of_measure_or_type;
{
    Object gensymed_symbol, ab_loop_list_, temp_1;
    char temp;

    x_note_fn_call(80,266);
    gensymed_symbol = Nil;
    ab_loop_list_ = Type_symbols_subtype_alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		unit_of_measure_or_type)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if ( ! !temp)
	temp_1 = unit_of_measure_or_type;
    else if (EQ(unit_of_measure_or_type,Qnumber) || 
	    EQ(unit_of_measure_or_type,Qinteger) || 
	    EQ(unit_of_measure_or_type,Qfloat) || 
	    EQ(unit_of_measure_or_type,Qlong) || 
	    lookup_global_or_kb_specific_property_value(unit_of_measure_or_type,
	    Numeric_data_type_gkbprop))
	temp_1 = Qnumber;
    else {
	warn_about_unrecognized_type(unit_of_measure_or_type);
	temp_1 = Qnumber;
    }
    return VALUES_1(temp_1);
}

Object No_component_value = UNBOUND;

Object Component_kind_description_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Set_of_all_component_kinds, Qset_of_all_component_kinds);

Object Attribute_mimic_prop = UNBOUND;

Object Attribute_mimics_of_class_prop = UNBOUND;

Object The_type_description_of_attribute_mimic = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_attribute_mimics, Qchain_of_available_attribute_mimics);

DEFINE_VARIABLE_WITH_SYMBOL(Attribute_mimic_count, Qattribute_mimic_count);

Object Chain_of_available_attribute_mimics_vector = UNBOUND;

/* ATTRIBUTE-MIMIC-STRUCTURE-MEMORY-USAGE */
Object attribute_mimic_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,267);
    temp = Attribute_mimic_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ATTRIBUTE-MIMIC-COUNT */
Object outstanding_attribute_mimic_count()
{
    Object def_structure_attribute_mimic_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,268);
    gensymed_symbol = IFIX(Attribute_mimic_count);
    def_structure_attribute_mimic_variable = 
	    Chain_of_available_attribute_mimics;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_attribute_mimic_variable))
	goto end_loop;
    def_structure_attribute_mimic_variable = 
	    ISVREF(def_structure_attribute_mimic_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ATTRIBUTE-MIMIC-1 */
Object reclaim_attribute_mimic_1(attribute_mimic)
    Object attribute_mimic;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,269);
    inline_note_reclaim_cons(attribute_mimic,Nil);
    temp = ISVREF(Chain_of_available_attribute_mimics_vector,
	    IFIX(Current_thread_index));
    SVREF(attribute_mimic,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_attribute_mimics_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = attribute_mimic;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ATTRIBUTE-MIMIC */
Object reclaim_structure_for_attribute_mimic(attribute_mimic)
    Object attribute_mimic;
{
    x_note_fn_call(80,270);
    return reclaim_attribute_mimic_1(attribute_mimic);
}

/* MAKE-PERMANENT-ATTRIBUTE-MIMIC-STRUCTURE-INTERNAL */
Object make_permanent_attribute_mimic_structure_internal()
{
    Object def_structure_attribute_mimic_variable, the_array;
    Object defstruct_g2_attribute_mimic_variable;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,271);
    def_structure_attribute_mimic_variable = Nil;
    atomic_incff_symval(Qattribute_mimic_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
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
	defstruct_g2_attribute_mimic_variable = the_array;
	def_structure_attribute_mimic_variable = 
		defstruct_g2_attribute_mimic_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_attribute_mimic_variable);
}

/* MAKE-ATTRIBUTE-MIMIC-1 */
Object make_attribute_mimic_1(attribute_mimic_argument_type,
	    attribute_mimic_value_type,attribute_mimic_initial_value,
	    attribute_mimic_features,
	    attribute_mimic_place_reference_constructor)
    Object attribute_mimic_argument_type, attribute_mimic_value_type;
    Object attribute_mimic_initial_value, attribute_mimic_features;
    Object attribute_mimic_place_reference_constructor;
{
    Object def_structure_attribute_mimic_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(80,272);
    def_structure_attribute_mimic_variable = 
	    ISVREF(Chain_of_available_attribute_mimics_vector,
	    IFIX(Current_thread_index));
    if (def_structure_attribute_mimic_variable) {
	svref_arg_1 = Chain_of_available_attribute_mimics_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_attribute_mimic_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_attribute_mimic_variable = 
		make_permanent_attribute_mimic_structure_internal();
    inline_note_allocate_cons(def_structure_attribute_mimic_variable,Nil);
    SVREF(def_structure_attribute_mimic_variable,FIX((SI_Long)0L)) = 
	    attribute_mimic_argument_type;
    SVREF(def_structure_attribute_mimic_variable,FIX((SI_Long)1L)) = 
	    attribute_mimic_value_type;
    SVREF(def_structure_attribute_mimic_variable,FIX((SI_Long)2L)) = 
	    attribute_mimic_initial_value;
    SVREF(def_structure_attribute_mimic_variable,FIX((SI_Long)3L)) = 
	    attribute_mimic_features;
    SVREF(def_structure_attribute_mimic_variable,FIX((SI_Long)4L)) = 
	    attribute_mimic_place_reference_constructor;
    return VALUES_1(def_structure_attribute_mimic_variable);
}

Object The_type_description_of_virtual_attribute = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_virtual_attributes, Qchain_of_available_virtual_attributes);

DEFINE_VARIABLE_WITH_SYMBOL(Virtual_attribute_count, Qvirtual_attribute_count);

Object Chain_of_available_virtual_attributes_vector = UNBOUND;

/* VIRTUAL-ATTRIBUTE-STRUCTURE-MEMORY-USAGE */
Object virtual_attribute_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,273);
    temp = Virtual_attribute_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-VIRTUAL-ATTRIBUTE-COUNT */
Object outstanding_virtual_attribute_count()
{
    Object def_structure_virtual_attribute_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,274);
    gensymed_symbol = IFIX(Virtual_attribute_count);
    def_structure_virtual_attribute_variable = 
	    Chain_of_available_virtual_attributes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_virtual_attribute_variable))
	goto end_loop;
    def_structure_virtual_attribute_variable = 
	    ISVREF(def_structure_virtual_attribute_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-VIRTUAL-ATTRIBUTE-1 */
Object reclaim_virtual_attribute_1(virtual_attribute)
    Object virtual_attribute;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,275);
    inline_note_reclaim_cons(virtual_attribute,Nil);
    temp = ISVREF(Chain_of_available_virtual_attributes_vector,
	    IFIX(Current_thread_index));
    SVREF(virtual_attribute,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_virtual_attributes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = virtual_attribute;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-VIRTUAL-ATTRIBUTE */
Object reclaim_structure_for_virtual_attribute(virtual_attribute)
    Object virtual_attribute;
{
    x_note_fn_call(80,276);
    return reclaim_virtual_attribute_1(virtual_attribute);
}

static Object Qg2_defstruct_structure_name_virtual_attribute_g2_struct;  /* g2-defstruct-structure-name::virtual-attribute-g2-struct */

/* MAKE-PERMANENT-VIRTUAL-ATTRIBUTE-STRUCTURE-INTERNAL */
Object make_permanent_virtual_attribute_structure_internal()
{
    Object def_structure_virtual_attribute_variable;
    Object defstruct_g2_virtual_attribute_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,277);
    def_structure_virtual_attribute_variable = Nil;
    atomic_incff_symval(Qvirtual_attribute_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_virtual_attribute_variable = Nil;
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
	defstruct_g2_virtual_attribute_variable = the_array;
	SVREF(defstruct_g2_virtual_attribute_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_virtual_attribute_g2_struct;
	def_structure_virtual_attribute_variable = 
		defstruct_g2_virtual_attribute_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_virtual_attribute_variable);
}

/* MAKE-VIRTUAL-ATTRIBUTE-1 */
Object make_virtual_attribute_1(virtual_attribute_name,
	    virtual_attribute_arg_type,virtual_attribute_value_type,
	    virtual_attribute_features,virtual_attribute_initial,
	    virtual_attribute_getter_qm,virtual_attribute_setter_qm)
    Object virtual_attribute_name, virtual_attribute_arg_type;
    Object virtual_attribute_value_type, virtual_attribute_features;
    Object virtual_attribute_initial, virtual_attribute_getter_qm;
    Object virtual_attribute_setter_qm;
{
    Object def_structure_virtual_attribute_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(80,278);
    def_structure_virtual_attribute_variable = 
	    ISVREF(Chain_of_available_virtual_attributes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_virtual_attribute_variable) {
	svref_arg_1 = Chain_of_available_virtual_attributes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_virtual_attribute_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_virtual_attribute_g2_struct;
    }
    else
	def_structure_virtual_attribute_variable = 
		make_permanent_virtual_attribute_structure_internal();
    inline_note_allocate_cons(def_structure_virtual_attribute_variable,Nil);
    SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)1L)) = 
	    virtual_attribute_name;
    SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)2L)) = 
	    virtual_attribute_arg_type;
    SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)3L)) = 
	    virtual_attribute_value_type;
    SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)4L)) = 
	    virtual_attribute_features;
    SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)5L)) = 
	    virtual_attribute_initial;
    SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)6L)) = 
	    virtual_attribute_getter_qm;
    SVREF(def_structure_virtual_attribute_variable,FIX((SI_Long)7L)) = 
	    virtual_attribute_setter_qm;
    return VALUES_1(def_structure_virtual_attribute_variable);
}

static Object Qvirtual_attribute;  /* virtual-attribute */

/* PRINT-VIRTUAL-ATTRIBUTE */
Object print_virtual_attribute(va,stream,depth)
    Object va, stream, depth;
{
    Object dot_object_dot, dot_stream_dot;

    x_note_fn_call(80,279);
    dot_object_dot = va;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    format((SI_Long)4L,stream,"~s ~s",Qvirtual_attribute,ISVREF(va,
	    (SI_Long)1L));
    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
}

Object Virtual_attribute_prop = UNBOUND;

Object Virtual_attributes_local_to_class_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Virtual_attributes_not_local_to_a_class, Qvirtual_attributes_not_local_to_a_class);

DEFINE_VARIABLE_WITH_SYMBOL(All_virtual_attributes, Qall_virtual_attributes);

static Object Qdeprecated;         /* deprecated */

/* CLASS-IS-SPECIFICALLY-DEPRECATED-IN-FEATURES-P */
Object class_is_specifically_deprecated_in_features_p(class_name,features)
    Object class_name, features;
{
    Object feature, value, ab_loop_list_, ab_loop_it_, temp;

    x_note_fn_call(80,280);
    feature = Nil;
    value = Nil;
    ab_loop_list_ = features;
    ab_loop_it_ = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    feature = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    ab_loop_it_ = EQ(Qdeprecated,feature) ? memq_function(class_name,
	    value) : Qnil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* ADD-VIRTUAL-ATTRIBUTE */
Object add_virtual_attribute(name,arg_type_spec,value_type_spec,features,
	    initial,getter,setter)
    Object name, arg_type_spec, value_type_spec, features, initial, getter;
    Object setter;
{
    Object va, temp;

    x_note_fn_call(80,281);
    va = get_property_value_function(3,
	    get_symbol_properties_function(name),Qvirtual_attribute,Nil);
    if (va) {
	SVREF(va,FIX((SI_Long)2L)) = arg_type_spec;
	SVREF(va,FIX((SI_Long)3L)) = value_type_spec;
	SVREF(va,FIX((SI_Long)4L)) = features;
	SVREF(va,FIX((SI_Long)5L)) = initial;
	SVREF(va,FIX((SI_Long)6L)) = getter;
	SVREF(va,FIX((SI_Long)7L)) = setter;
    }
    else {
	temp = get_symbol_properties_function(name);
	set_property_value_function(temp,Qvirtual_attribute,
		make_virtual_attribute_1(name,arg_type_spec,
		value_type_spec,features,initial,getter,setter));
    }
    return VALUES_1(name);
}

/* VIRTUAL-ATTRIBUTE-DEFINED-FOR-CLASS? */
Object virtual_attribute_defined_for_class_qm(virtual_attribute,class_1)
    Object virtual_attribute, class_1;
{
    Object arg_type, sub_type_class, gensymed_symbol, temp, sub_type;
    Object ab_loop_list_;

    x_note_fn_call(80,282);
    arg_type = ISVREF(virtual_attribute,(SI_Long)2L);
    if (class_type_specification_p(arg_type)) {
	sub_type_class = M_CAR(M_CDR(arg_type));
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	temp = (gensymed_symbol ? TRUEP(memq_function(sub_type_class,
		ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) ? 
		sub_type_class : Nil;
    }
    else {
	sub_type = Nil;
	ab_loop_list_ = M_CDR(arg_type);
	sub_type_class = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sub_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_type_class = M_CAR(M_CDR(sub_type));
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol ? TRUEP(memq_function(sub_type_class,
		ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) {
	    temp = sub_type_class;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* PLACE-REFERENCE-OF-VIRTUAL-ATTRIBUTE? */
Object place_reference_of_virtual_attribute_qm(frame,attribute)
    Object frame, attribute;
{
    Object virtual_attribute_qm, frame_type_spec, temp;

    x_note_fn_call(80,283);
    virtual_attribute_qm = get_property_value_function(3,
	    get_symbol_properties_function(attribute),Qvirtual_attribute,Nil);
    if (virtual_attribute_qm) {
	frame_type_spec = ISVREF(virtual_attribute_qm,(SI_Long)2L);
	temp = type_specification_type_p(frame,frame_type_spec) ? 
		make_evaluation_place_reference_to_place(slot_value_list_3(Qvirtual_attribute,
		attribute,Qcurrent_computation_frame),frame) : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-VIRTUAL-ATTRIBUTE-COMPONENT */
Object get_virtual_attribute_component(block,component_particulars)
    Object block, component_particulars;
{
    Object name, virtual_attribute_qm, getter_qm, temp;

    x_note_fn_call(80,284);
    name = M_CAR(M_CDR(component_particulars));
    virtual_attribute_qm = get_property_value_function(3,
	    get_symbol_properties_function(name),Qvirtual_attribute,Nil);
    if (virtual_attribute_qm) {
	getter_qm = ISVREF(virtual_attribute_qm,(SI_Long)6L);
	temp = getter_qm ? inline_funcall_1(getter_qm,block) : 
		No_component_value;
    }
    else
	temp = No_component_value;
    return VALUES_1(temp);
}

static Object string_constant_27;  /* "The attribute ~a of ~NF is read-only." */

static Object string_constant_28;  /* "No attribute named ~a exists in ~NF." */

/* SET-VIRTUAL-ATTRIBUTE-COMPONENT */
Object set_virtual_attribute_component(block,component_particulars,new_value)
    Object block, component_particulars, new_value;
{
    Object name, virtual_attribute_qm, setter_qm, temp;

    x_note_fn_call(80,285);
    name = M_CAR(M_CDR(component_particulars));
    virtual_attribute_qm = get_property_value_function(3,
	    get_symbol_properties_function(name),Qvirtual_attribute,Nil);
    if (virtual_attribute_qm) {
	setter_qm = ISVREF(virtual_attribute_qm,(SI_Long)7L);
	temp = setter_qm ? inline_funcall_2(setter_qm,block,new_value) : 
		tformat_text_string(3,string_constant_27,name,block);
    }
    else
	temp = tformat_text_string(3,string_constant_28,name,block);
    return VALUES_1(temp);
}

Object Category_evaluator_interface_prop = UNBOUND;

Object The_type_description_of_category_evaluator_interface = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_category_evaluator_interfaces, Qchain_of_available_category_evaluator_interfaces);

DEFINE_VARIABLE_WITH_SYMBOL(Category_evaluator_interface_count, Qcategory_evaluator_interface_count);

Object Chain_of_available_category_evaluator_interfaces_vector = UNBOUND;

/* CATEGORY-EVALUATOR-INTERFACE-STRUCTURE-MEMORY-USAGE */
Object category_evaluator_interface_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(80,286);
    temp = Category_evaluator_interface_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CATEGORY-EVALUATOR-INTERFACE-COUNT */
Object outstanding_category_evaluator_interface_count()
{
    Object def_structure_category_evaluator_interface_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(80,287);
    gensymed_symbol = IFIX(Category_evaluator_interface_count);
    def_structure_category_evaluator_interface_variable = 
	    Chain_of_available_category_evaluator_interfaces;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_category_evaluator_interface_variable))
	goto end_loop;
    def_structure_category_evaluator_interface_variable = 
	    ISVREF(def_structure_category_evaluator_interface_variable,
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

/* RECLAIM-CATEGORY-EVALUATOR-INTERFACE-1 */
Object reclaim_category_evaluator_interface_1(category_evaluator_interface)
    Object category_evaluator_interface;
{
    Object temp, svref_arg_2;

    x_note_fn_call(80,288);
    inline_note_reclaim_cons(category_evaluator_interface,Nil);
    temp = ISVREF(Chain_of_available_category_evaluator_interfaces_vector,
	    IFIX(Current_thread_index));
    SVREF(category_evaluator_interface,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_category_evaluator_interfaces_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = category_evaluator_interface;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CATEGORY-EVALUATOR-INTERFACE */
Object reclaim_structure_for_category_evaluator_interface(category_evaluator_interface)
    Object category_evaluator_interface;
{
    x_note_fn_call(80,289);
    return reclaim_category_evaluator_interface_1(category_evaluator_interface);
}

static Object Qg2_defstruct_structure_name_category_evaluator_interface_g2_struct;  /* g2-defstruct-structure-name::category-evaluator-interface-g2-struct */

/* MAKE-PERMANENT-CATEGORY-EVALUATOR-INTERFACE-STRUCTURE-INTERNAL */
Object make_permanent_category_evaluator_interface_structure_internal()
{
    Object def_structure_category_evaluator_interface_variable;
    Object defstruct_g2_category_evaluator_interface_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(80,290);
    def_structure_category_evaluator_interface_variable = Nil;
    atomic_incff_symval(Qcategory_evaluator_interface_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_category_evaluator_interface_variable = Nil;
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
	defstruct_g2_category_evaluator_interface_variable = the_array;
	SVREF(defstruct_g2_category_evaluator_interface_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_category_evaluator_interface_g2_struct;
	def_structure_category_evaluator_interface_variable = 
		defstruct_g2_category_evaluator_interface_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_category_evaluator_interface_variable);
}

/* MAKE-CATEGORY-EVALUATOR-INTERFACE-1 */
Object make_category_evaluator_interface_1(category_evaluator_interface_name)
    Object category_evaluator_interface_name;
{
    Object def_structure_category_evaluator_interface_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(80,291);
    def_structure_category_evaluator_interface_variable = 
	    ISVREF(Chain_of_available_category_evaluator_interfaces_vector,
	    IFIX(Current_thread_index));
    if (def_structure_category_evaluator_interface_variable) {
	svref_arg_1 = Chain_of_available_category_evaluator_interfaces_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_category_evaluator_interface_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_category_evaluator_interface_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_category_evaluator_interface_g2_struct;
    }
    else
	def_structure_category_evaluator_interface_variable = 
		make_permanent_category_evaluator_interface_structure_internal();
    inline_note_allocate_cons(def_structure_category_evaluator_interface_variable,
	    Nil);
    SVREF(def_structure_category_evaluator_interface_variable,
	    FIX((SI_Long)1L)) = category_evaluator_interface_name;
    SVREF(def_structure_category_evaluator_interface_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_category_evaluator_interface_variable,
	    FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_category_evaluator_interface_variable);
}

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* GET-CATEGORY-EVALUATOR-INTERFACE */
Object get_category_evaluator_interface(name)
    Object name;
{
    Object temp;

    x_note_fn_call(80,292);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
	    Qcategory_evaluator_interface);
    if (temp)
	return VALUES_1(temp);
    else
	return mutate_global_property(name,
		make_category_evaluator_interface_1(name),
		Qcategory_evaluator_interface);
}

/* SET-EVALUATION-VALUE-TO-CATEGORY-FUNCTION */
Object set_evaluation_value_to_category_function(name,value)
    Object name, value;
{
    Object svref_arg_1;

    x_note_fn_call(80,293);
    svref_arg_1 = get_category_evaluator_interface(name);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)3L)) = value);
}

/* SET-SLOT-VALUE-TO-EVALUATION-VALUE-FUNCTION */
Object set_slot_value_to_evaluation_value_function(name,value)
    Object name, value;
{
    Object svref_arg_1;

    x_note_fn_call(80,294);
    svref_arg_1 = get_category_evaluator_interface(name);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)2L)) = value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_reason_for_complex_type_rejection, Qlast_reason_for_complex_type_rejection);

DEFINE_VARIABLE_WITH_SYMBOL(Structure_slot_not_bound, Qstructure_slot_not_bound);

DEFINE_VARIABLE_WITH_SYMBOL(Reason_for_type_failure, Qreason_for_type_failure);

DEFINE_VARIABLE_WITH_SYMBOL(Type_at_type_failure, Qtype_at_type_failure);

DEFINE_VARIABLE_WITH_SYMBOL(Value_at_type_failure, Qvalue_at_type_failure);

DEFINE_VARIABLE_WITH_SYMBOL(Context_of_type_failure, Qcontext_of_type_failure);

DEFINE_VARIABLE_WITH_SYMBOL(Last_slot_checked_of_type_failure, Qlast_slot_checked_of_type_failure);

DEFINE_VARIABLE_WITH_SYMBOL(Structure_specs_allow_unknown_slots_p, Qstructure_specs_allow_unknown_slots_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_category_name_for_type_specification_type_p, Qcurrent_category_name_for_type_specification_type_p);

static Object Qtype_mismatch;      /* type-mismatch */

/* TYPE-SPECIFICATION-TYPE-P--WITH-EXPLANATION */
Object type_specification_type_p__with_explanation(thing,type)
    Object thing, type;
{
    Object temp, required_type, ab_loop_list_, name;
    Object current_category_name_for_type_specification_type_p;
    Declare_special(1);

    x_note_fn_call(80,295);
    if (CONSP(thing) && EQ(M_CDR(thing),Qitem_reference))
	temp = 
		type_specification_type_p__with_explanation(ISVREF(M_CAR(thing),
		(SI_Long)3L),type);
    else {
	temp = CONSP(type) ? M_CAR(type) : Qnil;
	if (EQ(temp,Qab_or))
	    temp = type_specification_type_p__with_explanation__or(thing,type);
	else if (EQ(temp,Qand)) {
	    required_type = Nil;
	    ab_loop_list_ = M_CDR(type);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    required_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_type_p__with_explanation(thing,
		    required_type))) {
		temp = Nil;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = T;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else if (EQ(temp,Qsequence))
	    temp = 
		    type_specification_type_p__with_explanation__sequence(thing,
		    type);
	else if (EQ(temp,Qab_structure))
	    temp = 
		    type_specification_type_p__with_explanation__structure(thing,
		    type);
	else if (EQ(temp,Qnamed)) {
	    name = CADR(type);
	    current_category_name_for_type_specification_type_p = name;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_category_name_for_type_specification_type_p,Qcurrent_category_name_for_type_specification_type_p,current_category_name_for_type_specification_type_p,
		    0);
	      temp = CADR(type);
	      if (SYMBOLP(temp) && EQ(CADR(type),Qcolor_or_metacolor))
		  temp =  !EQ(color_or_metacolor_p(thing),Nil) ? T : Nil;
	      else {
		  temp = get_property_value_function(3,
			  get_symbol_properties_function(name),
			  Qtype_specification_explicit_complex_type,Nil);
		  if (temp);
		  else
		      temp = get_property_value_function(3,
			      get_symbol_properties_function(name),
			      Qtype_specification_simple_expansion,Nil);
		  temp = type_specification_type_p__with_explanation(thing,
			  temp);
	      }
	    POP_SPECIAL();
	}
	else {
	    temp = type_specification_type_p(thing,type);
	    if (temp);
	    else {
		if ( !TRUEP(Reason_for_type_failure)) {
		    Value_at_type_failure = thing;
		    Type_at_type_failure = type;
		    Reason_for_type_failure = Qtype_mismatch;
		}
		temp = Nil;
	    }
	}
    }
    return VALUES_1(temp);
}

static Object Qdefault_overrides_for_class_definitions;  /* default-overrides-for-class-definitions */

static Object Qdefault_overrides_for_object_definitions;  /* default-overrides-for-object-definitions */

static Object list_constant_9;     /* # */

static Object Qrestrict_proprietary_items_and_configure_user_interface_statement;  /* restrict-proprietary-items-and-configure-user-interface-statement */

static Object list_constant_10;    /* # */

static Object Qsimple_type_mismatch;  /* simple-type-mismatch */

static Object Qneither_uan_nor_sad_present;  /* neither-uan-nor-sad-present */

static Object Qinvalid_operation_type;  /* invalid-operation-type */

static Object Qstructure_choose_type_mismatch;  /* structure-choose-type-mismatch */

/* TYPE-SPECIFICATION-TYPE-P--WITH-EXPLANATION--OR */
Object type_specification_type_p__with_explanation__or(thing,type)
    Object thing, type;
{
    Object required_type, ab_loop_list_, ab_loop_it_, temp, type_name;
    Object discriminant_list, required_type1, simplified_type, last_1;
    Object sequence_or_structure_p;
    char temp_1;

    x_note_fn_call(80,296);
    required_type = Nil;
    ab_loop_list_ = M_CDR(type);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    required_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = type_specification_type_p(thing,required_type);
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
    else {
	type_name = Current_category_name_for_type_specification_type_p;
	if (EQ(type_name,Qdefault_overrides_for_class_definitions) || 
		EQ(type_name,Qdefault_overrides_for_object_definitions))
	    discriminant_list = list_constant_9;
	else if (EQ(type_name,
		Qrestrict_proprietary_items_and_configure_user_interface_statement))
	    discriminant_list = list_constant_10;
	else
	    discriminant_list = Qnil;
	if ( !TRUEP(Reason_for_type_failure)) {
	    required_type = Nil;
	    ab_loop_list_ = M_CDR(type);
	    required_type1 = Nil;
	    simplified_type = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    required_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    required_type1 = expand_named_type(required_type);
	    if (ATOM(required_type1))
		simplified_type = required_type;
	    else if (EQ(CAR(required_type1),Qsequence))
		simplified_type = list_constant_7;
	    else if (EQ(CAR(required_type1),Qab_structure))
		simplified_type = list_constant_8;
	    else
		simplified_type = required_type;
	    if (type_specification_type_p(thing,simplified_type)) {
		temp_1 = TRUEP(Nil);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(T);
	    goto end_2;
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    if (temp_1) {
		Value_at_type_failure = thing;
		Type_at_type_failure = type;
		Reason_for_type_failure = Qsimple_type_mismatch;
	    }
	    else if (discriminant_list) {
		required_type = Nil;
		ab_loop_list_ = M_CDR(type);
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		required_type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		type_specification_type_p__with_explanation(thing,
			required_type);
		if ( !(CONSP(Context_of_type_failure) &&  
			!TRUEP(CDR(Context_of_type_failure)) && 
			memq_function(CAR(Context_of_type_failure),
			discriminant_list)))
		    goto end_3;
		Reason_for_type_failure = Nil;
		Context_of_type_failure = Nil;
		Last_slot_checked_of_type_failure = Nil;
		goto next_loop_2;
	      end_loop_2:
		if (CDR(discriminant_list)) {
		    Value_at_type_failure = thing;
		    Type_at_type_failure = type;
		    Reason_for_type_failure = Qneither_uan_nor_sad_present;
		    goto end_3;
		}
		else {
		    temp = Structure_slot_not_bound;
		    Value_at_type_failure = estructure_slot(thing,
			    CAR(discriminant_list),Structure_slot_not_bound);
		    if (EQ(temp,Value_at_type_failure)) {
			Value_at_type_failure = thing;
			Type_at_type_failure = type;
			Last_slot_checked_of_type_failure = 
				Structure_slot_not_bound;
			Reason_for_type_failure = Qinvalid_operation_type;
			goto end_3;
		    }
		    else {
			Type_at_type_failure = 
				get_combined_type_for_operation_type(type);
			Reason_for_type_failure = 
				Qstructure_choose_type_mismatch;
			goto end_3;
		    }
		}
		Reason_for_type_failure = Qnil;
	      end_3:;
	    }
	    else {
		temp = last(type,_);
		last_1 = CAR(temp);
		required_type = Nil;
		ab_loop_list_ = M_CDR(type);
		sequence_or_structure_p = Nil;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		required_type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (CONSP(required_type)) {
		    temp = EQ(CAR(required_type),Qsequence) ? T : Nil;
		    if (temp);
		    else
			temp = EQ(CAR(required_type),Qab_structure) ? T : Nil;
		    sequence_or_structure_p = temp;
		}
		else
		    sequence_or_structure_p = Nil;
		if ( !(ATOM(required_type) || (EQ(required_type,last_1) ? 
			TRUEP(sequence_or_structure_p) :  
			!TRUEP(sequence_or_structure_p)))) {
		    temp_1 = TRUEP(Nil);
		    goto end_4;
		}
		goto next_loop_3;
	      end_loop_3:
		temp_1 = TRUEP(T);
		goto end_4;
		temp_1 = TRUEP(Qnil);
	      end_4:;
		if (temp_1) {
		    temp = last(type,_);
		    type_specification_type_p__with_explanation(thing,
			    CAR(temp));
		}
		else {
		    Value_at_type_failure = thing;
		    Type_at_type_failure = type;
		    Reason_for_type_failure = Qtype_mismatch;
		}
	    }
	}
	return VALUES_1(Nil);
    }
}

/* GET-COMBINED-TYPE-FOR-OPERATION-TYPE */
Object get_combined_type_for_operation_type(type)
    Object type;
{
    Object choice, ab_loop_list_, choice_type, member_type, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, type_name, temp;

    x_note_fn_call(80,297);
    choice = Nil;
    ab_loop_list_ = CDR(type);
    choice_type = Nil;
    member_type = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    choice = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    type_name = CADR(choice);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(type_name),
	    Qtype_specification_explicit_complex_type,Nil);
    if (temp);
    else
	temp = get_property_value_function(3,
		get_symbol_properties_function(type_name),
		Qtype_specification_simple_expansion,Nil);
    choice_type = temp;
    temp = SECOND(choice_type);
    temp = FIRST(temp);
    member_type = SECOND(temp);
    ab_loopvar__2 = copy_list_using_eval_conses_1(CDR(member_type));
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return eval_cons_1(Qmember,temp);
}

static Object Qsequence_too_short;  /* sequence-too-short */

static Object Qsequence_too_long;  /* sequence-too-long */

/* TYPE-SPECIFICATION-TYPE-P--WITH-EXPLANATION--SEQUENCE */
Object type_specification_type_p__with_explanation__sequence(thing,type)
    Object thing, type;
{
    Object element_type, low_bound_qm, high_bound_qm, length_qm;
    Object gensymed_symbol, held_vector, element, ab_loop_iter_flag_, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1, index_1;
    char temp;

    x_note_fn_call(80,298);
    if ( !(CONSP(thing) && EQ(Qsequence,M_CDR(thing)))) {
	Value_at_type_failure = thing;
	Type_at_type_failure = list_constant_7;
	Reason_for_type_failure = Qsimple_type_mismatch;
	return VALUES_1(Nil);
    }
    else if ( !TRUEP(M_CDR(type)))
	return VALUES_1(T);
    else {
	element_type = CADR(type);
	low_bound_qm = CADDR(type);
	high_bound_qm = low_bound_qm ? CADDDR(type) : Qnil;
	length_qm = low_bound_qm ? FIXNUM_SUB1(ISVREF(M_CAR(thing),
		(SI_Long)1L)) : Qnil;
	temp =  !TRUEP(low_bound_qm);
	if (temp);
	else
	    temp = FIXNUM_LE(low_bound_qm,length_qm);
	if (temp);
	else {
	    Value_at_type_failure = thing;
	    Type_at_type_failure = type;
	    Reason_for_type_failure = Qsequence_too_short;
	    temp = TRUEP(Nil);
	}
	if (temp) {
	    temp =  !TRUEP(high_bound_qm);
	    if (temp);
	    else
		temp = FIXNUM_LT(length_qm,high_bound_qm);
	    if (temp);
	    else {
		Value_at_type_failure = thing;
		Type_at_type_failure = type;
		Reason_for_type_failure = Qsequence_too_long;
		temp = TRUEP(Nil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = thing;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    element = Nil;
	    index_1 = (SI_Long)0L;
	    ab_loop_iter_flag_ = T;
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
	    element = validated_elt;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 + (SI_Long)1L;
	    temp = 
		    TRUEP(type_specification_type_p__with_explanation(element,
		    element_type));
	    if (temp);
	    else {
		Context_of_type_failure = eval_cons_1(FIX(index_1),
			Context_of_type_failure);
		temp = TRUEP(Nil);
	    }
	    if ( !temp)
		return VALUES_1(Nil);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(T);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qconstrain_movement_of_items;  /* constrain-movement-of-items */

static Object Qtype_of_region;     /* type-of-region */

static Object Qobject_configuration_spec;  /* object-configuration-spec */

static Object Qconstrained_region;  /* constrained-region */

static Object Qclauses;            /* clauses */

static Object Qunknown_extra_structure_slot;  /* unknown-extra-structure-slot */

static Object Qmissing_required_structure_slots;  /* missing-required-structure-slots */

/* TYPE-SPECIFICATION-TYPE-P--WITH-EXPLANATION--STRUCTURE */
Object type_specification_type_p__with_explanation__structure(thing,type)
    Object thing, type;
{
    Object slot_specifications, minimum_contents, type_name;
    Object slot_containing_structure_type_name_qm;
    Object slot_containing_structure_qm, slot_name, slot_type, ab_loop_list_;
    Object slot_value, ab_loop_desetq_, temp, type_1, actual_slot_type;
    Object gensymed_symbol, held_vector, attribute_value;
    Object slot_specification_qm, conjunct;
    SI_Long next_index, length_1, gensymed_symbol_1;
    char temp_1;

    x_note_fn_call(80,299);
    if ( !(CONSP(thing) && EQ(Qab_structure,M_CDR(thing)))) {
	Value_at_type_failure = thing;
	Type_at_type_failure = list_constant_8;
	Reason_for_type_failure = Qsimple_type_mismatch;
	return VALUES_1(Nil);
    }
    else if ( !TRUEP(M_CDR(type)))
	return VALUES_1(T);
    else {
	slot_specifications = SECOND(type);
	minimum_contents = THIRD(type);
	type_name = Current_category_name_for_type_specification_type_p;
	if (EQ(type_name,Qconstrain_movement_of_items))
	    slot_containing_structure_type_name_qm = Qtype_of_region;
	else if (EQ(type_name,Qobject_configuration_spec))
	    slot_containing_structure_type_name_qm = Qtype;
	else
	    slot_containing_structure_type_name_qm = Qnil;
	if (slot_containing_structure_type_name_qm) {
	    if (EQ(type_name,Qconstrain_movement_of_items))
		slot_containing_structure_qm = Qconstrained_region;
	    else if (EQ(type_name,Qobject_configuration_spec))
		slot_containing_structure_qm = Qclauses;
	    else
		slot_containing_structure_qm = Qnil;
	}
	else
	    slot_containing_structure_qm = Nil;
	slot_name = Nil;
	slot_type = Nil;
	ab_loop_list_ = slot_specifications;
	slot_value = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	slot_name = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	slot_type = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	slot_value = estructure_slot(thing,slot_name,Structure_slot_not_bound);
	temp_1 = EQ(slot_value,Structure_slot_not_bound);
	if (temp_1);
	else if (slot_containing_structure_qm && EQ(slot_name,
		slot_containing_structure_qm)) {
	    type_1 = estructure_slot(thing,
		    slot_containing_structure_type_name_qm,Nil);
	    actual_slot_type = eval_list_2(Qnamed,type_1);
	    temp = type_specification_type_p__with_explanation(slot_value,
		    actual_slot_type);
	    reclaim_eval_list_1(actual_slot_type);
	    temp_1 = TRUEP(temp);
	}
	else
	    temp_1 = 
		    TRUEP(type_specification_type_p__with_explanation(slot_value,
		    slot_type));
	if (temp_1);
	else {
	    Context_of_type_failure = eval_cons_1(slot_name,
		    Context_of_type_failure);
	    temp_1 = TRUEP(Nil);
	}
	if ( !temp_1) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(Qnil);
      end_1:;
	if (temp_1) {
	    temp_1 = TRUEP(Structure_specs_allow_unknown_slots_p);
	    if (temp_1);
	    else {
		gensymed_symbol = thing;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		slot_name = Nil;
		attribute_value = Nil;
		slot_value = Nil;
		slot_specification_qm = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		slot_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		slot_value = 
			validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		slot_specification_qm = assq_function(slot_name,
			slot_specifications);
		temp_1 = TRUEP(slot_specification_qm);
		if (temp_1);
		else {
		    Value_at_type_failure = thing;
		    Type_at_type_failure = type;
		    Reason_for_type_failure = Qunknown_extra_structure_slot;
		    Last_slot_checked_of_type_failure = slot_name;
		    temp_1 = TRUEP(Nil);
		}
		if ( !temp_1) {
		    temp_1 = TRUEP(Nil);
		    goto end_2;
		}
		goto next_loop_1;
	      end_loop_1:
		temp_1 = TRUEP(T);
		goto end_2;
		temp_1 = TRUEP(Qnil);
	      end_2:;
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp =  !TRUEP(minimum_contents) ? T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else if (CONSP(minimum_contents) && EQ(Qand,
		    M_CAR(minimum_contents))) {
		conjunct = Nil;
		ab_loop_list_ = M_CDR(minimum_contents);
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		conjunct = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		temp_1 = TRUEP(eval_minimum_structure_contents(conjunct,
			thing));
		if (temp_1);
		else {
		    Value_at_type_failure = thing;
		    Type_at_type_failure = type;
		    Reason_for_type_failure = 
			    Qmissing_required_structure_slots;
		    Last_slot_checked_of_type_failure = conjunct;
		    temp_1 = TRUEP(Nil);
		}
		if ( !temp_1)
		    return VALUES_1(Nil);
		goto next_loop_2;
	      end_loop_2:
		return VALUES_1(T);
		return VALUES_1(Qnil);
	    }
	    else {
		temp = eval_minimum_structure_contents(minimum_contents,thing);
		if (temp)
		    return VALUES_1(temp);
		else {
		    Reason_for_type_failure = 
			    Qmissing_required_structure_slots;
		    Last_slot_checked_of_type_failure = 
			    CONSP(minimum_contents) && 
			    EQ(CAR(minimum_contents),Qab_or) ? 
			    CDR(minimum_contents) : minimum_contents;
		    return VALUES_1(Nil);
		}
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

/* MAKE-SIMPLIFIED-TYPE */
Object make_simplified_type(type)
    Object type;
{
    Object temp, temp_1, type1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(80,300);
    if (CONSP(type)) {
	temp = CAR(type);
	if (EQ(temp,Qsequence))
	    return eval_cons_1(Qsequence,Nil);
	else if (EQ(temp,Qab_structure))
	    return eval_cons_1(Qab_structure,Nil);
	else if (EQ(temp,Qand) || EQ(temp,Qab_or) || EQ(temp,Qnot)) {
	    temp_1 = CAR(type);
	    type1 = Nil;
	    ab_loop_list_ = CDR(type);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    type1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = eval_cons_1(make_simplified_type(type1),Nil);
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
	    return eval_cons_1(temp_1,temp);
	}
	else
	    return copy_tree_using_eval_conses_1(type);
    }
    else
	return VALUES_1(type);
}

static Object string_constant_29;  /* "the type ~NT" */

static Object Qdo_not_use;         /* do-not-use */

static Object string_constant_30;  /* "the ~(~A ~NF~)" */

static Object string_constant_31;  /* "the value ~(~NV~)" */

static Object string_constant_32;  /* "~%is not of ~A" */

static Object string_constant_33;  /* "~%is not of the correct type" */

static Object string_constant_34;  /* ",~%because a sequence was too short" */

static Object string_constant_35;  /* ",~%because a sequence was too long" */

static Object string_constant_36;  /* ",~%because at least one required structure slot was missing" */

static Object string_constant_37;  /* ",~%because a structure contained neither the slot ~(~a~) nor the slot ~(~a~)" */

static Object string_constant_38;  /* ",~%because a structure contained none of the following slots: ~(~L,|~)" */

static Object string_constant_39;  /* ",~%because the required structure slot ~(~a~) was missing" */

static Object string_constant_40;  /* ",~%because the structure slot ~(~a~) was not allowed, ~
				    *                                      because it was not one of ~(~L,|~)"
				    */

static Object string_constant_41;  /* ",~%because the required structure slot operation-type was not present" */

static Object string_constant_42;  /* ",~%because the operation-type slot had an illegal value" */

static Object string_constant_43;  /* ",~%because neither the structure slot user-attribute-name ~
				    *                             nor the structure system-attribute-designation was present"
				    */

static Object string_constant_44;  /* ",~%because ~(~NA~)~%was not of type ~NT" */

static Object string_constant_45;  /* "~%The problem occurred " */

static Object list_constant_11;    /* # */

static Object string_constant_46;  /* ", " */

static Object string_constant_47;  /* "inside element ~D" */

static Object string_constant_48;  /* "inside ~(~a~)" */

/* TYPE-ERROR-IN-SETTER */
Object type_error_in_setter(value,type,sub_value,sub_type,reason,context,
	    last_slot_checked)
    Object value, type, sub_value, sub_type, reason, context;
    Object last_slot_checked;
{
    Object type_string, temp, temp_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object x2, name, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, allowed_slots, simplified_type, firstp, subtype;
    Object expanded_subtype, expanded_subtype1, next_subtype, stype;
    Object ab_loop_list__1, stype1, minimum_contents_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char print_type_p, temp_2;
    Declare_special(5);

    x_note_fn_call(80,301);
    type_string = tformat_text_string(2,string_constant_29,type);
    temp = lengthw(type_string);
    temp_1 = FIX((SI_Long)800L);
    print_type_p = NUM_LT(temp,temp_1);
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
	      if (SIMPLE_VECTOR_P(value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(value,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(value,(SI_Long)1L);
		  temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2)
		  tformat(3,string_constant_30,class_function(value),value);
	      else
		  tformat(2,string_constant_31,value);
	      if (print_type_p)
		  tformat(2,string_constant_32,type_string);
	      else
		  tformat(1,string_constant_33);
	      if (reason) {
		  if (EQ(reason,Qsequence_too_short))
		      tformat(1,string_constant_34);
		  else if (EQ(reason,Qsequence_too_long))
		      tformat(1,string_constant_35);
		  else if (EQ(reason,Qmissing_required_structure_slots)) {
		      if ( !TRUEP(last_slot_checked))
			  tformat(1,string_constant_36);
		      else if (CONSP(last_slot_checked)) {
			  if (CADR(last_slot_checked) &&  
				  !TRUEP(CDDR(last_slot_checked)))
			      tformat(3,string_constant_37,
				      CAR(last_slot_checked),
				      CADR(last_slot_checked));
			  else
			      tformat(2,string_constant_38,last_slot_checked);
		      }
		      else
			  tformat(2,string_constant_39,last_slot_checked);
		  }
		  else if (EQ(reason,Qunknown_extra_structure_slot)) {
		      name = Nil;
		      ab_loop_list_ = SECOND(sub_type);
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		      ab_loop_desetq_ = Nil;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      ab_loop_desetq_ = M_CAR(ab_loop_list_);
		      name = CAR(ab_loop_desetq_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      ab_loopvar__2 = eval_cons_1(name,Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop;
		    end_loop:
		      allowed_slots = ab_loopvar_;
		      goto end_1;
		      allowed_slots = Qnil;
		    end_1:;
		      tformat(3,string_constant_40,last_slot_checked,
			      allowed_slots);
		      reclaim_eval_list_1(allowed_slots);
		  }
		  else if (EQ(reason,Qinvalid_operation_type)) {
		      if (EQ(last_slot_checked,Structure_slot_not_bound))
			  tformat(1,string_constant_41);
		      else
			  tformat(1,string_constant_42);
		  }
		  else if (EQ(reason,Qneither_uan_nor_sad_present))
		      tformat(1,string_constant_43);
		  else if (EQ(reason,Qsimple_type_mismatch)) {
		      if ( !EQUAL(sub_type,type)) {
			  simplified_type = make_simplified_type(sub_type);
			  tformat(3,string_constant_44,sub_value,
				  simplified_type);
			  reclaim_eval_tree_1(simplified_type);
		      }
		  }
		  else if (EQ(reason,Qstructure_choose_type_mismatch)) {
		      tformat(3,string_constant_44,sub_value,sub_type);
		      reclaim_eval_tree_1(sub_type);
		  }
		  else if (EQ(reason,Qtype_mismatch)) {
		      if ( !EQUAL(sub_type,type))
			  tformat(3,string_constant_44,sub_value,sub_type);
		  }
	      }
	      if (context) {
		  tformat(1,string_constant_45);
		  firstp = T;
		  subtype = type;
		  expanded_subtype = Nil;
		  expanded_subtype1 = Nil;
		  name = Nil;
		  ab_loop_list_ = context;
		  next_subtype = Nil;
		next_loop_1:
		  expanded_subtype = expand_named_type(subtype);
		  if (CONSP(expanded_subtype) && EQ(CAR(expanded_subtype),
			  Qab_or)) {
		      stype = Nil;
		      ab_loop_list__1 = CDR(expanded_subtype);
		      stype1 = Nil;
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list__1))
			  goto end_loop_1;
		      stype = M_CAR(ab_loop_list__1);
		      ab_loop_list__1 = M_CDR(ab_loop_list__1);
		      stype1 = expand_named_type(stype);
		      if (CONSP(stype1) && memq_function(CAR(stype1),
			      list_constant_11)) {
			  expanded_subtype1 = stype1;
			  goto end_2;
		      }
		      goto next_loop_2;
		    end_loop_1:
		      expanded_subtype1 = Qnil;
		    end_2:;
		  }
		  else
		      expanded_subtype1 = expanded_subtype;
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  name = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  temp_1 = CONSP(expanded_subtype1) ? 
			  CAR(expanded_subtype1) : expanded_subtype1;
		  if (EQ(temp_1,Qsequence))
		      next_subtype = FIXNUMP(name) ? 
			      CADR(expanded_subtype1) : Nil;
		  else if (EQ(temp_1,Qab_structure)) {
		      if (FIXNUMP(name))
			  next_subtype = Nil;
		      else {
			  temp_1 = assq_function(name,CADR(expanded_subtype1));
			  next_subtype = CADR(temp_1);
		      }
		  }
		  else
		      next_subtype = Nil;
		  if ( !TRUEP(firstp))
		      tformat(1,string_constant_46);
		  if (FIXNUMP(name))
		      tformat(2,string_constant_47,name);
		  else
		      tformat(2,string_constant_48,name);
		  firstp = Nil;
		  subtype = next_subtype;
		  goto next_loop_1;
		end_loop_2:
		  if (expanded_subtype &&  !print_type_p) {
		      if (EQ(reason,Qmissing_required_structure_slots)) {
			  if (ATOM(last_slot_checked)) {
			      minimum_contents_qm = CADDR(expanded_subtype);
			      if (minimum_contents_qm) {
				  twrite_beginning_of_wide_string(array_constant_34,
					  FIX((SI_Long)8L));
				  twrite_minimum_structure_contents(minimum_contents_qm,
					  T);
				  twrite_beginning_of_wide_string(array_constant_35,
					  FIX((SI_Long)16L));
			      }
			  }
		      }
		  }
	      }
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_text_string(type_string);
    reclaim_eval_list_1(context);
    return VALUES_1(temp_1);
}

Object Category_committer_function_prop = UNBOUND;

Object Category_extracter_function_prop = UNBOUND;

Object Text_category_evaluator_interface_p_prop = UNBOUND;

static Object Qtext_category_evaluator_interface_p;  /* text-category-evaluator-interface-p */

/* NOTE-TEXT-CATEGORY-EVALUATOR-INTERFACE */
Object note_text_category_evaluator_interface(category)
    Object category;
{
    x_note_fn_call(80,302);
    set_property_value_function(get_symbol_properties_function(category),
	    Qtext_category_evaluator_interface_p,T);
    return VALUES_1(T);
}

/* CHECK-TYPE-AND-RETURN-ERROR-STRING */
Object check_type_and_return_error_string(value,type)
    Object value, type;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure;
    Declare_special(5);
    Object result;

    x_note_fn_call(80,303);
    if ( !TRUEP(type_specification_type_p(value,type))) {
	value_at_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
		4);
	  type_at_type_failure = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		  3);
	    reason_for_type_failure = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      context_of_type_failure = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		      1);
		last_slot_checked_of_type_failure = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
			0);
		  type_specification_type_p__with_explanation(value,type);
		  result = type_error_in_setter(value,type,
			  Value_at_type_failure,Type_at_type_failure,
			  Reason_for_type_failure,Context_of_type_failure,
			  Last_slot_checked_of_type_failure);
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

/* CHECK-TYPE-ERROR-MESSAGE */
Object check_type_error_message varargs_1(int, n)
{
    Object value, type;
    Object allow_other_keys, maximum_number_of_slots_in_structure_type;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(80,304);
    INIT_ARGS_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    allow_other_keys = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    maximum_number_of_slots_in_structure_type = FIX((SI_Long)50L);
    PUSH_SPECIAL_WITH_SYMBOL(Maximum_number_of_slots_in_structure_type,Qmaximum_number_of_slots_in_structure_type,maximum_number_of_slots_in_structure_type,
	    0);
      if (allow_other_keys ||  !TRUEP(type_specification_type_p(value,type)))
	  result = explanation_for_type_error_qm(3,value,type,
		  allow_other_keys);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* EXPLANATION-FOR-TYPE-ERROR? */
Object explanation_for_type_error_qm varargs_1(int, n)
{
    Object value, type;
    Object allow_other_keys, structure_specs_allow_unknown_slots_p;
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure;
    Declare_varargs_nonrelocating;
    Declare_special(6);
    Object result;

    x_note_fn_call(80,305);
    INIT_ARGS_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    allow_other_keys = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    structure_specs_allow_unknown_slots_p = allow_other_keys;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_specs_allow_unknown_slots_p,Qstructure_specs_allow_unknown_slots_p,structure_specs_allow_unknown_slots_p,
	    5);
      value_at_type_failure = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
	      4);
	type_at_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		3);
	  reason_for_type_failure = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		  2);
	    context_of_type_failure = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		    1);
	      last_slot_checked_of_type_failure = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		      0);
		if ( 
			!TRUEP(type_specification_type_p__with_explanation(value,
			type)))
		    result = type_error_in_setter(value,type,
			    Value_at_type_failure,Type_at_type_failure,
			    Reason_for_type_failure,
			    Context_of_type_failure,
			    Last_slot_checked_of_type_failure);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* UNBOX-EVALUATION-VALUE */
Object unbox_evaluation_value varargs_1(int, n)
{
    Object ev;
    Object keys_to_omit;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(80,306);
    INIT_ARGS_nonrelocating();
    ev = REQUIRED_ARG_nonrelocating();
    keys_to_omit = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = unbox_evaluation_value_1(ev,keys_to_omit);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* UNBOX-EVALUATION-VALUE-1 */
Object unbox_evaluation_value_1(ev,keys_to_omit)
    Object ev, keys_to_omit;
{
    Object gensymed_symbol, held_vector, element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, slot, attribute_value, value;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, new_long, temp_2, x2;
    SI_Long next_index, length_1, gensymed_symbol_1;
    SI_int64 aref_new_value_1;
    char temp_3;
    double aref_new_value;

    x_note_fn_call(80,307);
    if (CONSP(ev) && EQ(M_CDR(ev),Qsequence)) {
	gensymed_symbol = ev;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	ab_loopvar__2 = gensym_cons_1(unbox_evaluation_value_1(element,
		Nil),Nil);
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
    else if (CONSP(ev) && EQ(M_CDR(ev),Qab_structure)) {
	gensymed_symbol = ev;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	slot = Nil;
	attribute_value = Nil;
	value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	slot = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	if ( !TRUEP(memq_function(slot,keys_to_omit))) {
	    ab_loopvar__2 = gensym_cons_1(slot,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    ab_loopvar__2 = gensym_cons_1(unbox_evaluation_value_1(value,
		    Nil),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(ev) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ev)) == (SI_Long)1L) {
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
	aref_new_value = DFLOAT_ISAREF_1(ev,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (INLINE_LONG_VECTOR_P(ev) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ev)) == (SI_Long)1L) {
	new_long = allocate_managed_long_box();
	temp_2 = aref1(ev,FIX((SI_Long)0L));
	aref_new_value_1 = INTEGER_TO_INT64(temp_2);
	set_aref1(new_long,FIX((SI_Long)0L),
		INT64_TO_INTEGER(aref_new_value_1));
	return VALUES_1(new_long);
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(ev) != (SI_Long)0L)
	return copy_text_string(ev);
    else if (FIXNUMP(ev))
	return VALUES_1(ev);
    else if (ev && SYMBOLP(ev))
	return VALUES_1(ev);
    else if (CONSP(ev) && EQ(M_CDR(ev),Qtruth_value)) {
	if (evaluation_truth_value_is_true_p(ev))
	    return VALUES_1(T);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (SIMPLE_VECTOR_P(ev) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ev)) > 
		(SI_Long)2L &&  !EQ(ISVREF(ev,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(ev,(SI_Long)1L);
	    temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3)
	    return VALUES_1(ev);
	else if ( !TRUEP(ev))
	    return VALUES_1(Nil);
	else
	    return VALUES_1(Nil);
    }
}

/* RECLAIM-UNBOXED-EVALUATION-VALUE */
Object reclaim_unboxed_evaluation_value(list_1)
    Object list_1;
{
    Object temp, e, ab_loop_list_;

    x_note_fn_call(80,308);
    temp =  !TRUEP(list_1) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	temp = SYMBOLP(list_1) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else {
	    temp = FIXNUMP(list_1) ? T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else if (text_string_p(list_1))
		return reclaim_text_string(list_1);
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(list_1) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(list_1)) == 
			(SI_Long)1L) {
		reclaim_managed_simple_float_array_of_length_1(list_1);
		return VALUES_1(Nil);
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(list_1) != (SI_Long)0L)
		return reclaim_managed_simple_float_array(list_1);
	    else if (CONSP(list_1)) {
		e = Nil;
		ab_loop_list_ = list_1;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		e = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		reclaim_unboxed_evaluation_value(e);
		goto next_loop;
	      end_loop:;
		return reclaim_gensym_list_1(list_1);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
}

void types_INIT()
{
    Object temp, reclaim_structure_for_g2_list_element_1, tail, head, new_cons;
    Object temp_1, svref_arg_2, svref_new_value, gensymed_symbol;
    Object gensymed_symbol_1, evaluation_unsigned_vector_16_eq_1;
    Object evaluation_member_eq_1, reclaim_structure_for_uuid_block_1;
    Object evaluation_item_reference_eq_1, evaluation_sequence_eq_1;
    Object evaluation_structure_eq_1, reclaim_structure_for_attribute_mimic_1;
    Object reclaim_structure_for_virtual_attribute_1;
    Object reclaim_structure_for_category_evaluator_interface_1;
    Object AB_package, Qcategory_extracter_function;
    Object Qcategory_committer_function, Qoperation_type;
    Object Qsystem_attribute_designation, Quser_attribute_name;
    Object list_constant_40, Qreclaim_structure;
    Object Qoutstanding_category_evaluator_interface_count;
    Object Qcategory_evaluator_interface_structure_memory_usage, Qutilities2;
    Object string_constant_60, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_59, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qset_virtual_attribute_component, Ksetter;
    Object Qget_virtual_attribute_component, Kgetter;
    Object Qcomponent_kind_description, Qvirtual_attributes_local_to_class;
    Object Qprint_virtual_attribute, Qoutstanding_virtual_attribute_count;
    Object Qvirtual_attribute_structure_memory_usage, string_constant_58;
    Object string_constant_57, Qattribute_mimic;
    Object Qoutstanding_attribute_mimic_count;
    Object Qattribute_mimic_structure_memory_usage, string_constant_56;
    Object Qg2_defstruct_structure_name_attribute_mimic_g2_struct;
    Object string_constant_55, Qattribute_mimics_of_class, string_constant_54;
    Object Qev_hash_buffer_size, Qev_hash_long_code, Qev_hash_structure_code;
    Object Qev_hash_sequence_code, Qev_hash_truth_value_code;
    Object Qev_hash_text_code, Qev_hash_symbol_code, Qev_hash_float_code;
    Object Qev_hash_integer_code, Qev_hash_null_code, Qev_hash_version;
    Object list_constant_21, list_constant_30, Qsingular_of_numeric_data_type;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qcategory_is_not_g2_element_datum_type, list_constant_39;
    Object Qitem_or_value, Qvalue, Qquantity, list_constant_38;
    Object list_constant_22, Qtype_specification_for_no_item, list_constant_37;
    Object Qtype_specification_for_unknown;
    Object Qtype_specification_for_iteration_state, list_constant_36;
    Object Qtype_specification_for_item, list_constant_35;
    Object Qtype_symbols_subtype_alist, list_constant_34, list_constant_33;
    Object list_constant_24, list_constant_26, list_constant_32;
    Object list_constant_31, list_constant_25, list_constant_29;
    Object list_constant_28, list_constant_27, Qevaluation_obsolete_datum_eql;
    Object Qdeep_copy_evaluation_obsolete_datum;
    Object Qcopy_evaluation_obsolete_datum, Qreclaim_evaluation_obsolete_datum;
    Object list_constant_23, Qevaluation_structure_eql;
    Object Qwrite_evaluation_structure, Qdeep_copy_evaluation_structure;
    Object Qcopy_evaluation_structure, Qreclaim_evaluation_structure;
    Object Qwrite_evaluation_sequence, Qevaluation_sequence_eql;
    Object Qg2_get_position_of_element_in_sequence;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qdeep_copy_evaluation_sequence, Qcopy_evaluation_sequence;
    Object Qreclaim_evaluation_sequence, Qwrite_evaluation_item_reference;
    Object Qevaluation_item_reference_eql, Qcopy_evaluation_item_reference;
    Object Qreclaim_evaluation_item_reference, Quuid_string_length;
    Object Qitem_reference_table_list_length_limit, Quuid_block_table_size;
    Object list_constant_20, Qreclaim_uuid_block_hash_table, list_constant_19;
    Object Qtypes, Qmake_uuid_block_hash_function, Kfuncall;
    Object Qmutate_uuid_block_hash_skip_list_entry, Quuid_block;
    Object Qoutstanding_uuid_block_count, Quuid_block_structure_memory_usage;
    Object string_constant_53, string_constant_52, Qwrite_evaluation_member;
    Object Qevaluation_member_eql, Qcopy_evaluation_member;
    Object Qreclaim_evaluation_member, list_constant_18;
    Object Qwrite_evaluation_unsigned_vector_16;
    Object Qevaluation_unsigned_vector_16_eql;
    Object Qcopy_evaluation_unsigned_vector_16;
    Object Qreclaim_evaluation_unsigned_vector_16, list_constant_17;
    Object Qdefined_evaluation_type_validator, Qevaluation_types;
    Object Qnumeric_data_type, string_constant_51, Qeval_cons_memory_usage;
    Object Qoutstanding_eval_conses, list_constant_16;
    Object Qeval_cons_counter_vector, Qmake_thread_array, list_constant_15;
    Object Qavailable_eval_conses_tail_vector, Qavailable_eval_conses_vector;
    Object list_constant_14, Qg2_list_structure_tail_marker, list_constant_13;
    Object Qg2_list_structure_head_marker, list_constant_12;
    Object Qg2_list_structure_marker, Qg2_list_element;
    Object Qoutstanding_g2_list_element_count;
    Object Qg2_list_element_structure_memory_usage, string_constant_50;
    Object Qg2_defstruct_structure_name_g2_list_element_g2_struct;
    Object string_constant_49;

    x_note_fn_call(80,309);
    SET_PACKAGE("AB");
    if (The_type_description_of_g2_list_element == UNBOUND)
	The_type_description_of_g2_list_element = Nil;
    string_constant_49 = 
	    STATIC_STRING("43Dy8m83hay1m83hay8k1l8k0000001m1m83*gy9k1n8y83-3ny1o83-2Iy83-2Ky83-2Gy83-2Hykqk0k0");
    temp = The_type_description_of_g2_list_element;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_g2_list_element = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_49));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_g2_list_element_g2_struct = 
	    STATIC_SYMBOL("G2-LIST-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_g2_list_element_g2_struct,
	    The_type_description_of_g2_list_element,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qg2_list_element = STATIC_SYMBOL("G2-LIST-ELEMENT",AB_package);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qg2_list_element,
	    The_type_description_of_g2_list_element,Qtype_description_of_type);
    Qoutstanding_g2_list_element_count = 
	    STATIC_SYMBOL("OUTSTANDING-G2-LIST-ELEMENT-COUNT",AB_package);
    Qg2_list_element_structure_memory_usage = 
	    STATIC_SYMBOL("G2-LIST-ELEMENT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_50 = STATIC_STRING("1q83hay8s83-VMy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_g2_list_element_count);
    push_optimized_constant(Qg2_list_element_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_50));
    Qchain_of_available_g2_list_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-G2-LIST-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_g2_list_elements,
	    Chain_of_available_g2_list_elements);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_g2_list_elements,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2_list_element_count = STATIC_SYMBOL("G2-LIST-ELEMENT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_list_element_count,G2_list_element_count);
    record_system_variable(Qg2_list_element_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_g2_list_elements_vector == UNBOUND)
	Chain_of_available_g2_list_elements_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qg2_list_element_structure_memory_usage,
	    STATIC_FUNCTION(g2_list_element_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_g2_list_element_count,
	    STATIC_FUNCTION(outstanding_g2_list_element_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_g2_list_element_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_g2_list_element,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qg2_list_element,
	    reclaim_structure_for_g2_list_element_1);
    Qg2_list_structure_marker = STATIC_SYMBOL("G2-LIST-STRUCTURE-MARKER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_list_structure_marker,
	    G2_list_structure_marker);
    list_constant_12 = STATIC_CONS(Qg2_list_structure_marker,Qnil);
    SET_SYMBOL_VALUE(Qg2_list_structure_marker,list_constant_12);
    Qg2_list_structure_head_marker = 
	    STATIC_SYMBOL("G2-LIST-STRUCTURE-HEAD-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_list_structure_head_marker,
	    G2_list_structure_head_marker);
    list_constant_13 = STATIC_CONS(Qg2_list_structure_head_marker,Qnil);
    SET_SYMBOL_VALUE(Qg2_list_structure_head_marker,list_constant_13);
    Qg2_list_structure_tail_marker = 
	    STATIC_SYMBOL("G2-LIST-STRUCTURE-TAIL-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_list_structure_tail_marker,
	    G2_list_structure_tail_marker);
    list_constant_14 = STATIC_CONS(Qg2_list_structure_tail_marker,Qnil);
    SET_SYMBOL_VALUE(Qg2_list_structure_tail_marker,list_constant_14);
    Qavailable_eval_conses = STATIC_SYMBOL("AVAILABLE-EVAL-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_eval_conses,Available_eval_conses);
    Qtypes = STATIC_SYMBOL("TYPES",AB_package);
    record_system_variable(Qavailable_eval_conses,Qtypes,Nil,Qnil,Qt,Qnil,
	    Qnil);
    Qavailable_eval_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-EVAL-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_eval_conses_tail,
	    Available_eval_conses_tail);
    record_system_variable(Qavailable_eval_conses_tail,Qtypes,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_eval_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-EVAL-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_eval_conses_vector,
	    Available_eval_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_eval_conses_vector,Qtypes,
	    list_constant_15,Qnil,Qt,Qnil,Qnil);
    Qavailable_eval_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-EVAL-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_eval_conses_tail_vector,
	    Available_eval_conses_tail_vector);
    record_system_variable(Qavailable_eval_conses_tail_vector,Qtypes,
	    list_constant_15,Qnil,Qt,Qnil,Qnil);
    Qeval_cons_counter_vector = STATIC_SYMBOL("EVAL-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qeval_cons_counter_vector,
	    Eval_cons_counter_vector);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qeval_cons_counter_vector,Qtypes,
	    list_constant_16,Qnil,Qt,Qnil,Qnil);
    Qeval_cons_counter = STATIC_SYMBOL("EVAL-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qeval_cons_counter,Eval_cons_counter);
    record_system_variable(Qeval_cons_counter,Qtypes,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    Qoutstanding_eval_conses = STATIC_SYMBOL("OUTSTANDING-EVAL-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_eval_conses,
	    STATIC_FUNCTION(outstanding_eval_conses,NIL,FALSE,0,0));
    Qeval_cons_memory_usage = STATIC_SYMBOL("EVAL-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_cons_memory_usage,
	    STATIC_FUNCTION(eval_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_51 = STATIC_STRING("1q83-T=y9k83-T*y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_eval_conses);
    push_optimized_constant(Qeval_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_51));
    Qnumeric_data_type = STATIC_SYMBOL("NUMERIC-DATA-TYPE",AB_package);
    Kb_specific_property_names = CONS(Qnumeric_data_type,
	    Kb_specific_property_names);
    Numeric_data_type_gkbprop = Qnumeric_data_type;
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qevaluation_types = STATIC_SYMBOL("EVALUATION-TYPES",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    if (Defined_evaluation_value_types == UNBOUND) {
	tail = 
		make_evaluation_types_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head = 
		make_evaluation_types_skip_list_sentinel(Most_negative_fixnum,
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol) = Qevaluation_types;
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
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_1) = head;
	M_CDR(gensymed_symbol_1) = tail;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	M_CDR(gensymed_symbol) = gensymed_symbol_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	Defined_evaluation_value_types = gensymed_symbol;
    }
    if (Defined_evaluation_datum_types == UNBOUND)
	Defined_evaluation_datum_types = Nil;
    Qtype_specification_of_defined_evaluation_type = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-OF-DEFINED-EVALUATION-TYPE",
	    AB_package);
    Type_specification_of_defined_evaluation_type_prop = 
	    Qtype_specification_of_defined_evaluation_type;
    Qdefined_evaluation_type_reclaimer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-RECLAIMER",AB_package);
    Defined_evaluation_type_reclaimer_prop = 
	    Qdefined_evaluation_type_reclaimer;
    Qdefined_evaluation_type_copier = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-COPIER",AB_package);
    Defined_evaluation_type_copier_prop = Qdefined_evaluation_type_copier;
    Qdefined_evaluation_type_deep_copier = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-DEEP-COPIER",AB_package);
    Defined_evaluation_type_deep_copier_prop = 
	    Qdefined_evaluation_type_deep_copier;
    Qdefined_evaluation_type_validator = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-VALIDATOR",AB_package);
    Defined_evaluation_type_validator_prop = 
	    Qdefined_evaluation_type_validator;
    Qdefined_evaluation_type_comparitor = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-COMPARITOR",AB_package);
    Defined_evaluation_type_comparitor_prop = 
	    Qdefined_evaluation_type_comparitor;
    Qdefined_evaluation_type_eq = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-=",AB_package);
    Defined_evaluation_type_eq_prop = Qdefined_evaluation_type_eq;
    Qdefined_evaluation_type_writer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-WRITER",AB_package);
    Defined_evaluation_type_writer_prop = Qdefined_evaluation_type_writer;
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Evaluation_true_value = CONS(Truth,Qtruth_value);
    Evaluation_false_value = CONS(Falsity,Qtruth_value);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qunsigned_vector_16 = STATIC_SYMBOL("UNSIGNED-VECTOR-16",AB_package);
    gensymed_symbol = Qunsigned_vector_16;
    temp = Defined_evaluation_value_types;
    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qunsigned_vector_16);
    temp_1 = adjoin(2,Qunsigned_vector_16,Defined_evaluation_datum_types);
    Defined_evaluation_datum_types = temp_1;
    list_constant_17 = STATIC_CONS(Qunsigned_vector_16,Qnil);
    set_property_value_function(get_symbol_properties_function(Qunsigned_vector_16),
	    Qtype_specification_of_defined_evaluation_type,list_constant_17);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    if (Test_removal_of_unsigned_vector_16 == UNBOUND)
	Test_removal_of_unsigned_vector_16 = Qunknown;
    string_constant = STATIC_STRING("TEST_REMOVAL_OF_UNSIGNED_VECTOR_16");
    Qreclaim_evaluation_unsigned_vector_16 = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-UNSIGNED-VECTOR-16",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_unsigned_vector_16,
	    STATIC_FUNCTION(reclaim_evaluation_unsigned_vector_16,NIL,
	    FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qunsigned_vector_16),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_unsigned_vector_16));
    Qcopy_evaluation_unsigned_vector_16 = 
	    STATIC_SYMBOL("COPY-EVALUATION-UNSIGNED-VECTOR-16",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_unsigned_vector_16,
	    STATIC_FUNCTION(copy_evaluation_unsigned_vector_16,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qunsigned_vector_16),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_unsigned_vector_16));
    Qevaluation_unsigned_vector_16_eql = 
	    STATIC_SYMBOL("EVALUATION-UNSIGNED-VECTOR-16-EQL",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_unsigned_vector_16_eql,
	    STATIC_FUNCTION(evaluation_unsigned_vector_16_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qunsigned_vector_16),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_unsigned_vector_16_eql));
    evaluation_unsigned_vector_16_eq_1 = 
	    STATIC_FUNCTION(evaluation_unsigned_vector_16_eq,NIL,FALSE,2,2);
    temp = get_symbol_properties_function(Qunsigned_vector_16);
    set_property_value_function(temp,Qdefined_evaluation_type_eq,
	    evaluation_unsigned_vector_16_eq_1);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qwrite_evaluation_unsigned_vector_16 = 
	    STATIC_SYMBOL("WRITE-EVALUATION-UNSIGNED-VECTOR-16",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_unsigned_vector_16,
	    STATIC_FUNCTION(write_evaluation_unsigned_vector_16,NIL,FALSE,
	    1,1));
    set_property_value_function(get_symbol_properties_function(Qunsigned_vector_16),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_unsigned_vector_16));
    gensymed_symbol = Qmember;
    temp = Defined_evaluation_value_types;
    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qmember);
    temp_1 = adjoin(2,Qmember,Defined_evaluation_datum_types);
    Defined_evaluation_datum_types = temp_1;
    list_constant_18 = STATIC_CONS(Qmember,Qnil);
    set_property_value_function(get_symbol_properties_function(Qmember),
	    Qtype_specification_of_defined_evaluation_type,list_constant_18);
    Qreclaim_evaluation_member = STATIC_SYMBOL("RECLAIM-EVALUATION-MEMBER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_member,
	    STATIC_FUNCTION(reclaim_evaluation_member,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qmember),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_member));
    Qcopy_evaluation_member = STATIC_SYMBOL("COPY-EVALUATION-MEMBER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_member,
	    STATIC_FUNCTION(copy_evaluation_member,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qmember),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_member));
    Qevaluation_member_eql = STATIC_SYMBOL("EVALUATION-MEMBER-EQL",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_member_eql,
	    STATIC_FUNCTION(evaluation_member_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qmember),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_member_eql));
    evaluation_member_eq_1 = STATIC_FUNCTION(evaluation_member_eq,NIL,
	    FALSE,2,2);
    temp = get_symbol_properties_function(Qmember);
    set_property_value_function(temp,Qdefined_evaluation_type_eq,
	    evaluation_member_eq_1);
    Qwrite_evaluation_member = STATIC_SYMBOL("WRITE-EVALUATION-MEMBER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_member,
	    STATIC_FUNCTION(write_evaluation_member,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qmember),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_member));
    Qg2_defstruct_structure_name_uuid_block_g2_struct = 
	    STATIC_SYMBOL("UUID-BLOCK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Quuid_block = STATIC_SYMBOL("UUID-BLOCK",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_uuid_block_g2_struct,
	    Quuid_block,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Quuid_block,
	    Qg2_defstruct_structure_name_uuid_block_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_uuid_block == UNBOUND)
	The_type_description_of_uuid_block = Nil;
    string_constant_52 = 
	    STATIC_STRING("43Dy8m83oQy1n83oQy8n8k1l8n0000001m1n8y83-6Gy1m83-G7y83-G6y1m83My83-BFykok0k0");
    temp = The_type_description_of_uuid_block;
    The_type_description_of_uuid_block = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_52));
    mutate_global_property(Qg2_defstruct_structure_name_uuid_block_g2_struct,
	    The_type_description_of_uuid_block,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Quuid_block,The_type_description_of_uuid_block,
	    Qtype_description_of_type);
    Qoutstanding_uuid_block_count = 
	    STATIC_SYMBOL("OUTSTANDING-UUID-BLOCK-COUNT",AB_package);
    Quuid_block_structure_memory_usage = 
	    STATIC_SYMBOL("UUID-BLOCK-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_53 = STATIC_STRING("1q83oQy8s83-w+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_uuid_block_count);
    push_optimized_constant(Quuid_block_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_53));
    Qchain_of_available_uuid_blocks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UUID-BLOCKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_uuid_blocks,
	    Chain_of_available_uuid_blocks);
    record_system_variable(Qchain_of_available_uuid_blocks,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Quuid_block_count = STATIC_SYMBOL("UUID-BLOCK-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_block_count,Uuid_block_count);
    record_system_variable(Quuid_block_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_uuid_blocks_vector == UNBOUND)
	Chain_of_available_uuid_blocks_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Quuid_block_structure_memory_usage,
	    STATIC_FUNCTION(uuid_block_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_uuid_block_count,
	    STATIC_FUNCTION(outstanding_uuid_block_count,NIL,FALSE,0,0));
    reclaim_structure_for_uuid_block_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_uuid_block,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Quuid_block,
	    reclaim_structure_for_uuid_block_1);
    Qmutate_uuid_block_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-UUID-BLOCK-HASH-SKIP-LIST-ENTRY",AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_uuid_block_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_uuid_block_hash_skip_list_entry,NIL,
	    FALSE,3,3));
    Fp_mutate_uuid_block_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_uuid_block_hash_skip_list_entry);
    Quuid_eq = STATIC_SYMBOL("UUID=",AB_package);
    Quuid_block_hash = STATIC_SYMBOL("UUID-BLOCK-HASH",AB_package);
    Quuid_block_hash_table = STATIC_SYMBOL("UUID-BLOCK-HASH-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_block_hash_table,Uuid_block_hash_table);
    Qmake_uuid_block_hash_function = 
	    STATIC_SYMBOL("MAKE-UUID-BLOCK-HASH-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_uuid_block_hash_function,
	    STATIC_FUNCTION(make_uuid_block_hash_function,NIL,FALSE,0,0));
    list_constant_19 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_uuid_block_hash_function);
    Qreclaim_uuid_block_hash_table = 
	    STATIC_SYMBOL("RECLAIM-UUID-BLOCK-HASH-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_uuid_block_hash_table,
	    STATIC_FUNCTION(reclaim_uuid_block_hash_table,NIL,FALSE,1,1));
    record_system_variable(Quuid_block_hash_table,Qtypes,list_constant_19,
	    Qnil,Qnil,Qreclaim_uuid_block_hash_table,Qt);
    Quuid_hash_block_table_for_merge_kb = 
	    STATIC_SYMBOL("UUID-HASH-BLOCK-TABLE-FOR-MERGE-KB",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_hash_block_table_for_merge_kb,
	    Uuid_hash_block_table_for_merge_kb);
    record_system_variable(Quuid_hash_block_table_for_merge_kb,Qtypes,
	    list_constant_19,Qnil,Qnil,Qreclaim_uuid_block_hash_table,Qt);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    gensymed_symbol = Qitem_reference;
    temp = Defined_evaluation_value_types;
    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qitem_reference);
    temp_1 = adjoin(2,Qitem_reference,Defined_evaluation_datum_types);
    Defined_evaluation_datum_types = temp_1;
    list_constant_20 = STATIC_CONS(Qitem_reference,Qnil);
    set_property_value_function(get_symbol_properties_function(Qitem_reference),
	    Qtype_specification_of_defined_evaluation_type,list_constant_20);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Quuid_block_table_size = STATIC_SYMBOL("UUID-BLOCK-TABLE-SIZE",AB_package);
    SET_SYMBOL_VALUE(Quuid_block_table_size,FIX((SI_Long)256L));
    Qitem_reference_table_list_length_limit = 
	    STATIC_SYMBOL("ITEM-REFERENCE-TABLE-LIST-LENGTH-LIMIT",AB_package);
    SET_SYMBOL_VALUE(Qitem_reference_table_list_length_limit,
	    FIX((SI_Long)10L));
    Quuid_string_length = STATIC_SYMBOL("UUID-STRING-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Quuid_string_length,FIX((SI_Long)8L));
    if (Lazy_assignment_of_uuids == UNBOUND)
	Lazy_assignment_of_uuids = T;
    Qreclaim_evaluation_item_reference = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_item_reference,
	    STATIC_FUNCTION(reclaim_evaluation_item_reference,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qitem_reference),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_item_reference));
    Qcopy_evaluation_item_reference = 
	    STATIC_SYMBOL("COPY-EVALUATION-ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_item_reference,
	    STATIC_FUNCTION(copy_evaluation_item_reference,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qitem_reference),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_item_reference));
    Qevaluation_item_reference_eql = 
	    STATIC_SYMBOL("EVALUATION-ITEM-REFERENCE-EQL",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_item_reference_eql,
	    STATIC_FUNCTION(evaluation_item_reference_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qitem_reference),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_item_reference_eql));
    evaluation_item_reference_eq_1 = 
	    STATIC_FUNCTION(evaluation_item_reference_eq,NIL,FALSE,2,2);
    temp = get_symbol_properties_function(Qitem_reference);
    set_property_value_function(temp,Qdefined_evaluation_type_eq,
	    evaluation_item_reference_eq_1);
    string_constant_1 = STATIC_STRING("item-reference (");
    string_constant_2 = STATIC_STRING(")");
    Qwrite_evaluation_item_reference = 
	    STATIC_SYMBOL("WRITE-EVALUATION-ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_item_reference,
	    STATIC_FUNCTION(write_evaluation_item_reference,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qitem_reference),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_item_reference));
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    if (Collecting_denotation_errors_p == UNBOUND)
	Collecting_denotation_errors_p = Nil;
    if (Denotation_error_list == UNBOUND)
	Denotation_error_list = Nil;
    Qthe_item_having_uuid = STATIC_SYMBOL("THE-ITEM-HAVING-UUID",AB_package);
    SET_SYMBOL_FUNCTION(Qthe_item_having_uuid,
	    STATIC_FUNCTION(the_item_having_uuid,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Quuid_eq,STATIC_FUNCTION(uuid_eq,NIL,FALSE,2,2));
    string_constant_3 = STATIC_STRING("UUID");
    string_constant_4 = STATIC_STRING("illegal character (~c) in a ~a string");
    string_constant_5 = 
	    STATIC_STRING("a ~a string must be ~d hex digits, but this has ~d");
    string_constant_6 = 
	    STATIC_STRING("a ~a string must have a total number of hex digits that is a multiple of four");
    Qeq_item_hash_table_reclaimer = 
	    STATIC_SYMBOL("EQ-ITEM-HASH-TABLE-RECLAIMER",AB_package);
    SET_SYMBOL_FUNCTION(Qeq_item_hash_table_reclaimer,
	    STATIC_FUNCTION(eq_item_hash_table_reclaimer,NIL,FALSE,1,1));
    if (Bogus_value_for_default == UNBOUND)
	Bogus_value_for_default = CONS(Nil,Nil);
    gensymed_symbol = Qsequence;
    temp = Defined_evaluation_value_types;
    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qsequence);
    temp_1 = adjoin(2,Qsequence,Defined_evaluation_datum_types);
    Defined_evaluation_datum_types = temp_1;
    list_constant_7 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qsequence),
	    Qtype_specification_of_defined_evaluation_type,list_constant_7);
    Qreclaim_evaluation_sequence = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_sequence,
	    STATIC_FUNCTION(reclaim_evaluation_sequence,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qsequence),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_sequence));
    Qcopy_evaluation_sequence = STATIC_SYMBOL("COPY-EVALUATION-SEQUENCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_sequence,
	    STATIC_FUNCTION(copy_evaluation_sequence,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qsequence),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_sequence));
    Qdeep_copy_evaluation_sequence = 
	    STATIC_SYMBOL("DEEP-COPY-EVALUATION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeep_copy_evaluation_sequence,
	    STATIC_FUNCTION(deep_copy_evaluation_sequence,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qsequence),
	    Qdefined_evaluation_type_deep_copier,
	    SYMBOL_FUNCTION(Qdeep_copy_evaluation_sequence));
    Qg2_get_position_of_element_in_sequence = 
	    STATIC_SYMBOL("G2-GET-POSITION-OF-ELEMENT-IN-SEQUENCE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_position_of_element_in_sequence,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_position_of_element_in_sequence,
	    STATIC_FUNCTION(g2_get_position_of_element_in_sequence,NIL,
	    FALSE,2,2));
    Qevaluation_sequence_eql = STATIC_SYMBOL("EVALUATION-SEQUENCE-EQL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_sequence_eql,
	    STATIC_FUNCTION(evaluation_sequence_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qsequence),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_sequence_eql));
    evaluation_sequence_eq_1 = STATIC_FUNCTION(evaluation_sequence_eq,NIL,
	    FALSE,2,2);
    temp = get_symbol_properties_function(Qsequence);
    set_property_value_function(temp,Qdefined_evaluation_type_eq,
	    evaluation_sequence_eq_1);
    if (Evaluation_value_indentation_depth == UNBOUND)
	Evaluation_value_indentation_depth = FIX((SI_Long)0L);
    if (Evaluation_value_writing_target_length_qm == UNBOUND)
	Evaluation_value_writing_target_length_qm = Nil;
    if (Indent_sequences_and_structures_p == UNBOUND)
	Indent_sequences_and_structures_p = T;
    string_constant_7 = STATIC_STRING("sequence (");
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING(",~%");
    array_constant_2 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_evaluation_sequence = STATIC_SYMBOL("WRITE-EVALUATION-SEQUENCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_sequence,
	    STATIC_FUNCTION(write_evaluation_sequence,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qsequence),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_sequence));
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qsequence,Qitem_or_datum);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    gensymed_symbol = Qab_structure;
    temp = Defined_evaluation_value_types;
    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qab_structure);
    temp_1 = adjoin(2,Qab_structure,Defined_evaluation_datum_types);
    Defined_evaluation_datum_types = temp_1;
    list_constant_8 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qab_structure),
	    Qtype_specification_of_defined_evaluation_type,list_constant_8);
    Qreclaim_evaluation_structure = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_structure,
	    STATIC_FUNCTION(reclaim_evaluation_structure,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qab_structure),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_structure));
    Qcopy_evaluation_structure = STATIC_SYMBOL("COPY-EVALUATION-STRUCTURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_structure,
	    STATIC_FUNCTION(copy_evaluation_structure,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qab_structure),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_structure));
    Qdeep_copy_evaluation_structure = 
	    STATIC_SYMBOL("DEEP-COPY-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeep_copy_evaluation_structure,
	    STATIC_FUNCTION(deep_copy_evaluation_structure,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qab_structure),
	    Qdefined_evaluation_type_deep_copier,
	    SYMBOL_FUNCTION(Qdeep_copy_evaluation_structure));
    array_constant_4 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_evaluation_structure = 
	    STATIC_SYMBOL("WRITE-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_structure,
	    STATIC_FUNCTION(write_evaluation_structure,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qab_structure),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_structure));
    Qevaluation_structure_eql = STATIC_SYMBOL("EVALUATION-STRUCTURE-EQL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_structure_eql,
	    STATIC_FUNCTION(evaluation_structure_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qab_structure),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_structure_eql));
    evaluation_structure_eq_1 = STATIC_FUNCTION(evaluation_structure_eq,
	    NIL,FALSE,2,2);
    temp = get_symbol_properties_function(Qab_structure);
    set_property_value_function(temp,Qdefined_evaluation_type_eq,
	    evaluation_structure_eq_1);
    if (Maximum_number_of_slots_in_structure_type == UNBOUND)
	Maximum_number_of_slots_in_structure_type = FIX((SI_Long)25L);
    if (Boolean_composition_over_symbols_allows_top_level_symbols_p == UNBOUND)
	Boolean_composition_over_symbols_allows_top_level_symbols_p = T;
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qand,Qab_or);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_22 = STATIC_CONS(Qno_item,Qnil);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_22);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    list_constant_3 = STATIC_CONS(Qiteration_state,Qnil);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    gensymed_symbol = Qobsolete_datum;
    temp = Defined_evaluation_value_types;
    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qobsolete_datum);
    list_constant_23 = STATIC_CONS(Qobsolete_datum,Qnil);
    set_property_value_function(get_symbol_properties_function(Qobsolete_datum),
	    Qtype_specification_of_defined_evaluation_type,list_constant_23);
    Qreclaim_evaluation_obsolete_datum = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-OBSOLETE-DATUM",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_obsolete_datum,
	    STATIC_FUNCTION(reclaim_evaluation_obsolete_datum,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qobsolete_datum),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_obsolete_datum));
    Qcopy_evaluation_obsolete_datum = 
	    STATIC_SYMBOL("COPY-EVALUATION-OBSOLETE-DATUM",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_obsolete_datum,
	    STATIC_FUNCTION(copy_evaluation_obsolete_datum,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qobsolete_datum),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_obsolete_datum));
    Qdeep_copy_evaluation_obsolete_datum = 
	    STATIC_SYMBOL("DEEP-COPY-EVALUATION-OBSOLETE-DATUM",AB_package);
    SET_SYMBOL_FUNCTION(Qdeep_copy_evaluation_obsolete_datum,
	    STATIC_FUNCTION(deep_copy_evaluation_obsolete_datum,NIL,FALSE,
	    1,1));
    set_property_value_function(get_symbol_properties_function(Qobsolete_datum),
	    Qdefined_evaluation_type_deep_copier,
	    SYMBOL_FUNCTION(Qdeep_copy_evaluation_obsolete_datum));
    Qevaluation_obsolete_datum_eql = 
	    STATIC_SYMBOL("EVALUATION-OBSOLETE-DATUM-EQL",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_obsolete_datum_eql,
	    STATIC_FUNCTION(evaluation_obsolete_datum_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qobsolete_datum),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_obsolete_datum_eql));
    Qevaluation_value = STATIC_SYMBOL("EVALUATION-VALUE",AB_package);
    list_constant_4 = STATIC_CONS(Qab_structure,list_constant_7);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Type_specification_simple_expansion_prop = 
	    Qtype_specification_simple_expansion;
    Qtype_specification_explicit_complex_type = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-EXPLICIT-COMPLEX-TYPE",
	    AB_package);
    Type_specification_explicit_complex_type_prop = 
	    Qtype_specification_explicit_complex_type;
    Qtype_symbols_subtype_alist = 
	    STATIC_SYMBOL("TYPE-SYMBOLS-SUBTYPE-ALIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtype_symbols_subtype_alist,
	    Type_symbols_subtype_alist);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_24 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_27 = STATIC_LIST_STAR((SI_Long)9L,Qdatum,Qnumber,
	    Qinteger,Qlong,Qfloat,Qtext,Qtruth_value,Qboolean,
	    list_constant_24);
    list_constant_25 = STATIC_CONS(Qlong,Qnil);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)4L,Qnumber,Qinteger,
	    Qfloat,list_constant_25);
    list_constant_29 = STATIC_CONS(Qinteger,Qnil);
    list_constant_30 = STATIC_CONS(Qfloat,Qnil);
    list_constant_31 = STATIC_CONS(Qtext,Qnil);
    list_constant_26 = STATIC_CONS(Qboolean,Qnil);
    list_constant_32 = STATIC_CONS(Qtruth_value,list_constant_26);
    list_constant_33 = STATIC_CONS(Qitem_or_datum,list_constant_27);
    list_constant_34 = STATIC_CONS(Qevaluation_value,list_constant_27);
    list_constant_35 = STATIC_LIST((SI_Long)11L,list_constant_27,
	    list_constant_28,list_constant_29,list_constant_25,
	    list_constant_30,list_constant_31,list_constant_32,
	    list_constant_26,list_constant_24,list_constant_33,
	    list_constant_34);
    SET_SYMBOL_VALUE(Qtype_symbols_subtype_alist,list_constant_35);
    Qtype_specification_for_item = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-FOR-ITEM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtype_specification_for_item,
	    Type_specification_for_item);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    SET_SYMBOL_VALUE(Qtype_specification_for_item,list_constant_36);
    Qtype_specification_for_iteration_state = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-FOR-ITERATION-STATE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtype_specification_for_iteration_state,
	    Type_specification_for_iteration_state);
    SET_SYMBOL_VALUE(Qtype_specification_for_iteration_state,list_constant_3);
    Qtype_specification_for_unknown = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-FOR-UNKNOWN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtype_specification_for_unknown,
	    Type_specification_for_unknown);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_37 = STATIC_CONS(Qunknown_datum,Qnil);
    SET_SYMBOL_VALUE(Qtype_specification_for_unknown,list_constant_37);
    Qtype_specification_for_no_item = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-FOR-NO-ITEM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtype_specification_for_no_item,
	    Type_specification_for_no_item);
    SET_SYMBOL_VALUE(Qtype_specification_for_no_item,list_constant_22);
    Qno_item_implies_unknown = STATIC_SYMBOL("NO-ITEM-IMPLIES-UNKNOWN",
	    AB_package);
    list_constant_5 = STATIC_CONS(Qno_item_implies_unknown,Qnil);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    Qaction_cache = STATIC_SYMBOL("ACTION-CACHE",AB_package);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)10L,Qnumber,Qinteger,
	    Qlong,Qfloat,Qsymbol,Qtruth_value,Qtext,Qdatum,Qitem_or_datum,
	    list_constant_4);
    if (Internal_g2_element_types_that_can_contain_datum == UNBOUND)
	Internal_g2_element_types_that_can_contain_datum = list_constant_38;
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    list_constant_39 = STATIC_LIST_STAR((SI_Long)10L,Qquantity,Qinteger,
	    Qlong,Qfloat,Qsymbol,Qtruth_value,Qtext,Qvalue,Qitem_or_value,
	    list_constant_4);
    if (G2_element_types_that_can_contain_datum == UNBOUND)
	G2_element_types_that_can_contain_datum = list_constant_39;
    Qcategory_is_not_g2_element_datum_type = 
	    STATIC_SYMBOL("CATEGORY-IS-NOT-G2-ELEMENT-DATUM-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qcategory_is_not_g2_element_datum_type,
	    STATIC_FUNCTION(category_is_not_g2_element_datum_type,NIL,
	    FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qcategory_is_not_g2_element_datum_type);
    array_constant_6 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    Qsingular_of_numeric_data_type = 
	    STATIC_SYMBOL("*SINGULAR-OF-NUMERIC-DATA-TYPE*",AB_package);
    Kb_specific_property_names = CONS(Qsingular_of_numeric_data_type,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qsingular_of_numeric_data_type,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Star_singular_of_numeric_data_type_star_kbprop = 
	    Qsingular_of_numeric_data_type;
    array_constant_8 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)57344L);
    Qcm = STATIC_SYMBOL(",",AB_package);
    string_constant_9 = STATIC_STRING("none");
    array_constant_10 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    string_constant_10 = STATIC_STRING("-.");
    string_constant_11 = STATIC_STRING(".");
    array_constant_12 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    string_constant_12 = STATIC_STRING("");
    string_constant_13 = STATIC_STRING("~a...");
    array_constant_15 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)57344L);
    Qf = STATIC_SYMBOL("F",AB_package);
    array_constant_18 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)57344L);
    Qc = STATIC_SYMBOL("C",AB_package);
    array_constant_19 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)57344L);
    Qpure_number = STATIC_SYMBOL("PURE-NUMBER",AB_package);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)5L,Qnumber,Qpure_number,
	    Qinteger,Qlong,list_constant_30);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_20 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)23L,(SI_Long)57344L);
    string_constant_14 = 
	    STATIC_STRING("a thing which satisfies the predicate ~a");
    array_constant_23 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)30L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)33L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)39L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)23L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)26L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)28L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)29L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)34L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)35L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)40L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)42L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)43L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)44L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)46L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)47L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)49L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)50L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)51L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)52L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)54L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)55L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)57L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)58L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)59L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)60L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)61L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)62L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)63L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)78L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)79L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)57344L);
    string_constant_15 = STATIC_STRING("~NV, ");
    string_constant_16 = STATIC_STRING("~NV, or ");
    string_constant_17 = STATIC_STRING("~NV or ");
    string_constant_18 = STATIC_STRING("~NV");
    array_constant_29 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)57344L);
    string_constant_19 = 
	    STATIC_STRING(" with at least ~D, and less than ~D elements of type ");
    string_constant_20 = STATIC_STRING(" with at least ~D element~a of type ");
    string_constant_21 = STATIC_STRING("s");
    string_constant_22 = STATIC_STRING(" with elements of type ");
    array_constant_30 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    array_constant_31 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)18L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)23L,(SI_Long)57344L);
    string_constant_23 = STATIC_STRING("~(~a~): ~NT");
    array_constant_32 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)57344L);
    array_constant_33 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)23L,(SI_Long)57344L);
    array_constant_36 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)57344L);
    string_constant_24 = STATIC_STRING(" ~a ");
    array_constant_37 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)57344L);
    array_constant_38 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)57344L);
    array_constant_39 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)15L,(SI_Long)57344L);
    array_constant_40 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)57344L);
    array_constant_41 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)57344L);
    array_constant_42 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)15L,(SI_Long)57344L);
    array_constant_43 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)15L,(SI_Long)57344L);
    array_constant_44 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)57344L);
    array_constant_45 = STATIC_ARRAY(list_constant_21,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)15L,(SI_Long)57344L);
    string_constant_25 = STATIC_STRING(", ~(~a~) ");
    string_constant_26 = STATIC_STRING(" ~(~a~) ");
    Qev_hash_version = STATIC_SYMBOL("EV-HASH-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_version,FIX((SI_Long)1L));
    Qev_hash_null_code = STATIC_SYMBOL("EV-HASH-NULL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_null_code,FIX((SI_Long)1L));
    Qev_hash_integer_code = STATIC_SYMBOL("EV-HASH-INTEGER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_integer_code,FIX((SI_Long)2L));
    Qev_hash_float_code = STATIC_SYMBOL("EV-HASH-FLOAT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_float_code,FIX((SI_Long)3L));
    Qev_hash_symbol_code = STATIC_SYMBOL("EV-HASH-SYMBOL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_symbol_code,FIX((SI_Long)4L));
    Qev_hash_text_code = STATIC_SYMBOL("EV-HASH-TEXT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_text_code,FIX((SI_Long)5L));
    Qev_hash_truth_value_code = STATIC_SYMBOL("EV-HASH-TRUTH-VALUE-CODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qev_hash_truth_value_code,FIX((SI_Long)6L));
    Qev_hash_sequence_code = STATIC_SYMBOL("EV-HASH-SEQUENCE-CODE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_sequence_code,FIX((SI_Long)7L));
    Qev_hash_structure_code = STATIC_SYMBOL("EV-HASH-STRUCTURE-CODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qev_hash_structure_code,FIX((SI_Long)8L));
    Qev_hash_long_code = STATIC_SYMBOL("EV-HASH-LONG-CODE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_long_code,FIX((SI_Long)9L));
    Qev_hash_buffer_size = STATIC_SYMBOL("EV-HASH-BUFFER-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qev_hash_buffer_size,FIX((SI_Long)8L));
    Qsymbol_name_wide_string = STATIC_SYMBOL("SYMBOL-NAME-WIDE-STRING",
	    AB_package);
    string_constant_54 = STATIC_STRING("NO-COMPONENT-VALUE");
    No_component_value = make_symbol(string_constant_54);
    Qcomponent_kind_description = 
	    STATIC_SYMBOL("COMPONENT-KIND-DESCRIPTION",AB_package);
    Component_kind_description_prop = Qcomponent_kind_description;
    if (Set_of_all_component_kinds == UNBOUND)
	Set_of_all_component_kinds = Nil;
    Qattribute_mimic = STATIC_SYMBOL("ATTRIBUTE-MIMIC",AB_package);
    Attribute_mimic_prop = Qattribute_mimic;
    Qattribute_mimics_of_class = STATIC_SYMBOL("ATTRIBUTE-MIMICS-OF-CLASS",
	    AB_package);
    Attribute_mimics_of_class_prop = Qattribute_mimics_of_class;
    if (The_type_description_of_attribute_mimic == UNBOUND)
	The_type_description_of_attribute_mimic = Nil;
    string_constant_55 = 
	    STATIC_STRING("43Dy8m83fBy1m83fBy8k1l8k0000001m1m83*gy9k1n8y83-2ny1p83pty83pxy83pvy83puy83pwykpk0k0");
    temp = The_type_description_of_attribute_mimic;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_attribute_mimic = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_55));
    Qg2_defstruct_structure_name_attribute_mimic_g2_struct = 
	    STATIC_SYMBOL("ATTRIBUTE-MIMIC-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_attribute_mimic_g2_struct,
	    The_type_description_of_attribute_mimic,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qattribute_mimic,
	    The_type_description_of_attribute_mimic,Qtype_description_of_type);
    Qoutstanding_attribute_mimic_count = 
	    STATIC_SYMBOL("OUTSTANDING-ATTRIBUTE-MIMIC-COUNT",AB_package);
    Qattribute_mimic_structure_memory_usage = 
	    STATIC_SYMBOL("ATTRIBUTE-MIMIC-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_56 = STATIC_STRING("1q83fBy8s83-K2y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_attribute_mimic_count);
    push_optimized_constant(Qattribute_mimic_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_56));
    Qchain_of_available_attribute_mimics = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ATTRIBUTE-MIMICS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_attribute_mimics,
	    Chain_of_available_attribute_mimics);
    record_system_variable(Qchain_of_available_attribute_mimics,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qattribute_mimic_count = STATIC_SYMBOL("ATTRIBUTE-MIMIC-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_mimic_count,Attribute_mimic_count);
    record_system_variable(Qattribute_mimic_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_attribute_mimics_vector == UNBOUND)
	Chain_of_available_attribute_mimics_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qattribute_mimic_structure_memory_usage,
	    STATIC_FUNCTION(attribute_mimic_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_attribute_mimic_count,
	    STATIC_FUNCTION(outstanding_attribute_mimic_count,NIL,FALSE,0,0));
    reclaim_structure_for_attribute_mimic_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_attribute_mimic,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qattribute_mimic,
	    reclaim_structure_for_attribute_mimic_1);
    Qg2_defstruct_structure_name_virtual_attribute_g2_struct = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_virtual_attribute_g2_struct,
	    Qvirtual_attribute,Qab_name_of_unique_structure_type);
    mutate_global_property(Qvirtual_attribute,
	    Qg2_defstruct_structure_name_virtual_attribute_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_virtual_attribute == UNBOUND)
	The_type_description_of_virtual_attribute = Nil;
    Qprint_virtual_attribute = STATIC_SYMBOL("PRINT-VIRTUAL-ATTRIBUTE",
	    AB_package);
    string_constant_57 = 
	    STATIC_STRING("43Dy8m83oUy1n83oUy8n8k1l8n0000001m1n8y83-6Hy1r83-Gay83-GWy83-Gcy83-GXy83-GZy83-GYy83-Gby1m83=0y9kksk0k0");
    temp = The_type_description_of_virtual_attribute;
    clear_optimized_constants();
    push_optimized_constant(Qprint_virtual_attribute);
    The_type_description_of_virtual_attribute = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_57));
    mutate_global_property(Qg2_defstruct_structure_name_virtual_attribute_g2_struct,
	    The_type_description_of_virtual_attribute,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qvirtual_attribute,
	    The_type_description_of_virtual_attribute,
	    Qtype_description_of_type);
    Qoutstanding_virtual_attribute_count = 
	    STATIC_SYMBOL("OUTSTANDING-VIRTUAL-ATTRIBUTE-COUNT",AB_package);
    Qvirtual_attribute_structure_memory_usage = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_58 = STATIC_STRING("1q83oUy8s83-wcy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_virtual_attribute_count);
    push_optimized_constant(Qvirtual_attribute_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_58));
    Qchain_of_available_virtual_attributes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-VIRTUAL-ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_virtual_attributes,
	    Chain_of_available_virtual_attributes);
    record_system_variable(Qchain_of_available_virtual_attributes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qvirtual_attribute_count = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvirtual_attribute_count,
	    Virtual_attribute_count);
    record_system_variable(Qvirtual_attribute_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_virtual_attributes_vector == UNBOUND)
	Chain_of_available_virtual_attributes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qvirtual_attribute_structure_memory_usage,
	    STATIC_FUNCTION(virtual_attribute_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_virtual_attribute_count,
	    STATIC_FUNCTION(outstanding_virtual_attribute_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_virtual_attribute_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_virtual_attribute,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qvirtual_attribute,
	    reclaim_structure_for_virtual_attribute_1);
    SET_SYMBOL_FUNCTION(Qprint_virtual_attribute,
	    STATIC_FUNCTION(print_virtual_attribute,NIL,FALSE,3,3));
    Virtual_attribute_prop = Qvirtual_attribute;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    Virtual_attributes_local_to_class_prop = 
	    Qvirtual_attributes_local_to_class;
    if (Virtual_attributes_not_local_to_a_class == UNBOUND)
	Virtual_attributes_not_local_to_a_class = Nil;
    if (All_virtual_attributes == UNBOUND)
	All_virtual_attributes = Nil;
    Qdeprecated = STATIC_SYMBOL("DEPRECATED",AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant_27 = 
	    STATIC_STRING("The attribute ~a of ~NF is read-only.");
    string_constant_28 = STATIC_STRING("No attribute named ~a exists in ~NF.");
    temp_1 = adjoin(2,Qvirtual_attribute,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp_1;
    Kgetter = STATIC_SYMBOL("GETTER",Pkeyword);
    Qget_virtual_attribute_component = 
	    STATIC_SYMBOL("GET-VIRTUAL-ATTRIBUTE-COMPONENT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_virtual_attribute_component,
	    STATIC_FUNCTION(get_virtual_attribute_component,NIL,FALSE,2,2));
    Ksetter = STATIC_SYMBOL("SETTER",Pkeyword);
    Qset_virtual_attribute_component = 
	    STATIC_SYMBOL("SET-VIRTUAL-ATTRIBUTE-COMPONENT",AB_package);
    SET_SYMBOL_FUNCTION(Qset_virtual_attribute_component,
	    STATIC_FUNCTION(set_virtual_attribute_component,NIL,FALSE,3,3));
    temp = get_symbol_properties_function(Qvirtual_attribute);
    set_property_value_function(temp,Qcomponent_kind_description,
	    LIST_4(Kgetter,
	    SYMBOL_FUNCTION(Qget_virtual_attribute_component),Ksetter,
	    SYMBOL_FUNCTION(Qset_virtual_attribute_component)));
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Category_evaluator_interface_prop = Qcategory_evaluator_interface;
    Qg2_defstruct_structure_name_category_evaluator_interface_g2_struct = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_category_evaluator_interface_g2_struct,
	    Qcategory_evaluator_interface,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcategory_evaluator_interface,
	    Qg2_defstruct_structure_name_category_evaluator_interface_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_category_evaluator_interface == UNBOUND)
	The_type_description_of_category_evaluator_interface = Nil;
    string_constant_59 = 
	    STATIC_STRING("43Dy8m83fdy1n83fdy8n8k1l8n0000001l1n8y83-32y1l83raykok0k0");
    temp = The_type_description_of_category_evaluator_interface;
    The_type_description_of_category_evaluator_interface = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_59));
    mutate_global_property(Qg2_defstruct_structure_name_category_evaluator_interface_g2_struct,
	    The_type_description_of_category_evaluator_interface,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcategory_evaluator_interface,
	    The_type_description_of_category_evaluator_interface,
	    Qtype_description_of_type);
    Qoutstanding_category_evaluator_interface_count = 
	    STATIC_SYMBOL("OUTSTANDING-CATEGORY-EVALUATOR-INTERFACE-COUNT",
	    AB_package);
    Qcategory_evaluator_interface_structure_memory_usage = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_60 = STATIC_STRING("1q83fdy8s83-Ldy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_category_evaluator_interface_count);
    push_optimized_constant(Qcategory_evaluator_interface_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_60));
    Qchain_of_available_category_evaluator_interfaces = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CATEGORY-EVALUATOR-INTERFACES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_category_evaluator_interfaces,
	    Chain_of_available_category_evaluator_interfaces);
    record_system_variable(Qchain_of_available_category_evaluator_interfaces,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcategory_evaluator_interface_count = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcategory_evaluator_interface_count,
	    Category_evaluator_interface_count);
    record_system_variable(Qcategory_evaluator_interface_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_category_evaluator_interfaces_vector == UNBOUND)
	Chain_of_available_category_evaluator_interfaces_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcategory_evaluator_interface_structure_memory_usage,
	    STATIC_FUNCTION(category_evaluator_interface_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_category_evaluator_interface_count,
	    STATIC_FUNCTION(outstanding_category_evaluator_interface_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_category_evaluator_interface_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_category_evaluator_interface,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcategory_evaluator_interface,
	    reclaim_structure_for_category_evaluator_interface_1);
    Qstructure_slot_not_bound = STATIC_SYMBOL("STRUCTURE-SLOT-NOT-BOUND",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstructure_slot_not_bound,
	    Structure_slot_not_bound);
    list_constant_40 = STATIC_CONS(Qstructure_slot_not_bound,Qnil);
    if (Structure_slot_not_bound == UNBOUND)
	Structure_slot_not_bound = list_constant_40;
    if (Reason_for_type_failure == UNBOUND)
	Reason_for_type_failure = Nil;
    if (Type_at_type_failure == UNBOUND)
	Type_at_type_failure = Nil;
    if (Value_at_type_failure == UNBOUND)
	Value_at_type_failure = Nil;
    if (Context_of_type_failure == UNBOUND)
	Context_of_type_failure = Nil;
    if (Last_slot_checked_of_type_failure == UNBOUND)
	Last_slot_checked_of_type_failure = Nil;
    if (Structure_specs_allow_unknown_slots_p == UNBOUND)
	Structure_specs_allow_unknown_slots_p = Nil;
    if (Current_category_name_for_type_specification_type_p == UNBOUND)
	Current_category_name_for_type_specification_type_p = Nil;
    Qtype_mismatch = STATIC_SYMBOL("TYPE-MISMATCH",AB_package);
    Qdefault_overrides_for_class_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS",
	    AB_package);
    Qdefault_overrides_for_object_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS",
	    AB_package);
    Quser_attribute_name = STATIC_SYMBOL("USER-ATTRIBUTE-NAME",AB_package);
    Qsystem_attribute_designation = 
	    STATIC_SYMBOL("SYSTEM-ATTRIBUTE-DESIGNATION",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Quser_attribute_name,
	    Qsystem_attribute_designation);
    Qrestrict_proprietary_items_and_configure_user_interface_statement = 
	    STATIC_SYMBOL("RESTRICT-PROPRIETARY-ITEMS-AND-CONFIGURE-USER-INTERFACE-STATEMENT",
	    AB_package);
    Qoperation_type = STATIC_SYMBOL("OPERATION-TYPE",AB_package);
    list_constant_10 = STATIC_CONS(Qoperation_type,Qnil);
    Qsimple_type_mismatch = STATIC_SYMBOL("SIMPLE-TYPE-MISMATCH",AB_package);
    Qneither_uan_nor_sad_present = 
	    STATIC_SYMBOL("NEITHER-UAN-NOR-SAD-PRESENT",AB_package);
    Qinvalid_operation_type = STATIC_SYMBOL("INVALID-OPERATION-TYPE",
	    AB_package);
    Qstructure_choose_type_mismatch = 
	    STATIC_SYMBOL("STRUCTURE-CHOOSE-TYPE-MISMATCH",AB_package);
    Qsequence_too_short = STATIC_SYMBOL("SEQUENCE-TOO-SHORT",AB_package);
    Qsequence_too_long = STATIC_SYMBOL("SEQUENCE-TOO-LONG",AB_package);
    Qconstrain_movement_of_items = 
	    STATIC_SYMBOL("CONSTRAIN-MOVEMENT-OF-ITEMS",AB_package);
    Qtype_of_region = STATIC_SYMBOL("TYPE-OF-REGION",AB_package);
    Qobject_configuration_spec = STATIC_SYMBOL("OBJECT-CONFIGURATION-SPEC",
	    AB_package);
    Qconstrained_region = STATIC_SYMBOL("CONSTRAINED-REGION",AB_package);
    Qclauses = STATIC_SYMBOL("CLAUSES",AB_package);
    Qunknown_extra_structure_slot = 
	    STATIC_SYMBOL("UNKNOWN-EXTRA-STRUCTURE-SLOT",AB_package);
    Qmissing_required_structure_slots = 
	    STATIC_SYMBOL("MISSING-REQUIRED-STRUCTURE-SLOTS",AB_package);
    string_constant_29 = STATIC_STRING("the type ~NT");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant_30 = STATIC_STRING("the ~(~A ~NF~)");
    string_constant_31 = STATIC_STRING("the value ~(~NV~)");
    string_constant_32 = STATIC_STRING("~%is not of ~A");
    string_constant_33 = STATIC_STRING("~%is not of the correct type");
    string_constant_34 = STATIC_STRING(",~%because a sequence was too short");
    string_constant_35 = STATIC_STRING(",~%because a sequence was too long");
    string_constant_36 = 
	    STATIC_STRING(",~%because at least one required structure slot was missing");
    string_constant_37 = 
	    STATIC_STRING(",~%because a structure contained neither the slot ~(~a~) nor the slot ~(~a~)");
    string_constant_38 = 
	    STATIC_STRING(",~%because a structure contained none of the following slots: ~(~L,|~)");
    string_constant_39 = 
	    STATIC_STRING(",~%because the required structure slot ~(~a~) was missing");
    string_constant_40 = 
	    STATIC_STRING(",~%because the structure slot ~(~a~) was not allowed, ~\n                                     because it was not one of ~(~L,|~)");
    string_constant_41 = 
	    STATIC_STRING(",~%because the required structure slot operation-type was not present");
    string_constant_42 = 
	    STATIC_STRING(",~%because the operation-type slot had an illegal value");
    string_constant_43 = 
	    STATIC_STRING(",~%because neither the structure slot user-attribute-name ~\n                            nor the structure system-attribute-designation was present");
    string_constant_44 = 
	    STATIC_STRING(",~%because ~(~NA~)~%was not of type ~NT");
    string_constant_45 = STATIC_STRING("~%The problem occurred ");
    list_constant_11 = STATIC_CONS(Qsequence,list_constant_8);
    string_constant_46 = STATIC_STRING(", ");
    string_constant_47 = STATIC_STRING("inside element ~D");
    string_constant_48 = STATIC_STRING("inside ~(~a~)");
    Qcategory_committer_function = 
	    STATIC_SYMBOL("CATEGORY-COMMITTER-FUNCTION",AB_package);
    Category_committer_function_prop = Qcategory_committer_function;
    Qcategory_extracter_function = 
	    STATIC_SYMBOL("CATEGORY-EXTRACTER-FUNCTION",AB_package);
    Category_extracter_function_prop = Qcategory_extracter_function;
    Qtext_category_evaluator_interface_p = 
	    STATIC_SYMBOL("TEXT-CATEGORY-EVALUATOR-INTERFACE-P",AB_package);
    Text_category_evaluator_interface_p_prop = 
	    Qtext_category_evaluator_interface_p;
}
