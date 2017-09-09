/* gsrpc2.c
 * Input file:  gsi-rpc2.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gsrpc2.h"


Object G2int_gsi_maximum_number_of_icp_bytes_to_buffer = UNBOUND;

Object G2int_gsi_collection_range_limit = UNBOUND;

Object G2int_gsi_current_resumable_item = UNBOUND;

Object G2int_list_of_gsi_circular_references = UNBOUND;

Object G2int_gsi_current_recursive_depth = UNBOUND;

Object G2int_gsi_depth_of_last_transmission = UNBOUND;

Object G2int_available_gsi_circularity_table_hash_vector_43_vectors = UNBOUND;

Object G2int_count_of_gsi_circularity_table_hash_vector_43_vectors = UNBOUND;

/* GSI-CIRCULARITY-TABLE-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object g2int_gsi_circularity_table_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(51,0);
    temp = G2int_count_of_gsi_circularity_table_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,g2int_bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-GSI-CIRCULARITY-TABLE-HASH-VECTOR-43-VECTORS */
Object g2int_out_gsi_circularity_table_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(51,1);
    temp = 
	    FIXNUM_MINUS(G2int_count_of_gsi_circularity_table_hash_vector_43_vectors,
	    length(G2int_available_gsi_circularity_table_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-GSI-CIRCULARITY-TABLE-HASH-VECTOR-43-VECTOR-INTERNAL */
Object g2int_make_permanent_gsi_circularity_table_hash_vector_43_vector_internal()
{
    Object count_of_gsi_circularity_table_hash_vector_43_vectors_new_value;
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(51,2);
    count_of_gsi_circularity_table_hash_vector_43_vectors_new_value = 
	    FIXNUM_ADD1(G2int_count_of_gsi_circularity_table_hash_vector_43_vectors);
    G2int_count_of_gsi_circularity_table_hash_vector_43_vectors = 
	    count_of_gsi_circularity_table_hash_vector_43_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qg2int_gensym;       /* gensym */

/* MAKE-GSI-CIRCULARITY-TABLE-HASH-VECTOR */
Object g2int_make_gsi_circularity_table_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(51,3);
    if (G2int_available_gsi_circularity_table_hash_vector_43_vectors) {
	temp = 
		M_CAR(G2int_available_gsi_circularity_table_hash_vector_43_vectors);
	temp_1 = 
		M_CDR(G2int_available_gsi_circularity_table_hash_vector_43_vectors);
	inline_note_reclaim_cons(G2int_available_gsi_circularity_table_hash_vector_43_vectors,
		Qg2int_gensym);
	cdr_arg = G2int_available_gsi_circularity_table_hash_vector_43_vectors;
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	G2int_available_gensym_conses = 
		G2int_available_gsi_circularity_table_hash_vector_43_vectors;
	G2int_available_gsi_circularity_table_hash_vector_43_vectors = temp_1;
    }
    else
	temp = 
		g2int_make_permanent_gsi_circularity_table_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-GSI-CIRCULARITY-TABLE-HASH-VECTOR */
Object g2int_reclaim_gsi_circularity_table_hash_vector(gsi_circularity_table_hash_vector_43_vector)
    Object gsi_circularity_table_hash_vector_43_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(51,4);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = gsi_circularity_table_hash_vector_43_vector;
    cdr_new_value = 
	    G2int_available_gsi_circularity_table_hash_vector_43_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    G2int_available_gsi_circularity_table_hash_vector_43_vectors = 
	    gensymed_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-GSI-CIRCULARITY-TABLE-TREE-FOR-HASH-LEAVES */
Object g2int_reclaim_gsi_circularity_table_tree_for_hash_leaves(gsi_circularity_table_tree_for_hash_binary_tree)
    Object gsi_circularity_table_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, cdr_new_value, last_1, next_qm, temp;

    x_note_fn_call(51,5);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(gsi_circularity_table_tree_for_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = 
	    ISVREF(gsi_circularity_table_tree_for_hash_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(gsi_circularity_table_tree_for_hash_binary_tree,
	    (SI_Long)2L);
    alist = ISVREF(gsi_circularity_table_tree_for_hash_binary_tree,
	    (SI_Long)3L);
    g2int_reclaim_binary_tree_element_1(gsi_circularity_table_tree_for_hash_binary_tree);
    alist_entry = Nil;
    ab_loop_list_ = alist;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    inline_note_reclaim_cons(alist_entry,Qg2int_gensym);
    cdr_new_value = G2int_available_gensym_conses;
    M_CDR(alist_entry) = cdr_new_value;
    G2int_available_gensym_conses = alist_entry;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	G2int_available_gensym_conses = alist;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	g2int_reclaim_gsi_circularity_table_tree_for_hash_leaves(less_than_branch_qm);
	gsi_circularity_table_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp = less_than_branch_qm;
	if (temp);
	else
	    temp = greater_than_branch_qm;
	gsi_circularity_table_tree_for_hash_binary_tree = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-GSI-CIRCULARITY-TABLE-TREE */
Object g2int_clear_gsi_circularity_table_tree(gsi_circularity_table_tree_for_hash_binary_tree)
    Object gsi_circularity_table_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(51,6);
    element_qm = CDR(gsi_circularity_table_tree_for_hash_binary_tree);
    if (element_qm) {
	g2int_reclaim_gsi_circularity_table_tree_for_hash_leaves(element_qm);
	M_CDR(gsi_circularity_table_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(gsi_circularity_table_tree_for_hash_binary_tree);
}

static Object Qg2int_gsi_circularity_table_tree_for_hash;  /* gsi-circularity-table-tree-for-hash */

/* MAKE-GSI-CIRCULARITY-TABLE */
Object g2int_make_gsi_circularity_table()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(51,7);
    new_vector = g2int_make_gsi_circularity_table_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
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
    M_CAR(gensymed_symbol) = Qg2int_gsi_circularity_table_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* FLATTEN-GSI-CIRCULARITY-TABLE */
Object g2int_flatten_gsi_circularity_table(gsi_circularity_table_hash_table)
    Object gsi_circularity_table_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(51,8);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(gsi_circularity_table_hash_table,index_1);
    if (subtree) {
	temp = g2int_flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-GSI-CIRCULARITY-TABLE */
Object g2int_clear_gsi_circularity_table(gsi_circularity_table_hash_table)
    Object gsi_circularity_table_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(51,9);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    g2int_clear_gsi_circularity_table_tree(ISVREF(gsi_circularity_table_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-GSI-CIRCULARITY-TABLE */
Object g2int_reclaim_gsi_circularity_table(gsi_circularity_table_hash_table)
    Object gsi_circularity_table_hash_table;
{
    Object gsi_circularity_table_tree_for_hash_binary_tree, element_qm;
    Object cdr_new_value, temp;
    SI_Long index_1;

    x_note_fn_call(51,10);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    gsi_circularity_table_tree_for_hash_binary_tree = 
	    ISVREF(gsi_circularity_table_hash_table,index_1);
    element_qm = M_CDR(gsi_circularity_table_tree_for_hash_binary_tree);
    if (element_qm)
	g2int_reclaim_gsi_circularity_table_tree_for_hash_leaves(element_qm);
    inline_note_reclaim_cons(gsi_circularity_table_tree_for_hash_binary_tree,
	    Qg2int_gensym);
    cdr_new_value = G2int_available_gensym_conses;
    M_CDR(gsi_circularity_table_tree_for_hash_binary_tree) = cdr_new_value;
    G2int_available_gensym_conses = 
	    gsi_circularity_table_tree_for_hash_binary_tree;
    ISVREF(gsi_circularity_table_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    g2int_reclaim_gsi_circularity_table_hash_vector(gsi_circularity_table_hash_table);
    return VALUES_1(temp);
}

/* MAYBE-SUSPEND-AND-CONTINUE-BUILDING-OBJECT */
Object g2int_maybe_suspend_and_continue_building_object()
{
    x_note_fn_call(51,11);
    if (IFIX(FIXNUM_ADD(G2int_number_of_icp_bytes_in_message_group,
	    FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
	    G2int_number_of_icp_bytes_to_fill_buffer))) + (SI_Long)3L >= 
	    IFIX(G2int_gsi_maximum_number_of_icp_bytes_to_buffer)) {
	g2int_write_icp_suspend_building_object(FIX((SI_Long)0L));
	g2int_next_icp_message_group();
	if (FIXNUM_NE(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
		G2int_icp_connection_closed))
	    g2int_send_icp_continue_building_resumable_object(G2int_gsi_current_resumable_item);
    }
    return VALUES_1(Nil);
}

/* GSI-PREPARE-FOR-RECURSIVE-DESCENT */
Object g2int_gsi_prepare_for_recursive_descent()
{
    x_note_fn_call(51,12);
    G2int_gsi_current_recursive_depth = FIX((SI_Long)0L);
    G2int_gsi_depth_of_last_transmission = FIX((SI_Long)0L);
    g2int_clear_gsi_circularity_table(G2int_reusable_circularity_table);
    return VALUES_1(Nil);
}

/* ITEM-IN-RESUMABLE-CIRCULARITY-TABLE-P */
Object g2int_item_in_resumable_circularity_table_p(key)
    Object key;
{
    Object temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(51,13);
    gensymed_symbol = SXHASH_SYMBOL_1(key) & IFIX(Most_positive_fixnum);
    temp = G2int_reusable_circularity_table;
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = CDR(temp);
    gensymed_symbol_2 = key;
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
	if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
	    temp = M_CDR(M_CAR(gensymed_symbol_1));
	    goto end;
	}
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end:;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* PUT-ITEM-IN-RESUMABLE-CIRCULARITY-TABLE */
Object g2int_put_item_in_resumable_circularity_table(key)
    Object key;
{
    Object temp;
    SI_Long gensymed_symbol, temp_1;

    x_note_fn_call(51,14);
    gensymed_symbol = SXHASH_SYMBOL_1(key) & IFIX(Most_positive_fixnum);
    temp = G2int_reusable_circularity_table;
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = g2int_set_balanced_binary_tree_entry(SVREF(temp,FIX(temp_1)),
	    Qeq,Nil,T,key,FIX(gensymed_symbol),T);
    return VALUES_1(temp);
}

static Object Qg2int_managed_array;  /* managed-array */

static Object Qg2int_simple_integer_vector;  /* simple-integer-vector */

static Object Qg2int_simple_float_array;  /* simple-float-array */

static Object Qg2int_managed_string_array;  /* managed-string-array */

/* GSI-MAKE-APPROPRIATE-ARRAY */
Object g2int_gsi_make_appropriate_array varargs_1(int, n)
{
    Object gsi_type_tag_init, element_count_init;
    Object gsi_instance_qm, new_array_wrapper, new_array, array;
    Object svref_new_value;
    SI_Long gsi_type_tag, element_count;
    Declare_varargs_nonrelocating;

    x_note_fn_call(51,15);
    INIT_ARGS_nonrelocating();
    gsi_type_tag_init = REQUIRED_ARG_nonrelocating();
    element_count_init = REQUIRED_ARG_nonrelocating();
    gsi_type_tag = IFIX(gsi_type_tag_init);
    element_count = IFIX(element_count_init);
    gsi_instance_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    new_array_wrapper = g2int_make_gsi_array_wrapper_1(Nil,Nil);
    if ( !((SI_Long)-128L <= gsi_type_tag && gsi_type_tag <= (SI_Long)127L))
	new_array = Nil;
    else
	switch ((char)gsi_type_tag) {
	  case 25:
	  case 41:
	  case 26:
	  case 42:
	  case 23:
	  case 39:
	  case 24:
	  case 40:
	    SVREF(new_array_wrapper,FIX((SI_Long)1L)) = Qg2int_managed_array;
	    array = g2int_gsi_allocate_managed_array(FIX(element_count + 
		    (SI_Long)1L));
	    svref_new_value = G2int_gsi_magic_number;
	    SVREF(array,FIX((SI_Long)0L)) = svref_new_value;
	    new_array = array;
	    break;
	  case 17:
	  case 33:
	  case 21:
	  case 37:
	    SVREF(new_array_wrapper,FIX((SI_Long)1L)) = 
		    Qg2int_simple_integer_vector;
	    new_array = g2int_gsi_allocate_managed_array(FIX(element_count));
	    break;
	  case 22:
	  case 38:
	    SVREF(new_array_wrapper,FIX((SI_Long)1L)) = 
		    Qg2int_simple_float_array;
	    new_array = 
		    g2int_allocate_managed_simple_float_array(FIX(element_count));
	    break;
	  case 20:
	  case 36:
	    SVREF(new_array_wrapper,FIX((SI_Long)1L)) = 
		    Qg2int_managed_string_array;
	    new_array = g2int_gsi_allocate_managed_array(FIX(element_count));
	    break;
	  case 19:
	  case 35:
	    SVREF(new_array_wrapper,FIX((SI_Long)1L)) = Qg2int_managed_array;
	    new_array = g2int_gsi_allocate_managed_array(FIX(element_count));
	    break;
	  default:
	    new_array = Nil;
	    break;
	}
    SVREF(new_array_wrapper,FIX((SI_Long)2L)) = new_array;
    g2int_gsi_push_onto_appropriate_list(2,new_array_wrapper,gsi_instance_qm);
    return VALUES_1(new_array);
}

static Object Qg2int_attribute;    /* attribute */

static Object Qg2int_gsi_superior_item;  /* gsi-superior-item */

static Object Qg2int_vector_element;  /* vector-element */

static Object Qg2int_list_element;  /* list-element */

/* GSI-ADD-TO-OR-TRAVERSE-ITEM-INSTANCE */
Object g2int_gsi_add_to_or_traverse_item_instance(current_subobject,
	    attribute_type,attribute_qualifier_qm,attribute_name_or_index,
	    class_name,gsi_type_tag,element_count,symbolic_attribute_count)
    Object current_subobject, attribute_type, attribute_qualifier_qm;
    Object attribute_name_or_index, class_name, gsi_type_tag, element_count;
    Object symbolic_attribute_count;
{
    Object attribute, attribute_item, gsi_instance_extension, temp, temp_2;
    Object item, index_1, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, temp_1;

    x_note_fn_call(51,16);
    if (EQ(attribute_type,Qg2int_attribute)) {
	attribute = g2int_make_gsi_attribute(2,attribute_name_or_index,
		attribute_qualifier_qm);
	attribute_item = g2int_make_gsi_instance(4,gsi_type_tag,Nil,Nil,
		class_name);
	SVREF(attribute,FIX((SI_Long)4L)) = attribute_item;
	gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	temp = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)8L) : Nil;
	gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	gensymed_symbol = gsi_instance_extension ? 
		IFIX(ISVREF(gsi_instance_extension,(SI_Long)9L)) : (SI_Long)0L;
	gensymed_symbol_1 = IFIX(G2int_gsi_magic_offset);
	temp_1 = gensymed_symbol + gensymed_symbol_1;
	ISVREF(temp,temp_1) = attribute;
	gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	gensymed_symbol = gsi_instance_extension ? 
		IFIX(ISVREF(gsi_instance_extension,(SI_Long)9L)) : (SI_Long)0L;
	gensymed_symbol_1 = (SI_Long)1L;
	temp_1 = gensymed_symbol + gensymed_symbol_1;
	gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(current_subobject,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	ISVREF(gsi_instance_extension,(SI_Long)9L) = FIX(temp_1);
	if (IFIX(symbolic_attribute_count) > (SI_Long)0L) {
	    gsi_instance_extension = ISVREF(attribute_item,(SI_Long)3L);
	    if ( !TRUEP(gsi_instance_extension)) {
		gsi_instance_extension = g2int_make_gsi_instance_extension_1();
		SVREF(attribute_item,FIX((SI_Long)3L)) = 
			gsi_instance_extension;
	    }
	    temp = g2int_gsi_make_appropriate_array(2,
		    G2int_gsi_item_array_type_tag,symbolic_attribute_count);
	    SVREF(gsi_instance_extension,FIX((SI_Long)8L)) = temp;
	}
	if (IFIX(element_count) > (SI_Long)0L) {
	    temp = g2int_gsi_make_appropriate_array(3,gsi_type_tag,
		    element_count,attribute_item);
	    SVREF(attribute_item,FIX((SI_Long)2L)) = temp;
	}
	g2int_set_gsi_instance_plist_value(attribute_item,
		Qg2int_gsi_superior_item,current_subobject);
	temp = G2int_current_receiving_resumable_object;
	SVREF(temp,FIX((SI_Long)8L)) = attribute_item;
	temp_2 = attribute_item;
    }
    else if (EQ(attribute_type,Qg2int_vector_element) || EQ(attribute_type,
	    Qg2int_list_element)) {
	item = g2int_make_gsi_instance(4,gsi_type_tag,Nil,Nil,class_name);
	gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	index_1 = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)7L) : FIX((SI_Long)0L);
	temp = ISVREF(current_subobject,(SI_Long)2L);
	svref_arg_2 = FIXNUM_ADD1(index_1);
	SVREF(temp,svref_arg_2) = item;
	gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	gensymed_symbol = gsi_instance_extension ? 
		IFIX(ISVREF(gsi_instance_extension,(SI_Long)7L)) : (SI_Long)0L;
	gensymed_symbol_1 = (SI_Long)1L;
	temp_1 = gensymed_symbol + gensymed_symbol_1;
	gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(current_subobject,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	ISVREF(gsi_instance_extension,(SI_Long)7L) = FIX(temp_1);
	if (IFIX(symbolic_attribute_count) > (SI_Long)0L) {
	    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	    if ( !TRUEP(gsi_instance_extension)) {
		gsi_instance_extension = g2int_make_gsi_instance_extension_1();
		SVREF(item,FIX((SI_Long)3L)) = gsi_instance_extension;
	    }
	    temp = g2int_gsi_make_appropriate_array(2,
		    G2int_gsi_item_array_type_tag,symbolic_attribute_count);
	    SVREF(gsi_instance_extension,FIX((SI_Long)8L)) = temp;
	}
	if (IFIX(element_count) > (SI_Long)0L) {
	    temp = g2int_gsi_make_appropriate_array(3,gsi_type_tag,
		    element_count,item);
	    SVREF(item,FIX((SI_Long)2L)) = temp;
	}
	g2int_set_gsi_instance_plist_value(item,Qg2int_gsi_superior_item,
		current_subobject);
	temp = G2int_current_receiving_resumable_object;
	SVREF(temp,FIX((SI_Long)8L)) = item;
	temp_2 = item;
    }
    else
	temp_2 = Qnil;
    return VALUES_1(temp_2);
}

/* GSI-BUILD-ITEM-INSTANCE */
Object g2int_gsi_build_item_instance(attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index,class_name,gsi_type_tag,
	    list_or_vector_length,symbolic_attribute_count)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, gsi_type_tag, list_or_vector_length;
    Object symbolic_attribute_count;
{
    Object current_subobject_qm, temp, toplevel_object, gsi_instance_extension;
    Object temp_1;

    x_note_fn_call(51,17);
    current_subobject_qm = ISVREF(G2int_current_receiving_resumable_object,
	    (SI_Long)8L);
    if (current_subobject_qm)
	temp = 
		g2int_gsi_add_to_or_traverse_item_instance(current_subobject_qm,
		attribute_type,attribute_qualifier_qm,
		attribute_name_or_index,class_name,gsi_type_tag,
		list_or_vector_length,symbolic_attribute_count);
    else {
	toplevel_object = g2int_make_gsi_instance(4,gsi_type_tag,Nil,Nil,
		class_name);
	if (IFIX(symbolic_attribute_count) > (SI_Long)0L) {
	    gsi_instance_extension = ISVREF(toplevel_object,(SI_Long)3L);
	    if ( !TRUEP(gsi_instance_extension)) {
		gsi_instance_extension = g2int_make_gsi_instance_extension_1();
		SVREF(toplevel_object,FIX((SI_Long)3L)) = 
			gsi_instance_extension;
	    }
	    temp_1 = g2int_gsi_make_appropriate_array(2,
		    G2int_gsi_item_array_type_tag,symbolic_attribute_count);
	    SVREF(gsi_instance_extension,FIX((SI_Long)8L)) = temp_1;
	}
	if (IFIX(list_or_vector_length) > (SI_Long)0L) {
	    temp_1 = g2int_gsi_make_appropriate_array(3,gsi_type_tag,
		    list_or_vector_length,toplevel_object);
	    SVREF(toplevel_object,FIX((SI_Long)2L)) = temp_1;
	}
	temp_1 = G2int_current_receiving_resumable_object;
	SVREF(temp_1,FIX((SI_Long)7L)) = toplevel_object;
	temp_1 = G2int_current_receiving_resumable_object;
	SVREF(temp_1,FIX((SI_Long)8L)) = toplevel_object;
	temp = toplevel_object;
    }
    return VALUES_1(temp);
}

static Object Qg2int_long;         /* long */

static Object Qg2int_float;        /* |float| */

static Object Qg2int_text;         /* text */

static Object Qg2int_truth;        /* truth */

/* GSI-TYPE-FROM-G2-ELEMENT-TYPE */
Object g2int_gsi_type_from_g2_element_type(g2_element_type)
    Object g2_element_type;
{
    Object temp;

    x_note_fn_call(51,18);
    if (EQ(g2_element_type,Qinteger))
	temp = G2int_gsi_integer_type_tag;
    else if (EQ(g2_element_type,Qg2int_long))
	temp = G2int_gsi_long_type_tag;
    else if (EQ(g2_element_type,Qg2int_float))
	temp = G2int_gsi_64bit_float_type_tag;
    else if (EQ(g2_element_type,Qg2int_text))
	temp = G2int_gsi_string_type_tag;
    else if (EQ(g2_element_type,Qg2int_truth))
	temp = G2int_gsi_logical_type_tag;
    else if (EQ(g2_element_type,Qsymbol))
	temp = G2int_gsi_symbol_type_tag;
    else
	temp = G2int_gsi_null_type_tag;
    return VALUES_1(temp);
}

static Object Qg2int_g2_element_type_from_gsi_type;  /* g2-element-type-from-gsi-type */

/* G2-ELEMENT-TYPE-FROM-GSI-TYPE */
Object g2int_g2_element_type_from_gsi_type(gsi_type)
    Object gsi_type;
{
    Object temp;

    x_note_fn_call(51,19);
    if ( !(FIXNUMP(gsi_type) && FIXNUM_LE(FIX((SI_Long)-128L),gsi_type) && 
	    FIXNUM_LE(gsi_type,FIX((SI_Long)127L))))
	temp = g2int_gsi_connection_error(2,
		Qg2int_g2_element_type_from_gsi_type,
		G2int_gsi_unknown_type_tag);
    else
	switch (INTEGER_TO_CHAR(gsi_type)) {
	  case 1:
	    temp = Qinteger;
	    break;
	  case 51:
	    temp = Qg2int_long;
	    break;
	  case 6:
	    temp = Qg2int_float;
	    break;
	  case 4:
	    temp = Qg2int_text;
	    break;
	  case 11:
	    temp = Qg2int_text;
	    break;
	  case 5:
	    temp = Qg2int_truth;
	    break;
	  case 3:
	    temp = Qsymbol;
	    break;
	  case 8:
	    temp = Nil;
	    break;
	  case 10:
	    temp = Nil;
	    break;
	  default:
	    temp = g2int_gsi_connection_error(2,
		    Qg2int_g2_element_type_from_gsi_type,
		    G2int_gsi_unknown_type_tag);
	    break;
	}
    return VALUES_1(temp);
}

/* GSI-ARRAY-TYPE-FROM-G2-ELEMENT-TYPE */
Object g2int_gsi_array_type_from_g2_element_type(g2_element_type)
    Object g2_element_type;
{
    Object temp;

    x_note_fn_call(51,20);
    if (EQ(g2_element_type,Qinteger))
	temp = G2int_gsi_integer_array_type_tag;
    else if (EQ(g2_element_type,Qg2int_float))
	temp = G2int_gsi_64bit_float_array_type_tag;
    else if (EQ(g2_element_type,Qg2int_text))
	temp = G2int_gsi_string_array_type_tag;
    else if (EQ(g2_element_type,Qg2int_truth))
	temp = G2int_gsi_logical_array_type_tag;
    else if (EQ(g2_element_type,Qsymbol))
	temp = G2int_gsi_symbol_array_type_tag;
    else
	temp = G2int_gsi_value_array_type_tag;
    return VALUES_1(temp);
}

/* GSI-LIST-TYPE-FROM-G2-ELEMENT-TYPE */
Object g2int_gsi_list_type_from_g2_element_type(g2_element_type)
    Object g2_element_type;
{
    Object temp;

    x_note_fn_call(51,21);
    if (EQ(g2_element_type,Qinteger))
	temp = G2int_gsi_integer_list_type_tag;
    else if (EQ(g2_element_type,Qg2int_float))
	temp = G2int_gsi_64bit_float_list_type_tag;
    else if (EQ(g2_element_type,Qg2int_text))
	temp = G2int_gsi_string_list_type_tag;
    else if (EQ(g2_element_type,Qg2int_truth))
	temp = G2int_gsi_logical_list_type_tag;
    else if (EQ(g2_element_type,Qsymbol))
	temp = G2int_gsi_symbol_list_type_tag;
    else
	temp = G2int_gsi_value_list_type_tag;
    return VALUES_1(temp);
}

/* G2-ELEMENT-TYPE-FROM-GSI-COLLECTION-TYPE */
Object g2int_g2_element_type_from_gsi_collection_type(gsi_collection_type)
    Object gsi_collection_type;
{
    Object temp;

    x_note_fn_call(51,22);
    if ( !(FIXNUMP(gsi_collection_type) && FIXNUM_LE(FIX((SI_Long)-128L),
	    gsi_collection_type) && FIXNUM_LE(gsi_collection_type,
	    FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(gsi_collection_type)) {
	  case 33:
	  case 17:
	    temp = Qinteger;
	    break;
	  case 38:
	  case 22:
	    temp = Qg2int_float;
	    break;
	  case 36:
	  case 20:
	    temp = Qg2int_text;
	    break;
	  case 37:
	  case 21:
	    temp = Qg2int_truth;
	    break;
	  case 35:
	  case 19:
	    temp = Qsymbol;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_1(temp);
}

/* GSI-TYPE-FROM-LEAF-TYPE */
Object g2int_gsi_type_from_leaf_type(leaf_type)
    Object leaf_type;
{
    Object temp;

    x_note_fn_call(51,23);
    if ( !(FIXNUMP(leaf_type) && FIXNUM_LE(FIX((SI_Long)-128L),leaf_type) 
	    && FIXNUM_LE(leaf_type,FIX((SI_Long)127L))))
	temp = G2int_gsi_null_type_tag;
    else
	switch (INTEGER_TO_CHAR(leaf_type)) {
	  case 5:
	    temp = G2int_gsi_integer_type_tag;
	    break;
	  case 16:
	    temp = G2int_gsi_long_type_tag;
	    break;
	  case 6:
	    temp = G2int_gsi_64bit_float_type_tag;
	    break;
	  case 7:
	    temp = G2int_gsi_symbol_type_tag;
	    break;
	  case 0:
	    temp = G2int_gsi_symbol_type_tag;
	    break;
	  case 1:
	    temp = G2int_gsi_symbol_type_tag;
	    break;
	  case 8:
	    temp = G2int_gsi_string_type_tag;
	    break;
	  case 9:
	    temp = G2int_gsi_logical_type_tag;
	    break;
	  default:
	    temp = G2int_gsi_null_type_tag;
	    break;
	}
    return VALUES_1(temp);
}

/* SIMPLE-VALUE-TYPE-P */
Object g2int_simple_value_type_p(type)
    Object type;
{
    Object temp;

    x_note_fn_call(51,24);
    if ( !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) && 
	    FIXNUM_LE(type,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(type)) {
	  case 1:
	  case 51:
	  case 6:
	  case 5:
	  case 3:
	  case 4:
	  case 11:
	    temp = T;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_1(temp);
}

/* SIMPLE-OR-NULL-VALUE-TYPE-P */
Object g2int_simple_or_null_value_type_p(type)
    Object type;
{
    Object temp;

    x_note_fn_call(51,25);
    if ( !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) && 
	    FIXNUM_LE(type,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(type)) {
	  case 1:
	  case 51:
	  case 6:
	  case 5:
	  case 3:
	  case 4:
	  case 11:
	  case 0:
	    temp = T;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_1(temp);
}

static Object Qg2int_name;         /* name */

static Object Qg2int_current_value;  /* current-value */

/* GSI-ADD-LEAF-TO-ITEM-INSTANCE */
Object g2int_gsi_add_leaf_to_item_instance(current_subobject,
	    attribute_type,attribute_qualifier_qm,attribute_name_or_index,
	    leaf_value,leaf_type)
    Object current_subobject, attribute_type, attribute_qualifier_qm;
    Object attribute_name_or_index, leaf_value, leaf_type;
{
    Object gsi_type_tag, gsi_instance_extension, temp, leaf, svref_arg_1;
    Object leaf_instance, element_count, current_subobject_qm, index_1;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, temp_1;

    x_note_fn_call(51,26);
    gsi_type_tag = g2int_gsi_type_from_leaf_type(leaf_type);
    if (EQ(attribute_type,Qg2int_attribute)) {
	if (EQ(attribute_name_or_index,Qg2int_name)) {
	    gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	    if ( !TRUEP(gsi_instance_extension)) {
		gsi_instance_extension = g2int_make_gsi_instance_extension_1();
		SVREF(current_subobject,FIX((SI_Long)3L)) = 
			gsi_instance_extension;
	    }
	    temp = SVREF(gsi_instance_extension,FIX((SI_Long)4L)) = leaf_value;
	}
	else if (EQ(attribute_name_or_index,Qg2int_current_value)) {
	    SVREF(current_subobject,FIX((SI_Long)2L)) = leaf_value;
	    temp = g2int_set_gsi_instance_value_type(current_subobject,
		    gsi_type_tag);
	}
	else {
	    leaf = g2int_make_gsi_attribute(2,attribute_name_or_index,
		    attribute_qualifier_qm);
	    gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	    svref_arg_1 = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
	    gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	    gensymed_symbol = gsi_instance_extension ? 
		    IFIX(ISVREF(gsi_instance_extension,(SI_Long)9L)) : 
		    (SI_Long)0L;
	    gensymed_symbol_1 = IFIX(G2int_gsi_magic_offset);
	    temp_1 = gensymed_symbol + gensymed_symbol_1;
	    ISVREF(svref_arg_1,temp_1) = leaf;
	    gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	    gensymed_symbol = gsi_instance_extension ? 
		    IFIX(ISVREF(gsi_instance_extension,(SI_Long)9L)) : 
		    (SI_Long)0L;
	    gensymed_symbol_1 = (SI_Long)1L;
	    temp_1 = gensymed_symbol + gensymed_symbol_1;
	    gsi_instance_extension = ISVREF(current_subobject,(SI_Long)3L);
	    if ( !TRUEP(gsi_instance_extension)) {
		gsi_instance_extension = g2int_make_gsi_instance_extension_1();
		SVREF(current_subobject,FIX((SI_Long)3L)) = 
			gsi_instance_extension;
	    }
	    ISVREF(gsi_instance_extension,(SI_Long)9L) = FIX(temp_1);
	    if (EQ(leaf_type,G2int_circular_reference_tag))
		temp = SVREF(leaf,FIX((SI_Long)4L)) = leaf_value;
	    else {
		leaf_instance = g2int_make_gsi_instance(2,gsi_type_tag,
			leaf_value);
		SVREF(leaf,FIX((SI_Long)4L)) = leaf_instance;
		gsi_instance_extension = ISVREF(leaf_instance,(SI_Long)3L);
		element_count = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L);
		if (element_count) {
		    gsi_instance_extension = ISVREF(leaf_instance,(SI_Long)3L);
		    if ( !TRUEP(gsi_instance_extension)) {
			gsi_instance_extension = 
				g2int_make_gsi_instance_extension_1();
			SVREF(leaf_instance,FIX((SI_Long)3L)) = 
				gsi_instance_extension;
		    }
		    temp = ISVREF(gsi_instance_extension,(SI_Long)7L) = 
			    FIX((SI_Long)0L);
		}
		else
		    temp = Nil;
	    }
	}
    }
    else if (EQ(attribute_type,Qg2int_vector_element) || EQ(attribute_type,
	    Qg2int_list_element)) {
	if (EQ(leaf_type,G2int_circular_reference_tag)) {
	    current_subobject_qm = 
		    ISVREF(G2int_current_receiving_resumable_object,
		    (SI_Long)8L);
	    if (current_subobject_qm) {
		gsi_instance_extension = ISVREF(current_subobject_qm,
			(SI_Long)3L);
		index_1 = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L);
		svref_arg_1 = ISVREF(current_subobject_qm,(SI_Long)2L);
		svref_arg_2 = FIXNUM_ADD1(index_1);
		SVREF(svref_arg_1,svref_arg_2) = leaf_value;
		gsi_instance_extension = ISVREF(current_subobject_qm,
			(SI_Long)3L);
		gensymed_symbol = gsi_instance_extension ? 
			IFIX(ISVREF(gsi_instance_extension,(SI_Long)7L)) : 
			(SI_Long)0L;
		gensymed_symbol_1 = (SI_Long)1L;
		temp_1 = gensymed_symbol + gensymed_symbol_1;
		gsi_instance_extension = ISVREF(current_subobject_qm,
			(SI_Long)3L);
		if ( !TRUEP(gsi_instance_extension)) {
		    gsi_instance_extension = 
			    g2int_make_gsi_instance_extension_1();
		    SVREF(current_subobject_qm,FIX((SI_Long)3L)) = 
			    gsi_instance_extension;
		}
		ISVREF(gsi_instance_extension,(SI_Long)7L) = FIX(temp_1);
		g2int_set_gsi_instance_plist_value(leaf_value,
			Qg2int_gsi_superior_item,current_subobject_qm);
		svref_arg_1 = G2int_current_receiving_resumable_object;
		temp = SVREF(svref_arg_1,FIX((SI_Long)8L)) = leaf_value;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* GSI-RECEIVE-ADD-HISTORY-RANGE */
Object g2int_gsi_receive_add_history_range(timestamps_use_float_array_p,
	    values_use_float_array_p,number_of_elements)
    Object timestamps_use_float_array_p, values_use_float_array_p;
    Object number_of_elements;
{
    Object receiving_item, gsi_instance_extension, history_structure;
    Object timestamps, values_1, temp, base_time, current_index;
    Object svref_new_value, history_value, value_type;
    SI_Long i, ab_loop_repeat_, svref_arg_2;
    double temp_1, aref_new_value;
    Object result;

    x_note_fn_call(51,27);
    receiving_item = ISVREF(G2int_current_receiving_resumable_object,
	    (SI_Long)8L);
    gsi_instance_extension = ISVREF(receiving_item,(SI_Long)3L);
    history_structure = gsi_instance_extension ? 
	    ISVREF(gsi_instance_extension,(SI_Long)12L) : Nil;
    timestamps = ISVREF(history_structure,(SI_Long)3L);
    values_1 = ISVREF(history_structure,(SI_Long)2L);
    temp = ISVREF(history_structure,(SI_Long)5L);
    base_time = FIRST(temp);
    current_index = ISVREF(history_structure,(SI_Long)6L);
    if (timestamps_use_float_array_p || values_use_float_array_p) {
	if (timestamps_use_float_array_p && values_use_float_array_p) {
	    i = IFIX(current_index);
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	    svref_arg_2 = i + (SI_Long)1L;
	    svref_new_value = g2int_make_gsi_instance(2,
		    G2int_gsi_64bit_float_type_tag,
		    g2int_read_icp_managed_double_float());
	    ISVREF(values_1,svref_arg_2) = svref_new_value;
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	else if (timestamps_use_float_array_p) {
	    i = IFIX(current_index);
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	    result = g2int_read_icp_attribute_value();
	    MVS_2(result,history_value,value_type);
	    svref_arg_2 = i + (SI_Long)1L;
	    svref_new_value = g2int_make_gsi_instance(2,
		    g2int_gsi_type_from_leaf_type(value_type),history_value);
	    ISVREF(values_1,svref_arg_2) = svref_new_value;
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else if (values_use_float_array_p) {
	    i = IFIX(current_index);
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_2:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_2;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if (EQ(g2int_read_icp_byte(),G2int_attribute_value_integer_tag)) {
		temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
		aref_new_value = temp_1 + 
			(double)IFIX(g2int_read_icp_fixnum());
	    }
	    else {
		temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
		aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	    }
	    DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	    svref_arg_2 = i + (SI_Long)1L;
	    svref_new_value = g2int_make_gsi_instance(2,
		    G2int_gsi_64bit_float_type_tag,
		    g2int_read_icp_managed_double_float());
	    ISVREF(values_1,svref_arg_2) = svref_new_value;
	    i = i + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:;
	}
    }
    else {
	i = IFIX(current_index);
	ab_loop_repeat_ = IFIX(number_of_elements);
      next_loop_3:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_3;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(g2int_read_icp_byte(),G2int_attribute_value_integer_tag)) {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + (double)IFIX(g2int_read_icp_fixnum());
	}
	else {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	}
	DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	result = g2int_read_icp_attribute_value();
	MVS_2(result,history_value,value_type);
	svref_arg_2 = i + (SI_Long)1L;
	svref_new_value = g2int_make_gsi_instance(2,
		g2int_gsi_type_from_leaf_type(value_type),history_value);
	ISVREF(values_1,svref_arg_2) = svref_new_value;
	i = i + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
    }
    svref_new_value = FIXNUM_ADD(current_index,number_of_elements);
    SVREF(history_structure,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qg2int_gsi_receive_add_homogeneous_history_range;  /* gsi-receive-add-homogeneous-history-range */

/* GSI-RECEIVE-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object g2int_gsi_receive_add_homogeneous_history_range(timestamps_use_floats_qm,
	    element_type,number_of_elements)
    Object timestamps_use_floats_qm, element_type, number_of_elements;
{
    Object receiving_item, gsi_instance_extension, history_structure;
    Object timestamps, values_1, temp, base_time, current_index;
    Object svref_new_value, symbol;
    SI_Long i, ab_loop_repeat_, aref_new_value_1;
    double temp_1, aref_new_value;

    x_note_fn_call(51,28);
    receiving_item = ISVREF(G2int_current_receiving_resumable_object,
	    (SI_Long)8L);
    gsi_instance_extension = ISVREF(receiving_item,(SI_Long)3L);
    history_structure = gsi_instance_extension ? 
	    ISVREF(gsi_instance_extension,(SI_Long)12L) : Nil;
    timestamps = ISVREF(history_structure,(SI_Long)3L);
    values_1 = ISVREF(history_structure,(SI_Long)2L);
    temp = ISVREF(history_structure,(SI_Long)5L);
    base_time = FIRST(temp);
    current_index = ISVREF(history_structure,(SI_Long)6L);
    if (timestamps_use_floats_qm) {
	if (EQ(element_type,Qinteger) || EQ(element_type,Qg2int_truth)) {
	    i = IFIX(current_index);
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	    aref_new_value_1 = IFIX(g2int_read_icp_fixnum());
	    BYTE_32_ISASET_1(values_1,i,aref_new_value_1);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	else if (EQ(element_type,Qg2int_float)) {
	    i = IFIX(current_index);
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	    aref_new_value = g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(values_1,i,aref_new_value);
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else if (EQ(element_type,Qg2int_text)) {
	    i = IFIX(current_index);
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_2:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_2;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	    svref_new_value = 
		    inline_extract_c_string(g2int_convert_value_to_gsi_value(g2int_read_icp_text_string()));
	    ISVREF(values_1,i) = svref_new_value;
	    i = i + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:;
	}
	else if (EQ(element_type,Qsymbol)) {
	    i = IFIX(current_index);
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	    symbol = g2int_read_icp_possibly_interned_symbol();
	    svref_new_value = 
		    g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) ? 
		    symbol : 
		    inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
		    G2int_gsi_wide_api_p));
	    ISVREF(values_1,i) = svref_new_value;
	    i = i + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	}
	else
	    g2int_gsi_connection_error(2,
		    Qg2int_gsi_receive_add_homogeneous_history_range,
		    G2int_gsi_invalid_history_type);
    }
    else if (EQ(element_type,Qinteger) || EQ(element_type,Qg2int_truth)) {
	i = IFIX(current_index);
	ab_loop_repeat_ = IFIX(number_of_elements);
      next_loop_4:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_4;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(g2int_read_icp_byte(),G2int_attribute_value_integer_tag)) {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + (double)IFIX(g2int_read_icp_fixnum());
	}
	else {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	}
	DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	aref_new_value_1 = IFIX(g2int_read_icp_fixnum());
	BYTE_32_ISASET_1(values_1,i,aref_new_value_1);
	i = i + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
    }
    else if (EQ(element_type,Qg2int_float)) {
	i = IFIX(current_index);
	ab_loop_repeat_ = IFIX(number_of_elements);
      next_loop_5:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_5;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(g2int_read_icp_byte(),G2int_attribute_value_integer_tag)) {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + (double)IFIX(g2int_read_icp_fixnum());
	}
	else {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	}
	DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	aref_new_value = g2int_read_icp_double_float_1();
	DFLOAT_ISASET_1(values_1,i,aref_new_value);
	i = i + (SI_Long)1L;
	goto next_loop_5;
      end_loop_5:;
    }
    else if (EQ(element_type,Qg2int_text)) {
	i = IFIX(current_index);
	ab_loop_repeat_ = IFIX(number_of_elements);
      next_loop_6:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_6;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(g2int_read_icp_byte(),G2int_attribute_value_integer_tag)) {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + (double)IFIX(g2int_read_icp_fixnum());
	}
	else {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	}
	DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	svref_new_value = 
		inline_extract_c_string(g2int_convert_value_to_gsi_value(g2int_read_icp_text_string()));
	ISVREF(values_1,i) = svref_new_value;
	i = i + (SI_Long)1L;
	goto next_loop_6;
      end_loop_6:;
    }
    else if (EQ(element_type,Qsymbol)) {
	i = IFIX(current_index);
	ab_loop_repeat_ = IFIX(number_of_elements);
      next_loop_7:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_7;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(g2int_read_icp_byte(),G2int_attribute_value_integer_tag)) {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + (double)IFIX(g2int_read_icp_fixnum());
	}
	else {
	    temp_1 = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	    aref_new_value = temp_1 + g2int_read_icp_double_float_1();
	}
	DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	symbol = g2int_read_icp_possibly_interned_symbol();
	svref_new_value = 
		g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) ? 
		symbol : 
		inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
		G2int_gsi_wide_api_p));
	ISVREF(values_1,i) = svref_new_value;
	i = i + (SI_Long)1L;
	goto next_loop_7;
      end_loop_7:;
    }
    else
	g2int_gsi_connection_error(2,
		Qg2int_gsi_receive_add_homogeneous_history_range,
		G2int_gsi_invalid_history_type);
    svref_new_value = FIXNUM_ADD(current_index,number_of_elements);
    SVREF(history_structure,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* GSI-ADD-RESUMABLE-CIRCULARITY */
Object g2int_gsi_add_resumable_circularity(corresponding_index)
    Object corresponding_index;
{
    Object svref_arg_1, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(51,29);
    g2int_store_corresponding_icp_object(corresponding_index,
	    ISVREF(G2int_current_receiving_resumable_object,(SI_Long)8L));
    svref_arg_1 = G2int_current_receiving_resumable_object;
    gensym_push_modify_macro_arg = corresponding_index;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)12L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(svref_arg_1,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qg2int_gsi;          /* gsi */

/* GSI-DELAYED-INVOCATION */
Object g2int_gsi_delayed_invocation(pending_invocation)
    Object pending_invocation;
{
    Object invocation_type, rpc_argument_list, remote_procedure_name;
    Object remote_procedure_identifier;

    x_note_fn_call(51,30);
    invocation_type = ISVREF(pending_invocation,(SI_Long)2L);
    rpc_argument_list = ISVREF(pending_invocation,(SI_Long)1L);
    remote_procedure_name = ISVREF(pending_invocation,(SI_Long)3L);
    remote_procedure_identifier = ISVREF(pending_invocation,(SI_Long)4L);
    g2int_gsi_start_or_call_local_function_or_handle_return_values(invocation_type,
	    remote_procedure_name,remote_procedure_identifier,
	    rpc_argument_list);
    if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	g2int_gsi_reclaim_contents(ISVREF(pending_invocation,(SI_Long)7L),
		Qg2int_gsi);
	SVREF(pending_invocation,FIX((SI_Long)7L)) = Nil;
    }
    SVREF(pending_invocation,FIX((SI_Long)1L)) = Nil;
    g2int_reclaim_receiving_rpc_arglist_structure_1(pending_invocation);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;  /* g2-defstruct-structure-name::receiving-resumable-object-g2-struct */

/* GSI-CHECK-IF-ALL-ITEMS-ARE-BUILT */
Object g2int_gsi_check_if_all_items_are_built(pending_invocation)
    Object pending_invocation;
{
    Object previous_qm, next_qm, temp, arguments, argument_or_resumable, item;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(51,31);
    previous_qm = ISVREF(G2int_current_receiving_resumable_object,(SI_Long)4L);
    next_qm = ISVREF(G2int_current_receiving_resumable_object,(SI_Long)3L);
    if (previous_qm && next_qm) {
	SVREF(previous_qm,FIX((SI_Long)3L)) = next_qm;
	temp = SVREF(next_qm,FIX((SI_Long)4L)) = previous_qm;
    }
    else if (previous_qm)
	temp = SVREF(previous_qm,FIX((SI_Long)3L)) = next_qm;
    else if (next_qm)
	temp = SVREF(next_qm,FIX((SI_Long)4L)) = Nil;
    else {
	arguments = ISVREF(pending_invocation,(SI_Long)1L);
	i = IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = IFIX(length(arguments));
	argument_or_resumable = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	argument_or_resumable = ISVREF(arguments,i);
	if (SIMPLE_VECTOR_P(argument_or_resumable) && 
		EQ(ISVREF(argument_or_resumable,(SI_Long)0L),
		Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		    {
	    item = ISVREF(argument_or_resumable,(SI_Long)7L);
	    g2int_reclaim_single_receiving_resumable_object(argument_or_resumable);
	    ISVREF(arguments,i) = item;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	temp = g2int_gsi_delayed_invocation(pending_invocation);
    }
    return VALUES_1(temp);
}

/* COPY-PORTION-OF-STRING-INTO-STRING */
Object g2int_copy_portion_of_string_into_string(source_string,source_start,
	    source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    Object ab_loop_iter_flag_;
    SI_Long i, ab_loop_bind_, j;
    char aref_new_value;

    x_note_fn_call(51,32);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(destination_string) != (SI_Long)0L)
	return g2int_copy_portion_of_string_into_text_string(source_string,
		source_start,source_end,destination_string,destination_start);
    else if ( !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(source_string) != 
	    (SI_Long)0L))
	return g2int_copy_portion_of_string_into_gensym_string(source_string,
		source_start,source_end,destination_string,destination_start);
    else {
	i = IFIX(source_start);
	ab_loop_bind_ = IFIX(source_end);
	j = IFIX(destination_start);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	aref_new_value = ICHAR(source_string,i);
	UBYTE_16_ISASET_1(destination_string,j,(SI_Long)aref_new_value);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* SIMPLE-TEXT-STRING-COPY-FROM-ATTRIBUTE-NAME */
Object g2int_simple_text_string_copy_from_attribute_name(base_name,
	    class_qualifier_qm)
    Object base_name, class_qualifier_qm;
{
    Object temp;

    x_note_fn_call(51,33);
    temp = g2int_simple_text_string_copy_from_attribute_name_1(base_name,
	    class_qualifier_qm,G2int_gsi_wide_api_p);
    return VALUES_1(temp);
}

static Object array_constant;      /* # */

static Object string_constant;     /* "::" */

/* SIMPLE-TEXT-STRING-COPY-FROM-ATTRIBUTE-NAME-1 */
Object g2int_simple_text_string_copy_from_attribute_name_1(base_name,
	    class_qualifier_qm,wide_string_p)
    Object base_name, class_qualifier_qm, wide_string_p;
{
    Object base_string, base_length, qualifier_string, qualifier_length;
    Object simple_text_string, temp;
    SI_Long actual_length;

    x_note_fn_call(51,34);
    base_string = wide_string_p ? g2int_symbol_name_text_string(base_name) 
	    : SYMBOL_NAME(base_name);
    base_length = g2int_lengthw(base_string);
    if (class_qualifier_qm) {
	qualifier_string = wide_string_p ? 
		g2int_symbol_name_text_string(class_qualifier_qm) : 
		SYMBOL_NAME(class_qualifier_qm);
	qualifier_length = g2int_lengthw(qualifier_string);
	actual_length = IFIX(FIXNUM_ADD(base_length,qualifier_length)) + 
		(SI_Long)2L;
	simple_text_string = wide_string_p ? 
		g2int_obtain_simple_text_string(FIX(actual_length)) : 
		g2int_obtain_simple_gensym_string(FIX(actual_length));
	g2int_copy_portion_of_string_into_string(qualifier_string,
		FIX((SI_Long)0L),qualifier_length,simple_text_string,
		FIX((SI_Long)0L));
	g2int_copy_portion_of_string_into_string(wide_string_p ? 
		array_constant : string_constant,FIX((SI_Long)0L),
		FIX((SI_Long)2L),simple_text_string,qualifier_length);
	g2int_copy_portion_of_string_into_string(base_string,
		FIX((SI_Long)0L),base_length,simple_text_string,
		FIX(IFIX(qualifier_length) + (SI_Long)2L));
	temp = simple_text_string;
    }
    else {
	simple_text_string = wide_string_p ? 
		g2int_obtain_simple_text_string(base_length) : 
		g2int_obtain_simple_gensym_string(base_length);
	g2int_copy_portion_of_string_into_string(base_string,
		FIX((SI_Long)0L),base_length,simple_text_string,
		FIX((SI_Long)0L));
	temp = simple_text_string;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_history_item;  /* send_history_item */

static Object array_constant_1;    /* # */

static Object string_constant_1;   /* "" */

/* GSI-SEND-HISTORY-ITEM */
Object g2int_gsi_send_history_item(attribute_spec_qm,class_1,
	    attribute_count,item)
    Object attribute_spec_qm, class_1, attribute_count, item;
{
    Object gsi_instance_extension, history, history_length, timestamps;
    Object values_1, g2_element_type, remainder_count, range_count, value;
    Object logical, string_1, element, symbol;
    SI_Long history_type, timestamp_index, ab_loop_repeat_, i;
    char copy_string_value_p;
    double timestamp, float_1;

    x_note_fn_call(51,35);
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    history = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)12L) : Nil;
    history_type = IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L;
    history_length = ISVREF(history,(SI_Long)1L);
    timestamps = ISVREF(history,(SI_Long)3L);
    values_1 = ISVREF(history,(SI_Long)2L);
    g2_element_type = g2int_g2_element_type_from_gsi_type(FIX(history_type));
    g2int_write_icp_add_attribute_history_object(attribute_spec_qm,class_1,
	    Nil,attribute_count,g2_element_type,history_length,
	    ISVREF(history,(SI_Long)4L),ISVREF(history,(SI_Long)5L),T,
	    EQ(FIX(history_type),G2int_gsi_64bit_float_type_tag) ? T : Nil);
    if (EQ(FIX(history_type),G2int_gsi_value_type_tag) || 
	    EQ(FIX(history_type),G2int_gsi_quantity_type_tag)) {
	remainder_count = history_length;
	range_count = Nil;
      next_loop:
	range_count = FIXNUM_MIN(remainder_count,
		G2int_gsi_collection_range_limit);
	if ( !FIXNUM_PLUSP(range_count))
	    goto end_loop;
	g2int_write_icp_byte(FIX((SI_Long)18L));
	g2int_write_icp_boolean(T);
	g2int_write_icp_boolean(Nil);
	g2int_write_icp_fixnum(range_count);
	timestamp_index = IFIX(FIXNUM_MINUS(history_length,remainder_count));
	ab_loop_repeat_ = IFIX(range_count);
	timestamp = 0.0;
	value = Nil;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	timestamp = DFLOAT_ISAREF_1(timestamps,timestamp_index);
	value = ISVREF(values_1,timestamp_index + (SI_Long)1L);
	g2int_write_icp_double_float_1(timestamp);
	g2int_write_icp_attribute_value(value,Nil);
	timestamp_index = timestamp_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	remainder_count = FIXNUM_MINUS(remainder_count,range_count);
	if (FIXNUM_PLUSP(remainder_count)) {
	    g2int_maybe_suspend_and_continue_building_object();
	    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
		    G2int_icp_connection_closed))
		goto end;
	}
	goto next_loop;
      end_loop:
      end:;
    }
    else {
	remainder_count = history_length;
	range_count = Nil;
      next_loop_2:
	range_count = FIXNUM_MIN(remainder_count,
		G2int_gsi_collection_range_limit);
	if ( !FIXNUM_PLUSP(range_count))
	    goto end_loop_2;
	g2int_write_icp_byte(FIX((SI_Long)19L));
	g2int_write_icp_boolean(T);
	g2int_write_icp_resumable_sequence_element_type(g2_element_type);
	g2int_write_icp_fixnum(range_count);
	if ( !((SI_Long)-128L <= history_type && history_type <= 
		(SI_Long)127L))
	    g2int_gsi_connection_error(2,Qg2int_send_history_item,
		    G2int_gsi_invalid_history_type);
	else
	    switch ((char)history_type) {
	      case 1:
	      case 5:
		i = IFIX(FIXNUM_MINUS(history_length,remainder_count));
		ab_loop_repeat_ = IFIX(range_count);
		timestamp = 0.0;
		logical = Nil;
	      next_loop_3:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop_3;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		timestamp = DFLOAT_ISAREF_1(timestamps,i);
		logical = FIX(BYTE_32_ISAREF_1(values_1,i));
		g2int_write_icp_double_float_1(timestamp);
		g2int_write_icp_fixnum(logical);
		i = i + (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:;
		break;
	      case 6:
		i = IFIX(FIXNUM_MINUS(history_length,remainder_count));
		ab_loop_repeat_ = IFIX(range_count);
		timestamp = 0.0;
		float_1 = 0.0;
	      next_loop_4:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop_4;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		timestamp = DFLOAT_ISAREF_1(timestamps,i);
		float_1 = DFLOAT_ISAREF_1(values_1,i);
		g2int_write_icp_double_float_1(timestamp);
		g2int_write_icp_double_float_1(float_1);
		i = i + (SI_Long)1L;
		goto next_loop_4;
	      end_loop_4:;
		break;
	      case 4:
		i = IFIX(FIXNUM_MINUS(history_length,remainder_count));
		ab_loop_repeat_ = IFIX(range_count);
		timestamp = 0.0;
		string_1 = Nil;
	      next_loop_5:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop_5;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		timestamp = DFLOAT_ISAREF_1(timestamps,i);
		element = ISVREF(values_1,i);
		string_1 =  !TRUEP(element) ? (G2int_gsi_wide_api_p ? 
			array_constant_1 : string_constant_1) : 
			G2int_gsi_wide_api_p ? 
			inline_restore_lisp_text_string(element) : 
			inline_restore_lisp_gensym_string(element);
		g2int_write_icp_double_float_1(timestamp);
		copy_string_value_p = STRINGP(string_1);
		if (copy_string_value_p)
		    string_1 = 
			    g2int_gensym_string_to_wide_string_for_gsi(string_1);
		g2int_write_icp_text_string(string_1);
		if (copy_string_value_p)
		    g2int_reclaim_wide_string(string_1);
		i = i + (SI_Long)1L;
		goto next_loop_5;
	      end_loop_5:;
		break;
	      case 3:
		i = IFIX(FIXNUM_MINUS(history_length,remainder_count));
		ab_loop_repeat_ = IFIX(range_count);
		timestamp = 0.0;
		symbol = Nil;
	      next_loop_6:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop_6;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		timestamp = DFLOAT_ISAREF_1(timestamps,i);
		element = ISVREF(values_1,i);
		symbol = 
			g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			? element :  !TRUEP(element) ? Nil : 
			g2int_symbol_for_gsi_string(G2int_gsi_wide_api_p ? 
			g2int_c_wide_string_to_text_string(element) : 
			g2int_c_string_to_gensym_string(element));
		g2int_write_icp_double_float_1(timestamp);
		g2int_write_icp_possibly_interned_symbol(symbol,Nil);
		i = i + (SI_Long)1L;
		goto next_loop_6;
	      end_loop_6:;
		break;
	      default:
		g2int_gsi_connection_error(2,Qg2int_send_history_item,
			G2int_gsi_invalid_history_type);
		break;
	    }
	remainder_count = FIXNUM_MINUS(remainder_count,range_count);
	if (FIXNUM_PLUSP(remainder_count))
	    g2int_maybe_suspend_and_continue_building_object();
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(Nil);
}

/* GSI-PREFLIGHT-ITEM */
Object g2int_gsi_preflight_item(item,attribute_spec_qm)
    Object item, attribute_spec_qm;
{
    Object gsi_instance_extension, class_qm, type, name_qm, value_qm, count_1;
    Object temp, count_2, attributes, attribute, my_item;
    SI_Long i, ab_loop_bind_, second_new_value;

    x_note_fn_call(51,36);
    if (attribute_spec_qm && (EQ(CONSP(attribute_spec_qm) ? 
	    THIRD(attribute_spec_qm) : attribute_spec_qm,Qg2int_name) || 
	    EQ(CONSP(attribute_spec_qm) ? THIRD(attribute_spec_qm) : 
	    attribute_spec_qm,Qg2int_current_value)));
    else if (g2int_item_in_resumable_circularity_table_p(item))
	G2int_list_of_gsi_circular_references = g2int_gensym_cons_1(item,
		G2int_list_of_gsi_circular_references);
    else {
	g2int_put_item_in_resumable_circularity_table(item);
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	class_qm = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)2L) : Nil;
	type = FIX(IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L);
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	name_qm = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)4L) : Nil;
	value_qm = ISVREF(item,(SI_Long)2L);
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	count_1 = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)7L) : FIX((SI_Long)0L);
	if ( !TRUEP(value_qm))
	    type = FIX((SI_Long)0L);
	if (class_qm) {
	    temp = FIXNUM_ADD1(G2int_gsi_current_recursive_depth);
	    G2int_gsi_current_recursive_depth = temp;
	    if (name_qm) {
		temp = G2int_reusable_name_instance;
		SVREF(temp,FIX((SI_Long)2L)) = name_qm;
		g2int_gsi_preflight_item(G2int_reusable_name_instance,
			G2int_item_name_attribute_spec);
	    }
	    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	    count_2 = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)9L) : 
		    FIX((SI_Long)0L);
	    if ( !(IFIX(count_2) == (SI_Long)0L)) {
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		attributes = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
		i = IFIX(G2int_gsi_magic_offset);
		ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_2));
		attribute = Nil;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		attribute = ISVREF(attributes,i);
		if ( !((SI_Long)1L == ((SI_Long)1L & IFIX(ISVREF(attribute,
			(SI_Long)3L)))))
		    g2int_gsi_preflight_item(ISVREF(attribute,(SI_Long)4L),
			    ISVREF(attribute,(SI_Long)1L));
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	    if (FIXNUM_EQ(type,G2int_gsi_item_array_type_tag) || 
		    FIXNUM_EQ(type,G2int_gsi_item_or_value_array_type_tag)) {
		if ( !(IFIX(count_1) == (SI_Long)0L)) {
		    i = IFIX(G2int_gsi_magic_offset);
		    ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_1));
		    my_item = Nil;
		  next_loop_1:
		    if (i >= ab_loop_bind_)
			goto end_loop_1;
		    my_item = ISVREF(value_qm,i);
		    temp = G2int_array_element_attribute_spec;
		    second_new_value = i - (SI_Long)1L;
		    M_SECOND(temp) = FIX(second_new_value);
		    g2int_gsi_preflight_item(my_item,
			    G2int_array_element_attribute_spec);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:;
		}
	    }
	    if (FIXNUM_EQ(type,G2int_gsi_item_list_type_tag) || 
		    FIXNUM_EQ(type,G2int_gsi_item_or_value_list_type_tag)) {
		if ( !(IFIX(count_1) == (SI_Long)0L)) {
		    i = IFIX(G2int_gsi_magic_offset);
		    ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_1));
		    my_item = Nil;
		  next_loop_2:
		    if (i >= ab_loop_bind_)
			goto end_loop_2;
		    my_item = ISVREF(value_qm,i);
		    temp = G2int_list_element_attribute_spec;
		    second_new_value = i - (SI_Long)1L;
		    M_SECOND(temp) = FIX(second_new_value);
		    g2int_gsi_preflight_item(my_item,
			    G2int_list_element_attribute_spec);
		    i = i + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:;
		}
	    }
	    if (g2int_simple_value_type_p(type) && value_qm) {
		g2int_set_gsi_instance_value_type(G2int_reusable_value_instance,
			type);
		temp = G2int_reusable_value_instance;
		SVREF(temp,FIX((SI_Long)2L)) = value_qm;
		g2int_gsi_preflight_item(G2int_reusable_value_instance,
			G2int_simple_item_value_attribute_spec);
	    }
	    if (FIXNUM_GT(G2int_gsi_current_recursive_depth,
		    G2int_gsi_depth_of_last_transmission))
		G2int_gsi_depth_of_last_transmission = 
			G2int_gsi_current_recursive_depth;
	    temp = FIXNUM_SUB1(G2int_gsi_current_recursive_depth);
	    G2int_gsi_current_recursive_depth = temp;
	}
    }
    return VALUES_1(Nil);
}

static Object Qab_g2int_gsi_send_item;  /* gsi_send_item */

/* GSI-SEND-ITEM */
Object g2int_gsi_send_item(item,attribute_spec_qm)
    Object item, attribute_spec_qm;
{
    Object object_index_qm, value_type, gsi_instance_extension, history_qm;
    Object temp, element_count, element_type_symbol, remainder_count;
    Object range_count, elements, element, converted_value, temp_2, class_qm;
    Object type, name_qm, value_qm, count_1, temp_3, count_2, attributes;
    Object attribute, my_item;
    SI_Long i, temp_1, ab_loop_bind_, second_new_value;
    char copy_string_value_p;

    x_note_fn_call(51,37);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_closed))
	return VALUES_1(Nil);
    object_index_qm = g2int_item_in_resumable_circularity_table_p(item);
    value_type = FIX(IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L);
    if ( !TRUEP(ISVREF(item,(SI_Long)2L)))
	value_type = FIX((SI_Long)0L);
    if (object_index_qm)
	g2int_write_icp_add_circular_attribute(attribute_spec_qm,
		object_index_qm);
    else {
	if (FIXNUM_LT(G2int_gsi_current_recursive_depth,
		G2int_gsi_depth_of_last_transmission)) {
	    g2int_write_icp_ascend_to_parent(FIXNUM_MINUS(G2int_gsi_depth_of_last_transmission,
		    G2int_gsi_current_recursive_depth));
	    G2int_gsi_depth_of_last_transmission = 
		    G2int_gsi_current_recursive_depth;
	}
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	if ( !(gsi_instance_extension ? 
		TRUEP(ISVREF(gsi_instance_extension,(SI_Long)2L)) : 
		TRUEP(Nil)))
	    g2int_write_icp_add_attribute_value(attribute_spec_qm,item,Nil);
	else if (! !(FIXNUMP(value_type) && FIXNUM_LE(FIX((SI_Long)-128L),
		value_type) && FIXNUM_LE(value_type,FIX((SI_Long)127L))))
	    switch (INTEGER_TO_CHAR(value_type)) {
	      case 1:
	      case 5:
	      case 3:
	      case 4:
	      case 6:
	      case 0:
	      case 7:
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		history_qm = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)12L) : Nil;
		if (history_qm) {
		    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		    temp = gsi_instance_extension ? 
			    ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		    g2int_gsi_send_history_item(attribute_spec_qm,temp,
			    gsi_instance_extension ? 
			    ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			    FIX((SI_Long)0L),item);
		}
		else {
		    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		    temp = gsi_instance_extension ? 
			    ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		    g2int_write_icp_add_attribute_object(attribute_spec_qm,
			    temp,Nil,gsi_instance_extension ? 
			    ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			    FIX((SI_Long)0L));
		}
		break;
	      case 17:
	      case 22:
	      case 21:
	      case 20:
	      case 19:
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		element_count = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L);
		element_type_symbol = 
			g2int_g2_element_type_from_gsi_collection_type(value_type);
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		g2int_write_icp_add_attribute_value_vector(attribute_spec_qm,
			temp,Nil,gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L),element_type_symbol,element_count);
		remainder_count = element_count;
		range_count = Nil;
	      next_loop:
		range_count = FIXNUM_MIN(remainder_count,
			G2int_gsi_collection_range_limit);
		if ( !FIXNUM_PLUSP(range_count))
		    goto end_loop;
		g2int_write_icp_byte(FIX((SI_Long)14L));
		g2int_write_icp_fixnum(range_count);
		g2int_write_icp_resumable_sequence_element_type(element_type_symbol);
		g2int_write_icp_fixnum(FIXNUM_SUB1(remainder_count));
		elements = ISVREF(item,(SI_Long)2L);
		i = IFIX(FIXNUM_SUB1(remainder_count));
		temp_1 = IFIX(FIXNUM_MINUS(remainder_count,
			G2int_gsi_collection_range_limit));
		ab_loop_bind_ = MAX((SI_Long)0L,temp_1);
	      next_loop_1:
		if (i < ab_loop_bind_)
		    goto end_loop_1;
		if (EQ(element_type_symbol,Qinteger) || 
			EQ(element_type_symbol,Qg2int_truth))
		    g2int_write_icp_fixnum(FIX(BYTE_32_ISAREF_1(elements,i)));
		else if (EQ(element_type_symbol,Qg2int_float))
		    g2int_write_icp_double_float_1(DFLOAT_ISAREF_1(elements,
			    i));
		else if (EQ(element_type_symbol,Qsymbol)) {
		    element = ISVREF(elements,i);
		    g2int_write_icp_possibly_interned_symbol(g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			    ? element :  !TRUEP(element) ? Nil : 
			    g2int_symbol_for_gsi_string(G2int_gsi_wide_api_p 
			    ? g2int_c_wide_string_to_text_string(element) :
			     g2int_c_string_to_gensym_string(element)),Nil);
		}
		else if (EQ(element_type_symbol,Qg2int_text)) {
		    element = ISVREF(elements,i);
		    converted_value =  !TRUEP(element) ? 
			    (G2int_gsi_wide_api_p ? array_constant_1 : 
			    string_constant_1) : G2int_gsi_wide_api_p ? 
			    inline_restore_lisp_text_string(element) : 
			    inline_restore_lisp_gensym_string(element);
		    copy_string_value_p = STRINGP(converted_value);
		    if (copy_string_value_p)
			converted_value = 
				g2int_gensym_string_to_wide_string_for_gsi(converted_value);
		    g2int_write_icp_text_string(converted_value);
		    if (copy_string_value_p)
			g2int_reclaim_wide_string(converted_value);
		}
		i = i - (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
		remainder_count = FIXNUM_MINUS(remainder_count,range_count);
		if (FIXNUM_PLUSP(remainder_count))
		    g2int_maybe_suspend_and_continue_building_object();
		goto next_loop;
	      end_loop:;
		break;
	      case 24:
	      case 26:
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		element_count = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L);
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		g2int_write_icp_add_attribute_value_vector(attribute_spec_qm,
			temp,Nil,gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L),Nil,element_count);
		remainder_count = element_count;
		range_count = Nil;
	      next_loop_2:
		range_count = FIXNUM_MIN(remainder_count,
			G2int_gsi_collection_range_limit);
		if ( !FIXNUM_PLUSP(range_count))
		    goto end_loop_2;
		g2int_write_icp_byte(FIX((SI_Long)8L));
		g2int_write_icp_fixnum(range_count);
		g2int_write_icp_fixnum(FIXNUM_SUB1(remainder_count));
		elements = ISVREF(item,(SI_Long)2L);
		i = IFIX(FIXNUM_SUB1(remainder_count));
		temp_1 = IFIX(FIXNUM_MINUS(remainder_count,
			G2int_gsi_collection_range_limit));
		ab_loop_bind_ = MAX((SI_Long)0L,temp_1);
	      next_loop_3:
		if (i < ab_loop_bind_)
		    goto end_loop_3;
		g2int_write_icp_attribute_value(ISVREF(elements,i + 
			(SI_Long)1L),Nil);
		i = i - (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:;
		remainder_count = FIXNUM_MINUS(remainder_count,range_count);
		if (FIXNUM_PLUSP(remainder_count))
		    g2int_maybe_suspend_and_continue_building_object();
		goto next_loop_2;
	      end_loop_2:;
		break;
	      case 23:
	      case 25:
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp_2 = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L);
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		g2int_write_icp_add_attribute_object_vector(attribute_spec_qm,
			temp,Nil,temp_2,gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L));
		break;
	      case 33:
	      case 38:
	      case 37:
	      case 36:
	      case 35:
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		element_count = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L);
		element_type_symbol = 
			g2int_g2_element_type_from_gsi_collection_type(value_type);
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		g2int_write_icp_add_attribute_value_list(attribute_spec_qm,
			temp,Nil,gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L),element_type_symbol,element_count);
		remainder_count = element_count;
		range_count = Nil;
	      next_loop_4:
		range_count = FIXNUM_MIN(remainder_count,
			G2int_gsi_collection_range_limit);
		if ( !FIXNUM_PLUSP(range_count))
		    goto end_loop_4;
		g2int_write_icp_byte(FIX((SI_Long)15L));
		g2int_write_icp_fixnum(range_count);
		g2int_write_icp_resumable_sequence_element_type(element_type_symbol);
		elements = ISVREF(item,(SI_Long)2L);
		i = IFIX(FIXNUM_MINUS(element_count,remainder_count));
		ab_loop_bind_ = IFIX(FIXNUM_ADD(range_count,
			FIXNUM_MINUS(element_count,remainder_count)));
	      next_loop_5:
		if (i >= ab_loop_bind_)
		    goto end_loop_5;
		if (EQ(element_type_symbol,Qinteger) || 
			EQ(element_type_symbol,Qg2int_truth))
		    g2int_write_icp_fixnum(FIX(BYTE_32_ISAREF_1(elements,i)));
		else if (EQ(element_type_symbol,Qg2int_float))
		    g2int_write_icp_double_float_1(DFLOAT_ISAREF_1(elements,
			    i));
		else if (EQ(element_type_symbol,Qsymbol)) {
		    element = ISVREF(elements,i);
		    g2int_write_icp_possibly_interned_symbol(g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			    ? element :  !TRUEP(element) ? Nil : 
			    g2int_symbol_for_gsi_string(G2int_gsi_wide_api_p 
			    ? g2int_c_wide_string_to_text_string(element) :
			     g2int_c_string_to_gensym_string(element)),Nil);
		}
		else if (EQ(element_type_symbol,Qg2int_text)) {
		    element = ISVREF(elements,i);
		    converted_value =  !TRUEP(element) ? 
			    (G2int_gsi_wide_api_p ? array_constant_1 : 
			    string_constant_1) : G2int_gsi_wide_api_p ? 
			    inline_restore_lisp_text_string(element) : 
			    inline_restore_lisp_gensym_string(element);
		    copy_string_value_p = STRINGP(converted_value);
		    if (copy_string_value_p)
			converted_value = 
				g2int_gensym_string_to_wide_string_for_gsi(converted_value);
		    g2int_write_icp_text_string(converted_value);
		    if (copy_string_value_p)
			g2int_reclaim_wide_string(converted_value);
		}
		i = i + (SI_Long)1L;
		goto next_loop_5;
	      end_loop_5:;
		remainder_count = FIXNUM_MINUS(remainder_count,range_count);
		if (FIXNUM_PLUSP(remainder_count))
		    g2int_maybe_suspend_and_continue_building_object();
		goto next_loop_4;
	      end_loop_4:;
		break;
	      case 40:
	      case 42:
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		element_count = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L);
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		g2int_write_icp_add_attribute_value_list(attribute_spec_qm,
			temp,Nil,gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L),Nil,element_count);
		remainder_count = element_count;
		range_count = Nil;
	      next_loop_6:
		range_count = FIXNUM_MIN(remainder_count,
			G2int_gsi_collection_range_limit);
		if ( !FIXNUM_PLUSP(range_count))
		    goto end_loop_6;
		g2int_write_icp_byte(FIX((SI_Long)9L));
		g2int_write_icp_fixnum(range_count);
		elements = ISVREF(item,(SI_Long)2L);
		i = IFIX(FIXNUM_MINUS(element_count,remainder_count));
		ab_loop_bind_ = IFIX(FIXNUM_ADD(range_count,
			FIXNUM_MINUS(element_count,remainder_count)));
	      next_loop_7:
		if (i >= ab_loop_bind_)
		    goto end_loop_7;
		g2int_write_icp_attribute_value(ISVREF(elements,i + 
			(SI_Long)1L),Nil);
		i = i + (SI_Long)1L;
		goto next_loop_7;
	      end_loop_7:;
		remainder_count = FIXNUM_MINUS(remainder_count,range_count);
		if (FIXNUM_PLUSP(remainder_count))
		    g2int_maybe_suspend_and_continue_building_object();
		goto next_loop_6;
	      end_loop_6:;
		break;
	      case 39:
	      case 41:
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		temp_2 = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L);
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		g2int_write_icp_add_attribute_object_list(attribute_spec_qm,
			temp,Nil,temp_2,gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)7L) : 
			FIX((SI_Long)0L));
		break;
	      default:
		break;
	    }
	if (EQ(item,FIRST(G2int_list_of_gsi_circular_references)))
	    g2int_gsi_connection_error(2,Qab_g2int_gsi_send_item,
		    G2int_gsi_circularity_not_supported);
    }
    if (FIXNUM_NE(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_closed)) {
	g2int_maybe_suspend_and_continue_building_object();
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	class_qm = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)2L) : Nil;
	type = FIX(IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L);
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	name_qm = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)4L) : Nil;
	value_qm = ISVREF(item,(SI_Long)2L);
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	count_1 = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)7L) : FIX((SI_Long)0L);
	if ( !TRUEP(value_qm))
	    type = FIX((SI_Long)0L);
	if (class_qm) {
	    temp_3 = FIXNUM_ADD1(G2int_gsi_current_recursive_depth);
	    G2int_gsi_current_recursive_depth = temp_3;
	    if (name_qm) {
		temp_3 = G2int_reusable_name_instance;
		SVREF(temp_3,FIX((SI_Long)2L)) = name_qm;
		g2int_gsi_send_item(G2int_reusable_name_instance,
			G2int_item_name_attribute_spec);
	    }
	    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	    count_2 = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)9L) : 
		    FIX((SI_Long)0L);
	    if ( !(IFIX(count_2) == (SI_Long)0L)) {
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		attributes = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
		i = IFIX(G2int_gsi_magic_offset);
		ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_2));
		attribute = Nil;
	      next_loop_8:
		if (i >= ab_loop_bind_)
		    goto end_loop_8;
		attribute = ISVREF(attributes,i);
		if ( !((SI_Long)1L == ((SI_Long)1L & IFIX(ISVREF(attribute,
			(SI_Long)3L)))))
		    g2int_gsi_send_item(ISVREF(attribute,(SI_Long)4L),
			    ISVREF(attribute,(SI_Long)1L));
		i = i + (SI_Long)1L;
		goto next_loop_8;
	      end_loop_8:;
	    }
	    if (FIXNUM_EQ(type,G2int_gsi_item_array_type_tag) || 
		    FIXNUM_EQ(type,G2int_gsi_item_or_value_array_type_tag)) {
		if ( !(IFIX(count_1) == (SI_Long)0L)) {
		    i = IFIX(G2int_gsi_magic_offset);
		    ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_1));
		    my_item = Nil;
		  next_loop_9:
		    if (i >= ab_loop_bind_)
			goto end_loop_9;
		    my_item = ISVREF(value_qm,i);
		    temp_3 = G2int_array_element_attribute_spec;
		    second_new_value = i - (SI_Long)1L;
		    M_SECOND(temp_3) = FIX(second_new_value);
		    g2int_gsi_send_item(my_item,
			    G2int_array_element_attribute_spec);
		    i = i + (SI_Long)1L;
		    goto next_loop_9;
		  end_loop_9:;
		}
	    }
	    if (FIXNUM_EQ(type,G2int_gsi_item_list_type_tag) || 
		    FIXNUM_EQ(type,G2int_gsi_item_or_value_list_type_tag)) {
		if ( !(IFIX(count_1) == (SI_Long)0L)) {
		    i = IFIX(G2int_gsi_magic_offset);
		    ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_1));
		    my_item = Nil;
		  next_loop_10:
		    if (i >= ab_loop_bind_)
			goto end_loop_10;
		    my_item = ISVREF(value_qm,i);
		    temp_3 = G2int_list_element_attribute_spec;
		    second_new_value = i - (SI_Long)1L;
		    M_SECOND(temp_3) = FIX(second_new_value);
		    g2int_gsi_send_item(my_item,
			    G2int_list_element_attribute_spec);
		    i = i + (SI_Long)1L;
		    goto next_loop_10;
		  end_loop_10:;
		}
	    }
	    if (g2int_simple_value_type_p(type) && value_qm) {
		g2int_set_gsi_instance_value_type(G2int_reusable_value_instance,
			type);
		temp_3 = G2int_reusable_value_instance;
		SVREF(temp_3,FIX((SI_Long)2L)) = value_qm;
		g2int_gsi_send_item(G2int_reusable_value_instance,
			G2int_simple_item_value_attribute_spec);
	    }
	    if (FIXNUM_GT(G2int_gsi_current_recursive_depth,
		    G2int_gsi_depth_of_last_transmission))
		G2int_gsi_depth_of_last_transmission = 
			G2int_gsi_current_recursive_depth;
	    temp_3 = FIXNUM_SUB1(G2int_gsi_current_recursive_depth);
	    G2int_gsi_current_recursive_depth = temp_3;
	}
	if (FIXNUM_NE(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
		G2int_icp_connection_closed)) {
	    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	    class_qm = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
	    type = FIX(IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L);
	    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	    name_qm = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)4L) : Nil;
	    value_qm = ISVREF(item,(SI_Long)2L);
	    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	    count_1 = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)7L) : 
		    FIX((SI_Long)0L);
	    if ( !TRUEP(value_qm))
		type = FIX((SI_Long)0L);
	    if (class_qm) {
		temp_3 = FIXNUM_ADD1(G2int_gsi_current_recursive_depth);
		G2int_gsi_current_recursive_depth = temp_3;
		if (name_qm) {
		    temp_3 = G2int_reusable_name_instance;
		    SVREF(temp_3,FIX((SI_Long)2L)) = name_qm;
		    g2int_gsi_send_item(G2int_reusable_name_instance,
			    G2int_item_name_attribute_spec);
		}
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		count_2 = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L);
		if ( !(IFIX(count_2) == (SI_Long)0L)) {
		    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		    attributes = gsi_instance_extension ? 
			    ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
		    i = IFIX(G2int_gsi_magic_offset);
		    ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_2));
		    attribute = Nil;
		  next_loop_11:
		    if (i >= ab_loop_bind_)
			goto end_loop_11;
		    attribute = ISVREF(attributes,i);
		    if ( !((SI_Long)1L == ((SI_Long)1L & 
			    IFIX(ISVREF(attribute,(SI_Long)3L)))))
			g2int_gsi_send_item(ISVREF(attribute,(SI_Long)4L),
				ISVREF(attribute,(SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_11;
		  end_loop_11:;
		}
		if (FIXNUM_EQ(type,G2int_gsi_item_array_type_tag) || 
			FIXNUM_EQ(type,
			    G2int_gsi_item_or_value_array_type_tag)) {
		    if ( !(IFIX(count_1) == (SI_Long)0L)) {
			i = IFIX(G2int_gsi_magic_offset);
			ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_1));
			my_item = Nil;
		      next_loop_12:
			if (i >= ab_loop_bind_)
			    goto end_loop_12;
			my_item = ISVREF(value_qm,i);
			temp_3 = G2int_array_element_attribute_spec;
			second_new_value = i - (SI_Long)1L;
			M_SECOND(temp_3) = FIX(second_new_value);
			g2int_gsi_send_item(my_item,
				G2int_array_element_attribute_spec);
			i = i + (SI_Long)1L;
			goto next_loop_12;
		      end_loop_12:;
		    }
		}
		if (FIXNUM_EQ(type,G2int_gsi_item_list_type_tag) || 
			FIXNUM_EQ(type,
			    G2int_gsi_item_or_value_list_type_tag)) {
		    if ( !(IFIX(count_1) == (SI_Long)0L)) {
			i = IFIX(G2int_gsi_magic_offset);
			ab_loop_bind_ = IFIX(FIXNUM_ADD1(count_1));
			my_item = Nil;
		      next_loop_13:
			if (i >= ab_loop_bind_)
			    goto end_loop_13;
			my_item = ISVREF(value_qm,i);
			temp_3 = G2int_list_element_attribute_spec;
			second_new_value = i - (SI_Long)1L;
			M_SECOND(temp_3) = FIX(second_new_value);
			g2int_gsi_send_item(my_item,
				G2int_list_element_attribute_spec);
			i = i + (SI_Long)1L;
			goto next_loop_13;
		      end_loop_13:;
		    }
		}
		if (g2int_simple_value_type_p(type) && value_qm) {
		    g2int_set_gsi_instance_value_type(G2int_reusable_value_instance,
			    type);
		    temp_3 = G2int_reusable_value_instance;
		    SVREF(temp_3,FIX((SI_Long)2L)) = value_qm;
		    g2int_gsi_send_item(G2int_reusable_value_instance,
			    G2int_simple_item_value_attribute_spec);
		}
		if (FIXNUM_GT(G2int_gsi_current_recursive_depth,
			G2int_gsi_depth_of_last_transmission))
		    G2int_gsi_depth_of_last_transmission = 
			    G2int_gsi_current_recursive_depth;
		temp_3 = FIXNUM_SUB1(G2int_gsi_current_recursive_depth);
		G2int_gsi_current_recursive_depth = temp_3;
	    }
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_gsi_instance_g2_struct;  /* g2-defstruct-structure-name::gsi-instance-g2-struct */

static Object Qg2int_write_item_argument;  /* write_item_argument */

/* FLUSH-OUTGOING-ITEM-LIST */
Object g2int_flush_outgoing_item_list(icp_socket)
    Object icp_socket;
{
    Object extension_data, item, gsi_current_resumable_item, gensym_pop_store;
    Object cons_1, next_cons, cdr_new_value, current_icp_port;
    Object current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, gsi_instance_extension;
    double gensymed_symbol_1;
    Declare_special(13);

    x_note_fn_call(51,38);
    if (FIXNUM_NE(ISVREF(icp_socket,(SI_Long)15L),
		G2int_icp_connection_closed)) {
	extension_data = ISVREF(icp_socket,(SI_Long)29L);
	item = Nil;
	gsi_current_resumable_item = Nil;
	PUSH_SPECIAL(G2int_gsi_current_resumable_item,gsi_current_resumable_item,
		12);
	next_loop:
	  gensym_pop_store = Nil;
	  cons_1 = ISVREF(extension_data,(SI_Long)5L);
	  if (cons_1) {
	      gensym_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	      cdr_new_value = G2int_available_gensym_conses;
	      M_CDR(cons_1) = cdr_new_value;
	      G2int_available_gensym_conses = cons_1;
	  }
	  else
	      next_cons = Nil;
	  SVREF(extension_data,FIX((SI_Long)5L)) = next_cons;
	  item = gensym_pop_store;
	  if ( !TRUEP(item))
	      goto end_loop;
	  if ( !FIXNUM_NE(ISVREF(icp_socket,(SI_Long)15L),
		  G2int_icp_connection_closed))
	      goto end_loop;
	  G2int_gsi_current_resumable_item = item;
	  if ( !(SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		  Qg2_defstruct_structure_name_gsi_instance_g2_struct)))
	      g2int_gsi_connection_error(2,Qg2int_write_item_argument,
		      G2int_gsi_incompatible_structure);
	  g2int_gsi_prepare_for_recursive_descent();
	  g2int_gsi_preflight_item(item,Nil);
	  current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	  PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
	    current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	      temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		      >= (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		      (SI_Long)53L) : Nil;
	      if (temp);
	      else
		  temp = Nil;
	      disable_resumability = temp;
	      PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,9);
		number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			8);
		  icp_buffers_for_message_group = Nil;
		  PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			  7);
		    icp_buffer_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
			    6);
		      icp_byte_position_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			      5);
			number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
			PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				4);
			  current_icp_buffer = Nil;
			  PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				  3);
			    current_write_icp_byte_position = Nil;
			    PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
				    2);
			      number_of_icp_bytes_in_message_group = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				      1);
				writing_icp_message_group = 
					FIXNUM_ADD1(G2int_writing_icp_message_group);
				PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
					0);
				  gensymed_symbol = Nil;
				  gensymed_symbol_1 = 0.0;
				  gensymed_symbol_1 = 0.0;
				  if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					  &&  
					  !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					      {
				      g2int_send_icp_continue_building_resumable_object(item);
				      g2int_gsi_prepare_for_recursive_descent();
				      g2int_gsi_send_item(item,Nil);
				      if (FIXNUM_NE(ISVREF(icp_socket,
					      (SI_Long)15L),
					      G2int_icp_connection_closed))
					  g2int_write_icp_finish_building_object(FIX((SI_Long)0L));
				      g2int_end_icp_message_group();
				  }
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
		  G2int_icp_connection_closed)) {
	      gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	      g2int_reclaim_gensym_list_1(gsi_instance_extension ? 
		      ISVREF(gsi_instance_extension,(SI_Long)13L) : Nil);
	      gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(item,FIX((SI_Long)3L)) = gsi_instance_extension;
	      }
	      SVREF(gsi_instance_extension,FIX((SI_Long)13L)) = Nil;
	  }
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qg2int_gsi_instance_squirrelled_index;  /* gsi-instance-squirrelled-index */

/* ESTABLISH-NEW-OBJECT-INDICES-AS-REQUIRED */
Object g2int_establish_new_object_indices_as_required(arguments)
    Object arguments;
{
    Object actual_size, value_or_object, gsi_instance_extension;
    Object get_gsi_instance_plist_value_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(51,39);
    actual_size = G2int_rpc_argument_count_overrideqm;
    if (actual_size);
    else
	actual_size = arguments ? 
		FIXNUM_SUB1(g2int_gsi_managed_array_length(arguments)) : 
		FIX((SI_Long)0L);
    i = IFIX(G2int_gsi_magic_offset);
    ab_loop_bind_ = IFIX(actual_size);
    value_or_object = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    value_or_object = ISVREF(arguments,i);
    gsi_instance_extension = ISVREF(value_or_object,(SI_Long)3L);
    if (gsi_instance_extension ? TRUEP(ISVREF(gsi_instance_extension,
	    (SI_Long)2L)) : TRUEP(Nil)) {
	get_gsi_instance_plist_value_new_value = 
		g2int_establish_new_object_index_for_gsi_instance(2,
		value_or_object,ISVREF(G2int_current_icp_socket,(SI_Long)4L));
	g2int_set_gsi_instance_plist_value(value_or_object,
		Qg2int_gsi_instance_squirrelled_index,
		get_gsi_instance_plist_value_new_value);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

void gsi_rpc2_INIT()
{
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant;
    Object Qg2int_utilities2;
    Object Qg2int_count_of_gsi_circularity_table_hash_vector_43_vectors;
    Object Qg2int_available_gsi_circularity_table_hash_vector_43_vectors;

    x_note_fn_call(51,40);
    SET_PACKAGE("AB");
    G2int_gsi_maximum_number_of_icp_bytes_to_buffer = FIX((SI_Long)4000L);
    G2int_gsi_collection_range_limit = FIX((SI_Long)1000L);
    if (G2int_gsi_current_resumable_item == UNBOUND)
	G2int_gsi_current_resumable_item = Nil;
    if (G2int_list_of_gsi_circular_references == UNBOUND)
	G2int_list_of_gsi_circular_references = Nil;
    if (G2int_gsi_current_recursive_depth == UNBOUND)
	G2int_gsi_current_recursive_depth = Nil;
    if (G2int_gsi_depth_of_last_transmission == UNBOUND)
	G2int_gsi_depth_of_last_transmission = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_available_gsi_circularity_table_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-GSI-CIRCULARITY-TABLE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_available_gsi_circularity_table_hash_vector_43_vectors,
	    G2int_available_gsi_circularity_table_hash_vector_43_vectors);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_available_gsi_circularity_table_hash_vector_43_vectors,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_count_of_gsi_circularity_table_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-GSI-CIRCULARITY-TABLE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_gsi_circularity_table_hash_vector_43_vectors,
	    G2int_count_of_gsi_circularity_table_hash_vector_43_vectors);
    g2int_record_system_variable(Qg2int_count_of_gsi_circularity_table_hash_vector_43_vectors,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_gsi_circularity_table_tree_for_hash = 
	    STATIC_SYMBOL("GSI-CIRCULARITY-TABLE-TREE-FOR-HASH",AB_package);
    Qg2int_managed_array = STATIC_SYMBOL("MANAGED-ARRAY",AB_package);
    Qg2int_simple_integer_vector = STATIC_SYMBOL("SIMPLE-INTEGER-VECTOR",
	    AB_package);
    Qg2int_simple_float_array = STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY",AB_package);
    Qg2int_managed_string_array = STATIC_SYMBOL("MANAGED-STRING-ARRAY",
	    AB_package);
    Qg2int_attribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qg2int_gsi_superior_item = STATIC_SYMBOL("GSI-SUPERIOR-ITEM",AB_package);
    Qg2int_vector_element = STATIC_SYMBOL("VECTOR-ELEMENT",AB_package);
    Qg2int_list_element = STATIC_SYMBOL("LIST-ELEMENT",AB_package);
    Qg2int_long = STATIC_SYMBOL("LONG",AB_package);
    Qg2int_float = STATIC_SYMBOL("float",AB_package);
    Qg2int_text = STATIC_SYMBOL("TEXT",AB_package);
    Qg2int_truth = STATIC_SYMBOL("TRUTH",AB_package);
    Qg2int_g2_element_type_from_gsi_type = 
	    STATIC_SYMBOL("G2-ELEMENT-TYPE-FROM-GSI-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_g2_element_type_from_gsi_type,
	    STATIC_FUNCTION(g2int_g2_element_type_from_gsi_type,NIL,FALSE,
	    1,1));
    Qg2int_name = STATIC_SYMBOL("NAME",AB_package);
    Qg2int_current_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    Qg2int_gsi_receive_add_homogeneous_history_range = 
	    STATIC_SYMBOL("GSI-RECEIVE-ADD-HOMOGENEOUS-HISTORY-RANGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_gsi_receive_add_homogeneous_history_range,
	    STATIC_FUNCTION(g2int_gsi_receive_add_homogeneous_history_range,
	    NIL,FALSE,3,3));
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant = STATIC_STRING("::");
    Qg2int_send_history_item = STATIC_SYMBOL("SEND_HISTORY_ITEM",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant_1 = STATIC_STRING("");
    Qab_g2int_gsi_send_item = STATIC_SYMBOL("GSI_SEND_ITEM",AB_package);
    Qg2_defstruct_structure_name_gsi_instance_g2_struct = 
	    STATIC_SYMBOL("GSI-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_write_item_argument = STATIC_SYMBOL("WRITE_ITEM_ARGUMENT",
	    AB_package);
    Qg2int_gsi_instance_squirrelled_index = 
	    STATIC_SYMBOL("GSI-INSTANCE-SQUIRRELLED-INDEX",AB_package);
}
