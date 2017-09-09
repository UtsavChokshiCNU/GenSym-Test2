/* mem-sp.c
 * Input file:  mem-sysproc.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "mem-sp.h"


Object Single_counter_slots_in_memory_profile = UNBOUND;

Object By_length_slots_in_memory_profile = UNBOUND;

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* WRITE-SLOT-VALUE-FOR-BY-LENGTH-ATTRIBUTE */
Object write_slot_value_for_by_length_attribute(by_length_attribute)
    Object by_length_attribute;
{
    Object length_1, count_1, ab_loop_list_, length_and_count_cons;
    Object last_length_and_count_p, ab_loop_iter_flag_, ab_loop_desetq_;

    x_note_fn_call(165,0);
    if (CONSP(by_length_attribute)) {
	length_1 = Nil;
	count_1 = Nil;
	ab_loop_list_ = by_length_attribute;
	length_and_count_cons = by_length_attribute;
	last_length_and_count_p = Nil;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	length_1 = CAR(ab_loop_desetq_);
	count_1 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    length_and_count_cons = M_CDR(length_and_count_cons);
	if ( !TRUEP(length_and_count_cons))
	    goto end_loop;
	last_length_and_count_p =  !TRUEP(CDR(length_and_count_cons)) ? T :
		 Nil;
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
	twrite_fixnum(length_1);
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)3L));
	twrite_fixnum(count_1);
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)1L));
	if ( !TRUEP(last_length_and_count_p))
	    twrite_line_separator();
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    else
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)4L));
    return VALUES_1(Nil);
}

/* WRITE-SIMPLE-GENERAL-ARRAYS-FROM-SLOT */
Object write_simple_general_arrays_from_slot(by_length_attribute,
	    gensymed_symbol)
    Object by_length_attribute, gensymed_symbol;
{
    x_note_fn_call(165,1);
    return write_slot_value_for_by_length_attribute(by_length_attribute);
}

/* WRITE-SIMPLE-UNSIGNED-BYTE-16-ARRAYS-FROM-SLOT */
Object write_simple_unsigned_byte_16_arrays_from_slot(by_length_attribute,
	    gensymed_symbol)
    Object by_length_attribute, gensymed_symbol;
{
    x_note_fn_call(165,2);
    return write_slot_value_for_by_length_attribute(by_length_attribute);
}

/* WRITE-SIMPLE-UNSIGNED-BYTE-8-ARRAYS-FROM-SLOT */
Object write_simple_unsigned_byte_8_arrays_from_slot(by_length_attribute,
	    gensymed_symbol)
    Object by_length_attribute, gensymed_symbol;
{
    x_note_fn_call(165,3);
    return write_slot_value_for_by_length_attribute(by_length_attribute);
}

/* WRITE-DOUBLE-FLOAT-ARRAYS-FROM-SLOT */
Object write_double_float_arrays_from_slot(by_length_attribute,gensymed_symbol)
    Object by_length_attribute, gensymed_symbol;
{
    x_note_fn_call(165,4);
    return write_slot_value_for_by_length_attribute(by_length_attribute);
}

/* WRITE-ADJUSTABLE-STRINGS-FROM-SLOT */
Object write_adjustable_strings_from_slot(by_length_attribute,gensymed_symbol)
    Object by_length_attribute, gensymed_symbol;
{
    x_note_fn_call(165,5);
    return write_slot_value_for_by_length_attribute(by_length_attribute);
}

/* WRITE-SIMPLE-STRINGS-FROM-SLOT */
Object write_simple_strings_from_slot(by_length_attribute,gensymed_symbol)
    Object by_length_attribute, gensymed_symbol;
{
    x_note_fn_call(165,6);
    return write_slot_value_for_by_length_attribute(by_length_attribute);
}

/* WRITE-FRAME-VECTORS-FROM-SLOT */
Object write_frame_vectors_from_slot(by_length_attribute,gensymed_symbol)
    Object by_length_attribute, gensymed_symbol;
{
    x_note_fn_call(165,7);
    return write_slot_value_for_by_length_attribute(by_length_attribute);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors, Qavailable_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors, Qcount_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors);

Object Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector = UNBOUND;

/* ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE */
Object items_encountered_in_memory_walk_hash_table_hash_vector_131_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(165,8);
    temp = 
	    Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)131L)));
    return VALUES_1(temp);
}

/* OUT-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR-131-VECTORS */
Object out_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors()
{
    Object temp;

    x_note_fn_call(165,9);
    temp = 
	    FIXNUM_MINUS(Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    length(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR-131-VECTOR-INTERNAL */
Object make_permanent_items_encountered_in_memory_walk_hash_table_hash_vector_131_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(165,10);
    atomic_incff_symval(Qcount_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)131L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR */
Object make_items_encountered_in_memory_walk_hash_table_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(165,11);
    if (ISVREF(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector,
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
		make_permanent_items_encountered_in_memory_walk_hash_table_hash_vector_131_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR */
Object reclaim_items_encountered_in_memory_walk_hash_table_hash_vector(items_encountered_in_memory_walk_hash_table_hash_vector_131_vector)
    Object items_encountered_in_memory_walk_hash_table_hash_vector_131_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(165,12);
    svref_arg_1 = 
	    Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector;
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
	    items_encountered_in_memory_walk_hash_table_hash_vector_131_vector;
    temp = 
	    ISVREF(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(165,13);
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

/* RECLAIM-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-TREE-FOR-HASH-NODES */
Object reclaim_items_encountered_in_memory_walk_hash_table_tree_for_hash_nodes(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list,
	    tail)
    Object items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list;
    Object tail;
{
    Object next_element, key, entry;

    x_note_fn_call(165,14);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list,
	    tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = 
	    ISVREF(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list,
	    (SI_Long)2L);
    entry = 
	    ISVREF(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list,
	    (SI_Long)3L);
    reclaim_skip_list_element(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list);
    items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list = 
	    next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-TREE */
Object clear_items_encountered_in_memory_walk_hash_table_tree(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list)
    Object items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(165,15);
    head = 
	    M_CAR(M_CDR(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_items_encountered_in_memory_walk_hash_table_tree_for_hash_nodes(element_qm,
		tail);
    return VALUES_1(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list);
}

static Object Qitems_encountered_in_memory_walk_hash_table_tree_for_hash;  /* items-encountered-in-memory-walk-hash-table-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-ITEMS-ENCOUNTERED-IN-MEMORY-WALK */
Object make_items_encountered_in_memory_walk()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(165,16);
    new_vector = 
	    make_items_encountered_in_memory_walk_hash_table_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    tail = 
	    make_items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = 
	    Qitems_encountered_in_memory_walk_hash_table_tree_for_hash;
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

/* FLATTEN-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE */
Object flatten_items_encountered_in_memory_walk_hash_table(items_encountered_in_memory_walk_hash_table_hash_table)
    Object items_encountered_in_memory_walk_hash_table_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(165,17);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    subtree = 
	    ISVREF(items_encountered_in_memory_walk_hash_table_hash_table,
	    index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-ITEMS-ENCOUNTERED-IN-MEMORY-WALK */
Object clear_items_encountered_in_memory_walk(items_encountered_in_memory_walk_hash_table_hash_table)
    Object items_encountered_in_memory_walk_hash_table_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(165,18);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    clear_items_encountered_in_memory_walk_hash_table_tree(ISVREF(items_encountered_in_memory_walk_hash_table_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE */
Object reclaim_items_encountered_in_memory_walk_hash_table(items_encountered_in_memory_walk_hash_table_hash_table)
    Object items_encountered_in_memory_walk_hash_table_hash_table;
{
    Object items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list;
    Object head, tail, element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(165,19);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list = 
	    ISVREF(items_encountered_in_memory_walk_hash_table_hash_table,
	    index_1);
    head = 
	    M_CAR(M_CDR(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_items_encountered_in_memory_walk_hash_table_tree_for_hash_nodes(element_qm,
		tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list) 
	    = Nil;
    M_CADR(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list) 
	    = Nil;
    M_CAR(items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list) 
	    = Nil;
    if (items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list) {
	last_1 = 
		items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list;
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
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = 
		    items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    items_encountered_in_memory_walk_hash_table_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(items_encountered_in_memory_walk_hash_table_hash_table,index_1) 
	    = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_items_encountered_in_memory_walk_hash_table_hash_vector(items_encountered_in_memory_walk_hash_table_hash_table);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Items_encountered_in_memory_walk, Qitems_encountered_in_memory_walk);

DEFINE_VARIABLE_WITH_SYMBOL(Subframe_depth, Qsubframe_depth);

DEFINE_VARIABLE_WITH_SYMBOL(Memory_walk_verbose_p, Qmemory_walk_verbose_p);

/* SUPPRESS-VERBOSITY-FOR-CONS-P */
Object suppress_verbosity_for_cons_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(165,20);
    if ( !TRUEP(thing) || text_string_p(thing) || SYMBOLP(thing) || 
	    NUMBERP(thing))
	temp = T;
    else if (ATOM(thing))
	temp = Nil;
    else
	temp = suppress_verbosity_for_cons_p(CAR(thing)) ? 
		suppress_verbosity_for_cons_p(CDR(thing)) : Qnil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_circularity_check_walking_through_conses_p, Qdo_circularity_check_walking_through_conses_p);

DEFINE_VARIABLE_WITH_SYMBOL(Do_circularity_check_walking_through_simple_vectors_p, Qdo_circularity_check_walking_through_simple_vectors_p);

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qsimple_strings;     /* simple-strings */

static Object Qadjustable_strings;  /* adjustable-strings */

static Object list_constant;       /* # */

static Object Qsimple_unsigned_byte_8_arrays;  /* simple-unsigned-byte-8-arrays */

static Object list_constant_1;     /* # */

static Object Qsimple_unsigned_byte_16_arrays;  /* simple-unsigned-byte-16-arrays */

static Object Qdouble_float_arrays;  /* double-float-arrays */

static Object Qsimple_general_arrays;  /* simple-general-arrays */

static Object Qitem_reference;     /* item-reference */

static Object Qconses;             /* conses */

static Object Qdouble_floats;      /* double-floats */

static Object Qsymbols;            /* symbols */

static Object Qfixnums;            /* fixnums */

static Object Qcharacters;         /* characters */

static Object Qfunctions;          /* functions */

static Object Qimmediates;         /* immediates */

/* WALK-FOR-MEMORY-RECURSION */
Object walk_for_memory_recursion(thing_to_walk,profile_object)
    Object thing_to_walk, profile_object;
{
    Object x2, temp_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_3, entry_hash, already_encountered_item_p;
    Object sub_class_bit_vector, stored_histories_qm, history_ring_buffer;
    Object incf_by_lengths_arg_1, list_kept_by_lengths;
    Object counter_for_this_length_qm, number_of_increments, incff_1_arg;
    Object temp_4, length_of_managed_array, already_encountered_item_qm;
    Object length_of_simple_array;
    SI_Long gensymed_symbol, temp_2, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, number_of_managed_buffers;
    SI_Long number_of_managed_buffers_minus_one, incf_by_lengths_arg_2;
    SI_Long incf_by_lengths_arg_1_1, index_1;
    char temp;
    Object result;

    x_note_fn_call(165,21);
    if ( !TRUEP(thing_to_walk))
	return VALUES_1(Nil);
    else {
	if (SIMPLE_VECTOR_P(thing_to_walk) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing_to_walk)) > 
		(SI_Long)2L &&  !EQ(ISVREF(thing_to_walk,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(thing_to_walk,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = SXHASH_SYMBOL_1(thing_to_walk) & 
		    IFIX(Most_positive_fixnum);
	    temp_1 = Items_encountered_in_memory_walk;
	    temp_2 = gensymed_symbol % (SI_Long)131L;
	    temp_1 = SVREF(temp_1,FIX(temp_2));
	    skip_list = CDR(temp_1);
	    key_value = thing_to_walk;
	    key_hash_value = gensymed_symbol;
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
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
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
	    already_encountered_item_p = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(already_encountered_item_p)) {
		gensymed_symbol = SXHASH_SYMBOL_1(thing_to_walk) & 
			IFIX(Most_positive_fixnum);
		temp_1 = Items_encountered_in_memory_walk;
		temp_2 = gensymed_symbol % (SI_Long)131L;
		set_skip_list_entry(SVREF(temp_1,FIX(temp_2)),
			FIX((SI_Long)31L),Qeq,Nil,T,thing_to_walk,
			FIX(gensymed_symbol),T);
		walk_frame_for_memory(thing_to_walk,profile_object);
	    }
	    sub_class_bit_vector = ISVREF(ISVREF(thing_to_walk,
		    (SI_Long)1L),(SI_Long)19L);
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
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		stored_histories_qm = ISVREF(thing_to_walk,(SI_Long)24L);
		if (stored_histories_qm) {
		    temp_1 = ISVREF(stored_histories_qm,(SI_Long)4L);
		    history_ring_buffer = CAR(temp_1);
		}
		else
		    history_ring_buffer = Nil;
		if (history_ring_buffer) {
		    walk_for_memory_recursion(history_ring_buffer,
			    profile_object);
		    walk_for_memory_recursion(ISVREF(history_ring_buffer,
			    (SI_Long)6L),profile_object);
		    walk_for_memory_recursion(ISVREF(history_ring_buffer,
			    (SI_Long)7L),profile_object);
		}
	    }
	}
	else if (SIMPLE_STRING_P(thing_to_walk)) {
	    incf_by_lengths_arg_1 = length(thing_to_walk);
	    list_kept_by_lengths = ISVREF(profile_object,(SI_Long)34L);
	    counter_for_this_length_qm = assoc_eql(incf_by_lengths_arg_1,
		    list_kept_by_lengths);
	    number_of_increments = Nil;
	    if (number_of_increments);
	    else
		number_of_increments = FIX((SI_Long)1L);
	    if (counter_for_this_length_qm) {
		incff_1_arg = number_of_increments;
		temp_4 = FIXNUM_ADD(CDR(counter_for_this_length_qm),
			incff_1_arg);
		M_CDR(counter_for_this_length_qm) = temp_4;
		list_kept_by_lengths;
	    }
	    else
		list_kept_by_lengths = 
			slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
			number_of_increments),list_kept_by_lengths);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(profile_object,Qsimple_strings);
	    SVREF(profile_object,FIX((SI_Long)34L)) = list_kept_by_lengths;
	}
	else if (STRINGP(thing_to_walk)) {
	    incf_by_lengths_arg_1 = length(thing_to_walk);
	    list_kept_by_lengths = ISVREF(profile_object,(SI_Long)33L);
	    counter_for_this_length_qm = assoc_eql(incf_by_lengths_arg_1,
		    list_kept_by_lengths);
	    number_of_increments = Nil;
	    if (number_of_increments);
	    else
		number_of_increments = FIX((SI_Long)1L);
	    if (counter_for_this_length_qm) {
		incff_1_arg = number_of_increments;
		temp_4 = FIXNUM_ADD(CDR(counter_for_this_length_qm),
			incff_1_arg);
		M_CDR(counter_for_this_length_qm) = temp_4;
		list_kept_by_lengths;
	    }
	    else
		list_kept_by_lengths = 
			slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
			number_of_increments),list_kept_by_lengths);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(profile_object,Qadjustable_strings);
	    SVREF(profile_object,FIX((SI_Long)33L)) = list_kept_by_lengths;
	}
	else {
	    if (SIMPLE_ARRAY_ANY_1_P(thing_to_walk)) {
		temp_1 = array_element_type(thing_to_walk);
		temp = EQUAL(list_constant,temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		incf_by_lengths_arg_1 = length(thing_to_walk);
		list_kept_by_lengths = ISVREF(profile_object,(SI_Long)31L);
		counter_for_this_length_qm = 
			assoc_eql(incf_by_lengths_arg_1,list_kept_by_lengths);
		number_of_increments = Nil;
		if (number_of_increments);
		else
		    number_of_increments = FIX((SI_Long)1L);
		if (counter_for_this_length_qm) {
		    incff_1_arg = number_of_increments;
		    temp_4 = FIXNUM_ADD(CDR(counter_for_this_length_qm),
			    incff_1_arg);
		    M_CDR(counter_for_this_length_qm) = temp_4;
		    list_kept_by_lengths;
		}
		else
		    list_kept_by_lengths = 
			    slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
			    number_of_increments),list_kept_by_lengths);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(profile_object,
			    Qsimple_unsigned_byte_8_arrays);
		SVREF(profile_object,FIX((SI_Long)31L)) = list_kept_by_lengths;
	    }
	    else {
		if (SIMPLE_ARRAY_ANY_1_P(thing_to_walk)) {
		    temp_1 = array_element_type(thing_to_walk);
		    temp = EQUAL(list_constant_1,temp_1);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    incf_by_lengths_arg_1 = length(thing_to_walk);
		    list_kept_by_lengths = ISVREF(profile_object,(SI_Long)30L);
		    counter_for_this_length_qm = 
			    assoc_eql(incf_by_lengths_arg_1,
			    list_kept_by_lengths);
		    number_of_increments = Nil;
		    if (number_of_increments);
		    else
			number_of_increments = FIX((SI_Long)1L);
		    if (counter_for_this_length_qm) {
			incff_1_arg = number_of_increments;
			temp_4 = 
				FIXNUM_ADD(CDR(counter_for_this_length_qm),
				incff_1_arg);
			M_CDR(counter_for_this_length_qm) = temp_4;
			list_kept_by_lengths;
		    }
		    else
			list_kept_by_lengths = 
				slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
				number_of_increments),list_kept_by_lengths);
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,
				Qsimple_unsigned_byte_16_arrays);
		    SVREF(profile_object,FIX((SI_Long)30L)) = 
			    list_kept_by_lengths;
		}
		else if (SIMPLE_ARRAY_ANY_1_P(thing_to_walk) && 
			EQ(Qdouble_float,array_element_type(thing_to_walk))) {
		    incf_by_lengths_arg_1 = length(thing_to_walk);
		    list_kept_by_lengths = ISVREF(profile_object,(SI_Long)32L);
		    counter_for_this_length_qm = 
			    assoc_eql(incf_by_lengths_arg_1,
			    list_kept_by_lengths);
		    number_of_increments = Nil;
		    if (number_of_increments);
		    else
			number_of_increments = FIX((SI_Long)1L);
		    if (counter_for_this_length_qm) {
			incff_1_arg = number_of_increments;
			temp_4 = 
				FIXNUM_ADD(CDR(counter_for_this_length_qm),
				incff_1_arg);
			M_CDR(counter_for_this_length_qm) = temp_4;
			list_kept_by_lengths;
		    }
		    else
			list_kept_by_lengths = 
				slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
				number_of_increments),list_kept_by_lengths);
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,
				Qdouble_float_arrays);
		    SVREF(profile_object,FIX((SI_Long)32L)) = 
			    list_kept_by_lengths;
		}
		else if (SIMPLE_VECTOR_P(thing_to_walk) && 
			EQ(ISVREF(thing_to_walk,(SI_Long)0L),
			Managed_array_unique_marker)) {
		    gensymed_symbol = SXHASH_SYMBOL_1(thing_to_walk) & 
			    IFIX(Most_positive_fixnum);
		    temp_1 = Items_encountered_in_memory_walk;
		    temp_2 = gensymed_symbol % (SI_Long)131L;
		    temp_1 = SVREF(temp_1,FIX(temp_2));
		    skip_list = CDR(temp_1);
		    key_value = thing_to_walk;
		    key_hash_value = gensymed_symbol;
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
		    temp_3 = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_3,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_5:
		    if ( !TRUEP(marked))
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_3,temp_1);
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
		    already_encountered_item_p = IFIX(ISVREF(curr,
			    (SI_Long)1L)) == key_hash_value ? 
			    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		    if ( !TRUEP(already_encountered_item_p)) {
			gensymed_symbol = SXHASH_SYMBOL_1(thing_to_walk) & 
				IFIX(Most_positive_fixnum);
			temp_1 = Items_encountered_in_memory_walk;
			temp_2 = gensymed_symbol % (SI_Long)131L;
			set_skip_list_entry(SVREF(temp_1,FIX(temp_2)),
				FIX((SI_Long)31L),Qeq,Nil,T,thing_to_walk,
				FIX(gensymed_symbol),T);
			length_of_managed_array = ISVREF(thing_to_walk,
				(SI_Long)1L);
			if (FIXNUM_GT(length_of_managed_array,
				Maximum_in_place_array_size)) {
			    temp_2 = 
				    IFIX(FIXNUM_ADD(length_of_managed_array,
				    FIXNUM_SUB1(Maximum_managed_array_buffer_size))) 
				    / IFIX(Maximum_managed_array_buffer_size);
			    number_of_managed_buffers = temp_2;
			    if (number_of_managed_buffers > (SI_Long)0L) {
				number_of_managed_buffers_minus_one = 
					number_of_managed_buffers - 
					(SI_Long)1L;
				incf_by_lengths_arg_2 = 
					number_of_managed_buffers_minus_one;
				list_kept_by_lengths = 
					ISVREF(profile_object,(SI_Long)29L);
				counter_for_this_length_qm = 
					assoc_eql(Maximum_managed_array_buffer_size,
					list_kept_by_lengths);
				number_of_increments = 
					FIX(incf_by_lengths_arg_2);
				if (number_of_increments);
				else
				    number_of_increments = FIX((SI_Long)1L);
				if (counter_for_this_length_qm) {
				    incff_1_arg = number_of_increments;
				    temp_4 = 
					    FIXNUM_ADD(CDR(counter_for_this_length_qm),
					    incff_1_arg);
				    M_CDR(counter_for_this_length_qm) = temp_4;
				    list_kept_by_lengths;
				}
				else
				    list_kept_by_lengths = 
					    slot_value_cons_1(slot_value_cons_1(Maximum_managed_array_buffer_size,
					    number_of_increments),
					    list_kept_by_lengths);
				if (Noting_changes_to_kb_p)
				    note_change_to_block_1(profile_object,
					    Qsimple_general_arrays);
				SVREF(profile_object,FIX((SI_Long)29L)) = 
					list_kept_by_lengths;
				incf_by_lengths_arg_1 = 
					length(ISVREF(thing_to_walk,
					number_of_managed_buffers_minus_one 
					+ (SI_Long)2L));
				list_kept_by_lengths = 
					ISVREF(profile_object,(SI_Long)29L);
				counter_for_this_length_qm = 
					assoc_eql(incf_by_lengths_arg_1,
					list_kept_by_lengths);
				number_of_increments = Nil;
				if (number_of_increments);
				else
				    number_of_increments = FIX((SI_Long)1L);
				if (counter_for_this_length_qm) {
				    incff_1_arg = number_of_increments;
				    temp_4 = 
					    FIXNUM_ADD(CDR(counter_for_this_length_qm),
					    incff_1_arg);
				    M_CDR(counter_for_this_length_qm) = temp_4;
				    list_kept_by_lengths;
				}
				else
				    list_kept_by_lengths = 
					    slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
					    number_of_increments),
					    list_kept_by_lengths);
				if (Noting_changes_to_kb_p)
				    note_change_to_block_1(profile_object,
					    Qsimple_general_arrays);
				SVREF(profile_object,FIX((SI_Long)29L)) = 
					list_kept_by_lengths;
				incf_by_lengths_arg_1_1 = 
					number_of_managed_buffers + 
					IFIX(Managed_array_index_offset);
				list_kept_by_lengths = 
					ISVREF(profile_object,(SI_Long)29L);
				counter_for_this_length_qm = 
					assoc_eql(FIX(incf_by_lengths_arg_1_1),
					list_kept_by_lengths);
				number_of_increments = Nil;
				if (number_of_increments);
				else
				    number_of_increments = FIX((SI_Long)1L);
				if (counter_for_this_length_qm) {
				    incff_1_arg = number_of_increments;
				    temp_4 = 
					    FIXNUM_ADD(CDR(counter_for_this_length_qm),
					    incff_1_arg);
				    M_CDR(counter_for_this_length_qm) = temp_4;
				    list_kept_by_lengths;
				}
				else
				    list_kept_by_lengths = 
					    slot_value_cons_1(slot_value_cons_1(FIX(incf_by_lengths_arg_1_1),
					    number_of_increments),
					    list_kept_by_lengths);
				if (Noting_changes_to_kb_p)
				    note_change_to_block_1(profile_object,
					    Qsimple_general_arrays);
				SVREF(profile_object,FIX((SI_Long)29L)) = 
					list_kept_by_lengths;
			    }
			}
			else {
			    incf_by_lengths_arg_1 = 
				    FIXNUM_ADD(length_of_managed_array,
				    Managed_array_index_offset);
			    list_kept_by_lengths = ISVREF(profile_object,
				    (SI_Long)29L);
			    counter_for_this_length_qm = 
				    assoc_eql(incf_by_lengths_arg_1,
				    list_kept_by_lengths);
			    number_of_increments = Nil;
			    if (number_of_increments);
			    else
				number_of_increments = FIX((SI_Long)1L);
			    if (counter_for_this_length_qm) {
				incff_1_arg = number_of_increments;
				temp_4 = 
					FIXNUM_ADD(CDR(counter_for_this_length_qm),
					incff_1_arg);
				M_CDR(counter_for_this_length_qm) = temp_4;
				list_kept_by_lengths;
			    }
			    else
				list_kept_by_lengths = 
					slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
					number_of_increments),
					list_kept_by_lengths);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(profile_object,
					Qsimple_general_arrays);
			    SVREF(profile_object,FIX((SI_Long)29L)) = 
				    list_kept_by_lengths;
			}
			index_1 = (SI_Long)0L;
			ab_loop_bind_ = IFIX(length_of_managed_array);
		      next_loop_6:
			if (index_1 >= ab_loop_bind_)
			    goto end_loop_6;
			walk_for_memory_recursion(FIXNUM_LE(ISVREF(thing_to_walk,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(thing_to_walk,index_1 + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(thing_to_walk,(index_1 >>  - 
				 - (SI_Long)10L) + (SI_Long)2L),index_1 & 
				(SI_Long)1023L),profile_object);
			index_1 = index_1 + (SI_Long)1L;
			goto next_loop_6;
		      end_loop_6:;
		    }
		}
		else if (SIMPLE_VECTOR_P(thing_to_walk)) {
		    if ( !((SI_Long)1L < IFIX(length(thing_to_walk)) && 
			    SIMPLE_VECTOR_P(thing_to_walk) && 
			    EQ(ISVREF(thing_to_walk,(SI_Long)1L),
			    Qavailable_frame_vector))) {
			if (allocated_named_gensym_structure_p(thing_to_walk) 
				|| 
				Do_circularity_check_walking_through_simple_vectors_p) 
				    {
			    gensymed_symbol = 
				    SXHASH_SYMBOL_1(thing_to_walk) & 
				    IFIX(Most_positive_fixnum);
			    temp_1 = Items_encountered_in_memory_walk;
			    temp_2 = gensymed_symbol % (SI_Long)131L;
			    temp_1 = SVREF(temp_1,FIX(temp_2));
			    skip_list = CDR(temp_1);
			    key_value = thing_to_walk;
			    key_hash_value = gensymed_symbol;
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_8:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_3 = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_3,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_9:
			    if ( !TRUEP(marked))
				goto end_loop_8;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_3 = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_3,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_9;
			  end_loop_8:
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
			  end_loop_9:
			  end_3:
			    level = level - (SI_Long)1L;
			    goto next_loop_7;
			  end_loop_7:;
			    already_encountered_item_qm = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (already_encountered_item_qm)
				goto end_block_tag;
			    else {
				gensymed_symbol = 
					SXHASH_SYMBOL_1(thing_to_walk) & 
					IFIX(Most_positive_fixnum);
				temp_1 = Items_encountered_in_memory_walk;
				temp_2 = gensymed_symbol % (SI_Long)131L;
				set_skip_list_entry(SVREF(temp_1,
					FIX(temp_2)),FIX((SI_Long)31L),Qeq,
					Nil,T,thing_to_walk,
					FIX(gensymed_symbol),T);
				goto body_tag;
			    }
			}
			else
			    goto body_tag;
		      body_tag:
			length_of_simple_array = length(thing_to_walk);
			incf_by_lengths_arg_1 = length_of_simple_array;
			list_kept_by_lengths = ISVREF(profile_object,
				(SI_Long)29L);
			counter_for_this_length_qm = 
				assoc_eql(incf_by_lengths_arg_1,
				list_kept_by_lengths);
			number_of_increments = Nil;
			if (number_of_increments);
			else
			    number_of_increments = FIX((SI_Long)1L);
			if (counter_for_this_length_qm) {
			    incff_1_arg = number_of_increments;
			    temp_4 = 
				    FIXNUM_ADD(CDR(counter_for_this_length_qm),
				    incff_1_arg);
			    M_CDR(counter_for_this_length_qm) = temp_4;
			    list_kept_by_lengths;
			}
			else
			    list_kept_by_lengths = 
				    slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
				    number_of_increments),
				    list_kept_by_lengths);
			if (Noting_changes_to_kb_p)
			    note_change_to_block_1(profile_object,
				    Qsimple_general_arrays);
			SVREF(profile_object,FIX((SI_Long)29L)) = 
				list_kept_by_lengths;
			if (allocated_named_gensym_structure_p(thing_to_walk))
			    walk_named_g2_structure_for_memory(thing_to_walk,
				    profile_object);
			else {
			    index_1 = (SI_Long)0L;
			    ab_loop_bind_ = IFIX(length_of_simple_array);
			  next_loop_10:
			    if (index_1 >= ab_loop_bind_)
				goto end_loop_10;
			    walk_for_memory_recursion(ISVREF(thing_to_walk,
				    index_1),profile_object);
			    index_1 = index_1 + (SI_Long)1L;
			    goto next_loop_10;
			  end_loop_10:;
			}
		      end_block_tag:;
		    }
		}
		else if (CONSP(thing_to_walk) && EQ(M_CDR(thing_to_walk),
			Qitem_reference)) {
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)22L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qconses);
		    SVREF(profile_object,FIX((SI_Long)22L)) = temp_4;
		}
		else if (CONSP(thing_to_walk)) {
		    if (Do_circularity_check_walking_through_conses_p) {
			gensymed_symbol = SXHASH_SYMBOL_1(thing_to_walk) & 
				IFIX(Most_positive_fixnum);
			temp_1 = Items_encountered_in_memory_walk;
			temp_2 = gensymed_symbol % (SI_Long)131L;
			temp_1 = SVREF(temp_1,FIX(temp_2));
			skip_list = CDR(temp_1);
			key_value = thing_to_walk;
			key_hash_value = gensymed_symbol;
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_11:
			if (level < ab_loop_bind_)
			    goto end_loop_11;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_12:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_3,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_13:
			if ( !TRUEP(marked))
			    goto end_loop_12;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_3,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_13;
		      end_loop_12:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_4;
			goto next_loop_12;
		      end_loop_13:
		      end_4:
			level = level - (SI_Long)1L;
			goto next_loop_11;
		      end_loop_11:;
			already_encountered_item_qm = IFIX(ISVREF(curr,
				(SI_Long)1L)) == key_hash_value ? 
				(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
				ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			if (already_encountered_item_qm)
			    goto end_block_tag_1;
			else {
			    gensymed_symbol = 
				    SXHASH_SYMBOL_1(thing_to_walk) & 
				    IFIX(Most_positive_fixnum);
			    temp_1 = Items_encountered_in_memory_walk;
			    temp_2 = gensymed_symbol % (SI_Long)131L;
			    set_skip_list_entry(SVREF(temp_1,FIX(temp_2)),
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    thing_to_walk,FIX(gensymed_symbol),T);
			    goto body_tag_1;
			}
		    }
		    else
			goto body_tag_1;
		  body_tag_1:
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)22L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qconses);
		    SVREF(profile_object,FIX((SI_Long)22L)) = temp_4;
		    walk_for_memory_recursion(CAR(thing_to_walk),
			    profile_object);
		    walk_for_memory_recursion(CDR(thing_to_walk),
			    profile_object);
		  end_block_tag_1:;
		}
		else if (FLOATP(thing_to_walk)) {
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)24L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qdouble_floats);
		    SVREF(profile_object,FIX((SI_Long)24L)) = temp_4;
		}
		else if (SYMBOLP(thing_to_walk)) {
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)23L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qsymbols);
		    SVREF(profile_object,FIX((SI_Long)23L)) = temp_4;
		}
		else if (FIXNUMP(thing_to_walk)) {
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)25L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qfixnums);
		    SVREF(profile_object,FIX((SI_Long)25L)) = temp_4;
		}
		else if (CHARACTERP(thing_to_walk)) {
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)26L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qcharacters);
		    SVREF(profile_object,FIX((SI_Long)26L)) = temp_4;
		}
		else if (FUNCTIONP(thing_to_walk)) {
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)27L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qfunctions);
		    SVREF(profile_object,FIX((SI_Long)27L)) = temp_4;
		}
		else {
		    temp_4 = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)28L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(profile_object,Qimmediates);
		    SVREF(profile_object,FIX((SI_Long)28L)) = temp_4;
		}
	    }
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Special_slot_names_for_memory_walk, Qspecial_slot_names_for_memory_walk);

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* WALK-NAMED-G2-STRUCTURE-FOR-MEMORY */
Object walk_named_g2_structure_for_memory(g2_structure,profile_object)
    Object g2_structure, profile_object;
{
    Object raw_name, type_description_qm, slots, slot_name_or_description;
    Object ab_loop_list_, slot_name, ab_loop_iter_flag_, special_slot_entry_qm;
    Object temp;
    SI_Long i;

    x_note_fn_call(165,22);
    raw_name = ISVREF(g2_structure,(SI_Long)0L);
    type_description_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(raw_name),
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    slots = type_description_qm ? ISVREF(type_description_qm,(SI_Long)5L) :
	     Nil;
    slot_name_or_description = Nil;
    ab_loop_list_ = slots;
    slot_name = Nil;
    i = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_name_or_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name = SYMBOLP(slot_name_or_description) ? 
	    slot_name_or_description : CAR(slot_name_or_description);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    special_slot_entry_qm = assq_function(slot_name,
	    Special_slot_names_for_memory_walk);
    if (special_slot_entry_qm) {
	temp = CDR(special_slot_entry_qm);
	FUNCALL_3(temp,g2_structure,ISVREF(g2_structure,i),profile_object);
    }
    else
	walk_for_memory_recursion(ISVREF(g2_structure,i),profile_object);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REMOVE-SPECIAL-SLOT-FOR-MEMORY-WALK */
Object remove_special_slot_for_memory_walk(slot_name)
    Object slot_name;
{
    x_note_fn_call(165,23);
    Special_slot_names_for_memory_walk = lremove(6,slot_name,
	    Special_slot_names_for_memory_walk,Kkey,SYMBOL_FUNCTION(Qcar),
	    Ktest,SYMBOL_FUNCTION(Qeql));
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-LRU-ELEMENT-NEXT-ELEMENT */
Object walk_memory_for_value_of_lru_element_next_element(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    x_note_fn_call(165,24);
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-LRU-ELEMENT-PREVIOUS-ELEMENT */
Object walk_memory_for_value_of_lru_element_previous_element(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    x_note_fn_call(165,25);
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-IMAGE-PLANE-FOR-GRAPH-RENDERING? */
Object walk_memory_for_value_of_image_plane_for_graph_rendering_qm(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    x_note_fn_call(165,26);
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-WINDOW-FOR-GRAPH-RENDERING */
Object walk_memory_for_value_of_window_for_graph_rendering(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    x_note_fn_call(165,27);
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-UUID-BLOCK-ITEM-REFERENCE-TABLE */
Object walk_memory_for_value_of_uuid_block_item_reference_table(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, temp, incf_by_lengths_arg_1, list_kept_by_lengths;
    Object counter_for_this_length_qm, number_of_increments;

    x_note_fn_call(165,28);
    if (LISTP(slot_value)) {
	incff_1_arg = length(slot_value);
	temp = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),incff_1_arg);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(profile_object,Qconses);
	SVREF(profile_object,FIX((SI_Long)22L)) = temp;
    }
    else {
	incf_by_lengths_arg_1 = length(slot_value);
	list_kept_by_lengths = ISVREF(profile_object,(SI_Long)29L);
	counter_for_this_length_qm = assoc_eql(incf_by_lengths_arg_1,
		list_kept_by_lengths);
	number_of_increments = Nil;
	if (number_of_increments);
	else
	    number_of_increments = FIX((SI_Long)1L);
	if (counter_for_this_length_qm) {
	    incff_1_arg = number_of_increments;
	    temp = FIXNUM_ADD(CDR(counter_for_this_length_qm),incff_1_arg);
	    M_CDR(counter_for_this_length_qm) = temp;
	    list_kept_by_lengths;
	}
	else
	    list_kept_by_lengths = 
		    slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
		    number_of_increments),list_kept_by_lengths);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(profile_object,Qsimple_general_arrays);
	SVREF(profile_object,FIX((SI_Long)29L)) = list_kept_by_lengths;
    }
    return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qicon_description;   /* icon-description */

/* WALK-MEMORY-FOR-VALUE-OF-ICON-DESCRIPTION */
Object walk_memory_for_value_of_icon_description(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object class_name, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object icon_description_of_class;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(165,29);
    class_name = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = class_name;
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
    icon_description_of_class = 
	    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
	    gensymed_symbol,Nil),(SI_Long)6L);
    if (!EQ(icon_description_of_class,slot_value))
	walk_for_memory_recursion(slot_value,profile_object);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Size_of_icon_slot_group, Qsize_of_icon_slot_group);

/* WALK-MEMORY-FOR-VALUE-OF-SLOT-GROUP-FOR-BLOCK? */
Object walk_memory_for_value_of_slot_group_for_block_qm(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object incf_by_lengths_arg_1, list_kept_by_lengths;
    Object counter_for_this_length_qm, number_of_increments, incff_1_arg;
    Object cdr_new_value, gensymed_symbol;

    x_note_fn_call(165,30);
    if (slot_value) {
	incf_by_lengths_arg_1 = Size_of_icon_slot_group;
	list_kept_by_lengths = ISVREF(profile_object,(SI_Long)29L);
	counter_for_this_length_qm = assoc_eql(incf_by_lengths_arg_1,
		list_kept_by_lengths);
	number_of_increments = Nil;
	if (number_of_increments);
	else
	    number_of_increments = FIX((SI_Long)1L);
	if (counter_for_this_length_qm) {
	    incff_1_arg = number_of_increments;
	    cdr_new_value = FIXNUM_ADD(CDR(counter_for_this_length_qm),
		    incff_1_arg);
	    M_CDR(counter_for_this_length_qm) = cdr_new_value;
	    list_kept_by_lengths;
	}
	else
	    list_kept_by_lengths = 
		    slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
		    number_of_increments),list_kept_by_lengths);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(profile_object,Qsimple_general_arrays);
	SVREF(profile_object,FIX((SI_Long)29L)) = list_kept_by_lengths;
	gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	walk_for_memory_recursion(gensymed_symbol,profile_object);
    }
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-THINGS-THIS-VARIABLE-IS-INTERESTED-IN */
Object walk_memory_for_value_of_things_this_variable_is_interested_in(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(165,31);
    incff_1_arg = length(slot_value);
    svref_new_value = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),
	    incff_1_arg);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qconses);
    SVREF(profile_object,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-THINGS-INTERESTED-IN-THIS-VARIABLE */
Object walk_memory_for_value_of_things_interested_in_this_variable(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(165,32);
    incff_1_arg = length(slot_value);
    svref_new_value = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),
	    incff_1_arg);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qconses);
    SVREF(profile_object,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-RELATION-INSTANCES */
Object walk_memory_for_value_of_relation_instances(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(165,33);
    incff_1_arg = length(slot_value);
    svref_new_value = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),
	    incff_1_arg);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qconses);
    SVREF(profile_object,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-LIST-ELEMENTS-FOR-ITEM */
Object walk_memory_for_value_of_list_elements_for_item(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(165,34);
    incff_1_arg = length(slot_value);
    svref_new_value = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),
	    incff_1_arg);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qconses);
    SVREF(profile_object,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-SUBBLOCKS */
Object walk_memory_for_value_of_subblocks(frame,slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(165,35);
    incff_1_arg = length(slot_value);
    svref_new_value = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),
	    incff_1_arg);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qconses);
    SVREF(profile_object,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-CONNECTIONS */
Object walk_memory_for_value_of_connections(frame,slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(165,36);
    incff_1_arg = length(slot_value);
    svref_new_value = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),
	    incff_1_arg);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qconses);
    SVREF(profile_object,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-BACKWARD-CHAIN-NEW-RULES */
Object walk_memory_for_value_of_backward_chain_new_rules(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object incff_1_arg, svref_new_value;

    x_note_fn_call(165,37);
    incff_1_arg = length(slot_value);
    svref_new_value = FIXNUM_ADD(ISVREF(profile_object,(SI_Long)22L),
	    incff_1_arg);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qconses);
    SVREF(profile_object,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qvector_slots;       /* vector-slots */

/* WALK-MEMORY-FOR-VALUE-OF-CLASS */
Object walk_memory_for_value_of_class(frame,slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,38);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-LOOKUP-STRUCTURE */
Object walk_memory_for_value_of_lookup_structure(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,39);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-CLASS-DESCRIPTION-SLOT */
Object walk_memory_for_value_of_class_description_slot(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,40);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-CLASS-SPECIFIC-INSTANCES-FORWARD-POINTER */
Object walk_memory_for_value_of_class_specific_instances_forward_pointer(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,41);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-CLASS-SPECIFIC-INSTANCES-REVERSE-POINTER */
Object walk_memory_for_value_of_class_specific_instances_reverse_pointer(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,42);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-MENUS-FOR-THIS */
Object walk_memory_for_value_of_menus_for_this(frame,slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,43);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-PARENT-FRAME */
Object walk_memory_for_value_of_parent_frame(frame,slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,44);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-PARENT-ATTRIBUTE-NAME */
Object walk_memory_for_value_of_parent_attribute_name(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,45);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-CELL-ARRAY */
Object walk_memory_for_value_of_cell_array(frame,slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,46);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-SUPERBLOCK? */
Object walk_memory_for_value_of_superblock_qm(frame,slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,47);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-IMAGE-PLANES-THIS-IS-ON */
Object walk_memory_for_value_of_image_planes_this_is_on(frame,slot_value,
	    profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,48);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-CURRENTLY-UP-TO-DATE-IMAGE-PLANES */
Object walk_memory_for_value_of_currently_up_to_date_image_planes(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,49);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* WALK-MEMORY-FOR-VALUE-OF-KB-STATE-CHANGES-PREVIOUS-CONS? */
Object walk_memory_for_value_of_kb_state_changes_previous_cons_qm(frame,
	    slot_value,profile_object)
    Object frame, slot_value, profile_object;
{
    Object svref_new_value;

    x_note_fn_call(165,50);
    svref_new_value = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qvector_slots);
    SVREF(profile_object,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Slots_containing_circular_unnamed_simple_vectors, Qslots_containing_circular_unnamed_simple_vectors);

/* CHARGE-ATTRIBUTE-TO-FRAME-P */
Object charge_attribute_to_frame_p(attribute,containing_frame)
    Object attribute, containing_frame;
{
    Object x2, temp_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(165,51);
    if (SIMPLE_VECTOR_P(attribute) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute)) > (SI_Long)2L &&  
	    !EQ(ISVREF(attribute,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(attribute,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 =  !temp ? T : Nil;
    if (temp_1);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(attribute,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Dependent_frame_class_description,(SI_Long)18L));
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
	    temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp_1 = Nil;
	if (temp_1);
	else
	    temp_1 = EQ(superior_frame(attribute),containing_frame) ? T : Nil;
    }
    return VALUES_1(temp_1);
}

static Object Qframe_vectors;      /* frame-vectors */

static Object Kfuncall;            /* :funcall */

static Object Qdefaulted_vector_slots;  /* defaulted-vector-slots */

static Object Quser_vector_slots;  /* user-vector-slots */

static Object Qdefaulted_user_vector_slots;  /* defaulted-user-vector-slots */

static Object Qlookup_slots;       /* lookup-slots */

static Object Qdefaulted_lookup_slots;  /* defaulted-lookup-slots */

static Object Qcompound_slot_descriptor;  /* compound-slot-descriptor */

static Object Q2d_image_plane_states;  /* 2d-image-plane-states */

static Object Qslot_value_reclaimer;  /* slot-value-reclaimer */

/* WALK-FRAME-FOR-MEMORY */
Object walk_frame_for_memory(frame,profile_object)
    Object frame, profile_object;
{
    Object class_description_of_frame, slot_descriptions_of_frame;
    Object incf_by_lengths_arg_1, list_kept_by_lengths;
    Object counter_for_this_length_qm, number_of_increments, incff_1_arg, temp;
    Object slot_description, ab_loop_list_, slot_to_walk, value_of_slot;
    Object default_value, vector_slot_p, user_vector_slot_p;
    Object undefaulted_slot_p, temp_1, special_slot_entry_qm;
    Object do_circularity_check_walking_through_conses_p;
    Object do_circularity_check_walking_through_simple_vectors_p;
    Declare_special(2);

    x_note_fn_call(165,52);
    if ( !TRUEP(frame))
	return VALUES_1(Nil);
    class_description_of_frame = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(frame,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    slot_descriptions_of_frame = ISVREF(class_description_of_frame,
	    (SI_Long)6L);
    incf_by_lengths_arg_1 = ISVREF(class_description_of_frame,(SI_Long)14L);
    list_kept_by_lengths = ISVREF(profile_object,(SI_Long)35L);
    counter_for_this_length_qm = assoc_eql(incf_by_lengths_arg_1,
	    list_kept_by_lengths);
    number_of_increments = Nil;
    if (number_of_increments);
    else
	number_of_increments = FIX((SI_Long)1L);
    if (counter_for_this_length_qm) {
	incff_1_arg = number_of_increments;
	temp = FIXNUM_ADD(CDR(counter_for_this_length_qm),incff_1_arg);
	M_CDR(counter_for_this_length_qm) = temp;
	list_kept_by_lengths;
    }
    else
	list_kept_by_lengths = 
		slot_value_cons_1(slot_value_cons_1(incf_by_lengths_arg_1,
		number_of_increments),list_kept_by_lengths);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(profile_object,Qframe_vectors);
    SVREF(profile_object,FIX((SI_Long)35L)) = list_kept_by_lengths;
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions_of_frame;
    slot_to_walk = Nil;
    value_of_slot = Nil;
    default_value = Nil;
    vector_slot_p = Nil;
    user_vector_slot_p = Nil;
    undefaulted_slot_p = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_to_walk = ISVREF(slot_description,(SI_Long)1L);
    value_of_slot = get_slot_description_value(frame,slot_description);
    default_value = ISVREF(slot_description,(SI_Long)6L);
    vector_slot_p = ISVREF(slot_description,(SI_Long)7L);
    user_vector_slot_p = ISVREF(slot_description,(SI_Long)8L);
    temp_1 = CONSP(default_value) ? (EQ(M_CAR(default_value),Kfuncall) ? T 
	    : Nil) : Qnil;
    if (temp_1);
    else
	temp_1 =  !EQ(value_of_slot,default_value) ? T : Nil;
    undefaulted_slot_p = temp_1;
    if (vector_slot_p) {
	temp = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)16L));
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(profile_object,Qvector_slots);
	SVREF(profile_object,FIX((SI_Long)16L)) = temp;
	if ( !TRUEP(undefaulted_slot_p)) {
	    temp = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)19L));
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(profile_object,Qdefaulted_vector_slots);
	    SVREF(profile_object,FIX((SI_Long)19L)) = temp;
	}
    }
    else if (user_vector_slot_p) {
	temp = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)17L));
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(profile_object,Quser_vector_slots);
	SVREF(profile_object,FIX((SI_Long)17L)) = temp;
	if ( !TRUEP(undefaulted_slot_p)) {
	    temp = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)20L));
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(profile_object,
			Qdefaulted_user_vector_slots);
	    SVREF(profile_object,FIX((SI_Long)20L)) = temp;
	}
    }
    else {
	temp = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)18L));
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(profile_object,Qlookup_slots);
	SVREF(profile_object,FIX((SI_Long)18L)) = temp;
	if ( !TRUEP(undefaulted_slot_p)) {
	    temp = FIXNUM_ADD1(ISVREF(profile_object,(SI_Long)21L));
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(profile_object,Qdefaulted_lookup_slots);
	    SVREF(profile_object,FIX((SI_Long)21L)) = temp;
	}
    }
    if (undefaulted_slot_p) {
	special_slot_entry_qm = assq_function(slot_to_walk,
		Special_slot_names_for_memory_walk);
	temp_1 = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_to_walk),
		Qcompound_slot_descriptor);
	if (temp_1);
	else
	    temp_1 = EQ(slot_to_walk,Q2d_image_plane_states) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_to_walk),
		    Qslot_value_reclaimer);
	do_circularity_check_walking_through_conses_p = temp_1;
	do_circularity_check_walking_through_simple_vectors_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Do_circularity_check_walking_through_simple_vectors_p,Qdo_circularity_check_walking_through_simple_vectors_p,do_circularity_check_walking_through_simple_vectors_p,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Do_circularity_check_walking_through_conses_p,Qdo_circularity_check_walking_through_conses_p,do_circularity_check_walking_through_conses_p,
		  0);
	    if (special_slot_entry_qm) {
		temp_1 = CDR(special_slot_entry_qm);
		FUNCALL_3(temp_1,frame,value_of_slot,profile_object);
	    }
	    else if (CONSP(value_of_slot))
		walk_for_memory_recursion(value_of_slot,profile_object);
	    else if (charge_attribute_to_frame_p(value_of_slot,frame))
		walk_for_memory_recursion(value_of_slot,profile_object);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* SIZE-OF-CONS */
Object size_of_cons()
{
    x_note_fn_call(165,53);
    return VALUES_1(FIX((SI_Long)8L));
}

/* SIZE-OF-IMMEDIATE */
Object size_of_immediate()
{
    x_note_fn_call(165,54);
    return VALUES_1(FIX((SI_Long)4L));
}

/* SIZE-OF-VECTOR-SLOT */
Object size_of_vector_slot()
{
    x_note_fn_call(165,55);
    return VALUES_1(FIX((SI_Long)4L));
}

/* SIZE-OF-DOUBLE-FLOAT */
Object size_of_double_float()
{
    x_note_fn_call(165,56);
    return VALUES_1(FIX((SI_Long)16L));
}

/* SIZE-OF-SYMBOL */
Object size_of_symbol(print_name_length)
    Object print_name_length;
{
    SI_Long temp;

    x_note_fn_call(165,57);
    temp = IFIX(print_name_length) / (SI_Long)4L;
    return VALUES_1(FIX((SI_Long)20L + (SI_Long)4L * temp));
}

/* SIZE-OF-SIMPLE-GENERAL-ARRAY */
Object size_of_simple_general_array(array_length)
    Object array_length;
{
    x_note_fn_call(165,58);
    return VALUES_1(FIX((SI_Long)16L + (SI_Long)4L * IFIX(array_length)));
}

/* SIZE-OF-SIMPLE-UNSIGNED-BYTE-16-ARRAY */
Object size_of_simple_unsigned_byte_16_array(array_length)
    Object array_length;
{
    SI_Long temp;

    x_note_fn_call(165,59);
    temp = (IFIX(array_length) + ((SI_Long)2L - (SI_Long)1L)) / (SI_Long)2L;
    return VALUES_1(FIX((SI_Long)8L + (SI_Long)2L * temp));
}

/* SIZE-OF-SIMPLE-UNSIGNED-BYTE-8-ARRAY */
Object size_of_simple_unsigned_byte_8_array(array_length)
    Object array_length;
{
    SI_Long temp;

    x_note_fn_call(165,60);
    temp = (IFIX(array_length) + ((SI_Long)4L - (SI_Long)1L)) / (SI_Long)4L;
    return VALUES_1(FIX((SI_Long)8L + (SI_Long)4L * temp));
}

/* SIZE-OF-DOUBLE-FLOAT-ARRAY */
Object size_of_double_float_array(array_length)
    Object array_length;
{
    x_note_fn_call(165,61);
    return VALUES_1(FIX((SI_Long)8L + (SI_Long)8L * IFIX(array_length)));
}

/* SIZE-OF-SIMPLE-STRING */
Object size_of_simple_string(string_length)
    Object string_length;
{
    SI_Long temp;

    x_note_fn_call(165,62);
    temp = (IFIX(string_length) + ((SI_Long)4L - (SI_Long)1L)) / (SI_Long)4L;
    return VALUES_1(FIX((SI_Long)8L + (SI_Long)4L * temp));
}

/* SIZE-OF-ADJUSTABLE-STRING */
Object size_of_adjustable_string(string_length)
    Object string_length;
{
    SI_Long temp;

    x_note_fn_call(165,63);
    temp = (IFIX(string_length) + ((SI_Long)4L - (SI_Long)1L)) / (SI_Long)4L;
    return VALUES_1(FIX((SI_Long)16L + (SI_Long)4L * temp));
}

DEFINE_VARIABLE_WITH_SYMBOL(Bytes_consumed_by_one_undefaulted_lookup_slot, Qbytes_consumed_by_one_undefaulted_lookup_slot);

static Object Qsymbol_list;        /* symbol-list */

static Object Qitem;               /* item */

/* LIST-OF-SUBCLASSES-OF-ITEM */
Object list_of_subclasses_of_item()
{
    Object list_frame, scope_conses, ab_loopvar_, class_symbol, temp;
    Declare_special(1);

    x_note_fn_call(165,64);
    list_frame = make_transient_item(Qsymbol_list);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qitem;
    class_symbol = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_symbol = temp;
      g2_list_insert_at_beginning(class_symbol,list_frame);
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return VALUES_1(list_frame);
}

/* G2-MEASURE-MEMORY-LISP-SIDE */
Object g2_measure_memory_lisp_side(frame)
    Object frame;
{
    Object profile, sum, double_floats, conses, vector_slots;
    Object user_vector_slots, lookup_slots, frame_vectors, arrays;
    Object result;

    x_note_fn_call(165,65);
    profile = get_memory_profile_of_item_lisp_side(frame);
    result = sum_memory_profile_lisp_side(profile);
    MVS_8(result,sum,double_floats,conses,vector_slots,user_vector_slots,
	    lookup_slots,frame_vectors,arrays);
    delete_frame(profile);
    return VALUES_8(sum,double_floats,conses,vector_slots,
	    user_vector_slots,lookup_slots,frame_vectors,arrays);
}

static Object Qsum;                /* sum */

static Object Qother_arrays;       /* other-arrays */

/* G2-MEASURE-MEMORY-FIELDS-LISP-SIDE */
Object g2_measure_memory_fields_lisp_side()
{
    x_note_fn_call(165,66);
    return VALUES_8(Qsum,Qdouble_floats,Qconses,Qvector_slots,
	    Quser_vector_slots,Qlookup_slots,Qframe_vectors,Qother_arrays);
}

static Object Qmemory_profile;     /* memory-profile */

/* GET-MEMORY-PROFILE-OF-ITEM-LISP-SIDE */
Object get_memory_profile_of_item_lisp_side(frame)
    Object frame;
{
    Object profile_object;

    x_note_fn_call(165,67);
    clear_items_encountered_in_memory_walk(Items_encountered_in_memory_walk);
    profile_object = make_transient_item(Qmemory_profile);
    walk_for_memory_recursion(frame,profile_object);
    return VALUES_1(profile_object);
}

/* SUM-MEMORY-PROFILE-LISP-SIDE */
Object sum_memory_profile_lisp_side(profile_object)
    Object profile_object;
{
    Object temp, double_floats, conses, vector_slots, user_vector_slots;
    Object lookup_slots, array_length, number_of_arrays, ab_loop_list_;
    Object ab_loopvar_, ab_loop_desetq_, frame_vectors, simple_general_arrays;
    Object simple_unsigned_byte_16_arrays, simple_unsigned_byte_8_arrays;
    Object double_float_arrays, adjustable_strings, simple_strings, temp_1;

    x_note_fn_call(165,68);
    temp = ISVREF(profile_object,(SI_Long)24L);
    double_floats = ltimes(temp,size_of_double_float());
    temp = ISVREF(profile_object,(SI_Long)22L);
    conses = ltimes(temp,size_of_cons());
    temp = ISVREF(profile_object,(SI_Long)16L);
    vector_slots = ltimes(temp,size_of_vector_slot());
    temp = ISVREF(profile_object,(SI_Long)17L);
    user_vector_slots = ltimes(temp,size_of_vector_slot());
    lookup_slots = ltimes(minus(ISVREF(profile_object,(SI_Long)18L),
	    ISVREF(profile_object,(SI_Long)21L)),
	    Bytes_consumed_by_one_undefaulted_lookup_slot);
    array_length = Nil;
    number_of_arrays = Nil;
    ab_loop_list_ = ISVREF(profile_object,(SI_Long)35L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    array_length = CAR(ab_loop_desetq_);
    number_of_arrays = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = number_of_arrays;
    temp = ltimes(temp,size_of_simple_general_array(array_length));
    ab_loopvar_ = add(temp,ab_loopvar_);
    goto next_loop;
  end_loop:
    frame_vectors = ab_loopvar_;
    goto end_1;
    frame_vectors = Qnil;
  end_1:;
    array_length = Nil;
    number_of_arrays = Nil;
    ab_loop_list_ = ISVREF(profile_object,(SI_Long)29L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    array_length = CAR(ab_loop_desetq_);
    number_of_arrays = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = number_of_arrays;
    temp = ltimes(temp,size_of_simple_general_array(array_length));
    ab_loopvar_ = add(temp,ab_loopvar_);
    goto next_loop_1;
  end_loop_1:
    simple_general_arrays = ab_loopvar_;
    goto end_2;
    simple_general_arrays = Qnil;
  end_2:;
    array_length = Nil;
    number_of_arrays = Nil;
    ab_loop_list_ = ISVREF(profile_object,(SI_Long)30L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    array_length = CAR(ab_loop_desetq_);
    number_of_arrays = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = number_of_arrays;
    temp = ltimes(temp,size_of_simple_unsigned_byte_16_array(array_length));
    ab_loopvar_ = add(temp,ab_loopvar_);
    goto next_loop_2;
  end_loop_2:
    simple_unsigned_byte_16_arrays = ab_loopvar_;
    goto end_3;
    simple_unsigned_byte_16_arrays = Qnil;
  end_3:;
    array_length = Nil;
    number_of_arrays = Nil;
    ab_loop_list_ = ISVREF(profile_object,(SI_Long)31L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    array_length = CAR(ab_loop_desetq_);
    number_of_arrays = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = number_of_arrays;
    temp = ltimes(temp,size_of_simple_unsigned_byte_8_array(array_length));
    ab_loopvar_ = add(temp,ab_loopvar_);
    goto next_loop_3;
  end_loop_3:
    simple_unsigned_byte_8_arrays = ab_loopvar_;
    goto end_4;
    simple_unsigned_byte_8_arrays = Qnil;
  end_4:;
    array_length = Nil;
    number_of_arrays = Nil;
    ab_loop_list_ = ISVREF(profile_object,(SI_Long)32L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    array_length = CAR(ab_loop_desetq_);
    number_of_arrays = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = number_of_arrays;
    temp = ltimes(temp,size_of_double_float_array(array_length));
    ab_loopvar_ = add(temp,ab_loopvar_);
    goto next_loop_4;
  end_loop_4:
    double_float_arrays = ab_loopvar_;
    goto end_5;
    double_float_arrays = Qnil;
  end_5:;
    array_length = Nil;
    number_of_arrays = Nil;
    ab_loop_list_ = ISVREF(profile_object,(SI_Long)33L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    array_length = CAR(ab_loop_desetq_);
    number_of_arrays = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = number_of_arrays;
    temp = ltimes(temp,size_of_adjustable_string(array_length));
    ab_loopvar_ = add(temp,ab_loopvar_);
    goto next_loop_5;
  end_loop_5:
    adjustable_strings = ab_loopvar_;
    goto end_6;
    adjustable_strings = Qnil;
  end_6:;
    array_length = Nil;
    number_of_arrays = Nil;
    ab_loop_list_ = ISVREF(profile_object,(SI_Long)34L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_6:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_6;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    array_length = CAR(ab_loop_desetq_);
    number_of_arrays = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = number_of_arrays;
    temp = ltimes(temp,size_of_simple_string(array_length));
    ab_loopvar_ = add(temp,ab_loopvar_);
    goto next_loop_6;
  end_loop_6:
    simple_strings = ab_loopvar_;
    goto end_7;
    simple_strings = Qnil;
  end_7:;
    temp_1 = addn(12,double_floats,conses,vector_slots,user_vector_slots,
	    lookup_slots,frame_vectors,simple_general_arrays,
	    simple_unsigned_byte_16_arrays,simple_unsigned_byte_8_arrays,
	    double_float_arrays,adjustable_strings,simple_strings);
    temp = addn(6,simple_general_arrays,simple_unsigned_byte_16_arrays,
	    simple_unsigned_byte_8_arrays,double_float_arrays,
	    adjustable_strings,simple_strings);
    return VALUES_8(temp_1,double_floats,conses,vector_slots,
	    user_vector_slots,lookup_slots,frame_vectors,temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Tab_length_for_counter_report, Qtab_length_for_counter_report);

/* REPORT-SIGNIFICANT-SINGLE-COUNTER-SLOT */
Object report_significant_single_counter_slot(slot,counter_value)
    Object slot, counter_value;
{
    x_note_fn_call(165,69);
    if ( !TRUEP(zerop(counter_value)))
	return format((SI_Long)5L,T,"~&~s:~vt~s~%",slot,
		Tab_length_for_counter_report,counter_value);
    else
	return VALUES_1(Nil);
}

/* REPORT-SIGNIFICANT-COUNT-BY-LENGTHS-SLOT */
Object report_significant_count_by_lengths_slot(slot,counter_value_qm)
    Object slot, counter_value_qm;
{
    Object count_1, length_1, ab_loop_list_, offset, ab_loop_iter_flag_;
    Object ab_loop_desetq_;

    x_note_fn_call(165,70);
    if (counter_value_qm)
	format((SI_Long)3L,T,"~&~s:",slot);
    count_1 = Nil;
    length_1 = Nil;
    ab_loop_list_ = counter_value_qm;
    offset = FIX((SI_Long)0L);
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    count_1 = CAR(ab_loop_desetq_);
    length_1 = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	offset = FIX((SI_Long)2L);
    format((SI_Long)5L,T,"~vt(~s . ~s)~%",
	    add(Tab_length_for_counter_report,offset),count_1,length_1);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REPORT-SIGNIFICANT-COUNTERS */
Object report_significant_counters(counter)
    Object counter;
{
    x_note_fn_call(165,71);
    report_significant_single_counter_slot(Qvector_slots,ISVREF(counter,
	    (SI_Long)16L));
    report_significant_single_counter_slot(Quser_vector_slots,
	    ISVREF(counter,(SI_Long)17L));
    report_significant_single_counter_slot(Qlookup_slots,ISVREF(counter,
	    (SI_Long)18L));
    report_significant_single_counter_slot(Qdefaulted_vector_slots,
	    ISVREF(counter,(SI_Long)19L));
    report_significant_single_counter_slot(Qdefaulted_user_vector_slots,
	    ISVREF(counter,(SI_Long)20L));
    report_significant_single_counter_slot(Qdefaulted_lookup_slots,
	    ISVREF(counter,(SI_Long)21L));
    report_significant_single_counter_slot(Qconses,ISVREF(counter,
	    (SI_Long)22L));
    report_significant_single_counter_slot(Qsymbols,ISVREF(counter,
	    (SI_Long)23L));
    report_significant_single_counter_slot(Qdouble_floats,ISVREF(counter,
	    (SI_Long)24L));
    report_significant_single_counter_slot(Qfixnums,ISVREF(counter,
	    (SI_Long)25L));
    report_significant_single_counter_slot(Qcharacters,ISVREF(counter,
	    (SI_Long)26L));
    report_significant_single_counter_slot(Qimmediates,ISVREF(counter,
	    (SI_Long)28L));
    report_significant_count_by_lengths_slot(Qsimple_general_arrays,sort(4,
	    ISVREF(counter,(SI_Long)29L),SYMBOL_FUNCTION(Qnum_lt),Kkey,
	    SYMBOL_FUNCTION(Qcar)));
    report_significant_count_by_lengths_slot(Qsimple_unsigned_byte_16_arrays,
	    sort(4,ISVREF(counter,(SI_Long)30L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar)));
    report_significant_count_by_lengths_slot(Qsimple_unsigned_byte_8_arrays,
	    sort(4,ISVREF(counter,(SI_Long)31L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar)));
    report_significant_count_by_lengths_slot(Qdouble_float_arrays,sort(4,
	    ISVREF(counter,(SI_Long)32L),SYMBOL_FUNCTION(Qnum_lt),Kkey,
	    SYMBOL_FUNCTION(Qcar)));
    report_significant_count_by_lengths_slot(Qadjustable_strings,sort(4,
	    ISVREF(counter,(SI_Long)33L),SYMBOL_FUNCTION(Qnum_lt),Kkey,
	    SYMBOL_FUNCTION(Qcar)));
    report_significant_count_by_lengths_slot(Qsimple_strings,sort(4,
	    ISVREF(counter,(SI_Long)34L),SYMBOL_FUNCTION(Qnum_lt),Kkey,
	    SYMBOL_FUNCTION(Qcar)));
    return report_significant_count_by_lengths_slot(Qframe_vectors,sort(4,
	    ISVREF(counter,(SI_Long)35L),SYMBOL_FUNCTION(Qnum_lt),Kkey,
	    SYMBOL_FUNCTION(Qcar)));
}

/* REPORT-DIFF-IN-SINGLE-COUNTER-SLOT */
Object report_diff_in_single_counter_slot(slot,count_1,count_2)
    Object slot, count_1, count_2;
{
    x_note_fn_call(165,72);
    if ( !FIXNUM_EQ(count_1,count_2))
	return format((SI_Long)6L,T,"~&~s~vt~s/~s~%",slot,
		Tab_length_for_counter_report,count_1,count_2);
    else
	return VALUES_1(Nil);
}

/* REPORT-DIFF-IN-COUNTER-BY-LENGTHS-SLOT */
Object report_diff_in_counter_by_lengths_slot(slot,list_by_lengths_1,
	    list_by_lengths_2)
    Object slot, list_by_lengths_1, list_by_lengths_2;
{
    Object number_of_lengths_1, number_of_lengths_2, length_1, count_1;
    Object ab_loop_list_, length_2, count_2, ab_loop_list__1, ab_loop_it_;
    Object ab_loop_desetq_, temp_1, list_by_lengths_2_new_value;
    Object list_by_lengths_2_old_value, ab_loop_destructure_, length_2_qm;
    Object count_2_qm, offset, gensymed_symbol;
    char temp;

    x_note_fn_call(165,73);
    number_of_lengths_1 = length(list_by_lengths_1);
    number_of_lengths_2 = length(list_by_lengths_2);
    temp = FIXNUM_NE(number_of_lengths_1,number_of_lengths_2);
    if (temp);
    else {
	length_1 = Nil;
	count_1 = Nil;
	ab_loop_list_ = list_by_lengths_1;
	length_2 = Nil;
	count_2 = Nil;
	ab_loop_list__1 = list_by_lengths_2;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	length_1 = CAR(ab_loop_desetq_);
	count_1 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	length_2 = CAR(ab_loop_desetq_);
	count_2 = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp_1 = NUM_NE(length_1,length_2) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = NUM_NE(count_1,count_2) ? T : Nil;
	ab_loop_it_ = temp_1;
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
	format((SI_Long)3L,T,"~&~s:",slot);
	if (FIXNUM_LT(number_of_lengths_1,number_of_lengths_2)) {
	    list_by_lengths_2_new_value = list_by_lengths_1;
	    list_by_lengths_1 = list_by_lengths_2;
	    list_by_lengths_2 = list_by_lengths_2_new_value;
	}
	length_1 = Nil;
	count_1 = Nil;
	ab_loop_list_ = list_by_lengths_1;
	list_by_lengths_2_old_value = list_by_lengths_2;
	temp_1 = FIRST(list_by_lengths_2_old_value);
	list_by_lengths_2 = REST(list_by_lengths_2_old_value);
	ab_loop_destructure_ = temp_1;
	length_2_qm = Nil;
	count_2_qm = Nil;
	length_2_qm = CAR(ab_loop_destructure_);
	count_2_qm = CDR(ab_loop_destructure_);
	offset = FIX((SI_Long)0L);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	length_1 = CAR(ab_loop_desetq_);
	count_1 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      next_loop_2:
	if ( !TRUEP(length_2_qm))
	    goto end_loop_2;
	if ( !NUM_LT(length_2_qm,length_1))
	    goto end_loop_2;
	format((SI_Long)5L,T,"~vt(~s . 0/~s)~%",
		add(Tab_length_for_counter_report,offset),length_2_qm,
		count_2_qm);
	if (zerop(offset))
	    offset = FIX((SI_Long)2L);
	list_by_lengths_2_old_value = list_by_lengths_2;
	temp_1 = FIRST(list_by_lengths_2_old_value);
	list_by_lengths_2 = REST(list_by_lengths_2_old_value);
	gensymed_symbol = temp_1;
	length_2_qm = CAR(gensymed_symbol);
	count_2_qm = CDR(gensymed_symbol);
	goto next_loop_2;
      end_loop_2:
	if (length_2_qm && NUM_EQ(length_1,length_2_qm)) {
	    format((SI_Long)6L,T,"~vt(~s . ~s/~s)~%",
		    add(Tab_length_for_counter_report,offset),length_1,
		    count_1,count_2_qm);
	    list_by_lengths_2_old_value = list_by_lengths_2;
	    temp_1 = FIRST(list_by_lengths_2_old_value);
	    list_by_lengths_2 = REST(list_by_lengths_2_old_value);
	    gensymed_symbol = temp_1;
	    length_2_qm = CAR(gensymed_symbol);
	    count_2_qm = CDR(gensymed_symbol);
	}
	else
	    format((SI_Long)5L,T,"~vt(~s . ~s/0)~%",
		    add(Tab_length_for_counter_report,offset),length_1,
		    count_1);
	if (zerop(offset))
	    offset = FIX((SI_Long)2L);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COUNTER-DIFF */
Object counter_diff(counter_1,counter_2)
    Object counter_1, counter_2;
{
    Object temp;

    x_note_fn_call(165,74);
    report_diff_in_single_counter_slot(Qvector_slots,ISVREF(counter_1,
	    (SI_Long)16L),ISVREF(counter_2,(SI_Long)16L));
    report_diff_in_single_counter_slot(Quser_vector_slots,ISVREF(counter_1,
	    (SI_Long)17L),ISVREF(counter_2,(SI_Long)17L));
    report_diff_in_single_counter_slot(Qlookup_slots,ISVREF(counter_1,
	    (SI_Long)18L),ISVREF(counter_2,(SI_Long)18L));
    report_diff_in_single_counter_slot(Qdefaulted_vector_slots,
	    ISVREF(counter_1,(SI_Long)19L),ISVREF(counter_2,(SI_Long)19L));
    report_diff_in_single_counter_slot(Qdefaulted_user_vector_slots,
	    ISVREF(counter_1,(SI_Long)20L),ISVREF(counter_2,(SI_Long)20L));
    report_diff_in_single_counter_slot(Qdefaulted_lookup_slots,
	    ISVREF(counter_1,(SI_Long)21L),ISVREF(counter_2,(SI_Long)21L));
    report_diff_in_single_counter_slot(Qconses,ISVREF(counter_1,
	    (SI_Long)22L),ISVREF(counter_2,(SI_Long)22L));
    report_diff_in_single_counter_slot(Qsymbols,ISVREF(counter_1,
	    (SI_Long)23L),ISVREF(counter_2,(SI_Long)23L));
    report_diff_in_single_counter_slot(Qdouble_floats,ISVREF(counter_1,
	    (SI_Long)24L),ISVREF(counter_2,(SI_Long)24L));
    report_diff_in_single_counter_slot(Qfixnums,ISVREF(counter_1,
	    (SI_Long)25L),ISVREF(counter_2,(SI_Long)25L));
    report_diff_in_single_counter_slot(Qcharacters,ISVREF(counter_1,
	    (SI_Long)26L),ISVREF(counter_2,(SI_Long)26L));
    report_diff_in_single_counter_slot(Qimmediates,ISVREF(counter_1,
	    (SI_Long)28L),ISVREF(counter_2,(SI_Long)28L));
    temp = sort(4,ISVREF(counter_1,(SI_Long)29L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar));
    report_diff_in_counter_by_lengths_slot(Qsimple_general_arrays,temp,
	    sort(4,ISVREF(counter_2,(SI_Long)29L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar)));
    temp = sort(4,ISVREF(counter_1,(SI_Long)30L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar));
    report_diff_in_counter_by_lengths_slot(Qsimple_unsigned_byte_16_arrays,
	    temp,sort(4,ISVREF(counter_2,(SI_Long)30L),
	    SYMBOL_FUNCTION(Qnum_lt),Kkey,SYMBOL_FUNCTION(Qcar)));
    temp = sort(4,ISVREF(counter_1,(SI_Long)31L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar));
    report_diff_in_counter_by_lengths_slot(Qsimple_unsigned_byte_8_arrays,
	    temp,sort(4,ISVREF(counter_2,(SI_Long)31L),
	    SYMBOL_FUNCTION(Qnum_lt),Kkey,SYMBOL_FUNCTION(Qcar)));
    temp = sort(4,ISVREF(counter_1,(SI_Long)32L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar));
    report_diff_in_counter_by_lengths_slot(Qdouble_float_arrays,temp,
	    sort(4,ISVREF(counter_2,(SI_Long)32L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar)));
    temp = sort(4,ISVREF(counter_1,(SI_Long)33L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar));
    report_diff_in_counter_by_lengths_slot(Qadjustable_strings,temp,sort(4,
	    ISVREF(counter_2,(SI_Long)33L),SYMBOL_FUNCTION(Qnum_lt),Kkey,
	    SYMBOL_FUNCTION(Qcar)));
    temp = sort(4,ISVREF(counter_1,(SI_Long)34L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar));
    report_diff_in_counter_by_lengths_slot(Qsimple_strings,temp,sort(4,
	    ISVREF(counter_2,(SI_Long)34L),SYMBOL_FUNCTION(Qnum_lt),Kkey,
	    SYMBOL_FUNCTION(Qcar)));
    temp = sort(4,ISVREF(counter_1,(SI_Long)35L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar));
    return report_diff_in_counter_by_lengths_slot(Qframe_vectors,temp,
	    sort(4,ISVREF(counter_2,(SI_Long)35L),SYMBOL_FUNCTION(Qnum_lt),
	    Kkey,SYMBOL_FUNCTION(Qcar)));
}

DEFINE_VARIABLE_WITH_SYMBOL(Memory_category_count, Qmemory_category_count);

/* INITIALIZE-MEMORY-CATEGORY-COUNT */
Object initialize_memory_category_count()
{
    x_note_fn_call(165,75);
    return length(Object_pool_meters);
}

/* MEMORY-CATEGORY-COUNT-LISP-SIDE */
Object memory_category_count_lisp_side()
{
    x_note_fn_call(165,76);
    return VALUES_1(Memory_category_count);
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_memory_stats_snapshot, Qlast_memory_stats_snapshot);

/* INITIALIZE-LAST-MEMORY-STATS-SNAPSHOT */
Object initialize_last_memory_stats_snapshot()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(165,77);
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(Memory_category_count);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    ab_loopvar__2 = LIST_1(LIST_2(FIX((SI_Long)0L),FIX((SI_Long)0L)));
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* SNAPSHOT-MEMORY-LEVELS */
Object snapshot_memory_levels()
{
    Object pool_entry, ab_loop_list_, cons_holding_levels, ab_loop_iter_flag_;
    Object temp, temp_1;

    x_note_fn_call(165,78);
    pool_entry = Nil;
    ab_loop_list_ = Object_pool_meters;
    cons_holding_levels = Last_memory_stats_snapshot;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pool_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	cons_holding_levels = M_CDR(cons_holding_levels);
    if ( !TRUEP(cons_holding_levels))
	goto end_loop;
    temp = CAR(cons_holding_levels);
    temp_1 = pool_entry_memory_usage_in_bytes(pool_entry);
    M_FIRST(temp) = temp_1;
    temp = CAR(cons_holding_levels);
    temp_1 = pool_entry_object_count(pool_entry);
    M_SECOND(temp) = temp_1;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* SNAPSHOT-MEMORY-LEVELS-LISP-SIDE */
Object snapshot_memory_levels_lisp_side()
{
    x_note_fn_call(165,79);
    snapshot_memory_levels();
    return VALUES_1(Evaluation_true_value);
}

static Object list_constant_2;     /* # */

static Object Qunsigned_8_bit_vector;  /* unsigned-8-bit-vector */

static Object string_constant;     /* "UNSIGNED-BYTE-~a" */

static Object string_constant_1;   /* "SIMPLE-~a-LONG-~a-ARRAY" */

static Object string_constant_2;   /* "SIMPLE-~a-ARRAY" */

static Object string_constant_3;   /* "SIMPLE-~a-LONG-ARAY" */

static Object string_constant_4;   /* "~a" */

/* MAP-ENCLOSING-MEMORY-CATEGORY-TO-SYMBOL */
Object map_enclosing_memory_category_to_symbol(enclosing_memory_category)
    Object enclosing_memory_category;
{
    Object gensymed_symbol, element_type, length_qm, specific_length_qm;
    Object specific_element_type_qm, temp;

    x_note_fn_call(165,80);
    if (SYMBOLP(enclosing_memory_category))
	return VALUES_1(enclosing_memory_category);
    else if (EQUAL(enclosing_memory_category,list_constant_2))
	return VALUES_1(Qunsigned_8_bit_vector);
    else if (CONSP(enclosing_memory_category) && 
	    EQ(FIRST(enclosing_memory_category),Qsimple_array)) {
	gensymed_symbol = enclosing_memory_category;
	gensymed_symbol = CDR(gensymed_symbol);
	element_type = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol = CAR(gensymed_symbol);
	length_qm = CAR(gensymed_symbol);
	specific_length_qm =  !TRUEP(length_qm) || EQ(length_qm,Qstar) ? 
		Nil : length_qm;
	if (EQ(element_type,T))
	    specific_element_type_qm = Nil;
	else if (SYMBOLP(element_type))
	    specific_element_type_qm = element_type;
	else {
	    temp = FIRST(element_type);
	    if (EQUAL(temp,Qunsigned_byte))
		specific_element_type_qm = intern_text_string(1,
			tformat_text_string(2,string_constant,
			SECOND(element_type)));
	    else
		specific_element_type_qm = Nil;
	}
	if (specific_element_type_qm && specific_length_qm)
	    return intern_text_string(1,tformat_text_string(3,
		    string_constant_1,specific_length_qm,
		    specific_element_type_qm));
	else if (specific_element_type_qm)
	    return intern_text_string(1,tformat_text_string(2,
		    string_constant_2,specific_element_type_qm));
	else if (specific_length_qm)
	    return intern_text_string(1,tformat_text_string(2,
		    string_constant_3,specific_length_qm));
	else
	    return VALUES_1(Qsimple_array);
    }
    else
	return intern_text_string(1,tformat_text_string(2,
		string_constant_4,enclosing_memory_category));
}

static Object list_constant_3;     /* # */

/* GET-MEMORY-ELEMENT-BYTE-SIZE-IF-POSSIBLE */
Object get_memory_element_byte_size_if_possible(enclosing_memory_category)
    Object enclosing_memory_category;
{
    Object gensymed_symbol, element_type, length_qm, specific_length_qm, temp;

    x_note_fn_call(165,81);
    if (EQ(enclosing_memory_category,Qcons))
	return size_of_cons();
    else if (CONSP(enclosing_memory_category) && 
	    EQ(FIRST(enclosing_memory_category),Qsimple_array)) {
	gensymed_symbol = enclosing_memory_category;
	gensymed_symbol = CDR(gensymed_symbol);
	element_type = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol = CAR(gensymed_symbol);
	length_qm = CAR(gensymed_symbol);
	specific_length_qm =  !TRUEP(length_qm) || EQ(length_qm,Qstar) ? 
		Nil : length_qm;
	if (specific_length_qm && CONSP(element_type) && 
		EQ(FIRST(element_type),Qunsigned_byte)) {
	    temp = SECOND(element_type);
	    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		    FIXNUM_LE(temp,FIX((SI_Long)127L))))
		return VALUES_1(Nil);
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 8:
		    return size_of_simple_unsigned_byte_8_array(specific_length_qm);
		  case 16:
		    return size_of_simple_unsigned_byte_16_array(specific_length_qm);
		  default:
		    return VALUES_1(Nil);
		}
	}
	else if (specific_length_qm && memq_function(element_type,
		list_constant_3))
	    return size_of_double_float_array(specific_length_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

static Object Qnone;               /* none */

/* MEMORY-CATEGORY-INFO-LISP-SIDE */
Object memory_category_info_lisp_side(g2_category_number)
    Object g2_category_number;
{
    Object category_number, category_index, pool_entry, g2_category_name;
    Object enclosing_category, g2_enclosing_category_name, current_level;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, g2_current_level, element_byte_size_qm;
    Object g2_element_byte_size, element_count, g2_element_count, temp_2;
    Object g2_byte_difference_from_last_stats;
    Object g2_element_difference_from_last_stats, new_float_1;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(165,82);
    category_number = g2_category_number;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (FIXNUM_PLUSP(category_number) && FIXNUM_LE(category_number,
		Memory_category_count)) {
	    category_index = FIXNUM_SUB1(category_number);
	    pool_entry = nth(category_index,Object_pool_meters);
	    g2_category_name = pool_entry_name(pool_entry);
	    enclosing_category = pool_entry_data_type(pool_entry);
	    g2_enclosing_category_name = 
		    map_enclosing_memory_category_to_symbol(enclosing_category);
	    current_level = pool_entry_memory_usage_in_bytes(pool_entry);
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    aref_new_value = (double)IFIX(current_level);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    g2_current_level = new_float;
	    element_byte_size_qm = 
		    get_memory_element_byte_size_if_possible(enclosing_category);
	    g2_element_byte_size = element_byte_size_qm ? 
		    element_byte_size_qm : FIX((SI_Long)0L);
	    element_count = pool_entry_object_count(pool_entry);
	    g2_element_count = element_count;
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    temp_2 = nth(category_index,Last_memory_stats_snapshot);
	    aref_new_value = (double)IFIX(FIXNUM_MINUS(current_level,
		    FIRST(temp_2)));
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    g2_byte_difference_from_last_stats = new_float;
	    temp_2 = nth(category_index,Last_memory_stats_snapshot);
	    g2_element_difference_from_last_stats = 
		    FIXNUM_MINUS(element_count,SECOND(temp_2));
	    result = VALUES_7(g2_category_name,g2_enclosing_category_name,
		    g2_element_byte_size,g2_element_count,g2_current_level,
		    g2_byte_difference_from_last_stats,
		    g2_element_difference_from_last_stats);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    new_float_1 = amf_result;
	    DFLOAT_ISASET_1(new_float_1,(SI_Long)0L,0.0);
	    result = VALUES_7(Qnone,Qnone,FIX((SI_Long)0L),
		    FIX((SI_Long)0L),new_float,new_float_1,FIX((SI_Long)0L));
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* G2-RECLAIM-SYMBOL */
Object g2_reclaim_symbol(symbol,package)
    Object symbol, package;
{
    x_note_fn_call(165,83);
    return unintern(symbol,package);
}

void mem_sysproc_INIT()
{
    Object temp, temp_1, pushnew_arg_1, pushnew_arg_3, pushnew_arg_5;
    Object special_slot_names_for_memory_walk_new_value, gensymed_symbol;
    Object Qg2_reclaim_symbol, Qfunction_keeps_procedure_environment_valid_qm;
    Object AB_package, Qmemory_category_info_lisp_side, Qgensym_float;
    Object Qsnapshot_memory_levels_lisp_side;
    Object Qinitialize_last_memory_stats_snapshot, list_constant_10;
    Object Qmem_sysproc, Qmemory_category_count_lisp_side;
    Object Qinitialize_memory_category_count, list_constant_9;
    Object Qg2_measure_memory_fields_lisp_side, Qg2_measure_memory_lisp_side;
    Object Qlist_of_subclasses_of_item, list_constant_8;
    Object Qchart_initial_update_task_qm, Qprocedure_invocations;
    Object Qscheduled_remote_procedure_starts, Qlist_structure;
    Object Qwalk_memory_for_value_of_kb_state_changes_previous_cons_qm;
    Object Qkb_state_changes_previous_cons_qm;
    Object Qwalk_memory_for_value_of_currently_up_to_date_image_planes;
    Object Qcurrently_up_to_date_image_planes;
    Object Qwalk_memory_for_value_of_image_planes_this_is_on;
    Object Qimage_planes_this_is_on, Qwalk_memory_for_value_of_superblock_qm;
    Object Qsuperblock_qm, Qwalk_memory_for_value_of_cell_array, Qcell_array;
    Object Qwalk_memory_for_value_of_parent_attribute_name;
    Object Qparent_attribute_name, Qwalk_memory_for_value_of_parent_frame;
    Object Qparent_frame, Qwalk_memory_for_value_of_menus_for_this;
    Object Qmenus_for_this;
    Object Qwalk_memory_for_value_of_class_specific_instances_reverse_pointer;
    Object Qclass_specific_instances_reverse_pointer;
    Object Qwalk_memory_for_value_of_class_specific_instances_forward_pointer;
    Object Qclass_specific_instances_forward_pointer;
    Object Qwalk_memory_for_value_of_class_description_slot;
    Object Qclass_description_slot, Qwalk_memory_for_value_of_lookup_structure;
    Object Qlookup_structure, Qwalk_memory_for_value_of_class, Qab_class;
    Object Qwalk_memory_for_value_of_backward_chain_new_rules;
    Object Qbackward_chain_new_rules, Qwalk_memory_for_value_of_connections;
    Object Qconnections, Qwalk_memory_for_value_of_subblocks, Qsubblocks;
    Object Qwalk_memory_for_value_of_list_elements_for_item;
    Object Qlist_elements_for_item;
    Object Qwalk_memory_for_value_of_relation_instances, Qrelation_instances;
    Object Qwalk_memory_for_value_of_things_interested_in_this_variable;
    Object Qthings_interested_in_this_variable;
    Object Qwalk_memory_for_value_of_things_this_variable_is_interested_in;
    Object Qthings_this_variable_is_interested_in;
    Object Qwalk_memory_for_value_of_slot_group_for_block_qm;
    Object Qslot_group_for_block_qm;
    Object Qwalk_memory_for_value_of_icon_description;
    Object Qwalk_memory_for_value_of_uuid_block_item_reference_table;
    Object Quuid_block_item_reference_table;
    Object Qwalk_memory_for_value_of_window_for_graph_rendering;
    Object Qwindow_for_graph_rendering;
    Object Qwalk_memory_for_value_of_image_plane_for_graph_rendering_qm;
    Object Qimage_plane_for_graph_rendering_qm;
    Object Qwalk_memory_for_value_of_lru_element_previous_element;
    Object Qlru_element_previous_element;
    Object Qwalk_memory_for_value_of_lru_element_next_element;
    Object Qlru_element_next_element, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object list_constant_7, Qmake_items_encountered_in_memory_walk;
    Object Qout_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors;
    Object Qitems_encountered_in_memory_walk_hash_table_hash_vector_131_vector_memory_usage;
    Object string_constant_20, Qutilities2, Qslot_value_writer;
    Object Qwrite_frame_vectors_from_slot, Qwrite_simple_strings_from_slot;
    Object Qwrite_adjustable_strings_from_slot;
    Object Qwrite_double_float_arrays_from_slot;
    Object Qwrite_simple_unsigned_byte_8_arrays_from_slot;
    Object Qwrite_simple_unsigned_byte_16_arrays_from_slot;
    Object Qwrite_simple_general_arrays_from_slot, list_constant_6;
    Object list_constant_5, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, list_constant_4;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5;

    x_note_fn_call(165,84);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qmemory_profile = STATIC_SYMBOL("MEMORY-PROFILE",AB_package);
    list_constant_4 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qmemory_profile,list_constant_4);
    string_constant_5 = STATIC_STRING("0");
    string_constant_6 = 
	    STATIC_STRING("13Gy4z8r83dsy83dsy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83diy83diy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83UT");
    string_constant_7 = 
	    STATIC_STRING("y83UTy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83JTy83JTy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83JSy83JSy83V9y8");
    string_constant_8 = 
	    STATIC_STRING("3V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83JRy83JRy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83Imy83Imy83V9y83V9y0k001o1l");
    string_constant_9 = 
	    STATIC_STRING("8l1l83Fy1m8p83-qy1l8o000004z8r83bGy83bGy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83K6y83K6y83V9y83V9y0k001o1l8l1l83Fy1m8p");
    string_constant_10 = 
	    STATIC_STRING("83-qy1l8o000004z8r83LYy83LYy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83Hqy83Hqy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000");
    string_constant_11 = 
	    STATIC_STRING("004z8r83MWy83MWy83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83S0y83S0y83V9y83V9y0k001o1l8l1l83Fy1m8p83-qy1l8o000004z8r83a2y8");
    string_constant_12 = 
	    STATIC_STRING("3a2y83V9y83V9y00001o1l8l1l83Fy1m8p83a2y1l8o000004z8r83a5y83a5y83V9y83V9y00001o1l8l1l83Fy1m8p83a5y1l8o000004z8r83a6y83a6y83V9y83V");
    string_constant_13 = 
	    STATIC_STRING("9y00001o1l8l1l83Fy1m8p83a6y1l8o000004z8r83K5y83K5y83V9y83V9y00001o1l8l1l83Fy1m8p83K5y1l8o000004z8r83GVy83GVy83V9y83V9y00001o1l8l");
    string_constant_14 = 
	    STATIC_STRING("1l83Fy1m8p83GVy1l8o000004z8r83a4y83a4y83V9y83V9y00001o1l8l1l83Fy1m8p83a4y1l8o000004z8r83MMy83MMy83V9y83V9y00001o1l8l1l83Fy1m8p83");
    string_constant_15 = STATIC_STRING("MMy1l8o00000");
    string_constant_16 = 
	    STATIC_STRING("13Iy8q1m83V9y1l9k1p83dsyk83Fy1m8p83-qy8o1p83diyk83Fy1m8p83-qy8o1p83UTyk83Fy1m8p83-qy8o1p83JTyk83Fy1m8p83-qy8o1p83JSyk83Fy1m8p83-");
    string_constant_17 = 
	    STATIC_STRING("qy8o1p83JRyk83Fy1m8p83-qy8o1p83Imyk83Fy1m8p83-qy8o1p83bGyk83Fy1m8p83-qy8o1p83K6yk83Fy1m8p83-qy8o1p83LYyk83Fy1m8p83-qy8o1p83Hqyk8");
    string_constant_18 = 
	    STATIC_STRING("3Fy1m8p83-qy8o1p83MWyk83Fy1m8p83-qy8o1p83S0yk83Fy1m8p83-qy8o1p83a2y083Fy1m8p83a2y8o1p83a5y083Fy1m8p83a5y8o1p83a6y083Fy1m8p83a6y8");
    string_constant_19 = 
	    STATIC_STRING("o1p83K5y083Fy1m8p83K5y8o1p83GVy083Fy1m8p83GVy8o1p83a4y083Fy1m8p83a4y8o1p83MMy083Fy1m8p83MMy8o");
    temp = regenerate_optimized_constant(string_constant_5);
    temp_1 = regenerate_optimized_constant(list(10,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qmemory_profile,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_4(string_constant_16,
	    string_constant_17,string_constant_18,string_constant_19)),Nil);
    Qvector_slots = STATIC_SYMBOL("VECTOR-SLOTS",AB_package);
    Quser_vector_slots = STATIC_SYMBOL("USER-VECTOR-SLOTS",AB_package);
    Qlookup_slots = STATIC_SYMBOL("LOOKUP-SLOTS",AB_package);
    Qdefaulted_vector_slots = STATIC_SYMBOL("DEFAULTED-VECTOR-SLOTS",
	    AB_package);
    Qdefaulted_user_vector_slots = 
	    STATIC_SYMBOL("DEFAULTED-USER-VECTOR-SLOTS",AB_package);
    Qdefaulted_lookup_slots = STATIC_SYMBOL("DEFAULTED-LOOKUP-SLOTS",
	    AB_package);
    Qconses = STATIC_SYMBOL("CONSES",AB_package);
    Qsymbols = STATIC_SYMBOL("SYMBOLS",AB_package);
    Qdouble_floats = STATIC_SYMBOL("DOUBLE-FLOATS",AB_package);
    Qfixnums = STATIC_SYMBOL("FIXNUMS",AB_package);
    Qcharacters = STATIC_SYMBOL("CHARACTERS",AB_package);
    Qimmediates = STATIC_SYMBOL("IMMEDIATES",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)12L,Qvector_slots,
	    Quser_vector_slots,Qlookup_slots,Qdefaulted_vector_slots,
	    Qdefaulted_user_vector_slots,Qdefaulted_lookup_slots,Qconses,
	    Qsymbols,Qdouble_floats,Qfixnums,Qcharacters,Qimmediates);
    Single_counter_slots_in_memory_profile = list_constant_5;
    Qsimple_general_arrays = STATIC_SYMBOL("SIMPLE-GENERAL-ARRAYS",AB_package);
    Qsimple_unsigned_byte_16_arrays = 
	    STATIC_SYMBOL("SIMPLE-UNSIGNED-BYTE-16-ARRAYS",AB_package);
    Qsimple_unsigned_byte_8_arrays = 
	    STATIC_SYMBOL("SIMPLE-UNSIGNED-BYTE-8-ARRAYS",AB_package);
    Qdouble_float_arrays = STATIC_SYMBOL("DOUBLE-FLOAT-ARRAYS",AB_package);
    Qadjustable_strings = STATIC_SYMBOL("ADJUSTABLE-STRINGS",AB_package);
    Qsimple_strings = STATIC_SYMBOL("SIMPLE-STRINGS",AB_package);
    Qframe_vectors = STATIC_SYMBOL("FRAME-VECTORS",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)7L,Qsimple_general_arrays,
	    Qsimple_unsigned_byte_16_arrays,Qsimple_unsigned_byte_8_arrays,
	    Qdouble_float_arrays,Qadjustable_strings,Qsimple_strings,
	    Qframe_vectors);
    By_length_slots_in_memory_profile = list_constant_6;
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_simple_general_arrays_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMPLE-GENERAL-ARRAYS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simple_general_arrays_from_slot,
	    STATIC_FUNCTION(write_simple_general_arrays_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qsimple_general_arrays,
	    SYMBOL_FUNCTION(Qwrite_simple_general_arrays_from_slot),
	    Qslot_value_writer);
    Qwrite_simple_unsigned_byte_16_arrays_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMPLE-UNSIGNED-BYTE-16-ARRAYS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simple_unsigned_byte_16_arrays_from_slot,
	    STATIC_FUNCTION(write_simple_unsigned_byte_16_arrays_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimple_unsigned_byte_16_arrays,
	    SYMBOL_FUNCTION(Qwrite_simple_unsigned_byte_16_arrays_from_slot),
	    Qslot_value_writer);
    Qwrite_simple_unsigned_byte_8_arrays_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMPLE-UNSIGNED-BYTE-8-ARRAYS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simple_unsigned_byte_8_arrays_from_slot,
	    STATIC_FUNCTION(write_simple_unsigned_byte_8_arrays_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimple_unsigned_byte_8_arrays,
	    SYMBOL_FUNCTION(Qwrite_simple_unsigned_byte_8_arrays_from_slot),
	    Qslot_value_writer);
    Qwrite_double_float_arrays_from_slot = 
	    STATIC_SYMBOL("WRITE-DOUBLE-FLOAT-ARRAYS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_double_float_arrays_from_slot,
	    STATIC_FUNCTION(write_double_float_arrays_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qdouble_float_arrays,
	    SYMBOL_FUNCTION(Qwrite_double_float_arrays_from_slot),
	    Qslot_value_writer);
    Qwrite_adjustable_strings_from_slot = 
	    STATIC_SYMBOL("WRITE-ADJUSTABLE-STRINGS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_adjustable_strings_from_slot,
	    STATIC_FUNCTION(write_adjustable_strings_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qadjustable_strings,
	    SYMBOL_FUNCTION(Qwrite_adjustable_strings_from_slot),
	    Qslot_value_writer);
    Qwrite_simple_strings_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMPLE-STRINGS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simple_strings_from_slot,
	    STATIC_FUNCTION(write_simple_strings_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qsimple_strings,
	    SYMBOL_FUNCTION(Qwrite_simple_strings_from_slot),
	    Qslot_value_writer);
    Qwrite_frame_vectors_from_slot = 
	    STATIC_SYMBOL("WRITE-FRAME-VECTORS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_frame_vectors_from_slot,
	    STATIC_FUNCTION(write_frame_vectors_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qframe_vectors,
	    SYMBOL_FUNCTION(Qwrite_frame_vectors_from_slot),
	    Qslot_value_writer);
    Qavailable_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors 
	    = 
	    STATIC_SYMBOL("AVAILABLE-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors 
	    = 
	    STATIC_SYMBOL("COUNT-OF-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors);
    record_system_variable(Qcount_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector 
	    == UNBOUND)
	Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_vector 
		= make_thread_array(Nil);
    Qout_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors 
	    = 
	    STATIC_SYMBOL("OUT-ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    Qitems_encountered_in_memory_walk_hash_table_hash_vector_131_vector_memory_usage 
	    = 
	    STATIC_SYMBOL("ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_20 = STATIC_STRING("1q83-bEy83*9y83-P-y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors);
    push_optimized_constant(Qitems_encountered_in_memory_walk_hash_table_hash_vector_131_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_20));
    SET_SYMBOL_FUNCTION(Qitems_encountered_in_memory_walk_hash_table_hash_vector_131_vector_memory_usage,
	    STATIC_FUNCTION(items_encountered_in_memory_walk_hash_table_hash_vector_131_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    STATIC_FUNCTION(out_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qitems_encountered_in_memory_walk_hash_table_tree_for_hash = 
	    STATIC_SYMBOL("ITEMS-ENCOUNTERED-IN-MEMORY-WALK-HASH-TABLE-TREE-FOR-HASH",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qitems_encountered_in_memory_walk = 
	    STATIC_SYMBOL("ITEMS-ENCOUNTERED-IN-MEMORY-WALK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qitems_encountered_in_memory_walk,
	    Items_encountered_in_memory_walk);
    Qmem_sysproc = STATIC_SYMBOL("MEM-SYSPROC",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_items_encountered_in_memory_walk = 
	    STATIC_SYMBOL("MAKE-ITEMS-ENCOUNTERED-IN-MEMORY-WALK",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_items_encountered_in_memory_walk,
	    STATIC_FUNCTION(make_items_encountered_in_memory_walk,NIL,
	    FALSE,0,0));
    list_constant_7 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_items_encountered_in_memory_walk);
    record_system_variable(Qitems_encountered_in_memory_walk,Qmem_sysproc,
	    list_constant_7,Qnil,Qnil,Qnil,Qnil);
    if (Subframe_depth == UNBOUND)
	Subframe_depth = FIX((SI_Long)0L);
    if (Memory_walk_verbose_p == UNBOUND)
	Memory_walk_verbose_p = Nil;
    if (Do_circularity_check_walking_through_conses_p == UNBOUND)
	Do_circularity_check_walking_through_conses_p = T;
    if (Do_circularity_check_walking_through_simple_vectors_p == UNBOUND)
	Do_circularity_check_walking_through_simple_vectors_p = Nil;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qfunctions = STATIC_SYMBOL("FUNCTIONS",AB_package);
    if (Special_slot_names_for_memory_walk == UNBOUND)
	Special_slot_names_for_memory_walk = Nil;
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    Qlru_element_next_element = STATIC_SYMBOL("LRU-ELEMENT-NEXT-ELEMENT",
	    AB_package);
    Qwalk_memory_for_value_of_lru_element_next_element = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-LRU-ELEMENT-NEXT-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_lru_element_next_element,
	    STATIC_FUNCTION(walk_memory_for_value_of_lru_element_next_element,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qlru_element_next_element,
	    Qwalk_memory_for_value_of_lru_element_next_element);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qlru_element_previous_element = 
	    STATIC_SYMBOL("LRU-ELEMENT-PREVIOUS-ELEMENT",AB_package);
    Qwalk_memory_for_value_of_lru_element_previous_element = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-LRU-ELEMENT-PREVIOUS-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_lru_element_previous_element,
	    STATIC_FUNCTION(walk_memory_for_value_of_lru_element_previous_element,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qlru_element_previous_element,
	    Qwalk_memory_for_value_of_lru_element_previous_element);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qimage_plane_for_graph_rendering_qm = 
	    STATIC_SYMBOL("IMAGE-PLANE-FOR-GRAPH-RENDERING\?",AB_package);
    Qwalk_memory_for_value_of_image_plane_for_graph_rendering_qm = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-IMAGE-PLANE-FOR-GRAPH-RENDERING\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_image_plane_for_graph_rendering_qm,
	    STATIC_FUNCTION(walk_memory_for_value_of_image_plane_for_graph_rendering_qm,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qimage_plane_for_graph_rendering_qm,
	    Qwalk_memory_for_value_of_image_plane_for_graph_rendering_qm);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qwindow_for_graph_rendering = 
	    STATIC_SYMBOL("WINDOW-FOR-GRAPH-RENDERING",AB_package);
    Qwalk_memory_for_value_of_window_for_graph_rendering = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-WINDOW-FOR-GRAPH-RENDERING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_window_for_graph_rendering,
	    STATIC_FUNCTION(walk_memory_for_value_of_window_for_graph_rendering,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qwindow_for_graph_rendering,
	    Qwalk_memory_for_value_of_window_for_graph_rendering);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Quuid_block_item_reference_table = 
	    STATIC_SYMBOL("UUID-BLOCK-ITEM-REFERENCE-TABLE",AB_package);
    Qwalk_memory_for_value_of_uuid_block_item_reference_table = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-UUID-BLOCK-ITEM-REFERENCE-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_uuid_block_item_reference_table,
	    STATIC_FUNCTION(walk_memory_for_value_of_uuid_block_item_reference_table,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Quuid_block_item_reference_table,
	    Qwalk_memory_for_value_of_uuid_block_item_reference_table);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qwalk_memory_for_value_of_icon_description = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-ICON-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_icon_description,
	    STATIC_FUNCTION(walk_memory_for_value_of_icon_description,NIL,
	    FALSE,3,3));
    pushnew_arg_1 = CONS(Qicon_description,
	    Qwalk_memory_for_value_of_icon_description);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    if (Size_of_icon_slot_group == UNBOUND)
	Size_of_icon_slot_group = FIX((SI_Long)7L);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qwalk_memory_for_value_of_slot_group_for_block_qm = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_slot_group_for_block_qm,
	    STATIC_FUNCTION(walk_memory_for_value_of_slot_group_for_block_qm,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qslot_group_for_block_qm,
	    Qwalk_memory_for_value_of_slot_group_for_block_qm);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qthings_this_variable_is_interested_in = 
	    STATIC_SYMBOL("THINGS-THIS-VARIABLE-IS-INTERESTED-IN",AB_package);
    Qwalk_memory_for_value_of_things_this_variable_is_interested_in = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-THINGS-THIS-VARIABLE-IS-INTERESTED-IN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_things_this_variable_is_interested_in,
	    STATIC_FUNCTION(walk_memory_for_value_of_things_this_variable_is_interested_in,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qthings_this_variable_is_interested_in,
	    Qwalk_memory_for_value_of_things_this_variable_is_interested_in);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qthings_interested_in_this_variable = 
	    STATIC_SYMBOL("THINGS-INTERESTED-IN-THIS-VARIABLE",AB_package);
    Qwalk_memory_for_value_of_things_interested_in_this_variable = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-THINGS-INTERESTED-IN-THIS-VARIABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_things_interested_in_this_variable,
	    STATIC_FUNCTION(walk_memory_for_value_of_things_interested_in_this_variable,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qthings_interested_in_this_variable,
	    Qwalk_memory_for_value_of_things_interested_in_this_variable);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qrelation_instances = STATIC_SYMBOL("RELATION-INSTANCES",AB_package);
    Qwalk_memory_for_value_of_relation_instances = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-RELATION-INSTANCES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_relation_instances,
	    STATIC_FUNCTION(walk_memory_for_value_of_relation_instances,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qrelation_instances,
	    Qwalk_memory_for_value_of_relation_instances);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qlist_elements_for_item = STATIC_SYMBOL("LIST-ELEMENTS-FOR-ITEM",
	    AB_package);
    Qwalk_memory_for_value_of_list_elements_for_item = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-LIST-ELEMENTS-FOR-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_list_elements_for_item,
	    STATIC_FUNCTION(walk_memory_for_value_of_list_elements_for_item,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qlist_elements_for_item,
	    Qwalk_memory_for_value_of_list_elements_for_item);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qsubblocks = STATIC_SYMBOL("SUBBLOCKS",AB_package);
    Qwalk_memory_for_value_of_subblocks = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-SUBBLOCKS",AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_subblocks,
	    STATIC_FUNCTION(walk_memory_for_value_of_subblocks,NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qsubblocks,Qwalk_memory_for_value_of_subblocks);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qconnections = STATIC_SYMBOL("CONNECTIONS",AB_package);
    Qwalk_memory_for_value_of_connections = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-CONNECTIONS",AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_connections,
	    STATIC_FUNCTION(walk_memory_for_value_of_connections,NIL,FALSE,
	    3,3));
    pushnew_arg_1 = CONS(Qconnections,Qwalk_memory_for_value_of_connections);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qbackward_chain_new_rules = STATIC_SYMBOL("BACKWARD-CHAIN-NEW-RULES",
	    AB_package);
    Qwalk_memory_for_value_of_backward_chain_new_rules = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-BACKWARD-CHAIN-NEW-RULES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_backward_chain_new_rules,
	    STATIC_FUNCTION(walk_memory_for_value_of_backward_chain_new_rules,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qbackward_chain_new_rules,
	    Qwalk_memory_for_value_of_backward_chain_new_rules);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qwalk_memory_for_value_of_class = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_class,
	    STATIC_FUNCTION(walk_memory_for_value_of_class,NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qab_class,Qwalk_memory_for_value_of_class);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qlookup_structure = STATIC_SYMBOL("LOOKUP-STRUCTURE",AB_package);
    Qwalk_memory_for_value_of_lookup_structure = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-LOOKUP-STRUCTURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_lookup_structure,
	    STATIC_FUNCTION(walk_memory_for_value_of_lookup_structure,NIL,
	    FALSE,3,3));
    pushnew_arg_1 = CONS(Qlookup_structure,
	    Qwalk_memory_for_value_of_lookup_structure);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qclass_description_slot = STATIC_SYMBOL("CLASS-DESCRIPTION-SLOT",
	    AB_package);
    Qwalk_memory_for_value_of_class_description_slot = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-CLASS-DESCRIPTION-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_class_description_slot,
	    STATIC_FUNCTION(walk_memory_for_value_of_class_description_slot,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qclass_description_slot,
	    Qwalk_memory_for_value_of_class_description_slot);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qclass_specific_instances_forward_pointer = 
	    STATIC_SYMBOL("CLASS-SPECIFIC-INSTANCES-FORWARD-POINTER",
	    AB_package);
    Qwalk_memory_for_value_of_class_specific_instances_forward_pointer = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-CLASS-SPECIFIC-INSTANCES-FORWARD-POINTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_class_specific_instances_forward_pointer,
	    STATIC_FUNCTION(walk_memory_for_value_of_class_specific_instances_forward_pointer,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qclass_specific_instances_forward_pointer,
	    Qwalk_memory_for_value_of_class_specific_instances_forward_pointer);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qclass_specific_instances_reverse_pointer = 
	    STATIC_SYMBOL("CLASS-SPECIFIC-INSTANCES-REVERSE-POINTER",
	    AB_package);
    Qwalk_memory_for_value_of_class_specific_instances_reverse_pointer = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-CLASS-SPECIFIC-INSTANCES-REVERSE-POINTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_class_specific_instances_reverse_pointer,
	    STATIC_FUNCTION(walk_memory_for_value_of_class_specific_instances_reverse_pointer,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qclass_specific_instances_reverse_pointer,
	    Qwalk_memory_for_value_of_class_specific_instances_reverse_pointer);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qmenus_for_this = STATIC_SYMBOL("MENUS-FOR-THIS",AB_package);
    Qwalk_memory_for_value_of_menus_for_this = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-MENUS-FOR-THIS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_menus_for_this,
	    STATIC_FUNCTION(walk_memory_for_value_of_menus_for_this,NIL,
	    FALSE,3,3));
    pushnew_arg_1 = CONS(Qmenus_for_this,
	    Qwalk_memory_for_value_of_menus_for_this);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qwalk_memory_for_value_of_parent_frame = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-PARENT-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_parent_frame,
	    STATIC_FUNCTION(walk_memory_for_value_of_parent_frame,NIL,
	    FALSE,3,3));
    pushnew_arg_1 = CONS(Qparent_frame,Qwalk_memory_for_value_of_parent_frame);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qwalk_memory_for_value_of_parent_attribute_name = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-PARENT-ATTRIBUTE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_parent_attribute_name,
	    STATIC_FUNCTION(walk_memory_for_value_of_parent_attribute_name,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qparent_attribute_name,
	    Qwalk_memory_for_value_of_parent_attribute_name);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qwalk_memory_for_value_of_cell_array = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-CELL-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_cell_array,
	    STATIC_FUNCTION(walk_memory_for_value_of_cell_array,NIL,FALSE,
	    3,3));
    pushnew_arg_1 = CONS(Qcell_array,Qwalk_memory_for_value_of_cell_array);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qsuperblock_qm = STATIC_SYMBOL("SUPERBLOCK\?",AB_package);
    Qwalk_memory_for_value_of_superblock_qm = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-SUPERBLOCK\?",AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_superblock_qm,
	    STATIC_FUNCTION(walk_memory_for_value_of_superblock_qm,NIL,
	    FALSE,3,3));
    pushnew_arg_1 = CONS(Qsuperblock_qm,
	    Qwalk_memory_for_value_of_superblock_qm);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qimage_planes_this_is_on = STATIC_SYMBOL("IMAGE-PLANES-THIS-IS-ON",
	    AB_package);
    Qwalk_memory_for_value_of_image_planes_this_is_on = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-IMAGE-PLANES-THIS-IS-ON",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_image_planes_this_is_on,
	    STATIC_FUNCTION(walk_memory_for_value_of_image_planes_this_is_on,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qimage_planes_this_is_on,
	    Qwalk_memory_for_value_of_image_planes_this_is_on);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qcurrently_up_to_date_image_planes = 
	    STATIC_SYMBOL("CURRENTLY-UP-TO-DATE-IMAGE-PLANES",AB_package);
    Qwalk_memory_for_value_of_currently_up_to_date_image_planes = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-CURRENTLY-UP-TO-DATE-IMAGE-PLANES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_currently_up_to_date_image_planes,
	    STATIC_FUNCTION(walk_memory_for_value_of_currently_up_to_date_image_planes,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qcurrently_up_to_date_image_planes,
	    Qwalk_memory_for_value_of_currently_up_to_date_image_planes);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qkb_state_changes_previous_cons_qm = 
	    STATIC_SYMBOL("KB-STATE-CHANGES-PREVIOUS-CONS\?",AB_package);
    Qwalk_memory_for_value_of_kb_state_changes_previous_cons_qm = 
	    STATIC_SYMBOL("WALK-MEMORY-FOR-VALUE-OF-KB-STATE-CHANGES-PREVIOUS-CONS\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwalk_memory_for_value_of_kb_state_changes_previous_cons_qm,
	    STATIC_FUNCTION(walk_memory_for_value_of_kb_state_changes_previous_cons_qm,
	    NIL,FALSE,3,3));
    pushnew_arg_1 = CONS(Qkb_state_changes_previous_cons_qm,
	    Qwalk_memory_for_value_of_kb_state_changes_previous_cons_qm);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcar);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    special_slot_names_for_memory_walk_new_value = adjoin(6,pushnew_arg_1,
	    Special_slot_names_for_memory_walk,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    Special_slot_names_for_memory_walk = 
	    special_slot_names_for_memory_walk_new_value;
    Qlist_structure = STATIC_SYMBOL("LIST-STRUCTURE",AB_package);
    Qscheduled_remote_procedure_starts = 
	    STATIC_SYMBOL("SCHEDULED-REMOTE-PROCEDURE-STARTS",AB_package);
    Qprocedure_invocations = STATIC_SYMBOL("PROCEDURE-INVOCATIONS",AB_package);
    Qchart_initial_update_task_qm = 
	    STATIC_SYMBOL("CHART-INITIAL-UPDATE-TASK\?",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)4L,Qlist_structure,
	    Qscheduled_remote_procedure_starts,Qprocedure_invocations,
	    Qchart_initial_update_task_qm);
    if (Slots_containing_circular_unnamed_simple_vectors == UNBOUND)
	Slots_containing_circular_unnamed_simple_vectors = list_constant_8;
    Qcompound_slot_descriptor = STATIC_SYMBOL("COMPOUND-SLOT-DESCRIPTOR",
	    AB_package);
    Q2d_image_plane_states = STATIC_SYMBOL("2D-IMAGE-PLANE-STATES",AB_package);
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    if (Bytes_consumed_by_one_undefaulted_lookup_slot == UNBOUND)
	Bytes_consumed_by_one_undefaulted_lookup_slot = FIX((SI_Long)8L);
    Qlist_of_subclasses_of_item = 
	    STATIC_SYMBOL("LIST-OF-SUBCLASSES-OF-ITEM",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qlist_of_subclasses_of_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qsymbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qlist_of_subclasses_of_item,
	    STATIC_FUNCTION(list_of_subclasses_of_item,NIL,FALSE,0,0));
    Qg2_measure_memory_lisp_side = 
	    STATIC_SYMBOL("G2-MEASURE-MEMORY-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_measure_memory_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_measure_memory_lisp_side,
	    STATIC_FUNCTION(g2_measure_memory_lisp_side,NIL,FALSE,1,1));
    Qg2_measure_memory_fields_lisp_side = 
	    STATIC_SYMBOL("G2-MEASURE-MEMORY-FIELDS-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_measure_memory_fields_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qsum = STATIC_SYMBOL("SUM",AB_package);
    Qother_arrays = STATIC_SYMBOL("OTHER-ARRAYS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_measure_memory_fields_lisp_side,
	    STATIC_FUNCTION(g2_measure_memory_fields_lisp_side,NIL,FALSE,0,0));
    if (Tab_length_for_counter_report == UNBOUND)
	Tab_length_for_counter_report = FIX((SI_Long)25L);
    Qmemory_category_count = STATIC_SYMBOL("MEMORY-CATEGORY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmemory_category_count,Memory_category_count);
    Qinitialize_memory_category_count = 
	    STATIC_SYMBOL("INITIALIZE-MEMORY-CATEGORY-COUNT",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_memory_category_count);
    record_system_variable(Qmemory_category_count,Qmem_sysproc,
	    list_constant_9,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_memory_category_count,
	    STATIC_FUNCTION(initialize_memory_category_count,NIL,FALSE,0,0));
    Qmemory_category_count_lisp_side = 
	    STATIC_SYMBOL("MEMORY-CATEGORY-COUNT-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qmemory_category_count_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qmemory_category_count_lisp_side,
	    STATIC_FUNCTION(memory_category_count_lisp_side,NIL,FALSE,0,0));
    Qlast_memory_stats_snapshot = 
	    STATIC_SYMBOL("LAST-MEMORY-STATS-SNAPSHOT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_memory_stats_snapshot,
	    Last_memory_stats_snapshot);
    Qinitialize_last_memory_stats_snapshot = 
	    STATIC_SYMBOL("INITIALIZE-LAST-MEMORY-STATS-SNAPSHOT",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_last_memory_stats_snapshot);
    record_system_variable(Qlast_memory_stats_snapshot,Qmem_sysproc,
	    list_constant_10,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_last_memory_stats_snapshot,
	    STATIC_FUNCTION(initialize_last_memory_stats_snapshot,NIL,
	    FALSE,0,0));
    Qsnapshot_memory_levels_lisp_side = 
	    STATIC_SYMBOL("SNAPSHOT-MEMORY-LEVELS-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qsnapshot_memory_levels_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qsnapshot_memory_levels_lisp_side,
	    STATIC_FUNCTION(snapshot_memory_levels_lisp_side,NIL,FALSE,0,0));
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qvector,list_constant);
    Qunsigned_8_bit_vector = STATIC_SYMBOL("UNSIGNED-8-BIT-VECTOR",AB_package);
    string_constant = STATIC_STRING("UNSIGNED-BYTE-~a");
    string_constant_1 = STATIC_STRING("SIMPLE-~a-LONG-~a-ARRAY");
    string_constant_2 = STATIC_STRING("SIMPLE-~a-ARRAY");
    string_constant_3 = STATIC_STRING("SIMPLE-~a-LONG-ARAY");
    string_constant_4 = STATIC_STRING("~a");
    Qgensym_float = STATIC_SYMBOL("GENSYM-FLOAT",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qdouble_float,Qgensym_float);
    Qmemory_category_info_lisp_side = 
	    STATIC_SYMBOL("MEMORY-CATEGORY-INFO-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qmemory_category_info_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    SET_SYMBOL_FUNCTION(Qmemory_category_info_lisp_side,
	    STATIC_FUNCTION(memory_category_info_lisp_side,NIL,FALSE,1,1));
    Qg2_reclaim_symbol = STATIC_SYMBOL("G2-RECLAIM-SYMBOL",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_reclaim_symbol,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_reclaim_symbol,
	    STATIC_FUNCTION(g2_reclaim_symbol,NIL,FALSE,2,2));
}
