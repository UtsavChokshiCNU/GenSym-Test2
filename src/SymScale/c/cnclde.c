/* cnclde.c
 * Input file:  conclude.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cnclde.h"


Object Debug_conclude_p = UNBOUND;

/* DOUBLE-REALLOCATE-MANAGED-SIMPLE-VECTOR */
Object double_reallocate_managed_simple_vector(vector_1)
    Object vector_1;
{
    Object length_1, new_vector, svref_new_value, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(191,0);
    length_1 = SIMPLE_ARRAY_ANY_1_LENGTH(vector_1);
    new_vector = allocate_managed_simple_vector(FIX((SI_Long)2L * 
	    IFIX(length_1)));
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    svref_new_value = ISVREF(vector_1,i);
    ISVREF(new_vector,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_managed_simple_vector(vector_1);
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object The_type_description_of_item_access_cache = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_item_access_caches, Qchain_of_available_item_access_caches);

DEFINE_VARIABLE_WITH_SYMBOL(Item_access_cache_count, Qitem_access_cache_count);

Object Chain_of_available_item_access_caches_vector = UNBOUND;

/* ITEM-ACCESS-CACHE-STRUCTURE-MEMORY-USAGE */
Object item_access_cache_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(191,1);
    temp = Item_access_cache_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ITEM-ACCESS-CACHE-COUNT */
Object outstanding_item_access_cache_count()
{
    Object def_structure_item_access_cache_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(191,2);
    gensymed_symbol = IFIX(Item_access_cache_count);
    def_structure_item_access_cache_variable = 
	    Chain_of_available_item_access_caches;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_item_access_cache_variable))
	goto end_loop;
    def_structure_item_access_cache_variable = 
	    ISVREF(def_structure_item_access_cache_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ITEM-ACCESS-CACHE-1 */
Object reclaim_item_access_cache_1(item_access_cache)
    Object item_access_cache;
{
    Object temp, svref_arg_2;

    x_note_fn_call(191,3);
    inline_note_reclaim_cons(item_access_cache,Nil);
    temp = ISVREF(Chain_of_available_item_access_caches_vector,
	    IFIX(Current_thread_index));
    SVREF(item_access_cache,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_item_access_caches_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = item_access_cache;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ITEM-ACCESS-CACHE */
Object reclaim_structure_for_item_access_cache(item_access_cache)
    Object item_access_cache;
{
    x_note_fn_call(191,4);
    return reclaim_item_access_cache_1(item_access_cache);
}

static Object Qg2_defstruct_structure_name_item_access_cache_g2_struct;  /* g2-defstruct-structure-name::item-access-cache-g2-struct */

/* MAKE-PERMANENT-ITEM-ACCESS-CACHE-STRUCTURE-INTERNAL */
Object make_permanent_item_access_cache_structure_internal()
{
    Object def_structure_item_access_cache_variable;
    Object defstruct_g2_item_access_cache_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(191,5);
    def_structure_item_access_cache_variable = Nil;
    atomic_incff_symval(Qitem_access_cache_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_item_access_cache_variable = Nil;
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
	defstruct_g2_item_access_cache_variable = the_array;
	SVREF(defstruct_g2_item_access_cache_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_item_access_cache_g2_struct;
	def_structure_item_access_cache_variable = 
		defstruct_g2_item_access_cache_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_item_access_cache_variable);
}

/* MAKE-ITEM-ACCESS-CACHE-INTERNAL-1 */
Object make_item_access_cache_internal_1()
{
    Object def_structure_item_access_cache_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(191,6);
    def_structure_item_access_cache_variable = 
	    ISVREF(Chain_of_available_item_access_caches_vector,
	    IFIX(Current_thread_index));
    if (def_structure_item_access_cache_variable) {
	svref_arg_1 = Chain_of_available_item_access_caches_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_item_access_cache_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_item_access_cache_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_item_access_cache_g2_struct;
    }
    else
	def_structure_item_access_cache_variable = 
		make_permanent_item_access_cache_structure_internal();
    inline_note_allocate_cons(def_structure_item_access_cache_variable,Nil);
    ISVREF(def_structure_item_access_cache_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_item_access_cache_variable,FIX((SI_Long)2L)) = Nil;
    ISVREF(def_structure_item_access_cache_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_item_access_cache_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_item_access_cache_variable);
}

/* MAKE-ITEM-ACCESS-CACHE */
Object make_item_access_cache()
{
    Object item_access_cache, slot_description_vector, attribute_value_vector;

    x_note_fn_call(191,7);
    item_access_cache = make_item_access_cache_internal_1();
    slot_description_vector = 
	    allocate_managed_simple_vector(FIX(IFIX(Slot_description_cache_entry_size) 
	    * (SI_Long)16L));
    attribute_value_vector = 
	    allocate_managed_simple_vector(FIX(IFIX(Attribute_value_cache_entry_size) 
	    * (SI_Long)16L));
    SVREF(item_access_cache,FIX((SI_Long)2L)) = slot_description_vector;
    SVREF(item_access_cache,FIX((SI_Long)4L)) = attribute_value_vector;
    return VALUES_1(item_access_cache);
}

/* LOOKUP-CACHED-SLOT-DESCRIPTION-OF-CLASS-DESCRIPTION */
Object lookup_cached_slot_description_of_class_description(cache,
	    attribute_name,class_description,class_qualifier_qm)
    Object cache, attribute_name, class_description, class_qualifier_qm;
{
    Object slot_description_vector, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(191,8);
    slot_description_vector = ISVREF(cache,(SI_Long)2L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_TIMES(Slot_description_cache_entry_size,
	    ISVREF(cache,(SI_Long)1L)));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (EQ(attribute_name,ISVREF(slot_description_vector,i)) && 
	    EQ(class_description,ISVREF(slot_description_vector,i + 
	    (SI_Long)1L)) && EQ(class_qualifier_qm,
	    ISVREF(slot_description_vector,i + (SI_Long)2L))) {
	temp = ISVREF(slot_description_vector,i + (SI_Long)3L);
	goto end_1;
    }
    i = i + IFIX(Slot_description_cache_entry_size);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CACHE-SLOT-DESCRIPTION-OF-CLASS-DESCRIPTION */
Object cache_slot_description_of_class_description(cache,attribute_name,
	    class_description,class_qualifier_qm)
    Object cache, attribute_name, class_description, class_qualifier_qm;
{
    Object cache_vector, cache_count, slot_description_qm, start, temp;
    SI_Long svref_arg_2;

    x_note_fn_call(191,9);
    cache_vector = ISVREF(cache,(SI_Long)2L);
    cache_count = ISVREF(cache,(SI_Long)1L);
    if (FIXNUM_EQ(FIXNUM_TIMES(Slot_description_cache_entry_size,
	    cache_count),SIMPLE_ARRAY_ANY_1_LENGTH(cache_vector))) {
	cache_vector = double_reallocate_managed_simple_vector(cache_vector);
	SVREF(cache,FIX((SI_Long)2L)) = cache_vector;
    }
    slot_description_qm = 
	    get_slot_description_of_class_description_function(attribute_name,
	    class_description,class_qualifier_qm);
    start = FIXNUM_TIMES(Slot_description_cache_entry_size,cache_count);
    SVREF(cache_vector,start) = attribute_name;
    temp = FIXNUM_ADD1(start);
    SVREF(cache_vector,temp) = class_description;
    svref_arg_2 = IFIX(start) + (SI_Long)2L;
    ISVREF(cache_vector,svref_arg_2) = class_qualifier_qm;
    svref_arg_2 = IFIX(start) + (SI_Long)3L;
    ISVREF(cache_vector,svref_arg_2) = slot_description_qm;
    temp = FIXNUM_ADD1(ISVREF(cache,(SI_Long)1L));
    SVREF(cache,FIX((SI_Long)1L)) = temp;
    return VALUES_1(slot_description_qm);
}

/* LOOKUP-CACHED-ATTRIBUTE-DESCRIPTION-EVALUATION-VALUE */
Object lookup_cached_attribute_description_evaluation_value(cache,item,
	    attribute_description)
    Object cache, item, attribute_description;
{
    Object slot_description_vector, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(191,10);
    slot_description_vector = ISVREF(cache,(SI_Long)4L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_TIMES(Attribute_value_cache_entry_size,
	    ISVREF(cache,(SI_Long)3L)));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (EQ(item,ISVREF(slot_description_vector,i)) && 
	    EQ(attribute_description,ISVREF(slot_description_vector,i + 
	    (SI_Long)1L))) {
	temp = ISVREF(slot_description_vector,i + (SI_Long)2L);
	goto end_1;
    }
    i = i + IFIX(Attribute_value_cache_entry_size);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CACHE-ATTRIBUTE-DESCRIPTION-EVALUATION-VALUE */
Object cache_attribute_description_evaluation_value(cache,item,
	    attribute_description)
    Object cache, item, attribute_description;
{
    Object cache_vector, cache_count, value, start, temp;
    SI_Long svref_arg_2;

    x_note_fn_call(191,11);
    cache_vector = ISVREF(cache,(SI_Long)4L);
    cache_count = ISVREF(cache,(SI_Long)3L);
    if (FIXNUM_EQ(FIXNUM_TIMES(Attribute_value_cache_entry_size,
	    cache_count),SIMPLE_ARRAY_ANY_1_LENGTH(cache_vector))) {
	cache_vector = double_reallocate_managed_simple_vector(cache_vector);
	SVREF(cache,FIX((SI_Long)4L)) = cache_vector;
    }
    value = get_attribute_description_evaluation_value(item,
	    attribute_description);
    start = FIXNUM_TIMES(Attribute_value_cache_entry_size,cache_count);
    SVREF(cache_vector,start) = item;
    temp = FIXNUM_ADD1(start);
    SVREF(cache_vector,temp) = attribute_description;
    svref_arg_2 = IFIX(start) + (SI_Long)2L;
    ISVREF(cache_vector,svref_arg_2) = value;
    temp = FIXNUM_ADD1(ISVREF(cache,(SI_Long)3L));
    SVREF(cache,FIX((SI_Long)3L)) = temp;
    return VALUES_1(value);
}

/* DELETE-ITEM-ACCESS-CACHE */
Object delete_item_access_cache(cache)
    Object cache;
{
    Object attribute_value_vector, thing;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(191,12);
    attribute_value_vector = ISVREF(cache,(SI_Long)4L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(cache,(SI_Long)3L));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    thing = ISVREF(attribute_value_vector,
	    IFIX(Attribute_value_cache_entry_size) * i + (SI_Long)2L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_managed_simple_vector(attribute_value_vector);
    reclaim_managed_simple_vector(ISVREF(cache,(SI_Long)2L));
    reclaim_item_access_cache_1(cache);
    return VALUES_1(Qnil);
}

Object Denotation_type_code_prop = UNBOUND;

Object Denotation_type_size_prop = UNBOUND;

Object Denotation_type_validator_prop = UNBOUND;

Object Denotation_type_defined_check_prop = UNBOUND;

Object Denotation_type_wildcard_arg_index_qm_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Denotation_size_vector, Qdenotation_size_vector);

DEFINE_VARIABLE_WITH_SYMBOL(Current_conclude_innermost_attribute_description, Qcurrent_conclude_innermost_attribute_description);

DEFINE_VARIABLE_WITH_SYMBOL(The_denotation_conversion_buffer, Qthe_denotation_conversion_buffer);

static Object Qab_structure;       /* structure */

static Object Qno_type_in_denotation_sequence_element_structure;  /* no-type-in-denotation-sequence-element-structure */

static Object Qelement_structure;  /* element-structure */

static Object string_constant;     /* "~NV" */

static Object Qnon_structure_indenotation_sequence_element;  /* non-structure-indenotation-sequence-element */

static Object Qindex;              /* index */

/* DENOTATION-SEQUENCE->DENOTATION */
Object denotation_sequence_gt_denotation(sequence)
    Object sequence;
{
    Object length_1, gensymed_symbol, held_vector, structure, type_qm;
    Object ab_loop_iter_flag_, elt_1, validated_elt, new_length_or_error, temp;
    Object result_1, svref_new_value;
    SI_Long next_index, length_2, i, ab_loop_bind_;

    x_note_fn_call(191,13);
    if ( !TRUEP(The_denotation_conversion_buffer))
	The_denotation_conversion_buffer = 
		allocate_managed_simple_vector(FIX((SI_Long)6L * 
		IFIX(Maximum_denotation_sequence_elements)));
    length_1 = FIX((SI_Long)0L);
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_2 = (SI_Long)0L;
    structure = Nil;
    i = (SI_Long)0L;
    type_qm = Nil;
    ab_loop_iter_flag_ = T;
    held_vector = M_CAR(gensymed_symbol);
    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_2)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    structure = validated_elt;
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    type_qm = CONSP(structure) && EQ(M_CDR(structure),Qab_structure) ? 
	    estructure_slot(structure,Qtype,Nil) : Qnil;
    if (type_qm) {
	new_length_or_error = 
		fill_denotation_from_denotation_element(structure,length_1);
	if (FIXNUMP(new_length_or_error))
	    length_1 = new_length_or_error;
	else
	    return VALUES_1(new_length_or_error);
    }
    else if (CONSP(structure) && EQ(M_CDR(structure),Qab_structure))
	return make_access_error_1(Qno_type_in_denotation_sequence_element_structure,
		gensym_list_2(Qelement_structure,tformat_text_string(2,
		string_constant,structure)));
    else {
	temp = tformat_text_string(2,string_constant,sequence);
	return make_access_error_1(Qnon_structure_indenotation_sequence_element,
		gensym_list_4(Qsequence,temp,Qindex,FIX(i)));
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    result_1 = allocate_managed_simple_vector(length_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    svref_new_value = ISVREF(The_denotation_conversion_buffer,i);
    ISVREF(result_1,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    temp = result_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qsequence_element;   /* sequence-element */

static Object Qelement;            /* element */

static Object Qdenotation_type_code;  /* denotation-type-code */

static Object Qdenotation_type_size;  /* denotation-type-size */

static Object Qno_index_for_element_denotation_element;  /* no-index-for-element-denotation-element */

static Object Qdenotation_element;  /* denotation-element */

static Object string_constant_1;   /* "~NA" */

static Object Qstructure_attribute;  /* structure-attribute */

static Object Qattribute;          /* attribute */

static Object Qname;               /* name */

static Object Qclass_qualifier;    /* class-qualifier */

static Object Qno_name_for_attribute_denotation_element;  /* no-name-for-attribute-denotation-element */

static Object Qvariable_value;     /* variable-value */

static Object Qitem_color_pattern_change;  /* item-color-pattern-change */

static Object Qcustom_event;       /* custom-event */

static Object Qcustom_event_name;  /* custom-event-name */

static Object Qadd_item_to_workspace;  /* add-item-to-workspace */

static Object Qremove_item_from_workspace;  /* remove-item-from-workspace */

static Object Qitem_event;         /* item-event */

static Object Qitem_event_name;    /* item-event-name */

static Object Qunknown_denotation_element_type;  /* unknown-denotation-element-type */

/* FILL-DENOTATION-FROM-DENOTATION-ELEMENT */
Object fill_denotation_from_denotation_element(structure,length_1)
    Object structure, length_1;
{
    Object type, index_1, vector_1, start_position, temp, temp_1, name;
    Object class_qualifier_qm;
    SI_Long svref_arg_2;

    x_note_fn_call(191,14);
    type = estructure_slot(structure,Qtype,Nil);
    if (EQ(type,Qsequence_element) || EQ(type,Qelement)) {
	index_1 = estructure_slot(structure,Qindex,Nil);
	if (index_1) {
	    vector_1 = The_denotation_conversion_buffer;
	    start_position = length_1;
	    svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qelement),
		    Qdenotation_type_code);
	    ISVREF(vector_1,svref_arg_2) = temp;
	    temp = FIXNUM_ADD1(start_position);
	    SVREF(vector_1,temp) = Qelement;
	    svref_arg_2 = IFIX(start_position) + (SI_Long)2L;
	    ISVREF(vector_1,svref_arg_2) = index_1;
	    temp_1 = FIXNUM_ADD(length_1,
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qelement),
		    Qdenotation_type_size));
	}
	else
	    temp_1 = 
		    make_access_error_1(Qno_index_for_element_denotation_element,
		    gensym_list_2(Qdenotation_element,
		    tformat_text_string(2,string_constant_1,structure)));
    }
    else if (EQ(type,Qstructure_attribute) || EQ(type,Qattribute)) {
	name = estructure_slot(structure,Qname,Nil);
	class_qualifier_qm = EQ(type,Qattribute) ? 
		estructure_slot(structure,Qclass_qualifier,Nil) : Qnil;
	if (name) {
	    vector_1 = The_denotation_conversion_buffer;
	    start_position = length_1;
	    svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute),
		    Qdenotation_type_code);
	    ISVREF(vector_1,svref_arg_2) = temp;
	    temp = FIXNUM_ADD1(start_position);
	    SVREF(vector_1,temp) = Qattribute;
	    svref_arg_2 = IFIX(start_position) + (SI_Long)2L;
	    ISVREF(vector_1,svref_arg_2) = name;
	    svref_arg_2 = IFIX(start_position) + (SI_Long)3L;
	    ISVREF(vector_1,svref_arg_2) = class_qualifier_qm;
	    temp_1 = FIXNUM_ADD(length_1,
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute),
		    Qdenotation_type_size));
	}
	else
	    temp_1 = 
		    make_access_error_1(Qno_name_for_attribute_denotation_element,
		    gensym_list_2(Qdenotation_element,
		    tformat_text_string(2,string_constant_1,structure)));
    }
    else if (EQ(type,Qvariable_value)) {
	vector_1 = The_denotation_conversion_buffer;
	start_position = length_1;
	svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvariable_value),
		Qdenotation_type_code);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp = FIXNUM_ADD1(start_position);
	SVREF(vector_1,temp) = Qvariable_value;
	temp_1 = FIXNUM_ADD(length_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvariable_value),
		Qdenotation_type_size));
    }
    else if (EQ(type,Qitem_color_pattern_change)) {
	vector_1 = The_denotation_conversion_buffer;
	start_position = length_1;
	svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_color_pattern_change),
		Qdenotation_type_code);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp = FIXNUM_ADD1(start_position);
	SVREF(vector_1,temp) = Qitem_color_pattern_change;
	temp_1 = FIXNUM_ADD(length_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_color_pattern_change),
		Qdenotation_type_size));
    }
    else if (EQ(type,Qcustom_event)) {
	vector_1 = The_denotation_conversion_buffer;
	start_position = length_1;
	svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcustom_event),
		Qdenotation_type_code);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp = FIXNUM_ADD1(start_position);
	SVREF(vector_1,temp) = Qcustom_event;
	svref_arg_2 = IFIX(start_position) + (SI_Long)2L;
	temp = estructure_slot(structure,Qcustom_event_name,Nil);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp_1 = FIXNUM_ADD(length_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcustom_event),
		Qdenotation_type_size));
    }
    else if (EQ(type,Qadd_item_to_workspace)) {
	vector_1 = The_denotation_conversion_buffer;
	start_position = length_1;
	svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qadd_item_to_workspace),
		Qdenotation_type_code);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp = FIXNUM_ADD1(start_position);
	SVREF(vector_1,temp) = Qadd_item_to_workspace;
	temp_1 = FIXNUM_ADD(length_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qadd_item_to_workspace),
		Qdenotation_type_size));
    }
    else if (EQ(type,Qremove_item_from_workspace)) {
	vector_1 = The_denotation_conversion_buffer;
	start_position = length_1;
	svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qremove_item_from_workspace),
		Qdenotation_type_code);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp = FIXNUM_ADD1(start_position);
	SVREF(vector_1,temp) = Qremove_item_from_workspace;
	temp_1 = FIXNUM_ADD(length_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qremove_item_from_workspace),
		Qdenotation_type_size));
    }
    else if (EQ(type,Qitem_event)) {
	vector_1 = The_denotation_conversion_buffer;
	start_position = length_1;
	svref_arg_2 = IFIX(start_position) + (SI_Long)0L;
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_event),
		Qdenotation_type_code);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp = FIXNUM_ADD1(start_position);
	SVREF(vector_1,temp) = Qitem_event;
	svref_arg_2 = IFIX(start_position) + (SI_Long)2L;
	temp = estructure_slot(structure,Qitem_event_name,Nil);
	ISVREF(vector_1,svref_arg_2) = temp;
	temp_1 = FIXNUM_ADD(length_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_event),
		Qdenotation_type_size));
    }
    else
	temp_1 = make_access_error_1(Qunknown_denotation_element_type,
		gensym_list_2(Qtype,type));
    return VALUES_1(temp_1);
}

/* SUB-DENOTATION */
Object sub_denotation varargs_1(int, n)
{
    Object denotation, start;
    Object end_qm, end_1, sub_denotation_1, ab_loop_iter_flag_;
    Object svref_new_value;
    SI_Long i, ab_loop_bind_, sub_i;
    Declare_varargs_nonrelocating;

    x_note_fn_call(191,15);
    INIT_ARGS_nonrelocating();
    denotation = REQUIRED_ARG_nonrelocating();
    start = REQUIRED_ARG_nonrelocating();
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    end_1 = end_qm;
    if (end_1);
    else
	end_1 = SIMPLE_ARRAY_ANY_1_LENGTH(denotation);
    sub_denotation_1 = allocate_managed_simple_vector(FIXNUM_MINUS(end_1,
	    start));
    i = IFIX(start);
    ab_loop_bind_ = IFIX(end_1);
    sub_i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	sub_i = sub_i + (SI_Long)1L;
    svref_new_value = ISVREF(denotation,i);
    ISVREF(sub_denotation_1,sub_i) = svref_new_value;
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(sub_denotation_1);
}

/* COPY-DENOTATION */
Object copy_denotation(d)
    Object d;
{
    Object len, new_d, svref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(191,16);
    len = SIMPLE_ARRAY_ANY_1_LENGTH(d);
    new_d = allocate_managed_simple_vector(len);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(len);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    svref_new_value = ISVREF(d,i);
    ISVREF(new_d,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(new_d);
}

/* RECLAIM-DENOTATION-FUNCTION */
Object reclaim_denotation_function(d)
    Object d;
{
    x_note_fn_call(191,17);
    reclaim_managed_simple_vector(d);
    return VALUES_1(Nil);
}

/* DENOTATION-NEXT-INDEX */
Object denotation_next_index(denotation,index_1)
    Object denotation, index_1;
{
    Object temp;

    x_note_fn_call(191,18);
    temp = FIXNUM_ADD(index_1,ISVREF(Denotation_size_vector,
	    IFIX(ISVREF(denotation,IFIX(index_1)))));
    return VALUES_1(temp);
}

/* DENOTATION-END-INDEX */
Object denotation_end_index(denotation)
    Object denotation;
{
    Object vector_length, result_1, i, temp;

    x_note_fn_call(191,19);
    vector_length = SIMPLE_ARRAY_ANY_1_LENGTH(denotation);
    result_1 = FIX((SI_Long)0L);
    i = FIX((SI_Long)0L);
  next_loop:
    if ( !FIXNUM_LT(i,vector_length))
	goto end_loop;
    result_1 = i;
    i = FIXNUM_ADD(i,ISVREF(Denotation_size_vector,IFIX(ISVREF(denotation,
	    IFIX(i)))));
    goto next_loop;
  end_loop:
    temp = result_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qitem_or_datum;      /* item-or-datum */

static Object list_constant;       /* # */

/* ITEM-TYPE-SPECIFICATION? */
Object item_type_specification_qm(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(191,20);
    if (symbolic_type_specification_subtype_p(type_specification,
	    Qitem_or_datum))
	temp = list_constant;
    else if (class_type_specification_p(type_specification))
	temp = type_specification;
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-CLASS-TYPE-SPECIFICATION-IF-UNIQUE */
Object get_class_type_specification_if_unique(type_specification)
    Object type_specification;
{
    Object temp, result_1, disjunct, ab_loop_list_, item_type_spec_qm;

    x_note_fn_call(191,21);
    temp = item_type_specification_qm(type_specification);
    if (temp);
    else if (union_type_specification_p(type_specification)) {
	result_1 = Nil;
	disjunct = Nil;
	ab_loop_list_ = CDR(type_specification);
	item_type_spec_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	disjunct = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	item_type_spec_qm = item_type_specification_qm(disjunct);
	if (item_type_spec_qm) {
	    if (result_1) {
		temp = Nil;
		goto end_1;
	    }
	    else
		result_1 = disjunct;
	}
	goto next_loop;
      end_loop:
	temp = result_1;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-STRUCTURE-TYPE-SPECIFICATION-IF-UNIQUE */
Object get_structure_type_specification_if_unique(type_specification)
    Object type_specification;
{
    Object temp, result_1, disjunct, ab_loop_list_;

    x_note_fn_call(191,22);
    if (structure_type_specification_p(type_specification))
	temp = type_specification;
    else if (union_type_specification_p(type_specification)) {
	result_1 = Nil;
	disjunct = Nil;
	ab_loop_list_ = CDR(type_specification);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	disjunct = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (structure_type_specification_p(disjunct)) {
	    if (result_1) {
		temp = Nil;
		goto end_1;
	    }
	    else
		result_1 = disjunct;
	}
	goto next_loop;
      end_loop:
	temp = result_1;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-SEQUENCE-TYPE-SPECIFICATION-IF-UNIQUE */
Object get_sequence_type_specification_if_unique(type_specification)
    Object type_specification;
{
    Object temp, result_1, disjunct, ab_loop_list_;

    x_note_fn_call(191,23);
    if (sequence_type_specification_p(type_specification))
	temp = type_specification;
    else if (union_type_specification_p(type_specification)) {
	result_1 = Nil;
	disjunct = Nil;
	ab_loop_list_ = CDR(type_specification);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	disjunct = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (sequence_type_specification_p(disjunct)) {
	    if (result_1) {
		temp = Nil;
		goto end_1;
	    }
	    else
		result_1 = disjunct;
	}
	goto next_loop;
      end_loop:
	temp = result_1;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qundefined_attribute;  /* undefined-attribute */

static Object Qattribute_name;     /* attribute-name */

static Object string_constant_2;   /* "~NQ" */

static Object Qattribute_does_not_exist_in_structure;  /* attribute-does-not-exist-in-structure */

/* ATTRIBUTE-DENOTATION-VALIDATOR */
Object attribute_denotation_validator(cache,root,denotation,index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object attribute_name, class_qualifier_qm, x2, item, class_description, sd;
    Object slot_description_qm, unaliased_name_qm, user_defined_slot_p;
    Object virtual_attribute_qm, slot_value_qm, temp_1, evaluator_info_qm;
    Object valid_p, next_root_qm;
    char temp;

    x_note_fn_call(191,24);
    attribute_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    class_qualifier_qm = ISVREF(denotation,(SI_Long)3L + IFIX(index_1));
    if (SIMPLE_VECTOR_P(root) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(root)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(root,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(root,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	item = root;
	class_description = ISVREF(item,(SI_Long)1L);
	sd = lookup_cached_slot_description_of_class_description(cache,
		attribute_name,class_description,class_qualifier_qm);
	if (sd);
	else
	    sd = cache_slot_description_of_class_description(cache,
		    attribute_name,class_description,class_qualifier_qm);
	if (Debug_conclude_p)
	    format((SI_Long)6L,T,"cd=~s aname=~s cq=~s sd=~s~%",
		    class_description,attribute_name,class_qualifier_qm,sd);
	slot_description_qm = sd;
	unaliased_name_qm =  !TRUEP(slot_description_qm) ||  
		!TRUEP(ISVREF(slot_description_qm,(SI_Long)8L)) ? 
		get_slot_name_for_alias_if_any(attribute_name,item) : Nil;
	user_defined_slot_p = slot_description_qm ? 
		ISVREF(slot_description_qm,(SI_Long)8L) : Qnil;
	virtual_attribute_qm = Nil;
	if (user_defined_slot_p) {
	    slot_value_qm = ISVREF(ISVREF(root,(SI_Long)0L),
		    IFIX(ISVREF(slot_description_qm,(SI_Long)8L)));
	    Current_conclude_innermost_attribute_description = 
		    slot_description_qm;
	    if (SIMPLE_VECTOR_P(slot_value_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(slot_value_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(slot_value_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	    if (temp);
	    else
		temp = TRUEP(serve_item_p(slot_value_qm));
	    temp_1 = temp ? slot_value_qm : 
		    make_inactive_item_in_attribute_error_message(slot_description_qm,
		    class_description,item,slot_value_qm);
	}
	else {
	    if (unaliased_name_qm) {
		temp_1 = 
			lookup_cached_slot_description_of_class_description(cache,
			unaliased_name_qm,class_description,Nil);
		if (temp_1);
		else
		    temp_1 = 
			    cache_slot_description_of_class_description(cache,
			    unaliased_name_qm,class_description,Nil);
		slot_description_qm = temp_1;
	    }
	    if (slot_description_qm) {
		evaluator_info_qm = ISVREF(slot_description_qm,(SI_Long)10L);
		if (evaluator_info_qm);
		else
		    evaluator_info_qm = 
			    cache_evaluator_slot_info(slot_description_qm);
	    }
	    else
		evaluator_info_qm = Nil;
	    valid_p = evaluator_info_qm ? (write_p ? 
		    ISVREF(evaluator_info_qm,(SI_Long)2L) : 
		    ISVREF(evaluator_info_qm,(SI_Long)3L)) : Qnil;
	    if (valid_p) {
		Current_conclude_innermost_attribute_description = 
			slot_description_qm;
		temp_1 = 
			lookup_cached_attribute_description_evaluation_value(cache,
			item,slot_description_qm);
		if (temp_1);
		else
		    temp_1 = 
			    cache_attribute_description_evaluation_value(cache,
			    item,slot_description_qm);
	    }
	    else {
		temp_1 = evaluator_info_qm ? ISVREF(evaluator_info_qm,
			(SI_Long)7L) : Qnil;
		if (temp_1);
		else
		    temp_1 = get_property_value_function(3,
			    get_symbol_properties_function(attribute_name),
			    Qvirtual_attribute,Nil);
		virtual_attribute_qm = temp_1;
		if (virtual_attribute_qm ? 
			TRUEP(type_specification_type_p(item,
			ISVREF(virtual_attribute_qm,(SI_Long)2L))) : 
			TRUEP(Nil)) {
		    Current_conclude_innermost_attribute_description = 
			    virtual_attribute_qm;
		    temp_1 = 
			    lookup_cached_attribute_description_evaluation_value(cache,
			    item,virtual_attribute_qm);
		    if (temp_1);
		    else
			temp_1 = 
				cache_attribute_description_evaluation_value(cache,
				item,virtual_attribute_qm);
		}
		else
		    temp_1 = write_p ? 
			    make_access_error_1(Qundefined_attribute,
			    gensym_list_2(Qattribute_name,
			    tformat_text_string(3,string_constant_2,
			    attribute_name,class_qualifier_qm))) : Qnil;
	    }
	}
    }
    else if (CONSP(root) && EQ(M_CDR(root),Qab_structure)) {
	next_root_qm = estructure_slot(root,attribute_name,Nil);
	temp_1 = next_root_qm ? next_root_qm : 
		make_access_error_1(Qattribute_does_not_exist_in_structure,
		gensym_list_4(Qab_structure,tformat_text_string(2,
		string_constant,root),Qattribute_name,attribute_name));
    }
    else
	temp_1 = make_attribute_access_on_non_frame_error(root,
		attribute_name,class_qualifier_qm);
    return VALUES_1(temp_1);
}

static Object Qg2_defstruct_structure_name_access_error_g2_struct;  /* g2-defstruct-structure-name::access-error-g2-struct */

static Object Qambiguous_attribute_definition;  /* ambiguous-attribute-definition */

static Object list_constant_1;     /* # */

static Object Qg2_defstruct_structure_name_virtual_attribute_g2_struct;  /* g2-defstruct-structure-name::virtual-attribute-g2-struct */

static Object Qunexported_attribute;  /* unexported-attribute */

static Object Qattribute_of_non_item;  /* attribute-of-non-item */

/* ATTRIBUTE-DENOTATION-DEFINED-CHECK */
Object attribute_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    Object attribute_name, class_qualifier_qm;
    Object item_type_specification_or_error;
    Object structure_type_specification_or_error, class_description;
    Object attribute_description_qm, temp, evaluator_info_qm;
    Object type_specification_qm, type_specification, slot_list, name;
    Object slot_type_spec, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(191,25);
    attribute_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    class_qualifier_qm = ISVREF(denotation,(SI_Long)3L + IFIX(index_1));
    item_type_specification_or_error = 
	    get_class_type_specification_if_unique(root);
    structure_type_specification_or_error = 
	    get_structure_type_specification_if_unique(root);
    if (SIMPLE_VECTOR_P(item_type_specification_or_error) && 
	    EQ(ISVREF(item_type_specification_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct))
	return VALUES_1(item_type_specification_or_error);
    else if (SIMPLE_VECTOR_P(structure_type_specification_or_error) && 
	    EQ(ISVREF(structure_type_specification_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct))
	return VALUES_1(structure_type_specification_or_error);
    else if (item_type_specification_or_error && 
	    structure_type_specification_or_error)
	return make_access_error_1(Qambiguous_attribute_definition,
		gensym_list_2(Qattribute_name,tformat_text_string(3,
		string_constant_2,attribute_name,class_qualifier_qm)));
    else if (item_type_specification_or_error) {
	class_description = 
		lookup_global_or_kb_specific_property_value(M_CAR(M_CDR(item_type_specification_or_error)),
		Class_description_gkbprop);
	attribute_description_qm = 
		get_attribute_description_from_class_description(class_description,
		attribute_name,class_qualifier_qm);
	if ( !TRUEP(attribute_description_qm)) {
	    if (EQ(attribute_name,Qstar))
		return VALUES_2(list_constant_1,Nil);
	    else
		return make_access_error_1(Qundefined_attribute,
			gensym_list_2(Qattribute_name,
			tformat_text_string(3,string_constant_2,
			attribute_name,class_qualifier_qm)));
	}
	else if (SIMPLE_VECTOR_P(attribute_description_qm) && 
		EQ(ISVREF(attribute_description_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_virtual_attribute_g2_struct)) {
	    temp = ISVREF(attribute_description_qm,(SI_Long)3L);
	    return VALUES_2(temp,Nil);
	}
	else if (ISVREF(attribute_description_qm,(SI_Long)8L)) {
	    temp = ISVREF(attribute_description_qm,(SI_Long)5L);
	    return VALUES_2(temp,T);
	}
	else {
	    if (attribute_description_qm) {
		evaluator_info_qm = ISVREF(attribute_description_qm,
			(SI_Long)10L);
		if (evaluator_info_qm);
		else
		    evaluator_info_qm = 
			    cache_evaluator_slot_info(attribute_description_qm);
	    }
	    else
		evaluator_info_qm = Nil;
	    type_specification_qm = evaluator_info_qm ? 
		    ISVREF(evaluator_info_qm,(SI_Long)1L) : Qnil;
	    if (type_specification_qm)
		return VALUES_2(type_specification_qm,Nil);
	    else
		return make_access_error_1(Qunexported_attribute,
			gensym_list_2(Qattribute_name,
			tformat_text_string(3,string_constant_2,
			attribute_name,class_qualifier_qm)));
	}
    }
    else if (structure_type_specification_or_error) {
	type_specification = structure_type_specification_or_error;
	if (EQ(attribute_name,Qstar))
	    return VALUES_2(list_constant_1,Nil);
	else if (M_CDR(type_specification)) {
	    slot_list = M_CAR(M_CDR(type_specification));
	    name = Nil;
	    slot_type_spec = Nil;
	    ab_loop_list_ = slot_list;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    name = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    slot_type_spec = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(name,attribute_name)) {
		temp =  
			!TRUEP(type_specifications_could_intersect_in_kb_p(slot_type_spec,
			list_constant)) ? T : Nil;
		return VALUES_2(slot_type_spec,temp);
	    }
	    goto next_loop;
	  end_loop:
	    return VALUES_2(list_constant_1,Nil);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_2(list_constant_1,Nil);
    }
    else
	return make_access_error_1(Qattribute_of_non_item,
		gensym_list_2(Qattribute_name,tformat_text_string(3,
		string_constant_2,attribute_name,class_qualifier_qm)));
}

/* ALIASED-ATTRIBUTE-DENOTATION-VALIDATOR */
Object aliased_attribute_denotation_validator(cache,root,denotation,
	    index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object aliased_name, attribute_name, class_qualifier_qm;

    x_note_fn_call(191,26);
    aliased_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    attribute_name = ISVREF(denotation,(SI_Long)3L + IFIX(index_1));
    class_qualifier_qm = ISVREF(denotation,(SI_Long)4L + IFIX(index_1));
    return VALUES_1(Nil);
}

/* ALIASED-ATTRIBUTE-DENOTATION-DEFINED-CHECK */
Object aliased_attribute_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    Object aliased_name, attribute_name, class_qualifier_qm;

    x_note_fn_call(191,27);
    aliased_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    attribute_name = ISVREF(denotation,(SI_Long)3L + IFIX(index_1));
    class_qualifier_qm = ISVREF(denotation,(SI_Long)4L + IFIX(index_1));
    return VALUES_1(Nil);
}

static Object Qnon_integer_index;  /* non-integer-index */

static Object Qvalue;              /* value */

static Object Qelement_does_not_exist;  /* element-does-not-exist */

static Object string_constant_3;   /* "~NF" */

static Object Qindex_out_of_range;  /* index-out-of-range */

static Object Qlist_is_empty;      /* list-is-empty */

static Object Qelement_of_item_not_array_or_list;  /* element-of-item-not-array-or-list */

static Object Qitem;               /* item */

static Object Qitem_reference;     /* item-reference */

static Object Qelement_of_non_array_list_or_sequence;  /* element-of-non-array-list-or-sequence */

static Object Qitem_or_value;      /* item-or-value */

/* ELEMENT-DENOTATION-VALIDATOR */
Object element_denotation_validator(cache,root,denotation,index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object element_index, temp, x2, sub_class_bit_vector, length_1;
    Object item_or_value, element_qm, gensymed_symbol_3, gensymed_symbol_4;
    Object element;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(191,28);
    element_index = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    if ( !FIXNUMP(element_index))
	temp = make_access_error_1(Qnon_integer_index,gensym_list_2(Qvalue,
		tformat_text_string(2,string_constant,element_index)));
    else {
	if (SIMPLE_VECTOR_P(root) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(root)) 
		> (SI_Long)2L &&  !EQ(ISVREF(root,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(root,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    sub_class_bit_vector = ISVREF(ISVREF(root,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	    if (temp_1) {
		length_1 = ISVREF(root,(SI_Long)20L);
		if (FIXNUMP(element_index) && IFIX(element_index) >= 
			(SI_Long)0L && FIXNUM_LT(element_index,length_1)) {
		    item_or_value = g2_array_aref(root,element_index);
		    if ( !TRUEP(item_or_value))
			temp = make_access_error_1(Qelement_does_not_exist,
				gensym_list_4(Qarray,tformat_text_string(2,
				string_constant_3,root),Qindex,element_index));
		    else {
			if (SIMPLE_VECTOR_P(item_or_value) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				> (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(item_or_value,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1);
			else
			    temp_1 = 
				    TRUEP(aggregate_evaluation_value_p(item_or_value));
			if (temp_1)
			    temp = FIXNUMP(item_or_value) || item_or_value 
				    && SYMBOLP(item_or_value) || 
				    SIMPLE_VECTOR_P(item_or_value) ? 
				    item_or_value : 
				    copy_if_evaluation_value_1(item_or_value);
			else
			    temp = Nil;
		    }
		}
		else
		    temp = make_access_error_1(Qindex_out_of_range,
			    gensym_list_2(Qindex,element_index));
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(root,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    if (g2_list_empty_p(root))
			temp = make_access_error_1(Qlist_is_empty,
				gensym_list_2(Qlist,tformat_text_string(2,
				string_constant_3,root)));
		    else {
			element_qm = 
				nth_g2_list_item_or_evaluation_value(element_index,
				root,Nil);
			if (SIMPLE_VECTOR_P(element_qm) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_qm)) 
				> (SI_Long)2L &&  !EQ(ISVREF(element_qm,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(element_qm,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1);
			else
			    temp_1 = 
				    TRUEP(aggregate_evaluation_value_p(element_qm));
			temp = temp_1 ? (FIXNUMP(element_qm) || element_qm 
				&& SYMBOLP(element_qm) || 
				SIMPLE_VECTOR_P(element_qm) ? element_qm : 
				copy_if_evaluation_value_1(element_qm)) : 
				make_access_error_1(Qelement_of_item_not_array_or_list,
				gensym_list_2(Qitem,tformat_text_string(2,
				string_constant_3,root)));
		    }
		}
		else
		    temp = Qnil;
	    }
	}
	else if (CONSP(root) && EQ(M_CDR(root),Qsequence)) {
	    length_1 = FIXNUM_SUB1(ISVREF(M_CAR(root),(SI_Long)1L));
	    if ((SI_Long)-1L < IFIX(element_index) && 
		    FIXNUM_LT(element_index,length_1)) {
		gensymed_symbol_3 = M_CAR(root);
		gensymed_symbol_4 = FIXNUM_ADD1(element_index);
		element = FIXNUM_LE(ISVREF(M_CAR(root),(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(M_CAR(root),
			IFIX(FIXNUM_ADD(gensymed_symbol_4,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(gensymed_symbol_3,
			(IFIX(gensymed_symbol_4) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(gensymed_symbol_4) & (SI_Long)1023L);
		if (CONSP(element) && EQ(M_CDR(element),Qitem_reference))
		    temp = ISVREF(M_CAR(element),(SI_Long)3L);
		else {
		    if (SIMPLE_VECTOR_P(element) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(element,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(element,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1);
		    else
			temp_1 = TRUEP(aggregate_evaluation_value_p(element));
		    if (temp_1)
			temp = FIXNUMP(element) || element && 
				SYMBOLP(element) || 
				SIMPLE_VECTOR_P(element) ? element : 
				copy_if_evaluation_value_1(element);
		    else
			temp = Nil;
		}
	    }
	    else
		temp = make_access_error_1(Qindex_out_of_range,
			gensym_list_2(Qsequence,tformat_text_string(2,
			string_constant_1,root)));
	}
	else
	    temp = 
		    make_access_error_1(Qelement_of_non_array_list_or_sequence,
		    gensym_list_2(Qitem_or_value,tformat(2,
		    string_constant_1,root)));
    }
    return VALUES_1(temp);
}

static Object Qdenotation_of_non_list_array_or_sequence;  /* denotation-of-non-list-array-or-sequence */

/* ELEMENT-DENOTATION-DEFINED-CHECK */
Object element_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    Object element_index, item_type_specification_or_error;
    Object sequence_type_specification_or_error, class_description;
    Object sub_class_bit_vector, list_element_type, element_type_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(191,29);
    element_index = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    item_type_specification_or_error = 
	    get_class_type_specification_if_unique(root);
    sequence_type_specification_or_error = 
	    get_sequence_type_specification_if_unique(root);
    if ( !TRUEP(item_type_specification_or_error) &&  
	    !TRUEP(sequence_type_specification_or_error))
	return make_access_error_1(Qdenotation_of_non_list_array_or_sequence,
		gensym_list_2(Qitem_or_value,tformat_text_string(2,
		string_constant_1,root)));
    else if (item_type_specification_or_error) {
	class_description = 
		lookup_global_or_kb_specific_property_value(M_CAR(M_CDR(item_type_specification_or_error)),
		Class_description_gkbprop);
	sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
	if (temp)
	    return VALUES_2(Nil,Nil);
	else {
	    sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		list_element_type = class_description_list_type(root);
		if (type_specifications_could_intersect_in_kb_p(list_element_type,
			list_constant))
		    return VALUES_2(list_element_type,T);
		else
		    return VALUES_2(Nil,Nil);
	    }
	    else
		return make_access_error_1(Qdenotation_of_non_list_array_or_sequence,
			gensym_list_2(Qitem_or_value,tformat_text_string(2,
			string_constant_1,root)));
	}
    }
    else if (sequence_type_specification_or_error) {
	element_type_qm = CADR(sequence_type_specification_or_error);
	FIXNUMP(element_index);
	if (element_type_qm)
	    return VALUES_2(element_type_qm,T);
	else
	    return VALUES_2(Nil,Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qlist_type;          /* list-type */

/* CLASS-DESCRIPTION-LIST-TYPE */
Object class_description_list_type(class_description)
    Object class_description;
{
    Object slot_description, temp;

    x_note_fn_call(191,30);
    slot_description = 
	    get_slot_description_of_class_description_function(Qlist_type,
	    class_description,Nil);
    temp = ISVREF(slot_description,(SI_Long)6L);
    return VALUES_1(temp);
}

/* VIRTUAL-ATTRIBUTE-DENOTATION-VALIDATOR */
Object virtual_attribute_denotation_validator(cache,root,denotation,
	    index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object virtual_attribute_name, virtual_attribute_qm, temp;

    x_note_fn_call(191,31);
    virtual_attribute_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    virtual_attribute_qm = get_property_value_function(3,
	    get_symbol_properties_function(virtual_attribute_name),
	    Qvirtual_attribute,Nil);
    if ( !TRUEP(virtual_attribute_qm))
	temp = make_no_such_virtual_attribute_error_message(root,
		virtual_attribute_name);
    else if (type_specification_type_p(root,ISVREF(virtual_attribute_qm,
	    (SI_Long)2L))) {
	Current_conclude_innermost_attribute_description = 
		virtual_attribute_qm;
	temp = lookup_cached_attribute_description_evaluation_value(cache,
		root,virtual_attribute_qm);
	if (temp);
	else
	    temp = cache_attribute_description_evaluation_value(cache,root,
		    virtual_attribute_qm);
    }
    else
	temp = make_no_such_virtual_attribute_error_message(root,
		virtual_attribute_name);
    return VALUES_1(temp);
}

/* VIRTUAL-ATTRIBUTE-DENOTATION-DEFINED-CHECK */
Object virtual_attribute_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    Object virtual_attribute_name, virtual_attribute_qm, temp;

    x_note_fn_call(191,32);
    virtual_attribute_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    virtual_attribute_qm = get_property_value_function(3,
	    get_symbol_properties_function(virtual_attribute_name),
	    Qvirtual_attribute,Nil);
    if ( !TRUEP(virtual_attribute_qm))
	return make_no_such_virtual_attribute_error_message(root,
		virtual_attribute_name);
    else {
	temp = ISVREF(virtual_attribute_qm,(SI_Long)2L);
	return VALUES_2(temp,Nil);
    }
}

/* VARIABLE-VALUE-DENOTATION-VALIDATOR */
Object variable_value_denotation_validator(cache,root,denotation,index_1,
	    write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object sub_class_bit_vector, current_computation_frame;
    Object current_computation_flags, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);

    x_note_fn_call(191,33);
    sub_class_bit_vector = ISVREF(ISVREF(root,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Variable_or_parameter_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
	current_computation_frame = root;
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  0);
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) &  ~(SI_Long)4L);
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) | (SI_Long)256L);
	    temp_1 = get_current_evaluation_value(root,Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	temp_1 = make_conclude_into_non_v_or_p_error_message(root);
    return VALUES_1(temp_1);
}

static Object Qvariable_value_of_non_variable_or_parameter;  /* variable-value-of-non-variable-or-parameter */

static Object Qab_class;           /* class */

/* VARIABLE-VALUE-DENOTATION-DEFINED-CHECK */
Object variable_value_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    Object item_type_specification_or_error_qm, class_description;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(191,34);
    item_type_specification_or_error_qm = 
	    get_class_type_specification_if_unique(root);
    if (SIMPLE_VECTOR_P(item_type_specification_or_error_qm) && 
	    EQ(ISVREF(item_type_specification_or_error_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct))
	return VALUES_2(item_type_specification_or_error_qm,Nil);
    else {
	class_description = 
		lookup_global_or_kb_specific_property_value(M_CAR(M_CDR(item_type_specification_or_error_qm)),
		Class_description_gkbprop);
	sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
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
	if (temp)
	    return VALUES_2(Nil,T);
	else {
	    temp_1 = 
		    make_access_error_1(Qvariable_value_of_non_variable_or_parameter,
		    gensym_list_2(Qab_class,ISVREF(class_description,
		    (SI_Long)1L)));
	    return VALUES_2(temp_1,Nil);
	}
    }
}

/* ITEM-COLOR-PATTERN-CHANGE-DENOTATION-VALIDATOR */
Object item_color_pattern_change_denotation_validator(cache,root,
	    denotation,index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object x2, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(191,35);
    if (SIMPLE_VECTOR_P(root) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(root)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(root,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(root,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(root,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? icon_color_pattern(root) : Nil;
    return VALUES_1(temp_1);
}

/* ITEM-COLOR-PATTERN-CHANGE-DENOTATION-DEFINED-CHECK */
Object item_color_pattern_change_denotation_defined_check(root,denotation,
	    index_1)
    Object root, denotation, index_1;
{
    x_note_fn_call(191,36);
    return VALUES_2(Nil,T);
}

/* CUSTOM-EVENT-DENOTATION-VALIDATOR */
Object custom_event_denotation_validator(cache,root,denotation,index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object event_name, x2, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(191,37);
    event_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    if (SIMPLE_VECTOR_P(root) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(root)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(root,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(root,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(root,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CUSTOM-EVENT-DENOTATION-DEFINED-CHECK */
Object custom_event_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    Object event_name;

    x_note_fn_call(191,38);
    event_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    return VALUES_2(Nil,T);
}

/* ADD-ITEM-TO-WORKSPACE-DENOTATION-VALIDATOR */
Object add_item_to_workspace_denotation_validator(cache,root,denotation,
	    index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(191,39);
    sub_class_bit_vector = ISVREF(ISVREF(root,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* ADD-ITEM-TO-WORKSPACE-DENOTATION-DEFINED-CHECK */
Object add_item_to_workspace_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    x_note_fn_call(191,40);
    return VALUES_2(Nil,T);
}

/* REMOVE-ITEM-FROM-WORKSPACE-DENOTATION-VALIDATOR */
Object remove_item_from_workspace_denotation_validator(cache,root,
	    denotation,index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(191,41);
    sub_class_bit_vector = ISVREF(ISVREF(root,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOVE-ITEM-FROM-WORKSPACE-DENOTATION-DEFINED-CHECK */
Object remove_item_from_workspace_denotation_defined_check(root,denotation,
	    index_1)
    Object root, denotation, index_1;
{
    x_note_fn_call(191,42);
    return VALUES_2(Nil,T);
}

/* ITEM-EVENT-DENOTATION-VALIDATOR */
Object item_event_denotation_validator(cache,root,denotation,index_1,write_p)
    Object cache, root, denotation, index_1, write_p;
{
    Object event_name, x2, temp_1;
    char temp;

    x_note_fn_call(191,43);
    event_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    if (EQ(event_name,Qdelete)) {
	if (SIMPLE_VECTOR_P(root) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(root)) 
		> (SI_Long)2L &&  !EQ(ISVREF(root,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(root,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? ISVREF(ISVREF(root,(SI_Long)1L),(SI_Long)16L) : Nil;
    return VALUES_1(temp_1);
}

/* ITEM-EVENT-DENOTATION-DEFINED-CHECK */
Object item_event_denotation_defined_check(root,denotation,index_1)
    Object root, denotation, index_1;
{
    Object event_name;

    x_note_fn_call(191,44);
    event_name = ISVREF(denotation,(SI_Long)2L + IFIX(index_1));
    return VALUES_2(Nil,T);
}

DEFINE_VARIABLE_WITH_SYMBOL(Comp_trace_level, Qcomp_trace_level);

Object Subscription_callback_arg_types = UNBOUND;

static Object Qprocedure;          /* procedure */

static Object Qno_callback_found;  /* no-callback-found */

static Object Qcallback;           /* callback */

static Object Qitem_representation;  /* item-representation */

static Object Qsocket;             /* socket */

static Object Qsession_id;         /* session-id */

/* REPRESENT-ITEM-INTERNAL */
Object represent_item_internal(icp_socket_qm,frame,denotation,callback,
	    user_data_value)
    Object icp_socket_qm, frame, denotation, callback, user_data_value;
{
    Object x2, sub_class_bit_vector, procedure_qm_1, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    Object gensymed_symbol_7, definition_error_or_inner_item_index;
    Object class_description_qm, temp_1, representation, svref_new_value;
    Object frame_serial_number_setf_arg, old, new_1, item_or_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Object result;

    x_note_fn_call(191,45);
    if (icp_socket_qm) {
	if (SIMPLE_VECTOR_P(callback) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(callback)) > (SI_Long)2L && 
		 !EQ(ISVREF(callback,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(callback,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(callback,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
    if (temp)
	icp_socket_qm = Nil;
    if ( !TRUEP(icp_socket_qm) && SYMBOLP(callback)) {
	procedure_qm_1 = get_instance_with_name_if_any(Qprocedure,callback);
	if ( !TRUEP(procedure_qm_1))
	    return make_access_error_1(Qno_callback_found,
		    gensym_list_2(Qcallback,callback));
	else
	    callback = procedure_qm_1;
    }
    if ( !TRUEP(icp_socket_qm)) {
	result = check_procedure_arglist(callback,
		Subscription_callback_arg_types,Nil);
	MVS_5(result,gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5,
		gensymed_symbol_6,gensymed_symbol_7);
	if (gensymed_symbol_3) {
	    if ((SI_Long)3L <= IFIX(Warning_message_level))
		give_warning_1(6,FIX((SI_Long)3L),gensymed_symbol_3,
			gensymed_symbol_4,gensymed_symbol_5,
			gensymed_symbol_6,gensymed_symbol_7);
	}
    }
    result = check_denotation_well_defined(frame,denotation);
    MVS_2(result,definition_error_or_inner_item_index,class_description_qm);
    if (SIMPLE_VECTOR_P(definition_error_or_inner_item_index) && 
	    EQ(ISVREF(definition_error_or_inner_item_index,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct))
	return VALUES_1(definition_error_or_inner_item_index);
    else {
	temp_1 = icp_socket_qm;
	if (temp_1);
	else
	    temp_1 = Local_pseudo_socket;
	representation = make_representation(temp_1,frame,
		Qitem_representation);
	temp_1 = icp_socket_qm;
	if (temp_1);
	else
	    temp_1 = Local_pseudo_socket;
	svref_new_value = slot_value_list_4(Qsocket,temp_1,Qsession_id,
		icp_socket_qm ? ISVREF(icp_socket_qm,(SI_Long)40L) : 
		FIX((SI_Long)12345678L));
	ISVREF(representation,(SI_Long)8L) = svref_new_value;
	svref_new_value = 
		demand_representation_callback_remote_procedure_name(callback);
	ISVREF(representation,(SI_Long)10L) = svref_new_value;
	if (SIMPLE_VECTOR_P(callback) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(callback)) > (SI_Long)2L && 
		 !EQ(ISVREF(callback,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(callback,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    frame_serial_number_setf_arg = ISVREF(callback,(SI_Long)3L);
	    old = ISVREF(representation,(SI_Long)11L);
	    new_1 = frame_serial_number_setf_arg;
	    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		    (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    ISVREF(representation,(SI_Long)11L) = svref_new_value;
	}
	ISVREF(representation,(SI_Long)13L) = denotation;
	item_or_value = user_data_value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	ISVREF(representation,(SI_Long)14L) = svref_new_value;
	install_subscription(class_description_qm,representation,
		denotation,definition_error_or_inner_item_index);
	return VALUES_1(representation);
    }
}

/* INSTALL-SUBSCRIPTION */
Object install_subscription(class_description,representation,denotation,
	    inner_item_index)
    Object class_description, representation, denotation, inner_item_index;
{
    Object subscription, class_name, subscriptions;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(191,46);
    subscription = make_class_subscription_1(denotation,inner_item_index,
	    representation);
    class_name = ISVREF(class_description,(SI_Long)1L);
    subscriptions = lookup_kb_specific_property_value(class_name,
	    Class_subscriptions_kbprop);
    if (subscriptions);
    else
	subscriptions = mutate_kb_specific_property_value(class_name,
		make_class_subscriptions_1(),Class_subscriptions_kbprop);
    if (denotation_element_specific_p(denotation,inner_item_index)) {
	gensym_push_modify_macro_arg = subscription;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(subscriptions,(SI_Long)1L);
	svref_new_value = gensym_cons_1(car_1,cdr_1);
	SVREF(subscriptions,FIX((SI_Long)1L)) = svref_new_value;
    }
    else {
	gensym_push_modify_macro_arg = subscription;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(subscriptions,(SI_Long)2L);
	svref_new_value = gensym_cons_1(car_1,cdr_1);
	SVREF(subscriptions,FIX((SI_Long)2L)) = svref_new_value;
    }
    return VALUES_1(ISVREF(representation,(SI_Long)15L) = subscriptions);
}

/* REMOVE-SUBSCRIPTION */
Object remove_subscription(class_subscriptions,representation)
    Object class_subscriptions, representation;
{
    Object subscription, ab_loop_list_, svref_new_value;
    char temp;

    x_note_fn_call(191,47);
    subscription = Nil;
    ab_loop_list_ = ISVREF(class_subscriptions,(SI_Long)1L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subscription = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(subscription,(SI_Long)3L),representation)) {
	reclaim_class_subscription_1(subscription);
	svref_new_value = delete_gensym_element_1(subscription,
		ISVREF(class_subscriptions,(SI_Long)1L));
	SVREF(class_subscriptions,FIX((SI_Long)1L)) = svref_new_value;
	temp = TRUEP(T);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp) {
	subscription = Nil;
	ab_loop_list_ = ISVREF(class_subscriptions,(SI_Long)2L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	subscription = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(ISVREF(subscription,(SI_Long)3L),representation)) {
	    svref_new_value = delete_gensym_element_1(subscription,
		    ISVREF(class_subscriptions,(SI_Long)2L));
	    SVREF(class_subscriptions,FIX((SI_Long)2L)) = svref_new_value;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
      end_2:;
    }
    return VALUES_1(ISVREF(representation,(SI_Long)15L) = Nil);
}

static Object Qall;                /* all */

/* DENOTATION->DENOTATION-SEQUENCE */
Object denotation_gt_denotation_sequence varargs_1(int, n)
{
    Object denotation;
    Object for_exposing_in_kb, end_index, sequence_elements, index_1;
    Object next_index, denotation_code, temp, gensymed_symbol, temp_1;
    Object item_or_value, x2, svref_new_value, val, structure;
    Object class_qualifier_qm;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(191,48);
    INIT_ARGS_nonrelocating();
    denotation = REQUIRED_ARG_nonrelocating();
    for_exposing_in_kb = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    end_index = denotation_end_index(denotation);
    sequence_elements = Qnil;
    index_1 = FIX((SI_Long)0L);
    next_index = denotation_next_index(denotation,FIX((SI_Long)0L));
    denotation_code = Nil;
  next_loop:
    denotation_code = ISVREF(denotation,IFIX(index_1));
    temp = denotation_code;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 1:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qattribute;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qattribute;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qname;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qname;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		val = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		item_or_value = EQ(val,Qstar) && for_exposing_in_kb ? Qall 
			: val;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		val = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		item_or_value = EQ(val,Qstar) && for_exposing_in_kb ? Qall 
			: val;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    structure = eval_cons_1(gensymed_symbol,Qab_structure);
	    class_qualifier_qm = ISVREF(denotation,IFIX(index_1) + 
		    (SI_Long)3L);
	    if (class_qualifier_qm)
		set_evaluation_structure_slot(structure,Qclass_qualifier,
			class_qualifier_qm);
	    temp = structure;
	    break;
	  case 3:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qelement;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qelement;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qindex;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qindex;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  case 4:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qvirtual_attribute;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qvirtual_attribute;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qname;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qname;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  case 5:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qvariable_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qvariable_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  case 6:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qitem_color_pattern_change;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qitem_color_pattern_change;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  case 7:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qcustom_event;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qcustom_event;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qcustom_event_name;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qcustom_event_name;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  case 8:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qadd_item_to_workspace;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qadd_item_to_workspace;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  case 9:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qremove_item_from_workspace;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qremove_item_from_workspace;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  case 10:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qitem_event;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qitem_event;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_event_name;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qitem_event_name;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    sequence_elements = eval_cons_1(temp,sequence_elements);
    if (FIXNUM_EQ(index_1,end_index))
	return allocate_evaluation_sequence(nreverse(sequence_elements));
    index_1 = next_index;
    next_index = denotation_next_index(denotation,index_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qdenotation_type_wildcard_arg_index_qm;  /* denotation-type-wildcard-arg-index? */

/* DENOTATION-ELEMENT-SPECIFIC-P */
Object denotation_element_specific_p(denotation,index_1)
    Object denotation, index_1;
{
    Object type, wildcard_arg_index_qm, denotation_wildcard_qm, temp;

    x_note_fn_call(191,49);
    type = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
    wildcard_arg_index_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
	    Qdenotation_type_wildcard_arg_index_qm);
    if (wildcard_arg_index_qm) {
	denotation_wildcard_qm = ISVREF(denotation,
		IFIX(wildcard_arg_index_qm));
	temp = EQ(denotation_wildcard_qm,Qstar) ? Nil : T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DENOTATION-ELEMENT-EQUAL-P */
Object denotation_element_equal_p(denotation_1,index_1,denotation_2,index_2)
    Object denotation_1, index_1, denotation_2, index_2;
{
    Object type, size, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(191,50);
    if (denotation_element_specific_p(denotation_2,index_2)) {
	type = ISVREF(denotation_1,IFIX(FIXNUM_ADD1(index_1)));
	size = getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
		Qdenotation_type_size);
	i = IFIX(Denotation_element_overhead_slot_count);
	ab_loop_bind_ = IFIX(size);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !EQ(ISVREF(denotation_1,IFIX(index_1) + i),
		ISVREF(denotation_2,IFIX(index_2) + i))) {
	    temp = Nil;
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = T;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_conclude_frame_list, Qcurrent_conclude_frame_list);

DEFINE_VARIABLE_WITH_SYMBOL(Current_conclude_innermost_frame, Qcurrent_conclude_innermost_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Current_conclude_innermost_item_index, Qcurrent_conclude_innermost_item_index);

DEFINE_VARIABLE_WITH_SYMBOL(Current_subscribe_innermost_class, Qcurrent_subscribe_innermost_class);

DEFINE_VARIABLE_WITH_SYMBOL(Current_subscribe_innermost_item_index, Qcurrent_subscribe_innermost_item_index);

static Object Qno_items_implied_by_denotation;  /* no-items-implied-by-denotation */

/* CHECK-DENOTATION-WELL-DEFINED */
Object check_denotation_well_defined(frame_or_class_description,denotation)
    Object frame_or_class_description, denotation;
{
    Object current_subscribe_innermost_class;
    Object current_subscribe_innermost_item_index, x2, class_description, root;
    Object error_string_qm, temp_1;
    char temp;
    Declare_stack_pointer;
    Declare_special(2);
    Object result;

    x_note_fn_call(191,51);
    SAVE_STACK();
    current_subscribe_innermost_class = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_subscribe_innermost_class,Qcurrent_subscribe_innermost_class,current_subscribe_innermost_class,
	    1);
      current_subscribe_innermost_item_index = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_subscribe_innermost_item_index,Qcurrent_subscribe_innermost_item_index,current_subscribe_innermost_item_index,
	      0);
	if (SIMPLE_VECTOR_P(frame_or_class_description) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_or_class_description)) 
		> (SI_Long)2L &&  !EQ(ISVREF(frame_or_class_description,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame_or_class_description,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	class_description = temp ? ISVREF(frame_or_class_description,
		(SI_Long)1L) : frame_or_class_description;
	root = gensym_list_2(Qab_class,ISVREF(class_description,(SI_Long)1L));
	error_string_qm = check_denotation_well_defined_1(root,denotation);
	if (SIMPLE_VECTOR_P(error_string_qm) && EQ(ISVREF(error_string_qm,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct))
	    SAVE_VALUES(VALUES_1(error_string_qm));
	else if ( !TRUEP(Current_subscribe_innermost_item_index))
	    SAVE_VALUES(make_access_error_1(Qno_items_implied_by_denotation,
		    Nil));
	else {
	    temp_1 = 
		    lookup_global_or_kb_specific_property_value(M_CAR(M_CDR(Current_subscribe_innermost_class)),
		    Class_description_gkbprop);
	    SAVE_VALUES(VALUES_2(Current_subscribe_innermost_item_index,
		    temp_1));
	}
	reclaim_gensym_list_1(root);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qdenotation_type_defined_check;  /* denotation-type-defined-check */

/* CHECK-DENOTATION-WELL-DEFINED-1 */
Object check_denotation_well_defined_1(root,denotation)
    Object root, denotation;
{
    Object end_index, next_root_or_error_string, invertible_p, index_1;
    Object denotation_type_name, temp, temp_1;
    Object result;

    x_note_fn_call(191,52);
    end_index = denotation_end_index(denotation);
    next_root_or_error_string = Nil;
    invertible_p = Nil;
    index_1 = FIX((SI_Long)0L);
    denotation_type_name = Nil;
  next_loop:
    denotation_type_name = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
    if (Debug_conclude_p) {
	temp = root;
	temp_1 = index_1;
	format((SI_Long)5L,T,
		"root = ~s index=~s well-defined-checker=~s~%",temp,temp_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(denotation_type_name),
		Qdenotation_type_defined_check));
    }
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(denotation_type_name),
	    Qdenotation_type_defined_check);
    result = FUNCALL_3(temp,root,denotation,index_1);
    MVS_2(result,next_root_or_error_string,invertible_p);
    if (class_type_specification_p(root)) {
	Current_subscribe_innermost_class = root;
	Current_subscribe_innermost_item_index = index_1;
    }
    if (SIMPLE_VECTOR_P(next_root_or_error_string) && 
	    EQ(ISVREF(next_root_or_error_string,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct)) {
	temp = next_root_or_error_string;
	goto end_1;
    }
    else if (FIXNUM_EQ(index_1,end_index)) {
	temp = root;
	goto end_1;
    }
    else
	root = next_root_or_error_string;
    index_1 = FIXNUM_ADD(index_1,ISVREF(Denotation_size_vector,
	    IFIX(ISVREF(denotation,IFIX(index_1)))));
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* DENOTATION-ENDS-IN-WILDCARD-P */
Object denotation_ends_in_wildcard_p(denotation)
    Object denotation;
{
    Object end_index, index_1, denotation_type, wildcard_arg_index_qm, temp;

    x_note_fn_call(191,53);
    end_index = denotation_end_index(denotation);
    index_1 = FIX((SI_Long)0L);
    denotation_type = Nil;
    wildcard_arg_index_qm = Nil;
  next_loop:
    denotation_type = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
    wildcard_arg_index_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(denotation_type),
	    Qdenotation_type_wildcard_arg_index_qm);
    if (FIXNUM_EQ(index_1,end_index)) {
	temp = wildcard_arg_index_qm ? (EQ(ISVREF(denotation,
		IFIX(FIXNUM_ADD(index_1,wildcard_arg_index_qm))),Qstar) ? 
		T : Nil) : Qnil;
	goto end_1;
    }
    else if (wildcard_arg_index_qm && EQ(ISVREF(denotation,
	    IFIX(wildcard_arg_index_qm)),Qstar)) {
	temp = Nil;
	goto end_1;
    }
    index_1 = FIXNUM_ADD(index_1,ISVREF(Denotation_size_vector,
	    IFIX(ISVREF(denotation,IFIX(index_1)))));
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* G2-GET-UNIQUE-NAMED-ITEM */
Object g2_get_unique_named_item(item_class_ev,item_name_ev)
    Object item_class_ev, item_name_ev;
{
    Object item_class, item_name, item_qm;

    x_note_fn_call(191,54);
    item_class = item_class_ev;
    item_name = item_name_ev;
    item_qm = get_instance_with_name_if_any(item_class,item_name);
    if (item_qm)
	return VALUES_1(item_qm);
    else
	return VALUES_1(Evaluation_false_value);
}

static Object Kstack_error;        /* :stack-error */

/* G2-GET-UNIQUE-NAMED-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_get_unique_named_item_system_rpc_internal(gensymed_symbol,
	    item_class,item_name)
    Object gensymed_symbol, item_class, item_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,55);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_unique_named_item(item_class,item_name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-ITEM-WITH-UUID */
Object g2_get_item_with_uuid(uuid)
    Object uuid;
{
    Object item_qm;

    x_note_fn_call(191,56);
    item_qm = the_item_having_uuid(Qitem,uuid);
    if ( !(FIXNUMP(uuid) || SYMBOLP(uuid) || SIMPLE_VECTOR_P(uuid)))
	reclaim_if_evaluation_value_1(uuid);
    if (item_qm)
	return VALUES_1(item_qm);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-GET-ITEM-WITH-UUID-SYSTEM-RPC-INTERNAL */
Object g2_get_item_with_uuid_system_rpc_internal(gensymed_symbol,uuid)
    Object gensymed_symbol, uuid;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,57);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_item_with_uuid(uuid);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* G2-MAKE-UUID */
Object g2_make_uuid()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object uuid_internal;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(191,58);
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
	      uuid_internal = make_uuid();
	      twrite_uuid_printed_representation(uuid_internal);
	      reclaim_wide_string(uuid_internal);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_4;   /* "~A" */

static Object string_constant_5;   /* "~a" */

static Object string_constant_6;   /* "Denotation ~NV in ~NF has no value" */

/* G2-GET-FROM-ITEM */
Object g2_get_from_item(item,denotation_sequence)
    Object item, denotation_sequence;
{
    Object denotation_or_error, top_of_stack, message_1;
    Object evaluation_value_or_error, definition_error_or_inner_item_index;
    Object sequence;

    x_note_fn_call(191,59);
    denotation_or_error = 
	    denotation_sequence_gt_denotation(denotation_sequence);
    reclaim_evaluation_value(denotation_sequence);
    if (SIMPLE_VECTOR_P(denotation_or_error) && 
	    EQ(ISVREF(denotation_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_4,
		make_default_text_string_for_access_error(denotation_or_error));
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	evaluation_value_or_error = get_denoted_evaluation_value(item,
		denotation_or_error);
	if (SIMPLE_VECTOR_P(evaluation_value_or_error) && 
		EQ(ISVREF(evaluation_value_or_error,(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    reclaim_managed_simple_vector(denotation_or_error);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_5,
		    make_default_text_string_for_access_error(evaluation_value_or_error));
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if ( !TRUEP(evaluation_value_or_error)) {
	    definition_error_or_inner_item_index = 
		    check_denotation_well_defined(item,denotation_or_error);
	    if (SIMPLE_VECTOR_P(definition_error_or_inner_item_index) && 
		    EQ(ISVREF(definition_error_or_inner_item_index,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_access_error_g2_struct)) {
		reclaim_managed_simple_vector(denotation_or_error);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_5,
			make_default_text_string_for_access_error(definition_error_or_inner_item_index));
		return raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else if ( !TRUEP(Current_system_rpc_icp_socket_qm)) {
		sequence = denotation_gt_denotation_sequence(1,
			denotation_or_error);
		reclaim_managed_simple_vector(denotation_or_error);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,sequence,item);
		return raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else {
		reclaim_managed_simple_vector(denotation_or_error);
		return VALUES_1(evaluation_value_or_error);
	    }
	}
	else {
	    reclaim_managed_simple_vector(denotation_or_error);
	    return VALUES_1(evaluation_value_or_error);
	}
    }
}

/* G2-GET-FROM-ITEM-MULTIPLE */
Object g2_get_from_item_multiple(item,denotation_sequences)
    Object item, denotation_sequences;
{
    Object gensymed_symbol, held_vector, denotation_sequence, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(191,60);
    gensymed_symbol = denotation_sequences;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    denotation_sequence = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
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
    denotation_sequence = validated_elt;
    ab_loopvar__2 = eval_cons_1(g2_get_from_item(item,
	    FIXNUMP(denotation_sequence) || denotation_sequence && 
	    SYMBOLP(denotation_sequence) ? denotation_sequence : 
	    copy_evaluation_value_1(denotation_sequence)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    temp = allocate_evaluation_sequence(temp);
    reclaim_evaluation_value(denotation_sequences);
    return VALUES_1(temp);
}

/* G2-GET-FROM-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_get_from_item_system_rpc_internal(gensymed_symbol,item,
	    denotation_evaluation_value)
    Object gensymed_symbol, item, denotation_evaluation_value;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,61);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_from_item(item,denotation_evaluation_value);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object list_constant_2;     /* # */

static Object string_constant_7;   /* "denotation-sequences argument ~NV must be a sequence of sequences" */

/* G2-GET-FROM-ITEM-MULTIPLE-SYSTEM-RPC-INTERNAL */
Object g2_get_from_item_multiple_system_rpc_internal(gensymed_symbol,item,
	    denotation_sequences)
    Object gensymed_symbol, item, denotation_sequences;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, top_of_stack;
    Object message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,62);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    if ( !TRUEP(type_specification_type_p(denotation_sequences,
		    list_constant_2))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_7,denotation_sequences);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_get_from_item_multiple(item,denotation_sequences);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-CONCLUDE-IN-ITEM */
Object g2_conclude_in_item(item,denotation_sequence,new_value)
    Object item, denotation_sequence, new_value;
{
    Object denotation_or_error, top_of_stack, message_1, error_qm;

    x_note_fn_call(191,63);
    denotation_or_error = 
	    denotation_sequence_gt_denotation(denotation_sequence);
    reclaim_evaluation_value(denotation_sequence);
    if (SIMPLE_VECTOR_P(denotation_or_error) && 
	    EQ(ISVREF(denotation_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct)) {
	if ( !(FIXNUMP(new_value) || SYMBOLP(new_value) || 
		SIMPLE_VECTOR_P(new_value)))
	    reclaim_if_evaluation_value_1(new_value);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_5,
		make_default_text_string_for_access_error(denotation_or_error));
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	error_qm = conclude_attribute_evaluation_value(item,
		denotation_or_error,new_value,T);
	reclaim_managed_simple_vector(denotation_or_error);
	if (SIMPLE_VECTOR_P(error_qm) && EQ(ISVREF(error_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_5,
		    make_default_text_string_for_access_error(error_qm));
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	return VALUES_1(Evaluation_true_value);
    }
}

/* G2-CONCLUDE-IN-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_conclude_in_item_system_rpc_internal(gensymed_symbol,item,
	    denotation_sequence,new_value)
    Object gensymed_symbol, item, denotation_sequence, new_value;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,64);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_conclude_in_item(item,denotation_sequence,new_value);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qsubscription_handle;  /* subscription-handle */

static Object Qinitial_value;      /* initial-value */

/* G2-SUBSCRIBE-TO-ITEM */
Object g2_subscribe_to_item(item,denotation_sequence,callback,user_data,
	    allow_batched_update_ev)
    Object item, denotation_sequence, callback, user_data;
    Object allow_batched_update_ev;
{
    Object denotation_or_error, top_of_stack, message_1, temp, rpc_qm;
    Object representation_or_error, initial_subscription_value_or_error;
    Object subscription_handle, gensymed_symbol, temp_1, item_or_value, x2;
    Object svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(191,65);
    evaluation_truth_value_is_true_p(allow_batched_update_ev);
    if ( !(EQ(allow_batched_update_ev,Evaluation_true_value) || 
	    EQ(allow_batched_update_ev,Evaluation_false_value)))
	reclaim_eval_cons_1(allow_batched_update_ev);
    denotation_or_error = 
	    denotation_sequence_gt_denotation(denotation_sequence);
    reclaim_evaluation_value(denotation_sequence);
    if (SIMPLE_VECTOR_P(denotation_or_error) && 
	    EQ(ISVREF(denotation_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct)) {
	if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
		SIMPLE_VECTOR_P(user_data)))
	    reclaim_if_evaluation_value_1(user_data);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_5,
		make_default_text_string_for_access_error(denotation_or_error));
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	temp = Current_system_rpc_icp_socket_qm;
	if (temp);
	else {
	    rpc_qm = 
		    find_remote_procedure_call_for_code_body_invocation(Current_computation_instance);
	    temp = rpc_qm ? ISVREF(rpc_qm,(SI_Long)24L) : Qnil;
	}
	representation_or_error = represent_item_internal(temp,item,
		denotation_or_error,callback,user_data);
	if (SIMPLE_VECTOR_P(representation_or_error) && 
		EQ(ISVREF(representation_or_error,(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    reclaim_managed_simple_vector(denotation_or_error);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_5,
		    make_default_text_string_for_access_error(representation_or_error));
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    initial_subscription_value_or_error = 
		    get_denoted_evaluation_value(item,denotation_or_error);
	    if (SIMPLE_VECTOR_P(initial_subscription_value_or_error) && 
		    EQ(ISVREF(initial_subscription_value_or_error,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_access_error_g2_struct)) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_5,
			make_default_text_string_for_access_error(initial_subscription_value_or_error));
		return raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else {
		subscription_handle = 
			store_callback_representation(representation_or_error);
		gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L 
			+ (SI_Long)1L));
		gensymed_symbol_1 = (SI_Long)0L;
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset);
		    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
			    Qsubscription_handle;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)1L)) = Qsubscription_handle;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = subscription_handle;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_1 = temp_2 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = subscription_handle;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    svref_new_value = temp_2 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qinitial_value;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)3L)) = Qinitial_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = initial_subscription_value_or_error;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_1 = temp_2 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = initial_subscription_value_or_error;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    svref_new_value = temp_2 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
		}
		return eval_cons_1(gensymed_symbol,Qab_structure);
	    }
	}
    }
}

/* G2-SUBSCRIBE-TO-ITEM-MULTIPLE */
Object g2_subscribe_to_item_multiple(item,denotation_sequences,callback,
	    user_data,allow_batched_update)
    Object item, denotation_sequences, callback, user_data;
    Object allow_batched_update;
{
    Object gensymed_symbol, held_vector, denotation_sequence, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt, temp, temp_1;
    SI_Long next_index, length_1;

    x_note_fn_call(191,66);
    gensymed_symbol = denotation_sequences;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    denotation_sequence = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
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
    denotation_sequence = validated_elt;
    temp = FIXNUMP(denotation_sequence) || denotation_sequence && 
	    SYMBOLP(denotation_sequence) ? denotation_sequence : 
	    copy_evaluation_value_1(denotation_sequence);
    temp_1 = FIXNUMP(user_data) || user_data && SYMBOLP(user_data) || 
	    SIMPLE_VECTOR_P(user_data) ? user_data : 
	    copy_if_evaluation_value_1(user_data);
    ab_loopvar__2 = eval_cons_1(g2_subscribe_to_item(item,temp,callback,
	    temp_1,FIXNUMP(allow_batched_update) || allow_batched_update 
	    && SYMBOLP(allow_batched_update) ? allow_batched_update : 
	    copy_evaluation_value_1(allow_batched_update)),Nil);
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
    temp_1 = allocate_evaluation_sequence(temp_1);
    reclaim_evaluation_value(denotation_sequences);
    if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
	    SIMPLE_VECTOR_P(user_data)))
	reclaim_if_evaluation_value_1(user_data);
    reclaim_evaluation_value(allow_batched_update);
    return VALUES_1(temp_1);
}

/* G2-SUBSCRIBE-TO-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_subscribe_to_item_system_rpc_internal(gensymed_symbol,item,
	    denotation_sequence,callback,user_data,allow_batched_update)
    Object gensymed_symbol, item, denotation_sequence, callback, user_data;
    Object allow_batched_update;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,67);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_subscribe_to_item(item,denotation_sequence,
		    callback,user_data,allow_batched_update);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SUBSCRIBE-TO-ITEM-MULTIPLE-SYSTEM-RPC-INTERNAL */
Object g2_subscribe_to_item_multiple_system_rpc_internal(gensymed_symbol,
	    item,denotation_sequences,callback,user_data,allow_batched_update)
    Object gensymed_symbol, item, denotation_sequences, callback, user_data;
    Object allow_batched_update;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, top_of_stack;
    Object message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,68);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    if ( !TRUEP(type_specification_type_p(denotation_sequences,
		    list_constant_2))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_7,denotation_sequences);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_subscribe_to_item_multiple(item,
		    denotation_sequences,callback,user_data,
		    allow_batched_update);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* GET-REPRESENTATION-FROM-SUBSCRIPTION-HANDLE */
Object get_representation_from_subscription_handle(handle)
    Object handle;
{
    x_note_fn_call(191,69);
    if ( !FIXNUM_MINUSP(handle))
	return representation_handle_gethash(handle);
    else
	return VALUES_1(Nil);
}

/* G2-UNSUBSCRIBE-TO-ITEM */
Object g2_unsubscribe_to_item(subscription_index)
    Object subscription_index;
{
    Object representation_qm;

    x_note_fn_call(191,70);
    representation_qm = 
	    get_representation_from_subscription_handle(subscription_index);
    if (representation_qm)
	delete_representation(1,representation_qm);
    return VALUES_1(Nil);
}

/* G2-UNSUBSCRIBE-TO-ITEM-MULTIPLE */
Object g2_unsubscribe_to_item_multiple(sequence_of_indices)
    Object sequence_of_indices;
{
    Object gensymed_symbol, held_vector, index_1, elt_1, validated_elt;
    SI_Long next_index, length_1;

    x_note_fn_call(191,71);
    gensymed_symbol = sequence_of_indices;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    index_1 = Nil;
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
    index_1 = validated_elt;
    g2_unsubscribe_to_item(index_1);
    goto next_loop;
  end_loop:;
    reclaim_evaluation_sequence(sequence_of_indices);
    return VALUES_1(Nil);
}

/* G2-UNSUBSCRIBE-TO-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_unsubscribe_to_item_system_rpc_internal(gensymed_symbol,
	    subscription_handle)
    Object gensymed_symbol, subscription_handle;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,72);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_unsubscribe_to_item(subscription_handle);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object list_constant_3;     /* # */

static Object string_constant_8;   /* "handle-sequence argument ~NV must be a sequence of integers" */

/* G2-UNSUBSCRIBE-TO-ITEM-MULTIPLE-SYSTEM-RPC-INTERNAL */
Object g2_unsubscribe_to_item_multiple_system_rpc_internal(gensymed_symbol,
	    subscription_handle_sequence)
    Object gensymed_symbol, subscription_handle_sequence;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(191,73);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    if ( 
		    !TRUEP(type_specification_type_p(subscription_handle_sequence,
		    list_constant_3))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_8,subscription_handle_sequence);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    gensymed_symbol_1 = 
		    g2_unsubscribe_to_item_multiple(subscription_handle_sequence);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SUBSCRIBE-TO-ITEM-ATTRIBUTES */
Object g2_subscribe_to_item_attributes(item,attr_spec,callback,user_data)
    Object item, attr_spec, callback, user_data;
{
    Object return_val, evaluation_structure, temp, evaluation_sequence;
    Object seq_to_return, gensymed_symbol, held_vector, struct_1;
    Object ab_loop_iter_flag_, elt_1, validated_elt, svref_arg_1;
    Object item_or_value, x2, svref_new_value;
    SI_Long next_index, length_1, i, gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(191,74);
    return_val = subscribe_to_item_attributes_body(item,attr_spec,callback,
	    user_data);
    if (CONSP(return_val) && EQ(M_CDR(return_val),Qab_structure)) {
	evaluation_structure = return_val;
	temp = structure_slot_1(M_CAR(evaluation_structure),
		Qsubscription_handle,Nil);
	reclaim_evaluation_structure(return_val);
	return VALUES_1(temp);
    }
    else if (CONSP(return_val) && EQ(M_CDR(return_val),Qsequence)) {
	evaluation_sequence = return_val;
	seq_to_return = 
		allocate_empty_evaluation_sequence(FIXNUM_SUB1(ISVREF(M_CAR(return_val),
		(SI_Long)1L)));
	gensymed_symbol = evaluation_sequence;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	struct_1 = Nil;
	i = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
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
	struct_1 = validated_elt;
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	gensymed_symbol = M_CAR(seq_to_return);
	gensymed_symbol_1 = i + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(M_CAR(seq_to_return),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_1 = M_CAR(seq_to_return);
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    item_or_value = structure_slot_1(M_CAR(struct_1),
		    Qsubscription_handle,Nil);
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    item_or_value = structure_slot_1(M_CAR(struct_1),
		    Qsubscription_handle,Nil);
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
	temp = seq_to_return;
	reclaim_evaluation_sequence(return_val);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(FIX((SI_Long)-1L));
}

static Object string_constant_9;   /* "The attribute-specification * is not allowed." */

static Object list_constant_4;     /* # */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_10;  /* "The attribute-specification ~NV must be a sequence of symbols." */

static Object string_constant_11;  /* "The attribute-specification ~NV must not contain the symbol *." */

static Object string_constant_12;  /* "The attribute-specification ~NV must be a symbol or a seqeuence ~
				    *           of symbols."
				    */

/* SUBSCRIBE-TO-ITEM-ATTRIBUTES-BODY */
Object subscribe_to_item_attributes_body(item,attr_spec,callback,user_data)
    Object item, attr_spec, callback, user_data;
{
    Object evaluation_symbol, top_of_stack, message_1, gensymed_symbol, temp_1;
    Object item_or_value, x2, svref_new_value, temp_3, evaluation_sequence;
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object problem_p, held_vector, attr_name, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, new_sequence_contents, seq;
    Object ab_loop_list_;
    SI_Long gensymed_symbol_1, temp, bv16_length, aref_new_value, length_1;
    SI_Long next_index, length_2;
    char temp_2;
    Declare_special(7);

    x_note_fn_call(191,75);
    if (attr_spec && SYMBOLP(attr_spec)) {
	evaluation_symbol = attr_spec;
	if (EQ(evaluation_symbol,Qstar)) {
	    if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
		    SIMPLE_VECTOR_P(user_data)))
		reclaim_if_evaluation_value_1(user_data);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_9);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,temp) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,temp) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qattribute;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qattribute;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qname;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qname;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = EQ(evaluation_symbol,Qall) ? Qstar : 
		    evaluation_symbol;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = EQ(evaluation_symbol,Qall) ? Qstar : 
		    evaluation_symbol;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp_3 = 
		allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
		Qab_structure),Nil));
	return g2_subscribe_to_item(item,temp_3,callback,user_data,
		Evaluation_false_value);
    }
    else if (CONSP(attr_spec) && EQ(M_CDR(attr_spec),Qsequence)) {
	evaluation_sequence = attr_spec;
	if ( !TRUEP(type_specification_type_p(evaluation_sequence,
		list_constant_4))) {
	    if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
		    SIMPLE_VECTOR_P(user_data)))
		reclaim_if_evaluation_value_1(user_data);
	    top_of_stack = Cached_top_of_stack;
	    text_string = Nil;
	    snapshots = Nil;
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
		  temp = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		  temp = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
			  tformat(2,string_constant_10,attr_spec);
			  reclaim_evaluation_sequence(attr_spec);
			  text_string = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		snapshots = Snapshots_of_related_blocks;
		Snapshots_of_related_blocks = Nil;
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	    message_1 = make_error_text(text_string,snapshots);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	problem_p = Nil;
	gensymed_symbol = attr_spec;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_2 = (SI_Long)0L;
	attr_name = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_2)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	attr_name = validated_elt;
	if ( !SYMBOLP(attr_name) || EQ(attr_name,Qstar)) {
	    problem_p = T;
	    goto end_loop;
	}
	else {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,temp) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		temp = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,temp) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qattribute;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qattribute;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qname;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qname;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = attr_name;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = attr_name;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    ab_loopvar__2 = 
		    eval_cons_1(allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
		    Qab_structure),Nil)),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	new_sequence_contents = ab_loopvar_;
	goto end_1;
	new_sequence_contents = Qnil;
      end_1:;
	if (problem_p) {
	    seq = Nil;
	    ab_loop_list_ = new_sequence_contents;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    seq = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    reclaim_evaluation_sequence(seq);
	    goto next_loop_1;
	  end_loop_1:;
	    reclaim_eval_list_1(new_sequence_contents);
	    if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
		    SIMPLE_VECTOR_P(user_data)))
		reclaim_if_evaluation_value_1(user_data);
	    top_of_stack = Cached_top_of_stack;
	    text_string = Nil;
	    snapshots = Nil;
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
		  temp = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		  temp = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
			  tformat(2,string_constant_11,attr_spec);
			  reclaim_evaluation_sequence(attr_spec);
			  text_string = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		snapshots = Snapshots_of_related_blocks;
		Snapshots_of_related_blocks = Nil;
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	    message_1 = make_error_text(text_string,snapshots);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	temp_3 = allocate_evaluation_sequence(new_sequence_contents);
	return g2_subscribe_to_item_multiple(item,temp_3,callback,
		user_data,Evaluation_false_value);
    }
    else {
	if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
		SIMPLE_VECTOR_P(user_data)))
	    reclaim_if_evaluation_value_1(user_data);
	top_of_stack = Cached_top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	      temp = bv16_length - (SI_Long)2L;
	      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	      temp = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
		      tformat(2,string_constant_12,attr_spec);
		      reclaim_evaluation_value(attr_spec);
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string,snapshots);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

/* G2-SUBSCRIBE-TO-ITEM-COLOR-PATTERN-CHANGE */
Object g2_subscribe_to_item_color_pattern_change(item,callback,user_data)
    Object item, callback, user_data;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    Object return_val;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(191,76);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qitem_color_pattern_change;
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
	item_or_value = Qitem_color_pattern_change;
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
    temp_2 = 
	    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
	    Qab_structure),Nil));
    return_val = g2_subscribe_to_item(item,temp_2,callback,user_data,
	    Evaluation_false_value);
    temp_2 = structure_slot_1(M_CAR(return_val),Qsubscription_handle,Nil);
    reclaim_evaluation_structure(return_val);
    return VALUES_1(temp_2);
}

/* G2-SUBSCRIBE-TO-CUSTOM-EVENT */
Object g2_subscribe_to_custom_event(item,custom_event_name,callback,user_data)
    Object item, custom_event_name, callback, user_data;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    Object return_val;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(191,77);
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qcustom_event;
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
	item_or_value = Qcustom_event;
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
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qcustom_event_name;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qcustom_event_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = custom_event_name;
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
	item_or_value = custom_event_name;
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
    temp_2 = 
	    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
	    Qab_structure),Nil));
    return_val = g2_subscribe_to_item(item,temp_2,callback,user_data,
	    Evaluation_false_value);
    temp_2 = structure_slot_1(M_CAR(return_val),Qsubscription_handle,Nil);
    reclaim_evaluation_structure(return_val);
    return VALUES_1(temp_2);
}

/* G2-SEND-NOTIFICATION-TO-ITEM */
Object g2_send_notification_to_item(item,event,info)
    Object item, event, info;
{
    Object temp;

    x_note_fn_call(191,78);
    temp = update_subscriptions_for_custom_event(item,event,info);
    if ( !(FIXNUMP(info) || SYMBOLP(info) || SIMPLE_VECTOR_P(info)))
	reclaim_if_evaluation_value_1(info);
    return VALUES_1(temp);
}

/* G2-SUBSCRIBE-TO-ITEM-EVENT */
Object g2_subscribe_to_item_event(item,item_event_name,callback,user_data)
    Object item, item_event_name, callback, user_data;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    Object return_val;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(191,79);
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qitem_event;
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
	item_or_value = Qitem_event;
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
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_event_name;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qitem_event_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = item_event_name;
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
	item_or_value = item_event_name;
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
    temp_2 = 
	    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
	    Qab_structure),Nil));
    return_val = g2_subscribe_to_item(item,temp_2,callback,user_data,
	    Evaluation_false_value);
    temp_2 = structure_slot_1(M_CAR(return_val),Qsubscription_handle,Nil);
    reclaim_evaluation_structure(return_val);
    return VALUES_1(temp_2);
}

/* SEND-NOTIFICATION-TO-ITEM-INTERNAL */
Object send_notification_to_item_internal(item,event)
    Object item, event;
{
    x_note_fn_call(191,80);
    update_subscriptions_for_item_event(item,event);
    return VALUES_1(Nil);
}

/* G2-SUBSCRIBE-TO-ADD-ITEM-TO-WORKSPACE */
Object g2_subscribe_to_add_item_to_workspace(workspace,callback,user_data)
    Object workspace, callback, user_data;
{
    x_note_fn_call(191,81);
    return subscribe_to_add_or_remove_item_from_workspace(workspace,
	    callback,user_data,Qadd_item_to_workspace);
}

/* G2-SUBSCRIBE-TO-REMOVE-ITEM-FROM-WORKSPACE */
Object g2_subscribe_to_remove_item_from_workspace(workspace,callback,user_data)
    Object workspace, callback, user_data;
{
    x_note_fn_call(191,82);
    return subscribe_to_add_or_remove_item_from_workspace(workspace,
	    callback,user_data,Qremove_item_from_workspace);
}

/* SUBSCRIBE-TO-ADD-OR-REMOVE-ITEM-FROM-WORKSPACE */
Object subscribe_to_add_or_remove_item_from_workspace(workspace,callback,
	    user_data,denotation_name)
    Object workspace, callback, user_data, denotation_name;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    Object return_val;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(191,83);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = denotation_name;
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
	item_or_value = denotation_name;
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
    temp_2 = 
	    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
	    Qab_structure),Nil));
    return_val = g2_subscribe_to_item(workspace,temp_2,callback,user_data,
	    Evaluation_false_value);
    temp_2 = structure_slot_1(M_CAR(return_val),Qsubscription_handle,Nil);
    reclaim_evaluation_structure(return_val);
    return VALUES_1(temp_2);
}

/* G2-SUBSCRIBE-TO-VARIABLE-OR-PARAMETER-VALUE */
Object g2_subscribe_to_variable_or_parameter_value(variable_or_parameter,
	    callback,user_data)
    Object variable_or_parameter, callback, user_data;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    Object return_val;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(191,84);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qvariable_value;
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
	item_or_value = Qvariable_value;
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
    temp_2 = 
	    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
	    Qab_structure),Nil));
    return_val = g2_subscribe_to_item(variable_or_parameter,temp_2,
	    callback,user_data,Evaluation_false_value);
    temp_2 = structure_slot_1(M_CAR(return_val),Qsubscription_handle,Nil);
    reclaim_evaluation_structure(return_val);
    return VALUES_1(temp_2);
}

static Object string_constant_13;  /* "~NV is not a valid subscription handle." */

static Object Qsubscribed_item;    /* subscribed-item */

static Object Qsubscribed_callback;  /* subscribed-callback */

static Object Qsubscription_denotation;  /* subscription-denotation */

static Object Qsubscription_user_data;  /* subscription-user-data */

/* G2-GET-SUBSCRIPTION-HANDLE-INFO */
Object g2_get_subscription_handle_info(handle)
    Object handle;
{
    Object representation_qm, top_of_stack, message_1, thing;
    Object subscribed_callback, gensymed_symbol, temp, item_or_value, x2;
    Object svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(191,85);
    representation_qm = get_representation_from_subscription_handle(handle);
    if ( !TRUEP(representation_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_13,
		handle);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	thing = ISVREF(representation_qm,(SI_Long)10L);
	subscribed_callback = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + 
		(SI_Long)1L));
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
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qsubscribed_item;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qsubscribed_item;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(representation_qm,(SI_Long)9L);
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(representation_qm,(SI_Long)9L);
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qsubscribed_callback;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qsubscribed_callback;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = subscribed_callback;
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = subscribed_callback;
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsubscription_denotation;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)5L)) = Qsubscription_denotation;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = denotation_gt_denotation_sequence(2,
		    ISVREF(representation_qm,(SI_Long)13L),T);
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = denotation_gt_denotation_sequence(2,
		    ISVREF(representation_qm,(SI_Long)13L),T);
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qsubscription_user_data;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)7L)) = Qsubscription_user_data;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    thing = ISVREF(representation_qm,(SI_Long)14L);
	    item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		    SIMPLE_VECTOR_P(thing) ? thing : 
		    copy_if_evaluation_value_1(thing);
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    thing = ISVREF(representation_qm,(SI_Long)14L);
	    item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		    SIMPLE_VECTOR_P(thing) ? thing : 
		    copy_if_evaluation_value_1(thing);
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	}
	return eval_cons_1(gensymed_symbol,Qab_structure);
    }
}

/* G2-GET-SUBSCRIPTION-HANDLES-FOR-ITEM */
Object g2_get_subscription_handles_for_item(item)
    Object item;
{
    Object representation, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(191,86);
    representation = Nil;
    ab_loop_list_ = ISVREF(item,(SI_Long)9L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qitem_representation,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(representation,(SI_Long)1L),
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
    if (temp) {
	ab_loopvar__2 = eval_cons_1(ISVREF(representation,(SI_Long)12L),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return allocate_evaluation_sequence(temp_1);
}

static Object Qdenotation_type_validator;  /* denotation-type-validator */

static Object Qtruth_value;        /* truth-value */

/* GET-DENOTED-EVALUATION-VALUE */
Object get_denoted_evaluation_value(item,denotation)
    Object item, denotation;
{
    Object end_index, all_user_visible_attributes, result_list;
    Object name_description, ab_loop_list_, name, temp, sub_denotation_1, root;
    Object cache, index_1, next_root_or_error_string, temp_1, gensymed_symbol;
    Object result_1, value, car_1, cdr_1, managed_value, x2;
    char temp_2;

    x_note_fn_call(191,87);
    if (denotation_ends_in_wildcard_p(denotation)) {
	end_index = denotation_end_index(denotation);
	if (IFIX(end_index) == (SI_Long)0L) {
	    all_user_visible_attributes = 
		    get_list_of_all_user_visible_attributes(ISVREF(item,
		    (SI_Long)1L));
	    result_list = Qnil;
	    name_description = Nil;
	    ab_loop_list_ = all_user_visible_attributes;
	    name = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name_description = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    name = M_CAR(name_description);
	    if ( !TRUEP(exclude_from_wildcard_denotation_p(name))) {
		result_list = eval_cons_1(name,result_list);
		temp = get_attribute_description_evaluation_value(item,
			M_CDR(name_description));
		result_list = eval_cons_1(temp,result_list);
	    }
	    goto next_loop;
	  end_loop:
	    reclaim_eval_alist(all_user_visible_attributes);
	    temp = nreverse(result_list);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    temp = allocate_evaluation_structure(temp);
	}
	else {
	    sub_denotation_1 = sub_denotation(3,denotation,
		    FIX((SI_Long)0L),end_index);
	    temp = get_denoted_evaluation_value(item,sub_denotation_1);
	    reclaim_managed_simple_vector(sub_denotation_1);
	}
    }
    else {
	root = item;
	cache = make_item_access_cache();
	end_index = denotation_end_index(denotation);
	index_1 = FIX((SI_Long)0L);
	next_root_or_error_string = Nil;
      next_loop_1:
	if (Debug_conclude_p) {
	    temp = root;
	    temp_1 = index_1;
	    gensymed_symbol = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
	    format((SI_Long)5L,T,"root = ~s index=~s validator=~s~%",temp,
		    temp_1,
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qdenotation_type_validator));
	}
	gensymed_symbol = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qdenotation_type_validator);
	next_root_or_error_string = FUNCALL_5(temp,cache,root,denotation,
		index_1,Nil);
	if (SIMPLE_VECTOR_P(next_root_or_error_string) && 
		EQ(ISVREF(next_root_or_error_string,(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    delete_item_access_cache(cache);
	    temp = next_root_or_error_string;
	    goto end_2;
	}
	else if (FIXNUM_EQ(index_1,end_index)) {
	    result_1 = FIXNUMP(next_root_or_error_string) || 
		    next_root_or_error_string && 
		    SYMBOLP(next_root_or_error_string) || 
		    SIMPLE_VECTOR_P(next_root_or_error_string) ? 
		    next_root_or_error_string : 
		    copy_if_evaluation_value_1(next_root_or_error_string);
	    delete_item_access_cache(cache);
	    if (CONSP(result_1) && EQ(M_CDR(result_1),Qtruth_value))
		temp = result_1;
	    else {
		value = result_1;
		if (CONSP(value)) {
		    car_1 = M_CAR(value);
		    cdr_1 = M_CDR(value);
		    if (CONSP(cdr_1)) {
			temp = M_CAR(cdr_1);
			temp_2 = SYMBOLP(temp);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_2 = temp_2 ? slot_value_number_p(car_1) || 
			    text_string_p(car_1) || STRINGP(car_1) : 
			    TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    managed_value = M_CAR(value);
		    if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(value))),
			    Qtruth_value)) {
			if (FIXNUM_EQ(managed_value,Truth))
			    temp = Evaluation_true_value;
			else if (FIXNUM_EQ(managed_value,Falsity))
			    temp = Evaluation_false_value;
			else
			    temp = eval_cons_1(managed_value,Qtruth_value);
		    }
		    else
			temp = FIXNUMP(managed_value) || 
				SYMBOLP(managed_value) ? managed_value : 
				copy_evaluation_value_1(managed_value);
		}
		else {
		    if (SIMPLE_VECTOR_P(value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2)
			temp = serve_item_p(value) ? value : Nil;
		    else
			temp = value;
		}
	    }
	    goto end_2;
	}
	else
	    root = next_root_or_error_string;
	index_1 = FIXNUM_ADD(index_1,ISVREF(Denotation_size_vector,
		IFIX(ISVREF(denotation,IFIX(index_1)))));
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_2:;
    }
    return VALUES_1(temp);
}

static Object Qab_gensym;          /* gensym */

/* CONCLUDE-ATTRIBUTE-EVALUATION-VALUE */
Object conclude_attribute_evaluation_value(item,denotation,new_value,mutate_p)
    Object item, denotation, new_value, mutate_p;
{
    Object current_conclude_innermost_frame, current_conclude_frame_list;
    Object current_conclude_innermost_item_index, cache;
    Object place_or_error_text_qm, gensymed_symbol, list_1;
    Object class_subscriptions, matching_subscriptions;
    Object matching_representations, subscription, ab_loop_list_;
    Object representation, represented_frame, match_p, access_error_qm, temp;
    Object representation_and_frame, frame, temp_1, svref_arg_2;
    Declare_special(3);

    x_note_fn_call(191,88);
    current_conclude_innermost_frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_conclude_innermost_frame,Qcurrent_conclude_innermost_frame,current_conclude_innermost_frame,
	    2);
      current_conclude_frame_list = Qnil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_conclude_frame_list,Qcurrent_conclude_frame_list,current_conclude_frame_list,
	      1);
	current_conclude_innermost_item_index = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_conclude_innermost_item_index,Qcurrent_conclude_innermost_item_index,current_conclude_innermost_item_index,
		0);
	  cache = make_item_access_cache();
	  place_or_error_text_qm = Nil;
	  place_or_error_text_qm = validate_denotation(cache,item,denotation);
	  if (Debug_conclude_p)
	      format((SI_Long)5L,T,
		      "~%Place or Error: ~s ~% f-list=~s~% inner-frame=~s~%",
		      place_or_error_text_qm,Current_conclude_frame_list,
		      Current_conclude_innermost_frame);
	  if ( !(SIMPLE_VECTOR_P(place_or_error_text_qm) && 
		  EQ(ISVREF(place_or_error_text_qm,(SI_Long)0L),
		  Qg2_defstruct_structure_name_access_error_g2_struct))) {
	      gensymed_symbol = 
		      ISVREF(ISVREF(Current_conclude_innermost_frame,
		      (SI_Long)1L),(SI_Long)1L);
	      list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
	    next_loop:
	      if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		      Current_kb_specific_property_list_property_name))
		  goto end_loop;
	      list_1 = M_CDR(M_CDR(list_1));
	      goto next_loop;
	    end_loop:
	      list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	    next_loop_1:
	      if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		      Class_subscriptions_kbprop))
		  goto end_loop_1;
	      list_1 = M_CDR(M_CDR(list_1));
	      goto next_loop_1;
	    end_loop_1:
	      class_subscriptions = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	      matching_subscriptions = class_subscriptions ? 
		      match_subscriptions(class_subscriptions,denotation,
		      Current_conclude_innermost_item_index) : Nil;
	      matching_representations = Qnil;
	      if (Debug_conclude_p)
		  format((SI_Long)3L,T,"matching-subscriptions=~s~%",
			  matching_subscriptions);
	      subscription = Nil;
	      ab_loop_list_ = matching_subscriptions;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      subscription = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      representation = ISVREF(subscription,(SI_Long)3L);
	      represented_frame = ISVREF(representation,(SI_Long)9L);
	      match_p = representation_represents_item_p(cache,
		      represented_frame,ISVREF(subscription,(SI_Long)1L),
		      ISVREF(subscription,(SI_Long)2L),
		      Current_conclude_innermost_frame);
	      if (Debug_conclude_p)
		  format((SI_Long)4L,T,"~s passes-filter=~s~%",
			  represented_frame,match_p);
	      if (match_p)
		  matching_representations = 
			  gensym_cons_1(gensym_cons_1(representation,
			  represented_frame),matching_representations);
	      goto next_loop_2;
	    end_loop_2:;
	      if (mutate_p) {
		  access_error_qm = 
			  mutate_denoted_item_part(Current_conclude_innermost_frame,
			  denotation,Current_conclude_innermost_item_index,
			  new_value);
		  if (SIMPLE_VECTOR_P(access_error_qm) && 
			  EQ(ISVREF(access_error_qm,(SI_Long)0L),
			  Qg2_defstruct_structure_name_access_error_g2_struct))
		      temp = access_error_qm;
		  else {
		      representation_and_frame = Nil;
		      ab_loop_list_ = matching_representations;
		      representation = Nil;
		      frame = Nil;
		    next_loop_3:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_3;
		      representation_and_frame = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      representation = M_CAR(representation_and_frame);
		      frame = M_CDR(representation_and_frame);
		      if (Nil)
			  update_representation_with_denotation(representation,
				  frame,denotation);
		      inline_note_reclaim_cons(representation_and_frame,
			      Qab_gensym);
		      if (ISVREF(Available_gensym_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_1 = 
				  ISVREF(Available_gensym_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp_1) = representation_and_frame;
			  temp_1 = Available_gensym_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = representation_and_frame;
		      }
		      else {
			  temp_1 = Available_gensym_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = representation_and_frame;
			  temp_1 = Available_gensym_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = representation_and_frame;
		      }
		      M_CDR(representation_and_frame) = Nil;
		      goto next_loop_3;
		    end_loop_3:;
		      reclaim_gensym_list_1(matching_representations);
		      temp = Nil;
		  }
		  reclaim_gensym_list_1(Current_conclude_frame_list);
		  delete_item_access_cache(cache);
	      }
	      else
		  temp = Nil;
	  }
	  else {
	      reclaim_gensym_list_1(Current_conclude_frame_list);
	      delete_item_access_cache(cache);
	      temp = place_or_error_text_qm;
	  }
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* GATHER-AFFECTED-REPRESENTATIONS */
Object gather_affected_representations(cache,matching_subscriptions,
	    mutated_frame)
    Object cache, matching_subscriptions, mutated_frame;
{
    Object matches, subscription, ab_loop_list_, match_p;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__1, ab_loop_it_;
    char temp;

    x_note_fn_call(191,89);
    matches = Qnil;
    subscription = Nil;
    ab_loop_list_ = matching_subscriptions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subscription = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    match_p = representation_represents_item_p(cache,
	    ISVREF(ISVREF(subscription,(SI_Long)3L),(SI_Long)9L),
	    ISVREF(subscription,(SI_Long)1L),ISVREF(subscription,
	    (SI_Long)2L),mutated_frame);
    if (match_p) {
	gensym_modify_macro_using_test_arg_1 = ISVREF(subscription,
		(SI_Long)3L);
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = matches;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__1 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	x_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	matches = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(matches);
}

/* VALIDATE-DENOTATION */
Object validate_denotation(cache,root,denotation)
    Object cache, root, denotation;
{
    Object end_index, index_1, next_root_or_error_string, temp, temp_1;
    Object gensymed_symbol, x2;
    char temp_2;

    x_note_fn_call(191,90);
    end_index = denotation_end_index(denotation);
    index_1 = FIX((SI_Long)0L);
    next_root_or_error_string = Nil;
  next_loop:
    if (Debug_conclude_p) {
	temp = root;
	temp_1 = index_1;
	gensymed_symbol = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
	format((SI_Long)5L,T,"root = ~s index=~s validator=~s~%",temp,
		temp_1,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qdenotation_type_validator));
    }
    gensymed_symbol = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qdenotation_type_validator);
    next_root_or_error_string = FUNCALL_5(temp,cache,root,denotation,
	    index_1,T);
    if (SIMPLE_VECTOR_P(root) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(root)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(root,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(root,(SI_Long)1L);
	temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	Current_conclude_innermost_item_index = index_1;
	Current_conclude_frame_list = gensym_cons_1(root,
		Current_conclude_frame_list);
	Current_conclude_innermost_frame = root;
    }
    if (SIMPLE_VECTOR_P(next_root_or_error_string) && 
	    EQ(ISVREF(next_root_or_error_string,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct)) {
	temp = next_root_or_error_string;
	goto end_1;
    }
    else if (FIXNUM_EQ(index_1,end_index)) {
	temp = root;
	goto end_1;
    }
    else
	root = next_root_or_error_string;
    index_1 = FIXNUM_ADD(index_1,ISVREF(Denotation_size_vector,
	    IFIX(ISVREF(denotation,IFIX(index_1)))));
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* REPRESENTATION-REPRESENTS-ITEM-P */
Object representation_represents_item_p(cache,root,denotation,end_index,
	    end_item)
    Object cache, root, denotation, end_index, end_item;
{
    Object index_1, temp, temp_1, gensymed_symbol, next_root_or_error;

    x_note_fn_call(191,91);
    index_1 = FIX((SI_Long)0L);
  next_loop:
    if (Debug_conclude_p) {
	temp = root;
	temp_1 = index_1;
	gensymed_symbol = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
	format((SI_Long)6L,T,
		"resfilter root = ~s index=~s end=~s validator=~s~%",temp,
		temp_1,end_index,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qdenotation_type_validator));
    }
    if (FIXNUM_EQ(index_1,end_index)) {
	temp = EQ(root,end_item) ? T : Nil;
	goto end_1;
    }
    else {
	gensymed_symbol = ISVREF(denotation,IFIX(FIXNUM_ADD1(index_1)));
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qdenotation_type_validator);
	next_root_or_error = FUNCALL_5(temp,cache,root,denotation,index_1,Nil);
	if (SIMPLE_VECTOR_P(next_root_or_error) && 
		EQ(ISVREF(next_root_or_error,(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    temp = Nil;
	    goto end_1;
	}
	else
	    root = next_root_or_error;
    }
    index_1 = FIXNUM_ADD(index_1,ISVREF(Denotation_size_vector,
	    IFIX(ISVREF(denotation,IFIX(index_1)))));
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GATHER-MATCHING-SUBSCRIPTIONS */
Object gather_matching_subscriptions(class_1,denotation,index_1)
    Object class_1, denotation, index_1;
{
    Object subscriptions_qm, result_1, temp;

    x_note_fn_call(191,92);
    subscriptions_qm = lookup_kb_specific_property_value(class_1,
	    Class_subscriptions_kbprop);
    if (subscriptions_qm) {
	result_1 = match_subscriptions(subscriptions_qm,denotation,index_1);
	temp = result_1;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* MATCH-SUBSCRIPTIONS */
Object match_subscriptions(subscriptions,denotation,index_1)
    Object subscriptions, denotation, index_1;
{
    Object result_1, subscription, ab_loop_list_;

    x_note_fn_call(191,93);
    result_1 = Qnil;
    if (denotation_element_specific_p(denotation,index_1)) {
	subscription = Nil;
	ab_loop_list_ = ISVREF(subscriptions,(SI_Long)1L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subscription = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (denotation_tails_match_p(ISVREF(subscription,(SI_Long)1L),
		ISVREF(subscription,(SI_Long)2L),denotation,index_1))
	    result_1 = gensym_cons_1(subscription,result_1);
	goto next_loop;
      end_loop:;
    }
    subscription = Nil;
    ab_loop_list_ = ISVREF(subscriptions,(SI_Long)2L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    subscription = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (denotation_tails_match_p(ISVREF(subscription,(SI_Long)1L),
	    ISVREF(subscription,(SI_Long)2L),denotation,index_1))
	result_1 = gensym_cons_1(subscription,result_1);
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(result_1);
}

/* DENOTATION-TAILS-MATCH-P */
Object denotation_tails_match_p(subscription_denotation,
	    subscription_start_index,conclude_denotation,conclude_start_index)
    Object subscription_denotation, subscription_start_index;
    Object conclude_denotation, conclude_start_index;
{
    Object subscription_end_index, conclude_end_index, subscription_index;
    Object conclude_index, subscription_denotation_code;
    Object conclude_denotation_code, temp, subscription_denotation_type;
    Object match_p, subscription_attribute_name;

    x_note_fn_call(191,94);
    subscription_end_index = 
	    SIMPLE_ARRAY_ANY_1_LENGTH(subscription_denotation);
    conclude_end_index = SIMPLE_ARRAY_ANY_1_LENGTH(conclude_denotation);
    subscription_index = subscription_start_index;
    conclude_index = conclude_start_index;
    subscription_denotation_code = Nil;
    conclude_denotation_code = Nil;
  next_loop:
    subscription_denotation_code = FIXNUM_LT(subscription_index,
	    subscription_end_index) ? ISVREF(subscription_denotation,
	    IFIX(subscription_index)) : Qnil;
    conclude_denotation_code = FIXNUM_LT(conclude_index,
	    conclude_end_index) ? ISVREF(conclude_denotation,
	    IFIX(conclude_index)) : Qnil;
    if (Debug_conclude_p)
	format((SI_Long)8L,T,
		"dtm-p loop si ~s sei ~s sdc ~s ci ~S cei~s cdc ~s~%",
		subscription_index,subscription_end_index,
		subscription_denotation_code,conclude_index,
		conclude_end_index,conclude_denotation_code);
    if (FIXNUM_EQ(subscription_index,subscription_end_index) && 
	    FIXNUM_EQ(conclude_index,conclude_end_index)) {
	temp = T;
	goto end_1;
    }
    else if (FIXNUM_EQ(subscription_index,subscription_end_index)) {
	temp = Nil;
	goto end_1;
    }
    else if (FIXNUM_EQ(conclude_index,conclude_end_index)) {
	temp = T;
	goto end_1;
    }
    else if (FIXNUM_EQ(subscription_denotation_code,
		conclude_denotation_code)) {
	if (denotation_element_equal_p(conclude_denotation,conclude_index,
		subscription_denotation,subscription_index)) {
	    if ( 
		    !TRUEP(denotation_element_specific_p(subscription_denotation,
		    subscription_index))) {
		if (Debug_conclude_p)
		    format((SI_Long)2L,T,"wildcard tail match~%");
		temp = T;
		goto end_1;
	    }
	}
	else {
	    temp = Nil;
	    goto end_1;
	}
    }
    else {
	subscription_denotation_type = ISVREF(subscription_denotation,
		IFIX(FIXNUM_ADD1(subscription_index)));
	match_p = Nil;
	temp = conclude_denotation_code;
	if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 1:
		if (Debug_conclude_p)
		    format((SI_Long)3L,T,"conc attr with sub ~S~%",
			    subscription_denotation_type);
		if (EQ(subscription_denotation_type,Qvirtual_attribute))
		    match_p = EQ(ISVREF(conclude_denotation,
			    IFIX(conclude_index) + (SI_Long)2L),
			    ISVREF(subscription_denotation,
			    IFIX(subscription_index) + (SI_Long)2L)) ? T : Nil;
		break;
	      case 4:
		if (Debug_conclude_p)
		    format((SI_Long)3L,T,"conc virt with sub ~S~%",
			    subscription_denotation_type);
		if (EQ(subscription_denotation_type,Qattribute)) {
		    subscription_attribute_name = 
			    ISVREF(subscription_denotation,
			    IFIX(subscription_index) + (SI_Long)2L);
		    temp = EQ(subscription_attribute_name,Qstar) ? ( 
			    !TRUEP(exclude_from_wildcard_denotation_p(ISVREF(conclude_denotation,
			    IFIX(conclude_index) + (SI_Long)2L))) ? T : 
			    Nil) : Qnil;
		    if (temp);
		    else
			temp = EQ(ISVREF(conclude_denotation,
				IFIX(conclude_index) + (SI_Long)2L),
				subscription_attribute_name) ? T : Nil;
		    match_p = temp;
		}
		break;
	      default:
		break;
	    }
	if ( !TRUEP(match_p)) {
	    temp = Nil;
	    goto end_1;
	}
    }
    subscription_index = FIXNUM_ADD(subscription_index,
	    ISVREF(Denotation_size_vector,
	    IFIX(ISVREF(subscription_denotation,IFIX(subscription_index)))));
    conclude_index = FIXNUM_ADD(conclude_index,
	    ISVREF(Denotation_size_vector,IFIX(ISVREF(conclude_denotation,
	    IFIX(conclude_index)))));
    goto next_loop;
  end_loop:
    error((SI_Long)1L,"internal error in denotation-tails-match-p");
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qexclude_from_wildcard_denotation;  /* exclude-from-wildcard-denotation */

/* EXCLUDE-FROM-WILDCARD-DENOTATION-P */
Object exclude_from_wildcard_denotation_p(attr_name)
    Object attr_name;
{
    Object virtual_attribute, features, feature, value, ab_loop_list_;
    Object ab_loop_it_, temp;

    x_note_fn_call(191,95);
    virtual_attribute = get_property_value_function(3,
	    get_symbol_properties_function(attr_name),Qvirtual_attribute,Nil);
    if (virtual_attribute) {
	features = ISVREF(virtual_attribute,(SI_Long)4L);
	feature = Nil;
	value = Nil;
	ab_loop_list_ = features;
	ab_loop_it_ = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	feature = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	value = CAR(temp);
	ab_loop_it_ = EQ(Qexclude_from_wildcard_denotation,feature) ? 
		value : Qnil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant_14;  /* "More than one attribute of class ~a has ~a as a possible ~
				    *                  value.  The implied attributes feature cannot be used when ~
				    *                  this is the case. Attributes found so far are ~NS and ~NS."
				    */

/* IMPLIED-ATTRIBUTE-OF-CLASS? */
Object implied_attribute_of_class_qm(target_class,symbolic_value)
    Object target_class, symbolic_value;
{
    Object target_description, slot_description, target_class_inheritance_path;
    Object desired_unique_attribute_qm, desired_unique_class_qm, class_1;
    Object attribute, list_1, ab_loop_list_, ab_loop_desetq_, gensymed_symbol;
    Object temp_1;
    char temp;

    x_note_fn_call(191,96);
    target_description = 
	    lookup_global_or_kb_specific_property_value(target_class,
	    Class_description_gkbprop);
    slot_description = Nil;
    target_class_inheritance_path = ISVREF(target_description,(SI_Long)2L);
    desired_unique_attribute_qm = Nil;
    desired_unique_class_qm = Nil;
    class_1 = Nil;
    attribute = Nil;
    list_1 = INLINE_SYMBOL_PLIST(symbolic_value);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Attribute_value_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    ab_loop_desetq_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_1 = CAR(ab_loop_desetq_);
    attribute = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = target_class_inheritance_path;
  next_loop_3:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_3;
    if (EQ(M_CAR(gensymed_symbol),class_1)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop_3;
  end_loop_3:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	if (desired_unique_attribute_qm) {
	    temp_1 = 
		    get_slot_description_of_class_description_function(desired_unique_attribute_qm,
		    target_description,desired_unique_class_qm);
	    temp_1 = tformat_text_string(7,string_constant_14,target_class,
		    symbolic_value,temp_1,target_description,
		    get_slot_description_of_class_description_function(attribute,
		    target_description,class_1),target_description);
	    return VALUES_3(Nil,Nil,temp_1);
	}
	else {
	    desired_unique_attribute_qm = attribute;
	    slot_description = 
		    get_slot_description_of_class_description_function(desired_unique_attribute_qm,
		    target_description,class_1);
	    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
		temp_1 = ISVREF(slot_description,(SI_Long)3L);
		temp =  !EQ(temp_1,
			ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
			(SI_Long)2L),target_description,Nil),(SI_Long)3L));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		desired_unique_class_qm = class_1;
	}
    }
    goto next_loop_2;
  end_loop_2:
    return VALUES_3(desired_unique_attribute_qm,desired_unique_class_qm,Nil);
    return VALUES_1(Qnil);
}

/* GET-IMPLIED-ATTRIBUTE-PLACE */
Object get_implied_attribute_place(item,symbolic_value,top_of_stack)
    Object item, symbolic_value, top_of_stack;
{
    Object class_1, attribute_class_qm, attribute_qm, implied_place_qm;
    Object class_qm, error_qm, top_of_stack_1, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, x2, gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(191,97);
    class_1 = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    attribute_class_qm = Nil;
    attribute_qm = Nil;
    implied_place_qm = Nil;
    result = implied_attribute_of_class_qm(class_1,symbolic_value);
    MVS_3(result,attribute_qm,class_qm,error_qm);
    if (error_qm) {
	top_of_stack_1 = top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
		      twrite_general_string(error_qm);
		      reclaim_text_string(error_qm);
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string,snapshots);
	result = raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else
	result = VALUES_2(attribute_qm,class_qm);
    MVS_2(result,attribute_qm,attribute_class_qm);
    if (attribute_qm) {
	implied_place_qm = get_slot_value_function(item,attribute_qm,
		attribute_class_qm);
	if (SIMPLE_VECTOR_P(implied_place_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(implied_place_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(implied_place_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(implied_place_qm,(SI_Long)1L);
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
		    IFIX(ISVREF(Variable_or_parameter_class_description,
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
	temp_1 = (temp ? (SI_Long)0L != (IFIX(ISVREF(implied_place_qm,
		(SI_Long)5L)) & (SI_Long)1L) : TRUEP(Nil)) ? 
		implied_place_qm : item;
    }
    else
	temp_1 = item;
    return VALUES_1(temp_1);
}

/* GET-IMPLIED-ATTRIBUTE-PLACE-OR-ERROR-DESCRIPTION */
Object get_implied_attribute_place_or_error_description(item,symbolic_value)
    Object item, symbolic_value;
{
    Object class_1, attribute_qm, attribute_class_qm, error_qm, temp;
    Object implied_place_qm, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Object result;

    x_note_fn_call(191,98);
    class_1 = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    result = implied_attribute_of_class_qm(class_1,symbolic_value);
    MVS_3(result,attribute_qm,attribute_class_qm,error_qm);
    if (error_qm)
	temp = error_qm;
    else if (attribute_qm) {
	implied_place_qm = get_slot_value_function(item,attribute_qm,
		attribute_class_qm);
	if (SIMPLE_VECTOR_P(implied_place_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(implied_place_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(implied_place_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(implied_place_qm,(SI_Long)1L);
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
		    IFIX(ISVREF(Variable_or_parameter_class_description,
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
	temp = (temp_1 ? (SI_Long)0L != (IFIX(ISVREF(implied_place_qm,
		(SI_Long)5L)) & (SI_Long)1L) : TRUEP(Nil)) ? 
		implied_place_qm : item;
    }
    else
	temp = item;
    return VALUES_1(temp);
}

static Object Qitem_not_editable_conclude_error;  /* item-not-editable-conclude-error */

static Object Qmessage;            /* message */

static Object string_constant_15;  /* "Cannot edit ~NF, because ~A.  See the saving-parameters." */

static Object Qg2_defstruct_structure_name_slot_description_g2_struct;  /* g2-defstruct-structure-name::slot-description-g2-struct */

/* MUTATE-DENOTED-ITEM-PART */
Object mutate_denoted_item_part(item,denotation,index_1,new_value)
    Object item, denotation, index_1, new_value;
{
    Object reason_not_editable_qm, temp, denotation_code, slot_description;
    Object virtual_attribute;

    x_note_fn_call(191,99);
    reason_not_editable_qm = 
	    reason_permanent_items_module_is_not_editable(1,item);
    if (reason_not_editable_qm) {
	temp = tformat_text_string(2,string_constant_1,item);
	return make_access_error_1(Qitem_not_editable_conclude_error,
		gensym_list_4(Qitem,temp,Qmessage,tformat_text_string(3,
		string_constant_15,item,reason_not_editable_qm)));
    }
    denotation_code = ISVREF(denotation,IFIX(index_1));
    temp = denotation_code;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 1:
	    if (SIMPLE_VECTOR_P(Current_conclude_innermost_attribute_description) 
		    && 
		    EQ(ISVREF(Current_conclude_innermost_attribute_description,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_slot_description_g2_struct)) {
		slot_description = 
			Current_conclude_innermost_attribute_description;
		temp = ISVREF(slot_description,(SI_Long)8L) ? 
			mutate_user_attribute(item,slot_description,
			denotation,index_1,new_value) : 
			mutate_system_attribute(item,slot_description,
			denotation,index_1,new_value);
	    }
	    else {
		virtual_attribute = 
			Current_conclude_innermost_attribute_description;
		temp = mutate_virtual_attribute(item,virtual_attribute,
			denotation,index_1,new_value);
	    }
	    break;
	  case 2:
	    temp = Nil;
	    break;
	  case 3:
	    temp = error((SI_Long)1L,"NYI");
	    break;
	  case 4:
	    virtual_attribute = 
		    Current_conclude_innermost_attribute_description;
	    temp = mutate_virtual_attribute(item,virtual_attribute,
		    denotation,index_1,new_value);
	    break;
	  case 5:
	    temp = mutate_variable_value(item,denotation,index_1,new_value);
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_1(temp);
}

static Object Qfloat_array;        /* float-array */

static Object Qtype_mismatch;      /* type-mismatch */

static Object string_constant_16;  /* "The attribute ~a of ~NF is read-only." */

static Object Qexpecting_structure_or_sequence_inside_attribute;  /* expecting-structure-or-sequence-inside-attribute */

/* MUTATE-VIRTUAL-ATTRIBUTE */
Object mutate_virtual_attribute(item,virtual_attribute,denotation,index_1,
	    new_value)
    Object item, virtual_attribute, denotation, index_1, new_value;
{
    Object end_index, type_specification, gensymed_symbol, gensymed_symbol_1;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2, value_to_conclude_qm, block, name, setter_qm;
    Object getter_qm, evaluation_value;
    Object replaced_partial_evaluation_value_or_error;
    double aref_new_value;

    x_note_fn_call(191,100);
    end_index = denotation_end_index(denotation);
    type_specification = ISVREF(virtual_attribute,(SI_Long)3L);
    if (FIXNUM_EQ(end_index,index_1)) {
	gensymed_symbol = type_specification;
	gensymed_symbol_1 = new_value;
	if (EQ(gensymed_symbol,Qfloat) && FIXNUMP(gensymed_symbol_1)) {
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
	    aref_new_value = (double)IFIX(gensymed_symbol_1);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_2 = new_float;
	    value_to_conclude_qm = temp_2;
	}
	else if (type_specification_type_p(gensymed_symbol_1,gensymed_symbol))
	    value_to_conclude_qm = gensymed_symbol_1;
	else
	    value_to_conclude_qm = make_access_error_1(Qtype_mismatch,Nil);
	if (SIMPLE_VECTOR_P(value_to_conclude_qm) && 
		EQ(ISVREF(value_to_conclude_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    temp_2 = ISVREF(virtual_attribute,(SI_Long)1L);
	    temp_2 = make_access_error_1(Qtype_mismatch,
		    gensym_list_4(Qattribute,temp_2,Qvalue,
		    tformat_text_string(2,string_constant_1,new_value)));
	}
	else {
	    block = item;
	    name = ISVREF(virtual_attribute,(SI_Long)1L);
	    new_value = value_to_conclude_qm;
	    setter_qm = ISVREF(virtual_attribute,(SI_Long)7L);
	    temp_2 = setter_qm ? inline_funcall_2(setter_qm,block,
		    new_value) : tformat_text_string(3,string_constant_16,
		    name,block);
	}
    }
    else {
	getter_qm = ISVREF(virtual_attribute,(SI_Long)6L);
	evaluation_value = getter_qm ? inline_funcall_1(getter_qm,item) : 
		No_component_value;
	if (aggregate_evaluation_value_p(evaluation_value)) {
	    replaced_partial_evaluation_value_or_error = 
		    substitute_denoted_evaluation_value_part(evaluation_value,
		    denotation,FIXNUM_ADD(index_1,
		    ISVREF(Denotation_size_vector,IFIX(ISVREF(denotation,
		    IFIX(index_1))))),end_index,new_value,T);
	    if (SIMPLE_VECTOR_P(replaced_partial_evaluation_value_or_error) 
		    && 
		    EQ(ISVREF(replaced_partial_evaluation_value_or_error,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_access_error_g2_struct))
		temp_2 = replaced_partial_evaluation_value_or_error;
	    else {
		if ( !(FIXNUMP(replaced_partial_evaluation_value_or_error) 
			|| 
			SYMBOLP(replaced_partial_evaluation_value_or_error) 
			|| 
			SIMPLE_VECTOR_P(replaced_partial_evaluation_value_or_error)))
		    reclaim_if_evaluation_value_1(replaced_partial_evaluation_value_or_error);
		if (type_specification_type_p(evaluation_value,
			type_specification)) {
		    block = item;
		    name = ISVREF(virtual_attribute,(SI_Long)1L);
		    new_value = evaluation_value;
		    setter_qm = ISVREF(virtual_attribute,(SI_Long)7L);
		    temp_2 = setter_qm ? inline_funcall_2(setter_qm,block,
			    new_value) : tformat_text_string(3,
			    string_constant_16,name,block);
		}
		else {
		    temp_2 = ISVREF(virtual_attribute,(SI_Long)1L);
		    temp_2 = make_access_error_1(Qtype_mismatch,
			    gensym_list_4(Qattribute,temp_2,Qvalue,
			    tformat_text_string(2,string_constant_1,
			    evaluation_value)));
		}
	    }
	}
	else {
	    temp_2 = 
		    make_access_error_1(Qexpecting_structure_or_sequence_inside_attribute,
		    gensym_list_2(Qvalue,tformat_text_string(2,
		    string_constant_1,evaluation_value)));
	    if ( !(FIXNUMP(evaluation_value) || SYMBOLP(evaluation_value) 
		    || SIMPLE_VECTOR_P(evaluation_value)))
		reclaim_if_evaluation_value_1(evaluation_value);
	}
    }
    return VALUES_1(temp_2);
}

/* SET-SYSTEM-ATTRIBUTE-EVALUATION-VALUE */
Object set_system_attribute_evaluation_value(item,slot_description,new_value)
    Object item, slot_description, new_value;
{
    Object evaluator_info, parse_result_maker, current_edit_state, svref_arg_1;
    Object parse_result_or_bad_phrase, error_string_qm, temp;
    Object class_description, temp_1;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(191,101);
    evaluator_info = ISVREF(slot_description,(SI_Long)10L);
    if (evaluator_info);
    else
	evaluator_info = cache_evaluator_slot_info(slot_description);
    parse_result_maker = ISVREF(evaluator_info,(SI_Long)2L);
    current_edit_state = make_edit_state_1();
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      svref_arg_1 = Current_edit_state;
      SVREF(svref_arg_1,FIX((SI_Long)3L)) = item;
      result = inline_funcall_4(parse_result_maker,new_value,item,
	      slot_description,Nil);
      MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
      if (EQ(parse_result_or_bad_phrase,Bad_phrase))
	  temp = error_string_qm;
      else {
	  temp = ISVREF(slot_description,(SI_Long)2L);
	  class_description = ISVREF(item,(SI_Long)1L);
	  if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	      temp_1 = ISVREF(slot_description,(SI_Long)3L);
	      temp_2 =  !EQ(temp_1,
		      ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		      (SI_Long)2L),class_description,Nil),(SI_Long)3L));
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  temp = simple_commit_parse_result(item,temp,temp_2 ? 
		  ISVREF(slot_description,(SI_Long)3L) : Nil,
		  slot_description,Nil,Nil,ISVREF(evaluator_info,
		  (SI_Long)1L),ISVREF(evaluator_info,(SI_Long)6L),
		  parse_result_or_bad_phrase,Nil,new_value);
      }
      goto end_attribute_export_conclude_context;
    end_attribute_export_conclude_context:
      reclaim_edit_state_1(Current_edit_state);
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qsystem_attribute_conclude_error;  /* system-attribute-conclude-error */

/* MUTATE-SYSTEM-ATTRIBUTE */
Object mutate_system_attribute(item,slot_description,denotation,index_1,
	    new_value)
    Object item, slot_description, denotation, index_1, new_value;
{
    Object end_index, error_string_qm, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, evaluation_value;
    Object replaced_partial_evaluation_value_or_error, temp;

    x_note_fn_call(191,102);
    end_index = denotation_end_index(denotation);
    if (FIXNUM_EQ(end_index,index_1)) {
	error_string_qm = set_system_attribute_evaluation_value(item,
		slot_description,new_value);
	if (error_string_qm) {
	    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qitem;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = tformat_text_string(2,string_constant_1,item);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qname;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = ISVREF(slot_description,(SI_Long)2L);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qvalue;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = tformat_text_string(2,string_constant_1,new_value);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qmessage;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = error_string_qm;
	    return make_access_error_1(Qsystem_attribute_conclude_error,
		    gensymed_symbol);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	evaluation_value = get_attribute_description_evaluation_value(item,
		slot_description);
	if (aggregate_evaluation_value_p(evaluation_value)) {
	    replaced_partial_evaluation_value_or_error = 
		    substitute_denoted_evaluation_value_part(evaluation_value,
		    denotation,FIXNUM_ADD(index_1,
		    ISVREF(Denotation_size_vector,IFIX(ISVREF(denotation,
		    IFIX(index_1))))),end_index,new_value,T);
	    if (SIMPLE_VECTOR_P(replaced_partial_evaluation_value_or_error) 
		    && 
		    EQ(ISVREF(replaced_partial_evaluation_value_or_error,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_access_error_g2_struct))
		return VALUES_1(replaced_partial_evaluation_value_or_error);
	    else {
		if ( !(FIXNUMP(replaced_partial_evaluation_value_or_error) 
			|| 
			SYMBOLP(replaced_partial_evaluation_value_or_error) 
			|| 
			SIMPLE_VECTOR_P(replaced_partial_evaluation_value_or_error)))
		    reclaim_if_evaluation_value_1(replaced_partial_evaluation_value_or_error);
		error_string_qm = 
			set_system_attribute_evaluation_value(item,
			slot_description,evaluation_value);
		if (error_string_qm) {
		    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
		    gensymed_symbol_1 = gensymed_symbol;
		    M_CAR(gensymed_symbol_1) = Qitem;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    car_new_value = tformat_text_string(2,
			    string_constant_1,item);
		    M_CAR(gensymed_symbol_1) = car_new_value;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = Qname;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    car_new_value = ISVREF(slot_description,(SI_Long)2L);
		    M_CAR(gensymed_symbol_1) = car_new_value;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = Qvalue;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    car_new_value = tformat_text_string(2,
			    string_constant_1,new_value);
		    M_CAR(gensymed_symbol_1) = car_new_value;
		    return make_access_error_1(Qsystem_attribute_conclude_error,
			    gensymed_symbol);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else {
	    temp = 
		    make_access_error_1(Qexpecting_structure_or_sequence_inside_attribute,
		    gensym_list_2(Qvalue,tformat_text_string(2,
		    string_constant_1,evaluation_value)));
	    if ( !(FIXNUMP(evaluation_value) || SYMBOLP(evaluation_value) 
		    || SIMPLE_VECTOR_P(evaluation_value)))
		reclaim_if_evaluation_value_1(evaluation_value);
	    return VALUES_1(temp);
	}
    }
}

static Object Qdatum;              /* datum */

static Object Qab_or;              /* or */

static Object list_constant_5;     /* # */

/* MUTATE-USER-ATTRIBUTE */
Object mutate_user_attribute(item,slot_description,denotation,index_1,
	    new_value)
    Object item, slot_description, denotation, index_1, new_value;
{
    Object end_index, gensymed_symbol, gensymed_symbol_1;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2, value_to_conclude_qm, type_specification;
    Object type_details, evaluation_value;
    Object replaced_partial_evaluation_value_or_error, new_whole_value;
    char temp_3;
    double aref_new_value;
    Object result;

    x_note_fn_call(191,103);
    end_index = denotation_end_index(denotation);
    if (FIXNUM_EQ(end_index,index_1)) {
	gensymed_symbol = ISVREF(slot_description,(SI_Long)5L);
	gensymed_symbol_1 = new_value;
	if (EQ(gensymed_symbol,Qfloat) && FIXNUMP(gensymed_symbol_1)) {
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
	    aref_new_value = (double)IFIX(gensymed_symbol_1);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_2 = new_float;
	    value_to_conclude_qm = temp_2;
	}
	else if (type_specification_type_p(gensymed_symbol_1,gensymed_symbol))
	    value_to_conclude_qm = gensymed_symbol_1;
	else
	    value_to_conclude_qm = make_access_error_1(Qtype_mismatch,Nil);
	if (SIMPLE_VECTOR_P(value_to_conclude_qm) && 
		EQ(ISVREF(value_to_conclude_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qitem;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = tformat_text_string(2,string_constant_1,item);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qname;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = ISVREF(slot_description,(SI_Long)2L);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qvalue;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = tformat_text_string(2,string_constant_1,new_value);
	    M_CAR(gensymed_symbol_1) = temp;
	    temp_2 = make_access_error_1(Qtype_mismatch,gensymed_symbol);
	}
	else if (CONSP(value_to_conclude_qm) && 
		EQ(M_CDR(value_to_conclude_qm),Qtruth_value)) {
	    change_slot_description_value_function(item,slot_description,
		    slot_value_list_2(M_CAR(value_to_conclude_qm),
		    Qtruth_value),Nil,Nil);
	    if ( !(EQ(value_to_conclude_qm,Evaluation_true_value) || 
		    EQ(value_to_conclude_qm,Evaluation_false_value)))
		reclaim_eval_cons_1(value_to_conclude_qm);
	    temp_2 = Nil;
	}
	else
	    temp_2 = change_slot_description_value_function(item,
		    slot_description,value_to_conclude_qm,Nil,Nil);
    }
    else {
	type_specification = ISVREF(slot_description,(SI_Long)5L);
	if (SYMBOLP(type_specification)) {
	    if (symbolic_type_specification_subtype_p(type_specification,
		    Qdatum)) {
		gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = Qitem;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp = tformat_text_string(2,string_constant_1,item);
		M_CAR(gensymed_symbol_1) = temp;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Qname;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp = ISVREF(slot_description,(SI_Long)2L);
		M_CAR(gensymed_symbol_1) = temp;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Qvalue;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp = tformat_text_string(2,string_constant_1,new_value);
		M_CAR(gensymed_symbol_1) = temp;
		temp_2 = make_access_error_1(Qtype_mismatch,gensymed_symbol);
	    }
	    else
		temp_2 = error((SI_Long)2L,
			"unknown type-specification for user attribute conclude ~s",
			type_specification);
	}
	else {
	    type_details = M_CDR(type_specification);
	    temp_2 = M_CAR(type_specification);
	    if (EQ(temp_2,Qab_or)) {
		if (EQ(M_CAR(type_details),Qitem_or_datum)) {
		    temp_2 = CADR(type_details);
		    temp_3 = EQUAL(temp_2,list_constant_5);
		}
		else
		    temp_3 = TRUEP(Nil);
		if ( !temp_3)
		    error((SI_Long)2L,
			    "unknown type-specification for user attribute conclude ~s",
			    type_specification);
	    }
	    else if (EQ(temp_2,Qab_structure) || EQ(temp_2,Qsequence));
	    else
		error((SI_Long)2L,
			"unknown type-specification for user attribute conclude ~s",
			type_specification);
	    evaluation_value = get_slot_description_value(item,
		    slot_description);
	    result = substitute_denoted_evaluation_value_part(evaluation_value,
		    denotation,FIXNUM_ADD(index_1,
		    ISVREF(Denotation_size_vector,IFIX(ISVREF(denotation,
		    IFIX(index_1))))),end_index,new_value,Nil);
	    MVS_2(result,replaced_partial_evaluation_value_or_error,
		    new_whole_value);
	    if (SIMPLE_VECTOR_P(replaced_partial_evaluation_value_or_error) 
		    && 
		    EQ(ISVREF(replaced_partial_evaluation_value_or_error,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_access_error_g2_struct))
		temp_2 = replaced_partial_evaluation_value_or_error;
	    else {
		if ( !(FIXNUMP(replaced_partial_evaluation_value_or_error) 
			|| 
			SYMBOLP(replaced_partial_evaluation_value_or_error) 
			|| 
			SIMPLE_VECTOR_P(replaced_partial_evaluation_value_or_error)))
		    reclaim_if_evaluation_value_1(replaced_partial_evaluation_value_or_error);
		temp_2 = change_slot_description_value_function(item,
			slot_description,FIXNUMP(new_whole_value) || 
			new_whole_value && SYMBOLP(new_whole_value) ? 
			new_whole_value : 
			copy_evaluation_value_1(new_whole_value),Nil,Nil);
	    }
	}
    }
    return VALUES_1(temp_2);
}

static Object Qexpecting_structure_inside_attribute;  /* expecting-structure-inside-attribute */

static Object Qexpecting_sequence_inside_attribute;  /* expecting-sequence-inside-attribute */

/* SUBSTITUTE-DENOTED-EVALUATION-VALUE-PART */
Object substitute_denoted_evaluation_value_part(evaluation_value,
	    denotation,index_1,end_index,part,unique_p)
    Object evaluation_value, denotation, index_1, end_index, part, unique_p;
{
    Object root, first_root, previous_root_is_structure_p, previous_root;
    Object previous_key, next_root, next_index, code, temp, gensymed_symbol;
    Object gensymed_symbol_2, svref_arg_1, temp_1, item_or_value, x2;
    Object svref_new_value, attribute_name, length_1, new_sequence, elt_index;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char mutable_p, temp_2;

    x_note_fn_call(191,104);
    root = evaluation_value;
    first_root = Nil;
    previous_root_is_structure_p = Nil;
    previous_root = Nil;
    previous_key = Nil;
    next_root = Nil;
    next_index = Nil;
    code = Nil;
  next_loop:
    next_index = FIXNUM_ADD(index_1,ISVREF(Denotation_size_vector,
	    IFIX(ISVREF(denotation,IFIX(index_1)))));
    code = ISVREF(denotation,IFIX(index_1));
    temp = code;
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 1:
	    if ( !(CONSP(root) && EQ(M_CDR(root),Qab_structure)))
		return make_access_error_1(Qexpecting_structure_inside_attribute,
			gensym_list_2(Qvalue,tformat_text_string(2,
			string_constant_1,root)));
	    if ( !TRUEP(unique_p)) {
		gensymed_symbol = M_CAR(root);
		gensymed_symbol_1 = (SI_Long)0L;
		mutable_p = (FIXNUM_LE(ISVREF(M_CAR(root),(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			IFIX(ISVREF(M_CAR(root),gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset))) : 
			IFIX(ISVREF(ISVREF(gensymed_symbol,
			(gensymed_symbol_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L))) 
			== (SI_Long)1L;
		if ( !mutable_p) {
		    gensymed_symbol = root;
		    gensymed_symbol = M_CAR(gensymed_symbol);
		    root = 
			    make_unique_evaluation_structure_copy_1(gensymed_symbol);
		}
		if (first_root) {
		    if ( !mutable_p) {
			if (previous_root_is_structure_p)
			    set_evaluation_structure_slot(previous_root,
				    previous_key,root);
			else {
			    gensymed_symbol = M_CAR(previous_root);
			    gensymed_symbol_2 = FIXNUM_ADD1(previous_key);
			    if (FIXNUM_LE(ISVREF(M_CAR(previous_root),
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				svref_arg_1 = M_CAR(previous_root);
				temp_1 = FIXNUM_ADD(gensymed_symbol_2,
					Managed_array_index_offset);
				item_or_value = root;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				svref_new_value = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(svref_arg_1,temp_1) = svref_new_value;
			    }
			    else {
				svref_arg_1 = ISVREF(gensymed_symbol,
					(IFIX(gensymed_symbol_2) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L);
				svref_arg_2 = IFIX(gensymed_symbol_2) & 
					(SI_Long)1023L;
				item_or_value = root;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_1 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				ISVREF(svref_arg_1,svref_arg_2) = temp_1;
			    }
			}
		    }
		}
		else
		    first_root = root;
	    }
	    attribute_name = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
	    next_root = estructure_slot(root,attribute_name,Nil);
	    if (FIXNUM_EQ(index_1,end_index)) {
		set_evaluation_structure_slot(root,attribute_name,part);
		return VALUES_2(next_root,first_root);
	    }
	    else {
		index_1 = next_index;
		if ( !TRUEP(unique_p)) {
		    previous_root = root;
		    previous_key = attribute_name;
		    previous_root_is_structure_p = T;
		}
		root = next_root;
	    }
	    break;
	  case 3:
	    if ( !(CONSP(root) && EQ(M_CDR(root),Qsequence)))
		return make_access_error_1(Qexpecting_sequence_inside_attribute,
			gensym_list_2(Qvalue,tformat_text_string(2,
			string_constant_1,root)));
	    if ( !TRUEP(unique_p)) {
		mutable_p = (FIXNUM_LE(ISVREF(M_CAR(evaluation_value),
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			IFIX(ISVREF(M_CAR(evaluation_value),(SI_Long)0L + 
			IFIX(Managed_array_index_offset))) : 
			IFIX(ISVREF(ISVREF(M_CAR(evaluation_value),
			(SI_Long)2L),(SI_Long)0L))) == (SI_Long)1L;
		if ( !mutable_p) {
		    length_1 = FIXNUM_SUB1(ISVREF(M_CAR(root),(SI_Long)1L));
		    new_sequence = 
			    allocate_empty_evaluation_sequence(length_1);
		    copy_evaluation_sequence_elements(root,
			    FIX((SI_Long)0L),length_1,new_sequence,
			    FIX((SI_Long)0L));
		    root = new_sequence;
		}
		if (first_root) {
		    if ( !mutable_p) {
			if (previous_root_is_structure_p)
			    set_evaluation_structure_slot(previous_root,
				    previous_key,root);
			else {
			    gensymed_symbol = M_CAR(previous_root);
			    gensymed_symbol_2 = FIXNUM_ADD1(previous_key);
			    if (FIXNUM_LE(ISVREF(M_CAR(previous_root),
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				svref_arg_1 = M_CAR(previous_root);
				temp_1 = FIXNUM_ADD(gensymed_symbol_2,
					Managed_array_index_offset);
				item_or_value = root;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				svref_new_value = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(svref_arg_1,temp_1) = svref_new_value;
			    }
			    else {
				svref_arg_1 = ISVREF(gensymed_symbol,
					(IFIX(gensymed_symbol_2) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L);
				svref_arg_2 = IFIX(gensymed_symbol_2) & 
					(SI_Long)1023L;
				item_or_value = root;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_1 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				ISVREF(svref_arg_1,svref_arg_2) = temp_1;
			    }
			}
		    }
		}
		else
		    first_root = root;
	    }
	    elt_index = ISVREF(denotation,IFIX(index_1) + (SI_Long)2L);
	    next_root = evaluation_sequence_aref(root,elt_index);
	    if (FIXNUM_EQ(index_1,end_index)) {
		gensymed_symbol = M_CAR(root);
		gensymed_symbol_2 = FIXNUM_ADD1(elt_index);
		if (FIXNUM_LE(ISVREF(M_CAR(root),(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_1 = M_CAR(root);
		    temp_1 = FIXNUM_ADD(gensymed_symbol_2,
			    Managed_array_index_offset);
		    item_or_value = part;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    svref_new_value = temp_2 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(svref_arg_1,temp_1) = svref_new_value;
		}
		else {
		    svref_arg_1 = ISVREF(gensymed_symbol,
			    (IFIX(gensymed_symbol_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = IFIX(gensymed_symbol_2) & (SI_Long)1023L;
		    item_or_value = part;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_1 = temp_2 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
		}
		return VALUES_2(next_root,first_root);
	    }
	    else {
		index_1 = next_index;
		if ( !TRUEP(unique_p)) {
		    previous_root = root;
		    previous_key = elt_index;
		    previous_root_is_structure_p = Nil;
		}
		root = next_root;
	    }
	    break;
	  default:
	    break;
	}
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qconclude_no_value_into_parameter;  /* conclude-no-value-into-parameter */

static Object Qparameter;          /* parameter */

static Object Qconclude_into_variable_error;  /* conclude-into-variable-error */

static Object Qexplanation;        /* explanation */

/* MUTATE-VARIABLE-VALUE */
Object mutate_variable_value(item,denotation,index_1,new_value)
    Object item, denotation, index_1, new_value;
{
    Object sub_class_bit_vector, temp_1, problem_description_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(191,105);
    if ( !TRUEP(new_value)) {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
    if (temp)
	return make_access_error_1(Qconclude_no_value_into_parameter,
		gensym_list_2(Qparameter,tformat(2,string_constant_3,item)));
    else if ( !TRUEP(new_value))
	return put_has_no_value(item);
    else {
	temp_1 = Nil;
	if (temp_1);
	else
	    temp_1 = Stack_expiration;
	problem_description_qm = put_current_evaluation_value(item,
		new_value,temp_1,Nil, ! !TRUEP(Nil) ? T : Nil);
	if (problem_description_qm)
	    return make_access_error_1(Qconclude_into_variable_error,
		    gensym_list_2(Qexplanation,problem_description_qm));
	else
	    return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_attribute_denotation, Qscratch_attribute_denotation);

/* MAKE-ATTRIBUTE-DENOTATION */
Object make_attribute_denotation(slot_name,class_qualifier_qm,permanent_p)
    Object slot_name, class_qualifier_qm, permanent_p;
{
    Object denotation, vector_1;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,106);
    length_1 = (SI_Long)4L;
    if (permanent_p)
	denotation = allocate_managed_simple_vector(FIX(length_1));
    else {
	denotation = Scratch_attribute_denotation;
	if (denotation);
	else {
	    Scratch_attribute_denotation = 
		    allocate_managed_simple_vector(FIX(length_1));
	    denotation = Scratch_attribute_denotation;
	}
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)1L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qattribute;
    svref_arg_2 = start_position + (SI_Long)2L;
    ISVREF(vector_1,svref_arg_2) = slot_name;
    svref_arg_2 = start_position + (SI_Long)3L;
    ISVREF(vector_1,svref_arg_2) = class_qualifier_qm;
    return VALUES_1(denotation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_virtual_attribute_denotation, Qscratch_virtual_attribute_denotation);

/* MAKE-VIRTUAL-ATTRIBUTE-DENOTATION */
Object make_virtual_attribute_denotation(virtual_attribute,permanent_p)
    Object virtual_attribute, permanent_p;
{
    Object denotation, vector_1, svref_new_value;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,107);
    length_1 = (SI_Long)3L;
    if (permanent_p)
	denotation = allocate_managed_simple_vector(FIX(length_1));
    else {
	denotation = Scratch_virtual_attribute_denotation;
	if (denotation);
	else {
	    Scratch_virtual_attribute_denotation = 
		    allocate_managed_simple_vector(FIX(length_1));
	    denotation = Scratch_virtual_attribute_denotation;
	}
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)4L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qvirtual_attribute;
    svref_arg_2 = start_position + (SI_Long)2L;
    svref_new_value = ISVREF(virtual_attribute,(SI_Long)1L);
    ISVREF(vector_1,svref_arg_2) = svref_new_value;
    return VALUES_1(denotation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_variable_value_denotation, Qscratch_variable_value_denotation);

/* MAKE-VARIABLE-VALUE-DENOTATION */
Object make_variable_value_denotation(permanent_p)
    Object permanent_p;
{
    Object denotation, vector_1;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,108);
    length_1 = (SI_Long)2L;
    if (permanent_p)
	denotation = allocate_managed_simple_vector(FIX(length_1));
    else {
	denotation = Scratch_variable_value_denotation;
	if (denotation);
	else {
	    Scratch_variable_value_denotation = 
		    allocate_managed_simple_vector(FIX(length_1));
	    denotation = Scratch_variable_value_denotation;
	}
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)5L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qvariable_value;
    return VALUES_1(denotation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_item_color_pattern_change_denotation, Qscratch_item_color_pattern_change_denotation);

/* MAKE-ITEM-COLOR-PATTERN-CHANGE-DENOTATION */
Object make_item_color_pattern_change_denotation()
{
    Object denotation, vector_1;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,109);
    length_1 = (SI_Long)2L;
    denotation = Scratch_item_color_pattern_change_denotation;
    if (denotation);
    else {
	Scratch_item_color_pattern_change_denotation = 
		allocate_managed_simple_vector(FIX(length_1));
	denotation = Scratch_item_color_pattern_change_denotation;
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)6L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qitem_color_pattern_change;
    return VALUES_1(denotation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_custom_event_denotation, Qscratch_custom_event_denotation);

/* MAKE-CUSTOM-EVENT-DENOTATION */
Object make_custom_event_denotation(event_name)
    Object event_name;
{
    Object denotation, vector_1;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,110);
    length_1 = (SI_Long)3L;
    denotation = Scratch_custom_event_denotation;
    if (denotation);
    else {
	Scratch_custom_event_denotation = 
		allocate_managed_simple_vector(FIX(length_1));
	denotation = Scratch_custom_event_denotation;
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)7L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qcustom_event;
    svref_arg_2 = start_position + (SI_Long)2L;
    ISVREF(vector_1,svref_arg_2) = event_name;
    return VALUES_1(denotation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_item_event_denotation, Qscratch_item_event_denotation);

/* MAKE-ITEM-EVENT-DENOTATION */
Object make_item_event_denotation(event_name)
    Object event_name;
{
    Object denotation, vector_1;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,111);
    length_1 = (SI_Long)3L;
    denotation = Scratch_item_event_denotation;
    if (denotation);
    else {
	Scratch_item_event_denotation = 
		allocate_managed_simple_vector(FIX(length_1));
	denotation = Scratch_item_event_denotation;
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)10L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qitem_event;
    svref_arg_2 = start_position + (SI_Long)2L;
    ISVREF(vector_1,svref_arg_2) = event_name;
    return VALUES_1(denotation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_add_item_to_workspace, Qscratch_add_item_to_workspace);

/* MAKE-ADD-ITEM-TO-WORKSPACE-DENOTATION */
Object make_add_item_to_workspace_denotation()
{
    Object denotation, vector_1;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,112);
    length_1 = (SI_Long)2L;
    denotation = Scratch_add_item_to_workspace;
    if (denotation);
    else {
	Scratch_add_item_to_workspace = 
		allocate_managed_simple_vector(FIX(length_1));
	denotation = Scratch_add_item_to_workspace;
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)8L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qadd_item_to_workspace;
    return VALUES_1(denotation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_remove_item_from_workspace, Qscratch_remove_item_from_workspace);

/* MAKE-REMOVE-ITEM-FROM-WORKSPACE-DENOTATION */
Object make_remove_item_from_workspace_denotation()
{
    Object denotation, vector_1;
    SI_Long length_1, start_position, svref_arg_2;

    x_note_fn_call(191,113);
    length_1 = (SI_Long)2L;
    denotation = Scratch_remove_item_from_workspace;
    if (denotation);
    else {
	Scratch_remove_item_from_workspace = 
		allocate_managed_simple_vector(FIX(length_1));
	denotation = Scratch_remove_item_from_workspace;
    }
    vector_1 = denotation;
    start_position = (SI_Long)0L;
    svref_arg_2 = start_position + (SI_Long)0L;
    ISVREF(vector_1,svref_arg_2) = FIX((SI_Long)9L);
    svref_arg_2 = start_position + (SI_Long)1L;
    ISVREF(vector_1,svref_arg_2) = Qremove_item_from_workspace;
    return VALUES_1(denotation);
}

void conclude_INIT()
{
    Object temp, reclaim_structure_for_item_access_cache_1, temp_1;
    Object gensymed_symbol;
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2_get_subscription_handles_for_item;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_get_subscription_handle_info;
    Object Qg2_subscribe_to_variable_or_parameter_value;
    Object Qg2_subscribe_to_remove_item_from_workspace;
    Object Qg2_subscribe_to_add_item_to_workspace, Qg2_subscribe_to_item_event;
    Object Qg2_send_notification_to_item, Qg2_subscribe_to_custom_event;
    Object Qg2_subscribe_to_item_color_pattern_change, list_constant_44;
    Object Qg2_subscribe_to_item_attributes;
    Object Qg2_unsubscribe_to_item_multiple_system_rpc_internal;
    Object list_constant_39, Qg2_unsubscribe_to_item_multiple;
    Object Qsystem_defined_rpc, list_constant_43, list_constant_42;
    Object list_constant_23, Qsubscription_handle_sequence;
    Object Qg2_unsubscribe_to_item_system_rpc_internal;
    Object Qg2_unsubscribe_to_item, list_constant_41, list_constant_40;
    Object Qg2_subscribe_to_item_multiple_system_rpc_internal;
    Object Qg2_subscribe_to_item_multiple, list_constant_20, list_constant_38;
    Object list_constant_37, list_constant_21, list_constant_15;
    Object list_constant_33, list_constant_32, list_constant_31;
    Object Qg2_subscribe_to_item_system_rpc_internal, Qg2_subscribe_to_item;
    Object list_constant_36, list_constant_35, list_constant_34;
    Object list_constant_26, list_constant_29, Qallow_batched_update;
    Object list_constant_30, Quser_data, list_constant_24, list_constant_8;
    Object Qg2_conclude_in_item_system_rpc_internal, Qg2_conclude_in_item;
    Object list_constant_28, list_constant_27, list_constant_25, Qnew_value;
    Object Qdenotation_sequence;
    Object Qg2_get_from_item_multiple_system_rpc_internal;
    Object Qg2_get_from_item_multiple, list_constant_22, Qdenotation_sequences;
    Object list_constant_6, Qg2_get_from_item_system_rpc_internal;
    Object Qg2_get_from_item, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_12, list_constant_16;
    Object Qdenotation_evaluation_value, Qg2_make_uuid;
    Object Qg2_get_item_with_uuid_system_rpc_internal, Qg2_get_item_with_uuid;
    Object list_constant_14, list_constant_13, Qtext, Quuid;
    Object Qg2_get_unique_named_item_system_rpc_internal;
    Object Qg2_get_unique_named_item, list_constant_11, list_constant_10;
    Object list_constant_9, Qitem_name, Qitem_class, list_constant_7;
    Object Qsubscription_callback_arg_types;
    Object Qitem_event_denotation_defined_check;
    Object Qitem_event_denotation_validator;
    Object Qremove_item_from_workspace_denotation_defined_check;
    Object Qremove_item_from_workspace_denotation_validator;
    Object Qadd_item_to_workspace_denotation_defined_check;
    Object Qadd_item_to_workspace_denotation_validator;
    Object Qcustom_event_denotation_defined_check;
    Object Qcustom_event_denotation_validator;
    Object Qitem_color_pattern_change_denotation_defined_check;
    Object Qitem_color_pattern_change_denotation_validator;
    Object Qvariable_value_denotation_defined_check;
    Object Qvariable_value_denotation_validator;
    Object Qvirtual_attribute_denotation_defined_check;
    Object Qvirtual_attribute_denotation_validator;
    Object Qelement_denotation_defined_check, Qelement_denotation_validator;
    Object Qaliased_attribute_denotation_defined_check, Qaliased_attribute;
    Object Qaliased_attribute_denotation_validator;
    Object Qattribute_denotation_defined_check, Qno_item;
    Object Qattribute_denotation_validator, Qitem_access_cache;
    Object Qreclaim_structure, Qoutstanding_item_access_cache_count;
    Object Qitem_access_cache_structure_memory_usage, Qutilities2;
    Object string_constant_18, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_17, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    XDeclare_area(1);

    x_note_fn_call(191,114);
    SET_PACKAGE("AB");
    Debug_conclude_p = Nil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_item_access_cache_g2_struct = 
	    STATIC_SYMBOL("ITEM-ACCESS-CACHE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qitem_access_cache = STATIC_SYMBOL("ITEM-ACCESS-CACHE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_item_access_cache_g2_struct,
	    Qitem_access_cache,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qitem_access_cache,
	    Qg2_defstruct_structure_name_item_access_cache_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_item_access_cache == UNBOUND)
	The_type_description_of_item_access_cache = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83jMy1n83jMy8n8k1l8n0000001l1n8y83-4gy0kpk0k0");
    temp = The_type_description_of_item_access_cache;
    The_type_description_of_item_access_cache = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_item_access_cache_g2_struct,
	    The_type_description_of_item_access_cache,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qitem_access_cache,
	    The_type_description_of_item_access_cache,
	    Qtype_description_of_type);
    Qoutstanding_item_access_cache_count = 
	    STATIC_SYMBOL("OUTSTANDING-ITEM-ACCESS-CACHE-COUNT",AB_package);
    Qitem_access_cache_structure_memory_usage = 
	    STATIC_SYMBOL("ITEM-ACCESS-CACHE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_18 = STATIC_STRING("1q83jMy8s83-b8y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_item_access_cache_count);
    push_optimized_constant(Qitem_access_cache_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_item_access_caches = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ITEM-ACCESS-CACHES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_item_access_caches,
	    Chain_of_available_item_access_caches);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_item_access_caches,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qitem_access_cache_count = STATIC_SYMBOL("ITEM-ACCESS-CACHE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qitem_access_cache_count,
	    Item_access_cache_count);
    record_system_variable(Qitem_access_cache_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_item_access_caches_vector == UNBOUND)
	Chain_of_available_item_access_caches_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qitem_access_cache_structure_memory_usage,
	    STATIC_FUNCTION(item_access_cache_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_item_access_cache_count,
	    STATIC_FUNCTION(outstanding_item_access_cache_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_item_access_cache_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_item_access_cache,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qitem_access_cache,
	    reclaim_structure_for_item_access_cache_1);
    Qdenotation_type_code = STATIC_SYMBOL("DENOTATION-TYPE-CODE",AB_package);
    Denotation_type_code_prop = Qdenotation_type_code;
    Qdenotation_type_size = STATIC_SYMBOL("DENOTATION-TYPE-SIZE",AB_package);
    Denotation_type_size_prop = Qdenotation_type_size;
    Qdenotation_type_validator = STATIC_SYMBOL("DENOTATION-TYPE-VALIDATOR",
	    AB_package);
    Denotation_type_validator_prop = Qdenotation_type_validator;
    Qdenotation_type_defined_check = 
	    STATIC_SYMBOL("DENOTATION-TYPE-DEFINED-CHECK",AB_package);
    Denotation_type_defined_check_prop = Qdenotation_type_defined_check;
    Qdenotation_type_wildcard_arg_index_qm = 
	    STATIC_SYMBOL("DENOTATION-TYPE-WILDCARD-ARG-INDEX\?",AB_package);
    Denotation_type_wildcard_arg_index_qm_prop = 
	    Qdenotation_type_wildcard_arg_index_qm;
    if (Denotation_size_vector == UNBOUND) {
	if (PUSH_AREA(Dynamic_area,0))
	    Denotation_size_vector = make_array(1,Maximum_denotation_types);
	POP_AREA(0);
    }
    if (Current_conclude_innermost_attribute_description == UNBOUND)
	Current_conclude_innermost_attribute_description = Nil;
    if (The_denotation_conversion_buffer == UNBOUND)
	The_denotation_conversion_buffer = Nil;
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qno_type_in_denotation_sequence_element_structure = 
	    STATIC_SYMBOL("NO-TYPE-IN-DENOTATION-SEQUENCE-ELEMENT-STRUCTURE",
	    AB_package);
    Qelement_structure = STATIC_SYMBOL("ELEMENT-STRUCTURE",AB_package);
    string_constant = STATIC_STRING("~NV");
    Qnon_structure_indenotation_sequence_element = 
	    STATIC_SYMBOL("NON-STRUCTURE-INDENOTATION-SEQUENCE-ELEMENT",
	    AB_package);
    Qindex = STATIC_SYMBOL("INDEX",AB_package);
    Qsequence_element = STATIC_SYMBOL("SEQUENCE-ELEMENT",AB_package);
    Qelement = STATIC_SYMBOL("ELEMENT",AB_package);
    Qno_index_for_element_denotation_element = 
	    STATIC_SYMBOL("NO-INDEX-FOR-ELEMENT-DENOTATION-ELEMENT",
	    AB_package);
    Qdenotation_element = STATIC_SYMBOL("DENOTATION-ELEMENT",AB_package);
    string_constant_1 = STATIC_STRING("~NA");
    Qstructure_attribute = STATIC_SYMBOL("STRUCTURE-ATTRIBUTE",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qclass_qualifier = STATIC_SYMBOL("CLASS-QUALIFIER",AB_package);
    Qno_name_for_attribute_denotation_element = 
	    STATIC_SYMBOL("NO-NAME-FOR-ATTRIBUTE-DENOTATION-ELEMENT",
	    AB_package);
    Qvariable_value = STATIC_SYMBOL("VARIABLE-VALUE",AB_package);
    Qitem_color_pattern_change = STATIC_SYMBOL("ITEM-COLOR-PATTERN-CHANGE",
	    AB_package);
    Qcustom_event = STATIC_SYMBOL("CUSTOM-EVENT",AB_package);
    Qcustom_event_name = STATIC_SYMBOL("CUSTOM-EVENT-NAME",AB_package);
    Qadd_item_to_workspace = STATIC_SYMBOL("ADD-ITEM-TO-WORKSPACE",AB_package);
    Qremove_item_from_workspace = 
	    STATIC_SYMBOL("REMOVE-ITEM-FROM-WORKSPACE",AB_package);
    Qitem_event = STATIC_SYMBOL("ITEM-EVENT",AB_package);
    Qitem_event_name = STATIC_SYMBOL("ITEM-EVENT-NAME",AB_package);
    Qunknown_denotation_element_type = 
	    STATIC_SYMBOL("UNKNOWN-DENOTATION-ELEMENT-TYPE",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    mutate_global_property(Qattribute,FIX((SI_Long)1L),Qdenotation_type_code);
    mutate_global_property(Qattribute,FIX((SI_Long)4L),Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)1L) = FIX((SI_Long)4L);
    mutate_global_property(Qattribute,
	    FIX(IFIX(Denotation_element_overhead_slot_count) + 
	    (SI_Long)0L),Qdenotation_type_wildcard_arg_index_qm);
    Qattribute_denotation_validator = 
	    STATIC_SYMBOL("ATTRIBUTE-DENOTATION-VALIDATOR",AB_package);
    mutate_global_property(Qattribute,Qattribute_denotation_validator,
	    Qdenotation_type_validator);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qundefined_attribute = STATIC_SYMBOL("UNDEFINED-ATTRIBUTE",AB_package);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    string_constant_2 = STATIC_STRING("~NQ");
    Qattribute_does_not_exist_in_structure = 
	    STATIC_SYMBOL("ATTRIBUTE-DOES-NOT-EXIST-IN-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qattribute_denotation_validator,
	    STATIC_FUNCTION(attribute_denotation_validator,NIL,FALSE,5,5));
    Qattribute_denotation_defined_check = 
	    STATIC_SYMBOL("ATTRIBUTE-DENOTATION-DEFINED-CHECK",AB_package);
    mutate_global_property(Qattribute,Qattribute_denotation_defined_check,
	    Qdenotation_type_defined_check);
    Qg2_defstruct_structure_name_access_error_g2_struct = 
	    STATIC_SYMBOL("ACCESS-ERROR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qambiguous_attribute_definition = 
	    STATIC_SYMBOL("AMBIGUOUS-ATTRIBUTE-DEFINITION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_5 = STATIC_CONS(Qno_item,Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_5);
    Qg2_defstruct_structure_name_virtual_attribute_g2_struct = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunexported_attribute = STATIC_SYMBOL("UNEXPORTED-ATTRIBUTE",AB_package);
    Qattribute_of_non_item = STATIC_SYMBOL("ATTRIBUTE-OF-NON-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qattribute_denotation_defined_check,
	    STATIC_FUNCTION(attribute_denotation_defined_check,NIL,FALSE,3,3));
    Qaliased_attribute = STATIC_SYMBOL("ALIASED-ATTRIBUTE",AB_package);
    mutate_global_property(Qaliased_attribute,FIX((SI_Long)2L),
	    Qdenotation_type_code);
    mutate_global_property(Qaliased_attribute,FIX((SI_Long)5L),
	    Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)2L) = FIX((SI_Long)5L);
    mutate_global_property(Qaliased_attribute,
	    FIX(IFIX(Denotation_element_overhead_slot_count) + 
	    (SI_Long)0L),Qdenotation_type_wildcard_arg_index_qm);
    Qaliased_attribute_denotation_validator = 
	    STATIC_SYMBOL("ALIASED-ATTRIBUTE-DENOTATION-VALIDATOR",AB_package);
    mutate_global_property(Qaliased_attribute,
	    Qaliased_attribute_denotation_validator,
	    Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qaliased_attribute_denotation_validator,
	    STATIC_FUNCTION(aliased_attribute_denotation_validator,NIL,
	    FALSE,5,5));
    Qaliased_attribute_denotation_defined_check = 
	    STATIC_SYMBOL("ALIASED-ATTRIBUTE-DENOTATION-DEFINED-CHECK",
	    AB_package);
    mutate_global_property(Qaliased_attribute,
	    Qaliased_attribute_denotation_defined_check,
	    Qdenotation_type_defined_check);
    SET_SYMBOL_FUNCTION(Qaliased_attribute_denotation_defined_check,
	    STATIC_FUNCTION(aliased_attribute_denotation_defined_check,NIL,
	    FALSE,3,3));
    mutate_global_property(Qelement,FIX((SI_Long)3L),Qdenotation_type_code);
    mutate_global_property(Qelement,FIX((SI_Long)3L),Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)3L) = FIX((SI_Long)3L);
    mutate_global_property(Qelement,
	    FIX(IFIX(Denotation_element_overhead_slot_count) + 
	    (SI_Long)0L),Qdenotation_type_wildcard_arg_index_qm);
    Qelement_denotation_validator = 
	    STATIC_SYMBOL("ELEMENT-DENOTATION-VALIDATOR",AB_package);
    mutate_global_property(Qelement,Qelement_denotation_validator,
	    Qdenotation_type_validator);
    Qnon_integer_index = STATIC_SYMBOL("NON-INTEGER-INDEX",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qelement_does_not_exist = STATIC_SYMBOL("ELEMENT-DOES-NOT-EXIST",
	    AB_package);
    string_constant_3 = STATIC_STRING("~NF");
    Qindex_out_of_range = STATIC_SYMBOL("INDEX-OUT-OF-RANGE",AB_package);
    Qlist_is_empty = STATIC_SYMBOL("LIST-IS-EMPTY",AB_package);
    Qelement_of_item_not_array_or_list = 
	    STATIC_SYMBOL("ELEMENT-OF-ITEM-NOT-ARRAY-OR-LIST",AB_package);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qelement_of_non_array_list_or_sequence = 
	    STATIC_SYMBOL("ELEMENT-OF-NON-ARRAY-LIST-OR-SEQUENCE",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qelement_denotation_validator,
	    STATIC_FUNCTION(element_denotation_validator,NIL,FALSE,5,5));
    Qelement_denotation_defined_check = 
	    STATIC_SYMBOL("ELEMENT-DENOTATION-DEFINED-CHECK",AB_package);
    mutate_global_property(Qelement,Qelement_denotation_defined_check,
	    Qdenotation_type_defined_check);
    Qdenotation_of_non_list_array_or_sequence = 
	    STATIC_SYMBOL("DENOTATION-OF-NON-LIST-ARRAY-OR-SEQUENCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qelement_denotation_defined_check,
	    STATIC_FUNCTION(element_denotation_defined_check,NIL,FALSE,3,3));
    Qlist_type = STATIC_SYMBOL("LIST-TYPE",AB_package);
    mutate_global_property(Qvirtual_attribute,FIX((SI_Long)4L),
	    Qdenotation_type_code);
    mutate_global_property(Qvirtual_attribute,FIX((SI_Long)3L),
	    Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)4L) = FIX((SI_Long)3L);
    mutate_global_property(Qvirtual_attribute,
	    FIX(IFIX(Denotation_element_overhead_slot_count) + 
	    (SI_Long)0L),Qdenotation_type_wildcard_arg_index_qm);
    Qvirtual_attribute_denotation_validator = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-DENOTATION-VALIDATOR",AB_package);
    mutate_global_property(Qvirtual_attribute,
	    Qvirtual_attribute_denotation_validator,
	    Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qvirtual_attribute_denotation_validator,
	    STATIC_FUNCTION(virtual_attribute_denotation_validator,NIL,
	    FALSE,5,5));
    Qvirtual_attribute_denotation_defined_check = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-DENOTATION-DEFINED-CHECK",
	    AB_package);
    mutate_global_property(Qvirtual_attribute,
	    Qvirtual_attribute_denotation_defined_check,
	    Qdenotation_type_defined_check);
    SET_SYMBOL_FUNCTION(Qvirtual_attribute_denotation_defined_check,
	    STATIC_FUNCTION(virtual_attribute_denotation_defined_check,NIL,
	    FALSE,3,3));
    mutate_global_property(Qvariable_value,FIX((SI_Long)5L),
	    Qdenotation_type_code);
    mutate_global_property(Qvariable_value,FIX((SI_Long)2L),
	    Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)5L) = FIX((SI_Long)2L);
    Qvariable_value_denotation_validator = 
	    STATIC_SYMBOL("VARIABLE-VALUE-DENOTATION-VALIDATOR",AB_package);
    mutate_global_property(Qvariable_value,
	    Qvariable_value_denotation_validator,Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qvariable_value_denotation_validator,
	    STATIC_FUNCTION(variable_value_denotation_validator,NIL,FALSE,
	    5,5));
    Qvariable_value_denotation_defined_check = 
	    STATIC_SYMBOL("VARIABLE-VALUE-DENOTATION-DEFINED-CHECK",
	    AB_package);
    mutate_global_property(Qvariable_value,
	    Qvariable_value_denotation_defined_check,
	    Qdenotation_type_defined_check);
    Qvariable_value_of_non_variable_or_parameter = 
	    STATIC_SYMBOL("VARIABLE-VALUE-OF-NON-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qvariable_value_denotation_defined_check,
	    STATIC_FUNCTION(variable_value_denotation_defined_check,NIL,
	    FALSE,3,3));
    mutate_global_property(Qitem_color_pattern_change,FIX((SI_Long)6L),
	    Qdenotation_type_code);
    mutate_global_property(Qitem_color_pattern_change,FIX((SI_Long)2L),
	    Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)6L) = FIX((SI_Long)2L);
    Qitem_color_pattern_change_denotation_validator = 
	    STATIC_SYMBOL("ITEM-COLOR-PATTERN-CHANGE-DENOTATION-VALIDATOR",
	    AB_package);
    mutate_global_property(Qitem_color_pattern_change,
	    Qitem_color_pattern_change_denotation_validator,
	    Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qitem_color_pattern_change_denotation_validator,
	    STATIC_FUNCTION(item_color_pattern_change_denotation_validator,
	    NIL,FALSE,5,5));
    Qitem_color_pattern_change_denotation_defined_check = 
	    STATIC_SYMBOL("ITEM-COLOR-PATTERN-CHANGE-DENOTATION-DEFINED-CHECK",
	    AB_package);
    mutate_global_property(Qitem_color_pattern_change,
	    Qitem_color_pattern_change_denotation_defined_check,
	    Qdenotation_type_defined_check);
    SET_SYMBOL_FUNCTION(Qitem_color_pattern_change_denotation_defined_check,
	    STATIC_FUNCTION(item_color_pattern_change_denotation_defined_check,
	    NIL,FALSE,3,3));
    mutate_global_property(Qcustom_event,FIX((SI_Long)7L),
	    Qdenotation_type_code);
    mutate_global_property(Qcustom_event,FIX((SI_Long)3L),
	    Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)7L) = FIX((SI_Long)3L);
    mutate_global_property(Qcustom_event,
	    FIX(IFIX(Denotation_element_overhead_slot_count) + 
	    (SI_Long)0L),Qdenotation_type_wildcard_arg_index_qm);
    Qcustom_event_denotation_validator = 
	    STATIC_SYMBOL("CUSTOM-EVENT-DENOTATION-VALIDATOR",AB_package);
    mutate_global_property(Qcustom_event,
	    Qcustom_event_denotation_validator,Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qcustom_event_denotation_validator,
	    STATIC_FUNCTION(custom_event_denotation_validator,NIL,FALSE,5,5));
    Qcustom_event_denotation_defined_check = 
	    STATIC_SYMBOL("CUSTOM-EVENT-DENOTATION-DEFINED-CHECK",AB_package);
    mutate_global_property(Qcustom_event,
	    Qcustom_event_denotation_defined_check,
	    Qdenotation_type_defined_check);
    SET_SYMBOL_FUNCTION(Qcustom_event_denotation_defined_check,
	    STATIC_FUNCTION(custom_event_denotation_defined_check,NIL,
	    FALSE,3,3));
    mutate_global_property(Qadd_item_to_workspace,FIX((SI_Long)8L),
	    Qdenotation_type_code);
    mutate_global_property(Qadd_item_to_workspace,FIX((SI_Long)2L),
	    Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)8L) = FIX((SI_Long)2L);
    Qadd_item_to_workspace_denotation_validator = 
	    STATIC_SYMBOL("ADD-ITEM-TO-WORKSPACE-DENOTATION-VALIDATOR",
	    AB_package);
    mutate_global_property(Qadd_item_to_workspace,
	    Qadd_item_to_workspace_denotation_validator,
	    Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qadd_item_to_workspace_denotation_validator,
	    STATIC_FUNCTION(add_item_to_workspace_denotation_validator,NIL,
	    FALSE,5,5));
    Qadd_item_to_workspace_denotation_defined_check = 
	    STATIC_SYMBOL("ADD-ITEM-TO-WORKSPACE-DENOTATION-DEFINED-CHECK",
	    AB_package);
    mutate_global_property(Qadd_item_to_workspace,
	    Qadd_item_to_workspace_denotation_defined_check,
	    Qdenotation_type_defined_check);
    SET_SYMBOL_FUNCTION(Qadd_item_to_workspace_denotation_defined_check,
	    STATIC_FUNCTION(add_item_to_workspace_denotation_defined_check,
	    NIL,FALSE,3,3));
    mutate_global_property(Qremove_item_from_workspace,FIX((SI_Long)9L),
	    Qdenotation_type_code);
    mutate_global_property(Qremove_item_from_workspace,FIX((SI_Long)2L),
	    Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)9L) = FIX((SI_Long)2L);
    Qremove_item_from_workspace_denotation_validator = 
	    STATIC_SYMBOL("REMOVE-ITEM-FROM-WORKSPACE-DENOTATION-VALIDATOR",
	    AB_package);
    mutate_global_property(Qremove_item_from_workspace,
	    Qremove_item_from_workspace_denotation_validator,
	    Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qremove_item_from_workspace_denotation_validator,
	    STATIC_FUNCTION(remove_item_from_workspace_denotation_validator,
	    NIL,FALSE,5,5));
    Qremove_item_from_workspace_denotation_defined_check = 
	    STATIC_SYMBOL("REMOVE-ITEM-FROM-WORKSPACE-DENOTATION-DEFINED-CHECK",
	    AB_package);
    mutate_global_property(Qremove_item_from_workspace,
	    Qremove_item_from_workspace_denotation_defined_check,
	    Qdenotation_type_defined_check);
    SET_SYMBOL_FUNCTION(Qremove_item_from_workspace_denotation_defined_check,
	    STATIC_FUNCTION(remove_item_from_workspace_denotation_defined_check,
	    NIL,FALSE,3,3));
    mutate_global_property(Qitem_event,FIX((SI_Long)10L),
	    Qdenotation_type_code);
    mutate_global_property(Qitem_event,FIX((SI_Long)3L),Qdenotation_type_size);
    temp_1 = Denotation_size_vector;
    ISVREF(temp_1,(SI_Long)10L) = FIX((SI_Long)3L);
    mutate_global_property(Qitem_event,
	    FIX(IFIX(Denotation_element_overhead_slot_count) + 
	    (SI_Long)0L),Qdenotation_type_wildcard_arg_index_qm);
    Qitem_event_denotation_validator = 
	    STATIC_SYMBOL("ITEM-EVENT-DENOTATION-VALIDATOR",AB_package);
    mutate_global_property(Qitem_event,Qitem_event_denotation_validator,
	    Qdenotation_type_validator);
    SET_SYMBOL_FUNCTION(Qitem_event_denotation_validator,
	    STATIC_FUNCTION(item_event_denotation_validator,NIL,FALSE,5,5));
    Qitem_event_denotation_defined_check = 
	    STATIC_SYMBOL("ITEM-EVENT-DENOTATION-DEFINED-CHECK",AB_package);
    mutate_global_property(Qitem_event,
	    Qitem_event_denotation_defined_check,
	    Qdenotation_type_defined_check);
    SET_SYMBOL_FUNCTION(Qitem_event_denotation_defined_check,
	    STATIC_FUNCTION(item_event_denotation_defined_check,NIL,FALSE,
	    3,3));
    if (Comp_trace_level == UNBOUND)
	Comp_trace_level = FIX((SI_Long)0L);
    Qsubscription_callback_arg_types = 
	    STATIC_SYMBOL("SUBSCRIPTION-CALLBACK-ARG-TYPES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsubscription_callback_arg_types,
	    Subscription_callback_arg_types);
    list_constant_6 = STATIC_CONS(Qsequence,Qnil);
    list_constant_7 = STATIC_LIST((SI_Long)6L,Qsymbol,list_constant,
	    list_constant_6,Qitem_or_datum,Qitem_or_datum,Qinteger);
    SET_SYMBOL_VALUE(Qsubscription_callback_arg_types,list_constant_7);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qno_callback_found = STATIC_SYMBOL("NO-CALLBACK-FOUND",AB_package);
    Qcallback = STATIC_SYMBOL("CALLBACK",AB_package);
    Qitem_representation = STATIC_SYMBOL("ITEM-REPRESENTATION",AB_package);
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    Qsession_id = STATIC_SYMBOL("SESSION-ID",AB_package);
    Qall = STATIC_SYMBOL("ALL",AB_package);
    if (Current_conclude_frame_list == UNBOUND)
	Current_conclude_frame_list = Nil;
    if (Current_conclude_innermost_frame == UNBOUND)
	Current_conclude_innermost_frame = Nil;
    if (Current_conclude_innermost_item_index == UNBOUND)
	Current_conclude_innermost_item_index = Nil;
    if (Current_subscribe_innermost_class == UNBOUND)
	Current_subscribe_innermost_class = Nil;
    if (Current_subscribe_innermost_item_index == UNBOUND)
	Current_subscribe_innermost_item_index = Nil;
    Qno_items_implied_by_denotation = 
	    STATIC_SYMBOL("NO-ITEMS-IMPLIED-BY-DENOTATION",AB_package);
    Qg2_get_unique_named_item = STATIC_SYMBOL("G2-GET-UNIQUE-NAMED-ITEM",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_unique_named_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_unique_named_item,
	    STATIC_FUNCTION(g2_get_unique_named_item,NIL,FALSE,2,2));
    Qg2_get_unique_named_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-UNIQUE-NAMED-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qitem_class = STATIC_SYMBOL("ITEM-CLASS",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Ktype,Qsymbol);
    list_constant_9 = STATIC_CONS(Qitem_class,list_constant_8);
    Qitem_name = STATIC_SYMBOL("ITEM-NAME",AB_package);
    list_constant_10 = STATIC_CONS(Qitem_name,list_constant_8);
    list_constant_11 = STATIC_LIST((SI_Long)2L,list_constant_9,
	    list_constant_10);
    list_constant_12 = STATIC_CONS(Qitem_or_datum,Qnil);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_get_unique_named_item,
	    make_system_rpc_1(Qg2_get_unique_named_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_11,
	    Nil,T),list_constant_12),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_get_unique_named_item,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_get_unique_named_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_unique_named_item_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_item_with_uuid = STATIC_SYMBOL("G2-GET-ITEM-WITH-UUID",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_item_with_uuid,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_item_with_uuid,
	    STATIC_FUNCTION(g2_get_item_with_uuid,NIL,FALSE,1,1));
    Qg2_get_item_with_uuid_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ITEM-WITH-UUID-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Quuid,Ktype,Qtext);
    list_constant_14 = STATIC_CONS(list_constant_13,Qnil);
    mutate_global_property(Qg2_get_item_with_uuid,
	    make_system_rpc_1(Qg2_get_item_with_uuid_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_14,
	    Nil,T),list_constant_12),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_get_item_with_uuid,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    SET_SYMBOL_FUNCTION(Qg2_get_item_with_uuid_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_item_with_uuid_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_make_uuid = STATIC_SYMBOL("G2-MAKE-UUID",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_make_uuid,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_make_uuid,STATIC_FUNCTION(g2_make_uuid,NIL,
	    FALSE,0,0));
    Qg2_get_from_item = STATIC_SYMBOL("G2-GET-FROM-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_from_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_4 = STATIC_STRING("~A");
    string_constant_5 = STATIC_STRING("~a");
    string_constant_6 = STATIC_STRING("Denotation ~NV in ~NF has no value");
    SET_SYMBOL_FUNCTION(Qg2_get_from_item,STATIC_FUNCTION(g2_get_from_item,
	    NIL,FALSE,2,2));
    Qg2_get_from_item_multiple = STATIC_SYMBOL("G2-GET-FROM-ITEM-MULTIPLE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_from_item_multiple,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_from_item_multiple,
	    STATIC_FUNCTION(g2_get_from_item_multiple,NIL,FALSE,2,2));
    Qg2_get_from_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-FROM-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qitem,Ktype,list_constant);
    Qdenotation_evaluation_value = 
	    STATIC_SYMBOL("DENOTATION-EVALUATION-VALUE",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)3L,
	    Qdenotation_evaluation_value,Ktype,Qdatum);
    list_constant_18 = STATIC_LIST((SI_Long)2L,list_constant_15,
	    list_constant_16);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_12);
    list_constant_19 = STATIC_CONS(list_constant_17,Qnil);
    mutate_global_property(Qg2_get_from_item,
	    make_system_rpc_1(Qg2_get_from_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_18,
	    Nil,T),list_constant_19),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_get_from_item,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    SET_SYMBOL_FUNCTION(Qg2_get_from_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_from_item_system_rpc_internal,NIL,FALSE,
	    3,3));
    Qg2_get_from_item_multiple_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-FROM-ITEM-MULTIPLE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qdenotation_sequences = STATIC_SYMBOL("DENOTATION-SEQUENCES",AB_package);
    list_constant_20 = STATIC_CONS(list_constant_6,Qnil);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)3L,Qdenotation_sequences,
	    Ktype,list_constant_20);
    list_constant_22 = STATIC_LIST((SI_Long)2L,list_constant_15,
	    list_constant_21);
    mutate_global_property(Qg2_get_from_item_multiple,
	    make_system_rpc_1(Qg2_get_from_item_multiple_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_22,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_get_from_item_multiple,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    list_constant_2 = STATIC_CONS(Qsequence,list_constant_20);
    string_constant_7 = 
	    STATIC_STRING("denotation-sequences argument ~NV must be a sequence of sequences");
    SET_SYMBOL_FUNCTION(Qg2_get_from_item_multiple_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_from_item_multiple_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_conclude_in_item = STATIC_SYMBOL("G2-CONCLUDE-IN-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_conclude_in_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_conclude_in_item,
	    STATIC_FUNCTION(g2_conclude_in_item,NIL,FALSE,3,3));
    Qg2_conclude_in_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CONCLUDE-IN-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qdenotation_sequence = STATIC_SYMBOL("DENOTATION-SEQUENCE",AB_package);
    list_constant_23 = STATIC_CONS(Ktype,list_constant_20);
    list_constant_26 = STATIC_CONS(Qdenotation_sequence,list_constant_23);
    Qnew_value = STATIC_SYMBOL("NEW-VALUE",AB_package);
    list_constant_24 = STATIC_CONS(Qdatum,Qnil);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_24);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qnew_value,Ktype,
	    list_constant_25);
    list_constant_28 = STATIC_LIST((SI_Long)3L,list_constant_15,
	    list_constant_26,list_constant_27);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_29 = STATIC_CONS(Qtruth_value,Qnil);
    mutate_global_property(Qg2_conclude_in_item,
	    make_system_rpc_1(Qg2_conclude_in_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_28,
	    Nil,T),list_constant_29),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_conclude_in_item,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    SET_SYMBOL_FUNCTION(Qg2_conclude_in_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_conclude_in_item_system_rpc_internal,NIL,
	    FALSE,4,4));
    Qg2_subscribe_to_item = STATIC_SYMBOL("G2-SUBSCRIBE-TO-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qsubscription_handle = STATIC_SYMBOL("SUBSCRIPTION-HANDLE",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_item,
	    STATIC_FUNCTION(g2_subscribe_to_item,NIL,FALSE,5,5));
    Qg2_subscribe_to_item_multiple = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-ITEM-MULTIPLE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_item_multiple,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_item_multiple,
	    STATIC_FUNCTION(g2_subscribe_to_item_multiple,NIL,FALSE,5,5));
    Qg2_subscribe_to_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_31 = STATIC_CONS(Qcallback,list_constant_8);
    Quser_data = STATIC_SYMBOL("USER-DATA",AB_package);
    list_constant_30 = STATIC_CONS(Ktype,list_constant_24);
    list_constant_32 = STATIC_CONS(Quser_data,list_constant_30);
    Qallow_batched_update = STATIC_SYMBOL("ALLOW-BATCHED-UPDATE",AB_package);
    list_constant_33 = STATIC_LIST_STAR((SI_Long)3L,Qallow_batched_update,
	    Ktype,list_constant_29);
    list_constant_35 = STATIC_LIST((SI_Long)5L,list_constant_15,
	    list_constant_26,list_constant_31,list_constant_32,
	    list_constant_33);
    list_constant_34 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_36 = STATIC_CONS(list_constant_34,Qnil);
    mutate_global_property(Qg2_subscribe_to_item,
	    make_system_rpc_1(Qg2_subscribe_to_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_35,
	    Nil,T),list_constant_36),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_subscribe_to_item,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_subscribe_to_item_system_rpc_internal,NIL,
	    FALSE,6,6));
    Qg2_subscribe_to_item_multiple_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-ITEM-MULTIPLE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)3L,list_constant_31,
	    list_constant_32,list_constant_33);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)3L,list_constant_15,
	    list_constant_21,list_constant_37);
    mutate_global_property(Qg2_subscribe_to_item_multiple,
	    make_system_rpc_1(Qg2_subscribe_to_item_multiple_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_38,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_subscribe_to_item_multiple,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_item_multiple_system_rpc_internal,
	    STATIC_FUNCTION(g2_subscribe_to_item_multiple_system_rpc_internal,
	    NIL,FALSE,6,6));
    Qg2_unsubscribe_to_item = STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-ITEM",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_unsubscribe_to_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_item,
	    STATIC_FUNCTION(g2_unsubscribe_to_item,NIL,FALSE,1,1));
    Qg2_unsubscribe_to_item_multiple = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-ITEM-MULTIPLE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_unsubscribe_to_item_multiple,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_item_multiple,
	    STATIC_FUNCTION(g2_unsubscribe_to_item_multiple,NIL,FALSE,1,1));
    Qg2_unsubscribe_to_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_39 = STATIC_CONS(Qinteger,Qnil);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)3L,Qsubscription_handle,
	    Ktype,list_constant_39);
    list_constant_41 = STATIC_CONS(list_constant_40,Qnil);
    mutate_global_property(Qg2_unsubscribe_to_item,
	    make_system_rpc_1(Qg2_unsubscribe_to_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_41,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_unsubscribe_to_item,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_unsubscribe_to_item_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_unsubscribe_to_item_multiple_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-ITEM-MULTIPLE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qsubscription_handle_sequence = 
	    STATIC_SYMBOL("SUBSCRIPTION-HANDLE-SEQUENCE",AB_package);
    list_constant_42 = STATIC_CONS(Qsubscription_handle_sequence,
	    list_constant_23);
    list_constant_43 = STATIC_CONS(list_constant_42,Qnil);
    mutate_global_property(Qg2_unsubscribe_to_item_multiple,
	    make_system_rpc_1(Qg2_unsubscribe_to_item_multiple_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_43,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_1 = adjoin(2,Qg2_unsubscribe_to_item_multiple,System_defined_rpcs);
    System_defined_rpcs = temp_1;
    list_constant_3 = STATIC_CONS(Qsequence,list_constant_39);
    string_constant_8 = 
	    STATIC_STRING("handle-sequence argument ~NV must be a sequence of integers");
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_item_multiple_system_rpc_internal,
	    STATIC_FUNCTION(g2_unsubscribe_to_item_multiple_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_subscribe_to_item_attributes = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-ITEM-ATTRIBUTES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_item_attributes,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_item_attributes,
	    STATIC_FUNCTION(g2_subscribe_to_item_attributes,NIL,FALSE,4,4));
    string_constant_9 = 
	    STATIC_STRING("The attribute-specification * is not allowed.");
    list_constant_44 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_4 = STATIC_CONS(Qsequence,list_constant_44);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_10 = 
	    STATIC_STRING("The attribute-specification ~NV must be a sequence of symbols.");
    string_constant_11 = 
	    STATIC_STRING("The attribute-specification ~NV must not contain the symbol *.");
    string_constant_12 = 
	    STATIC_STRING("The attribute-specification ~NV must be a symbol or a seqeuence ~\n          of symbols.");
    Qg2_subscribe_to_item_color_pattern_change = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-ITEM-COLOR-PATTERN-CHANGE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_item_color_pattern_change,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_item_color_pattern_change,
	    STATIC_FUNCTION(g2_subscribe_to_item_color_pattern_change,NIL,
	    FALSE,3,3));
    Qg2_subscribe_to_custom_event = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-CUSTOM-EVENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_custom_event,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_custom_event,
	    STATIC_FUNCTION(g2_subscribe_to_custom_event,NIL,FALSE,4,4));
    Qg2_send_notification_to_item = 
	    STATIC_SYMBOL("G2-SEND-NOTIFICATION-TO-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_send_notification_to_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_send_notification_to_item,
	    STATIC_FUNCTION(g2_send_notification_to_item,NIL,FALSE,3,3));
    Qg2_subscribe_to_item_event = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-ITEM-EVENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_item_event,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_item_event,
	    STATIC_FUNCTION(g2_subscribe_to_item_event,NIL,FALSE,4,4));
    Qg2_subscribe_to_add_item_to_workspace = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-ADD-ITEM-TO-WORKSPACE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_add_item_to_workspace,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_add_item_to_workspace,
	    STATIC_FUNCTION(g2_subscribe_to_add_item_to_workspace,NIL,
	    FALSE,3,3));
    Qg2_subscribe_to_remove_item_from_workspace = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-REMOVE-ITEM-FROM-WORKSPACE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_remove_item_from_workspace,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_remove_item_from_workspace,
	    STATIC_FUNCTION(g2_subscribe_to_remove_item_from_workspace,NIL,
	    FALSE,3,3));
    Qg2_subscribe_to_variable_or_parameter_value = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-VARIABLE-OR-PARAMETER-VALUE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_variable_or_parameter_value,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_variable_or_parameter_value,
	    STATIC_FUNCTION(g2_subscribe_to_variable_or_parameter_value,
	    NIL,FALSE,3,3));
    Qg2_get_subscription_handle_info = 
	    STATIC_SYMBOL("G2-GET-SUBSCRIPTION-HANDLE-INFO",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_subscription_handle_info,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_13 = 
	    STATIC_STRING("~NV is not a valid subscription handle.");
    Qsubscribed_item = STATIC_SYMBOL("SUBSCRIBED-ITEM",AB_package);
    Qsubscribed_callback = STATIC_SYMBOL("SUBSCRIBED-CALLBACK",AB_package);
    Qsubscription_denotation = STATIC_SYMBOL("SUBSCRIPTION-DENOTATION",
	    AB_package);
    Qsubscription_user_data = STATIC_SYMBOL("SUBSCRIPTION-USER-DATA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_subscription_handle_info,
	    STATIC_FUNCTION(g2_get_subscription_handle_info,NIL,FALSE,1,1));
    Qg2_get_subscription_handles_for_item = 
	    STATIC_SYMBOL("G2-GET-SUBSCRIPTION-HANDLES-FOR-ITEM",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_subscription_handles_for_item,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_subscription_handles_for_item,
	    STATIC_FUNCTION(g2_get_subscription_handles_for_item,NIL,FALSE,
	    1,1));
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qexclude_from_wildcard_denotation = 
	    STATIC_SYMBOL("EXCLUDE-FROM-WILDCARD-DENOTATION",AB_package);
    string_constant_14 = 
	    string_append2(STATIC_STRING("More than one attribute of class ~a has ~a as a possible ~\n                 value.  The implied attributes feature cannot be used when ~\n                 this is the case. Att"),
	    STATIC_STRING("ributes found so far are ~NS and ~NS."));
    Qitem_not_editable_conclude_error = 
	    STATIC_SYMBOL("ITEM-NOT-EDITABLE-CONCLUDE-ERROR",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_15 = 
	    STATIC_STRING("Cannot edit ~NF, because ~A.  See the saving-parameters.");
    Qg2_defstruct_structure_name_slot_description_g2_struct = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtype_mismatch = STATIC_SYMBOL("TYPE-MISMATCH",AB_package);
    string_constant_16 = 
	    STATIC_STRING("The attribute ~a of ~NF is read-only.");
    Qexpecting_structure_or_sequence_inside_attribute = 
	    STATIC_SYMBOL("EXPECTING-STRUCTURE-OR-SEQUENCE-INSIDE-ATTRIBUTE",
	    AB_package);
    Qsystem_attribute_conclude_error = 
	    STATIC_SYMBOL("SYSTEM-ATTRIBUTE-CONCLUDE-ERROR",AB_package);
    Qexpecting_structure_inside_attribute = 
	    STATIC_SYMBOL("EXPECTING-STRUCTURE-INSIDE-ATTRIBUTE",AB_package);
    Qexpecting_sequence_inside_attribute = 
	    STATIC_SYMBOL("EXPECTING-SEQUENCE-INSIDE-ATTRIBUTE",AB_package);
    Qconclude_no_value_into_parameter = 
	    STATIC_SYMBOL("CONCLUDE-NO-VALUE-INTO-PARAMETER",AB_package);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    Qconclude_into_variable_error = 
	    STATIC_SYMBOL("CONCLUDE-INTO-VARIABLE-ERROR",AB_package);
    Qexplanation = STATIC_SYMBOL("EXPLANATION",AB_package);
    if (Scratch_attribute_denotation == UNBOUND)
	Scratch_attribute_denotation = Nil;
    if (Scratch_virtual_attribute_denotation == UNBOUND)
	Scratch_virtual_attribute_denotation = Nil;
    if (Scratch_variable_value_denotation == UNBOUND)
	Scratch_variable_value_denotation = Nil;
    if (Scratch_item_color_pattern_change_denotation == UNBOUND)
	Scratch_item_color_pattern_change_denotation = Nil;
    if (Scratch_custom_event_denotation == UNBOUND)
	Scratch_custom_event_denotation = Nil;
    if (Scratch_item_event_denotation == UNBOUND)
	Scratch_item_event_denotation = Nil;
    if (Scratch_add_item_to_workspace == UNBOUND)
	Scratch_add_item_to_workspace = Nil;
    if (Scratch_remove_item_from_workspace == UNBOUND)
	Scratch_remove_item_from_workspace = Nil;
}
