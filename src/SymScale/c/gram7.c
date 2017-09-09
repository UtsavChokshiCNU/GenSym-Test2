/* gram7.c
 * Input file:  grammar7.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram7.h"


static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qinference_engine;   /* inference-engine */

static Object Qcomputation;        /* computation */

static Object Qg2_simulator;       /* g2-simulator */

static Object Qsimulator_data_server;  /* simulator-data-server */

static Object Qg2_meter;           /* g2-meter */

static Object Qg2_meter_data_server;  /* g2-meter-data-server */

static Object Qgfi_data_server;    /* gfi-data-server */

static Object Qgsi_data_server;    /* gsi-data-server */

static Object Qreserved_word_p;    /* reserved-word-p */

/* DATA-SERVER-MAP-EVALUATION-SETTER */
Object data_server_map_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,0);
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
		      goto end_data_server_map_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qinference_engine))
	result = VALUES_1(Qcomputation);
    else if (EQ(evaluation_value,Qg2_simulator))
	result = VALUES_1(Qsimulator_data_server);
    else if (EQ(evaluation_value,Qg2_meter))
	result = VALUES_1(Qg2_meter_data_server);
    else if (EQ(evaluation_value,Qgfi_data_server))
	result = VALUES_1(Qgfi_data_server);
    else if (EQ(evaluation_value,Qgsi_data_server))
	result = VALUES_1(Qgsi_data_server);
    else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(evaluation_value),
	    Qreserved_word_p))
	result = VALUES_1(Qcomputation);
    else
	result = VALUES_1(evaluation_value);
  end_data_server_map_evaluation_setter:
    return result;
}

/* DATA-SERVER-MAP-EVALUATION-GETTER */
Object data_server_map_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(203,1);
    if (EQ(slot_value,Qcomputation))
	temp = Qinference_engine;
    else if (EQ(slot_value,Qsimulator_data_server))
	temp = Qg2_simulator;
    else if (EQ(slot_value,Qg2_meter_data_server))
	temp = Qg2_meter;
    else
	temp = slot_value;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qsc;                 /* \; */

/* COMPILE-DATA-SERVER-MAP-FOR-SLOT */
Object compile_data_server_map_for_slot varargs_1(int, n)
{
    Object parse_result, variable_or_definition, gensymed_symbol;
    Object form, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, cdr_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,2);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    variable_or_definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (ATOM(parse_result))
	return VALUES_1(parse_result);
    else if (EQ(CAR(parse_result),Qsc)) {
	form = Nil;
	ab_loop_list_ = CDR(parse_result);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	form = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = CDR(form);
	if (ATOM(temp)) {
	    temp = form;
	    cdr_new_value = phrase_cons(CDR(form),Nil);
	    M_CDR(form) = cdr_new_value;
	}
	else
	    temp = form;
	ab_loopvar__2 = phrase_cons(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else {
	temp = CDR(parse_result);
	if (ATOM(temp)) {
	    temp = parse_result;
	    cdr_new_value = phrase_cons(CDR(parse_result),Nil);
	    M_CDR(parse_result) = cdr_new_value;
	}
	else
	    temp = parse_result;
	return phrase_cons(temp,Nil);
    }
}

static Object string_constant;     /* "inference engine" */

static Object string_constant_1;   /* "G2 simulator" */

static Object string_constant_2;   /* "G2 meter" */

static Object string_constant_3;   /* "~(~a~)" */

static Object string_constant_4;   /* "~(if ~a use ~a~)" */

static Object string_constant_5;   /* " with " */

static Object string_constant_6;   /* ", " */

static Object string_constant_7;   /* ", and " */

static Object string_constant_8;   /* "; " */

/* WRITE-DATA-SERVER-MAP-FROM-SLOT */
Object write_data_server_map_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp, defined_pretty_name_qm, mode, server_name;
    Object rest_of_server_spec, more_qm, ab_loop_list_, item, more_items_qm;
    Object ab_loop_list__1;

    x_note_fn_call(203,3);
    if (EQ(value,Qcomputation))
	return twrite(string_constant);
    else if (EQ(value,Qsimulator_data_server))
	return twrite(string_constant_1);
    else if (EQ(value,Qg2_meter_data_server))
	return twrite(string_constant_2);
    else if (SYMBOLP(value)) {
	temp = assq_function(value,Data_server_pretty_name_alist);
	defined_pretty_name_qm = CDR(temp);
	if (defined_pretty_name_qm)
	    return twrite(defined_pretty_name_qm);
	else
	    return tformat(2,string_constant_3,value);
    }
    else {
	mode = Nil;
	server_name = Nil;
	rest_of_server_spec = Nil;
	more_qm = Nil;
	ab_loop_list_ = value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	temp = CAR(ab_loop_list_);
	mode = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	server_name = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	rest_of_server_spec = CDR(temp);
	more_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	tformat(3,string_constant_4,mode,server_name);
	if (rest_of_server_spec) {
	    twrite(string_constant_5);
	    item = Nil;
	    more_items_qm = Nil;
	    ab_loop_list__1 = rest_of_server_spec;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    item = CAR(ab_loop_list__1);
	    more_items_qm = CDR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    tformat(2,string_constant_3,item);
	    if (CDR(more_items_qm))
		twrite(string_constant_6);
	    else if (more_items_qm)
		twrite(string_constant_7);
	    goto next_loop_1;
	  end_loop_1:;
	}
	if (more_qm)
	    twrite(string_constant_8);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qinherited;          /* inherited */

/* COMPILE-COLOR-FOR-CLASS?-FOR-SLOT */
Object compile_color_for_class_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,4);
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
    if (EQ(parse_result,Qinherited))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* WRITE-COLOR-FOR-CLASS?-FROM-SLOT */
Object write_color_for_class_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,5);
    if (value)
	return twrite_color(value);
    else
	return twrite(Qinherited);
}

static Object Qblack;              /* black */

/* WRITE-COLOR-FROM-SLOT */
Object write_color_from_slot(color,gensymed_symbol)
    Object color, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(203,6);
    temp = color;
    if (temp);
    else
	temp = Qblack;
    return twrite_color(temp);
}

/* COMPILE-CLASS-DEFINITION-CHANGE-FOR-SLOT */
Object compile_class_definition_change_for_slot varargs_1(int, n)
{
    Object parse_result, definition, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,7);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_definition_changes(parse_result,definition);
}

/* COMPILE-OBJECT-CHANGE-FOR-SLOT */
Object compile_object_change_for_slot varargs_1(int, n)
{
    Object parse_result, definition, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,8);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_definition_changes(parse_result,definition);
}

/* COMPILE-CONNECTION-CHANGE-FOR-SLOT */
Object compile_connection_change_for_slot varargs_1(int, n)
{
    Object parse_result, definition, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,9);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_definition_changes(parse_result,definition);
}

/* COMPILE-MESSAGE-CHANGE-FOR-SLOT */
Object compile_message_change_for_slot varargs_1(int, n)
{
    Object parse_result, definition, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,10);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_definition_changes(parse_result,definition);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qnone;               /* none */

static Object Qmove_attribute;     /* move-attribute */

static Object Qcar_eq;             /* car-eq */

static Object string_constant_9;   /* "The attribute is not defined for this class" */

static Object string_constant_10;  /* "An attribute cannot be moved to the same class." */

static Object array_constant;      /* # */

static Object string_constant_11;  /* "The target class cannot be a system-defined class." */

static Object string_constant_12;  /* "The target class must be an inferior or superior class." */

static Object string_constant_13;  /* "The target class already has this attribute." */

static Object list_constant_2;     /* # */

static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

static Object Qicon_description;   /* icon-description */

static Object string_constant_14;  /* "The class defined by this definition cannot have connections." */

static Object Qcopy_inherited_icon_description;  /* copy-inherited-icon-description */

static Object string_constant_15;  /* "The class defined by this definition cannot have an icon." */

static Object Qupdate_definition_attribute;  /* update-definition-attribute */

static Object Qdefault_message_properties;  /* default-message-properties */

static Object string_constant_16;  /* "The class defined by this definition cannot have default message properties." */

static Object Qadd_attribute;      /* add-attribute */

static Object Qrename_attribute;   /* rename-attribute */

static Object string_constant_17;  /* "You cannot make changes to a class before it exists." */

/* COMPILE-DEFINITION-CHANGES */
Object compile_definition_changes(change_qm,definition)
    Object change_qm, definition;
{
    Object class_1, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp, temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, attribute_name, target_class;
    Object sub_class_bit_vector, superior, ab_loop_list_, ab_loop_it_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(203,11);
    class_1 = ISVREF(definition,(SI_Long)20L);
    if (SYMBOLP(class_1)) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if ( !TRUEP(change_qm))
	    return VALUES_1(Nil);
	else if (EQ(change_qm,Qnone))
	    return VALUES_1(Nil);
	else {
	    temp_1 = CAR(change_qm);
	    if (EQ(temp_1,Qmove_attribute)) {
		attribute_name = SECOND(change_qm);
		target_class = THIRD(change_qm);
		if ( !TRUEP(member(4,attribute_name,ISVREF(definition,
			(SI_Long)22L),Ktest,Qcar_eq))) {
		    temp = Bad_phrase;
		    temp_1 = copy_text_string(string_constant_9);
		    return VALUES_2(temp,temp_1);
		}
		else if (EQ(class_1,target_class)) {
		    temp = Bad_phrase;
		    temp_1 = copy_text_string(string_constant_10);
		    return VALUES_2(temp,temp_1);
		}
		else {
		    if (SYMBOLP(target_class)) {
			skip_list = CDR(Symbol_properties_table);
			key_value = target_class;
			key_hash_value = SXHASH_SYMBOL_1(target_class) & 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_13:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_14:
			if ( !TRUEP(marked))
			    goto end_loop_13;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_14;
		      end_loop_13:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = target_class;
			    temp = Symbol_properties_table;
			    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
				    & IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_1 = new_cons;
			    }
			    else
				gensymed_symbol_1 = Nil;
			    if ( !TRUEP(gensymed_symbol_1))
				gensymed_symbol_1 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_1) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_2 = new_cons;
			    }
			    else
				gensymed_symbol_2 = Nil;
			    if ( !TRUEP(gensymed_symbol_2))
				gensymed_symbol_2 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_2) = head;
			    M_CDR(gensymed_symbol_2) = tail;
			    inline_note_allocate_cons(gensymed_symbol_2,
				    Qlookup);
			    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			    inline_note_allocate_cons(gensymed_symbol_1,
				    Qlookup);
			    gensymed_symbol = set_skip_list_entry(temp,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp_1,gensymed_symbol_1);
			}
			global_properties = gensymed_symbol;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_16:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_17:
			if ( !TRUEP(marked))
			    goto end_loop_16;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_17;
		      end_loop_16:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_19:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_20:
			    if ( !TRUEP(marked))
				goto end_loop_19;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
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
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
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
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
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
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_23:
			    if ( !TRUEP(marked))
				goto end_loop_22;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
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
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			temp_2 = TRUEP(resulting_value);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if ( !temp_2) {
			temp = Bad_phrase;
			temp_1 = 
				copy_constant_wide_string_given_length(array_constant,
				FIX((SI_Long)33L));
			return VALUES_2(temp,temp_1);
		    }
		    else {
			if (lookup_global_or_kb_specific_property_value(target_class,
				Class_description_gkbprop)) {
			    temp_1 = 
				    lookup_global_or_kb_specific_property_value(target_class,
				    Class_definition_gkbprop);
			    temp_2 = CONSP(temp_1);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    temp = Bad_phrase;
			    temp_1 = copy_text_string(string_constant_11);
			    return VALUES_2(temp,temp_1);
			}
			else {
			    gensymed_symbol = 
				    lookup_global_or_kb_specific_property_value(class_1,
				    Class_description_gkbprop);
			    temp_2 = gensymed_symbol ? 
				    TRUEP(memq_function(target_class,
				    ISVREF(gensymed_symbol,(SI_Long)2L))) :
				     TRUEP(Nil);
			    if (temp_2);
			    else {
				gensymed_symbol = 
					lookup_global_or_kb_specific_property_value(target_class,
					Class_description_gkbprop);
				temp_2 = gensymed_symbol ? 
					TRUEP(memq_function(class_1,
					ISVREF(gensymed_symbol,
					(SI_Long)2L))) : TRUEP(Nil);
			    }
			    if ( !temp_2) {
				temp = Bad_phrase;
				temp_1 = copy_text_string(string_constant_12);
				return VALUES_2(temp,temp_1);
			    }
			    else if (member(4,attribute_name,
				    ISVREF(lookup_global_or_kb_specific_property_value(target_class,
				    Class_definition_gkbprop),
				    (SI_Long)22L),Ktest,Qcar_eq)) {
				temp = Bad_phrase;
				temp_1 = copy_text_string(string_constant_13);
				return VALUES_2(temp,temp_1);
			    }
			    else
				return VALUES_1(change_qm);
			}
		    }
		}
	    }
	    else if (member_eql(temp_1,list_constant_2)) {
		sub_class_bit_vector = ISVREF(ISVREF(definition,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    if (get_lookup_slot_value_given_default(definition,
			    Qclass_inheritance_path_of_definition,Nil)) {
			superior = Nil;
			ab_loop_list_ = ISVREF(definition,(SI_Long)21L);
			ab_loop_it_ = Nil;
		      next_loop_24:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_24;
			superior = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			skip_list = CDR(Symbol_properties_table);
			key_value = superior;
			key_hash_value = SXHASH_SYMBOL_1(superior) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_25:
			if (level < ab_loop_bind_)
			    goto end_loop_25;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_26:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_27:
			if ( !TRUEP(marked))
			    goto end_loop_26;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_27;
		      end_loop_26:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_9;
			goto next_loop_26;
		      end_loop_27:
		      end_9:
			level = level - (SI_Long)1L;
			goto next_loop_25;
		      end_loop_25:;
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = superior;
			    temp = Symbol_properties_table;
			    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
				    & IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_1 = new_cons;
			    }
			    else
				gensymed_symbol_1 = Nil;
			    if ( !TRUEP(gensymed_symbol_1))
				gensymed_symbol_1 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_1) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_2 = new_cons;
			    }
			    else
				gensymed_symbol_2 = Nil;
			    if ( !TRUEP(gensymed_symbol_2))
				gensymed_symbol_2 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_2) = head;
			    M_CDR(gensymed_symbol_2) = tail;
			    inline_note_allocate_cons(gensymed_symbol_2,
				    Qlookup);
			    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			    inline_note_allocate_cons(gensymed_symbol_1,
				    Qlookup);
			    gensymed_symbol = set_skip_list_entry(temp,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp_1,gensymed_symbol_1);
			}
			global_properties = gensymed_symbol;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
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
		      next_loop_28:
			if (level < ab_loop_bind_)
			    goto end_loop_28;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_29:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_30:
			if ( !TRUEP(marked))
			    goto end_loop_29;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_30;
		      end_loop_29:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_10;
			goto next_loop_29;
		      end_loop_30:
		      end_10:
			level = level - (SI_Long)1L;
			goto next_loop_28;
		      end_loop_28:;
			kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_31:
			    if (level < ab_loop_bind_)
				goto end_loop_31;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_32:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_33:
			    if ( !TRUEP(marked))
				goto end_loop_32;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_33;
			  end_loop_32:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_11;
			    goto next_loop_32;
			  end_loop_33:
			  end_11:
			    level = level - (SI_Long)1L;
			    goto next_loop_31;
			  end_loop_31:;
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
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
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_34:
			    if (level < ab_loop_bind_)
				goto end_loop_34;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_35:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_36:
			    if ( !TRUEP(marked))
				goto end_loop_35;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_36;
			  end_loop_35:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_12;
			    goto next_loop_35;
			  end_loop_36:
			  end_12:
			    level = level - (SI_Long)1L;
			    goto next_loop_34;
			  end_loop_34:;
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			gensymed_symbol = resulting_value;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Entity_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol_3 = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_4 = (SI_Long)1L;
				gensymed_symbol_5 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_4 = gensymed_symbol_4 << 
					gensymed_symbol_5;
				gensymed_symbol_3 = gensymed_symbol_3 & 
					gensymed_symbol_4;
				temp_2 = (SI_Long)0L < gensymed_symbol_3;
			    }
			    else
				temp_2 = TRUEP(Nil);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = superior;
			    key_hash_value = SXHASH_SYMBOL_1(superior) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_37:
			    if (level < ab_loop_bind_)
				goto end_loop_37;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_38:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_39:
			    if ( !TRUEP(marked))
				goto end_loop_38;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_39;
			  end_loop_38:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_13;
			    goto next_loop_38;
			  end_loop_39:
			  end_13:
			    level = level - (SI_Long)1L;
			    goto next_loop_37;
			  end_loop_37:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = superior;
				temp = Symbol_properties_table;
				temp_1 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = set_skip_list_entry(temp,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_1,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_40:
			    if (level < ab_loop_bind_)
				goto end_loop_40;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_41:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_42:
			    if ( !TRUEP(marked))
				goto end_loop_41;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_42;
			  end_loop_41:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_14;
			    goto next_loop_41;
			  end_loop_42:
			  end_14:
			    level = level - (SI_Long)1L;
			    goto next_loop_40;
			  end_loop_40:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_43:
				if (level < ab_loop_bind_)
				    goto end_loop_43;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_44:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_45:
				if ( !TRUEP(marked))
				    goto end_loop_44;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_45;
			      end_loop_44:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_15;
				goto next_loop_44;
			      end_loop_45:
			      end_15:
				level = level - (SI_Long)1L;
				goto next_loop_43;
			      end_loop_43:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_46:
				if (level < ab_loop_bind_)
				    goto end_loop_46;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_47:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_48:
				if ( !TRUEP(marked))
				    goto end_loop_47;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_48;
			      end_loop_47:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_16;
				goto next_loop_47;
			      end_loop_48:
			      end_16:
				level = level - (SI_Long)1L;
				goto next_loop_46;
			      end_loop_46:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Connection_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp_2 = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp_2 = TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    temp_2 =  !temp_2;
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = superior;
			    key_hash_value = SXHASH_SYMBOL_1(superior) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_49:
			    if (level < ab_loop_bind_)
				goto end_loop_49;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_50:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_51:
			    if ( !TRUEP(marked))
				goto end_loop_50;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_51;
			  end_loop_50:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_17;
			    goto next_loop_50;
			  end_loop_51:
			  end_17:
			    level = level - (SI_Long)1L;
			    goto next_loop_49;
			  end_loop_49:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = superior;
				temp = Symbol_properties_table;
				temp_1 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = set_skip_list_entry(temp,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_1,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_52:
			    if (level < ab_loop_bind_)
				goto end_loop_52;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_53:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_54:
			    if ( !TRUEP(marked))
				goto end_loop_53;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_54;
			  end_loop_53:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_18;
			    goto next_loop_53;
			  end_loop_54:
			  end_18:
			    level = level - (SI_Long)1L;
			    goto next_loop_52;
			  end_loop_52:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_55:
				if (level < ab_loop_bind_)
				    goto end_loop_55;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_56:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_57:
				if ( !TRUEP(marked))
				    goto end_loop_56;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_57;
			      end_loop_56:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_19;
				goto next_loop_56;
			      end_loop_57:
			      end_19:
				level = level - (SI_Long)1L;
				goto next_loop_55;
			      end_loop_55:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_58:
				if (level < ab_loop_bind_)
				    goto end_loop_58;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_59:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_60:
				if ( !TRUEP(marked))
				    goto end_loop_59;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_60;
			      end_loop_59:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_20;
				goto next_loop_59;
			      end_loop_60:
			      end_20:
				level = level - (SI_Long)1L;
				goto next_loop_58;
			      end_loop_58:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Meter_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp_2 = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp_2 = TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    temp_2 =  !temp_2;
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = superior;
			    key_hash_value = SXHASH_SYMBOL_1(superior) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_61:
			    if (level < ab_loop_bind_)
				goto end_loop_61;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_62:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_63:
			    if ( !TRUEP(marked))
				goto end_loop_62;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_63;
			  end_loop_62:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_21;
			    goto next_loop_62;
			  end_loop_63:
			  end_21:
			    level = level - (SI_Long)1L;
			    goto next_loop_61;
			  end_loop_61:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = superior;
				temp = Symbol_properties_table;
				temp_1 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = set_skip_list_entry(temp,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_1,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_64:
			    if (level < ab_loop_bind_)
				goto end_loop_64;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_65:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_66:
			    if ( !TRUEP(marked))
				goto end_loop_65;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_66;
			  end_loop_65:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_22;
			    goto next_loop_65;
			  end_loop_66:
			  end_22:
			    level = level - (SI_Long)1L;
			    goto next_loop_64;
			  end_loop_64:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_67:
				if (level < ab_loop_bind_)
				    goto end_loop_67;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_68:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_69:
				if ( !TRUEP(marked))
				    goto end_loop_68;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_69;
			      end_loop_68:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_23;
				goto next_loop_68;
			      end_loop_69:
			      end_23:
				level = level - (SI_Long)1L;
				goto next_loop_67;
			      end_loop_67:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_70:
				if (level < ab_loop_bind_)
				    goto end_loop_70;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_71:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_72:
				if ( !TRUEP(marked))
				    goto end_loop_71;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_72;
			      end_loop_71:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_24;
				goto next_loop_71;
			      end_loop_72:
			      end_24:
				level = level - (SI_Long)1L;
				goto next_loop_70;
			      end_loop_70:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    ab_loop_it_ = 
				    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
				    gensymed_symbol,Nil),(SI_Long)6L);
			}
			else
			    ab_loop_it_ = Nil;
			if (ab_loop_it_) {
			    temp_2 = TRUEP(ab_loop_it_);
			    goto end_25;
			}
			goto next_loop_24;
		      end_loop_24:
			temp_2 = TRUEP(Qnil);
		      end_25:;
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_2 =  !temp_2;
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp = Bad_phrase;
		    temp_1 = copy_text_string(string_constant_14);
		    return VALUES_2(temp,temp_1);
		}
		else
		    return VALUES_1(change_qm);
	    }
	    else if (EQ(temp_1,Qcopy_inherited_icon_description)) {
		sub_class_bit_vector = ISVREF(ISVREF(definition,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    if (get_lookup_slot_value_given_default(definition,
			    Qclass_inheritance_path_of_definition,Nil)) {
			superior = Nil;
			ab_loop_list_ = ISVREF(definition,(SI_Long)21L);
			ab_loop_it_ = Nil;
		      next_loop_73:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_73;
			superior = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			skip_list = CDR(Symbol_properties_table);
			key_value = superior;
			key_hash_value = SXHASH_SYMBOL_1(superior) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_74:
			if (level < ab_loop_bind_)
			    goto end_loop_74;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_75:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_76:
			if ( !TRUEP(marked))
			    goto end_loop_75;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_76;
		      end_loop_75:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_26;
			goto next_loop_75;
		      end_loop_76:
		      end_26:
			level = level - (SI_Long)1L;
			goto next_loop_74;
		      end_loop_74:;
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = superior;
			    temp = Symbol_properties_table;
			    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
				    & IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_1 = new_cons;
			    }
			    else
				gensymed_symbol_1 = Nil;
			    if ( !TRUEP(gensymed_symbol_1))
				gensymed_symbol_1 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_1) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_2 = new_cons;
			    }
			    else
				gensymed_symbol_2 = Nil;
			    if ( !TRUEP(gensymed_symbol_2))
				gensymed_symbol_2 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_2) = head;
			    M_CDR(gensymed_symbol_2) = tail;
			    inline_note_allocate_cons(gensymed_symbol_2,
				    Qlookup);
			    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			    inline_note_allocate_cons(gensymed_symbol_1,
				    Qlookup);
			    gensymed_symbol = set_skip_list_entry(temp,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp_1,gensymed_symbol_1);
			}
			global_properties = gensymed_symbol;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
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
		      next_loop_77:
			if (level < ab_loop_bind_)
			    goto end_loop_77;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_78:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_79:
			if ( !TRUEP(marked))
			    goto end_loop_78;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_79;
		      end_loop_78:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_27;
			goto next_loop_78;
		      end_loop_79:
		      end_27:
			level = level - (SI_Long)1L;
			goto next_loop_77;
		      end_loop_77:;
			kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_80:
			    if (level < ab_loop_bind_)
				goto end_loop_80;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_81:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_82:
			    if ( !TRUEP(marked))
				goto end_loop_81;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_82;
			  end_loop_81:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_28;
			    goto next_loop_81;
			  end_loop_82:
			  end_28:
			    level = level - (SI_Long)1L;
			    goto next_loop_80;
			  end_loop_80:;
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
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
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_83:
			    if (level < ab_loop_bind_)
				goto end_loop_83;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_84:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_85:
			    if ( !TRUEP(marked))
				goto end_loop_84;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_85;
			  end_loop_84:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_29;
			    goto next_loop_84;
			  end_loop_85:
			  end_29:
			    level = level - (SI_Long)1L;
			    goto next_loop_83;
			  end_loop_83:;
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			gensymed_symbol = resulting_value;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Entity_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol_3 = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_4 = (SI_Long)1L;
				gensymed_symbol_5 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_4 = gensymed_symbol_4 << 
					gensymed_symbol_5;
				gensymed_symbol_3 = gensymed_symbol_3 & 
					gensymed_symbol_4;
				temp_2 = (SI_Long)0L < gensymed_symbol_3;
			    }
			    else
				temp_2 = TRUEP(Nil);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = superior;
			    key_hash_value = SXHASH_SYMBOL_1(superior) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_86:
			    if (level < ab_loop_bind_)
				goto end_loop_86;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_87:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_88:
			    if ( !TRUEP(marked))
				goto end_loop_87;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_88;
			  end_loop_87:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_30;
			    goto next_loop_87;
			  end_loop_88:
			  end_30:
			    level = level - (SI_Long)1L;
			    goto next_loop_86;
			  end_loop_86:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = superior;
				temp = Symbol_properties_table;
				temp_1 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = set_skip_list_entry(temp,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_1,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_89:
			    if (level < ab_loop_bind_)
				goto end_loop_89;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_90:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_91:
			    if ( !TRUEP(marked))
				goto end_loop_90;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_91;
			  end_loop_90:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_31;
			    goto next_loop_90;
			  end_loop_91:
			  end_31:
			    level = level - (SI_Long)1L;
			    goto next_loop_89;
			  end_loop_89:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_92:
				if (level < ab_loop_bind_)
				    goto end_loop_92;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_93:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_94:
				if ( !TRUEP(marked))
				    goto end_loop_93;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_94;
			      end_loop_93:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_32;
				goto next_loop_93;
			      end_loop_94:
			      end_32:
				level = level - (SI_Long)1L;
				goto next_loop_92;
			      end_loop_92:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_95:
				if (level < ab_loop_bind_)
				    goto end_loop_95;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_96:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_97:
				if ( !TRUEP(marked))
				    goto end_loop_96;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_97;
			      end_loop_96:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_33;
				goto next_loop_96;
			      end_loop_97:
			      end_33:
				level = level - (SI_Long)1L;
				goto next_loop_95;
			      end_loop_95:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Connection_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp_2 = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp_2 = TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    temp_2 =  !temp_2;
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = superior;
			    key_hash_value = SXHASH_SYMBOL_1(superior) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_98:
			    if (level < ab_loop_bind_)
				goto end_loop_98;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_99:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_100:
			    if ( !TRUEP(marked))
				goto end_loop_99;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_100;
			  end_loop_99:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_34;
			    goto next_loop_99;
			  end_loop_100:
			  end_34:
			    level = level - (SI_Long)1L;
			    goto next_loop_98;
			  end_loop_98:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = superior;
				temp = Symbol_properties_table;
				temp_1 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = set_skip_list_entry(temp,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_1,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_101:
			    if (level < ab_loop_bind_)
				goto end_loop_101;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_102:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_103:
			    if ( !TRUEP(marked))
				goto end_loop_102;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_103;
			  end_loop_102:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_35;
			    goto next_loop_102;
			  end_loop_103:
			  end_35:
			    level = level - (SI_Long)1L;
			    goto next_loop_101;
			  end_loop_101:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_104:
				if (level < ab_loop_bind_)
				    goto end_loop_104;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_105:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_106:
				if ( !TRUEP(marked))
				    goto end_loop_105;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_106;
			      end_loop_105:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_36;
				goto next_loop_105;
			      end_loop_106:
			      end_36:
				level = level - (SI_Long)1L;
				goto next_loop_104;
			      end_loop_104:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_107:
				if (level < ab_loop_bind_)
				    goto end_loop_107;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_108:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_109:
				if ( !TRUEP(marked))
				    goto end_loop_108;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_109;
			      end_loop_108:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_37;
				goto next_loop_108;
			      end_loop_109:
			      end_37:
				level = level - (SI_Long)1L;
				goto next_loop_107;
			      end_loop_107:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Meter_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp_2 = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp_2 = TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    temp_2 =  !temp_2;
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = superior;
			    key_hash_value = SXHASH_SYMBOL_1(superior) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_110:
			    if (level < ab_loop_bind_)
				goto end_loop_110;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_111:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_112:
			    if ( !TRUEP(marked))
				goto end_loop_111;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_112;
			  end_loop_111:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_38;
			    goto next_loop_111;
			  end_loop_112:
			  end_38:
			    level = level - (SI_Long)1L;
			    goto next_loop_110;
			  end_loop_110:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = superior;
				temp = Symbol_properties_table;
				temp_1 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = set_skip_list_entry(temp,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_1,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_113:
			    if (level < ab_loop_bind_)
				goto end_loop_113;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_114:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			  next_loop_115:
			    if ( !TRUEP(marked))
				goto end_loop_114;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp = ATOMIC_REF_OBJECT(reference);
			    temp_1 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp,temp_1);
			    MVS_2(result,succ,marked);
			    goto next_loop_115;
			  end_loop_114:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_39;
			    goto next_loop_114;
			  end_loop_115:
			  end_39:
			    level = level - (SI_Long)1L;
			    goto next_loop_113;
			  end_loop_113:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_116:
				if (level < ab_loop_bind_)
				    goto end_loop_116;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_117:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_118:
				if ( !TRUEP(marked))
				    goto end_loop_117;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_118;
			      end_loop_117:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_40;
				goto next_loop_117;
			      end_loop_118:
			      end_40:
				level = level - (SI_Long)1L;
				goto next_loop_116;
			      end_loop_116:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_119:
				if (level < ab_loop_bind_)
				    goto end_loop_119;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_120:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_121:
				if ( !TRUEP(marked))
				    goto end_loop_120;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp = ATOMIC_REF_OBJECT(reference);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_121;
			      end_loop_120:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_41;
				goto next_loop_120;
			      end_loop_121:
			      end_41:
				level = level - (SI_Long)1L;
				goto next_loop_119;
			      end_loop_119:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    ab_loop_it_ = 
				    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
				    gensymed_symbol,Nil),(SI_Long)6L);
			}
			else
			    ab_loop_it_ = Nil;
			if (ab_loop_it_) {
			    temp_2 = TRUEP(ab_loop_it_);
			    goto end_42;
			}
			goto next_loop_73;
		      end_loop_73:
			temp_2 = TRUEP(Qnil);
		      end_42:;
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_2 =  !temp_2;
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp = Bad_phrase;
		    temp_1 = copy_text_string(string_constant_15);
		    return VALUES_2(temp,temp_1);
		}
		else
		    return VALUES_1(change_qm);
	    }
	    else if (EQ(temp_1,Qupdate_definition_attribute)) {
		if (EQ(SECOND(change_qm),Qdefault_message_properties)) {
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
		  next_loop_122:
		    if (level < ab_loop_bind_)
			goto end_loop_122;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_123:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_124:
		    if ( !TRUEP(marked))
			goto end_loop_123;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_124;
		  end_loop_123:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_43;
		    goto next_loop_123;
		  end_loop_124:
		  end_43:
		    level = level - (SI_Long)1L;
		    goto next_loop_122;
		  end_loop_122:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = class_1;
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
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
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
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_1,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
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
		  next_loop_125:
		    if (level < ab_loop_bind_)
			goto end_loop_125;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_126:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_127:
		    if ( !TRUEP(marked))
			goto end_loop_126;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_127;
		  end_loop_126:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_44;
		    goto next_loop_126;
		  end_loop_127:
		  end_44:
		    level = level - (SI_Long)1L;
		    goto next_loop_125;
		  end_loop_125:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_128:
			if (level < ab_loop_bind_)
			    goto end_loop_128;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_129:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_130:
			if ( !TRUEP(marked))
			    goto end_loop_129;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_130;
		      end_loop_129:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_45;
			goto next_loop_129;
		      end_loop_130:
		      end_45:
			level = level - (SI_Long)1L;
			goto next_loop_128;
		      end_loop_128:;
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_131:
			if (level < ab_loop_bind_)
			    goto end_loop_131;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_132:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_133:
			if ( !TRUEP(marked))
			    goto end_loop_132;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_133;
		      end_loop_132:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_46;
			goto next_loop_132;
		      end_loop_133:
		      end_46:
			level = level - (SI_Long)1L;
			goto next_loop_131;
		      end_loop_131:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Message_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_3 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_4 = (SI_Long)1L;
			    gensymed_symbol_5 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_4 = gensymed_symbol_4 << 
				    gensymed_symbol_5;
			    gensymed_symbol_3 = gensymed_symbol_3 & 
				    gensymed_symbol_4;
			    temp_2 = (SI_Long)0L < gensymed_symbol_3;
			}
			else
			    temp_2 = TRUEP(Nil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2)
			return VALUES_1(change_qm);
		    else {
			temp = Bad_phrase;
			temp_1 = copy_text_string(string_constant_16);
			return VALUES_2(temp,temp_1);
		    }
		}
		else
		    return VALUES_1(change_qm);
	    }
	    else if (EQ(temp_1,Qadd_attribute)) {
		temp_1 = SECOND(change_qm);
		if (reserved_system_slot_name_p(definition,FIRST(temp_1))) {
		    temp_1 = SECOND(change_qm);
		    return bad_attribute_name(FIRST(temp_1));
		}
		else
		    return VALUES_1(change_qm);
	    }
	    else if (EQ(temp_1,Qrename_attribute)) {
		if (reserved_system_slot_name_p(definition,THIRD(change_qm)))
		    return bad_attribute_name(THIRD(change_qm));
		else
		    return VALUES_1(change_qm);
	    }
	    else
		return VALUES_1(change_qm);
	}
    }
    else {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_17);
	return VALUES_2(temp,temp_1);
    }
}

/* COMPILE-STUB-DESIGNATION-OR-NONE-FOR-SLOT */
Object compile_stub_designation_or_none_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,12);
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

static Object string_constant_18;  /* "none" */

static Object string_constant_19;  /* "the connection located at ~(~a~) ~d" */

static Object string_constant_20;  /* "the connection at ~(~a~)" */

/* WRITE-STUB-DESIGNATION-OR-NONE-FROM-SLOT */
Object write_stub_designation_or_none_from_slot(stub_designation_or_none,
	    gensymed_symbol)
    Object stub_designation_or_none, gensymed_symbol;
{
    x_note_fn_call(203,13);
    if ( !TRUEP(stub_designation_or_none))
	return tformat(1,string_constant_18);
    else if (CONSP(stub_designation_or_none))
	return tformat(3,string_constant_19,
		FIRST(stub_designation_or_none),
		SECOND(stub_designation_or_none));
    else
	return tformat(2,string_constant_20,stub_designation_or_none);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object string_constant_21;  /* "~a is a reserved word" */

static Object list_constant_6;     /* # */

static Object Qedge;               /* edge */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_22;  /* "~NT " */

static Object string_constant_23;  /* "~NV must be one of the following types: ~a" */

/* STUB-DESIGNATION-OR-NONE-EVALUATION-SETTER */
Object stub_designation_or_none_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, s;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,14);
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
			      list_constant_4,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_stub_designation_or_none_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_5))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,Qsymbol)) {
	s = evaluation_value;
	if (getfq_function_no_default(INLINE_SYMBOL_PLIST(evaluation_value),
		Qreserved_word_p)) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant_21,s);
	    result = VALUES_2(temp,temp_1);
	    goto end_blocky_block_block;
	}
	result = VALUES_1(s);
    }
    else if (type_specification_type_p(gensymed_symbol,list_constant_6)) {
	gensymed_symbol = evaluation_value;
	temp_1 = estructure_slot(gensymed_symbol,Qedge,Nil);
	result = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,
		Qposition,Nil));
    }
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
		  tformat(2,string_constant_22,list_constant_5);
		  tformat(2,string_constant_22,Qsymbol);
		  tformat(2,string_constant_22,list_constant_6);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_23,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_blocky_block_block:
  end_stub_designation_or_none_evaluation_setter:
    return result;
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_structure;       /* structure */

/* STUB-DESIGNATION-OR-NONE-EVALUATION-GETTER */
Object stub_designation_or_none_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(203,15);
    if ( !TRUEP(slot_value))
	temp = Nil;
    else if (SYMBOLP(slot_value))
	temp = slot_value;
    else if (CONSP(slot_value)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qedge;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qedge;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = CAR(slot_value);
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
	    item_or_value = CAR(slot_value);
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
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qposition;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qposition;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = CADR(slot_value);
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
	    item_or_value = CADR(slot_value);
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
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-CLASS-DEFINITION-CHANGE-FROM-SLOT */
Object write_class_definition_change_from_slot(change,gensymed_symbol)
    Object change, gensymed_symbol;
{
    x_note_fn_call(203,16);
    return twrite(string_constant_18);
}

/* WRITE-OBJECT-CHANGE-FROM-SLOT */
Object write_object_change_from_slot(change,gensymed_symbol)
    Object change, gensymed_symbol;
{
    x_note_fn_call(203,17);
    return twrite(string_constant_18);
}

/* WRITE-CONNECTION-CHANGE-FROM-SLOT */
Object write_connection_change_from_slot(change,gensymed_symbol)
    Object change, gensymed_symbol;
{
    x_note_fn_call(203,18);
    return twrite(string_constant_18);
}

/* WRITE-MESSAGE-CHANGE-FROM-SLOT */
Object write_message_change_from_slot(change,gensymed_symbol)
    Object change, gensymed_symbol;
{
    x_note_fn_call(203,19);
    return twrite(string_constant_18);
}

static Object Qfinal;              /* final */

/* COMPILE-MENU-OPTION-FOR-SLOT */
Object compile_menu_option_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,20);
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
    if ( !EQ(CAR(parse_result),Qfinal))
	return VALUES_1(CAR(parse_result));
    else
	return VALUES_1(Nil);
}

static Object string_constant_24;  /* "a final menu choice" */

static Object string_constant_25;  /* "never a menu choice" */

static Object string_constant_26;  /* "not a final menu choice" */

/* WRITE-MENU-OPTION-FROM-SLOT */
Object write_menu_option_from_slot(slot_value,frame)
    Object slot_value, frame;
{
    Object instantiate_qm, include_in_menus_qm;

    x_note_fn_call(203,21);
    instantiate_qm = ISVREF(frame,(SI_Long)25L);
    include_in_menus_qm = ISVREF(frame,(SI_Long)26L);
    if (instantiate_qm) {
	if (include_in_menus_qm)
	    return twrite(string_constant_24);
	else
	    return twrite(string_constant_25);
    }
    else
	return twrite(string_constant_26);
}

static Object Qdefault;            /* default */

static Object Qinterval;           /* interval */

static Object Qseconds;            /* seconds */

static Object Qtime_stamp;         /* time-stamp */

static Object Qfree_text;          /* free-text */

static Object Qdate_format_description;  /* date-format-description */

/* COMPILE-FORMAT?-FOR-SLOT */
Object compile_format_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object left, right;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(203,22);
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
	return VALUES_1(Nil);
    else if (EQ(parse_result,Qinterval))
	return VALUES_1(Qseconds);
    else if (EQ(parse_result,Qtime_stamp) || EQ(parse_result,Qfree_text))
	return VALUES_1(parse_result);
    else if (SYMBOLP(parse_result) && 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(parse_result),
	    Qdate_format_description))
	return VALUES_1(parse_result);
    else {
	result = decode_format(parse_result);
	MVS_2(result,left,right);
	if (left)
	    return phrase_cons(left,right);
	else
	    return VALUES_1(Bad_phrase);
    }
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qwhole_number_precision;  /* whole-number-precision */

static Object string_constant_27;  /* "The whole-number-precision ~D is not between 0 and ~D" */

static Object Qfraction_precision;  /* fraction-precision */

static Object string_constant_28;  /* "The fraction-precision ~D is not between 0 and ~D" */

static Object string_constant_29;  /* "d" */

static Object string_constant_30;  /* "." */

/* FLOAT-FORMAT-EVALUATION-SETTER */
Object float_format_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object fstring;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,23);
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
			  list_constant_7))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_8,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_float_format_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (IFIX(estructure_slot(gensymed_symbol,Qwhole_number_precision,Nil)) 
	    < (SI_Long)0L || FIXNUM_GT(estructure_slot(gensymed_symbol,
	    Qwhole_number_precision,Nil),Float_format_precision_limit)) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_27,
		estructure_slot(gensymed_symbol,Qwhole_number_precision,
		Nil),Float_format_precision_limit);
	result = VALUES_2(temp,temp_1);
    }
    else if (IFIX(estructure_slot(gensymed_symbol,Qfraction_precision,
	    Nil)) < (SI_Long)0L || 
	    FIXNUM_GT(estructure_slot(gensymed_symbol,Qfraction_precision,
	    Nil),Float_format_precision_limit)) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_28,
		estructure_slot(gensymed_symbol,Qfraction_precision,Nil),
		Float_format_precision_limit);
	result = VALUES_2(temp,temp_1);
    }
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
		  i = (SI_Long)1L;
		  ab_loop_bind_ = IFIX(estructure_slot(gensymed_symbol,
			  Qwhole_number_precision,Nil));
		next_loop:
		  if (i > ab_loop_bind_)
		      goto end_loop;
		  twrite(string_constant_29);
		  i = i + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
		  twrite(string_constant_30);
		  i = (SI_Long)1L;
		  ab_loop_bind_ = IFIX(estructure_slot(gensymed_symbol,
			  Qfraction_precision,Nil));
		next_loop_1:
		  if (i > ab_loop_bind_)
		      goto end_loop_1;
		  twrite(string_constant_29);
		  i = i + (SI_Long)1L;
		  goto next_loop_1;
		end_loop_1:;
		  fstring = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = intern_text_string(1,fstring);
    }
  end_float_format_evaluation_setter:
    return result;
}

/* FLOAT-FORMAT-EVALUATION-GETTER */
Object float_format_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol;

    x_note_fn_call(203,24);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qwhole_number_precision,
	    CAR(slot_value));
    set_evaluation_structure_slot(gensymed_symbol,Qfraction_precision,
	    CDR(slot_value));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object Qfloat_format;       /* float-format */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* FORMAT?-EVALUATION-SETTER */
Object format_qm_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,25);
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
			  list_constant_9))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_10,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_format_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qdefault) || EQ(evaluation_value,Qinterval) || 
	    EQ(evaluation_value,Qtime_stamp) || EQ(evaluation_value,
	    Qfree_text))
	result = VALUES_1(evaluation_value);
    else if (SYMBOLP(evaluation_value) && 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(evaluation_value),
	    Qdate_format_description))
	result = VALUES_1(evaluation_value);
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfloat_format),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
  end_format_qm_evaluation_setter:
    return result;
}

/* FORMAT?-EVALUATION-GETTER */
Object format_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(203,26);
    if ( !TRUEP(slot_value))
	temp = Qdefault;
    else if (EQ(slot_value,Qseconds))
	temp = Qinterval;
    else if (EQ(slot_value,Qtime_stamp) || EQ(slot_value,Qfree_text))
	temp = slot_value;
    else if (SYMBOLP(slot_value) && 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_value),
	    Qdate_format_description))
	temp = slot_value;
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfloat_format),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_31;  /* "default" */

static Object string_constant_32;  /* "time stamp" */

static Object string_constant_33;  /* "free text" */

static Object string_constant_34;  /* "interval" */

/* WRITE-FORMAT?-FROM-SLOT */
Object write_format_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(203,27);
    if ( !TRUEP(value))
	return twrite(string_constant_31);
    else if (EQ(value,Qtime_stamp))
	return twrite(string_constant_32);
    else if (EQ(value,Qfree_text))
	return twrite(string_constant_33);
    else if (EQ(value,Qseconds))
	return twrite(string_constant_34);
    else if (SYMBOLP(value) && 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(value),
	    Qdate_format_description))
	return twrite(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(value),
		Qdate_format_description),(SI_Long)4L));
    else if (ATOM(value))
	return VALUES_1(value);
    else {
	i = (SI_Long)1L;
	ab_loop_bind_ = IFIX(CAR(value));
      next_loop:
	if (i > ab_loop_bind_)
	    goto end_loop;
	tprin(string_constant_29,Nil);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	tprin(string_constant_30,Nil);
	i = (SI_Long)1L;
	ab_loop_bind_ = IFIX(CDR(value));
      next_loop_1:
	if (i > ab_loop_bind_)
	    goto end_loop_1;
	tprin(string_constant_29,Nil);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* COMPILE-TYPE-IN-BOX-FORMAT?-FOR-SLOT */
Object compile_type_in_box_format_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,28);
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
    return compile_format_qm_for_slot(6,parse_result,Nil,Nil,Nil,Nil,Nil);
}

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

static Object Qformat_qm;          /* format? */

/* TYPE-IN-BOX-FORMAT?-EVALUATION-SETTER */
Object type_in_box_format_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,29);
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
			  list_constant_11))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_12,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_type_in_box_format_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qformat_qm),
	    Qcategory_evaluator_interface);
    temp_1 = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    result = FUNCALL_4(temp_1,evaluation_value,Nil,Nil,Nil);
  end_type_in_box_format_qm_evaluation_setter:
    return result;
}

/* TYPE-IN-BOX-FORMAT?-EVALUATION-GETTER */
Object type_in_box_format_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, temp;

    x_note_fn_call(203,30);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qformat_qm),
	    Qcategory_evaluator_interface);
    temp = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    GENSYM_RETURN_ONE(FUNCALL_3(temp,slot_value,Nil,Nil));
    return VALUES_1(Nil);
}

/* WRITE-TYPE-IN-BOX-FORMAT?-FROM-SLOT */
Object write_type_in_box_format_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,31);
    return write_format_qm_from_slot(value,Nil);
}

/* COMPILE-EXTRA-GRID-LINE-SPECS-FOR-SLOT */
Object compile_extra_grid_line_specs_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,32);
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

static Object Qcm;                 /* \, */

/* WRITE-EXTRA-GRID-LINE-SPECS-FROM-SLOT */
Object write_extra_grid_line_specs_from_slot(extra_grid_line_specs,
	    gensymed_symbol)
    Object extra_grid_line_specs, gensymed_symbol;
{
    Object grid_line_spec, ab_loop_list_, first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(203,33);
    if ( !TRUEP(extra_grid_line_specs))
	return twrite(string_constant_18);
    else if (CONSP(extra_grid_line_specs) && EQ(CAR(extra_grid_line_specs),
	    Qcm)) {
	grid_line_spec = Nil;
	ab_loop_list_ = CDR(extra_grid_line_specs);
	first_time_qm = T;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	grid_line_spec = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_time_qm = Nil;
	if ( !TRUEP(first_time_qm))
	    twrite(string_constant_6);
	print_grid_line_spec(grid_line_spec);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return print_grid_line_spec(extra_grid_line_specs);
}

static Object string_constant_35;  /* "at " */

static Object string_constant_36;  /* " in " */

/* PRINT-GRID-LINE-SPEC */
Object print_grid_line_spec(grid_line_spec)
    Object grid_line_spec;
{
    Object temp, slot_value_number;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,34);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (slot_value_number_p(grid_line_spec)) {
	    twrite(string_constant_35);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(grid_line_spec) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(grid_line_spec)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(grid_line_spec,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(grid_line_spec) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(grid_line_spec)) == 
		    (SI_Long)1L)
		temp = aref1(grid_line_spec,FIX((SI_Long)0L));
	    else
		temp = grid_line_spec;
	    result = print_ruling_parameter_number(temp);
	}
	else {
	    twrite(string_constant_35);
	    slot_value_number = CAR(grid_line_spec);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		temp = slot_value_number;
	    print_ruling_parameter_number(temp);
	    twrite(string_constant_36);
	    result = twrite(CDR(grid_line_spec));
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* PRINT-RULING-PARAMETER-NUMBER */
Object print_ruling_parameter_number(ruling_parameter_number)
    Object ruling_parameter_number;
{
    x_note_fn_call(203,35);
    if (FLOATP(ruling_parameter_number))
	return write_floating_point_number_simple_c_format(1,
		ruling_parameter_number);
    else
	return twrite(ruling_parameter_number);
}

/* WRITE-DIAL-RULING-PARAMETER-FROM-SLOT */
Object write_dial_ruling_parameter_from_slot(dial_ruling_parameter,
	    gensymed_symbol)
    Object dial_ruling_parameter, gensymed_symbol;
{
    Object temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,36);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(dial_ruling_parameter) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(dial_ruling_parameter)) == 
		(SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(dial_ruling_parameter,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(dial_ruling_parameter) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(dial_ruling_parameter)) == 
		(SI_Long)1L)
	    temp = aref1(dial_ruling_parameter,FIX((SI_Long)0L));
	else
	    temp = dial_ruling_parameter;
	result = print_ruling_parameter_number(temp);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-METER-RULING-PARAMETER-FROM-SLOT */
Object write_meter_ruling_parameter_from_slot(meter_ruling_parameter,
	    gensymed_symbol)
    Object meter_ruling_parameter, gensymed_symbol;
{
    Object temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,37);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(meter_ruling_parameter) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(meter_ruling_parameter)) == 
		(SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(meter_ruling_parameter,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(meter_ruling_parameter) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(meter_ruling_parameter)) == 
		(SI_Long)1L)
	    temp = aref1(meter_ruling_parameter,FIX((SI_Long)0L));
	else
	    temp = meter_ruling_parameter;
	result = print_ruling_parameter_number(temp);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qincrement_per_dial_ruling;  /* increment-per-dial-ruling */

static Object string_constant_37;  /* "Increment per dial ruling must be positive." */

/* COMPILE-DIAL-RULING-PARAMETER-FOR-SLOT */
Object compile_dial_ruling_parameter_for_slot varargs_1(int, n)
{
    Object parse_result, dial, slot_name;
    Object temp, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(203,38);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    dial = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(slot_name,Qincrement_per_dial_ruling)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(parse_result,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(parse_result) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		temp = aref1(parse_result,FIX((SI_Long)0L));
	    else
		temp = parse_result;
	    temp_1 = TRUEP(minusp(temp));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_2 = Bad_phrase;
	temp = copy_text_string(string_constant_37);
	return VALUES_2(temp_2,temp);
    }
    else
	return VALUES_1(parse_result);
}

static Object list_constant_13;    /* # */

static Object Qfloat_array;        /* float-array */

/* DIAL-RULING-PARAMETER-EVALUATION-SETTER */
Object dial_ruling_parameter_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    double aref_new_value;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,39);
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
			  list_constant_13))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qnumber,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_dial_ruling_parameter_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_2 = Vector_of_simple_float_array_pools;
	    temp_3 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    else {
		temp_2 = Available_float_array_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	aref_new_value = DFLOAT_ISAREF_1(evaluation_value,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = note_use_of_managed_float_in_phrase(new_float);
    }
    else
	result = VALUES_1(evaluation_value);
  end_dial_ruling_parameter_evaluation_setter:
    return result;
}

/* DIAL-RULING-PARAMETER-EVALUATION-GETTER */
Object dial_ruling_parameter_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,40);
    GENSYM_RETURN_ONE(FIXNUMP(slot_value) ? slot_value : 
	    copy_managed_float(slot_value));
    return VALUES_1(Nil);
}

static Object Qincrement_per_meter_ruling;  /* increment-per-meter-ruling */

static Object string_constant_38;  /* "Increment per meter ruling must be positive." */

/* COMPILE-METER-RULING-PARAMETER-FOR-SLOT */
Object compile_meter_ruling_parameter_for_slot varargs_1(int, n)
{
    Object parse_result, meter, slot_name;
    Object temp, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(203,41);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    meter = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(slot_name,Qincrement_per_meter_ruling)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(parse_result,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(parse_result) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		temp = aref1(parse_result,FIX((SI_Long)0L));
	    else
		temp = parse_result;
	    temp_1 = TRUEP(minusp(temp));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_2 = Bad_phrase;
	temp = copy_text_string(string_constant_38);
	return VALUES_2(temp_2,temp);
    }
    else
	return VALUES_1(parse_result);
}

static Object list_constant_14;    /* # */

static Object Qdial_ruling_parameter;  /* dial-ruling-parameter */

/* METER-RULING-PARAMETER-EVALUATION-SETTER */
Object meter_ruling_parameter_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,42);
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
			  list_constant_14))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qnumber,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_meter_ruling_parameter_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdial_ruling_parameter),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_meter_ruling_parameter_evaluation_setter:
    return result;
}

/* METER-RULING-PARAMETER-EVALUATION-GETTER */
Object meter_ruling_parameter_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,43);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdial_ruling_parameter),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_39;  /* "graph background: " */

static Object string_constant_40;  /* ", grid background: " */

/* WRITE-GRAPH-BACKGROUND-COLORS-FROM-SLOT */
Object write_graph_background_colors_from_slot(graph_background_colors,
	    gensymed_symbol)
    Object graph_background_colors, gensymed_symbol;
{
    x_note_fn_call(203,44);
    twrite(string_constant_39);
    twrite_color(CAR(graph_background_colors));
    twrite(string_constant_40);
    return twrite_color(CDR(graph_background_colors));
}

static Object Qwithout_tickmark_labels;  /* without-tickmark-labels */

static Object string_constant_41;  /* " to " */

static Object string_constant_42;  /* " after start" */

static Object string_constant_43;  /* " without tickmark labels" */

/* WRITE-HORIZONTAL-GRAPH-RULING-PARAMETER?-FROM-SLOT */
Object write_horizontal_graph_ruling_parameter_qm_from_slot(horizontal_graph_ruling_parameter_qm,
	    gensymed_symbol)
    Object horizontal_graph_ruling_parameter_qm, gensymed_symbol;
{
    Object without_labels_qm, parse_var, temp;
    Object result;

    x_note_fn_call(203,45);
    without_labels_qm = Nil;
    parse_var = horizontal_graph_ruling_parameter_qm;
    if (CONSP(parse_var) && EQ(CAR(parse_var),Qwithout_tickmark_labels))
	result = VALUES_2(CDR(parse_var),T);
    else
	result = VALUES_2(parse_var,Nil);
    MVS_2(result,horizontal_graph_ruling_parameter_qm,without_labels_qm);
    if ( !TRUEP(horizontal_graph_ruling_parameter_qm))
	twrite(string_constant_18);
    else if (NUMBERP(horizontal_graph_ruling_parameter_qm))
	twrite(string_constant_18);
    else if ( !EQ(CAR(horizontal_graph_ruling_parameter_qm),Qsc))
	print_constant(2,CAR(horizontal_graph_ruling_parameter_qm),Qseconds);
    else {
	temp = SECOND(horizontal_graph_ruling_parameter_qm);
	if (ATOM(temp))
	    twrite(string_constant_18);
	else {
	    temp = SECOND(horizontal_graph_ruling_parameter_qm);
	    print_constant(2,CAR(temp),Qseconds);
	    twrite(string_constant_41);
	    temp = THIRD(horizontal_graph_ruling_parameter_qm);
	    print_constant(2,CAR(temp),Qseconds);
	    twrite(string_constant_42);
	}
    }
    if (without_labels_qm)
	return twrite(string_constant_43);
    else
	return VALUES_1(Nil);
}

static Object string_constant_44;  /* " with all intervals the same" */

/* WRITE-VERTICAL-GRAPH-RULING-PARAMETER?-FROM-SLOT */
Object write_vertical_graph_ruling_parameter_qm_from_slot(vertical_graph_ruling_parameter_qm,
	    gensymed_symbol)
    Object vertical_graph_ruling_parameter_qm, gensymed_symbol;
{
    Object without_labels_qm, parse_var, temp, slot_value_number;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,46);
    without_labels_qm = Nil;
    parse_var = vertical_graph_ruling_parameter_qm;
    if (CONSP(parse_var) && EQ(CAR(parse_var),Qwithout_tickmark_labels))
	result = VALUES_2(CDR(parse_var),T);
    else
	result = VALUES_2(parse_var,Nil);
    MVS_2(result,vertical_graph_ruling_parameter_qm,without_labels_qm);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if ( !TRUEP(vertical_graph_ruling_parameter_qm))
	    twrite(string_constant_18);
	else if (slot_value_number_p(vertical_graph_ruling_parameter_qm)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(vertical_graph_ruling_parameter_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vertical_graph_ruling_parameter_qm)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(vertical_graph_ruling_parameter_qm,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(vertical_graph_ruling_parameter_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vertical_graph_ruling_parameter_qm)) 
		    == (SI_Long)1L)
		temp = aref1(vertical_graph_ruling_parameter_qm,
			FIX((SI_Long)0L));
	    else
		temp = vertical_graph_ruling_parameter_qm;
	    print_ruling_parameter_number(temp);
	}
	else if (slot_value_number_p(CAR(vertical_graph_ruling_parameter_qm))) 
		    {
	    slot_value_number = CAR(vertical_graph_ruling_parameter_qm);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		temp = slot_value_number;
	    print_ruling_parameter_number(temp);
	    twrite(string_constant_44);
	}
	else {
	    slot_value_number = SECOND(vertical_graph_ruling_parameter_qm);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		temp = slot_value_number;
	    print_ruling_parameter_number(temp);
	    twrite(string_constant_41);
	    slot_value_number = THIRD(vertical_graph_ruling_parameter_qm);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		temp = slot_value_number;
	    print_ruling_parameter_number(temp);
	    if (FOURTH(vertical_graph_ruling_parameter_qm))
		twrite(string_constant_44);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    if (without_labels_qm)
	return twrite(string_constant_43);
    else
	return VALUES_1(Nil);
}

static Object string_constant_45;  /* "compute automatically" */

static Object string_constant_46;  /* " beginning at " */

/* WRITE-HORIZONTAL-GRIDLINE-INTERVAL?-FROM-SLOT */
Object write_horizontal_gridline_interval_qm_from_slot(horizontal_gridline_interval_qm,
	    gensymed_symbol)
    Object horizontal_gridline_interval_qm, gensymed_symbol;
{
    Object slot_value_number, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,47);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if ( !TRUEP(horizontal_gridline_interval_qm))
	    result = twrite(string_constant_45);
	else {
	    slot_value_number = CAR(horizontal_gridline_interval_qm);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		temp = slot_value_number;
	    print_ruling_parameter_number(temp);
	    twrite(string_constant_46);
	    slot_value_number = CDR(horizontal_gridline_interval_qm);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		temp = slot_value_number;
	    result = print_ruling_parameter_number(temp);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_47;  /* "Horizontal axis range can not be greater than 24 weeks." */

static Object string_constant_48;  /* "Horizontal axis range must be greater than 0." */

/* COMPILE-HORIZONTAL-GRAPH-RULING-PARAMETER?-FOR-SLOT */
Object compile_horizontal_graph_ruling_parameter_qm_for_slot varargs_1(int, n)
{
    Object parse_result, graph, slot_name;
    Object original_parse, without_labels_qm, parse_var, temp, temp_1, range;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(203,48);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    graph = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    original_parse = parse_result;
    without_labels_qm = Nil;
    parse_var = parse_result;
    if (CONSP(parse_var) && EQ(CAR(parse_var),Qwithout_tickmark_labels))
	result = VALUES_2(CDR(parse_var),T);
    else
	result = VALUES_2(parse_var,Nil);
    MVS_2(result,parse_result,without_labels_qm);
    if (EQ(parse_result,Qnone)) {
	if ( !TRUEP(without_labels_qm))
	    return VALUES_1(Nil);
	else {
	    M_CDR(original_parse) = Nil;
	    return VALUES_1(original_parse);
	}
    }
    else if ( !EQ(CAR(parse_result),Qsc)) {
	temp = CAR(parse_result);
	temp_1 = FIX((SI_Long)14515200L);
	if (NUM_GT(temp,temp_1)) {
	    temp_1 = Bad_phrase;
	    temp = copy_text_string(string_constant_47);
	    return VALUES_2(temp_1,temp);
	}
	else
	    return VALUES_1(original_parse);
    }
    else {
	temp_1 = THIRD(parse_result);
	temp = SECOND(parse_result);
	range = minus(CAR(temp_1),CAR(temp));
	temp = FIX((SI_Long)14515200L);
	if (NUM_GT(range,temp)) {
	    temp_1 = Bad_phrase;
	    temp = copy_text_string(string_constant_47);
	    return VALUES_2(temp_1,temp);
	}
	else {
	    temp = FIX((SI_Long)0L);
	    if (NUM_LE(range,temp)) {
		temp_1 = Bad_phrase;
		temp = copy_text_string(string_constant_48);
		return VALUES_2(temp_1,temp);
	    }
	    else
		return VALUES_1(original_parse);
	}
    }
}

static Object string_constant_49;  /* "Vertical axis range can not be less than 0." */

/* COMPILE-VERTICAL-GRAPH-RULING-PARAMETER?-FOR-SLOT */
Object compile_vertical_graph_ruling_parameter_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object original_parse, without_labels_qm, parse_var, range;
    Object value_to_return_if_ok, temp, temp_1, phrase_number;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,49);
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
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	original_parse = parse_result;
	without_labels_qm = Nil;
	parse_var = parse_result;
	if (CONSP(parse_var) && EQ(CAR(parse_var),Qwithout_tickmark_labels))
	    result = VALUES_2(CDR(parse_var),T);
	else
	    result = VALUES_2(parse_var,Nil);
	MVS_2(result,parse_result,without_labels_qm);
	if (EQ(parse_result,Qnone)) {
	    if ( !TRUEP(without_labels_qm))
		result = VALUES_1(Nil);
	    else {
		M_CDR(original_parse) = Nil;
		result = VALUES_1(original_parse);
	    }
	}
	else if (phrase_number_p(parse_result)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		range = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(parse_result,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(parse_result) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		range = aref1(parse_result,FIX((SI_Long)0L));
	    else
		range = parse_result;
	    value_to_return_if_ok = original_parse;
	    if (minusp(range)) {
		temp = Bad_phrase;
		temp_1 = copy_text_string(string_constant_49);
		result = VALUES_2(temp,temp_1);
	    }
	    else
		result = VALUES_1(value_to_return_if_ok);
	}
	else if (phrase_number_p(CAR(parse_result))) {
	    phrase_number = CAR(parse_result);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		range = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		range = aref1(phrase_number,FIX((SI_Long)0L));
	    else
		range = phrase_number;
	    value_to_return_if_ok = original_parse;
	    if (minusp(range)) {
		temp = Bad_phrase;
		temp_1 = copy_text_string(string_constant_49);
		result = VALUES_2(temp,temp_1);
	    }
	    else
		result = VALUES_1(value_to_return_if_ok);
	}
	else {
	    phrase_number = THIRD(parse_result);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		temp_1 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		temp_1 = aref1(phrase_number,FIX((SI_Long)0L));
	    else
		temp_1 = phrase_number;
	    phrase_number = SECOND(parse_result);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		temp = aref1(phrase_number,FIX((SI_Long)0L));
	    else
		temp = phrase_number;
	    range = minus(temp_1,temp);
	    if (minusp(range)) {
		temp = Bad_phrase;
		temp_1 = copy_text_string(string_constant_49);
		result = VALUES_2(temp,temp_1);
	    }
	    else
		result = VALUES_1(original_parse);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object array_constant_1;    /* # */

/* COMPILE-HORIZONTAL-GRIDLINE-INTERVAL?-FOR-SLOT */
Object compile_horizontal_gridline_interval_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object phrase_number, number, temp_1, temp_2;
    char temp;
    double arg, arg_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,50);
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
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    phrase_number = phrase_number_p(parse_result) ? parse_result : 
		    CAR(parse_result);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		number = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		number = aref1(phrase_number,FIX((SI_Long)0L));
	    else
		number = phrase_number;
	    if (FIXNUMP(number))
		temp = IFIX(number) <= (SI_Long)0L;
	    else {
		arg = DOUBLE_FLOAT_TO_DOUBLE(number);
		arg_1 = 0.0;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp) {
		temp_1 = Bad_phrase;
		temp_2 = 
			copy_constant_wide_string_given_length(array_constant_1,
			FIX((SI_Long)39L));
		result = VALUES_2(temp_1,temp_2);
	    }
	    else if (phrase_number_p(parse_result))
		result = phrase_cons(parse_result,FIX((SI_Long)0L));
	    else
		result = VALUES_1(parse_result);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

static Object Qobsolete_datum;     /* obsolete-datum */

static Object array_constant_2;    /* # */

static Object list_constant_15;    /* # */

static Object Qslot_value_writer;  /* slot-value-writer */

static Object string_constant_50;  /* "[deleted attribute]" */

/* WRITE-READOUT-TABLE-VALUE-PER-FORMAT */
Object write_readout_table_value_per_format(evaluation_value,format_1)
    Object evaluation_value, format_1;
{
    Object grammar_category_symbol, slot_value, frame_qm, slot_value_writer_qm;
    Object write_symbols_in_lower_case_qm, write_symbols_parsably_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(203,51);
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qobsolete_datum)) {
	write_readout_table_value_per_format(M_CAR(evaluation_value),format_1);
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)2L));
    }
    else if (CONSP(format_1)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		(SI_Long)1L)
	    return write_floating_point_number(7,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_value,
		    (SI_Long)0L)),M_CAR(format_1),M_CDR(format_1),
		    FIX((SI_Long)6L),Nil,Nil,Nil);
	else
	    return write_evaluation_value(1,evaluation_value);
    }
    else if (memq_function(format_1,list_constant_15)) {
	if (FIXNUMP(evaluation_value) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		(SI_Long)1L || INLINE_LONG_VECTOR_P(evaluation_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		(SI_Long)1L)
	    return print_constant(3,
		    evaluation_quantity_value(evaluation_value),format_1,
		    EQ(format_1,Qfree_text) ? T : Nil);
	else
	    return write_evaluation_value(2,evaluation_value,EQ(format_1,
		    Qfree_text) ? T : Nil);
    }
    else if (SYMBOLP(format_1) && 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(format_1),
	    Qdate_format_description)) {
	grammar_category_symbol = 
		ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(format_1),
		Qdate_format_description),(SI_Long)1L);
	slot_value = evaluation_value;
	frame_qm = Nil;
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
		result = VALUES_1(inline_funcall_2(slot_value_writer_qm,
			slot_value,frame_qm));
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return twrite(string_constant_50);
    }
    else
	return write_evaluation_value(1,evaluation_value);
}

static Object Qformat_for_readout_table;  /* format-for-readout-table */

static Object array_constant_3;    /* # */

/* WRITE-VALUE-FOR-READOUT-TABLE-FROM-SLOT */
Object write_value_for_readout_table_from_slot(ignored_value,readout_table)
    Object ignored_value, readout_table;
{
    Object evaluation_value_qm, format_qm, default_float_to_text_format;
    Declare_special(1);
    Object result;

    x_note_fn_call(203,52);
    evaluation_value_qm = 
	    get_cached_value_for_cell_based_display(readout_table);
    if ( !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_qm) != 
	    (SI_Long)0L))
	Leave_text_representation_as_a_single_line_qm = T;
    format_qm = get_lookup_slot_value(readout_table,Qformat_for_readout_table);
    if ( !TRUEP(evaluation_value_qm))
	return twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)4L));
    else if ( !TRUEP(format_qm)) {
	default_float_to_text_format = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Default_float_to_text_format,Qdefault_float_to_text_format,default_float_to_text_format,
		0);
	  result = write_evaluation_value(1,evaluation_value_qm);
	POP_SPECIAL();
	return result;
    }
    else
	return write_readout_table_value_per_format(evaluation_value_qm,
		format_qm);
}

static Object array_constant_4;    /* # */

/* WRITE-VALUE-FOR-DIGITAL-CLOCK-FROM-SLOT */
Object write_value_for_digital_clock_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,53);
    Leave_text_representation_as_a_single_line_qm = T;
    if (value)
	return print_constant(2,value,Qtime_stamp);
    else
	return twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)4L));
}

/* WRITE-DISPLAY-INTERVAL-FROM-SLOT */
Object write_display_interval_from_slot(display_interval,gensymed_symbol)
    Object display_interval, gensymed_symbol;
{
    x_note_fn_call(203,54);
    return print_constant(2,display_interval,Qseconds);
}

/* COMPILE-DISPLAY-INTERVAL-FOR-SLOT */
Object compile_display_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object interval_number_specified, temp_1, temp_2;
    char temp;
    double arg, arg_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(203,55);
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
    interval_number_specified = M_CAR(parse_result);
    temp = FIXNUMP(interval_number_specified) ? 
	    FIXNUM_PLUSP(interval_number_specified) : TRUEP(Qnil);
    if (temp);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(interval_number_specified) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interval_number_specified)) == 
	    (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    arg = DFLOAT_ISAREF_1(interval_number_specified,(SI_Long)0L);
	    arg_1 = 0.0;
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(interval_number_specified);
    else {
	temp_1 = Bad_phrase;
	temp_2 = copy_constant_wide_string_given_length(array_constant_1,
		FIX((SI_Long)39L));
	return VALUES_2(temp_1,temp_2);
    }
}

static Object list_constant_16;    /* # */

static Object Qpositive_quantity_interval_qm;  /* positive-quantity-interval? */

/* DISPLAY-INTERVAL-EVALUATION-SETTER */
Object display_interval_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,56);
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
			  list_constant_16))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qnumber,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_display_interval_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_quantity_interval_qm),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_display_interval_evaluation_setter:
    return result;
}

/* DISPLAY-INTERVAL-EVALUATION-GETTER */
Object display_interval_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,57);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_quantity_interval_qm),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-YES-OR-NO-FOR-SLOT */
Object compile_yes_or_no_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,58);
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

static Object string_constant_51;  /* "yes" */

static Object string_constant_52;  /* "no" */

/* WRITE-YES-OR-NO-FROM-SLOT */
Object write_yes_or_no_from_slot(yes_or_no,gensymed_symbol)
    Object yes_or_no, gensymed_symbol;
{
    x_note_fn_call(203,59);
    return twrite_general_string(yes_or_no ? string_constant_51 : 
	    string_constant_52);
}

static Object Qcell_array;         /* cell-array */

static Object Qg2_cell_array;      /* g2-cell-array */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qpart_stack;         /* part-stack */

static Object Qmark;               /* mark */

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

static Object Qempty_expression_cell;  /* empty-expression-cell */

static Object Qbad;                /* bad */

/* COMPILE-DISPLAY-EXPRESSION-FOR-SLOT */
Object compile_display_expression_for_slot varargs_1(int, n)
{
    Object parse_result, display_frame, gensymed_symbol;
    Object current_computation_frame;
    Object current_computation_component_particulars;
    Object current_computation_style, current_block_of_dependent_frame;
    Object cell_array_qm, expression_cell_qm, expression_qm, temp, result_1;
    Object current_flag_state_qm, slot_description, new_cons, temp_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object old_current_part_description, sub_class_bit_vector;
    Object part_feature_index, exit_feature_handler, part_stack_pop_store;
    Object cons_1, next_cons, frame_and_slot_or_atom, ab_loop_list_;
    Object ab_loop_it_, stack_change_pop_store;
    SI_Long svref_new_value_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,60);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    display_frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    current_computation_frame = display_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    4);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      3);
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		2);
	  current_block_of_dependent_frame = display_frame;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		  1);
	    cell_array_qm = 
		    get_lookup_slot_value_given_default(display_frame,
		    Qcell_array,Nil);
	    expression_cell_qm = cell_array_qm ? 
		    (FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),(SI_Long)0L + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
		    (SI_Long)2L),(SI_Long)0L)) : Nil;
	    expression_qm = parse_result;
	    if (expression_qm) {
		if ( !(cell_array_qm && expression_cell_qm)) {
		    cell_array_qm = make_frame(Qg2_cell_array);
		    change_slot_value(3,display_frame,Qcell_array,
			    cell_array_qm);
		    make_empty_expression_cell(cell_array_qm);
		    expression_cell_qm = 
			    FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,
			    (SI_Long)3L),(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
			    (SI_Long)0L + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(ISVREF(cell_array_qm,
			    (SI_Long)3L),(SI_Long)2L),(SI_Long)0L);
		    temp = ISVREF(display_frame,(SI_Long)8L);
		    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
			    (IFIX(ISVREF(display_frame,(SI_Long)5L)) & 
			    (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
			    && (SI_Long)0L != (IFIX(ISVREF(display_frame,
			    (SI_Long)4L)) & (SI_Long)16777216L) &&  
			    !((SI_Long)0L != (IFIX(ISVREF(display_frame,
			    (SI_Long)4L)) & (SI_Long)8192L))))
			activate_g2_cell_array(cell_array_qm);
		}
		result_1 = Nil;
		current_flag_state_qm = Nil;
		slot_description = 
			get_slot_description_of_class_description_function(Qframe_status_and_notes,
			ISVREF(display_frame,(SI_Long)1L),Nil);
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_stack_change_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_stack_change_cons_pool();
		if (Nil)
		    gensymed_symbol_1 = 
			    nconc2(stack_change_list_2(display_frame,
			    slot_description),stack_change_cons_1(Nil,Nil));
		else {
		    new_cons = ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_stack_change_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_stack_change_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_stack_change_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_stack_change_cons_pool();
		    M_CAR(gensymed_symbol_1) = display_frame;
		    M_CDR(gensymed_symbol_1) = slot_description;
		    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
		}
		M_CAR(gensymed_symbol) = gensymed_symbol_1;
		temp_1 = Stack_of_slot_value_changes;
		M_CDR(gensymed_symbol) = temp_1;
		inline_note_allocate_cons(gensymed_symbol,Qstack_change);
		stack_of_slot_value_changes = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
			0);
		  current_flag_state_qm = (SI_Long)0L != 
			  (IFIX(ISVREF(display_frame,(SI_Long)5L)) & 
			  (SI_Long)16777216L) ? T : Nil;
		  if ( !TRUEP(current_flag_state_qm)) {
		      gensymed_symbol = 
			      ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
			      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
			      (SI_Long)1L);
		      gensymed_symbol_1 = display_frame;
		      gensymed_symbol_2 = Nil;
		      gensymed_symbol_3 = T;
		      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			      gensymed_symbol_2,gensymed_symbol_3);
		      svref_new_value_1 = IFIX(ISVREF(display_frame,
			      (SI_Long)5L)) | (SI_Long)16777216L;
		      ISVREF(display_frame,(SI_Long)5L) = 
			      FIX(svref_new_value_1);
		  }
		  old_current_part_description = Current_part_description;
		  Current_part_description = 
			  get_default_computation_style_of_class();
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      new_cons = ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  temp_1 = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp_1,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_part_stack_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp_1 = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = Nil;
			  }
			  gensymed_symbol = new_cons;
		      }
		      else
			  gensymed_symbol = Nil;
		      if ( !TRUEP(gensymed_symbol))
			  gensymed_symbol = replenish_part_stack_cons_pool();
		      temp_1 = Current_part_description;
		      M_CAR(gensymed_symbol) = temp_1;
		      temp_1 = Stack_of_current_part_descriptions;
		      M_CDR(gensymed_symbol) = temp_1;
		      inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		      Stack_of_current_part_descriptions = gensymed_symbol;
		  }
		  new_cons = ISVREF(Available_part_stack_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp_1 = Available_part_stack_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp_1,svref_arg_2) = svref_new_value;
		      if ( 
			      !TRUEP(ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp_1 = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = Nil;
		      }
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_part_stack_cons_pool();
		  M_CAR(gensymed_symbol) = Qmark;
		  temp_1 = Part_feature_recall_stack;
		  M_CDR(gensymed_symbol) = temp_1;
		  inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		  Part_feature_recall_stack = gensymed_symbol;
		  enter_part_description(Current_part_description);
		  update_computation_style_with_display_settings(Current_computation_style,
			  display_frame);
		  temp = cell_array_qm;
		  sub_class_bit_vector = ISVREF(ISVREF(display_frame,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Readout_table_class_description,
			  (SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
		  if (sub_class_vector_index < 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			      {
		      gensymed_symbol_4 = 
			      UBYTE_8_ISAREF_1(sub_class_bit_vector,
			      sub_class_vector_index);
		      gensymed_symbol_5 = (SI_Long)1L;
		      gensymed_symbol_6 = superior_class_bit_number & 
			      (SI_Long)7L;
		      gensymed_symbol_5 = gensymed_symbol_5 << 
			      gensymed_symbol_6;
		      gensymed_symbol_4 = gensymed_symbol_4 & 
			      gensymed_symbol_5;
		      temp_2 = (SI_Long)0L < gensymed_symbol_4;
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  register_expression_cell_during_compilation(5,temp,
			  FIX((SI_Long)0L),T,expression_qm,temp_2 ? 
			  list_constant_17 : list_constant_18);
		  if ( !EQ(ISVREF(expression_cell_qm,(SI_Long)2L),
			  Qempty_expression_cell)) {
		      update_frame_status(display_frame,Nil,Nil);
		      temp = T;
		  }
		  else {
		      update_frame_status(display_frame,Qbad,Nil);
		      temp = Nil;
		  }
		  part_feature_index = Nil;
		  exit_feature_handler = Nil;
		next_loop:
		  part_stack_pop_store = Nil;
		  cons_1 = Part_feature_recall_stack;
		  if (cons_1) {
		      part_stack_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qpart_stack);
		      if (ISVREF(Available_part_stack_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_1 = 
				  ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp_1) = cons_1;
			  temp_1 = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      else {
			  temp_1 = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
			  temp_1 = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      M_CDR(cons_1) = Nil;
		  }
		  else
		      next_cons = Nil;
		  Part_feature_recall_stack = next_cons;
		  part_feature_index = part_stack_pop_store;
		  if (EQ(part_feature_index,Qmark))
		      goto end_loop;
		  exit_feature_handler = ISVREF(Part_feature_exit_methods,
			  IFIX(part_feature_index));
		  inline_funcall_0(exit_feature_handler);
		  goto next_loop;
		end_loop:;
		  Current_part_description = old_current_part_description;
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      part_stack_pop_store = Nil;
		      cons_1 = Stack_of_current_part_descriptions;
		      if (cons_1) {
			  part_stack_pop_store = M_CAR(cons_1);
			  next_cons = M_CDR(cons_1);
			  inline_note_reclaim_cons(cons_1,Qpart_stack);
			  if (ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_1 = 
				      ISVREF(Available_part_stack_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_1) = cons_1;
			      temp_1 = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = cons_1;
			  }
			  else {
			      temp_1 = Available_part_stack_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = cons_1;
			      temp_1 = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = cons_1;
			  }
			  M_CDR(cons_1) = Nil;
		      }
		      else
			  next_cons = Nil;
		      Stack_of_current_part_descriptions = next_cons;
		  }
		  result_1 = temp;
		  if ( !TRUEP(current_flag_state_qm)) {
		      svref_new_value_1 = IFIX(ISVREF(display_frame,
			      (SI_Long)5L)) &  ~(SI_Long)16777216L;
		      ISVREF(display_frame,(SI_Long)5L) = 
			      FIX(svref_new_value_1);
		      gensymed_symbol = 
			      ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
			      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
			      (SI_Long)1L);
		      gensymed_symbol_1 = display_frame;
		      gensymed_symbol_2 = T;
		      gensymed_symbol_3 = Nil;
		      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			      gensymed_symbol_2,gensymed_symbol_3);
		  }
		  temp_2 = 
			  TRUEP(Suppress_updating_of_slot_value_representations_qm);
		  if (temp_2);
		  else if (M_CDR(Stack_of_slot_value_changes)) {
		      frame_and_slot_or_atom = Nil;
		      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		      ab_loop_it_ = Nil;
		    next_loop_1:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_1;
		      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (ATOM(frame_and_slot_or_atom))
			  goto end_loop_1;
		      temp_2 = EQ(slot_description,
			      M_CDR(frame_and_slot_or_atom));
		      if (temp_2);
		      else {
			  temp = M_CDR(frame_and_slot_or_atom);
			  temp_2 = CONSP(temp) ? EQ(slot_description,
				  SECOND(frame_and_slot_or_atom)) && 
				  EQ(Nil,THIRD(frame_and_slot_or_atom)) && 
				  EQ(Nil,CDDDR(frame_and_slot_or_atom)) : 
				  TRUEP(Nil);
		      }
		      ab_loop_it_ = temp_2 ? (EQ(display_frame,
			      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		      if (ab_loop_it_) {
			  temp_2 = TRUEP(ab_loop_it_);
			  goto end_1;
		      }
		      goto next_loop_1;
		    end_loop_1:
		      temp_2 = TRUEP(Qnil);
		    end_1:;
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if ( !temp_2)
		      update_all_representations_of_slot(display_frame,
			      slot_description,Nil,Nil);
		  if (ISVREF(slot_description,(SI_Long)14L))
		      update_frame_name_references(display_frame);
		  stack_change_pop_store = Nil;
		  cons_1 = Stack_of_slot_value_changes;
		  if (cons_1) {
		      stack_change_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qstack_change);
		      if (ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_1 = 
				  ISVREF(Available_stack_change_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp_1) = cons_1;
			  temp_1 = Available_stack_change_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      else {
			  temp_1 = Available_stack_change_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
			  temp_1 = Available_stack_change_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      M_CDR(cons_1) = Nil;
		  }
		  else
		      next_cons = Nil;
		  Stack_of_slot_value_changes = next_cons;
		  reclaim_stack_change_tree_1(stack_change_pop_store);
		  if (Stack_of_slot_value_changes) {
		      temp = M_CAR(Stack_of_slot_value_changes);
		      temp_2 = ATOM(temp);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2 ?  
			  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			  : TRUEP(Nil))
		      do_deferred_updates_to_representations_in_tables();
		POP_SPECIAL();
		result = VALUES_1(result_1);
	    }
	    else {
		result_1 = Nil;
		current_flag_state_qm = Nil;
		slot_description = 
			get_slot_description_of_class_description_function(Qframe_status_and_notes,
			ISVREF(display_frame,(SI_Long)1L),Nil);
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_stack_change_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_stack_change_cons_pool();
		if (Nil)
		    gensymed_symbol_1 = 
			    nconc2(stack_change_list_2(display_frame,
			    slot_description),stack_change_cons_1(Nil,Nil));
		else {
		    new_cons = ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_stack_change_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_stack_change_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_stack_change_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_stack_change_cons_pool();
		    M_CAR(gensymed_symbol_1) = display_frame;
		    M_CDR(gensymed_symbol_1) = slot_description;
		    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
		}
		M_CAR(gensymed_symbol) = gensymed_symbol_1;
		temp_1 = Stack_of_slot_value_changes;
		M_CDR(gensymed_symbol) = temp_1;
		inline_note_allocate_cons(gensymed_symbol,Qstack_change);
		stack_of_slot_value_changes = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
			0);
		  current_flag_state_qm = (SI_Long)0L != 
			  (IFIX(ISVREF(display_frame,(SI_Long)5L)) & 
			  (SI_Long)16777216L) ? T : Nil;
		  if ( !TRUEP(current_flag_state_qm)) {
		      gensymed_symbol = 
			      ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
			      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
			      (SI_Long)1L);
		      gensymed_symbol_1 = display_frame;
		      gensymed_symbol_2 = Nil;
		      gensymed_symbol_3 = T;
		      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			      gensymed_symbol_2,gensymed_symbol_3);
		      svref_new_value_1 = IFIX(ISVREF(display_frame,
			      (SI_Long)5L)) | (SI_Long)16777216L;
		      ISVREF(display_frame,(SI_Long)5L) = 
			      FIX(svref_new_value_1);
		  }
		  if (cell_array_qm) {
		      temp = ISVREF(display_frame,(SI_Long)8L);
		      if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
			      (IFIX(ISVREF(display_frame,(SI_Long)5L)) & 
			      (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
			      && (SI_Long)0L != (IFIX(ISVREF(display_frame,
			      (SI_Long)4L)) & (SI_Long)16777216L) &&  
			      !((SI_Long)0L != (IFIX(ISVREF(display_frame,
			      (SI_Long)4L)) & (SI_Long)8192L))))
			  deactivate_g2_cell_array(cell_array_qm);
		      result_1 = change_slot_value(3,display_frame,
			      Qcell_array,Nil);
		  }
		  else
		      result_1 = Nil;
		  if ( !TRUEP(current_flag_state_qm)) {
		      svref_new_value_1 = IFIX(ISVREF(display_frame,
			      (SI_Long)5L)) &  ~(SI_Long)16777216L;
		      ISVREF(display_frame,(SI_Long)5L) = 
			      FIX(svref_new_value_1);
		      gensymed_symbol = 
			      ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
			      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
			      (SI_Long)1L);
		      gensymed_symbol_1 = display_frame;
		      gensymed_symbol_2 = T;
		      gensymed_symbol_3 = Nil;
		      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			      gensymed_symbol_2,gensymed_symbol_3);
		  }
		  temp_2 = 
			  TRUEP(Suppress_updating_of_slot_value_representations_qm);
		  if (temp_2);
		  else if (M_CDR(Stack_of_slot_value_changes)) {
		      frame_and_slot_or_atom = Nil;
		      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		      ab_loop_it_ = Nil;
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_2;
		      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (ATOM(frame_and_slot_or_atom))
			  goto end_loop_2;
		      temp_2 = EQ(slot_description,
			      M_CDR(frame_and_slot_or_atom));
		      if (temp_2);
		      else {
			  temp = M_CDR(frame_and_slot_or_atom);
			  temp_2 = CONSP(temp) ? EQ(slot_description,
				  SECOND(frame_and_slot_or_atom)) && 
				  EQ(Nil,THIRD(frame_and_slot_or_atom)) && 
				  EQ(Nil,CDDDR(frame_and_slot_or_atom)) : 
				  TRUEP(Nil);
		      }
		      ab_loop_it_ = temp_2 ? (EQ(display_frame,
			      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		      if (ab_loop_it_) {
			  temp_2 = TRUEP(ab_loop_it_);
			  goto end_2;
		      }
		      goto next_loop_2;
		    end_loop_2:
		      temp_2 = TRUEP(Qnil);
		    end_2:;
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if ( !temp_2)
		      update_all_representations_of_slot(display_frame,
			      slot_description,Nil,Nil);
		  if (ISVREF(slot_description,(SI_Long)14L))
		      update_frame_name_references(display_frame);
		  stack_change_pop_store = Nil;
		  cons_1 = Stack_of_slot_value_changes;
		  if (cons_1) {
		      stack_change_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qstack_change);
		      if (ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_1 = 
				  ISVREF(Available_stack_change_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp_1) = cons_1;
			  temp_1 = Available_stack_change_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      else {
			  temp_1 = Available_stack_change_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
			  temp_1 = Available_stack_change_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      M_CDR(cons_1) = Nil;
		  }
		  else
		      next_cons = Nil;
		  Stack_of_slot_value_changes = next_cons;
		  reclaim_stack_change_tree_1(stack_change_pop_store);
		  if (Stack_of_slot_value_changes) {
		      temp = M_CAR(Stack_of_slot_value_changes);
		      temp_2 = ATOM(temp);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2 ?  
			  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			  : TRUEP(Nil))
		      do_deferred_updates_to_representations_in_tables();
		POP_SPECIAL();
		result = VALUES_1(Nil);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMPILE-LIST-OF-DISPLAY-EXPRESSIONS-FOR-SLOT */
Object compile_list_of_display_expressions_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,61);
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

DEFINE_VARIABLE_WITH_SYMBOL(Graph_expression_uses_local_name_qm, Qgraph_expression_uses_local_name_qm);

static Object Qgraph_expression;   /* graph-expression */

static Object string_constant_53;  /* "Local names are not allowed in display expressions for graphs." */

/* COMPILE-LIST-OF-GRAPH-EXPRESSIONS-FOR-SLOT */
Object compile_list_of_graph_expressions_for_slot varargs_1(int, n)
{
    Object parse_result, graph, slot_name;
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object graph_expression_uses_local_name_qm, current_computation_frame;
    Object problem_qm, compiled_expression_qm;
    Object current_computation_component_particulars;
    Object graph_expression_with_info, ab_loop_list_, collected_compilations;
    Object ab_loopvar_, ab_loopvar__1, ab_loop_iter_flag_;
    Object compiled_graph_expressions;
    Object compiled_expression_or_expressions_with_info, compilation_result;
    Object temp_1, frame_and_slot_or_atom, ab_loop_it_, temp_3;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long expression_index;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(203,62);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    graph = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(graph,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = nconc2(stack_change_list_2(graph,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = graph;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    3);
      graph_expression_uses_local_name_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Graph_expression_uses_local_name_qm,Qgraph_expression_uses_local_name_qm,graph_expression_uses_local_name_qm,
	      2);
	current_computation_frame = graph;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		1);
	  delete_all_frame_notes_for_rule_or_expression(T);
	  if (CONSP(parse_result) && EQ(CAR(parse_result),Qsc)) {
	      problem_qm = Nil;
	      compiled_expression_qm = Nil;
	      current_computation_component_particulars = 
		      slot_value_cons_1(Qgraph_expression,FIX((SI_Long)1L));
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		      0);
		graph_expression_with_info = Nil;
		ab_loop_list_ = CDR(parse_result);
		expression_index = (SI_Long)1L;
		collected_compilations = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loop_iter_flag_ = T;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		graph_expression_with_info = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_))
		    expression_index = expression_index + (SI_Long)1L;
		temp = Current_computation_component_particulars;
		M_CDR(temp) = FIX(expression_index);
		compiled_expression_qm = 
			compile_graph_expression_with_info(graph_expression_with_info);
		if ( !TRUEP(compiled_expression_qm))
		    problem_qm = T;
		ab_loopvar__1 = phrase_cons(compiled_expression_qm,Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    collected_compilations = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		ab_loop_iter_flag_ = Nil;
		goto next_loop;
	      end_loop:
		reclaim_slot_value_cons_1(Current_computation_component_particulars);
		compiled_graph_expressions = problem_qm ? Nil : 
			collected_compilations;
		goto end_1;
		compiled_graph_expressions = Qnil;
	      end_1:;
	      POP_SPECIAL();
	      compiled_expression_or_expressions_with_info = 
		      compiled_graph_expressions ? phrase_cons(Qsc,
		      compiled_graph_expressions) : Nil;
	  }
	  else {
	      current_computation_component_particulars = 
		      slot_value_cons_1(Qgraph_expression,FIX((SI_Long)1L));
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		      0);
		compilation_result = 
			compile_graph_expression_with_info(parse_result);
		reclaim_slot_value_cons_1(Current_computation_component_particulars);
		compiled_expression_or_expressions_with_info = 
			compilation_result;
	      POP_SPECIAL();
	  }
	  if (Graph_expression_uses_local_name_qm) {
	      temp_1 = Bad_phrase;
	      copy_text_string(string_constant_53);
	  }
	  else {
	      if (compiled_expression_or_expressions_with_info)
		  update_frame_status(graph,Nil,Nil);
	      else
		  update_frame_status(graph,Qbad,Nil);
	      temp_1 = compiled_expression_or_expressions_with_info;
	  }
	POP_SPECIAL();
      POP_SPECIAL();
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_2);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop_1;
	  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_2);
	  else {
	      temp_3 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_3) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(graph,M_CAR(frame_and_slot_or_atom)) ?
		   T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_2 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(graph,slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(graph);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp_3 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_3);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
      result = VALUES_1(temp_1);
    POP_SPECIAL();
    return result;
}

/* COMPILE-GRAPH-EXPRESSION-WITH-INFO */
Object compile_graph_expression_with_info(graph_expression_with_info)
    Object graph_expression_with_info;
{
    Object compiled_expression_qm;

    x_note_fn_call(203,63);
    if (CONSP(graph_expression_with_info) && 
	    EQ(CAR(graph_expression_with_info),Qcm)) {
	compiled_expression_qm = 
		compile_expression(SECOND(graph_expression_with_info),Nil,Nil);
	M_SECOND(graph_expression_with_info) = compiled_expression_qm;
	return return_compiled_graph_expression_if_ok(compiled_expression_qm,
		graph_expression_with_info);
    }
    else {
	compiled_expression_qm = 
		compile_expression(graph_expression_with_info,Nil,Nil);
	return return_compiled_graph_expression_if_ok(compiled_expression_qm,
		compiled_expression_qm);
    }
}

static Object Qab_let;             /* let */

/* GRAPH-EXPRESSION-USES-LOCAL-NAME-P */
Object graph_expression_uses_local_name_p(compiled_graph_expression)
    Object compiled_graph_expression;
{
    x_note_fn_call(203,64);
    if (CONSP(compiled_graph_expression))
	return VALUES_1(EQ(CAR(compiled_graph_expression),Qab_let) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* RETURN-COMPILED-GRAPH-EXPRESSION-IF-OK */
Object return_compiled_graph_expression_if_ok(compiled_expression_qm,
	    form_to_return)
    Object compiled_expression_qm, form_to_return;
{
    x_note_fn_call(203,65);
    if (compiled_expression_qm) {
	if (graph_expression_uses_local_name_p(compiled_expression_qm)) {
	    Graph_expression_uses_local_name_qm = T;
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(form_to_return);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-EXPRESSION */
Object write_expression(exp_1)
    Object exp_1;
{
    x_note_fn_call(203,66);
    if (SYMBOLP(exp_1))
	return twrite(exp_1);
    else
	return write_exp(exp_1,FIX((SI_Long)0L));
}

Object Precedence_table = UNBOUND;

static Object string_constant_54;  /* "~s" */

static Object string_constant_55;  /* "!!!" */

static Object Qevaluator_form_writer;  /* evaluator-form-writer */

static Object Qop;                 /* \( */

static Object Qcp;                 /* \) */

/* WRITE-EXP */
Object write_exp(exp_1,external_precedence)
    Object exp_1, external_precedence;
{
    Object temp, thing, temporary_for_writing, op, op_precedence, form_writer;
    Object listed_arg;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,67);
    if (SYMBOLP(exp_1))
	return twrite_symbol(1,exp_1);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(exp_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(exp_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    write_floating_point_number_simple_c_format(1,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(exp_1,
		    (SI_Long)0L)));
	    result = VALUES_1(Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (FLOATP(exp_1))
	return write_floating_point_number_simple_c_format(1,exp_1);
    else if (NUMBERP(exp_1))
	return twrite(exp_1);
    else if (text_string_p(exp_1))
	return tformat(2,string_constant_54,exp_1);
    else if (ATOM(exp_1))
	return twrite(string_constant_55);
    else {
	temp = CAR(exp_1);
	if (NUMBERP(temp))
	    return print_constant(2,CAR(exp_1),CDR(exp_1));
	else {
	    thing = CAR(exp_1);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    print_constant(2,
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(CAR(exp_1),
			    (SI_Long)0L)),CDR(exp_1));
		    result = VALUES_1(Nil);
		}
		POP_LOCAL_ALLOCATION(0,0);
		return result;
	    }
	    else if (CONSP(exp_1) && (CONSP(exp_1) && EQ(M_CDR(exp_1),
		    Qsequence) || CONSP(exp_1) && EQ(M_CDR(exp_1),
		    Qab_structure)))
		return write_evaluation_value(1,exp_1);
	    else if (CONSP(exp_1) && (CONSP(exp_1) && EQ(M_CDR(exp_1),
		    Phrase_structure_marker) || CONSP(exp_1) && 
		    EQ(M_CDR(exp_1),Phrase_sequence_marker))) {
		temporary_for_writing = copy_for_slot_value(exp_1);
		write_exp(temporary_for_writing,FIX((SI_Long)0L));
		return reclaim_slot_value(temporary_for_writing);
	    }
	    else {
		op = CAR(exp_1);
		temp = assq_function(op,Precedence_table);
		op_precedence = CDR(temp);
		form_writer = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(op),
			Qevaluator_form_writer);
		if (op_precedence) {
		    if ( !NUM_GT(op_precedence,external_precedence))
			twrite(Qop);
		    write_infix_or_prefix_expression(op,CDR(exp_1),
			    op_precedence);
		    if ( !NUM_GT(op_precedence,external_precedence))
			return twrite(Qcp);
		    else
			return VALUES_1(Nil);
		}
		else if (ATOM(exp_1) ? exp_1 && SYMBOLP(exp_1) : 
			TRUEP(designation_operator_or_giver_of_value_p(CAR(exp_1))))
		    return print_designation(exp_1);
		else if (form_writer)
		    return FUNCALL_1(form_writer,exp_1);
		else {
		    twrite_symbol(1,CAR(exp_1));
		    twrite(Qop);
		    listed_arg = CDR(exp_1);
		  next_loop:
		    if ( !TRUEP(listed_arg))
			goto end_loop;
		    write_exp(CAR(listed_arg),FIX((SI_Long)0L));
		    if (CDR(listed_arg))
			twrite(string_constant_6);
		    listed_arg = M_CDR(listed_arg);
		    goto next_loop;
		  end_loop:;
		    return twrite(Qcp);
		}
	    }
	}
    }
}

static Object string_constant_56;  /* " " */

/* WRITE-INFIX-OR-PREFIX-EXPRESSION */
Object write_infix_or_prefix_expression(op,args,op_precedence)
    Object op, args, op_precedence;
{
    Object listed_arg;

    x_note_fn_call(203,68);
    if ( !TRUEP(CDR(args))) {
	twrite(op);
	twrite(string_constant_56);
	return write_exp(CAR(args),op_precedence);
    }
    else {
	listed_arg = args;
      next_loop:
	if ( !TRUEP(listed_arg))
	    goto end_loop;
	write_exp(CAR(listed_arg),op_precedence);
	if (CDR(listed_arg)) {
	    twrite(string_constant_56);
	    twrite(op);
	    twrite(string_constant_56);
	}
	listed_arg = M_CDR(listed_arg);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_57;  /* "date outside of legal range" */

/* TRANSFORM-INPUT-PHRASE-INTO-UNIVERSAL-DATE */
Object transform_input_phrase_into_universal_date(list_1)
    Object list_1;
{
    Object temp;

    x_note_fn_call(203,69);
    temp = convert_input_to_universal_date(list_1);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_2(Bad_phrase,string_constant_57);
}

/* COMPILE-DATE?-FOR-SLOT */
Object compile_date_qm_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,70);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(translation,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(translation);
}

/* WRITE-DATE?-FROM-SLOT */
Object write_date_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object day, month, year;
    Object result;

    x_note_fn_call(203,71);
    if ( !TRUEP(value))
	return twrite(string_constant_18);
    else {
	result = decode_universal_date(value);
	MVS_3(result,day,month,year);
	return print_decoded_date(day,month,year);
    }
}

/* COMPILE-CHARTING-LIBRARY-TYPE-SELECT-FOR-SLOT */
Object compile_charting_library_type_select_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,72);
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

static Object Qgigasoft;           /* gigasoft */

static Object string_constant_58;  /* "gigasoft" */

static Object Qjfreechart;         /* jfreechart */

static Object string_constant_59;  /* "jfreechart" */

/* WRITE-CHARTING-LIBRARY-TYPE-SELECT-FROM-SLOT */
Object write_charting_library_type_select_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,73);
    if (EQ(value,Qgigasoft))
	return twrite(string_constant_58);
    else if (EQ(value,Qjfreechart))
	return twrite(string_constant_59);
    else
	return twrite(string_constant_58);
}

static Object list_constant_19;    /* # */

static Object list_constant_20;    /* # */

/* CHARTING-LIBRARY-TYPE-SELECT-EVALUATION-SETTER */
Object charting_library_type_select_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,74);
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
			  list_constant_19))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_20,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_charting_library_type_select_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_charting_library_type_select_evaluation_setter:
    return result;
}

/* CHARTING-LIBRARY-TYPE-SELECT-EVALUATION-GETTER */
Object charting_library_type_select_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,75);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object string_constant_60;  /* "~f seconds" */

static Object string_constant_61;  /* "never" */

/* WRITE-DEADLOCK-DETECTION-FREQUENCY-TYPE-FROM-SLOT */
Object write_deadlock_detection_frequency_type_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,76);
    if (FIXNUMP(value))
	return tformat(2,string_constant_60,value);
    else if ( !TRUEP(value))
	return tformat(1,string_constant_61);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_21;    /* # */

static Object list_constant_22;    /* # */

static Object Qnever;              /* never */

/* DEADLOCK-DETECTION-FREQUENCY-TYPE-EVALUATION-SETTER */
Object deadlock_detection_frequency_type_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,77);
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
			  list_constant_21))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_22,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_deadlock_detection_frequency_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qnever))
	result = VALUES_1(Qnever);
    else
	result = phrase_cons(evaluation_value,Qseconds);
  end_deadlock_detection_frequency_type_evaluation_setter:
    return result;
}

/* DEADLOCK-DETECTION-FREQUENCY-TYPE-EVALUATION-GETTER */
Object deadlock_detection_frequency_type_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,78);
    GENSYM_RETURN_ONE(EQ(slot_value,Qnil) ? Qnever : slot_value);
    return VALUES_1(Nil);
}

static Object string_constant_62;  /* "The interval must be at least 1 second" */

/* COMPILE-DEADLOCK-DETECTION-FREQUENCY-TYPE-FOR-SLOT */
Object compile_deadlock_detection_frequency_type_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,79);
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
    if (EQ(parse_result,Qnever))
	return VALUES_1(Nil);
    else if ( !((SI_Long)0L < IFIX(CAR(parse_result)))) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_62);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(CAR(parse_result));
}

/* PUT-AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY */
Object put_automatic_deadlock_detection_frequency(miscellaneous_parameters_frame,
	    new_value,gensymed_symbol)
    Object miscellaneous_parameters_frame, new_value, gensymed_symbol;
{
    x_note_fn_call(203,80);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(miscellaneous_parameters_frame,
		Qautomatic_deadlock_detection_frequency);
    SVREF(miscellaneous_parameters_frame,FIX((SI_Long)29L)) = new_value;
    if (EQ(Miscellaneous_parameters,miscellaneous_parameters_frame))
	set_deadlock_detection_frequency(new_value,Nil);
    return VALUES_1(new_value);
}

/* ACTIVATE-FOR-MISCELLANEOUS-PARAMETERS */
Object activate_for_miscellaneous_parameters(miscellaneous_parameters)
    Object miscellaneous_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(203,81);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    0);
      if (system_table_installed_p(Miscellaneous_parameters))
	  result = set_deadlock_detection_frequency(ISVREF(Miscellaneous_parameters,
		  (SI_Long)29L),T);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qconnection_caching_enabled_qm;  /* connection-caching-enabled? */

/* INSTALL-SYSTEM-TABLE-FOR-MISCELLANEOUS-PARAMETERS */
Object install_system_table_for_miscellaneous_parameters(miscellaneous_parameters)
    Object miscellaneous_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(203,82);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    0);
      use_role_caching(get_lookup_slot_value_given_default(Miscellaneous_parameters,
	      Qconnection_caching_enabled_qm,Nil));
      Cached_name_for_local_home = Nil;
      if (Servicing_workstation_qm)
	  reset_current_workstation_new_g2_classic_ui_p();
      set_deadlock_detection_frequency(ISVREF(Miscellaneous_parameters,
	      (SI_Long)29L),Nil);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-MISCELLANEOUS-PARAMETERS */
Object deinstall_system_table_for_miscellaneous_parameters(miscellaneous_parameters)
    Object miscellaneous_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(203,83);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    0);
      use_role_caching(Nil);
      Cached_name_for_local_home = Nil;
      if (Servicing_workstation_qm)
	  reset_current_workstation_new_g2_classic_ui_p();
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qbackward_compatibility_features;  /* backward-compatibility-features */

static Object Qright_click_lifts_to_top_in_native_ui;  /* right-click-lifts-to-top-in-native-ui */

/* PUT-BACKWARD-COMPATIBILITY-FEATURES */
Object put_backward_compatibility_features(miscellaneous_parameters,value,
	    gensymed_symbol)
    Object miscellaneous_parameters, value, gensymed_symbol;
{
    Object svref_arg_1, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(203,84);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Miscellaneous_parameters,
		  Qbackward_compatibility_features);
      svref_arg_1 = Miscellaneous_parameters;
      svref_new_value = 
	      delete_slot_value_element_1(Qright_click_lifts_to_top_in_native_ui,
	      value);
      SVREF(svref_arg_1,FIX((SI_Long)26L)) = svref_new_value;
      result = VALUES_1(value);
    POP_SPECIAL();
    return result;
}

/* PUT-CONNECTION-CACHING-ENABLED? */
Object put_connection_caching_enabled_qm(miscellaneous_parameters,value,
	    gensymed_symbol)
    Object miscellaneous_parameters, value, gensymed_symbol;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(203,85);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    0);
      if (system_table_installed_p(Miscellaneous_parameters))
	  use_role_caching(value);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Miscellaneous_parameters,
		  Qconnection_caching_enabled_qm);
      result = set_lookup_slot_value_1(Miscellaneous_parameters,
	      Qconnection_caching_enabled_qm,value);
    POP_SPECIAL();
    return result;
}

/* START-KB-AFTER-LOAD-FROM-SYSTEM-TABLE? */
Object start_kb_after_load_from_system_table_qm()
{
    x_note_fn_call(203,86);
    return VALUES_1(ISVREF(Miscellaneous_parameters,(SI_Long)24L));
}

/* FLOAT-TO-TEXT-DEFAULT-FORMAT-FROM-SYSTEM-TABLE */
Object float_to_text_default_format_from_system_table()
{
    x_note_fn_call(203,87);
    return VALUES_1(ISVREF(Miscellaneous_parameters,(SI_Long)30L));
}

static Object Qallow_only_one_table_display_for_item_qm;  /* allow-only-one-table-display-for-item? */

/* ALLOW-ONLY-ONE-TABLE-DISPLAY-FOR-ITEM?-FROM-SYSTEM-TABLE */
Object allow_only_one_table_display_for_item_qm_from_system_table()
{
    x_note_fn_call(203,88);
    return get_lookup_slot_value_given_default(Miscellaneous_parameters,
	    Qallow_only_one_table_display_for_item_qm,Nil);
}

/* FLOAT-TO-TEXT-DEFAULT-PRECISION-FROM-SYSTEM-TABLE */
Object float_to_text_default_precision_from_system_table()
{
    x_note_fn_call(203,89);
    return VALUES_1(ISVREF(Miscellaneous_parameters,(SI_Long)31L));
}

static Object Qexplanation_related_features_enabled_qm;  /* explanation-related-features-enabled? */

/* EXPLANATION-RELATED-FEATURES-ENABLED-FUNC? */
Object explanation_related_features_enabled_func_qm()
{
    Object temp;

    x_note_fn_call(203,90);
    temp = get_lookup_slot_value_given_default(Miscellaneous_parameters,
	    Qexplanation_related_features_enabled_qm,Nil);
    return VALUES_1(temp);
}

/* WRITE-G2-RUN-STATE-FROM-SLOT */
Object write_g2_run_state_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,91);
    return twrite_symbol(1,value);
}

/* G2-RUN-STATE-EVALUATION-GETTER */
Object g2_run_state_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,92);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qg2_run_state;       /* g2-run-state */

/* UPDATE-G2-RUN-STATE */
Object update_g2_run_state()
{
    Object run_state, scope_conses, ab_loopvar_, ab_loopvar__1, system_frame;
    char temp;
    Declare_special(1);

    x_note_fn_call(203,93);
    run_state = current_g2_run_state();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    system_frame = Nil;
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
      system_frame = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      change_slot_value(3,system_frame,Qg2_run_state,run_state);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qconfirm_run_state_changes;  /* confirm-run-state-changes */

/* CONFIRM-RUN-STATE-CHANGES-P */
Object confirm_run_state_changes_p()
{
    x_note_fn_call(203,94);
    return get_lookup_slot_value_given_default(Miscellaneous_parameters,
	    Qconfirm_run_state_changes,Nil);
}

static Object list_constant_23;    /* # */

static Object list_constant_24;    /* # */

/* BACKWARD-COMPATIBLE-G2-FEATURE-LIST-EVALUATION-SETTER */
Object backward_compatible_g2_feature_list_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,95);
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
			  list_constant_23))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_24,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_backward_compatible_g2_feature_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),Qsequence)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	ab_loopvar__2 = phrase_cons(element,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	result = VALUES_1(ab_loopvar_);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    else
	result = VALUES_1(evaluation_value);
  end_backward_compatible_g2_feature_list_evaluation_setter:
    return result;
}

/* BACKWARD-COMPATIBLE-G2-FEATURE-LIST-EVALUATION-GETTER */
Object backward_compatible_g2_feature_list_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,96);
    GENSYM_RETURN_ONE(slot_value ? 
	    allocate_evaluation_sequence(copy_list_using_eval_conses_1(slot_value)) 
	    : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_25;    /* # */

/* INITIAL-MARGIN-FOR-WORKSPACES-EVALUATION-SETTER */
Object initial_margin_for_workspaces_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,97);
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
			  list_constant_25))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_initial_margin_for_workspaces_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_initial_margin_for_workspaces_evaluation_setter:
    return result;
}

/* INITIAL-MARGIN-FOR-WORKSPACES-EVALUATION-GETTER */
Object initial_margin_for_workspaces_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,98);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object string_constant_63;  /* "~d" */

/* WRITE-INITIAL-MARGIN-FOR-WORKSPACES-FROM-SLOT */
Object write_initial_margin_for_workspaces_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,99);
    return tformat(2,string_constant_63,value);
}

/* WRITE-INITIAL-WIDTH-OR-HEIGHT-FOR-WORKSPACES-FROM-SLOT */
Object write_initial_width_or_height_for_workspaces_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,100);
    return tformat(2,string_constant_63,value);
}

/* COMPILE-BACKWARD-COMPATIBLE-G2-FEATURE-LIST-FOR-SLOT */
Object compile_backward_compatible_g2_feature_list_for_slot varargs_1(int, n)
{
    Object parse_result, variable_or_definition, gensymed_symbol;
    Object result_1, an_item, ab_loop_list_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,101);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    variable_or_definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    result_1 = Nil;
    an_item = Nil;
    ab_loop_list_ = parse_result;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    an_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(EQ(an_item,Qcm) || memq_function(an_item,result_1)))
	result_1 = phrase_cons(an_item,result_1);
    goto next_loop;
  end_loop:;
    return nreverse(result_1);
}

static Object Qignore_duplicate_list_element_error;  /* ignore-duplicate-list-element-error */

static Object string_constant_64;  /* "ignore duplicate list element error" */

static Object Qextra_vertices_in_g2_get_connection_vertices;  /* extra-vertices-in-g2-get-connection-vertices */

static Object string_constant_65;  /* "extra vertices in g2-get-connection-vertices" */

static Object Qprint_means_print_to_server_in_configurations;  /* print-means-print-to-server-in-configurations */

static Object string_constant_66;  /* "print means print-to-server in configurations" */

static Object Qinconsistent_behavior_of_move_in_configurations;  /* inconsistent-behavior-of-move-in-configurations */

static Object string_constant_67;  /* "inconsistent behavior of move in configurations" */

static Object Qignore_snap_grid_in_transfer_operations;  /* ignore-snap-grid-in-transfer-operations */

static Object string_constant_68;  /* "ignore snap grid in transfer operations" */

static Object Qfirst_value_ok_for_the_named_by_grammar;  /* first-value-ok-for-the-named-by-grammar */

static Object string_constant_69;  /* "first value ok for the named-by grammar" */

static Object string_constant_70;  /* "unknown" */

/* TWRITE-BACKWARD-COMPATIBLE-G2-FEATURE-LIST-ITEM */
Object twrite_backward_compatible_g2_feature_list_item(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(203,102);
    if (EQ(symbol,Qignore_duplicate_list_element_error))
	temp = tformat(1,string_constant_64);
    else if (EQ(symbol,Qextra_vertices_in_g2_get_connection_vertices))
	temp = tformat(1,string_constant_65);
    else if (EQ(symbol,Qprint_means_print_to_server_in_configurations))
	temp = tformat(1,string_constant_66);
    else if (EQ(symbol,Qinconsistent_behavior_of_move_in_configurations))
	temp = tformat(1,string_constant_67);
    else if (EQ(symbol,Qignore_snap_grid_in_transfer_operations))
	temp = tformat(1,string_constant_68);
    else if (EQ(symbol,Qfirst_value_ok_for_the_named_by_grammar))
	temp = tformat(1,string_constant_69);
    else
	temp = twrite(string_constant_70);
    return VALUES_1(temp);
}

static Object Qtwrite_backward_compatible_g2_feature_list_item;  /* twrite-backward-compatible-g2-feature-list-item */

/* WRITE-BACKWARD-COMPATIBLE-G2-FEATURE-LIST-FROM-SLOT */
Object write_backward_compatible_g2_feature_list_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,103);
    return twrite_list_function(value,
	    SYMBOL_FUNCTION(Qtwrite_backward_compatible_g2_feature_list_item),
	    string_constant_18,string_constant_6,string_constant_6);
}

/* INSERT-ACTION-DUPLICATE-ELEMENT-BACKWARD-COMPATIBILITY-P */
Object insert_action_duplicate_element_backward_compatibility_p()
{
    x_note_fn_call(203,104);
    return memq_function(Qignore_duplicate_list_element_error,
	    ISVREF(Miscellaneous_parameters,(SI_Long)26L));
}

/* SET-IGNORE-INSERT-ACTION-DUPLICATE-ELEMENT */
Object set_ignore_insert_action_duplicate_element()
{
    Object svref_arg_1, car_1, cdr_1, key_result, x_element, ab_loop_list_;
    Object ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(203,105);
    svref_arg_1 = Miscellaneous_parameters;
    car_1 = Qignore_duplicate_list_element_error;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)26L);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    svref_new_value = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qbackward_compatibility_features);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)26L)) = svref_new_value);
}

/* GET-CONNECTION-VERTICES-BACKWARD-COMPATIBILITY-P */
Object get_connection_vertices_backward_compatibility_p()
{
    x_note_fn_call(203,106);
    return memq_function(Qextra_vertices_in_g2_get_connection_vertices,
	    ISVREF(Miscellaneous_parameters,(SI_Long)26L));
}

/* SET-GET-CONNECTION-VERTICES-BACKWARD-COMPATIBILITY */
Object set_get_connection_vertices_backward_compatibility()
{
    Object svref_arg_1, car_1, cdr_1, key_result, x_element, ab_loop_list_;
    Object ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(203,107);
    svref_arg_1 = Miscellaneous_parameters;
    car_1 = Qextra_vertices_in_g2_get_connection_vertices;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)26L);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    svref_new_value = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qbackward_compatibility_features);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)26L)) = svref_new_value);
}

/* PRINT-MEANS-PRINT-TO-SERVER-IN-CONFIGURATIONS-P */
Object print_means_print_to_server_in_configurations_p()
{
    x_note_fn_call(203,108);
    return memq_function(Qprint_means_print_to_server_in_configurations,
	    ISVREF(Miscellaneous_parameters,(SI_Long)26L));
}

/* SET-PRINT-MEANS-PRINT-TO-SERVER-IN-CONFIGURATIONS */
Object set_print_means_print_to_server_in_configurations()
{
    Object svref_arg_1, car_1, cdr_1, key_result, x_element, ab_loop_list_;
    Object ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(203,109);
    svref_arg_1 = Miscellaneous_parameters;
    car_1 = Qprint_means_print_to_server_in_configurations;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)26L);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    svref_new_value = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qbackward_compatibility_features);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)26L)) = svref_new_value);
}

/* INCONSISTENT-BEHAVIOR-OF-MOVE-IN-CONFIGURATIONS-P */
Object inconsistent_behavior_of_move_in_configurations_p()
{
    x_note_fn_call(203,110);
    return memq_function(Qinconsistent_behavior_of_move_in_configurations,
	    ISVREF(Miscellaneous_parameters,(SI_Long)26L));
}

/* SET-INCONSISTENT-BEHAVIOR-OF-MOVE-IN-CONFIGURATIONS */
Object set_inconsistent_behavior_of_move_in_configurations()
{
    Object svref_arg_1, car_1, cdr_1, key_result, x_element, ab_loop_list_;
    Object ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(203,111);
    svref_arg_1 = Miscellaneous_parameters;
    car_1 = Qinconsistent_behavior_of_move_in_configurations;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)26L);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    svref_new_value = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qbackward_compatibility_features);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)26L)) = svref_new_value);
}

/* IGNORE-SNAP-GRID-IN-TRANSFER-OPERATIONS-P */
Object ignore_snap_grid_in_transfer_operations_p()
{
    x_note_fn_call(203,112);
    return memq_function(Qignore_snap_grid_in_transfer_operations,
	    ISVREF(Miscellaneous_parameters,(SI_Long)26L));
}

/* SET-IGNORE-SNAP-GRID-IN-TRANSFER-OPERATIONS */
Object set_ignore_snap_grid_in_transfer_operations()
{
    Object svref_arg_1, car_1, cdr_1, key_result, x_element, ab_loop_list_;
    Object ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(203,113);
    svref_arg_1 = Miscellaneous_parameters;
    car_1 = Qignore_snap_grid_in_transfer_operations;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)26L);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    svref_new_value = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qbackward_compatibility_features);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)26L)) = svref_new_value);
}

/* FIRST-VALUE-OK-FOR-THE-NAMED-BY-GRAMMAR-P */
Object first_value_ok_for_the_named_by_grammar_p()
{
    x_note_fn_call(203,114);
    return memq_function(Qfirst_value_ok_for_the_named_by_grammar,
	    ISVREF(Miscellaneous_parameters,(SI_Long)26L));
}

/* SET-FIRST-VALUE-OK-FOR-THE-NAMED-BY-GRAMMAR */
Object set_first_value_ok_for_the_named_by_grammar()
{
    Object svref_arg_1, car_1, cdr_1, key_result, x_element, ab_loop_list_;
    Object ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(203,115);
    svref_arg_1 = Miscellaneous_parameters;
    car_1 = Qfirst_value_ok_for_the_named_by_grammar;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)26L);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    svref_new_value = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qbackward_compatibility_features);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)26L)) = svref_new_value);
}

static Object Qab_standard;        /* standard */

static Object Qkb_workspace;       /* kb-workspace */

static Object Qworkspace_margin;   /* workspace-margin */

static Object string_constant_71;  /* "Please choose an integer between 0 and 100." */

/* COMPILE-INITIAL-MARGIN-FOR-WORKSPACES-FOR-SLOT */
Object compile_initial_margin_for_workspaces_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,116);
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
    if (EQ(parse_result,Qab_standard))
	return get_slot_init_form(2,Qkb_workspace,Qworkspace_margin);
    else if (IFIX(parse_result) < (SI_Long)0L || IFIX(parse_result) > 
	    (SI_Long)100L) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_71);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

/* REPEAT-RANDOM-FUNCTION-ON-RESET?-FUNCTION */
Object repeat_random_function_on_reset_qm_function(miscellaneous_parameters)
    Object miscellaneous_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(203,117);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    0);
      result = VALUES_1(ISVREF(Miscellaneous_parameters,(SI_Long)22L));
    POP_SPECIAL();
    return result;
}

static Object Qinlineable;         /* inlineable */

/* BLOCK-CAN-BE-INLINED-P */
Object block_can_be_inlined_p(block)
    Object block;
{
    x_note_fn_call(203,118);
    if (Miscellaneous_parameters && ISVREF(Miscellaneous_parameters,
	    (SI_Long)35L))
	return VALUES_1(Nil);
    else
	return get_property_value_in_object_configuration(block,
		Qinlineable,Nil);
}

static Object Qdefault_window_style;  /* default-window-style */

/* PUT-DEFAULT-WINDOW-STYLE */
Object put_default_window_style(miscellaneous_parameters,value,initializing_p)
    Object miscellaneous_parameters, value, initializing_p;
{
    Object svref_arg_1, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(203,119);
    PUSH_SPECIAL_WITH_SYMBOL(Miscellaneous_parameters,Qmiscellaneous_parameters,miscellaneous_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Miscellaneous_parameters,
		  Qdefault_window_style);
      svref_arg_1 = Miscellaneous_parameters;
      temp = SVREF(svref_arg_1,FIX((SI_Long)27L)) = value;
      if (Servicing_workstation_qm &&  !TRUEP(initializing_p) && 
	      system_table_installed_p(Miscellaneous_parameters))
	  reset_current_workstation_new_g2_classic_ui_p();
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* COMPILE-FLOATING-POINT-NUMBER-TEXT-STYLE-NAME-FOR-SLOT */
Object compile_floating_point_number_text_style_name_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,120);
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

static Object string_constant_72;  /* "float" */

static Object Qexponent;           /* exponent */

static Object string_constant_73;  /* "exponent" */

static Object Qbest;               /* best */

static Object string_constant_74;  /* "best" */

static Object Qforce_zero;         /* force-zero */

static Object string_constant_75;  /* "force-zero" */

/* WRITE-FLOATING-POINT-NUMBER-TEXT-STYLE-NAME-FROM-SLOT */
Object write_floating_point_number_text_style_name_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,121);
    if (EQ(value,Qdefault))
	return twrite(string_constant_31);
    else if (EQ(value,Qfloat))
	return twrite(string_constant_72);
    else if (EQ(value,Qexponent))
	return twrite(string_constant_73);
    else if (EQ(value,Qbest))
	return twrite(string_constant_74);
    else if (EQ(value,Qforce_zero))
	return twrite(string_constant_75);
    else
	return twrite(string_constant_18);
}

static Object list_constant_26;    /* # */

static Object list_constant_27;    /* # */

/* FLOATING-POINT-NUMBER-TEXT-STYLE-NAME-EVALUATION-SETTER */
Object floating_point_number_text_style_name_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,122);
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
			  list_constant_26))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_27,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_floating_point_number_text_style_name_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_floating_point_number_text_style_name_evaluation_setter:
    return result;
}

/* FLOATING-POINT-NUMBER-TEXT-STYLE-NAME-EVALUATION-GETTER */
Object floating_point_number_text_style_name_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,123);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object string_constant_76;  /* "Floating point number precision must be a number between 0 and 16." */

/* COMPILE-FLOATING-POINT-NUMBER-PRECISION-FOR-SLOT */
Object compile_floating_point_number_precision_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(203,124);
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
    if ( !((SI_Long)0L <= IFIX(parse_result) && IFIX(parse_result) <= 
	    (SI_Long)16L)) {
	temp = Bad_phrase;
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
		  tformat(1,string_constant_76);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

/* WRITE-FLOATING-POINT-NUMBER-PRECISION-FROM-SLOT */
Object write_floating_point_number_precision_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(203,125);
    return twrite(value);
}

static Object list_constant_28;    /* # */

static Object list_constant_29;    /* # */

static Object Qnon_negative_integer;  /* non-negative-integer */

/* FLOATING-POINT-NUMBER-PRECISION-EVALUATION-SETTER */
Object floating_point_number_precision_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,126);
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
			  list_constant_28))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_29,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_floating_point_number_precision_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnon_negative_integer),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_floating_point_number_precision_evaluation_setter:
    return result;
}

/* FLOATING-POINT-NUMBER-PRECISION-EVALUATION-GETTER */
Object floating_point_number_precision_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,127);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnon_negative_integer),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-LOG-FILE-DIRECTORY-FROM-SLOT */
Object write_log_file_directory_from_slot(thing,gensymed_symbol)
    Object thing, gensymed_symbol;
{
    x_note_fn_call(203,128);
    if ( !TRUEP(thing))
	return twrite(Qdefault);
    else
	return twrite_parsably(thing);
}

static Object list_constant_30;    /* # */

static Object list_constant_31;    /* # */

static Object Qwhole_string;       /* whole-string */

/* LOG-FILE-DIRECTORY-EVALUATION-SETTER */
Object log_file_directory_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,129);
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
			  list_constant_30))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_31,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_log_file_directory_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qdefault))
	result = VALUES_1(evaluation_value);
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
  end_log_file_directory_evaluation_setter:
    return result;
}

/* LOG-FILE-DIRECTORY-EVALUATION-GETTER */
Object log_file_directory_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,130);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Qdefault;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

/* COMPILE-LOG-FILE-DIRECTORY-FOR-SLOT */
Object compile_log_file_directory_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(203,131);
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
    if (Log_file_outputting_qm || ISVREF(Log_file_parameters,(SI_Long)22L)) {
	temp = Bad_phrase;
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
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)56L));
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp,temp_1);
    }
    else if (EQ(parse_result,Qdefault))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object array_constant_6;    /* # */

/* WRITE-LOG-FILE-NAME-FROM-SLOT */
Object write_log_file_name_from_slot(thing,gensymed_symbol)
    Object thing, gensymed_symbol;
{
    x_note_fn_call(203,132);
    return tformat(2,string_constant_54,text_string_p(thing) ? thing : 
	    array_constant_6);
}

static Object list_constant_32;    /* # */

static Object list_constant_33;    /* # */

/* LOG-FILE-NAME-EVALUATION-SETTER */
Object log_file_name_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,133);
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
			  list_constant_32))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_33,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_log_file_name_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_log_file_name_evaluation_setter:
    return result;
}

/* LOG-FILE-NAME-EVALUATION-GETTER */
Object log_file_name_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,134);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = text_string_p(slot_value) ? slot_value : 
		array_constant_6;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-LOG-FILE-NAME-FOR-SLOT */
Object compile_log_file_name_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(203,135);
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
    if (Log_file_outputting_qm || ISVREF(Log_file_parameters,(SI_Long)22L)) {
	temp = Bad_phrase;
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
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)56L));
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

/* WRITE-LOG-FILE-MAXIMUM-FROM-SLOT */
Object write_log_file_maximum_from_slot(thing,gensymed_symbol)
    Object thing, gensymed_symbol;
{
    x_note_fn_call(203,136);
    if ( !TRUEP(thing))
	return twrite(Qnone);
    else
	return twrite(thing);
}

static Object list_constant_34;    /* # */

static Object list_constant_35;    /* # */

static Object Qpositive_integer_qm;  /* positive-integer? */

/* LOG-FILE-MAXIMUM-EVALUATION-SETTER */
Object log_file_maximum_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,137);
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
			  list_constant_34))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_35,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_log_file_maximum_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_integer_qm),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_log_file_maximum_evaluation_setter:
    return result;
}

/* LOG-FILE-MAXIMUM-EVALUATION-GETTER */
Object log_file_maximum_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,138);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_integer_qm),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_77;  /* "The maximum number of log files must be either none or a number ~
				    *             between 1 and 999."
				    */

/* COMPILE-LOG-FILE-MAXIMUM-FOR-SLOT */
Object compile_log_file_maximum_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(203,139);
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
    else if ( !((SI_Long)0L < IFIX(parse_result) && IFIX(parse_result) < 
	    (SI_Long)1000L)) {
	temp = Bad_phrase;
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
		  tformat(1,string_constant_77);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

static Object list_constant_36;    /* # */

static Object list_constant_37;    /* # */

static Object Qafter_messages;     /* after-messages */

static Object Qafter_interval;     /* after-interval */

/* UPDATE-LOG-FILE-EVALUATION-SETTER */
Object update_log_file_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,140);
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
			  list_constant_36))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_37,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_update_log_file_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	gensymed_symbol = evaluation_value;
	temp_1 = estructure_slot(gensymed_symbol,Qafter_messages,Nil) ? 
		phrase_cons(estructure_slot(gensymed_symbol,
		Qafter_messages,Nil),Nil) : Nil;
	result = VALUES_1(nconc2(temp_1,estructure_slot(gensymed_symbol,
		Qafter_interval,Nil) ? 
		phrase_cons(phrase_cons(estructure_slot(gensymed_symbol,
		Qafter_interval,Nil),Qseconds),Nil) : Nil));
    }
    else
	result = VALUES_1(Nil);
  end_update_log_file_evaluation_setter:
    return result;
}

/* UPDATE-LOG-FILE-EVALUATION-GETTER */
Object update_log_file_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, value_1_qm, value_2_qm, source_maximum_interval;
    Object source_maximum_messages, value, temp;
    char interval_first_qm;

    x_note_fn_call(203,141);
    gensymed_symbol = slot_value;
    value_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_2_qm = CAR(gensymed_symbol);
    interval_first_qm = CONSP(value_1_qm);
    if (interval_first_qm)
	source_maximum_interval = M_CAR(value_1_qm);
    else if (value_2_qm)
	source_maximum_interval = M_CAR(value_2_qm);
    else
	source_maximum_interval = Nil;
    source_maximum_messages =  !interval_first_qm ? value_1_qm : value_2_qm;
    if (source_maximum_messages || source_maximum_interval) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	value = source_maximum_messages;
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol,Qafter_messages,
		    value);
	value = source_maximum_interval;
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol,Qafter_interval,
		    value);
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-CLOSE-LOG-FILE-FROM-SLOT */
Object write_close_log_file_from_slot(message_count_and_interval,
	    gensymed_symbol)
    Object message_count_and_interval, gensymed_symbol;
{
    x_note_fn_call(203,142);
    return update_log_file_slot_value_writer(message_count_and_interval);
}

static Object list_constant_38;    /* # */

static Object Qupdate_log_file;    /* update-log-file */

/* CLOSE-LOG-FILE-EVALUATION-SETTER */
Object close_log_file_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,143);
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
			  list_constant_38))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_36,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_close_log_file_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_log_file),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_close_log_file_evaluation_setter:
    return result;
}

/* CLOSE-LOG-FILE-EVALUATION-GETTER */
Object close_log_file_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,144);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_log_file),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-CLOSE-LOG-FILE-FOR-SLOT */
Object compile_close_log_file_for_slot varargs_1(int, n)
{
    Object message_count_and_interval, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,145);
    INIT_ARGS_nonrelocating();
    message_count_and_interval = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return update_log_file_slot_value_compiler(message_count_and_interval);
}

/* WRITE-BACK-UP-LOG-FILE-FROM-SLOT */
Object write_back_up_log_file_from_slot(message_count_and_interval,
	    gensymed_symbol)
    Object message_count_and_interval, gensymed_symbol;
{
    x_note_fn_call(203,146);
    if ( !TRUEP(message_count_and_interval))
	return twrite_symbol(1,Qnever);
    else
	return update_log_file_slot_value_writer(message_count_and_interval);
}

static Object list_constant_39;    /* # */

static Object list_constant_40;    /* # */

/* BACK-UP-LOG-FILE-EVALUATION-SETTER */
Object back_up_log_file_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,147);
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
			  list_constant_39))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_40,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_back_up_log_file_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qnever))
	result = VALUES_1(Qnever);
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_log_file),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
  end_back_up_log_file_evaluation_setter:
    return result;
}

/* BACK-UP-LOG-FILE-EVALUATION-GETTER */
Object back_up_log_file_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(203,148);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_log_file),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Qnever;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-BACK-UP-LOG-FILE-FOR-SLOT */
Object compile_back_up_log_file_for_slot varargs_1(int, n)
{
    Object message_count_and_interval, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,149);
    INIT_ARGS_nonrelocating();
    message_count_and_interval = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(message_count_and_interval,Qnever))
	return VALUES_1(Nil);
    else
	return update_log_file_slot_value_compiler(message_count_and_interval);
}

static Object array_constant_7;    /* # */

static Object string_constant_78;  /* " or ~d" */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

/* UPDATE-LOG-FILE-SLOT-VALUE-WRITER */
Object update_log_file_slot_value_writer(message_count_and_interval)
    Object message_count_and_interval;
{
    Object temp, message_count_qm, interval_qm;
    char interval_count_first_qm;

    x_note_fn_call(203,150);
    temp = FIRST(message_count_and_interval);
    interval_count_first_qm = CONSP(temp);
    message_count_qm = message_count_and_interval ? 
	    (interval_count_first_qm ? SECOND(message_count_and_interval) :
	     FIRST(message_count_and_interval)) : Nil;
    interval_qm = message_count_and_interval ? (interval_count_first_qm ? 
	    FIRST(message_count_and_interval) : 
	    SECOND(message_count_and_interval)) : Nil;
    if ( !TRUEP(message_count_and_interval))
	return twrite_symbol(1,Qnone);
    else if (interval_count_first_qm && interval_qm) {
	twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)6L));
	print_constant(2,FIRST(interval_qm),Qseconds);
	if (message_count_qm) {
	    tformat(2,string_constant_78,message_count_qm);
	    if (IFIX(message_count_qm) == (SI_Long)1L)
		twrite_beginning_of_wide_string(array_constant_8,
			FIX((SI_Long)8L));
	    else
		twrite_beginning_of_wide_string(array_constant_9,
			FIX((SI_Long)9L));
	    return twrite_beginning_of_wide_string(array_constant_10,
		    FIX((SI_Long)23L));
	}
	else
	    return VALUES_1(Nil);
    }
    else if (message_count_qm) {
	twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)6L));
	twrite(message_count_qm);
	if (IFIX(message_count_qm) == (SI_Long)1L)
	    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)8L));
	else
	    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)9L));
	if (interval_qm) {
	    twrite_beginning_of_wide_string(array_constant_11,
		    FIX((SI_Long)4L));
	    print_constant(2,FIRST(interval_qm),Qseconds);
	    return twrite_beginning_of_wide_string(array_constant_10,
		    FIX((SI_Long)23L));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_79;  /* "The message count, ~d, must be between 1 and 9999." */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

/* UPDATE-LOG-FILE-SLOT-VALUE-COMPILER */
Object update_log_file_slot_value_compiler(message_count_and_interval_qm)
    Object message_count_and_interval_qm;
{
    Object temp, message_count_qm, interval_qm, bad_message_count_qm;
    Object bad_interval_qm, temp_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char interval_count_first_qm;
    Declare_special(5);

    x_note_fn_call(203,151);
    temp = FIRST(message_count_and_interval_qm);
    interval_count_first_qm = CONSP(temp);
    message_count_qm = message_count_and_interval_qm ? 
	    (interval_count_first_qm ? 
	    SECOND(message_count_and_interval_qm) : 
	    FIRST(message_count_and_interval_qm)) : Nil;
    interval_qm = message_count_and_interval_qm ? (interval_count_first_qm 
	    ? FIRST(message_count_and_interval_qm) : 
	    SECOND(message_count_and_interval_qm)) : Nil;
    bad_message_count_qm = Nil;
    bad_interval_qm = Nil;
    if (message_count_qm &&  !((SI_Long)0L < IFIX(message_count_qm) && 
	    IFIX(message_count_qm) < (SI_Long)10000L))
	bad_message_count_qm = T;
    if (interval_qm && IFIX(FIRST(interval_qm)) <= (SI_Long)0L)
	bad_interval_qm = T;
    if (bad_message_count_qm && bad_interval_qm) {
	temp_1 = Bad_phrase;
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
		  tformat(2,string_constant_79,message_count_qm);
		  twrite_beginning_of_wide_string(array_constant_12,
			  FIX((SI_Long)16L));
		  print_constant(2,FIRST(interval_qm),Qseconds);
		  twrite_beginning_of_wide_string(array_constant_13,
			  FIX((SI_Long)25L));
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp_1,temp);
    }
    else if (bad_interval_qm) {
	temp_1 = Bad_phrase;
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
		  twrite_beginning_of_wide_string(array_constant_14,
			  FIX((SI_Long)14L));
		  print_constant(2,FIRST(interval_qm),Qseconds);
		  twrite_beginning_of_wide_string(array_constant_13,
			  FIX((SI_Long)25L));
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp_1,temp);
    }
    else if (bad_message_count_qm) {
	temp_1 = Bad_phrase;
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
		  tformat(2,string_constant_79,message_count_qm);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp_1,temp);
    }
    else
	return VALUES_1(message_count_and_interval_qm);
}

static Object list_constant_41;    /* # */

static Object list_constant_42;    /* # */

static Object Qcross_section_regions;  /* cross-section-regions */

static Object Qregion_name;        /* region-name */

static Object Qregion_color;       /* region-color */

static Object Qpolychrome;         /* polychrome */

static Object Qcross_section_stripes;  /* cross-section-stripes */

static Object Qregion_size;        /* region-size */

/* CROSS-SECTION-PATTERN-EVALUATION-SETTER */
Object cross_section_pattern_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, gensymed_symbol_1;
    Object held_vector, regions_info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, first_part_of_phrase_value;
    Object stripes_info, second_part_of_phrase_value, stripes_information;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,152);
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
			  list_constant_41))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_42,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_cross_section_pattern_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_5))
	result = VALUES_1(Qinherited);
    else if (type_specification_type_p(gensymed_symbol,list_constant_6)) {
	gensymed_symbol = evaluation_value;
	if (estructure_slot(gensymed_symbol,Qcross_section_regions,Nil)) {
	    gensymed_symbol_1 = estructure_slot(gensymed_symbol,
		    Qcross_section_regions,Nil);
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    regions_info = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    held_vector = M_CAR(gensymed_symbol_1);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop:
	    if (next_index >= length_1)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    regions_info = validated_elt;
	    gensymed_symbol_1 = regions_info;
	    temp_1 = estructure_slot(gensymed_symbol_1,Qregion_name,Nil);
	    ab_loopvar__2 = phrase_cons(phrase_cons(temp_1,
		    estructure_slot(gensymed_symbol_1,Qregion_color,Nil)),Nil);
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
	    first_part_of_phrase_value = 
		    phrase_list_2(phrase_cons(Qpolychrome,temp_1),Qcm);
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qcross_section_stripes,Nil);
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    stripes_info = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    stripes_info = validated_elt;
	    gensymed_symbol = stripes_info;
	    temp_1 = estructure_slot(gensymed_symbol,Qregion_name,Nil);
	    ab_loopvar__2 = phrase_cons(phrase_cons(temp_1,
		    estructure_slot(gensymed_symbol,Qregion_size,Nil)),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    second_part_of_phrase_value = ab_loopvar_;
	    goto end_2;
	    second_part_of_phrase_value = Qnil;
	  end_2:;
	    result = VALUES_1(nconc2(first_part_of_phrase_value,
		    second_part_of_phrase_value));
	}
	else {
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qcross_section_stripes,Nil);
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    stripes_info = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
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
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    stripes_info = validated_elt;
	    gensymed_symbol = stripes_info;
	    temp_1 = estructure_slot(gensymed_symbol,Qregion_name,Nil);
	    ab_loopvar__2 = phrase_cons(phrase_cons(temp_1,
		    estructure_slot(gensymed_symbol,Qregion_size,Nil)),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_2;
	  end_loop_2:
	    stripes_information = ab_loopvar_;
	    goto end_3;
	    stripes_information = Qnil;
	  end_3:;
	    result = VALUES_1(stripes_information);
	}
    }
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
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_22,list_constant_5);
		  tformat(2,string_constant_22,list_constant_6);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_23,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_cross_section_pattern_evaluation_setter:
    return result;
}

/* CROSS-SECTION-PATTERN-EVALUATION-GETTER */
Object cross_section_pattern_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    Object source_cross_section_regions, source_cross_section_stripes;
    Object region_info, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object gensymed_symbol_2, gensymed_symbol_3, source_region_name;
    Object source_region_color, stripe_info, source_region_size;

    x_note_fn_call(203,153);
    if (slot_value) {
	temp = CAAR(slot_value);
	if (CONSP(temp)) {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    gensymed_symbol_1 = slot_value;
	    source_cross_section_regions = CAR(gensymed_symbol_1);
	    source_cross_section_stripes = CDR(gensymed_symbol_1);
	    region_info = Nil;
	    ab_loop_list_ = source_cross_section_regions;
	    gensymed_symbol_1 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    region_info = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol_2 = allocate_evaluation_structure(Nil);
	    gensymed_symbol_3 = region_info;
	    source_region_name = CAR(gensymed_symbol_3);
	    source_region_color = CDR(gensymed_symbol_3);
	    set_evaluation_structure_slot(gensymed_symbol_2,Qregion_name,
		    source_region_name);
	    set_evaluation_structure_slot(gensymed_symbol_2,Qregion_color,
		    source_region_color);
	    ab_loopvar__1 = eval_cons_1(gensymed_symbol_2,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol_1 = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    temp = allocate_evaluation_sequence(gensymed_symbol_1);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qcross_section_regions,temp);
	    stripe_info = Nil;
	    ab_loop_list_ = source_cross_section_stripes;
	    gensymed_symbol_1 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    stripe_info = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol_2 = allocate_evaluation_structure(Nil);
	    gensymed_symbol_3 = stripe_info;
	    source_region_name = CAR(gensymed_symbol_3);
	    source_region_size = CDR(gensymed_symbol_3);
	    set_evaluation_structure_slot(gensymed_symbol_2,Qregion_name,
		    source_region_name);
	    set_evaluation_structure_slot(gensymed_symbol_2,Qregion_size,
		    source_region_size);
	    ab_loopvar__1 = eval_cons_1(gensymed_symbol_2,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol_1 = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_1;
	  end_loop_1:
	    temp = allocate_evaluation_sequence(gensymed_symbol_1);
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qcross_section_stripes,temp);
	    temp = gensymed_symbol;
	}
	else {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    stripe_info = Nil;
	    ab_loop_list_ = slot_value;
	    gensymed_symbol_1 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    stripe_info = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol_2 = allocate_evaluation_structure(Nil);
	    gensymed_symbol_3 = stripe_info;
	    source_region_name = CAR(gensymed_symbol_3);
	    source_region_size = CDR(gensymed_symbol_3);
	    set_evaluation_structure_slot(gensymed_symbol_2,Qregion_name,
		    source_region_name);
	    set_evaluation_structure_slot(gensymed_symbol_2,Qregion_size,
		    source_region_size);
	    ab_loopvar__1 = eval_cons_1(gensymed_symbol_2,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol_1 = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_2;
	  end_loop_2:
	    temp = allocate_evaluation_sequence(gensymed_symbol_1);
	    goto end_3;
	    temp = Qnil;
	  end_3:;
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qcross_section_stripes,temp);
	    temp = gensymed_symbol;
	}
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_43;    /* # */

static Object list_constant_44;    /* # */

/* G2-METER-NAME-EVALUATION-SETTER */
Object g2_meter_name_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,154);
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
			  list_constant_43))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_g2_meter_name_evaluation_setter;
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
  end_g2_meter_name_evaluation_setter:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_meter_names_and_forms, Qg2_meter_names_and_forms);

/* G2-METER-NAME-EVALUATION-GETTER */
Object g2_meter_name_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object name_and_symbol_pair, ab_loop_list_, temp;

    x_note_fn_call(203,155);
    if (slot_value) {
	name_and_symbol_pair = Nil;
	ab_loop_list_ = G2_meter_names_and_forms;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name_and_symbol_pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = SECOND(name_and_symbol_pair);
	if (EQUAL(slot_value,temp)) {
	    temp = FIRST(name_and_symbol_pair);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = FIRST(slot_value);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_45;    /* # */

static Object Qtruth_value;        /* truth-value */

/* GFI-YES-OR-NO?-EVALUATION-SETTER */
Object gfi_yes_or_no_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,156);
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
			  list_constant_45))) {
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
		      goto end_gfi_yes_or_no_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = evaluation_truth_value_is_true_p(evaluation_value);
  end_gfi_yes_or_no_qm_evaluation_setter:
    return result;
}

/* GFI-YES-OR-NO?-EVALUATION-GETTER */
Object gfi_yes_or_no_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,157);
    GENSYM_RETURN_ONE(slot_value ? Evaluation_true_value : 
	    Evaluation_false_value);
    return VALUES_1(Nil);
}

static Object list_constant_46;    /* # */

static Object list_constant_47;    /* # */

/* GFI-FILE-FORMAT-EVALUATION-SETTER */
Object gfi_file_format_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,158);
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
			  list_constant_46))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_47,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gfi_file_format_evaluation_setter;
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
  end_gfi_file_format_evaluation_setter:
    return result;
}

/* GFI-FILE-FORMAT-EVALUATION-GETTER */
Object gfi_file_format_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,159);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_48;    /* # */

static Object list_constant_49;    /* # */

static Object Qexplicit_time_stamp;  /* explicit-time-stamp */

static Object Qexplicit;           /* explicit */

static Object Qrelative;           /* relative */

/* GFI-TIME-STAMP-FORMAT-EVALUATION-SETTER */
Object gfi_time_stamp_format_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,160);
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
			  list_constant_48))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_49,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gfi_time_stamp_format_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qexplicit_time_stamp))
	result = VALUES_1(Qexplicit);
    else
	result = VALUES_1(Qrelative);
  end_gfi_time_stamp_format_evaluation_setter:
    return result;
}

static Object Qrelative_time_stamp;  /* relative-time-stamp */

/* GFI-TIME-STAMP-FORMAT-EVALUATION-GETTER */
Object gfi_time_stamp_format_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,161);
    GENSYM_RETURN_ONE(EQ(slot_value,Qexplicit) ? Qexplicit_time_stamp : 
	    Qrelative_time_stamp);
    return VALUES_1(Nil);
}

static Object list_constant_50;    /* # */

static Object list_constant_51;    /* # */

static Object Qwrite_interval;     /* write-interval */

static Object Qwhen_variables_receive_values;  /* when-variables-receive-values */

static Object Qwhen_received_value;  /* when-received-value */

static Object Qwhen_activated;     /* when-activated */

static Object Qoutput_one_shot_when_activated;  /* output-one-shot-when-activated */

static Object Qwhen_activated_without_interruption;  /* when-activated-without-interruption */

static Object Qoutput_one_shot_when_activated_without_interruption;  /* output-one-shot-when-activated-without-interruption */

/* GFI-OUTPUT-FILE-UPDATE-FREQUENCY-EVALUATION-SETTER */
Object gfi_output_file_update_frequency_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,162);
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
			  list_constant_50))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_51,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gfi_output_file_update_frequency_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (FIXNUMP(evaluation_value))
	result = phrase_list_2(Qwrite_interval,
		phrase_cons(evaluation_value,Qseconds));
    else if (EQ(evaluation_value,Qwhen_variables_receive_values))
	result = VALUES_1(Qwhen_received_value);
    else if (EQ(evaluation_value,Qwhen_activated))
	result = VALUES_1(Qoutput_one_shot_when_activated);
    else if (EQ(evaluation_value,Qwhen_activated_without_interruption))
	result = VALUES_1(Qoutput_one_shot_when_activated_without_interruption);
    else
	result = VALUES_1(Qnone);
  end_gfi_output_file_update_frequency_evaluation_setter:
    return result;
}

/* GFI-OUTPUT-FILE-UPDATE-FREQUENCY-EVALUATION-GETTER */
Object gfi_output_file_update_frequency_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(203,163);
    if (CONSP(slot_value)) {
	temp = SECOND(slot_value);
	temp = CAR(temp);
    }
    else if (EQ(slot_value,Qwhen_received_value))
	temp = Qwhen_variables_receive_values;
    else if (EQ(slot_value,Qoutput_one_shot_when_activated))
	temp = Qwhen_activated;
    else if (EQ(slot_value,
	    Qoutput_one_shot_when_activated_without_interruption))
	temp = Qwhen_activated_without_interruption;
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_52;    /* # */

static Object list_constant_53;    /* # */

static Object Qclass_identifying_attributes;  /* class-identifying-attributes */

static Object string_constant_80;  /* "Incorrect - empty configuration parameters for interface" */

static Object Qab_class;           /* class */

static Object Qattribute;          /* attribute */

static Object Qname_for_network;   /* name-for-network */

/* ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE-EVALUATION-SETTER */
Object attributes_which_identify_a_network_item_reference_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object attribute_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, held_vector_1, attribute, ab_loopvar__3;
    Object ab_loopvar__4;
    SI_Long next_index, length_1, next_index_1, length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,164);
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
			  list_constant_52))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_53,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_attributes_which_identify_a_network_item_reference_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(evaluation_value))
	result = VALUES_1(Qnone);
    else {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	attribute_name = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	attribute_name = validated_elt;
	if (SYMBOLP(attribute_name))
	    temp_1 = attribute_name;
	else if ( !TRUEP(estructure_slot(attribute_name,
		Qclass_identifying_attributes,Nil))) {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_80);
	    result = VALUES_2(temp,temp_1);
	    goto end_att_w_iden_s_form_block;
	}
	else {
	    gensymed_symbol = attribute_name;
	    temp = estructure_slot(gensymed_symbol,Qab_class,Nil);
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qclass_identifying_attributes,Nil);
	    held_vector_1 = Nil;
	    next_index_1 = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    attribute = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    held_vector_1 = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	  next_loop_1:
	    if (next_index_1 >= length_2)
		goto end_loop_1;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    next_index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_1 & 
		    (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index_1 = next_index_1 + (SI_Long)1L;
	    attribute = validated_elt;
	    if (SYMBOLP(attribute))
		temp_1 = attribute;
	    else {
		gensymed_symbol = attribute;
		temp_1 = estructure_slot(gensymed_symbol,Qattribute,Nil);
		temp_1 = phrase_list_2(temp_1,
			estructure_slot(gensymed_symbol,Qname_for_network,
			Nil));
	    }
	    ab_loopvar__4 = phrase_cons(temp_1,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = ab_loopvar__2;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	    temp_1 = phrase_list_3(Qab_class,temp,phrase_cons(Qcm,temp_1));
	}
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	result = phrase_cons(Qcm,temp_1);
    }
  end_att_w_iden_s_form_block:
  end_attributes_which_identify_a_network_item_reference_evaluation_setter:
    return result;
}

/* ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE-EVALUATION-GETTER */
Object attributes_which_identify_a_network_item_reference_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object attribute_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp, gensymed_symbol_1, gensymed_symbol_2;
    Object spec_class, spec_class_identifying_attributes, attribute;
    Object ab_loop_list__1, ab_loopvar__2, gensymed_symbol_3, spec_attribute;
    Object spec_name_for_network;

    x_note_fn_call(203,165);
    if (slot_value) {
	attribute_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SYMBOLP(attribute_name))
	    temp = attribute_name;
	else {
	    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	    gensymed_symbol_2 = attribute_name;
	    spec_class = CAR(gensymed_symbol_2);
	    spec_class_identifying_attributes = CDR(gensymed_symbol_2);
	    set_evaluation_structure_slot(gensymed_symbol_1,Qab_class,
		    spec_class);
	    attribute = Nil;
	    ab_loop_list__1 = spec_class_identifying_attributes;
	    gensymed_symbol_2 = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    attribute = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    gensymed_symbol_3 = attribute;
	    spec_attribute = CAR(gensymed_symbol_3);
	    spec_name_for_network = CDR(gensymed_symbol_3);
	    if ( !TRUEP(spec_name_for_network))
		temp = spec_attribute;
	    else {
		gensymed_symbol_3 = allocate_evaluation_structure(Nil);
		set_evaluation_structure_slot(gensymed_symbol_3,Qattribute,
			spec_attribute);
		set_evaluation_structure_slot(gensymed_symbol_3,
			Qname_for_network,spec_name_for_network);
		temp = gensymed_symbol_3;
	    }
	    ab_loopvar__2 = eval_cons_1(temp,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		gensymed_symbol_2 = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    temp = allocate_evaluation_sequence(gensymed_symbol_2);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qclass_identifying_attributes,temp);
	    temp = gensymed_symbol_1;
	}
	ab_loopvar__1 = eval_cons_1(temp,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_54;    /* # */

static Object list_constant_55;    /* # */

static Object Qhome;               /* home */

static Object Qconvert_home_to_local;  /* convert-home-to-local */

static Object Qno_conversion;      /* no-conversion */

static Object Qname;               /* name */

static Object Qname_includes_home;  /* name-includes-home */

static Object Qname_includes_home_unless_local;  /* name-includes-home-unless-local */

static Object Qunless_local;       /* unless-local */

static Object Qadd_home_to_name;   /* add-home-to-name */

static Object Qunsupplied;         /* unsupplied */

static Object Qdefault_remote_class;  /* default-remote-class */

static Object Qremote_class_prefix;  /* remote-class-prefix */

static Object Qnon_local_item_class;  /* non-local-item-class */

static Object Qreference_lookup;   /* reference-lookup */

static Object Qlook_up_references;  /* look-up-references */

static Object Qdo_not_look_up_references;  /* do-not-look-up-references */

static Object Qreference_creation;  /* reference-creation */

static Object Qcreate_references;  /* create-references */

static Object Qdo_not_create_references;  /* do-not-create-references */

/* OPTIONS-FOR-ITEM-REFERENCE-EVALUATION-SETTER */
Object options_for_item_reference_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, temp_2, temp_3;
    Object temp_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,166);
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
			  list_constant_54))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_55,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_options_for_item_reference_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(evaluation_value))
	result = VALUES_1(Nil);
    else {
	gensymed_symbol = evaluation_value;
	if (estructure_slot(gensymed_symbol,Qhome,Nil)) {
	    temp_1 = estructure_slot(gensymed_symbol,Qhome,Nil);
	    if (EQ(temp_1,Qconvert_home_to_local))
		temp_1 = Qt;
	    else if (EQ(temp_1,Qno_conversion))
		temp_1 = Qnil;
	    else
		temp_1 = Qnil;
	    temp = phrase_list_2(Qconvert_home_to_local,temp_1);
	}
	else
	    temp = Nil;
	if (estructure_slot(gensymed_symbol,Qname,Nil)) {
	    temp_1 = estructure_slot(gensymed_symbol,Qname,Nil);
	    if (EQ(temp_1,Qname_includes_home))
		temp_1 = Qt;
	    else if (EQ(temp_1,Qname_includes_home_unless_local))
		temp_1 = Qunless_local;
	    else if (EQ(temp_1,Qno_conversion))
		temp_1 = Qnil;
	    else
		temp_1 = Qnil;
	    temp_2 = phrase_list_2(Qadd_home_to_name,temp_1);
	}
	else
	    temp_2 = Nil;
	if ( !(EQ(Qunsupplied,estructure_slot(evaluation_value,
		Qdefault_remote_class,Qunsupplied)) && EQ(Qunsupplied,
		estructure_slot(evaluation_value,Qremote_class_prefix,
		Qunsupplied)))) {
	    temp_1 = estructure_slot(gensymed_symbol,Qdefault_remote_class,
		    Nil);
	    temp_3 = phrase_list_3(Qnon_local_item_class,temp_1,
		    estructure_slot(gensymed_symbol,Qremote_class_prefix,Nil));
	}
	else
	    temp_3 = Nil;
	if (estructure_slot(gensymed_symbol,Qreference_lookup,Nil)) {
	    temp_1 = estructure_slot(gensymed_symbol,Qreference_lookup,Nil);
	    if (EQ(temp_1,Qlook_up_references))
		temp_1 = Qt;
	    else if (EQ(temp_1,Qdo_not_look_up_references))
		temp_1 = Qnil;
	    else
		temp_1 = Qnil;
	    temp_4 = phrase_list_2(Qreference_lookup,temp_1);
	}
	else
	    temp_4 = Nil;
	if (estructure_slot(gensymed_symbol,Qreference_creation,Nil)) {
	    temp_1 = estructure_slot(gensymed_symbol,Qreference_lookup,Nil);
	    if (EQ(temp_1,Qcreate_references))
		temp_1 = Qt;
	    else if (EQ(temp_1,Qdo_not_create_references))
		temp_1 = Qnil;
	    else
		temp_1 = Qnil;
	    temp_1 = phrase_list_2(Qreference_creation,temp_1);
	}
	else
	    temp_1 = Nil;
	result = phrase_cons(Qsc,phrase_cons(nconc2(temp,nconc2(temp_2,
		nconc2(temp_3,nconc2(temp_4,temp_1)))),Nil));
    }
  end_options_for_item_reference_evaluation_setter:
    return result;
}

/* OPTIONS-FOR-ITEM-REFERENCE-EVALUATION-GETTER */
Object options_for_item_reference_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, home_1, name, default_remote_class, remote_class_prefix;
    Object reference_lookup, reference_creation, option, ab_loop_list_, temp_1;
    Object temp_2, temp_3;

    x_note_fn_call(203,167);
    if ( !TRUEP(slot_value))
	temp = Nil;
    else {
	home_1 = Nil;
	name = Nil;
	default_remote_class = Nil;
	remote_class_prefix = Nil;
	reference_lookup = Nil;
	reference_creation = Nil;
	option = Nil;
	ab_loop_list_ = slot_value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	option = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = FIRST(option);
	if (EQ(temp,Qconvert_home_to_local))
	    home_1 = SECOND(option) ? Qconvert_home_to_local : Qno_conversion;
	else if (EQ(temp,Qadd_home_to_name)) {
	    temp = SECOND(option);
	    if (EQ(temp,Qt))
		name = Qname_includes_home;
	    else if (EQ(temp,Qunless_local))
		name = Qname_includes_home_unless_local;
	    else if (EQ(temp,Qnil))
		name = Qno_conversion;
	    else
		name = Qnil;
	}
	else if (EQ(temp,Qnon_local_item_class)) {
	    if (SECOND(option))
		default_remote_class = SECOND(option);
	    if (THIRD(option))
		remote_class_prefix = THIRD(option);
	}
	else if (EQ(temp,Qreference_lookup))
	    reference_lookup = SECOND(option) ? Qlook_up_references : 
		    Qdo_not_look_up_references;
	else if (EQ(temp,Qreference_creation))
	    reference_creation = SECOND(option) ? Qcreate_references : 
		    Qdo_not_create_references;
	goto next_loop;
      end_loop:;
	temp_1 = home_1 ? eval_list_2(Qhome,home_1) : Nil;
	temp_2 = name ? eval_list_2(Qname,name) : Nil;
	temp_3 = remote_class_prefix ? eval_list_2(Qremote_class_prefix,
		remote_class_prefix) : Nil;
	temp = default_remote_class ? eval_list_2(Qdefault_remote_class,
		default_remote_class) : Nil;
	temp = allocate_evaluation_structure(nconc2(temp_1,nconc2(temp_2,
		nconc2(temp_3,nconc2(temp,nconc2(reference_lookup ? 
		eval_list_2(Qreference_lookup,reference_lookup) : Nil,
		reference_creation ? eval_list_2(Qreference_creation,
		reference_creation) : Nil))))));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_56;    /* # */

static Object list_constant_57;    /* # */

static Object Qno_grouping;        /* no-grouping */

/* GSI-VARIABLE-GROUPING-SPECIFICATION-EVALUATION-SETTER */
Object gsi_variable_grouping_specification_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object attribute_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,168);
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
			  list_constant_56))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_57,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gsi_variable_grouping_specification_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	attribute_name = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	attribute_name = validated_elt;
	ab_loopvar__2 = phrase_cons(attribute_name,Nil);
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
	result = phrase_cons(Qcm,temp_1);
    }
    else
	result = VALUES_1(Qno_grouping);
  end_gsi_variable_grouping_specification_evaluation_setter:
    return result;
}

/* GSI-VARIABLE-GROUPING-SPECIFICATION-EVALUATION-GETTER */
Object gsi_variable_grouping_specification_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object attribute_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(203,169);
    if (CONSP(slot_value)) {
	attribute_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(attribute_name,Nil);
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
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_58;    /* # */

static Object list_constant_59;    /* # */

static Object Qonly_while_sliding;  /* only-while-sliding */

static Object Qwhile_sliding;      /* while-sliding */

/* WHEN-TO-SHOW-VALUE-EVALUATION-SETTER */
Object when_to_show_value_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,170);
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
			  list_constant_58))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_59,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_when_to_show_value_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qonly_while_sliding))
	result = VALUES_1(Qwhile_sliding);
    else
	result = VALUES_1(evaluation_value);
  end_when_to_show_value_evaluation_setter:
    return result;
}

static Object Qalways;             /* always */

/* WHEN-TO-SHOW-VALUE-EVALUATION-GETTER */
Object when_to_show_value_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(203,171);
    if (EQ(slot_value,Qwhile_sliding))
	temp = Qonly_while_sliding;
    else {
	temp = slot_value;
	if (temp);
	else
	    temp = Qalways;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_60;    /* # */

static Object list_constant_61;    /* # */

static Object Qasynchronous_input;  /* asynchronous-input */

static Object Qasynchronous;       /* asynchronous */

static Object Qasynchronous_input_ignoring_the_data_server;  /* asynchronous-input-ignoring-the-data-server */

static Object Qasynchronous_ignoring_data_server;  /* asynchronous-ignoring-data-server */

static Object Qinput_on_request_preserving_time_stamps;  /* input-on-request-preserving-time-stamps */

static Object Qon_request;         /* on-request */

static Object Qinput_on_request_sample_and_hold;  /* input-on-request-sample-and-hold */

static Object Qon_request_sample_and_hold;  /* on-request-sample-and-hold */

static Object Qinput_when_activated;  /* input-when-activated */

static Object Qinput_one_shot_when_activated;  /* input-one-shot-when-activated */

static Object Qinput_when_activated_without_interruption;  /* input-when-activated-without-interruption */

static Object Qinput_one_shot_when_activated_without_interruption;  /* input-one-shot-when-activated-without-interruption */

/* GFI-INPUT-VARIABLES-UPDATE-MODE-EVALUATION-SETTER */
Object gfi_input_variables_update_mode_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,172);
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
			  list_constant_60))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_61,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gfi_input_variables_update_mode_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qasynchronous_input))
	result = VALUES_1(Qasynchronous);
    else if (EQ(evaluation_value,Qasynchronous_input_ignoring_the_data_server))
	result = VALUES_1(Qasynchronous_ignoring_data_server);
    else if (EQ(evaluation_value,Qinput_on_request_preserving_time_stamps))
	result = VALUES_1(Qon_request);
    else if (EQ(evaluation_value,Qinput_on_request_sample_and_hold))
	result = VALUES_1(Qon_request_sample_and_hold);
    else if (EQ(evaluation_value,Qinput_when_activated))
	result = VALUES_1(Qinput_one_shot_when_activated);
    else if (EQ(evaluation_value,Qinput_when_activated_without_interruption))
	result = VALUES_1(Qinput_one_shot_when_activated_without_interruption);
    else
	result = VALUES_1(Nil);
  end_gfi_input_variables_update_mode_evaluation_setter:
    return result;
}

/* GFI-INPUT-VARIABLES-UPDATE-MODE-EVALUATION-GETTER */
Object gfi_input_variables_update_mode_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(203,173);
    if (EQ(slot_value,Qasynchronous))
	temp = Qasynchronous_input;
    else if (EQ(slot_value,Qasynchronous_ignoring_data_server))
	temp = Qasynchronous_input_ignoring_the_data_server;
    else if (EQ(slot_value,Qon_request))
	temp = Qinput_on_request_preserving_time_stamps;
    else if (EQ(slot_value,Qon_request_sample_and_hold))
	temp = Qinput_on_request_sample_and_hold;
    else if (EQ(slot_value,Qinput_one_shot_when_activated))
	temp = Qinput_when_activated;
    else if (EQ(slot_value,
	    Qinput_one_shot_when_activated_without_interruption))
	temp = Qinput_when_activated_without_interruption;
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* SLOT-DESCRIPTION-FROM-SUPERIOR-CLASS */
Object slot_description_from_superior_class(unaliased_slot_name,
	    class_definition)
    Object unaliased_slot_name, class_definition;
{
    Object direct_superiors_of_defined_class, symbol, property_name, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(203,174);
    direct_superiors_of_defined_class = ISVREF(class_definition,(SI_Long)21L);
    if (direct_superiors_are_defined_p(direct_superiors_of_defined_class)) {
	symbol = most_refined_foundation_class_of_direct_superiors(2,
		direct_superiors_of_defined_class,unaliased_slot_name);
	property_name = Class_description_gkbprop;
	skip_list = CDR(Symbol_properties_table);
	key_value = symbol;
	key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = symbol;
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
	    key_value = property_name;
	    key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
	    key_value = property_name;
	    key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
	return get_slot_description_of_class_description_function(unaliased_slot_name,
		gensymed_symbol,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* POSSIBLY-ALIASED-SLOT-DESCRIPTION-FROM-SUPERIOR-CLASS */
Object possibly_aliased_slot_description_from_superior_class(possibly_aliased_slot_name,
	    class_definition)
    Object possibly_aliased_slot_name, class_definition;
{
    Object direct_superiors_of_defined_class, superior, ab_loop_list_;
    Object ab_loop_it_, unaliased_slot_name, foundation_class, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(203,175);
    direct_superiors_of_defined_class = ISVREF(class_definition,(SI_Long)21L);
    superior = Nil;
    ab_loop_list_ = direct_superiors_of_defined_class;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = 
	    get_slot_name_for_alias_if_any(possibly_aliased_slot_name,
	    superior);
    if (ab_loop_it_) {
	unaliased_slot_name = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    unaliased_slot_name = Qnil;
  end_1:;
    if (unaliased_slot_name);
    else
	unaliased_slot_name = possibly_aliased_slot_name;
    foundation_class = most_refined_foundation_class_of_direct_superiors(2,
	    direct_superiors_of_defined_class,unaliased_slot_name);
    skip_list = CDR(Symbol_properties_table);
    key_value = foundation_class;
    key_hash_value = SXHASH_SYMBOL_1(foundation_class) & 
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
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_2;
    goto next_loop_2;
  end_loop_3:
  end_2:
    level = level - (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = foundation_class;
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
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_3;
    goto next_loop_5;
  end_loop_6:
  end_3:
    level = level - (SI_Long)1L;
    goto next_loop_4;
  end_loop_4:;
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
      next_loop_7:
	if (level < ab_loop_bind_)
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_8:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_9:
	if ( !TRUEP(marked))
	    goto end_loop_8;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    goto end_4;
	goto next_loop_8;
      end_loop_9:
      end_4:
	level = level - (SI_Long)1L;
	goto next_loop_7;
      end_loop_7:;
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
      next_loop_10:
	if (level < ab_loop_bind_)
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_11:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_12:
	if ( !TRUEP(marked))
	    goto end_loop_11;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_12;
      end_loop_11:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_5;
	goto next_loop_11;
      end_loop_12:
      end_5:
	level = level - (SI_Long)1L;
	goto next_loop_10;
      end_loop_10:;
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    return get_slot_description_of_class_description_function(unaliased_slot_name,
	    gensymed_symbol,Nil);
}

/* MAP-SYSTEM-SLOT-NAME-TO-ALIAS */
Object map_system_slot_name_to_alias(slot_name,frame)
    Object slot_name, frame;
{
    Object slot_description_qm, class_1, temp;

    x_note_fn_call(203,176);
    slot_description_qm = slot_description_from_superior_class(slot_name,
	    frame);
    if (slot_description_qm) {
	class_1 = ISVREF(slot_description_qm,(SI_Long)3L);
	temp = get_alias_for_slot_name_if_any(slot_name,class_1);
	if (temp);
	else
	    temp = slot_name;
	return VALUES_2(temp,class_1);
    }
    else
	return VALUES_1(slot_name);
}

/* MAP-ALIAS-TO-SYSTEM-SLOT-NAME */
Object map_alias_to_system_slot_name(alias,frame)
    Object alias, frame;
{
    Object slot_description_qm, class_1, temp;

    x_note_fn_call(203,177);
    slot_description_qm = 
	    possibly_aliased_slot_description_from_superior_class(alias,frame);
    if (slot_description_qm) {
	class_1 = ISVREF(slot_description_qm,(SI_Long)3L);
	temp = get_slot_name_for_alias_if_any(alias,class_1);
	if (temp);
	else
	    temp = alias;
	return VALUES_2(temp,class_1);
    }
    else
	return VALUES_1(alias);
}

static Object Qstubs_for_class;    /* stubs-for-class */

static Object Qconnections_qm;     /* connections? */

static Object Qattribute_displays_for_class;  /* attribute-displays-for-class */

static Object Qattribute_displays_spec_qm;  /* attribute-displays-spec? */

static Object Qcross_section_pattern_for_class;  /* cross-section-pattern-for-class */

static Object Qcross_section_pattern;  /* cross-section-pattern */

static Object Qcell_annotations;   /* cell-annotations */

static Object Qtable_dimensions;   /* table-dimensions */

static Object Qstub_length_for_class;  /* stub-length-for-class */

static Object Qstub_length;        /* stub-length */

static Object Qjunction_block_for_class;  /* junction-block-for-class */

static Object Qjunction_class;     /* junction-class */

static Object Qdefault_message_properties_for_class;  /* default-message-properties-for-class */

static Object Qmessage_properties;  /* message-properties */

static Object Qdefault_text_box_colors_for_class;  /* default-text-box-colors-for-class */

static Object Qtext_cell_colors;   /* text-cell-colors */

static Object Qinitial_value_of_variable_or_parameter;  /* initial-value-of-variable-or-parameter */

static Object Qcondition_for_using_user_menu_choice_qm;  /* condition-for-using-user-menu-choice? */

static Object Quser_menu_choice_expression_initialization;  /* user-menu-choice-expression-initialization */

/* GET-GRAMMAR-CATEGORY-FOR-DEFAULT-OVERRIDE */
Object get_grammar_category_for_default_override(unaliased_slot_name,
	    class_or_class_definition,readp)
    Object unaliased_slot_name, class_or_class_definition, readp;
{
    Object slot_description, slot_type_qm, default_category_qm, category_qm;
    Object category_evaluator_interface;
    char temp;

    x_note_fn_call(203,178);
    slot_description = SYMBOLP(class_or_class_definition) ? 
	    get_slot_description_from_class(2,class_or_class_definition,
	    unaliased_slot_name) : 
	    slot_description_from_superior_class(unaliased_slot_name,
	    class_or_class_definition);
    slot_type_qm = slot_description ? assq_function(Qtype,
	    ISVREF(slot_description,(SI_Long)9L)) : Qnil;
    default_category_qm = SECOND(slot_type_qm);
    if (EQ(unaliased_slot_name,Qstubs_for_class))
	category_qm = Qconnections_qm;
    else if (EQ(unaliased_slot_name,Qattribute_displays_for_class))
	category_qm = Qattribute_displays_spec_qm;
    else if (EQ(unaliased_slot_name,Qcross_section_pattern_for_class))
	category_qm = Qcross_section_pattern;
    else if (EQ(unaliased_slot_name,Qcell_annotations))
	category_qm = Qtable_dimensions;
    else if (EQ(unaliased_slot_name,Qstub_length_for_class))
	category_qm = Qstub_length;
    else if (EQ(unaliased_slot_name,Qjunction_block_for_class))
	category_qm = Qjunction_class;
    else if (EQ(unaliased_slot_name,Qdefault_message_properties_for_class))
	category_qm = Qmessage_properties;
    else if (EQ(unaliased_slot_name,Qdefault_text_box_colors_for_class))
	category_qm = Qtext_cell_colors;
    else if (EQ(unaliased_slot_name,Qinitial_value_of_variable_or_parameter))
	category_qm = Qattribute;
    else if (EQ(unaliased_slot_name,Qcondition_for_using_user_menu_choice_qm))
	category_qm = Quser_menu_choice_expression_initialization;
    else
	category_qm = default_category_qm;
    if (category_qm) {
	if (readp) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
		    Qcategory_evaluator_interface);
	    temp = category_evaluator_interface ? 
		    TRUEP(ISVREF(category_evaluator_interface,
		    (SI_Long)2L)) : TRUEP(Qnil);
	}
	else {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
		    Qcategory_evaluator_interface);
	    temp = category_evaluator_interface ? 
		    TRUEP(ISVREF(category_evaluator_interface,
		    (SI_Long)3L)) : TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(category_qm);
    else
	return VALUES_1(Nil);
}

static Object Qshow_simulated_values;  /* show-simulated-values */

static Object Qreadout_table;      /* readout-table */

static Object Qdial;               /* dial */

static Object Qmeter;              /* meter */

static Object Qgraph;              /* graph */

static Object Qdigital_clock;      /* digital-clock */

static Object Qdisplay_update_interval;  /* display-update-interval */

static Object Qdisplay_wait_interval;  /* display-wait-interval */

static Object Qdisplay_update_priority;  /* display-update-priority */

static Object Qdisplay_format;     /* display-format */

static Object Qclass_of_procedure_invocation;  /* class-of-procedure-invocation */

static Object Qdefault_procedure_priority;  /* default-procedure-priority */

static Object Quninterrupted_procedure_execution_limit;  /* uninterrupted-procedure-execution-limit */

static Object Qprocedure;          /* procedure */

static Object Qmethod_declaration;  /* method-declaration */

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

static Object Qvariable_or_parameter;  /* variable-or-parameter */

static Object Qgeneric_simulation_formula;  /* generic-simulation-formula */

static Object Qrule;               /* rule */

static Object Qsimulation_subtable;  /* simulation-subtable */

static Object Qstubs;              /* stubs */

static Object Qattribute_displays;  /* attribute-displays */

static Object Qobject;             /* object */

static Object Qimage_definition;   /* image-definition */

static Object Qrelation;           /* relation */

static Object Qframe_style_definition;  /* frame-style-definition */

static Object Quser_menu_choice;   /* user-menu-choice */

static Object Qtabular_function;   /* tabular-function */

static Object Qprocedure_invocation;  /* procedure-invocation */

static Object Qmodel_definition;   /* model-definition */

static Object Qexternal_simulation_definition;  /* external-simulation-definition */

static Object Qaction_button;      /* action-button */

static Object Qcheck_box;          /* check-box */

static Object Qradio_button;       /* radio-button */

static Object Qslider;             /* slider */

static Object Qnetwork_wire;       /* network-wire */

static Object Qvariable_frame_flags;  /* variable-frame-flags */

static Object Qparameter_frame_flags;  /* parameter-frame-flags */

static Object Qparameter;          /* parameter */

/* MAKE-ACCEPTABLE-CLASSES-PHRASE-FOR-DEFAULT-OVERRIDE */
Object make_acceptable_classes_phrase_for_default_override(aliased_slot_name,
	    defining_class,grammar_category_qm)
    Object aliased_slot_name, defining_class, grammar_category_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;

    x_note_fn_call(203,179);
    if (EQ(aliased_slot_name,Qshow_simulated_values))
	return phrase_list_2(phrase_list_4(Qreadout_table,Qdial,Qmeter,
		Qgraph),phrase_cons(Qdigital_clock,Nil));
    else if (EQ(aliased_slot_name,Qdisplay_update_interval) || 
	    EQ(aliased_slot_name,Qdisplay_wait_interval) || 
	    EQ(aliased_slot_name,Qdisplay_update_priority))
	return phrase_list_2(phrase_list_4(Qreadout_table,Qdial,Qmeter,
		Qgraph),Nil);
    else if (EQ(aliased_slot_name,Qdisplay_format))
	return phrase_list_2(phrase_cons(Qreadout_table,Nil),
		phrase_cons(Qdigital_clock,Nil));
    else if (EQ(aliased_slot_name,Qclass_of_procedure_invocation) || 
	    EQ(aliased_slot_name,Qdefault_procedure_priority) || 
	    EQ(aliased_slot_name,Quninterrupted_procedure_execution_limit))
	return phrase_list_2(phrase_cons(Qprocedure,Nil),
		phrase_cons(Qmethod_declaration,Nil));
    else if (EQ(aliased_slot_name,Qtracing_and_breakpoints)) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qprocedure;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qvariable_or_parameter;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qgeneric_simulation_formula;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qrule;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qsimulation_subtable;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qdial;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qmeter;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qreadout_table;
	return phrase_list_2(gensymed_symbol,
		phrase_list_2(Qmethod_declaration,Qdigital_clock));
    }
    else if (EQ(aliased_slot_name,Qstubs) || EQ(aliased_slot_name,
	    Qattribute_displays) || EQ(aliased_slot_name,
	    Qattribute_displays_for_class)) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)17L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qobject;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qimage_definition;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qrelation;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qframe_style_definition;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Quser_menu_choice;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qtabular_function;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qprocedure;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qdial;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qmeter;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qprocedure_invocation;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qmodel_definition;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qexternal_simulation_definition;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qaction_button;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qcheck_box;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qradio_button;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qslider;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qnetwork_wire;
	return phrase_list_2(gensymed_symbol,Nil);
    }
    else {
	if (EQ(grammar_category_qm,Qvariable_frame_flags))
	    temp = Qvariable;
	else if (EQ(grammar_category_qm,Qparameter_frame_flags))
	    temp = Qparameter;
	else
	    temp = defining_class;
	return phrase_list_2(phrase_cons(temp,Nil),Nil);
    }
}

/* GET-INITIAL-EVALUATION-VALUE-FOR-DEFAULT-OVERRIDE-1 */
Object get_initial_evaluation_value_for_default_override_1(initialization,
	    definition,grammar_category_qm)
    Object initialization, definition, grammar_category_qm;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(203,180);
    if ( !TRUEP(grammar_category_qm))
	return VALUES_1(Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = initialization;
	gensymed_symbol_2 = definition;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_details;  /* simulation-details */

static Object Quuid;               /* uuid */

/* GET-INITIAL-EVALUATION-VALUE-FOR-DEFAULT-OVERRIDE */
Object get_initial_evaluation_value_for_default_override(unaliased_slot_name,
	    defining_class,definition,initialization)
    Object unaliased_slot_name, defining_class, definition, initialization;
{
    x_note_fn_call(203,181);
    if (EQ(unaliased_slot_name,Qsimulation_details))
	return VALUES_1(THIRD(initialization));
    if ( !TRUEP(definition) && EQ(unaliased_slot_name,Quuid))
	return VALUES_1(Nil);
    return get_initial_evaluation_value_for_default_override_1(initialization,
	    definition,
	    get_grammar_category_for_default_override(unaliased_slot_name,
	    defining_class,T));
}

static Object list_constant_62;    /* # */

static Object list_constant_63;    /* # */

static Object Quser_attribute_name;  /* user-attribute-name */

static Object Qsystem_attribute_designation;  /* system-attribute-designation */

static Object string_constant_81;  /* "The class-definition must first have a defined set of direct ~
				    *                            superior classes."
				    */

static Object string_constant_82;  /* "The inheritance for this class does not include an attribute named ~a." */

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object Qinitialization;     /* initialization */

static Object Qinitial_value;      /* initial-value */

static Object Qinitial_item_class;  /* initial-item-class */

static Object Quser_defined;       /* user-defined */

static Object Kfuncall;            /* :funcall */

static Object Qmake_simulation_subtable_with_specific_class_and_install;  /* make-simulation-subtable-with-specific-class-and-install */

static Object Qg2_array_element_type;  /* g2-array-element-type */

static Object Qitem_array;         /* item-array */

static Object Qlist_type;          /* list-type */

static Object Qitem_list;          /* item-list */

static Object Qvalue;              /* value */

static Object Qdatum;              /* datum */

static Object Qitem_or_value;      /* item-or-value */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qquantity;           /* quantity */

static Object string_constant_83;  /* "the attribute, ~NQ, is not concludable" */

/* DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS-EVALUATION-SETTER */
Object default_overrides_for_class_definitions_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object override_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, list_of_system_names_qm, name_qm, ab_loop_list_;
    Object system_slot_aliased_names_qm, direct_superiors_qm, aliased_name;
    Object slot_description_qm, symbol_name_text_string_1, symbol_name_length;
    Object this_char, ab_loop_it_, class_symbol, name_symbol, attribute_name;
    Object result_1, error_string_qm, fixed_initial_value, value_type_phrase;
    Object unaliased_slot_name, defining_class, grammar_category_qm;
    Object initialization_phrase, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, parse_result_or_bad_phrase;
    Object acceptable_classes_phrase;
    SI_Long next_index, length_1, i, ab_loop_bind_;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,182);
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
			  list_constant_62))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_63,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_default_overrides_for_class_definitions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value && (SI_Long)0L < 
	    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_value),(SI_Long)1L)))) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	override_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	override_info = validated_elt;
	temp_1 = estructure_slot(override_info,Quser_attribute_name,No_value);
	if (EQ(temp_1,No_value)) {
	    gensymed_symbol = override_info;
	    temp_1 = estructure_slot(gensymed_symbol,
		    Qsystem_attribute_designation,Nil);
	}
	else
	    temp_1 = Nil;
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	list_of_system_names_qm = ab_loopvar_;
	goto end_1;
	list_of_system_names_qm = Qnil;
      end_1:;
	name_qm = Nil;
	ab_loop_list_ = list_of_system_names_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	name_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (name_qm) {
	    ab_loopvar__2 = phrase_cons(name_qm,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_1;
      end_loop_1:
	system_slot_aliased_names_qm = ab_loopvar_;
	goto end_2;
	system_slot_aliased_names_qm = Qnil;
      end_2:;
	if (system_slot_aliased_names_qm) {
	    direct_superiors_qm = ISVREF(frame,(SI_Long)21L);
	    if ( !TRUEP(direct_superiors_qm) ||  
		    !TRUEP(direct_superiors_are_defined_p(direct_superiors_qm))) 
			{
		temp = Bad_phrase;
		temp_1 = tformat_text_string(1,string_constant_81);
		result = VALUES_2(temp,temp_1);
		goto end_block_default_overrides_for_class_definitions_setter;
	    }
	    aliased_name = Nil;
	    ab_loop_list_ = system_slot_aliased_names_qm;
	    slot_description_qm = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    aliased_name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    slot_description_qm = 
		    possibly_aliased_slot_description_from_superior_class(aliased_name,
		    frame);
	    if ( !TRUEP(slot_description_qm)) {
		temp = Bad_phrase;
		temp_1 = tformat_text_string(2,string_constant_82,
			aliased_name);
		result = VALUES_2(temp,temp_1);
		goto end_block_default_overrides_for_class_definitions_setter;
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	override_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_3:
	if (next_index >= length_1)
	    goto end_loop_3;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	override_info = validated_elt;
	temp_1 = estructure_slot(override_info,Quser_attribute_name,No_value);
	if ( !EQ(temp_1,No_value)) {
	    gensymed_symbol = override_info;
	    temp_1 = SYMBOL_PACKAGE(estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil));
	    if (EQ(temp_1,Keyword_package_1)) {
		symbol_name_text_string_1 = 
			symbol_name_text_string(estructure_slot(gensymed_symbol,
			Quser_attribute_name,Nil));
		symbol_name_length = 
			text_string_length(symbol_name_text_string_1);
		i = (SI_Long)0L;
		ab_loop_bind_ = IFIX(symbol_name_length);
		this_char = Nil;
		ab_loop_it_ = Nil;
	      next_loop_4:
		if (i >= ab_loop_bind_)
		    goto end_loop_4;
		this_char = 
			FIX(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i));
		ab_loop_it_ = IFIX(this_char) == (SI_Long)58L && i + 
			(SI_Long)1L < IFIX(symbol_name_length) ? 
			(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i + 
			(SI_Long)1L) == (SI_Long)58L ? T : Nil) : Qnil;
		if (ab_loop_it_) {
		    temp_2 = TRUEP(ab_loop_it_);
		    goto end_3;
		}
		i = i + (SI_Long)1L;
		goto next_loop_4;
	      end_loop_4:
		temp_2 = TRUEP(Qnil);
	      end_3:;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		result = decompose_class_qualified_symbol(estructure_slot(gensymed_symbol,
			Quser_attribute_name,Nil));
		MVS_2(result,class_symbol,name_symbol);
		attribute_name = phrase_list_3(Qclass_qualified_name,
			class_symbol,name_symbol);
	    }
	    else
		attribute_name = estructure_slot(gensymed_symbol,
			Quser_attribute_name,Nil);
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qinitialization,Nil);
	    temp_1 = estructure_slot(gensymed_symbol,Qinitial_value,Nil);
	    result = fix_attribute_initial_value(4,temp_1,
		    estructure_slot(gensymed_symbol,Qinitial_item_class,
		    Nil),Nil,Nil);
	    MVS_2(result,result_1,error_string_qm);
	    if (EQ(result_1,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_block_default_overrides_for_class_definitions_setter;
	    }
	    else
		fixed_initial_value = result_1;
	    value_type_phrase = 
		    fix_override_initial_value(fixed_initial_value);
	    temp_1 = phrase_list_3(attribute_name,value_type_phrase,
		    Quser_defined);
	}
	else {
	    gensymed_symbol = override_info;
	    result = map_alias_to_system_slot_name(estructure_slot(gensymed_symbol,
		    Qsystem_attribute_designation,Nil),frame);
	    MVS_2(result,unaliased_slot_name,defining_class);
	    grammar_category_qm = 
		    get_grammar_category_for_default_override(unaliased_slot_name,
		    defining_class,Nil);
	    if (EQ(unaliased_slot_name,Qsimulation_details))
		initialization_phrase = slot_value_list_3(Kfuncall,
			Qmake_simulation_subtable_with_specific_class_and_install,
			estructure_slot(gensymed_symbol,Qinitialization,Nil));
	    else {
		if (EQ(unaliased_slot_name,Qg2_array_element_type))
		    temp_1 = definition_subclassp(frame,Qitem_array);
		else if (EQ(unaliased_slot_name,Qlist_type))
		    temp_1 = definition_subclassp(frame,Qitem_list);
		else
		    temp_1 = Qnil;
		if (temp_1) {
		    temp_1 = estructure_slot(gensymed_symbol,
			    Qinitialization,Nil);
		    if (EQ(temp_1,Qvalue))
			initialization_phrase = Qdatum;
		    else if (EQ(temp_1,Qitem_or_value))
			initialization_phrase = Qitem_or_datum;
		    else if (EQ(temp_1,Qquantity))
			initialization_phrase = Qnumber;
		    else
			initialization_phrase = 
				estructure_slot(gensymed_symbol,
				Qinitialization,Nil);
		}
		else if (grammar_category_qm) {
		    category_evaluator_interface = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
			    Qcategory_evaluator_interface);
		    function = category_evaluator_interface ? 
			    ISVREF(category_evaluator_interface,
			    (SI_Long)3L) : Qnil;
		    if (function) {
			gensymed_symbol_1 = function;
			gensymed_symbol_2 = 
				estructure_slot(gensymed_symbol,
				Qinitialization,Nil);
			gensymed_symbol_3 = Nil;
			gensymed_symbol_4 = Nil;
			gensymed_symbol_5 = Nil;
			result = inline_funcall_4(gensymed_symbol_1,
				gensymed_symbol_2,gensymed_symbol_3,
				gensymed_symbol_4,gensymed_symbol_5);
		    }
		    else
			result = VALUES_1(Nil);
		    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
		    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
			result = VALUES_2(Bad_phrase,error_string_qm);
			goto end_safe_category_setter_calling_block;
		    }
		    else
			initialization_phrase = parse_result_or_bad_phrase;
		}
		else {
		    temp = Bad_phrase;
		    temp_1 = tformat_text_string(3,string_constant_83,
			    estructure_slot(gensymed_symbol,
			    Qsystem_attribute_designation,Nil),Nil);
		    result = VALUES_2(temp,temp_1);
		    goto end_block_default_overrides_for_class_definitions_setter;
		}
	    }
	    acceptable_classes_phrase = 
		    make_acceptable_classes_phrase_for_default_override(estructure_slot(gensymed_symbol,
		    Qsystem_attribute_designation,Nil),defining_class,
		    grammar_category_qm);
	    temp_1 = phrase_list_3(unaliased_slot_name,
		    initialization_phrase,acceptable_classes_phrase);
	}
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_3;
      end_loop_3:
	temp_1 = ab_loopvar_;
	goto end_4;
	temp_1 = Qnil;
      end_4:;
	result = phrase_cons(Qsc,temp_1);
      end_block_default_overrides_for_class_definitions_setter:
      end_safe_category_setter_calling_block:;
    }
    else
	result = VALUES_1(Qnone);
  end_default_overrides_for_class_definitions_evaluation_setter:
    return result;
}

static Object Quser_overridable;   /* user-overridable */

/* DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS-EVALUATION-GETTER */
Object default_overrides_for_class_definitions_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object default_override, ab_loop_list_, user_defined_p, slot_name;
    Object specified_class_of_override_qm, override_alias, slot_description_qm;
    Object unaliased_slot_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, gensymed_symbol, source_attribute_name;
    Object source_value_type_phrase, source_initial_value;
    Object source_initial_item_class, source_initial_type, gensymed_symbol_1;
    Object value, evaluation_value_qm;

    x_note_fn_call(203,183);
    default_override = Nil;
    ab_loop_list_ = slot_value;
    user_defined_p = Nil;
    slot_name = Nil;
    specified_class_of_override_qm = Nil;
    override_alias = Nil;
    slot_description_qm = Nil;
    unaliased_slot_name = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    default_override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    user_defined_p = EQ(THIRD(default_override),Quser_defined) ? T : Nil;
    slot_name = FIRST(default_override);
    specified_class_of_override_qm = THIRD(default_override);
    if ( !TRUEP(user_defined_p)) {
	if (specified_class_of_override_qm) {
	    temp = get_alias_for_slot_name_if_any(slot_name,
		    specified_class_of_override_qm);
	    if (temp);
	    else
		temp = slot_name;
	    override_alias = temp;
	}
	else
	    override_alias = map_system_slot_name_to_alias(slot_name,frame);
    }
    else
	override_alias = Nil;
    slot_description_qm =  !TRUEP(user_defined_p) ? 
	    possibly_aliased_slot_description_from_superior_class(override_alias,
	    frame) : Nil;
    if (user_defined_p)
	unaliased_slot_name = slot_name;
    else if (specified_class_of_override_qm) {
	temp = get_slot_name_for_alias_if_any(override_alias,
		specified_class_of_override_qm);
	if (temp);
	else
	    temp = override_alias;
	unaliased_slot_name = temp;
    }
    else
	unaliased_slot_name = map_alias_to_system_slot_name(override_alias,
		frame);
    if (user_defined_p || slot_description_qm && 
	    assq_function(Quser_overridable,ISVREF(slot_description_qm,
	    (SI_Long)9L))) {
	if (user_defined_p) {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    source_attribute_name = CAR(default_override);
	    source_value_type_phrase = CADR(default_override);
	    source_initial_value = source_value_type_phrase ? 
		    (CONSP(source_value_type_phrase) && 
		    EQ(M_CDR(source_value_type_phrase),Qsequence) || 
		    CONSP(source_value_type_phrase) && 
		    EQ(M_CDR(source_value_type_phrase),Qab_structure) ? 
		    source_value_type_phrase : 
		    M_CAR(source_value_type_phrase)) : Qnil;
	    source_initial_item_class = CONSP(source_initial_value) && 
		    EQ(M_CAR(source_initial_value),Kfuncall) ? 
		    THIRD(source_initial_value) : Nil;
	    if (source_value_type_phrase) {
		if (CONSP(source_value_type_phrase) && 
			EQ(M_CDR(source_value_type_phrase),Qsequence) || 
			CONSP(source_value_type_phrase) && 
			EQ(M_CDR(source_value_type_phrase),Qab_structure))
		    source_initial_type = CDR(source_value_type_phrase);
		else if (source_initial_item_class)
		    source_initial_type = source_initial_item_class;
		else
		    source_initial_type = 
			    M_CAR(M_CDR(source_value_type_phrase));
	    }
	    else
		source_initial_type = Nil;
	    set_evaluation_structure_slot(gensymed_symbol,
		    Quser_attribute_name,CONSP(source_attribute_name) && 
		    EQ(M_CAR(source_attribute_name),Qclass_qualified_name) 
		    ? 
		    convert_class_qualified_list_to_keyword_symbol(source_attribute_name) 
		    : source_attribute_name);
	    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	    value = 
		    make_initial_value_for_user_given_type(source_initial_value,
		    source_initial_type);
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qinitial_value,value);
	    value = make_initial_item_class_for_user(source_initial_value);
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qinitial_item_class,value);
	    set_evaluation_structure_slot(gensymed_symbol,Qinitialization,
		    gensymed_symbol_1);
	    temp = gensymed_symbol;
	}
	else {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qsystem_attribute_designation,override_alias);
	    evaluation_value_qm = 
		    get_initial_evaluation_value_for_default_override(unaliased_slot_name,
		    specified_class_of_override_qm,frame,
		    CADR(default_override));
	    if (evaluation_value_qm)
		set_evaluation_structure_slot(gensymed_symbol,
			Qinitialization,evaluation_value_qm);
	    temp = gensymed_symbol;
	}
	ab_loopvar__2 = eval_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object list_constant_64;    /* # */

static Object list_constant_65;    /* # */

static Object Qmake_simulation_subtable_and_install;  /* make-simulation-subtable-and-install */

/* DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS-EVALUATION-SETTER */
Object default_overrides_for_object_definitions_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object override_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, list_of_system_names_qm, name_qm, ab_loop_list_;
    Object system_slot_aliased_names_qm, direct_superiors_qm, aliased_name;
    Object slot_description_qm, symbol_name_text_string_1, symbol_name_length;
    Object this_char, ab_loop_it_, class_symbol, name_symbol, attribute_name;
    Object result_1, error_string_qm, fixed_initial_value, value_type_phrase;
    Object unaliased_slot_name, defining_class, slot_name_to_use;
    Object grammar_category_qm, initialization_phrase;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase;
    SI_Long next_index, length_1, i, ab_loop_bind_;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,184);
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
			  list_constant_64))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_65,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_default_overrides_for_object_definitions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value && (SI_Long)0L < 
	    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_value),(SI_Long)1L)))) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	override_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	override_info = validated_elt;
	temp_1 = estructure_slot(override_info,Quser_attribute_name,No_value);
	if (EQ(temp_1,No_value)) {
	    gensymed_symbol = override_info;
	    temp_1 = estructure_slot(gensymed_symbol,
		    Qsystem_attribute_designation,Nil);
	}
	else
	    temp_1 = Nil;
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	list_of_system_names_qm = ab_loopvar_;
	goto end_1;
	list_of_system_names_qm = Qnil;
      end_1:;
	name_qm = Nil;
	ab_loop_list_ = list_of_system_names_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	name_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (name_qm) {
	    ab_loopvar__2 = phrase_cons(name_qm,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_1;
      end_loop_1:
	system_slot_aliased_names_qm = ab_loopvar_;
	goto end_2;
	system_slot_aliased_names_qm = Qnil;
      end_2:;
	if (system_slot_aliased_names_qm) {
	    direct_superiors_qm = ISVREF(frame,(SI_Long)21L);
	    if ( !TRUEP(direct_superiors_qm) ||  
		    !TRUEP(direct_superiors_are_defined_p(direct_superiors_qm))) 
			{
		temp = Bad_phrase;
		temp_1 = tformat_text_string(1,string_constant_81);
		result = VALUES_2(temp,temp_1);
		goto end_block_default_overrides_for_object_definitions_setter;
	    }
	    aliased_name = Nil;
	    ab_loop_list_ = system_slot_aliased_names_qm;
	    slot_description_qm = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    aliased_name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    slot_description_qm = 
		    possibly_aliased_slot_description_from_superior_class(aliased_name,
		    frame);
	    if ( !TRUEP(slot_description_qm)) {
		temp = Bad_phrase;
		temp_1 = tformat_text_string(2,string_constant_82,
			aliased_name);
		result = VALUES_2(temp,temp_1);
		goto end_block_default_overrides_for_object_definitions_setter;
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	override_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_3:
	if (next_index >= length_1)
	    goto end_loop_3;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	override_info = validated_elt;
	temp_1 = estructure_slot(override_info,Quser_attribute_name,No_value);
	if ( !EQ(temp_1,No_value)) {
	    gensymed_symbol = override_info;
	    temp_1 = SYMBOL_PACKAGE(estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil));
	    if (EQ(temp_1,Keyword_package_1)) {
		symbol_name_text_string_1 = 
			symbol_name_text_string(estructure_slot(gensymed_symbol,
			Quser_attribute_name,Nil));
		symbol_name_length = 
			text_string_length(symbol_name_text_string_1);
		i = (SI_Long)0L;
		ab_loop_bind_ = IFIX(symbol_name_length);
		this_char = Nil;
		ab_loop_it_ = Nil;
	      next_loop_4:
		if (i >= ab_loop_bind_)
		    goto end_loop_4;
		this_char = 
			FIX(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i));
		ab_loop_it_ = IFIX(this_char) == (SI_Long)58L && i + 
			(SI_Long)1L < IFIX(symbol_name_length) ? 
			(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i + 
			(SI_Long)1L) == (SI_Long)58L ? T : Nil) : Qnil;
		if (ab_loop_it_) {
		    temp_2 = TRUEP(ab_loop_it_);
		    goto end_3;
		}
		i = i + (SI_Long)1L;
		goto next_loop_4;
	      end_loop_4:
		temp_2 = TRUEP(Qnil);
	      end_3:;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		result = decompose_class_qualified_symbol(estructure_slot(gensymed_symbol,
			Quser_attribute_name,Nil));
		MVS_2(result,class_symbol,name_symbol);
		attribute_name = phrase_list_3(Qclass_qualified_name,
			class_symbol,name_symbol);
	    }
	    else
		attribute_name = estructure_slot(gensymed_symbol,
			Quser_attribute_name,Nil);
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qinitialization,Nil);
	    temp_1 = estructure_slot(gensymed_symbol,Qinitial_value,Nil);
	    result = fix_attribute_initial_value(4,temp_1,
		    estructure_slot(gensymed_symbol,Qinitial_item_class,
		    Nil),Nil,Nil);
	    MVS_2(result,result_1,error_string_qm);
	    if (EQ(result_1,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_block_default_overrides_for_object_definitions_setter;
	    }
	    else
		fixed_initial_value = result_1;
	    value_type_phrase = 
		    fix_override_initial_value(fixed_initial_value);
	    temp_1 = phrase_list_3(attribute_name,value_type_phrase,
		    Quser_defined);
	}
	else {
	    gensymed_symbol = override_info;
	    result = map_alias_to_system_slot_name(estructure_slot(gensymed_symbol,
		    Qsystem_attribute_designation,Nil),frame);
	    MVS_2(result,unaliased_slot_name,defining_class);
	    slot_name_to_use = EQ(unaliased_slot_name,
		    Qinitial_value_of_variable_or_parameter) ? 
		    Qinitial_value : unaliased_slot_name;
	    grammar_category_qm = 
		    get_grammar_category_for_default_override(unaliased_slot_name,
		    defining_class,Nil);
	    if (EQ(slot_name_to_use,Qsimulation_details))
		initialization_phrase = slot_value_list_2(Kfuncall,
			Qmake_simulation_subtable_and_install);
	    else {
		if (EQ(slot_name_to_use,Qg2_array_element_type))
		    temp_1 = definition_subclassp(frame,Qitem_array);
		else if (EQ(slot_name_to_use,Qlist_type))
		    temp_1 = definition_subclassp(frame,Qitem_list);
		else
		    temp_1 = Qnil;
		if (temp_1) {
		    temp_1 = estructure_slot(gensymed_symbol,
			    Qinitialization,Nil);
		    if (EQ(temp_1,Qvalue))
			initialization_phrase = Qdatum;
		    else if (EQ(temp_1,Qitem_or_value))
			initialization_phrase = Qitem_or_datum;
		    else if (EQ(temp_1,Qquantity))
			initialization_phrase = Qnumber;
		    else
			initialization_phrase = 
				estructure_slot(gensymed_symbol,
				Qinitialization,Nil);
		}
		else if (grammar_category_qm) {
		    category_evaluator_interface = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_qm),
			    Qcategory_evaluator_interface);
		    function = category_evaluator_interface ? 
			    ISVREF(category_evaluator_interface,
			    (SI_Long)3L) : Qnil;
		    if (function) {
			gensymed_symbol_1 = function;
			gensymed_symbol = estructure_slot(gensymed_symbol,
				Qinitialization,Nil);
			gensymed_symbol_2 = Nil;
			gensymed_symbol_3 = Nil;
			gensymed_symbol_4 = Nil;
			result = inline_funcall_4(gensymed_symbol_1,
				gensymed_symbol,gensymed_symbol_2,
				gensymed_symbol_3,gensymed_symbol_4);
		    }
		    else
			result = VALUES_1(Nil);
		    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
		    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
			result = VALUES_2(Bad_phrase,error_string_qm);
			goto end_safe_category_setter_calling_block;
		    }
		    else
			initialization_phrase = parse_result_or_bad_phrase;
		}
		else {
		    temp = Bad_phrase;
		    temp_1 = tformat_text_string(3,string_constant_83,
			    estructure_slot(gensymed_symbol,
			    Qsystem_attribute_designation,Nil),Nil);
		    result = VALUES_2(temp,temp_1);
		    goto end_block_default_overrides_for_object_definitions_setter;
		}
	    }
	    if (EQ(grammar_category_qm,Qvariable_frame_flags))
		temp_1 = Qvariable;
	    else if (EQ(grammar_category_qm,Qparameter_frame_flags))
		temp_1 = Qparameter;
	    else
		temp_1 = defining_class;
	    temp_1 = phrase_list_3(slot_name_to_use,initialization_phrase,
		    temp_1);
	}
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_3;
      end_loop_3:
	temp_1 = ab_loopvar_;
	goto end_4;
	temp_1 = Qnil;
      end_4:;
	result = phrase_cons(Qsc,temp_1);
      end_block_default_overrides_for_object_definitions_setter:
      end_safe_category_setter_calling_block:;
    }
    else
	result = VALUES_1(Qnone);
  end_default_overrides_for_object_definitions_evaluation_setter:
    return result;
}

static Object Qsupply_simulation_subtable;  /* supply-simulation-subtable */

/* DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS-EVALUATION-GETTER */
Object default_overrides_for_object_definitions_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object default_override, ab_loop_list_, user_defined_p, slot_name;
    Object specified_class_of_override_qm, override_alias, slot_description_qm;
    Object unaliased_slot_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, gensymed_symbol, source_attribute_name;
    Object source_value_type_phrase, source_initial_value;
    Object source_initial_item_class, source_initial_type, gensymed_symbol_1;
    Object value, evaluation_value_qm, temp_1;

    x_note_fn_call(203,185);
    default_override = Nil;
    ab_loop_list_ = slot_value;
    user_defined_p = Nil;
    slot_name = Nil;
    specified_class_of_override_qm = Nil;
    override_alias = Nil;
    slot_description_qm = Nil;
    unaliased_slot_name = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    default_override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    user_defined_p = EQ(THIRD(default_override),Quser_defined) ? T : Nil;
    slot_name = FIRST(default_override);
    specified_class_of_override_qm = THIRD(default_override);
    if ( !TRUEP(user_defined_p)) {
	if (specified_class_of_override_qm) {
	    temp = get_alias_for_slot_name_if_any(slot_name,
		    specified_class_of_override_qm);
	    if (temp);
	    else
		temp = slot_name;
	    override_alias = temp;
	}
	else
	    override_alias = map_system_slot_name_to_alias(slot_name,frame);
    }
    else
	override_alias = Nil;
    slot_description_qm =  !TRUEP(user_defined_p) ? 
	    possibly_aliased_slot_description_from_superior_class(override_alias,
	    frame) : Nil;
    if (user_defined_p)
	unaliased_slot_name = slot_name;
    else if (specified_class_of_override_qm) {
	temp = get_slot_name_for_alias_if_any(override_alias,
		specified_class_of_override_qm);
	if (temp);
	else
	    temp = override_alias;
	unaliased_slot_name = temp;
    }
    else
	unaliased_slot_name = map_alias_to_system_slot_name(override_alias,
		frame);
    if (user_defined_p || slot_description_qm && 
	    assq_function(Quser_overridable,ISVREF(slot_description_qm,
	    (SI_Long)9L))) {
	if (user_defined_p) {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    source_attribute_name = CAR(default_override);
	    source_value_type_phrase = CADR(default_override);
	    source_initial_value = source_value_type_phrase ? 
		    (CONSP(source_value_type_phrase) && 
		    EQ(M_CDR(source_value_type_phrase),Qsequence) || 
		    CONSP(source_value_type_phrase) && 
		    EQ(M_CDR(source_value_type_phrase),Qab_structure) ? 
		    source_value_type_phrase : 
		    M_CAR(source_value_type_phrase)) : Qnil;
	    source_initial_item_class = CONSP(source_initial_value) && 
		    EQ(M_CAR(source_initial_value),Kfuncall) ? 
		    THIRD(source_initial_value) : Nil;
	    if (source_value_type_phrase) {
		if (CONSP(source_value_type_phrase) && 
			EQ(M_CDR(source_value_type_phrase),Qsequence) || 
			CONSP(source_value_type_phrase) && 
			EQ(M_CDR(source_value_type_phrase),Qab_structure))
		    source_initial_type = CDR(source_value_type_phrase);
		else if (source_initial_item_class)
		    source_initial_type = source_initial_item_class;
		else
		    source_initial_type = 
			    M_CAR(M_CDR(source_value_type_phrase));
	    }
	    else
		source_initial_type = Nil;
	    set_evaluation_structure_slot(gensymed_symbol,
		    Quser_attribute_name,CONSP(source_attribute_name) && 
		    EQ(M_CAR(source_attribute_name),Qclass_qualified_name) 
		    ? 
		    convert_class_qualified_list_to_keyword_symbol(source_attribute_name) 
		    : source_attribute_name);
	    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	    value = 
		    make_initial_value_for_user_given_type(source_initial_value,
		    source_initial_type);
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qinitial_value,value);
	    value = make_initial_item_class_for_user(source_initial_value);
	    if (value)
		set_evaluation_structure_slot(gensymed_symbol_1,
			Qinitial_item_class,value);
	    set_evaluation_structure_slot(gensymed_symbol,Qinitialization,
		    gensymed_symbol_1);
	    temp = gensymed_symbol;
	}
	else {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qsystem_attribute_designation,override_alias);
	    if (EQ(slot_name,Qsimulation_details))
		evaluation_value_qm = Qsupply_simulation_subtable;
	    else {
		temp_1 = unaliased_slot_name;
		temp = specified_class_of_override_qm;
		if (temp);
		else
		    temp = ISVREF(slot_description_qm,(SI_Long)3L);
		evaluation_value_qm = 
			get_initial_evaluation_value_for_default_override(temp_1,
			temp,frame,CADR(default_override));
	    }
	    if (evaluation_value_qm)
		set_evaluation_structure_slot(gensymed_symbol,
			Qinitialization,evaluation_value_qm);
	    temp = gensymed_symbol;
	}
	ab_loopvar__2 = eval_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object list_constant_66;    /* # */

static Object list_constant_67;    /* # */

/* DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS-EVALUATION-SETTER */
Object default_overrides_for_message_definitions_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object override_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, symbol_name_text_string_1, symbol_name_length;
    Object this_char, ab_loop_it_, class_symbol, name_symbol, attribute_name;
    Object result_1, error_string_qm, fixed_initial_value, value_type_phrase;
    SI_Long next_index, length_1, i, ab_loop_bind_;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,186);
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
			  list_constant_66))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_67,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_default_overrides_for_message_definitions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value && (SI_Long)0L < 
	    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_value),(SI_Long)1L)))) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	override_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	override_info = validated_elt;
	gensymed_symbol = override_info;
	temp_1 = SYMBOL_PACKAGE(estructure_slot(gensymed_symbol,
		Quser_attribute_name,Nil));
	if (EQ(temp_1,Keyword_package_1)) {
	    symbol_name_text_string_1 = 
		    symbol_name_text_string(estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil));
	    symbol_name_length = text_string_length(symbol_name_text_string_1);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(symbol_name_length);
	    this_char = Nil;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    this_char = FIX(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i));
	    ab_loop_it_ = IFIX(this_char) == (SI_Long)58L && i + 
		    (SI_Long)1L < IFIX(symbol_name_length) ? 
		    (UBYTE_16_ISAREF_1(symbol_name_text_string_1,i + 
		    (SI_Long)1L) == (SI_Long)58L ? T : Nil) : Qnil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    result = decompose_class_qualified_symbol(estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil));
	    MVS_2(result,class_symbol,name_symbol);
	    attribute_name = phrase_list_3(Qclass_qualified_name,
		    class_symbol,name_symbol);
	}
	else
	    attribute_name = estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil);
	gensymed_symbol = estructure_slot(gensymed_symbol,Qinitialization,Nil);
	temp_1 = estructure_slot(gensymed_symbol,Qinitial_value,Nil);
	result = fix_attribute_initial_value(4,temp_1,
		estructure_slot(gensymed_symbol,Qinitial_item_class,Nil),
		Nil,Nil);
	MVS_2(result,result_1,error_string_qm);
	if (EQ(result_1,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_setter;
	}
	else
	    fixed_initial_value = result_1;
	value_type_phrase = fix_override_initial_value(fixed_initial_value);
	ab_loopvar__2 = phrase_cons(phrase_list_3(attribute_name,
		value_type_phrase,Quser_defined),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	result = phrase_cons(Qsc,temp_1);
    }
    else
	result = VALUES_1(Qnone);
  end_setter:
  end_default_overrides_for_message_definitions_evaluation_setter:
    return result;
}

/* DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS-EVALUATION-GETTER */
Object default_overrides_for_message_definitions_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object default_override, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, source_attribute_name;
    Object source_value_type_phrase, source_initial_value;
    Object source_initial_item_class, source_initial_type, gensymed_symbol_2;
    Object value, temp;

    x_note_fn_call(203,187);
    default_override = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    default_override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    source_attribute_name = CAR(default_override);
    source_value_type_phrase = CADR(default_override);
    source_initial_value = source_value_type_phrase ? 
	    (CONSP(source_value_type_phrase) && 
	    EQ(M_CDR(source_value_type_phrase),Qsequence) || 
	    CONSP(source_value_type_phrase) && 
	    EQ(M_CDR(source_value_type_phrase),Qab_structure) ? 
	    source_value_type_phrase : M_CAR(source_value_type_phrase)) : Qnil;
    source_initial_item_class = CONSP(source_initial_value) && 
	    EQ(M_CAR(source_initial_value),Kfuncall) ? 
	    THIRD(source_initial_value) : Nil;
    if (source_value_type_phrase) {
	if (CONSP(source_value_type_phrase) && 
		EQ(M_CDR(source_value_type_phrase),Qsequence) || 
		CONSP(source_value_type_phrase) && 
		EQ(M_CDR(source_value_type_phrase),Qab_structure))
	    source_initial_type = CDR(source_value_type_phrase);
	else if (source_initial_item_class)
	    source_initial_type = source_initial_item_class;
	else
	    source_initial_type = M_CAR(M_CDR(source_value_type_phrase));
    }
    else
	source_initial_type = Nil;
    set_evaluation_structure_slot(gensymed_symbol_1,Quser_attribute_name,
	    CONSP(source_attribute_name) && 
	    EQ(M_CAR(source_attribute_name),Qclass_qualified_name) ? 
	    convert_class_qualified_list_to_keyword_symbol(source_attribute_name) 
	    : source_attribute_name);
    gensymed_symbol_2 = allocate_evaluation_structure(Nil);
    value = make_initial_value_for_user_given_type(source_initial_value,
	    source_initial_type);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol_2,Qinitial_value,value);
    value = make_initial_item_class_for_user(source_initial_value);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol_2,
		Qinitial_item_class,value);
    set_evaluation_structure_slot(gensymed_symbol_1,Qinitialization,
	    gensymed_symbol_2);
    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
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

static Object list_constant_68;    /* # */

/* DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS-EVALUATION-SETTER */
Object default_overrides_for_connection_definitions_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object override_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, symbol_name_text_string_1, symbol_name_length;
    Object this_char, ab_loop_it_, class_symbol, name_symbol, attribute_name;
    Object result_1, error_string_qm, fixed_initial_value, value_type_phrase;
    SI_Long next_index, length_1, i, ab_loop_bind_;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,188);
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
			  list_constant_68))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_67,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_default_overrides_for_connection_definitions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value && (SI_Long)0L < 
	    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_value),(SI_Long)1L)))) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	override_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	override_info = validated_elt;
	gensymed_symbol = override_info;
	temp_1 = SYMBOL_PACKAGE(estructure_slot(gensymed_symbol,
		Quser_attribute_name,Nil));
	if (EQ(temp_1,Keyword_package_1)) {
	    symbol_name_text_string_1 = 
		    symbol_name_text_string(estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil));
	    symbol_name_length = text_string_length(symbol_name_text_string_1);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(symbol_name_length);
	    this_char = Nil;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    this_char = FIX(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i));
	    ab_loop_it_ = IFIX(this_char) == (SI_Long)58L && i + 
		    (SI_Long)1L < IFIX(symbol_name_length) ? 
		    (UBYTE_16_ISAREF_1(symbol_name_text_string_1,i + 
		    (SI_Long)1L) == (SI_Long)58L ? T : Nil) : Qnil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    result = decompose_class_qualified_symbol(estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil));
	    MVS_2(result,class_symbol,name_symbol);
	    attribute_name = phrase_list_3(Qclass_qualified_name,
		    class_symbol,name_symbol);
	}
	else
	    attribute_name = estructure_slot(gensymed_symbol,
		    Quser_attribute_name,Nil);
	gensymed_symbol = estructure_slot(gensymed_symbol,Qinitialization,Nil);
	temp_1 = estructure_slot(gensymed_symbol,Qinitial_value,Nil);
	result = fix_attribute_initial_value(4,temp_1,
		estructure_slot(gensymed_symbol,Qinitial_item_class,Nil),
		Nil,Nil);
	MVS_2(result,result_1,error_string_qm);
	if (EQ(result_1,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_setter;
	}
	else
	    fixed_initial_value = result_1;
	value_type_phrase = fix_override_initial_value(fixed_initial_value);
	ab_loopvar__2 = phrase_cons(phrase_list_3(attribute_name,
		value_type_phrase,Quser_defined),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	result = phrase_cons(Qsc,temp_1);
    }
    else
	result = VALUES_1(Qnone);
  end_setter:
  end_default_overrides_for_connection_definitions_evaluation_setter:
    return result;
}

/* DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS-EVALUATION-GETTER */
Object default_overrides_for_connection_definitions_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object default_override, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, source_attribute_name;
    Object source_value_type_phrase, source_initial_value;
    Object source_initial_item_class, source_initial_type, gensymed_symbol_2;
    Object value, temp;

    x_note_fn_call(203,189);
    default_override = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    default_override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    source_attribute_name = CAR(default_override);
    source_value_type_phrase = CADR(default_override);
    source_initial_value = source_value_type_phrase ? 
	    (CONSP(source_value_type_phrase) && 
	    EQ(M_CDR(source_value_type_phrase),Qsequence) || 
	    CONSP(source_value_type_phrase) && 
	    EQ(M_CDR(source_value_type_phrase),Qab_structure) ? 
	    source_value_type_phrase : M_CAR(source_value_type_phrase)) : Qnil;
    source_initial_item_class = CONSP(source_initial_value) && 
	    EQ(M_CAR(source_initial_value),Kfuncall) ? 
	    THIRD(source_initial_value) : Nil;
    if (source_value_type_phrase) {
	if (CONSP(source_value_type_phrase) && 
		EQ(M_CDR(source_value_type_phrase),Qsequence) || 
		CONSP(source_value_type_phrase) && 
		EQ(M_CDR(source_value_type_phrase),Qab_structure))
	    source_initial_type = CDR(source_value_type_phrase);
	else if (source_initial_item_class)
	    source_initial_type = source_initial_item_class;
	else
	    source_initial_type = M_CAR(M_CDR(source_value_type_phrase));
    }
    else
	source_initial_type = Nil;
    set_evaluation_structure_slot(gensymed_symbol_1,Quser_attribute_name,
	    CONSP(source_attribute_name) && 
	    EQ(M_CAR(source_attribute_name),Qclass_qualified_name) ? 
	    convert_class_qualified_list_to_keyword_symbol(source_attribute_name) 
	    : source_attribute_name);
    gensymed_symbol_2 = allocate_evaluation_structure(Nil);
    value = make_initial_value_for_user_given_type(source_initial_value,
	    source_initial_type);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol_2,Qinitial_value,value);
    value = make_initial_item_class_for_user(source_initial_value);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol_2,
		Qinitial_item_class,value);
    set_evaluation_structure_slot(gensymed_symbol_1,Qinitialization,
	    gensymed_symbol_2);
    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
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

static Object list_constant_69;    /* # */

static Object list_constant_70;    /* # */

static Object Qblock_3_dot_1415926;  /* block-3.1415926 */

static Object Qgranularity;        /* granularity */

static Object Qdisplay_interval;   /* display-interval */

static Object Qupdate_interval;    /* update-interval */

static Object Qinterval_with_granularity;  /* interval-with-granularity */

/* PLOT-UPDATE-INTERVAL-SPEC-EVALUATION-SETTER */
Object plot_update_interval_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, tag_temp;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object value_or_bad_phrase, error_string_qm, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_catch(1);
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(203,190);
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
			  list_constant_69))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_70,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_plot_update_interval_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    tag_temp = UNIQUE_TAG(Qblock_3_dot_1415926);
    if (PUSH_CATCH(tag_temp,0)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (estructure_slot(evaluation_value,Qgranularity,Nil)) {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)3L) : 
			Qnil;
		if (function) {
		    gensymed_symbol = function;
		    gensymed_symbol_1 = estructure_slot(evaluation_value,
			    Qupdate_interval,Nil);
		    gensymed_symbol_2 = Nil;
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    result = inline_funcall_4(gensymed_symbol,
			    gensymed_symbol_1,gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4);
		}
		else
		    result = VALUES_1(Nil);
		MVS_2(result,value_or_bad_phrase,error_string_qm);
		if (EQ(value_or_bad_phrase,Bad_phrase)) {
		    result = VALUES_2(Bad_phrase,error_string_qm);
		    THROW(tag_temp,result);
		}
		value = 
			evaluation_value_value(estructure_slot(evaluation_value,
			Qgranularity,Nil));
		if (FIXNUMP(value))
		    temp_1 = value;
		else if (INLINE_LONG_P(value) != (SI_Long)0L) {
		    new_long = allocate_managed_long_box();
		    aref_new_value = INTEGER_TO_INT64(value);
		    set_aref1(new_long,FIX((SI_Long)0L),
			    INT64_TO_INTEGER(aref_new_value));
		    temp_1 = note_use_of_managed_long_in_phrase(new_long);
		}
		else {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
		    temp_1 = note_use_of_managed_float_in_phrase(new_float);
		}
		result = phrase_list_3(Qinterval_with_granularity,
			value_or_bad_phrase,temp_1);
	    }
	    else {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)3L) : 
			Qnil;
		if (function) {
		    gensymed_symbol = function;
		    gensymed_symbol_1 = estructure_slot(evaluation_value,
			    Qupdate_interval,Nil);
		    gensymed_symbol_2 = Nil;
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    result = inline_funcall_4(gensymed_symbol,
			    gensymed_symbol_1,gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4);
		}
		else
		    result = VALUES_1(Nil);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
  end_plot_update_interval_spec_evaluation_setter:
    return result;
}

/* PLOT-UPDATE-INTERVAL-SPEC-EVALUATION-GETTER */
Object plot_update_interval_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, temp, category_evaluator_interface, function;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, item_or_value, x2, temp_2, value;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    Object temp_3, temp_4;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(203,191);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (CONSP(slot_value) && EQ(M_CAR(slot_value),
		Qinterval_with_granularity)) {
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
		temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qupdate_interval;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qupdate_interval;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_2 = function;
		    gensymed_symbol_3 = CADR(slot_value);
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = Nil;
		    item_or_value = inline_funcall_3(gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		else
		    item_or_value = Nil;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_2 = function;
		    gensymed_symbol_3 = CADR(slot_value);
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = Nil;
		    item_or_value = inline_funcall_3(gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		else
		    item_or_value = Nil;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qgranularity;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qgranularity;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		value = CADDR(slot_value);
		if (FIXNUMP(value))
		    item_or_value = value;
		else if ( !TRUEP(value))
		    item_or_value = Evaluation_false_value;
		else if (EQ(value,T))
		    item_or_value = Evaluation_true_value;
		else if (SYMBOLP(value))
		    item_or_value = value;
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_float(value);
		else if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_2 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_2;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = amf_available_array_cons_qm;
			    temp = Available_float_array_conses_tail_vector;
			    temp_2 = Current_thread_index;
			    SVREF(temp,temp_2) = amf_available_array_cons_qm;
			}
			else {
			    temp = Available_float_array_conses_vector;
			    temp_2 = Current_thread_index;
			    SVREF(temp,temp_2) = amf_available_array_cons_qm;
			    temp = Available_float_array_conses_tail_vector;
			    temp_2 = Current_thread_index;
			    SVREF(temp,temp_2) = amf_available_array_cons_qm;
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    item_or_value = new_float;
		}
		else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_long(value);
		else if (INLINE_LONG_P(value) != (SI_Long)0L)
		    item_or_value = make_evaluation_long(value);
		else if (text_string_p(value))
		    item_or_value = copy_as_wide_string(value);
		else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		    gensymed_symbol_2 = M_CAR(value);
		    if (FIXNUM_EQ(gensymed_symbol_2,Truth))
			item_or_value = Evaluation_true_value;
		    else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
			item_or_value = Evaluation_false_value;
		    else
			item_or_value = eval_cons_1(gensymed_symbol_2,
				Qtruth_value);
		}
		else
		    item_or_value = error((SI_Long)2L,
			    "Bad type ~a for make-evaluation-value-based-on-type.",
			    type_of(value));
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		value = CADDR(slot_value);
		if (FIXNUMP(value))
		    item_or_value = value;
		else if ( !TRUEP(value))
		    item_or_value = Evaluation_false_value;
		else if (EQ(value,T))
		    item_or_value = Evaluation_true_value;
		else if (SYMBOLP(value))
		    item_or_value = value;
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_float(value);
		else if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    item_or_value = new_float;
		}
		else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_long(value);
		else if (INLINE_LONG_P(value) != (SI_Long)0L)
		    item_or_value = make_evaluation_long(value);
		else if (text_string_p(value))
		    item_or_value = copy_as_wide_string(value);
		else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		    gensymed_symbol_2 = M_CAR(value);
		    if (FIXNUM_EQ(gensymed_symbol_2,Truth))
			item_or_value = Evaluation_true_value;
		    else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
			item_or_value = Evaluation_false_value;
		    else
			item_or_value = eval_cons_1(gensymed_symbol_2,
				Qtruth_value);
		}
		else
		    item_or_value = error((SI_Long)2L,
			    "Bad type ~a for make-evaluation-value-based-on-type.",
			    type_of(value));
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)4L)) = temp_2;
	    }
	    temp_4 = eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else {
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
		temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qupdate_interval;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qupdate_interval;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_2 = function;
		    gensymed_symbol_3 = slot_value;
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = Nil;
		    item_or_value = inline_funcall_3(gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		else
		    item_or_value = Nil;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_2 = function;
		    gensymed_symbol_3 = slot_value;
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = Nil;
		    item_or_value = inline_funcall_3(gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		else
		    item_or_value = Nil;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	    }
	    temp_4 = eval_cons_1(gensymed_symbol,Qab_structure);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    GENSYM_RETURN_ONE(temp_4);
    return VALUES_1(Nil);
}

static Object string_constant_84;  /* "multiple use of names" */

static Object Qcompound_type_descriptor;  /* compound-type-descriptor */

/* MAKE-PARSE-RESULT-FOR-MULTIPLE-COMPOUND-SLOT */
Object make_parse_result_for_multiple_compound_slot(evaluation_value,frame,
	    compound_type)
    Object evaluation_value, frame, compound_type;
{
    Object header, default_seen_p, length_1, triples, header_or_bad_phrase;
    Object error_string_qm, id_list, index_1, gensymed_symbol, held_vector;
    Object struct_1, id, elt_1, validated_elt, temp, temp_1, temp_2;
    Object new_triples_or_bad_phrase;
    SI_Long next_index, length_2;
    Object result;

    x_note_fn_call(203,192);
    header = Nil;
    default_seen_p = Nil;
    length_1 = FIXNUM_SUB1(ISVREF(M_CAR(evaluation_value),(SI_Long)1L));
    triples = Qnil;
    result = get_multiple_compound_slot_parse_result_header(evaluation_value);
    MVS_2(result,header_or_bad_phrase,error_string_qm);
    if (EQ(header_or_bad_phrase,Bad_phrase))
	return VALUES_2(Bad_phrase,error_string_qm);
    else
	header = header_or_bad_phrase;
    id_list = Qnil;
    index_1 = FIX((SI_Long)0L);
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_2 = (SI_Long)0L;
    struct_1 = Nil;
    id = Nil;
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
    struct_1 = validated_elt;
    id = get_component_group_id_from_structure(struct_1);
    if (id && memq_function(id,id_list)) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(1,string_constant_84);
	return VALUES_2(temp,temp_1);
    }
    else
	id_list = phrase_cons(id,id_list);
    if (EQ(id,Qdefault))
	default_seen_p = T;
    else
	index_1 = FIXNUM_ADD1(index_1);
    temp_2 = struct_1;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(compound_type),
	    Qcompound_type_descriptor);
    temp_1 = id;
    if (temp_1);
    else
	temp_1 = index_1;
    result = add_triples_for_compound_slot_structure_parse_result(frame,
	    temp_2,temp,temp_1,T);
    MVS_2(result,new_triples_or_bad_phrase,error_string_qm);
    if (EQ(new_triples_or_bad_phrase,Bad_phrase))
	return VALUES_2(Bad_phrase,error_string_qm);
    else
	triples = nconc2(triples,new_triples_or_bad_phrase);
    goto next_loop;
  end_loop:;
    return phrase_list_2(phrase_list_2(default_seen_p ? 
	    FIXNUM_SUB1(length_1) : length_1,header),phrase_cons(Qsc,triples));
}

static Object Qsingle;             /* single */

/* MAKE-PARSE-RESULT-FOR-SINGLE-COMPOUND-SLOT */
Object make_parse_result_for_single_compound_slot(evaluation_value,frame,
	    compound_type)
    Object evaluation_value, frame, compound_type;
{
    Object triples_or_bad_phrase, error_string_qm;
    Object result;

    x_note_fn_call(203,193);
    result = add_triples_for_compound_slot_structure_parse_result(frame,
	    evaluation_value,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(compound_type),
	    Qcompound_type_descriptor),Qsingle,Nil);
    MVS_2(result,triples_or_bad_phrase,error_string_qm);
    if (EQ(triples_or_bad_phrase,Bad_phrase))
	return VALUES_2(Bad_phrase,error_string_qm);
    else
	return phrase_list_2(Nil,phrase_cons(Qsc,triples_or_bad_phrase));
}

static Object list_constant_71;    /* # */

static Object list_constant_72;    /* # */

static Object Qpoint_format;       /* point-format */

/* TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC-EVALUATION-SETTER */
Object trend_chart_point_formats_grammar_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, x;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,194);
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
			  list_constant_71))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_72,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_point_formats_grammar_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    x = make_parse_result_for_multiple_compound_slot(evaluation_value,
	    frame,Qpoint_format);
    result = VALUES_1(x);
  end_trend_chart_point_formats_grammar_spec_evaluation_setter:
    return result;
}

/* TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC-EVALUATION-GETTER */
Object trend_chart_point_formats_grammar_spec_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,195);
    GENSYM_RETURN_ONE(make_evaluation_sequence_from_multiple_compound_slot(frame,
	    slot_value,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_format),
	    Qcompound_type_descriptor),Nil));
    return VALUES_1(Nil);
}

static Object list_constant_73;    /* # */

static Object list_constant_74;    /* # */

static Object Qconnector_format;   /* connector-format */

/* TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC-EVALUATION-SETTER */
Object trend_chart_connector_formats_grammar_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, x;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,196);
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
			  list_constant_73))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_74,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_connector_formats_grammar_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    x = make_parse_result_for_multiple_compound_slot(evaluation_value,
	    frame,Qconnector_format);
    result = VALUES_1(x);
  end_trend_chart_connector_formats_grammar_spec_evaluation_setter:
    return result;
}

/* TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC-EVALUATION-GETTER */
Object trend_chart_connector_formats_grammar_spec_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,197);
    GENSYM_RETURN_ONE(make_evaluation_sequence_from_multiple_compound_slot(frame,
	    slot_value,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnector_format),
	    Qcompound_type_descriptor),Nil));
    return VALUES_1(Nil);
}

static Object list_constant_75;    /* # */

static Object list_constant_76;    /* # */

static Object Qvalue_axis;         /* value-axis */

/* TREND-CHART-VALUE-AXES-GRAMMAR-SPEC-EVALUATION-SETTER */
Object trend_chart_value_axes_grammar_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, x;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,198);
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
			  list_constant_75))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_76,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_value_axes_grammar_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    x = make_parse_result_for_multiple_compound_slot(evaluation_value,
	    frame,Qvalue_axis);
    result = VALUES_1(x);
  end_trend_chart_value_axes_grammar_spec_evaluation_setter:
    return result;
}

/* TREND-CHART-VALUE-AXES-GRAMMAR-SPEC-EVALUATION-GETTER */
Object trend_chart_value_axes_grammar_spec_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,199);
    GENSYM_RETURN_ONE(make_evaluation_sequence_from_multiple_compound_slot(frame,
	    slot_value,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvalue_axis),
	    Qcompound_type_descriptor),Nil));
    return VALUES_1(Nil);
}

static Object list_constant_77;    /* # */

static Object list_constant_78;    /* # */

static Object Qtrend_chart_format;  /* trend-chart-format */

/* TREND-CHART-FORMAT-GRAMMAR-SPEC-EVALUATION-SETTER */
Object trend_chart_format_grammar_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, x;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,200);
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
			  list_constant_77))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_78,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_format_grammar_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    x = make_parse_result_for_single_compound_slot(evaluation_value,frame,
	    Qtrend_chart_format);
    result = VALUES_1(x);
  end_trend_chart_format_grammar_spec_evaluation_setter:
    return result;
}

/* TREND-CHART-FORMAT-GRAMMAR-SPEC-EVALUATION-GETTER */
Object trend_chart_format_grammar_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,201);
    GENSYM_RETURN_ONE(make_evaluation_structure_from_slot_component(frame,
	    slot_value,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtrend_chart_format),
	    Qcompound_type_descriptor),T,Nil));
    return VALUES_1(Nil);
}

static Object list_constant_79;    /* # */

static Object list_constant_80;    /* # */

static Object Qtime_axis;          /* time-axis */

/* TREND-CHART-TIME-AXIS-GRAMMAR-SPEC-EVALUATION-SETTER */
Object trend_chart_time_axis_grammar_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, x;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,202);
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
			  list_constant_79))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_80,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_time_axis_grammar_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    x = make_parse_result_for_single_compound_slot(evaluation_value,frame,
	    Qtime_axis);
    result = VALUES_1(x);
  end_trend_chart_time_axis_grammar_spec_evaluation_setter:
    return result;
}

/* TREND-CHART-TIME-AXIS-GRAMMAR-SPEC-EVALUATION-GETTER */
Object trend_chart_time_axis_grammar_spec_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,203);
    GENSYM_RETURN_ONE(make_evaluation_structure_from_slot_component(frame,
	    slot_value,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtime_axis),
	    Qcompound_type_descriptor),T,Nil));
    return VALUES_1(Nil);
}

static Object list_constant_81;    /* # */

static Object list_constant_82;    /* # */

static Object Qplot;               /* plot */

/* TREND-CHART-PLOTS-GRAMMAR-SPEC-EVALUATION-SETTER */
Object trend_chart_plots_grammar_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, x;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,204);
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
			  list_constant_81))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_82,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_plots_grammar_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    x = make_parse_result_for_multiple_compound_slot(evaluation_value,
	    frame,Qplot);
    result = VALUES_1(x);
  end_trend_chart_plots_grammar_spec_evaluation_setter:
    return result;
}

/* TREND-CHART-PLOTS-GRAMMAR-SPEC-EVALUATION-GETTER */
Object trend_chart_plots_grammar_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(203,205);
    GENSYM_RETURN_ONE(make_evaluation_sequence_from_multiple_compound_slot(frame,
	    slot_value,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qplot),
	    Qcompound_type_descriptor),Nil));
    return VALUES_1(Nil);
}

static Object Qexpression;         /* expression */

static Object Qplot_expression;    /* plot-expression */

/* TREND-CHART-PLOTS-GRAMMAR-SPEC-EVALUATION-COMMITTER */
Object trend_chart_plots_grammar_spec_evaluation_committer(slot_value,
	    evaluation_value,evaluator_info)
    Object slot_value, evaluation_value, evaluator_info;
{
    Object plot_list, the_plot, gensymed_symbol, held_vector, struct_1, id;
    Object elt_1, validated_elt, plot_list_old_value, temp, expression_text_qm;
    Object plot_expression, old_text, cdr_new_value;
    SI_Long next_index, length_1;

    x_note_fn_call(203,206);
    plot_list = CDDR(slot_value);
    the_plot = Nil;
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    struct_1 = Nil;
    id = Nil;
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
    struct_1 = validated_elt;
    id = get_component_group_id_from_structure(struct_1);
    if ( !EQ(id,Qdefault)) {
	plot_list_old_value = plot_list;
	temp = FIRST(plot_list_old_value);
	plot_list = REST(plot_list_old_value);
	the_plot = temp;
	expression_text_qm = estructure_slot(struct_1,Qexpression,Nil);
	if (expression_text_qm) {
	    temp = assq_function(Qplot_expression,CDDR(the_plot));
	    plot_expression = CADR(temp);
	    old_text = CDR(plot_expression);
	    cdr_new_value = 
		    convert_text_string_to_text(copy_text_string(expression_text_qm));
	    M_CDR(plot_expression) = cdr_new_value;
	    reclaim_text(old_text);
	}
    }
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* COMPILE-WORKSPACE-TITLE-BAR-TEXT-FOR-SLOT */
Object compile_workspace_title_bar_text_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,207);
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

static Object string_constant_85;  /* " if any, otherwise " */

/* WRITE-WORKSPACE-TITLE-BAR-TEXT-FROM-SLOT */
Object write_workspace_title_bar_text_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object x, more_qm, ab_loop_list_;

    x_note_fn_call(203,208);
    if ( !TRUEP(value))
	return tformat(1,string_constant_31);
    else if (ATOM(value))
	return twrite_title_bar_text_directive_or_string(value);
    else {
	x = Nil;
	more_qm = Nil;
	ab_loop_list_ = value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	x = CAR(ab_loop_list_);
	more_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	twrite_title_bar_text_directive_or_string(x);
	if (more_qm)
	    twrite(string_constant_85);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_86;  /* "the name" */

static Object string_constant_87;  /* "the class" */

static Object Qtable_header;       /* table-header */

static Object string_constant_88;  /* "the table header" */

/* TWRITE-TITLE-BAR-TEXT-DIRECTIVE-OR-STRING */
Object twrite_title_bar_text_directive_or_string(directive_or_string)
    Object directive_or_string;
{
    Object temp;

    x_note_fn_call(203,209);
    if (text_string_p(directive_or_string))
	return twrite_parsably(directive_or_string);
    else {
	if (EQ(directive_or_string,Qname))
	    temp = string_constant_86;
	else if (EQ(directive_or_string,Qab_class))
	    temp = string_constant_87;
	else if (EQ(directive_or_string,Qtable_header))
	    temp = string_constant_88;
	else
	    temp = Qnil;
	return twrite_general_string(temp);
    }
}

static Object Qtitle_bar_text;     /* title-bar-text */

/* PUT-TITLE-BAR-TEXT */
Object put_title_bar_text(workspace,value,initializing_p)
    Object workspace, value, initializing_p;
{
    Object original_value, temp;

    x_note_fn_call(203,210);
    original_value = get_lookup_slot_value(workspace,Qtitle_bar_text);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(workspace,Qtitle_bar_text);
    temp = set_lookup_slot_value_1(workspace,Qtitle_bar_text,value);
    if ( !(initializing_p ||  !(ISVREF(workspace,(SI_Long)16L) ||  
	    !TRUEP(T) && workspace_showing_on_ui_client_p(workspace)) || 
	    equalw(value,original_value)))
	refresh_title_bar(workspace);
    return VALUES_1(temp);
}

static Object list_constant_83;    /* # */

static Object list_constant_84;    /* # */

static Object string_constant_89;  /* "workspace-title-bar-text had ~d elements, but it ~
				    *                     cannot have more than two elements"
				    */

/* WORKSPACE-TITLE-BAR-TEXT-EVALUATION-SETTER */
Object workspace_title_bar_text_evaluation_setter(new_value,frame,
	    slot_description,gensymed_symbol)
    Object new_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, length_1, x;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,211);
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
			  !TRUEP(type_specification_type_p__with_explanation(new_value,
			  list_constant_83))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(new_value,
			      list_constant_84,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_workspace_title_bar_text_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(new_value))
	result = VALUES_1(Nil);
    else if (CONSP(new_value) && EQ(M_CDR(new_value),Qsequence)) {
	length_1 = FIXNUM_SUB1(ISVREF(M_CAR(new_value),(SI_Long)1L));
	if (IFIX(length_1) == (SI_Long)1L) {
	    x = evaluation_sequence_aref(new_value,FIX((SI_Long)0L));
	    if ( !TRUEP(title_bar_directive_or_string_p(x)))
		result = values_for_bad_title_bar_directive_or_string(x);
	    else
		result = copy_for_phrase(x);
	}
	else if (IFIX(length_1) > (SI_Long)2L) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant_89,length_1);
	    result = VALUES_2(temp,temp_1);
	}
	else if (IFIX(length_1) > (SI_Long)0L)
	    result = copy_and_check_workspace_title_bar_sequence(new_value);
	else
	    result = VALUES_1(Nil);
    }
    else if ( !TRUEP(title_bar_directive_or_string_p(new_value)))
	result = values_for_bad_title_bar_directive_or_string(new_value);
    else
	result = copy_for_phrase(new_value);
  end_workspace_title_bar_text_evaluation_setter:
    return result;
}

/* WORKSPACE-TITLE-BAR-TEXT-EVALUATION-GETTER */
Object workspace_title_bar_text_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object spec_element, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float, gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(203,212);
    if (CONSP(slot_value)) {
	spec_element = Nil;
	ab_loop_list_ = slot_value;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	spec_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (FIXNUMP(spec_element))
	    temp = spec_element;
	else if ( !TRUEP(spec_element))
	    temp = Evaluation_false_value;
	else if (EQ(spec_element,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(spec_element))
	    temp = spec_element;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(spec_element) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(spec_element)) == 
		(SI_Long)1L)
	    temp = copy_managed_float(spec_element);
	else if (FLOATP(spec_element)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(spec_element);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(spec_element) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(spec_element)) == (SI_Long)1L)
	    temp = copy_managed_long(spec_element);
	else if (INLINE_LONG_P(spec_element) != (SI_Long)0L)
	    temp = make_evaluation_long(spec_element);
	else if (text_string_p(spec_element))
	    temp = copy_as_wide_string(spec_element);
	else if (CONSP(spec_element) && EQ(M_CDR(spec_element),Qtruth_value)) {
	    gensymed_symbol = M_CAR(spec_element);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(spec_element));
	ab_loopvar__2 = eval_cons_1(temp,Nil);
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
    }
    else if (slot_value) {
	if (FIXNUMP(slot_value))
	    temp = slot_value;
	else if ( !TRUEP(slot_value))
	    temp = Evaluation_false_value;
	else if (EQ(slot_value,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(slot_value))
	    temp = slot_value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L)
	    temp = copy_managed_float(slot_value);
	else if (FLOATP(slot_value)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(slot_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(slot_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L)
	    temp = copy_managed_long(slot_value);
	else if (INLINE_LONG_P(slot_value) != (SI_Long)0L)
	    temp = make_evaluation_long(slot_value);
	else if (text_string_p(slot_value))
	    temp = copy_as_wide_string(slot_value);
	else if (CONSP(slot_value) && EQ(M_CDR(slot_value),Qtruth_value)) {
	    gensymed_symbol = M_CAR(slot_value);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(slot_value));
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_90;  /* "workspace-title-bar-text contains illegal element ~s" */

/* VALUES-FOR-BAD-TITLE-BAR-DIRECTIVE-OR-STRING */
Object values_for_bad_title_bar_directive_or_string(element)
    Object element;
{
    Object temp, temp_1;

    x_note_fn_call(203,213);
    temp = Bad_phrase;
    temp_1 = tformat_text_string(2,string_constant_90,element);
    return VALUES_2(temp,temp_1);
}

static Object string_constant_91;  /* "workspace-title-bar-text had ~d elements, but it cannot ~
				    *                      have more than one element unless the first is the ~
				    *                      symbol NAME"
				    */

static Object string_constant_92;  /* "workspace-title-bar-text cannot have ~
				    *                                     the symbol NAME as its second element"
				    */

/* COPY-AND-CHECK-WORKSPACE-TITLE-BAR-SEQUENCE */
Object copy_and_check_workspace_title_bar_sequence(new_value_as_sequence)
    Object new_value_as_sequence;
{
    Object length_1, gensymed_symbol, held_vector, spec_element, result_1;
    Object ab_loopvar_, ab_loopvar__1, elt_1, validated_elt, temp, temp_1, x;
    Object ab_loop_list_, first_time_p, ab_loop_iter_flag_;
    SI_Long next_index, length_2;

    x_note_fn_call(203,214);
    length_1 = FIXNUM_SUB1(ISVREF(M_CAR(new_value_as_sequence),(SI_Long)1L));
    gensymed_symbol = new_value_as_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_2 = (SI_Long)0L;
    spec_element = Nil;
    result_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
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
    spec_element = validated_elt;
    ab_loopvar__1 = phrase_cons(copy_for_phrase(spec_element),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	result_1 = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    if (IFIX(length_1) > (SI_Long)1L &&  !EQ(FIRST(result_1),Qname)) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_91,length_1);
	return VALUES_2(temp,temp_1);
    }
    else {
	x = Nil;
	ab_loop_list_ = result_1;
	first_time_p = T;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	x = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_time_p = Nil;
	if ( !TRUEP(title_bar_directive_or_string_p(x)))
	    return values_for_bad_title_bar_directive_or_string(x);
	if (EQ(x,Qname) &&  !TRUEP(first_time_p)) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(1,string_constant_92);
	    return VALUES_2(temp,temp_1);
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
    return VALUES_1(Qnil);
}

/* TITLE-BAR-DIRECTIVE-OR-STRING-P */
Object title_bar_directive_or_string_p(directive_or_string)
    Object directive_or_string;
{
    Object temp;

    x_note_fn_call(203,215);
    temp = text_string_p(directive_or_string);
    if (temp)
	return VALUES_1(temp);
    else {
	temp = EQ(directive_or_string,Qname) ? T : Nil;
	if (temp);
	else
	    temp = EQ(directive_or_string,Qab_class) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(EQ(directive_or_string,Qtable_header) ? T : Nil);
    }
}

/* COMPILE-VIEW-PREFERENCES-FOR-SLOT */
Object compile_view_preferences_for_slot varargs_1(int, n)
{
    Object parse, gensymed_symbol, gensymed_symbol_1;
    Object parse_old_value, p, v, ab_loop_list_, result_1, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_desetq_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,216);
    INIT_ARGS_nonrelocating();
    parse = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !EQ(parse,Qnone)) {
	if (EQ(CAR(parse),Qsc)) {
	    parse_old_value = parse;
	    parse = REST(parse_old_value);
	}
	p = Nil;
	v = Nil;
	ab_loop_list_ = parse;
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	p = CAR(ab_loop_desetq_);
	v = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (v) {
	    if ( !TRUEP(getf(result_1,p,_))) {
		ab_loopvar__1 = phrase_cons(p,Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    result_1 = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		ab_loopvar__1 = phrase_cons(v,Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    result_1 = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
	    }
	}
	goto next_loop;
      end_loop:
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Kfirst;              /* :first */

static Object string_constant_93;  /* ": " */

/* TWRITE-BOOLEAN-PLIST */
Object twrite_boolean_plist(plist)
    Object plist;
{
    Object sublist, p, v, temp;

    x_note_fn_call(203,217);
    if ( !TRUEP(plist))
	return twrite(string_constant_18);
    else {
	sublist = plist;
	p = Nil;
	v = Nil;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	p = CAR(sublist);
	temp = CDR(sublist);
	v = CAR(temp);
	if (v) {
	    twrite_symbol_name(p,Kfirst,T,Nil,Nil);
	    if ( !EQ(v,T)) {
		twrite(string_constant_93);
		twrite(v);
	    }
	}
	if (CDDR(sublist))
	    twrite(string_constant_8);
	sublist = CDDR(sublist);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* WRITE-VIEW-PREFERENCES-FROM-SLOT */
Object write_view_preferences_from_slot(plist,gensymed_symbol)
    Object plist, gensymed_symbol;
{
    x_note_fn_call(203,218);
    return twrite_boolean_plist(plist);
}

static Object list_constant_85;    /* # */

static Object list_constant_86;    /* # */

/* VIEW-PREFERENCES-EVALUATION-SETTER */
Object view_preferences_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector, name;
    Object attribute_value, value, lisp_value, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    SI_Long next_index, length_1, gensymed_symbol_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,219);
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
			  list_constant_85))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_86,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_view_preferences_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	name = Nil;
	attribute_value = Nil;
	value = Nil;
	lisp_value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
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
	value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	lisp_value = CONSP(value) && EQ(M_CDR(value),Qtruth_value) ? 
		evaluation_truth_value_is_true_p(value) : value;
	if (lisp_value) {
	    ab_loopvar__2 = phrase_cons(phrase_cons(name,lisp_value),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	result = VALUES_1(ab_loopvar_);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    else
	result = VALUES_1(Nil);
  end_view_preferences_evaluation_setter:
    return result;
}

/* VIEW-PREFERENCES-EVALUATION-GETTER */
Object view_preferences_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object p, v, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(203,220);
    p = Nil;
    v = Nil;
    ab_loop_list_ = slot_value;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    p = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    v = CAR(temp);
    if (v) {
	ab_loopvar__2 = eval_cons_1(p,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = 
		eval_cons_1(make_evaluation_value_from_lisp_value(v),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
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
    GENSYM_RETURN_ONE(allocate_evaluation_structure(temp));
    return VALUES_1(Nil);
}

static Object Qon;                 /* on */

static Object list_constant_87;    /* # */

/* COMPILE-AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR-FOR-SLOT */
Object compile_automatically_show_developer_menu_bar_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object events, modes, temp, event, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(203,221);
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
    gensymed_symbol_1 = CDR(parse_result);
    events = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    modes = CAR(gensymed_symbol_1);
    temp = phrase_cons(Qon,Nil);
    event = Nil;
    ab_loop_list_ = list_constant_87;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    event = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(event,events)) {
	ab_loopvar__2 = phrase_cons(event,Nil);
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
    temp_1 = phrase_cons(temp_1,Nil);
    return VALUES_1(nconc2(temp,nconc2(temp_1,modes ? 
	    phrase_cons(remove_noise_at_head_of_list_phrase(modes),Nil) : 
	    Nil)));
}

static Object Qconnect;            /* connect */

static Object string_constant_94;  /* "initial connection" */

/* TWRITE-INTERESTING-UI-EVENT */
Object twrite_interesting_ui_event(event)
    Object event;
{
    Object temp;

    x_note_fn_call(203,222);
    temp = EQ(event,Qconnect) ? twrite(string_constant_94) : 
	    twrite_symbol(1,event);
    return VALUES_1(temp);
}

static Object string_constant_95;  /* "on " */

static Object string_constant_96;  /* " or " */

static Object Qtwrite_interesting_ui_event;  /* twrite-interesting-ui-event */

static Object string_constant_97;  /* ", or " */

static Object string_constant_98;  /* ", only in " */

static Object Qab_or;              /* or */

static Object string_constant_99;  /* "nothing" */

static Object string_constant_100;  /* " mode" */

/* WRITE-AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR-FROM-SLOT */
Object write_automatically_show_developer_menu_bar_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object events, modes;

    x_note_fn_call(203,223);
    gensymed_symbol = CDR(value);
    events = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    modes = CAR(gensymed_symbol);
    if ( !TRUEP(events))
	return twrite(string_constant_61);
    else {
	twrite(string_constant_95);
	if (IFIX(length(events)) == (SI_Long)2L) {
	    twrite_interesting_ui_event(FIRST(events));
	    twrite(string_constant_96);
	    twrite_interesting_ui_event(SECOND(events));
	}
	else
	    twrite_list_function(events,
		    SYMBOL_FUNCTION(Qtwrite_interesting_ui_event),Nil,
		    string_constant_97,string_constant_6);
	if (modes) {
	    twrite(string_constant_98);
	    write_symbol_list(4,modes,Nil,Qab_or,string_constant_99);
	    return tformat(1,string_constant_100);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object list_constant_88;    /* # */

static Object list_constant_89;    /* # */

static Object Qevents;             /* events */

static Object Qmodes;              /* modes */

/* AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR-EVALUATION-SETTER */
Object automatically_show_developer_menu_bar_evaluation_setter(value,frame,
	    slot_description,gensymed_symbol)
    Object value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, events, modes;
    Object temp_2, held_vector, event, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, mode;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(203,224);
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
			  !TRUEP(type_specification_type_p__with_explanation(value,
			  list_constant_88))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(value,list_constant_89,
			      Value_at_type_failure,Type_at_type_failure,
			      Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_automatically_show_developer_menu_bar_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    events = estructure_slot(value,Qevents,Nil);
    modes = estructure_slot(value,Qmodes,Nil);
    temp_2 = phrase_cons(Qon,Nil);
    gensymed_symbol = events;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    event = Nil;
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
    event = validated_elt;
    ab_loopvar__2 = phrase_cons(event,Nil);
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
    temp = phrase_cons(temp_1,Nil);
    if ( !(IFIX(FIXNUM_SUB1(ISVREF(M_CAR(modes),(SI_Long)1L))) == 
		(SI_Long)0L)) {
	gensymed_symbol = modes;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	mode = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	mode = validated_elt;
	ab_loopvar__2 = phrase_cons(mode,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	temp_1 = phrase_cons(temp_1,Nil);
    }
    else
	temp_1 = Nil;
    result = VALUES_1(nconc2(temp_2,nconc2(temp,temp_1)));
  end_automatically_show_developer_menu_bar_evaluation_setter:
    return result;
}

/* AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR-EVALUATION-GETTER */
Object automatically_show_developer_menu_bar_evaluation_getter(value,frame,
	    slot_description)
    Object value, frame, slot_description;
{
    Object gensymed_symbol, events, modes, temp;

    x_note_fn_call(203,225);
    gensymed_symbol = CDR(value);
    events = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    modes = CAR(gensymed_symbol);
    temp = eval_list_2(Qevents,
	    allocate_evaluation_sequence(copy_list_using_eval_conses_1(events)));
    GENSYM_RETURN_ONE(allocate_evaluation_structure(nconc2(temp,
	    eval_list_2(Qmodes,
	    allocate_evaluation_sequence(copy_list_using_eval_conses_1(modes))))));
    return VALUES_1(Nil);
}

static Object Qautomatically_show_developer_menu_bar;  /* automatically-show-developer-menu-bar */

/* SHOW-DEVELOPER-MENU-BAR-P */
Object show_developer_menu_bar_p(gensym_window,event)
    Object gensym_window, event;
{
    Object value, mode, gensymed_symbol, events, modes;

    x_note_fn_call(203,226);
    value = get_lookup_slot_value(Menu_parameters,
	    Qautomatically_show_developer_menu_bar);
    mode = ISVREF(ISVREF(gensym_window,(SI_Long)2L),(SI_Long)19L);
    gensymed_symbol = CDR(value);
    events = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    modes = CAR(gensymed_symbol);
    if (memq_function(event,events)) {
	if (modes)
	    return memq_function(mode,modes);
	else
	    return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

void grammar7_INIT()
{
    Object data_server_map_evaluation_setter_1;
    Object data_server_map_evaluation_getter_1;
    Object stub_designation_or_none_evaluation_setter_1;
    Object stub_designation_or_none_evaluation_getter_1;
    Object float_format_evaluation_setter_1, float_format_evaluation_getter_1;
    Object format_qm_evaluation_setter_1, format_qm_evaluation_getter_1;
    Object type_in_box_format_qm_evaluation_setter_1;
    Object type_in_box_format_qm_evaluation_getter_1;
    Object dial_ruling_parameter_evaluation_setter_1;
    Object dial_ruling_parameter_evaluation_getter_1;
    Object meter_ruling_parameter_evaluation_setter_1;
    Object meter_ruling_parameter_evaluation_getter_1;
    Object display_interval_evaluation_setter_1;
    Object display_interval_evaluation_getter_1, temp, temp_1;
    Object charting_library_type_select_evaluation_setter_1;
    Object charting_library_type_select_evaluation_getter_1;
    Object deadlock_detection_frequency_type_evaluation_setter_1;
    Object deadlock_detection_frequency_type_evaluation_getter_1, temp_2;
    Object g2_run_state_evaluation_getter_1;
    Object backward_compatible_g2_feature_list_evaluation_setter_1;
    Object backward_compatible_g2_feature_list_evaluation_getter_1;
    Object initial_margin_for_workspaces_evaluation_setter_1;
    Object initial_margin_for_workspaces_evaluation_getter_1;
    Object floating_point_number_text_style_name_evaluation_setter_1;
    Object floating_point_number_text_style_name_evaluation_getter_1;
    Object floating_point_number_precision_evaluation_setter_1;
    Object floating_point_number_precision_evaluation_getter_1;
    Object log_file_directory_evaluation_setter_1;
    Object log_file_directory_evaluation_getter_1;
    Object log_file_name_evaluation_setter_1;
    Object log_file_name_evaluation_getter_1;
    Object log_file_maximum_evaluation_setter_1;
    Object log_file_maximum_evaluation_getter_1;
    Object update_log_file_evaluation_setter_1;
    Object update_log_file_evaluation_getter_1;
    Object close_log_file_evaluation_setter_1;
    Object close_log_file_evaluation_getter_1;
    Object back_up_log_file_evaluation_setter_1;
    Object back_up_log_file_evaluation_getter_1;
    Object cross_section_pattern_evaluation_setter_1;
    Object cross_section_pattern_evaluation_getter_1;
    Object g2_meter_name_evaluation_setter_1;
    Object g2_meter_name_evaluation_getter_1;
    Object gfi_yes_or_no_qm_evaluation_setter_1;
    Object gfi_yes_or_no_qm_evaluation_getter_1;
    Object gfi_file_format_evaluation_setter_1;
    Object gfi_file_format_evaluation_getter_1;
    Object gfi_time_stamp_format_evaluation_setter_1;
    Object gfi_time_stamp_format_evaluation_getter_1;
    Object gfi_output_file_update_frequency_evaluation_setter_1;
    Object gfi_output_file_update_frequency_evaluation_getter_1;
    Object attributes_which_identify_a_network_item_reference_evaluation_setter_1;
    Object attributes_which_identify_a_network_item_reference_evaluation_getter_1;
    Object options_for_item_reference_evaluation_setter_1;
    Object options_for_item_reference_evaluation_getter_1;
    Object gsi_variable_grouping_specification_evaluation_setter_1;
    Object gsi_variable_grouping_specification_evaluation_getter_1;
    Object when_to_show_value_evaluation_setter_1;
    Object when_to_show_value_evaluation_getter_1;
    Object gfi_input_variables_update_mode_evaluation_setter_1;
    Object gfi_input_variables_update_mode_evaluation_getter_1;
    Object default_overrides_for_class_definitions_evaluation_setter_1;
    Object default_overrides_for_class_definitions_evaluation_getter_1;
    Object default_overrides_for_object_definitions_evaluation_setter_1;
    Object default_overrides_for_object_definitions_evaluation_getter_1;
    Object default_overrides_for_message_definitions_evaluation_setter_1;
    Object default_overrides_for_message_definitions_evaluation_getter_1;
    Object default_overrides_for_connection_definitions_evaluation_setter_1;
    Object default_overrides_for_connection_definitions_evaluation_getter_1;
    Object plot_update_interval_spec_evaluation_setter_1;
    Object plot_update_interval_spec_evaluation_getter_1;
    Object trend_chart_point_formats_grammar_spec_evaluation_setter_1;
    Object trend_chart_point_formats_grammar_spec_evaluation_getter_1;
    Object trend_chart_connector_formats_grammar_spec_evaluation_setter_1;
    Object trend_chart_connector_formats_grammar_spec_evaluation_getter_1;
    Object trend_chart_value_axes_grammar_spec_evaluation_setter_1;
    Object trend_chart_value_axes_grammar_spec_evaluation_getter_1;
    Object trend_chart_format_grammar_spec_evaluation_setter_1;
    Object trend_chart_format_grammar_spec_evaluation_getter_1;
    Object trend_chart_time_axis_grammar_spec_evaluation_setter_1;
    Object trend_chart_time_axis_grammar_spec_evaluation_getter_1;
    Object trend_chart_plots_grammar_spec_evaluation_setter_1;
    Object trend_chart_plots_grammar_spec_evaluation_getter_1;
    Object trend_chart_plots_grammar_spec_evaluation_committer_1;
    Object workspace_title_bar_text_evaluation_setter_1;
    Object workspace_title_bar_text_evaluation_getter_1;
    Object view_preferences_evaluation_setter_1;
    Object view_preferences_evaluation_getter_1;
    Object automatically_show_developer_menu_bar_evaluation_setter_1;
    Object automatically_show_developer_menu_bar_evaluation_getter_1;
    Object Qnamed, list_constant_406, list_constant_405, list_constant_404;
    Object list_constant_403, AB_package, list_constant_402, list_constant_92;
    Object Qtype_specification_simple_expansion;
    Object Qwrite_automatically_show_developer_menu_bar_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler;
    Object Qcompile_automatically_show_developer_menu_bar_for_slot, Qreset;
    Object Qpause, Qinteresting_ui_event, Qinteresting_ui_events;
    Object string_constant_177, string_constant_176, Qview_preferences;
    Object list_constant_401, list_constant_400, list_constant_399;
    Object list_constant_398, list_constant_397, list_constant_396;
    Object Qfixed_size, Qunselectable, Qvisible_grid, list_constant_140;
    Object Qwrite_view_preferences_from_slot;
    Object Qcompile_view_preferences_for_slot, Qview_preference;
    Object string_constant_175, Qworkspace_title_bar_text, list_constant_395;
    Object list_constant_394, Qtext, list_constant_393, list_constant_392;
    Object list_constant_375, list_constant_391, list_constant_134;
    Object Qslot_putter, Qput_title_bar_text;
    Object Qwrite_workspace_title_bar_text_from_slot, string_constant_174;
    Object string_constant_173, Qnil_function;
    Object Qcompile_workspace_title_bar_text_for_slot;
    Object Qcategory_committer_function, Qtrend_chart_plots_grammar_spec;
    Object list_constant_151, list_constant_390, list_constant_389;
    Object list_constant_388, list_constant_387, list_constant_386;
    Object list_constant_385, list_constant_384, list_constant_383;
    Object list_constant_382, list_constant_381, list_constant_380;
    Object list_constant_379, list_constant_378, list_constant_377;
    Object list_constant_376, list_constant_291, list_constant_290;
    Object list_constant_298, Qinclude_in_legend_qm, list_constant_217;
    Object Quse_simulator_qm, Qmay_request_event_updates_qm;
    Object Qmay_request_data_seeking_qm, list_constant_215, Qupdate_priority;
    Object list_constant_354, Qwait_interval, list_constant_374;
    Object Qconnector_format_name_or_number, Qpoint_format_name_or_number;
    Object Qvalue_axis_name_or_number, list_constant_373, Qcomponent_reference;
    Object Quse_local_history_qm, Qtrend_chart_time_axis_grammar_spec;
    Object list_constant_372, list_constant_371, list_constant_329;
    Object list_constant_328, list_constant_327, list_constant_370;
    Object list_constant_369, list_constant_368, list_constant_367;
    Object list_constant_366, list_constant_365, list_constant_364;
    Object list_constant_363, list_constant_362, list_constant_361;
    Object list_constant_360, list_constant_359, list_constant_332;
    Object list_constant_331, list_constant_287, Qlabel_color;
    Object list_constant_358, Qtime_format, Qtime_axis_label_format_spec;
    Object list_constant_357, Qlabel_alignment, Qtime_axis_label_alignment;
    Object list_constant_356, Qlabel_frequency;
    Object Q2d_time_axis_tickmark_frequency_spec, Qrelative_labels_visible_qm;
    Object Qabsolute_labels_visible_qm, list_constant_355;
    Object Qjump_scroll_interval, Qtrend_chart_scroll_interval;
    Object Qjump_scroll_qm, list_constant_353, Qend_time, Q2d_end_time_spec;
    Object list_constant_352, Qtotal_time_span, Q2d_total_time_span_spec;
    Object list_constant_351, Qdata_window_time_span, Q2d_time_span_spec;
    Object Qtrend_chart_format_grammar_spec, list_constant_350;
    Object list_constant_349, list_constant_348, list_constant_347;
    Object list_constant_346, list_constant_345, list_constant_344;
    Object list_constant_343, list_constant_342, list_constant_341;
    Object list_constant_340, list_constant_339, list_constant_338;
    Object list_constant_337, Qtitle_position, Qtitle_color, Qtitle_visible_qm;
    Object Qlegend_position, list_constant_336, Qtrend_chart_legend_position;
    Object list_constant_335, Qlegend_color, Qtrend_chart_legend_color_spec;
    Object Qlegend_visible_qm, Qdata_window_background_color;
    Object Qdata_window_border_color, Qdata_window_border_visible_qm;
    Object Qouter_background_color, Qouter_border_color;
    Object Qouter_border_visible_qm, Qtrend_chart_value_axes_grammar_spec;
    Object list_constant_334, list_constant_333, list_constant_330;
    Object list_constant_326, list_constant_325, list_constant_324;
    Object list_constant_323, list_constant_322, list_constant_321;
    Object list_constant_320, list_constant_319, list_constant_318;
    Object list_constant_317, Qbaseline_color, Qbaseline_visible_qm;
    Object list_constant_316, Qextra_grid_lines, Qextra_value_grid_lines;
    Object list_constant_315, Qgrid_lines_per_label, Qgrid_line_ratio;
    Object Qgrid_line_color, Qgrid_lines_visible_qm, list_constant_314;
    Object Qsignificant_digits_for_labels, Qsignificant_digit_spec;
    Object Qshow_labels_as_percent_qm, list_constant_313;
    Object Q2d_value_axis_tickmark_frequency_spec, list_constant_312;
    Object Q2d_tickmark_label_color, Qlabels_visible_qm, list_constant_311;
    Object Qrange_slack_percentage, Qrange_slack_spec, list_constant_310;
    Object Qrange_bounds, Q2d_value_axis_bounds_spec, list_constant_309;
    Object Qrange_mode, Q2d_range_mode, list_constant_308;
    Object Qvalue_axis_position, Qvalue_axis_visible_qm;
    Object Qtrend_chart_connector_formats_grammar_spec, list_constant_307;
    Object list_constant_306, list_constant_305, list_constant_304;
    Object list_constant_303, list_constant_302, list_constant_301;
    Object list_constant_300, Qconnector_shading_target;
    Object Q2d_shading_target_spec, list_constant_101, Qconnector_line_width;
    Object list_constant_299, Qconnector_interpolation, Q2d_line_style;
    Object Qconnector_line_color, Qconnectors_visible_qm, list_constant_206;
    Object Qtrend_chart_point_formats_grammar_spec, list_constant_297;
    Object list_constant_296, list_constant_295, list_constant_294;
    Object list_constant_293, list_constant_292, list_constant_289;
    Object Qmarker_frequency, Q2d_plot_marker_frequency, list_constant_288;
    Object Qmarker_style, Q2d_plot_marker_shape, Qmarker_color;
    Object list_constant_146, Qmarkers_visible_qm, list_constant_286;
    Object Qchart_element_uid, list_constant_285, Qnames, list_constant_284;
    Object list_constant_192, Qslot_component_pretty_name, Qpoint_frequency;
    Object Qslot_component_alias, Qpoint_style, Qpoint_color;
    Object Qpoint_visible_qm, Qplot_update_interval_spec, list_constant_283;
    Object list_constant_282, list_constant_281, list_constant_280;
    Object Qdefault_overrides_for_connection_definitions, list_constant_135;
    Object Qdefault_overrides_for_message_definitions, list_constant_279;
    Object list_constant_267, Qdefault_overrides_for_object_definitions;
    Object list_constant_278, list_constant_277, list_constant_276;
    Object list_constant_275, list_constant_274, list_constant_266;
    Object list_constant_273, list_constant_263, list_constant_272;
    Object list_constant_210, list_constant_208, list_constant_237;
    Object list_constant_236, list_constant_235, list_constant_234;
    Object list_constant_233, list_constant_232, list_constant_231;
    Object list_constant_230, list_constant_229, list_constant_228;
    Object list_constant_271, list_constant_226, list_constant_260;
    Object list_constant_259, list_constant_258, list_constant_257;
    Object list_constant_256, list_constant_255, list_constant_254;
    Object list_constant_253, list_constant_248;
    Object Qdefault_overrides_for_class_definitions, list_constant_270;
    Object list_constant_269, list_constant_268, list_constant_265;
    Object list_constant_264, list_constant_262, list_constant_261;
    Object list_constant_252, list_constant_251, list_constant_250;
    Object list_constant_249, list_constant_247, list_constant_246;
    Object list_constant_245, list_constant_244, list_constant_243;
    Object list_constant_242, list_constant_241, list_constant_240;
    Object list_constant_239, list_constant_238, list_constant_227;
    Object list_constant_225, list_constant_224, list_constant_223;
    Object list_constant_222, list_constant_221, list_constant_220;
    Object list_constant_219, list_constant_218, list_constant_216;
    Object list_constant_214, list_constant_213, list_constant_212;
    Object list_constant_211, list_constant_209, list_constant_207;
    Object list_constant_205, list_constant_204, Qnew_class;
    Object Qhistory_specification, Qquantitative_data_type, Qdata_type;
    Object Qnumber_qm, Qyes_or_no, Qvalidity_interval, Qwhole_string_qm;
    Object Qstandard_or_class_qualified_symbol_qm, Qinitial_value_integer_qm;
    Object Qinitial_value_long_qm, Qinitial_value_float_qm, Qquantity_qm;
    Object Qtruth_value_qm, Qg2_array_length, Qextant_color_or_metacolor;
    Object Qmodule_name_qm, Qframe_style_name_qm;
    Object Qclass_of_procedure_invocation_qm, Qpriority;
    Object Qexecution_interval_qm_or_default, Qtruth_value_list;
    Object Qwhole_string_list, Qsymbol_list, Qfloat_list, Qinteger_list;
    Object Qquantity_list, Qconstant_designation_list_qm;
    Object Qlist_of_datum_constants, Qrelation_name_qm, Qcategories;
    Object Qfocal_objects, Qsimulation_time_increment_qm;
    Object Qlist_of_item_and_datum_constants_qm, Qfocal_classes;
    Object Qframe_description, Qrelation_yes_or_no_qm, Qoneness_type;
    Object Quser_instantiable_kb_class_qm, Qcomputation_style_or_none;
    Object Qcell_format_or_none, Qchart_style, list_constant_203;
    Object list_constant_202, list_constant_201, list_constant_200;
    Object list_constant_199, list_constant_198, list_constant_197;
    Object list_constant_196, list_constant_195, Qinitial_type;
    Object Qgfi_input_variables_update_mode, list_constant_194;
    Object list_constant_162, Qwhen_to_show_value, list_constant_193;
    Object Qgsi_variable_grouping_specification, Qoptions_for_item_reference;
    Object list_constant_191, list_constant_190, list_constant_189;
    Object list_constant_188, list_constant_187, list_constant_186;
    Object list_constant_185, list_constant_184, list_constant_183;
    Object list_constant_182, list_constant_181, list_constant_180;
    Object list_constant_178, list_constant_179;
    Object Qattributes_which_identify_a_network_item_reference;
    Object list_constant_177, list_constant_176, list_constant_175;
    Object list_constant_174, list_constant_173, list_constant_172;
    Object list_constant_171, list_constant_170, list_constant_169;
    Object list_constant_168, list_constant_167, list_constant_166;
    Object Qgfi_output_file_update_frequency, list_constant_165;
    Object list_constant_164, list_constant_108, Qgfi_time_stamp_format;
    Object Qgfi_file_format, list_constant_163, Qspreadsheet, Qevent_log;
    Object Qgfi_yes_or_no_qm, Qg2_meter_name, list_constant_161;
    Object list_constant_160, list_constant_159, list_constant_158;
    Object list_constant_157, list_constant_156, list_constant_155;
    Object list_constant_154, list_constant_153, list_constant_147;
    Object list_constant_152, list_constant_150, list_constant_149;
    Object list_constant_148, Qcolor_or_metacolor, list_constant_93;
    Object Qback_up_log_file, Qcompile_back_up_log_file_for_slot;
    Object list_constant_132, list_constant_109;
    Object Qwrite_back_up_log_file_from_slot, Qclose_log_file;
    Object Qcompile_close_log_file_for_slot, Qwrite_close_log_file_from_slot;
    Object list_constant_145, list_constant_144, list_constant_143;
    Object list_constant_142, list_constant_141, list_constant_139;
    Object Qlog_file_maximum, Qcompile_log_file_maximum_for_slot;
    Object Qwrite_log_file_maximum_from_slot, Qlog_file_name;
    Object Qcompile_log_file_name_for_slot, Qwrite_log_file_name_from_slot;
    Object Qlog_file_directory, Qcompile_log_file_directory_for_slot;
    Object list_constant_138, Qwrite_log_file_directory_from_slot;
    Object string_constant_172, string_constant_171, string_constant_170;
    Object Qmessage, Qfloating_point_number_precision;
    Object Qwrite_floating_point_number_precision_from_slot;
    Object Qcompile_floating_point_number_precision_for_slot;
    Object Qfloating_point_number_text_style_name;
    Object Qwrite_floating_point_number_text_style_name_from_slot;
    Object Qcompile_floating_point_number_text_style_name_for_slot;
    Object string_constant_169, Qput_default_window_style;
    Object Qinitial_margin_for_workspaces;
    Object Qcompile_initial_margin_for_workspaces_for_slot;
    Object Qwrite_backward_compatible_g2_feature_list_from_slot;
    Object Qbackward_compatible_g2_feature_list;
    Object Qcompile_backward_compatible_g2_feature_list_for_slot;
    Object Qwrite_initial_width_or_height_for_workspaces_from_slot;
    Object Qinitial_width_or_height_for_workspaces;
    Object Qwrite_initial_margin_for_workspaces_from_slot, string_constant_168;
    Object string_constant_167, string_constant_166, string_constant_165;
    Object Qg2_get_connection_vertices, list_constant_137, list_constant_136;
    Object Qbackward_compatible_g2_feature_list_item, list_constant_133;
    Object Qabort_g2, Qpaused, Qrunning, Qwrite_g2_run_state_from_slot;
    Object Qput_connection_caching_enabled_qm;
    Object Qput_backward_compatibility_features, Qclasses_which_define;
    Object Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_miscellaneous_parameters;
    Object Qinstall_system_table;
    Object Qinstall_system_table_for_miscellaneous_parameters;
    Object Qenable_explanation_controls, Qactivate;
    Object Qactivate_for_miscellaneous_parameters;
    Object Qput_automatic_deadlock_detection_frequency;
    Object Qdeadlock_detection_frequency_type;
    Object Qcompile_deadlock_detection_frequency_type_for_slot;
    Object list_constant_131;
    Object Qwrite_deadlock_detection_frequency_type_from_slot;
    Object string_constant_164, Qcharting_library_type_select;
    Object Qwrite_charting_library_type_select_from_slot;
    Object Qcompile_charting_library_type_select_for_slot, string_constant_163;
    Object Ksystem_frame, Qgrammar7, string_constant_162, string_constant_161;
    Object string_constant_160, string_constant_159, string_constant_158;
    Object list_constant_130, Qcurrent_g2_run_state, Qget_slot_init_form;
    Object string_constant_157, string_constant_156, string_constant_155;
    Object string_constant_154, string_constant_153, string_constant_152;
    Object string_constant_151, string_constant_150, string_constant_149;
    Object string_constant_148, string_constant_147, Qsystem_table;
    Object string_constant_146, string_constant_145, string_constant_144;
    Object string_constant_143, string_constant_142, Qcheck_ddd_dddd_format;
    Object Qsimplify_associative_operation, Qwrite_date_qm_from_slot, Qdate_qm;
    Object Qcompile_date_qm_for_slot;
    Object Qtransform_input_phrase_into_universal_date, string_constant_141;
    Object string_constant_140, string_constant_139, string_constant_138;
    Object string_constant_137, string_constant_136, list_constant_129;
    Object Qprecedence_table, list_constant_128, list_constant_127;
    Object list_constant_126, list_constant_125, list_constant_124;
    Object list_constant_123, list_constant_122, list_constant_121;
    Object list_constant_120, list_constant_119, list_constant_118;
    Object list_constant_117, list_constant_116, list_constant_115, Qct;
    Object Qlist_of_graph_expressions;
    Object Qcompile_list_of_graph_expressions_for_slot;
    Object Qlist_of_display_expressions;
    Object Qcompile_list_of_display_expressions_for_slot, Qdisplay_expression;
    Object Qcompile_display_expression_for_slot, list_constant_114;
    Object list_constant_113, list_constant_112, Qunknown_datum;
    Object Qwrite_yes_or_no_from_slot, Qcompile_yes_or_no_for_slot;
    Object Qwrite_symbol_from_slot, Qtext_box_format_name_qm;
    Object Qcompile_display_interval_for_slot;
    Object Qwrite_display_interval_from_slot;
    Object Qwrite_value_for_digital_clock_from_slot, Qvalue_for_digital_clock;
    Object Qwrite_value_for_readout_table_from_slot, Qvalue_for_readout_table;
    Object list_constant_111, Qhorizontal_gridline_interval_qm;
    Object Qcompile_horizontal_gridline_interval_qm_for_slot;
    Object Qvertical_graph_ruling_parameter_qm;
    Object Qcompile_vertical_graph_ruling_parameter_qm_for_slot;
    Object Qhorizontal_graph_ruling_parameter_qm;
    Object Qcompile_horizontal_graph_ruling_parameter_qm_for_slot;
    Object Qwrite_horizontal_gridline_interval_qm_from_slot;
    Object Qwrite_vertical_graph_ruling_parameter_qm_from_slot;
    Object Qwrite_horizontal_graph_ruling_parameter_qm_from_slot;
    Object Qwrite_graph_background_colors_from_slot, Qgraph_background_colors;
    Object Qmeter_ruling_parameter, Qcompile_meter_ruling_parameter_for_slot;
    Object Qcompile_dial_ruling_parameter_for_slot;
    Object Qwrite_meter_ruling_parameter_from_slot;
    Object Qwrite_dial_ruling_parameter_from_slot;
    Object Qwrite_extra_grid_line_specs_from_slot, Qextra_grid_line_specs;
    Object Qcompile_extra_grid_line_specs_for_slot, string_constant_135;
    Object string_constant_134, string_constant_133, string_constant_132;
    Object string_constant_131, string_constant_130, string_constant_129;
    Object string_constant_128, string_constant_127, string_constant_126;
    Object string_constant_125, string_constant_124, string_constant_123;
    Object string_constant_122, string_constant_121;
    Object Qwrite_type_in_box_format_qm_from_slot, Qtype_in_box_format_qm;
    Object list_constant_110, list_constant_107;
    Object Qcompile_type_in_box_format_qm_for_slot, string_constant_120;
    Object Qwrite_format_qm_from_slot, list_constant_106, list_constant_105;
    Object list_constant_104, list_constant_103, list_constant_102;
    Object Qcompile_format_qm_for_slot, string_constant_119, Qjunction_block;
    Object Qjunction_block_class_for_connection, Qstub_length_for_connection;
    Object Qcross_section_pattern_for_connection, Qmenu_option;
    Object Qdefinition_menu_option, Qdefinition;
    Object Qicon_description_for_class_qm, Qconnections_for_class_qm;
    Object Qdirect_superior_classes, Qdirect_superiors_of_defined_class;
    Object Qab_class_name, Qname_of_defined_class;
    Object Qwrite_menu_option_from_slot, Qcompile_menu_option_for_slot;
    Object string_constant_118, string_constant_117, Qmenu;
    Object Qwrite_message_change_from_slot, Qmessage_change;
    Object Qwrite_connection_change_from_slot, Qconnection_change;
    Object Qwrite_object_change_from_slot, Qobject_change;
    Object Qwrite_class_definition_change_from_slot, Qclass_definition_change;
    Object Qstub_designation_or_none, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object list_constant_100, list_constant_99, list_constant_98;
    Object list_constant_97, list_constant_96, list_constant_95, Qleft, Qright;
    Object Qbottom, Qtop, list_constant_94, Qno_item;
    Object Qwrite_stub_designation_or_none_from_slot;
    Object Qcompile_stub_designation_or_none_for_slot;
    Object Qchange_connection_class, Qchange_direction, Qchange_portname;
    Object Qmove_stub, Qdelete_stub, Qadd_stub;
    Object Qcompile_message_change_for_slot;
    Object Qcompile_connection_change_for_slot;
    Object Qcompile_object_change_for_slot;
    Object Qcompile_class_definition_change_for_slot, Qwrite_color_from_slot;
    Object Qcolor, Qwrite_color_for_class_qm_from_slot, Qcolor_for_class_qm;
    Object Qcompile_color_for_class_qm_for_slot, Qunreserved_symbol;
    Object string_constant_116, string_constant_115, string_constant_114;
    Object string_constant_113, string_constant_112, string_constant_111;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, string_constant_103, Qsubclasses;
    Object Qwrite_data_server_map_from_slot, Qdata_server_map;
    Object Qcompile_data_server_map_for_slot, list_constant_91;
    Object Qg2_data_server, list_constant_90, string_constant_102;
    Object string_constant_101;

    x_note_fn_call(203,227);
    SET_PACKAGE("AB");
    string_constant_101 = 
	    STATIC_STRING("1s1m83*My83-Pqy1m83-Pqy83-6y1n83BXy1m1m9k83-Zny1m9k83-Smy83BLy1n83*My1m1m9k83-Zny1m9k83-Smy83BLy1n83BXy1m1m9k830Jy1m9k83nAy83F5y");
    string_constant_102 = 
	    STATIC_STRING("1n83*My1m1m9k830Jy1m9k83nAy83F5y1n83BXy1m1m9k830Jy1m9k835my83CAy1n83*My1m1m9k830Jy1m9k835my83CAy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_101,
	    string_constant_102)));
    AB_package = STATIC_PACKAGE("AB");
    Qdata_server_map = STATIC_SYMBOL("DATA-SERVER-MAP",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_90 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qdata_server_map),
	    Qtype_specification_simple_expansion,list_constant_90);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    Qg2_simulator = STATIC_SYMBOL("G2-SIMULATOR",AB_package);
    Qg2_meter = STATIC_SYMBOL("G2-METER",AB_package);
    Qgfi_data_server = STATIC_SYMBOL("GFI-DATA-SERVER",AB_package);
    Qgsi_data_server = STATIC_SYMBOL("GSI-DATA-SERVER",AB_package);
    Qg2_data_server = STATIC_SYMBOL("G2-DATA-SERVER",AB_package);
    list_constant_91 = STATIC_LIST((SI_Long)7L,Qmember,Qinference_engine,
	    Qg2_simulator,Qg2_meter,Qgfi_data_server,Qgsi_data_server,
	    Qg2_data_server);
    list_constant_92 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_1 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_91,
	    list_constant_92);
    define_type_specification_explicit_complex_type(Qdata_server_map,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qdata_server_map);
    Qcomputation = STATIC_SYMBOL("COMPUTATION",AB_package);
    Qsimulator_data_server = STATIC_SYMBOL("SIMULATOR-DATA-SERVER",AB_package);
    Qg2_meter_data_server = STATIC_SYMBOL("G2-METER-DATA-SERVER",AB_package);
    Qreserved_word_p = STATIC_SYMBOL("RESERVED-WORD-P",AB_package);
    data_server_map_evaluation_setter_1 = 
	    STATIC_FUNCTION(data_server_map_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdata_server_map,
	    data_server_map_evaluation_setter_1);
    data_server_map_evaluation_getter_1 = 
	    STATIC_FUNCTION(data_server_map_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdata_server_map,
	    data_server_map_evaluation_getter_1);
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qcompile_data_server_map_for_slot = 
	    STATIC_SYMBOL("COMPILE-DATA-SERVER-MAP-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_data_server_map_for_slot,
	    STATIC_FUNCTION(compile_data_server_map_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qdata_server_map,
	    SYMBOL_FUNCTION(Qcompile_data_server_map_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qdata_server_map,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant = STATIC_STRING("inference engine");
    string_constant_1 = STATIC_STRING("G2 simulator");
    string_constant_2 = STATIC_STRING("G2 meter");
    string_constant_3 = STATIC_STRING("~(~a~)");
    string_constant_4 = STATIC_STRING("~(if ~a use ~a~)");
    string_constant_5 = STATIC_STRING(" with ");
    string_constant_6 = STATIC_STRING(", ");
    string_constant_7 = STATIC_STRING(", and ");
    string_constant_8 = STATIC_STRING("; ");
    Qwrite_data_server_map_from_slot = 
	    STATIC_SYMBOL("WRITE-DATA-SERVER-MAP-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_data_server_map_from_slot,
	    STATIC_FUNCTION(write_data_server_map_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qdata_server_map,
	    SYMBOL_FUNCTION(Qwrite_data_server_map_from_slot),
	    Qslot_value_writer);
    Qrename_attribute = STATIC_SYMBOL("RENAME-ATTRIBUTE",AB_package);
    Qsubclasses = STATIC_SYMBOL("SUBCLASSES",AB_package);
    SET_SYMBOL_FUNCTION(Qsubclasses,STATIC_FUNCTION(subclasses,NIL,FALSE,1,1));
    Qadd_stub = STATIC_SYMBOL("ADD-STUB",AB_package);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_103 = 
	    STATIC_STRING("13dy1n83-Qcy1p1m9k83-mFy1m9k83-qy83*my1m9k83=3y83*my1n9lnp1n83-Qcy1v1m9k83=cy1m9k9m1m9k83-qy830Ty1m9k83-Ty1m9k838Dy1m9k831Ly1m9k");
    string_constant_104 = 
	    STATIC_STRING("83=3y1m9k9m1m9k83Py1m9k83*ly1m83-M+yo1n83-Qcy13Ly1m9k83=cy1m9k9m1m9k83-qy83-K7y1m9k83-Ty1m9k838Dy1m9k831Ly1m9k83=3y1m9k9m1m9k83P");
    string_constant_105 = 
	    STATIC_STRING("y1m9k83*ly1m9k83vy1m9k83lfy1m9k83-gqy1m9k9n1m9k837ey1m9k83-rXy1m9k83=3y1m9k83=Uy1m9k832+y1m9k9n1m9k8344y1m9k83*ty1m9k83=Yy1m9k83");
    string_constant_106 = 
	    STATIC_STRING("0Cy1m83-M-yo1n83-Qcy1t1m9k9o1m9k830*y1m9k83-aFy1m9k83-ty1m9k9p1m9k83-=ny1m9k831Ty1m9k83=Iy83-Gy1m83-eQyt1n83-Qcy1p1m9k83*py1m9k8");
    string_constant_107 = 
	    STATIC_STRING("3-qy83*my1m9k83=3y83-Gy1n83-fiynp1m83-Qcy1m9k83Zy1m83E6y83-Qcy1n83E6y1o1m9k83Ipy1m9k83S6y1m9k83-*Ly1m9k83-R0y1l83-Ogy1n83E6y1p1m");
    string_constant_108 = 
	    STATIC_STRING("9k837cy1m9k838Dy1m9k831Ly1m9k83Xiy83-vSy1m83-vUyp1m83-vSy1m9k83*ey1m83E6y83-rFy1n83-rFy1m1m9k83pRy83-Duy1m9qm1n83-rFy1m1m9k9r83-");
    string_constant_109 = 
	    STATIC_STRING("rGy1m83-Qpym1n83-rFy1o1m9k83*py83-rGy1m9k83*ty83Sy1o83-ftym83*tyo1n83-rFy1o1m9k83*py83-rGy1m9k83=3y83-ey1o83-ftym83=3yo1n83-rFy1");
    string_constant_110 = 
	    STATIC_STRING("r1m9k83=cy1m9k9m1m9k83-jOy1m9k83-Ty83-rGy1m9k83=3y839jy1n83-M6ypr1n83-rFy1r1m9k83=cy1m9k9m1m9k83gjy1m9k83-Ty83-rGy1m9k83=3y83v7y");
    string_constant_111 = 
	    STATIC_STRING("1n83-Lvypr1n83-rFy1s1m9k83=cy1m9k9m1m9k83=+y1m9k83-Gy1m9k83-Ty83-rGy1m9k83=3y83BOy1n83-Ltyqs1n83-rGy1o1m9k9m1m9k83=+y1m9k83=Gy83");
    string_constant_112 = 
	    STATIC_STRING("9jyo1n83-rGy1q1m9k9m1m9k83=+y1m9k83-2Ty1m9k83=Gy83gsy83Sy1mpq1m83FEy83-rGy1m83FEy1m9k83Zy1m83BNy83-Qcy1m83Diy83-Qcy1n83Diy1p1m9k");
    string_constant_113 = 
	    STATIC_STRING("837cy1m9k838Dy1m9k831Ly1m9k83Xiy83-vRy1m83-vUyp1m83-vRy1m9k8387y1m83-K7y83*my1m83-K7y83-QZy1m83B8y83-Qcy1m83B8y83E6y1m83B8y83Diy");
    string_constant_114 = 
	    STATIC_STRING("1m83=Hy1m9k83S6y1m83=Hy1n1m9k83Ipy1m9k83S6y1m9k83-8ly1m83=Hy83-PUy1m83=Hy83Sy1m83-PUy83-r6y1n83-PUy1n83-BTy1m9k83-Zy83-r6y2l2l83");
    string_constant_115 = 
	    STATIC_STRING("-1yln1m83-r6y83-r5y1o83-r6y1n83-r5y1m9k83vy83-r6y1nmln9s1n83-r5y1m83Sy83*uy2lml1n83-r5y1m83Sy83Yky2lml1m833Zy83Sy1m833Zy1m9k83S6");
    string_constant_116 = STATIC_STRING("y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qrename_attribute);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qvalues);
    push_optimized_constant(Qmerge);
    push_optimized_constant(Qsubclasses);
    push_optimized_constant(Qadd_stub);
    push_optimized_constant(Qdelete);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(list(14,
	    string_constant_103,string_constant_104,string_constant_105,
	    string_constant_106,string_constant_107,string_constant_108,
	    string_constant_109,string_constant_110,string_constant_111,
	    string_constant_112,string_constant_113,string_constant_114,
	    string_constant_115,string_constant_116)));
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    mutate_global_property(Qunreserved_symbol,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qinherited = STATIC_SYMBOL("INHERITED",AB_package);
    Qcolor_for_class_qm = STATIC_SYMBOL("COLOR-FOR-CLASS\?",AB_package);
    Qcompile_color_for_class_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-COLOR-FOR-CLASS\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_color_for_class_qm_for_slot,
	    STATIC_FUNCTION(compile_color_for_class_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qcolor_for_class_qm,
	    SYMBOL_FUNCTION(Qcompile_color_for_class_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qcolor_for_class_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_color_for_class_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-COLOR-FOR-CLASS\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_color_for_class_qm_from_slot,
	    STATIC_FUNCTION(write_color_for_class_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qcolor_for_class_qm,
	    SYMBOL_FUNCTION(Qwrite_color_for_class_qm_from_slot),
	    Qslot_value_writer);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qwrite_color_from_slot = STATIC_SYMBOL("WRITE-COLOR-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_color_from_slot,
	    STATIC_FUNCTION(write_color_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qcolor,SYMBOL_FUNCTION(Qwrite_color_from_slot),
	    Qslot_value_writer);
    Qclass_definition_change = STATIC_SYMBOL("CLASS-DEFINITION-CHANGE",
	    AB_package);
    Qcompile_class_definition_change_for_slot = 
	    STATIC_SYMBOL("COMPILE-CLASS-DEFINITION-CHANGE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_class_definition_change_for_slot,
	    STATIC_FUNCTION(compile_class_definition_change_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qclass_definition_change,
	    SYMBOL_FUNCTION(Qcompile_class_definition_change_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qclass_definition_change,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qobject_change = STATIC_SYMBOL("OBJECT-CHANGE",AB_package);
    Qcompile_object_change_for_slot = 
	    STATIC_SYMBOL("COMPILE-OBJECT-CHANGE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_object_change_for_slot,
	    STATIC_FUNCTION(compile_object_change_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qobject_change,
	    SYMBOL_FUNCTION(Qcompile_object_change_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qobject_change,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qconnection_change = STATIC_SYMBOL("CONNECTION-CHANGE",AB_package);
    Qcompile_connection_change_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONNECTION-CHANGE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_connection_change_for_slot,
	    STATIC_FUNCTION(compile_connection_change_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qconnection_change,
	    SYMBOL_FUNCTION(Qcompile_connection_change_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qconnection_change,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qmessage_change = STATIC_SYMBOL("MESSAGE-CHANGE",AB_package);
    Qcompile_message_change_for_slot = 
	    STATIC_SYMBOL("COMPILE-MESSAGE-CHANGE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_message_change_for_slot,
	    STATIC_FUNCTION(compile_message_change_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qmessage_change,
	    SYMBOL_FUNCTION(Qcompile_message_change_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmessage_change,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qmove_attribute = STATIC_SYMBOL("MOVE-ATTRIBUTE",AB_package);
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    string_constant_9 = 
	    STATIC_STRING("The attribute is not defined for this class");
    string_constant_10 = 
	    STATIC_STRING("An attribute cannot be moved to the same class.");
    list_constant_93 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)57344L);
    string_constant_11 = 
	    STATIC_STRING("The target class cannot be a system-defined class.");
    string_constant_12 = 
	    STATIC_STRING("The target class must be an inferior or superior class.");
    string_constant_13 = 
	    STATIC_STRING("The target class already has this attribute.");
    Qdelete_stub = STATIC_SYMBOL("DELETE-STUB",AB_package);
    Qmove_stub = STATIC_SYMBOL("MOVE-STUB",AB_package);
    Qchange_portname = STATIC_SYMBOL("CHANGE-PORTNAME",AB_package);
    Qchange_direction = STATIC_SYMBOL("CHANGE-DIRECTION",AB_package);
    Qchange_connection_class = STATIC_SYMBOL("CHANGE-CONNECTION-CLASS",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)6L,Qadd_stub,Qdelete_stub,
	    Qmove_stub,Qchange_portname,Qchange_direction,
	    Qchange_connection_class);
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    string_constant_14 = 
	    STATIC_STRING("The class defined by this definition cannot have connections.");
    Qcopy_inherited_icon_description = 
	    STATIC_SYMBOL("COPY-INHERITED-ICON-DESCRIPTION",AB_package);
    string_constant_15 = 
	    STATIC_STRING("The class defined by this definition cannot have an icon.");
    Qupdate_definition_attribute = 
	    STATIC_SYMBOL("UPDATE-DEFINITION-ATTRIBUTE",AB_package);
    Qdefault_message_properties = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES",AB_package);
    string_constant_16 = 
	    STATIC_STRING("The class defined by this definition cannot have default message properties.");
    Qadd_attribute = STATIC_SYMBOL("ADD-ATTRIBUTE",AB_package);
    string_constant_17 = 
	    STATIC_STRING("You cannot make changes to a class before it exists.");
    Qstub_designation_or_none = STATIC_SYMBOL("STUB-DESIGNATION-OR-NONE",
	    AB_package);
    Qcompile_stub_designation_or_none_for_slot = 
	    STATIC_SYMBOL("COMPILE-STUB-DESIGNATION-OR-NONE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_stub_designation_or_none_for_slot,
	    STATIC_FUNCTION(compile_stub_designation_or_none_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qstub_designation_or_none,
	    SYMBOL_FUNCTION(Qcompile_stub_designation_or_none_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qstub_designation_or_none,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_18 = STATIC_STRING("none");
    string_constant_19 = STATIC_STRING("the connection located at ~(~a~) ~d");
    string_constant_20 = STATIC_STRING("the connection at ~(~a~)");
    Qwrite_stub_designation_or_none_from_slot = 
	    STATIC_SYMBOL("WRITE-STUB-DESIGNATION-OR-NONE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_stub_designation_or_none_from_slot,
	    STATIC_FUNCTION(write_stub_designation_or_none_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qstub_designation_or_none,
	    SYMBOL_FUNCTION(Qwrite_stub_designation_or_none_from_slot),
	    Qslot_value_writer);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_5 = STATIC_CONS(Qno_item,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_6 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_94 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_5,
	    Qsymbol,list_constant_6);
    set_property_value_function(get_symbol_properties_function(Qstub_designation_or_none),
	    Qtype_specification_simple_expansion,list_constant_94);
    Qedge = STATIC_SYMBOL("EDGE",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    list_constant_95 = STATIC_LIST((SI_Long)5L,Qmember,Qtop,Qbottom,Qright,
	    Qleft);
    list_constant_96 = STATIC_LIST((SI_Long)2L,Qedge,list_constant_95);
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qposition,Qinteger);
    list_constant_98 = STATIC_LIST((SI_Long)2L,list_constant_96,
	    list_constant_97);
    list_constant_99 = STATIC_LIST((SI_Long)3L,Qand,Qedge,Qposition);
    list_constant_100 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_98,list_constant_99);
    list_constant_4 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_5,
	    Qsymbol,list_constant_100);
    define_type_specification_explicit_complex_type(Qstub_designation_or_none,
	    list_constant_4);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qstub_designation_or_none);
    string_constant_21 = STATIC_STRING("~a is a reserved word");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_22 = STATIC_STRING("~NT ");
    string_constant_23 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    stub_designation_or_none_evaluation_setter_1 = 
	    STATIC_FUNCTION(stub_designation_or_none_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qstub_designation_or_none,
	    stub_designation_or_none_evaluation_setter_1);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    stub_designation_or_none_evaluation_getter_1 = 
	    STATIC_FUNCTION(stub_designation_or_none_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qstub_designation_or_none,
	    stub_designation_or_none_evaluation_getter_1);
    Qwrite_class_definition_change_from_slot = 
	    STATIC_SYMBOL("WRITE-CLASS-DEFINITION-CHANGE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_class_definition_change_from_slot,
	    STATIC_FUNCTION(write_class_definition_change_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qclass_definition_change,
	    SYMBOL_FUNCTION(Qwrite_class_definition_change_from_slot),
	    Qslot_value_writer);
    Qwrite_object_change_from_slot = 
	    STATIC_SYMBOL("WRITE-OBJECT-CHANGE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_object_change_from_slot,
	    STATIC_FUNCTION(write_object_change_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qobject_change,
	    SYMBOL_FUNCTION(Qwrite_object_change_from_slot),
	    Qslot_value_writer);
    Qwrite_connection_change_from_slot = 
	    STATIC_SYMBOL("WRITE-CONNECTION-CHANGE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_connection_change_from_slot,
	    STATIC_FUNCTION(write_connection_change_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qconnection_change,
	    SYMBOL_FUNCTION(Qwrite_connection_change_from_slot),
	    Qslot_value_writer);
    Qwrite_message_change_from_slot = 
	    STATIC_SYMBOL("WRITE-MESSAGE-CHANGE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_message_change_from_slot,
	    STATIC_FUNCTION(write_message_change_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qmessage_change,
	    SYMBOL_FUNCTION(Qwrite_message_change_from_slot),
	    Qslot_value_writer);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    string_constant_117 = 
	    STATIC_STRING("1n1n83Dey1o1m9k83=Yy1m9k83-U*y1m9k9l1m9k83-MPy1lm1n83Dey1p1m9k9m1m9k83=Yy1m9k83-U*y1m9k9l1m9k83-MPy1l83-h=y1n83Dey1o1m9k8329y1m9");
    string_constant_118 = STATIC_STRING("k83=Yy1m9k9l1m9k83-MPy1l83-gTy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmenu);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_117,
	    string_constant_118)));
    Qfinal = STATIC_SYMBOL("FINAL",AB_package);
    Qmenu_option = STATIC_SYMBOL("MENU-OPTION",AB_package);
    Qcompile_menu_option_for_slot = 
	    STATIC_SYMBOL("COMPILE-MENU-OPTION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_menu_option_for_slot,
	    STATIC_FUNCTION(compile_menu_option_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qmenu_option,
	    SYMBOL_FUNCTION(Qcompile_menu_option_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmenu_option,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_24 = STATIC_STRING("a final menu choice");
    string_constant_25 = STATIC_STRING("never a menu choice");
    string_constant_26 = STATIC_STRING("not a final menu choice");
    Qwrite_menu_option_from_slot = 
	    STATIC_SYMBOL("WRITE-MENU-OPTION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_menu_option_from_slot,
	    STATIC_FUNCTION(write_menu_option_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qmenu_option,
	    SYMBOL_FUNCTION(Qwrite_menu_option_from_slot),Qslot_value_writer);
    Qname_of_defined_class = STATIC_SYMBOL("NAME-OF-DEFINED-CLASS",AB_package);
    Qab_class_name = STATIC_SYMBOL("CLASS-NAME",AB_package);
    Qdefinition = STATIC_SYMBOL("DEFINITION",AB_package);
    alias_slot_name(3,Qname_of_defined_class,Qab_class_name,Qdefinition);
    Qdirect_superiors_of_defined_class = 
	    STATIC_SYMBOL("DIRECT-SUPERIORS-OF-DEFINED-CLASS",AB_package);
    Qdirect_superior_classes = STATIC_SYMBOL("DIRECT-SUPERIOR-CLASSES",
	    AB_package);
    alias_slot_name(3,Qdirect_superiors_of_defined_class,
	    Qdirect_superior_classes,Qdefinition);
    Qconnections_for_class_qm = STATIC_SYMBOL("CONNECTIONS-FOR-CLASS\?",
	    AB_package);
    Qstubs = STATIC_SYMBOL("STUBS",AB_package);
    alias_slot_name(3,Qconnections_for_class_qm,Qstubs,Qdefinition);
    Qicon_description_for_class_qm = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-FOR-CLASS\?",AB_package);
    alias_slot_name(3,Qicon_description_for_class_qm,Qicon_description,
	    Qdefinition);
    Qdefinition_menu_option = STATIC_SYMBOL("DEFINITION-MENU-OPTION",
	    AB_package);
    alias_slot_name(3,Qdefinition_menu_option,Qmenu_option,Qnil);
    Qcross_section_pattern_for_connection = 
	    STATIC_SYMBOL("CROSS-SECTION-PATTERN-FOR-CONNECTION",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    alias_slot_name(3,Qcross_section_pattern_for_connection,
	    Qcross_section_pattern,Qnil);
    Qstub_length_for_connection = 
	    STATIC_SYMBOL("STUB-LENGTH-FOR-CONNECTION",AB_package);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    alias_slot_name(3,Qstub_length_for_connection,Qstub_length,Qnil);
    Qjunction_block_class_for_connection = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-FOR-CONNECTION",AB_package);
    Qjunction_block = STATIC_SYMBOL("JUNCTION-BLOCK",AB_package);
    alias_slot_name(3,Qjunction_block_class_for_connection,Qjunction_block,
	    Qnil);
    string_constant_119 = 
	    STATIC_STRING("1p1m83*Wy83J9y1n83*Wy1m1m9k831Ay1m9k83A*y832ny1n83*Wy1m1m9k83-dy1m9k83Gy8341y1m83*Wy1m9k83-oy1m83*Wy1m9k83Py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_119));
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    Qdate_format_description = STATIC_SYMBOL("DATE-FORMAT-DESCRIPTION",
	    AB_package);
    Qformat_qm = STATIC_SYMBOL("FORMAT\?",AB_package);
    Qcompile_format_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-FORMAT\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_format_qm_for_slot,
	    STATIC_FUNCTION(compile_format_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qformat_qm,
	    SYMBOL_FUNCTION(Qcompile_format_qm_for_slot),Qslot_value_compiler);
    mutate_global_property(Qformat_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qfloat_format = STATIC_SYMBOL("FLOAT-FORMAT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qfloat_format),
	    Qtype_specification_simple_expansion,list_constant_6);
    Qwhole_number_precision = STATIC_SYMBOL("WHOLE-NUMBER-PRECISION",
	    AB_package);
    list_constant_101 = STATIC_CONS(Qinteger,Qnil);
    list_constant_102 = STATIC_CONS(Qwhole_number_precision,list_constant_101);
    Qfraction_precision = STATIC_SYMBOL("FRACTION-PRECISION",AB_package);
    list_constant_103 = STATIC_CONS(Qfraction_precision,list_constant_101);
    list_constant_104 = STATIC_LIST((SI_Long)2L,list_constant_102,
	    list_constant_103);
    list_constant_105 = STATIC_LIST((SI_Long)3L,Qand,
	    Qwhole_number_precision,Qfraction_precision);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_104,list_constant_105);
    define_type_specification_explicit_complex_type(Qfloat_format,
	    list_constant_8);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qfloat_format);
    string_constant_27 = 
	    STATIC_STRING("The whole-number-precision ~D is not between 0 and ~D");
    string_constant_28 = 
	    STATIC_STRING("The fraction-precision ~D is not between 0 and ~D");
    string_constant_29 = STATIC_STRING("d");
    string_constant_30 = STATIC_STRING(".");
    float_format_evaluation_setter_1 = 
	    STATIC_FUNCTION(float_format_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfloat_format,
	    float_format_evaluation_setter_1);
    float_format_evaluation_getter_1 = 
	    STATIC_FUNCTION(float_format_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfloat_format,
	    float_format_evaluation_getter_1);
    list_constant_106 = STATIC_LIST((SI_Long)4L,Qab_or,Qnil,Qsymbol,Qnil);
    set_property_value_function(get_symbol_properties_function(Qformat_qm),
	    Qtype_specification_simple_expansion,list_constant_106);
    list_constant_107 = STATIC_LIST((SI_Long)5L,Qmember,Qdefault,Qinterval,
	    Qtime_stamp,Qfree_text);
    list_constant_10 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_107,
	    Qsymbol,list_constant_7);
    define_type_specification_explicit_complex_type(Qformat_qm,
	    list_constant_10);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qnamed,Qformat_qm);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    format_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(format_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qformat_qm,
	    format_qm_evaluation_setter_1);
    format_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(format_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qformat_qm,
	    format_qm_evaluation_getter_1);
    string_constant_31 = STATIC_STRING("default");
    string_constant_32 = STATIC_STRING("time stamp");
    string_constant_33 = STATIC_STRING("free text");
    string_constant_34 = STATIC_STRING("interval");
    Qwrite_format_qm_from_slot = STATIC_SYMBOL("WRITE-FORMAT\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_format_qm_from_slot,
	    STATIC_FUNCTION(write_format_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qformat_qm,
	    SYMBOL_FUNCTION(Qwrite_format_qm_from_slot),Qslot_value_writer);
    string_constant_120 = STATIC_STRING("1l1m83AJy83*Wy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_120));
    Qtype_in_box_format_qm = STATIC_SYMBOL("TYPE-IN-BOX-FORMAT\?",AB_package);
    Qcompile_type_in_box_format_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-TYPE-IN-BOX-FORMAT\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_type_in_box_format_qm_for_slot,
	    STATIC_FUNCTION(compile_type_in_box_format_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qtype_in_box_format_qm,
	    SYMBOL_FUNCTION(Qcompile_type_in_box_format_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtype_in_box_format_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_108 = STATIC_CONS(Qnil,Qnil);
    list_constant_109 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnil,
	    list_constant_108);
    set_property_value_function(get_symbol_properties_function(Qtype_in_box_format_qm),
	    Qtype_specification_simple_expansion,list_constant_109);
    list_constant_110 = STATIC_CONS(list_constant_7,Qnil);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_107,list_constant_110);
    define_type_specification_explicit_complex_type(Qtype_in_box_format_qm,
	    list_constant_12);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qnamed,Qtype_in_box_format_qm);
    type_in_box_format_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(type_in_box_format_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qtype_in_box_format_qm,
	    type_in_box_format_qm_evaluation_setter_1);
    type_in_box_format_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(type_in_box_format_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtype_in_box_format_qm,
	    type_in_box_format_qm_evaluation_getter_1);
    Qwrite_type_in_box_format_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-TYPE-IN-BOX-FORMAT\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_type_in_box_format_qm_from_slot,
	    STATIC_FUNCTION(write_type_in_box_format_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtype_in_box_format_qm,
	    SYMBOL_FUNCTION(Qwrite_type_in_box_format_qm_from_slot),
	    Qslot_value_writer);
    Qnil_function = STATIC_SYMBOL("NIL-FUNCTION",AB_package);
    string_constant_121 = 
	    STATIC_STRING("13oy1m831*y83=xy1m831*y831Py1m83-cwy831*y1o83-cwy1n831*y1m9k83-Zy83-cwy1nmln9l1m83DSy83-X3y1o83DSy1n83-X3y1m9k83-Zy83DSy1nmln9l1");
    string_constant_122 = 
	    STATIC_STRING("m83-X3y830By1n83-X3y1m830By83-ixy1n83vylm1n83-X3y1m830By83-j0y1o83vyl0m1n83-X3y1m830By83-j2y1p83vyl00m1n83-X3y1n830By83-ixy83-j0");
    string_constant_123 = 
	    STATIC_STRING("y1o83vylmn1n83-X3y1n830By83-ixy83-j2y1p83vylm0n1n83-X3y1n830By83-j0y83-j2y1p83vyl0mn1n83-X3y1o830By83-ixy83-j0y83-j2y1p83vylmno1");
    string_constant_124 = 
	    STATIC_STRING("n83-ixy1m1m9k83*Xy83*xym1n83-j2y1q1m9k83=Fy1m9k83-9vy1m9k832+y83-Hy1m9k83=3y83-Hy2loq1m83-j0y83-dry1n83-j0y1m1m9k83Fmy1m9k83-oWy");
    string_constant_125 = 
	    STATIC_STRING("m1m83-j0y83-j*y1n83-j0y1n83-dry1m9k83-ty83-j*y2lln1n83-j*y1o1m9k83Fmy1m9k83kUy1m9k83*4y83-eyo1n83-dry1o1m9k83Fmy83-j=y1m9k833Wy1");
    string_constant_126 = 
	    STATIC_STRING("m9k83-doym1m83-j=y1m9k83amy1m83-j=y1m9k83ly1m83-j=y1m9k83lZy1n83Ky1m9k83-xpy8k1o83Ky1m9k83=Ty09m1m83-sSy83-6y1m83=Qy831Ny1m8388y");
    string_constant_127 = 
	    STATIC_STRING("83-Hy1m839Ry83-Hy1m8391y1m9k83Zy1m83ARy1m9k83Zy1m83ARy83-Hy1n83ARy1q83-Hy1m9k83=Fy1m9k830*y1m9k83-aYy1m9k9n1m9k83Euy2llq1m8391y8");
    string_constant_128 = 
	    STATIC_STRING("3-oy1n83ARy1n83-Hy1m9k83=3y83-Hy1n83-Zyln1n83ARy1s83-Hy1m9k83=3y83-Hy1m9k83=Fy1m9k830*y1m9k83-aYy1m9k9n1m9k83Euy1o83-Zylns1n8391");
    string_constant_129 = 
	    STATIC_STRING("y1p83-oy1m9k83=3y83-oy1m9k835+y1m9k836Gy1n83-Zyln1n83ARy1o83-Hy1m9k83AUy1m9k83-sty1m9k9o2l83-xHyl1n83ARy1q83-Hy1m9k83=3y83-Hy1m9");
    string_constant_130 = 
	    STATIC_STRING("k83AUy1m9k83-sty1m9k9o1o83-xHy83-Zyln1n8391y1o83-oy1m9k83AUy1m9k83-sty1m9k9o2l83-xHyl1n8391y1s83-oy1m9k83=3y83-oy1m9k835+y1m9k83");
    string_constant_131 = 
	    STATIC_STRING("6Gy1m9k83AUy1m9k83-sty1m9k9o1o83-xHy83-Zyln1n83ARy1t83-Hy1m9k83=Fy1m9k830*y1m9k83-aYy1m9k9n1m9k83Euy1m9k83AUy1m9k83-sty1m9k9o2m8");
    string_constant_132 = 
	    STATIC_STRING("3-xHylq1n83ARy1v83-Hy1m9k83=3y83-Hy1m9k83=Fy1m9k830*y1m9k83-aYy1m9k9n1m9k83Euy1m9k83AUy1m9k83-sty1m9k9o1p83-xHy83-Zylns1n8392y1m");
    string_constant_133 = 
	    STATIC_STRING("1m9k83-Ney1m9k83q2y83Zy1m8392y83-Hy1n8392y1o83-Hy1m9k83HBy1m9k83=Gy83-Hy2llo1m838Jy83-Tby1o838Jy1n83-Tby1m9k83vy838Jy1nmln9l1n83");
    string_constant_134 = 
	    STATIC_STRING("-Tby1m1m9k83=Gy83-Hym1n83-Tby1o1m9k83=Gy83-Hy1m9k83*Xy83*xy2lmo1m83-Tby1m9k83Zy1n838xy1t1m9k833My1m9k83-KSy1m9k83-Py83*xy1m9k83v");
    string_constant_135 = 
	    STATIC_STRING("y1m9k83Qxy1m9k83-KSy1m9k83-Py83*xy2lot");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qnil_function);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qlabels);
    add_grammar_rules_function(regenerate_optimized_constant(list(15,
	    string_constant_121,string_constant_122,string_constant_123,
	    string_constant_124,string_constant_125,string_constant_126,
	    string_constant_127,string_constant_128,string_constant_129,
	    string_constant_130,string_constant_131,string_constant_132,
	    string_constant_133,string_constant_134,string_constant_135)));
    Qextra_grid_line_specs = STATIC_SYMBOL("EXTRA-GRID-LINE-SPECS",AB_package);
    Qcompile_extra_grid_line_specs_for_slot = 
	    STATIC_SYMBOL("COMPILE-EXTRA-GRID-LINE-SPECS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_extra_grid_line_specs_for_slot,
	    STATIC_FUNCTION(compile_extra_grid_line_specs_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qextra_grid_line_specs,
	    SYMBOL_FUNCTION(Qcompile_extra_grid_line_specs_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qextra_grid_line_specs,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qwrite_extra_grid_line_specs_from_slot = 
	    STATIC_SYMBOL("WRITE-EXTRA-GRID-LINE-SPECS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_extra_grid_line_specs_from_slot,
	    STATIC_FUNCTION(write_extra_grid_line_specs_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qextra_grid_line_specs,
	    SYMBOL_FUNCTION(Qwrite_extra_grid_line_specs_from_slot),
	    Qslot_value_writer);
    string_constant_35 = STATIC_STRING("at ");
    string_constant_36 = STATIC_STRING(" in ");
    Qdial_ruling_parameter = STATIC_SYMBOL("DIAL-RULING-PARAMETER",AB_package);
    Qwrite_dial_ruling_parameter_from_slot = 
	    STATIC_SYMBOL("WRITE-DIAL-RULING-PARAMETER-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dial_ruling_parameter_from_slot,
	    STATIC_FUNCTION(write_dial_ruling_parameter_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qdial_ruling_parameter,
	    SYMBOL_FUNCTION(Qwrite_dial_ruling_parameter_from_slot),
	    Qslot_value_writer);
    Qmeter_ruling_parameter = STATIC_SYMBOL("METER-RULING-PARAMETER",
	    AB_package);
    Qwrite_meter_ruling_parameter_from_slot = 
	    STATIC_SYMBOL("WRITE-METER-RULING-PARAMETER-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_meter_ruling_parameter_from_slot,
	    STATIC_FUNCTION(write_meter_ruling_parameter_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qmeter_ruling_parameter,
	    SYMBOL_FUNCTION(Qwrite_meter_ruling_parameter_from_slot),
	    Qslot_value_writer);
    Qincrement_per_dial_ruling = STATIC_SYMBOL("INCREMENT-PER-DIAL-RULING",
	    AB_package);
    string_constant_37 = 
	    STATIC_STRING("Increment per dial ruling must be positive.");
    Qcompile_dial_ruling_parameter_for_slot = 
	    STATIC_SYMBOL("COMPILE-DIAL-RULING-PARAMETER-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_dial_ruling_parameter_for_slot,
	    STATIC_FUNCTION(compile_dial_ruling_parameter_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qdial_ruling_parameter,
	    SYMBOL_FUNCTION(Qcompile_dial_ruling_parameter_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdial_ruling_parameter,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qdial_ruling_parameter),
	    Qtype_specification_simple_expansion,Qnumber);
    define_type_specification_explicit_complex_type(Qdial_ruling_parameter,
	    Qnumber);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qnamed,Qdial_ruling_parameter);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    dial_ruling_parameter_evaluation_setter_1 = 
	    STATIC_FUNCTION(dial_ruling_parameter_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qdial_ruling_parameter,
	    dial_ruling_parameter_evaluation_setter_1);
    dial_ruling_parameter_evaluation_getter_1 = 
	    STATIC_FUNCTION(dial_ruling_parameter_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdial_ruling_parameter,
	    dial_ruling_parameter_evaluation_getter_1);
    Qincrement_per_meter_ruling = 
	    STATIC_SYMBOL("INCREMENT-PER-METER-RULING",AB_package);
    string_constant_38 = 
	    STATIC_STRING("Increment per meter ruling must be positive.");
    Qcompile_meter_ruling_parameter_for_slot = 
	    STATIC_SYMBOL("COMPILE-METER-RULING-PARAMETER-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_meter_ruling_parameter_for_slot,
	    STATIC_FUNCTION(compile_meter_ruling_parameter_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qmeter_ruling_parameter,
	    SYMBOL_FUNCTION(Qcompile_meter_ruling_parameter_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmeter_ruling_parameter,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qmeter_ruling_parameter),
	    Qtype_specification_simple_expansion,Qnumber);
    define_type_specification_explicit_complex_type(Qmeter_ruling_parameter,
	    Qnumber);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qnamed,Qmeter_ruling_parameter);
    meter_ruling_parameter_evaluation_setter_1 = 
	    STATIC_FUNCTION(meter_ruling_parameter_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qmeter_ruling_parameter,
	    meter_ruling_parameter_evaluation_setter_1);
    meter_ruling_parameter_evaluation_getter_1 = 
	    STATIC_FUNCTION(meter_ruling_parameter_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmeter_ruling_parameter,
	    meter_ruling_parameter_evaluation_getter_1);
    string_constant_39 = STATIC_STRING("graph background: ");
    string_constant_40 = STATIC_STRING(", grid background: ");
    Qgraph_background_colors = STATIC_SYMBOL("GRAPH-BACKGROUND-COLORS",
	    AB_package);
    Qwrite_graph_background_colors_from_slot = 
	    STATIC_SYMBOL("WRITE-GRAPH-BACKGROUND-COLORS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_graph_background_colors_from_slot,
	    STATIC_FUNCTION(write_graph_background_colors_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qgraph_background_colors,
	    SYMBOL_FUNCTION(Qwrite_graph_background_colors_from_slot),
	    Qslot_value_writer);
    Qwithout_tickmark_labels = STATIC_SYMBOL("WITHOUT-TICKMARK-LABELS",
	    AB_package);
    string_constant_41 = STATIC_STRING(" to ");
    string_constant_42 = STATIC_STRING(" after start");
    string_constant_43 = STATIC_STRING(" without tickmark labels");
    Qhorizontal_graph_ruling_parameter_qm = 
	    STATIC_SYMBOL("HORIZONTAL-GRAPH-RULING-PARAMETER\?",AB_package);
    Qwrite_horizontal_graph_ruling_parameter_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-HORIZONTAL-GRAPH-RULING-PARAMETER\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_horizontal_graph_ruling_parameter_qm_from_slot,
	    STATIC_FUNCTION(write_horizontal_graph_ruling_parameter_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhorizontal_graph_ruling_parameter_qm,
	    SYMBOL_FUNCTION(Qwrite_horizontal_graph_ruling_parameter_qm_from_slot),
	    Qslot_value_writer);
    string_constant_44 = STATIC_STRING(" with all intervals the same");
    Qvertical_graph_ruling_parameter_qm = 
	    STATIC_SYMBOL("VERTICAL-GRAPH-RULING-PARAMETER\?",AB_package);
    Qwrite_vertical_graph_ruling_parameter_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-VERTICAL-GRAPH-RULING-PARAMETER\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_vertical_graph_ruling_parameter_qm_from_slot,
	    STATIC_FUNCTION(write_vertical_graph_ruling_parameter_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qvertical_graph_ruling_parameter_qm,
	    SYMBOL_FUNCTION(Qwrite_vertical_graph_ruling_parameter_qm_from_slot),
	    Qslot_value_writer);
    string_constant_45 = STATIC_STRING("compute automatically");
    string_constant_46 = STATIC_STRING(" beginning at ");
    Qhorizontal_gridline_interval_qm = 
	    STATIC_SYMBOL("HORIZONTAL-GRIDLINE-INTERVAL\?",AB_package);
    Qwrite_horizontal_gridline_interval_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-HORIZONTAL-GRIDLINE-INTERVAL\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_horizontal_gridline_interval_qm_from_slot,
	    STATIC_FUNCTION(write_horizontal_gridline_interval_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhorizontal_gridline_interval_qm,
	    SYMBOL_FUNCTION(Qwrite_horizontal_gridline_interval_qm_from_slot),
	    Qslot_value_writer);
    string_constant_47 = 
	    STATIC_STRING("Horizontal axis range can not be greater than 24 weeks.");
    string_constant_48 = 
	    STATIC_STRING("Horizontal axis range must be greater than 0.");
    Qcompile_horizontal_graph_ruling_parameter_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-HORIZONTAL-GRAPH-RULING-PARAMETER\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_horizontal_graph_ruling_parameter_qm_for_slot,
	    STATIC_FUNCTION(compile_horizontal_graph_ruling_parameter_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qhorizontal_graph_ruling_parameter_qm,
	    SYMBOL_FUNCTION(Qcompile_horizontal_graph_ruling_parameter_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qhorizontal_graph_ruling_parameter_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_49 = 
	    STATIC_STRING("Vertical axis range can not be less than 0.");
    Qcompile_vertical_graph_ruling_parameter_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-VERTICAL-GRAPH-RULING-PARAMETER\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_vertical_graph_ruling_parameter_qm_for_slot,
	    STATIC_FUNCTION(compile_vertical_graph_ruling_parameter_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qvertical_graph_ruling_parameter_qm,
	    SYMBOL_FUNCTION(Qcompile_vertical_graph_ruling_parameter_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qvertical_graph_ruling_parameter_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_1 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)57344L);
    Qcompile_horizontal_gridline_interval_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-HORIZONTAL-GRIDLINE-INTERVAL\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_horizontal_gridline_interval_qm_for_slot,
	    STATIC_FUNCTION(compile_horizontal_gridline_interval_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qhorizontal_gridline_interval_qm,
	    SYMBOL_FUNCTION(Qcompile_horizontal_gridline_interval_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qhorizontal_gridline_interval_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    list_constant_111 = STATIC_CONS(Qfree_text,Qnil);
    list_constant_15 = STATIC_LIST_STAR((SI_Long)3L,Qtime_stamp,Qseconds,
	    list_constant_111);
    string_constant_50 = STATIC_STRING("[deleted attribute]");
    Qformat_for_readout_table = STATIC_SYMBOL("FORMAT-FOR-READOUT-TABLE",
	    AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qvalue_for_readout_table = STATIC_SYMBOL("VALUE-FOR-READOUT-TABLE",
	    AB_package);
    Qwrite_value_for_readout_table_from_slot = 
	    STATIC_SYMBOL("WRITE-VALUE-FOR-READOUT-TABLE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_value_for_readout_table_from_slot,
	    STATIC_FUNCTION(write_value_for_readout_table_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qvalue_for_readout_table,
	    SYMBOL_FUNCTION(Qwrite_value_for_readout_table_from_slot),
	    Qslot_value_writer);
    array_constant_4 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qvalue_for_digital_clock = STATIC_SYMBOL("VALUE-FOR-DIGITAL-CLOCK",
	    AB_package);
    Qwrite_value_for_digital_clock_from_slot = 
	    STATIC_SYMBOL("WRITE-VALUE-FOR-DIGITAL-CLOCK-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_value_for_digital_clock_from_slot,
	    STATIC_FUNCTION(write_value_for_digital_clock_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qvalue_for_digital_clock,
	    SYMBOL_FUNCTION(Qwrite_value_for_digital_clock_from_slot),
	    Qslot_value_writer);
    Qdisplay_interval = STATIC_SYMBOL("DISPLAY-INTERVAL",AB_package);
    Qwrite_display_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-DISPLAY-INTERVAL-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_display_interval_from_slot,
	    STATIC_FUNCTION(write_display_interval_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qdisplay_interval,
	    SYMBOL_FUNCTION(Qwrite_display_interval_from_slot),
	    Qslot_value_writer);
    Qcompile_display_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-DISPLAY-INTERVAL-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_display_interval_for_slot,
	    STATIC_FUNCTION(compile_display_interval_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qdisplay_interval,
	    SYMBOL_FUNCTION(Qcompile_display_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdisplay_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qdisplay_interval),
	    Qtype_specification_simple_expansion,Qnumber);
    define_type_specification_explicit_complex_type(Qdisplay_interval,Qnumber);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qnamed,Qdisplay_interval);
    Qpositive_quantity_interval_qm = 
	    STATIC_SYMBOL("POSITIVE-QUANTITY-INTERVAL\?",AB_package);
    display_interval_evaluation_setter_1 = 
	    STATIC_FUNCTION(display_interval_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdisplay_interval,
	    display_interval_evaluation_setter_1);
    display_interval_evaluation_getter_1 = 
	    STATIC_FUNCTION(display_interval_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdisplay_interval,
	    display_interval_evaluation_getter_1);
    Qtext_box_format_name_qm = STATIC_SYMBOL("TEXT-BOX-FORMAT-NAME\?",
	    AB_package);
    mutate_global_property(Qtext_box_format_name_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qyes_or_no = STATIC_SYMBOL("YES-OR-NO",AB_package);
    Qcompile_yes_or_no_for_slot = 
	    STATIC_SYMBOL("COMPILE-YES-OR-NO-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_yes_or_no_for_slot,
	    STATIC_FUNCTION(compile_yes_or_no_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qyes_or_no,
	    SYMBOL_FUNCTION(Qcompile_yes_or_no_for_slot),Qslot_value_compiler);
    mutate_global_property(Qyes_or_no,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_51 = STATIC_STRING("yes");
    string_constant_52 = STATIC_STRING("no");
    Qwrite_yes_or_no_from_slot = STATIC_SYMBOL("WRITE-YES-OR-NO-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yes_or_no_from_slot,
	    STATIC_FUNCTION(write_yes_or_no_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qyes_or_no,
	    SYMBOL_FUNCTION(Qwrite_yes_or_no_from_slot),Qslot_value_writer);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qpart_stack = STATIC_SYMBOL("PART-STACK",AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_112 = STATIC_CONS(Qunknown_datum,Qnil);
    list_constant_113 = STATIC_CONS(Qobsolete_datum,Qnil);
    list_constant_114 = STATIC_LIST((SI_Long)2L,list_constant_112,
	    list_constant_113);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qdatum,
	    list_constant_114);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_114);
    Qempty_expression_cell = STATIC_SYMBOL("EMPTY-EXPRESSION-CELL",AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qdisplay_expression = STATIC_SYMBOL("DISPLAY-EXPRESSION",AB_package);
    Qcompile_display_expression_for_slot = 
	    STATIC_SYMBOL("COMPILE-DISPLAY-EXPRESSION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_display_expression_for_slot,
	    STATIC_FUNCTION(compile_display_expression_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qdisplay_expression,
	    SYMBOL_FUNCTION(Qcompile_display_expression_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdisplay_expression,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qlist_of_display_expressions = 
	    STATIC_SYMBOL("LIST-OF-DISPLAY-EXPRESSIONS",AB_package);
    Qcompile_list_of_display_expressions_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-DISPLAY-EXPRESSIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_display_expressions_for_slot,
	    STATIC_FUNCTION(compile_list_of_display_expressions_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qlist_of_display_expressions,
	    SYMBOL_FUNCTION(Qcompile_list_of_display_expressions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_display_expressions,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgraph_expression = STATIC_SYMBOL("GRAPH-EXPRESSION",AB_package);
    string_constant_53 = 
	    STATIC_STRING("Local names are not allowed in display expressions for graphs.");
    Qlist_of_graph_expressions = STATIC_SYMBOL("LIST-OF-GRAPH-EXPRESSIONS",
	    AB_package);
    Qcompile_list_of_graph_expressions_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-GRAPH-EXPRESSIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_graph_expressions_for_slot,
	    STATIC_FUNCTION(compile_list_of_graph_expressions_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qlist_of_graph_expressions,
	    SYMBOL_FUNCTION(Qcompile_list_of_graph_expressions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_graph_expressions,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qprecedence_table = STATIC_SYMBOL("PRECEDENCE-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprecedence_table,Precedence_table);
    list_constant_115 = STATIC_CONS(Qab_or,FIX((SI_Long)20L));
    list_constant_116 = STATIC_CONS(Qand,FIX((SI_Long)20L));
    list_constant_117 = STATIC_CONS(Qnot,FIX((SI_Long)30L));
    list_constant_118 = STATIC_CONS(Qnum_eq,FIX((SI_Long)50L));
    list_constant_119 = STATIC_CONS(Qnum_ne,FIX((SI_Long)50L));
    list_constant_120 = STATIC_CONS(Qnum_lt,FIX((SI_Long)50L));
    list_constant_121 = STATIC_CONS(Qnum_le,FIX((SI_Long)50L));
    list_constant_122 = STATIC_CONS(Qnum_gt,FIX((SI_Long)50L));
    list_constant_123 = STATIC_CONS(Qnum_ge,FIX((SI_Long)50L));
    list_constant_124 = STATIC_CONS(Qplus,FIX((SI_Long)100L));
    list_constant_125 = STATIC_CONS(Qminus,FIX((SI_Long)100L));
    list_constant_126 = STATIC_CONS(Qstar,FIX((SI_Long)110L));
    list_constant_127 = STATIC_CONS(Qslash,FIX((SI_Long)110L));
    Qct = STATIC_SYMBOL("^",AB_package);
    list_constant_128 = STATIC_CONS(Qct,FIX((SI_Long)120L));
    list_constant_129 = STATIC_LIST((SI_Long)14L,list_constant_115,
	    list_constant_116,list_constant_117,list_constant_118,
	    list_constant_119,list_constant_120,list_constant_121,
	    list_constant_122,list_constant_123,list_constant_124,
	    list_constant_125,list_constant_126,list_constant_127,
	    list_constant_128);
    SET_SYMBOL_VALUE(Qprecedence_table,list_constant_129);
    string_constant_54 = STATIC_STRING("~s");
    string_constant_55 = STATIC_STRING("!!!");
    Qevaluator_form_writer = STATIC_SYMBOL("EVALUATOR-FORM-WRITER",AB_package);
    Qop = STATIC_SYMBOL("(",AB_package);
    Qcp = STATIC_SYMBOL(")",AB_package);
    string_constant_56 = STATIC_STRING(" ");
    string_constant_136 = STATIC_STRING("1m1m83-Q-y1m9k83Zy1m83-Q-y8355y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_136));
    Qtransform_input_phrase_into_universal_date = 
	    STATIC_SYMBOL("TRANSFORM-INPUT-PHRASE-INTO-UNIVERSAL-DATE",
	    AB_package);
    string_constant_137 = STATIC_STRING("1l1o8355y1n833+y83E+y836Vy1nlmn9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_input_phrase_into_universal_date);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_137));
    string_constant_138 = STATIC_STRING("1l1m833+y83-ey");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_138));
    string_constant_139 = 
	    STATIC_STRING("1w1m83E+y1m9k83-bGy1m83E+y1m9k83-Toy1m83E+y1m9k83-dhy1m83E+y1m9k83-Jly1m83E+y1m9k83-6Ty1m83E+y1m9k83-biy1m83E+y1m9k83-bfy1m83E+y");
    string_constant_140 = 
	    STATIC_STRING("1m9k83-KDy1m83E+y1m9k83-oCy1m83E+y1m9k83-hPy1m83E+y1m9k83-h3y1m83E+y1m9k83-QUy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_139,
	    string_constant_140)));
    string_constant_141 = STATIC_STRING("1l1m836Vy83-ey");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_141));
    string_constant_57 = STATIC_STRING("date outside of legal range");
    SET_SYMBOL_FUNCTION(Qtransform_input_phrase_into_universal_date,
	    STATIC_FUNCTION(transform_input_phrase_into_universal_date,NIL,
	    FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qtransform_input_phrase_into_universal_date);
    Qdate_qm = STATIC_SYMBOL("DATE\?",AB_package);
    Qcompile_date_qm_for_slot = STATIC_SYMBOL("COMPILE-DATE\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_date_qm_for_slot,
	    STATIC_FUNCTION(compile_date_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qdate_qm,
	    SYMBOL_FUNCTION(Qcompile_date_qm_for_slot),Qslot_value_compiler);
    mutate_global_property(Qdate_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_date_qm_from_slot = STATIC_SYMBOL("WRITE-DATE\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_date_qm_from_slot,
	    STATIC_FUNCTION(write_date_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qdate_qm,
	    SYMBOL_FUNCTION(Qwrite_date_qm_from_slot),Qslot_value_writer);
    Qcheck_ddd_dddd_format = STATIC_SYMBOL("CHECK-DDD-DDDD-FORMAT",AB_package);
    string_constant_142 = 
	    STATIC_STRING("13Ey1o836qy1m83Toy83-hky1n836qylm9k1o83-hky1m83-Umy83ZBy1n836qylm9k1o83-hky1m83-Umy83-Uny1n836qylm9k1o83-Uny1m83VUy83-hky1n836qy");
    string_constant_143 = 
	    STATIC_STRING("lm9k1m83-Umy83=py1n83-Umy1p83=py1m9l83*5y83=Zy1m9l831Ay1m9l83A*y1n838Pyl1m9l832ny1n83-Umy1o83=py1m9l83*5y83=Zy1m9l83-oy1n838Pyl1");
    string_constant_144 = 
	    STATIC_STRING("m9l832Ky1o83-Umy1n83=py1m9l83*5y83J9y1n83J9yln9m1m83=py836qy1o83-v5y1m83Toy83-v8y1n836qylm9k1o83-v8y1m83-v3y83ZBy1n836qylm9k1o83");
    string_constant_145 = 
	    STATIC_STRING("-v8y1m83-v3y83-v4y1n836qylm9k1o83-v4y1m83VUy83-v8y1n836qylm9k1m83-v3y83=xy1n83-v3y1p83=xy1m9l83*5y83=Zy1m9l831Ay1m9l83A*y1n838Py");
    string_constant_146 = 
	    STATIC_STRING("l1m9l832ny1n83-v3y1o83=xy1m9l83*5y83=Zy1m9l83-oy1n838Pyl1m9l832Ky1o83-v3y1n83=xy1m9l83*5y83J9y1n83J9yln9m1m83=xy83-v5y");
    clear_optimized_constants();
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qcheck_ddd_dddd_format);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_142,
	    string_constant_143,string_constant_144,string_constant_145,
	    string_constant_146)));
    Qmiscellaneous_parameters = STATIC_SYMBOL("MISCELLANEOUS-PARAMETERS",
	    AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_130 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qmiscellaneous_parameters,
	    list_constant_130);
    string_constant_147 = STATIC_STRING("1l1l83ey");
    Qget_slot_init_form = STATIC_SYMBOL("GET-SLOT-INIT-FORM",AB_package);
    SET_SYMBOL_FUNCTION(Qget_slot_init_form,
	    STATIC_FUNCTION(get_slot_init_form,NIL,TRUE,2,3));
    Qcurrent_g2_run_state = STATIC_SYMBOL("CURRENT-G2-RUN-STATE",AB_package);
    SET_SYMBOL_FUNCTION(Qcurrent_g2_run_state,
	    STATIC_FUNCTION(current_g2_run_state,NIL,FALSE,0,0));
    string_constant_148 = 
	    STATIC_STRING("13Hy4z8r83Ywy83Ywy83Vny83Vny00001n1l8o1l8l1m8p83Ky000004z8r83D+y83D+y83Vny83Vny01o8w9k83=uy83*Ly001n1l8o1l8l1m8p83D+y000004z8r83");
    string_constant_149 = 
	    STATIC_STRING("aty83aty83Vny83Vny00001n1l8o1l8l1m8p83Ky000004z8r83NNy83NNy83Vny83Vny01m83*Ay9l001p1l8o1l8l1l83Hy1l83Fy1m8p83NNy000004z8r83Ify83");
    string_constant_150 = 
	    STATIC_STRING("Ify83Vny83Vny00001m1l8l1m8p83Ky000004z8r83H2y83H2y83Vny83Vny00001n1l8o1l8l1m8p83H3y000004z8r83a*y83a*y83Vny83Vny00001n1l8l1l83Cy");
    string_constant_151 = 
	    STATIC_STRING("1m8p83Ky000004z8r83D1y83D1y83Vny83Vny0835oy001o1l8l1l83Hy1l83Ny1m8p83D1y000004z8r83DTy83DTy83Vny83Vny00001o1l8l1l83Hy1l83Ny1m8p8");
    string_constant_152 = 
	    STATIC_STRING("3DTy000004z8r83Kry83Kry83Vny83Vny00001n1l83Ey1l8l1m8p83Ky000004z8r83Ihy83Ihy83Vny83Vny00001n1l83Ey1l8l1m8p83Ky000004z8r83JQy83JQ");
    string_constant_153 = 
	    STATIC_STRING("y83Vny83Vny00001n1l8o1l8l1m8p830Ky000004z8r83Y1y83Y1y83Vny83Vny08k001o1m8p83Ky1l8o1l8l1l83Cy000004z8r83H-y83H-y83Vny83Vny00001o1");
    string_constant_154 = 
	    STATIC_STRING("m8p83BYy1l8o1l8l1l83Cy000004z8r83LZy83LZy83Vny83Vny083Py001n1m8p83C3y1l8o1l8l000004z8r83Lay83Lay83Vny83Vny0n001n1m8p83C2y1l8o1l8");
    string_constant_155 = 
	    STATIC_STRING("l000004z8r83HXy83HXy83Vny83Vny083=Oy001n1l8o1l8l1m8p83Ky000004z8r83Huy83Huy83Vny83Vny083CUy001o1m8p83B7y1l8o1l8l1l83Cy000004z8r8");
    string_constant_156 = 
	    STATIC_STRING("3ecy83ecy83Vny83Vny00001n1l8o1l8l1m8p83Ky000004z8r83Rwy83Rwy83Vny83Vny00001n1l8o1l8l1m8p83Ky000004z8r83GZy83GZy83Vny83Vny00001n1");
    string_constant_157 = STATIC_STRING("l8l1l83Cy1m8p83Ky00000");
    string_constant_158 = 
	    STATIC_STRING("13Jy8q1n83Vny1l83-sy83ey1p83Ywy08o8l1m8p83Ky1p83D+y1o8w9k83=uy83*Ly8o8l1m8p83D+y1p83aty08o8l1m8p83Ky1r83NNy1m83*Ay9l8o8l83Hy83Fy");
    string_constant_159 = 
	    STATIC_STRING("1m8p83NNy1o83Ify08l1m8p83Ky1p83H2y08o8l1m8p83H3y1p83a*y01l8l1l83Cy1m8p83Ky1q83D1y835oy8l83Hy1l83Ny1m8p83D1y1q83DTy08l83Hy1l83Ny1");
    string_constant_160 = 
	    STATIC_STRING("m8p83DTy1p83Kry083Ey8l1m8p83Ky1p83Ihy083Ey8l1m8p83Ky1p83JQy08o8l1m8p830Ky1q83Y1y8k1m8p83Ky8o8l83Cy1q83H-y01m8p83BYy8o8l83Cy1p83L");
    string_constant_161 = 
	    STATIC_STRING("Zy83Py1m8p83C3y8o8l1p83Layn1m8p83C2y8o8l1p83HXy83=Oy8o8l1m8p83Ky1q83Huy83CUy1m8p83B7y1l8o1l8l1l83Cy1p83ecy08o8l1m8p83Ky1p83Rwy08");
    string_constant_162 = 
	    STATIC_STRING("o8l1m8p83Ky1p83GZy01l8l1l83Cy1m8p83Ky");
    temp = regenerate_optimized_constant(string_constant_147);
    clear_optimized_constants();
    push_optimized_constant(Qget_slot_init_form);
    push_optimized_constant(Qcurrent_g2_run_state);
    temp_1 = regenerate_optimized_constant(list(10,string_constant_148,
	    string_constant_149,string_constant_150,string_constant_151,
	    string_constant_152,string_constant_153,string_constant_154,
	    string_constant_155,string_constant_156,string_constant_157));
    clear_optimized_constants();
    push_optimized_constant(Qget_slot_init_form);
    push_optimized_constant(Qcurrent_g2_run_state);
    add_class_to_environment(9,Qmiscellaneous_parameters,list_constant_130,
	    Nil,temp,Nil,temp_1,list_constant_130,
	    regenerate_optimized_constant(LIST_5(string_constant_158,
	    string_constant_159,string_constant_160,string_constant_161,
	    string_constant_162)),Nil);
    Qgrammar7 = STATIC_SYMBOL("GRAMMAR7",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qmiscellaneous_parameters,Qgrammar7,
	    Ksystem_frame,Qnil,Qnil,Qnil,Qt);
    string_constant_163 = STATIC_STRING("1m1m83B7y1m9k83CUy1m83B7y1m9k83-bYy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_163));
    Qcharting_library_type_select = 
	    STATIC_SYMBOL("CHARTING-LIBRARY-TYPE-SELECT",AB_package);
    Qcompile_charting_library_type_select_for_slot = 
	    STATIC_SYMBOL("COMPILE-CHARTING-LIBRARY-TYPE-SELECT-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_charting_library_type_select_for_slot,
	    STATIC_FUNCTION(compile_charting_library_type_select_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qcharting_library_type_select,
	    SYMBOL_FUNCTION(Qcompile_charting_library_type_select_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qcharting_library_type_select,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgigasoft = STATIC_SYMBOL("GIGASOFT",AB_package);
    string_constant_58 = STATIC_STRING("gigasoft");
    Qjfreechart = STATIC_SYMBOL("JFREECHART",AB_package);
    string_constant_59 = STATIC_STRING("jfreechart");
    Qwrite_charting_library_type_select_from_slot = 
	    STATIC_SYMBOL("WRITE-CHARTING-LIBRARY-TYPE-SELECT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_charting_library_type_select_from_slot,
	    STATIC_FUNCTION(write_charting_library_type_select_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcharting_library_type_select,
	    SYMBOL_FUNCTION(Qwrite_charting_library_type_select_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qcharting_library_type_select),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qmember,Qgigasoft,Qjfreechart);
    define_type_specification_explicit_complex_type(Qcharting_library_type_select,
	    list_constant_20);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qcharting_library_type_select);
    charting_library_type_select_evaluation_setter_1 = 
	    STATIC_FUNCTION(charting_library_type_select_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qcharting_library_type_select,
	    charting_library_type_select_evaluation_setter_1);
    charting_library_type_select_evaluation_getter_1 = 
	    STATIC_FUNCTION(charting_library_type_select_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcharting_library_type_select,
	    charting_library_type_select_evaluation_getter_1);
    string_constant_164 = STATIC_STRING("1m1m83BYy83-oy1m83BYy1m9k8329y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_164));
    string_constant_60 = STATIC_STRING("~f seconds");
    string_constant_61 = STATIC_STRING("never");
    Qdeadlock_detection_frequency_type = 
	    STATIC_SYMBOL("DEADLOCK-DETECTION-FREQUENCY-TYPE",AB_package);
    Qwrite_deadlock_detection_frequency_type_from_slot = 
	    STATIC_SYMBOL("WRITE-DEADLOCK-DETECTION-FREQUENCY-TYPE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_deadlock_detection_frequency_type_from_slot,
	    STATIC_FUNCTION(write_deadlock_detection_frequency_type_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdeadlock_detection_frequency_type,
	    SYMBOL_FUNCTION(Qwrite_deadlock_detection_frequency_type_from_slot),
	    Qslot_value_writer);
    list_constant_131 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnil,
	    list_constant_101);
    set_property_value_function(get_symbol_properties_function(Qdeadlock_detection_frequency_type),
	    Qtype_specification_simple_expansion,list_constant_131);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    list_constant_132 = STATIC_LIST((SI_Long)2L,Qmember,Qnever);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_132,list_constant_101);
    define_type_specification_explicit_complex_type(Qdeadlock_detection_frequency_type,
	    list_constant_22);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdeadlock_detection_frequency_type);
    deadlock_detection_frequency_type_evaluation_setter_1 = 
	    STATIC_FUNCTION(deadlock_detection_frequency_type_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdeadlock_detection_frequency_type,
	    deadlock_detection_frequency_type_evaluation_setter_1);
    deadlock_detection_frequency_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(deadlock_detection_frequency_type_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdeadlock_detection_frequency_type,
	    deadlock_detection_frequency_type_evaluation_getter_1);
    string_constant_62 = 
	    STATIC_STRING("The interval must be at least 1 second");
    Qcompile_deadlock_detection_frequency_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-DEADLOCK-DETECTION-FREQUENCY-TYPE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_deadlock_detection_frequency_type_for_slot,
	    STATIC_FUNCTION(compile_deadlock_detection_frequency_type_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qdeadlock_detection_frequency_type,
	    SYMBOL_FUNCTION(Qcompile_deadlock_detection_frequency_type_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdeadlock_detection_frequency_type,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qautomatic_deadlock_detection_frequency = 
	    STATIC_SYMBOL("AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY",AB_package);
    Qput_automatic_deadlock_detection_frequency = 
	    STATIC_SYMBOL("PUT-AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_automatic_deadlock_detection_frequency,
	    STATIC_FUNCTION(put_automatic_deadlock_detection_frequency,NIL,
	    FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qautomatic_deadlock_detection_frequency,
	    SYMBOL_FUNCTION(Qput_automatic_deadlock_detection_frequency),
	    Qslot_putter);
    Qactivate_for_miscellaneous_parameters = 
	    STATIC_SYMBOL("ACTIVATE-FOR-MISCELLANEOUS-PARAMETERS",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_miscellaneous_parameters,
	    STATIC_FUNCTION(activate_for_miscellaneous_parameters,NIL,
	    FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_miscellaneous_parameters);
    set_get(Qmiscellaneous_parameters,Qactivate,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qmiscellaneous_parameters,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    Qexplanation_related_features_enabled_qm = 
	    STATIC_SYMBOL("EXPLANATION-RELATED-FEATURES-ENABLED\?",AB_package);
    Qenable_explanation_controls = 
	    STATIC_SYMBOL("ENABLE-EXPLANATION-CONTROLS",AB_package);
    alias_slot_name(3,Qexplanation_related_features_enabled_qm,
	    Qenable_explanation_controls,Qmiscellaneous_parameters);
    Qconnection_caching_enabled_qm = 
	    STATIC_SYMBOL("CONNECTION-CACHING-ENABLED\?",AB_package);
    Qinstall_system_table_for_miscellaneous_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-MISCELLANEOUS-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_miscellaneous_parameters,
	    STATIC_FUNCTION(install_system_table_for_miscellaneous_parameters,
	    NIL,FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qinstall_system_table_for_miscellaneous_parameters);
    set_get(Qmiscellaneous_parameters,Qinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qmiscellaneous_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_miscellaneous_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-MISCELLANEOUS-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_miscellaneous_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_miscellaneous_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qdeinstall_system_table_for_miscellaneous_parameters);
    set_get(Qmiscellaneous_parameters,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qmiscellaneous_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    Qbackward_compatibility_features = 
	    STATIC_SYMBOL("BACKWARD-COMPATIBILITY-FEATURES",AB_package);
    Qright_click_lifts_to_top_in_native_ui = 
	    STATIC_SYMBOL("RIGHT-CLICK-LIFTS-TO-TOP-IN-NATIVE-UI",AB_package);
    Qput_backward_compatibility_features = 
	    STATIC_SYMBOL("PUT-BACKWARD-COMPATIBILITY-FEATURES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_backward_compatibility_features,
	    STATIC_FUNCTION(put_backward_compatibility_features,NIL,FALSE,
	    3,3));
    mutate_global_property(Qbackward_compatibility_features,
	    SYMBOL_FUNCTION(Qput_backward_compatibility_features),
	    Qslot_putter);
    Qput_connection_caching_enabled_qm = 
	    STATIC_SYMBOL("PUT-CONNECTION-CACHING-ENABLED\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_connection_caching_enabled_qm,
	    STATIC_FUNCTION(put_connection_caching_enabled_qm,NIL,FALSE,3,3));
    mutate_global_property(Qconnection_caching_enabled_qm,
	    SYMBOL_FUNCTION(Qput_connection_caching_enabled_qm),Qslot_putter);
    Qallow_only_one_table_display_for_item_qm = 
	    STATIC_SYMBOL("ALLOW-ONLY-ONE-TABLE-DISPLAY-FOR-ITEM\?",
	    AB_package);
    Qg2_run_state = STATIC_SYMBOL("G2-RUN-STATE",AB_package);
    Qwrite_g2_run_state_from_slot = 
	    STATIC_SYMBOL("WRITE-G2-RUN-STATE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_g2_run_state_from_slot,
	    STATIC_FUNCTION(write_g2_run_state_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qg2_run_state,
	    SYMBOL_FUNCTION(Qwrite_g2_run_state_from_slot),Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qg2_run_state),
	    Qtype_specification_simple_expansion,Qsymbol);
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    Qpaused = STATIC_SYMBOL("PAUSED",AB_package);
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    list_constant_133 = STATIC_LIST((SI_Long)5L,Qmember,Qreset,Qrunning,
	    Qpaused,Qabort_g2);
    define_type_specification_explicit_complex_type(Qg2_run_state,
	    list_constant_133);
    g2_run_state_evaluation_getter_1 = 
	    STATIC_FUNCTION(g2_run_state_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qg2_run_state,
	    g2_run_state_evaluation_getter_1);
    Qconfirm_run_state_changes = STATIC_SYMBOL("CONFIRM-RUN-STATE-CHANGES",
	    AB_package);
    Qbackward_compatible_g2_feature_list = 
	    STATIC_SYMBOL("BACKWARD-COMPATIBLE-G2-FEATURE-LIST",AB_package);
    Qbackward_compatible_g2_feature_list_item = 
	    STATIC_SYMBOL("BACKWARD-COMPATIBLE-G2-FEATURE-LIST-ITEM",
	    AB_package);
    add_grammar_rules_for_list(5,Qbackward_compatible_g2_feature_list,
	    Qbackward_compatible_g2_feature_list_item,Nil,Nil,Qnone);
    list_constant_134 = STATIC_CONS(Qsequence,Qnil);
    list_constant_135 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_134);
    set_property_value_function(get_symbol_properties_function(Qbackward_compatible_g2_feature_list),
	    Qtype_specification_simple_expansion,list_constant_135);
    Qignore_duplicate_list_element_error = 
	    STATIC_SYMBOL("IGNORE-DUPLICATE-LIST-ELEMENT-ERROR",AB_package);
    Qextra_vertices_in_g2_get_connection_vertices = 
	    STATIC_SYMBOL("EXTRA-VERTICES-IN-G2-GET-CONNECTION-VERTICES",
	    AB_package);
    Qprint_means_print_to_server_in_configurations = 
	    STATIC_SYMBOL("PRINT-MEANS-PRINT-TO-SERVER-IN-CONFIGURATIONS",
	    AB_package);
    Qinconsistent_behavior_of_move_in_configurations = 
	    STATIC_SYMBOL("INCONSISTENT-BEHAVIOR-OF-MOVE-IN-CONFIGURATIONS",
	    AB_package);
    Qignore_snap_grid_in_transfer_operations = 
	    STATIC_SYMBOL("IGNORE-SNAP-GRID-IN-TRANSFER-OPERATIONS",
	    AB_package);
    Qfirst_value_ok_for_the_named_by_grammar = 
	    STATIC_SYMBOL("FIRST-VALUE-OK-FOR-THE-NAMED-BY-GRAMMAR",
	    AB_package);
    list_constant_136 = STATIC_LIST((SI_Long)7L,Qmember,
	    Qignore_duplicate_list_element_error,
	    Qextra_vertices_in_g2_get_connection_vertices,
	    Qprint_means_print_to_server_in_configurations,
	    Qinconsistent_behavior_of_move_in_configurations,
	    Qignore_snap_grid_in_transfer_operations,
	    Qfirst_value_ok_for_the_named_by_grammar);
    list_constant_137 = STATIC_LIST((SI_Long)3L,Qsequence,
	    list_constant_136,FIX((SI_Long)0L));
    list_constant_24 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_137);
    define_type_specification_explicit_complex_type(Qbackward_compatible_g2_feature_list,
	    list_constant_24);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qbackward_compatible_g2_feature_list);
    backward_compatible_g2_feature_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(backward_compatible_g2_feature_list_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qbackward_compatible_g2_feature_list,
	    backward_compatible_g2_feature_list_evaluation_setter_1);
    backward_compatible_g2_feature_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(backward_compatible_g2_feature_list_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qbackward_compatible_g2_feature_list,
	    backward_compatible_g2_feature_list_evaluation_getter_1);
    Qinitial_margin_for_workspaces = 
	    STATIC_SYMBOL("INITIAL-MARGIN-FOR-WORKSPACES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinitial_margin_for_workspaces),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qinitial_margin_for_workspaces,
	    Qinteger);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qinitial_margin_for_workspaces);
    initial_margin_for_workspaces_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_margin_for_workspaces_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qinitial_margin_for_workspaces,
	    initial_margin_for_workspaces_evaluation_setter_1);
    initial_margin_for_workspaces_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_margin_for_workspaces_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_margin_for_workspaces,
	    initial_margin_for_workspaces_evaluation_getter_1);
    Qg2_get_connection_vertices = 
	    STATIC_SYMBOL("G2-GET-CONNECTION-VERTICES",AB_package);
    string_constant_165 = 
	    STATIC_STRING("1r1m83D+y83Sy1n83-KYy1p1m9k83-Z=y1m9k83gpy1m9k9l1m9k83Buy1m9k9m83-Z0y1n83-KYy1o1m9k83-Tay1m9k83-GTy1m9k83*Xy1m9k9n83-Tgy1n83-KYy");
    string_constant_166 = 
	    STATIC_STRING("1p1m9k9o1m9k83-e5y1m9k836+y1m9k83*Xy1m9k83-Nny83-jay1n83-KYy1q1m9k83-Zby1m9k83-Kiy1m9k83-Ty1m9k83*py1m9k83*Xy1m9k83-Nny83-Zcy1n8");
    string_constant_167 = 
	    STATIC_STRING("3-KYy1q1m9k83-Z=y1m9k83-DHy1m9k83Qxy1m9k83*Xy1m9k832oy1m9k83-hqy83-Z2y1n83-KYy1r1m9k9p1m9k83*ly1m9k839Xy1m9k83=Iy1m9k9q1m9k83-7D");
    string_constant_168 = STATIC_STRING("y1m9k83-X-y83-UAy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qlist);
    push_optimized_constant(Qerror);
    push_optimized_constant(Qg2_get_connection_vertices);
    push_optimized_constant(Qprint);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_165,
	    string_constant_166,string_constant_167,string_constant_168)));
    string_constant_63 = STATIC_STRING("~d");
    Qwrite_initial_margin_for_workspaces_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-MARGIN-FOR-WORKSPACES-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_margin_for_workspaces_from_slot,
	    STATIC_FUNCTION(write_initial_margin_for_workspaces_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinitial_margin_for_workspaces,
	    SYMBOL_FUNCTION(Qwrite_initial_margin_for_workspaces_from_slot),
	    Qslot_value_writer);
    Qinitial_width_or_height_for_workspaces = 
	    STATIC_SYMBOL("INITIAL-WIDTH-OR-HEIGHT-FOR-WORKSPACES",AB_package);
    Qwrite_initial_width_or_height_for_workspaces_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-WIDTH-OR-HEIGHT-FOR-WORKSPACES-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_width_or_height_for_workspaces_from_slot,
	    STATIC_FUNCTION(write_initial_width_or_height_for_workspaces_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinitial_width_or_height_for_workspaces,
	    SYMBOL_FUNCTION(Qwrite_initial_width_or_height_for_workspaces_from_slot),
	    Qslot_value_writer);
    Qcompile_backward_compatible_g2_feature_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-BACKWARD-COMPATIBLE-G2-FEATURE-LIST-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_backward_compatible_g2_feature_list_for_slot,
	    STATIC_FUNCTION(compile_backward_compatible_g2_feature_list_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qbackward_compatible_g2_feature_list,
	    SYMBOL_FUNCTION(Qcompile_backward_compatible_g2_feature_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qbackward_compatible_g2_feature_list,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_64 = STATIC_STRING("ignore duplicate list element error");
    string_constant_65 = 
	    STATIC_STRING("extra vertices in g2-get-connection-vertices");
    string_constant_66 = 
	    STATIC_STRING("print means print-to-server in configurations");
    string_constant_67 = 
	    STATIC_STRING("inconsistent behavior of move in configurations");
    string_constant_68 = 
	    STATIC_STRING("ignore snap grid in transfer operations");
    string_constant_69 = 
	    STATIC_STRING("first value ok for the named-by grammar");
    string_constant_70 = STATIC_STRING("unknown");
    Qtwrite_backward_compatible_g2_feature_list_item = 
	    STATIC_SYMBOL("TWRITE-BACKWARD-COMPATIBLE-G2-FEATURE-LIST-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qtwrite_backward_compatible_g2_feature_list_item,
	    STATIC_FUNCTION(twrite_backward_compatible_g2_feature_list_item,
	    NIL,FALSE,1,1));
    Qwrite_backward_compatible_g2_feature_list_from_slot = 
	    STATIC_SYMBOL("WRITE-BACKWARD-COMPATIBLE-G2-FEATURE-LIST-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_backward_compatible_g2_feature_list_from_slot,
	    STATIC_FUNCTION(write_backward_compatible_g2_feature_list_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qbackward_compatible_g2_feature_list,
	    SYMBOL_FUNCTION(Qwrite_backward_compatible_g2_feature_list_from_slot),
	    Qslot_value_writer);
    Qab_standard = STATIC_SYMBOL("STANDARD",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qworkspace_margin = STATIC_SYMBOL("WORKSPACE-MARGIN",AB_package);
    string_constant_71 = 
	    STATIC_STRING("Please choose an integer between 0 and 100.");
    Qcompile_initial_margin_for_workspaces_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-MARGIN-FOR-WORKSPACES-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_margin_for_workspaces_for_slot,
	    STATIC_FUNCTION(compile_initial_margin_for_workspaces_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qinitial_margin_for_workspaces,
	    SYMBOL_FUNCTION(Qcompile_initial_margin_for_workspaces_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_margin_for_workspaces,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qinlineable = STATIC_SYMBOL("INLINEABLE",AB_package);
    Qdefault_window_style = STATIC_SYMBOL("DEFAULT-WINDOW-STYLE",AB_package);
    Qput_default_window_style = STATIC_SYMBOL("PUT-DEFAULT-WINDOW-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_default_window_style,
	    STATIC_FUNCTION(put_default_window_style,NIL,FALSE,3,3));
    mutate_global_property(Qdefault_window_style,
	    SYMBOL_FUNCTION(Qput_default_window_style),Qslot_putter);
    string_constant_169 = 
	    STATIC_STRING("1q1m83C3y1m9k83Py1m83C3y1m9k9l1m83C3y1m9k83-TMy1m83C3y1m9k83-Kky1m83C3y1m9k83-UYy1m83C2y83*7y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_169));
    Qfloating_point_number_text_style_name = 
	    STATIC_SYMBOL("FLOATING-POINT-NUMBER-TEXT-STYLE-NAME",AB_package);
    Qcompile_floating_point_number_text_style_name_for_slot = 
	    STATIC_SYMBOL("COMPILE-FLOATING-POINT-NUMBER-TEXT-STYLE-NAME-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_floating_point_number_text_style_name_for_slot,
	    STATIC_FUNCTION(compile_floating_point_number_text_style_name_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qfloating_point_number_text_style_name,
	    SYMBOL_FUNCTION(Qcompile_floating_point_number_text_style_name_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfloating_point_number_text_style_name,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_72 = STATIC_STRING("float");
    Qexponent = STATIC_SYMBOL("EXPONENT",AB_package);
    string_constant_73 = STATIC_STRING("exponent");
    Qbest = STATIC_SYMBOL("BEST",AB_package);
    string_constant_74 = STATIC_STRING("best");
    Qforce_zero = STATIC_SYMBOL("FORCE-ZERO",AB_package);
    string_constant_75 = STATIC_STRING("force-zero");
    Qwrite_floating_point_number_text_style_name_from_slot = 
	    STATIC_SYMBOL("WRITE-FLOATING-POINT-NUMBER-TEXT-STYLE-NAME-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_floating_point_number_text_style_name_from_slot,
	    STATIC_FUNCTION(write_floating_point_number_text_style_name_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qfloating_point_number_text_style_name,
	    SYMBOL_FUNCTION(Qwrite_floating_point_number_text_style_name_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qfloating_point_number_text_style_name),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_27 = STATIC_LIST((SI_Long)6L,Qmember,Qdefault,Qfloat,
	    Qexponent,Qbest,Qforce_zero);
    define_type_specification_explicit_complex_type(Qfloating_point_number_text_style_name,
	    list_constant_27);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qfloating_point_number_text_style_name);
    floating_point_number_text_style_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(floating_point_number_text_style_name_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfloating_point_number_text_style_name,
	    floating_point_number_text_style_name_evaluation_setter_1);
    floating_point_number_text_style_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(floating_point_number_text_style_name_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfloating_point_number_text_style_name,
	    floating_point_number_text_style_name_evaluation_getter_1);
    string_constant_76 = 
	    STATIC_STRING("Floating point number precision must be a number between 0 and 16.");
    Qfloating_point_number_precision = 
	    STATIC_SYMBOL("FLOATING-POINT-NUMBER-PRECISION",AB_package);
    Qcompile_floating_point_number_precision_for_slot = 
	    STATIC_SYMBOL("COMPILE-FLOATING-POINT-NUMBER-PRECISION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_floating_point_number_precision_for_slot,
	    STATIC_FUNCTION(compile_floating_point_number_precision_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qfloating_point_number_precision,
	    SYMBOL_FUNCTION(Qcompile_floating_point_number_precision_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfloating_point_number_precision,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_floating_point_number_precision_from_slot = 
	    STATIC_SYMBOL("WRITE-FLOATING-POINT-NUMBER-PRECISION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_floating_point_number_precision_from_slot,
	    STATIC_FUNCTION(write_floating_point_number_precision_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qfloating_point_number_precision,
	    SYMBOL_FUNCTION(Qwrite_floating_point_number_precision_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qfloating_point_number_precision),
	    Qtype_specification_simple_expansion,Qnil);
    Qnon_negative_integer = STATIC_SYMBOL("NON-NEGATIVE-INTEGER",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qnamed,Qnon_negative_integer);
    define_type_specification_explicit_complex_type(Qfloating_point_number_precision,
	    list_constant_29);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qfloating_point_number_precision);
    floating_point_number_precision_evaluation_setter_1 = 
	    STATIC_FUNCTION(floating_point_number_precision_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfloating_point_number_precision,
	    floating_point_number_precision_evaluation_setter_1);
    floating_point_number_precision_evaluation_getter_1 = 
	    STATIC_FUNCTION(floating_point_number_precision_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfloating_point_number_precision,
	    floating_point_number_precision_evaluation_getter_1);
    Qclose_log_file = STATIC_SYMBOL("CLOSE-LOG-FILE",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_170 = 
	    STATIC_STRING("1x1m83DUy1m9k83Py1m83DUy83-Uy1m83DWy83-Uy1m83DVy832fy1m9l83-vXy1m83Aty1m9k8329y1m83Aty83-vXy1n83-vXy1m1m9k835+y83-dCy1lm1n83-vXy");
    string_constant_171 = 
	    STATIC_STRING("1m1m9k835+y83-oy1lm1n83-vXy1s1m9k835+y83-dCy1m9k83=Uy83-oy1m9k83vy1m9k83-x2y1m9k83-NBy1m9k9m1mmo1n83-vXy1s1m9k835+y83-oy1m9k83=U");
    string_constant_172 = 
	    STATIC_STRING("y83-dCy1m9k83vy1m9k83-x2y1m9k83-NBy1m9k9m1mmo1n83-dCy1m83Sy1m9k83Djyl1n83-dCy1m83Sy1m9k9nl");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qclose_log_file);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qmessage);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_170,
	    string_constant_171,string_constant_172)));
    Qlog_file_directory = STATIC_SYMBOL("LOG-FILE-DIRECTORY",AB_package);
    Qwrite_log_file_directory_from_slot = 
	    STATIC_SYMBOL("WRITE-LOG-FILE-DIRECTORY-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_log_file_directory_from_slot,
	    STATIC_FUNCTION(write_log_file_directory_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlog_file_directory,
	    SYMBOL_FUNCTION(Qwrite_log_file_directory_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qlog_file_directory),
	    Qtype_specification_simple_expansion,list_constant_109);
    list_constant_138 = STATIC_LIST((SI_Long)2L,Qmember,Qdefault);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string);
    list_constant_31 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_138,
	    list_constant_33);
    define_type_specification_explicit_complex_type(Qlog_file_directory,
	    list_constant_31);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qnamed,Qlog_file_directory);
    log_file_directory_evaluation_setter_1 = 
	    STATIC_FUNCTION(log_file_directory_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qlog_file_directory,
	    log_file_directory_evaluation_setter_1);
    log_file_directory_evaluation_getter_1 = 
	    STATIC_FUNCTION(log_file_directory_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qlog_file_directory,
	    log_file_directory_evaluation_getter_1);
    array_constant_5 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)33L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)36L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)40L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)42L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)45L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)46L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)49L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)50L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)51L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)52L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)54L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)55L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)62L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)63L,(SI_Long)57344L);
    Qcompile_log_file_directory_for_slot = 
	    STATIC_SYMBOL("COMPILE-LOG-FILE-DIRECTORY-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_log_file_directory_for_slot,
	    STATIC_FUNCTION(compile_log_file_directory_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlog_file_directory,
	    SYMBOL_FUNCTION(Qcompile_log_file_directory_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlog_file_directory,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_6 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    Qlog_file_name = STATIC_SYMBOL("LOG-FILE-NAME",AB_package);
    Qwrite_log_file_name_from_slot = 
	    STATIC_SYMBOL("WRITE-LOG-FILE-NAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_log_file_name_from_slot,
	    STATIC_FUNCTION(write_log_file_name_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlog_file_name,
	    SYMBOL_FUNCTION(Qwrite_log_file_name_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qlog_file_name),
	    Qtype_specification_simple_expansion,Qnil);
    define_type_specification_explicit_complex_type(Qlog_file_name,
	    list_constant_33);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qnamed,Qlog_file_name);
    log_file_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(log_file_name_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlog_file_name,
	    log_file_name_evaluation_setter_1);
    log_file_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(log_file_name_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlog_file_name,
	    log_file_name_evaluation_getter_1);
    Qcompile_log_file_name_for_slot = 
	    STATIC_SYMBOL("COMPILE-LOG-FILE-NAME-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_log_file_name_for_slot,
	    STATIC_FUNCTION(compile_log_file_name_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlog_file_name,
	    SYMBOL_FUNCTION(Qcompile_log_file_name_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlog_file_name,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qlog_file_maximum = STATIC_SYMBOL("LOG-FILE-MAXIMUM",AB_package);
    Qwrite_log_file_maximum_from_slot = 
	    STATIC_SYMBOL("WRITE-LOG-FILE-MAXIMUM-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_log_file_maximum_from_slot,
	    STATIC_FUNCTION(write_log_file_maximum_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlog_file_maximum,
	    SYMBOL_FUNCTION(Qwrite_log_file_maximum_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qlog_file_maximum),
	    Qtype_specification_simple_expansion,Qnil);
    Qpositive_integer_qm = STATIC_SYMBOL("POSITIVE-INTEGER\?",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qnamed,Qpositive_integer_qm);
    define_type_specification_explicit_complex_type(Qlog_file_maximum,
	    list_constant_35);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qnamed,Qlog_file_maximum);
    log_file_maximum_evaluation_setter_1 = 
	    STATIC_FUNCTION(log_file_maximum_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlog_file_maximum,
	    log_file_maximum_evaluation_setter_1);
    log_file_maximum_evaluation_getter_1 = 
	    STATIC_FUNCTION(log_file_maximum_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlog_file_maximum,
	    log_file_maximum_evaluation_getter_1);
    string_constant_77 = 
	    STATIC_STRING("The maximum number of log files must be either none or a number ~\n            between 1 and 999.");
    Qcompile_log_file_maximum_for_slot = 
	    STATIC_SYMBOL("COMPILE-LOG-FILE-MAXIMUM-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_log_file_maximum_for_slot,
	    STATIC_FUNCTION(compile_log_file_maximum_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlog_file_maximum,
	    SYMBOL_FUNCTION(Qcompile_log_file_maximum_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlog_file_maximum,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qupdate_log_file = STATIC_SYMBOL("UPDATE-LOG-FILE",AB_package);
    list_constant_139 = STATIC_CONS(list_constant_6,Qnil);
    list_constant_140 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_5,list_constant_139);
    set_property_value_function(get_symbol_properties_function(Qupdate_log_file),
	    Qtype_specification_simple_expansion,list_constant_140);
    Qafter_messages = STATIC_SYMBOL("AFTER-MESSAGES",AB_package);
    list_constant_141 = STATIC_CONS(Qafter_messages,list_constant_101);
    Qafter_interval = STATIC_SYMBOL("AFTER-INTERVAL",AB_package);
    list_constant_142 = STATIC_CONS(Qafter_interval,list_constant_101);
    list_constant_143 = STATIC_LIST((SI_Long)2L,list_constant_141,
	    list_constant_142);
    list_constant_144 = STATIC_LIST((SI_Long)3L,Qab_or,Qafter_messages,
	    Qafter_interval);
    list_constant_145 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_143,list_constant_144);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_145);
    define_type_specification_explicit_complex_type(Qupdate_log_file,
	    list_constant_37);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qnamed,Qupdate_log_file);
    update_log_file_evaluation_setter_1 = 
	    STATIC_FUNCTION(update_log_file_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qupdate_log_file,
	    update_log_file_evaluation_setter_1);
    update_log_file_evaluation_getter_1 = 
	    STATIC_FUNCTION(update_log_file_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qupdate_log_file,
	    update_log_file_evaluation_getter_1);
    Qwrite_close_log_file_from_slot = 
	    STATIC_SYMBOL("WRITE-CLOSE-LOG-FILE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_close_log_file_from_slot,
	    STATIC_FUNCTION(write_close_log_file_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qclose_log_file,
	    SYMBOL_FUNCTION(Qwrite_close_log_file_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qclose_log_file),
	    Qtype_specification_simple_expansion,Qnil);
    define_type_specification_explicit_complex_type(Qclose_log_file,
	    list_constant_36);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qnamed,Qclose_log_file);
    close_log_file_evaluation_setter_1 = 
	    STATIC_FUNCTION(close_log_file_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qclose_log_file,
	    close_log_file_evaluation_setter_1);
    close_log_file_evaluation_getter_1 = 
	    STATIC_FUNCTION(close_log_file_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qclose_log_file,
	    close_log_file_evaluation_getter_1);
    Qcompile_close_log_file_for_slot = 
	    STATIC_SYMBOL("COMPILE-CLOSE-LOG-FILE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_close_log_file_for_slot,
	    STATIC_FUNCTION(compile_close_log_file_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qclose_log_file,
	    SYMBOL_FUNCTION(Qcompile_close_log_file_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qclose_log_file,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qback_up_log_file = STATIC_SYMBOL("BACK-UP-LOG-FILE",AB_package);
    Qwrite_back_up_log_file_from_slot = 
	    STATIC_SYMBOL("WRITE-BACK-UP-LOG-FILE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_back_up_log_file_from_slot,
	    STATIC_FUNCTION(write_back_up_log_file_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qback_up_log_file,
	    SYMBOL_FUNCTION(Qwrite_back_up_log_file_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qback_up_log_file),
	    Qtype_specification_simple_expansion,list_constant_109);
    list_constant_40 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_132,
	    list_constant_36);
    define_type_specification_explicit_complex_type(Qback_up_log_file,
	    list_constant_40);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qnamed,Qback_up_log_file);
    back_up_log_file_evaluation_setter_1 = 
	    STATIC_FUNCTION(back_up_log_file_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qback_up_log_file,
	    back_up_log_file_evaluation_setter_1);
    back_up_log_file_evaluation_getter_1 = 
	    STATIC_FUNCTION(back_up_log_file_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qback_up_log_file,
	    back_up_log_file_evaluation_getter_1);
    Qcompile_back_up_log_file_for_slot = 
	    STATIC_SYMBOL("COMPILE-BACK-UP-LOG-FILE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_back_up_log_file_for_slot,
	    STATIC_FUNCTION(compile_back_up_log_file_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qback_up_log_file,
	    SYMBOL_FUNCTION(Qcompile_back_up_log_file_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qback_up_log_file,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_7 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    string_constant_78 = STATIC_STRING(" or ~d");
    array_constant_8 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    string_constant_79 = 
	    STATIC_STRING("The message count, ~d, must be between 1 and 9999.");
    array_constant_12 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_93,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)57344L);
    set_property_value_function(get_symbol_properties_function(Qcross_section_pattern),
	    Qtype_specification_simple_expansion,list_constant_140);
    Qcross_section_regions = STATIC_SYMBOL("CROSS-SECTION-REGIONS",AB_package);
    Qregion_name = STATIC_SYMBOL("REGION-NAME",AB_package);
    list_constant_147 = STATIC_CONS(Qregion_name,list_constant_92);
    Qregion_color = STATIC_SYMBOL("REGION-COLOR",AB_package);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    list_constant_146 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_or_metacolor);
    list_constant_148 = STATIC_LIST((SI_Long)2L,Qregion_color,
	    list_constant_146);
    list_constant_149 = STATIC_LIST((SI_Long)2L,list_constant_147,
	    list_constant_148);
    list_constant_150 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_149);
    list_constant_151 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_152 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_150,list_constant_151);
    list_constant_157 = STATIC_LIST((SI_Long)2L,Qcross_section_regions,
	    list_constant_152);
    Qcross_section_stripes = STATIC_SYMBOL("CROSS-SECTION-STRIPES",AB_package);
    Qregion_size = STATIC_SYMBOL("REGION-SIZE",AB_package);
    list_constant_153 = STATIC_CONS(Qregion_size,list_constant_101);
    list_constant_154 = STATIC_LIST((SI_Long)2L,list_constant_147,
	    list_constant_153);
    list_constant_155 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_154);
    list_constant_156 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_155,list_constant_151);
    list_constant_158 = STATIC_LIST((SI_Long)2L,Qcross_section_stripes,
	    list_constant_156);
    list_constant_159 = STATIC_LIST((SI_Long)2L,list_constant_157,
	    list_constant_158);
    list_constant_160 = STATIC_LIST((SI_Long)2L,Qand,Qcross_section_stripes);
    list_constant_161 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_159,list_constant_160);
    list_constant_42 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_161);
    define_type_specification_explicit_complex_type(Qcross_section_pattern,
	    list_constant_42);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qnamed,Qcross_section_pattern);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    cross_section_pattern_evaluation_setter_1 = 
	    STATIC_FUNCTION(cross_section_pattern_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qcross_section_pattern,
	    cross_section_pattern_evaluation_setter_1);
    cross_section_pattern_evaluation_getter_1 = 
	    STATIC_FUNCTION(cross_section_pattern_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcross_section_pattern,
	    cross_section_pattern_evaluation_getter_1);
    Qg2_meter_name = STATIC_SYMBOL("G2-METER-NAME",AB_package);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_92);
    set_property_value_function(get_symbol_properties_function(Qg2_meter_name),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qg2_meter_name,
	    list_constant_44);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qnamed,Qg2_meter_name);
    g2_meter_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(g2_meter_name_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qg2_meter_name,
	    g2_meter_name_evaluation_setter_1);
    g2_meter_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(g2_meter_name_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qg2_meter_name,
	    g2_meter_name_evaluation_getter_1);
    Qgfi_yes_or_no_qm = STATIC_SYMBOL("GFI-YES-OR-NO\?",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgfi_yes_or_no_qm),
	    Qtype_specification_simple_expansion,Qtruth_value);
    define_type_specification_explicit_complex_type(Qgfi_yes_or_no_qm,
	    Qtruth_value);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qnamed,Qgfi_yes_or_no_qm);
    gfi_yes_or_no_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_yes_or_no_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_yes_or_no_qm,
	    gfi_yes_or_no_qm_evaluation_setter_1);
    gfi_yes_or_no_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_yes_or_no_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_yes_or_no_qm,
	    gfi_yes_or_no_qm_evaluation_getter_1);
    Qgfi_file_format = STATIC_SYMBOL("GFI-FILE-FORMAT",AB_package);
    list_constant_162 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_5,list_constant_108);
    set_property_value_function(get_symbol_properties_function(Qgfi_file_format),
	    Qtype_specification_simple_expansion,list_constant_162);
    Qevent_log = STATIC_SYMBOL("EVENT-LOG",AB_package);
    Qspreadsheet = STATIC_SYMBOL("SPREADSHEET",AB_package);
    list_constant_163 = STATIC_LIST((SI_Long)3L,Qmember,Qevent_log,
	    Qspreadsheet);
    list_constant_47 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_163);
    define_type_specification_explicit_complex_type(Qgfi_file_format,
	    list_constant_47);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qnamed,Qgfi_file_format);
    gfi_file_format_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_file_format_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_file_format,
	    gfi_file_format_evaluation_setter_1);
    gfi_file_format_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_file_format_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_file_format,
	    gfi_file_format_evaluation_getter_1);
    Qgfi_time_stamp_format = STATIC_SYMBOL("GFI-TIME-STAMP-FORMAT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgfi_time_stamp_format),
	    Qtype_specification_simple_expansion,Qnil);
    Qexplicit_time_stamp = STATIC_SYMBOL("EXPLICIT-TIME-STAMP",AB_package);
    Qrelative_time_stamp = STATIC_SYMBOL("RELATIVE-TIME-STAMP",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qmember,
	    Qexplicit_time_stamp,Qrelative_time_stamp);
    define_type_specification_explicit_complex_type(Qgfi_time_stamp_format,
	    list_constant_49);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qnamed,Qgfi_time_stamp_format);
    Qexplicit = STATIC_SYMBOL("EXPLICIT",AB_package);
    Qrelative = STATIC_SYMBOL("RELATIVE",AB_package);
    gfi_time_stamp_format_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_time_stamp_format_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_time_stamp_format,
	    gfi_time_stamp_format_evaluation_setter_1);
    gfi_time_stamp_format_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_time_stamp_format_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_time_stamp_format,
	    gfi_time_stamp_format_evaluation_getter_1);
    Qgfi_output_file_update_frequency = 
	    STATIC_SYMBOL("GFI-OUTPUT-FILE-UPDATE-FREQUENCY",AB_package);
    list_constant_164 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_5,Qinteger,list_constant_108);
    set_property_value_function(get_symbol_properties_function(Qgfi_output_file_update_frequency),
	    Qtype_specification_simple_expansion,list_constant_164);
    Qwhen_variables_receive_values = 
	    STATIC_SYMBOL("WHEN-VARIABLES-RECEIVE-VALUES",AB_package);
    Qwhen_activated = STATIC_SYMBOL("WHEN-ACTIVATED",AB_package);
    Qwhen_activated_without_interruption = 
	    STATIC_SYMBOL("WHEN-ACTIVATED-WITHOUT-INTERRUPTION",AB_package);
    list_constant_165 = STATIC_LIST((SI_Long)4L,Qmember,
	    Qwhen_variables_receive_values,Qwhen_activated,
	    Qwhen_activated_without_interruption);
    list_constant_51 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_5,
	    Qinteger,list_constant_165);
    define_type_specification_explicit_complex_type(Qgfi_output_file_update_frequency,
	    list_constant_51);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qgfi_output_file_update_frequency);
    Qwrite_interval = STATIC_SYMBOL("WRITE-INTERVAL",AB_package);
    Qwhen_received_value = STATIC_SYMBOL("WHEN-RECEIVED-VALUE",AB_package);
    Qoutput_one_shot_when_activated = 
	    STATIC_SYMBOL("OUTPUT-ONE-SHOT-WHEN-ACTIVATED",AB_package);
    Qoutput_one_shot_when_activated_without_interruption = 
	    STATIC_SYMBOL("OUTPUT-ONE-SHOT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION",
	    AB_package);
    gfi_output_file_update_frequency_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_output_file_update_frequency_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_output_file_update_frequency,
	    gfi_output_file_update_frequency_evaluation_setter_1);
    gfi_output_file_update_frequency_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_output_file_update_frequency_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_output_file_update_frequency,
	    gfi_output_file_update_frequency_evaluation_getter_1);
    Qattributes_which_identify_a_network_item_reference = 
	    STATIC_SYMBOL("ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qattributes_which_identify_a_network_item_reference),
	    Qtype_specification_simple_expansion,list_constant_135);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_172 = STATIC_CONS(Qab_class,list_constant_92);
    Qclass_identifying_attributes = 
	    STATIC_SYMBOL("CLASS-IDENTIFYING-ATTRIBUTES",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    list_constant_166 = STATIC_CONS(Qattribute,list_constant_92);
    Qname_for_network = STATIC_SYMBOL("NAME-FOR-NETWORK",AB_package);
    list_constant_167 = STATIC_CONS(Qname_for_network,list_constant_92);
    list_constant_168 = STATIC_LIST((SI_Long)2L,list_constant_166,
	    list_constant_167);
    list_constant_169 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_168);
    list_constant_170 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_169);
    list_constant_171 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_170,list_constant_151);
    list_constant_173 = STATIC_LIST((SI_Long)2L,
	    Qclass_identifying_attributes,list_constant_171);
    list_constant_174 = STATIC_LIST((SI_Long)2L,list_constant_172,
	    list_constant_173);
    list_constant_175 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_174);
    list_constant_176 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_175);
    list_constant_177 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_176,list_constant_151);
    list_constant_53 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_177);
    define_type_specification_explicit_complex_type(Qattributes_which_identify_a_network_item_reference,
	    list_constant_53);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qattributes_which_identify_a_network_item_reference);
    string_constant_80 = 
	    STATIC_STRING("Incorrect - empty configuration parameters for interface");
    attributes_which_identify_a_network_item_reference_evaluation_setter_1 
	    = 
	    STATIC_FUNCTION(attributes_which_identify_a_network_item_reference_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qattributes_which_identify_a_network_item_reference,
	    attributes_which_identify_a_network_item_reference_evaluation_setter_1);
    attributes_which_identify_a_network_item_reference_evaluation_getter_1 
	    = 
	    STATIC_FUNCTION(attributes_which_identify_a_network_item_reference_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qattributes_which_identify_a_network_item_reference,
	    attributes_which_identify_a_network_item_reference_evaluation_getter_1);
    Qoptions_for_item_reference = 
	    STATIC_SYMBOL("OPTIONS-FOR-ITEM-REFERENCE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qoptions_for_item_reference),
	    Qtype_specification_simple_expansion,list_constant_140);
    Qhome = STATIC_SYMBOL("HOME",AB_package);
    Qconvert_home_to_local = STATIC_SYMBOL("CONVERT-HOME-TO-LOCAL",AB_package);
    Qno_conversion = STATIC_SYMBOL("NO-CONVERSION",AB_package);
    list_constant_178 = STATIC_CONS(Qno_conversion,Qnil);
    list_constant_179 = STATIC_LIST_STAR((SI_Long)3L,Qmember,
	    Qconvert_home_to_local,list_constant_178);
    list_constant_184 = STATIC_LIST((SI_Long)2L,Qhome,list_constant_179);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qname_includes_home = STATIC_SYMBOL("NAME-INCLUDES-HOME",AB_package);
    Qname_includes_home_unless_local = 
	    STATIC_SYMBOL("NAME-INCLUDES-HOME-UNLESS-LOCAL",AB_package);
    list_constant_180 = STATIC_LIST_STAR((SI_Long)4L,Qmember,
	    Qname_includes_home,Qname_includes_home_unless_local,
	    list_constant_178);
    list_constant_185 = STATIC_LIST((SI_Long)2L,Qname,list_constant_180);
    Qremote_class_prefix = STATIC_SYMBOL("REMOTE-CLASS-PREFIX",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_181 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,Qtext);
    list_constant_186 = STATIC_LIST((SI_Long)2L,Qremote_class_prefix,
	    list_constant_181);
    Qdefault_remote_class = STATIC_SYMBOL("DEFAULT-REMOTE-CLASS",AB_package);
    list_constant_187 = STATIC_LIST((SI_Long)2L,Qdefault_remote_class,
	    list_constant_44);
    Qreference_lookup = STATIC_SYMBOL("REFERENCE-LOOKUP",AB_package);
    Qlook_up_references = STATIC_SYMBOL("LOOK-UP-REFERENCES",AB_package);
    Qdo_not_look_up_references = STATIC_SYMBOL("DO-NOT-LOOK-UP-REFERENCES",
	    AB_package);
    list_constant_182 = STATIC_LIST((SI_Long)3L,Qmember,
	    Qlook_up_references,Qdo_not_look_up_references);
    list_constant_188 = STATIC_LIST((SI_Long)2L,Qreference_lookup,
	    list_constant_182);
    Qreference_creation = STATIC_SYMBOL("REFERENCE-CREATION",AB_package);
    Qcreate_references = STATIC_SYMBOL("CREATE-REFERENCES",AB_package);
    Qdo_not_create_references = STATIC_SYMBOL("DO-NOT-CREATE-REFERENCES",
	    AB_package);
    list_constant_183 = STATIC_LIST((SI_Long)3L,Qmember,Qcreate_references,
	    Qdo_not_create_references);
    list_constant_189 = STATIC_LIST((SI_Long)2L,Qreference_creation,
	    list_constant_183);
    list_constant_190 = STATIC_LIST((SI_Long)6L,list_constant_184,
	    list_constant_185,list_constant_186,list_constant_187,
	    list_constant_188,list_constant_189);
    list_constant_191 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_190);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_191);
    define_type_specification_explicit_complex_type(Qoptions_for_item_reference,
	    list_constant_55);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qoptions_for_item_reference);
    Qunless_local = STATIC_SYMBOL("UNLESS-LOCAL",AB_package);
    Qadd_home_to_name = STATIC_SYMBOL("ADD-HOME-TO-NAME",AB_package);
    Qunsupplied = STATIC_SYMBOL("UNSUPPLIED",AB_package);
    Qnon_local_item_class = STATIC_SYMBOL("NON-LOCAL-ITEM-CLASS",AB_package);
    options_for_item_reference_evaluation_setter_1 = 
	    STATIC_FUNCTION(options_for_item_reference_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qoptions_for_item_reference,
	    options_for_item_reference_evaluation_setter_1);
    options_for_item_reference_evaluation_getter_1 = 
	    STATIC_FUNCTION(options_for_item_reference_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qoptions_for_item_reference,
	    options_for_item_reference_evaluation_getter_1);
    Qgsi_variable_grouping_specification = 
	    STATIC_SYMBOL("GSI-VARIABLE-GROUPING-SPECIFICATION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgsi_variable_grouping_specification),
	    Qtype_specification_simple_expansion,list_constant_135);
    list_constant_192 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qsymbol,
	    list_constant_151);
    list_constant_57 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_192);
    define_type_specification_explicit_complex_type(Qgsi_variable_grouping_specification,
	    list_constant_57);
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qgsi_variable_grouping_specification);
    Qno_grouping = STATIC_SYMBOL("NO-GROUPING",AB_package);
    gsi_variable_grouping_specification_evaluation_setter_1 = 
	    STATIC_FUNCTION(gsi_variable_grouping_specification_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgsi_variable_grouping_specification,
	    gsi_variable_grouping_specification_evaluation_setter_1);
    gsi_variable_grouping_specification_evaluation_getter_1 = 
	    STATIC_FUNCTION(gsi_variable_grouping_specification_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgsi_variable_grouping_specification,
	    gsi_variable_grouping_specification_evaluation_getter_1);
    Qwhen_to_show_value = STATIC_SYMBOL("WHEN-TO-SHOW-VALUE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qwhen_to_show_value),
	    Qtype_specification_simple_expansion,Qnil);
    Qonly_while_sliding = STATIC_SYMBOL("ONLY-WHILE-SLIDING",AB_package);
    Qalways = STATIC_SYMBOL("ALWAYS",AB_package);
    list_constant_193 = STATIC_CONS(Qnever,Qnil);
    list_constant_59 = STATIC_LIST_STAR((SI_Long)4L,Qmember,
	    Qonly_while_sliding,Qalways,list_constant_193);
    define_type_specification_explicit_complex_type(Qwhen_to_show_value,
	    list_constant_59);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhen_to_show_value);
    Qwhile_sliding = STATIC_SYMBOL("WHILE-SLIDING",AB_package);
    when_to_show_value_evaluation_setter_1 = 
	    STATIC_FUNCTION(when_to_show_value_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qwhen_to_show_value,
	    when_to_show_value_evaluation_setter_1);
    when_to_show_value_evaluation_getter_1 = 
	    STATIC_FUNCTION(when_to_show_value_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qwhen_to_show_value,
	    when_to_show_value_evaluation_getter_1);
    Qgfi_input_variables_update_mode = 
	    STATIC_SYMBOL("GFI-INPUT-VARIABLES-UPDATE-MODE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgfi_input_variables_update_mode),
	    Qtype_specification_simple_expansion,list_constant_162);
    Qasynchronous_input = STATIC_SYMBOL("ASYNCHRONOUS-INPUT",AB_package);
    Qasynchronous_input_ignoring_the_data_server = 
	    STATIC_SYMBOL("ASYNCHRONOUS-INPUT-IGNORING-THE-DATA-SERVER",
	    AB_package);
    Qinput_on_request_preserving_time_stamps = 
	    STATIC_SYMBOL("INPUT-ON-REQUEST-PRESERVING-TIME-STAMPS",
	    AB_package);
    Qinput_on_request_sample_and_hold = 
	    STATIC_SYMBOL("INPUT-ON-REQUEST-SAMPLE-AND-HOLD",AB_package);
    Qinput_when_activated = STATIC_SYMBOL("INPUT-WHEN-ACTIVATED",AB_package);
    Qinput_when_activated_without_interruption = 
	    STATIC_SYMBOL("INPUT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION",
	    AB_package);
    list_constant_194 = STATIC_LIST((SI_Long)7L,Qmember,
	    Qasynchronous_input,
	    Qasynchronous_input_ignoring_the_data_server,
	    Qinput_on_request_preserving_time_stamps,
	    Qinput_on_request_sample_and_hold,Qinput_when_activated,
	    Qinput_when_activated_without_interruption);
    list_constant_61 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_194);
    define_type_specification_explicit_complex_type(Qgfi_input_variables_update_mode,
	    list_constant_61);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qgfi_input_variables_update_mode);
    Qasynchronous = STATIC_SYMBOL("ASYNCHRONOUS",AB_package);
    Qasynchronous_ignoring_data_server = 
	    STATIC_SYMBOL("ASYNCHRONOUS-IGNORING-DATA-SERVER",AB_package);
    Qon_request = STATIC_SYMBOL("ON-REQUEST",AB_package);
    Qon_request_sample_and_hold = 
	    STATIC_SYMBOL("ON-REQUEST-SAMPLE-AND-HOLD",AB_package);
    Qinput_one_shot_when_activated = 
	    STATIC_SYMBOL("INPUT-ONE-SHOT-WHEN-ACTIVATED",AB_package);
    Qinput_one_shot_when_activated_without_interruption = 
	    STATIC_SYMBOL("INPUT-ONE-SHOT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION",
	    AB_package);
    gfi_input_variables_update_mode_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_input_variables_update_mode_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_input_variables_update_mode,
	    gfi_input_variables_update_mode_evaluation_setter_1);
    gfi_input_variables_update_mode_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_input_variables_update_mode_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_input_variables_update_mode,
	    gfi_input_variables_update_mode_evaluation_getter_1);
    Qstubs_for_class = STATIC_SYMBOL("STUBS-FOR-CLASS",AB_package);
    Qconnections_qm = STATIC_SYMBOL("CONNECTIONS\?",AB_package);
    Qattribute_displays_for_class = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAYS-FOR-CLASS",AB_package);
    Qattribute_displays_spec_qm = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAYS-SPEC\?",AB_package);
    Qcross_section_pattern_for_class = 
	    STATIC_SYMBOL("CROSS-SECTION-PATTERN-FOR-CLASS",AB_package);
    Qcell_annotations = STATIC_SYMBOL("CELL-ANNOTATIONS",AB_package);
    Qtable_dimensions = STATIC_SYMBOL("TABLE-DIMENSIONS",AB_package);
    Qstub_length_for_class = STATIC_SYMBOL("STUB-LENGTH-FOR-CLASS",AB_package);
    Qjunction_block_for_class = STATIC_SYMBOL("JUNCTION-BLOCK-FOR-CLASS",
	    AB_package);
    Qjunction_class = STATIC_SYMBOL("JUNCTION-CLASS",AB_package);
    Qdefault_message_properties_for_class = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES-FOR-CLASS",AB_package);
    Qmessage_properties = STATIC_SYMBOL("MESSAGE-PROPERTIES",AB_package);
    Qdefault_text_box_colors_for_class = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-COLORS-FOR-CLASS",AB_package);
    Qtext_cell_colors = STATIC_SYMBOL("TEXT-CELL-COLORS",AB_package);
    Qinitial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qcondition_for_using_user_menu_choice_qm = 
	    STATIC_SYMBOL("CONDITION-FOR-USING-USER-MENU-CHOICE\?",AB_package);
    Quser_menu_choice_expression_initialization = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-EXPRESSION-INITIALIZATION",
	    AB_package);
    Qshow_simulated_values = STATIC_SYMBOL("SHOW-SIMULATED-VALUES",AB_package);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qdigital_clock = STATIC_SYMBOL("DIGITAL-CLOCK",AB_package);
    Qdisplay_update_interval = STATIC_SYMBOL("DISPLAY-UPDATE-INTERVAL",
	    AB_package);
    Qdisplay_wait_interval = STATIC_SYMBOL("DISPLAY-WAIT-INTERVAL",AB_package);
    Qdisplay_update_priority = STATIC_SYMBOL("DISPLAY-UPDATE-PRIORITY",
	    AB_package);
    Qdisplay_format = STATIC_SYMBOL("DISPLAY-FORMAT",AB_package);
    Qclass_of_procedure_invocation = 
	    STATIC_SYMBOL("CLASS-OF-PROCEDURE-INVOCATION",AB_package);
    Qdefault_procedure_priority = 
	    STATIC_SYMBOL("DEFAULT-PROCEDURE-PRIORITY",AB_package);
    Quninterrupted_procedure_execution_limit = 
	    STATIC_SYMBOL("UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT",
	    AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    Qattribute_displays = STATIC_SYMBOL("ATTRIBUTE-DISPLAYS",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qframe_style_definition = STATIC_SYMBOL("FRAME-STYLE-DEFINITION",
	    AB_package);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    Qtabular_function = STATIC_SYMBOL("TABULAR-FUNCTION",AB_package);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    Qmodel_definition = STATIC_SYMBOL("MODEL-DEFINITION",AB_package);
    Qexternal_simulation_definition = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION",AB_package);
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    Qcheck_box = STATIC_SYMBOL("CHECK-BOX",AB_package);
    Qradio_button = STATIC_SYMBOL("RADIO-BUTTON",AB_package);
    Qslider = STATIC_SYMBOL("SLIDER",AB_package);
    Qnetwork_wire = STATIC_SYMBOL("NETWORK-WIRE",AB_package);
    Qvariable_frame_flags = STATIC_SYMBOL("VARIABLE-FRAME-FLAGS",AB_package);
    Qparameter_frame_flags = STATIC_SYMBOL("PARAMETER-FRAME-FLAGS",AB_package);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qdefault_overrides_for_class_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-CLASS-DEFINITIONS",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qdefault_overrides_for_class_definitions),
	    Qtype_specification_simple_expansion,list_constant_135);
    Quser_attribute_name = STATIC_SYMBOL("USER-ATTRIBUTE-NAME",AB_package);
    list_constant_200 = STATIC_CONS(Quser_attribute_name,list_constant_92);
    Qinitialization = STATIC_SYMBOL("INITIALIZATION",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    list_constant_195 = STATIC_LIST((SI_Long)2L,Qinitial_value,Qdatum);
    Qinitial_item_class = STATIC_SYMBOL("INITIAL-ITEM-CLASS",AB_package);
    list_constant_196 = STATIC_CONS(Qinitial_item_class,list_constant_92);
    Qinitial_type = STATIC_SYMBOL("INITIAL-TYPE",AB_package);
    list_constant_197 = STATIC_CONS(Qinitial_type,list_constant_92);
    list_constant_198 = STATIC_LIST((SI_Long)3L,list_constant_195,
	    list_constant_196,list_constant_197);
    list_constant_199 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_198);
    list_constant_201 = STATIC_LIST((SI_Long)2L,Qinitialization,
	    list_constant_199);
    list_constant_202 = STATIC_LIST((SI_Long)2L,list_constant_200,
	    list_constant_201);
    list_constant_203 = STATIC_LIST((SI_Long)2L,Qand,Quser_attribute_name);
    list_constant_267 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_202,list_constant_203);
    Qsystem_attribute_designation = 
	    STATIC_SYMBOL("SYSTEM-ATTRIBUTE-DESIGNATION",AB_package);
    list_constant_263 = STATIC_CONS(Qsystem_attribute_designation,
	    list_constant_92);
    Qchart_style = STATIC_SYMBOL("CHART-STYLE",AB_package);
    list_constant_239 = STATIC_LIST((SI_Long)2L,Qnamed,Qchart_style);
    list_constant_240 = STATIC_LIST((SI_Long)2L,Qnamed,Qtable_dimensions);
    Qcell_format_or_none = STATIC_SYMBOL("CELL-FORMAT-OR-NONE",AB_package);
    list_constant_241 = STATIC_LIST((SI_Long)2L,Qnamed,Qcell_format_or_none);
    Qcomputation_style_or_none = STATIC_SYMBOL("COMPUTATION-STYLE-OR-NONE",
	    AB_package);
    list_constant_242 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qcomputation_style_or_none);
    Quser_instantiable_kb_class_qm = 
	    STATIC_SYMBOL("USER-INSTANTIABLE-KB-CLASS\?",AB_package);
    list_constant_243 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Quser_instantiable_kb_class_qm);
    Qoneness_type = STATIC_SYMBOL("ONENESS-TYPE",AB_package);
    list_constant_244 = STATIC_LIST((SI_Long)2L,Qnamed,Qoneness_type);
    Qrelation_yes_or_no_qm = STATIC_SYMBOL("RELATION-YES-OR-NO\?",AB_package);
    list_constant_245 = STATIC_LIST((SI_Long)2L,Qnamed,Qrelation_yes_or_no_qm);
    Qframe_description = STATIC_SYMBOL("FRAME-DESCRIPTION",AB_package);
    list_constant_246 = STATIC_LIST((SI_Long)2L,Qnamed,Qframe_description);
    Qfocal_classes = STATIC_SYMBOL("FOCAL-CLASSES",AB_package);
    list_constant_247 = STATIC_LIST((SI_Long)2L,Qnamed,Qfocal_classes);
    Qlist_of_item_and_datum_constants_qm = 
	    STATIC_SYMBOL("LIST-OF-ITEM-AND-DATUM-CONSTANTS\?",AB_package);
    list_constant_248 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qlist_of_item_and_datum_constants_qm);
    Qsimulation_time_increment_qm = 
	    STATIC_SYMBOL("SIMULATION-TIME-INCREMENT\?",AB_package);
    list_constant_249 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qsimulation_time_increment_qm);
    Qfocal_objects = STATIC_SYMBOL("FOCAL-OBJECTS",AB_package);
    list_constant_250 = STATIC_LIST((SI_Long)2L,Qnamed,Qfocal_objects);
    Qcategories = STATIC_SYMBOL("CATEGORIES",AB_package);
    list_constant_251 = STATIC_LIST((SI_Long)2L,Qnamed,Qcategories);
    Qrelation_name_qm = STATIC_SYMBOL("RELATION-NAME\?",AB_package);
    list_constant_252 = STATIC_LIST((SI_Long)2L,Qnamed,Qrelation_name_qm);
    Qlist_of_datum_constants = STATIC_SYMBOL("LIST-OF-DATUM-CONSTANTS",
	    AB_package);
    list_constant_253 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qlist_of_datum_constants);
    Qconstant_designation_list_qm = 
	    STATIC_SYMBOL("CONSTANT-DESIGNATION-LIST\?",AB_package);
    list_constant_254 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qconstant_designation_list_qm);
    Qquantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    list_constant_255 = STATIC_LIST((SI_Long)2L,Qnamed,Qquantity_list);
    Qinteger_list = STATIC_SYMBOL("INTEGER-LIST",AB_package);
    list_constant_256 = STATIC_LIST((SI_Long)2L,Qnamed,Qinteger_list);
    Qfloat_list = STATIC_SYMBOL("FLOAT-LIST",AB_package);
    list_constant_257 = STATIC_LIST((SI_Long)2L,Qnamed,Qfloat_list);
    Qsymbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    list_constant_258 = STATIC_LIST((SI_Long)2L,Qnamed,Qsymbol_list);
    Qwhole_string_list = STATIC_SYMBOL("WHOLE-STRING-LIST",AB_package);
    list_constant_259 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string_list);
    Qtruth_value_list = STATIC_SYMBOL("TRUTH-VALUE-LIST",AB_package);
    list_constant_260 = STATIC_LIST((SI_Long)2L,Qnamed,Qtruth_value_list);
    Qexecution_interval_qm_or_default = 
	    STATIC_SYMBOL("EXECUTION-INTERVAL\?-OR-DEFAULT",AB_package);
    list_constant_214 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qexecution_interval_qm_or_default);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    list_constant_215 = STATIC_LIST((SI_Long)2L,Qnamed,Qpriority);
    Qclass_of_procedure_invocation_qm = 
	    STATIC_SYMBOL("CLASS-OF-PROCEDURE-INVOCATION\?",AB_package);
    list_constant_216 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qclass_of_procedure_invocation_qm);
    list_constant_217 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtracing_and_breakpoints);
    list_constant_218 = STATIC_LIST((SI_Long)2L,Qnamed,Qtext_cell_colors);
    list_constant_219 = STATIC_LIST((SI_Long)2L,Qnamed,Qmessage_properties);
    Qframe_style_name_qm = STATIC_SYMBOL("FRAME-STYLE-NAME\?",AB_package);
    list_constant_220 = STATIC_LIST((SI_Long)2L,Qnamed,Qframe_style_name_qm);
    Qmodule_name_qm = STATIC_SYMBOL("MODULE-NAME\?",AB_package);
    list_constant_221 = STATIC_LIST((SI_Long)2L,Qnamed,Qmodule_name_qm);
    Qextant_color_or_metacolor = STATIC_SYMBOL("EXTANT-COLOR-OR-METACOLOR",
	    AB_package);
    list_constant_222 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qextant_color_or_metacolor);
    list_constant_223 = STATIC_LIST((SI_Long)2L,Qnamed,Qconnections_qm);
    list_constant_224 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qattribute_displays_spec_qm);
    list_constant_225 = STATIC_LIST((SI_Long)2L,Qnamed,Qattribute);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    list_constant_226 = STATIC_LIST((SI_Long)2L,Qnamed,Qg2_array_length);
    Qtruth_value_qm = STATIC_SYMBOL("TRUTH-VALUE\?",AB_package);
    list_constant_227 = STATIC_LIST((SI_Long)2L,Qnamed,Qtruth_value_qm);
    Qquantity_qm = STATIC_SYMBOL("QUANTITY\?",AB_package);
    list_constant_228 = STATIC_LIST((SI_Long)2L,Qnamed,Qquantity_qm);
    Qinitial_value_float_qm = STATIC_SYMBOL("INITIAL-VALUE-FLOAT\?",
	    AB_package);
    list_constant_229 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qinitial_value_float_qm);
    Qinitial_value_long_qm = STATIC_SYMBOL("INITIAL-VALUE-LONG\?",AB_package);
    list_constant_230 = STATIC_LIST((SI_Long)2L,Qnamed,Qinitial_value_long_qm);
    Qinitial_value_integer_qm = STATIC_SYMBOL("INITIAL-VALUE-INTEGER\?",
	    AB_package);
    list_constant_231 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qinitial_value_integer_qm);
    Qstandard_or_class_qualified_symbol_qm = 
	    STATIC_SYMBOL("STANDARD-OR-CLASS-QUALIFIED-SYMBOL\?",AB_package);
    list_constant_232 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qstandard_or_class_qualified_symbol_qm);
    Qwhole_string_qm = STATIC_SYMBOL("WHOLE-STRING\?",AB_package);
    list_constant_233 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string_qm);
    list_constant_234 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qpositive_quantity_interval_qm);
    list_constant_235 = STATIC_LIST((SI_Long)2L,Qnamed,Qvariable_frame_flags);
    list_constant_236 = STATIC_LIST((SI_Long)2L,Qnamed,Qparameter_frame_flags);
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    list_constant_237 = STATIC_LIST((SI_Long)2L,Qnamed,Qvalidity_interval);
    list_constant_204 = STATIC_LIST((SI_Long)2L,Qnamed,Qstub_length);
    list_constant_205 = STATIC_LIST((SI_Long)2L,Qnamed,Qjunction_class);
    list_constant_206 = STATIC_LIST((SI_Long)2L,Qnamed,Qyes_or_no);
    Qnumber_qm = STATIC_SYMBOL("NUMBER\?",AB_package);
    list_constant_207 = STATIC_LIST((SI_Long)2L,Qnamed,Qnumber_qm);
    Qdata_type = STATIC_SYMBOL("DATA-TYPE",AB_package);
    list_constant_208 = STATIC_LIST((SI_Long)2L,Qnamed,Qdata_type);
    Qquantitative_data_type = STATIC_SYMBOL("QUANTITATIVE-DATA-TYPE",
	    AB_package);
    list_constant_209 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qquantitative_data_type);
    Qhistory_specification = STATIC_SYMBOL("HISTORY-SPECIFICATION",AB_package);
    list_constant_210 = STATIC_LIST((SI_Long)2L,Qnamed,Qhistory_specification);
    list_constant_211 = STATIC_CONS(Qnamed,list_constant_92);
    list_constant_212 = STATIC_LIST((SI_Long)2L,Qnamed,Qab_class);
    Qnew_class = STATIC_SYMBOL("NEW-CLASS",AB_package);
    list_constant_213 = STATIC_LIST((SI_Long)2L,Qnamed,Qnew_class);
    list_constant_238 = STATIC_LIST((SI_Long)13L,list_constant_41,
	    list_constant_204,list_constant_205,list_constant_206,
	    list_constant_207,list_constant_45,list_constant_208,
	    list_constant_209,list_constant,list_constant_210,
	    list_constant_211,list_constant_212,list_constant_213);
    list_constant_261 = STATIC_LIST_STAR((SI_Long)32L,list_constant_16,
	    list_constant_13,list_constant_14,list_constant_9,
	    list_constant_214,list_constant_215,list_constant_216,
	    list_constant_217,list_constant_218,list_constant_219,
	    list_constant_220,list_constant_221,list_constant_29,
	    list_constant_222,list_constant_35,list_constant_223,
	    list_constant_224,list_constant_225,list_constant_226,
	    list_constant_43,list_constant_227,list_constant_228,
	    list_constant_229,list_constant_230,list_constant_231,
	    list_constant_232,list_constant_233,list_constant_234,
	    list_constant_235,list_constant_236,list_constant_237,
	    list_constant_238);
    list_constant_262 = STATIC_LIST_STAR((SI_Long)32L,Qab_or,
	    list_constant_239,list_constant_240,list_constant_241,
	    list_constant_242,list_constant_243,list_constant_244,
	    list_constant_245,list_constant_246,list_constant_247,
	    list_constant_248,list_constant_249,list_constant_250,
	    list_constant_251,list_constant_11,list_constant_58,
	    list_constant_56,list_constant_52,list_constant_50,
	    list_constant_48,list_constant_46,list_constant_60,
	    list_constant_252,list_constant_253,list_constant_254,
	    list_constant_255,list_constant_256,list_constant_257,
	    list_constant_258,list_constant_259,list_constant_260,
	    list_constant_261);
    list_constant_264 = STATIC_LIST((SI_Long)2L,Qinitialization,
	    list_constant_262);
    list_constant_265 = STATIC_LIST((SI_Long)2L,list_constant_263,
	    list_constant_264);
    list_constant_266 = STATIC_LIST((SI_Long)2L,Qand,
	    Qsystem_attribute_designation);
    list_constant_268 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_265,list_constant_266);
    list_constant_269 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_267,
	    list_constant_268);
    list_constant_270 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_269);
    list_constant_63 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_270);
    define_type_specification_explicit_complex_type(Qdefault_overrides_for_class_definitions,
	    list_constant_63);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdefault_overrides_for_class_definitions);
    string_constant_81 = 
	    STATIC_STRING("The class-definition must first have a defined set of direct ~\n                           superior classes.");
    string_constant_82 = 
	    STATIC_STRING("The inheritance for this class does not include an attribute named ~a.");
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Quser_defined = STATIC_SYMBOL("USER-DEFINED",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_simulation_subtable_with_specific_class_and_install = 
	    STATIC_SYMBOL("MAKE-SIMULATION-SUBTABLE-WITH-SPECIFIC-CLASS-AND-INSTALL",
	    AB_package);
    Qg2_array_element_type = STATIC_SYMBOL("G2-ARRAY-ELEMENT-TYPE",AB_package);
    Qitem_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    Qlist_type = STATIC_SYMBOL("LIST-TYPE",AB_package);
    Qitem_list = STATIC_SYMBOL("ITEM-LIST",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    string_constant_83 = 
	    STATIC_STRING("the attribute, ~NQ, is not concludable");
    default_overrides_for_class_definitions_evaluation_setter_1 = 
	    STATIC_FUNCTION(default_overrides_for_class_definitions_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdefault_overrides_for_class_definitions,
	    default_overrides_for_class_definitions_evaluation_setter_1);
    Quser_overridable = STATIC_SYMBOL("USER-OVERRIDABLE",AB_package);
    default_overrides_for_class_definitions_evaluation_getter_1 = 
	    STATIC_FUNCTION(default_overrides_for_class_definitions_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdefault_overrides_for_class_definitions,
	    default_overrides_for_class_definitions_evaluation_getter_1);
    Qdefault_overrides_for_object_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-OBJECT-DEFINITIONS",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qdefault_overrides_for_object_definitions),
	    Qtype_specification_simple_expansion,list_constant_135);
    list_constant_271 = STATIC_LIST((SI_Long)2L,Qnamed,Qtruth_value);
    list_constant_272 = STATIC_LIST((SI_Long)26L,Qab_or,list_constant_248,
	    list_constant_253,list_constant_254,list_constant_255,
	    list_constant_256,list_constant_257,list_constant_258,
	    list_constant_259,list_constant_260,list_constant_226,
	    list_constant_271,list_constant_228,list_constant_229,
	    list_constant_230,list_constant_231,list_constant_232,
	    list_constant_233,list_constant_234,list_constant_235,
	    list_constant_236,list_constant_237,list_constant_206,
	    list_constant_208,list_constant,list_constant_210);
    list_constant_273 = STATIC_LIST((SI_Long)2L,Qinitialization,
	    list_constant_272);
    list_constant_274 = STATIC_LIST((SI_Long)2L,list_constant_263,
	    list_constant_273);
    list_constant_275 = STATIC_CONS(list_constant_266,Qnil);
    list_constant_276 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_274,list_constant_275);
    list_constant_277 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_267,
	    list_constant_276);
    list_constant_278 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_277);
    list_constant_65 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_278);
    define_type_specification_explicit_complex_type(Qdefault_overrides_for_object_definitions,
	    list_constant_65);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdefault_overrides_for_object_definitions);
    Qmake_simulation_subtable_and_install = 
	    STATIC_SYMBOL("MAKE-SIMULATION-SUBTABLE-AND-INSTALL",AB_package);
    default_overrides_for_object_definitions_evaluation_setter_1 = 
	    STATIC_FUNCTION(default_overrides_for_object_definitions_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdefault_overrides_for_object_definitions,
	    default_overrides_for_object_definitions_evaluation_setter_1);
    Qsupply_simulation_subtable = 
	    STATIC_SYMBOL("SUPPLY-SIMULATION-SUBTABLE",AB_package);
    default_overrides_for_object_definitions_evaluation_getter_1 = 
	    STATIC_FUNCTION(default_overrides_for_object_definitions_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdefault_overrides_for_object_definitions,
	    default_overrides_for_object_definitions_evaluation_getter_1);
    Qdefault_overrides_for_message_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-MESSAGE-DEFINITIONS",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qdefault_overrides_for_message_definitions),
	    Qtype_specification_simple_expansion,list_constant_135);
    list_constant_279 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_267);
    list_constant_67 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_279);
    define_type_specification_explicit_complex_type(Qdefault_overrides_for_message_definitions,
	    list_constant_67);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdefault_overrides_for_message_definitions);
    default_overrides_for_message_definitions_evaluation_setter_1 = 
	    STATIC_FUNCTION(default_overrides_for_message_definitions_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdefault_overrides_for_message_definitions,
	    default_overrides_for_message_definitions_evaluation_setter_1);
    default_overrides_for_message_definitions_evaluation_getter_1 = 
	    STATIC_FUNCTION(default_overrides_for_message_definitions_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdefault_overrides_for_message_definitions,
	    default_overrides_for_message_definitions_evaluation_getter_1);
    Qdefault_overrides_for_connection_definitions = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-FOR-CONNECTION-DEFINITIONS",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qdefault_overrides_for_connection_definitions),
	    Qtype_specification_simple_expansion,list_constant_135);
    define_type_specification_explicit_complex_type(Qdefault_overrides_for_connection_definitions,
	    list_constant_67);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdefault_overrides_for_connection_definitions);
    default_overrides_for_connection_definitions_evaluation_setter_1 = 
	    STATIC_FUNCTION(default_overrides_for_connection_definitions_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdefault_overrides_for_connection_definitions,
	    default_overrides_for_connection_definitions_evaluation_setter_1);
    default_overrides_for_connection_definitions_evaluation_getter_1 = 
	    STATIC_FUNCTION(default_overrides_for_connection_definitions_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdefault_overrides_for_connection_definitions,
	    default_overrides_for_connection_definitions_evaluation_getter_1);
    Qplot_update_interval_spec = STATIC_SYMBOL("PLOT-UPDATE-INTERVAL-SPEC",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qplot_update_interval_spec),
	    Qtype_specification_simple_expansion,list_constant_6);
    Qupdate_interval = STATIC_SYMBOL("UPDATE-INTERVAL",AB_package);
    list_constant_280 = STATIC_LIST((SI_Long)2L,Qupdate_interval,
	    list_constant_16);
    Qgranularity = STATIC_SYMBOL("GRANULARITY",AB_package);
    list_constant_281 = STATIC_LIST((SI_Long)2L,Qgranularity,Qnumber);
    list_constant_282 = STATIC_LIST((SI_Long)2L,list_constant_280,
	    list_constant_281);
    list_constant_283 = STATIC_LIST((SI_Long)2L,Qand,Qupdate_interval);
    list_constant_70 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_282,list_constant_283);
    define_type_specification_explicit_complex_type(Qplot_update_interval_spec,
	    list_constant_70);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qplot_update_interval_spec);
    Qblock_3_dot_1415926 = STATIC_SYMBOL("BLOCK-3.1415926",AB_package);
    Qinterval_with_granularity = STATIC_SYMBOL("INTERVAL-WITH-GRANULARITY",
	    AB_package);
    plot_update_interval_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(plot_update_interval_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qplot_update_interval_spec,
	    plot_update_interval_spec_evaluation_setter_1);
    plot_update_interval_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(plot_update_interval_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qplot_update_interval_spec,
	    plot_update_interval_spec_evaluation_getter_1);
    Qpoint_visible_qm = STATIC_SYMBOL("POINT-VISIBLE\?",AB_package);
    Qmarkers_visible_qm = STATIC_SYMBOL("MARKERS-VISIBLE\?",AB_package);
    Qslot_component_alias = STATIC_SYMBOL("SLOT-COMPONENT-ALIAS",AB_package);
    mutate_global_property(Qpoint_visible_qm,Qmarkers_visible_qm,
	    Qslot_component_alias);
    Qslot_component_pretty_name = 
	    STATIC_SYMBOL("SLOT-COMPONENT-PRETTY-NAME",AB_package);
    Qpoint_format = STATIC_SYMBOL("POINT-FORMAT",AB_package);
    temp_2 = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarkers_visible_qm),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_visible_qm);
    mutate_global_property(Qmarkers_visible_qm,temp_2,
	    Qslot_component_pretty_name);
    Qpoint_color = STATIC_SYMBOL("POINT-COLOR",AB_package);
    Qmarker_color = STATIC_SYMBOL("MARKER-COLOR",AB_package);
    mutate_global_property(Qpoint_color,Qmarker_color,Qslot_component_alias);
    temp_2 = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarker_color),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_color);
    mutate_global_property(Qmarker_color,temp_2,Qslot_component_pretty_name);
    Qpoint_style = STATIC_SYMBOL("POINT-STYLE",AB_package);
    Qmarker_style = STATIC_SYMBOL("MARKER-STYLE",AB_package);
    mutate_global_property(Qpoint_style,Qmarker_style,Qslot_component_alias);
    temp_2 = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarker_style),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_style);
    mutate_global_property(Qmarker_style,temp_2,Qslot_component_pretty_name);
    Qpoint_frequency = STATIC_SYMBOL("POINT-FREQUENCY",AB_package);
    Qmarker_frequency = STATIC_SYMBOL("MARKER-FREQUENCY",AB_package);
    mutate_global_property(Qpoint_frequency,Qmarker_frequency,
	    Qslot_component_alias);
    temp_2 = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarker_frequency),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_frequency);
    mutate_global_property(Qmarker_frequency,temp_2,
	    Qslot_component_pretty_name);
    string_constant_84 = STATIC_STRING("multiple use of names");
    Qcompound_type_descriptor = STATIC_SYMBOL("COMPOUND-TYPE-DESCRIPTOR",
	    AB_package);
    Qsingle = STATIC_SYMBOL("SINGLE",AB_package);
    Qtrend_chart_point_formats_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC",AB_package);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_point_formats_grammar_spec),
	    Qtype_specification_simple_expansion,list_constant_134);
    Qnames = STATIC_SYMBOL("NAMES",AB_package);
    list_constant_284 = STATIC_CONS(list_constant_192,Qnil);
    list_constant_285 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_5,Qsymbol,list_constant_284);
    list_constant_290 = STATIC_LIST((SI_Long)2L,Qnames,list_constant_285);
    Qchart_element_uid = STATIC_SYMBOL("CHART-ELEMENT-UID",AB_package);
    list_constant_286 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_101);
    list_constant_291 = STATIC_LIST((SI_Long)2L,Qchart_element_uid,
	    list_constant_286);
    list_constant_292 = STATIC_LIST((SI_Long)2L,Qmarkers_visible_qm,
	    list_constant_206);
    list_constant_287 = STATIC_CONS(list_constant_146,Qnil);
    list_constant_293 = STATIC_CONS(Qmarker_color,list_constant_287);
    Q2d_plot_marker_shape = STATIC_SYMBOL("2D-PLOT-MARKER-SHAPE",AB_package);
    list_constant_288 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_plot_marker_shape);
    list_constant_294 = STATIC_LIST((SI_Long)2L,Qmarker_style,
	    list_constant_288);
    Q2d_plot_marker_frequency = STATIC_SYMBOL("2D-PLOT-MARKER-FREQUENCY",
	    AB_package);
    list_constant_289 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_plot_marker_frequency);
    list_constant_295 = STATIC_LIST((SI_Long)2L,Qmarker_frequency,
	    list_constant_289);
    list_constant_296 = STATIC_LIST((SI_Long)6L,list_constant_290,
	    list_constant_291,list_constant_292,list_constant_293,
	    list_constant_294,list_constant_295);
    list_constant_297 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_296);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_297,list_constant_151);
    define_type_specification_explicit_complex_type(Qtrend_chart_point_formats_grammar_spec,
	    list_constant_72);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_point_formats_grammar_spec);
    trend_chart_point_formats_grammar_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_point_formats_grammar_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_point_formats_grammar_spec,
	    trend_chart_point_formats_grammar_spec_evaluation_setter_1);
    trend_chart_point_formats_grammar_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_point_formats_grammar_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_point_formats_grammar_spec,
	    trend_chart_point_formats_grammar_spec_evaluation_getter_1);
    Qtrend_chart_connector_formats_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_connector_formats_grammar_spec),
	    Qtype_specification_simple_expansion,list_constant_134);
    Qconnectors_visible_qm = STATIC_SYMBOL("CONNECTORS-VISIBLE\?",AB_package);
    list_constant_298 = STATIC_CONS(list_constant_206,Qnil);
    list_constant_301 = STATIC_CONS(Qconnectors_visible_qm,list_constant_298);
    Qconnector_line_color = STATIC_SYMBOL("CONNECTOR-LINE-COLOR",AB_package);
    list_constant_302 = STATIC_CONS(Qconnector_line_color,list_constant_287);
    Qconnector_interpolation = STATIC_SYMBOL("CONNECTOR-INTERPOLATION",
	    AB_package);
    Q2d_line_style = STATIC_SYMBOL("2D-LINE-STYLE",AB_package);
    list_constant_299 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_line_style);
    list_constant_303 = STATIC_LIST((SI_Long)2L,Qconnector_interpolation,
	    list_constant_299);
    Qconnector_line_width = STATIC_SYMBOL("CONNECTOR-LINE-WIDTH",AB_package);
    list_constant_304 = STATIC_CONS(Qconnector_line_width,list_constant_101);
    Qconnector_shading_target = STATIC_SYMBOL("CONNECTOR-SHADING-TARGET",
	    AB_package);
    Q2d_shading_target_spec = STATIC_SYMBOL("2D-SHADING-TARGET-SPEC",
	    AB_package);
    list_constant_300 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_shading_target_spec);
    list_constant_305 = STATIC_LIST((SI_Long)2L,Qconnector_shading_target,
	    list_constant_300);
    list_constant_306 = STATIC_LIST((SI_Long)7L,list_constant_290,
	    list_constant_291,list_constant_301,list_constant_302,
	    list_constant_303,list_constant_304,list_constant_305);
    list_constant_307 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_306);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_307,list_constant_151);
    define_type_specification_explicit_complex_type(Qtrend_chart_connector_formats_grammar_spec,
	    list_constant_74);
    list_constant_73 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_connector_formats_grammar_spec);
    Qconnector_format = STATIC_SYMBOL("CONNECTOR-FORMAT",AB_package);
    trend_chart_connector_formats_grammar_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_connector_formats_grammar_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_connector_formats_grammar_spec,
	    trend_chart_connector_formats_grammar_spec_evaluation_setter_1);
    trend_chart_connector_formats_grammar_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_connector_formats_grammar_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_connector_formats_grammar_spec,
	    trend_chart_connector_formats_grammar_spec_evaluation_getter_1);
    Qtrend_chart_value_axes_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-VALUE-AXES-GRAMMAR-SPEC",AB_package);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_value_axes_grammar_spec),
	    Qtype_specification_simple_expansion,list_constant_134);
    Qvalue_axis_visible_qm = STATIC_SYMBOL("VALUE-AXIS-VISIBLE\?",AB_package);
    list_constant_317 = STATIC_CONS(Qvalue_axis_visible_qm,list_constant_298);
    Qvalue_axis_position = STATIC_SYMBOL("VALUE-AXIS-POSITION",AB_package);
    list_constant_308 = STATIC_LIST((SI_Long)2L,Qnamed,Qvalue_axis_position);
    list_constant_318 = STATIC_LIST((SI_Long)2L,Qvalue_axis_position,
	    list_constant_308);
    Qrange_mode = STATIC_SYMBOL("RANGE-MODE",AB_package);
    Q2d_range_mode = STATIC_SYMBOL("2D-RANGE-MODE",AB_package);
    list_constant_309 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_range_mode);
    list_constant_319 = STATIC_LIST((SI_Long)2L,Qrange_mode,list_constant_309);
    Qrange_bounds = STATIC_SYMBOL("RANGE-BOUNDS",AB_package);
    Q2d_value_axis_bounds_spec = STATIC_SYMBOL("2D-VALUE-AXIS-BOUNDS-SPEC",
	    AB_package);
    list_constant_310 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_value_axis_bounds_spec);
    list_constant_320 = STATIC_LIST((SI_Long)2L,Qrange_bounds,
	    list_constant_310);
    Qrange_slack_percentage = STATIC_SYMBOL("RANGE-SLACK-PERCENTAGE",
	    AB_package);
    Qrange_slack_spec = STATIC_SYMBOL("RANGE-SLACK-SPEC",AB_package);
    list_constant_311 = STATIC_LIST((SI_Long)2L,Qnamed,Qrange_slack_spec);
    list_constant_321 = STATIC_LIST((SI_Long)2L,Qrange_slack_percentage,
	    list_constant_311);
    Qlabels_visible_qm = STATIC_SYMBOL("LABELS-VISIBLE\?",AB_package);
    list_constant_322 = STATIC_CONS(Qlabels_visible_qm,list_constant_298);
    Qlabel_color = STATIC_SYMBOL("LABEL-COLOR",AB_package);
    Q2d_tickmark_label_color = STATIC_SYMBOL("2D-TICKMARK-LABEL-COLOR",
	    AB_package);
    list_constant_312 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_tickmark_label_color);
    list_constant_323 = STATIC_LIST((SI_Long)2L,Qlabel_color,
	    list_constant_312);
    Qlabel_frequency = STATIC_SYMBOL("LABEL-FREQUENCY",AB_package);
    Q2d_value_axis_tickmark_frequency_spec = 
	    STATIC_SYMBOL("2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC",AB_package);
    list_constant_313 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_value_axis_tickmark_frequency_spec);
    list_constant_324 = STATIC_LIST((SI_Long)2L,Qlabel_frequency,
	    list_constant_313);
    Qshow_labels_as_percent_qm = STATIC_SYMBOL("SHOW-LABELS-AS-PERCENT\?",
	    AB_package);
    list_constant_325 = STATIC_CONS(Qshow_labels_as_percent_qm,
	    list_constant_298);
    Qsignificant_digits_for_labels = 
	    STATIC_SYMBOL("SIGNIFICANT-DIGITS-FOR-LABELS",AB_package);
    Qsignificant_digit_spec = STATIC_SYMBOL("SIGNIFICANT-DIGIT-SPEC",
	    AB_package);
    list_constant_314 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qsignificant_digit_spec);
    list_constant_326 = STATIC_LIST((SI_Long)2L,
	    Qsignificant_digits_for_labels,list_constant_314);
    Qgrid_lines_visible_qm = STATIC_SYMBOL("GRID-LINES-VISIBLE\?",AB_package);
    list_constant_327 = STATIC_CONS(Qgrid_lines_visible_qm,list_constant_298);
    Qgrid_line_color = STATIC_SYMBOL("GRID-LINE-COLOR",AB_package);
    list_constant_328 = STATIC_CONS(Qgrid_line_color,list_constant_287);
    Qgrid_lines_per_label = STATIC_SYMBOL("GRID-LINES-PER-LABEL",AB_package);
    Qgrid_line_ratio = STATIC_SYMBOL("GRID-LINE-RATIO",AB_package);
    list_constant_315 = STATIC_LIST((SI_Long)2L,Qnamed,Qgrid_line_ratio);
    list_constant_329 = STATIC_LIST((SI_Long)2L,Qgrid_lines_per_label,
	    list_constant_315);
    Qextra_grid_lines = STATIC_SYMBOL("EXTRA-GRID-LINES",AB_package);
    Qextra_value_grid_lines = STATIC_SYMBOL("EXTRA-VALUE-GRID-LINES",
	    AB_package);
    list_constant_316 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qextra_value_grid_lines);
    list_constant_330 = STATIC_LIST((SI_Long)2L,Qextra_grid_lines,
	    list_constant_316);
    Qbaseline_visible_qm = STATIC_SYMBOL("BASELINE-VISIBLE\?",AB_package);
    list_constant_331 = STATIC_CONS(Qbaseline_visible_qm,list_constant_298);
    Qbaseline_color = STATIC_SYMBOL("BASELINE-COLOR",AB_package);
    list_constant_332 = STATIC_CONS(Qbaseline_color,list_constant_287);
    list_constant_333 = STATIC_LIST((SI_Long)18L,list_constant_290,
	    list_constant_291,list_constant_317,list_constant_318,
	    list_constant_319,list_constant_320,list_constant_321,
	    list_constant_322,list_constant_323,list_constant_324,
	    list_constant_325,list_constant_326,list_constant_327,
	    list_constant_328,list_constant_329,list_constant_330,
	    list_constant_331,list_constant_332);
    list_constant_334 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_333);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_334,list_constant_151);
    define_type_specification_explicit_complex_type(Qtrend_chart_value_axes_grammar_spec,
	    list_constant_76);
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_value_axes_grammar_spec);
    Qvalue_axis = STATIC_SYMBOL("VALUE-AXIS",AB_package);
    trend_chart_value_axes_grammar_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_value_axes_grammar_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_value_axes_grammar_spec,
	    trend_chart_value_axes_grammar_spec_evaluation_setter_1);
    trend_chart_value_axes_grammar_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_value_axes_grammar_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_value_axes_grammar_spec,
	    trend_chart_value_axes_grammar_spec_evaluation_getter_1);
    Qtrend_chart_format_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-FORMAT-GRAMMAR-SPEC",AB_package);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_format_grammar_spec),
	    Qtype_specification_simple_expansion,list_constant_6);
    Qouter_border_visible_qm = STATIC_SYMBOL("OUTER-BORDER-VISIBLE\?",
	    AB_package);
    list_constant_338 = STATIC_CONS(Qouter_border_visible_qm,
	    list_constant_298);
    Qouter_border_color = STATIC_SYMBOL("OUTER-BORDER-COLOR",AB_package);
    list_constant_339 = STATIC_CONS(Qouter_border_color,list_constant_287);
    Qouter_background_color = STATIC_SYMBOL("OUTER-BACKGROUND-COLOR",
	    AB_package);
    list_constant_340 = STATIC_CONS(Qouter_background_color,list_constant_287);
    Qdata_window_border_visible_qm = 
	    STATIC_SYMBOL("DATA-WINDOW-BORDER-VISIBLE\?",AB_package);
    list_constant_341 = STATIC_CONS(Qdata_window_border_visible_qm,
	    list_constant_298);
    Qdata_window_border_color = STATIC_SYMBOL("DATA-WINDOW-BORDER-COLOR",
	    AB_package);
    list_constant_342 = STATIC_CONS(Qdata_window_border_color,
	    list_constant_287);
    Qdata_window_background_color = 
	    STATIC_SYMBOL("DATA-WINDOW-BACKGROUND-COLOR",AB_package);
    list_constant_343 = STATIC_CONS(Qdata_window_background_color,
	    list_constant_287);
    Qlegend_visible_qm = STATIC_SYMBOL("LEGEND-VISIBLE\?",AB_package);
    list_constant_344 = STATIC_CONS(Qlegend_visible_qm,list_constant_298);
    Qlegend_color = STATIC_SYMBOL("LEGEND-COLOR",AB_package);
    Qtrend_chart_legend_color_spec = 
	    STATIC_SYMBOL("TREND-CHART-LEGEND-COLOR-SPEC",AB_package);
    list_constant_335 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_legend_color_spec);
    list_constant_345 = STATIC_LIST((SI_Long)2L,Qlegend_color,
	    list_constant_335);
    Qlegend_position = STATIC_SYMBOL("LEGEND-POSITION",AB_package);
    Qtrend_chart_legend_position = 
	    STATIC_SYMBOL("TREND-CHART-LEGEND-POSITION",AB_package);
    list_constant_336 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_legend_position);
    list_constant_337 = STATIC_CONS(list_constant_336,Qnil);
    list_constant_346 = STATIC_CONS(Qlegend_position,list_constant_337);
    Qtitle_visible_qm = STATIC_SYMBOL("TITLE-VISIBLE\?",AB_package);
    list_constant_347 = STATIC_CONS(Qtitle_visible_qm,list_constant_298);
    Qtitle_color = STATIC_SYMBOL("TITLE-COLOR",AB_package);
    list_constant_348 = STATIC_CONS(Qtitle_color,list_constant_287);
    Qtitle_position = STATIC_SYMBOL("TITLE-POSITION",AB_package);
    list_constant_349 = STATIC_CONS(Qtitle_position,list_constant_337);
    list_constant_350 = STATIC_LIST((SI_Long)12L,list_constant_338,
	    list_constant_339,list_constant_340,list_constant_341,
	    list_constant_342,list_constant_343,list_constant_344,
	    list_constant_345,list_constant_346,list_constant_347,
	    list_constant_348,list_constant_349);
    list_constant_78 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_350);
    define_type_specification_explicit_complex_type(Qtrend_chart_format_grammar_spec,
	    list_constant_78);
    list_constant_77 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_format_grammar_spec);
    Qtrend_chart_format = STATIC_SYMBOL("TREND-CHART-FORMAT",AB_package);
    trend_chart_format_grammar_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_format_grammar_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_format_grammar_spec,
	    trend_chart_format_grammar_spec_evaluation_setter_1);
    trend_chart_format_grammar_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_format_grammar_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_format_grammar_spec,
	    trend_chart_format_grammar_spec_evaluation_getter_1);
    Qtrend_chart_time_axis_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-TIME-AXIS-GRAMMAR-SPEC",AB_package);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_time_axis_grammar_spec),
	    Qtype_specification_simple_expansion,list_constant_6);
    Qdata_window_time_span = STATIC_SYMBOL("DATA-WINDOW-TIME-SPAN",AB_package);
    Q2d_time_span_spec = STATIC_SYMBOL("2D-TIME-SPAN-SPEC",AB_package);
    list_constant_351 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_time_span_spec);
    list_constant_359 = STATIC_LIST((SI_Long)2L,Qdata_window_time_span,
	    list_constant_351);
    Qtotal_time_span = STATIC_SYMBOL("TOTAL-TIME-SPAN",AB_package);
    Q2d_total_time_span_spec = STATIC_SYMBOL("2D-TOTAL-TIME-SPAN-SPEC",
	    AB_package);
    list_constant_352 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_total_time_span_spec);
    list_constant_360 = STATIC_LIST((SI_Long)2L,Qtotal_time_span,
	    list_constant_352);
    Qend_time = STATIC_SYMBOL("END-TIME",AB_package);
    Q2d_end_time_spec = STATIC_SYMBOL("2D-END-TIME-SPEC",AB_package);
    list_constant_353 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_end_time_spec);
    list_constant_361 = STATIC_LIST((SI_Long)2L,Qend_time,list_constant_353);
    list_constant_354 = STATIC_CONS(list_constant_16,Qnil);
    list_constant_362 = STATIC_CONS(Qdisplay_update_interval,
	    list_constant_354);
    Qjump_scroll_qm = STATIC_SYMBOL("JUMP-SCROLL\?",AB_package);
    list_constant_363 = STATIC_CONS(Qjump_scroll_qm,list_constant_298);
    Qjump_scroll_interval = STATIC_SYMBOL("JUMP-SCROLL-INTERVAL",AB_package);
    Qtrend_chart_scroll_interval = 
	    STATIC_SYMBOL("TREND-CHART-SCROLL-INTERVAL",AB_package);
    list_constant_355 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_scroll_interval);
    list_constant_364 = STATIC_LIST((SI_Long)2L,Qjump_scroll_interval,
	    list_constant_355);
    Qabsolute_labels_visible_qm = 
	    STATIC_SYMBOL("ABSOLUTE-LABELS-VISIBLE\?",AB_package);
    list_constant_365 = STATIC_CONS(Qabsolute_labels_visible_qm,
	    list_constant_298);
    Qrelative_labels_visible_qm = 
	    STATIC_SYMBOL("RELATIVE-LABELS-VISIBLE\?",AB_package);
    list_constant_366 = STATIC_CONS(Qrelative_labels_visible_qm,
	    list_constant_298);
    Q2d_time_axis_tickmark_frequency_spec = 
	    STATIC_SYMBOL("2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC",AB_package);
    list_constant_356 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_time_axis_tickmark_frequency_spec);
    list_constant_367 = STATIC_LIST((SI_Long)2L,Qlabel_frequency,
	    list_constant_356);
    Qlabel_alignment = STATIC_SYMBOL("LABEL-ALIGNMENT",AB_package);
    Qtime_axis_label_alignment = STATIC_SYMBOL("TIME-AXIS-LABEL-ALIGNMENT",
	    AB_package);
    list_constant_357 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtime_axis_label_alignment);
    list_constant_368 = STATIC_LIST((SI_Long)2L,Qlabel_alignment,
	    list_constant_357);
    Qtime_format = STATIC_SYMBOL("TIME-FORMAT",AB_package);
    Qtime_axis_label_format_spec = 
	    STATIC_SYMBOL("TIME-AXIS-LABEL-FORMAT-SPEC",AB_package);
    list_constant_358 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtime_axis_label_format_spec);
    list_constant_369 = STATIC_LIST((SI_Long)2L,Qtime_format,
	    list_constant_358);
    list_constant_370 = STATIC_CONS(Qlabel_color,list_constant_287);
    list_constant_371 = STATIC_LIST((SI_Long)2L,list_constant_331,
	    list_constant_332);
    list_constant_372 = STATIC_LIST_STAR((SI_Long)16L,list_constant_359,
	    list_constant_360,list_constant_361,list_constant_362,
	    list_constant_363,list_constant_364,list_constant_365,
	    list_constant_366,list_constant_367,list_constant_368,
	    list_constant_369,list_constant_370,list_constant_327,
	    list_constant_328,list_constant_329,list_constant_371);
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_372);
    define_type_specification_explicit_complex_type(Qtrend_chart_time_axis_grammar_spec,
	    list_constant_80);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_time_axis_grammar_spec);
    Qtime_axis = STATIC_SYMBOL("TIME-AXIS",AB_package);
    trend_chart_time_axis_grammar_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_time_axis_grammar_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_time_axis_grammar_spec,
	    trend_chart_time_axis_grammar_spec_evaluation_setter_1);
    trend_chart_time_axis_grammar_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_time_axis_grammar_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_time_axis_grammar_spec,
	    trend_chart_time_axis_grammar_spec_evaluation_getter_1);
    Qtrend_chart_plots_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-PLOTS-GRAMMAR-SPEC",AB_package);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_plots_grammar_spec),
	    Qtype_specification_simple_expansion,list_constant_134);
    Quse_local_history_qm = STATIC_SYMBOL("USE-LOCAL-HISTORY\?",AB_package);
    list_constant_376 = STATIC_CONS(Quse_local_history_qm,list_constant_298);
    Qvalue_axis_name_or_number = STATIC_SYMBOL("VALUE-AXIS-NAME-OR-NUMBER",
	    AB_package);
    Qcomponent_reference = STATIC_SYMBOL("COMPONENT-REFERENCE",AB_package);
    list_constant_373 = STATIC_LIST((SI_Long)2L,Qnamed,Qcomponent_reference);
    list_constant_374 = STATIC_CONS(list_constant_373,Qnil);
    list_constant_377 = STATIC_CONS(Qvalue_axis_name_or_number,
	    list_constant_374);
    Qpoint_format_name_or_number = 
	    STATIC_SYMBOL("POINT-FORMAT-NAME-OR-NUMBER",AB_package);
    list_constant_378 = STATIC_CONS(Qpoint_format_name_or_number,
	    list_constant_374);
    Qconnector_format_name_or_number = 
	    STATIC_SYMBOL("CONNECTOR-FORMAT-NAME-OR-NUMBER",AB_package);
    list_constant_379 = STATIC_CONS(Qconnector_format_name_or_number,
	    list_constant_374);
    list_constant_380 = STATIC_LIST((SI_Long)2L,Qupdate_interval,
	    list_constant_69);
    Qwait_interval = STATIC_SYMBOL("WAIT-INTERVAL",AB_package);
    list_constant_381 = STATIC_CONS(Qwait_interval,list_constant_354);
    Qupdate_priority = STATIC_SYMBOL("UPDATE-PRIORITY",AB_package);
    list_constant_382 = STATIC_LIST((SI_Long)2L,Qupdate_priority,
	    list_constant_215);
    Qmay_request_data_seeking_qm = 
	    STATIC_SYMBOL("MAY-REQUEST-DATA-SEEKING\?",AB_package);
    list_constant_383 = STATIC_CONS(Qmay_request_data_seeking_qm,
	    list_constant_298);
    Qmay_request_event_updates_qm = 
	    STATIC_SYMBOL("MAY-REQUEST-EVENT-UPDATES\?",AB_package);
    list_constant_384 = STATIC_CONS(Qmay_request_event_updates_qm,
	    list_constant_298);
    Quse_simulator_qm = STATIC_SYMBOL("USE-SIMULATOR\?",AB_package);
    list_constant_385 = STATIC_CONS(Quse_simulator_qm,list_constant_298);
    list_constant_386 = STATIC_LIST((SI_Long)2L,Qtracing_and_breakpoints,
	    list_constant_217);
    Qinclude_in_legend_qm = STATIC_SYMBOL("INCLUDE-IN-LEGEND\?",AB_package);
    list_constant_387 = STATIC_CONS(Qinclude_in_legend_qm,list_constant_298);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    list_constant_375 = STATIC_CONS(Qtext,Qnil);
    list_constant_388 = STATIC_CONS(Qexpression,list_constant_375);
    list_constant_389 = STATIC_LIST((SI_Long)15L,list_constant_290,
	    list_constant_291,list_constant_376,list_constant_377,
	    list_constant_378,list_constant_379,list_constant_380,
	    list_constant_381,list_constant_382,list_constant_383,
	    list_constant_384,list_constant_385,list_constant_386,
	    list_constant_387,list_constant_388);
    list_constant_390 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_389);
    list_constant_82 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_390,list_constant_151);
    define_type_specification_explicit_complex_type(Qtrend_chart_plots_grammar_spec,
	    list_constant_82);
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_plots_grammar_spec);
    Qplot = STATIC_SYMBOL("PLOT",AB_package);
    trend_chart_plots_grammar_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_plots_grammar_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_plots_grammar_spec,
	    trend_chart_plots_grammar_spec_evaluation_setter_1);
    trend_chart_plots_grammar_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_plots_grammar_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_plots_grammar_spec,
	    trend_chart_plots_grammar_spec_evaluation_getter_1);
    Qcategory_committer_function = 
	    STATIC_SYMBOL("CATEGORY-COMMITTER-FUNCTION",AB_package);
    Qplot_expression = STATIC_SYMBOL("PLOT-EXPRESSION",AB_package);
    trend_chart_plots_grammar_spec_evaluation_committer_1 = 
	    STATIC_FUNCTION(trend_chart_plots_grammar_spec_evaluation_committer,
	    NIL,FALSE,3,3);
    temp = get_symbol_properties_function(Qtrend_chart_plots_grammar_spec);
    set_property_value_function(temp,Qcategory_committer_function,
	    trend_chart_plots_grammar_spec_evaluation_committer_1);
    Qworkspace_title_bar_text = STATIC_SYMBOL("WORKSPACE-TITLE-BAR-TEXT",
	    AB_package);
    Qcompile_workspace_title_bar_text_for_slot = 
	    STATIC_SYMBOL("COMPILE-WORKSPACE-TITLE-BAR-TEXT-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_workspace_title_bar_text_for_slot,
	    STATIC_FUNCTION(compile_workspace_title_bar_text_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qworkspace_title_bar_text,
	    SYMBOL_FUNCTION(Qcompile_workspace_title_bar_text_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qworkspace_title_bar_text,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_173 = 
	    STATIC_STRING("1t1o833cy1m9k83Py09l1m833cy83-tOy1m83-tOy83-pUy1m83-tOy83-Nly1m83-pUy83-Uy1n83-pUy1m1m9k9m1m9k83-Gy83-Gy1n83-pUy1n1m9k9m1m9k83*J");
    string_constant_174 = 
	    STATIC_STRING("y1m9k83-Xgy83-rwy1n83-Nly1r1m9k9m1m9k83=hy1m9k8312y1m9k83=by1m9k83vy1m9k83XHy83-pUy1m83=hyr1n83-Nly1m1m9k9m1m9k83=hy83=hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnil_function);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_173,
	    string_constant_174)));
    string_constant_85 = STATIC_STRING(" if any, otherwise ");
    Qwrite_workspace_title_bar_text_from_slot = 
	    STATIC_SYMBOL("WRITE-WORKSPACE-TITLE-BAR-TEXT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_workspace_title_bar_text_from_slot,
	    STATIC_FUNCTION(write_workspace_title_bar_text_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qworkspace_title_bar_text,
	    SYMBOL_FUNCTION(Qwrite_workspace_title_bar_text_from_slot),
	    Qslot_value_writer);
    string_constant_86 = STATIC_STRING("the name");
    string_constant_87 = STATIC_STRING("the class");
    Qtable_header = STATIC_SYMBOL("TABLE-HEADER",AB_package);
    string_constant_88 = STATIC_STRING("the table header");
    Qtitle_bar_text = STATIC_SYMBOL("TITLE-BAR-TEXT",AB_package);
    Qput_title_bar_text = STATIC_SYMBOL("PUT-TITLE-BAR-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_title_bar_text,
	    STATIC_FUNCTION(put_title_bar_text,NIL,FALSE,3,3));
    mutate_global_property(Qtitle_bar_text,
	    SYMBOL_FUNCTION(Qput_title_bar_text),Qslot_putter);
    list_constant_391 = STATIC_LIST((SI_Long)5L,Qab_or,Qsymbol,Qtext,
	    list_constant_134,list_constant_5);
    set_property_value_function(get_symbol_properties_function(Qworkspace_title_bar_text),
	    Qtype_specification_simple_expansion,list_constant_391);
    list_constant_392 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_375);
    list_constant_393 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_394 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_392,list_constant_393);
    list_constant_395 = STATIC_CONS(list_constant_5,Qnil);
    list_constant_84 = STATIC_LIST_STAR((SI_Long)5L,Qab_or,Qsymbol,Qtext,
	    list_constant_394,list_constant_395);
    define_type_specification_explicit_complex_type(Qworkspace_title_bar_text,
	    list_constant_84);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qworkspace_title_bar_text);
    string_constant_89 = 
	    STATIC_STRING("workspace-title-bar-text had ~d elements, but it ~\n                    cannot have more than two elements");
    workspace_title_bar_text_evaluation_setter_1 = 
	    STATIC_FUNCTION(workspace_title_bar_text_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qworkspace_title_bar_text,
	    workspace_title_bar_text_evaluation_setter_1);
    workspace_title_bar_text_evaluation_getter_1 = 
	    STATIC_FUNCTION(workspace_title_bar_text_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qworkspace_title_bar_text,
	    workspace_title_bar_text_evaluation_getter_1);
    string_constant_90 = 
	    STATIC_STRING("workspace-title-bar-text contains illegal element ~s");
    string_constant_91 = 
	    STATIC_STRING("workspace-title-bar-text had ~d elements, but it cannot ~\n                     have more than one element unless the first is the ~\n                     symbol NAME");
    string_constant_92 = 
	    STATIC_STRING("workspace-title-bar-text cannot have ~\n                                    the symbol NAME as its second element");
    string_constant_175 = 
	    STATIC_STRING("1n1n83-way1m1m9k83-Gdy1m9k83Qxy2l83-wdy8k1n83-way1m9k83-vOy2l83-vOy8k1n83-way1m1m9k83wJy1m9k83nBy2l83-UBy8k");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_175));
    Qview_preferences = STATIC_SYMBOL("VIEW-PREFERENCES",AB_package);
    Qview_preference = STATIC_SYMBOL("VIEW-PREFERENCE",AB_package);
    add_grammar_rules_for_list(5,Qview_preferences,Qview_preference,Qsc,
	    Nil,Qnone);
    Qcompile_view_preferences_for_slot = 
	    STATIC_SYMBOL("COMPILE-VIEW-PREFERENCES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_view_preferences_for_slot,
	    STATIC_FUNCTION(compile_view_preferences_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qview_preferences,
	    SYMBOL_FUNCTION(Qcompile_view_preferences_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qview_preferences,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    string_constant_93 = STATIC_STRING(": ");
    Qwrite_view_preferences_from_slot = 
	    STATIC_SYMBOL("WRITE-VIEW-PREFERENCES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_view_preferences_from_slot,
	    STATIC_FUNCTION(write_view_preferences_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qview_preferences,
	    SYMBOL_FUNCTION(Qwrite_view_preferences_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qview_preferences),
	    Qtype_specification_simple_expansion,list_constant_140);
    Qvisible_grid = STATIC_SYMBOL("VISIBLE-GRID",AB_package);
    list_constant_396 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_397 = STATIC_CONS(Qvisible_grid,list_constant_396);
    Qunselectable = STATIC_SYMBOL("UNSELECTABLE",AB_package);
    list_constant_398 = STATIC_CONS(Qunselectable,list_constant_396);
    Qfixed_size = STATIC_SYMBOL("FIXED-SIZE",AB_package);
    list_constant_399 = STATIC_CONS(Qfixed_size,list_constant_396);
    list_constant_400 = STATIC_LIST((SI_Long)3L,list_constant_397,
	    list_constant_398,list_constant_399);
    list_constant_401 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_400);
    list_constant_86 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_401);
    define_type_specification_explicit_complex_type(Qview_preferences,
	    list_constant_86);
    list_constant_85 = STATIC_LIST((SI_Long)2L,Qnamed,Qview_preferences);
    view_preferences_evaluation_setter_1 = 
	    STATIC_FUNCTION(view_preferences_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qview_preferences,
	    view_preferences_evaluation_setter_1);
    view_preferences_evaluation_getter_1 = 
	    STATIC_FUNCTION(view_preferences_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qview_preferences,
	    view_preferences_evaluation_getter_1);
    string_constant_176 = 
	    STATIC_STRING("1n1n83Asy1m1m9k830Py83-aMy1m830Pym1n83Asy1q1m9k830Py83-aMy1m9k83vy1m9k839Zy1m9k83*Xy839Sy1n830Pymq1n83Asy1m9k8329y1m830Py0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_176));
    string_constant_177 = 
	    STATIC_STRING("1n1m83-aLy1m9k831iy1m83-aLy1m9k834Wy1n83-aLy1m1m9k83Cxy1m9k83=+y836iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_177));
    Qinteresting_ui_events = STATIC_SYMBOL("INTERESTING-UI-EVENTS",AB_package);
    Qinteresting_ui_event = STATIC_SYMBOL("INTERESTING-UI-EVENT",AB_package);
    add_grammar_rules_for_list(5,Qinteresting_ui_events,
	    Qinteresting_ui_event,Qcm,Qab_or,Qnil);
    Qon = STATIC_SYMBOL("ON",AB_package);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    Qconnect = STATIC_SYMBOL("CONNECT",AB_package);
    list_constant_87 = STATIC_LIST((SI_Long)3L,Qpause,Qreset,Qconnect);
    Qautomatically_show_developer_menu_bar = 
	    STATIC_SYMBOL("AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR",AB_package);
    Qcompile_automatically_show_developer_menu_bar_for_slot = 
	    STATIC_SYMBOL("COMPILE-AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_automatically_show_developer_menu_bar_for_slot,
	    STATIC_FUNCTION(compile_automatically_show_developer_menu_bar_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qautomatically_show_developer_menu_bar,
	    SYMBOL_FUNCTION(Qcompile_automatically_show_developer_menu_bar_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qautomatically_show_developer_menu_bar,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_94 = STATIC_STRING("initial connection");
    string_constant_95 = STATIC_STRING("on ");
    string_constant_96 = STATIC_STRING(" or ");
    Qtwrite_interesting_ui_event = 
	    STATIC_SYMBOL("TWRITE-INTERESTING-UI-EVENT",AB_package);
    SET_SYMBOL_FUNCTION(Qtwrite_interesting_ui_event,
	    STATIC_FUNCTION(twrite_interesting_ui_event,NIL,FALSE,1,1));
    string_constant_97 = STATIC_STRING(", or ");
    string_constant_98 = STATIC_STRING(", only in ");
    string_constant_99 = STATIC_STRING("nothing");
    string_constant_100 = STATIC_STRING(" mode");
    Qwrite_automatically_show_developer_menu_bar_from_slot = 
	    STATIC_SYMBOL("WRITE-AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_automatically_show_developer_menu_bar_from_slot,
	    STATIC_FUNCTION(write_automatically_show_developer_menu_bar_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qautomatically_show_developer_menu_bar,
	    SYMBOL_FUNCTION(Qwrite_automatically_show_developer_menu_bar_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qautomatically_show_developer_menu_bar),
	    Qtype_specification_simple_expansion,list_constant_6);
    Qevents = STATIC_SYMBOL("EVENTS",AB_package);
    list_constant_402 = STATIC_CONS(Qsequence,list_constant_92);
    list_constant_403 = STATIC_CONS(list_constant_402,Qnil);
    list_constant_404 = STATIC_CONS(Qevents,list_constant_403);
    Qmodes = STATIC_SYMBOL("MODES",AB_package);
    list_constant_405 = STATIC_CONS(Qmodes,list_constant_403);
    list_constant_406 = STATIC_LIST((SI_Long)2L,list_constant_404,
	    list_constant_405);
    list_constant_89 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_406);
    define_type_specification_explicit_complex_type(Qautomatically_show_developer_menu_bar,
	    list_constant_89);
    list_constant_88 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qautomatically_show_developer_menu_bar);
    automatically_show_developer_menu_bar_evaluation_setter_1 = 
	    STATIC_FUNCTION(automatically_show_developer_menu_bar_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qautomatically_show_developer_menu_bar,
	    automatically_show_developer_menu_bar_evaluation_setter_1);
    automatically_show_developer_menu_bar_evaluation_getter_1 = 
	    STATIC_FUNCTION(automatically_show_developer_menu_bar_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qautomatically_show_developer_menu_bar,
	    automatically_show_developer_menu_bar_evaluation_getter_1);
}
