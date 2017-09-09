/* hshtbl.c
 * Input file:  hash-tables.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "hshtbl.h"


Object Available_user_hash_table_internal_hash_vector_43_vectors = UNBOUND;

Object Count_of_user_hash_table_internal_hash_vector_43_vectors = UNBOUND;

/* USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object user_hash_table_internal_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(146,0);
    temp = Count_of_user_hash_table_internal_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTORS */
Object out_user_hash_table_internal_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(146,1);
    temp = 
	    FIXNUM_MINUS(Count_of_user_hash_table_internal_hash_vector_43_vectors,
	    length(Available_user_hash_table_internal_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_user_hash_table_internal_hash_vector_43_vector_internal()
{
    Object count_of_user_hash_table_internal_hash_vector_43_vectors_new_value;
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(146,2);
    count_of_user_hash_table_internal_hash_vector_43_vectors_new_value = 
	    FIXNUM_ADD1(Count_of_user_hash_table_internal_hash_vector_43_vectors);
    Count_of_user_hash_table_internal_hash_vector_43_vectors = 
	    count_of_user_hash_table_internal_hash_vector_43_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qab_gensym;          /* gensym */

/* MAKE-USER-HASH-TABLE-INTERNAL-HASH-VECTOR */
Object make_user_hash_table_internal_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(146,3);
    if (Available_user_hash_table_internal_hash_vector_43_vectors) {
	temp = 
		M_CAR(Available_user_hash_table_internal_hash_vector_43_vectors);
	temp_1 = 
		M_CDR(Available_user_hash_table_internal_hash_vector_43_vectors);
	inline_note_reclaim_cons(Available_user_hash_table_internal_hash_vector_43_vectors,
		Qab_gensym);
	cdr_arg = Available_user_hash_table_internal_hash_vector_43_vectors;
	cdr_new_value = Available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	Available_gensym_conses = 
		Available_user_hash_table_internal_hash_vector_43_vectors;
	Available_user_hash_table_internal_hash_vector_43_vectors = temp_1;
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
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(146,4);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = user_hash_table_internal_hash_vector_43_vector;
    cdr_new_value = Available_user_hash_table_internal_hash_vector_43_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    Available_user_hash_table_internal_hash_vector_43_vectors = 
	    gensymed_symbol;
    return VALUES_1(Nil);
}

/* MUTATE-USER-HASH-TABLE-INTERNAL-TREE-FOR-HASH-TREE-ENTRY */
Object mutate_user_hash_table_internal_tree_for_hash_tree_entry(entry_cons,
	    new_key,new_entry)
    Object entry_cons, new_key, new_entry;
{
    x_note_fn_call(146,5);
    reclaim_user_hash_table_key(M_CAR(entry_cons));
    reclaim_user_hash_table_entry(M_CDR(entry_cons));
    M_CAR(entry_cons) = new_key;
    M_CDR(entry_cons) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_user_hash_table_internal_tree_for_hash_tree_entry = UNBOUND;

static Object Quser_hash_comparitor;  /* user-hash-comparitor */

/* CLEAR-USER-HASH-TABLE-INTERNAL-TREE */
Object clear_user_hash_table_internal_tree(user_hash_table_internal_tree_for_hash_binary_tree)
    Object user_hash_table_internal_tree_for_hash_binary_tree;
{
    Object element_qm, temp, gensymed_symbol, old_key, old_entry;
    Object result;

    x_note_fn_call(146,6);
    element_qm = Nil;
  next_loop:
    element_qm = CDR(user_hash_table_internal_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop;
    temp = ISVREF(element_qm,(SI_Long)3L);
    gensymed_symbol = CAAR(temp);
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
	    gensymed_symbol,
	    user_hash_table_internal_tree_for_hash_binary_tree,
	    user_hash_function(gensymed_symbol));
    MVS_2(result,old_key,old_entry);
    reclaim_user_hash_table_key(old_key);
    reclaim_user_hash_table_entry(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(user_hash_table_internal_tree_for_hash_binary_tree);
}

static Object Quser_hash_table_internal_tree_for_hash;  /* user-hash-table-internal-tree-for-hash */

/* MAKE-USER-HASH-TABLE-INTERNAL */
Object make_user_hash_table_internal()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(146,7);
    new_vector = make_user_hash_table_internal_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Quser_hash_table_internal_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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

    x_note_fn_call(146,8);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(user_hash_table_internal_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
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

    x_note_fn_call(146,9);
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
    Object user_hash_table_internal_tree_for_hash_binary_tree, element_qm;
    Object gensymed_symbol, old_key, old_entry, cdr_new_value, temp;
    SI_Long index_1;
    Object result;

    x_note_fn_call(146,10);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    user_hash_table_internal_tree_for_hash_binary_tree = 
	    ISVREF(user_hash_table_internal_hash_table,index_1);
    element_qm = Nil;
  next_loop_1:
    element_qm = M_CDR(user_hash_table_internal_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop_1;
    gensymed_symbol = M_CAR(M_CAR(ISVREF(element_qm,(SI_Long)3L)));
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
	    gensymed_symbol,
	    user_hash_table_internal_tree_for_hash_binary_tree,
	    user_hash_function(gensymed_symbol));
    MVS_2(result,old_key,old_entry);
    reclaim_user_hash_table_key(old_key);
    reclaim_user_hash_table_entry(old_entry);
    goto next_loop_1;
  end_loop_1:
    inline_note_reclaim_cons(user_hash_table_internal_tree_for_hash_binary_tree,
	    Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(user_hash_table_internal_tree_for_hash_binary_tree) = cdr_new_value;
    Available_gensym_conses = 
	    user_hash_table_internal_tree_for_hash_binary_tree;
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
    x_note_fn_call(146,11);
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
    Object x2, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(146,12);
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
	return gensym_cons_1(Stand_in_marker,get_reference_to_item(thing));
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
		gensymed_symbol_1 = CDR(Defined_evaluation_value_types);
		gensymed_symbol_2 = SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop:
		if ( !TRUEP(gensymed_symbol_1))
		    goto end_loop;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		else {
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_1:
		    if ( !TRUEP(gensymed_symbol_1))
			goto end_loop_1;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
		    if (EQ(gensymed_symbol,gensymed_symbol_4)) {
			temp = TRUEP(M_CDR(M_CAR(gensymed_symbol_1)));
			goto end_1;
		    }
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    goto next_loop_1;
		  end_loop_1:
		    temp = TRUEP(Qnil);
		  end_1:;
		    goto end_2;
		}
		goto next_loop;
	      end_loop:
		temp = TRUEP(Qnil);
	      end_2:;
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(146,13);
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
		gensymed_symbol_1 = CDR(Defined_evaluation_value_types);
		gensymed_symbol_2 = SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop:
		if ( !TRUEP(gensymed_symbol_1))
		    goto end_loop;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		else {
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_1:
		    if ( !TRUEP(gensymed_symbol_1))
			goto end_loop_1;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
		    if (EQ(gensymed_symbol,gensymed_symbol_4)) {
			temp = TRUEP(M_CDR(M_CAR(gensymed_symbol_1)));
			goto end_1;
		    }
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    goto next_loop_1;
		  end_loop_1:
		    temp = TRUEP(Qnil);
		  end_1:;
		    goto end_2;
		}
		goto next_loop;
	      end_loop:
		temp = TRUEP(Qnil);
	      end_2:;
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4;
    SI_Long temp, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(146,14);
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
		gensymed_symbol_1 = CDR(Defined_evaluation_value_types);
		gensymed_symbol_2 = SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop:
		if ( !TRUEP(gensymed_symbol_1))
		    goto end_loop;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		else {
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_1:
		    if ( !TRUEP(gensymed_symbol_1))
			goto end_loop_1;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
		    if (EQ(gensymed_symbol,gensymed_symbol_4)) {
			temp_1 = TRUEP(M_CDR(M_CAR(gensymed_symbol_1)));
			goto end_1;
		    }
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    goto next_loop_1;
		  end_loop_1:
		    temp_1 = TRUEP(Qnil);
		  end_1:;
		    goto end_2;
		}
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(Qnil);
	      end_2:;
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(146,15);
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
		gensymed_symbol_1 = CDR(Defined_evaluation_value_types);
		gensymed_symbol_2 = SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop:
		if ( !TRUEP(gensymed_symbol_1))
		    goto end_loop;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		else {
		    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_1:
		    if ( !TRUEP(gensymed_symbol_1))
			goto end_loop_1;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
		    if (EQ(gensymed_symbol,gensymed_symbol_4)) {
			temp = TRUEP(M_CDR(M_CAR(gensymed_symbol_1)));
			goto end_1;
		    }
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    goto next_loop_1;
		  end_loop_1:
		    temp = TRUEP(Qnil);
		  end_1:;
		    goto end_2;
		}
		goto next_loop;
	      end_loop:
		temp = TRUEP(Qnil);
	      end_2:;
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
		    gensymed_symbol_1 = CDR(Defined_evaluation_value_types);
		    gensymed_symbol_2 = SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_3 = (SI_Long)0L;
		  next_loop_2:
		    if ( !TRUEP(gensymed_symbol_1))
			goto end_loop_2;
		    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,
			    (SI_Long)0L));
		    if (gensymed_symbol_2 < gensymed_symbol_3)
			gensymed_symbol_1 = ISVREF(gensymed_symbol_1,
				(SI_Long)1L);
		    else if (gensymed_symbol_2 > gensymed_symbol_3)
			gensymed_symbol_1 = ISVREF(gensymed_symbol_1,
				(SI_Long)2L);
		    else {
			gensymed_symbol_1 = ISVREF(gensymed_symbol_1,
				(SI_Long)3L);
			gensymed_symbol_4 = Nil;
		      next_loop_3:
			if ( !TRUEP(gensymed_symbol_1))
			    goto end_loop_3;
			gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
			if (EQ(gensymed_symbol,gensymed_symbol_4)) {
			    temp = TRUEP(M_CDR(M_CAR(gensymed_symbol_1)));
			    goto end_3;
			}
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			goto next_loop_3;
		      end_loop_3:
			temp = TRUEP(Qnil);
		      end_3:;
			goto end_4;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp = TRUEP(Qnil);
		  end_4:;
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
    x_note_fn_call(146,16);
    if (wrapped_item_p(key)) {
	reclaim_evaluation_value(CDR(key));
	return reclaim_gensym_cons_1(key);
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
    x_note_fn_call(146,17);
    if (wrapped_item_p(key)) {
	reclaim_evaluation_value(CDR(key));
	return reclaim_gensym_cons_1(key);
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
    Object internal_key, temp_1, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_4, result_reference, old_key, old_entry;
    SI_Long gensymed_symbol, temp, gensymed_symbol_3;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(146,18);
    SAVE_STACK();
    internal_key = wrap_or_copy_for_user_hash_table(key);
    gensymed_symbol = IFIX(user_hash_function(internal_key));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_1 = SVREF(table,FIX(temp));
    gensymed_symbol_1 = CDR(temp_1);
    gensymed_symbol_2 = internal_key;
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_1))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
    if (gensymed_symbol < gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    else if (gensymed_symbol > gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	if (user_hash_comparitor(gensymed_symbol_2,gensymed_symbol_4)) {
	    result_reference = M_CDR(M_CAR(gensymed_symbol_1));
	    goto end_1;
	}
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	result_reference = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    result_reference = Qnil;
  end_2:;
    if (result_reference) {
	temp_1 = unwrap_or_copy_for_user_hash_table(result_reference);
	if (temp_1)
	    SAVE_VALUES(VALUES_1(temp_1));
	else {
	    gensymed_symbol = IFIX(user_hash_function(internal_key));
	    temp = gensymed_symbol % (SI_Long)43L;
	    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
		    internal_key,SVREF(table,FIX(temp)),FIX(gensymed_symbol));
	    MVS_2(result,old_key,old_entry);
	    reclaim_user_hash_table_key(old_key);
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

    x_note_fn_call(146,19);
    wrapped_key = wrap_or_copy_for_user_hash_table(key);
    wrapped_value = wrap_or_copy_for_user_hash_table(value);
    old_value = user_hash_table_gethash(table,key);
    gensymed_symbol = IFIX(user_hash_function(wrapped_key));
    temp = gensymed_symbol % (SI_Long)43L;
    set_balanced_binary_tree_entry(SVREF(table,FIX(temp)),
	    Quser_hash_comparitor,
	    Fp_mutate_user_hash_table_internal_tree_for_hash_tree_entry,T,
	    wrapped_key,FIX(gensymed_symbol),wrapped_value);
    return VALUES_1( !TRUEP(old_value) ? T : Nil);
}

/* DEACTIVATE-FOR-HASH-TABLE */
Object deactivate_for_hash_table(hash_table)
    Object hash_table;
{
    x_note_fn_call(146,20);
    clear_user_hash_table_internal(ISVREF(hash_table,(SI_Long)20L));
    return VALUES_1(ISVREF(hash_table,(SI_Long)21L) = FIX((SI_Long)0L));
}

/* ACTIVATE-FOR-HASH-TABLE */
Object activate_for_hash_table(hash_table)
    Object hash_table;
{
    x_note_fn_call(146,21);
    return initialize_hash_table_from_initial_values_attribute(hash_table);
}

/* INITIALIZE-HASH-TABLE-FROM-INITIAL-VALUES-ATTRIBUTE */
Object initialize_hash_table_from_initial_values_attribute(hash_table)
    Object hash_table;
{
    x_note_fn_call(146,22);
    return VALUES_1(Nil);
}

/* RECLAIM-INTERNAL-HASH-TABLE-VALUE */
Object reclaim_internal_hash_table_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(146,23);
    reclaim_user_hash_table_internal(value);
    ISVREF(frame,(SI_Long)20L) = Nil;
    return VALUES_1(Nil);
}

/* G2-HASH-TABLE-SET-VALUE */
Object g2_hash_table_set_value(table,key,value)
    Object table, key, value;
{
    Object svref_new_value;

    x_note_fn_call(146,24);
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

    x_note_fn_call(146,25);
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
    Object wrapped_key, temp, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_4, key_exists, old_key, old_entry, svref_new_value;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;
    Object result;

    x_note_fn_call(146,26);
    wrapped_key = wrap_or_copy_for_user_hash_table(key);
    gensymed_symbol = IFIX(user_hash_function(wrapped_key));
    temp = ISVREF(table,(SI_Long)20L);
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = CDR(temp);
    gensymed_symbol_2 = wrapped_key;
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_1))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
    if (gensymed_symbol < gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    else if (gensymed_symbol > gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	if (user_hash_comparitor(gensymed_symbol_2,gensymed_symbol_4)) {
	    key_exists = M_CDR(M_CAR(gensymed_symbol_1));
	    goto end_1;
	}
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	key_exists = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    key_exists = Qnil;
  end_2:;
    gensymed_symbol = IFIX(user_hash_function(wrapped_key));
    temp = ISVREF(table,(SI_Long)20L);
    temp_1 = gensymed_symbol % (SI_Long)43L;
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Quser_hash_comparitor),
	    wrapped_key,SVREF(temp,FIX(temp_1)),FIX(gensymed_symbol));
    MVS_2(result,old_key,old_entry);
    reclaim_user_hash_table_key(old_key);
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
    x_note_fn_call(146,27);
    clear_user_hash_table_internal(ISVREF(table,(SI_Long)20L));
    return VALUES_1(ISVREF(table,(SI_Long)21L) = FIX((SI_Long)0L));
}

/* G2-HASH-TABLE-RESET */
Object g2_hash_table_reset(table)
    Object table;
{
    x_note_fn_call(146,28);
    clear_user_hash_table_internal(ISVREF(table,(SI_Long)20L));
    return initialize_hash_table_from_initial_values_attribute(table);
}

/* INITIAL-G2-HASH-TABLE-NUMBER-OF-ENTRIES */
Object initial_g2_hash_table_number_of_entries(class_1)
    Object class_1;
{
    x_note_fn_call(146,29);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-G2-HASH-TABLE-NUMBER-OF-ENTRIES */
Object get_g2_hash_table_number_of_entries(hash_table)
    Object hash_table;
{
    Object flattened_table, key_or_val, ab_loop_list_;
    SI_Long result_1;

    x_note_fn_call(146,30);
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
    reclaim_gensym_list_1(flattened_table);
    return VALUES_1(FIX(result_1));
}

/* INITIAL-G2-HASH-TABLE-SEQUENCE */
Object initial_g2_hash_table_sequence(class_1)
    Object class_1;
{
    x_note_fn_call(146,31);
    return VALUES_1(Nil);
}

/* GET-G2-HASH-TABLE-SEQUENCE */
Object get_g2_hash_table_sequence(hash_table)
    Object hash_table;
{
    Object temp;

    x_note_fn_call(146,32);
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

    x_note_fn_call(146,33);
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
    x_note_fn_call(146,34);
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

    x_note_fn_call(146,35);
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
		gensym_cons_1(unwrap_or_copy_for_user_hash_table(CAR(key_cons)),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = 
		gensym_cons_1(unwrap_or_copy_for_user_hash_table(CADR(key_cons)),
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
    reclaim_gensym_list_1(keys_and_values);
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

    x_note_fn_call(146,36);
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
    ab_loopvar__2 = gensym_cons_1(gensym_cons_1(gensymed_symbol,
	    Qab_structure),Nil);
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
    reclaim_gensym_list_1(flattened_table);
    temp_2 = allocate_evaluation_sequence(result_list);
    return VALUES_1(temp_2);
}

/* G2-HASH-TABLE-TO-SEQUENCE */
Object g2_hash_table_to_sequence(table)
    Object table;
{
    Object keys_and_values;

    x_note_fn_call(146,37);
    keys_and_values = flatten_user_hash_table(ISVREF(table,(SI_Long)20L));
    return allocate_evaluation_sequence(keys_and_values);
}

/* GET-KEY/VALUE-LIST */
Object get_key_sl_value_list(hash_table)
    Object hash_table;
{
    Object flattened_table, key_cons, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, result_list, key_or_val, ab_loop_list_;

    x_note_fn_call(146,38);
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
    reclaim_gensym_list_1(flattened_table);
    return VALUES_1(result_list);
}

/* WRITE-HASH-TABLE-DATA-FOR-KB */
Object write_hash_table_data_for_kb(table)
    Object table;
{
    Object data_seq, key, val, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(146,39);
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

    x_note_fn_call(146,40);
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

    x_note_fn_call(146,41);
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
    Object Qmutate_user_hash_table_internal_tree_for_hash_tree_entry;
    Object Qout_user_hash_table_internal_hash_vector_43_vectors;
    Object Quser_hash_table_internal_hash_vector_43_vector_memory_usage;
    Object string_constant, Qutilities2;
    Object Qcount_of_user_hash_table_internal_hash_vector_43_vectors;
    Object Qavailable_user_hash_table_internal_hash_vector_43_vectors;

    x_note_fn_call(146,42);
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
    Qout_user_hash_table_internal_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Quser_hash_table_internal_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("USER-HASH-TABLE-INTERNAL-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant = STATIC_STRING("1q83-u=y83*By83-PBy09k9l");
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
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qmutate_user_hash_table_internal_tree_for_hash_tree_entry = 
	    STATIC_SYMBOL("MUTATE-USER-HASH-TABLE-INTERNAL-TREE-FOR-HASH-TREE-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_user_hash_table_internal_tree_for_hash_tree_entry,
	    STATIC_FUNCTION(mutate_user_hash_table_internal_tree_for_hash_tree_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_user_hash_table_internal_tree_for_hash_tree_entry = 
	    SYMBOL_FUNCTION(Qmutate_user_hash_table_internal_tree_for_hash_tree_entry);
    Quser_hash_comparitor = STATIC_SYMBOL("USER-HASH-COMPARITOR",AB_package);
    Quser_hash_table_internal_tree_for_hash = 
	    STATIC_SYMBOL("USER-HASH-TABLE-INTERNAL-TREE-FOR-HASH",AB_package);
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
	    STATIC_STRING("1n4z8r8u8u8390y8390y01v8w9k3ky3ky13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Xy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1");
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
	    STATIC_STRING("on000004z8r83SWy83SWy8390y8390y01m83*9y9l001o1l8o1l8l1l83Fy1l83Hy000004z8r83J*y83J*y8390y8390y0k001m1l8o1l8l00000");
    string_constant_9 = 
	    STATIC_STRING("1p8q1p8390y1l83-Oy1m8v8390y8t1m83-Cy53-4yhash tables provide a way to associate keys with values with fast lookup1m8u1v8w9k3ky3k");
    string_constant_10 = 
	    STATIC_STRING("y13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Xy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3k");
    string_constant_11 = 
	    STATIC_STRING("yk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk1o83Oy1mp3fy1m3ey3fy1m3eyp83-my1q83q");
    string_constant_12 = 
	    STATIC_STRING("y1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1");
    string_constant_13 = 
	    STATIC_STRING("m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp3fy83*Uy1o83Gy+s3-4ykkkkkl3A++y1ms3Hy83=Ay83*Uy1o83Gy+s3fykkkk");
    string_constant_14 = 
	    STATIC_STRING("kl3A++y1m3Iy3Sy83=Ay83*Uy1o83Gy+s3-Gykkkkkl3A++y1m3Qy3dy83=Ay000001q1p83*Ny3Ny3My3dy3cy1p83-Lykk3ky3ky1p83-nykk3ky3ky1p83-mykk3k");
    string_constant_15 = 
	    STATIC_STRING("y3ky1p83*Nykk3ky3ky1p83*Uysq3Gy3My1q83SWy1m83*9y9l8o8l83Fy83Hy1o83J*yk8o8l");
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
