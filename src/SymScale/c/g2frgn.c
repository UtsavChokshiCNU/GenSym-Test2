/* g2frgn.c
 * Input file:  g2-foreign.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2frgn.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_foreign_function_registry_internal_hash_vector_131_vectors, Qavailable_foreign_function_registry_internal_hash_vector_131_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_foreign_function_registry_internal_hash_vector_131_vectors, Qcount_of_foreign_function_registry_internal_hash_vector_131_vectors);

Object Available_foreign_function_registry_internal_hash_vector_131_vectors_vector = UNBOUND;

/* FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR-131-VECTOR-MEMORY-USAGE */
Object foreign_function_registry_internal_hash_vector_131_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(214,0);
    temp = Count_of_foreign_function_registry_internal_hash_vector_131_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)131L)));
    return VALUES_1(temp);
}

/* OUT-FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR-131-VECTORS */
Object out_foreign_function_registry_internal_hash_vector_131_vectors()
{
    Object temp;

    x_note_fn_call(214,1);
    temp = 
	    FIXNUM_MINUS(Count_of_foreign_function_registry_internal_hash_vector_131_vectors,
	    length(Available_foreign_function_registry_internal_hash_vector_131_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR-131-VECTOR-INTERNAL */
Object make_permanent_foreign_function_registry_internal_hash_vector_131_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(214,2);
    atomic_incff_symval(Qcount_of_foreign_function_registry_internal_hash_vector_131_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)131L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR */
Object make_foreign_function_registry_internal_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(214,3);
    if (ISVREF(Available_foreign_function_registry_internal_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_foreign_function_registry_internal_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_foreign_function_registry_internal_hash_vector_131_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_foreign_function_registry_internal_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_foreign_function_registry_internal_hash_vector_131_vectors_vector,
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
		make_permanent_foreign_function_registry_internal_hash_vector_131_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR */
Object reclaim_foreign_function_registry_internal_hash_vector(foreign_function_registry_internal_hash_vector_131_vector)
    Object foreign_function_registry_internal_hash_vector_131_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(214,4);
    svref_arg_1 = 
	    Available_foreign_function_registry_internal_hash_vector_131_vectors_vector;
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
	    foreign_function_registry_internal_hash_vector_131_vector;
    temp = 
	    ISVREF(Available_foreign_function_registry_internal_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-FOREIGN-FUNCTION-REGISTRY-INTERNAL-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_foreign_function_registry_internal_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(214,5);
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

/* RECLAIM-FOREIGN-FUNCTION-REGISTRY-INTERNAL-TREE-FOR-HASH-NODES */
Object reclaim_foreign_function_registry_internal_tree_for_hash_nodes(foreign_function_registry_internal_tree_for_hash_skip_list,
	    tail)
    Object foreign_function_registry_internal_tree_for_hash_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(214,6);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(foreign_function_registry_internal_tree_for_hash_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(foreign_function_registry_internal_tree_for_hash_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = 
	    ISVREF(foreign_function_registry_internal_tree_for_hash_skip_list,
	    (SI_Long)2L);
    entry = 
	    ISVREF(foreign_function_registry_internal_tree_for_hash_skip_list,
	    (SI_Long)3L);
    reclaim_skip_list_element(foreign_function_registry_internal_tree_for_hash_skip_list);
    foreign_function_registry_internal_tree_for_hash_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-FOREIGN-FUNCTION-REGISTRY-INTERNAL-TREE */
Object clear_foreign_function_registry_internal_tree(foreign_function_registry_internal_tree_for_hash_skip_list)
    Object foreign_function_registry_internal_tree_for_hash_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(214,7);
    head = 
	    M_CAR(M_CDR(foreign_function_registry_internal_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(foreign_function_registry_internal_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_foreign_function_registry_internal_tree_for_hash_nodes(element_qm,
		tail);
    return VALUES_1(foreign_function_registry_internal_tree_for_hash_skip_list);
}

static Object Qforeign_function_registry_internal_tree_for_hash;  /* foreign-function-registry-internal-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-FOREIGN-FUNCTION-REGISTRY */
Object make_foreign_function_registry()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(214,8);
    new_vector = make_foreign_function_registry_internal_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    tail = 
	    make_foreign_function_registry_internal_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_foreign_function_registry_internal_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qforeign_function_registry_internal_tree_for_hash;
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

/* FLATTEN-FOREIGN-FUNCTION-REGISTRY-INTERNAL */
Object flatten_foreign_function_registry_internal(foreign_function_registry_internal_hash_table)
    Object foreign_function_registry_internal_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(214,9);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    subtree = ISVREF(foreign_function_registry_internal_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-FOREIGN-FUNCTION-REGISTRY-INTERNAL */
Object clear_foreign_function_registry_internal(foreign_function_registry_internal_hash_table)
    Object foreign_function_registry_internal_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(214,10);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    clear_foreign_function_registry_internal_tree(ISVREF(foreign_function_registry_internal_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-FOREIGN-FUNCTION-REGISTRY-INTERNAL */
Object reclaim_foreign_function_registry_internal(foreign_function_registry_internal_hash_table)
    Object foreign_function_registry_internal_hash_table;
{
    Object foreign_function_registry_internal_tree_for_hash_skip_list, head;
    Object tail, element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(214,11);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    foreign_function_registry_internal_tree_for_hash_skip_list = 
	    ISVREF(foreign_function_registry_internal_hash_table,index_1);
    head = 
	    M_CAR(M_CDR(foreign_function_registry_internal_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(foreign_function_registry_internal_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_foreign_function_registry_internal_tree_for_hash_nodes(element_qm,
		tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(foreign_function_registry_internal_tree_for_hash_skip_list) = Nil;
    M_CADR(foreign_function_registry_internal_tree_for_hash_skip_list) = Nil;
    M_CAR(foreign_function_registry_internal_tree_for_hash_skip_list) = Nil;
    if (foreign_function_registry_internal_tree_for_hash_skip_list) {
	last_1 = foreign_function_registry_internal_tree_for_hash_skip_list;
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
		    foreign_function_registry_internal_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    foreign_function_registry_internal_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(foreign_function_registry_internal_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_foreign_function_registry_internal_hash_vector(foreign_function_registry_internal_hash_table);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_function_registry, Qforeign_function_registry);

Object The_type_description_of_element_of_foreign_linking_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_element_of_foreign_linking_infos, Qchain_of_available_element_of_foreign_linking_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Element_of_foreign_linking_info_count, Qelement_of_foreign_linking_info_count);

Object Chain_of_available_element_of_foreign_linking_infos_vector = UNBOUND;

/* ELEMENT-OF-FOREIGN-LINKING-INFO-STRUCTURE-MEMORY-USAGE */
Object element_of_foreign_linking_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,12);
    temp = Element_of_foreign_linking_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ELEMENT-OF-FOREIGN-LINKING-INFO-COUNT */
Object outstanding_element_of_foreign_linking_info_count()
{
    Object def_structure_element_of_foreign_linking_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,13);
    gensymed_symbol = IFIX(Element_of_foreign_linking_info_count);
    def_structure_element_of_foreign_linking_info_variable = 
	    Chain_of_available_element_of_foreign_linking_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_element_of_foreign_linking_info_variable))
	goto end_loop;
    def_structure_element_of_foreign_linking_info_variable = 
	    ISVREF(def_structure_element_of_foreign_linking_info_variable,
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

/* RECLAIM-ELEMENT-OF-FOREIGN-LINKING-INFO-1 */
Object reclaim_element_of_foreign_linking_info_1(element_of_foreign_linking_info)
    Object element_of_foreign_linking_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(214,14);
    inline_note_reclaim_cons(element_of_foreign_linking_info,Nil);
    temp = 
	    ISVREF(Chain_of_available_element_of_foreign_linking_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(element_of_foreign_linking_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_element_of_foreign_linking_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = element_of_foreign_linking_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ELEMENT-OF-FOREIGN-LINKING-INFO */
Object reclaim_structure_for_element_of_foreign_linking_info(element_of_foreign_linking_info)
    Object element_of_foreign_linking_info;
{
    x_note_fn_call(214,15);
    return reclaim_element_of_foreign_linking_info_1(element_of_foreign_linking_info);
}

static Object Qg2_defstruct_structure_name_element_of_foreign_linking_info_g2_struct;  /* g2-defstruct-structure-name::element-of-foreign-linking-info-g2-struct */

/* MAKE-PERMANENT-ELEMENT-OF-FOREIGN-LINKING-INFO-STRUCTURE-INTERNAL */
Object make_permanent_element_of_foreign_linking_info_structure_internal()
{
    Object def_structure_element_of_foreign_linking_info_variable;
    Object defstruct_g2_element_of_foreign_linking_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,16);
    def_structure_element_of_foreign_linking_info_variable = Nil;
    atomic_incff_symval(Qelement_of_foreign_linking_info_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_element_of_foreign_linking_info_variable = Nil;
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
	defstruct_g2_element_of_foreign_linking_info_variable = the_array;
	SVREF(defstruct_g2_element_of_foreign_linking_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_element_of_foreign_linking_info_g2_struct;
	def_structure_element_of_foreign_linking_info_variable = 
		defstruct_g2_element_of_foreign_linking_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_element_of_foreign_linking_info_variable);
}

/* MAKE-ELEMENT-OF-FOREIGN-LINKING-INFO-1 */
Object make_element_of_foreign_linking_info_1(frame_or_structure_in_foreign_linking_info,
	    enclosing_frame_or_structure_in_foreign_linking_info_qm)
    Object frame_or_structure_in_foreign_linking_info;
    Object enclosing_frame_or_structure_in_foreign_linking_info_qm;
{
    Object def_structure_element_of_foreign_linking_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(214,17);
    def_structure_element_of_foreign_linking_info_variable = 
	    ISVREF(Chain_of_available_element_of_foreign_linking_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_element_of_foreign_linking_info_variable) {
	svref_arg_1 = 
		Chain_of_available_element_of_foreign_linking_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_element_of_foreign_linking_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_element_of_foreign_linking_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_element_of_foreign_linking_info_g2_struct;
    }
    else
	def_structure_element_of_foreign_linking_info_variable = 
		make_permanent_element_of_foreign_linking_info_structure_internal();
    inline_note_allocate_cons(def_structure_element_of_foreign_linking_info_variable,
	    Nil);
    SVREF(def_structure_element_of_foreign_linking_info_variable,
	    FIX((SI_Long)1L)) = frame_or_structure_in_foreign_linking_info;
    SVREF(def_structure_element_of_foreign_linking_info_variable,
	    FIX((SI_Long)2L)) = 
	    enclosing_frame_or_structure_in_foreign_linking_info_qm;
    SVREF(def_structure_element_of_foreign_linking_info_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_element_of_foreign_linking_info_variable,
	    FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_element_of_foreign_linking_info_variable);
}

/* SPLICE-ELEMENT-INTO-FOREIGN-LINKING-INFO */
Object splice_element_into_foreign_linking_info(new_element_of_foreign_linking_info,
	    beginning_of_foreign_linking_info)
    Object new_element_of_foreign_linking_info;
    Object beginning_of_foreign_linking_info;
{
    Object old_first_element;

    x_note_fn_call(214,18);
    old_first_element = ISVREF(beginning_of_foreign_linking_info,(SI_Long)3L);
    SVREF(beginning_of_foreign_linking_info,FIX((SI_Long)3L)) = 
	    new_element_of_foreign_linking_info;
    SVREF(new_element_of_foreign_linking_info,FIX((SI_Long)4L)) = 
	    beginning_of_foreign_linking_info;
    SVREF(new_element_of_foreign_linking_info,FIX((SI_Long)3L)) = 
	    old_first_element;
    return VALUES_1(SVREF(old_first_element,FIX((SI_Long)4L)) = 
	    new_element_of_foreign_linking_info);
}

/* SPLICE-ELEMENT-OUT-OF-FOREIGN-LINKING-INFO */
Object splice_element_out_of_foreign_linking_info(element_of_foreign_linking_info)
    Object element_of_foreign_linking_info;
{
    Object next_element_qm, previous_element_qm;

    x_note_fn_call(214,19);
    next_element_qm = ISVREF(element_of_foreign_linking_info,(SI_Long)3L);
    previous_element_qm = ISVREF(element_of_foreign_linking_info,(SI_Long)4L);
    if (previous_element_qm)
	SVREF(previous_element_qm,FIX((SI_Long)3L)) = next_element_qm;
    if (next_element_qm)
	SVREF(next_element_qm,FIX((SI_Long)4L)) = previous_element_qm;
    return reclaim_element_of_foreign_linking_info_1(element_of_foreign_linking_info);
}

Object Starting_element_marker_for_foreign_linking_info = UNBOUND;

Object Final_element_marker_for_foreign_linking_info = UNBOUND;

/* MAKE-EMPTY-FOREIGN-LINKING-INFO */
Object make_empty_foreign_linking_info()
{
    Object starting_element, final_element;

    x_note_fn_call(214,20);
    starting_element = 
	    make_element_of_foreign_linking_info_1(Starting_element_marker_for_foreign_linking_info,
	    Nil);
    final_element = 
	    make_element_of_foreign_linking_info_1(Final_element_marker_for_foreign_linking_info,
	    Nil);
    SVREF(starting_element,FIX((SI_Long)3L)) = final_element;
    return VALUES_1(SVREF(final_element,FIX((SI_Long)4L)) = starting_element);
}

/* RECLAIM-EMPTY-FOREIGN-LINKING-INFO */
Object reclaim_empty_foreign_linking_info(empty_foreign_linking_info)
    Object empty_foreign_linking_info;
{
    Object final_element;

    x_note_fn_call(214,21);
    final_element = ISVREF(empty_foreign_linking_info,(SI_Long)3L);
    reclaim_element_of_foreign_linking_info_1(empty_foreign_linking_info);
    return reclaim_element_of_foreign_linking_info_1(final_element);
}

/* END-OF-FOREIGN-LINKING-INFO-P */
Object end_of_foreign_linking_info_p(element_of_foreign_linking_info)
    Object element_of_foreign_linking_info;
{
    x_note_fn_call(214,22);
    return VALUES_1(EQ(ISVREF(element_of_foreign_linking_info,(SI_Long)1L),
	    Final_element_marker_for_foreign_linking_info) ? T : Nil);
}

Object The_type_description_of_foreign_function_entry = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_foreign_function_entrys, Qchain_of_available_foreign_function_entrys);

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_function_entry_count, Qforeign_function_entry_count);

Object Chain_of_available_foreign_function_entrys_vector = UNBOUND;

/* FOREIGN-FUNCTION-ENTRY-STRUCTURE-MEMORY-USAGE */
Object foreign_function_entry_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,23);
    temp = Foreign_function_entry_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FOREIGN-FUNCTION-ENTRY-COUNT */
Object outstanding_foreign_function_entry_count()
{
    Object def_structure_foreign_function_entry_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,24);
    gensymed_symbol = IFIX(Foreign_function_entry_count);
    def_structure_foreign_function_entry_variable = 
	    Chain_of_available_foreign_function_entrys;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_foreign_function_entry_variable))
	goto end_loop;
    def_structure_foreign_function_entry_variable = 
	    ISVREF(def_structure_foreign_function_entry_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-FOREIGN-FUNCTION-ENTRY-INTERNAL-1 */
Object reclaim_foreign_function_entry_internal_1(foreign_function_entry)
    Object foreign_function_entry;
{
    Object temp, svref_arg_2;

    x_note_fn_call(214,25);
    inline_note_reclaim_cons(foreign_function_entry,Nil);
    temp = ISVREF(Chain_of_available_foreign_function_entrys_vector,
	    IFIX(Current_thread_index));
    SVREF(foreign_function_entry,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_foreign_function_entrys_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = foreign_function_entry;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FOREIGN-FUNCTION-ENTRY */
Object reclaim_structure_for_foreign_function_entry(foreign_function_entry)
    Object foreign_function_entry;
{
    x_note_fn_call(214,26);
    return reclaim_foreign_function_entry_internal_1(foreign_function_entry);
}

static Object Qg2_defstruct_structure_name_foreign_function_entry_g2_struct;  /* g2-defstruct-structure-name::foreign-function-entry-g2-struct */

/* MAKE-PERMANENT-FOREIGN-FUNCTION-ENTRY-STRUCTURE-INTERNAL */
Object make_permanent_foreign_function_entry_structure_internal()
{
    Object def_structure_foreign_function_entry_variable;
    Object defstruct_g2_foreign_function_entry_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,27);
    def_structure_foreign_function_entry_variable = Nil;
    atomic_incff_symval(Qforeign_function_entry_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_foreign_function_entry_variable = Nil;
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
	defstruct_g2_foreign_function_entry_variable = the_array;
	SVREF(defstruct_g2_foreign_function_entry_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_foreign_function_entry_g2_struct;
	def_structure_foreign_function_entry_variable = 
		defstruct_g2_foreign_function_entry_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_foreign_function_entry_variable);
}

/* MAKE-FOREIGN-FUNCTION-ENTRY-1 */
Object make_foreign_function_entry_1(foreign_function_name,
	    foreign_function_id,foreign_function_argument_count,
	    foreign_function_type_list,foreign_function_return_type)
    Object foreign_function_name, foreign_function_id;
    Object foreign_function_argument_count, foreign_function_type_list;
    Object foreign_function_return_type;
{
    Object def_structure_foreign_function_entry_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(214,28);
    def_structure_foreign_function_entry_variable = 
	    ISVREF(Chain_of_available_foreign_function_entrys_vector,
	    IFIX(Current_thread_index));
    if (def_structure_foreign_function_entry_variable) {
	svref_arg_1 = Chain_of_available_foreign_function_entrys_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_foreign_function_entry_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_foreign_function_entry_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_foreign_function_entry_g2_struct;
    }
    else
	def_structure_foreign_function_entry_variable = 
		make_permanent_foreign_function_entry_structure_internal();
    inline_note_allocate_cons(def_structure_foreign_function_entry_variable,
	    Nil);
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)1L)) 
	    = foreign_function_name;
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)2L)) 
	    = foreign_function_id;
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)3L)) 
	    = foreign_function_argument_count;
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)4L)) 
	    = foreign_function_type_list;
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)5L)) 
	    = foreign_function_return_type;
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)6L)) 
	    = Nil;
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)7L)) 
	    = Nil;
    SVREF(def_structure_foreign_function_entry_variable,FIX((SI_Long)8L)) 
	    = Nil;
    return VALUES_1(def_structure_foreign_function_entry_variable);
}

/* RECLAIM-FOREIGN-FUNCTION-ENTRY */
Object reclaim_foreign_function_entry(entry)
    Object entry;
{
    Object serial_numbers, serial_number, ab_loop_list_;

    x_note_fn_call(214,29);
    if (ISVREF(entry,(SI_Long)1L)) {
	reclaim_text_string(ISVREF(entry,(SI_Long)1L));
	SVREF(entry,FIX((SI_Long)1L)) = Nil;
    }
    if (ISVREF(entry,(SI_Long)4L)) {
	reclaim_icp_list_1(ISVREF(entry,(SI_Long)4L));
	SVREF(entry,FIX((SI_Long)4L)) = Nil;
    }
    if (ISVREF(entry,(SI_Long)7L)) {
	reclaim_icp_list_1(ISVREF(entry,(SI_Long)7L));
	SVREF(entry,FIX((SI_Long)7L)) = Nil;
    }
    serial_numbers = ISVREF(entry,(SI_Long)8L);
    if (serial_numbers) {
	serial_number = Nil;
	ab_loop_list_ = serial_numbers;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	serial_number = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_frame_serial_number(serial_number);
	goto next_loop;
      end_loop:;
	reclaim_icp_list_1(serial_numbers);
	SVREF(entry,FIX((SI_Long)8L)) = Nil;
    }
    return reclaim_foreign_function_entry_internal_1(entry);
}

static Object Qstring_eq_w;        /* string=w */

/* GET-OR-MAKE-FOREIGN-FUNCTION-ENTRY */
Object get_or_make_foreign_function_entry(foreign_function_name,
	    foreign_function_id,foreign_function_argument_count,
	    foreign_function_type_list,foreign_function_return_type,
	    foreign_image_info)
    Object foreign_function_name, foreign_function_id;
    Object foreign_function_argument_count, foreign_function_type_list;
    Object foreign_function_return_type, foreign_image_info;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_2, entry_hash, old_entry_qm, new_entry;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(214,30);
    gensymed_symbol = IFIX(sxhashw(foreign_function_name));
    temp = Foreign_function_registry;
    temp_1 = gensymed_symbol % (SI_Long)131L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = foreign_function_name;
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
	    key_hash_value &&  !TRUEP(string_eq_w(key_value,ISVREF(curr,
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
    old_entry_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (string_eq_w(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (old_entry_qm) {
	reclaim_icp_list_1(foreign_function_type_list);
	temp = ISVREF(old_entry_qm,(SI_Long)6L);
	return VALUES_2(old_entry_qm,temp);
    }
    else {
	new_entry = make_foreign_function_entry_1(foreign_function_name,
		foreign_function_id,foreign_function_argument_count,
		foreign_function_type_list,foreign_function_return_type);
	SVREF(new_entry,FIX((SI_Long)6L)) = foreign_image_info;
	gensymed_symbol = IFIX(sxhashw(foreign_function_name));
	temp = Foreign_function_registry;
	temp_1 = gensymed_symbol % (SI_Long)131L;
	set_skip_list_entry(SVREF(temp,FIX(temp_1)),FIX((SI_Long)31L),
		Qstring_eq_w,Nil,T,foreign_function_name,
		FIX(gensymed_symbol),new_entry);
	return VALUES_2(new_entry,Nil);
    }
}

Object The_type_description_of_foreign_function_image_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_foreign_function_image_infos, Qchain_of_available_foreign_function_image_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_function_image_info_count, Qforeign_function_image_info_count);

Object Chain_of_available_foreign_function_image_infos_vector = UNBOUND;

/* FOREIGN-FUNCTION-IMAGE-INFO-STRUCTURE-MEMORY-USAGE */
Object foreign_function_image_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,31);
    temp = Foreign_function_image_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FOREIGN-FUNCTION-IMAGE-INFO-COUNT */
Object outstanding_foreign_function_image_info_count()
{
    Object def_structure_foreign_function_image_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,32);
    gensymed_symbol = IFIX(Foreign_function_image_info_count);
    def_structure_foreign_function_image_info_variable = 
	    Chain_of_available_foreign_function_image_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_foreign_function_image_info_variable))
	goto end_loop;
    def_structure_foreign_function_image_info_variable = 
	    ISVREF(def_structure_foreign_function_image_info_variable,
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

/* RECLAIM-FOREIGN-IMAGE-INFO-INTERNAL-1 */
Object reclaim_foreign_image_info_internal_1(foreign_function_image_info)
    Object foreign_function_image_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(214,33);
    inline_note_reclaim_cons(foreign_function_image_info,Nil);
    temp = ISVREF(Chain_of_available_foreign_function_image_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(foreign_function_image_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_foreign_function_image_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = foreign_function_image_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FOREIGN-FUNCTION-IMAGE-INFO */
Object reclaim_structure_for_foreign_function_image_info(foreign_function_image_info)
    Object foreign_function_image_info;
{
    x_note_fn_call(214,34);
    return reclaim_foreign_image_info_internal_1(foreign_function_image_info);
}

static Object Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct;  /* g2-defstruct-structure-name::foreign-function-image-info-g2-struct */

/* MAKE-PERMANENT-FOREIGN-FUNCTION-IMAGE-INFO-STRUCTURE-INTERNAL */
Object make_permanent_foreign_function_image_info_structure_internal()
{
    Object def_structure_foreign_function_image_info_variable;
    Object defstruct_g2_foreign_function_image_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,35);
    def_structure_foreign_function_image_info_variable = Nil;
    atomic_incff_symval(Qforeign_function_image_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_foreign_function_image_info_variable = Nil;
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
	defstruct_g2_foreign_function_image_info_variable = the_array;
	SVREF(defstruct_g2_foreign_function_image_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct;
	def_structure_foreign_function_image_info_variable = 
		defstruct_g2_foreign_function_image_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_foreign_function_image_info_variable);
}

/* MAKE-FOREIGN-FUNCTION-IMAGE-INFO-1 */
Object make_foreign_function_image_info_1()
{
    Object def_structure_foreign_function_image_info_variable, temp;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(214,36);
    def_structure_foreign_function_image_info_variable = 
	    ISVREF(Chain_of_available_foreign_function_image_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_foreign_function_image_info_variable) {
	temp = Chain_of_available_foreign_function_image_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_foreign_function_image_info_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_foreign_function_image_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct;
    }
    else
	def_structure_foreign_function_image_info_variable = 
		make_permanent_foreign_function_image_info_structure_internal();
    inline_note_allocate_cons(def_structure_foreign_function_image_info_variable,
	    Nil);
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)1L)) = Nil;
    temp = make_empty_foreign_linking_info();
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)11L)) = Nil;
    ISVREF(def_structure_foreign_function_image_info_variable,
	    (SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_foreign_function_image_info_variable,
	    FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_foreign_function_image_info_variable);
}

/* CONNECTION-SPECIFICATION-TO-FOREIGN-IMAGE-FUNCTION */
Object connection_specification_to_foreign_image_function(foreign_function_image_info)
    Object foreign_function_image_info;
{
    Object temp;

    x_note_fn_call(214,37);
    temp = ISVREF(foreign_function_image_info,(SI_Long)6L);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Unused_foreign_image_indices, Qunused_foreign_image_indices);

DEFINE_VARIABLE_WITH_SYMBOL(Highest_foreign_image_index, Qhighest_foreign_image_index);

/* GET-FOREIGN-IMAGE-INFO-FROM-ICP-SOCKET */
Object get_foreign_image_info_from_icp_socket(foreign_image_icp_socket)
    Object foreign_image_icp_socket;
{
    Object image, ab_loop_list_, ab_loop_it_, temp;

    x_note_fn_call(214,38);
    image = Nil;
    ab_loop_list_ = All_foreign_function_images_qm;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(ISVREF(image,(SI_Long)5L),foreign_image_icp_socket) ? 
	    image : Qnil;
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
	image = Nil;
	ab_loop_list_ = All_external_foreign_function_images_qm;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	image = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQ(ISVREF(image,(SI_Long)5L),
		foreign_image_icp_socket) ? image : Qnil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* PATHNAME-OF-A-CONNECTED-FOREIGN-IMAGE-P */
Object pathname_of_a_connected_foreign_image_p(pathname_1)
    Object pathname_1;
{
    Object image, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(214,39);
    image = Nil;
    ab_loop_list_ = All_foreign_function_images_qm;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = gensym_pathnames_equal_enough_p(pathname_1,ISVREF(image,
	    (SI_Long)3L));
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

/* GET-FOREIGN-IMAGE-INFO-FROM-PATHNAME */
Object get_foreign_image_info_from_pathname(pathname_1)
    Object pathname_1;
{
    volatile Object probed_pathname_qm;
    Object image, ab_loop_list_, ab_loop_it_;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(214,40);
    SAVE_STACK();
    probed_pathname_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	probed_pathname_qm = gensym_probe_file(pathname_1);
	if (probed_pathname_qm) {
	    image = Nil;
	    ab_loop_list_ = All_foreign_function_images_qm;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    image = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = gensym_pathnames_equal_enough_p(ISVREF(image,
		    (SI_Long)3L),probed_pathname_qm) ? image : Qnil;
	    if (ab_loop_it_) {
		SAVE_VALUES(VALUES_1(ab_loop_it_));
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    SAVE_VALUES(VALUES_1(Qnil));
	  end_1:;
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (probed_pathname_qm) {
	if ( !EQ(probed_pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(probed_pathname_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* GENSYM-EQUAL */
Object gensym_equal(thing1,thing2)
    Object thing1, thing2;
{
    Object cond_temporary_1, temp, cond_temporary_2, cond_temporary_3;
    Object cond_temporary_4;

    x_note_fn_call(214,41);
    cond_temporary_1 = Nil;
    cond_temporary_1 =  !TRUEP(thing1) ? T : Nil;
    if (cond_temporary_1 &&  !TRUEP(thing2))
	temp = T;
    else if (cond_temporary_1 ||  !TRUEP(thing2))
	temp = Nil;
    else {
	cond_temporary_2 = Nil;
	cond_temporary_2 = CONSP(thing1) ? T : Nil;
	if (cond_temporary_2 && CONSP(thing2))
	    temp = gensym_equal(M_CAR(thing1),M_CAR(thing2)) ? 
		    gensym_equal(M_CDR(thing1),M_CDR(thing2)) : Qnil;
	else if (cond_temporary_2 || CONSP(thing2))
	    temp = Nil;
	else {
	    cond_temporary_3 = Nil;
	    cond_temporary_3 = STRINGP(thing1) ? T : Nil;
	    if (cond_temporary_3 && STRINGP(thing2))
		temp = string_eq(2,thing1,thing2);
	    else if (cond_temporary_3 || STRINGP(thing2))
		temp = Nil;
	    else {
		cond_temporary_4 = Nil;
		cond_temporary_4 = text_string_p(thing1);
		if (cond_temporary_4 && text_string_p(thing2))
		    temp = string_eq_w(thing1,thing2);
		else if (cond_temporary_4 || text_string_p(thing2))
		    temp = Nil;
		else
		    temp = EQL(thing1,thing2) ? T : Nil;
	    }
	}
    }
    return VALUES_1(temp);
}

/* GET-FOREIGN-IMAGE-INFO-FROM-CONNECTION-SPEC */
Object get_foreign_image_info_from_connection_spec(connection_spec)
    Object connection_spec;
{
    Object image, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(214,42);
    image = Nil;
    ab_loop_list_ = All_external_foreign_function_images_qm;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = gensym_equal(connection_spec,ISVREF(image,(SI_Long)6L)) ?
	     image : Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qicp;                /* icp */

/* REMOVE-FOREIGN-IMAGE-INFO-FROM-ALL-FOREIGN-FUNCTION-IMAGES */
Object remove_foreign_image_info_from_all_foreign_function_images(info_to_remove)
    Object info_to_remove;
{
    Object icp_pop_store, cons_1, next_cons, temp, svref_arg_2, info_in_list;
    Object ab_loop_list_, cons_in_list, ab_loop_iter_flag_;

    x_note_fn_call(214,43);
    if (EQ(CAR(All_foreign_function_images_qm),info_to_remove)) {
	icp_pop_store = Nil;
	cons_1 = All_foreign_function_images_qm;
	if (cons_1) {
	    icp_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qicp);
	    if (ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	All_foreign_function_images_qm = next_cons;
	return VALUES_1(icp_pop_store);
    }
    info_in_list = Nil;
    ab_loop_list_ = CDR(All_foreign_function_images_qm);
    cons_in_list = All_foreign_function_images_qm;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    info_in_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	cons_in_list = M_CDR(cons_in_list);
    if ( !TRUEP(cons_in_list))
	goto end_loop;
    if (EQ(info_to_remove,info_in_list)) {
	temp = CDDR(cons_in_list);
	M_CDR(cons_in_list) = temp;
	return VALUES_1(info_to_remove);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    if (EQ(CAR(All_external_foreign_function_images_qm),info_to_remove)) {
	icp_pop_store = Nil;
	cons_1 = All_external_foreign_function_images_qm;
	if (cons_1) {
	    icp_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qicp);
	    if (ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	All_external_foreign_function_images_qm = next_cons;
	return VALUES_1(icp_pop_store);
    }
    info_in_list = Nil;
    ab_loop_list_ = CDR(All_external_foreign_function_images_qm);
    cons_in_list = All_external_foreign_function_images_qm;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    info_in_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	cons_in_list = M_CDR(cons_in_list);
    if ( !TRUEP(cons_in_list))
	goto end_loop_1;
    if (EQ(info_to_remove,info_in_list)) {
	temp = CDDR(cons_in_list);
	M_CDR(cons_in_list) = temp;
	return VALUES_1(info_to_remove);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(info_to_remove);
}

Object The_type_description_of_foreign_function_call_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_foreign_function_call_infos, Qchain_of_available_foreign_function_call_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_function_call_info_count, Qforeign_function_call_info_count);

Object Chain_of_available_foreign_function_call_infos_vector = UNBOUND;

/* FOREIGN-FUNCTION-CALL-INFO-STRUCTURE-MEMORY-USAGE */
Object foreign_function_call_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,44);
    temp = Foreign_function_call_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FOREIGN-FUNCTION-CALL-INFO-COUNT */
Object outstanding_foreign_function_call_info_count()
{
    Object def_structure_foreign_function_call_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,45);
    gensymed_symbol = IFIX(Foreign_function_call_info_count);
    def_structure_foreign_function_call_info_variable = 
	    Chain_of_available_foreign_function_call_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_foreign_function_call_info_variable))
	goto end_loop;
    def_structure_foreign_function_call_info_variable = 
	    ISVREF(def_structure_foreign_function_call_info_variable,
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

/* RECLAIM-FOREIGN-FUNCTION-CALL-INFO-1 */
Object reclaim_foreign_function_call_info_1(foreign_function_call_info)
    Object foreign_function_call_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(214,46);
    inline_note_reclaim_cons(foreign_function_call_info,Nil);
    temp = ISVREF(Chain_of_available_foreign_function_call_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(foreign_function_call_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_foreign_function_call_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = foreign_function_call_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FOREIGN-FUNCTION-CALL-INFO */
Object reclaim_structure_for_foreign_function_call_info(foreign_function_call_info)
    Object foreign_function_call_info;
{
    x_note_fn_call(214,47);
    return reclaim_foreign_function_call_info_1(foreign_function_call_info);
}

static Object Qg2_defstruct_structure_name_foreign_function_call_info_g2_struct;  /* g2-defstruct-structure-name::foreign-function-call-info-g2-struct */

/* MAKE-PERMANENT-FOREIGN-FUNCTION-CALL-INFO-STRUCTURE-INTERNAL */
Object make_permanent_foreign_function_call_info_structure_internal()
{
    Object def_structure_foreign_function_call_info_variable;
    Object defstruct_g2_foreign_function_call_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,48);
    def_structure_foreign_function_call_info_variable = Nil;
    atomic_incff_symval(Qforeign_function_call_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_foreign_function_call_info_variable = Nil;
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
	defstruct_g2_foreign_function_call_info_variable = the_array;
	SVREF(defstruct_g2_foreign_function_call_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_foreign_function_call_info_g2_struct;
	def_structure_foreign_function_call_info_variable = 
		defstruct_g2_foreign_function_call_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_foreign_function_call_info_variable);
}

/* MAKE-FOREIGN-FUNCTION-CALL-INFO-1 */
Object make_foreign_function_call_info_1()
{
    Object def_structure_foreign_function_call_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(214,49);
    def_structure_foreign_function_call_info_variable = 
	    ISVREF(Chain_of_available_foreign_function_call_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_foreign_function_call_info_variable) {
	svref_arg_1 = Chain_of_available_foreign_function_call_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_foreign_function_call_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_foreign_function_call_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_foreign_function_call_info_g2_struct;
    }
    else
	def_structure_foreign_function_call_info_variable = 
		make_permanent_foreign_function_call_info_structure_internal();
    inline_note_allocate_cons(def_structure_foreign_function_call_info_variable,
	    Nil);
    SVREF(def_structure_foreign_function_call_info_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_foreign_function_call_info_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_foreign_function_call_info_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_foreign_function_call_info_variable,
	    FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_foreign_function_call_info_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_foreign_function_call_info, Qcurrent_foreign_function_call_info);

/* INITIALIZE-CURRENT-FOREIGN-FUNCTION-CALL-INFO */
Object initialize_current_foreign_function_call_info()
{
    x_note_fn_call(214,50);
    return make_foreign_function_call_info_1();
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qwhole_string;       /* whole-string */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* FOREIGN-FUNCTION-NAME-EVALUATION-SETTER */
Object foreign_function_name_evaluation_setter(evaluation_value_qm,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value_qm, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(214,51);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value_qm,
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value_qm,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_foreign_function_name_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value_qm) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value_qm;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Nil);
  end_foreign_function_name_evaluation_setter:
    return result;
}

/* FOREIGN-FUNCTION-NAME-EVALUATION-GETTER */
Object foreign_function_name_evaluation_getter(slot_value_qm,frame,
	    slot_description)
    Object slot_value_qm, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(214,52);
    if (slot_value_qm) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value_qm;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qab_real;            /* real */

/* FOREIGN-FUNCTION-ARGUMENT-DESCRIPTION-EVALUATION-GETTER */
Object foreign_function_argument_description_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object argument_description, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(214,53);
    argument_description = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(EQ(argument_description,Qab_real) ? Qfloat 
	    : argument_description,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* FOREIGN-FUNCTION-RESULT-TYPE-EVALUATION-GETTER */
Object foreign_function_result_type_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(214,54);
    GENSYM_RETURN_ONE(EQ(slot_value,Qab_real) ? Qfloat : slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object Qseconds;            /* seconds */

static Object Quse_default;        /* use-default */

static Object Qdefault;            /* default */

/* FOREIGN-FUNCTION-TIMEOUT-INTERVAL-EVALUATION-SETTER */
Object foreign_function_timeout_interval_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(214,55);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_2))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_3,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_foreign_function_timeout_interval_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INTEGERP(evaluation_value))
	result = phrase_cons(evaluation_value,Qseconds);
    else if (EQ(evaluation_value,Quse_default))
	result = VALUES_1(Qdefault);
    else
	result = VALUES_1(Nil);
  end_foreign_function_timeout_interval_evaluation_setter:
    return result;
}

/* FOREIGN-FUNCTION-TIMEOUT-INTERVAL-EVALUATION-GETTER */
Object foreign_function_timeout_interval_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(214,56);
    GENSYM_RETURN_ONE(slot_value ? (EQ(slot_value,Qdefault) ? Quse_default 
	    : slot_value) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_4;     /* # */

/* DEFAULT-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-EVALUATION-SETTER */
Object default_foreign_function_timeout_interval_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(214,57);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_4))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_3,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_default_foreign_function_timeout_interval_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INTEGERP(evaluation_value))
	result = phrase_cons(evaluation_value,Qseconds);
    else if (EQ(evaluation_value,Quse_default))
	result = VALUES_1(Qdefault);
    else
	result = VALUES_1(Nil);
  end_default_foreign_function_timeout_interval_evaluation_setter:
    return result;
}

/* DEFAULT-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-EVALUATION-GETTER */
Object default_foreign_function_timeout_interval_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(214,58);
    GENSYM_RETURN_ONE(slot_value ? (EQ(slot_value,Qdefault) ? Quse_default 
	    : slot_value) : Nil);
    return VALUES_1(Nil);
}

/* PUT-WAIT-STRATEGY-WHERE-SLOT-IS-ABSENT */
Object put_wait_strategy_where_slot_is_absent(foreign_function_declaration,
	    new_wait_strategy)
    Object foreign_function_declaration, new_wait_strategy;
{
    x_note_fn_call(214,59);
    return VALUES_1(Nil);
}

static Object Qforeign_function_declaration;  /* foreign-function-declaration */

static Object Qincomplete;         /* incomplete */

/* INITIALIZE-FOR-FOREIGN-FUNCTION-DECLARATION */
Object initialize_for_foreign_function_declaration(foreign_function_declaration)
    Object foreign_function_declaration;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,60);
    frame = foreign_function_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qforeign_function_declaration)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    if ( !TRUEP(ISVREF(foreign_function_declaration,(SI_Long)16L)))
	return update_frame_status(foreign_function_declaration,
		Qincomplete,Nil);
    else
	return VALUES_1(Nil);
}

/* KILL-FOREIGN-IMAGE-PROCESS-UNCONDITIONALLY */
Object kill_foreign_image_process_unconditionally(foreign_image_id_qm)
    Object foreign_image_id_qm;
{
    Object temp;

    x_note_fn_call(214,61);
    if (foreign_image_id_qm) {
	g2ext_kill_spawned_command_line(DFLOAT_ISAREF_1(foreign_image_id_qm,
		(SI_Long)0L));
	reclaim_managed_simple_float_array_of_length_1(foreign_image_id_qm);
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qg2_defstruct_structure_name_icp_socket_g2_struct;  /* g2-defstruct-structure-name::icp-socket-g2-struct */

/* CLOSE-FOREIGN-IMAGE-SOCKET */
Object close_foreign_image_socket(image_info)
    Object image_info;
{
    Object foreign_socket_qm;

    x_note_fn_call(214,62);
    foreign_socket_qm = ISVREF(image_info,(SI_Long)5L);
    if (SIMPLE_VECTOR_P(foreign_socket_qm) && EQ(ISVREF(foreign_socket_qm,
	    (SI_Long)0L),Qg2_defstruct_structure_name_icp_socket_g2_struct))
	shutdown_icp_socket_connection(1,foreign_socket_qm);
    return VALUES_1(SVREF(image_info,FIX((SI_Long)5L)) = Nil);
}

/* KILL-FOREIGN-IMAGE-UNCONDITIONALLY */
Object kill_foreign_image_unconditionally(image_info)
    Object image_info;
{
    Object foreign_image_id_qm;

    x_note_fn_call(214,63);
    close_foreign_image_socket(image_info);
    foreign_image_id_qm = ISVREF(image_info,(SI_Long)14L) ? Nil : 
	    ISVREF(image_info,(SI_Long)10L);
    if (foreign_image_id_qm) {
	kill_foreign_image_process_unconditionally(foreign_image_id_qm);
	return VALUES_1(SVREF(image_info,FIX((SI_Long)10L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qunlinked_to_unconnected_foreign_image;  /* unlinked-to-unconnected-foreign-image */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* RECLAIM-FOREIGN-FUNCTION-IMAGE-INFO */
Object reclaim_foreign_function_image_info(image_info)
    Object image_info;
{
    Object entry_list, entry, ab_loop_list_, connected_frame, ab_loop_list__1;
    Object serial_number, ab_loop_list__2, gensymed_symbol, gensymed_symbol_1;
    Object temp, unlinked_element, unlinked_declaration, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object connection_spec_qm, item, index_qm, overlay_pathname_qm;
    volatile Object overlay_truename;
    Object image_pathname_qm, image_namestring_qm;
    SI_Long gensymed_symbol_2, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(214,64);
    SAVE_STACK();
    if ( !(SIMPLE_VECTOR_P(image_info) && EQ(ISVREF(image_info,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct))) 
		{
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    remove_foreign_image_info_from_all_foreign_function_images(image_info);
    entry_list = ISVREF(image_info,(SI_Long)1L);
    entry = Nil;
    ab_loop_list_ = entry_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    connected_frame = Nil;
    ab_loop_list__1 = ISVREF(entry,(SI_Long)7L);
    serial_number = Nil;
    ab_loop_list__2 = ISVREF(entry,(SI_Long)8L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    connected_frame = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_list__2))
	goto end_loop_1;
    serial_number = M_CAR(ab_loop_list__2);
    ab_loop_list__2 = M_CDR(ab_loop_list__2);
    gensymed_symbol = ISVREF(connected_frame,(SI_Long)3L);
    gensymed_symbol_1 = serial_number;
    if (FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
	    FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : TRUEP(Nil)) : 
	    FIXNUMP(gensymed_symbol_1) ? TRUEP(Nil) : 
	    FIXNUM_EQ(M_CAR(gensymed_symbol),M_CAR(gensymed_symbol_1)) && 
	    FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1))) {
	ISVREF(connected_frame,(SI_Long)22L) = Nil;
	add_frame_note(5,Qunlinked_to_unconnected_foreign_image,
		connected_frame,Nil,T,Nil);
    }
    goto next_loop_1;
  end_loop_1:;
    gensymed_symbol = ISVREF(entry,(SI_Long)1L);
    gensymed_symbol_2 = IFIX(sxhashw(gensymed_symbol));
    temp = Foreign_function_registry;
    temp_1 = gensymed_symbol_2 % (SI_Long)131L;
    delete_skip_list_entry(SYMBOL_FUNCTION(Qstring_eq_w),gensymed_symbol,
	    SVREF(temp,FIX(temp_1)),FIX((SI_Long)31L),FIX(gensymed_symbol_2));
    reclaim_foreign_function_entry(entry);
    goto next_loop;
  end_loop:
    reclaim_icp_list_1(entry_list);
    SVREF(image_info,FIX((SI_Long)1L)) = Nil;
    unlinked_element = ISVREF(ISVREF(image_info,(SI_Long)2L),(SI_Long)3L);
  next_loop_2:
    if (end_of_foreign_linking_info_p(unlinked_element))
	goto end_loop_2;
    unlinked_declaration = ISVREF(unlinked_element,(SI_Long)1L);
    gensymed_symbol = ISVREF(unlinked_declaration,(SI_Long)21L);
    gensymed_symbol_2 = IFIX(sxhashw(gensymed_symbol));
    temp = Foreign_function_registry;
    temp_1 = gensymed_symbol_2 % (SI_Long)131L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = gensymed_symbol;
    key_hash_value = gensymed_symbol_2;
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
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
  next_loop_5:
    if ( !TRUEP(marked))
	goto end_loop_4;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
    goto next_loop_5;
  end_loop_4:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !TRUEP(string_eq_w(key_value,ISVREF(curr,
	    (SI_Long)2L)))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_1;
    goto next_loop_4;
  end_loop_5:
  end_1:
    level = level - (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    update_foreign_function_linking(unlinked_declaration,IFIX(ISVREF(curr,
	    (SI_Long)1L)) == key_hash_value ? (string_eq_w(key_value,
	    ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : 
	    Nil,T);
    unlinked_element = ISVREF(unlinked_element,(SI_Long)3L);
    goto next_loop_2;
  end_loop_2:
    reclaim_empty_foreign_linking_info(ISVREF(image_info,(SI_Long)2L));
    SVREF(image_info,FIX((SI_Long)2L)) = Nil;
    connection_spec_qm = ISVREF(image_info,(SI_Long)6L);
    if (connection_spec_qm) {
	item = Nil;
	ab_loop_list_ = connection_spec_qm;
      next_loop_6:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_6;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (text_string_p(item))
	    reclaim_text_string(item);
	goto next_loop_6;
      end_loop_6:;
	reclaim_icp_list_1(connection_spec_qm);
	SVREF(image_info,FIX((SI_Long)7L)) = Nil;
	SVREF(image_info,FIX((SI_Long)6L)) = Nil;
    }
    Unused_foreign_image_indices = nconc2(Unused_foreign_image_indices,
	    ISVREF(image_info,(SI_Long)13L));
    SVREF(image_info,FIX((SI_Long)13L)) = Nil;
    index_qm = ISVREF(image_info,(SI_Long)8L);
    if (index_qm &&  !TRUEP(member_eql(index_qm,Unused_foreign_image_indices)))
	Unused_foreign_image_indices = nconc2(Unused_foreign_image_indices,
		icp_cons_1(index_qm,Nil));
    overlay_pathname_qm = ISVREF(image_info,(SI_Long)9L);
    if (overlay_pathname_qm) {
	overlay_truename = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    overlay_truename = gensym_probe_file(overlay_pathname_qm);
	    gensym_delete_file(overlay_truename);
	}
	POP_UNWIND_PROTECT(0);
	if (overlay_truename) {
	    if ( !EQ(overlay_truename,Qunbound_in_protected_let))
		reclaim_gensym_pathname(overlay_truename);
	}
	CONTINUE_UNWINDING(0);
	reclaim_gensym_pathname(overlay_pathname_qm);
    }
    image_pathname_qm = ISVREF(image_info,(SI_Long)3L);
    if (SIMPLE_VECTOR_P(image_pathname_qm) && EQ(ISVREF(image_pathname_qm,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	reclaim_gensym_pathname(image_pathname_qm);
    SVREF(image_info,FIX((SI_Long)3L)) = Nil;
    image_namestring_qm = ISVREF(image_info,(SI_Long)4L);
    if (image_namestring_qm)
	reclaim_text_string(image_namestring_qm);
    SVREF(image_info,FIX((SI_Long)4L)) = Nil;
    result = reclaim_foreign_image_info_internal_1(image_info);
    RESTORE_STACK();
    return result;
}

static Object Qcm;                 /* \, */

static Object Qdeclared_arglist;   /* declared-arglist */

static Object Qdeclared_return_type;  /* declared-return-type */

static Object Qname_in_foreign_image;  /* name-in-foreign-image */

static Object string_constant;     /* "~(~a~)" */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* COMPILE-FOREIGN-FUNCTION-DECLARATION-FOR-SLOT */
Object compile_foreign_function_declaration_for_slot varargs_1(int, n)
{
    Object parse_result, declaration, gensymed_symbol;
    Object temp, cons_of_parameters, name, temp_1, parameter_cons;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,65);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    declaration = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    temp = CDDDR(parse_result);
    cons_of_parameters = CDDR(temp);
    name = FIFTH(parse_result);
    if ( !TRUEP(CAR(cons_of_parameters)));
    else {
	temp = CAR(cons_of_parameters);
	if (ATOM(temp)) {
	    temp_1 = phrase_cons(CAR(cons_of_parameters),Nil);
	    M_CAR(cons_of_parameters) = temp_1;
	}
	else if (EQ(CAAR(cons_of_parameters),Qcm)) {
	    temp_1 = CDAR(cons_of_parameters);
	    M_CAR(cons_of_parameters) = temp_1;
	}
    }
    parameter_cons = CAR(cons_of_parameters);
  next_loop:
    if ( !TRUEP(parameter_cons))
	goto end_loop;
    if (EQ(CAR(parameter_cons),Qfloat))
	M_CAR(parameter_cons) = Qab_real;
    parameter_cons = M_CDR(parameter_cons);
    goto next_loop;
  end_loop:;
    if (EQ(THIRD(parse_result),Qfloat))
	M_THIRD(parse_result) = Qab_real;
    reclaim_slot_value(ISVREF(declaration,(SI_Long)25L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(declaration,Qdeclared_arglist);
    temp_1 = copy_for_slot_value(CAR(cons_of_parameters));
    SVREF(declaration,FIX((SI_Long)25L)) = temp_1;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(declaration,Qdeclared_return_type);
    temp_1 = THIRD(parse_result);
    SVREF(declaration,FIX((SI_Long)26L)) = temp_1;
    if ( !TRUEP(ISVREF(declaration,(SI_Long)20L)))
	change_slot_value(3,declaration,Qname_in_foreign_image,
		tformat_text_string(2,string_constant,name));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(declaration,Qname_or_names_for_frame);
    set_lookup_slot_value_1(declaration,Qname_or_names_for_frame,name);
    return VALUES_1(parse_result);
}

static Object Qnone;               /* none */

static Object Qname_furnished_by_user_qm;  /* name-furnished-by-user? */

static Object string_constant_1;   /* "~(~A~)" */

/* COMPILE-FOREIGN-FUNCTION-NAME-FOR-SLOT */
Object compile_foreign_function_name_for_slot varargs_1(int, n)
{
    Object parse_result, declaration, gensymed_symbol;
    Object box_translation_and_text, translation_qm, name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,66);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    declaration = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone)) {
	box_translation_and_text = ISVREF(declaration,(SI_Long)16L);
	translation_qm =  !EQ(box_translation_and_text,No_value) ? 
		CAR(box_translation_and_text) : Nil;
	name = FIFTH(translation_qm);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(declaration,Qname_furnished_by_user_qm);
	SVREF(declaration,FIX((SI_Long)20L)) = Nil;
	if (name)
	    return tformat_text_string(2,string_constant_1,name);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(declaration,Qname_furnished_by_user_qm);
	SVREF(declaration,FIX((SI_Long)20L)) = T;
	return VALUES_1(parse_result);
    }
}

Object Largest_allowable_foreign_function_timeout_interval = UNBOUND;

Object Too_long_timeout_error_text = UNBOUND;

/* COMPILE-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FOR-SLOT */
Object compile_foreign_function_timeout_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object nseconds, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,67);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qdefault))
	return VALUES_1(Qdefault);
    else {
	nseconds = CAR(parse_result);
	if (FIXNUM_GT(nseconds,
		Largest_allowable_foreign_function_timeout_interval)) {
	    temp = Bad_phrase;
	    temp_1 = copy_wide_string(Too_long_timeout_error_text);
	    return VALUES_2(temp,temp_1);
	}
	else
	    return VALUES_1(nseconds);
    }
}

/* COMPILE-DEFAULT-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FOR-SLOT */
Object compile_default_foreign_function_timeout_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object nseconds, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,68);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    nseconds = CAR(parse_result);
    if (FIXNUM_GT(nseconds,
	    Largest_allowable_foreign_function_timeout_interval)) {
	temp = Bad_phrase;
	temp_1 = copy_wide_string(Too_long_timeout_error_text);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(nseconds);
}

static Object string_constant_2;   /* "none" */

/* WRITE-FOREIGN-FUNCTION-NAME-FROM-SLOT */
Object write_foreign_function_name_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(214,69);
    temp = value;
    if (temp);
    else
	temp = string_constant_2;
    return tprin(temp,value);
}

static Object string_constant_3;   /* "use default" */

/* WRITE-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FROM-SLOT */
Object write_foreign_function_timeout_interval_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(214,70);
    if (NUMBERP(value))
	return print_constant(2,value,Qseconds);
    else
	return twrite(string_constant_3);
}

/* WRITE-DEFAULT-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FROM-SLOT */
Object write_default_foreign_function_timeout_interval_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(214,71);
    return print_constant(2,value,Qseconds);
}

/* PUT-NAME-IN-FOREIGN-LANGUAGE-WHERE-SLOT-IS-ABSENT */
Object put_name_in_foreign_language_where_slot_is_absent(foreign_function_declaration,
	    new_name)
    Object foreign_function_declaration, new_name;
{
    x_note_fn_call(214,72);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(foreign_function_declaration,
		Qname_in_foreign_image);
    SVREF(foreign_function_declaration,FIX((SI_Long)21L)) = new_name;
    return VALUES_1(Nil);
}

/* PUT-FOREIGN-FUNCTION-LINKED-P-WHERE-SLOT-IS-ABSENT */
Object put_foreign_function_linked_p_where_slot_is_absent(foreign_function_declaration,
	    linked_p)
    Object foreign_function_declaration, linked_p;
{
    x_note_fn_call(214,73);
    return VALUES_1(Nil);
}

static Object string_constant_4;   /* "Foreign function \"~a\" has a mismatch in argument count.  ~
				    *               The declaration for this function takes ~a arguments but ~
				    *               the foreign image \"~a\" takes ~a arguments.  ~
				    *               G2 is unable to link the declaration to the foreign image."
				    */

static Object Qargcount_mismatch;  /* argcount-mismatch */

static Object Qunlinked_to_connected_foreign_image;  /* unlinked-to-connected-foreign-image */

/* CHECK-FOREIGN-FUNCTION-FOR-ARGCOUNT-AGREEMENT */
Object check_foreign_function_for_argcount_agreement(foreign_function_declaration,
	    entry_for_foreign_function)
    Object foreign_function_declaration, entry_for_foreign_function;
{
    Object declaration_type_list, declaration_argcount, image_argcount, temp;

    x_note_fn_call(214,74);
    declaration_type_list = ISVREF(foreign_function_declaration,(SI_Long)25L);
    declaration_argcount = length(declaration_type_list);
    image_argcount = ISVREF(entry_for_foreign_function,(SI_Long)3L);
    if (FIXNUM_NE(image_argcount,declaration_argcount)) {
	temp = ISVREF(foreign_function_declaration,(SI_Long)21L);
	if (temp);
	else
	    temp = 
		    get_or_make_up_designation_for_block(foreign_function_declaration);
	notify_user(5,string_constant_4,temp,declaration_argcount,
		ISVREF(ISVREF(entry_for_foreign_function,(SI_Long)6L),
		(SI_Long)4L),image_argcount);
	add_to_frame_note_particulars_list_if_necessary(slot_value_list_3(Qargcount_mismatch,
		declaration_argcount,image_argcount),
		Qunlinked_to_connected_foreign_image,
		foreign_function_declaration);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(T);
}

static Object string_constant_5;   /* "s" */

static Object string_constant_6;   /* "" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_7;   /* "arg ~a is declared as type ~a but ~
				    *                                  image expects type ~a.~%"
				    */

static Object string_constant_8;   /* "Foreign function declaration \"~a\" disagrees with ~
				    *                 foreign image \"~a\" on argument type~a:~%~a ~
				    *                 G2 is unable to link the declaration to the foreign image."
				    */

static Object Qargtype_mismatch;   /* argtype-mismatch */

/* CHECK-FOREIGN-FUNCTION-FOR-ARGTYPE-AGREEMENT */
Object check_foreign_function_for_argtype_agreement(foreign_function_declaration,
	    entry_for_foreign_function)
    Object foreign_function_declaration, entry_for_foreign_function;
{
    Object declaration_type_list, declared_type, ab_loop_list_, image_type;
    Object ab_loop_list__1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_iter_flag_, mismatch_spec_qm, temp, temp_1, temp_2;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object mismatch_item, temp_3;
    SI_Long index_1, bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(214,75);
    declaration_type_list = ISVREF(foreign_function_declaration,(SI_Long)25L);
    declared_type = Nil;
    ab_loop_list_ = declaration_type_list;
    image_type = Nil;
    ab_loop_list__1 = ISVREF(entry_for_foreign_function,(SI_Long)4L);
    index_1 = (SI_Long)1L;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    declared_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    image_type = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    if ( !(CONSP(declared_type) ? EQ(CAR(declared_type),image_type) : 
	    EQ(declared_type,image_type))) {
	ab_loopvar__2 = slot_value_cons_1(slot_value_list_3(FIX(index_1),
		declared_type,image_type),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    mismatch_spec_qm = ab_loopvar_;
    goto end_1;
    mismatch_spec_qm = Qnil;
  end_1:;
    if (mismatch_spec_qm) {
	temp = ISVREF(foreign_function_declaration,(SI_Long)21L);
	if (temp);
	else
	    temp = 
		    get_or_make_up_designation_for_block(foreign_function_declaration);
	temp_1 = ISVREF(ISVREF(entry_for_foreign_function,(SI_Long)6L),
		(SI_Long)4L);
	temp_2 = CDR(mismatch_spec_qm) ? string_constant_5 : string_constant_6;
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
		  mismatch_item = Nil;
		  ab_loop_list_ = mismatch_spec_qm;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  mismatch_item = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  tformat(4,string_constant_7,FIRST(mismatch_item),
			  SECOND(mismatch_item),THIRD(mismatch_item));
		  goto next_loop_1;
		end_loop_1:;
		  temp_3 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	notify_user(5,string_constant_8,temp,temp_1,temp_2,temp_3);
	add_to_frame_note_particulars_list_if_necessary(slot_value_cons_1(Qargtype_mismatch,
		mismatch_spec_qm),Qunlinked_to_connected_foreign_image,
		foreign_function_declaration);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(T);
}

static Object string_constant_9;   /* "Foreign function \"~a\" has a mismatch in return type.  ~
				    *                 The declaration for this function expects a return type ~
				    *                 of ~a but the foreign image \"~a\" will return type ~a. ~
				    *                 G2 is unable to link the declaration to the foreign image."
				    */

static Object Qreturn_type_mismatch;  /* return-type-mismatch */

/* CHECK-FOREIGN-FUNCTION-FOR-RETURN-TYPE-AGREEMENT */
Object check_foreign_function_for_return_type_agreement(foreign_function_declaration,
	    entry_for_foreign_function)
    Object foreign_function_declaration, entry_for_foreign_function;
{
    Object declaration_return_type, image_return_type, temp;

    x_note_fn_call(214,76);
    declaration_return_type = ISVREF(foreign_function_declaration,
	    (SI_Long)26L);
    image_return_type = ISVREF(entry_for_foreign_function,(SI_Long)5L);
    if (EQ(declaration_return_type,image_return_type))
	return VALUES_1(T);
    else {
	temp = ISVREF(foreign_function_declaration,(SI_Long)21L);
	if (temp);
	else
	    temp = 
		    get_or_make_up_designation_for_block(foreign_function_declaration);
	notify_user(5,string_constant_9,temp,declaration_return_type,
		ISVREF(ISVREF(entry_for_foreign_function,(SI_Long)6L),
		(SI_Long)4L),image_return_type);
	add_to_frame_note_particulars_list_if_necessary(slot_value_list_3(Qreturn_type_mismatch,
		declaration_return_type,image_return_type),
		Qunlinked_to_connected_foreign_image,
		foreign_function_declaration);
	return VALUES_1(Nil);
    }
}

/* CHECK-FOREIGN-FUNCTION-FOR-TYPE-AND-COUNT-AGREEMENT */
Object check_foreign_function_for_type_and_count_agreement(foreign_function_declaration,
	    entry_for_foreign_function)
    Object foreign_function_declaration, entry_for_foreign_function;
{
    Object argtype_agreement_p, return_type_agreement_p;

    x_note_fn_call(214,77);
    if (check_foreign_function_for_argcount_agreement(foreign_function_declaration,
	    entry_for_foreign_function)) {
	argtype_agreement_p = 
		check_foreign_function_for_argtype_agreement(foreign_function_declaration,
		entry_for_foreign_function);
	return_type_agreement_p = 
		check_foreign_function_for_return_type_agreement(foreign_function_declaration,
		entry_for_foreign_function);
	if (argtype_agreement_p)
	    return VALUES_1(return_type_agreement_p);
	else
	    return VALUES_1(Nil);
    }
    else {
	check_foreign_function_for_return_type_agreement(foreign_function_declaration,
		entry_for_foreign_function);
	return VALUES_1(Nil);
    }
}

/* REMOVE-UNLINKABILITY-INFO-FROM-FOREIGN-FUNCTION-DECLARATION */
Object remove_unlinkability_info_from_foreign_function_declaration(foreign_function_declaration)
    Object foreign_function_declaration;
{
    Object unlinkable_image_qm;

    x_note_fn_call(214,78);
    delete_frame_note_if_any(Qunlinked_to_unconnected_foreign_image,
	    foreign_function_declaration);
    delete_frame_note_if_any(Qunlinked_to_connected_foreign_image,
	    foreign_function_declaration);
    unlinkable_image_qm = ISVREF(foreign_function_declaration,(SI_Long)23L);
    if (unlinkable_image_qm) {
	ISVREF(foreign_function_declaration,(SI_Long)23L) = Nil;
	return splice_element_out_of_foreign_linking_info(unlinkable_image_qm);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-FOREIGN-FUNCTION-LINKING */
Object update_foreign_function_linking(foreign_function_declaration,
	    entry_for_foreign_function_qm,update_declaration_with_no_entry_p)
    Object foreign_function_declaration, entry_for_foreign_function_qm;
    Object update_declaration_with_no_entry_p;
{
    Object image_info, unlinked_element, icp_push_modify_macro_arg, car_1;
    Object cdr_1, svref_new_value;

    x_note_fn_call(214,79);
    if (update_declaration_with_no_entry_p || entry_for_foreign_function_qm)
	remove_unlinkability_info_from_foreign_function_declaration(foreign_function_declaration);
    image_info = Nil;
    unlinked_element = Nil;
    if (entry_for_foreign_function_qm) {
	image_info = ISVREF(entry_for_foreign_function_qm,(SI_Long)6L);
	unlinked_element = 
		make_element_of_foreign_linking_info_1(foreign_function_declaration,
		image_info);
	ISVREF(foreign_function_declaration,(SI_Long)23L) = unlinked_element;
    }
    if (entry_for_foreign_function_qm && 
	    check_foreign_function_for_type_and_count_agreement(foreign_function_declaration,
	    entry_for_foreign_function_qm)) {
	ISVREF(foreign_function_declaration,(SI_Long)23L) = Nil;
	reclaim_element_of_foreign_linking_info_1(unlinked_element);
	ISVREF(foreign_function_declaration,(SI_Long)22L) = 
		entry_for_foreign_function_qm;
	icp_push_modify_macro_arg = foreign_function_declaration;
	car_1 = icp_push_modify_macro_arg;
	cdr_1 = ISVREF(entry_for_foreign_function_qm,(SI_Long)7L);
	svref_new_value = icp_cons_1(car_1,cdr_1);
	SVREF(entry_for_foreign_function_qm,FIX((SI_Long)7L)) = 
		svref_new_value;
	icp_push_modify_macro_arg = 
		copy_frame_serial_number(ISVREF(foreign_function_declaration,
		(SI_Long)3L));
	car_1 = icp_push_modify_macro_arg;
	cdr_1 = ISVREF(entry_for_foreign_function_qm,(SI_Long)8L);
	svref_new_value = icp_cons_1(car_1,cdr_1);
	return VALUES_1(SVREF(entry_for_foreign_function_qm,
		FIX((SI_Long)8L)) = svref_new_value);
    }
    else if (entry_for_foreign_function_qm) {
	ISVREF(foreign_function_declaration,(SI_Long)22L) = Nil;
	return splice_element_into_foreign_linking_info(unlinked_element,
		ISVREF(image_info,(SI_Long)2L));
    }
    else if (update_declaration_with_no_entry_p) {
	add_frame_note(5,Qunlinked_to_unconnected_foreign_image,
		foreign_function_declaration,Nil,T,Nil);
	return VALUES_1(ISVREF(foreign_function_declaration,(SI_Long)22L) 
		= Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* PUT-NAME-IN-FOREIGN-IMAGE */
Object put_name_in_foreign_image(foreign_function_declaration,value,
	    gensymed_symbol)
    Object foreign_function_declaration, value, gensymed_symbol;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_2, entry_hash;
    SI_Long gensymed_symbol_1, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(214,80);
    if ( !TRUEP(Reading_kb_p)) {
	gensymed_symbol_1 = IFIX(sxhashw(value));
	temp = Foreign_function_registry;
	temp_1 = gensymed_symbol_1 % (SI_Long)131L;
	temp = SVREF(temp,FIX(temp_1));
	skip_list = CDR(temp);
	key_value = value;
	key_hash_value = gensymed_symbol_1;
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
		key_hash_value &&  !TRUEP(string_eq_w(key_value,
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
	update_foreign_function_linking(foreign_function_declaration,
		IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(string_eq_w(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil,T);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(foreign_function_declaration,
		Qname_in_foreign_image);
    return VALUES_1(SVREF(foreign_function_declaration,FIX((SI_Long)21L)) 
	    = value);
}

/* LINK-COMPLETED-FOREIGN-FUNCTION-DECLARATIONS */
Object link_completed_foreign_function_declarations()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1;
    Object foreign_function_declaration, temp_1, gensymed_symbol, temp_2;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_4;
    Object entry_hash;
    SI_Long gensymed_symbol_1, temp_3, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,81);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    foreign_function_declaration = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qforeign_function_declaration);
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
      foreign_function_declaration = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      temp_1 = foreign_function_declaration;
      gensymed_symbol = ISVREF(foreign_function_declaration,(SI_Long)21L);
      gensymed_symbol_1 = IFIX(sxhashw(gensymed_symbol));
      temp_2 = Foreign_function_registry;
      temp_3 = gensymed_symbol_1 % (SI_Long)131L;
      temp_2 = SVREF(temp_2,FIX(temp_3));
      skip_list = CDR(temp_2);
      key_value = gensymed_symbol;
      key_hash_value = gensymed_symbol_1;
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
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_3:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_4 = ATOMIC_REF_OBJECT(reference);
      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_4,temp_2);
      MVS_2(result,succ,marked);
    next_loop_4:
      if ( !TRUEP(marked))
	  goto end_loop_3;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_4 = ATOMIC_REF_OBJECT(reference);
      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_4,temp_2);
      MVS_2(result,succ,marked);
      goto next_loop_4;
    end_loop_3:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !TRUEP(string_eq_w(key_value,ISVREF(curr,
	      (SI_Long)2L)))) {
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
      update_foreign_function_linking(temp_1,IFIX(ISVREF(curr,
	      (SI_Long)1L)) == key_hash_value ? (string_eq_w(key_value,
	      ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
	       Nil,T);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_10;  /* "this declaration is not linked to any foreign image" */

/* WRITE-UNLINKED-TO-UNCONNECTED-FOREIGN-IMAGE-NOTE */
Object write_unlinked_to_unconnected_foreign_image_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(214,82);
    GENSYM_RETURN_ONE(tformat(1,string_constant_10));
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* "this foreign function declaration cannot link to the foreign image " */

static Object string_constant_12;  /* "\"~a\" " */

static Object string_constant_13;  /* "because" */

static Object string_constant_14;  /* ":~%" */

static Object string_constant_15;  /* " " */

static Object string_constant_16;  /* "(~a) " */

static Object string_constant_17;  /* "the declaration has ~a arguments ~
				    *                     but the image expects ~a arguments"
				    */

static Object string_constant_18;  /* ";~%" */

static Object string_constant_19;  /* "the declaration argument #~a is of type ~a ~
				    *                         but the image expects type ~a"
				    */

static Object string_constant_20;  /* "the declaration specifies a return type of ~a ~
				    *                     but the image will return type ~a"
				    */

/* WRITE-UNLINKED-TO-CONNECTED-FOREIGN-IMAGE-NOTE */
Object write_unlinked_to_connected_foreign_image_note(unlinkable_reasons,
	    declaration)
    Object unlinkable_reasons, declaration;
{
    Object first_reason, unlinkable_element_qm, image_info_qm, enumerate_p;
    Object reason_type, particulars_spec, ab_loop_list_, unlinkable_cons;
    Object final_outer_entry_p, index_1, ab_loop_iter_flag_, ab_loop_desetq_;
    Object gensymed_symbol, declaration_argcount, image_argcount;
    Object argument_number, declaration_type, image_type, ab_loop_list__1;
    Object particulars_cons, final_inner_entry_p, temp;
    Object declaration_return_type, image_return_type;
    SI_Long number_of_notes_written, incff_1_arg;
    SI_Long frame_note_index_skip_new_value;

    x_note_fn_call(214,83);
    first_reason = FIRST(unlinkable_reasons);
    tformat(1,string_constant_11);
    unlinkable_element_qm = ISVREF(declaration,(SI_Long)23L);
    if (unlinkable_element_qm) {
	image_info_qm = ISVREF(unlinkable_element_qm,(SI_Long)2L);
	if (image_info_qm)
	    tformat(2,string_constant_12,ISVREF(image_info_qm,(SI_Long)4L));
    }
    tformat(1,string_constant_13);
    enumerate_p = CDR(unlinkable_reasons);
    if (enumerate_p);
    else
	enumerate_p = EQ(Qargtype_mismatch,FIRST(first_reason)) ? 
		CDDR(first_reason) : Qnil;
    if (enumerate_p)
	tformat(1,string_constant_14);
    else
	tformat(1,string_constant_15);
    reason_type = Nil;
    particulars_spec = Nil;
    ab_loop_list_ = unlinkable_reasons;
    unlinkable_cons = unlinkable_reasons;
    final_outer_entry_p = Nil;
    index_1 = FIXNUM_SUB1(Frame_note_index);
    number_of_notes_written = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    reason_type = CAR(ab_loop_desetq_);
    particulars_spec = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	unlinkable_cons = M_CDR(unlinkable_cons);
    if ( !TRUEP(unlinkable_cons))
	goto end_loop;
    final_outer_entry_p =  !TRUEP(CDR(unlinkable_cons)) ? T : Nil;
    if ( !TRUEP(ab_loop_iter_flag_))
	number_of_notes_written = number_of_notes_written + (SI_Long)1L;
    if (EQ(reason_type,Qargcount_mismatch)) {
	gensymed_symbol = particulars_spec;
	declaration_argcount = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	image_argcount = CAR(gensymed_symbol);
	if (enumerate_p) {
	    index_1 = FIXNUM_ADD1(index_1);
	    tformat(2,string_constant_16,index_1);
	}
	tformat(3,string_constant_17,declaration_argcount,image_argcount);
	if ( !TRUEP(final_outer_entry_p))
	    tformat(1,string_constant_18);
    }
    else if (EQ(reason_type,Qargtype_mismatch)) {
	argument_number = Nil;
	declaration_type = Nil;
	image_type = Nil;
	ab_loop_list__1 = particulars_spec;
	particulars_cons = particulars_spec;
	final_inner_entry_p = Nil;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	argument_number = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	declaration_type = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	image_type = CAR(temp);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_iter_flag_))
	    particulars_cons = M_CDR(particulars_cons);
	if ( !TRUEP(particulars_cons))
	    goto end_loop_1;
	final_inner_entry_p =  !TRUEP(CDR(particulars_cons)) ? T : Nil;
	if (enumerate_p) {
	    index_1 = FIXNUM_ADD1(index_1);
	    tformat(2,string_constant_16,index_1);
	}
	tformat(4,string_constant_19,argument_number,declaration_type,
		image_type);
	if ( !(final_outer_entry_p && final_inner_entry_p))
	    tformat(1,string_constant_18);
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:;
    }
    else if (EQ(reason_type,Qreturn_type_mismatch)) {
	gensymed_symbol = particulars_spec;
	declaration_return_type = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	image_return_type = CAR(gensymed_symbol);
	if (enumerate_p) {
	    index_1 = FIXNUM_ADD1(index_1);
	    tformat(2,string_constant_16,index_1);
	}
	tformat(3,string_constant_20,declaration_return_type,
		image_return_type);
	if ( !TRUEP(final_outer_entry_p))
	    tformat(1,string_constant_18);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    incff_1_arg = number_of_notes_written;
    frame_note_index_skip_new_value = IFIX(Frame_note_index_skip) + 
	    incff_1_arg;
    Frame_note_index_skip = FIX(frame_note_index_skip_new_value);
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-FOREIGN-FUNCTION-DECLARATION */
Object put_box_translation_and_text_slot_value_for_foreign_function_declaration(foreign_function_declaration,
	    new_value,initializing_qm)
    Object foreign_function_declaration, new_value, initializing_qm;
{
    Object name, old_box_translation_and_text, old_name_qm;

    x_note_fn_call(214,84);
    name = FIFTH( !EQ(new_value,No_value) ? CAR(new_value) : Nil);
    old_box_translation_and_text = ISVREF(foreign_function_declaration,
	    (SI_Long)16L);
    old_name_qm =  !EQ(CAR(old_box_translation_and_text),No_value) ? 
	    FIFTH(CAR(old_box_translation_and_text)) : Nil;
    if (old_name_qm)
	delete_as_frame_with_name(foreign_function_declaration,old_name_qm);
    if (name)
	add_as_frame_with_name(foreign_function_declaration,name);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(foreign_function_declaration,
		Qbox_translation_and_text);
    SVREF(foreign_function_declaration,FIX((SI_Long)16L)) = new_value;
    if ( !TRUEP(initializing_qm))
	update_frame_status(foreign_function_declaration,Nil,Nil);
    return VALUES_2(new_value,Nil);
}

/* CLEANUP-FOR-FOREIGN-FUNCTION-DECLARATION */
Object cleanup_for_foreign_function_declaration(foreign_function_declaration)
    Object foreign_function_declaration;
{
    Object frame, sub_vector_qm, method_function_qm, unlinkable_info_qm;
    Object old_box_translation_and_text, old_name_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,85);
    frame = foreign_function_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qforeign_function_declaration)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    ISVREF(foreign_function_declaration,(SI_Long)22L) = Nil;
    unlinkable_info_qm = ISVREF(foreign_function_declaration,(SI_Long)23L);
    if (unlinkable_info_qm) {
	splice_element_out_of_foreign_linking_info(unlinkable_info_qm);
	ISVREF(foreign_function_declaration,(SI_Long)23L) = Nil;
    }
    old_box_translation_and_text = ISVREF(foreign_function_declaration,
	    (SI_Long)16L);
    old_name_qm =  !EQ(CAR(old_box_translation_and_text),No_value) ? 
	    FIFTH(CAR(old_box_translation_and_text)) : Nil;
    if (old_name_qm)
	return delete_as_frame_with_name(foreign_function_declaration,
		old_name_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-LIST-OF-FOREIGN-FUNCTION-REGISTRATIONS */
Object reclaim_list_of_foreign_function_registrations(list_of_foreign_function_registrations)
    Object list_of_foreign_function_registrations;
{
    Object foreign_name, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(214,86);
    foreign_name = Nil;
    ab_loop_list_ = list_of_foreign_function_registrations;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    foreign_name = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_text_string(foreign_name);
    goto next_loop;
  end_loop:;
    reclaim_icp_tree_1(list_of_foreign_function_registrations);
    return VALUES_1(Nil);
}

static Object Qlist_of_foreign_function_registrations_qm;  /* list-of-foreign-function-registrations? */

static Object string_constant_21;  /* "[value]" */

static Object Qvalue;              /* value */

/* READ-ICP-LIST-OF-FOREIGN-FUNCTION-REGISTRATIONS? */
Object read_icp_list_of_foreign_function_registrations_qm()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, raw_foreign_name, temp;
    Object foreign_name, foreign_id, argument_count, ab_loopvar__3;
    Object ab_loopvar__4, type_list, return_type, gensymed_symbol;
    Object gensymed_symbol_1, result_of_read;
    SI_Long index_1, ab_loop_bind_, index_2, ab_loop_bind__1;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,87);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,
		    Qlist_of_foreign_function_registrations_qm,
		    string_constant_21,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  index_1 = (SI_Long)1L;
	  ab_loop_bind_ = IFIX(read_icp_integer());
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if (index_1 > ab_loop_bind_)
	      goto end_loop;
	  raw_foreign_name = read_icp_text_string();
	  temp = copy_text_string(raw_foreign_name);
	  reclaim_text_string(raw_foreign_name);
	  foreign_name = temp;
	  foreign_id = read_icp_integer();
	  argument_count = read_icp_integer();
	  index_2 = (SI_Long)1L;
	  ab_loop_bind__1 = IFIX(argument_count);
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	next_loop_1:
	  if (index_2 > ab_loop_bind__1)
	      goto end_loop_1;
	  ab_loopvar__4 = icp_cons_1(read_icp_integer(),Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
	  index_2 = index_2 + (SI_Long)1L;
	  goto next_loop_1;
	end_loop_1:
	  type_list = ab_loopvar__2;
	  goto end_1;
	  type_list = Qnil;
	end_1:;
	  return_type = read_icp_integer();
	  gensymed_symbol = make_icp_list_1(FIX((SI_Long)5L));
	  gensymed_symbol_1 = gensymed_symbol;
	  M_CAR(gensymed_symbol_1) = foreign_name;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = foreign_id;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = argument_count;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = type_list;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = return_type;
	  ab_loopvar__2 = icp_cons_1(gensymed_symbol,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  result_of_read = ab_loopvar_;
	  goto end_2;
	  result_of_read = Qnil;
	end_2:;
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qlist_of_foreign_function_registrations_qm,
		      string_constant_21,Qvalue,T,result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else {
	index_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(read_icp_integer());
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if (index_1 > ab_loop_bind_)
	    goto end_loop_2;
	raw_foreign_name = read_icp_text_string();
	temp = copy_text_string(raw_foreign_name);
	reclaim_text_string(raw_foreign_name);
	foreign_name = temp;
	foreign_id = read_icp_integer();
	argument_count = read_icp_integer();
	index_2 = (SI_Long)1L;
	ab_loop_bind__1 = IFIX(argument_count);
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
      next_loop_3:
	if (index_2 > ab_loop_bind__1)
	    goto end_loop_3;
	ab_loopvar__4 = icp_cons_1(read_icp_integer(),Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	index_2 = index_2 + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:
	type_list = ab_loopvar__2;
	goto end_3;
	type_list = Qnil;
      end_3:;
	return_type = read_icp_integer();
	gensymed_symbol = make_icp_list_1(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = foreign_name;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = foreign_id;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = argument_count;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = type_list;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = return_type;
	ab_loopvar__2 = icp_cons_1(gensymed_symbol,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

/* WRITE-ICP-LIST-OF-FOREIGN-FUNCTION-REGISTRATIONS? */
Object write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm)
    Object list_of_foreign_function_registrations_qm;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,88);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,
		    Qlist_of_foreign_function_registrations_qm,
		    string_constant_21,Qvalue,T,
		    list_of_foreign_function_registrations_qm,Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  result_of_write = Nil;
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qlist_of_foreign_function_registrations_qm,
		      string_constant_21,Qvalue,Nil,Nil,Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qforeign_function_argument;  /* foreign-function-argument */

static Object Qwrite_icp_foreign_function_argument;  /* write-icp-foreign-function-argument */

static Object string_constant_22;  /* "resumable icp synch error: ~S expected, ~S found" */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* WRITE-ICP-FOREIGN-FUNCTION-ARGUMENT */
Object write_icp_foreign_function_argument(foreign_function_argument)
    Object foreign_function_argument;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object evaluation_integer, result_of_write, evaluation_text;
    Object evaluation_symbol, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object test, value, v1, v2, v3, evaluation_float_1;
    char temp_1;
    double evaluation_float, temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,89);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qforeign_function_argument,
			string_constant_21,Qvalue,T,
			foreign_function_argument,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if (FIXNUMP(foreign_function_argument)) {
		  evaluation_integer = foreign_function_argument;
		  write_icp_byte(Foreign_function_integer_type_tag);
		  result_of_write = write_icp_integer(evaluation_integer);
	      }
	      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(foreign_function_argument) 
		      != (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(foreign_function_argument)) 
		      == (SI_Long)1L) {
		  evaluation_float = 
			  DFLOAT_ISAREF_1(foreign_function_argument,
			  (SI_Long)0L);
		  write_icp_byte(Foreign_function_real_type_tag);
		  result_of_write = write_icp_double_float_1(evaluation_float);
	      }
	      else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(foreign_function_argument) 
		      != (SI_Long)0L) {
		  evaluation_text = foreign_function_argument;
		  write_icp_byte(Foreign_function_text_type_tag);
		  result_of_write = write_icp_text_string(evaluation_text);
	      }
	      else if (foreign_function_argument && 
		      SYMBOLP(foreign_function_argument)) {
		  evaluation_symbol = foreign_function_argument;
		  write_icp_byte(Foreign_function_symbol_type_tag);
		  result_of_write = 
			  write_icp_text_string(symbol_name_text_string(evaluation_symbol));
	      }
	      else
		  result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qforeign_function_argument,string_constant_21,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if (FIXNUMP(foreign_function_argument)) {
	    evaluation_integer = foreign_function_argument;
	    write_icp_byte(Foreign_function_integer_type_tag);
	    temp = write_icp_integer(evaluation_integer);
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(foreign_function_argument) 
		!= (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(foreign_function_argument)) 
		== (SI_Long)1L) {
	    evaluation_float = DFLOAT_ISAREF_1(foreign_function_argument,
		    (SI_Long)0L);
	    write_icp_byte(Foreign_function_real_type_tag);
	    temp = write_icp_double_float_1(evaluation_float);
	}
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(foreign_function_argument) 
		!= (SI_Long)0L) {
	    evaluation_text = foreign_function_argument;
	    write_icp_byte(Foreign_function_text_type_tag);
	    temp = write_icp_text_string(evaluation_text);
	}
	else if (foreign_function_argument && 
		SYMBOLP(foreign_function_argument)) {
	    evaluation_symbol = foreign_function_argument;
	    write_icp_byte(Foreign_function_symbol_type_tag);
	    temp = 
		    write_icp_text_string(symbol_name_text_string(evaluation_symbol));
	}
	else
	    temp = Qnil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_foreign_function_argument,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qwrite_icp_foreign_function_argument,top,Nil);
		goto end_write_icp_foreign_function_argument;
	    }
	}
	foreign_function_argument = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : foreign_function_argument;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qforeign_function_argument,
			string_constant_21,Qvalue,T,
			foreign_function_argument,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qtrue) : 
			  FIXNUMP(foreign_function_argument)) {
		  evaluation_integer = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : foreign_function_argument;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp = resumable_icp_pop();
		      if (! !(FIXNUMP(temp) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			      FIXNUM_LE(temp,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp)) {
			    case 1:
			      goto l1;
			      break;
			    case 2:
			      goto l2;
			      break;
			    default:
			      break;
			  }
		  }
		l1:
		  if (EQ(icp_suspend_1,
			  write_icp_byte(Foreign_function_integer_type_tag))) {
		      resumable_icp_push(FIX((SI_Long)1L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block;
		  }
		l2:
		  value = write_icp_integer(evaluation_integer);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block;
		  }
		  result = VALUES_1(value);
		  goto end_block;
		end_block:
		  MVS_3(result,v1,v2,v3);
		  if (EQ(icp_suspend_1,v1)) {
		      resumable_icp_push(evaluation_integer);
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(foreign_function_argument);
		      resumable_icp_push(Qwrite_icp_foreign_function_argument);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_foreign_function_argument;
		  }
		  temp = v1;
		  result_of_write = temp;
	      }
	      else {
		  test = Nil;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      test = resumable_icp_pop();
		      temp_1 = TRUEP(test);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ? EQ(test,Qtrue) : 
			  INLINE_DOUBLE_FLOAT_VECTOR_P(foreign_function_argument) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(foreign_function_argument)) 
			  == (SI_Long)1L) {
		      evaluation_float_1 = (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			      ? resumable_icp_pop() : 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(foreign_function_argument,
			      (SI_Long)0L));
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  temp = resumable_icp_pop();
			  if (! !(FIXNUMP(temp) && 
				  FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L))))
			      switch (INTEGER_TO_CHAR(temp)) {
				case 1:
				  goto l1_1;
				  break;
				case 2:
				  goto l2_1;
				  break;
				default:
				  break;
			      }
		      }
		    l1_1:
		      if (EQ(icp_suspend_1,
			      write_icp_byte(Foreign_function_real_type_tag))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block_1;
		      }
		    l2_1:
		      temp_2 = DOUBLE_FLOAT_TO_DOUBLE(evaluation_float_1);
		      value = write_icp_double_float_1(temp_2);
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block_1;
		      }
		      result = VALUES_1(value);
		      goto end_block_1;
		    end_block_1:
		      MVS_3(result,v1,v2,v3);
		      if (EQ(icp_suspend_1,v1)) {
			  resumable_icp_push(evaluation_float_1);
			  resumable_icp_push(Qtrue);
			  resumable_icp_push(Qfalse);
			  resumable_icp_push(foreign_function_argument);
			  resumable_icp_push(Qwrite_icp_foreign_function_argument);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_write_icp_foreign_function_argument;
		      }
		      temp = v1;
		      result_of_write = temp;
		  }
		  else {
		      test = Nil;
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  test = resumable_icp_pop();
			  temp_1 = TRUEP(test);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1 ? EQ(test,Qtrue) : 
			      INLINE_UNSIGNED_BYTE_16_VECTOR_P(foreign_function_argument) 
			      != (SI_Long)0L) {
			  evaluation_text = (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()) 
				  ? resumable_icp_pop() : 
				  foreign_function_argument;
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      temp = resumable_icp_pop();
			      if (! !(FIXNUMP(temp) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),temp) 
				      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
				  switch (INTEGER_TO_CHAR(temp)) {
				    case 1:
				      goto l1_2;
				      break;
				    case 2:
				      goto l2_2;
				      break;
				    default:
				      break;
				  }
			  }
			l1_2:
			  if (EQ(icp_suspend_1,
				  write_icp_byte(Foreign_function_text_type_tag))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_2;
			  }
			l2_2:
			  value = write_icp_text_string(evaluation_text);
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_2;
			  }
			  result = VALUES_1(value);
			  goto end_block_2;
			end_block_2:
			  MVS_3(result,v1,v2,v3);
			  if (EQ(icp_suspend_1,v1)) {
			      resumable_icp_push(evaluation_text);
			      resumable_icp_push(Qtrue);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(foreign_function_argument);
			      resumable_icp_push(Qwrite_icp_foreign_function_argument);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_write_icp_foreign_function_argument;
			  }
			  temp = v1;
			  result_of_write = temp;
		      }
		      else if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) || 
			      foreign_function_argument && 
			      SYMBOLP(foreign_function_argument)) {
			  evaluation_symbol = (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()) 
				  ? resumable_icp_pop() : 
				  foreign_function_argument;
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      temp = resumable_icp_pop();
			      if (! !(FIXNUMP(temp) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),temp) 
				      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
				  switch (INTEGER_TO_CHAR(temp)) {
				    case 1:
				      goto l1_3;
				      break;
				    case 2:
				      goto l2_3;
				      break;
				    default:
				      break;
				  }
			  }
			l1_3:
			  if (EQ(icp_suspend_1,
				  write_icp_byte(Foreign_function_symbol_type_tag))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_3;
			  }
			l2_3:
			  value = 
				  write_icp_text_string(symbol_name_text_string(evaluation_symbol));
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_3;
			  }
			  result = VALUES_1(value);
			  goto end_block_3;
			end_block_3:
			  MVS_3(result,v1,v2,v3);
			  if (EQ(icp_suspend_1,v1)) {
			      resumable_icp_push(evaluation_symbol);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(foreign_function_argument);
			      resumable_icp_push(Qwrite_icp_foreign_function_argument);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_write_icp_foreign_function_argument;
			  }
			  temp = v1;
			  result_of_write = temp;
		      }
		      else
			  result_of_write = Qnil;
		  }
	      }
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qforeign_function_argument,string_constant_21,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qtrue) : FIXNUMP(foreign_function_argument)) {
		evaluation_integer = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : foreign_function_argument;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp = resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1_4;
			    break;
			  case 2:
			    goto l2_4;
			    break;
			  default:
			    break;
			}
		}
	      l1_4:
		if (EQ(icp_suspend_1,
			write_icp_byte(Foreign_function_integer_type_tag))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_4;
		}
	      l2_4:
		value = write_icp_integer(evaluation_integer);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_4;
		}
		result = VALUES_1(value);
		goto end_block_4;
	      end_block_4:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    resumable_icp_push(evaluation_integer);
		    resumable_icp_push(Qtrue);
		    resumable_icp_push(foreign_function_argument);
		    resumable_icp_push(Qwrite_icp_foreign_function_argument);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_foreign_function_argument;
		}
		temp = v1;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : 
			INLINE_DOUBLE_FLOAT_VECTOR_P(foreign_function_argument) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(foreign_function_argument)) 
			== (SI_Long)1L) {
		    evaluation_float_1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(foreign_function_argument,
			    (SI_Long)0L));
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp = resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1_5;
				break;
			      case 2:
				goto l2_5;
				break;
			      default:
				break;
			    }
		    }
		  l1_5:
		    if (EQ(icp_suspend_1,
			    write_icp_byte(Foreign_function_real_type_tag))) {
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_5;
		    }
		  l2_5:
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(evaluation_float_1);
		    value = write_icp_double_float_1(temp_2);
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			goto end_block_5;
		    }
		    result = VALUES_1(value);
		    goto end_block_5;
		  end_block_5:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			resumable_icp_push(evaluation_float_1);
			resumable_icp_push(Qtrue);
			resumable_icp_push(Qfalse);
			resumable_icp_push(foreign_function_argument);
			resumable_icp_push(Qwrite_icp_foreign_function_argument);
			result = VALUES_1(Icp_suspend);
			goto end_write_icp_foreign_function_argument;
		    }
		    temp = v1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			test = resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qtrue) : 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(foreign_function_argument) 
			    != (SI_Long)0L) {
			evaluation_text = (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()) 
				? resumable_icp_pop() : 
				foreign_function_argument;
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    temp = resumable_icp_pop();
			    if (! !(FIXNUMP(temp) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp)) {
				  case 1:
				    goto l1_6;
				    break;
				  case 2:
				    goto l2_6;
				    break;
				  default:
				    break;
				}
			}
		      l1_6:
			if (EQ(icp_suspend_1,
				write_icp_byte(Foreign_function_text_type_tag))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_6;
			}
		      l2_6:
			value = write_icp_text_string(evaluation_text);
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_6;
			}
			result = VALUES_1(value);
			goto end_block_6;
		      end_block_6:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    resumable_icp_push(evaluation_text);
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(foreign_function_argument);
			    resumable_icp_push(Qwrite_icp_foreign_function_argument);
			    result = VALUES_1(Icp_suspend);
			    goto end_write_icp_foreign_function_argument;
			}
			temp = v1;
		    }
		    else if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) || 
			    foreign_function_argument && 
			    SYMBOLP(foreign_function_argument)) {
			evaluation_symbol = (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()) 
				? resumable_icp_pop() : 
				foreign_function_argument;
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    temp = resumable_icp_pop();
			    if (! !(FIXNUMP(temp) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp)) {
				  case 1:
				    goto l1_7;
				    break;
				  case 2:
				    goto l2_7;
				    break;
				  default:
				    break;
				}
			}
		      l1_7:
			if (EQ(icp_suspend_1,
				write_icp_byte(Foreign_function_symbol_type_tag))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_7;
			}
		      l2_7:
			value = 
				write_icp_text_string(symbol_name_text_string(evaluation_symbol));
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_7;
			}
			result = VALUES_1(value);
			goto end_block_7;
		      end_block_7:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    resumable_icp_push(evaluation_symbol);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(foreign_function_argument);
			    resumable_icp_push(Qwrite_icp_foreign_function_argument);
			    result = VALUES_1(Icp_suspend);
			    goto end_write_icp_foreign_function_argument;
			}
			temp = v1;
		    }
		    else
			temp = Qnil;
		}
	    }
	}
    }
    result = VALUES_1(temp);
  end_write_icp_foreign_function_argument:
    return result;
}

static Object Qread_icp_foreign_function_argument;  /* read-icp-foreign-function-argument */

/* READ-ICP-FOREIGN-FUNCTION-ARGUMENT */
Object read_icp_foreign_function_argument()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(214,90);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qforeign_function_argument,
			string_constant_21,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qforeign_function_argument,string_constant_21,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_foreign_function_argument,top))
		return icp_error_internal(Qerror,string_constant_22,
			Qread_icp_foreign_function_argument,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qforeign_function_argument,
			string_constant_21,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qforeign_function_argument,string_constant_21,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qforeign_function_value;  /* foreign-function-value */

static Object Qfloat_array;        /* float-array */

static Object Qread_icp_foreign_function_value;  /* read-icp-foreign-function-value */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* READ-ICP-FOREIGN-FUNCTION-VALUE */
Object read_icp_foreign_function_value()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, type_tag;
    Object temp, result_of_read, amf_available_array_cons_qm, amf_array;
    Object temp_1, amf_result, new_float, temp_2, resumable_icp_state_1;
    Object icp_suspend_1, top, value, key, arg1;
    double aref_new_value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,91);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qforeign_function_value,
			string_constant_21,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      type_tag = read_icp_byte();
	      temp = Current_foreign_function_call_info;
	      SVREF(temp,FIX((SI_Long)3L)) = type_tag;
	      if ( !(FIXNUMP(type_tag) && FIXNUM_LE(FIX((SI_Long)-128L),
		      type_tag) && FIXNUM_LE(type_tag,FIX((SI_Long)127L))))
		  result_of_read = Nil;
	      else
		  switch (INTEGER_TO_CHAR(type_tag)) {
		    case 1:
		      result_of_read = read_icp_fixnum();
		      break;
		    case 6:
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp = Vector_of_simple_float_array_pools;
			  temp_1 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_float_array_conses_tail_vector,
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
		      aref_new_value = read_icp_double_float_1();
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      result_of_read = new_float;
		      break;
		    case 3:
		      result_of_read = intern_text_string(1,
			      read_icp_text_string());
		      break;
		    case 4:
		      result_of_read = read_icp_text_string();
		      break;
		    default:
		      result_of_read = Nil;
		      break;
		  }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qforeign_function_value,string_constant_21,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp_2 = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    type_tag = read_icp_byte();
	    temp = Current_foreign_function_call_info;
	    SVREF(temp,FIX((SI_Long)3L)) = type_tag;
	    if ( !(FIXNUMP(type_tag) && FIXNUM_LE(FIX((SI_Long)-128L),
		    type_tag) && FIXNUM_LE(type_tag,FIX((SI_Long)127L))))
		temp_2 = Nil;
	    else
		switch (INTEGER_TO_CHAR(type_tag)) {
		  case 1:
		    temp_2 = read_icp_fixnum();
		    break;
		  case 6:
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_1 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = read_icp_double_float_1();
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    temp_2 = new_float;
		    break;
		  case 3:
		    temp_2 = intern_text_string(1,read_icp_text_string());
		    break;
		  case 4:
		    temp_2 = read_icp_text_string();
		    break;
		  default:
		    temp_2 = Nil;
		    break;
		}
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_foreign_function_value,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qread_icp_foreign_function_value,top,Nil);
		goto end_read_icp_foreign_function_value;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qforeign_function_value,
			string_constant_21,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  type_tag = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_foreign_function_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_foreign_function_value;
		  }
		  type_tag = value;
	      }
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))) {
		  temp = Current_foreign_function_call_info;
		  SVREF(temp,FIX((SI_Long)3L)) = type_tag;
	      }
	      key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : type_tag;
	      if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		      FIXNUM_LE(key,FIX((SI_Long)127L))))
		  result_of_read = Nil;
	      else
		  switch (INTEGER_TO_CHAR(key)) {
		    case 1:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  value = read_icp_fixnum();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(key);
			      resumable_icp_push(type_tag);
			      resumable_icp_push(Qread_icp_foreign_function_value);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_foreign_function_value;
			  }
			  arg1 = value;
		      }
		      result_of_read = arg1;
		      break;
		    case 6:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  value_1 = read_icp_double_float_1();
			  if (EQ(icp_suspend_1,
				  DOUBLE_TO_DOUBLE_FLOAT(value_1))) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(key);
			      resumable_icp_push(type_tag);
			      resumable_icp_push(Qread_icp_foreign_function_value);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_foreign_function_value;
			  }
			  arg1 = DOUBLE_TO_DOUBLE_FLOAT(value_1);
		      }
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp = Vector_of_simple_float_array_pools;
			  temp_1 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_float_array_conses_tail_vector,
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
		      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(arg1);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      result_of_read = new_float;
		      break;
		    case 3:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()))
			      arg1 = resumable_icp_pop();
			  else {
			      value = read_icp_text_string();
			      if (EQ(icp_suspend_1,value)) {
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(key);
				  resumable_icp_push(type_tag);
				  resumable_icp_push(Qread_icp_foreign_function_value);
				  result = VALUES_1(Icp_suspend);
				  POP_SPECIAL();
				  goto end_read_icp_foreign_function_value;
			      }
			      arg1 = value;
			  }
			  arg1 = intern_text_string(1,arg1);
		      }
		      result_of_read = arg1;
		      break;
		    case 4:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  value = read_icp_text_string();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(key);
			      resumable_icp_push(type_tag);
			      resumable_icp_push(Qread_icp_foreign_function_value);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_foreign_function_value;
			  }
			  arg1 = value;
		      }
		      result_of_read = arg1;
		      break;
		    default:
		      result_of_read = Nil;
		      break;
		  }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qforeign_function_value,string_constant_21,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp_2 = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		type_tag = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_foreign_function_value);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_foreign_function_value;
		}
		type_tag = value;
	    }
	    if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))) {
		temp = Current_foreign_function_call_info;
		SVREF(temp,FIX((SI_Long)3L)) = type_tag;
	    }
	    key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : type_tag;
	    if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		    FIXNUM_LE(key,FIX((SI_Long)127L))))
		temp_2 = Nil;
	    else
		switch (INTEGER_TO_CHAR(key)) {
		  case 1:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value = read_icp_fixnum();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(type_tag);
			    resumable_icp_push(Qread_icp_foreign_function_value);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_foreign_function_value;
			}
			arg1 = value;
		    }
		    temp_2 = arg1;
		    break;
		  case 6:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value_1 = read_icp_double_float_1();
			if (EQ(icp_suspend_1,
				    DOUBLE_TO_DOUBLE_FLOAT(value_1))) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(type_tag);
			    resumable_icp_push(Qread_icp_foreign_function_value);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_foreign_function_value;
			}
			arg1 = DOUBLE_TO_DOUBLE_FLOAT(value_1);
		    }
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_1 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(arg1);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    temp_2 = new_float;
		    break;
		  case 3:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    arg1 = resumable_icp_pop();
			else {
			    value = read_icp_text_string();
			    if (EQ(icp_suspend_1,value)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(key);
				resumable_icp_push(type_tag);
				resumable_icp_push(Qread_icp_foreign_function_value);
				result = VALUES_1(Icp_suspend);
				goto end_read_icp_foreign_function_value;
			    }
			    arg1 = value;
			}
			arg1 = intern_text_string(1,arg1);
		    }
		    temp_2 = arg1;
		    break;
		  case 4:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value = read_icp_text_string();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(type_tag);
			    resumable_icp_push(Qread_icp_foreign_function_value);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_foreign_function_value;
			}
			arg1 = value;
		    }
		    temp_2 = arg1;
		    break;
		  default:
		    temp_2 = Nil;
		    break;
		}
	}
    }
    result = VALUES_1(temp_2);
  end_read_icp_foreign_function_value:
    return result;
}

static Object Qwrite_icp_foreign_function_value;  /* write-icp-foreign-function-value */

/* WRITE-ICP-FOREIGN-FUNCTION-VALUE */
Object write_icp_foreign_function_value(foreign_function_value)
    Object foreign_function_value;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(214,92);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qforeign_function_value,
			string_constant_21,Qvalue,T,foreign_function_value,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qforeign_function_value,string_constant_21,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_foreign_function_value,top))
		return icp_error_internal(Qerror,string_constant_22,
			Qwrite_icp_foreign_function_value,top,Nil);
	}
	foreign_function_value = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : foreign_function_value;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qforeign_function_value,
			string_constant_21,Qvalue,T,foreign_function_value,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qforeign_function_value,string_constant_21,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* GET-OR-CREATE-FOREIGN-FUNCTION-IMAGE-INDEX */
Object get_or_create_foreign_function_image_index()
{
    Object icp_pop_store, cons_1, next_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(214,93);
    icp_pop_store = Nil;
    cons_1 = Unused_foreign_image_indices;
    if (cons_1) {
	icp_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qicp);
	if (ISVREF(Available_icp_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_icp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_icp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_icp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Unused_foreign_image_indices = next_cons;
    temp_1 = icp_pop_store;
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	temp = add1(Highest_foreign_image_index);
	Highest_foreign_image_index = temp;
	return VALUES_1(Highest_foreign_image_index);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Tcp_ip_port_offset_for_foreign_images, Qtcp_ip_port_offset_for_foreign_images);

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_image_connection_mode, Qforeign_image_connection_mode);

static Object Qtcp_ip;             /* tcp-ip */

/* INITIALIZE-FOREIGN-IMAGE-CONNECTION-MODE */
Object initialize_foreign_image_connection_mode()
{
    x_note_fn_call(214,94);
    return VALUES_1(Qtcp_ip);
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_tcpip_listener_address_qm, Qcached_tcpip_listener_address_qm);

static Object Kuncached;           /* :uncached */

static Object string_constant_23;  /* "TCP_IP" */

/* GET-NEXT-UNUSED-FOREIGN-IMAGE-PORT-OR-TASK */
Object get_next_unused_foreign_image_port_or_task()
{
    Object unused_index, proposed_port, all_network_addresses, transport;
    Object address, ab_loop_list_, ab_loop_it_, ab_loop_desetq_, temp;
    Object this_transport_address_qm, better_index;

    x_note_fn_call(214,95);
    unused_index = get_or_create_foreign_function_image_index();
    if (EQ(Foreign_image_connection_mode,Qtcp_ip)) {
	proposed_port = add(Tcp_ip_port_offset_for_foreign_images,
		unused_index);
	if (EQ(Cached_tcpip_listener_address_qm,Kuncached)) {
	    all_network_addresses = get_local_host_addresses();
	    transport = Nil;
	    address = Nil;
	    ab_loop_list_ = all_network_addresses;
	    ab_loop_it_ = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    transport = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    address = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = equalw(transport,string_constant_23) ? address : 
		    Qnil;
	    if (ab_loop_it_) {
		this_transport_address_qm = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    this_transport_address_qm = Qnil;
	  end_1:;
	    Cached_tcpip_listener_address_qm = this_transport_address_qm ? 
		    text_string_parse_integer_function(this_transport_address_qm,
		    FIX((SI_Long)0L),Nil,Nil) : Nil;
	    temp = Cached_tcpip_listener_address_qm;
	    reclaim_network_addresses(all_network_addresses);
	}
	else
	    temp = Cached_tcpip_listener_address_qm;
	if (EQUAL(temp,proposed_port)) {
	    better_index = get_or_create_foreign_function_image_index();
	    temp = add(Tcp_ip_port_offset_for_foreign_images,better_index);
	    return VALUES_2(temp,better_index);
	}
	else
	    return VALUES_2(proposed_port,unused_index);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Spawn_command_line_process_failure, Qspawn_command_line_process_failure);

static Object Qwin32;              /* win32 */

static Object string_constant_24;  /* "~s ~a" */

static Object string_constant_25;  /* "~a ~a" */

/* SPAWN-FOREIGN-FUNCTION-IMAGE */
Object spawn_foreign_function_image(image_info,port_or_task,port_or_task_index)
    Object image_info, port_or_task, port_or_task_index;
{
    volatile Object ascii_namestring_of_foreign_image;
    volatile Object command_line;
    Object process_id_or_failure_flag, amf_available_array_cons_qm, amf_array;
    Object temp, temp_1, amf_result, new_float;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(214,96);
    SAVE_STACK();
    SVREF(image_info,FIX((SI_Long)7L)) = port_or_task;
    SVREF(image_info,FIX((SI_Long)8L)) = port_or_task_index;
    if (EQ(Foreign_image_connection_mode,Qtcp_ip)) {
	ascii_namestring_of_foreign_image = Qunbound_in_protected_let;
	command_line = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    ascii_namestring_of_foreign_image = 
		    convert_text_string_to_ascii_filename_as_much_as_possible(ISVREF(image_info,
		    (SI_Long)4L));
	    command_line = tformat_text_string(3,EQ(Local_file_system,
		    Qwin32) ? string_constant_24 : string_constant_25,
		    ascii_namestring_of_foreign_image,ISVREF(image_info,
		    (SI_Long)7L));
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		process_id_or_failure_flag = 
			c_spawn_command_line_process(command_line);
		if (NUM_EQ(process_id_or_failure_flag,
			Spawn_command_line_process_failure))
		    result = VALUES_1(Nil);
		else {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_1 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    DOUBLE_FLOAT_TO_DOUBLE(process_id_or_failure_flag);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    SVREF(image_info,FIX((SI_Long)10L)) = new_float;
		    result = VALUES_1(T);
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    SAVE_VALUES(result);
	}
	POP_UNWIND_PROTECT(0);
	if (command_line) {
	    if ( !EQ(command_line,Qunbound_in_protected_let))
		reclaim_text_string(command_line);
	}
	if (ascii_namestring_of_foreign_image) {
	    if ( !EQ(ascii_namestring_of_foreign_image,
		    Qunbound_in_protected_let))
		reclaim_text_string(ascii_namestring_of_foreign_image);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	result = error((SI_Long)2L,
		"SPAWN-FOREIGN-FUNCTION-IMAGE: Unknown connect mode ~a",
		Foreign_image_connection_mode);
	RESTORE_STACK();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_image_connection_checkup_interval_in_ms, Qforeign_image_connection_checkup_interval_in_ms);

DEFINE_VARIABLE_WITH_SYMBOL(Total_foreign_image_connection_checkup_interval_in_ms, Qtotal_foreign_image_connection_checkup_interval_in_ms);

DEFINE_VARIABLE_WITH_SYMBOL(Ff_connect_finalized, Qff_connect_finalized);

static Object Qsuccess;            /* success */

/* FF-CONNECT-CALLBACK */
Object ff_connect_callback(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(214,97);
    Ff_connect_finalized = Qsuccess;
    return VALUES_1(Nil);
}

static Object Qfailure;            /* failure */

/* HANDLE-FF-CONNECT-FAILURE */
Object handle_ff_connect_failure(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    x_note_fn_call(214,98);
    Ff_connect_finalized = Qfailure;
    return VALUES_1(Nil);
}

static Object Qhandle_ff_connect_failure;  /* handle-ff-connect-failure */

static Object Qff_connect_callback;  /* ff-connect-callback */

/* MAKE-ICP-CONNECTION-TO-FOREIGN-IMAGE */
Object make_icp_connection_to_foreign_image(connection_specification)
    Object connection_specification;
{
    Object scheduler_enabled_qm, ff_connect_finalized;
    Object initial_icp_version_info_enabled_p, icp_connection_qm;
    char display_events_were_enabled;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(214,99);
    SAVE_STACK();
    display_events_were_enabled = (SI_Long)0L != ne_display_events_enabled();
    ne_disable_display_events();
    if (PUSH_UNWIND_PROTECT(0)) {
	scheduler_enabled_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scheduler_enabled_qm,Qscheduler_enabled_qm,scheduler_enabled_qm,
		2);
	  ff_connect_finalized = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Ff_connect_finalized,Qff_connect_finalized,ff_connect_finalized,
		  1);
	    initial_icp_version_info_enabled_p = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Initial_icp_version_info_enabled_p,Qinitial_icp_version_info_enabled_p,initial_icp_version_info_enabled_p,
		    0);
	      icp_connection_qm = make_icp_connection(1,
		      connection_specification);
	      if (icp_connection_qm) {
		  register_icp_connection_loss_callback(Qhandle_ff_connect_failure,
			  icp_connection_qm);
		  setup_network_connection_for_connect(2,icp_connection_qm,
			  Qff_connect_callback);
		next_loop:
		  if (Ff_connect_finalized)
		      goto end_loop;
		  g2_event_cycle_handling_windows_quit();
		  goto next_loop;
		end_loop:
		  if (EQ(Ff_connect_finalized,Qfailure))
		      SAVE_VALUES(VALUES_1(Nil));
		  else {
		      deregister_all_icp_connection_loss_callbacks(icp_connection_qm);
		      SAVE_VALUES(VALUES_1(icp_connection_qm));
		  }
	      }
	      else
		  SAVE_VALUES(VALUES_1(Nil));
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    if (display_events_were_enabled)
	ne_enable_display_events();
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* HANDLE-INTERNAL-FOREIGN-IMAGE-CONNECTION-FAILURE */
Object handle_internal_foreign_image_connection_failure(icp_socket_to_foreign_image,
	    clean_qm)
    Object icp_socket_to_foreign_image, clean_qm;
{
    Object internal_image_info, ab_loop_list_;

    x_note_fn_call(214,100);
    internal_image_info = Nil;
    ab_loop_list_ = All_foreign_function_images_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    internal_image_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(internal_image_info,(SI_Long)5L),
	    icp_socket_to_foreign_image)) {
	SVREF(internal_image_info,FIX((SI_Long)5L)) = Nil;
	kill_foreign_image(internal_image_info);
	goto end_loop;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qhandle_internal_foreign_image_connection_failure;  /* handle-internal-foreign-image-connection-failure */

/* CREATE-FOREIGN-IMAGE-CONNECTION */
Object create_foreign_image_connection(image_info)
    Object image_info;
{
    Object host_name, port_or_task, connection_specification;
    Object icp_connection_qm, temp;

    x_note_fn_call(214,101);
    host_name = copy_text_string(get_local_host_name());
    port_or_task = ISVREF(image_info,(SI_Long)7L);
    connection_specification = EQ(Foreign_image_connection_mode,Qtcp_ip) ? 
	    icp_list_4(Qtcp_ip,host_name,port_or_task,Nil) : Nil;
    icp_connection_qm = 
	    make_icp_connection_to_foreign_image(connection_specification);
    if (icp_connection_qm) {
	SVREF(image_info,FIX((SI_Long)5L)) = icp_connection_qm;
	SVREF(image_info,FIX((SI_Long)6L)) = connection_specification;
	register_icp_connection_loss_callback(Qhandle_internal_foreign_image_connection_failure,
		icp_connection_qm);
	temp = icp_connection_qm;
    }
    else {
	if (text_string_p(host_name))
	    reclaim_text_string(host_name);
	reclaim_icp_list_1(connection_specification);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* HANDLE-EXTERNAL-FOREIGN-IMAGE-CONNECTION-FAILURE */
Object handle_external_foreign_image_connection_failure(icp_socket_to_foreign_image,
	    clean_qm)
    Object icp_socket_to_foreign_image, clean_qm;
{
    Object external_image_info, ab_loop_list_;

    x_note_fn_call(214,102);
    external_image_info = Nil;
    ab_loop_list_ = All_external_foreign_function_images_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    external_image_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(external_image_info,(SI_Long)5L),
	    icp_socket_to_foreign_image)) {
	SVREF(external_image_info,FIX((SI_Long)5L)) = Nil;
	kill_foreign_image(external_image_info);
	goto end_loop;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qhandle_external_foreign_image_connection_failure;  /* handle-external-foreign-image-connection-failure */

/* CREATE-EXTERNAL-FOREIGN-IMAGE-CONNECTION */
Object create_external_foreign_image_connection(image_info,connection_spec)
    Object image_info, connection_spec;
{
    Object icp_connection_qm, temp;

    x_note_fn_call(214,103);
    icp_connection_qm = make_icp_connection_to_foreign_image(connection_spec);
    if (icp_connection_qm) {
	SVREF(image_info,FIX((SI_Long)5L)) = icp_connection_qm;
	SVREF(image_info,FIX((SI_Long)6L)) = connection_spec;
	register_icp_connection_loss_callback(Qhandle_external_foreign_image_connection_failure,
		icp_connection_qm);
	temp = icp_connection_qm;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_retries_for_foreign_image_connection, Qmaximum_retries_for_foreign_image_connection);

DEFINE_VARIABLE_WITH_SYMBOL(Milliseconds_between_retries_for_foreign_image_connection, Qmilliseconds_between_retries_for_foreign_image_connection);

DEFINE_VARIABLE_WITH_SYMBOL(Milliseconds_to_sleep_before_connecting_to_foreign_image, Qmilliseconds_to_sleep_before_connecting_to_foreign_image);

DEFINE_VARIABLE_WITH_SYMBOL(Milliseconds_to_sleep_after_connection_on_pc_platforms, Qmilliseconds_to_sleep_after_connection_on_pc_platforms);

static Object string_constant_26;  /* "G2 could not connect to foreign image \"~a\"." */

static Object string_constant_27;  /* "G2 could not create a process for foreign image \"~a\"." */

/* INITIALIZE-FOREIGN-FUNCTION-IMAGE */
Object initialize_foreign_function_image(image_info)
    Object image_info;
{
    Object connection_succeeded_p, spawn_succeeded_p, failed_socket_indices;
    Object svref_new_value, port_or_task, unused_index, temp;
    SI_Long retry_count, ab_loop_bind_;
    Object result;

    x_note_fn_call(214,104);
    retry_count = IFIX(ISVREF(image_info,(SI_Long)12L));
    ab_loop_bind_ = IFIX(Maximum_retries_for_foreign_image_connection);
    connection_succeeded_p = Nil;
    spawn_succeeded_p = Nil;
    failed_socket_indices = Nil;
  next_loop:
    if (retry_count > ab_loop_bind_)
	goto end_loop;
    svref_new_value = FIXNUM_ADD1(ISVREF(image_info,(SI_Long)12L));
    SVREF(image_info,FIX((SI_Long)12L)) = svref_new_value;
    result = get_next_unused_foreign_image_port_or_task();
    MVS_2(result,port_or_task,unused_index);
    spawn_succeeded_p = spawn_foreign_function_image(image_info,
	    port_or_task,unused_index);
    if (spawn_succeeded_p) {
	g2ext_sys_sleep(IFIX(Milliseconds_between_retries_for_foreign_image_connection));
	if (create_foreign_image_connection(image_info)) {
	    connection_succeeded_p = T;
	    goto end_loop;
	}
	kill_foreign_image_unconditionally(image_info);
    }
    failed_socket_indices = icp_cons_1(unused_index,failed_socket_indices);
    g2ext_sys_sleep(IFIX(Milliseconds_between_retries_for_foreign_image_connection));
    retry_count = retry_count + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (connection_succeeded_p) {
	svref_new_value = nconc2(ISVREF(image_info,(SI_Long)13L),
		failed_socket_indices);
	SVREF(image_info,FIX((SI_Long)13L)) = svref_new_value;
	if (windows_platform_p())
	    g2ext_sys_sleep(IFIX(Milliseconds_to_sleep_after_connection_on_pc_platforms));
    }
    else {
	Unused_foreign_image_indices = nconc2(Unused_foreign_image_indices,
		failed_socket_indices);
	if (spawn_succeeded_p)
	    notify_user(2,string_constant_26,ISVREF(image_info,(SI_Long)4L));
	else
	    notify_user(2,string_constant_27,ISVREF(image_info,(SI_Long)4L));
    }
    temp = connection_succeeded_p;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Tcpip_external_foreign_image_prologue, Qtcpip_external_foreign_image_prologue);

static Object array_constant;      /* # */

/* EXTERNAL-FOREIGN-IMAGE-DISCONNECTION-SPEC-P */
Object external_foreign_image_disconnection_spec_p(choice)
    Object choice;
{
    Object length_1, temp;

    x_note_fn_call(214,105);
    length_1 = length(choice);
    temp = IFIX(length_1) >= (SI_Long)16L ? 
	    gensym_search_complex(array_constant,choice,Nil,
	    SYMBOL_FUNCTION(Qeql),Nil,Nil,FIX((SI_Long)0L),
	    FIX((SI_Long)0L),Nil,FIX((SI_Long)16L)) : Qnil;
    return VALUES_1(temp);
}

static Object array_constant_1;    /* # */

static Object Qlocalnet;           /* localnet */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* TWRITE-ICP-CONNECTION-SPEC */
Object twrite_icp_connection_spec(connection_spec_qm)
    Object connection_spec_qm;
{
    Object transport_type, temp, schar_arg_2, schar_new_value;
    SI_Long thing;

    x_note_fn_call(214,106);
    if (connection_spec_qm) {
	transport_type = FIRST(connection_spec_qm);
	if (EQ(transport_type,Qtcp_ip)) {
	    twrite_general_string(Tcpip_external_foreign_image_prologue);
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = (SI_Long)34L;
		twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = (SI_Long)34L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	    twrite_general_string(SECOND(connection_spec_qm));
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = (SI_Long)34L;
		twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = (SI_Long)34L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	    twrite_beginning_of_wide_string(array_constant_1,
		    FIX((SI_Long)13L));
	    twrite_fixnum(THIRD(connection_spec_qm));
	}
	else if (EQ(transport_type,Qlocalnet))
	    twrite_beginning_of_wide_string(array_constant_2,
		    FIX((SI_Long)14L));
    }
    else
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)4L));
    return VALUES_1(Nil);
}

/* TWRITE-FOREIGN-IMAGE-CONNECTION-SPEC */
Object twrite_foreign_image_connection_spec(connection_spec)
    Object connection_spec;
{
    x_note_fn_call(214,107);
    twrite_icp_connection_spec(connection_spec);
    return VALUES_1(Nil);
}

static Object string_constant_28;  /* "G2 could not connect to external foreign image `~a'." */

/* INITIALIZE-EXTERNAL-FOREIGN-FUNCTION-IMAGE */
Object initialize_external_foreign_function_image(image_info,connection_spec)
    Object image_info, connection_spec;
{
    Object connection_succeeded_p, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object connection_spec_text, temp;
    SI_Long retry_count, ab_loop_bind_, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(214,108);
    retry_count = IFIX(ISVREF(image_info,(SI_Long)12L));
    ab_loop_bind_ = IFIX(Maximum_retries_for_foreign_image_connection);
    connection_succeeded_p = Nil;
  next_loop:
    if (retry_count > ab_loop_bind_)
	goto end_loop;
    if (create_external_foreign_image_connection(image_info,connection_spec)) {
	connection_succeeded_p = T;
	goto end_loop;
    }
    kill_foreign_image_unconditionally(image_info);
    g2ext_sys_sleep(IFIX(Milliseconds_between_retries_for_foreign_image_connection));
    retry_count = retry_count + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (connection_succeeded_p)
	ISVREF(image_info,(SI_Long)12L) = FIX(retry_count);
    else {
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
		  twrite_foreign_image_connection_spec(connection_spec);
		  connection_spec_text = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	notify_user(2,string_constant_28,connection_spec_text);
	reclaim_text_string(connection_spec_text);
    }
    temp = connection_succeeded_p;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qtelewindows;        /* telewindows */

static Object array_constant_4;    /* # */

/* INITIALIZE-FOREIGN-FUNCTION-IMAGE-IF-POSSIBLE */
Object initialize_foreign_function_image_if_possible varargs_1(int, n)
{
    Object image_truename_qm;
    Object retry_count_qm, image_info, temp, current_icp_port;
    Object current_icp_socket, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_varargs_nonrelocating;
    Declare_special(12);
    Object result;

    x_note_fn_call(214,109);
    INIT_ARGS_nonrelocating();
    image_truename_qm = REQUIRED_ARG_nonrelocating();
    retry_count_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    image_info = make_foreign_function_image_info_1();
    SVREF(image_info,FIX((SI_Long)3L)) = image_truename_qm;
    temp = gensym_namestring_as_text_string(1,image_truename_qm);
    SVREF(image_info,FIX((SI_Long)4L)) = temp;
    if (retry_count_qm)
	SVREF(image_info,FIX((SI_Long)12L)) = retry_count_qm;
    if (initialize_foreign_function_image(image_info)) {
	All_foreign_function_images_qm = icp_cons_1(image_info,
		All_foreign_function_images_qm);
	current_icp_port = ISVREF(ISVREF(image_info,(SI_Long)5L),(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    temp = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(temp,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    temp_1 = 
					    send_icp_request_foreign_function_registry(FIX((SI_Long)0L),
					    array_constant_4);
				    end_icp_message_group();
				}
				else
				    temp_1 = Nil;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    temp = ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(temp,(SI_Long)0L,
					    aref_new_value);
				    temp = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(temp,(SI_Long)0L,
					    aref_new_value);
				}
				result = VALUES_1(temp_1);
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
	return result;
    }
    else
	return reclaim_foreign_function_image_info(image_info);
}

static Object string_constant_29;  /* "G2 is already connected to foreign image \"~a\".  ~
				    *                  To overwrite existing foreign functions, you must ~
				    *                  disconnect from this image and then re-connect to it."
				    */

static Object string_constant_30;  /* "Attempt to connect to foreign image  \"~a\".  ~
				    *            This file does not exist."
				    */

/* CONNECT-TO-FOREIGN-IMAGE */
Object connect_to_foreign_image(image_pathname)
    Object image_pathname;
{
    Object image_truename_qm;
    volatile Object namestring_of_connection_attempt;
    Object temp, extant_image_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(214,110);
    SAVE_STACK();
    image_truename_qm = Qunbound_in_protected_let;
    namestring_of_connection_attempt = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	image_truename_qm = gensym_probe_file(image_pathname);
	namestring_of_connection_attempt = 
		gensym_namestring_as_text_string(1,image_pathname);
	reclaim_pathname_or_string(Current_foreign_image_pathname_qm);
	if (text_string_p(image_pathname)) {
	    temp = gensym_pathname(image_pathname);
	    reclaim_text_string(image_pathname);
	    Current_foreign_image_pathname_qm = temp;
	}
	else
	    Current_foreign_image_pathname_qm = image_pathname;
	if (image_truename_qm) {
	    extant_image_qm = 
		    get_foreign_image_info_from_pathname(image_truename_qm);
	    if (extant_image_qm)
		SAVE_VALUES(notify_user(2,string_constant_29,
			ISVREF(extant_image_qm,(SI_Long)4L)));
	    else
		SAVE_VALUES(initialize_foreign_function_image_if_possible(1,
			image_truename_qm));
	}
	else
	    SAVE_VALUES(notify_user(2,string_constant_30,
		    namestring_of_connection_attempt));
    }
    POP_UNWIND_PROTECT(0);
    if (namestring_of_connection_attempt) {
	if ( !EQ(namestring_of_connection_attempt,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_of_connection_attempt);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_31;  /* "G2 is already connected to external foreign image `~a'.  ~
				    *              To overwrite existing foreign functions, you must ~
				    *              disconnect from this image and then re-connect to it."
				    */

/* CONNECT-TO-EXTERNAL-FOREIGN-IMAGE */
Object connect_to_external_foreign_image(connection_spec)
    Object connection_spec;
{
    Object extant_image_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object connection_spec_text, image_info, temp, current_icp_port;
    Object current_icp_socket, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value_1;
    Declare_special(12);
    Object result;

    x_note_fn_call(214,111);
    extant_image_qm = 
	    get_foreign_image_info_from_connection_spec(connection_spec);
    if (extant_image_qm) {
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
		  twrite_foreign_image_connection_spec(connection_spec);
		  connection_spec_text = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	notify_user(2,string_constant_31,connection_spec_text);
	return reclaim_text_string(connection_spec_text);
    }
    else {
	image_info = make_foreign_function_image_info_1();
	SVREF(image_info,FIX((SI_Long)14L)) = T;
	SVREF(image_info,FIX((SI_Long)6L)) = connection_spec;
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
		  twrite_foreign_image_connection_spec(connection_spec);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SVREF(image_info,FIX((SI_Long)4L)) = temp;
	if (initialize_external_foreign_function_image(image_info,
		connection_spec)) {
	    All_external_foreign_function_images_qm = 
		    icp_cons_1(image_info,
		    All_external_foreign_function_images_qm);
	    current_icp_port = ISVREF(ISVREF(image_info,(SI_Long)5L),
		    (SI_Long)4L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    11);
	      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		      10);
		temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)17L ? ISVREF(Current_icp_socket,
			(SI_Long)53L) : Nil;
		if (temp_1);
		else
		    temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			    Qtelewindows) ? T : Nil;
		disable_resumability = temp_1;
		PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			9);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  8);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			    7);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			      6);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				5);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  4);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				    3);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				      2);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					1);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(Writing_icp_message_group);
				  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					  0);
				    gensymed_symbol = Nil;
				    gensymed_symbol_1 = 0.0;
				    gensymed_symbol_2 = 0.0;
				    if (Profiling_enabled_qm) {
					gensymed_symbol = T;
					gensymed_symbol_1 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_2 = 
						g2ext_unix_time_as_float();
					temp = ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					DFLOAT_ISASET_1(temp,(SI_Long)0L,
						gensymed_symbol_2);
				    }
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					temp_1 = 
						send_icp_request_foreign_function_registry(FIX((SI_Long)0L),
						array_constant_4);
					end_icp_message_group();
				    }
				    else
					temp_1 = Nil;
				    if (Profiling_enabled_qm) {
					gensymed_symbol_3 = 
						g2ext_unix_time_as_float();
					gensymed_symbol_4 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_5 = 
						gensymed_symbol_3 - 
						gensymed_symbol_4;
					temp = ISVREF(Profiling_enabled_qm,
						(SI_Long)6L);
					aref_new_value_1 = 
						gensymed_symbol_5 + 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)6L),(SI_Long)0L);
					DFLOAT_ISASET_1(temp,(SI_Long)0L,
						aref_new_value_1);
					temp = ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					aref_new_value_1 = gensymed_symbol 
						? gensymed_symbol_1 + 
						gensymed_symbol_5 + 
						(gensymed_symbol_4 - 
						gensymed_symbol_2) : 
						gensymed_symbol_3;
					DFLOAT_ISASET_1(temp,(SI_Long)0L,
						aref_new_value_1);
				    }
				    result = VALUES_1(temp_1);
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
	    return result;
	}
	else
	    return reclaim_foreign_function_image_info(image_info);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Wait_interval_before_killing_foreign_process, Qwait_interval_before_killing_foreign_process);

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qkill_foreign_image_process_unconditionally;  /* kill-foreign-image-process-unconditionally */

/* KILL-FOREIGN-IMAGE */
Object kill_foreign_image(foreign_image_info)
    Object foreign_image_info;
{
    Object image_socket_qm, external_p, foreign_process_id_qm;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, old, new_1;
    Object def_structure_schedule_task_variable, svref_arg_2, svref_new_value;
    Object task, structure_being_reclaimed;
    SI_Long shutdown_context_flag;
    char svref_new_value_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(214,112);
    image_socket_qm = ISVREF(foreign_image_info,(SI_Long)5L);
    external_p = ISVREF(foreign_image_info,(SI_Long)14L);
    foreign_process_id_qm = external_p ? Nil : ISVREF(foreign_image_info,
	    (SI_Long)10L);
    if (image_socket_qm) {
	shutdown_context_flag = external_p ? 
		IFIX(Shutdown_context_only_flag_set) : 
		IFIX(Shutdown_context_only_flag_clear);
	current_icp_port = ISVREF(image_socket_qm,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_kill_foreign_function_server(FIX(shutdown_context_flag),
					    array_constant_4);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    aref_new_value);
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    aref_new_value);
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
	flush_and_shutdown_icp_socket(image_socket_qm);
	SVREF(foreign_image_info,FIX((SI_Long)5L)) = Nil;
    }
    if (foreign_process_id_qm) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(foreign_image_info,(SI_Long)11L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp_1 = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 
		(double)IFIX(Wait_interval_before_killing_foreign_process);
	DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	temp_1 = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = 
		Qkill_foreign_image_process_unconditionally;
	temp_1 = SYMBOL_FUNCTION(Qkill_foreign_image_process_unconditionally);
	SVREF(task,FIX((SI_Long)8L)) = temp_1;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = foreign_process_id_qm;
	new_1 = task;
	if (CAS_SVREF(foreign_image_info,(SI_Long)11L,old,new_1)) {
	    if (old) {
		if (EQ(old,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(old,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(old);
		inline_note_reclaim_cons(old,Nil);
		structure_being_reclaimed = old;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(old,(SI_Long)9L));
		  SVREF(old,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = old;
	    }
	    future_task_schedule_2(new_1);
	    goto end_1;
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    return reclaim_foreign_function_image_info(foreign_image_info);
}

static Object string_constant_32;  /* "Disconnected from foreign image \"~a\"." */

static Object string_constant_33;  /* "Attempt to disconnect from foreign image \"~a\".  ~
				    *                          G2 was not connected to this image."
				    */

static Object string_constant_34;  /* "Attempt to disconnect from foreign image \"~a\".  ~
				    *               This file does not exist."
				    */

/* DISCONNECT-FROM-FOREIGN-IMAGE */
Object disconnect_from_foreign_image(image_pathname)
    Object image_pathname;
{
    volatile Object image_truename_qm;
    volatile Object namestring_of_disconnection_attempt;
    Object temp, extant_image_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(214,113);
    SAVE_STACK();
    image_truename_qm = Qunbound_in_protected_let;
    namestring_of_disconnection_attempt = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	image_truename_qm = gensym_probe_file(image_pathname);
	namestring_of_disconnection_attempt = 
		gensym_namestring_as_text_string(1,image_pathname);
	reclaim_pathname_or_string(Current_foreign_image_pathname_qm);
	if (text_string_p(image_pathname)) {
	    temp = gensym_pathname(image_pathname);
	    reclaim_text_string(image_pathname);
	    Current_foreign_image_pathname_qm = temp;
	}
	else
	    Current_foreign_image_pathname_qm = image_pathname;
	if (image_truename_qm) {
	    extant_image_qm = 
		    get_foreign_image_info_from_pathname(image_truename_qm);
	    if (extant_image_qm) {
		kill_foreign_image(extant_image_qm);
		notify_user(2,string_constant_32,
			namestring_of_disconnection_attempt);
		SAVE_VALUES(VALUES_1(T));
	    }
	    else {
		notify_user(2,string_constant_33,
			namestring_of_disconnection_attempt);
		SAVE_VALUES(VALUES_1(Nil));
	    }
	}
	else {
	    notify_user(2,string_constant_34,
		    namestring_of_disconnection_attempt);
	    SAVE_VALUES(VALUES_1(Nil));
	}
    }
    POP_UNWIND_PROTECT(0);
    if (namestring_of_disconnection_attempt) {
	if ( !EQ(namestring_of_disconnection_attempt,
		Qunbound_in_protected_let))
	    reclaim_text_string(namestring_of_disconnection_attempt);
    }
    if (image_truename_qm) {
	if ( !EQ(image_truename_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(image_truename_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_35;  /* "Disconnected from external foreign image `~a'." */

static Object string_constant_36;  /* "Attempt to disconnect from external foreign image `~a'.  ~
				    *                 G2 was not connected to this image."
				    */

/* DISCONNECT-FROM-EXTERNAL-FOREIGN-IMAGE */
Object disconnect_from_external_foreign_image(connection_spec)
    Object connection_spec;
{
    Object extant_image_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object connections_spec_text, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(214,114);
    extant_image_qm = 
	    get_foreign_image_info_from_connection_spec(connection_spec);
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
	      twrite_foreign_image_connection_spec(connection_spec);
	      connections_spec_text = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (extant_image_qm) {
	kill_foreign_image(extant_image_qm);
	notify_user(2,string_constant_35,connections_spec_text);
	temp = T;
    }
    else {
	notify_user(2,string_constant_36,connections_spec_text);
	temp = Nil;
    }
    reclaim_text_string(connections_spec_text);
    return VALUES_1(temp);
}

static Object string_constant_37;  /* "Disconnecting from foreign image \"~a\"." */

/* DISCONNECT-FROM-FOREIGN-IMAGES-IN-LIST */
Object disconnect_from_foreign_images_in_list(list_of_foreign_images)
    Object list_of_foreign_images;
{
    Object copy_of_list_of_foreign_images, image, ab_loop_list_;

    x_note_fn_call(214,115);
    copy_of_list_of_foreign_images = 
	    copy_list_using_icp_conses_1(list_of_foreign_images);
    image = Nil;
    ab_loop_list_ = copy_of_list_of_foreign_images;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    kill_foreign_image(image);
    notify_user(2,string_constant_37,ISVREF(image,(SI_Long)4L));
    goto next_loop;
  end_loop:
    reclaim_icp_list_1(copy_of_list_of_foreign_images);
    return VALUES_1(Nil);
}

static Object string_constant_38;  /* "Disconnected from all foreign images." */

/* DISCONNECT-FROM-ALL-FOREIGN-IMAGES */
Object disconnect_from_all_foreign_images()
{
    x_note_fn_call(214,116);
    disconnect_from_foreign_images_in_list(All_foreign_function_images_qm);
    disconnect_from_foreign_images_in_list(All_external_foreign_function_images_qm);
    notify_user(1,string_constant_38);
    return VALUES_1(Nil);
}

static Object Qsend_icp_request_foreign_function_registry;  /* send-icp-request-foreign-function-registry */

static Object Qrequest_foreign_function_registry;  /* request-foreign-function-registry */

static Object string_constant_39;  /* "[message]" */

static Object Qmessage;            /* message */

static Object Qspare_code;         /* spare-code */

static Object string_constant_40;  /* "[value arg]" */

static Object Qargument;           /* argument */

static Object Qout_of_band_message;  /* out-of-band-message */

/* SEND-ICP-REQUEST-FOREIGN-FUNCTION-REGISTRY */
Object send_icp_request_foreign_function_registry(spare_code,
	    out_of_band_message)
    Object spare_code, out_of_band_message;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,117);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_request_foreign_function_registry;
	  }
	  start_writing_icp_message(FIX((SI_Long)311L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qrequest_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qspare_code,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_integer(spare_code);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qspare_code,string_constant_40,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(spare_code);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_text_string(out_of_band_message);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrequest_foreign_function_registry,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(spare_code);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qspare_code,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(spare_code);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(out_of_band_message);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_request_foreign_function_registry,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qsend_icp_request_foreign_function_registry,top,Nil);
		goto end_send_icp_request_foreign_function_registry;
	    }
	}
	spare_code = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : spare_code;
	out_of_band_message = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : out_of_band_message;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_request_foreign_function_registry;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)311L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qrequest_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qspare_code,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qspare_code,string_constant_40,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(out_of_band_message))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(out_of_band_message))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrequest_foreign_function_registry,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qspare_code,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_text_string(out_of_band_message))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(out_of_band_message))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(out_of_band_message);
	      resumable_icp_push(spare_code);
	      resumable_icp_push(Qsend_icp_request_foreign_function_registry);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_request_foreign_function_registry;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_request_foreign_function_registry:
    return result;
}

/* HANDLE-ICP-REQUEST-FOREIGN-FUNCTION-REGISTRY--BODY */
Object handle_icp_request_foreign_function_registry__body(spare_code,
	    out_of_band_message)
    Object spare_code, out_of_band_message;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(214,118);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				send_icp_provide_foreign_function_registry(Nil,
					FIX((SI_Long)0L),out_of_band_message);
				end_icp_message_group();
			    }
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
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
    return VALUES_1(Nil);
}

static Object Qhandle_icp_request_foreign_function_registry;  /* handle-icp-request-foreign-function-registry */

/* HANDLE-ICP-REQUEST-FOREIGN-FUNCTION-REGISTRY */
Object handle_icp_request_foreign_function_registry()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, spare_code;
    Object out_of_band_message, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,119);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qrequest_foreign_function_registry,
			string_constant_39,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qspare_code,string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    spare_code = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  spare_code = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    out_of_band_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  out_of_band_message = read_icp_text_string();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_request_foreign_function_registry__body(spare_code,
			out_of_band_message);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(out_of_band_message);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrequest_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qspare_code,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  spare_code = result_of_read;
		POP_SPECIAL();
	    }
	    else
		spare_code = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qout_of_band_message,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  out_of_band_message = result_of_read;
		POP_SPECIAL();
	    }
	    else
		out_of_band_message = read_icp_text_string();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_request_foreign_function_registry__body(spare_code,
		      out_of_band_message);
	    POP_SPECIAL();
	    reclaim_text_string(out_of_band_message);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_request_foreign_function_registry,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qhandle_icp_request_foreign_function_registry,top,Nil);
		goto end_handle_icp_request_foreign_function_registry;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qrequest_foreign_function_registry,
			string_constant_39,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  spare_code = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_request_foreign_function_registry;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qspare_code,string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    spare_code = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_request_foreign_function_registry;
		  }
		  spare_code = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  out_of_band_message = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(spare_code);
			resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_request_foreign_function_registry;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    out_of_band_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(spare_code);
		      resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_request_foreign_function_registry;
		  }
		  out_of_band_message = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_request_foreign_function_registry__body(spare_code,
			out_of_band_message);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(out_of_band_message);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrequest_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		spare_code = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_request_foreign_function_registry;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qspare_code,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  spare_code = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_request_foreign_function_registry;
		}
		spare_code = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		out_of_band_message = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(spare_code);
		      resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_request_foreign_function_registry;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qout_of_band_message,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  out_of_band_message = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(spare_code);
		    resumable_icp_push(Qhandle_icp_request_foreign_function_registry);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_request_foreign_function_registry;
		}
		out_of_band_message = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_request_foreign_function_registry__body(spare_code,
		      out_of_band_message);
	    POP_SPECIAL();
	    reclaim_text_string(out_of_band_message);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_request_foreign_function_registry:
    return result;
}

static Object Qsend_icp_call_foreign_function;  /* send-icp-call-foreign-function */

static Object Qcall_foreign_function;  /* call-foreign-function */

static Object Qforeign_function_id;  /* foreign-function-id */

/* SEND-ICP-CALL-FOREIGN-FUNCTION */
Object send_icp_call_foreign_function(foreign_function_id)
    Object foreign_function_id;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,120);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_call_foreign_function;
	  }
	  start_writing_icp_message(FIX((SI_Long)313L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qcall_foreign_function,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qforeign_function_id,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_integer(foreign_function_id);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qforeign_function_id,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_integer(foreign_function_id);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qcall_foreign_function,string_constant_39,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qforeign_function_id,
			  string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_integer(foreign_function_id);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qforeign_function_id,string_constant_40,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_integer(foreign_function_id);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_call_foreign_function,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qsend_icp_call_foreign_function,top,Nil);
		goto end_send_icp_call_foreign_function;
	    }
	}
	foreign_function_id = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : foreign_function_id;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_call_foreign_function;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)313L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qcall_foreign_function,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qforeign_function_id,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(foreign_function_id))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qforeign_function_id,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(foreign_function_id))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qcall_foreign_function,string_constant_39,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qforeign_function_id,
			  string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,write_icp_integer(foreign_function_id))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qforeign_function_id,string_constant_40,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,write_icp_integer(foreign_function_id))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(foreign_function_id);
	      resumable_icp_push(Qsend_icp_call_foreign_function);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_call_foreign_function;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_call_foreign_function:
    return result;
}

/* HANDLE-ICP-CALL-FOREIGN-FUNCTION */
Object handle_icp_call_foreign_function()
{
    x_note_fn_call(214,121);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qcall_foreign_function,FIX((SI_Long)313L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_kill_foreign_function_server;  /* send-icp-kill-foreign-function-server */

static Object Qkill_foreign_function_server;  /* kill-foreign-function-server */

static Object Qshutdown_context_only_flag;  /* shutdown-context-only-flag */

/* SEND-ICP-KILL-FOREIGN-FUNCTION-SERVER */
Object send_icp_kill_foreign_function_server(shutdown_context_only_flag,
	    out_of_band_message)
    Object shutdown_context_only_flag, out_of_band_message;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,122);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_kill_foreign_function_server;
	  }
	  start_writing_icp_message(FIX((SI_Long)316L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qkill_foreign_function_server,string_constant_39,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qshutdown_context_only_flag,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_integer(shutdown_context_only_flag);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qshutdown_context_only_flag,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(shutdown_context_only_flag);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_text_string(out_of_band_message);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qkill_foreign_function_server,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qshutdown_context_only_flag,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_integer(shutdown_context_only_flag);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qshutdown_context_only_flag,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(shutdown_context_only_flag);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(out_of_band_message);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_kill_foreign_function_server,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qsend_icp_kill_foreign_function_server,top,Nil);
		goto end_send_icp_kill_foreign_function_server;
	    }
	}
	shutdown_context_only_flag = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : shutdown_context_only_flag;
	out_of_band_message = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : out_of_band_message;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_kill_foreign_function_server;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)316L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qkill_foreign_function_server,string_constant_39,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qshutdown_context_only_flag,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(shutdown_context_only_flag))) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qshutdown_context_only_flag,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(shutdown_context_only_flag))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(out_of_band_message))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(out_of_band_message))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qkill_foreign_function_server,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qshutdown_context_only_flag,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(shutdown_context_only_flag))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qshutdown_context_only_flag,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(shutdown_context_only_flag))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_text_string(out_of_band_message))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(out_of_band_message))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(out_of_band_message);
	      resumable_icp_push(shutdown_context_only_flag);
	      resumable_icp_push(Qsend_icp_kill_foreign_function_server);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_kill_foreign_function_server;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_kill_foreign_function_server:
    return result;
}

/* HANDLE-ICP-KILL-FOREIGN-FUNCTION-SERVER */
Object handle_icp_kill_foreign_function_server()
{
    x_note_fn_call(214,123);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qkill_foreign_function_server,FIX((SI_Long)316L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_shut_down_foreign_server_context;  /* send-icp-shut-down-foreign-server-context */

static Object Qshut_down_foreign_server_context;  /* shut-down-foreign-server-context */

/* SEND-ICP-SHUT-DOWN-FOREIGN-SERVER-CONTEXT */
Object send_icp_shut_down_foreign_server_context()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,124);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_shut_down_foreign_server_context;
	  }
	  start_writing_icp_message(FIX((SI_Long)317L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qshut_down_foreign_server_context,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qshut_down_foreign_server_context,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_shut_down_foreign_server_context,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qsend_icp_shut_down_foreign_server_context,top,Nil);
		goto end_send_icp_shut_down_foreign_server_context;
	    }
	}
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_shut_down_foreign_server_context;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)317L)))) {
	      resumable_icp_push(Qsend_icp_shut_down_foreign_server_context);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_shut_down_foreign_server_context;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qshut_down_foreign_server_context,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qshut_down_foreign_server_context,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_shut_down_foreign_server_context:
    return result;
}

/* HANDLE-ICP-SHUT-DOWN-FOREIGN-SERVER-CONTEXT */
Object handle_icp_shut_down_foreign_server_context()
{
    x_note_fn_call(214,125);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qshut_down_foreign_server_context,FIX((SI_Long)317L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_signal_foreign_function_error;  /* send-icp-signal-foreign-function-error */

static Object Qsignal_foreign_function_error;  /* signal-foreign-function-error */

static Object Qlocal_foreign_function_error;  /* local-foreign-function-error */

static Object Qsignal_caught_if_any;  /* signal-caught-if-any */

static Object Qerrno_if_applicable;  /* errno-if-applicable */

static Object Qerror_string;       /* error-string */

/* SEND-ICP-SIGNAL-FOREIGN-FUNCTION-ERROR */
Object send_icp_signal_foreign_function_error(local_foreign_function_error,
	    signal_caught_if_any,errno_if_applicable,error_string,
	    spare_code,out_of_band_message)
    Object local_foreign_function_error, signal_caught_if_any;
    Object errno_if_applicable, error_string, spare_code, out_of_band_message;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,126);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_signal_foreign_function_error;
	  }
	  start_writing_icp_message(FIX((SI_Long)315L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qsignal_foreign_function_error,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlocal_foreign_function_error,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_integer(local_foreign_function_error);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlocal_foreign_function_error,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(local_foreign_function_error);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qsignal_caught_if_any,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_integer(signal_caught_if_any);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qsignal_caught_if_any,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(signal_caught_if_any);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qerrno_if_applicable,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_integer(errno_if_applicable);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerrno_if_applicable,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(errno_if_applicable);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_string,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_text_string(error_string);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_string,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_text_string(error_string);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qspare_code,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_integer(spare_code);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qspare_code,string_constant_40,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(spare_code);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_text_string(out_of_band_message);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsignal_foreign_function_error,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlocal_foreign_function_error,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_integer(local_foreign_function_error);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlocal_foreign_function_error,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(local_foreign_function_error);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qsignal_caught_if_any,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(signal_caught_if_any);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qsignal_caught_if_any,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(signal_caught_if_any);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerrno_if_applicable,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(errno_if_applicable);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerrno_if_applicable,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(errno_if_applicable);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_string,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_text_string(error_string);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_string,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(error_string);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(spare_code);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qspare_code,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(spare_code);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(out_of_band_message);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_signal_foreign_function_error,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qsend_icp_signal_foreign_function_error,top,Nil);
		goto end_send_icp_signal_foreign_function_error;
	    }
	}
	local_foreign_function_error = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : local_foreign_function_error;
	signal_caught_if_any = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : signal_caught_if_any;
	errno_if_applicable = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : errno_if_applicable;
	error_string = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		: TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_string;
	spare_code = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : spare_code;
	out_of_band_message = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : out_of_band_message;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_signal_foreign_function_error;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)315L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qsignal_foreign_function_error,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3;
			    break;
			  case 4:
			    goto l4;
			    break;
			  case 5:
			    goto l5;
			    break;
			  case 6:
			    goto l6;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlocal_foreign_function_error,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(local_foreign_function_error))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlocal_foreign_function_error,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(local_foreign_function_error))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qsignal_caught_if_any,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(signal_caught_if_any))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qsignal_caught_if_any,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(signal_caught_if_any))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qerrno_if_applicable,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(errno_if_applicable))) {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerrno_if_applicable,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(errno_if_applicable))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_string,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(error_string))) {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_string,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			    write_icp_text_string(error_string))) {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l5:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qspare_code,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
			  resumable_icp_push(FIX((SI_Long)5L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qspare_code,string_constant_40,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l6:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(out_of_band_message))) {
			  resumable_icp_push(FIX((SI_Long)6L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(out_of_band_message))) {
		    resumable_icp_push(FIX((SI_Long)6L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsignal_foreign_function_error,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_1;
			  break;
			case 4:
			  goto l4_1;
			  break;
			case 5:
			  goto l5_1;
			  break;
			case 6:
			  goto l6_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlocal_foreign_function_error,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(local_foreign_function_error))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlocal_foreign_function_error,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(local_foreign_function_error))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qsignal_caught_if_any,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(signal_caught_if_any))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qsignal_caught_if_any,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(signal_caught_if_any))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerrno_if_applicable,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(errno_if_applicable))) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerrno_if_applicable,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(errno_if_applicable))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_string,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
				write_icp_text_string(error_string))) {
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_string,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_text_string(error_string))) {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l5_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qspare_code,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l6_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_text_string(out_of_band_message))) {
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(out_of_band_message))) {
		  resumable_icp_push(FIX((SI_Long)6L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(out_of_band_message);
	      resumable_icp_push(spare_code);
	      resumable_icp_push(error_string);
	      resumable_icp_push(errno_if_applicable);
	      resumable_icp_push(signal_caught_if_any);
	      resumable_icp_push(local_foreign_function_error);
	      resumable_icp_push(Qsend_icp_signal_foreign_function_error);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_signal_foreign_function_error;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_signal_foreign_function_error:
    return result;
}

static Object string_constant_41;  /* "(no function)" */

static Object string_constant_42;  /* "(no image)" */

static Object Qffs_connection_open_already;  /* ffs_connection_open_already */

static Object string_constant_43;  /* "Connection open already for foreign image \"~a\"." */

static Object Qffs_signal_caught_during_call;  /* ffs_signal_caught_during_call */

static Object string_constant_44;  /* "Error in call to foreign function \"~a\" in image \"~a\"  ~
				    *           Signal ~a (\"~a\") caught."
				    */

static Object Qffs_unknown_function;  /* ffs_unknown_function */

static Object string_constant_45;  /* "Foreign function \"~a\" is not present in foreign image \"~a\"." */

static Object Qffs_unknown_return_type;  /* ffs_unknown_return_type */

static Object string_constant_46;  /* "Unknown return type ~a from foreign function \"~a\" in image \"~a\"" */

static Object Qffs_unspecified_error;  /* ffs_unspecified_error */

static Object string_constant_47;  /* "Unspecified problem in foreign function \"~a\" in image \"~a\"~%~
				    *           Code: ~a~%Signal: ~a~%Errno: ~a~%Errno string: \"~a\""
				    */

/* HANDLE-ICP-SIGNAL-FOREIGN-FUNCTION-ERROR--BODY */
Object handle_icp_signal_foreign_function_error__body(local_foreign_function_error,
	    signal_caught_if_any,errno_if_applicable,error_string,
	    spare_code,out_of_band_message)
    Object local_foreign_function_error, signal_caught_if_any;
    Object errno_if_applicable, error_string, spare_code, out_of_band_message;
{
    Object foreign_entry_qm, foreign_function_name, image_info_qm;
    Object foreign_function_image, top_of_stack, message_1;

    x_note_fn_call(214,127);
    foreign_entry_qm = ISVREF(Current_foreign_function_call_info,(SI_Long)2L);
    foreign_function_name = foreign_entry_qm ? ISVREF(foreign_entry_qm,
	    (SI_Long)1L) : string_constant_41;
    image_info_qm = ISVREF(Current_foreign_function_call_info,(SI_Long)1L);
    foreign_function_image = image_info_qm ? ISVREF(image_info_qm,
	    (SI_Long)4L) : string_constant_42;
    if (EQ(local_foreign_function_error,Qffs_connection_open_already))
	notify_user(2,string_constant_43,foreign_function_image);
    else if (EQ(local_foreign_function_error,Qffs_signal_caught_during_call)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_44,
		foreign_function_name,foreign_function_image,
		signal_caught_if_any,error_string);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (EQ(local_foreign_function_error,Qffs_unknown_function)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_45,
		foreign_function_name,foreign_function_image);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (EQ(local_foreign_function_error,Qffs_unknown_return_type)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_46,
		errno_if_applicable,foreign_function_name,
		foreign_function_image);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (EQ(local_foreign_function_error,Qffs_unspecified_error))
	notify_user(7,string_constant_47,foreign_function_name,
		foreign_function_image,local_foreign_function_error,
		signal_caught_if_any,errno_if_applicable,error_string);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_signal_foreign_function_error;  /* handle-icp-signal-foreign-function-error */

/* HANDLE-ICP-SIGNAL-FOREIGN-FUNCTION-ERROR */
Object handle_icp_signal_foreign_function_error()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, local_foreign_function_error;
    Object signal_caught_if_any, errno_if_applicable, error_string, spare_code;
    Object out_of_band_message, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,128);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qsignal_foreign_function_error,string_constant_39,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlocal_foreign_function_error,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlocal_foreign_function_error,
				string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    local_foreign_function_error = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  local_foreign_function_error = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qsignal_caught_if_any,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsignal_caught_if_any,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    signal_caught_if_any = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  signal_caught_if_any = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qerrno_if_applicable,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerrno_if_applicable,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    errno_if_applicable = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  errno_if_applicable = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qerror_string,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_string,string_constant_40,Qargument,
				T,result_of_read,Nil,Nil);
		    error_string = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  error_string = read_icp_text_string();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qspare_code,string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    spare_code = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  spare_code = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    out_of_band_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  out_of_band_message = read_icp_text_string();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_signal_foreign_function_error__body(local_foreign_function_error,
			signal_caught_if_any,errno_if_applicable,
			error_string,spare_code,out_of_band_message);
	      POP_SPECIAL();
	      reclaim_text_string(error_string);
	      result_of_read = reclaim_text_string(out_of_band_message);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qsignal_foreign_function_error,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlocal_foreign_function_error,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlocal_foreign_function_error,
			      string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  local_foreign_function_error = result_of_read;
		POP_SPECIAL();
	    }
	    else
		local_foreign_function_error = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qsignal_caught_if_any,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsignal_caught_if_any,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  signal_caught_if_any = result_of_read;
		POP_SPECIAL();
	    }
	    else
		signal_caught_if_any = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qerrno_if_applicable,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerrno_if_applicable,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  errno_if_applicable = result_of_read;
		POP_SPECIAL();
	    }
	    else
		errno_if_applicable = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qerror_string,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_string,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_string = result_of_read;
		POP_SPECIAL();
	    }
	    else
		error_string = read_icp_text_string();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qspare_code,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  spare_code = result_of_read;
		POP_SPECIAL();
	    }
	    else
		spare_code = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qout_of_band_message,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  out_of_band_message = result_of_read;
		POP_SPECIAL();
	    }
	    else
		out_of_band_message = read_icp_text_string();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_signal_foreign_function_error__body(local_foreign_function_error,
		      signal_caught_if_any,errno_if_applicable,
		      error_string,spare_code,out_of_band_message);
	    POP_SPECIAL();
	    reclaim_text_string(error_string);
	    reclaim_text_string(out_of_band_message);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_signal_foreign_function_error,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qhandle_icp_signal_foreign_function_error,top,Nil);
		goto end_handle_icp_signal_foreign_function_error;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qsignal_foreign_function_error,string_constant_39,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  local_foreign_function_error = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlocal_foreign_function_error,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_signal_foreign_function_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlocal_foreign_function_error,
				string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    local_foreign_function_error = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  local_foreign_function_error = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  signal_caught_if_any = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qsignal_caught_if_any,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(local_foreign_function_error);
			resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_signal_foreign_function_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsignal_caught_if_any,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    signal_caught_if_any = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  signal_caught_if_any = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  errno_if_applicable = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qerrno_if_applicable,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(signal_caught_if_any);
			resumable_icp_push(local_foreign_function_error);
			resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_signal_foreign_function_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerrno_if_applicable,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    errno_if_applicable = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  errno_if_applicable = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_string = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qerror_string,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(errno_if_applicable);
			resumable_icp_push(signal_caught_if_any);
			resumable_icp_push(local_foreign_function_error);
			resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_signal_foreign_function_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_string,string_constant_40,Qargument,
				T,result_of_read,Nil,Nil);
		    error_string = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(errno_if_applicable);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  error_string = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  spare_code = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(error_string);
			resumable_icp_push(errno_if_applicable);
			resumable_icp_push(signal_caught_if_any);
			resumable_icp_push(local_foreign_function_error);
			resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_signal_foreign_function_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qspare_code,string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    spare_code = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_string);
		      resumable_icp_push(errno_if_applicable);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  spare_code = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  out_of_band_message = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(spare_code);
			resumable_icp_push(error_string);
			resumable_icp_push(errno_if_applicable);
			resumable_icp_push(signal_caught_if_any);
			resumable_icp_push(local_foreign_function_error);
			resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_signal_foreign_function_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    out_of_band_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(spare_code);
		      resumable_icp_push(error_string);
		      resumable_icp_push(errno_if_applicable);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  out_of_band_message = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_signal_foreign_function_error__body(local_foreign_function_error,
			signal_caught_if_any,errno_if_applicable,
			error_string,spare_code,out_of_band_message);
	      POP_SPECIAL();
	      reclaim_text_string(error_string);
	      result_of_read = reclaim_text_string(out_of_band_message);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qsignal_foreign_function_error,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		local_foreign_function_error = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlocal_foreign_function_error,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlocal_foreign_function_error,
			      string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  local_foreign_function_error = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_signal_foreign_function_error;
		}
		local_foreign_function_error = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		signal_caught_if_any = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qsignal_caught_if_any,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsignal_caught_if_any,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  signal_caught_if_any = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(local_foreign_function_error);
		    resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_signal_foreign_function_error;
		}
		signal_caught_if_any = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		errno_if_applicable = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qerrno_if_applicable,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerrno_if_applicable,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  errno_if_applicable = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(signal_caught_if_any);
		    resumable_icp_push(local_foreign_function_error);
		    resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_signal_foreign_function_error;
		}
		errno_if_applicable = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_string = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qerror_string,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(errno_if_applicable);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_string,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_string = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(errno_if_applicable);
		    resumable_icp_push(signal_caught_if_any);
		    resumable_icp_push(local_foreign_function_error);
		    resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_signal_foreign_function_error;
		}
		error_string = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		spare_code = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_string);
		      resumable_icp_push(errno_if_applicable);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qspare_code,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  spare_code = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(error_string);
		    resumable_icp_push(errno_if_applicable);
		    resumable_icp_push(signal_caught_if_any);
		    resumable_icp_push(local_foreign_function_error);
		    resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_signal_foreign_function_error;
		}
		spare_code = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		out_of_band_message = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(spare_code);
		      resumable_icp_push(error_string);
		      resumable_icp_push(errno_if_applicable);
		      resumable_icp_push(signal_caught_if_any);
		      resumable_icp_push(local_foreign_function_error);
		      resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_signal_foreign_function_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qout_of_band_message,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  out_of_band_message = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(spare_code);
		    resumable_icp_push(error_string);
		    resumable_icp_push(errno_if_applicable);
		    resumable_icp_push(signal_caught_if_any);
		    resumable_icp_push(local_foreign_function_error);
		    resumable_icp_push(Qhandle_icp_signal_foreign_function_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_signal_foreign_function_error;
		}
		out_of_band_message = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_signal_foreign_function_error__body(local_foreign_function_error,
		      signal_caught_if_any,errno_if_applicable,
		      error_string,spare_code,out_of_band_message);
	    POP_SPECIAL();
	    reclaim_text_string(error_string);
	    reclaim_text_string(out_of_band_message);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_signal_foreign_function_error:
    return result;
}

static Object Qtext;               /* text */

static Object string_constant_48;  /* "Relinking function \"~a\" to foreign image \"~a\".  ~
				    *                    This replaces the link to foreign image \"~a\"."
				    */

/* UPDATE-FOREIGN-FUNCTION-REGISTRY */
Object update_foreign_function_registry(list_of_foreign_function_registrations,
	    icp_socket_of_foreign_image)
    Object list_of_foreign_function_registrations, icp_socket_of_foreign_image;
{
    Object image_info, entries_to_connect, registration, ab_loop_list_, name;
    Object id, argcount, type_tag, ab_loop_list__1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, typelist, return_type, entry;
    Object old_image_info_qm, svref_new_value;
    volatile Object names_of_entries;
    Object scope_conses, declaration, declaration_name_qm, entry_to_connect_qm;
    Object possible_entry, name_of_entry, ab_loop_it_;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(214,129);
    SAVE_STACK();
    image_info = 
	    get_foreign_image_info_from_icp_socket(icp_socket_of_foreign_image);
    entries_to_connect = Nil;
    registration = Nil;
    ab_loop_list_ = list_of_foreign_function_registrations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    registration = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    name = FIRST(registration);
    id = SECOND(registration);
    argcount = THIRD(registration);
    type_tag = Nil;
    ab_loop_list__1 = FOURTH(registration);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    type_tag = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !(FIXNUMP(type_tag) && FIXNUM_LE(FIX((SI_Long)-128L),type_tag) && 
	    FIXNUM_LE(type_tag,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(type_tag)) {
	  case 1:
	    temp = Qinteger;
	    break;
	  case 6:
	    temp = Qab_real;
	    break;
	  case 3:
	    temp = Qsymbol;
	    break;
	  case 4:
	    temp = Qtext;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    ab_loopvar__2 = icp_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    reclaim_icp_list_1(FOURTH(registration));
    typelist = ab_loopvar_;
    goto end_1;
    typelist = Qnil;
  end_1:;
    type_tag = FIFTH(registration);
    if ( !(FIXNUMP(type_tag) && FIXNUM_LE(FIX((SI_Long)-128L),type_tag) && 
	    FIXNUM_LE(type_tag,FIX((SI_Long)127L))))
	return_type = Nil;
    else
	switch (INTEGER_TO_CHAR(type_tag)) {
	  case 1:
	    return_type = Qinteger;
	    break;
	  case 6:
	    return_type = Qab_real;
	    break;
	  case 3:
	    return_type = Qsymbol;
	    break;
	  case 4:
	    return_type = Qtext;
	    break;
	  default:
	    return_type = Nil;
	    break;
	}
    result = get_or_make_foreign_function_entry(name,id,argcount,typelist,
	    return_type,image_info);
    MVS_2(result,entry,old_image_info_qm);
    if (old_image_info_qm) {
	notify_user(4,string_constant_48,name,ISVREF(image_info,
		(SI_Long)4L),ISVREF(old_image_info_qm,(SI_Long)4L));
	svref_new_value = delete_icp_element_1(entry,
		ISVREF(old_image_info_qm,(SI_Long)1L));
	SVREF(old_image_info_qm,FIX((SI_Long)1L)) = svref_new_value;
	reclaim_text_string(name);
    }
    SVREF(entry,FIX((SI_Long)6L)) = image_info;
    entries_to_connect = icp_cons_1(entry,entries_to_connect);
    goto next_loop;
  end_loop:
    reclaim_icp_list_1(registration);
    names_of_entries = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	entry = Nil;
	ab_loop_list_ = entries_to_connect;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = icp_cons_1(ISVREF(entry,(SI_Long)1L),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	names_of_entries = ab_loopvar_;
	goto end_2;
	names_of_entries = Qnil;
      end_2:;
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	declaration = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  declaration_name_qm = Nil;
	  entry_to_connect_qm = Nil;
	  ab_loopvar_ = collect_subclasses(Qforeign_function_declaration);
	next_loop_3:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_4:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_3;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_3;
	      goto next_loop_4;
	    end_loop_3:
	      temp_1 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      goto end_loop_4;
	  declaration = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  declaration_name_qm = ISVREF(declaration,(SI_Long)21L);
	  if (declaration_name_qm) {
	      possible_entry = Nil;
	      ab_loop_list_ = entries_to_connect;
	      name_of_entry = Nil;
	      ab_loop_list__1 = names_of_entries;
	      ab_loop_it_ = Nil;
	    next_loop_5:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_5;
	      possible_entry = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_5;
	      name_of_entry = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      ab_loop_it_ = string_eq_w(declaration_name_qm,name_of_entry) 
		      ? possible_entry : Qnil;
	      if (ab_loop_it_) {
		  entry_to_connect_qm = ab_loop_it_;
		  goto end_3;
	      }
	      goto next_loop_5;
	    end_loop_5:
	      entry_to_connect_qm = Qnil;
	    end_3:;
	  }
	  else
	      entry_to_connect_qm = Nil;
	  update_foreign_function_linking(declaration,entry_to_connect_qm,Nil);
	  goto next_loop_3;
	end_loop_4:;
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    if (names_of_entries) {
	if ( !EQ(names_of_entries,Qunbound_in_protected_let))
	    reclaim_icp_list_1(names_of_entries);
    }
    CONTINUE_UNWINDING(0);
    RESTORE_STACK();
    return VALUES_1(SVREF(image_info,FIX((SI_Long)1L)) = entries_to_connect);
}

static Object Qsend_icp_provide_foreign_function_registry;  /* send-icp-provide-foreign-function-registry */

static Object Qprovide_foreign_function_registry;  /* provide-foreign-function-registry */

/* SEND-ICP-PROVIDE-FOREIGN-FUNCTION-REGISTRY */
Object send_icp_provide_foreign_function_registry(list_of_foreign_function_registrations_qm,
	    spare_code,out_of_band_message)
    Object list_of_foreign_function_registrations_qm, spare_code;
    Object out_of_band_message;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,130);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_provide_foreign_function_registry;
	  }
	  start_writing_icp_message(FIX((SI_Long)312L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qprovide_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_foreign_function_registrations_qm,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_foreign_function_registrations_qm,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qspare_code,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_integer(spare_code);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qspare_code,string_constant_40,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(spare_code);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_text_string(out_of_band_message);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprovide_foreign_function_registry,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_foreign_function_registrations_qm,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_foreign_function_registrations_qm,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(spare_code);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qspare_code,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(spare_code);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_text_string(out_of_band_message);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(out_of_band_message);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_provide_foreign_function_registry,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qsend_icp_provide_foreign_function_registry,top,Nil);
		goto end_send_icp_provide_foreign_function_registry;
	    }
	}
	list_of_foreign_function_registrations_qm = (resumable_icp_state_1 
		? TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		list_of_foreign_function_registrations_qm;
	spare_code = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : spare_code;
	out_of_band_message = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : out_of_band_message;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_provide_foreign_function_registry;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)312L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qprovide_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_foreign_function_registrations_qm,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_foreign_function_registrations_qm,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qspare_code,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qspare_code,string_constant_40,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(out_of_band_message))) {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qout_of_band_message,string_constant_40,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(out_of_band_message))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprovide_foreign_function_registry,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_foreign_function_registrations_qm,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_foreign_function_registrations_qm,
				string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list_of_foreign_function_registrations_qm(list_of_foreign_function_registrations_qm))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qspare_code,string_constant_40,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_integer(spare_code))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_text_string(out_of_band_message))) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(out_of_band_message))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(out_of_band_message);
	      resumable_icp_push(spare_code);
	      resumable_icp_push(list_of_foreign_function_registrations_qm);
	      resumable_icp_push(Qsend_icp_provide_foreign_function_registry);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_provide_foreign_function_registry;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_provide_foreign_function_registry:
    return result;
}

static Object string_constant_49;  /* "Successfully connected to foreign image ~s." */

static Object string_constant_50;  /* "Can't acquire lock in foreign image ~s." */

/* HANDLE-ICP-PROVIDE-FOREIGN-FUNCTION-REGISTRY--BODY */
Object handle_icp_provide_foreign_function_registry__body(list_of_foreign_function_registrations_qm,
	    spare_code,out_of_band_message)
    Object list_of_foreign_function_registrations_qm, spare_code;
    Object out_of_band_message;
{
    Object image_info, image_pathname_qm, namestring_of_connection_attempt;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, extant_pathname_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value_1;
    Declare_special(12);

    x_note_fn_call(214,131);
    image_info = get_foreign_image_info_from_icp_socket(Current_icp_socket);
    image_pathname_qm = ISVREF(image_info,(SI_Long)3L);
    if (image_pathname_qm)
	namestring_of_connection_attempt = 
		gensym_namestring_as_text_string(1,image_pathname_qm);
    else {
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
		  twrite_foreign_image_connection_spec(ISVREF(image_info,
			  (SI_Long)6L));
		  namestring_of_connection_attempt = 
			  copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (list_of_foreign_function_registrations_qm) {
	notify_user(2,string_constant_49,namestring_of_connection_attempt);
	Unused_foreign_image_indices = nconc2(Unused_foreign_image_indices,
		ISVREF(image_info,(SI_Long)13L));
	SVREF(image_info,FIX((SI_Long)13L)) = Nil;
	update_foreign_function_registry(list_of_foreign_function_registrations_qm,
		Current_icp_socket);
    }
    else {
	current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_shut_down_foreign_server_context();
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value_1 = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value_1);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value_1 = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value_1);
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
	SVREF(image_info,FIX((SI_Long)8L)) = Nil;
	flush_and_shutdown_icp_socket(Current_icp_socket);
	if (ISVREF(image_info,(SI_Long)14L) || FIXNUM_GE(ISVREF(image_info,
		(SI_Long)12L),Maximum_retries_for_foreign_image_connection)) {
	    Unused_foreign_image_indices = 
		    nconc2(Unused_foreign_image_indices,ISVREF(image_info,
		    (SI_Long)13L));
	    SVREF(image_info,FIX((SI_Long)13L)) = Nil;
	    notify_user(2,string_constant_50,namestring_of_connection_attempt);
	}
	else {
	    extant_pathname_qm = ISVREF(image_info,(SI_Long)3L);
	    temp = extant_pathname_qm ? 
		    copy_gensym_pathname(extant_pathname_qm) : Qnil;
	    initialize_foreign_function_image_if_possible(2,temp,
		    ISVREF(image_info,(SI_Long)12L));
	}
    }
    reclaim_text_string(namestring_of_connection_attempt);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_provide_foreign_function_registry;  /* handle-icp-provide-foreign-function-registry */

/* HANDLE-ICP-PROVIDE-FOREIGN-FUNCTION-REGISTRY */
Object handle_icp_provide_foreign_function_registry()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read;
    Object list_of_foreign_function_registrations_qm, spare_code;
    Object out_of_band_message, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,132);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qprovide_foreign_function_registry,
			string_constant_39,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_foreign_function_registrations_qm,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_list_of_foreign_function_registrations_qm();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_foreign_function_registrations_qm,
				string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_foreign_function_registrations_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  list_of_foreign_function_registrations_qm = 
			  read_icp_list_of_foreign_function_registrations_qm();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qspare_code,string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    spare_code = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  spare_code = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    out_of_band_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  out_of_band_message = read_icp_text_string();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_provide_foreign_function_registry__body(list_of_foreign_function_registrations_qm,
			spare_code,out_of_band_message);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(out_of_band_message);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qprovide_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_foreign_function_registrations_qm,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_list_of_foreign_function_registrations_qm();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_foreign_function_registrations_qm,
			      string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  list_of_foreign_function_registrations_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else
		list_of_foreign_function_registrations_qm = 
			read_icp_list_of_foreign_function_registrations_qm();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qspare_code,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  spare_code = result_of_read;
		POP_SPECIAL();
	    }
	    else
		spare_code = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qout_of_band_message,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  out_of_band_message = result_of_read;
		POP_SPECIAL();
	    }
	    else
		out_of_band_message = read_icp_text_string();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_provide_foreign_function_registry__body(list_of_foreign_function_registrations_qm,
		      spare_code,out_of_band_message);
	    POP_SPECIAL();
	    reclaim_text_string(out_of_band_message);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_provide_foreign_function_registry,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qhandle_icp_provide_foreign_function_registry,top,Nil);
		goto end_handle_icp_provide_foreign_function_registry;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qprovide_foreign_function_registry,
			string_constant_39,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  list_of_foreign_function_registrations_qm = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_foreign_function_registrations_qm,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = 
			    read_icp_list_of_foreign_function_registrations_qm();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_provide_foreign_function_registry;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_foreign_function_registrations_qm,
				string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_foreign_function_registrations_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_list_of_foreign_function_registrations_qm();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_provide_foreign_function_registry;
		  }
		  list_of_foreign_function_registrations_qm = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  spare_code = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(list_of_foreign_function_registrations_qm);
			resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_provide_foreign_function_registry;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qspare_code,string_constant_40,Qargument,T,
				result_of_read,Nil,Nil);
		    spare_code = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_foreign_function_registrations_qm);
		      resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_provide_foreign_function_registry;
		  }
		  spare_code = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  out_of_band_message = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			      string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(spare_code);
			resumable_icp_push(list_of_foreign_function_registrations_qm);
			resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_provide_foreign_function_registry;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qout_of_band_message,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    out_of_band_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(spare_code);
		      resumable_icp_push(list_of_foreign_function_registrations_qm);
		      resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_provide_foreign_function_registry;
		  }
		  out_of_band_message = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_provide_foreign_function_registry__body(list_of_foreign_function_registrations_qm,
			spare_code,out_of_band_message);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(out_of_band_message);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qprovide_foreign_function_registry,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		list_of_foreign_function_registrations_qm = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_foreign_function_registrations_qm,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_list_of_foreign_function_registrations_qm();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_provide_foreign_function_registry;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_foreign_function_registrations_qm,
			      string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  list_of_foreign_function_registrations_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_list_of_foreign_function_registrations_qm();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_provide_foreign_function_registry;
		}
		list_of_foreign_function_registrations_qm = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		spare_code = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qspare_code,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_foreign_function_registrations_qm);
		      resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_provide_foreign_function_registry;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qspare_code,string_constant_40,Qargument,T,
			      result_of_read,Nil,Nil);
		  spare_code = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_of_foreign_function_registrations_qm);
		    resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_provide_foreign_function_registry;
		}
		spare_code = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		out_of_band_message = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qout_of_band_message,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(spare_code);
		      resumable_icp_push(list_of_foreign_function_registrations_qm);
		      resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_provide_foreign_function_registry;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qout_of_band_message,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  out_of_band_message = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(spare_code);
		    resumable_icp_push(list_of_foreign_function_registrations_qm);
		    resumable_icp_push(Qhandle_icp_provide_foreign_function_registry);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_provide_foreign_function_registry;
		}
		out_of_band_message = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_provide_foreign_function_registry__body(list_of_foreign_function_registrations_qm,
		      spare_code,out_of_band_message);
	    POP_SPECIAL();
	    reclaim_text_string(out_of_band_message);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_provide_foreign_function_registry:
    return result;
}

static Object Qsend_icp_return_foreign_function_value;  /* send-icp-return-foreign-function-value */

static Object Qreturn_foreign_function_value;  /* return-foreign-function-value */

/* SEND-ICP-RETURN-FOREIGN-FUNCTION-VALUE */
Object send_icp_return_foreign_function_value(foreign_function_value)
    Object foreign_function_value;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,133);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_return_foreign_function_value;
	  }
	  start_writing_icp_message(FIX((SI_Long)314L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qreturn_foreign_function_value,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qforeign_function_value,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_foreign_function_value(foreign_function_value);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qforeign_function_value,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_foreign_function_value(foreign_function_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qreturn_foreign_function_value,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qforeign_function_value,
			  string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_foreign_function_value(foreign_function_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qforeign_function_value,string_constant_40,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_foreign_function_value(foreign_function_value);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_return_foreign_function_value,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qsend_icp_return_foreign_function_value,top,Nil);
		goto end_send_icp_return_foreign_function_value;
	    }
	}
	foreign_function_value = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : foreign_function_value;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_return_foreign_function_value;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)314L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qreturn_foreign_function_value,
			  string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qforeign_function_value,string_constant_40,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_foreign_function_value(foreign_function_value))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qforeign_function_value,
				  string_constant_40,Qargument,Nil,Nil,Nil,
				  Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_foreign_function_value(foreign_function_value))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qreturn_foreign_function_value,
			    string_constant_39,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qforeign_function_value,
			  string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_foreign_function_value(foreign_function_value))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qforeign_function_value,string_constant_40,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_foreign_function_value(foreign_function_value))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(foreign_function_value);
	      resumable_icp_push(Qsend_icp_return_foreign_function_value);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_return_foreign_function_value;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_return_foreign_function_value:
    return result;
}

static Object string_constant_51;  /* "Bad value returned from foreign function \"~a\" in image \"~a\"." */

/* HANDLE-ICP-RETURN-FOREIGN-FUNCTION-VALUE--BODY */
Object handle_icp_return_foreign_function_value__body(foreign_function_value)
    Object foreign_function_value;
{
    Object top_of_stack, foreign_entry_qm, message_1, svref_arg_1;

    x_note_fn_call(214,134);
    if ( !TRUEP(foreign_function_value)) {
	top_of_stack = Cached_top_of_stack;
	foreign_entry_qm = ISVREF(Current_foreign_function_call_info,
		(SI_Long)2L);
	message_1 = tformat_stack_error_text_string(3,string_constant_51,
		foreign_entry_qm ? ISVREF(foreign_entry_qm,(SI_Long)1L) : 
		string_constant_41,
		ISVREF(ISVREF(Current_foreign_function_call_info,
		(SI_Long)1L),(SI_Long)4L));
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    svref_arg_1 = Current_foreign_function_call_info;
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = foreign_function_value;
    return VALUES_1(Nil);
}

static Object Qhandle_icp_return_foreign_function_value;  /* handle-icp-return-foreign-function-value */

/* HANDLE-ICP-RETURN-FOREIGN-FUNCTION-VALUE */
Object handle_icp_return_foreign_function_value()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, foreign_function_value;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,135);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qreturn_foreign_function_value,string_constant_39,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qforeign_function_value,string_constant_40,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_foreign_function_value();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qforeign_function_value,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    foreign_function_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  foreign_function_value = read_icp_foreign_function_value();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_return_foreign_function_value__body(foreign_function_value);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qreturn_foreign_function_value,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qforeign_function_value,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_foreign_function_value();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qforeign_function_value,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  foreign_function_value = result_of_read;
		POP_SPECIAL();
	    }
	    else
		foreign_function_value = read_icp_foreign_function_value();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_return_foreign_function_value__body(foreign_function_value);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_return_foreign_function_value,top)) {
		result = icp_error_internal(Qerror,string_constant_22,
			Qhandle_icp_return_foreign_function_value,top,Nil);
		goto end_handle_icp_return_foreign_function_value;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qreturn_foreign_function_value,string_constant_39,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  foreign_function_value = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qforeign_function_value,string_constant_40,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_foreign_function_value();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_return_foreign_function_value);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_return_foreign_function_value;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qforeign_function_value,string_constant_40,
				Qargument,T,result_of_read,Nil,Nil);
		    foreign_function_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_foreign_function_value();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_return_foreign_function_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_return_foreign_function_value;
		  }
		  foreign_function_value = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_return_foreign_function_value__body(foreign_function_value);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qreturn_foreign_function_value,
			  string_constant_39,Qmessage,Nil,result_of_read,
			  Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		foreign_function_value = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qforeign_function_value,
			    string_constant_40,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_foreign_function_value();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_return_foreign_function_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_return_foreign_function_value;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qforeign_function_value,string_constant_40,
			      Qargument,T,result_of_read,Nil,Nil);
		  foreign_function_value = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_foreign_function_value();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_return_foreign_function_value);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_return_foreign_function_value;
		}
		foreign_function_value = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_return_foreign_function_value__body(foreign_function_value);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_return_foreign_function_value:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_timed_out_foreign_function_name_qm, Qcached_timed_out_foreign_function_name_qm);

/* KILL-FOREIGN-IMAGE-AND-POSSIBLY-RECONNECT */
Object kill_foreign_image_and_possibly_reconnect(foreign_image_info)
    Object foreign_image_info;
{
    Object reconnect_p, component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, saved_connection_spec, saved_pathname;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(214,136);
    reconnect_p = ISVREF(Timing_parameters,(SI_Long)29L);
    if (reconnect_p && ISVREF(foreign_image_info,(SI_Long)14L)) {
	component = Nil;
	ab_loop_list_ = ISVREF(foreign_image_info,(SI_Long)6L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = icp_cons_1(STRINGP(component) ? 
		copy_text_string(component) : component,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	saved_connection_spec = ab_loopvar_;
	goto end_1;
	saved_connection_spec = Qnil;
      end_1:;
	if (PUSH_AREA(Dynamic_area,0)) {
	    kill_foreign_image(foreign_image_info);
	    result = connect_to_external_foreign_image(saved_connection_spec);
	}
	POP_AREA(0);
	return result;
    }
    else if (reconnect_p) {
	saved_pathname = copy_gensym_pathname(ISVREF(foreign_image_info,
		(SI_Long)3L));
	if (PUSH_AREA(Dynamic_area,0)) {
	    kill_foreign_image(foreign_image_info);
	    result = connect_to_foreign_image(saved_pathname);
	}
	POP_AREA(0);
	return result;
    }
    else {
	if (PUSH_AREA(Dynamic_area,0))
	    result = kill_foreign_image(foreign_image_info);
	POP_AREA(0);
	return result;
    }
}

static Object Qcall_connected_foreign_function;  /* call-connected-foreign-function */

static Object string_constant_52;  /* "Foreign function \"~a\" timed out after ~a seconds." */

static Object string_constant_53;  /* "Connection lost to Foreign function library -- call aborted." */

/* CALL-CONNECTED-FOREIGN-FUNCTION */
Object call_connected_foreign_function(foreign_function_entry_qm,
	    foreign_image_info,foreign_function_declaration,stack,
	    stack_location,argument_count,top_of_stack)
    Object foreign_function_entry_qm, foreign_image_info;
    Object foreign_function_declaration, stack, stack_location, argument_count;
    Object top_of_stack;
{
    Object tag_temp;
    volatile Object foreign_image_socket;
    Object local_timeout_interval, timeout_interval, current_icp_port;
    Object current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol_2, temp_1, argument, active_icp_sockets;
    Object during_ffi_call_qm, scheduler_enabled_qm, start_time;
    Object foreign_result_qm, icp_pop_store, cons_1, next_cons, svref_arg_2;
    Object previous_cons, maybe_foreign_image_socket_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1, arg_offset, ab_loop_bind_;
    SI_Long temp_2;
    char display_events_were_enabled;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    double gensymed_symbol_6, gensymed_symbol_7, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(12);
    Object result;

    x_note_fn_call(214,137);
    SAVE_STACK();
    tag_temp = UNIQUE_TAG(Qcall_connected_foreign_function);
    if (PUSH_CATCH(tag_temp,3)) {
	foreign_image_socket = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(2)) {
	    foreign_image_socket = ISVREF(foreign_image_info,(SI_Long)5L);
	    gensymed_symbol = IFIX(Fixnum_time_units_per_second);
	    local_timeout_interval = ISVREF(foreign_function_declaration,
		    (SI_Long)24L);
	    gensymed_symbol_1 = EQ(Qdefault,local_timeout_interval) ? 
		    IFIX(ISVREF(Timing_parameters,(SI_Long)28L)) : 
		    IFIX(local_timeout_interval);
	    timeout_interval = fixnum_time_interval(FIX(gensymed_symbol * 
		    gensymed_symbol_1));
	    current_icp_port = ISVREF(foreign_image_socket,(SI_Long)4L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    11);
	      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		      10);
		temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)17L ? ISVREF(Current_icp_socket,
			(SI_Long)53L) : Nil;
		if (temp);
		else
		    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			    Qtelewindows) ? T : Nil;
		disable_resumability = temp;
		PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			9);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  8);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			    7);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			      6);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				5);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  4);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				    3);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				      2);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					1);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(Writing_icp_message_group);
				  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					  0);
				    gensymed_symbol_2 = Nil;
				    gensymed_symbol_3 = 0.0;
				    gensymed_symbol_4 = 0.0;
				    if (Profiling_enabled_qm) {
					gensymed_symbol_2 = T;
					gensymed_symbol_3 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_4 = 
						g2ext_unix_time_as_float();
					temp_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
						gensymed_symbol_4);
				    }
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					send_icp_call_foreign_function(ISVREF(foreign_function_entry_qm,
						(SI_Long)2L));
					arg_offset = (SI_Long)0L;
					ab_loop_bind_ = IFIX(argument_count);
					argument = Nil;
				      next_loop:
					if (arg_offset >= ab_loop_bind_)
					    goto end_loop;
					argument = ISVREF(stack,
						IFIX(stack_location) + 
						arg_offset);
					write_icp_foreign_function_argument(argument);
					arg_offset = arg_offset + (SI_Long)1L;
					goto next_loop;
				      end_loop:;
					end_icp_message_group();
				    }
				    if (Profiling_enabled_qm) {
					gensymed_symbol_5 = 
						g2ext_unix_time_as_float();
					gensymed_symbol_6 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_7 = 
						gensymed_symbol_5 - 
						gensymed_symbol_6;
					temp_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)6L);
					aref_new_value = gensymed_symbol_7 
						+ 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)6L),(SI_Long)0L);
					DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
						aref_new_value);
					temp_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					aref_new_value = gensymed_symbol_2 
						? gensymed_symbol_3 + 
						gensymed_symbol_7 + 
						(gensymed_symbol_6 - 
						gensymed_symbol_4) : 
						gensymed_symbol_5;
					DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
						aref_new_value);
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
	    if (Icp_output_ports_to_flush)
		flush_icp_output_ports();
	    temp_1 = Current_foreign_function_call_info;
	    SVREF(temp_1,FIX((SI_Long)4L)) = Nil;
	    active_icp_sockets = Qunbound_in_protected_let;
	    during_ffi_call_qm = Qunbound_in_protected_let;
	    PUSH_SPECIAL_WITH_SYMBOL(During_ffi_call_qm,Qduring_ffi_call_qm,during_ffi_call_qm,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Active_icp_sockets,Qactive_icp_sockets,active_icp_sockets,
		      1);
		if (PUSH_UNWIND_PROTECT(1)) {
		    Active_icp_sockets = icp_cons_1(foreign_image_socket,Nil);
		    During_ffi_call_qm = T;
		    Cached_top_of_stack = top_of_stack;
		    display_events_were_enabled = (SI_Long)0L != 
			    ne_display_events_enabled();
		    ne_disable_display_events();
		    if (PUSH_UNWIND_PROTECT(0)) {
			scheduler_enabled_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Scheduler_enabled_qm,Qscheduler_enabled_qm,scheduler_enabled_qm,
				0);
			  ne_set_next_timer_event((SI_Long)500L);
			  if (Cached_timed_out_foreign_function_name_qm)
			      reclaim_text_string(Cached_timed_out_foreign_function_name_qm);
			  Cached_timed_out_foreign_function_name_qm = 
				  copy_text_string(ISVREF(ISVREF(Current_foreign_function_call_info,
				  (SI_Long)2L),(SI_Long)1L));
			  start_time = c_native_clock_ticks_or_cache(Nil,Nil);
			next_loop_1:
			  g2_event_cycle_handling_windows_quit();
			  if (ISVREF(Current_foreign_function_call_info,
				  (SI_Long)4L))
			      goto end_loop_1;
			  gensymed_symbol = 
				  IFIX(c_native_clock_ticks_or_cache(T,Nil));
			  gensymed_symbol_1 = IFIX(start_time);
			  if (gensymed_symbol >= gensymed_symbol_1)
			      temp = FIX(gensymed_symbol - gensymed_symbol_1);
			  else {
			      gensymed_symbol = gensymed_symbol - 
				      gensymed_symbol_1;
			      gensymed_symbol = gensymed_symbol + 
				      IFIX(Most_positive_fixnum);
			      temp = FIX(gensymed_symbol + (SI_Long)1L);
			  }
			  if (FIXNUM_GT(temp,timeout_interval))
			      goto end_loop_1;
			  ne_set_next_timer_event((SI_Long)500L);
			  goto next_loop_1;
			end_loop_1:
			  foreign_result_qm = 
				  ISVREF(Current_foreign_function_call_info,
				  (SI_Long)4L);
			  if (foreign_result_qm)
			      SAVE_VALUES(VALUES_1(foreign_result_qm));
			  else if (ISVREF(foreign_image_info,(SI_Long)5L)) {
			      if (Cached_timed_out_foreign_function_name_qm)
				  reclaim_text_string(Cached_timed_out_foreign_function_name_qm);
			      Cached_timed_out_foreign_function_name_qm = 
				      copy_text_string(ISVREF(ISVREF(Current_foreign_function_call_info,
				      (SI_Long)2L),(SI_Long)1L));
			      kill_foreign_image_and_possibly_reconnect(foreign_image_info);
			      temp = Cached_timed_out_foreign_function_name_qm;
			      temp_2 = IFIX(timeout_interval) / 
				      IFIX(Fixnum_time_units_per_second);
			      temp = tformat_stack_error_text_string(3,
				      string_constant_52,temp,FIX(temp_2));
			      result = VALUES_2(Nil,temp);
			      THROW(tag_temp,result);
			  }
			  else {
			      kill_foreign_image_and_possibly_reconnect(foreign_image_info);
			      temp = tformat_stack_error_text_string(1,
				      string_constant_53);
			      result = VALUES_2(Nil,temp);
			      THROW(tag_temp,result);
			  }
			  goto end_1;
			  SAVE_VALUES(VALUES_1(Qnil));
			end_1:;
			POP_SPECIAL();
		    }
		    POP_UNWIND_PROTECT(0);
		    if (display_events_were_enabled)
			ne_enable_display_events();
		    CONTINUE_UNWINDING(0);
		}
		POP_UNWIND_PROTECT(1);
		if (Active_icp_sockets) {
		    if ( !EQ(Active_icp_sockets,Qunbound_in_protected_let)) {
			if (SIMPLE_VECTOR_P(foreign_image_socket) && 
				EQ(ISVREF(foreign_image_socket,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_icp_socket_g2_struct))
			    reclaim_icp_list_1(Active_icp_sockets);
		    }
		}
		CONTINUE_UNWINDING(1);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(2);
	if (foreign_image_socket) {
	    if ( !EQ(foreign_image_socket,Qunbound_in_protected_let)) {
		if ( !(SIMPLE_VECTOR_P(foreign_image_socket) && 
			EQ(ISVREF(foreign_image_socket,(SI_Long)0L),
			Qg2_defstruct_structure_name_icp_socket_g2_struct))) {
		    if (EQ(CAR(Active_icp_sockets),foreign_image_socket)) {
			icp_pop_store = Nil;
			cons_1 = Active_icp_sockets;
			if (cons_1) {
			    icp_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qicp);
			    if (ISVREF(Available_icp_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_icp_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = Available_icp_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_icp_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = Available_icp_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Active_icp_sockets = next_cons;
		    }
		    else {
			previous_cons = Active_icp_sockets;
			maybe_foreign_image_socket_qm = Nil;
		      next_loop_2:
			if ( !TRUEP(previous_cons))
			    goto end_loop_2;
			maybe_foreign_image_socket_qm = CADR(previous_cons);
			if ( !TRUEP(maybe_foreign_image_socket_qm))
			    goto end_loop_2;
			if (EQ(maybe_foreign_image_socket_qm,
				foreign_image_socket)) {
			    reclaim_icp_cons_1(CDR(previous_cons));
			    temp_1 = CDDR(previous_cons);
			    M_CDR(previous_cons) = temp_1;
			    goto end_loop_2;
			}
			previous_cons = M_CDR(previous_cons);
			goto next_loop_2;
		      end_loop_2:;
		    }
		    kill_foreign_image_and_possibly_reconnect(foreign_image_info);
		}
	    }
	}
	CONTINUE_UNWINDING(2);
	result = RESTORE_VALUES();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(3);
    RESTORE_STACK();
    return result;
}

static Object string_constant_54;  /* "The declaration for foreign function \"~a\" is not OK.  ~
				    *            This function cannot be called."
				    */

static Object string_constant_55;  /* "Cannot locate foreign function \"~a\"." */

static Object string_constant_56;  /* "Wrong number of arguments passed to foreign function \"~a\"." */

static Object string_constant_57;  /* "Cannot locate foreign image for function \"~a\"." */

/* NEW-CALL-FOREIGN-FUNCTION */
Object new_call_foreign_function(foreign_function_declaration,stack,
	    stack_location,argument_count,top_of_stack)
    Object foreign_function_declaration, stack, stack_location, argument_count;
    Object top_of_stack;
{
    Object temp, foreign_function_entry_qm, foreign_image_info_qm, svref_arg_1;

    x_note_fn_call(214,138);
    temp = ISVREF(foreign_function_declaration,(SI_Long)8L);
    if (CAR(temp)) {
	temp = ISVREF(foreign_function_declaration,(SI_Long)21L);
	if (temp);
	else
	    temp = 
		    get_or_make_up_designation_for_block(foreign_function_declaration);
	temp = tformat_stack_error_text_string(2,string_constant_54,temp);
	return VALUES_2(Nil,temp);
    }
    foreign_function_entry_qm = ISVREF(foreign_function_declaration,
	    (SI_Long)22L);
    if ( !TRUEP(foreign_function_entry_qm)) {
	temp = ISVREF(foreign_function_declaration,(SI_Long)21L);
	if (temp);
	else
	    temp = 
		    get_or_make_up_designation_for_block(foreign_function_declaration);
	temp = tformat_stack_error_text_string(2,string_constant_55,temp);
	return VALUES_2(Nil,temp);
    }
    else if (FIXNUM_NE(ISVREF(foreign_function_entry_qm,(SI_Long)3L),
	    argument_count)) {
	temp = ISVREF(foreign_function_declaration,(SI_Long)21L);
	if (temp);
	else
	    temp = 
		    get_or_make_up_designation_for_block(foreign_function_declaration);
	temp = tformat_stack_error_text_string(2,string_constant_56,temp);
	return VALUES_2(Nil,temp);
    }
    else {
	foreign_image_info_qm = ISVREF(foreign_function_entry_qm,(SI_Long)6L);
	if ( !TRUEP(foreign_image_info_qm)) {
	    temp = ISVREF(foreign_function_declaration,(SI_Long)21L);
	    if (temp);
	    else
		temp = 
			get_or_make_up_designation_for_block(foreign_function_declaration);
	    temp = tformat_stack_error_text_string(2,string_constant_57,temp);
	    return VALUES_2(Nil,temp);
	}
	else {
	    svref_arg_1 = Current_foreign_function_call_info;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = foreign_function_entry_qm;
	    svref_arg_1 = Current_foreign_function_call_info;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = foreign_image_info_qm;
	    return call_connected_foreign_function(foreign_function_entry_qm,
		    foreign_image_info_qm,foreign_function_declaration,
		    stack,stack_location,argument_count,top_of_stack);
	}
    }
}

static Object string_constant_58;  /* "Attempt to call an old-style foreign function ~a.  ~
				    *      These foreign functions are no longer implemented."
				    */

/* CALL-FOREIGN-FUNCTION */
Object call_foreign_function(name,arguments)
    Object name, arguments;
{
    x_note_fn_call(214,139);
    notify_user(2,string_constant_58,name);
    return abort_g2(0);
}

void g2_foreign_INIT()
{
    Object temp, reclaim_structure_for_element_of_foreign_linking_info_1;
    Object reclaim_structure_for_foreign_function_entry_1;
    Object reclaim_structure_for_foreign_function_image_info_1;
    Object reclaim_structure_for_foreign_function_call_info_1, temp_1;
    Object foreign_function_name_evaluation_setter_1;
    Object foreign_function_name_evaluation_getter_1;
    Object foreign_function_argument_description_evaluation_getter_1;
    Object foreign_function_result_type_evaluation_getter_1;
    Object foreign_function_timeout_interval_evaluation_setter_1;
    Object foreign_function_timeout_interval_evaluation_getter_1;
    Object default_foreign_function_timeout_interval_evaluation_setter_1;
    Object default_foreign_function_timeout_interval_evaluation_getter_1;
    Object temp_2, write_unlinked_to_unconnected_foreign_image_note_1;
    Object write_unlinked_to_connected_foreign_image_note_1;
    Object AB_package, Qg2_foreign;
    Object Qhandle_icp_shut_down_foreign_server_context;
    Object Qhandle_icp_kill_foreign_function_server;
    Object Qhandle_icp_call_foreign_function;
    Object Qdisconnect_from_all_foreign_images;
    Object Qdisconnect_from_external_foreign_image;
    Object Qdisconnect_from_foreign_image, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qconnect_to_external_foreign_image, Qconnect_to_foreign_image;
    Object list_constant_18, float_constant;
    Object Qinitialize_foreign_image_connection_mode, list_constant_17;
    Object Kfuncall, Qclasses_which_define, Qcleanup;
    Object Qcleanup_for_foreign_function_declaration;
    Object Qput_box_translation_and_text_slot_value;
    Object Qput_box_translation_and_text_slot_value_for_foreign_function_declaration;
    Object Qframe_note_writer_1, Qlink_completed_foreign_function_declarations;
    Object Qslot_putter, Qput_name_in_foreign_image, Qabsent_slot_putter;
    Object Qput_foreign_function_linked_p_where_slot_is_absent;
    Object Qforeign_function_linked_p;
    Object Qput_name_in_foreign_language_where_slot_is_absent;
    Object Qname_in_foreign_language, Qslot_value_writer;
    Object Qwrite_default_foreign_function_timeout_interval_from_slot;
    Object Qdefault_foreign_function_timeout_interval;
    Object Qwrite_foreign_function_timeout_interval_from_slot;
    Object Qforeign_function_timeout_interval;
    Object Qwrite_foreign_function_name_from_slot, Qforeign_function_name;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler;
    Object Qcompile_default_foreign_function_timeout_interval_for_slot;
    Object Qcompile_foreign_function_timeout_interval_for_slot;
    Object string_constant_86, Qtoo_long_timeout_error_text;
    Object Qlargest_allowable_foreign_function_timeout_interval;
    Object Qcompile_foreign_function_name_for_slot;
    Object Qcompile_foreign_function_declaration_for_slot, string_constant_85;
    Object string_constant_84, string_constant_83, string_constant_82;
    Object string_constant_81, Qsimplify_associative_operation, Qinitialize;
    Object Qinitialize_for_foreign_function_declaration;
    Object Qput_wait_strategy_where_slot_is_absent, Qwait_strategy, Qnamed;
    Object list_constant_14, Qtype_specification_simple_expansion;
    Object list_constant_16, list_constant_15, Qab_or;
    Object Qforeign_function_result_type, list_constant_13, list_constant_8;
    Object Qforeign_function_argument_description, list_constant_12;
    Object list_constant_11, list_constant_10, list_constant_9, Qno_item;
    Object string_constant_80, string_constant_79, string_constant_78;
    Object list_constant_7, string_constant_77, string_constant_76;
    Object string_constant_75, string_constant_74, string_constant_73;
    Object string_constant_72, string_constant_71, string_constant_70;
    Object string_constant_69, string_constant_68, Qstatement;
    Object Qinitialize_current_foreign_function_call_info, list_constant_6;
    Object Qforeign_function_call_info, Qreclaim_structure;
    Object Qoutstanding_foreign_function_call_info_count;
    Object Qforeign_function_call_info_structure_memory_usage, Qutilities2;
    Object string_constant_67, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_66, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qforeign_function_image_info;
    Object Qoutstanding_foreign_function_image_info_count;
    Object Qforeign_function_image_info_structure_memory_usage;
    Object string_constant_65, string_constant_64, Qforeign_function_entry;
    Object Qoutstanding_foreign_function_entry_count;
    Object Qforeign_function_entry_structure_memory_usage, string_constant_63;
    Object string_constant_62, Qfinal_element;
    Object Qfinal_element_marker_for_foreign_linking_info, Qstarting_element;
    Object Qstarting_element_marker_for_foreign_linking_info;
    Object Qelement_of_foreign_linking_info;
    Object Qoutstanding_element_of_foreign_linking_info_count;
    Object Qelement_of_foreign_linking_info_structure_memory_usage;
    Object string_constant_61, string_constant_60, list_constant_5;
    Object Qmake_foreign_function_registry;
    Object Qout_foreign_function_registry_internal_hash_vector_131_vectors;
    Object Qforeign_function_registry_internal_hash_vector_131_vector_memory_usage;
    Object string_constant_59;

    x_note_fn_call(214,140);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_foreign_function_registry_internal_hash_vector_131_vectors 
	    = 
	    STATIC_SYMBOL("AVAILABLE-FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_foreign_function_registry_internal_hash_vector_131_vectors,
	    Available_foreign_function_registry_internal_hash_vector_131_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_foreign_function_registry_internal_hash_vector_131_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_foreign_function_registry_internal_hash_vector_131_vectors = 
	    STATIC_SYMBOL("COUNT-OF-FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_foreign_function_registry_internal_hash_vector_131_vectors,
	    Count_of_foreign_function_registry_internal_hash_vector_131_vectors);
    record_system_variable(Qcount_of_foreign_function_registry_internal_hash_vector_131_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_foreign_function_registry_internal_hash_vector_131_vectors_vector 
	    == UNBOUND)
	Available_foreign_function_registry_internal_hash_vector_131_vectors_vector 
		= make_thread_array(Nil);
    Qout_foreign_function_registry_internal_hash_vector_131_vectors = 
	    STATIC_SYMBOL("OUT-FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR-131-VECTORS",
	    AB_package);
    Qforeign_function_registry_internal_hash_vector_131_vector_memory_usage 
	    = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-REGISTRY-INTERNAL-HASH-VECTOR-131-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_59 = STATIC_STRING("1q83-Uey83*9y83-Oqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_foreign_function_registry_internal_hash_vector_131_vectors);
    push_optimized_constant(Qforeign_function_registry_internal_hash_vector_131_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_59));
    SET_SYMBOL_FUNCTION(Qforeign_function_registry_internal_hash_vector_131_vector_memory_usage,
	    STATIC_FUNCTION(foreign_function_registry_internal_hash_vector_131_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_foreign_function_registry_internal_hash_vector_131_vectors,
	    STATIC_FUNCTION(out_foreign_function_registry_internal_hash_vector_131_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qforeign_function_registry_internal_tree_for_hash = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-REGISTRY-INTERNAL-TREE-FOR-HASH",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qforeign_function_registry = STATIC_SYMBOL("FOREIGN-FUNCTION-REGISTRY",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeign_function_registry,
	    Foreign_function_registry);
    Qg2_foreign = STATIC_SYMBOL("G2-FOREIGN",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_foreign_function_registry = 
	    STATIC_SYMBOL("MAKE-FOREIGN-FUNCTION-REGISTRY",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_foreign_function_registry,
	    STATIC_FUNCTION(make_foreign_function_registry,NIL,FALSE,0,0));
    list_constant_5 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_foreign_function_registry);
    record_system_variable(Qforeign_function_registry,Qg2_foreign,
	    list_constant_5,Qnil,Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_element_of_foreign_linking_info_g2_struct 
	    = STATIC_SYMBOL("ELEMENT-OF-FOREIGN-LINKING-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qelement_of_foreign_linking_info = 
	    STATIC_SYMBOL("ELEMENT-OF-FOREIGN-LINKING-INFO",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_element_of_foreign_linking_info_g2_struct,
	    Qelement_of_foreign_linking_info,
	    Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qelement_of_foreign_linking_info,
	    Qg2_defstruct_structure_name_element_of_foreign_linking_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_element_of_foreign_linking_info == UNBOUND)
	The_type_description_of_element_of_foreign_linking_info = Nil;
    string_constant_60 = 
	    STATIC_STRING("43Dy8m83h+y1n83h+y8n8k1l8n0000001l1n8y83-3Vy1m83wwy83vXykpk0k0");
    temp = The_type_description_of_element_of_foreign_linking_info;
    The_type_description_of_element_of_foreign_linking_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_60));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_element_of_foreign_linking_info_g2_struct,
	    The_type_description_of_element_of_foreign_linking_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qelement_of_foreign_linking_info,
	    The_type_description_of_element_of_foreign_linking_info,
	    Qtype_description_of_type);
    Qoutstanding_element_of_foreign_linking_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-ELEMENT-OF-FOREIGN-LINKING-INFO-COUNT",
	    AB_package);
    Qelement_of_foreign_linking_info_structure_memory_usage = 
	    STATIC_SYMBOL("ELEMENT-OF-FOREIGN-LINKING-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_61 = STATIC_STRING("1q83h+y8s83-SSy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_element_of_foreign_linking_info_count);
    push_optimized_constant(Qelement_of_foreign_linking_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_61));
    Qchain_of_available_element_of_foreign_linking_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ELEMENT-OF-FOREIGN-LINKING-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_element_of_foreign_linking_infos,
	    Chain_of_available_element_of_foreign_linking_infos);
    record_system_variable(Qchain_of_available_element_of_foreign_linking_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qelement_of_foreign_linking_info_count = 
	    STATIC_SYMBOL("ELEMENT-OF-FOREIGN-LINKING-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qelement_of_foreign_linking_info_count,
	    Element_of_foreign_linking_info_count);
    record_system_variable(Qelement_of_foreign_linking_info_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_element_of_foreign_linking_infos_vector == UNBOUND)
	Chain_of_available_element_of_foreign_linking_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qelement_of_foreign_linking_info_structure_memory_usage,
	    STATIC_FUNCTION(element_of_foreign_linking_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_element_of_foreign_linking_info_count,
	    STATIC_FUNCTION(outstanding_element_of_foreign_linking_info_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_element_of_foreign_linking_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_element_of_foreign_linking_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qelement_of_foreign_linking_info,
	    reclaim_structure_for_element_of_foreign_linking_info_1);
    Qstarting_element_marker_for_foreign_linking_info = 
	    STATIC_SYMBOL("STARTING-ELEMENT-MARKER-FOR-FOREIGN-LINKING-INFO",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstarting_element_marker_for_foreign_linking_info,
	    Starting_element_marker_for_foreign_linking_info);
    Qstarting_element = STATIC_SYMBOL("STARTING-ELEMENT",AB_package);
    SET_SYMBOL_VALUE(Qstarting_element_marker_for_foreign_linking_info,
	    Qstarting_element);
    Qfinal_element_marker_for_foreign_linking_info = 
	    STATIC_SYMBOL("FINAL-ELEMENT-MARKER-FOR-FOREIGN-LINKING-INFO",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfinal_element_marker_for_foreign_linking_info,
	    Final_element_marker_for_foreign_linking_info);
    Qfinal_element = STATIC_SYMBOL("FINAL-ELEMENT",AB_package);
    SET_SYMBOL_VALUE(Qfinal_element_marker_for_foreign_linking_info,
	    Qfinal_element);
    Qg2_defstruct_structure_name_foreign_function_entry_g2_struct = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-ENTRY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qforeign_function_entry = STATIC_SYMBOL("FOREIGN-FUNCTION-ENTRY",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_foreign_function_entry_g2_struct,
	    Qforeign_function_entry,Qab_name_of_unique_structure_type);
    mutate_global_property(Qforeign_function_entry,
	    Qg2_defstruct_structure_name_foreign_function_entry_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_foreign_function_entry == UNBOUND)
	The_type_description_of_foreign_function_entry = Nil;
    string_constant_62 = 
	    STATIC_STRING("43Dy8m83hNy1n83hNy8n8k1l8n0000001m1n8y83-3fy1p836py83way83wYy83wcy83wby1m83My83-ADyktk0k0");
    temp = The_type_description_of_foreign_function_entry;
    The_type_description_of_foreign_function_entry = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_62));
    mutate_global_property(Qg2_defstruct_structure_name_foreign_function_entry_g2_struct,
	    The_type_description_of_foreign_function_entry,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qforeign_function_entry,
	    The_type_description_of_foreign_function_entry,
	    Qtype_description_of_type);
    Qoutstanding_foreign_function_entry_count = 
	    STATIC_SYMBOL("OUTSTANDING-FOREIGN-FUNCTION-ENTRY-COUNT",
	    AB_package);
    Qforeign_function_entry_structure_memory_usage = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-ENTRY-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_63 = STATIC_STRING("1q83hNy8s83-Ucy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_foreign_function_entry_count);
    push_optimized_constant(Qforeign_function_entry_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_63));
    Qchain_of_available_foreign_function_entrys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FOREIGN-FUNCTION-ENTRYS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_foreign_function_entrys,
	    Chain_of_available_foreign_function_entrys);
    record_system_variable(Qchain_of_available_foreign_function_entrys,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qforeign_function_entry_count = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-ENTRY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeign_function_entry_count,
	    Foreign_function_entry_count);
    record_system_variable(Qforeign_function_entry_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_foreign_function_entrys_vector == UNBOUND)
	Chain_of_available_foreign_function_entrys_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qforeign_function_entry_structure_memory_usage,
	    STATIC_FUNCTION(foreign_function_entry_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_foreign_function_entry_count,
	    STATIC_FUNCTION(outstanding_foreign_function_entry_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_foreign_function_entry_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_foreign_function_entry,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qforeign_function_entry,
	    reclaim_structure_for_foreign_function_entry_1);
    Qstring_eq_w = STATIC_SYMBOL("STRING=W",AB_package);
    Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-IMAGE-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qforeign_function_image_info = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-IMAGE-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct,
	    Qforeign_function_image_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qforeign_function_image_info,
	    Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_foreign_function_image_info == UNBOUND)
	The_type_description_of_foreign_function_image_info = Nil;
    string_constant_64 = 
	    STATIC_STRING("43Dy8m83hOy1n83hOy8n8k1l8n0000001m1n8y83-3gy01m83My83-AEykzk0k0");
    temp = The_type_description_of_foreign_function_image_info;
    The_type_description_of_foreign_function_image_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_64));
    mutate_global_property(Qg2_defstruct_structure_name_foreign_function_image_info_g2_struct,
	    The_type_description_of_foreign_function_image_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qforeign_function_image_info,
	    The_type_description_of_foreign_function_image_info,
	    Qtype_description_of_type);
    Qoutstanding_foreign_function_image_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-FOREIGN-FUNCTION-IMAGE-INFO-COUNT",
	    AB_package);
    Qforeign_function_image_info_structure_memory_usage = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-IMAGE-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_65 = STATIC_STRING("1q83hOy8s83-Udy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_foreign_function_image_info_count);
    push_optimized_constant(Qforeign_function_image_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_65));
    Qchain_of_available_foreign_function_image_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FOREIGN-FUNCTION-IMAGE-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_foreign_function_image_infos,
	    Chain_of_available_foreign_function_image_infos);
    record_system_variable(Qchain_of_available_foreign_function_image_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qforeign_function_image_info_count = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-IMAGE-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeign_function_image_info_count,
	    Foreign_function_image_info_count);
    record_system_variable(Qforeign_function_image_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_foreign_function_image_infos_vector == UNBOUND)
	Chain_of_available_foreign_function_image_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qforeign_function_image_info_structure_memory_usage,
	    STATIC_FUNCTION(foreign_function_image_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_foreign_function_image_info_count,
	    STATIC_FUNCTION(outstanding_foreign_function_image_info_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_foreign_function_image_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_foreign_function_image_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qforeign_function_image_info,
	    reclaim_structure_for_foreign_function_image_info_1);
    Qunused_foreign_image_indices = 
	    STATIC_SYMBOL("UNUSED-FOREIGN-IMAGE-INDICES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunused_foreign_image_indices,
	    Unused_foreign_image_indices);
    record_system_variable(Qunused_foreign_image_indices,Qg2_foreign,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qhighest_foreign_image_index = 
	    STATIC_SYMBOL("HIGHEST-FOREIGN-IMAGE-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhighest_foreign_image_index,
	    Highest_foreign_image_index);
    record_system_variable(Qhighest_foreign_image_index,Qg2_foreign,
	    FIX((SI_Long)-1L),Qnil,Qnil,Qnil,Qnil);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qg2_defstruct_structure_name_foreign_function_call_info_g2_struct = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-CALL-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qforeign_function_call_info = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-CALL-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_foreign_function_call_info_g2_struct,
	    Qforeign_function_call_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qforeign_function_call_info,
	    Qg2_defstruct_structure_name_foreign_function_call_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_foreign_function_call_info == UNBOUND)
	The_type_description_of_foreign_function_call_info = Nil;
    string_constant_66 = 
	    STATIC_STRING("43Dy8m83hMy1n83hMy8n8k1l8n0000001l1n8y83-3ey0kpk0k0");
    temp = The_type_description_of_foreign_function_call_info;
    The_type_description_of_foreign_function_call_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_66));
    mutate_global_property(Qg2_defstruct_structure_name_foreign_function_call_info_g2_struct,
	    The_type_description_of_foreign_function_call_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qforeign_function_call_info,
	    The_type_description_of_foreign_function_call_info,
	    Qtype_description_of_type);
    Qoutstanding_foreign_function_call_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-FOREIGN-FUNCTION-CALL-INFO-COUNT",
	    AB_package);
    Qforeign_function_call_info_structure_memory_usage = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-CALL-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_67 = STATIC_STRING("1q83hMy8s83-Uby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_foreign_function_call_info_count);
    push_optimized_constant(Qforeign_function_call_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_67));
    Qchain_of_available_foreign_function_call_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FOREIGN-FUNCTION-CALL-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_foreign_function_call_infos,
	    Chain_of_available_foreign_function_call_infos);
    record_system_variable(Qchain_of_available_foreign_function_call_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qforeign_function_call_info_count = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-CALL-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeign_function_call_info_count,
	    Foreign_function_call_info_count);
    record_system_variable(Qforeign_function_call_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_foreign_function_call_infos_vector == UNBOUND)
	Chain_of_available_foreign_function_call_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qforeign_function_call_info_structure_memory_usage,
	    STATIC_FUNCTION(foreign_function_call_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_foreign_function_call_info_count,
	    STATIC_FUNCTION(outstanding_foreign_function_call_info_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_foreign_function_call_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_foreign_function_call_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qforeign_function_call_info,
	    reclaim_structure_for_foreign_function_call_info_1);
    Qcurrent_foreign_function_call_info = 
	    STATIC_SYMBOL("CURRENT-FOREIGN-FUNCTION-CALL-INFO",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_foreign_function_call_info,
	    Current_foreign_function_call_info);
    Qinitialize_current_foreign_function_call_info = 
	    STATIC_SYMBOL("INITIALIZE-CURRENT-FOREIGN-FUNCTION-CALL-INFO",
	    AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_current_foreign_function_call_info);
    record_system_variable(Qcurrent_foreign_function_call_info,Qg2_foreign,
	    list_constant_6,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_current_foreign_function_call_info,
	    STATIC_FUNCTION(initialize_current_foreign_function_call_info,
	    NIL,FALSE,0,0));
    Qforeign_function_declaration = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-DECLARATION",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    list_constant_7 = STATIC_CONS(Qstatement,Qnil);
    check_if_superior_classes_are_defined(Qforeign_function_declaration,
	    list_constant_7);
    string_constant_68 = STATIC_STRING("1m1m8v835Cy1l8t");
    string_constant_69 = 
	    STATIC_STRING("1v4z8r83--y83--y835Cy835Cy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_70 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_71 = 
	    STATIC_STRING("0004z8r83-0y83-0y835Cy835Cy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_72 = 
	    STATIC_STRING("ion is available at this time)000004z8r83-Fy83-Fy835Cy835Cy00001q1l8l1m8p01l83Hy1l83Uy1l83*-y1m83Dy53MySee comment in class bloc");
    string_constant_73 = 
	    STATIC_STRING("k000004z8r83ry83ry835Cy835Cy00001p1l8o1l8l1n8p835Cy83Gy1l83-5y1l83-3y000004z8r83W8y83W8y835Cy835Cy00001n1l8o1l8l1l83Cy000004z8r8");
    string_constant_74 = 
	    STATIC_STRING("3W9y83W9y835Cy835Cy00001o1l8o1l8l1m8p836py1m83Dy53Cyexport as string000004z8r83Lsy83Lsy835Cy835Cy00001n1l8o1l8l1l83Hy000004z8r83");
    string_constant_75 = 
	    STATIC_STRING("dSy83dSy835Cy835Cy00001n1l8o1l8l1l83Hy000004z8r83FQy83FQy835Cy835Cy083Py001q1l8o1l8l1l8z1m8p8336y1l83Cy1m83Dy53Jyexport as time-");
    string_constant_76 = 
	    STATIC_STRING("interval000004z8r83JBy83JBy835Cy835Cy00001p1m8p83Lry1l8o1l8l1l83Ny1l83Cy000004z8r83JCy83JCy835Cy835Cy00001p1m8p83Lty1l8o1l8l1l83");
    string_constant_77 = STATIC_STRING("Ny1l83Cy00000");
    string_constant_78 = 
	    STATIC_STRING("1x8q1o835Cy1l83*ry1m8v835Cy8t1n83--y01m8p83-*y1n83-0y01m8p83-0y1p83-Fy08l1m8p083Hy1q83ry08o8l1n8p835Cy83Gy83-5y1p83W8y08o8l83Cy1");
    string_constant_79 = 
	    STATIC_STRING("q83W9y08o8l1m8p836py1m83Dy53Cyexport as string1p83Lsy08o8l83Hy1p83dSy08o8l83Hy1s83FQy83Py8o8l8z1m8p8336y83Cy1m83Dy53Jyexport as ");
    string_constant_80 = 
	    STATIC_STRING("time-interval1r83JBy01m8p83Lry8o8l83Ny83Cy1r83JCy01m8p83Lty8o8l83Ny83Cy");
    temp = regenerate_optimized_constant(string_constant_68);
    temp_1 = regenerate_optimized_constant(list(9,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75,
	    string_constant_76,string_constant_77));
    add_class_to_environment(9,Qforeign_function_declaration,
	    list_constant_7,Nil,temp,Nil,temp_1,list_constant_7,
	    regenerate_optimized_constant(LIST_3(string_constant_78,
	    string_constant_79,string_constant_80)),Nil);
    Foreign_function_declaration_class_description = 
	    lookup_global_or_kb_specific_property_value(Qforeign_function_declaration,
	    Class_description_gkbprop);
    Qforeign_function_name = STATIC_SYMBOL("FOREIGN-FUNCTION-NAME",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_8 = STATIC_CONS(Qno_item,Qnil);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_8,Qnil);
    set_property_value_function(get_symbol_properties_function(Qforeign_function_name),
	    Qtype_specification_simple_expansion,list_constant_9);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_10);
    define_type_specification_explicit_complex_type(Qforeign_function_name,
	    list_constant_1);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qforeign_function_name);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    foreign_function_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(foreign_function_name_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qforeign_function_name,
	    foreign_function_name_evaluation_setter_1);
    foreign_function_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(foreign_function_name_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qforeign_function_name,
	    foreign_function_name_evaluation_getter_1);
    Qforeign_function_argument_description = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-ARGUMENT-DESCRIPTION",AB_package);
    list_constant_11 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qforeign_function_argument_description),
	    Qtype_specification_simple_expansion,list_constant_11);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qsequence,Qsymbol,
	    FIX((SI_Long)0L));
    define_type_specification_explicit_complex_type(Qforeign_function_argument_description,
	    list_constant_12);
    Qab_real = STATIC_SYMBOL("REAL",AB_package);
    foreign_function_argument_description_evaluation_getter_1 = 
	    STATIC_FUNCTION(foreign_function_argument_description_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qforeign_function_argument_description,
	    foreign_function_argument_description_evaluation_getter_1);
    Qforeign_function_result_type = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-RESULT-TYPE",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_8,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qforeign_function_result_type),
	    Qtype_specification_simple_expansion,list_constant_13);
    define_type_specification_explicit_complex_type(Qforeign_function_result_type,
	    list_constant_13);
    foreign_function_result_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(foreign_function_result_type_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qforeign_function_result_type,
	    foreign_function_result_type_evaluation_getter_1);
    Qforeign_function_timeout_interval = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-TIMEOUT-INTERVAL",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,Qinteger);
    set_property_value_function(get_symbol_properties_function(Qforeign_function_timeout_interval),
	    Qtype_specification_simple_expansion,list_constant_14);
    Quse_default = STATIC_SYMBOL("USE-DEFAULT",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qmember,Quse_default);
    list_constant_16 = STATIC_CONS(Qinteger,Qnil);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_15,
	    list_constant_16);
    define_type_specification_explicit_complex_type(Qforeign_function_timeout_interval,
	    list_constant_3);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qforeign_function_timeout_interval);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    foreign_function_timeout_interval_evaluation_setter_1 = 
	    STATIC_FUNCTION(foreign_function_timeout_interval_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qforeign_function_timeout_interval,
	    foreign_function_timeout_interval_evaluation_setter_1);
    foreign_function_timeout_interval_evaluation_getter_1 = 
	    STATIC_FUNCTION(foreign_function_timeout_interval_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qforeign_function_timeout_interval,
	    foreign_function_timeout_interval_evaluation_getter_1);
    Qdefault_foreign_function_timeout_interval = 
	    STATIC_SYMBOL("DEFAULT-FOREIGN-FUNCTION-TIMEOUT-INTERVAL",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qdefault_foreign_function_timeout_interval),
	    Qtype_specification_simple_expansion,list_constant_14);
    define_type_specification_explicit_complex_type(Qdefault_foreign_function_timeout_interval,
	    list_constant_3);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdefault_foreign_function_timeout_interval);
    default_foreign_function_timeout_interval_evaluation_setter_1 = 
	    STATIC_FUNCTION(default_foreign_function_timeout_interval_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdefault_foreign_function_timeout_interval,
	    default_foreign_function_timeout_interval_evaluation_setter_1);
    default_foreign_function_timeout_interval_evaluation_getter_1 = 
	    STATIC_FUNCTION(default_foreign_function_timeout_interval_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdefault_foreign_function_timeout_interval,
	    default_foreign_function_timeout_interval_evaluation_getter_1);
    Qwait_strategy = STATIC_SYMBOL("WAIT-STRATEGY",AB_package);
    Qput_wait_strategy_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-WAIT-STRATEGY-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_wait_strategy_where_slot_is_absent,
	    STATIC_FUNCTION(put_wait_strategy_where_slot_is_absent,NIL,
	    FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qwait_strategy,
	    SYMBOL_FUNCTION(Qput_wait_strategy_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qinitialize_for_foreign_function_declaration = 
	    STATIC_SYMBOL("INITIALIZE-FOR-FOREIGN-FUNCTION-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_foreign_function_declaration,
	    STATIC_FUNCTION(initialize_for_foreign_function_declaration,
	    NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_foreign_function_declaration);
    set_get(Qforeign_function_declaration,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qforeign_function_declaration,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qkill_foreign_image_process_unconditionally = 
	    STATIC_SYMBOL("KILL-FOREIGN-IMAGE-PROCESS-UNCONDITIONALLY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qkill_foreign_image_process_unconditionally,
	    STATIC_FUNCTION(kill_foreign_image_process_unconditionally,NIL,
	    FALSE,1,1));
    Qg2_defstruct_structure_name_icp_socket_g2_struct = 
	    STATIC_SYMBOL("ICP-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunlinked_to_unconnected_foreign_image = 
	    STATIC_SYMBOL("UNLINKED-TO-UNCONNECTED-FOREIGN-IMAGE",AB_package);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_81 = 
	    STATIC_STRING("13Dy1n835Cy1m1m9k83gXy83-Uay2llm1n83-Uay1s1m9k83wXy1m9k9l83-7Oy1m9k83-9y83-UZy1m9k83-Ay1m9k9m83-Uiy1plsmnp1n83-Uay1r1m9k83wXy1m9");
    string_constant_82 = 
	    STATIC_STRING("k9l83-7Oy1m9k83-9y1m9k83-Ay1m9k9m83-Uiy1plrmn01m83-UZy83-Uhy1o83-UZy1n83-Uhy1m9k83vy83-UZy1nmln9n1m83-7Oy83-6y1m83-Uhy1m9k83Sy1m");
    string_constant_83 = 
	    STATIC_STRING("83-Uhy1m9k9o1m83-Uhy1m9k83-2y1m83-Uhy1m9k83Gy1m83-Uiy1m9k83Sy1m83-Uiy1m9k9o1m83-Uiy1m9k83-2y1m83-Uiy1m9k83Gy1m836py83-Uy1m836py1");
    string_constant_84 = 
	    STATIC_STRING("m9k83Zy1n836py1o1m9k83-Qwy1m9k832+y1m9k83umy1m9k83Gy83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfunction);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_81,
	    string_constant_82,string_constant_83,string_constant_84)));
    string_constant_85 = 
	    STATIC_STRING("1n1n8336y1m1m9k83AMy1m9k83Pym1m8336y83-oy1m83BZy83-oy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_85));
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qdeclared_arglist = STATIC_SYMBOL("DECLARED-ARGLIST",AB_package);
    Qdeclared_return_type = STATIC_SYMBOL("DECLARED-RETURN-TYPE",AB_package);
    Qname_in_foreign_image = STATIC_SYMBOL("NAME-IN-FOREIGN-IMAGE",AB_package);
    string_constant = STATIC_STRING("~(~a~)");
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qcompile_foreign_function_declaration_for_slot = 
	    STATIC_SYMBOL("COMPILE-FOREIGN-FUNCTION-DECLARATION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_foreign_function_declaration_for_slot,
	    STATIC_FUNCTION(compile_foreign_function_declaration_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qforeign_function_declaration,
	    SYMBOL_FUNCTION(Qcompile_foreign_function_declaration_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qforeign_function_declaration,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qname_furnished_by_user_qm = STATIC_SYMBOL("NAME-FURNISHED-BY-USER\?",
	    AB_package);
    string_constant_1 = STATIC_STRING("~(~A~)");
    Qcompile_foreign_function_name_for_slot = 
	    STATIC_SYMBOL("COMPILE-FOREIGN-FUNCTION-NAME-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_foreign_function_name_for_slot,
	    STATIC_FUNCTION(compile_foreign_function_name_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qforeign_function_name,
	    SYMBOL_FUNCTION(Qcompile_foreign_function_name_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qforeign_function_name,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qlargest_allowable_foreign_function_timeout_interval = 
	    STATIC_SYMBOL("LARGEST-ALLOWABLE-FOREIGN-FUNCTION-TIMEOUT-INTERVAL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlargest_allowable_foreign_function_timeout_interval,
	    Largest_allowable_foreign_function_timeout_interval);
    SET_SYMBOL_VALUE(Qlargest_allowable_foreign_function_timeout_interval,
	    chestnut_floorf_function(Most_positive_fixnum,
	    Largest_known_fixnum_time_units_per_second));
    Qtoo_long_timeout_error_text = 
	    STATIC_SYMBOL("TOO-LONG-TIMEOUT-ERROR-TEXT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtoo_long_timeout_error_text,
	    Too_long_timeout_error_text);
    string_constant_86 = 
	    STATIC_STRING("The largest allowable foreign-function timeout interval is ~d seconds.");
    SET_SYMBOL_VALUE(Qtoo_long_timeout_error_text,tformat_text_string(2,
	    string_constant_86,
	    Largest_allowable_foreign_function_timeout_interval));
    Qcompile_foreign_function_timeout_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_foreign_function_timeout_interval_for_slot,
	    STATIC_FUNCTION(compile_foreign_function_timeout_interval_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qforeign_function_timeout_interval,
	    SYMBOL_FUNCTION(Qcompile_foreign_function_timeout_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qforeign_function_timeout_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_default_foreign_function_timeout_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-DEFAULT-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_default_foreign_function_timeout_interval_for_slot,
	    STATIC_FUNCTION(compile_default_foreign_function_timeout_interval_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qdefault_foreign_function_timeout_interval,
	    SYMBOL_FUNCTION(Qcompile_default_foreign_function_timeout_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdefault_foreign_function_timeout_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_2 = STATIC_STRING("none");
    Qwrite_foreign_function_name_from_slot = 
	    STATIC_SYMBOL("WRITE-FOREIGN-FUNCTION-NAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_foreign_function_name_from_slot,
	    STATIC_FUNCTION(write_foreign_function_name_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qforeign_function_name,
	    SYMBOL_FUNCTION(Qwrite_foreign_function_name_from_slot),
	    Qslot_value_writer);
    string_constant_3 = STATIC_STRING("use default");
    Qwrite_foreign_function_timeout_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_foreign_function_timeout_interval_from_slot,
	    STATIC_FUNCTION(write_foreign_function_timeout_interval_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qforeign_function_timeout_interval,
	    SYMBOL_FUNCTION(Qwrite_foreign_function_timeout_interval_from_slot),
	    Qslot_value_writer);
    Qwrite_default_foreign_function_timeout_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-DEFAULT-FOREIGN-FUNCTION-TIMEOUT-INTERVAL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_default_foreign_function_timeout_interval_from_slot,
	    STATIC_FUNCTION(write_default_foreign_function_timeout_interval_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdefault_foreign_function_timeout_interval,
	    SYMBOL_FUNCTION(Qwrite_default_foreign_function_timeout_interval_from_slot),
	    Qslot_value_writer);
    Qname_in_foreign_language = STATIC_SYMBOL("NAME-IN-FOREIGN-LANGUAGE",
	    AB_package);
    Qput_name_in_foreign_language_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-NAME-IN-FOREIGN-LANGUAGE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_name_in_foreign_language_where_slot_is_absent,
	    STATIC_FUNCTION(put_name_in_foreign_language_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qname_in_foreign_language,
	    SYMBOL_FUNCTION(Qput_name_in_foreign_language_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qforeign_function_linked_p = STATIC_SYMBOL("FOREIGN-FUNCTION-LINKED-P",
	    AB_package);
    Qput_foreign_function_linked_p_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-FOREIGN-FUNCTION-LINKED-P-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_foreign_function_linked_p_where_slot_is_absent,
	    STATIC_FUNCTION(put_foreign_function_linked_p_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qforeign_function_linked_p,
	    SYMBOL_FUNCTION(Qput_foreign_function_linked_p_where_slot_is_absent),
	    Qabsent_slot_putter);
    string_constant_4 = 
	    string_append2(STATIC_STRING("Foreign function \"~a\" has a mismatch in argument count.  ~\n              The declaration for this function takes ~a arguments but ~\n              the foreign image \"~a\" takes "),
	    STATIC_STRING("~a arguments.  ~\n              G2 is unable to link the declaration to the foreign image."));
    Qargcount_mismatch = STATIC_SYMBOL("ARGCOUNT-MISMATCH",AB_package);
    Qunlinked_to_connected_foreign_image = 
	    STATIC_SYMBOL("UNLINKED-TO-CONNECTED-FOREIGN-IMAGE",AB_package);
    string_constant_5 = STATIC_STRING("s");
    string_constant_6 = STATIC_STRING("");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_7 = 
	    STATIC_STRING("arg ~a is declared as type ~a but ~\n                                 image expects type ~a.~%");
    string_constant_8 = 
	    string_append2(STATIC_STRING("Foreign function declaration \"~a\" disagrees with ~\n                foreign image \"~a\" on argument type~a:~%~a ~\n                G2 is unable to link the declaration to the for"),
	    STATIC_STRING("eign image."));
    Qargtype_mismatch = STATIC_SYMBOL("ARGTYPE-MISMATCH",AB_package);
    string_constant_9 = 
	    string_append2(STATIC_STRING("Foreign function \"~a\" has a mismatch in return type.  ~\n                The declaration for this function expects a return type ~\n                of ~a but the foreign image \""),
	    STATIC_STRING("~a\" will return type ~a. ~\n                G2 is unable to link the declaration to the foreign image."));
    Qreturn_type_mismatch = STATIC_SYMBOL("RETURN-TYPE-MISMATCH",AB_package);
    Qput_name_in_foreign_image = STATIC_SYMBOL("PUT-NAME-IN-FOREIGN-IMAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_name_in_foreign_image,
	    STATIC_FUNCTION(put_name_in_foreign_image,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qname_in_foreign_image,
	    SYMBOL_FUNCTION(Qput_name_in_foreign_image),Qslot_putter);
    Qlink_completed_foreign_function_declarations = 
	    STATIC_SYMBOL("LINK-COMPLETED-FOREIGN-FUNCTION-DECLARATIONS",
	    AB_package);
    temp_2 = adjoin(2,Qlink_completed_foreign_function_declarations,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_2;
    temp_2 = adjoin(2,Qlink_completed_foreign_function_declarations,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_2;
    SET_SYMBOL_FUNCTION(Qlink_completed_foreign_function_declarations,
	    STATIC_FUNCTION(link_completed_foreign_function_declarations,
	    NIL,FALSE,0,0));
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_10 = 
	    STATIC_STRING("this declaration is not linked to any foreign image");
    write_unlinked_to_unconnected_foreign_image_note_1 = 
	    STATIC_FUNCTION(write_unlinked_to_unconnected_foreign_image_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qunlinked_to_unconnected_foreign_image,
	    write_unlinked_to_unconnected_foreign_image_note_1,
	    Qframe_note_writer_1);
    string_constant_11 = 
	    STATIC_STRING("this foreign function declaration cannot link to the foreign image ");
    string_constant_12 = STATIC_STRING("\"~a\" ");
    string_constant_13 = STATIC_STRING("because");
    string_constant_14 = STATIC_STRING(":~%");
    string_constant_15 = STATIC_STRING(" ");
    string_constant_16 = STATIC_STRING("(~a) ");
    string_constant_17 = 
	    STATIC_STRING("the declaration has ~a arguments ~\n                    but the image expects ~a arguments");
    string_constant_18 = STATIC_STRING(";~%");
    string_constant_19 = 
	    STATIC_STRING("the declaration argument #~a is of type ~a ~\n                        but the image expects type ~a");
    string_constant_20 = 
	    STATIC_STRING("the declaration specifies a return type of ~a ~\n                    but the image will return type ~a");
    write_unlinked_to_connected_foreign_image_note_1 = 
	    STATIC_FUNCTION(write_unlinked_to_connected_foreign_image_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qunlinked_to_connected_foreign_image,
	    write_unlinked_to_connected_foreign_image_note_1,
	    Qframe_note_writer_1);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qput_box_translation_and_text_slot_value_for_foreign_function_declaration 
	    = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-FOREIGN-FUNCTION-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_foreign_function_declaration,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_foreign_function_declaration,
	    NIL,FALSE,3,3));
    Qput_box_translation_and_text_slot_value = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_foreign_function_declaration);
    set_get(Qforeign_function_declaration,
	    Qput_box_translation_and_text_slot_value,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp_2 = CONS(Qforeign_function_declaration,temp);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp_2,
	    Qclasses_which_define);
    Qcleanup_for_foreign_function_declaration = 
	    STATIC_SYMBOL("CLEANUP-FOR-FOREIGN-FUNCTION-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_foreign_function_declaration,
	    STATIC_FUNCTION(cleanup_for_foreign_function_declaration,NIL,
	    FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_foreign_function_declaration);
    set_get(Qforeign_function_declaration,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qforeign_function_declaration,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qlist_of_foreign_function_registrations_qm = 
	    STATIC_SYMBOL("LIST-OF-FOREIGN-FUNCTION-REGISTRATIONS\?",
	    AB_package);
    string_constant_21 = STATIC_STRING("[value]");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qforeign_function_argument = STATIC_SYMBOL("FOREIGN-FUNCTION-ARGUMENT",
	    AB_package);
    Qwrite_icp_foreign_function_argument = 
	    STATIC_SYMBOL("WRITE-ICP-FOREIGN-FUNCTION-ARGUMENT",AB_package);
    string_constant_22 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_foreign_function_argument,
	    STATIC_FUNCTION(write_icp_foreign_function_argument,NIL,FALSE,
	    1,1));
    Qread_icp_foreign_function_argument = 
	    STATIC_SYMBOL("READ-ICP-FOREIGN-FUNCTION-ARGUMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_foreign_function_argument,
	    STATIC_FUNCTION(read_icp_foreign_function_argument,NIL,FALSE,0,0));
    Qforeign_function_value = STATIC_SYMBOL("FOREIGN-FUNCTION-VALUE",
	    AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qread_icp_foreign_function_value = 
	    STATIC_SYMBOL("READ-ICP-FOREIGN-FUNCTION-VALUE",AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_foreign_function_value,
	    STATIC_FUNCTION(read_icp_foreign_function_value,NIL,FALSE,0,0));
    Qwrite_icp_foreign_function_value = 
	    STATIC_SYMBOL("WRITE-ICP-FOREIGN-FUNCTION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_foreign_function_value,
	    STATIC_FUNCTION(write_icp_foreign_function_value,NIL,FALSE,1,1));
    Qtcp_ip_port_offset_for_foreign_images = 
	    STATIC_SYMBOL("TCP-IP-PORT-OFFSET-FOR-FOREIGN-IMAGES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtcp_ip_port_offset_for_foreign_images,
	    Tcp_ip_port_offset_for_foreign_images);
    record_system_variable(Qtcp_ip_port_offset_for_foreign_images,
	    Qg2_foreign,FIX((SI_Long)2222L),Qnil,Qnil,Qnil,Qnil);
    Qforeign_image_connection_mode = 
	    STATIC_SYMBOL("FOREIGN-IMAGE-CONNECTION-MODE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeign_image_connection_mode,
	    Foreign_image_connection_mode);
    Qinitialize_foreign_image_connection_mode = 
	    STATIC_SYMBOL("INITIALIZE-FOREIGN-IMAGE-CONNECTION-MODE",
	    AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_foreign_image_connection_mode);
    record_system_variable(Qforeign_image_connection_mode,Qg2_foreign,
	    list_constant_17,Qnil,Qnil,Qnil,Qnil);
    Qtcp_ip = STATIC_SYMBOL("TCP-IP",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_foreign_image_connection_mode,
	    STATIC_FUNCTION(initialize_foreign_image_connection_mode,NIL,
	    FALSE,0,0));
    Kuncached = STATIC_SYMBOL("UNCACHED",Pkeyword);
    if (Cached_tcpip_listener_address_qm == UNBOUND)
	Cached_tcpip_listener_address_qm = Kuncached;
    string_constant_23 = STATIC_STRING("TCP_IP");
    float_constant = STATIC_FLOAT(-1.0);
    if (Spawn_command_line_process_failure == UNBOUND)
	Spawn_command_line_process_failure = float_constant;
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    string_constant_24 = STATIC_STRING("~s ~a");
    string_constant_25 = STATIC_STRING("~a ~a");
    if (Foreign_image_connection_checkup_interval_in_ms == UNBOUND)
	Foreign_image_connection_checkup_interval_in_ms = FIX((SI_Long)100L);
    if (Total_foreign_image_connection_checkup_interval_in_ms == UNBOUND)
	Total_foreign_image_connection_checkup_interval_in_ms = 
		FIX((SI_Long)5000L);
    Qsuccess = STATIC_SYMBOL("SUCCESS",AB_package);
    Qfailure = STATIC_SYMBOL("FAILURE",AB_package);
    Qhandle_ff_connect_failure = STATIC_SYMBOL("HANDLE-FF-CONNECT-FAILURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_ff_connect_failure,
	    STATIC_FUNCTION(handle_ff_connect_failure,NIL,FALSE,2,2));
    Qff_connect_callback = STATIC_SYMBOL("FF-CONNECT-CALLBACK",AB_package);
    SET_SYMBOL_FUNCTION(Qff_connect_callback,
	    STATIC_FUNCTION(ff_connect_callback,NIL,FALSE,1,1));
    Qhandle_internal_foreign_image_connection_failure = 
	    STATIC_SYMBOL("HANDLE-INTERNAL-FOREIGN-IMAGE-CONNECTION-FAILURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_internal_foreign_image_connection_failure,
	    STATIC_FUNCTION(handle_internal_foreign_image_connection_failure,
	    NIL,FALSE,2,2));
    Qhandle_external_foreign_image_connection_failure = 
	    STATIC_SYMBOL("HANDLE-EXTERNAL-FOREIGN-IMAGE-CONNECTION-FAILURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_external_foreign_image_connection_failure,
	    STATIC_FUNCTION(handle_external_foreign_image_connection_failure,
	    NIL,FALSE,2,2));
    if (Maximum_retries_for_foreign_image_connection == UNBOUND)
	Maximum_retries_for_foreign_image_connection = FIX((SI_Long)10L);
    if (Milliseconds_between_retries_for_foreign_image_connection == UNBOUND)
	Milliseconds_between_retries_for_foreign_image_connection = 
		FIX((SI_Long)1000L);
    if (Milliseconds_to_sleep_before_connecting_to_foreign_image == UNBOUND)
	Milliseconds_to_sleep_before_connecting_to_foreign_image = 
		windows_platform_p() ? FIX((SI_Long)6000L) : 
		FIX((SI_Long)3000L);
    if (Milliseconds_to_sleep_after_connection_on_pc_platforms == UNBOUND)
	Milliseconds_to_sleep_after_connection_on_pc_platforms = 
		FIX((SI_Long)2000L);
    string_constant_26 = 
	    STATIC_STRING("G2 could not connect to foreign image \"~a\".");
    string_constant_27 = 
	    STATIC_STRING("G2 could not create a process for foreign image \"~a\".");
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    if (Tcpip_external_foreign_image_prologue == UNBOUND)
	Tcpip_external_foreign_image_prologue = array_constant;
    array_constant_1 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qlocalnet = STATIC_SYMBOL("LOCALNET",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    string_constant_28 = 
	    STATIC_STRING("G2 could not connect to external foreign image `~a\'.");
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    string_constant_29 = 
	    string_append2(STATIC_STRING("G2 is already connected to foreign image \"~a\".  ~\n                 To overwrite existing foreign functions, you must ~\n                 disconnect from this image and then re-"),
	    STATIC_STRING("connect to it."));
    string_constant_30 = 
	    STATIC_STRING("Attempt to connect to foreign image  \"~a\".  ~\n           This file does not exist.");
    Qconnect_to_foreign_image = STATIC_SYMBOL("CONNECT-TO-FOREIGN-IMAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconnect_to_foreign_image,
	    STATIC_FUNCTION(connect_to_foreign_image,NIL,FALSE,1,1));
    string_constant_31 = 
	    string_append2(STATIC_STRING("G2 is already connected to external foreign image `~a\'.  ~\n             To overwrite existing foreign functions, you must ~\n             disconnect from this image and then re"),
	    STATIC_STRING("-connect to it."));
    Qconnect_to_external_foreign_image = 
	    STATIC_SYMBOL("CONNECT-TO-EXTERNAL-FOREIGN-IMAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qconnect_to_external_foreign_image,
	    STATIC_FUNCTION(connect_to_external_foreign_image,NIL,FALSE,1,1));
    if (Wait_interval_before_killing_foreign_process == UNBOUND)
	Wait_interval_before_killing_foreign_process = FIX((SI_Long)5L);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_32 = 
	    STATIC_STRING("Disconnected from foreign image \"~a\".");
    string_constant_33 = 
	    STATIC_STRING("Attempt to disconnect from foreign image \"~a\".  ~\n                         G2 was not connected to this image.");
    string_constant_34 = 
	    STATIC_STRING("Attempt to disconnect from foreign image \"~a\".  ~\n              This file does not exist.");
    Qdisconnect_from_foreign_image = 
	    STATIC_SYMBOL("DISCONNECT-FROM-FOREIGN-IMAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qdisconnect_from_foreign_image,
	    STATIC_FUNCTION(disconnect_from_foreign_image,NIL,FALSE,1,1));
    string_constant_35 = 
	    STATIC_STRING("Disconnected from external foreign image `~a\'.");
    string_constant_36 = 
	    STATIC_STRING("Attempt to disconnect from external foreign image `~a\'.  ~\n                G2 was not connected to this image.");
    Qdisconnect_from_external_foreign_image = 
	    STATIC_SYMBOL("DISCONNECT-FROM-EXTERNAL-FOREIGN-IMAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qdisconnect_from_external_foreign_image,
	    STATIC_FUNCTION(disconnect_from_external_foreign_image,NIL,
	    FALSE,1,1));
    string_constant_37 = 
	    STATIC_STRING("Disconnecting from foreign image \"~a\".");
    string_constant_38 = 
	    STATIC_STRING("Disconnected from all foreign images.");
    Qdisconnect_from_all_foreign_images = 
	    STATIC_SYMBOL("DISCONNECT-FROM-ALL-FOREIGN-IMAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qdisconnect_from_all_foreign_images,
	    STATIC_FUNCTION(disconnect_from_all_foreign_images,NIL,FALSE,0,0));
    Qsend_icp_request_foreign_function_registry = 
	    STATIC_SYMBOL("SEND-ICP-REQUEST-FOREIGN-FUNCTION-REGISTRY",
	    AB_package);
    Qrequest_foreign_function_registry = 
	    STATIC_SYMBOL("REQUEST-FOREIGN-FUNCTION-REGISTRY",AB_package);
    string_constant_39 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qspare_code = STATIC_SYMBOL("SPARE-CODE",AB_package);
    string_constant_40 = STATIC_STRING("[value arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    Qout_of_band_message = STATIC_SYMBOL("OUT-OF-BAND-MESSAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_request_foreign_function_registry,
	    STATIC_FUNCTION(send_icp_request_foreign_function_registry,NIL,
	    FALSE,2,2));
    Qhandle_icp_request_foreign_function_registry = 
	    STATIC_SYMBOL("HANDLE-ICP-REQUEST-FOREIGN-FUNCTION-REGISTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_request_foreign_function_registry,
	    STATIC_FUNCTION(handle_icp_request_foreign_function_registry,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_request_foreign_function_registry,
	    FIX((SI_Long)311L));
    Qsend_icp_call_foreign_function = 
	    STATIC_SYMBOL("SEND-ICP-CALL-FOREIGN-FUNCTION",AB_package);
    Qcall_foreign_function = STATIC_SYMBOL("CALL-FOREIGN-FUNCTION",AB_package);
    Qforeign_function_id = STATIC_SYMBOL("FOREIGN-FUNCTION-ID",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_call_foreign_function,
	    STATIC_FUNCTION(send_icp_call_foreign_function,NIL,FALSE,1,1));
    Qhandle_icp_call_foreign_function = 
	    STATIC_SYMBOL("HANDLE-ICP-CALL-FOREIGN-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_call_foreign_function,
	    STATIC_FUNCTION(handle_icp_call_foreign_function,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_call_foreign_function,
	    FIX((SI_Long)313L));
    Qsend_icp_kill_foreign_function_server = 
	    STATIC_SYMBOL("SEND-ICP-KILL-FOREIGN-FUNCTION-SERVER",AB_package);
    Qkill_foreign_function_server = 
	    STATIC_SYMBOL("KILL-FOREIGN-FUNCTION-SERVER",AB_package);
    Qshutdown_context_only_flag = 
	    STATIC_SYMBOL("SHUTDOWN-CONTEXT-ONLY-FLAG",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_kill_foreign_function_server,
	    STATIC_FUNCTION(send_icp_kill_foreign_function_server,NIL,
	    FALSE,2,2));
    Qhandle_icp_kill_foreign_function_server = 
	    STATIC_SYMBOL("HANDLE-ICP-KILL-FOREIGN-FUNCTION-SERVER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_kill_foreign_function_server,
	    STATIC_FUNCTION(handle_icp_kill_foreign_function_server,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_kill_foreign_function_server,
	    FIX((SI_Long)316L));
    Qsend_icp_shut_down_foreign_server_context = 
	    STATIC_SYMBOL("SEND-ICP-SHUT-DOWN-FOREIGN-SERVER-CONTEXT",
	    AB_package);
    Qshut_down_foreign_server_context = 
	    STATIC_SYMBOL("SHUT-DOWN-FOREIGN-SERVER-CONTEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_shut_down_foreign_server_context,
	    STATIC_FUNCTION(send_icp_shut_down_foreign_server_context,NIL,
	    FALSE,0,0));
    Qhandle_icp_shut_down_foreign_server_context = 
	    STATIC_SYMBOL("HANDLE-ICP-SHUT-DOWN-FOREIGN-SERVER-CONTEXT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_shut_down_foreign_server_context,
	    STATIC_FUNCTION(handle_icp_shut_down_foreign_server_context,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_shut_down_foreign_server_context,
	    FIX((SI_Long)317L));
    Qsend_icp_signal_foreign_function_error = 
	    STATIC_SYMBOL("SEND-ICP-SIGNAL-FOREIGN-FUNCTION-ERROR",AB_package);
    Qsignal_foreign_function_error = 
	    STATIC_SYMBOL("SIGNAL-FOREIGN-FUNCTION-ERROR",AB_package);
    Qlocal_foreign_function_error = 
	    STATIC_SYMBOL("LOCAL-FOREIGN-FUNCTION-ERROR",AB_package);
    Qsignal_caught_if_any = STATIC_SYMBOL("SIGNAL-CAUGHT-IF-ANY",AB_package);
    Qerrno_if_applicable = STATIC_SYMBOL("ERRNO-IF-APPLICABLE",AB_package);
    Qerror_string = STATIC_SYMBOL("ERROR-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_signal_foreign_function_error,
	    STATIC_FUNCTION(send_icp_signal_foreign_function_error,NIL,
	    FALSE,6,6));
    string_constant_41 = STATIC_STRING("(no function)");
    string_constant_42 = STATIC_STRING("(no image)");
    Qffs_connection_open_already = 
	    STATIC_SYMBOL("FFS_CONNECTION_OPEN_ALREADY",AB_package);
    string_constant_43 = 
	    STATIC_STRING("Connection open already for foreign image \"~a\".");
    Qffs_signal_caught_during_call = 
	    STATIC_SYMBOL("FFS_SIGNAL_CAUGHT_DURING_CALL",AB_package);
    string_constant_44 = 
	    STATIC_STRING("Error in call to foreign function \"~a\" in image \"~a\"  ~\n          Signal ~a (\"~a\") caught.");
    Qffs_unknown_function = STATIC_SYMBOL("FFS_UNKNOWN_FUNCTION",AB_package);
    string_constant_45 = 
	    STATIC_STRING("Foreign function \"~a\" is not present in foreign image \"~a\".");
    Qffs_unknown_return_type = STATIC_SYMBOL("FFS_UNKNOWN_RETURN_TYPE",
	    AB_package);
    string_constant_46 = 
	    STATIC_STRING("Unknown return type ~a from foreign function \"~a\" in image \"~a\"");
    Qffs_unspecified_error = STATIC_SYMBOL("FFS_UNSPECIFIED_ERROR",AB_package);
    string_constant_47 = 
	    STATIC_STRING("Unspecified problem in foreign function \"~a\" in image \"~a\"~%~\n          Code: ~a~%Signal: ~a~%Errno: ~a~%Errno string: \"~a\"");
    Qhandle_icp_signal_foreign_function_error = 
	    STATIC_SYMBOL("HANDLE-ICP-SIGNAL-FOREIGN-FUNCTION-ERROR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_signal_foreign_function_error,
	    STATIC_FUNCTION(handle_icp_signal_foreign_function_error,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_signal_foreign_function_error,
	    FIX((SI_Long)315L));
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_48 = 
	    STATIC_STRING("Relinking function \"~a\" to foreign image \"~a\".  ~\n                   This replaces the link to foreign image \"~a\".");
    Qsend_icp_provide_foreign_function_registry = 
	    STATIC_SYMBOL("SEND-ICP-PROVIDE-FOREIGN-FUNCTION-REGISTRY",
	    AB_package);
    Qprovide_foreign_function_registry = 
	    STATIC_SYMBOL("PROVIDE-FOREIGN-FUNCTION-REGISTRY",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_provide_foreign_function_registry,
	    STATIC_FUNCTION(send_icp_provide_foreign_function_registry,NIL,
	    FALSE,3,3));
    string_constant_49 = 
	    STATIC_STRING("Successfully connected to foreign image ~s.");
    string_constant_50 = 
	    STATIC_STRING("Can\'t acquire lock in foreign image ~s.");
    Qhandle_icp_provide_foreign_function_registry = 
	    STATIC_SYMBOL("HANDLE-ICP-PROVIDE-FOREIGN-FUNCTION-REGISTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_provide_foreign_function_registry,
	    STATIC_FUNCTION(handle_icp_provide_foreign_function_registry,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_provide_foreign_function_registry,
	    FIX((SI_Long)312L));
    Qsend_icp_return_foreign_function_value = 
	    STATIC_SYMBOL("SEND-ICP-RETURN-FOREIGN-FUNCTION-VALUE",AB_package);
    Qreturn_foreign_function_value = 
	    STATIC_SYMBOL("RETURN-FOREIGN-FUNCTION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_return_foreign_function_value,
	    STATIC_FUNCTION(send_icp_return_foreign_function_value,NIL,
	    FALSE,1,1));
    string_constant_51 = 
	    STATIC_STRING("Bad value returned from foreign function \"~a\" in image \"~a\".");
    Qhandle_icp_return_foreign_function_value = 
	    STATIC_SYMBOL("HANDLE-ICP-RETURN-FOREIGN-FUNCTION-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_return_foreign_function_value,
	    STATIC_FUNCTION(handle_icp_return_foreign_function_value,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_return_foreign_function_value,
	    FIX((SI_Long)314L));
    Qcached_timed_out_foreign_function_name_qm = 
	    STATIC_SYMBOL("CACHED-TIMED-OUT-FOREIGN-FUNCTION-NAME\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_timed_out_foreign_function_name_qm,
	    Cached_timed_out_foreign_function_name_qm);
    record_system_variable(Qcached_timed_out_foreign_function_name_qm,
	    Qg2_foreign,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcall_connected_foreign_function = 
	    STATIC_SYMBOL("CALL-CONNECTED-FOREIGN-FUNCTION",AB_package);
    string_constant_52 = 
	    STATIC_STRING("Foreign function \"~a\" timed out after ~a seconds.");
    string_constant_53 = 
	    STATIC_STRING("Connection lost to Foreign function library -- call aborted.");
    SET_SYMBOL_FUNCTION(Qcall_connected_foreign_function,
	    STATIC_FUNCTION(call_connected_foreign_function,NIL,FALSE,7,7));
    string_constant_54 = 
	    STATIC_STRING("The declaration for foreign function \"~a\" is not OK.  ~\n           This function cannot be called.");
    string_constant_55 = 
	    STATIC_STRING("Cannot locate foreign function \"~a\".");
    string_constant_56 = 
	    STATIC_STRING("Wrong number of arguments passed to foreign function \"~a\".");
    string_constant_57 = 
	    STATIC_STRING("Cannot locate foreign image for function \"~a\".");
    string_constant_58 = 
	    STATIC_STRING("Attempt to call an old-style foreign function ~a.  ~\n     These foreign functions are no longer implemented.");
    SET_SYMBOL_FUNCTION(Qcall_foreign_function,
	    STATIC_FUNCTION(call_foreign_function,NIL,FALSE,2,2));
}
