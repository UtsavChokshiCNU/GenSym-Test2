/* pcdbg.c
 * Input file:  proc-debug.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pcdbg.h"


DEFINE_VARIABLE_WITH_SYMBOL(Current_graph_layout_hashing_function, Qcurrent_graph_layout_hashing_function);

DEFINE_VARIABLE_WITH_SYMBOL(Available_graph_node_of_graphed_thing_hash_vector_43_vectors, Qavailable_graph_node_of_graphed_thing_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors, Qcount_of_graph_node_of_graphed_thing_hash_vector_43_vectors);

Object Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector = UNBOUND;

/* GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object graph_node_of_graphed_thing_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(162,0);
    temp = Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR-43-VECTORS */
Object out_graph_node_of_graphed_thing_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(162,1);
    temp = 
	    FIXNUM_MINUS(Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    length(Available_graph_node_of_graphed_thing_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_graph_node_of_graphed_thing_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(162,2);
    atomic_incff_symval(Qcount_of_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR */
Object make_graph_node_of_graphed_thing_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(162,3);
    if (ISVREF(Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector,
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
		make_permanent_graph_node_of_graphed_thing_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR */
Object reclaim_graph_node_of_graphed_thing_hash_vector(graph_node_of_graphed_thing_hash_vector_43_vector)
    Object graph_node_of_graphed_thing_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(162,4);
    svref_arg_1 = 
	    Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector;
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
    M_CAR(gensymed_symbol) = graph_node_of_graphed_thing_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-GRAPH-NODE-OF-GRAPHED-THING-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_graph_node_of_graphed_thing_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(162,5);
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

/* RECLAIM-GRAPH-NODE-OF-GRAPHED-THING-TREE-FOR-HASH-NODES */
Object reclaim_graph_node_of_graphed_thing_tree_for_hash_nodes(graph_node_of_graphed_thing_tree_for_hash_skip_list,
	    tail)
    Object graph_node_of_graphed_thing_tree_for_hash_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(162,6);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(graph_node_of_graphed_thing_tree_for_hash_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(graph_node_of_graphed_thing_tree_for_hash_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(graph_node_of_graphed_thing_tree_for_hash_skip_list,
	    (SI_Long)2L);
    entry = ISVREF(graph_node_of_graphed_thing_tree_for_hash_skip_list,
	    (SI_Long)3L);
    reclaim_skip_list_element(graph_node_of_graphed_thing_tree_for_hash_skip_list);
    graph_node_of_graphed_thing_tree_for_hash_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-GRAPH-NODE-OF-GRAPHED-THING-TREE */
Object clear_graph_node_of_graphed_thing_tree(graph_node_of_graphed_thing_tree_for_hash_skip_list)
    Object graph_node_of_graphed_thing_tree_for_hash_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(162,7);
    head = M_CAR(M_CDR(graph_node_of_graphed_thing_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(graph_node_of_graphed_thing_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_graph_node_of_graphed_thing_tree_for_hash_nodes(element_qm,
		tail);
    return VALUES_1(graph_node_of_graphed_thing_tree_for_hash_skip_list);
}

static Object Qgraph_node_of_graphed_thing_tree_for_hash;  /* graph-node-of-graphed-thing-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-GRAPH-NODE-OF-GRAPHED-THING */
Object make_graph_node_of_graphed_thing()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(162,8);
    new_vector = make_graph_node_of_graphed_thing_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_graph_node_of_graphed_thing_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_graph_node_of_graphed_thing_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qgraph_node_of_graphed_thing_tree_for_hash;
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

/* FLATTEN-GRAPH-NODE-OF-GRAPHED-THING */
Object flatten_graph_node_of_graphed_thing(graph_node_of_graphed_thing_hash_table)
    Object graph_node_of_graphed_thing_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(162,9);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(graph_node_of_graphed_thing_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-GRAPH-NODE-OF-GRAPHED-THING */
Object clear_graph_node_of_graphed_thing(graph_node_of_graphed_thing_hash_table)
    Object graph_node_of_graphed_thing_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(162,10);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_graph_node_of_graphed_thing_tree(ISVREF(graph_node_of_graphed_thing_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-GRAPH-NODE-OF-GRAPHED-THING */
Object reclaim_graph_node_of_graphed_thing(graph_node_of_graphed_thing_hash_table)
    Object graph_node_of_graphed_thing_hash_table;
{
    Object graph_node_of_graphed_thing_tree_for_hash_skip_list, head, tail;
    Object element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(162,11);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    graph_node_of_graphed_thing_tree_for_hash_skip_list = 
	    ISVREF(graph_node_of_graphed_thing_hash_table,index_1);
    head = M_CAR(M_CDR(graph_node_of_graphed_thing_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(graph_node_of_graphed_thing_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_graph_node_of_graphed_thing_tree_for_hash_nodes(element_qm,
		tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(graph_node_of_graphed_thing_tree_for_hash_skip_list) = Nil;
    M_CADR(graph_node_of_graphed_thing_tree_for_hash_skip_list) = Nil;
    M_CAR(graph_node_of_graphed_thing_tree_for_hash_skip_list) = Nil;
    if (graph_node_of_graphed_thing_tree_for_hash_skip_list) {
	last_1 = graph_node_of_graphed_thing_tree_for_hash_skip_list;
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
	    M_CDR(temp) = graph_node_of_graphed_thing_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    graph_node_of_graphed_thing_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(graph_node_of_graphed_thing_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_graph_node_of_graphed_thing_hash_vector(graph_node_of_graphed_thing_hash_table);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_graph_layout_conses, Qavailable_graph_layout_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_graph_layout_conses_tail, Qavailable_graph_layout_conses_tail);

Object Available_graph_layout_conses_vector = UNBOUND;

Object Available_graph_layout_conses_tail_vector = UNBOUND;

Object Graph_layout_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Graph_layout_cons_counter, Qgraph_layout_cons_counter);

/* OUTSTANDING-GRAPH-LAYOUT-CONSES */
Object outstanding_graph_layout_conses()
{
    Object temp;

    x_note_fn_call(162,12);
    temp = FIXNUM_MINUS(Graph_layout_cons_counter,
	    length(Available_graph_layout_conses));
    return VALUES_1(temp);
}

/* GRAPH-LAYOUT-CONS-MEMORY-USAGE */
Object graph_layout_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(162,13);
    temp = FIXNUM_TIMES(Graph_layout_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-GRAPH-LAYOUT-CONS-POOL */
Object replenish_graph_layout_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(162,14);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qgraph_layout_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_graph_layout_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Graph_layout_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qgraph_layout;       /* graph-layout */

/* GRAPH-LAYOUT-CONS-1 */
Object graph_layout_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(162,15);
    new_cons = ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_graph_layout_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_graph_layout_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qgraph_layout);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-GRAPH-LAYOUT-LIST-POOL */
Object replenish_graph_layout_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(162,16);
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
    if (ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_graph_layout_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qgraph_layout_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-GRAPH-LAYOUT-LIST-1 */
Object make_graph_layout_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(162,17);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_graph_layout_conses_vector,
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
	replenish_graph_layout_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_graph_layout_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qgraph_layout);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_graph_layout_conses_tail_vector;
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

/* GRAPH-LAYOUT-LIST-2 */
Object graph_layout_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(162,18);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_graph_layout_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgraph_layout);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_graph_layout_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_graph_layout_conses_tail_vector;
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

/* GRAPH-LAYOUT-LIST-3 */
Object graph_layout_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(162,19);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_graph_layout_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgraph_layout);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_graph_layout_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_graph_layout_conses_tail_vector;
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

/* GRAPH-LAYOUT-LIST-4 */
Object graph_layout_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(162,20);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_graph_layout_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgraph_layout);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_graph_layout_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_graph_layout_conses_tail_vector;
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

/* GRAPH-LAYOUT-LIST-TRACE-HOOK */
Object graph_layout_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(162,21);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-GRAPH-LAYOUT-CONSES-1 */
Object copy_tree_using_graph_layout_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(162,22);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graph_layout_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graph_layout_cons_pool();
	temp_1 = copy_tree_using_graph_layout_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraph_layout);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graph_layout_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graph_layout_cons_pool();
	temp_1 = 
		copy_tree_using_graph_layout_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraph_layout);
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

/* COPY-LIST-USING-GRAPH-LAYOUT-CONSES-1 */
Object copy_list_using_graph_layout_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(162,23);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graph_layout_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graph_layout_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraph_layout);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_graph_layout_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graph_layout_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graph_layout_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graph_layout_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraph_layout);
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

/* RECLAIM-GRAPH-LAYOUT-CONS-1 */
Object reclaim_graph_layout_cons_1(graph_layout_cons)
    Object graph_layout_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(162,24);
    inline_note_reclaim_cons(graph_layout_cons,Qgraph_layout);
    if (ISVREF(Available_graph_layout_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_graph_layout_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = graph_layout_cons;
	temp = Available_graph_layout_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = graph_layout_cons;
    }
    else {
	temp = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = graph_layout_cons;
	temp = Available_graph_layout_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = graph_layout_cons;
    }
    M_CDR(graph_layout_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-GRAPH-LAYOUT-LIST-1 */
Object reclaim_graph_layout_list_1(graph_layout_list)
    Object graph_layout_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(162,25);
    if (graph_layout_list) {
	last_1 = graph_layout_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qgraph_layout);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qgraph_layout);
	if (ISVREF(Available_graph_layout_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_graph_layout_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = graph_layout_list;
	    temp = Available_graph_layout_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_graph_layout_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = graph_layout_list;
	    temp = Available_graph_layout_conses_tail_vector;
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

/* RECLAIM-GRAPH-LAYOUT-LIST*-1 */
Object reclaim_graph_layout_list_star_1(graph_layout_list)
    Object graph_layout_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(162,26);
    if (CONSP(graph_layout_list)) {
	temp = last(graph_layout_list,_);
	M_CDR(temp) = Nil;
	if (graph_layout_list) {
	    last_1 = graph_layout_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qgraph_layout);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qgraph_layout);
	    if (ISVREF(Available_graph_layout_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_graph_layout_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = graph_layout_list;
		temp = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_graph_layout_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = graph_layout_list;
		temp = Available_graph_layout_conses_tail_vector;
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

/* RECLAIM-GRAPH-LAYOUT-TREE-1 */
Object reclaim_graph_layout_tree_1(tree)
    Object tree;
{
    Object e, e2, graph_layout_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(162,27);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_graph_layout_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		graph_layout_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(graph_layout_cons,Qgraph_layout);
		if (EQ(graph_layout_cons,e))
		    goto end_1;
		else if ( !TRUEP(graph_layout_cons))
		    goto end_1;
		else
		    graph_layout_cons = CDR(graph_layout_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_graph_layout_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_graph_layout_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_graph_layout_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_graph_layout_conses_tail_vector;
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

/* DELETE-GRAPH-LAYOUT-ELEMENT-1 */
Object delete_graph_layout_element_1(element,graph_layout_list)
    Object element, graph_layout_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(162,28);
    if (graph_layout_list) {
	if (EQ(element,M_CAR(graph_layout_list))) {
	    temp = CDR(graph_layout_list);
	    inline_note_reclaim_cons(graph_layout_list,Qgraph_layout);
	    if (ISVREF(Available_graph_layout_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_graph_layout_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = graph_layout_list;
		temp_1 = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = graph_layout_list;
	    }
	    else {
		temp_1 = Available_graph_layout_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = graph_layout_list;
		temp_1 = Available_graph_layout_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = graph_layout_list;
	    }
	    M_CDR(graph_layout_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = graph_layout_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qgraph_layout);
		if (ISVREF(Available_graph_layout_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_graph_layout_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_graph_layout_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_graph_layout_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_graph_layout_conses_tail_vector;
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
	    temp = graph_layout_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-GRAPH-LAYOUT-CONS-1 */
Object delete_graph_layout_cons_1(graph_layout_cons,graph_layout_list)
    Object graph_layout_cons, graph_layout_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(162,29);
    if (EQ(graph_layout_cons,graph_layout_list))
	temp = CDR(graph_layout_list);
    else {
	l_trailer_qm = Nil;
	l = graph_layout_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,graph_layout_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = graph_layout_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_graph_layout_cons_1(graph_layout_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_graph_display = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_graph_displays, Qchain_of_available_graph_displays);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_display_count, Qgraph_display_count);

Object Chain_of_available_graph_displays_vector = UNBOUND;

/* GRAPH-DISPLAY-STRUCTURE-MEMORY-USAGE */
Object graph_display_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(162,30);
    temp = Graph_display_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)21L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GRAPH-DISPLAY-COUNT */
Object outstanding_graph_display_count()
{
    Object def_structure_graph_display_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(162,31);
    gensymed_symbol = IFIX(Graph_display_count);
    def_structure_graph_display_variable = Chain_of_available_graph_displays;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_graph_display_variable))
	goto end_loop;
    def_structure_graph_display_variable = 
	    ISVREF(def_structure_graph_display_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GRAPH-DISPLAY-1 */
Object reclaim_graph_display_1(graph_display)
    Object graph_display;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(162,32);
    inline_note_reclaim_cons(graph_display,Nil);
    structure_being_reclaimed = graph_display;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_graph_node_function(ISVREF(graph_display,(SI_Long)3L));
      SVREF(graph_display,FIX((SI_Long)3L)) = Nil;
      reclaim_graph_node_of_graphed_thing(ISVREF(graph_display,(SI_Long)4L));
      SVREF(graph_display,FIX((SI_Long)4L)) = Nil;
      reclaim_if_managed_array(ISVREF(graph_display,(SI_Long)17L));
      SVREF(graph_display,FIX((SI_Long)17L)) = Nil;
      reclaim_graph_node_of_graphed_thing(ISVREF(graph_display,(SI_Long)19L));
      SVREF(graph_display,FIX((SI_Long)19L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_graph_displays_vector,
	    IFIX(Current_thread_index));
    SVREF(graph_display,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_graph_displays_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = graph_display;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GRAPH-DISPLAY */
Object reclaim_structure_for_graph_display(graph_display)
    Object graph_display;
{
    x_note_fn_call(162,33);
    return reclaim_graph_display_1(graph_display);
}

static Object Qg2_defstruct_structure_name_graph_display_g2_struct;  /* g2-defstruct-structure-name::graph-display-g2-struct */

/* MAKE-PERMANENT-GRAPH-DISPLAY-STRUCTURE-INTERNAL */
Object make_permanent_graph_display_structure_internal()
{
    Object def_structure_graph_display_variable;
    Object defstruct_g2_graph_display_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(162,34);
    def_structure_graph_display_variable = Nil;
    atomic_incff_symval(Qgraph_display_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_graph_display_variable = Nil;
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
	defstruct_g2_graph_display_variable = the_array;
	SVREF(defstruct_g2_graph_display_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graph_display_g2_struct;
	def_structure_graph_display_variable = 
		defstruct_g2_graph_display_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_graph_display_variable);
}

/* MAKE-GRAPH-DISPLAY-1 */
Object make_graph_display_1(graph_display_root_item,
	    graph_display_orientation,graph_display_vertical_spacing,
	    graph_display_horizontal_spacing,
	    graph_display_children_function,graph_display_extra_argument,
	    graph_display_short_rep_function,graph_display_hash_function)
    Object graph_display_root_item, graph_display_orientation;
    Object graph_display_vertical_spacing, graph_display_horizontal_spacing;
    Object graph_display_children_function, graph_display_extra_argument;
    Object graph_display_short_rep_function, graph_display_hash_function;
{
    Object def_structure_graph_display_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(162,35);
    def_structure_graph_display_variable = 
	    ISVREF(Chain_of_available_graph_displays_vector,
	    IFIX(Current_thread_index));
    if (def_structure_graph_display_variable) {
	temp = Chain_of_available_graph_displays_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_graph_display_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_graph_display_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graph_display_g2_struct;
    }
    else
	def_structure_graph_display_variable = 
		make_permanent_graph_display_structure_internal();
    inline_note_allocate_cons(def_structure_graph_display_variable,Nil);
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)2L)) = 
	    graph_display_root_item;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)1L)) = 
	    graph_display_orientation;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)5L)) = 
	    graph_display_vertical_spacing;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)6L)) = 
	    graph_display_horizontal_spacing;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)7L)) = 
	    graph_display_children_function;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)8L)) = 
	    graph_display_extra_argument;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)9L)) = 
	    graph_display_short_rep_function;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)10L)) = 
	    graph_display_hash_function;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)3L)) = Nil;
    temp = make_graph_node_of_graphed_thing();
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)4L)) = temp;
    ISVREF(def_structure_graph_display_variable,(SI_Long)11L) = 
	    FIX((SI_Long)10L);
    ISVREF(def_structure_graph_display_variable,(SI_Long)12L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_graph_display_variable,(SI_Long)13L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_graph_display_variable,(SI_Long)14L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_graph_display_variable,(SI_Long)15L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_graph_display_variable,(SI_Long)16L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)18L)) = Nil;
    temp = make_graph_node_of_graphed_thing();
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)19L)) = temp;
    SVREF(def_structure_graph_display_variable,FIX((SI_Long)20L)) = Nil;
    return VALUES_1(def_structure_graph_display_variable);
}

Object The_type_description_of_graph_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_graph_nodes, Qchain_of_available_graph_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_node_count, Qgraph_node_count);

Object Chain_of_available_graph_nodes_vector = UNBOUND;

/* GRAPH-NODE-STRUCTURE-MEMORY-USAGE */
Object graph_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(162,36);
    temp = Graph_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GRAPH-NODE-COUNT */
Object outstanding_graph_node_count()
{
    Object def_structure_graph_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(162,37);
    gensymed_symbol = IFIX(Graph_node_count);
    def_structure_graph_node_variable = Chain_of_available_graph_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_graph_node_variable))
	goto end_loop;
    def_structure_graph_node_variable = 
	    ISVREF(def_structure_graph_node_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GRAPH-NODE-1 */
Object reclaim_graph_node_1(graph_node)
    Object graph_node;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(162,38);
    inline_note_reclaim_cons(graph_node,Nil);
    structure_being_reclaimed = graph_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_graph_node_list(ISVREF(graph_node,(SI_Long)5L));
      SVREF(graph_node,FIX((SI_Long)5L)) = Nil;
      reclaim_graph_layout_list_1(ISVREF(graph_node,(SI_Long)11L));
      SVREF(graph_node,FIX((SI_Long)11L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_graph_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(graph_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_graph_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = graph_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GRAPH-NODE */
Object reclaim_structure_for_graph_node(graph_node)
    Object graph_node;
{
    x_note_fn_call(162,39);
    return reclaim_graph_node_1(graph_node);
}

static Object Qg2_defstruct_structure_name_graph_node_g2_struct;  /* g2-defstruct-structure-name::graph-node-g2-struct */

/* MAKE-PERMANENT-GRAPH-NODE-STRUCTURE-INTERNAL */
Object make_permanent_graph_node_structure_internal()
{
    Object def_structure_graph_node_variable, defstruct_g2_graph_node_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(162,40);
    def_structure_graph_node_variable = Nil;
    atomic_incff_symval(Qgraph_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_graph_node_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_graph_node_variable = the_array;
	SVREF(defstruct_g2_graph_node_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graph_node_g2_struct;
	def_structure_graph_node_variable = defstruct_g2_graph_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_graph_node_variable);
}

/* MAKE-GRAPH-NODE-1 */
Object make_graph_node_1(graph_node_item,graph_node_superior,
	    graph_node_depth,graph_node_short_representation,graph_node_graph)
    Object graph_node_item, graph_node_superior, graph_node_depth;
    Object graph_node_short_representation, graph_node_graph;
{
    Object def_structure_graph_node_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(162,41);
    def_structure_graph_node_variable = 
	    ISVREF(Chain_of_available_graph_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_graph_node_variable) {
	svref_arg_1 = Chain_of_available_graph_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_graph_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_graph_node_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graph_node_g2_struct;
    }
    else
	def_structure_graph_node_variable = 
		make_permanent_graph_node_structure_internal();
    inline_note_allocate_cons(def_structure_graph_node_variable,Nil);
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)2L)) = 
	    graph_node_item;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)4L)) = 
	    graph_node_superior;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)9L)) = 
	    graph_node_depth;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)3L)) = 
	    graph_node_short_representation;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)1L)) = 
	    graph_node_graph;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_graph_node_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)11L)) = Nil;
    ISVREF(def_structure_graph_node_variable,(SI_Long)12L) = FIX((SI_Long)0L);
    ISVREF(def_structure_graph_node_variable,(SI_Long)13L) = FIX((SI_Long)0L);
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_graph_node_variable,FIX((SI_Long)15L)) = Nil;
    return VALUES_1(def_structure_graph_node_variable);
}

/* RECLAIM-GRAPH-NODE-FUNCTION */
Object reclaim_graph_node_function(graph_node)
    Object graph_node;
{
    x_note_fn_call(162,42);
    return reclaim_graph_node_1(graph_node);
}

/* RECLAIM-GRAPH-NODE-LIST */
Object reclaim_graph_node_list(graph_nodes)
    Object graph_nodes;
{
    Object trailer_cons, graph_node_cons, graph_layout_cons, temp, svref_arg_2;

    x_note_fn_call(162,43);
    if (graph_nodes) {
	reclaim_graph_node_1(CAR(graph_nodes));
	trailer_cons = graph_nodes;
	graph_node_cons = CDR(graph_nodes);
      next_loop:
	if ( !TRUEP(graph_node_cons))
	    goto end_loop;
	reclaim_graph_node_1(CAR(graph_node_cons));
	trailer_cons = graph_node_cons;
	graph_node_cons = M_CDR(graph_node_cons);
	goto next_loop;
      end_loop:
	if (graph_nodes &&  !((SI_Long)0L == inline_debugging_consing())) {
	    graph_layout_cons = graph_nodes;
	  next_loop_1:
	    inline_note_reclaim_cons(graph_layout_cons,Qgraph_layout);
	    if (EQ(graph_layout_cons,trailer_cons))
		goto end_1;
	    else if ( !TRUEP(graph_layout_cons))
		goto end_1;
	    else
		graph_layout_cons = CDR(graph_layout_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_1:;
	}
	if (ISVREF(Available_graph_layout_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_graph_layout_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = graph_nodes;
	    temp = Available_graph_layout_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer_cons;
	}
	else {
	    temp = Available_graph_layout_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = graph_nodes;
	    temp = Available_graph_layout_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer_cons;
	}
	M_CDR(trailer_cons) = Nil;
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_dynamic_workspace_associated_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_dynamic_workspace_associated_structures, Qchain_of_available_dynamic_workspace_associated_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Dynamic_workspace_associated_structure_count, Qdynamic_workspace_associated_structure_count);

Object Chain_of_available_dynamic_workspace_associated_structures_vector = UNBOUND;

/* DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object dynamic_workspace_associated_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(162,44);
    temp = Dynamic_workspace_associated_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-COUNT */
Object outstanding_dynamic_workspace_associated_structure_count()
{
    Object def_structure_dynamic_workspace_associated_structure_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(162,45);
    gensymed_symbol = IFIX(Dynamic_workspace_associated_structure_count);
    def_structure_dynamic_workspace_associated_structure_variable = 
	    Chain_of_available_dynamic_workspace_associated_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_dynamic_workspace_associated_structure_variable))
	goto end_loop;
    def_structure_dynamic_workspace_associated_structure_variable = 
	    ISVREF(def_structure_dynamic_workspace_associated_structure_variable,
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

/* RECLAIM-DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-1 */
Object reclaim_dynamic_workspace_associated_structure_1(dynamic_workspace_associated_structure)
    Object dynamic_workspace_associated_structure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(162,46);
    inline_note_reclaim_cons(dynamic_workspace_associated_structure,Nil);
    temp = 
	    ISVREF(Chain_of_available_dynamic_workspace_associated_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(dynamic_workspace_associated_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_dynamic_workspace_associated_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = dynamic_workspace_associated_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE */
Object reclaim_structure_for_dynamic_workspace_associated_structure(dynamic_workspace_associated_structure)
    Object dynamic_workspace_associated_structure;
{
    x_note_fn_call(162,47);
    return reclaim_dynamic_workspace_associated_structure_1(dynamic_workspace_associated_structure);
}

static Object Qg2_defstruct_structure_name_dynamic_workspace_associated_structure_g2_struct;  /* g2-defstruct-structure-name::dynamic-workspace-associated-structure-g2-struct */

/* MAKE-PERMANENT-DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_dynamic_workspace_associated_structure_structure_internal()
{
    Object def_structure_dynamic_workspace_associated_structure_variable;
    Object defstruct_g2_dynamic_workspace_associated_structure_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(162,48);
    def_structure_dynamic_workspace_associated_structure_variable = Nil;
    atomic_incff_symval(Qdynamic_workspace_associated_structure_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_dynamic_workspace_associated_structure_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_dynamic_workspace_associated_structure_variable = 
		the_array;
	SVREF(defstruct_g2_dynamic_workspace_associated_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_dynamic_workspace_associated_structure_g2_struct;
	def_structure_dynamic_workspace_associated_structure_variable = 
		defstruct_g2_dynamic_workspace_associated_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_dynamic_workspace_associated_structure_variable);
}

/* MAKE-DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-1 */
Object make_dynamic_workspace_associated_structure_1()
{
    Object def_structure_dynamic_workspace_associated_structure_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(162,49);
    def_structure_dynamic_workspace_associated_structure_variable = 
	    ISVREF(Chain_of_available_dynamic_workspace_associated_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_dynamic_workspace_associated_structure_variable) {
	svref_arg_1 = 
		Chain_of_available_dynamic_workspace_associated_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_dynamic_workspace_associated_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_dynamic_workspace_associated_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_dynamic_workspace_associated_structure_g2_struct;
    }
    else
	def_structure_dynamic_workspace_associated_structure_variable = 
		make_permanent_dynamic_workspace_associated_structure_structure_internal();
    inline_note_allocate_cons(def_structure_dynamic_workspace_associated_structure_variable,
	    Nil);
    SVREF(def_structure_dynamic_workspace_associated_structure_variable,
	    FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_dynamic_workspace_associated_structure_variable);
}

/* RECLAIM-ASSOCIATED-DYNAMIC-STRUCTURE-VALUE */
Object reclaim_associated_dynamic_structure_value(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object structure_reclaimer_qm, temp;

    x_note_fn_call(162,50);
    structure_reclaimer_qm = ISVREF(value,(SI_Long)1L);
    if (structure_reclaimer_qm) {
	temp = SYMBOL_FUNCTION(structure_reclaimer_qm);
	FUNCALL_1(temp,value);
    }
    return VALUES_1(Nil);
}

static Object Qsxhashw;            /* sxhashw */

/* REPRESENTED-IN-GRAPH-DISPLAY-P */
Object represented_in_graph_display_p(thing,graph_display)
    Object thing, graph_display;
{
    Object current_graph_layout_hashing_function, hash_table, temp, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_2, entry_hash;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,51);
    current_graph_layout_hashing_function = ISVREF(graph_display,(SI_Long)10L);
    hash_table = ISVREF(graph_display,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_graph_layout_hashing_function,Qcurrent_graph_layout_hashing_function,current_graph_layout_hashing_function,
	    0);
      temp = Current_graph_layout_hashing_function;
      if (temp);
      else
	  temp = Qsxhashw;
      temp = SYMBOL_FUNCTION(temp);
      gensymed_symbol = IFIX(FUNCALL_1(temp,thing));
      temp_1 = gensymed_symbol % (SI_Long)43L;
      temp = SVREF(hash_table,FIX(temp_1));
      skip_list = CDR(temp);
      key_value = thing;
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
      if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? (EQ(key_value,
	      ISVREF(curr,(SI_Long)2L)) ? TRUEP(ISVREF(curr,(SI_Long)3L)) :
	       TRUEP(Nil)) : TRUEP(Nil))
	  result = VALUES_1(T);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qleft;               /* left */

static Object Qtop;                /* top */

/* GRAPH-FRAME-HIERARCHY-FUNCTION */
Object graph_frame_hierarchy_function(item,children_function,
	    extra_argument_qm,short_representation_function,hash_function,
	    orientation,vertical_spacing,horizontal_spacing,
	    pane_for_workspace_display_qm,class_of_workspace,workspace_qm,
	    left_edge_for_graph_qm,top_edge_for_graph_qm)
    Object item, children_function, extra_argument_qm;
    Object short_representation_function, hash_function, orientation;
    Object vertical_spacing, horizontal_spacing, pane_for_workspace_display_qm;
    Object class_of_workspace, workspace_qm, left_edge_for_graph_qm;
    Object top_edge_for_graph_qm;
{
    Object current_graph_layout_hashing_function, graph, workspace;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,52);
    current_graph_layout_hashing_function = hash_function;
    graph = make_graph_display_1(item,orientation,vertical_spacing,
	    horizontal_spacing,children_function,extra_argument_qm,
	    short_representation_function,hash_function);
    workspace = workspace_qm;
    if (workspace);
    else
	workspace = make_workspace(6,class_of_workspace,Nil,Nil,Nil,Nil,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_graph_layout_hashing_function,Qcurrent_graph_layout_hashing_function,current_graph_layout_hashing_function,
	    0);
      SVREF(graph,FIX((SI_Long)20L)) = workspace;
      represent_items_in_graph(graph,item,children_function,
	      extra_argument_qm,short_representation_function);
      determine_node_positions(3,graph,left_edge_for_graph_qm,
	      top_edge_for_graph_qm);
      display_graph_on_workspace(graph);
      if (pane_for_workspace_display_qm)
	  put_workspace_on_pane_function(workspace,
		  pane_for_workspace_display_qm,Qleft,Qtop,T,
		  FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
      result = VALUES_1(graph);
    POP_SPECIAL();
    return result;
}

Object Original_graph_depth = UNBOUND;

/* REPRESENT-ITEMS-IN-GRAPH */
Object represent_items_in_graph(graph,item,children_function,
	    extra_argument_qm,short_rep_function)
    Object graph, item, children_function, extra_argument_qm;
    Object short_rep_function;
{
    Object node_table, row_array, root_node, maximum_height_array;
    Object result;

    x_note_fn_call(162,53);
    node_table = ISVREF(graph,(SI_Long)4L);
    row_array = allocate_managed_array(1,Original_graph_depth);
    root_node = Nil;
    result = make_node_for_item(item,children_function,extra_argument_qm,
	    short_rep_function,node_table,row_array,Nil,FIX((SI_Long)0L),
	    graph);
    MVS_2(result,root_node,row_array);
    SVREF(graph,FIX((SI_Long)3L)) = root_node;
    maximum_height_array = allocate_managed_array(1,ISVREF(graph,
	    (SI_Long)16L));
    SVREF(graph,FIX((SI_Long)17L)) = maximum_height_array;
    initialize_graph_display_maximum_height_array(maximum_height_array,
	    row_array,ISVREF(graph,(SI_Long)1L));
    return reclaim_managed_array(row_array);
}

/* MAKE-NODE-FOR-ITEM */
Object make_node_for_item(item,children_function,extra_argument_qm,
	    short_rep_function,node_table,row_array,superior,depth,graph)
    Object item, children_function, extra_argument_qm, short_rep_function;
    Object node_table, row_array, superior, depth, graph;
{
    Object temp, new_node, existing_node_qm, node_to_left_qm, temp_2;
    Object new_depth, children, child, ab_loop_list_, child_node, child_nodes;
    Object ab_loopvar_, ab_loopvar__1;
    SI_Long old_length, gensymed_symbol, temp_1, svref_arg_2;
    SI_Long maximum_child_depth;
    Object result;

    x_note_fn_call(162,54);
    old_length = IFIX(ISVREF(row_array,(SI_Long)1L));
    temp = SYMBOL_FUNCTION(short_rep_function);
    new_node = make_graph_node_1(item,superior,depth,FUNCALL_1(temp,item),
	    graph);
    temp = Current_graph_layout_hashing_function;
    if (temp);
    else
	temp = Qsxhashw;
    temp = SYMBOL_FUNCTION(temp);
    gensymed_symbol = IFIX(FUNCALL_1(temp,item));
    temp_1 = gensymed_symbol % (SI_Long)43L;
    existing_node_qm = set_skip_list_entry(SVREF(node_table,FIX(temp_1)),
	    FIX((SI_Long)31L),Qeq,Nil,Nil,item,FIX(gensymed_symbol),new_node);
    if (IFIX(depth) >= old_length)
	row_array = adjust_managed_array(2,row_array,FIX(old_length + 
		IFIX(Original_graph_depth)));
    node_to_left_qm = FIXNUM_LE(ISVREF(row_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(row_array,
	    IFIX(FIXNUM_ADD(depth,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(row_array,(IFIX(depth) >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),IFIX(depth) & (SI_Long)1023L);
    if (node_to_left_qm) {
	SVREF(node_to_left_qm,FIX((SI_Long)8L)) = new_node;
	SVREF(new_node,FIX((SI_Long)7L)) = node_to_left_qm;
    }
    if (FIXNUM_GE(depth,ISVREF(graph,(SI_Long)16L))) {
	temp_2 = FIXNUM_ADD1(depth);
	SVREF(graph,FIX((SI_Long)16L)) = temp_2;
    }
    SVREF(new_node,FIX((SI_Long)9L)) = depth;
    if (FIXNUM_LE(ISVREF(row_array,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_2 = FIXNUM_ADD(depth,Managed_array_index_offset);
	SVREF(row_array,temp_2) = new_node;
    }
    else {
	temp_2 = ISVREF(row_array,(IFIX(depth) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = IFIX(depth) & (SI_Long)1023L;
	ISVREF(temp_2,svref_arg_2) = new_node;
    }
    if ( !EQ(existing_node_qm,new_node)) {
	SVREF(new_node,FIX((SI_Long)10L)) = existing_node_qm;
	temp_2 = graph_layout_cons_1(new_node,ISVREF(existing_node_qm,
		(SI_Long)11L));
	SVREF(existing_node_qm,FIX((SI_Long)11L)) = temp_2;
    }
    else {
	new_depth = FIXNUM_ADD1(depth);
	temp = SYMBOL_FUNCTION(children_function);
	children = FUNCALL_2(temp,item,extra_argument_qm);
	maximum_child_depth = (SI_Long)0L;
	child = Nil;
	ab_loop_list_ = children;
	child_node = Nil;
	child_nodes = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	child = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result = make_node_for_item(child,children_function,
		extra_argument_qm,short_rep_function,node_table,row_array,
		new_node,new_depth,graph);
	MVS_2(result,child_node,row_array);
	ab_loopvar__1 = graph_layout_cons_1(child_node,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    child_nodes = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	temp_1 = IFIX(FIXNUM_ADD1(ISVREF(child_node,(SI_Long)6L)));
	maximum_child_depth = MAX(maximum_child_depth,temp_1);
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(children);
	ISVREF(new_node,(SI_Long)6L) = FIX(maximum_child_depth);
	SVREF(new_node,FIX((SI_Long)5L)) = child_nodes;
    }
    return VALUES_2(new_node,row_array);
}

DEFINE_VARIABLE_WITH_SYMBOL(Graph_display_changed_during_update_qm, Qgraph_display_changed_during_update_qm);

/* UPDATE-GRAPH-DISPLAY */
Object update_graph_display(graph)
    Object graph;
{
    Object current_graph_layout_hashing_function;
    Object graph_display_changed_during_update_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(162,55);
    current_graph_layout_hashing_function = ISVREF(graph,(SI_Long)10L);
    graph_display_changed_during_update_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Graph_display_changed_during_update_qm,Qgraph_display_changed_during_update_qm,graph_display_changed_during_update_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_graph_layout_hashing_function,Qcurrent_graph_layout_hashing_function,current_graph_layout_hashing_function,
	      0);
	update_graph_display_nodes(graph);
	determine_node_positions(1,graph);
	update_display_of_graph_on_workspace(graph);
	reclaim_graph_node_1(ISVREF(graph,(SI_Long)18L));
	SVREF(graph,FIX((SI_Long)18L)) = Nil;
	clear_graph_node_of_graphed_thing(ISVREF(graph,(SI_Long)19L));
	result = VALUES_1(Graph_display_changed_during_update_qm);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* UPDATE-GRAPH-DISPLAY-NODES */
Object update_graph_display_nodes(graph)
    Object graph;
{
    Object node_table, row_array, item, children_function, extra_argument_qm;
    Object short_rep_function, svref_new_value, maximum_height_array;

    x_note_fn_call(162,56);
    node_table = ISVREF(graph,(SI_Long)19L);
    row_array = allocate_managed_array(1,Original_graph_depth);
    item = ISVREF(graph,(SI_Long)2L);
    children_function = ISVREF(graph,(SI_Long)7L);
    extra_argument_qm = ISVREF(graph,(SI_Long)8L);
    short_rep_function = ISVREF(graph,(SI_Long)9L);
    svref_new_value = ISVREF(graph,(SI_Long)4L);
    SVREF(graph,FIX((SI_Long)19L)) = svref_new_value;
    SVREF(graph,FIX((SI_Long)4L)) = node_table;
    svref_new_value = ISVREF(graph,(SI_Long)3L);
    SVREF(graph,FIX((SI_Long)18L)) = svref_new_value;
    SVREF(graph,FIX((SI_Long)3L)) = Nil;
    svref_new_value = make_or_update_node_for_item(item,children_function,
	    extra_argument_qm,short_rep_function,node_table,row_array,Nil,
	    FIX((SI_Long)0L),graph);
    SVREF(graph,FIX((SI_Long)3L)) = svref_new_value;
    maximum_height_array = allocate_managed_array(1,ISVREF(graph,
	    (SI_Long)16L));
    SVREF(graph,FIX((SI_Long)17L)) = maximum_height_array;
    initialize_graph_display_maximum_height_array(maximum_height_array,
	    row_array,ISVREF(graph,(SI_Long)1L));
    return reclaim_managed_array(row_array);
}

/* PREVIOUS-ACTUAL-GRAPH-NODE */
Object previous_actual_graph_node(new_node,previous_node_version)
    Object new_node, previous_node_version;
{
    Object superior_graph_node_qm, superior_item_qm;
    Object previous_superior_graph_node_qm, previous_superior_item_qm;
    Object previous_node, ab_loop_list_;

    x_note_fn_call(162,57);
    superior_graph_node_qm = ISVREF(new_node,(SI_Long)4L);
    superior_item_qm = superior_graph_node_qm ? 
	    ISVREF(superior_graph_node_qm,(SI_Long)2L) : Nil;
    previous_superior_graph_node_qm = ISVREF(previous_node_version,
	    (SI_Long)4L);
    previous_superior_item_qm = previous_superior_graph_node_qm ? 
	    ISVREF(previous_superior_graph_node_qm,(SI_Long)2L) : Nil;
    if (EQ(superior_item_qm,previous_superior_item_qm))
	return VALUES_1(previous_node_version);
    else {
	previous_node = Nil;
	ab_loop_list_ = ISVREF(previous_node_version,(SI_Long)11L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	previous_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	previous_superior_graph_node_qm = ISVREF(previous_node,(SI_Long)4L);
	if (previous_superior_graph_node_qm && EQ(superior_item_qm,
		ISVREF(previous_superior_graph_node_qm,(SI_Long)2L)))
	    return VALUES_1(previous_node);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* MAKE-OR-UPDATE-NODE-FOR-ITEM */
Object make_or_update_node_for_item(item,children_function,
	    extra_argument_qm,short_rep_function,node_table,row_array,
	    superior,depth,graph)
    Object item, children_function, extra_argument_qm, short_rep_function;
    Object node_table, row_array, superior, depth, graph;
{
    Object old_length, new_node, temp, existing_update_node_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object previous_expanded_graph_node_qm, previous_actual_graph_node_qm;
    Object node_to_left_qm, temp_3, new_depth, children, child, ab_loop_list_;
    Object child_node, child_nodes, ab_loopvar_, ab_loopvar__1;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, svref_arg_2, maximum_child_depth;
    Object result;

    x_note_fn_call(162,58);
    old_length = ISVREF(row_array,(SI_Long)1L);
    new_node = make_graph_node_1(item,superior,depth,Nil,graph);
    temp = Current_graph_layout_hashing_function;
    if (temp);
    else
	temp = Qsxhashw;
    temp = SYMBOL_FUNCTION(temp);
    gensymed_symbol = IFIX(FUNCALL_1(temp,item));
    temp_1 = gensymed_symbol % (SI_Long)43L;
    existing_update_node_qm = set_skip_list_entry(SVREF(node_table,
	    FIX(temp_1)),FIX((SI_Long)31L),Qeq,Nil,Nil,item,
	    FIX(gensymed_symbol),new_node);
    temp = Current_graph_layout_hashing_function;
    if (temp);
    else
	temp = Qsxhashw;
    temp = SYMBOL_FUNCTION(temp);
    gensymed_symbol = IFIX(FUNCALL_1(temp,item));
    temp = ISVREF(graph,(SI_Long)19L);
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = item;
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
    previous_expanded_graph_node_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
	    key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
	    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
    previous_actual_graph_node_qm = previous_expanded_graph_node_qm ? 
	    previous_actual_graph_node(new_node,
	    previous_expanded_graph_node_qm) : Nil;
    node_to_left_qm = FIXNUM_LE(ISVREF(row_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(row_array,
	    IFIX(FIXNUM_ADD(depth,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(row_array,(IFIX(depth) >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),IFIX(depth) & (SI_Long)1023L);
    if (FIXNUM_GE(depth,old_length))
	row_array = adjust_managed_array(2,row_array,FIXNUM_ADD(old_length,
		Original_graph_depth));
    if (previous_actual_graph_node_qm) {
	SVREF(new_node,FIX((SI_Long)15L)) = previous_actual_graph_node_qm;
	temp_3 = ISVREF(previous_actual_graph_node_qm,(SI_Long)3L);
	SVREF(new_node,FIX((SI_Long)3L)) = temp_3;
	SVREF(previous_actual_graph_node_qm,FIX((SI_Long)3L)) = Nil;
    }
    else {
	temp = SYMBOL_FUNCTION(short_rep_function);
	temp_3 = FUNCALL_1(temp,item);
	SVREF(new_node,FIX((SI_Long)3L)) = temp_3;
    }
    if (node_to_left_qm) {
	SVREF(node_to_left_qm,FIX((SI_Long)8L)) = new_node;
	SVREF(new_node,FIX((SI_Long)7L)) = node_to_left_qm;
    }
    if (FIXNUM_GE(depth,ISVREF(graph,(SI_Long)16L))) {
	temp_3 = FIXNUM_ADD1(depth);
	SVREF(graph,FIX((SI_Long)16L)) = temp_3;
    }
    SVREF(new_node,FIX((SI_Long)9L)) = depth;
    if (FIXNUM_LE(ISVREF(row_array,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_3 = FIXNUM_ADD(depth,Managed_array_index_offset);
	SVREF(row_array,temp_3) = new_node;
    }
    else {
	temp_3 = ISVREF(row_array,(IFIX(depth) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = IFIX(depth) & (SI_Long)1023L;
	ISVREF(temp_3,svref_arg_2) = new_node;
    }
    if ( !EQ(existing_update_node_qm,new_node)) {
	SVREF(new_node,FIX((SI_Long)10L)) = existing_update_node_qm;
	temp_3 = graph_layout_cons_1(new_node,
		ISVREF(existing_update_node_qm,(SI_Long)11L));
	SVREF(existing_update_node_qm,FIX((SI_Long)11L)) = temp_3;
    }
    else {
	new_depth = FIXNUM_ADD1(depth);
	temp = SYMBOL_FUNCTION(children_function);
	children = FUNCALL_2(temp,item,extra_argument_qm);
	maximum_child_depth = (SI_Long)0L;
	child = Nil;
	ab_loop_list_ = children;
	child_node = Nil;
	child_nodes = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	child = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	child_node = make_or_update_node_for_item(child,children_function,
		extra_argument_qm,short_rep_function,node_table,row_array,
		new_node,new_depth,graph);
	ab_loopvar__1 = graph_layout_cons_1(child_node,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    child_nodes = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	temp_1 = IFIX(FIXNUM_ADD1(ISVREF(child_node,(SI_Long)6L)));
	maximum_child_depth = MAX(maximum_child_depth,temp_1);
	goto next_loop_3;
      end_loop_3:
	reclaim_gensym_list_1(children);
	ISVREF(new_node,(SI_Long)6L) = FIX(maximum_child_depth);
	SVREF(new_node,FIX((SI_Long)5L)) = child_nodes;
    }
    return VALUES_1(new_node);
}

static Object Qvertical;           /* vertical */

/* INITIALIZE-GRAPH-DISPLAY-MAXIMUM-HEIGHT-ARRAY */
Object initialize_graph_display_maximum_height_array(maximum_height_array,
	    row_array,orientation)
    Object maximum_height_array, row_array, orientation;
{
    Object maximum_height, node, short_rep, gensymed_symbol_1, temp;
    Object svref_new_value;
    SI_Long row_number, ab_loop_bind_, gensymed_symbol, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(162,59);
    row_number = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(maximum_height_array,(SI_Long)1L));
  next_loop:
    if (row_number >= ab_loop_bind_)
	goto end_loop;
    maximum_height = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Maximum_height,Qmaximum_height,maximum_height,0);
      node = FIXNUM_LE(ISVREF(row_array,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(row_array,row_number + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(row_array,
	      (row_number >>  -  - (SI_Long)10L) + (SI_Long)2L),row_number 
	      & (SI_Long)1023L);
      short_rep = Nil;
    next_loop_1:
      if ( !TRUEP(node))
	  goto end_loop_1;
      short_rep = ISVREF(node,(SI_Long)3L);
      if (EQ(orientation,Qvertical)) {
	  gensymed_symbol = IFIX(Maximum_height);
	  gensymed_symbol_1 = ISVREF(short_rep,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	  gensymed_symbol_1 = ISVREF(short_rep,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	  gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	  Maximum_height = FIX(MAX(gensymed_symbol,gensymed_symbol_2));
      }
      else {
	  gensymed_symbol = IFIX(Maximum_height);
	  gensymed_symbol_1 = ISVREF(short_rep,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	  gensymed_symbol_1 = ISVREF(short_rep,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	  gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	  Maximum_height = FIX(MAX(gensymed_symbol,gensymed_symbol_2));
      }
      node = ISVREF(node,(SI_Long)7L);
      goto next_loop_1;
    end_loop_1:
      if (FIXNUM_LE(ISVREF(maximum_height_array,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  svref_arg_2 = row_number + IFIX(Managed_array_index_offset);
	  temp = Maximum_height;
	  ISVREF(maximum_height_array,svref_arg_2) = temp;
      }
      else {
	  temp = ISVREF(maximum_height_array,(row_number >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = row_number & (SI_Long)1023L;
	  svref_new_value = Maximum_height;
	  ISVREF(temp,svref_arg_2) = svref_new_value;
      }
    POP_SPECIAL();
    row_number = row_number + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DETERMINE-NODE-POSITIONS */
Object determine_node_positions varargs_1(int, n)
{
    Object graph;
    Object left_edge_for_graph_qm, top_edge_for_graph_qm, root;
    Object svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(162,60);
    INIT_ARGS_nonrelocating();
    graph = REQUIRED_ARG_nonrelocating();
    left_edge_for_graph_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    top_edge_for_graph_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    root = ISVREF(graph,(SI_Long)3L);
    ISVREF(graph,(SI_Long)12L) = FIX((SI_Long)0L);
    ISVREF(graph,(SI_Long)13L) = FIX((SI_Long)0L);
    ISVREF(graph,(SI_Long)14L) = FIX((SI_Long)0L);
    ISVREF(graph,(SI_Long)15L) = FIX((SI_Long)0L);
    if (EQ(ISVREF(graph,(SI_Long)1L),Qvertical)) {
	position_node_vertically(root);
	if (IFIX(ISVREF(root,(SI_Long)12L)) != (SI_Long)0L)
	    shift_graph_node_and_children_to_right(root,graph,
		    FIXNUM_NEGATE(ISVREF(root,(SI_Long)12L)));
	svref_new_value = FIXNUM_SUB1(maximum_graph_node_extent_to_left(root));
	SVREF(graph,FIX((SI_Long)12L)) = svref_new_value;
	svref_new_value = 
		FIXNUM_ADD1(maximum_graph_node_extent_to_right(root));
	SVREF(graph,FIX((SI_Long)13L)) = svref_new_value;
    }
    else {
	position_node_horizontally(root);
	if (IFIX(ISVREF(root,(SI_Long)13L)) != (SI_Long)0L)
	    shift_graph_node_and_children_toward_bottom(root,graph,
		    FIXNUM_NEGATE(ISVREF(root,(SI_Long)13L)));
	svref_new_value = FIXNUM_SUB1(maximum_graph_node_extent_to_top(root));
	SVREF(graph,FIX((SI_Long)14L)) = svref_new_value;
	svref_new_value = 
		FIXNUM_ADD1(maximum_graph_node_extent_to_bottom(root));
	SVREF(graph,FIX((SI_Long)15L)) = svref_new_value;
    }
    if (left_edge_for_graph_qm || top_edge_for_graph_qm) {
	if (left_edge_for_graph_qm)
	    shift_graph_node_and_children_to_right(root,graph,
		    FIXNUM_MINUS(left_edge_for_graph_qm,ISVREF(graph,
		    (SI_Long)12L)));
	if (top_edge_for_graph_qm)
	    shift_graph_node_and_children_toward_bottom(root,graph,
		    FIXNUM_MINUS(top_edge_for_graph_qm,ISVREF(graph,
		    (SI_Long)14L)));
	svref_new_value = FIXNUM_SUB1(maximum_graph_node_extent_to_left(root));
	SVREF(graph,FIX((SI_Long)12L)) = svref_new_value;
	svref_new_value = 
		FIXNUM_ADD1(maximum_graph_node_extent_to_right(root));
	SVREF(graph,FIX((SI_Long)13L)) = svref_new_value;
	svref_new_value = FIXNUM_SUB1(maximum_graph_node_extent_to_top(root));
	SVREF(graph,FIX((SI_Long)14L)) = svref_new_value;
	svref_new_value = 
		FIXNUM_ADD1(maximum_graph_node_extent_to_bottom(root));
	SVREF(graph,FIX((SI_Long)15L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* MAXIMUM-GRAPH-NODE-EXTENT-TO-RIGHT */
Object maximum_graph_node_extent_to_right(graph_node)
    Object graph_node;
{
    Object block, gensymed_symbol_1, kid, ab_loop_list_;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3, right_edge;
    SI_Long temp, temp_1;

    x_note_fn_call(162,61);
    gensymed_symbol = IFIX(ISVREF(graph_node,(SI_Long)12L));
    block = ISVREF(graph_node,(SI_Long)3L);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    right_edge = gensymed_symbol + gensymed_symbol_2;
    kid = Nil;
    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = right_edge;
    temp_1 = IFIX(maximum_graph_node_extent_to_right(kid));
    right_edge = MAX(temp,temp_1);
    goto next_loop;
  end_loop:;
    return VALUES_1(FIX(right_edge));
}

/* MAXIMUM-GRAPH-NODE-EXTENT-TO-LEFT */
Object maximum_graph_node_extent_to_left(graph_node)
    Object graph_node;
{
    Object kid, ab_loop_list_;
    SI_Long left_edge, kid_left;

    x_note_fn_call(162,62);
    left_edge = IFIX(ISVREF(graph_node,(SI_Long)12L));
    kid = Nil;
    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
    kid_left = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    kid_left = IFIX(maximum_graph_node_extent_to_left(kid));
    if (kid_left < left_edge)
	left_edge = kid_left;
    goto next_loop;
  end_loop:;
    return VALUES_1(FIX(left_edge));
}

/* MAXIMUM-GRAPH-NODE-EXTENT-TO-BOTTOM */
Object maximum_graph_node_extent_to_bottom(graph_node)
    Object graph_node;
{
    Object block, gensymed_symbol_1, kid, ab_loop_list_;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3, bottom_edge;
    SI_Long temp, temp_1;

    x_note_fn_call(162,63);
    gensymed_symbol = IFIX(ISVREF(graph_node,(SI_Long)13L));
    block = ISVREF(graph_node,(SI_Long)3L);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    bottom_edge = gensymed_symbol + gensymed_symbol_2;
    kid = Nil;
    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = bottom_edge;
    temp_1 = IFIX(maximum_graph_node_extent_to_bottom(kid));
    bottom_edge = MAX(temp,temp_1);
    goto next_loop;
  end_loop:;
    return VALUES_1(FIX(bottom_edge));
}

/* MAXIMUM-GRAPH-NODE-EXTENT-TO-TOP */
Object maximum_graph_node_extent_to_top(graph_node)
    Object graph_node;
{
    Object kid, ab_loop_list_;
    SI_Long top_edge, kid_top;

    x_note_fn_call(162,64);
    top_edge = IFIX(ISVREF(graph_node,(SI_Long)13L));
    kid = Nil;
    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
    kid_top = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    kid_top = IFIX(maximum_graph_node_extent_to_top(kid));
    if (kid_top < top_edge)
	top_edge = kid_top;
    goto next_loop;
  end_loop:;
    return VALUES_1(FIX(top_edge));
}

/* POSITION-NODE-VERTICALLY */
Object position_node_vertically(graph_node)
    Object graph_node;
{
    Object graph, short_rep, depth, superior_node_qm, temp, gensymed_symbol;
    Object gensymed_symbol_1, y_position, kids, first_kid, kid, ab_loop_list_;
    Object left_edge, last_kid, block, svref_new_value_1, node_to_left_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long right_edge, svref_new_value;

    x_note_fn_call(162,65);
    graph = ISVREF(graph_node,(SI_Long)1L);
    short_rep = ISVREF(graph_node,(SI_Long)3L);
    depth = ISVREF(graph_node,(SI_Long)9L);
    superior_node_qm = ISVREF(graph_node,(SI_Long)4L);
    if (superior_node_qm) {
	temp = ISVREF(superior_node_qm,(SI_Long)13L);
	gensymed_symbol = ISVREF(graph,(SI_Long)17L);
	gensymed_symbol_1 = FIXNUM_SUB1(depth);
	y_position = FIXNUM_ADD(FIXNUM_ADD(temp,
		FIXNUM_LE(ISVREF(ISVREF(graph,(SI_Long)17L),(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(ISVREF(graph,
		(SI_Long)17L),IFIX(FIXNUM_ADD(gensymed_symbol_1,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) >>  
		-  - (SI_Long)10L) + (SI_Long)2L),IFIX(gensymed_symbol_1) 
		& (SI_Long)1023L)),ISVREF(graph,(SI_Long)5L));
    }
    else
	y_position = ISVREF(graph,(SI_Long)14L);
    kids = ISVREF(graph_node,(SI_Long)5L);
    SVREF(graph_node,FIX((SI_Long)13L)) = y_position;
    if (kids) {
	first_kid = FIRST(kids);
	kid = Nil;
	ab_loop_list_ = kids;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	kid = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	position_node_vertically(kid);
	if ( !EQ(kid,first_kid))
	    pack_graph_node_to_left(kid);
	goto next_loop;
      end_loop:;
	left_edge = ISVREF(FIRST(kids),(SI_Long)12L);
	temp = last(kids,_);
	last_kid = CAR(temp);
	gensymed_symbol_2 = IFIX(ISVREF(last_kid,(SI_Long)12L));
	block = ISVREF(last_kid,(SI_Long)3L);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	right_edge = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_2 = IFIX(left_edge) + (right_edge - 
		IFIX(left_edge) >>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 >>  -  - gensymed_symbol_4;
	svref_new_value = gensymed_symbol_2 - gensymed_symbol_3;
	ISVREF(graph_node,(SI_Long)12L) = FIX(svref_new_value);
	if (FIXNUM_LT(ISVREF(graph_node,(SI_Long)12L),ISVREF(graph,
		(SI_Long)12L))) {
	    svref_new_value_1 = ISVREF(graph_node,(SI_Long)12L);
	    SVREF(graph,FIX((SI_Long)12L)) = svref_new_value_1;
	}
	gensymed_symbol_2 = IFIX(ISVREF(graph_node,(SI_Long)12L));
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	if (FIXNUM_GT(FIX(gensymed_symbol_2 + gensymed_symbol_3),
		ISVREF(graph,(SI_Long)13L))) {
	    gensymed_symbol_2 = IFIX(ISVREF(graph_node,(SI_Long)12L));
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    svref_new_value = gensymed_symbol_2 + gensymed_symbol_3;
	    return VALUES_1(ISVREF(graph,(SI_Long)13L) = FIX(svref_new_value));
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	node_to_left_qm = ISVREF(graph_node,(SI_Long)7L);
	if (FIXNUM_EQ(ISVREF(graph,(SI_Long)13L),ISVREF(graph,(SI_Long)12L)))
	    svref_new_value_1 = ISVREF(graph,(SI_Long)12L);
	else {
	    gensymed_symbol_2 = IFIX(ISVREF(graph,(SI_Long)13L));
	    gensymed_symbol_3 = IFIX(ISVREF(graph,(SI_Long)6L));
	    gensymed_symbol_4 = node_to_left_qm &&  !EQ(ISVREF(graph_node,
		    (SI_Long)4L),ISVREF(node_to_left_qm,(SI_Long)4L)) ? 
		    IFIX(ISVREF(graph,(SI_Long)11L)) : (SI_Long)0L;
	    svref_new_value_1 = FIX(gensymed_symbol_2 + gensymed_symbol_3 
		    + gensymed_symbol_4);
	}
	SVREF(graph_node,FIX((SI_Long)12L)) = svref_new_value_1;
	gensymed_symbol_2 = IFIX(ISVREF(graph_node,(SI_Long)12L));
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	svref_new_value = gensymed_symbol_2 + gensymed_symbol_3;
	ISVREF(graph,(SI_Long)13L) = FIX(svref_new_value);
	gensymed_symbol_2 = IFIX(y_position);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	if (FIXNUM_GT(FIX(gensymed_symbol_2 + gensymed_symbol_3),
		ISVREF(graph,(SI_Long)15L))) {
	    gensymed_symbol_2 = IFIX(y_position);
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    svref_new_value = gensymed_symbol_2 + gensymed_symbol_3;
	    return VALUES_1(ISVREF(graph,(SI_Long)15L) = FIX(svref_new_value));
	}
	else
	    return VALUES_1(Nil);
    }
}

/* SHIFT-GRAPH-NODE-AND-CHILDREN-TO-RIGHT */
Object shift_graph_node_and_children_to_right(graph_node,graph,shift_amount)
    Object graph_node, graph, shift_amount;
{
    Object incff_1_arg, new_x, kid, ab_loop_list_, block, gensymed_symbol_1;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long rightmost_extent;

    x_note_fn_call(162,66);
    incff_1_arg = shift_amount;
    new_x = FIXNUM_ADD(ISVREF(graph_node,(SI_Long)12L),incff_1_arg);
    SVREF(graph_node,FIX((SI_Long)12L)) = new_x;
    kid = Nil;
    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    shift_graph_node_and_children_to_right(kid,graph,shift_amount);
    goto next_loop;
  end_loop:;
    if (IFIX(shift_amount) > (SI_Long)0L) {
	gensymed_symbol = IFIX(new_x);
	block = ISVREF(graph_node,(SI_Long)3L);
	gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	rightmost_extent = gensymed_symbol + gensymed_symbol_2;
	if (rightmost_extent > IFIX(ISVREF(graph,(SI_Long)13L)))
	    ISVREF(graph,(SI_Long)13L) = FIX(rightmost_extent);
    }
    else if (FIXNUM_LT(new_x,ISVREF(graph,(SI_Long)12L)))
	SVREF(graph,FIX((SI_Long)12L)) = new_x;
    return VALUES_1(Nil);
}

/* SHIFT-GRAPH-NODE-AND-CHILDREN-TOWARD-BOTTOM */
Object shift_graph_node_and_children_toward_bottom(graph_node,graph,
	    shift_amount)
    Object graph_node, graph, shift_amount;
{
    Object incff_1_arg, new_y, kid, ab_loop_list_, block, gensymed_symbol_1;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bottommost_extent;

    x_note_fn_call(162,67);
    incff_1_arg = shift_amount;
    new_y = FIXNUM_ADD(ISVREF(graph_node,(SI_Long)13L),incff_1_arg);
    SVREF(graph_node,FIX((SI_Long)13L)) = new_y;
    kid = Nil;
    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    shift_graph_node_and_children_toward_bottom(kid,graph,shift_amount);
    goto next_loop;
  end_loop:;
    if (IFIX(shift_amount) > (SI_Long)0L) {
	gensymed_symbol = IFIX(new_y);
	block = ISVREF(graph_node,(SI_Long)3L);
	gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	bottommost_extent = gensymed_symbol + gensymed_symbol_2;
	if (bottommost_extent > IFIX(ISVREF(graph,(SI_Long)15L)))
	    ISVREF(graph,(SI_Long)15L) = FIX(bottommost_extent);
    }
    else if (FIXNUM_LT(new_y,ISVREF(graph,(SI_Long)14L)))
	SVREF(graph,FIX((SI_Long)14L)) = new_y;
    return VALUES_1(Nil);
}

/* PACK-GRAPH-NODE-TO-LEFT */
Object pack_graph_node_to_left(graph_node)
    Object graph_node;
{
    Object shift_amount_qm;

    x_note_fn_call(162,68);
    shift_amount_qm = graph_node_freedom_to_shift_left_qm(graph_node,
	    FIX((SI_Long)0L));
    if (shift_amount_qm)
	return shift_graph_node_and_children_to_right(graph_node,
		ISVREF(graph_node,(SI_Long)1L),FIXNUM_NEGATE(shift_amount_qm));
    else
	return VALUES_1(Nil);
}

/* PACK-GRAPH-NODE-TO-TOP */
Object pack_graph_node_to_top(graph_node)
    Object graph_node;
{
    Object shift_amount_qm;

    x_note_fn_call(162,69);
    shift_amount_qm = graph_node_freedom_to_shift_up_qm(graph_node,
	    FIX((SI_Long)0L));
    if (shift_amount_qm)
	return shift_graph_node_and_children_toward_bottom(graph_node,
		ISVREF(graph_node,(SI_Long)1L),FIXNUM_NEGATE(shift_amount_qm));
    else
	return VALUES_1(Nil);
}

/* GRAPH-NODE-FREEDOM-TO-SHIFT-LEFT? */
Object graph_node_freedom_to_shift_left_qm(graph_node,levels_to_ignore_init)
    Object graph_node, levels_to_ignore_init;
{
    Object freedom_qm, child_freedom_qm, kid, ab_loop_list_, temp;
    Object node_to_left_qm, graph_display, short_representation_to_left;
    Object gensymed_symbol_2;
    SI_Long levels_to_ignore, maximum_child_depth, kid_levels_to_ignore;
    SI_Long depth_seen, child_depth, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, freedom;
    Object result;

    x_note_fn_call(162,70);
    levels_to_ignore = IFIX(levels_to_ignore_init);
    maximum_child_depth = IFIX(ISVREF(graph_node,(SI_Long)6L));
    if (levels_to_ignore > maximum_child_depth)
	return VALUES_2(Nil,FIX(maximum_child_depth + (SI_Long)1L));
    else if (levels_to_ignore > (SI_Long)0L) {
	freedom_qm = Nil;
	kid_levels_to_ignore = levels_to_ignore - (SI_Long)1L;
	depth_seen = (SI_Long)0L;
	child_freedom_qm = Nil;
	child_depth = (SI_Long)0L;
	kid = Nil;
	ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	kid = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result = graph_node_freedom_to_shift_left_qm(kid,
		FIX(MAX(depth_seen,kid_levels_to_ignore)));
	MVS_2(result,child_freedom_qm,temp);
	child_depth = IFIX(temp);
	if (child_depth > depth_seen)
	    depth_seen = child_depth;
	if (child_freedom_qm && ( !TRUEP(freedom_qm) || 
		FIXNUM_LT(child_freedom_qm,freedom_qm)))
	    freedom_qm = child_freedom_qm;
	goto next_loop;
      end_loop:
	return VALUES_2(freedom_qm,FIX(depth_seen + (SI_Long)1L));
	return VALUES_1(Qnil);
    }
    else {
	node_to_left_qm = ISVREF(graph_node,(SI_Long)7L);
	graph_display = ISVREF(graph_node,(SI_Long)1L);
	if (node_to_left_qm) {
	    short_representation_to_left = ISVREF(node_to_left_qm,(SI_Long)3L);
	    gensymed_symbol = IFIX(ISVREF(graph_node,(SI_Long)12L));
	    gensymed_symbol_1 = IFIX(ISVREF(node_to_left_qm,(SI_Long)12L));
	    gensymed_symbol_2 = ISVREF(short_representation_to_left,
		    (SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_2 = ISVREF(short_representation_to_left,
		    (SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_3;
	    gensymed_symbol_3 = IFIX(ISVREF(graph_display,(SI_Long)6L));
	    gensymed_symbol_4 = EQ(ISVREF(graph_node,(SI_Long)4L),
		    ISVREF(node_to_left_qm,(SI_Long)4L)) ? (SI_Long)0L : 
		    IFIX(ISVREF(graph_display,(SI_Long)11L));
	    freedom = gensymed_symbol - gensymed_symbol_1 - 
		    gensymed_symbol_3 - gensymed_symbol_4;
	    depth_seen = (SI_Long)0L;
	    child_freedom_qm = Nil;
	    child_depth = (SI_Long)0L;
	    kid = Nil;
	    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    kid = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    result = graph_node_freedom_to_shift_left_qm(kid,FIX(depth_seen));
	    MVS_2(result,child_freedom_qm,temp);
	    child_depth = IFIX(temp);
	    if (child_depth > depth_seen)
		depth_seen = child_depth;
	    if (child_freedom_qm && IFIX(child_freedom_qm) < freedom)
		freedom = IFIX(child_freedom_qm);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_2(FIX(freedom),FIX(depth_seen + (SI_Long)1L));
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_2(Nil,FIX(maximum_child_depth + (SI_Long)1L));
    }
}

/* GRAPH-NODE-FREEDOM-TO-SHIFT-UP? */
Object graph_node_freedom_to_shift_up_qm(graph_node,levels_to_ignore_init)
    Object graph_node, levels_to_ignore_init;
{
    Object freedom_qm, child_freedom_qm, kid, ab_loop_list_, temp;
    Object node_to_left_qm, graph_display, short_representation_to_left;
    Object gensymed_symbol_2;
    SI_Long levels_to_ignore, maximum_child_depth, kid_levels_to_ignore;
    SI_Long depth_seen, child_depth, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, freedom;
    Object result;

    x_note_fn_call(162,71);
    levels_to_ignore = IFIX(levels_to_ignore_init);
    maximum_child_depth = IFIX(ISVREF(graph_node,(SI_Long)6L));
    if (levels_to_ignore > maximum_child_depth)
	return VALUES_2(Nil,FIX(maximum_child_depth + (SI_Long)1L));
    else if (levels_to_ignore > (SI_Long)0L) {
	freedom_qm = Nil;
	kid_levels_to_ignore = levels_to_ignore - (SI_Long)1L;
	depth_seen = (SI_Long)0L;
	child_freedom_qm = Nil;
	child_depth = (SI_Long)0L;
	kid = Nil;
	ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	kid = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result = graph_node_freedom_to_shift_up_qm(kid,FIX(MAX(depth_seen,
		kid_levels_to_ignore)));
	MVS_2(result,child_freedom_qm,temp);
	child_depth = IFIX(temp);
	if (child_depth > depth_seen)
	    depth_seen = child_depth;
	if (child_freedom_qm && ( !TRUEP(freedom_qm) || 
		FIXNUM_LT(child_freedom_qm,freedom_qm)))
	    freedom_qm = child_freedom_qm;
	goto next_loop;
      end_loop:
	return VALUES_2(freedom_qm,FIX(depth_seen + (SI_Long)1L));
	return VALUES_1(Qnil);
    }
    else {
	node_to_left_qm = ISVREF(graph_node,(SI_Long)7L);
	graph_display = ISVREF(graph_node,(SI_Long)1L);
	if (node_to_left_qm) {
	    short_representation_to_left = ISVREF(node_to_left_qm,(SI_Long)3L);
	    gensymed_symbol = IFIX(ISVREF(graph_node,(SI_Long)13L));
	    gensymed_symbol_1 = IFIX(ISVREF(node_to_left_qm,(SI_Long)13L));
	    gensymed_symbol_2 = ISVREF(short_representation_to_left,
		    (SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_2 = ISVREF(short_representation_to_left,
		    (SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_3;
	    gensymed_symbol_3 = IFIX(ISVREF(ISVREF(graph_node,(SI_Long)1L),
		    (SI_Long)5L));
	    gensymed_symbol_4 = EQ(ISVREF(graph_node,(SI_Long)4L),
		    ISVREF(node_to_left_qm,(SI_Long)4L)) ? (SI_Long)0L : 
		    IFIX(ISVREF(graph_display,(SI_Long)11L));
	    freedom = gensymed_symbol - gensymed_symbol_1 - 
		    gensymed_symbol_3 - gensymed_symbol_4;
	    depth_seen = (SI_Long)0L;
	    child_freedom_qm = Nil;
	    child_depth = (SI_Long)0L;
	    kid = Nil;
	    ab_loop_list_ = ISVREF(graph_node,(SI_Long)5L);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    kid = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    result = graph_node_freedom_to_shift_up_qm(kid,FIX(depth_seen));
	    MVS_2(result,child_freedom_qm,temp);
	    child_depth = IFIX(temp);
	    if (child_depth > depth_seen)
		depth_seen = child_depth;
	    if (child_freedom_qm && IFIX(child_freedom_qm) < freedom)
		freedom = IFIX(child_freedom_qm);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_2(FIX(freedom),FIX(depth_seen + (SI_Long)1L));
	    return VALUES_1(Qnil);
	}
	else {
	    temp = FIXNUM_ADD1(ISVREF(graph_node,(SI_Long)6L));
	    return VALUES_2(Nil,temp);
	}
    }
}

/* POSITION-NODE-HORIZONTALLY */
Object position_node_horizontally(graph_node)
    Object graph_node;
{
    Object graph, short_rep, depth, superior_node_qm, temp, gensymed_symbol;
    Object gensymed_symbol_1, x_position, kids, first_kid, kid, ab_loop_list_;
    Object top_edge, last_kid, block, svref_new_value_1, node_to_left_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long bottom_edge, svref_new_value;

    x_note_fn_call(162,72);
    graph = ISVREF(graph_node,(SI_Long)1L);
    short_rep = ISVREF(graph_node,(SI_Long)3L);
    depth = ISVREF(graph_node,(SI_Long)9L);
    superior_node_qm = ISVREF(graph_node,(SI_Long)4L);
    if (superior_node_qm) {
	temp = ISVREF(superior_node_qm,(SI_Long)12L);
	gensymed_symbol = ISVREF(graph,(SI_Long)17L);
	gensymed_symbol_1 = FIXNUM_SUB1(depth);
	x_position = FIXNUM_ADD(FIXNUM_ADD(temp,
		FIXNUM_LE(ISVREF(ISVREF(graph,(SI_Long)17L),(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(ISVREF(graph,
		(SI_Long)17L),IFIX(FIXNUM_ADD(gensymed_symbol_1,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) >>  
		-  - (SI_Long)10L) + (SI_Long)2L),IFIX(gensymed_symbol_1) 
		& (SI_Long)1023L)),ISVREF(graph,(SI_Long)6L));
    }
    else
	x_position = ISVREF(graph,(SI_Long)12L);
    kids = ISVREF(graph_node,(SI_Long)5L);
    SVREF(graph_node,FIX((SI_Long)12L)) = x_position;
    if (kids) {
	first_kid = FIRST(kids);
	kid = Nil;
	ab_loop_list_ = kids;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	kid = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	position_node_horizontally(kid);
	if ( !EQ(kid,first_kid))
	    pack_graph_node_to_top(kid);
	goto next_loop;
      end_loop:;
	top_edge = ISVREF(FIRST(kids),(SI_Long)13L);
	temp = last(kids,_);
	last_kid = CAR(temp);
	gensymed_symbol_2 = IFIX(ISVREF(last_kid,(SI_Long)13L));
	block = ISVREF(last_kid,(SI_Long)3L);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	bottom_edge = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_2 = IFIX(top_edge) + (bottom_edge - IFIX(top_edge) 
		>>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 >>  -  - gensymed_symbol_4;
	svref_new_value = gensymed_symbol_2 - gensymed_symbol_3;
	ISVREF(graph_node,(SI_Long)13L) = FIX(svref_new_value);
	if (FIXNUM_LT(ISVREF(graph_node,(SI_Long)13L),ISVREF(graph,
		(SI_Long)14L))) {
	    svref_new_value_1 = ISVREF(graph_node,(SI_Long)13L);
	    SVREF(graph,FIX((SI_Long)14L)) = svref_new_value_1;
	}
	gensymed_symbol_2 = IFIX(ISVREF(graph_node,(SI_Long)13L));
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	if (FIXNUM_GT(FIX(gensymed_symbol_2 + gensymed_symbol_3),
		ISVREF(graph,(SI_Long)15L))) {
	    gensymed_symbol_2 = IFIX(ISVREF(graph_node,(SI_Long)13L));
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    svref_new_value = gensymed_symbol_2 + gensymed_symbol_3;
	    return VALUES_1(ISVREF(graph,(SI_Long)15L) = FIX(svref_new_value));
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	node_to_left_qm = ISVREF(graph_node,(SI_Long)7L);
	if (FIXNUM_EQ(ISVREF(graph,(SI_Long)14L),ISVREF(graph,(SI_Long)15L)))
	    svref_new_value_1 = ISVREF(graph,(SI_Long)14L);
	else {
	    gensymed_symbol_2 = IFIX(ISVREF(graph,(SI_Long)15L));
	    gensymed_symbol_3 = IFIX(ISVREF(graph,(SI_Long)5L));
	    gensymed_symbol_4 = node_to_left_qm &&  !EQ(ISVREF(graph_node,
		    (SI_Long)4L),ISVREF(node_to_left_qm,(SI_Long)4L)) ? 
		    IFIX(ISVREF(graph,(SI_Long)11L)) : (SI_Long)0L;
	    svref_new_value_1 = FIX(gensymed_symbol_2 + gensymed_symbol_3 
		    + gensymed_symbol_4);
	}
	SVREF(graph_node,FIX((SI_Long)13L)) = svref_new_value_1;
	gensymed_symbol_2 = IFIX(ISVREF(graph_node,(SI_Long)13L));
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	svref_new_value = gensymed_symbol_2 + gensymed_symbol_3;
	ISVREF(graph,(SI_Long)15L) = FIX(svref_new_value);
	gensymed_symbol_2 = IFIX(x_position);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	if (FIXNUM_GT(FIX(gensymed_symbol_2 + gensymed_symbol_3),
		ISVREF(graph,(SI_Long)13L))) {
	    gensymed_symbol_2 = IFIX(x_position);
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    svref_new_value = gensymed_symbol_2 + gensymed_symbol_3;
	    return VALUES_1(ISVREF(graph,(SI_Long)13L) = FIX(svref_new_value));
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Kdraw_as_soon_as_possible;  /* :draw-as-soon-as-possible */

/* DISPLAY-GRAPH-ON-WORKSPACE */
Object display_graph_on_workspace(graph)
    Object graph;
{
    Object workspace, current_drawing_priority;
    Declare_special(1);

    x_note_fn_call(162,73);
    workspace = ISVREF(graph,(SI_Long)20L);
    current_drawing_priority = Kdraw_as_late_as_possible;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	    0);
      enlarge_workspace_if_necessary(5,workspace,ISVREF(graph,
	      (SI_Long)12L),ISVREF(graph,(SI_Long)14L),ISVREF(graph,
	      (SI_Long)13L),ISVREF(graph,(SI_Long)15L));
      display_graph_node(ISVREF(graph,(SI_Long)3L),workspace);
    POP_SPECIAL();
    if (EQ(Current_drawing_priority,Kdraw_as_soon_as_possible))
	return force_process_drawing();
    else
	return VALUES_1(Nil);
}

/* UPDATE-DISPLAY-OF-GRAPH-ON-WORKSPACE */
Object update_display_of_graph_on_workspace(graph)
    Object graph;
{
    Object workspace;

    x_note_fn_call(162,74);
    workspace = ISVREF(graph,(SI_Long)20L);
    enlarge_workspace_if_necessary(5,workspace,ISVREF(graph,(SI_Long)12L),
	    ISVREF(graph,(SI_Long)14L),ISVREF(graph,(SI_Long)13L),
	    ISVREF(graph,(SI_Long)15L));
    update_display_of_graph_nodes(graph);
    return change_workspace_edges_after_including_margin(workspace,
	    ISVREF(graph,(SI_Long)12L),ISVREF(graph,(SI_Long)14L),
	    ISVREF(graph,(SI_Long)13L),ISVREF(graph,(SI_Long)15L));
}

/* DISPLAY-GRAPH-NODE */
Object display_graph_node(graph_node,workspace)
    Object graph_node, workspace;
{
    Object graph, short_rep, kids, kid, ab_loop_list_;

    x_note_fn_call(162,75);
    graph = ISVREF(graph_node,(SI_Long)1L);
    short_rep = ISVREF(graph_node,(SI_Long)3L);
    kids = ISVREF(graph_node,(SI_Long)5L);
    add_to_workspace(5,short_rep,workspace,ISVREF(graph_node,(SI_Long)12L),
	    ISVREF(graph_node,(SI_Long)13L),T);
    if (kids) {
	kid = Nil;
	ab_loop_list_ = kids;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	kid = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	display_graph_node(kid,workspace);
	goto next_loop;
      end_loop:;
	return connect_superior_and_kid_graph_display_nodes(graph,
		graph_node,ISVREF(graph,(SI_Long)1L),kids);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Graphed_block_groups_to_move, Qgraphed_block_groups_to_move);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_nodes_needing_children_connections, Qgraph_nodes_needing_children_connections);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_nodes_to_add_as_subblocks, Qgraph_nodes_to_add_as_subblocks);

/* MAKE-GRAPHED-BLOCK-GROUP */
Object make_graphed_block_group(x_movement,y_movement,initial_block)
    Object x_movement, y_movement, initial_block;
{
    Object new_group;

    x_note_fn_call(162,76);
    new_group = graph_layout_list_3(x_movement,y_movement,initial_block);
    Graphed_block_groups_to_move = graph_layout_cons_1(new_group,
	    Graphed_block_groups_to_move);
    return VALUES_1(new_group);
}

/* ADD-BLOCKS-TO-GRAPHED-BLOCK-GROUP */
Object add_blocks_to_graphed_block_group(block_group,graph_layout_block_list)
    Object block_group, graph_layout_block_list;
{
    Object cddr_new_value;

    x_note_fn_call(162,77);
    if (graph_layout_block_list) {
	cddr_new_value = nconc2(graph_layout_block_list,CDDR(block_group));
	M_CDDR(block_group) = cddr_new_value;
    }
    return VALUES_1(Nil);
}

/* UPDATE-DISPLAY-OF-GRAPH-NODES */
Object update_display_of_graph_nodes(graph)
    Object graph;
{
    Object root_node, workspace, orientation, graphed_block_groups_to_move;
    Object graph_nodes_needing_children_connections;
    Object graph_nodes_to_add_as_subblocks, block_group, ab_loop_list_;
    Object x_shift, y_shift, graph_node, short_rep;
    Declare_special(3);
    Object result;

    x_note_fn_call(162,78);
    root_node = ISVREF(graph,(SI_Long)3L);
    workspace = ISVREF(graph,(SI_Long)20L);
    orientation = ISVREF(graph,(SI_Long)1L);
    graphed_block_groups_to_move = Nil;
    graph_nodes_needing_children_connections = Nil;
    graph_nodes_to_add_as_subblocks = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Graph_nodes_to_add_as_subblocks,Qgraph_nodes_to_add_as_subblocks,graph_nodes_to_add_as_subblocks,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Graph_nodes_needing_children_connections,Qgraph_nodes_needing_children_connections,graph_nodes_needing_children_connections,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Graphed_block_groups_to_move,Qgraphed_block_groups_to_move,graphed_block_groups_to_move,
		0);
	  schedule_or_reposition_graph_node(root_node,
		  make_graphed_block_group(FIX((SI_Long)0L),
		  FIX((SI_Long)0L),ISVREF(root_node,(SI_Long)3L)));
	  delete_short_representation_frames_of_graph_node_tree(ISVREF(graph,
		  (SI_Long)18L));
	  block_group = Nil;
	  ab_loop_list_ = Graphed_block_groups_to_move;
	  x_shift = Nil;
	  y_shift = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  block_group = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  x_shift = CAR(block_group);
	  y_shift = CADR(block_group);
	  if (IFIX(x_shift) != (SI_Long)0L || IFIX(y_shift) != (SI_Long)0L) {
	      Graph_display_changed_during_update_qm = T;
	      move_blocks_with_their_external_connections(CDDR(block_group),
		      workspace,x_shift,y_shift);
	  }
	  reclaim_graph_layout_list_1(block_group);
	  goto next_loop;
	end_loop:;
	  reclaim_graph_layout_list_1(Graphed_block_groups_to_move);
	  graph_node = Nil;
	  ab_loop_list_ = Graph_nodes_to_add_as_subblocks;
	  short_rep = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  graph_node = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  short_rep = ISVREF(graph_node,(SI_Long)3L);
	  Graph_display_changed_during_update_qm = T;
	  add_to_workspace(5,short_rep,workspace,ISVREF(graph_node,
		  (SI_Long)12L),ISVREF(graph_node,(SI_Long)13L),T);
	  goto next_loop_1;
	end_loop_1:;
	  reclaim_graph_layout_list_1(Graph_nodes_to_add_as_subblocks);
	  graph_node = Nil;
	  ab_loop_list_ = Graph_nodes_needing_children_connections;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  graph_node = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  Graph_display_changed_during_update_qm = T;
	  connect_superior_and_kid_graph_display_nodes(graph,graph_node,
		  orientation,ISVREF(graph_node,(SI_Long)5L));
	  goto next_loop_2;
	end_loop_2:;
	  reclaim_graph_layout_list_1(Graph_nodes_needing_children_connections);
	  result = VALUES_1(Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* SCHEDULE-OR-REPOSITION-GRAPH-NODE */
Object schedule_or_reposition_graph_node(graph_node,
	    block_group_already_containing_this_node_qm)
    Object graph_node, block_group_already_containing_this_node_qm;
{
    Object short_rep, kids, original_node_qm, temp, kid, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_1;

    x_note_fn_call(162,79);
    short_rep = ISVREF(graph_node,(SI_Long)3L);
    kids = ISVREF(graph_node,(SI_Long)5L);
    original_node_qm = ISVREF(graph_node,(SI_Long)15L);
    if (original_node_qm) {
	if ( !TRUEP(block_group_already_containing_this_node_qm))
	    block_group_already_containing_this_node_qm = 
		    make_graphed_block_group(FIXNUM_MINUS(ISVREF(graph_node,
		    (SI_Long)12L),ISVREF(original_node_qm,(SI_Long)12L)),
		    FIXNUM_MINUS(ISVREF(graph_node,(SI_Long)13L),
		    ISVREF(original_node_qm,(SI_Long)13L)),short_rep);
	if (graph_node_children_can_be_included_in_block_group_p(graph_node,
		block_group_already_containing_this_node_qm)) {
	    temp = block_group_already_containing_this_node_qm;
	    add_blocks_to_graphed_block_group(temp,
		    graph_layout_list_of_children_junctions(short_rep));
	    temp = block_group_already_containing_this_node_qm;
	    kid = Nil;
	    ab_loop_list_ = kids;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    kid = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = graph_layout_cons_1(ISVREF(kid,(SI_Long)3L),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    temp_1 = ab_loopvar_;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	    add_blocks_to_graphed_block_group(temp,temp_1);
	    kid = Nil;
	    ab_loop_list_ = kids;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    kid = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    schedule_or_reposition_graph_node(kid,
		    block_group_already_containing_this_node_qm);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else {
	    remove_connections_to_sub_nodes(ISVREF(graph_node,(SI_Long)3L));
	    if (kids) {
		Graph_nodes_needing_children_connections = 
			graph_layout_cons_1(graph_node,
			Graph_nodes_needing_children_connections);
		kid = Nil;
		ab_loop_list_ = kids;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		kid = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		schedule_or_reposition_graph_node(kid,Nil);
		goto next_loop_2;
	      end_loop_2:
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else {
	Graph_nodes_to_add_as_subblocks = graph_layout_cons_1(graph_node,
		Graph_nodes_to_add_as_subblocks);
	if (kids) {
	    Graph_nodes_needing_children_connections = 
		    graph_layout_cons_1(graph_node,
		    Graph_nodes_needing_children_connections);
	    kid = Nil;
	    ab_loop_list_ = kids;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    kid = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    schedule_or_reposition_graph_node(kid,Nil);
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* GRAPH-NODE-CHILDREN-CAN-BE-INCLUDED-IN-BLOCK-GROUP-P */
Object graph_node_children_can_be_included_in_block_group_p(graph_node,
	    block_group)
    Object graph_node, block_group;
{
    Object original_node, kids, kid_cons, old_kid_cons, kid, kid_original;
    SI_Long x_shift, y_shift;

    x_note_fn_call(162,80);
    original_node = ISVREF(graph_node,(SI_Long)15L);
    kids = ISVREF(graph_node,(SI_Long)5L);
    x_shift = IFIX(CAR(block_group));
    y_shift = IFIX(CADR(block_group));
    if (original_node && kids) {
	kid_cons = kids;
	old_kid_cons = ISVREF(original_node,(SI_Long)5L);
	kid = Nil;
	kid_original = Nil;
      next_loop:
	if ( !(kid_cons && old_kid_cons))
	    goto end_loop;
	kid = CAR(kid_cons);
	kid_original = ISVREF(kid,(SI_Long)15L);
	if ( !EQ(kid_original,CAR(old_kid_cons)) || 
		IFIX(FIXNUM_MINUS(ISVREF(kid,(SI_Long)12L),
		ISVREF(kid_original,(SI_Long)12L))) != x_shift || 
		IFIX(FIXNUM_MINUS(ISVREF(kid,(SI_Long)13L),
		ISVREF(kid_original,(SI_Long)13L))) != y_shift)
	    return VALUES_1(Nil);
	kid_cons = CDR(kid_cons);
	old_kid_cons = CDR(old_kid_cons);
	goto next_loop;
      end_loop:
	if ( !TRUEP(kid_cons))
	    return VALUES_1( !TRUEP(old_kid_cons) ? T : Nil);
	else
	    return VALUES_1(Nil);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsub_nodes;          /* sub-nodes */

/* GRAPH-LAYOUT-LIST-OF-CHILDREN-JUNCTIONS */
Object graph_layout_list_of_children_junctions(block)
    Object block;
{
    Object junctions, search_origins, scope_conses, ab_node_stack_;
    Object ab_current_node_, gensymed_symbol, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object ab_port_name_, other_end, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, ab_less_than_branch_qm_, sub_class_bit_vector, new_junctions;
    Object ab_loop_iter_flag_, temp_2, svref_arg_2, junction, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(162,81);
    junctions = Nil;
    search_origins = graph_layout_cons_1(block,Nil);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(CAR(search_origins),(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    ab_port_name_ = Qsub_nodes;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      other_end = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
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
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && memq_function(ab_port_name_,
	      connection_item_name_or_names(ab_connection_item_)))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      other_end = get_block_at_other_end_of_connection(connection,
	      CAR(search_origins));
      sub_class_bit_vector = ISVREF(ISVREF(other_end,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(Default_junction_class_description,(SI_Long)18L));
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
      if (temp_1) {
	  ab_loopvar__2 = eval_cons_1(other_end,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop_2:
      new_junctions = ab_loopvar_;
      goto end_2;
      new_junctions = Qnil;
    end_2:;
    POP_SPECIAL();
    ab_loop_iter_flag_ = T;
  next_loop_3:
    if ( !TRUEP(search_origins))
	goto end_loop_3;
    if ( !TRUEP(ab_loop_iter_flag_)) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(CAR(search_origins),
		(SI_Long)14L));
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
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
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
	next_loop_4:
	next_loop_5:
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
		next_loop_6:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_4;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_6;
		end_loop_4:;
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
	      goto end_3;
	  goto next_loop_5;
	end_loop_5:
	end_3:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_6;
	  connection = ab_connection_;
	  other_end = get_block_at_other_end_of_connection(connection,
		  CAR(search_origins));
	  sub_class_bit_vector = ISVREF(ISVREF(other_end,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Default_junction_class_description,
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
	      temp_1 = (SI_Long)0L < gensymed_symbol_1;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      ab_loopvar__2 = eval_cons_1(other_end,Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	  }
	  goto next_loop_4;
	end_loop_6:
	  new_junctions = ab_loopvar_;
	  goto end_4;
	  new_junctions = Qnil;
	end_4:;
	POP_SPECIAL();
    }
    temp = CDR(search_origins);
    inline_note_reclaim_cons(search_origins,Qgraph_layout);
    if (ISVREF(Available_graph_layout_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp_2 = ISVREF(Available_graph_layout_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp_2) = search_origins;
	temp_2 = Available_graph_layout_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_2,svref_arg_2) = search_origins;
    }
    else {
	temp_2 = Available_graph_layout_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_2,svref_arg_2) = search_origins;
	temp_2 = Available_graph_layout_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_2,svref_arg_2) = search_origins;
    }
    M_CDR(search_origins) = Nil;
    search_origins = temp;
    junction = Nil;
    ab_loop_list_ = new_junctions;
  next_loop_7:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_7;
    junction = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(junction,junctions))) {
	junctions = graph_layout_cons_1(junction,junctions);
	search_origins = graph_layout_cons_1(junction,search_origins);
    }
    goto next_loop_7;
  end_loop_7:;
    reclaim_eval_list_1(new_junctions);
    ab_loop_iter_flag_ = Nil;
    goto next_loop_3;
  end_loop_3:
    return VALUES_1(junctions);
    return VALUES_1(Qnil);
}

/* GRAPH-LAYOUT-LIST-OF-CONNECTED-CHILD-SHORT-REPRESENTATIONS */
Object graph_layout_list_of_connected_child_short_representations(block)
    Object block;
{
    Object blocks, search_origins, new_blocks, ab_loop_iter_flag_, temp;
    Object new_block, ab_loop_list_, sub_class_bit_vector, candidate;
    Object result_blocks, ab_loopvar_, ab_loopvar__1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(162,82);
    blocks = graph_layout_cons_1(block,Nil);
    search_origins = graph_layout_cons_1(block,Nil);
    new_blocks = eval_list_of_connected_blocks(CAR(search_origins),
	    Qsub_nodes,Nil);
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(search_origins))
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	new_blocks = eval_list_of_connected_blocks(CAR(search_origins),
		Qsub_nodes,Nil);
    temp = CDR(search_origins);
    reclaim_graph_layout_cons_1(search_origins);
    search_origins = temp;
    new_block = Nil;
    ab_loop_list_ = new_blocks;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    new_block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(new_block,blocks))) {
	blocks = graph_layout_cons_1(new_block,blocks);
	sub_class_bit_vector = ISVREF(ISVREF(new_block,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Default_junction_class_description,(SI_Long)18L));
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
	if (temp_1)
	    search_origins = graph_layout_cons_1(new_block,search_origins);
    }
    goto next_loop_1;
  end_loop_1:;
    reclaim_eval_list_1(new_blocks);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    candidate = Nil;
    ab_loop_list_ = blocks;
    result_blocks = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    candidate = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = EQ(block,candidate);
    if (temp_1);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(candidate,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Default_junction_class_description,(SI_Long)18L));
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
    }
    if (temp_1);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(candidate,(SI_Long)1L),
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
    }
    if (temp_1);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(candidate,(SI_Long)1L),
		(SI_Long)19L);
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    if ( !temp_1) {
	ab_loopvar__1 = graph_layout_cons_1(candidate,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_blocks = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop_2;
  end_loop_2:
    reclaim_graph_layout_list_1(blocks);
    return VALUES_1(result_blocks);
    return VALUES_1(Qnil);
}

/* REMOVE-CONNECTIONS-TO-SUB-NODES */
Object remove_connections_to_sub_nodes(short_rep)
    Object short_rep;
{
    Object junction_blocks, connected_children, sub_nodes_connection_1;
    Object junction, ab_loop_list_, child, connection;

    x_note_fn_call(162,83);
    junction_blocks = graph_layout_list_of_children_junctions(short_rep);
    connected_children = 
	    graph_layout_list_of_connected_child_short_representations(short_rep);
    sub_nodes_connection_1 = Nil;
    junction = Nil;
    ab_loop_list_ = junction_blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    junction = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    Graph_display_changed_during_update_qm = T;
    delete_frame(junction);
    goto next_loop;
  end_loop:;
    reclaim_graph_layout_list_1(junction_blocks);
    sub_nodes_connection_1 = sub_nodes_connection(1,short_rep);
    if (sub_nodes_connection_1) {
	Graph_display_changed_during_update_qm = T;
	delete_connection(1,sub_nodes_connection_1);
    }
    child = Nil;
    ab_loop_list_ = connected_children;
    connection = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    connection = superior_node_connection(child);
    if (connection) {
	Graph_display_changed_during_update_qm = T;
	delete_connection(1,connection);
    }
    goto next_loop_1;
  end_loop_1:;
    return reclaim_graph_layout_list_1(connected_children);
}

/* DELETE-SHORT-REPRESENTATION-FRAMES-OF-GRAPH-NODE-TREE */
Object delete_short_representation_frames_of_graph_node_tree(graph_node)
    Object graph_node;
{
    Object short_rep_qm, kids, kid, ab_loop_list_;

    x_note_fn_call(162,84);
    short_rep_qm = ISVREF(graph_node,(SI_Long)3L);
    kids = ISVREF(graph_node,(SI_Long)5L);
    if (short_rep_qm) {
	remove_connections_to_sub_nodes(short_rep_qm);
	delete_frame(short_rep_qm);
    }
    kid = Nil;
    ab_loop_list_ = kids;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_short_representation_frames_of_graph_node_tree(kid);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qinverted;           /* inverted */

static Object Qinverted_sub_nodes;  /* inverted-sub-nodes */

static Object Qbottom;             /* bottom */

static Object Qhorizontal;         /* horizontal */

static Object Qright;              /* right */

static Object Qbackwards;          /* backwards */

static Object Qconnection;         /* connection */

/* ADD-PARENT-STUB-TO-GRAPH-DISPLAY-BLOCK */
Object add_parent_stub_to_graph_display_block(block,orientation,workspace)
    Object block, orientation, workspace;
{
    Object temp, temp_1, gensymed_symbol, new_connection;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(162,85);
    if ( !TRUEP(sub_nodes_connection(1,block))) {
	temp = EQ(orientation,Qinverted) ? Qinverted_sub_nodes : Qsub_nodes;
	if (EQ(orientation,Qvertical))
	    temp_1 = Qbottom;
	else if (EQ(orientation,Qhorizontal))
	    temp_1 = Qright;
	else if (EQ(orientation,Qinverted))
	    temp_1 = Qtop;
	else if (EQ(orientation,Qbackwards))
	    temp_1 = Qleft;
	else
	    temp_1 = Qnil;
	if (EQ(orientation,Qvertical) || EQ(orientation,Qinverted)) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	}
	else if (EQ(orientation,Qhorizontal) || EQ(orientation,Qbackwards)) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	}
	else
	    gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = (SI_Long)1L;
	new_connection = add_stub(6,block,temp,Qconnection,Nil,temp_1,
		FIX(gensymed_symbol_1 >>  -  - gensymed_symbol_2));
	update_connection_images(Nil,workspace,new_connection);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsuperior_node;      /* superior-node */

/* ADD-SUPERIOR-NODE-STUB-TO-GRAPH-DISPLAY-BLOCK */
Object add_superior_node_stub_to_graph_display_block(block,orientation,
	    workspace)
    Object block, orientation, workspace;
{
    Object temp, gensymed_symbol, new_connection;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(162,86);
    if ( !TRUEP(superior_node_connection(block))) {
	if (EQ(orientation,Qvertical))
	    temp = Qtop;
	else if (EQ(orientation,Qhorizontal))
	    temp = Qleft;
	else if (EQ(orientation,Qinverted))
	    temp = Qbottom;
	else if (EQ(orientation,Qbackwards))
	    temp = Qright;
	else
	    temp = Qnil;
	if (EQ(orientation,Qvertical) || EQ(orientation,Qinverted)) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	}
	else if (EQ(orientation,Qhorizontal) || EQ(orientation,Qbackwards)) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	}
	else
	    gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = (SI_Long)1L;
	new_connection = add_stub(6,block,Qsuperior_node,Qconnection,Nil,
		temp,FIX(gensymed_symbol_1 >>  -  - gensymed_symbol_2));
	update_connection_images(Nil,workspace,new_connection);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CONNECT-SUPERIOR-AND-KID-GRAPH-DISPLAY-NODES */
Object connect_superior_and_kid_graph_display_nodes(graph,graph_node,
	    orientation,kids)
    Object graph, graph_node, orientation, kids;
{
    Object kid, ab_loop_list_, kid_frames, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(162,87);
    kid = Nil;
    ab_loop_list_ = kids;
    kid_frames = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = graph_layout_cons_1(ISVREF(kid,(SI_Long)3L),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	kid_frames = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    connect_superior_and_kid_frames(ISVREF(graph_node,(SI_Long)3L),
	    orientation,kid_frames,ISVREF(graph,(SI_Long)20L),ISVREF(graph,
	    (SI_Long)6L),ISVREF(graph,(SI_Long)5L));
    reclaim_graph_layout_list_1(kid_frames);
    return VALUES_1(Qnil);
}

/* CONNECT-SUPERIOR-AND-KID-FRAMES */
Object connect_superior_and_kid_frames(parent_frame,orientation,kid_frames,
	    workspace,horizontal_spacing,vertical_spacing)
    Object parent_frame, orientation, kid_frames, workspace;
    Object horizontal_spacing, vertical_spacing;
{
    Object short_rep, kid, ab_loop_list_, parent_connection, parent_loose_end;
    Object kid_short_rep, kid_loose_end, first_short_rep, first_loose_end;
    Object temp, last_short_rep, last_connection, last_loose_end;
    Object gensymed_symbol, junction_x, junction_y, junction, temp_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long first_connection_limit, last_connection_limit, kid_x, kid_y;
    SI_Long temp_2;

    x_note_fn_call(162,88);
    short_rep = parent_frame;
    add_parent_stub_to_graph_display_block(short_rep,orientation,workspace);
    kid = Nil;
    ab_loop_list_ = kid_frames;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kid = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_superior_node_stub_to_graph_display_block(kid,orientation,workspace);
    goto next_loop;
  end_loop:;
    parent_connection = sub_nodes_connection(2,short_rep,orientation);
    parent_loose_end = 
	    get_block_at_other_end_of_connection(parent_connection,short_rep);
    if ( !TRUEP(CDR(kid_frames))) {
	kid_short_rep = CAR(kid_frames);
	kid_loose_end = 
		get_block_at_other_end_of_connection(superior_node_connection(kid_short_rep),
		kid_short_rep);
	return join_two_connections(parent_loose_end,kid_loose_end);
    }
    else {
	first_short_rep = CAR(kid_frames);
	first_loose_end = 
		get_block_at_other_end_of_connection(superior_node_connection(first_short_rep),
		first_short_rep);
	temp = last(kid_frames,_);
	last_short_rep = CAR(temp);
	last_connection = superior_node_connection(last_short_rep);
	last_loose_end = 
		get_block_at_other_end_of_connection(last_connection,
		last_short_rep);
	if (EQ(orientation,Qvertical) || EQ(orientation,Qinverted)) {
	    gensymed_symbol = ISVREF(parent_loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    junction_x = gensymed_symbol;
	}
	else if (EQ(orientation,Qhorizontal)) {
	    gensymed_symbol = ISVREF(first_short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(horizontal_spacing) >>  -  - (SI_Long)1L;
	    junction_x = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else if (EQ(orientation,Qbackwards)) {
	    gensymed_symbol = ISVREF(first_short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(horizontal_spacing) >>  -  - (SI_Long)1L;
	    junction_x = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	else
	    junction_x = Qnil;
	if (EQ(orientation,Qvertical)) {
	    gensymed_symbol = ISVREF(first_short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(vertical_spacing) >>  -  - (SI_Long)1L;
	    junction_y = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else if (EQ(orientation,Qhorizontal) || EQ(orientation,Qbackwards)) {
	    gensymed_symbol = ISVREF(parent_loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    junction_y = gensymed_symbol;
	}
	else if (EQ(orientation,Qinverted)) {
	    gensymed_symbol = ISVREF(first_short_rep,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(vertical_spacing) >>  -  - (SI_Long)1L;
	    junction_y = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	else
	    junction_y = Qnil;
	junction = Nil;
	update_connection_images(T,workspace,parent_connection);
	toggle_side_for_loose_end(parent_loose_end,parent_connection);
	if (EQ(orientation,Qvertical) || EQ(orientation,Qinverted)) {
	    gensymed_symbol = ISVREF(first_loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	}
	else if (EQ(orientation,Qhorizontal) || EQ(orientation,Qbackwards))
	    temp = junction_x;
	else
	    temp = Qnil;
	if (EQ(orientation,Qvertical) || EQ(orientation,Qinverted))
	    temp_1 = junction_y;
	else if (EQ(orientation,Qhorizontal) || EQ(orientation,Qbackwards)) {
	    gensymed_symbol = ISVREF(first_loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_1 = gensymed_symbol;
	}
	else
	    temp_1 = Qnil;
	move_block_to_position(parent_loose_end,temp,temp_1);
	add_bend_to_connection(parent_connection,parent_loose_end);
	gensymed_symbol = ISVREF(first_loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp = gensymed_symbol;
	gensymed_symbol = ISVREF(first_loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	move_block_to_position(parent_loose_end,temp,gensymed_symbol);
	update_connection_images(Nil,workspace,parent_connection);
	join_two_connections(parent_loose_end,first_loose_end);
	update_connection_images(T,workspace,
		get_connection_for_loose_end(last_loose_end));
	toggle_side_for_loose_end(last_loose_end,
		get_connection_for_loose_end(last_loose_end));
	move_block_to_position(last_loose_end,junction_x,junction_y);
	update_connection_images(Nil,workspace,
		get_connection_for_loose_end(last_loose_end));
	make_junction(parent_connection,last_loose_end);
	parent_connection = sub_nodes_connection(2,short_rep,orientation);
	junction = get_block_at_other_end_of_connection(parent_connection,
		short_rep);
	if (EQ(orientation,Qvertical) || EQ(orientation,Qinverted)) {
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    first_connection_limit = gensymed_symbol_1 - gensymed_symbol_2;
	}
	else if (EQ(orientation,Qhorizontal) || EQ(orientation,Qbackwards)) {
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    first_connection_limit = gensymed_symbol_1 - gensymed_symbol_2;
	}
	else
	    first_connection_limit = (SI_Long)0L;
	if (EQ(orientation,Qvertical) || EQ(orientation,Qinverted)) {
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    last_connection_limit = gensymed_symbol_1 + gensymed_symbol_2;
	}
	else if (EQ(orientation,Qhorizontal) || EQ(orientation,Qbackwards)) {
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    last_connection_limit = gensymed_symbol_1 + gensymed_symbol_2;
	}
	else
	    last_connection_limit = (SI_Long)0L;
	kid_short_rep = Nil;
	ab_loop_list_ = CDR(kid_frames);
	kid_loose_end = Nil;
	kid_x = (SI_Long)0L;
	kid_y = (SI_Long)0L;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	kid_short_rep = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(kid_short_rep,last_short_rep))
	    goto end_loop_1;
	temp = superior_node_connection(kid_short_rep);
	kid_loose_end = get_block_at_other_end_of_connection(temp,
		kid_short_rep);
	gensymed_symbol = ISVREF(kid_loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	kid_x = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(kid_loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	kid_y = IFIX(gensymed_symbol);
	update_connection_images(T,workspace,
		superior_node_connection(kid_short_rep));
	temp = kid_loose_end;
	toggle_side_for_loose_end(temp,
		superior_node_connection(kid_short_rep));
	if (kid_x < first_connection_limit && (EQ(orientation,Qvertical) 
		|| EQ(orientation,Qinverted))) {
	    move_block_to_position(kid_loose_end,FIX(kid_x),junction_y);
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    temp = get_left_connection_of_junction(junction,parent_connection);
	    make_junction(temp,kid_loose_end);
	}
	else if (kid_y < first_connection_limit &&  !(EQ(orientation,
		Qvertical) || EQ(orientation,Qinverted))) {
	    move_block_to_position(kid_loose_end,junction_x,FIX(kid_y));
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    temp = get_top_connection_of_junction(junction,parent_connection);
	    make_junction(temp,kid_loose_end);
	}
	else if ((EQ(orientation,Qvertical) || EQ(orientation,Qinverted)) 
		&& kid_x > last_connection_limit) {
	    move_block_to_position(kid_loose_end,FIX(kid_x),junction_y);
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    temp = superior_node_connection(last_short_rep);
	    make_junction(temp,kid_loose_end);
	}
	else if ( !(EQ(orientation,Qvertical) || EQ(orientation,
		Qinverted)) && kid_y > last_connection_limit) {
	    move_block_to_position(kid_loose_end,junction_x,FIX(kid_y));
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    temp = superior_node_connection(last_short_rep);
	    make_junction(temp,kid_loose_end);
	}
	else if (EQ(orientation,Qvertical)) {
	    temp_2 = kid_x;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    if (temp_2 <= IFIX(gensymed_symbol)) {
		temp = kid_loose_end;
		temp_1 = FIX(kid_x + (SI_Long)40L);
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = (SI_Long)2L;
		move_block_to_position(temp,temp_1,FIX(gensymed_symbol_1 + 
			gensymed_symbol_2));
		temp = superior_node_connection(kid_short_rep);
		add_bend_to_connection(temp,kid_loose_end);
	    }
	    else {
		temp_2 = kid_x;
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		if (temp_2 >= IFIX(gensymed_symbol)) {
		    temp = kid_loose_end;
		    temp_1 = FIX(kid_x - (SI_Long)40L);
		    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = (SI_Long)2L;
		    move_block_to_position(temp,temp_1,
			    FIX(gensymed_symbol_1 + gensymed_symbol_2));
		    temp = superior_node_connection(kid_short_rep);
		    add_bend_to_connection(temp,kid_loose_end);
		}
	    }
	    temp = kid_loose_end;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	    temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = (SI_Long)2L;
	    move_block_to_position(temp,temp_1,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    add_new_connection_to_block(3,kid_loose_end,junction,T);
	}
	else if (EQ(orientation,Qinverted)) {
	    temp_2 = kid_x;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    if (temp_2 <= IFIX(gensymed_symbol)) {
		temp = kid_loose_end;
		temp_1 = FIX(kid_x + (SI_Long)40L);
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = (SI_Long)2L;
		move_block_to_position(temp,temp_1,FIX(gensymed_symbol_1 - 
			gensymed_symbol_2));
		temp = superior_node_connection(kid_short_rep);
		add_bend_to_connection(temp,kid_loose_end);
	    }
	    else {
		temp_2 = kid_x;
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		if (temp_2 >= IFIX(gensymed_symbol)) {
		    temp = kid_loose_end;
		    temp_1 = FIX(kid_x - (SI_Long)40L);
		    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = (SI_Long)2L;
		    move_block_to_position(temp,temp_1,
			    FIX(gensymed_symbol_1 - gensymed_symbol_2));
		    temp = superior_node_connection(kid_short_rep);
		    add_bend_to_connection(temp,kid_loose_end);
		}
	    }
	    temp = kid_loose_end;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	    temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = (SI_Long)2L;
	    move_block_to_position(temp,temp_1,FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2));
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    add_new_connection_to_block(3,kid_loose_end,junction,T);
	}
	else if (EQ(orientation,Qhorizontal)) {
	    temp_2 = kid_y;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    if (temp_2 <= IFIX(gensymed_symbol)) {
		temp = kid_loose_end;
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = (SI_Long)2L;
		move_block_to_position(temp,FIX(gensymed_symbol_1 + 
			gensymed_symbol_2),FIX(kid_y + (SI_Long)40L));
		temp = superior_node_connection(kid_short_rep);
		add_bend_to_connection(temp,kid_loose_end);
	    }
	    else {
		temp_2 = kid_y;
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		if (temp_2 >= IFIX(gensymed_symbol)) {
		    temp = kid_loose_end;
		    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = (SI_Long)2L;
		    move_block_to_position(temp,FIX(gensymed_symbol_1 + 
			    gensymed_symbol_2),FIX(kid_y - (SI_Long)40L));
		    temp = superior_node_connection(kid_short_rep);
		    add_bend_to_connection(temp,kid_loose_end);
		}
	    }
	    temp = kid_loose_end;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = (SI_Long)2L;
	    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	    move_block_to_position(temp,temp_1,FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2));
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    add_new_connection_to_block(3,kid_loose_end,junction,T);
	}
	else if (EQ(orientation,Qbackwards)) {
	    temp_2 = kid_y;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    if (temp_2 <= IFIX(gensymed_symbol)) {
		temp = kid_loose_end;
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = (SI_Long)2L;
		move_block_to_position(temp,FIX(gensymed_symbol_1 - 
			gensymed_symbol_2),FIX(kid_y + (SI_Long)40L));
		temp = superior_node_connection(kid_short_rep);
		add_bend_to_connection(temp,kid_loose_end);
	    }
	    else {
		temp_2 = kid_y;
		gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		if (temp_2 >= IFIX(gensymed_symbol)) {
		    temp = kid_loose_end;
		    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = (SI_Long)2L;
		    move_block_to_position(temp,FIX(gensymed_symbol_1 - 
			    gensymed_symbol_2),FIX(kid_y - (SI_Long)40L));
		    temp = superior_node_connection(kid_short_rep);
		    add_bend_to_connection(temp,kid_loose_end);
		}
	    }
	    temp = kid_loose_end;
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = (SI_Long)2L;
	    temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	    move_block_to_position(temp,temp_1,FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2));
	    update_connection_images(Nil,workspace,
		    superior_node_connection(kid_short_rep));
	    add_new_connection_to_block(3,kid_loose_end,junction,T);
	}
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* MOVE-BLOCK-TO-POSITION */
Object move_block_to_position(block,x_position,y_position)
    Object block, x_position, y_position;
{
    Object gensymed_symbol, old_x, old_y, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(162,89);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    old_x = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    old_y = gensymed_symbol;
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
    gensymed_symbol_1 = block;
    gensymed_symbol_2 = FIXNUM_MINUS(x_position,old_x);
    gensymed_symbol_3 = FIXNUM_MINUS(y_position,old_y);
    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3);
}

/* EVAL-LIST-OF-CONNECTED-BLOCKS */
Object eval_list_of_connected_blocks(block,port_name_qm,class_qm)
    Object block, port_name_qm, class_qm;
{
    Object result_1, scope_conses, ab_node_stack_, ab_current_node_;
    Object gensymed_symbol, ab_skip_list_form_, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_port_name_, other_end, temp;
    Object ab_less_than_branch_qm_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(162,90);
    result_1 = Nil;
    if (port_name_qm) {
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
	ab_port_name_ = port_name_qm;
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
	next_loop:
	next_loop_1:
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
		next_loop_2:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_2;
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
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		  ab_connection_ && memq_function(ab_port_name_,
		  connection_item_name_or_names(ab_connection_item_)))
	      goto end_1;
	  goto next_loop_1;
	end_loop_1:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_2;
	  connection = ab_connection_;
	  other_end = get_block_at_other_end_of_connection(connection,block);
	  temp_1 =  !TRUEP(class_qm);
	  if (temp_1);
	  else {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(class_qm,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(other_end,
			  (SI_Long)1L),(SI_Long)19L);
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp_1 = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  if (temp_1)
	      result_1 = eval_cons_1(other_end,result_1);
	  goto next_loop;
	end_loop_2:;
	POP_SPECIAL();
    }
    else {
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
	next_loop_3:
	next_loop_4:
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
		next_loop_5:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_3;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_5;
		end_loop_3:;
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
	      goto end_2;
	  goto next_loop_4;
	end_loop_4:
	end_2:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_5;
	  connection = ab_connection_;
	  other_end = get_block_at_other_end_of_connection(connection,block);
	  temp_1 =  !TRUEP(class_qm);
	  if (temp_1);
	  else {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(class_qm,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(other_end,
			  (SI_Long)1L),(SI_Long)19L);
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp_1 = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  if (temp_1)
	      result_1 = eval_cons_1(other_end,result_1);
	  goto next_loop_3;
	end_loop_5:;
	POP_SPECIAL();
    }
    return VALUES_1(result_1);
}

/* SUPERIOR-NODE-CONNECTION */
Object superior_node_connection(display_node_entity)
    Object display_node_entity;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_port_name_, temp;
    Object ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,91);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(display_node_entity,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    ab_port_name_ = Qsuperior_node;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
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
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && memq_function(ab_port_name_,
	      connection_item_name_or_names(ab_connection_item_)))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      result = VALUES_1(connection);
      goto end_2;
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* SUB-NODES-CONNECTION */
Object sub_nodes_connection varargs_1(int, n)
{
    Object display_node_entity;
    Object orientation, scope_conses, ab_node_stack_, ab_current_node_;
    Object gensymed_symbol, ab_skip_list_form_, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_port_name_, temp;
    Object ab_less_than_branch_qm_;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,92);
    INIT_ARGS_nonrelocating();
    display_node_entity = REQUIRED_ARG_nonrelocating();
    orientation = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(display_node_entity,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    ab_port_name_ = EQ(orientation,Qinverted) ? Qinverted_sub_nodes : 
	    Qsub_nodes;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
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
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && memq_function(ab_port_name_,
	      connection_item_name_or_names(ab_connection_item_)))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      result = VALUES_1(connection);
      goto end_2;
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* GET-LEFT-CONNECTION-OF-JUNCTION */
Object get_left_connection_of_junction(junction,parent_connection)
    Object junction, parent_connection;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,93);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(junction,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
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
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      if ( !EQ(connection,parent_connection)) {
	  gensymed_symbol = 
		  ISVREF(get_block_at_other_end_of_connection(connection,
		  junction),(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  temp = gensymed_symbol;
	  gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  temp_1 = FIXNUM_LT(temp,gensymed_symbol);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  result = VALUES_1(connection);
	  goto end_2;
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* GET-TOP-CONNECTION-OF-JUNCTION */
Object get_top_connection_of_junction(junction,parent_connection)
    Object junction, parent_connection;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,94);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(junction,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
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
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      if ( !EQ(connection,parent_connection)) {
	  gensymed_symbol = 
		  ISVREF(get_block_at_other_end_of_connection(connection,
		  junction),(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  temp = gensymed_symbol;
	  gensymed_symbol = ISVREF(junction,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  temp_1 = FIXNUM_LT(temp,gensymed_symbol);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  result = VALUES_1(connection);
	  goto end_2;
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

static Object Qframe_hash_function;  /* frame-hash-function */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qcalled_procedure_invocations_for_graph;  /* called-procedure-invocations-for-graph */

static Object Qmake_short_representation;  /* make-short-representation */

/* GRAPH-PROCEDURE-INVOCATIONS */
Object graph_procedure_invocations(procedure_invocation)
    Object procedure_invocation;
{
    Object temp, temp_1, temp_2, temp_3, temp_4;

    x_note_fn_call(162,95);
    temp = IDENTITY(Qframe_hash_function);
    if (temp);
    else
	temp = Qsxhashw;
    temp_1 = IDENTITY(Qvertical);
    if (temp_1);
    else
	temp_1 = Qvertical;
    temp_2 = IDENTITY(Nil);
    if (temp_2);
    else
	temp_2 = FIX((SI_Long)50L);
    temp_3 = IDENTITY(Nil);
    if (temp_3);
    else
	temp_3 = FIX((SI_Long)50L);
    temp_4 = IDENTITY(Nil);
    if (temp_4);
    else
	temp_4 = Qtemporary_workspace;
    return graph_frame_hierarchy_function(procedure_invocation,
	    Qcalled_procedure_invocations_for_graph,Nil,
	    Qmake_short_representation,temp,temp_1,temp_2,temp_3,Nil,
	    temp_4,Nil,Nil,Nil);
}

/* CALLED-PROCEDURE-INVOCATIONS-FOR-GRAPH */
Object called_procedure_invocations_for_graph(procedure_invocation,extra_arg)
    Object procedure_invocation, extra_arg;
{
    Object invocation, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(162,96);
    invocation = Nil;
    ab_loop_list_ = ISVREF(procedure_invocation,(SI_Long)13L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    invocation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = called_procedure_invocations_for_graph_1(invocation);
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_procedure_invocation_g2_struct;  /* g2-defstruct-structure-name::procedure-invocation-g2-struct */

/* CALLED-PROCEDURE-INVOCATIONS-FOR-GRAPH-1 */
Object called_procedure_invocations_for_graph_1(invocation)
    Object invocation;
{
    Object invocation_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(162,97);
    if (SIMPLE_VECTOR_P(invocation) && EQ(ISVREF(invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct))
	return gensym_cons_1(invocation,Nil);
    else {
	invocation_1 = Nil;
	ab_loop_list_ = ISVREF(invocation,(SI_Long)13L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	invocation_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = called_procedure_invocations_for_graph_1(invocation_1);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Focus_for_graph_detailed_procedures, Qfocus_for_graph_detailed_procedures);

/* GET-WORKSPACE-FOR-GRAPH-DETAILED-PROCEDURES */
Object get_workspace_for_graph_detailed_procedures()
{
    x_note_fn_call(162,98);
    return make_workspace(6,Qtemporary_workspace,Nil,Nil,Nil,Nil,Nil);
}

static Object Qg2_defstruct_structure_name_code_body_invocation_g2_struct;  /* g2-defstruct-structure-name::code-body-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_remote_procedure_call_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-call-g2-struct */

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

static Object Qg2_defstruct_structure_name_formula_invocation_g2_struct;  /* g2-defstruct-structure-name::formula-invocation-g2-struct */

/* VALID-COMPUTATION-INSTANCE-P */
Object valid_computation_instance_p(invocation)
    Object invocation;
{
    Object type_name, temp;

    x_note_fn_call(162,99);
    if (SIMPLE_VECTOR_P(invocation)) {
	type_name = ISVREF(invocation,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct) 
		? T : Nil;
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct) 
		    ? T : Nil;
    }
    else
	temp = Nil;
    if (temp);
    else
	temp = SIMPLE_VECTOR_P(invocation) ? (EQ(ISVREF(invocation,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_remote_procedure_call_g2_struct) 
		? T : Nil) : Qnil;
    if (temp);
    else
	temp = SIMPLE_VECTOR_P(invocation) ? (EQ(ISVREF(invocation,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct) ? T :
		 Nil) : Qnil;
    if (temp);
    else
	temp = SIMPLE_VECTOR_P(invocation) ? (EQ(ISVREF(invocation,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_formula_invocation_g2_struct) 
		? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* LIST-CALLERS-OF-COMPUTATION-INSTANCE */
Object list_callers_of_computation_instance(computation_instance_at_breakpoint)
    Object computation_instance_at_breakpoint;
{
    Object invocation, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,100);
    PUSH_SPECIAL_WITH_SYMBOL(Computation_instance_at_breakpoint,Qcomputation_instance_at_breakpoint,computation_instance_at_breakpoint,
	    0);
      invocation = Computation_instance_at_breakpoint;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      if ( !TRUEP(valid_computation_instance_p(invocation)))
	  goto end_loop;
      ab_loopvar__2 = gensym_cons_1(invocation,Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      invocation = ISVREF(invocation,(SI_Long)12L);
      goto next_loop;
    end_loop:
      result = VALUES_1(ab_loopvar_);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object Qtop_level;          /* top-level */

static Object Qhash_detailed_procedure_graph;  /* hash-detailed-procedure-graph */

static Object Qcalled_detailed_procedure_graph;  /* called-detailed-procedure-graph */

static Object Qdetailed_procedure_graph_short_representation;  /* detailed-procedure-graph-short-representation */

/* GRAPH-DETAILED-PROCEDURES */
Object graph_detailed_procedures varargs_1(int, n)
{
    Object invocation, inspect_command_qm, focus_for_graph_detailed_procedures;
    Object workspace_with_inspect_command_qm, workspace_qm, temp, temp_1;
    Object temp_2, temp_3, temp_4, temp_5, temp_6, gensymed_symbol, temp_7;
    Object temp_8;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,101);
    INIT_ARGS_nonrelocating();
    invocation = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    focus_for_graph_detailed_procedures = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Focus_for_graph_detailed_procedures,Qfocus_for_graph_detailed_procedures,focus_for_graph_detailed_procedures,
	    0);
      END_ARGS_nonrelocating();
      workspace_with_inspect_command_qm = inspect_command_qm ? 
	      get_and_clear_workspace_for_inspect_command(1,
	      inspect_command_qm) : Nil;
      workspace_qm = workspace_with_inspect_command_qm;
      if (workspace_qm);
      else
	  workspace_qm = get_workspace_for_graph_detailed_procedures();
      temp = valid_computation_instance_p(invocation) ? invocation : 
	      Qtop_level;
      temp_1 = IDENTITY(Qhash_detailed_procedure_graph);
      if (temp_1);
      else
	  temp_1 = Qsxhashw;
      temp_2 = IDENTITY(Nil);
      if (temp_2);
      else
	  temp_2 = Qvertical;
      temp_3 = IDENTITY(Nil);
      if (temp_3);
      else
	  temp_3 = FIX((SI_Long)50L);
      temp_4 = IDENTITY(Nil);
      if (temp_4);
      else
	  temp_4 = FIX((SI_Long)50L);
      if ( !TRUEP(workspace_with_inspect_command_qm)) {
	  temp_5 = Pane_for_debugger_pause;
	  if (temp_5);
	  else
	      temp_5 = BOUNDP(Qcurrent_workstation_detail_pane) ? 
		      Current_workstation_detail_pane : Qnil;
	  if (temp_5);
	  else {
	      temp_5 = ISVREF(System_window,(SI_Long)3L);
	      temp_5 = CAR(temp_5);
	  }
      }
      else
	  temp_5 = Nil;
      temp_6 = IDENTITY(Nil);
      if (temp_6);
      else
	  temp_6 = Qtemporary_workspace;
      if (inspect_command_qm) {
	  gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  temp_7 = gensymed_symbol;
      }
      else
	  temp_7 = Nil;
      if (inspect_command_qm) {
	  gensymed_symbol_1 = (SI_Long)5L;
	  gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  temp_8 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
      }
      else
	  temp_8 = Nil;
      reclaim_graph_display_1(graph_frame_hierarchy_function(temp,
	      Qcalled_detailed_procedure_graph,Nil,
	      Qdetailed_procedure_graph_short_representation,temp_1,temp_2,
	      temp_3,temp_4,temp_5,temp_6,workspace_qm,temp_7,temp_8));
      if (workspace_with_inspect_command_qm)
	  result = shrink_wrap_workspace(workspace_with_inspect_command_qm);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Non_procedure_root_invocations, Qnon_procedure_root_invocations);

/* ROOT-INVOCATION-OF-INVOCATION */
Object root_invocation_of_invocation(instance)
    Object instance;
{
    Object invocation, next;

    x_note_fn_call(162,102);
    if (valid_computation_instance_p(instance)) {
	invocation = instance;
	next = Nil;
      next_loop:
	next = ISVREF(invocation,(SI_Long)12L);
	if ( !TRUEP(valid_computation_instance_p(next)))
	    goto end_loop;
	invocation = next;
	goto next_loop;
      end_loop:
	return VALUES_1(invocation);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* MAYBE-COLLECT-ROOT-INVOCATION-OF-INVOCATION */
Object maybe_collect_root_invocation_of_invocation(instance)
    Object instance;
{
    Object invocation, type_name;
    char temp;

    x_note_fn_call(162,103);
    invocation = root_invocation_of_invocation(instance);
    temp =  !TRUEP(invocation);
    if (temp);
    else if (SIMPLE_VECTOR_P(invocation)) {
	type_name = ISVREF(invocation,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else
	temp = SIMPLE_VECTOR_P(invocation) ? EQ(ISVREF(invocation,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_remote_procedure_call_g2_struct) 
		: TRUEP(Qnil);
    if (temp);
    else
	temp = TRUEP(memq_function(invocation,Non_procedure_root_invocations));
    if ( !temp) {
	Non_procedure_root_invocations = gensym_cons_1(invocation,
		Non_procedure_root_invocations);
	return VALUES_1(Non_procedure_root_invocations);
    }
    else
	return VALUES_1(Nil);
}

static Object Qexecute_computation_instance;  /* execute-computation-instance */

/* COLLECT-NON-PROCEDURE-ROOT-INVOCATIONS-IN-QUEUE */
Object collect_non_procedure_root_invocations_in_queue(constant_queue)
    Object constant_queue;
{
    Object fn, queue, next_queue_element, schedule_task;

    x_note_fn_call(162,104);
    fn = SYMBOL_FUNCTION(Qexecute_computation_instance);
    queue = constant_queue;
    next_queue_element = Nil;
    schedule_task = Nil;
    next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),queue);
  next_loop:
    if ( !TRUEP(next_queue_element))
	goto end_loop;
    schedule_task = ISVREF(next_queue_element,(SI_Long)4L);
    next_queue_element = constant_queue_next(next_queue_element,queue);
    if (EQ(ISVREF(schedule_task,(SI_Long)8L),fn))
	maybe_collect_root_invocation_of_invocation(ISVREF(schedule_task,
		(SI_Long)13L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COLLECT-NON-PROCEDURE-ROOT-INVOCATIONS */
Object collect_non_procedure_root_invocations()
{
    Object non_procedure_root_invocations, queue, constant_queue;
    SI_Long i, ab_loop_bind_, priority;
    Declare_special(1);
    Object result;

    x_note_fn_call(162,105);
    non_procedure_root_invocations = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Non_procedure_root_invocations,Qnon_procedure_root_invocations,non_procedure_root_invocations,
	    0);
      i = (SI_Long)0L;
      ab_loop_bind_ = IFIX(Number_of_all_threads);
      queue = Nil;
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      queue = ISVREF(Immediate_task_queue_vector,i);
      if ( ! !TRUEP(constant_queue_next(ISVREF(queue,(SI_Long)2L),queue)))
	  collect_non_procedure_root_invocations_in_queue(queue);
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:;
      priority = IFIX(Highest_system_priority);
      constant_queue = Nil;
    next_loop_1:
      if (priority > IFIX(Lowest_system_priority))
	  goto end_loop_1;
      constant_queue = ISVREF(Current_task_queue_vector,priority);
      collect_non_procedure_root_invocations_in_queue(constant_queue);
      priority = priority + (SI_Long)1L;
      goto next_loop_1;
    end_loop_1:;
      maybe_collect_root_invocation_of_invocation(Computation_instance_at_breakpoint);
      result = VALUES_1(Non_procedure_root_invocations);
    POP_SPECIAL();
    return result;
}

/* CALLED-DETAILED-PROCEDURE-GRAPH */
Object called_detailed_procedure_graph(top_level_or_invocation,extra_arg)
    Object top_level_or_invocation, extra_arg;
{
    Object valid_invocation_qm, top_array, invocation_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, result_1, x, ab_loop_list_;
    Object focus_element;
    SI_Long index_1, ab_loop_bind_;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(162,106);
    SAVE_STACK();
    valid_invocation_qm = Nil;
    if (EQ(top_level_or_invocation,Qtop_level)) {
	LOCK(Procedure_invocations_lock);
	if (PUSH_UNWIND_PROTECT(0)) {
	    top_array = Top_level_procedure_invocations_array;
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(ISVREF(top_array,(SI_Long)1L));
	    invocation_qm = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    invocation_qm = FIXNUM_LE(ISVREF(top_array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(top_array,
		    index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(top_array,(index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (invocation_qm) {
		temp = ISVREF(invocation_qm,(SI_Long)12L);
		if (temp);
		else
		    temp = invocation_qm;
		valid_invocation_qm = temp;
		temp_1 = TRUEP(valid_invocation_qm);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ?  
		    !TRUEP(g2gl_call_invocation_p_function(valid_invocation_qm)) 
		    : TRUEP(Nil)) {
		ab_loopvar__2 = gensym_cons_1(valid_invocation_qm,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = ab_loopvar_;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    SAVE_VALUES(VALUES_1(temp));
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Procedure_invocations_lock);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	temp = result;
	result_1 = nconc2(temp,collect_non_procedure_root_invocations());
    }
    else if (SIMPLE_VECTOR_P(top_level_or_invocation) && 
	    EQ(ISVREF(top_level_or_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct) || 
	    SIMPLE_VECTOR_P(top_level_or_invocation) && 
	    EQ(ISVREF(top_level_or_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_formula_invocation_g2_struct))
	result_1 = Nil;
    else if (valid_computation_instance_p(top_level_or_invocation))
	result_1 = 
		copy_list_using_gensym_conses_1(ISVREF(top_level_or_invocation,
		(SI_Long)13L));
    else
	result_1 = Qt;
    x = Nil;
    ab_loop_list_ = Focus_for_graph_detailed_procedures;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(x,result_1)) {
	focus_element = x;
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
    focus_element = Qnil;
  end_2:;
    if (focus_element) {
	result = gensym_cons_1(focus_element,
		delete_gensym_element_1(focus_element,result_1));
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(result_1);
    }
}

static Object string_constant;     /* "~%" */

/* TWRITE-DETAILED-SHORT-REPRESENTATION-OF-CODE-BODY-INVOCATION */
Object twrite_detailed_short_representation_of_code_body_invocation(invocation)
    Object invocation;
{
    x_note_fn_call(162,107);
    if (Disassemble_enabled_qm) {
	write_stack_instruction(ISVREF(invocation,(SI_Long)3L),
		ISVREF(invocation,(SI_Long)1L),ISVREF(invocation,(SI_Long)4L));
	tformat(1,string_constant);
    }
    return write_code_body_environment(ISVREF(ISVREF(invocation,
	    (SI_Long)8L),(SI_Long)7L),ISVREF(invocation,(SI_Long)2L));
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_1;   /* "RPC ~A" */

static Object string_constant_2;   /* "call" */

static Object string_constant_3;   /* "start" */

static Object string_constant_4;   /* " from " */

static Object string_constant_5;   /* "closed connection" */

static Object string_constant_6;   /* "~%server interface ~NF" */

static Object string_constant_7;   /* " to ~NF across ~NF~%connecting to " */

static Object string_constant_8;   /* " to closed connection" */

static Object string_constant_9;   /* "~NF" */

static Object string_constant_10;  /* "Unknown thing ~a" */

/* DETAILED-PROCEDURE-GRAPH-SHORT-REPRESENTATION */
Object detailed_procedure_graph_short_representation(symbol_or_invocation)
    Object symbol_or_invocation;
{
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object socket_qm, interface_1, type_name;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(5);

    x_note_fn_call(162,108);
    if (SYMBOLP(symbol_or_invocation))
	temp = copy_text_string(symbol_name_text_string(symbol_or_invocation));
    else if (SIMPLE_VECTOR_P(symbol_or_invocation) && 
	    EQ(ISVREF(symbol_or_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct)) {
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
		  write_procedure_invocation_instance_from_slot(symbol_or_invocation,
			  Nil);
		  tformat(1,string_constant);
		  twrite_detailed_short_representation_of_code_body_invocation(symbol_or_invocation);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else if (SIMPLE_VECTOR_P(symbol_or_invocation) && 
	    EQ(ISVREF(symbol_or_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct)) {
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
		  tformat(2,string_constant_1,ISVREF(symbol_or_invocation,
			  (SI_Long)22L) ? string_constant_2 : 
			  string_constant_3);
		  socket_qm = ISVREF(symbol_or_invocation,(SI_Long)24L);
		  if (ISVREF(symbol_or_invocation,(SI_Long)13L)) {
		      tformat(1,string_constant_4);
		      if (socket_qm)
			  twrite_icp_socket_connection_name(socket_qm);
		      else
			  tformat(1,string_constant_5);
		      interface_1 = ISVREF(symbol_or_invocation,(SI_Long)25L);
		      if (interface_1)
			  tformat(2,string_constant_6,interface_1);
		  }
		  else if (socket_qm) {
		      tformat(3,string_constant_7,
			      ISVREF(symbol_or_invocation,(SI_Long)23L),
			      ISVREF(symbol_or_invocation,(SI_Long)25L));
		      twrite_icp_socket_connection_name(ISVREF(symbol_or_invocation,
			      (SI_Long)24L));
		  }
		  else
		      tformat(1,string_constant_8);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else if (SIMPLE_VECTOR_P(symbol_or_invocation) && 
	    EQ(ISVREF(symbol_or_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct) || 
	    SIMPLE_VECTOR_P(symbol_or_invocation) && 
	    EQ(ISVREF(symbol_or_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_formula_invocation_g2_struct)) {
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
		  tformat(2,string_constant_9,
			  SIMPLE_VECTOR_P(symbol_or_invocation) && 
			  EQ(ISVREF(symbol_or_invocation,(SI_Long)0L),
			  Qg2_defstruct_structure_name_rule_instance_g2_struct) 
			  ? ISVREF(symbol_or_invocation,(SI_Long)8L) : 
			  ISVREF(symbol_or_invocation,(SI_Long)8L));
		  if (Disassemble_enabled_qm) {
		      tformat(1,string_constant);
		      write_stack_instruction(ISVREF(symbol_or_invocation,
			      (SI_Long)3L),ISVREF(symbol_or_invocation,
			      (SI_Long)1L),ISVREF(symbol_or_invocation,
			      (SI_Long)4L));
		  }
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else {
	if (SIMPLE_VECTOR_P(symbol_or_invocation)) {
	    type_name = ISVREF(symbol_or_invocation,(SI_Long)0L);
	    temp_1 = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp_1);
	    else
		temp_1 = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      twrite_detailed_short_representation_of_code_body_invocation(symbol_or_invocation);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = tformat_text_string(2,string_constant_10,
		    symbol_or_invocation);
    }
    return make_description_box(temp);
}

/* HASH-DETAILED-PROCEDURE-GRAPH */
Object hash_detailed_procedure_graph(symbol_or_invocation)
    Object symbol_or_invocation;
{
    x_note_fn_call(162,109);
    return VALUES_1(FIX((SI_Long)1L));
}

/* WRITE-CODE-BODIES-FROM-SLOT */
Object write_code_bodies_from_slot(code_bodies,gensymed_symbol)
    Object code_bodies, gensymed_symbol;
{
    x_note_fn_call(162,110);
    return write_disassembled_code_bodies(code_bodies);
}

static Object string_constant_11;  /* "~%~%" */

static Object string_constant_12;  /* "Code Body ~a~%" */

static Object array_constant;      /* # */

/* WRITE-DISASSEMBLED-CODE-BODIES */
Object write_disassembled_code_bodies(code_bodies)
    Object code_bodies;
{
    Object default_constant_vector_qm, code_body_to_print, ab_loop_list_;
    Object byte_code_body_qm, first_time_qm, ab_loop_iter_flag_, temp, temp_1;
    SI_Long code_body_number;

    x_note_fn_call(162,111);
    default_constant_vector_qm = CAR(code_bodies) ? 
	    ISVREF(ISVREF(CAR(code_bodies),(SI_Long)8L),(SI_Long)3L) : Nil;
    code_body_number = (SI_Long)0L;
    code_body_to_print = Nil;
    ab_loop_list_ = code_bodies;
    byte_code_body_qm = Nil;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    code_body_to_print = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    byte_code_body_qm = ISVREF(code_body_to_print,(SI_Long)8L);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	tformat(1,string_constant_11);
    tformat(2,string_constant_12,FIX(code_body_number));
    if (byte_code_body_qm) {
	temp = byte_code_body_qm;
	temp_1 = ISVREF(byte_code_body_qm,(SI_Long)3L);
	if (temp_1);
	else
	    temp_1 = default_constant_vector_qm;
	write_byte_code_body(temp,temp_1);
    }
    else
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)16L));
    ab_loop_iter_flag_ = Nil;
    code_body_number = code_body_number + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

void proc_debug_INIT()
{
    Object temp, reclaim_structure_for_graph_display_1;
    Object reclaim_structure_for_graph_node_1, temp_1;
    Object reclaim_structure_for_dynamic_workspace_associated_structure_1;
    Object list_constant_3, Qslot_value_writer, Qwrite_code_bodies_from_slot;
    Object Qcode_bodies, AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qslot_value_reclaimer, Qreclaim_associated_dynamic_structure_value;
    Object Qassociated_dynamic_structure;
    Object Qdynamic_workspace_associated_structure, Qreclaim_structure;
    Object Qoutstanding_dynamic_workspace_associated_structure_count;
    Object Qdynamic_workspace_associated_structure_structure_memory_usage;
    Object Qutilities2, string_constant_23, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_22, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, string_constant_21;
    Object list_constant_2, Qdynamic_temporary_workspace, string_constant_20;
    Object string_constant_19, Qgraph_node, Qoutstanding_graph_node_count;
    Object Qgraph_node_structure_memory_usage, string_constant_18;
    Object string_constant_17, Qgraph_display;
    Object Qoutstanding_graph_display_count;
    Object Qgraph_display_structure_memory_usage, string_constant_16;
    Object string_constant_15, string_constant_14;
    Object Qgraph_layout_cons_memory_usage, Qoutstanding_graph_layout_conses;
    Object Qutilities1, list_constant_1, Qgraph_layout_cons_counter_vector;
    Object Qmake_thread_array, Kfuncall, list_constant;
    Object Qavailable_graph_layout_conses_tail_vector;
    Object Qavailable_graph_layout_conses_vector;
    Object Qout_graph_node_of_graphed_thing_hash_vector_43_vectors;
    Object Qgraph_node_of_graphed_thing_hash_vector_43_vector_memory_usage;
    Object string_constant_13;

    x_note_fn_call(162,112);
    SET_PACKAGE("AB");
    if (Current_graph_layout_hashing_function == UNBOUND)
	Current_graph_layout_hashing_function = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_graph_node_of_graphed_thing_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    Available_graph_node_of_graphed_thing_hash_vector_43_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_graph_node_of_graphed_thing_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors);
    record_system_variable(Qcount_of_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector 
	    == UNBOUND)
	Available_graph_node_of_graphed_thing_hash_vector_43_vectors_vector 
		= make_thread_array(Nil);
    Qout_graph_node_of_graphed_thing_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qgraph_node_of_graphed_thing_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("GRAPH-NODE-OF-GRAPHED-THING-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_13 = STATIC_STRING("1q83-X7y83*9y83-Ouy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_graph_node_of_graphed_thing_hash_vector_43_vectors);
    push_optimized_constant(Qgraph_node_of_graphed_thing_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    SET_SYMBOL_FUNCTION(Qgraph_node_of_graphed_thing_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(graph_node_of_graphed_thing_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_graph_node_of_graphed_thing_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qgraph_node_of_graphed_thing_tree_for_hash = 
	    STATIC_SYMBOL("GRAPH-NODE-OF-GRAPHED-THING-TREE-FOR-HASH",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qavailable_graph_layout_conses = 
	    STATIC_SYMBOL("AVAILABLE-GRAPH-LAYOUT-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graph_layout_conses,
	    Available_graph_layout_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_graph_layout_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_graph_layout_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-GRAPH-LAYOUT-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graph_layout_conses_tail,
	    Available_graph_layout_conses_tail);
    record_system_variable(Qavailable_graph_layout_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_graph_layout_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-GRAPH-LAYOUT-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graph_layout_conses_vector,
	    Available_graph_layout_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,Qnil);
    record_system_variable(Qavailable_graph_layout_conses_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_graph_layout_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-GRAPH-LAYOUT-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graph_layout_conses_tail_vector,
	    Available_graph_layout_conses_tail_vector);
    record_system_variable(Qavailable_graph_layout_conses_tail_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qgraph_layout_cons_counter_vector = 
	    STATIC_SYMBOL("GRAPH-LAYOUT-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraph_layout_cons_counter_vector,
	    Graph_layout_cons_counter_vector);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qgraph_layout_cons_counter_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qgraph_layout_cons_counter = STATIC_SYMBOL("GRAPH-LAYOUT-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraph_layout_cons_counter,
	    Graph_layout_cons_counter);
    record_system_variable(Qgraph_layout_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_graph_layout_conses = 
	    STATIC_SYMBOL("OUTSTANDING-GRAPH-LAYOUT-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_graph_layout_conses,
	    STATIC_FUNCTION(outstanding_graph_layout_conses,NIL,FALSE,0,0));
    Qgraph_layout_cons_memory_usage = 
	    STATIC_SYMBOL("GRAPH-LAYOUT-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qgraph_layout_cons_memory_usage,
	    STATIC_FUNCTION(graph_layout_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_14 = STATIC_STRING("1q83-X5y9k83-X4y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_graph_layout_conses);
    push_optimized_constant(Qgraph_layout_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qgraph_layout = STATIC_SYMBOL("GRAPH-LAYOUT",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_graph_display_g2_struct = 
	    STATIC_SYMBOL("GRAPH-DISPLAY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgraph_display = STATIC_SYMBOL("GRAPH-DISPLAY",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_graph_display_g2_struct,
	    Qgraph_display,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgraph_display,
	    Qg2_defstruct_structure_name_graph_display_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_graph_display == UNBOUND)
	The_type_description_of_graph_display = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83i5y1n83i5y8n8k1l8n0000001l1n8y83-42y1s83--My83--Ly83--Oy83--Ky83--Hy83--Iy83--Ny83--Jyk3Hyk0k0");
    temp = The_type_description_of_graph_display;
    The_type_description_of_graph_display = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_graph_display_g2_struct,
	    The_type_description_of_graph_display,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgraph_display,
	    The_type_description_of_graph_display,Qtype_description_of_type);
    Qoutstanding_graph_display_count = 
	    STATIC_SYMBOL("OUTSTANDING-GRAPH-DISPLAY-COUNT",AB_package);
    Qgraph_display_structure_memory_usage = 
	    STATIC_SYMBOL("GRAPH-DISPLAY-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_16 = STATIC_STRING("1q83i5y8s83-X2y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_graph_display_count);
    push_optimized_constant(Qgraph_display_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_graph_displays = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GRAPH-DISPLAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_graph_displays,
	    Chain_of_available_graph_displays);
    record_system_variable(Qchain_of_available_graph_displays,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qgraph_display_count = STATIC_SYMBOL("GRAPH-DISPLAY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraph_display_count,Graph_display_count);
    record_system_variable(Qgraph_display_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_graph_displays_vector == UNBOUND)
	Chain_of_available_graph_displays_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgraph_display_structure_memory_usage,
	    STATIC_FUNCTION(graph_display_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_graph_display_count,
	    STATIC_FUNCTION(outstanding_graph_display_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_graph_display_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_graph_display,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgraph_display,
	    reclaim_structure_for_graph_display_1);
    Qg2_defstruct_structure_name_graph_node_g2_struct = 
	    STATIC_SYMBOL("GRAPH-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgraph_node = STATIC_SYMBOL("GRAPH-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_graph_node_g2_struct,
	    Qgraph_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgraph_node,
	    Qg2_defstruct_structure_name_graph_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_graph_node == UNBOUND)
	The_type_description_of_graph_node = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83i6y1n83i6y8n8k1l8n0000001l1n8y83-43y1p83--Sy83--Uy83--Qy83--Ty83--Ryk3Cyk0k0");
    temp = The_type_description_of_graph_node;
    The_type_description_of_graph_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_graph_node_g2_struct,
	    The_type_description_of_graph_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgraph_node,The_type_description_of_graph_node,
	    Qtype_description_of_type);
    Qoutstanding_graph_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-GRAPH-NODE-COUNT",AB_package);
    Qgraph_node_structure_memory_usage = 
	    STATIC_SYMBOL("GRAPH-NODE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_18 = STATIC_STRING("1q83i6y8s83-X6y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_graph_node_count);
    push_optimized_constant(Qgraph_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_graph_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GRAPH-NODES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_graph_nodes,
	    Chain_of_available_graph_nodes);
    record_system_variable(Qchain_of_available_graph_nodes,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qgraph_node_count = STATIC_SYMBOL("GRAPH-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraph_node_count,Graph_node_count);
    record_system_variable(Qgraph_node_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_graph_nodes_vector == UNBOUND)
	Chain_of_available_graph_nodes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgraph_node_structure_memory_usage,
	    STATIC_FUNCTION(graph_node_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_graph_node_count,
	    STATIC_FUNCTION(outstanding_graph_node_count,NIL,FALSE,0,0));
    reclaim_structure_for_graph_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_graph_node,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgraph_node,
	    reclaim_structure_for_graph_node_1);
    Qdynamic_temporary_workspace = 
	    STATIC_SYMBOL("DYNAMIC-TEMPORARY-WORKSPACE",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    list_constant_2 = STATIC_CONS(Qtemporary_workspace,Qnil);
    check_if_superior_classes_are_defined(Qdynamic_temporary_workspace,
	    list_constant_2);
    string_constant_19 = STATIC_STRING("0");
    string_constant_20 = 
	    STATIC_STRING("1l4z8r83Giy83Giy83KDy83KDy00001m1l8l1l8o00000");
    string_constant_21 = STATIC_STRING("1n8q1m83KDy1l8318y1o83Giy01l8l1l8o");
    temp = regenerate_optimized_constant(string_constant_19);
    temp_1 = regenerate_optimized_constant(string_constant_20);
    add_class_to_environment(9,Qdynamic_temporary_workspace,
	    list_constant_2,Nil,temp,Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_21),Nil);
    Qg2_defstruct_structure_name_dynamic_workspace_associated_structure_g2_struct 
	    = 
	    STATIC_SYMBOL("DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdynamic_workspace_associated_structure = 
	    STATIC_SYMBOL("DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_dynamic_workspace_associated_structure_g2_struct,
	    Qdynamic_workspace_associated_structure,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qdynamic_workspace_associated_structure,
	    Qg2_defstruct_structure_name_dynamic_workspace_associated_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_dynamic_workspace_associated_structure == 
	    UNBOUND)
	The_type_description_of_dynamic_workspace_associated_structure = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8m836my1n836my8n8k1l8n0000000kmk0k0");
    temp = The_type_description_of_dynamic_workspace_associated_structure;
    The_type_description_of_dynamic_workspace_associated_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_22));
    mutate_global_property(Qg2_defstruct_structure_name_dynamic_workspace_associated_structure_g2_struct,
	    The_type_description_of_dynamic_workspace_associated_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qdynamic_workspace_associated_structure,
	    The_type_description_of_dynamic_workspace_associated_structure,
	    Qtype_description_of_type);
    Qoutstanding_dynamic_workspace_associated_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-COUNT",
	    AB_package);
    Qdynamic_workspace_associated_structure_structure_memory_usage = 
	    STATIC_SYMBOL("DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_23 = STATIC_STRING("1q836my8s83-S7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_dynamic_workspace_associated_structure_count);
    push_optimized_constant(Qdynamic_workspace_associated_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_dynamic_workspace_associated_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_dynamic_workspace_associated_structures,
	    Chain_of_available_dynamic_workspace_associated_structures);
    record_system_variable(Qchain_of_available_dynamic_workspace_associated_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qdynamic_workspace_associated_structure_count = 
	    STATIC_SYMBOL("DYNAMIC-WORKSPACE-ASSOCIATED-STRUCTURE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdynamic_workspace_associated_structure_count,
	    Dynamic_workspace_associated_structure_count);
    record_system_variable(Qdynamic_workspace_associated_structure_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_dynamic_workspace_associated_structures_vector 
	    == UNBOUND)
	Chain_of_available_dynamic_workspace_associated_structures_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdynamic_workspace_associated_structure_structure_memory_usage,
	    STATIC_FUNCTION(dynamic_workspace_associated_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_dynamic_workspace_associated_structure_count,
	    STATIC_FUNCTION(outstanding_dynamic_workspace_associated_structure_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_dynamic_workspace_associated_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_dynamic_workspace_associated_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qdynamic_workspace_associated_structure,
	    reclaim_structure_for_dynamic_workspace_associated_structure_1);
    Qassociated_dynamic_structure = 
	    STATIC_SYMBOL("ASSOCIATED-DYNAMIC-STRUCTURE",AB_package);
    Qreclaim_associated_dynamic_structure_value = 
	    STATIC_SYMBOL("RECLAIM-ASSOCIATED-DYNAMIC-STRUCTURE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_associated_dynamic_structure_value,
	    STATIC_FUNCTION(reclaim_associated_dynamic_structure_value,NIL,
	    FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qassociated_dynamic_structure,
	    SYMBOL_FUNCTION(Qreclaim_associated_dynamic_structure_value),
	    Qslot_value_reclaimer);
    Qsxhashw = STATIC_SYMBOL("SXHASHW",AB_package);
    SET_SYMBOL_FUNCTION(Qsxhashw,STATIC_FUNCTION(sxhashw,NIL,FALSE,1,1));
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Original_graph_depth = FIX((SI_Long)32L);
    if (Graph_display_changed_during_update_qm == UNBOUND)
	Graph_display_changed_during_update_qm = Nil;
    Qvertical = STATIC_SYMBOL("VERTICAL",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Kdraw_as_soon_as_possible = STATIC_SYMBOL("DRAW-AS-SOON-AS-POSSIBLE",
	    Pkeyword);
    if (Graphed_block_groups_to_move == UNBOUND)
	Graphed_block_groups_to_move = Nil;
    if (Graph_nodes_needing_children_connections == UNBOUND)
	Graph_nodes_needing_children_connections = Nil;
    if (Graph_nodes_to_add_as_subblocks == UNBOUND)
	Graph_nodes_to_add_as_subblocks = Nil;
    Qsub_nodes = STATIC_SYMBOL("SUB-NODES",AB_package);
    Qinverted = STATIC_SYMBOL("INVERTED",AB_package);
    Qinverted_sub_nodes = STATIC_SYMBOL("INVERTED-SUB-NODES",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qhorizontal = STATIC_SYMBOL("HORIZONTAL",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbackwards = STATIC_SYMBOL("BACKWARDS",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qsuperior_node = STATIC_SYMBOL("SUPERIOR-NODE",AB_package);
    Qframe_hash_function = STATIC_SYMBOL("FRAME-HASH-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qframe_hash_function,
	    STATIC_FUNCTION(frame_hash_function,NIL,FALSE,1,1));
    Qcalled_procedure_invocations_for_graph = 
	    STATIC_SYMBOL("CALLED-PROCEDURE-INVOCATIONS-FOR-GRAPH",AB_package);
    Qmake_short_representation = STATIC_SYMBOL("MAKE-SHORT-REPRESENTATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_short_representation,
	    STATIC_FUNCTION(make_short_representation,NIL,TRUE,1,4));
    SET_SYMBOL_FUNCTION(Qcalled_procedure_invocations_for_graph,
	    STATIC_FUNCTION(called_procedure_invocations_for_graph,NIL,
	    FALSE,2,2));
    Qg2_defstruct_structure_name_procedure_invocation_g2_struct = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Focus_for_graph_detailed_procedures == UNBOUND)
	Focus_for_graph_detailed_procedures = Nil;
    Qg2_defstruct_structure_name_code_body_invocation_g2_struct = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-CALL-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_formula_invocation_g2_struct = 
	    STATIC_SYMBOL("FORMULA-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    Qhash_detailed_procedure_graph = 
	    STATIC_SYMBOL("HASH-DETAILED-PROCEDURE-GRAPH",AB_package);
    Qcurrent_workstation_detail_pane = 
	    STATIC_SYMBOL("CURRENT-WORKSTATION-DETAIL-PANE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_workstation_detail_pane,
	    Current_workstation_detail_pane);
    Qcalled_detailed_procedure_graph = 
	    STATIC_SYMBOL("CALLED-DETAILED-PROCEDURE-GRAPH",AB_package);
    Qdetailed_procedure_graph_short_representation = 
	    STATIC_SYMBOL("DETAILED-PROCEDURE-GRAPH-SHORT-REPRESENTATION",
	    AB_package);
    if (Non_procedure_root_invocations == UNBOUND)
	Non_procedure_root_invocations = Nil;
    Qexecute_computation_instance = 
	    STATIC_SYMBOL("EXECUTE-COMPUTATION-INSTANCE",AB_package);
    SET_SYMBOL_FUNCTION(Qcalled_detailed_procedure_graph,
	    STATIC_FUNCTION(called_detailed_procedure_graph,NIL,FALSE,2,2));
    string_constant = STATIC_STRING("~%");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_1 = STATIC_STRING("RPC ~A");
    string_constant_2 = STATIC_STRING("call");
    string_constant_3 = STATIC_STRING("start");
    string_constant_4 = STATIC_STRING(" from ");
    string_constant_5 = STATIC_STRING("closed connection");
    string_constant_6 = STATIC_STRING("~%server interface ~NF");
    string_constant_7 = STATIC_STRING(" to ~NF across ~NF~%connecting to ");
    string_constant_8 = STATIC_STRING(" to closed connection");
    string_constant_9 = STATIC_STRING("~NF");
    string_constant_10 = STATIC_STRING("Unknown thing ~a");
    SET_SYMBOL_FUNCTION(Qdetailed_procedure_graph_short_representation,
	    STATIC_FUNCTION(detailed_procedure_graph_short_representation,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qhash_detailed_procedure_graph,
	    STATIC_FUNCTION(hash_detailed_procedure_graph,NIL,FALSE,1,1));
    Qcode_bodies = STATIC_SYMBOL("CODE-BODIES",AB_package);
    Qwrite_code_bodies_from_slot = 
	    STATIC_SYMBOL("WRITE-CODE-BODIES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_code_bodies_from_slot,
	    STATIC_FUNCTION(write_code_bodies_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qcode_bodies,
	    SYMBOL_FUNCTION(Qwrite_code_bodies_from_slot),Qslot_value_writer);
    string_constant_11 = STATIC_STRING("~%~%");
    string_constant_12 = STATIC_STRING("Code Body ~a~%");
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
}
