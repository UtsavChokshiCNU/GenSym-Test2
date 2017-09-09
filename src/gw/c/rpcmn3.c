/* rpcmn3.c
 * Input file:  rpc-common3.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rpcmn3.h"


Object G2int_class_rpc_item_info_to_slot_names_interned_list_prop = UNBOUND;

static Object Qg2int_attribute_description_list;  /* attribute-description-list */

/* SET-INTERNED-LIST--ATTRIBUTE-DESCRIPTION-LIST */
Object g2int_set_interned_list__attribute_description_list(interned_list,value)
    Object interned_list, value;
{
    Object plist, tail, svref_new_value;

    x_note_fn_call(48,0);
    plist = ISVREF(interned_list,(SI_Long)3L);
    tail = g2int_memq_function(Qg2int_attribute_description_list,plist);
    if (tail)
	M_CADR(tail) = value;
    else {
	svref_new_value = 
		g2int_gensym_cons_1(Qg2int_attribute_description_list,
		g2int_gensym_cons_1(value,plist));
	SVREF(interned_list,FIX((SI_Long)3L)) = svref_new_value;
    }
    return VALUES_1(value);
}

static Object Qg2int_interned_list_table;  /* interned-list-table */

static Object Qg2_defstruct_structure_name_interned_list_g2_struct;  /* g2-defstruct-structure-name::interned-list-g2-struct */

static Object Qg2int_none;         /* none */

/* DECACHE-ALL-ATTRIBUTE-DESCRIPTION-LISTS */
Object g2int_decache_all_attribute_description_lists(tree)
    Object tree;
{
    Object symbol, ab_loop_list_, table, car_1, cdr_1, list_1;

    x_note_fn_call(48,1);
    if ( !TRUEP(tree)) {
	if (G2int_interned_list_nil)
	    g2int_decache_all_attribute_description_lists(G2int_interned_list_nil);
	if (G2int_interned_list_non_symbol_root)
	    g2int_decache_all_attribute_description_lists(G2int_interned_list_non_symbol_root);
	symbol = Nil;
	ab_loop_list_ = G2int_interned_list_symbols;
	table = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	table = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		Qg2int_interned_list_table);
	if (table)
	    g2int_decache_all_attribute_description_lists(table);
	goto next_loop;
      end_loop:;
    }
    else if (CONSP(tree)) {
	car_1 = M_CAR(tree);
	cdr_1 = M_CDR(tree);
	if (car_1)
	    g2int_decache_all_attribute_description_lists(car_1);
	if (cdr_1)
	    g2int_decache_all_attribute_description_lists(cdr_1);
    }
    else if (SIMPLE_VECTOR_P(tree) && EQ(ISVREF(tree,(SI_Long)0L),
	    Qg2_defstruct_structure_name_interned_list_g2_struct)) {
	list_1 = g2int_getfq_function(ISVREF(tree,(SI_Long)3L),
		Qg2int_attribute_description_list,Qg2int_none);
	if (CONSP(list_1)) {
	    g2int_set_interned_list__attribute_description_list(tree,
		    Qg2int_none);
	    g2int_reclaim_gensym_list_1(list_1);
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_class_rpc_item_info_to_slot_names_interned_list;  /* class-rpc-item-info-to-slot-names-interned-list */

/* DECACHE-ATTRIBUTE-DESCRIPTION-LISTS-OF-INTERNED-LISTS */
Object g2int_decache_attribute_description_lists_of_interned_lists(class_1)
    Object class_1;
{
    Object alist, a, ab_loop_list_, table;

    x_note_fn_call(48,2);
    alist = g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
	    Qg2int_class_rpc_item_info_to_slot_names_interned_list);
    g2int_mutate_global_property(class_1,Nil,
	    Qg2int_class_rpc_item_info_to_slot_names_interned_list);
    a = Nil;
    ab_loop_list_ = alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    a = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_reclaim_gensym_cons_1(a);
    goto next_loop;
  end_loop:;
    g2int_reclaim_gensym_list_1(alist);
    table = g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
	    Qg2int_interned_list_table);
    if (table)
	g2int_decache_all_attribute_description_lists(table);
    return VALUES_1(Nil);
}

/* CHECK-CLASS-FOR-ITEM-PASSING-1 */
Object g2int_check_class_for_item_passing_1(class_1)
    Object class_1;
{
    x_note_fn_call(48,3);
    return VALUES_1(Nil);
}

static Object Qg2int_resumable_error;  /* resumable-error */

static Object array_constant;      /* # */

/* CHECK-CLASS-FOR-ITEM-PASSING */
Object g2int_check_class_for_item_passing(class_1)
    Object class_1;
{
    Object error_string, temp;

    x_note_fn_call(48,4);
    error_string = g2int_check_class_for_item_passing_1(class_1);
    temp = error_string ? g2int_icp_error_internal(Qg2int_resumable_error,
	    error_string,array_constant,class_1,Nil) : Nil;
    return VALUES_1(temp);
}

/* GET-ATTRIBUTE-DESCRIPTION-LIST-FOR-INTERNED-LIST */
Object g2int_get_attribute_description_list_for_interned_list(interned_list)
    Object interned_list;
{
    x_note_fn_call(48,5);
    return VALUES_1(Nil);
}

/* INCLUDE-USER-ATTRIBUTE-FOR-ITEM-PASSING-P */
Object g2int_include_user_attribute_for_item_passing_p(slot_description,
	    class_description,included_attributes_qm,excluded_attributes_qm)
    Object slot_description, class_description, included_attributes_qm;
    Object excluded_attributes_qm;
{
    x_note_fn_call(48,6);
    return VALUES_1(T);
}

Object G2int_attributes_to_exclude_from_item_passing = UNBOUND;

/* GET-SLOT-NAMES-FOR-ITEM-PASSING-FROM-CLASS-DESCRIPTION-1 */
Object g2int_get_slot_names_for_item_passing_from_class_description_1(class_description,
	    included_attributes_qm,excluded_attributes_qm,
	    included_system_attributes,excluded_system_attributes)
    Object class_description, included_attributes_qm, excluded_attributes_qm;
    Object included_system_attributes, excluded_system_attributes;
{
    x_note_fn_call(48,7);
    return VALUES_1(Nil);
}

/* GET-INTERNED-SLOT-NAMES-FOR-ITEM-PASSING-FROM-CLASS-DESCRIPTION */
Object g2int_get_interned_slot_names_for_item_passing_from_class_description(class_description,
	    rpc_item_info,icp_protocol_version)
    Object class_description, rpc_item_info, icp_protocol_version;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(48,8);
    PUSH_SPECIAL(G2int_icp_protocol_version,icp_protocol_version,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2int_names;        /* names */

static Object Qg2int_value_structure_using_unix_time;  /* value-structure-using-unix-time */

static Object Qg2int_gsi_append_flag;  /* gsi-append-flag */

static Object Qg2int_g2_array_sequence_append;  /* g2-array-sequence-append */

static Object list_constant;       /* # */

static Object Qg2int_gsi_update_items_in_lists_and_arrays_flag;  /* gsi-update-items-in-lists-and-arrays-flag */

static Object Qg2int_gsi_delete_flag;  /* gsi-delete-flag */

static Object Qg2int_g2_array_sequence_immediate_with_delete;  /* g2-array-sequence-immediate-with-delete */

static Object Qg2int_g2_array_sequence_immediate;  /* g2-array-sequence-immediate */

static Object Qg2int_g2_array_sequence_with_delete;  /* g2-array-sequence-with-delete */

static Object Qg2int_g2_array_sequence;  /* g2-array-sequence */

static Object Qg2int_element_type;  /* element-type */

static Object Qg2int_g2_list_sequence_append;  /* g2-list-sequence-append */

static Object list_constant_1;     /* # */

static Object Qg2int_g2_list_sequence_immediate_with_delete;  /* g2-list-sequence-immediate-with-delete */

static Object Qg2int_g2_list_sequence_immediate;  /* g2-list-sequence-immediate */

static Object Qg2int_g2_list_sequence_with_delete;  /* g2-list-sequence-with-delete */

static Object Qg2int_g2_list_sequence;  /* g2-list-sequence */

static Object Qg2int_history_keeping_spec;  /* history-keeping-spec */

static Object Qg2int_history_using_unix_time;  /* history-using-unix-time */

static Object Qg2int_class_qualified_name;  /* class-qualified-name */

/* GSI-GET-SLOT-NAMES-FOR-ITEM-PASSING */
Object g2int_gsi_get_slot_names_for_item_passing(item)
    Object item;
{
    Object gsi_instance_extension, temp, temp_2, temp_3, temp_4, gsi_item;
    Object attribute_count, attribute_count_with_offset, attributes, attribute;
    Object attribute_spec, base_name, class_qualifier_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;
    SI_Long temp_1, i, ab_loop_bind_;

    x_note_fn_call(48,9);
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    temp = (gsi_instance_extension ? TRUEP(ISVREF(gsi_instance_extension,
	    (SI_Long)4L)) : TRUEP(Nil)) ? g2int_gensym_cons_1(Qg2int_names,
	    Nil) : Nil;
    temp_1 = IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L;
    if ( !((SI_Long)-128L <= temp_1 && temp_1 <= (SI_Long)127L))
	temp_2 = Nil;
    else
	switch ((char)temp_1) {
	  case 1:
	  case 4:
	  case 6:
	  case 5:
	  case 3:
	  case 11:
	    temp_2 = ISVREF(item,(SI_Long)2L) ? 
		    g2int_gensym_cons_1(Qg2int_value_structure_using_unix_time,
		    Nil) : Nil;
	    break;
	  case 22:
	  case 20:
	  case 17:
	  case 21:
	  case 19:
	  case 23:
	  case 24:
	  case 25:
	  case 26:
	    if (g2int_get_gsi_instance_plist_value(item,
		    Qg2int_gsi_append_flag))
		temp_3 = Qg2int_g2_array_sequence_append;
	    else if (g2int_memq_function(FIX(IFIX(ISVREF(item,
		    (SI_Long)1L)) >>  -  - (SI_Long)3L),list_constant) && 
		    g2int_get_gsi_instance_plist_value(item,
		    Qg2int_gsi_update_items_in_lists_and_arrays_flag)) {
		temp_4 = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
		temp_3 = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
		temp_3 = IFIX(FIXNUM_MIN(temp_4,temp_3)) >= (SI_Long)19L ? 
			(g2int_get_gsi_instance_plist_value(item,
			Qg2int_gsi_delete_flag) ? 
			Qg2int_g2_array_sequence_immediate_with_delete : 
			Qg2int_g2_array_sequence_immediate) : 
			Qg2int_g2_array_sequence_immediate;
	    }
	    else {
		temp_4 = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
		temp_3 = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
		temp_3 = IFIX(FIXNUM_MIN(temp_4,temp_3)) >= (SI_Long)19L ? 
			(g2int_get_gsi_instance_plist_value(item,
			Qg2int_gsi_delete_flag) ? 
			Qg2int_g2_array_sequence_with_delete : 
			Qg2int_g2_array_sequence) : Qg2int_g2_array_sequence;
	    }
	    temp_2 = g2int_gensym_list_2(Qg2int_element_type,temp_3);
	    break;
	  case 38:
	  case 36:
	  case 33:
	  case 37:
	  case 35:
	  case 39:
	  case 40:
	  case 41:
	  case 42:
	    if (g2int_get_gsi_instance_plist_value(item,
		    Qg2int_gsi_append_flag))
		temp_3 = Qg2int_g2_list_sequence_append;
	    else if (g2int_memq_function(FIX(IFIX(ISVREF(item,
		    (SI_Long)1L)) >>  -  - (SI_Long)3L),list_constant_1) 
		    && g2int_get_gsi_instance_plist_value(item,
		    Qg2int_gsi_update_items_in_lists_and_arrays_flag)) {
		temp_4 = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
		temp_3 = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
		temp_3 = IFIX(FIXNUM_MIN(temp_4,temp_3)) >= (SI_Long)19L ? 
			(g2int_get_gsi_instance_plist_value(item,
			Qg2int_gsi_delete_flag) ? 
			Qg2int_g2_list_sequence_immediate_with_delete : 
			Qg2int_g2_list_sequence_immediate) : 
			Qg2int_g2_list_sequence_immediate;
	    }
	    else {
		temp_4 = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
		temp_3 = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
		temp_3 = IFIX(FIXNUM_MIN(temp_4,temp_3)) >= (SI_Long)19L ? 
			(g2int_get_gsi_instance_plist_value(item,
			Qg2int_gsi_delete_flag) ? 
			Qg2int_g2_list_sequence_with_delete : 
			Qg2int_g2_list_sequence) : Qg2int_g2_list_sequence;
	    }
	    temp_2 = g2int_gensym_list_2(Qg2int_element_type,temp_3);
	    break;
	  default:
	    temp_2 = Nil;
	    break;
	}
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    temp_4 = (gsi_instance_extension ? TRUEP(ISVREF(gsi_instance_extension,
	    (SI_Long)12L)) : TRUEP(Nil)) ? 
	    g2int_gensym_list_2(Qg2int_history_keeping_spec,
	    Qg2int_history_using_unix_time) : Nil;
    gsi_item = item;
    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
    attribute_count = gsi_instance_extension ? 
	    ISVREF(gsi_instance_extension,(SI_Long)9L) : FIX((SI_Long)0L);
    attribute_count_with_offset = FIXNUM_ADD1(attribute_count);
    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
    attributes = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)8L) : Nil;
    if ((SI_Long)0L < IFIX(attribute_count)) {
	i = IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = IFIX(attribute_count_with_offset);
	attribute = Nil;
	attribute_spec = Nil;
	base_name = Nil;
	class_qualifier_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	attribute = ISVREF(attributes,i);
	attribute_spec = ISVREF(attribute,(SI_Long)1L);
	base_name = CONSP(attribute_spec) ? THIRD(attribute_spec) : 
		attribute_spec;
	class_qualifier_qm = CONSP(attribute_spec) ? 
		SECOND(attribute_spec) : Nil;
	if ( !((SI_Long)1L == ((SI_Long)1L & IFIX(ISVREF(attribute,
		(SI_Long)3L))))) {
	    ab_loopvar__2 = g2int_gensym_cons_1(class_qualifier_qm ? 
		    g2int_gensym_list_3(Qg2int_class_qualified_name,
		    class_qualifier_qm,base_name) : base_name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_3 = ab_loopvar_;
	goto end;
	temp_3 = Qnil;
      end:;
    }
    else
	temp_3 = Nil;
    temp_3 = nconc2(temp,nconc2(temp_2,nconc2(temp_4,temp_3)));
    return VALUES_1(temp_3);
}

/* GSI-GET-INTERNED-SLOT-NAMES-FOR-ITEM-PASSING */
Object g2int_gsi_get_interned_slot_names_for_item_passing(class_1,item)
    Object class_1, item;
{
    Object slot_names, list_1, interned_slot_names;

    x_note_fn_call(48,10);
    slot_names = g2int_gsi_get_slot_names_for_item_passing(item);
    list_1 = g2int_gensym_cons_1(class_1,slot_names);
    interned_slot_names = g2int_intern_list(list_1);
    g2int_reclaim_gensym_tree_1(list_1);
    return VALUES_1(interned_slot_names);
}

static Object list_constant_2;     /* # */

/* GSI-SPECIAL-ATTRIBUTE-P */
Object g2int_gsi_special_attribute_p(attribute)
    Object attribute;
{
    Object temp;

    x_note_fn_call(48,11);
    temp = g2int_memq_function(attribute,list_constant_2);
    return VALUES_1(temp);
}

static Object Qg2int_text;         /* text */

static Object Qg2int_truth_value;  /* truth-value */

static Object Qg2int_item_or_value;  /* item-or-value */

static Object Qg2int_quantity;     /* quantity */

static Object Qg2int_item;         /* item */

static Object Qg2int_value;        /* value */

/* ELEMENT-TYPE-FOR-GSI-TYPE */
Object g2int_element_type_for_gsi_type(gsi_type)
    Object gsi_type;
{
    Object temp;

    x_note_fn_call(48,12);
    if ( !(FIXNUMP(gsi_type) && FIXNUM_LE(FIX((SI_Long)-128L),gsi_type) && 
	    FIXNUM_LE(gsi_type,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(gsi_type)) {
	  case 22:
	    temp = Qfloat;
	    break;
	  case 38:
	    temp = Qfloat;
	    break;
	  case 20:
	    temp = Qg2int_text;
	    break;
	  case 36:
	    temp = Qg2int_text;
	    break;
	  case 17:
	    temp = Qinteger;
	    break;
	  case 33:
	    temp = Qinteger;
	    break;
	  case 21:
	    temp = Qg2int_truth_value;
	    break;
	  case 37:
	    temp = Qg2int_truth_value;
	    break;
	  case 19:
	    temp = Qsymbol;
	    break;
	  case 35:
	    temp = Qsymbol;
	    break;
	  case 25:
	    temp = Qg2int_item_or_value;
	    break;
	  case 41:
	    temp = Qg2int_item_or_value;
	    break;
	  case 26:
	    temp = Qg2int_quantity;
	    break;
	  case 42:
	    temp = Qg2int_quantity;
	    break;
	  case 23:
	    temp = Qg2int_item;
	    break;
	  case 39:
	    temp = Qg2int_item;
	    break;
	  case 24:
	    temp = Qg2int_value;
	    break;
	  case 40:
	    temp = Qg2int_value;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_1(temp);
}

Object G2int_item_copy_root_item = UNBOUND;

Object G2int_item_copy_handle_for_root_item = UNBOUND;

Object G2int_item_copy_rpc_item_info = UNBOUND;

static Object Qg2int_item_copy_index_space;  /* item-copy-index-space */

/* ENSURE-ITEM-COPY-INDEX-SPACE */
Object g2int_ensure_item_copy_index_space()
{
    Object temp;

    x_note_fn_call(48,13);
    if (SYMBOLP(G2int_item_copy_index_space)) {
	G2int_item_copy_index_space = 
		g2int_make_index_space_1(Qg2int_item_copy_index_space,Nil);
	temp = G2int_item_copy_index_space;
    }
    else
	temp = G2int_item_copy_index_space;
    return VALUES_1(temp);
}

/* LOOKUP-INDEX-IN-INDEX-SPACE */
Object g2int_lookup_index_in_index_space(x,index_space)
    Object x, index_space;
{
    Object vector_of_vectors, vector_1, value;
    SI_Long i, ab_loop_bind_, j, ab_loop_bind__1;

    x_note_fn_call(48,14);
    vector_of_vectors = ISVREF(index_space,(SI_Long)2L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_of_vectors));
    vector_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    vector_1 = ISVREF(vector_of_vectors,i);
    if ( !TRUEP(vector_1))
	goto end_loop;
    j = (SI_Long)0L;
    ab_loop_bind__1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
    value = Nil;
  next_loop_1:
    if (j >= ab_loop_bind__1)
	goto end_loop_1;
    value = ISVREF(vector_1,j);
    if ( !TRUEP(value))
	goto end_loop_1;
    if (EQ(x,value))
	return VALUES_1(FIX((i << (SI_Long)10L) + j));
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

Object G2int_current_attribute_description_index = UNBOUND;

Object G2int_current_slot_value_of_user_slot = UNBOUND;

/* MAKE-TRANSIENT-FRAME-FOR-ITEM-PASSING */
Object g2int_make_transient_frame_for_item_passing(class_1)
    Object class_1;
{
    x_note_fn_call(48,15);
    return VALUES_1(class_1);
}

/* ACTIVATE-ITEM-IF-NECESSARY */
Object g2int_activate_item_if_necessary(item)
    Object item;
{
    x_note_fn_call(48,16);
    return VALUES_1(item);
}

static Object Qg2int_truth;        /* truth */

static Object Qg2int_float;        /* |float| */

static Object list_constant_3;     /* # */

static Object Qg2int_maybe;        /* maybe */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

/* ARRAY-OR-LIST-ELEMENT-TYPE-SUITABLE-P */
Object g2int_array_or_list_element_type_suitable_p(received_element_type,
	    required_element_type)
    Object received_element_type, required_element_type;
{
    Object temp;

    x_note_fn_call(48,17);
    if (EQ(received_element_type,Qg2int_truth))
	received_element_type = Qg2int_truth_value;
    else if (EQ(received_element_type,Qg2int_float))
	received_element_type = Qfloat;
    else;
    if (EQ(required_element_type,received_element_type) || 
	    EQ(required_element_type,Qg2int_item_or_value))
	temp = Qt;
    else if (EQ(required_element_type,Qg2int_value)) {
	if (g2int_memq_function(received_element_type,list_constant_3))
	    temp = Qt;
	else if (EQ(received_element_type,Qg2int_item_or_value))
	    temp = Qg2int_maybe;
	else
	    temp = Qnil;
    }
    else if (EQ(required_element_type,Qg2int_quantity)) {
	if (g2int_memq_function(received_element_type,list_constant_4))
	    temp = Qt;
	else if (g2int_memq_function(received_element_type,list_constant_5))
	    temp = Qg2int_maybe;
	else
	    temp = Qnil;
    }
    else if (g2int_memq_function(required_element_type,list_constant_4))
	temp = g2int_memq_function(received_element_type,list_constant_6) ?
		 Qg2int_maybe : Nil;
    else if (g2int_memq_function(required_element_type,list_constant_7))
	temp = g2int_memq_function(received_element_type,list_constant_5) ?
		 Qg2int_maybe : Nil;
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_item_new_copy;  /* write-icp-item-new-copy */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* WRITE-ICP-ITEM-NEW-COPY */
Object g2int_write_icp_item_new_copy(item_new_copy)
    Object item_new_copy;
{
    Object class_1, interned_list, new_index, svref_arg_1;
    Object gsi_instance_extension, name, element_type, history, gsi_item;
    Object attribute_count, attribute_count_with_offset, attributes, attribute;
    Object attribute_value, temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Object key, v1, v2, v3;
    SI_Long svref_arg_2, temp, i, ab_loop_bind_;
    Object result;

    x_note_fn_call(48,18);
    if (G2int_disable_resumability) {
	class_1 = g2int_class_for_gsi_item(item_new_copy);
	interned_list = 
		g2int_gsi_get_interned_slot_names_for_item_passing(class_1,
		item_new_copy);
	new_index = 
		g2int_assign_index_in_index_space(g2int_ensure_item_copy_index_space());
	if (FIXNUM_GE(new_index,ISVREF(G2int_item_copy_index_space,
		(SI_Long)4L)))
	    g2int_enlarge_index_space(G2int_item_copy_index_space,new_index);
	svref_arg_1 = ISVREF(ISVREF(G2int_item_copy_index_space,
		(SI_Long)2L),IFIX(new_index) >>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(new_index) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = item_new_copy;
	g2int_write_icp_interned_list_as_value_type(interned_list);
	gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	name = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)4L) : Nil;
	if (name)
	    g2int_write_icp_symbol_as_value_type(name);
	if (ISVREF(item_new_copy,(SI_Long)2L)) {
	    temp = IFIX(ISVREF(item_new_copy,(SI_Long)1L)) >>  -  - 
		    (SI_Long)3L;
	    if (! !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
		switch ((char)temp) {
		  case 1:
		  case 4:
		  case 6:
		  case 5:
		  case 3:
		  case 11:
		    g2int_write_gsi_value_structure(item_new_copy);
		    break;
		  default:
		    break;
		}
	}
	element_type = 
		g2int_element_type_for_gsi_type(FIX(IFIX(ISVREF(item_new_copy,
		(SI_Long)1L)) >>  -  - (SI_Long)3L));
	if (element_type) {
	    g2int_write_icp_remote_value(element_type);
	    g2int_write_sequence_from_gsi_item(item_new_copy,element_type);
	}
	gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	history = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)12L) : Nil;
	if (history) {
	    g2int_write_gsi_history_specification(history);
	    g2int_write_gsi_history(history,item_new_copy);
	}
	gsi_item = item_new_copy;
	gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	attribute_count = gsi_instance_extension ? 
		ISVREF(gsi_instance_extension,(SI_Long)9L) : FIX((SI_Long)0L);
	attribute_count_with_offset = FIXNUM_ADD1(attribute_count);
	gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	attributes = gsi_instance_extension ? 
		ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
	if ((SI_Long)0L < IFIX(attribute_count)) {
	    i = IFIX(G2int_gsi_magic_offset);
	    ab_loop_bind_ = IFIX(attribute_count_with_offset);
	    attribute = Nil;
	    attribute_value = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    attribute = ISVREF(attributes,i);
	    attribute_value = ISVREF(attribute,(SI_Long)4L);
	    if ( !((SI_Long)1L == ((SI_Long)1L & IFIX(ISVREF(attribute,
		    (SI_Long)3L)))))
		g2int_write_icp_remote_value(attribute_value);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp_1 = Qnil;
	}
	else
	    temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_item_new_copy,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_item_new_copy,top,Nil);
	}
	item_new_copy = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item_new_copy;
	class_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		g2int_class_for_gsi_item(item_new_copy);
	interned_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		g2int_gsi_get_interned_slot_names_for_item_passing(class_1,
		item_new_copy);
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp_1 = g2int_resumable_icp_pop();
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
	new_index = 
		g2int_assign_index_in_index_space(g2int_ensure_item_copy_index_space());
	if (FIXNUM_GE(new_index,ISVREF(G2int_item_copy_index_space,
		(SI_Long)4L)))
	    g2int_enlarge_index_space(G2int_item_copy_index_space,new_index);
	svref_arg_1 = ISVREF(ISVREF(G2int_item_copy_index_space,
		(SI_Long)2L),IFIX(new_index) >>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(new_index) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = item_new_copy;
      l1:
	if (EQ(icp_suspend_1,
		g2int_write_icp_interned_list_as_value_type(interned_list))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp_1 = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		    temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		  default:
		    break;
		}
	}
      l1_1:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	    name = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		    (SI_Long)4L) : Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		    name) {
	    if (EQ(icp_suspend_1,g2int_write_icp_symbol_as_value_type(name))) {
		g2int_resumable_icp_push(name);
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block_1;
	    }
	}
      l2_1:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		ISVREF(item_new_copy,(SI_Long)2L)) {
	    key = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : 
		    FIX(IFIX(ISVREF(item_new_copy,(SI_Long)1L)) >>  -  - 
		    (SI_Long)3L);
	    if (! !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		    FIXNUM_LE(key,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(key)) {
		  case 1:
		  case 4:
		  case 6:
		  case 5:
		  case 3:
		  case 11:
		    if (EQ(icp_suspend_1,
			    g2int_write_gsi_value_structure(item_new_copy))) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_1;
		    }
		    break;
		  default:
		    break;
		}
	}
      l3:
	element_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		g2int_element_type_for_gsi_type(FIX(IFIX(ISVREF(item_new_copy,
		(SI_Long)1L)) >>  -  - (SI_Long)3L));
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		element_type) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp_1 = g2int_resumable_icp_pop();
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
	    if (EQ(icp_suspend_1,g2int_write_icp_remote_value(element_type))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		temp_1 = G2int_icp_suspend;
		goto end_block_2;
	    }
	  l2_2:
	    if (EQ(icp_suspend_1,
		    g2int_write_sequence_from_gsi_item(item_new_copy,
		    element_type))) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		temp_1 = G2int_icp_suspend;
		goto end_block_2;
	    }
	    else
		temp_1 = Nil;
	    goto end_block_2;
	  end_block_2:
	    if (EQ(icp_suspend_1,temp_1)) {
		g2int_resumable_icp_push(element_type);
		g2int_resumable_icp_push(FIX((SI_Long)3L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block_1;
	    }
	}
      l4:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    history = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	    history = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)12L) : Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		history) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp_1 = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp_1)) {
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
		    g2int_write_gsi_history_specification(history))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		temp_1 = G2int_icp_suspend;
		goto end_block_3;
	    }
	  l2_3:
	    if (EQ(icp_suspend_1,g2int_write_gsi_history(history,
		    item_new_copy))) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		temp_1 = G2int_icp_suspend;
		goto end_block_3;
	    }
	    else
		temp_1 = Nil;
	    goto end_block_3;
	  end_block_3:
	    if (EQ(icp_suspend_1,temp_1)) {
		g2int_resumable_icp_push(history);
		g2int_resumable_icp_push(FIX((SI_Long)4L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block_1;
	    }
	}
      l5:
	gsi_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item_new_copy;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    attribute_count = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    attribute_count = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)9L) : 
		    FIX((SI_Long)0L);
	}
	attribute_count_with_offset = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : FIXNUM_ADD1(attribute_count);
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    attributes = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    attributes = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		(SI_Long)0L < IFIX(attribute_count)) {
	    i = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : 
		    IFIX(G2int_gsi_magic_offset);
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : 
		    IFIX(attribute_count_with_offset);
	    attribute = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    attribute_value = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		goto resume;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    attribute = ISVREF(attributes,i);
	    attribute_value = ISVREF(attribute,(SI_Long)4L);
	  resume:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    ||  !((SI_Long)1L == ((SI_Long)1L & 
		    IFIX(ISVREF(attribute,(SI_Long)3L))))) {
		if (EQ(icp_suspend_1,
			g2int_write_icp_remote_value(attribute_value))) {
		    g2int_resumable_icp_push(attribute_value);
		    g2int_resumable_icp_push(attribute);
		    g2int_resumable_icp_push(FIX(ab_loop_bind_));
		    g2int_resumable_icp_push(FIX(i));
		    g2int_resumable_icp_push(attributes);
		    g2int_resumable_icp_push(attribute_count_with_offset);
		    g2int_resumable_icp_push(attribute_count);
		    g2int_resumable_icp_push(gsi_item);
		    g2int_resumable_icp_push(FIX((SI_Long)5L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_1;
		}
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_1(Qnil);
	}
	else
	    result = VALUES_1(Nil);
	goto end_block_1;
      end_block_1:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	result = VALUES_3(v1,v2,v3);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(interned_list);
	    g2int_resumable_icp_push(class_1);
	    g2int_resumable_icp_push(item_new_copy);
	    g2int_resumable_icp_push(Qg2int_write_icp_item_new_copy);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp_1 = v1;
    }
    return VALUES_1(temp_1);
}

static Object Qg2int_default_error;  /* default-error */

static Object array_constant_1;    /* # */

/* GET-DEFAULT-CLASS-FOR-MISSING-CLASS */
Object g2int_get_default_class_for_missing_class(desired_class,
	    foundation_class)
    Object desired_class, foundation_class;
{
    Object new_class, error_string, temp;

    x_note_fn_call(48,19);
    if (desired_class && foundation_class) {
	new_class = EQ(foundation_class,Qerror) ? Qg2int_default_error : Nil;
	error_string = new_class ? 
		g2int_check_class_for_item_passing_1(new_class) : 
		array_constant_1;
	temp =  !TRUEP(error_string) ? new_class : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* HANDLE-MISSING-CLASS-IN-RPC */
Object g2int_handle_missing_class_in_rpc(error_string,desired_class,
	    contents_as_structure,index_1)
    Object error_string, desired_class, contents_as_structure, index_1;
{
    Object temp;

    x_note_fn_call(48,20);
    temp = g2int_icp_error_internal(Qerror,error_string,array_constant,
	    desired_class,Nil);
    return VALUES_1(temp);
}

Object G2int_append_into_arrays_and_lists = UNBOUND;

Object G2int_delete_old_elements_from_arrays_and_lists = UNBOUND;

/* CHANGE-ATTRIBUTE-DESCRIPTION-EVALUATION-VALUE-FOR-ICP */
Object g2int_change_attribute_description_evaluation_value_for_icp(item_new_copy,
	    attribute_description,value)
    Object item_new_copy, attribute_description, value;
{
    x_note_fn_call(48,21);
    return VALUES_1(Nil);
}

Object G2int_allow_no_value_p = UNBOUND;

/* DELETE-FRAME-FOR-RPC */
Object g2int_delete_frame_for_rpc(frame)
    Object frame;
{
    x_note_fn_call(48,22);
    return VALUES_1(Nil);
}

static Object Qg2int_read_immediate_g2_array_sequence;  /* read-immediate-g2-array-sequence */

/* READ-IMMEDIATE-G2-ARRAY-SEQUENCE */
Object g2int_read_immediate_g2_array_sequence(g2_array,delete_p)
    Object g2_array, delete_p;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(48,23);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_immediate_g2_array_sequence,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_immediate_g2_array_sequence,top,Nil);
	}
	g2_array = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : g2_array;
	delete_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : delete_p;
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_immediate_g2_list_sequence;  /* read-immediate-g2-list-sequence */

/* READ-IMMEDIATE-G2-LIST-SEQUENCE */
Object g2int_read_immediate_g2_list_sequence(g2_list,delete_p)
    Object g2_list, delete_p;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(48,24);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_immediate_g2_list_sequence,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_immediate_g2_list_sequence,top,Nil);
	}
	g2_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : g2_list;
	delete_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : delete_p;
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* REPLACE-G2-LIST-ELEMENT */
Object g2int_replace_g2_list_element(element_structure,item_or_datum_qm,
	    allow_no_value_p,element_type,delete_p)
    Object element_structure, item_or_datum_qm, allow_no_value_p, element_type;
    Object delete_p;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(48,25);
    PUSH_SPECIAL(G2int_allow_no_value_p,allow_no_value_p,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* MAYBE-INSERT-G2-LIST-ELEMENT-AT-END */
Object g2int_maybe_insert_g2_list_element_at_end(item_or_datum_qm,g2_list,
	    allow_no_value_p,element_type)
    Object item_or_datum_qm, g2_list, allow_no_value_p, element_type;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(48,26);
    PUSH_SPECIAL(G2int_allow_no_value_p,allow_no_value_p,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

Object G2int_corresponding_icp_object_index_for_item_new_copy = UNBOUND;

Object G2int_item_being_read_for_new_reference = UNBOUND;

static Object Qg2int_context;      /* context */

static Object list_constant_8;     /* # */

static Object Qg2int_gsi_name_is_identifying_flag;  /* gsi-name-is-identifying-flag */

static Object Qg2int_effective_data_type;  /* effective-data-type */

static Object Qg2int_class;        /* class */

static Object Qg2int_read_icp_item_new_copy;  /* read-icp-item-new-copy */

static Object Qg2int_resumable_icp_list_end;  /* resumable-icp-list-end */

static Object Qg2int_true;         /* true */

static Object Qg2int_false;        /* false */

/* READ-ICP-ITEM-NEW-COPY */
Object g2int_read_icp_item_new_copy()
{
    Object current_computation_flags, new_index, interned_list, temp;
    Object interned_class, attribute_name_list, class_1;
    Object attribute_description_list, attribute, ab_loop_list_;
    Object gsi_special_attributes_count, use_bound_value_for_item_new_copy_p;
    Object owner, instance, item_new_copy, temp_1, names, gsi_item;
    Object gsi_instance_extension, attributes, element_type, i, attribute_name;
    Object identifying_attribute_p, gsi_remote_value_creates_instance_p;
    Object make_gsi_instance_existing_instance, value, base_name;
    Object class_qualified_name_qm, attribute_spec, new_attributes;
    Object name_attribute, resumable_icp_state_1, icp_suspend_1, top, value_1;
    Object all_attributes_count_1, attribute_count_1;
    Object item_with_identifying_attributes_p_1, key, test, arg1, arg2;
    SI_Long all_attributes_count, ab_loopvar_, attribute_count, temp_2, i_1;
    SI_Long ab_loop_bind_;
    char item_with_identifying_attributes_p, temp_3;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,27);
    if (G2int_disable_resumability) {
	current_computation_flags = G2int_current_computation_flags;
	PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		1);
	  new_index = 
		  g2int_assign_index_in_index_space(g2int_ensure_item_copy_index_space());
	  interned_list = g2int_read_icp_interned_list_as_value_type();
	  temp = ISVREF(interned_list,(SI_Long)1L);
	  interned_class = CAR(temp);
	  temp = ISVREF(interned_list,(SI_Long)1L);
	  attribute_name_list = CDR(temp);
	  class_1 = interned_class;
	  attribute_description_list = Nil;
	  all_attributes_count = IFIX(length(attribute_name_list));
	  attribute = Nil;
	  ab_loop_list_ = attribute_name_list;
	  ab_loopvar_ = (SI_Long)0L;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  attribute = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (g2int_gsi_special_attribute_p(attribute))
	      ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  gsi_special_attributes_count = FIX(ab_loopvar_);
	  goto end;
	  gsi_special_attributes_count = Qnil;
	end:;
	  attribute_count = all_attributes_count - 
		  IFIX(gsi_special_attributes_count);
	  use_bound_value_for_item_new_copy_p = Nil;
	  owner = G2int_identifying_attribute_count_for_item_new_copy ? 
		  Qg2int_context : g2int_default_owner_for_gsi_objects();
	  instance = g2int_make_gsi_instance(6,G2int_gsi_null_type_tag,Nil,
		  g2int_gsi_make_attributes_for_user_or_gsi(FIX(attribute_count),
		  owner),class_1,Nil,owner);
	  if (G2int_corresponding_icp_object_index_for_item_new_copy) {
	      g2int_store_corresponding_item(G2int_corresponding_icp_object_index_for_item_new_copy,
		      instance);
	      G2int_corresponding_icp_object_index_for_item_new_copy = Nil;
	  }
	  if (owner &&  !TRUEP(G2int_item_being_read_for_new_reference))
	      G2int_item_being_read_for_new_reference = instance;
	  item_new_copy = instance;
	  if (FIXNUM_GE(new_index,ISVREF(G2int_item_copy_index_space,
		  (SI_Long)4L)))
	      g2int_enlarge_index_space(G2int_item_copy_index_space,new_index);
	  temp_1 = ISVREF(ISVREF(G2int_item_copy_index_space,(SI_Long)2L),
		  IFIX(new_index) >>  -  - (SI_Long)10L);
	  temp_2 = IFIX(new_index) & (SI_Long)1023L;
	  ISVREF(temp_1,temp_2) = item_new_copy;
	  item_with_identifying_attributes_p = 
		  EQ(G2int_item_being_read_for_new_reference,item_new_copy);
	  names = Nil;
	  gsi_item = item_new_copy;
	  if (gsi_item) {
	      gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	      attributes = gsi_instance_extension ? 
		      ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
	  }
	  else
	      attributes = Nil;
	  element_type = Nil;
	  i = G2int_gsi_magic_offset;
	  attribute_name = Nil;
	  ab_loop_list_ = attribute_name_list;
	  identifying_attribute_p = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  attribute_name = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  identifying_attribute_p = item_with_identifying_attributes_p ? 
		  ((SI_Long)0L < 
		  IFIX(G2int_identifying_attribute_count_for_item_new_copy) 
		  ? T : Nil) : Qnil;
	  if (EQ(attribute_name,Qg2int_names)) {
	      if (g2int_memq_function(g2int_peek_icp_byte(),list_constant_8))
		  names = g2int_read_icp_remote_value();
	      else {
		  gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
		  if ( !TRUEP(gsi_instance_extension)) {
		      gsi_instance_extension = 
			      g2int_make_gsi_instance_extension_1();
		      SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			      gsi_instance_extension;
		  }
		  gsi_remote_value_creates_instance_p = Nil;
		  PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
			  0);
		    temp_1 = g2int_read_icp_remote_value();
		  POP_SPECIAL();
		  SVREF(gsi_instance_extension,FIX((SI_Long)4L)) = temp_1;
		  if (identifying_attribute_p)
		      g2int_set_gsi_instance_plist_value(item_new_copy,
			      Qg2int_gsi_name_is_identifying_flag,T);
	      }
	  }
	  else if (EQ(attribute_name,Qg2int_value)) {
	      make_gsi_instance_existing_instance = gsi_item;
	      PUSH_SPECIAL(G2int_make_gsi_instance_existing_instance,make_gsi_instance_existing_instance,
		      0);
		g2int_read_icp_remote_value();
	      POP_SPECIAL();
	  }
	  else if (EQ(attribute_name,Qg2int_value_structure_using_unix_time))
	      g2int_read_gsi_value_structure(item_new_copy);
	  else if (EQ(attribute_name,Qg2int_element_type))
	      element_type = g2int_read_icp_symbol_as_value_type();
	  else if (EQ(attribute_name,Qg2int_g2_array_sequence))
	      g2int_read_sequence_into_gsi_item(item_new_copy,element_type,
		      Qarray);
	  else if (EQ(attribute_name,Qg2int_g2_list_sequence))
	      g2int_read_sequence_into_gsi_item(item_new_copy,element_type,
		      Qlist);
	  else if (EQ(attribute_name,Qg2int_effective_data_type))
	      g2int_read_gsi_effective_data_type_into_item(item_new_copy);
	  else if (EQ(attribute_name,Qg2int_history_keeping_spec)) {
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			  gsi_instance_extension;
	      }
	      temp_1 = g2int_read_gsi_history_specification();
	      SVREF(gsi_instance_extension,FIX((SI_Long)12L)) = temp_1;
	  }
	  else if (EQ(attribute_name,Qg2int_history_using_unix_time)) {
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      g2int_read_gsi_history(gsi_instance_extension ? 
		      ISVREF(gsi_instance_extension,(SI_Long)12L) : Nil,
		      item_new_copy);
	  }
	  else if (EQ(attribute_name,Qg2int_class)) {
	      gsi_remote_value_creates_instance_p = Nil;
	      PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		      0);
		g2int_read_icp_remote_value();
	      POP_SPECIAL();
	  }
	  else {
	      value = g2int_read_icp_remote_value();
	      attribute = ISVREF(attributes,IFIX(i));
	      if (CONSP(attribute_name)) {
		  base_name = CONSP(attribute_name) ? 
			  THIRD(attribute_name) : attribute_name;
		  class_qualified_name_qm = CONSP(attribute_name) ? 
			  SECOND(attribute_name) : Nil;
		  attribute_spec = ISVREF(attribute,(SI_Long)1L);
		  M_THIRD(attribute_spec) = base_name;
		  M_SECOND(attribute_spec) = class_qualified_name_qm;
	      }
	      else
		  g2int_set_gsi_attribute_name(attribute,attribute_name);
	      SVREF(attribute,FIX((SI_Long)4L)) = value;
	      if (identifying_attribute_p)
		  g2int_set_gsi_attribute_is_identifying_p(attribute,T);
	      i = FIXNUM_ADD1(i);
	  }
	  if (identifying_attribute_p) {
	      temp_1 = 
		      FIXNUM_SUB1(G2int_identifying_attribute_count_for_item_new_copy);
	      G2int_identifying_attribute_count_for_item_new_copy = temp_1;
	  }
	  goto next_loop_1;
	end_loop_1:
	  if (names && item_new_copy) {
	      temp = FIX(attribute_count + (SI_Long)1L);
	      new_attributes = g2int_gsi_make_array_for_user_or_gsi(temp,
		      g2int_default_owner_for_gsi_objects());
	      name_attribute = 
		      g2int_make_gsi_attribute_for_user_or_gsi(g2int_default_owner_for_gsi_objects());
	      SVREF(new_attributes,G2int_gsi_magic_offset) = name_attribute;
	      SVREF(name_attribute,FIX((SI_Long)4L)) = names;
	      i_1 = IFIX(G2int_gsi_magic_offset);
	      ab_loop_bind_ = attribute_count + (SI_Long)1L;
	    next_loop_2:
	      if (i_1 >= ab_loop_bind_)
		  goto end_loop_2;
	      temp_2 = i_1 + (SI_Long)1L;
	      temp_1 = ISVREF(attributes,i_1);
	      ISVREF(new_attributes,temp_2) = temp_1;
	      i_1 = i_1 + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:;
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			  gsi_instance_extension;
	      }
	      SVREF(gsi_instance_extension,FIX((SI_Long)8L)) = new_attributes;
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			  gsi_instance_extension;
	      }
	      temp_2 = attribute_count + (SI_Long)1L;
	      ISVREF(gsi_instance_extension,(SI_Long)9L) = FIX(temp_2);
	  }
	  temp = item_new_copy;
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_item_new_copy,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_item_new_copy,top,Nil);
		goto end_read_icp_item_new_copy;
	    }
	}
	current_computation_flags = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : G2int_current_computation_flags;
	PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		1);
	  new_index = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_assign_index_in_index_space(g2int_ensure_item_copy_index_space());
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      interned_list = g2int_resumable_icp_pop();
	  else {
	      value_1 = g2int_read_icp_interned_list_as_value_type();
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	      interned_list = value_1;
	  }
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      interned_class = g2int_resumable_icp_pop();
	  else {
	      temp = ISVREF(interned_list,(SI_Long)1L);
	      interned_class = CAR(temp);
	  }
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      attribute_name_list = g2int_resumable_icp_pop();
	  else {
	      temp = ISVREF(interned_list,(SI_Long)1L);
	      attribute_name_list = CDR(temp);
	  }
	  class_1 = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : interned_class;
	  attribute_description_list = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : Nil;
	  all_attributes_count_1 = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : length(attribute_name_list);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      gsi_special_attributes_count = g2int_resumable_icp_pop();
	  else {
	      attribute = Nil;
	      ab_loop_list_ = attribute_name_list;
	      ab_loopvar_ = (SI_Long)0L;
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_3;
	      attribute = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (g2int_gsi_special_attribute_p(attribute))
		  ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	      goto next_loop_3;
	    end_loop_3:
	      gsi_special_attributes_count = FIX(ab_loopvar_);
	      goto end_1;
	      gsi_special_attributes_count = Qnil;
	    end_1:;
	  }
	  attribute_count_1 = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  FIXNUM_MINUS(all_attributes_count_1,
		  gsi_special_attributes_count);
	  use_bound_value_for_item_new_copy_p = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : Nil;
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      item_new_copy = g2int_resumable_icp_pop();
	  else {
	      owner = G2int_identifying_attribute_count_for_item_new_copy ?
		       Qg2int_context : g2int_default_owner_for_gsi_objects();
	      instance = g2int_make_gsi_instance(6,G2int_gsi_null_type_tag,
		      Nil,
		      g2int_gsi_make_attributes_for_user_or_gsi(attribute_count_1,
		      owner),class_1,Nil,owner);
	      if (G2int_corresponding_icp_object_index_for_item_new_copy) {
		  g2int_store_corresponding_item(G2int_corresponding_icp_object_index_for_item_new_copy,
			  instance);
		  G2int_corresponding_icp_object_index_for_item_new_copy = Nil;
	      }
	      if (owner &&  !TRUEP(G2int_item_being_read_for_new_reference))
		  G2int_item_being_read_for_new_reference = instance;
	      item_new_copy = instance;
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))) {
	      if (FIXNUM_GE(new_index,ISVREF(G2int_item_copy_index_space,
		      (SI_Long)4L)))
		  g2int_enlarge_index_space(G2int_item_copy_index_space,
			  new_index);
	      temp_1 = ISVREF(ISVREF(G2int_item_copy_index_space,
		      (SI_Long)2L),IFIX(new_index) >>  -  - (SI_Long)10L);
	      temp_2 = IFIX(new_index) & (SI_Long)1023L;
	      ISVREF(temp_1,temp_2) = item_new_copy;
	  }
	  item_with_identifying_attributes_p_1 = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  EQ(G2int_item_being_read_for_new_reference,
		  item_new_copy) ? T : Nil;
	  names = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : Nil;
	  gsi_item = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : item_new_copy;
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      attributes = g2int_resumable_icp_pop();
	  else if (gsi_item) {
	      gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	      attributes = gsi_instance_extension ? 
		      ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
	  }
	  else
	      attributes = Nil;
	  element_type = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : Nil;
	  i = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : G2int_gsi_magic_offset;
	  attribute_name = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : Nil;
	  ab_loop_list_ = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : attribute_name_list;
	  identifying_attribute_p = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : Nil;
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	      goto resume;
	next_loop_4:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_4;
	  attribute_name = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  identifying_attribute_p = item_with_identifying_attributes_p_1 ? 
		  ((SI_Long)0L < 
		  IFIX(G2int_identifying_attribute_count_for_item_new_copy) 
		  ? T : Nil) : Qnil;
	resume:
	  key = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : attribute_name;
	  if (EQ(key,Qg2int_names)) {
	      test = Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  test = g2int_resumable_icp_pop();
		  temp_3 = TRUEP(test);
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      if (temp_3)
		  temp_3 = EQ(test,Qg2int_true);
	      else {
		  if ((resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		      arg1 = g2int_resumable_icp_pop();
		  else {
		      value_1 = g2int_peek_icp_byte();
		      if (EQ(icp_suspend_1,value_1)) {
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(Nil);
			  g2int_resumable_icp_push(key);
			  g2int_resumable_icp_push(identifying_attribute_p);
			  g2int_resumable_icp_push(ab_loop_list_);
			  g2int_resumable_icp_push(attribute_name);
			  g2int_resumable_icp_push(i);
			  g2int_resumable_icp_push(element_type);
			  g2int_resumable_icp_push(attributes);
			  g2int_resumable_icp_push(gsi_item);
			  g2int_resumable_icp_push(names);
			  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
			  g2int_resumable_icp_push(item_new_copy);
			  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
			  g2int_resumable_icp_push(attribute_count_1);
			  g2int_resumable_icp_push(gsi_special_attributes_count);
			  g2int_resumable_icp_push(all_attributes_count_1);
			  g2int_resumable_icp_push(attribute_description_list);
			  g2int_resumable_icp_push(class_1);
			  g2int_resumable_icp_push(attribute_name_list);
			  g2int_resumable_icp_push(interned_class);
			  g2int_resumable_icp_push(interned_list);
			  g2int_resumable_icp_push(new_index);
			  g2int_resumable_icp_push(G2int_current_computation_flags);
			  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
			  result = VALUES_1(G2int_icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_item_new_copy;
		      }
		      arg1 = value_1;
		  }
		  arg2 = (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? g2int_resumable_icp_pop() : list_constant_8;
		  temp_3 = TRUEP(g2int_memq_function(arg1,arg2));
	      }
	      if (temp_3) {
		  value_1 = g2int_read_icp_remote_value();
		  if (EQ(icp_suspend_1,value_1)) {
		      g2int_resumable_icp_push(Qg2int_true);
		      g2int_resumable_icp_push(key);
		      g2int_resumable_icp_push(identifying_attribute_p);
		      g2int_resumable_icp_push(ab_loop_list_);
		      g2int_resumable_icp_push(attribute_name);
		      g2int_resumable_icp_push(i);
		      g2int_resumable_icp_push(element_type);
		      g2int_resumable_icp_push(attributes);
		      g2int_resumable_icp_push(gsi_item);
		      g2int_resumable_icp_push(names);
		      g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		      g2int_resumable_icp_push(item_new_copy);
		      g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		      g2int_resumable_icp_push(attribute_count_1);
		      g2int_resumable_icp_push(gsi_special_attributes_count);
		      g2int_resumable_icp_push(all_attributes_count_1);
		      g2int_resumable_icp_push(attribute_description_list);
		      g2int_resumable_icp_push(class_1);
		      g2int_resumable_icp_push(attribute_name_list);
		      g2int_resumable_icp_push(interned_class);
		      g2int_resumable_icp_push(interned_list);
		      g2int_resumable_icp_push(new_index);
		      g2int_resumable_icp_push(G2int_current_computation_flags);
		      g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		      result = VALUES_1(G2int_icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_item_new_copy;
		  }
		  names = value_1;
	      }
	      else if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) || T) {
		  gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
		  if ( !TRUEP(gsi_instance_extension)) {
		      gsi_instance_extension = 
			      g2int_make_gsi_instance_extension_1();
		      SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			      gsi_instance_extension;
		  }
		  gsi_remote_value_creates_instance_p = 
			  (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? g2int_resumable_icp_pop() : Nil;
		  PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
			  0);
		    value_1 = g2int_read_icp_remote_value();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(identifying_attribute_p);
			g2int_resumable_icp_push(ab_loop_list_);
			g2int_resumable_icp_push(attribute_name);
			g2int_resumable_icp_push(i);
			g2int_resumable_icp_push(element_type);
			g2int_resumable_icp_push(attributes);
			g2int_resumable_icp_push(gsi_item);
			g2int_resumable_icp_push(names);
			g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
			g2int_resumable_icp_push(item_new_copy);
			g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
			g2int_resumable_icp_push(attribute_count_1);
			g2int_resumable_icp_push(gsi_special_attributes_count);
			g2int_resumable_icp_push(all_attributes_count_1);
			g2int_resumable_icp_push(attribute_description_list);
			g2int_resumable_icp_push(class_1);
			g2int_resumable_icp_push(attribute_name_list);
			g2int_resumable_icp_push(interned_class);
			g2int_resumable_icp_push(interned_list);
			g2int_resumable_icp_push(new_index);
			g2int_resumable_icp_push(G2int_current_computation_flags);
			g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
			result = VALUES_1(G2int_icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_read_icp_item_new_copy;
		    }
		  POP_SPECIAL();
		  SVREF(gsi_instance_extension,FIX((SI_Long)4L)) = value_1;
		  if (identifying_attribute_p)
		      g2int_set_gsi_instance_plist_value(item_new_copy,
			      Qg2int_gsi_name_is_identifying_flag,T);
	      }
	  }
	  else if (EQ(key,Qg2int_value)) {
	      make_gsi_instance_existing_instance = (resumable_icp_state_1 
		      ? TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : gsi_item;
	      PUSH_SPECIAL(G2int_make_gsi_instance_existing_instance,make_gsi_instance_existing_instance,
		      0);
		if (EQ(icp_suspend_1,g2int_read_icp_remote_value())) {
		    g2int_resumable_icp_push(G2int_make_gsi_instance_existing_instance);
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(identifying_attribute_p);
		    g2int_resumable_icp_push(ab_loop_list_);
		    g2int_resumable_icp_push(attribute_name);
		    g2int_resumable_icp_push(i);
		    g2int_resumable_icp_push(element_type);
		    g2int_resumable_icp_push(attributes);
		    g2int_resumable_icp_push(gsi_item);
		    g2int_resumable_icp_push(names);
		    g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		    g2int_resumable_icp_push(item_new_copy);
		    g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		    g2int_resumable_icp_push(attribute_count_1);
		    g2int_resumable_icp_push(gsi_special_attributes_count);
		    g2int_resumable_icp_push(all_attributes_count_1);
		    g2int_resumable_icp_push(attribute_description_list);
		    g2int_resumable_icp_push(class_1);
		    g2int_resumable_icp_push(attribute_name_list);
		    g2int_resumable_icp_push(interned_class);
		    g2int_resumable_icp_push(interned_list);
		    g2int_resumable_icp_push(new_index);
		    g2int_resumable_icp_push(G2int_current_computation_flags);
		    g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		    result = VALUES_1(G2int_icp_suspend);
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_read_icp_item_new_copy;
		}
	      POP_SPECIAL();
	  }
	  else if (EQ(key,Qg2int_value_structure_using_unix_time)) {
	      if (EQ(icp_suspend_1,
		      g2int_read_gsi_value_structure(item_new_copy))) {
		  g2int_resumable_icp_push(key);
		  g2int_resumable_icp_push(identifying_attribute_p);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(attribute_name);
		  g2int_resumable_icp_push(i);
		  g2int_resumable_icp_push(element_type);
		  g2int_resumable_icp_push(attributes);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(names);
		  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		  g2int_resumable_icp_push(item_new_copy);
		  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		  g2int_resumable_icp_push(attribute_count_1);
		  g2int_resumable_icp_push(gsi_special_attributes_count);
		  g2int_resumable_icp_push(all_attributes_count_1);
		  g2int_resumable_icp_push(attribute_description_list);
		  g2int_resumable_icp_push(class_1);
		  g2int_resumable_icp_push(attribute_name_list);
		  g2int_resumable_icp_push(interned_class);
		  g2int_resumable_icp_push(interned_list);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	  }
	  else if (EQ(key,Qg2int_element_type)) {
	      value_1 = g2int_read_icp_symbol_as_value_type();
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(key);
		  g2int_resumable_icp_push(identifying_attribute_p);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(attribute_name);
		  g2int_resumable_icp_push(i);
		  g2int_resumable_icp_push(element_type);
		  g2int_resumable_icp_push(attributes);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(names);
		  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		  g2int_resumable_icp_push(item_new_copy);
		  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		  g2int_resumable_icp_push(attribute_count_1);
		  g2int_resumable_icp_push(gsi_special_attributes_count);
		  g2int_resumable_icp_push(all_attributes_count_1);
		  g2int_resumable_icp_push(attribute_description_list);
		  g2int_resumable_icp_push(class_1);
		  g2int_resumable_icp_push(attribute_name_list);
		  g2int_resumable_icp_push(interned_class);
		  g2int_resumable_icp_push(interned_list);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	      element_type = value_1;
	  }
	  else if (EQ(key,Qg2int_g2_array_sequence)) {
	      if (EQ(icp_suspend_1,
		      g2int_read_sequence_into_gsi_item(item_new_copy,
		      element_type,Qarray))) {
		  g2int_resumable_icp_push(key);
		  g2int_resumable_icp_push(identifying_attribute_p);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(attribute_name);
		  g2int_resumable_icp_push(i);
		  g2int_resumable_icp_push(element_type);
		  g2int_resumable_icp_push(attributes);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(names);
		  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		  g2int_resumable_icp_push(item_new_copy);
		  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		  g2int_resumable_icp_push(attribute_count_1);
		  g2int_resumable_icp_push(gsi_special_attributes_count);
		  g2int_resumable_icp_push(all_attributes_count_1);
		  g2int_resumable_icp_push(attribute_description_list);
		  g2int_resumable_icp_push(class_1);
		  g2int_resumable_icp_push(attribute_name_list);
		  g2int_resumable_icp_push(interned_class);
		  g2int_resumable_icp_push(interned_list);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	  }
	  else if (EQ(key,Qg2int_g2_list_sequence)) {
	      if (EQ(icp_suspend_1,
		      g2int_read_sequence_into_gsi_item(item_new_copy,
		      element_type,Qlist))) {
		  g2int_resumable_icp_push(key);
		  g2int_resumable_icp_push(identifying_attribute_p);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(attribute_name);
		  g2int_resumable_icp_push(i);
		  g2int_resumable_icp_push(element_type);
		  g2int_resumable_icp_push(attributes);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(names);
		  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		  g2int_resumable_icp_push(item_new_copy);
		  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		  g2int_resumable_icp_push(attribute_count_1);
		  g2int_resumable_icp_push(gsi_special_attributes_count);
		  g2int_resumable_icp_push(all_attributes_count_1);
		  g2int_resumable_icp_push(attribute_description_list);
		  g2int_resumable_icp_push(class_1);
		  g2int_resumable_icp_push(attribute_name_list);
		  g2int_resumable_icp_push(interned_class);
		  g2int_resumable_icp_push(interned_list);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	  }
	  else if (EQ(key,Qg2int_effective_data_type)) {
	      if (EQ(icp_suspend_1,
		      g2int_read_gsi_effective_data_type_into_item(item_new_copy))) 
			  {
		  g2int_resumable_icp_push(key);
		  g2int_resumable_icp_push(identifying_attribute_p);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(attribute_name);
		  g2int_resumable_icp_push(i);
		  g2int_resumable_icp_push(element_type);
		  g2int_resumable_icp_push(attributes);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(names);
		  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		  g2int_resumable_icp_push(item_new_copy);
		  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		  g2int_resumable_icp_push(attribute_count_1);
		  g2int_resumable_icp_push(gsi_special_attributes_count);
		  g2int_resumable_icp_push(all_attributes_count_1);
		  g2int_resumable_icp_push(attribute_description_list);
		  g2int_resumable_icp_push(class_1);
		  g2int_resumable_icp_push(attribute_name_list);
		  g2int_resumable_icp_push(interned_class);
		  g2int_resumable_icp_push(interned_list);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	  }
	  else if (EQ(key,Qg2int_history_keeping_spec)) {
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			  gsi_instance_extension;
	      }
	      value_1 = g2int_read_gsi_history_specification();
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(key);
		  g2int_resumable_icp_push(identifying_attribute_p);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(attribute_name);
		  g2int_resumable_icp_push(i);
		  g2int_resumable_icp_push(element_type);
		  g2int_resumable_icp_push(attributes);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(names);
		  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		  g2int_resumable_icp_push(item_new_copy);
		  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		  g2int_resumable_icp_push(attribute_count_1);
		  g2int_resumable_icp_push(gsi_special_attributes_count);
		  g2int_resumable_icp_push(all_attributes_count_1);
		  g2int_resumable_icp_push(attribute_description_list);
		  g2int_resumable_icp_push(class_1);
		  g2int_resumable_icp_push(attribute_name_list);
		  g2int_resumable_icp_push(interned_class);
		  g2int_resumable_icp_push(interned_list);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	      SVREF(gsi_instance_extension,FIX((SI_Long)12L)) = value_1;
	  }
	  else if (EQ(key,Qg2int_history_using_unix_time)) {
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      if (EQ(icp_suspend_1,
		      g2int_read_gsi_history(gsi_instance_extension ? 
		      ISVREF(gsi_instance_extension,(SI_Long)12L) : Nil,
		      item_new_copy))) {
		  g2int_resumable_icp_push(key);
		  g2int_resumable_icp_push(identifying_attribute_p);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(attribute_name);
		  g2int_resumable_icp_push(i);
		  g2int_resumable_icp_push(element_type);
		  g2int_resumable_icp_push(attributes);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(names);
		  g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		  g2int_resumable_icp_push(item_new_copy);
		  g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		  g2int_resumable_icp_push(attribute_count_1);
		  g2int_resumable_icp_push(gsi_special_attributes_count);
		  g2int_resumable_icp_push(all_attributes_count_1);
		  g2int_resumable_icp_push(attribute_description_list);
		  g2int_resumable_icp_push(class_1);
		  g2int_resumable_icp_push(attribute_name_list);
		  g2int_resumable_icp_push(interned_class);
		  g2int_resumable_icp_push(interned_list);
		  g2int_resumable_icp_push(new_index);
		  g2int_resumable_icp_push(G2int_current_computation_flags);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_new_copy;
	      }
	  }
	  else if (EQ(key,Qg2int_class)) {
	      gsi_remote_value_creates_instance_p = (resumable_icp_state_1 
		      ? TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		      0);
		if (EQ(icp_suspend_1,g2int_read_icp_remote_value())) {
		    g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(identifying_attribute_p);
		    g2int_resumable_icp_push(ab_loop_list_);
		    g2int_resumable_icp_push(attribute_name);
		    g2int_resumable_icp_push(i);
		    g2int_resumable_icp_push(element_type);
		    g2int_resumable_icp_push(attributes);
		    g2int_resumable_icp_push(gsi_item);
		    g2int_resumable_icp_push(names);
		    g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		    g2int_resumable_icp_push(item_new_copy);
		    g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		    g2int_resumable_icp_push(attribute_count_1);
		    g2int_resumable_icp_push(gsi_special_attributes_count);
		    g2int_resumable_icp_push(all_attributes_count_1);
		    g2int_resumable_icp_push(attribute_description_list);
		    g2int_resumable_icp_push(class_1);
		    g2int_resumable_icp_push(attribute_name_list);
		    g2int_resumable_icp_push(interned_class);
		    g2int_resumable_icp_push(interned_list);
		    g2int_resumable_icp_push(new_index);
		    g2int_resumable_icp_push(G2int_current_computation_flags);
		    g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		    result = VALUES_1(G2int_icp_suspend);
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_read_icp_item_new_copy;
		}
	      POP_SPECIAL();
	  }
	  else {
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  value = g2int_resumable_icp_pop();
	      else {
		  value_1 = g2int_read_icp_remote_value();
		  if (EQ(icp_suspend_1,value_1)) {
		      g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		      g2int_resumable_icp_push(key);
		      g2int_resumable_icp_push(identifying_attribute_p);
		      g2int_resumable_icp_push(ab_loop_list_);
		      g2int_resumable_icp_push(attribute_name);
		      g2int_resumable_icp_push(i);
		      g2int_resumable_icp_push(element_type);
		      g2int_resumable_icp_push(attributes);
		      g2int_resumable_icp_push(gsi_item);
		      g2int_resumable_icp_push(names);
		      g2int_resumable_icp_push(item_with_identifying_attributes_p_1);
		      g2int_resumable_icp_push(item_new_copy);
		      g2int_resumable_icp_push(use_bound_value_for_item_new_copy_p);
		      g2int_resumable_icp_push(attribute_count_1);
		      g2int_resumable_icp_push(gsi_special_attributes_count);
		      g2int_resumable_icp_push(all_attributes_count_1);
		      g2int_resumable_icp_push(attribute_description_list);
		      g2int_resumable_icp_push(class_1);
		      g2int_resumable_icp_push(attribute_name_list);
		      g2int_resumable_icp_push(interned_class);
		      g2int_resumable_icp_push(interned_list);
		      g2int_resumable_icp_push(new_index);
		      g2int_resumable_icp_push(G2int_current_computation_flags);
		      g2int_resumable_icp_push(Qg2int_read_icp_item_new_copy);
		      result = VALUES_1(G2int_icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_item_new_copy;
		  }
		  value = value_1;
	      }
	      attribute = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : ISVREF(attributes,IFIX(i));
	      if (CONSP(attribute_name)) {
		  base_name = CONSP(attribute_name) ? 
			  THIRD(attribute_name) : attribute_name;
		  class_qualified_name_qm = CONSP(attribute_name) ? 
			  SECOND(attribute_name) : Nil;
		  attribute_spec = ISVREF(attribute,(SI_Long)1L);
		  M_THIRD(attribute_spec) = base_name;
		  M_SECOND(attribute_spec) = class_qualified_name_qm;
	      }
	      else
		  g2int_set_gsi_attribute_name(attribute,attribute_name);
	      SVREF(attribute,FIX((SI_Long)4L)) = value;
	      if (identifying_attribute_p)
		  g2int_set_gsi_attribute_is_identifying_p(attribute,T);
	      i = FIXNUM_ADD1(i);
	  }
	  if (identifying_attribute_p) {
	      temp_1 = 
		      FIXNUM_SUB1(G2int_identifying_attribute_count_for_item_new_copy);
	      G2int_identifying_attribute_count_for_item_new_copy = temp_1;
	  }
	  goto next_loop_4;
	end_loop_4:
	  if (names && item_new_copy) {
	      temp = FIXNUM_ADD1(attribute_count_1);
	      new_attributes = g2int_gsi_make_array_for_user_or_gsi(temp,
		      g2int_default_owner_for_gsi_objects());
	      name_attribute = 
		      g2int_make_gsi_attribute_for_user_or_gsi(g2int_default_owner_for_gsi_objects());
	      SVREF(new_attributes,G2int_gsi_magic_offset) = name_attribute;
	      SVREF(name_attribute,FIX((SI_Long)4L)) = names;
	      i_1 = IFIX(G2int_gsi_magic_offset);
	      ab_loop_bind_ = IFIX(FIXNUM_ADD1(attribute_count_1));
	    next_loop_5:
	      if (i_1 >= ab_loop_bind_)
		  goto end_loop_5;
	      temp_2 = i_1 + (SI_Long)1L;
	      temp_1 = ISVREF(attributes,i_1);
	      ISVREF(new_attributes,temp_2) = temp_1;
	      i_1 = i_1 + (SI_Long)1L;
	      goto next_loop_5;
	    end_loop_5:;
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			  gsi_instance_extension;
	      }
	      SVREF(gsi_instance_extension,FIX((SI_Long)8L)) = new_attributes;
	      gsi_instance_extension = ISVREF(item_new_copy,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(item_new_copy,FIX((SI_Long)3L)) = 
			  gsi_instance_extension;
	      }
	      temp_1 = FIXNUM_ADD1(attribute_count_1);
	      SVREF(gsi_instance_extension,FIX((SI_Long)9L)) = temp_1;
	  }
	  temp = item_new_copy;
	POP_SPECIAL();
    }
    result = VALUES_1(temp);
  end_read_icp_item_new_copy:
    return result;
}

static Object string_constant_1;   /* "Expected a value-structure" */

static Object Qg2int_data_point_value;  /* data-point-value */

static Object Qg2int_data_point_collection_time;  /* data-point-collection-time */

static Object Qg2int_data_point_expiration_time;  /* data-point-expiration-time */

static Object Qg2int_read_gsi_value_structure;  /* read-gsi-value-structure */

/* READ-GSI-VALUE-STRUCTURE */
Object g2int_read_gsi_value_structure(gsi_item)
    Object gsi_item;
{
    Object temp, list_1, name, ab_loop_list_;
    Object make_gsi_instance_existing_instance;
    Object gsi_remote_value_creates_instance_p, value, gsi_instance_extension;
    Object resumable_icp_state_1, icp_suspend_1, top, test, arg1, arg2;
    Object value_1, v1, v2, v3;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,28);
    if (G2int_disable_resumability) {
	if (EQ(FIX((SI_Long)0L),g2int_peek_icp_byte())) {
	    g2int_read_icp_byte();
	    temp = Nil;
	}
	else {
	    if ( !EQ(g2int_read_icp_byte(),FIX((SI_Long)50L)))
		return g2int_icp_error_internal(Qerror,string_constant_1,
			Nil,Nil,Nil);
	    list_1 = ISVREF(g2int_read_icp_interned_list_as_value_type(),
		    (SI_Long)1L);
	    name = Nil;
	    ab_loop_list_ = list_1;
	    make_gsi_instance_existing_instance = Nil;
	    PUSH_SPECIAL(G2int_make_gsi_instance_existing_instance,make_gsi_instance_existing_instance,
		    1);
	      gsi_remote_value_creates_instance_p = Nil;
	      PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		      0);
		value = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		name = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		G2int_make_gsi_instance_existing_instance = EQ(name,
			Qg2int_data_point_value) ? gsi_item : Nil;
		G2int_gsi_remote_value_creates_instance_p =  ! 
			!TRUEP(G2int_make_gsi_instance_existing_instance) ?
			 T : Nil;
		value = g2int_read_icp_remote_value();
		if (EQ(name,Qg2int_data_point_value));
		else if (EQ(name,Qg2int_data_point_collection_time)) {
		    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
		    if ( !TRUEP(gsi_instance_extension)) {
			gsi_instance_extension = 
				g2int_make_gsi_instance_extension_1();
			SVREF(gsi_item,FIX((SI_Long)3L)) = 
				gsi_instance_extension;
		    }
		    SVREF(gsi_instance_extension,FIX((SI_Long)10L)) = value;
		}
		else if (EQ(name,Qg2int_data_point_expiration_time)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L)
			g2int_reclaim_managed_simple_float_array_of_length_1(value);
		}
		goto next_loop;
	      end_loop:
		temp = Qnil;
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_gsi_value_structure,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_gsi_value_structure,top,Nil);
	}
	gsi_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_item;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp_1 = EQ(test,Qg2int_true);
	else {
	    arg1 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX((SI_Long)0L);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg2 = g2int_resumable_icp_pop();
	    else {
		value_1 = g2int_peek_icp_byte();
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(Nil);
		    g2int_resumable_icp_push(gsi_item);
		    g2int_resumable_icp_push(Qg2int_read_gsi_value_structure);
		    return VALUES_1(G2int_icp_suspend);
		}
		arg2 = value_1;
	    }
	    temp_1 = EQ(arg1,arg2);
	}
	if (temp_1) {
	    if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(gsi_item);
		g2int_resumable_icp_push(Qg2int_read_gsi_value_structure);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = Nil;
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp_1 = EQ(test,Qg2int_true);
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Nil);
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block;
			}
			arg1 = value_1;
		    }
		    arg2 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : FIX((SI_Long)50L);
		    arg1 = EQ(arg1,arg2) ? T : Nil;
		}
		temp_1 =  !TRUEP(arg1);
	    }
	    if (temp_1) {
		value_1 = g2int_icp_error_internal(Qerror,
			string_constant_1,Nil,Nil,Nil);
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		return VALUES_1(value_1);
	    }
	  l2:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		list_1 = g2int_resumable_icp_pop();
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value_1 = g2int_read_icp_interned_list_as_value_type();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		    arg1 = value_1;
		}
		arg2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : FIX((SI_Long)1L);
		list_1 = ISVREF(arg1,IFIX(arg2));
	    }
	    name = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    ab_loop_list_ = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : list_1;
	    make_gsi_instance_existing_instance = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_make_gsi_instance_existing_instance,make_gsi_instance_existing_instance,
		    1);
	      gsi_remote_value_creates_instance_p = (resumable_icp_state_1 
		      ? TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		      0);
		value = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		    goto resume;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		name = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		G2int_make_gsi_instance_existing_instance = EQ(name,
			Qg2int_data_point_value) ? gsi_item : Nil;
		G2int_gsi_remote_value_creates_instance_p =  ! 
			!TRUEP(G2int_make_gsi_instance_existing_instance) ?
			 T : Nil;
	      resume:
		value_1 = g2int_read_icp_remote_value();
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(value);
		    g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
		    g2int_resumable_icp_push(G2int_make_gsi_instance_existing_instance);
		    g2int_resumable_icp_push(ab_loop_list_);
		    g2int_resumable_icp_push(name);
		    g2int_resumable_icp_push(list_1);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_block;
		}
		value = value_1;
		if (EQ(name,Qg2int_data_point_value));
		else if (EQ(name,Qg2int_data_point_collection_time)) {
		    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
		    if ( !TRUEP(gsi_instance_extension)) {
			gsi_instance_extension = 
				g2int_make_gsi_instance_extension_1();
			SVREF(gsi_item,FIX((SI_Long)3L)) = 
				gsi_instance_extension;
		    }
		    SVREF(gsi_instance_extension,FIX((SI_Long)10L)) = value;
		}
		else if (EQ(name,Qg2int_data_point_expiration_time)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L)
			g2int_reclaim_managed_simple_float_array_of_length_1(value);
		}
		goto next_loop_1;
	      end_loop_1:
		result = VALUES_1(Qnil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(gsi_item);
		g2int_resumable_icp_push(Qg2int_read_gsi_value_structure);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

Object G2int_data_point_value_interned_list = UNBOUND;

Object G2int_data_point_value_and_collection_time_interned_list = UNBOUND;

static Object Qg2int_write_gsi_value_structure;  /* write-gsi-value-structure */

/* WRITE-GSI-VALUE-STRUCTURE */
Object g2int_write_gsi_value_structure(gsi_item)
    Object gsi_item;
{
    Object temp, gsi_instance_extension, collection_time;
    Object write_value_of_gsi_item_p, resumable_icp_state_1, icp_suspend_1;
    Object top, test, value, v1, v2, v3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,29);
    if (G2int_disable_resumability) {
	if ( !TRUEP(ISVREF(gsi_item,(SI_Long)2L)))
	    temp = g2int_write_icp_byte(FIX((SI_Long)0L));
	else {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    collection_time = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)10L) : Nil;
	    g2int_write_icp_byte(FIX((SI_Long)50L));
	    g2int_write_icp_interned_list_as_value_type(collection_time ? 
		    G2int_data_point_value_and_collection_time_interned_list 
		    : G2int_data_point_value_interned_list);
	    write_value_of_gsi_item_p = T;
	    PUSH_SPECIAL(G2int_write_value_of_gsi_item_p,write_value_of_gsi_item_p,
		    0);
	      g2int_write_icp_remote_value(gsi_item);
	    POP_SPECIAL();
	    temp = collection_time ? 
		    g2int_write_icp_remote_value(collection_time) : Nil;
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_gsi_value_structure,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_gsi_value_structure,top,Nil);
	}
	gsi_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_item;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) :  !TRUEP(ISVREF(gsi_item,
		(SI_Long)2L))) {
	    value = g2int_write_icp_byte(FIX((SI_Long)0L));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(gsi_item);
		g2int_resumable_icp_push(Qg2int_write_gsi_value_structure);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		collection_time = g2int_resumable_icp_pop();
	    else {
		gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
		collection_time = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)10L) : Nil;
	    }
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1;
			break;
		      case 2:
			goto l2;
			break;
		      case 3:
			goto l3;
			break;
		      case 4:
			goto l4;
			break;
		      default:
			break;
		    }
	    }
	  l1:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)50L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l2:
	    if (EQ(icp_suspend_1,
		    g2int_write_icp_interned_list_as_value_type(collection_time 
		    ? 
		    G2int_data_point_value_and_collection_time_interned_list 
		    : G2int_data_point_value_interned_list))) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l3:
	    write_value_of_gsi_item_p = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : T;
	    PUSH_SPECIAL(G2int_write_value_of_gsi_item_p,write_value_of_gsi_item_p,
		    0);
	      if (EQ(icp_suspend_1,g2int_write_icp_remote_value(gsi_item))) {
		  g2int_resumable_icp_push(G2int_write_value_of_gsi_item_p);
		  g2int_resumable_icp_push(FIX((SI_Long)3L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	    POP_SPECIAL();
	  l4:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || collection_time) {
		value = g2int_write_icp_remote_value(collection_time);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)4L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		result = VALUES_1(value);
	    }
	    else
		result = VALUES_1(Nil);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(collection_time);
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(gsi_item);
		g2int_resumable_icp_push(Qg2int_write_gsi_value_structure);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

static Object list_constant_9;     /* # */

static Object Qg2int_read_sequence_into_gsi_item;  /* read-sequence-into-gsi-item */

/* READ-SEQUENCE-INTO-GSI-ITEM */
Object g2int_read_sequence_into_gsi_item(gsi_item,element_type,array_or_list)
    Object gsi_item, element_type, array_or_list;
{
    Object temp, value_type, typetag, length_1, remote_value_known_typetag;
    Object array, gsi_instance_extension, gsi_remote_value_creates_instance_p;
    Object value, symbol, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top, test, arg1, arg2, value_1, key;
    SI_Long index_1, ab_loop_bind_, temp_1, i;
    char temp_2;
    double aref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,30);
    if (G2int_disable_resumability) {
	if (EQ(FIX((SI_Long)0L),g2int_peek_icp_byte())) {
	    g2int_read_icp_byte();
	    temp = Nil;
	}
	else {
	    if (EQ(array_or_list,Qarray)) {
		if (EQ(element_type,Qg2int_item_or_value))
		    value_type = FIX((SI_Long)25L);
		else if (EQ(element_type,Qg2int_value))
		    value_type = FIX((SI_Long)24L);
		else if (EQ(element_type,Qg2int_quantity))
		    value_type = FIX((SI_Long)26L);
		else if (EQ(element_type,Qg2int_text))
		    value_type = FIX((SI_Long)20L);
		else if (EQ(element_type,Qg2int_truth_value))
		    value_type = FIX((SI_Long)21L);
		else if (EQ(element_type,Qsymbol))
		    value_type = FIX((SI_Long)19L);
		else if (EQ(element_type,Qfloat))
		    value_type = FIX((SI_Long)22L);
		else if (EQ(element_type,Qinteger))
		    value_type = FIX((SI_Long)17L);
		else
		    value_type = FIX((SI_Long)23L);
	    }
	    else if (EQ(array_or_list,Qlist)) {
		if (EQ(element_type,Qg2int_item_or_value))
		    value_type = FIX((SI_Long)41L);
		else if (EQ(element_type,Qg2int_value))
		    value_type = FIX((SI_Long)40L);
		else if (EQ(element_type,Qg2int_quantity))
		    value_type = FIX((SI_Long)42L);
		else if (EQ(element_type,Qg2int_text))
		    value_type = FIX((SI_Long)36L);
		else if (EQ(element_type,Qg2int_truth_value))
		    value_type = FIX((SI_Long)37L);
		else if (EQ(element_type,Qsymbol))
		    value_type = FIX((SI_Long)35L);
		else if (EQ(element_type,Qfloat))
		    value_type = FIX((SI_Long)38L);
		else if (EQ(element_type,Qinteger))
		    value_type = FIX((SI_Long)33L);
		else
		    value_type = FIX((SI_Long)39L);
	    }
	    else
		value_type = Qnil;
	    g2int_set_gsi_instance_value_type(gsi_item,value_type);
	    temp = g2int_read_icp_byte();
	    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		    FIXNUM_LE(temp,FIX((SI_Long)127L))))
		typetag = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 67:
		    typetag = g2int_read_icp_byte();
		    break;
		  case 49:
		    typetag = FIX((SI_Long)8L);
		    break;
		  default:
		    typetag = Nil;
		    break;
		}
	    length_1 = g2int_read_icp_fixnum();
	    element_type = g2int_memq_function(element_type,
		    list_constant_9) ? element_type : Nil;
	    remote_value_known_typetag = IFIX(typetag) == (SI_Long)8L ? 
		    Nil : typetag;
	    PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		    1);
	      array = g2int_gsi_make_appropriate_array(3,value_type,
		      length_1,gsi_item);
	      SVREF(gsi_item,FIX((SI_Long)2L)) = array;
	      gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	      if ( !TRUEP(gsi_instance_extension)) {
		  gsi_instance_extension = 
			  g2int_make_gsi_instance_extension_1();
		  SVREF(gsi_item,FIX((SI_Long)3L)) = gsi_instance_extension;
	      }
	      SVREF(gsi_instance_extension,FIX((SI_Long)7L)) = length_1;
	      if (element_type) {
		  gsi_remote_value_creates_instance_p = Nil;
		  PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
			  0);
		    index_1 = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(length_1);
		    value = Nil;
		  next_loop:
		    if (index_1 >= ab_loop_bind_)
			goto end_loop;
		    value = g2int_read_icp_remote_value();
		    if (EQ(element_type,Qinteger)) {
			temp_1 = IFIX(value);
			BYTE_32_ISASET_1(array,index_1,temp_1);
		    }
		    else if (EQ(element_type,Qg2int_truth_value)) {
			temp_1 = IFIX(value);
			BYTE_32_ISASET_1(array,index_1,temp_1);
		    }
		    else if (EQ(element_type,Qfloat)) {
			aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
			DFLOAT_ISASET_1(array,index_1,aref_new_value);
			g2int_reclaim_managed_simple_float_array_of_length_1(value);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			symbol = value;
			svref_new_value = 
				g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
				? symbol : 
				inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
				G2int_gsi_wide_api_p));
			ISVREF(array,index_1) = svref_new_value;
		    }
		    else if (EQ(element_type,Qg2int_text)) {
			svref_new_value = inline_extract_c_string(value);
			ISVREF(array,index_1) = svref_new_value;
		    }
		    index_1 = index_1 + (SI_Long)1L;
		    goto next_loop;
		  end_loop:
		    temp = Qnil;
		  POP_SPECIAL();
	      }
	      else {
		  i = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(length_1);
		next_loop_1:
		  if (i >= ab_loop_bind_)
		      goto end_loop_1;
		  temp_1 = i + (SI_Long)1L;
		  svref_new_value = g2int_read_icp_remote_value();
		  ISVREF(array,temp_1) = svref_new_value;
		  i = i + (SI_Long)1L;
		  goto next_loop_1;
		end_loop_1:
		  temp = Qnil;
	      }
	    POP_SPECIAL();
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_sequence_into_gsi_item,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_sequence_into_gsi_item,top,Nil);
		goto end_read_sequence_into_gsi_item;
	    }
	}
	gsi_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_item;
	element_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : element_type;
	array_or_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : array_or_list;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_2 = TRUEP(test);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    temp_2 = EQ(test,Qg2int_true);
	else {
	    arg1 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX((SI_Long)0L);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg2 = g2int_resumable_icp_pop();
	    else {
		value_1 = g2int_peek_icp_byte();
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(Nil);
		    g2int_resumable_icp_push(array_or_list);
		    g2int_resumable_icp_push(element_type);
		    g2int_resumable_icp_push(gsi_item);
		    g2int_resumable_icp_push(Qg2int_read_sequence_into_gsi_item);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_read_sequence_into_gsi_item;
		}
		arg2 = value_1;
	    }
	    temp_2 = EQ(arg1,arg2);
	}
	if (temp_2) {
	    if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(array_or_list);
		g2int_resumable_icp_push(element_type);
		g2int_resumable_icp_push(gsi_item);
		g2int_resumable_icp_push(Qg2int_read_sequence_into_gsi_item);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_sequence_into_gsi_item;
	    }
	    temp = Nil;
	}
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		value_type = g2int_resumable_icp_pop();
	    else {
		key = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : array_or_list;
		if (EQ(key,Qarray)) {
		    if (EQ(element_type,Qg2int_item_or_value))
			value_type = FIX((SI_Long)25L);
		    else if (EQ(element_type,Qg2int_value))
			value_type = FIX((SI_Long)24L);
		    else if (EQ(element_type,Qg2int_quantity))
			value_type = FIX((SI_Long)26L);
		    else if (EQ(element_type,Qg2int_text))
			value_type = FIX((SI_Long)20L);
		    else if (EQ(element_type,Qg2int_truth_value))
			value_type = FIX((SI_Long)21L);
		    else if (EQ(element_type,Qsymbol))
			value_type = FIX((SI_Long)19L);
		    else if (EQ(element_type,Qfloat))
			value_type = FIX((SI_Long)22L);
		    else if (EQ(element_type,Qinteger))
			value_type = FIX((SI_Long)17L);
		    else
			value_type = FIX((SI_Long)23L);
		}
		else if (EQ(key,Qlist)) {
		    if (EQ(element_type,Qg2int_item_or_value))
			value_type = FIX((SI_Long)41L);
		    else if (EQ(element_type,Qg2int_value))
			value_type = FIX((SI_Long)40L);
		    else if (EQ(element_type,Qg2int_quantity))
			value_type = FIX((SI_Long)42L);
		    else if (EQ(element_type,Qg2int_text))
			value_type = FIX((SI_Long)36L);
		    else if (EQ(element_type,Qg2int_truth_value))
			value_type = FIX((SI_Long)37L);
		    else if (EQ(element_type,Qsymbol))
			value_type = FIX((SI_Long)35L);
		    else if (EQ(element_type,Qfloat))
			value_type = FIX((SI_Long)38L);
		    else if (EQ(element_type,Qinteger))
			value_type = FIX((SI_Long)33L);
		    else
			value_type = FIX((SI_Long)39L);
		}
		else
		    value_type = Qnil;
	    }
	    if ( !(resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)))
		g2int_set_gsi_instance_value_type(gsi_item,value_type);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		typetag = g2int_resumable_icp_pop();
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    key = g2int_resumable_icp_pop();
		else {
		    value_1 = g2int_read_icp_byte();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(value_type);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(array_or_list);
			g2int_resumable_icp_push(element_type);
			g2int_resumable_icp_push(gsi_item);
			g2int_resumable_icp_push(Qg2int_read_sequence_into_gsi_item);
			result = VALUES_1(G2int_icp_suspend);
			goto end_read_sequence_into_gsi_item;
		    }
		    key = value_1;
		}
		if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) 
			&& FIXNUM_LE(key,FIX((SI_Long)127L))))
		    typetag = Nil;
		else
		    switch (INTEGER_TO_CHAR(key)) {
		      case 67:
			value_1 = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(value_type);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(array_or_list);
			    g2int_resumable_icp_push(element_type);
			    g2int_resumable_icp_push(gsi_item);
			    g2int_resumable_icp_push(Qg2int_read_sequence_into_gsi_item);
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_read_sequence_into_gsi_item;
			}
			typetag = value_1;
			break;
		      case 49:
			typetag = FIX((SI_Long)8L);
			break;
		      default:
			typetag = Nil;
			break;
		    }
	    }
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		length_1 = g2int_resumable_icp_pop();
	    else {
		value_1 = g2int_read_icp_fixnum();
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(typetag);
		    g2int_resumable_icp_push(value_type);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(array_or_list);
		    g2int_resumable_icp_push(element_type);
		    g2int_resumable_icp_push(gsi_item);
		    g2int_resumable_icp_push(Qg2int_read_sequence_into_gsi_item);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_read_sequence_into_gsi_item;
		}
		length_1 = value_1;
	    }
	    element_type = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : 
		    g2int_memq_function(element_type,list_constant_9) ? 
		    element_type : Nil;
	    remote_value_known_typetag = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : IFIX(typetag) == 
		    (SI_Long)8L ? Nil : typetag;
	    PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		    1);
	      array = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      g2int_gsi_make_appropriate_array(3,value_type,
		      length_1,gsi_item);
	      if ( !(resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))) {
		  SVREF(gsi_item,FIX((SI_Long)2L)) = array;
		  gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
		  if ( !TRUEP(gsi_instance_extension)) {
		      gsi_instance_extension = 
			      g2int_make_gsi_instance_extension_1();
		      SVREF(gsi_item,FIX((SI_Long)3L)) = 
			      gsi_instance_extension;
		  }
		  SVREF(gsi_instance_extension,FIX((SI_Long)7L)) = length_1;
	      }
	      test = Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  test = g2int_resumable_icp_pop();
		  temp_2 = TRUEP(test);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2 ? EQ(test,Qg2int_true) : TRUEP(element_type)) {
		  gsi_remote_value_creates_instance_p = 
			  (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? g2int_resumable_icp_pop() : Nil;
		  PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
			  0);
		    index_1 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
		    ab_loop_bind_ = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
		    value = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil))
			goto resume;
		  next_loop_2:
		    if (index_1 >= ab_loop_bind_)
			goto end_loop_2;
		  resume:
		    value_1 = g2int_read_icp_remote_value();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(value);
			g2int_resumable_icp_push(FIX(ab_loop_bind_));
			g2int_resumable_icp_push(FIX(index_1));
			g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(array);
			g2int_resumable_icp_push(G2int_remote_value_known_typetag);
			g2int_resumable_icp_push(element_type);
			g2int_resumable_icp_push(length_1);
			g2int_resumable_icp_push(typetag);
			g2int_resumable_icp_push(value_type);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(array_or_list);
			g2int_resumable_icp_push(element_type);
			g2int_resumable_icp_push(gsi_item);
			g2int_resumable_icp_push(Qg2int_read_sequence_into_gsi_item);
			result = VALUES_1(G2int_icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_read_sequence_into_gsi_item;
		    }
		    value = value_1;
		    if (EQ(element_type,Qinteger)) {
			temp_1 = IFIX(value);
			BYTE_32_ISASET_1(array,index_1,temp_1);
		    }
		    else if (EQ(element_type,Qg2int_truth_value)) {
			temp_1 = IFIX(value);
			BYTE_32_ISASET_1(array,index_1,temp_1);
		    }
		    else if (EQ(element_type,Qfloat)) {
			aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
			DFLOAT_ISASET_1(array,index_1,aref_new_value);
			g2int_reclaim_managed_simple_float_array_of_length_1(value);
		    }
		    else if (EQ(element_type,Qsymbol)) {
			symbol = value;
			svref_new_value = 
				g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
				? symbol : 
				inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
				G2int_gsi_wide_api_p));
			ISVREF(array,index_1) = svref_new_value;
		    }
		    else if (EQ(element_type,Qg2int_text)) {
			svref_new_value = inline_extract_c_string(value);
			ISVREF(array,index_1) = svref_new_value;
		    }
		    index_1 = index_1 + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:
		    temp = Qnil;
		  POP_SPECIAL();
	      }
	      else {
		  i = (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
		  ab_loop_bind_ = (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
		  if (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil))
		      goto resume_1;
		next_loop_3:
		  if (i >= ab_loop_bind_)
		      goto end_loop_3;
		resume_1:
		  temp_1 = i + (SI_Long)1L;
		  value_1 = g2int_read_icp_remote_value();
		  if (EQ(icp_suspend_1,value_1)) {
		      g2int_resumable_icp_push(FIX(ab_loop_bind_));
		      g2int_resumable_icp_push(FIX(i));
		      g2int_resumable_icp_push(Qg2int_false);
		      g2int_resumable_icp_push(array);
		      g2int_resumable_icp_push(G2int_remote_value_known_typetag);
		      g2int_resumable_icp_push(element_type);
		      g2int_resumable_icp_push(length_1);
		      g2int_resumable_icp_push(typetag);
		      g2int_resumable_icp_push(value_type);
		      g2int_resumable_icp_push(Qg2int_false);
		      g2int_resumable_icp_push(array_or_list);
		      g2int_resumable_icp_push(element_type);
		      g2int_resumable_icp_push(gsi_item);
		      g2int_resumable_icp_push(Qg2int_read_sequence_into_gsi_item);
		      result = VALUES_1(G2int_icp_suspend);
		      POP_SPECIAL();
		      goto end_read_sequence_into_gsi_item;
		  }
		  ISVREF(array,temp_1) = value_1;
		  i = i + (SI_Long)1L;
		  goto next_loop_3;
		end_loop_3:
		  temp = Qnil;
	      }
	    POP_SPECIAL();
	}
    }
    result = VALUES_1(temp);
  end_read_sequence_into_gsi_item:
    return result;
}

static Object list_constant_10;    /* # */

static Object Qg2int_long;         /* long */

static Object Qg2int_unsigned_short_vector;  /* unsigned-short-vector */

static Object array_constant_2;    /* # */

static Object string_constant_2;   /* "" */

static Object Qg2int_gensym;       /* gensym */

static Object Qg2int_write_sequence_from_gsi_item;  /* write-sequence-from-gsi-item */

/* WRITE-SEQUENCE-FROM-GSI-ITEM */
Object g2int_write_sequence_from_gsi_item(gsi_item,element_type)
    Object gsi_item, element_type;
{
    Object gsi_instance_extension, length_1, array, known_type, type, typetag;
    Object remote_value_known_typetag, value, element;
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top, test, v1, v2, v3;
    SI_Long i, ab_loop_bind_;
    char temp_2;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,31);
    if (G2int_disable_resumability) {
	gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	length_1 = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)7L) : FIX((SI_Long)0L);
	array = ISVREF(gsi_item,(SI_Long)2L);
	known_type = g2int_memq_function(element_type,list_constant_10) ? 
		element_type : Nil;
	type = known_type;
	if (EQ(type,Qnull))
	    typetag = FIX((SI_Long)0L);
	else if (EQ(type,Qinteger))
	    typetag = FIX((SI_Long)1L);
	else if (EQ(type,Qg2int_long))
	    typetag = FIX((SI_Long)51L);
	else if (EQ(type,Qg2int_truth_value))
	    typetag = FIX((SI_Long)5L);
	else if (EQ(type,Qfloat))
	    typetag = FIX((SI_Long)6L);
	else if (EQ(type,Qg2int_text))
	    typetag = FIX((SI_Long)4L);
	else if (EQ(type,Qg2int_unsigned_short_vector))
	    typetag = FIX((SI_Long)11L);
	else
	    typetag = Nil;
	remote_value_known_typetag = typetag;
	PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		0);
	  if (typetag) {
	      g2int_write_icp_byte(FIX((SI_Long)67L));
	      g2int_write_icp_byte(typetag);
	  }
	  else
	      g2int_write_icp_byte(FIX((SI_Long)49L));
	  g2int_write_icp_fixnum(length_1);
	  if (array) {
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_1);
	      value = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      if (EQ(element_type,Qg2int_text)) {
		  element = ISVREF(array,i);
		  value =  !TRUEP(element) ? (G2int_gsi_wide_api_p ? 
			  array_constant_2 : string_constant_2) : 
			  G2int_gsi_wide_api_p ? 
			  inline_restore_lisp_text_string(element) : 
			  inline_restore_lisp_gensym_string(element);
	      }
	      else if (EQ(element_type,Qg2int_truth_value))
		  value = FIX(BYTE_32_ISAREF_1(array,i));
	      else if (EQ(element_type,Qsymbol)) {
		  element = ISVREF(array,i);
		  value = 
			  g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			  ? element :  !TRUEP(element) ? Nil : 
			  g2int_symbol_for_gsi_string(G2int_gsi_wide_api_p 
			  ? g2int_c_wide_string_to_text_string(element) : 
			  g2int_c_string_to_gensym_string(element));
	      }
	      else if (EQ(element_type,Qfloat)) {
		  amf_available_array_cons_qm = 
			  ISVREF(G2int_vector_of_simple_float_array_pools,
			  (SI_Long)1L);
		  if (amf_available_array_cons_qm) {
		      amf_array = M_CAR(amf_available_array_cons_qm);
		      temp = G2int_vector_of_simple_float_array_pools;
		      svref_new_value = M_CDR(amf_available_array_cons_qm);
		      SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		      inline_note_reclaim_cons(amf_available_array_cons_qm,
			      Qg2int_gensym);
		      temp = G2int_available_gensym_conses;
		      M_CDR(amf_available_array_cons_qm) = temp;
		      G2int_available_gensym_conses = 
			      amf_available_array_cons_qm;
		      amf_result = amf_array;
		  }
		  else {
		      temp = 
			      FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		      G2int_created_simple_float_array_pool_arrays = temp;
		      incff_1_arg = 
			      g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		      temp = 
			      FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			      incff_1_arg);
		      G2int_simple_float_array_pool_memory_usage = temp;
		      amf_result = 
			      g2int_generate_float_vector(FIX((SI_Long)1L));
		  }
		  new_float = amf_result;
		  aref_new_value = DFLOAT_ISAREF_1(array,i);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  value = new_float;
	      }
	      else if (EQ(element_type,Qinteger))
		  value = FIX(BYTE_32_ISAREF_1(array,i));
	      else
		  value = ISVREF(array,i + (SI_Long)1L);
	      g2int_write_icp_remote_value(value);
	      if (EQ(element_type,Qfloat))
		  g2int_reclaim_managed_simple_float_array_of_length_1(value);
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      temp_1 = Qnil;
	  }
	  else
	      temp_1 = Nil;
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_sequence_from_gsi_item,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_sequence_from_gsi_item,top,Nil);
		goto end_write_sequence_from_gsi_item;
	    }
	}
	gsi_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_item;
	element_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : element_type;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    length_1 = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    length_1 = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)7L) : 
		    FIX((SI_Long)0L);
	}
	array = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : ISVREF(gsi_item,(SI_Long)2L);
	known_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		g2int_memq_function(element_type,list_constant_10) ? 
		element_type : Nil;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    typetag = g2int_resumable_icp_pop();
	else {
	    type = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : known_type;
	    if (EQ(type,Qnull))
		typetag = FIX((SI_Long)0L);
	    else if (EQ(type,Qinteger))
		typetag = FIX((SI_Long)1L);
	    else if (EQ(type,Qg2int_long))
		typetag = FIX((SI_Long)51L);
	    else if (EQ(type,Qg2int_truth_value))
		typetag = FIX((SI_Long)5L);
	    else if (EQ(type,Qfloat))
		typetag = FIX((SI_Long)6L);
	    else if (EQ(type,Qg2int_text))
		typetag = FIX((SI_Long)4L);
	    else if (EQ(type,Qg2int_unsigned_short_vector))
		typetag = FIX((SI_Long)11L);
	    else
		typetag = Nil;
	}
	remote_value_known_typetag = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : typetag;
	PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		0);
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  test = Nil;
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      test = g2int_resumable_icp_pop();
	      temp_2 = TRUEP(test);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ? EQ(test,Qg2int_true) : TRUEP(typetag)) {
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  temp_1 = g2int_resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	      if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)67L)))) {
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	    l2_1:
	      if (EQ(icp_suspend_1,g2int_write_icp_byte(typetag))) {
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  g2int_resumable_icp_push(Qg2int_true);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	  }
	  else if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		      || T) {
	      if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)49L)))) {
		  g2int_resumable_icp_push(Qg2int_false);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	  }
	l2:
	  if (EQ(icp_suspend_1,g2int_write_icp_fixnum(length_1))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      result = VALUES_1(G2int_icp_suspend);
	      goto end_block_1;
	  }
	l3:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  || array) {
	      i = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	      ab_loop_bind_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
	      value = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		  goto resume;
	    next_loop_1:
	      if (i >= ab_loop_bind_)
		  goto end_loop_1;
	      if (EQ(element_type,Qg2int_text)) {
		  element = ISVREF(array,i);
		  value =  !TRUEP(element) ? (G2int_gsi_wide_api_p ? 
			  array_constant_2 : string_constant_2) : 
			  G2int_gsi_wide_api_p ? 
			  inline_restore_lisp_text_string(element) : 
			  inline_restore_lisp_gensym_string(element);
	      }
	      else if (EQ(element_type,Qg2int_truth_value))
		  value = FIX(BYTE_32_ISAREF_1(array,i));
	      else if (EQ(element_type,Qsymbol)) {
		  element = ISVREF(array,i);
		  value = 
			  g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			  ? element :  !TRUEP(element) ? Nil : 
			  g2int_symbol_for_gsi_string(G2int_gsi_wide_api_p 
			  ? g2int_c_wide_string_to_text_string(element) : 
			  g2int_c_string_to_gensym_string(element));
	      }
	      else if (EQ(element_type,Qfloat)) {
		  amf_available_array_cons_qm = 
			  ISVREF(G2int_vector_of_simple_float_array_pools,
			  (SI_Long)1L);
		  if (amf_available_array_cons_qm) {
		      amf_array = M_CAR(amf_available_array_cons_qm);
		      temp = G2int_vector_of_simple_float_array_pools;
		      svref_new_value = M_CDR(amf_available_array_cons_qm);
		      SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		      inline_note_reclaim_cons(amf_available_array_cons_qm,
			      Qg2int_gensym);
		      temp = G2int_available_gensym_conses;
		      M_CDR(amf_available_array_cons_qm) = temp;
		      G2int_available_gensym_conses = 
			      amf_available_array_cons_qm;
		      amf_result = amf_array;
		  }
		  else {
		      temp = 
			      FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		      G2int_created_simple_float_array_pool_arrays = temp;
		      incff_1_arg = 
			      g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		      temp = 
			      FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			      incff_1_arg);
		      G2int_simple_float_array_pool_memory_usage = temp;
		      amf_result = 
			      g2int_generate_float_vector(FIX((SI_Long)1L));
		  }
		  new_float = amf_result;
		  aref_new_value = DFLOAT_ISAREF_1(array,i);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  value = new_float;
	      }
	      else if (EQ(element_type,Qinteger))
		  value = FIX(BYTE_32_ISAREF_1(array,i));
	      else
		  value = ISVREF(array,i + (SI_Long)1L);
	    resume:
	      if (EQ(icp_suspend_1,g2int_write_icp_remote_value(value))) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX(ab_loop_bind_));
		  g2int_resumable_icp_push(FIX(i));
		  g2int_resumable_icp_push(FIX((SI_Long)3L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	      if (EQ(element_type,Qfloat))
		  g2int_reclaim_managed_simple_float_array_of_length_1(value);
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      result = VALUES_1(Qnil);
	  }
	  else
	      result = VALUES_1(Nil);
	  goto end_block_1;
	end_block_1:
	  MVS_3(result,v1,v2,v3);
	  if (EQ(icp_suspend_1,v1)) {
	      g2int_resumable_icp_push(G2int_remote_value_known_typetag);
	      g2int_resumable_icp_push(typetag);
	      g2int_resumable_icp_push(known_type);
	      g2int_resumable_icp_push(array);
	      g2int_resumable_icp_push(length_1);
	      g2int_resumable_icp_push(element_type);
	      g2int_resumable_icp_push(gsi_item);
	      g2int_resumable_icp_push(Qg2int_write_sequence_from_gsi_item);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_write_sequence_from_gsi_item;
	  }
	  temp_1 = v1;
	POP_SPECIAL();
    }
    result = VALUES_1(temp_1);
  end_write_sequence_from_gsi_item:
    return result;
}

static Object string_constant_3;   /* "Expected a history specification" */

static Object Qg2int_maximum_number_of_data_points;  /* maximum-number-of-data-points */

static Object Qg2int_maximum_age_of_data_points;  /* maximum-age-of-data-points */

static Object Qg2int_minimum_interval_between_data_points;  /* minimum-interval-between-data-points */

static Object Qg2int_read_gsi_history_specification;  /* read-gsi-history-specification */

/* READ-GSI-HISTORY-SPECIFICATION */
Object g2int_read_gsi_history_specification()
{
    Object temp, maximum_number_of_data_points, maximum_age_of_data_points;
    Object minimum_interval_between_data_points, list_1;
    Object gsi_remote_value_creates_instance_p, name, ab_loop_list_, value;
    Object resumable_icp_state_1, icp_suspend_1, top, test, arg1, arg2;
    Object value_1, v1, v2, v3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,32);
    if (G2int_disable_resumability) {
	if (EQ(FIX((SI_Long)0L),g2int_peek_icp_byte())) {
	    g2int_read_icp_byte();
	    temp = Nil;
	}
	else {
	    if ( !EQ(g2int_read_icp_byte(),FIX((SI_Long)50L)))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Nil,Nil,Nil);
	    maximum_number_of_data_points = Nil;
	    maximum_age_of_data_points = Nil;
	    minimum_interval_between_data_points = Nil;
	    list_1 = ISVREF(g2int_read_icp_interned_list_as_value_type(),
		    (SI_Long)1L);
	    gsi_remote_value_creates_instance_p = Nil;
	    PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		    0);
	      name = Nil;
	      ab_loop_list_ = list_1;
	      value = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      name = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      value = g2int_read_icp_remote_value();
	      if (EQ(name,Qg2int_maximum_number_of_data_points))
		  maximum_number_of_data_points = value;
	      else if (EQ(name,Qg2int_maximum_age_of_data_points))
		  maximum_age_of_data_points = value;
	      else if (EQ(name,Qg2int_minimum_interval_between_data_points))
		  minimum_interval_between_data_points = value;
	      goto next_loop;
	    end_loop:;
	    POP_SPECIAL();
	    temp = 
		    g2int_make_gsi_history_from_specification(maximum_number_of_data_points,
		    maximum_age_of_data_points,
		    minimum_interval_between_data_points);
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_gsi_history_specification,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_gsi_history_specification,top,Nil);
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp_1 = EQ(test,Qg2int_true);
	else {
	    arg1 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX((SI_Long)0L);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg2 = g2int_resumable_icp_pop();
	    else {
		value_1 = g2int_peek_icp_byte();
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(Nil);
		    g2int_resumable_icp_push(Qg2int_read_gsi_history_specification);
		    return VALUES_1(G2int_icp_suspend);
		}
		arg2 = value_1;
	    }
	    temp_1 = EQ(arg1,arg2);
	}
	if (temp_1) {
	    if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(Qg2int_read_gsi_history_specification);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = Nil;
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp_1 = EQ(test,Qg2int_true);
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Nil);
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block;
			}
			arg1 = value_1;
		    }
		    arg2 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : FIX((SI_Long)50L);
		    arg1 = EQ(arg1,arg2) ? T : Nil;
		}
		temp_1 =  !TRUEP(arg1);
	    }
	    if (temp_1) {
		value_1 = g2int_icp_error_internal(Qerror,
			string_constant_3,Nil,Nil,Nil);
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		return VALUES_1(value_1);
	    }
	  l2:
	    maximum_number_of_data_points = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    maximum_age_of_data_points = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    minimum_interval_between_data_points = (resumable_icp_state_1 ?
		     TRUEP(G2int_starresumable_icp_statestar) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		list_1 = g2int_resumable_icp_pop();
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value_1 = g2int_read_icp_interned_list_as_value_type();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(minimum_interval_between_data_points);
			g2int_resumable_icp_push(maximum_age_of_data_points);
			g2int_resumable_icp_push(maximum_number_of_data_points);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		    arg1 = value_1;
		}
		arg2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : FIX((SI_Long)1L);
		list_1 = ISVREF(arg1,IFIX(arg2));
	    }
	    gsi_remote_value_creates_instance_p = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		    0);
	      name = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loop_list_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : list_1;
	      value = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		  goto resume;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      name = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	    resume:
	      value_1 = g2int_read_icp_remote_value();
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(ab_loop_list_);
		  g2int_resumable_icp_push(name);
		  g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
		  g2int_resumable_icp_push(list_1);
		  g2int_resumable_icp_push(minimum_interval_between_data_points);
		  g2int_resumable_icp_push(maximum_age_of_data_points);
		  g2int_resumable_icp_push(maximum_number_of_data_points);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	      value = value_1;
	      if (EQ(name,Qg2int_maximum_number_of_data_points))
		  maximum_number_of_data_points = value;
	      else if (EQ(name,Qg2int_maximum_age_of_data_points))
		  maximum_age_of_data_points = value;
	      else if (EQ(name,Qg2int_minimum_interval_between_data_points))
		  minimum_interval_between_data_points = value;
	      goto next_loop_1;
	    end_loop_1:;
	    POP_SPECIAL();
	    result = g2int_make_gsi_history_from_specification(maximum_number_of_data_points,
		    maximum_age_of_data_points,
		    minimum_interval_between_data_points);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(Qg2int_read_gsi_history_specification);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

Object G2int_attributes_of_history_specification_structure_as_interned_list = UNBOUND;

static Object Qg2int_write_gsi_history_specification;  /* write-gsi-history-specification */

/* WRITE-GSI-HISTORY-SPECIFICATION */
Object g2int_write_gsi_history_specification(history)
    Object history;
{
    Object history_spec, max_count_qm, max_age_qm, granularity_qm, temp;
    Object list_1, resumable_icp_state_1, icp_suspend_1, top, test;
    char temp_1;

    x_note_fn_call(48,33);
    if (G2int_disable_resumability) {
	if ( !TRUEP(history))
	    g2int_write_icp_byte(FIX((SI_Long)0L));
	else {
	    history_spec = ISVREF(history,(SI_Long)4L);
	    max_count_qm = SECOND(history_spec);
	    max_age_qm = THIRD(history_spec);
	    granularity_qm = FOURTH(history_spec);
	    temp = max_count_qm ? 
		    g2int_gensym_cons_1(Qg2int_maximum_number_of_data_points,
		    Nil) : Nil;
	    list_1 = nconc2(temp,nconc2(max_age_qm ? 
		    g2int_gensym_cons_1(Qg2int_maximum_age_of_data_points,
		    Nil) : Nil,granularity_qm ? 
		    g2int_gensym_cons_1(Qg2int_minimum_interval_between_data_points,
		    Nil) : Nil));
	    if (list_1) {
		g2int_write_icp_byte(FIX((SI_Long)50L));
		g2int_write_icp_interned_list_as_value_type(g2int_intern_list(list_1));
		g2int_reclaim_gensym_list_1(list_1);
		if (max_count_qm)
		    g2int_write_icp_remote_value(max_count_qm);
		if (max_age_qm)
		    g2int_write_icp_remote_value(max_age_qm);
		if (granularity_qm)
		    g2int_write_icp_remote_value(granularity_qm);
	    }
	    else
		g2int_write_icp_byte(FIX((SI_Long)0L));
	}
	temp = history;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_gsi_history_specification,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_gsi_history_specification,top,Nil);
	}
	history = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : history;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) :  !TRUEP(history)) {
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)0L)))) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(history);
		g2int_resumable_icp_push(Qg2int_write_gsi_history_specification);
		return VALUES_1(G2int_icp_suspend);
	    }
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    history_spec = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : ISVREF(history,(SI_Long)4L);
	    max_count_qm = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : SECOND(history_spec);
	    max_age_qm = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : THIRD(history_spec);
	    granularity_qm = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FOURTH(history_spec);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		list_1 = g2int_resumable_icp_pop();
	    else {
		temp = max_count_qm ? 
			g2int_gensym_cons_1(Qg2int_maximum_number_of_data_points,
			Nil) : Nil;
		list_1 = nconc2(temp,nconc2(max_age_qm ? 
			g2int_gensym_cons_1(Qg2int_maximum_age_of_data_points,
			Nil) : Nil,granularity_qm ? 
			g2int_gensym_cons_1(Qg2int_minimum_interval_between_data_points,
			Nil) : Nil));
	    }
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : TRUEP(list_1)) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
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
			  default:
			    break;
			}
		}
	      l1:
		if (EQ(icp_suspend_1,
			    g2int_write_icp_byte(FIX((SI_Long)50L)))) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    temp = G2int_icp_suspend;
		    goto end_block;
		}
	      l2:
		if (EQ(icp_suspend_1,
			g2int_write_icp_interned_list_as_value_type(g2int_intern_list(list_1)))) 
			    {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    temp = G2int_icp_suspend;
		    goto end_block;
		}
		g2int_reclaim_gensym_list_1(list_1);
	      l3:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) || max_count_qm) {
		    if (EQ(icp_suspend_1,
			    g2int_write_icp_remote_value(max_count_qm))) {
			g2int_resumable_icp_push(FIX((SI_Long)3L));
			temp = G2int_icp_suspend;
			goto end_block;
		    }
		}
	      l4:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) || max_age_qm) {
		    if (EQ(icp_suspend_1,
			    g2int_write_icp_remote_value(max_age_qm))) {
			g2int_resumable_icp_push(FIX((SI_Long)4L));
			temp = G2int_icp_suspend;
			goto end_block;
		    }
		}
	      l5:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) || granularity_qm) {
		    if (EQ(icp_suspend_1,
			    g2int_write_icp_remote_value(granularity_qm))) {
			g2int_resumable_icp_push(FIX((SI_Long)5L));
			temp = G2int_icp_suspend;
			goto end_block;
		    }
		    else
			temp = Nil;
		}
		else
		    temp = Nil;
		goto end_block;
	      end_block:
		if (EQ(icp_suspend_1,temp)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(list_1);
		    g2int_resumable_icp_push(granularity_qm);
		    g2int_resumable_icp_push(max_age_qm);
		    g2int_resumable_icp_push(max_count_qm);
		    g2int_resumable_icp_push(history_spec);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(history);
		    g2int_resumable_icp_push(Qg2int_write_gsi_history_specification);
		    return VALUES_1(G2int_icp_suspend);
		}
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)0L)))) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(list_1);
		    g2int_resumable_icp_push(granularity_qm);
		    g2int_resumable_icp_push(max_age_qm);
		    g2int_resumable_icp_push(max_count_qm);
		    g2int_resumable_icp_push(history_spec);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(history);
		    g2int_resumable_icp_push(Qg2int_write_gsi_history_specification);
		    return VALUES_1(G2int_icp_suspend);
		}
	    }
	}
	temp = history;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_gsi_effective_data_type_into_item;  /* read-gsi-effective-data-type-into-item */

/* READ-GSI-EFFECTIVE-DATA-TYPE-INTO-ITEM */
Object g2int_read_gsi_effective_data_type_into_item(gsi_item)
    Object gsi_item;
{
    Object gsi_remote_value_creates_instance_p, type, tag;
    Object gsi_instance_extension, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, value, key;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,34);
    if (G2int_disable_resumability) {
	gsi_remote_value_creates_instance_p = Nil;
	PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		0);
	  type = g2int_read_icp_remote_value();
	POP_SPECIAL();
	if (EQ(type,Qg2int_text))
	    tag = FIX((SI_Long)4L);
	else if (EQ(type,Qsymbol))
	    tag = FIX((SI_Long)3L);
	else if (EQ(type,Qfloat))
	    tag = FIX((SI_Long)6L);
	else if (EQ(type,Qinteger))
	    tag = FIX((SI_Long)1L);
	else if (EQ(type,Qg2int_truth_value))
	    tag = FIX((SI_Long)5L);
	else if (EQ(type,Qg2int_quantity))
	    tag = FIX((SI_Long)10L);
	else
	    tag = FIX((SI_Long)8L);
	gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(gsi_item,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	temp = SVREF(gsi_instance_extension,FIX((SI_Long)3L)) = tag;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_gsi_effective_data_type_into_item,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_gsi_effective_data_type_into_item,top,Nil);
		goto end_read_gsi_effective_data_type_into_item;
	    }
	}
	gsi_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_item;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    type = g2int_resumable_icp_pop();
	else {
	    gsi_remote_value_creates_instance_p = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		    0);
	      value = g2int_read_icp_remote_value();
	      if (EQ(icp_suspend_1,value)) {
		  g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
		  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		  g2int_resumable_icp_push(gsi_item);
		  g2int_resumable_icp_push(Qg2int_read_gsi_effective_data_type_into_item);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_gsi_effective_data_type_into_item;
	      }
	      type = value;
	    POP_SPECIAL();
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    tag = g2int_resumable_icp_pop();
	else {
	    key = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : type;
	    if (EQ(key,Qg2int_text))
		tag = FIX((SI_Long)4L);
	    else if (EQ(key,Qsymbol))
		tag = FIX((SI_Long)3L);
	    else if (EQ(key,Qfloat))
		tag = FIX((SI_Long)6L);
	    else if (EQ(key,Qinteger))
		tag = FIX((SI_Long)1L);
	    else if (EQ(key,Qg2int_truth_value))
		tag = FIX((SI_Long)5L);
	    else if (EQ(key,Qg2int_quantity))
		tag = FIX((SI_Long)10L);
	    else
		tag = FIX((SI_Long)8L);
	}
	gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(gsi_item,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	temp = SVREF(gsi_instance_extension,FIX((SI_Long)3L)) = tag;
    }
    result = VALUES_1(temp);
  end_read_gsi_effective_data_type_into_item:
    return result;
}

Object G2int_attributes_of_history_element_structure_as_interned_list = UNBOUND;

static Object string_constant_4;   /* "expected a history sequence" */

static Object string_constant_5;   /* "expected at least one element in the history" */

static Object string_constant_6;   /* "expected a history element structure" */

static Object Qg2int_read_gsi_history;  /* read-gsi-history */

/* READ-GSI-HISTORY */
Object g2int_read_gsi_history(history,item)
    Object history, item;
{
    Object temp, length_1, gsi_remote_value_creates_instance_p;
    Object gsi_instance_extension, type, values_1, timestamps, history_value;
    Object history_collection_time, svref_new_value, symbol;
    Object resumable_icp_state_1, icp_suspend_1, top, test, arg1, arg2, value;
    Object v1, v2, v3;
    SI_Long i, ab_loop_bind_, temp_2;
    char temp_1;
    double aref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,35);
    if (G2int_disable_resumability) {
	if (EQ(FIX((SI_Long)0L),g2int_peek_icp_byte())) {
	    g2int_read_icp_byte();
	    temp = history;
	}
	else {
	    if ( !EQ(g2int_read_icp_byte(),FIX((SI_Long)49L))) {
		result = g2int_icp_error_internal(Qerror,string_constant_4,
			Nil,Nil,Nil);
		goto end_read_gsi_history;
	    }
	    length_1 = g2int_read_icp_fixnum();
	    if ( !((SI_Long)1L <= IFIX(length_1))) {
		result = g2int_icp_error_internal(Qerror,string_constant_5,
			Nil,Nil,Nil);
		goto end_read_gsi_history;
	    }
	    g2int_add_vectors_to_gsi_history(length_1,history,item);
	    gsi_remote_value_creates_instance_p = Nil;
	    PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		    1);
	      gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	      type = gsi_instance_extension ? 
		      ISVREF(gsi_instance_extension,(SI_Long)3L) : 
		      FIX((SI_Long)0L);
	      values_1 = ISVREF(history,(SI_Long)2L);
	      timestamps = ISVREF(history,(SI_Long)3L);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_1);
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      if (EQ(g2int_read_icp_byte(),FIX((SI_Long)50L))) {
		  temp = g2int_read_icp_interned_list_as_value_type();
		  temp_1 = EQ(temp,
			  G2int_attributes_of_history_element_structure_as_interned_list);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if ( !temp_1) {
		  result = g2int_icp_error_internal(Qerror,
			  string_constant_6,Nil,Nil,Nil);
		  POP_SPECIAL();
		  goto end_read_gsi_history;
	      }
	      if ((SI_Long)8L == IFIX(type) || (SI_Long)10L == IFIX(type)) {
		  gsi_remote_value_creates_instance_p = T;
		  PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
			  0);
		    history_value = g2int_read_icp_remote_value();
		  POP_SPECIAL();
	      }
	      else
		  history_value = g2int_read_icp_remote_value();
	      history_collection_time = g2int_read_icp_remote_value();
	      if (! !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) 
		      && FIXNUM_LE(type,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(type)) {
		    case 1:
		      temp_2 = IFIX(history_value);
		      BYTE_32_ISASET_1(values_1,i,temp_2);
		      break;
		    case 5:
		      temp_2 = IFIX(history_value);
		      BYTE_32_ISASET_1(values_1,i,temp_2);
		      break;
		    case 6:
		      aref_new_value = DFLOAT_ISAREF_1(history_value,
			      (SI_Long)0L);
		      DFLOAT_ISASET_1(values_1,i,aref_new_value);
		      g2int_reclaim_managed_simple_float_array_of_length_1(history_value);
		      break;
		    case 4:
		      svref_new_value = inline_extract_c_string(history_value);
		      ISVREF(values_1,i) = svref_new_value;
		      break;
		    case 3:
		      symbol = history_value;
		      svref_new_value = 
			      g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			      ? symbol : 
			      inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
			      G2int_gsi_wide_api_p));
		      ISVREF(values_1,i) = svref_new_value;
		      break;
		    case 8:
		    case 10:
		      temp_2 = i + (SI_Long)1L;
		      ISVREF(values_1,temp_2) = history_value;
		      break;
		    default:
		      break;
		  }
	      aref_new_value = DFLOAT_ISAREF_1(history_collection_time,
		      (SI_Long)0L);
	      DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	      g2int_reclaim_managed_simple_float_array_of_length_1(history_collection_time);
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      temp = Qnil;
	    POP_SPECIAL();
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_gsi_history,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_gsi_history,top,Nil);
		goto end_read_gsi_history;
	    }
	}
	history = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : history;
	item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp_1 = EQ(test,Qg2int_true);
	else {
	    arg1 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX((SI_Long)0L);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg2 = g2int_resumable_icp_pop();
	    else {
		value = g2int_peek_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(Nil);
		    g2int_resumable_icp_push(item);
		    g2int_resumable_icp_push(history);
		    g2int_resumable_icp_push(Qg2int_read_gsi_history);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_read_gsi_history;
		}
		arg2 = value;
	    }
	    temp_1 = EQ(arg1,arg2);
	}
	if (temp_1) {
	    if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(history);
		g2int_resumable_icp_push(Qg2int_read_gsi_history);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_gsi_history;
	    }
	    temp = history;
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp_1 = EQ(test,Qg2int_true);
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Nil);
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_block;
			}
			arg1 = value;
		    }
		    arg2 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : FIX((SI_Long)49L);
		    arg1 = EQ(arg1,arg2) ? T : Nil;
		}
		temp_1 =  !TRUEP(arg1);
	    }
	    if (temp_1) {
		value = g2int_icp_error_internal(Qerror,string_constant_4,
			Nil,Nil,Nil);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		result = VALUES_1(value);
		goto end_read_gsi_history;
	    }
	  l2:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		length_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_fixnum();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		length_1 = value;
	    }
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    ||  !((SI_Long)1L <= IFIX(length_1))) {
		value = g2int_icp_error_internal(Qerror,string_constant_5,
			Nil,Nil,Nil);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_1;
		}
		result = VALUES_1(value);
		goto end_read_gsi_history;
	    }
	    g2int_add_vectors_to_gsi_history(length_1,history,item);
	  l2_1:
	    gsi_remote_value_creates_instance_p = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
		    1);
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  type = g2int_resumable_icp_pop();
	      else {
		  gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		  type = gsi_instance_extension ? 
			  ISVREF(gsi_instance_extension,(SI_Long)3L) : 
			  FIX((SI_Long)0L);
	      }
	      values_1 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : ISVREF(history,
		      (SI_Long)2L);
	      timestamps = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : ISVREF(history,
		      (SI_Long)3L);
	      i = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	      ab_loop_bind_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		  goto resume;
	    next_loop_1:
	      if (i >= ab_loop_bind_)
		  goto end_loop_1;
	    resume:
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  temp = g2int_resumable_icp_pop();
		  if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	      test = Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  test = g2int_resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  temp_1 = EQ(test,Qg2int_true);
	      else {
		  if ((resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		      arg1 = g2int_resumable_icp_pop();
		  else {
		      test = Nil;
		      if (resumable_icp_state_1 ? 
			      TRUEP(G2int_starresumable_icp_statestar) : 
			      TRUEP(Nil)) {
			  test = g2int_resumable_icp_pop();
			  temp_1 = TRUEP(test);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1)
			  temp_1 = EQ(test,Qg2int_true);
		      else {
			  if ((resumable_icp_state_1 ? 
				  TRUEP(G2int_starresumable_icp_statestar) 
				  : TRUEP(Nil)) &&  
				  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			      arg1 = g2int_resumable_icp_pop();
			  else {
			      value = g2int_read_icp_byte();
			      if (EQ(icp_suspend_1,value)) {
				  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				  g2int_resumable_icp_push(Nil);
				  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				  g2int_resumable_icp_push(Nil);
				  g2int_resumable_icp_push(FIX((SI_Long)1L));
				  temp = G2int_icp_suspend;
				  goto end_block_2;
			      }
			      arg1 = value;
			  }
			  arg2 = (resumable_icp_state_1 ? 
				  TRUEP(G2int_starresumable_icp_statestar) 
				  : TRUEP(Nil)) &&  
				  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				  ? g2int_resumable_icp_pop() : 
				  FIX((SI_Long)50L);
			  temp_1 = EQ(arg1,arg2);
		      }
		      if (temp_1) {
			  if ((resumable_icp_state_1 ? 
				  TRUEP(G2int_starresumable_icp_statestar) 
				  : TRUEP(Nil)) &&  
				  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			      arg1 = g2int_resumable_icp_pop();
			  else {
			      value = 
				      g2int_read_icp_interned_list_as_value_type();
			      if (EQ(icp_suspend_1,value)) {
				  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				  g2int_resumable_icp_push(Qg2int_true);
				  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				  g2int_resumable_icp_push(Nil);
				  g2int_resumable_icp_push(FIX((SI_Long)1L));
				  temp = G2int_icp_suspend;
				  goto end_block_2;
			      }
			      arg1 = value;
			  }
			  arg2 = (resumable_icp_state_1 ? 
				  TRUEP(G2int_starresumable_icp_statestar) 
				  : TRUEP(Nil)) &&  
				  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				  ? g2int_resumable_icp_pop() : 
				  G2int_attributes_of_history_element_structure_as_interned_list;
			  arg1 = EQ(arg1,arg2) ? T : Nil;
		      }
		      else
			  arg1 = Nil;
		  }
		  temp_1 =  !TRUEP(arg1);
	      }
	      if (temp_1) {
		  value = g2int_icp_error_internal(Qerror,
			  string_constant_6,Nil,Nil,Nil);
		  if (EQ(icp_suspend_1,value)) {
		      g2int_resumable_icp_push(Qg2int_true);
		      g2int_resumable_icp_push(FIX((SI_Long)1L));
		      temp = G2int_icp_suspend;
		      goto end_block_2;
		  }
		  result = VALUES_1(value);
		  POP_SPECIAL();
		  goto end_read_gsi_history;
	      }
	    l2_2:
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  history_value = g2int_resumable_icp_pop();
	      else {
		  test = Nil;
		  if (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) {
		      test = g2int_resumable_icp_pop();
		      temp_1 = TRUEP(test);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ? EQ(test,Qg2int_true) : (SI_Long)8L == 
			  IFIX(type) || (SI_Long)10L == IFIX(type)) {
		      gsi_remote_value_creates_instance_p = 
			      (resumable_icp_state_1 ? 
			      TRUEP(G2int_starresumable_icp_statestar) : 
			      TRUEP(Nil)) &&  
			      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			      ? g2int_resumable_icp_pop() : T;
		      PUSH_SPECIAL(G2int_gsi_remote_value_creates_instance_p,gsi_remote_value_creates_instance_p,
			      0);
			value = g2int_read_icp_remote_value();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(FIX((SI_Long)2L));
			    temp = G2int_icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			history_value = value;
		      POP_SPECIAL();
		  }
		  else {
		      value = g2int_read_icp_remote_value();
		      if (EQ(icp_suspend_1,value)) {
			  g2int_resumable_icp_push(Qg2int_false);
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(FIX((SI_Long)2L));
			  temp = G2int_icp_suspend;
			  goto end_block_2;
		      }
		      history_value = value;
		  }
	      }
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  history_collection_time = g2int_resumable_icp_pop();
	      else {
		  value = g2int_read_icp_remote_value();
		  if (EQ(icp_suspend_1,value)) {
		      g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		      g2int_resumable_icp_push(history_value);
		      g2int_resumable_icp_push(FIX((SI_Long)2L));
		      temp = G2int_icp_suspend;
		      goto end_block_2;
		  }
		  history_collection_time = value;
	      }
	      if (! !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) 
		      && FIXNUM_LE(type,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(type)) {
		    case 1:
		      temp_2 = IFIX(history_value);
		      BYTE_32_ISASET_1(values_1,i,temp_2);
		      break;
		    case 5:
		      temp_2 = IFIX(history_value);
		      BYTE_32_ISASET_1(values_1,i,temp_2);
		      break;
		    case 6:
		      aref_new_value = DFLOAT_ISAREF_1(history_value,
			      (SI_Long)0L);
		      DFLOAT_ISASET_1(values_1,i,aref_new_value);
		      g2int_reclaim_managed_simple_float_array_of_length_1(history_value);
		      break;
		    case 4:
		      svref_new_value = inline_extract_c_string(history_value);
		      ISVREF(values_1,i) = svref_new_value;
		      break;
		    case 3:
		      symbol = history_value;
		      svref_new_value = 
			      g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			      ? symbol : 
			      inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
			      G2int_gsi_wide_api_p));
		      ISVREF(values_1,i) = svref_new_value;
		      break;
		    case 8:
		    case 10:
		      temp_2 = i + (SI_Long)1L;
		      ISVREF(values_1,temp_2) = history_value;
		      break;
		    default:
		      break;
		  }
	      aref_new_value = DFLOAT_ISAREF_1(history_collection_time,
		      (SI_Long)0L);
	      DFLOAT_ISASET_1(timestamps,i,aref_new_value);
	      g2int_reclaim_managed_simple_float_array_of_length_1(history_collection_time);
	      temp = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp)) {
		  g2int_resumable_icp_push(FIX(ab_loop_bind_));
		  g2int_resumable_icp_push(FIX(i));
		  g2int_resumable_icp_push(timestamps);
		  g2int_resumable_icp_push(values_1);
		  g2int_resumable_icp_push(type);
		  g2int_resumable_icp_push(G2int_gsi_remote_value_creates_instance_p);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block_1;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      result = VALUES_1(Qnil);
	    POP_SPECIAL();
	    goto end_block_1;
	  end_block_1:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(length_1);
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    result = VALUES_3(v1,v2,v3);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(history);
		g2int_resumable_icp_push(Qg2int_read_gsi_history);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_gsi_history;
	    }
	    temp = v1;
	}
	else
	    temp = Qnil;
    }
    result = VALUES_1(temp);
  end_read_gsi_history:
    return result;
}

static Object Qg2int_write_gsi_history;  /* write-gsi-history */

/* WRITE-GSI-HISTORY */
Object g2int_write_gsi_history(history,item)
    Object history, item;
{
    Object temp, gsi_instance_extension, type, values_1, timestamps;
    Object history_value, history_collection_time, element;
    Object amf_available_array_cons_qm, amf_array, temp_1, svref_new_value;
    Object amf_result, incff_1_arg, new_float, resumable_icp_state_1;
    Object icp_suspend_1, top, test, value, v1, v2, v3;
    SI_Long i, ab_loop_bind_;
    char temp_2;
    double aref_new_value;
    Object result;

    x_note_fn_call(48,36);
    if (G2int_disable_resumability) {
	if ( !TRUEP(history) || (SI_Long)0L == IFIX(ISVREF(item,
		(SI_Long)1L)) >>  -  - (SI_Long)3L)
	    temp = g2int_write_icp_byte(FIX((SI_Long)0L));
	else {
	    g2int_write_icp_byte(FIX((SI_Long)49L));
	    g2int_write_icp_fixnum(ISVREF(history,(SI_Long)1L));
	    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	    type = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    values_1 = ISVREF(history,(SI_Long)2L);
	    timestamps = ISVREF(history,(SI_Long)3L);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(ISVREF(history,(SI_Long)1L));
	    history_value = Nil;
	    history_collection_time = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if ( !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) && 
		    FIXNUM_LE(type,FIX((SI_Long)127L))))
		history_value = Nil;
	    else
		switch (INTEGER_TO_CHAR(type)) {
		  case 1:
		    history_value = FIX(BYTE_32_ISAREF_1(values_1,i));
		    break;
		  case 5:
		    history_value = 
			    g2int_gensym_cons_1(FIX(BYTE_32_ISAREF_1(values_1,
			    i)),Qg2int_truth_value);
		    break;
		  case 4:
		    element = ISVREF(values_1,i);
		    history_value =  !TRUEP(element) ? 
			    (G2int_gsi_wide_api_p ? array_constant_2 : 
			    string_constant_2) : G2int_gsi_wide_api_p ? 
			    inline_restore_lisp_text_string(element) : 
			    inline_restore_lisp_gensym_string(element);
		    break;
		  case 3:
		    element = ISVREF(values_1,i);
		    history_value = 
			    g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			    ? element :  !TRUEP(element) ? Nil : 
			    g2int_symbol_for_gsi_string(G2int_gsi_wide_api_p 
			    ? g2int_c_wide_string_to_text_string(element) :
			     g2int_c_string_to_gensym_string(element));
		    break;
		  case 6:
		    amf_available_array_cons_qm = 
			    ISVREF(G2int_vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = G2int_vector_of_simple_float_array_pools;
			svref_new_value = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qg2int_gensym);
			temp_1 = G2int_available_gensym_conses;
			M_CDR(amf_available_array_cons_qm) = temp_1;
			G2int_available_gensym_conses = 
				amf_available_array_cons_qm;
			amf_result = amf_array;
		    }
		    else {
			temp_1 = 
				FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			G2int_created_simple_float_array_pool_arrays = temp_1;
			incff_1_arg = 
				g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			temp_1 = 
				FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				incff_1_arg);
			G2int_simple_float_array_pool_memory_usage = temp_1;
			amf_result = 
				g2int_generate_float_vector(FIX((SI_Long)1L));
		    }
		    new_float = amf_result;
		    aref_new_value = DFLOAT_ISAREF_1(values_1,i);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    history_value = new_float;
		    break;
		  case 8:
		  case 10:
		    history_value = ISVREF(values_1,i + (SI_Long)1L);
		    break;
		  default:
		    history_value = Nil;
		    break;
		}
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp_1 = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp_1;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp_1 = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp_1;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp_1 = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp_1;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value = DFLOAT_ISAREF_1(timestamps,i);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    history_collection_time = new_float;
	    g2int_write_icp_byte(FIX((SI_Long)50L));
	    g2int_write_icp_interned_list_as_value_type(G2int_attributes_of_history_element_structure_as_interned_list);
	    g2int_write_icp_remote_value(history_value);
	    if (! !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) 
		    && FIXNUM_LE(type,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(type)) {
		  case 6:
		    g2int_reclaim_managed_simple_float_array_of_length_1(history_value);
		    break;
		  case 5:
		    g2int_reclaim_gensym_cons_1(history_value);
		    break;
		  default:
		    break;
		}
	    g2int_write_icp_remote_value(history_collection_time);
	    g2int_reclaim_managed_simple_float_array_of_length_1(history_collection_time);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_gsi_history,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_gsi_history,top,Nil);
	}
	history = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : history;
	item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_2 = TRUEP(test);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? EQ(test,Qg2int_true) :  !TRUEP(history) || 
		(SI_Long)0L == IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - 
		(SI_Long)3L) {
	    value = g2int_write_icp_byte(FIX((SI_Long)0L));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(history);
		g2int_resumable_icp_push(Qg2int_write_gsi_history);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1;
			break;
		      case 2:
			goto l2;
			break;
		      case 3:
			goto l3;
			break;
		      default:
			break;
		    }
	    }
	  l1:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)49L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l2:
	    if (EQ(icp_suspend_1,g2int_write_icp_fixnum(ISVREF(history,
		    (SI_Long)1L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l3:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		type = g2int_resumable_icp_pop();
	    else {
		gsi_instance_extension = ISVREF(item,(SI_Long)3L);
		type = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)3L) : 
			FIX((SI_Long)0L);
	    }
	    values_1 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : ISVREF(history,(SI_Long)2L);
	    timestamps = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : ISVREF(history,(SI_Long)3L);
	    i = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : IFIX(ISVREF(history,
		    (SI_Long)1L));
	    history_value = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    history_collection_time = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		goto resume;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    if ( !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) && 
		    FIXNUM_LE(type,FIX((SI_Long)127L))))
		history_value = Nil;
	    else
		switch (INTEGER_TO_CHAR(type)) {
		  case 1:
		    history_value = FIX(BYTE_32_ISAREF_1(values_1,i));
		    break;
		  case 5:
		    history_value = 
			    g2int_gensym_cons_1(FIX(BYTE_32_ISAREF_1(values_1,
			    i)),Qg2int_truth_value);
		    break;
		  case 4:
		    element = ISVREF(values_1,i);
		    history_value =  !TRUEP(element) ? 
			    (G2int_gsi_wide_api_p ? array_constant_2 : 
			    string_constant_2) : G2int_gsi_wide_api_p ? 
			    inline_restore_lisp_text_string(element) : 
			    inline_restore_lisp_gensym_string(element);
		    break;
		  case 3:
		    element = ISVREF(values_1,i);
		    history_value = 
			    g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) 
			    ? element :  !TRUEP(element) ? Nil : 
			    g2int_symbol_for_gsi_string(G2int_gsi_wide_api_p 
			    ? g2int_c_wide_string_to_text_string(element) :
			     g2int_c_string_to_gensym_string(element));
		    break;
		  case 6:
		    amf_available_array_cons_qm = 
			    ISVREF(G2int_vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = G2int_vector_of_simple_float_array_pools;
			svref_new_value = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qg2int_gensym);
			temp_1 = G2int_available_gensym_conses;
			M_CDR(amf_available_array_cons_qm) = temp_1;
			G2int_available_gensym_conses = 
				amf_available_array_cons_qm;
			amf_result = amf_array;
		    }
		    else {
			temp_1 = 
				FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			G2int_created_simple_float_array_pool_arrays = temp_1;
			incff_1_arg = 
				g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			temp_1 = 
				FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				incff_1_arg);
			G2int_simple_float_array_pool_memory_usage = temp_1;
			amf_result = 
				g2int_generate_float_vector(FIX((SI_Long)1L));
		    }
		    new_float = amf_result;
		    aref_new_value = DFLOAT_ISAREF_1(values_1,i);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    history_value = new_float;
		    break;
		  case 8:
		  case 10:
		    history_value = ISVREF(values_1,i + (SI_Long)1L);
		    break;
		  default:
		    history_value = Nil;
		    break;
		}
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp_1 = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp_1;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp_1 = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp_1;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp_1 = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp_1;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value = DFLOAT_ISAREF_1(timestamps,i);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    history_collection_time = new_float;
	  resume:
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1_1;
			break;
		      case 2:
			goto l2_1;
			break;
		      case 3:
			goto l3_1;
			break;
		      case 4:
			goto l4;
			break;
		      default:
			break;
		    }
	    }
	  l1_1:
	    if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)50L)))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		temp = G2int_icp_suspend;
		goto end_block_1;
	    }
	  l2_1:
	    if (EQ(icp_suspend_1,
		    g2int_write_icp_interned_list_as_value_type(G2int_attributes_of_history_element_structure_as_interned_list))) 
			{
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		temp = G2int_icp_suspend;
		goto end_block_1;
	    }
	  l3_1:
	    if (EQ(icp_suspend_1,
			g2int_write_icp_remote_value(history_value))) {
		g2int_resumable_icp_push(FIX((SI_Long)3L));
		temp = G2int_icp_suspend;
		goto end_block_1;
	    }
	    if (! !(FIXNUMP(type) && FIXNUM_LE(FIX((SI_Long)-128L),type) 
		    && FIXNUM_LE(type,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(type)) {
		  case 6:
		    g2int_reclaim_managed_simple_float_array_of_length_1(history_value);
		    break;
		  case 5:
		    g2int_reclaim_gensym_cons_1(history_value);
		    break;
		  default:
		    break;
		}
	  l4:
	    if (EQ(icp_suspend_1,
		    g2int_write_icp_remote_value(history_collection_time))) {
		g2int_resumable_icp_push(FIX((SI_Long)4L));
		temp = G2int_icp_suspend;
		goto end_block_1;
	    }
	    g2int_reclaim_managed_simple_float_array_of_length_1(history_collection_time);
	    temp = Nil;
	    goto end_block_1;
	  end_block_1:
	    if (EQ(icp_suspend_1,temp)) {
		g2int_resumable_icp_push(history_collection_time);
		g2int_resumable_icp_push(history_value);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(i));
		g2int_resumable_icp_push(timestamps);
		g2int_resumable_icp_push(values_1);
		g2int_resumable_icp_push(type);
		g2int_resumable_icp_push(FIX((SI_Long)3L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_1(Qnil);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(history);
		g2int_resumable_icp_push(Qg2int_write_gsi_history);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

Object G2int_pending_write_reference_list = UNBOUND;

Object G2int_using_pending_write_reference_list = UNBOUND;

/* WRITE-ICP-ITEM-REFERENCE-1-FUNCTION */
Object g2int_write_icp_item_reference_1_function(item)
    Object item;
{
    Object pending_write_reference_list, using_pending_write_reference_list;
    Object temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,37);
    if ( !TRUEP(G2int_using_pending_write_reference_list)) {
	pending_write_reference_list = Nil;
	using_pending_write_reference_list = T;
	PUSH_SPECIAL(G2int_using_pending_write_reference_list,using_pending_write_reference_list,
		1);
	  PUSH_SPECIAL(G2int_pending_write_reference_list,pending_write_reference_list,
		  0);
	    temp = g2int_write_icp_item_reference(item);
	    g2int_reclaim_gensym_list_1(G2int_pending_write_reference_list);
	    result = VALUES_1(temp);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return g2int_write_icp_item_reference(item);
}

static Object Qg2int_write_icp_item_copy;  /* write-icp-item-copy */

/* WRITE-ICP-ITEM-COPY */
Object g2int_write_icp_item_copy(item_copy)
    Object item_copy;
{
    Object existing_index, temp, pending_write_reference_list;
    Object using_pending_write_reference_list, resumable_icp_state_1;
    Object icp_suspend_1, top, test, value, v1, v2, v3, gensymed_symbol;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,38);
    if (G2int_disable_resumability) {
	existing_index = G2int_item_copy_index_space ? 
		g2int_lookup_index_in_index_space(item_copy,
		G2int_item_copy_index_space) : Nil;
	if (existing_index) {
	    g2int_write_icp_byte(G2int_rpc_existing_item_copy);
	    temp = g2int_write_icp_fixnum(existing_index);
	}
	else {
	    if (Nil) {
		g2int_write_icp_byte(G2int_rpc_new_item_copy_with_reference);
		if ( !TRUEP(G2int_using_pending_write_reference_list)) {
		    pending_write_reference_list = Nil;
		    using_pending_write_reference_list = T;
		    PUSH_SPECIAL(G2int_using_pending_write_reference_list,using_pending_write_reference_list,
			    1);
		      PUSH_SPECIAL(G2int_pending_write_reference_list,pending_write_reference_list,
			      0);
			g2int_write_icp_item_reference(item_copy);
			g2int_reclaim_gensym_list_1(G2int_pending_write_reference_list);
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		else
		    g2int_write_icp_item_reference(item_copy);
	    }
	    else if (G2int_item_copy_handle_for_root_item && EQ(item_copy,
		    G2int_item_copy_root_item)) {
		g2int_write_icp_byte(G2int_rpc_new_item_copy_with_handle);
		g2int_write_icp_fixnum(G2int_item_copy_handle_for_root_item);
	    }
	    else
		g2int_write_icp_byte(G2int_rpc_new_item_copy);
	    temp = g2int_write_icp_item_new_copy(item_copy);
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_item_copy,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_item_copy,top,Nil);
	}
	item_copy = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item_copy;
	existing_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : G2int_item_copy_index_space ? 
		g2int_lookup_index_in_index_space(item_copy,
		G2int_item_copy_index_space) : Nil;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : TRUEP(existing_index)) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
		    g2int_write_icp_byte(G2int_rpc_existing_item_copy))) {
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	  l2:
	    value = g2int_write_icp_fixnum(existing_index);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    result = VALUES_1(value);
	    goto end_block;
	  end_block:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(existing_index);
		g2int_resumable_icp_push(item_copy);
		g2int_resumable_icp_push(Qg2int_write_icp_item_copy);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || T) {
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		temp = g2int_resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : TRUEP(Nil)) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
			g2int_write_icp_byte(G2int_rpc_new_item_copy_with_reference))) 
			    {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    temp = G2int_icp_suspend;
		    goto end_block_1;
		}
	      l2_2:
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) :  
			!TRUEP(G2int_using_pending_write_reference_list)) {
		    pending_write_reference_list = (resumable_icp_state_1 ?
			     TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : Nil;
		    PUSH_SPECIAL(G2int_pending_write_reference_list,pending_write_reference_list,
			    1);
		      using_pending_write_reference_list = 
			      (resumable_icp_state_1 ? 
			      TRUEP(G2int_starresumable_icp_statestar) : 
			      TRUEP(Nil)) &&  
			      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			      ? g2int_resumable_icp_pop() : T;
		      PUSH_SPECIAL(G2int_using_pending_write_reference_list,using_pending_write_reference_list,
			      0);
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    gensymed_symbol = g2int_resumable_icp_pop();
			else {
			    value = g2int_write_icp_item_reference(item_copy);
			    if (EQ(icp_suspend_1,value)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(G2int_using_pending_write_reference_list);
				g2int_resumable_icp_push(G2int_pending_write_reference_list);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(FIX((SI_Long)2L));
				temp = G2int_icp_suspend;
				POP_SPECIAL();
				POP_SPECIAL();
				goto end_block_1;
			    }
			    gensymed_symbol = value;
			}
			g2int_reclaim_gensym_list_1(G2int_pending_write_reference_list);
			temp = gensymed_symbol;
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			g2int_write_icp_item_reference(item_copy))) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    temp = G2int_icp_suspend;
		    goto end_block_1;
		}
		else
		    temp = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block_2;
		}
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : 
			G2int_item_copy_handle_for_root_item && 
			EQ(item_copy,G2int_item_copy_root_item)) {
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			temp = g2int_resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
			    g2int_write_icp_byte(G2int_rpc_new_item_copy_with_handle))) 
				{
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			temp = G2int_icp_suspend;
			goto end_block_3;
		    }
		  l2_3:
		    if (EQ(icp_suspend_1,
			    g2int_write_icp_fixnum(G2int_item_copy_handle_for_root_item))) 
				{
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			temp = G2int_icp_suspend;
			goto end_block_3;
		    }
		    else
			temp = Nil;
		    goto end_block_3;
		  end_block_3:
		    if (EQ(icp_suspend_1,temp)) {
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_2;
		    }
		}
		else if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) || T) {
		    if (EQ(icp_suspend_1,
			    g2int_write_icp_byte(G2int_rpc_new_item_copy))) {
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block_2;
		    }
		}
	    }
	  l2_1:
	    value = g2int_write_icp_item_new_copy(item_copy);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block_2;
	    }
	    result = VALUES_1(value);
	    goto end_block_2;
	  end_block_2:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(existing_index);
		g2int_resumable_icp_push(item_copy);
		g2int_resumable_icp_push(Qg2int_write_icp_item_copy);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = v1;
	}
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_item_copy;  /* read-icp-item-copy */

/* READ-ICP-ITEM-COPY */
Object g2int_read_icp_item_copy()
{
    Object tag, index_space, index_1, temp, handle, item_copy, reference;
    Object resumable_icp_state_1, icp_suspend_1, top, value, test;
    char temp_1;

    x_note_fn_call(48,39);
    if (G2int_disable_resumability) {
	tag = g2int_read_icp_byte();
	if (FIXNUM_EQ(G2int_rpc_existing_item_copy,tag)) {
	    index_space = G2int_item_copy_index_space;
	    index_1 = g2int_read_icp_fixnum();
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    temp = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else if (FIXNUM_EQ(G2int_rpc_new_item_copy_with_handle,tag)) {
	    handle = g2int_read_icp_fixnum();
	    item_copy = g2int_read_icp_item_new_copy();
	    if (item_copy) {
		g2int_register_item_with_handle_on_port(handle,item_copy,
			G2int_current_icp_port);
		g2int_set_icp_object_index_for_gsi_instance(item_copy,
			handle,G2int_current_icp_port);
	    }
	    temp = item_copy;
	}
	else if (FIXNUM_EQ(G2int_rpc_new_item_copy_with_reference,tag)) {
	    reference = g2int_read_icp_item_reference();
	    handle = reference ? 
		    g2int_get_icp_object_index_for_gsi_instance(reference,
		    G2int_current_icp_port) : Nil;
	    item_copy = g2int_read_icp_item_new_copy();
	    if (handle && item_copy) {
		g2int_register_item_with_handle_on_port(handle,item_copy,
			G2int_current_icp_port);
		g2int_set_icp_object_index_for_gsi_instance(item_copy,
			handle,G2int_current_icp_port);
	    }
	    temp = item_copy;
	}
	else if (FIXNUM_EQ(G2int_rpc_new_item_copy,tag))
	    temp = g2int_read_icp_item_new_copy();
	else
	    temp = g2int_icp_out_of_synch(1,FIX((SI_Long)7L));
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_item_copy,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_item_copy,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    tag = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_item_copy);
		return VALUES_1(G2int_icp_suspend);
	    }
	    tag = value;
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : 
		FIXNUM_EQ(G2int_rpc_existing_item_copy,tag)) {
	    index_space = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : G2int_item_copy_index_space;
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_fixnum();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(index_space);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(tag);
		    g2int_resumable_icp_push(Qg2int_read_icp_item_copy);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    temp = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : 
		    FIXNUM_EQ(G2int_rpc_new_item_copy_with_handle,tag)) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    handle = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_fixnum();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(tag);
			g2int_resumable_icp_push(Qg2int_read_icp_item_copy);
			return VALUES_1(G2int_icp_suspend);
		    }
		    handle = value;
		}
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    item_copy = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_item_new_copy();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(handle);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(tag);
			g2int_resumable_icp_push(Qg2int_read_icp_item_copy);
			return VALUES_1(G2int_icp_suspend);
		    }
		    item_copy = value;
		}
		if (item_copy) {
		    g2int_register_item_with_handle_on_port(handle,
			    item_copy,G2int_current_icp_port);
		    g2int_set_icp_object_index_for_gsi_instance(item_copy,
			    handle,G2int_current_icp_port);
		}
		temp = item_copy;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : 
			FIXNUM_EQ(G2int_rpc_new_item_copy_with_reference,
			    tag)) {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			reference = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_item_reference();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(tag);
			    g2int_resumable_icp_push(Qg2int_read_icp_item_copy);
			    return VALUES_1(G2int_icp_suspend);
			}
			reference = value;
		    }
		    handle = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : reference ? 
			    g2int_get_icp_object_index_for_gsi_instance(reference,
			    G2int_current_icp_port) : Nil;
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			item_copy = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_item_new_copy();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(handle);
			    g2int_resumable_icp_push(reference);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(tag);
			    g2int_resumable_icp_push(Qg2int_read_icp_item_copy);
			    return VALUES_1(G2int_icp_suspend);
			}
			item_copy = value;
		    }
		    if (handle && item_copy) {
			g2int_register_item_with_handle_on_port(handle,
				item_copy,G2int_current_icp_port);
			g2int_set_icp_object_index_for_gsi_instance(item_copy,
				handle,G2int_current_icp_port);
		    }
		    temp = item_copy;
		}
		else if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) || FIXNUM_EQ(G2int_rpc_new_item_copy,
			    tag)) {
		    value = g2int_read_icp_item_new_copy();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(tag);
			g2int_resumable_icp_push(Qg2int_read_icp_item_copy);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value;
		}
		else
		    temp = T ? g2int_icp_out_of_synch(1,FIX((SI_Long)7L)) :
			     Nil;
	    }
	}
    }
    return VALUES_1(temp);
}

static Object Qg2_defstruct_structure_name_gsi_instance_g2_struct;  /* g2-defstruct-structure-name::gsi-instance-g2-struct */

static Object Qg2int_copy;         /* copy */

static Object Qg2int_handle;       /* handle */

static Object Qg2int_gsi_reference_flag;  /* gsi-reference-flag */

static Object Qg2int_reference;    /* reference */

static Object Qg2int_write_icp_item;  /* write-icp-item */

/* WRITE-ICP-ITEM */
Object g2int_write_icp_item(item)
    Object item;
{
    Object temp, pending_write_reference_list;
    Object using_pending_write_reference_list, resumable_icp_state_1;
    Object icp_suspend_1, top, key, value, test, gensymed_symbol;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,40);
    if (G2int_disable_resumability) {
	if ( !(SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		Qg2_defstruct_structure_name_gsi_instance_g2_struct)))
	    temp = Qg2int_copy;
	else if (EQ(FIX((SI_Long)9L),FIX(IFIX(ISVREF(item,(SI_Long)1L)) >> 
		 -  - (SI_Long)3L)))
	    temp = Qg2int_handle;
	else if (g2int_get_gsi_instance_plist_value(item,
		Qg2int_gsi_reference_flag))
	    temp = Qg2int_reference;
	else
	    temp = Qg2int_copy;
	if (EQ(temp,Qg2int_handle))
	    temp = g2int_write_icp_item_handle(item);
	else if (EQ(temp,Qg2int_reference)) {
	    if ( !TRUEP(G2int_using_pending_write_reference_list)) {
		pending_write_reference_list = Nil;
		using_pending_write_reference_list = T;
		PUSH_SPECIAL(G2int_using_pending_write_reference_list,using_pending_write_reference_list,
			1);
		  PUSH_SPECIAL(G2int_pending_write_reference_list,pending_write_reference_list,
			  0);
		    temp = g2int_write_icp_item_reference(item);
		    g2int_reclaim_gensym_list_1(G2int_pending_write_reference_list);
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		temp = g2int_write_icp_item_reference(item);
	}
	else if (EQ(temp,Qg2int_copy))
	    temp = g2int_write_icp_item_copy(item);
	else
	    temp = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_item,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_item,top,Nil);
		goto end_write_icp_item;
	    }
	}
	item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    key = g2int_resumable_icp_pop();
	else if ( !(SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		Qg2_defstruct_structure_name_gsi_instance_g2_struct)))
	    key = Qg2int_copy;
	else if (EQ(FIX((SI_Long)9L),FIX(IFIX(ISVREF(item,(SI_Long)1L)) >> 
		 -  - (SI_Long)3L)))
	    key = Qg2int_handle;
	else if (g2int_get_gsi_instance_plist_value(item,
		Qg2int_gsi_reference_flag))
	    key = Qg2int_reference;
	else
	    key = Qg2int_copy;
	if (EQ(key,Qg2int_handle)) {
	    value = g2int_write_icp_item_handle(item);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(key);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(Qg2int_write_icp_item);
		result = VALUES_1(G2int_icp_suspend);
		goto end_write_icp_item;
	    }
	    temp = value;
	}
	else if (EQ(key,Qg2int_reference)) {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) :  
		    !TRUEP(G2int_using_pending_write_reference_list)) {
		pending_write_reference_list = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		PUSH_SPECIAL(G2int_pending_write_reference_list,pending_write_reference_list,
			1);
		  using_pending_write_reference_list = 
			  (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? g2int_resumable_icp_pop() : T;
		  PUSH_SPECIAL(G2int_using_pending_write_reference_list,using_pending_write_reference_list,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			gensymed_symbol = g2int_resumable_icp_pop();
		    else {
			value = g2int_write_icp_item_reference(item);
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(G2int_using_pending_write_reference_list);
			    g2int_resumable_icp_push(G2int_pending_write_reference_list);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(item);
			    g2int_resumable_icp_push(Qg2int_write_icp_item);
			    result = VALUES_1(G2int_icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_write_icp_item;
			}
			gensymed_symbol = value;
		    }
		    g2int_reclaim_gensym_list_1(G2int_pending_write_reference_list);
		    temp = gensymed_symbol;
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else {
		value = g2int_write_icp_item_reference(item);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(item);
		    g2int_resumable_icp_push(Qg2int_write_icp_item);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_write_icp_item;
		}
		temp = value;
	    }
	}
	else if (EQ(key,Qg2int_copy)) {
	    value = g2int_write_icp_item_copy(item);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(key);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(Qg2int_write_icp_item);
		result = VALUES_1(G2int_icp_suspend);
		goto end_write_icp_item;
	    }
	    temp = value;
	}
	else
	    temp = Qnil;
    }
    result = VALUES_1(temp);
  end_write_icp_item:
    return result;
}

static Object Qg2int_read_icp_item;  /* read-icp-item */

/* READ-ICP-ITEM */
Object g2int_read_icp_item()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, key, value;

    x_note_fn_call(48,41);
    if (G2int_disable_resumability) {
	temp = g2int_peek_icp_byte();
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 60:
	      case 61:
	      case 74:
	      case 62:
		temp = g2int_read_icp_item_reference();
		break;
	      case 64:
	      case 65:
	      case 66:
	      case 63:
		temp = g2int_read_icp_item_copy();
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_item,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_item,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    key = g2int_resumable_icp_pop();
	else {
	    value = g2int_peek_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_item);
		return VALUES_1(G2int_icp_suspend);
	    }
	    key = value;
	}
	temp = key;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 60:
	      case 61:
	      case 74:
	      case 62:
		value = g2int_read_icp_item_reference();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_item);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
		break;
	      case 64:
	      case 65:
	      case 66:
	      case 63:
		value = g2int_read_icp_item_copy();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_read_icp_item);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_item_handle;  /* write-icp-item-handle */

/* WRITE-ICP-ITEM-HANDLE */
Object g2int_write_icp_item_handle(item_handle)
    Object item_handle;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value, v1, v2, v3;
    Object result;

    x_note_fn_call(48,42);
    if (G2int_disable_resumability) {
	g2int_write_icp_byte(G2int_rpc_object_handle_type_tag);
	temp = g2int_write_icp_fixnum(ISVREF(item_handle,(SI_Long)2L));
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_item_handle,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_item_handle,top,Nil);
	}
	item_handle = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item_handle;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
		g2int_write_icp_byte(G2int_rpc_object_handle_type_tag))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	value = g2int_write_icp_fixnum(ISVREF(item_handle,(SI_Long)2L));
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	result = VALUES_1(value);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(item_handle);
	    g2int_resumable_icp_push(Qg2int_write_icp_item_handle);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_item_handle;  /* read-icp-item-handle */

/* READ-ICP-ITEM-HANDLE */
Object g2int_read_icp_item_handle()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(48,43);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_item_handle,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_item_handle,top,Nil);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_value_or_reference_argument_list;  /* write-icp-value-or-reference-argument-list */

/* WRITE-ICP-VALUE-OR-REFERENCE-ARGUMENT-LIST */
Object g2int_write_icp_value_or_reference_argument_list(value_or_reference_argument_list)
    Object value_or_reference_argument_list;
{
    Object value_or_item, ab_loop_list_, write_remote_value_items_kind, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,44);
    if (G2int_disable_resumability) {
	g2int_write_icp_unsigned_integer(length(value_or_reference_argument_list));
	value_or_item = Nil;
	ab_loop_list_ = value_or_reference_argument_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	value_or_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_remote_value_items_kind = Qg2int_reference;
	PUSH_SPECIAL(G2int_write_remote_value_items_kind,write_remote_value_items_kind,
		0);
	  g2int_write_icp_remote_value(value_or_item);
	POP_SPECIAL();
	goto next_loop;
      end_loop:
	temp = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_value_or_reference_argument_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_value_or_reference_argument_list,
			top,Nil);
	}
	value_or_reference_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value_or_reference_argument_list;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
		g2int_write_icp_unsigned_integer(length(value_or_reference_argument_list)))) 
		    {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	value_or_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loop_list_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value_or_reference_argument_list;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	value_or_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      resume:
	write_remote_value_items_kind = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Qg2int_reference;
	PUSH_SPECIAL(G2int_write_remote_value_items_kind,write_remote_value_items_kind,
		0);
	  if (EQ(icp_suspend_1,g2int_write_icp_remote_value(value_or_item))) {
	      g2int_resumable_icp_push(G2int_write_remote_value_items_kind);
	      g2int_resumable_icp_push(ab_loop_list_);
	      g2int_resumable_icp_push(value_or_item);
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_block;
	  }
	POP_SPECIAL();
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(value_or_reference_argument_list);
	    g2int_resumable_icp_push(Qg2int_write_icp_value_or_reference_argument_list);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_unbound;      /* unbound */

static Object Qg2int_read_icp_value_or_reference_argument_list;  /* read-icp-value-or-reference-argument-list */

/* READ-ICP-VALUE-OR-REFERENCE-ARGUMENT-LIST */
Object g2int_read_icp_value_or_reference_argument_list()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, item_copy_index_space;
    Object current_computation_flags, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value, arg1, test, gensymed_symbol, arg2;
    SI_Long ab_loop_repeat_;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,45);
    if (G2int_disable_resumability) {
	ab_loop_repeat_ = IFIX(g2int_read_icp_unsigned_integer());
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(Qg2int_unbound,G2int_item_copy_index_space)) {
	    item_copy_index_space = Nil;
	    current_computation_flags = G2int_current_computation_flags;
	    PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		    1);
	      PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
		      0);
		temp = g2int_read_icp_remote_value();
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = g2int_read_icp_remote_value();
	ab_loopvar__2 = g2int_gensym_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end;
	temp = Qnil;
      end:;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_value_or_reference_argument_list,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_value_or_reference_argument_list,
			top,Nil);
		goto end_read_icp_value_or_reference_argument_list;
	    }
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    ab_loop_repeat_ = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_value_or_reference_argument_list);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_icp_value_or_reference_argument_list;
	    }
	    ab_loop_repeat_ = IFIX(value);
	}
	ab_loopvar_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : EQ(Qg2int_unbound,
		    G2int_item_copy_index_space)) {
		item_copy_index_space = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
			1);
		  current_computation_flags = (resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			  ? g2int_resumable_icp_pop() : 
			  G2int_current_computation_flags;
		  PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			gensymed_symbol = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_remote_value();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(G2int_current_computation_flags);
			    g2int_resumable_icp_push(G2int_item_copy_index_space);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(ab_loopvar__2);
			    g2int_resumable_icp_push(ab_loopvar__1);
			    g2int_resumable_icp_push(ab_loopvar_);
			    g2int_resumable_icp_push(FIX(ab_loop_repeat_));
			    g2int_resumable_icp_push(Qg2int_read_icp_value_or_reference_argument_list);
			    result = VALUES_1(G2int_icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_read_icp_value_or_reference_argument_list;
			}
			gensymed_symbol = value;
		    }
		    if (G2int_item_copy_index_space)
			g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		    arg1 = gensymed_symbol;
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else {
		value = g2int_read_icp_remote_value();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(ab_loopvar__2);
		    g2int_resumable_icp_push(ab_loopvar__1);
		    g2int_resumable_icp_push(ab_loopvar_);
		    g2int_resumable_icp_push(FIX(ab_loop_repeat_));
		    g2int_resumable_icp_push(Qg2int_read_icp_value_or_reference_argument_list);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_read_icp_value_or_reference_argument_list;
		}
		arg1 = value;
	    }
	}
	arg2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = g2int_gensym_cons_1(arg1,arg2);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    result = VALUES_1(temp);
  end_read_icp_value_or_reference_argument_list:
    return result;
}

static Object Qg2int_write_icp_resumable_rpc_argument_list;  /* write-icp-resumable-rpc-argument-list */

/* WRITE-ICP-RESUMABLE-RPC-ARGUMENT-LIST */
Object g2int_write_icp_resumable_rpc_argument_list(resumable_rpc_argument_list)
    Object resumable_rpc_argument_list;
{
    Object actual_size, value_or_object, write_remote_value_items_kind;
    Object item_copy_index_space, current_computation_flags, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, test, gensymed_symbol;
    Object value, v1, v2, v3;
    SI_Long i, ab_loop_bind_;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(48,46);
    if (G2int_disable_resumability) {
	actual_size = G2int_rpc_argument_count_overrideqm;
	if (actual_size);
	else
	    actual_size = resumable_rpc_argument_list ? 
		    FIXNUM_SUB1(g2int_gsi_managed_array_length(resumable_rpc_argument_list)) 
		    : FIX((SI_Long)0L);
	g2int_write_icp_unsigned_integer(actual_size);
	i = IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = IFIX(actual_size);
	value_or_object = Nil;
      next_loop:
	if (i > ab_loop_bind_)
	    goto end_loop;
	value_or_object = ISVREF(resumable_rpc_argument_list,i);
	write_remote_value_items_kind = Qg2int_copy;
	PUSH_SPECIAL(G2int_write_remote_value_items_kind,write_remote_value_items_kind,
		2);
	  if (EQ(Qg2int_unbound,G2int_item_copy_index_space)) {
	      item_copy_index_space = Nil;
	      current_computation_flags = G2int_current_computation_flags;
	      PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		      1);
		PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
			0);
		  g2int_write_icp_remote_value(value_or_object);
		  if (G2int_item_copy_index_space)
		      g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  else
	      g2int_write_icp_remote_value(value_or_object);
	POP_SPECIAL();
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_resumable_rpc_argument_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_resumable_rpc_argument_list,top,Nil);
	}
	resumable_rpc_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : resumable_rpc_argument_list;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    actual_size = g2int_resumable_icp_pop();
	else {
	    actual_size = G2int_rpc_argument_count_overrideqm;
	    if (actual_size);
	    else
		actual_size = resumable_rpc_argument_list ? 
			FIXNUM_SUB1(g2int_gsi_managed_array_length(resumable_rpc_argument_list)) 
			: FIX((SI_Long)0L);
	}
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	if (EQ(icp_suspend_1,g2int_write_icp_unsigned_integer(actual_size))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	i = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : IFIX(actual_size);
	value_or_object = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if (i > ab_loop_bind_)
	    goto end_loop_1;
	value_or_object = ISVREF(resumable_rpc_argument_list,i);
      resume:
	write_remote_value_items_kind = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Qg2int_copy;
	PUSH_SPECIAL(G2int_write_remote_value_items_kind,write_remote_value_items_kind,
		2);
	  test = Nil;
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      test = g2int_resumable_icp_pop();
	      temp_1 = TRUEP(test);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ? EQ(test,Qg2int_true) : EQ(Qg2int_unbound,
		  G2int_item_copy_index_space)) {
	      item_copy_index_space = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
		      1);
		current_computation_flags = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			G2int_current_computation_flags;
		PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
			0);
		  if ((resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		      gensymed_symbol = g2int_resumable_icp_pop();
		  else {
		      value = g2int_write_icp_remote_value(value_or_object);
		      if (EQ(icp_suspend_1,value)) {
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(G2int_current_computation_flags);
			  g2int_resumable_icp_push(G2int_item_copy_index_space);
			  g2int_resumable_icp_push(Qg2int_true);
			  g2int_resumable_icp_push(G2int_write_remote_value_items_kind);
			  g2int_resumable_icp_push(value_or_object);
			  g2int_resumable_icp_push(FIX(ab_loop_bind_));
			  g2int_resumable_icp_push(FIX(i));
			  g2int_resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(G2int_icp_suspend);
			  POP_SPECIAL();
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      gensymed_symbol = value;
		  }
		  if (G2int_item_copy_index_space)
		      g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  g2int_write_icp_remote_value(value_or_object))) {
	      g2int_resumable_icp_push(Qg2int_false);
	      g2int_resumable_icp_push(G2int_write_remote_value_items_kind);
	      g2int_resumable_icp_push(value_or_object);
	      g2int_resumable_icp_push(FIX(ab_loop_bind_));
	      g2int_resumable_icp_push(FIX(i));
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_block;
	  }
	POP_SPECIAL();
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(actual_size);
	    g2int_resumable_icp_push(resumable_rpc_argument_list);
	    g2int_resumable_icp_push(Qg2int_write_icp_resumable_rpc_argument_list);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_managed_array;  /* managed-array */

/* MAKE-GSI-RPC-ARGUMENT-LIST */
Object g2int_make_gsi_rpc_argument_list(length_1)
    Object length_1;
{
    Object arg_array, svref_new_value;

    x_note_fn_call(48,47);
    arg_array = g2int_gsi_allocate_managed_array(FIXNUM_ADD1(length_1));
    g2int_gsi_push_onto_appropriate_list(1,
	    g2int_make_gsi_array_wrapper_1(Qg2int_managed_array,arg_array));
    svref_new_value = G2int_gsi_magic_number;
    SVREF(arg_array,FIX((SI_Long)0L)) = svref_new_value;
    return VALUES_1(arg_array);
}

static Object Qg2int_read_icp_resumable_rpc_argument_list;  /* read-icp-resumable-rpc-argument-list */

/* READ-ICP-RESUMABLE-RPC-ARGUMENT-LIST */
Object g2int_read_icp_resumable_rpc_argument_list()
{
    Object length_1, rpc_argument_list_error, arg_array, argument;
    Object item_copy_index_space, current_computation_flags, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, test;
    Object gensymed_symbol;
    SI_Long item_count, ab_loop_bind_;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(48,48);
    if (G2int_disable_resumability) {
	length_1 = g2int_read_icp_unsigned_integer();
	rpc_argument_list_error = Nil;
	PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,2);
	  arg_array = g2int_make_gsi_rpc_argument_list(length_1);
	  item_count = IFIX(G2int_gsi_magic_offset);
	  ab_loop_bind_ = IFIX(FIXNUM_ADD1(length_1));
	  argument = Nil;
	next_loop:
	  if (item_count >= ab_loop_bind_)
	      goto end_loop;
	  if (EQ(Qg2int_unbound,G2int_item_copy_index_space)) {
	      item_copy_index_space = Nil;
	      current_computation_flags = G2int_current_computation_flags;
	      PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		      1);
		PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
			0);
		  temp = g2int_read_icp_remote_value();
		  if (G2int_item_copy_index_space)
		      g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		  argument = temp;
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  else
	      argument = g2int_read_icp_remote_value();
	  ISVREF(arg_array,item_count) = argument;
	  item_count = item_count + (SI_Long)1L;
	  goto next_loop;
	end_loop:;
	  temp = arg_array;
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_resumable_rpc_argument_list,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_resumable_rpc_argument_list,top,Nil);
		goto end_read_icp_resumable_rpc_argument_list;
	    }
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    length_1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_resumable_rpc_argument_list);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_icp_resumable_rpc_argument_list;
	    }
	    length_1 = value;
	}
	rpc_argument_list_error = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,2);
	  arg_array = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_make_gsi_rpc_argument_list(length_1);
	  item_count = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? IFIX(g2int_resumable_icp_pop()) : 
		  IFIX(G2int_gsi_magic_offset);
	  ab_loop_bind_ = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? IFIX(g2int_resumable_icp_pop()) : 
		  IFIX(FIXNUM_ADD1(length_1));
	  argument = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : Nil;
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	      goto resume;
	next_loop_1:
	  if (item_count >= ab_loop_bind_)
	      goto end_loop_1;
	resume:
	  test = Nil;
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      test = g2int_resumable_icp_pop();
	      temp_1 = TRUEP(test);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ? EQ(test,Qg2int_true) : EQ(Qg2int_unbound,
		  G2int_item_copy_index_space)) {
	      item_copy_index_space = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
		      1);
		current_computation_flags = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			G2int_current_computation_flags;
		PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
			0);
		  if ((resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		      gensymed_symbol = g2int_resumable_icp_pop();
		  else {
		      value = g2int_read_icp_remote_value();
		      if (EQ(icp_suspend_1,value)) {
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(G2int_current_computation_flags);
			  g2int_resumable_icp_push(G2int_item_copy_index_space);
			  g2int_resumable_icp_push(Qg2int_true);
			  g2int_resumable_icp_push(argument);
			  g2int_resumable_icp_push(FIX(ab_loop_bind_));
			  g2int_resumable_icp_push(FIX(item_count));
			  g2int_resumable_icp_push(arg_array);
			  g2int_resumable_icp_push(G2int_rpc_argument_list_error);
			  g2int_resumable_icp_push(length_1);
			  g2int_resumable_icp_push(Qg2int_read_icp_resumable_rpc_argument_list);
			  result = VALUES_1(G2int_icp_suspend);
			  POP_SPECIAL();
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_read_icp_resumable_rpc_argument_list;
		      }
		      gensymed_symbol = value;
		  }
		  if (G2int_item_copy_index_space)
		      g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		  argument = gensymed_symbol;
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  else {
	      value = g2int_read_icp_remote_value();
	      if (EQ(icp_suspend_1,value)) {
		  g2int_resumable_icp_push(Qg2int_false);
		  g2int_resumable_icp_push(argument);
		  g2int_resumable_icp_push(FIX(ab_loop_bind_));
		  g2int_resumable_icp_push(FIX(item_count));
		  g2int_resumable_icp_push(arg_array);
		  g2int_resumable_icp_push(G2int_rpc_argument_list_error);
		  g2int_resumable_icp_push(length_1);
		  g2int_resumable_icp_push(Qg2int_read_icp_resumable_rpc_argument_list);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_resumable_rpc_argument_list;
	      }
	      argument = value;
	  }
	  ISVREF(arg_array,item_count) = argument;
	  item_count = item_count + (SI_Long)1L;
	  goto next_loop_1;
	end_loop_1:;
	  temp = arg_array;
	POP_SPECIAL();
    }
    result = VALUES_1(temp);
  end_read_icp_resumable_rpc_argument_list:
    return result;
}

/* INTERN-LIST-OF-ITEM-REFERENCE-ATTRIBUTES */
Object g2int_intern_list_of_item_reference_attributes(identifying_attributes_plist,
	    creation_attributes_plist)
    Object identifying_attributes_plist, creation_attributes_plist;
{
    Object class_1, accumulating_list_p, list_1, element, root, table;
    Object entry_or_table, entry, temp, element_copy, e, cdr_new_value;
    Object element_count_1, root_1, key, val, ab_loop_list_, ab_loop_list__1;
    Object entry_or_table_1, entry_1, result_1;
    SI_Long element_count, limit;

    x_note_fn_call(48,49);
    class_1 = g2int_getfq_function_no_default(identifying_attributes_plist,
	    Qg2int_class);
    if (class_1);
    else
	class_1 = 
		g2int_getfq_function_no_default(creation_attributes_plist,
		Qg2int_class);
    element_count = (SI_Long)0L;
    accumulating_list_p = Nil;
    list_1 = Nil;
    element = Nil;
    root = Nil;
    table = Nil;
    entry_or_table = Nil;
    entry = Nil;
    element = class_1;
    element_count = element_count + (SI_Long)1L;
    if (element_count == (SI_Long)1L) {
	root = SYMBOLP(element) ? element : Nil;
	if (root) {
	    temp = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
		    Qg2int_interned_list_table);
	    if (temp);
	    else {
		accumulating_list_p = T;
		G2int_interned_list_symbols = 
			g2int_interned_list_cons(root,
			G2int_interned_list_symbols);
		temp = root;
		temp = g2int_mutate_global_property(temp,
			g2int_interned_list_cons(Nil,Nil),
			Qg2int_interned_list_table);
	    }
	    table = temp;
	}
	else {
	    temp = G2int_interned_list_non_symbol_root;
	    if (temp);
	    else {
		G2int_interned_list_non_symbol_root = 
			g2int_interned_list_cons(Nil,Nil);
		temp = G2int_interned_list_non_symbol_root;
	    }
	    table = temp;
	}
	if (accumulating_list_p && root)
	    list_1 = g2int_interned_list_cons(root,list_1);
	entry_or_table = table;
	entry = Nil;
    }
    if ( !(element_count == (SI_Long)1L && root)) {
	if (CONSP(entry_or_table))
	    table = entry_or_table;
	else {
	    table = g2int_interned_list_cons(entry_or_table,Nil);
	    M_CDR(entry) = table;
	}
	temp = SYMBOLP(element) ? g2int_assq_function(element,CDR(table)) :
		 g2int_assoc_equal(element,CDR(table));
	if (temp);
	else {
	    element_copy = CONSP(element) ? 
		    g2int_copy_tree_for_interned_list(element) : element;
	    e = g2int_interned_list_cons(element_copy,Nil);
	    cdr_new_value = g2int_interned_list_cons(e,CDR(table));
	    M_CDR(table) = cdr_new_value;
	    if ( !TRUEP(accumulating_list_p)) {
		accumulating_list_p = T;
		element_count_1 = FIX((SI_Long)0L);
		element = Nil;
		root_1 = Nil;
		table = Nil;
		entry_or_table = Nil;
		entry = Nil;
		limit = element_count - (SI_Long)1L;
		if (limit == IFIX(element_count_1))
		    goto end_list_so_far_block;
		element = class_1;
		element_count_1 = FIXNUM_ADD1(element_count_1);
		if (IFIX(element_count_1) == (SI_Long)1L) {
		    root_1 = SYMBOLP(element) ? element : Nil;
		    if (root_1) {
			temp = 
				g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
				Qg2int_interned_list_table);
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    else {
			temp = G2int_interned_list_non_symbol_root;
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    if (accumulating_list_p && root_1)
			list_1 = g2int_interned_list_cons(root_1,list_1);
		    entry_or_table = table;
		    entry = Nil;
		}
		if ( !(IFIX(element_count_1) == (SI_Long)1L && root_1)) {
		    table = CONSP(entry_or_table) ? entry_or_table : Nil;
		    temp = SYMBOLP(element) ? g2int_assq_function(element,
			    CDR(table)) : g2int_assoc_equal(element,
			    CDR(table));
		    if (temp);
		    else
			temp = Nil;
		    entry = temp;
		    if (accumulating_list_p)
			list_1 = g2int_interned_list_cons(CAR(entry),list_1);
		    entry_or_table = CDR(entry);
		}
		key = Nil;
		val = Nil;
		ab_loop_list_ = identifying_attributes_plist;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
	      next_loop:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
		if ( !EQ(key,Qg2int_class)) {
		    if (limit == IFIX(element_count_1))
			goto end_list_so_far_block;
		    element = key;
		    element_count_1 = FIXNUM_ADD1(element_count_1);
		    if (IFIX(element_count_1) == (SI_Long)1L) {
			root_1 = SYMBOLP(element) ? element : Nil;
			if (root_1) {
			    temp = 
				    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
				    Qg2int_interned_list_table);
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			else {
			    temp = G2int_interned_list_non_symbol_root;
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			if (accumulating_list_p && root_1)
			    list_1 = g2int_interned_list_cons(root_1,list_1);
			entry_or_table = table;
			entry = Nil;
		    }
		    if ( !(IFIX(element_count_1) == (SI_Long)1L && root_1)) {
			table = CONSP(entry_or_table) ? entry_or_table : Nil;
			temp = SYMBOLP(element) ? 
				g2int_assq_function(element,CDR(table)) : 
				g2int_assoc_equal(element,CDR(table));
			if (temp);
			else
			    temp = Nil;
			entry = temp;
			if (accumulating_list_p)
			    list_1 = g2int_interned_list_cons(CAR(entry),
				    list_1);
			entry_or_table = CDR(entry);
		    }
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		goto next_loop;
	      end_loop:;
		key = Nil;
		val = Nil;
		ab_loop_list_ = creation_attributes_plist;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
	      next_loop_1:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
		if ( !EQ(key,Qg2int_class)) {
		    if (limit == IFIX(element_count_1))
			goto end_list_so_far_block;
		    element = key;
		    element_count_1 = FIXNUM_ADD1(element_count_1);
		    if (IFIX(element_count_1) == (SI_Long)1L) {
			root_1 = SYMBOLP(element) ? element : Nil;
			if (root_1) {
			    temp = 
				    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
				    Qg2int_interned_list_table);
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			else {
			    temp = G2int_interned_list_non_symbol_root;
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			if (accumulating_list_p && root_1)
			    list_1 = g2int_interned_list_cons(root_1,list_1);
			entry_or_table = table;
			entry = Nil;
		    }
		    if ( !(IFIX(element_count_1) == (SI_Long)1L && root_1)) {
			table = CONSP(entry_or_table) ? entry_or_table : Nil;
			temp = SYMBOLP(element) ? 
				g2int_assq_function(element,CDR(table)) : 
				g2int_assoc_equal(element,CDR(table));
			if (temp);
			else
			    temp = Nil;
			entry = temp;
			if (accumulating_list_p)
			    list_1 = g2int_interned_list_cons(CAR(entry),
				    list_1);
			entry_or_table = CDR(entry);
		    }
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		goto next_loop_1;
	      end_loop_1:;
	      end_list_so_far_block:;
	    }
	    temp = e;
	}
	entry = temp;
	if (accumulating_list_p)
	    list_1 = g2int_interned_list_cons(CAR(entry),list_1);
	entry_or_table = CDR(entry);
    }
    key = Nil;
    val = Nil;
    ab_loop_list_ = identifying_attributes_plist;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
  next_loop_2:
    key = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    val = CAR(temp);
    if ( !EQ(key,Qg2int_class)) {
	element = key;
	element_count = element_count + (SI_Long)1L;
	if (element_count == (SI_Long)1L) {
	    root = SYMBOLP(element) ? element : Nil;
	    if (root) {
		temp = 
			g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
			Qg2int_interned_list_table);
		if (temp);
		else {
		    accumulating_list_p = T;
		    G2int_interned_list_symbols = 
			    g2int_interned_list_cons(root,
			    G2int_interned_list_symbols);
		    temp = root;
		    temp = g2int_mutate_global_property(temp,
			    g2int_interned_list_cons(Nil,Nil),
			    Qg2int_interned_list_table);
		}
		table = temp;
	    }
	    else {
		temp = G2int_interned_list_non_symbol_root;
		if (temp);
		else {
		    G2int_interned_list_non_symbol_root = 
			    g2int_interned_list_cons(Nil,Nil);
		    temp = G2int_interned_list_non_symbol_root;
		}
		table = temp;
	    }
	    if (accumulating_list_p && root)
		list_1 = g2int_interned_list_cons(root,list_1);
	    entry_or_table = table;
	    entry = Nil;
	}
	if ( !(element_count == (SI_Long)1L && root)) {
	    if (CONSP(entry_or_table))
		table = entry_or_table;
	    else {
		table = g2int_interned_list_cons(entry_or_table,Nil);
		M_CDR(entry) = table;
	    }
	    temp = SYMBOLP(element) ? g2int_assq_function(element,
		    CDR(table)) : g2int_assoc_equal(element,CDR(table));
	    if (temp);
	    else {
		element_copy = CONSP(element) ? 
			g2int_copy_tree_for_interned_list(element) : element;
		e = g2int_interned_list_cons(element_copy,Nil);
		cdr_new_value = g2int_interned_list_cons(e,CDR(table));
		M_CDR(table) = cdr_new_value;
		if ( !TRUEP(accumulating_list_p)) {
		    accumulating_list_p = T;
		    element_count_1 = FIX((SI_Long)0L);
		    element = Nil;
		    root_1 = Nil;
		    table = Nil;
		    entry_or_table = Nil;
		    entry = Nil;
		    limit = element_count - (SI_Long)1L;
		    if (limit == IFIX(element_count_1))
			goto end_list_so_far_block_1;
		    element = class_1;
		    element_count_1 = FIXNUM_ADD1(element_count_1);
		    if (IFIX(element_count_1) == (SI_Long)1L) {
			root_1 = SYMBOLP(element) ? element : Nil;
			if (root_1) {
			    temp = 
				    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
				    Qg2int_interned_list_table);
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			else {
			    temp = G2int_interned_list_non_symbol_root;
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			if (accumulating_list_p && root_1)
			    list_1 = g2int_interned_list_cons(root_1,list_1);
			entry_or_table = table;
			entry = Nil;
		    }
		    if ( !(IFIX(element_count_1) == (SI_Long)1L && root_1)) {
			table = CONSP(entry_or_table) ? entry_or_table : Nil;
			temp = SYMBOLP(element) ? 
				g2int_assq_function(element,CDR(table)) : 
				g2int_assoc_equal(element,CDR(table));
			if (temp);
			else
			    temp = Nil;
			entry = temp;
			if (accumulating_list_p)
			    list_1 = g2int_interned_list_cons(CAR(entry),
				    list_1);
			entry_or_table = CDR(entry);
		    }
		    key = Nil;
		    val = Nil;
		    ab_loop_list__1 = identifying_attributes_plist;
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_3;
		  next_loop_3:
		    key = CAR(ab_loop_list__1);
		    temp = CDR(ab_loop_list__1);
		    val = CAR(temp);
		    if ( !EQ(key,Qg2int_class)) {
			if (limit == IFIX(element_count_1))
			    goto end_list_so_far_block_1;
			element = key;
			element_count_1 = FIXNUM_ADD1(element_count_1);
			if (IFIX(element_count_1) == (SI_Long)1L) {
			    root_1 = SYMBOLP(element) ? element : Nil;
			    if (root_1) {
				temp = 
					g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
					Qg2int_interned_list_table);
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    else {
				temp = G2int_interned_list_non_symbol_root;
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    if (accumulating_list_p && root_1)
				list_1 = g2int_interned_list_cons(root_1,
					list_1);
			    entry_or_table = table;
			    entry = Nil;
			}
			if ( !(IFIX(element_count_1) == (SI_Long)1L && 
				    root_1)) {
			    table = CONSP(entry_or_table) ? entry_or_table 
				    : Nil;
			    temp = SYMBOLP(element) ? 
				    g2int_assq_function(element,
				    CDR(table)) : 
				    g2int_assoc_equal(element,CDR(table));
			    if (temp);
			    else
				temp = Nil;
			    entry = temp;
			    if (accumulating_list_p)
				list_1 = 
					g2int_interned_list_cons(CAR(entry),
					list_1);
			    entry_or_table = CDR(entry);
			}
		    }
		    ab_loop_list__1 = CDDR(ab_loop_list__1);
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_3;
		    goto next_loop_3;
		  end_loop_3:;
		    key = Nil;
		    val = Nil;
		    ab_loop_list__1 = creation_attributes_plist;
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_4;
		  next_loop_4:
		    key = CAR(ab_loop_list__1);
		    temp = CDR(ab_loop_list__1);
		    val = CAR(temp);
		    if ( !EQ(key,Qg2int_class)) {
			if (limit == IFIX(element_count_1))
			    goto end_list_so_far_block_1;
			element = key;
			element_count_1 = FIXNUM_ADD1(element_count_1);
			if (IFIX(element_count_1) == (SI_Long)1L) {
			    root_1 = SYMBOLP(element) ? element : Nil;
			    if (root_1) {
				temp = 
					g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
					Qg2int_interned_list_table);
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    else {
				temp = G2int_interned_list_non_symbol_root;
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    if (accumulating_list_p && root_1)
				list_1 = g2int_interned_list_cons(root_1,
					list_1);
			    entry_or_table = table;
			    entry = Nil;
			}
			if ( !(IFIX(element_count_1) == (SI_Long)1L && 
				    root_1)) {
			    table = CONSP(entry_or_table) ? entry_or_table 
				    : Nil;
			    temp = SYMBOLP(element) ? 
				    g2int_assq_function(element,
				    CDR(table)) : 
				    g2int_assoc_equal(element,CDR(table));
			    if (temp);
			    else
				temp = Nil;
			    entry = temp;
			    if (accumulating_list_p)
				list_1 = 
					g2int_interned_list_cons(CAR(entry),
					list_1);
			    entry_or_table = CDR(entry);
			}
		    }
		    ab_loop_list__1 = CDDR(ab_loop_list__1);
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_4;
		    goto next_loop_4;
		  end_loop_4:;
		  end_list_so_far_block_1:;
		}
		temp = e;
	    }
	    entry = temp;
	    if (accumulating_list_p)
		list_1 = g2int_interned_list_cons(CAR(entry),list_1);
	    entry_or_table = CDR(entry);
	}
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    goto next_loop_2;
  end_loop_2:;
    key = Nil;
    val = Nil;
    ab_loop_list_ = creation_attributes_plist;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
  next_loop_5:
    key = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    val = CAR(temp);
    if ( !EQ(key,Qg2int_class)) {
	element = key;
	element_count = element_count + (SI_Long)1L;
	if (element_count == (SI_Long)1L) {
	    root = SYMBOLP(element) ? element : Nil;
	    if (root) {
		temp = 
			g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
			Qg2int_interned_list_table);
		if (temp);
		else {
		    accumulating_list_p = T;
		    G2int_interned_list_symbols = 
			    g2int_interned_list_cons(root,
			    G2int_interned_list_symbols);
		    temp = root;
		    temp = g2int_mutate_global_property(temp,
			    g2int_interned_list_cons(Nil,Nil),
			    Qg2int_interned_list_table);
		}
		table = temp;
	    }
	    else {
		temp = G2int_interned_list_non_symbol_root;
		if (temp);
		else {
		    G2int_interned_list_non_symbol_root = 
			    g2int_interned_list_cons(Nil,Nil);
		    temp = G2int_interned_list_non_symbol_root;
		}
		table = temp;
	    }
	    if (accumulating_list_p && root)
		list_1 = g2int_interned_list_cons(root,list_1);
	    entry_or_table = table;
	    entry = Nil;
	}
	if ( !(element_count == (SI_Long)1L && root)) {
	    if (CONSP(entry_or_table))
		table = entry_or_table;
	    else {
		table = g2int_interned_list_cons(entry_or_table,Nil);
		M_CDR(entry) = table;
	    }
	    temp = SYMBOLP(element) ? g2int_assq_function(element,
		    CDR(table)) : g2int_assoc_equal(element,CDR(table));
	    if (temp);
	    else {
		element_copy = CONSP(element) ? 
			g2int_copy_tree_for_interned_list(element) : element;
		e = g2int_interned_list_cons(element_copy,Nil);
		cdr_new_value = g2int_interned_list_cons(e,CDR(table));
		M_CDR(table) = cdr_new_value;
		if ( !TRUEP(accumulating_list_p)) {
		    accumulating_list_p = T;
		    element_count_1 = FIX((SI_Long)0L);
		    element = Nil;
		    root_1 = Nil;
		    table = Nil;
		    entry_or_table = Nil;
		    entry = Nil;
		    limit = element_count - (SI_Long)1L;
		    if (limit == IFIX(element_count_1))
			goto end_list_so_far_block_2;
		    element = class_1;
		    element_count_1 = FIXNUM_ADD1(element_count_1);
		    if (IFIX(element_count_1) == (SI_Long)1L) {
			root_1 = SYMBOLP(element) ? element : Nil;
			if (root_1) {
			    temp = 
				    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
				    Qg2int_interned_list_table);
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			else {
			    temp = G2int_interned_list_non_symbol_root;
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			if (accumulating_list_p && root_1)
			    list_1 = g2int_interned_list_cons(root_1,list_1);
			entry_or_table = table;
			entry = Nil;
		    }
		    if ( !(IFIX(element_count_1) == (SI_Long)1L && root_1)) {
			table = CONSP(entry_or_table) ? entry_or_table : Nil;
			temp = SYMBOLP(element) ? 
				g2int_assq_function(element,CDR(table)) : 
				g2int_assoc_equal(element,CDR(table));
			if (temp);
			else
			    temp = Nil;
			entry = temp;
			if (accumulating_list_p)
			    list_1 = g2int_interned_list_cons(CAR(entry),
				    list_1);
			entry_or_table = CDR(entry);
		    }
		    key = Nil;
		    val = Nil;
		    ab_loop_list__1 = identifying_attributes_plist;
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_6;
		  next_loop_6:
		    key = CAR(ab_loop_list__1);
		    temp = CDR(ab_loop_list__1);
		    val = CAR(temp);
		    if ( !EQ(key,Qg2int_class)) {
			if (limit == IFIX(element_count_1))
			    goto end_list_so_far_block_2;
			element = key;
			element_count_1 = FIXNUM_ADD1(element_count_1);
			if (IFIX(element_count_1) == (SI_Long)1L) {
			    root_1 = SYMBOLP(element) ? element : Nil;
			    if (root_1) {
				temp = 
					g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
					Qg2int_interned_list_table);
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    else {
				temp = G2int_interned_list_non_symbol_root;
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    if (accumulating_list_p && root_1)
				list_1 = g2int_interned_list_cons(root_1,
					list_1);
			    entry_or_table = table;
			    entry = Nil;
			}
			if ( !(IFIX(element_count_1) == (SI_Long)1L && 
				    root_1)) {
			    table = CONSP(entry_or_table) ? entry_or_table 
				    : Nil;
			    temp = SYMBOLP(element) ? 
				    g2int_assq_function(element,
				    CDR(table)) : 
				    g2int_assoc_equal(element,CDR(table));
			    if (temp);
			    else
				temp = Nil;
			    entry = temp;
			    if (accumulating_list_p)
				list_1 = 
					g2int_interned_list_cons(CAR(entry),
					list_1);
			    entry_or_table = CDR(entry);
			}
		    }
		    ab_loop_list__1 = CDDR(ab_loop_list__1);
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_6;
		    goto next_loop_6;
		  end_loop_6:;
		    key = Nil;
		    val = Nil;
		    ab_loop_list__1 = creation_attributes_plist;
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_7;
		  next_loop_7:
		    key = CAR(ab_loop_list__1);
		    temp = CDR(ab_loop_list__1);
		    val = CAR(temp);
		    if ( !EQ(key,Qg2int_class)) {
			if (limit == IFIX(element_count_1))
			    goto end_list_so_far_block_2;
			element = key;
			element_count_1 = FIXNUM_ADD1(element_count_1);
			if (IFIX(element_count_1) == (SI_Long)1L) {
			    root_1 = SYMBOLP(element) ? element : Nil;
			    if (root_1) {
				temp = 
					g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
					Qg2int_interned_list_table);
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    else {
				temp = G2int_interned_list_non_symbol_root;
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    if (accumulating_list_p && root_1)
				list_1 = g2int_interned_list_cons(root_1,
					list_1);
			    entry_or_table = table;
			    entry = Nil;
			}
			if ( !(IFIX(element_count_1) == (SI_Long)1L && 
				    root_1)) {
			    table = CONSP(entry_or_table) ? entry_or_table 
				    : Nil;
			    temp = SYMBOLP(element) ? 
				    g2int_assq_function(element,
				    CDR(table)) : 
				    g2int_assoc_equal(element,CDR(table));
			    if (temp);
			    else
				temp = Nil;
			    entry = temp;
			    if (accumulating_list_p)
				list_1 = 
					g2int_interned_list_cons(CAR(entry),
					list_1);
			    entry_or_table = CDR(entry);
			}
		    }
		    ab_loop_list__1 = CDDR(ab_loop_list__1);
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_7;
		    goto next_loop_7;
		  end_loop_7:;
		  end_list_so_far_block_2:;
		}
		temp = e;
	    }
	    entry = temp;
	    if (accumulating_list_p)
		list_1 = g2int_interned_list_cons(CAR(entry),list_1);
	    entry_or_table = CDR(entry);
	}
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    goto next_loop_5;
  end_loop_5:;
    if ((SI_Long)0L == element_count) {
	temp = G2int_interned_list_nil;
	if (temp);
	else {
	    G2int_interned_list_nil = g2int_make_interned_list_1(Nil);
	    temp = G2int_interned_list_nil;
	}
    }
    else {
	temp = CONSP(entry_or_table) ? CAR(entry_or_table) : entry_or_table;
	if (temp);
	else {
	    if ( !TRUEP(accumulating_list_p)) {
		accumulating_list_p = T;
		element_count_1 = FIX((SI_Long)0L);
		element = Nil;
		root = Nil;
		table = Nil;
		entry_or_table_1 = Nil;
		entry_1 = Nil;
		limit = element_count;
		if (limit == IFIX(element_count_1))
		    goto end_list_so_far_block_3;
		element = class_1;
		element_count_1 = FIXNUM_ADD1(element_count_1);
		if (IFIX(element_count_1) == (SI_Long)1L) {
		    root = SYMBOLP(element) ? element : Nil;
		    if (root) {
			temp = 
				g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
				Qg2int_interned_list_table);
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    else {
			temp = G2int_interned_list_non_symbol_root;
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    if (accumulating_list_p && root)
			list_1 = g2int_interned_list_cons(root,list_1);
		    entry_or_table_1 = table;
		    entry_1 = Nil;
		}
		if ( !(IFIX(element_count_1) == (SI_Long)1L && root)) {
		    table = CONSP(entry_or_table_1) ? entry_or_table_1 : Nil;
		    temp = SYMBOLP(element) ? g2int_assq_function(element,
			    CDR(table)) : g2int_assoc_equal(element,
			    CDR(table));
		    if (temp);
		    else
			temp = Nil;
		    entry_1 = temp;
		    if (accumulating_list_p)
			list_1 = g2int_interned_list_cons(CAR(entry_1),list_1);
		    entry_or_table_1 = CDR(entry_1);
		}
		key = Nil;
		val = Nil;
		ab_loop_list_ = identifying_attributes_plist;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_8;
	      next_loop_8:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
		if ( !EQ(key,Qg2int_class)) {
		    if (limit == IFIX(element_count_1))
			goto end_list_so_far_block_3;
		    element = key;
		    element_count_1 = FIXNUM_ADD1(element_count_1);
		    if (IFIX(element_count_1) == (SI_Long)1L) {
			root = SYMBOLP(element) ? element : Nil;
			if (root) {
			    temp = 
				    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
				    Qg2int_interned_list_table);
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			else {
			    temp = G2int_interned_list_non_symbol_root;
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			if (accumulating_list_p && root)
			    list_1 = g2int_interned_list_cons(root,list_1);
			entry_or_table_1 = table;
			entry_1 = Nil;
		    }
		    if ( !(IFIX(element_count_1) == (SI_Long)1L && root)) {
			table = CONSP(entry_or_table_1) ? entry_or_table_1 
				: Nil;
			temp = SYMBOLP(element) ? 
				g2int_assq_function(element,CDR(table)) : 
				g2int_assoc_equal(element,CDR(table));
			if (temp);
			else
			    temp = Nil;
			entry_1 = temp;
			if (accumulating_list_p)
			    list_1 = g2int_interned_list_cons(CAR(entry_1),
				    list_1);
			entry_or_table_1 = CDR(entry_1);
		    }
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_8;
		goto next_loop_8;
	      end_loop_8:;
		key = Nil;
		val = Nil;
		ab_loop_list_ = creation_attributes_plist;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_9;
	      next_loop_9:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
		if ( !EQ(key,Qg2int_class)) {
		    if (limit == IFIX(element_count_1))
			goto end_list_so_far_block_3;
		    element = key;
		    element_count_1 = FIXNUM_ADD1(element_count_1);
		    if (IFIX(element_count_1) == (SI_Long)1L) {
			root = SYMBOLP(element) ? element : Nil;
			if (root) {
			    temp = 
				    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
				    Qg2int_interned_list_table);
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			else {
			    temp = G2int_interned_list_non_symbol_root;
			    if (temp);
			    else
				temp = Nil;
			    table = temp;
			}
			if (accumulating_list_p && root)
			    list_1 = g2int_interned_list_cons(root,list_1);
			entry_or_table_1 = table;
			entry_1 = Nil;
		    }
		    if ( !(IFIX(element_count_1) == (SI_Long)1L && root)) {
			table = CONSP(entry_or_table_1) ? entry_or_table_1 
				: Nil;
			temp = SYMBOLP(element) ? 
				g2int_assq_function(element,CDR(table)) : 
				g2int_assoc_equal(element,CDR(table));
			if (temp);
			else
			    temp = Nil;
			entry_1 = temp;
			if (accumulating_list_p)
			    list_1 = g2int_interned_list_cons(CAR(entry_1),
				    list_1);
			entry_or_table_1 = CDR(entry_1);
		    }
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_9;
		goto next_loop_9;
	      end_loop_9:;
	      end_list_so_far_block_3:;
	    }
	    result_1 = g2int_make_interned_list_1(nreverse(list_1));
	    if (CONSP(entry_or_table))
		temp = M_CAR(entry_or_table) = result_1;
	    else
		temp = M_CDR(entry) = result_1;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_new;          /* new */

static Object Qg2int_temporary;    /* temporary */

static Object Qg2int_remote;       /* remote */

static Object Qg2int_local;        /* local */

static Object Qg2int_write_icp_item_reference;  /* write-icp-item-reference */

/* WRITE-ICP-ITEM-REFERENCE */
Object g2int_write_icp_item_reference(item_reference)
    Object item_reference;
{
    Object writing_resumable_icp_messages_p, reference_type;
    Object corresponding_icp_object_index, pending_index;
    Object identifying_attributes_plist, creation_attributes_plist, temp, key;
    Object val, ab_loop_list_, class_is_identifying_p;
    Object corresponding_icp_object_index_for_item_reference;
    Object resumable_icp_state_1, icp_suspend_1, top, temp_1, temp_2, temp_3;
    Object temp_4, identifying_attribute_count_1, v1, v2, v3;
    SI_Long identifying_attribute_count;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,50);
    if (G2int_disable_resumability) {
	g2int_write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		1);
	  result = g2int_network_item_reference_information(item_reference);
	  MVS_5(result,reference_type,corresponding_icp_object_index,
		  pending_index,identifying_attributes_plist,
		  creation_attributes_plist);
	  if ( !(EQ(reference_type,Qg2int_new) ? 
		  (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		  (SI_Long)18L ? TRUEP(T) : TRUEP(Nil)) : 
		  IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		  (SI_Long)12L ? TRUEP(T) : TRUEP(Nil))) {
	      g2int_write_icp_byte(G2int_gsi_null_type_tag);
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_write_icp_item_reference;
	  }
	  if (EQ(reference_type,Qg2int_temporary))
	      temp = G2int_rpc_handle_for_temporary_object_handle_type_tag;
	  else if (EQ(reference_type,Qg2int_remote))
	      temp = 
		      G2int_rpc_handle_for_receiving_side_object_handle_type_tag;
	  else if (EQ(reference_type,Qg2int_local))
	      temp = G2int_rpc_handle_for_sending_side_object_type_tag;
	  else if (EQ(reference_type,Qg2int_new))
	      temp = G2int_rpc_handle_for_new_sending_side_object_type_tag;
	  else
	      temp = Qnil;
	  g2int_write_icp_byte(temp);
	  g2int_write_icp_fixnum(corresponding_icp_object_index);
	  if (EQ(Qg2int_new,reference_type)) {
	      identifying_attribute_count = 
		      IFIX(length(identifying_attributes_plist)) >>  -  - 
		      (SI_Long)1L;
	      key = Nil;
	      val = Nil;
	      ab_loop_list_ = identifying_attributes_plist;
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	    next_loop:
	      key = CAR(ab_loop_list_);
	      temp = CDR(ab_loop_list_);
	      val = CAR(temp);
	      if (EQ(key,Qg2int_class)) {
		  class_is_identifying_p = T;
		  goto end;
	      }
	      ab_loop_list_ = CDDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      goto next_loop;
	    end_loop:
	      class_is_identifying_p = Nil;
	      goto end;
	      class_is_identifying_p = Qnil;
	    end:;
	      g2int_write_icp_fixnum(class_is_identifying_p ? FIX( - 
		      identifying_attribute_count) : 
		      FIX(identifying_attribute_count));
	      g2int_write_icp_interned_list_as_value_type(g2int_intern_list_of_item_reference_attributes(identifying_attributes_plist,
		      creation_attributes_plist));
	      corresponding_icp_object_index_for_item_reference = Nil;
	      PUSH_SPECIAL(G2int_corresponding_icp_object_index_for_item_reference,corresponding_icp_object_index_for_item_reference,
		      0);
		key = Nil;
		val = Nil;
		ab_loop_list_ = identifying_attributes_plist;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
	      next_loop_1:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
		if ( !EQ(key,Qg2int_class))
		    g2int_write_icp_remote_value(val);
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		goto next_loop_1;
	      end_loop_1:;
		key = Nil;
		val = Nil;
		ab_loop_list_ = creation_attributes_plist;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
	      next_loop_2:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
		if ( !EQ(key,Qg2int_class))
		    g2int_write_icp_remote_value(val);
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		goto next_loop_2;
	      end_loop_2:;
	      POP_SPECIAL();
	      g2int_reclaim_gensym_list_1(identifying_attributes_plist);
	      temp = g2int_reclaim_gensym_list_1(creation_attributes_plist);
	  }
	  else
	      temp = Nil;
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_item_reference,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_item_reference,top,Nil);
		goto end_write_icp_item_reference;
	    }
	}
	item_reference = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item_reference;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
	if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		1);
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      temp_2 = g2int_resumable_icp_pop();
	      temp_3 = g2int_resumable_icp_pop();
	      temp_4 = g2int_resumable_icp_pop();
	      temp = g2int_resumable_icp_pop();
	      result = VALUES_5(temp_1,temp_2,temp_3,temp_4,temp);
	  }
	  else
	      result = g2int_network_item_reference_information(item_reference);
	  MVS_5(result,reference_type,corresponding_icp_object_index,
		  pending_index,identifying_attributes_plist,
		  creation_attributes_plist);
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp)) {
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
		    default:
		      break;
		  }
	  }
	pending_index_1:
	l1_1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  ||  !(EQ(reference_type,Qg2int_new) ? 
		  (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		  (SI_Long)18L ? TRUEP(T) : TRUEP(Nil)) : 
		  IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		  (SI_Long)12L ? TRUEP(T) : TRUEP(Nil))) {
	      if (EQ(icp_suspend_1,
		      g2int_write_icp_byte(G2int_gsi_null_type_tag))) {
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_write_icp_item_reference;
	  }
	l2_1:
	  if (EQ(reference_type,Qg2int_temporary))
	      temp = G2int_rpc_handle_for_temporary_object_handle_type_tag;
	  else if (EQ(reference_type,Qg2int_remote))
	      temp = 
		      G2int_rpc_handle_for_receiving_side_object_handle_type_tag;
	  else if (EQ(reference_type,Qg2int_local))
	      temp = G2int_rpc_handle_for_sending_side_object_type_tag;
	  else if (EQ(reference_type,Qg2int_new))
	      temp = G2int_rpc_handle_for_new_sending_side_object_type_tag;
	  else
	      temp = Qnil;
	  if (EQ(icp_suspend_1,g2int_write_icp_byte(temp))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      result = VALUES_1(G2int_icp_suspend);
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_fixnum(corresponding_icp_object_index))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      result = VALUES_1(G2int_icp_suspend);
	      goto end_block_1;
	  }
	l4:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  || EQ(Qg2int_new,reference_type)) {
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  temp = g2int_resumable_icp_pop();
		  if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp)) {
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
	      identifying_attribute_count_1 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      FIX(IFIX(length(identifying_attributes_plist)) >>  - 
		       - (SI_Long)1L);
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  class_is_identifying_p = g2int_resumable_icp_pop();
	      else {
		  key = Nil;
		  val = Nil;
		  ab_loop_list_ = identifying_attributes_plist;
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_3;
		next_loop_3:
		  key = CAR(ab_loop_list_);
		  temp = CDR(ab_loop_list_);
		  val = CAR(temp);
		  if (EQ(key,Qg2int_class)) {
		      class_is_identifying_p = T;
		      goto end_1;
		  }
		  ab_loop_list_ = CDDR(ab_loop_list_);
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_3;
		  goto next_loop_3;
		end_loop_3:
		  class_is_identifying_p = Nil;
		  goto end_1;
		  class_is_identifying_p = Qnil;
		end_1:;
	      }
	      if (EQ(icp_suspend_1,
		      g2int_write_icp_fixnum(class_is_identifying_p ? 
		      FIXNUM_NEGATE(identifying_attribute_count_1) : 
		      identifying_attribute_count_1))) {
		  g2int_resumable_icp_push(class_is_identifying_p);
		  g2int_resumable_icp_push(identifying_attribute_count_1);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_2;
	      }
	    l2_2:
	      if (EQ(icp_suspend_1,
		      g2int_write_icp_interned_list_as_value_type(g2int_intern_list_of_item_reference_attributes(identifying_attributes_plist,
		      creation_attributes_plist)))) {
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_2;
	      }
	    l3_1:
	      corresponding_icp_object_index_for_item_reference = 
		      (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      PUSH_SPECIAL(G2int_corresponding_icp_object_index_for_item_reference,corresponding_icp_object_index_for_item_reference,
		      0);
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
		key = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		val = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loop_list_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			identifying_attributes_plist;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		    goto resume;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_4;
	      next_loop_4:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
	      resume:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) ||  !EQ(key,Qg2int_class)) {
		    if (EQ(icp_suspend_1,g2int_write_icp_remote_value(val))) {
			g2int_resumable_icp_push(ab_loop_list_);
			g2int_resumable_icp_push(val);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			temp = G2int_icp_suspend;
			goto end_block_3;
		    }
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_4;
		goto next_loop_4;
	      end_loop_4:;
	      l2_3:
		key = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		val = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loop_list_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			creation_attributes_plist;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		    goto resume_1;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
	      next_loop_5:
		key = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		val = CAR(temp);
	      resume_1:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) ||  !EQ(key,Qg2int_class)) {
		    if (EQ(icp_suspend_1,g2int_write_icp_remote_value(val))) {
			g2int_resumable_icp_push(ab_loop_list_);
			g2int_resumable_icp_push(val);
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			temp = G2int_icp_suspend;
			goto end_block_3;
		    }
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
		goto next_loop_5;
	      end_loop_5:
		temp = Qnil;
		goto end_block_3;
	      end_block_3:
		if (EQ(icp_suspend_1,temp)) {
		    g2int_resumable_icp_push(G2int_corresponding_icp_object_index_for_item_reference);
		    g2int_resumable_icp_push(FIX((SI_Long)3L));
		    result = VALUES_1(G2int_icp_suspend);
		    POP_SPECIAL();
		    goto end_block_2;
		}
	      POP_SPECIAL();
	      g2int_reclaim_gensym_list_1(identifying_attributes_plist);
	      result = g2int_reclaim_gensym_list_1(creation_attributes_plist);
	      goto end_block_2;
	    end_block_2:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  g2int_resumable_icp_push(FIX((SI_Long)4L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	      result = VALUES_3(v1,v2,v3);
	  }
	  else
	      result = VALUES_1(Nil);
	  goto end_block_1;
	end_block_1:
	  MVS_3(result,v1,v2,v3);
	  if (EQ(icp_suspend_1,v1)) {
	      g2int_resumable_icp_push(creation_attributes_plist);
	      g2int_resumable_icp_push(identifying_attributes_plist);
	      g2int_resumable_icp_push(pending_index);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(reference_type);
	      g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_block;
	  }
	  result = VALUES_3(v1,v2,v3);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(item_reference);
	    g2int_resumable_icp_push(Qg2int_write_icp_item_reference);
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_write_icp_item_reference;
	}
	temp = v1;
    }
    result = VALUES_1(temp);
  end_write_icp_item_reference:
    return result;
}

static Object Qg2int_read_reference_attributes;  /* read-reference-attributes */

/* READ-REFERENCE-ATTRIBUTES */
Object g2int_read_reference_attributes(attr_list,limit,class_qm)
    Object attr_list, limit, class_qm;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(48,51);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_reference_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_reference_attributes,top,Nil);
	}
	attr_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : attr_list;
	limit = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : limit;
	class_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : class_qm;
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object string_constant_7;   /* "Internal error: Bad type-tag for reading an item reference" */

static Object Qg2int_item_index_space;  /* item-index-space */

static Object Qg2int_reading_new_item_reference;  /* reading-new-item-reference */

static Object string_constant_8;   /* "an item sent by reference has been deleted" */

static Object Qg2int_gsi_class_is_identifying_flag;  /* gsi-class-is-identifying-flag */

static Object string_constant_9;   /* "an item sent by reference could not be found or constructed" */

static Object Qg2int_read_icp_item_reference;  /* read-icp-item-reference */

/* READ-ICP-ITEM-REFERENCE */
Object g2int_read_icp_item_reference()
{
    Object type_tag, corresponding_icp_object_index, temp, item;
    Object identifying_attributes_count_with_class;
    Object identifying_attributes_count;
    Object identifying_attribute_count_for_item_new_copy;
    Object corresponding_icp_object_index_for_item_new_copy;
    Object item_being_read_for_new_reference, resumable_icp_state_1;
    Object icp_suspend_1, top, value, key, class_is_identifying_p_1;
    char class_is_identifying_p;
    Declare_special(3);
    Object result;

    x_note_fn_call(48,52);
    if (G2int_disable_resumability) {
	type_tag = g2int_read_icp_byte();
	corresponding_icp_object_index = g2int_read_icp_fixnum();
	temp = type_tag;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    item = g2int_icp_error_internal(Qerror,string_constant_7,Nil,
		    Nil,Nil);
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 74:
		if (FIXNUM_GE(corresponding_icp_object_index,
			ISVREF(G2int_current_temporary_icp_object_index_space,
			(SI_Long)4L)))
		    g2int_enlarge_index_space(G2int_current_temporary_icp_object_index_space,
			    corresponding_icp_object_index);
		item = 
			ISVREF(ISVREF(ISVREF(G2int_current_temporary_icp_object_index_space,
			(SI_Long)2L),IFIX(corresponding_icp_object_index) 
			>>  -  - (SI_Long)10L),
			IFIX(corresponding_icp_object_index) & (SI_Long)1023L);
		break;
	      case 60:
		item = g2int_get_from_icp_port(G2int_current_icp_port,
			corresponding_icp_object_index,
			Qg2int_item_index_space);
		break;
	      case 61:
		item = 
			g2int_get_from_icp_port(ISVREF(ISVREF(G2int_current_icp_port,
			(SI_Long)2L),(SI_Long)4L),
			corresponding_icp_object_index,
			Qg2int_item_index_space);
		break;
	      case 62:
		item = Qg2int_reading_new_item_reference;
		break;
	      default:
		item = g2int_icp_error_internal(Qerror,string_constant_7,
			Nil,Nil,Nil);
		break;
	    }
	if ( !EQ(item,Qg2int_reading_new_item_reference)) {
	    if ( !TRUEP(item))
		G2int_rpc_argument_list_error = 
			g2int_tformat_text_string(1,string_constant_8);
	    result = VALUES_1(item);
	    goto end_read_icp_item_reference;
	}
	identifying_attributes_count_with_class = g2int_read_icp_fixnum();
	class_is_identifying_p = (SI_Long)0L > 
		IFIX(identifying_attributes_count_with_class);
	identifying_attributes_count = class_is_identifying_p ? 
		FIXNUM_NEGATE(identifying_attributes_count_with_class) : 
		identifying_attributes_count_with_class;
	identifying_attribute_count_for_item_new_copy = 
		identifying_attributes_count;
	PUSH_SPECIAL(G2int_identifying_attribute_count_for_item_new_copy,identifying_attribute_count_for_item_new_copy,
		2);
	  corresponding_icp_object_index_for_item_new_copy = 
		  corresponding_icp_object_index;
	  PUSH_SPECIAL(G2int_corresponding_icp_object_index_for_item_new_copy,corresponding_icp_object_index_for_item_new_copy,
		  1);
	    item_being_read_for_new_reference = Nil;
	    PUSH_SPECIAL(G2int_item_being_read_for_new_reference,item_being_read_for_new_reference,
		    0);
	      item = g2int_read_icp_item_new_copy();
	      if (class_is_identifying_p)
		  g2int_set_gsi_instance_plist_value(item,
			  Qg2int_gsi_class_is_identifying_flag,T);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (item &&  !TRUEP(g2int_text_string_p(item)) && T) {
	    g2int_store_corresponding_item(corresponding_icp_object_index,
		    item);
	    g2int_set_icp_object_index_for_gsi_instance(item,
		    corresponding_icp_object_index,
		    ISVREF(G2int_current_icp_socket,(SI_Long)3L));
	    g2int_gsi_call_receive_registration_callback(item);
	    temp = item;
	}
	else {
	    G2int_rpc_argument_list_error = g2int_text_string_p(item) ? 
		    item : g2int_tformat_text_string(1,string_constant_9);
	    temp = Nil;
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_item_reference,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_item_reference,top,Nil);
		goto end_read_icp_item_reference;
	    }
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    type_tag = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_item_reference);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_icp_item_reference;
	    }
	    type_tag = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(type_tag);
		g2int_resumable_icp_push(Qg2int_read_icp_item_reference);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_icp_item_reference;
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    item = g2int_resumable_icp_pop();
	else {
	    key = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : type_tag;
	    temp = key;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		value = g2int_icp_error_internal(Qerror,string_constant_7,
			Nil,Nil,Nil);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(type_tag);
		    g2int_resumable_icp_push(Qg2int_read_icp_item_reference);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_read_icp_item_reference;
		}
		item = value;
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 74:
		    if (FIXNUM_GE(corresponding_icp_object_index,
			    ISVREF(G2int_current_temporary_icp_object_index_space,
			    (SI_Long)4L)))
			g2int_enlarge_index_space(G2int_current_temporary_icp_object_index_space,
				corresponding_icp_object_index);
		    item = 
			    ISVREF(ISVREF(ISVREF(G2int_current_temporary_icp_object_index_space,
			    (SI_Long)2L),
			    IFIX(corresponding_icp_object_index) >>  -  - 
			    (SI_Long)10L),
			    IFIX(corresponding_icp_object_index) & 
			    (SI_Long)1023L);
		    break;
		  case 60:
		    item = g2int_get_from_icp_port(G2int_current_icp_port,
			    corresponding_icp_object_index,
			    Qg2int_item_index_space);
		    break;
		  case 61:
		    item = 
			    g2int_get_from_icp_port(ISVREF(ISVREF(G2int_current_icp_port,
			    (SI_Long)2L),(SI_Long)4L),
			    corresponding_icp_object_index,
			    Qg2int_item_index_space);
		    break;
		  case 62:
		    item = Qg2int_reading_new_item_reference;
		    break;
		  default:
		    value = g2int_icp_error_internal(Qerror,
			    string_constant_7,Nil,Nil,Nil);
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(corresponding_icp_object_index);
			g2int_resumable_icp_push(type_tag);
			g2int_resumable_icp_push(Qg2int_read_icp_item_reference);
			result = VALUES_1(G2int_icp_suspend);
			goto end_read_icp_item_reference;
		    }
		    item = value;
		    break;
		}
	}
	if ( !(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))) {
	    if ( !EQ(item,Qg2int_reading_new_item_reference)) {
		if ( !TRUEP(item))
		    G2int_rpc_argument_list_error = 
			    g2int_tformat_text_string(1,string_constant_8);
		result = VALUES_1(item);
		goto end_read_icp_item_reference;
	    }
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    identifying_attributes_count_with_class = 
		    g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(type_tag);
		g2int_resumable_icp_push(Qg2int_read_icp_item_reference);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_icp_item_reference;
	    }
	    identifying_attributes_count_with_class = value;
	}
	class_is_identifying_p_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : (SI_Long)0L > 
		IFIX(identifying_attributes_count_with_class) ? T : Nil;
	identifying_attributes_count = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : class_is_identifying_p_1 ? 
		FIXNUM_NEGATE(identifying_attributes_count_with_class) : 
		identifying_attributes_count_with_class;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    item = g2int_resumable_icp_pop();
	else {
	    identifying_attribute_count_for_item_new_copy = 
		    (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : identifying_attributes_count;
	    PUSH_SPECIAL(G2int_identifying_attribute_count_for_item_new_copy,identifying_attribute_count_for_item_new_copy,
		    2);
	      corresponding_icp_object_index_for_item_new_copy = 
		      (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      corresponding_icp_object_index;
	      PUSH_SPECIAL(G2int_corresponding_icp_object_index_for_item_new_copy,corresponding_icp_object_index_for_item_new_copy,
		      1);
		item_being_read_for_new_reference = (resumable_icp_state_1 
			? TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		PUSH_SPECIAL(G2int_item_being_read_for_new_reference,item_being_read_for_new_reference,
			0);
		  if ((resumable_icp_state_1 ? 
			  TRUEP(G2int_starresumable_icp_statestar) : 
			  TRUEP(Nil)) &&  
			  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		      item = g2int_resumable_icp_pop();
		  else {
		      value = g2int_read_icp_item_new_copy();
		      if (EQ(icp_suspend_1,value)) {
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(G2int_item_being_read_for_new_reference);
			  g2int_resumable_icp_push(G2int_corresponding_icp_object_index_for_item_new_copy);
			  g2int_resumable_icp_push(G2int_identifying_attribute_count_for_item_new_copy);
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(identifying_attributes_count);
			  g2int_resumable_icp_push(class_is_identifying_p_1);
			  g2int_resumable_icp_push(identifying_attributes_count_with_class);
			  g2int_resumable_icp_push(item);
			  g2int_resumable_icp_push(corresponding_icp_object_index);
			  g2int_resumable_icp_push(type_tag);
			  g2int_resumable_icp_push(Qg2int_read_icp_item_reference);
			  result = VALUES_1(G2int_icp_suspend);
			  POP_SPECIAL();
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_read_icp_item_reference;
		      }
		      item = value;
		  }
		  if (class_is_identifying_p_1)
		      g2int_set_gsi_instance_plist_value(item,
			      Qg2int_gsi_class_is_identifying_flag,T);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	if (item &&  !TRUEP(g2int_text_string_p(item)) && T) {
	    g2int_store_corresponding_item(corresponding_icp_object_index,
		    item);
	    g2int_set_icp_object_index_for_gsi_instance(item,
		    corresponding_icp_object_index,
		    ISVREF(G2int_current_icp_socket,(SI_Long)3L));
	    g2int_gsi_call_receive_registration_callback(item);
	    temp = item;
	}
	else {
	    G2int_rpc_argument_list_error = g2int_text_string_p(item) ? 
		    item : g2int_tformat_text_string(1,string_constant_9);
	    temp = Nil;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_item_reference:
    return result;
}

/* GSI-CALL-RECEIVE-REGISTRATION-CALLBACK */
Object g2int_gsi_call_receive_registration_callback(item)
    Object item;
{
    Object temp;

    x_note_fn_call(48,53);
    temp = g2int_call_gsi_callback(2,G2int_gsi_receive_registration,item);
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_item_reference_2;  /* write-icp-item-reference-2 */

/* WRITE-ICP-ITEM-REFERENCE-2 */
Object g2int_write_icp_item_reference_2(item)
    Object item;
{
    Object item_copy_index_space, current_computation_flags, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, test, gensymed_symbol;
    Object value;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(48,54);
    if (G2int_disable_resumability) {
	if (EQ(Qg2int_unbound,G2int_item_copy_index_space)) {
	    item_copy_index_space = Nil;
	    current_computation_flags = G2int_current_computation_flags;
	    PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		    1);
	      PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
		      0);
		temp = g2int_write_icp_item_reference(item);
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = g2int_write_icp_item_reference(item);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_item_reference_2,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_item_reference_2,top,Nil);
		goto end_write_icp_item_reference_2;
	    }
	}
	item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : EQ(Qg2int_unbound,
		G2int_item_copy_index_space)) {
	    item_copy_index_space = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,1);
	      current_computation_flags = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      G2int_current_computation_flags;
	      PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		      0);
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    gensymed_symbol = g2int_resumable_icp_pop();
		else {
		    value = g2int_write_icp_item_reference(item);
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(G2int_current_computation_flags);
			g2int_resumable_icp_push(G2int_item_copy_index_space);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(item);
			g2int_resumable_icp_push(Qg2int_write_icp_item_reference_2);
			result = VALUES_1(G2int_icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_write_icp_item_reference_2;
		    }
		    gensymed_symbol = value;
		}
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		temp = gensymed_symbol;
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else {
	    value = g2int_write_icp_item_reference(item);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(item);
		g2int_resumable_icp_push(Qg2int_write_icp_item_reference_2);
		result = VALUES_1(G2int_icp_suspend);
		goto end_write_icp_item_reference_2;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_item_reference_2:
    return result;
}

static Object Qg2int_read_icp_item_reference_2;  /* read-icp-item-reference-2 */

/* READ-ICP-ITEM-REFERENCE-2 */
Object g2int_read_icp_item_reference_2()
{
    Object item_copy_index_space, current_computation_flags;
    Object rpc_argument_list_error, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, test, gensymed_symbol, value;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(48,55);
    if (G2int_disable_resumability) {
	if (EQ(Qg2int_unbound,G2int_item_copy_index_space)) {
	    item_copy_index_space = Nil;
	    current_computation_flags = G2int_current_computation_flags;
	    PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		    2);
	      PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
		      1);
		rpc_argument_list_error = Nil;
		PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
			0);
		  temp = g2int_read_icp_item_reference();
		POP_SPECIAL();
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else {
	    rpc_argument_list_error = Nil;
	    PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
		    0);
	      temp = g2int_read_icp_item_reference();
	    POP_SPECIAL();
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_item_reference_2,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_item_reference_2,top,Nil);
		goto end_read_icp_item_reference_2;
	    }
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : EQ(Qg2int_unbound,
		G2int_item_copy_index_space)) {
	    item_copy_index_space = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,2);
	      current_computation_flags = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      G2int_current_computation_flags;
	      PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		      1);
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    gensymed_symbol = g2int_resumable_icp_pop();
		else {
		    rpc_argument_list_error = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : Nil;
		    PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
			    0);
		      value = g2int_read_icp_item_reference();
		      if (EQ(icp_suspend_1,value)) {
			  g2int_resumable_icp_push(G2int_rpc_argument_list_error);
			  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			  g2int_resumable_icp_push(G2int_current_computation_flags);
			  g2int_resumable_icp_push(G2int_item_copy_index_space);
			  g2int_resumable_icp_push(Qg2int_true);
			  g2int_resumable_icp_push(Qg2int_read_icp_item_reference_2);
			  result = VALUES_1(G2int_icp_suspend);
			  POP_SPECIAL();
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_read_icp_item_reference_2;
		      }
		      gensymed_symbol = value;
		    POP_SPECIAL();
		}
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		temp = gensymed_symbol;
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else {
	    rpc_argument_list_error = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
		    0);
	      value = g2int_read_icp_item_reference();
	      if (EQ(icp_suspend_1,value)) {
		  g2int_resumable_icp_push(G2int_rpc_argument_list_error);
		  g2int_resumable_icp_push(Qg2int_false);
		  g2int_resumable_icp_push(Qg2int_read_icp_item_reference_2);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_item_reference_2;
	      }
	      temp = value;
	    POP_SPECIAL();
	}
    }
    result = VALUES_1(temp);
  end_read_icp_item_reference_2:
    return result;
}

static Object Qg2int_send_icp_create_item_reference;  /* send-icp-create-item-reference */

/* SEND-ICP-CREATE-ITEM-REFERENCE */
Object g2int_send_icp_create_item_reference(item)
    Object item;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,56);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_create_item_reference;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)355L));
	  g2int_write_icp_item_reference_2(item);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_create_item_reference,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_create_item_reference,top,Nil);
		goto end_send_icp_create_item_reference;
	    }
	}
	item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : item;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_create_item_reference;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
		  g2int_start_writing_icp_message(FIX((SI_Long)355L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,g2int_write_icp_item_reference_2(item))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(item);
	      g2int_resumable_icp_push(Qg2int_send_icp_create_item_reference);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_create_item_reference;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_create_item_reference:
    return result;
}

/* HANDLE-ICP-CREATE-ITEM-REFERENCE--BODY */
Object g2int_handle_icp_create_item_reference__body(item)
    Object item;
{
    x_note_fn_call(48,57);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_create_item_reference;  /* handle-icp-create-item-reference */

/* HANDLE-ICP-CREATE-ITEM-REFERENCE */
Object g2int_handle_icp_create_item_reference()
{
    Object item, abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(48,58);
    if (G2int_disable_resumability) {
	item = g2int_read_icp_item_reference_2();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_create_item_reference__body(item);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_create_item_reference,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_create_item_reference,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    item = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_item_reference_2();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_create_item_reference);
		return VALUES_1(G2int_icp_suspend);
	    }
	    item = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_create_item_reference__body(item);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* NETWORK-ITEM-REFERENCE-INFORMATION */
Object g2int_network_item_reference_information(item)
    Object item;
{
    Object pending_item, ab_loop_list_, pending_index, class_description_p;
    Object gsi_instance_extension, object_map, corresponding_icp_object_index;
    Object identifying_attributes_plist, creation_attributes_plist;
    SI_Long i;
    Object result;

    x_note_fn_call(48,59);
    if (G2int_using_pending_write_reference_list) {
	i = (SI_Long)0L;
	pending_item = Nil;
	ab_loop_list_ = G2int_pending_write_reference_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pending_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(item,pending_item)) {
	    pending_index = FIX(i);
	    goto end;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	pending_index = Qnil;
      end:;
    }
    else
	pending_index = Nil;
    class_description_p = Nil;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    object_map = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)13L) : Nil;
    if (G2int_inhibit_corresponding_icp_object_making) {
	corresponding_icp_object_index = 
		g2int_getfq_function_no_default(object_map,
		ISVREF(G2int_current_icp_socket,(SI_Long)4L));
	if (corresponding_icp_object_index)
	    return VALUES_3(Qg2int_temporary,
		    corresponding_icp_object_index,pending_index);
    }
    if ( !TRUEP(G2int_corresponding_icp_object_index_for_item_reference)) {
	corresponding_icp_object_index = 
		g2int_getfq_function_no_default(object_map,
		ISVREF(G2int_current_icp_socket,(SI_Long)4L));
	if (corresponding_icp_object_index)
	    return VALUES_3(Qg2int_local,corresponding_icp_object_index,
		    pending_index);
	corresponding_icp_object_index = 
		g2int_getfq_function_no_default(object_map,
		ISVREF(G2int_current_icp_socket,(SI_Long)3L));
	if (corresponding_icp_object_index)
	    return VALUES_3(Qg2int_remote,corresponding_icp_object_index,
		    pending_index);
    }
    corresponding_icp_object_index = 
	    G2int_corresponding_icp_object_index_for_item_reference;
    if (corresponding_icp_object_index);
    else
	corresponding_icp_object_index = 
		g2int_establish_new_object_index_for_gsi_instance(3,item,
		ISVREF(G2int_current_icp_socket,(SI_Long)4L),Nil);
    if (G2int_inhibit_corresponding_icp_object_making)
	return VALUES_3(Qg2int_temporary,corresponding_icp_object_index,Nil);
    else {
	if (G2int_using_pending_write_reference_list)
	    G2int_pending_write_reference_list = 
		    nconc2(G2int_pending_write_reference_list,
		    g2int_gensym_cons_1(item,Nil));
	if (class_description_p)
	    result = g2int_get_class_description_reference_attributes(item);
	else
	    result = g2int_get_item_reference_attributes(item);
	MVS_2(result,identifying_attributes_plist,creation_attributes_plist);
	return VALUES_5(Qg2int_new,corresponding_icp_object_index,Nil,
		identifying_attributes_plist,creation_attributes_plist);
    }
}

Object G2int_current_network_interface = UNBOUND;

Object G2int_reference_class_info_p = UNBOUND;

/* GET-CLASS-DESCRIPTION-REFERENCE-ATTRIBUTES */
Object g2int_get_class_description_reference_attributes(class_description)
    Object class_description;
{
    x_note_fn_call(48,60);
    return VALUES_1(Nil);
}

static Object Qg2int_home;         /* home */

/* GET-ITEM-REFERENCE-ATTRIBUTES */
Object g2int_get_item_reference_attributes(item)
    Object item;
{
    Object gsi_instance_extension, attribute_count;
    Object attribute_count_with_offset, attributes, attribute, attribute_value;
    Object transientp, identifyingp, attribute_name;
    Object identifying_attributes_plist, ab_loopvar_, ab_loopvar__1;
    Object creation_attributes_plist, ab_loopvar__2, value_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(48,61);
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    attribute_count = gsi_instance_extension ? 
	    ISVREF(gsi_instance_extension,(SI_Long)9L) : FIX((SI_Long)0L);
    attribute_count_with_offset = FIXNUM_ADD1(attribute_count);
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    attributes = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)8L) : Nil;
    i = IFIX(G2int_gsi_magic_offset);
    ab_loop_bind_ = IFIX(attribute_count_with_offset);
    attribute = Nil;
    attribute_value = Nil;
    transientp = Nil;
    identifyingp = Nil;
    attribute_name = Nil;
    identifying_attributes_plist = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    creation_attributes_plist = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    attribute = ISVREF(attributes,i);
    attribute_value = ISVREF(attribute,(SI_Long)4L);
    transientp = (SI_Long)1L == ((SI_Long)1L & IFIX(ISVREF(attribute,
	    (SI_Long)3L))) ? T : Nil;
    identifyingp = (SI_Long)2L == ((SI_Long)2L & IFIX(ISVREF(attribute,
	    (SI_Long)3L))) ? T : Nil;
    attribute_name = g2int_gsi_attribute_qualified_name(attribute);
    if ( !TRUEP(transientp) && identifyingp) {
	ab_loopvar__1 = g2int_gensym_list_2(attribute_name,attribute_value);
	if (ab_loopvar__1) {
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		identifying_attributes_plist = ab_loopvar__1;
	    ab_loopvar_ = last(ab_loopvar__1,_);
	}
    }
    if ( !TRUEP(transientp) &&  !TRUEP(identifyingp)) {
	ab_loopvar__1 = g2int_gensym_list_2(attribute_name,attribute_value);
	if (ab_loopvar__1) {
	    if (ab_loopvar__2)
		M_CDR(ab_loopvar__2) = ab_loopvar__1;
	    else
		creation_attributes_plist = ab_loopvar__1;
	    ab_loopvar__2 = last(ab_loopvar__1,_);
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if ( 
	    !TRUEP(g2int_getfq_function_no_default(identifying_attributes_plist,
	    Qg2int_home)))
	identifying_attributes_plist = 
		nconc2(g2int_gensym_list_2(Qg2int_home,
		G2int_gsi_local_home),identifying_attributes_plist);
    if ( !(g2int_getfq_function_no_default(identifying_attributes_plist,
	    Qg2int_class) || 
	    g2int_getfq_function_no_default(creation_attributes_plist,
	    Qg2int_class))) {
	value_1 = g2int_class_for_gsi_item(item);
	if (value_1) {
	    if (g2int_get_gsi_instance_plist_value(item,
		    Qg2int_gsi_class_is_identifying_flag))
		identifying_attributes_plist = 
			nconc2(g2int_gensym_list_2(Qg2int_class,value_1),
			identifying_attributes_plist);
	    else
		creation_attributes_plist = 
			nconc2(g2int_gensym_list_2(Qg2int_class,value_1),
			creation_attributes_plist);
	}
    }
    if ( !(g2int_getfq_function_no_default(identifying_attributes_plist,
	    Qg2int_names) || 
	    g2int_getfq_function_no_default(creation_attributes_plist,
	    Qg2int_names))) {
	gsi_instance_extension = ISVREF(item,(SI_Long)3L);
	value_1 = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)4L) : Nil;
	if (value_1) {
	    if (g2int_get_gsi_instance_plist_value(item,
		    Qg2int_gsi_name_is_identifying_flag))
		identifying_attributes_plist = 
			nconc2(g2int_gensym_list_2(Qg2int_names,value_1),
			identifying_attributes_plist);
	    else
		creation_attributes_plist = 
			nconc2(g2int_gensym_list_2(Qg2int_names,value_1),
			creation_attributes_plist);
	}
    }
    return VALUES_2(identifying_attributes_plist,creation_attributes_plist);
    return VALUES_1(Qnil);
}

/* SELECT-ATTRIBUTES-FROM-ITEM */
Object g2int_select_attributes_from_item(item,identifying_attributes,
	    network_attribute_plist)
    Object item, identifying_attributes, network_attribute_plist;
{
    x_note_fn_call(48,62);
    return VALUES_1(Nil);
}

/* IDENTIFYING-OR-CREATION-ATTRIBUTES-OF-ITEM-FOR-INTERFACE */
Object g2int_identifying_or_creation_attributes_of_item_for_interface(item,
	    interface_1,identifying_p)
    Object item, interface_1, identifying_p;
{
    x_note_fn_call(48,63);
    return VALUES_1(Nil);
}

/* LOOKUP-OR-CREATE-ITEM-FROM-REFERENCE-ATTRIBUTES */
Object g2int_lookup_or_create_item_from_reference_attributes(identifying_attributes,
	    creation_attributes,reclaim_p,allow_create_p)
    Object identifying_attributes, creation_attributes, reclaim_p;
    Object allow_create_p;
{
    x_note_fn_call(48,64);
    return VALUES_1(Nil);
}

/* PROCESS-REGISTER-ITEM-REFERENCE-ATTRIBUTES */
Object g2int_process_register_item_reference_attributes(identifying_attributes,
	    creation_attributes,interface_identifying_attributes,
	    interface_creation_attributes,item_reference_options)
    Object identifying_attributes, creation_attributes;
    Object interface_identifying_attributes, interface_creation_attributes;
    Object item_reference_options;
{
    x_note_fn_call(48,65);
    return VALUES_1(Nil);
}

/* GET-ATTRIBUTE-TRANSLATIONS */
Object g2int_get_attribute_translations(class_1,interface_attributes)
    Object class_1, interface_attributes;
{
    x_note_fn_call(48,66);
    return VALUES_1(Nil);
}

/* LOOKUP-ITEM-FROM-FRAME-OR-FRAMES */
Object g2int_lookup_item_from_frame_or_frames(frame_or_frames,
	    identifying_attributes,class_1,names,attribute_translations,list_p)
    Object frame_or_frames, identifying_attributes, class_1, names;
    Object attribute_translations, list_p;
{
    x_note_fn_call(48,67);
    return VALUES_1(Nil);
}

/* LOOKUP-ITEM-FROM-IDENTIFYING-ATTRIBUTES-AND-TRANSLATIONS */
Object g2int_lookup_item_from_identifying_attributes_and_translations(identifying_attributes,
	    class_1,names,attribute_translations,list_p)
    Object identifying_attributes, class_1, names, attribute_translations;
    Object list_p;
{
    x_note_fn_call(48,68);
    return VALUES_1(Nil);
}

/* ATTRIBUTE-IS-IN-IDENTIFYING-ATTRIBUTES-P */
Object g2int_attribute_is_in_identifying_attributes_p(attr_name,
	    identifying_attributes,attribute_translations)
    Object attr_name, identifying_attributes, attribute_translations;
{
    x_note_fn_call(48,69);
    return VALUES_1(Nil);
}

/* CHOOSE-ROLE-FOR-IDENTIFYING-ATTRIBUTES */
Object g2int_choose_role_for_identifying_attributes(identifying_attributes,
	    class_1,names,attribute_translations)
    Object identifying_attributes, class_1, names, attribute_translations;
{
    x_note_fn_call(48,70);
    return VALUES_1(Nil);
}

/* ITEM-OR-VALUE-EQUAL */
Object g2int_item_or_value_equal(x,y)
    Object x, y;
{
    x_note_fn_call(48,71);
    return VALUES_1(Nil);
}

/* ITEM-MATCHES-IDENTIFYING-ATTRIBUTES-P */
Object g2int_item_matches_identifying_attributes_p(item,
	    identifying_attributes,class_1,names,attribute_translations)
    Object item, identifying_attributes, class_1, names;
    Object attribute_translations;
{
    x_note_fn_call(48,72);
    return VALUES_1(Nil);
}

/* CREATE-ITEM-FROM-ATTRIBUTES-AND-TRANSLATIONS */
Object g2int_create_item_from_attributes_and_translations(identifying_attributes,
	    creation_attributes,class_1,names,
	    identifying_attribute_translations,creation_attribute_translations)
    Object identifying_attributes, creation_attributes, class_1, names;
    Object identifying_attribute_translations, creation_attribute_translations;
{
    x_note_fn_call(48,73);
    return VALUES_1(creation_attribute_translations);
}

Object G2int_remote_gsi_interface_list = UNBOUND;

/* G2-INITIALIZE-GSI-INTERFACE */
Object g2int_g2_initialize_gsi_interface(interface_name,class_name,
	    keep_connection_on_g2_reset,listener_network_type,
	    listener_host_name,listener_port_name,
	    remote_process_initialization_string,already_initialized_p)
    Object interface_name, class_name, keep_connection_on_g2_reset;
    Object listener_network_type, listener_host_name, listener_port_name;
    Object remote_process_initialization_string, already_initialized_p;
{
    x_note_fn_call(48,74);
    return VALUES_1(Nil);
}

/* FIND-NETWORK-INTERFACE-FOR-ICP-SOCKET */
Object g2int_find_network_interface_for_icp_socket(icp_socket,stack_eval_p)
    Object icp_socket, stack_eval_p;
{
    x_note_fn_call(48,75);
    return VALUES_1(Nil);
}

/* GET-ITEM-REFERENCE-ATTRIBUTES-FROM-CURRENT-INTERFACE */
Object g2int_get_item_reference_attributes_from_current_interface()
{
    x_note_fn_call(48,76);
    return VALUES_1(Nil);
}

/* GET-DEFAULT-SLOT-VALUE-FROM-CLASS */
Object g2int_get_default_slot_value_from_class(class_1,slot_name)
    Object class_1, slot_name;
{
    x_note_fn_call(48,77);
    return VALUES_1(Nil);
}

/* CONVERT-NAMES-FOR-NETWORK */
Object g2int_convert_names_for_network(names,add_home_to_name,localp,item_home)
    Object names, add_home_to_name, localp, item_home;
{
    x_note_fn_call(48,78);
    return VALUES_1(names);
}

/* PUT-ON-ICP-PLIST */
Object g2int_put_on_icp_plist(property_1,value,plist)
    Object property_1, value, plist;
{
    Object tail;

    x_note_fn_call(48,79);
    tail = plist;
  next_loop:
    if ( !TRUEP(tail))
	goto end_loop;
    if (EQ(CAR(tail),property_1)) {
	M_CADR(tail) = value;
	return VALUES_1(plist);
    }
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
    return g2int_gensym_cons_1(property_1,g2int_gensym_cons_1(value,plist));
    return VALUES_1(Qnil);
}

/* ASSQ-LOOKUP */
Object g2int_assq_lookup(name,alist,default_1)
    Object name, alist, default_1;
{
    Object gensymed_symbol, ab_loop_list_, a;

    x_note_fn_call(48,80);
    gensymed_symbol = Nil;
    ab_loop_list_ = alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),name)) {
	a = gensymed_symbol;
	goto end;
    }
    goto next_loop;
  end_loop:
    a = Qnil;
  end:;
    if (a)
	return VALUES_1(CDR(a));
    else
	return VALUES_1(default_1);
}

/* COPY-EVALUATION-STRUCTURE-INTO-ITEM */
Object g2int_copy_evaluation_structure_into_item(item,structure,
	    attribute_translations,value_translations)
    Object item, structure, attribute_translations, value_translations;
{
    x_note_fn_call(48,81);
    return VALUES_1(Nil);
}

Object G2int_home_name_separator = UNBOUND;

/* REMOVE-HOME-FROM-NAME */
Object g2int_remove_home_from_name(home,name)
    Object home, name;
{
    Object name_string, home_string;
    SI_Long length_1, name_string_length, home_string_length;
    SI_Long home_name_separator_length, prefix_length, i, ab_loop_bind_;
    char temp;

    x_note_fn_call(48,82);
    if ( !(name && SYMBOLP(name) && home && (SYMBOLP(home) || 
	    g2int_text_string_p(home))))
	return VALUES_1(name);
    else {
	name_string = g2int_symbol_name_text_string(name);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(name_string));
	name_string_length = UBYTE_16_ISAREF_1(name_string,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(name_string,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	home_string = SYMBOLP(home) ? g2int_symbol_name_text_string(home) :
		 home;
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(home_string));
	home_string_length = UBYTE_16_ISAREF_1(home_string,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(home_string,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_home_name_separator));
	home_name_separator_length = 
		UBYTE_16_ISAREF_1(G2int_home_name_separator,length_1 - 
		(SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(G2int_home_name_separator,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	prefix_length = home_string_length + home_name_separator_length;
	temp = (SI_Long)0L == home_string_length;
	if (temp);
	else
	    temp = (SI_Long)0L == name_string_length;
	if (temp);
	else
	    temp = name_string_length < prefix_length;
	if (temp);
	else {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = home_string_length;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if ( !(UBYTE_16_ISAREF_1(name_string,i) == 
		    UBYTE_16_ISAREF_1(home_string,i))) {
		temp = TRUEP(T);
		goto end;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(Nil);
	    goto end;
	    temp = TRUEP(Qnil);
	  end:;
	}
	if (temp);
	else {
	    ab_loop_bind_ = home_name_separator_length;
	    i = (SI_Long)0L;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    if ( !(UBYTE_16_ISAREF_1(G2int_home_name_separator,i) == 
		    UBYTE_16_ISAREF_1(name_string,i + home_string_length))) {
		temp = TRUEP(T);
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Nil);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	if (temp)
	    return VALUES_1(name);
	else
	    return g2int_intern_text_string(1,
		    g2int_copy_text_string_portion(name,FIX(prefix_length),
		    FIX(name_string_length)));
    }
}

static Object string_constant_10;  /* "~A~A~A" */

/* ADD-HOME-TO-NAME */
Object g2int_add_home_to_name(home,name)
    Object home, name;
{
    Object name_string, home_string;

    x_note_fn_call(48,83);
    if ( !(name && SYMBOLP(name) && home && (SYMBOLP(home) || 
	    g2int_text_string_p(home))))
	return VALUES_1(name);
    else {
	name_string = g2int_symbol_name_text_string(name);
	home_string = SYMBOLP(home) ? g2int_symbol_name_text_string(home) :
		 home;
	return g2int_intern_text_string(1,g2int_tformat_text_string(4,
		string_constant_10,home_string,G2int_home_name_separator,
		name_string));
    }
}

/* INTERNED-LIST--REMOTE-PROCEDURE-ITEM-PASSING-LISTS */
Object g2int_interned_list__remote_procedure_item_passing_lists(interned_list)
    Object interned_list;
{
    Object list_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, list_of_nils;
    Object list_old_value, temp, temp_1, temp_2, temp_3, temp_4, temp_5;
    Object temp_6, included_attributes_spec;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(48,84);
    list_1 = ISVREF(interned_list,(SI_Long)1L);
    if (list_1 && FIXNUMP(CAR(list_1)) &&  !TRUEP(CDR(list_1))) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(CAR(list_1));
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ab_loopvar__2 = g2int_gensym_cons_1(Nil,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	list_of_nils = ab_loopvar_;
	goto end;
	list_of_nils = Qnil;
      end:;
	return VALUES_7(list_of_nils,list_of_nils,list_of_nils,
		list_of_nils,list_of_nils,list_of_nils,Nil);
    }
    else if ((SI_Long)7L == IFIX(length(list_1))) {
	list_old_value = list_1;
	temp = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_1 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_2 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_3 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_4 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_5 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_6 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	return VALUES_7(temp,temp_1,temp_2,temp_3,temp_4,temp_5,temp_6);
    }
    else {
	list_old_value = list_1;
	temp = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	included_attributes_spec = temp;
	list_old_value = list_1;
	temp = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_1 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_2 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(included_attributes_spec));
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ab_loopvar__2 = g2int_gensym_cons_1(Nil,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_3 = ab_loopvar_;
	goto end_1;
	temp_3 = Qnil;
      end_1:;
	list_old_value = list_1;
	temp_4 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	list_old_value = list_1;
	temp_5 = FIRST(list_old_value);
	list_1 = REST(list_old_value);
	return VALUES_7(included_attributes_spec,temp,temp_1,temp_2,temp_3,
		temp_4,temp_5);
    }
}

static Object Qg2int_remote_procedure_item_passing_info;  /* remote-procedure-item-passing-info */

/* SET-INTERNED-LIST--REMOTE-PROCEDURE-ITEM-PASSING-INFO */
Object g2int_set_interned_list__remote_procedure_item_passing_info(interned_list,
	    value)
    Object interned_list, value;
{
    Object plist, tail, svref_new_value;

    x_note_fn_call(48,85);
    plist = ISVREF(interned_list,(SI_Long)3L);
    tail = g2int_memq_function(Qg2int_remote_procedure_item_passing_info,
	    plist);
    if (tail)
	M_CADR(tail) = value;
    else {
	svref_new_value = 
		g2int_gensym_cons_1(Qg2int_remote_procedure_item_passing_info,
		g2int_gensym_cons_1(value,plist));
	SVREF(interned_list,FIX((SI_Long)3L)) = svref_new_value;
    }
    return VALUES_1(value);
}

/* GET-REMOTE-PROCEDURE-ITEM-PASSING-INFO-FOR-INTERNED-LIST */
Object g2int_get_remote_procedure_item_passing_info_for_interned_list(interned_list)
    Object interned_list;
{
    Object temp, list_1, included_attributes_spec, excluded_attributes_spec;
    Object included_system_attributes_spec, include_all_system_attributes_spec;
    Object include_all_system_attributes_except_spec, kind_spec, varargs_p;
    Object list_of_interned_item_infos, info, ab_loop_list_, incl_attr;
    Object excl_attr, incl_sys_attr, incl_all_sys_attr, kind, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object new_list_of_interned_item_infos, new_list;
    char temp_1;
    Object result;

    x_note_fn_call(48,86);
    temp = g2int_getfq_function_no_default(ISVREF(interned_list,
	    (SI_Long)3L),Qg2int_remote_procedure_item_passing_info);
    if (temp);
    else {
	list_1 = ISVREF(interned_list,(SI_Long)1L);
	if (list_1) {
	    temp_1 =  !TRUEP(CDR(list_1)) ? FIXNUMP(CAR(list_1)) : TRUEP(Qnil);
	    if (temp_1);
	    else {
		temp = CAR(list_1);
		temp_1 = CONSP(temp);
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    result = g2int_interned_list__remote_procedure_item_passing_lists(interned_list);
	    MVS_7(result,included_attributes_spec,excluded_attributes_spec,
		    included_system_attributes_spec,
		    include_all_system_attributes_spec,
		    include_all_system_attributes_except_spec,kind_spec,
		    varargs_p);
	    temp = 
		    g2int_make_remote_procedure_item_passing_info_from_specs(T,
		    included_attributes_spec,excluded_attributes_spec,
		    included_system_attributes_spec,
		    include_all_system_attributes_spec,
		    include_all_system_attributes_except_spec,kind_spec,
		    varargs_p);
	}
	else {
	    temp = ISVREF(interned_list,(SI_Long)1L);
	    if (CDR(temp)) {
		temp = ISVREF(interned_list,(SI_Long)1L);
		temp_1 = (SI_Long)6L == IFIX(length(ISVREF(CADR(temp),
			(SI_Long)1L)));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp = interned_list;
	    else {
		list_1 = ISVREF(interned_list,(SI_Long)1L);
		varargs_p = CAR(list_1);
		list_of_interned_item_infos = CDR(list_1);
		info = Nil;
		ab_loop_list_ = list_of_interned_item_infos;
		incl_attr = Nil;
		excl_attr = Nil;
		incl_sys_attr = Nil;
		incl_all_sys_attr = Nil;
		kind = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		ab_loop_desetq_ = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		info = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loop_desetq_ = ISVREF(info,(SI_Long)1L);
		incl_attr = CAR(ab_loop_desetq_);
		temp = CDR(ab_loop_desetq_);
		excl_attr = CAR(temp);
		temp = CDR(ab_loop_desetq_);
		temp = CDR(temp);
		incl_sys_attr = CAR(temp);
		temp = CDR(ab_loop_desetq_);
		temp = CDR(temp);
		temp = CDR(temp);
		incl_all_sys_attr = CAR(temp);
		temp = CDR(ab_loop_desetq_);
		temp = CDR(temp);
		temp = CDR(temp);
		temp = CDR(temp);
		kind = CAR(temp);
		ab_loopvar__2 = 
			g2int_gensym_cons_1(g2int_make_remote_procedure_item_info(incl_attr,
			excl_attr,incl_sys_attr,incl_all_sys_attr,Nil,
			kind),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop;
	      end_loop:
		new_list_of_interned_item_infos = ab_loopvar_;
		goto end;
		new_list_of_interned_item_infos = Qnil;
	      end:;
		new_list = g2int_gensym_cons_1(varargs_p,
			new_list_of_interned_item_infos);
		temp = g2int_intern_list(new_list);
		g2int_reclaim_gensym_list_1(new_list);
	    }
	    temp = 
		    g2int_make_interned_remote_procedure_item_passing_info_1_1(temp);
	}
	temp = 
		g2int_set_interned_list__remote_procedure_item_passing_info(interned_list,
		temp);
    }
    return VALUES_1(temp);
}

/* LIST-OF-NIL-P */
Object g2int_list_of_nil_p(list_1)
    Object list_1;
{
    Object e, ab_loop_list_, temp;

    x_note_fn_call(48,87);
    e = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    e = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (e) {
	temp = Nil;
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = T;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_define_resumable_remote_procedure_identifier;  /* send-icp-define-resumable-remote-procedure-identifier */

/* SEND-ICP-DEFINE-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_send_icp_define_resumable_remote_procedure_identifier(corresponding_icp_object_index,
	    remote_procedure_identifier_tag,remote_procedure_item_passing_info)
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object remote_procedure_item_passing_info;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,88);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_define_resumable_remote_procedure_identifier;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_item_passing_info,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_interned_list(remote_procedure_item_passing_info);
	  remote_procedure_item_passing_info = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)352L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_unsigned_integer(remote_procedure_identifier_tag);
	  g2int_write_icp_corresponding_object_index(remote_procedure_item_passing_info);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_send_icp_define_resumable_remote_procedure_identifier,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_define_resumable_remote_procedure_identifier,
			top,Nil);
		goto end_send_icp_define_resumable_remote_procedure_identifier;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	remote_procedure_identifier_tag = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_identifier_tag;
	remote_procedure_item_passing_info = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_item_passing_info;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_define_resumable_remote_procedure_identifier;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_item_passing_info,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      remote_procedure_item_passing_info = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_interned_list(remote_procedure_item_passing_info);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_item_passing_info = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)352L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    case 3:
		      goto l3_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(remote_procedure_identifier_tag))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(remote_procedure_item_passing_info))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(remote_procedure_item_passing_info);
	      g2int_resumable_icp_push(remote_procedure_identifier_tag);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_define_resumable_remote_procedure_identifier);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_resumable_remote_procedure_identifier;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_resumable_remote_procedure_identifier:
    return result;
}

/* HANDLE-ICP-DEFINE-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER--BODY */
Object g2int_handle_icp_define_resumable_remote_procedure_identifier__body(corresponding_icp_object_index,
	    remote_procedure_identifier_tag,remote_procedure_item_passing_info)
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object remote_procedure_item_passing_info;
{
    x_note_fn_call(48,89);
    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
	    g2int_make_incoming_remote_procedure_identifier(remote_procedure_identifier_tag,
	    g2int_get_remote_procedure_item_passing_info_for_interned_list(remote_procedure_item_passing_info)));
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_define_resumable_remote_procedure_identifier;  /* handle-icp-define-resumable-remote-procedure-identifier */

/* HANDLE-ICP-DEFINE-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_handle_icp_define_resumable_remote_procedure_identifier()
{
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object index_1, index_space, remote_procedure_item_passing_info;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(48,90);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	remote_procedure_identifier_tag = g2int_read_icp_unsigned_integer();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    remote_procedure_item_passing_info = 
		    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    remote_procedure_item_passing_info = Nil;
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_resumable_remote_procedure_identifier__body(corresponding_icp_object_index,
		  remote_procedure_identifier_tag,
		  remote_procedure_item_passing_info);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_handle_icp_define_resumable_remote_procedure_identifier,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_define_resumable_remote_procedure_identifier,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_resumable_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_identifier_tag = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_resumable_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    remote_procedure_identifier_tag = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_item_passing_info = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(remote_procedure_identifier_tag);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_define_resumable_remote_procedure_identifier);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		remote_procedure_item_passing_info = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		remote_procedure_item_passing_info = Nil;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_resumable_remote_procedure_identifier__body(corresponding_icp_object_index,
		  remote_procedure_identifier_tag,
		  remote_procedure_item_passing_info);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_standard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qg2int_establish_new_object_index_for_resumable_remote_procedure_identifier;  /* establish-new-object-index-for-resumable-remote-procedure-identifier */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_establish_new_object_index_for_resumable_remote_procedure_identifier varargs_1(int, n)
{
    Object resumable_remote_procedure_identifier, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(48,91);
    INIT_ARGS_nonrelocating();
    resumable_remote_procedure_identifier = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (G2int_disable_resumability) {
	result = g2int_assign_corresponding_icp_object_index(resumable_remote_procedure_identifier,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(resumable_remote_procedure_identifier,(SI_Long)2L)));
	SVREF(resumable_remote_procedure_identifier,FIX((SI_Long)2L)) = 
		svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_establish_new_object_index_for_resumable_remote_procedure_identifier,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_establish_new_object_index_for_resumable_remote_procedure_identifier,
			top,Nil);
	}
	resumable_remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		resumable_remote_procedure_identifier;
	icp_port = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : send_enlarge_message_p;
	result = g2int_assign_corresponding_icp_object_index(resumable_remote_procedure_identifier,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(resumable_remote_procedure_identifier,(SI_Long)2L)));
	SVREF(resumable_remote_procedure_identifier,FIX((SI_Long)2L)) = 
		svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qg2int_make_corresponding_icp_resumable_remote_procedure_identifier;  /* make-corresponding-icp-resumable-remote-procedure-identifier */

/* MAKE-CORRESPONDING-ICP-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_make_corresponding_icp_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier)
    Object resumable_remote_procedure_identifier;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, temp, temp_1, interned_list, temp_2;
    Object list_1, varargs_p, list_of_interned_item_infos, info, ab_loop_list_;
    Object incl_attr, excl_attr, incl_sys_attr, incl_all_sys_attr;
    Object incl_all_sys_attr_except, kind, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, old_list_of_interned_item_infos;
    Object old_list, item_passing_info, item_info, included_attributes_spec;
    Object excluded_attributes_spec, included_system_attributes_spec;
    Object ab_loopvar__3, include_all_system_attributes_spec, ab_loopvar__4;
    Object include_all_system_attributes_except_spec, ab_loopvar__5, kind_spec;
    Object ab_loopvar__6, gensymed_symbol, gensymed_symbol_1;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    char car_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,92);
    if (G2int_disable_resumability) {
	g2int_write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = g2int_assign_corresponding_icp_object_index(resumable_remote_procedure_identifier,
		  Qg2int_standard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  temp = g2int_gensym_cons_1(G2int_current_icp_port,
		  g2int_gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(resumable_remote_procedure_identifier,(SI_Long)2L)));
	  SVREF(resumable_remote_procedure_identifier,FIX((SI_Long)2L)) = temp;
	  if (T);
	  else {
	      temp_1 = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp_1;
	  }
	  if ( !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      temp_1 = ISVREF(resumable_remote_procedure_identifier,
		      (SI_Long)1L);
	      if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		      (SI_Long)9L) {
		  interned_list = 
			  ISVREF(ISVREF(resumable_remote_procedure_identifier,
			  (SI_Long)8L),(SI_Long)1L);
		  if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
			  >= (SI_Long)25L)
		      temp_2 = interned_list;
		  else {
		      list_1 = ISVREF(interned_list,(SI_Long)1L);
		      varargs_p = CAR(list_1);
		      list_of_interned_item_infos = CDR(list_1);
		      info = Nil;
		      ab_loop_list_ = list_of_interned_item_infos;
		      incl_attr = Nil;
		      excl_attr = Nil;
		      incl_sys_attr = Nil;
		      incl_all_sys_attr = Nil;
		      incl_all_sys_attr_except = Nil;
		      kind = Nil;
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		      ab_loop_desetq_ = Nil;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      info = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      ab_loop_desetq_ = ISVREF(info,(SI_Long)1L);
		      incl_attr = CAR(ab_loop_desetq_);
		      temp_2 = CDR(ab_loop_desetq_);
		      excl_attr = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      incl_sys_attr = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      incl_all_sys_attr = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      incl_all_sys_attr_except = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      kind = CAR(temp_2);
		      ab_loopvar__2 = 
			      g2int_gensym_cons_1(g2int_make_remote_procedure_item_info_old(incl_attr,
			      excl_attr,incl_sys_attr,incl_all_sys_attr,
			      kind),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop;
		    end_loop:
		      old_list_of_interned_item_infos = ab_loopvar_;
		      goto end;
		      old_list_of_interned_item_infos = Qnil;
		    end:;
		      old_list = g2int_gensym_cons_1(varargs_p,
			      old_list_of_interned_item_infos);
		      temp_2 = g2int_intern_list(old_list);
		      g2int_reclaim_gensym_list_1(old_list);
		  }
	      }
	      else {
		  item_passing_info = 
			  ISVREF(resumable_remote_procedure_identifier,
			  (SI_Long)8L);
		  temp_2 = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  varargs_p = CAR(temp_2);
		  item_info = Nil;
		  temp_2 = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  ab_loop_list_ = CDR(temp_2);
		  included_attributes_spec = Nil;
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  excluded_attributes_spec = Nil;
		  ab_loopvar__2 = Nil;
		  ab_loopvar__1 = Nil;
		  included_system_attributes_spec = Nil;
		  ab_loopvar__3 = Nil;
		  ab_loopvar__1 = Nil;
		  include_all_system_attributes_spec = Nil;
		  ab_loopvar__4 = Nil;
		  ab_loopvar__1 = Nil;
		  include_all_system_attributes_except_spec = Nil;
		  ab_loopvar__5 = Nil;
		  ab_loopvar__1 = Nil;
		  kind_spec = Nil;
		  ab_loopvar__6 = Nil;
		  ab_loopvar__1 = Nil;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  item_info = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_attributes(item_info),
			  Nil);
		  if (ab_loopvar_)
		      M_CDR(ab_loopvar_) = ab_loopvar__1;
		  else
		      included_attributes_spec = ab_loopvar__1;
		  ab_loopvar_ = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_excluded_attributes(item_info),
			  Nil);
		  if (ab_loopvar__2)
		      M_CDR(ab_loopvar__2) = ab_loopvar__1;
		  else
		      excluded_attributes_spec = ab_loopvar__1;
		  ab_loopvar__2 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_system_attributes(item_info),
			  Nil);
		  if (ab_loopvar__3)
		      M_CDR(ab_loopvar__3) = ab_loopvar__1;
		  else
		      included_system_attributes_spec = ab_loopvar__1;
		  ab_loopvar__3 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes(item_info),
			  Nil);
		  if (ab_loopvar__4)
		      M_CDR(ab_loopvar__4) = ab_loopvar__1;
		  else
		      include_all_system_attributes_spec = ab_loopvar__1;
		  ab_loopvar__4 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes_except(item_info),
			  Nil);
		  if (ab_loopvar__5)
		      M_CDR(ab_loopvar__5) = ab_loopvar__1;
		  else
		      include_all_system_attributes_except_spec = 
			      ab_loopvar__1;
		  ab_loopvar__5 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_kind(item_info),
			  Nil);
		  if (ab_loopvar__6)
		      M_CDR(ab_loopvar__6) = ab_loopvar__1;
		  else
		      kind_spec = ab_loopvar__1;
		  ab_loopvar__6 = ab_loopvar__1;
		  goto next_loop_1;
		end_loop_1:
		  if (g2int_list_of_nil_p(included_attributes_spec) && 
			  g2int_list_of_nil_p(excluded_attributes_spec) && 
			  g2int_list_of_nil_p(included_system_attributes_spec) 
			  && 
			  g2int_list_of_nil_p(include_all_system_attributes_spec) 
			  && g2int_list_of_nil_p(kind_spec) &&  
			  !TRUEP(varargs_p))
		      list_1 = 
			      g2int_gensym_cons_1(length(included_attributes_spec),
			      Nil);
		  else {
		      gensymed_symbol = 
			      g2int_make_gensym_list_1(FIX((SI_Long)6L));
		      gensymed_symbol_1 = gensymed_symbol;
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(included_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(excluded_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(included_system_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(include_all_system_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = g2int_copy_list_using_gensym_conses_1(kind_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      car_new_value =  ! !TRUEP(varargs_p);
		      M_CAR(gensymed_symbol_1) = car_new_value ? T : Nil;
		      list_1 = gensymed_symbol;
		  }
		  temp_2 = g2int_intern_list(list_1);
		  g2int_reclaim_gensym_list_1(list_1);
		  g2int_reclaim_gensym_list_1(included_attributes_spec);
		  g2int_reclaim_gensym_list_1(excluded_attributes_spec);
		  g2int_reclaim_gensym_list_1(included_system_attributes_spec);
		  g2int_reclaim_gensym_list_1(include_all_system_attributes_spec);
		  g2int_reclaim_gensym_list_1(include_all_system_attributes_except_spec);
		  g2int_reclaim_gensym_list_1(kind_spec);
		  goto end_1;
		  temp_2 = Qnil;
		end_1:;
	      }
	      g2int_send_icp_define_resumable_remote_procedure_identifier(corresponding_icp_object_index,
		      temp_1,temp_2);
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_make_corresponding_icp_resumable_remote_procedure_identifier,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_make_corresponding_icp_resumable_remote_procedure_identifier,
			top,Nil);
	}
	resumable_remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		resumable_remote_procedure_identifier;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp_1 = g2int_resumable_icp_pop();
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
	if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = g2int_resumable_icp_pop();
	  else {
	      result = g2int_assign_corresponding_icp_object_index(resumable_remote_procedure_identifier,
		      Qg2int_standard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      temp = g2int_gensym_cons_1(G2int_current_icp_port,
		      g2int_gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(resumable_remote_procedure_identifier,
		      (SI_Long)2L)));
	      SVREF(resumable_remote_procedure_identifier,
		      FIX((SI_Long)2L)) = temp;
	      if (T);
	      else {
		  temp_1 = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp_1;
	      }
	  }
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  ||  !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      temp_1 = ISVREF(resumable_remote_procedure_identifier,
		      (SI_Long)1L);
	      if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		      (SI_Long)9L) {
		  interned_list = 
			  ISVREF(ISVREF(resumable_remote_procedure_identifier,
			  (SI_Long)8L),(SI_Long)1L);
		  if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
			  >= (SI_Long)25L)
		      temp_2 = interned_list;
		  else {
		      list_1 = ISVREF(interned_list,(SI_Long)1L);
		      varargs_p = CAR(list_1);
		      list_of_interned_item_infos = CDR(list_1);
		      info = Nil;
		      ab_loop_list_ = list_of_interned_item_infos;
		      incl_attr = Nil;
		      excl_attr = Nil;
		      incl_sys_attr = Nil;
		      incl_all_sys_attr = Nil;
		      incl_all_sys_attr_except = Nil;
		      kind = Nil;
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		      ab_loop_desetq_ = Nil;
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_2;
		      info = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      ab_loop_desetq_ = ISVREF(info,(SI_Long)1L);
		      incl_attr = CAR(ab_loop_desetq_);
		      temp_2 = CDR(ab_loop_desetq_);
		      excl_attr = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      incl_sys_attr = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      incl_all_sys_attr = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      incl_all_sys_attr_except = CAR(temp_2);
		      temp_2 = CDR(ab_loop_desetq_);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      temp_2 = CDR(temp_2);
		      kind = CAR(temp_2);
		      ab_loopvar__2 = 
			      g2int_gensym_cons_1(g2int_make_remote_procedure_item_info_old(incl_attr,
			      excl_attr,incl_sys_attr,incl_all_sys_attr,
			      kind),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_2;
		    end_loop_2:
		      old_list_of_interned_item_infos = ab_loopvar_;
		      goto end_2;
		      old_list_of_interned_item_infos = Qnil;
		    end_2:;
		      old_list = g2int_gensym_cons_1(varargs_p,
			      old_list_of_interned_item_infos);
		      temp_2 = g2int_intern_list(old_list);
		      g2int_reclaim_gensym_list_1(old_list);
		  }
	      }
	      else {
		  item_passing_info = 
			  ISVREF(resumable_remote_procedure_identifier,
			  (SI_Long)8L);
		  temp_2 = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  varargs_p = CAR(temp_2);
		  item_info = Nil;
		  temp_2 = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  ab_loop_list_ = CDR(temp_2);
		  included_attributes_spec = Nil;
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  excluded_attributes_spec = Nil;
		  ab_loopvar__2 = Nil;
		  ab_loopvar__1 = Nil;
		  included_system_attributes_spec = Nil;
		  ab_loopvar__3 = Nil;
		  ab_loopvar__1 = Nil;
		  include_all_system_attributes_spec = Nil;
		  ab_loopvar__4 = Nil;
		  ab_loopvar__1 = Nil;
		  include_all_system_attributes_except_spec = Nil;
		  ab_loopvar__5 = Nil;
		  ab_loopvar__1 = Nil;
		  kind_spec = Nil;
		  ab_loopvar__6 = Nil;
		  ab_loopvar__1 = Nil;
		next_loop_3:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_3;
		  item_info = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_attributes(item_info),
			  Nil);
		  if (ab_loopvar_)
		      M_CDR(ab_loopvar_) = ab_loopvar__1;
		  else
		      included_attributes_spec = ab_loopvar__1;
		  ab_loopvar_ = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_excluded_attributes(item_info),
			  Nil);
		  if (ab_loopvar__2)
		      M_CDR(ab_loopvar__2) = ab_loopvar__1;
		  else
		      excluded_attributes_spec = ab_loopvar__1;
		  ab_loopvar__2 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_system_attributes(item_info),
			  Nil);
		  if (ab_loopvar__3)
		      M_CDR(ab_loopvar__3) = ab_loopvar__1;
		  else
		      included_system_attributes_spec = ab_loopvar__1;
		  ab_loopvar__3 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes(item_info),
			  Nil);
		  if (ab_loopvar__4)
		      M_CDR(ab_loopvar__4) = ab_loopvar__1;
		  else
		      include_all_system_attributes_spec = ab_loopvar__1;
		  ab_loopvar__4 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes_except(item_info),
			  Nil);
		  if (ab_loopvar__5)
		      M_CDR(ab_loopvar__5) = ab_loopvar__1;
		  else
		      include_all_system_attributes_except_spec = 
			      ab_loopvar__1;
		  ab_loopvar__5 = ab_loopvar__1;
		  ab_loopvar__1 = 
			  g2int_gensym_cons_1(g2int_remote_procedure_item_info_kind(item_info),
			  Nil);
		  if (ab_loopvar__6)
		      M_CDR(ab_loopvar__6) = ab_loopvar__1;
		  else
		      kind_spec = ab_loopvar__1;
		  ab_loopvar__6 = ab_loopvar__1;
		  goto next_loop_3;
		end_loop_3:
		  if (g2int_list_of_nil_p(included_attributes_spec) && 
			  g2int_list_of_nil_p(excluded_attributes_spec) && 
			  g2int_list_of_nil_p(included_system_attributes_spec) 
			  && 
			  g2int_list_of_nil_p(include_all_system_attributes_spec) 
			  && g2int_list_of_nil_p(kind_spec) &&  
			  !TRUEP(varargs_p))
		      list_1 = 
			      g2int_gensym_cons_1(length(included_attributes_spec),
			      Nil);
		  else {
		      gensymed_symbol = 
			      g2int_make_gensym_list_1(FIX((SI_Long)6L));
		      gensymed_symbol_1 = gensymed_symbol;
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(included_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(excluded_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(included_system_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = 
			      g2int_copy_list_using_gensym_conses_1(include_all_system_attributes_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      temp = g2int_copy_list_using_gensym_conses_1(kind_spec);
		      M_CAR(gensymed_symbol_1) = temp;
		      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		      car_new_value =  ! !TRUEP(varargs_p);
		      M_CAR(gensymed_symbol_1) = car_new_value ? T : Nil;
		      list_1 = gensymed_symbol;
		  }
		  temp_2 = g2int_intern_list(list_1);
		  g2int_reclaim_gensym_list_1(list_1);
		  g2int_reclaim_gensym_list_1(included_attributes_spec);
		  g2int_reclaim_gensym_list_1(excluded_attributes_spec);
		  g2int_reclaim_gensym_list_1(included_system_attributes_spec);
		  g2int_reclaim_gensym_list_1(include_all_system_attributes_spec);
		  g2int_reclaim_gensym_list_1(include_all_system_attributes_except_spec);
		  g2int_reclaim_gensym_list_1(kind_spec);
		  goto end_3;
		  temp_2 = Qnil;
		end_3:;
	      }
	      if (EQ(icp_suspend_1,
		      g2int_send_icp_define_resumable_remote_procedure_identifier(corresponding_icp_object_index,
		      temp_1,temp_2))) {
		  g2int_resumable_icp_push(corresponding_icp_object_index);
		  g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(resumable_remote_procedure_identifier);
	    g2int_resumable_icp_push(Qg2int_make_corresponding_icp_resumable_remote_procedure_identifier);
	    return VALUES_1(G2int_icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_get_icp_object_index_for_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier,
	    icp_port)
    Object resumable_remote_procedure_identifier, icp_port;
{
    x_note_fn_call(48,93);
    return g2int_getfq_function_no_default(ISVREF(resumable_remote_procedure_identifier,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_set_icp_object_index_for_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier,
	    corresponding_icp_object_index,icp_port)
    Object resumable_remote_procedure_identifier;
    Object corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(48,94);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_remote_procedure_identifier,(SI_Long)2L)));
    return VALUES_1(SVREF(resumable_remote_procedure_identifier,
	    FIX((SI_Long)2L)) = svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_reclaim_icp_object_map_for_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier)
    Object resumable_remote_procedure_identifier;
{
    Object icp_object_map;

    x_note_fn_call(48,95);
    icp_object_map = ISVREF(resumable_remote_procedure_identifier,(SI_Long)2L);
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(resumable_remote_procedure_identifier,
		icp_object_map,Qg2int_standard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_resumable_remote_procedure_identifier;  /* set-access-form-for-resumable-remote-procedure-identifier */

/* RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_reclaim_icp_port_entry_for_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier,
	    icp_port)
    Object resumable_remote_procedure_identifier, icp_port;
{
    x_note_fn_call(48,96);
    return g2int_reclaim_icp_port_entry(icp_port,
	    resumable_remote_procedure_identifier,
	    ISVREF(resumable_remote_procedure_identifier,(SI_Long)2L),
	    Qg2int_set_access_form_for_resumable_remote_procedure_identifier);
}

/* SET-ACCESS-FORM-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_set_access_form_for_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier,
	    new_value)
    Object resumable_remote_procedure_identifier, new_value;
{
    x_note_fn_call(48,97);
    return VALUES_1(SVREF(resumable_remote_procedure_identifier,
	    FIX((SI_Long)2L)) = new_value);
}

static Object Qg2int_send_icp_resumable_rpc_start;  /* send-icp-resumable-rpc-start */

/* SEND-ICP-RESUMABLE-RPC-START */
Object g2int_send_icp_resumable_rpc_start(remote_procedure_name,
	    rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,98);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resumable_rpc_start;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	  remote_procedure_name = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)247L));
	  g2int_write_icp_corresponding_object_index(remote_procedure_name);
	  g2int_write_icp_resumable_rpc_argument_list(rpc_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_resumable_rpc_start,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_resumable_rpc_start,top,Nil);
		goto end_send_icp_resumable_rpc_start;
	    }
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_name;
	rpc_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : rpc_argument_list;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resumable_rpc_start;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      remote_procedure_name = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)247L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(remote_procedure_name))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_resumable_rpc_argument_list(rpc_argument_list))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(rpc_argument_list);
	      g2int_resumable_icp_push(remote_procedure_name);
	      g2int_resumable_icp_push(Qg2int_send_icp_resumable_rpc_start);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_resumable_rpc_start;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_resumable_rpc_start:
    return result;
}

static Object Qg2int_start;        /* start */

static Object Qg2int_gsi;          /* gsi */

/* HANDLE-ICP-RESUMABLE-RPC-START--BODY */
Object g2int_handle_icp_resumable_rpc_start__body(remote_procedure_name,
	    rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    x_note_fn_call(48,99);
    g2int_gsi_start_or_call_local_function_or_handle_return_values(Qg2int_start,
	    remote_procedure_name,Nil,rpc_argument_list);
    if ( !TRUEP(G2int_current_resumable_icp_read_task)) {
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_resumable_rpc_start;  /* handle-icp-resumable-rpc-start */

/* HANDLE-ICP-RESUMABLE-RPC-START */
Object g2int_handle_icp_resumable_rpc_start()
{
    Object index_1, index_space, remote_procedure_name, rpc_argument_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(48,100);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    remote_procedure_name = Nil;
	rpc_argument_list = g2int_read_icp_resumable_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_start__body(remote_procedure_name,
		  rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_resumable_rpc_start,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_resumable_rpc_start,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_name = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_start);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		remote_procedure_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    rpc_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_resumable_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(remote_procedure_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_start);
		return VALUES_1(G2int_icp_suspend);
	    }
	    rpc_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_start__body(remote_procedure_name,
		  rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_resumable_rpc_call;  /* send-icp-resumable-rpc-call */

/* SEND-ICP-RESUMABLE-RPC-CALL */
Object g2int_send_icp_resumable_rpc_call(remote_procedure_name,
	    resumable_remote_procedure_identifier,rpc_argument_list)
    Object remote_procedure_name, resumable_remote_procedure_identifier;
    Object rpc_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,101);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resumable_rpc_call;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	  remote_procedure_name = temp_1;
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(resumable_remote_procedure_identifier,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier);
	  resumable_remote_procedure_identifier = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)248L));
	  g2int_write_icp_corresponding_object_index(remote_procedure_name);
	  g2int_write_icp_corresponding_object_index(resumable_remote_procedure_identifier);
	  g2int_write_icp_resumable_rpc_argument_list(rpc_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_resumable_rpc_call,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_resumable_rpc_call,top,Nil);
		goto end_send_icp_resumable_rpc_call;
	    }
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_name;
	resumable_remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		resumable_remote_procedure_identifier;
	rpc_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : rpc_argument_list;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resumable_rpc_call;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    case 4:
		      goto l4;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      remote_procedure_name = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name = value_1;
	  }
	l2:
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(resumable_remote_procedure_identifier,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      resumable_remote_procedure_identifier = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_resumable_remote_procedure_identifier(resumable_remote_procedure_identifier);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      resumable_remote_procedure_identifier = value_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)248L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l4:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    case 3:
		      goto l3_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(remote_procedure_name))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(resumable_remote_procedure_identifier))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_resumable_rpc_argument_list(rpc_argument_list))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(rpc_argument_list);
	      g2int_resumable_icp_push(resumable_remote_procedure_identifier);
	      g2int_resumable_icp_push(remote_procedure_name);
	      g2int_resumable_icp_push(Qg2int_send_icp_resumable_rpc_call);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_resumable_rpc_call;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_resumable_rpc_call:
    return result;
}

static Object Qg2int_call;         /* call */

/* HANDLE-ICP-RESUMABLE-RPC-CALL--BODY */
Object g2int_handle_icp_resumable_rpc_call__body(remote_procedure_name,
	    resumable_remote_procedure_identifier,rpc_argument_list)
    Object remote_procedure_name, resumable_remote_procedure_identifier;
    Object rpc_argument_list;
{
    x_note_fn_call(48,102);
    g2int_gsi_start_or_call_local_function_or_handle_return_values(Qg2int_call,
	    remote_procedure_name,resumable_remote_procedure_identifier,
	    rpc_argument_list);
    if ( !TRUEP(G2int_current_resumable_icp_read_task)) {
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_resumable_rpc_call;  /* handle-icp-resumable-rpc-call */

/* HANDLE-ICP-RESUMABLE-RPC-CALL */
Object g2int_handle_icp_resumable_rpc_call()
{
    Object index_1, index_space, remote_procedure_name;
    Object resumable_remote_procedure_identifier, rpc_argument_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(48,103);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    remote_procedure_name = Nil;
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    resumable_remote_procedure_identifier = 
		    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    resumable_remote_procedure_identifier = Nil;
	rpc_argument_list = g2int_read_icp_resumable_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_call__body(remote_procedure_name,
		  resumable_remote_procedure_identifier,rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_resumable_rpc_call,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_resumable_rpc_call,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_name = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_call);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		remote_procedure_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    resumable_remote_procedure_identifier = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(remote_procedure_name);
		    g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_call);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		resumable_remote_procedure_identifier = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		resumable_remote_procedure_identifier = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    rpc_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_resumable_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(resumable_remote_procedure_identifier);
		g2int_resumable_icp_push(remote_procedure_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_call);
		return VALUES_1(G2int_icp_suspend);
	    }
	    rpc_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_call__body(remote_procedure_name,
		  resumable_remote_procedure_identifier,rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_resumable_rpc_return_values;  /* send-icp-resumable-rpc-return-values */

/* SEND-ICP-RESUMABLE-RPC-RETURN-VALUES */
Object g2int_send_icp_resumable_rpc_return_values(calling_procedure_index,
	    return_values_list)
    Object calling_procedure_index, return_values_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,104);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_resumable_rpc_return_values;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)249L));
	  g2int_write_icp_unsigned_integer(calling_procedure_index);
	  g2int_write_icp_resumable_rpc_argument_list(return_values_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_resumable_rpc_return_values,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_resumable_rpc_return_values,top,Nil);
		goto end_send_icp_resumable_rpc_return_values;
	    }
	}
	calling_procedure_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : calling_procedure_index;
	return_values_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : return_values_list;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_resumable_rpc_return_values;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
		  g2int_start_writing_icp_message(FIX((SI_Long)249L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(calling_procedure_index))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_resumable_rpc_argument_list(return_values_list))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(return_values_list);
	      g2int_resumable_icp_push(calling_procedure_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_resumable_rpc_return_values);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_resumable_rpc_return_values;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_resumable_rpc_return_values:
    return result;
}

static Object Qg2int_rpc_return_values;  /* rpc-return-values */

static Object Qg2int_outstanding;  /* outstanding */

static Object Qg2int_returned;     /* returned */

/* HANDLE-ICP-RESUMABLE-RPC-RETURN-VALUES--BODY */
Object g2int_handle_icp_resumable_rpc_return_values__body(calling_procedure_index,
	    return_values_list)
    Object calling_procedure_index, return_values_list;
{
    Object remote_procedure_identifier;

    x_note_fn_call(48,105);
    remote_procedure_identifier = 
	    g2int_lookup_remote_procedure_identifier_from_index(calling_procedure_index);
    if (remote_procedure_identifier);
    else
	remote_procedure_identifier = g2int_gsi_connection_error(2,
		Qg2int_rpc_return_values,
		G2int_gsi_unknown_calling_procedure_index);
    if (remote_procedure_identifier && EQ(Qg2int_outstanding,
	    ISVREF(remote_procedure_identifier,(SI_Long)6L)))
	SVREF(remote_procedure_identifier,FIX((SI_Long)6L)) = Qg2int_returned;
    g2int_gsi_start_or_call_local_function_or_handle_return_values(Qreturn,
	    ISVREF(ISVREF(remote_procedure_identifier,(SI_Long)3L),
	    (SI_Long)2L),remote_procedure_identifier,return_values_list);
    if ( !TRUEP(G2int_current_resumable_icp_read_task)) {
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_resumable_rpc_return_values;  /* handle-icp-resumable-rpc-return-values */

/* HANDLE-ICP-RESUMABLE-RPC-RETURN-VALUES */
Object g2int_handle_icp_resumable_rpc_return_values()
{
    Object calling_procedure_index, return_values_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(48,106);
    if (G2int_disable_resumability) {
	calling_procedure_index = g2int_read_icp_unsigned_integer();
	return_values_list = g2int_read_icp_resumable_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_return_values__body(calling_procedure_index,
		  return_values_list);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_resumable_rpc_return_values,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_resumable_rpc_return_values,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    calling_procedure_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_return_values);
		return VALUES_1(G2int_icp_suspend);
	    }
	    calling_procedure_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    return_values_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_resumable_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(calling_procedure_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_return_values);
		return VALUES_1(G2int_icp_suspend);
	    }
	    return_values_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_return_values__body(calling_procedure_index,
		  return_values_list);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_resumable_rpc_error;  /* send-icp-resumable-rpc-error */

static Object Qg2int_corresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

/* SEND-ICP-RESUMABLE-RPC-ERROR */
Object g2int_send_icp_resumable_rpc_error(error_name,error_level,
	    error_description,error_argument_list)
    Object error_name, error_level, error_description, error_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,107);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resumable_rpc_error;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(error_name);
	  error_name = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)353L));
	  g2int_write_icp_corresponding_object_index(error_name);
	  g2int_write_icp_unsigned_integer(error_level);
	  g2int_write_icp_text_string(error_description);
	  g2int_write_icp_resumable_rpc_argument_list(error_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_resumable_rpc_error,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_resumable_rpc_error,top,Nil);
		goto end_send_icp_resumable_rpc_error;
	    }
	}
	error_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_name;
	error_level = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_level;
	error_description = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_description;
	error_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_argument_list;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resumable_rpc_error;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      error_name = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(error_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      error_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)353L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    case 3:
		      goto l3_1;
		      break;
		    case 4:
		      goto l4;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(error_name))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_unsigned_integer(error_level))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_text_string(error_description))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_resumable_rpc_argument_list(error_argument_list))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(error_argument_list);
	      g2int_resumable_icp_push(error_description);
	      g2int_resumable_icp_push(error_level);
	      g2int_resumable_icp_push(error_name);
	      g2int_resumable_icp_push(Qg2int_send_icp_resumable_rpc_error);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_resumable_rpc_error;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_resumable_rpc_error:
    return result;
}

static Object Qg2int_rpc_error_handler_1;  /* rpc_error_handler_1 */

/* HANDLE-ICP-RESUMABLE-RPC-ERROR--BODY */
Object g2int_handle_icp_resumable_rpc_error__body(error_name,error_level,
	    error_description,error_argument_list)
    Object error_name, error_level, error_description, error_argument_list;
{
    x_note_fn_call(48,108);
    g2int_gsi_warning(4,Qg2int_rpc_error_handler_1,
	    G2int_gsi_rpc_error_from_g2,error_level,error_description);
    if ( !TRUEP(G2int_current_resumable_icp_read_task)) {
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_resumable_rpc_error;  /* handle-icp-resumable-rpc-error */

/* HANDLE-ICP-RESUMABLE-RPC-ERROR */
Object g2int_handle_icp_resumable_rpc_error()
{
    Object index_1, index_space, error_name, error_level, error_description;
    Object error_argument_list, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(48,109);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    error_name = Nil;
	error_level = g2int_read_icp_unsigned_integer();
	error_description = g2int_read_icp_text_string();
	error_argument_list = g2int_read_icp_resumable_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_error__body(error_name,
		  error_level,error_description,error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_resumable_rpc_error,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_resumable_rpc_error,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_name = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		error_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_level = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_level = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_description = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_description = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_resumable_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_description);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_error__body(error_name,
		  error_level,error_description,error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object string_constant_11;  /* "The error-object did not have a null type tag" */

static Object Qg2int_error_description;  /* error-description */

static Object string_constant_12;  /* "The error-object did not have a error-description attribute" */

static Object string_constant_13;  /* "The error-description attribute of the error-object was not a string" */

static Object Qg2int_g2_error;     /* g2-error */

static Object Qg2int_g2_rpc_error;  /* g2-rpc-error */

/* CHECK-GSI-ERROR-OBJECT */
Object g2int_check_gsi_error_object(error_object)
    Object error_object;
{
    Object temp, gsi_instance_extension, error_class, descr;

    x_note_fn_call(48,110);
    if (IFIX(G2int_gsi_null_type_tag) != IFIX(ISVREF(error_object,
	    (SI_Long)1L)) >>  -  - (SI_Long)3L)
	temp = string_constant_11;
    else {
	gsi_instance_extension = ISVREF(error_object,(SI_Long)3L);
	error_class = gsi_instance_extension ? 
		ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
	if ( !TRUEP(error_class))
	    temp = Nil;
	else {
	    descr = g2int_gsi_get_item_of_attribute_named(error_object,
		    Qg2int_error_description);
	    if ( !TRUEP(descr))
		temp = string_constant_12;
	    else if (IFIX(G2int_gsi_string_type_tag) != IFIX(ISVREF(descr,
		    (SI_Long)1L)) >>  -  - (SI_Long)3L)
		temp = string_constant_13;
	    else
		temp = Qnil;
	    if (temp);
	    else if (EQ(error_class,Qerror) || EQ(error_class,
		    Qg2int_default_error) || EQ(error_class,
		    Qg2int_g2_error) || EQ(error_class,Qg2int_g2_rpc_error))
		temp = Nil;
	    else
		temp = Nil;
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_14;  /* "The first result, error-name, is not a symbol" */

static Object string_constant_15;  /* "The second result, error-message, is not a string" */

static Object string_constant_16;  /* "The number of results is not equal to 1 or 2" */

/* CHECK-GSI-ERROR-ARGUMENT-LIST */
Object g2int_check_gsi_error_argument_list(argument_array)
    Object argument_array;
{
    Object temp;

    x_note_fn_call(48,111);
    if ((SI_Long)2L == 
	    IFIX(FIXNUM_SUB1(g2int_gsi_managed_array_length(argument_array)))) 
		{
	if (IFIX(G2int_gsi_symbol_type_tag) != 
		IFIX(ISVREF(ISVREF(argument_array,(SI_Long)1L),
		(SI_Long)1L)) >>  -  - (SI_Long)3L)
	    temp = string_constant_14;
	else if (IFIX(G2int_gsi_string_type_tag) != 
		IFIX(ISVREF(ISVREF(argument_array,(SI_Long)2L),
		(SI_Long)1L)) >>  -  - (SI_Long)3L)
	    temp = string_constant_15;
	else
	    temp = Nil;
    }
    else if ((SI_Long)1L == 
	    IFIX(FIXNUM_SUB1(g2int_gsi_managed_array_length(argument_array))))
	temp = g2int_check_gsi_error_object(ISVREF(argument_array,
		(SI_Long)1L));
    else
	temp = string_constant_16;
    return VALUES_1(temp);
}

/* MAKE-GSI-ERROR-ARGUMENT-LIST */
Object g2int_make_gsi_error_argument_list(error_name,error_description,
	    error_object)
    Object error_name, error_description, error_object;
{
    Object new_error_argument_list, temp, svref_new_value;

    x_note_fn_call(48,112);
    if (error_object) {
	new_error_argument_list = 
		g2int_make_gsi_rpc_argument_list(FIX((SI_Long)1L));
	SVREF(new_error_argument_list,FIX((SI_Long)1L)) = error_object;
	temp = new_error_argument_list;
    }
    else {
	new_error_argument_list = 
		g2int_make_gsi_rpc_argument_list(FIX((SI_Long)2L));
	svref_new_value = g2int_make_gsi_instance(2,
		G2int_gsi_symbol_type_tag,error_name);
	SVREF(new_error_argument_list,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = g2int_make_gsi_instance(2,
		G2int_gsi_string_type_tag,
		g2int_convert_value_to_gsi_value(g2int_copy_text_string(error_description)));
	SVREF(new_error_argument_list,FIX((SI_Long)2L)) = svref_new_value;
	temp = new_error_argument_list;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_resumable_rpc_error_to_caller;  /* send-icp-resumable-rpc-error-to-caller */

/* SEND-ICP-RESUMABLE-RPC-ERROR-TO-CALLER */
Object g2int_send_icp_resumable_rpc_error_to_caller(remote_caller_index,
	    signaller_qm,error_name,error_level,error_description,
	    error_argument_list)
    Object remote_caller_index, signaller_qm, error_name, error_level;
    Object error_description, error_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(48,113);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_resumable_rpc_error_to_caller;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(error_name);
	  error_name = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)354L));
	  g2int_write_icp_unsigned_integer(remote_caller_index);
	  g2int_write_icp_unsigned_integer_or_nil(signaller_qm);
	  g2int_write_icp_corresponding_object_index(error_name);
	  g2int_write_icp_unsigned_integer(error_level);
	  g2int_write_icp_text_string(error_description);
	  g2int_write_icp_resumable_rpc_argument_list(error_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_resumable_rpc_error_to_caller,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_resumable_rpc_error_to_caller,top,Nil);
		goto end_send_icp_resumable_rpc_error_to_caller;
	    }
	}
	remote_caller_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_caller_index;
	signaller_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : signaller_qm;
	error_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_name;
	error_level = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_level;
	error_description = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_description;
	error_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_argument_list;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_resumable_rpc_error_to_caller;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      error_name = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(error_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      error_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)354L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    case 3:
		      goto l3_1;
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(remote_caller_index))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer_or_nil(signaller_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(error_name))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_unsigned_integer(error_level))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_text_string(error_description))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_resumable_rpc_argument_list(error_argument_list))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(error_argument_list);
	      g2int_resumable_icp_push(error_description);
	      g2int_resumable_icp_push(error_level);
	      g2int_resumable_icp_push(error_name);
	      g2int_resumable_icp_push(signaller_qm);
	      g2int_resumable_icp_push(remote_caller_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_resumable_rpc_error_to_caller);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_resumable_rpc_error_to_caller;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_resumable_rpc_error_to_caller:
    return result;
}

static Object Qg2int_sync_abort;   /* sync-abort */

static Object Qg2int_error_return;  /* error-return */

/* HANDLE-ICP-RESUMABLE-RPC-ERROR-TO-CALLER--BODY */
Object g2int_handle_icp_resumable_rpc_error_to_caller__body(remote_caller_index,
	    signaller_qm,error_name,error_level,error_description,
	    error_argument_list)
    Object remote_caller_index, signaller_qm, error_name, error_level;
    Object error_description, error_argument_list;
{
    Object remote_procedure_identifier;

    x_note_fn_call(48,114);
    remote_procedure_identifier = (SI_Long)0L < IFIX(remote_caller_index) ?
	     
	    g2int_lookup_remote_procedure_identifier_from_index(remote_caller_index) 
	    : Nil;
    if (remote_procedure_identifier && EQ(Qg2int_outstanding,
	    ISVREF(remote_procedure_identifier,(SI_Long)6L)))
	SVREF(remote_procedure_identifier,FIX((SI_Long)6L)) = 
		Qg2int_sync_abort;
    if ( !TRUEP(g2int_check_gsi_error_argument_list(error_argument_list)))
	error_argument_list = 
		g2int_make_gsi_error_argument_list(error_name,
		error_description,Nil);
    g2int_gsi_start_or_call_local_function_or_handle_return_values(Qg2int_error_return,
	    ISVREF(ISVREF(remote_procedure_identifier,(SI_Long)3L),
	    (SI_Long)2L),remote_procedure_identifier,error_argument_list);
    if ( !TRUEP(G2int_current_resumable_icp_read_task)) {
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_resumable_rpc_error_to_caller;  /* handle-icp-resumable-rpc-error-to-caller */

/* HANDLE-ICP-RESUMABLE-RPC-ERROR-TO-CALLER */
Object g2int_handle_icp_resumable_rpc_error_to_caller()
{
    Object remote_caller_index, signaller_qm, index_1, index_space, error_name;
    Object error_level, error_description, error_argument_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(48,115);
    if (G2int_disable_resumability) {
	remote_caller_index = g2int_read_icp_unsigned_integer();
	signaller_qm = g2int_read_icp_unsigned_integer_or_nil();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    error_name = Nil;
	error_level = g2int_read_icp_unsigned_integer();
	error_description = g2int_read_icp_text_string();
	error_argument_list = g2int_read_icp_resumable_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_error_to_caller__body(remote_caller_index,
		  signaller_qm,error_name,error_level,error_description,
		  error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_resumable_rpc_error_to_caller,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_resumable_rpc_error_to_caller,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_caller_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    remote_caller_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    signaller_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer_or_nil();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    signaller_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_name = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(signaller_qm);
		    g2int_resumable_icp_push(remote_caller_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error_to_caller);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		error_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_level = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(signaller_qm);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_level = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_description = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(signaller_qm);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_description = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_resumable_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_description);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(signaller_qm);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_resumable_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resumable_rpc_error_to_caller__body(remote_caller_index,
		  signaller_qm,error_name,error_level,error_description,
		  error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* SEND-RPC-START */
Object g2int_send_rpc_start(output_port,execution_priority,
	    remote_procedure_name_structure,argument_list,
	    do_not_reclaim_arguments)
    Object output_port, execution_priority, remote_procedure_name_structure;
    Object argument_list, do_not_reclaim_arguments;
{
    x_note_fn_call(48,116);
    return VALUES_1(Nil);
}

/* SEND-RPC-CALL */
Object g2int_send_rpc_call(output_port,execution_priority,
	    remote_procedure_name_structure,remote_procedure_identifier,
	    argument_list)
    Object output_port, execution_priority, remote_procedure_name_structure;
    Object remote_procedure_identifier, argument_list;
{
    Object svref_new_value;

    x_note_fn_call(48,117);
    svref_new_value = ISVREF(remote_procedure_name_structure,(SI_Long)1L);
    SVREF(remote_procedure_identifier,FIX((SI_Long)10L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* SEND-RPC-RETURN-VALUES */
Object g2int_send_rpc_return_values(output_port,execution_priority,
	    remote_procedure_identifier_tag,return_results_list)
    Object output_port, execution_priority, remote_procedure_identifier_tag;
    Object return_results_list;
{
    x_note_fn_call(48,118);
    return VALUES_1(Nil);
}

void rpc_common3_INIT()
{
    Object AB_package;
    Object Qg2int_reclaim_icp_port_entry_for_resumable_remote_procedure_identifier;
    Object Qg2int_reclaim_remote_procedure_identifier_for_connection_loss;
    Object Qg2int_reclaim_incoming_remote_procedure_identifier;
    Object Qg2int_resumable_remote_procedure_identifier, list_constant_18;
    Object Qg2int_icp_object_map_for_remote_procedure_identifier;
    Object array_constant_3, list_constant_11, Qg2int_rpc_common3;
    Object Qg2int_remote_gsi_interface_list;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_17;
    Object Qg2int_history_collection_time, Qg2int_history_value;
    Object list_constant_16, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_12, Qg2int_attribute_display_items;
    Object Qg2int_name_box_item, Qg2int_position_in_workspace;
    Object Qg2int_following_item_in_workspace_layering, Qg2int_value_structure;
    Object Qg2int_history;
    Object Qg2int_decache_attribute_description_lists_of_interned_lists;
    Object Qg2int_decache_attribute_description_lists_of_interned_lists_function;

    x_note_fn_call(48,119);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_class_rpc_item_info_to_slot_names_interned_list = 
	    STATIC_SYMBOL("CLASS-RPC-ITEM-INFO-TO-SLOT-NAMES-INTERNED-LIST",
	    AB_package);
    G2int_class_rpc_item_info_to_slot_names_interned_list_prop = 
	    Qg2int_class_rpc_item_info_to_slot_names_interned_list;
    Qg2int_attribute_description_list = 
	    STATIC_SYMBOL("ATTRIBUTE-DESCRIPTION-LIST",AB_package);
    Qg2int_interned_list_table = STATIC_SYMBOL("INTERNED-LIST-TABLE",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_interned_list_g2_struct = 
	    STATIC_SYMBOL("INTERNED-LIST-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_none = STATIC_SYMBOL("NONE",AB_package);
    Qg2int_decache_attribute_description_lists_of_interned_lists_function 
	    = 
	    STATIC_SYMBOL("DECACHE-ATTRIBUTE-DESCRIPTION-LISTS-OF-INTERNED-LISTS-FUNCTION",
	    AB_package);
    Qg2int_decache_attribute_description_lists_of_interned_lists = 
	    STATIC_SYMBOL("DECACHE-ATTRIBUTE-DESCRIPTION-LISTS-OF-INTERNED-LISTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_decache_attribute_description_lists_of_interned_lists,
	    STATIC_FUNCTION(g2int_decache_attribute_description_lists_of_interned_lists,
	    NIL,FALSE,1,1));
    set(Qg2int_decache_attribute_description_lists_of_interned_lists_function,
	    SYMBOL_FUNCTION(Qg2int_decache_attribute_description_lists_of_interned_lists));
    Qg2int_resumable_error = STATIC_SYMBOL("RESUMABLE-ERROR",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    Qg2int_class = STATIC_SYMBOL("CLASS",AB_package);
    Qg2int_history = STATIC_SYMBOL("HISTORY",AB_package);
    Qg2int_value_structure = STATIC_SYMBOL("VALUE-STRUCTURE",AB_package);
    Qg2int_attribute_display_items = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAY-ITEMS",AB_package);
    Qg2int_following_item_in_workspace_layering = 
	    STATIC_SYMBOL("FOLLOWING-ITEM-IN-WORKSPACE-LAYERING",AB_package);
    Qg2int_position_in_workspace = STATIC_SYMBOL("POSITION-IN-WORKSPACE",
	    AB_package);
    Qg2int_name_box_item = STATIC_SYMBOL("NAME-BOX-ITEM",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)8L,Qg2int_class,Qg2int_history,
	    Qg2int_value_structure,Qg2int_attribute_display_items,
	    Qg2int_following_item_in_workspace_layering,
	    Qg2int_position_in_workspace,Qg2int_name_box_item,
	    Qg2int_attribute_display_items);
    G2int_attributes_to_exclude_from_item_passing = list_constant_12;
    Qg2int_names = STATIC_SYMBOL("NAMES",AB_package);
    Qg2int_value_structure_using_unix_time = 
	    STATIC_SYMBOL("VALUE-STRUCTURE-USING-UNIX-TIME",AB_package);
    Qg2int_gsi_append_flag = STATIC_SYMBOL("GSI-APPEND-FLAG",AB_package);
    Qg2int_g2_array_sequence_append = 
	    STATIC_SYMBOL("G2-ARRAY-SEQUENCE-APPEND",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)23L),
	    FIX((SI_Long)25L));
    Qg2int_gsi_update_items_in_lists_and_arrays_flag = 
	    STATIC_SYMBOL("GSI-UPDATE-ITEMS-IN-LISTS-AND-ARRAYS-FLAG",
	    AB_package);
    Qg2int_gsi_delete_flag = STATIC_SYMBOL("GSI-DELETE-FLAG",AB_package);
    Qg2int_g2_array_sequence_immediate_with_delete = 
	    STATIC_SYMBOL("G2-ARRAY-SEQUENCE-IMMEDIATE-WITH-DELETE",
	    AB_package);
    Qg2int_g2_array_sequence_immediate = 
	    STATIC_SYMBOL("G2-ARRAY-SEQUENCE-IMMEDIATE",AB_package);
    Qg2int_g2_array_sequence_with_delete = 
	    STATIC_SYMBOL("G2-ARRAY-SEQUENCE-WITH-DELETE",AB_package);
    Qg2int_g2_array_sequence = STATIC_SYMBOL("G2-ARRAY-SEQUENCE",AB_package);
    Qg2int_element_type = STATIC_SYMBOL("ELEMENT-TYPE",AB_package);
    Qg2int_g2_list_sequence_append = 
	    STATIC_SYMBOL("G2-LIST-SEQUENCE-APPEND",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)39L),
	    FIX((SI_Long)41L));
    Qg2int_g2_list_sequence_immediate_with_delete = 
	    STATIC_SYMBOL("G2-LIST-SEQUENCE-IMMEDIATE-WITH-DELETE",AB_package);
    Qg2int_g2_list_sequence_immediate = 
	    STATIC_SYMBOL("G2-LIST-SEQUENCE-IMMEDIATE",AB_package);
    Qg2int_g2_list_sequence_with_delete = 
	    STATIC_SYMBOL("G2-LIST-SEQUENCE-WITH-DELETE",AB_package);
    Qg2int_g2_list_sequence = STATIC_SYMBOL("G2-LIST-SEQUENCE",AB_package);
    Qg2int_history_keeping_spec = STATIC_SYMBOL("HISTORY-KEEPING-SPEC",
	    AB_package);
    Qg2int_history_using_unix_time = 
	    STATIC_SYMBOL("HISTORY-USING-UNIX-TIME",AB_package);
    Qg2int_class_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",
	    AB_package);
    Qg2int_value = STATIC_SYMBOL("VALUE",AB_package);
    Qg2int_effective_data_type = STATIC_SYMBOL("EFFECTIVE-DATA-TYPE",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)10L,Qg2int_class,Qg2int_names,
	    Qg2int_value,Qg2int_element_type,Qg2int_g2_array_sequence,
	    Qg2int_g2_list_sequence,Qg2int_effective_data_type,
	    Qg2int_history_keeping_spec,Qg2int_history_using_unix_time,
	    Qg2int_value_structure_using_unix_time);
    Qg2int_text = STATIC_SYMBOL("TEXT",AB_package);
    Qg2int_truth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qg2int_item_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qg2int_quantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qg2int_item = STATIC_SYMBOL("ITEM",AB_package);
    if (G2int_item_copy_root_item == UNBOUND)
	G2int_item_copy_root_item = Nil;
    if (G2int_item_copy_handle_for_root_item == UNBOUND)
	G2int_item_copy_handle_for_root_item = Nil;
    if (G2int_item_copy_rpc_item_info == UNBOUND)
	G2int_item_copy_rpc_item_info = Nil;
    Qg2int_item_copy_index_space = STATIC_SYMBOL("ITEM-COPY-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_item_copy_index_space,
	    G2int_item_copy_index_space);
    if (G2int_current_attribute_description_index == UNBOUND)
	G2int_current_attribute_description_index = Nil;
    if (G2int_current_slot_value_of_user_slot == UNBOUND)
	G2int_current_slot_value_of_user_slot = Nil;
    Qg2int_truth = STATIC_SYMBOL("TRUTH",AB_package);
    Qg2int_float = STATIC_SYMBOL("float",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qg2int_text,
	    Qg2int_truth_value,Qsymbol);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)4L,Qfloat,Qinteger,
	    Qg2int_quantity,list_constant_7);
    Qg2int_maybe = STATIC_SYMBOL("MAYBE",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qfloat,Qinteger);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qg2int_item_or_value,
	    Qg2int_value);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qg2int_item_or_value,
	    Qg2int_value,Qg2int_quantity);
    Qg2int_write_icp_item_new_copy = 
	    STATIC_SYMBOL("WRITE-ICP-ITEM-NEW-COPY",AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_item_new_copy,
	    STATIC_FUNCTION(g2int_write_icp_item_new_copy,NIL,FALSE,1,1));
    Qg2int_default_error = STATIC_SYMBOL("DEFAULT-ERROR",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    if (G2int_append_into_arrays_and_lists == UNBOUND)
	G2int_append_into_arrays_and_lists = Nil;
    if (G2int_delete_old_elements_from_arrays_and_lists == UNBOUND)
	G2int_delete_old_elements_from_arrays_and_lists = Nil;
    if (G2int_allow_no_value_p == UNBOUND)
	G2int_allow_no_value_p = T;
    Qg2int_read_immediate_g2_array_sequence = 
	    STATIC_SYMBOL("READ-IMMEDIATE-G2-ARRAY-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_immediate_g2_array_sequence,
	    STATIC_FUNCTION(g2int_read_immediate_g2_array_sequence,NIL,
	    FALSE,2,2));
    Qg2int_read_immediate_g2_list_sequence = 
	    STATIC_SYMBOL("READ-IMMEDIATE-G2-LIST-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_immediate_g2_list_sequence,
	    STATIC_FUNCTION(g2int_read_immediate_g2_list_sequence,NIL,
	    FALSE,2,2));
    if (G2int_identifying_attribute_count_for_item_new_copy == UNBOUND)
	G2int_identifying_attribute_count_for_item_new_copy = Nil;
    if (G2int_corresponding_icp_object_index_for_item_new_copy == UNBOUND)
	G2int_corresponding_icp_object_index_for_item_new_copy = Nil;
    if (G2int_item_being_read_for_new_reference == UNBOUND)
	G2int_item_being_read_for_new_reference = Nil;
    Qg2int_context = STATIC_SYMBOL("CONTEXT",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)49L),
	    FIX((SI_Long)67L));
    Qg2int_gsi_name_is_identifying_flag = 
	    STATIC_SYMBOL("GSI-NAME-IS-IDENTIFYING-FLAG",AB_package);
    Qg2int_read_icp_item_new_copy = STATIC_SYMBOL("READ-ICP-ITEM-NEW-COPY",
	    AB_package);
    Qg2int_resumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    Qg2int_true = STATIC_SYMBOL("TRUE",AB_package);
    Qg2int_false = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_item_new_copy,
	    STATIC_FUNCTION(g2int_read_icp_item_new_copy,NIL,FALSE,0,0));
    string_constant_1 = STATIC_STRING("Expected a value-structure");
    Qg2int_data_point_value = STATIC_SYMBOL("DATA-POINT-VALUE",AB_package);
    Qg2int_data_point_collection_time = 
	    STATIC_SYMBOL("DATA-POINT-COLLECTION-TIME",AB_package);
    Qg2int_data_point_expiration_time = 
	    STATIC_SYMBOL("DATA-POINT-EXPIRATION-TIME",AB_package);
    Qg2int_read_gsi_value_structure = 
	    STATIC_SYMBOL("READ-GSI-VALUE-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_gsi_value_structure,
	    STATIC_FUNCTION(g2int_read_gsi_value_structure,NIL,FALSE,1,1));
    list_constant_13 = STATIC_CONS(Qg2int_data_point_value,Qnil);
    if (G2int_data_point_value_interned_list == UNBOUND)
	G2int_data_point_value_interned_list = 
		g2int_intern_list(list_constant_13);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qg2int_data_point_value,
	    Qg2int_data_point_collection_time);
    if (G2int_data_point_value_and_collection_time_interned_list == UNBOUND)
	G2int_data_point_value_and_collection_time_interned_list = 
		g2int_intern_list(list_constant_14);
    Qg2int_write_gsi_value_structure = 
	    STATIC_SYMBOL("WRITE-GSI-VALUE-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_gsi_value_structure,
	    STATIC_FUNCTION(g2int_write_gsi_value_structure,NIL,FALSE,1,1));
    list_constant_9 = STATIC_LIST((SI_Long)5L,Qinteger,Qg2int_truth_value,
	    Qfloat,Qsymbol,Qg2int_text);
    Qg2int_read_sequence_into_gsi_item = 
	    STATIC_SYMBOL("READ-SEQUENCE-INTO-GSI-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_sequence_into_gsi_item,
	    STATIC_FUNCTION(g2int_read_sequence_into_gsi_item,NIL,FALSE,3,3));
    list_constant_15 = STATIC_CONS(Qinteger,Qnil);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)5L,Qg2int_text,
	    Qg2int_truth_value,Qfloat,Qsymbol,list_constant_15);
    Qg2int_long = STATIC_SYMBOL("LONG",AB_package);
    Qg2int_unsigned_short_vector = STATIC_SYMBOL("UNSIGNED-SHORT-VECTOR",
	    AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING("");
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_write_sequence_from_gsi_item = 
	    STATIC_SYMBOL("WRITE-SEQUENCE-FROM-GSI-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_sequence_from_gsi_item,
	    STATIC_FUNCTION(g2int_write_sequence_from_gsi_item,NIL,FALSE,2,2));
    string_constant_3 = STATIC_STRING("Expected a history specification");
    Qg2int_maximum_number_of_data_points = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-DATA-POINTS",AB_package);
    Qg2int_maximum_age_of_data_points = 
	    STATIC_SYMBOL("MAXIMUM-AGE-OF-DATA-POINTS",AB_package);
    Qg2int_minimum_interval_between_data_points = 
	    STATIC_SYMBOL("MINIMUM-INTERVAL-BETWEEN-DATA-POINTS",AB_package);
    Qg2int_read_gsi_history_specification = 
	    STATIC_SYMBOL("READ-GSI-HISTORY-SPECIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_gsi_history_specification,
	    STATIC_FUNCTION(g2int_read_gsi_history_specification,NIL,FALSE,
	    0,0));
    list_constant_16 = STATIC_LIST((SI_Long)3L,
	    Qg2int_maximum_number_of_data_points,
	    Qg2int_maximum_age_of_data_points,
	    Qg2int_minimum_interval_between_data_points);
    if (G2int_attributes_of_history_specification_structure_as_interned_list 
	    == UNBOUND)
	G2int_attributes_of_history_specification_structure_as_interned_list 
		= g2int_intern_list(list_constant_16);
    Qg2int_write_gsi_history_specification = 
	    STATIC_SYMBOL("WRITE-GSI-HISTORY-SPECIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_gsi_history_specification,
	    STATIC_FUNCTION(g2int_write_gsi_history_specification,NIL,
	    FALSE,1,1));
    Qg2int_read_gsi_effective_data_type_into_item = 
	    STATIC_SYMBOL("READ-GSI-EFFECTIVE-DATA-TYPE-INTO-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_gsi_effective_data_type_into_item,
	    STATIC_FUNCTION(g2int_read_gsi_effective_data_type_into_item,
	    NIL,FALSE,1,1));
    Qg2int_history_value = STATIC_SYMBOL("HISTORY-VALUE",AB_package);
    Qg2int_history_collection_time = 
	    STATIC_SYMBOL("HISTORY-COLLECTION-TIME",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qg2int_history_value,
	    Qg2int_history_collection_time);
    if (G2int_attributes_of_history_element_structure_as_interned_list == 
	    UNBOUND)
	G2int_attributes_of_history_element_structure_as_interned_list = 
		g2int_intern_list(list_constant_17);
    string_constant_4 = STATIC_STRING("expected a history sequence");
    string_constant_5 = 
	    STATIC_STRING("expected at least one element in the history");
    string_constant_6 = STATIC_STRING("expected a history element structure");
    Qg2int_read_gsi_history = STATIC_SYMBOL("READ-GSI-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_gsi_history,
	    STATIC_FUNCTION(g2int_read_gsi_history,NIL,FALSE,2,2));
    Qg2int_write_gsi_history = STATIC_SYMBOL("WRITE-GSI-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_gsi_history,
	    STATIC_FUNCTION(g2int_write_gsi_history,NIL,FALSE,2,2));
    if (G2int_pending_write_reference_list == UNBOUND)
	G2int_pending_write_reference_list = Nil;
    if (G2int_using_pending_write_reference_list == UNBOUND)
	G2int_using_pending_write_reference_list = Nil;
    Qg2int_write_icp_item_copy = STATIC_SYMBOL("WRITE-ICP-ITEM-COPY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_item_copy,
	    STATIC_FUNCTION(g2int_write_icp_item_copy,NIL,FALSE,1,1));
    Qg2int_read_icp_item_copy = STATIC_SYMBOL("READ-ICP-ITEM-COPY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_item_copy,
	    STATIC_FUNCTION(g2int_read_icp_item_copy,NIL,FALSE,0,0));
    Qg2_defstruct_structure_name_gsi_instance_g2_struct = 
	    STATIC_SYMBOL("GSI-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_copy = STATIC_SYMBOL("COPY",AB_package);
    Qg2int_handle = STATIC_SYMBOL("HANDLE",AB_package);
    Qg2int_gsi_reference_flag = STATIC_SYMBOL("GSI-REFERENCE-FLAG",AB_package);
    Qg2int_reference = STATIC_SYMBOL("REFERENCE",AB_package);
    Qg2int_write_icp_item = STATIC_SYMBOL("WRITE-ICP-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_item,
	    STATIC_FUNCTION(g2int_write_icp_item,NIL,FALSE,1,1));
    Qg2int_read_icp_item = STATIC_SYMBOL("READ-ICP-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_item,
	    STATIC_FUNCTION(g2int_read_icp_item,NIL,FALSE,0,0));
    Qg2int_write_icp_item_handle = STATIC_SYMBOL("WRITE-ICP-ITEM-HANDLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_item_handle,
	    STATIC_FUNCTION(g2int_write_icp_item_handle,NIL,FALSE,1,1));
    Qg2int_read_icp_item_handle = STATIC_SYMBOL("READ-ICP-ITEM-HANDLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_item_handle,
	    STATIC_FUNCTION(g2int_read_icp_item_handle,NIL,FALSE,0,0));
    Qg2int_write_icp_value_or_reference_argument_list = 
	    STATIC_SYMBOL("WRITE-ICP-VALUE-OR-REFERENCE-ARGUMENT-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_value_or_reference_argument_list,
	    STATIC_FUNCTION(g2int_write_icp_value_or_reference_argument_list,
	    NIL,FALSE,1,1));
    Qg2int_unbound = STATIC_SYMBOL("UNBOUND",AB_package);
    Qg2int_read_icp_value_or_reference_argument_list = 
	    STATIC_SYMBOL("READ-ICP-VALUE-OR-REFERENCE-ARGUMENT-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_value_or_reference_argument_list,
	    STATIC_FUNCTION(g2int_read_icp_value_or_reference_argument_list,
	    NIL,FALSE,0,0));
    Qg2int_write_icp_resumable_rpc_argument_list = 
	    STATIC_SYMBOL("WRITE-ICP-RESUMABLE-RPC-ARGUMENT-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_resumable_rpc_argument_list,
	    STATIC_FUNCTION(g2int_write_icp_resumable_rpc_argument_list,
	    NIL,FALSE,1,1));
    Qg2int_managed_array = STATIC_SYMBOL("MANAGED-ARRAY",AB_package);
    if (G2int_rpc_argument_list_error == UNBOUND)
	G2int_rpc_argument_list_error = Nil;
    Qg2int_read_icp_resumable_rpc_argument_list = 
	    STATIC_SYMBOL("READ-ICP-RESUMABLE-RPC-ARGUMENT-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_resumable_rpc_argument_list,
	    STATIC_FUNCTION(g2int_read_icp_resumable_rpc_argument_list,NIL,
	    FALSE,0,0));
    if (G2int_corresponding_icp_object_index_for_item_reference == UNBOUND)
	G2int_corresponding_icp_object_index_for_item_reference = Nil;
    Qg2int_new = STATIC_SYMBOL("NEW",AB_package);
    Qg2int_temporary = STATIC_SYMBOL("TEMPORARY",AB_package);
    Qg2int_remote = STATIC_SYMBOL("REMOTE",AB_package);
    Qg2int_local = STATIC_SYMBOL("LOCAL",AB_package);
    Qg2int_write_icp_item_reference = 
	    STATIC_SYMBOL("WRITE-ICP-ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_item_reference,
	    STATIC_FUNCTION(g2int_write_icp_item_reference,NIL,FALSE,1,1));
    Qg2int_read_reference_attributes = 
	    STATIC_SYMBOL("READ-REFERENCE-ATTRIBUTES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_reference_attributes,
	    STATIC_FUNCTION(g2int_read_reference_attributes,NIL,FALSE,3,3));
    string_constant_7 = 
	    STATIC_STRING("Internal error: Bad type-tag for reading an item reference");
    Qg2int_item_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2int_reading_new_item_reference = 
	    STATIC_SYMBOL("READING-NEW-ITEM-REFERENCE",AB_package);
    string_constant_8 = 
	    STATIC_STRING("an item sent by reference has been deleted");
    Qg2int_gsi_class_is_identifying_flag = 
	    STATIC_SYMBOL("GSI-CLASS-IS-IDENTIFYING-FLAG",AB_package);
    string_constant_9 = 
	    STATIC_STRING("an item sent by reference could not be found or constructed");
    Qg2int_read_icp_item_reference = 
	    STATIC_SYMBOL("READ-ICP-ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_item_reference,
	    STATIC_FUNCTION(g2int_read_icp_item_reference,NIL,FALSE,0,0));
    Qg2int_write_icp_item_reference_2 = 
	    STATIC_SYMBOL("WRITE-ICP-ITEM-REFERENCE-2",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_item_reference_2,
	    STATIC_FUNCTION(g2int_write_icp_item_reference_2,NIL,FALSE,1,1));
    Qg2int_read_icp_item_reference_2 = 
	    STATIC_SYMBOL("READ-ICP-ITEM-REFERENCE-2",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_item_reference_2,
	    STATIC_FUNCTION(g2int_read_icp_item_reference_2,NIL,FALSE,0,0));
    Qg2int_send_icp_create_item_reference = 
	    STATIC_SYMBOL("SEND-ICP-CREATE-ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_create_item_reference,
	    STATIC_FUNCTION(g2int_send_icp_create_item_reference,NIL,FALSE,
	    1,1));
    Qg2int_handle_icp_create_item_reference = 
	    STATIC_SYMBOL("HANDLE-ICP-CREATE-ITEM-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_create_item_reference,
	    STATIC_FUNCTION(g2int_handle_icp_create_item_reference,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_create_item_reference,
	    FIX((SI_Long)355L));
    if (G2int_current_network_interface == UNBOUND)
	G2int_current_network_interface = Nil;
    if (G2int_reference_class_info_p == UNBOUND)
	G2int_reference_class_info_p = Nil;
    Qg2int_home = STATIC_SYMBOL("HOME",AB_package);
    Qg2int_remote_gsi_interface_list = 
	    STATIC_SYMBOL("REMOTE-GSI-INTERFACE-LIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_remote_gsi_interface_list,
	    G2int_remote_gsi_interface_list);
    Qg2int_rpc_common3 = STATIC_SYMBOL("RPC-COMMON3",AB_package);
    g2int_record_system_variable(Qg2int_remote_gsi_interface_list,
	    Qg2int_rpc_common3,Nil,Qnil,Qnil,Qnil,Qnil);
    array_constant_3 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    if (G2int_home_name_separator == UNBOUND)
	G2int_home_name_separator = array_constant_3;
    string_constant_10 = STATIC_STRING("~A~A~A");
    Qg2int_remote_procedure_item_passing_info = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO",AB_package);
    Qg2int_send_icp_define_resumable_remote_procedure_identifier = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_define_resumable_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_send_icp_define_resumable_remote_procedure_identifier,
	    NIL,FALSE,3,3));
    Qg2int_handle_icp_define_resumable_remote_procedure_identifier = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_define_resumable_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_handle_icp_define_resumable_remote_procedure_identifier,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_define_resumable_remote_procedure_identifier,
	    FIX((SI_Long)352L));
    Qg2int_standard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qg2int_establish_new_object_index_for_resumable_remote_procedure_identifier 
	    = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_establish_new_object_index_for_resumable_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_establish_new_object_index_for_resumable_remote_procedure_identifier,
	    NIL,TRUE,2,3));
    Qg2int_make_corresponding_icp_resumable_remote_procedure_identifier = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_corresponding_icp_resumable_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_make_corresponding_icp_resumable_remote_procedure_identifier,
	    NIL,FALSE,1,1));
    Qg2int_set_access_form_for_resumable_remote_procedure_identifier = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_resumable_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_set_access_form_for_resumable_remote_procedure_identifier,
	    NIL,FALSE,2,2));
    Qg2int_resumable_remote_procedure_identifier = 
	    STATIC_SYMBOL("RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",AB_package);
    Qg2int_icp_object_map_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,
	    Qg2int_icp_object_map_for_remote_procedure_identifier,
	    Qg2int_resumable_remote_procedure_identifier);
    g2int_initialize_icp_object_type_compile(Qg2int_resumable_remote_procedure_identifier,
	    Qg2int_standard_icp_object_index_space,list_constant_18);
    Qg2int_reclaim_incoming_remote_procedure_identifier = 
	    STATIC_SYMBOL("RECLAIM-INCOMING-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    Qg2int_reclaim_remote_procedure_identifier_for_connection_loss = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-IDENTIFIER-FOR-CONNECTION-LOSS",
	    AB_package);
    Qg2int_reclaim_icp_port_entry_for_resumable_remote_procedure_identifier 
	    = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_resumable_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_resumable_remote_procedure_identifier,
	    NIL,FALSE,2,2));
    g2int_initialize_icp_object_type(Qg2int_resumable_remote_procedure_identifier,
	    Qg2int_reclaim_incoming_remote_procedure_identifier,
	    Qg2int_reclaim_remote_procedure_identifier_for_connection_loss,
	    Qg2int_reclaim_icp_port_entry_for_resumable_remote_procedure_identifier);
    Qg2int_send_icp_resumable_rpc_start = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-START",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_start,
	    STATIC_FUNCTION(g2int_send_icp_resumable_rpc_start,NIL,FALSE,2,2));
    Qg2int_start = STATIC_SYMBOL("START",AB_package);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_handle_icp_resumable_rpc_start = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUMABLE-RPC-START",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_resumable_rpc_start,
	    STATIC_FUNCTION(g2int_handle_icp_resumable_rpc_start,NIL,FALSE,
	    0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_resumable_rpc_start,
	    FIX((SI_Long)247L));
    Qg2int_send_icp_resumable_rpc_call = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-CALL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_call,
	    STATIC_FUNCTION(g2int_send_icp_resumable_rpc_call,NIL,FALSE,3,3));
    Qg2int_call = STATIC_SYMBOL("CALL",AB_package);
    Qg2int_handle_icp_resumable_rpc_call = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUMABLE-RPC-CALL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_resumable_rpc_call,
	    STATIC_FUNCTION(g2int_handle_icp_resumable_rpc_call,NIL,FALSE,
	    0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_resumable_rpc_call,
	    FIX((SI_Long)248L));
    Qg2int_send_icp_resumable_rpc_return_values = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-RETURN-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_return_values,
	    STATIC_FUNCTION(g2int_send_icp_resumable_rpc_return_values,NIL,
	    FALSE,2,2));
    Qg2int_rpc_return_values = STATIC_SYMBOL("RPC-RETURN-VALUES",AB_package);
    Qg2int_outstanding = STATIC_SYMBOL("OUTSTANDING",AB_package);
    Qg2int_returned = STATIC_SYMBOL("RETURNED",AB_package);
    Qg2int_handle_icp_resumable_rpc_return_values = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUMABLE-RPC-RETURN-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_resumable_rpc_return_values,
	    STATIC_FUNCTION(g2int_handle_icp_resumable_rpc_return_values,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_resumable_rpc_return_values,
	    FIX((SI_Long)249L));
    Qg2int_send_icp_resumable_rpc_error = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-ERROR",AB_package);
    Qg2int_corresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_error,
	    STATIC_FUNCTION(g2int_send_icp_resumable_rpc_error,NIL,FALSE,4,4));
    Qg2int_rpc_error_handler_1 = STATIC_SYMBOL("RPC_ERROR_HANDLER_1",
	    AB_package);
    Qg2int_handle_icp_resumable_rpc_error = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUMABLE-RPC-ERROR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_resumable_rpc_error,
	    STATIC_FUNCTION(g2int_handle_icp_resumable_rpc_error,NIL,FALSE,
	    0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_resumable_rpc_error,
	    FIX((SI_Long)353L));
    string_constant_11 = 
	    STATIC_STRING("The error-object did not have a null type tag");
    Qg2int_error_description = STATIC_SYMBOL("ERROR-DESCRIPTION",AB_package);
    string_constant_12 = 
	    STATIC_STRING("The error-object did not have a error-description attribute");
    string_constant_13 = 
	    STATIC_STRING("The error-description attribute of the error-object was not a string");
    Qg2int_g2_error = STATIC_SYMBOL("G2-ERROR",AB_package);
    Qg2int_g2_rpc_error = STATIC_SYMBOL("G2-RPC-ERROR",AB_package);
    string_constant_14 = 
	    STATIC_STRING("The first result, error-name, is not a symbol");
    string_constant_15 = 
	    STATIC_STRING("The second result, error-message, is not a string");
    string_constant_16 = 
	    STATIC_STRING("The number of results is not equal to 1 or 2");
    Qg2int_send_icp_resumable_rpc_error_to_caller = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-ERROR-TO-CALLER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_error_to_caller,
	    STATIC_FUNCTION(g2int_send_icp_resumable_rpc_error_to_caller,
	    NIL,FALSE,6,6));
    Qg2int_sync_abort = STATIC_SYMBOL("SYNC-ABORT",AB_package);
    Qg2int_error_return = STATIC_SYMBOL("ERROR-RETURN",AB_package);
    Qg2int_handle_icp_resumable_rpc_error_to_caller = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUMABLE-RPC-ERROR-TO-CALLER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_resumable_rpc_error_to_caller,
	    STATIC_FUNCTION(g2int_handle_icp_resumable_rpc_error_to_caller,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_resumable_rpc_error_to_caller,
	    FIX((SI_Long)354L));
}
