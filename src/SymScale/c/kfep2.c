/* kfep2.c
 * Input file:  kfep2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kfep2.h"


Object Allowable_non_alpha_characters_in_kfep_conversions = UNBOUND;

/* KKA_P_BATKANAKAN */
Object kka_p_batkanakan(sw,inbuf,inlen,outbuf)
    Object sw, inbuf, inlen, outbuf;
{
    Object inbuf_to_use, reclaim_qm, number_of_jis_characters_used;
    Object bytes_in_output, number_of_candidates_left;
    Object result;

    x_note_fn_call(121,0);
    inbuf_to_use = inbuf;
    reclaim_qm = Nil;
    if (ARRAY_HAS_FILL_POINTER_P(inbuf)) {
	reclaim_qm = T;
	inbuf_to_use = copy_managed_lisp_string(inbuf,FIX((SI_Long)0L),inlen);
    }
    result = kfep_kka_p_batkanakan(sw,inbuf_to_use,inlen,outbuf);
    MVS_3(result,number_of_jis_characters_used,bytes_in_output,
	    number_of_candidates_left);
    if (reclaim_qm)
	reclaim_gensym_string(inbuf_to_use);
    return VALUES_3(number_of_jis_characters_used,bytes_in_output,
	    number_of_candidates_left);
}

Object Ascii_and_kana_suffix_pairs = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Ascii_to_kana_map, Qascii_to_kana_map);

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_length_of_ascii_string, Qmaximum_length_of_ascii_string);

DEFINE_VARIABLE_WITH_SYMBOL(Kana_to_ascii_map, Qkana_to_ascii_map);

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_length_of_kana_string, Qmaximum_length_of_kana_string);

DEFINE_VARIABLE_WITH_SYMBOL(Available_jis_map_hash_vector_307_vectors, Qavailable_jis_map_hash_vector_307_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_jis_map_hash_vector_307_vectors, Qcount_of_jis_map_hash_vector_307_vectors);

Object Available_jis_map_hash_vector_307_vectors_vector = UNBOUND;

/* JIS-MAP-HASH-VECTOR-307-VECTOR-MEMORY-USAGE */
Object jis_map_hash_vector_307_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(121,1);
    temp = Count_of_jis_map_hash_vector_307_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)307L)));
    return VALUES_1(temp);
}

/* OUT-JIS-MAP-HASH-VECTOR-307-VECTORS */
Object out_jis_map_hash_vector_307_vectors()
{
    Object temp;

    x_note_fn_call(121,2);
    temp = FIXNUM_MINUS(Count_of_jis_map_hash_vector_307_vectors,
	    length(Available_jis_map_hash_vector_307_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-JIS-MAP-HASH-VECTOR-307-VECTOR-INTERNAL */
Object make_permanent_jis_map_hash_vector_307_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(121,3);
    atomic_incff_symval(Qcount_of_jis_map_hash_vector_307_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)307L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-JIS-MAP-HASH-VECTOR */
Object make_jis_map_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(121,4);
    if (ISVREF(Available_jis_map_hash_vector_307_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_jis_map_hash_vector_307_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = Available_jis_map_hash_vector_307_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_jis_map_hash_vector_307_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_jis_map_hash_vector_307_vectors_vector,
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
	temp = make_permanent_jis_map_hash_vector_307_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-JIS-MAP-HASH-VECTOR */
Object reclaim_jis_map_hash_vector(jis_map_hash_vector_307_vector)
    Object jis_map_hash_vector_307_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(121,5);
    svref_arg_1 = Available_jis_map_hash_vector_307_vectors_vector;
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
    M_CAR(gensymed_symbol) = jis_map_hash_vector_307_vector;
    temp = ISVREF(Available_jis_map_hash_vector_307_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-JIS-MAP-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_jis_map_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(121,6);
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

/* RECLAIM-JIS-MAP-TREE-FOR-HASH-NODES */
Object reclaim_jis_map_tree_for_hash_nodes(jis_map_tree_for_hash_skip_list,
	    tail)
    Object jis_map_tree_for_hash_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(121,7);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(jis_map_tree_for_hash_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(jis_map_tree_for_hash_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(jis_map_tree_for_hash_skip_list,(SI_Long)2L);
    entry = ISVREF(jis_map_tree_for_hash_skip_list,(SI_Long)3L);
    reclaim_skip_list_element(jis_map_tree_for_hash_skip_list);
    jis_map_tree_for_hash_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-JIS-MAP-TREE */
Object clear_jis_map_tree(jis_map_tree_for_hash_skip_list)
    Object jis_map_tree_for_hash_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(121,8);
    head = M_CAR(M_CDR(jis_map_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(jis_map_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_jis_map_tree_for_hash_nodes(element_qm,tail);
    return VALUES_1(jis_map_tree_for_hash_skip_list);
}

static Object Qjis_map_tree_for_hash;  /* jis-map-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-JIS-MAP */
Object make_jis_map()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(121,9);
    new_vector = make_jis_map_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)307L)
	goto end_loop;
    tail = 
	    make_jis_map_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_jis_map_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qjis_map_tree_for_hash;
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

/* FLATTEN-JIS-MAP */
Object flatten_jis_map(jis_map_hash_table)
    Object jis_map_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(121,10);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)307L)
	goto end_loop;
    subtree = ISVREF(jis_map_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-JIS-MAP */
Object clear_jis_map(jis_map_hash_table)
    Object jis_map_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(121,11);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)307L)
	goto end_loop;
    clear_jis_map_tree(ISVREF(jis_map_hash_table,index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-JIS-MAP */
Object reclaim_jis_map(jis_map_hash_table)
    Object jis_map_hash_table;
{
    Object jis_map_tree_for_hash_skip_list, head, tail, element_qm, last_1;
    Object next_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(121,12);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)307L)
	goto end_loop;
    jis_map_tree_for_hash_skip_list = ISVREF(jis_map_hash_table,index_1);
    head = M_CAR(M_CDR(jis_map_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(jis_map_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_jis_map_tree_for_hash_nodes(element_qm,tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(jis_map_tree_for_hash_skip_list) = Nil;
    M_CADR(jis_map_tree_for_hash_skip_list) = Nil;
    M_CAR(jis_map_tree_for_hash_skip_list) = Nil;
    if (jis_map_tree_for_hash_skip_list) {
	last_1 = jis_map_tree_for_hash_skip_list;
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
	    M_CDR(temp) = jis_map_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = jis_map_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(jis_map_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = reclaim_jis_map_hash_vector(jis_map_hash_table);
    return VALUES_1(temp_1);
}

/* INITIALIZE-ASCII-KANA-CONVERTERS-IF-NECCESSARY */
Object initialize_ascii_kana_converters_if_neccessary()
{
    Object new_ascii_to_kana_map, new_kana_to_ascii_map, ascii_kana_pair;
    Object ab_loop_list_, ascii_string, kana_string_or_translation_marker;
    SI_Long gensymed_symbol, temp;

    x_note_fn_call(121,13);
    if ( !TRUEP(Ascii_to_kana_map) ||  !TRUEP(Kana_to_ascii_map)) {
	new_ascii_to_kana_map = make_jis_map();
	new_kana_to_ascii_map = make_jis_map();
	ascii_kana_pair = Nil;
	ab_loop_list_ = Ascii_and_kana_suffix_pairs;
	ascii_string = Nil;
	kana_string_or_translation_marker = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ascii_kana_pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ascii_string = CAR(ascii_kana_pair);
	kana_string_or_translation_marker = CDR(ascii_kana_pair);
	if (FIXNUM_GT(length(ascii_string),Maximum_length_of_ascii_string))
	    Maximum_length_of_ascii_string = length(ascii_string);
	if (STRINGP(kana_string_or_translation_marker)) {
	    if (FIXNUM_GT(length(kana_string_or_translation_marker),
		    Maximum_length_of_kana_string))
		Maximum_length_of_kana_string = 
			length(kana_string_or_translation_marker);
	    gensymed_symbol = IFIX(sxhashw(kana_string_or_translation_marker));
	    temp = gensymed_symbol % (SI_Long)307L;
	    set_skip_list_entry(SVREF(new_kana_to_ascii_map,FIX(temp)),
		    FIX((SI_Long)31L),Qstring_eq,Nil,T,
		    kana_string_or_translation_marker,FIX(gensymed_symbol),
		    ascii_string);
	}
	gensymed_symbol = IFIX(sxhashw(ascii_string));
	temp = gensymed_symbol % (SI_Long)307L;
	set_skip_list_entry(SVREF(new_ascii_to_kana_map,FIX(temp)),
		FIX((SI_Long)31L),Qstring_eq,Nil,T,ascii_string,
		FIX(gensymed_symbol),kana_string_or_translation_marker);
	goto next_loop;
      end_loop:;
	Ascii_to_kana_map = new_ascii_to_kana_map;
	Kana_to_ascii_map = new_kana_to_ascii_map;
	return VALUES_1(Kana_to_ascii_map);
    }
    else
	return VALUES_1(Nil);
}

/* MAP-LONGEST-POSSIBLE-SUBSTRING-USING-JIS-MAP */
Object map_longest_possible_substring_using_jis_map(string_1,jis_map,
	    start_index,end_index,maximum_length_of_substring_to_consider)
    Object string_1, jis_map, start_index, end_index;
    Object maximum_length_of_substring_to_consider;
{
    Object mapped_string_to_return_qm, length_of_substring_to_return_qm;
    Object substring, mapped_string_qm, temp, maximum_index_in_string;
    Object end_index_for_substring, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_2, entry_hash;
    SI_Long length_of_substring, gensymed_symbol, temp_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(121,14);
    mapped_string_to_return_qm = Nil;
    length_of_substring_to_return_qm = Nil;
    substring = Nil;
    mapped_string_qm = Nil;
    temp = length(string_1);
    maximum_index_in_string = FIXNUM_MIN(temp,end_index);
    length_of_substring = 
	    IFIX(FIXNUM_ADD(maximum_length_of_substring_to_consider,
	    start_index));
    end_index_for_substring = Nil;
  next_loop:
    if (length_of_substring < (SI_Long)1L)
	goto end_loop;
    end_index_for_substring = FIX(IFIX(start_index) + length_of_substring);
    if (FIXNUM_LE(end_index_for_substring,maximum_index_in_string)) {
	substring = gensym_string_substring(string_1,start_index,
		end_index_for_substring);
	gensymed_symbol = IFIX(sxhashw(substring));
	temp_1 = gensymed_symbol % (SI_Long)307L;
	temp = SVREF(jis_map,FIX(temp_1));
	skip_list = CDR(temp);
	key_value = substring;
	key_hash_value = gensymed_symbol;
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
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
	goto next_loop_3;
      end_loop_2:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !TRUEP(string_eq(2,key_value,
		ISVREF(curr,(SI_Long)2L)))) {
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
	mapped_string_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (string_eq(2,key_value,ISVREF(curr,
		(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	reclaim_gensym_string(substring);
	if (mapped_string_qm) {
	    mapped_string_to_return_qm = mapped_string_qm;
	    length_of_substring_to_return_qm = FIX(length_of_substring);
	    goto end_2;
	}
    }
    length_of_substring = length_of_substring - (SI_Long)1L;
    goto next_loop;
  end_loop:
    goto end_2;
  end_2:;
    return VALUES_2(mapped_string_to_return_qm,
	    length_of_substring_to_return_qm);
}

Object Ascii_to_jis_code_map = UNBOUND;

static Object Qascii;              /* ascii */

/* CONVERT-ASCII-TO-KANA-IN-LISP-STRING */
Object convert_ascii_to_kana_in_lisp_string(case_insensitive_ascii_buffer,
	    number_of_bytes_in_ascii_buffer,kana_buffer,
	    size_of_kana_buffer_in_bytes,convert_to_hiragana_p)
    Object case_insensitive_ascii_buffer, number_of_bytes_in_ascii_buffer;
    Object kana_buffer, size_of_kana_buffer_in_bytes, convert_to_hiragana_p;
{
    Object ascii_buffer, ascii_buffer_index, kana_buffer_index, translation_qm;
    Object ascii_buffer_index_increment_qm, switch_once_to_katakana_p;
    Object after_switch_once_to_katakana_p, character_1, incff_1_arg, temp;
    Object ascii_character, char_new_value_2, string_is_simple_qm, jis_code;
    SI_Long index_1, ab_loop_bind_, jis_index, base_index, byte_index;
    SI_Long char_arg_2;
    char kana_high_byte_character, char_new_value;
    char char_new_value_1;
    Object result;

    x_note_fn_call(121,15);
    ascii_buffer = 
	    copy_lisp_string_with_change_to_upper_case(case_insensitive_ascii_buffer);
    ascii_buffer_index = FIX((SI_Long)0L);
    kana_buffer_index = FIX((SI_Long)0L);
    kana_high_byte_character = convert_to_hiragana_p ? 
	    CHARACTER_TO_CHAR(CODE_CHAR(FIX((SI_Long)36L))) : 
	    CHARACTER_TO_CHAR(CODE_CHAR(FIX((SI_Long)37L)));
  next_loop:
    if ( !(FIXNUM_LT(ascii_buffer_index,number_of_bytes_in_ascii_buffer) 
	    && FIXNUM_LT(kana_buffer_index,size_of_kana_buffer_in_bytes)))
	goto end_loop;
    result = map_longest_possible_substring_using_jis_map(ascii_buffer,
	    Ascii_to_kana_map,ascii_buffer_index,
	    number_of_bytes_in_ascii_buffer,Maximum_length_of_ascii_string);
    MVS_2(result,translation_qm,ascii_buffer_index_increment_qm);
    if (STRINGP(translation_qm)) {
	switch_once_to_katakana_p = Nil;
	after_switch_once_to_katakana_p = Nil;
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(translation_qm));
	character_1 = Nil;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	character_1 = CHR(ICHAR(translation_qm,index_1));
	if (after_switch_once_to_katakana_p && CHAR_EQ(character_1,CHR('%')));
	else if (CHAR_EQ(character_1,CHR('~'))) {
	    after_switch_once_to_katakana_p = Nil;
	    switch_once_to_katakana_p = T;
	}
	else {
	    after_switch_once_to_katakana_p = Nil;
	    char_new_value = switch_once_to_katakana_p ? '%' : 
		    kana_high_byte_character;
	    SET_CHAR(kana_buffer,kana_buffer_index,
		    CHAR_TO_CHARACTER(char_new_value));
	    if (switch_once_to_katakana_p)
		after_switch_once_to_katakana_p = T;
	    switch_once_to_katakana_p = Nil;
	    kana_buffer_index = FIXNUM_ADD1(kana_buffer_index);
	    if (FIXNUM_LT(kana_buffer_index,size_of_kana_buffer_in_bytes)) {
		char_new_value_1 = ICHAR(translation_qm,index_1);
		SET_CHAR(kana_buffer,kana_buffer_index,CHR(char_new_value_1));
	    }
	    kana_buffer_index = FIXNUM_ADD1(kana_buffer_index);
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	incff_1_arg = ascii_buffer_index_increment_qm;
	ascii_buffer_index = FIXNUM_ADD(ascii_buffer_index,incff_1_arg);
    }
    else if (EQUAL(translation_qm,Qascii)) {
	index_1 = IFIX(ascii_buffer_index);
	ab_loop_bind_ = IFIX(FIXNUM_ADD(ascii_buffer_index,
		ascii_buffer_index_increment_qm));
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	temp = CHR('#');
	SET_CHAR(kana_buffer,kana_buffer_index,temp);
	kana_buffer_index = FIXNUM_ADD1(kana_buffer_index);
	if (FIXNUM_LT(kana_buffer_index,size_of_kana_buffer_in_bytes)) {
	    char_new_value_1 = ICHAR(case_insensitive_ascii_buffer,index_1);
	    SET_CHAR(kana_buffer,kana_buffer_index,CHR(char_new_value_1));
	}
	kana_buffer_index = FIXNUM_ADD1(kana_buffer_index);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	incff_1_arg = ascii_buffer_index_increment_qm;
	ascii_buffer_index = FIXNUM_ADD(ascii_buffer_index,incff_1_arg);
    }
    else {
	ascii_character = CHAR(case_insensitive_ascii_buffer,
		ascii_buffer_index);
	translation_qm = ISVREF(Ascii_to_jis_code_map,
		IFIX(CHAR_INT(ascii_character)));
	ascii_buffer_index = FIXNUM_ADD1(ascii_buffer_index);
	char_new_value_2 = CHAR(translation_qm,FIX((SI_Long)0L));
	SET_CHAR(kana_buffer,kana_buffer_index,char_new_value_2);
	kana_buffer_index = FIXNUM_ADD1(kana_buffer_index);
	if (FIXNUM_LT(kana_buffer_index,size_of_kana_buffer_in_bytes)) {
	    char_new_value_2 = CHAR(translation_qm,FIX((SI_Long)1L));
	    SET_CHAR(kana_buffer,kana_buffer_index,char_new_value_2);
	}
	kana_buffer_index = FIXNUM_ADD1(kana_buffer_index);
    }
    goto next_loop;
  end_loop:
    reclaim_gensym_string(ascii_buffer);
    string_is_simple_qm = Nil;
    jis_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(kana_buffer_index) >>  -  - (SI_Long)1L;
    jis_code = Nil;
  next_loop_3:
    if (jis_index >= ab_loop_bind_)
	goto end_loop_3;
    if (string_is_simple_qm) {
	base_index = jis_index << (SI_Long)1L;
	jis_code = FIX((IFIX(CHAR_INT(CHR(ISCHAR(kana_buffer,
		base_index)))) << (SI_Long)8L) + 
		IFIX(CHAR_INT(CHR(ISCHAR(kana_buffer,base_index + 
		(SI_Long)1L)))));
    }
    else {
	base_index = jis_index << (SI_Long)1L;
	jis_code = FIX((IFIX(CHAR_INT(CHR(ICHAR(kana_buffer,base_index)))) 
		<< (SI_Long)8L) + IFIX(CHAR_INT(CHR(ICHAR(kana_buffer,
		base_index + (SI_Long)1L)))));
    }
    if (IFIX(jis_code) == (SI_Long)9038L || IFIX(jis_code) == (SI_Long)9070L) {
	byte_index = jis_index << (SI_Long)1L;
	SET_ICHAR(kana_buffer,byte_index,kana_high_byte_character);
	char_arg_2 = byte_index + (SI_Long)1L;
	SET_ICHAR(kana_buffer,char_arg_2,'s');
    }
    jis_index = jis_index + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    if (FIXNUM_LT(ascii_buffer_index,number_of_bytes_in_ascii_buffer) && 
	    FIXNUM_GE(kana_buffer_index,size_of_kana_buffer_in_bytes))
	return VALUES_1(FIX((SI_Long)-1L));
    else
	return VALUES_1(kana_buffer_index);
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_roman_kana_g2_length, Qlast_roman_kana_g2_length);

/* ROMAN_KANA_G2 */
Object roman_kana_g2(roman_ascii_buffer,length_of_ascii_buffer,kana_buffer,
	    number_of_bytes_in_kana_buffer,last_value_p)
    Object roman_ascii_buffer, length_of_ascii_buffer, kana_buffer;
    Object number_of_bytes_in_kana_buffer, last_value_p;
{
    Object result_1;

    x_note_fn_call(121,16);
    if (IFIX(last_value_p) == (SI_Long)0L) {
	result_1 = convert_ascii_to_kana_in_lisp_string(roman_ascii_buffer,
		length_of_ascii_buffer,kana_buffer,
		number_of_bytes_in_kana_buffer,T);
	if (IFIX(result_1) < (SI_Long)0L)
	    return VALUES_1(result_1);
	else {
	    Last_roman_kana_g2_length = result_1;
	    return VALUES_1(Last_roman_kana_g2_length);
	}
    }
    else
	return VALUES_1(Last_roman_kana_g2_length);
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_roman_kata_g2_length, Qlast_roman_kata_g2_length);

/* ROMAN_KATA_G2 */
Object roman_kata_g2(roman_ascii_buffer,length_of_ascii_buffer,kata_buffer,
	    number_of_bytes_in_kata_buffer,last_value_p)
    Object roman_ascii_buffer, length_of_ascii_buffer, kata_buffer;
    Object number_of_bytes_in_kata_buffer, last_value_p;
{
    Object result_1;

    x_note_fn_call(121,17);
    if (IFIX(last_value_p) == (SI_Long)0L) {
	result_1 = convert_ascii_to_kana_in_lisp_string(roman_ascii_buffer,
		length_of_ascii_buffer,kata_buffer,
		number_of_bytes_in_kata_buffer,Nil);
	if (IFIX(result_1) < (SI_Long)0L)
	    return VALUES_1(result_1);
	else {
	    Last_roman_kata_g2_length = result_1;
	    return VALUES_1(Last_roman_kata_g2_length);
	}
    }
    else
	return VALUES_1(Last_roman_kata_g2_length);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_converters_have_been_initialized_qm, Qkfep_converters_have_been_initialized_qm);

/* INITIALIZE-FOR-ASIAN-LANGUAGES */
Object initialize_for_asian_languages()
{
    Object code;

    x_note_fn_call(121,18);
    if (T) {
	Hfep_capability_qm = T;
	Kfep_capability_qm = T;
    }
    if (T) {
	code = M_CAR(M_CDR(Get_object_on_kb_workspace_for_item));
	if (FIXNUMP(code) && (IFIX(code) & (SI_Long)2048L) != (SI_Long)0L ?
		 TRUEP(M_CAR(M_CDR(Cache_korean_semantics_graph))) : 
		TRUEP(Nil))
	    load_korean_outline_font();
	Hfep_capability_qm = T;
    }
    code = M_CAR(M_CDR(Reclaim_fonts_stack));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)32L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_chinese_semantics_graph))) : TRUEP(Nil)) {
	code = M_CAR(M_CDR(Reclaim_fonts_stack));
	if (FIXNUMP(code) && (IFIX(code) & (SI_Long)32L) != (SI_Long)0L ? 
		TRUEP(M_CAR(M_CDR(Cache_chinese_semantics_graph))) : 
		TRUEP(Nil))
	    return load_chinese_outline_font();
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_kb_serial_number, Qcurrent_kb_serial_number);

static Object string_constant;     /* "~a~%Please wait . . . " */

static Object string_constant_1;   /* "Initializing Korean outline font ..." */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* LOAD-KOREAN-OUTLINE-FONT */
Object load_korean_outline_font()
{
    Object temp, current_long_operation_notification_workspace;
    Object frame_serial_number, kb_serial_number;
    Object fixnum_time_at_start_of_current_long_notification;
    Object doing_long_operation_with_notification_qm;
    Object long_operation_notification_has_been_put_up_qm, gensymed_symbol_2;
    Object xa, ya;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(121,19);
    SAVE_STACK();
    temp = make_message(1,tformat_text_string(2,string_constant,
	    tformat_text_string(1,string_constant_1)));
    current_long_operation_notification_workspace = make_workspace(6,
	    Qtemporary_workspace,Nil,temp,Nil,
	    Width_for_prominent_notification_workspaces,
	    Height_for_prominent_notification_workspaces);
    PUSH_SPECIAL_WITH_SYMBOL(Current_long_operation_notification_workspace,Qcurrent_long_operation_notification_workspace,current_long_operation_notification_workspace,
	    3);
      frame_serial_number = 
	      copy_frame_serial_number(Current_frame_serial_number);
      kb_serial_number = Current_kb_serial_number;
      fixnum_time_at_start_of_current_long_notification = 
	      c_native_clock_ticks_or_cache(Nil,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Fixnum_time_at_start_of_current_long_notification,Qfixnum_time_at_start_of_current_long_notification,fixnum_time_at_start_of_current_long_notification,
	      2);
	if (PUSH_UNWIND_PROTECT(0)) {
	    doing_long_operation_with_notification_qm = T;
	    long_operation_notification_has_been_put_up_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Long_operation_notification_has_been_put_up_qm,Qlong_operation_notification_has_been_put_up_qm,long_operation_notification_has_been_put_up_qm,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Doing_long_operation_with_notification_qm,Qdoing_long_operation_with_notification_qm,doing_long_operation_with_notification_qm,
		      0);
		if ( !TRUEP(Nil)) {
		    if (Doing_long_operation_with_notification_qm &&  
			    !TRUEP(Long_operation_notification_has_been_put_up_qm)) 
				{
			gensymed_symbol = 
				IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
			gensymed_symbol_1 = 
				IFIX(Fixnum_time_at_start_of_current_long_notification);
			if (gensymed_symbol >= gensymed_symbol_1)
			    temp = FIX(gensymed_symbol - gensymed_symbol_1);
			else {
			    gensymed_symbol = gensymed_symbol - 
				    gensymed_symbol_1;
			    gensymed_symbol = gensymed_symbol + 
				    IFIX(Most_positive_fixnum);
			    temp = FIX(gensymed_symbol + (SI_Long)1L);
			}
			temp_1 = FIXNUM_GE(temp,
				fixnum_time_interval(FIX((SI_Long)0L)));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			put_up_long_operation_notification_now();
		}
		SAVE_VALUES(load_hangul_font());
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	if (FIXNUM_EQ(Current_kb_serial_number,kb_serial_number)) {
	    gensymed_symbol_2 = 
		    ISVREF(Current_long_operation_notification_workspace,
		    (SI_Long)3L);
	    temp_1 = 
		    SIMPLE_VECTOR_P(Current_long_operation_notification_workspace) 
		    ? 
		    EQ(ISVREF(Current_long_operation_notification_workspace,
		    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			IFIX(gensymed_symbol_2) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_serial_number))
		temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			FIXNUM_LT(frame_serial_number,gensymed_symbol_2) : 
			TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_2))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number);
		ya = M_CAR(gensymed_symbol_2);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number),
			    M_CDR(gensymed_symbol_2)) : TRUEP(Qnil);
	    }
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    delete_frame(Current_long_operation_notification_workspace);
	reclaim_frame_serial_number(frame_serial_number);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_2;   /* "Initializing Chinese outline font ..." */

/* LOAD-CHINESE-OUTLINE-FONT */
Object load_chinese_outline_font()
{
    Object temp, current_long_operation_notification_workspace;
    Object frame_serial_number, kb_serial_number;
    Object fixnum_time_at_start_of_current_long_notification;
    Object doing_long_operation_with_notification_qm;
    Object long_operation_notification_has_been_put_up_qm, gensymed_symbol_2;
    Object xa, ya;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(121,20);
    SAVE_STACK();
    temp = make_message(1,tformat_text_string(2,string_constant,
	    tformat_text_string(1,string_constant_2)));
    current_long_operation_notification_workspace = make_workspace(6,
	    Qtemporary_workspace,Nil,temp,Nil,
	    Width_for_prominent_notification_workspaces,
	    Height_for_prominent_notification_workspaces);
    PUSH_SPECIAL_WITH_SYMBOL(Current_long_operation_notification_workspace,Qcurrent_long_operation_notification_workspace,current_long_operation_notification_workspace,
	    3);
      frame_serial_number = 
	      copy_frame_serial_number(Current_frame_serial_number);
      kb_serial_number = Current_kb_serial_number;
      fixnum_time_at_start_of_current_long_notification = 
	      c_native_clock_ticks_or_cache(Nil,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Fixnum_time_at_start_of_current_long_notification,Qfixnum_time_at_start_of_current_long_notification,fixnum_time_at_start_of_current_long_notification,
	      2);
	if (PUSH_UNWIND_PROTECT(0)) {
	    doing_long_operation_with_notification_qm = T;
	    long_operation_notification_has_been_put_up_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Long_operation_notification_has_been_put_up_qm,Qlong_operation_notification_has_been_put_up_qm,long_operation_notification_has_been_put_up_qm,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Doing_long_operation_with_notification_qm,Qdoing_long_operation_with_notification_qm,doing_long_operation_with_notification_qm,
		      0);
		if ( !TRUEP(Nil)) {
		    if (Doing_long_operation_with_notification_qm &&  
			    !TRUEP(Long_operation_notification_has_been_put_up_qm)) 
				{
			gensymed_symbol = 
				IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
			gensymed_symbol_1 = 
				IFIX(Fixnum_time_at_start_of_current_long_notification);
			if (gensymed_symbol >= gensymed_symbol_1)
			    temp = FIX(gensymed_symbol - gensymed_symbol_1);
			else {
			    gensymed_symbol = gensymed_symbol - 
				    gensymed_symbol_1;
			    gensymed_symbol = gensymed_symbol + 
				    IFIX(Most_positive_fixnum);
			    temp = FIX(gensymed_symbol + (SI_Long)1L);
			}
			temp_1 = FIXNUM_GE(temp,
				fixnum_time_interval(FIX((SI_Long)0L)));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			put_up_long_operation_notification_now();
		}
		SAVE_VALUES(load_chinese_font());
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	if (FIXNUM_EQ(Current_kb_serial_number,kb_serial_number)) {
	    gensymed_symbol_2 = 
		    ISVREF(Current_long_operation_notification_workspace,
		    (SI_Long)3L);
	    temp_1 = 
		    SIMPLE_VECTOR_P(Current_long_operation_notification_workspace) 
		    ? 
		    EQ(ISVREF(Current_long_operation_notification_workspace,
		    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			IFIX(gensymed_symbol_2) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_serial_number))
		temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			FIXNUM_LT(frame_serial_number,gensymed_symbol_2) : 
			TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_2))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number);
		ya = M_CAR(gensymed_symbol_2);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number),
			    M_CDR(gensymed_symbol_2)) : TRUEP(Qnil);
	    }
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    delete_frame(Current_long_operation_notification_workspace);
	reclaim_frame_serial_number(frame_serial_number);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qkfep_filename;      /* kfep-filename */

static Object string_constant_3;   /* "Initializing KFEP dictionaries from ~s, ~s, and ~s." */

static Object string_constant_4;   /* "The KFEP dictionaries have been initialized from ~s, ~s, and ~s." */

static Object string_constant_5;   /* "Some of the KFEP dictionary files ~s, ~s, or ~s could not be accessed." */

/* INITIALIZE-KANA-TO-KANJI-CONVERTERS */
Object initialize_kana_to_kanji_converters()
{
    Object kfep_index_filename_in_file_system;
    Object kfep_main_filename_in_file_system;
    Object kfep_kojin_filename_in_file_system;
    volatile Object kfep_index_filename_for_user;
    volatile Object kfep_main_filename_for_user;
    volatile Object kfep_kojin_filename_for_user;
    Object temp, current_long_operation_notification_workspace;
    Object frame_serial_number, kb_serial_number;
    Object fixnum_time_at_start_of_current_long_notification;
    Object doing_long_operation_with_notification_qm;
    Object long_operation_notification_has_been_put_up_qm, gensymed_symbol_2;
    Object xa, ya;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(4);
    Object result;

    x_note_fn_call(121,21);
    SAVE_STACK();
    if ( !TRUEP(Kfep_converters_have_been_initialized_qm)) {
	initialize_ascii_kana_converters_if_neccessary();
	kfep_index_filename_in_file_system = Qunbound_in_protected_let;
	kfep_main_filename_in_file_system = Qunbound_in_protected_let;
	kfep_kojin_filename_in_file_system = Qunbound_in_protected_let;
	kfep_index_filename_for_user = Qunbound_in_protected_let;
	kfep_main_filename_for_user = Qunbound_in_protected_let;
	kfep_kojin_filename_for_user = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(1)) {
	    kfep_index_filename_in_file_system = get_kfep_index_filename();
	    kfep_main_filename_in_file_system = get_kfep_main_filename();
	    kfep_kojin_filename_in_file_system = get_kfep_kojin_filename();
	    kfep_index_filename_for_user = import_text_string(2,
		    kfep_index_filename_in_file_system,Qkfep_filename);
	    kfep_main_filename_for_user = import_text_string(2,
		    kfep_main_filename_in_file_system,Qkfep_filename);
	    kfep_kojin_filename_for_user = import_text_string(2,
		    kfep_kojin_filename_in_file_system,Qkfep_filename);
	    temp = make_message(1,tformat_text_string(2,string_constant,
		    tformat_text_string(4,string_constant_3,
		    kfep_index_filename_for_user,
		    kfep_main_filename_for_user,
		    kfep_kojin_filename_for_user)));
	    current_long_operation_notification_workspace = 
		    make_workspace(6,Qtemporary_workspace,Nil,temp,Nil,
		    Width_for_prominent_notification_workspaces,
		    Height_for_prominent_notification_workspaces);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_long_operation_notification_workspace,Qcurrent_long_operation_notification_workspace,current_long_operation_notification_workspace,
		    3);
	      frame_serial_number = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      kb_serial_number = Current_kb_serial_number;
	      fixnum_time_at_start_of_current_long_notification = 
		      c_native_clock_ticks_or_cache(Nil,Nil);
	      PUSH_SPECIAL_WITH_SYMBOL(Fixnum_time_at_start_of_current_long_notification,Qfixnum_time_at_start_of_current_long_notification,fixnum_time_at_start_of_current_long_notification,
		      2);
		if (PUSH_UNWIND_PROTECT(0)) {
		    doing_long_operation_with_notification_qm = T;
		    long_operation_notification_has_been_put_up_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Long_operation_notification_has_been_put_up_qm,Qlong_operation_notification_has_been_put_up_qm,long_operation_notification_has_been_put_up_qm,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Doing_long_operation_with_notification_qm,Qdoing_long_operation_with_notification_qm,doing_long_operation_with_notification_qm,
			      0);
			if ( !TRUEP(Nil)) {
			    if (Doing_long_operation_with_notification_qm 
				    &&  
				    !TRUEP(Long_operation_notification_has_been_put_up_qm)) 
					{
				gensymed_symbol = 
					IFIX(c_native_clock_ticks_or_cache(Nil,
					Nil));
				gensymed_symbol_1 = 
					IFIX(Fixnum_time_at_start_of_current_long_notification);
				if (gensymed_symbol >= gensymed_symbol_1)
				    temp = FIX(gensymed_symbol - 
					    gensymed_symbol_1);
				else {
				    gensymed_symbol = gensymed_symbol - 
					    gensymed_symbol_1;
				    gensymed_symbol = gensymed_symbol + 
					    IFIX(Most_positive_fixnum);
				    temp = FIX(gensymed_symbol + (SI_Long)1L);
				}
				temp_1 = FIXNUM_GE(temp,
					fixnum_time_interval(FIX((SI_Long)0L)));
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1)
				put_up_long_operation_notification_now();
			}
			force_process_drawing();
			if (g2_stream_probe_file_for_read(kfep_index_filename_in_file_system) 
				&&  
				!TRUEP(g2_stream_directory_p(kfep_index_filename_in_file_system)) 
				&& 
				g2_stream_probe_file_for_read(kfep_main_filename_in_file_system) 
				&&  
				!TRUEP(g2_stream_directory_p(kfep_main_filename_in_file_system)) 
				&& 
				g2_stream_probe_file_for_read(kfep_kojin_filename_in_file_system) 
				&&  
				!TRUEP(g2_stream_directory_p(kfep_kojin_filename_in_file_system)) 
				&& kfep_kka_mainit(FIX((SI_Long)0L),
				kfep_index_filename_in_file_system,
				kfep_main_filename_in_file_system,
				kfep_kojin_filename_in_file_system)) {
			    force_process_drawing();
			    temp_1 = TRUEP(kfep_kka_koinit());
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    force_process_drawing();
			    Kfep_converters_have_been_initialized_qm = T;
			    Kfep_capability_qm = T;
			    notify_user(4,string_constant_4,
				    kfep_index_filename_for_user,
				    kfep_main_filename_for_user,
				    kfep_kojin_filename_for_user);
			}
			else
			    notify_user(4,string_constant_5,
				    kfep_index_filename_for_user,
				    kfep_main_filename_for_user,
				    kfep_kojin_filename_for_user);
			SAVE_VALUES(force_process_drawing());
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		POP_UNWIND_PROTECT(0);
		if (FIXNUM_EQ(Current_kb_serial_number,kb_serial_number)) {
		    gensymed_symbol_2 = 
			    ISVREF(Current_long_operation_notification_workspace,
			    (SI_Long)3L);
		    temp_1 = 
			    SIMPLE_VECTOR_P(Current_long_operation_notification_workspace) 
			    ? 
			    EQ(ISVREF(Current_long_operation_notification_workspace,
			    (SI_Long)1L),Qavailable_frame_vector) : 
			    TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = FIXNUMP(gensymed_symbol_2) ? 
				IFIX(gensymed_symbol_2) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp_1);
		    else if (FIXNUMP(frame_serial_number))
			temp_1 = FIXNUMP(gensymed_symbol_2) ? 
				FIXNUM_LT(frame_serial_number,
				gensymed_symbol_2) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol_2))
			temp_1 = TRUEP(Nil);
		    else {
			xa = M_CAR(frame_serial_number);
			ya = M_CAR(gensymed_symbol_2);
			temp_1 = FIXNUM_LT(xa,ya);
			if (temp_1);
			else
			    temp_1 = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(frame_serial_number),
				    M_CDR(gensymed_symbol_2)) : TRUEP(Qnil);
		    }
		    temp_1 =  !temp_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    delete_frame(Current_long_operation_notification_workspace);
		reclaim_frame_serial_number(frame_serial_number);
		CONTINUE_UNWINDING(0);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(1);
	if (kfep_kojin_filename_for_user) {
	    if ( !EQ(kfep_kojin_filename_for_user,Qunbound_in_protected_let))
		reclaim_text_string(kfep_kojin_filename_for_user);
	}
	if (kfep_main_filename_for_user) {
	    if ( !EQ(kfep_main_filename_for_user,Qunbound_in_protected_let))
		reclaim_text_string(kfep_main_filename_for_user);
	}
	if (kfep_index_filename_for_user) {
	    if ( !EQ(kfep_index_filename_for_user,Qunbound_in_protected_let))
		reclaim_text_string(kfep_index_filename_for_user);
	}
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object array_constant;      /* # */

/* GET-KFEP-INDEX-FILENAME */
Object get_kfep_index_filename()
{
    Object filename_variable, temp;

    x_note_fn_call(121,22);
    filename_variable = Qspecified_kfep_index_filename_qm;
    temp = SYMBOL_VALUE(filename_variable);
    if (temp);
    else
	temp = get_command_line_keyword_argument(1,array_constant);
    if (temp);
    else
	temp = make_absolute_pathname_if_possible(Kfep_index_filename);
    return set(filename_variable,temp);
}

static Object array_constant_1;    /* # */

/* GET-KFEP-MAIN-FILENAME */
Object get_kfep_main_filename()
{
    Object filename_variable, temp;

    x_note_fn_call(121,23);
    filename_variable = Qspecified_kfep_main_filename_qm;
    temp = SYMBOL_VALUE(filename_variable);
    if (temp);
    else
	temp = get_command_line_keyword_argument(1,array_constant_1);
    if (temp);
    else
	temp = make_absolute_pathname_if_possible(Kfep_main_filename);
    return set(filename_variable,temp);
}

static Object array_constant_2;    /* # */

/* GET-KFEP-KOJIN-FILENAME */
Object get_kfep_kojin_filename()
{
    Object filename_variable, temp;

    x_note_fn_call(121,24);
    filename_variable = Qspecified_kfep_kojin_filename_qm;
    temp = SYMBOL_VALUE(filename_variable);
    if (temp);
    else
	temp = get_command_line_keyword_argument(1,array_constant_2);
    if (temp);
    else
	temp = make_absolute_pathname_if_possible(Kfep_kojin_filename);
    return set(filename_variable,temp);
}

/* CONVERT-TO-JIS-STRING-IF-POSSIBLE */
Object convert_to_jis_string_if_possible(string_1)
    Object string_1;
{
    Object string_length, jis_string, jis_string_is_simple_qm, wide_character;
    Object jis_code_qm, temp, unicode, cjk_code, cjk_code_mapping_vector, l;
    Object temp_2, gensymed_symbol_1, jis_string_1;
    SI_Long string_index, jis_string_index, temp_1, base_index, temp_3;
    SI_Long gensymed_symbol, jis_char_new_value, arg, arg_1, arg_2, index_1;

    x_note_fn_call(121,25);
    string_length = text_string_length(string_1);
    string_index = (SI_Long)0L;
    jis_string = obtain_simple_gensym_string(FIX(IFIX(string_length) << 
	    (SI_Long)1L << (SI_Long)1L));
    jis_string_is_simple_qm = Nil;
    jis_string_index = (SI_Long)0L;
    wide_character = Nil;
    jis_code_qm = Nil;
  next_loop:
    if (string_index >= IFIX(string_length))
	return VALUES_2(jis_string,FIX(jis_string_index << (SI_Long)1L));
    temp = FIX(UBYTE_16_ISAREF_1(string_1,string_index));
    string_index = string_index + (SI_Long)1L;
    wide_character = temp;
    unicode = wide_character;
    cjk_code = unicode;
    cjk_code_mapping_vector = Unicode_to_jis_x_0208_map;
    temp_1 = IFIX(cjk_code) % (SI_Long)307L;
    l = ISVREF(cjk_code_mapping_vector,temp_1);
  next_loop_1:
    if ( !TRUEP(l))
	goto end_loop;
    if (FIXNUM_EQ(CAR(l),cjk_code)) {
	jis_code_qm = CADR(l);
	goto end_1;
    }
    l = CDDR(l);
    goto next_loop_1;
  end_loop:
    jis_code_qm = Qnil;
  end_1:;
    if (jis_code_qm) {
	if (jis_string_is_simple_qm) {
	    base_index = jis_string_index << (SI_Long)1L;
	    temp_2 = CODE_CHAR(FIX(IFIX(jis_code_qm) >>  -  - (SI_Long)8L));
	    SET_ISCHAR(jis_string,base_index,ICHAR_CODE(temp_2));
	    temp_3 = base_index + (SI_Long)1L;
	    gensymed_symbol = IFIX(jis_code_qm) & (SI_Long)255L;
	    temp_2 = CODE_CHAR(FIX(gensymed_symbol));
	    SET_ISCHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
	}
	else {
	    base_index = jis_string_index << (SI_Long)1L;
	    temp_2 = CODE_CHAR(FIX(IFIX(jis_code_qm) >>  -  - (SI_Long)8L));
	    SET_ICHAR(jis_string,base_index,ICHAR_CODE(temp_2));
	    temp_3 = base_index + (SI_Long)1L;
	    gensymed_symbol = IFIX(jis_code_qm) & (SI_Long)255L;
	    temp_2 = CODE_CHAR(FIX(gensymed_symbol));
	    SET_ICHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
	}
    }
    else {
	gensymed_symbol_1 = wide_character;
	if ((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
		IFIX(gensymed_symbol_1) <= (SI_Long)122L || (SI_Long)65L 
		<= IFIX(gensymed_symbol_1) && IFIX(gensymed_symbol_1) <= 
		(SI_Long)90L) {
	    jis_char_new_value = (SI_Long)9025L - (SI_Long)65L + 
		    IFIX(wide_character);
	    if (jis_string_is_simple_qm) {
		base_index = jis_string_index << (SI_Long)1L;
		temp_2 = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
			(SI_Long)8L));
		SET_ISCHAR(jis_string,base_index,ICHAR_CODE(temp_2));
		temp_3 = base_index + (SI_Long)1L;
		gensymed_symbol = jis_char_new_value & (SI_Long)255L;
		temp_2 = CODE_CHAR(FIX(gensymed_symbol));
		SET_ISCHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
	    }
	    else {
		base_index = jis_string_index << (SI_Long)1L;
		temp_2 = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
			(SI_Long)8L));
		SET_ICHAR(jis_string,base_index,ICHAR_CODE(temp_2));
		temp_3 = base_index + (SI_Long)1L;
		gensymed_symbol = jis_char_new_value & (SI_Long)255L;
		temp_2 = CODE_CHAR(FIX(gensymed_symbol));
		SET_ICHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
	    }
	}
	else {
	    gensymed_symbol = IFIX(wide_character);
	    if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		    (SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
		    (SI_Long)48L)) : TRUEP(Nil)) {
		jis_char_new_value = (SI_Long)9008L - (SI_Long)48L + 
			IFIX(wide_character);
		if (jis_string_is_simple_qm) {
		    base_index = jis_string_index << (SI_Long)1L;
		    temp_2 = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
			    (SI_Long)8L));
		    SET_ISCHAR(jis_string,base_index,ICHAR_CODE(temp_2));
		    temp_3 = base_index + (SI_Long)1L;
		    gensymed_symbol = jis_char_new_value & (SI_Long)255L;
		    temp_2 = CODE_CHAR(FIX(gensymed_symbol));
		    SET_ISCHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
		}
		else {
		    base_index = jis_string_index << (SI_Long)1L;
		    temp_2 = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
			    (SI_Long)8L));
		    SET_ICHAR(jis_string,base_index,ICHAR_CODE(temp_2));
		    temp_3 = base_index + (SI_Long)1L;
		    gensymed_symbol = jis_char_new_value & (SI_Long)255L;
		    temp_2 = CODE_CHAR(FIX(gensymed_symbol));
		    SET_ICHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
		}
	    }
	    else {
		arg = (SI_Long)31L;
		arg_1 = IFIX(wide_character);
		arg_2 = (SI_Long)127L;
		if (arg < arg_1 && arg_1 < arg_2) {
		    jis_string_1 = ISVREF(Ascii_to_jis_code_map,
			    IFIX(wide_character));
		    index_1 = (SI_Long)0L;
		    base_index = index_1 << (SI_Long)1L;
		    jis_char_new_value = 
			    (IFIX(CHAR_INT(CHR(ICHAR(jis_string_1,
			    base_index)))) << (SI_Long)8L) + 
			    IFIX(CHAR_INT(CHR(ICHAR(jis_string_1,
			    base_index + (SI_Long)1L))));
		    if (jis_string_is_simple_qm) {
			base_index = jis_string_index << (SI_Long)1L;
			temp_2 = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
				(SI_Long)8L));
			SET_ISCHAR(jis_string,base_index,ICHAR_CODE(temp_2));
			temp_3 = base_index + (SI_Long)1L;
			gensymed_symbol = jis_char_new_value & (SI_Long)255L;
			temp_2 = CODE_CHAR(FIX(gensymed_symbol));
			SET_ISCHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
		    }
		    else {
			base_index = jis_string_index << (SI_Long)1L;
			temp_2 = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
				(SI_Long)8L));
			SET_ICHAR(jis_string,base_index,ICHAR_CODE(temp_2));
			temp_3 = base_index + (SI_Long)1L;
			gensymed_symbol = jis_char_new_value & (SI_Long)255L;
			temp_2 = CODE_CHAR(FIX(gensymed_symbol));
			SET_ICHAR(jis_string,temp_3,ICHAR_CODE(temp_2));
		    }
		}
		else
		    goto end_loop_1;
	    }
	}
    }
    jis_string_index = jis_string_index + (SI_Long)1L;
    goto next_loop;
  end_loop_1:
    reclaim_gensym_string(jis_string);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

void kfep2_INIT()
{
    Object list_constant_1, AB_package, Qinitialize_for_asian_languages;
    Object Qkfep2, string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, Qascii_to_jis_code_map;
    Object Qout_jis_map_hash_vector_307_vectors;
    Object Qjis_map_hash_vector_307_vector_memory_usage, string_constant_47;
    Object Qutilities2, Qkfep3, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object Qascii_and_kana_suffix_pairs, list_constant;

    x_note_fn_call(121,26);
    SET_PACKAGE("AB");
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)45L),
	    FIX((SI_Long)39L));
    Allowable_non_alpha_characters_in_kfep_conversions = list_constant;
    AB_package = STATIC_PACKAGE("AB");
    Qascii_and_kana_suffix_pairs = 
	    STATIC_SYMBOL("ASCII-AND-KANA-SUFFIX-PAIRS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qascii_and_kana_suffix_pairs,
	    Ascii_and_kana_suffix_pairs);
    string_constant_6 = 
	    STATIC_STRING("133Gy2l5lA5l\"2l5mBA5lP2l5mDA5l@2l5mFA5mU!2l5mGA5l,2l5mHA5lO2l5mJA5m8c2l5mKA5l+2l5mLA5li2l5mMA5l^2l5mNA5lJ2l5mPA5lQ2l5mQA5m/!2l5m");
    string_constant_7 = 
	    STATIC_STRING("RA5li2l5mSA5l52l5mTA5l\?2l5mVA5n~t!2l5mWA5lo2l5mXA5l!2l5mYA5ld2l5mZA5l62l5mMY83Gfy2l5nBBA5mCP2l5nDDA5mC@2l5nFFA5nCU!2l5nGGA5mC,2l");
    string_constant_8 = 
	    STATIC_STRING("5nCHA5mAc2l5nDHA5mGc2l5nHHA5mCO2l5nSHA5m7c2l5nTHA5mFc2l5nJJA5nC8c2l5nKKA5mC+2l5nXKA5m~u2l5nLLA5mCi2l5nMMA5ms^2l5nNNA5msJ2l5nPPA5");
    string_constant_9 = 
	    STATIC_STRING("mCQ2l5nQQA5nC/!2l5nRRA5mCi2l5nSSA5mC52l5nTSA5mD!2l5nTTA5mC\?2l5nVVA5oC~t!2l5nGWA5m0n2l5nKWA5m/n2l5nWWA5mCo2l5nXWA5ln2l5nBYA5mSc2l");
    string_constant_10 = 
	    STATIC_STRING("5nCYA5mAc2l5nDYA5mBc2l5nFYA5mUc2l5nGYA5m.c2l5nHYA5mRc2l5nJYA5m8c2l5nKYA5m-c2l5nLYA5mjc2l5nMYA5m_c2l5nNYA5mKc2l5nPYA5mTc2l5nQYA5m");
    string_constant_11 = 
	    STATIC_STRING("/c2l5nRYA5mjc2l5nSYA5m7c2l5nTYA5mAc2l5nXYA5lc2l5nYYA5mCd2l5nZYA5m8c2l5nZZA5mC62l5oCCHA5nCAc2l5oTCHA5nCAc2l5oDDHA5nCGc2l5oSSHA5nC");
    string_constant_12 = 
	    STATIC_STRING("7c2l5oTTHA5nCFc2l5oTTSA5nCD!2l5oGGWA5nC0n2l5oKKWA5nC/n2l5oBBYA5nCSc2l5oCCYA5nCAc2l5oDDYA5nCBc2l5oFFYA5nCUc2l5oGGYA5nC.c2l5oHHYA5");
    string_constant_13 = 
	    STATIC_STRING("nCRc2l5oJJYA5nC8c2l5oKKYA5nC-c2l5oLLYA5nCjc2l5oMMYA5ns_c2l5oNNYA5nsKc2l5oPPYA5nCTc2l5oQQYA5nC/c2l5oRRYA5nCjc2l5oSSYA5nC7c2l5oTTY");
    string_constant_14 = 
	    STATIC_STRING("A5nCAc2l5oZZYA5nC8c2l5lE5l(2l5mBE5lY2l5mDE5lG2l5mFE5mU\'2l5mGE5l22l5mHE5lX2l5mJE5m8\'2l5mKE5l12l5mLE5ll2l5mME5la2l5mNE5lM2l5mPE5lZ");
    string_constant_15 = 
	    STATIC_STRING("2l5mQE5m/\'2l5mRE5ll2l5mSE5l;2l5mTE5lF2l5mVE5n~t\'2l5mWE5lq2l5mXE5l\'2l5mYE5l(2l5mZE5l<2l5nBBE5mCY2l5nDDE5mCG2l5nFFE5nCU\'2l5nGGE5mC");
    string_constant_16 = 
	    STATIC_STRING("22l5nCHE5mA\'2l5nDHE5mG\'2l5nHHE5mCX2l5nSHE5m7\'2l5nTHE5mF\'2l5nJJE5nC8\'2l5nKKE5mC12l5nXKE5m~v2l5nLLE5mCl2l5nMME5msa2l5nNNE5msM2l5nP");
    string_constant_17 = 
	    STATIC_STRING("PE5mCZ2l5nQQE5nC/\'2l5nRRE5mCl2l5nSSE5mC;2l5nTSE5mD\'2l5nTTE5mCF2l5nVVE5oC~t\'2l5nGWE5m0\'2l5nKWE5m/\'2l5nWWE5mCq2l5nBYE5mS\'2l5nCYE5m");
    string_constant_18 = 
	    STATIC_STRING("A\'2l5nDYE5mB\'2l5nFYE5mU\'2l5nGYE5m.\'2l5nHYE5mR\'2l5nJYE5m8\'2l5nKYE5m-\'2l5nLYE5mj\'2l5nMYE5m_\'2l5nNYE5mK\'2l5nPYE5mT\'2l5nQYE5m/\'2l5nR");
    string_constant_19 = 
	    STATIC_STRING("YE5mj\'2l5nSYE5m7\'2l5nTYE5mA\'2l5nXYE5l\'2l5nYYE5mC(2l5nZYE5m8\'2l5nZZE5mC<2l5oCCHE5nCA\'2l5oTCHE5nCA\'2l5oDDHE5nCG\'2l5oSSHE5nC7\'2l5oT");
    string_constant_20 = 
	    STATIC_STRING("THE5nCF\'2l5oTTSE5nCD\'2l5oGGWE5nC0\'2l5oKKWE5nC/\'2l5oBBYE5nCS\'2l5oCCYE5nCA\'2l5oDDYE5nCB\'2l5oFFYE5nCU\'2l5oGGYE5nC.\'2l5oHHYE5nCR\'2l5");
    string_constant_21 = 
	    STATIC_STRING("oJJYE5nC8\'2l5oKKYE5nC-\'2l5oLLYE5nCj\'2l5oMMYE5ns_\'2l5oNNYE5nsK\'2l5oPPYE5nCT\'2l5oQQYE5nC/\'2l5oRRYE5nCj\'2l5oSSYE5nC7\'2l5oTTYE5nCA\'2");
    string_constant_22 = 
	    STATIC_STRING("l5oZZYE5nC8\'2l5lI7l3Wy2l5mBI5lS2l5mDI5lB2l5mFI5mU#2l5mGI5l.2l5mHI5lR2l5mJI5l82l5mKI5l-2l5mLI5lj2l5mMI5l_2l5mNI5lK2l5mPI5lT2l5mQI");
    string_constant_23 = 
	    STATIC_STRING("5m/#2l5mRI5lj2l5mSI5l72l5mTI5lA2l5mVI5n~t#2l5mWI5lp2l5mXI5l#2l5mYI7l3Wy2l5mZI5l82l5nBBI5mCS2l5nDDI5mCB2l5nFFI5nCU#2l5nGGI5mC.2l5");
    string_constant_24 = 
	    STATIC_STRING("nCHI5lA2l5nDHI5mG#2l5nHHI5mCR2l5nSHI5l72l5nTHI5mF#2l5nJJI5mC82l5nKKI5mC-2l5nLLI5mCj2l5nMMI5ms_2l5nNNI5msK2l5nPPI5mCT2l5nQQI5nC/#");
    string_constant_25 = 
	    STATIC_STRING("2l5nRRI5mCj2l5nSSI5mC72l5nTSI5mD#2l5nTTI5mCA2l5nVVI5oC~t#2l5nGWI5m0#2l5nKWI5m/#2l5nWWI5mCp2l5nBYI5mS#2l5nCYI5mA#2l5nDYI5mB#2l5nF");
    string_constant_26 = 
	    STATIC_STRING("YI5mU#2l5nGYI5m.#2l5nHYI5mR#2l5nJYI5m8#2l5nKYI5m-#2l5nLYI5mj#2l5nMYI5m_#2l5nNYI5mK#2l5nPYI5mT#2l5nQYI5m/#2l5nRYI5mj#2l5nSYI5m7#2");
    string_constant_27 = 
	    STATIC_STRING("l5nTYI5mA#2l5nXYI5l#2l5nYYI7m3-=y3Wy2l5nZYI5m8#2l5nZZI5mC82l5oCCHI5mCA2l5oTCHI5mCA2l5oDDHI5nCG#2l5oSSHI5mC72l5oTTHI5nCF#2l5oTTSI");
    string_constant_28 = 
	    STATIC_STRING("5nCD#2l5oGGWI5nC0#2l5oKKWI5nC/#2l5oBBYI5nCS#2l5oCCYI5nCA#2l5oDDYI5nCB#2l5oFFYI5nCU#2l5oGGYI5nC.#2l5oHHYI5nCR#2l5oJJYI5nC8#2l5oKK");
    string_constant_29 = 
	    STATIC_STRING("YI5nC-#2l5oLLYI5nCj#2l5oMMYI5ns_#2l5oNNYI5nsK#2l5oPPYI5nCT#2l5oQQYI5nC/#2l5oRRYI5nCj#2l5oSSYI5nC7#2l5oTTYI5nCA#2l5oZZYI5nC8#2l5l");
    string_constant_30 = 
	    STATIC_STRING("O5l*2l5mBO5l\\2l5mDO5lI2l5mFO5mU)2l5mGO5l42l5mHO5l[2l5mJO5m8g2l5mKO5l32l5mLO5lm2l5mMO5lb2l5mNO5lN2l5mPO5l]2l5mQO5m/)2l5mRO5lm2l5m");
    string_constant_31 = 
	    STATIC_STRING("SO5l=2l5mTO5lH2l5mVO5n~t)2l5mWO5lr2l5mXO5l)2l5mYO5lh2l5mZO5l>2l5nBBO5mC\\2l5nDDO5mCI2l5nFFO5nCU)2l5nGGO5mC42l5nCHO5mAg2l5nDHO5mGg");
    string_constant_32 = 
	    STATIC_STRING("2l5nHHO5mC[2l5nSHO5m7g2l5nTHO5mFg2l5nJJO5nC8g2l5nKKO5mC32l5nLLO5mCm2l5nMMO5msb2l5nNNO5msN2l5nPPO5mC]2l5nQQO5nC/)2l5nRRO5mCm2l5nS");
    string_constant_33 = 
	    STATIC_STRING("SO5mC=2l5nTSO5mD)2l5nTTO5mCH2l5nVVO5oC~t)2l5nGWO5m0)2l5nKWO5m/)2l5nWWO5mCr2l5nBYO5mSg2l5nCYO5mAg2l5nDYO5mBg2l5nFYO5mUg2l5nGYO5m.");
    string_constant_34 = 
	    STATIC_STRING("g2l5nHYO5mRg2l5nJYO5m8g2l5nKYO5m-g2l5nLYO5mjg2l5nMYO5m_g2l5nNYO5mKg2l5nPYO5mTg2l5nQYO5m/g2l5nRYO5mjg2l5nSYO5m7g2l5nTYO5mAg2l5nXY");
    string_constant_35 = 
	    STATIC_STRING("O5lg2l5nYYO5mCh2l5nZYO5m8g2l5nZZO5mC>2l5oCCHO5nCAg2l5oTCHO5nCAg2l5oDDHO5nCGg2l5oSSHO5nC7)2l5oTTHO5nCFg2l5oTTSO5nCD)2l5oGGWO5nC0)");
    string_constant_36 = 
	    STATIC_STRING("2l5oKKWO5nC/)2l5oBBYO5nCSg2l5oCCYO5nCAg2l5oDDYO5nCBg2l5oFFYO5nCUg2l5oGGYO5nC.g2l5oHHYO5nCRg2l5oJJYO5nC8g2l5oKKYO5nC-g2l5oLLYO5nC");
    string_constant_37 = 
	    STATIC_STRING("jg2l5oMMYO5ns_g2l5oNNYO5nsKg2l5oPPYO5nCTg2l5oQQYO5nC/g2l5oRRYO5nCjg2l5oSSYO5nC7g2l5oTTYO5nCAg2l5oZZYO5nC8g2l5lU5l&2l5mBU5lV2l5mD");
    string_constant_38 = 
	    STATIC_STRING("U5lE2l5mFU5lU2l5mGU5l02l5mHU5lU2l5mJU5m8e2l5mKU5l/2l5mLU5lk2l5mMU5l`2l5mNU5lL2l5mPU5lW2l5mQU5m/%2l5mRU5lk2l5mSU5l92l5mTU5lD2l5mV");
    string_constant_39 = 
	    STATIC_STRING("U5n~t%2l5mWU5l&2l5mXU5l%2l5mYU5lf2l5mZU5l:2l5nBBU5mCV2l5nDDU5mCE2l5nFFU5mCU2l5nGGU5mC02l5nCHU5mAe2l5nDHU5mGe2l5nHHU5mCU2l5nSHU5m");
    string_constant_40 = 
	    STATIC_STRING("7e2l5nTHU5mFe2l5nJJU5nC8e2l5nKKU5mC/2l5nLLU5mCk2l5nMMU5ms`2l5nNNU5msL2l5nPPU5mCW2l5nQQU5nC/%2l5nRRU5mCk2l5nSSU5mC92l5nTSU5lD2l5n");
    string_constant_41 = 
	    STATIC_STRING("TTU5mCD2l5nXTU5lC2l5nVVU5oC~t%2l5nGWU5l02l5nKWU5l/2l5nWWU5mC&2l5nXWU5l%2l5nBYU5mSe2l5nCYU5mAe2l5nDYU5mBe2l5nFYU5mUe2l5nGYU5m.e2l");
    string_constant_42 = 
	    STATIC_STRING("5nHYU5mRe2l5nJYU5m8e2l5nKYU5m-e2l5nLYU5mje2l5nMYU5m_e2l5nNYU5mKe2l5nPYU5mTe2l5nQYU5m/e2l5nRYU5mje2l5nSYU5m7e2l5nTYU5mAe2l5nXYU5l");
    string_constant_43 = 
	    STATIC_STRING("e2l5nYYU5mCf2l5nZYU5m8e2l5nZZU5mC:2l5oCCHU5nCAe2l5oTCHU5nCAe2l5oDDHU5nCGe2l5oSSHU5nC7e2l5oTTHU5nCFe2l5oTTSU5mCD2l5oXTSU5lC2l5oGG");
    string_constant_44 = 
	    STATIC_STRING("WU5mC02l5oKKWU5mC/2l5oBBYU5nCSe2l5oCCYU5nCAe2l5oDDYU5nCBe2l5oFFYU5nCUe2l5oGGYU5nC.e2l5oHHYU5nCRe2l5oJJYU5nC8e2l5oKKYU5nC-e2l5oLL");
    string_constant_45 = 
	    STATIC_STRING("YU5nCje2l5oMMYU5ns_e2l5oNNYU5nsKe2l5oPPYU5nCTe2l5oQQYU5nC/e2l5oRRYU5nCje2l5oSSYU5nC7e2l5oTTYU5nCAe2l5oZZYU5nC8e2l5lN5ls2l5nN\'A5m");
    string_constant_46 = 
	    STATIC_STRING("s\"2l5nN\'I7m3-ly3Wy2l5nN\'U5ms&2l5nN\'E5ms(2l5nN\'O5ms*2l5mCA5l+2l5mCI5l72l5mCU5l/2l5mCE5l;2l5mCO5l3");
    SET_SYMBOL_VALUE(Qascii_and_kana_suffix_pairs,
	    regenerate_optimized_constant(list(41,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25,string_constant_26,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31,string_constant_32,string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46)));
    Qascii_to_kana_map = STATIC_SYMBOL("ASCII-TO-KANA-MAP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qascii_to_kana_map,Ascii_to_kana_map);
    Qkfep2 = STATIC_SYMBOL("KFEP2",AB_package);
    record_system_variable(Qascii_to_kana_map,Qkfep2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qmaximum_length_of_ascii_string = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-OF-ASCII-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_length_of_ascii_string,
	    Maximum_length_of_ascii_string);
    Qkfep3 = STATIC_SYMBOL("KFEP3",AB_package);
    record_system_variable(Qmaximum_length_of_ascii_string,Qkfep3,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qkana_to_ascii_map = STATIC_SYMBOL("KANA-TO-ASCII-MAP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkana_to_ascii_map,Kana_to_ascii_map);
    record_system_variable(Qkana_to_ascii_map,Qkfep2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qmaximum_length_of_kana_string = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-OF-KANA-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_length_of_kana_string,
	    Maximum_length_of_kana_string);
    record_system_variable(Qmaximum_length_of_kana_string,Qkfep2,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qavailable_jis_map_hash_vector_307_vectors = 
	    STATIC_SYMBOL("AVAILABLE-JIS-MAP-HASH-VECTOR-307-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_jis_map_hash_vector_307_vectors,
	    Available_jis_map_hash_vector_307_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_jis_map_hash_vector_307_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_jis_map_hash_vector_307_vectors = 
	    STATIC_SYMBOL("COUNT-OF-JIS-MAP-HASH-VECTOR-307-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_jis_map_hash_vector_307_vectors,
	    Count_of_jis_map_hash_vector_307_vectors);
    record_system_variable(Qcount_of_jis_map_hash_vector_307_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_jis_map_hash_vector_307_vectors_vector == UNBOUND)
	Available_jis_map_hash_vector_307_vectors_vector = 
		make_thread_array(Nil);
    Qout_jis_map_hash_vector_307_vectors = 
	    STATIC_SYMBOL("OUT-JIS-MAP-HASH-VECTOR-307-VECTORS",AB_package);
    Qjis_map_hash_vector_307_vector_memory_usage = 
	    STATIC_SYMBOL("JIS-MAP-HASH-VECTOR-307-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_47 = STATIC_STRING("1q83-bay83*9y83-P*y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_jis_map_hash_vector_307_vectors);
    push_optimized_constant(Qjis_map_hash_vector_307_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_47));
    SET_SYMBOL_FUNCTION(Qjis_map_hash_vector_307_vector_memory_usage,
	    STATIC_FUNCTION(jis_map_hash_vector_307_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_jis_map_hash_vector_307_vectors,
	    STATIC_FUNCTION(out_jis_map_hash_vector_307_vectors,NIL,FALSE,
	    0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qjis_map_tree_for_hash = STATIC_SYMBOL("JIS-MAP-TREE-FOR-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qascii_to_jis_code_map = STATIC_SYMBOL("ASCII-TO-JIS-CODE-MAP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qascii_to_jis_code_map,Ascii_to_jis_code_map);
    string_constant_48 = 
	    STATIC_STRING("43*+y5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5k5m!!5m!*5m!m5m!t5m!p5m!s5m!u5m!l5m!J5m!K5m\"(5m!&7m3Ty3Wy5m!");
    string_constant_49 = 
	    STATIC_STRING("<5m!#5m!\?5m#05m#15m#25m#35m#45m#55m#65m#75m#85m#95m!\'5m!\"5m!c5m\"/5m!d5m!)5m!}5m#A5m#B5m#C5m#D5m#E5m#F5m#G5m#H5m#I5m#J5m#K5m#L5m#");
    string_constant_50 = 
	    STATIC_STRING("M5m#N5m#O5m#P5m#Q5m#R5m#S5m#T5m#U5m#V5m#W5m#X5m#Y5m#Z5m!V5m!@5m!W5m!05m!25m!F5m#a5m#b5m#c5m#d5m#e5m#f5m#g5m#h5m#i5m#j5m#k5m#l5m#");
    string_constant_51 = 
	    STATIC_STRING("m5m#n5m#o5m#p5m#q5m#r5m#s5m#t5m#u5m#v5m#w5m#x5m#y5m#z5m!P5m!C5m!Q5m!A5k");
    SET_SYMBOL_VALUE(Qascii_to_jis_code_map,
	    regenerate_optimized_constant(LIST_4(string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51)));
    Qascii = STATIC_SYMBOL("ASCII",AB_package);
    Qlast_roman_kana_g2_length = STATIC_SYMBOL("LAST-ROMAN_KANA_G2-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_roman_kana_g2_length,
	    Last_roman_kana_g2_length);
    record_system_variable(Qlast_roman_kana_g2_length,Qkfep2,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qlast_roman_kata_g2_length = STATIC_SYMBOL("LAST-ROMAN_KATA_G2-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_roman_kata_g2_length,
	    Last_roman_kata_g2_length);
    record_system_variable(Qlast_roman_kata_g2_length,Qkfep2,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qkfep_converters_have_been_initialized_qm = 
	    STATIC_SYMBOL("KFEP-CONVERTERS-HAVE-BEEN-INITIALIZED\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_converters_have_been_initialized_qm,
	    Kfep_converters_have_been_initialized_qm);
    record_system_variable(Qkfep_converters_have_been_initialized_qm,
	    Qkfep2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qinitialize_for_asian_languages = 
	    STATIC_SYMBOL("INITIALIZE-FOR-ASIAN-LANGUAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_asian_languages,
	    STATIC_FUNCTION(initialize_for_asian_languages,NIL,FALSE,0,0));
    string_constant = STATIC_STRING("~a~%Please wait . . . ");
    string_constant_1 = STATIC_STRING("Initializing Korean outline font ...");
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    string_constant_2 = STATIC_STRING("Initializing Chinese outline font ...");
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qkfep_filename = STATIC_SYMBOL("KFEP-FILENAME",AB_package);
    string_constant_3 = 
	    STATIC_STRING("Initializing KFEP dictionaries from ~s, ~s, and ~s.");
    string_constant_4 = 
	    STATIC_STRING("The KFEP dictionaries have been initialized from ~s, ~s, and ~s.");
    string_constant_5 = 
	    STATIC_STRING("Some of the KFEP dictionary files ~s, ~s, or ~s could not be accessed.");
    Qspecified_kfep_index_filename_qm = 
	    STATIC_SYMBOL("SPECIFIED-KFEP-INDEX-FILENAME\?",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qspecified_kfep_main_filename_qm = 
	    STATIC_SYMBOL("SPECIFIED-KFEP-MAIN-FILENAME\?",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qspecified_kfep_kojin_filename_qm = 
	    STATIC_SYMBOL("SPECIFIED-KFEP-KOJIN-FILENAME\?",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
}
