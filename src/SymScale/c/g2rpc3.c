/* g2rpc3.c
 * Input file:  g2-rpc3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2rpc3.h"


static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qvariable_or_parameter_stored_histories_qm;  /* variable-or-parameter-stored-histories? */

static Object Qhistory_object_sent_to_non_history_attribute;  /* history-object-sent-to-non-history-attribute */

static Object Qhistory_object_sent_to_non_history_class_definition;  /* history-object-sent-to-non-history-class-definition */

/* G2-RECEIVE-ADD-ATTRIBUTE-HISTORY-OBJECT */
Object g2_receive_add_attribute_history_object(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,element_type,resumable_history_length,
	    timestamps_use_float_array_p,values_use_float_array_p,
	    datapoint_count_qm,datapoint_age_qm,granularity_qm,base_time,
	    lowest_ever,highest_ever,time_at_start_qm)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type;
    Object resumable_history_length, timestamps_use_float_array_p;
    Object values_use_float_array_p, datapoint_count_qm, datapoint_age_qm;
    Object granularity_qm, base_time, lowest_ever, highest_ever;
    Object time_at_start_qm;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object new_history_object_qm, x2, remote_time_at_start_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(168,0);
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
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_4 = (SI_Long)1L;
	    gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	    temp_2 = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_history_object_qm = g2_build_remote_object(attribute_type,
		attribute_qualifier_qm,attribute_name_or_index,class_name);
	if (SIMPLE_VECTOR_P(new_history_object_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_history_object_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(new_history_object_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(new_history_object_qm,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    sub_class_bit_vector = ISVREF(ISVREF(new_history_object_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_or_parameter_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		temp_2 = (SI_Long)0L < gensymed_symbol_3;
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    if (datapoint_count_qm || datapoint_age_qm || granularity_qm) {
		add_history_spec_for_object_passing(new_history_object_qm,
			datapoint_count_qm,datapoint_age_qm,granularity_qm);
		change_slot_value_for_object_passing(new_history_object_qm,
			Qvariable_or_parameter_stored_histories_qm,
			make_cascaded_ring_buffer_for_history_object_passing(resumable_history_length,
			timestamps_use_float_array_p,
			values_use_float_array_p,datapoint_count_qm,
			datapoint_age_qm,base_time,lowest_ever,highest_ever));
		remote_time_at_start_qm = 
			ISVREF(Current_receiving_resumable_object,
			(SI_Long)14L);
		if (remote_time_at_start_qm) {
		    if (time_at_start_qm)
			reclaim_managed_simple_float_array_of_length_1(time_at_start_qm);
		}
		else {
		    svref_arg_1 = Current_receiving_resumable_object;
		    SVREF(svref_arg_1,FIX((SI_Long)14L)) = time_at_start_qm;
		}
	    }
	}
	else
	    record_object_building_problem_on_receiving_side_1(Qhistory_object_sent_to_non_history_attribute,
		    Nil,Nil,class_name,Nil,Nil,Nil);
    }
    else
	record_object_building_problem_on_receiving_side_1(Qhistory_object_sent_to_non_history_class_definition,
		Nil,Nil,class_name,Nil,Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qvariable_or_parameter_history_specification_qm;  /* variable-or-parameter-history-specification? */

static Object Qhistory;            /* history */

/* ADD-HISTORY-SPEC-FOR-OBJECT-PASSING */
Object add_history_spec_for_object_passing(new_history_object,
	    datapoint_count,datapoint_age,granularity)
    Object new_history_object, datapoint_count, datapoint_age, granularity;
{
    x_note_fn_call(168,1);
    change_slot_value_for_object_passing(new_history_object,
	    Qvariable_or_parameter_history_specification_qm,
	    slot_value_list_4(Qhistory,datapoint_count,datapoint_age,
	    granularity));
    return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* GET-FOLLOWING-HISTORY-TIMESTAMP */
Object get_following_history_timestamp(history,timestamp_vector,
	    base_ring_index,delta)
    Object history, timestamp_vector, base_ring_index, delta;
{
    Object size, raw_index, first_uncached_index, managed_number_or_value;
    Object first_uncached_timestamp, amf_available_array_cons_qm, amf_array;
    Object temp, temp_1, amf_result, new_float, managed_timestamp;
    double aref_new_value;

    x_note_fn_call(168,2);
    size = ISVREF(history,(SI_Long)4L);
    raw_index = FIXNUM_ADD(base_ring_index,delta);
    first_uncached_index = FIXNUM_GE(raw_index,size) ? 
	    FIXNUM_MINUS(raw_index,size) : raw_index;
    if (SIMPLE_VECTOR_P(timestamp_vector) && EQ(ISVREF(timestamp_vector,
	    (SI_Long)0L),Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(timestamp_vector,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(timestamp_vector,
		IFIX(FIXNUM_ADD(first_uncached_index,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(timestamp_vector,(IFIX(first_uncached_index) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(first_uncached_index) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    first_uncached_timestamp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    first_uncached_timestamp = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    first_uncached_timestamp = 
		    copy_text_string(managed_number_or_value);
	else
	    first_uncached_timestamp = managed_number_or_value;
    }
    else
	first_uncached_timestamp = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
		(IFIX(first_uncached_index) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(first_uncached_index) & (SI_Long)1023L));
    if (FLOATP(first_uncached_timestamp)) {
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(first_uncached_timestamp);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	managed_timestamp = new_float;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(first_uncached_timestamp) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(first_uncached_timestamp)) == 
	    (SI_Long)1L)
	managed_timestamp = copy_managed_float(first_uncached_timestamp);
    else if (FIXNUMP(first_uncached_timestamp)) {
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
	aref_new_value = (double)IFIX(first_uncached_timestamp);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	managed_timestamp = new_float;
    }
    else
	managed_timestamp = Qnil;
    return VALUES_2(first_uncached_index,managed_timestamp);
}

static Object Qiterate_over_history;  /* iterate-over-history */

/* COPY-NUMERIC-HISTORY-STATE-INTO-RESUMABLE-HISTORY-NODE */
Object copy_numeric_history_state_into_resumable_history_node(history_node,
	    history,history_length,float_vector_for_timestamps_p,
	    timestamp_vector,float_vector_for_values_p)
    Object history_node, history, history_length;
    Object float_vector_for_timestamps_p, timestamp_vector;
    Object float_vector_for_values_p;
{
    Object oldest_element_index, cached_timestamp_subsequence;
    Object cached_value_subsequence, cache_index, previous_timestamp_qm;
    volatile Object identical_timestamp_count;
    Object value_history_ring_buffer_or_cascade, tag_temp;
    Object oldest_active_element_index, newest_active_element_index;
    Object history_value, history_collection_time, points_read, element_index;
    Object initial_element_index_qm, vector_1, managed_number_or_value, temp;
    Object temp_1, temp_2, amf_available_array_cons_qm, amf_array, temp_5;
    Object amf_result, new_float, first_uncached_index, managed_timestamp;
    SI_Long aref_arg_2, temp_4;
    char temp_3;
    double aref_new_value, arg, arg_1;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(168,3);
    ISVREF(history_node,(SI_Long)28L) = FIX((SI_Long)0L);
    SVREF(history_node,FIX((SI_Long)20L)) = history;
    oldest_element_index = ISVREF(history,(SI_Long)2L);
    cached_timestamp_subsequence = float_vector_for_timestamps_p ? 
	    allocate_managed_float_array(1,
	    Size_of_cached_subsequence_for_resumable_history) : 
	    allocate_managed_simple_vector(Size_of_cached_subsequence_for_resumable_history);
    cached_value_subsequence = float_vector_for_values_p ? 
	    allocate_managed_float_array(1,
	    Size_of_cached_subsequence_for_resumable_history) : 
	    allocate_managed_simple_vector(Size_of_cached_subsequence_for_resumable_history);
    cache_index = FIX((SI_Long)0L);
    previous_timestamp_qm = Nil;
    identical_timestamp_count = FIX((SI_Long)0L);
    value_history_ring_buffer_or_cascade = history;
    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
	    0);
      SVREF(history_node,FIX((SI_Long)23L)) = oldest_element_index;
      SVREF(history_node,FIX((SI_Long)29L)) = cached_timestamp_subsequence;
      SVREF(history_node,FIX((SI_Long)30L)) = cached_value_subsequence;
      if (float_vector_for_timestamps_p && float_vector_for_values_p) {
	  tag_temp = UNIQUE_TAG(Qiterate_over_history);
	  if (PUSH_CATCH(tag_temp,0)) {
	      oldest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	      newest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	      history_value = Nil;
	      history_collection_time = Nil;
	      points_read = FIX((SI_Long)0L);
	      element_index = oldest_active_element_index;
	      initial_element_index_qm = T;
	    next_loop:
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		next_loop_1:
		  if (initial_element_index_qm)
		      initial_element_index_qm = Nil;
		  else
		      element_index = FIXNUM_EQ(element_index,
			      FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			      FIXNUM_ADD1(element_index);
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)6L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp = copy_text_string(managed_number_or_value);
		      else
			  temp = managed_number_or_value;
		  }
		  else
		      temp = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)7L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp_1 = copy_text_string(managed_number_or_value);
		      else
			  temp_1 = managed_number_or_value;
		  }
		  else
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  history_value = temp;
		  history_collection_time = temp_1;
		  points_read = FIXNUM_ADD1(points_read);
		  temp_2 = ISVREF(cached_timestamp_subsequence,
			  (IFIX(cache_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L);
		  aref_arg_2 = IFIX(cache_index) & (SI_Long)1023L;
		  aref_new_value = 
			  DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
		  DFLOAT_ISASET_1(temp_2,aref_arg_2,aref_new_value);
		  temp_2 = ISVREF(cached_value_subsequence,
			  (IFIX(cache_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L);
		  aref_arg_2 = IFIX(cache_index) & (SI_Long)1023L;
		  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(history_value);
		  DFLOAT_ISASET_1(temp_2,aref_arg_2,aref_new_value);
		  if (Previous_timestamp_qm) {
		      arg = DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
		      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
		      temp_3 = arg == arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  if (temp_3)
		      identical_timestamp_count = 
			      FIXNUM_ADD1(identical_timestamp_count);
		  else
		      identical_timestamp_count = FIX((SI_Long)0L);
		  Previous_timestamp_qm = history_collection_time;
		  cache_index = FIXNUM_ADD1(cache_index);
		  if (FIXNUM_GE(cache_index,
			  Size_of_cached_subsequence_for_resumable_history)) {
		      result = VALUES_1(Nil);
		      THROW(tag_temp,result);
		  }
		  temp_3 = FIXNUM_EQ(element_index,
			  newest_active_element_index);
		  if (temp_3);
		  else {
		      temp_4 = IFIX(points_read) % (SI_Long)500L;
		      temp_3 = temp_4 == (SI_Long)0L;
		  }
		  if (temp_3)
		      goto end_loop;
		  goto next_loop_1;
		end_loop:;
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	      if (FIXNUM_EQ(element_index,newest_active_element_index))
		  goto end_loop_1;
	      goto next_loop;
	    end_loop_1:;
	  }
	  POP_CATCH(0);
      }
      else if (float_vector_for_timestamps_p) {
	  tag_temp = UNIQUE_TAG(Qiterate_over_history);
	  if (PUSH_CATCH(tag_temp,0)) {
	      oldest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	      newest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	      history_value = Nil;
	      history_collection_time = Nil;
	      points_read = FIX((SI_Long)0L);
	      element_index = oldest_active_element_index;
	      initial_element_index_qm = T;
	    next_loop_2:
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		next_loop_3:
		  if (initial_element_index_qm)
		      initial_element_index_qm = Nil;
		  else
		      element_index = FIXNUM_EQ(element_index,
			      FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			      FIXNUM_ADD1(element_index);
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)6L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp = copy_text_string(managed_number_or_value);
		      else
			  temp = managed_number_or_value;
		  }
		  else
		      temp = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)7L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp_1 = copy_text_string(managed_number_or_value);
		      else
			  temp_1 = managed_number_or_value;
		  }
		  else
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  history_value = temp;
		  history_collection_time = temp_1;
		  points_read = FIXNUM_ADD1(points_read);
		  temp_2 = ISVREF(cached_timestamp_subsequence,
			  (IFIX(cache_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L);
		  aref_arg_2 = IFIX(cache_index) & (SI_Long)1023L;
		  aref_new_value = 
			  DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
		  DFLOAT_ISASET_1(temp_2,aref_arg_2,aref_new_value);
		  if (FLOATP(history_value)) {
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_2 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_2,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_2 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_2) = amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_2 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
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
		      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(history_value);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  }
		  else
		      new_float = FIXNUMP(history_value) || history_value 
			      && SYMBOLP(history_value) ? history_value : 
			      copy_evaluation_value_1(history_value);
		  SVREF(cached_value_subsequence,cache_index) = new_float;
		  if (Previous_timestamp_qm) {
		      arg = DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
		      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
		      temp_3 = arg == arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  if (temp_3)
		      identical_timestamp_count = 
			      FIXNUM_ADD1(identical_timestamp_count);
		  else
		      identical_timestamp_count = FIX((SI_Long)0L);
		  Previous_timestamp_qm = history_collection_time;
		  cache_index = FIXNUM_ADD1(cache_index);
		  if (FIXNUM_GE(cache_index,
			  Size_of_cached_subsequence_for_resumable_history)) {
		      result = VALUES_1(Nil);
		      THROW(tag_temp,result);
		  }
		  temp_3 = FIXNUM_EQ(element_index,
			  newest_active_element_index);
		  if (temp_3);
		  else {
		      temp_4 = IFIX(points_read) % (SI_Long)500L;
		      temp_3 = temp_4 == (SI_Long)0L;
		  }
		  if (temp_3)
		      goto end_loop_2;
		  goto next_loop_3;
		end_loop_2:;
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	      if (FIXNUM_EQ(element_index,newest_active_element_index))
		  goto end_loop_3;
	      goto next_loop_2;
	    end_loop_3:;
	  }
	  POP_CATCH(0);
      }
      else if (float_vector_for_values_p) {
	  tag_temp = UNIQUE_TAG(Qiterate_over_history);
	  if (PUSH_CATCH(tag_temp,0)) {
	      oldest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	      newest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	      history_value = Nil;
	      history_collection_time = Nil;
	      points_read = FIX((SI_Long)0L);
	      element_index = oldest_active_element_index;
	      initial_element_index_qm = T;
	    next_loop_4:
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		next_loop_5:
		  if (initial_element_index_qm)
		      initial_element_index_qm = Nil;
		  else
		      element_index = FIXNUM_EQ(element_index,
			      FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			      FIXNUM_ADD1(element_index);
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)6L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp = copy_text_string(managed_number_or_value);
		      else
			  temp = managed_number_or_value;
		  }
		  else
		      temp = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)7L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp_1 = copy_text_string(managed_number_or_value);
		      else
			  temp_1 = managed_number_or_value;
		  }
		  else
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  history_value = temp;
		  history_collection_time = temp_1;
		  points_read = FIXNUM_ADD1(points_read);
		  if (FLOATP(history_collection_time)) {
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_2 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_2,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_2 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_2) = amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_2 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
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
			      DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  }
		  else
		      new_float = FIXNUMP(history_collection_time) || 
			      history_collection_time && 
			      SYMBOLP(history_collection_time) ? 
			      history_collection_time : 
			      copy_evaluation_value_1(history_collection_time);
		  SVREF(cached_timestamp_subsequence,cache_index) = new_float;
		  temp_2 = ISVREF(cached_value_subsequence,
			  (IFIX(cache_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L);
		  aref_arg_2 = IFIX(cache_index) & (SI_Long)1023L;
		  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(history_value);
		  DFLOAT_ISASET_1(temp_2,aref_arg_2,aref_new_value);
		  if (Previous_timestamp_qm) {
		      if (FLOATP(history_collection_time) && 
			      FLOATP(Previous_timestamp_qm)) {
			  arg = DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			  arg_1 = 
				  DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
			  temp_3 = arg == arg_1 &&  
				  !inline_nanp_for_comparison(arg) ?  
				  !inline_nanp_for_comparison(arg_1) : 
				  TRUEP(Qnil);
		      }
		      else if (FLOATP(history_collection_time) || 
			      FLOATP(Previous_timestamp_qm))
			  temp_3 = TRUEP(Nil);
		      else
			  temp_3 = TRUEP(evaluation_value_eql(2,
				  Previous_timestamp_qm,
				  history_collection_time));
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  if (temp_3)
		      identical_timestamp_count = 
			      FIXNUM_ADD1(identical_timestamp_count);
		  else
		      identical_timestamp_count = FIX((SI_Long)0L);
		  Previous_timestamp_qm = history_collection_time;
		  cache_index = FIXNUM_ADD1(cache_index);
		  if (FIXNUM_GE(cache_index,
			  Size_of_cached_subsequence_for_resumable_history)) {
		      result = VALUES_1(Nil);
		      THROW(tag_temp,result);
		  }
		  temp_3 = FIXNUM_EQ(element_index,
			  newest_active_element_index);
		  if (temp_3);
		  else {
		      temp_4 = IFIX(points_read) % (SI_Long)500L;
		      temp_3 = temp_4 == (SI_Long)0L;
		  }
		  if (temp_3)
		      goto end_loop_4;
		  goto next_loop_5;
		end_loop_4:;
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	      if (FIXNUM_EQ(element_index,newest_active_element_index))
		  goto end_loop_5;
	      goto next_loop_4;
	    end_loop_5:;
	  }
	  POP_CATCH(0);
      }
      else {
	  tag_temp = UNIQUE_TAG(Qiterate_over_history);
	  if (PUSH_CATCH(tag_temp,0)) {
	      oldest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	      newest_active_element_index = 
		      ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	      history_value = Nil;
	      history_collection_time = Nil;
	      points_read = FIX((SI_Long)0L);
	      element_index = oldest_active_element_index;
	      initial_element_index_qm = T;
	    next_loop_6:
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		next_loop_7:
		  if (initial_element_index_qm)
		      initial_element_index_qm = Nil;
		  else
		      element_index = FIXNUM_EQ(element_index,
			      FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			      FIXNUM_ADD1(element_index);
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)6L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp = copy_text_string(managed_number_or_value);
		      else
			  temp = managed_number_or_value;
		  }
		  else
		      temp = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			  (SI_Long)7L);
		  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			  (SI_Long)0L),Managed_array_unique_marker)) {
		      managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(vector_1,
			      IFIX(FIXNUM_ADD(element_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(vector_1,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      IFIX(element_index) & (SI_Long)1023L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp_1 = copy_text_string(managed_number_or_value);
		      else
			  temp_1 = managed_number_or_value;
		  }
		  else
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L));
		  history_value = temp;
		  history_collection_time = temp_1;
		  points_read = FIXNUM_ADD1(points_read);
		  if (FLOATP(history_collection_time)) {
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_2 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_2,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_2 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_2) = amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_2 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
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
			      DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  }
		  else
		      new_float = FIXNUMP(history_collection_time) || 
			      history_collection_time && 
			      SYMBOLP(history_collection_time) ? 
			      history_collection_time : 
			      copy_evaluation_value_1(history_collection_time);
		  SVREF(cached_timestamp_subsequence,cache_index) = new_float;
		  if (FLOATP(history_value)) {
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_2 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_2,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_2 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_2) = amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_2 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_2 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_2,temp_5) = 
				      amf_available_array_cons_qm;
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
		      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(history_value);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  }
		  else
		      new_float = FIXNUMP(history_value) || history_value 
			      && SYMBOLP(history_value) ? history_value : 
			      copy_evaluation_value_1(history_value);
		  SVREF(cached_value_subsequence,cache_index) = new_float;
		  if (Previous_timestamp_qm) {
		      if (FLOATP(history_collection_time) && 
			      FLOATP(Previous_timestamp_qm)) {
			  arg = DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			  arg_1 = 
				  DOUBLE_FLOAT_TO_DOUBLE(history_collection_time);
			  temp_3 = arg == arg_1 &&  
				  !inline_nanp_for_comparison(arg) ?  
				  !inline_nanp_for_comparison(arg_1) : 
				  TRUEP(Qnil);
		      }
		      else if (FLOATP(history_collection_time) || 
			      FLOATP(Previous_timestamp_qm))
			  temp_3 = TRUEP(Nil);
		      else
			  temp_3 = TRUEP(evaluation_value_eql(2,
				  Previous_timestamp_qm,
				  history_collection_time));
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  if (temp_3)
		      identical_timestamp_count = 
			      FIXNUM_ADD1(identical_timestamp_count);
		  else
		      identical_timestamp_count = FIX((SI_Long)0L);
		  Previous_timestamp_qm = history_collection_time;
		  cache_index = FIXNUM_ADD1(cache_index);
		  if (FIXNUM_GE(cache_index,
			  Size_of_cached_subsequence_for_resumable_history)) {
		      result = VALUES_1(Nil);
		      THROW(tag_temp,result);
		  }
		  temp_3 = FIXNUM_EQ(element_index,
			  newest_active_element_index);
		  if (temp_3);
		  else {
		      temp_4 = IFIX(points_read) % (SI_Long)500L;
		      temp_3 = temp_4 == (SI_Long)0L;
		  }
		  if (temp_3)
		      goto end_loop_6;
		  goto next_loop_7;
		end_loop_6:;
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	      if (FIXNUM_EQ(element_index,newest_active_element_index))
		  goto end_loop_7;
	      goto next_loop_6;
	    end_loop_7:;
	  }
	  POP_CATCH(0);
      }
      SVREF(history_node,FIX((SI_Long)27L)) = identical_timestamp_count;
      if (FIXNUM_GT(history_length,
	      Size_of_cached_subsequence_for_resumable_history)) {
	  result = get_following_history_timestamp(history,
		  timestamp_vector,oldest_element_index,
		  Size_of_cached_subsequence_for_resumable_history);
	  MVS_2(result,first_uncached_index,managed_timestamp);
	  SVREF(history_node,FIX((SI_Long)24L)) = first_uncached_index;
	  SVREF(history_node,FIX((SI_Long)26L)) = managed_timestamp;
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* COPY-HISTORY-STATE-INTO-RESUMABLE-HISTORY-NODE */
Object copy_history_state_into_resumable_history_node(history_node,
	    history_enclosure_qm,history,history_spec)
    Object history_node, history_enclosure_qm, history, history_spec;
{
    Object svref_new_value, contents_qm, temp, temp_1, temp_2, ring_buffer;
    Object index_1, oldest_active_element_index_for_ring_buffer;
    Object timestamp_vector, float_vector_for_timestamps_p, thing;
    Object float_vector_for_values_p;
    SI_Long history_length;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(168,4);
    svref_new_value = copy_list_using_icp_conses_1(history_spec);
    SVREF(history_node,FIX((SI_Long)21L)) = svref_new_value;
    if (history_enclosure_qm) {
	contents_qm = ISVREF(history_enclosure_qm,(SI_Long)10L);
	temp = contents_qm ? (FIXNUMP(contents_qm) || contents_qm && 
		SYMBOLP(contents_qm) ? contents_qm : 
		copy_evaluation_value_1(contents_qm)) : Nil;
	contents_qm = ISVREF(history_enclosure_qm,(SI_Long)8L);
	temp_1 = contents_qm ? (FIXNUMP(contents_qm) || contents_qm && 
		SYMBOLP(contents_qm) ? contents_qm : 
		copy_evaluation_value_1(contents_qm)) : Nil;
	contents_qm = ISVREF(history_enclosure_qm,(SI_Long)7L);
	temp_2 = contents_qm ? (FIXNUMP(contents_qm) || contents_qm && 
		SYMBOLP(contents_qm) ? contents_qm : 
		copy_evaluation_value_1(contents_qm)) : Nil;
	svref_new_value = icp_list_4(temp,temp_1,temp_2,
		copy_managed_float(G2_time_at_start));
	SVREF(history_node,FIX((SI_Long)22L)) = svref_new_value;
    }
    else {
	svref_new_value = icp_list_4(Nil,Nil,Nil,Nil);
	SVREF(history_node,FIX((SI_Long)22L)) = svref_new_value;
    }
    ring_buffer = history;
    index_1 = ISVREF(history,(SI_Long)1L);
    oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
	    (SI_Long)2L);
    history_length = FIXNUM_GE(index_1,
	    oldest_active_element_index_for_ring_buffer) ? 
	    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
	    oldest_active_element_index_for_ring_buffer))) : 
	    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
	    ISVREF(ring_buffer,(SI_Long)4L)),
	    oldest_active_element_index_for_ring_buffer)));
    ISVREF(history_node,(SI_Long)18L) = FIX(history_length);
    if (history_length > (SI_Long)0L) {
	timestamp_vector = ISVREF(history,(SI_Long)7L);
	float_vector_for_timestamps_p = SIMPLE_VECTOR_P(timestamp_vector) ?
		 (EQ(ISVREF(timestamp_vector,(SI_Long)0L),
		Managed_float_array_unique_marker) ? T : Nil) : Qnil;
	thing = ISVREF(history,(SI_Long)6L);
	float_vector_for_values_p = SIMPLE_VECTOR_P(thing) ? 
		(EQ(ISVREF(thing,(SI_Long)0L),
		Managed_float_array_unique_marker) ? T : Nil) : Qnil;
	if (float_vector_for_timestamps_p || float_vector_for_values_p) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		copy_numeric_history_state_into_resumable_history_node(history_node,
			history,FIX(history_length),
			float_vector_for_timestamps_p,timestamp_vector,
			float_vector_for_values_p);
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else
	    copy_numeric_history_state_into_resumable_history_node(history_node,
		    history,FIX(history_length),
		    float_vector_for_timestamps_p,timestamp_vector,
		    float_vector_for_values_p);
    }
    return VALUES_1(Nil);
}

static Object float_constant;      /* 0.0 */

/* SAME-TIMESTAMP-AS */
Object same_timestamp_as(timestamp,managed_float_timestamp)
    Object timestamp, managed_float_timestamp;
{
    Object temp;
    double arg, arg_1;

    x_note_fn_call(168,5);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == (SI_Long)1L) {
	arg = DFLOAT_ISAREF_1(managed_float_timestamp,(SI_Long)0L);
	arg_1 = DFLOAT_ISAREF_1(timestamp,(SI_Long)0L);
	temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else if (FLOATP(timestamp)) {
	arg = DFLOAT_ISAREF_1(managed_float_timestamp,(SI_Long)0L);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
	temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else if (FIXNUMP(timestamp)) {
	arg = DFLOAT_ISAREF_1(managed_float_timestamp,(SI_Long)0L);
	temp = lfloat(timestamp,float_constant);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* LATER-TIMESTAMP-THAN */
Object later_timestamp_than(timestamp,managed_float_timestamp)
    Object timestamp, managed_float_timestamp;
{
    Object temp;
    double arg, arg_1;

    x_note_fn_call(168,6);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == (SI_Long)1L) {
	arg = DFLOAT_ISAREF_1(managed_float_timestamp,(SI_Long)0L);
	arg_1 = DFLOAT_ISAREF_1(timestamp,(SI_Long)0L);
	temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else if (FLOATP(timestamp)) {
	arg = DFLOAT_ISAREF_1(managed_float_timestamp,(SI_Long)0L);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
	temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else if (FIXNUMP(timestamp)) {
	arg = DFLOAT_ISAREF_1(managed_float_timestamp,(SI_Long)0L);
	temp = lfloat(timestamp,float_constant);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-INDEX-OF-TIMESTAMP-IF-ANY */
Object get_index_of_timestamp_if_any(timestamp,history)
    Object timestamp, history;
{
    Object lowest_possible_index, highest_possible_index, probe_offset;
    Object oldest_index, temp, size, raw_index, index_to_try, vector_1;
    Object managed_number_or_value, this_timestamp;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(168,7);
    lowest_possible_index = ISVREF(history,(SI_Long)2L);
    highest_possible_index = ISVREF(history,(SI_Long)1L);
    probe_offset = Nil;
  next_loop:
    oldest_index = ISVREF(history,(SI_Long)2L);
    if (FIXNUM_GE(lowest_possible_index,oldest_index) && 
	    FIXNUM_GE(highest_possible_index,oldest_index) || 
	    FIXNUM_LT(lowest_possible_index,oldest_index) && 
	    FIXNUM_LT(highest_possible_index,oldest_index))
	temp = FIXNUM_LT(lowest_possible_index,highest_possible_index) ? T 
		: Nil;
    else if (FIXNUM_GE(lowest_possible_index,oldest_index))
	temp = T;
    else
	temp = Nil;
    if ( !TRUEP(temp))
	goto end_loop;
    gensymed_symbol = FIXNUM_GE(highest_possible_index,
	    lowest_possible_index) ? 
	    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(highest_possible_index,
	    lowest_possible_index))) : 
	    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(highest_possible_index,
	    ISVREF(history,(SI_Long)4L)),lowest_possible_index)));
    gensymed_symbol_1 = (SI_Long)1L;
    probe_offset = FIX(gensymed_symbol >>  -  - gensymed_symbol_1);
    size = ISVREF(history,(SI_Long)4L);
    raw_index = FIXNUM_ADD(lowest_possible_index,probe_offset);
    index_to_try = FIXNUM_GE(raw_index,size) ? FIXNUM_MINUS(raw_index,
	    size) : raw_index;
    vector_1 = ISVREF(history,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(index_to_try,Managed_array_index_offset))) 
		: ISVREF(ISVREF(vector_1,(IFIX(index_to_try) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_to_try) & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    this_timestamp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    this_timestamp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    this_timestamp = copy_text_string(managed_number_or_value);
	else
	    this_timestamp = managed_number_or_value;
    }
    else
	this_timestamp = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(index_to_try) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(index_to_try) & (SI_Long)1023L));
    if (same_timestamp_as(this_timestamp,timestamp)) {
	temp = index_to_try;
	goto end_1;
    }
    else if (later_timestamp_than(this_timestamp,timestamp))
	highest_possible_index = index_to_try;
    else
	lowest_possible_index = index_to_try;
    goto next_loop;
  end_loop:
    temp = Nil;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SITUATE-PREVIOUS-INDEX-IN-IDENTICAL-TIMESTAMPS */
Object situate_previous_index_in_identical_timestamps(history,history_node,
	    new_entry_index,timestamp)
    Object history, history_node, new_entry_index, timestamp;
{
    Object previous_count, oldest_index, index_1, ring_buffer, delta, size;
    Object raw_index, possible_index_of_first_identical_timestamp, vector_1;
    Object managed_number_or_value, possible_first_identical_timestamp, temp_1;
    Object gensymed_symbol_1, ring_index;
    Object earliest_index_with_identical_timestamp_qm;
    Object possible_new_entry_index;
    SI_Long gensymed_symbol;
    char temp;

    x_note_fn_call(168,8);
    previous_count = ISVREF(history_node,(SI_Long)27L);
    oldest_index = ISVREF(history,(SI_Long)2L);
    if (FIXNUM_LT(FIXNUM_GE(new_entry_index,oldest_index) ? 
	    FIXNUM_ADD1(FIXNUM_MINUS(new_entry_index,oldest_index)) : 
	    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(new_entry_index,
	    ISVREF(history,(SI_Long)4L)),oldest_index)),previous_count))
	return VALUES_1(Nil);
    index_1 = new_entry_index;
    ring_buffer = history;
    delta = FIXNUM_NEGATE(previous_count);
    size = ISVREF(ring_buffer,(SI_Long)4L);
    raw_index = FIXNUM_ADD(index_1,delta);
    possible_index_of_first_identical_timestamp = FIXNUM_GE(raw_index,
	    size) ? FIXNUM_MINUS(raw_index,size) : raw_index;
    vector_1 = ISVREF(history,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(possible_index_of_first_identical_timestamp,
		Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		(IFIX(possible_index_of_first_identical_timestamp) >>  -  
		- (SI_Long)10L) + (SI_Long)2L),
		IFIX(possible_index_of_first_identical_timestamp) & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    possible_first_identical_timestamp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    possible_first_identical_timestamp = 
		    aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    possible_first_identical_timestamp = 
		    copy_text_string(managed_number_or_value);
	else
	    possible_first_identical_timestamp = managed_number_or_value;
    }
    else
	possible_first_identical_timestamp = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(possible_index_of_first_identical_timestamp) >>  -  
		- (SI_Long)10L) + (SI_Long)2L),
		IFIX(possible_index_of_first_identical_timestamp) & 
		(SI_Long)1023L));
    if (same_timestamp_as(possible_first_identical_timestamp,timestamp)) {
	temp = FIXNUM_EQ(possible_index_of_first_identical_timestamp,
		oldest_index);
	if (temp);
	else {
	    vector_1 = ISVREF(history,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		gensymed_symbol = 
			IFIX(possible_index_of_first_identical_timestamp) 
			== (SI_Long)0L ? IFIX(FIXNUM_SUB1(ISVREF(history,
			(SI_Long)4L))) : 
			IFIX(FIXNUM_SUB1(possible_index_of_first_identical_timestamp));
		managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,gensymed_symbol + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(vector_1,(gensymed_symbol >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
			(SI_Long)1023L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp_1 = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp_1 = copy_text_string(managed_number_or_value);
		else
		    temp_1 = managed_number_or_value;
	    }
	    else {
		gensymed_symbol = 
			IFIX(possible_index_of_first_identical_timestamp) 
			== (SI_Long)0L ? IFIX(FIXNUM_SUB1(ISVREF(history,
			(SI_Long)4L))) : 
			IFIX(FIXNUM_SUB1(possible_index_of_first_identical_timestamp));
		gensymed_symbol_1 = ISVREF(vector_1,(gensymed_symbol >>  - 
			 - (SI_Long)10L) + (SI_Long)2L);
		temp_1 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gensymed_symbol_1,
			gensymed_symbol & (SI_Long)1023L));
	    }
	    temp =  !TRUEP(same_timestamp_as(temp_1,timestamp));
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(new_entry_index);
    ring_index = IFIX(new_entry_index) == (SI_Long)0L ? 
	    FIXNUM_SUB1(ISVREF(history,(SI_Long)4L)) : 
	    FIXNUM_SUB1(new_entry_index);
  next_loop:
    vector_1 = ISVREF(history,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(ring_index,Managed_array_index_offset))) : 
		ISVREF(ISVREF(vector_1,(IFIX(ring_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp_1 = copy_text_string(managed_number_or_value);
	else
	    temp_1 = managed_number_or_value;
    }
    else
	temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(ring_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(ring_index) & (SI_Long)1023L));
    if ( !TRUEP(same_timestamp_as(temp_1,timestamp)))
	goto end_loop;
    ring_index = IFIX(ring_index) == (SI_Long)0L ? 
	    FIXNUM_SUB1(ISVREF(history,(SI_Long)4L)) : FIXNUM_SUB1(ring_index);
    goto next_loop;
  end_loop:
    earliest_index_with_identical_timestamp_qm = FIXNUM_EQ(ring_index,
	    oldest_index) ? Nil : FIXNUM_EQ(ring_index,
	    FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? FIX((SI_Long)0L) : 
	    FIXNUM_ADD1(ring_index);
    goto end_1;
    earliest_index_with_identical_timestamp_qm = Qnil;
  end_1:;
    if ( !TRUEP(earliest_index_with_identical_timestamp_qm))
	return VALUES_1(Nil);
    size = ISVREF(history,(SI_Long)4L);
    raw_index = FIXNUM_ADD(earliest_index_with_identical_timestamp_qm,
	    previous_count);
    possible_new_entry_index = FIXNUM_GE(raw_index,size) ? 
	    FIXNUM_MINUS(raw_index,size) : raw_index;
    vector_1 = ISVREF(history,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(possible_new_entry_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		(IFIX(possible_new_entry_index) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(possible_new_entry_index) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp_1 = copy_text_string(managed_number_or_value);
	else
	    temp_1 = managed_number_or_value;
    }
    else
	temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(possible_new_entry_index) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(possible_new_entry_index) & (SI_Long)1023L));
    if (same_timestamp_as(temp_1,timestamp))
	return VALUES_1(possible_new_entry_index);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* LOCATE-NEW-HISTORY-INDEX-IF-ANY */
Object locate_new_history_index_if_any(history,history_node,timestamp)
    Object history, history_node, timestamp;
{
    Object temp, old_entry_index, old_index_of_oldest_entry, vector_1;
    Object managed_number_or_value, timestamp_at_old_index, new_entry_index_qm;
    Object index_1, ring_buffer, delta, size, raw_index;
    Object old_index_corrected_for_rotation;

    x_note_fn_call(168,9);
    if (FIXNUM_LT(ISVREF(history,(SI_Long)4L),
	    FIXNUM_MINUS(ISVREF(history_node,(SI_Long)18L),
	    ISVREF(history_node,(SI_Long)25L))))
	temp = Nil;
    else {
	old_entry_index = ISVREF(history_node,(SI_Long)24L);
	old_index_of_oldest_entry = ISVREF(history_node,(SI_Long)23L);
	vector_1 = ISVREF(history,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(old_entry_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(old_entry_index) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(old_entry_index) & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		timestamp_at_old_index = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		timestamp_at_old_index = aref1(managed_number_or_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		timestamp_at_old_index = 
			copy_text_string(managed_number_or_value);
	    else
		timestamp_at_old_index = managed_number_or_value;
	}
	else
	    timestamp_at_old_index = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(old_entry_index) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(old_entry_index) & (SI_Long)1023L));
	new_entry_index_qm = same_timestamp_as(timestamp_at_old_index,
		timestamp) ? old_entry_index : Qnil;
	if (new_entry_index_qm);
	else {
	    index_1 = old_entry_index;
	    ring_buffer = history;
	    delta = FIXNUM_NEGATE(old_index_of_oldest_entry);
	    size = ISVREF(ring_buffer,(SI_Long)4L);
	    raw_index = FIXNUM_ADD(index_1,delta);
	    old_index_corrected_for_rotation = FIXNUM_GE(raw_index,size) ? 
		    FIXNUM_MINUS(raw_index,size) : raw_index;
	    vector_1 = ISVREF(history,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,
			IFIX(FIXNUM_ADD(old_index_corrected_for_rotation,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,
			(IFIX(old_index_corrected_for_rotation) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),
			IFIX(old_index_corrected_for_rotation) & 
			(SI_Long)1023L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp = copy_text_string(managed_number_or_value);
		else
		    temp = managed_number_or_value;
	    }
	    else
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			(IFIX(old_index_corrected_for_rotation) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),
			IFIX(old_index_corrected_for_rotation) & 
			(SI_Long)1023L));
	    new_entry_index_qm = same_timestamp_as(temp,timestamp) ? 
		    old_index_corrected_for_rotation : Nil;
	}
	if (new_entry_index_qm);
	else
	    new_entry_index_qm = get_index_of_timestamp_if_any(timestamp,
		    history);
	temp = new_entry_index_qm ? 
		situate_previous_index_in_identical_timestamps(history,
		history_node,new_entry_index_qm,timestamp) : Nil;
    }
    return VALUES_1(temp);
}

static Object QFLOAT;              /* |float| */

static Object Qtext;               /* text */

static Object Qtruth;              /* truth */

/* GET-BANDWIDTH-FOR-UNTAGGED-HISTORY-VALUE */
Object get_bandwidth_for_untagged_history_value(element_type,value,icp_port)
    Object element_type, value, icp_port;
{
    Object fixnum, text_string, length_1, symbol, index_qm, symbol_name_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_2;

    x_note_fn_call(168,10);
    if (EQ(element_type,Qinteger)) {
	fixnum = value;
	if (IFIX(fixnum) > (SI_Long)63000L)
	    return VALUES_1(FIX((SI_Long)4L));
	else
	    return VALUES_1(FIX((SI_Long)2L));
    }
    else if (EQ(element_type,QFLOAT))
	return VALUES_1(FIX((SI_Long)8L));
    else if (EQ(element_type,Qtext)) {
	text_string = value;
	length_1 = length(text_string);
	gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? (SI_Long)4L : 
		(SI_Long)2L;
	gensymed_symbol_1 = IFIX(length_1);
	return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
    }
    else if (EQ(element_type,Qsymbol)) {
	symbol = value;
	index_qm = get_icp_object_index_for_symbol(symbol,icp_port);
	if (index_qm)
	    return VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
		    FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	else {
	    symbol_name_1 = symbol_name_text_string(symbol);
	    length_2 = IFIX(text_string_length(symbol_name_1)) << (SI_Long)1L;
	    gensymed_symbol = length_2 > (SI_Long)63000L ? (SI_Long)4L : 
		    (SI_Long)2L;
	    gensymed_symbol_1 = length_2;
	    return VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),Nil);
	}
    }
    else if (EQ(element_type,Qtruth)) {
	if (IFIX(value) > (SI_Long)63000L)
	    return VALUES_1(FIX((SI_Long)4L));
	else
	    return VALUES_1(FIX((SI_Long)2L));
    }
    else
	return VALUES_1(Qnil);
}

static Object Qtruth_value;        /* truth-value */

static Object Qab_structure;       /* structure */

/* GET-CACHED-HISTORY-ARRAY-TRANSMISSION-INFO */
Object get_cached_history_array_transmission_info(resumable_history_node,
	    element_type_qm,icp_port,next_cached_index,max_cached_count,
	    bandwidth_needed,bandwidth_available)
    Object resumable_history_node, element_type_qm, icp_port;
    Object next_cached_index, max_cached_count, bandwidth_needed;
    Object bandwidth_available;
{
    Object timestamp_vector, value_vector, float_timestamps_p, float_values_p;
    Object temp, temp_1, number_to_transmit, new_cached_count;
    Object number_of_cached_elements_to_transmit, cached_interning_details;
    Object cached_timestamp, cached_value, timestamp_bandwidth;
    Object value_bandwidth, corresponding_index_qm, bandwidth_to_transmit_1;
    Object new_bandwidth_available, incff_1_arg, evaluation_integer;
    Object evaluation_text, length_1, evaluation_truth_value;
    Object evaluation_symbol, index_qm, symbol_name_1, evaluation_sequence;
    Object evaluation_structure, bandwidth, corresponding_index_qm_1;
    SI_Long element_bandwidth, bandwidth_to_transmit, cached_index;
    SI_Long ab_loop_bind_, gensymed_symbol, gensymed_symbol_1, length_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(168,11);
    timestamp_vector = ISVREF(resumable_history_node,(SI_Long)29L);
    value_vector = ISVREF(resumable_history_node,(SI_Long)30L);
    float_timestamps_p = SIMPLE_VECTOR_P(timestamp_vector) ? 
	    (EQ(ISVREF(timestamp_vector,(SI_Long)0L),
	    Managed_float_array_unique_marker) ? T : Nil) : Qnil;
    float_values_p = SIMPLE_VECTOR_P(value_vector) ? 
	    (EQ(ISVREF(value_vector,(SI_Long)0L),
	    Managed_float_array_unique_marker) ? T : Nil) : Qnil;
    if (float_timestamps_p || float_values_p) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (float_timestamps_p && float_values_p) {
		element_bandwidth = (SI_Long)8L * (SI_Long)2L;
		temp = chestnut_floorf_function(bandwidth_available,
			FIX(element_bandwidth));
		temp_1 = FIXNUM_MINUS(max_cached_count,next_cached_index);
		number_to_transmit = FIXNUM_MIN(temp,temp_1);
		bandwidth_to_transmit = IFIX(number_to_transmit) * 
			element_bandwidth;
		new_cached_count = FIXNUM_ADD(number_to_transmit,
			next_cached_index);
		result = VALUES_7(number_to_transmit,
			FIXNUM_GE(new_cached_count,max_cached_count) ? Nil 
			: new_cached_count,Nil,float_timestamps_p,
			float_values_p,FIX(IFIX(bandwidth_needed) + 
			bandwidth_to_transmit),
			FIX(IFIX(bandwidth_available) - 
			bandwidth_to_transmit));
	    }
	    else if (float_timestamps_p) {
		if (element_type_qm) {
		    number_of_cached_elements_to_transmit = FIX((SI_Long)0L);
		    cached_interning_details = Nil;
		    cached_index = IFIX(next_cached_index);
		    ab_loop_bind_ = IFIX(max_cached_count);
		    cached_timestamp = Nil;
		    cached_value = Nil;
		  next_loop:
		    if (cached_index >= ab_loop_bind_)
			goto end_loop;
		    cached_timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (cached_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),cached_index & (SI_Long)1023L));
		    cached_value = ISVREF(value_vector,cached_index);
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    timestamp_bandwidth = FIX((SI_Long)8L);
		    result = get_bandwidth_for_untagged_history_value(element_type_qm,
			    cached_value,icp_port);
		    MVS_2(result,value_bandwidth,corresponding_index_qm);
		    bandwidth_to_transmit_1 = 
			    FIXNUM_ADD(timestamp_bandwidth,value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit_1);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit_1;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_cached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_cached_elements_to_transmit);
			if (corresponding_index_qm)
			    cached_interning_details = 
				    icp_cons_1(icp_cons_1(FIX(cached_index),
				    corresponding_index_qm),
				    cached_interning_details);
		    }
		    else {
			temp = number_of_cached_elements_to_transmit;
			temp_1 = nreverse(cached_interning_details);
			result = VALUES_7(temp,next_cached_index,temp_1,T,
				Nil,bandwidth_needed,bandwidth_available);
			goto end_1;
		    }
		    cached_index = cached_index + (SI_Long)1L;
		    goto next_loop;
		  end_loop:
		    temp = number_of_cached_elements_to_transmit;
		    temp_1 = nreverse(cached_interning_details);
		    result = VALUES_7(temp,Nil,temp_1,T,Nil,
			    bandwidth_needed,bandwidth_available);
		    goto end_1;
		    result = VALUES_1(Qnil);
		  end_1:;
		}
		else {
		    number_of_cached_elements_to_transmit = FIX((SI_Long)0L);
		    cached_interning_details = Nil;
		    cached_index = IFIX(next_cached_index);
		    ab_loop_bind_ = IFIX(max_cached_count);
		    cached_timestamp = Nil;
		    cached_value = Nil;
		  next_loop_1:
		    if (cached_index >= ab_loop_bind_)
			goto end_loop_1;
		    cached_timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (cached_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),cached_index & (SI_Long)1023L));
		    cached_value = ISVREF(value_vector,cached_index);
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    timestamp_bandwidth = FIX((SI_Long)8L);
		    if (FIXNUMP(cached_value)) {
			evaluation_integer = cached_value;
			if (IFIX(evaluation_integer) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(cached_value) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(cached_value)) 
			    == (SI_Long)1L)
			result = VALUES_1(FIX((SI_Long)8L));
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(cached_value) 
			    != (SI_Long)0L) {
			evaluation_text = cached_value;
			length_1 = length(evaluation_text);
			gensymed_symbol = IFIX(length_1) > (SI_Long)63000L 
				? (SI_Long)4L : (SI_Long)2L;
			gensymed_symbol_1 = IFIX(length_1);
			result = VALUES_1(FIX(gensymed_symbol + 
				gensymed_symbol_1));
		    }
		    else if (CONSP(cached_value) && EQ(M_CDR(cached_value),
			    Qtruth_value)) {
			evaluation_truth_value = M_CAR(cached_value);
			if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (cached_value && SYMBOLP(cached_value)) {
			evaluation_symbol = cached_value;
			index_qm = 
				get_icp_object_index_for_symbol(evaluation_symbol,
				icp_port);
			if (index_qm)
			    result = VALUES_2(IFIX(index_qm) > 
				    (SI_Long)63000L ? FIX((SI_Long)4L) : 
				    FIX((SI_Long)2L),index_qm);
			else {
			    symbol_name_1 = 
				    symbol_name_text_string(evaluation_symbol);
			    length_2 = 
				    IFIX(text_string_length(symbol_name_1)) 
				    << (SI_Long)1L;
			    gensymed_symbol = length_2 > (SI_Long)63000L ? 
				    (SI_Long)4L : (SI_Long)2L;
			    gensymed_symbol_1 = length_2;
			    result = VALUES_2(FIX(gensymed_symbol + 
				    gensymed_symbol_1),Nil);
			}
		    }
		    else if (CONSP(cached_value) && EQ(M_CDR(cached_value),
			    Qsequence)) {
			evaluation_sequence = cached_value;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if (CONSP(cached_value) && EQ(M_CDR(cached_value),
			    Qab_structure)) {
			evaluation_structure = cached_value;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if ( !TRUEP(cached_value))
			result = VALUES_1(FIX((SI_Long)2L));
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,bandwidth,corresponding_index_qm);
		    result = VALUES_2(FIX(IFIX(bandwidth) + (SI_Long)2L),
			    corresponding_index_qm);
		    MVS_2(result,value_bandwidth,corresponding_index_qm);
		    bandwidth_to_transmit_1 = 
			    FIXNUM_ADD(timestamp_bandwidth,value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit_1);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit_1;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_cached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_cached_elements_to_transmit);
			if (corresponding_index_qm)
			    cached_interning_details = 
				    icp_cons_1(icp_cons_1(FIX(cached_index),
				    corresponding_index_qm),
				    cached_interning_details);
		    }
		    else {
			temp = number_of_cached_elements_to_transmit;
			temp_1 = nreverse(cached_interning_details);
			result = VALUES_7(temp,next_cached_index,temp_1,T,
				Nil,bandwidth_needed,bandwidth_available);
			goto end_2;
		    }
		    cached_index = cached_index + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:
		    temp = number_of_cached_elements_to_transmit;
		    temp_1 = nreverse(cached_interning_details);
		    result = VALUES_7(temp,Nil,temp_1,T,Nil,
			    bandwidth_needed,bandwidth_available);
		    goto end_2;
		    result = VALUES_1(Qnil);
		  end_2:;
		}
	    }
	    else if (float_values_p) {
		if (element_type_qm) {
		    number_of_cached_elements_to_transmit = FIX((SI_Long)0L);
		    cached_interning_details = Nil;
		    cached_index = IFIX(next_cached_index);
		    ab_loop_bind_ = IFIX(max_cached_count);
		    cached_timestamp = Nil;
		    cached_value = Nil;
		  next_loop_2:
		    if (cached_index >= ab_loop_bind_)
			goto end_loop_2;
		    cached_timestamp = ISVREF(timestamp_vector,cached_index);
		    cached_value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
			    (cached_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),cached_index & (SI_Long)1023L));
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    if (FIXNUMP(cached_timestamp)) {
			evaluation_integer = cached_timestamp;
			if (IFIX(evaluation_integer) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(cached_timestamp) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(cached_timestamp)) 
			    == (SI_Long)1L)
			result = VALUES_1(FIX((SI_Long)8L));
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(cached_timestamp) 
			    != (SI_Long)0L) {
			evaluation_text = cached_timestamp;
			length_1 = length(evaluation_text);
			gensymed_symbol = IFIX(length_1) > (SI_Long)63000L 
				? (SI_Long)4L : (SI_Long)2L;
			gensymed_symbol_1 = IFIX(length_1);
			result = VALUES_1(FIX(gensymed_symbol + 
				gensymed_symbol_1));
		    }
		    else if (CONSP(cached_timestamp) && 
			    EQ(M_CDR(cached_timestamp),Qtruth_value)) {
			evaluation_truth_value = M_CAR(cached_timestamp);
			if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (cached_timestamp && SYMBOLP(cached_timestamp)) {
			evaluation_symbol = cached_timestamp;
			index_qm = 
				get_icp_object_index_for_symbol(evaluation_symbol,
				icp_port);
			if (index_qm)
			    result = VALUES_2(IFIX(index_qm) > 
				    (SI_Long)63000L ? FIX((SI_Long)4L) : 
				    FIX((SI_Long)2L),index_qm);
			else {
			    symbol_name_1 = 
				    symbol_name_text_string(evaluation_symbol);
			    length_2 = 
				    IFIX(text_string_length(symbol_name_1)) 
				    << (SI_Long)1L;
			    gensymed_symbol = length_2 > (SI_Long)63000L ? 
				    (SI_Long)4L : (SI_Long)2L;
			    gensymed_symbol_1 = length_2;
			    result = VALUES_2(FIX(gensymed_symbol + 
				    gensymed_symbol_1),Nil);
			}
		    }
		    else if (CONSP(cached_timestamp) && 
			    EQ(M_CDR(cached_timestamp),Qsequence)) {
			evaluation_sequence = cached_timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if (CONSP(cached_timestamp) && 
			    EQ(M_CDR(cached_timestamp),Qab_structure)) {
			evaluation_structure = cached_timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if ( !TRUEP(cached_timestamp))
			result = VALUES_1(FIX((SI_Long)2L));
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,bandwidth,corresponding_index_qm);
		    temp_1 = FIX(IFIX(bandwidth) + (SI_Long)2L);
		    timestamp_bandwidth = temp_1;
		    result = get_bandwidth_for_untagged_history_value(element_type_qm,
			    cached_value,icp_port);
		    MVS_2(result,value_bandwidth,corresponding_index_qm);
		    bandwidth_to_transmit_1 = 
			    FIXNUM_ADD(timestamp_bandwidth,value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit_1);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit_1;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_cached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_cached_elements_to_transmit);
			if (corresponding_index_qm)
			    cached_interning_details = 
				    icp_cons_1(icp_cons_1(FIX(cached_index),
				    corresponding_index_qm),
				    cached_interning_details);
		    }
		    else {
			temp = number_of_cached_elements_to_transmit;
			temp_1 = nreverse(cached_interning_details);
			result = VALUES_7(temp,next_cached_index,temp_1,
				Nil,T,bandwidth_needed,bandwidth_available);
			goto end_3;
		    }
		    cached_index = cached_index + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:
		    temp = number_of_cached_elements_to_transmit;
		    temp_1 = nreverse(cached_interning_details);
		    result = VALUES_7(temp,Nil,temp_1,Nil,T,
			    bandwidth_needed,bandwidth_available);
		    goto end_3;
		    result = VALUES_1(Qnil);
		  end_3:;
		}
		else {
		    number_of_cached_elements_to_transmit = FIX((SI_Long)0L);
		    cached_interning_details = Nil;
		    cached_index = IFIX(next_cached_index);
		    ab_loop_bind_ = IFIX(max_cached_count);
		    cached_timestamp = Nil;
		    cached_value = Nil;
		  next_loop_3:
		    if (cached_index >= ab_loop_bind_)
			goto end_loop_3;
		    cached_timestamp = ISVREF(timestamp_vector,cached_index);
		    cached_value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
			    (cached_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),cached_index & (SI_Long)1023L));
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    if (FIXNUMP(cached_timestamp)) {
			evaluation_integer = cached_timestamp;
			if (IFIX(evaluation_integer) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(cached_timestamp) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(cached_timestamp)) 
			    == (SI_Long)1L)
			result = VALUES_1(FIX((SI_Long)8L));
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(cached_timestamp) 
			    != (SI_Long)0L) {
			evaluation_text = cached_timestamp;
			length_1 = length(evaluation_text);
			gensymed_symbol = IFIX(length_1) > (SI_Long)63000L 
				? (SI_Long)4L : (SI_Long)2L;
			gensymed_symbol_1 = IFIX(length_1);
			result = VALUES_1(FIX(gensymed_symbol + 
				gensymed_symbol_1));
		    }
		    else if (CONSP(cached_timestamp) && 
			    EQ(M_CDR(cached_timestamp),Qtruth_value)) {
			evaluation_truth_value = M_CAR(cached_timestamp);
			if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (cached_timestamp && SYMBOLP(cached_timestamp)) {
			evaluation_symbol = cached_timestamp;
			index_qm = 
				get_icp_object_index_for_symbol(evaluation_symbol,
				icp_port);
			if (index_qm)
			    result = VALUES_2(IFIX(index_qm) > 
				    (SI_Long)63000L ? FIX((SI_Long)4L) : 
				    FIX((SI_Long)2L),index_qm);
			else {
			    symbol_name_1 = 
				    symbol_name_text_string(evaluation_symbol);
			    length_2 = 
				    IFIX(text_string_length(symbol_name_1)) 
				    << (SI_Long)1L;
			    gensymed_symbol = length_2 > (SI_Long)63000L ? 
				    (SI_Long)4L : (SI_Long)2L;
			    gensymed_symbol_1 = length_2;
			    result = VALUES_2(FIX(gensymed_symbol + 
				    gensymed_symbol_1),Nil);
			}
		    }
		    else if (CONSP(cached_timestamp) && 
			    EQ(M_CDR(cached_timestamp),Qsequence)) {
			evaluation_sequence = cached_timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if (CONSP(cached_timestamp) && 
			    EQ(M_CDR(cached_timestamp),Qab_structure)) {
			evaluation_structure = cached_timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if ( !TRUEP(cached_timestamp))
			result = VALUES_1(FIX((SI_Long)2L));
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,bandwidth,corresponding_index_qm_1);
		    temp_1 = FIX(IFIX(bandwidth) + (SI_Long)2L);
		    timestamp_bandwidth = temp_1;
		    value_bandwidth = FIX((SI_Long)8L);
		    bandwidth_to_transmit_1 = 
			    FIXNUM_ADD(timestamp_bandwidth,value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit_1);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit_1;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_cached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_cached_elements_to_transmit);
			if (corresponding_index_qm)
			    cached_interning_details = 
				    icp_cons_1(icp_cons_1(FIX(cached_index),
				    corresponding_index_qm),
				    cached_interning_details);
		    }
		    else {
			temp = number_of_cached_elements_to_transmit;
			temp_1 = nreverse(cached_interning_details);
			result = VALUES_7(temp,next_cached_index,temp_1,
				Nil,T,bandwidth_needed,bandwidth_available);
			goto end_4;
		    }
		    cached_index = cached_index + (SI_Long)1L;
		    goto next_loop_3;
		  end_loop_3:
		    temp = number_of_cached_elements_to_transmit;
		    temp_1 = nreverse(cached_interning_details);
		    result = VALUES_7(temp,Nil,temp_1,Nil,T,
			    bandwidth_needed,bandwidth_available);
		    goto end_4;
		    result = VALUES_1(Qnil);
		  end_4:;
		}
	    }
	    else
		result = VALUES_1(Qnil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (element_type_qm) {
	number_of_cached_elements_to_transmit = FIX((SI_Long)0L);
	cached_interning_details = Nil;
	cached_index = IFIX(next_cached_index);
	ab_loop_bind_ = IFIX(max_cached_count);
	cached_timestamp = Nil;
	cached_value = Nil;
      next_loop_4:
	if (cached_index >= ab_loop_bind_)
	    goto end_loop_4;
	cached_timestamp = ISVREF(timestamp_vector,cached_index);
	cached_value = ISVREF(value_vector,cached_index);
	timestamp_bandwidth = Nil;
	value_bandwidth = Nil;
	corresponding_index_qm = Nil;
	if (FIXNUMP(cached_timestamp)) {
	    evaluation_integer = cached_timestamp;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(cached_timestamp) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(cached_timestamp)) == 
		(SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(cached_timestamp) != 
		(SI_Long)0L) {
	    evaluation_text = cached_timestamp;
	    length_1 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_1);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(cached_timestamp) && EQ(M_CDR(cached_timestamp),
		Qtruth_value)) {
	    evaluation_truth_value = M_CAR(cached_timestamp);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (cached_timestamp && SYMBOLP(cached_timestamp)) {
	    evaluation_symbol = cached_timestamp;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_2 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_2 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_2;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(cached_timestamp) && EQ(M_CDR(cached_timestamp),
		Qsequence)) {
	    evaluation_sequence = cached_timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(cached_timestamp) && EQ(M_CDR(cached_timestamp),
		Qab_structure)) {
	    evaluation_structure = cached_timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(cached_timestamp))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	temp_1 = FIX(IFIX(bandwidth) + (SI_Long)2L);
	timestamp_bandwidth = temp_1;
	result = get_bandwidth_for_untagged_history_value(element_type_qm,
		cached_value,icp_port);
	MVS_2(result,value_bandwidth,corresponding_index_qm);
	bandwidth_to_transmit_1 = FIXNUM_ADD(timestamp_bandwidth,
		value_bandwidth);
	new_bandwidth_available = FIXNUM_MINUS(bandwidth_available,
		bandwidth_to_transmit_1);
	if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
	    incff_1_arg = bandwidth_to_transmit_1;
	    bandwidth_needed = FIXNUM_ADD(bandwidth_needed,incff_1_arg);
	    bandwidth_available = new_bandwidth_available;
	    number_of_cached_elements_to_transmit = 
		    FIXNUM_ADD1(number_of_cached_elements_to_transmit);
	    if (corresponding_index_qm)
		cached_interning_details = 
			icp_cons_1(icp_cons_1(FIX(cached_index),
			corresponding_index_qm),cached_interning_details);
	}
	else {
	    temp = number_of_cached_elements_to_transmit;
	    temp_1 = nreverse(cached_interning_details);
	    return VALUES_7(temp,next_cached_index,temp_1,Nil,Nil,
		    bandwidth_needed,bandwidth_available);
	}
	cached_index = cached_index + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:
	temp = number_of_cached_elements_to_transmit;
	temp_1 = nreverse(cached_interning_details);
	return VALUES_7(temp,Nil,temp_1,Nil,Nil,bandwidth_needed,
		bandwidth_available);
	return VALUES_1(Qnil);
    }
    else {
	number_of_cached_elements_to_transmit = FIX((SI_Long)0L);
	cached_interning_details = Nil;
	cached_index = IFIX(next_cached_index);
	ab_loop_bind_ = IFIX(max_cached_count);
	cached_timestamp = Nil;
	cached_value = Nil;
      next_loop_5:
	if (cached_index >= ab_loop_bind_)
	    goto end_loop_5;
	cached_timestamp = ISVREF(timestamp_vector,cached_index);
	cached_value = ISVREF(value_vector,cached_index);
	timestamp_bandwidth = Nil;
	value_bandwidth = Nil;
	corresponding_index_qm = Nil;
	if (FIXNUMP(cached_timestamp)) {
	    evaluation_integer = cached_timestamp;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(cached_timestamp) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(cached_timestamp)) == 
		(SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(cached_timestamp) != 
		(SI_Long)0L) {
	    evaluation_text = cached_timestamp;
	    length_1 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_1);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(cached_timestamp) && EQ(M_CDR(cached_timestamp),
		Qtruth_value)) {
	    evaluation_truth_value = M_CAR(cached_timestamp);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (cached_timestamp && SYMBOLP(cached_timestamp)) {
	    evaluation_symbol = cached_timestamp;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_2 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_2 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_2;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(cached_timestamp) && EQ(M_CDR(cached_timestamp),
		Qsequence)) {
	    evaluation_sequence = cached_timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(cached_timestamp) && EQ(M_CDR(cached_timestamp),
		Qab_structure)) {
	    evaluation_structure = cached_timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(cached_timestamp))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	temp_1 = FIX(IFIX(bandwidth) + (SI_Long)2L);
	timestamp_bandwidth = temp_1;
	if (FIXNUMP(cached_value)) {
	    evaluation_integer = cached_value;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(cached_value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(cached_value)) == 
		(SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(cached_value) != 
		    (SI_Long)0L) {
	    evaluation_text = cached_value;
	    length_1 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_1);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(cached_value) && EQ(M_CDR(cached_value),Qtruth_value)) {
	    evaluation_truth_value = M_CAR(cached_value);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (cached_value && SYMBOLP(cached_value)) {
	    evaluation_symbol = cached_value;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_2 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_2 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_2;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(cached_value) && EQ(M_CDR(cached_value),Qsequence)) {
	    evaluation_sequence = cached_value;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(cached_value) && EQ(M_CDR(cached_value),
		    Qab_structure)) {
	    evaluation_structure = cached_value;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(cached_value))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	result = VALUES_2(FIX(IFIX(bandwidth) + (SI_Long)2L),
		corresponding_index_qm);
	MVS_2(result,value_bandwidth,corresponding_index_qm);
	bandwidth_to_transmit_1 = FIXNUM_ADD(timestamp_bandwidth,
		value_bandwidth);
	new_bandwidth_available = FIXNUM_MINUS(bandwidth_available,
		bandwidth_to_transmit_1);
	if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
	    incff_1_arg = bandwidth_to_transmit_1;
	    bandwidth_needed = FIXNUM_ADD(bandwidth_needed,incff_1_arg);
	    bandwidth_available = new_bandwidth_available;
	    number_of_cached_elements_to_transmit = 
		    FIXNUM_ADD1(number_of_cached_elements_to_transmit);
	    if (corresponding_index_qm)
		cached_interning_details = 
			icp_cons_1(icp_cons_1(FIX(cached_index),
			corresponding_index_qm),cached_interning_details);
	}
	else {
	    temp = number_of_cached_elements_to_transmit;
	    temp_1 = nreverse(cached_interning_details);
	    return VALUES_7(temp,next_cached_index,temp_1,Nil,Nil,
		    bandwidth_needed,bandwidth_available);
	}
	cached_index = cached_index + (SI_Long)1L;
	goto next_loop_5;
      end_loop_5:
	temp = number_of_cached_elements_to_transmit;
	temp_1 = nreverse(cached_interning_details);
	return VALUES_7(temp,Nil,temp_1,Nil,Nil,bandwidth_needed,
		bandwidth_available);
	return VALUES_1(Qnil);
    }
}

static Object Kabort_transmitting_resumable_object;  /* :abort-transmitting-resumable-object */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "A history-keeping variable-or-parameter " */

static Object string_constant_1;   /* "at top level in the argument list " */

static Object string_constant_2;   /* ", being sent as a subobject of ~NF, " */

static Object string_constant_3;   /* "has had its history-keeping spec ~
				    *                       changed to \"none\""
				    */

static Object Qg2_history_array_deleted;  /* g2-history-array-deleted */

static Object string_constant_4;   /* "has overwritten an old value ~
				    *                         before it could be transmitted"
				    */

static Object Qg2_history_array_index_lost;  /* g2-history-array-index-lost */

static Object string_constant_5;   /* "has overwritten some old values ~
				    *                         before they could be transmitted"
				    */

static Object Qg2_history_array_entries_lost;  /* g2-history-array-entries-lost */

/* GET-UNCACHED-HISTORY-ARRAY-TRANSMISSION-INFO */
Object get_uncached_history_array_transmission_info(resumable_history_node,
	    element_type_qm,resumable_object,icp_port,
	    remaining_uncached_count,bandwidth_needed,bandwidth_available)
    Object resumable_history_node, element_type_qm, resumable_object, icp_port;
    Object remaining_uncached_count, bandwidth_needed, bandwidth_available;
{
    Object current_object, toplevel_object, history_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, new_ring_index_qm, newest_ring_index, timestamp_vector;
    Object value_vector, float_timestamps_p, float_values_p;
    Object number_to_transmit, number_of_uncached_elements_to_transmit;
    Object uncached_interning_details, ring_index, timestamp, value;
    Object timestamp_bandwidth, value_bandwidth, corresponding_index_qm;
    Object bandwidth_to_transmit, new_bandwidth_available, incff_1_arg, temp_1;
    Object evaluation_integer, evaluation_text, length_2;
    Object evaluation_truth_value, evaluation_symbol, index_qm, symbol_name_1;
    Object evaluation_sequence, evaluation_structure, bandwidth;
    Object corresponding_index_qm_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long element_bandwidth, new_bandwidth_needed, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(168,12);
    current_object = ISVREF(resumable_history_node,(SI_Long)4L);
    toplevel_object = ISVREF(resumable_object,(SI_Long)8L);
    history_qm = ISVREF(resumable_history_node,(SI_Long)20L);
    if ( !TRUEP(history_qm)) {
	Rpc_throw_tag = Kabort_transmitting_resumable_object;
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
		  tformat(1,string_constant);
		  if (EQ(current_object,toplevel_object))
		      tformat(1,string_constant_1);
		  else
		      tformat(2,string_constant_2,toplevel_object);
		  tformat(1,string_constant_3);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return icp_list_2(Qg2_history_array_deleted,temp);
    }
    new_ring_index_qm = locate_new_history_index_if_any(history_qm,
	    resumable_history_node,ISVREF(resumable_history_node,
	    (SI_Long)26L));
    if ( !TRUEP(new_ring_index_qm)) {
	Rpc_throw_tag = Kabort_transmitting_resumable_object;
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
		  tformat(1,string_constant);
		  if (EQ(current_object,toplevel_object))
		      tformat(1,string_constant_1);
		  else
		      tformat(2,string_constant_2,toplevel_object);
		  tformat(1,string_constant_4);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return icp_list_2(Qg2_history_array_index_lost,temp);
    }
    newest_ring_index = ISVREF(history_qm,(SI_Long)1L);
    if ( !FIXNUM_GE(FIXNUM_GE(newest_ring_index,new_ring_index_qm) ? 
	    FIXNUM_ADD1(FIXNUM_MINUS(newest_ring_index,new_ring_index_qm)) 
	    : FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(newest_ring_index,
	    ISVREF(history_qm,(SI_Long)4L)),new_ring_index_qm)),
	    remaining_uncached_count)) {
	Rpc_throw_tag = Kabort_transmitting_resumable_object;
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
		  tformat(1,string_constant);
		  if (EQ(current_object,toplevel_object))
		      tformat(1,string_constant_1);
		  else
		      tformat(2,string_constant_2,toplevel_object);
		  tformat(1,string_constant_5);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return icp_list_2(Qg2_history_array_entries_lost,temp);
    }
    timestamp_vector = ISVREF(history_qm,(SI_Long)7L);
    value_vector = ISVREF(history_qm,(SI_Long)6L);
    float_timestamps_p = SIMPLE_VECTOR_P(timestamp_vector) ? 
	    (EQ(ISVREF(timestamp_vector,(SI_Long)0L),
	    Managed_float_array_unique_marker) ? T : Nil) : Qnil;
    float_values_p = SIMPLE_VECTOR_P(value_vector) ? 
	    (EQ(ISVREF(value_vector,(SI_Long)0L),
	    Managed_float_array_unique_marker) ? T : Nil) : Qnil;
    if (float_timestamps_p || float_values_p) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (float_timestamps_p && float_values_p) {
		element_bandwidth = (SI_Long)8L * (SI_Long)2L;
		temp = chestnut_floorf_function(bandwidth_available,
			FIX(element_bandwidth));
		number_to_transmit = FIXNUM_MIN(temp,remaining_uncached_count);
		new_bandwidth_needed = IFIX(bandwidth_needed) + 
			IFIX(number_to_transmit) * element_bandwidth;
		result = VALUES_6(number_to_transmit,new_ring_index_qm,Nil,
			T,T,FIX(new_bandwidth_needed));
	    }
	    else if (float_timestamps_p) {
		if (element_type_qm) {
		    number_of_uncached_elements_to_transmit = FIX((SI_Long)0L);
		    uncached_interning_details = Nil;
		    ring_index = new_ring_index_qm;
		    timestamp = Nil;
		    value = Nil;
		  next_loop:
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L));
		    value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(value_vector,IFIX(FIXNUM_ADD(ring_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(value_vector,(IFIX(ring_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    IFIX(ring_index) & (SI_Long)1023L);
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    timestamp_bandwidth = FIX((SI_Long)8L);
		    result = get_bandwidth_for_untagged_history_value(element_type_qm,
			    value,icp_port);
		    MVS_2(result,value_bandwidth,corresponding_index_qm);
		    bandwidth_to_transmit = FIXNUM_ADD(timestamp_bandwidth,
			    value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_uncached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_uncached_elements_to_transmit);
			if (corresponding_index_qm)
			    uncached_interning_details = 
				    icp_cons_1(icp_cons_1(ring_index,
				    corresponding_index_qm),
				    uncached_interning_details);
		    }
		    else {
			temp_1 = number_of_uncached_elements_to_transmit;
			temp = nreverse(uncached_interning_details);
			result = VALUES_6(temp_1,new_ring_index_qm,temp,T,
				Nil,bandwidth_needed);
			goto end_1;
		    }
		    if (FIXNUM_EQ(ring_index,newest_ring_index))
			goto end_loop;
		    ring_index = FIXNUM_EQ(ring_index,
			    FIXNUM_SUB1(ISVREF(history_qm,(SI_Long)4L))) ? 
			    FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    goto next_loop;
		  end_loop:
		    temp_1 = number_of_uncached_elements_to_transmit;
		    temp = nreverse(uncached_interning_details);
		    result = VALUES_6(temp_1,new_ring_index_qm,temp,T,Nil,
			    bandwidth_needed);
		    goto end_1;
		    result = VALUES_1(Qnil);
		  end_1:;
		}
		else {
		    number_of_uncached_elements_to_transmit = FIX((SI_Long)0L);
		    uncached_interning_details = Nil;
		    ring_index = new_ring_index_qm;
		    timestamp = Nil;
		    value = Nil;
		  next_loop_1:
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L));
		    value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(value_vector,IFIX(FIXNUM_ADD(ring_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(value_vector,(IFIX(ring_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    IFIX(ring_index) & (SI_Long)1023L);
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    timestamp_bandwidth = FIX((SI_Long)8L);
		    if (FIXNUMP(value)) {
			evaluation_integer = value;
			if (IFIX(evaluation_integer) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L)
			result = VALUES_1(FIX((SI_Long)8L));
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			    (SI_Long)0L) {
			evaluation_text = value;
			length_2 = length(evaluation_text);
			gensymed_symbol = IFIX(length_2) > (SI_Long)63000L 
				? (SI_Long)4L : (SI_Long)2L;
			gensymed_symbol_1 = IFIX(length_2);
			result = VALUES_1(FIX(gensymed_symbol + 
				gensymed_symbol_1));
		    }
		    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
			evaluation_truth_value = M_CAR(value);
			if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (value && SYMBOLP(value)) {
			evaluation_symbol = value;
			index_qm = 
				get_icp_object_index_for_symbol(evaluation_symbol,
				icp_port);
			if (index_qm)
			    result = VALUES_2(IFIX(index_qm) > 
				    (SI_Long)63000L ? FIX((SI_Long)4L) : 
				    FIX((SI_Long)2L),index_qm);
			else {
			    symbol_name_1 = 
				    symbol_name_text_string(evaluation_symbol);
			    length_1 = 
				    IFIX(text_string_length(symbol_name_1)) 
				    << (SI_Long)1L;
			    gensymed_symbol = length_1 > (SI_Long)63000L ? 
				    (SI_Long)4L : (SI_Long)2L;
			    gensymed_symbol_1 = length_1;
			    result = VALUES_2(FIX(gensymed_symbol + 
				    gensymed_symbol_1),Nil);
			}
		    }
		    else if (CONSP(value) && EQ(M_CDR(value),Qsequence)) {
			evaluation_sequence = value;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if (CONSP(value) && EQ(M_CDR(value),Qab_structure)) {
			evaluation_structure = value;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if ( !TRUEP(value))
			result = VALUES_1(FIX((SI_Long)2L));
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,bandwidth,corresponding_index_qm);
		    result = VALUES_2(FIX(IFIX(bandwidth) + (SI_Long)2L),
			    corresponding_index_qm);
		    MVS_2(result,value_bandwidth,corresponding_index_qm);
		    bandwidth_to_transmit = FIXNUM_ADD(timestamp_bandwidth,
			    value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_uncached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_uncached_elements_to_transmit);
			if (corresponding_index_qm)
			    uncached_interning_details = 
				    icp_cons_1(icp_cons_1(ring_index,
				    corresponding_index_qm),
				    uncached_interning_details);
		    }
		    else {
			temp_1 = number_of_uncached_elements_to_transmit;
			temp = nreverse(uncached_interning_details);
			result = VALUES_6(temp_1,new_ring_index_qm,temp,T,
				Nil,bandwidth_needed);
			goto end_2;
		    }
		    if (FIXNUM_EQ(ring_index,newest_ring_index))
			goto end_loop_1;
		    ring_index = FIXNUM_EQ(ring_index,
			    FIXNUM_SUB1(ISVREF(history_qm,(SI_Long)4L))) ? 
			    FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    goto next_loop_1;
		  end_loop_1:
		    temp_1 = number_of_uncached_elements_to_transmit;
		    temp = nreverse(uncached_interning_details);
		    result = VALUES_6(temp_1,new_ring_index_qm,temp,T,Nil,
			    bandwidth_needed);
		    goto end_2;
		    result = VALUES_1(Qnil);
		  end_2:;
		}
	    }
	    else if (float_values_p) {
		if (element_type_qm) {
		    number_of_uncached_elements_to_transmit = FIX((SI_Long)0L);
		    uncached_interning_details = Nil;
		    ring_index = new_ring_index_qm;
		    timestamp = Nil;
		    value = Nil;
		  next_loop_2:
		    timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(timestamp_vector,
			    IFIX(FIXNUM_ADD(ring_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(timestamp_vector,
			    (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L);
		    value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
			    (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L));
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    if (FIXNUMP(timestamp)) {
			evaluation_integer = timestamp;
			if (IFIX(evaluation_integer) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == 
			    (SI_Long)1L)
			result = VALUES_1(FIX((SI_Long)8L));
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(timestamp) 
			    != (SI_Long)0L) {
			evaluation_text = timestamp;
			length_2 = length(evaluation_text);
			gensymed_symbol = IFIX(length_2) > (SI_Long)63000L 
				? (SI_Long)4L : (SI_Long)2L;
			gensymed_symbol_1 = IFIX(length_2);
			result = VALUES_1(FIX(gensymed_symbol + 
				gensymed_symbol_1));
		    }
		    else if (CONSP(timestamp) && EQ(M_CDR(timestamp),
			    Qtruth_value)) {
			evaluation_truth_value = M_CAR(timestamp);
			if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (timestamp && SYMBOLP(timestamp)) {
			evaluation_symbol = timestamp;
			index_qm = 
				get_icp_object_index_for_symbol(evaluation_symbol,
				icp_port);
			if (index_qm)
			    result = VALUES_2(IFIX(index_qm) > 
				    (SI_Long)63000L ? FIX((SI_Long)4L) : 
				    FIX((SI_Long)2L),index_qm);
			else {
			    symbol_name_1 = 
				    symbol_name_text_string(evaluation_symbol);
			    length_1 = 
				    IFIX(text_string_length(symbol_name_1)) 
				    << (SI_Long)1L;
			    gensymed_symbol = length_1 > (SI_Long)63000L ? 
				    (SI_Long)4L : (SI_Long)2L;
			    gensymed_symbol_1 = length_1;
			    result = VALUES_2(FIX(gensymed_symbol + 
				    gensymed_symbol_1),Nil);
			}
		    }
		    else if (CONSP(timestamp) && EQ(M_CDR(timestamp),
			    Qsequence)) {
			evaluation_sequence = timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if (CONSP(timestamp) && EQ(M_CDR(timestamp),
			    Qab_structure)) {
			evaluation_structure = timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if ( !TRUEP(timestamp))
			result = VALUES_1(FIX((SI_Long)2L));
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,bandwidth,corresponding_index_qm);
		    temp = FIX(IFIX(bandwidth) + (SI_Long)2L);
		    timestamp_bandwidth = temp;
		    result = get_bandwidth_for_untagged_history_value(element_type_qm,
			    value,icp_port);
		    MVS_2(result,value_bandwidth,corresponding_index_qm);
		    bandwidth_to_transmit = FIXNUM_ADD(timestamp_bandwidth,
			    value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_uncached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_uncached_elements_to_transmit);
			if (corresponding_index_qm)
			    uncached_interning_details = 
				    icp_cons_1(icp_cons_1(ring_index,
				    corresponding_index_qm),
				    uncached_interning_details);
		    }
		    else {
			temp_1 = number_of_uncached_elements_to_transmit;
			temp = nreverse(uncached_interning_details);
			result = VALUES_6(temp_1,new_ring_index_qm,temp,
				Nil,T,bandwidth_needed);
			goto end_3;
		    }
		    if (FIXNUM_EQ(ring_index,newest_ring_index))
			goto end_loop_2;
		    ring_index = FIXNUM_EQ(ring_index,
			    FIXNUM_SUB1(ISVREF(history_qm,(SI_Long)4L))) ? 
			    FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    goto next_loop_2;
		  end_loop_2:
		    temp_1 = number_of_uncached_elements_to_transmit;
		    temp = nreverse(uncached_interning_details);
		    result = VALUES_6(temp_1,new_ring_index_qm,temp,Nil,T,
			    bandwidth_needed);
		    goto end_3;
		    result = VALUES_1(Qnil);
		  end_3:;
		}
		else {
		    number_of_uncached_elements_to_transmit = FIX((SI_Long)0L);
		    uncached_interning_details = Nil;
		    ring_index = new_ring_index_qm;
		    timestamp = Nil;
		    value = Nil;
		  next_loop_3:
		    timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(timestamp_vector,
			    IFIX(FIXNUM_ADD(ring_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(timestamp_vector,
			    (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L);
		    value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
			    (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L));
		    timestamp_bandwidth = Nil;
		    value_bandwidth = Nil;
		    corresponding_index_qm = Nil;
		    if (FIXNUMP(timestamp)) {
			evaluation_integer = timestamp;
			if (IFIX(evaluation_integer) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == 
			    (SI_Long)1L)
			result = VALUES_1(FIX((SI_Long)8L));
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(timestamp) 
			    != (SI_Long)0L) {
			evaluation_text = timestamp;
			length_2 = length(evaluation_text);
			gensymed_symbol = IFIX(length_2) > (SI_Long)63000L 
				? (SI_Long)4L : (SI_Long)2L;
			gensymed_symbol_1 = IFIX(length_2);
			result = VALUES_1(FIX(gensymed_symbol + 
				gensymed_symbol_1));
		    }
		    else if (CONSP(timestamp) && EQ(M_CDR(timestamp),
			    Qtruth_value)) {
			evaluation_truth_value = M_CAR(timestamp);
			if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
			    result = VALUES_1(FIX((SI_Long)4L));
			else
			    result = VALUES_1(FIX((SI_Long)2L));
		    }
		    else if (timestamp && SYMBOLP(timestamp)) {
			evaluation_symbol = timestamp;
			index_qm = 
				get_icp_object_index_for_symbol(evaluation_symbol,
				icp_port);
			if (index_qm)
			    result = VALUES_2(IFIX(index_qm) > 
				    (SI_Long)63000L ? FIX((SI_Long)4L) : 
				    FIX((SI_Long)2L),index_qm);
			else {
			    symbol_name_1 = 
				    symbol_name_text_string(evaluation_symbol);
			    length_1 = 
				    IFIX(text_string_length(symbol_name_1)) 
				    << (SI_Long)1L;
			    gensymed_symbol = length_1 > (SI_Long)63000L ? 
				    (SI_Long)4L : (SI_Long)2L;
			    gensymed_symbol_1 = length_1;
			    result = VALUES_2(FIX(gensymed_symbol + 
				    gensymed_symbol_1),Nil);
			}
		    }
		    else if (CONSP(timestamp) && EQ(M_CDR(timestamp),
			    Qsequence)) {
			evaluation_sequence = timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if (CONSP(timestamp) && EQ(M_CDR(timestamp),
			    Qab_structure)) {
			evaluation_structure = timestamp;
			result = VALUES_2(FIX((SI_Long)0L),Nil);
		    }
		    else if ( !TRUEP(timestamp))
			result = VALUES_1(FIX((SI_Long)2L));
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,bandwidth,corresponding_index_qm_1);
		    temp = FIX(IFIX(bandwidth) + (SI_Long)2L);
		    timestamp_bandwidth = temp;
		    value_bandwidth = FIX((SI_Long)8L);
		    bandwidth_to_transmit = FIXNUM_ADD(timestamp_bandwidth,
			    value_bandwidth);
		    new_bandwidth_available = 
			    FIXNUM_MINUS(bandwidth_available,
			    bandwidth_to_transmit);
		    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
			incff_1_arg = bandwidth_to_transmit;
			bandwidth_needed = FIXNUM_ADD(bandwidth_needed,
				incff_1_arg);
			bandwidth_available = new_bandwidth_available;
			number_of_uncached_elements_to_transmit = 
				FIXNUM_ADD1(number_of_uncached_elements_to_transmit);
			if (corresponding_index_qm)
			    uncached_interning_details = 
				    icp_cons_1(icp_cons_1(ring_index,
				    corresponding_index_qm),
				    uncached_interning_details);
		    }
		    else {
			temp_1 = number_of_uncached_elements_to_transmit;
			temp = nreverse(uncached_interning_details);
			result = VALUES_6(temp_1,new_ring_index_qm,temp,
				Nil,T,bandwidth_needed);
			goto end_4;
		    }
		    if (FIXNUM_EQ(ring_index,newest_ring_index))
			goto end_loop_3;
		    ring_index = FIXNUM_EQ(ring_index,
			    FIXNUM_SUB1(ISVREF(history_qm,(SI_Long)4L))) ? 
			    FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    goto next_loop_3;
		  end_loop_3:
		    temp_1 = number_of_uncached_elements_to_transmit;
		    temp = nreverse(uncached_interning_details);
		    result = VALUES_6(temp_1,new_ring_index_qm,temp,Nil,T,
			    bandwidth_needed);
		    goto end_4;
		    result = VALUES_1(Qnil);
		  end_4:;
		}
	    }
	    else
		result = VALUES_1(Qnil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (element_type_qm) {
	number_of_uncached_elements_to_transmit = FIX((SI_Long)0L);
	uncached_interning_details = Nil;
	ring_index = new_ring_index_qm;
	timestamp = Nil;
	value = Nil;
      next_loop_4:
	timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(timestamp_vector,
		IFIX(FIXNUM_ADD(ring_index,Managed_array_index_offset))) : 
		ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		(SI_Long)1023L);
	value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(value_vector,
		IFIX(FIXNUM_ADD(ring_index,Managed_array_index_offset))) : 
		ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		(SI_Long)1023L);
	timestamp_bandwidth = Nil;
	value_bandwidth = Nil;
	corresponding_index_qm = Nil;
	if (FIXNUMP(timestamp)) {
	    evaluation_integer = timestamp;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == (SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(timestamp) != (SI_Long)0L) {
	    evaluation_text = timestamp;
	    length_2 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_2) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_2);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(timestamp) && EQ(M_CDR(timestamp),Qtruth_value)) {
	    evaluation_truth_value = M_CAR(timestamp);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (timestamp && SYMBOLP(timestamp)) {
	    evaluation_symbol = timestamp;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_1 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_1 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_1;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(timestamp) && EQ(M_CDR(timestamp),Qsequence)) {
	    evaluation_sequence = timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(timestamp) && EQ(M_CDR(timestamp),Qab_structure)) {
	    evaluation_structure = timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(timestamp))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	temp = FIX(IFIX(bandwidth) + (SI_Long)2L);
	timestamp_bandwidth = temp;
	result = get_bandwidth_for_untagged_history_value(element_type_qm,
		value,icp_port);
	MVS_2(result,value_bandwidth,corresponding_index_qm);
	bandwidth_to_transmit = FIXNUM_ADD(timestamp_bandwidth,
		value_bandwidth);
	new_bandwidth_available = FIXNUM_MINUS(bandwidth_available,
		bandwidth_to_transmit);
	if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
	    incff_1_arg = bandwidth_to_transmit;
	    bandwidth_needed = FIXNUM_ADD(bandwidth_needed,incff_1_arg);
	    bandwidth_available = new_bandwidth_available;
	    number_of_uncached_elements_to_transmit = 
		    FIXNUM_ADD1(number_of_uncached_elements_to_transmit);
	    if (corresponding_index_qm)
		uncached_interning_details = 
			icp_cons_1(icp_cons_1(ring_index,
			corresponding_index_qm),uncached_interning_details);
	}
	else {
	    temp_1 = number_of_uncached_elements_to_transmit;
	    temp = nreverse(uncached_interning_details);
	    return VALUES_6(temp_1,new_ring_index_qm,temp,Nil,Nil,
		    bandwidth_needed);
	}
	if (FIXNUM_EQ(ring_index,newest_ring_index))
	    goto end_loop_4;
	ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history_qm,
		(SI_Long)4L))) ? FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	goto next_loop_4;
      end_loop_4:
	temp_1 = number_of_uncached_elements_to_transmit;
	temp = nreverse(uncached_interning_details);
	return VALUES_6(temp_1,new_ring_index_qm,temp,Nil,Nil,
		bandwidth_needed);
	return VALUES_1(Qnil);
    }
    else {
	number_of_uncached_elements_to_transmit = FIX((SI_Long)0L);
	uncached_interning_details = Nil;
	ring_index = new_ring_index_qm;
	timestamp = Nil;
	value = Nil;
      next_loop_5:
	timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(timestamp_vector,
		IFIX(FIXNUM_ADD(ring_index,Managed_array_index_offset))) : 
		ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		(SI_Long)1023L);
	value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(value_vector,
		IFIX(FIXNUM_ADD(ring_index,Managed_array_index_offset))) : 
		ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		(SI_Long)1023L);
	timestamp_bandwidth = Nil;
	value_bandwidth = Nil;
	corresponding_index_qm = Nil;
	if (FIXNUMP(timestamp)) {
	    evaluation_integer = timestamp;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == (SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(timestamp) != (SI_Long)0L) {
	    evaluation_text = timestamp;
	    length_2 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_2) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_2);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(timestamp) && EQ(M_CDR(timestamp),Qtruth_value)) {
	    evaluation_truth_value = M_CAR(timestamp);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (timestamp && SYMBOLP(timestamp)) {
	    evaluation_symbol = timestamp;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_1 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_1 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_1;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(timestamp) && EQ(M_CDR(timestamp),Qsequence)) {
	    evaluation_sequence = timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(timestamp) && EQ(M_CDR(timestamp),Qab_structure)) {
	    evaluation_structure = timestamp;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(timestamp))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	temp = FIX(IFIX(bandwidth) + (SI_Long)2L);
	timestamp_bandwidth = temp;
	if (FIXNUMP(value)) {
	    evaluation_integer = value;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L) {
	    evaluation_text = value;
	    length_2 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_2) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_2);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    evaluation_truth_value = M_CAR(value);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (value && SYMBOLP(value)) {
	    evaluation_symbol = value;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_1 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_1 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_1;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(value) && EQ(M_CDR(value),Qsequence)) {
	    evaluation_sequence = value;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(value) && EQ(M_CDR(value),Qab_structure)) {
	    evaluation_structure = value;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(value))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	result = VALUES_2(FIX(IFIX(bandwidth) + (SI_Long)2L),
		corresponding_index_qm);
	MVS_2(result,value_bandwidth,corresponding_index_qm);
	bandwidth_to_transmit = FIXNUM_ADD(timestamp_bandwidth,
		value_bandwidth);
	new_bandwidth_available = FIXNUM_MINUS(bandwidth_available,
		bandwidth_to_transmit);
	if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
	    incff_1_arg = bandwidth_to_transmit;
	    bandwidth_needed = FIXNUM_ADD(bandwidth_needed,incff_1_arg);
	    bandwidth_available = new_bandwidth_available;
	    number_of_uncached_elements_to_transmit = 
		    FIXNUM_ADD1(number_of_uncached_elements_to_transmit);
	    if (corresponding_index_qm)
		uncached_interning_details = 
			icp_cons_1(icp_cons_1(ring_index,
			corresponding_index_qm),uncached_interning_details);
	}
	else {
	    temp_1 = number_of_uncached_elements_to_transmit;
	    temp = nreverse(uncached_interning_details);
	    return VALUES_6(temp_1,new_ring_index_qm,temp,Nil,Nil,
		    bandwidth_needed);
	}
	if (FIXNUM_EQ(ring_index,newest_ring_index))
	    goto end_loop_5;
	ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history_qm,
		(SI_Long)4L))) ? FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	goto next_loop_5;
      end_loop_5:
	temp_1 = number_of_uncached_elements_to_transmit;
	temp = nreverse(uncached_interning_details);
	return VALUES_6(temp_1,new_ring_index_qm,temp,Nil,Nil,
		bandwidth_needed);
	return VALUES_1(Qnil);
    }
}

/* GET-HISTORY-ARRAY-TRANSMISSION-INFO */
Object get_history_array_transmission_info(resumable_history_node,
	    resumable_object,element_type_qm,icp_port)
    Object resumable_history_node, resumable_object, element_type_qm, icp_port;
{
    Object history_length, number_of_cached_elements_to_transmit;
    Object cached_interning_details, next_cached_index_qm;
    Object number_of_uncached_elements_to_transmit;
    Object timestamps_use_float_array_p, values_use_float_array_p;
    Object uncached_interning_details, bandwidth_needed, global_bandwidth;
    Object network_is_limiting_factor_p, bandwidth_available;
    Object next_uncached_ring_index, max_cached_count, temp;
    Object remaining_uncached_count, possible_throw_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object result;

    x_note_fn_call(168,13);
    history_length = ISVREF(resumable_history_node,(SI_Long)18L);
    number_of_cached_elements_to_transmit = FIX((SI_Long)0L);
    cached_interning_details = Nil;
    next_cached_index_qm = ISVREF(resumable_history_node,(SI_Long)28L);
    number_of_uncached_elements_to_transmit = FIX((SI_Long)0L);
    timestamps_use_float_array_p = Nil;
    values_use_float_array_p = Nil;
    uncached_interning_details = Nil;
    gensymed_symbol = element_type_qm ? (SI_Long)2L : (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)2L;
    gensymed_symbol_2 = (SI_Long)2L * (SI_Long)2L;
    bandwidth_needed = FIX(gensymed_symbol + gensymed_symbol_1 + 
	    gensymed_symbol_2);
    global_bandwidth = Nil;
    network_is_limiting_factor_p = Nil;
    bandwidth_available = Nil;
    next_uncached_ring_index = Nil;
    result = get_available_object_passing_bandwidth(resumable_object);
    MVS_2(result,global_bandwidth,network_is_limiting_factor_p);
    bandwidth_available = FIXNUM_MINUS(global_bandwidth,bandwidth_needed);
    if (next_cached_index_qm) {
	max_cached_count = 
		FIXNUM_MIN(Size_of_cached_subsequence_for_resumable_history,
		history_length);
	result = get_cached_history_array_transmission_info(resumable_history_node,
		element_type_qm,icp_port,next_cached_index_qm,
		max_cached_count,bandwidth_needed,bandwidth_available);
	MVS_7(result,number_of_cached_elements_to_transmit,
		next_cached_index_qm,cached_interning_details,
		timestamps_use_float_array_p,values_use_float_array_p,
		bandwidth_needed,bandwidth_available);
    }
    if ( !TRUEP(next_cached_index_qm)) {
	if (ISVREF(resumable_history_node,(SI_Long)26L)) {
	    temp = ISVREF(resumable_history_node,(SI_Long)25L);
	    remaining_uncached_count = FIXNUM_MINUS(history_length,
		    FIXNUM_MAX(Size_of_cached_subsequence_for_resumable_history,
		    temp));
	    result = get_uncached_history_array_transmission_info(resumable_history_node,
		    element_type_qm,resumable_object,icp_port,
		    remaining_uncached_count,bandwidth_needed,
		    bandwidth_available);
	    MVS_7(result,number_of_uncached_elements_to_transmit,
		    next_uncached_ring_index,uncached_interning_details,
		    timestamps_use_float_array_p,values_use_float_array_p,
		    bandwidth_needed,bandwidth_available);
	    possible_throw_value = number_of_uncached_elements_to_transmit;
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	}
    }
    return VALUES_9(number_of_cached_elements_to_transmit,
	    cached_interning_details,next_uncached_ring_index,
	    number_of_uncached_elements_to_transmit,
	    uncached_interning_details,timestamps_use_float_array_p,
	    values_use_float_array_p,bandwidth_needed,
	    network_is_limiting_factor_p);
}

/* MAKE-CASCADED-RING-BUFFER-FOR-HISTORY-OBJECT-PASSING */
Object make_cascaded_ring_buffer_for_history_object_passing(resumable_history_length,
	    timestamps_use_float_array_p,values_use_float_array_p,
	    datapoint_count_qm,datapoint_age,base_time,lowest_ever,
	    highest_ever)
    Object resumable_history_length, timestamps_use_float_array_p;
    Object values_use_float_array_p, datapoint_count_qm, datapoint_age;
    Object base_time, lowest_ever, highest_ever;
{
    Object new_buffer, ring_buffer_size, svref_new_value, new_history;

    x_note_fn_call(168,14);
    new_buffer = make_history_ring_buffer_1();
    ring_buffer_size = datapoint_count_qm ? 
	    FIXNUM_MAX(resumable_history_length,datapoint_count_qm) : 
	    resumable_history_length;
    svref_new_value = timestamps_use_float_array_p ? 
	    allocate_managed_float_array(1,ring_buffer_size) : 
	    allocate_managed_array(1,ring_buffer_size);
    SVREF(new_buffer,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = values_use_float_array_p ? 
	    allocate_managed_float_array(1,ring_buffer_size) : 
	    allocate_managed_array(1,ring_buffer_size);
    SVREF(new_buffer,FIX((SI_Long)6L)) = svref_new_value;
    SVREF(new_buffer,FIX((SI_Long)3L)) = Nil;
    SVREF(new_buffer,FIX((SI_Long)4L)) = ring_buffer_size;
    ISVREF(new_buffer,(SI_Long)1L) = FIX((SI_Long)-1L);
    new_history = make_cascaded_ring_buffer_1();
    svref_new_value = history_cons_1(history_list_3(datapoint_count_qm,
	    datapoint_age,Nil),Nil);
    SVREF(new_history,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = history_cons_1(new_buffer,Nil);
    SVREF(new_history,FIX((SI_Long)4L)) = svref_new_value;
    SVREF(new_history,FIX((SI_Long)10L)) = base_time;
    SVREF(new_history,FIX((SI_Long)9L)) = Nil;
    SVREF(new_history,FIX((SI_Long)8L)) = lowest_ever;
    SVREF(new_history,FIX((SI_Long)7L)) = highest_ever;
    return VALUES_1(new_history);
}

static Object Qicp;                /* icp */

/* G2-TRANSMIT-ADD-HISTORY-RANGE */
Object g2_transmit_add_history_range(resumable_node,
	    number_of_cached_elements,cached_interning_details_qm,
	    ring_index_of_first_uncached_element,
	    number_of_uncached_elements,uncached_interning_details_qm,
	    timestamps_use_float_array_p,values_use_float_array_p)
    Object resumable_node, number_of_cached_elements;
    Object cached_interning_details_qm, ring_index_of_first_uncached_element;
    Object number_of_uncached_elements, uncached_interning_details_qm;
    Object timestamps_use_float_array_p, values_use_float_array_p;
{
    Object cached_timestamp_vector, cached_timestamps_use_float_array_p;
    Object cached_value_vector, cached_values_use_float_array_p;
    Object first_cache_index, timestamp, value, ab_loop_iter_flag_;
    Object incff_1_arg, temp_1, corresponding_index_qm;
    Object next_interning_index_qm, icp_pop_store, cons_1, next_cons;
    Object svref_arg_2, history, timestamp_vector, value_vector;
    Object identical_timestamp_count, ring_index, previous_timestamp_qm;
    Object first_uncached_index, managed_timestamp;
    SI_Long ab_loop_repeat_, cache_index;
    char temp_2;
    double temp, arg, arg_1;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(168,15);
    if (IFIX(number_of_cached_elements) > (SI_Long)0L) {
	cached_timestamp_vector = ISVREF(resumable_node,(SI_Long)29L);
	cached_timestamps_use_float_array_p = 
		SIMPLE_VECTOR_P(cached_timestamp_vector) ? 
		(EQ(ISVREF(cached_timestamp_vector,(SI_Long)0L),
		Managed_float_array_unique_marker) ? T : Nil) : Qnil;
	cached_value_vector = ISVREF(resumable_node,(SI_Long)30L);
	cached_values_use_float_array_p = 
		SIMPLE_VECTOR_P(cached_value_vector) ? 
		(EQ(ISVREF(cached_value_vector,(SI_Long)0L),
		Managed_float_array_unique_marker) ? T : Nil) : Qnil;
	first_cache_index = ISVREF(resumable_node,(SI_Long)28L);
	if (cached_timestamps_use_float_array_p || 
		cached_values_use_float_array_p) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (cached_timestamps_use_float_array_p && 
			cached_values_use_float_array_p) {
		    ab_loop_repeat_ = IFIX(number_of_cached_elements);
		    cache_index = IFIX(first_cache_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			cache_index = cache_index + (SI_Long)1L;
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
			    (cache_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),cache_index & (SI_Long)1023L));
		    value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
			    (cache_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),cache_index & (SI_Long)1023L));
		    temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    write_icp_double_float_1(temp);
		    temp = DOUBLE_FLOAT_TO_DOUBLE(value);
		    write_icp_double_float_1(temp);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop;
		  end_loop:
		    incff_1_arg = number_of_cached_elements;
		    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
			    (SI_Long)25L),incff_1_arg);
		    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
		    incff_1_arg = number_of_cached_elements;
		    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
			    (SI_Long)28L),incff_1_arg);
		    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
		    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
			    Size_of_cached_subsequence_for_resumable_history))
			SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
		    if (cached_interning_details_qm)
			reclaim_icp_tree_1(cached_interning_details_qm);
		}
		else if (cached_timestamps_use_float_array_p) {
		    if (cached_interning_details_qm) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			corresponding_index_qm = Nil;
			next_interning_index_qm = 
				CAAR(cached_interning_details_qm);
			ab_loop_iter_flag_ = T;
		      next_loop_1:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_1;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = ISVREF(cached_value_vector,cache_index);
			if (next_interning_index_qm && 
				IFIX(next_interning_index_qm) == cache_index) {
			    corresponding_index_qm = 
				    CDAR(cached_interning_details_qm);
			    icp_pop_store = Nil;
			    cons_1 = cached_interning_details_qm;
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
			    cached_interning_details_qm = next_cons;
			    reclaim_icp_cons_1(icp_pop_store);
			    next_interning_index_qm = 
				    CAAR(cached_interning_details_qm);
			}
			else
			    corresponding_index_qm = Nil;
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_attribute_value(value,
				corresponding_index_qm);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_1;
		      end_loop_1:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			corresponding_index_qm = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_2:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_2;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = ISVREF(cached_value_vector,cache_index);
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_attribute_value(value,
				corresponding_index_qm);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_2;
		      end_loop_2:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		}
		else if (cached_values_use_float_array_p) {
		    ab_loop_repeat_ = IFIX(number_of_cached_elements);
		    cache_index = IFIX(first_cache_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_3:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_3;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			cache_index = cache_index + (SI_Long)1L;
		    timestamp = ISVREF(cached_timestamp_vector,cache_index);
		    value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
			    (cache_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),cache_index & (SI_Long)1023L));
		    write_icp_history_timestamp(timestamp);
		    temp = DOUBLE_FLOAT_TO_DOUBLE(value);
		    write_icp_double_float_1(temp);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_3;
		  end_loop_3:
		    incff_1_arg = number_of_cached_elements;
		    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
			    (SI_Long)25L),incff_1_arg);
		    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
		    incff_1_arg = number_of_cached_elements;
		    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
			    (SI_Long)28L),incff_1_arg);
		    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
		    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
			    Size_of_cached_subsequence_for_resumable_history))
			SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
		    if (cached_interning_details_qm)
			reclaim_icp_tree_1(cached_interning_details_qm);
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else if (cached_interning_details_qm) {
	    ab_loop_repeat_ = IFIX(number_of_cached_elements);
	    cache_index = IFIX(first_cache_index);
	    timestamp = Nil;
	    value = Nil;
	    corresponding_index_qm = Nil;
	    next_interning_index_qm = CAAR(cached_interning_details_qm);
	    ab_loop_iter_flag_ = T;
	  next_loop_4:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_4;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		cache_index = cache_index + (SI_Long)1L;
	    timestamp = ISVREF(cached_timestamp_vector,cache_index);
	    value = ISVREF(cached_value_vector,cache_index);
	    if (next_interning_index_qm && IFIX(next_interning_index_qm) 
		    == cache_index) {
		corresponding_index_qm = CDAR(cached_interning_details_qm);
		icp_pop_store = Nil;
		cons_1 = cached_interning_details_qm;
		if (cons_1) {
		    icp_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qicp);
		    if (ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = ISVREF(Available_icp_conses_tail_vector,
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
		cached_interning_details_qm = next_cons;
		reclaim_icp_cons_1(icp_pop_store);
		next_interning_index_qm = CAAR(cached_interning_details_qm);
	    }
	    else
		corresponding_index_qm = Nil;
	    write_icp_history_timestamp(timestamp);
	    write_icp_attribute_value(value,corresponding_index_qm);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_4;
	  end_loop_4:
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)28L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
	    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
		    Size_of_cached_subsequence_for_resumable_history))
		SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
	    if (cached_interning_details_qm)
		reclaim_icp_tree_1(cached_interning_details_qm);
	}
	else {
	    ab_loop_repeat_ = IFIX(number_of_cached_elements);
	    cache_index = IFIX(first_cache_index);
	    timestamp = Nil;
	    value = Nil;
	    corresponding_index_qm = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_5:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_5;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		cache_index = cache_index + (SI_Long)1L;
	    timestamp = ISVREF(cached_timestamp_vector,cache_index);
	    value = ISVREF(cached_value_vector,cache_index);
	    write_icp_history_timestamp(timestamp);
	    write_icp_attribute_value(value,corresponding_index_qm);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_5;
	  end_loop_5:
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)28L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
	    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
		    Size_of_cached_subsequence_for_resumable_history))
		SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
	    if (cached_interning_details_qm)
		reclaim_icp_tree_1(cached_interning_details_qm);
	}
    }
    if (IFIX(number_of_uncached_elements) > (SI_Long)0L) {
	history = ISVREF(resumable_node,(SI_Long)20L);
	timestamp_vector = ISVREF(history,(SI_Long)7L);
	value_vector = ISVREF(history,(SI_Long)6L);
	if (timestamps_use_float_array_p || values_use_float_array_p) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (timestamps_use_float_array_p && values_use_float_array_p) {
		    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
		    identical_timestamp_count = FIX((SI_Long)0L);
		    ring_index = ring_index_of_first_uncached_element;
		    timestamp = Nil;
		    previous_timestamp_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
			    0);
		      value = Nil;
		      ab_loop_iter_flag_ = T;
		    next_loop_6:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_6;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      if ( !TRUEP(ab_loop_iter_flag_))
			  ring_index = FIXNUM_EQ(ring_index,
				  FIXNUM_SUB1(ISVREF(history,
				  (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				  FIXNUM_ADD1(ring_index);
		      timestamp = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			      (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			      (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L));
		      value = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
			      (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			      (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L));
		      temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		      write_icp_double_float_1(temp);
		      temp = DOUBLE_FLOAT_TO_DOUBLE(value);
		      write_icp_double_float_1(temp);
		      if (Previous_timestamp_qm) {
			  arg = DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			  arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  temp_2 = arg == arg_1 &&  
				  !inline_nanp_for_comparison(arg) ?  
				  !inline_nanp_for_comparison(arg_1) : 
				  TRUEP(Qnil);
		      }
		      else
			  temp_2 = TRUEP(Nil);
		      if (temp_2)
			  identical_timestamp_count = 
				  FIXNUM_ADD1(identical_timestamp_count);
		      else
			  identical_timestamp_count = FIX((SI_Long)0L);
		      Previous_timestamp_qm = timestamp;
		      ab_loop_iter_flag_ = Nil;
		      goto next_loop_6;
		    end_loop_6:
		      incff_1_arg = number_of_uncached_elements;
		      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
			      (SI_Long)25L),incff_1_arg);
		      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
		      temp_1 = ISVREF(history,(SI_Long)2L);
		      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
		      SVREF(resumable_node,FIX((SI_Long)27L)) = 
			      identical_timestamp_count;
		      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
			      ISVREF(resumable_node,(SI_Long)18L))) {
			  result = get_following_history_timestamp(history,
				  timestamp_vector,ring_index,
				  FIX((SI_Long)1L));
			  MVS_2(result,first_uncached_index,managed_timestamp);
			  SVREF(resumable_node,FIX((SI_Long)24L)) = 
				  first_uncached_index;
			  SVREF(resumable_node,FIX((SI_Long)26L)) = 
				  managed_timestamp;
		      }
		      if (uncached_interning_details_qm)
			  reclaim_icp_tree_1(uncached_interning_details_qm);
		    POP_SPECIAL();
		}
		else if (timestamps_use_float_array_p) {
		    if (uncached_interning_details_qm) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  corresponding_index_qm = Nil;
			  next_interning_index_qm = 
				  CAAR(uncached_interning_details_qm);
			  ab_loop_iter_flag_ = T;
			next_loop_7:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_7;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = FIXNUM_LE(ISVREF(value_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(value_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  if (next_interning_index_qm && 
				  FIXNUM_EQ(next_interning_index_qm,
				  ring_index)) {
			      corresponding_index_qm = 
				      CDAR(uncached_interning_details_qm);
			      icp_pop_store = Nil;
			      cons_1 = uncached_interning_details_qm;
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
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  else {
				      temp_1 = Available_icp_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  M_CDR(cons_1) = Nil;
			      }
			      else
				  next_cons = Nil;
			      uncached_interning_details_qm = next_cons;
			      reclaim_icp_cons_1(icp_pop_store);
			      next_interning_index_qm = 
				      CAAR(uncached_interning_details_qm);
			  }
			  else
			      corresponding_index_qm = Nil;
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_attribute_value(value,
				  corresponding_index_qm);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_2 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if (temp_2)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_7;
			end_loop_7:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  corresponding_index_qm = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_8:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_8;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = FIXNUM_LE(ISVREF(value_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(value_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_attribute_value(value,
				  corresponding_index_qm);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_2 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if (temp_2)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_8;
			end_loop_8:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		}
		else if (values_use_float_array_p) {
		    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
		    identical_timestamp_count = FIX((SI_Long)0L);
		    ring_index = ring_index_of_first_uncached_element;
		    timestamp = Nil;
		    previous_timestamp_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
			    0);
		      value = Nil;
		      ab_loop_iter_flag_ = T;
		    next_loop_9:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_9;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      if ( !TRUEP(ab_loop_iter_flag_))
			  ring_index = FIXNUM_EQ(ring_index,
				  FIXNUM_SUB1(ISVREF(history,
				  (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				  FIXNUM_ADD1(ring_index);
		      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(timestamp_vector,
			      IFIX(FIXNUM_ADD(ring_index,
			      Managed_array_index_offset))) : 
			      ISVREF(ISVREF(timestamp_vector,
			      (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			      (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L);
		      value = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
			      (IFIX(ring_index) >>  -  - (SI_Long)10L) + 
			      (SI_Long)2L),IFIX(ring_index) & (SI_Long)1023L));
		      write_icp_history_timestamp(timestamp);
		      temp = DOUBLE_FLOAT_TO_DOUBLE(value);
		      write_icp_double_float_1(temp);
		      if (Previous_timestamp_qm && evaluation_value_eql(2,
			      Previous_timestamp_qm,timestamp))
			  identical_timestamp_count = 
				  FIXNUM_ADD1(identical_timestamp_count);
		      else
			  identical_timestamp_count = FIX((SI_Long)0L);
		      Previous_timestamp_qm = timestamp;
		      ab_loop_iter_flag_ = Nil;
		      goto next_loop_9;
		    end_loop_9:
		      incff_1_arg = number_of_uncached_elements;
		      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
			      (SI_Long)25L),incff_1_arg);
		      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
		      temp_1 = ISVREF(history,(SI_Long)2L);
		      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
		      SVREF(resumable_node,FIX((SI_Long)27L)) = 
			      identical_timestamp_count;
		      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
			      ISVREF(resumable_node,(SI_Long)18L))) {
			  result = get_following_history_timestamp(history,
				  timestamp_vector,ring_index,
				  FIX((SI_Long)1L));
			  MVS_2(result,first_uncached_index,managed_timestamp);
			  SVREF(resumable_node,FIX((SI_Long)24L)) = 
				  first_uncached_index;
			  SVREF(resumable_node,FIX((SI_Long)26L)) = 
				  managed_timestamp;
		      }
		      if (uncached_interning_details_qm)
			  reclaim_icp_tree_1(uncached_interning_details_qm);
		    POP_SPECIAL();
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else if (uncached_interning_details_qm) {
	    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
	    identical_timestamp_count = FIX((SI_Long)0L);
	    ring_index = ring_index_of_first_uncached_element;
	    timestamp = Nil;
	    previous_timestamp_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		    0);
	      value = Nil;
	      corresponding_index_qm = Nil;
	      next_interning_index_qm = CAAR(uncached_interning_details_qm);
	      ab_loop_iter_flag_ = T;
	    next_loop_10:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_10;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  ring_index = FIXNUM_EQ(ring_index,
			  FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(timestamp_vector,IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(value_vector,
		      IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      if (next_interning_index_qm && 
		      FIXNUM_EQ(next_interning_index_qm,ring_index)) {
		  corresponding_index_qm = CDAR(uncached_interning_details_qm);
		  icp_pop_store = Nil;
		  cons_1 = uncached_interning_details_qm;
		  if (cons_1) {
		      icp_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qicp);
		      if (ISVREF(Available_icp_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_1 = ISVREF(Available_icp_conses_tail_vector,
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
		  uncached_interning_details_qm = next_cons;
		  reclaim_icp_cons_1(icp_pop_store);
		  next_interning_index_qm = 
			  CAAR(uncached_interning_details_qm);
	      }
	      else
		  corresponding_index_qm = Nil;
	      write_icp_history_timestamp(timestamp);
	      write_icp_attribute_value(value,corresponding_index_qm);
	      if (Previous_timestamp_qm && evaluation_value_eql(2,
		      Previous_timestamp_qm,timestamp))
		  identical_timestamp_count = 
			  FIXNUM_ADD1(identical_timestamp_count);
	      else
		  identical_timestamp_count = FIX((SI_Long)0L);
	      Previous_timestamp_qm = timestamp;
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_10;
	    end_loop_10:
	      incff_1_arg = number_of_uncached_elements;
	      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		      incff_1_arg);
	      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	      temp_1 = ISVREF(history,(SI_Long)2L);
	      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
	      SVREF(resumable_node,FIX((SI_Long)27L)) = 
		      identical_timestamp_count;
	      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		      ISVREF(resumable_node,(SI_Long)18L))) {
		  result = get_following_history_timestamp(history,
			  timestamp_vector,ring_index,FIX((SI_Long)1L));
		  MVS_2(result,first_uncached_index,managed_timestamp);
		  SVREF(resumable_node,FIX((SI_Long)24L)) = 
			  first_uncached_index;
		  SVREF(resumable_node,FIX((SI_Long)26L)) = managed_timestamp;
	      }
	      if (uncached_interning_details_qm)
		  reclaim_icp_tree_1(uncached_interning_details_qm);
	    POP_SPECIAL();
	}
	else {
	    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
	    identical_timestamp_count = FIX((SI_Long)0L);
	    ring_index = ring_index_of_first_uncached_element;
	    timestamp = Nil;
	    previous_timestamp_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		    0);
	      value = Nil;
	      corresponding_index_qm = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_11:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_11;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  ring_index = FIXNUM_EQ(ring_index,
			  FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(timestamp_vector,IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(value_vector,
		      IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      write_icp_history_timestamp(timestamp);
	      write_icp_attribute_value(value,corresponding_index_qm);
	      if (Previous_timestamp_qm && evaluation_value_eql(2,
		      Previous_timestamp_qm,timestamp))
		  identical_timestamp_count = 
			  FIXNUM_ADD1(identical_timestamp_count);
	      else
		  identical_timestamp_count = FIX((SI_Long)0L);
	      Previous_timestamp_qm = timestamp;
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_11;
	    end_loop_11:
	      incff_1_arg = number_of_uncached_elements;
	      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		      incff_1_arg);
	      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	      temp_1 = ISVREF(history,(SI_Long)2L);
	      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
	      SVREF(resumable_node,FIX((SI_Long)27L)) = 
		      identical_timestamp_count;
	      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		      ISVREF(resumable_node,(SI_Long)18L))) {
		  result = get_following_history_timestamp(history,
			  timestamp_vector,ring_index,FIX((SI_Long)1L));
		  MVS_2(result,first_uncached_index,managed_timestamp);
		  SVREF(resumable_node,FIX((SI_Long)24L)) = 
			  first_uncached_index;
		  SVREF(resumable_node,FIX((SI_Long)26L)) = managed_timestamp;
	      }
	      if (uncached_interning_details_qm)
		  reclaim_icp_tree_1(uncached_interning_details_qm);
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

/* G2-TRANSMIT-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object g2_transmit_add_homogeneous_history_range(resumable_node,
	    element_type,number_of_cached_elements,
	    cached_interning_details_qm,
	    ring_index_of_first_uncached_element,
	    number_of_uncached_elements,uncached_interning_details_qm,
	    timestamps_use_float_array_p)
    Object resumable_node, element_type, number_of_cached_elements;
    Object cached_interning_details_qm, ring_index_of_first_uncached_element;
    Object number_of_uncached_elements, uncached_interning_details_qm;
    Object timestamps_use_float_array_p;
{
    Object cached_timestamp_vector, cached_timestamps_use_float_array_p;
    Object cached_value_vector, cached_values_use_float_array_p;
    Object first_cache_index, timestamp, value, ab_loop_iter_flag_;
    Object incff_1_arg, temp_1, next_interning_index_qm;
    Object corresponding_index_qm, temp_2, icp_pop_store, cons_1, next_cons;
    Object svref_arg_2, history, timestamp_vector, value_vector;
    Object identical_timestamp_count, ring_index, previous_timestamp_qm;
    Object first_uncached_index, managed_timestamp;
    SI_Long ab_loop_repeat_, cache_index;
    char values_use_float_array_p, temp_3;
    double temp, arg, arg_1;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(168,16);
    values_use_float_array_p = EQ(element_type,QFLOAT);
    if (IFIX(number_of_cached_elements) > (SI_Long)0L) {
	cached_timestamp_vector = ISVREF(resumable_node,(SI_Long)29L);
	cached_timestamps_use_float_array_p = 
		SIMPLE_VECTOR_P(cached_timestamp_vector) ? 
		(EQ(ISVREF(cached_timestamp_vector,(SI_Long)0L),
		Managed_float_array_unique_marker) ? T : Nil) : Qnil;
	cached_value_vector = ISVREF(resumable_node,(SI_Long)30L);
	cached_values_use_float_array_p = 
		SIMPLE_VECTOR_P(cached_value_vector) ? 
		(EQ(ISVREF(cached_value_vector,(SI_Long)0L),
		Managed_float_array_unique_marker) ? T : Nil) : Qnil;
	first_cache_index = ISVREF(resumable_node,(SI_Long)28L);
	if (cached_timestamps_use_float_array_p || 
		cached_values_use_float_array_p) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (cached_timestamps_use_float_array_p && 
			values_use_float_array_p) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_fixnum(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop;
		      end_loop:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_1:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_1;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			temp = DOUBLE_FLOAT_TO_DOUBLE(value);
			write_icp_double_float_1(temp);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_1;
		      end_loop_1:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_2:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_2;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_text_string(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_2;
		      end_loop_2:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_3:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_3;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_evaluation_truth_value(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_3;
		      end_loop_3:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			next_interning_index_qm = 
				CAAR(cached_interning_details_qm);
			corresponding_index_qm = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_4:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_4;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			if (next_interning_index_qm && 
				IFIX(next_interning_index_qm) == cache_index) {
			    temp_2 = CDAR(cached_interning_details_qm);
			    icp_pop_store = Nil;
			    cons_1 = cached_interning_details_qm;
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
			    cached_interning_details_qm = next_cons;
			    reclaim_icp_cons_1(icp_pop_store);
			    next_interning_index_qm = 
				    CAAR(cached_interning_details_qm);
			    corresponding_index_qm = temp_2;
			}
			else
			    corresponding_index_qm = Nil;
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_possibly_interned_symbol(value,
				corresponding_index_qm);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_4;
		      end_loop_4:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		}
		else if (cached_timestamps_use_float_array_p) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_5:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_5;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = ISVREF(cached_value_vector,cache_index);
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_fixnum(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_5;
		      end_loop_5:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_6:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_6;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = ISVREF(cached_value_vector,cache_index);
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			temp = DOUBLE_FLOAT_TO_DOUBLE(value);
			write_icp_double_float_1(temp);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_6;
		      end_loop_6:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_7:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_7;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = ISVREF(cached_value_vector,cache_index);
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_text_string(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_7;
		      end_loop_7:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_8:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_8;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = ISVREF(cached_value_vector,cache_index);
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_evaluation_truth_value(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_8;
		      end_loop_8:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			next_interning_index_qm = 
				CAAR(cached_interning_details_qm);
			corresponding_index_qm = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_9:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_9;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_timestamp_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			value = ISVREF(cached_value_vector,cache_index);
			if (next_interning_index_qm && 
				IFIX(next_interning_index_qm) == cache_index) {
			    temp_2 = CDAR(cached_interning_details_qm);
			    icp_pop_store = Nil;
			    cons_1 = cached_interning_details_qm;
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
			    cached_interning_details_qm = next_cons;
			    reclaim_icp_cons_1(icp_pop_store);
			    next_interning_index_qm = 
				    CAAR(cached_interning_details_qm);
			    corresponding_index_qm = temp_2;
			}
			else
			    corresponding_index_qm = Nil;
			temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			write_icp_double_float_1(temp);
			write_icp_possibly_interned_symbol(value,
				corresponding_index_qm);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_9;
		      end_loop_9:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		}
		else if (cached_values_use_float_array_p) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_10:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_10;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = ISVREF(cached_timestamp_vector,
				cache_index);
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			write_icp_history_timestamp(timestamp);
			write_icp_fixnum(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_10;
		      end_loop_10:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_11:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_11;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = ISVREF(cached_timestamp_vector,
				cache_index);
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			write_icp_history_timestamp(timestamp);
			temp = DOUBLE_FLOAT_TO_DOUBLE(value);
			write_icp_double_float_1(temp);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_11;
		      end_loop_11:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_12:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_12;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = ISVREF(cached_timestamp_vector,
				cache_index);
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			write_icp_history_timestamp(timestamp);
			write_icp_text_string(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_12;
		      end_loop_12:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_13:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_13;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = ISVREF(cached_timestamp_vector,
				cache_index);
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			write_icp_history_timestamp(timestamp);
			write_icp_evaluation_truth_value(value);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_13;
		      end_loop_13:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_cached_elements);
			cache_index = IFIX(first_cache_index);
			timestamp = Nil;
			value = Nil;
			next_interning_index_qm = 
				CAAR(cached_interning_details_qm);
			corresponding_index_qm = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_14:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_14;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    cache_index = cache_index + (SI_Long)1L;
			timestamp = ISVREF(cached_timestamp_vector,
				cache_index);
			value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(cached_value_vector,
				(cache_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),cache_index & (SI_Long)1023L));
			if (next_interning_index_qm && 
				IFIX(next_interning_index_qm) == cache_index) {
			    temp_2 = CDAR(cached_interning_details_qm);
			    icp_pop_store = Nil;
			    cons_1 = cached_interning_details_qm;
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
			    cached_interning_details_qm = next_cons;
			    reclaim_icp_cons_1(icp_pop_store);
			    next_interning_index_qm = 
				    CAAR(cached_interning_details_qm);
			    corresponding_index_qm = temp_2;
			}
			else
			    corresponding_index_qm = Nil;
			write_icp_history_timestamp(timestamp);
			write_icp_possibly_interned_symbol(value,
				corresponding_index_qm);
			ab_loop_iter_flag_ = Nil;
			goto next_loop_14;
		      end_loop_14:
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)25L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			incff_1_arg = number_of_cached_elements;
			temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				(SI_Long)28L),incff_1_arg);
			SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
			if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
				Size_of_cached_subsequence_for_resumable_history))
			    SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
			if (cached_interning_details_qm)
			    reclaim_icp_tree_1(cached_interning_details_qm);
		    }
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else if (EQ(element_type,Qinteger)) {
	    ab_loop_repeat_ = IFIX(number_of_cached_elements);
	    cache_index = IFIX(first_cache_index);
	    timestamp = Nil;
	    value = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_15:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_15;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		cache_index = cache_index + (SI_Long)1L;
	    timestamp = ISVREF(cached_timestamp_vector,cache_index);
	    value = ISVREF(cached_value_vector,cache_index);
	    write_icp_history_timestamp(timestamp);
	    write_icp_fixnum(value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_15;
	  end_loop_15:
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)28L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
	    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
		    Size_of_cached_subsequence_for_resumable_history))
		SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
	    if (cached_interning_details_qm)
		reclaim_icp_tree_1(cached_interning_details_qm);
	}
	else if (EQ(element_type,QFLOAT)) {
	    ab_loop_repeat_ = IFIX(number_of_cached_elements);
	    cache_index = IFIX(first_cache_index);
	    timestamp = Nil;
	    value = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_16:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_16;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		cache_index = cache_index + (SI_Long)1L;
	    timestamp = ISVREF(cached_timestamp_vector,cache_index);
	    value = ISVREF(cached_value_vector,cache_index);
	    write_icp_history_timestamp(timestamp);
	    temp = DOUBLE_FLOAT_TO_DOUBLE(value);
	    write_icp_double_float_1(temp);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_16;
	  end_loop_16:
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)28L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
	    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
		    Size_of_cached_subsequence_for_resumable_history))
		SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
	    if (cached_interning_details_qm)
		reclaim_icp_tree_1(cached_interning_details_qm);
	}
	else if (EQ(element_type,Qtext)) {
	    ab_loop_repeat_ = IFIX(number_of_cached_elements);
	    cache_index = IFIX(first_cache_index);
	    timestamp = Nil;
	    value = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_17:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_17;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		cache_index = cache_index + (SI_Long)1L;
	    timestamp = ISVREF(cached_timestamp_vector,cache_index);
	    value = ISVREF(cached_value_vector,cache_index);
	    write_icp_history_timestamp(timestamp);
	    write_icp_text_string(value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_17;
	  end_loop_17:
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)28L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
	    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
		    Size_of_cached_subsequence_for_resumable_history))
		SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
	    if (cached_interning_details_qm)
		reclaim_icp_tree_1(cached_interning_details_qm);
	}
	else if (EQ(element_type,Qtruth)) {
	    ab_loop_repeat_ = IFIX(number_of_cached_elements);
	    cache_index = IFIX(first_cache_index);
	    timestamp = Nil;
	    value = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_18:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_18;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		cache_index = cache_index + (SI_Long)1L;
	    timestamp = ISVREF(cached_timestamp_vector,cache_index);
	    value = ISVREF(cached_value_vector,cache_index);
	    write_icp_history_timestamp(timestamp);
	    write_icp_evaluation_truth_value(value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_18;
	  end_loop_18:
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)28L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
	    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
		    Size_of_cached_subsequence_for_resumable_history))
		SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
	    if (cached_interning_details_qm)
		reclaim_icp_tree_1(cached_interning_details_qm);
	}
	else if (EQ(element_type,Qsymbol)) {
	    ab_loop_repeat_ = IFIX(number_of_cached_elements);
	    cache_index = IFIX(first_cache_index);
	    timestamp = Nil;
	    value = Nil;
	    next_interning_index_qm = CAAR(cached_interning_details_qm);
	    corresponding_index_qm = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_19:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_19;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		cache_index = cache_index + (SI_Long)1L;
	    timestamp = ISVREF(cached_timestamp_vector,cache_index);
	    value = ISVREF(cached_value_vector,cache_index);
	    if (next_interning_index_qm && IFIX(next_interning_index_qm) 
		    == cache_index) {
		temp_2 = CDAR(cached_interning_details_qm);
		icp_pop_store = Nil;
		cons_1 = cached_interning_details_qm;
		if (cons_1) {
		    icp_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qicp);
		    if (ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = ISVREF(Available_icp_conses_tail_vector,
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
		cached_interning_details_qm = next_cons;
		reclaim_icp_cons_1(icp_pop_store);
		next_interning_index_qm = CAAR(cached_interning_details_qm);
		corresponding_index_qm = temp_2;
	    }
	    else
		corresponding_index_qm = Nil;
	    write_icp_history_timestamp(timestamp);
	    write_icp_possibly_interned_symbol(value,corresponding_index_qm);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_19;
	  end_loop_19:
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	    incff_1_arg = number_of_cached_elements;
	    temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)28L),
		    incff_1_arg);
	    SVREF(resumable_node,FIX((SI_Long)28L)) = temp_1;
	    if (FIXNUM_EQ(ISVREF(resumable_node,(SI_Long)28L),
		    Size_of_cached_subsequence_for_resumable_history))
		SVREF(resumable_node,FIX((SI_Long)28L)) = Nil;
	    if (cached_interning_details_qm)
		reclaim_icp_tree_1(cached_interning_details_qm);
	}
    }
    if (IFIX(number_of_uncached_elements) > (SI_Long)0L) {
	history = ISVREF(resumable_node,(SI_Long)20L);
	timestamp_vector = ISVREF(history,(SI_Long)7L);
	value_vector = ISVREF(history,(SI_Long)6L);
	if (timestamps_use_float_array_p || values_use_float_array_p) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (timestamps_use_float_array_p && values_use_float_array_p) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_20:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_20;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_fixnum(value);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_20;
			end_loop_20:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_21:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_21;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(value);
			  write_icp_double_float_1(temp);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_21;
			end_loop_21:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_22:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_22;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_text_string(value);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_22;
			end_loop_22:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_23:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_23;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_evaluation_truth_value(value);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_23;
			end_loop_23:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  next_interning_index_qm = 
				  CAAR(uncached_interning_details_qm);
			  corresponding_index_qm = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_24:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_24;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  if (next_interning_index_qm && 
				  FIXNUM_EQ(next_interning_index_qm,
				  ring_index)) {
			      temp_2 = CDAR(uncached_interning_details_qm);
			      icp_pop_store = Nil;
			      cons_1 = uncached_interning_details_qm;
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
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  else {
				      temp_1 = Available_icp_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  M_CDR(cons_1) = Nil;
			      }
			      else
				  next_cons = Nil;
			      uncached_interning_details_qm = next_cons;
			      reclaim_icp_cons_1(icp_pop_store);
			      next_interning_index_qm = 
				      CAAR(uncached_interning_details_qm);
			      corresponding_index_qm = temp_2;
			  }
			  else
			      corresponding_index_qm = Nil;
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_possibly_interned_symbol(value,
				  corresponding_index_qm);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_24;
			end_loop_24:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		}
		else if (timestamps_use_float_array_p) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_25:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_25;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = FIXNUM_LE(ISVREF(value_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(value_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_fixnum(value);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_25;
			end_loop_25:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_26:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_26;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = FIXNUM_LE(ISVREF(value_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(value_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(value);
			  write_icp_double_float_1(temp);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_26;
			end_loop_26:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_27:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_27;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = FIXNUM_LE(ISVREF(value_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(value_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_text_string(value);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_27;
			end_loop_27:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_28:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_28;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = FIXNUM_LE(ISVREF(value_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(value_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_evaluation_truth_value(value);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_28;
			end_loop_28:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  next_interning_index_qm = 
				  CAAR(uncached_interning_details_qm);
			  corresponding_index_qm = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_29:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_29;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  value = FIXNUM_LE(ISVREF(value_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(value_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  if (next_interning_index_qm && 
				  FIXNUM_EQ(next_interning_index_qm,
				  ring_index)) {
			      temp_2 = CDAR(uncached_interning_details_qm);
			      icp_pop_store = Nil;
			      cons_1 = uncached_interning_details_qm;
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
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  else {
				      temp_1 = Available_icp_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  M_CDR(cons_1) = Nil;
			      }
			      else
				  next_cons = Nil;
			      uncached_interning_details_qm = next_cons;
			      reclaim_icp_cons_1(icp_pop_store);
			      next_interning_index_qm = 
				      CAAR(uncached_interning_details_qm);
			      corresponding_index_qm = temp_2;
			  }
			  else
			      corresponding_index_qm = Nil;
			  temp = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			  write_icp_double_float_1(temp);
			  write_icp_possibly_interned_symbol(value,
				  corresponding_index_qm);
			  if (Previous_timestamp_qm) {
			      arg = 
				      DOUBLE_FLOAT_TO_DOUBLE(Previous_timestamp_qm);
			      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			      temp_3 = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  else
			      temp_3 = TRUEP(Nil);
			  if (temp_3)
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_29;
			end_loop_29:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		}
		else if (values_use_float_array_p) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_30:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_30;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(timestamp_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  write_icp_history_timestamp(timestamp);
			  write_icp_fixnum(value);
			  if (Previous_timestamp_qm && 
				  evaluation_value_eql(2,
				  Previous_timestamp_qm,timestamp))
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_30;
			end_loop_30:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_31:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_31;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(timestamp_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  write_icp_history_timestamp(timestamp);
			  temp = DOUBLE_FLOAT_TO_DOUBLE(value);
			  write_icp_double_float_1(temp);
			  if (Previous_timestamp_qm && 
				  evaluation_value_eql(2,
				  Previous_timestamp_qm,timestamp))
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_31;
			end_loop_31:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_32:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_32;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(timestamp_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  write_icp_history_timestamp(timestamp);
			  write_icp_text_string(value);
			  if (Previous_timestamp_qm && 
				  evaluation_value_eql(2,
				  Previous_timestamp_qm,timestamp))
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_32;
			end_loop_32:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_33:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_33;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(timestamp_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  write_icp_history_timestamp(timestamp);
			  write_icp_evaluation_truth_value(value);
			  if (Previous_timestamp_qm && 
				  evaluation_value_eql(2,
				  Previous_timestamp_qm,timestamp))
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_33;
			end_loop_33:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_uncached_elements);
			identical_timestamp_count = FIX((SI_Long)0L);
			ring_index = ring_index_of_first_uncached_element;
			timestamp = Nil;
			previous_timestamp_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
				0);
			  value = Nil;
			  next_interning_index_qm = 
				  CAAR(uncached_interning_details_qm);
			  corresponding_index_qm = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_34:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_34;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  if ( !TRUEP(ab_loop_iter_flag_))
			      ring_index = FIXNUM_EQ(ring_index,
				      FIXNUM_SUB1(ISVREF(history,
				      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				      FIXNUM_ADD1(ring_index);
			  timestamp = FIXNUM_LE(ISVREF(timestamp_vector,
				  (SI_Long)1L),
				  Maximum_in_place_array_size) ? 
				  ISVREF(timestamp_vector,
				  IFIX(FIXNUM_ADD(ring_index,
				  Managed_array_index_offset))) : 
				  ISVREF(ISVREF(timestamp_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L);
			  value = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_vector,
				  (IFIX(ring_index) >>  -  - (SI_Long)10L) 
				  + (SI_Long)2L),IFIX(ring_index) & 
				  (SI_Long)1023L));
			  if (next_interning_index_qm && 
				  FIXNUM_EQ(next_interning_index_qm,
				  ring_index)) {
			      temp_2 = CDAR(uncached_interning_details_qm);
			      icp_pop_store = Nil;
			      cons_1 = uncached_interning_details_qm;
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
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  else {
				      temp_1 = Available_icp_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				      temp_1 = 
					      Available_icp_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp_1,svref_arg_2) = cons_1;
				  }
				  M_CDR(cons_1) = Nil;
			      }
			      else
				  next_cons = Nil;
			      uncached_interning_details_qm = next_cons;
			      reclaim_icp_cons_1(icp_pop_store);
			      next_interning_index_qm = 
				      CAAR(uncached_interning_details_qm);
			      corresponding_index_qm = temp_2;
			  }
			  else
			      corresponding_index_qm = Nil;
			  write_icp_history_timestamp(timestamp);
			  write_icp_possibly_interned_symbol(value,
				  corresponding_index_qm);
			  if (Previous_timestamp_qm && 
				  evaluation_value_eql(2,
				  Previous_timestamp_qm,timestamp))
			      identical_timestamp_count = 
				      FIXNUM_ADD1(identical_timestamp_count);
			  else
			      identical_timestamp_count = FIX((SI_Long)0L);
			  Previous_timestamp_qm = timestamp;
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_34;
			end_loop_34:
			  incff_1_arg = number_of_uncached_elements;
			  temp_1 = FIXNUM_ADD(ISVREF(resumable_node,
				  (SI_Long)25L),incff_1_arg);
			  SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
			  temp_1 = ISVREF(history,(SI_Long)2L);
			  SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
			  SVREF(resumable_node,FIX((SI_Long)27L)) = 
				  identical_timestamp_count;
			  if ( !FIXNUM_GE(ISVREF(resumable_node,
				  (SI_Long)25L),ISVREF(resumable_node,
				  (SI_Long)18L))) {
			      result = get_following_history_timestamp(history,
				      timestamp_vector,ring_index,
				      FIX((SI_Long)1L));
			      MVS_2(result,first_uncached_index,
				      managed_timestamp);
			      SVREF(resumable_node,FIX((SI_Long)24L)) = 
				      first_uncached_index;
			      SVREF(resumable_node,FIX((SI_Long)26L)) = 
				      managed_timestamp;
			  }
			  if (uncached_interning_details_qm)
			      reclaim_icp_tree_1(uncached_interning_details_qm);
			POP_SPECIAL();
		    }
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else if (EQ(element_type,Qinteger)) {
	    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
	    identical_timestamp_count = FIX((SI_Long)0L);
	    ring_index = ring_index_of_first_uncached_element;
	    timestamp = Nil;
	    previous_timestamp_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		    0);
	      value = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_35:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_35;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  ring_index = FIXNUM_EQ(ring_index,
			  FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(timestamp_vector,IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(value_vector,
		      IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      write_icp_history_timestamp(timestamp);
	      write_icp_fixnum(value);
	      if (Previous_timestamp_qm && evaluation_value_eql(2,
		      Previous_timestamp_qm,timestamp))
		  identical_timestamp_count = 
			  FIXNUM_ADD1(identical_timestamp_count);
	      else
		  identical_timestamp_count = FIX((SI_Long)0L);
	      Previous_timestamp_qm = timestamp;
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_35;
	    end_loop_35:
	      incff_1_arg = number_of_uncached_elements;
	      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		      incff_1_arg);
	      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	      temp_1 = ISVREF(history,(SI_Long)2L);
	      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
	      SVREF(resumable_node,FIX((SI_Long)27L)) = 
		      identical_timestamp_count;
	      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		      ISVREF(resumable_node,(SI_Long)18L))) {
		  result = get_following_history_timestamp(history,
			  timestamp_vector,ring_index,FIX((SI_Long)1L));
		  MVS_2(result,first_uncached_index,managed_timestamp);
		  SVREF(resumable_node,FIX((SI_Long)24L)) = 
			  first_uncached_index;
		  SVREF(resumable_node,FIX((SI_Long)26L)) = managed_timestamp;
	      }
	      if (uncached_interning_details_qm)
		  reclaim_icp_tree_1(uncached_interning_details_qm);
	    POP_SPECIAL();
	}
	else if (EQ(element_type,QFLOAT)) {
	    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
	    identical_timestamp_count = FIX((SI_Long)0L);
	    ring_index = ring_index_of_first_uncached_element;
	    timestamp = Nil;
	    previous_timestamp_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		    0);
	      value = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_36:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_36;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  ring_index = FIXNUM_EQ(ring_index,
			  FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(timestamp_vector,IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(value_vector,
		      IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      write_icp_history_timestamp(timestamp);
	      temp = DOUBLE_FLOAT_TO_DOUBLE(value);
	      write_icp_double_float_1(temp);
	      if (Previous_timestamp_qm && evaluation_value_eql(2,
		      Previous_timestamp_qm,timestamp))
		  identical_timestamp_count = 
			  FIXNUM_ADD1(identical_timestamp_count);
	      else
		  identical_timestamp_count = FIX((SI_Long)0L);
	      Previous_timestamp_qm = timestamp;
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_36;
	    end_loop_36:
	      incff_1_arg = number_of_uncached_elements;
	      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		      incff_1_arg);
	      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	      temp_1 = ISVREF(history,(SI_Long)2L);
	      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
	      SVREF(resumable_node,FIX((SI_Long)27L)) = 
		      identical_timestamp_count;
	      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		      ISVREF(resumable_node,(SI_Long)18L))) {
		  result = get_following_history_timestamp(history,
			  timestamp_vector,ring_index,FIX((SI_Long)1L));
		  MVS_2(result,first_uncached_index,managed_timestamp);
		  SVREF(resumable_node,FIX((SI_Long)24L)) = 
			  first_uncached_index;
		  SVREF(resumable_node,FIX((SI_Long)26L)) = managed_timestamp;
	      }
	      if (uncached_interning_details_qm)
		  reclaim_icp_tree_1(uncached_interning_details_qm);
	    POP_SPECIAL();
	}
	else if (EQ(element_type,Qtext)) {
	    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
	    identical_timestamp_count = FIX((SI_Long)0L);
	    ring_index = ring_index_of_first_uncached_element;
	    timestamp = Nil;
	    previous_timestamp_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		    0);
	      value = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_37:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_37;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  ring_index = FIXNUM_EQ(ring_index,
			  FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(timestamp_vector,IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(value_vector,
		      IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      write_icp_history_timestamp(timestamp);
	      write_icp_text_string(value);
	      if (Previous_timestamp_qm && evaluation_value_eql(2,
		      Previous_timestamp_qm,timestamp))
		  identical_timestamp_count = 
			  FIXNUM_ADD1(identical_timestamp_count);
	      else
		  identical_timestamp_count = FIX((SI_Long)0L);
	      Previous_timestamp_qm = timestamp;
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_37;
	    end_loop_37:
	      incff_1_arg = number_of_uncached_elements;
	      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		      incff_1_arg);
	      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	      temp_1 = ISVREF(history,(SI_Long)2L);
	      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
	      SVREF(resumable_node,FIX((SI_Long)27L)) = 
		      identical_timestamp_count;
	      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		      ISVREF(resumable_node,(SI_Long)18L))) {
		  result = get_following_history_timestamp(history,
			  timestamp_vector,ring_index,FIX((SI_Long)1L));
		  MVS_2(result,first_uncached_index,managed_timestamp);
		  SVREF(resumable_node,FIX((SI_Long)24L)) = 
			  first_uncached_index;
		  SVREF(resumable_node,FIX((SI_Long)26L)) = managed_timestamp;
	      }
	      if (uncached_interning_details_qm)
		  reclaim_icp_tree_1(uncached_interning_details_qm);
	    POP_SPECIAL();
	}
	else if (EQ(element_type,Qtruth)) {
	    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
	    identical_timestamp_count = FIX((SI_Long)0L);
	    ring_index = ring_index_of_first_uncached_element;
	    timestamp = Nil;
	    previous_timestamp_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		    0);
	      value = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_38:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_38;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  ring_index = FIXNUM_EQ(ring_index,
			  FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(timestamp_vector,IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(value_vector,
		      IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      write_icp_history_timestamp(timestamp);
	      write_icp_evaluation_truth_value(value);
	      if (Previous_timestamp_qm && evaluation_value_eql(2,
		      Previous_timestamp_qm,timestamp))
		  identical_timestamp_count = 
			  FIXNUM_ADD1(identical_timestamp_count);
	      else
		  identical_timestamp_count = FIX((SI_Long)0L);
	      Previous_timestamp_qm = timestamp;
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_38;
	    end_loop_38:
	      incff_1_arg = number_of_uncached_elements;
	      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		      incff_1_arg);
	      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	      temp_1 = ISVREF(history,(SI_Long)2L);
	      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
	      SVREF(resumable_node,FIX((SI_Long)27L)) = 
		      identical_timestamp_count;
	      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		      ISVREF(resumable_node,(SI_Long)18L))) {
		  result = get_following_history_timestamp(history,
			  timestamp_vector,ring_index,FIX((SI_Long)1L));
		  MVS_2(result,first_uncached_index,managed_timestamp);
		  SVREF(resumable_node,FIX((SI_Long)24L)) = 
			  first_uncached_index;
		  SVREF(resumable_node,FIX((SI_Long)26L)) = managed_timestamp;
	      }
	      if (uncached_interning_details_qm)
		  reclaim_icp_tree_1(uncached_interning_details_qm);
	    POP_SPECIAL();
	}
	else if (EQ(element_type,Qsymbol)) {
	    ab_loop_repeat_ = IFIX(number_of_uncached_elements);
	    identical_timestamp_count = FIX((SI_Long)0L);
	    ring_index = ring_index_of_first_uncached_element;
	    timestamp = Nil;
	    previous_timestamp_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		    0);
	      value = Nil;
	      next_interning_index_qm = CAAR(uncached_interning_details_qm);
	      corresponding_index_qm = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_39:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_39;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  ring_index = FIXNUM_EQ(ring_index,
			  FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	      timestamp = FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(timestamp_vector,IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(timestamp_vector,(IFIX(ring_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      value = FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(value_vector,
		      IFIX(FIXNUM_ADD(ring_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(value_vector,(IFIX(ring_index) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),IFIX(ring_index) & 
		      (SI_Long)1023L);
	      if (next_interning_index_qm && 
		      FIXNUM_EQ(next_interning_index_qm,ring_index)) {
		  temp_2 = CDAR(uncached_interning_details_qm);
		  icp_pop_store = Nil;
		  cons_1 = uncached_interning_details_qm;
		  if (cons_1) {
		      icp_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qicp);
		      if (ISVREF(Available_icp_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_1 = ISVREF(Available_icp_conses_tail_vector,
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
		  uncached_interning_details_qm = next_cons;
		  reclaim_icp_cons_1(icp_pop_store);
		  next_interning_index_qm = 
			  CAAR(uncached_interning_details_qm);
		  corresponding_index_qm = temp_2;
	      }
	      else
		  corresponding_index_qm = Nil;
	      write_icp_history_timestamp(timestamp);
	      write_icp_possibly_interned_symbol(value,corresponding_index_qm);
	      if (Previous_timestamp_qm && evaluation_value_eql(2,
		      Previous_timestamp_qm,timestamp))
		  identical_timestamp_count = 
			  FIXNUM_ADD1(identical_timestamp_count);
	      else
		  identical_timestamp_count = FIX((SI_Long)0L);
	      Previous_timestamp_qm = timestamp;
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_39;
	    end_loop_39:
	      incff_1_arg = number_of_uncached_elements;
	      temp_1 = FIXNUM_ADD(ISVREF(resumable_node,(SI_Long)25L),
		      incff_1_arg);
	      SVREF(resumable_node,FIX((SI_Long)25L)) = temp_1;
	      temp_1 = ISVREF(history,(SI_Long)2L);
	      SVREF(resumable_node,FIX((SI_Long)23L)) = temp_1;
	      SVREF(resumable_node,FIX((SI_Long)27L)) = 
		      identical_timestamp_count;
	      if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		      ISVREF(resumable_node,(SI_Long)18L))) {
		  result = get_following_history_timestamp(history,
			  timestamp_vector,ring_index,FIX((SI_Long)1L));
		  MVS_2(result,first_uncached_index,managed_timestamp);
		  SVREF(resumable_node,FIX((SI_Long)24L)) = 
			  first_uncached_index;
		  SVREF(resumable_node,FIX((SI_Long)26L)) = managed_timestamp;
	      }
	      if (uncached_interning_details_qm)
		  reclaim_icp_tree_1(uncached_interning_details_qm);
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

/* G2-RECEIVE-ADD-HISTORY-RANGE */
Object g2_receive_add_history_range(timestamps_use_float_array_p,
	    values_use_float_array_p,number_of_elements)
    Object timestamps_use_float_array_p, values_use_float_array_p;
    Object number_of_elements;
{
    Object history_item, history, timestamp_vector, value_vector;
    Object new_managed_array, element_index, temp, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float, index_1;
    Object ring_buffer, ring_index, ab_loop_iter_flag_, value_1, timestamp_1;
    SI_Long temp_3, ab_loop_repeat_, starting_newest_ring_index;
    double aref_new_value, timestamp, value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(168,17);
    history_item = ISVREF(Current_receiving_resumable_object,(SI_Long)8L);
    history = get_history_ring_buffer_if_any(history_item,Nil);
    timestamp_vector = ISVREF(history,(SI_Long)7L);
    value_vector = ISVREF(history,(SI_Long)6L);
    if ( !TRUEP(timestamps_use_float_array_p)) {
	if (SIMPLE_VECTOR_P(timestamp_vector) && 
		EQ(ISVREF(timestamp_vector,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    new_managed_array = allocate_managed_array(1,
		    ISVREF(timestamp_vector,(SI_Long)1L));
	    if ( !TRUEP(ISVREF(history,(SI_Long)3L))) {
		element_index = ISVREF(history,(SI_Long)2L);
	      next_loop:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_2 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    SVREF(new_managed_array,temp) = new_float;
		}
		else {
		    temp = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_2 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    ISVREF(temp,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(history,(SI_Long)1L)))
		    goto end_loop;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		goto next_loop;
	      end_loop:;
	    }
	    reclaim_managed_float_array(timestamp_vector);
	    SVREF(history,FIX((SI_Long)7L)) = new_managed_array;
	}
    }
    if ( !TRUEP(values_use_float_array_p)) {
	if (SIMPLE_VECTOR_P(value_vector) && EQ(ISVREF(value_vector,
		(SI_Long)0L),Managed_float_array_unique_marker)) {
	    new_managed_array = allocate_managed_array(1,
		    ISVREF(value_vector,(SI_Long)1L));
	    if ( !TRUEP(ISVREF(history,(SI_Long)3L))) {
		element_index = ISVREF(history,(SI_Long)2L);
	      next_loop_1:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_2 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_vector,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    SVREF(new_managed_array,temp) = new_float;
		}
		else {
		    temp = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_2 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_vector,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    ISVREF(temp,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(history,(SI_Long)1L)))
		    goto end_loop_1;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		goto next_loop_1;
	      end_loop_1:;
	    }
	    reclaim_managed_float_array(value_vector);
	    SVREF(history,FIX((SI_Long)6L)) = new_managed_array;
	}
    }
    if (timestamps_use_float_array_p || values_use_float_array_p) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (timestamps_use_float_array_p && values_use_float_array_p) {
		if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    ab_loop_iter_flag_ = T;
		  next_loop_2:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_2;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    read_icp_double_float_1();
		    read_icp_double_float_1();
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_2;
		  end_loop_2:;
		}
		else {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    ab_loop_iter_flag_ = T;
		  next_loop_3:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_3;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = read_icp_double_float_1();
		    value = read_icp_double_float_1();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    DFLOAT_ISASET_1(temp,temp_3,timestamp);
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    DFLOAT_ISASET_1(temp,temp_3,value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_3;
		  end_loop_3:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		}
	    }
	    else if (timestamps_use_float_array_p) {
		if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    ab_loop_iter_flag_ = T;
		  next_loop_4:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_4;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    read_icp_double_float_1();
		    read_icp_attribute_value();
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_4;
		  end_loop_4:;
		}
		else {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    ab_loop_iter_flag_ = T;
		  next_loop_5:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_5;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = read_icp_double_float_1();
		    value_1 = read_icp_attribute_value();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    DFLOAT_ISASET_1(temp,temp_3,timestamp);
		    if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(value_vector,temp) = value_1;
		    }
		    else {
			temp = ISVREF(value_vector,(IFIX(ring_index) >>  - 
				 - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = value_1;
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_5;
		  end_loop_5:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		}
	    }
	    else if (values_use_float_array_p) {
		if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    ab_loop_iter_flag_ = T;
		  next_loop_6:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_6;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    read_icp_history_timestamp();
		    read_icp_double_float_1();
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_6;
		  end_loop_6:;
		}
		else {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    ab_loop_iter_flag_ = T;
		  next_loop_7:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_7;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp_1 = read_icp_history_timestamp();
		    value = read_icp_double_float_1();
		    if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(timestamp_vector,temp) = timestamp_1;
		    }
		    else {
			temp = ISVREF(timestamp_vector,(IFIX(ring_index) 
				>>  -  - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = timestamp_1;
		    }
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    DFLOAT_ISASET_1(temp,temp_3,value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_7;
		  end_loop_7:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		}
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = ISVREF(history,(SI_Long)1L);
	ring_buffer = history;
	starting_newest_ring_index = FIXNUM_EQ(index_1,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	ring_index = FIX(starting_newest_ring_index);
	ab_loop_iter_flag_ = T;
      next_loop_8:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_8;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history,
		    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		    FIXNUM_ADD1(ring_index);
	read_icp_history_timestamp();
	read_icp_attribute_value();
	ab_loop_iter_flag_ = Nil;
	goto next_loop_8;
      end_loop_8:;
    }
    else {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = ISVREF(history,(SI_Long)1L);
	ring_buffer = history;
	starting_newest_ring_index = FIXNUM_EQ(index_1,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	ring_index = FIX(starting_newest_ring_index);
	ab_loop_iter_flag_ = T;
      next_loop_9:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_9;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history,
		    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		    FIXNUM_ADD1(ring_index);
	timestamp_1 = read_icp_history_timestamp();
	value_1 = read_icp_attribute_value();
	if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(timestamp_vector,temp) = timestamp_1;
	}
	else {
	    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = timestamp_1;
	}
	if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(value_vector,temp) = value_1;
	}
	else {
	    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = value_1;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_9;
      end_loop_9:
	SVREF(history,FIX((SI_Long)1L)) = ring_index;
    }
    return VALUES_1(Nil);
}

/* G2-RECEIVE-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object g2_receive_add_homogeneous_history_range(timestamps_use_float_array_p,
	    element_type,number_of_elements)
    Object timestamps_use_float_array_p, element_type, number_of_elements;
{
    Object history_item, history, timestamp_vector, value_vector;
    Object new_managed_array, element_index, temp, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float, index_1;
    Object ring_buffer, ring_index, ab_loop_iter_flag_, timestamp, value;
    SI_Long temp_3, ab_loop_repeat_, starting_newest_ring_index;
    char values_use_float_array_p;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(168,18);
    history_item = ISVREF(Current_receiving_resumable_object,(SI_Long)8L);
    history = get_history_ring_buffer_if_any(history_item,Nil);
    timestamp_vector = ISVREF(history,(SI_Long)7L);
    value_vector = ISVREF(history,(SI_Long)6L);
    if ( !TRUEP(timestamps_use_float_array_p)) {
	if (SIMPLE_VECTOR_P(timestamp_vector) && 
		EQ(ISVREF(timestamp_vector,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    new_managed_array = allocate_managed_array(1,
		    ISVREF(timestamp_vector,(SI_Long)1L));
	    if ( !TRUEP(ISVREF(history,(SI_Long)3L))) {
		element_index = ISVREF(history,(SI_Long)2L);
	      next_loop:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_2 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    SVREF(new_managed_array,temp) = new_float;
		}
		else {
		    temp = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_2 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    DFLOAT_ISAREF_1(ISVREF(timestamp_vector,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    ISVREF(temp,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(history,(SI_Long)1L)))
		    goto end_loop;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		goto next_loop;
	      end_loop:;
	    }
	    reclaim_managed_float_array(timestamp_vector);
	    SVREF(history,FIX((SI_Long)7L)) = new_managed_array;
	}
    }
    values_use_float_array_p = EQ(element_type,QFLOAT);
    if (timestamps_use_float_array_p || values_use_float_array_p) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (timestamps_use_float_array_p && values_use_float_array_p) {
		if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_1:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_1;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_fixnum();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_1;
		      end_loop_1:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_2:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_2;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_double_float_1();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_2;
		      end_loop_2:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_3:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_3;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_text_string();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_3;
		      end_loop_3:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_4:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_4;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_fixnum();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_4;
		      end_loop_4:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_5:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_5;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_possibly_interned_symbol();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_5;
		      end_loop_5:
			result = VALUES_1(Qnil);
		    }
		    else
			result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qinteger)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_6:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_6;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_fixnum();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_6;
		  end_loop_6:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,QFLOAT)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_7:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_7;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_7;
		  end_loop_7:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qtext)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_8:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_8;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_text_string();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_8;
		  end_loop_8:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qtruth)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_9:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_9;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_fixnum();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_9;
		  end_loop_9:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qsymbol)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_10:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_10;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_possibly_interned_symbol();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_10;
		  end_loop_10:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else
		    result = VALUES_1(Qnil);
	    }
	    else if (timestamps_use_float_array_p) {
		if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_11:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_11;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_fixnum();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_11;
		      end_loop_11:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_12:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_12;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_double_float_1();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_12;
		      end_loop_12:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_13:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_13;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_text_string();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_13;
		      end_loop_13:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_14:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_14;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_fixnum();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_14;
		      end_loop_14:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_15:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_15;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_double_float_1();
			read_icp_possibly_interned_symbol();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_15;
		      end_loop_15:
			result = VALUES_1(Qnil);
		    }
		    else
			result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qinteger)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_16:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_16;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_fixnum();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(value_vector,temp) = value;
		    }
		    else {
			temp = ISVREF(value_vector,(IFIX(ring_index) >>  - 
				 - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = value;
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_16;
		  end_loop_16:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,QFLOAT)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_17:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_17;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(value_vector,temp) = value;
		    }
		    else {
			temp = ISVREF(value_vector,(IFIX(ring_index) >>  - 
				 - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = value;
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_17;
		  end_loop_17:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qtext)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_18:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_18;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_text_string();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(value_vector,temp) = value;
		    }
		    else {
			temp = ISVREF(value_vector,(IFIX(ring_index) >>  - 
				 - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = value;
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_18;
		  end_loop_18:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qtruth)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_19:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_19;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_fixnum();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(value_vector,temp) = value;
		    }
		    else {
			temp = ISVREF(value_vector,(IFIX(ring_index) >>  - 
				 - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = value;
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_19;
		  end_loop_19:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qsymbol)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_20:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_20;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    value = read_icp_possibly_interned_symbol();
		    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(value_vector,temp) = value;
		    }
		    else {
			temp = ISVREF(value_vector,(IFIX(ring_index) >>  - 
				 - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = value;
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_20;
		  end_loop_20:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else
		    result = VALUES_1(Qnil);
	    }
	    else if (values_use_float_array_p) {
		if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
		    if (EQ(element_type,Qinteger)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_21:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_21;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_history_timestamp();
			read_icp_fixnum();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_21;
		      end_loop_21:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,QFLOAT)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_22:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_22;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_history_timestamp();
			read_icp_double_float_1();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_22;
		      end_loop_22:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qtext)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_23:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_23;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_history_timestamp();
			read_icp_text_string();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_23;
		      end_loop_23:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qtruth)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_24:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_24;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_history_timestamp();
			read_icp_fixnum();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_24;
		      end_loop_24:
			result = VALUES_1(Qnil);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			ab_loop_repeat_ = IFIX(number_of_elements);
			index_1 = ISVREF(history,(SI_Long)1L);
			ring_buffer = history;
			starting_newest_ring_index = FIXNUM_EQ(index_1,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? (SI_Long)0L : 
				IFIX(FIXNUM_ADD1(index_1));
			ring_index = FIX(starting_newest_ring_index);
			ab_loop_iter_flag_ = T;
		      next_loop_25:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_25;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			if ( !TRUEP(ab_loop_iter_flag_))
			    ring_index = FIXNUM_EQ(ring_index,
				    FIXNUM_SUB1(ISVREF(history,
				    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
				    FIXNUM_ADD1(ring_index);
			read_icp_history_timestamp();
			read_icp_possibly_interned_symbol();
			ab_loop_iter_flag_ = Nil;
			goto next_loop_25;
		      end_loop_25:
			result = VALUES_1(Qnil);
		    }
		    else
			result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qinteger)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_26:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_26;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = read_icp_history_timestamp();
		    value = read_icp_fixnum();
		    if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(timestamp_vector,temp) = timestamp;
		    }
		    else {
			temp = ISVREF(timestamp_vector,(IFIX(ring_index) 
				>>  -  - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = timestamp;
		    }
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_26;
		  end_loop_26:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,QFLOAT)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_27:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_27;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = read_icp_history_timestamp();
		    value = DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(timestamp_vector,temp) = timestamp;
		    }
		    else {
			temp = ISVREF(timestamp_vector,(IFIX(ring_index) 
				>>  -  - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = timestamp;
		    }
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_27;
		  end_loop_27:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qtext)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_28:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_28;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = read_icp_history_timestamp();
		    value = read_icp_text_string();
		    if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(timestamp_vector,temp) = timestamp;
		    }
		    else {
			temp = ISVREF(timestamp_vector,(IFIX(ring_index) 
				>>  -  - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = timestamp;
		    }
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_28;
		  end_loop_28:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qtruth)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_29:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_29;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = read_icp_history_timestamp();
		    value = read_icp_fixnum();
		    if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(timestamp_vector,temp) = timestamp;
		    }
		    else {
			temp = ISVREF(timestamp_vector,(IFIX(ring_index) 
				>>  -  - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = timestamp;
		    }
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_29;
		  end_loop_29:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else if (EQ(element_type,Qsymbol)) {
		    ab_loop_repeat_ = IFIX(number_of_elements);
		    index_1 = ISVREF(history,(SI_Long)1L);
		    ring_buffer = history;
		    starting_newest_ring_index = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ring_index = FIX(starting_newest_ring_index);
		    timestamp = Nil;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_30:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_30;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			ring_index = FIXNUM_EQ(ring_index,
				FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ?
				 FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
		    timestamp = read_icp_history_timestamp();
		    value = read_icp_possibly_interned_symbol();
		    if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp = FIXNUM_ADD(ring_index,
				Managed_array_index_offset);
			SVREF(timestamp_vector,temp) = timestamp;
		    }
		    else {
			temp = ISVREF(timestamp_vector,(IFIX(ring_index) 
				>>  -  - (SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(ring_index) & (SI_Long)1023L;
			ISVREF(temp,temp_3) = timestamp;
		    }
		    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp,temp_3,aref_new_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_30;
		  end_loop_30:
		    SVREF(history,FIX((SI_Long)1L)) = ring_index;
		    result = VALUES_1(Qnil);
		}
		else
		    result = VALUES_1(Qnil);
	    }
	    else
		result = VALUES_1(Qnil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
	if (EQ(element_type,Qinteger)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = ISVREF(history,(SI_Long)1L);
	    ring_buffer = history;
	    starting_newest_ring_index = FIXNUM_EQ(index_1,
		    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		    (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	    ring_index = FIX(starting_newest_ring_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_31:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_31;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		ring_index = FIXNUM_EQ(ring_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	    read_icp_history_timestamp();
	    read_icp_fixnum();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_31;
	  end_loop_31:
	    return VALUES_1(Qnil);
	}
	else if (EQ(element_type,QFLOAT)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = ISVREF(history,(SI_Long)1L);
	    ring_buffer = history;
	    starting_newest_ring_index = FIXNUM_EQ(index_1,
		    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		    (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	    ring_index = FIX(starting_newest_ring_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_32:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_32;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		ring_index = FIXNUM_EQ(ring_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	    read_icp_history_timestamp();
	    read_icp_double_float_1();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_32;
	  end_loop_32:
	    return VALUES_1(Qnil);
	}
	else if (EQ(element_type,Qtext)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = ISVREF(history,(SI_Long)1L);
	    ring_buffer = history;
	    starting_newest_ring_index = FIXNUM_EQ(index_1,
		    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		    (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	    ring_index = FIX(starting_newest_ring_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_33:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_33;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		ring_index = FIXNUM_EQ(ring_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	    read_icp_history_timestamp();
	    read_icp_text_string();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_33;
	  end_loop_33:
	    return VALUES_1(Qnil);
	}
	else if (EQ(element_type,Qtruth)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = ISVREF(history,(SI_Long)1L);
	    ring_buffer = history;
	    starting_newest_ring_index = FIXNUM_EQ(index_1,
		    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		    (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	    ring_index = FIX(starting_newest_ring_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_34:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_34;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		ring_index = FIXNUM_EQ(ring_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	    read_icp_history_timestamp();
	    read_icp_fixnum();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_34;
	  end_loop_34:
	    return VALUES_1(Qnil);
	}
	else if (EQ(element_type,Qsymbol)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = ISVREF(history,(SI_Long)1L);
	    ring_buffer = history;
	    starting_newest_ring_index = FIXNUM_EQ(index_1,
		    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		    (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	    ring_index = FIX(starting_newest_ring_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_35:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_35;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		ring_index = FIXNUM_EQ(ring_index,
			FIXNUM_SUB1(ISVREF(history,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(ring_index);
	    read_icp_history_timestamp();
	    read_icp_possibly_interned_symbol();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_35;
	  end_loop_35:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(element_type,Qinteger)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = ISVREF(history,(SI_Long)1L);
	ring_buffer = history;
	starting_newest_ring_index = FIXNUM_EQ(index_1,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	ring_index = FIX(starting_newest_ring_index);
	timestamp = Nil;
	value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_36:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_36;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history,
		    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		    FIXNUM_ADD1(ring_index);
	timestamp = read_icp_history_timestamp();
	value = read_icp_fixnum();
	if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(timestamp_vector,temp) = timestamp;
	}
	else {
	    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = timestamp;
	}
	if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(value_vector,temp) = value;
	}
	else {
	    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = value;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_36;
      end_loop_36:
	SVREF(history,FIX((SI_Long)1L)) = ring_index;
	return VALUES_1(Qnil);
    }
    else if (EQ(element_type,QFLOAT)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = ISVREF(history,(SI_Long)1L);
	ring_buffer = history;
	starting_newest_ring_index = FIXNUM_EQ(index_1,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	ring_index = FIX(starting_newest_ring_index);
	timestamp = Nil;
	value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_37:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_37;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history,
		    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		    FIXNUM_ADD1(ring_index);
	timestamp = read_icp_history_timestamp();
	value = DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
	if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(timestamp_vector,temp) = timestamp;
	}
	else {
	    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = timestamp;
	}
	if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(value_vector,temp) = value;
	}
	else {
	    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = value;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_37;
      end_loop_37:
	SVREF(history,FIX((SI_Long)1L)) = ring_index;
	return VALUES_1(Qnil);
    }
    else if (EQ(element_type,Qtext)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = ISVREF(history,(SI_Long)1L);
	ring_buffer = history;
	starting_newest_ring_index = FIXNUM_EQ(index_1,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	ring_index = FIX(starting_newest_ring_index);
	timestamp = Nil;
	value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_38:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_38;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history,
		    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		    FIXNUM_ADD1(ring_index);
	timestamp = read_icp_history_timestamp();
	value = read_icp_text_string();
	if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(timestamp_vector,temp) = timestamp;
	}
	else {
	    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = timestamp;
	}
	if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(value_vector,temp) = value;
	}
	else {
	    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = value;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_38;
      end_loop_38:
	SVREF(history,FIX((SI_Long)1L)) = ring_index;
	return VALUES_1(Qnil);
    }
    else if (EQ(element_type,Qtruth)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = ISVREF(history,(SI_Long)1L);
	ring_buffer = history;
	starting_newest_ring_index = FIXNUM_EQ(index_1,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	ring_index = FIX(starting_newest_ring_index);
	timestamp = Nil;
	value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_39:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_39;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history,
		    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		    FIXNUM_ADD1(ring_index);
	timestamp = read_icp_history_timestamp();
	value = read_icp_fixnum();
	if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(timestamp_vector,temp) = timestamp;
	}
	else {
	    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = timestamp;
	}
	if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(value_vector,temp) = value;
	}
	else {
	    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = value;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_39;
      end_loop_39:
	SVREF(history,FIX((SI_Long)1L)) = ring_index;
	return VALUES_1(Qnil);
    }
    else if (EQ(element_type,Qsymbol)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = ISVREF(history,(SI_Long)1L);
	ring_buffer = history;
	starting_newest_ring_index = FIXNUM_EQ(index_1,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	ring_index = FIX(starting_newest_ring_index);
	timestamp = Nil;
	value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_40:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_40;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ring_index = FIXNUM_EQ(ring_index,FIXNUM_SUB1(ISVREF(history,
		    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		    FIXNUM_ADD1(ring_index);
	timestamp = read_icp_history_timestamp();
	value = read_icp_possibly_interned_symbol();
	if (FIXNUM_LE(ISVREF(timestamp_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(timestamp_vector,temp) = timestamp;
	}
	else {
	    temp = ISVREF(timestamp_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = timestamp;
	}
	if (FIXNUM_LE(ISVREF(value_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(ring_index,Managed_array_index_offset);
	    SVREF(value_vector,temp) = value;
	}
	else {
	    temp = ISVREF(value_vector,(IFIX(ring_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_3 = IFIX(ring_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_3) = value;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_40;
      end_loop_40:
	SVREF(history,FIX((SI_Long)1L)) = ring_index;
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

/* G2-WRITE-HISTORY-TIMESTAMP */
Object g2_write_history_timestamp(history_timestamp)
    Object history_timestamp;
{
    x_note_fn_call(168,19);
    if (FIXNUMP(history_timestamp)) {
	write_icp_byte(Attribute_value_integer_tag);
	write_icp_fixnum(history_timestamp);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(history_timestamp) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(history_timestamp)) == 
		(SI_Long)1L) {
	write_icp_byte(Attribute_value_float_tag);
	write_icp_managed_double_float(history_timestamp);
    }
    return VALUES_1(Nil);
}

/* G2-SEND-ADD-VALUE-LIST-RANGE */
Object g2_send_add_value_list_range(number_of_elements,resumable_node,
	    interning_details_qm)
    Object number_of_elements, resumable_node, interning_details_qm;
{
    Object list_element, corresponding_index_qm, next_interning_index_qm;
    Object ab_loop_iter_flag_, icp_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;
    SI_Long list_index, ab_loop_bind_;

    x_note_fn_call(168,20);
    write_icp_fixnum(number_of_elements);
    if (interning_details_qm) {
	list_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_elements);
	list_element = ISVREF(resumable_node,(SI_Long)20L);
	corresponding_index_qm = Nil;
	next_interning_index_qm = CAAR(interning_details_qm);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (list_index > ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	if (next_interning_index_qm && IFIX(next_interning_index_qm) == 
		list_index) {
	    corresponding_index_qm = CDAR(interning_details_qm);
	    icp_pop_store = Nil;
	    cons_1 = interning_details_qm;
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
	    interning_details_qm = next_cons;
	    reclaim_icp_cons_1(icp_pop_store);
	    next_interning_index_qm = CAAR(interning_details_qm);
	}
	else
	    corresponding_index_qm = Nil;
	write_icp_attribute_value(ISVREF(list_element,(SI_Long)4L),
		corresponding_index_qm);
	ab_loop_iter_flag_ = Nil;
	list_index = list_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	SVREF(resumable_node,FIX((SI_Long)20L)) = temp;
	if (interning_details_qm)
	    reclaim_icp_tree_1(interning_details_qm);
    }
    else {
	list_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_elements);
	list_element = ISVREF(resumable_node,(SI_Long)20L);
	corresponding_index_qm = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (list_index > ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	write_icp_attribute_value(ISVREF(list_element,(SI_Long)4L),
		corresponding_index_qm);
	ab_loop_iter_flag_ = Nil;
	list_index = list_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	SVREF(resumable_node,FIX((SI_Long)20L)) = temp;
	if (interning_details_qm)
	    reclaim_icp_tree_1(interning_details_qm);
    }
    return VALUES_1(Nil);
}

static Object Qunexpected_non_value_list;  /* unexpected-non-value-list */

static Object Qpremature_access_to_toplevel_g2_value_list;  /* premature-access-to-toplevel-g2-value-list */

static Object Qg2_value_list_deleted_during_object_passing;  /* g2-value-list-deleted-during-object-passing */

static Object Qvalue_list_contains_an_element_inappropriate_for_receiving_array;  /* value-list-contains-an-element-inappropriate-for-receiving-array */

/* G2-RECEIVE-ADD-VALUE-LIST-RANGE */
Object g2_receive_add_value_list_range(number_of_elements)
    Object number_of_elements;
{
    Object current_subobject_qm, x2, current_subobject_is_frame_p;
    Object sub_class_bit_vector, list_element_type, new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, ab_loop_repeat_;
    char temp;

    x_note_fn_call(168,21);
    current_subobject_qm = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)8L);
    if (SIMPLE_VECTOR_P(current_subobject_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_subobject_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(current_subobject_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(current_subobject_qm,(SI_Long)1L);
	current_subobject_is_frame_p = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_subobject_is_frame_p = Nil;
    if (current_subobject_is_frame_p) {
	sub_class_bit_vector = ISVREF(ISVREF(current_subobject_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Value_list_class_description,(SI_Long)18L));
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
    if (temp);
    else if (current_subobject_is_frame_p)
	record_object_building_problem_on_receiving_side_1(Qunexpected_non_value_list,
		Nil,Nil,ISVREF(ISVREF(current_subobject_qm,(SI_Long)1L),
		(SI_Long)1L),Nil,Nil,Nil);
    else if ( !TRUEP(current_subobject_qm))
	record_object_building_problem_on_receiving_side_1(Qpremature_access_to_toplevel_g2_value_list,
		Nil,Nil,Nil,Nil,Nil,Nil);
    else
	record_object_building_problem_on_receiving_side_1(Qg2_value_list_deleted_during_object_passing,
		Nil,Nil,Nil,Nil,Nil,Nil);
    if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	read_icp_attribute_value();
	goto next_loop;
      end_loop:;
    }
    else {
	list_element_type = ISVREF(current_subobject_qm,(SI_Long)21L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	new_value = Nil;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	new_value = read_icp_attribute_value();
	if (type_specification_type_p(new_value,list_element_type))
	    g2_list_insert_for_object_passing(new_value,current_subobject_qm);
	else {
	    new_value = reclaim_managed_number_or_value_function(new_value);
	    record_object_building_problem_on_receiving_side_1(Qvalue_list_contains_an_element_inappropriate_for_receiving_array,
		    Nil,Nil,ISVREF(ISVREF(current_subobject_qm,
		    (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
	}
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

/* G2-SEND-ADD-HOMOGENEOUS-VALUE-LIST-RANGE */
Object g2_send_add_homogeneous_value_list_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm)
    Object number_of_elements, element_type, resumable_node;
    Object interning_details_qm;
{
    Object list_element, element_value, ab_loop_iter_flag_, temp;
    Object next_interning_index_qm, corresponding_index_qm, temp_1;
    Object icp_pop_store, cons_1, next_cons, svref_arg_2;
    SI_Long list_index, ab_loop_bind_;

    x_note_fn_call(168,22);
    write_icp_fixnum(number_of_elements);
    write_icp_resumable_sequence_element_type(element_type);
    if (EQ(element_type,Qinteger)) {
	list_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_elements);
	list_element = ISVREF(resumable_node,(SI_Long)20L);
	element_value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if (list_index > ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	element_value = ISVREF(list_element,(SI_Long)4L);
	write_icp_fixnum(element_value);
	ab_loop_iter_flag_ = Nil;
	list_index = list_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	SVREF(resumable_node,FIX((SI_Long)20L)) = temp;
	if (interning_details_qm)
	    reclaim_icp_tree_1(interning_details_qm);
    }
    else if (EQ(element_type,QFLOAT)) {
	list_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_elements);
	list_element = ISVREF(resumable_node,(SI_Long)20L);
	element_value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (list_index > ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	element_value = ISVREF(list_element,(SI_Long)4L);
	write_icp_managed_double_float(element_value);
	ab_loop_iter_flag_ = Nil;
	list_index = list_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	SVREF(resumable_node,FIX((SI_Long)20L)) = temp;
	if (interning_details_qm)
	    reclaim_icp_tree_1(interning_details_qm);
    }
    else if (EQ(element_type,Qtext)) {
	list_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_elements);
	list_element = ISVREF(resumable_node,(SI_Long)20L);
	element_value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_2:
	if (list_index > ab_loop_bind_)
	    goto end_loop_2;
	if ( !TRUEP(ab_loop_iter_flag_))
	    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	element_value = ISVREF(list_element,(SI_Long)4L);
	write_icp_text_string(element_value);
	ab_loop_iter_flag_ = Nil;
	list_index = list_index + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	temp = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	SVREF(resumable_node,FIX((SI_Long)20L)) = temp;
	if (interning_details_qm)
	    reclaim_icp_tree_1(interning_details_qm);
    }
    else if (EQ(element_type,Qtruth)) {
	list_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_elements);
	list_element = ISVREF(resumable_node,(SI_Long)20L);
	element_value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_3:
	if (list_index > ab_loop_bind_)
	    goto end_loop_3;
	if ( !TRUEP(ab_loop_iter_flag_))
	    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	element_value = ISVREF(list_element,(SI_Long)4L);
	write_icp_evaluation_truth_value(evaluation_truth_value_value_function(element_value));
	ab_loop_iter_flag_ = Nil;
	list_index = list_index + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:
	temp = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	SVREF(resumable_node,FIX((SI_Long)20L)) = temp;
	if (interning_details_qm)
	    reclaim_icp_tree_1(interning_details_qm);
    }
    else if (EQ(element_type,Qsymbol)) {
	list_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_elements);
	list_element = ISVREF(resumable_node,(SI_Long)20L);
	element_value = Nil;
	next_interning_index_qm = CAAR(interning_details_qm);
	corresponding_index_qm = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_4:
	if (list_index > ab_loop_bind_)
	    goto end_loop_4;
	if ( !TRUEP(ab_loop_iter_flag_))
	    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	element_value = ISVREF(list_element,(SI_Long)4L);
	if (next_interning_index_qm && IFIX(next_interning_index_qm) == 
		list_index) {
	    temp_1 = CDAR(interning_details_qm);
	    icp_pop_store = Nil;
	    cons_1 = interning_details_qm;
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
	    interning_details_qm = next_cons;
	    reclaim_icp_cons_1(icp_pop_store);
	    next_interning_index_qm = CAAR(interning_details_qm);
	    corresponding_index_qm = temp_1;
	}
	else
	    corresponding_index_qm = Nil;
	write_icp_possibly_interned_symbol(element_value,
		corresponding_index_qm);
	ab_loop_iter_flag_ = Nil;
	list_index = list_index + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:
	temp = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
	SVREF(resumable_node,FIX((SI_Long)20L)) = temp;
	if (interning_details_qm)
	    reclaim_icp_tree_1(interning_details_qm);
    }
    return VALUES_1(Nil);
}

/* G2-RECEIVE-ADD-HOMOGENEOUS-VALUE-LIST-RANGE */
Object g2_receive_add_homogeneous_value_list_range(number_of_elements,
	    element_type)
    Object number_of_elements, element_type;
{
    Object current_subobject_qm, x2, current_subobject_is_frame_p;
    Object sub_class_bit_vector, element;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, ab_loop_repeat_;
    char temp;

    x_note_fn_call(168,23);
    current_subobject_qm = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)8L);
    if (SIMPLE_VECTOR_P(current_subobject_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_subobject_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(current_subobject_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(current_subobject_qm,(SI_Long)1L);
	current_subobject_is_frame_p = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_subobject_is_frame_p = Nil;
    if (current_subobject_is_frame_p) {
	sub_class_bit_vector = ISVREF(ISVREF(current_subobject_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Value_list_class_description,(SI_Long)18L));
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
    if (temp);
    else if (current_subobject_is_frame_p)
	record_object_building_problem_on_receiving_side_1(Qunexpected_non_value_list,
		Nil,Nil,ISVREF(ISVREF(current_subobject_qm,(SI_Long)1L),
		(SI_Long)1L),Nil,Nil,Nil);
    else if ( !TRUEP(current_subobject_qm))
	record_object_building_problem_on_receiving_side_1(Qpremature_access_to_toplevel_g2_value_list,
		Nil,Nil,Nil,Nil,Nil,Nil);
    else
	record_object_building_problem_on_receiving_side_1(Qg2_value_list_deleted_during_object_passing,
		Nil,Nil,Nil,Nil,Nil,Nil);
    if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
	if (EQ(element_type,Qinteger)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    read_icp_fixnum();
	    goto next_loop;
	  end_loop:;
	}
	else if (EQ(element_type,QFLOAT)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    read_icp_managed_double_float();
	    goto next_loop_1;
	  end_loop_1:;
	}
	else if (EQ(element_type,Qtext)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_2:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_2;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    read_icp_text_string();
	    goto next_loop_2;
	  end_loop_2:;
	}
	else if (EQ(element_type,Qtruth)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    read_icp_evaluation_truth_value();
	    goto next_loop_3;
	  end_loop_3:;
	}
	else if (EQ(element_type,Qsymbol)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	  next_loop_4:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_4;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    read_icp_possibly_interned_symbol();
	    goto next_loop_4;
	  end_loop_4:;
	}
    }
    else if (EQ(element_type,Qinteger)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	element = Nil;
      next_loop_5:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_5;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	element = read_icp_fixnum();
	g2_list_insert_for_object_passing(element,current_subobject_qm);
	goto next_loop_5;
      end_loop_5:;
    }
    else if (EQ(element_type,QFLOAT)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	element = Nil;
      next_loop_6:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_6;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	element = read_icp_managed_double_float();
	g2_list_insert_for_object_passing(element,current_subobject_qm);
	goto next_loop_6;
      end_loop_6:;
    }
    else if (EQ(element_type,Qtext)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	element = Nil;
      next_loop_7:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_7;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	element = read_icp_text_string();
	g2_list_insert_for_object_passing(element,current_subobject_qm);
	goto next_loop_7;
      end_loop_7:;
    }
    else if (EQ(element_type,Qtruth)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	element = Nil;
      next_loop_8:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_8;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	element = read_icp_evaluation_truth_value();
	g2_list_insert_for_object_passing(element,current_subobject_qm);
	goto next_loop_8;
      end_loop_8:;
    }
    else if (EQ(element_type,Qsymbol)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	element = Nil;
      next_loop_9:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_9;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	element = read_icp_possibly_interned_symbol();
	g2_list_insert_for_object_passing(element,current_subobject_qm);
	goto next_loop_9;
      end_loop_9:;
    }
    return VALUES_1(Nil);
}

static Object string_constant_6;   /* "A g2-value-list " */

static Object string_constant_7;   /* "has been deleted" */

static Object Qg2_value_list_subobject_deleted;  /* g2-value-list-subobject-deleted */

static Object string_constant_8;   /* "An element of the g2-value-list ~NF " */

static Object string_constant_9;   /* "has been removed" */

static Object Qg2_value_list_element_removed;  /* g2-value-list-element-removed */

/* CHECK-RESUMABLE-VALUE-LIST-CONTENTS */
Object check_resumable_value_list_contents(resumable_node,resumable_object)
    Object resumable_node, resumable_object;
{
    Object current_object, toplevel_object, gensymed_symbol, x, y, xa, ya;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object x2, temp_1, list_element_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(168,24);
    current_object = ISVREF(resumable_node,(SI_Long)4L);
    toplevel_object = ISVREF(resumable_object,(SI_Long)8L);
    gensymed_symbol = ISVREF(current_object,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(current_object) ? EQ(ISVREF(current_object,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(resumable_node,(SI_Long)10L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if (temp) {
	Rpc_throw_tag = Kabort_transmitting_resumable_object;
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
		  tformat(1,string_constant_6);
		  if (SIMPLE_VECTOR_P(toplevel_object) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(toplevel_object)) 
			  > (SI_Long)2L &&  !EQ(ISVREF(toplevel_object,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(toplevel_object,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp ? EQ(current_object,toplevel_object) : TRUEP(Nil))
		      tformat(1,string_constant_1);
		  else {
		      if (SIMPLE_VECTOR_P(toplevel_object) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(toplevel_object)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(toplevel_object,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(toplevel_object,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  tformat(2,string_constant_2,toplevel_object);
		      else;
		  }
		  tformat(1,string_constant_7);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return icp_list_2(Qg2_value_list_subobject_deleted,temp_1);
    }
    list_element_qm = ISVREF(resumable_node,(SI_Long)20L);
    if (list_element_qm) {
	if ( !EQ(ISVREF(list_element_qm,(SI_Long)4L),
		    G2_list_structure_marker)) {
	    temp_1 = ISVREF(list_element_qm,(SI_Long)5L);
	    if ( !EQL(current_object,temp_1)) {
		Rpc_throw_tag = Kabort_transmitting_resumable_object;
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
			  tformat(2,string_constant_8,current_object);
			  if (EQ(current_object,toplevel_object))
			      tformat(1,string_constant_1);
			  else
			      tformat(2,string_constant_2,toplevel_object);
			  tformat(1,string_constant_9);
			  temp_1 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		return icp_list_2(Qg2_value_list_element_removed,temp_1);
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

DEFINE_VARIABLE_WITH_SYMBOL(Minimnal_bandwidth_for_resumable_sequence_range, Qminimnal_bandwidth_for_resumable_sequence_range);

/* TRANSMIT-RESUMABLE-VALUE-LIST-RANGE */
Object transmit_resumable_value_list_range(resumable_node,resumable_object,
	    icp_port)
    Object resumable_node, resumable_object, icp_port;
{
    Object possible_throw_value, element_type_qm, icp_socket;
    Object number_of_elements, bandwidth_needed, elements_remain_p;
    Object interning_details, network_is_limiting_factor_p, temp;
    Object gensymed_symbol, first_1, last_1, temp_1, next, incff_1_arg;
    Object decff_1_arg, svref_new_value;
    Object result;

    x_note_fn_call(168,25);
    if (ISVREF(resumable_node,(SI_Long)20L)) {
	possible_throw_value = 
		check_resumable_value_list_contents(resumable_node,
		resumable_object);
	if (Rpc_throw_tag)
	    return VALUES_1(possible_throw_value);
	element_type_qm = ISVREF(resumable_node,(SI_Long)19L);
	icp_socket = ISVREF(icp_port,(SI_Long)2L);
	result = get_value_list_transmission_info(resumable_node,
		element_type_qm,resumable_object,icp_port);
	MVS_5(result,number_of_elements,bandwidth_needed,elements_remain_p,
		interning_details,network_is_limiting_factor_p);
	possible_throw_value = number_of_elements;
	if (Rpc_throw_tag)
	    return VALUES_1(possible_throw_value);
	if (elements_remain_p && IFIX(number_of_elements) <= (SI_Long)0L) {
	    reclaim_icp_tree_1(interning_details);
	    if (network_is_limiting_factor_p) {
		temp = Minimnal_bandwidth_for_resumable_sequence_range;
		SVREF(resumable_object,FIX((SI_Long)17L)) = temp;
		gensymed_symbol = resumable_object;
		gensymed_symbol = icp_cons_1(gensymed_symbol,Nil);
	      next_loop:
		first_1 = ISVREF(icp_socket,(SI_Long)31L);
		last_1 = ISVREF(icp_socket,(SI_Long)32L);
		temp_1 = ISVREF(icp_socket,(SI_Long)32L);
		next = CDR(temp_1);
		if ( !TRUEP(first_1)) {
		    if (CAS_SVREF(icp_socket,(SI_Long)31L,first_1,
			    gensymed_symbol)) {
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,
				gensymed_symbol);
			goto end_1;
		    }
		}
		else if (EQ(last_1,ISVREF(icp_socket,(SI_Long)32L))) {
		    if ( !TRUEP(next)) {
			if (CAS_CDR(last_1,next,gensymed_symbol)) {
			    CAS_SVREF(icp_socket,(SI_Long)32L,last_1,
				    gensymed_symbol);
			    goto end_1;
			}
		    }
		    else
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,next);
		}
		goto next_loop;
	      end_loop:
	      end_1:;
		possible_throw_value = 
			suspend_object_passing_transmission(3,
			resumable_object,resumable_node,Nil);
		if (Rpc_throw_tag)
		    return VALUES_1(possible_throw_value);
	    }
	    else {
		possible_throw_value = 
			suspend_object_passing_transmission(2,
			resumable_object,resumable_node);
		if (Rpc_throw_tag)
		    return VALUES_1(possible_throw_value);
	    }
	}
	incff_1_arg = bandwidth_needed;
	temp = FIXNUM_ADD(ISVREF(resumable_object,(SI_Long)15L),incff_1_arg);
	SVREF(resumable_object,FIX((SI_Long)15L)) = temp;
	temp = ISVREF(resumable_object,(SI_Long)11L);
	decff_1_arg = bandwidth_needed;
	svref_new_value = FIXNUM_MINUS(ISVREF(temp,(SI_Long)30L),decff_1_arg);
	SVREF(temp,FIX((SI_Long)30L)) = svref_new_value;
	if (elements_remain_p && element_type_qm) {
	    write_icp_add_homogeneous_value_list_range(number_of_elements,
		    element_type_qm,resumable_node,interning_details);
	    possible_throw_value = suspend_object_passing_transmission(2,
		    resumable_object,resumable_node);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    temp_1 = possible_throw_value;
	}
	else if (elements_remain_p) {
	    write_icp_add_value_list_range(number_of_elements,
		    resumable_node,interning_details);
	    possible_throw_value = suspend_object_passing_transmission(2,
		    resumable_object,resumable_node);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    temp_1 = possible_throw_value;
	}
	else if (element_type_qm)
	    temp_1 = 
		    write_icp_add_homogeneous_value_list_range(number_of_elements,
		    element_type_qm,resumable_node,interning_details);
	else
	    temp_1 = write_icp_add_value_list_range(number_of_elements,
		    resumable_node,interning_details);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qvector_element;     /* vector-element */

static Object Qattribute;          /* attribute */

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object list_constant;       /* # */

static Object Qimport_declarations;  /* import-declarations */

static Object Qpackage_declaration;  /* package-declaration */

static Object Qname;               /* name */

static Object Qcurrent_value;      /* current-value */

static Object Qiteration_state;    /* iteration-state */

/* G2-GET-ATTRIBUTE-FOR-OBJECT-PASSING */
Object g2_get_attribute_for_object_passing(object,attribute_name)
    Object object, attribute_name;
{
    Object temp, type, base_name, class_qualifier_qm, x2, gensymed_symbol;
    Object sub_class_bit_vector, raw_value_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_2, entry_hash, car_1, cdr_1;
    Object inner_value, constant_type;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(168,26);
    if (FIXNUMP(attribute_name))
	temp = Qvector_element;
    else if (SYMBOLP(attribute_name))
	temp = Qattribute;
    else if (CONSP(attribute_name)) {
	type = M_CAR(attribute_name);
	temp = EQ(type,Qclass_qualified_name) ? Qattribute : type;
    }
    else
	temp = Qnil;
    if (EQ(temp,Qattribute)) {
	base_name = CONSP(attribute_name) ? THIRD(attribute_name) : 
		attribute_name;
	class_qualifier_qm = CONSP(attribute_name) ? 
		SECOND(attribute_name) : Nil;
	if (memq_function(base_name,list_constant)) {
	    if (EQ(base_name,Qimport_declarations))
		temp = 
			get_import_declarations_system_attribute_for_object_passing(object);
	    else if (EQ(base_name,Qpackage_declaration))
		temp = 
			get_package_declaration_system_attribute_for_object_passing(object);
	    else if (EQ(base_name,Qtext))
		temp = get_text_system_attribute_for_object_passing(object);
	    else if (EQ(base_name,Qname))
		temp = get_name_system_attribute_for_object_passing(object);
	    else if (EQ(base_name,Qcurrent_value))
		temp = 
			get_current_value_system_attribute_for_object_passing(object);
	    else
		temp = Qnil;
	}
	else {
	    if (SIMPLE_VECTOR_P(object) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(object,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(object,(SI_Long)1L);
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
			IFIX(ISVREF(Object_class_description,(SI_Long)18L));
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
	    raw_value_qm = temp_1 ? get_slot_value_if_any_function(object,
		    base_name,class_qualifier_qm) : 
		    frame_or_evaluation_value_user_attribute_value(object,
		    base_name,class_qualifier_qm);
	    gensymed_symbol = raw_value_qm;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
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
	    if (temp_1)
		temp = FIXNUMP(raw_value_qm) || raw_value_qm && 
			SYMBOLP(raw_value_qm) ? raw_value_qm : 
			copy_evaluation_value_1(raw_value_qm);
	    else {
		if (CONSP(raw_value_qm)) {
		    car_1 = M_CAR(raw_value_qm);
		    cdr_1 = M_CDR(raw_value_qm);
		    if (CONSP(cdr_1)) {
			temp = M_CAR(cdr_1);
			temp_1 = SYMBOLP(temp);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
			    text_string_p(car_1) || STRINGP(car_1) : 
			    TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    inner_value = FIRST(raw_value_qm);
		    constant_type = SECOND(raw_value_qm);
		    if (EQ(constant_type,Qtruth_value)) {
			if (FIXNUM_EQ(inner_value,Truth))
			    temp = Evaluation_true_value;
			else if (FIXNUM_EQ(inner_value,Falsity))
			    temp = Evaluation_false_value;
			else
			    temp = eval_cons_1(inner_value,Qtruth_value);
		    }
		    else
			temp = FIXNUMP(inner_value) || inner_value && 
				SYMBOLP(inner_value) ? inner_value : 
				copy_evaluation_value_1(inner_value);
		}
		else
		    temp = raw_value_qm;
	    }
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* G2-WRITE-ICP-ATTRIBUTE-VALUE */
Object g2_write_icp_attribute_value(simple_value,corresponding_index_qm)
    Object simple_value, corresponding_index_qm;
{
    Object evaluation_integer, managed_float, evaluation_text;
    Object evaluation_truth_value, evaluation_symbol, evaluation_sequence;
    Object evaluation_structure;

    x_note_fn_call(168,27);
    if (FIXNUMP(simple_value)) {
	evaluation_integer = simple_value;
	write_icp_byte(Attribute_value_integer_tag);
	write_icp_fixnum(evaluation_integer);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(simple_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simple_value)) == (SI_Long)1L) {
	managed_float = simple_value;
	write_icp_byte(Attribute_value_float_tag);
	write_icp_managed_double_float(managed_float);
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(simple_value) != (SI_Long)0L) {
	evaluation_text = simple_value;
	write_icp_byte(Attribute_value_text_tag);
	write_icp_text_string(evaluation_text);
    }
    else if (CONSP(simple_value) && EQ(M_CDR(simple_value),Qtruth_value)) {
	evaluation_truth_value = M_CAR(simple_value);
	write_icp_byte(Attribute_value_truth_value_tag);
	write_icp_evaluation_truth_value(evaluation_truth_value);
    }
    else if (simple_value && SYMBOLP(simple_value)) {
	evaluation_symbol = simple_value;
	write_icp_possibly_interned_symbol(evaluation_symbol,
		corresponding_index_qm);
    }
    else if (CONSP(simple_value) && EQ(M_CDR(simple_value),Qsequence)) {
	evaluation_sequence = simple_value;
	write_icp_byte(Attribute_value_evaluation_sequence_tag);
	write_icp_evaluation_sequence(evaluation_sequence);
    }
    else if (CONSP(simple_value) && EQ(M_CDR(simple_value),Qab_structure)) {
	evaluation_structure = simple_value;
	write_icp_byte(Attribute_value_evaluation_structure_tag);
	write_icp_evaluation_structure(evaluation_structure);
    }
    else if ( !TRUEP(simple_value))
	write_icp_byte(Attribute_value_null_tag);
    return VALUES_1(Nil);
}

/* G2-MAYBE-CONTINUE-RPC-AFTER-OBJECT-BUILDING */
Object g2_maybe_continue_rpc_after_object_building(rpc_arglist_structure)
    Object rpc_arglist_structure;
{
    Object previous_qm, next_qm;

    x_note_fn_call(168,28);
    previous_qm = ISVREF(Current_receiving_resumable_object,(SI_Long)4L);
    next_qm = ISVREF(Current_receiving_resumable_object,(SI_Long)3L);
    if (previous_qm && next_qm) {
	SVREF(previous_qm,FIX((SI_Long)3L)) = next_qm;
	SVREF(next_qm,FIX((SI_Long)4L)) = previous_qm;
    }
    else if (previous_qm)
	SVREF(previous_qm,FIX((SI_Long)3L)) = next_qm;
    else if (next_qm)
	SVREF(next_qm,FIX((SI_Long)4L)) = Nil;
    else
	g2_continue_rpc_after_final_object_build(rpc_arglist_structure);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;  /* g2-defstruct-structure-name::receiving-resumable-object-g2-struct */

static Object Qobject_passing_info_qm;  /* object-passing-info? */

static Object list_constant_1;     /* # */

static Object Qstart;              /* start */

static Object Qcall;               /* call */

static Object Qoutstanding;        /* outstanding */

static Object Qreturned;           /* returned */

static Object Qole;                /* ole */

static Object Qole_object_passing_in_progress;  /* ole-object-passing-in-progress */

/* G2-CONTINUE-RPC-AFTER-FINAL-OBJECT-BUILD */
Object g2_continue_rpc_after_final_object_build(rpc_arglist_structure)
    Object rpc_arglist_structure;
{
    Object rpc_arglist, arg, ab_loop_list_, problem_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, object, gensymed_symbol;
    Object gensymed_symbol_1, slot_group_qm, svref_arg_1, temp, x2;
    Object converted_rpc_arglist, continuation_tag, temp_2, temp_3;
    Object remote_procedure_identifier, object_passed_by_ole;
    char temp_1;

    x_note_fn_call(168,29);
    rpc_arglist = ISVREF(rpc_arglist_structure,(SI_Long)1L);
    arg = Nil;
    ab_loop_list_ = rpc_arglist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(arg) && EQ(ISVREF(arg,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	problem_qm = ISVREF(arg,(SI_Long)10L);
	if (problem_qm) {
	    deferred_abort_rpc_for_failed_resumable_object(arg,ISVREF(arg,
		    (SI_Long)9L),problem_qm);
	    reclaim_receiving_resumable_object(arg);
	    return VALUES_1(Nil);
	}
    }
    goto next_loop;
  end_loop:;
    arg = Nil;
    ab_loop_list_ = rpc_arglist;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(arg) && EQ(ISVREF(arg,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	object = ISVREF(arg,(SI_Long)7L);
	gensymed_symbol = object;
	gensymed_symbol_1 = Nil;
	slot_group_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qobject_passing_info_qm,Nil);
	note_change_to_block_or_struct_or_seq(gensymed_symbol,
		Qobject_passing_info_qm);
	gensymed_symbol_1 = T;
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,Qt)) {
	    set_non_savable_lookup_slot_value(gensymed_symbol,
		    Qobject_passing_info_qm,make_object_passing_info_1());
	    svref_arg_1 = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = gensymed_symbol_1;
	}
	temp = object;
    }
    else {
	if (SIMPLE_VECTOR_P(arg) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) > 
		(SI_Long)2L &&  !EQ(ISVREF(arg,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(arg,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = arg;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    note_change_to_block_or_struct_or_seq(gensymed_symbol,
		    Qobject_passing_info_qm);
	    gensymed_symbol_1 = T;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qt)) {
		set_non_savable_lookup_slot_value(gensymed_symbol,
			Qobject_passing_info_qm,make_object_passing_info_1());
		svref_arg_1 = 
			get_lookup_slot_value_given_default(gensymed_symbol,
			Qobject_passing_info_qm,Nil);
		SVREF(svref_arg_1,FIX((SI_Long)1L)) = gensymed_symbol_1;
	    }
	}
	temp = arg;
    }
    ab_loopvar__2 = icp_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    converted_rpc_arglist = ab_loopvar_;
    goto end_1;
    converted_rpc_arglist = Qnil;
  end_1:;
    continuation_tag = ISVREF(rpc_arglist_structure,(SI_Long)2L);
    if (memq_function(continuation_tag,list_constant_1)) {
	if (EQ(continuation_tag,Qstart)) {
	    temp = Current_icp_socket;
	    temp_2 = ISVREF(ISVREF(rpc_arglist_structure,(SI_Long)3L),
		    (SI_Long)1L);
	    temp_3 = frame_serial_number_0();
	    receive_start_or_call_remote_procedure(temp,temp_2,
		    icp_cons_1(temp_3,icp_cons_1(Nil,
		    converted_rpc_arglist)),Nil);
	}
	else if (EQ(continuation_tag,Qcall)) {
	    temp = Current_icp_socket;
	    temp_2 = ISVREF(ISVREF(rpc_arglist_structure,(SI_Long)3L),
		    (SI_Long)1L);
	    temp_3 = frame_serial_number_0();
	    receive_start_or_call_remote_procedure(temp,temp_2,
		    icp_cons_1(temp_3,icp_cons_1(Nil,
		    converted_rpc_arglist)),ISVREF(rpc_arglist_structure,
		    (SI_Long)4L));
	}
	else if (EQ(continuation_tag,Qreturn)) {
	    remote_procedure_identifier = 
		    lookup_remote_procedure_identifier_from_index(ISVREF(rpc_arglist_structure,
		    (SI_Long)5L));
	    if (remote_procedure_identifier && EQ(Qoutstanding,
		    ISVREF(remote_procedure_identifier,(SI_Long)6L)))
		SVREF(remote_procedure_identifier,FIX((SI_Long)6L)) = 
			Qreturned;
	    temp = frame_serial_number_0();
	    receive_remote_procedure_values(remote_procedure_identifier,
		    icp_cons_1(temp,icp_cons_1(Nil,converted_rpc_arglist)));
	}
	else if (EQ(continuation_tag,Qole)) {
	    object_passed_by_ole = CAR(converted_rpc_arglist);
	    delete_frame_note_if_any(Qole_object_passing_in_progress,
		    object_passed_by_ole);
	    reclaim_transformed_rpc_argument_list(converted_rpc_arglist,Nil);
	}
    }
    else {
	arg = Nil;
	ab_loop_list_ = converted_rpc_arglist;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(arg) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) > 
		(SI_Long)2L &&  !EQ(ISVREF(arg,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(arg,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = arg;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    note_change_to_block_or_struct_or_seq(gensymed_symbol,
		    Qobject_passing_info_qm);
	    gensymed_symbol_1 = Nil;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qt)) {
		set_non_savable_lookup_slot_value(gensymed_symbol,
			Qobject_passing_info_qm,make_object_passing_info_1());
		svref_arg_1 = 
			get_lookup_slot_value_given_default(gensymed_symbol,
			Qobject_passing_info_qm,Nil);
		SVREF(svref_arg_1,FIX((SI_Long)1L)) = gensymed_symbol_1;
	    }
	}
	goto next_loop_2;
      end_loop_2:;
	reclaim_transformed_rpc_argument_list(converted_rpc_arglist,Nil);
    }
    temp = reclaim_receiving_rpc_arglist_structure_1(rpc_arglist_structure);
    return VALUES_1(temp);
}

static Object string_constant_10;  /* "A remote procedure call to ~A has been aborted " */

static Object string_constant_11;  /* "A remote procedure call has been aborted " */

static Object string_constant_12;  /* "while receiving a subobject of class ~A " */

static Object string_constant_13;  /* "index ~A" */

static Object string_constant_14;  /* "attribute ~A" */

static Object string_constant_15;  /* "at ~A: " */

static Object string_constant_16;  /* "~A.  " */

static Object Qtformat;            /* tformat */

static Object Qproblem_building_rpc_object_arguments;  /* problem-building-rpc-object-arguments */

static Object Qrpc_error;          /* rpc-error */

static Object Qproblem_registering_rpc_object_on_network;  /* problem-registering-rpc-object-on-network */

/* DEFERRED-ABORT-RPC-FOR-FAILED-RESUMABLE-OBJECT */
Object deferred_abort_rpc_for_failed_resumable_object(resumable_object,
	    rpc_arglist,problem)
    Object resumable_object, rpc_arglist, problem;
{
    Object rpc_name_qm, continuation, attribute_name_qm, class_name_qm;
    Object extra_info_format_qm, extra_info_components;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object attribute_substring, temp, error_string;
    Object remote_procedure_identifier_qm, remote_procedure_call_qm, caller_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(168,30);
    rpc_name_qm = ISVREF(resumable_object,(SI_Long)1L);
    continuation = ISVREF(rpc_arglist,(SI_Long)2L);
    attribute_name_qm = ISVREF(problem,(SI_Long)2L);
    class_name_qm = ISVREF(problem,(SI_Long)3L);
    extra_info_format_qm = ISVREF(problem,(SI_Long)4L);
    extra_info_components = ISVREF(problem,(SI_Long)5L);
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
	      if (rpc_name_qm)
		  tformat(2,string_constant_10,rpc_name_qm);
	      else
		  tformat(1,string_constant_11);
	      if (class_name_qm)
		  tformat(2,string_constant_12,class_name_qm);
	      if (attribute_name_qm) {
		  attribute_substring = FIXNUMP(attribute_name_qm) ? 
			  tformat_text_string(2,string_constant_13,
			  attribute_name_qm) : tformat_text_string(2,
			  string_constant_14,attribute_name_qm);
		  tformat(2,string_constant_15,attribute_substring);
		  reclaim_text_string(attribute_substring);
	      }
	      tformat(2,string_constant_16,ISVREF(problem,(SI_Long)1L));
	      if (extra_info_format_qm) {
		  temp = SYMBOL_FUNCTION(Qtformat);
		  APPLY_2(temp,extra_info_format_qm,extra_info_components);
	      }
	      error_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (EQ(continuation,Qstart) || EQ(continuation,Qcall))
	return remote_procedure_error(Current_icp_socket,
		Qproblem_building_rpc_object_arguments,error_string,
		EQ(continuation,Qcall) ? ISVREF(rpc_arglist,(SI_Long)4L) : 
		Nil);
    else if (EQ(continuation,Qreturn)) {
	remote_procedure_identifier_qm = 
		lookup_remote_procedure_identifier_from_index(ISVREF(rpc_arglist,
		(SI_Long)5L));
	if (remote_procedure_identifier_qm) {
	    remote_procedure_call_qm = 
		    ISVREF(remote_procedure_identifier_qm,(SI_Long)3L);
	    if (remote_procedure_call_qm) {
		caller_qm = ISVREF(remote_procedure_call_qm,(SI_Long)12L);
		if (caller_qm)
		    return signal_code_body_invocation_error(9,caller_qm,
			    Qrpc_error,FIX((SI_Long)1L),error_string,Nil,
			    Nil,Nil,Nil,Nil);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return remote_procedure_error(Current_icp_socket,
		Qproblem_registering_rpc_object_on_network,error_string,Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qtry_to_transmit_resumable_object;  /* try-to-transmit-resumable-object */

static Object Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct;  /* g2-defstruct-structure-name::resumable-evaluation-sequence-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct;  /* g2-defstruct-structure-name::resumable-evaluation-structure-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_object_node_g2_struct;  /* g2-defstruct-structure-name::resumable-object-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct;  /* g2-defstruct-structure-name::resumable-object-vector-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct;  /* g2-defstruct-structure-name::resumable-value-vector-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_history_node_g2_struct;  /* g2-defstruct-structure-name::resumable-history-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct;  /* g2-defstruct-structure-name::resumable-object-list-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct;  /* g2-defstruct-structure-name::resumable-value-list-node-g2-struct */

static Object Ksuspend_transmitting_resumable_object;  /* :suspend-transmitting-resumable-object */

/* SUSPEND-OBJECT-PASSING-TRANSMISSION */
Object suspend_object_passing_transmission varargs_1(int, n)
{
    Object resumable_object, current_resumable_node;
    Object reschedule_p, schedule_task_qm, gensymed_symbol;
    Object structure_being_reclaimed, temp, svref_arg_2, old, new_1;
    Object def_structure_schedule_task_variable, svref_new_value, task, ctask;
    Object p, v, q, suspended_resumable_node;
    char g2_p;
    double aref_new_value;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(168,31);
    INIT_ARGS_nonrelocating();
    resumable_object = REQUIRED_ARG_nonrelocating();
    current_resumable_node = REQUIRED_ARG_nonrelocating();
    reschedule_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    write_icp_suspend_building_object(ISVREF(resumable_object,(SI_Long)15L));
    schedule_task_qm = ISVREF(resumable_object,(SI_Long)19L);
    if (schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task))) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(resumable_object,(SI_Long)19L);
	if (CAS_SVREF(resumable_object,(SI_Long)19L,gensymed_symbol,Nil)) {
	    if (gensymed_symbol) {
		if (EQ(gensymed_symbol,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		structure_being_reclaimed = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
	    }
	    goto end_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    if (reschedule_p) {
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = ISVREF(resumable_object,(SI_Long)19L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
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
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	temp = ISVREF(resumable_object,(SI_Long)14L);
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qtry_to_transmit_resumable_object;
	temp = SYMBOL_FUNCTION(Qtry_to_transmit_resumable_object);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = resumable_object;
	new_1 = task;
	if (CAS_SVREF(resumable_object,(SI_Long)19L,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
	    goto end_2;
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_1;
	}
	goto next_loop_1;
      end_loop_1:
      end_2:;
    }
    suspended_resumable_node = SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_resumable_node) && 
	    EQ(ISVREF(current_resumable_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct) 
	    ? current_resumable_node : ISVREF(current_resumable_node,
	    (SI_Long)1L);
    Rpc_throw_tag = Ksuspend_transmitting_resumable_object;
    return VALUES_1(suspended_resumable_node);
}

static Object string_constant_17;  /* "A g2-value-array " */

static Object Qg2_value_array_deleted;  /* g2-value-array-deleted */

static Object string_constant_18;  /* "A g2-value-array ~NF" */

static Object string_constant_19;  /* " at top level in the argument list " */

static Object string_constant_20;  /* "has had its length changed" */

static Object Qg2_value_array_length_diminished;  /* g2-value-array-length-diminished */

/* CHECK-RESUMABLE-VALUE-VECTOR-CONTENTS */
Object check_resumable_value_vector_contents(resumable_node,resumable_object)
    Object resumable_node, resumable_object;
{
    Object current_object, toplevel_object, gensymed_symbol, x, y, xa, ya;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(168,32);
    current_object = ISVREF(resumable_node,(SI_Long)4L);
    toplevel_object = ISVREF(resumable_object,(SI_Long)8L);
    gensymed_symbol = ISVREF(current_object,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(current_object) ? EQ(ISVREF(current_object,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(resumable_node,(SI_Long)10L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if (temp) {
	Rpc_throw_tag = Kabort_transmitting_resumable_object;
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
		  tformat(1,string_constant_17);
		  if (EQ(current_object,toplevel_object))
		      tformat(1,string_constant_1);
		  else
		      tformat(2,string_constant_2,toplevel_object);
		  tformat(1,string_constant_7);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return icp_list_2(Qg2_value_array_deleted,temp_1);
    }
    if ( !FIXNUM_LE(ISVREF(resumable_node,(SI_Long)18L),
	    ISVREF(current_object,(SI_Long)20L))) {
	Rpc_throw_tag = Kabort_transmitting_resumable_object;
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
		  tformat(2,string_constant_18,current_object);
		  if (EQ(current_object,toplevel_object))
		      tformat(1,string_constant_19);
		  else
		      tformat(2,string_constant_2,toplevel_object);
		  tformat(1,string_constant_20);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return icp_list_2(Qg2_value_array_length_diminished,temp_1);
    }
    else
	return VALUES_1(Nil);
}

/* TRANSMIT-RESUMABLE-VALUE-VECTOR-RANGE */
Object transmit_resumable_value_vector_range(resumable_node,
	    resumable_object,icp_port)
    Object resumable_node, resumable_object, icp_port;
{
    Object remaining_element_count, possible_throw_value, element_type_qm;
    Object icp_socket, number_of_elements, bandwidth_needed, interning_details;
    Object network_is_limiting_factor_p, temp, gensymed_symbol, first_1;
    Object last_1, temp_1, next, incff_1_arg, decff_1_arg, svref_new_value;
    Object result;

    x_note_fn_call(168,33);
    remaining_element_count = FIXNUM_ADD1(ISVREF(resumable_node,(SI_Long)21L));
    if ( !(IFIX(remaining_element_count) < (SI_Long)1L)) {
	possible_throw_value = 
		check_resumable_value_vector_contents(resumable_node,
		resumable_object);
	if (Rpc_throw_tag)
	    return VALUES_1(possible_throw_value);
	element_type_qm = ISVREF(resumable_node,(SI_Long)19L);
	icp_socket = ISVREF(icp_port,(SI_Long)2L);
	result = get_value_vector_transmission_info(resumable_node,
		element_type_qm,resumable_object,icp_port);
	MVS_4(result,number_of_elements,bandwidth_needed,interning_details,
		network_is_limiting_factor_p);
	if (IFIX(number_of_elements) <= (SI_Long)0L) {
	    reclaim_icp_tree_1(interning_details);
	    if (network_is_limiting_factor_p) {
		temp = Minimnal_bandwidth_for_resumable_sequence_range;
		SVREF(resumable_object,FIX((SI_Long)17L)) = temp;
		gensymed_symbol = resumable_object;
		gensymed_symbol = icp_cons_1(gensymed_symbol,Nil);
	      next_loop:
		first_1 = ISVREF(icp_socket,(SI_Long)31L);
		last_1 = ISVREF(icp_socket,(SI_Long)32L);
		temp_1 = ISVREF(icp_socket,(SI_Long)32L);
		next = CDR(temp_1);
		if ( !TRUEP(first_1)) {
		    if (CAS_SVREF(icp_socket,(SI_Long)31L,first_1,
			    gensymed_symbol)) {
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,
				gensymed_symbol);
			goto end_1;
		    }
		}
		else if (EQ(last_1,ISVREF(icp_socket,(SI_Long)32L))) {
		    if ( !TRUEP(next)) {
			if (CAS_CDR(last_1,next,gensymed_symbol)) {
			    CAS_SVREF(icp_socket,(SI_Long)32L,last_1,
				    gensymed_symbol);
			    goto end_1;
			}
		    }
		    else
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,next);
		}
		goto next_loop;
	      end_loop:
	      end_1:;
		possible_throw_value = 
			suspend_object_passing_transmission(3,
			resumable_object,resumable_node,Nil);
		if (Rpc_throw_tag)
		    return VALUES_1(possible_throw_value);
	    }
	    else {
		possible_throw_value = 
			suspend_object_passing_transmission(2,
			resumable_object,resumable_node);
		if (Rpc_throw_tag)
		    return VALUES_1(possible_throw_value);
	    }
	}
	incff_1_arg = bandwidth_needed;
	temp = FIXNUM_ADD(ISVREF(resumable_object,(SI_Long)15L),incff_1_arg);
	SVREF(resumable_object,FIX((SI_Long)15L)) = temp;
	temp = ISVREF(resumable_object,(SI_Long)11L);
	decff_1_arg = bandwidth_needed;
	svref_new_value = FIXNUM_MINUS(ISVREF(temp,(SI_Long)30L),decff_1_arg);
	SVREF(temp,FIX((SI_Long)30L)) = svref_new_value;
	if (FIXNUM_LT(number_of_elements,remaining_element_count) && 
		element_type_qm) {
	    write_icp_add_homogeneous_value_vector_range(number_of_elements,
		    element_type_qm,resumable_node,interning_details);
	    possible_throw_value = suspend_object_passing_transmission(2,
		    resumable_object,resumable_node);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    temp_1 = possible_throw_value;
	}
	else if (FIXNUM_LT(number_of_elements,remaining_element_count)) {
	    write_icp_add_value_vector_range(number_of_elements,
		    resumable_node,interning_details);
	    possible_throw_value = suspend_object_passing_transmission(2,
		    resumable_object,resumable_node);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    temp_1 = possible_throw_value;
	}
	else if (element_type_qm)
	    temp_1 = 
		    write_icp_add_homogeneous_value_vector_range(number_of_elements,
		    element_type_qm,resumable_node,interning_details);
	else
	    temp_1 = 
		    write_icp_add_value_vector_range(remaining_element_count,
		    resumable_node,interning_details);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* TRANSMIT-RESUMABLE-HISTORY-RANGE */
Object transmit_resumable_history_range(resumable_node,resumable_object,
	    icp_port)
    Object resumable_node, resumable_object, icp_port;
{
    Object element_type_qm, icp_socket, number_of_cached_elements;
    Object cached_interning_details, ring_index_of_first_uncached_element;
    Object number_of_uncached_elements, uncached_interning_details;
    Object uncached_timestamps_use_float_array_p;
    Object uncached_values_use_float_array_p, bandwidth_needed;
    Object network_is_limiting_factor_p, possible_throw_value, temp;
    Object gensymed_symbol, first_1, last_1, temp_1, next, incff_1_arg;
    Object decff_1_arg, svref_new_value;
    Object result;

    x_note_fn_call(168,34);
    if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
	    ISVREF(resumable_node,(SI_Long)18L))) {
	element_type_qm = ISVREF(resumable_node,(SI_Long)19L);
	icp_socket = ISVREF(icp_port,(SI_Long)2L);
	result = get_history_array_transmission_info(resumable_node,
		resumable_object,element_type_qm,icp_port);
	MVS_9(result,number_of_cached_elements,cached_interning_details,
		ring_index_of_first_uncached_element,
		number_of_uncached_elements,uncached_interning_details,
		uncached_timestamps_use_float_array_p,
		uncached_values_use_float_array_p,bandwidth_needed,
		network_is_limiting_factor_p);
	possible_throw_value = number_of_cached_elements;
	if (Rpc_throw_tag)
	    return VALUES_1(possible_throw_value);
	if ( !(IFIX(number_of_cached_elements) > (SI_Long)0L || 
		IFIX(number_of_uncached_elements) > (SI_Long)0L)) {
	    reclaim_icp_tree_1(cached_interning_details);
	    reclaim_icp_tree_1(uncached_interning_details);
	    if (network_is_limiting_factor_p) {
		temp = Minimnal_bandwidth_for_resumable_sequence_range;
		SVREF(resumable_object,FIX((SI_Long)17L)) = temp;
		gensymed_symbol = resumable_object;
		gensymed_symbol = icp_cons_1(gensymed_symbol,Nil);
	      next_loop:
		first_1 = ISVREF(icp_socket,(SI_Long)31L);
		last_1 = ISVREF(icp_socket,(SI_Long)32L);
		temp_1 = ISVREF(icp_socket,(SI_Long)32L);
		next = CDR(temp_1);
		if ( !TRUEP(first_1)) {
		    if (CAS_SVREF(icp_socket,(SI_Long)31L,first_1,
			    gensymed_symbol)) {
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,
				gensymed_symbol);
			goto end_1;
		    }
		}
		else if (EQ(last_1,ISVREF(icp_socket,(SI_Long)32L))) {
		    if ( !TRUEP(next)) {
			if (CAS_CDR(last_1,next,gensymed_symbol)) {
			    CAS_SVREF(icp_socket,(SI_Long)32L,last_1,
				    gensymed_symbol);
			    goto end_1;
			}
		    }
		    else
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,next);
		}
		goto next_loop;
	      end_loop:
	      end_1:;
		possible_throw_value = 
			suspend_object_passing_transmission(3,
			resumable_object,resumable_node,Nil);
		if (Rpc_throw_tag)
		    return VALUES_1(possible_throw_value);
	    }
	    else {
		possible_throw_value = 
			suspend_object_passing_transmission(2,
			resumable_object,resumable_node);
		if (Rpc_throw_tag)
		    return VALUES_1(possible_throw_value);
	    }
	}
	incff_1_arg = bandwidth_needed;
	temp = FIXNUM_ADD(ISVREF(resumable_object,(SI_Long)15L),incff_1_arg);
	SVREF(resumable_object,FIX((SI_Long)15L)) = temp;
	temp = ISVREF(resumable_object,(SI_Long)11L);
	decff_1_arg = bandwidth_needed;
	svref_new_value = FIXNUM_MINUS(ISVREF(temp,(SI_Long)30L),decff_1_arg);
	SVREF(temp,FIX((SI_Long)30L)) = svref_new_value;
	if (element_type_qm)
	    write_icp_add_homogeneous_history_range(resumable_node,
		    number_of_cached_elements,element_type_qm,
		    cached_interning_details,
		    ring_index_of_first_uncached_element,
		    number_of_uncached_elements,uncached_interning_details,
		    uncached_timestamps_use_float_array_p);
	else
	    write_icp_add_history_range(resumable_node,
		    number_of_cached_elements,cached_interning_details,
		    ring_index_of_first_uncached_element,
		    number_of_uncached_elements,uncached_interning_details,
		    uncached_timestamps_use_float_array_p,
		    uncached_values_use_float_array_p);
	if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
		ISVREF(resumable_node,(SI_Long)18L))) {
	    possible_throw_value = suspend_object_passing_transmission(2,
		    resumable_object,resumable_node);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    temp_1 = possible_throw_value;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qg2_defstruct_structure_name_resumable_value_node_g2_struct;  /* g2-defstruct-structure-name::resumable-value-node-g2-struct */

static Object Qg2_defstruct_structure_name_resumable_circular_node_g2_struct;  /* g2-defstruct-structure-name::resumable-circular-node-g2-struct */

/* TRANSMIT-RESUMABLE-NODE */
Object transmit_resumable_node(resumable_node,resumable_object,
	    bandwidth_needed)
    Object resumable_node, resumable_object, bandwidth_needed;
{
    Object incff_1_arg, temp, decff_1_arg, svref_new_value, class_name;
    Object corresponding_index_of_class_name_qm, attribute_spec;
    Object circularity_index_qm, attribute_count, temp_1, temp_2, temp_3;
    Object temp_4, thing, temp_5;

    x_note_fn_call(168,35);
    incff_1_arg = bandwidth_needed;
    temp = FIXNUM_ADD(ISVREF(resumable_object,(SI_Long)15L),incff_1_arg);
    SVREF(resumable_object,FIX((SI_Long)15L)) = temp;
    temp = ISVREF(resumable_object,(SI_Long)11L);
    decff_1_arg = bandwidth_needed;
    svref_new_value = FIXNUM_MINUS(ISVREF(temp,(SI_Long)30L),decff_1_arg);
    SVREF(temp,FIX((SI_Long)30L)) = svref_new_value;
    if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_node_g2_struct))
	return write_icp_add_attribute_value(ISVREF(resumable_node,
		(SI_Long)2L),ISVREF(resumable_node,(SI_Long)3L),
		ISVREF(resumable_node,(SI_Long)4L));
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_circular_node_g2_struct))
	return write_icp_add_circular_attribute(ISVREF(resumable_node,
		(SI_Long)2L),ISVREF(resumable_node,(SI_Long)3L));
    else {
	class_name = ISVREF(resumable_node,(SI_Long)11L);
	corresponding_index_of_class_name_qm = ISVREF(resumable_node,
		(SI_Long)12L);
	attribute_spec = ISVREF(resumable_node,(SI_Long)2L);
	circularity_index_qm = 
		get_icp_object_index_for_resumable_instance_node(resumable_node,
		Current_icp_port);
	attribute_count = ISVREF(resumable_node,(SI_Long)17L);
	if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_node_g2_struct))
	    write_icp_add_attribute_object(attribute_spec,class_name,
		    corresponding_index_of_class_name_qm,attribute_count);
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct));
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct));
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct))
	    write_icp_add_attribute_object_vector(attribute_spec,
		    class_name,corresponding_index_of_class_name_qm,
		    attribute_count,ISVREF(resumable_node,(SI_Long)18L));
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct))
	    write_icp_add_attribute_value_vector(attribute_spec,class_name,
		    corresponding_index_of_class_name_qm,attribute_count,
		    ISVREF(resumable_node,(SI_Long)19L),
		    ISVREF(resumable_node,(SI_Long)18L));
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_history_node_g2_struct)) 
		    {
	    temp_1 = ISVREF(resumable_node,(SI_Long)19L);
	    temp_2 = ISVREF(resumable_node,(SI_Long)18L);
	    temp_3 = ISVREF(resumable_node,(SI_Long)21L);
	    temp_4 = ISVREF(resumable_node,(SI_Long)22L);
	    thing = ISVREF(resumable_node,(SI_Long)29L);
	    temp_5 = SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,
		    (SI_Long)0L),Managed_float_array_unique_marker) ? T : 
		    Nil) : Qnil;
	    thing = ISVREF(resumable_node,(SI_Long)30L);
	    write_icp_add_attribute_history_object(attribute_spec,
		    class_name,corresponding_index_of_class_name_qm,
		    attribute_count,temp_1,temp_2,temp_3,temp_4,temp_5,
		    SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,(SI_Long)0L),
		    Managed_float_array_unique_marker) ? T : Nil) : Qnil);
	}
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct))
	    write_icp_add_attribute_object_list(attribute_spec,class_name,
		    corresponding_index_of_class_name_qm,attribute_count,
		    ISVREF(resumable_node,(SI_Long)18L));
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct))
	    write_icp_add_attribute_value_list(attribute_spec,class_name,
		    corresponding_index_of_class_name_qm,attribute_count,
		    ISVREF(resumable_node,(SI_Long)19L),
		    ISVREF(resumable_node,(SI_Long)18L));
	if (circularity_index_qm)
	    write_icp_add_resumable_circularity(circularity_index_qm);
	return VALUES_1(SVREF(resumable_node,FIX((SI_Long)5L)) = T);
    }
}

static Object Kfinished_transmitting_resumable_object;  /* :finished-transmitting-resumable-object */

/* TRANSMIT-RESUMABLE-OBJECT */
Object transmit_resumable_object(resumable_object,resumable_node)
    Object resumable_object, resumable_node;
{
    Object icp_socket, icp_port, current_object, svref_new_value;
    Object possible_throw_value, bandwidth_needed, gensymed_symbol, first_1;
    Object last_1, temp, next, allocated_bandwidth, parent_qm, svref_old_value;
    Object next_node_qm, ascension_target_qm;

    x_note_fn_call(168,36);
    icp_socket = ISVREF(resumable_object,(SI_Long)11L);
    icp_port = ISVREF(icp_socket,(SI_Long)4L);
  transmit_sequence_contents_if_any:
    if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct)) 
		{
	if (ISVREF(resumable_node,(SI_Long)5L)) {
	    current_object = ISVREF(resumable_node,(SI_Long)4L);
	    if ( !TRUEP(ISVREF(current_object,(SI_Long)23L)))
		initialize_g2_array(current_object);
	    svref_new_value = ISVREF(current_object,(SI_Long)23L);
	    SVREF(resumable_node,FIX((SI_Long)20L)) = svref_new_value;
	    possible_throw_value = 
		    transmit_resumable_value_vector_range(resumable_node,
		    resumable_object,icp_port);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    goto get_next_node_1;
	}
    }
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct)) {
	if (ISVREF(resumable_node,(SI_Long)5L)) {
	    current_object = ISVREF(resumable_node,(SI_Long)4L);
	    svref_new_value = 
		    get_history_ring_buffer_if_any(current_object,Nil);
	    SVREF(resumable_node,FIX((SI_Long)20L)) = svref_new_value;
	    possible_throw_value = 
		    transmit_resumable_history_range(resumable_node,
		    resumable_object,icp_port);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    goto get_next_node_1;
	}
    }
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct)) 
		{
	if (ISVREF(resumable_node,(SI_Long)5L)) {
	    possible_throw_value = 
		    transmit_resumable_value_list_range(resumable_node,
		    resumable_object,icp_port);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    goto get_next_node_1;
	}
    }
    else
	goto transmit_node_itself;
  transmit_node_itself:
    if ( !((SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct)) 
	    && ISVREF(resumable_node,(SI_Long)5L))) {
	bandwidth_needed = 
		bandwidth_needed_for_resumable_node(resumable_node,icp_port);
	if (IFIX(FIXNUM_MINUS(ISVREF(icp_socket,(SI_Long)30L),
		bandwidth_needed)) < (SI_Long)0L) {
	    SVREF(resumable_object,FIX((SI_Long)17L)) = bandwidth_needed;
	    gensymed_symbol = resumable_object;
	    gensymed_symbol = icp_cons_1(gensymed_symbol,Nil);
	  next_loop:
	    first_1 = ISVREF(icp_socket,(SI_Long)31L);
	    last_1 = ISVREF(icp_socket,(SI_Long)32L);
	    temp = ISVREF(icp_socket,(SI_Long)32L);
	    next = CDR(temp);
	    if ( !TRUEP(first_1)) {
		if (CAS_SVREF(icp_socket,(SI_Long)31L,first_1,
			    gensymed_symbol)) {
		    CAS_SVREF(icp_socket,(SI_Long)32L,last_1,gensymed_symbol);
		    goto end_1;
		}
	    }
	    else if (EQ(last_1,ISVREF(icp_socket,(SI_Long)32L))) {
		if ( !TRUEP(next)) {
		    if (CAS_CDR(last_1,next,gensymed_symbol)) {
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,
				gensymed_symbol);
			goto end_1;
		    }
		}
		else
		    CAS_SVREF(icp_socket,(SI_Long)32L,last_1,next);
	    }
	    goto next_loop;
	  end_loop:
	  end_1:;
	    possible_throw_value = suspend_object_passing_transmission(3,
		    resumable_object,resumable_node,Nil);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	}
	else if (time_slice_expired_p()) {
	    allocated_bandwidth = ISVREF(resumable_object,(SI_Long)15L);
	    if (IFIX(allocated_bandwidth) > (SI_Long)0L)
		Most_recent_bandwidth_per_timeslice_qm = 
			FIXNUM_MAX(allocated_bandwidth,
			Minimum_bandwidth_per_timeslice);
	    possible_throw_value = suspend_object_passing_transmission(2,
		    resumable_object,resumable_node);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	}
	else {
	    possible_throw_value = transmit_resumable_node(resumable_node,
		    resumable_object,bandwidth_needed);
	    if (Rpc_throw_tag)
		return VALUES_1(possible_throw_value);
	    parent_qm = ISVREF(resumable_node,(SI_Long)1L);
	    if (parent_qm) {
		svref_old_value = ISVREF(parent_qm,(SI_Long)14L);
		svref_new_value = REST(svref_old_value);
		SVREF(parent_qm,FIX((SI_Long)14L)) = svref_new_value;
	    }
	    if (SIMPLE_VECTOR_P(resumable_node) && 
		    EQ(ISVREF(resumable_node,(SI_Long)0L),
		    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct)) 
			{
		if ( !(IFIX(ISVREF(resumable_node,(SI_Long)21L)) < 
			(SI_Long)0L))
		    goto transmit_sequence_contents_if_any;
	    }
	    else if (SIMPLE_VECTOR_P(resumable_node) && 
		    EQ(ISVREF(resumable_node,(SI_Long)0L),
		    Qg2_defstruct_structure_name_resumable_history_node_g2_struct)) 
			{
		if ( !FIXNUM_GE(ISVREF(resumable_node,(SI_Long)25L),
			ISVREF(resumable_node,(SI_Long)18L)))
		    goto transmit_sequence_contents_if_any;
	    }
	    else if (SIMPLE_VECTOR_P(resumable_node) && 
		    EQ(ISVREF(resumable_node,(SI_Long)0L),
		    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct)) 
			{
		if (ISVREF(resumable_node,(SI_Long)20L))
		    goto transmit_sequence_contents_if_any;
	    }
	    else
		goto get_next_node_1;
	}
    }
  get_next_node_1:
    if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct) 
	    || SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct)) 
		{
	temp = ISVREF(resumable_node,(SI_Long)14L);
	temp = CAR(temp);
	if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct)) 
		    {
	    svref_new_value = FIXNUM_ADD1(ISVREF(resumable_node,(SI_Long)21L));
	    SVREF(resumable_node,FIX((SI_Long)21L)) = svref_new_value;
	}
	next_node_qm = temp;
	if (next_node_qm)
	    resumable_node = next_node_qm;
	else {
	    ascension_target_qm = ISVREF(resumable_node,(SI_Long)6L);
	    if (ascension_target_qm) {
		write_icp_ascend_to_parent(ISVREF(resumable_node,(SI_Long)7L));
		resumable_node = ascension_target_qm;
		if (ISVREF(resumable_node,(SI_Long)5L))
		    goto get_next_node_1;
	    }
	    else {
		write_icp_finish_building_object(ISVREF(resumable_object,
			(SI_Long)15L));
		Rpc_throw_tag = Kfinished_transmitting_resumable_object;
		return VALUES_1(T);
	    }
	}
    }
    else {
	resumable_node = ISVREF(resumable_node,(SI_Long)1L);
	if (ISVREF(resumable_node,(SI_Long)5L))
	    goto get_next_node_1;
    }
    SVREF(resumable_object,FIX((SI_Long)10L)) = resumable_node;
    goto transmit_sequence_contents_if_any;
    return VALUES_1(Qnil);
}

static Object Qrpc_object_argument_deleted;  /* rpc-object-argument-deleted */

static Object string_constant_21;  /* "An object being sent as an RPC argument has been deleted" */

/* CHECK-TOPLEVEL-RESUMABLE-NODE-INTEGRITY */
Object check_toplevel_resumable_node_integrity(resumable_object)
    Object resumable_object;
{
    Object toplevel_node, toplevel_object, toplevel_reference_number;
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(168,37);
    toplevel_node = ISVREF(resumable_object,(SI_Long)9L);
    toplevel_object = ISVREF(toplevel_node,(SI_Long)4L);
    toplevel_reference_number = ISVREF(toplevel_node,(SI_Long)10L);
    gensymed_symbol = ISVREF(toplevel_object,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(toplevel_object) ? EQ(ISVREF(toplevel_object,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(toplevel_reference_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(toplevel_reference_number,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(toplevel_reference_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(toplevel_reference_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if (temp) {
	Rpc_throw_tag = Kabort_transmitting_resumable_object;
	return icp_list_2(Qrpc_object_argument_deleted,
		tformat_text_string(1,string_constant_21));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_22;  /* "The remote procedure call ~A ~
				    *                    has been aborted while transmitting: ~A"
				    */

static Object string_constant_23;  /* "A remote procedure call ~
				    *                    has been aborted while transmitting: ~A"
				    */

/* TRANSMIT-RESUMABLE-OBJECT-WITH-CATCH-HANDLERS */
Object transmit_resumable_object_with_catch_handlers(resumable_object)
    Object resumable_object;
{
    Object rpc_throw_tag, possible_throw_value, gensymed_symbol, abort_info;
    Object rpc_name_qm, error_message, error_string, info, ab_loop_list_;
    Object new_resumable_node;
    Declare_special(1);
    Object result;

    x_note_fn_call(168,38);
    rpc_throw_tag = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Rpc_throw_tag,Qrpc_throw_tag,rpc_throw_tag,0);
      possible_throw_value = 
	      check_toplevel_resumable_node_integrity(resumable_object);
      if (Rpc_throw_tag) {
	  gensymed_symbol = possible_throw_value;
	  goto end_transmit_resumable_object_with_catch_handlers_body;
      }
      possible_throw_value = transmit_resumable_object(resumable_object,
	      ISVREF(resumable_object,(SI_Long)10L));
      if (Rpc_throw_tag) {
	  gensymed_symbol = possible_throw_value;
	  goto end_transmit_resumable_object_with_catch_handlers_body;
      }
      gensymed_symbol = possible_throw_value;
    end_transmit_resumable_object_with_catch_handlers_body:
      if (EQ(Rpc_throw_tag,Kabort_transmitting_resumable_object)) {
	  abort_info = gensymed_symbol;
	  rpc_name_qm = ISVREF(resumable_object,(SI_Long)1L);
	  error_message = SECOND(abort_info);
	  error_string = rpc_name_qm ? tformat_text_string(3,
		  string_constant_22,rpc_name_qm,error_message) : 
		  tformat_text_string(2,string_constant_23,error_message);
	  receive_object_passing_remote_procedure_error(resumable_object,
		  FIRST(abort_info),error_string);
	  info = Nil;
	  ab_loop_list_ = abort_info;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  info = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (text_string_p(info))
	      reclaim_text_string(info);
	  goto next_loop;
	end_loop:
	  reclaim_icp_list_1(abort_info);
	  reclaim_text_string(error_string);
	  write_icp_abort_building_object(ISVREF(resumable_object,
		  (SI_Long)15L));
	  result = g2_reclaim_sending_resumable_object(1,resumable_object);
      }
      else if (EQ(Rpc_throw_tag,Kfinished_transmitting_resumable_object))
	  result = g2_reclaim_sending_resumable_object(2,resumable_object,T);
      else if (EQ(Rpc_throw_tag,Ksuspend_transmitting_resumable_object)) {
	  new_resumable_node = gensymed_symbol;
	  result = VALUES_1(SVREF(resumable_object,FIX((SI_Long)10L)) = 
		  new_resumable_node);
      }
      else
	  result = VALUES_1(gensymed_symbol);
    POP_SPECIAL();
    return result;
}

static Object Qtelewindows;        /* telewindows */

/* TRANSMIT-RESUMABLE-OBJECT-MESSAGE-GROUP */
Object transmit_resumable_object_message_group(resumable_object,icp_port)
    Object resumable_object, icp_port;
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
    Object result;

    x_note_fn_call(168,39);
    ISVREF(resumable_object,(SI_Long)15L) = FIX((SI_Long)0L);
    SVREF(resumable_object,FIX((SI_Long)16L)) = Nil;
    current_icp_port = icp_port;
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
				send_icp_continue_building_resumable_object(resumable_object);
				temp = 
					transmit_resumable_object_with_catch_handlers(resumable_object);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
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
			    result = VALUES_1(temp);
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

/* TRY-TO-TRANSMIT-RESUMABLE-OBJECT */
Object try_to_transmit_resumable_object(resumable_object)
    Object resumable_object;
{
    Object icp_interface_qm, gensymed_symbol, x, y, xa, ya, icp_socket, temp_1;
    char temp;

    x_note_fn_call(168,40);
    icp_interface_qm = ISVREF(resumable_object,(SI_Long)13L);
    if (icp_interface_qm) {
	gensymed_symbol = ISVREF(icp_interface_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(icp_interface_qm) ? 
		EQ(ISVREF(icp_interface_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(resumable_object,(SI_Long)6L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(T);
    if (temp) {
	icp_socket = ISVREF(resumable_object,(SI_Long)11L);
	temp_1 = icp_connection_being_shutdown_qm(icp_socket) ||  
		!TRUEP(icp_connection_open_p(icp_socket)) ? 
		g2_reclaim_sending_resumable_object(1,resumable_object) : 
		transmit_resumable_object_message_group(resumable_object,
		ISVREF(icp_socket,(SI_Long)4L));
    }
    else
	temp_1 = g2_reclaim_sending_resumable_object(1,resumable_object);
    return VALUES_1(temp_1);
}

/* GET-ATTRIBUTE-NAMES-FOR-OBJECT-PASSING */
Object get_attribute_names_for_object_passing(object,
	    included_attributes_qm,excluded_attributes_qm,
	    included_system_attributes)
    Object object, included_attributes_qm, excluded_attributes_qm;
    Object included_system_attributes;
{
    Object class_description_of_object, slot_descriptions_of_object;
    Object attribute_names_qm, attribute_names_tail, slot_description;
    Object ab_loop_list_, base_slot_name;
    Object slot_name_with_qualifier_if_necessary, temp, new_attribute_name;
    Object new_attribute_name_cons, system_attribute_names, attribute_spec_qm;

    x_note_fn_call(168,41);
    class_description_of_object = ISVREF(object,(SI_Long)1L);
    slot_descriptions_of_object = ISVREF(class_description_of_object,
	    (SI_Long)6L);
    attribute_names_qm = Nil;
    attribute_names_tail = Nil;
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions_of_object;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	base_slot_name = ISVREF(slot_description,(SI_Long)2L);
	slot_name_with_qualifier_if_necessary = 
		denote_slot_using_slot_value_conses(slot_description,
		class_description_of_object);
	if (included_attributes_qm)
	    temp = member_equal(slot_name_with_qualifier_if_necessary,
		    included_attributes_qm);
	else if (excluded_attributes_qm)
	    temp =  
		    !TRUEP(member_equal(slot_name_with_qualifier_if_necessary,
		    excluded_attributes_qm)) ? T : Nil;
	else
	    temp = T;
	if (temp) {
	    new_attribute_name = gensym_list_3(Qattribute,
		    CONSP(slot_name_with_qualifier_if_necessary) ? 
		    SECOND(slot_name_with_qualifier_if_necessary) : Nil,
		    base_slot_name);
	    new_attribute_name_cons = icp_cons_1(new_attribute_name,Nil);
	    if (attribute_names_qm)
		M_CDR(attribute_names_tail) = new_attribute_name_cons;
	    else
		attribute_names_qm = new_attribute_name_cons;
	    attribute_names_tail = new_attribute_name_cons;
	}
	if (CONSP(slot_name_with_qualifier_if_necessary))
	    reclaim_slot_value_list_1(slot_name_with_qualifier_if_necessary);
    }
    goto next_loop;
  end_loop:;
    system_attribute_names = Nil;
    attribute_spec_qm = 
	    get_import_declarations_attribute_spec_structure_for_object_passing(object,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_package_declaration_attribute_spec_structure_for_object_passing(object,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_text_attribute_spec_structure_for_object_passing(object,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_name_attribute_spec_structure_for_object_passing(object,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_current_value_attribute_spec_structure_for_object_passing(object,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    temp = nreverse(system_attribute_names);
    temp = nconc2(temp,attribute_names_qm);
    return VALUES_1(temp);
}

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* WRITABLE-EXPORTED-ATTRIBUTE-FOR-OBJECT-PASSING-P */
Object writable_exported_attribute_for_object_passing_p(item,slot_name)
    Object item, slot_name;
{
    Object virtual_attribute_structure_qm, temp, slot_description_qm;
    Object slot_description_type_qm, category_symbol;
    Object category_evaluator_interface, alias_qm, alias_description_qm;

    x_note_fn_call(168,42);
    virtual_attribute_structure_qm = get_property_value_function(3,
	    get_symbol_properties_function(slot_name),Qvirtual_attribute,Nil);
    if (virtual_attribute_structure_qm)
	temp = ISVREF(virtual_attribute_structure_qm,(SI_Long)7L);
    else {
	slot_description_qm = 
		get_slot_description_of_class_description_function(slot_name,
		ISVREF(item,(SI_Long)1L),Nil);
	if (slot_description_qm) {
	    slot_description_type_qm = assq_function(Qtype,
		    ISVREF(slot_description_qm,(SI_Long)9L));
	    if (slot_description_type_qm) {
		category_symbol = SECOND(slot_description_type_qm);
		if (category_symbol) {
		    category_evaluator_interface = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_symbol),
			    Qcategory_evaluator_interface);
		    temp = category_evaluator_interface ? 
			    ISVREF(category_evaluator_interface,
			    (SI_Long)3L) : Qnil;
		}
		else
		    temp = Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
	if (temp);
	else {
	    alias_qm = get_slot_name_for_alias_if_any(slot_name,item);
	    if (alias_qm) {
		alias_description_qm = 
			get_slot_description_of_class_description_function(alias_qm,
			ISVREF(item,(SI_Long)1L),Nil);
		if (alias_description_qm) {
		    slot_description_type_qm = assq_function(Qtype,
			    ISVREF(alias_description_qm,(SI_Long)9L));
		    if (slot_description_type_qm) {
			category_symbol = SECOND(slot_description_type_qm);
			if (category_symbol) {
			    category_evaluator_interface = 
				    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_symbol),
				    Qcategory_evaluator_interface);
			    temp = category_evaluator_interface ? 
				    ISVREF(category_evaluator_interface,
				    (SI_Long)3L) : Qnil;
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
	    else
		temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* GET-EXPORTED-ATTRIBUTE-NAMES-FOR-OBJECT-PASSING */
Object get_exported_attribute_names_for_object_passing(item,
	    included_attributes_qm,excluded_attributes_qm,
	    included_system_attributes)
    Object item, included_attributes_qm, excluded_attributes_qm;
    Object included_system_attributes;
{
    Object class_description_of_item, slot_descriptions_of_item;
    Object attribute_names_qm, attribute_names_tail, slot_name, ab_loop_list_;
    Object ab_loop_desetq_, new_attribute_name, new_attribute_name_cons;
    Object system_attribute_names, attribute_spec_qm, temp_1;
    char temp;

    x_note_fn_call(168,43);
    class_description_of_item = ISVREF(item,(SI_Long)1L);
    slot_descriptions_of_item = 
	    get_list_of_all_user_visible_attributes(class_description_of_item);
    attribute_names_qm = Nil;
    attribute_names_tail = Nil;
    slot_name = Nil;
    ab_loop_list_ = slot_descriptions_of_item;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    slot_name = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (writable_exported_attribute_for_object_passing_p(item,slot_name)) {
	if (included_attributes_qm)
	    temp = TRUEP(memq_function(slot_name,included_attributes_qm));
	else if (excluded_attributes_qm)
	    temp =  !TRUEP(memq_function(slot_name,excluded_attributes_qm));
	else
	    temp = TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	new_attribute_name = gensym_list_3(Qattribute,Nil,slot_name);
	new_attribute_name_cons = icp_cons_1(new_attribute_name,Nil);
	if (attribute_names_qm)
	    M_CDR(attribute_names_tail) = new_attribute_name_cons;
	else
	    attribute_names_qm = new_attribute_name_cons;
	attribute_names_tail = new_attribute_name_cons;
    }
    goto next_loop;
  end_loop:;
    reclaim_eval_tree_1(slot_descriptions_of_item);
    system_attribute_names = Nil;
    attribute_spec_qm = 
	    get_import_declarations_attribute_spec_structure_for_object_passing(item,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_package_declaration_attribute_spec_structure_for_object_passing(item,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_text_attribute_spec_structure_for_object_passing(item,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_name_attribute_spec_structure_for_object_passing(item,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    attribute_spec_qm = 
	    get_current_value_attribute_spec_structure_for_object_passing(item,
	    included_system_attributes);
    if (attribute_spec_qm)
	system_attribute_names = icp_cons_1(attribute_spec_qm,
		system_attribute_names);
    temp_1 = nreverse(system_attribute_names);
    temp_1 = nconc2(temp_1,attribute_names_qm);
    return VALUES_1(temp_1);
}

/* MAKE-TOPLEVEL-RESUMABLE-NODE */
Object make_toplevel_resumable_node(object,included_attributes,
	    excluded_attributes,included_system_attributes)
    Object object, included_attributes, excluded_attributes;
    Object included_system_attributes;
{
    Object class_of_object, serial_number, attribute_names, gensymed_symbol;
    Object sub_class_bit_vector, resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, resumable_sequence_length;
    Object internal_vector_for_object_passing, resumable_node_parent_node_qm;
    Object value_vector_node, svref_new_value, toplevel_node, temp_1;
    Object object_vector_node, history_spec_qm, history_enclosure_qm;
    Object history_qm, temp_2, temp_3, old_list, new_list;
    Object exported_attribute_names;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(168,44);
    if (T) {
	class_of_object = ISVREF(ISVREF(object,(SI_Long)1L),(SI_Long)1L);
	serial_number = ISVREF(object,(SI_Long)3L);
	attribute_names = get_attribute_names_for_object_passing(object,
		included_attributes,excluded_attributes,
		included_system_attributes);
	gensymed_symbol = ISVREF(object,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Value_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    resumable_instance_current_object = object;
	    resumable_instance_reference_serial_number = 
		    copy_frame_serial_number(serial_number);
	    current_attribute_names = attribute_names;
	    symbolic_attribute_count = 
		    count_of_symbolic_attributes(attribute_names);
	    resumable_attribute_spec_qm = Nil;
	    resumable_instance_class_name = class_of_object;
	    resumable_sequence_length = ISVREF(object,(SI_Long)20L);
	    if ( !TRUEP(ISVREF(object,(SI_Long)23L)))
		initialize_g2_array(object);
	    internal_vector_for_object_passing = ISVREF(object,(SI_Long)23L);
	    resumable_node_parent_node_qm = Nil;
	    value_vector_node = 
		    make_resumable_value_vector_node_internal_1(resumable_instance_current_object,
		    resumable_instance_reference_serial_number,
		    current_attribute_names,symbolic_attribute_count,
		    resumable_attribute_spec_qm,
		    resumable_instance_class_name,
		    resumable_sequence_length,
		    internal_vector_for_object_passing,
		    resumable_node_parent_node_qm);
	    svref_new_value = sub1(resumable_sequence_length);
	    SVREF(value_vector_node,FIX((SI_Long)21L)) = svref_new_value;
	    toplevel_node = value_vector_node;
	    g2_set_resumable_node_homogeneous_element_type(toplevel_node,
		    object);
	    temp_1 = toplevel_node;
	}
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Item_array_class_description,(SI_Long)18L));
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
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		resumable_instance_current_object = object;
		resumable_instance_reference_serial_number = 
			copy_frame_serial_number(serial_number);
		current_attribute_names = attribute_names;
		symbolic_attribute_count = 
			count_of_symbolic_attributes(attribute_names);
		resumable_attribute_spec_qm = Nil;
		resumable_instance_class_name = class_of_object;
		resumable_sequence_length = ISVREF(object,(SI_Long)20L);
		if ( !TRUEP(ISVREF(object,(SI_Long)23L)))
		    initialize_g2_array(object);
		internal_vector_for_object_passing = ISVREF(object,
			(SI_Long)23L);
		resumable_node_parent_node_qm = Nil;
		object_vector_node = 
			make_resumable_object_vector_node_internal_1(resumable_instance_current_object,
			resumable_instance_reference_serial_number,
			current_attribute_names,symbolic_attribute_count,
			resumable_attribute_spec_qm,
			resumable_instance_class_name,
			resumable_sequence_length,
			internal_vector_for_object_passing,
			resumable_node_parent_node_qm);
		svref_new_value = sub1(resumable_sequence_length);
		SVREF(object_vector_node,FIX((SI_Long)22L)) = svref_new_value;
		temp_1 = object_vector_node;
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_or_parameter_class_description,
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
		    history_spec_qm = ISVREF(object,(SI_Long)25L);
		    if (history_spec_qm) {
			temp_1 = copy_frame_serial_number(serial_number);
			toplevel_node = 
				make_resumable_history_node_1(object,
				temp_1,attribute_names,
				count_of_symbolic_attributes(attribute_names),
				Nil,class_of_object,FIX((SI_Long)0L),Nil);
			history_enclosure_qm = ISVREF(object,(SI_Long)24L);
			history_qm = get_history_ring_buffer_if_any(object,
				Nil);
			if (history_qm)
			    copy_history_state_into_resumable_history_node(toplevel_node,
				    history_enclosure_qm,history_qm,
				    history_spec_qm);
			g2_set_resumable_node_homogeneous_element_type(toplevel_node,
				object);
			temp_1 = toplevel_node;
		    }
		    else {
			temp_1 = copy_frame_serial_number(serial_number);
			temp_1 = make_resumable_object_node_1(object,
				temp_1,attribute_names,
				count_of_symbolic_attributes(attribute_names),
				Nil,class_of_object,Nil);
		    }
		}
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Value_list_class_description,
			    (SI_Long)18L));
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
		    if (temp) {
			temp_2 = copy_frame_serial_number(serial_number);
			temp_3 = count_of_symbolic_attributes(attribute_names);
			old_list = ISVREF(object,(SI_Long)20L);
			if ( !TRUEP(old_list)) {
			    new_list = create_empty_g2_list_structure();
			    if ( !TRUEP(CAS_SVREF(object,(SI_Long)20L,
				    old_list,new_list)))
				reclaim_empty_g2_list_structure(new_list);
			}
			temp_1 = 
				ATOMIC_REF_OBJECT(ISVREF(ISVREF(ISVREF(object,
				(SI_Long)20L),(SI_Long)2L),(SI_Long)2L));
			toplevel_node = 
				make_resumable_value_list_node_1(object,
				temp_2,attribute_names,temp_3,Nil,
				class_of_object,temp_1,
				g2_list_length(object),Nil);
			g2_set_resumable_node_homogeneous_element_type(toplevel_node,
				object);
			temp_1 = toplevel_node;
		    }
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Item_list_class_description,
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
			if (temp);
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
			}
			if (temp) {
			    temp_2 = copy_frame_serial_number(serial_number);
			    temp_3 = 
				    count_of_symbolic_attributes(attribute_names);
			    old_list = ISVREF(object,(SI_Long)20L);
			    if ( !TRUEP(old_list)) {
				new_list = create_empty_g2_list_structure();
				if ( !TRUEP(CAS_SVREF(object,(SI_Long)20L,
					old_list,new_list)))
				    reclaim_empty_g2_list_structure(new_list);
			    }
			    temp_1 = 
				    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ISVREF(object,
				    (SI_Long)20L),(SI_Long)2L),(SI_Long)2L));
			    temp_1 = 
				    make_resumable_object_list_node_1(object,
				    temp_2,attribute_names,temp_3,Nil,
				    class_of_object,temp_1,
				    g2_list_length(object),Nil);
			}
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Object_class_description,
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
			    if (temp) {
				temp_1 = 
					copy_frame_serial_number(serial_number);
				temp_1 = 
					make_resumable_object_node_1(object,
					temp_1,attribute_names,
					count_of_symbolic_attributes(attribute_names),
					Nil,class_of_object,Nil);
			    }
			    else if (ISVREF(gensymed_symbol,(SI_Long)16L)) {
				exported_attribute_names = 
					get_exported_attribute_names_for_object_passing(object,
					included_attributes,
					excluded_attributes,
					included_system_attributes);
				temp_1 = 
					copy_frame_serial_number(serial_number);
				temp_1 = 
					make_resumable_object_node_1(object,
					temp_1,exported_attribute_names,
					length(exported_attribute_names),
					Nil,class_of_object,Nil);
			    }
			    else
				temp_1 = Nil;
			}
		    }
		}
	    }
	}
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* MAKE-SENDING-RESUMABLE-OBJECT-GIVEN-OPTIONS */
Object make_sending_resumable_object_given_options(rpc_name,rpc_object,
	    icp_socket,interface_frame_qm,priority,included_attributes,
	    excluded_attributes,included_system_attributes)
    Object rpc_name, rpc_object, icp_socket, interface_frame_qm, priority;
    Object included_attributes, excluded_attributes;
    Object included_system_attributes;
{
    Object toplevel_resumable_node, fsn1, fsn2, xa, ya, temp_1;
    Object sending_resumable_object, current_icp_socket, current_icp_port;
    Object new_icp_index, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, resumable_object;
    char temp;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(14);

    x_note_fn_call(168,45);
    toplevel_resumable_node = make_toplevel_resumable_node(rpc_object,
	    included_attributes,excluded_attributes,
	    included_system_attributes);
    if (ATOM(rpc_object)) {
	if (interface_frame_qm) {
	    fsn1 = ISVREF(rpc_object,(SI_Long)3L);
	    fsn2 = ISVREF(interface_frame_qm,(SI_Long)3L);
	    if (FIXNUMP(fsn1))
		temp = FIXNUMP(fsn2) ? FIXNUM_LT(fsn1,fsn2) : TRUEP(T);
	    else if (FIXNUMP(fsn2))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(fsn1);
		ya = M_CAR(fsn2);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn1),
			    M_CDR(fsn2)) : TRUEP(Qnil);
	    }
	    temp_1 = temp ? fsn2 : fsn1;
	}
	else
	    temp_1 = ISVREF(rpc_object,(SI_Long)3L);
    }
    else
	temp_1 = Nil;
    sending_resumable_object = 
	    make_sending_resumable_object_internal_1(rpc_name,rpc_object,
	    toplevel_resumable_node,toplevel_resumable_node,temp_1,
	    icp_socket,interface_frame_qm,priority,Nil,included_attributes,
	    excluded_attributes,included_system_attributes);
    current_icp_socket = icp_socket;
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	    13);
      current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	      12);
	new_icp_index = Nil;
	current_icp_port = Current_icp_port;
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
				    new_icp_index = 
					    establish_new_object_index_for_resumable_object(2,
					    sending_resumable_object,
					    Current_icp_port);
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
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
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
	SVREF(sending_resumable_object,FIX((SI_Long)12L)) = new_icp_index;
	resumable_object = sending_resumable_object;
      POP_SPECIAL();
    POP_SPECIAL();
    set_index_of_circular_resumable_node(rpc_object,resumable_object,
	    toplevel_resumable_node);
    return VALUES_1(resumable_object);
}

static Object Kgeneral_description;  /* :general-description */

static Object Kinclude_attributes;  /* :include-attributes */

static Object Kexclude_attributes;  /* :exclude-attributes */

static Object Kinclude_system_attributes;  /* :include-system-attributes */

static Object Kinclude_all_system_attributes;  /* :include-all-system-attributes */

static Object Kinclude_all_system_attributes_except;  /* :include-all-system-attributes-except */

static Object Kkind;               /* :kind */

/* VAR-RPC-INFO-FROM-INDEX */
Object var_rpc_info_from_index(descriptions,description_index)
    Object descriptions, description_index;
{
    Object gensymed_symbol_1, description, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(168,46);
    gensymed_symbol = IFIX(description_index) * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(descriptions,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(descriptions,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description)) {
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	description = gensymed_symbol_1;
    }
    else
	description = Nil;
    temp = make_remote_procedure_item_info(getf(description,
	    Kinclude_attributes,_),getf(description,Kexclude_attributes,_),
	    getf(description,Kinclude_system_attributes,_),
	    getf(description,Kinclude_all_system_attributes,_),
	    getf(description,Kinclude_all_system_attributes_except,_),
	    getf(description,Kkind,_));
    return VALUES_1(temp);
}

static Object Kall_remaining;      /* :all-remaining */

static Object Qby_copy_with_handle;  /* by-copy-with-handle */

static Object Qreference;          /* reference */

static Object Qhandle;             /* handle */

static Object string_constant_24;  /* "The RPC argument or result ~NC was sent as a handle but is ~
				    *                     not the network handle for any object in this interface"
				    */

static Object Qreturn_remote_procedure_result_as_handle;  /* return-remote-procedure-result-as-handle */

static Object string_constant_25;  /* "The RPC argument or result ~NC was sent as a handle ~
				    *              but the remote process is not equipped for item-passing"
				    */

static Object Qreturn_remote_procedure_result_as_object_from_handle;  /* return-remote-procedure-result-as-object-from-handle */

static Object string_constant_26;  /* "The RPC argument or result ~NF was sent by copy, but is not an object ~
				    *                  and the remote process is not equipped to receive non-object items"
				    */

static Object string_constant_27;  /* "The RPC argument or result ~NF was sent by copy with a handle ~
				    *                       but the remote process is not equipped to receive by copy with a handle"
				    */

static Object Qreturn_remote_procedure_result;  /* return-remote-procedure-result */

static Object Qcopy;               /* copy */

static Object list_constant_2;     /* # */

static Object string_constant_28;  /* "The RPC argument or result ~NF is an item ~
				    *              but the remote process is not equipped for item-passing"
				    */

/* TRANSFORM-RPC-ARGUMENT-OR-RESULT-LIST */
Object transform_rpc_argument_or_result_list varargs_1(int, n)
{
    Object remote_procedure_declaration_qm, arguments_or_results, descriptions;
    Object icp_socket, interface_frame_qm, priority, argument_list_p;
    Object return_info_list, varargs_p, gensymed_symbol_1, temp;
    Object current_computation_flags, info_count, argument_or_result;
    Object ab_loop_list_, argument_or_result_cons, rest_args_p;
    Object description_index, restp, argument_type_or_class, info, kind;
    Object by_copy_with_handle_p, as_reference_p, as_handle_p, frame_p;
    Object previous_sending_resumable_object_qm, designation;
    Object ab_loop_iter_flag_, return_info_list_old_value, x2, temp_2;
    Object constant_value, handled_object_exists_p, resumable_object_as_handle;
    Object rpc_name, handle, reference_type;
    Object sending_resumable_object_as_handle, registration_number;
    Object sub_class_bit_vector, name, resumable_object, temp_3, car_new_value;
    SI_Long gensymed_symbol, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(168,47);
    INIT_ARGS_nonrelocating();
    remote_procedure_declaration_qm = REQUIRED_ARG_nonrelocating();
    arguments_or_results = REQUIRED_ARG_nonrelocating();
    descriptions = REQUIRED_ARG_nonrelocating();
    icp_socket = REQUIRED_ARG_nonrelocating();
    interface_frame_qm = REQUIRED_ARG_nonrelocating();
    priority = REQUIRED_ARG_nonrelocating();
    argument_list_p = REQUIRED_ARG_nonrelocating();
    return_info_list = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    varargs_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (argument_list_p && (SI_Long)0L < IFIX(var_count(descriptions))) {
	gensymed_symbol = IFIX(FIXNUM_SUB1(var_count(descriptions))) * 
		(SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(descriptions,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(descriptions,
		gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(descriptions,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description)) {
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    temp = gensymed_symbol_1;
	}
	else
	    temp = Nil;
	temp_1 = TRUEP(getf(temp,Kall_remaining,_));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	varargs_p = T;
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    0);
      info_count = argument_list_p ? var_count(descriptions) : 
	      length(return_info_list);
      argument_or_result = Nil;
      ab_loop_list_ = arguments_or_results;
      argument_or_result_cons = arguments_or_results;
      rest_args_p = Nil;
      description_index = FIX((SI_Long)0L);
      restp = Nil;
      argument_type_or_class = Nil;
      info = Nil;
      kind = Nil;
      by_copy_with_handle_p = Nil;
      as_reference_p = Nil;
      as_handle_p = Nil;
      frame_p = Nil;
      previous_sending_resumable_object_qm = Nil;
      designation = Nil;
      ab_loop_iter_flag_ = T;
      if (ISVREF(icp_socket,(SI_Long)48L))
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  | (SI_Long)16L);
      else
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  &  ~(SI_Long)16L);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      argument_or_result = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_))
	  argument_or_result_cons = M_CDR(argument_or_result_cons);
      if ( !TRUEP(argument_or_result_cons))
	  goto end_loop;
      if ( !TRUEP(ab_loop_iter_flag_)) {
	  temp = rest_args_p;
	  if (temp);
	  else
	      temp = restp;
	  rest_args_p = temp;
	  description_index = rest_args_p ? description_index : 
		  FIXNUM_ADD1(description_index);
      }
      temp = rest_args_p;
      if (temp);
      else
	  temp = varargs_p ? (FIXNUM_EQ(description_index,
		  FIXNUM_SUB1(info_count)) ? T : Nil) : Qnil;
      restp = temp;
      if (argument_list_p) {
	  gensymed_symbol = IFIX(description_index) * (SI_Long)2L + 
		  (SI_Long)1L;
	  gensymed_symbol_1 = FIXNUM_LE(ISVREF(descriptions,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(descriptions,
		  gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(descriptions,(gensymed_symbol >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		  (SI_Long)1023L);
	  if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		  Kgeneral_description))
	      gensymed_symbol_1 = 
		      getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
	  argument_type_or_class = gensymed_symbol_1;
      }
      else
	  argument_type_or_class = Nil;
      if (argument_list_p)
	  info = var_rpc_info_from_index(descriptions,description_index);
      else if (restp)
	  info = CAR(return_info_list);
      else {
	  return_info_list_old_value = return_info_list;
	  temp = FIRST(return_info_list_old_value);
	  return_info_list = REST(return_info_list_old_value);
	  info = temp;
      }
      kind = remote_procedure_item_info_kind(info);
      by_copy_with_handle_p = EQ(Qby_copy_with_handle,kind) ? T : Nil;
      as_reference_p = EQ(Qreference,kind) ? T : Nil;
      as_handle_p = EQ(Qhandle,kind) ? T : Nil;
      if (SIMPLE_VECTOR_P(argument_or_result) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(argument_or_result)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(argument_or_result,(SI_Long)1L),
	      Qavailable_frame_vector)) {
	  x2 = ISVREF(argument_or_result,(SI_Long)1L);
	  frame_p = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? x2 : Qnil;
      }
      else
	  frame_p = Nil;
      if (argument_type_or_class && FIXNUMP(argument_or_result) && 
	      class_type_specification_p(argument_type_or_class) && 
	      as_handle_p) {
	  temp = ISVREF(icp_socket,(SI_Long)21L);
	  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
	  if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)5L) {
	      constant_value = argument_or_result;
	      handled_object_exists_p = as_handle_p ? 
		      get_item_from_local_handle(constant_value,
		      icp_socket) : Nil;
	      if (as_handle_p &&  !TRUEP(handled_object_exists_p)) {
		  result = tformat_text_string(2,string_constant_24,
			  constant_value);
		  goto end_1;
	      }
	      else {
		  temp = ISVREF(icp_socket,(SI_Long)21L);
		  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
		  if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L)
		      resumable_object_as_handle = icp_cons_1(kind,
			      constant_value);
		  else {
		      if (remote_procedure_declaration_qm) {
			  rpc_name = designation;
			  if (rpc_name);
			  else {
			      designation = 
				      get_or_make_up_designation_for_block(remote_procedure_declaration_qm);
			      rpc_name = designation;
			  }
		      }
		      else
			  rpc_name = Qreturn_remote_procedure_result_as_handle;
		      handle = constant_value;
		      reference_type = kind;
		      sending_resumable_object_as_handle = 
			      make_sending_resumable_object_internal_1(rpc_name,
			      handle,Nil,Nil,Nil,icp_socket,Nil,Nil,
			      reference_type,Nil,Nil,Nil);
		      resumable_object_as_handle = 
			      sending_resumable_object_as_handle;
		  }
		  M_CAR(argument_or_result_cons) = resumable_object_as_handle;
	      }
	  }
	  else {
	      result = tformat_text_string(2,string_constant_25,
		      argument_or_result);
	      POP_SPECIAL();
	      goto end_transform_rpc_argument_or_result_list;
	  }
      }
      else if (frame_p) {
	  temp = ISVREF(icp_socket,(SI_Long)21L);
	  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
	  if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)5L) {
	      if (as_reference_p && frame_p) {
		  temp = ISVREF(icp_socket,(SI_Long)21L);
		  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
		  if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L)
		      resumable_object_as_handle = icp_cons_1(kind,
			      argument_or_result);
		  else {
		      rpc_name = remote_procedure_declaration_qm ? 
			      get_or_make_up_designation_for_block(remote_procedure_declaration_qm) 
			      : 
			      Qreturn_remote_procedure_result_as_object_from_handle;
		      handle = argument_or_result;
		      reference_type = kind;
		      sending_resumable_object_as_handle = 
			      make_sending_resumable_object_internal_1(rpc_name,
			      handle,Nil,Nil,Nil,icp_socket,Nil,Nil,
			      reference_type,Nil,Nil,Nil);
		      resumable_object_as_handle = 
			      sending_resumable_object_as_handle;
		  }
		  M_CAR(argument_or_result_cons) = resumable_object_as_handle;
	      }
	      else if (as_handle_p && frame_p) {
		  registration_number = 
			  ensure_registration_on_network(argument_or_result,
			  interface_frame_qm);
		  temp = ISVREF(icp_socket,(SI_Long)21L);
		  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
		  if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L)
		      resumable_object_as_handle = icp_cons_1(kind,
			      argument_or_result);
		  else {
		      rpc_name = remote_procedure_declaration_qm ? 
			      get_or_make_up_designation_for_block(remote_procedure_declaration_qm) 
			      : 
			      Qreturn_remote_procedure_result_as_object_from_handle;
		      handle = registration_number;
		      reference_type = kind;
		      sending_resumable_object_as_handle = 
			      make_sending_resumable_object_internal_1(rpc_name,
			      handle,Nil,Nil,Nil,icp_socket,Nil,Nil,
			      reference_type,Nil,Nil,Nil);
		      resumable_object_as_handle = 
			      sending_resumable_object_as_handle;
		  }
		  M_CAR(argument_or_result_cons) = resumable_object_as_handle;
	      }
	      else {
		  temp = ISVREF(icp_socket,(SI_Long)21L);
		  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
		  if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L)
		      temp_1 = TRUEP(Nil);
		  else {
		      if (SIMPLE_VECTOR_P(argument_or_result) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(argument_or_result)) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(argument_or_result,(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(argument_or_result,(SI_Long)1L);
			  gensymed_symbol_1 = SIMPLE_VECTOR_P(x2) && 
				  EQ(ISVREF(x2,(SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? x2 : Qnil;
		      }
		      else
			  gensymed_symbol_1 = Nil;
		      if (gensymed_symbol_1) {
			  sub_class_bit_vector = ISVREF(gensymed_symbol_1,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Object_class_description,
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
			      gensymed_symbol_2 = (SI_Long)1L;
			      gensymed_symbol_3 = 
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_2 = gensymed_symbol_2 << 
				      gensymed_symbol_3;
			      gensymed_symbol = gensymed_symbol & 
				      gensymed_symbol_2;
			      temp_1 = (SI_Long)0L < gensymed_symbol;
			  }
			  else
			      temp_1 = TRUEP(Nil);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      temp_1 =  !temp_1;
		  }
		  if (temp_1) {
		      result = tformat_text_string(2,string_constant_26,
			      argument_or_result);
		      POP_SPECIAL();
		      goto end_transform_rpc_argument_or_result_list;
		  }
		  else {
		      if (by_copy_with_handle_p && frame_p) {
			  temp = ISVREF(icp_socket,(SI_Long)21L);
			  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
			  if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L)
			      handle = (IFIX(ISVREF(icp_socket,
				      (SI_Long)22L)) >= (SI_Long)16L ? 
				      TRUEP(item_references_enabled_p(icp_socket)) 
				      : TRUEP(Nil)) ? T : 
				      ensure_registration_on_network(argument_or_result,
				      interface_frame_qm);
			  else {
			      result = tformat_text_string(2,
				      string_constant_27,argument_or_result);
			      POP_SPECIAL();
			      goto end_transform_rpc_argument_or_result_list;
			  }
		      }
		      else
			  handle = Nil;
		      if (argument_list_p) {
			  name = designation;
			  if (name);
			  else {
			      designation = 
				      get_or_make_up_designation_for_block(remote_procedure_declaration_qm);
			      name = designation;
			  }
		      }
		      else
			  name = Qreturn_remote_procedure_result;
		      temp = ISVREF(icp_socket,(SI_Long)21L);
		      temp_2 = ISVREF(icp_socket,(SI_Long)22L);
		      if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L)
			  resumable_object = icp_list_4(Qcopy,
				  argument_or_result,info,handle);
		      else {
			  temp_3 = argument_or_result;
			  temp_2 = 
				  remote_procedure_item_info_included_attributes(info);
			  temp = 
				  remote_procedure_item_info_excluded_attributes(info);
			  resumable_object = 
				  make_sending_resumable_object_given_options(name,
				  temp_3,icp_socket,interface_frame_qm,
				  priority,temp_2,temp,
				  remote_procedure_item_info_include_all_system_attributes(info) 
				  ? list_constant_2 : 
				  remote_procedure_item_info_included_system_attributes(info));
		      }
		      temp = ISVREF(icp_socket,(SI_Long)21L);
		      temp_2 = ISVREF(icp_socket,(SI_Long)22L);
		      if (!(IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L)) {
			  if (previous_sending_resumable_object_qm)
			      SVREF(previous_sending_resumable_object_qm,
				      FIX((SI_Long)3L)) = resumable_object;
			  SVREF(resumable_object,FIX((SI_Long)4L)) = 
				  previous_sending_resumable_object_qm;
			  previous_sending_resumable_object_qm = 
				  resumable_object;
		      }
		      M_CAR(argument_or_result_cons) = resumable_object;
		  }
	      }
	  }
	  else {
	      result = tformat_text_string(2,string_constant_28,
		      argument_or_result);
	      POP_SPECIAL();
	      goto end_transform_rpc_argument_or_result_list;
	  }
      }
      else {
	  temp = ISVREF(icp_socket,(SI_Long)21L);
	  temp_2 = ISVREF(icp_socket,(SI_Long)22L);
	  if ((IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)10L ? TRUEP(T) : 
		  TRUEP(Nil)) && as_handle_p && (CONSP(argument_or_result) 
		  && EQ(M_CDR(argument_or_result),Qsequence) || 
		  CONSP(argument_or_result) && 
		  EQ(M_CDR(argument_or_result),Qab_structure))) {
	      register_all_items_in_value(argument_or_result,
		      interface_frame_qm);
	      car_new_value = icp_cons_1(Qhandle,argument_or_result);
	      M_CAR(argument_or_result_cons) = car_new_value;
	  }
	  else {
	      temp = ISVREF(icp_socket,(SI_Long)21L);
	      temp_2 = ISVREF(icp_socket,(SI_Long)22L);
	      if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)8L) {
		  car_new_value = as_reference_p ? icp_cons_1(Qreference,
			  argument_or_result) : icp_list_4(Qcopy,
			  argument_or_result,info,Nil);
		  M_CAR(argument_or_result_cons) = car_new_value;
	      }
	  }
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:
      result = VALUES_1(Nil);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
  end_transform_rpc_argument_or_result_list:
    return result;
}

/* REGISTER-ALL-ITEMS-IN-VALUE */
Object register_all_items_in_value(value_or_item,interface_frame)
    Object value_or_item, interface_frame;
{
    Object gensymed_symbol, held_vector, element, elt_1, validated_elt, key;
    Object attribute_value, val, x2;
    SI_Long next_index, length_1, gensymed_symbol_1;
    char temp;

    x_note_fn_call(168,48);
    if (CONSP(value_or_item) && EQ(M_CDR(value_or_item),Qsequence)) {
	gensymed_symbol = value_or_item;
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
	register_all_items_in_value(element,interface_frame);
	goto next_loop;
      end_loop:;
    }
    else if (CONSP(value_or_item) && EQ(M_CDR(value_or_item),Qab_structure)) {
	gensymed_symbol = value_or_item;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	key = Nil;
	attribute_value = Nil;
	val = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	key = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
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
	val = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	register_all_items_in_value(val,interface_frame);
	goto next_loop_1;
      end_loop_1:;
    }
    else {
	if (SIMPLE_VECTOR_P(value_or_item) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_or_item)) > 
		(SI_Long)2L &&  !EQ(ISVREF(value_or_item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(value_or_item,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    ensure_registration_on_network(value_or_item,interface_frame);
    }
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

static Object Qg2_defstruct_structure_name_code_body_invocation_g2_struct;  /* g2-defstruct-structure-name::code-body-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_procedure_invocation_g2_struct;  /* g2-defstruct-structure-name::procedure-invocation-g2-struct */

/* GET-RPC-PRIORITY-FROM-COMPUTATION-CONTEXT */
Object get_rpc_priority_from_computation_context()
{
    Object type_name;
    char temp;

    x_note_fn_call(168,49);
    if (SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct))
	return VALUES_1(ISVREF(Current_computation_instance,(SI_Long)14L));
    else {
	if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	    type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp);
	    else
		temp = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(ISVREF(Current_computation_instance,(SI_Long)10L));
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qg2_defstruct_structure_name_sending_resumable_object_g2_struct;  /* g2-defstruct-structure-name::sending-resumable-object-g2-struct */

/* CALL-REMOTE-PROCEDURE-AFTER-CHECKS */
Object call_remote_procedure_after_checks(calling_code_body,argument_list,
	    icp_socket_qm,remote_procedure_declaration,icp_interface)
    Object calling_code_body, argument_list, icp_socket_qm;
    Object remote_procedure_declaration, icp_interface;
{
    Object remote_procedure_identifier, remote_procedure_call, svref_new_value;
    Object proc_push_modify_macro_arg, car_1, cdr_1, temp, temp_1, arg;
    Object ab_loop_list_, icp_push_modify_macro_arg;

    x_note_fn_call(168,50);
    remote_procedure_identifier = 
	    make_outgoing_remote_procedure_identifier_from_declaration(remote_procedure_declaration);
    remote_procedure_call = 
	    make_outgoing_remote_procedure_call(remote_procedure_identifier,
	    remote_procedure_declaration,icp_socket_qm,icp_interface);
    svref_new_value = ISVREF(calling_code_body,(SI_Long)10L);
    SVREF(remote_procedure_call,FIX((SI_Long)10L)) = svref_new_value;
    SVREF(remote_procedure_call,FIX((SI_Long)12L)) = calling_code_body;
    proc_push_modify_macro_arg = remote_procedure_call;
    car_1 = proc_push_modify_macro_arg;
    cdr_1 = ISVREF(calling_code_body,(SI_Long)13L);
    svref_new_value = proc_cons_1(car_1,cdr_1);
    SVREF(calling_code_body,FIX((SI_Long)13L)) = svref_new_value;
    svref_new_value = copy_frame_serial_number(Current_frame_serial_number);
    SVREF(remote_procedure_call,FIX((SI_Long)9L)) = svref_new_value;
    SVREF(remote_procedure_call,FIX((SI_Long)11L)) = Nil;
    SVREF(remote_procedure_call,FIX((SI_Long)13L)) = Nil;
    SVREF(remote_procedure_identifier,FIX((SI_Long)3L)) = 
	    remote_procedure_call;
    temp = ISVREF(icp_socket_qm,(SI_Long)21L);
    temp_1 = ISVREF(icp_socket_qm,(SI_Long)22L);
    if (!(IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)8L)) {
	arg = Nil;
	ab_loop_list_ = argument_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(arg) && EQ(ISVREF(arg,(SI_Long)0L),
		Qg2_defstruct_structure_name_sending_resumable_object_g2_struct) 
		&&  !TRUEP(ISVREF(arg,(SI_Long)2L))) {
	    icp_push_modify_macro_arg = arg;
	    car_1 = icp_push_modify_macro_arg;
	    cdr_1 = ISVREF(remote_procedure_identifier,(SI_Long)5L);
	    svref_new_value = icp_cons_1(car_1,cdr_1);
	    SVREF(remote_procedure_identifier,FIX((SI_Long)5L)) = 
		    svref_new_value;
	    SVREF(arg,FIX((SI_Long)5L)) = remote_procedure_identifier;
	}
	goto next_loop;
      end_loop:;
    }
    return send_rpc_call(ISVREF(icp_socket_qm,(SI_Long)4L),
	    ISVREF(remote_procedure_call,(SI_Long)10L),
	    ISVREF(remote_procedure_declaration,(SI_Long)21L),
	    remote_procedure_identifier,argument_list);
}

static Object string_constant_29;  /* "The returned value was not of the type ~NT, ~
				    *                                as required by the declaration for ~NF."
				    */

static Object Qlong;               /* long */

static Object list_constant_3;     /* # */

static Object string_constant_30;  /* "The returned value ~A was not of the type ~NT, ~
				    *                                  as required by the declaration for ~NF."
				    */

/* CHECK-REMOTE-PROCEDURE-RESULT-LIST-TYPES */
Object check_remote_procedure_result_list_types(returned_values,
	    return_descriptions,remote_procedure_declaration)
    Object returned_values, return_descriptions, remote_procedure_declaration;
{
    Object evaluation_value_or_frame_qm, ab_loop_list_, rest_return_p, index_1;
    Object return_type, return_description, restp, ab_loop_iter_flag_, temp;
    Object gensymed_symbol_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, temp_to_reclaim;
    Object resumable_objects_reclaimed_p, type1, type2, constant_value;
    Object handled_object_qm;
    SI_Long gensymed_symbol, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(168,51);
    evaluation_value_or_frame_qm = Nil;
    ab_loop_list_ = returned_values;
    rest_return_p = Nil;
    index_1 = FIX((SI_Long)0L);
    return_type = Nil;
    return_description = Nil;
    restp = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    evaluation_value_or_frame_qm = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_)) {
	temp = rest_return_p;
	if (temp);
	else
	    temp = restp;
	rest_return_p = temp;
	index_1 = rest_return_p ? index_1 : FIXNUM_ADD1(index_1);
    }
    gensymed_symbol = IFIX(index_1) * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(return_descriptions,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(return_descriptions,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(return_descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description))
	gensymed_symbol_1 = 
		getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
    return_type = gensymed_symbol_1;
    gensymed_symbol = IFIX(index_1) * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(return_descriptions,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(return_descriptions,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(return_descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description)) {
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	return_description = gensymed_symbol_1;
    }
    else
	return_description = Nil;
    temp = rest_return_p;
    if (temp);
    else
	temp = getf(return_description,Kall_remaining,_);
    restp = temp;
    if (SIMPLE_VECTOR_P(evaluation_value_or_frame_qm) && 
	    EQ(ISVREF(evaluation_value_or_frame_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct));
    else {
	gensymed_symbol_1 = evaluation_value_or_frame_qm;
	temp_1 = FIXNUMP(gensymed_symbol_1);
	if (temp_1);
	else
	    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol_1) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = gensymed_symbol_1 ? SYMBOLP(gensymed_symbol_1) : 
		    TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol_1) 
		    != (SI_Long)0L;
	if (temp_1);
	else if (CONSP(gensymed_symbol_1)) {
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp_1 = EQ(gensymed_symbol_1,Qtruth_value);
	    if (temp_1);
	    else
		temp_1 = EQ(gensymed_symbol_1,Qiteration_state);
	    if (temp_1);
	    else if (SYMBOLP(gensymed_symbol_1)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol_1;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol_1) & 
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
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_3:
		if ( !TRUEP(marked))
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
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
	if ( !temp_1) {
	    temp_to_reclaim = Nil;
	    ab_loop_list_ = returned_values;
	    resumable_objects_reclaimed_p = Nil;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_4;
	    temp_to_reclaim = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol_1 = temp_to_reclaim;
	    temp_1 = FIXNUMP(gensymed_symbol_1);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) 
			!= (SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol_1) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol_1 ? SYMBOLP(gensymed_symbol_1) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = 
			INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol_1) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol_1)) {
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_1 = EQ(gensymed_symbol_1,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol_1,Qiteration_state);
		if (temp_1);
		else if (SYMBOLP(gensymed_symbol_1)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = gensymed_symbol_1;
		    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol_1) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
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
	    if (temp_1)
		reclaim_evaluation_value(temp_to_reclaim);
	    if ( !TRUEP(resumable_objects_reclaimed_p)) {
		if (SIMPLE_VECTOR_P(temp_to_reclaim) && 
			EQ(ISVREF(temp_to_reclaim,(SI_Long)0L),
			Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
			    {
		    reclaim_receiving_resumable_object(temp_to_reclaim);
		    resumable_objects_reclaimed_p = T;
		}
	    }
	    goto next_loop_4;
	  end_loop_4:;
	    return tformat_text_string(3,string_constant_29,return_type,
		    remote_procedure_declaration);
	}
	else {
	    if (valid_datum_type_specification_p(return_type)) {
		type1 = return_type;
		type2 = evaluation_value_type(evaluation_value_or_frame_qm);
		temp_1 = EQ(type1,type2);
		if (temp_1);
		else
		    temp_1 = EQ(type1,Qnumber) ? EQ(type2,Qnumber) || 
			    EQ(type2,Qinteger) || EQ(type2,Qfloat) || 
			    EQ(type2,Qlong) || 
			    lookup_global_or_kb_specific_property_value(type2,
			    Numeric_data_type_gkbprop) : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = EQ(type2,Qnumber) ? EQ(type1,Qnumber) || 
			    EQ(type1,Qinteger) || EQ(type1,Qfloat) || 
			    EQ(type1,Qlong) || 
			    lookup_global_or_kb_specific_property_value(type1,
			    Numeric_data_type_gkbprop) : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = EQ(type1,Qinteger) || memq_function(type1,
			    list_constant_3) ? EQ(type2,Qinteger) || 
			    memq_function(type2,list_constant_3) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else {
		if (EQ(Qhandle,getf(return_type,Kkind,_)) && 
			FIXNUMP(evaluation_value_or_frame_qm)) {
		    constant_value = evaluation_value_or_frame_qm;
		    handled_object_qm = 
			    get_item_from_local_handle(constant_value,
			    Current_icp_socket);
		    temp_1 = handled_object_qm ? 
			    TRUEP(type_specification_type_p(handled_object_qm,
			    return_type)) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1);
		else {
		    temp_to_reclaim = Nil;
		    ab_loop_list_ = returned_values;
		    resumable_objects_reclaimed_p = Nil;
		  next_loop_8:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_8;
		    temp_to_reclaim = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    gensymed_symbol_1 = temp_to_reclaim;
		    temp_1 = FIXNUMP(gensymed_symbol_1);
		    if (temp_1);
		    else
			temp_1 = 
				INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) 
				!= (SI_Long)0L ? 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
				== (SI_Long)1L : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol_1) 
				!= (SI_Long)0L ? 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
				== (SI_Long)1L : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = gensymed_symbol_1 ? 
				SYMBOLP(gensymed_symbol_1) : TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = 
				INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol_1) 
				!= (SI_Long)0L;
		    if (temp_1);
		    else if (CONSP(gensymed_symbol_1)) {
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			temp_1 = EQ(gensymed_symbol_1,Qtruth_value);
			if (temp_1);
			else
			    temp_1 = EQ(gensymed_symbol_1,Qiteration_state);
			if (temp_1);
			else if (SYMBOLP(gensymed_symbol_1)) {
			    skip_list = CDR(Defined_evaluation_value_types);
			    key_value = gensymed_symbol_1;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(gensymed_symbol_1) & 
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_10:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_2 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_2,temp);
			    MVS_2(result,succ,marked);
			  next_loop_11:
			    if ( !TRUEP(marked))
				goto end_loop_10;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_2 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_2,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_11;
			  end_loop_10:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_3;
			    goto next_loop_10;
			  end_loop_11:
			  end_3:
			    level = level - (SI_Long)1L;
			    goto next_loop_9;
			  end_loop_9:;
			    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				    key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				    TRUEP(Nil)) : TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			reclaim_evaluation_value(temp_to_reclaim);
		    if ( !TRUEP(resumable_objects_reclaimed_p)) {
			if (SIMPLE_VECTOR_P(temp_to_reclaim) && 
				EQ(ISVREF(temp_to_reclaim,(SI_Long)0L),
				Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
				    {
			    reclaim_receiving_resumable_object(temp_to_reclaim);
			    resumable_objects_reclaimed_p = T;
			}
		    }
		    goto next_loop_8;
		  end_loop_8:;
		    return tformat_text_string(4,string_constant_30,
			    evaluation_value_value(evaluation_value_or_frame_qm),
			    return_type,remote_procedure_declaration);
		}
	    }
	}
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    temp = Nil;
    goto end_4;
    temp = Qnil;
  end_4:;
    return VALUES_1(temp);
}

static Object string_constant_31;  /* "~A values were returned, but the remote procedure declaration ~
				    *                 ~a declares that ~a values would be returned."
				    */

static Object string_constant_32;  /* "Procedure ~a is requesting more values than ~a can return." */

/* CHECK-THAT-REMOTE-PROCEDURE-CAN-RECEIVE-VALUES */
Object check_that_remote_procedure_can_receive_values(procedure_index,
	    returned_values)
    Object procedure_index, returned_values;
{
    Object ok_p, remote_procedure_identifier, remote_procedure_call, caller;
    Object remote_procedure_declaration, return_descriptions;
    Object formal_return_restp_index, caller_procedure_invocation;
    Object current_computation_frame, i, gensymed_symbol_1, temp;
    Object error_string_qm;
    SI_Long values_count, count_1, gensymed_symbol;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(168,52);
    ok_p = Nil;
    remote_procedure_identifier = 
	    lookup_remote_procedure_identifier_from_index(procedure_index);
    remote_procedure_call = remote_procedure_identifier ? 
	    ISVREF(remote_procedure_identifier,(SI_Long)3L) : Nil;
    caller = remote_procedure_call ? ISVREF(remote_procedure_call,
	    (SI_Long)12L) : Nil;
    if (caller) {
	remote_procedure_declaration = ISVREF(remote_procedure_call,
		(SI_Long)23L);
	return_descriptions = ISVREF(remote_procedure_declaration,
		(SI_Long)25L);
	formal_return_restp_index = Nil;
	caller_procedure_invocation = ISVREF(caller,(SI_Long)11L);
	current_computation_frame = ISVREF(caller_procedure_invocation,
		(SI_Long)23L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  values_count = IFIX(length(returned_values));
	  count_1 = IFIX(ISVREF(caller,(SI_Long)6L));
	  i = FIXNUM_SUB1(var_count(return_descriptions));
	  if ((SI_Long)0L <= IFIX(i)) {
	      gensymed_symbol = IFIX(i) * (SI_Long)2L + (SI_Long)1L;
	      gensymed_symbol_1 = FIXNUM_LE(ISVREF(return_descriptions,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(return_descriptions,gensymed_symbol + 
		      IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(return_descriptions,(gensymed_symbol 
		      >>  -  - (SI_Long)10L) + (SI_Long)2L),
		      gensymed_symbol & (SI_Long)1023L);
	      if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		      Kgeneral_description)) {
		  gensymed_symbol_1 = CDR(gensymed_symbol_1);
		  temp = gensymed_symbol_1;
	      }
	      else
		  temp = Nil;
	      temp_1 = TRUEP(getf(temp,Kall_remaining,_));
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      formal_return_restp_index = i;
	  if (formal_return_restp_index ? values_count < 
		  IFIX(FIXNUM_SUB1(var_count(return_descriptions))) : 
		  values_count != IFIX(var_count(return_descriptions))) {
	      temp = 
		      get_or_make_up_designation_for_block(remote_procedure_declaration);
	      signal_code_body_invocation_error(9,caller,Qrpc_error,
		      FIX((SI_Long)1L),tformat_text_string(4,
		      string_constant_31,FIX(values_count),temp,
		      var_count(return_descriptions)),Nil,Nil,Nil,Nil,Nil);
	  }
	  else if (count_1 > values_count) {
	      temp = 
		      get_or_make_up_designation_for_block(ISVREF(ISVREF(caller,
		      (SI_Long)11L),(SI_Long)23L));
	      signal_code_body_invocation_error(9,caller,Qrpc_error,
		      FIX((SI_Long)1L),tformat_text_string(3,
		      string_constant_32,temp,
		      get_or_make_up_designation_for_block(remote_procedure_declaration)),
		      Nil,Nil,Nil,Nil,Nil);
	  }
	  else {
	      error_string_qm = 
		      check_remote_procedure_result_list_types(returned_values,
		      return_descriptions,remote_procedure_declaration);
	      if (error_string_qm)
		  signal_code_body_invocation_error(9,caller,Qrpc_error,
			  FIX((SI_Long)1L),error_string_qm,Nil,Nil,Nil,Nil,
			  Nil);
	      else
		  ok_p = T;
	  }
	POP_SPECIAL();
    }
    return VALUES_1(ok_p);
}

/* CDR-OF-SECOND-IN-PLACE */
Object cdr_of_second_in_place(list_1)
    Object list_1;
{
    Object temp;

    x_note_fn_call(168,53);
    temp = SECOND(list_1);
    return VALUES_1(nconc2(phrase_list_2(FIRST(list_1),CDR(temp)),
	    CDDR(list_1)));
}

/* MERGE-OBJECT-PASSING-PROPERTY-LISTS */
Object merge_object_passing_property_lists(list_of_property_lists)
    Object list_of_property_lists;
{
    Object merged_property_list, property_list, ab_loop_list_;
    Object property_list_element, ab_loop_list__1;

    x_note_fn_call(168,54);
    merged_property_list = Nil;
    property_list = Nil;
    ab_loop_list_ = list_of_property_lists;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    property_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    property_list_element = Nil;
    ab_loop_list__1 = property_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    property_list_element = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    merged_property_list = phrase_cons(property_list_element,
	    merged_property_list);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return nreverse(merged_property_list);
    return VALUES_1(Qnil);
}

static Object Qsimplify_associative_operation;  /* simplify-associative-operation */

static Object string_constant_33;  /* "1y1n83-8jy1m1m9k83*5y1m9k83-lJy1m83-1fy83-lJy1m83-7Ky83-gRy1n83-gRy1t1m9k83-9y1m9k83jRy1m9k83-Ty1m9k83-Gy83jNy1m9k83-*0y1m9k83Gr" */

static Object string_constant_34;  /* "y83-cpy1m9k83-Ay1n83-Gyps1n83-gRy1x1m9k83-9y1m9k83jRy1m9k83-Ty1m9k83-Gy83jNy1m9k83-*0y1m9k830*y1m9k83Gry1m9k83*Xy1m9k9l1m9k83-qy" */

static Object string_constant_35;  /* "836Iy1m9k83-Ay1n83-Gyp1m9mw1m83-cpy83-MTy1o83-cpy1n83-MTy1m9k83vy83-cpy1nmln9n1m83-MTy836Iy1n83-MTy1p83dey1m9k83-*1y1m9k83-7Hy1m" */

static Object string_constant_36;  /* "9k83=hy83dey1mlo1n833*y1p1m9k9l1m9k83-7Hy1m9k83D0y1m9k83=Iy833*y1m83-gSyp1n830By1p1m9k9l1m9k83-7Hy1m9k83D0y1m9k83=Iy830By1m83-gS" */

static Object string_constant_37;  /* "yp1n83F2y1p1m9k9l1m9k83-7Hy1m9k83D0y1m9k83=Iy83F2y1m83-gSyp1n83lIy1n1m9k83DAy1m9k83-Py839ay1n83DAyn1m1l8328y01n83lIy1n1m9k83E=y1" */

static Object string_constant_38;  /* "m9k83-Py83-ky1n83E=yn1m1l8328y01n83lIy1n1m9k83BCy1m9k83-Py83-2y1n83BCyn1m1l8328y0" */

static Object Qnetwork_interface;  /* network-interface */

static Object list_constant_4;     /* # */

static Object Qdo_not_put_in_attribute_tables;  /* do-not-put-in-attribute-tables */

static Object list_constant_5;     /* # */

static Object Qdo_not_save;        /* do-not-save */

static Object Qcreation_attributes;  /* creation-attributes */

static Object Qitem_reference_options;  /* item-reference-options */

static Object Qnames_of_remote_interface;  /* names-of-remote-interface */

static Object Qclass_of_remote_interface;  /* class-of-remote-interface */

/* ENABLE-REFERENCES-FOR-ITEM-PASSING */
Object enable_references_for_item_passing()
{
    Object scope_conses, ab_loopvar_, class_1, temp, slot_name, ab_loop_list_;
    Object slot_description, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, temp_2, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, entry;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(168,55);
    if ( !TRUEP(G2_to_g2_uses_references_p)) {
	if (PUSH_AREA(Dynamic_area,0)) {
	    clear_optimized_constants();
	    push_optimized_constant(Qquote);
	    push_optimized_constant(Qthe);
	    push_optimized_constant(Qstar);
	    push_optimized_constant(Qsimplify_associative_operation);
	    add_grammar_rules_function(regenerate_optimized_constant(list(6,
		    string_constant_33,string_constant_34,
		    string_constant_35,string_constant_36,
		    string_constant_37,string_constant_38)));
	}
	POP_AREA(0);
	G2_to_g2_uses_references_p = T;
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar_ = Qnetwork_interface;
	class_1 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(ab_loopvar_);
	next_loop:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  temp = M_CAR(ab_loopvar_);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  class_1 = temp;
	  slot_name = Nil;
	  ab_loop_list_ = list_constant_4;
	  slot_description = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  slot_name = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  skip_list = CDR(Symbol_properties_table);
	  key_value = class_1;
	  key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_3:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_4:
	  if ( !TRUEP(marked))
	      goto end_loop_3;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = class_1;
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
		  temp_2 = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp_2,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp_2 = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = Nil;
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
		  temp_2 = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp_2,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp_2 = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = Nil;
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
	next_loop_5:
	  if (level < ab_loop_bind_)
	      goto end_loop_5;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_6:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_7:
	  if ( !TRUEP(marked))
	      goto end_loop_6;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_7;
	end_loop_6:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		  ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		  (SI_Long)3L) : Nil) : Nil;
	  if (kb_properties);
	  else
	      kb_properties = Nil;
	  if (kb_properties) {
	      skip_list = CDR(kb_properties);
	      key_value = Class_description_gkbprop;
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
	      bottom_level = (SI_Long)0L;
	      marked = Nil;
	      pred = M_CAR(skip_list);
	      curr = Nil;
	      succ = Nil;
	      level = (SI_Long)31L;
	      ab_loop_bind_ = bottom_level;
	    next_loop_8:
	      if (level < ab_loop_bind_)
		  goto end_loop_8;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_9:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	    next_loop_10:
	      if ( !TRUEP(marked))
		  goto end_loop_9;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	      goto next_loop_10;
	    end_loop_9:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
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
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
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
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_12:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	    next_loop_13:
	      if ( !TRUEP(marked))
		  goto end_loop_12;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	      goto next_loop_13;
	    end_loop_12:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
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
	      resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if (resulting_value);
	      else
		  resulting_value = Nil;
	  }
	  gensymed_symbol = resulting_value;
	  slot_description = 
		  get_slot_description_of_class_description_function(slot_name,
		  gensymed_symbol,Nil);
	  temp_2 = ldelete(4,Qdo_not_put_in_attribute_tables,
		  ISVREF(slot_description,(SI_Long)9L),Kkey,
		  SYMBOL_FUNCTION(Qcar));
	  SVREF(slot_description,FIX((SI_Long)9L)) = temp_2;
	  goto next_loop_1;
	end_loop_1:;
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
	class_1 = Qmiscellaneous_parameters;
	slot_name = Nil;
	ab_loop_list_ = list_constant_5;
	slot_description = Nil;
      next_loop_14:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_14;
	slot_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	skip_list = CDR(Symbol_properties_table);
	key_value = class_1;
	key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
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
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_16:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_17:
	if ( !TRUEP(marked))
	    goto end_loop_16;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_17;
      end_loop_16:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_5;
	goto next_loop_16;
      end_loop_17:
      end_5:
	level = level - (SI_Long)1L;
	goto next_loop_15;
      end_loop_15:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
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
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
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
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
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
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
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
      next_loop_18:
	if (level < ab_loop_bind_)
	    goto end_loop_18;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_19:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_20:
	if ( !TRUEP(marked))
	    goto end_loop_19;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_20;
      end_loop_19:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_6;
	goto next_loop_19;
      end_loop_20:
      end_6:
	level = level - (SI_Long)1L;
	goto next_loop_18;
      end_loop_18:;
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
	  next_loop_21:
	    if (level < ab_loop_bind_)
		goto end_loop_21;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_22:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_23:
	    if ( !TRUEP(marked))
		goto end_loop_22;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_23;
	  end_loop_22:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_7;
	    goto next_loop_22;
	  end_loop_23:
	  end_7:
	    level = level - (SI_Long)1L;
	    goto next_loop_21;
	  end_loop_21:;
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_24:
	    if (level < ab_loop_bind_)
		goto end_loop_24;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_25:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_26:
	    if ( !TRUEP(marked))
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_26;
	  end_loop_25:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_8;
	    goto next_loop_25;
	  end_loop_26:
	  end_8:
	    level = level - (SI_Long)1L;
	    goto next_loop_24;
	  end_loop_24:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	slot_description = 
		get_slot_description_of_class_description_function(slot_name,
		gensymed_symbol,Nil);
	temp_2 = ldelete(4,Qdo_not_save,ldelete(4,
		Qdo_not_put_in_attribute_tables,ISVREF(slot_description,
		(SI_Long)9L),Kkey,SYMBOL_FUNCTION(Qcar)),Kkey,
		SYMBOL_FUNCTION(Qcar));
	SVREF(slot_description,FIX((SI_Long)9L)) = temp_2;
	goto next_loop_14;
      end_loop_14:;
	entry = assq_function(Qnetwork_interface,
		List_of_user_overridable_system_slots);
	temp_2 = nconc2(SECOND(entry),gensym_list_4(Qcreation_attributes,
		Qitem_reference_options,Qnames_of_remote_interface,
		Qclass_of_remote_interface));
	M_SECOND(entry) = temp_2;
	temp_2 = nconc2(FOURTH(entry),gensym_list_4(Qcreation_attributes,
		Qitem_reference_options,Qnames_of_remote_interface,
		Qclass_of_remote_interface));
	M_FOURTH(entry) = temp_2;
	return VALUES_1(Evaluation_true_value);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_39;  /* "~A is not an item, and so cannot be registered on the network" */

static Object Qcannot_register_non_item;  /* cannot-register-non-item */

static Object string_constant_40;  /* "~A is not an item, and so cannot be an ICP interface" */

static Object Qicp_interface_not_item;  /* icp-interface-not-item */

static Object Qgsi_interface;      /* gsi-interface */

static Object Qg2_to_g2_data_interface;  /* g2-to-g2-data-interface */

static Object string_constant_41;  /* "The object ~NF is neither a GSI nor a G2-to-G2 interface" */

static Object Qno_icp_interface_capability;  /* no-icp-interface-capability */

static Object string_constant_42;  /* "There is no ICP connection for ~NF" */

static Object Qno_icp_connection;  /* no-icp-connection */

static Object string_constant_43;  /* "The ICP connection for ~NF is not open" */

static Object Qicp_connection_not_open;  /* icp-connection-not-open */

static Object array_constant;      /* # */

static Object Qno_error_in_register_on_network;  /* no-error-in-register-on-network */

/* REGISTER-ON-NETWORK-LISP-SIDE */
Object register_on_network_lisp_side(rpc_object,icp_interface)
    Object rpc_object, icp_interface;
{
    Object x2, temp_1, gensymed_symbol, sub_class_bit_vector, icp_socket_qm;
    Object registration_number;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(168,56);
    if (SIMPLE_VECTOR_P(rpc_object) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(rpc_object)) > (SI_Long)2L &&  
	    !EQ(ISVREF(rpc_object,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(rpc_object,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	temp_1 = tformat_text_string(2,string_constant_39,rpc_object);
	return VALUES_3(No_resumable_object_index,
		Qcannot_register_non_item,temp_1);
    }
    if (SIMPLE_VECTOR_P(icp_interface) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_interface)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(icp_interface,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(icp_interface,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	temp_1 = tformat_text_string(2,string_constant_40,icp_interface);
	return VALUES_3(No_resumable_object_index,Qicp_interface_not_item,
		temp_1);
    }
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_interface,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
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
    if (temp);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qg2_to_g2_data_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,
		    (SI_Long)1L),(SI_Long)19L);
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
    }
    if ( !temp) {
	temp_1 = tformat_text_string(1,string_constant_41);
	return VALUES_3(No_resumable_object_index,
		Qno_icp_interface_capability,temp_1);
    }
    icp_socket_qm = icp_socket_of_interface_object(icp_interface);
    if ( !TRUEP(icp_socket_qm)) {
	temp_1 = tformat_text_string(2,string_constant_42,icp_interface);
	return VALUES_3(No_resumable_object_index,Qno_icp_connection,temp_1);
    }
    if ( !(icp_connection_open_p(icp_socket_qm) &&  
	    !TRUEP(icp_connection_being_shutdown_qm(icp_socket_qm)))) {
	temp_1 = tformat_text_string(2,string_constant_43,icp_interface);
	return VALUES_3(No_resumable_object_index,Qicp_connection_not_open,
		temp_1);
    }
    registration_number = register_item_with_socket(rpc_object,
	    icp_socket_qm,Nil);
    temp_1 = copy_constant_wide_string_given_length(array_constant,
	    FIX((SI_Long)0L));
    return VALUES_3(registration_number,Qno_error_in_register_on_network,
	    temp_1);
}

static Object string_constant_44;  /* "The handle ~A must be 0 or greater" */

static Object Qno_such_network_item;  /* no-such-network-item */

static Object Qout_of_range_handle;  /* out-of-range-handle */

static Object string_constant_45;  /* "There is no item registered for handle ~S under interface ~NF" */

static Object Qno_such_item_registered;  /* no-such-item-registered */

static Object Qno_error_in_get_item_from_network_handle;  /* no-error-in-get-item-from-network-handle */

/* GET-ITEM-FROM-NETWORK-HANDLE-LISP-SIDE */
Object get_item_from_network_handle_lisp_side(g2_network_handle,icp_interface)
    Object g2_network_handle, icp_interface;
{
    Object network_handle, temp, x2, gensymed_symbol, sub_class_bit_vector;
    Object icp_socket_qm, network_registry_entry_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(168,57);
    network_handle = g2_network_handle;
    if ( !(IFIX(network_handle) > (SI_Long)-1L)) {
	temp = tformat_text_string(2,string_constant_44,network_handle);
	return VALUES_3(Qno_such_network_item,Qout_of_range_handle,temp);
    }
    if (SIMPLE_VECTOR_P(icp_interface) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_interface)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(icp_interface,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(icp_interface,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1) {
	temp = tformat_text_string(2,string_constant_40,icp_interface);
	return VALUES_3(Qno_such_network_item,Qicp_interface_not_item,temp);
    }
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_interface,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qg2_to_g2_data_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,
		    (SI_Long)1L),(SI_Long)19L);
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
		temp_1 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    if ( !temp_1) {
	temp = tformat_text_string(1,string_constant_41);
	return VALUES_3(Qno_such_network_item,Qno_icp_interface_capability,
		temp);
    }
    icp_socket_qm = icp_socket_of_interface_object(icp_interface);
    if ( !TRUEP(icp_socket_qm)) {
	temp = tformat_text_string(2,string_constant_42,icp_interface);
	return VALUES_3(Qno_such_network_item,Qno_icp_connection,temp);
    }
    if ( !(icp_connection_open_p(icp_socket_qm) &&  
	    !TRUEP(icp_connection_being_shutdown_qm(icp_socket_qm)))) {
	temp = tformat_text_string(2,string_constant_43,icp_interface);
	return VALUES_3(Qno_such_network_item,Qicp_connection_not_open,temp);
    }
    network_registry_entry_qm = get_item_from_local_handle(network_handle,
	    icp_socket_qm);
    if ( !TRUEP(network_registry_entry_qm)) {
	temp = tformat_text_string(3,string_constant_45,network_handle,
		icp_interface);
	return VALUES_3(Qno_such_network_item,Qno_such_item_registered,temp);
    }
    temp = copy_constant_wide_string_given_length(array_constant,
	    FIX((SI_Long)0L));
    return VALUES_3(network_registry_entry_qm,
	    Qno_error_in_get_item_from_network_handle,temp);
}

static Object string_constant_46;  /* "~A is not an item, and so cannot have a network handle" */

static Object string_constant_47;  /* "No handle for variable ~NF under ICP interface ~NF" */

static Object Qno_such_handle;     /* no-such-handle */

static Object Qno_error_in_get_network_handle_from_item;  /* no-error-in-get-network-handle-from-item */

/* GET-NETWORK-HANDLE-FROM-ITEM-LISP-SIDE */
Object get_network_handle_from_item_lisp_side(rpc_object,icp_interface)
    Object rpc_object, icp_interface;
{
    Object x2, temp_1, gensymed_symbol, sub_class_bit_vector, icp_socket_qm;
    Object handle, wide_string_bv16;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value;
    char temp;

    x_note_fn_call(168,58);
    if (SIMPLE_VECTOR_P(rpc_object) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(rpc_object)) > (SI_Long)2L &&  
	    !EQ(ISVREF(rpc_object,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(rpc_object,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	temp_1 = tformat_text_string(2,string_constant_46,rpc_object);
	return VALUES_3(No_resumable_object_index,
		Qcannot_register_non_item,temp_1);
    }
    if (SIMPLE_VECTOR_P(icp_interface) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_interface)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(icp_interface,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(icp_interface,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	temp_1 = tformat_text_string(2,string_constant_40,icp_interface);
	return VALUES_3(No_resumable_object_index,Qicp_interface_not_item,
		temp_1);
    }
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_interface,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
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
    if (temp);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qg2_to_g2_data_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,
		    (SI_Long)1L),(SI_Long)19L);
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
    }
    if ( !temp) {
	temp_1 = tformat_text_string(1,string_constant_41);
	return VALUES_3(No_resumable_object_index,
		Qno_icp_interface_capability,temp_1);
    }
    icp_socket_qm = icp_socket_of_interface_object(icp_interface);
    if ( !TRUEP(icp_socket_qm)) {
	temp_1 = tformat_text_string(2,string_constant_42,icp_interface);
	return VALUES_3(No_resumable_object_index,Qno_icp_connection,temp_1);
    }
    if ( !(icp_connection_open_p(icp_socket_qm) &&  
	    !TRUEP(icp_connection_being_shutdown_qm(icp_socket_qm)))) {
	temp_1 = tformat_text_string(2,string_constant_43,icp_interface);
	return VALUES_3(No_resumable_object_index,Qicp_connection_not_open,
		temp_1);
    }
    handle = get_icp_object_index_for_registered_item(rpc_object,
	    ISVREF(icp_socket_qm,(SI_Long)4L));
    if ( !TRUEP(handle)) {
	temp_1 = tformat_text_string(3,string_constant_47,rpc_object,
		icp_interface);
	return VALUES_3(No_resumable_object_index,Qno_such_handle,temp_1);
    }
    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = (SI_Long)0L & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
    return VALUES_3(handle,Qno_error_in_get_network_handle_from_item,
	    wide_string_bv16);
}

static Object string_constant_48;  /* "~A is neither an item nor an integer, and so cannot be deregistered" */

static Object Qcannot_deregister_non_item;  /* cannot-deregister-non-item */

static Object string_constant_49;  /* "There is no item registered for handle ~S ~
				    *                   under interface ~NF"
				    */

static Object Qno_error_in_deregister_on_network;  /* no-error-in-deregister-on-network */

/* DEREGISTER-ON-NETWORK-LISP-SIDE */
Object deregister_on_network_lisp_side(rpc_object_or_handle,icp_interface)
    Object rpc_object_or_handle, icp_interface;
{
    Object x2, temp_1, temp_2, gensymed_symbol, sub_class_bit_vector;
    Object icp_socket_qm, registered_item_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(168,59);
    if (SIMPLE_VECTOR_P(rpc_object_or_handle) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(rpc_object_or_handle)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(rpc_object_or_handle,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(rpc_object_or_handle,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else
	temp = FIXNUMP(rpc_object_or_handle);
    if ( !temp) {
	temp_1 = Evaluation_false_value;
	temp_2 = tformat_text_string(2,string_constant_48,
		rpc_object_or_handle);
	return VALUES_3(temp_1,Qcannot_deregister_non_item,temp_2);
    }
    if (SIMPLE_VECTOR_P(icp_interface) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_interface)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(icp_interface,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(icp_interface,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	temp_1 = Evaluation_false_value;
	temp_2 = tformat_text_string(2,string_constant_40,icp_interface);
	return VALUES_3(temp_1,Qicp_interface_not_item,temp_2);
    }
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_interface,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
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
    if (temp);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qg2_to_g2_data_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,
		    (SI_Long)1L),(SI_Long)19L);
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
    }
    if ( !temp) {
	temp_1 = Evaluation_false_value;
	temp_2 = tformat_text_string(1,string_constant_41);
	return VALUES_3(temp_1,Qno_icp_interface_capability,temp_2);
    }
    icp_socket_qm = icp_socket_of_interface_object(icp_interface);
    if ( !TRUEP(icp_socket_qm)) {
	temp_1 = Evaluation_false_value;
	temp_2 = tformat_text_string(2,string_constant_42,icp_interface);
	return VALUES_3(temp_1,Qno_icp_connection,temp_2);
    }
    if ( !(icp_connection_open_p(icp_socket_qm) &&  
	    !TRUEP(icp_connection_being_shutdown_qm(icp_socket_qm)))) {
	temp_1 = Evaluation_false_value;
	temp_2 = tformat_text_string(2,string_constant_43,icp_interface);
	return VALUES_3(temp_1,Qicp_connection_not_open,temp_2);
    }
    if (SIMPLE_VECTOR_P(rpc_object_or_handle) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(rpc_object_or_handle)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(rpc_object_or_handle,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(rpc_object_or_handle,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	registered_item_qm = 
		get_item_from_local_handle(rpc_object_or_handle,icp_socket_qm);
	if ( !TRUEP(registered_item_qm)) {
	    temp_1 = Evaluation_false_value;
	    temp_2 = tformat_text_string(3,string_constant_49,
		    rpc_object_or_handle,icp_interface);
	    return VALUES_3(temp_1,Qno_such_item_registered,temp_2);
	}
	rpc_object_or_handle = registered_item_qm;
    }
    deregister_item_with_socket(rpc_object_or_handle,icp_socket_qm);
    temp_1 = Evaluation_true_value;
    temp_2 = copy_constant_wide_string_given_length(array_constant,
	    FIX((SI_Long)0L));
    return VALUES_3(temp_1,Qno_error_in_deregister_on_network,temp_2);
}

static Object string_constant_50;  /* "The system procedure g2-local-home was called, ~
				    *          but the system table attribute local-item-home ~
				    *          was not set properly"
				    */

/* G2-LOCAL-HOME */
Object g2_local_home()
{
    Object name, top_of_stack, message_1;

    x_note_fn_call(168,60);
    name = name_for_local_home();
    if ( !TRUEP(name)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_50);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(name);
}

static Object Qitem_home;          /* item-home */

/* G2-ITEM-HOME */
Object g2_item_home(item)
    Object item;
{
    Object item_1, slot_description_qm;
    Object category_interface_or_virtual_attribute_qm, value, temp;
    Object result;

    x_note_fn_call(168,61);
    item_1 = item;
    result = user_attribute_slot_description_or_virtual_attribute(item_1,
	    Qitem_home,Nil,Qget);
    MVS_2(result,slot_description_qm,
	    category_interface_or_virtual_attribute_qm);
    if (slot_description_qm || category_interface_or_virtual_attribute_qm) {
	value = get_slot_evaluation_value_1(item_1,slot_description_qm,
		category_interface_or_virtual_attribute_qm);
	temp = value;
	if (temp)
	    return VALUES_1(temp);
	else
	    return name_for_local_home();
    }
    else
	return name_for_local_home();
}

static Object Qnames;              /* names */

/* G2-LOOKUP-NETWORK-INTERFACE-FOR-HOME */
Object g2_lookup_network_interface_for_home(item_home)
    Object item_home;
{
    Object attribute, first_interface, interface_1, ab_loop_list_;
    Object gensymed_symbol, sub_class_bit_vector, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, interface_home, item, slot_description_qm;
    Object category_interface_or_virtual_attribute_qm, value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(168,62);
    attribute = interface_home_attribute_function();
    if (attribute);
    else
	attribute = Qnames;
    if (EQ(attribute,Qnames)) {
	first_interface = Nil;
	interface_1 = Nil;
	ab_loop_list_ = lookup_kb_specific_property_value(item_home,
		Frame_or_frames_with_this_name_kbprop);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	interface_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qnetwork_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(interface_1,(SI_Long)1L),
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
	    if (first_interface)
		return VALUES_1(Nil);
	    else
		first_interface = interface_1;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(first_interface);
	return VALUES_1(Qnil);
    }
    else {
	first_interface = Nil;
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	interface_1 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  interface_home = Nil;
	  ab_loopvar_ = collect_subclasses(Qnetwork_interface);
	next_loop_1:
	  first_interface = Nil;
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
	  interface_1 = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  item = interface_1;
	  result = user_attribute_slot_description_or_virtual_attribute(item,
		  attribute,Nil,Qget);
	  MVS_2(result,slot_description_qm,
		  category_interface_or_virtual_attribute_qm);
	  if (slot_description_qm || 
		  category_interface_or_virtual_attribute_qm) {
	      value = get_slot_evaluation_value_1(item,slot_description_qm,
		      category_interface_or_virtual_attribute_qm);
	      interface_home = value;
	  }
	  else
	      interface_home = Nil;
	  if (item_or_value_eql(item_home,interface_home)) {
	      if (first_interface) {
		  result = VALUES_1(Nil);
		  goto end_1;
	      }
	      else
		  first_interface = interface_1;
	  }
	  goto next_loop_1;
	end_loop_2:
	  result = VALUES_1(first_interface);
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
}

/* G2-ITEM-IDENTIFYING-ATTRIBUTES-FOR-NETWORK */
Object g2_item_identifying_attributes_for_network(item,interface_1)
    Object item, interface_1;
{
    x_note_fn_call(168,63);
    return identifying_or_creation_attributes_of_item_for_interface(item,
	    interface_1,T);
}

/* G2-ITEM-CREATION-ATTRIBUTES-FOR-NETWORK */
Object g2_item_creation_attributes_for_network(item,interface_1)
    Object item, interface_1;
{
    x_note_fn_call(168,64);
    return identifying_or_creation_attributes_of_item_for_interface(item,
	    interface_1,Nil);
}

/* G2-LOOKUP-ITEM-FROM-REFERENCE-ATTRIBUTES */
Object g2_lookup_item_from_reference_attributes(identifying_attributes,
	    interface_1)
    Object identifying_attributes, interface_1;
{
    Object current_network_interface;
    Declare_special(1);
    Object result;

    x_note_fn_call(168,65);
    current_network_interface = interface_1;
    PUSH_SPECIAL_WITH_SYMBOL(Current_network_interface,Qcurrent_network_interface,current_network_interface,
	    0);
      result = allocate_evaluation_sequence(lookup_or_create_item_from_reference_attributes(identifying_attributes,
	      Nil,Nil,Nil));
    POP_SPECIAL();
    return result;
}

/* G2-LOOKUP-OR-CREATE-ITEM-FROM-REFERENCE-ATTRIBUTES */
Object g2_lookup_or_create_item_from_reference_attributes(identifying_attributes,
	    creation_attributes,interface_1)
    Object identifying_attributes, creation_attributes, interface_1;
{
    Object current_network_interface;
    Declare_special(1);
    Object result;

    x_note_fn_call(168,66);
    current_network_interface = interface_1;
    PUSH_SPECIAL_WITH_SYMBOL(Current_network_interface,Qcurrent_network_interface,current_network_interface,
	    0);
      result = lookup_or_create_item_from_reference_attributes(identifying_attributes,
	      creation_attributes,Nil,T);
    POP_SPECIAL();
    return result;
}

static Object Qinterface_home_attribute;  /* interface-home-attribute */

/* PUT-INTERFACE-HOME-ATTRIBUTE-WHERE-SLOT-IS-ABSENT */
Object put_interface_home_attribute_where_slot_is_absent(item,new_value)
    Object item, new_value;
{
    x_note_fn_call(168,67);
    enable_references_for_item_passing();
    change_slot_value(3,Miscellaneous_parameters,Qinterface_home_attribute,
	    new_value);
    return VALUES_1(Nil);
}

static Object Qlocal_item_home;    /* local-item-home */

/* PUT-LOCAL-ITEM-HOME-WHERE-SLOT-IS-ABSENT */
Object put_local_item_home_where_slot_is_absent(item,new_value)
    Object item, new_value;
{
    x_note_fn_call(168,68);
    enable_references_for_item_passing();
    change_slot_value(3,Miscellaneous_parameters,Qlocal_item_home,new_value);
    return VALUES_1(Nil);
}

static Object Qitem_reference_parameters;  /* item-reference-parameters */

/* PUT-SHOW-UUIDS-IN-ATTRIBUTE-TABLES-WHERE-SLOT-IS-ABSENT */
Object put_show_uuids_in_attribute_tables_where_slot_is_absent(item_reference_parameters,
	    value)
    Object item_reference_parameters, value;
{
    x_note_fn_call(168,69);
    change_slot_value(3,Miscellaneous_parameters,
	    Qitem_reference_parameters,value);
    return VALUES_1(Nil);
}

static Object Qshow_uuids_in_attribute_tables;  /* show-uuids-in-attribute-tables */

/* FIX-FRAME-WITH-SUBSTITUTE-CLASS-FOR-MISCELLANEOUS-PARAMETERS */
Object fix_frame_with_substitute_class_for_miscellaneous_parameters(miscellaneous_parameters)
    Object miscellaneous_parameters;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, x;
    Object installed_miscellaneous_parameters_qm;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(168,70);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    1);
      scope_conses = Scope_conses;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      x = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(Qmiscellaneous_parameters);
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
	x = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	if (ISVREF(x,(SI_Long)20L)) {
	    installed_miscellaneous_parameters_qm = x;
	    goto end_1;
	}
	goto next_loop;
      end_loop_1:
	installed_miscellaneous_parameters_qm = Qnil;
      end_1:;
      POP_SPECIAL();
      if (installed_miscellaneous_parameters_qm)
	  change_slot_value(3,installed_miscellaneous_parameters_qm,
		  Qshow_uuids_in_attribute_tables,
		  get_slot_value_function(Miscellaneous_parameters,
		  Qshow_uuids_in_attribute_tables,Nil));
      result = delete_frame(Miscellaneous_parameters);
    POP_SPECIAL();
    return result;
}

/* SHOW-UUIDS-IN-ATTRIBUTE-TABLES-FUNCTION */
Object show_uuids_in_attribute_tables_function()
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(168,71);
    if (SIMPLE_VECTOR_P(Miscellaneous_parameters) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Miscellaneous_parameters)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Miscellaneous_parameters,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Miscellaneous_parameters,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? get_slot_value_function(Miscellaneous_parameters,
	    Qshow_uuids_in_attribute_tables,Nil) : Nil;
    return VALUES_1(temp_1);
}

/* INTERFACE-HOME-ATTRIBUTE-FUNCTION */
Object interface_home_attribute_function()
{
    Object temp;

    x_note_fn_call(168,72);
    temp = get_slot_value_function(Miscellaneous_parameters,
	    Qinterface_home_attribute,Nil);
    return VALUES_1(temp);
}

/* LOCAL-ITEM-HOME-FUNCTION */
Object local_item_home_function()
{
    Object temp;

    x_note_fn_call(168,73);
    temp = get_slot_value_function(Miscellaneous_parameters,
	    Qlocal_item_home,Nil);
    return VALUES_1(temp);
}

static Object Qnone;               /* none */

/* COMPILE-INTERFACE-HOME-ATTRIBUTE-FOR-SLOT */
Object compile_interface_home_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(168,74);
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
    if (EQ(parse_result,Qnone))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(parse_result);
}

/* WRITE-INTERFACE-HOME-ATTRIBUTE-FROM-SLOT */
Object write_interface_home_attribute_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(168,75);
    return write_name_denotation(slot_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_name_for_local_home, Qcached_name_for_local_home);

/* PUT-INTERFACE-HOME-ATTRIBUTE */
Object put_interface_home_attribute(frame,value,initializing_qm)
    Object frame, value, initializing_qm;
{
    x_note_fn_call(168,76);
    Cached_name_for_local_home = Nil;
    set_slot_value_function(frame,Qinterface_home_attribute,value,Nil);
    return VALUES_1(value);
}

/* COMPILE-LOCAL-ITEM-HOME-FOR-SLOT */
Object compile_local_item_home_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(168,77);
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
    return VALUES_1(parse_result);
}

static Object string_constant_51;  /* "look up local home from kb g2-to-g2-data-interfaces" */

/* WRITE-LOCAL-ITEM-HOME-FROM-SLOT */
Object write_local_item_home_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(168,78);
    if (CONSP(slot_value) && EQ(CAR(slot_value),Qstar))
	return tformat(1,string_constant_51);
    else
	return write_evaluation_value(1,slot_value);
}

/* PUT-LOCAL-ITEM-HOME */
Object put_local_item_home(frame,value,initializing_qm)
    Object frame, value, initializing_qm;
{
    x_note_fn_call(168,79);
    Cached_name_for_local_home = Nil;
    set_slot_value_function(frame,Qlocal_item_home,value,Nil);
    return VALUES_1(value);
}

Object Compute_name_for_local_home_p = UNBOUND;

static Object Qicp_connection_specification;  /* icp-connection-specification */

static Object Qlocalnet;           /* localnet */

static Object array_constant_1;    /* # */

static Object Qtcp_ip;             /* tcp-ip */

static Object string_constant_52;  /* "~A" */

static Object Qab_gensym;          /* gensym */

/* NAME-FOR-LOCAL-HOME */
Object name_for_local_home()
{
    Object local_home, evaluation_value, local_host_name, listener_info_list;
    Object local_interface_list, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object int_1, interface_configuration_qm, temp_1, interface_protocol;
    Object interface_address, protocol, address, ab_loop_list_, ab_loop_it_;
    Object ab_loop_desetq_, str, gensym_pop_store, cons_1, next_cons, temp_2;
    Object svref_arg_2, interface_1, attribute, value;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(168,80);
    if (Compute_name_for_local_home_p) {
	if (Cached_name_for_local_home) {
	    if (FIXNUMP(Cached_name_for_local_home) || 
		    Cached_name_for_local_home && 
		    SYMBOLP(Cached_name_for_local_home))
		return VALUES_1(Cached_name_for_local_home);
	    else
		return copy_evaluation_value_1(Cached_name_for_local_home);
	}
	else {
	    local_home = local_item_home_function();
	    if (local_home &&  !(CONSP(local_home) && EQ(CAR(local_home),
		    Qstar))) {
		Cached_name_for_local_home = local_home;
		evaluation_value = Cached_name_for_local_home;
		if (FIXNUMP(evaluation_value) || evaluation_value && 
			SYMBOLP(evaluation_value))
		    return VALUES_1(evaluation_value);
		else
		    return copy_evaluation_value_1(evaluation_value);
	    }
	    else {
		local_host_name = get_local_host_name();
		PUSH_SPECIAL_WITH_SYMBOL(Local_host_name,Qlocal_host_name,local_host_name,
			1);
		  listener_info_list = get_local_host_addresses();
		  local_interface_list = Nil;
		  scope_conses = Scope_conses;
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  int_1 = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			  0);
		    interface_configuration_qm = Nil;
		    ab_loopvar_ = collect_subclasses(Qg2_to_g2_data_interface);
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
		    int_1 = ab_loopvar__1;
		    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		    temp_1 = get_slot_value_if_any_function(int_1,
			    Qicp_connection_specification,Nil);
		    interface_configuration_qm = CAR(temp_1);
		    if (interface_configuration_qm &&  
			    !EQ(FIRST(interface_configuration_qm),
			    Qlocalnet) && (equalw(array_constant_1,
			    SECOND(interface_configuration_qm)) || 
			    equalw(Local_host_name,
			    SECOND(interface_configuration_qm)))) {
			interface_protocol = FIRST(interface_configuration_qm);
			interface_address = THIRD(interface_configuration_qm);
			protocol = Nil;
			address = Nil;
			ab_loop_list_ = listener_info_list;
			ab_loop_it_ = Nil;
			ab_loop_desetq_ = Nil;
		      next_loop_2:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_2;
			ab_loop_desetq_ = M_CAR(ab_loop_list_);
			protocol = CAR(ab_loop_desetq_);
			temp_1 = CDR(ab_loop_desetq_);
			address = CAR(temp_1);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if (EQ(interface_protocol,Qtcp_ip) ? (SI_Long)84L 
				== UBYTE_16_ISAREF_1(protocol,(SI_Long)0L) 
				: TRUEP(Nil)) {
			    str = tformat_text_string(2,string_constant_52,
				    interface_address);
			    temp_1 = string_equalw(str,address);
			    reclaim_text_string(str);
			    ab_loop_it_ = temp_1;
			}
			else
			    ab_loop_it_ = Nil;
			if (ab_loop_it_) {
			    temp = TRUEP(ab_loop_it_);
			    goto end_1;
			}
			goto next_loop_2;
		      end_loop_2:
			temp = TRUEP(Qnil);
		      end_1:;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			local_interface_list = gensym_cons_1(int_1,
				local_interface_list);
		    goto next_loop;
		  end_loop_1:
		    reclaim_network_addresses(listener_info_list);
		    if ( !TRUEP(local_interface_list) || 
			    CDR(local_interface_list)) {
			reclaim_gensym_list_1(local_interface_list);
			result = VALUES_1(Nil);
		    }
		    else {
			gensym_pop_store = Nil;
			cons_1 = local_interface_list;
			if (cons_1) {
			    gensym_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qab_gensym);
			    if (ISVREF(Available_gensym_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_2 = 
					ISVREF(Available_gensym_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_2) = cons_1;
				temp_2 = Available_gensym_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_2,svref_arg_2) = cons_1;
			    }
			    else {
				temp_2 = Available_gensym_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_2,svref_arg_2) = cons_1;
				temp_2 = Available_gensym_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_2,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			local_interface_list = next_cons;
			interface_1 = gensym_pop_store;
			attribute = interface_home_attribute_function();
			if (attribute);
			else
			    attribute = Qnames;
			value = 
				frame_or_evaluation_value_user_attribute_value(interface_1,
				attribute,Nil);
			if (value) {
			    Cached_name_for_local_home = value;
			    evaluation_value = Cached_name_for_local_home;
			    if (FIXNUMP(evaluation_value) || 
				    evaluation_value && 
				    SYMBOLP(evaluation_value))
				result = VALUES_1(evaluation_value);
			    else
				result = copy_evaluation_value_1(evaluation_value);
			}
			else
			    result = VALUES_1(Nil);
		    }
		    goto end_2;
		    result = VALUES_1(Qnil);
		  end_2:;
		  POP_SPECIAL();
		POP_SPECIAL();
		return result;
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

void g2_rpc3_INIT()
{
    Object gensymed_symbol, temp, temp_1;
    Object AB_package, list_constant_6, Qslot_putter, Qput_local_item_home;
    Object Qslot_value_writer, Qwrite_local_item_home_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_local_item_home_for_slot;
    Object Qput_interface_home_attribute;
    Object Qwrite_interface_home_attribute_from_slot;
    Object Qcompile_interface_home_attribute_for_slot, string_constant_68;
    Object Qhome, Qclasses_which_define, Qfix_frame_with_substitute_class;
    Object Qfix_frame_with_substitute_class_for_miscellaneous_parameters;
    Object Qabsent_slot_putter;
    Object Qput_show_uuids_in_attribute_tables_where_slot_is_absent;
    Object Qsubstitute_class_and_kb_flags;
    Object Qput_local_item_home_where_slot_is_absent;
    Object Qput_interface_home_attribute_where_slot_is_absent;
    Object Qg2_lookup_or_create_item_from_reference_attributes;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_lookup_item_from_reference_attributes;
    Object Qg2_item_creation_attributes_for_network;
    Object Qg2_item_identifying_attributes_for_network;
    Object Qg2_lookup_network_interface_for_home, Qg2_item_home;
    Object Qg2_local_home, Qderegister_on_network_lisp_side;
    Object Qget_network_handle_from_item_lisp_side;
    Object Qget_item_from_network_handle_lisp_side;
    Object Qregister_on_network_lisp_side, Qenable_references_for_item_passing;
    Object Qimplemented_object_passing_system_attribute;
    Object Qimplemented_object_passing_system_attributes, string_constant_67;
    Object string_constant_66, string_constant_65, string_constant_64;
    Object string_constant_63, string_constant_62, string_constant_61;
    Object string_constant_60, string_constant_59, string_constant_58;
    Object string_constant_57, string_constant_56, string_constant_55;
    Object string_constant_54, string_constant_53, Qcdr_of_second_in_place;
    Object Qmerge_object_passing_property_lists, Qinterval, Qseconds;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(168,81);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qvariable_or_parameter_stored_histories_qm = 
	    STATIC_SYMBOL("VARIABLE-OR-PARAMETER-STORED-HISTORIES\?",
	    AB_package);
    Qhistory_object_sent_to_non_history_attribute = 
	    STATIC_SYMBOL("HISTORY-OBJECT-SENT-TO-NON-HISTORY-ATTRIBUTE",
	    AB_package);
    Qhistory_object_sent_to_non_history_class_definition = 
	    STATIC_SYMBOL("HISTORY-OBJECT-SENT-TO-NON-HISTORY-CLASS-DEFINITION",
	    AB_package);
    Qvariable_or_parameter_history_specification_qm = 
	    STATIC_SYMBOL("VARIABLE-OR-PARAMETER-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qhistory = STATIC_SYMBOL("HISTORY",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qiterate_over_history = STATIC_SYMBOL("ITERATE-OVER-HISTORY",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    QFLOAT = STATIC_SYMBOL("float",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtruth = STATIC_SYMBOL("TRUTH",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Kabort_transmitting_resumable_object = 
	    STATIC_SYMBOL("ABORT-TRANSMITTING-RESUMABLE-OBJECT",Pkeyword);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = 
	    STATIC_STRING("A history-keeping variable-or-parameter ");
    string_constant_1 = STATIC_STRING("at top level in the argument list ");
    string_constant_2 = STATIC_STRING(", being sent as a subobject of ~NF, ");
    string_constant_3 = 
	    STATIC_STRING("has had its history-keeping spec ~\n                      changed to \"none\"");
    Qg2_history_array_deleted = STATIC_SYMBOL("G2-HISTORY-ARRAY-DELETED",
	    AB_package);
    string_constant_4 = 
	    STATIC_STRING("has overwritten an old value ~\n                        before it could be transmitted");
    Qg2_history_array_index_lost = 
	    STATIC_SYMBOL("G2-HISTORY-ARRAY-INDEX-LOST",AB_package);
    string_constant_5 = 
	    STATIC_STRING("has overwritten some old values ~\n                        before they could be transmitted");
    Qg2_history_array_entries_lost = 
	    STATIC_SYMBOL("G2-HISTORY-ARRAY-ENTRIES-LOST",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qunexpected_non_value_list = STATIC_SYMBOL("UNEXPECTED-NON-VALUE-LIST",
	    AB_package);
    Qpremature_access_to_toplevel_g2_value_list = 
	    STATIC_SYMBOL("PREMATURE-ACCESS-TO-TOPLEVEL-G2-VALUE-LIST",
	    AB_package);
    Qg2_value_list_deleted_during_object_passing = 
	    STATIC_SYMBOL("G2-VALUE-LIST-DELETED-DURING-OBJECT-PASSING",
	    AB_package);
    Qvalue_list_contains_an_element_inappropriate_for_receiving_array = 
	    STATIC_SYMBOL("VALUE-LIST-CONTAINS-AN-ELEMENT-INAPPROPRIATE-FOR-RECEIVING-ARRAY",
	    AB_package);
    string_constant_6 = STATIC_STRING("A g2-value-list ");
    string_constant_7 = STATIC_STRING("has been deleted");
    Qg2_value_list_subobject_deleted = 
	    STATIC_SYMBOL("G2-VALUE-LIST-SUBOBJECT-DELETED",AB_package);
    string_constant_8 = STATIC_STRING("An element of the g2-value-list ~NF ");
    string_constant_9 = STATIC_STRING("has been removed");
    Qg2_value_list_element_removed = 
	    STATIC_SYMBOL("G2-VALUE-LIST-ELEMENT-REMOVED",AB_package);
    if (Minimnal_bandwidth_for_resumable_sequence_range == UNBOUND)
	Minimnal_bandwidth_for_resumable_sequence_range = FIX((SI_Long)100L);
    Qvector_element = STATIC_SYMBOL("VECTOR-ELEMENT",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qimport_declarations = STATIC_SYMBOL("IMPORT-DECLARATIONS",AB_package);
    Qpackage_declaration = STATIC_SYMBOL("PACKAGE-DECLARATION",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qcurrent_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    list_constant = STATIC_LIST((SI_Long)5L,Qimport_declarations,
	    Qpackage_declaration,Qtext,Qname,Qcurrent_value);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qobject_passing_info_qm = STATIC_SYMBOL("OBJECT-PASSING-INFO\?",
	    AB_package);
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    Qole = STATIC_SYMBOL("OLE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qstart,Qcall,Qreturn,Qole);
    Qoutstanding = STATIC_SYMBOL("OUTSTANDING",AB_package);
    Qreturned = STATIC_SYMBOL("RETURNED",AB_package);
    Qole_object_passing_in_progress = 
	    STATIC_SYMBOL("OLE-OBJECT-PASSING-IN-PROGRESS",AB_package);
    string_constant_10 = 
	    STATIC_STRING("A remote procedure call to ~A has been aborted ");
    string_constant_11 = 
	    STATIC_STRING("A remote procedure call has been aborted ");
    string_constant_12 = 
	    STATIC_STRING("while receiving a subobject of class ~A ");
    string_constant_13 = STATIC_STRING("index ~A");
    string_constant_14 = STATIC_STRING("attribute ~A");
    string_constant_15 = STATIC_STRING("at ~A: ");
    string_constant_16 = STATIC_STRING("~A.  ");
    Qtformat = STATIC_SYMBOL("TFORMAT",AB_package);
    Qproblem_building_rpc_object_arguments = 
	    STATIC_SYMBOL("PROBLEM-BUILDING-RPC-OBJECT-ARGUMENTS",AB_package);
    Qrpc_error = STATIC_SYMBOL("RPC-ERROR",AB_package);
    Qproblem_registering_rpc_object_on_network = 
	    STATIC_SYMBOL("PROBLEM-REGISTERING-RPC-OBJECT-ON-NETWORK",
	    AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtry_to_transmit_resumable_object = 
	    STATIC_SYMBOL("TRY-TO-TRANSMIT-RESUMABLE-OBJECT",AB_package);
    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct 
	    = STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct 
	    = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-STRUCTURE-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_object_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-VECTOR-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-VECTOR-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_history_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-HISTORY-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-LIST-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-LIST-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Ksuspend_transmitting_resumable_object = 
	    STATIC_SYMBOL("SUSPEND-TRANSMITTING-RESUMABLE-OBJECT",Pkeyword);
    string_constant_17 = STATIC_STRING("A g2-value-array ");
    Qg2_value_array_deleted = STATIC_SYMBOL("G2-VALUE-ARRAY-DELETED",
	    AB_package);
    string_constant_18 = STATIC_STRING("A g2-value-array ~NF");
    string_constant_19 = STATIC_STRING(" at top level in the argument list ");
    string_constant_20 = STATIC_STRING("has had its length changed");
    Qg2_value_array_length_diminished = 
	    STATIC_SYMBOL("G2-VALUE-ARRAY-LENGTH-DIMINISHED",AB_package);
    Qg2_defstruct_structure_name_resumable_value_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_resumable_circular_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-CIRCULAR-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Kfinished_transmitting_resumable_object = 
	    STATIC_SYMBOL("FINISHED-TRANSMITTING-RESUMABLE-OBJECT",Pkeyword);
    Qrpc_object_argument_deleted = 
	    STATIC_SYMBOL("RPC-OBJECT-ARGUMENT-DELETED",AB_package);
    string_constant_21 = 
	    STATIC_STRING("An object being sent as an RPC argument has been deleted");
    string_constant_22 = 
	    STATIC_STRING("The remote procedure call ~A ~\n                   has been aborted while transmitting: ~A");
    string_constant_23 = 
	    STATIC_STRING("A remote procedure call ~\n                   has been aborted while transmitting: ~A");
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    SET_SYMBOL_FUNCTION(Qtry_to_transmit_resumable_object,
	    STATIC_FUNCTION(try_to_transmit_resumable_object,NIL,FALSE,1,1));
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Kgeneral_description = STATIC_SYMBOL("GENERAL-DESCRIPTION",Pkeyword);
    Kinclude_attributes = STATIC_SYMBOL("INCLUDE-ATTRIBUTES",Pkeyword);
    Kexclude_attributes = STATIC_SYMBOL("EXCLUDE-ATTRIBUTES",Pkeyword);
    Kinclude_system_attributes = STATIC_SYMBOL("INCLUDE-SYSTEM-ATTRIBUTES",
	    Pkeyword);
    Kinclude_all_system_attributes = 
	    STATIC_SYMBOL("INCLUDE-ALL-SYSTEM-ATTRIBUTES",Pkeyword);
    Kinclude_all_system_attributes_except = 
	    STATIC_SYMBOL("INCLUDE-ALL-SYSTEM-ATTRIBUTES-EXCEPT",Pkeyword);
    Kkind = STATIC_SYMBOL("KIND",Pkeyword);
    Kall_remaining = STATIC_SYMBOL("ALL-REMAINING",Pkeyword);
    Qby_copy_with_handle = STATIC_SYMBOL("BY-COPY-WITH-HANDLE",AB_package);
    Qreference = STATIC_SYMBOL("REFERENCE",AB_package);
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    string_constant_24 = 
	    STATIC_STRING("The RPC argument or result ~NC was sent as a handle but is ~\n                    not the network handle for any object in this interface");
    Qreturn_remote_procedure_result_as_handle = 
	    STATIC_SYMBOL("RETURN-REMOTE-PROCEDURE-RESULT-AS-HANDLE",
	    AB_package);
    string_constant_25 = 
	    STATIC_STRING("The RPC argument or result ~NC was sent as a handle ~\n             but the remote process is not equipped for item-passing");
    Qreturn_remote_procedure_result_as_object_from_handle = 
	    STATIC_SYMBOL("RETURN-REMOTE-PROCEDURE-RESULT-AS-OBJECT-FROM-HANDLE",
	    AB_package);
    string_constant_26 = 
	    STATIC_STRING("The RPC argument or result ~NF was sent by copy, but is not an object ~\n                 and the remote process is not equipped to receive non-object items");
    string_constant_27 = 
	    STATIC_STRING("The RPC argument or result ~NF was sent by copy with a handle ~\n                      but the remote process is not equipped to receive by copy with a handle");
    Qreturn_remote_procedure_result = 
	    STATIC_SYMBOL("RETURN-REMOTE-PROCEDURE-RESULT",AB_package);
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    list_constant_2 = STATIC_CONS(Qhistory,list_constant);
    string_constant_28 = 
	    STATIC_STRING("The RPC argument or result ~NF is an item ~\n             but the remote process is not equipped for item-passing");
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_code_body_invocation_g2_struct = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_procedure_invocation_g2_struct = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_sending_resumable_object_g2_struct = 
	    STATIC_SYMBOL("SENDING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_29 = 
	    STATIC_STRING("The returned value was not of the type ~NT, ~\n                               as required by the declaration for ~NF.");
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qseconds,Qinterval);
    string_constant_30 = 
	    STATIC_STRING("The returned value ~A was not of the type ~NT, ~\n                                 as required by the declaration for ~NF.");
    string_constant_31 = 
	    STATIC_STRING("~A values were returned, but the remote procedure declaration ~\n                ~a declares that ~a values would be returned.");
    string_constant_32 = 
	    STATIC_STRING("Procedure ~a is requesting more values than ~a can return.");
    Qmerge_object_passing_property_lists = 
	    STATIC_SYMBOL("MERGE-OBJECT-PASSING-PROPERTY-LISTS",AB_package);
    SET_SYMBOL_FUNCTION(Qmerge_object_passing_property_lists,
	    STATIC_FUNCTION(merge_object_passing_property_lists,NIL,FALSE,
	    1,1));
    Qcdr_of_second_in_place = STATIC_SYMBOL("CDR-OF-SECOND-IN-PLACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcdr_of_second_in_place,
	    STATIC_FUNCTION(cdr_of_second_in_place,NIL,FALSE,1,1));
    string_constant_53 = 
	    STATIC_STRING("13ey1n83-Boy1n1m9k83-9y83-m6y1m9k83-Ay1lm1n83-Boy1n1m9k83-9y83-JTy1m9k83-Ay1lm1o83-JTy1n1m9k830*y1m9k83-Bby83-m6y1mn1m83-JSy8k9l");
    string_constant_54 = 
	    STATIC_STRING("1n83-m6y1n1m9k83-Gy83-Gy83-hNy2m83*gy1m83-Gymn1n83-m6y1m1m9k8377y83-hNy2m83*gy83=Kym1n83-m6y1m1m9k83*ly83-hNy2m83*gy83=oym1n83-m");
    string_constant_55 = 
	    STATIC_STRING("6y1m1m9k8s83-hNy2m83*gy1l8sm1n83-m6y1m1m9k830Sy83-hNy2m83*gy1l830Sym1n83mHy1m1m9k83-Gy83-Gy1m83*gy1m83-Gym1n83mHy1n1m9k83-Gy83-G");
    string_constant_56 = 
	    STATIC_STRING("y83-8jy2m83*gy1m83-Gymn1n83mHy1n1m9k83-Gy83-Gy83-iUy2m83*gy1m83-Gymn1n83mHy1o1m9k83-9y1m9k83-Gy83-Gy1m9k83-Ay1m83*gy1m83-Gyn1n83");
    string_constant_57 = 
	    STATIC_STRING("mHy1n1m9k83-9y1m9k8377y1m9k83-Ay1m83*gy83=Ky1n83mHy1n1m9k83-9y1m9k83*ly1m9k83-Ay1m83*gy83=oy1n83mHy1n1m9k83-9y1m9k8s1m9k83-Ay1m8");
    string_constant_58 = 
	    STATIC_STRING("3*gy1l8s1n83mHy1n1m9k83-9y1m9k830Sy1m9k83-Ay1m83*gy1l830Sy1n83mHy1p1m9k83-9y1m9k83-Gy83-Gy83-hNy1m9k83-Ay2m83*gy1m83-Gyno1n83mHy");
    string_constant_59 = 
	    STATIC_STRING("1o1m9k83-9y1m9k8377y83-hNy1m9k83-Ay2m83*gy83=Kyn1n83mHy1o1m9k83-9y1m9k83*ly83-hNy1m9k83-Ay2m83*gy83=oyn1n83mHy1o1m9k83-9y1m9k8s8");
    string_constant_60 = 
	    STATIC_STRING("3-hNy1m9k83-Ay2m83*gy1l8sn1n83mHy1o1m9k83-9y1m9k830Sy83-hNy1m9k83-Ay2m83*gy1l830Syn1m83-hNy83-hMy1m83-hNy83-hOy1o83-hNy1m83-iUy8");
    string_constant_61 = 
	    STATIC_STRING("3-hOy1mlm9l1o83-hNy1m83-hOy83-iUy1mlm9l1m83-hMy83-8jy1m83-hMy83-iUy1n83-8jy1m1m9k83*5y1m9k83-Xdy1m83-1fy83-Xdy1n83-iUy1m1m9k83=F");
    string_constant_62 = 
	    STATIC_STRING("y1m9k83-Xdy1m83-1fy83-L8y1o83-hOy1n83-ZVy1m9k83-ty83-ZUy1mln9l1m83-hOy83-ZVy1m83-ZVy83-ZPy1m83-ZVy83-TBy1o83-ZPy1r1m9k83-=Ky1m9k");
    string_constant_63 = 
	    STATIC_STRING("839Zy1m9k9m1m9k83oIy1m9k83Gry1m9k83-Py83oJy1m83-ZOyr9n1n83-ZPy1q1m9k83-=Ky1m9k839Zy1m9k9m1m9k83oIy1m9k83-qy83dey1m83-ZOy1lq1o83-");
    string_constant_64 = 
	    STATIC_STRING("TBy1q1m9k83-TDy1m9k9m1m9k83oIy1m9k83Gry1m9k83-Py83oJy1m83-TAyq9n1n83-TBy1p1m9k83-TDy1m9k9m1m9k83oIy1m9k83-qy83dey1m83-TAy1lp1m83");
    string_constant_65 = 
	    STATIC_STRING("-hOy83-ZUy1n83-ZUy1o1m9k83-=Ky1m9k830*y1m9k8l1m9k83Gry1m83-ZMy8k1o83-ZUy1r1m9k83-=Ky1m9k830*y1m9k8l1m9k83Gry1m9k83vny1m9k83-Py83");
    string_constant_66 = 
	    STATIC_STRING("-ZFy1o83-ZNyr83-ZMy8k9n1o83-ZUy1q1m9k83-=Ky1m9k9m1m9k8l1m9k83Gry1m9k83-Py83-ZFy1m83-ZTyq9n1n83-ZUy1p1m9k83-=Ky1m9k9m1m9k8l1m9k83");
    string_constant_67 = 
	    STATIC_STRING("-qy83iuy1m83-ZTy1lp1n83iuy1n1m9k836xy1m9k83-Ty1m9k830Cy836xy1m83iuy83FJy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmerge_object_passing_property_lists);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qcdr_of_second_in_place);
    add_grammar_rules_function(regenerate_optimized_constant(list(15,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64,
	    string_constant_65,string_constant_66,string_constant_67)));
    Qimplemented_object_passing_system_attributes = 
	    STATIC_SYMBOL("IMPLEMENTED-OBJECT-PASSING-SYSTEM-ATTRIBUTES",
	    AB_package);
    Qimplemented_object_passing_system_attribute = 
	    STATIC_SYMBOL("IMPLEMENTED-OBJECT-PASSING-SYSTEM-ATTRIBUTE",
	    AB_package);
    add_grammar_rules_for_list(2,
	    Qimplemented_object_passing_system_attributes,
	    Qimplemented_object_passing_system_attribute);
    Qenable_references_for_item_passing = 
	    STATIC_SYMBOL("ENABLE-REFERENCES-FOR-ITEM-PASSING",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qenable_references_for_item_passing,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_33 = 
	    STATIC_STRING("1y1n83-8jy1m1m9k83*5y1m9k83-lJy1m83-1fy83-lJy1m83-7Ky83-gRy1n83-gRy1t1m9k83-9y1m9k83jRy1m9k83-Ty1m9k83-Gy83jNy1m9k83-*0y1m9k83Gr");
    string_constant_34 = 
	    STATIC_STRING("y83-cpy1m9k83-Ay1n83-Gyps1n83-gRy1x1m9k83-9y1m9k83jRy1m9k83-Ty1m9k83-Gy83jNy1m9k83-*0y1m9k830*y1m9k83Gry1m9k83*Xy1m9k9l1m9k83-qy");
    string_constant_35 = 
	    STATIC_STRING("836Iy1m9k83-Ay1n83-Gyp1m9mw1m83-cpy83-MTy1o83-cpy1n83-MTy1m9k83vy83-cpy1nmln9n1m83-MTy836Iy1n83-MTy1p83dey1m9k83-*1y1m9k83-7Hy1m");
    string_constant_36 = 
	    STATIC_STRING("9k83=hy83dey1mlo1n833*y1p1m9k9l1m9k83-7Hy1m9k83D0y1m9k83=Iy833*y1m83-gSyp1n830By1p1m9k9l1m9k83-7Hy1m9k83D0y1m9k83=Iy830By1m83-gS");
    string_constant_37 = 
	    STATIC_STRING("yp1n83F2y1p1m9k9l1m9k83-7Hy1m9k83D0y1m9k83=Iy83F2y1m83-gSyp1n83lIy1n1m9k83DAy1m9k83-Py839ay1n83DAyn1m1l8328y01n83lIy1n1m9k83E=y1");
    string_constant_38 = 
	    STATIC_STRING("m9k83-Py83-ky1n83E=yn1m1l8328y01n83lIy1n1m9k83BCy1m9k83-Py83-2y1n83BCyn1m1l8328y0");
    Qnetwork_interface = STATIC_SYMBOL("NETWORK-INTERFACE",AB_package);
    Qcreation_attributes = STATIC_SYMBOL("CREATION-ATTRIBUTES",AB_package);
    Qitem_reference_options = STATIC_SYMBOL("ITEM-REFERENCE-OPTIONS",
	    AB_package);
    Qnames_of_remote_interface = STATIC_SYMBOL("NAMES-OF-REMOTE-INTERFACE",
	    AB_package);
    Qclass_of_remote_interface = STATIC_SYMBOL("CLASS-OF-REMOTE-INTERFACE",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)4L,Qcreation_attributes,
	    Qitem_reference_options,Qnames_of_remote_interface,
	    Qclass_of_remote_interface);
    Qdo_not_put_in_attribute_tables = 
	    STATIC_SYMBOL("DO-NOT-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    Qmiscellaneous_parameters = STATIC_SYMBOL("MISCELLANEOUS-PARAMETERS",
	    AB_package);
    Qinterface_home_attribute = STATIC_SYMBOL("INTERFACE-HOME-ATTRIBUTE",
	    AB_package);
    Qlocal_item_home = STATIC_SYMBOL("LOCAL-ITEM-HOME",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qinterface_home_attribute,
	    Qlocal_item_home);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    SET_SYMBOL_FUNCTION(Qenable_references_for_item_passing,
	    STATIC_FUNCTION(enable_references_for_item_passing,NIL,FALSE,0,0));
    Qregister_on_network_lisp_side = 
	    STATIC_SYMBOL("REGISTER-ON-NETWORK-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qregister_on_network_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_39 = 
	    STATIC_STRING("~A is not an item, and so cannot be registered on the network");
    Qcannot_register_non_item = STATIC_SYMBOL("CANNOT-REGISTER-NON-ITEM",
	    AB_package);
    string_constant_40 = 
	    STATIC_STRING("~A is not an item, and so cannot be an ICP interface");
    Qicp_interface_not_item = STATIC_SYMBOL("ICP-INTERFACE-NOT-ITEM",
	    AB_package);
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    Qg2_to_g2_data_interface = STATIC_SYMBOL("G2-TO-G2-DATA-INTERFACE",
	    AB_package);
    string_constant_41 = 
	    STATIC_STRING("The object ~NF is neither a GSI nor a G2-to-G2 interface");
    Qno_icp_interface_capability = 
	    STATIC_SYMBOL("NO-ICP-INTERFACE-CAPABILITY",AB_package);
    string_constant_42 = STATIC_STRING("There is no ICP connection for ~NF");
    Qno_icp_connection = STATIC_SYMBOL("NO-ICP-CONNECTION",AB_package);
    string_constant_43 = 
	    STATIC_STRING("The ICP connection for ~NF is not open");
    Qicp_connection_not_open = STATIC_SYMBOL("ICP-CONNECTION-NOT-OPEN",
	    AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qno_error_in_register_on_network = 
	    STATIC_SYMBOL("NO-ERROR-IN-REGISTER-ON-NETWORK",AB_package);
    SET_SYMBOL_FUNCTION(Qregister_on_network_lisp_side,
	    STATIC_FUNCTION(register_on_network_lisp_side,NIL,FALSE,2,2));
    Qget_item_from_network_handle_lisp_side = 
	    STATIC_SYMBOL("GET-ITEM-FROM-NETWORK-HANDLE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_item_from_network_handle_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_44 = STATIC_STRING("The handle ~A must be 0 or greater");
    Qno_such_network_item = STATIC_SYMBOL("NO-SUCH-NETWORK-ITEM",AB_package);
    Qout_of_range_handle = STATIC_SYMBOL("OUT-OF-RANGE-HANDLE",AB_package);
    string_constant_45 = 
	    STATIC_STRING("There is no item registered for handle ~S under interface ~NF");
    Qno_such_item_registered = STATIC_SYMBOL("NO-SUCH-ITEM-REGISTERED",
	    AB_package);
    Qno_error_in_get_item_from_network_handle = 
	    STATIC_SYMBOL("NO-ERROR-IN-GET-ITEM-FROM-NETWORK-HANDLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_from_network_handle_lisp_side,
	    STATIC_FUNCTION(get_item_from_network_handle_lisp_side,NIL,
	    FALSE,2,2));
    Qget_network_handle_from_item_lisp_side = 
	    STATIC_SYMBOL("GET-NETWORK-HANDLE-FROM-ITEM-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_network_handle_from_item_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_46 = 
	    STATIC_STRING("~A is not an item, and so cannot have a network handle");
    string_constant_47 = 
	    STATIC_STRING("No handle for variable ~NF under ICP interface ~NF");
    Qno_such_handle = STATIC_SYMBOL("NO-SUCH-HANDLE",AB_package);
    Qno_error_in_get_network_handle_from_item = 
	    STATIC_SYMBOL("NO-ERROR-IN-GET-NETWORK-HANDLE-FROM-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_network_handle_from_item_lisp_side,
	    STATIC_FUNCTION(get_network_handle_from_item_lisp_side,NIL,
	    FALSE,2,2));
    Qderegister_on_network_lisp_side = 
	    STATIC_SYMBOL("DEREGISTER-ON-NETWORK-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qderegister_on_network_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_48 = 
	    STATIC_STRING("~A is neither an item nor an integer, and so cannot be deregistered");
    Qcannot_deregister_non_item = 
	    STATIC_SYMBOL("CANNOT-DEREGISTER-NON-ITEM",AB_package);
    string_constant_49 = 
	    STATIC_STRING("There is no item registered for handle ~S ~\n                  under interface ~NF");
    Qno_error_in_deregister_on_network = 
	    STATIC_SYMBOL("NO-ERROR-IN-DEREGISTER-ON-NETWORK",AB_package);
    SET_SYMBOL_FUNCTION(Qderegister_on_network_lisp_side,
	    STATIC_FUNCTION(deregister_on_network_lisp_side,NIL,FALSE,2,2));
    Qg2_local_home = STATIC_SYMBOL("G2-LOCAL-HOME",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_local_home,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_50 = 
	    STATIC_STRING("The system procedure g2-local-home was called, ~\n         but the system table attribute local-item-home ~\n         was not set properly");
    SET_SYMBOL_FUNCTION(Qg2_local_home,STATIC_FUNCTION(g2_local_home,NIL,
	    FALSE,0,0));
    Qg2_item_home = STATIC_SYMBOL("G2-ITEM-HOME",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_item_home,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qitem_home = STATIC_SYMBOL("ITEM-HOME",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_item_home,STATIC_FUNCTION(g2_item_home,NIL,
	    FALSE,1,1));
    Qg2_lookup_network_interface_for_home = 
	    STATIC_SYMBOL("G2-LOOKUP-NETWORK-INTERFACE-FOR-HOME",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_lookup_network_interface_for_home,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qnames = STATIC_SYMBOL("NAMES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_lookup_network_interface_for_home,
	    STATIC_FUNCTION(g2_lookup_network_interface_for_home,NIL,FALSE,
	    1,1));
    Qg2_item_identifying_attributes_for_network = 
	    STATIC_SYMBOL("G2-ITEM-IDENTIFYING-ATTRIBUTES-FOR-NETWORK",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_item_identifying_attributes_for_network,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_item_identifying_attributes_for_network,
	    STATIC_FUNCTION(g2_item_identifying_attributes_for_network,NIL,
	    FALSE,2,2));
    Qg2_item_creation_attributes_for_network = 
	    STATIC_SYMBOL("G2-ITEM-CREATION-ATTRIBUTES-FOR-NETWORK",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_item_creation_attributes_for_network,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_item_creation_attributes_for_network,
	    STATIC_FUNCTION(g2_item_creation_attributes_for_network,NIL,
	    FALSE,2,2));
    Qg2_lookup_item_from_reference_attributes = 
	    STATIC_SYMBOL("G2-LOOKUP-ITEM-FROM-REFERENCE-ATTRIBUTES",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lookup_item_from_reference_attributes,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lookup_item_from_reference_attributes,
	    STATIC_FUNCTION(g2_lookup_item_from_reference_attributes,NIL,
	    FALSE,2,2));
    Qg2_lookup_or_create_item_from_reference_attributes = 
	    STATIC_SYMBOL("G2-LOOKUP-OR-CREATE-ITEM-FROM-REFERENCE-ATTRIBUTES",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lookup_or_create_item_from_reference_attributes,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lookup_or_create_item_from_reference_attributes,
	    STATIC_FUNCTION(g2_lookup_or_create_item_from_reference_attributes,
	    NIL,FALSE,3,3));
    Qput_interface_home_attribute_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-INTERFACE-HOME-ATTRIBUTE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_interface_home_attribute_where_slot_is_absent,
	    STATIC_FUNCTION(put_interface_home_attribute_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qinterface_home_attribute,
	    SYMBOL_FUNCTION(Qput_interface_home_attribute_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qput_local_item_home_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-LOCAL-ITEM-HOME-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_local_item_home_where_slot_is_absent,
	    STATIC_FUNCTION(put_local_item_home_where_slot_is_absent,NIL,
	    FALSE,2,2));
    mutate_global_property(Qlocal_item_home,
	    SYMBOL_FUNCTION(Qput_local_item_home_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qitem_reference_parameters = STATIC_SYMBOL("ITEM-REFERENCE-PARAMETERS",
	    AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    mutate_global_property(Qitem_reference_parameters,
	    CONS(Qmiscellaneous_parameters,
	    Last_kb_flags_saved_with_item_reference_parameters),
	    Qsubstitute_class_and_kb_flags);
    Qshow_uuids_in_attribute_tables = 
	    STATIC_SYMBOL("SHOW-UUIDS-IN-ATTRIBUTE-TABLES",AB_package);
    Qput_show_uuids_in_attribute_tables_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SHOW-UUIDS-IN-ATTRIBUTE-TABLES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_show_uuids_in_attribute_tables_where_slot_is_absent,
	    STATIC_FUNCTION(put_show_uuids_in_attribute_tables_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qshow_uuids_in_attribute_tables,
	    SYMBOL_FUNCTION(Qput_show_uuids_in_attribute_tables_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qfix_frame_with_substitute_class_for_miscellaneous_parameters = 
	    STATIC_SYMBOL("FIX-FRAME-WITH-SUBSTITUTE-CLASS-FOR-MISCELLANEOUS-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfix_frame_with_substitute_class_for_miscellaneous_parameters,
	    STATIC_FUNCTION(fix_frame_with_substitute_class_for_miscellaneous_parameters,
	    NIL,FALSE,1,1));
    Qfix_frame_with_substitute_class = 
	    STATIC_SYMBOL("FIX-FRAME-WITH-SUBSTITUTE-CLASS",AB_package);
    temp = 
	    SYMBOL_FUNCTION(Qfix_frame_with_substitute_class_for_miscellaneous_parameters);
    set_get(Qmiscellaneous_parameters,Qfix_frame_with_substitute_class,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfix_frame_with_substitute_class),
	    Qclasses_which_define);
    temp = CONS(Qmiscellaneous_parameters,temp_1);
    mutate_global_property(Qfix_frame_with_substitute_class,temp,
	    Qclasses_which_define);
    Qhome = STATIC_SYMBOL("HOME",AB_package);
    string_constant_68 = 
	    STATIC_STRING("1n1m83D1y836Iy1n83DTy1r1m9k83-2cy1m9k837by1m9k83UIy1m9k9l1m9k832+y1m9k83k8y1m9k83-VYy1l9m1m83DTy83-qy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qhome);
    push_optimized_constant(Qstar);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_68));
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qcompile_interface_home_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTERFACE-HOME-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interface_home_attribute_for_slot,
	    STATIC_FUNCTION(compile_interface_home_attribute_for_slot,NIL,
	    TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qinterface_home_attribute,
	    SYMBOL_FUNCTION(Qcompile_interface_home_attribute_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qinterface_home_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_interface_home_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERFACE-HOME-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interface_home_attribute_from_slot,
	    STATIC_FUNCTION(write_interface_home_attribute_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qinterface_home_attribute,
	    SYMBOL_FUNCTION(Qwrite_interface_home_attribute_from_slot),
	    Qslot_value_writer);
    Qput_interface_home_attribute = 
	    STATIC_SYMBOL("PUT-INTERFACE-HOME-ATTRIBUTE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_interface_home_attribute,
	    STATIC_FUNCTION(put_interface_home_attribute,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qinterface_home_attribute,
	    SYMBOL_FUNCTION(Qput_interface_home_attribute),Qslot_putter);
    Qcompile_local_item_home_for_slot = 
	    STATIC_SYMBOL("COMPILE-LOCAL-ITEM-HOME-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_local_item_home_for_slot,
	    STATIC_FUNCTION(compile_local_item_home_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlocal_item_home,
	    SYMBOL_FUNCTION(Qcompile_local_item_home_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlocal_item_home,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_51 = 
	    STATIC_STRING("look up local home from kb g2-to-g2-data-interfaces");
    Qwrite_local_item_home_from_slot = 
	    STATIC_SYMBOL("WRITE-LOCAL-ITEM-HOME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_local_item_home_from_slot,
	    STATIC_FUNCTION(write_local_item_home_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlocal_item_home,
	    SYMBOL_FUNCTION(Qwrite_local_item_home_from_slot),
	    Qslot_value_writer);
    Qput_local_item_home = STATIC_SYMBOL("PUT-LOCAL-ITEM-HOME",AB_package);
    SET_SYMBOL_FUNCTION(Qput_local_item_home,
	    STATIC_FUNCTION(put_local_item_home,NIL,FALSE,3,3));
    mutate_global_property(Qlocal_item_home,
	    SYMBOL_FUNCTION(Qput_local_item_home),Qslot_putter);
    if (Cached_name_for_local_home == UNBOUND)
	Cached_name_for_local_home = Nil;
    Compute_name_for_local_home_p = Nil;
    Qicp_connection_specification = 
	    STATIC_SYMBOL("ICP-CONNECTION-SPECIFICATION",AB_package);
    Qlocalnet = STATIC_SYMBOL("LOCALNET",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qtcp_ip = STATIC_SYMBOL("TCP-IP",AB_package);
    string_constant_52 = STATIC_STRING("~A");
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qname_for_local_home = STATIC_SYMBOL("NAME-FOR-LOCAL-HOME",AB_package);
    SET_SYMBOL_FUNCTION(Qname_for_local_home,
	    STATIC_FUNCTION(name_for_local_home,NIL,FALSE,0,0));
}
