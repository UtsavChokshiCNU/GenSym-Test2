/* hshtbl.c
 * Input file:  hash-tables.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "hshtbl.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_user_hash_table_internal_hash_vector_43_vectors, Qavailable_user_hash_table_internal_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_user_hash_table_internal_hash_vector_43_vectors, Qcount_of_user_hash_table_internal_hash_vector_43_vectors);

Object Available_user_hash_table_internal_hash_vector_43_vectors_vector = UNBOUND;

/* USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object user_hash_table_internal_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(145,0);
    temp = Count_of_user_hash_table_internal_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTORS */
Object out_user_hash_table_internal_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(145,1);
    temp = 
	    FIXNUM_MINUS(Count_of_user_hash_table_internal_hash_vector_43_vectors,
	    length(Available_user_hash_table_internal_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_user_hash_table_internal_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(145,2);
    atomic_incff_symval(Qcount_of_user_hash_table_internal_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-USER-HASH-TABLE-INTERNAL-HASH-VECTOR */
Object make_user_hash_table_internal_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(145,3);
    if (ISVREF(Available_user_hash_table_internal_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_user_hash_table_internal_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_user_hash_table_internal_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_user_hash_table_internal_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_user_hash_table_internal_hash_vector_43_vectors_vector,
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
		make_permanent_user_hash_table_internal_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-USER-HASH-TABLE-INTERNAL-HASH-VECTOR */
Object reclaim_user_hash_table_internal_hash_vector(user_hash_table_internal_hash_vector_43_vector)
    Object user_hash_table_internal_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(145,4);
    svref_arg_1 = 
	    Available_user_hash_table_internal_hash_vector_43_vectors_vector;
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
    M_CAR(gensymed_symbol) = user_hash_table_internal_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_user_hash_table_internal_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-USER-HASH-TABLE-INTERNAL-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_user_hash_table_internal_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(145,5);
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

/* MUTATE-USER-HASH-TABLE-INTERNAL-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_user_hash_table_internal_tree_for_hash_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(145,6);
    reclaim_user_hash_table_key(ISVREF(node,(SI_Long)2L));
    reclaim_user_hash_table_entry(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_user_hash_table_internal_tree_for_hash_skip_list_entry = UNBOUND;

static Object Quser_hash_comparitor;  /* user-hash-comparitor */

/* CLEAR-USER-HASH-TABLE-INTERNAL-TREE */
Object clear_user_hash_table_internal_tree(user_hash_table_internal_tree_for_hash_skip_list)
    Object user_hash_table_internal_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_key, old_entry;
    Object result;

    x_note_fn_call(145,7);
    head = M_CAR(M_CDR(user_hash_table_internal_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(user_hash_table_internal_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
	    temp,user_hash_table_internal_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),user_hash_function(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_user_hash_table_key(old_key);
    if (old_entry)
	reclaim_user_hash_table_entry(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(user_hash_table_internal_tree_for_hash_skip_list);
}

static Object Quser_hash_table_internal_tree_for_hash;  /* user-hash-table-internal-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-USER-HASH-TABLE-INTERNAL */
Object make_user_hash_table_internal()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(145,8);
    new_vector = make_user_hash_table_internal_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_user_hash_table_internal_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_user_hash_table_internal_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Quser_hash_table_internal_tree_for_hash;
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

/* FLATTEN-USER-HASH-TABLE-INTERNAL */
Object flatten_user_hash_table_internal(user_hash_table_internal_hash_table)
    Object user_hash_table_internal_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(145,9);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(user_hash_table_internal_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-USER-HASH-TABLE-INTERNAL */
Object clear_user_hash_table_internal(user_hash_table_internal_hash_table)
    Object user_hash_table_internal_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(145,10);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_user_hash_table_internal_tree(ISVREF(user_hash_table_internal_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-USER-HASH-TABLE-INTERNAL */
Object reclaim_user_hash_table_internal(user_hash_table_internal_hash_table)
    Object user_hash_table_internal_hash_table;
{
    Object user_hash_table_internal_tree_for_hash_skip_list, head, tail;
    Object element_qm, key_qm, temp, old_key, old_entry, last_1, next_qm;
    Object temp_1, svref_arg_2;
    SI_Long index_1;
    Object result;

    x_note_fn_call(145,11);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    user_hash_table_internal_tree_for_hash_skip_list = 
	    ISVREF(user_hash_table_internal_hash_table,index_1);
    head = M_CAR(M_CDR(user_hash_table_internal_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(user_hash_table_internal_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
	    temp,user_hash_table_internal_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),user_hash_function(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_user_hash_table_key(old_key);
    if (old_entry)
	reclaim_user_hash_table_entry(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(user_hash_table_internal_tree_for_hash_skip_list) = Nil;
    M_CADR(user_hash_table_internal_tree_for_hash_skip_list) = Nil;
    M_CAR(user_hash_table_internal_tree_for_hash_skip_list) = Nil;
    if (user_hash_table_internal_tree_for_hash_skip_list) {
	last_1 = user_hash_table_internal_tree_for_hash_skip_list;
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
	    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = user_hash_table_internal_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = 
		    user_hash_table_internal_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(user_hash_table_internal_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    reclaim_user_hash_table_internal_hash_vector(user_hash_table_internal_hash_table);
    return VALUES_1(temp);
}

Object Stand_in_marker = UNBOUND;

/* WRAPPED-ITEM-P */
Object wrapped_item_p(thing)
    Object thing;
{
    x_note_fn_call(145,12);
    if (CONSP(thing))
	return VALUES_1(EQ(CAR(thing),Stand_in_marker) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

/* WRAP-OR-COPY-FOR-USER-HASH-TABLE */
Object wrap_or_copy_for_user_hash_table(thing)
    Object thing;
{
    Object x2, gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(145,13);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return slot_value_cons_1(Stand_in_marker,get_reference_to_item(thing));
    else {
	gensymed_symbol = thing;
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
	if (temp) {
	    if (FIXNUMP(thing) || thing && SYMBOLP(thing))
		return VALUES_1(thing);
	    else
		return copy_evaluation_value_1(thing);
	}
	else
	    return VALUES_1(thing);
    }
}

/* UNWRAP-OR-COPY-FOR-USER-HASH-TABLE */
Object unwrap_or_copy_for_user_hash_table(thing)
    Object thing;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(145,14);
    if (wrapped_item_p(thing))
	return VALUES_1(ISVREF(M_CAR(CDR(thing)),(SI_Long)3L));
    else {
	gensymed_symbol = thing;
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
	if (temp) {
	    if (FIXNUMP(thing) || thing && SYMBOLP(thing))
		return VALUES_1(thing);
	    else
		return copy_evaluation_value_1(thing);
	}
	else
	    return VALUES_1(thing);
    }
}

static Object Qitem_reference;     /* item-reference */

/* USER-HASH-FUNCTION */
Object user_hash_function(thing)
    Object thing;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, temp_3, entry_hash;
    SI_Long temp, key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(145,15);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	return hash_wide_string(thing);
    else if (FIXNUMP(thing))
	return VALUES_1(FIXNUM_ABS(thing));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = inline_floor_1(DFLOAT_ISAREF_1(thing,(SI_Long)0L));
	    result = VALUES_1(FIX(ABS(temp)));
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (CONSP(thing) && EQ(M_CDR(thing),Qitem_reference))
	return VALUES_1(FIX(SXHASH_SYMBOL_1(thing) & 
		IFIX(Most_positive_fixnum)));
    else if (wrapped_item_p(thing))
	return VALUES_1(FIX(SXHASH_SYMBOL_1(CDR(thing)) & 
		IFIX(Most_positive_fixnum)));
    else {
	gensymed_symbol = thing;
	temp_1 = FIXNUMP(gensymed_symbol);
	if (temp_1);
	else
	    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ?
		     IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
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
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
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
	if (temp_1)
	    return VALUES_1(FIX((SI_Long)0L));
	else
	    return VALUES_1(FIX((SI_Long)0L));
    }
}

/* USER-HASH-COMPARITOR */
Object user_hash_comparitor(thing1,thing2)
    Object thing1, thing2;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(145,16);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing1) != (SI_Long)0L && 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing2) != (SI_Long)0L)
	return string_eq_w(thing1,thing2);
    else {
	gensymed_symbol = thing1;
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
	if (temp) {
	    gensymed_symbol = thing2;
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
	if (temp)
	    return evaluation_value_eq(thing1,thing2);
	else if (wrapped_item_p(thing1) && wrapped_item_p(thing2))
	    return VALUES_1(EQ(CDR(thing1),CDR(thing2)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
}

/* RECLAIM-USER-HASH-TABLE-KEY */
Object reclaim_user_hash_table_key(key)
    Object key;
{
    x_note_fn_call(145,17);
    if (wrapped_item_p(key)) {
	reclaim_evaluation_value(CDR(key));
	return reclaim_slot_value_cons_1(key);
    }
    else if ( !(FIXNUMP(key) || SYMBOLP(key) || SIMPLE_VECTOR_P(key)))
	return reclaim_if_evaluation_value_1(key);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-USER-HASH-TABLE-ENTRY */
Object reclaim_user_hash_table_entry(key)
    Object key;
{
    x_note_fn_call(145,18);
    if (wrapped_item_p(key)) {
	reclaim_evaluation_value(CDR(key));
	return reclaim_slot_value_cons_1(key);
    }
    else if ( !(FIXNUMP(key) || SYMBOLP(key) || SIMPLE_VECTOR_P(key)))
	return reclaim_if_evaluation_value_1(key);
    else
	return VALUES_1(Nil);
}

/* USER-HASH-TABLE-GETHASH */
Object user_hash_table_gethash(table,key)
    Object table, key;
{
    Object internal_key, temp_1, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_2, entry_hash, result_reference, old_key;
    Object old_entry;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(145,19);
    SAVE_STACK();
    internal_key = wrap_or_copy_for_user_hash_table(key);
    gensymed_symbol = IFIX(user_hash_function(internal_key));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_1 = SVREF(table,FIX(temp));
    skip_list = CDR(temp_1);
    key_value = internal_key;
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
	    key_hash_value &&  !TRUEP(user_hash_comparitor(key_value,
	    ISVREF(curr,(SI_Long)2L)))) {
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
    result_reference = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (user_hash_comparitor(key_value,ISVREF(curr,(SI_Long)2L)) ? 
	    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
    if (result_reference) {
	temp_1 = unwrap_or_copy_for_user_hash_table(result_reference);
	if (temp_1)
	    SAVE_VALUES(VALUES_1(temp_1));
	else {
	    gensymed_symbol = IFIX(user_hash_function(internal_key));
	    temp = gensymed_symbol % (SI_Long)43L;
	    result = delete_skip_list_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
		    internal_key,SVREF(table,FIX(temp)),FIX((SI_Long)31L),
		    FIX(gensymed_symbol));
	    MVS_2(result,old_key,old_entry);
	    if (old_key)
		reclaim_user_hash_table_key(old_key);
	    if (old_entry)
		reclaim_user_hash_table_entry(old_entry);
	    SAVE_VALUES(VALUES_2(Nil,T));
	}
    }
    else
	SAVE_VALUES(VALUES_2(Nil,Nil));
    reclaim_user_hash_table_key(internal_key);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* USER-HASH-TABLE-SETHASH */
Object user_hash_table_sethash(table,key,value)
    Object table, key, value;
{
    Object wrapped_key, wrapped_value, old_value;
    SI_Long gensymed_symbol, temp;

    x_note_fn_call(145,20);
    wrapped_key = wrap_or_copy_for_user_hash_table(key);
    wrapped_value = wrap_or_copy_for_user_hash_table(value);
    old_value = user_hash_table_gethash(table,key);
    gensymed_symbol = IFIX(user_hash_function(wrapped_key));
    temp = gensymed_symbol % (SI_Long)43L;
    set_skip_list_entry(SVREF(table,FIX(temp)),FIX((SI_Long)31L),
	    Quser_hash_comparitor,
	    Fp_mutate_user_hash_table_internal_tree_for_hash_skip_list_entry,
	    T,wrapped_key,FIX(gensymed_symbol),wrapped_value);
    return VALUES_1( !TRUEP(old_value) ? T : Nil);
}

/* DEACTIVATE-FOR-HASH-TABLE */
Object deactivate_for_hash_table(hash_table)
    Object hash_table;
{
    x_note_fn_call(145,21);
    clear_user_hash_table_internal(ISVREF(hash_table,(SI_Long)20L));
    return VALUES_1(ISVREF(hash_table,(SI_Long)21L) = FIX((SI_Long)0L));
}

/* ACTIVATE-FOR-HASH-TABLE */
Object activate_for_hash_table(hash_table)
    Object hash_table;
{
    x_note_fn_call(145,22);
    return initialize_hash_table_from_initial_values_attribute(hash_table);
}

/* INITIALIZE-HASH-TABLE-FROM-INITIAL-VALUES-ATTRIBUTE */
Object initialize_hash_table_from_initial_values_attribute(hash_table)
    Object hash_table;
{
    x_note_fn_call(145,23);
    return VALUES_1(Nil);
}

/* RECLAIM-INTERNAL-HASH-TABLE-VALUE */
Object reclaim_internal_hash_table_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(145,24);
    reclaim_user_hash_table_internal(value);
    ISVREF(frame,(SI_Long)20L) = Nil;
    return VALUES_1(Nil);
}

/* G2-HASH-TABLE-SET-VALUE */
Object g2_hash_table_set_value(table,key,value)
    Object table, key, value;
{
    Object svref_new_value;

    x_note_fn_call(145,25);
    if (user_hash_table_sethash(ISVREF(table,(SI_Long)20L),key,value)) {
	svref_new_value = FIXNUM_ADD1(ISVREF(table,(SI_Long)21L));
	ISVREF(table,(SI_Long)21L) = svref_new_value;
    }
    if ( !(FIXNUMP(key) || SYMBOLP(key) || SIMPLE_VECTOR_P(key)))
	reclaim_if_evaluation_value_1(key);
    if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	return reclaim_if_evaluation_value_1(value);
    else
	return VALUES_1(Nil);
}

/* G2-HASH-TABLE-GET-VALUE */
Object g2_hash_table_get_value(table,key)
    Object table, key;
{
    Object result_1, deleted_item_found, svref_new_value;
    Object result;

    x_note_fn_call(145,26);
    result = user_hash_table_gethash(ISVREF(table,(SI_Long)20L),key);
    MVS_2(result,result_1,deleted_item_found);
    if (deleted_item_found) {
	svref_new_value = FIXNUM_SUB1(ISVREF(table,(SI_Long)21L));
	ISVREF(table,(SI_Long)21L) = svref_new_value;
    }
    if ( !(FIXNUMP(key) || SYMBOLP(key) || SIMPLE_VECTOR_P(key)))
	reclaim_if_evaluation_value_1(key);
    if (result_1)
	return VALUES_2(result_1,T ? Evaluation_true_value : 
		Evaluation_false_value);
    else
	return VALUES_2(Nil ? Evaluation_true_value : 
		Evaluation_false_value,Nil ? Evaluation_true_value : 
		Evaluation_false_value);
}

/* G2-HASH-TABLE-CLEAR-VALUE */
Object g2_hash_table_clear_value(table,key)
    Object table, key;
{
    Object wrapped_key, temp, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, key_exists, old_key, old_entry;
    Object svref_new_value;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(145,27);
    wrapped_key = wrap_or_copy_for_user_hash_table(key);
    gensymed_symbol = IFIX(user_hash_function(wrapped_key));
    temp = ISVREF(table,(SI_Long)20L);
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = wrapped_key;
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
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !TRUEP(user_hash_comparitor(key_value,
	    ISVREF(curr,(SI_Long)2L)))) {
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
    key_exists = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (user_hash_comparitor(key_value,ISVREF(curr,(SI_Long)2L)) ? 
	    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
    gensymed_symbol = IFIX(user_hash_function(wrapped_key));
    temp = ISVREF(table,(SI_Long)20L);
    temp_1 = gensymed_symbol % (SI_Long)43L;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
	    wrapped_key,SVREF(temp,FIX(temp_1)),FIX((SI_Long)31L),
	    FIX(gensymed_symbol));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_user_hash_table_key(old_key);
    if (old_entry)
	reclaim_user_hash_table_entry(old_entry);
    if (key_exists) {
	svref_new_value = FIXNUM_SUB1(ISVREF(table,(SI_Long)21L));
	ISVREF(table,(SI_Long)21L) = svref_new_value;
    }
    reclaim_user_hash_table_key(wrapped_key);
    if ( !(FIXNUMP(key) || SYMBOLP(key) || SIMPLE_VECTOR_P(key)))
	return reclaim_if_evaluation_value_1(key);
    else
	return VALUES_1(Nil);
}

/* G2-HASH-TABLE-CLEAR */
Object g2_hash_table_clear(table)
    Object table;
{
    x_note_fn_call(145,28);
    clear_user_hash_table_internal(ISVREF(table,(SI_Long)20L));
    return VALUES_1(ISVREF(table,(SI_Long)21L) = FIX((SI_Long)0L));
}

/* G2-HASH-TABLE-RESET */
Object g2_hash_table_reset(table)
    Object table;
{
    x_note_fn_call(145,29);
    clear_user_hash_table_internal(ISVREF(table,(SI_Long)20L));
    return initialize_hash_table_from_initial_values_attribute(table);
}

/* INITIAL-G2-HASH-TABLE-NUMBER-OF-ENTRIES */
Object initial_g2_hash_table_number_of_entries(class_1)
    Object class_1;
{
    x_note_fn_call(145,30);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-G2-HASH-TABLE-NUMBER-OF-ENTRIES */
Object get_g2_hash_table_number_of_entries(hash_table)
    Object hash_table;
{
    Object flattened_table, key_or_val, ab_loop_list_;
    SI_Long result_1;

    x_note_fn_call(145,31);
    flattened_table = flatten_user_hash_table(ISVREF(hash_table,(SI_Long)20L));
    result_1 = IFIX(length(flattened_table)) >>  -  - (SI_Long)1L;
    key_or_val = Nil;
    ab_loop_list_ = flattened_table;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    key_or_val = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(FIXNUMP(key_or_val) || SYMBOLP(key_or_val) || 
	    SIMPLE_VECTOR_P(key_or_val)))
	reclaim_if_evaluation_value_1(key_or_val);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(flattened_table);
    return VALUES_1(FIX(result_1));
}

/* INITIAL-G2-HASH-TABLE-SEQUENCE */
Object initial_g2_hash_table_sequence(class_1)
    Object class_1;
{
    x_note_fn_call(145,32);
    return VALUES_1(Nil);
}

/* GET-G2-HASH-TABLE-SEQUENCE */
Object get_g2_hash_table_sequence(hash_table)
    Object hash_table;
{
    Object temp;

    x_note_fn_call(145,33);
    temp = (SI_Long)0L != (IFIX(ISVREF(hash_table,(SI_Long)5L)) & 
	    (SI_Long)1L) ? 
	    flatten_user_hash_table_into_sequence_of_structures(ISVREF(hash_table,
	    (SI_Long)20L)) : Nil;
    return VALUES_1(temp);
}

static Object Qentry_key;          /* entry-key */

static Object Qentry_value;        /* entry-value */

/* SET-G2-HASH-TABLE-SEQUENCE */
Object set_g2_hash_table_sequence(hash_table,new_value)
    Object hash_table, new_value;
{
    Object table, gensymed_symbol, held_vector, element, key, value, elt_1;
    Object validated_elt, svref_new_value;
    SI_Long next_index, length_1;

    x_note_fn_call(145,34);
    table = ISVREF(hash_table,(SI_Long)20L);
    gensymed_symbol = new_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    key = Nil;
    value = Nil;
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
    key = estructure_slot(element,Qentry_key,Nil);
    value = estructure_slot(element,Qentry_value,Nil);
    if (user_hash_table_sethash(table,key,value)) {
	svref_new_value = FIXNUM_ADD1(ISVREF(hash_table,(SI_Long)21L));
	ISVREF(hash_table,(SI_Long)21L) = svref_new_value;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* DELETED-HASH-TABLE-ENTRY-P */
Object deleted_hash_table_entry_p(key_or_value)
    Object key_or_value;
{
    x_note_fn_call(145,35);
    if (wrapped_item_p(key_or_value))
	return VALUES_1( !TRUEP(ISVREF(M_CAR(CDR(key_or_value)),
		(SI_Long)3L)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* FLATTEN-USER-HASH-TABLE */
Object flatten_user_hash_table(table)
    Object table;
{
    Object keys_and_values, key_cons, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, pruned_list;

    x_note_fn_call(145,36);
    keys_and_values = flatten_user_hash_table_internal(table);
    key_cons = keys_and_values;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(key_cons))
	goto end_loop;
    if ( !(deleted_hash_table_entry_p(CAR(key_cons)) || 
	    deleted_hash_table_entry_p(CADR(key_cons)))) {
	ab_loopvar__2 = 
		eval_cons_1(unwrap_or_copy_for_user_hash_table(CAR(key_cons)),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = 
		eval_cons_1(unwrap_or_copy_for_user_hash_table(CADR(key_cons)),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    key_cons = CDDR(key_cons);
    goto next_loop;
  end_loop:
    pruned_list = ab_loopvar_;
    goto end_1;
    pruned_list = Qnil;
  end_1:;
    reclaim_eval_list_1(keys_and_values);
    return VALUES_1(pruned_list);
}

static Object Qab_structure;       /* structure */

/* FLATTEN-USER-HASH-TABLE-INTO-SEQUENCE-OF-STRUCTURES */
Object flatten_user_hash_table_into_sequence_of_structures(table)
    Object table;
{
    Object flattened_table, key_value, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol, temp, item_or_value, x2;
    Object svref_new_value, result_list, key_or_val, ab_loop_list_, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(145,37);
    flattened_table = flatten_user_hash_table(table);
    key_value = flattened_table;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(key_value))
	goto end_loop;
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qentry_key;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qentry_key;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = unwrap_or_copy_for_user_hash_table(FIRST(key_value));
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
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = unwrap_or_copy_for_user_hash_table(FIRST(key_value));
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
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qentry_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qentry_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = unwrap_or_copy_for_user_hash_table(SECOND(key_value));
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
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = unwrap_or_copy_for_user_hash_table(SECOND(key_value));
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
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    ab_loopvar__2 = eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    key_value = CDDR(key_value);
    goto next_loop;
  end_loop:
    result_list = ab_loopvar_;
    goto end_1;
    result_list = Qnil;
  end_1:;
    key_or_val = Nil;
    ab_loop_list_ = flattened_table;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    key_or_val = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(FIXNUMP(key_or_val) || SYMBOLP(key_or_val) || 
	    SIMPLE_VECTOR_P(key_or_val)))
	reclaim_if_evaluation_value_1(key_or_val);
    goto next_loop_1;
  end_loop_1:
    reclaim_eval_list_1(flattened_table);
    temp_2 = allocate_evaluation_sequence(result_list);
    return VALUES_1(temp_2);
}

/* G2-HASH-TABLE-TO-SEQUENCE */
Object g2_hash_table_to_sequence(table)
    Object table;
{
    Object keys_and_values;

    x_note_fn_call(145,38);
    keys_and_values = flatten_user_hash_table(ISVREF(table,(SI_Long)20L));
    return allocate_evaluation_sequence(keys_and_values);
}

/* GET-KEY/VALUE-LIST */
Object get_key_sl_value_list(hash_table)
    Object hash_table;
{
    Object flattened_table, key_cons, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, result_list, key_or_val, ab_loop_list_;

    x_note_fn_call(145,39);
    flattened_table = flatten_user_hash_table(ISVREF(hash_table,(SI_Long)20L));
    key_cons = flattened_table;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(key_cons))
	goto end_loop;
    temp = unwrap_or_copy_for_user_hash_table(CAR(key_cons));
    ab_loopvar__2 = gensym_cons_1(gensym_list_2(temp,
	    unwrap_or_copy_for_user_hash_table(CADR(key_cons))),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    key_cons = CDDR(key_cons);
    goto next_loop;
  end_loop:
    result_list = ab_loopvar_;
    goto end_1;
    result_list = Qnil;
  end_1:;
    key_or_val = Nil;
    ab_loop_list_ = flattened_table;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    key_or_val = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(FIXNUMP(key_or_val) || SYMBOLP(key_or_val) || 
	    SIMPLE_VECTOR_P(key_or_val)))
	reclaim_if_evaluation_value_1(key_or_val);
    goto next_loop_1;
  end_loop_1:
    reclaim_eval_list_1(flattened_table);
    return VALUES_1(result_list);
}

/* WRITE-HASH-TABLE-DATA-FOR-KB */
Object write_hash_table_data_for_kb(table)
    Object table;
{
    Object data_seq, key, val, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(145,40);
    data_seq = get_key_sl_value_list(table);
    if ( !TRUEP(Left_braket_written_qm)) {
	write_char_for_kb(CHR('['));
	Left_braket_written_qm = T;
    }
    write_char_for_kb(CHR('O'));
    write_fixnum_for_kb(ISVREF(table,(SI_Long)21L));
    key = Nil;
    val = Nil;
    ab_loop_list_ = data_seq;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    key = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    val = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    write_element_for_kb(key);
    write_element_for_kb(val);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* READ-HASH-TABLE-DATA */
Object read_hash_table_data(table)
    Object table;
{
    Object len, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(145,41);
    len = read_element_for_kb(Nil);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(len);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    temp = read_element_for_kb(Nil);
    ab_loopvar__2 = gensym_cons_1(gensym_list_2(temp,
	    read_element_for_kb(Nil)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* UNSQUIRREL-HASH-TABLE-DATA */
Object unsquirrel_hash_table_data(table,data)
    Object table, data;
{
    Object key_sl_value_pair, ab_loop_list_;

    x_note_fn_call(145,42);
    key_sl_value_pair = Nil;
    ab_loop_list_ = data;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    key_sl_value_pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_hash_table_set_value(table,FIRST(key_sl_value_pair),
	    SECOND(key_sl_value_pair));
    reclaim_gensym_list_1(key_sl_value_pair);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(data);
}

void hash_tables_INIT()
{
    Object temp, temp_1, temp_2, gensymed_symbol;
    Object Qg2_hash_table_to_sequence;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qset_g2_hash_table_sequence, Qget_g2_hash_table_sequence;
    Object Qinitial_g2_hash_table_sequence, list_constant_2, list_constant_5;
    Object list_constant_1, Qg2_hash_table_sequence, list_constant_4;
    Object list_constant_3, Qab_or, Qno_item;
    Object Qvirtual_attributes_local_to_class;
    Object Qget_g2_hash_table_number_of_entries;
    Object Qinitial_g2_hash_table_number_of_entries;
    Object Qg2_hash_table_number_of_entries, Qexclude_from_wildcard_denotation;
    Object Qab_class, Qg2_hash_table_reset, Qg2_hash_table_clear;
    Object Qg2_hash_table_clear_value, Qg2_hash_table_get_value;
    Object Qg2_hash_table_set_value, Qslot_value_reclaimer;
    Object Qreclaim_internal_hash_table_value, Qinternal_hash_table;
    Object Qclasses_which_define, Qactivate, Qactivate_for_hash_table;
    Object Qdeactivate, Qdeactivate_for_hash_table, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object list_constant, Qmake_user_hash_table_internal;
    Object Qcreate_icon_description, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant_1, Qobject;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Quser_hash_table_stand_in;
    Object Qstand_in_marker;
    Object Qmutate_user_hash_table_internal_tree_for_hash_skip_list_entry;
    Object Qout_user_hash_table_internal_hash_vector_43_vectors;
    Object Quser_hash_table_internal_hash_vector_43_vector_memory_usage;
    Object string_constant, Qutilities2;

    x_note_fn_call(145,43);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_user_hash_table_internal_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_user_hash_table_internal_hash_vector_43_vectors,
	    Available_user_hash_table_internal_hash_vector_43_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_user_hash_table_internal_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_user_hash_table_internal_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_user_hash_table_internal_hash_vector_43_vectors,
	    Count_of_user_hash_table_internal_hash_vector_43_vectors);
    record_system_variable(Qcount_of_user_hash_table_internal_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_user_hash_table_internal_hash_vector_43_vectors_vector 
	    == UNBOUND)
	Available_user_hash_table_internal_hash_vector_43_vectors_vector = 
		make_thread_array(Nil);
    Qout_user_hash_table_internal_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Quser_hash_table_internal_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant = STATIC_STRING("1q83-viy83*9y83-PHy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_user_hash_table_internal_hash_vector_43_vectors);
    push_optimized_constant(Quser_hash_table_internal_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant));
    SET_SYMBOL_FUNCTION(Quser_hash_table_internal_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(user_hash_table_internal_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_user_hash_table_internal_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_user_hash_table_internal_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_user_hash_table_internal_tree_for_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-USER-HASH-TABLE-INTERNAL-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_user_hash_table_internal_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_user_hash_table_internal_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_user_hash_table_internal_tree_for_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_user_hash_table_internal_tree_for_hash_skip_list_entry);
    Quser_hash_comparitor = STATIC_SYMBOL("USER-HASH-COMPARITOR",AB_package);
    Quser_hash_table_internal_tree_for_hash = 
	    STATIC_SYMBOL("USER-HASH-TABLE-INTERNAL-TREE-FOR-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qstand_in_marker = STATIC_SYMBOL("STAND-IN-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstand_in_marker,Stand_in_marker);
    Quser_hash_table_stand_in = STATIC_SYMBOL("USER-HASH-TABLE-STAND-IN",
	    AB_package);
    SET_SYMBOL_VALUE(Qstand_in_marker,
	    gensym_cons_1(Quser_hash_table_stand_in,Nil));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Quser_hash_comparitor,
	    STATIC_FUNCTION(user_hash_comparitor,NIL,FALSE,2,2));
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qhash_table,list_constant);
    string_constant_1 = 
	    STATIC_STRING("1n1m8v8390y1l8t1m83-Cy53-4yhash tables provide a way to associate keys with values with fast lookup");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    Qmake_user_hash_table_internal = 
	    STATIC_SYMBOL("MAKE-USER-HASH-TABLE-INTERNAL",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_user_hash_table_internal,
	    STATIC_FUNCTION(make_user_hash_table_internal,NIL,FALSE,0,0));
    string_constant_2 = 
	    STATIC_STRING("1n4z8r8u8u8390y8390y01v8w9k3ky3ky13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1");
    string_constant_3 = 
	    STATIC_STRING("mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk1o83");
    string_constant_4 = 
	    STATIC_STRING("Oy1mp3fy1m3ey3fy1m3eyp83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3h");
    string_constant_5 = 
	    STATIC_STRING("y1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp3fy83*Uy1o83Gy+s3-4ykkkkkl3A++");
    string_constant_6 = 
	    STATIC_STRING("y1ms3Hy83=Ay83*Uy1o83Gy+s3fykkkkkl3A++y1m3Iy3Sy83=Ay83*Uy1o83Gy+s3-Gykkkkkl3A++y1m3Qy3dy83=Ay000001q1p83*Ny3Ny3My3dy3cy1p83-Lykk");
    string_constant_7 = 
	    STATIC_STRING("3ky3ky1p83-nykk3ky3ky1p83-mykk3ky3ky1p83*Nykk3ky3ky1p83*Uysq3Gy3My001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definiti");
    string_constant_8 = 
	    STATIC_STRING("on000004z8r83STy83STy8390y8390y01m83*Ay9l001o1l8o1l8l1l83Fy1l83Hy000004z8r83J*y83J*y8390y8390y0k001m1l8o1l8l00000");
    string_constant_9 = 
	    STATIC_STRING("1p8q1p8390y1l83-Oy1m8v8390y8t1m83-Cy53-4yhash tables provide a way to associate keys with values with fast lookup1m8u1v8w9k3ky3k");
    string_constant_10 = 
	    STATIC_STRING("y13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3k");
    string_constant_11 = 
	    STATIC_STRING("yk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk1o83Oy1mp3fy1m3ey3fy1m3eyp83-my1q83q");
    string_constant_12 = 
	    STATIC_STRING("y1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1");
    string_constant_13 = 
	    STATIC_STRING("m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp3fy83*Uy1o83Gy+s3-4ykkkkkl3A++y1ms3Hy83=Ay83*Uy1o83Gy+s3fykkkk");
    string_constant_14 = 
	    STATIC_STRING("kl3A++y1m3Iy3Sy83=Ay83*Uy1o83Gy+s3-Gykkkkkl3A++y1m3Qy3dy83=Ay000001q1p83*Ny3Ny3My3dy3cy1p83-Lykk3ky3ky1p83-nykk3ky3ky1p83-mykk3k");
    string_constant_15 = 
	    STATIC_STRING("y3ky1p83*Nykk3ky3ky1p83*Uysq3Gy3My1q83STy1m83*Ay9l8o8l83Fy83Hy1o83J*yk8o8l");
    temp = regenerate_optimized_constant(string_constant_1);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qmake_user_hash_table_internal);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_2,
	    string_constant_3,string_constant_4,string_constant_5,
	    string_constant_6,string_constant_7,string_constant_8));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qmake_user_hash_table_internal);
    add_class_to_environment(9,Qhash_table,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,regenerate_optimized_constant(list(7,
	    string_constant_9,string_constant_10,string_constant_11,
	    string_constant_12,string_constant_13,string_constant_14,
	    string_constant_15)),Nil);
    Qdeactivate_for_hash_table = STATIC_SYMBOL("DEACTIVATE-FOR-HASH-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_hash_table,
	    STATIC_FUNCTION(deactivate_for_hash_table,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_hash_table);
    set_get(Qhash_table,Qdeactivate,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qhash_table,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qactivate_for_hash_table = STATIC_SYMBOL("ACTIVATE-FOR-HASH-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_hash_table,
	    STATIC_FUNCTION(activate_for_hash_table,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_hash_table);
    set_get(Qhash_table,Qactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qhash_table,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    Qinternal_hash_table = STATIC_SYMBOL("INTERNAL-HASH-TABLE",AB_package);
    Qreclaim_internal_hash_table_value = 
	    STATIC_SYMBOL("RECLAIM-INTERNAL-HASH-TABLE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_internal_hash_table_value,
	    STATIC_FUNCTION(reclaim_internal_hash_table_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qinternal_hash_table,
	    SYMBOL_FUNCTION(Qreclaim_internal_hash_table_value),
	    Qslot_value_reclaimer);
    Qg2_hash_table_set_value = STATIC_SYMBOL("G2-HASH-TABLE-SET-VALUE",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_hash_table_set_value,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_hash_table_set_value,
	    STATIC_FUNCTION(g2_hash_table_set_value,NIL,FALSE,3,3));
    Qg2_hash_table_get_value = STATIC_SYMBOL("G2-HASH-TABLE-GET-VALUE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_hash_table_get_value,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_hash_table_get_value,
	    STATIC_FUNCTION(g2_hash_table_get_value,NIL,FALSE,2,2));
    Qg2_hash_table_clear_value = STATIC_SYMBOL("G2-HASH-TABLE-CLEAR-VALUE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_hash_table_clear_value,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_hash_table_clear_value,
	    STATIC_FUNCTION(g2_hash_table_clear_value,NIL,FALSE,2,2));
    Qg2_hash_table_clear = STATIC_SYMBOL("G2-HASH-TABLE-CLEAR",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_hash_table_clear,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_hash_table_clear,
	    STATIC_FUNCTION(g2_hash_table_clear,NIL,FALSE,1,1));
    Qg2_hash_table_reset = STATIC_SYMBOL("G2-HASH-TABLE-RESET",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_hash_table_reset,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_hash_table_reset,
	    STATIC_FUNCTION(g2_hash_table_reset,NIL,FALSE,1,1));
    Qg2_hash_table_number_of_entries = 
	    STATIC_SYMBOL("G2-HASH-TABLE-NUMBER-OF-ENTRIES",AB_package);
    temp_2 = CONS(Qg2_hash_table_number_of_entries,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qhash_table),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qg2_hash_table_number_of_entries,temp);
    set_property_value_function(get_symbol_properties_function(Qhash_table),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qab_class,Qhash_table);
    Qexclude_from_wildcard_denotation = 
	    STATIC_SYMBOL("EXCLUDE-FROM-WILDCARD-DENOTATION",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qexclude_from_wildcard_denotation,Qt);
    Qinitial_g2_hash_table_number_of_entries = 
	    STATIC_SYMBOL("INITIAL-G2-HASH-TABLE-NUMBER-OF-ENTRIES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_hash_table_number_of_entries,
	    STATIC_FUNCTION(initial_g2_hash_table_number_of_entries,NIL,
	    FALSE,1,1));
    Qget_g2_hash_table_number_of_entries = 
	    STATIC_SYMBOL("GET-G2-HASH-TABLE-NUMBER-OF-ENTRIES",AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_hash_table_number_of_entries,
	    STATIC_FUNCTION(get_g2_hash_table_number_of_entries,NIL,FALSE,
	    1,1));
    add_virtual_attribute(Qg2_hash_table_number_of_entries,list_constant_1,
	    Qinteger,list_constant_2,
	    SYMBOL_FUNCTION(Qinitial_g2_hash_table_number_of_entries),
	    SYMBOL_FUNCTION(Qget_g2_hash_table_number_of_entries),Nil);
    Qg2_hash_table_sequence = STATIC_SYMBOL("G2-HASH-TABLE-SEQUENCE",
	    AB_package);
    temp_2 = CONS(Qg2_hash_table_sequence,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qhash_table),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qg2_hash_table_sequence,temp);
    set_property_value_function(get_symbol_properties_function(Qhash_table),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qentry_key = STATIC_SYMBOL("ENTRY-KEY",AB_package);
    Qentry_value = STATIC_SYMBOL("ENTRY-VALUE",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_3 = STATIC_CONS(Qno_item,Qnil);
    list_constant_4 = STATIC_CONS(Qsequence,Qnil);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_3,
	    list_constant_4);
    Qinitial_g2_hash_table_sequence = 
	    STATIC_SYMBOL("INITIAL-G2-HASH-TABLE-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_hash_table_sequence,
	    STATIC_FUNCTION(initial_g2_hash_table_sequence,NIL,FALSE,1,1));
    Qget_g2_hash_table_sequence = 
	    STATIC_SYMBOL("GET-G2-HASH-TABLE-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_hash_table_sequence,
	    STATIC_FUNCTION(get_g2_hash_table_sequence,NIL,FALSE,1,1));
    Qset_g2_hash_table_sequence = 
	    STATIC_SYMBOL("SET-G2-HASH-TABLE-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_g2_hash_table_sequence,
	    STATIC_FUNCTION(set_g2_hash_table_sequence,NIL,FALSE,2,2));
    add_virtual_attribute(Qg2_hash_table_sequence,list_constant_1,
	    list_constant_5,list_constant_2,
	    SYMBOL_FUNCTION(Qinitial_g2_hash_table_sequence),
	    SYMBOL_FUNCTION(Qget_g2_hash_table_sequence),
	    SYMBOL_FUNCTION(Qset_g2_hash_table_sequence));
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qg2_hash_table_to_sequence = STATIC_SYMBOL("G2-HASH-TABLE-TO-SEQUENCE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_hash_table_to_sequence,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_hash_table_to_sequence,
	    STATIC_FUNCTION(g2_hash_table_to_sequence,NIL,FALSE,1,1));
}
