/* rltns.c
 * Input file:  relations.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rltns.h"


static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* WRITE-DUPLICATE-UUIDS-NOTE */
Object write_duplicate_uuids_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(104,0);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)15L));
    twrite(particulars);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_1,
	    FIX((SI_Long)34L)));
    return VALUES_1(Nil);
}

static Object Qremote_item;        /* remote-item */

static Object Qduplicate_uuids;    /* duplicate-uuids */

/* UPDATE-FRAME-NOTES-FOR-DUPLICATE-UUIDS */
Object update_frame_notes_for_duplicate_uuids(uuid)
    Object uuid;
{
    Object block_or_block_list, frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, number_of_blocks_with_that_uuid, temp_1;
    SI_Long ab_loopvar_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(104,1);
    if (uuid) {
	block_or_block_list = get_item_or_item_list_for_uuid(uuid);
	if (LISTP(block_or_block_list)) {
	    frame = Nil;
	    ab_loop_list_ = block_or_block_list;
	    ab_loopvar_ = (SI_Long)0L;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    frame = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qremote_item,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
	    if ( !temp) {
		if (FIX((SI_Long)1L))
		    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	    }
	    goto next_loop;
	  end_loop:
	    number_of_blocks_with_that_uuid = FIX(ab_loopvar_);
	    goto end_1;
	    number_of_blocks_with_that_uuid = Qnil;
	  end_1:;
	}
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qremote_item,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(block_or_block_list,
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
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    number_of_blocks_with_that_uuid = temp ? FIX((SI_Long)0L) : 
		    FIX((SI_Long)1L);
	}
	if (IFIX(number_of_blocks_with_that_uuid) > (SI_Long)1L) {
	    frame = Nil;
	    ab_loop_list_ = block_or_block_list;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    frame = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qremote_item,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
	    if ( !temp)
		add_frame_note(3,Qduplicate_uuids,frame,
			number_of_blocks_with_that_uuid);
	    goto next_loop_1;
	  end_loop_1:;
	    return VALUES_1(T);
	}
	else if (IFIX(number_of_blocks_with_that_uuid) == (SI_Long)1L) {
	    if (LISTP(block_or_block_list)) {
		frame = Nil;
		ab_loop_list_ = block_or_block_list;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		frame = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qremote_item,
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
		if ( !temp) {
		    temp_1 = frame;
		    goto end_2;
		}
		goto next_loop_2;
	      end_loop_2:
		temp_1 = Qnil;
	      end_2:;
	    }
	    else
		temp_1 = block_or_block_list;
	    delete_frame_note_if_any(Qduplicate_uuids,temp_1);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-RELATION-INSTANCE-TREE-SKIP-LIST-SENTINEL */
Object make_relation_instance_tree_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(104,2);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)7L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)8L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)7L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* RECLAIM-RELATION-INSTANCE-TREE-NODES */
Object reclaim_relation_instance_tree_nodes(relation_instance_tree_skip_list,
	    tail)
    Object relation_instance_tree_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(104,3);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(relation_instance_tree_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(relation_instance_tree_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(relation_instance_tree_skip_list,(SI_Long)2L);
    entry = ISVREF(relation_instance_tree_skip_list,(SI_Long)3L);
    reclaim_skip_list_element(relation_instance_tree_skip_list);
    relation_instance_tree_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-RELATION-INSTANCE-TREE-SKIP-LIST */
Object clear_relation_instance_tree_skip_list(relation_instance_tree_skip_list)
    Object relation_instance_tree_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(104,4);
    head = M_CAR(M_CDR(relation_instance_tree_skip_list));
    tail = M_CDR(M_CDR(relation_instance_tree_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_relation_instance_tree_nodes(element_qm,tail);
    return VALUES_1(relation_instance_tree_skip_list);
}

/* RELATION-INSTANCES-EMPTY-P */
Object relation_instances_empty_p(relation_instances)
    Object relation_instances;
{
    Object temp, gensymed_symbol;
    char temp_1;

    x_note_fn_call(104,5);
    temp =  !TRUEP(relation_instances) ? T : Nil;
    if (temp);
    else {
	gensymed_symbol = CDR(relation_instances);
	if (CONSP(gensymed_symbol)) {
	    temp = M_CAR(gensymed_symbol);
	    temp_1 = SIMPLE_VECTOR_P(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = M_CDR(gensymed_symbol);
	    temp_1 = SIMPLE_VECTOR_P(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = M_CDR(relation_instances);
	    temp = ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol),
		    (SI_Long)0L),(SI_Long)0L));
	    temp = EQ(temp,M_CDR(gensymed_symbol)) ? T : Nil;
	}
	else
	    temp =  !TRUEP(M_CDR(relation_instances)) ? T : Nil;
    }
    return VALUES_1(temp);
}

/* GET-RELATION-INSTANCE-FUNCTION */
Object get_relation_instance_function(key,tree)
    Object key, tree;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(104,6);
    skip_list = CDR(tree);
    key_value = key;
    key_hash_value = SXHASH_SYMBOL_1(key) & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)7L;
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
    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    return VALUES_1(temp_1);
}

static Object Qlookup;             /* lookup */

/* RECLAIM-RELATION-INSTANCES */
Object reclaim_relation_instances(tree)
    Object tree;
{
    Object head, tail, element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(104,7);
    if (tree) {
	head = M_CAR(M_CDR(tree));
	tail = M_CDR(M_CDR(tree));
	element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
		(SI_Long)0L));
	if ( !EQ(element_qm,tail))
	    reclaim_relation_instance_tree_nodes(element_qm,tail);
	reclaim_skip_list_element(head);
	reclaim_skip_list_element(tail);
	M_CDDR(tree) = Nil;
	M_CADR(tree) = Nil;
	M_CAR(tree) = Nil;
	if (tree) {
	    last_1 = tree;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qlookup);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_lookup_conses_tail_vector;
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

Object The_type_description_of_relation_instance = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_relation_instances, Qchain_of_available_relation_instances);

DEFINE_VARIABLE_WITH_SYMBOL(Relation_instance_count, Qrelation_instance_count);

Object Chain_of_available_relation_instances_vector = UNBOUND;

/* RELATION-INSTANCE-STRUCTURE-MEMORY-USAGE */
Object relation_instance_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(104,8);
    temp = Relation_instance_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RELATION-INSTANCE-COUNT */
Object outstanding_relation_instance_count()
{
    Object def_structure_relation_instance_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(104,9);
    gensymed_symbol = IFIX(Relation_instance_count);
    def_structure_relation_instance_variable = 
	    Chain_of_available_relation_instances;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_relation_instance_variable))
	goto end_loop;
    def_structure_relation_instance_variable = 
	    ISVREF(def_structure_relation_instance_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RELATION-INSTANCE-STRUCTURE-1 */
Object reclaim_relation_instance_structure_1(relation_instance)
    Object relation_instance;
{
    Object temp, svref_arg_2;

    x_note_fn_call(104,10);
    inline_note_reclaim_cons(relation_instance,Nil);
    temp = ISVREF(Chain_of_available_relation_instances_vector,
	    IFIX(Current_thread_index));
    SVREF(relation_instance,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_relation_instances_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = relation_instance;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RELATION-INSTANCE */
Object reclaim_structure_for_relation_instance(relation_instance)
    Object relation_instance;
{
    x_note_fn_call(104,11);
    return reclaim_relation_instance_structure_1(relation_instance);
}

/* MAKE-PERMANENT-RELATION-INSTANCE-STRUCTURE-INTERNAL */
Object make_permanent_relation_instance_structure_internal()
{
    Object def_structure_relation_instance_variable, the_array;
    Object defstruct_g2_relation_instance_variable, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(104,12);
    def_structure_relation_instance_variable = Nil;
    atomic_incff_symval(Qrelation_instance_count,FIX((SI_Long)100L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)3L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_relation_instance_variable = the_array;
	def_structure_relation_instance_variable = 
		defstruct_g2_relation_instance_variable;
	if (gensymed_symbol >= (SI_Long)100L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_relation_instances_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_relation_instance_variable,FIX((SI_Long)0L)) = 
		temp;
	temp = Chain_of_available_relation_instances_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_relation_instance_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_relation_instance_variable);
}

/* MAKE-RELATION-INSTANCE-STRUCTURE-1 */
Object make_relation_instance_structure_1(relation_instance_name,
	    relation_instance_relation,relation_instance_items)
    Object relation_instance_name, relation_instance_relation;
    Object relation_instance_items;
{
    Object def_structure_relation_instance_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(104,13);
    def_structure_relation_instance_variable = 
	    ISVREF(Chain_of_available_relation_instances_vector,
	    IFIX(Current_thread_index));
    if (def_structure_relation_instance_variable) {
	svref_arg_1 = Chain_of_available_relation_instances_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_relation_instance_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_relation_instance_variable = 
		make_permanent_relation_instance_structure_internal();
    inline_note_allocate_cons(def_structure_relation_instance_variable,Nil);
    SVREF(def_structure_relation_instance_variable,FIX((SI_Long)0L)) = 
	    relation_instance_name;
    SVREF(def_structure_relation_instance_variable,FIX((SI_Long)1L)) = 
	    relation_instance_relation;
    SVREF(def_structure_relation_instance_variable,FIX((SI_Long)2L)) = 
	    relation_instance_items;
    return VALUES_1(def_structure_relation_instance_variable);
}

/* MAKE-RELATED-ITEM-TREE-SKIP-LIST-SENTINEL */
Object make_related_item_tree_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(104,14);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)7L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)8L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)7L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* RECLAIM-RELATED-ITEM-TREE-NODES */
Object reclaim_related_item_tree_nodes(related_item_tree_skip_list,tail)
    Object related_item_tree_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(104,15);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(related_item_tree_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(related_item_tree_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(related_item_tree_skip_list,(SI_Long)2L);
    entry = ISVREF(related_item_tree_skip_list,(SI_Long)3L);
    reclaim_skip_list_element(related_item_tree_skip_list);
    related_item_tree_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-RELATED-ITEM-TREE-SKIP-LIST */
Object clear_related_item_tree_skip_list(related_item_tree_skip_list)
    Object related_item_tree_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(104,16);
    head = M_CAR(M_CDR(related_item_tree_skip_list));
    tail = M_CDR(M_CDR(related_item_tree_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_related_item_tree_nodes(element_qm,tail);
    return VALUES_1(related_item_tree_skip_list);
}

static Object Qrelated_item_tree;  /* related-item-tree */

/* MAKE-RELATION-INSTANCE */
Object make_relation_instance(name,relation,object)
    Object name, relation, object;
{
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, blocks, temp;

    x_note_fn_call(104,17);
    tail = make_related_item_tree_skip_list_sentinel(Most_positive_fixnum,Nil);
    head = make_related_item_tree_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qrelated_item_tree;
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
    blocks = gensymed_symbol;
    if (object) {
	gensymed_symbol = object;
	set_skip_list_entry(blocks,FIX((SI_Long)7L),Qeq,Nil,T,
		gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum)),object);
    }
    temp = make_relation_instance_structure_1(name,relation,blocks);
    return VALUES_1(temp);
}

/* RECLAIM-RELATION-INSTANCE */
Object reclaim_relation_instance(instance)
    Object instance;
{
    Object gensymed_symbol, gensymed_symbol_1, related_item_tree_skip_list;
    Object head, tail, element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(104,18);
  next_loop:
    gensymed_symbol = ISVREF(instance,(SI_Long)2L);
    gensymed_symbol_1 = Nil;
    if (CAS_SVREF(instance,(SI_Long)2L,gensymed_symbol,gensymed_symbol_1)) {
	related_item_tree_skip_list = gensymed_symbol;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    related_item_tree_skip_list = Qnil;
  end_1:
    head = M_CAR(M_CDR(related_item_tree_skip_list));
    tail = M_CDR(M_CDR(related_item_tree_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_related_item_tree_nodes(element_qm,tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(related_item_tree_skip_list) = Nil;
    M_CADR(related_item_tree_skip_list) = Nil;
    M_CAR(related_item_tree_skip_list) = Nil;
    if (related_item_tree_skip_list) {
	last_1 = related_item_tree_skip_list;
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
	    M_CDR(temp) = related_item_tree_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = related_item_tree_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    temp_1 = reclaim_relation_instance_structure_1(instance);
    return VALUES_1(temp_1);
}

/* COPY-LIST-OF-RELATION-INSTANCE */
Object copy_list_of_relation_instance(relation_instance)
    Object relation_instance;
{
    Object head, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, temp, gensymed_symbol;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, block, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_less_than_branch_qm_, tail;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(104,19);
    head = slot_value_list_2(ISVREF(relation_instance,(SI_Long)0L),
	    copy_for_slot_value(ISVREF(relation_instance,(SI_Long)1L)));
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
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
	ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
    }
    else
	ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
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
      block = M_CDR(ab_entry_cons_);
      if (block) {
	  ab_loopvar__2 = slot_value_cons_1(copy_for_slot_value(block),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop_1:
      tail = ab_loopvar_;
      goto end_1;
      tail = Qnil;
    end_1:;
    POP_SPECIAL();
    temp = nconc2(head,tail);
    return VALUES_1(temp);
}

/* MORE-THAN-ONE-RELATED-ITEM-P */
Object more_than_one_related_item_p(skip_list_or_binary_tree)
    Object skip_list_or_binary_tree;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object item, ab_less_than_branch_qm_;
    SI_Long count_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(104,20);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_skip_list_form_ = skip_list_or_binary_tree;
    ab_binary_tree_form_ = skip_list_or_binary_tree;
    gensymed_symbol = CDR(skip_list_or_binary_tree);
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
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      count_1 = (SI_Long)0L;
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
      item = M_CDR(ab_entry_cons_);
      if ((SI_Long)2L == count_1)
	  goto end_loop_1;
      if (item)
	  count_1 = count_1 + (SI_Long)1L;
      goto next_loop;
    end_loop_1:
      temp = (SI_Long)2L == count_1 ? T : Nil;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* ONLY-ONE-RELATED-ITEM-P */
Object only_one_related_item_p(skip_list_or_binary_tree)
    Object skip_list_or_binary_tree;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object item, ab_less_than_branch_qm_;
    SI_Long count_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(104,21);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_skip_list_form_ = skip_list_or_binary_tree;
    ab_binary_tree_form_ = skip_list_or_binary_tree;
    gensymed_symbol = CDR(skip_list_or_binary_tree);
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
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      count_1 = (SI_Long)0L;
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
      item = M_CDR(ab_entry_cons_);
      if (item)
	  count_1 = count_1 + (SI_Long)1L;
      goto next_loop;
    end_loop_1:
      temp = count_1 == (SI_Long)1L ? T : Nil;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* COPY-LIST-OF-RELATION-INSTANCES */
Object copy_list_of_relation_instances(relation_instances)
    Object relation_instances;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object instance, new_entry, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(104,22);
    if (relation_instances) {
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
	instance = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  new_entry = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
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
	  instance = M_CDR(ab_entry_cons_);
	  new_entry = copy_list_of_relation_instance(instance);
	  if (new_entry) {
	      ab_loopvar__2 = slot_value_cons_1(new_entry,Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	  }
	  goto next_loop;
	end_loop_1:
	  temp = ab_loopvar_;
	  goto end_1;
	  temp = Qnil;
	end_1:;
	POP_SPECIAL();
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* COPY-RELATED-ITEMS */
Object copy_related_items(related_items)
    Object related_items;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object related_item, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(104,23);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_skip_list_form_ = related_items;
    ab_binary_tree_form_ = related_items;
    gensymed_symbol = CDR(related_items);
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
    related_item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
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
      related_item = M_CDR(ab_entry_cons_);
      if (related_item) {
	  ab_loopvar__2 = frame_cons_1(related_item,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop_1:
      temp = ab_loopvar_;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* UPGRADE-RELATION-INSTANCES */
Object upgrade_relation_instances(blocks)
    Object blocks;
{
    Object block, ab_loop_list_;

    x_note_fn_call(104,24);
    if (LISTP(blocks)) {
	block = Nil;
	ab_loop_list_ = blocks;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	upgrade_relation_instance(block);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qrelation_instance_tree;  /* relation-instance-tree */

static Object Qold_relation_instances;  /* old-relation-instances */

/* UPGRADE-RELATION-INSTANCE */
Object upgrade_relation_instance(block)
    Object block;
{
    Object old_relation_instances_qm, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object new_relation_instances;

    x_note_fn_call(104,25);
    old_relation_instances_qm = ISVREF(block,(SI_Long)12L);
    if ( !TRUEP(old_relation_instances_qm) || 
	    CONSP(old_relation_instances_qm) &&  
	    !EQ(CAR(old_relation_instances_qm),Qrelation_instance_tree)) {
	tail = 
		make_relation_instance_tree_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head = 
		make_relation_instance_tree_skip_list_sentinel(Most_negative_fixnum,
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
	M_CAR(gensymed_symbol) = Qrelation_instance_tree;
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
	new_relation_instances = gensymed_symbol;
	upgrade_relation_instance_internal(old_relation_instances_qm,
		new_relation_instances);
	if (CAS_SVREF(block,(SI_Long)12L,old_relation_instances_qm,
		new_relation_instances)) {
	    if (old_relation_instances_qm)
		return reclaim_slot_value_tree_1(SYMBOL_VALUE(Qold_relation_instances));
	    else
		return VALUES_1(Nil);
	}
	else
	    return error((SI_Long)1L,"what\?!");
    }
    else
	return VALUES_1(Nil);
}

/* UPGRADE-RELATION-INSTANCE-INTERNAL */
Object upgrade_relation_instance_internal(old_relation_instances,
	    new_relation_instances)
    Object old_relation_instances, new_relation_instances;
{
    Object old_relation_instance, ab_loop_list_, name, relation;
    Object new_relation_instance, queue_or_tree, instance, ab_loop_list__1;
    Object gensymed_symbol, temp, temp_1;

    x_note_fn_call(104,26);
    old_relation_instance = Nil;
    ab_loop_list_ = old_relation_instances;
    name = Nil;
    relation = Nil;
    new_relation_instance = Nil;
    queue_or_tree = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    old_relation_instance = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    name = CAR(old_relation_instance);
    relation = CADR(old_relation_instance);
    new_relation_instance = make_relation_instance(name,relation,Nil);
    queue_or_tree = ISVREF(new_relation_instance,(SI_Long)2L);
    instance = Nil;
    ab_loop_list__1 = CDDR(old_relation_instance);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    instance = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    gensymed_symbol = instance;
    temp = queue_or_tree;
    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum));
    set_skip_list_entry(temp,FIX((SI_Long)7L),Qeq,Nil,T,gensymed_symbol,
	    temp_1,instance);
    goto next_loop_1;
  end_loop_1:;
    gensymed_symbol = name;
    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & IFIX(Most_positive_fixnum));
    set_skip_list_entry(new_relation_instances,FIX((SI_Long)7L),Qeq,Nil,T,
	    gensymed_symbol,temp,new_relation_instance);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PUT-RELATION-IS-SYMETRIC-WHERE-SLOT-IS-ABSENT */
Object put_relation_is_symetric_where_slot_is_absent(relation,value)
    Object relation, value;
{
    x_note_fn_call(104,27);
    put_relation_is_symmetric(relation,value,T);
    return VALUES_1(Nil);
}

static Object string_constant;     /* "Cannot establish the relation ~a between ~NF and ~NF.  ~
				    *                   ~NF is not of class ~a."
				    */

/* RELATION-VIOLATES-CLASS-OR-PERMANENCY-CONSTRAINTS-P */
Object relation_violates_class_or_permanency_constraints_p(given_name,
	    relation,item1,item2)
    Object given_name, relation, item1, item2;
{
    Object relation_name, subject_class, object_class, other_name, subject;
    Object object, gensymed_symbol, sub_class_bit_vector, temp_1;
    Object error_string_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(104,28);
    relation_name = relation;
    subject_class = ISVREF(relation,(SI_Long)21L);
    object_class = ISVREF(relation,(SI_Long)20L);
    other_name = Nil;
    subject = Nil;
    object = Nil;
    if (EQ(given_name,ISVREF(relation,(SI_Long)22L))) {
	temp =  !TRUEP(ISVREF(relation,(SI_Long)25L));
	if (temp);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(subject_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item2,(SI_Long)1L),
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
	    if (temp) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(object_class,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(item1,
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
	}
	if (temp);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(object_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item2,(SI_Long)1L),
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
	    temp =  !temp;
	}
	if (temp);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(subject_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item1,(SI_Long)1L),
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
	    temp =  !temp;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (ISVREF(relation,(SI_Long)25L))
	    other_name = relation_name;
	else {
	    temp_1 = ISVREF(relation,(SI_Long)23L);
	    if (temp_1);
	    else
		temp_1 = ISVREF(relation,(SI_Long)26L);
	    other_name = temp_1;
	}
	subject = item2;
	object = item1;
    }
    else {
	other_name = given_name;
	subject = item1;
	object = item2;
    }
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(subject_class,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(subject,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if ( !temp)
	error_string_qm = tformat_text_string(6,string_constant,given_name,
		object,subject,subject,subject_class);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(object_class,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    error_string_qm = tformat_text_string(6,string_constant,
		    given_name,object,subject,object,object_class);
	else
	    error_string_qm = Nil;
    }
    if (error_string_qm)
	return VALUES_1(error_string_qm);
    else
	return VALUES_1(Nil);
}

/* INITIAL-RELATIONSHIPS */
Object initial_relationships(class_1)
    Object class_1;
{
    x_note_fn_call(104,29);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(In_write_module_as_clear_text_p, Qin_write_module_as_clear_text_p);

static Object Qrelation_name_reference;  /* relation-name-reference */

static Object Qrelation_is_inverted;  /* relation-is-inverted */

static Object Qrelated_items;      /* related-items */

/* GET-RELATIONSHIPS */
Object get_relationships(block)
    Object block;
{
    Object relation_instances, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, gensymed_symbol, temp;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, relation_instance, source_name_reference, relation;
    Object relation_name, secret_inverse_name_qm, name_reference_to_export;
    Object related_items_qm, relations_eval_list, ab_loopvar_, ab_loopvar__1;
    Object ab_less_than_branch_qm_, ab_node_stack__1, ab_current_node__1;
    Object ab_skip_list_p__1, ab_next_node__1, ab_tail_node__1;
    Object ab_current_alist__1, ab_entry_cons__1, related_item, ab_loopvar__2;
    Object ab_loopvar__3, temp_2, item, ab_loop_list_, temp_3;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(104,30);
    relation_instances = ISVREF(block,(SI_Long)12L);
    if (relation_instances) {
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
	  source_name_reference = Nil;
	  relation = Nil;
	  relation_name = Nil;
	  secret_inverse_name_qm = Nil;
	  name_reference_to_export = Nil;
	  related_items_qm = Nil;
	  relations_eval_list = Nil;
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
	  source_name_reference = ISVREF(relation_instance,(SI_Long)0L);
	  relation = ISVREF(relation_instance,(SI_Long)1L);
	  relation_name = ISVREF(relation,(SI_Long)22L);
	  secret_inverse_name_qm =  !(ISVREF(relation,(SI_Long)25L) || 
		  ISVREF(relation,(SI_Long)23L)) ? ISVREF(relation,
		  (SI_Long)26L) : Nil;
	  name_reference_to_export = EQ(source_name_reference,
		  secret_inverse_name_qm) ? relation_name : 
		  source_name_reference;
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
	  related_item = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
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
	    related_item = M_CDR(ab_entry_cons__1);
	    if (related_item && serve_item_p(related_item) && 
		    (In_write_module_as_clear_text_p ? 
		    TRUEP(savable_block_p(related_item)) : TRUEP(T))) {
		ab_loopvar__3 = frame_cons_1(related_item,Nil);
		if (ab_loopvar__2)
		    M_CDR(ab_loopvar__2) = ab_loopvar__3;
		else
		    ab_loopvar__1 = ab_loopvar__3;
		ab_loopvar__2 = ab_loopvar__3;
	    }
	    goto next_loop_2;
	  end_loop_3:
	    related_items_qm = ab_loopvar__1;
	    goto end_1;
	    related_items_qm = Qnil;
	  end_1:;
	  POP_SPECIAL();
	  if (related_items_qm) {
	      temp_2 = eval_list_2(Qrelation_name_reference,
		      name_reference_to_export);
	      temp = eval_list_2(Qrelation_is_inverted, 
		      !TRUEP(ISVREF(relation,(SI_Long)25L)) &&  
		      !EQ(source_name_reference,secret_inverse_name_qm) ? 
		      Evaluation_true_value : Evaluation_false_value);
	      item = Nil;
	      ab_loop_list_ = related_items_qm;
	      gensymed_symbol = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop_4:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_4;
	      item = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loopvar__2 = eval_cons_1(item,Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  gensymed_symbol = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      goto next_loop_4;
	    end_loop_4:
	      temp_3 = allocate_evaluation_sequence(gensymed_symbol);
	      goto end_2;
	      temp_3 = Qnil;
	    end_2:;
	      temp_3 = eval_list_2(Qrelated_items,temp_3);
	      reclaim_frame_list_1(related_items_qm);
	      ab_loopvar__1 = 
		      eval_cons_1(allocate_evaluation_structure(nconc2(temp_2,
		      nconc2(temp,temp_3))),Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  relations_eval_list = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	  }
	  goto next_loop;
	end_loop_1:
	  temp = allocate_evaluation_sequence(relations_eval_list);
	  goto end_3;
	  temp = Qnil;
	end_3:;
	POP_SPECIAL();
    }
    else
	temp = allocate_evaluation_sequence(Nil);
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qrelation;           /* relation */

static Object string_constant_1;   /* "~a~%The value of a relation-name-reference component, ~
				    *                                  ~a, does not name a relation."
				    */

static Object string_constant_2;   /* "The value of a relation-name-reference component, ~a, ~
				    *                              does not name a relation."
				    */

static Object Qtruth_value;        /* truth-value */

static Object string_constant_3;   /* "~a~%~a" */

/* SET-RELATIONSHIPS */
Object set_relationships(block,new_value)
    Object block, new_value;
{
    Object relation_instances, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, gensymed_symbol, temp;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, relation_instance, relation_frame, related_items;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_less_than_branch_qm_;
    Object old_relations_for_block_qm, relations_to_add_information_qm;
    Object string_of_errors_qm, no_error_condition_qm, held_vector;
    Object relation_structure, exported_name_reference, related_items_sequence;
    Object elt_1, validated_elt, held_vector_1, related_item, x2;
    Object relation_name, relation_is_symmetric_qm, secret_inverse_name_qm;
    Object relation_reference_for_setting, ab_loop_list_, error_result_qm;
    Object subject_class, sub_class_bit_vector, block_is_subject_class_p;
    Object relation_direction_ambiguous_p, relation_is_inverted_eval_val_qm;
    Object copy_of_current_value, relation_reference, inverse_of_relation_qm;
    Object relation_reference_for_removing;
    Object relation_frame_appears_in_new_value_qm, ab_loop_list__1, item1;
    Object item2, cons_holding_relation_frame_in_previous_value_qm;
    Object items_were_in_relation_in_old_value_qm, ab_loop_desetq_;
    SI_Long next_index, length_1, next_index_1, length_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(104,31);
    relation_instances = ISVREF(block,(SI_Long)12L);
    if (relation_instances) {
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
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  relation_frame = Nil;
	  related_items = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
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
	  related_items = ISVREF(relation_instance,(SI_Long)2L);
	  temp = frame_cons_1(relation_frame,Nil);
	  ab_loopvar__2 = frame_cons_1(nconc2(temp,
		  copy_related_items(related_items)),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop;
	end_loop_1:
	  old_relations_for_block_qm = ab_loopvar_;
	  goto end_1;
	  old_relations_for_block_qm = Qnil;
	end_1:;
	POP_SPECIAL();
    }
    else
	old_relations_for_block_qm = Nil;
    relations_to_add_information_qm = Nil;
    string_of_errors_qm = Nil;
    if ( !( !TRUEP(new_value) || IFIX(FIXNUM_SUB1(ISVREF(M_CAR(new_value),
	    (SI_Long)1L))) == (SI_Long)0L)) {
	no_error_condition_qm = T;
	gensymed_symbol = new_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	relation_structure = Nil;
	exported_name_reference = Nil;
	related_items_sequence = Nil;
	related_items = Nil;
	relation_frame = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_2:
	if (next_index >= length_1)
	    goto end_loop_2;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	relation_structure = validated_elt;
	exported_name_reference = estructure_slot(relation_structure,
		Qrelation_name_reference,Nil);
	related_items_sequence = estructure_slot(relation_structure,
		Qrelated_items,Nil);
	gensymed_symbol = related_items_sequence;
	held_vector_1 = Nil;
	next_index_1 = (SI_Long)1L;
	length_2 = (SI_Long)0L;
	related_item = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector_1 = M_CAR(gensymed_symbol);
	length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
      next_loop_3:
	if (next_index_1 >= length_2)
	    goto end_loop_3;
	elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		next_index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index_1 & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index_1 = next_index_1 + (SI_Long)1L;
	related_item = validated_elt;
	if (related_item) {
	    if (SIMPLE_VECTOR_P(related_item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(related_item)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(related_item,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(related_item,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    ab_loopvar__2 = frame_cons_1(related_item,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_3;
      end_loop_3:
	related_items = ab_loopvar_;
	goto end_2;
	related_items = Qnil;
      end_2:;
	relation_frame = get_instance_with_name_if_any(Qrelation,
		exported_name_reference);
	if ( !TRUEP(relation_frame)) {
	    reclaim_frame_list_1(related_items);
	    if (string_of_errors_qm) {
		temp = tformat_text_string(3,string_constant_1,
			string_of_errors_qm,exported_name_reference);
		reclaim_text_string(string_of_errors_qm);
		string_of_errors_qm = temp;
	    }
	    else
		string_of_errors_qm = tformat_text_string(2,
			string_constant_2,exported_name_reference);
	}
	else {
	    relation_name = ISVREF(relation_frame,(SI_Long)22L);
	    relation_is_symmetric_qm = ISVREF(relation_frame,(SI_Long)25L);
	    secret_inverse_name_qm =  !(relation_is_symmetric_qm || 
		    ISVREF(relation_frame,(SI_Long)23L)) ? 
		    ISVREF(relation_frame,(SI_Long)26L) : Nil;
	    relation_reference_for_setting =  !EQ(exported_name_reference,
		    relation_name) ? relation_name : 
		    relation_is_symmetric_qm || secret_inverse_name_qm ? 
		    relation_name : ISVREF(relation_frame,(SI_Long)23L);
	    related_item = Nil;
	    ab_loop_list_ = related_items;
	    error_result_qm = Nil;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_4;
	    related_item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (secret_inverse_name_qm) {
		subject_class = ISVREF(relation_frame,(SI_Long)20L);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(subject_class,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(block,
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
			block_is_subject_class_p = (SI_Long)0L < 
				gensymed_symbol_1 ? T : Nil;
		    }
		    else
			block_is_subject_class_p = Nil;
		}
		else
		    block_is_subject_class_p = Nil;
		if (block_is_subject_class_p) {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(subject_class,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(related_item,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			    relation_direction_ambiguous_p = (SI_Long)0L < 
				    gensymed_symbol_1 ? T : Nil;
			}
			else
			    relation_direction_ambiguous_p = Nil;
		    }
		    else
			relation_direction_ambiguous_p = Nil;
		}
		else
		    relation_direction_ambiguous_p = Nil;
		if (relation_direction_ambiguous_p) {
		    relation_is_inverted_eval_val_qm = 
			    estructure_slot(relation_structure,
			    Qrelation_is_inverted,Nil);
		    temp_1 = relation_is_inverted_eval_val_qm && 
			    CONSP(relation_is_inverted_eval_val_qm) && 
			    EQ(M_CDR(relation_is_inverted_eval_val_qm),
			    Qtruth_value) ?  
			    !TRUEP(evaluation_truth_value_is_true_p(relation_is_inverted_eval_val_qm)) 
			    : TRUEP(block_is_subject_class_p);
		}
		else
		    temp_1 = TRUEP(block_is_subject_class_p);
		if (temp_1) {
		    if (no_error_condition_qm)
			relations_to_add_information_qm = 
				nconc2(relations_to_add_information_qm,
				frame_cons_1(frame_list_4(relation_frame,
				relation_reference_for_setting,block,
				related_item),Nil));
		    error_result_qm = 
			    relation_violates_class_or_permanency_constraints_p(relation_reference_for_setting,
			    relation_frame,block,related_item);
		}
		else {
		    if (no_error_condition_qm)
			relations_to_add_information_qm = 
				nconc2(relations_to_add_information_qm,
				frame_cons_1(frame_list_4(relation_frame,
				relation_reference_for_setting,
				related_item,block),Nil));
		    error_result_qm = 
			    relation_violates_class_or_permanency_constraints_p(relation_reference_for_setting,
			    relation_frame,related_item,block);
		}
	    }
	    else {
		if (no_error_condition_qm)
		    relations_to_add_information_qm = 
			    nconc2(relations_to_add_information_qm,
			    frame_cons_1(frame_list_4(relation_frame,
			    relation_reference_for_setting,block,
			    related_item),Nil));
		error_result_qm = 
			relation_violates_class_or_permanency_constraints_p(relation_reference_for_setting,
			relation_frame,block,related_item);
	    }
	    if (error_result_qm) {
		no_error_condition_qm = Nil;
		if (string_of_errors_qm) {
		    temp = tformat_text_string(3,string_constant_3,
			    string_of_errors_qm,error_result_qm);
		    reclaim_text_string(string_of_errors_qm);
		    string_of_errors_qm = temp;
		}
		else
		    string_of_errors_qm = error_result_qm;
	    }
	    goto next_loop_4;
	  end_loop_4:
	    reclaim_frame_list_1(related_items);
	}
	goto next_loop_2;
      end_loop_2:;
    }
    if (string_of_errors_qm) {
	reclaim_frame_tree_1(relations_to_add_information_qm);
	reclaim_frame_tree_1(old_relations_for_block_qm);
	temp = string_of_errors_qm;
    }
    else {
	relation_instances = ISVREF(block,(SI_Long)12L);
	if (relation_instances) {
	    copy_of_current_value = 
		    copy_list_of_relation_instances(relation_instances);
	    relation_instance = Nil;
	    ab_loop_list_ = copy_of_current_value;
	    relation_reference = Nil;
	    relation_frame = Nil;
	    relation_name = Nil;
	    related_items = Nil;
	    relation_is_symmetric_qm = Nil;
	    inverse_of_relation_qm = Nil;
	    secret_inverse_name_qm = Nil;
	    relation_reference_for_removing = Nil;
	    relation_frame_appears_in_new_value_qm = Nil;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    relation_instance = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    relation_reference = M_CAR(relation_instance);
	    relation_frame = M_CAR(M_CDR(relation_instance));
	    relation_name = ISVREF(relation_frame,(SI_Long)22L);
	    related_items = CDDR(relation_instance);
	    relation_is_symmetric_qm = ISVREF(relation_frame,(SI_Long)25L);
	    inverse_of_relation_qm = ISVREF(relation_frame,(SI_Long)23L);
	    secret_inverse_name_qm =  !(relation_is_symmetric_qm || 
		    inverse_of_relation_qm) ? ISVREF(relation_frame,
		    (SI_Long)26L) : Nil;
	    relation_reference_for_removing =  !EQ(relation_reference,
		    relation_name) ? relation_name : 
		    relation_is_symmetric_qm || secret_inverse_name_qm ? 
		    relation_name : inverse_of_relation_qm;
	    relation_frame_appears_in_new_value_qm = 
		    assq_function(relation_frame,
		    relations_to_add_information_qm);
	    related_item = Nil;
	    ab_loop_list__1 = related_items;
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_6;
	    related_item = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (secret_inverse_name_qm) {
		if (EQ(relation_reference,secret_inverse_name_qm))
		    remove_from_relation(relation_reference_for_removing,
			    block,related_item,Nil, 
			    !TRUEP(relation_frame_appears_in_new_value_qm) 
			    ? T : Nil,Nil);
		else
		    remove_from_relation(relation_reference_for_removing,
			    related_item,block,Nil, 
			    !TRUEP(relation_frame_appears_in_new_value_qm) 
			    ? T : Nil,Nil);
	    }
	    else
		remove_from_relation(relation_reference_for_removing,block,
			related_item,Nil, 
			!TRUEP(relation_frame_appears_in_new_value_qm) ? T 
			: Nil,Nil);
	    goto next_loop_6;
	  end_loop_6:;
	    goto next_loop_5;
	  end_loop_5:
	    reclaim_slot_value(copy_of_current_value);
	}
	relation_frame = Nil;
	relation_reference = Nil;
	item1 = Nil;
	item2 = Nil;
	ab_loop_list_ = relations_to_add_information_qm;
	cons_holding_relation_frame_in_previous_value_qm = Nil;
	items_were_in_relation_in_old_value_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	relation_frame = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	relation_reference = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	item1 = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	item2 = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	cons_holding_relation_frame_in_previous_value_qm = 
		assq_function(relation_frame,old_relations_for_block_qm);
	if (cons_holding_relation_frame_in_previous_value_qm) {
	    temp = memq_function(item1,
		    cons_holding_relation_frame_in_previous_value_qm);
	    if (temp);
	    else
		temp = memq_function(item2,
			cons_holding_relation_frame_in_previous_value_qm);
	    items_were_in_relation_in_old_value_qm = temp;
	}
	else
	    items_were_in_relation_in_old_value_qm = Nil;
	add_to_relation(relation_reference,item1,item2,T,Nil, 
		!TRUEP(items_were_in_relation_in_old_value_qm) ? T : Nil);
	goto next_loop_7;
      end_loop_7:
	reclaim_frame_tree_1(relations_to_add_information_qm);
	reclaim_frame_tree_1(old_relations_for_block_qm);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* INITIAL-ITEMS-IN-THIS-RELATION */
Object initial_items_in_this_relation(class_1)
    Object class_1;
{
    x_note_fn_call(104,32);
    return VALUES_1(Nil);
}

/* GET-ITEMS-IN-THIS-RELATION */
Object get_items_in_this_relation(relation)
    Object relation;
{
    Object relation_name, inverse_name, class_of_subject;
    Object class_of_subject_name_reference, class_of_object, collector_list;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, block, relation_instances;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_1;
    Object temp_2, entry_hash, items_in_relation_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(104,33);
    relation_name = ISVREF(relation,(SI_Long)22L);
    inverse_name = ISVREF(relation,(SI_Long)23L);
    if (inverse_name);
    else
	inverse_name = ISVREF(relation,(SI_Long)26L);
    class_of_subject = ISVREF(relation,(SI_Long)20L);
    class_of_subject_name_reference = inverse_name;
    if (class_of_subject_name_reference);
    else
	class_of_subject_name_reference = relation_name;
    class_of_object = ISVREF(relation,(SI_Long)21L);
    collector_list = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      relation_instances = Nil;
      ab_loopvar_ = collect_subclasses(class_of_subject);
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
      block = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances = ISVREF(block,(SI_Long)12L);
      if (relation_instances) {
	  skip_list = CDR(relation_instances);
	  key_value = class_of_subject_name_reference;
	  key_hash_value = 
		  SXHASH_SYMBOL_1(class_of_subject_name_reference) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)7L;
	  ab_loop_bind_ = bottom_level;
	next_loop_2:
	  if (level < ab_loop_bind_)
	      goto end_loop_2;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_3:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	next_loop_4:
	  if ( !TRUEP(marked))
	      goto end_loop_3;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	  goto next_loop_4;
	end_loop_3:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	  temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		  TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp ? TRUEP(serve_item_p(block)) : TRUEP(Nil))
	  collector_list = eval_cons_1(block,collector_list);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      relation_instances = Nil;
      ab_loopvar_ = collect_subclasses(class_of_object);
    next_loop_5:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_6:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_5;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_5;
	  goto next_loop_6;
	end_loop_5:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_6;
      block = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances = ISVREF(block,(SI_Long)12L);
      if (relation_instances) {
	  skip_list = CDR(relation_instances);
	  key_value = relation_name;
	  key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)7L;
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
	      goto end_2;
	  goto next_loop_8;
	end_loop_9:
	end_2:
	  level = level - (SI_Long)1L;
	  goto next_loop_7;
	end_loop_7:;
	  temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		  TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if ((temp ?  !TRUEP(memq_function(block,collector_list)) : 
	      TRUEP(Nil)) ? TRUEP(serve_item_p(block)) : TRUEP(Nil))
	  collector_list = eval_cons_1(block,collector_list);
      goto next_loop_5;
    end_loop_6:;
    POP_SPECIAL();
    items_in_relation_qm = collector_list;
    temp_2 = items_in_relation_qm ? 
	    allocate_evaluation_sequence(items_in_relation_qm) : Nil;
    return VALUES_1(temp_2);
}

static Object array_constant_2;    /* # */

/* NO-CHANGE-WHILE-RUNNING */
Object no_change_while_running()
{
    Object temp, temp_1;

    x_note_fn_call(104,34);
    temp = Bad_phrase;
    temp_1 = copy_constant_wide_string_given_length(array_constant_2,
	    FIX((SI_Long)32L));
    return VALUES_2(temp,temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Grammar_categories_getting_yes_no_feature, Qgrammar_categories_getting_yes_no_feature);

static Object string_constant_4;   /* "yes" */

static Object string_constant_5;   /* "no" */

/* WRITE-RELATION-YES-OR-NO?-FROM-SLOT */
Object write_relation_yes_or_no_qm_from_slot(yes_or_no,gensymed_symbol)
    Object yes_or_no, gensymed_symbol;
{
    x_note_fn_call(104,35);
    if (yes_or_no)
	return twrite(string_constant_4);
    else
	return twrite(string_constant_5);
}

static Object Qnone;               /* none */

static Object Qrelation_name;      /* relation-name */

static Object array_constant_3;    /* # */

static Object Qinverse_of_relation;  /* inverse-of-relation */

static Object Qroot;               /* root */

static Object array_constant_4;    /* # */

static Object string_constant_6;   /* "A symmetric relation may not have an inverse of relation." */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object array_constant_5;    /* # */

/* COMPILE-RELATION-NAME?-FOR-SLOT */
Object compile_relation_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, relation, slot_name;
    Object new_name_qm, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(104,36);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    relation = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    new_name_qm =  !EQ(parse_result,Qnone) ? parse_result : Nil;
    if (EQ(slot_name,Qrelation_name) &&  !TRUEP(new_name_qm) && 
	    ISVREF(relation,(SI_Long)23L)) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_3,
		FIX((SI_Long)30L));
	return VALUES_2(temp,temp_1);
    }
    else if (EQ(slot_name,Qrelation_name) && EQ(new_name_qm,
	    ISVREF(relation,(SI_Long)22L)) || EQ(slot_name,
	    Qinverse_of_relation) && EQ(new_name_qm,ISVREF(relation,
	    (SI_Long)23L)))
	return VALUES_1(new_name_qm);
    else if (get_instance_with_name_if_any(Qroot,new_name_qm)) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_4,
		FIX((SI_Long)20L));
	return VALUES_2(temp,temp_1);
    }
    else if (EQ(slot_name,Qrelation_name)) {
	change_primary_name_of_frame(relation,new_name_qm,Nil);
	return VALUES_1(new_name_qm);
    }
    else if (ISVREF(relation,(SI_Long)25L)) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_6);
	return VALUES_2(temp,temp_1);
    }
    else if (get_lookup_slot_value_given_default(relation,
	    Qname_or_names_for_frame,Nil)) {
	change_secondary_name_of_frame(relation,new_name_qm,Nil);
	return VALUES_1(new_name_qm);
    }
    else {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_5,
		FIX((SI_Long)31L));
	return VALUES_2(temp,temp_1);
    }
}

static Object string_constant_7;   /* "~(~a~)" */

/* WRITE-ONENESS-TYPE-FROM-SLOT */
Object write_oneness_type_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(104,37);
    return tformat(2,string_constant_7,value);
}

static Object list_constant;       /* # */

static Object string_constant_8;   /* "A symmetric relation can only be one-to-one or many-to-many." */

/* COMPILE-ONENESS-TYPE-FOR-SLOT */
Object compile_oneness_type_for_slot varargs_1(int, n)
{
    Object parse_result, relation, gensymed_symbol;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(104,38);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    relation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (ISVREF(relation,(SI_Long)25L) &&  
	    !TRUEP(memq_function(parse_result,list_constant))) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_8);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* ONENESS-TYPE-EVALUATION-SETTER */
Object oneness_type_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(104,39);
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
			  list_constant_1))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_2,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_oneness_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_oneness_type_evaluation_setter:
    return result;
}

/* ONENESS-TYPE-EVALUATION-GETTER */
Object oneness_type_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(104,40);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

/* RELATION-YES-OR-NO?-EVALUATION-SETTER */
Object relation_yes_or_no_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(104,41);
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
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qtruth_value,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_relation_yes_or_no_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = evaluation_truth_value_is_true_p(evaluation_value);
  end_relation_yes_or_no_qm_evaluation_setter:
    return result;
}

/* RELATION-YES-OR-NO?-EVALUATION-GETTER */
Object relation_yes_or_no_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(104,42);
    GENSYM_RETURN_ONE(slot_value ? Evaluation_true_value : 
	    Evaluation_false_value);
    return VALUES_1(Nil);
}

static Object string_constant_9;   /* "~(~a~a may be ~a ~a ~a~)" */

static Object list_constant_4;     /* # */

static Object string_constant_10;  /* "at most one" */

static Object string_constant_11;  /* "more than one" */

static Object string_constant_12;  /* ";~%" */

static Object list_constant_5;     /* # */

static Object string_constant_13;  /* "~(~a ~a may be ~a ~a~a~)" */

/* WRITE-RELATION-SUMMARY-FROM-SLOT */
Object write_relation_summary_from_slot(value,relation)
    Object value, relation;
{
    Object name, reverse_name, forward_class, reverse_class, uniqueness_type;
    Object temp;

    x_note_fn_call(104,43);
    name = ISVREF(relation,(SI_Long)22L);
    reverse_name = ISVREF(relation,(SI_Long)23L);
    forward_class = ISVREF(relation,(SI_Long)20L);
    reverse_class = ISVREF(relation,(SI_Long)21L);
    uniqueness_type = ISVREF(relation,(SI_Long)24L);
    if (name) {
	temp = supply_a_or_an(forward_class);
	tformat(6,string_constant_9,temp,forward_class,name,
		memq_function(uniqueness_type,list_constant_4) ? 
		string_constant_10 : string_constant_11,reverse_class);
	tformat(1,string_constant_12);
	if (reverse_name) {
	    temp = supply_a_or_an(reverse_class);
	    return tformat(6,string_constant_9,temp,reverse_class,
		    reverse_name,memq_function(uniqueness_type,
		    list_constant_5) ? string_constant_10 : 
		    string_constant_11,forward_class);
	}
	else {
	    temp = memq_function(uniqueness_type,list_constant_5) ? 
		    string_constant_10 : string_constant_11;
	    return tformat(6,string_constant_13,temp,forward_class,name,
		    supply_a_or_an(reverse_class),reverse_class);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_14;  /* "~a sEcReT iNvErSe NaMe" */

static Object Qrelation_summary;   /* relation-summary */

/* PUT-RELATION-NAME */
Object put_relation_name(relation,value,initializing_qm)
    Object relation, value, initializing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, old_value, svref_new_value;

    x_note_fn_call(104,44);
  next_loop:
    gensymed_symbol = ISVREF(relation,(SI_Long)22L);
    gensymed_symbol_1 = value;
    if (CAS_SVREF(relation,(SI_Long)22L,gensymed_symbol,gensymed_symbol_1)) {
	old_value = gensymed_symbol;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    old_value = Qnil;
  end_1:
    if (old_value)
	delete_from_directory_of_names(old_value,Qrelation_name);
    if (value) {
	add_to_directory_of_names(value,Qrelation_name);
	svref_new_value = intern_text_string(1,tformat_text_string(2,
		string_constant_14,value));
	ISVREF(relation,(SI_Long)26L) = svref_new_value;
    }
    if (initializing_qm)
	change_primary_name_of_frame(relation,value,initializing_qm);
    else {
	update_relation_instances_if_necessary(relation,Qrelation_name,
		value,old_value);
	update_representations_of_slot_value(2,relation,Qrelation_summary);
    }
    return VALUES_1(value);
}

/* RECLAIM-RELATION-NAME-VALUE */
Object reclaim_relation_name_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(104,45);
    put_relation_name(frame,Nil,Nil);
    return VALUES_1(Nil);
}

/* PUT-INVERSE-OF-RELATION */
Object put_inverse_of_relation(relation,value,initializing_qm)
    Object relation, value, initializing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, old_value;

    x_note_fn_call(104,46);
  next_loop:
    gensymed_symbol = ISVREF(relation,(SI_Long)23L);
    gensymed_symbol_1 = value;
    if (CAS_SVREF(relation,(SI_Long)23L,gensymed_symbol,gensymed_symbol_1)) {
	old_value = gensymed_symbol;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    old_value = Qnil;
  end_1:
    if (old_value)
	delete_from_directory_of_names(old_value,Qrelation_name);
    if (value)
	add_to_directory_of_names(value,Qrelation_name);
    if (initializing_qm)
	change_secondary_name_of_frame(relation,value,initializing_qm);
    else {
	update_relation_instances_if_necessary(relation,
		Qinverse_of_relation,value,old_value);
	update_representations_of_slot_value(2,relation,Qrelation_summary);
    }
    return VALUES_1(value);
}

/* RECLAIM-INVERSE-OF-RELATION-VALUE */
Object reclaim_inverse_of_relation_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(104,47);
    put_inverse_of_relation(frame,Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qclass_of_subject;   /* class-of-subject */

/* PUT-CLASS-OF-SUBJECT */
Object put_class_of_subject(relation,value,initializing_qm)
    Object relation, value, initializing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, old_value;

    x_note_fn_call(104,48);
  next_loop:
    gensymed_symbol = ISVREF(relation,(SI_Long)20L);
    gensymed_symbol_1 = value;
    if (CAS_SVREF(relation,(SI_Long)20L,gensymed_symbol,gensymed_symbol_1)) {
	old_value = gensymed_symbol;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    old_value = Qnil;
  end_1:
    if ( !TRUEP(initializing_qm)) {
	update_relation_instances_if_necessary(relation,Qclass_of_subject,
		value,old_value);
	update_representations_of_slot_value(2,relation,Qrelation_summary);
    }
    return VALUES_1(value);
}

static Object Qclass_of_object;    /* class-of-object */

/* PUT-CLASS-OF-OBJECT */
Object put_class_of_object(relation,value,initializing_qm)
    Object relation, value, initializing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, old_value;

    x_note_fn_call(104,49);
  next_loop:
    gensymed_symbol = ISVREF(relation,(SI_Long)21L);
    gensymed_symbol_1 = value;
    if (CAS_SVREF(relation,(SI_Long)21L,gensymed_symbol,gensymed_symbol_1)) {
	old_value = gensymed_symbol;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    old_value = Qnil;
  end_1:
    if ( !TRUEP(initializing_qm)) {
	update_relation_instances_if_necessary(relation,Qclass_of_object,
		value,old_value);
	update_representations_of_slot_value(2,relation,Qrelation_summary);
    }
    return VALUES_1(value);
}

static Object Qtype_of_relation;   /* type-of-relation */

/* PUT-TYPE-OF-RELATION */
Object put_type_of_relation(relation,value,initializing_qm)
    Object relation, value, initializing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, old_value;

    x_note_fn_call(104,50);
  next_loop:
    gensymed_symbol = ISVREF(relation,(SI_Long)24L);
    gensymed_symbol_1 = value;
    if (CAS_SVREF(relation,(SI_Long)24L,gensymed_symbol,gensymed_symbol_1)) {
	old_value = gensymed_symbol;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    old_value = Qnil;
  end_1:
    if ( !TRUEP(initializing_qm)) {
	update_relation_instances_if_necessary(relation,Qtype_of_relation,
		value,old_value);
	update_representations_of_slot_value(2,relation,Qrelation_summary);
    }
    return VALUES_1(value);
}

static Object Qrelation_is_symmetric;  /* relation-is-symmetric */

/* PUT-RELATION-IS-SYMMETRIC */
Object put_relation_is_symmetric(relation,value,initializing_qm)
    Object relation, value, initializing_qm;
{
    Object old_value_qm, new_value_qm;

    x_note_fn_call(104,51);
    old_value_qm = ISVREF(relation,(SI_Long)25L);
    new_value_qm = value ? ( !TRUEP(ISVREF(relation,(SI_Long)23L)) ? T : 
	    Nil) : Qnil;
    if ( !TRUEP(CAS_SVREF(relation,(SI_Long)25L,old_value_qm,new_value_qm)))
	error((SI_Long)1L,"what\?!");
    if ( !TRUEP(initializing_qm)) {
	update_relation_instances_if_necessary(relation,
		Qrelation_is_symmetric,new_value_qm,old_value_qm);
	update_representations_of_slot_value(2,relation,Qrelation_summary);
    }
    return VALUES_1(new_value_qm);
}

static Object string_constant_15;  /* "There is no relation named ~a." */

static Object string_constant_16;  /* "~a" */

static Object Qone_to_one;         /* one-to-one */

static Object Qone_to_many;        /* one-to-many */

static Object Qmany_to_one;        /* many-to-one */

static Object Qrelationships;      /* relationships */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qitems_in_this_relation;  /* items-in-this-relation */

/* ADD-TO-RELATION */
Object add_to_relation(given_name,item1,item2,now_case,
	    called_from_procedure_qm,invoke_rules_for_relation_chaining_qm)
    Object given_name, item1, item2, now_case, called_from_procedure_qm;
    Object invoke_rules_for_relation_chaining_qm;
{
    Object errors, relation, relation_name, other_name, subject, object;
    Object subject_class, object_class, subject_instances, object_instances;
    Object subject_instance_form, object_instance_form, unique_forward_qm;
    Object unique_reverse_qm, subject_and_object_switched_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, error_string, gensymed_symbol, sub_class_bit_vector;
    Object the_block, blocks, error_string_qm, previously_related_item;
    Object related_items, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object item, ab_less_than_branch_qm_, subject_related_items;
    Object object_related_items, ab_loop_it_, temp_3, temp_4, instance_items;
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, new_tree, old_tree, old_instance_form;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(104,52);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(item1);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(item2);
    errors = Nil;
    relation = Nil;
    relation_name = Nil;
    other_name = Nil;
    subject = Nil;
    object = Nil;
    subject_class = Nil;
    object_class = Nil;
    subject_instances = Nil;
    object_instances = Nil;
    subject_instance_form = Nil;
    object_instance_form = Nil;
    unique_forward_qm = Nil;
    unique_reverse_qm = Nil;
    subject_and_object_switched_qm = Nil;
    subject_instances = ISVREF(item2,(SI_Long)12L);
    if (subject_instances) {
	skip_list = CDR(subject_instances);
	key_value = given_name;
	key_hash_value = SXHASH_SYMBOL_1(given_name) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)7L;
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
	subject_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (subject_instance_form)
	    relation = ISVREF(subject_instance_form,(SI_Long)1L);
    }
    if ( !TRUEP(subject_instance_form))
	relation = get_instance_with_name_if_any(Qrelation,given_name);
    if ( !TRUEP(relation)) {
	error_string = tformat_text_string(2,string_constant_15,given_name);
	if (called_from_procedure_qm)
	    return VALUES_1(error_string);
	else {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_16,
			error_string);
	    reclaim_text_string(error_string);
	    return VALUES_1(FIX((SI_Long)0L));
	}
    }
    relation_name = ISVREF(relation,(SI_Long)22L);
    subject_class = ISVREF(relation,(SI_Long)21L);
    object_class = ISVREF(relation,(SI_Long)20L);
    if (EQ(given_name,ISVREF(relation,(SI_Long)22L))) {
	temp_2 =  !TRUEP(ISVREF(relation,(SI_Long)25L));
	if (temp_2);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(subject_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item2,(SI_Long)1L),
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
		    temp_2 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(object_class,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(item1,
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
			temp_2 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	if (temp_2);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(object_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item2,(SI_Long)1L),
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
		    temp_2 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_2 =  !temp_2;
	}
	if (temp_2);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(subject_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item1,(SI_Long)1L),
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
		    temp_2 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_2 =  !temp_2;
	}
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if (ISVREF(relation,(SI_Long)25L))
	    other_name = relation_name;
	else {
	    temp_1 = ISVREF(relation,(SI_Long)23L);
	    if (temp_1);
	    else
		temp_1 = ISVREF(relation,(SI_Long)26L);
	    other_name = temp_1;
	}
	subject = item2;
	object = item1;
	object_instances = ISVREF(object,(SI_Long)12L);
	if (object_instances) {
	    skip_list = CDR(object_instances);
	    key_value = other_name;
	    key_hash_value = SXHASH_SYMBOL_1(other_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
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
	    object_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	}
	else
	    object_instance_form = Nil;
    }
    else {
	other_name = given_name;
	subject = item1;
	object = item2;
	subject_and_object_switched_qm = T;
	object_instances = subject_instances;
	object_instance_form = subject_instance_form;
	subject_instances = ISVREF(subject,(SI_Long)12L);
	if (subject_instances) {
	    skip_list = CDR(subject_instances);
	    key_value = relation_name;
	    key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
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
	    subject_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	}
	else
	    subject_instance_form = Nil;
    }
    temp_1 = ISVREF(relation,(SI_Long)24L);
    if (EQ(temp_1,Qone_to_one)) {
	unique_forward_qm = T;
	unique_reverse_qm = T;
    }
    else if (EQ(temp_1,Qone_to_many))
	unique_forward_qm = T;
    else if (EQ(temp_1,Qmany_to_one))
	unique_reverse_qm = T;
    if (subject_instance_form) {
	the_block = object;
	blocks = ISVREF(subject_instance_form,(SI_Long)2L);
	skip_list = CDR(blocks);
	key_value = the_block;
	key_hash_value = SXHASH_SYMBOL_1(the_block) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)7L;
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
	temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return VALUES_1(Nil);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(subject_class,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(subject,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	    temp_2 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2)
	error_string_qm = tformat_text_string(6,string_constant,given_name,
		object,subject,subject,subject_class);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(object_class,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
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
		temp_2 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if ( !temp_2)
	    error_string_qm = tformat_text_string(6,string_constant,
		    given_name,object,subject,object,object_class);
	else
	    error_string_qm = Nil;
    }
    if (error_string_qm) {
	if (called_from_procedure_qm)
	    errors = error_string_qm;
	else {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_16,
			error_string_qm);
	    reclaim_text_string(error_string_qm);
	    errors = T;
	}
    }
    if (now_case) {
	previously_related_item = Nil;
	if (unique_forward_qm && subject_instance_form) {
	    temp_1 = object;
	    related_items = ISVREF(subject_instance_form,(SI_Long)2L);
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = related_items;
	    ab_binary_tree_form_ = related_items;
	    gensymed_symbol = CDR(related_items);
	    if (CONSP(gensymed_symbol)) {
		temp = M_CAR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
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
	    next_loop_12:
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
		    next_loop_13:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_12;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_13;
		    end_loop_12:;
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
		  goto end_loop_13;
	      item = M_CDR(ab_entry_cons_);
	      if (item) {
		  previously_related_item = item;
		  goto end_5;
	      }
	      goto next_loop_12;
	    end_loop_13:
	      previously_related_item = Nil;
	      goto end_5;
	      previously_related_item = Qnil;
	    end_5:;
	    POP_SPECIAL();
	    temp_2 =  !EQ(temp_1,previously_related_item);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    remove_from_relation(relation_name,previously_related_item,
		    subject,Nil,T,Nil);
	    subject_instances = ISVREF(subject,(SI_Long)12L);
	    if (subject_instances) {
		skip_list = CDR(subject_instances);
		key_value = relation_name;
		key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_14:
		if (level < ab_loop_bind_)
		    goto end_loop_14;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_15:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_16:
		if ( !TRUEP(marked))
		    goto end_loop_15;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_16;
	      end_loop_15:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_6;
		goto next_loop_15;
	      end_loop_16:
	      end_6:
		level = level - (SI_Long)1L;
		goto next_loop_14;
	      end_loop_14:;
		subject_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    object_instances = ISVREF(object,(SI_Long)12L);
	    if (object_instances) {
		skip_list = CDR(object_instances);
		key_value = other_name;
		key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_17:
		if (level < ab_loop_bind_)
		    goto end_loop_17;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_18:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_19:
		if ( !TRUEP(marked))
		    goto end_loop_18;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_19;
	      end_loop_18:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_18;
	      end_loop_19:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_17;
	      end_loop_17:;
		object_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	}
	if (unique_reverse_qm && object_instance_form) {
	    temp_1 = subject;
	    related_items = ISVREF(object_instance_form,(SI_Long)2L);
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = related_items;
	    ab_binary_tree_form_ = related_items;
	    gensymed_symbol = CDR(related_items);
	    if (CONSP(gensymed_symbol)) {
		temp = M_CAR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
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
	    next_loop_20:
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
		    next_loop_21:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_20;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_21;
		    end_loop_20:;
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
		  goto end_loop_21;
	      item = M_CDR(ab_entry_cons_);
	      if (item) {
		  previously_related_item = item;
		  goto end_8;
	      }
	      goto next_loop_20;
	    end_loop_21:
	      previously_related_item = Nil;
	      goto end_8;
	      previously_related_item = Qnil;
	    end_8:;
	    POP_SPECIAL();
	    temp_2 =  !EQ(temp_1,previously_related_item);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    remove_from_relation(relation_name,object,
		    previously_related_item,Nil,T,Nil);
	    subject_instances = ISVREF(subject,(SI_Long)12L);
	    if (subject_instances) {
		skip_list = CDR(subject_instances);
		key_value = relation_name;
		key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_22:
		if (level < ab_loop_bind_)
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_23:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_24:
		if ( !TRUEP(marked))
		    goto end_loop_23;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_24;
	      end_loop_23:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_9;
		goto next_loop_23;
	      end_loop_24:
	      end_9:
		level = level - (SI_Long)1L;
		goto next_loop_22;
	      end_loop_22:;
		subject_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    object_instances = ISVREF(object,(SI_Long)12L);
	    if (object_instances) {
		skip_list = CDR(object_instances);
		key_value = other_name;
		key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_25:
		if (level < ab_loop_bind_)
		    goto end_loop_25;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_26:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_27:
		if ( !TRUEP(marked))
		    goto end_loop_26;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_27;
	      end_loop_26:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_10;
		goto next_loop_26;
	      end_loop_27:
	      end_10:
		level = level - (SI_Long)1L;
		goto next_loop_25;
	      end_loop_25:;
		object_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	}
    }
    else {
	subject_related_items = subject_instance_form ? 
		ISVREF(subject_instance_form,(SI_Long)2L) : Nil;
	object_related_items = object_instance_form ? 
		ISVREF(object_instance_form,(SI_Long)2L) : Nil;
	if (unique_forward_qm) {
	    if (subject_instance_form) {
		if (subject_related_items) {
		    scope_conses = Scope_conses;
		    ab_node_stack_ = Nil;
		    ab_current_node_ = Nil;
		    ab_skip_list_form_ = subject_related_items;
		    ab_binary_tree_form_ = subject_related_items;
		    gensymed_symbol = CDR(subject_related_items);
		    if (CONSP(gensymed_symbol)) {
			temp_1 = M_CAR(gensymed_symbol);
			temp_2 = SIMPLE_VECTOR_P(temp_1);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			temp_1 = M_CDR(gensymed_symbol);
			ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		    }
		    else
			ab_skip_list_p_ = Nil;
		    ab_next_node_ = Nil;
		    ab_tail_node_ = Nil;
		    ab_current_alist_ = Nil;
		    ab_entry_cons_ = Nil;
		    item = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			    0);
		      ab_loop_it_ = Nil;
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
		    next_loop_28:
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
			      ab_entry_cons_ = 
				      scope_cons(ISVREF(ab_current_node_,
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
			    next_loop_29:
			      ab_less_than_branch_qm_ = 
				      ISVREF(ab_current_node_,(SI_Long)1L);
			      if ( !TRUEP(ab_less_than_branch_qm_))
				  goto end_loop_28;
			      ab_node_stack_ = scope_cons(ab_current_node_,
				      ab_node_stack_);
			      ab_current_node_ = ab_less_than_branch_qm_;
			      goto next_loop_29;
			    end_loop_28:;
			  }
			  else if (ab_node_stack_) {
			      ab_next_node_ = ab_node_stack_;
			      ab_current_node_ = M_CAR(ab_node_stack_);
			      ab_node_stack_ = M_CDR(ab_node_stack_);
			  }
			  else
			      ab_current_node_ = Nil;
			  if (ab_current_node_) {
			      ab_next_node_ = ISVREF(ab_current_node_,
				      (SI_Long)2L);
			      ab_current_alist_ = ISVREF(ab_current_node_,
				      (SI_Long)3L);
			      ab_entry_cons_ = M_CAR(ab_current_alist_);
			      ab_current_alist_ = M_CDR(ab_current_alist_);
			  }
		      }
		      if ( !TRUEP(ab_current_node_))
			  goto end_loop_29;
		      item = M_CDR(ab_entry_cons_);
		      ab_loop_it_ = item;
		      if (ab_loop_it_) {
			  temp_2 = TRUEP(ab_loop_it_);
			  goto end_11;
		      }
		      goto next_loop_28;
		    end_loop_29:
		      temp_2 = TRUEP(Qnil);
		    end_11:;
		    POP_SPECIAL();
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_3 = relation_name;
	    temp = relation;
	    if (subject_and_object_switched_qm)
		temp_4 = item1;
	    else {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = subject_related_items;
		ab_binary_tree_form_ = subject_related_items;
		gensymed_symbol = CDR(subject_related_items);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		next_loop_30:
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
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
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
			next_loop_31:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_30;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_31;
			end_loop_30:;
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
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_31;
		  item = M_CDR(ab_entry_cons_);
		  if (item) {
		      temp_4 = item;
		      goto end_12;
		  }
		  goto next_loop_30;
		end_loop_31:
		  temp_4 = Nil;
		  goto end_12;
		  temp_4 = Qnil;
		end_12:;
		POP_SPECIAL();
	    }
	    if (subject_and_object_switched_qm) {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = subject_related_items;
		ab_binary_tree_form_ = subject_related_items;
		gensymed_symbol = CDR(subject_related_items);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		next_loop_32:
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
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
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
			next_loop_33:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_32;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_33;
			end_loop_32:;
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
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_33;
		  item = M_CDR(ab_entry_cons_);
		  if (item) {
		      temp_1 = item;
		      goto end_13;
		  }
		  goto next_loop_32;
		end_loop_33:
		  temp_1 = Nil;
		  goto end_13;
		  temp_1 = Qnil;
		end_13:;
		POP_SPECIAL();
	    }
	    else
		temp_1 = item2;
	    error_string_qm = uniqueness_message(temp_3,given_name,temp,
		    item1,item2,temp_4,temp_1,called_from_procedure_qm);
	    temp_1 = error_string_qm;
	    if (temp_1);
	    else
		temp_1 = T;
	    errors = temp_1;
	}
	if (unique_reverse_qm) {
	    if (object_instance_form) {
		if (object_related_items) {
		    scope_conses = Scope_conses;
		    ab_node_stack_ = Nil;
		    ab_current_node_ = Nil;
		    ab_skip_list_form_ = object_related_items;
		    ab_binary_tree_form_ = object_related_items;
		    gensymed_symbol = CDR(object_related_items);
		    if (CONSP(gensymed_symbol)) {
			temp_1 = M_CAR(gensymed_symbol);
			temp_2 = SIMPLE_VECTOR_P(temp_1);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			temp_1 = M_CDR(gensymed_symbol);
			ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		    }
		    else
			ab_skip_list_p_ = Nil;
		    ab_next_node_ = Nil;
		    ab_tail_node_ = Nil;
		    ab_current_alist_ = Nil;
		    ab_entry_cons_ = Nil;
		    item = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			    0);
		      ab_loop_it_ = Nil;
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
		    next_loop_34:
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
			      ab_entry_cons_ = 
				      scope_cons(ISVREF(ab_current_node_,
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
			    next_loop_35:
			      ab_less_than_branch_qm_ = 
				      ISVREF(ab_current_node_,(SI_Long)1L);
			      if ( !TRUEP(ab_less_than_branch_qm_))
				  goto end_loop_34;
			      ab_node_stack_ = scope_cons(ab_current_node_,
				      ab_node_stack_);
			      ab_current_node_ = ab_less_than_branch_qm_;
			      goto next_loop_35;
			    end_loop_34:;
			  }
			  else if (ab_node_stack_) {
			      ab_next_node_ = ab_node_stack_;
			      ab_current_node_ = M_CAR(ab_node_stack_);
			      ab_node_stack_ = M_CDR(ab_node_stack_);
			  }
			  else
			      ab_current_node_ = Nil;
			  if (ab_current_node_) {
			      ab_next_node_ = ISVREF(ab_current_node_,
				      (SI_Long)2L);
			      ab_current_alist_ = ISVREF(ab_current_node_,
				      (SI_Long)3L);
			      ab_entry_cons_ = M_CAR(ab_current_alist_);
			      ab_current_alist_ = M_CDR(ab_current_alist_);
			  }
		      }
		      if ( !TRUEP(ab_current_node_))
			  goto end_loop_35;
		      item = M_CDR(ab_entry_cons_);
		      ab_loop_it_ = item;
		      if (ab_loop_it_) {
			  temp_2 = TRUEP(ab_loop_it_);
			  goto end_14;
		      }
		      goto next_loop_34;
		    end_loop_35:
		      temp_2 = TRUEP(Qnil);
		    end_14:;
		    POP_SPECIAL();
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_3 = relation_name;
	    temp = relation;
	    if (subject_and_object_switched_qm) {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = object_related_items;
		ab_binary_tree_form_ = object_related_items;
		gensymed_symbol = CDR(object_related_items);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		next_loop_36:
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
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
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
			next_loop_37:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_36;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_37;
			end_loop_36:;
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
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_37;
		  item = M_CDR(ab_entry_cons_);
		  if (item) {
		      temp_4 = item;
		      goto end_15;
		  }
		  goto next_loop_36;
		end_loop_37:
		  temp_4 = Nil;
		  goto end_15;
		  temp_4 = Qnil;
		end_15:;
		POP_SPECIAL();
	    }
	    else
		temp_4 = item1;
	    if (subject_and_object_switched_qm)
		temp_1 = item2;
	    else {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = object_related_items;
		ab_binary_tree_form_ = object_related_items;
		gensymed_symbol = CDR(object_related_items);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		next_loop_38:
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
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
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
			next_loop_39:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_38;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_39;
			end_loop_38:;
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
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_39;
		  item = M_CDR(ab_entry_cons_);
		  if (item) {
		      temp_1 = item;
		      goto end_16;
		  }
		  goto next_loop_38;
		end_loop_39:
		  temp_1 = Nil;
		  goto end_16;
		  temp_1 = Qnil;
		end_16:;
		POP_SPECIAL();
	    }
	    error_string_qm = uniqueness_message(temp_3,given_name,temp,
		    item1,item2,temp_4,temp_1,called_from_procedure_qm);
	    temp_1 = error_string_qm;
	    if (temp_1);
	    else
		temp_1 = T;
	    errors = temp_1;
	}
    }
    if (errors)
	return VALUES_1(errors);
    if (subject_instance_form) {
	instance_items = ISVREF(subject_instance_form,(SI_Long)2L);
	gensymed_symbol = object;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	set_skip_list_entry(instance_items,FIX((SI_Long)7L),Qeq,Nil,T,
		gensymed_symbol,temp_1,object);
    }
    else {
	subject_instance_form = make_relation_instance(relation_name,
		relation,object);
	if (subject_instances) {
	    gensymed_symbol = relation_name;
	    temp_1 = subject_instances;
	    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    set_skip_list_entry(temp_1,FIX((SI_Long)7L),Qeq,Nil,T,
		    gensymed_symbol,temp,subject_instance_form);
	}
	else {
	    tail = 
		    make_relation_instance_tree_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_relation_instance_tree_skip_list_sentinel(Most_negative_fixnum,
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
	    M_CAR(gensymed_symbol) = Qrelation_instance_tree;
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
		gensymed_symbol_4 = new_cons;
	    }
	    else
		gensymed_symbol_4 = Nil;
	    if ( !TRUEP(gensymed_symbol_4))
		gensymed_symbol_4 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_4) = head;
	    M_CDR(gensymed_symbol_4) = tail;
	    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
	    M_CDR(gensymed_symbol) = gensymed_symbol_4;
	    inline_note_allocate_cons(gensymed_symbol,Qlookup);
	    new_tree = gensymed_symbol;
	    if (CAS_SVREF(subject,(SI_Long)12L,Nil,new_tree)) {
		gensymed_symbol = relation_name;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		set_skip_list_entry(new_tree,FIX((SI_Long)7L),Qeq,Nil,T,
			gensymed_symbol,temp_1,subject_instance_form);
	    }
	    else {
		temp_1 = ISVREF(subject,(SI_Long)12L);
		reclaim_relation_instances(new_tree);
		old_tree = temp_1;
		skip_list = CDR(old_tree);
		key_value = relation_name;
		key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_40:
		if (level < ab_loop_bind_)
		    goto end_loop_40;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_41:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_42:
		if ( !TRUEP(marked))
		    goto end_loop_41;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_42;
	      end_loop_41:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_17;
		goto next_loop_41;
	      end_loop_42:
	      end_17:
		level = level - (SI_Long)1L;
		goto next_loop_40;
	      end_loop_40:;
		old_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (old_instance_form) {
		    reclaim_relation_instance(subject_instance_form);
		    subject_instance_form = old_instance_form;
		    instance_items = ISVREF(subject_instance_form,(SI_Long)2L);
		    gensymed_symbol = object;
		    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    set_skip_list_entry(instance_items,FIX((SI_Long)7L),
			    Qeq,Nil,T,gensymed_symbol,temp_1,object);
		}
		else {
		    gensymed_symbol = relation_name;
		    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    set_skip_list_entry(old_tree,FIX((SI_Long)7L),Qeq,Nil,
			    T,gensymed_symbol,temp_1,subject_instance_form);
		}
	    }
	}
    }
    if ( !EQ(item1,item2) ||  !TRUEP(ISVREF(relation,(SI_Long)25L))) {
	if (EQ(item1,item2)) {
	    object_instances = ISVREF(object,(SI_Long)12L);
	    if (object_instances) {
		skip_list = CDR(object_instances);
		key_value = other_name;
		key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_43:
		if (level < ab_loop_bind_)
		    goto end_loop_43;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_44:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_45:
		if ( !TRUEP(marked))
		    goto end_loop_44;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_45;
	      end_loop_44:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_18;
		goto next_loop_44;
	      end_loop_45:
	      end_18:
		level = level - (SI_Long)1L;
		goto next_loop_43;
	      end_loop_43:;
		object_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    else
		object_instance_form = Nil;
	}
	if (object_instance_form) {
	    instance_items = ISVREF(object_instance_form,(SI_Long)2L);
	    gensymed_symbol = subject;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    set_skip_list_entry(instance_items,FIX((SI_Long)7L),Qeq,Nil,T,
		    gensymed_symbol,temp_1,subject);
	}
	else {
	    object_instance_form = make_relation_instance(other_name,
		    relation,subject);
	    if (object_instances) {
		gensymed_symbol = other_name;
		temp_1 = object_instances;
		temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		set_skip_list_entry(temp_1,FIX((SI_Long)7L),Qeq,Nil,T,
			gensymed_symbol,temp,object_instance_form);
	    }
	    else {
		tail = 
			make_relation_instance_tree_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_relation_instance_tree_skip_list_sentinel(Most_negative_fixnum,
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
		M_CAR(gensymed_symbol) = Qrelation_instance_tree;
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
		    gensymed_symbol_4 = new_cons;
		}
		else
		    gensymed_symbol_4 = Nil;
		if ( !TRUEP(gensymed_symbol_4))
		    gensymed_symbol_4 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_4) = head;
		M_CDR(gensymed_symbol_4) = tail;
		inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		M_CDR(gensymed_symbol) = gensymed_symbol_4;
		inline_note_allocate_cons(gensymed_symbol,Qlookup);
		new_tree = gensymed_symbol;
		if (CAS_SVREF(object,(SI_Long)12L,Nil,new_tree)) {
		    gensymed_symbol = other_name;
		    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    set_skip_list_entry(new_tree,FIX((SI_Long)7L),Qeq,Nil,
			    T,gensymed_symbol,temp_1,object_instance_form);
		}
		else {
		    temp_1 = ISVREF(object,(SI_Long)12L);
		    reclaim_relation_instances(new_tree);
		    old_tree = temp_1;
		    skip_list = CDR(old_tree);
		    key_value = other_name;
		    key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)7L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_46:
		    if (level < ab_loop_bind_)
			goto end_loop_46;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_47:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_48:
		    if ( !TRUEP(marked))
			goto end_loop_47;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_48;
		  end_loop_47:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_19;
		    goto next_loop_47;
		  end_loop_48:
		  end_19:
		    level = level - (SI_Long)1L;
		    goto next_loop_46;
		  end_loop_46:;
		    old_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (old_instance_form) {
			reclaim_relation_instance(object_instance_form);
			object_instance_form = old_instance_form;
			instance_items = ISVREF(object_instance_form,
				(SI_Long)2L);
			gensymed_symbol = subject;
			temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			set_skip_list_entry(instance_items,
				FIX((SI_Long)7L),Qeq,Nil,T,gensymed_symbol,
				temp_1,subject);
		    }
		    else {
			gensymed_symbol = other_name;
			temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			set_skip_list_entry(old_tree,FIX((SI_Long)7L),Qeq,
				Nil,T,gensymed_symbol,temp_1,
				object_instance_form);
		    }
		}
	    }
	}
	if (invoke_rules_for_relation_chaining_qm &&  !EQ(other_name,
		ISVREF(relation,(SI_Long)26L)))
	    invoke_rules_for_relation_chaining(other_name,subject,object,T);
    }
    if (invoke_rules_for_relation_chaining_qm) {
	invoke_rules_for_relation_chaining(relation_name,object,subject,T);
	temp_1 = subject;
	update_subscriptions_from_virtual_attribute_change(temp_1,
		get_property_value_function(3,
		get_symbol_properties_function(Qrelationships),
		Qvirtual_attribute,Nil),Nil);
	temp_1 = object;
	update_subscriptions_from_virtual_attribute_change(temp_1,
		get_property_value_function(3,
		get_symbol_properties_function(Qrelationships),
		Qvirtual_attribute,Nil),Nil);
	temp_1 = relation;
	update_subscriptions_from_virtual_attribute_change(temp_1,
		get_property_value_function(3,
		get_symbol_properties_function(Qitems_in_this_relation),
		Qvirtual_attribute,Nil),Nil);
    }
    return VALUES_1(Nil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_17;  /* "Because the relation ~a is ~a and ~NF is currently ~a ~NF, you ~
				    *                cannot conclude that ~NF is ~a ~NF."
				    */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

/* UNIQUENESS-MESSAGE */
Object uniqueness_message(relation_name,given_name,relation,item1,item2,
	    item_x,item_y,called_from_procedure_qm)
    Object relation_name, given_name, relation, item1, item2, item_x, item_y;
    Object called_from_procedure_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_string, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(104,53);
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
	      tformat(9,string_constant_17,relation_name,ISVREF(relation,
		      (SI_Long)24L),item_x,given_name,item_y,item1,
		      given_name,item2);
	      error_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (called_from_procedure_qm)
	return VALUES_1(error_string);
    else {
	if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	    if ( !TRUEP(Defer_notifications_qm))
		break_out_of_debug_messages();
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		    6);
	      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		      5);
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
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
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  write_warning_message_header(FIX((SI_Long)1L));
			  twrite_general_string(error_string);
			  temp = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_user_1(temp);
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	return reclaim_text_string(error_string);
    }
}

/* REMOVE-FROM-RELATION */
Object remove_from_relation(given_name,item1,item2,
	    called_from_procedure_qm,invoke_rules_for_relation_chaining_qm,
	    remove_given_name_direction_only_qm)
    Object given_name, item1, item2, called_from_procedure_qm;
    Object invoke_rules_for_relation_chaining_qm;
    Object remove_given_name_direction_only_qm;
{
    Object subject_instances, object_instances, subject_instance_form;
    Object object_instance_form, other_name, relation, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object error_string, blocks, found_item, gensymed_symbol, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, item, ab_less_than_branch_qm_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(104,54);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(item1);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(item2);
    subject_instances = Nil;
    object_instances = Nil;
    subject_instance_form = Nil;
    object_instance_form = Nil;
    other_name = Nil;
    relation = Nil;
    subject_instances = ISVREF(item2,(SI_Long)12L);
    if (subject_instances) {
	skip_list = CDR(subject_instances);
	key_value = given_name;
	key_hash_value = SXHASH_SYMBOL_1(given_name) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)7L;
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
	subject_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (subject_instance_form)
	    relation = ISVREF(subject_instance_form,(SI_Long)1L);
    }
    if ( !(get_instance_with_name_if_any(Qrelation,given_name) || 
	    remove_given_name_direction_only_qm && relation && 
	    (EQ(ISVREF(relation,(SI_Long)22L),given_name) || 
	    EQ(ISVREF(relation,(SI_Long)23L),given_name) || 
	    EQ(ISVREF(relation,(SI_Long)26L),given_name)))) {
	error_string = tformat_text_string(2,string_constant_15,given_name);
	if (called_from_procedure_qm)
	    return VALUES_1(error_string);
	else {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_16,
			error_string);
	    reclaim_text_string(error_string);
	    return VALUES_1(Nil);
	}
    }
    if ( !TRUEP(subject_instances))
	return VALUES_1(Nil);
    if ( !TRUEP(subject_instance_form))
	return VALUES_1(Nil);
    blocks = ISVREF(subject_instance_form,(SI_Long)2L);
    skip_list = CDR(blocks);
    key_value = item1;
    key_hash_value = SXHASH_SYMBOL_1(item1) & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)7L;
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
    found_item = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (found_item) {
	if (invoke_rules_for_relation_chaining_qm)
	    invoke_rules_for_relation_chaining(given_name,item1,item2,Nil);
	gensymed_symbol = item1;
	set_skip_list_entry(blocks,FIX((SI_Long)7L),Qeq,Nil,T,
		gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum)),Nil);
	delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),item1,blocks,
		FIX((SI_Long)7L),FIX(SXHASH_SYMBOL_1(item1) & 
		IFIX(Most_positive_fixnum)));
	temp_2 =  !TRUEP(blocks);
	if (temp_2);
	else {
	    gensymed_symbol = CDR(blocks);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = M_CDR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = M_CDR(blocks);
		temp_1 = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol),
			(SI_Long)0L),(SI_Long)0L));
		temp_2 = EQ(temp_1,M_CDR(gensymed_symbol));
	    }
	    else
		temp_2 =  !TRUEP(M_CDR(blocks));
	    if (temp_2);
	    else {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = blocks;
		ab_binary_tree_form_ = blocks;
		gensymed_symbol = CDR(blocks);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		next_loop_6:
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
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
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
			next_loop_7:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_6;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_7;
			end_loop_6:;
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
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_7;
		  item = M_CDR(ab_entry_cons_);
		  if (item) {
		      temp_2 = TRUEP(Nil);
		      goto end_3;
		  }
		  goto next_loop_6;
		end_loop_7:
		  temp_2 = TRUEP(T);
		  goto end_3;
		  temp_2 = TRUEP(Qnil);
		end_3:;
		POP_SPECIAL();
	    }
	}
	if (temp_2) {
	    gensymed_symbol = given_name;
	    temp_1 = subject_instances;
	    set_skip_list_entry(temp_1,FIX((SI_Long)7L),Qeq,Nil,T,
		    gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),Nil);
	    temp_1 = subject_instances;
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),given_name,temp_1,
		    FIX((SI_Long)7L),FIX(SXHASH_SYMBOL_1(given_name) & 
		    IFIX(Most_positive_fixnum)));
	    reclaim_relation_instance(subject_instance_form);
	    subject_instance_form = Nil;
	}
    }
    if ( !TRUEP(remove_given_name_direction_only_qm)) {
	if (ISVREF(relation,(SI_Long)25L))
	    other_name = given_name;
	else if (EQ(given_name,ISVREF(relation,(SI_Long)22L))) {
	    temp_1 = ISVREF(relation,(SI_Long)23L);
	    if (temp_1);
	    else
		temp_1 = ISVREF(relation,(SI_Long)26L);
	    other_name = temp_1;
	}
	else
	    other_name = ISVREF(relation,(SI_Long)22L);
	if ( !EQ(item1,item2) ||  !EQ(given_name,other_name)) {
	    if (SYMBOL_PACKAGE(other_name) && 
		    invoke_rules_for_relation_chaining_qm)
		invoke_rules_for_relation_chaining(other_name,item2,item1,Nil);
	    object_instances = ISVREF(item1,(SI_Long)12L);
	    if (object_instances) {
		skip_list = CDR(object_instances);
		key_value = other_name;
		key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_8:
		if (level < ab_loop_bind_)
		    goto end_loop_8;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_9:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_10:
		if ( !TRUEP(marked))
		    goto end_loop_9;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_10;
	      end_loop_9:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_4;
		goto next_loop_9;
	      end_loop_10:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_8;
	      end_loop_8:;
		object_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    if (object_instance_form) {
		blocks = ISVREF(object_instance_form,(SI_Long)2L);
		skip_list = CDR(blocks);
		key_value = item2;
		key_hash_value = SXHASH_SYMBOL_1(item2) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_11:
		if (level < ab_loop_bind_)
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_12:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_13:
		if ( !TRUEP(marked))
		    goto end_loop_12;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_13;
	      end_loop_12:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_5;
		goto next_loop_12;
	      end_loop_13:
	      end_5:
		level = level - (SI_Long)1L;
		goto next_loop_11;
	      end_loop_11:;
		found_item = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (found_item) {
		    gensymed_symbol = item2;
		    set_skip_list_entry(blocks,FIX((SI_Long)7L),Qeq,Nil,T,
			    gensymed_symbol,
			    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum)),Nil);
		    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),item2,
			    blocks,FIX((SI_Long)7L),
			    FIX(SXHASH_SYMBOL_1(item2) & 
			    IFIX(Most_positive_fixnum)));
		}
		temp_2 =  !TRUEP(blocks);
		if (temp_2);
		else {
		    gensymed_symbol = CDR(blocks);
		    if (CONSP(gensymed_symbol)) {
			temp_1 = M_CAR(gensymed_symbol);
			temp_2 = SIMPLE_VECTOR_P(temp_1);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			temp_1 = M_CDR(gensymed_symbol);
			temp_2 = SIMPLE_VECTOR_P(temp_1);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			gensymed_symbol = M_CDR(blocks);
			temp_1 = 
				ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol),
				(SI_Long)0L),(SI_Long)0L));
			temp_2 = EQ(temp_1,M_CDR(gensymed_symbol));
		    }
		    else
			temp_2 =  !TRUEP(M_CDR(blocks));
		    if (temp_2);
		    else {
			scope_conses = Scope_conses;
			ab_node_stack_ = Nil;
			ab_current_node_ = Nil;
			ab_skip_list_form_ = blocks;
			ab_binary_tree_form_ = blocks;
			gensymed_symbol = CDR(blocks);
			if (CONSP(gensymed_symbol)) {
			    temp_1 = M_CAR(gensymed_symbol);
			    temp_2 = SIMPLE_VECTOR_P(temp_1);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    temp_1 = M_CDR(gensymed_symbol);
			    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T :
				     Nil;
			}
			else
			    ab_skip_list_p_ = Nil;
			ab_next_node_ = Nil;
			ab_tail_node_ = Nil;
			ab_current_alist_ = Nil;
			ab_entry_cons_ = Nil;
			item = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
				0);
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
			next_loop_14:
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
				  ab_entry_cons_ = 
					  scope_cons(ISVREF(ab_current_node_,
					  (SI_Long)2L),
					  ISVREF(ab_current_node_,
					  (SI_Long)3L));
			      }
			      else
				  ab_current_node_ = Nil;
			  }
			  else {
			      if (ab_next_node_) {
				  ab_current_node_ = ab_next_node_;
				  ab_less_than_branch_qm_ = Nil;
				next_loop_15:
				  ab_less_than_branch_qm_ = 
					  ISVREF(ab_current_node_,(SI_Long)1L);
				  if ( !TRUEP(ab_less_than_branch_qm_))
				      goto end_loop_14;
				  ab_node_stack_ = 
					  scope_cons(ab_current_node_,
					  ab_node_stack_);
				  ab_current_node_ = ab_less_than_branch_qm_;
				  goto next_loop_15;
				end_loop_14:;
			      }
			      else if (ab_node_stack_) {
				  ab_next_node_ = ab_node_stack_;
				  ab_current_node_ = M_CAR(ab_node_stack_);
				  ab_node_stack_ = M_CDR(ab_node_stack_);
			      }
			      else
				  ab_current_node_ = Nil;
			      if (ab_current_node_) {
				  ab_next_node_ = ISVREF(ab_current_node_,
					  (SI_Long)2L);
				  ab_current_alist_ = 
					  ISVREF(ab_current_node_,(SI_Long)3L);
				  ab_entry_cons_ = M_CAR(ab_current_alist_);
				  ab_current_alist_ = M_CDR(ab_current_alist_);
			      }
			  }
			  if ( !TRUEP(ab_current_node_))
			      goto end_loop_15;
			  item = M_CDR(ab_entry_cons_);
			  if (item) {
			      temp_2 = TRUEP(Nil);
			      goto end_6;
			  }
			  goto next_loop_14;
			end_loop_15:
			  temp_2 = TRUEP(T);
			  goto end_6;
			  temp_2 = TRUEP(Qnil);
			end_6:;
			POP_SPECIAL();
		    }
		}
		if (temp_2) {
		    gensymed_symbol = other_name;
		    temp_1 = object_instances;
		    set_skip_list_entry(temp_1,FIX((SI_Long)7L),Qeq,Nil,T,
			    gensymed_symbol,
			    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum)),Nil);
		    temp_1 = other_name;
		    temp = object_instances;
		    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp_1,
			    temp,FIX((SI_Long)7L),
			    FIX(SXHASH_SYMBOL_1(other_name) & 
			    IFIX(Most_positive_fixnum)));
		    reclaim_relation_instance(object_instance_form);
		    object_instance_form = Nil;
		}
	    }
	}
    }
    if (invoke_rules_for_relation_chaining_qm) {
	update_subscriptions_from_virtual_attribute_change(item1,
		get_property_value_function(3,
		get_symbol_properties_function(Qrelationships),
		Qvirtual_attribute,Nil),Nil);
	update_subscriptions_from_virtual_attribute_change(item2,
		get_property_value_function(3,
		get_symbol_properties_function(Qrelationships),
		Qvirtual_attribute,Nil),Nil);
	temp_1 = relation;
	update_subscriptions_from_virtual_attribute_change(temp_1,
		get_property_value_function(3,
		get_symbol_properties_function(Qitems_in_this_relation),
		Qvirtual_attribute,Nil),Nil);
    }
    return VALUES_1(T);
}

DEFINE_VARIABLE_WITH_SYMBOL(Resolving_definitional_name_conflicts_qm, Qresolving_definitional_name_conflicts_qm);

/* UPDATE-RELATION-INSTANCES-IF-NECESSARY */
Object update_relation_instances_if_necessary(relation,slot_name,new_value,
	    old_value)
    Object relation, slot_name, new_value, old_value;
{
    x_note_fn_call(104,55);
    if ( !TRUEP(Resolving_definitional_name_conflicts_qm)) {
	if ( !EQ(old_value,new_value) && (ISVREF(relation,(SI_Long)22L) || 
		EQ(slot_name,Qrelation_name))) {
	    if (EQ(slot_name,Qrelation_name))
		update_relation_name_for_relation_instances(relation,
			new_value,old_value);
	    else if (EQ(slot_name,Qinverse_of_relation))
		update_relation_inverse_name_for_relation_instances(relation,
			new_value,old_value);
	    else if (EQ(slot_name,Qclass_of_subject))
		update_relation_subject_class_for_relation_instances(relation,
			new_value,old_value);
	    else if (EQ(slot_name,Qclass_of_object))
		update_relation_object_class_for_relation_instances(relation,
			new_value,old_value);
	    else if (EQ(slot_name,Qtype_of_relation))
		update_type_of_relation_for_relation_instances(relation,
			new_value,old_value);
	    else if (EQ(slot_name,Qrelation_is_symmetric))
		update_relation_is_symmetric_for_relation_instances(relation,
			new_value,old_value);
	    else;
	}
    }
    return VALUES_1(Nil);
}

/* UPDATE-RELATION-NAME-FOR-RELATION-INSTANCES */
Object update_relation_name_for_relation_instances(relation,new_name,old_name)
    Object relation, new_name, old_name;
{
    x_note_fn_call(104,56);
    if ( !TRUEP(old_name));
    else if ( !TRUEP(new_name))
	remove_all_relations_instances_for_relation(relation,old_name);
    else
	change_relation_name_or_inverse_for_relation_instances(relation,
		new_name,old_name,Nil);
    return VALUES_1(Nil);
}

/* UPDATE-RELATION-INVERSE-NAME-FOR-RELATION-INSTANCES */
Object update_relation_inverse_name_for_relation_instances(relation,
	    new_inverse_name,old_inverse_name)
    Object relation, new_inverse_name, old_inverse_name;
{
    x_note_fn_call(104,57);
    if ( !TRUEP(new_inverse_name)) {
	if (old_inverse_name)
	    change_relation_name_or_inverse_for_relation_instances(relation,
		    ISVREF(relation,(SI_Long)26L),old_inverse_name,T);
    }
    else if ( !TRUEP(old_inverse_name))
	change_relation_name_or_inverse_for_relation_instances(relation,
		new_inverse_name,ISVREF(relation,(SI_Long)26L),T);
    else
	change_relation_name_or_inverse_for_relation_instances(relation,
		new_inverse_name,old_inverse_name,T);
    return VALUES_1(Nil);
}

/* CHANGE-RELATION-NAME-OR-INVERSE-FOR-RELATION-INSTANCES */
Object change_relation_name_or_inverse_for_relation_instances(relation,
	    new_name,old_name,new_name_is_inverse_p_qm)
    Object relation, new_name, old_name, new_name_is_inverse_p_qm;
{
    Object relation_is_symmetric_p_qm, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, item, relation_instances_qm;
    Object relation_has_inverse_p_qm, other_name_qm, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_binary_tree_form_;
    Object gensymed_symbol, temp_1, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance_form, relation_name_for_item, relation_for_item;
    Object ab_less_than_branch_qm_, gensymed_symbol_1, ab_node_stack__1;
    Object ab_current_node__1, ab_skip_list_p__1, ab_next_node__1;
    Object ab_tail_node__1, ab_current_alist__1, ab_entry_cons__1;
    Object related_subject_item, subject_relation_instances_qm;
    Object ab_node_stack__2, ab_current_node__2, ab_skip_list_p__2;
    Object ab_next_node__2, ab_tail_node__2, ab_current_alist__2;
    Object ab_entry_cons__2, subject_relation_instance_form;
    Object subject_relation_name, subject_relation;
    char temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(104,58);
    relation_is_symmetric_p_qm = ISVREF(relation,(SI_Long)25L);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,3);
      relation_instances_qm = Nil;
      relation_has_inverse_p_qm = ISVREF(relation,(SI_Long)23L);
      other_name_qm = Nil;
      ab_loopvar_ = collect_subclasses( !TRUEP(new_name_is_inverse_p_qm) ? 
	      ISVREF(relation,(SI_Long)21L) : ISVREF(relation,(SI_Long)20L));
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
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances_qm = ISVREF(item,(SI_Long)12L);
      if (relation_instances_qm) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = relation_instances_qm;
	  ab_binary_tree_form_ = relation_instances_qm;
	  gensymed_symbol = CDR(relation_instances_qm);
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
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  relation_instance_form = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,2);
	    relation_name_for_item = Nil;
	    relation_for_item = Nil;
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
	  next_loop_2:
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
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    relation_instance_form = M_CDR(ab_entry_cons_);
	    relation_name_for_item = ISVREF(relation_instance_form,
		    (SI_Long)0L);
	    relation_for_item = ISVREF(relation_instance_form,(SI_Long)1L);
	    if (EQ(relation,relation_for_item) && 
		    EQ(relation_name_for_item,old_name)) {
	      next_loop_4:
		gensymed_symbol = ISVREF(relation_instance_form,(SI_Long)0L);
		gensymed_symbol_1 = new_name;
		if (CAS_SVREF(relation_instance_form,(SI_Long)0L,
			gensymed_symbol,gensymed_symbol_1))
		    goto end_1;
		goto next_loop_4;
	      end_loop_4:
	      end_1:
		if ( !(new_name_is_inverse_p_qm || 
			relation_has_inverse_p_qm || 
			relation_is_symmetric_p_qm)) {
		    other_name_qm = ISVREF(relation,(SI_Long)26L);
		    scope_conses = Scope_conses;
		    ab_node_stack__1 = Nil;
		    ab_current_node__1 = Nil;
		    ab_skip_list_form_ = ISVREF(relation_instance_form,
			    (SI_Long)2L);
		    ab_binary_tree_form_ = ISVREF(relation_instance_form,
			    (SI_Long)2L);
		    temp_1 = ISVREF(relation_instance_form,(SI_Long)2L);
		    gensymed_symbol = CDR(temp_1);
		    if (CONSP(gensymed_symbol)) {
			temp_1 = M_CAR(gensymed_symbol);
			temp = SIMPLE_VECTOR_P(temp_1);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			temp_1 = M_CDR(gensymed_symbol);
			ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		    }
		    else
			ab_skip_list_p__1 = Nil;
		    ab_next_node__1 = Nil;
		    ab_tail_node__1 = Nil;
		    ab_current_alist__1 = Nil;
		    ab_entry_cons__1 = Nil;
		    related_subject_item = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			    1);
		      subject_relation_instances_qm = Nil;
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
		    next_loop_5:
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
				      (SI_Long)2L),
				      ISVREF(ab_current_node__1,(SI_Long)3L));
			  }
			  else
			      ab_current_node__1 = Nil;
		      }
		      else {
			  if (ab_next_node__1) {
			      ab_current_node__1 = ab_next_node__1;
			      ab_less_than_branch_qm_ = Nil;
			    next_loop_6:
			      ab_less_than_branch_qm_ = 
				      ISVREF(ab_current_node__1,(SI_Long)1L);
			      if ( !TRUEP(ab_less_than_branch_qm_))
				  goto end_loop_5;
			      ab_node_stack__1 = 
				      scope_cons(ab_current_node__1,
				      ab_node_stack__1);
			      ab_current_node__1 = ab_less_than_branch_qm_;
			      goto next_loop_6;
			    end_loop_5:;
			  }
			  else if (ab_node_stack__1) {
			      ab_next_node__1 = ab_node_stack__1;
			      ab_current_node__1 = M_CAR(ab_node_stack__1);
			      ab_node_stack__1 = M_CDR(ab_node_stack__1);
			  }
			  else
			      ab_current_node__1 = Nil;
			  if (ab_current_node__1) {
			      ab_next_node__1 = ISVREF(ab_current_node__1,
				      (SI_Long)2L);
			      ab_current_alist__1 = 
				      ISVREF(ab_current_node__1,(SI_Long)3L);
			      ab_entry_cons__1 = M_CAR(ab_current_alist__1);
			      ab_current_alist__1 = M_CDR(ab_current_alist__1);
			  }
		      }
		      if ( !TRUEP(ab_current_node__1))
			  goto end_loop_6;
		      related_subject_item = M_CDR(ab_entry_cons__1);
		      subject_relation_instances_qm = 
			      ISVREF(related_subject_item,(SI_Long)12L);
		      if ( !TRUEP(subject_relation_instances_qm))
			  goto end_loop_6;
		      scope_conses = Scope_conses;
		      ab_node_stack__2 = Nil;
		      ab_current_node__2 = Nil;
		      ab_skip_list_form_ = subject_relation_instances_qm;
		      ab_binary_tree_form_ = subject_relation_instances_qm;
		      gensymed_symbol = CDR(subject_relation_instances_qm);
		      if (CONSP(gensymed_symbol)) {
			  temp_1 = M_CAR(gensymed_symbol);
			  temp = SIMPLE_VECTOR_P(temp_1);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  temp_1 = M_CDR(gensymed_symbol);
			  ab_skip_list_p__2 = SIMPLE_VECTOR_P(temp_1) ? T :
				   Nil;
		      }
		      else
			  ab_skip_list_p__2 = Nil;
		      ab_next_node__2 = Nil;
		      ab_tail_node__2 = Nil;
		      ab_current_alist__2 = Nil;
		      ab_entry_cons__2 = Nil;
		      subject_relation_instance_form = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			      0);
			subject_relation_name = Nil;
			subject_relation = Nil;
			if (ab_skip_list_p__2) {
			    ab_next_node__2 = 
				    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
				    (SI_Long)0L),(SI_Long)0L));
			    ab_tail_node__2 = M_CDR(M_CDR(ab_skip_list_form_));
			    if (EQ(ab_next_node__2,ab_tail_node__2))
				ab_next_node__2 = Nil;
			}
			else
			    ab_next_node__2 = M_CDR(ab_binary_tree_form_);
		      next_loop_7:
			if (ab_current_alist__2) {
			    ab_entry_cons__2 = M_CAR(ab_current_alist__2);
			    ab_current_alist__2 = M_CDR(ab_current_alist__2);
			}
			else if (ab_skip_list_p__2) {
			    if (ab_next_node__2) {
				ab_current_node__2 = ab_next_node__2;
				ab_next_node__2 = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__2,
					(SI_Long)0L),(SI_Long)0L));
				if (EQ(ab_next_node__2,ab_tail_node__2))
				    ab_next_node__2 = Nil;
				ab_entry_cons__2 = 
					scope_cons(ISVREF(ab_current_node__2,
					(SI_Long)2L),
					ISVREF(ab_current_node__2,
					(SI_Long)3L));
			    }
			    else
				ab_current_node__2 = Nil;
			}
			else {
			    if (ab_next_node__2) {
				ab_current_node__2 = ab_next_node__2;
				ab_less_than_branch_qm_ = Nil;
			      next_loop_8:
				ab_less_than_branch_qm_ = 
					ISVREF(ab_current_node__2,(SI_Long)1L);
				if ( !TRUEP(ab_less_than_branch_qm_))
				    goto end_loop_7;
				ab_node_stack__2 = 
					scope_cons(ab_current_node__2,
					ab_node_stack__2);
				ab_current_node__2 = ab_less_than_branch_qm_;
				goto next_loop_8;
			      end_loop_7:;
			    }
			    else if (ab_node_stack__2) {
				ab_next_node__2 = ab_node_stack__2;
				ab_current_node__2 = M_CAR(ab_node_stack__2);
				ab_node_stack__2 = M_CDR(ab_node_stack__2);
			    }
			    else
				ab_current_node__2 = Nil;
			    if (ab_current_node__2) {
				ab_next_node__2 = 
					ISVREF(ab_current_node__2,(SI_Long)2L);
				ab_current_alist__2 = 
					ISVREF(ab_current_node__2,(SI_Long)3L);
				ab_entry_cons__2 = M_CAR(ab_current_alist__2);
				ab_current_alist__2 = 
					M_CDR(ab_current_alist__2);
			    }
			}
			if ( !TRUEP(ab_current_node__2))
			    goto end_loop_8;
			subject_relation_instance_form = 
				M_CDR(ab_entry_cons__2);
			subject_relation_name = 
				ISVREF(subject_relation_instance_form,
				(SI_Long)0L);
			subject_relation = 
				ISVREF(subject_relation_instance_form,
				(SI_Long)1L);
			if (EQ(relation,subject_relation) &&  
				!(EQ(subject_relation_name,old_name) || 
				EQ(subject_relation_name,new_name))) {
			    if ( 
				    !TRUEP(CAS_SVREF(subject_relation_instance_form,
				    (SI_Long)0L,subject_relation_name,
				    other_name_qm)))
				error((SI_Long)1L,"what\?!");
			}
			goto next_loop_7;
		      end_loop_8:;
		      POP_SPECIAL();
		      goto next_loop_5;
		    end_loop_6:;
		    POP_SPECIAL();
		}
	    }
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    if ( !( !TRUEP(new_name_is_inverse_p_qm) && relation_is_symmetric_p_qm))
	return VALUES_1(Nil);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      relation_instances_qm = Nil;
      ab_loopvar_ = collect_subclasses(ISVREF(relation,(SI_Long)20L));
    next_loop_9:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_10:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_9;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_9;
	  goto next_loop_10;
	end_loop_9:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_10;
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances_qm = ISVREF(item,(SI_Long)12L);
      if (relation_instances_qm) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = relation_instances_qm;
	  ab_binary_tree_form_ = relation_instances_qm;
	  gensymed_symbol = CDR(relation_instances_qm);
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
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  relation_instance_form = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    relation_name_for_item = Nil;
	    relation_for_item = Nil;
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
	  next_loop_11:
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
		  next_loop_12:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_11;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_12;
		  end_loop_11:;
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
		goto end_loop_12;
	    relation_instance_form = M_CDR(ab_entry_cons_);
	    relation_name_for_item = ISVREF(relation_instance_form,
		    (SI_Long)0L);
	    relation_for_item = ISVREF(relation_instance_form,(SI_Long)1L);
	    if (EQ(relation,relation_for_item) && 
		    EQ(relation_name_for_item,old_name)) {
		if ( !TRUEP(CAS_SVREF(relation_instance_form,(SI_Long)0L,
			relation_name_for_item,new_name)))
		    error((SI_Long)1L,"what\?!");
	    }
	    goto next_loop_11;
	  end_loop_12:;
	  POP_SPECIAL();
      }
      goto next_loop_9;
    end_loop_10:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qitem;               /* item */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

/* UPDATE-RELATION-SUBJECT-CLASS-FOR-RELATION-INSTANCES */
Object update_relation_subject_class_for_relation_instances(relation,
	    new_subject_class,old_subject_class)
    Object relation, new_subject_class, old_subject_class;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(104,59);
    if ( !EQ(new_subject_class,Qitem) &&  !EQ(new_subject_class,
	    old_subject_class)) {
	if (SYMBOLP(new_subject_class)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = new_subject_class;
	    key_hash_value = SXHASH_SYMBOL_1(new_subject_class) & 
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
		gensymed_symbol = new_subject_class;
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
	if ( !temp_2) {
	    if (SYMBOLP(old_subject_class)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = old_subject_class;
		key_hash_value = SXHASH_SYMBOL_1(old_subject_class) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_13:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_14:
		if ( !TRUEP(marked))
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
		    gensymed_symbol = old_subject_class;
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
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
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
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_17:
		if ( !TRUEP(marked))
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_20:
		    if ( !TRUEP(marked))
			goto end_loop_19;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_23:
		    if ( !TRUEP(marked))
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(old_subject_class,
		    Class_description_gkbprop);
	    temp_2 =  !(gensymed_symbol ? 
		    TRUEP(memq_function(new_subject_class,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil));
	}
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return change_subject_or_object_class_for_relation_instances(relation,
		new_subject_class,old_subject_class,T);
    else
	return VALUES_1(Nil);
}

/* UPDATE-RELATION-OBJECT-CLASS-FOR-RELATION-INSTANCES */
Object update_relation_object_class_for_relation_instances(relation,
	    new_object_class,old_object_class)
    Object relation, new_object_class, old_object_class;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(104,60);
    if ( !EQ(new_object_class,Qitem) &&  !EQ(new_object_class,
	    old_object_class)) {
	if (SYMBOLP(new_object_class)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = new_object_class;
	    key_hash_value = SXHASH_SYMBOL_1(new_object_class) & 
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
		gensymed_symbol = new_object_class;
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
	if ( !temp_2) {
	    if (SYMBOLP(old_object_class)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = old_object_class;
		key_hash_value = SXHASH_SYMBOL_1(old_object_class) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_13:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_14:
		if ( !TRUEP(marked))
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
		    gensymed_symbol = old_object_class;
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
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
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
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_17:
		if ( !TRUEP(marked))
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
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
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_20:
		    if ( !TRUEP(marked))
			goto end_loop_19;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_23:
		    if ( !TRUEP(marked))
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(old_object_class,
		    Class_description_gkbprop);
	    temp_2 =  !(gensymed_symbol ? 
		    TRUEP(memq_function(new_object_class,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil));
	}
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return change_subject_or_object_class_for_relation_instances(relation,
		new_object_class,old_object_class,Nil);
    else
	return VALUES_1(Nil);
}

/* CHANGE-SUBJECT-OR-OBJECT-CLASS-FOR-RELATION-INSTANCES */
Object change_subject_or_object_class_for_relation_instances(relation,
	    new_class,iteration_class,new_class_for_subject_p_qm)
    Object relation, new_class, iteration_class, new_class_for_subject_p_qm;
{
    Object relation_is_symmetric_p_qm, relation_name, check_inverse_first_p_qm;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    Object relation_instances_qm, invalid_item_class_p_qm, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_binary_tree_form_;
    Object gensymed_symbol, temp_1, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance_form, relation_name_for_item, relation_for_item;
    Object ab_less_than_branch_qm_, sub_class_bit_vector, instance_items;
    Object related_inverse_item, error_string_qm;
    Object invalid_reverse_item_class_p_qm, remove_this_relation_instance_p_qm;
    Object other_class;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(104,61);
    relation_is_symmetric_p_qm = ISVREF(relation,(SI_Long)25L);
    relation_name = ISVREF(relation,(SI_Long)22L);
    check_inverse_first_p_qm = new_class_for_subject_p_qm;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,2);
      relation_instances_qm = Nil;
      invalid_item_class_p_qm = Nil;
      ab_loopvar_ = collect_subclasses(iteration_class);
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
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances_qm = ISVREF(item,(SI_Long)12L);
      invalid_item_class_p_qm = Nil;
      if (relation_instances_qm) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = relation_instances_qm;
	  ab_binary_tree_form_ = relation_instances_qm;
	  gensymed_symbol = CDR(relation_instances_qm);
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
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  relation_instance_form = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	    relation_name_for_item = Nil;
	    relation_for_item = Nil;
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
	  next_loop_2:
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
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    relation_instance_form = M_CDR(ab_entry_cons_);
	    relation_name_for_item = ISVREF(relation_instance_form,
		    (SI_Long)0L);
	    relation_for_item = ISVREF(relation_instance_form,(SI_Long)1L);
	    if (EQ(relation,relation_for_item) && ( 
		    !TRUEP(check_inverse_first_p_qm) || 
		    relation_is_symmetric_p_qm ? EQ(relation_name,
		    relation_name_for_item) :  !EQ(relation_name,
		    relation_name_for_item))) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(new_class,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			    (SI_Long)19L);
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
		if ( !temp)
		    invalid_item_class_p_qm = T;
		if (invalid_item_class_p_qm || relation_is_symmetric_p_qm) {
		    instance_items = ISVREF(relation_instance_form,
			    (SI_Long)2L);
		    scope_conses = Scope_conses;
		    ab_node_stack_ = Nil;
		    ab_current_node_ = Nil;
		    ab_skip_list_form_ = instance_items;
		    ab_binary_tree_form_ = instance_items;
		    gensymed_symbol = CDR(instance_items);
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
		    ab_next_node_ = Nil;
		    ab_tail_node_ = Nil;
		    ab_current_alist_ = Nil;
		    ab_entry_cons_ = Nil;
		    related_inverse_item = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			    0);
		      error_string_qm = Nil;
		      invalid_reverse_item_class_p_qm = Nil;
		      remove_this_relation_instance_p_qm = Nil;
		      other_class = new_class_for_subject_p_qm ? 
			      ISVREF(relation,(SI_Long)21L) : 
			      ISVREF(relation,(SI_Long)20L);
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
		    next_loop_4:
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
			      ab_entry_cons_ = 
				      scope_cons(ISVREF(ab_current_node_,
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
			    next_loop_5:
			      ab_less_than_branch_qm_ = 
				      ISVREF(ab_current_node_,(SI_Long)1L);
			      if ( !TRUEP(ab_less_than_branch_qm_))
				  goto end_loop_4;
			      ab_node_stack_ = scope_cons(ab_current_node_,
				      ab_node_stack_);
			      ab_current_node_ = ab_less_than_branch_qm_;
			      goto next_loop_5;
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
			      ab_next_node_ = ISVREF(ab_current_node_,
				      (SI_Long)2L);
			      ab_current_alist_ = ISVREF(ab_current_node_,
				      (SI_Long)3L);
			      ab_entry_cons_ = M_CAR(ab_current_alist_);
			      ab_current_alist_ = M_CDR(ab_current_alist_);
			  }
		      }
		      if ( !TRUEP(ab_current_node_))
			  goto end_loop_5;
		      related_inverse_item = M_CDR(ab_entry_cons_);
		      error_string_qm = Nil;
		      invalid_reverse_item_class_p_qm = Nil;
		      remove_this_relation_instance_p_qm = 
			      invalid_item_class_p_qm ? ( 
			      !TRUEP(relation_is_symmetric_p_qm) ? T : 
			      Nil) : Qnil;
		      if ( !TRUEP(remove_this_relation_instance_p_qm)) {
			  if (relation_is_symmetric_p_qm) {
			      gensymed_symbol = 
				      lookup_global_or_kb_specific_property_value(other_class,
				      Class_description_gkbprop);
			      if (gensymed_symbol) {
				  sub_class_bit_vector = 
					  ISVREF(ISVREF(related_inverse_item,
					  (SI_Long)1L),(SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(gensymed_symbol,
					  (SI_Long)18L));
				  sub_class_vector_index = 
					  superior_class_bit_number >>  -  
					  - (SI_Long)3L;
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
			      invalid_reverse_item_class_p_qm =  !temp ? T 
				      : Nil;
			      if (invalid_item_class_p_qm || 
				      invalid_reverse_item_class_p_qm) {
				  gensymed_symbol = 
					  lookup_global_or_kb_specific_property_value(other_class,
					  Class_description_gkbprop);
				  if (gensymed_symbol) {
				      sub_class_bit_vector = 
					      ISVREF(ISVREF(item,
					      (SI_Long)1L),(SI_Long)19L);
				      superior_class_bit_number = 
					      IFIX(ISVREF(gensymed_symbol,
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
					  temp = (SI_Long)0L < 
						  gensymed_symbol_1;
				      }
				      else
					  temp = TRUEP(Nil);
				  }
				  else
				      temp = TRUEP(Nil);
				  temp_1 =  !temp ? T : Nil;
				  if (temp_1);
				  else {
				      gensymed_symbol = 
					      lookup_global_or_kb_specific_property_value(new_class,
					      Class_description_gkbprop);
				      if (gensymed_symbol) {
					  sub_class_bit_vector = 
						  ISVREF(ISVREF(related_inverse_item,
						  (SI_Long)1L),(SI_Long)19L);
					  superior_class_bit_number = 
						  IFIX(ISVREF(gensymed_symbol,
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
				      else
					  temp = TRUEP(Nil);
				      temp_1 =  !temp ? T : Nil;
				  }
				  remove_this_relation_instance_p_qm = temp_1;
			      }
			      else
				  remove_this_relation_instance_p_qm = Nil;
			  }
		      }
		      if (remove_this_relation_instance_p_qm) {
			  error_string_qm =  
				  !TRUEP(check_inverse_first_p_qm) ? 
				  remove_from_relation(relation_name,
				  related_inverse_item,item,T,T,Nil) : 
				  remove_from_relation(relation_name,item,
				  related_inverse_item,T,T,Nil);
			  if (text_string_p(error_string_qm))
			      reclaim_text_string(error_string_qm);
		      }
		      goto next_loop_4;
		    end_loop_5:;
		    POP_SPECIAL();
		}
	    }
	    goto end_1;
	    goto next_loop_2;
	  end_loop_3:
	  end_1:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* UPDATE-TYPE-OF-RELATION-FOR-RELATION-INSTANCES */
Object update_type_of_relation_for_relation_instances(relation,
	    new_type_of_relation,old_type_of_relation)
    Object relation, new_type_of_relation, old_type_of_relation;
{
    Object relation_name, relation_is_symmetric_p_qm, subject_class;
    Object object_class, gensymed_symbol, unique_forward_qm, unique_reverse_qm;
    Object previously_unique_forward_qm, previously_unique_reverse_qm;
    Object test_forward_qm, test_reverse_qm, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, item, relation_instances_qm;
    Object item_can_be_subject_and_object_p_qm, frame, symbol;
    Object sub_class_bit_vector, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, temp_1, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance_form, relation_name_for_item, relation_for_item;
    Object tree, first_item_qm, ab_less_than_branch_qm_, ab_node_stack__1;
    Object ab_current_node__1, ab_skip_list_p__1, ab_next_node__1;
    Object ab_tail_node__1, ab_current_alist__1, ab_entry_cons__1, item_1;
    Object item2, item2_is_subject_of_symmetric_relation_p_qm, error_string_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp, disjoint_classes_p_qm;
    Declare_special(3);

    x_note_fn_call(104,62);
    relation_name = ISVREF(relation,(SI_Long)22L);
    relation_is_symmetric_p_qm = ISVREF(relation,(SI_Long)25L);
    subject_class = ISVREF(relation,(SI_Long)20L);
    object_class = ISVREF(relation,(SI_Long)21L);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(subject_class,
	    Class_description_gkbprop);
    temp = gensymed_symbol ? TRUEP(memq_function(object_class,
	    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
    if (temp);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(object_class,
		Class_description_gkbprop);
	temp = gensymed_symbol ? TRUEP(memq_function(subject_class,
		ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
    }
    disjoint_classes_p_qm =  !temp;
    unique_forward_qm = Nil;
    unique_reverse_qm = Nil;
    previously_unique_forward_qm = Nil;
    previously_unique_reverse_qm = Nil;
    if (EQ(old_type_of_relation,Qone_to_one)) {
	previously_unique_forward_qm = T;
	previously_unique_reverse_qm = T;
    }
    else if (EQ(old_type_of_relation,Qone_to_many))
	previously_unique_forward_qm = T;
    else if (EQ(old_type_of_relation,Qmany_to_one))
	previously_unique_reverse_qm = T;
    if (EQ(new_type_of_relation,Qone_to_one)) {
	unique_forward_qm = T;
	unique_reverse_qm = T;
    }
    else if (EQ(new_type_of_relation,Qone_to_many))
	unique_forward_qm = T;
    else if (EQ(new_type_of_relation,Qmany_to_one))
	unique_reverse_qm = T;
    if ( !( !TRUEP(previously_unique_forward_qm) && unique_forward_qm ||  
	    !TRUEP(previously_unique_reverse_qm) && unique_reverse_qm))
	return VALUES_1(Nil);
    test_forward_qm = unique_forward_qm;
    test_reverse_qm = unique_reverse_qm;
  next_loop:
    if ( !TRUEP(test_forward_qm) &&  !TRUEP(test_reverse_qm))
	goto end_loop;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,2);
      relation_instances_qm = Nil;
      item_can_be_subject_and_object_p_qm = Nil;
      ab_loopvar_ = collect_subclasses(test_forward_qm ? ISVREF(relation,
	      (SI_Long)21L) : ISVREF(relation,(SI_Long)20L));
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_2:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_1;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_1;
	  goto next_loop_2;
	end_loop_1:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_2;
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances_qm = ISVREF(item,(SI_Long)12L);
      frame = item;
      symbol = test_forward_qm ? subject_class : object_class;
      gensymed_symbol = lookup_global_or_kb_specific_property_value(symbol,
	      Class_description_gkbprop);
      if (gensymed_symbol) {
	  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
	      item_can_be_subject_and_object_p_qm = (SI_Long)0L < 
		      gensymed_symbol_1 ? T : Nil;
	  }
	  else
	      item_can_be_subject_and_object_p_qm = Nil;
      }
      else
	  item_can_be_subject_and_object_p_qm = Nil;
      if (relation_instances_qm) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = relation_instances_qm;
	  ab_binary_tree_form_ = relation_instances_qm;
	  gensymed_symbol = CDR(relation_instances_qm);
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
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  relation_instance_form = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	    relation_name_for_item = Nil;
	    relation_for_item = Nil;
	    tree = Nil;
	    first_item_qm = Nil;
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
	  next_loop_3:
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
		  next_loop_4:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_3;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_4;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_4;
	    relation_instance_form = M_CDR(ab_entry_cons_);
	    relation_name_for_item = ISVREF(relation_instance_form,
		    (SI_Long)0L);
	    relation_for_item = ISVREF(relation_instance_form,(SI_Long)1L);
	    tree = ISVREF(relation_instance_form,(SI_Long)2L);
	    scope_conses = Scope_conses;
	    ab_node_stack__1 = Nil;
	    ab_current_node__1 = Nil;
	    ab_skip_list_form_ = tree;
	    ab_binary_tree_form_ = tree;
	    gensymed_symbol = CDR(tree);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p__1 = Nil;
	    ab_next_node__1 = Nil;
	    ab_tail_node__1 = Nil;
	    ab_current_alist__1 = Nil;
	    ab_entry_cons__1 = Nil;
	    item_1 = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
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
	    next_loop_5:
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
		    next_loop_6:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node__1,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_5;
		      ab_node_stack__1 = scope_cons(ab_current_node__1,
			      ab_node_stack__1);
		      ab_current_node__1 = ab_less_than_branch_qm_;
		      goto next_loop_6;
		    end_loop_5:;
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
		  goto end_loop_6;
	      item_1 = M_CDR(ab_entry_cons__1);
	      if (item_1) {
		  first_item_qm = item_1;
		  goto end_1;
	      }
	      goto next_loop_5;
	    end_loop_6:
	      first_item_qm = Nil;
	      goto end_1;
	      first_item_qm = Qnil;
	    end_1:;
	    POP_SPECIAL();
	    if (EQ(relation,relation_for_item) && (test_forward_qm || 
		    relation_is_symmetric_p_qm ? EQ(relation_name,
		    relation_name_for_item) :  !EQ(relation_name,
		    relation_name_for_item)) && 
		    more_than_one_related_item_p(tree)) {
		scope_conses = Scope_conses;
		ab_node_stack__1 = Nil;
		ab_current_node__1 = Nil;
		ab_skip_list_form_ = tree;
		ab_binary_tree_form_ = tree;
		gensymed_symbol = CDR(tree);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p__1 = Nil;
		ab_next_node__1 = Nil;
		ab_tail_node__1 = Nil;
		ab_current_alist__1 = Nil;
		ab_entry_cons__1 = Nil;
		item2 = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		next_loop_7:
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
			next_loop_8:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node__1,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_7;
			  ab_node_stack__1 = scope_cons(ab_current_node__1,
				  ab_node_stack__1);
			  ab_current_node__1 = ab_less_than_branch_qm_;
			  goto next_loop_8;
			end_loop_7:;
		      }
		      else if (ab_node_stack__1) {
			  ab_next_node__1 = ab_node_stack__1;
			  ab_current_node__1 = M_CAR(ab_node_stack__1);
			  ab_node_stack__1 = M_CDR(ab_node_stack__1);
		      }
		      else
			  ab_current_node__1 = Nil;
		      if (ab_current_node__1) {
			  ab_next_node__1 = ISVREF(ab_current_node__1,
				  (SI_Long)2L);
			  ab_current_alist__1 = ISVREF(ab_current_node__1,
				  (SI_Long)3L);
			  ab_entry_cons__1 = M_CAR(ab_current_alist__1);
			  ab_current_alist__1 = M_CDR(ab_current_alist__1);
		      }
		  }
		  if ( !TRUEP(ab_current_node__1))
		      goto end_loop_8;
		  item2 = M_CDR(ab_entry_cons__1);
		  if ( !EQ(item2,first_item_qm)) {
		      if (relation_is_symmetric_p_qm) {
			  if (disjoint_classes_p_qm ||  
				  !TRUEP(item_can_be_subject_and_object_p_qm))
			      item2_is_subject_of_symmetric_relation_p_qm 
				      = test_forward_qm;
			  else {
			      gensymed_symbol = 
				      lookup_global_or_kb_specific_property_value(subject_class,
				      Class_description_gkbprop);
			      if (gensymed_symbol) {
				  sub_class_bit_vector = 
					  ISVREF(ISVREF(item2,(SI_Long)1L),
					  (SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(gensymed_symbol,
					  (SI_Long)18L));
				  sub_class_vector_index = 
					  superior_class_bit_number >>  -  
					  - (SI_Long)3L;
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
				      gensymed_symbol_2 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_3;
				      gensymed_symbol_1 = 
					      gensymed_symbol_1 & 
					      gensymed_symbol_2;
				      item2_is_subject_of_symmetric_relation_p_qm 
					      = (SI_Long)0L < 
					      gensymed_symbol_1 ? T : Nil;
				  }
				  else
				      item2_is_subject_of_symmetric_relation_p_qm 
					      = Nil;
			      }
			      else
				  item2_is_subject_of_symmetric_relation_p_qm 
					  = Nil;
			  }
		      }
		      else
			  item2_is_subject_of_symmetric_relation_p_qm = Nil;
		      error_string_qm = 
			      item2_is_subject_of_symmetric_relation_p_qm 
			      || test_forward_qm &&  
			      !TRUEP(relation_is_symmetric_p_qm) ? 
			      remove_from_relation(relation_name,item2,
			      item,T,T,Nil) : 
			      remove_from_relation(relation_name,item,
			      item2,T,T,Nil);
		      if (error_string_qm && text_string_p(error_string_qm))
			  reclaim_text_string(error_string_qm);
		  }
		  goto next_loop_7;
		end_loop_8:;
		POP_SPECIAL();
	    }
	    goto next_loop_3;
	  end_loop_4:;
	  POP_SPECIAL();
      }
      goto next_loop_1;
    end_loop_2:;
    POP_SPECIAL();
    if (test_forward_qm)
	test_forward_qm = Nil;
    else if (test_reverse_qm)
	test_reverse_qm = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* UPDATE-RELATION-IS-SYMMETRIC-FOR-RELATION-INSTANCES */
Object update_relation_is_symmetric_for_relation_instances(relation,
	    new_symmetric_flag,old_symmetric_flag)
    Object relation, new_symmetric_flag, old_symmetric_flag;
{
    Object relation_name, new_related_items_list_qm, relation_object_class;
    Object relation_subject_class, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object item, relation_instances_qm, copy_of_relation_instances_qm;
    Object relation_instance_form, ab_loop_list_, relation_name_for_item;
    Object relation_for_item, error_string_qm, relation_subject;
    Object relation_object, item2, ab_loop_list__1, gensymed_symbol;
    Object sub_class_bit_vector, relation_triplet_form, ab_loop_desetq_;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(104,63);
    if ( !EQ(old_symmetric_flag,new_symmetric_flag)) {
	relation_name = ISVREF(relation,(SI_Long)22L);
	new_related_items_list_qm = Nil;
	if (new_symmetric_flag &&  !TRUEP(ISVREF(relation,(SI_Long)23L)) 
		||  !TRUEP(new_symmetric_flag)) {
	    relation_object_class = ISVREF(relation,(SI_Long)21L);
	    relation_subject_class = ISVREF(relation,(SI_Long)20L);
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      relation_instances_qm = Nil;
	      copy_of_relation_instances_qm = Nil;
	      ab_loopvar_ = collect_subclasses(new_symmetric_flag ? 
		      relation_object_class : relation_subject_class);
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
	      item = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      relation_instances_qm = ISVREF(item,(SI_Long)12L);
	      copy_of_relation_instances_qm = 
		      copy_list_of_relation_instances(relation_instances_qm);
	      relation_instance_form = Nil;
	      ab_loop_list_ = copy_of_relation_instances_qm;
	      relation_name_for_item = Nil;
	      relation_for_item = Nil;
	      error_string_qm = Nil;
	      relation_subject = Nil;
	      relation_object = Nil;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      relation_instance_form = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      relation_name_for_item = M_CAR(relation_instance_form);
	      relation_for_item = M_CAR(M_CDR(relation_instance_form));
	      error_string_qm = Nil;
	      if (EQ(relation,relation_for_item) && 
		      EQ(relation_name_for_item,relation_name)) {
		  item2 = Nil;
		  ab_loop_list__1 = M_CDR(M_CDR(relation_instance_form));
		next_loop_3:
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop_3;
		  item2 = M_CAR(ab_loop_list__1);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  if (new_symmetric_flag) {
		      relation_subject = item2;
		      relation_object = item;
		  }
		  else {
		      gensymed_symbol = 
			      lookup_global_or_kb_specific_property_value(relation_object_class,
			      Class_description_gkbprop);
		      if (gensymed_symbol) {
			  sub_class_bit_vector = ISVREF(ISVREF(item2,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
				      superior_class_bit_number & (SI_Long)7L;
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
		      if (temp) {
			  relation_subject = item;
			  relation_object = item2;
		      }
		      else {
			  relation_subject = item2;
			  relation_object = item;
		      }
		  }
		  error_string_qm = new_symmetric_flag ? 
			  remove_from_relation(ISVREF(relation,
			  (SI_Long)26L),relation_object,relation_subject,T,
			  Nil,T) : remove_from_relation(relation_name,
			  relation_object,relation_subject,T,T,T);
		  if (error_string_qm && text_string_p(error_string_qm))
		      reclaim_text_string(error_string_qm);
		  error_string_qm = remove_from_relation(relation_name,
			  relation_subject,relation_object,T,Nil,T);
		  if (error_string_qm && text_string_p(error_string_qm))
		      reclaim_text_string(error_string_qm);
		  relation_triplet_form = 
			  gensym_cons_1(gensym_list_3(relation_name,
			  relation_subject,relation_object),Nil);
		  new_related_items_list_qm = new_related_items_list_qm ? 
			  nconc2(new_related_items_list_qm,
			  relation_triplet_form) : relation_triplet_form;
		  goto next_loop_3;
		end_loop_3:;
	      }
	      goto next_loop_2;
	    end_loop_2:;
	      goto next_loop;
	    end_loop_1:
	      reclaim_slot_value_tree_1(copy_of_relation_instances_qm);
	    POP_SPECIAL();
	    relation_name = Nil;
	    relation_subject = Nil;
	    relation_object = Nil;
	    ab_loop_list_ = new_related_items_list_qm;
	    error_string_qm = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_4;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    relation_name = CAR(ab_loop_desetq_);
	    temp_1 = CDR(ab_loop_desetq_);
	    relation_subject = CAR(temp_1);
	    temp_1 = CDR(ab_loop_desetq_);
	    temp_1 = CDR(temp_1);
	    relation_object = CAR(temp_1);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    error_string_qm = Nil;
	    error_string_qm = add_to_relation(relation_name,
		    relation_subject,relation_object,Nil,T,Nil);
	    if ( !TRUEP(error_string_qm)) {
		if (new_symmetric_flag) {
		    invoke_rules_for_relation_chaining(relation_name,
			    relation_object,relation_subject,T);
		    temp_1 = relation_object;
		    update_subscriptions_from_virtual_attribute_change(temp_1,
			    get_property_value_function(3,
			    get_symbol_properties_function(Qrelationships),
			    Qvirtual_attribute,Nil),Nil);
		    temp_1 = relation_subject;
		    update_subscriptions_from_virtual_attribute_change(temp_1,
			    get_property_value_function(3,
			    get_symbol_properties_function(Qrelationships),
			    Qvirtual_attribute,Nil),Nil);
		}
	    }
	    else if (text_string_p(error_string_qm))
		reclaim_text_string(error_string_qm);
	    goto next_loop_4;
	  end_loop_4:
	    if (new_related_items_list_qm)
		reclaim_gensym_tree_1(new_related_items_list_qm);
	    new_related_items_list_qm = Nil;
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* VALIDATE-ITEMS-IN-ALL-RELATIONS */
Object validate_items_in_all_relations(class_qm,old_class_qm)
    Object class_qm, old_class_qm;
{
    Object relation_needs_validation_qm, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, relation, subject_class, object_class;
    Object gensymed_symbol, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(104,64);
    relation_needs_validation_qm = Nil;
    if ( !TRUEP(class_qm) &&  !TRUEP(old_class_qm))
	relation_needs_validation_qm = T;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    relation = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      subject_class = Nil;
      object_class = Nil;
      ab_loopvar_ = collect_subclasses(Qrelation);
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
      relation = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      subject_class = ISVREF(relation,(SI_Long)20L);
      object_class = ISVREF(relation,(SI_Long)21L);
      if (relation_needs_validation_qm)
	  goto end_loop_1;
      if ( !EQ(subject_class,Qitem)) {
	  if (class_qm) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(subject_class,
		      Class_description_gkbprop);
	      temp = gensymed_symbol ? TRUEP(memq_function(class_qm,
		      ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else if (old_class_qm) {
	      temp = EQ(subject_class,old_class_qm);
	      if (temp);
	      else {
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(subject_class,
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
	  relation_needs_validation_qm = T;
      if ( !EQ(object_class,Qitem)) {
	  if (class_qm) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(object_class,
		      Class_description_gkbprop);
	      temp = gensymed_symbol ? TRUEP(memq_function(class_qm,
		      ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else if (old_class_qm) {
	      temp = EQ(object_class,old_class_qm);
	      if (temp);
	      else {
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(object_class,
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
	  relation_needs_validation_qm = T;
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    if (relation_needs_validation_qm) {
	temp_1 = class_qm;
	if (temp_1);
	else
	    temp_1 = Qitem;
	validate_relations_for_class(temp_1);
    }
    return VALUES_1(Nil);
}

static Object Qrelation_instances;  /* relation-instances */

/* VALIDATE-RELATIONS-FOR-CLASS */
Object validate_relations_for_class(class_1)
    Object class_1;
{
    Object class_description_qm, relation_instance_slot_description_qm;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    Object relation_instances_qm, invalid_relation_instance_p_qm;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp_1, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance_form, relation_instance_name, relation;
    Object relation_is_symmetric_p_qm, relation_instance_is_inverse_p_qm;
    Object error_string_qm, ab_less_than_branch_qm_, frame, symbol;
    Object sub_class_bit_vector, relation_name, ab_node_stack__1;
    Object ab_current_node__1, ab_skip_list_p__1, ab_next_node__1;
    Object ab_tail_node__1, ab_current_alist__1, ab_entry_cons__1;
    Object related_inverse_item;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(104,65);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    relation_instance_slot_description_qm = class_description_qm ? 
	    get_slot_description_of_class_description_function(Qrelation_instances,
	    class_description_qm,Nil) : Qnil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,2);
      relation_instances_qm = Nil;
      invalid_relation_instance_p_qm = Nil;
      ab_loopvar_ = collect_subclasses(class_1);
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
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances_qm = relation_instance_slot_description_qm ? 
	      get_slot_description_value(item,
	      relation_instance_slot_description_qm) : Qnil;
      invalid_relation_instance_p_qm = Nil;
      if (relation_instances_qm) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = relation_instances_qm;
	  ab_binary_tree_form_ = relation_instances_qm;
	  gensymed_symbol = CDR(relation_instances_qm);
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
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  relation_instance_form = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	    relation_instance_name = Nil;
	    relation = Nil;
	    relation_is_symmetric_p_qm = Nil;
	    relation_instance_is_inverse_p_qm = Nil;
	    error_string_qm = Nil;
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
	  next_loop_2:
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
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    relation_instance_form = M_CDR(ab_entry_cons_);
	    relation_instance_name = ISVREF(relation_instance_form,
		    (SI_Long)0L);
	    relation = ISVREF(relation_instance_form,(SI_Long)1L);
	    relation_is_symmetric_p_qm = ISVREF(relation,(SI_Long)25L);
	    if ( !EQ(relation_instance_name,ISVREF(relation,(SI_Long)22L)))
		relation_instance_is_inverse_p_qm = T;
	    if (relation_instance_is_inverse_p_qm) {
		frame = item;
		symbol = ISVREF(relation,(SI_Long)20L);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(symbol,
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
		if ( !temp)
		    invalid_relation_instance_p_qm = T;
	    }
	    else if (relation_is_symmetric_p_qm) {
		frame = item;
		symbol = ISVREF(relation,(SI_Long)21L);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(symbol,
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
		if (temp) {
		    frame = item;
		    symbol = ISVREF(relation,(SI_Long)20L);
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(symbol,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
		}
		else
		    temp = TRUEP(Nil);
		if ( !temp)
		    invalid_relation_instance_p_qm = T;
	    }
	    else {
		frame = item;
		symbol = ISVREF(relation,(SI_Long)21L);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(symbol,
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
		if ( !temp)
		    invalid_relation_instance_p_qm = T;
	    }
	    if (invalid_relation_instance_p_qm) {
		relation_name = ISVREF(relation,(SI_Long)22L);
		scope_conses = Scope_conses;
		ab_node_stack__1 = Nil;
		ab_current_node__1 = Nil;
		ab_skip_list_form_ = ISVREF(relation_instance_form,
			(SI_Long)2L);
		ab_binary_tree_form_ = ISVREF(relation_instance_form,
			(SI_Long)2L);
		temp_1 = ISVREF(relation_instance_form,(SI_Long)2L);
		gensymed_symbol = CDR(temp_1);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p__1 = Nil;
		ab_next_node__1 = Nil;
		ab_tail_node__1 = Nil;
		ab_current_alist__1 = Nil;
		ab_entry_cons__1 = Nil;
		related_inverse_item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		next_loop_4:
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
			next_loop_5:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node__1,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_4;
			  ab_node_stack__1 = scope_cons(ab_current_node__1,
				  ab_node_stack__1);
			  ab_current_node__1 = ab_less_than_branch_qm_;
			  goto next_loop_5;
			end_loop_4:;
		      }
		      else if (ab_node_stack__1) {
			  ab_next_node__1 = ab_node_stack__1;
			  ab_current_node__1 = M_CAR(ab_node_stack__1);
			  ab_node_stack__1 = M_CDR(ab_node_stack__1);
		      }
		      else
			  ab_current_node__1 = Nil;
		      if (ab_current_node__1) {
			  ab_next_node__1 = ISVREF(ab_current_node__1,
				  (SI_Long)2L);
			  ab_current_alist__1 = ISVREF(ab_current_node__1,
				  (SI_Long)3L);
			  ab_entry_cons__1 = M_CAR(ab_current_alist__1);
			  ab_current_alist__1 = M_CDR(ab_current_alist__1);
		      }
		  }
		  if ( !TRUEP(ab_current_node__1))
		      goto end_loop_5;
		  related_inverse_item = M_CDR(ab_entry_cons__1);
		  error_string_qm = relation_instance_is_inverse_p_qm ? 
			  remove_from_relation(relation_name,item,
			  related_inverse_item,T,T,Nil) : 
			  remove_from_relation(relation_name,
			  related_inverse_item,item,T,T,Nil);
		  if (text_string_p(error_string_qm))
		      reclaim_text_string(error_string_qm);
		  goto next_loop_4;
		end_loop_5:;
		POP_SPECIAL();
	    }
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* NOTE-CHANGE-TO-ALL-RELATED-ITEMS */
Object note_change_to_all_related_items(relation)
    Object relation;
{
    Object relation_name, inverse_name, secret_name, subject_class;
    Object object_class, check_one_class_only_qm, gensymed_symbol;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    Object relation_instances_qm, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, temp_1, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance_form, item_relation_name, item_relation;
    Object relation_found_qm, ab_less_than_branch_qm_;
    char temp;
    Declare_special(2);

    x_note_fn_call(104,66);
    relation_name = ISVREF(relation,(SI_Long)22L);
    inverse_name = ISVREF(relation,(SI_Long)23L);
    secret_name = ISVREF(relation,(SI_Long)26L);
    subject_class = ISVREF(relation,(SI_Long)20L);
    object_class = ISVREF(relation,(SI_Long)21L);
    if (EQ(subject_class,object_class))
	check_one_class_only_qm = subject_class;
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(subject_class,
		Class_description_gkbprop);
	if (gensymed_symbol ? TRUEP(memq_function(object_class,
		ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil))
	    check_one_class_only_qm = object_class;
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(object_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol ? TRUEP(memq_function(subject_class,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil))
		check_one_class_only_qm = subject_class;
	    else
		check_one_class_only_qm = Nil;
	}
    }
    if (check_one_class_only_qm) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	item = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	  relation_instances_qm = Nil;
	  ab_loopvar_ = collect_subclasses(check_one_class_only_qm);
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
	  item = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  relation_instances_qm = ISVREF(item,(SI_Long)12L);
	  if (relation_instances_qm) {
	      scope_conses = Scope_conses;
	      ab_node_stack_ = Nil;
	      ab_current_node_ = Nil;
	      ab_skip_list_form_ = relation_instances_qm;
	      ab_binary_tree_form_ = relation_instances_qm;
	      gensymed_symbol = CDR(relation_instances_qm);
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
	      ab_next_node_ = Nil;
	      ab_tail_node_ = Nil;
	      ab_current_alist_ = Nil;
	      ab_entry_cons_ = Nil;
	      relation_instance_form = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		item_relation_name = Nil;
		item_relation = Nil;
		relation_found_qm = Nil;
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
	      next_loop_2:
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
			ab_entry_cons_ = 
				scope_cons(ISVREF(ab_current_node_,
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
		      next_loop_3:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_2;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_3;
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
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
		    }
		}
		if ( !TRUEP(ab_current_node_))
		    goto end_loop_3;
		relation_instance_form = M_CDR(ab_entry_cons_);
		item_relation_name = ISVREF(relation_instance_form,
			(SI_Long)0L);
		item_relation = ISVREF(relation_instance_form,(SI_Long)1L);
		if (EQ(item_relation,relation)) {
		    temp_1 = EQ(item_relation_name,relation_name) ? T : Nil;
		    if (temp_1);
		    else
			temp_1 = EQ(item_relation_name,inverse_name) ? T : Nil;
		    if (temp_1);
		    else
			temp_1 = EQ(item_relation_name,secret_name) ? T : Nil;
		    relation_found_qm = temp_1;
		}
		else
		    relation_found_qm = Nil;
		if (relation_found_qm)
		    goto end_loop_3;
		goto next_loop_2;
	      end_loop_3:
		if (relation_found_qm)
		    note_change_or_deletion(item,T);
	      POP_SPECIAL();
	  }
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
    }
    else {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	item = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	  relation_instances_qm = Nil;
	  ab_loopvar_ = collect_subclasses(subject_class);
	next_loop_4:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_5:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_4;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_4;
	      goto next_loop_5;
	    end_loop_4:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_5;
	  item = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  relation_instances_qm = ISVREF(item,(SI_Long)12L);
	  if (relation_instances_qm) {
	      scope_conses = Scope_conses;
	      ab_node_stack_ = Nil;
	      ab_current_node_ = Nil;
	      ab_skip_list_form_ = relation_instances_qm;
	      ab_binary_tree_form_ = relation_instances_qm;
	      gensymed_symbol = CDR(relation_instances_qm);
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
	      ab_next_node_ = Nil;
	      ab_tail_node_ = Nil;
	      ab_current_alist_ = Nil;
	      ab_entry_cons_ = Nil;
	      relation_instance_form = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		item_relation_name = Nil;
		item_relation = Nil;
		relation_found_qm = Nil;
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
	      next_loop_6:
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
			ab_entry_cons_ = 
				scope_cons(ISVREF(ab_current_node_,
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
		      next_loop_7:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_6;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_7;
		      end_loop_6:;
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
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
		    }
		}
		if ( !TRUEP(ab_current_node_))
		    goto end_loop_7;
		relation_instance_form = M_CDR(ab_entry_cons_);
		item_relation_name = ISVREF(relation_instance_form,
			(SI_Long)0L);
		item_relation = ISVREF(relation_instance_form,(SI_Long)1L);
		if (EQ(item_relation,relation)) {
		    temp_1 = EQ(item_relation_name,inverse_name) ? T : Nil;
		    if (temp_1);
		    else
			temp_1 = EQ(item_relation_name,secret_name) ? T : Nil;
		    relation_found_qm = temp_1;
		}
		else
		    relation_found_qm = Nil;
		if (relation_found_qm)
		    goto end_loop_7;
		goto next_loop_6;
	      end_loop_7:
		if (relation_found_qm)
		    note_change_or_deletion(item,T);
	      POP_SPECIAL();
	  }
	  goto next_loop_4;
	end_loop_5:;
	POP_SPECIAL();
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	item = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	  relation_instances_qm = Nil;
	  ab_loopvar_ = collect_subclasses(object_class);
	next_loop_8:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_9:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_8;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_8;
	      goto next_loop_9;
	    end_loop_8:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_9;
	  item = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  relation_instances_qm = ISVREF(item,(SI_Long)12L);
	  if (relation_instances_qm) {
	      scope_conses = Scope_conses;
	      ab_node_stack_ = Nil;
	      ab_current_node_ = Nil;
	      ab_skip_list_form_ = relation_instances_qm;
	      ab_binary_tree_form_ = relation_instances_qm;
	      gensymed_symbol = CDR(relation_instances_qm);
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
	      ab_next_node_ = Nil;
	      ab_tail_node_ = Nil;
	      ab_current_alist_ = Nil;
	      ab_entry_cons_ = Nil;
	      relation_instance_form = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		item_relation_name = Nil;
		item_relation = Nil;
		relation_found_qm = Nil;
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
	      next_loop_10:
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
			ab_entry_cons_ = 
				scope_cons(ISVREF(ab_current_node_,
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
		      next_loop_11:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_10;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_11;
		      end_loop_10:;
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
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
		    }
		}
		if ( !TRUEP(ab_current_node_))
		    goto end_loop_11;
		relation_instance_form = M_CDR(ab_entry_cons_);
		item_relation_name = ISVREF(relation_instance_form,
			(SI_Long)0L);
		item_relation = ISVREF(relation_instance_form,(SI_Long)1L);
		relation_found_qm = EQ(item_relation,relation) ? 
			(EQ(item_relation_name,relation_name) ? T : Nil) : 
			Qnil;
		if (relation_found_qm)
		    goto end_loop_11;
		goto next_loop_10;
	      end_loop_11:
		if (relation_found_qm)
		    note_change_or_deletion(item,T);
	      POP_SPECIAL();
	  }
	  goto next_loop_8;
	end_loop_9:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Initializing_clear_text_p, Qinitializing_clear_text_p);

static Object Qrelation_is_permanent;  /* relation-is-permanent */

/* REMOVE-TRANSIENT-RELATION-INSTANCES */
Object remove_transient_relation_instances(item,called_from_system_reset_qm)
    Object item, called_from_system_reset_qm;
{
    Object relation_instances, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, gensymed_symbol, temp;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, relation_instance_form, given_name, other_name_qm;
    Object relation_or_reference, deleted_names, ab_less_than_branch_qm_, x2;
    Object ab_node_stack__1, ab_current_node__1, ab_skip_list_p__1;
    Object ab_next_node__1, ab_tail_node__1, ab_current_alist__1;
    Object ab_entry_cons__1, item2, object_instances_qm, object_instance_forms;
    Object ab_node_stack__2, ab_current_node__2, ab_skip_list_p__2;
    Object ab_next_node__2, ab_tail_node__2, ab_current_alist__2;
    Object ab_entry_cons__2, form, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object entry_hash, object_instance_form, ab_loop_list_, name, tree;
    Object found_item, item_1, slot_value_modify_macro_using_test_arg_1, car_1;
    Object cdr_1, key_result, x_element, ab_loop_list__1, ab_loop_it_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(104,67);
    if (Initializing_clear_text_p)
	return VALUES_1(Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(item);
    relation_instances = ISVREF(item,(SI_Long)12L);
    if (relation_instances) {
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
	relation_instance_form = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,2);
	  given_name = Nil;
	  other_name_qm = Nil;
	  relation_or_reference = Nil;
	  deleted_names = Nil;
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
	  relation_instance_form = M_CDR(ab_entry_cons_);
	  if ( !TRUEP(relation_instance_form));
	  else if (called_from_system_reset_qm && 
		  get_lookup_slot_value(ISVREF(relation_instance_form,
		  (SI_Long)1L),Qrelation_is_permanent));
	  else {
	      given_name = ISVREF(relation_instance_form,(SI_Long)0L);
	      relation_or_reference = ISVREF(relation_instance_form,
		      (SI_Long)1L);
	      if (SIMPLE_VECTOR_P(relation_or_reference) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(relation_or_reference)) 
		      > (SI_Long)2L &&  !EQ(ISVREF(relation_or_reference,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(relation_or_reference,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  if ( !EQ(given_name,ISVREF(relation_or_reference,
			  (SI_Long)22L)))
		      other_name_qm = ISVREF(relation_or_reference,
			      (SI_Long)22L);
		  else if (ISVREF(relation_or_reference,(SI_Long)25L))
		      other_name_qm = given_name;
		  else {
		      temp = ISVREF(relation_or_reference,(SI_Long)23L);
		      if (temp);
		      else
			  temp = ISVREF(relation_or_reference,(SI_Long)26L);
		      other_name_qm = temp;
		  }
	      }
	      else
		  other_name_qm = Nil;
	      scope_conses = Scope_conses;
	      ab_node_stack__1 = Nil;
	      ab_current_node__1 = Nil;
	      ab_skip_list_form_ = ISVREF(relation_instance_form,(SI_Long)2L);
	      ab_binary_tree_form_ = ISVREF(relation_instance_form,
		      (SI_Long)2L);
	      temp = ISVREF(relation_instance_form,(SI_Long)2L);
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
	      item2 = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      1);
		object_instances_qm = Nil;
		object_instance_forms = Nil;
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
			ab_less_than_branch_qm_ = 
				ISVREF(ab_current_node__1,(SI_Long)1L);
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
			ab_next_node__1 = ISVREF(ab_current_node__1,
				(SI_Long)2L);
			ab_current_alist__1 = ISVREF(ab_current_node__1,
				(SI_Long)3L);
			ab_entry_cons__1 = M_CAR(ab_current_alist__1);
			ab_current_alist__1 = M_CDR(ab_current_alist__1);
		    }
		}
		if ( !TRUEP(ab_current_node__1))
		    goto end_loop_3;
		item2 = M_CDR(ab_entry_cons__1);
		if (SIMPLE_VECTOR_P(item2) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item2)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item2,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(item2,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		object_instances_qm = temp_1 ? ISVREF(item2,(SI_Long)12L) :
			 Nil;
		if (object_instances_qm) {
		    if (SIMPLE_VECTOR_P(relation_or_reference) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(relation_or_reference)) 
			    > (SI_Long)2L &&  
			    !EQ(ISVREF(relation_or_reference,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(relation_or_reference,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if ( !temp_1) {
			scope_conses = Scope_conses;
			ab_node_stack__2 = Nil;
			ab_current_node__2 = Nil;
			ab_skip_list_form_ = object_instances_qm;
			ab_binary_tree_form_ = object_instances_qm;
			gensymed_symbol = CDR(object_instances_qm);
			if (CONSP(gensymed_symbol)) {
			    temp = M_CAR(gensymed_symbol);
			    temp_1 = SIMPLE_VECTOR_P(temp);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    temp = M_CDR(gensymed_symbol);
			    ab_skip_list_p__2 = SIMPLE_VECTOR_P(temp) ? T :
				     Nil;
			}
			else
			    ab_skip_list_p__2 = Nil;
			ab_next_node__2 = Nil;
			ab_tail_node__2 = Nil;
			ab_current_alist__2 = Nil;
			ab_entry_cons__2 = Nil;
			form = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
				0);
			  ab_loopvar_ = Nil;
			  ab_loopvar__1 = Nil;
			  ab_loopvar__2 = Nil;
			  if (ab_skip_list_p__2) {
			      ab_next_node__2 = 
				      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
				      (SI_Long)0L),(SI_Long)0L));
			      ab_tail_node__2 = 
				      M_CDR(M_CDR(ab_skip_list_form_));
			      if (EQ(ab_next_node__2,ab_tail_node__2))
				  ab_next_node__2 = Nil;
			  }
			  else
			      ab_next_node__2 = M_CDR(ab_binary_tree_form_);
			next_loop_4:
			  if (ab_current_alist__2) {
			      ab_entry_cons__2 = M_CAR(ab_current_alist__2);
			      ab_current_alist__2 = M_CDR(ab_current_alist__2);
			  }
			  else if (ab_skip_list_p__2) {
			      if (ab_next_node__2) {
				  ab_current_node__2 = ab_next_node__2;
				  ab_next_node__2 = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__2,
					  (SI_Long)0L),(SI_Long)0L));
				  if (EQ(ab_next_node__2,ab_tail_node__2))
				      ab_next_node__2 = Nil;
				  ab_entry_cons__2 = 
					  scope_cons(ISVREF(ab_current_node__2,
					  (SI_Long)2L),
					  ISVREF(ab_current_node__2,
					  (SI_Long)3L));
			      }
			      else
				  ab_current_node__2 = Nil;
			  }
			  else {
			      if (ab_next_node__2) {
				  ab_current_node__2 = ab_next_node__2;
				  ab_less_than_branch_qm_ = Nil;
				next_loop_5:
				  ab_less_than_branch_qm_ = 
					  ISVREF(ab_current_node__2,
					  (SI_Long)1L);
				  if ( !TRUEP(ab_less_than_branch_qm_))
				      goto end_loop_4;
				  ab_node_stack__2 = 
					  scope_cons(ab_current_node__2,
					  ab_node_stack__2);
				  ab_current_node__2 = ab_less_than_branch_qm_;
				  goto next_loop_5;
				end_loop_4:;
			      }
			      else if (ab_node_stack__2) {
				  ab_next_node__2 = ab_node_stack__2;
				  ab_current_node__2 = M_CAR(ab_node_stack__2);
				  ab_node_stack__2 = M_CDR(ab_node_stack__2);
			      }
			      else
				  ab_current_node__2 = Nil;
			      if (ab_current_node__2) {
				  ab_next_node__2 = 
					  ISVREF(ab_current_node__2,
					  (SI_Long)2L);
				  ab_current_alist__2 = 
					  ISVREF(ab_current_node__2,
					  (SI_Long)3L);
				  ab_entry_cons__2 = 
					  M_CAR(ab_current_alist__2);
				  ab_current_alist__2 = 
					  M_CDR(ab_current_alist__2);
			      }
			  }
			  if ( !TRUEP(ab_current_node__2))
			      goto end_loop_5;
			  form = M_CDR(ab_entry_cons__2);
			  ab_loopvar__2 = gensym_cons_1(form,Nil);
			  if (ab_loopvar__1)
			      M_CDR(ab_loopvar__1) = ab_loopvar__2;
			  else
			      ab_loopvar_ = ab_loopvar__2;
			  ab_loopvar__1 = ab_loopvar__2;
			  goto next_loop_4;
			end_loop_5:
			  object_instance_forms = ab_loopvar_;
			  goto end_1;
			  object_instance_forms = Qnil;
			end_1:;
			POP_SPECIAL();
		    }
		    else {
			skip_list = CDR(object_instances_qm);
			key_value = other_name_qm;
			key_hash_value = SXHASH_SYMBOL_1(other_name_qm) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)7L;
			ab_loop_bind_ = bottom_level;
		      next_loop_6:
			if (level < ab_loop_bind_)
			    goto end_loop_6;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_7:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
		      next_loop_8:
			if ( !TRUEP(marked))
			    goto end_loop_7;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
			goto next_loop_8;
		      end_loop_7:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_2;
			goto next_loop_7;
		      end_loop_8:
		      end_2:
			level = level - (SI_Long)1L;
			goto next_loop_6;
		      end_loop_6:;
			object_instance_forms = 
				gensym_cons_1(IFIX(ISVREF(curr,
				(SI_Long)1L)) == key_hash_value ? 
				(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
				ISVREF(curr,(SI_Long)3L) : Nil) : Nil,Nil);
		    }
		}
		else
		    object_instance_forms = Nil;
		if (SIMPLE_VECTOR_P(relation_or_reference) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(relation_or_reference)) 
			> (SI_Long)2L &&  !EQ(ISVREF(relation_or_reference,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(relation_or_reference,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if ( !temp_1 ?  !EQ(item2,item) :  !EQ(item2,item) ||  
			!EQ(other_name_qm,given_name)) {
		    if (SIMPLE_VECTOR_P(item2) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item2)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(item2,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(item2,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			if (Noting_changes_to_kb_p)
			    note_change_to_runtime_data_for_block_1(item2);
		    }
		    object_instance_form = Nil;
		    ab_loop_list_ = object_instance_forms;
		  next_loop_9:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_9;
		    object_instance_form = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (object_instance_form) {
			name = ISVREF(object_instance_form,(SI_Long)0L);
			tree = ISVREF(object_instance_form,(SI_Long)2L);
			skip_list = CDR(tree);
			key_value = item;
			key_hash_value = SXHASH_SYMBOL_1(item) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)7L;
			ab_loop_bind_ = bottom_level;
		      next_loop_10:
			if (level < ab_loop_bind_)
			    goto end_loop_10;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_11:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
		      next_loop_12:
			if ( !TRUEP(marked))
			    goto end_loop_11;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
			goto next_loop_12;
		      end_loop_11:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_3;
			goto next_loop_11;
		      end_loop_12:
		      end_3:
			level = level - (SI_Long)1L;
			goto next_loop_10;
		      end_loop_10:;
			found_item = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if ( !TRUEP(found_item));
			else {
			    gensymed_symbol = item;
			    set_skip_list_entry(tree,FIX((SI_Long)7L),Qeq,
				    Nil,T,gensymed_symbol,
				    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				    IFIX(Most_positive_fixnum)),Nil);
			    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
				    item,tree,FIX((SI_Long)7L),
				    FIX(SXHASH_SYMBOL_1(item) & 
				    IFIX(Most_positive_fixnum)));
			    temp_1 =  !TRUEP(tree);
			    if (temp_1);
			    else {
				gensymed_symbol = CDR(tree);
				if (CONSP(gensymed_symbol)) {
				    temp = M_CAR(gensymed_symbol);
				    temp_1 = SIMPLE_VECTOR_P(temp);
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1) {
				    temp = M_CDR(gensymed_symbol);
				    temp_1 = SIMPLE_VECTOR_P(temp);
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1) {
				    gensymed_symbol = M_CDR(tree);
				    temp = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol),
					    (SI_Long)0L),(SI_Long)0L));
				    temp_1 = EQ(temp,M_CDR(gensymed_symbol));
				}
				else
				    temp_1 =  !TRUEP(M_CDR(tree));
				if (temp_1);
				else {
				    scope_conses = Scope_conses;
				    ab_node_stack__2 = Nil;
				    ab_current_node__2 = Nil;
				    ab_skip_list_form_ = tree;
				    ab_binary_tree_form_ = tree;
				    gensymed_symbol = CDR(tree);
				    if (CONSP(gensymed_symbol)) {
					temp = M_CAR(gensymed_symbol);
					temp_1 = SIMPLE_VECTOR_P(temp);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1) {
					temp = M_CDR(gensymed_symbol);
					ab_skip_list_p__2 = 
						SIMPLE_VECTOR_P(temp) ? T :
						 Nil;
				    }
				    else
					ab_skip_list_p__2 = Nil;
				    ab_next_node__2 = Nil;
				    ab_tail_node__2 = Nil;
				    ab_current_alist__2 = Nil;
				    ab_entry_cons__2 = Nil;
				    item_1 = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
					    0);
				      if (ab_skip_list_p__2) {
					  ab_next_node__2 = 
						  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
						  (SI_Long)0L),(SI_Long)0L));
					  ab_tail_node__2 = 
						  M_CDR(M_CDR(ab_skip_list_form_));
					  if (EQ(ab_next_node__2,
						  ab_tail_node__2))
					      ab_next_node__2 = Nil;
				      }
				      else
					  ab_next_node__2 = 
						  M_CDR(ab_binary_tree_form_);
				    next_loop_13:
				      if (ab_current_alist__2) {
					  ab_entry_cons__2 = 
						  M_CAR(ab_current_alist__2);
					  ab_current_alist__2 = 
						  M_CDR(ab_current_alist__2);
				      }
				      else if (ab_skip_list_p__2) {
					  if (ab_next_node__2) {
					      ab_current_node__2 = 
						      ab_next_node__2;
					      ab_next_node__2 = 
						      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__2,
						      (SI_Long)0L),
						      (SI_Long)0L));
					      if (EQ(ab_next_node__2,
						      ab_tail_node__2))
						  ab_next_node__2 = Nil;
					      ab_entry_cons__2 = 
						      scope_cons(ISVREF(ab_current_node__2,
						      (SI_Long)2L),
						      ISVREF(ab_current_node__2,
						      (SI_Long)3L));
					  }
					  else
					      ab_current_node__2 = Nil;
				      }
				      else {
					  if (ab_next_node__2) {
					      ab_current_node__2 = 
						      ab_next_node__2;
					      ab_less_than_branch_qm_ = Nil;
					    next_loop_14:
					      ab_less_than_branch_qm_ = 
						      ISVREF(ab_current_node__2,
						      (SI_Long)1L);
					      if ( 
						      !TRUEP(ab_less_than_branch_qm_))
						  goto end_loop_13;
					      ab_node_stack__2 = 
						      scope_cons(ab_current_node__2,
						      ab_node_stack__2);
					      ab_current_node__2 = 
						      ab_less_than_branch_qm_;
					      goto next_loop_14;
					    end_loop_13:;
					  }
					  else if (ab_node_stack__2) {
					      ab_next_node__2 = 
						      ab_node_stack__2;
					      ab_current_node__2 = 
						      M_CAR(ab_node_stack__2);
					      ab_node_stack__2 = 
						      M_CDR(ab_node_stack__2);
					  }
					  else
					      ab_current_node__2 = Nil;
					  if (ab_current_node__2) {
					      ab_next_node__2 = 
						      ISVREF(ab_current_node__2,
						      (SI_Long)2L);
					      ab_current_alist__2 = 
						      ISVREF(ab_current_node__2,
						      (SI_Long)3L);
					      ab_entry_cons__2 = 
						      M_CAR(ab_current_alist__2);
					      ab_current_alist__2 = 
						      M_CDR(ab_current_alist__2);
					  }
				      }
				      if ( !TRUEP(ab_current_node__2))
					  goto end_loop_14;
				      item_1 = M_CDR(ab_entry_cons__2);
				      if (item_1) {
					  temp_1 = TRUEP(Nil);
					  goto end_4;
				      }
				      goto next_loop_13;
				    end_loop_14:
				      temp_1 = TRUEP(T);
				      goto end_4;
				      temp_1 = TRUEP(Qnil);
				    end_4:;
				    POP_SPECIAL();
				}
			    }
			    if (temp_1) {
				gensymed_symbol = name;
				temp = object_instances_qm;
				set_skip_list_entry(temp,FIX((SI_Long)7L),
					Qeq,Nil,T,gensymed_symbol,
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum)),Nil);
				if ( !EQ(item2,item)) {
				    temp = object_instances_qm;
				    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
					    name,temp,FIX((SI_Long)7L),
					    FIX(SXHASH_SYMBOL_1(name) & 
					    IFIX(Most_positive_fixnum)));
				}
				else {
				    slot_value_modify_macro_using_test_arg_1 
					    = name;
				    car_1 = 
					    slot_value_modify_macro_using_test_arg_1;
				    cdr_1 = deleted_names;
				    key_result = car_1;
				    x_element = Nil;
				    ab_loop_list__1 = cdr_1;
				    ab_loop_it_ = Nil;
				  next_loop_15:
				    if ( !TRUEP(ab_loop_list__1))
					goto end_loop_15;
				    x_element = M_CAR(ab_loop_list__1);
				    ab_loop_list__1 = M_CDR(ab_loop_list__1);
				    ab_loop_it_ = EQL(key_result,
					    x_element) ? T : Nil;
				    if (ab_loop_it_) {
					temp_1 = TRUEP(ab_loop_it_);
					goto end_5;
				    }
				    goto next_loop_15;
				  end_loop_15:
				    temp_1 = TRUEP(Qnil);
				  end_5:;
				    deleted_names = temp_1 ? cdr_1 : 
					    slot_value_cons_1(car_1,cdr_1);
				}
				reclaim_relation_instance(object_instance_form);
			    }
			}
		    }
		    goto next_loop_9;
		  end_loop_9:
		    reclaim_gensym_list_1(object_instance_forms);
		}
		goto next_loop_2;
	      end_loop_3:;
	      POP_SPECIAL();
	      gensymed_symbol = given_name;
	      set_skip_list_entry(relation_instances,FIX((SI_Long)7L),Qeq,
		      Nil,T,gensymed_symbol,
		      FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		      IFIX(Most_positive_fixnum)),Nil);
	      deleted_names = slot_value_cons_1(given_name,deleted_names);
	      reclaim_relation_instance(relation_instance_form);
	      relation_instance_form = Nil;
	  }
	  goto next_loop;
	end_loop_1:
	  if (deleted_names) {
	      name = Nil;
	      ab_loop_list_ = deleted_names;
	    next_loop_16:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_16;
	      name = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      temp = name;
	      delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
		      relation_instances,FIX((SI_Long)7L),
		      FIX(SXHASH_SYMBOL_1(name) & IFIX(Most_positive_fixnum)));
	      goto next_loop_16;
	    end_loop_16:;
	      reclaim_slot_value_list_1(deleted_names);
	  }
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* CLEANUP-FOR-RELATION */
Object cleanup_for_relation(relation)
    Object relation;
{
    Object frame, sub_vector_qm, method_function_qm, relation_name_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(104,68);
    frame = relation;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrelation)) {
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
    if ( !TRUEP(Resolving_definitional_name_conflicts_qm)) {
	relation_name_qm = ISVREF(relation,(SI_Long)22L);
	if (relation_name_qm)
	    return remove_all_relations_instances_for_relation(relation,
		    relation_name_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-ALL-RELATIONS-INSTANCES-FOR-RELATION */
Object remove_all_relations_instances_for_relation(relation,relation_name)
    Object relation, relation_name;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(104,69);
    if ( !TRUEP(Releasing_kb_qm)) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	item = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(ISVREF(relation,(SI_Long)21L));
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
	  item = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  remove_relations_instances_for_object_of_relation(relation,
		  relation_name,item);
	  goto next_loop;
	end_loop_1:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-RELATIONS-INSTANCES-FOR-OBJECT-OF-RELATION */
Object remove_relations_instances_for_object_of_relation(relation,
	    relation_name,item)
    Object relation, relation_name, item;
{
    Object relation_instances, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, relation_instance_form;
    Object gensymed_symbol, other_name, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_binary_tree_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, item2, subject_instances, subject_instance_form;
    Object ab_less_than_branch_qm_, tree, found_item, ab_node_stack__1;
    Object ab_current_node__1, ab_skip_list_p__1, ab_next_node__1;
    Object ab_tail_node__1, ab_current_alist__1, ab_entry_cons__1, item_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(104,70);
    relation_instances = ISVREF(item,(SI_Long)12L);
    if (relation_instances) {
	skip_list = CDR(relation_instances);
	key_value = relation_name;
	key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)7L;
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
	relation_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (relation_instance_form) {
	    if (EQ(ISVREF(relation_instance_form,(SI_Long)1L),relation)) {
		gensymed_symbol = relation_name;
		set_skip_list_entry(relation_instances,FIX((SI_Long)7L),
			Qeq,Nil,T,gensymed_symbol,
			FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum)),Nil);
		delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),relation_name,
			relation_instances,FIX((SI_Long)7L),
			FIX(SXHASH_SYMBOL_1(relation_name) & 
			IFIX(Most_positive_fixnum)));
		if (ISVREF(relation,(SI_Long)25L))
		    other_name = relation_name;
		else {
		    other_name = ISVREF(relation,(SI_Long)23L);
		    if (other_name);
		    else
			other_name = ISVREF(relation,(SI_Long)26L);
		}
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = ISVREF(relation_instance_form,
			(SI_Long)2L);
		ab_binary_tree_form_ = ISVREF(relation_instance_form,
			(SI_Long)2L);
		temp_1 = ISVREF(relation_instance_form,(SI_Long)2L);
		gensymed_symbol = CDR(temp_1);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		item2 = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			1);
		  subject_instances = Nil;
		  subject_instance_form = Nil;
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
		next_loop_3:
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
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
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
			next_loop_4:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_3;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_4;
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
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_4;
		  item2 = M_CDR(ab_entry_cons_);
		  subject_instances = ISVREF(item2,(SI_Long)12L);
		  skip_list = CDR(subject_instances);
		  key_value = other_name;
		  key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			  IFIX(Most_positive_fixnum);
		  bottom_level = (SI_Long)0L;
		  marked = Nil;
		  pred = M_CAR(skip_list);
		  curr = Nil;
		  succ = Nil;
		  level = (SI_Long)7L;
		  ab_loop_bind_ = bottom_level;
		next_loop_5:
		  if (level < ab_loop_bind_)
		      goto end_loop_5;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_6:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_7:
		  if ( !TRUEP(marked))
		      goto end_loop_6;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
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
		      goto end_2;
		  goto next_loop_6;
		end_loop_7:
		end_2:
		  level = level - (SI_Long)1L;
		  goto next_loop_5;
		end_loop_5:;
		  subject_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) 
			  == key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (EQ(ISVREF(subject_instance_form,(SI_Long)1L),
			  relation) && ( !EQ(item2,item) ||  
			  !EQ(other_name,relation_name))) {
		      tree = ISVREF(subject_instance_form,(SI_Long)2L);
		      skip_list = CDR(tree);
		      key_value = item;
		      key_hash_value = SXHASH_SYMBOL_1(item) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)7L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_8:
		      if (level < ab_loop_bind_)
			  goto end_loop_8;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_9:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_10:
		      if ( !TRUEP(marked))
			  goto end_loop_9;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_10;
		    end_loop_9:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_3;
		      goto next_loop_9;
		    end_loop_10:
		    end_3:
		      level = level - (SI_Long)1L;
		      goto next_loop_8;
		    end_loop_8:;
		      found_item = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if ( !TRUEP(found_item));
		      else {
			  gensymed_symbol = item;
			  set_skip_list_entry(tree,FIX((SI_Long)7L),Qeq,
				  Nil,T,gensymed_symbol,
				  FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				  IFIX(Most_positive_fixnum)),Nil);
			  delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),item,
				  tree,FIX((SI_Long)7L),
				  FIX(SXHASH_SYMBOL_1(item) & 
				  IFIX(Most_positive_fixnum)));
			  temp_2 =  !TRUEP(tree);
			  if (temp_2);
			  else {
			      gensymed_symbol = CDR(tree);
			      if (CONSP(gensymed_symbol)) {
				  temp_1 = M_CAR(gensymed_symbol);
				  temp_2 = SIMPLE_VECTOR_P(temp_1);
			      }
			      else
				  temp_2 = TRUEP(Nil);
			      if (temp_2) {
				  temp_1 = M_CDR(gensymed_symbol);
				  temp_2 = SIMPLE_VECTOR_P(temp_1);
			      }
			      else
				  temp_2 = TRUEP(Nil);
			      if (temp_2) {
				  gensymed_symbol = M_CDR(tree);
				  temp_1 = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol),
					  (SI_Long)0L),(SI_Long)0L));
				  temp_2 = EQ(temp_1,M_CDR(gensymed_symbol));
			      }
			      else
				  temp_2 =  !TRUEP(M_CDR(tree));
			      if (temp_2);
			      else {
				  scope_conses = Scope_conses;
				  ab_node_stack__1 = Nil;
				  ab_current_node__1 = Nil;
				  ab_skip_list_form_ = tree;
				  ab_binary_tree_form_ = tree;
				  gensymed_symbol = CDR(tree);
				  if (CONSP(gensymed_symbol)) {
				      temp_1 = M_CAR(gensymed_symbol);
				      temp_2 = SIMPLE_VECTOR_P(temp_1);
				  }
				  else
				      temp_2 = TRUEP(Nil);
				  if (temp_2) {
				      temp_1 = M_CDR(gensymed_symbol);
				      ab_skip_list_p__1 = 
					      SIMPLE_VECTOR_P(temp_1) ? T :
					       Nil;
				  }
				  else
				      ab_skip_list_p__1 = Nil;
				  ab_next_node__1 = Nil;
				  ab_tail_node__1 = Nil;
				  ab_current_alist__1 = Nil;
				  ab_entry_cons__1 = Nil;
				  item_1 = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
					  0);
				    if (ab_skip_list_p__1) {
					ab_next_node__1 = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
						(SI_Long)0L),(SI_Long)0L));
					ab_tail_node__1 = 
						M_CDR(M_CDR(ab_skip_list_form_));
					if (EQ(ab_next_node__1,
						ab_tail_node__1))
					    ab_next_node__1 = Nil;
				    }
				    else
					ab_next_node__1 = 
						M_CDR(ab_binary_tree_form_);
				  next_loop_11:
				    if (ab_current_alist__1) {
					ab_entry_cons__1 = 
						M_CAR(ab_current_alist__1);
					ab_current_alist__1 = 
						M_CDR(ab_current_alist__1);
				    }
				    else if (ab_skip_list_p__1) {
					if (ab_next_node__1) {
					    ab_current_node__1 = 
						    ab_next_node__1;
					    ab_next_node__1 = 
						    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__1,
						    (SI_Long)0L),(SI_Long)0L));
					    if (EQ(ab_next_node__1,
						    ab_tail_node__1))
						ab_next_node__1 = Nil;
					    ab_entry_cons__1 = 
						    scope_cons(ISVREF(ab_current_node__1,
						    (SI_Long)2L),
						    ISVREF(ab_current_node__1,
						    (SI_Long)3L));
					}
					else
					    ab_current_node__1 = Nil;
				    }
				    else {
					if (ab_next_node__1) {
					    ab_current_node__1 = 
						    ab_next_node__1;
					    ab_less_than_branch_qm_ = Nil;
					  next_loop_12:
					    ab_less_than_branch_qm_ = 
						    ISVREF(ab_current_node__1,
						    (SI_Long)1L);
					    if ( 
						    !TRUEP(ab_less_than_branch_qm_))
						goto end_loop_11;
					    ab_node_stack__1 = 
						    scope_cons(ab_current_node__1,
						    ab_node_stack__1);
					    ab_current_node__1 = 
						    ab_less_than_branch_qm_;
					    goto next_loop_12;
					  end_loop_11:;
					}
					else if (ab_node_stack__1) {
					    ab_next_node__1 = ab_node_stack__1;
					    ab_current_node__1 = 
						    M_CAR(ab_node_stack__1);
					    ab_node_stack__1 = 
						    M_CDR(ab_node_stack__1);
					}
					else
					    ab_current_node__1 = Nil;
					if (ab_current_node__1) {
					    ab_next_node__1 = 
						    ISVREF(ab_current_node__1,
						    (SI_Long)2L);
					    ab_current_alist__1 = 
						    ISVREF(ab_current_node__1,
						    (SI_Long)3L);
					    ab_entry_cons__1 = 
						    M_CAR(ab_current_alist__1);
					    ab_current_alist__1 = 
						    M_CDR(ab_current_alist__1);
					}
				    }
				    if ( !TRUEP(ab_current_node__1))
					goto end_loop_12;
				    item_1 = M_CDR(ab_entry_cons__1);
				    if (item_1) {
					temp_2 = TRUEP(Nil);
					goto end_4;
				    }
				    goto next_loop_11;
				  end_loop_12:
				    temp_2 = TRUEP(T);
				    goto end_4;
				    temp_2 = TRUEP(Qnil);
				  end_4:;
				  POP_SPECIAL();
			      }
			  }
			  if (temp_2) {
			      gensymed_symbol = other_name;
			      temp_1 = subject_instances;
			      set_skip_list_entry(temp_1,FIX((SI_Long)7L),
				      Qeq,Nil,T,gensymed_symbol,
				      FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
				      & IFIX(Most_positive_fixnum)),Nil);
			      temp_1 = subject_instances;
			      delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
				      other_name,temp_1,FIX((SI_Long)7L),
				      FIX(SXHASH_SYMBOL_1(other_name) & 
				      IFIX(Most_positive_fixnum)));
			      reclaim_relation_instance(subject_instance_form);
			  }
		      }
		  }
		  goto next_loop_3;
		end_loop_4:;
		POP_SPECIAL();
		return reclaim_relation_instance(relation_instance_form);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* BLOCK-RELATION-INSTANCES-VIOLATE-CLASS-TYPE-P */
Object block_relation_instances_violate_class_type_p(block)
    Object block;
{
    Object relation_instances, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, gensymed_symbol, temp;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, relation_instance, ab_loop_it_;
    Object ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(104,71);
    relation_instances = ISVREF(block,(SI_Long)12L);
    if (relation_instances) {
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
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loop_it_ = Nil;
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
	  ab_loop_it_ =  !TRUEP(valid_relation_instance_classes_p(block,
		  relation_instance)) ? T : Nil;
	  if (ab_loop_it_) {
	      result = VALUES_1(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop_1:
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qclass_1;            /* class-1 */

static Object Qclass_2;            /* class-2 */

/* VALID-RELATION-INSTANCE-CLASSES-P */
Object valid_relation_instance_classes_p(block,relation_instance)
    Object block, relation_instance;
{
    Object related_blocks, relation, relation_is_symmetric_qm;
    Object relation_instance_name, inverse_name, other_name, class_1;
    Object class_2_qm, gensymed_symbol, sub_class_bit_vector;
    Object class_of_block_qm, desired_other_block_class, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, temp_1, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_, other_block;
    Object ab_less_than_branch_qm_, relation_instances, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object relation_instance_form, the_block, blocks;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(104,72);
    related_blocks = ISVREF(relation_instance,(SI_Long)2L);
    relation = ISVREF(relation_instance,(SI_Long)1L);
    relation_is_symmetric_qm = ISVREF(relation,(SI_Long)25L);
    relation_instance_name = ISVREF(relation_instance,(SI_Long)0L);
    if (ISVREF(relation,(SI_Long)25L))
	inverse_name = ISVREF(relation,(SI_Long)22L);
    else {
	inverse_name = ISVREF(relation,(SI_Long)23L);
	if (inverse_name);
	else
	    inverse_name = ISVREF(relation,(SI_Long)26L);
    }
    other_name = EQ(relation_instance_name,inverse_name) ? ISVREF(relation,
	    (SI_Long)22L) : inverse_name;
    result = classes_for_block_containing_relation(relation_instance);
    MVS_2(result,class_1,class_2_qm);
    if (relation_is_symmetric_qm) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    class_of_block_qm = Qclass_1;
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_2_qm,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
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
	    if (temp)
		class_of_block_qm = Qclass_2;
	    else
		class_of_block_qm = Nil;
	}
	if (class_of_block_qm) {
	    desired_other_block_class = EQ(class_of_block_qm,Qclass_1) ? 
		    class_2_qm : class_1;
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = related_blocks;
	    ab_binary_tree_form_ = related_blocks;
	    gensymed_symbol = CDR(related_blocks);
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
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    other_block = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
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
	      other_block = M_CDR(ab_entry_cons_);
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(desired_other_block_class,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(other_block,
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
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  relation_instances = ISVREF(other_block,(SI_Long)12L);
		  if (relation_instances) {
		      skip_list = CDR(relation_instances);
		      key_value = relation_instance_name;
		      key_hash_value = 
			      SXHASH_SYMBOL_1(relation_instance_name) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)7L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_2:
		      if (level < ab_loop_bind_)
			  goto end_loop_2;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_3:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_4:
		      if ( !TRUEP(marked))
			  goto end_loop_3;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_4;
		    end_loop_3:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		      relation_instance_form = IFIX(ISVREF(curr,
			      (SI_Long)1L)) == key_hash_value ? 
			      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			      ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		      if (relation_instance_form) {
			  the_block = block;
			  blocks = ISVREF(relation_instance_form,(SI_Long)2L);
			  skip_list = CDR(blocks);
			  key_value = the_block;
			  key_hash_value = SXHASH_SYMBOL_1(the_block) & 
				  IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)7L;
			  ab_loop_bind_ = bottom_level;
			next_loop_5:
			  if (level < ab_loop_bind_)
			      goto end_loop_5;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_6:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_7:
			  if ( !TRUEP(marked))
			      goto end_loop_6;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
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
			      goto end_2;
			  goto next_loop_6;
			end_loop_7:
			end_2:
			  level = level - (SI_Long)1L;
			  goto next_loop_5;
			end_loop_5:;
			  temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				  key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? 
				  TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				  TRUEP(Nil)) : TRUEP(Nil);
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if ( !temp) {
		  result = VALUES_1(Nil);
		  goto end_3;
	      }
	      goto next_loop;
	    end_loop_1:
	      result = VALUES_1(T);
	      goto end_3;
	      result = VALUES_1(Qnil);
	    end_3:;
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp =  !TRUEP(class_2_qm);
	    if (temp);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_2_qm,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(block,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    result = classes_for_other_blocks_in_relation(relation_instance);
	    MVS_2(result,class_1,class_2_qm);
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = related_blocks;
	    ab_binary_tree_form_ = related_blocks;
	    gensymed_symbol = CDR(related_blocks);
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
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    other_block = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
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
	    next_loop_8:
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
		    next_loop_9:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_8;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_9;
		    end_loop_8:;
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
		  goto end_loop_9;
	      other_block = M_CDR(ab_entry_cons_);
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(class_1,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(other_block,
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
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  temp =  !TRUEP(class_2_qm);
		  if (temp);
		  else {
		      gensymed_symbol = 
			      lookup_global_or_kb_specific_property_value(class_2_qm,
			      Class_description_gkbprop);
		      if (gensymed_symbol) {
			  sub_class_bit_vector = ISVREF(ISVREF(other_block,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
				      superior_class_bit_number & (SI_Long)7L;
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
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  relation_instances = ISVREF(other_block,(SI_Long)12L);
		  if (relation_instances) {
		      skip_list = CDR(relation_instances);
		      key_value = other_name;
		      key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)7L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_10:
		      if (level < ab_loop_bind_)
			  goto end_loop_10;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_11:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_12:
		      if ( !TRUEP(marked))
			  goto end_loop_11;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_12;
		    end_loop_11:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		      relation_instance_form = IFIX(ISVREF(curr,
			      (SI_Long)1L)) == key_hash_value ? 
			      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			      ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		      if (relation_instance_form) {
			  the_block = block;
			  blocks = ISVREF(relation_instance_form,(SI_Long)2L);
			  skip_list = CDR(blocks);
			  key_value = the_block;
			  key_hash_value = SXHASH_SYMBOL_1(the_block) & 
				  IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)7L;
			  ab_loop_bind_ = bottom_level;
			next_loop_13:
			  if (level < ab_loop_bind_)
			      goto end_loop_13;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_14:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_15:
			  if ( !TRUEP(marked))
			      goto end_loop_14;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			  goto next_loop_15;
			end_loop_14:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_5;
			  goto next_loop_14;
			end_loop_15:
			end_5:
			  level = level - (SI_Long)1L;
			  goto next_loop_13;
			end_loop_13:;
			  temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				  key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? 
				  TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				  TRUEP(Nil)) : TRUEP(Nil);
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if ( !temp) {
		  result = VALUES_1(Nil);
		  goto end_6;
	      }
	      goto next_loop_8;
	    end_loop_9:
	      result = VALUES_1(T);
	      goto end_6;
	      result = VALUES_1(Qnil);
	    end_6:;
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
}

/* CLASSES-FOR-BLOCK-CONTAINING-RELATION */
Object classes_for_block_containing_relation(relation_instance)
    Object relation_instance;
{
    Object relation, relation_instance_name, temp, temp_1;

    x_note_fn_call(104,73);
    relation = ISVREF(relation_instance,(SI_Long)1L);
    relation_instance_name = ISVREF(relation_instance,(SI_Long)0L);
    if ( !EQ(relation_instance_name,ISVREF(relation,(SI_Long)22L)))
	return VALUES_1(ISVREF(relation,(SI_Long)20L));
    else if (ISVREF(relation,(SI_Long)25L)) {
	temp = ISVREF(relation,(SI_Long)20L);
	temp_1 = ISVREF(relation,(SI_Long)21L);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(ISVREF(relation,(SI_Long)21L));
}

/* CLASSES-FOR-OTHER-BLOCKS-IN-RELATION */
Object classes_for_other_blocks_in_relation(relation_instance)
    Object relation_instance;
{
    Object relation, relation_instance_name, temp, temp_1;

    x_note_fn_call(104,74);
    relation = ISVREF(relation_instance,(SI_Long)1L);
    relation_instance_name = ISVREF(relation_instance,(SI_Long)0L);
    if ( !EQ(relation_instance_name,ISVREF(relation,(SI_Long)22L)))
	return VALUES_1(ISVREF(relation,(SI_Long)21L));
    else if (ISVREF(relation,(SI_Long)25L)) {
	temp = ISVREF(relation,(SI_Long)21L);
	temp_1 = ISVREF(relation,(SI_Long)20L);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(ISVREF(relation,(SI_Long)20L));
}

/* REMOVE-INVALID-RELATION-INSTANCES */
Object remove_invalid_relation_instances(item)
    Object item;
{
    Object copy_of_relation_instances_qm, invalid_item_p_qm;
    Object relation_instance_form, ab_loop_list_, relation_instance_name;
    Object inverse_name, other_name, relation, relation_is_symmetric_p_qm;
    Object relation_instance_is_inverse_p_qm, error_string_qm, temp, frame;
    Object symbol, gensymed_symbol, sub_class_bit_vector;
    Object invalid_inverse_item_p_qm, related_inverse_item, ab_loop_list__1;
    Object relation_instances, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, the_block, blocks, sublist;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(104,75);
    copy_of_relation_instances_qm = 
	    copy_list_of_relation_instances(ISVREF(item,(SI_Long)12L));
    invalid_item_p_qm = Nil;
    if (copy_of_relation_instances_qm) {
	relation_instance_form = Nil;
	ab_loop_list_ = copy_of_relation_instances_qm;
	relation_instance_name = Nil;
	inverse_name = Nil;
	other_name = Nil;
	relation = Nil;
	relation_is_symmetric_p_qm = Nil;
	relation_instance_is_inverse_p_qm = Nil;
	error_string_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	relation_instance_form = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	relation_instance_name = M_CAR(relation_instance_form);
	relation = M_CAR(M_CDR(relation_instance_form));
	relation_is_symmetric_p_qm = ISVREF(relation,(SI_Long)25L);
	if (ISVREF(relation,(SI_Long)25L))
	    inverse_name = ISVREF(relation,(SI_Long)22L);
	else {
	    temp = ISVREF(relation,(SI_Long)23L);
	    if (temp);
	    else
		temp = ISVREF(relation,(SI_Long)26L);
	    inverse_name = temp;
	}
	other_name = EQ(relation_instance_name,inverse_name) ? 
		ISVREF(relation,(SI_Long)22L) : inverse_name;
	if ( !EQ(relation_instance_name,ISVREF(relation,(SI_Long)22L)))
	    relation_instance_is_inverse_p_qm = T;
	if (relation_instance_is_inverse_p_qm) {
	    frame = item;
	    symbol = ISVREF(relation,(SI_Long)20L);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1)
		invalid_item_p_qm = T;
	}
	else if (relation_is_symmetric_p_qm) {
	    frame = item;
	    symbol = ISVREF(relation,(SI_Long)21L);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		frame = item;
		symbol = ISVREF(relation,(SI_Long)20L);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(symbol,
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
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1)
		invalid_item_p_qm = T;
	}
	else {
	    frame = item;
	    symbol = ISVREF(relation,(SI_Long)21L);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1)
		invalid_item_p_qm = T;
	}
	invalid_inverse_item_p_qm = Nil;
	related_inverse_item = Nil;
	ab_loop_list__1 = M_CDR(M_CDR(relation_instance_form));
      next_loop_1:
	invalid_inverse_item_p_qm = Nil;
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	related_inverse_item = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(invalid_item_p_qm)) {
	    relation_instances = ISVREF(related_inverse_item,(SI_Long)12L);
	    if (relation_instances) {
		skip_list = CDR(relation_instances);
		key_value = other_name;
		key_hash_value = SXHASH_SYMBOL_1(other_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
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
		relation_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (relation_instance_form) {
		    the_block = item;
		    blocks = ISVREF(relation_instance_form,(SI_Long)2L);
		    skip_list = CDR(blocks);
		    key_value = the_block;
		    key_hash_value = SXHASH_SYMBOL_1(the_block) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)7L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_5:
		    if (level < ab_loop_bind_)
			goto end_loop_5;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_6:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_7:
		    if ( !TRUEP(marked))
			goto end_loop_6;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
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
			goto end_2;
		    goto next_loop_6;
		  end_loop_7:
		  end_2:
		    level = level - (SI_Long)1L;
		    goto next_loop_5;
		  end_loop_5:;
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
	    invalid_inverse_item_p_qm =  !temp_1 ? T : Nil;
	    if ( !TRUEP(invalid_inverse_item_p_qm)) {
		if (relation_instance_is_inverse_p_qm) {
		    frame = related_inverse_item;
		    symbol = ISVREF(relation,(SI_Long)21L);
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(symbol,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			    temp_1 = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if ( !temp_1)
			invalid_inverse_item_p_qm = T;
		}
		else if (relation_is_symmetric_p_qm) {
		    frame = related_inverse_item;
		    symbol = ISVREF(relation,(SI_Long)21L);
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(symbol,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			    temp_1 = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			frame = related_inverse_item;
			symbol = ISVREF(relation,(SI_Long)20L);
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(symbol,
				Class_description_gkbprop);
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(ISVREF(frame,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
				temp_1 = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if ( !temp_1)
			invalid_inverse_item_p_qm = T;
		}
		else {
		    frame = related_inverse_item;
		    symbol = ISVREF(relation,(SI_Long)20L);
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(symbol,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			    temp_1 = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if ( !temp_1)
			invalid_inverse_item_p_qm = T;
		}
	    }
	}
	if (invalid_item_p_qm || invalid_inverse_item_p_qm) {
	    if (relation_instance_is_inverse_p_qm) {
		remove_from_relation(other_name,item,related_inverse_item,
			T,Nil,T);
		error_string_qm = 
			remove_from_relation(relation_instance_name,
			related_inverse_item,item,T,Nil,T);
	    }
	    else {
		remove_from_relation(relation_instance_name,
			related_inverse_item,item,T,Nil,T);
		error_string_qm = remove_from_relation(other_name,item,
			related_inverse_item,T,Nil,T);
	    }
	}
	if (text_string_p(error_string_qm))
	    reclaim_text_string(error_string_qm);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    sublist = Nil;
    ab_loop_list_ = copy_of_relation_instances_qm;
  next_loop_8:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_8;
    sublist = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_list_1(sublist);
    goto next_loop_8;
  end_loop_8:;
    return reclaim_gensym_list_1(copy_of_relation_instances_qm);
}

void relations_INIT()
{
    Object write_duplicate_uuids_note_1, temp;
    Object reclaim_structure_for_relation_instance_1, temp_1, temp_2;
    Object oneness_type_evaluation_setter_1, oneness_type_evaluation_getter_1;
    Object relation_yes_or_no_qm_evaluation_setter_1;
    Object relation_yes_or_no_qm_evaluation_getter_1;
    Object AB_package, Qclasses_which_define, Qcleanup, Qcleanup_for_relation;
    Object Qslot_putter, Qput_relation_is_symmetric, Qput_type_of_relation;
    Object Qput_class_of_object, Qput_class_of_subject, Qslot_value_reclaimer;
    Object Qreclaim_inverse_of_relation_value, Qput_inverse_of_relation;
    Object Qreclaim_relation_name_value, Qput_relation_name;
    Object Qslot_value_writer, Qwrite_relation_summary_from_slot;
    Object Qrelation_yes_or_no_qm, list_constant_24, Qnamed;
    Object Qtype_specification_simple_expansion, Qoneness_type;
    Object list_constant_25, Qmany_to_many;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_oneness_type_for_slot;
    Object Qwrite_oneness_type_from_slot, string_constant_46;
    Object Qrelation_name_qm, Qcompile_relation_name_qm_for_slot;
    Object list_constant_6, Qwrite_symbol_from_slot;
    Object Qwrite_relation_yes_or_no_qm_from_slot, Qget_items_in_this_relation;
    Object Qinitial_items_in_this_relation, list_constant_20, list_constant_23;
    Object list_constant_22, list_constant_21, list_constant_16, Qab_or;
    Object list_constant_9, Qab_class, Qvirtual_attributes_local_to_class;
    Object Qset_relationships, Qget_relationships, Qinitial_relationships;
    Object list_constant_19, list_constant_18, Kwithin_putter, Kevent_updates;
    Object list_constant_17, list_constant_15, list_constant_14;
    Object list_constant_13, Qab_structure, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_8, Qno_item;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qsecond_class, Qfirst_class;
    Object Qabsent_slot_putter, Qput_relation_is_symetric_where_slot_is_absent;
    Object Qrelation_is_symetric, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object string_constant_26, string_constant_25, string_constant_37;
    Object list_constant_7, Qcreate_icon_description, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, Qentity, Qrelation_instance;
    Object Qreclaim_structure, Qoutstanding_relation_instance_count;
    Object Qrelation_instance_structure_memory_usage, Qutilities2;
    Object string_constant_19, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_relation_instance_g2_struct;
    Object string_constant_18, Qframe_note_writer_1;

    x_note_fn_call(104,76);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qduplicate_uuids = STATIC_SYMBOL("DUPLICATE-UUIDS",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)57344L);
    write_duplicate_uuids_note_1 = 
	    STATIC_FUNCTION(write_duplicate_uuids_note,NIL,FALSE,2,2);
    mutate_global_property(Qduplicate_uuids,write_duplicate_uuids_note_1,
	    Qframe_note_writer_1);
    Qremote_item = STATIC_SYMBOL("REMOTE-ITEM",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    if (The_type_description_of_relation_instance == UNBOUND)
	The_type_description_of_relation_instance = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83mDy1m83mDy8k1l8k0000001o1m83*gy9k1m83=ey3-Wy1n8y83-5Ny1n83-BYy83-BZy83-BXy1m83My83-Awyknk0k0");
    temp = The_type_description_of_relation_instance;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_relation_instance = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_18));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_relation_instance_g2_struct = 
	    STATIC_SYMBOL("RELATION-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_relation_instance_g2_struct,
	    The_type_description_of_relation_instance,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qrelation_instance = STATIC_SYMBOL("RELATION-INSTANCE",AB_package);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qrelation_instance,
	    The_type_description_of_relation_instance,
	    Qtype_description_of_type);
    Qoutstanding_relation_instance_count = 
	    STATIC_SYMBOL("OUTSTANDING-RELATION-INSTANCE-COUNT",AB_package);
    Qrelation_instance_structure_memory_usage = 
	    STATIC_SYMBOL("RELATION-INSTANCE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_19 = STATIC_STRING("1q83mDy8s83-m*y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_relation_instance_count);
    push_optimized_constant(Qrelation_instance_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_relation_instances = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RELATION-INSTANCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_relation_instances,
	    Chain_of_available_relation_instances);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_relation_instances,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qrelation_instance_count = STATIC_SYMBOL("RELATION-INSTANCE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrelation_instance_count,
	    Relation_instance_count);
    record_system_variable(Qrelation_instance_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_relation_instances_vector == UNBOUND)
	Chain_of_available_relation_instances_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qrelation_instance_structure_memory_usage,
	    STATIC_FUNCTION(relation_instance_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_relation_instance_count,
	    STATIC_FUNCTION(outstanding_relation_instance_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_relation_instance_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_relation_instance,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qrelation_instance,
	    reclaim_structure_for_relation_instance_1);
    Qrelated_item_tree = STATIC_SYMBOL("RELATED-ITEM-TREE",AB_package);
    Qrelation_instance_tree = STATIC_SYMBOL("RELATION-INSTANCE-TREE",
	    AB_package);
    Qold_relation_instances = STATIC_SYMBOL("OLD-RELATION-INSTANCES",
	    AB_package);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qrelation,list_constant_7);
    string_constant_20 = STATIC_STRING("1l1m8v837Ky");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_21 = 
	    STATIC_STRING("1x4z8r83--y83--y837Ky837Ky00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_22 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_23 = 
	    STATIC_STRING("0004z8r83-0y83-0y837Ky837Ky00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_24 = 
	    STATIC_STRING("ion is available at this time)000004z8r83-Fy83-Fy837Ky837Ky00001r1l8l1l83Hy1m8p01l83Ny1m83Dy73-by3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Yy");
    string_constant_25 = 
	    STATIC_STRING("3-hy3-ky3Sy3-Vy3-hy3-gy3-oy3-Xy3-gy3-by3-Xy3-gy3-Vy3-Xy3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-Yy3-Ty3-ey3-ly3-Xy3ey3Sy");
    string_constant_26 = 
	    STATIC_STRING("3-ky3-Xy3-ey3-Ty3-my3-by3-hy3-gy3fy3-gy3-Ty3-fy3-Xy3Sy3-by3-ly3Sy3-ly3-Xy3-my3-my3-Ty3-Uy3-ey3-Xy3Sy3-wyut3Sy3-Ty3-gy3-Wy3Sy3-gy");
    string_constant_27 = 
	    STATIC_STRING("3-Ty3-fy3-Xy3Sy3-Ty3-ny3-my3-hy3-fy3-Ty3-my3-by3-Vy3-Ty3-ey3-ey3-ry3Sy3-Yy3-by3-ey3-ey3-Xy3-Wy3Sy3-by3-gy3gy1l83Uy1l83*-y000004z");
    string_constant_28 = 
	    STATIC_STRING("8r83BDy83BDy837Ky837Ky083Ry001o1l8l1l8z1l8o1m8p83-Gy000004z8r83BAy83BAy837Ky837Ky083Ry001o1l8l1l8z1l8o1m8p83-Gy000004z8r834Uy834");
    string_constant_29 = 
	    STATIC_STRING("Uy837Ky837Ky00001p1l8l1l8o1m8p83Ehy1l83Uy1m83Dy53-2yType = (or none symbol). writable = true, List of names not permitted.000004");
    string_constant_30 = 
	    STATIC_STRING("z8r83Smy83Smy837Ky837Ky00001p1l8l1l8o1m8p83Ehy1l83Uy1m83Dy53aytype = (or symbol none), writable = true000004z8r83cuy83cuy837Ky83");
    string_constant_31 = 
	    STATIC_STRING("7Ky083Day001o1l8l1l8o1m8p83EDy1m83Dy53-*ytype = (member one-to-one, one-to-many, many-to-one, many-to-many)000004z8r83Yny83Yny83");
    string_constant_32 = 
	    STATIC_STRING("7Ky837Ky00001o1l8l1l8o1m8p83Eiy1m83Dy53bywritable = true, type = (or none boolean)000004z8r83Egy83Egy837Ky837Ky00001p1l8l1l8z1m8");
    string_constant_33 = 
	    STATIC_STRING("p83Ky1l8z1m83Dy53Rywritable = true, type = boolean000004z8r83Yoy83Yoy837Ky837Ky00001q1l8l1l83Ey1l83Fy1l83-3y1m8p83Yoy1m83Dy53Ryw");
    string_constant_34 = 
	    STATIC_STRING("ritable = false, type = string000004z8r83Zny83Zny837Ky837Ky00001m1l8l1l8o000004z8r8u8u837Ky837Ky01p8w9k3uy3ay1l1v83Jy1mzk1mzz1m3");
    string_constant_35 = 
	    STATIC_STRING("fyz1m3fyk1m3uy3Gy1m3fy3ay1m3fy3Ly1mz3Ly1mz3ay1mk3Gy001o1l8l1m83Dy53*MyShould we handle exporting of this icon-description, which");
    string_constant_36 = 
	    STATIC_STRING(" is defined ~\n on the class rather than inherited, differently from those on most other classes\?1l8o1l8z00000");
    string_constant_37 = 
	    STATIC_STRING("1z8q1n837Ky1m83Ry83-+y1m8v837Ky1n83--y01m8p83-*y1n83-0y01m8p83-0y1q83-Fy083Hy1m8p083Ny1m83Dy73-by3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Yy");
    string_constant_38 = 
	    STATIC_STRING("3-Ty3-fy3-Xy3Sy3-Ty3-ny3-my3-hy3-fy3-Ty3-my3-by3-Vy3-Ty3-ey3-ey3-ry3Sy3-Yy3-by3-ey3-ey3-Xy3-Wy3Sy3-by3-gy3gy1q83BDy83Ry8l8z8o1m8");
    string_constant_39 = 
	    STATIC_STRING("p83-Gy1q83BAy83Ry8l8z8o1m8p83-Gy1r834Uy08l8o1m8p83Ehy83Uy1m83Dy53-2yType = (or none symbol). writable = true, List of names not ");
    string_constant_40 = 
	    STATIC_STRING("permitted.1r83Smy08l8o1m8p83Ehy83Uy1m83Dy53aytype = (or symbol none), writable = true1q83cuy83Day8l8o1m8p83EDy1m83Dy53-*ytype = ");
    string_constant_41 = 
	    STATIC_STRING("(member one-to-one, one-to-many, many-to-one, many-to-many)1p83Yny08o1m8p83Eiy1m83Dy53bywritable = true, type = (or none boolean");
    string_constant_42 = 
	    STATIC_STRING(")1r83Egy08l8z1m8p83Ky8z1m83Dy53Rywritable = true, type = boolean1s83Yoy08l83Ey83Fy83-3y1m8p83Yoy1m83Dy53Rywritable = false, type");
    string_constant_43 = 
	    STATIC_STRING(" = string1o83Zny08l8o1n8u1p8w9k3uy3ay1l1v83Jy1mzk1mzz1m3fyz1m3fyk1m3uy3Gy1m3fy3ay1m3fy3Ly1mz3Ly1mz3ay1mk3Gy1m83Dy53*MyShould we ");
    string_constant_44 = 
	    STATIC_STRING("handle exporting of this icon-description, which is defined ~\n on the class rather than inherited, differently from those on mos");
    string_constant_45 = STATIC_STRING("t other classes\?");
    temp = regenerate_optimized_constant(string_constant_20);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(16,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25,string_constant_26,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31,string_constant_32,string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qrelation,list_constant_7,Nil,temp,Nil,
	    temp_1,list_constant_7,regenerate_optimized_constant(list(11,
	    string_constant_37,string_constant_25,string_constant_26,
	    string_constant_38,string_constant_39,string_constant_40,
	    string_constant_41,string_constant_42,string_constant_43,
	    string_constant_44,string_constant_45)),Nil);
    Relation_class_description = 
	    lookup_global_or_kb_specific_property_value(Qrelation,
	    Class_description_gkbprop);
    Qrelation_is_symetric = STATIC_SYMBOL("RELATION-IS-SYMETRIC",AB_package);
    Qput_relation_is_symetric_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-RELATION-IS-SYMETRIC-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_relation_is_symetric_where_slot_is_absent,
	    STATIC_FUNCTION(put_relation_is_symetric_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qrelation_is_symetric,
	    SYMBOL_FUNCTION(Qput_relation_is_symetric_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qclass_of_subject = STATIC_SYMBOL("CLASS-OF-SUBJECT",AB_package);
    Qfirst_class = STATIC_SYMBOL("FIRST-CLASS",AB_package);
    alias_slot_name(3,Qclass_of_subject,Qfirst_class,Qrelation);
    Qclass_of_object = STATIC_SYMBOL("CLASS-OF-OBJECT",AB_package);
    Qsecond_class = STATIC_SYMBOL("SECOND-CLASS",AB_package);
    alias_slot_name(3,Qclass_of_object,Qsecond_class,Qrelation);
    string_constant = 
	    STATIC_STRING("Cannot establish the relation ~a between ~NF and ~NF.  ~\n                  ~NF is not of class ~a.");
    Qrelationships = STATIC_SYMBOL("RELATIONSHIPS",AB_package);
    temp_2 = CONS(Qrelationships,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qrelationships,temp);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qrelation_name_reference = STATIC_SYMBOL("RELATION-NAME-REFERENCE",
	    AB_package);
    Qrelation_is_inverted = STATIC_SYMBOL("RELATION-IS-INVERTED",AB_package);
    Qrelated_items = STATIC_SYMBOL("RELATED-ITEMS",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_1 = 
	    STATIC_STRING("~a~%The value of a relation-name-reference component, ~\n                                 ~a, does not name a relation.");
    string_constant_2 = 
	    STATIC_STRING("The value of a relation-name-reference component, ~a, ~\n                             does not name a relation.");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    string_constant_3 = STATIC_STRING("~a~%~a");
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qab_class,Qblock);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_16 = STATIC_CONS(Qno_item,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qrelation_name_reference,
	    Qsymbol);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qrelation_is_inverted,
	    Qtruth_value);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_8,
	    FIX((SI_Long)1L));
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qrelated_items,list_constant_9);
    list_constant_13 = STATIC_LIST((SI_Long)3L,list_constant_10,
	    list_constant_11,list_constant_12);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qand,
	    Qrelation_name_reference,Qrelated_items);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_13,list_constant_14);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_15);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_16,
	    list_constant_17);
    Kevent_updates = STATIC_SYMBOL("EVENT-UPDATES",Pkeyword);
    Kwithin_putter = STATIC_SYMBOL("WITHIN-PUTTER",Pkeyword);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Kevent_updates,Kwithin_putter);
    Qinitial_relationships = STATIC_SYMBOL("INITIAL-RELATIONSHIPS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_relationships,
	    STATIC_FUNCTION(initial_relationships,NIL,FALSE,1,1));
    Qget_relationships = STATIC_SYMBOL("GET-RELATIONSHIPS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_relationships,
	    STATIC_FUNCTION(get_relationships,NIL,FALSE,1,1));
    Qset_relationships = STATIC_SYMBOL("SET-RELATIONSHIPS",AB_package);
    SET_SYMBOL_FUNCTION(Qset_relationships,
	    STATIC_FUNCTION(set_relationships,NIL,FALSE,2,2));
    add_virtual_attribute(Qrelationships,list_constant_18,list_constant_19,
	    list_constant_20,SYMBOL_FUNCTION(Qinitial_relationships),
	    SYMBOL_FUNCTION(Qget_relationships),
	    SYMBOL_FUNCTION(Qset_relationships));
    Qitems_in_this_relation = STATIC_SYMBOL("ITEMS-IN-THIS-RELATION",
	    AB_package);
    temp_2 = CONS(Qitems_in_this_relation,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qrelation),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qitems_in_this_relation,temp);
    set_property_value_function(get_symbol_properties_function(Qrelation),
	    Qvirtual_attributes_local_to_class,temp_2);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qab_class,Qrelation);
    list_constant_21 = STATIC_CONS(list_constant_9,Qnil);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_16,list_constant_21);
    Qinitial_items_in_this_relation = 
	    STATIC_SYMBOL("INITIAL-ITEMS-IN-THIS-RELATION",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_items_in_this_relation,
	    STATIC_FUNCTION(initial_items_in_this_relation,NIL,FALSE,1,1));
    Qget_items_in_this_relation = 
	    STATIC_SYMBOL("GET-ITEMS-IN-THIS-RELATION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_items_in_this_relation,
	    STATIC_FUNCTION(get_items_in_this_relation,NIL,FALSE,1,1));
    add_virtual_attribute(Qitems_in_this_relation,list_constant_22,
	    list_constant_23,list_constant_20,
	    SYMBOL_FUNCTION(Qinitial_items_in_this_relation),
	    SYMBOL_FUNCTION(Qget_items_in_this_relation),Nil);
    array_constant_2 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)57344L);
    Qrelation_yes_or_no_qm = STATIC_SYMBOL("RELATION-YES-OR-NO\?",AB_package);
    list_constant_24 = STATIC_CONS(Qrelation_yes_or_no_qm,Qnil);
    if (Grammar_categories_getting_yes_no_feature == UNBOUND)
	Grammar_categories_getting_yes_no_feature = list_constant_24;
    string_constant_4 = STATIC_STRING("yes");
    string_constant_5 = STATIC_STRING("no");
    Qwrite_relation_yes_or_no_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-RELATION-YES-OR-NO\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_relation_yes_or_no_qm_from_slot,
	    STATIC_FUNCTION(write_relation_yes_or_no_qm_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qrelation_yes_or_no_qm,
	    SYMBOL_FUNCTION(Qwrite_relation_yes_or_no_qm_from_slot),
	    Qslot_value_writer);
    Qrelation_name_qm = STATIC_SYMBOL("RELATION-NAME\?",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    mutate_global_property(Qrelation_name_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qrelation_name = STATIC_SYMBOL("RELATION-NAME",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)57344L);
    Qinverse_of_relation = STATIC_SYMBOL("INVERSE-OF-RELATION",AB_package);
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    string_constant_6 = 
	    STATIC_STRING("A symmetric relation may not have an inverse of relation.");
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)57344L);
    Qcompile_relation_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-RELATION-NAME\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_relation_name_qm_for_slot,
	    STATIC_FUNCTION(compile_relation_name_qm_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qrelation_name_qm,
	    SYMBOL_FUNCTION(Qcompile_relation_name_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qrelation_name_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_46 = 
	    STATIC_STRING("1r1m83EDy1m9k83-hjy1m83EDy1m9k83-hiy1m83EDy1m9k83-dgy1m83EDy1m9k83Day1m83Ehy834Uy1m83Ehy1m9k83Zy1m83Eiy83Ky");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_46));
    string_constant_7 = STATIC_STRING("~(~a~)");
    Qoneness_type = STATIC_SYMBOL("ONENESS-TYPE",AB_package);
    Qwrite_oneness_type_from_slot = 
	    STATIC_SYMBOL("WRITE-ONENESS-TYPE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_oneness_type_from_slot,
	    STATIC_FUNCTION(write_oneness_type_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qoneness_type,
	    SYMBOL_FUNCTION(Qwrite_oneness_type_from_slot),Qslot_value_writer);
    Qone_to_one = STATIC_SYMBOL("ONE-TO-ONE",AB_package);
    Qmany_to_many = STATIC_SYMBOL("MANY-TO-MANY",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qone_to_one,Qmany_to_many);
    string_constant_8 = 
	    STATIC_STRING("A symmetric relation can only be one-to-one or many-to-many.");
    Qcompile_oneness_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-ONENESS-TYPE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_oneness_type_for_slot,
	    STATIC_FUNCTION(compile_oneness_type_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qoneness_type,
	    SYMBOL_FUNCTION(Qcompile_oneness_type_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qoneness_type,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qoneness_type),
	    Qtype_specification_simple_expansion,Qnil);
    Qone_to_many = STATIC_SYMBOL("ONE-TO-MANY",AB_package);
    Qmany_to_one = STATIC_SYMBOL("MANY-TO-ONE",AB_package);
    list_constant_25 = STATIC_CONS(Qmany_to_many,Qnil);
    list_constant_2 = STATIC_LIST_STAR((SI_Long)5L,Qmember,Qone_to_one,
	    Qone_to_many,Qmany_to_one,list_constant_25);
    define_type_specification_explicit_complex_type(Qoneness_type,
	    list_constant_2);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,Qoneness_type);
    oneness_type_evaluation_setter_1 = 
	    STATIC_FUNCTION(oneness_type_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qoneness_type,
	    oneness_type_evaluation_setter_1);
    oneness_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(oneness_type_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qoneness_type,
	    oneness_type_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qrelation_yes_or_no_qm),
	    Qtype_specification_simple_expansion,Qtruth_value);
    define_type_specification_explicit_complex_type(Qrelation_yes_or_no_qm,
	    Qtruth_value);
    list_constant_3 = STATIC_CONS(Qnamed,list_constant_24);
    relation_yes_or_no_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(relation_yes_or_no_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qrelation_yes_or_no_qm,
	    relation_yes_or_no_qm_evaluation_setter_1);
    relation_yes_or_no_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(relation_yes_or_no_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrelation_yes_or_no_qm,
	    relation_yes_or_no_qm_evaluation_getter_1);
    string_constant_9 = STATIC_STRING("~(~a~a may be ~a ~a ~a~)");
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qone_to_one,Qmany_to_one);
    string_constant_10 = STATIC_STRING("at most one");
    string_constant_11 = STATIC_STRING("more than one");
    string_constant_12 = STATIC_STRING(";~%");
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qone_to_one,Qone_to_many);
    string_constant_13 = STATIC_STRING("~(~a ~a may be ~a ~a~a~)");
    Qrelation_summary = STATIC_SYMBOL("RELATION-SUMMARY",AB_package);
    Qwrite_relation_summary_from_slot = 
	    STATIC_SYMBOL("WRITE-RELATION-SUMMARY-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_relation_summary_from_slot,
	    STATIC_FUNCTION(write_relation_summary_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qrelation_summary,
	    SYMBOL_FUNCTION(Qwrite_relation_summary_from_slot),
	    Qslot_value_writer);
    string_constant_14 = STATIC_STRING("~a sEcReT iNvErSe NaMe");
    Qput_relation_name = STATIC_SYMBOL("PUT-RELATION-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qput_relation_name,
	    STATIC_FUNCTION(put_relation_name,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qrelation_name,
	    SYMBOL_FUNCTION(Qput_relation_name),Qslot_putter);
    Qreclaim_relation_name_value = 
	    STATIC_SYMBOL("RECLAIM-RELATION-NAME-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_relation_name_value,
	    STATIC_FUNCTION(reclaim_relation_name_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qrelation_name,
	    SYMBOL_FUNCTION(Qreclaim_relation_name_value),
	    Qslot_value_reclaimer);
    Qput_inverse_of_relation = STATIC_SYMBOL("PUT-INVERSE-OF-RELATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_inverse_of_relation,
	    STATIC_FUNCTION(put_inverse_of_relation,NIL,FALSE,3,3));
    mutate_global_property(Qinverse_of_relation,
	    SYMBOL_FUNCTION(Qput_inverse_of_relation),Qslot_putter);
    Qreclaim_inverse_of_relation_value = 
	    STATIC_SYMBOL("RECLAIM-INVERSE-OF-RELATION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_inverse_of_relation_value,
	    STATIC_FUNCTION(reclaim_inverse_of_relation_value,NIL,FALSE,2,2));
    mutate_global_property(Qinverse_of_relation,
	    SYMBOL_FUNCTION(Qreclaim_inverse_of_relation_value),
	    Qslot_value_reclaimer);
    Qput_class_of_subject = STATIC_SYMBOL("PUT-CLASS-OF-SUBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_class_of_subject,
	    STATIC_FUNCTION(put_class_of_subject,NIL,FALSE,3,3));
    mutate_global_property(Qclass_of_subject,
	    SYMBOL_FUNCTION(Qput_class_of_subject),Qslot_putter);
    Qput_class_of_object = STATIC_SYMBOL("PUT-CLASS-OF-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_class_of_object,
	    STATIC_FUNCTION(put_class_of_object,NIL,FALSE,3,3));
    mutate_global_property(Qclass_of_object,
	    SYMBOL_FUNCTION(Qput_class_of_object),Qslot_putter);
    Qtype_of_relation = STATIC_SYMBOL("TYPE-OF-RELATION",AB_package);
    Qput_type_of_relation = STATIC_SYMBOL("PUT-TYPE-OF-RELATION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_type_of_relation,
	    STATIC_FUNCTION(put_type_of_relation,NIL,FALSE,3,3));
    mutate_global_property(Qtype_of_relation,
	    SYMBOL_FUNCTION(Qput_type_of_relation),Qslot_putter);
    Qrelation_is_symmetric = STATIC_SYMBOL("RELATION-IS-SYMMETRIC",AB_package);
    Qput_relation_is_symmetric = STATIC_SYMBOL("PUT-RELATION-IS-SYMMETRIC",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_relation_is_symmetric,
	    STATIC_FUNCTION(put_relation_is_symmetric,NIL,FALSE,3,3));
    mutate_global_property(Qrelation_is_symmetric,
	    SYMBOL_FUNCTION(Qput_relation_is_symmetric),Qslot_putter);
    string_constant_15 = STATIC_STRING("There is no relation named ~a.");
    string_constant_16 = STATIC_STRING("~a");
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_17 = 
	    STATIC_STRING("Because the relation ~a is ~a and ~NF is currently ~a ~NF, you ~\n               cannot conclude that ~NF is ~a ~NF.");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    if (Resolving_definitional_name_conflicts_qm == UNBOUND)
	Resolving_definitional_name_conflicts_qm = Nil;
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qrelation_instances = STATIC_SYMBOL("RELATION-INSTANCES",AB_package);
    Qrelation_is_permanent = STATIC_SYMBOL("RELATION-IS-PERMANENT",AB_package);
    Qcleanup_for_relation = STATIC_SYMBOL("CLEANUP-FOR-RELATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_relation,
	    STATIC_FUNCTION(cleanup_for_relation,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_relation);
    set_get(Qrelation,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qrelation,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qclass_1 = STATIC_SYMBOL("CLASS-1",AB_package);
    Qclass_2 = STATIC_SYMBOL("CLASS-2",AB_package);
}
