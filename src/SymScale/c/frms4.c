/* frms4.c
 * Input file:  frames4.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms4.h"


Object Absent_slot_putter_prop = UNBOUND;

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* PUT-SUBBLOCKS-WHERE-SLOT-IS-ABSENT */
Object put_subblocks_where_slot_is_absent(block,value)
    Object block, value;
{
    Object subblock, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object slot_group_qm, temp;

    x_note_fn_call(86,0);
    subblock = Nil;
    ab_loop_list_ = value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subblock = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = subblock;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    gensymed_symbol_1 = block;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)5L)) = gensymed_symbol_1;
    }
    goto next_loop;
  end_loop:;
    if (value) {
	gensymed_symbol = block;
	gensymed_symbol_1 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	gensymed_symbol_1 = upgrade_subblocks(value);
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)4L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,Qnil)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	    temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp,FIX((SI_Long)4L)) = gensymed_symbol_1;
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Blocks_with_connections_from_kb_read, Qblocks_with_connections_from_kb_read);

/* PUT-CONNECTIONS-WHERE-SLOT-IS-ABSENT */
Object put_connections_where_slot_is_absent(block,value)
    Object block, value;
{
    Object gensymed_symbol, gensymed_symbol_1, slot_group_qm, temp;

    x_note_fn_call(86,1);
    if (value) {
	gensymed_symbol = block;
	gensymed_symbol_1 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	gensymed_symbol_1 = upgrade_connections(value);
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,Qnil)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	    temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp,FIX((SI_Long)6L)) = gensymed_symbol_1;
	}
	Blocks_with_connections_from_kb_read = gensym_cons_1(block,
		Blocks_with_connections_from_kb_read);
    }
    return VALUES_1(Nil);
}

/* PUT-LEFT-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT */
Object put_left_edge_of_content_of_block_1_where_slot_is_absent(block,edge)
    Object block, edge;
{
    x_note_fn_call(86,2);
    return VALUES_1(Nil);
}

/* PUT-TOP-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT */
Object put_top_edge_of_content_of_block_1_where_slot_is_absent(block,edge)
    Object block, edge;
{
    x_note_fn_call(86,3);
    return VALUES_1(Nil);
}

/* PUT-RIGHT-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT */
Object put_right_edge_of_content_of_block_1_where_slot_is_absent(block,edge)
    Object block, edge;
{
    x_note_fn_call(86,4);
    return VALUES_1(Nil);
}

/* PUT-BOTTOM-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT */
Object put_bottom_edge_of_content_of_block_1_where_slot_is_absent(block,edge)
    Object block, edge;
{
    x_note_fn_call(86,5);
    return VALUES_1(Nil);
}

Object Substitute_class_and_kb_flags_prop = UNBOUND;

/* WRITE-NAME-OR-CLASS-QUALIFIED-NAME */
Object write_name_or_class_qualified_name(name_denotation)
    Object name_denotation;
{
    Object temp;

    x_note_fn_call(86,6);
    temp = write_name_denotation(name_denotation);
    return VALUES_1(temp);
}

static Object Qclass_qualified_name;  /* class-qualified-name */

/* DENOTE-SLOT-USING-SLOT-VALUE-CONSES */
Object denote_slot_using_slot_value_conses(slot_description,class_description)
    Object slot_description, class_description;
{
    Object slot_name, temp, defining_class_qm;
    char temp_1;

    x_note_fn_call(86,7);
    slot_name = ISVREF(slot_description,(SI_Long)2L);
    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	temp = ISVREF(slot_description,(SI_Long)3L);
	temp_1 =  !EQ(temp,
		ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		(SI_Long)2L),class_description,Nil),(SI_Long)3L));
    }
    else
	temp_1 = TRUEP(Nil);
    defining_class_qm = temp_1 ? ISVREF(slot_description,(SI_Long)3L) : Nil;
    temp = defining_class_qm ? slot_value_cons_1(Qclass_qualified_name,
	    slot_value_cons_1(defining_class_qm,
	    slot_value_cons_1(slot_name,Nil))) : slot_name;
    return VALUES_1(temp);
}

/* WRITE-NAME-DENOTATION-FOR-SLOT */
Object write_name_denotation_for_slot(slot_description,class_description)
    Object slot_description, class_description;
{
    Object temp, temp_1;
    char temp_2;

    x_note_fn_call(86,8);
    if ( !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	temp = get_alias_for_slot_name_if_any(ISVREF(slot_description,
		(SI_Long)2L),ISVREF(class_description,(SI_Long)1L));
	if (temp);
	else
	    temp = ISVREF(slot_description,(SI_Long)2L);
    }
    else
	temp = ISVREF(slot_description,(SI_Long)2L);
    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	temp_1 = ISVREF(slot_description,(SI_Long)3L);
	temp_2 =  !EQ(temp_1,
		ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		(SI_Long)2L),class_description,Nil),(SI_Long)3L));
    }
    else
	temp_2 = TRUEP(Nil);
    write_name_denotation_components(temp,temp_2 ? ISVREF(slot_description,
	    (SI_Long)3L) : Nil);
    return VALUES_1(Nil);
}

/* WRITE-NAME-DENOTATION */
Object write_name_denotation(name_denotation)
    Object name_denotation;
{
    Object temp;

    x_note_fn_call(86,9);
    temp = write_name_denotation_components(CONSP(name_denotation) ? 
	    M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation,
	    CONSP(name_denotation) ? M_CAR(M_CDR(name_denotation)) : Nil);
    return VALUES_1(temp);
}

static Object string_constant;     /* "~(~a::~a~)" */

static Object string_constant_1;   /* "~(~a~)" */

/* WRITE-NAME-DENOTATION-COMPONENTS */
Object write_name_denotation_components(name,defining_class_qm)
    Object name, defining_class_qm;
{
    Object temp;

    x_note_fn_call(86,10);
    temp = defining_class_qm;
    if (temp);
    else
	temp = name;
    temp = tformat(3,defining_class_qm ? string_constant : 
	    string_constant_1,temp,name);
    return VALUES_1(temp);
}

/* SLOT-DENOTATION-MEMBER */
Object slot_denotation_member(slot_name,class_qualifier_qm,
	    name_denotations_list)
    Object slot_name, class_qualifier_qm, name_denotations_list;
{
    Object name_denotations, name_denotation, temp;

    x_note_fn_call(86,11);
    name_denotations = name_denotations_list;
    name_denotation = Nil;
  next_loop:
    if ( !TRUEP(name_denotations))
	goto end_loop;
    name_denotation = CAR(name_denotations);
    if (EQ(slot_name,CONSP(name_denotation) ? 
	    M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation) && 
	    EQ(class_qualifier_qm,CONSP(name_denotation) ? 
	    M_CAR(M_CDR(name_denotation)) : Nil)) {
	temp = name_denotations;
	goto end_1;
    }
    name_denotations = M_CDR(name_denotations);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-PRETTY-SLOT-NAME-FOR-PARENT-ATTRIBUTE-IF-ANY */
Object get_pretty_slot_name_for_parent_attribute_if_any(item)
    Object item;
{
    Object parent_slot_name_qm;
    Object result;

    x_note_fn_call(86,12);
    result = get_kb_parent_information(item);
    parent_slot_name_qm = NTH_VALUE((SI_Long)1L, result);
    return VALUES_1(parent_slot_name_qm);
}

/* GET-DEFINING-CLASS-FOR-PARENT-ATTRIBUTE-IF-ANY */
Object get_defining_class_for_parent_attribute_if_any(item)
    Object item;
{
    Object parent_frame_qm, parent_slot_name_qm;
    Object parent_slot_name_defining_class_qm, temp, class_description;
    Object result;

    x_note_fn_call(86,13);
    result = get_kb_parent_information(item);
    MVS_3(result,parent_frame_qm,parent_slot_name_qm,
	    parent_slot_name_defining_class_qm);
    if (parent_frame_qm) {
	temp = parent_slot_name_defining_class_qm;
	if (temp)
	    return VALUES_1(temp);
	else {
	    class_description = ISVREF(parent_frame_qm,(SI_Long)1L);
	    return VALUES_1(ISVREF(get_slot_description(2,
		    parent_slot_name_qm,ISVREF(class_description,
		    (SI_Long)6L)),(SI_Long)3L));
	}
    }
    else
	return VALUES_1(Nil);
}

/* SLOT-EXISTS-IN-FRAME-P */
Object slot_exists_in_frame_p(slot_designation,frame)
    Object slot_designation, frame;
{
    x_note_fn_call(86,14);
    return VALUES_1( ! 
	    !TRUEP(get_slot_description_of_class_description_function(CONSP(slot_designation) 
	    ? M_CAR(M_CDR(M_CDR(slot_designation))) : slot_designation,
	    ISVREF(frame,(SI_Long)1L),CONSP(slot_designation) ? 
	    M_CAR(M_CDR(slot_designation)) : Nil)) ? T : Nil);
}

/* PARSE-SLOT-NAME-DENOTATION */
Object parse_slot_name_denotation(symbol,frame)
    Object symbol, frame;
{
    Object string_1, end_1, pos_qm, temp, temp_1, pos2, substring;
    Object slot_name_qm, class_name_qm, slot_name;
    SI_Long delimiter, i, ab_loop_bind_, code;
    Object result;

    x_note_fn_call(86,15);
    string_1 = symbol_name_text_string(symbol);
    end_1 = text_string_length(string_1);
    delimiter = (SI_Long)58L;
    pos_qm = position_in_text_string(FIX(delimiter),string_1);
    if ( !TRUEP(pos_qm)) {
	temp = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
	result = VALUES_2(symbol,temp);
    }
    else {
	i = IFIX(pos_qm);
	ab_loop_bind_ = IFIX(end_1);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	code = UBYTE_16_ISAREF_1(string_1,i);
	if (code < (SI_Long)127L)
	    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? FIX(code 
		    + (SI_Long)32L) : FIX(code);
	else {
	    temp = unicode_lowercase_if_uppercase(FIX(code));
	    if (temp);
	    else
		temp = FIX(code);
	}
	code = delimiter;
	if (code < (SI_Long)127L)
	    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
		    FIX(code + (SI_Long)32L) : FIX(code);
	else {
	    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
	    if (temp_1);
	    else
		temp_1 = FIX(code);
	}
	if ( !NUM_EQ(temp,temp_1))
	    goto end_loop;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	pos2 = FIX(i);
	goto end_2;
	pos2 = Qnil;
      end_2:;
	if (FIXNUM_LT(pos2,end_1)) {
	    substring = text_string_substring(string_1,pos2,end_1);
	    temp_1 = intern_text_string(2,substring,Ab_package_1);
	}
	else
	    temp_1 = Nil;
	substring = text_string_substring(string_1,FIX((SI_Long)0L),pos_qm);
	temp = intern_text_string(2,substring,Ab_package_1);
	result = VALUES_2(temp_1,temp);
    }
    MVS_2(result,slot_name_qm,class_name_qm);
    if (slot_name_qm) {
	slot_name = get_slot_name_for_alias_if_any(slot_name_qm,class_name_qm);
	if (slot_name);
	else
	    slot_name = slot_name_qm;
	if (class_name_qm)
	    return slot_value_cons_1(Qclass_qualified_name,
		    slot_value_cons_1(class_name_qm,
		    slot_value_cons_1(slot_name,Nil)));
	else
	    return VALUES_1(slot_name);
    }
    else
	return VALUES_1(Nil);
}

/* GET-TYPE-OF-SLOT-IF-ANY */
Object get_type_of_slot_if_any varargs_1(int, n)
{
    Object frame, pretty_slot_name;
    Object class_qualifier_qm, slot_description_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(86,16);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    pretty_slot_name = REQUIRED_ARG_nonrelocating();
    class_qualifier_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    slot_description_qm = 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_qualifier_qm);
    if (slot_description_qm)
	return assq_function(Qtype,ISVREF(slot_description_qm,(SI_Long)9L));
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* TYPE-OF-SLOT-IF-EDITABLE */
Object type_of_slot_if_editable varargs_1(int, n)
{
    Object class_qm, slot_name_qm;
    Object slot_description_if_known_qm, class_if_specific_qm, x2;
    Object slot_description, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, slot_features;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(86,17);
    INIT_ARGS_nonrelocating();
    class_qm = REQUIRED_ARG_nonrelocating();
    slot_name_qm = REQUIRED_ARG_nonrelocating();
    slot_description_if_known_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    class_if_specific_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SIMPLE_VECTOR_P(class_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(class_qm)) > (SI_Long)2L &&  
	    !EQ(ISVREF(class_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(class_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_qm = ISVREF(ISVREF(class_qm,(SI_Long)1L),(SI_Long)1L);
    slot_description = slot_description_if_known_qm;
    if (slot_description);
    else {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_qm;
	key_hash_value = SXHASH_SYMBOL_1(class_qm) & 
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_qm;
	    temp_1 = Symbol_properties_table;
	    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
	  next_loop_9:
	    if (level < ab_loop_bind_)
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	gensymed_symbol = resulting_value;
	slot_description = 
		get_slot_description_of_class_description_function(slot_name_qm,
		gensymed_symbol,class_if_specific_qm);
    }
    slot_features = ISVREF(slot_description,(SI_Long)9L);
    return type_slot_feature_assq_if_editable(slot_features);
}

DEFINE_VARIABLE_WITH_SYMBOL(Gathering_normally_editable_slots_for_search_qm, Qgathering_normally_editable_slots_for_search_qm);

static Object Qnot_user_editable;  /* not-user-editable */

static Object Qfree;               /* free */

static Object Qfree_text_attribute;  /* free-text-attribute */

static Object Qprocedure_definition;  /* procedure-definition */

static Object Qselect_changes;     /* select-changes */

/* TYPE-SLOT-FEATURE-ASSQ-IF-EDITABLE */
Object type_slot_feature_assq_if_editable(slot_features)
    Object slot_features;
{
    Object type_of_slot_qm, code;
    char temp;

    x_note_fn_call(86,18);
    if ( !TRUEP(assq_function(Qnot_user_editable,slot_features))) {
	type_of_slot_qm = assq_function(Qtype,slot_features);
	if (type_of_slot_qm && (EQ(CADR(type_of_slot_qm),Qfree) || 
		EQ(CADR(type_of_slot_qm),Qfree_text_attribute) || 
		get(SECOND(type_of_slot_qm),
		Current_indicator_for_category_of_this_name,_))) {
	    temp = TRUEP(Gathering_normally_editable_slots_for_search_qm);
	    if (temp);
	    else {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !(temp ? TRUEP(memq_function(Qprocedure_definition,
			type_of_slot_qm)) : TRUEP(Nil));
	    }
	    if (temp);
	    else
		temp =  !TRUEP(assq_function(Qselect_changes,slot_features));
	    if (temp)
		return VALUES_1(type_of_slot_qm);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qedit_attribute;     /* edit-attribute */

/* GET-SLOT-DESCRIPTION-IF-EDITABLE-ATTRIBUTE */
Object get_slot_description_if_editable_attribute(frame,aliased_slot_name,
	    class_qualifier_qm)
    Object frame, aliased_slot_name, class_qualifier_qm;
{
    Object slot_name, class_description, slot_description_qm;

    x_note_fn_call(86,19);
    slot_name = get_slot_name_for_alias_if_any(aliased_slot_name,frame);
    if (slot_name);
    else
	slot_name = aliased_slot_name;
    class_description = ISVREF(frame,(SI_Long)1L);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(slot_name,
	    class_description,class_qualifier_qm);
    if (slot_description_qm && 
	    type_slot_feature_assq_if_editable(ISVREF(slot_description_qm,
	    (SI_Long)9L)) && 
	    attribute_operation_is_allowed_p(Qedit_attribute,frame,
	    aliased_slot_name,ISVREF(slot_description_qm,(SI_Long)3L)))
	return VALUES_1(slot_description_qm);
    else
	return VALUES_1(Nil);
}

/* SLOT-EDITABLE-P */
Object slot_editable_p(frame,internal_slot_name,class_qualifier_qm)
    Object frame, internal_slot_name, class_qualifier_qm;
{
    Object temp;

    x_note_fn_call(86,20);
    temp = get_alias_for_slot_name_if_any(internal_slot_name,frame);
    if (temp);
    else
	temp = internal_slot_name;
    return get_slot_description_if_editable_attribute(frame,temp,
	    class_qualifier_qm);
}

Object Slot_value_compiler_prop = UNBOUND;

Object Use_slot_value_compiler_for_default_overrides_p_prop = UNBOUND;

Object Slot_value_writer_prop = UNBOUND;

static Object Qnone;               /* none */

/* WRITE-SYMBOL-FROM-SLOT */
Object write_symbol_from_slot(symbol,frame)
    Object symbol, frame;
{
    Object temp;

    x_note_fn_call(86,21);
    temp = symbol;
    if (temp);
    else
	temp = Qnone;
    return twrite_symbol(1,temp);
}

/* WRITE-EXPRESSION-FROM-SLOT */
Object write_expression_from_slot(expression,frame)
    Object expression, frame;
{
    Object temp;

    x_note_fn_call(86,22);
    temp = expression;
    if (temp);
    else
	temp = Qnone;
    return write_expression(temp);
}

/* MAKE-TEXT-REPRESENTATION-FOR-SLOT-VALUE */
Object make_text_representation_for_slot_value varargs_1(int, n)
{
    Object frame, pretty_slot_name;
    Object class_qualifier_qm, slot_description;
    Declare_varargs_nonrelocating;

    x_note_fn_call(86,23);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    pretty_slot_name = REQUIRED_ARG_nonrelocating();
    class_qualifier_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    slot_description = 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_qualifier_qm);
    return make_text_representation_for_slot_value_itself(frame,
	    get_slot_description_value(frame,slot_description),
	    assq_function(Qtype,ISVREF(slot_description,(SI_Long)9L)));
}

/* MAKE-TEXT-REPRESENTATION-FOR-SLOT-DESCRIPTION-VALUE */
Object make_text_representation_for_slot_description_value(frame,
	    slot_description)
    Object frame, slot_description;
{
    x_note_fn_call(86,24);
    return make_text_representation_for_slot_value_itself(frame,
	    get_slot_description_value(frame,slot_description),
	    assq_function(Qtype,ISVREF(slot_description,(SI_Long)9L)));
}

/* MAKE-TEXT-STRING-REPRESENTATION-FOR-SLOT-VALUE-ITSELF */
Object make_text_string_representation_for_slot_value_itself(frame,
	    slot_value,type_of_slot)
    Object frame, slot_value, type_of_slot;
{
    x_note_fn_call(86,25);
    return make_text_or_text_string_representation_for_slot_value_itself(frame,
	    slot_value,type_of_slot,Nil);
}

/* MAKE-TEXT-REPRESENTATION-FOR-SLOT-VALUE-ITSELF */
Object make_text_representation_for_slot_value_itself(frame,slot_value,
	    type_of_slot)
    Object frame, slot_value, type_of_slot;
{
    x_note_fn_call(86,26);
    return make_text_or_text_string_representation_for_slot_value_itself(frame,
	    slot_value,type_of_slot,T);
}

static Object Qtext;               /* text */

static Object Qslot_value_writer;  /* slot-value-writer */

/* MAKE-TEXT-OR-TEXT-STRING-REPRESENTATION-FOR-SLOT-VALUE-ITSELF */
Object make_text_or_text_string_representation_for_slot_value_itself(frame,
	    slot_value,type_of_slot,text_case_qm)
    Object frame, slot_value, type_of_slot, text_case_qm;
{
    Object temp, gensymed_symbol;
    char temp_1;

    x_note_fn_call(86,27);
    if (memq_function(Qtext,CDDR(type_of_slot))) {
	if (slot_value && CONSP(slot_value)) {
	    temp = CDR(slot_value);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = text_case_qm ? copy_text(CDR(slot_value)) : 
		    convert_text_to_text_string(1,CDR(slot_value));
	else {
	    gensymed_symbol = SECOND(type_of_slot);
	    temp =  
		    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qslot_value_writer)) ? (text_case_qm ? 
		    make_empty_text() : 
		    obtain_simple_text_string(FIX((SI_Long)0L))) : Nil;
	}
    }
    else
	temp = Nil;
    if (temp)
	return VALUES_1(temp);
    else if (text_case_qm)
	return write_slot_value_to_text(frame,slot_value,type_of_slot);
    else
	return write_slot_value_to_string(frame,slot_value,type_of_slot);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_2;   /* "[deleted attribute]" */

/* WRITE-SLOT-VALUE-TO-STRING */
Object write_slot_value_to_string(frame,slot_value,type_of_slot)
    Object frame, slot_value, type_of_slot;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object grammar_category_symbol, frame_qm, slot_value_writer_qm;
    Object write_symbols_in_lower_case_qm, write_symbols_parsably_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);
    Object result;

    x_note_fn_call(86,28);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
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
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      grammar_category_symbol = SECOND(type_of_slot);
	      frame_qm = frame;
	      slot_value_writer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_symbol),
		      Qslot_value_writer);
	      if (slot_value_writer_qm) {
		  write_symbols_in_lower_case_qm = T;
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    0);
		      inline_funcall_2(slot_value_writer_qm,slot_value,
			      frame_qm);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  twrite(string_constant_2);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qab_slot_value;      /* slot-value */

/* WRITE-SLOT-VALUE-TO-TEXT */
Object write_slot_value_to_text(frame,slot_value,type_of_slot)
    Object frame, slot_value, type_of_slot;
{
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object grammar_category_symbol, frame_qm, slot_value_writer_qm;
    Object write_symbols_in_lower_case_qm, write_symbols_parsably_qm, temp;
    Object temp_1, gensym_list_of_wide_strings, string_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object svref_new_value, gensymed_symbol, short_string, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(86,29);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
      current_wide_string = new_wide_string;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      grammar_category_symbol = SECOND(type_of_slot);
	      frame_qm = frame;
	      slot_value_writer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_symbol),
		      Qslot_value_writer);
	      if (slot_value_writer_qm) {
		  write_symbols_in_lower_case_qm = T;
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    0);
		      inline_funcall_2(slot_value_writer_qm,slot_value,
			      frame_qm);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  twrite(string_constant_2);
	      temp = Current_wide_string;
	      temp_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(temp_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(temp_1) >>  -  - 
		      (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp,IFIX(temp_1),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_slot_value_conses_vector;
	temp_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,temp_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_slot_value_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_slot_value_conses_vector;
	temp_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,temp_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_slot_value_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp = short_string;
    }
    else
	temp = string_1;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp_2 = ab_loopvar_;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    return VALUES_1(temp_2);
}

static Object Qitem_position;      /* item-position */

static Object Qicon_position;      /* icon-position */

static Object Qoriginal_kb_state_plist;  /* original-kb-state-plist */

/* PUT-ORIGINAL-KB-STATE-PLIST */
Object put_original_kb_state_plist(block,value,initializing_qm)
    Object block, value, initializing_qm;
{
    Object indicator, value_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp;

    x_note_fn_call(86,30);
    if (initializing_qm && value &&  !TRUEP(Loading_kb_p)) {
	if (getf(value,Qitem_position,_) || getf(value,Qicon_position,_)) {
	    indicator = Nil;
	    value_1 = Nil;
	    ab_loop_list_ = value;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    indicator = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    value_1 = CAR(temp);
	    if ( !(EQ(indicator,Qitem_position) || EQ(indicator,
		    Qicon_position))) {
		ab_loopvar__2 = slot_value_list_2(indicator,value_1);
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
	    }
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:
	    temp = ab_loopvar_;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    reclaim_slot_value_list_1(value);
	    value = temp;
	}
    }
    if (value)
	note_as_frame_with_kb_state_changes(block);
    return set_non_savable_lookup_slot_value(block,
	    Qoriginal_kb_state_plist,value);
}

/* RECLAIM-KB-STATE-CHANGES-PREVIOUS-CONS?-VALUE */
Object reclaim_kb_state_changes_previous_cons_qm_value(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(86,31);
    return VALUES_1(Nil);
}

static Object Qkb_state_changes_previous_cons_qm;  /* kb-state-changes-previous-cons? */

/* PUT-KB-STATE-CHANGES-PREVIOUS-CONS? */
Object put_kb_state_changes_previous_cons_qm(block,value,gensymed_symbol)
    Object block, value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(86,32);
    temp = set_non_savable_lookup_slot_value(block,
	    Qkb_state_changes_previous_cons_qm,value);
    return VALUES_2(temp,T);
}

static Object Qwhat_this_is_a_menu_for_qm;  /* what-this-is-a-menu-for? */

static Object Qmenus_for_this;     /* menus-for-this */

/* RECLAIM-MENUS-FOR-THIS-VALUE */
Object reclaim_menus_for_this_value(value,frame)
    Object value, frame;
{
    Object menu_1, ab_loop_list_;

    x_note_fn_call(86,33);
    menu_1 = Nil;
    ab_loop_list_ = value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    menu_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_slot_value_function(menu_1,Qwhat_this_is_a_menu_for_qm,Nil,Nil);
    delete_menu(menu_1);
    goto next_loop;
  end_loop:;
    if (CONSP(value))
	reclaim_slot_value_list_1(value);
    set_non_savable_lookup_slot_value(frame,Qmenus_for_this,Nil);
    return VALUES_1(Nil);
}

/* MIDLINE-X-OF-BLOCK-FUNCTION */
Object midline_x_of_block_function(block)
    Object block;
{
    Object gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(86,34);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    return VALUES_1(FIX(gensymed_symbol_1 >>  -  - gensymed_symbol_2));
}

/* MIDLINE-Y-OF-BLOCK-FUNCTION */
Object midline_y_of_block_function(block)
    Object block;
{
    Object gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(86,35);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    return VALUES_1(FIX(gensymed_symbol_1 >>  -  - gensymed_symbol_2));
}

/* DELETE-SUBBLOCKS-OF-CLASS */
Object delete_subblocks_of_class(block,class_or_classes)
    Object block, class_or_classes;
{
    x_note_fn_call(86,36);
    return delete_subblocks_based_on_class(block,class_or_classes,Nil);
}

/* DELETE-SUBBLOCKS-NOT-OF-CLASS */
Object delete_subblocks_not_of_class(block,class_or_classes)
    Object block, class_or_classes;
{
    x_note_fn_call(86,37);
    return delete_subblocks_based_on_class(block,class_or_classes,T);
}

static Object Qab_gensym;          /* gensym */

/* DELETE-SUBBLOCKS-BASED-ON-CLASS */
Object delete_subblocks_based_on_class(block,class_or_classes,
	    not_of_class_case_qm)
    Object block, class_or_classes, not_of_class_case_qm;
{
    Object frame_reference_serial_number, class_qm, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock;
    Object subblocks_to_delete, ab_loopvar_, ab_loopvar__1;
    Object sub_class_bit_vector, class_1, ab_loop_list_, ab_loop_it_, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, subblock_to_delete, xa;
    Object ya;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(86,38);
    frame_reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    class_qm = ATOM(class_or_classes) ? class_or_classes : Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    subblocks_to_delete = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    if (class_qm) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_qm,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
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
    }
    else {
	class_1 = Nil;
	ab_loop_list_ = class_or_classes;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
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
		ab_loop_it_ = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	    }
	    else
		ab_loop_it_ = Nil;
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
    }
    if (temp ?  !TRUEP(not_of_class_case_qm) : TRUEP(not_of_class_case_qm)) {
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol) = subblock;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ab_loopvar__1 = gensymed_symbol;
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    subblocks_to_delete = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    if (subblocks_to_delete) {
	delete_frame(CAR(subblocks_to_delete));
	if (CDR(subblocks_to_delete)) {
	    subblock_to_delete = Nil;
	    ab_loop_list_ = CDR(subblocks_to_delete);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    subblock_to_delete = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(subblock_to_delete,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(subblock_to_delete) ? 
		    EQ(ISVREF(subblock_to_delete,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(frame_reference_serial_number))
		temp = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_reference_serial_number,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_reference_serial_number);
		ya = M_CAR(gensymed_symbol);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_reference_serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp)
		delete_frame(subblock_to_delete);
	    goto next_loop_2;
	  end_loop_2:;
	}
	reclaim_gensym_list_1(subblocks_to_delete);
    }
    reclaim_frame_serial_number(frame_reference_serial_number);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Models_used_p, Qmodels_used_p);

/* RECLAIM-SUBBLOCKS-VALUE */
Object reclaim_subblocks_value(superblock)
    Object superblock;
{
    Object gensymed_symbol, subblocks, sub_class_bit_vector, ab_queue_form_;
    Object ab_next_queue_element_, subblock, gensymed_symbol_4, slot_group_qm;
    Object temp_1, reference_serial_number, xa, ya;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(86,39);
    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    sub_class_bit_vector = ISVREF(ISVREF(superblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
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
    if (temp ? TRUEP(Models_used_p) : TRUEP(Nil)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
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
	gensymed_symbol = subblock;
	gensymed_symbol_4 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	gensymed_symbol_4 = Nil;
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_4;
	else if ( !EQ(gensymed_symbol_4,Qnil)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp_1 = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = gensymed_symbol_4;
	}
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Model_definition_class_description,(SI_Long)18L));
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
	    install_item_in_model_if_appropriate(superblock,Nil,T);
	goto next_loop;
      end_loop:;
    }
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_1:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_1;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	gensymed_symbol = subblock;
	gensymed_symbol_4 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	gensymed_symbol_4 = Nil;
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_4;
	else if ( !EQ(gensymed_symbol_4,Qnil)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp_1 = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = gensymed_symbol_4;
	}
	goto next_loop_1;
      end_loop_1:;
    }
    reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_2:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_2;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    gensymed_symbol = ISVREF(subblock,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(subblock) ? EQ(ISVREF(subblock,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp)
	delete_frame(subblock);
    goto next_loop_2;
  end_loop_2:
    reclaim_frame_serial_number(reference_serial_number);
    if (subblocks)
	reclaim_constant_queue(subblocks);
    gensymed_symbol = superblock;
    gensymed_symbol_4 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_4 = Nil;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)4L)) = gensymed_symbol_4;
    else if ( !EQ(gensymed_symbol_4,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp_1 = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp_1,FIX((SI_Long)4L)) = gensymed_symbol_4;
    }
    return VALUES_1(gensymed_symbol_4);
}

/* RECLAIM-SLOT-GROUP-FOR-BLOCK?-VALUE */
Object reclaim_slot_group_for_block_qm_value(slot_group_for_block_qm,block)
    Object slot_group_for_block_qm, block;
{
    x_note_fn_call(86,40);
    if (slot_group_for_block_qm) {
	reclaim_subblocks_value(block);
	reclaim_connections_value(block);
	reclaim_icon_slot_group_1(slot_group_for_block_qm);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qslot_group_for_block_qm);
    SVREF(block,FIX((SI_Long)14L)) = Nil;
    return VALUES_1(Nil);
}

/* SHIFT-BLOCK */
Object shift_block(block,delta_x_in_workspace,delta_y_in_workspace)
    Object block, delta_x_in_workspace, delta_y_in_workspace;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(86,41);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
    gensymed_symbol_1 = block;
    gensymed_symbol_2 = delta_x_in_workspace;
    gensymed_symbol_3 = delta_y_in_workspace;
    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3);
}

/* SHIFT-BLOCK-TO */
Object shift_block_to(block,x_in_workspace,y_in_workspace)
    Object block, x_in_workspace, y_in_workspace;
{
    Object gensymed_symbol_1, temp;
    SI_Long gensymed_symbol, gensymed_symbol_2;

    x_note_fn_call(86,42);
    gensymed_symbol = IFIX(x_in_workspace);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    temp = FIX(gensymed_symbol - gensymed_symbol_2);
    gensymed_symbol = IFIX(y_in_workspace);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    return shift_block(block,temp,FIX(gensymed_symbol - gensymed_symbol_2));
}

/* SHIFT-FOR-BLOCK */
Object shift_for_block(block,delta_x,delta_y)
    Object block, delta_x, delta_y;
{
    Object new_left_qm, new_top_qm, new_right_qm, new_bottom_qm;
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(86,43);
    new_left_qm = Nil;
    new_top_qm = Nil;
    new_right_qm = Nil;
    new_bottom_qm = Nil;
    if ( !(IFIX(delta_x) == (SI_Long)0L)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(delta_x);
	new_left_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(delta_x);
	new_right_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    if ( !(IFIX(delta_y) == (SI_Long)0L)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(delta_y);
	new_top_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(delta_y);
	new_bottom_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    change_edges_of_block(block,new_left_qm,new_top_qm,new_right_qm,
	    new_bottom_qm);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(subblock,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
    gensymed_symbol_3 = subblock;
    gensymed_symbol_4 = delta_x;
    gensymed_symbol_5 = delta_y;
    inline_funcall_3(gensymed_symbol,gensymed_symbol_3,gensymed_symbol_4,
	    gensymed_symbol_5);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-BACKGROUND-IMAGES-INFO */
Object reclaim_background_images_info(images_info)
    Object images_info;
{
    Object image_info, ab_loop_list_;

    x_note_fn_call(86,44);
    image_info = Nil;
    ab_loop_list_ = images_info;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_frame_serial_number(SECOND(image_info));
    M_SECOND(image_info) = Nil;
    goto next_loop;
  end_loop:;
    return reclaim_slot_value_tree_1(images_info);
}

/* RECLAIM-WORKSPACE-PREVIOUS-BACKGROUND-IMAGES-INFO-VALUE */
Object reclaim_workspace_previous_background_images_info_value(images_info,
	    gensymed_symbol)
    Object images_info, gensymed_symbol;
{
    x_note_fn_call(86,45);
    reclaim_background_images_info(images_info);
    return VALUES_1(Nil);
}

/* RECLAIM-CHANGED-BLOCKS-OF-WORKSPACE-VALUE */
Object reclaim_changed_blocks_of_workspace_value(changed_blocks,
	    gensymed_symbol)
    Object changed_blocks, gensymed_symbol;
{
    x_note_fn_call(86,46);
    atomic_incff_symval(Qcount_of_pending_workspace_drawing,
	    FIXNUM_NEGATE(length(changed_blocks)));
    reclaim_slot_value_list_1(changed_blocks);
    return VALUES_1(Nil);
}

/* RECLAIM-INVALID-REGION-OF-WORKSPACE?-VALUE */
Object reclaim_invalid_region_of_workspace_qm_value(workspace_region,
	    gensymed_symbol)
    Object workspace_region, gensymed_symbol;
{
    x_note_fn_call(86,47);
    atomic_incff_symval(Qcount_of_pending_workspace_drawing,FIX( - 
	    (SI_Long)1L));
    reclaim_workspace_region(workspace_region);
    return VALUES_1(Nil);
}

static Object Qworkspace;          /* workspace */

static Object Qbackground_images;  /* background-images */

/* CLEANUP-FOR-WORKSPACE */
Object cleanup_for_workspace(workspace)
    Object workspace;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(86,48);
    frame = workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qworkspace)) {
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
    return change_slot_value(3,workspace,Qbackground_images,Nil);
}

/* PUT-STACK-OF-SUBBLOCKS-WHERE-SLOT-IS-ABSENT */
Object put_stack_of_subblocks_where_slot_is_absent(workspace,list_of_blocks)
    Object workspace, list_of_blocks;
{
    x_note_fn_call(86,49);
    reclaim_slot_value_list_1(list_of_blocks);
    return VALUES_1(Nil);
}

static Object Qworkspace_margin;   /* workspace-margin */

/* PUT-WORKSPACE-MARGIN */
Object put_workspace_margin(workspace,workspace_margin,initializing_qm)
    Object workspace, workspace_margin, initializing_qm;
{
    x_note_fn_call(86,50);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(workspace,Qworkspace_margin);
    SVREF(workspace,FIX((SI_Long)17L)) = workspace_margin;
    if ( !TRUEP(initializing_qm))
	change_workspace_edges_after_margin_change(workspace);
    return VALUES_1(workspace_margin);
}

/* COMPILE-FRAME-STYLE-NAME?-FOR-SLOT */
Object compile_frame_style_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(86,51);
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
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* FRAME-STYLE-NAME?-EVALUATION-SETTER */
Object frame_style_name_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(86,52);
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
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
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
		      goto end_frame_style_name_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value)
	result = VALUES_1(evaluation_value);
    else
	result = VALUES_1(Qnone);
  end_frame_style_name_qm_evaluation_setter:
    return result;
}

/* FRAME-STYLE-NAME?-EVALUATION-GETTER */
Object frame_style_name_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(86,53);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qworkspace_background_color_qm;  /* workspace-background-color? */

/* PUT-NON-DEFAULT-BACKGROUND-COLOR-FOR-WORKSPACE?-WHERE-SLOT-IS-ABSENT */
Object put_non_default_background_color_for_workspace_qm_where_slot_is_absent(workspace,
	    color_qm)
    Object workspace, color_qm;
{
    x_note_fn_call(86,54);
    if (color_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qworkspace_background_color_qm);
	SVREF(workspace,FIX((SI_Long)21L)) = color_qm;
    }
    return VALUES_1(Nil);
}

static Object Qworkspace_foreground_color_qm;  /* workspace-foreground-color? */

/* PUT-NON-DEFAULT-FOREGROUND-COLOR-FOR-WORKSPACE?-WHERE-SLOT-IS-ABSENT */
Object put_non_default_foreground_color_for_workspace_qm_where_slot_is_absent(workspace,
	    color_qm)
    Object workspace, color_qm;
{
    x_note_fn_call(86,55);
    if (color_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qworkspace_foreground_color_qm);
	SVREF(workspace,FIX((SI_Long)22L)) = color_qm;
    }
    return VALUES_1(Nil);
}

/* PUT-WORKBLOCK-MARGIN-WHERE-SLOT-IS-ABSENT */
Object put_workblock_margin_where_slot_is_absent(workspace,workspace_margin)
    Object workspace, workspace_margin;
{
    x_note_fn_call(86,56);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(workspace,Qworkspace_margin);
    SVREF(workspace,FIX((SI_Long)17L)) = workspace_margin;
    return VALUES_1(Nil);
}

/* RECLAIM-ONLY-WORKSTATION-THIS-NON-KB-WORKSPACE-CAN-BE-ON?-VALUE */
Object reclaim_only_workstation_this_non_kb_workspace_can_be_on_qm_value(workstation_qm,
	    non_kb_workspace)
    Object workstation_qm, non_kb_workspace;
{
    Object svref_new_value;

    x_note_fn_call(86,57);
    if (workstation_qm) {
	svref_new_value = delete_gensym_element_1(non_kb_workspace,
		ISVREF(workstation_qm,(SI_Long)32L));
	SVREF(workstation_qm,FIX((SI_Long)32L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* WORKSPACE-CAN-APPEAR-ON-WORKSTATION-P */
Object workspace_can_appear_on_workstation_p(workspace,workstation)
    Object workspace, workstation;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(86,58);
    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Non_kb_workspace_class_description,(SI_Long)18L));
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
    temp_1 =  !temp ? T : Nil;
    if (temp_1);
    else
	temp_1 =  !TRUEP(ISVREF(workspace,(SI_Long)27L)) ? T : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(EQ(ISVREF(workspace,(SI_Long)27L),workstation) ? T 
		: Nil);
}

/* GET-WORKSPACE-IF-ANY */
Object get_workspace_if_any(block)
    Object block;
{
    Object this_block, superblock_qm, gensymed_symbol, sub_class_bit_vector;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(86,59);
    this_block = block;
    superblock_qm = Nil;
  next_loop:
    gensymed_symbol = ACCESS_ONCE(ISVREF(this_block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_qm = gensymed_symbol;
    if ( !TRUEP(superblock_qm)) {
	sub_class_bit_vector = ISVREF(ISVREF(this_block,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	temp_1 = temp ? this_block : Nil;
	goto end_1;
    }
    this_block = superblock_qm;
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_image_plane_per_window, Qworkspace_image_plane_per_window);

DEFINE_VARIABLE_WITH_SYMBOL(Image_plane_is_obscured_p, Qimage_plane_is_obscured_p);

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* MAKE-WORKSPACE */
Object make_workspace varargs_1(int, n)
{
    Object class_1;
    Object name_qm, initial_subblock_qm, non_default_margin_qm;
    Object minimum_initial_width_qm, minimum_initial_height_qm;
    Object only_workstation_workspace_can_be_on_qm, workspace, temp;
    Object sub_class_bit_vector, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object gensymed_symbol_3, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, delta_x, delta_y;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(86,60);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    initial_subblock_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    non_default_margin_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    minimum_initial_width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    minimum_initial_height_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    only_workstation_workspace_can_be_on_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    workspace = make_frame(class_1);
    if (non_default_margin_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qworkspace_margin);
	SVREF(workspace,FIX((SI_Long)17L)) = non_default_margin_qm;
    }
    change_edges_of_block(workspace,minimum_initial_width_qm ? FIX( - 
	    (IFIX(minimum_initial_width_qm) >>  -  - (SI_Long)1L)) : 
	    FIX((SI_Long)0L),minimum_initial_height_qm ? FIX( - 
	    (IFIX(minimum_initial_height_qm) >>  -  - (SI_Long)1L)) : 
	    FIX((SI_Long)0L),minimum_initial_width_qm ? 
	    FIX(IFIX(minimum_initial_width_qm) +  - 
	    (IFIX(minimum_initial_width_qm) >>  -  - (SI_Long)1L)) : 
	    FIX((SI_Long)0L),minimum_initial_height_qm ? 
	    FIX(IFIX(minimum_initial_height_qm) +  - 
	    (IFIX(minimum_initial_height_qm) >>  -  - (SI_Long)1L)) : 
	    FIX((SI_Long)0L));
    if (EQ(only_workstation_workspace_can_be_on_qm,FIX((SI_Long)-1L))) {
	temp = Image_plane_is_obscured_p;
	M_SECOND(temp) = Nil;
    }
    else {
	if (only_workstation_workspace_can_be_on_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Non_kb_workspace_class_description,
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
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensym_push_modify_macro_arg = workspace;
	    car_1 = gensym_push_modify_macro_arg;
	    cdr_1 = ISVREF(only_workstation_workspace_can_be_on_qm,
		    (SI_Long)32L);
	    temp = gensym_cons_1(car_1,cdr_1);
	    SVREF(only_workstation_workspace_can_be_on_qm,
		    FIX((SI_Long)32L)) = temp;
	    ISVREF(workspace,(SI_Long)27L) = 
		    only_workstation_workspace_can_be_on_qm;
	}
    }
    if (initial_subblock_qm) {
	gensymed_symbol_3 = ISVREF(initial_subblock_qm,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol = IFIX(gensymed_symbol_3);
	gensymed_symbol_3 = ISVREF(initial_subblock_qm,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol_3);
	gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol = gensymed_symbol >>  -  - gensymed_symbol_1;
	delta_x =  - gensymed_symbol;
	gensymed_symbol_3 = ISVREF(initial_subblock_qm,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol = IFIX(gensymed_symbol_3);
	gensymed_symbol_3 = ISVREF(initial_subblock_qm,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol_3);
	gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol = gensymed_symbol >>  -  - gensymed_symbol_1;
	delta_y =  - gensymed_symbol;
	gensymed_symbol_3 = 
		ISVREF(ISVREF(ISVREF(ISVREF(initial_subblock_qm,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	gensymed_symbol_4 = initial_subblock_qm;
	gensymed_symbol = delta_x;
	gensymed_symbol_1 = delta_y;
	inline_funcall_3(gensymed_symbol_3,gensymed_symbol_4,
		FIX(gensymed_symbol),FIX(gensymed_symbol_1));
	add_subblock(initial_subblock_qm,workspace);
	enlarge_workspace_for_block_and_subblocks_as_necessary(initial_subblock_qm,
		workspace);
	add_loose_ends_as_subblocks_and_shift(initial_subblock_qm,
		workspace,FIX(delta_x),FIX(delta_y));
	sub_class_bit_vector = ISVREF(ISVREF(initial_subblock_qm,
		(SI_Long)1L),(SI_Long)19L);
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    update_name_box(initial_subblock_qm);
    }
    else
	enlarge_workspace_if_necessary(5,workspace,FIX((SI_Long)0L),
		FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)0L));
    if (name_qm)
	change_slot_value(3,workspace,Qname_or_names_for_frame,name_qm);
    return VALUES_1(workspace);
}

/* ORPHAN-WORKSPACE-P */
Object orphan_workspace_p(workspace)
    Object workspace;
{
    Object gensymed_symbol, subblocks;

    x_note_fn_call(86,61);
    if ( !TRUEP(get_lookup_slot_value_given_default(workspace,
	    Qname_or_names_for_frame,Nil)) &&  !TRUEP(ISVREF(workspace,
	    (SI_Long)18L)) &&  
	    !TRUEP(workspace_showing_p_function(workspace,Nil))) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	return VALUES_1( !(subblocks &&  ! 
		!TRUEP(constant_queue_next(ISVREF(subblocks,(SI_Long)2L),
		subblocks))) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Known_view_preferences = UNBOUND;

/* GET-VIEW-PREFERENCE */
Object get_view_preference(plist,indicator)
    Object plist, indicator;
{
    x_note_fn_call(86,62);
    return getf(plist,indicator,_);
}

/* SET-VIEW-PREFERENCE-1 */
Object set_view_preference_1(plist,indicator,value)
    Object plist, indicator, value;
{
    Object head, property_1, value_1, temp, previous_cons, rest_1;

    x_note_fn_call(86,63);
    if (value) {
	head = plist;
	property_1 = Nil;
	value_1 = Nil;
      next_loop:
	if ( !TRUEP(head))
	    goto end_loop;
	property_1 = CAR(head);
	temp = CDR(head);
	value_1 = CAR(temp);
	if (EQ(property_1,indicator)) {
	    M_CADR(head) = value;
	    return VALUES_1(plist);
	}
	head = CDDR(head);
	goto next_loop;
      end_loop:
	return slot_value_cons_1(indicator,slot_value_cons_1(value,plist));
	return VALUES_1(Qnil);
    }
    else {
	previous_cons = Nil;
	head = plist;
	property_1 = Nil;
	value_1 = Nil;
	rest_1 = Nil;
      next_loop_1:
	if ( !TRUEP(head))
	    goto end_loop_1;
	property_1 = CAR(head);
	temp = CDR(head);
	value_1 = CAR(temp);
	temp = CDR(head);
	rest_1 = CDR(temp);
	if (EQ(property_1,indicator)) {
	    if (previous_cons)
		M_CDR(previous_cons) = rest_1;
	    reclaim_slot_value_cons_1(CDR(head));
	    reclaim_slot_value_cons_1(head);
	    if (previous_cons)
		return VALUES_1(plist);
	    else
		return VALUES_1(rest_1);
	}
	previous_cons = CDR(head);
	head = CDDR(head);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(plist);
	return VALUES_1(Qnil);
    }
}

void frames4_INIT()
{
    Object temp, temp_1, temp_2, frame_style_name_qm_evaluation_setter_1;
    Object frame_style_name_qm_evaluation_getter_1, sublist, key;
    Object list_constant_18, list_constant_17, Qtruth_value, Qvisible_grid;
    Object list_constant_16, list_constant_15, AB_package, Qvisible;
    Object list_constant_14, list_constant_13, Qunselectable, list_constant_12;
    Object list_constant_11, Qfixed_size, list_constant_10, list_constant_9;
    Object Qsize, Qfixed, Qtemporary_workspace, string_constant_30;
    Object list_constant_8, string_constant_3, string_constant_5;
    Object Qnon_kb_workspace, Qslot_value_reclaimer;
    Object Qreclaim_only_workstation_this_non_kb_workspace_can_be_on_qm_value;
    Object Qonly_workstation_this_non_kb_workspace_can_be_on_qm;
    Object string_constant_29, list_constant_7, string_constant_28;
    Object Qabsent_slot_putter, Qput_workblock_margin_where_slot_is_absent;
    Object Qworkblock_margin, Qsubstitute_class_and_kb_flags, Qworkblock;
    Object Qput_non_default_foreground_color_for_workspace_qm_where_slot_is_absent;
    Object Qnon_default_foreground_color_for_workspace_qm;
    Object Qput_non_default_background_color_for_workspace_qm_where_slot_is_absent;
    Object Qnon_default_background_color_for_workspace_qm;
    Object Qwrite_symbol_from_slot, Qframe_style_name_qm, Qframe_style_name;
    Object Qnamed, Qtype_specification_simple_expansion, list_constant_6;
    Object Qab_or, Qno_item, Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_frame_style_name_qm_for_slot;
    Object string_constant_27, string_constant_26, Qslot_putter;
    Object Qput_workspace_margin, Qput_stack_of_subblocks_where_slot_is_absent;
    Object Qstack_of_subblocks, Qclasses_which_define, Qcleanup;
    Object Qcleanup_for_workspace;
    Object Qreclaim_invalid_region_of_workspace_qm_value;
    Object Qinvalid_region_of_workspace_qm;
    Object Qreclaim_changed_blocks_of_workspace_value;
    Object Qchanged_blocks_of_workspace;
    Object Qreclaim_workspace_previous_background_images_info_value;
    Object Qworkspace_previous_background_images_info, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object list_constant_5, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_11;
    Object string_constant_10, string_constant_9, string_constant_8;
    Object string_constant_7, string_constant_6, Qshift, Qshift_for_block;
    Object Qgeneric_method_lambda_list, list_constant_4, Qdelta_y, Qdelta_x;
    Object Qreclaim_slot_group_for_block_qm_value, list_constant_3;
    Object Qcopy_frame, Qdependent_frame, string_constant_4, list_constant_2;
    Object Qkb_frame, Qreclaim_menus_for_this_value;
    Object Qput_kb_state_changes_previous_cons_qm;
    Object Qreclaim_kb_state_changes_previous_cons_qm_value;
    Object Qput_original_kb_state_plist, Qframes4;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qput_bottom_edge_of_content_of_block_1_where_slot_is_absent;
    Object Qbottom_edge_of_content_of_block_1;
    Object Qput_right_edge_of_content_of_block_1_where_slot_is_absent;
    Object Qright_edge_of_content_of_block_1;
    Object Qput_top_edge_of_content_of_block_1_where_slot_is_absent;
    Object Qtop_edge_of_content_of_block_1;
    Object Qput_left_edge_of_content_of_block_1_where_slot_is_absent;
    Object Qleft_edge_of_content_of_block_1;
    Object Qput_connections_where_slot_is_absent, Qconnections;
    Object Qput_subblocks_where_slot_is_absent, Qsubblocks;

    x_note_fn_call(86,64);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    Absent_slot_putter_prop = Qabsent_slot_putter;
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qsubblocks = STATIC_SYMBOL("SUBBLOCKS",AB_package);
    Qput_subblocks_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SUBBLOCKS-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_subblocks_where_slot_is_absent,
	    STATIC_FUNCTION(put_subblocks_where_slot_is_absent,NIL,FALSE,2,2));
    mutate_global_property(Qsubblocks,
	    SYMBOL_FUNCTION(Qput_subblocks_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qconnections = STATIC_SYMBOL("CONNECTIONS",AB_package);
    Qput_connections_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CONNECTIONS-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_connections_where_slot_is_absent,
	    STATIC_FUNCTION(put_connections_where_slot_is_absent,NIL,FALSE,
	    2,2));
    mutate_global_property(Qconnections,
	    SYMBOL_FUNCTION(Qput_connections_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qleft_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("LEFT-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qput_left_edge_of_content_of_block_1_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-LEFT-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_left_edge_of_content_of_block_1_where_slot_is_absent,
	    STATIC_FUNCTION(put_left_edge_of_content_of_block_1_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qleft_edge_of_content_of_block_1,
	    SYMBOL_FUNCTION(Qput_left_edge_of_content_of_block_1_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qtop_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("TOP-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qput_top_edge_of_content_of_block_1_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-TOP-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_top_edge_of_content_of_block_1_where_slot_is_absent,
	    STATIC_FUNCTION(put_top_edge_of_content_of_block_1_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtop_edge_of_content_of_block_1,
	    SYMBOL_FUNCTION(Qput_top_edge_of_content_of_block_1_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qright_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("RIGHT-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qput_right_edge_of_content_of_block_1_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-RIGHT-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_right_edge_of_content_of_block_1_where_slot_is_absent,
	    STATIC_FUNCTION(put_right_edge_of_content_of_block_1_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qright_edge_of_content_of_block_1,
	    SYMBOL_FUNCTION(Qput_right_edge_of_content_of_block_1_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qbottom_edge_of_content_of_block_1 = 
	    STATIC_SYMBOL("BOTTOM-EDGE-OF-CONTENT-OF-BLOCK-1",AB_package);
    Qput_bottom_edge_of_content_of_block_1_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-BOTTOM-EDGE-OF-CONTENT-OF-BLOCK-1-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_bottom_edge_of_content_of_block_1_where_slot_is_absent,
	    STATIC_FUNCTION(put_bottom_edge_of_content_of_block_1_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qbottom_edge_of_content_of_block_1,
	    SYMBOL_FUNCTION(Qput_bottom_edge_of_content_of_block_1_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    Substitute_class_and_kb_flags_prop = Qsubstitute_class_and_kb_flags;
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    string_constant = STATIC_STRING("~(~a::~a~)");
    string_constant_1 = STATIC_STRING("~(~a~)");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    if (Gathering_normally_editable_slots_for_search_qm == UNBOUND)
	Gathering_normally_editable_slots_for_search_qm = Nil;
    Qnot_user_editable = STATIC_SYMBOL("NOT-USER-EDITABLE",AB_package);
    Qfree = STATIC_SYMBOL("FREE",AB_package);
    Qfree_text_attribute = STATIC_SYMBOL("FREE-TEXT-ATTRIBUTE",AB_package);
    Qprocedure_definition = STATIC_SYMBOL("PROCEDURE-DEFINITION",AB_package);
    Qselect_changes = STATIC_SYMBOL("SELECT-CHANGES",AB_package);
    Qedit_attribute = STATIC_SYMBOL("EDIT-ATTRIBUTE",AB_package);
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    Slot_value_compiler_prop = Qslot_value_compiler;
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    Use_slot_value_compiler_for_default_overrides_p_prop = 
	    Quse_slot_value_compiler_for_default_overrides_p;
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    Slot_value_writer_prop = Qslot_value_writer;
    Qleave_text_representation_as_a_single_line_qm = 
	    STATIC_SYMBOL("LEAVE-TEXT-REPRESENTATION-AS-A-SINGLE-LINE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleave_text_representation_as_a_single_line_qm,
	    Leave_text_representation_as_a_single_line_qm);
    Qframes4 = STATIC_SYMBOL("FRAMES4",AB_package);
    record_system_variable(Qleave_text_representation_as_a_single_line_qm,
	    Qframes4,Nil,Qnil,Qnil,Qnil,Qnil);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_2 = STATIC_STRING("[deleted attribute]");
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qitem_position = STATIC_SYMBOL("ITEM-POSITION",AB_package);
    Qicon_position = STATIC_SYMBOL("ICON-POSITION",AB_package);
    Qoriginal_kb_state_plist = STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST",
	    AB_package);
    Qput_original_kb_state_plist = 
	    STATIC_SYMBOL("PUT-ORIGINAL-KB-STATE-PLIST",AB_package);
    SET_SYMBOL_FUNCTION(Qput_original_kb_state_plist,
	    STATIC_FUNCTION(put_original_kb_state_plist,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qoriginal_kb_state_plist,
	    SYMBOL_FUNCTION(Qput_original_kb_state_plist),Qslot_putter);
    Qkb_state_changes_previous_cons_qm = 
	    STATIC_SYMBOL("KB-STATE-CHANGES-PREVIOUS-CONS\?",AB_package);
    Qreclaim_kb_state_changes_previous_cons_qm_value = 
	    STATIC_SYMBOL("RECLAIM-KB-STATE-CHANGES-PREVIOUS-CONS\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_kb_state_changes_previous_cons_qm_value,
	    STATIC_FUNCTION(reclaim_kb_state_changes_previous_cons_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qkb_state_changes_previous_cons_qm,
	    SYMBOL_FUNCTION(Qreclaim_kb_state_changes_previous_cons_qm_value),
	    Qslot_value_reclaimer);
    Qput_kb_state_changes_previous_cons_qm = 
	    STATIC_SYMBOL("PUT-KB-STATE-CHANGES-PREVIOUS-CONS\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_state_changes_previous_cons_qm,
	    STATIC_FUNCTION(put_kb_state_changes_previous_cons_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qkb_state_changes_previous_cons_qm,
	    SYMBOL_FUNCTION(Qput_kb_state_changes_previous_cons_qm),
	    Qslot_putter);
    Qwhat_this_is_a_menu_for_qm = 
	    STATIC_SYMBOL("WHAT-THIS-IS-A-MENU-FOR\?",AB_package);
    Qmenus_for_this = STATIC_SYMBOL("MENUS-FOR-THIS",AB_package);
    Qreclaim_menus_for_this_value = 
	    STATIC_SYMBOL("RECLAIM-MENUS-FOR-THIS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_menus_for_this_value,
	    STATIC_FUNCTION(reclaim_menus_for_this_value,NIL,FALSE,2,2));
    mutate_global_property(Qmenus_for_this,
	    SYMBOL_FUNCTION(Qreclaim_menus_for_this_value),
	    Qslot_value_reclaimer);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    list_constant_2 = STATIC_CONS(Qkb_frame,Qnil);
    check_if_superior_classes_are_defined(Qdependent_frame,list_constant_2);
    string_constant_3 = STATIC_STRING("0");
    string_constant_4 = STATIC_STRING("1m8q1m83=fy1l839Cy");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(string_constant_3);
    add_class_to_environment(9,Qdependent_frame,list_constant_2,Nil,temp,
	    Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_4),Nil);
    Dependent_frame_class_description = 
	    lookup_global_or_kb_specific_property_value(Qdependent_frame,
	    Class_description_gkbprop);
    Qcopy_frame = STATIC_SYMBOL("COPY-FRAME",AB_package);
    list_constant_3 = STATIC_CONS(Qdependent_frame,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qcopy_frame,list_constant_3,
	    Qgeneric_method_lambda_list);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qreclaim_slot_group_for_block_qm_value = 
	    STATIC_SYMBOL("RECLAIM-SLOT-GROUP-FOR-BLOCK\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_slot_group_for_block_qm_value,
	    STATIC_FUNCTION(reclaim_slot_group_for_block_qm_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qslot_group_for_block_qm,
	    SYMBOL_FUNCTION(Qreclaim_slot_group_for_block_qm_value),
	    Qslot_value_reclaimer);
    Qshift = STATIC_SYMBOL("SHIFT",AB_package);
    Qdelta_x = STATIC_SYMBOL("DELTA-X",AB_package);
    Qdelta_y = STATIC_SYMBOL("DELTA-Y",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qblock,Qdelta_x,Qdelta_y);
    mutate_global_property(Qshift,list_constant_4,Qgeneric_method_lambda_list);
    Qshift_for_block = STATIC_SYMBOL("SHIFT-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qshift_for_block,STATIC_FUNCTION(shift_for_block,
	    NIL,FALSE,3,3));
    temp_2 = SYMBOL_FUNCTION(Qshift_for_block);
    set_get(Qblock,Qshift,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qshift),
	    Qclasses_which_define);
    temp_2 = CONS(Qblock,temp);
    mutate_global_property(Qshift,temp_2,Qclasses_which_define);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    list_constant_5 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qworkspace,list_constant_5);
    string_constant_5 = STATIC_STRING("1l1l8t");
    string_constant_6 = 
	    STATIC_STRING("13Ky4z8r83S=y83S=y83*qy83*qy00001m1l8l1l8o000004z8r83*Ly83*Ly83*qy83*qy03Qy001n1l8l1l8o1m8p83*7y000004z8r83Xby83Xby83*qy83*qy000");
    string_constant_7 = 
	    STATIC_STRING("01o1l8l1l8o1l83Cy1l83Uy000004z8r83Xny83Xny83*qy83*qy00001n1l8l1l8o1l83Cy000004z8r83Wpy83Wpy83*qy83*qy0k001m1l8l1l8o000004z8r83Wb");
    string_constant_8 = 
	    STATIC_STRING("y83Wby83*qy83*qy0k001m1l8l1l83Ey000004z8r834sy834sy83*qy83*qy00001n1l8l1l8o1l83Cy000004z8r834ty834ty83*qy83*qy00001n1l8l1l8o1l83");
    string_constant_9 = 
	    STATIC_STRING("Cy000004z8r83Sly83Sly83*qy83*qy00001m1l8l1l8o000004z8r83Hky83Hky83*qy83*qy00001m1l8l1l8o000004z8r83eay83eay83*qy83*qy00001m1l8l1");
    string_constant_10 = 
	    STATIC_STRING("l83Ey000004z8r83eTy83eTy83*qy83*qy00001m1l8l1l83Ey000004z8r83eVy83eVy83*qy83*qy00001m1l8l1l83Ey000004z8r833gy833gy83*qy83*qy0000");
    string_constant_11 = 
	    STATIC_STRING("1m1l8l1m8p833gy000004z8r8340y8340y83*qy83*qy00001m1l8l1m8p8337y000004z8r83c8y83c8y83*qy83*qy00001n1l8l1m8p83Gy1l83Ny000004z8r836");
    string_constant_12 = 
	    STATIC_STRING("Hy836Hy83*qy83*qy00001n1l8l1m8p83Ky1l83Ny000004z8r834ky834ky83*qy83*qy00001m1l8l1m8p833cy000004z8r83eZy83eZy83*qy83*qy00001l1l8l");
    string_constant_13 = 
	    STATIC_STRING("000004z8r83eUy83eUy83*qy83*qy0k001m1l8l1l8o000004z8r83e=y83e=y83*qy83*qy00001o1l83Ey1l8l1l83Cy1m8p83e=y000004z8r83dXy83dXy83*qy8");
    string_constant_14 = 
	    STATIC_STRING("3*qy00001n1l83Ey1l8l1l83Cy000004z8r83Y*y83Y*y83*qy83*qy00001o1l83Ey1l8l1l83Cy1m8p83Ky000004z8r834Sy834Sy83*qy83*qy00001o1l8o1l8l");
    string_constant_15 = 
	    STATIC_STRING("1m8p834Sy1m83Dy532ByProprietary package exports as a symbol type: ~\n(member (proprietary non-proprietary potentially-proprietary");
    string_constant_16 = 
	    STATIC_STRING(")). However ~\nthe slot is only visible when package-preparation mode is on. The ~\nuser may change the value only from non-propri");
    string_constant_17 = 
	    STATIC_STRING("etary to potentially-proprietary, ~\nand only when package-preparation mode is on, Some special-casing would be ~\nnecessary to co");
    string_constant_18 = 
	    STATIC_STRING("nditionally export this attribute. 00000");
    string_constant_19 = 
	    STATIC_STRING("13My8q1n83*qy1l9k8t1o83S=y08l8o1p83*Ly3Qy8l8o1m8p83*7y1q83Xby08l8o83Cy83Uy1p83Xny08l8o83Cy1o83Wpyk8l8o1o83Wbyk8l83Ey1p834sy08l8o");
    string_constant_20 = 
	    STATIC_STRING("83Cy1p834ty08l8o83Cy1o83Sly08l8o1o83Hky08l8o1o83eay08l83Ey1o83eTy08l83Ey1o83eVy08l83Ey1n833gy01m8p833gy1n8340y01m8p8337y1p83c8y0");
    string_constant_21 = 
	    STATIC_STRING("8l1m8p83Gy83Ny1p836Hy08l1m8p83Ky83Ny1o834ky08l1m8p833cy1m83eZy01o83eUyk8l8o1q83e=y083Ey8l83Cy1m8p83e=y1p83dXy083Ey8l83Cy1q83Y*y0");
    string_constant_22 = 
	    STATIC_STRING("83Ey8l83Cy1m8p83Ky1q834Sy08o8l1m8p834Sy1m83Dy532ByProprietary package exports as a symbol type: ~\n(member (proprietary non-propr");
    string_constant_23 = 
	    STATIC_STRING("ietary potentially-proprietary)). However ~\nthe slot is only visible when package-preparation mode is on. The ~\nuser may change ");
    string_constant_24 = 
	    STATIC_STRING("the value only from non-proprietary to potentially-proprietary, ~\nand only when package-preparation mode is on, Some special-cas");
    string_constant_25 = 
	    STATIC_STRING("ing would be ~\nnecessary to conditionally export this attribute. ");
    temp = regenerate_optimized_constant(string_constant_5);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qworkspace,list_constant_5,Nil,temp,Nil,
	    temp_1,list_constant_5,regenerate_optimized_constant(list(7,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25)),Nil);
    Workspace_class_description = 
	    lookup_global_or_kb_specific_property_value(Qworkspace,
	    Class_description_gkbprop);
    Qworkspace_previous_background_images_info = 
	    STATIC_SYMBOL("WORKSPACE-PREVIOUS-BACKGROUND-IMAGES-INFO",
	    AB_package);
    Qreclaim_workspace_previous_background_images_info_value = 
	    STATIC_SYMBOL("RECLAIM-WORKSPACE-PREVIOUS-BACKGROUND-IMAGES-INFO-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_workspace_previous_background_images_info_value,
	    STATIC_FUNCTION(reclaim_workspace_previous_background_images_info_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qworkspace_previous_background_images_info,
	    SYMBOL_FUNCTION(Qreclaim_workspace_previous_background_images_info_value),
	    Qslot_value_reclaimer);
    Qcount_of_pending_workspace_drawing = 
	    STATIC_SYMBOL("COUNT-OF-PENDING-WORKSPACE-DRAWING",AB_package);
    Qchanged_blocks_of_workspace = 
	    STATIC_SYMBOL("CHANGED-BLOCKS-OF-WORKSPACE",AB_package);
    Qreclaim_changed_blocks_of_workspace_value = 
	    STATIC_SYMBOL("RECLAIM-CHANGED-BLOCKS-OF-WORKSPACE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_changed_blocks_of_workspace_value,
	    STATIC_FUNCTION(reclaim_changed_blocks_of_workspace_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qchanged_blocks_of_workspace,
	    SYMBOL_FUNCTION(Qreclaim_changed_blocks_of_workspace_value),
	    Qslot_value_reclaimer);
    Qinvalid_region_of_workspace_qm = 
	    STATIC_SYMBOL("INVALID-REGION-OF-WORKSPACE\?",AB_package);
    Qreclaim_invalid_region_of_workspace_qm_value = 
	    STATIC_SYMBOL("RECLAIM-INVALID-REGION-OF-WORKSPACE\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_invalid_region_of_workspace_qm_value,
	    STATIC_FUNCTION(reclaim_invalid_region_of_workspace_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinvalid_region_of_workspace_qm,
	    SYMBOL_FUNCTION(Qreclaim_invalid_region_of_workspace_qm_value),
	    Qslot_value_reclaimer);
    Qbackground_images = STATIC_SYMBOL("BACKGROUND-IMAGES",AB_package);
    Qcleanup_for_workspace = STATIC_SYMBOL("CLEANUP-FOR-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_workspace,
	    STATIC_FUNCTION(cleanup_for_workspace,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_workspace);
    set_get(Qworkspace,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qworkspace,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qstack_of_subblocks = STATIC_SYMBOL("STACK-OF-SUBBLOCKS",AB_package);
    Qput_stack_of_subblocks_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-STACK-OF-SUBBLOCKS-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_stack_of_subblocks_where_slot_is_absent,
	    STATIC_FUNCTION(put_stack_of_subblocks_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qstack_of_subblocks,
	    SYMBOL_FUNCTION(Qput_stack_of_subblocks_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qworkspace_margin = STATIC_SYMBOL("WORKSPACE-MARGIN",AB_package);
    Qput_workspace_margin = STATIC_SYMBOL("PUT-WORKSPACE-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qput_workspace_margin,
	    STATIC_FUNCTION(put_workspace_margin,NIL,FALSE,3,3));
    mutate_global_property(Qworkspace_margin,
	    SYMBOL_FUNCTION(Qput_workspace_margin),Qslot_putter);
    string_constant_26 = STATIC_STRING("1l1m83x+y83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_26));
    string_constant_27 = STATIC_STRING("1m1m8337y83x+y1m8337y1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_27));
    Qframe_style_name_qm = STATIC_SYMBOL("FRAME-STYLE-NAME\?",AB_package);
    Qcompile_frame_style_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-FRAME-STYLE-NAME\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_frame_style_name_qm_for_slot,
	    STATIC_FUNCTION(compile_frame_style_name_qm_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qframe_style_name_qm,
	    SYMBOL_FUNCTION(Qcompile_frame_style_name_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qframe_style_name_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_6 = STATIC_CONS(Qno_item,Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_6,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qframe_style_name_qm),
	    Qtype_specification_simple_expansion,list_constant_1);
    define_type_specification_explicit_complex_type(Qframe_style_name_qm,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qframe_style_name_qm);
    frame_style_name_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(frame_style_name_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qframe_style_name_qm,
	    frame_style_name_qm_evaluation_setter_1);
    frame_style_name_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(frame_style_name_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qframe_style_name_qm,
	    frame_style_name_qm_evaluation_getter_1);
    Qframe_style_name = STATIC_SYMBOL("FRAME-STYLE-NAME",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_symbol_from_slot,
	    STATIC_FUNCTION(write_symbol_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qframe_style_name,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    mutate_global_property(Qframe_style_name_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qnon_default_background_color_for_workspace_qm = 
	    STATIC_SYMBOL("NON-DEFAULT-BACKGROUND-COLOR-FOR-WORKSPACE\?",
	    AB_package);
    Qput_non_default_background_color_for_workspace_qm_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-NON-DEFAULT-BACKGROUND-COLOR-FOR-WORKSPACE\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_non_default_background_color_for_workspace_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_non_default_background_color_for_workspace_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnon_default_background_color_for_workspace_qm,
	    SYMBOL_FUNCTION(Qput_non_default_background_color_for_workspace_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qworkspace_foreground_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-FOREGROUND-COLOR\?",AB_package);
    Qnon_default_foreground_color_for_workspace_qm = 
	    STATIC_SYMBOL("NON-DEFAULT-FOREGROUND-COLOR-FOR-WORKSPACE\?",
	    AB_package);
    Qput_non_default_foreground_color_for_workspace_qm_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-NON-DEFAULT-FOREGROUND-COLOR-FOR-WORKSPACE\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_non_default_foreground_color_for_workspace_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_non_default_foreground_color_for_workspace_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnon_default_foreground_color_for_workspace_qm,
	    SYMBOL_FUNCTION(Qput_non_default_foreground_color_for_workspace_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qworkblock = STATIC_SYMBOL("WORKBLOCK",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qworkblock,CONS(Qworkspace,temp),
	    Qsubstitute_class_and_kb_flags);
    Qworkblock_margin = STATIC_SYMBOL("WORKBLOCK-MARGIN",AB_package);
    Qput_workblock_margin_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-WORKBLOCK-MARGIN-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_workblock_margin_where_slot_is_absent,
	    STATIC_FUNCTION(put_workblock_margin_where_slot_is_absent,NIL,
	    FALSE,2,2));
    mutate_global_property(Qworkblock_margin,
	    SYMBOL_FUNCTION(Qput_workblock_margin_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qnon_kb_workspace = STATIC_SYMBOL("NON-KB-WORKSPACE",AB_package);
    list_constant_7 = STATIC_CONS(Qworkspace,Qnil);
    check_if_superior_classes_are_defined(Qnon_kb_workspace,list_constant_7);
    string_constant_28 = 
	    STATIC_STRING("1l4z8r83XEy83XEy832Ay832Ay00001m1l8l1l8o00000");
    string_constant_29 = STATIC_STRING("1n8q1n832Ay1l83*qy8t1o83XEy08l8o");
    temp = regenerate_optimized_constant(string_constant_5);
    temp_1 = regenerate_optimized_constant(string_constant_28);
    add_class_to_environment(9,Qnon_kb_workspace,list_constant_7,Nil,temp,
	    Nil,temp_1,list_constant_7,
	    regenerate_optimized_constant(string_constant_29),Nil);
    Non_kb_workspace_class_description = 
	    lookup_global_or_kb_specific_property_value(Qnon_kb_workspace,
	    Class_description_gkbprop);
    Qonly_workstation_this_non_kb_workspace_can_be_on_qm = 
	    STATIC_SYMBOL("ONLY-WORKSTATION-THIS-NON-KB-WORKSPACE-CAN-BE-ON\?",
	    AB_package);
    Qreclaim_only_workstation_this_non_kb_workspace_can_be_on_qm_value = 
	    STATIC_SYMBOL("RECLAIM-ONLY-WORKSTATION-THIS-NON-KB-WORKSPACE-CAN-BE-ON\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_only_workstation_this_non_kb_workspace_can_be_on_qm_value,
	    STATIC_FUNCTION(reclaim_only_workstation_this_non_kb_workspace_can_be_on_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qonly_workstation_this_non_kb_workspace_can_be_on_qm,
	    SYMBOL_FUNCTION(Qreclaim_only_workstation_this_non_kb_workspace_can_be_on_qm_value),
	    Qslot_value_reclaimer);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    list_constant_8 = STATIC_CONS(Qnon_kb_workspace,Qnil);
    check_if_superior_classes_are_defined(Qtemporary_workspace,
	    list_constant_8);
    string_constant_30 = STATIC_STRING("1m8q1n8318y1l832Ay8t");
    temp = regenerate_optimized_constant(string_constant_5);
    temp_1 = regenerate_optimized_constant(string_constant_3);
    add_class_to_environment(9,Qtemporary_workspace,list_constant_8,Nil,
	    temp,Nil,temp_1,list_constant_8,
	    regenerate_optimized_constant(string_constant_30),Nil);
    Temporary_workspace_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtemporary_workspace,
	    Class_description_gkbprop);
    if (Workspace_image_plane_per_window == UNBOUND)
	Workspace_image_plane_per_window = LIST_2(Nil,Nil);
    if (Image_plane_is_obscured_p == UNBOUND) {
	temp = CDR(Workspace_image_plane_per_window);
	Image_plane_is_obscured_p = CONS(Nil,temp);
    }
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Known_view_preferences = Nil;
    Qfixed_size = STATIC_SYMBOL("FIXED-SIZE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qfixed = STATIC_SYMBOL("FIXED",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qquote,Qfixed);
    Qsize = STATIC_SYMBOL("SIZE",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qquote,Qsize);
    list_constant_11 = STATIC_LIST((SI_Long)2L,list_constant_9,
	    list_constant_10);
    list_constant_12 = STATIC_CONS(Qfixed_size,Qt);
    sublist = Known_view_preferences;
    key = Nil;
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    temp = CAR(sublist);
    key = CAR(temp);
    temp = LIST_4(Qfixed_size,Qtruth_value,list_constant_11,list_constant_12);
    if (EQ(key,CAR(temp))) {
	temp_2 = LIST_4(Qfixed_size,Qtruth_value,list_constant_11,
		list_constant_12);
	M_CAR(sublist) = temp_2;
	goto end_1;
    }
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:
    temp = LIST_4(Qfixed_size,Qtruth_value,list_constant_11,list_constant_12);
    Known_view_preferences = CONS(temp,Known_view_preferences);
  end_1:;
    Qunselectable = STATIC_SYMBOL("UNSELECTABLE",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qquote,Qunselectable);
    list_constant_14 = STATIC_CONS(Qunselectable,Qt);
    sublist = Known_view_preferences;
    key = Nil;
  next_loop_1:
    if ( !TRUEP(sublist))
	goto end_loop_1;
    temp = CAR(sublist);
    key = CAR(temp);
    temp = LIST_4(Qunselectable,Qtruth_value,list_constant_13,
	    list_constant_14);
    if (EQ(key,CAR(temp))) {
	temp_2 = LIST_4(Qunselectable,Qtruth_value,list_constant_13,
		list_constant_14);
	M_CAR(sublist) = temp_2;
	goto end_2;
    }
    sublist = M_CDR(sublist);
    goto next_loop_1;
  end_loop_1:
    temp = LIST_4(Qunselectable,Qtruth_value,list_constant_13,
	    list_constant_14);
    Known_view_preferences = CONS(temp,Known_view_preferences);
  end_2:;
    Qvisible_grid = STATIC_SYMBOL("VISIBLE-GRID",AB_package);
    Qvisible = STATIC_SYMBOL("VISIBLE",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qquote,Qvisible);
    Qgrid = STATIC_SYMBOL("GRID",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qquote,Qgrid);
    list_constant_17 = STATIC_LIST((SI_Long)2L,list_constant_15,
	    list_constant_16);
    list_constant_18 = STATIC_CONS(Qvisible_grid,Qt);
    sublist = Known_view_preferences;
    key = Nil;
  next_loop_2:
    if ( !TRUEP(sublist))
	goto end_loop_2;
    temp = CAR(sublist);
    key = CAR(temp);
    temp = LIST_4(Qvisible_grid,Qtruth_value,list_constant_17,
	    list_constant_18);
    if (EQ(key,CAR(temp))) {
	temp_2 = LIST_4(Qvisible_grid,Qtruth_value,list_constant_17,
		list_constant_18);
	M_CAR(sublist) = temp_2;
	goto end_3;
    }
    sublist = M_CDR(sublist);
    goto next_loop_2;
  end_loop_2:
    temp = LIST_4(Qvisible_grid,Qtruth_value,list_constant_17,
	    list_constant_18);
    Known_view_preferences = CONS(temp,Known_view_preferences);
  end_3:;
}
