/* kbsv1.c
 * Input file:  kb-save1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kbsv1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Ok_file_saving_mode_qm, Qok_file_saving_mode_qm);

static Object list_constant;       /* # */

/* MAKE-SYSTEM-VERSION-FOR-OK-FILE */
Object make_system_version_for_ok_file()
{
    x_note_fn_call(133,0);
    return VALUES_1(list_constant);
}

/* MAKE-KB-FLAGS-FOR-OK-FILE */
Object make_kb_flags_for_ok_file()
{
    x_note_fn_call(133,1);
    return VALUES_1(FIX((SI_Long)234L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Slots_to_skip_saving_in_ok_files, Qslots_to_skip_saving_in_ok_files);

Object The_type_description_of_kb_transfer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_kb_transfers, Qchain_of_available_kb_transfers);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_transfer_count, Qkb_transfer_count);

Object Chain_of_available_kb_transfers_vector = UNBOUND;

/* KB-TRANSFER-STRUCTURE-MEMORY-USAGE */
Object kb_transfer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(133,2);
    temp = Kb_transfer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)20L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-KB-TRANSFER-COUNT */
Object outstanding_kb_transfer_count()
{
    Object def_structure_kb_transfer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(133,3);
    gensymed_symbol = IFIX(Kb_transfer_count);
    def_structure_kb_transfer_variable = Chain_of_available_kb_transfers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_kb_transfer_variable))
	goto end_loop;
    def_structure_kb_transfer_variable = 
	    ISVREF(def_structure_kb_transfer_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-KB-TRANSFER-1 */
Object reclaim_kb_transfer_1(kb_transfer)
    Object kb_transfer;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(133,4);
    inline_note_reclaim_cons(kb_transfer,Nil);
    structure_being_reclaimed = kb_transfer;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_pathname(ISVREF(kb_transfer,(SI_Long)5L));
      SVREF(kb_transfer,FIX((SI_Long)5L)) = Nil;
      reclaim_text_string(ISVREF(kb_transfer,(SI_Long)6L));
      SVREF(kb_transfer,FIX((SI_Long)6L)) = Nil;
      reclaim_text_string(ISVREF(kb_transfer,(SI_Long)7L));
      SVREF(kb_transfer,FIX((SI_Long)7L)) = Nil;
      reclaim_modified_pane_description(ISVREF(kb_transfer,(SI_Long)12L));
      SVREF(kb_transfer,FIX((SI_Long)12L)) = Nil;
      reclaim_if_gensym_pathname(ISVREF(kb_transfer,(SI_Long)16L));
      SVREF(kb_transfer,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_kb_transfers_vector,
	    IFIX(Current_thread_index));
    SVREF(kb_transfer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_kb_transfers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = kb_transfer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-KB-TRANSFER */
Object reclaim_structure_for_kb_transfer(kb_transfer)
    Object kb_transfer;
{
    x_note_fn_call(133,5);
    return reclaim_kb_transfer_1(kb_transfer);
}

static Object Qg2_defstruct_structure_name_kb_transfer_g2_struct;  /* g2-defstruct-structure-name::kb-transfer-g2-struct */

/* MAKE-PERMANENT-KB-TRANSFER-STRUCTURE-INTERNAL */
Object make_permanent_kb_transfer_structure_internal()
{
    Object def_structure_kb_transfer_variable;
    Object defstruct_g2_kb_transfer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(133,6);
    def_structure_kb_transfer_variable = Nil;
    atomic_incff_symval(Qkb_transfer_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_kb_transfer_variable = Nil;
	gensymed_symbol = (SI_Long)20L;
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
	defstruct_g2_kb_transfer_variable = the_array;
	SVREF(defstruct_g2_kb_transfer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kb_transfer_g2_struct;
	def_structure_kb_transfer_variable = defstruct_g2_kb_transfer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_kb_transfer_variable);
}

/* MAKE-KB-TRANSFER-1 */
Object make_kb_transfer_1()
{
    Object def_structure_kb_transfer_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(133,7);
    def_structure_kb_transfer_variable = 
	    ISVREF(Chain_of_available_kb_transfers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_kb_transfer_variable) {
	svref_arg_1 = Chain_of_available_kb_transfers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_kb_transfer_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kb_transfer_g2_struct;
    }
    else
	def_structure_kb_transfer_variable = 
		make_permanent_kb_transfer_structure_internal();
    inline_note_allocate_cons(def_structure_kb_transfer_variable,Nil);
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)1L)) = Koutput;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)2L)) = Kstream;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_kb_transfer_variable,FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_kb_transfer_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_kb_fsn_hash_table_hash_vector_131_vectors, Qavailable_kb_fsn_hash_table_hash_vector_131_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_kb_fsn_hash_table_hash_vector_131_vectors, Qcount_of_kb_fsn_hash_table_hash_vector_131_vectors);

Object Available_kb_fsn_hash_table_hash_vector_131_vectors_vector = UNBOUND;

/* KB-FSN-HASH-TABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE */
Object kb_fsn_hash_table_hash_vector_131_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(133,8);
    temp = Count_of_kb_fsn_hash_table_hash_vector_131_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)131L)));
    return VALUES_1(temp);
}

/* OUT-KB-FSN-HASH-TABLE-HASH-VECTOR-131-VECTORS */
Object out_kb_fsn_hash_table_hash_vector_131_vectors()
{
    Object temp;

    x_note_fn_call(133,9);
    temp = FIXNUM_MINUS(Count_of_kb_fsn_hash_table_hash_vector_131_vectors,
	    length(Available_kb_fsn_hash_table_hash_vector_131_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-KB-FSN-HASH-TABLE-HASH-VECTOR-131-VECTOR-INTERNAL */
Object make_permanent_kb_fsn_hash_table_hash_vector_131_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(133,10);
    atomic_incff_symval(Qcount_of_kb_fsn_hash_table_hash_vector_131_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)131L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-KB-FSN-HASH-TABLE-HASH-VECTOR */
Object make_kb_fsn_hash_table_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(133,11);
    if (ISVREF(Available_kb_fsn_hash_table_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_kb_fsn_hash_table_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_kb_fsn_hash_table_hash_vector_131_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_kb_fsn_hash_table_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_kb_fsn_hash_table_hash_vector_131_vectors_vector,
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
		make_permanent_kb_fsn_hash_table_hash_vector_131_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-KB-FSN-HASH-TABLE-HASH-VECTOR */
Object reclaim_kb_fsn_hash_table_hash_vector(kb_fsn_hash_table_hash_vector_131_vector)
    Object kb_fsn_hash_table_hash_vector_131_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(133,12);
    svref_arg_1 = Available_kb_fsn_hash_table_hash_vector_131_vectors_vector;
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
    M_CAR(gensymed_symbol) = kb_fsn_hash_table_hash_vector_131_vector;
    temp = 
	    ISVREF(Available_kb_fsn_hash_table_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-KB-FSN-HASH-TABLE-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_kb_fsn_hash_table_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(133,13);
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

/* MUTATE-KB-FSN-HASH-TABLE-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry(node,new_key,
	    new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(133,14);
    reclaim_frame_serial_number(ISVREF(node,(SI_Long)2L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry = UNBOUND;

static Object Qframe_serial_number_equal_function;  /* frame-serial-number-equal-function */

/* CLEAR-KB-FSN-HASH-TABLE-TREE */
Object clear_kb_fsn_hash_table_tree(kb_fsn_hash_table_tree_for_hash_skip_list)
    Object kb_fsn_hash_table_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_key;

    x_note_fn_call(133,15);
    head = M_CAR(M_CDR(kb_fsn_hash_table_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(kb_fsn_hash_table_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    temp = 
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qframe_serial_number_equal_function),
	    temp,kb_fsn_hash_table_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),frame_serial_number_hash_function(key_qm));
    old_key = temp;
    if (old_key)
	reclaim_frame_serial_number(old_key);
    goto next_loop;
  end_loop:;
    return VALUES_1(kb_fsn_hash_table_tree_for_hash_skip_list);
}

static Object Qkb_fsn_hash_table_tree_for_hash;  /* kb-fsn-hash-table-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-KB-FSN-HASH-TABLE */
Object make_kb_fsn_hash_table()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(133,16);
    new_vector = make_kb_fsn_hash_table_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    tail = 
	    make_kb_fsn_hash_table_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_kb_fsn_hash_table_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qkb_fsn_hash_table_tree_for_hash;
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

/* FLATTEN-KB-FSN-HASH-TABLE */
Object flatten_kb_fsn_hash_table(kb_fsn_hash_table_hash_table)
    Object kb_fsn_hash_table_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(133,17);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    subtree = ISVREF(kb_fsn_hash_table_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-KB-FSN-HASH-TABLE */
Object clear_kb_fsn_hash_table(kb_fsn_hash_table_hash_table)
    Object kb_fsn_hash_table_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(133,18);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    clear_kb_fsn_hash_table_tree(ISVREF(kb_fsn_hash_table_hash_table,index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-KB-FSN-HASH-TABLE */
Object reclaim_kb_fsn_hash_table(kb_fsn_hash_table_hash_table)
    Object kb_fsn_hash_table_hash_table;
{
    Object kb_fsn_hash_table_tree_for_hash_skip_list, head, tail, element_qm;
    Object key_qm, temp, old_key, last_1, next_qm, temp_1, svref_arg_2;
    SI_Long index_1;

    x_note_fn_call(133,19);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    kb_fsn_hash_table_tree_for_hash_skip_list = 
	    ISVREF(kb_fsn_hash_table_hash_table,index_1);
    head = M_CAR(M_CDR(kb_fsn_hash_table_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(kb_fsn_hash_table_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    temp = 
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qframe_serial_number_equal_function),
	    temp,kb_fsn_hash_table_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),frame_serial_number_hash_function(key_qm));
    old_key = temp;
    if (old_key)
	reclaim_frame_serial_number(old_key);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(kb_fsn_hash_table_tree_for_hash_skip_list) = Nil;
    M_CADR(kb_fsn_hash_table_tree_for_hash_skip_list) = Nil;
    M_CAR(kb_fsn_hash_table_tree_for_hash_skip_list) = Nil;
    if (kb_fsn_hash_table_tree_for_hash_skip_list) {
	last_1 = kb_fsn_hash_table_tree_for_hash_skip_list;
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
	    M_CDR(temp_1) = kb_fsn_hash_table_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = 
		    kb_fsn_hash_table_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(kb_fsn_hash_table_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = reclaim_kb_fsn_hash_table_hash_vector(kb_fsn_hash_table_hash_table);
    return VALUES_1(temp);
}

/* RECLAIM-FRAME-REFERENCE-BALANCE-LEAVES */
Object reclaim_frame_reference_balance_leaves(frame_reference_balance_binary_tree)
    Object frame_reference_balance_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, temp, svref_arg_2, last_1, next_qm, temp_1;

    x_note_fn_call(133,20);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(frame_reference_balance_binary_tree))
	goto end_loop;
    less_than_branch_qm = ISVREF(frame_reference_balance_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = ISVREF(frame_reference_balance_binary_tree,
	    (SI_Long)2L);
    alist = ISVREF(frame_reference_balance_binary_tree,(SI_Long)3L);
    reclaim_binary_tree_element_1(frame_reference_balance_binary_tree);
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
	reclaim_frame_reference_balance_leaves(less_than_branch_qm);
	frame_reference_balance_binary_tree = greater_than_branch_qm;
    }
    else {
	temp_1 = less_than_branch_qm;
	if (temp_1);
	else
	    temp_1 = greater_than_branch_qm;
	frame_reference_balance_binary_tree = temp_1;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-FRAME-REFERENCE-BALANCE-TREE */
Object clear_frame_reference_balance_tree(frame_reference_balance_binary_tree)
    Object frame_reference_balance_binary_tree;
{
    Object element_qm;

    x_note_fn_call(133,21);
    element_qm = CDR(frame_reference_balance_binary_tree);
    if (element_qm) {
	reclaim_frame_reference_balance_leaves(element_qm);
	M_CDR(frame_reference_balance_binary_tree) = Nil;
    }
    return VALUES_1(frame_reference_balance_binary_tree);
}

Object The_type_description_of_kb_save = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_kb_saves, Qchain_of_available_kb_saves);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_save_count, Qkb_save_count);

Object Chain_of_available_kb_saves_vector = UNBOUND;

/* KB-SAVE-STRUCTURE-MEMORY-USAGE */
Object kb_save_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(133,22);
    temp = Kb_save_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)50L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-KB-SAVE-COUNT */
Object outstanding_kb_save_count()
{
    Object def_structure_kb_save_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(133,23);
    gensymed_symbol = IFIX(Kb_save_count);
    def_structure_kb_save_variable = Chain_of_available_kb_saves;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_kb_save_variable))
	goto end_loop;
    def_structure_kb_save_variable = ISVREF(def_structure_kb_save_variable,
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

/* RECLAIM-KB-SAVE-1 */
Object reclaim_kb_save_1(kb_save)
    Object kb_save;
{
    Object structure_being_reclaimed, frame_reference_balance_binary_tree;
    Object element_qm, temp, svref_arg_2, thing;
    Declare_special(1);

    x_note_fn_call(133,24);
    inline_note_reclaim_cons(kb_save,Nil);
    structure_being_reclaimed = kb_save;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_pathname(ISVREF(kb_save,(SI_Long)5L));
      SVREF(kb_save,FIX((SI_Long)5L)) = Nil;
      reclaim_text_string(ISVREF(kb_save,(SI_Long)6L));
      SVREF(kb_save,FIX((SI_Long)6L)) = Nil;
      reclaim_text_string(ISVREF(kb_save,(SI_Long)7L));
      SVREF(kb_save,FIX((SI_Long)7L)) = Nil;
      reclaim_modified_pane_description(ISVREF(kb_save,(SI_Long)12L));
      SVREF(kb_save,FIX((SI_Long)12L)) = Nil;
      reclaim_if_gensym_pathname(ISVREF(kb_save,(SI_Long)16L));
      SVREF(kb_save,FIX((SI_Long)16L)) = Nil;
      reclaim_kb_fsn_hash_table(ISVREF(kb_save,(SI_Long)20L));
      SVREF(kb_save,FIX((SI_Long)20L)) = Nil;
      reclaim_gensym_string(ISVREF(kb_save,(SI_Long)25L));
      SVREF(kb_save,FIX((SI_Long)25L)) = Nil;
      reclaim_slot_value(ISVREF(kb_save,(SI_Long)27L));
      SVREF(kb_save,FIX((SI_Long)27L)) = Nil;
      reclaim_journal_list_function(ISVREF(kb_save,(SI_Long)28L));
      SVREF(kb_save,FIX((SI_Long)28L)) = Nil;
      frame_reference_balance_binary_tree = ISVREF(kb_save,(SI_Long)33L);
      element_qm = M_CDR(frame_reference_balance_binary_tree);
      if (element_qm)
	  reclaim_frame_reference_balance_leaves(element_qm);
      inline_note_reclaim_cons(frame_reference_balance_binary_tree,Qlookup);
      if (ISVREF(Available_lookup_conses_tail_vector,
	      IFIX(Current_thread_index))) {
	  temp = ISVREF(Available_lookup_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp) = frame_reference_balance_binary_tree;
	  temp = Available_lookup_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = frame_reference_balance_binary_tree;
      }
      else {
	  temp = Available_lookup_conses_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = frame_reference_balance_binary_tree;
	  temp = Available_lookup_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = frame_reference_balance_binary_tree;
      }
      M_CDR(frame_reference_balance_binary_tree) = Nil;
      SVREF(kb_save,FIX((SI_Long)33L)) = Nil;
      reclaim_deferred_kb_save_write_buffers(ISVREF(kb_save,(SI_Long)34L));
      SVREF(kb_save,FIX((SI_Long)34L)) = Nil;
      reclaim_kb_traversal_state(ISVREF(kb_save,(SI_Long)39L));
      SVREF(kb_save,FIX((SI_Long)39L)) = Nil;
      reclaim_gensym_string(ISVREF(kb_save,(SI_Long)40L));
      SVREF(kb_save,FIX((SI_Long)40L)) = Nil;
      reclaim_slot_value(ISVREF(kb_save,(SI_Long)43L));
      SVREF(kb_save,FIX((SI_Long)43L)) = Nil;
      reclaim_xml_object_and_fixups(ISVREF(kb_save,(SI_Long)47L));
      SVREF(kb_save,FIX((SI_Long)47L)) = Nil;
      thing = ISVREF(kb_save,(SI_Long)48L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(kb_save,FIX((SI_Long)48L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_kb_saves_vector,
	    IFIX(Current_thread_index));
    SVREF(kb_save,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_kb_saves_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = kb_save;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-KB-SAVE */
Object reclaim_structure_for_kb_save(kb_save)
    Object kb_save;
{
    x_note_fn_call(133,25);
    return reclaim_kb_save_1(kb_save);
}

static Object Qg2_defstruct_structure_name_kb_save_g2_struct;  /* g2-defstruct-structure-name::kb-save-g2-struct */

/* MAKE-PERMANENT-KB-SAVE-STRUCTURE-INTERNAL */
Object make_permanent_kb_save_structure_internal()
{
    Object def_structure_kb_save_variable, defstruct_g2_kb_save_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(133,26);
    def_structure_kb_save_variable = Nil;
    atomic_incff_symval(Qkb_save_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_kb_save_variable = Nil;
	gensymed_symbol = (SI_Long)50L;
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
	defstruct_g2_kb_save_variable = the_array;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kb_save_g2_struct;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_kb_save_variable,FIX((SI_Long)19L)) = Nil;
	def_structure_kb_save_variable = defstruct_g2_kb_save_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_kb_save_variable);
}

static Object Qframe_reference_balance;  /* frame-reference-balance */

static Object Kkb;                 /* :kb */

/* MAKE-KB-SAVE-INTERNAL-1 */
Object make_kb_save_internal_1()
{
    Object def_structure_kb_save_variable, temp, svref_arg_2, svref_new_value;
    Object new_cons, gensymed_symbol;

    x_note_fn_call(133,27);
    def_structure_kb_save_variable = 
	    ISVREF(Chain_of_available_kb_saves_vector,
	    IFIX(Current_thread_index));
    if (def_structure_kb_save_variable) {
	temp = Chain_of_available_kb_saves_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_kb_save_variable,(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_kb_save_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kb_save_g2_struct;
    }
    else
	def_structure_kb_save_variable = 
		make_permanent_kb_save_structure_internal();
    inline_note_allocate_cons(def_structure_kb_save_variable,Nil);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)1L)) = Koutput;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)2L)) = Kstream;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)19L)) = Nil;
    temp = make_kb_fsn_hash_table();
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)20L)) = temp;
    ISVREF(def_structure_kb_save_variable,(SI_Long)21L) = FIX((SI_Long)0L);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)22L)) = Nil;
    ISVREF(def_structure_kb_save_variable,(SI_Long)23L) = FIX((SI_Long)0L);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)24L)) = Nil;
    temp = obtain_simple_gensym_string(Write_kb_buffer_length);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)25L)) = temp;
    ISVREF(def_structure_kb_save_variable,(SI_Long)26L) = FIX((SI_Long)0L);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)28L)) = Nil;
    ISVREF(def_structure_kb_save_variable,(SI_Long)29L) = FIX((SI_Long)0L);
    ISVREF(def_structure_kb_save_variable,(SI_Long)30L) = FIX((SI_Long)0L);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)31L)) = Nil;
    ISVREF(def_structure_kb_save_variable,(SI_Long)32L) = FIX((SI_Long)0L);
    new_cons = ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qframe_reference_balance;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)33L)) = gensymed_symbol;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)36L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)37L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)38L)) = Nil;
    temp = 
	    journal_cons_1(journal_list_2(copy_frame_serial_number(Current_frame_serial_number),
	    Kkb),Nil);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)39L)) = temp;
    temp = obtain_simple_gensym_string(Write_kb_buffer_length);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)40L)) = temp;
    ISVREF(def_structure_kb_save_variable,(SI_Long)41L) = FIX((SI_Long)0L);
    ISVREF(def_structure_kb_save_variable,(SI_Long)42L) = FIX((SI_Long)0L);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)43L)) = Nil;
    ISVREF(def_structure_kb_save_variable,(SI_Long)44L) = FIX((SI_Long)0L);
    ISVREF(def_structure_kb_save_variable,(SI_Long)45L) = FIX((SI_Long)0L);
    ISVREF(def_structure_kb_save_variable,(SI_Long)46L) = FIX((SI_Long)1L);
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)47L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)48L)) = Nil;
    SVREF(def_structure_kb_save_variable,FIX((SI_Long)49L)) = Nil;
    return VALUES_1(def_structure_kb_save_variable);
}

/* RECLAIM-KB-TRAVERSAL-STATE */
Object reclaim_kb_traversal_state(list_1)
    Object list_1;
{
    Object x, ab_loop_list_, temp;

    x_note_fn_call(133,28);
    x = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CAR(x);
    M_CAR(x) = Nil;
    reclaim_frame_serial_number(temp);
    goto next_loop;
  end_loop:;
    return reclaim_journal_tree_1(list_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_object_index_property_name_pool, Qkb_object_index_property_name_pool);

DEFINE_VARIABLE_WITH_SYMBOL(Next_object_index_property_number, Qnext_object_index_property_number);

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

/* SET-COMPILED-KB-FILE-PATHNAME */
Object set_compiled_kb_file_pathname(kb_save,pathname_1,index_1)
    Object kb_save, pathname_1, index_1;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, aref_arg_2_1, indexed_basename;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(133,29);
    if (T) {
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
		  twrite_general_string(ISVREF(pathname_1,(SI_Long)4L));
		  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			  Total_length_of_current_wide_string))
		      extend_current_wide_string(Fill_pointer_for_current_wide_string);
		  temp = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)95L);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		  Fill_pointer_for_current_wide_string = temp;
		  twrite_fixnum(index_1);
		  indexed_basename = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	indexed_basename = Nil;
    temp = gensym_make_pathname_with_copied_components(Nil,Nil,
	    ISVREF(pathname_1,(SI_Long)3L),Nil,T ? array_constant : Nil,
	    Nil,indexed_basename);
    SVREF(kb_save,FIX((SI_Long)16L)) = temp;
    reclaim_text_string(indexed_basename);
    return VALUES_1(Nil);
}

static Object Qab_gensym;          /* gensym */

static Object string_constant;     /* "OBJECT-INDEX-PROPERTY-~d" */

static Object Qclear_text;         /* clear-text */

static Object Qnormal;             /* normal */

/* MAKE-KB-SAVE */
Object make_kb_save(pathname_1,serial_number,module_qm,pane_description_qm,
	    use_clear_text_qm,log_message_for_commit_after_saving_qm,
	    use_crlf_qm)
    Object pathname_1, serial_number, module_qm, pane_description_qm;
    Object use_clear_text_qm, log_message_for_commit_after_saving_qm;
    Object use_crlf_qm;
{
    Object kb_save, temp, compiled_file_pathname, gensym_pop_store, cons_1;
    Object next_cons, svref_arg_2;

    x_note_fn_call(133,30);
    kb_save = make_kb_save_internal_1();
    SVREF(kb_save,FIX((SI_Long)1L)) = Koutput;
    SVREF(kb_save,FIX((SI_Long)2L)) = Kstream;
    SVREF(kb_save,FIX((SI_Long)5L)) = pathname_1;
    temp = gensym_namestring(1,pathname_1);
    SVREF(kb_save,FIX((SI_Long)6L)) = temp;
    temp = copy_text_string(ISVREF(kb_save,(SI_Long)6L));
    SVREF(kb_save,FIX((SI_Long)7L)) = temp;
    SVREF(kb_save,FIX((SI_Long)8L)) = use_crlf_qm;
    if (Enable_saving_compiled_kbs_p)
	set_compiled_kb_file_pathname(kb_save,pathname_1,FIX((SI_Long)1L));
    else if (Enable_loading_compiled_kbs_p) {
	compiled_file_pathname = pathname_gt_shared_file_pathname(pathname_1);
	if (gensym_probe_file(compiled_file_pathname))
	    gensym_delete_file(compiled_file_pathname);
	reclaim_gensym_pathname(compiled_file_pathname);
    }
    if (Kb_object_index_property_name_pool) {
	gensym_pop_store = Nil;
	cons_1 = Kb_object_index_property_name_pool;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Kb_object_index_property_name_pool = next_cons;
	temp = gensym_pop_store;
    }
    else {
	temp = FIXNUM_ADD1(Next_object_index_property_number);
	Next_object_index_property_number = temp;
	temp = intern_text_string(1,tformat_text_string(2,string_constant,
		Next_object_index_property_number));
    }
    SVREF(kb_save,FIX((SI_Long)22L)) = temp;
    SVREF(kb_save,FIX((SI_Long)10L)) = serial_number;
    SVREF(kb_save,FIX((SI_Long)37L)) = module_qm;
    SVREF(kb_save,FIX((SI_Long)12L)) = pane_description_qm;
    temp = use_clear_text_qm ? Qclear_text : Qnormal;
    SVREF(kb_save,FIX((SI_Long)38L)) = temp;
    temp = 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(log_message_for_commit_after_saving_qm) 
	    != (SI_Long)0L ? 
	    copy_text_string(log_message_for_commit_after_saving_qm) : 
	    log_message_for_commit_after_saving_qm;
    SVREF(kb_save,FIX((SI_Long)48L)) = temp;
    return VALUES_1(kb_save);
}

Object The_type_description_of_saving_context = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_saving_contexts, Qchain_of_available_saving_contexts);

DEFINE_VARIABLE_WITH_SYMBOL(Saving_context_count, Qsaving_context_count);

Object Chain_of_available_saving_contexts_vector = UNBOUND;

/* SAVING-CONTEXT-STRUCTURE-MEMORY-USAGE */
Object saving_context_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(133,31);
    temp = Saving_context_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SAVING-CONTEXT-COUNT */
Object outstanding_saving_context_count()
{
    Object def_structure_saving_context_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(133,32);
    gensymed_symbol = IFIX(Saving_context_count);
    def_structure_saving_context_variable = Chain_of_available_saving_contexts;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_saving_context_variable))
	goto end_loop;
    def_structure_saving_context_variable = 
	    ISVREF(def_structure_saving_context_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SAVING-CONTEXT-1 */
Object reclaim_saving_context_1(saving_context)
    Object saving_context;
{
    Object structure_being_reclaimed, managed_float, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(133,33);
    inline_note_reclaim_cons(saving_context,Nil);
    structure_being_reclaimed = saving_context;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_journal_list_1(ISVREF(saving_context,(SI_Long)1L));
      SVREF(saving_context,FIX((SI_Long)1L)) = Nil;
      managed_float = ISVREF(saving_context,(SI_Long)5L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(saving_context,FIX((SI_Long)5L)) = Nil;
      reclaim_gensym_list_function(ISVREF(saving_context,(SI_Long)8L));
      SVREF(saving_context,FIX((SI_Long)8L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_saving_contexts_vector,
	    IFIX(Current_thread_index));
    SVREF(saving_context,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_saving_contexts_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = saving_context;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SAVING-CONTEXT */
Object reclaim_structure_for_saving_context(saving_context)
    Object saving_context;
{
    x_note_fn_call(133,34);
    return reclaim_saving_context_1(saving_context);
}

static Object Qg2_defstruct_structure_name_saving_context_g2_struct;  /* g2-defstruct-structure-name::saving-context-g2-struct */

/* MAKE-PERMANENT-SAVING-CONTEXT-STRUCTURE-INTERNAL */
Object make_permanent_saving_context_structure_internal()
{
    Object def_structure_saving_context_variable;
    Object defstruct_g2_saving_context_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(133,35);
    def_structure_saving_context_variable = Nil;
    atomic_incff_symval(Qsaving_context_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_saving_context_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_saving_context_variable = the_array;
	SVREF(defstruct_g2_saving_context_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_saving_context_g2_struct;
	def_structure_saving_context_variable = 
		defstruct_g2_saving_context_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_saving_context_variable);
}

static Object Qnever_opened;       /* never-opened */

/* MAKE-SAVING-CONTEXT-INTERNAL-1 */
Object make_saving_context_internal_1(list_of_kb_saves_in_progress,
	    type_of_kb_save,save_permanent_data_qm,save_runtime_data_qm,
	    saving_context_kb_file_progress_displays,saving_compiled_kbs_p)
    Object list_of_kb_saves_in_progress, type_of_kb_save;
    Object save_permanent_data_qm, save_runtime_data_qm;
    Object saving_context_kb_file_progress_displays, saving_compiled_kbs_p;
{
    Object def_structure_saving_context_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(133,36);
    def_structure_saving_context_variable = 
	    ISVREF(Chain_of_available_saving_contexts_vector,
	    IFIX(Current_thread_index));
    if (def_structure_saving_context_variable) {
	temp = Chain_of_available_saving_contexts_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_saving_context_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_saving_context_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_saving_context_g2_struct;
    }
    else
	def_structure_saving_context_variable = 
		make_permanent_saving_context_structure_internal();
    inline_note_allocate_cons(def_structure_saving_context_variable,Nil);
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)1L)) = 
	    list_of_kb_saves_in_progress;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)2L)) = 
	    type_of_kb_save;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)4L)) = 
	    save_permanent_data_qm;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)3L)) = 
	    save_runtime_data_qm;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)8L)) = 
	    saving_context_kb_file_progress_displays;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)10L)) = 
	    saving_compiled_kbs_p;
    temp = get_unix_time_to_the_second_as_managed_float();
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)5L)) = temp;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_saving_context_variable,FIX((SI_Long)9L)) = 
	    Qnever_opened;
    return VALUES_1(def_structure_saving_context_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_saving_context, Qcurrent_saving_context);

DEFINE_VARIABLE_WITH_SYMBOL(Current_kb_save, Qcurrent_kb_save);

DEFINE_VARIABLE_WITH_SYMBOL(Continuation_task_for_current_backup, Qcontinuation_task_for_current_backup);

Object Number_of_characters_beyond_which_to_start_a_new_saved_kb_line = UNBOUND;

Object Number_of_characters_beyond_which_to_start_a_new_saved_compiled_line = UNBOUND;

Object Number_of_characters_beyond_which_to_start_a_new_saved_compiled_file = UNBOUND;

Object Number_of_characters_at_which_to_break_a_character_sequence = UNBOUND;

/* FLUSH-KB-WRITE-BUFFER */
Object flush_kb_write_buffer()
{
    Object svref_arg_1, svref_new_value, temp;

    x_note_fn_call(133,37);
    if (ISVREF(Current_kb_save,(SI_Long)4L)) {
	if ( !TRUEP(flush_deferred_pending_kb_write_buffers_to_stream()) 
		||  !TRUEP(flush_kb_write_buffer_to_stream())) {
	    if ( !TRUEP(ISVREF(Current_kb_save,(SI_Long)27L))) {
		svref_arg_1 = Current_kb_save;
		svref_new_value = most_recent_file_operation_status_as_text();
		SVREF(svref_arg_1,FIX((SI_Long)27L)) = svref_new_value;
	    }
	}
    }
    else {
	svref_arg_1 = Current_kb_save;
	temp = ISVREF(Current_kb_save,(SI_Long)34L);
	svref_new_value = nconc2(temp,
		slot_value_cons_1(make_current_kb_write_buffer_copy(),Nil));
	SVREF(svref_arg_1,FIX((SI_Long)34L)) = svref_new_value;
	svref_arg_1 = Current_kb_save;
	ISVREF(svref_arg_1,(SI_Long)26L) = FIX((SI_Long)0L);
    }
    return VALUES_1(Nil);
}

/* FLUSH-COMPILED-KB-WRITE-BUFFER */
Object flush_compiled_kb_write_buffer()
{
    Object svref_arg_1, svref_new_value, temp;

    x_note_fn_call(133,38);
    if (ISVREF(Current_kb_save,(SI_Long)15L)) {
	if ( 
		!TRUEP(flush_deferred_pending_compiled_kb_write_buffers_to_stream()) 
		||  !TRUEP(flush_compiled_kb_write_buffer_to_stream())) {
	    if ( !TRUEP(ISVREF(Current_kb_save,(SI_Long)27L))) {
		svref_arg_1 = Current_kb_save;
		svref_new_value = most_recent_file_operation_status_as_text();
		SVREF(svref_arg_1,FIX((SI_Long)27L)) = svref_new_value;
	    }
	}
    }
    else if ((SI_Long)0L < IFIX(ISVREF(Current_kb_save,(SI_Long)41L))) {
	svref_arg_1 = Current_kb_save;
	temp = ISVREF(Current_kb_save,(SI_Long)43L);
	svref_new_value = nconc2(temp,
		slot_value_cons_1(make_current_compiled_kb_write_buffer_copy(),
		Nil));
	SVREF(svref_arg_1,FIX((SI_Long)43L)) = svref_new_value;
	svref_arg_1 = Current_kb_save;
	ISVREF(svref_arg_1,(SI_Long)41L) = FIX((SI_Long)0L);
    }
    return VALUES_1(Nil);
}

static Object Qab_slot_value;      /* slot-value */

/* RECLAIM-DEFERRED-KB-SAVE-WRITE-BUFFERS */
Object reclaim_deferred_kb_save_write_buffers(buffer_list)
    Object buffer_list;
{
    Object buffer, slot_value_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(133,39);
    buffer = Nil;
  next_loop:
    if ( !TRUEP(buffer_list))
	goto end_loop;
    slot_value_pop_store = Nil;
    cons_1 = buffer_list;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    buffer_list = next_cons;
    buffer = slot_value_pop_store;
    reclaim_simple_gensym_string(buffer);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* FLUSH-KB-WRITE-BUFFER-TO-STREAM */
Object flush_kb_write_buffer_to_stream()
{
    Object status, svref_arg_1;

    x_note_fn_call(133,40);
    status = g2_stream_write_from_buffer(ISVREF(Current_kb_save,
	    (SI_Long)25L),ISVREF(Current_kb_save,(SI_Long)26L),
	    ISVREF(Current_kb_save,(SI_Long)4L));
    svref_arg_1 = Current_kb_save;
    ISVREF(svref_arg_1,(SI_Long)26L) = FIX((SI_Long)0L);
    return VALUES_1(status ? T : Qnil);
}

/* FLUSH-COMPILED-KB-WRITE-BUFFER-TO-STREAM */
Object flush_compiled_kb_write_buffer_to_stream()
{
    Object status, svref_arg_1;

    x_note_fn_call(133,41);
    status = g2_stream_write_from_buffer(ISVREF(Current_kb_save,
	    (SI_Long)40L),ISVREF(Current_kb_save,(SI_Long)41L),
	    ISVREF(Current_kb_save,(SI_Long)15L));
    svref_arg_1 = Current_kb_save;
    ISVREF(svref_arg_1,(SI_Long)41L) = FIX((SI_Long)0L);
    return VALUES_1(status ? T : Qnil);
}

/* FLUSH-DEFERRED-PENDING-KB-WRITE-BUFFERS-TO-STREAM */
Object flush_deferred_pending_kb_write_buffers_to_stream()
{
    Object buffer, status, slot_value_pop_store, svref_arg_1, cons_1;
    Object next_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(133,42);
    buffer = Nil;
    status = Nil;
  next_loop:
    if ( !TRUEP(ISVREF(Current_kb_save,(SI_Long)34L)))
	goto end_loop;
    slot_value_pop_store = Nil;
    svref_arg_1 = Current_kb_save;
    cons_1 = ISVREF(svref_arg_1,(SI_Long)34L);
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    SVREF(svref_arg_1,FIX((SI_Long)34L)) = next_cons;
    buffer = slot_value_pop_store;
    status = g2_stream_write_from_buffer(buffer,
	    SIMPLE_ARRAY_ANY_1_LENGTH(buffer),ISVREF(Current_kb_save,
	    (SI_Long)4L));
    reclaim_simple_gensym_string(buffer);
    if ( !TRUEP(status)) {
	temp_1 = Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = T;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* FLUSH-DEFERRED-PENDING-COMPILED-KB-WRITE-BUFFERS-TO-STREAM */
Object flush_deferred_pending_compiled_kb_write_buffers_to_stream()
{
    Object buffer, status, slot_value_pop_store, svref_arg_1, cons_1;
    Object next_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(133,43);
    buffer = Nil;
    status = Nil;
  next_loop:
    if ( !TRUEP(ISVREF(Current_kb_save,(SI_Long)43L)))
	goto end_loop;
    slot_value_pop_store = Nil;
    svref_arg_1 = Current_kb_save;
    cons_1 = ISVREF(svref_arg_1,(SI_Long)43L);
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    SVREF(svref_arg_1,FIX((SI_Long)43L)) = next_cons;
    buffer = slot_value_pop_store;
    status = g2_stream_write_from_buffer(buffer,
	    SIMPLE_ARRAY_ANY_1_LENGTH(buffer),ISVREF(Current_kb_save,
	    (SI_Long)15L));
    reclaim_simple_gensym_string(buffer);
    if ( !TRUEP(status)) {
	temp_1 = Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = T;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* MAKE-CURRENT-KB-WRITE-BUFFER-COPY */
Object make_current_kb_write_buffer_copy()
{
    Object buffer, length_1, new_simple_gensym_string;

    x_note_fn_call(133,44);
    buffer = ISVREF(Current_kb_save,(SI_Long)25L);
    length_1 = ISVREF(Current_kb_save,(SI_Long)26L);
    new_simple_gensym_string = obtain_simple_gensym_string(length_1);
    copy_portion_of_string_into_simple_gensym_string(buffer,
	    FIX((SI_Long)0L),length_1,new_simple_gensym_string,
	    FIX((SI_Long)0L));
    return VALUES_1(new_simple_gensym_string);
}

/* MAKE-CURRENT-COMPILED-KB-WRITE-BUFFER-COPY */
Object make_current_compiled_kb_write_buffer_copy()
{
    Object buffer, length_1, new_simple_gensym_string;

    x_note_fn_call(133,45);
    buffer = ISVREF(Current_kb_save,(SI_Long)40L);
    length_1 = ISVREF(Current_kb_save,(SI_Long)41L);
    new_simple_gensym_string = obtain_simple_gensym_string(length_1);
    copy_portion_of_string_into_simple_gensym_string(buffer,
	    FIX((SI_Long)0L),length_1,new_simple_gensym_string,
	    FIX((SI_Long)0L));
    return VALUES_1(new_simple_gensym_string);
}

/* WRITE-CHAR-FOR-KB */
Object write_char_for_kb(character_1)
    Object character_1;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(133,46);
    temp = Current_kb_save;
    SVREF(temp,FIX((SI_Long)24L)) = Nil;
    if (CHAR_EQ(CHR('\n'),character_1) && ISVREF(Current_kb_save,(SI_Long)8L))
	write_char_for_kb(CHR('\r'));
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
    SVREF(temp,FIX((SI_Long)29L)) = temp_1;
    temp = ISVREF(Current_kb_save,(SI_Long)25L);
    temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
    SET_SCHAR(temp,temp_1,character_1);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
    temp_2 = FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
	    Write_kb_buffer_length) ? flush_kb_write_buffer() : Nil;
    return VALUES_1(temp_2);
}

/* START-NEW-KB-LINE */
Object start_new_kb_line()
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(133,47);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)30L));
    SVREF(temp,FIX((SI_Long)30L)) = temp_1;
    update_file_progress_for_writing(0);
    if (CHAR_EQ(CHR('\n'),CHR('\n')) && ISVREF(Current_kb_save,(SI_Long)8L))
	write_char_for_kb(CHR('\r'));
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
    SVREF(temp,FIX((SI_Long)29L)) = temp_1;
    temp = ISVREF(Current_kb_save,(SI_Long)25L);
    temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
    temp_2 = CHR('\n');
    SET_SCHAR(temp,temp_1,temp_2);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
    if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
	    Write_kb_buffer_length))
	flush_kb_write_buffer();
    temp = Current_kb_save;
    ISVREF(temp,(SI_Long)29L) = FIX((SI_Long)0L);
    temp = Current_kb_save;
    return VALUES_1(SVREF(temp,FIX((SI_Long)24L)) = Nil);
}

/* UPDATE-FILE-PROGRESS-FOR-WRITING */
Object update_file_progress_for_writing varargs_1(int, n)
{
    Object force_update_p;
    SI_Long temp_1;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(133,48);
    INIT_ARGS_nonrelocating();
    force_update_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (ISVREF(Current_kb_save,(SI_Long)13L)) {
	temp = TRUEP(force_update_p);
	if (temp);
	else {
	    temp_1 = IFIX(ISVREF(Current_kb_save,(SI_Long)30L)) % (SI_Long)50L;
	    temp = temp_1 == (SI_Long)0L;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return update_file_progress_display(3,ISVREF(Current_kb_save,
		(SI_Long)13L),ISVREF(Current_kb_save,(SI_Long)30L),
		force_update_p);
    else
	return VALUES_1(Nil);
}

/* WRITE-CHAR-FOR-COMPILED-KB */
Object write_char_for_compiled_kb(character_1)
    Object character_1;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(133,49);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)42L));
    SVREF(temp,FIX((SI_Long)42L)) = temp_1;
    temp = ISVREF(Current_kb_save,(SI_Long)40L);
    temp_1 = ISVREF(Current_kb_save,(SI_Long)41L);
    SET_SCHAR(temp,temp_1,character_1);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)41L));
    temp_2 = FIXNUM_GE(SVREF(temp,FIX((SI_Long)41L)) = temp_1,
	    Write_kb_buffer_length) ? flush_compiled_kb_write_buffer() : Nil;
    return VALUES_1(temp_2);
}

/* WRITE-GENSYM-STRING-FOR-COMPILED-KB */
Object write_gensym_string_for_compiled_kb(gensym_string)
    Object gensym_string;
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(133,50);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(gensym_string));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    write_char_for_compiled_kb(CHR(ICHAR(gensym_string,i)));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

static Object string_constant_1;   /* "/*" */

static Object string_constant_2;   /* "?/" */

/* WRITE-GENSYM-STRING-COMMENT-FOR-COMPILED-KB */
Object write_gensym_string_comment_for_compiled_kb(gensym_string)
    Object gensym_string;
{
    Object prev, char_1, ab_loop_iter_flag_, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(133,51);
    write_gensym_string_for_compiled_kb(string_constant_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(gensym_string));
    prev = CHR(' ');
    char_1 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	prev = char_1;
    char_1 = CHR(ICHAR(gensym_string,i));
    if (EQ(prev,CHR('/')) && EQ(char_1,CHR('*')) || EQ(prev,CHR('*')) && 
	    EQ(char_1,CHR('/')))
	write_char_for_compiled_kb(CHR('\\'));
    write_char_for_compiled_kb(char_1);
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = write_gensym_string_for_compiled_kb(string_constant_2);
    return VALUES_1(temp);
}

/* START-NEW-COMPILED-KB-LINE-FUNCTION */
Object start_new_compiled_kb_line_function()
{
    x_note_fn_call(133,52);
    write_char_for_compiled_kb(CHR('\n'));
    return VALUES_1(Nil);
}

/* WRITE-BINARY-WORD-FOR-KB */
Object write_binary_word_for_kb(left_half,right_half)
    Object left_half, right_half;
{
    Object num;
    SI_Long temp;

    x_note_fn_call(133,53);
    num = FIX(IFIX(left_half) >>  -  - (SI_Long)3L);
    temp = IFIX(num) / (SI_Long)94L;
    write_char_for_kb(CODE_CHAR(FIX(temp + (SI_Long)33L)));
    temp = IFIX(num) % (SI_Long)94L;
    write_char_for_kb(CODE_CHAR(FIX(temp + (SI_Long)33L)));
    num = FIX(((IFIX(left_half) & (SI_Long)7L) << (SI_Long)16L) + 
	    IFIX(right_half));
    temp = IFIX(num) / (SI_Long)8836L;
    write_char_for_kb(CODE_CHAR(FIX(temp + (SI_Long)33L)));
    temp = IFIX(num) % (SI_Long)8836L;
    num = FIX(temp);
    temp = IFIX(num) / (SI_Long)94L;
    write_char_for_kb(CODE_CHAR(FIX(temp + (SI_Long)33L)));
    temp = IFIX(num) % (SI_Long)94L;
    return write_char_for_kb(CODE_CHAR(FIX(temp + (SI_Long)33L)));
}

/* WRITE-INTEGER-FOR-KB */
Object write_integer_for_kb(integer)
    Object integer;
{
    Object fixnum, temp, temp_1, temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(133,54);
    if (NUM_LE(Most_negative_fixnum32,integer) && NUM_LE(integer,
	    Most_positive_fixnum32)) {
	fixnum = coerce_number_to_fixnum(integer);
	write_fixnum_for_kb_1(fixnum);
    }
    else {
	if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
		Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	    start_new_kb_line();
	if (ISVREF(Current_kb_save,(SI_Long)24L)) {
	    if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,
		    (SI_Long)8L))
		write_char_for_kb(CHR('\r'));
	    temp = Current_kb_save;
	    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	    SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	    temp = ISVREF(Current_kb_save,(SI_Long)25L);
	    temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	    temp_2 = CHR(' ');
	    SET_SCHAR(temp,temp_1,temp_2);
	    temp = Current_kb_save;
	    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	    if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		    Write_kb_buffer_length))
		flush_kb_write_buffer();
	}
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_LONG_P(integer) != (SI_Long)0L && NUM_EQ(integer,
		    Most_negative_int64)) {
		write_most_negative_int64_for_kb(integer);
		temp_2 = CHR('-');
	    }
	    else {
		temp_2 = FIX((SI_Long)0L);
		if (NUM_GE(integer,temp_2)) {
		    write_bignum_digits_for_kb(integer);
		    temp_2 = CHR('+');
		}
		else {
		    write_bignum_digits_for_kb(negate(integer));
		    temp_2 = CHR('-');
		}
	    }
	    write_char_for_kb(temp_2);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    return VALUES_1(Nil);
}

/* WRITE-FIXNUM-FOR-KB */
Object write_fixnum_for_kb(fixnum)
    Object fixnum;
{
    x_note_fn_call(133,55);
    write_integer_for_kb(fixnum);
    return VALUES_1(Nil);
}

/* WRITE-LONG-FOR-KB */
Object write_long_for_kb(gensym_long)
    Object gensym_long;
{
    x_note_fn_call(133,56);
    write_char_for_kb(CHR('\?'));
    return write_integer_for_kb(gensym_long);
}

/* WRITE-FIXNUM-FOR-KB-1 */
Object write_fixnum_for_kb_1(fixnum_init)
    Object fixnum_init;
{
    Object temp, temp_1, temp_2;
    SI_Long fixnum;

    x_note_fn_call(133,57);
    fixnum = IFIX(fixnum_init);
    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	start_new_kb_line();
    if (ISVREF(Current_kb_save,(SI_Long)24L)) {
	if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	temp_2 = CHR(' ');
	SET_SCHAR(temp,temp_1,temp_2);
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
    }
    if (fixnum == IFIX(Most_negative_fixnum)) {
	write_fixnum_digits_for_kb(FIX((SI_Long)0L));
	temp_2 = CHR('-');
    }
    else if (fixnum < (SI_Long)0L) {
	write_fixnum_digits_for_kb(FIX( - fixnum));
	temp_2 = CHR('-');
    }
    else if (fixnum == (SI_Long)0L)
	temp_2 = CHR('Z');
    else {
	write_fixnum_digits_for_kb(FIX(fixnum));
	temp_2 = CHR('+');
    }
    write_char_for_kb(temp_2);
    return VALUES_1(Nil);
}

/* WRITE-FRAME-SERIAL-NUMBER-FOR-KB */
Object write_frame_serial_number_for_kb(frame_serial_number)
    Object frame_serial_number;
{
    Object ht, temp_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, gensymed_symbol_1, svref_arg_1;
    Object svref_new_value;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(133,58);
    ht = ISVREF(Current_kb_save,(SI_Long)20L);
    gensymed_symbol = 
	    IFIX(frame_serial_number_hash_function(frame_serial_number));
    temp = gensymed_symbol % (SI_Long)131L;
    temp_1 = SVREF(ht,FIX(temp));
    skip_list = CDR(temp_1);
    key_value = frame_serial_number;
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
	    key_hash_value &&  
	    !TRUEP(frame_serial_number_equal_function(key_value,
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
    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (frame_serial_number_equal_function(key_value,ISVREF(curr,
	    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
    if (temp_1);
    else {
	gensymed_symbol_1 = copy_frame_serial_number(frame_serial_number);
	gensymed_symbol = 
		IFIX(frame_serial_number_hash_function(gensymed_symbol_1));
	temp = gensymed_symbol % (SI_Long)131L;
	temp_2 = SVREF(ht,FIX(temp));
	temp_1 = Fp_mutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry;
	svref_arg_1 = Current_kb_save;
	svref_new_value = add1(ISVREF(svref_arg_1,(SI_Long)21L));
	temp_1 = set_skip_list_entry(temp_2,FIX((SI_Long)31L),
		Qframe_serial_number_equal_function,temp_1,T,
		gensymed_symbol_1,FIX(gensymed_symbol),SVREF(svref_arg_1,
		FIX((SI_Long)21L)) = svref_new_value);
    }
    return write_fixnum_for_kb(temp_1);
}

/* WRITE-FIXNUM-DIGITS-FOR-KB */
Object write_fixnum_digits_for_kb(non_negative_fixnum_init)
    Object non_negative_fixnum_init;
{
    Object chars_written_qm, temp, temp_1, character_2;
    SI_Long non_negative_fixnum, weight, gensymed_symbol, gensymed_symbol_1;
    char character_1;

    x_note_fn_call(133,59);
    non_negative_fixnum = IFIX(non_negative_fixnum_init);
    chars_written_qm = Nil;
    if (chars_written_qm || non_negative_fixnum >= (SI_Long)33554432L) {
	weight = non_negative_fixnum >>  -  - (SI_Long)25L;
	gensymed_symbol = weight;
	gensymed_symbol_1 = weight < (SI_Long)10L ? (SI_Long)48L : 
		(SI_Long)87L;
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(gensymed_symbol + 
		gensymed_symbol_1)));
	if (CHAR_EQ(CHR('\n'),CHAR_TO_CHARACTER(character_1)) && 
		ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	SET_SCHAR(temp,temp_1,CHAR_TO_CHARACTER(character_1));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
	non_negative_fixnum = non_negative_fixnum & (SI_Long)33554431L;
	chars_written_qm = T;
    }
    if (chars_written_qm || non_negative_fixnum >= (SI_Long)1048576L) {
	weight = non_negative_fixnum >>  -  - (SI_Long)20L;
	gensymed_symbol = weight;
	gensymed_symbol_1 = weight < (SI_Long)10L ? (SI_Long)48L : 
		(SI_Long)87L;
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(gensymed_symbol + 
		gensymed_symbol_1)));
	if (CHAR_EQ(CHR('\n'),CHAR_TO_CHARACTER(character_1)) && 
		ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	SET_SCHAR(temp,temp_1,CHAR_TO_CHARACTER(character_1));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
	non_negative_fixnum = non_negative_fixnum & (SI_Long)1048575L;
	chars_written_qm = T;
    }
    if (chars_written_qm || non_negative_fixnum >= (SI_Long)32768L) {
	weight = non_negative_fixnum >>  -  - (SI_Long)15L;
	gensymed_symbol = weight;
	gensymed_symbol_1 = weight < (SI_Long)10L ? (SI_Long)48L : 
		(SI_Long)87L;
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(gensymed_symbol + 
		gensymed_symbol_1)));
	if (CHAR_EQ(CHR('\n'),CHAR_TO_CHARACTER(character_1)) && 
		ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	SET_SCHAR(temp,temp_1,CHAR_TO_CHARACTER(character_1));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
	non_negative_fixnum = non_negative_fixnum & (SI_Long)32767L;
	chars_written_qm = T;
    }
    if (chars_written_qm || non_negative_fixnum >= (SI_Long)1024L) {
	weight = non_negative_fixnum >>  -  - (SI_Long)10L;
	gensymed_symbol = weight;
	gensymed_symbol_1 = weight < (SI_Long)10L ? (SI_Long)48L : 
		(SI_Long)87L;
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(gensymed_symbol + 
		gensymed_symbol_1)));
	if (CHAR_EQ(CHR('\n'),CHAR_TO_CHARACTER(character_1)) && 
		ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	SET_SCHAR(temp,temp_1,CHAR_TO_CHARACTER(character_1));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
	non_negative_fixnum = non_negative_fixnum & (SI_Long)1023L;
	chars_written_qm = T;
    }
    if (chars_written_qm || non_negative_fixnum >= (SI_Long)32L) {
	weight = non_negative_fixnum >>  -  - (SI_Long)5L;
	gensymed_symbol = weight;
	gensymed_symbol_1 = weight < (SI_Long)10L ? (SI_Long)48L : 
		(SI_Long)87L;
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(gensymed_symbol + 
		gensymed_symbol_1)));
	if (CHAR_EQ(CHR('\n'),CHAR_TO_CHARACTER(character_1)) && 
		ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	SET_SCHAR(temp,temp_1,CHAR_TO_CHARACTER(character_1));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
	non_negative_fixnum = non_negative_fixnum & (SI_Long)31L;
	chars_written_qm = T;
    }
    gensymed_symbol = non_negative_fixnum;
    gensymed_symbol_1 = non_negative_fixnum < (SI_Long)10L ? (SI_Long)48L :
	     (SI_Long)87L;
    character_2 = CODE_CHAR(FIX(gensymed_symbol + gensymed_symbol_1));
    if (CHAR_EQ(CHR('\n'),character_2) && ISVREF(Current_kb_save,(SI_Long)8L))
	write_char_for_kb(CHR('\r'));
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
    SVREF(temp,FIX((SI_Long)29L)) = temp_1;
    temp = ISVREF(Current_kb_save,(SI_Long)25L);
    temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
    SET_SCHAR(temp,temp_1,character_2);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
    if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
	    Write_kb_buffer_length))
	flush_kb_write_buffer();
    return VALUES_1(Nil);
}

/* WRITE-BIGNUM-DIGITS-FOR-KB */
Object write_bignum_digits_for_kb(non_negative_bignum)
    Object non_negative_bignum;
{
    Object temp, next, last_1, character_1, temp_1, temp_2;
    SI_Long lastf, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(133,60);
    temp = FIX((SI_Long)31L);
    if (NUM_GT(non_negative_bignum,temp)) {
	next = ash(non_negative_bignum,FIX((SI_Long)-5L));
	write_bignum_digits_for_kb(next);
    }
    last_1 = logand(non_negative_bignum,FIX((SI_Long)31L));
    lastf = IFIX(coerce(last_1,Qfixnum));
    gensymed_symbol = lastf;
    gensymed_symbol_1 = lastf < (SI_Long)10L ? (SI_Long)48L : (SI_Long)87L;
    character_1 = CODE_CHAR(FIX(gensymed_symbol + gensymed_symbol_1));
    if (CHAR_EQ(CHR('\n'),character_1) && ISVREF(Current_kb_save,(SI_Long)8L))
	write_char_for_kb(CHR('\r'));
    temp_1 = Current_kb_save;
    temp_2 = FIXNUM_ADD1(ISVREF(temp_1,(SI_Long)29L));
    SVREF(temp_1,FIX((SI_Long)29L)) = temp_2;
    temp_1 = ISVREF(Current_kb_save,(SI_Long)25L);
    temp_2 = ISVREF(Current_kb_save,(SI_Long)26L);
    SET_SCHAR(temp_1,temp_2,character_1);
    temp_1 = Current_kb_save;
    temp_2 = FIXNUM_ADD1(ISVREF(temp_1,(SI_Long)26L));
    if (FIXNUM_GE(SVREF(temp_1,FIX((SI_Long)26L)) = temp_2,
	    Write_kb_buffer_length))
	return flush_kb_write_buffer();
    else
	return VALUES_1(Nil);
}

Object Minus_most_negative_int64_ash_minus_5 = UNBOUND;

/* WRITE-MOST-NEGATIVE-INT64-FOR-KB */
Object write_most_negative_int64_for_kb(bignum)
    Object bignum;
{
    Object character_1, temp, temp_1;
    SI_Long last_1, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(133,61);
    write_bignum_digits_for_kb(Minus_most_negative_int64_ash_minus_5);
    last_1 = (SI_Long)0L;
    gensymed_symbol = last_1;
    gensymed_symbol_1 = last_1 < (SI_Long)10L ? (SI_Long)48L : (SI_Long)87L;
    character_1 = CODE_CHAR(FIX(gensymed_symbol + gensymed_symbol_1));
    if (CHAR_EQ(CHR('\n'),character_1) && ISVREF(Current_kb_save,(SI_Long)8L))
	write_char_for_kb(CHR('\r'));
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
    SVREF(temp,FIX((SI_Long)29L)) = temp_1;
    temp = ISVREF(Current_kb_save,(SI_Long)25L);
    temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
    SET_SCHAR(temp,temp_1,character_1);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
    if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
	    Write_kb_buffer_length))
	return flush_kb_write_buffer();
    else
	return VALUES_1(Nil);
}

/* WRITE-CHARACTER-SEQUENCE-FOR-KB */
Object write_character_sequence_for_kb(prefix_character,text_string,encrypt_qm)
    Object prefix_character, text_string, encrypt_qm;
{
    Object gensym_string, number_of_chars, temp, temp_1, temp_2, char_1;
    Object character_1;
    SI_Long local_base_reference, i, ab_loop_bind_, code, result_code;
    char string_is_simple_qm;

    x_note_fn_call(133,62);
    gensym_string = wide_string_to_gensym_string(text_string);
    number_of_chars = gensym_string_length(gensym_string);
    if (IFIX(FIXNUM_ADD(ISVREF(Current_kb_save,(SI_Long)29L),
	    number_of_chars)) + (SI_Long)3L > 
	    IFIX(Number_of_characters_at_which_to_break_a_character_sequence))
	start_new_kb_line();
    if (ISVREF(Current_kb_save,(SI_Long)24L)) {
	if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	temp_2 = CHR(' ');
	SET_SCHAR(temp,temp_1,temp_2);
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
    }
    else {
	temp = Current_kb_save;
	SVREF(temp,FIX((SI_Long)24L)) = T;
    }
    write_fixnum_digits_for_kb(number_of_chars);
    write_char_for_kb(prefix_character);
    if (Ok_file_saving_mode_qm) {
	temp_2 = ISVREF(Current_kb_save,(SI_Long)9L);
	if (temp_2);
	else
	    temp_2 = FIX((SI_Long)0L);
	local_base_reference = IFIX(temp_2);
    }
    else
	local_base_reference = IFIX(Standard_base_reference);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(number_of_chars);
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = string_is_simple_qm ? CHR(ISCHAR(gensym_string,i)) : 
	    CHR(ICHAR(gensym_string,i));
    if (FIXNUM_GE(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_at_which_to_break_a_character_sequence)) {
	if (CHAR_EQ(CHR('\n'),CHR('\\')) && ISVREF(Current_kb_save,
		(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	temp_2 = CHR('\\');
	SET_SCHAR(temp,temp_1,temp_2);
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
	start_new_kb_line();
	if (CHAR_EQ(CHR('\n'),CHR('\\')) && ISVREF(Current_kb_save,
		(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	temp_2 = CHR('\\');
	SET_SCHAR(temp,temp_1,temp_2);
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
    }
    if (encrypt_qm) {
	code = IFIX(CHAR_CODE(char_1));
	result_code = code;
	if (result_code != (SI_Long)92L && (SI_Long)32L <= result_code && 
		result_code <= (SI_Long)126L) {
	    local_base_reference = 
		    g2ext_eval_base_ref_val(local_base_reference);
	    result_code = g2ext_characters_cipher(code,
		    local_base_reference,Nil ? (SI_Long)1L : (SI_Long)0L);
	}
	code = result_code;
	character_1 = CODE_CHAR(FIX(code));
    }
    else
	character_1 = char_1;
    if (CHAR_EQ(CHR('\n'),character_1) && ISVREF(Current_kb_save,(SI_Long)8L))
	write_char_for_kb(CHR('\r'));
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
    SVREF(temp,FIX((SI_Long)29L)) = temp_1;
    temp = ISVREF(Current_kb_save,(SI_Long)25L);
    temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
    SET_SCHAR(temp,temp_1,character_1);
    temp = Current_kb_save;
    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
    if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
	    Write_kb_buffer_length))
	flush_kb_write_buffer();
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (encrypt_qm && Ok_file_saving_mode_qm) {
	temp = Current_kb_save;
	ISVREF(temp,(SI_Long)9L) = FIX(local_base_reference);
    }
    if (IFIX(number_of_chars) > (SI_Long)0L && CHAR_EQ(char_1,CHR('\\')))
	write_char_for_kb(CHR('\\'));
    reclaim_gensym_string(gensym_string);
    return VALUES_1(Nil);
}

static Object Qtype_of_syntactic_anomaly;  /* type-of-syntactic-anomaly */

static Object Qnumeric;            /* numeric */

/* WRITE-SYMBOL-FOR-KB */
Object write_symbol_for_kb(symbol,indexed_qm)
    Object symbol, indexed_qm;
{
    Object kb_object_index_qm, temp, temp_1, temp_2, name, package_qm;

    x_note_fn_call(133,63);
    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	start_new_kb_line();
    kb_object_index_qm = indexed_qm ? get(symbol,ISVREF(Current_kb_save,
	    (SI_Long)22L),_) : Nil;
    if (kb_object_index_qm) {
	if (ISVREF(Current_kb_save,(SI_Long)24L)) {
	    if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,
		    (SI_Long)8L))
		write_char_for_kb(CHR('\r'));
	    temp = Current_kb_save;
	    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	    SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	    temp = ISVREF(Current_kb_save,(SI_Long)25L);
	    temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	    temp_2 = CHR(' ');
	    SET_SCHAR(temp,temp_1,temp_2);
	    temp = Current_kb_save;
	    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	    if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		    Write_kb_buffer_length))
		flush_kb_write_buffer();
	}
	else {
	    temp = Current_kb_save;
	    SVREF(temp,FIX((SI_Long)24L)) = T;
	}
	write_fixnum_digits_for_kb(kb_object_index_qm);
    }
    else {
	if (indexed_qm) {
	    temp = gensym_cons_1(ISVREF(Current_kb_save,(SI_Long)22L),
		    gensym_cons_1(ISVREF(Current_kb_save,(SI_Long)23L),
		    SYMBOL_PLIST(symbol)));
	    SET_SYMBOL_PLIST(symbol,temp);
	    temp = Current_kb_save;
	    temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)23L));
	    SVREF(temp,FIX((SI_Long)23L)) = temp_1;
	    temp = Current_kb_save;
	    temp_1 = journal_cons_1(symbol,ISVREF(Current_kb_save,
		    (SI_Long)28L));
	    SVREF(temp,FIX((SI_Long)28L)) = temp_1;
	}
	if (EQ(getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		Qtype_of_syntactic_anomaly),Qnumeric)) {
	    if (indexed_qm) {
		temp = Current_kb_save;
		temp_1 = slot_value_cons_1(symbol,ISVREF(Current_kb_save,
			(SI_Long)11L));
		SVREF(temp,FIX((SI_Long)11L)) = temp_1;
	    }
	    else
		write_char_for_kb(CHR('$'));
	}
	name = symbol_name_text_string(symbol);
	package_qm = SYMBOL_PACKAGE(symbol);
	if (EQ(package_qm,Package) || EQ(package_qm,Lisp_package_1))
	    temp_2 = indexed_qm ? CHR('\'') : CHR('`');
	else if (EQ(package_qm,Keyword_package_1))
	    temp_2 = indexed_qm ? CHR(':') : CHR(',');
	else if (find_symbol(name,_))
	    temp_2 = indexed_qm ? CHR('\'') : CHR('`');
	else if ( !TRUEP(package_qm))
	    temp_2 = error((SI_Long)2L,
		    "Uninterned symbol ~S encountered while trying to save KB",
		    symbol);
	else
	    temp_2 = error((SI_Long)2L,
		    "Symbol ~S from a foreign package encountered while trying to save KB",
		    symbol);
	write_character_sequence_for_kb(temp_2,name,ISVREF(Current_kb_save,
		(SI_Long)9L));
    }
    return VALUES_1(Nil);
}

static Object Qmodules_this_format_frame_has_been_referenced_in;  /* modules-this-format-frame-has-been-referenced-in */

static Object Qcomputation_style;  /* computation-style */

static Object Qmodules_this_computation_style_has_been_referenced_in;  /* modules-this-computation-style-has-been-referenced-in */

static Object Qmodules_this_format_frame_has_been_written_in;  /* modules-this-format-frame-has-been-written-in */

static Object Qmodules_this_computation_style_has_been_written_in;  /* modules-this-computation-style-has-been-written-in */

/* PREPARE-BLOCKS-AND-CONNECTIONS-FOR-SAVING */
Object prepare_blocks_and_connections_for_saving(saving_modules_qm)
    Object saving_modules_qm;
{
    Object referenced_recorder_slot_name_qm, written_recorder_slot_name;
    Object scope_conses, ab_loopvar_, class_1, temp, gensymed_symbol;
    Object sub_class_bit_vector, gensymed_symbol_4, ab_loopvar__1, block;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_;
    Object connection_structure, ab_less_than_branch_qm_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(133,64);
    finish_all_table_updates();
    referenced_recorder_slot_name_qm = Nil;
    written_recorder_slot_name = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qblock;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      if (saving_modules_qm) {
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop);
	  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
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
	  if (temp_1)
	      referenced_recorder_slot_name_qm = 
		      Qmodules_this_format_frame_has_been_referenced_in;
	  else {
	      gensymed_symbol_4 = 
		      lookup_global_or_kb_specific_property_value(Qcomputation_style,
		      Class_description_gkbprop);
	      if (gensymed_symbol_4) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
	      if (temp_1)
		  referenced_recorder_slot_name_qm = 
			  Qmodules_this_computation_style_has_been_referenced_in;
	      else
		  referenced_recorder_slot_name_qm = Qnil;
	  }
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop);
	  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
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
	  if (temp_1)
	      written_recorder_slot_name = 
		      Qmodules_this_format_frame_has_been_written_in;
	  else {
	      gensymed_symbol_4 = 
		      lookup_global_or_kb_specific_property_value(Qcomputation_style,
		      Class_description_gkbprop);
	      if (gensymed_symbol_4) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
	      if (temp_1)
		  written_recorder_slot_name = 
			  Qmodules_this_computation_style_has_been_written_in;
	      else
		  written_recorder_slot_name = Qnil;
	  }
      }
      ab_loopvar__1 = lookup_kb_specific_property_value(class_1,
	      Instances_specific_to_this_class_kbprop);
      block = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1))
	  goto end_loop_1;
      block = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (referenced_recorder_slot_name_qm) {
	  temp = get_slot_value_function(block,
		  referenced_recorder_slot_name_qm,Nil);
	  set_slot_value_function(block,referenced_recorder_slot_name_qm,
		  Nil,Nil);
	  reclaim_slot_value(temp);
	  temp = get_slot_value_function(block,written_recorder_slot_name,Nil);
	  set_slot_value_function(block,written_recorder_slot_name,Nil,Nil);
	  reclaim_slot_value(temp);
      }
      else {
	  svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) &  
		  ~(SI_Long)8388608L;
	  ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	  svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) &  ~(SI_Long)2L;
	  ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
      }
      svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | (SI_Long)8L;
      ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
      gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
      if (gensymed_symbol) {
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
	  connection_structure = Nil;
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
	  next_loop_2:
	  next_loop_3:
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
		  next_loop_4:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_4;
		  end_loop_2:;
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
		    ab_connection_ && EQ(ISVREF(ab_connection_,
		    (SI_Long)3L),block))
		goto end_1;
	    goto next_loop_3;
	  end_loop_3:
	  end_1:
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_4;
	    connection_structure = ab_connection_;
	    svref_new_value = IFIX(ISVREF(connection_structure,
		    (SI_Long)7L)) &  ~(SI_Long)4L;
	    ISVREF(connection_structure,(SI_Long)7L) = FIX(svref_new_value);
	    svref_new_value = IFIX(ISVREF(connection_structure,
		    (SI_Long)7L)) | (SI_Long)8L;
	    ISVREF(connection_structure,(SI_Long)7L) = FIX(svref_new_value);
	    goto next_loop_2;
	  end_loop_4:;
	  POP_SPECIAL();
      }
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* BLOCK-REFERENCED-IN-CURRENT-SAVE-P */
Object block_referenced_in_current_save_p(block)
    Object block;
{
    Object class_1, gensymed_symbol, sub_class_bit_vector;
    Object referenced_recorder_slot_name_qm, gensymed_symbol_4, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(133,65);
    if (ISVREF(Current_kb_save,(SI_Long)37L)) {
	class_1 = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
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
	if (temp)
	    referenced_recorder_slot_name_qm = 
		    Qmodules_this_format_frame_has_been_referenced_in;
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qcomputation_style,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    if (temp)
		referenced_recorder_slot_name_qm = 
			Qmodules_this_computation_style_has_been_referenced_in;
	    else
		referenced_recorder_slot_name_qm = Qnil;
	}
    }
    else
	referenced_recorder_slot_name_qm = Nil;
    if (referenced_recorder_slot_name_qm) {
	gensymed_symbol = ISVREF(Current_kb_save,(SI_Long)37L);
	gensymed_symbol_4 = get_slot_value_function(block,
		referenced_recorder_slot_name_qm,Nil);
      next_loop:
	if ( !TRUEP(gensymed_symbol_4))
	    goto end_loop;
	if (EQ(M_CAR(gensymed_symbol_4),gensymed_symbol)) {
	    temp_1 = gensymed_symbol_4;
	    goto end_1;
	}
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)8388608L) ? T : Nil;
    return VALUES_1(temp_1);
}

/* SET-BLOCK-REFERENCED-IN-CURRENT-SAVE */
Object set_block_referenced_in_current_save(block,value)
    Object block, value;
{
    Object class_1, gensymed_symbol, sub_class_bit_vector;
    Object referenced_recorder_slot_name_qm, gensymed_symbol_4, old_slot_value;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(133,66);
    if (ISVREF(Current_kb_save,(SI_Long)37L)) {
	class_1 = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
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
	if (temp)
	    referenced_recorder_slot_name_qm = 
		    Qmodules_this_format_frame_has_been_referenced_in;
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qcomputation_style,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    if (temp)
		referenced_recorder_slot_name_qm = 
			Qmodules_this_computation_style_has_been_referenced_in;
	    else
		referenced_recorder_slot_name_qm = Qnil;
	}
    }
    else
	referenced_recorder_slot_name_qm = Nil;
    if (referenced_recorder_slot_name_qm) {
	old_slot_value = get_slot_value_function(block,
		referenced_recorder_slot_name_qm,Nil);
	if (value) {
	    gensymed_symbol = ISVREF(Current_kb_save,(SI_Long)37L);
	    gensymed_symbol_4 = old_slot_value;
	  next_loop:
	    if ( !TRUEP(gensymed_symbol_4))
		goto end_loop;
	    if (EQ(M_CAR(gensymed_symbol_4),gensymed_symbol)) {
		temp = TRUEP(gensymed_symbol_4);
		goto end_1;
	    }
	    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(Qnil);
	  end_1:;
	    temp_1 = temp ? old_slot_value : 
		    slot_value_cons_1(ISVREF(Current_kb_save,(SI_Long)37L),
		    old_slot_value);
	}
	else
	    temp_1 = delete_slot_value_element_1(ISVREF(Current_kb_save,
		    (SI_Long)37L),old_slot_value);
	set_slot_value_function(block,referenced_recorder_slot_name_qm,
		temp_1,Nil);
	temp_1 = value;
    }
    else {
	if (value) {
	    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | 
		    (SI_Long)8388608L;
	    ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	}
	else {
	    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) &  
		    ~(SI_Long)8388608L;
	    ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	}
	temp_1 = value;
    }
    return VALUES_1(temp_1);
}

/* BLOCK-WRITTEN-IN-CURRENT-SAVE-P */
Object block_written_in_current_save_p(block)
    Object block;
{
    Object class_1, gensymed_symbol, sub_class_bit_vector;
    Object written_recorder_slot_name_qm, gensymed_symbol_4, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(133,67);
    if (ISVREF(Current_kb_save,(SI_Long)37L)) {
	class_1 = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
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
	if (temp)
	    written_recorder_slot_name_qm = 
		    Qmodules_this_format_frame_has_been_written_in;
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qcomputation_style,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    if (temp)
		written_recorder_slot_name_qm = 
			Qmodules_this_computation_style_has_been_written_in;
	    else
		written_recorder_slot_name_qm = Qnil;
	}
    }
    else
	written_recorder_slot_name_qm = Nil;
    if (written_recorder_slot_name_qm) {
	gensymed_symbol = ISVREF(Current_kb_save,(SI_Long)37L);
	gensymed_symbol_4 = get_slot_value_function(block,
		written_recorder_slot_name_qm,Nil);
      next_loop:
	if ( !TRUEP(gensymed_symbol_4))
	    goto end_loop;
	if (EQ(M_CAR(gensymed_symbol_4),gensymed_symbol)) {
	    temp = TRUEP(gensymed_symbol_4);
	    goto end_1;
	}
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	temp_1 = temp ? T : Nil;
    }
    else
	temp_1 = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)2L) ? T : Nil;
    return VALUES_1(temp_1);
}

/* SET-BLOCK-WRITTEN-IN-CURRENT-SAVE */
Object set_block_written_in_current_save(block,value)
    Object block, value;
{
    Object class_1, gensymed_symbol, sub_class_bit_vector;
    Object written_recorder_slot_name_qm, gensymed_symbol_4, old_slot_value;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(133,68);
    if (ISVREF(Current_kb_save,(SI_Long)37L)) {
	class_1 = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
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
	if (temp)
	    written_recorder_slot_name_qm = 
		    Qmodules_this_format_frame_has_been_written_in;
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qcomputation_style,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    if (temp)
		written_recorder_slot_name_qm = 
			Qmodules_this_computation_style_has_been_written_in;
	    else
		written_recorder_slot_name_qm = Qnil;
	}
    }
    else
	written_recorder_slot_name_qm = Nil;
    if (written_recorder_slot_name_qm) {
	old_slot_value = get_slot_value_function(block,
		written_recorder_slot_name_qm,Nil);
	if (value) {
	    gensymed_symbol = ISVREF(Current_kb_save,(SI_Long)37L);
	    gensymed_symbol_4 = old_slot_value;
	  next_loop:
	    if ( !TRUEP(gensymed_symbol_4))
		goto end_loop;
	    if (EQ(M_CAR(gensymed_symbol_4),gensymed_symbol)) {
		temp = TRUEP(gensymed_symbol_4);
		goto end_1;
	    }
	    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(Qnil);
	  end_1:;
	    temp_1 = temp ? old_slot_value : 
		    slot_value_cons_1(ISVREF(Current_kb_save,(SI_Long)37L),
		    old_slot_value);
	}
	else
	    temp_1 = delete_slot_value_element_1(ISVREF(Current_kb_save,
		    (SI_Long)37L),old_slot_value);
	set_slot_value_function(block,written_recorder_slot_name_qm,temp_1,
		Nil);
	temp_1 = value;
    }
    else {
	if (value) {
	    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | (SI_Long)2L;
	    ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	}
	else {
	    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) &  ~(SI_Long)2L;
	    ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	}
	temp_1 = value;
    }
    return VALUES_1(temp_1);
}

/* INCREMENT-FRAME-REFERENCE-BALANCE */
Object increment_frame_reference_balance(frame,calling_function)
    Object frame, calling_function;
{
    Object svref_arg_1, svref_new_value, tree, gensymed_symbol, fsn;

    x_note_fn_call(133,69);
    svref_arg_1 = Current_kb_save;
    svref_new_value = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)32L));
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = svref_new_value;
    if (Debug_frame_reference_balance_qm) {
	tree = ISVREF(Current_kb_save,(SI_Long)33L);
	if ((SI_Long)1L > (SI_Long)0L) {
	    gensymed_symbol = frame;
	    fsn = ISVREF(gensymed_symbol,(SI_Long)3L);
	    set_balanced_binary_tree_entry(tree,Qeq,Nil,T,gensymed_symbol,
		    FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),
		    M_CDR(fsn)),calling_function);
	}
	else {
	    fsn = ISVREF(frame,(SI_Long)3L);
	    delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),frame,
		    tree,FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),
		    M_CDR(fsn)));
	}
    }
    return VALUES_1(Nil);
}

/* DECREMENT-FRAME-REFERENCE-BALANCE */
Object decrement_frame_reference_balance(frame,calling_function)
    Object frame, calling_function;
{
    Object svref_arg_1, svref_new_value, tree, gensymed_symbol, fsn;

    x_note_fn_call(133,70);
    svref_arg_1 = Current_kb_save;
    svref_new_value = FIXNUM_SUB1(ISVREF(svref_arg_1,(SI_Long)32L));
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = svref_new_value;
    if (Debug_frame_reference_balance_qm) {
	tree = ISVREF(Current_kb_save,(SI_Long)33L);
	if ((SI_Long)-1L > (SI_Long)0L) {
	    gensymed_symbol = frame;
	    fsn = ISVREF(gensymed_symbol,(SI_Long)3L);
	    set_balanced_binary_tree_entry(tree,Qeq,Nil,T,gensymed_symbol,
		    FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),
		    M_CDR(fsn)),calling_function);
	}
	else {
	    fsn = ISVREF(frame,(SI_Long)3L);
	    delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),frame,
		    tree,FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),
		    M_CDR(fsn)));
	}
    }
    return VALUES_1(Nil);
}

/* CLIP-TRANSIENTS-FROM-CONNECTIONS */
Object clip_transients_from_connections(connections)
    Object connections;
{
    Object connection_or_symbol, symbols_and_connection, clipped_list;
    Object clipped_list_tail, new_tail, list_to_add, temp;

    x_note_fn_call(133,71);
    connection_or_symbol = Nil;
    symbols_and_connection = Nil;
    clipped_list = Nil;
    clipped_list_tail = Nil;
  next_loop:
    if ( !TRUEP(connections))
	goto end_loop;
    connection_or_symbol = FIRST(connections);
    if (SYMBOLP(connection_or_symbol))
	symbols_and_connection = nconc2(symbols_and_connection,
		gensym_cons_1(connection_or_symbol,Nil));
    else if ( !((SI_Long)0L != (IFIX(ISVREF(connection_or_symbol,
	    (SI_Long)7L)) & (SI_Long)64L))) {
	new_tail = gensym_cons_1(connection_or_symbol,Nil);
	list_to_add = nconc2(symbols_and_connection,new_tail);
	if ( !TRUEP(clipped_list)) {
	    clipped_list = list_to_add;
	    clipped_list_tail = new_tail;
	}
	else {
	    M_CDR(clipped_list_tail) = list_to_add;
	    clipped_list_tail = new_tail;
	}
	symbols_and_connection = Nil;
    }
    else {
	reclaim_gensym_list_1(symbols_and_connection);
	symbols_and_connection = Nil;
    }
    connections = CDR(connections);
    goto next_loop;
  end_loop:
    temp = clipped_list;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object list_constant_1;     /* # */

static Object string_constant_3;   /* "~a~~" */

/* CHECKPOINT-FILE-IF-NECESSARY */
Object checkpoint_file_if_necessary(convertible_thing)
    Object convertible_thing;
{
    volatile Object truename_qm;
    volatile Object namestring_1;
    volatile Object new_name_for_existing_file;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(133,72);
    SAVE_STACK();
    truename_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(1)) {
	truename_qm = gensym_probe_file(convertible_thing);
	if (truename_qm && memq_function(ISVREF(truename_qm,(SI_Long)8L),
		list_constant_1)) {
	    namestring_1 = Qunbound_in_protected_let;
	    new_name_for_existing_file = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		namestring_1 = gensym_namestring(1,convertible_thing);
		new_name_for_existing_file = tformat_text_string(2,
			string_constant_3,namestring_1);
		gensym_rename_file_indifferent_to_return_values(namestring_1,
			new_name_for_existing_file);
		SAVE_VALUES(VALUES_1(T));
	    }
	    POP_UNWIND_PROTECT(0);
	    if (new_name_for_existing_file) {
		if ( !EQ(new_name_for_existing_file,Qunbound_in_protected_let))
		    reclaim_text_string(new_name_for_existing_file);
	    }
	    if (namestring_1) {
		if ( !EQ(namestring_1,Qunbound_in_protected_let))
		    reclaim_text_string(namestring_1);
	    }
	    CONTINUE_UNWINDING(0);
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(1);
    if (truename_qm) {
	if ( !EQ(truename_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(truename_qm);
    }
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Saving_parameters, Qsaving_parameters);

static Object Qidentifier_of_basis_kb;  /* identifier-of-basis-kb */

static Object Qfilename_of_basis_kb;  /* filename-of-basis-kb */

static Object Qkb_file_comment;    /* kb-file-comment */

/* MAKE-OR-CLEAR-COMPLETE-KB-NAME */
Object make_or_clear_complete_kb_name varargs_1(int, n)
{
    Object complete_kb_name_or_kb_name_qm, complete_as_is_qm;
    Object module_qm, kb_file_comment_qm, saving_parameters_instance_qm;
    Object do_not_note_permanent_changes_p, temp, temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(133,73);
    INIT_ARGS_nonrelocating();
    complete_kb_name_or_kb_name_qm = REQUIRED_ARG_nonrelocating();
    complete_as_is_qm = REQUIRED_ARG_nonrelocating();
    module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    kb_file_comment_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Complete_kb_name_qm)
	reclaim_text_string(Complete_kb_name_qm);
    Complete_kb_name_qm = complete_kb_name_or_kb_name_qm ? 
	    (complete_as_is_qm ? 
	    copy_text_string(complete_kb_name_or_kb_name_qm) : 
	    make_complete_kb_name(complete_kb_name_or_kb_name_qm)) : Nil;
    saving_parameters_instance_qm = module_qm ? 
	    get_system_table_of_class_for_module_or_nil(module_qm,
	    Qsaving_parameters) : Saving_parameters;
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      if (saving_parameters_instance_qm) {
	  temp = Saving_parameters;
	  change_slot_value(3,temp,Qidentifier_of_basis_kb,
		  Complete_kb_name_qm ? 
		  copy_text_string(Complete_kb_name_qm) : Nil);
	  temp = Saving_parameters;
	  change_slot_value(3,temp,Qfilename_of_basis_kb,
		  Current_kb_pathname_qm ? (Complete_kb_name_qm ? 
		  gensym_namestring(1,Current_kb_pathname_qm) : Nil) : Nil);
	  if (kb_file_comment_qm) {
	      temp = Saving_parameters;
	      temp_1 = No_value;
	      change_slot_value(3,temp,Qkb_file_comment,
		      slot_value_cons_1(temp_1,
		      convert_text_string_to_text(kb_file_comment_qm)));
	  }
      }
    POP_SPECIAL();
    return VALUES_1(Complete_kb_name_qm);
}

static Object string_constant_4;   /* "~a ~a " */

/* MAKE-COMPLETE-KB-NAME */
Object make_complete_kb_name(kb_name)
    Object kb_name;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, success_qm, text_string_result, temp_1, temp_2, maximum_index;
    Object local_machine_id, second_1, minute, hour, date, month, year;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    Declare_special(5);
    Object result;

    x_note_fn_call(133,74);
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
	      temp = obtain_simple_gensym_string(Size_of_local_machine_id);
	      success_qm = Nil;
	      text_string_result = Nil;
	      temp_1 = CHR('\000');
	      SET_SCHAR(temp,FIX((SI_Long)0L),temp_1);
	      success_qm = IFIX(c_nsleep(temp)) >= (SI_Long)0L ? T : Nil;
	      temp_1 = copy_text_string(temp);
	      reclaim_simple_gensym_string(temp);
	      text_string_result = temp_1;
	      if (!success_qm) {
		  if (!shunned_machine_id_string_p(text_string_result)) {
		      UBYTE_16_ISASET_1(text_string_result,(SI_Long)0L,
			      (SI_Long)69L);
		      UBYTE_16_ISASET_1(text_string_result,(SI_Long)1L,
			      (SI_Long)82L);
		      UBYTE_16_ISASET_1(text_string_result,(SI_Long)2L,
			      (SI_Long)82L);
		      UBYTE_16_ISASET_1(text_string_result,(SI_Long)3L,
			      (SI_Long)79L);
		      UBYTE_16_ISASET_1(text_string_result,(SI_Long)4L,
			      (SI_Long)82L);
		      UBYTE_16_ISASET_1(text_string_result,(SI_Long)5L,
			      (SI_Long)0L);
		  }
	      }
	      temp_2 = text_string_result;
	      maximum_index = 
		      FIXNUM_SUB1(text_string_length(text_string_result));
	      i = (SI_Long)0L;
	    next_loop:
	      if (UBYTE_16_ISAREF_1(text_string_result,i) == (SI_Long)0L) {
		  temp_1 = FIX(i);
		  goto end_1;
	      }
	      if (i >= IFIX(maximum_index)) {
		  temp_1 = FIX(i + (SI_Long)1L);
		  goto end_1;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      temp_1 = Qnil;
	    end_1:;
	      temp_1 = text_string_substring(temp_2,FIX((SI_Long)0L),temp_1);
	      reclaim_text_string(text_string_result);
	      local_machine_id = temp_1;
	      tformat(3,string_constant_4,kb_name,local_machine_id);
	      reclaim_text_string(local_machine_id);
	      result = get_decoded_real_time();
	      MVS_6(result,second_1,minute,hour,date,month,year);
	      print_decoded_time(second_1,minute,hour,date,month,year);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COPY-COLLECTABLE-BLOCKS */
Object copy_collectable_blocks(list_1)
    Object list_1;
{
    Object block, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(133,75);
    block = Nil;
    ab_loop_list_ = list_1;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L) || 
	    ISVREF(Current_saving_context,(SI_Long)3L) && (SI_Long)0L != 
	    (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)262144L)) {
	ab_loopvar__2 = gensym_cons_1(block,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* COPY-COLLECTABLE-BLOCKS-FOR-SUBBLOCKS */
Object copy_collectable_blocks_for_subblocks(list_1)
    Object list_1;
{
    Object queue, next_queue_element, block, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(133,76);
    if (list_1) {
	queue = list_1;
	next_queue_element = Nil;
	block = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),
		queue);
      next_loop:
	if ( !TRUEP(next_queue_element))
	    goto end_loop;
	block = ISVREF(next_queue_element,(SI_Long)4L);
	next_queue_element = constant_queue_next(next_queue_element,queue);
	if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L) 
		|| ISVREF(Current_saving_context,(SI_Long)3L) && 
		(SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)262144L)) {
	    ab_loopvar__2 = gensym_cons_1(block,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COPY-COLLECTABLE-BLOCKS-WITHIN-MODULE */
Object copy_collectable_blocks_within_module(list_1,module)
    Object list_1, module;
{
    Object block, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(133,77);
    block = Nil;
    ab_loop_list_ = list_1;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L) || 
	    ISVREF(Current_saving_context,(SI_Long)3L) && (SI_Long)0L != 
	    (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)262144L)) && 
	    EQ(get_module_block_is_in(block),module)) {
	ab_loopvar__2 = gensym_cons_1(block,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qrelation_is_permanent;  /* relation-is-permanent */

/* CONVERT-INTERMODUAL-RELATION-INSTANCES-FOR-SAVING */
Object convert_intermodual_relation_instances_for_saving(block,
	    relation_instances)
    Object block, relation_instances;
{
    Object converted_value_qm, block_module_qm, block_denotation_qm;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance, relation_frame;
    Object object_class_references_for_saving_qm, ab_less_than_branch_qm_;
    Object ab_node_stack__1, ab_current_node__1, ab_skip_list_p__1;
    Object ab_next_node__1, ab_tail_node__1, ab_current_alist__1;
    Object ab_entry_cons__1, object_frame, object_frame_module_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, object_frame_denotation_qm, temp_2;
    Object temp_3;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(133,78);
    converted_value_qm = Nil;
    block_module_qm = ISVREF(Current_kb_save,(SI_Long)37L);
    block_denotation_qm = 
	    copy_for_slot_value(get_primary_name_for_frame_if_any(block));
    if (block_denotation_qm);
    else
	block_denotation_qm = item_uuid(block);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_skip_list_form_ = relation_instances;
    ab_binary_tree_form_ = relation_instances;
    gensymed_symbol = CDR(relation_instances);
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
    relation_instance = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      relation_frame = Nil;
      object_class_references_for_saving_qm = Nil;
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
		      (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_1:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
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
      relation_instance = M_CDR(ab_entry_cons_);
      relation_frame = ISVREF(relation_instance,(SI_Long)1L);
      if ( !((SI_Long)0L != (IFIX(ISVREF(relation_frame,(SI_Long)5L)) & 
	      (SI_Long)262144L)) && get_lookup_slot_value(relation_frame,
	      Qrelation_is_permanent)) {
	  scope_conses = Scope_conses;
	  ab_node_stack__1 = Nil;
	  ab_current_node__1 = Nil;
	  ab_skip_list_form_ = ISVREF(relation_instance,(SI_Long)2L);
	  ab_binary_tree_form_ = ISVREF(relation_instance,(SI_Long)2L);
	  temp = ISVREF(relation_instance,(SI_Long)2L);
	  gensymed_symbol = CDR(temp);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p__1 = Nil;
	  ab_next_node__1 = Nil;
	  ab_tail_node__1 = Nil;
	  ab_current_alist__1 = Nil;
	  ab_entry_cons__1 = Nil;
	  object_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    object_frame_module_qm = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    if (ab_skip_list_p__1) {
		ab_next_node__1 = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node__1 = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node__1,ab_tail_node__1))
		    ab_next_node__1 = Nil;
	    }
	    else
		ab_next_node__1 = M_CDR(ab_binary_tree_form_);
	  next_loop_2:
	    if (ab_current_alist__1) {
		ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		ab_current_alist__1 = M_CDR(ab_current_alist__1);
	    }
	    else if (ab_skip_list_p__1) {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_next_node__1 = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__1,
			    (SI_Long)0L),(SI_Long)0L));
		    if (EQ(ab_next_node__1,ab_tail_node__1))
			ab_next_node__1 = Nil;
		    ab_entry_cons__1 = 
			    scope_cons(ISVREF(ab_current_node__1,
			    (SI_Long)2L),ISVREF(ab_current_node__1,
			    (SI_Long)3L));
		}
		else
		    ab_current_node__1 = Nil;
	    }
	    else {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node__1,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack__1 = scope_cons(ab_current_node__1,
			    ab_node_stack__1);
		    ab_current_node__1 = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
		}
		else if (ab_node_stack__1) {
		    ab_next_node__1 = ab_node_stack__1;
		    ab_current_node__1 = M_CAR(ab_node_stack__1);
		    ab_node_stack__1 = M_CDR(ab_node_stack__1);
		}
		else
		    ab_current_node__1 = Nil;
		if (ab_current_node__1) {
		    ab_next_node__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_current_alist__1 = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		    ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		    ab_current_alist__1 = M_CDR(ab_current_alist__1);
		}
	    }
	    if ( !TRUEP(ab_current_node__1))
		goto end_loop_3;
	    object_frame = M_CDR(ab_entry_cons__1);
	    object_frame_module_qm = object_frame ? 
		    get_module_block_is_in(object_frame) : Nil;
	    if (object_frame) {
		if ( !((SI_Long)0L != (IFIX(ISVREF(object_frame,
			(SI_Long)5L)) & (SI_Long)262144L) ||  
			!((SI_Long)0L != (IFIX(ISVREF(object_frame,
			(SI_Long)5L)) & (SI_Long)262144L)) &&  
			!((SI_Long)0L != (IFIX(ISVREF(object_frame,
			(SI_Long)4L)) & (SI_Long)1L)))) {
		    if (EQ(block_module_qm,object_frame_module_qm) ||  
			    !TRUEP(block_module_qm))
			ab_loopvar__2 = slot_value_cons_1(object_frame,Nil);
		    else {
			object_frame_denotation_qm = 
				copy_for_slot_value(get_primary_name_for_frame_if_any(object_frame));
			if (object_frame_denotation_qm);
			else
			    object_frame_denotation_qm = 
				    item_uuid(object_frame);
			ab_loopvar__2 = block_denotation_qm && 
				object_frame_denotation_qm ? 
				slot_value_cons_1(object_frame_denotation_qm,
				Nil) : Nil;
		    }
		}
		else
		    ab_loopvar__2 = Nil;
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
	    }
	    goto next_loop_2;
	  end_loop_3:
	    object_class_references_for_saving_qm = ab_loopvar_;
	    goto end_1;
	    object_class_references_for_saving_qm = Qnil;
	  end_1:;
	  POP_SPECIAL();
      }
      else
	  object_class_references_for_saving_qm = Nil;
      temp_2 = converted_value_qm;
      if (object_class_references_for_saving_qm) {
	  temp_3 = ISVREF(relation_instance,(SI_Long)0L);
	  if (EQ(block_module_qm,get_module_block_is_in(relation_frame)))
	      temp = relation_frame;
	  else {
	      temp = 
		      copy_for_slot_value(get_primary_name_for_frame_if_any(relation_frame));
	      if (temp);
	      else
		  temp = item_uuid(relation_frame);
	  }
	  temp = slot_value_cons_1(nconc2(slot_value_list_2(temp_3,temp),
		  object_class_references_for_saving_qm),Nil);
      }
      else
	  temp = Nil;
      converted_value_qm = nconc2(temp_2,temp);
      goto next_loop;
    end_loop_1:
      reclaim_slot_value(block_denotation_qm);
    POP_SPECIAL();
    return VALUES_1(converted_value_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Frame_for_write_frame_for_kb, Qframe_for_write_frame_for_kb);

DEFINE_VARIABLE_WITH_SYMBOL(Slot_name_for_write_frame_for_kb, Qslot_name_for_write_frame_for_kb);

DEFINE_VARIABLE_WITH_SYMBOL(Slot_value_for_write_frame_for_kb, Qslot_value_for_write_frame_for_kb);

static Object Qwrite_frame_for_kb;  /* write-frame-for-kb */

static Object Qruntime_data_only;  /* runtime-data-only */

static Object Qframe_flags;        /* frame-flags */

static Object Qsubworkspaces;      /* subworkspaces */

static Object Qframe_representations;  /* frame-representations */

static Object Qicon_attributes_plist;  /* icon-attributes-plist */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Quuid;               /* uuid */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qrelation_instances;  /* relation-instances */

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

static Object Qab_structure;       /* structure */

static Object Qentangled_slots;    /* entangled-slots */

static Object Qoriginal_kb_state_plist;  /* original-kb-state-plist */

static Object Qlist_structure;     /* list-structure */

static Object Qmanaged_g2_array;   /* managed-g2-array */

/* WRITE-FRAME-FOR-KB */
Object write_frame_for_kb varargs_1(int, n)
{
    Object frame, block_qm;
    Object as_ghost_qm, frame_for_write_frame_for_kb, class_1;
    Object class_description, sub_class_bit_vector;
    Object include_initializations_for_all_slots_qm;
    Object last_thing_written_was_long_qm, frame_is_a_class_definition_qm;
    Object slot_descriptions, gensymed_symbol_3, gensymed_symbol_4;
    Object slot_description, frame_flags, ab_loop_list_, slot_name;
    Object slot_name_for_write_frame_for_kb, possibly_transient_slot_value;
    Object slot_value, entangled_slot_on_definition_qm, x2, temp_1;
    Object slot_features, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object temp_2, slot_value_to_save_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(133,79);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    block_qm = REQUIRED_ARG_nonrelocating();
    as_ghost_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    frame_for_write_frame_for_kb = frame;
    PUSH_SPECIAL_WITH_SYMBOL(Frame_for_write_frame_for_kb,Qframe_for_write_frame_for_kb,frame_for_write_frame_for_kb,
	    1);
      class_1 = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
      class_description = ISVREF(frame,(SI_Long)1L);
      sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
      sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
      if (sub_class_vector_index < 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	  gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		  sub_class_vector_index);
	  gensymed_symbol_1 = (SI_Long)1L;
	  gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	  gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	  gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	  include_initializations_for_all_slots_qm = (SI_Long)0L < 
		  gensymed_symbol ? T : Nil;
      }
      else
	  include_initializations_for_all_slots_qm = Nil;
      last_thing_written_was_long_qm = Nil;
      sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
      sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
      if (sub_class_vector_index < 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	  gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		  sub_class_vector_index);
	  gensymed_symbol_1 = (SI_Long)1L;
	  gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	  gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	  gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	  frame_is_a_class_definition_qm = (SI_Long)0L < gensymed_symbol ? 
		  T : Nil;
      }
      else
	  frame_is_a_class_definition_qm = Nil;
      slot_descriptions = ISVREF(class_description,(SI_Long)6L);
      gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)55L),(SI_Long)1L);
      gensymed_symbol_4 = frame;
      inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4);
      start_new_kb_line();
      write_char_for_kb(block_qm ? CHR('F') : CHR('Y'));
      if (block_qm) {
	  if (block_referenced_in_current_save_p(frame))
	      decrement_frame_reference_balance(frame,Qwrite_frame_for_kb);
	  write_frame_serial_number_for_kb(ISVREF(frame,(SI_Long)3L));
      }
      write_symbol_for_kb(class_1,T);
      if ( !TRUEP(block_qm) ||  !EQ(ISVREF(Current_saving_context_qm,
	      (SI_Long)2L),Qruntime_data_only) || (SI_Long)0L != 
	      (IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)262144L)) {
	  if (block_qm) {
	      slot_description = 
		      get_slot_description_of_class_description_function(Qframe_flags,
		      class_description,Nil);
	      frame_flags = ISVREF(frame,(SI_Long)4L);
	      if ( !EQ(frame_flags,ISVREF(slot_description,(SI_Long)6L)))
		  write_slot_for_kb(5,frame,slot_description,frame_flags,
			  as_ghost_qm,last_thing_written_was_long_qm);
	  }
	  slot_description = Nil;
	  ab_loop_list_ = slot_descriptions;
	  slot_name = Nil;
	  slot_name_for_write_frame_for_kb = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Slot_name_for_write_frame_for_kb,Qslot_name_for_write_frame_for_kb,slot_name_for_write_frame_for_kb,
		  0);
	    possibly_transient_slot_value = Nil;
	    slot_value = Nil;
	    entangled_slot_on_definition_qm = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    slot_description = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    slot_name = ISVREF(slot_description,(SI_Long)2L);
	    Slot_name_for_write_frame_for_kb = slot_name;
	    if (as_ghost_qm && (EQ(slot_name,Qsubworkspaces) || 
		    EQ(slot_name,Qframe_representations) || EQ(slot_name,
		    Qicon_attributes_plist)))
		possibly_transient_slot_value = Nil;
	    else if (EQ(class_1,Qmodule_information) && EQ(slot_name,
		    Qframe_status_and_notes))
		possibly_transient_slot_value = Nil;
	    else if (EQ(slot_name,Quuid))
		possibly_transient_slot_value = item_uuid(frame);
	    else
		possibly_transient_slot_value = 
			get_slot_description_value(frame,slot_description);
	    if (SIMPLE_VECTOR_P(possibly_transient_slot_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(possibly_transient_slot_value)) 
		    > (SI_Long)2L &&  
		    !EQ(ISVREF(possibly_transient_slot_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(possibly_transient_slot_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = 
			ISVREF(ISVREF(possibly_transient_slot_value,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
	    slot_value = ((temp ? (SI_Long)0L != 
		    (IFIX(ISVREF(possibly_transient_slot_value,
		    (SI_Long)5L)) & (SI_Long)262144L) : TRUEP(Nil)) ?  
		    !TRUEP(ISVREF(Current_saving_context,(SI_Long)3L)) : 
		    TRUEP(Nil)) ? Nil : possibly_transient_slot_value;
	    if (frame_is_a_class_definition_qm && slot_value) {
		temp_1 = EQ(slot_name,Qrelation_instances) ? T : Nil;
		if (temp_1);
		else
		    temp_1 = EQ(slot_name,Qsubworkspaces) ? T : Nil;
		if (temp_1);
		else {
		    slot_features = ISVREF(slot_description,(SI_Long)9L);
		    if (assq_function(Qtype,slot_features) ?  
			    !TRUEP(assq_function(Qdo_not_save,
			    slot_features)) : TRUEP(assq_function(Qsave,
			    slot_features))) {
			if (SIMPLE_VECTOR_P(slot_value) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) 
				> (SI_Long)2L &&  !EQ(ISVREF(slot_value,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(slot_value,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? x2 : Qnil;
			}
			else
			    temp_1 = Nil;
			if (temp_1);
			else
			    temp_1 = CONSP(slot_value) ? 
				    (EQ(M_CDR(slot_value),Qsequence) ? T : 
				    Nil) : Qnil;
			if (temp_1);
			else
			    temp_1 = CONSP(slot_value) ? 
				    (EQ(M_CDR(slot_value),Qab_structure) ? 
				    T : Nil) : Qnil;
		    }
		    else
			temp_1 = Nil;
		}
		entangled_slot_on_definition_qm = temp_1;
	    }
	    else
		entangled_slot_on_definition_qm = Nil;
	    if (entangled_slot_on_definition_qm) {
		slot_value_push_modify_macro_arg = ISVREF(slot_description,
			(SI_Long)1L);
		car_1 = slot_value_push_modify_macro_arg;
		cdr_1 = get_lookup_slot_value_given_default(frame,
			Qentangled_slots,Nil);
		temp_2 = slot_value_cons_1(car_1,cdr_1);
		set_non_savable_lookup_slot_value(frame,Qentangled_slots,
			temp_2);
	    }
	    if ( !EQ(slot_value,ISVREF(slot_description,(SI_Long)6L)) || 
		    include_initializations_for_all_slots_qm) {
		slot_features = ISVREF(slot_description,(SI_Long)9L);
		temp = assq_function(Qtype,slot_features) ?  
			!TRUEP(assq_function(Qdo_not_save,slot_features)) :
			 TRUEP(assq_function(Qsave,slot_features));
		if (temp);
		else
		    temp = EQ(slot_name,Qoriginal_kb_state_plist);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ?  !TRUEP(Ok_file_saving_mode_qm) ||  
		    !TRUEP(memq_function(slot_name,
		    Slots_to_skip_saving_in_ok_files)) : TRUEP(Nil)) {
		temp =  !TRUEP(entangled_slot_on_definition_qm);
		if (temp);
		else if ( !TRUEP(ISVREF(Current_saving_context,
			(SI_Long)3L)) || EQ(slot_name,Qrelation_instances)) {
		    temp = TRUEP(ISVREF(Current_kb_save,(SI_Long)31L));
		    if (temp);
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Definition_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
		    }
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (EQ(slot_name,Qrelation_instances) && slot_value || 
			EQ(slot_name,Qlist_structure) || EQ(slot_name,
			Qmanaged_g2_array)) {
		    if (EQ(slot_name,Qrelation_instances))
			slot_value_to_save_qm = 
				convert_intermodual_relation_instances_for_saving(frame,
				slot_value);
		    else if (EQ(slot_name,Qlist_structure))
			slot_value_to_save_qm = 
				convert_permanent_list_structure_for_saving(frame);
		    else if (EQ(slot_name,Qmanaged_g2_array))
			slot_value_to_save_qm = 
				convert_permanent_array_structure_for_saving(frame);
		    else
			slot_value_to_save_qm = Qnil;
		    if (slot_value_to_save_qm) {
			last_thing_written_was_long_qm = 
				write_slot_for_kb(5,frame,slot_description,
				slot_value_to_save_qm,as_ghost_qm,
				last_thing_written_was_long_qm);
			reclaim_slot_value(slot_value_to_save_qm);
		    }
		}
		else
		    last_thing_written_was_long_qm = write_slot_for_kb(5,
			    frame,slot_description,slot_value,as_ghost_qm,
			    last_thing_written_was_long_qm);
		if (EQ(slot_name,Quuid))
		    reclaim_text_string(slot_value);
		if (EQ(slot_name,Qoriginal_kb_state_plist)) {
		    temp_2 = Current_kb_save;
		    SVREF(temp_2,FIX((SI_Long)35L)) = T;
		}
	    }
	    goto next_loop;
	  end_loop:;
	  POP_SPECIAL();
      }
      if (block_qm && ISVREF(Current_saving_context,(SI_Long)3L))
	  write_runtime_data_for_kb(frame,class_1);
      write_char_for_kb(CHR('!'));
      gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)56L),(SI_Long)1L);
      gensymed_symbol_4 = frame;
      result = inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4);
    POP_SPECIAL();
    return result;
}

Object The_type_description_of_pseudo_frame = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_pseudo_frames, Qchain_of_available_pseudo_frames);

DEFINE_VARIABLE_WITH_SYMBOL(Pseudo_frame_count, Qpseudo_frame_count);

Object Chain_of_available_pseudo_frames_vector = UNBOUND;

/* PSEUDO-FRAME-STRUCTURE-MEMORY-USAGE */
Object pseudo_frame_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(133,80);
    temp = Pseudo_frame_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PSEUDO-FRAME-COUNT */
Object outstanding_pseudo_frame_count()
{
    Object def_structure_pseudo_frame_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(133,81);
    gensymed_symbol = IFIX(Pseudo_frame_count);
    def_structure_pseudo_frame_variable = Chain_of_available_pseudo_frames;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_pseudo_frame_variable))
	goto end_loop;
    def_structure_pseudo_frame_variable = 
	    ISVREF(def_structure_pseudo_frame_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PSEUDO-FRAME-1 */
Object reclaim_pseudo_frame_1(pseudo_frame)
    Object pseudo_frame;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(133,82);
    inline_note_reclaim_cons(pseudo_frame,Nil);
    structure_being_reclaimed = pseudo_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(pseudo_frame,(SI_Long)2L));
      SVREF(pseudo_frame,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_pseudo_frames_vector,
	    IFIX(Current_thread_index));
    SVREF(pseudo_frame,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_pseudo_frames_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = pseudo_frame;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PSEUDO-FRAME */
Object reclaim_structure_for_pseudo_frame(pseudo_frame)
    Object pseudo_frame;
{
    x_note_fn_call(133,83);
    return reclaim_pseudo_frame_1(pseudo_frame);
}

static Object Qg2_defstruct_structure_name_pseudo_frame_g2_struct;  /* g2-defstruct-structure-name::pseudo-frame-g2-struct */

/* MAKE-PERMANENT-PSEUDO-FRAME-STRUCTURE-INTERNAL */
Object make_permanent_pseudo_frame_structure_internal()
{
    Object def_structure_pseudo_frame_variable;
    Object defstruct_g2_pseudo_frame_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(133,84);
    def_structure_pseudo_frame_variable = Nil;
    atomic_incff_symval(Qpseudo_frame_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_pseudo_frame_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_pseudo_frame_variable = the_array;
	SVREF(defstruct_g2_pseudo_frame_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pseudo_frame_g2_struct;
	def_structure_pseudo_frame_variable = 
		defstruct_g2_pseudo_frame_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_pseudo_frame_variable);
}

/* MAKE-PSEUDO-FRAME-1 */
Object make_pseudo_frame_1(pseudo_frame_item,pseudo_frame_frame_serial_number)
    Object pseudo_frame_item, pseudo_frame_frame_serial_number;
{
    Object def_structure_pseudo_frame_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(133,85);
    def_structure_pseudo_frame_variable = 
	    ISVREF(Chain_of_available_pseudo_frames_vector,
	    IFIX(Current_thread_index));
    if (def_structure_pseudo_frame_variable) {
	svref_arg_1 = Chain_of_available_pseudo_frames_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_pseudo_frame_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_pseudo_frame_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pseudo_frame_g2_struct;
    }
    else
	def_structure_pseudo_frame_variable = 
		make_permanent_pseudo_frame_structure_internal();
    inline_note_allocate_cons(def_structure_pseudo_frame_variable,Nil);
    SVREF(def_structure_pseudo_frame_variable,FIX((SI_Long)1L)) = 
	    pseudo_frame_item;
    SVREF(def_structure_pseudo_frame_variable,FIX((SI_Long)2L)) = 
	    pseudo_frame_frame_serial_number;
    return VALUES_1(def_structure_pseudo_frame_variable);
}

/* HAS-SLOT-VALUES-TO-SAVE-P */
Object has_slot_values_to_save_p varargs_1(int, n)
{
    Object frame;
    Object names_of_slots_to_disregard, class_description, slot_descriptions;
    Object temp, gensymed_symbol, slot_description, ab_loop_list_;
    Object slot_init_form, slot_value, ab_loop_it_, vector_slot_index_qm;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm, slot_features;
    SI_Long max_i, i, ab_loop_bind_;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(133,86);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    names_of_slots_to_disregard = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    class_description = ISVREF(frame,(SI_Long)1L);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    temp = ISVREF(Current_saving_context,(SI_Long)3L) ? T : Nil;
    if (temp);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	temp = gensymed_symbol;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	slot_description = Nil;
	ab_loop_list_ = slot_descriptions;
	slot_init_form = Nil;
	slot_value = Nil;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	slot_init_form = ISVREF(slot_description,(SI_Long)6L);
	vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	if (vector_slot_index_qm)
	    slot_value = ISVREF(frame,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	    if (user_vector_slot_index_qm)
		slot_value = ISVREF(ISVREF(frame,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description,(SI_Long)1L);
		lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop_1:
		    if (i >= ab_loop_bind_)
			goto end_loop_1;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop_1;
		  end_loop_1:
		    slot_index_qm = Qnil;
		  end_1:;
		    slot_value = slot_index_qm ? 
			    ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : ISVREF(slot_description,
			    (SI_Long)6L);
		}
		else
		    slot_value = ISVREF(slot_description,(SI_Long)6L);
	    }
	}
	if ( !EQ(slot_value,slot_init_form)) {
	    slot_features = ISVREF(slot_description,(SI_Long)9L);
	    temp_1 = assq_function(Qtype,slot_features) ?  
		    !TRUEP(assq_function(Qdo_not_save,slot_features)) : 
		    TRUEP(assq_function(Qsave,slot_features));
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(slot_description,(SI_Long)1L),
			Qframe_flags) ? (IFIX(ISVREF(frame,(SI_Long)4L)) & 
			 ~(SI_Long)131073L) != (IFIX(slot_init_form) &  
			~(SI_Long)131072L) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	ab_loop_it_ = (temp_1 ?  
		!TRUEP(memq_function(ISVREF(slot_description,(SI_Long)1L),
		names_of_slots_to_disregard)) : TRUEP(Nil)) ? 
		ISVREF(slot_description,(SI_Long)1L) : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qstack_of_subblocks;  /* stack-of-subblocks */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qcolumn_of_args;     /* column-of-args */

static Object Qcolumn_of_values;   /* column-of-values */

static Object Qnumber_of_rows_in_table;  /* number-of-rows-in-table */

/* WRITE-SLOT-FOR-KB */
Object write_slot_for_kb varargs_1(int, n)
{
    Object frame, slot_description, slot_value;
    Object as_ghost_qm, good_to_force_newline_qm, force_newline_qm, slot_name;
    Object slot_denotation, collectable_blocks, series_of_values;
    SI_Long i, ab_loop_bind_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(133,87);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_description = REQUIRED_ARG_nonrelocating();
    slot_value = REQUIRED_ARG_nonrelocating();
    as_ghost_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    good_to_force_newline_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    force_newline_qm = good_to_force_newline_qm;
    if (force_newline_qm);
    else {
	force_newline_qm = CONSP(slot_value) ? T : Nil;
	if (force_newline_qm);
	else
	    force_newline_qm = text_string_p(slot_value) ? 
		    (IFIX(text_string_length(slot_value)) > (SI_Long)60L ? 
		    T : Nil) : Qnil;
    }
    if (force_newline_qm)
	start_new_kb_line();
    slot_name = ISVREF(slot_description,(SI_Long)2L);
    slot_denotation = denote_slot_using_slot_value_conses(slot_description,
	    ISVREF(frame,(SI_Long)1L));
    write_element_for_kb(slot_denotation);
    reclaim_slot_value(slot_denotation);
    if (EQ(slot_name,Qstack_of_subblocks) || EQ(slot_name,
	    Qframe_representations) || EQ(slot_name,Qsubworkspaces)) {
	collectable_blocks = ISVREF(Current_kb_save,(SI_Long)37L) && 
		EQ(slot_name,Qframe_representations) ? 
		copy_collectable_blocks_within_module(slot_value,
		ISVREF(Current_kb_save,(SI_Long)37L)) : 
		copy_collectable_blocks(slot_value);
	write_element_for_kb(collectable_blocks);
	reclaim_gensym_list_1(collectable_blocks);
    }
    else if (EQ(slot_name,Qslot_group_for_block_qm))
	write_slot_group_for_block_qm(3,frame,slot_value,as_ghost_qm);
    else if (EQ(slot_name,Qcolumn_of_args) || EQ(slot_name,
		Qcolumn_of_values)) {
	write_char_for_kb(CHR('L'));
	series_of_values = slot_value;
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(get_slot_value_function(frame,
		Qnumber_of_rows_in_table,Nil));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	write_element_for_kb(ISVREF(nth(ash(FIX(i),FIX((SI_Long)-6L)),
		series_of_values),i & (SI_Long)63L));
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	write_char_for_kb(CHR('R'));
    }
    else
	write_element_for_kb(slot_value);
    return VALUES_1(force_newline_qm);
}

static Object Qitem_reference;     /* item-reference */

/* WRITE-AGGREGATE-EVALUATION-VALUE-FOR-KB */
Object write_aggregate_evaluation_value_for_kb(evaluation_value)
    Object evaluation_value;
{
    Object managed_array, managed_array_length, current_module_qm;
    Object aggregate_type, element, dereferenced_element, x2, temp_1;
    Object denotation_qm;
    SI_Long index_1, ab_loop_bind_;
    char temp;
    Declare_special(1);

    x_note_fn_call(133,88);
    managed_array = evaluation_value_value(evaluation_value);
    managed_array_length = ISVREF(managed_array,(SI_Long)1L);
    current_module_qm = ISVREF(Current_kb_save,(SI_Long)37L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_module_qm,Qcurrent_module_qm,current_module_qm,
	    0);
      aggregate_type = CDR(evaluation_value);
      write_element_for_kb(aggregate_type);
      write_element_for_kb(FIXNUM_LE(ISVREF(M_CAR(evaluation_value),
	      (SI_Long)1L),Maximum_in_place_array_size) ? 
	      ISVREF(M_CAR(evaluation_value),(SI_Long)0L + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(M_CAR(evaluation_value),(SI_Long)2L),(SI_Long)0L));
      write_element_for_kb(managed_array_length);
      if (EQ(aggregate_type,Qsequence))
	  index_1 = (SI_Long)1L;
      else if (EQ(aggregate_type,Qab_structure))
	  index_1 = (SI_Long)1L;
      else
	  index_1 = IFIX(Qnil);
      ab_loop_bind_ = IFIX(managed_array_length);
      element = Nil;
      dereferenced_element = Nil;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      element = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(managed_array,index_1 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),index_1 & (SI_Long)1023L);
      dereferenced_element = CONSP(element) && EQ(M_CDR(element),
	      Qitem_reference) ? ISVREF(M_CAR(element),(SI_Long)3L) : element;
      if ( !TRUEP(dereferenced_element))
	  write_element_for_kb(Nil);
      else {
	  if (SIMPLE_VECTOR_P(dereferenced_element) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(dereferenced_element)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(dereferenced_element,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(dereferenced_element,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      if ( !((SI_Long)0L != (IFIX(ISVREF(dereferenced_element,
		      (SI_Long)5L)) & (SI_Long)262144L)) || 
		      ISVREF(Current_saving_context,(SI_Long)3L)) {
		  temp =  !TRUEP(Current_module_qm);
		  if (temp);
		  else {
		      temp_1 = get_module_block_is_in(dereferenced_element);
		      temp = EQ(temp_1,Current_module_qm);
		  }
		  if (temp)
		      write_element_for_kb(dereferenced_element);
		  else {
		      denotation_qm = 
			      copy_for_slot_value(get_primary_name_for_frame_if_any(dereferenced_element));
		      if (denotation_qm);
		      else
			  denotation_qm = item_uuid(dereferenced_element);
		      if (denotation_qm) {
			  write_char_for_kb(CHR('~'));
			  write_element_for_kb(denotation_qm);
			  reclaim_slot_value(denotation_qm);
		      }
		      else
			  write_element_for_kb(Nil);
		  }
	      }
	      else
		  write_element_for_kb(Nil);
	  }
	  else
	      write_element_for_kb(element);
      }
      index_1 = index_1 + (SI_Long)1L;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qframe_denotation;   /* frame-denotation */

static Object Qg2gl_variable_compilation;  /* g2gl-variable-compilation */

static Object Qparent_frame;       /* parent-frame */

static Object Qkb_workspace;       /* kb-workspace */

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qg2_defstruct_structure_name_byte_code_body_g2_struct;  /* g2-defstruct-structure-name::byte-code-body-g2-struct */

static Object Qg2_defstruct_structure_name_user_mode_alias_g2_struct;  /* g2-defstruct-structure-name::user-mode-alias-g2-struct */

static Object string_constant_5;   /* "Illegal vector (starting with ~A) encountered while trying to save KB" */

/* WRITE-ELEMENT-FOR-KB */
Object write_element_for_kb(x)
    Object x;
{
    Object y, temp, x2, sub_class_bit_vector, gensymed_symbol_3, frame, symbol;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    SI_int64 gensym_long;
    char temp_1;
    double gensym_float;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(133,89);
    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	start_new_kb_line();
    if (CONSP(x)) {
	if (EQ(x,No_value))
	    write_char_for_kb(CHR('X'));
	else if (CONSP(x) && EQ(M_CDR(x),Qitem_reference))
	    write_element_for_kb(ISVREF(M_CAR(x),(SI_Long)3L));
	else if (aggregate_evaluation_value_p(x)) {
	    write_char_for_kb(CHR('%'));
	    write_aggregate_evaluation_value_for_kb(x);
	}
	else if (EQ(CAR(x),Qframe_denotation)) {
	    write_char_for_kb(CHR('~'));
	    write_element_for_kb(SECOND(x));
	}
	else {
	    write_char_for_kb(CHR('L'));
	    y = x;
	  next_loop:
	    if (ATOM(y) || EQ(y,No_value))
		goto end_loop;
	    write_element_for_kb(CAR(y));
	    y = CDR(y);
	    goto next_loop;
	  end_loop:
	    if ( ! !TRUEP(y)) {
		write_char_for_kb(CHR('.'));
		write_element_for_kb(y);
	    }
	    else
		write_char_for_kb(CHR('R'));
	}
    }
    else if (SYMBOLP(x)) {
	if ( !TRUEP(x))
	    write_char_for_kb(CHR('N'));
	else if (EQ(x,Qt))
	    write_char_for_kb(CHR('T'));
	else if (EQ(x,Simulation_no_value))
	    write_char_for_kb(CHR('#'));
	else
	    write_symbol_for_kb(x,T);
    }
    else if (INTEGERP(x))
	write_integer_for_kb(x);
    else if (text_string_p(x))
	write_character_sequence_for_kb(CHR('S'),x,ISVREF(Current_kb_save,
		(SI_Long)9L));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    gensym_float = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	    write_double_float_for_kb(DOUBLE_TO_DOUBLE_FLOAT(gensym_float));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = aref1(x,FIX((SI_Long)0L));
	    gensym_long = INTEGER_TO_INT64(temp);
	    write_long_for_kb(INT64_TO_INTEGER(gensym_long));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    write_double_float_for_kb(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,
		    (SI_Long)0L)));
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (FLOATP(x)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    write_double_float_for_kb(x);
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (INLINE_LONG_P(x) != (SI_Long)0L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    write_long_for_kb(x);
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (SIMPLE_VECTOR_P(x)) {
	if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		(SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(x,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    sub_class_bit_vector = ISVREF(ISVREF(x,(SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Dependent_frame_class_description,
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
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		write_frame_for_kb(2,x,Nil);
	    else {
		if ( !TRUEP(block_written_in_current_save_p(x))) {
		    sub_class_bit_vector = ISVREF(ISVREF(x,(SI_Long)1L),
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Format_frame_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp_1 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1);
		    else {
			gensymed_symbol_3 = 
				lookup_global_or_kb_specific_property_value(Qcomputation_style,
				Class_description_gkbprop);
			if (gensymed_symbol_3) {
			    sub_class_bit_vector = ISVREF(ISVREF(x,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol_3,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp_1 = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    if (temp_1);
		    else {
			gensymed_symbol_3 = 
				lookup_global_or_kb_specific_property_value(Qg2gl_variable_compilation,
				Class_description_gkbprop);
			if (gensymed_symbol_3) {
			    sub_class_bit_vector = ISVREF(ISVREF(x,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol_3,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp_1 = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    if (temp_1);
		    else if (get_lookup_slot_value_given_default(x,
			    Qparent_frame,Nil)) {
			frame = get_lookup_slot_value_given_default(x,
				Qparent_frame,Nil);
			symbol = Qkb_workspace;
			gensymed_symbol_3 = 
				lookup_global_or_kb_specific_property_value(symbol,
				Class_description_gkbprop);
			if (gensymed_symbol_3) {
			    sub_class_bit_vector = ISVREF(ISVREF(frame,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol_3,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp_1 = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    set_block_written_in_current_save(x,T);
		    write_frame_for_kb(2,x,T);
		}
		else
		    write_reference_to_frame(x);
	    }
	}
	else if (SIMPLE_VECTOR_P(x) && EQ(ISVREF(x,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct)) {
	    write_char_for_kb(CHR('I'));
	    write_frame_serial_number_for_kb(ISVREF(x,(SI_Long)10L));
	}
	else if (SIMPLE_VECTOR_P(x) && EQ(ISVREF(x,(SI_Long)0L),
		Managed_float_array_unique_marker))
	    write_managed_float_array_for_kb(x);
	else if (SIMPLE_VECTOR_P(x) && EQ(ISVREF(x,(SI_Long)0L),
		Managed_array_unique_marker))
	    write_managed_array_for_kb(x);
	else if (SIMPLE_VECTOR_P(x) && EQ(ISVREF(x,(SI_Long)0L),
		Qg2_defstruct_structure_name_byte_code_body_g2_struct))
	    write_byte_code_body_for_kb(x);
	else if (SIMPLE_VECTOR_P(x) && EQ(ISVREF(x,(SI_Long)0L),
		Qg2_defstruct_structure_name_pseudo_frame_g2_struct)) {
	    write_char_for_kb(CHR('H'));
	    write_frame_serial_number_for_kb(ISVREF(x,(SI_Long)2L));
	}
	else if (media_stream_p_function(x))
	    write_element_for_kb(Nil);
	else if (SIMPLE_VECTOR_P(x) && EQ(ISVREF(x,(SI_Long)0L),
		Qg2_defstruct_structure_name_user_mode_alias_g2_struct))
	    write_user_mode_alias_for_kb(x);
	else {
	    notify_user_at_console(2,string_constant_5,ISVREF(x,(SI_Long)0L));
	    write_char_for_kb(CHR('N'));
	}
    }
    else
	error((SI_Long)2L,
		"Illegal object ~A encountered while trying to save KB",x);
    return VALUES_1(Nil);
}

/* WRITE-CONNECTION-FOR-KB */
Object write_connection_for_kb(connection)
    Object connection;
{
    Object connection_frame_or_class;

    x_note_fn_call(133,90);
    write_char_for_kb(CHR('C'));
    write_frame_serial_number_for_kb(ISVREF(connection,(SI_Long)10L));
    if ( !EQ(ISVREF(Current_saving_context_qm,(SI_Long)2L),
	    Qruntime_data_only) || (SI_Long)0L != (IFIX(ISVREF(connection,
	    (SI_Long)7L)) & (SI_Long)64L)) {
	connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	if (SYMBOLP(connection_frame_or_class))
	    write_symbol_for_kb(connection_frame_or_class,T);
	else if (has_slot_values_to_save_p(1,connection_frame_or_class))
	    write_reference_to_frame(connection_frame_or_class);
	else
	    write_symbol_for_kb(ISVREF(ISVREF(connection_frame_or_class,
		    (SI_Long)1L),(SI_Long)1L),T);
	write_element_for_kb(ISVREF(connection,(SI_Long)3L));
	write_element_for_kb(ISVREF(connection,(SI_Long)2L));
	write_element_for_kb(ISVREF(connection,(SI_Long)5L));
	write_element_for_kb(ISVREF(connection,(SI_Long)4L));
	write_element_for_kb(ISVREF(connection,(SI_Long)6L));
	write_element_for_kb(FIXNUM_LOGAND(ISVREF(connection,(SI_Long)7L),
		Savable_connection_flags));
	return write_connection_attributes_plist_for_kb(ISVREF(connection,
		(SI_Long)9L));
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-CONNECTION-ATTRIBUTES-PLIST-FOR-KB */
Object write_connection_attributes_plist_for_kb(connection_attributes_plist)
    Object connection_attributes_plist;
{
    Object attributes_to_save;

    x_note_fn_call(133,91);
    attributes_to_save = 
	    get_savable_connection_attributes_plist(connection_attributes_plist);
    write_element_for_kb(attributes_to_save);
    return reclaim_slot_value_list_1(attributes_to_save);
}

/* WRITE-MANAGED-FLOAT-ARRAY-FOR-KB */
Object write_managed_float_array_for_kb(managed_float_array)
    Object managed_float_array;
{
    Object temp, temp_1, temp_2;
    SI_Long length_1;

    x_note_fn_call(133,92);
    length_1 = IFIX(ISVREF(managed_float_array,(SI_Long)1L));
    if (ISVREF(Current_kb_save,(SI_Long)24L)) {
	if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	temp_2 = CHR(' ');
	SET_SCHAR(temp,temp_1,temp_2);
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
    }
    else {
	temp = Current_kb_save;
	SVREF(temp,FIX((SI_Long)24L)) = T;
    }
    write_fixnum_digits_for_kb(FIX(length_1));
    write_char_for_kb(CHR('O'));
    return finish_writing_out_managed_float_array_for_kb(managed_float_array,
	    FIX((SI_Long)0L),FIX(length_1));
}

/* FINISH-WRITING-OUT-MANAGED-FLOAT-ARRAY-FOR-KB */
Object finish_writing_out_managed_float_array_for_kb(managed_float_array,
	    start_index_init,end_index_init)
    Object managed_float_array, start_index_init, end_index_init;
{
    SI_Long start_index, end_index, i, temp, ab_loop_repeat_;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(133,93);
    start_index = IFIX(start_index_init);
    end_index = IFIX(end_index_init);
    if (start_index < end_index) {
	i = start_index;
      next_loop:
	if (i == end_index)
	    goto end_loop;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = end_index - i;
	    ab_loop_repeat_ = MIN((SI_Long)500L,temp);
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
		    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
		start_new_kb_line();
	    write_double_float_for_kb(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_float_array,
		    (i >>  -  - (SI_Long)10L) + (SI_Long)2L),i & 
		    (SI_Long)1023L)));
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-MANAGED-ARRAY-FOR-KB */
Object write_managed_array_for_kb(managed_array)
    Object managed_array;
{
    Object length_1, temp, temp_1, temp_2;

    x_note_fn_call(133,94);
    length_1 = ISVREF(managed_array,(SI_Long)1L);
    if (ISVREF(Current_kb_save,(SI_Long)24L)) {
	if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	temp_2 = CHR(' ');
	SET_SCHAR(temp,temp_1,temp_2);
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    flush_kb_write_buffer();
    }
    else {
	temp = Current_kb_save;
	SVREF(temp,FIX((SI_Long)24L)) = T;
    }
    write_fixnum_digits_for_kb(length_1);
    write_char_for_kb(CHR('W'));
    return finish_writing_out_managed_array_for_kb(managed_array,
	    FIX((SI_Long)0L),length_1);
}

/* FINISH-WRITING-OUT-MANAGED-ARRAY-FOR-KB */
Object finish_writing_out_managed_array_for_kb(managed_array,
	    start_index_init,end_index_init)
    Object managed_array, start_index_init, end_index_init;
{
    SI_Long start_index, end_index, i, ab_loop_bind_;

    x_note_fn_call(133,95);
    start_index = IFIX(start_index_init);
    end_index = IFIX(end_index_init);
    i = start_index;
    ab_loop_bind_ = end_index;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    write_element_for_kb(FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array,i + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_array,(i >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),i & (SI_Long)1023L));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-FIXNUM-FOR-COMPILED-KB */
Object write_fixnum_for_compiled_kb(fixnum)
    Object fixnum;
{
    SI_Long temp, quotient, remainder_1;

    x_note_fn_call(133,96);
    if (IFIX(fixnum) < (SI_Long)0L) {
	write_char_for_compiled_kb(CHR('-'));
	fixnum = FIXNUM_NEGATE(fixnum);
    }
    if (IFIX(fixnum) > (SI_Long)9L) {
	temp = IFIX(fixnum) / (SI_Long)10L;
	quotient = temp;
	temp = IFIX(fixnum) % (SI_Long)10L;
	remainder_1 = temp;
	write_fixnum_for_compiled_kb(FIX(quotient));
	return write_char_for_compiled_kb(CODE_CHAR(FIX((SI_Long)48L + 
		remainder_1)));
    }
    else
	return write_char_for_compiled_kb(CODE_CHAR(FIX((SI_Long)48L + 
		IFIX(fixnum))));
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_kb_indent, Qcompiled_kb_indent);

/* WRITE-NEWLINE-FOR-COMPILED-KB */
Object write_newline_for_compiled_kb()
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(133,97);
    write_char_for_compiled_kb(CHR('\n'));
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(Compiled_kb_indent);
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    write_char_for_compiled_kb(CHR(' '));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-VARIABLE-FOR-COMPILED-KB */
Object write_variable_for_compiled_kb(variable)
    Object variable;
{
    Object string_1, char_1, dchar;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(133,98);
    if (EQ(variable,T))
	write_char_for_compiled_kb(CHR('T'));
    else {
	string_1 = SYMBOL_NAME(variable);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(string_1));
	char_1 = Nil;
	dchar = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	char_1 = CHR(ISCHAR(string_1,i));
	dchar = EQ(char_1,CHR('-')) ? CHR('_') : CHAR_DOWNCASE(char_1);
	if (CHAR_EQ(dchar,CHR('\?'))) {
	    write_char_for_compiled_kb(CHR('_'));
	    write_char_for_compiled_kb(CHR('q'));
	    write_char_for_compiled_kb(CHR('m'));
	}
	else
	    write_char_for_compiled_kb(dchar);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* WRITE-VARIABLE-LIST-FOR-COMPILED-KB */
Object write_variable_list_for_compiled_kb(variable_list,separator_string)
    Object variable_list, separator_string;
{
    Object first_1, variable, ab_loop_list_;

    x_note_fn_call(133,99);
    first_1 = T;
    variable = Nil;
    ab_loop_list_ = variable_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(first_1))
	write_gensym_string_for_compiled_kb(separator_string);
    write_variable_for_compiled_kb(variable);
    first_1 = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-TAG-FOR-COMPILED-KB */
Object write_tag_for_compiled_kb(tag)
    Object tag;
{
    x_note_fn_call(133,100);
    if (SYMBOLP(tag))
	return write_variable_for_compiled_kb(tag);
    else if (FIXNUMP(tag))
	return write_fixnum_for_compiled_kb(tag);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_6;   /* "default:" */

static Object string_constant_7;   /* "case " */

/* WRITE-CASE-TAG-FOR-COMPILED-KB */
Object write_case_tag_for_compiled_kb(tag)
    Object tag;
{
    x_note_fn_call(133,101);
    if (EQ(tag,T))
	return write_gensym_string_for_compiled_kb(string_constant_6);
    else {
	write_gensym_string_for_compiled_kb(string_constant_7);
	write_tag_for_compiled_kb(tag);
	return write_char_for_compiled_kb(CHR(':'));
    }
}

static Object Kdouble;             /* :double */

static Object Kint;                /* :int */

static Object Kobject;             /* :object */

static Object Qcompiled_function_in_place;  /* compiled-function-in-place */

static Object Qab_or;              /* or */

static Object Kboolean;            /* :boolean */

static Object Qab_let;             /* let */

static Object Qab_let_star;        /* let* */

static Object Qife;                /* ife */

/* C-TYPE-OF-EXPRESSION */
Object c_type_of_expression(form,desired_type)
    Object form, desired_type;
{
    Object temp, type;

    x_note_fn_call(133,102);
    if (FLOATP(form))
	return VALUES_1(Kdouble);
    else if (INTEGERP(form))
	return VALUES_1(Kint);
    else if ( !TRUEP(form)) {
	if (EQ(desired_type,Kobject))
	    return VALUES_1(Kobject);
	else
	    return VALUES_1(Kint);
    }
    else if (SYMBOLP(form))
	return c_type_of_variable(form);
    else if (CONSP(form)) {
	temp = CAR(form);
	if (EQ(temp,Qcompiled_function_in_place))
	    return VALUES_1(Kobject);
	else if (EQ(temp,Qsetf))
	    return c_type_of_expression(SECOND(form),desired_type);
	else if (EQ(temp,Qab_or) || EQ(temp,Qand)) {
	    if (EQ(desired_type,Kboolean))
		return VALUES_1(Kboolean);
	    else
		return c_type_of_expression(SECOND(form),desired_type);
	}
	else if (EQ(temp,Qprogn) || EQ(temp,Qab_let) || EQ(temp,
		    Qab_let_star)) {
	    temp = last(form,_);
	    return c_type_of_expression(CAR(temp),desired_type);
	}
	else if (EQ(temp,Qife))
	    return c_type_of_expression(THIRD(form),desired_type);
	else if (EQ(temp,Qquote))
	    return VALUES_1(Kobject);
	else {
	    type = 
		    inlined_function_return_type(inlined_function_data(CAR(form)));
	    return VALUES_1(type);
	}
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_8;   /* "FIX(" */

static Object string_constant_9;   /* ")" */

static Object string_constant_10;  /* "(" */

static Object string_constant_11;  /* " ? T : Nil)" */

static Object string_constant_12;  /* "DOUBLE_TO_DOUBLE_FLOAT(" */

static Object string_constant_13;  /* "(IFIX(" */

static Object string_constant_14;  /* "))" */

static Object string_constant_15;  /* "((" */

static Object string_constant_16;  /* ") != Nil)" */

static Object string_constant_17;  /* "T" */

static Object string_constant_18;  /* "DOUBLE_FLOAT_TO_DOUBLE(" */

/* WRITE-EXPRESSION-FOR-COMPILED-KB-AS-TYPE */
Object write_expression_for_compiled_kb_as_type(form,desired_type)
    Object form, desired_type;
{
    Object actual_type;

    x_note_fn_call(133,103);
    actual_type = c_type_of_expression(form,desired_type);
    if (EQ(desired_type,Kobject)) {
	if (EQ(actual_type,Kobject))
	    return write_object_expression_for_compiled_kb(form);
	else if (EQ(actual_type,Kint)) {
	    write_gensym_string_for_compiled_kb(string_constant_8);
	    write_int_expression_for_compiled_kb(form);
	    return write_gensym_string_for_compiled_kb(string_constant_9);
	}
	else if (EQ(actual_type,Kboolean)) {
	    write_gensym_string_for_compiled_kb(string_constant_10);
	    write_boolean_expression_for_compiled_kb(form);
	    return write_gensym_string_for_compiled_kb(string_constant_11);
	}
	else if (EQ(actual_type,Kdouble)) {
	    write_gensym_string_for_compiled_kb(string_constant_12);
	    write_double_expression_for_compiled_kb(form);
	    return write_gensym_string_for_compiled_kb(string_constant_9);
	}
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(desired_type,Kint)) {
	if (EQ(actual_type,Kobject)) {
	    write_gensym_string_for_compiled_kb(string_constant_13);
	    write_object_expression_for_compiled_kb(form);
	    return write_gensym_string_for_compiled_kb(string_constant_14);
	}
	else if (EQ(actual_type,Kint))
	    return write_int_expression_for_compiled_kb(form);
	else if (EQ(actual_type,Kboolean))
	    return write_boolean_expression_for_compiled_kb(form);
	else if (EQ(actual_type,Kdouble))
	    return write_double_expression_for_compiled_kb(form);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(desired_type,Kboolean)) {
	if (EQ(actual_type,Kobject)) {
	    write_gensym_string_for_compiled_kb(string_constant_15);
	    write_object_expression_for_compiled_kb(form);
	    return write_gensym_string_for_compiled_kb(string_constant_16);
	}
	else if (EQ(actual_type,Kboolean))
	    return write_boolean_expression_for_compiled_kb(form);
	else if (EQ(actual_type,Kint))
	    return write_gensym_string_for_compiled_kb(string_constant_17);
	else if (EQ(actual_type,Kdouble))
	    return write_gensym_string_for_compiled_kb(string_constant_17);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(desired_type,Kdouble)) {
	if (EQ(actual_type,Kobject)) {
	    write_gensym_string_for_compiled_kb(string_constant_18);
	    write_object_expression_for_compiled_kb(form);
	    return write_gensym_string_for_compiled_kb(string_constant_9);
	}
	else if (EQ(actual_type,Kint))
	    return write_int_expression_for_compiled_kb(form);
	else if (EQ(actual_type,Kboolean))
	    return write_boolean_expression_for_compiled_kb(form);
	else if (EQ(actual_type,Kdouble))
	    return write_double_expression_for_compiled_kb(form);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_19;  /* " = " */

static Object list_constant_2;     /* # */

static Object string_constant_20;  /* " || " */

static Object string_constant_21;  /* " && " */

static Object string_constant_22;  /* ", " */

static Object string_constant_23;  /* " ? " */

static Object string_constant_24;  /* " : " */

static Object string_constant_25;  /* "STATIC_SYMBOL(\"" */

static Object string_constant_26;  /* "\")" */

static Object list_constant_3;     /* # */

static Object string_constant_27;  /* "/* bad let ?/" */

static Object list_constant_4;     /* # */

/* WRITE-FUNCTION-CALL-FOR-COMPILED-KB */
Object write_function_call_for_compiled_kb(form,c_type)
    Object form, c_type;
{
    Object fn, temp, firstp, form_tail, lastp, compiled_kb_indent, name, value;
    Object ab_loop_list_, ab_loop_desetq_, expression, inlined_function_data_1;
    Object numbered_qm, form_old_value;
    Declare_special(1);

    x_note_fn_call(133,104);
    fn = CAR(form);
    if (EQ(fn,Qsetf)) {
	write_expression_for_compiled_kb_as_type(CADR(form),c_type);
	write_gensym_string_for_compiled_kb(string_constant_19);
	return write_expression_for_compiled_kb_as_type(CADDR(form),c_type);
    }
    else if (memq_function(fn,list_constant_2)) {
	write_char_for_compiled_kb(CHR('('));
	write_expression_for_compiled_kb_as_type(CADR(form),c_type);
	if (EQ(fn,Qab_or))
	    temp = string_constant_20;
	else if (EQ(fn,Qand))
	    temp = string_constant_21;
	else
	    temp = Qnil;
	write_gensym_string_for_compiled_kb(temp);
	write_expression_for_compiled_kb_as_type(CADDR(form),c_type);
	return write_char_for_compiled_kb(CHR(')'));
    }
    else if (EQ(fn,Qprogn)) {
	write_char_for_compiled_kb(CHR('('));
	firstp = T;
	form_tail = CDR(form);
	form = Nil;
	lastp = Nil;
      next_loop:
	if ( !TRUEP(form_tail))
	    goto end_loop;
	form = CAR(form_tail);
	lastp =  !TRUEP(CDR(form_tail)) ? T : Nil;
	if ( !TRUEP(firstp))
	    write_gensym_string_for_compiled_kb(string_constant_22);
	write_expression_for_compiled_kb_as_type(form,lastp ? c_type : 
		Kobject);
	firstp = Nil;
	form_tail = M_CDR(form_tail);
	goto next_loop;
      end_loop:;
	return write_char_for_compiled_kb(CHR(')'));
    }
    else if (EQ(fn,Qife)) {
	write_char_for_compiled_kb(CHR('('));
	write_boolean_expression_for_compiled_kb(CADR(form));
	write_gensym_string_for_compiled_kb(string_constant_23);
	write_expression_for_compiled_kb_as_type(CADDR(form),c_type);
	write_gensym_string_for_compiled_kb(string_constant_24);
	write_expression_for_compiled_kb_as_type(CADDDR(form),c_type);
	return write_char_for_compiled_kb(CHR(')'));
    }
    else if (EQ(fn,Qquote)) {
	write_gensym_string_for_compiled_kb(string_constant_25);
	write_object_expression_for_compiled_kb(CADR(form));
	return write_gensym_string_for_compiled_kb(string_constant_26);
    }
    else if (memq_function(fn,list_constant_3)) {
	write_newline_for_compiled_kb();
	write_gensym_string_for_compiled_kb(string_constant_27);
	write_newline_for_compiled_kb();
	write_char_for_compiled_kb(CHR('{'));
	compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		0);
	  write_newline_for_compiled_kb();
	  name = Nil;
	  value = Nil;
	  ab_loop_list_ = CADR(form);
	  ab_loop_desetq_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  name = CAR(ab_loop_desetq_);
	  temp = CDR(ab_loop_desetq_);
	  value = CAR(temp);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  write_object_expression_for_compiled_kb(name);
	  write_gensym_string_for_compiled_kb(string_constant_19);
	  write_object_expression_for_compiled_kb(value);
	  write_char_for_compiled_kb(CHR(';'));
	  write_newline_for_compiled_kb();
	  goto next_loop_1;
	end_loop_1:;
	  expression = Nil;
	  ab_loop_list_ = CDDR(form);
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  expression = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  write_object_expression_for_compiled_kb(expression);
	  write_char_for_compiled_kb(CHR(';'));
	  write_newline_for_compiled_kb();
	  goto next_loop_2;
	end_loop_2:;
	POP_SPECIAL();
	write_char_for_compiled_kb(CHR('}'));
	return write_newline_for_compiled_kb();
    }
    else {
	inlined_function_data_1 = inlined_function_data_given_arg_count(fn,
		FIXNUM_SUB1(length(form)));
	numbered_qm = inlined_function_numbered(inlined_function_data_1);
	name = inlined_function_c_name(inlined_function_data_1);
	write_gensym_string_for_compiled_kb(name);
	if (numbered_qm)
	    write_fixnum_for_compiled_kb(minus(length(CDR(form)),numbered_qm));
	write_char_for_compiled_kb(CHR('('));
	if (memq_function(fn,list_constant_4)) {
	    write_fixnum_for_compiled_kb(CADR(form));
	    form_old_value = form;
	    form = REST(form_old_value);
	    if (CDR(form))
		write_gensym_string_for_compiled_kb(string_constant_22);
	}
	temp = CDR(form);
	write_expression_list_for_compiled_kb(temp,string_constant_22,
		inlined_function_argument_type(inlined_function_data_1));
	return write_char_for_compiled_kb(CHR(')'));
    }
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

/* C-TYPE-OF-VARIABLE */
Object c_type_of_variable(variable_name)
    Object variable_name;
{
    x_note_fn_call(133,105);
    if (memq_function(variable_name,list_constant_5))
	return VALUES_1(Kobject);
    else if (memq_function(variable_name,list_constant_6))
	return VALUES_1(Kdouble);
    else
	return VALUES_1(Kobject);
}

static Object string_constant_28;  /* "Nil" */

/* WRITE-OBJECT-EXPRESSION-FOR-COMPILED-KB */
Object write_object_expression_for_compiled_kb(form)
    Object form;
{
    x_note_fn_call(133,106);
    if ( !TRUEP(form))
	return write_gensym_string_for_compiled_kb(string_constant_28);
    else if (SYMBOLP(form))
	return write_variable_for_compiled_kb(form);
    else if (CONSP(form)) {
	if (EQ(CAR(form),Qcompiled_function_in_place))
	    return write_expression_for_compiled_kb_as_type(CADR(form),
		    Kobject);
	else
	    return write_function_call_for_compiled_kb(form,Kobject);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_29;  /* "0" */

/* WRITE-BOOLEAN-EXPRESSION-FOR-COMPILED-KB */
Object write_boolean_expression_for_compiled_kb(form)
    Object form;
{
    x_note_fn_call(133,107);
    if ( !TRUEP(form))
	return write_gensym_string_for_compiled_kb(string_constant_29);
    else if (SYMBOLP(form))
	return write_variable_for_compiled_kb(form);
    else if (CONSP(form))
	return write_function_call_for_compiled_kb(form,Kboolean);
    else
	return VALUES_1(Qnil);
}

/* WRITE-INT-EXPRESSION-FOR-COMPILED-KB */
Object write_int_expression_for_compiled_kb(form)
    Object form;
{
    x_note_fn_call(133,108);
    if (FIXNUMP(form))
	return write_fixnum_for_compiled_kb(form);
    else if (SYMBOLP(form))
	return write_variable_for_compiled_kb(form);
    else if (CONSP(form))
	return write_function_call_for_compiled_kb(form,Kint);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_30;  /* "~F" */

/* WRITE-DOUBLE-EXPRESSION-FOR-COMPILED-KB */
Object write_double_expression_for_compiled_kb(form)
    Object form;
{
    Object gensym_string;

    x_note_fn_call(133,109);
    if (FLOATP(form)) {
	gensym_string = tformat_gensym_string(2,string_constant_30,form);
	write_gensym_string_for_compiled_kb(gensym_string);
	return reclaim_gensym_string(gensym_string);
    }
    else if (SYMBOLP(form))
	return write_variable_for_compiled_kb(form);
    else if (CONSP(form))
	return write_function_call_for_compiled_kb(form,Kdouble);
    else
	return VALUES_1(Qnil);
}

/* WRITE-EXPRESSION-LIST-FOR-COMPILED-KB */
Object write_expression_list_for_compiled_kb(form_list,separator_string,
	    c_types)
    Object form_list, separator_string, c_types;
{
    Object first_1, form, ab_loop_list_, c_types_left, c_type;
    Object ab_loop_iter_flag_;

    x_note_fn_call(133,110);
    first_1 = T;
    form = Nil;
    ab_loop_list_ = form_list;
    c_types_left = CONSP(c_types) ? c_types : Nil;
    c_type = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	c_types_left = c_types_left ? CDR(c_types_left) : Nil;
    c_type = c_types_left ? CAR(c_types_left) : c_types;
    if ( !TRUEP(first_1))
	write_gensym_string_for_compiled_kb(separator_string);
    write_expression_for_compiled_kb_as_type(form,c_type);
    ab_loop_iter_flag_ = Nil;
    first_1 = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_31;  /* "goto " */

static Object Qab_loop;            /* loop */

static Object string_constant_32;  /* "while (" */

static Object string_constant_33;  /* ") {" */

static Object string_constant_34;  /* "}" */

static Object Qfixnum_case;        /* fixnum-case */

static Object Qfixnum_case_with_fallthrough;  /* fixnum-case-with-fallthrough */

static Object string_constant_35;  /* "switch (" */

static Object string_constant_36;  /* "break;" */

static Object Qab_if;              /* if */

static Object string_constant_37;  /* "if (" */

static Object string_constant_38;  /* "} else {" */

static Object string_constant_39;  /* "{Object result = " */

static Object string_constant_40;  /* "MVS_" */

static Object string_constant_41;  /* "(result," */

static Object string_constant_42;  /* "," */

static Object string_constant_43;  /* ");}" */

static Object string_constant_44;  /* "Object " */

static Object string_constant_45;  /* "int " */

static Object string_constant_46;  /* "double " */

/* WRITE-STATEMENT-FOR-COMPILED-KB */
Object write_statement_for_compiled_kb(form)
    Object form;
{
    Object temp, compiled_kb_indent, clause, ab_loop_list_, var, init;
    Object ab_loop_desetq_, c_type;
    Declare_special(2);

    x_note_fn_call(133,111);
    if (CONSP(form)) {
	temp = CAR(form);
	if (EQ(temp,Qtagbody))
	    write_statement_or_tag_block_for_compiled_kb(CDR(form));
	else if (EQ(temp,Qprogn))
	    write_statement_list_for_compiled_kb(CDR(form));
	else if (EQ(temp,Qgo)) {
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_31);
	    write_tag_for_compiled_kb(CADR(form));
	}
	else if (EQ(temp,Qab_loop)) {
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_32);
	    write_expression_for_compiled_kb_as_type(THIRD(form),Kboolean);
	    write_gensym_string_for_compiled_kb(string_constant_33);
	    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		    0);
	      write_statement_list_for_compiled_kb(CDDDDR(form));
	    POP_SPECIAL();
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_34);
	}
	else if (EQ(temp,Qfixnum_case) || EQ(temp,
		Qfixnum_case_with_fallthrough)) {
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_35);
	    write_expression_for_compiled_kb_as_type(CADR(form),Kint);
	    write_gensym_string_for_compiled_kb(string_constant_33);
	    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		    1);
	      clause = Nil;
	      ab_loop_list_ = CDDR(form);
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      clause = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) - (SI_Long)2L);
	      PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		      0);
		write_newline_for_compiled_kb();
		write_case_tag_for_compiled_kb(CAR(clause));
	      POP_SPECIAL();
	      write_statement_list_for_compiled_kb(CDR(clause));
	      write_newline_for_compiled_kb();
	      if (EQ(CAR(form),Qfixnum_case))
		  write_gensym_string_for_compiled_kb(string_constant_36);
	      goto next_loop;
	    end_loop:;
	    POP_SPECIAL();
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_34);
	}
	else if (EQ(temp,Qab_if)) {
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_37);
	    write_expression_for_compiled_kb_as_type(CADR(form),Kboolean);
	    write_gensym_string_for_compiled_kb(string_constant_33);
	    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		    0);
	      write_statement_for_compiled_kb(CADDR(form));
	    POP_SPECIAL();
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_38);
	    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		    0);
	      write_statement_for_compiled_kb(CADDDR(form));
	    POP_SPECIAL();
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_34);
	}
	else if (EQ(temp,Qmultiple_value_setq)) {
	    write_newline_for_compiled_kb();
	    write_gensym_string_for_compiled_kb(string_constant_39);
	    write_expression_for_compiled_kb_as_type(CADDR(form),Kobject);
	    write_char_for_compiled_kb(CHR(';'));
	    compiled_kb_indent = FIXNUM_ADD1(Compiled_kb_indent);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		    0);
	      write_newline_for_compiled_kb();
	      write_gensym_string_for_compiled_kb(string_constant_40);
	      write_fixnum_for_compiled_kb(length(CADR(form)));
	      write_gensym_string_for_compiled_kb(string_constant_41);
	      write_variable_list_for_compiled_kb(CADR(form),
		      string_constant_42);
	      write_gensym_string_for_compiled_kb(string_constant_43);
	    POP_SPECIAL();
	}
	else if (EQ(temp,Qab_let) || EQ(temp,Qab_let_star)) {
	    write_newline_for_compiled_kb();
	    write_char_for_compiled_kb(CHR('{'));
	    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		    0);
	      var = Nil;
	      init = Nil;
	      ab_loop_list_ = CADR(form);
	      ab_loop_desetq_ = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      ab_loop_desetq_ = M_CAR(ab_loop_list_);
	      var = CAR(ab_loop_desetq_);
	      temp = CDR(ab_loop_desetq_);
	      init = CAR(temp);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      write_newline_for_compiled_kb();
	      c_type = c_type_of_variable(var);
	      temp = c_type_of_variable(var);
	      if (EQ(temp,Kobject))
		  temp = string_constant_44;
	      else if (EQ(temp,Kint))
		  temp = string_constant_45;
	      else if (EQ(temp,Kdouble))
		  temp = string_constant_46;
	      else if (EQ(temp,Kboolean))
		  temp = string_constant_45;
	      else
		  temp = Qnil;
	      write_gensym_string_for_compiled_kb(temp);
	      write_variable_for_compiled_kb(var);
	      write_gensym_string_for_compiled_kb(string_constant_19);
	      write_expression_for_compiled_kb_as_type(init,c_type);
	      write_char_for_compiled_kb(CHR(';'));
	      goto next_loop_1;
	    end_loop_1:;
	      write_statement_list_for_compiled_kb(CDDR(form));
	    POP_SPECIAL();
	    write_newline_for_compiled_kb();
	    write_char_for_compiled_kb(CHR('}'));
	}
	else {
	    write_newline_for_compiled_kb();
	    write_expression_for_compiled_kb_as_type(form,
		    c_type_of_expression(form,Kobject));
	}
    }
    return write_char_for_compiled_kb(CHR(';'));
}

/* WRITE-STATEMENT-OR-TAG-LIST-FOR-COMPILED-KB */
Object write_statement_or_tag_list_for_compiled_kb(form_list)
    Object form_list;
{
    Object form, ab_loop_list_, compiled_kb_indent;
    Declare_special(1);

    x_note_fn_call(133,112);
    form = Nil;
    ab_loop_list_ = form_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ATOM(form)) {
	if (form) {
	    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) - (SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
		    0);
	      write_newline_for_compiled_kb();
	      write_tag_for_compiled_kb(form);
	      write_char_for_compiled_kb(CHR(':'));
	    POP_SPECIAL();
	}
    }
    else
	write_statement_for_compiled_kb(form);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-STATEMENT-LIST-FOR-COMPILED-KB */
Object write_statement_list_for_compiled_kb(form_list)
    Object form_list;
{
    Object form, ab_loop_list_;

    x_note_fn_call(133,113);
    form = Nil;
    ab_loop_list_ = form_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    write_statement_for_compiled_kb(form);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_47;  /* "  char *fn_name = \"fn" */

static Object string_constant_48;  /* "\";" */

/* WRITE-STATEMENT-BLOCK-FOR-COMPILED-KB */
Object write_statement_block_for_compiled_kb(form_list,index_1)
    Object form_list, index_1;
{
    Object compiled_kb_indent;
    Declare_special(1);

    x_note_fn_call(133,114);
    write_newline_for_compiled_kb();
    write_char_for_compiled_kb(CHR('{'));
    write_gensym_string_for_compiled_kb(string_constant_47);
    write_fixnum_for_compiled_kb(index_1);
    write_gensym_string_for_compiled_kb(string_constant_48);
    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
	    0);
      write_statement_list_for_compiled_kb(form_list);
    POP_SPECIAL();
    write_newline_for_compiled_kb();
    write_char_for_compiled_kb(CHR('}'));
    return VALUES_1(Nil);
}

/* WRITE-STATEMENT-OR-TAG-BLOCK-FOR-COMPILED-KB */
Object write_statement_or_tag_block_for_compiled_kb(form_list)
    Object form_list;
{
    Object compiled_kb_indent;
    Declare_special(1);

    x_note_fn_call(133,115);
    write_newline_for_compiled_kb();
    write_char_for_compiled_kb(CHR('{'));
    compiled_kb_indent = FIX(IFIX(Compiled_kb_indent) + (SI_Long)2L);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
	    0);
      write_statement_or_tag_list_for_compiled_kb(form_list);
    POP_SPECIAL();
    write_newline_for_compiled_kb();
    return write_char_for_compiled_kb(CHR('}'));
}

static Object string_constant_49;  /* "static Object fn" */

static Object string_constant_50;  /* "  Object " */

/* WRITE-FUNCTION-FOR-COMPILED-KB */
Object write_function_for_compiled_kb(index_1,lambda_form)
    Object index_1, lambda_form;
{
    Object compiled_kb_indent;
    Declare_special(1);

    x_note_fn_call(133,116);
    compiled_kb_indent = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_kb_indent,Qcompiled_kb_indent,compiled_kb_indent,
	    0);
      write_char_for_compiled_kb(CHR('\n'));
      write_gensym_string_for_compiled_kb(string_constant_49);
      write_fixnum_for_compiled_kb(index_1);
      write_char_for_compiled_kb(CHR('('));
      write_variable_list_for_compiled_kb(CADR(lambda_form),
	      string_constant_22);
      write_char_for_compiled_kb(CHR(')'));
      write_char_for_compiled_kb(CHR('\n'));
      write_gensym_string_for_compiled_kb(string_constant_50);
      write_variable_list_for_compiled_kb(CADR(lambda_form),
	      string_constant_22);
      write_char_for_compiled_kb(CHR(';'));
      write_statement_block_for_compiled_kb(CDDR(lambda_form),index_1);
      write_char_for_compiled_kb(CHR('\n'));
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_51;  /* "#define fn" */

static Object string_constant_52;  /* " 0" */

/* WRITE-UNCOMPILED-FUNCTION-FOR-COMPILED-KB */
Object write_uncompiled_function_for_compiled_kb()
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(133,117);
    if (T) {
	write_char_for_compiled_kb(CHR('\n'));
	write_gensym_string_for_compiled_kb(string_constant_51);
	svref_arg_1 = Current_kb_save;
	svref_new_value = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)44L));
	write_fixnum_for_compiled_kb(SVREF(svref_arg_1,FIX((SI_Long)44L)) 
		= svref_new_value);
	write_gensym_string_for_compiled_kb(string_constant_52);
	write_char_for_compiled_kb(CHR('\n'));
	if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)42L),
		Number_of_characters_beyond_which_to_start_a_new_saved_compiled_file))
	    increment_compiled_kb_file();
    }
    return VALUES_1(Nil);
}

/* WRITE-FUNCTION-DEFINITION-FOR-COMPILED-KB */
Object write_function_definition_for_compiled_kb(byte_code_body,
	    constant_vector,entry_points)
    Object byte_code_body, constant_vector, entry_points;
{
    Object gensymed_symbol, gensymed_symbol_1, current_edit_state, svref_arg_1;
    Object lambda_form, new_constant_vector, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(133,118);
    gensymed_symbol = Current_edit_state;
    if (Generate_source_annotation_info) {
	gensymed_symbol_1 = Current_edit_state ? 
		get_current_sexp_annotation_hash() : Nil;
	if (gensymed_symbol_1);
	else
	    gensymed_symbol_1 = make_sexp_annotation_hash();
    }
    else
	gensymed_symbol_1 = Nil;
    current_edit_state = make_edit_state_1();
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      svref_arg_1 = Current_edit_state;
      SVREF(svref_arg_1,FIX((SI_Long)90L)) = gensymed_symbol_1;
      result = lisp_for_byte_code_body(byte_code_body,constant_vector,
	      entry_points);
      MVS_2(result,lambda_form,new_constant_vector);
      if ( !EQ(constant_vector,new_constant_vector))
	  SVREF(byte_code_body,FIX((SI_Long)3L)) = new_constant_vector;
      if (T) {
	  write_char_for_compiled_kb(CHR('\n'));
	  svref_arg_1 = Current_kb_save;
	  svref_new_value = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)44L));
	  write_function_for_compiled_kb(SVREF(svref_arg_1,
		  FIX((SI_Long)44L)) = svref_new_value,lambda_form);
	  if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)42L),
		  Number_of_characters_beyond_which_to_start_a_new_saved_compiled_file))
	      increment_compiled_kb_file();
      }
      if (gensymed_symbol) {
	  svref_arg_1 = Current_edit_state;
	  SVREF(svref_arg_1,FIX((SI_Long)90L)) = Nil;
      }
      reclaim_edit_state_1(Current_edit_state);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_53;  /* "  ~NF ~D~%" */

static Object string_constant_54;  /* "  ~NF~%" */

static Object string_constant_55;  /* "  ~NF ~A~%" */

static Object string_constant_56;  /* "  ~A ~A~%" */

static Object string_constant_57;  /* "~%" */

static Object Qgensym_string;      /* gensym-string */

/* WRITE-DESCRIPTION-OF-FUNCTION-FOR-COMPILED-KB */
Object write_description_of_function_for_compiled_kb(byte_code_body,frame,
	    definition,code_bodies,constant_vector,long_form_p)
    Object byte_code_body, frame, definition, code_bodies, constant_vector;
    Object long_form_p;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object text_string, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, gensym_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(5);

    x_note_fn_call(133,119);
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
	      if (SIMPLE_VECTOR_P(frame) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(frame,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(frame,(SI_Long)1L);
		  gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol = Nil;
	      if (gensymed_symbol) {
		  gensymed_symbol_1 = 
			  lookup_global_or_kb_specific_property_value(Qcode_body,
			  Class_description_gkbprop);
		  if (gensymed_symbol_1) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  temp = (SI_Long)0L < gensymed_symbol_2;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  if (CDR(code_bodies))
		      tformat(3,string_constant_53,definition,position(2,
			      frame,code_bodies));
		  else
		      tformat(2,string_constant_54,definition);
	      }
	      else {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Block_class_description,(SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
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
		      temp = (SI_Long)0L < gensymed_symbol_2;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      tformat(3,string_constant_55,frame,
			      Slot_name_for_write_frame_for_kb);
		  else {
		      if (SIMPLE_VECTOR_P(frame) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(frame,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(frame,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  tformat(3,string_constant_56,ISVREF(ISVREF(frame,
				  (SI_Long)1L),(SI_Long)1L),
				  Slot_name_for_write_frame_for_kb);
		  }
	      }
	      if (long_form_p) {
		  write_byte_code_body(byte_code_body,constant_vector);
		  tformat(1,string_constant_57);
	      }
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    twrite_general_string(text_string);
	    reclaim_text_string(text_string);
	    gensym_string = copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (T)
	write_gensym_string_comment_for_compiled_kb(gensym_string);
    reclaim_gensym_string(gensym_string);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Write_all_byte_code_bodies_for_kb_p, Qwrite_all_byte_code_bodies_for_kb_p);

/* COMPILE-BYTE-CODE-BODY-FOR-KB-P */
Object compile_byte_code_body_for_kb_p(byte_code_body,frame,definition,
	    constant_vector)
    Object byte_code_body, frame, definition, constant_vector;
{
    Object temp;

    x_note_fn_call(133,120);
    if (definition &&  
	    !TRUEP(byte_code_body_contains_instruction_that_should_not_be_compiled_p(byte_code_body,
	    constant_vector)) &&  
	    !TRUEP(byte_code_body_is_too_long_to_compile_p(byte_code_body))) {
	temp = Write_all_byte_code_bodies_for_kb_p;
	if (temp)
	    return VALUES_1(temp);
	else
	    return byte_code_body_contains_backward_branch_p(byte_code_body,
		    constant_vector);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-COMPILED-BYTE-CODE-BODY-FOR-KB */
Object write_compiled_byte_code_body_for_kb(byte_code_body)
    Object byte_code_body;
{
    Object frame, x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object definition, code_bodies, constant_vector, code_body_1;
    Object ab_loop_list_, entry_points, compile_p;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(133,121);
    if (Enable_saving_compiled_kbs_p) {
	frame = Frame_for_write_frame_for_kb;
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qcode_body,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	definition = temp ? 
		procedure_definition_of_code_body_function(frame) : Nil;
	if (SIMPLE_VECTOR_P(definition) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(definition)) > (SI_Long)2L 
		&&  !EQ(ISVREF(definition,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(definition,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	code_bodies = temp ? code_bodies_function(definition) : Nil;
	constant_vector = ISVREF(byte_code_body,(SI_Long)3L);
	if (constant_vector);
	else
	    constant_vector = code_bodies ? 
		    ISVREF(code_body_byte_code_body_function(CAR(code_bodies)),
		    (SI_Long)3L) : Qnil;
	if (definition) {
	    code_body_1 = Nil;
	    ab_loop_list_ = code_bodies_function(definition);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    code_body_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(code_body_byte_code_body_function(code_body_1),
		    byte_code_body)) {
		entry_points = code_body_entry_points_function(code_body_1);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    entry_points = Nil;
	    goto end_1;
	    entry_points = Qnil;
	  end_1:;
	}
	else
	    entry_points = Nil;
	compile_p = compile_byte_code_body_for_kb_p(byte_code_body,frame,
		definition,constant_vector);
	write_description_of_function_for_compiled_kb(byte_code_body,frame,
		definition,code_bodies,constant_vector,compile_p);
	if (compile_p)
	    return write_function_definition_for_compiled_kb(byte_code_body,
		    constant_vector,entry_points);
	else
	    return write_uncompiled_function_for_compiled_kb();
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-BYTE-CODE-BODY-FOR-KB */
Object write_byte_code_body_for_kb(byte_code_body)
    Object byte_code_body;
{
    Object body_vector, body_vector_length, constant_vector_qm;
    Object constant_vector_length_qm, free_reference_vector_qm;
    Object free_reference_vector_length_qm, constant;
    SI_Long temp, length_in_words, index_1, ab_loop_bind_;

    x_note_fn_call(133,122);
    write_compiled_byte_code_body_for_kb(byte_code_body);
    body_vector = ISVREF(byte_code_body,(SI_Long)2L);
    body_vector_length = ISVREF(byte_code_body,(SI_Long)1L);
    temp = (IFIX(body_vector_length) + ((SI_Long)4L - (SI_Long)1L)) / 
	    (SI_Long)4L;
    length_in_words = temp;
    constant_vector_qm = ISVREF(byte_code_body,(SI_Long)3L);
    constant_vector_length_qm = constant_vector_qm ? 
	    SIMPLE_ARRAY_ANY_1_LENGTH(constant_vector_qm) : Nil;
    free_reference_vector_qm = ISVREF(byte_code_body,(SI_Long)7L);
    free_reference_vector_length_qm = free_reference_vector_qm ? 
	    SIMPLE_ARRAY_ANY_1_LENGTH(free_reference_vector_qm) : Nil;
    write_char_for_kb(CHR('B'));
    write_fixnum_for_kb(body_vector_length);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = length_in_words * (SI_Long)4L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	start_new_kb_line();
    write_binary_word_for_kb(FIX(UBYTE_8_ISAREF_1(body_vector,index_1 + 
	    (SI_Long)2L) | UBYTE_8_ISAREF_1(body_vector,index_1 + 
	    (SI_Long)3L) << (SI_Long)8L),FIX(UBYTE_8_ISAREF_1(body_vector,
	    index_1) | UBYTE_8_ISAREF_1(body_vector,index_1 + (SI_Long)1L) 
	    << (SI_Long)8L));
    index_1 = index_1 + (SI_Long)4L;
    goto next_loop;
  end_loop:;
    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	start_new_kb_line();
    if (constant_vector_qm) {
	write_fixnum_for_kb(constant_vector_length_qm);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(constant_vector_length_qm);
	constant = Nil;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	constant = ISVREF(constant_vector_qm,index_1);
	write_element_for_kb(thing_is_item_p(constant) ? Nil : constant);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else
	write_char_for_kb(CHR('N'));
    write_element_for_kb(ISVREF(byte_code_body,(SI_Long)4L));
    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	start_new_kb_line();
    if (free_reference_vector_qm) {
	write_fixnum_for_kb(free_reference_vector_length_qm);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(free_reference_vector_length_qm);
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	write_element_for_kb(ISVREF(free_reference_vector_qm,index_1));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
    else
	return write_char_for_kb(CHR('N'));
}

static Object Qwrite_reference_to_frame;  /* write-reference-to-frame */

static Object Qui_client_item;     /* ui-client-item */

/* WRITE-REFERENCE-TO-FRAME */
Object write_reference_to_frame(frame)
    Object frame;
{
    Object gensymed_symbol, sub_class_bit_vector, svref_arg_1, temp_1;
    Object journal_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(133,123);
    if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
	    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	start_new_kb_line();
    if (block_referenced_in_current_save_p(frame) || 
	    block_written_in_current_save_p(frame)) {
	write_char_for_kb(CHR('H'));
	return write_frame_serial_number_for_kb(ISVREF(frame,(SI_Long)3L));
    }
    else {
	increment_frame_reference_balance(frame,Qwrite_reference_to_frame);
	if (ISVREF(Current_saving_context,(SI_Long)3L)) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qui_client_item,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Procedure_invocation_class_description,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    svref_arg_1 = Current_kb_save;
	    temp_1 = copy_frame_serial_number(Current_frame_serial_number);
	    journal_push_modify_macro_arg = journal_cons_1(temp_1,
		    journal_cons_1(frame,Nil));
	    car_1 = journal_push_modify_macro_arg;
	    cdr_1 = ISVREF(svref_arg_1,(SI_Long)39L);
	    svref_new_value = journal_cons_1(car_1,cdr_1);
	    SVREF(svref_arg_1,FIX((SI_Long)39L)) = svref_new_value;
	}
	set_block_referenced_in_current_save(frame,T);
	write_char_for_kb(CHR('G'));
	write_frame_serial_number_for_kb(ISVREF(frame,(SI_Long)3L));
	if (FIXNUM_GT(ISVREF(Current_kb_save,(SI_Long)29L),
		Number_of_characters_beyond_which_to_start_a_new_saved_kb_line))
	    start_new_kb_line();
	return write_symbol_for_kb(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)1L),T);
    }
}

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

/* WRITE-SLOT-GROUP-FOR-BLOCK? */
Object write_slot_group_for_block_qm varargs_1(int, n)
{
    Object block, slot_group_for_block_qm;
    Object as_ghost_qm, gensymed_symbol, connections, collectable_connections;
    Object collectable_subblocks, temp, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(133,124);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    slot_group_for_block_qm = REQUIRED_ARG_nonrelocating();
    as_ghost_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (slot_group_for_block_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	connections = downgrade_connections(gensymed_symbol);
	collectable_connections = connections &&  
		!TRUEP(ISVREF(Current_saving_context,(SI_Long)3L)) ? 
		clip_transients_from_connections(connections) : connections;
	if (as_ghost_qm)
	    collectable_subblocks = Nil;
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    collectable_subblocks = 
		    copy_collectable_blocks_for_subblocks(gensymed_symbol);
	}
	write_char_for_kb(CHR('L'));
	if (as_ghost_qm)
	    temp = FIX((SI_Long)0L);
	else {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	}
	write_fixnum_for_kb(temp);
	if (as_ghost_qm)
	    temp = FIX((SI_Long)0L);
	else {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	}
	write_fixnum_for_kb(temp);
	if (as_ghost_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	    if (temp_1 ? TRUEP(ISVREF(block,(SI_Long)16L)) : TRUEP(Nil)) {
		temp = getfq_function_no_default(ISVREF(block,
			(SI_Long)17L),Qwidth);
		if (temp);
		else
		    temp = ISVREF(ISVREF(block,(SI_Long)16L),(SI_Long)1L);
	    }
	    else {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    }
	}
	else {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	}
	write_fixnum_for_kb(temp);
	if (as_ghost_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	    if (temp_1 ? TRUEP(ISVREF(block,(SI_Long)16L)) : TRUEP(Nil)) {
		temp = getfq_function_no_default(ISVREF(block,
			(SI_Long)17L),Qheight);
		if (temp);
		else
		    temp = ISVREF(ISVREF(block,(SI_Long)16L),(SI_Long)2L);
	    }
	    else {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    }
	}
	else {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	}
	write_fixnum_for_kb(temp);
	if (collectable_subblocks || collectable_connections)
	    write_element_for_kb(collectable_subblocks);
	if (collectable_connections)
	    write_element_for_kb(collectable_connections);
	write_char_for_kb(CHR('R'));
	reclaim_gensym_list_1(collectable_subblocks);
	if ( !TRUEP(ISVREF(Current_saving_context,(SI_Long)3L)) && 
		collectable_connections)
	    reclaim_gensym_list_1(collectable_connections);
	return reclaim_slot_value_list_1(connections);
    }
    else
	return write_element_for_kb(Nil);
}

/* WRITE-DOUBLE-FLOAT-FOR-KB */
Object write_double_float_for_kb(double_float)
    Object double_float;
{
    Object temp_1, x1, x2, x3, x4;
    SI_Long b0, b1, b2, b3;
    char temp;
    double arg, arg_1, arg_2, temp_2;
    Object result;

    x_note_fn_call(133,125);
    if ( !TRUEP(exceptional_float_p(double_float))) {
	arg = -1.6777216E+7;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(double_float);
	arg_2 = 1.6777215E+7;
	temp = arg < arg_1 && arg_1 < arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) ?  
		!inline_nanp_for_comparison(arg_2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = lftruncate(double_float,_);
	temp = NUM_EQ(double_float,temp_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	write_char_for_kb(CHR('M'));
	return write_fixnum_for_kb(ltruncate(double_float,_));
    }
    else {
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(double_float);
	g2ext_foreign_partition_float(temp_2,
		UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	MVS_4(result,x1,x2,x3,x4);
	write_char_for_kb(CHR('P'));
	write_binary_word_for_kb(x1,x2);
	return write_binary_word_for_kb(x3,x4);
    }
}

/* DELETE-KB-OBJECT-INDEX-PROPERTY-NAMES */
Object delete_kb_object_index_property_names(property_name,symbol_list)
    Object property_name, symbol_list;
{
    Object symbol, ab_loop_list_, l_trailer_qm, l, temp;

    x_note_fn_call(133,126);
    symbol = Nil;
    ab_loop_list_ = symbol_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    l_trailer_qm = Nil;
    l = SYMBOL_PLIST(symbol);
  next_loop_1:
    if ( !TRUEP(l))
	goto end_loop_1;
    if (EQ(CAR(l),property_name)) {
	if (l_trailer_qm) {
	    temp = CDDR(l);
	    M_CDR(l_trailer_qm) = temp;
	}
	else {
	    temp = CDDR(l);
	    SET_SYMBOL_PLIST(symbol,temp);
	}
	M_CDDR(l) = Nil;
	reclaim_gensym_list_1(l);
	goto end_loop_1;
    }
    l_trailer_qm = CDR(l);
    l = CDR(l_trailer_qm);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qsystem_version;     /* system-version */

static Object Qtimestamp;          /* timestamp */

static Object Qbase_time;          /* base-time */

static Object Qstart_time;         /* start-time */

static Object Qkb_name;            /* kb-name */

static Object Qab_current_frame_serial_number;  /* current-frame-serial-number */

static Object Qtype_of_file;       /* type-of-file */

static Object Qkb_save;            /* kb-save */

static Object Qsave_kb;            /* save-kb */

static Object Qkb_save_with_runtine_data;  /* kb-save-with-runtine-data */

static Object Qsave_kb_with_runtine_data;  /* save-kb-with-runtine-data */

static Object Qjournal;            /* journal */

static Object Qclass_hierarchy_flags;  /* class-hierarchy-flags */

static Object Qgraphics_tuning_bits;  /* graphics-tuning-bits */

static Object Qperformance_tuning_bits;  /* performance-tuning-bits */

static Object Qreal_time;          /* real-time */

static Object Qsimulated_time;     /* simulated-time */

static Object Qtop_level_module;   /* top-level-module */

static Object Qrequired_modules;   /* required-modules */

/* WRITE-INITIAL-PLIST */
Object write_initial_plist(kb_name)
    Object kb_name;
{
    volatile Object clean_version;
    Object plist, gensymed_symbol, gensymed_symbol_1, car_new_value, fsn;
    Object module_information_table_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(133,127);
    SAVE_STACK();
    clean_version = Qunbound_in_protected_let;
    plist = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	clean_version = copy_for_slot_value(Ok_file_saving_mode_qm ? 
		make_system_version_for_ok_file() : Current_system_version);
	gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)18L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qsystem_version;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = clean_version;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qkb_flags;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = Ok_file_saving_mode_qm ? 
		make_kb_flags_for_ok_file() : Kb_flags_for_saving;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qtimestamp;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qbase_time;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = Gensym_base_time_as_managed_float;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qstart_time;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = Gensym_time_at_start;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qgensym_time;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = Gensym_time;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qkb_name;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = kb_name;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qab_current_frame_serial_number;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	fsn = Current_frame_serial_number;
	car_new_value = FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),
		M_CDR(fsn));
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qtype_of_file;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	if (EQ(ISVREF(Current_saving_context_qm,(SI_Long)2L),Qkb_save))
	    car_new_value = Qsave_kb;
	else if (EQ(ISVREF(Current_saving_context_qm,(SI_Long)2L),
		Qkb_save_with_runtine_data))
	    car_new_value = Qsave_kb_with_runtine_data;
	else if ( !TRUEP(ISVREF(Current_saving_context_qm,(SI_Long)2L)))
	    car_new_value = Qjournal;
	else
	    car_new_value = ISVREF(Current_saving_context_qm,(SI_Long)2L);
	M_CAR(gensymed_symbol_1) = car_new_value;
	plist = gensymed_symbol;
	if (SEVENTH(Consistency_tree_focus_shifts))
	    plist = nconc2(plist,slot_value_list_2(Qclass_hierarchy_flags,
		    SEVENTH(Consistency_tree_focus_shifts)));
	if (Evaluator_tradeoff_info)
	    plist = nconc2(plist,slot_value_list_2(Qgraphics_tuning_bits,
		    Evaluator_tradeoff_info));
	if (Drawing_task_tuning_info)
	    plist = nconc2(plist,
		    slot_value_list_2(Qperformance_tuning_bits,
		    Drawing_task_tuning_info));
	if ( !EQ(Qreal_time,ISVREF(Timing_parameters,(SI_Long)22L)))
	    nconc2(plist,slot_value_list_2(Qsimulated_time,Gensym_time));
	module_information_table_qm = ISVREF(Current_kb_save,(SI_Long)37L) 
		? lookup_kb_specific_property_value(ISVREF(Current_kb_save,
		(SI_Long)37L),
		Module_information_instance_for_module_qm_kbprop) : Nil;
	if (module_information_table_qm) {
	    if (ISVREF(module_information_table_qm,(SI_Long)23L))
		nconc2(plist,slot_value_list_2(Qtop_level_module,
			ISVREF(module_information_table_qm,(SI_Long)23L)));
	    if (ISVREF(module_information_table_qm,(SI_Long)24L))
		nconc2(plist,slot_value_list_2(Qrequired_modules,
			ISVREF(module_information_table_qm,(SI_Long)24L)));
	}
	write_source_code_comment_if_any_for_kb();
	write_char_for_kb(CHR('J'));
	write_element_for_kb(plist);
	SAVE_VALUES(reclaim_slot_value_list_1(plist));
    }
    POP_UNWIND_PROTECT(0);
    if (clean_version) {
	if ( !EQ(clean_version,Qunbound_in_protected_let))
	    reclaim_slot_value(clean_version);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qparagraph;          /* paragraph */

static Object Qnewline;            /* newline */

static Object Qlinefeed;           /* linefeed */

/* WRITE-SOURCE-CODE-COMMENT-IF-ANY-FOR-KB */
Object write_source_code_comment_if_any_for_kb()
{
    Object saving_parameters_instance_qm, temp, kb_file_comment_text_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object output_string_start, ab_end_line_index_qm;
    Object ab_end_character_index_qm, ab_suppress_lost_spaces_at_end_qm;
    Object ab_text_line, ab_lost_space_at_end_of_line, ab_next_text_tail_qm;
    Object ab_explicit_paragraph_or_newline_qm, ab_text_, ab_this_text_tail_qm;
    Object indentation_if_new_qm, character_2, s, temp_4, schar_arg_2;
    Object schar_new_value, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    Object gensymed_symbol_7;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, character_1;
    SI_Long ab_line_index, ab_character_index, ab_line_length;
    SI_Long ab_current_indentation, temp_1, temp_2, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_, thing;
    char temp_3;
    Declare_special(5);
    Object result;

    x_note_fn_call(133,128);
    saving_parameters_instance_qm = ISVREF(Current_kb_save,(SI_Long)37L) ? 
	    get_system_table_instance_for_module(Qsaving_parameters,
	    ISVREF(Current_kb_save,(SI_Long)37L)) : Saving_parameters;
    if (saving_parameters_instance_qm) {
	temp = get_slot_value_function(saving_parameters_instance_qm,
		Qkb_file_comment,Nil);
	kb_file_comment_text_qm = CDR(temp);
    }
    else
	kb_file_comment_text_qm = Nil;
    if (kb_file_comment_text_qm) {
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
		  output_string_start = Fill_pointer_for_current_wide_string;
		  character_1 = (SI_Long)0L;
		  temp = Nil;
		  if (temp);
		  else
		      temp = FIX((SI_Long)1L);
		  ab_line_index = IFIX(temp);
		  temp = Nil;
		  if (temp);
		  else
		      temp = FIX((SI_Long)0L);
		  ab_character_index = IFIX(temp);
		  ab_end_line_index_qm = Nil;
		  if (ab_end_line_index_qm);
		  else
		      ab_end_line_index_qm = Nil;
		  ab_end_character_index_qm = Nil;
		  if (ab_end_character_index_qm);
		  else
		      ab_end_character_index_qm = Nil;
		  ab_suppress_lost_spaces_at_end_qm = Nil;
		  if (ab_suppress_lost_spaces_at_end_qm);
		  else
		      ab_suppress_lost_spaces_at_end_qm = Nil;
		  ab_text_line = Nil;
		  ab_line_length = (SI_Long)0L;
		  ab_lost_space_at_end_of_line = Nil;
		  ab_next_text_tail_qm = Nil;
		  ab_current_indentation = (SI_Long)0L;
		  ab_explicit_paragraph_or_newline_qm = Nil;
		  ab_text_ = kb_file_comment_text_qm;
		  ab_this_text_tail_qm = Nil;
		  if ( !TRUEP(ab_this_text_tail_qm))
		      ab_this_text_tail_qm = 
			      find_text_tail_for_line(ab_text_,
			      FIX(ab_line_index));
		  result = get_next_text_line(ab_this_text_tail_qm);
		  MVS_4(result,ab_text_line,temp,
			  ab_lost_space_at_end_of_line,ab_next_text_tail_qm);
		  ab_line_length = IFIX(temp);
		next_loop:
		  if (ab_end_line_index_qm && ab_line_index == 
			  IFIX(ab_end_line_index_qm) ||  
			  !TRUEP(ab_next_text_tail_qm)) {
		      temp_1 = ab_character_index;
		      if (ab_suppress_lost_spaces_at_end_qm)
			  temp_2 = ab_line_length;
		      else {
			  gensymed_symbol = ab_line_length;
			  gensymed_symbol_1 = 
				  FIXNUMP(ab_lost_space_at_end_of_line) ? 
				  IFIX(ab_lost_space_at_end_of_line) : 
				  IFIX(text_string_length(ab_lost_space_at_end_of_line));
			  temp_2 = gensymed_symbol + gensymed_symbol_1;
		      }
		      temp_3 = temp_1 >= temp_2;
		      if (temp_3);
		      else
			  temp_3 = ab_end_character_index_qm ? 
				  ab_character_index >= 
				  IFIX(ab_end_character_index_qm) : 
				  TRUEP(Qnil);
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  if (temp_3)
		      goto end_loop;
		  indentation_if_new_qm = Nil;
		  character_2 = Nil;
		next_loop_1:
		  if (ab_character_index >= ab_line_length) {
		      temp_2 = ab_character_index - ab_line_length;
		      if (temp_2 < (FIXNUMP(ab_lost_space_at_end_of_line) ?
			       IFIX(ab_lost_space_at_end_of_line) : 
			      IFIX(text_string_length(ab_lost_space_at_end_of_line)))) 
				  {
			  character_2 = 
				  FIXNUMP(ab_lost_space_at_end_of_line) ? 
				  FIX((SI_Long)32L) : 
				  FIX(UBYTE_16_ISAREF_1(ab_lost_space_at_end_of_line,
				  ab_character_index - ab_line_length));
			  ab_character_index = ab_character_index + 
				  (SI_Long)1L;
			  goto end_loop_1;
		      }
		      if ( !TRUEP(ab_next_text_tail_qm)) {
			  ab_explicit_paragraph_or_newline_qm = Nil;
			  character_2 = Nil;
			  character_1 = IFIX(character_2);
			  goto end_1;
		      }
		      ab_this_text_tail_qm = ab_next_text_tail_qm;
		      ab_line_index = ab_line_index + (SI_Long)1L;
		      ab_character_index = (SI_Long)0L;
		      result = get_next_text_line(ab_next_text_tail_qm);
		      MVS_5(result,ab_text_line,temp,
			      ab_lost_space_at_end_of_line,
			      ab_next_text_tail_qm,indentation_if_new_qm);
		      ab_line_length = IFIX(temp);
		      if (indentation_if_new_qm)
			  ab_current_indentation = IFIX(indentation_if_new_qm);
		  }
		  else {
		      temp = FIX(UBYTE_16_ISAREF_1(ab_text_line,
			      ab_character_index));
		      ab_character_index = ab_character_index + (SI_Long)1L;
		      character_2 = temp;
		      goto end_loop_1;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp = character_2;
		  if (! !(FIXNUM_LE(FIX((SI_Long)-32768L),temp) && 
			  FIXNUM_LE(temp,FIX((SI_Long)32767L))))
		      switch (INTEGER_TO_SHORT(temp)) {
			case 8233:
			  ab_explicit_paragraph_or_newline_qm = Qparagraph;
			  break;
			case 8232:
			  ab_explicit_paragraph_or_newline_qm = Qnewline;
			  break;
			case 13:
			  ab_explicit_paragraph_or_newline_qm = Qreturn;
			  break;
			case 10:
			  ab_explicit_paragraph_or_newline_qm = Qlinefeed;
			  break;
			default:
			  break;
		      }
		  character_1 = IFIX(character_2);
		  goto end_1;
		  character_1 = IFIX(Qnil);
		end_1:;
		  if (newline_p(FIX(character_1))) {
		      s = export_text_string(4,Current_wide_string,
			      Qkb_file_comment,output_string_start,
			      Fill_pointer_for_current_wide_string);
		      write_char_for_kb(CHR(';'));
		      write_char_for_kb(CHR(' '));
		      i = (SI_Long)0L;
		      ab_loop_bind_ = IFIX(length(s));
		    next_loop_2:
		      if (i >= ab_loop_bind_)
			  goto end_loop_2;
		      write_char_for_kb(CHR(ICHAR(s,i)));
		      i = i + (SI_Long)1L;
		      goto next_loop_2;
		    end_loop_2:;
		      reclaim_gensym_string(s);
		      output_string_start = 
			      Fill_pointer_for_current_wide_string;
		      start_new_kb_line();
		  }
		  else if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = character_1;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp_4 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = character_1;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp_4,schar_arg_2,schar_new_value);
		      temp_4 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_4;
		  }
		  goto next_loop;
		end_loop:
		  if ( !FIXNUM_EQ(Fill_pointer_for_current_wide_string,
			  output_string_start)) {
		      s = export_text_string(4,Current_wide_string,
			      Qkb_file_comment,output_string_start,
			      Fill_pointer_for_current_wide_string);
		      write_char_for_kb(CHR(';'));
		      write_char_for_kb(CHR(' '));
		      i = (SI_Long)0L;
		      ab_loop_bind_ = IFIX(length(s));
		    next_loop_3:
		      if (i >= ab_loop_bind_)
			  goto end_loop_3;
		      write_char_for_kb(CHR(ICHAR(s,i)));
		      i = i + (SI_Long)1L;
		      goto next_loop_3;
		    end_loop_3:;
		      reclaim_gensym_string(s);
		      output_string_start = 
			      Fill_pointer_for_current_wide_string;
		      start_new_kb_line();
		  }
		  result = VALUES_1(Qnil);
		  MVS_6(result,gensymed_symbol_2,gensymed_symbol_3,
			  gensymed_symbol_4,gensymed_symbol_5,
			  gensymed_symbol_6,gensymed_symbol_7);
		  reclaim_wide_string(Current_wide_string);
		  result = VALUES_6(gensymed_symbol_2,gensymed_symbol_3,
			  gensymed_symbol_4,gensymed_symbol_5,
			  gensymed_symbol_6,gensymed_symbol_7);
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

static Object Qfinal_frame_serial_number;  /* final-frame-serial-number */

static Object Qindex_displacement;  /* index-displacement */

static Object Qreclaimed_index_count;  /* reclaimed-index-count */

static Object Qdetail_pane_description;  /* detail-pane-description */

static Object Qnumeric_symbols;    /* numeric-symbols */

/* WRITE-FINAL-PLIST */
Object write_final_plist(pane_description_qm,timestamp)
    Object pane_description_qm, timestamp;
{
    Object gensymed_symbol, gensymed_symbol_1, fsn, car_new_value, code;
    Object temp_2, plist;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, temp_1, gensymed_symbol_4;
    SI_Long car_new_value_1;
    char temp;

    x_note_fn_call(133,129);
    start_new_kb_line();
    write_char_for_kb(CHR('E'));
    if (pane_description_qm)
	pane_description_qm = 
		check_pane_description_for_unwritten_workspaces(pane_description_qm);
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qfinal_frame_serial_number;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    fsn = Current_frame_serial_number;
    car_new_value = FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qindex_displacement;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = timestamp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qreclaimed_index_count;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    if (temp)
	gensymed_symbol_2 = (SI_Long)1L;
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
	if (temp)
	    gensymed_symbol_2 = (SI_Long)2L;
	else {
	    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
	    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != 
		    (SI_Long)0L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = 
			TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
	    if (temp)
		gensymed_symbol_2 = (SI_Long)3L;
	    else
		gensymed_symbol_2 = (SI_Long)0L;
	}
    }
    fsn = Current_frame_serial_number;
    gensymed_symbol_3 = FIXNUMP(fsn) ? IFIX(fsn) : 
	    IFIX(FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)));
    gensymed_symbol_3 =  - gensymed_symbol_3;
    temp_1 = IFIX(c_native_clock_ticks_or_cache(Nil,Nil)) % (SI_Long)16777215L;
    temp_1 = temp_1 / (SI_Long)11L;
    gensymed_symbol_4 = temp_1 * (SI_Long)11L;
    car_new_value_1 = gensymed_symbol_2 + gensymed_symbol_3 + 
	    gensymed_symbol_4;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value_1);
    temp_2 = pane_description_qm ? 
	    slot_value_list_2(Qdetail_pane_description,
	    pane_description_qm) : Nil;
    plist = nconc2(gensymed_symbol,nconc2(temp_2,
	    nconc2(ISVREF(Current_kb_save,(SI_Long)11L) ? 
	    slot_value_list_2(Qnumeric_symbols,ISVREF(Current_kb_save,
	    (SI_Long)11L)) : Nil,ISVREF(Current_kb_save,(SI_Long)35L) ? 
	    slot_value_list_2(Qoriginal_kb_state_plist_written_qm,T) : Nil)));
    write_element_for_kb(plist);
    reclaim_slot_value_list_1(plist);
    write_element_for_kb(ISVREF(Current_kb_save,(SI_Long)23L));
    write_element_for_kb(FIX((SI_Long)0L));
    write_element_for_kb(FIX((SI_Long)0L));
    start_new_kb_line();
    return update_file_progress_for_writing(1,T);
}

/* WRITE-TIMESTAMP-FOR-KB */
Object write_timestamp_for_kb(gensym_time_arg)
    Object gensym_time_arg;
{
    Object delta, temp, temp_1, temp_2, x1, x2, x3, x4;
    SI_Long b0, b1, b2, b3;
    Object result;

    x_note_fn_call(133,130);
    if (ISVREF(Current_kb_save,(SI_Long)36L)) {
	delta = minus(gensym_time_arg,ISVREF(Current_kb_save,(SI_Long)36L));
	if (IFIX(delta) < (SI_Long)0L && IFIX(delta) > (SI_Long)-16777216L) {
	    if (ISVREF(Current_kb_save,(SI_Long)24L)) {
		if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,
			(SI_Long)8L))
		    write_char_for_kb(CHR('\r'));
		temp = Current_kb_save;
		temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
		SVREF(temp,FIX((SI_Long)29L)) = temp_1;
		temp = ISVREF(Current_kb_save,(SI_Long)25L);
		temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
		temp_2 = CHR(' ');
		SET_SCHAR(temp,temp_1,temp_2);
		temp = Current_kb_save;
		temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
		if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
			Write_kb_buffer_length))
		    flush_kb_write_buffer();
	    }
	    else {
		temp = Current_kb_save;
		SVREF(temp,FIX((SI_Long)24L)) = T;
	    }
	    write_fixnum_digits_for_kb(FIXNUM_NEGATE(delta));
	    write_char_for_kb(CHR(')'));
	}
	else if (IFIX(delta) >= (SI_Long)0L && IFIX(delta) < 
		(SI_Long)16777215L) {
	    if (ISVREF(Current_kb_save,(SI_Long)24L)) {
		if (CHAR_EQ(CHR('\n'),CHR(' ')) && ISVREF(Current_kb_save,
			(SI_Long)8L))
		    write_char_for_kb(CHR('\r'));
		temp = Current_kb_save;
		temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
		SVREF(temp,FIX((SI_Long)29L)) = temp_1;
		temp = ISVREF(Current_kb_save,(SI_Long)25L);
		temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
		temp_2 = CHR(' ');
		SET_SCHAR(temp,temp_1,temp_2);
		temp = Current_kb_save;
		temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
		if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
			Write_kb_buffer_length))
		    flush_kb_write_buffer();
	    }
	    else {
		temp = Current_kb_save;
		SVREF(temp,FIX((SI_Long)24L)) = T;
	    }
	    write_fixnum_digits_for_kb(delta);
	    write_char_for_kb(CHR('('));
	}
	else {
	    g2ext_foreign_partition_float((double)IFIX(FIXNUM_MINUS(gensym_time_arg,
		    Gensym_time_at_start)) + 
		    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L),
		    UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	    result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	    MVS_4(result,x1,x2,x3,x4);
	    write_char_for_kb(CHR('&'));
	    write_binary_word_for_kb(x1,x2);
	    write_binary_word_for_kb(x3,x4);
	}
    }
    else {
	g2ext_foreign_partition_float((double)IFIX(FIXNUM_MINUS(gensym_time_arg,
		Gensym_time_at_start)) + DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L),
		UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	MVS_4(result,x1,x2,x3,x4);
	write_char_for_kb(CHR('&'));
	write_binary_word_for_kb(x1,x2);
	write_binary_word_for_kb(x3,x4);
    }
    temp = Current_kb_save;
    return VALUES_1(SVREF(temp,FIX((SI_Long)36L)) = gensym_time_arg);
}

DEFINE_VARIABLE_WITH_SYMBOL(Left_braket_written_qm, Qleft_braket_written_qm);

static Object Qtrend_chart;        /* trend-chart */

/* WRITE-RUNTIME-DATA-FOR-KB */
Object write_runtime_data_for_kb(block,class_1)
    Object block, class_1;
{
    Object gensymed_symbol, sub_class_bit_vector, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(133,131);
    Left_braket_written_qm = Nil;
    gensymed_symbol = lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Parameter_class_description,
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
    if (temp)
	write_parameter_data_for_kb(block);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    write_variable_data_for_kb(block);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Simulation_subtable_class_description,
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		write_simulation_subtable_data_for_kb(block);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
		if (temp) {
		    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			    (SI_Long)1L)) {
			if ( !TRUEP(Left_braket_written_qm)) {
			    write_char_for_kb(CHR('['));
			    Left_braket_written_qm = T;
			}
			write_char_for_kb(CHR('K'));
		    }
		}
		else {
		    gensymed_symbol_4 = 
			    lookup_global_or_kb_specific_property_value(Qtrend_chart,
			    Class_description_gkbprop);
		    if (gensymed_symbol_4) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
		    else
			temp = TRUEP(Nil);
		    if (temp)
			write_trend_chart_data_for_kb(block);
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(G2_array_class_description,
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
			if (temp)
			    write_g2_array_data_for_kb(block);
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(G2_list_class_description,
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
			    if (temp)
				write_g2_list_data_for_kb(block);
			    else {
				gensymed_symbol_4 = 
					lookup_global_or_kb_specific_property_value(Qhash_table,
					Class_description_gkbprop);
				if (gensymed_symbol_4) {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(gensymed_symbol_4,
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
				else
				    temp = TRUEP(Nil);
				if (temp)
				    write_hash_table_data_for_kb(block);
			    }
			}
		    }
		}
	    }
	}
    }
    if (ISVREF(block,(SI_Long)12L)) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	temp = temp ? TRUEP(ISVREF(Current_kb_save,(SI_Long)31L)) : TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	write_relation_instances_for_kb(block);
    return VALUES_1(Nil);
}

/* WRITE-RELATION-INSTANCES-FOR-KB */
Object write_relation_instances_for_kb(block)
    Object block;
{
    Object relation_instances, converted_value_qm, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance, relation_frame, object_frames_for_saving_qm;
    Object ab_less_than_branch_qm_, ab_node_stack__1, ab_current_node__1;
    Object ab_skip_list_p__1, ab_next_node__1, ab_tail_node__1;
    Object ab_current_alist__1, ab_entry_cons__1, object_frame, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, value_to_save_qm;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(133,132);
    relation_instances = ISVREF(block,(SI_Long)12L);
    if (relation_instances) {
	converted_value_qm = Nil;
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_skip_list_form_ = relation_instances;
	ab_binary_tree_form_ = relation_instances;
	gensymed_symbol = CDR(relation_instances);
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
	relation_instance = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	  relation_frame = Nil;
	  object_frames_for_saving_qm = Nil;
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
			  (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
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
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
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
	  relation_instance = M_CDR(ab_entry_cons_);
	  relation_frame = ISVREF(relation_instance,(SI_Long)1L);
	  scope_conses = Scope_conses;
	  ab_node_stack__1 = Nil;
	  ab_current_node__1 = Nil;
	  ab_skip_list_form_ = ISVREF(relation_instance,(SI_Long)2L);
	  ab_binary_tree_form_ = ISVREF(relation_instance,(SI_Long)2L);
	  temp = ISVREF(relation_instance,(SI_Long)2L);
	  gensymed_symbol = CDR(temp);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p__1 = Nil;
	  ab_next_node__1 = Nil;
	  ab_tail_node__1 = Nil;
	  ab_current_alist__1 = Nil;
	  ab_entry_cons__1 = Nil;
	  object_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    if (ab_skip_list_p__1) {
		ab_next_node__1 = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node__1 = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node__1,ab_tail_node__1))
		    ab_next_node__1 = Nil;
	    }
	    else
		ab_next_node__1 = M_CDR(ab_binary_tree_form_);
	  next_loop_2:
	    if (ab_current_alist__1) {
		ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		ab_current_alist__1 = M_CDR(ab_current_alist__1);
	    }
	    else if (ab_skip_list_p__1) {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_next_node__1 = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__1,
			    (SI_Long)0L),(SI_Long)0L));
		    if (EQ(ab_next_node__1,ab_tail_node__1))
			ab_next_node__1 = Nil;
		    ab_entry_cons__1 = 
			    scope_cons(ISVREF(ab_current_node__1,
			    (SI_Long)2L),ISVREF(ab_current_node__1,
			    (SI_Long)3L));
		}
		else
		    ab_current_node__1 = Nil;
	    }
	    else {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node__1,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack__1 = scope_cons(ab_current_node__1,
			    ab_node_stack__1);
		    ab_current_node__1 = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
		}
		else if (ab_node_stack__1) {
		    ab_next_node__1 = ab_node_stack__1;
		    ab_current_node__1 = M_CAR(ab_node_stack__1);
		    ab_node_stack__1 = M_CDR(ab_node_stack__1);
		}
		else
		    ab_current_node__1 = Nil;
		if (ab_current_node__1) {
		    ab_next_node__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_current_alist__1 = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		    ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		    ab_current_alist__1 = M_CDR(ab_current_alist__1);
		}
	    }
	    if ( !TRUEP(ab_current_node__1))
		goto end_loop_3;
	    object_frame = M_CDR(ab_entry_cons__1);
	    if ((SI_Long)0L != (IFIX(ISVREF(object_frame,(SI_Long)4L)) & 
		    (SI_Long)1L) || ISVREF(Current_saving_context,
		    (SI_Long)3L) && (SI_Long)0L != 
		    (IFIX(ISVREF(object_frame,(SI_Long)5L)) & 
		    (SI_Long)262144L)) {
		ab_loopvar__2 = slot_value_cons_1(object_frame,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_2;
	  end_loop_3:
	    object_frames_for_saving_qm = ab_loopvar_;
	    goto end_1;
	    object_frames_for_saving_qm = Qnil;
	  end_1:;
	  POP_SPECIAL();
	  temp = converted_value_qm;
	  converted_value_qm = nconc2(temp,object_frames_for_saving_qm ? 
		  slot_value_cons_1(nconc2(slot_value_list_2(CONSP(relation_instance) 
		  ? FIRST(relation_instance) : ISVREF(relation_instance,
		  (SI_Long)0L),relation_frame),
		  object_frames_for_saving_qm),Nil) : Nil);
	  goto next_loop;
	end_loop_1:
	  value_to_save_qm = converted_value_qm;
	  goto end_2;
	  value_to_save_qm = Qnil;
	end_2:;
	POP_SPECIAL();
    }
    else
	value_to_save_qm = Nil;
    if (value_to_save_qm) {
	if ( !TRUEP(Left_braket_written_qm)) {
	    write_char_for_kb(CHR('['));
	    Left_braket_written_qm = T;
	}
	write_char_for_kb(CHR('R'));
	write_element_for_kb(value_to_save_qm);
	reclaim_slot_value(value_to_save_qm);
    }
    return VALUES_1(Nil);
}

/* WRITE-RUNTIME-DATA-FRAME-MODIFICATION */
Object write_runtime_data_frame_modification(block)
    Object block;
{
    x_note_fn_call(133,133);
    start_new_kb_line();
    write_char_for_kb(CHR('F'));
    write_frame_serial_number_for_kb(ISVREF(block,(SI_Long)3L));
    write_element_for_kb(ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L));
    write_runtime_data_for_kb(block,ISVREF(ISVREF(block,(SI_Long)1L),
	    (SI_Long)1L));
    write_char_for_kb(CHR('!'));
    return VALUES_1(Nil);
}

static Object Qdefinition;         /* definition */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

/* WRITE-ENTANGLED-SLOTS-OF-DEFINITION-AS-FRAME-MODIFICATION */
Object write_entangled_slots_of_definition_as_frame_modification(definition)
    Object definition;
{
    Object entangled_slots, unique_slot_name, ab_loop_list_, slot_description;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    Object relation_instances_slot_description, slot_value_to_save;
    Object vector_slot_index_qm, user_vector_slot_index_qm, slot_name;
    Object lookup_structure_qm, slot_index_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, max_i, i;
    Object result;

    x_note_fn_call(133,134);
    if (get_lookup_slot_value_given_default(definition,Qentangled_slots,Nil)) {
	start_new_kb_line();
	write_char_for_kb(CHR('F'));
	write_frame_serial_number_for_kb(ISVREF(definition,(SI_Long)3L));
	write_element_for_kb(ISVREF(ISVREF(definition,(SI_Long)1L),
		(SI_Long)1L));
	entangled_slots = get_lookup_slot_value_given_default(definition,
		Qentangled_slots,Nil);
	unique_slot_name = Nil;
	ab_loop_list_ = get_lookup_slot_value_given_default(definition,
		Qentangled_slots,Nil);
	slot_description = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	unique_slot_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	slot_description = 
		get_slot_description_of_class_description_function(unique_slot_name,
		ISVREF(definition,(SI_Long)1L),Nil);
	if (EQ(unique_slot_name,Qrelation_instances)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = Qdefinition;
	    key_hash_value = SXHASH_SYMBOL_1(Qdefinition) & 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_2:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_3:
	    if ( !TRUEP(marked))
		goto end_loop_2;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_3;
	  end_loop_2:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qdefinition;
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
	  next_loop_4:
	    if (level < ab_loop_bind_)
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_5:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_6:
	    if ( !TRUEP(marked))
		goto end_loop_5;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_6;
	  end_loop_5:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	      next_loop_7:
		if (level < ab_loop_bind_)
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_8:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_9:
		if ( !TRUEP(marked))
		    goto end_loop_8;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_9;
	      end_loop_8:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	      next_loop_10:
		if (level < ab_loop_bind_)
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_11:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_12:
		if ( !TRUEP(marked))
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_12;
	      end_loop_11:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    relation_instances_slot_description = 
		    get_slot_description_of_class_description_function(Qrelation_instances,
		    gensymed_symbol,Nil);
	    slot_value_to_save = 
		    convert_intermodual_relation_instances_for_saving(definition,
		    ISVREF(definition,(SI_Long)12L));
	    write_slot_for_kb(3,definition,
		    relation_instances_slot_description,slot_value_to_save);
	    reclaim_slot_value(slot_value_to_save);
	}
	else {
	    temp_1 = slot_description;
	    vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	    if (vector_slot_index_qm)
		temp = ISVREF(definition,IFIX(vector_slot_index_qm));
	    else {
		user_vector_slot_index_qm = ISVREF(slot_description,
			(SI_Long)8L);
		if (user_vector_slot_index_qm)
		    temp = ISVREF(ISVREF(definition,(SI_Long)0L),
			    IFIX(user_vector_slot_index_qm));
		else {
		    slot_name = ISVREF(slot_description,(SI_Long)1L);
		    lookup_structure_qm = ISVREF(definition,(SI_Long)0L);
		    if (lookup_structure_qm) {
			max_i = 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
			max_i = max_i - (SI_Long)1L;
			i = IFIX(ISVREF(ISVREF(definition,(SI_Long)1L),
				(SI_Long)15L));
			ab_loop_bind_ = max_i;
		      next_loop_13:
			if (i >= ab_loop_bind_)
			    goto end_loop_13;
			if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			    slot_index_qm = FIX(i + (SI_Long)1L);
			    goto end_5;
			}
			i = i + (SI_Long)2L;
			goto next_loop_13;
		      end_loop_13:
			slot_index_qm = Qnil;
		      end_5:;
			temp = slot_index_qm ? ISVREF(lookup_structure_qm,
				IFIX(slot_index_qm)) : 
				ISVREF(slot_description,(SI_Long)6L);
		    }
		    else
			temp = ISVREF(slot_description,(SI_Long)6L);
		}
	    }
	    write_slot_for_kb(3,definition,temp_1,temp);
	}
	goto next_loop;
      end_loop:
	reclaim_slot_value(entangled_slots);
	set_non_savable_lookup_slot_value(definition,Qentangled_slots,Nil);
	write_char_for_kb(CHR('!'));
    }
    return VALUES_1(Nil);
}

/* REFORMAT-AS-APPROPRIATE */
Object reformat_as_appropriate(block,superblock_will_do_reformatting_qm)
    Object block, superblock_will_do_reformatting_qm;
{
    Object frame, sub_vector_qm, function_qm, temp, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock;
    SI_Long method_index;

    x_note_fn_call(133,135);
    method_index = (SI_Long)28L;
    frame = block;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    temp = function_qm ? inline_funcall_2(function_qm,frame,
	    superblock_will_do_reformatting_qm) : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	reformat_as_appropriate(subblock,Nil);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qformat_change_qm;   /* format-change? */

static Object Qformat_frame;       /* format-frame */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qdefault_text_box_format_name;  /* default-text-box-format-name */

/* FORMAT-FRAME-TO-REFORMAT-BY-IF-ANY */
Object format_frame_to_reformat_by_if_any(block_qm,format_frame)
    Object block_qm, format_frame;
{
    Object format_change_qm, sub_class_bit_vector, format_name, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(133,136);
    format_change_qm = get_lookup_slot_value_given_default(format_frame,
	    Qformat_change_qm,Nil);
    if (format_change_qm) {
	if (INTEGERP(format_change_qm)) {
	    if (block_qm)
		return VALUES_1(format_frame);
	    else
		return VALUES_1(Nil);
	}
	else if (Reformat_as_appropriate_qm)
	    return get_instance_with_name_if_any(Qformat_frame,
		    format_change_qm);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (block_qm &&  
		!TRUEP(get_lookup_slot_value_given_default(format_frame,
		Qname_or_names_for_frame,Nil))) {
	    sub_class_bit_vector = ISVREF(ISVREF(block_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
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
	if (temp ? TRUEP(get_lookup_slot_value(block_qm,
		Qdefault_text_box_format_name)) : TRUEP(Nil)) {
	    format_name = get_lookup_slot_value(block_qm,
		    Qdefault_text_box_format_name);
	    temp_1 = get_instance_with_name_if_any(Qformat_frame,format_name);
	    if (temp_1)
		return VALUES_1(temp_1);
	    else
		return make_format_frame(format_name);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qtable_format;       /* table-format */

static Object Qdone;               /* done */

/* REFORMAT-AS-APPROPRIATE-FOR-TABLE */
Object reformat_as_appropriate_for_table(table,
	    superblock_will_do_reformatting_qm)
    Object table, superblock_will_do_reformatting_qm;
{
    Object table_format_to_reformat_by_qm, reformat_table_qm, row;
    Object ab_loop_list_, cell_qm, ab_loop_list__1;
    Object text_box_format_to_reformat_by_qm;
    char temp;
    Declare_special(1);

    x_note_fn_call(133,137);
    table_format_to_reformat_by_qm = 
	    format_frame_to_reformat_by_if_any(table,ISVREF(table,
	    (SI_Long)16L));
    reformat_table_qm = table_format_to_reformat_by_qm;
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      cell_qm = Nil;
      ab_loop_list__1 = Row;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      cell_qm = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (cell_qm) {
	  if (ATOM(cell_qm))
	      temp = EQ(reformat_as_appropriate(cell_qm,T),Qdo);
	  else {
	      text_box_format_to_reformat_by_qm = 
		      format_frame_to_reformat_by_if_any(table,CAR(cell_qm));
	      if (text_box_format_to_reformat_by_qm)
		  temp = TRUEP(M_CAR(cell_qm) = 
			  text_box_format_to_reformat_by_qm);
	      else
		  temp = TRUEP(Nil);
	  }
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  reformat_table_qm = T;
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    if (table_format_to_reformat_by_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(table,Qtable_format);
	SVREF(table,FIX((SI_Long)16L)) = table_format_to_reformat_by_qm;
    }
    if (reformat_table_qm) {
	if (superblock_will_do_reformatting_qm)
	    return VALUES_1(Qdo);
	else {
	    reformat_table_in_place(1,table);
	    Refresh_all_windows_after_merging_qm = T;
	    return VALUES_1(Qdone);
	}
    }
    else
	return VALUES_1(Qdone);
}

static Object Qtext_box_format;    /* text-box-format */

/* REFORMAT-AS-APPROPRIATE-FOR-TEXT-BOX */
Object reformat_as_appropriate_for_text_box(text_box,
	    superblock_will_do_reformatting_qm)
    Object text_box, superblock_will_do_reformatting_qm;
{
    Object text_box_format_to_reformat_by_qm;

    x_note_fn_call(133,138);
    text_box_format_to_reformat_by_qm = 
	    format_frame_to_reformat_by_if_any(text_box,ISVREF(text_box,
	    (SI_Long)17L));
    if (text_box_format_to_reformat_by_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(text_box,Qtext_box_format);
	SVREF(text_box,FIX((SI_Long)17L)) = text_box_format_to_reformat_by_qm;
	if (superblock_will_do_reformatting_qm)
	    return VALUES_1(Qdo);
	else {
	    reformat_text_box_in_place(2,text_box,Nil);
	    Refresh_all_windows_after_merging_qm = T;
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

void kb_save1_INIT()
{
    Object temp, reclaim_structure_for_kb_transfer_1;
    Object reclaim_structure_for_kb_save_1;
    Object reclaim_structure_for_saving_context_1;
    Object reclaim_structure_for_pseudo_frame_1, temp_1;
    Object Qclasses_which_define, Qreformat_as_appropriate, Qtext_box;
    Object Qreformat_as_appropriate_for_text_box, AB_package, Qtable;
    Object Qreformat_as_appropriate_for_table, Qgeneric_method_lambda_list;
    Object list_constant_9, Qsuperblock_will_do_reformatting_qm, Qkb_save1;
    Object Qfloat_register_2, Qfloat_register_1, Qfixnum_register_2;
    Object Qfixnum_register_1, Qcall_function, Qcall_simple_function;
    Object Qget_variable, Qget_constant, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qpseudo_frame, Qreclaim_structure, Qoutstanding_pseudo_frame_count;
    Object Qpseudo_frame_structure_memory_usage, Qutilities2;
    Object string_constant_67, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_66, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qwin32, Qunix, Qkb_save3;
    Object Qsaving_context, Qoutstanding_saving_context_count;
    Object Qsaving_context_structure_memory_usage, string_constant_65;
    Object string_constant_64, list_constant_8, Qreclaim_gensym_list_function;
    Object Qoutstanding_kb_save_count, Qkb_save_structure_memory_usage;
    Object string_constant_63, string_constant_62;
    Object Qmutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry;
    Object Qout_kb_fsn_hash_table_hash_vector_131_vectors;
    Object Qkb_fsn_hash_table_hash_vector_131_vector_memory_usage;
    Object string_constant_61, Qwrite_kb_buffer_length, Qkb_transfer;
    Object Qoutstanding_kb_transfer_count, Qkb_transfer_structure_memory_usage;
    Object string_constant_60, string_constant_59, list_constant_7;
    Object Qposition_of_vertical_elevator, Qposition_of_horizontal_elevator;
    Object Qremembered_block_transform, Qobject_passing_info_qm;
    Object Qbottom_edge_of_content_of_block_1;
    Object Qright_edge_of_content_of_block_1, Qtop_edge_of_content_of_block_1;
    Object Qleft_edge_of_content_of_block_1, Qwalking_menus;
    Object Qobject_configuration, Quser_annotations, string_constant_58;
    Object Qalpha_or_beta;

    x_note_fn_call(133,139);
    SET_PACKAGE("AB");
    if (Ok_file_saving_mode_qm == UNBOUND)
	Ok_file_saving_mode_qm = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qalpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    string_constant_58 = STATIC_STRING("Rev. 5");
    list_constant = STATIC_LIST((SI_Long)4L,FIX((SI_Long)3L),
	    FIX((SI_Long)0L),Qalpha_or_beta,string_constant_58);
    Quser_annotations = STATIC_SYMBOL("USER-ANNOTATIONS",AB_package);
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qwalking_menus = STATIC_SYMBOL("WALKING-MENUS",AB_package);
    Qleft_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("LEFT-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qtop_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("TOP-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qright_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("RIGHT-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qbottom_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("BOTTOM-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qobject_passing_info_qm = STATIC_SYMBOL("OBJECT-PASSING-INFO\?",
	    AB_package);
    Qremembered_block_transform = 
	    STATIC_SYMBOL("REMEMBERED-BLOCK-TRANSFORM",AB_package);
    Qposition_of_horizontal_elevator = 
	    STATIC_SYMBOL("POSITION-OF-HORIZONTAL-ELEVATOR",AB_package);
    Qposition_of_vertical_elevator = 
	    STATIC_SYMBOL("POSITION-OF-VERTICAL-ELEVATOR",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)11L,Quser_annotations,
	    Qobject_configuration,Qwalking_menus,
	    Qleft_edge_of_content_of_block_1,
	    Qtop_edge_of_content_of_block_1,
	    Qright_edge_of_content_of_block_1,
	    Qbottom_edge_of_content_of_block_1,Qobject_passing_info_qm,
	    Qremembered_block_transform,Qposition_of_horizontal_elevator,
	    Qposition_of_vertical_elevator);
    if (Slots_to_skip_saving_in_ok_files == UNBOUND)
	Slots_to_skip_saving_in_ok_files = list_constant_7;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_kb_transfer_g2_struct = 
	    STATIC_SYMBOL("KB-TRANSFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qkb_transfer = STATIC_SYMBOL("KB-TRANSFER",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_kb_transfer_g2_struct,
	    Qkb_transfer,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qkb_transfer,
	    Qg2_defstruct_structure_name_kb_transfer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_kb_transfer == UNBOUND)
	The_type_description_of_kb_transfer = Nil;
    string_constant_59 = 
	    STATIC_STRING("43Dy8m83DKy1n83DKy8n8k1l8n0000000k3Gyk0k0");
    temp = The_type_description_of_kb_transfer;
    The_type_description_of_kb_transfer = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_59));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_kb_transfer_g2_struct,
	    The_type_description_of_kb_transfer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qkb_transfer,
	    The_type_description_of_kb_transfer,Qtype_description_of_type);
    Qoutstanding_kb_transfer_count = 
	    STATIC_SYMBOL("OUTSTANDING-KB-TRANSFER-COUNT",AB_package);
    Qkb_transfer_structure_memory_usage = 
	    STATIC_SYMBOL("KB-TRANSFER-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_60 = STATIC_STRING("1q83DKy8s83-buy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_kb_transfer_count);
    push_optimized_constant(Qkb_transfer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_60));
    Qchain_of_available_kb_transfers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-KB-TRANSFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_kb_transfers,
	    Chain_of_available_kb_transfers);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_kb_transfers,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qkb_transfer_count = STATIC_SYMBOL("KB-TRANSFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_transfer_count,Kb_transfer_count);
    record_system_variable(Qkb_transfer_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_kb_transfers_vector == UNBOUND)
	Chain_of_available_kb_transfers_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qkb_transfer_structure_memory_usage,
	    STATIC_FUNCTION(kb_transfer_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_kb_transfer_count,
	    STATIC_FUNCTION(outstanding_kb_transfer_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_kb_transfer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_kb_transfer,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qkb_transfer,
	    reclaim_structure_for_kb_transfer_1);
    Qwrite_kb_buffer_length = STATIC_SYMBOL("WRITE-KB-BUFFER-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE(Qwrite_kb_buffer_length,FIX((SI_Long)2048L));
    Qavailable_kb_fsn_hash_table_hash_vector_131_vectors = 
	    STATIC_SYMBOL("AVAILABLE-KB-FSN-HASH-TABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_kb_fsn_hash_table_hash_vector_131_vectors,
	    Available_kb_fsn_hash_table_hash_vector_131_vectors);
    record_system_variable(Qavailable_kb_fsn_hash_table_hash_vector_131_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_kb_fsn_hash_table_hash_vector_131_vectors = 
	    STATIC_SYMBOL("COUNT-OF-KB-FSN-HASH-TABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_kb_fsn_hash_table_hash_vector_131_vectors,
	    Count_of_kb_fsn_hash_table_hash_vector_131_vectors);
    record_system_variable(Qcount_of_kb_fsn_hash_table_hash_vector_131_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_kb_fsn_hash_table_hash_vector_131_vectors_vector == UNBOUND)
	Available_kb_fsn_hash_table_hash_vector_131_vectors_vector = 
		make_thread_array(Nil);
    Qout_kb_fsn_hash_table_hash_vector_131_vectors = 
	    STATIC_SYMBOL("OUT-KB-FSN-HASH-TABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    Qkb_fsn_hash_table_hash_vector_131_vector_memory_usage = 
	    STATIC_SYMBOL("KB-FSN-HASH-TABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_61 = STATIC_STRING("1q83-bny83*9y83-P0y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_kb_fsn_hash_table_hash_vector_131_vectors);
    push_optimized_constant(Qkb_fsn_hash_table_hash_vector_131_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_61));
    SET_SYMBOL_FUNCTION(Qkb_fsn_hash_table_hash_vector_131_vector_memory_usage,
	    STATIC_FUNCTION(kb_fsn_hash_table_hash_vector_131_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_kb_fsn_hash_table_hash_vector_131_vectors,
	    STATIC_FUNCTION(out_kb_fsn_hash_table_hash_vector_131_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-KB-FSN-HASH-TABLE-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_kb_fsn_hash_table_tree_for_hash_skip_list_entry);
    Qframe_serial_number_equal_function = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-EQUAL-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qframe_serial_number_equal_function,
	    STATIC_FUNCTION(frame_serial_number_equal_function,NIL,FALSE,2,2));
    Qkb_fsn_hash_table_tree_for_hash = 
	    STATIC_SYMBOL("KB-FSN-HASH-TABLE-TREE-FOR-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qg2_defstruct_structure_name_kb_save_g2_struct = 
	    STATIC_SYMBOL("KB-SAVE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qkb_save = STATIC_SYMBOL("KB-SAVE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_kb_save_g2_struct,
	    Qkb_save,Qab_name_of_unique_structure_type);
    mutate_global_property(Qkb_save,
	    Qg2_defstruct_structure_name_kb_save_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_kb_save == UNBOUND)
	The_type_description_of_kb_save = Nil;
    string_constant_62 = 
	    STATIC_STRING("43Dy8m83TEy1o83TEy83DKy8n8k1l83DKy0000001m1m8x83DKy1m8y83-4hyk3kyk0k0");
    temp = The_type_description_of_kb_save;
    The_type_description_of_kb_save = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_62));
    mutate_global_property(Qg2_defstruct_structure_name_kb_save_g2_struct,
	    The_type_description_of_kb_save,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qkb_save,The_type_description_of_kb_save,
	    Qtype_description_of_type);
    Qoutstanding_kb_save_count = STATIC_SYMBOL("OUTSTANDING-KB-SAVE-COUNT",
	    AB_package);
    Qkb_save_structure_memory_usage = 
	    STATIC_SYMBOL("KB-SAVE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_63 = STATIC_STRING("1q83TEy8s83-bty09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_kb_save_count);
    push_optimized_constant(Qkb_save_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_63));
    Qchain_of_available_kb_saves = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-KB-SAVES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_kb_saves,
	    Chain_of_available_kb_saves);
    record_system_variable(Qchain_of_available_kb_saves,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qkb_save_count = STATIC_SYMBOL("KB-SAVE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_save_count,Kb_save_count);
    record_system_variable(Qkb_save_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_kb_saves_vector == UNBOUND)
	Chain_of_available_kb_saves_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qkb_save_structure_memory_usage,
	    STATIC_FUNCTION(kb_save_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_kb_save_count,
	    STATIC_FUNCTION(outstanding_kb_save_count,NIL,FALSE,0,0));
    reclaim_structure_for_kb_save_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_kb_save,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qkb_save,
	    reclaim_structure_for_kb_save_1);
    Qframe_reference_balance = STATIC_SYMBOL("FRAME-REFERENCE-BALANCE",
	    AB_package);
    Kkb = STATIC_SYMBOL("KB",Pkeyword);
    Qkb_object_index_property_name_pool = 
	    STATIC_SYMBOL("KB-OBJECT-INDEX-PROPERTY-NAME-POOL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_object_index_property_name_pool,
	    Kb_object_index_property_name_pool);
    Qkb_save1 = STATIC_SYMBOL("KB-SAVE1",AB_package);
    Qreclaim_gensym_list_function = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-LIST-FUNCTION",AB_package);
    record_system_variable(Qkb_object_index_property_name_pool,Qkb_save1,
	    Nil,Qnil,Qt,Qreclaim_gensym_list_function,Qt);
    if (Next_object_index_property_number == UNBOUND)
	Next_object_index_property_number = FIX((SI_Long)0L);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    string_constant = STATIC_STRING("OBJECT-INDEX-PROPERTY-~d");
    Qclear_text = STATIC_SYMBOL("CLEAR-TEXT",AB_package);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qg2_defstruct_structure_name_saving_context_g2_struct = 
	    STATIC_SYMBOL("SAVING-CONTEXT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsaving_context = STATIC_SYMBOL("SAVING-CONTEXT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_saving_context_g2_struct,
	    Qsaving_context,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsaving_context,
	    Qg2_defstruct_structure_name_saving_context_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_saving_context == UNBOUND)
	The_type_description_of_saving_context = Nil;
    string_constant_64 = 
	    STATIC_STRING("43Dy8m83mcy1n83mcy8n8k1l8n0000001l1n8y83-5ey1q83-2Jy83-FRy83-CFy83-CGy83-CIy83-CHykvk0k0");
    temp = The_type_description_of_saving_context;
    The_type_description_of_saving_context = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_64));
    mutate_global_property(Qg2_defstruct_structure_name_saving_context_g2_struct,
	    The_type_description_of_saving_context,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsaving_context,
	    The_type_description_of_saving_context,Qtype_description_of_type);
    Qoutstanding_saving_context_count = 
	    STATIC_SYMBOL("OUTSTANDING-SAVING-CONTEXT-COUNT",AB_package);
    Qsaving_context_structure_memory_usage = 
	    STATIC_SYMBOL("SAVING-CONTEXT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_65 = STATIC_STRING("1q83mcy8s83-nTy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_saving_context_count);
    push_optimized_constant(Qsaving_context_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_65));
    Qchain_of_available_saving_contexts = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SAVING-CONTEXTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_saving_contexts,
	    Chain_of_available_saving_contexts);
    record_system_variable(Qchain_of_available_saving_contexts,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qsaving_context_count = STATIC_SYMBOL("SAVING-CONTEXT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaving_context_count,Saving_context_count);
    record_system_variable(Qsaving_context_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_saving_contexts_vector == UNBOUND)
	Chain_of_available_saving_contexts_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsaving_context_structure_memory_usage,
	    STATIC_FUNCTION(saving_context_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_saving_context_count,
	    STATIC_FUNCTION(outstanding_saving_context_count,NIL,FALSE,0,0));
    reclaim_structure_for_saving_context_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_saving_context,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qsaving_context,
	    reclaim_structure_for_saving_context_1);
    Qnever_opened = STATIC_SYMBOL("NEVER-OPENED",AB_package);
    Qcurrent_saving_context_qm = STATIC_SYMBOL("CURRENT-SAVING-CONTEXT\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_saving_context_qm,
	    Current_saving_context_qm);
    Qkb_save3 = STATIC_SYMBOL("KB-SAVE3",AB_package);
    record_system_variable(Qcurrent_saving_context_qm,Qkb_save3,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcontinuation_task_for_current_backup = 
	    STATIC_SYMBOL("CONTINUATION-TASK-FOR-CURRENT-BACKUP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcontinuation_task_for_current_backup,
	    Continuation_task_for_current_backup);
    record_system_variable(Qcontinuation_task_for_current_backup,Qkb_save3,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Number_of_characters_beyond_which_to_start_a_new_saved_kb_line = 
	    FIX((SI_Long)60L);
    Number_of_characters_beyond_which_to_start_a_new_saved_compiled_line = 
	    FIX((SI_Long)100L);
    Number_of_characters_beyond_which_to_start_a_new_saved_compiled_file = 
	    FIX((SI_Long)400000L);
    Number_of_characters_at_which_to_break_a_character_sequence = 
	    FIX((SI_Long)75L);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    string_constant_1 = STATIC_STRING("/*");
    string_constant_2 = STATIC_STRING("*/");
    Minus_most_negative_int64_ash_minus_5 = ltimes(FIX((SI_Long)256L),
	    ltimes(FIX((SI_Long)33554432L),FIX((SI_Long)33554432L)));
    Qtype_of_syntactic_anomaly = STATIC_SYMBOL("TYPE-OF-SYNTACTIC-ANOMALY",
	    AB_package);
    Qnumeric = STATIC_SYMBOL("NUMERIC",AB_package);
    Qmodules_this_format_frame_has_been_referenced_in = 
	    STATIC_SYMBOL("MODULES-THIS-FORMAT-FRAME-HAS-BEEN-REFERENCED-IN",
	    AB_package);
    Qcomputation_style = STATIC_SYMBOL("COMPUTATION-STYLE",AB_package);
    Qmodules_this_computation_style_has_been_referenced_in = 
	    STATIC_SYMBOL("MODULES-THIS-COMPUTATION-STYLE-HAS-BEEN-REFERENCED-IN",
	    AB_package);
    Qmodules_this_format_frame_has_been_written_in = 
	    STATIC_SYMBOL("MODULES-THIS-FORMAT-FRAME-HAS-BEEN-WRITTEN-IN",
	    AB_package);
    Qmodules_this_computation_style_has_been_written_in = 
	    STATIC_SYMBOL("MODULES-THIS-COMPUTATION-STYLE-HAS-BEEN-WRITTEN-IN",
	    AB_package);
    Debug_frame_reference_balance_qm = Nil;
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunix,Qwin32);
    string_constant_3 = STATIC_STRING("~a~~");
    Qsaving_parameters = STATIC_SYMBOL("SAVING-PARAMETERS",AB_package);
    Qidentifier_of_basis_kb = STATIC_SYMBOL("IDENTIFIER-OF-BASIS-KB",
	    AB_package);
    Qfilename_of_basis_kb = STATIC_SYMBOL("FILENAME-OF-BASIS-KB",AB_package);
    Qkb_file_comment = STATIC_SYMBOL("KB-FILE-COMMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaving_parameters,Saving_parameters);
    string_constant_4 = STATIC_STRING("~a ~a ");
    Qrelation_is_permanent = STATIC_SYMBOL("RELATION-IS-PERMANENT",AB_package);
    if (Frame_for_write_frame_for_kb == UNBOUND)
	Frame_for_write_frame_for_kb = Nil;
    if (Slot_name_for_write_frame_for_kb == UNBOUND)
	Slot_name_for_write_frame_for_kb = Nil;
    if (Slot_value_for_write_frame_for_kb == UNBOUND)
	Slot_value_for_write_frame_for_kb = Nil;
    Qwrite_frame_for_kb = STATIC_SYMBOL("WRITE-FRAME-FOR-KB",AB_package);
    Qruntime_data_only = STATIC_SYMBOL("RUNTIME-DATA-ONLY",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qsubworkspaces = STATIC_SYMBOL("SUBWORKSPACES",AB_package);
    Qframe_representations = STATIC_SYMBOL("FRAME-REPRESENTATIONS",AB_package);
    Qicon_attributes_plist = STATIC_SYMBOL("ICON-ATTRIBUTES-PLIST",AB_package);
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrelation_instances = STATIC_SYMBOL("RELATION-INSTANCES",AB_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qentangled_slots = STATIC_SYMBOL("ENTANGLED-SLOTS",AB_package);
    Qoriginal_kb_state_plist = STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST",
	    AB_package);
    Qlist_structure = STATIC_SYMBOL("LIST-STRUCTURE",AB_package);
    Qmanaged_g2_array = STATIC_SYMBOL("MANAGED-G2-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_frame_for_kb,
	    STATIC_FUNCTION(write_frame_for_kb,NIL,TRUE,2,3));
    Qg2_defstruct_structure_name_pseudo_frame_g2_struct = 
	    STATIC_SYMBOL("PSEUDO-FRAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpseudo_frame = STATIC_SYMBOL("PSEUDO-FRAME",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_pseudo_frame_g2_struct,
	    Qpseudo_frame,Qab_name_of_unique_structure_type);
    mutate_global_property(Qpseudo_frame,
	    Qg2_defstruct_structure_name_pseudo_frame_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_pseudo_frame == UNBOUND)
	The_type_description_of_pseudo_frame = Nil;
    string_constant_66 = 
	    STATIC_STRING("43Dy8m83lpy1n83lpy8n8k1l8n0000001l1n8y83-5Cy1m83-9ay83-9Zyknk0k0");
    temp = The_type_description_of_pseudo_frame;
    The_type_description_of_pseudo_frame = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_66));
    mutate_global_property(Qg2_defstruct_structure_name_pseudo_frame_g2_struct,
	    The_type_description_of_pseudo_frame,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qpseudo_frame,
	    The_type_description_of_pseudo_frame,Qtype_description_of_type);
    Qoutstanding_pseudo_frame_count = 
	    STATIC_SYMBOL("OUTSTANDING-PSEUDO-FRAME-COUNT",AB_package);
    Qpseudo_frame_structure_memory_usage = 
	    STATIC_SYMBOL("PSEUDO-FRAME-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_67 = STATIC_STRING("1q83lpy8s83-kfy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_pseudo_frame_count);
    push_optimized_constant(Qpseudo_frame_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_67));
    Qchain_of_available_pseudo_frames = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PSEUDO-FRAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_pseudo_frames,
	    Chain_of_available_pseudo_frames);
    record_system_variable(Qchain_of_available_pseudo_frames,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qpseudo_frame_count = STATIC_SYMBOL("PSEUDO-FRAME-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpseudo_frame_count,Pseudo_frame_count);
    record_system_variable(Qpseudo_frame_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_pseudo_frames_vector == UNBOUND)
	Chain_of_available_pseudo_frames_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qpseudo_frame_structure_memory_usage,
	    STATIC_FUNCTION(pseudo_frame_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_pseudo_frame_count,
	    STATIC_FUNCTION(outstanding_pseudo_frame_count,NIL,FALSE,0,0));
    reclaim_structure_for_pseudo_frame_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_pseudo_frame,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qpseudo_frame,
	    reclaim_structure_for_pseudo_frame_1);
    Qstack_of_subblocks = STATIC_SYMBOL("STACK-OF-SUBBLOCKS",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qcolumn_of_args = STATIC_SYMBOL("COLUMN-OF-ARGS",AB_package);
    Qcolumn_of_values = STATIC_SYMBOL("COLUMN-OF-VALUES",AB_package);
    Qnumber_of_rows_in_table = STATIC_SYMBOL("NUMBER-OF-ROWS-IN-TABLE",
	    AB_package);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qframe_denotation = STATIC_SYMBOL("FRAME-DENOTATION",AB_package);
    Qg2gl_variable_compilation = STATIC_SYMBOL("G2GL-VARIABLE-COMPILATION",
	    AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_byte_code_body_g2_struct = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_user_mode_alias_g2_struct = 
	    STATIC_SYMBOL("USER-MODE-ALIAS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_5 = 
	    STATIC_STRING("Illegal vector (starting with ~A) encountered while trying to save KB");
    if (Compiled_kb_indent == UNBOUND)
	Compiled_kb_indent = FIX((SI_Long)0L);
    string_constant_6 = STATIC_STRING("default:");
    string_constant_7 = STATIC_STRING("case ");
    Kdouble = STATIC_SYMBOL("DOUBLE",Pkeyword);
    Kint = STATIC_SYMBOL("INT",Pkeyword);
    Kobject = STATIC_SYMBOL("OBJECT",Pkeyword);
    Qcompiled_function_in_place = 
	    STATIC_SYMBOL("COMPILED-FUNCTION-IN-PLACE",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Kboolean = STATIC_SYMBOL("BOOLEAN",Pkeyword);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qab_let_star = STATIC_SYMBOL("LET*",AB_package);
    Qife = STATIC_SYMBOL("IFE",AB_package);
    string_constant_8 = STATIC_STRING("FIX(");
    string_constant_9 = STATIC_STRING(")");
    string_constant_10 = STATIC_STRING("(");
    string_constant_11 = STATIC_STRING(" \? T : Nil)");
    string_constant_12 = STATIC_STRING("DOUBLE_TO_DOUBLE_FLOAT(");
    string_constant_13 = STATIC_STRING("(IFIX(");
    string_constant_14 = STATIC_STRING("))");
    string_constant_15 = STATIC_STRING("((");
    string_constant_16 = STATIC_STRING(") != Nil)");
    string_constant_17 = STATIC_STRING("T");
    string_constant_18 = STATIC_STRING("DOUBLE_FLOAT_TO_DOUBLE(");
    string_constant_19 = STATIC_STRING(" = ");
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qab_or,Qand);
    string_constant_20 = STATIC_STRING(" || ");
    string_constant_21 = STATIC_STRING(" && ");
    string_constant_22 = STATIC_STRING(", ");
    string_constant_23 = STATIC_STRING(" \? ");
    string_constant_24 = STATIC_STRING(" : ");
    string_constant_25 = STATIC_STRING("STATIC_SYMBOL(\"");
    string_constant_26 = STATIC_STRING("\")");
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qab_let,Qab_let_star);
    string_constant_27 = STATIC_STRING("/* bad let */");
    Qget_constant = STATIC_SYMBOL("GET-CONSTANT",AB_package);
    Qget_variable = STATIC_SYMBOL("GET-VARIABLE",AB_package);
    Qcall_simple_function = STATIC_SYMBOL("CALL-SIMPLE-FUNCTION",AB_package);
    Qcall_function = STATIC_SYMBOL("CALL-FUNCTION",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)4L,Qget_constant,Qget_variable,
	    Qcall_simple_function,Qcall_function);
    Qfixnum_register_1 = STATIC_SYMBOL("FIXNUM-REGISTER-1",AB_package);
    Qfixnum_register_2 = STATIC_SYMBOL("FIXNUM-REGISTER-2",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qfixnum_register_1,
	    Qfixnum_register_2);
    Qfloat_register_1 = STATIC_SYMBOL("FLOAT-REGISTER-1",AB_package);
    Qfloat_register_2 = STATIC_SYMBOL("FLOAT-REGISTER-2",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qfloat_register_1,
	    Qfloat_register_2);
    string_constant_28 = STATIC_STRING("Nil");
    string_constant_29 = STATIC_STRING("0");
    string_constant_30 = STATIC_STRING("~F");
    string_constant_31 = STATIC_STRING("goto ");
    Qab_loop = STATIC_SYMBOL("LOOP",AB_package);
    string_constant_32 = STATIC_STRING("while (");
    string_constant_33 = STATIC_STRING(") {");
    string_constant_34 = STATIC_STRING("}");
    Qfixnum_case = STATIC_SYMBOL("FIXNUM-CASE",AB_package);
    Qfixnum_case_with_fallthrough = 
	    STATIC_SYMBOL("FIXNUM-CASE-WITH-FALLTHROUGH",AB_package);
    string_constant_35 = STATIC_STRING("switch (");
    string_constant_36 = STATIC_STRING("break;");
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    string_constant_37 = STATIC_STRING("if (");
    string_constant_38 = STATIC_STRING("} else {");
    string_constant_39 = STATIC_STRING("{Object result = ");
    string_constant_40 = STATIC_STRING("MVS_");
    string_constant_41 = STATIC_STRING("(result,");
    string_constant_42 = STATIC_STRING(",");
    string_constant_43 = STATIC_STRING(");}");
    string_constant_44 = STATIC_STRING("Object ");
    string_constant_45 = STATIC_STRING("int ");
    string_constant_46 = STATIC_STRING("double ");
    string_constant_47 = STATIC_STRING("  char *fn_name = \"fn");
    string_constant_48 = STATIC_STRING("\";");
    string_constant_49 = STATIC_STRING("static Object fn");
    string_constant_50 = STATIC_STRING("  Object ");
    string_constant_51 = STATIC_STRING("#define fn");
    string_constant_52 = STATIC_STRING(" 0");
    Qcode_body = STATIC_SYMBOL("CODE-BODY",AB_package);
    string_constant_53 = STATIC_STRING("  ~NF ~D~%");
    string_constant_54 = STATIC_STRING("  ~NF~%");
    string_constant_55 = STATIC_STRING("  ~NF ~A~%");
    string_constant_56 = STATIC_STRING("  ~A ~A~%");
    string_constant_57 = STATIC_STRING("~%");
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    if (Write_all_byte_code_bodies_for_kb_p == UNBOUND)
	Write_all_byte_code_bodies_for_kb_p = Nil;
    Qwrite_reference_to_frame = STATIC_SYMBOL("WRITE-REFERENCE-TO-FRAME",
	    AB_package);
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_reference_to_frame,
	    STATIC_FUNCTION(write_reference_to_frame,NIL,FALSE,1,1));
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    Qkb_flags = STATIC_SYMBOL("KB-FLAGS",AB_package);
    Qtimestamp = STATIC_SYMBOL("TIMESTAMP",AB_package);
    Qbase_time = STATIC_SYMBOL("BASE-TIME",AB_package);
    Qstart_time = STATIC_SYMBOL("START-TIME",AB_package);
    Qgensym_time = STATIC_SYMBOL("GENSYM-TIME",AB_package);
    Qkb_name = STATIC_SYMBOL("KB-NAME",AB_package);
    Qab_current_frame_serial_number = 
	    STATIC_SYMBOL("CURRENT-FRAME-SERIAL-NUMBER",AB_package);
    Qtype_of_file = STATIC_SYMBOL("TYPE-OF-FILE",AB_package);
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    Qkb_save_with_runtine_data = STATIC_SYMBOL("KB-SAVE-WITH-RUNTINE-DATA",
	    AB_package);
    Qsave_kb_with_runtine_data = STATIC_SYMBOL("SAVE-KB-WITH-RUNTINE-DATA",
	    AB_package);
    Qjournal = STATIC_SYMBOL("JOURNAL",AB_package);
    Qclass_hierarchy_flags = STATIC_SYMBOL("CLASS-HIERARCHY-FLAGS",AB_package);
    Qgraphics_tuning_bits = STATIC_SYMBOL("GRAPHICS-TUNING-BITS",AB_package);
    Qperformance_tuning_bits = STATIC_SYMBOL("PERFORMANCE-TUNING-BITS",
	    AB_package);
    Qreal_time = STATIC_SYMBOL("REAL-TIME",AB_package);
    Qsimulated_time = STATIC_SYMBOL("SIMULATED-TIME",AB_package);
    Qtop_level_module = STATIC_SYMBOL("TOP-LEVEL-MODULE",AB_package);
    Qrequired_modules = STATIC_SYMBOL("REQUIRED-MODULES",AB_package);
    Qparagraph = STATIC_SYMBOL("PARAGRAPH",AB_package);
    Qnewline = STATIC_SYMBOL("NEWLINE",AB_package);
    Qlinefeed = STATIC_SYMBOL("LINEFEED",AB_package);
    Qfinal_frame_serial_number = STATIC_SYMBOL("FINAL-FRAME-SERIAL-NUMBER",
	    AB_package);
    Qindex_displacement = STATIC_SYMBOL("INDEX-DISPLACEMENT",AB_package);
    Qreclaimed_index_count = STATIC_SYMBOL("RECLAIMED-INDEX-COUNT",AB_package);
    Qdetail_pane_description = STATIC_SYMBOL("DETAIL-PANE-DESCRIPTION",
	    AB_package);
    Qnumeric_symbols = STATIC_SYMBOL("NUMERIC-SYMBOLS",AB_package);
    Qoriginal_kb_state_plist_written_qm = 
	    STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST-WRITTEN\?",AB_package);
    Qleft_braket_written_qm = STATIC_SYMBOL("LEFT-BRAKET-WRITTEN\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleft_braket_written_qm,Left_braket_written_qm);
    record_system_variable(Qleft_braket_written_qm,Qkb_save1,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qdefinition = STATIC_SYMBOL("DEFINITION",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qreformat_as_appropriate = STATIC_SYMBOL("REFORMAT-AS-APPROPRIATE",
	    AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qsuperblock_will_do_reformatting_qm = 
	    STATIC_SYMBOL("SUPERBLOCK-WILL-DO-REFORMATTING\?",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qtable,
	    Qsuperblock_will_do_reformatting_qm);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qreformat_as_appropriate,list_constant_9,
	    Qgeneric_method_lambda_list);
    SET_SYMBOL_FUNCTION(Qreformat_as_appropriate,
	    STATIC_FUNCTION(reformat_as_appropriate,NIL,FALSE,2,2));
    Qformat_change_qm = STATIC_SYMBOL("FORMAT-CHANGE\?",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    Qtable_format = STATIC_SYMBOL("TABLE-FORMAT",AB_package);
    Qdone = STATIC_SYMBOL("DONE",AB_package);
    Qreformat_as_appropriate_for_table = 
	    STATIC_SYMBOL("REFORMAT-AS-APPROPRIATE-FOR-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qreformat_as_appropriate_for_table,
	    STATIC_FUNCTION(reformat_as_appropriate_for_table,NIL,FALSE,2,2));
    temp_1 = SYMBOL_FUNCTION(Qreformat_as_appropriate_for_table);
    set_get(Qtable,Qreformat_as_appropriate,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qreformat_as_appropriate),
	    Qclasses_which_define);
    temp_1 = CONS(Qtable,temp);
    mutate_global_property(Qreformat_as_appropriate,temp_1,
	    Qclasses_which_define);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qreformat_as_appropriate_for_text_box = 
	    STATIC_SYMBOL("REFORMAT-AS-APPROPRIATE-FOR-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qreformat_as_appropriate_for_text_box,
	    STATIC_FUNCTION(reformat_as_appropriate_for_text_box,NIL,FALSE,
	    2,2));
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qreformat_as_appropriate_for_text_box);
    set_get(Qtext_box,Qreformat_as_appropriate,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qreformat_as_appropriate),
	    Qclasses_which_define);
    temp_1 = CONS(Qtext_box,temp);
    mutate_global_property(Qreformat_as_appropriate,temp_1,
	    Qclasses_which_define);
}
