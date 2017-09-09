/* g2rpc1.c
 * Input file:  g2-rpc1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2rpc1.h"


static Object Qitem_or_datum;      /* item-or-datum */

static Object Qitem_or_value;      /* item-or-value */

static Object Qdatum;              /* datum */

static Object Qvalue;              /* value */

static Object Qquantity;           /* quantity */

static Object Qis_class_instance;  /* is-class-instance */

static Object Qtype_name;          /* type-name */

static Object Qab_class;           /* class */

static Object Kkind;               /* :kind */

static Object Kinclude_system_attributes;  /* :include-system-attributes */

static Object Kinclude_all_system_attributes;  /* :include-all-system-attributes */

static Object Kinclude_all_system_attributes_except;  /* :include-all-system-attributes-except */

static Object Kinclude_attributes;  /* :include-attributes */

static Object Kexclude_attributes;  /* :exclude-attributes */

static Object Qkind;               /* kind */

static Object Qinclude_all_system_attributes;  /* include-all-system-attributes */

static Object Qinclude_all_system_attributes_except;  /* include-all-system-attributes-except */

static Object Qincluded_system_attributes;  /* included-system-attributes */

static Object Qincluded_user_attributes;  /* included-user-attributes */

static Object Qexcluded_user_attributes;  /* excluded-user-attributes */

/* CONVERT-REMOTE-PROCEDURE-DESCRIPTION-TO-STRUCTURE */
Object convert_remote_procedure_description_to_structure(remote_procedure_description)
    Object remote_procedure_description;
{
    Object temp, temp_1, general_description_qm, general_type, class_name;
    Object kind, included_system_attrs, include_all_system_attrs;
    Object include_all_system_attrs_except, included_user_attrs;
    Object excluded_user_attrs, temp_2, attr, ab_loop_list_, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, temp_3, temp_4, temp_5;
    char is_value_p;

    x_note_fn_call(166,0);
    is_value_p = SYMBOLP(remote_procedure_description);
    if (is_value_p) {
	temp = Evaluation_false_value;
	if (EQ(remote_procedure_description,Qitem_or_datum))
	    temp_1 = Qitem_or_value;
	else if (EQ(remote_procedure_description,Qdatum))
	    temp_1 = Qvalue;
	else if (EQ(remote_procedure_description,Qnumber))
	    temp_1 = Qquantity;
	else
	    temp_1 = remote_procedure_description;
	temp = 
		allocate_evaluation_structure(eval_cons_1(Qis_class_instance,
		eval_cons_1(temp,eval_cons_1(Qtype_name,eval_cons_1(temp_1,
		Nil)))));
    }
    else {
	general_description_qm = CONSP(remote_procedure_description) ? 
		CDR(remote_procedure_description) : Qnil;
	general_type = getf(general_description_qm,Ktype,_);
	class_name = CONSP(general_type) && EQ(FIRST(general_type),
		Qab_class) ? SECOND(general_type) : Qnil;
	kind = getf(general_description_qm,Kkind,_);
	included_system_attrs = getf(general_description_qm,
		Kinclude_system_attributes,_);
	include_all_system_attrs = getf(general_description_qm,
		Kinclude_all_system_attributes,_);
	include_all_system_attrs_except = getf(general_description_qm,
		Kinclude_all_system_attributes_except,_);
	included_user_attrs = getf(general_description_qm,
		Kinclude_attributes,_);
	excluded_user_attrs = getf(general_description_qm,
		Kexclude_attributes,_);
	if (general_description_qm) {
	    temp_2 = Evaluation_true_value;
	    temp_1 = include_all_system_attrs ? Evaluation_true_value : 
		    Evaluation_false_value;
	    attr = Nil;
	    ab_loop_list_ = include_all_system_attrs_except;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    attr = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = eval_cons_1(attr,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    temp_3 = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_1;
	    temp_3 = Qnil;
	  end_1:;
	    attr = Nil;
	    ab_loop_list_ = included_system_attrs;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    attr = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = eval_cons_1(attr,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_1;
	  end_loop_1:
	    temp_4 = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_2;
	    temp_4 = Qnil;
	  end_2:;
	    attr = Nil;
	    ab_loop_list_ = included_user_attrs;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    attr = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = eval_cons_1(attr,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_2;
	  end_loop_2:
	    temp_5 = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_3;
	    temp_5 = Qnil;
	  end_3:;
	    attr = Nil;
	    ab_loop_list_ = excluded_user_attrs;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    attr = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = eval_cons_1(attr,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_3;
	  end_loop_3:
	    temp = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	    temp = 
		    allocate_evaluation_structure(eval_cons_1(Qis_class_instance,
		    eval_cons_1(temp_2,eval_cons_1(Qtype_name,
		    eval_cons_1(class_name,eval_cons_1(Qkind,
		    eval_cons_1(kind,
		    eval_cons_1(Qinclude_all_system_attributes,
		    eval_cons_1(temp_1,
		    eval_cons_1(Qinclude_all_system_attributes_except,
		    eval_cons_1(temp_3,
		    eval_cons_1(Qincluded_system_attributes,
		    eval_cons_1(temp_4,
		    eval_cons_1(Qincluded_user_attributes,
		    eval_cons_1(temp_5,
		    eval_cons_1(Qexcluded_user_attributes,eval_cons_1(temp,
		    Nil)))))))))))))))));
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ARGUMENT-DESCRIPTIONS-EVALUATION-GETTER */
Object remote_procedure_argument_descriptions_evaluation_getter(slot_value_qm,
	    frame,slot_description)
    Object slot_value_qm, frame, slot_description;
{
    Object description, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arg_descriptions;
    SI_Long counter, ab_loop_bind_;

    x_note_fn_call(166,1);
    if (slot_value_qm) {
	counter = (SI_Long)1L;
	ab_loop_bind_ = IFIX(ISVREF(slot_value_qm,(SI_Long)1L));
	description = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (counter >= ab_loop_bind_)
	    goto end_loop;
	description = FIXNUM_LE(ISVREF(slot_value_qm,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(slot_value_qm,
		counter + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(slot_value_qm,(counter >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),counter & (SI_Long)1023L);
	ab_loopvar__2 = 
		eval_cons_1(convert_remote_procedure_description_to_structure(description),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	counter = counter + (SI_Long)2L;
	goto next_loop;
      end_loop:
	arg_descriptions = ab_loopvar_;
	goto end_1;
	arg_descriptions = Qnil;
      end_1:;
    }
    else
	arg_descriptions = Nil;
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(arg_descriptions));
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qnone;               /* none */

/* REMOTE-PROCEDURE-NAME-EVALUATION-SETTER */
Object remote_procedure_name_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(166,2);
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
		      goto end_remote_procedure_name_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value)
	result = copy_for_phrase(evaluation_value);
    else
	result = VALUES_1(Qnone);
  end_remote_procedure_name_evaluation_setter:
    return result;
}

/* REMOTE-PROCEDURE-NAME-EVALUATION-GETTER */
Object remote_procedure_name_evaluation_getter(slot_value_qm,frame,
	    slot_description)
    Object slot_value_qm, frame, slot_description;
{
    x_note_fn_call(166,3);
    GENSYM_RETURN_ONE(slot_value_qm ? 
	    copy_wide_string(symbol_name_text_string(slot_value_qm)) : Nil);
    return VALUES_1(Nil);
}

/* REMOTE-PROCEDURE-ARGUMENT-DESCRIPTION-FUNCTION */
Object remote_procedure_argument_description_function(remote_procedure_declaration)
    Object remote_procedure_declaration;
{
    Object temp;

    x_note_fn_call(166,4);
    temp = ISVREF(remote_procedure_declaration,(SI_Long)24L);
    return VALUES_1(temp);
}

static Object Qremote_procedure_argument_description;  /* remote-procedure-argument-description */

/* SET-REMOTE-PROCEDURE-ARGUMENT-DESCRIPTION-FUNCTION */
Object set_remote_procedure_argument_description_function(remote_procedure_declaration,
	    new_value)
    Object remote_procedure_declaration, new_value;
{
    x_note_fn_call(166,5);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(remote_procedure_declaration,
		Qremote_procedure_argument_description);
    return VALUES_1(SVREF(remote_procedure_declaration,FIX((SI_Long)24L)) 
	    = new_value);
}

/* REMOTE-PROCEDURE-RETURNED-VALUES-DESCRIPTION-FUNCTION */
Object remote_procedure_returned_values_description_function(remote_procedure_declaration)
    Object remote_procedure_declaration;
{
    Object temp;

    x_note_fn_call(166,6);
    temp = ISVREF(remote_procedure_declaration,(SI_Long)25L);
    return VALUES_1(temp);
}

static Object Qremote_procedure_returned_values_description;  /* remote-procedure-returned-values-description */

/* SET-REMOTE-PROCEDURE-RETURNED-VALUES-DESCRIPTION-FUNCTION */
Object set_remote_procedure_returned_values_description_function(remote_procedure_declaration,
	    new_value)
    Object remote_procedure_declaration, new_value;
{
    x_note_fn_call(166,7);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(remote_procedure_declaration,
		Qremote_procedure_returned_values_description);
    return VALUES_1(SVREF(remote_procedure_declaration,FIX((SI_Long)25L)) 
	    = new_value);
}

/* REMOTE-PROCEDURE-RETURN-VALUE-TYPES-FUNCTION */
Object remote_procedure_return_value_types_function(remote_procedure_declaration)
    Object remote_procedure_declaration;
{
    Object temp;

    x_note_fn_call(166,8);
    temp = ISVREF(remote_procedure_declaration,(SI_Long)16L);
    temp = CAR(temp);
    return VALUES_1(THIRD(temp));
}

static Object Kall_remaining;      /* :all-remaining */

/* ENCODE-REMAINING-INTO-REMOTE-PROCEDURE-TYPE */
Object encode_remaining_into_remote_procedure_type(form)
    Object form;
{
    Object temp;

    x_note_fn_call(166,9);
    temp = ATOM(form) ? phrase_list_4(Ktype,form,Kall_remaining,T) : 
	    nconc2(form,phrase_list_2(Kall_remaining,T));
    return VALUES_1(temp);
}

static Object Qcm;                 /* \, */

/* ENCODE-REMAINING-INTO-REMOTE-PROCEDURE-TYPE-1 */
Object encode_remaining_into_remote_procedure_type_1(form)
    Object form;
{
    x_note_fn_call(166,10);
    return phrase_list_2(Qcm,
	    encode_remaining_into_remote_procedure_type(SECOND(form)));
}

/* ENCODE-REMAINING-INTO-REMOTE-PROCEDURE-TYPE-2 */
Object encode_remaining_into_remote_procedure_type_2(form)
    Object form;
{
    Object temp;

    x_note_fn_call(166,11);
    temp = SECOND(form);
    return simplify_associative_operation(phrase_list_3(Qcm,temp,
	    encode_remaining_into_remote_procedure_type(THIRD(form))));
}

static Object Kgeneral_description;  /* :general-description */

static Object Kas_handle_p;        /* :as-handle-p */

static Object Qhandle;             /* handle */

/* FIX-REMOTE-PROCEDURE-DECLARATION-DESCRIPTIONS */
Object fix_remote_procedure_declaration_descriptions(descriptions)
    Object descriptions;
{
    Object var_whole_type_description, type, gensymed_symbol_1;
    Object badly_formated_properties_qm, temp, svref_new_value, description;
    Object tail;
    SI_Long index_1, ab_loop_bind_, gensymed_symbol, temp_1;

    x_note_fn_call(166,12);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(var_count(descriptions));
    var_whole_type_description = Nil;
    type = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
    var_whole_type_description = FIXNUM_LE(ISVREF(descriptions,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(descriptions,gensymed_symbol + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(descriptions,
	    (gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    gensymed_symbol & (SI_Long)1023L);
    gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(descriptions,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(descriptions,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description))
	gensymed_symbol_1 = 
		getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
    type = gensymed_symbol_1;
    if (CONSP(type) && EQ(CAR(type),Qab_class)) {
	badly_formated_properties_qm = CDDR(type);
	if (badly_formated_properties_qm) {
	    M_CDDR(type) = Nil;
	    if (EQ(CAR(var_whole_type_description),Kgeneral_description)) {
		temp = last(var_whole_type_description,_);
		M_CDR(temp) = badly_formated_properties_qm;
	    }
	    else {
		temp_1 = index_1 * (SI_Long)2L + (SI_Long)1L;
		svref_new_value = slot_value_cons_1(Kgeneral_description,
			slot_value_cons_1(Ktype,slot_value_cons_1(type,
			badly_formated_properties_qm)));
		if (FIXNUM_LE(ISVREF(descriptions,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = temp_1 + IFIX(Managed_array_index_offset);
		    ISVREF(descriptions,temp_1) = svref_new_value;
		}
		else {
		    temp = ISVREF(descriptions,(temp_1 >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_1 = temp_1 & (SI_Long)1023L;
		    ISVREF(temp,temp_1) = svref_new_value;
		}
	    }
	}
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(var_count(descriptions));
    description = Nil;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
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
    tail = CDR(description);
  next_loop_2:
    if ( !TRUEP(tail))
	goto end_loop_2;
    if (CDR(tail) && EQ(CADR(tail),Kas_handle_p)) {
	temp = CADDR(tail) ? slot_value_cons_1(Kkind,
		slot_value_cons_1(Qhandle,CDDDR(tail))) : CDDDR(tail);
	M_CDR(tail) = temp;
    }
    tail = CDDR(tail);
    goto next_loop_2;
  end_loop_2:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(descriptions);
}

static Object Qremote_procedure_declaration;  /* remote-procedure-declaration */

/* REFORMAT-REMOTE-PROCEDURE-DECLARATION-DESCRIPTIONS */
Object reformat_remote_procedure_declaration_descriptions()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object remote_procedure_declaration, old_value, svref_new_value, temp_1;
    Object declarations, arg_declarations, result_declarations;
    Object arg_declaration, ab_loop_list_, excess_info_qm, result_declaration;
    char temp;
    Declare_special(2);

    x_note_fn_call(166,13);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)259L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  remote_procedure_declaration = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qremote_procedure_declaration);
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
	    remote_procedure_declaration = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    old_value = ISVREF(remote_procedure_declaration,(SI_Long)24L);
	    if (CONSP(old_value)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(remote_procedure_declaration,
			    Qremote_procedure_argument_description);
		svref_new_value = 
			convert_description_list_to_managed_array(1,old_value);
		SVREF(remote_procedure_declaration,FIX((SI_Long)24L)) = 
			svref_new_value;
		reclaim_slot_value(old_value);
	    }
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(remote_procedure_declaration,
			Qremote_procedure_argument_description);
	    svref_new_value = 
		    fix_remote_procedure_declaration_descriptions(ISVREF(remote_procedure_declaration,
		    (SI_Long)24L));
	    SVREF(remote_procedure_declaration,FIX((SI_Long)24L)) = 
		    svref_new_value;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(remote_procedure_declaration,
			Qremote_procedure_returned_values_description);
	    svref_new_value = ISVREF(remote_procedure_declaration,
		    (SI_Long)25L);
	    if (svref_new_value);
	    else {
		temp_1 = ISVREF(remote_procedure_declaration,(SI_Long)16L);
		temp_1 = CAR(temp_1);
		svref_new_value = copy_for_slot_value(THIRD(temp_1));
	    }
	    SVREF(remote_procedure_declaration,FIX((SI_Long)25L)) = 
		    svref_new_value;
	    old_value = ISVREF(remote_procedure_declaration,(SI_Long)25L);
	    if (CONSP(old_value)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(remote_procedure_declaration,
			    Qremote_procedure_returned_values_description);
		svref_new_value = 
			convert_description_list_to_managed_array(1,old_value);
		SVREF(remote_procedure_declaration,FIX((SI_Long)25L)) = 
			svref_new_value;
		reclaim_slot_value(old_value);
	    }
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(remote_procedure_declaration,
			Qremote_procedure_returned_values_description);
	    svref_new_value = 
		    fix_remote_procedure_declaration_descriptions(ISVREF(remote_procedure_declaration,
		    (SI_Long)25L));
	    SVREF(remote_procedure_declaration,FIX((SI_Long)25L)) = 
		    svref_new_value;
	    temp_1 = ISVREF(remote_procedure_declaration,(SI_Long)16L);
	    declarations = FIRST(temp_1);
	    arg_declarations = SECOND(declarations);
	    result_declarations = THIRD(declarations);
	    arg_declaration = Nil;
	    ab_loop_list_ = arg_declarations;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    arg_declaration = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (CONSP(arg_declaration) && EQ(CAR(arg_declaration),Qab_class)) {
		excess_info_qm = CDDR(arg_declaration);
		if (excess_info_qm) {
		    M_CDDR(arg_declaration) = Nil;
		    reclaim_slot_value_cons_1(excess_info_qm);
		}
	    }
	    goto next_loop_2;
	  end_loop_2:;
	    result_declaration = Nil;
	    ab_loop_list_ = result_declarations;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    result_declaration = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (CONSP(result_declaration) && EQ(CAR(result_declaration),
		    Qab_class)) {
		excess_info_qm = CDDR(result_declaration);
		if (excess_info_qm) {
		    M_CDDR(result_declaration) = Nil;
		    reclaim_slot_value_cons_1(excess_info_qm);
		}
	    }
	    goto next_loop_3;
	  end_loop_3:;
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qname_in_remote_system;  /* name-in-remote-system */

static Object Quser_supplied_remote_name_qm;  /* user-supplied-remote-name? */

/* COMPILE-REMOTE-PROCEDURE-DECLARATION-FOR-SLOT */
Object compile_remote_procedure_declaration_for_slot varargs_1(int, n)
{
    Object parse_result, declaration, gensymed_symbol;
    Object name, arg_descriptions, result_descriptions, temp, type;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_1;
    Object temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(166,14);
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
    name = FIRST(parse_result);
    arg_descriptions = SECOND(parse_result);
    result_descriptions = THIRD(parse_result);
    if ( !TRUEP(ISVREF(declaration,(SI_Long)22L)))
	change_slot_value(3,declaration,Qname_in_remote_system,name);
    else if (EQ(ISVREF(declaration,(SI_Long)20L),name)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(declaration,Quser_supplied_remote_name_qm);
	SVREF(declaration,FIX((SI_Long)22L)) = Nil;
    }
    change_slot_value(3,declaration,Qremote_procedure_argument_description,
	    convert_description_list_to_managed_array(1,arg_descriptions));
    change_slot_value(3,declaration,
	    Qremote_procedure_returned_values_description,
	    convert_description_list_to_managed_array(2,
	    result_descriptions,T));
    temp = FIRST(parse_result);
    type = Nil;
    ab_loop_list_ = arg_descriptions;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(SYMBOLP(type) ? type : 
	    copy_list_using_phrase_conses(getf(type,Ktype,_)),Nil);
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
    type = Nil;
    ab_loop_list_ = result_descriptions;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(SYMBOLP(type) ? type : 
	    copy_list_using_phrase_conses(getf(type,Ktype,_)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp_2 = ab_loopvar_;
    goto end_2;
    temp_2 = Qnil;
  end_2:;
    return phrase_list_3(temp,temp_1,temp_2);
}

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-REMOTE-PROCEDURE-DECLARATION */
Object put_box_translation_and_text_slot_value_for_remote_procedure_declaration(remote_procedure_declaration,
	    new_value,initializing_qm)
    Object remote_procedure_declaration, new_value, initializing_qm;
{
    Object temp, new_name;
    char same_name_qm;

    x_note_fn_call(166,15);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(remote_procedure_declaration,
		Qbox_translation_and_text);
    SVREF(remote_procedure_declaration,FIX((SI_Long)16L)) = new_value;
    if ( !TRUEP(initializing_qm)) {
	temp = CAR(new_value);
	new_name = CAR(temp);
	same_name_qm = EQ(new_name,
		get_lookup_slot_value_given_default(remote_procedure_declaration,
		Qname_or_names_for_frame,Nil));
	update_frame_status(remote_procedure_declaration,Nil,Nil);
	change_slot_value(3,remote_procedure_declaration,
		Qname_or_names_for_frame,new_name);
	if (same_name_qm)
	    analyze_compiled_items_for_consistency(new_name);
    }
    return VALUES_2(new_value,Nil);
}

static Object string_constant;     /* "~(~A~)" */

/* COMPILE-REMOTE-PROCEDURE-NAME-FOR-SLOT */
Object compile_remote_procedure_name_for_slot varargs_1(int, n)
{
    Object parse_result, declaration, gensymed_symbol;
    Object box_translation_and_text, translation_qm, name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(166,16);
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
	name = CAR(translation_qm);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(declaration,Quser_supplied_remote_name_qm);
	SVREF(declaration,FIX((SI_Long)22L)) = Nil;
	if (name)
	    return intern_text_string(1,tformat_text_string(2,
		    string_constant,name));
	else
	    return VALUES_1(Nil);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(declaration,Quser_supplied_remote_name_qm);
	SVREF(declaration,FIX((SI_Long)22L)) = T;
	return intern_text_string(1,copy_text_string(parse_result));
    }
}

static Object string_constant_1;   /* "none" */

/* WRITE-REMOTE-PROCEDURE-NAME-FROM-SLOT */
Object write_remote_procedure_name_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(166,17);
    return tprin(value ? symbol_name_text_string(value) : 
	    string_constant_1,value);
}

/* PUT-NAME-IN-REMOTE-SYSTEM */
Object put_name_in_remote_system(remote_procedure_declaration,new_name,
	    gensymed_symbol)
    Object remote_procedure_declaration, new_name, gensymed_symbol;
{
    Object old_name, svref_new_value;

    x_note_fn_call(166,18);
    old_name = ISVREF(remote_procedure_declaration,(SI_Long)21L);
    if (old_name)
	reclaim_remote_procedure_name(old_name);
    svref_new_value = make_remote_procedure_name_1(new_name);
    ISVREF(remote_procedure_declaration,(SI_Long)21L) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(remote_procedure_declaration,
		Qname_in_remote_system);
    return VALUES_1(SVREF(remote_procedure_declaration,FIX((SI_Long)20L)) 
	    = new_name);
}

/* RECLAIM-REMOTE-PROCEDURE-NAME-STRUCTURE-VALUE */
Object reclaim_remote_procedure_name_structure_value(name_structure_qm,
	    gensymed_symbol)
    Object name_structure_qm, gensymed_symbol;
{
    x_note_fn_call(166,19);
    if (name_structure_qm)
	reclaim_remote_procedure_name(name_structure_qm);
    return VALUES_1(Nil);
}

Object The_type_description_of_scheduled_remote_procedure_start = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_scheduled_remote_procedure_starts, Qchain_of_available_scheduled_remote_procedure_starts);

DEFINE_VARIABLE_WITH_SYMBOL(Scheduled_remote_procedure_start_count, Qscheduled_remote_procedure_start_count);

Object Chain_of_available_scheduled_remote_procedure_starts_vector = UNBOUND;

/* SCHEDULED-REMOTE-PROCEDURE-START-STRUCTURE-MEMORY-USAGE */
Object scheduled_remote_procedure_start_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(166,20);
    temp = Scheduled_remote_procedure_start_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SCHEDULED-REMOTE-PROCEDURE-START-COUNT */
Object outstanding_scheduled_remote_procedure_start_count()
{
    Object def_structure_scheduled_remote_procedure_start_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(166,21);
    gensymed_symbol = IFIX(Scheduled_remote_procedure_start_count);
    def_structure_scheduled_remote_procedure_start_variable = 
	    Chain_of_available_scheduled_remote_procedure_starts;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_scheduled_remote_procedure_start_variable))
	goto end_loop;
    def_structure_scheduled_remote_procedure_start_variable = 
	    ISVREF(def_structure_scheduled_remote_procedure_start_variable,
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

/* RECLAIM-SCHEDULED-REMOTE-PROCEDURE-START-1 */
Object reclaim_scheduled_remote_procedure_start_1(scheduled_remote_procedure_start)
    Object scheduled_remote_procedure_start;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(166,22);
    inline_note_reclaim_cons(scheduled_remote_procedure_start,Nil);
    structure_being_reclaimed = scheduled_remote_procedure_start;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      reclaim_frame_serial_number(ISVREF(scheduled_remote_procedure_start,
	      (SI_Long)1L));
      SVREF(scheduled_remote_procedure_start,FIX((SI_Long)1L)) = Nil;
      reclaim_rpc_argument_list(ISVREF(scheduled_remote_procedure_start,
	      (SI_Long)4L),Nil);
      SVREF(scheduled_remote_procedure_start,FIX((SI_Long)4L)) = Nil;
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(scheduled_remote_procedure_start,(SI_Long)5L);
      if (CAS_SVREF(scheduled_remote_procedure_start,(SI_Long)5L,
	      gensymed_symbol,Nil)) {
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
      SVREF(scheduled_remote_procedure_start,FIX((SI_Long)5L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_scheduled_remote_procedure_starts_vector,
	    IFIX(Current_thread_index));
    SVREF(scheduled_remote_procedure_start,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_scheduled_remote_procedure_starts_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = scheduled_remote_procedure_start;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SCHEDULED-REMOTE-PROCEDURE-START */
Object reclaim_structure_for_scheduled_remote_procedure_start(scheduled_remote_procedure_start)
    Object scheduled_remote_procedure_start;
{
    x_note_fn_call(166,23);
    return reclaim_scheduled_remote_procedure_start_1(scheduled_remote_procedure_start);
}

static Object Qg2_defstruct_structure_name_scheduled_remote_procedure_start_g2_struct;  /* g2-defstruct-structure-name::scheduled-remote-procedure-start-g2-struct */

/* MAKE-PERMANENT-SCHEDULED-REMOTE-PROCEDURE-START-STRUCTURE-INTERNAL */
Object make_permanent_scheduled_remote_procedure_start_structure_internal()
{
    Object def_structure_scheduled_remote_procedure_start_variable;
    Object defstruct_g2_scheduled_remote_procedure_start_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(166,24);
    def_structure_scheduled_remote_procedure_start_variable = Nil;
    atomic_incff_symval(Qscheduled_remote_procedure_start_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_scheduled_remote_procedure_start_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_scheduled_remote_procedure_start_variable = the_array;
	SVREF(defstruct_g2_scheduled_remote_procedure_start_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_scheduled_remote_procedure_start_g2_struct;
	def_structure_scheduled_remote_procedure_start_variable = 
		defstruct_g2_scheduled_remote_procedure_start_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_scheduled_remote_procedure_start_variable);
}

/* MAKE-SCHEDULED-REMOTE-PROCEDURE-START-1 */
Object make_scheduled_remote_procedure_start_1(remote_procedure_start_reference_serial_number,
	    remote_procedure_start_declaration,
	    remote_procedure_start_icp_interface,
	    remote_procedure_start_argument_list)
    Object remote_procedure_start_reference_serial_number;
    Object remote_procedure_start_declaration;
    Object remote_procedure_start_icp_interface;
    Object remote_procedure_start_argument_list;
{
    Object def_structure_scheduled_remote_procedure_start_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(166,25);
    def_structure_scheduled_remote_procedure_start_variable = 
	    ISVREF(Chain_of_available_scheduled_remote_procedure_starts_vector,
	    IFIX(Current_thread_index));
    if (def_structure_scheduled_remote_procedure_start_variable) {
	svref_arg_1 = 
		Chain_of_available_scheduled_remote_procedure_starts_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_scheduled_remote_procedure_start_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_scheduled_remote_procedure_start_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_scheduled_remote_procedure_start_g2_struct;
    }
    else
	def_structure_scheduled_remote_procedure_start_variable = 
		make_permanent_scheduled_remote_procedure_start_structure_internal();
    inline_note_allocate_cons(def_structure_scheduled_remote_procedure_start_variable,
	    Nil);
    SVREF(def_structure_scheduled_remote_procedure_start_variable,
	    FIX((SI_Long)1L)) = remote_procedure_start_reference_serial_number;
    SVREF(def_structure_scheduled_remote_procedure_start_variable,
	    FIX((SI_Long)2L)) = remote_procedure_start_declaration;
    SVREF(def_structure_scheduled_remote_procedure_start_variable,
	    FIX((SI_Long)3L)) = remote_procedure_start_icp_interface;
    SVREF(def_structure_scheduled_remote_procedure_start_variable,
	    FIX((SI_Long)4L)) = remote_procedure_start_argument_list;
    SVREF(def_structure_scheduled_remote_procedure_start_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_scheduled_remote_procedure_start_variable);
}

/* ACTIVATE-FOR-REMOTE-PROCEDURE-DECLARATION */
Object activate_for_remote_procedure_declaration(remote_procedure_declaration)
    Object remote_procedure_declaration;
{
    Object svref_new_value, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(166,26);
    if ( !TRUEP(In_suspend_resume_p)) {
	svref_new_value = make_empty_constant_queue();
	ISVREF(remote_procedure_declaration,(SI_Long)23L) = svref_new_value;
    }
    frame = remote_procedure_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)6L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qremote_procedure_declaration)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-REMOTE-PROCEDURE-DECLARATION */
Object deactivate_for_remote_procedure_declaration(remote_procedure_declaration)
    Object remote_procedure_declaration;
{
    Object queue, scheduled_start, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(166,27);
    if ( !TRUEP(In_suspend_resume_p)) {
	queue = ISVREF(remote_procedure_declaration,(SI_Long)23L);
	scheduled_start = Nil;
      next_loop:
	scheduled_start = constant_queue_pop_left(2,queue,Nil);
	if ( !TRUEP(scheduled_start))
	    goto end_loop;
	reclaim_scheduled_remote_procedure_start_1(scheduled_start);
	goto next_loop;
      end_loop:
	reclaim_constant_queue(queue);
	ISVREF(remote_procedure_declaration,(SI_Long)23L) = Nil;
    }
    frame = remote_procedure_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qremote_procedure_declaration)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_1;
  end_loop_1:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_2;   /* "Argument error while starting remote procedure ~NF: ~a." */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qexecute_scheduled_remote_procedure_start;  /* execute-scheduled-remote-procedure-start */

/* START-REMOTE-PROCEDURE */
Object start_remote_procedure(remote_procedure_declaration,icp_interface,
	    argument_list,wait_interval_qm,priority_qm,new_top_of_stack)
    Object remote_procedure_declaration, icp_interface, argument_list;
    Object wait_interval_qm, priority_qm, new_top_of_stack;
{
    Object argument_error_message_qm, sub_class_bit_vector, top_of_stack;
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, temp_1, execution_priority, scheduled_start, old, new_1;
    Object def_structure_schedule_task_variable, temp_2, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp, svref_new_value_1;
    double gensymed_symbol_3, gensymed_symbol_4, aref_new_value_1;
    Declare_special(7);

    x_note_fn_call(166,28);
    argument_error_message_qm = 
	    remote_procedure_arg_type_error_p(ISVREF(remote_procedure_declaration,
	    (SI_Long)24L),argument_list);
    if (argument_error_message_qm) {
	reclaim_rpc_argument_list(argument_list,Nil);
	if (Current_computation_frame) {
	    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
		    (SI_Long)1L),(SI_Long)19L);
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
	if (temp) {
	    top_of_stack = new_top_of_stack;
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
			  tformat(3,string_constant_2,
				  remote_procedure_declaration,
				  argument_error_message_qm);
			  reclaim_text_string(argument_error_message_qm);
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
			  tformat(3,string_constant_2,
				  remote_procedure_declaration,
				  argument_error_message_qm);
			  reclaim_text_string(argument_error_message_qm);
			  temp_1 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_user_1(temp_1);
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	return VALUES_1(Nil);
    }
    execution_priority = priority_qm;
    if (execution_priority);
    else
	execution_priority = get_rpc_priority_from_computation_context();
    if ( !TRUEP(wait_interval_qm)) {
	sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,
		    (SI_Long)1L),(SI_Long)19L);
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
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	}
	if (temp)
	    execute_parallel_remote_procedure_start(remote_procedure_declaration,
		    icp_interface,argument_list,execution_priority);
	else
	    execute_remote_procedure_start(remote_procedure_declaration,
		    icp_interface,argument_list,execution_priority,Nil);
    }
    else {
	scheduled_start = 
		make_scheduled_remote_procedure_start_1(copy_frame_serial_number(Current_frame_serial_number),
		remote_procedure_declaration,icp_interface,argument_list);
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(scheduled_start,(SI_Long)5L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp_2 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp_2,svref_arg_2) = svref_new_value;
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
	temp_2 = ISVREF(task,(SI_Long)1L);
	gensymed_symbol_3 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	gensymed_symbol_4 = FIXNUMP(wait_interval_qm) ? 
		(double)IFIX(wait_interval_qm) : 
		DFLOAT_ISAREF_1(wait_interval_qm,(SI_Long)0L);
	aref_new_value_1 = gensymed_symbol_3 + gensymed_symbol_4;
	DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value_1);
	temp_2 = ISVREF(task,(SI_Long)1L);
	aref_new_value_1 = -1.0;
	DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value_1);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	SVREF(task,FIX((SI_Long)4L)) = execution_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = 
		Qexecute_scheduled_remote_procedure_start;
	temp_2 = SYMBOL_FUNCTION(Qexecute_scheduled_remote_procedure_start);
	SVREF(task,FIX((SI_Long)8L)) = temp_2;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)13L)) = scheduled_start;
	SVREF(task,FIX((SI_Long)14L)) = execution_priority;
	new_1 = task;
	if (CAS_SVREF(scheduled_start,(SI_Long)5L,old,new_1)) {
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
		temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp_2;
		temp_2 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = old;
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
	    temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
	    temp_2 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
	reclaim_evaluation_quantity(wait_interval_qm);
	temp_2 = 
		constant_queue_push_right(ISVREF(remote_procedure_declaration,
		(SI_Long)23L),scheduled_start);
	SVREF(scheduled_start,FIX((SI_Long)6L)) = temp_2;
    }
    return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* ALL-ELEMENTS-OK-FOR-PARALLEL-RPC-START */
Object all_elements_ok_for_parallel_rpc_start(icp_interface)
    Object icp_interface;
{
    Object sub_class_bit_vector, gensymed_symbol_3, ab_loopvar_, ab_loopvar__1;
    Object element, x2, temp_1, array, element_type, items_possible_p;
    Object managed_g2_array, float_or_quantity_p, tag_temp, elt_1, thing;
    Object gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, array_length;
    SI_Long managed_step_size, managed_length, max_inner_index, outer_index;
    SI_Long inner_index, ab_loop_bind_, incff_1_arg;
    char temp;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(166,29);
    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol_3 = icp_interface;
	ab_loopvar_ = ISVREF(gensymed_symbol_3,(SI_Long)20L);
	ab_loopvar__1 = Nil;
	element = Nil;
	ab_loopvar__1 = ab_loopvar_ ? 
		g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		ab_loopvar_) : Nil;
      next_loop:
	if ( !TRUEP(ab_loopvar__1))
	    goto end_loop;
	element = ISVREF(ab_loopvar__1,(SI_Long)4L);
	ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	if (SIMPLE_VECTOR_P(element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L &&  
		!EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !(temp ?  !TRUEP(serve_item_p(element)) || 
		g2_to_g2_data_interface_p_function(element) || 
		gsi_interface_p_function(element) : TRUEP(Nil))) {
	    temp_1 = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = T;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else {
	array = icp_interface;
	element_type = ISVREF(array,(SI_Long)21L);
	items_possible_p = 
		g2_list_or_array_element_type_may_contain_item_p(element_type);
	managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	managed_length = array_length * managed_step_size;
	float_or_quantity_p = EQ(element_type,Qfloat) ? T : Nil;
	if (float_or_quantity_p);
	else
	    float_or_quantity_p = EQ(element_type,Qquantity) ? T : Nil;
	max_inner_index = float_or_quantity_p ? (SI_Long)100L : managed_length;
	outer_index = (SI_Long)0L;
	tag_temp = UNIQUE_TAG(Qnil);
	if (PUSH_CATCH(tag_temp,0)) {
	    if ( !TRUEP(managed_g2_array)) {
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	  next_loop_1:
	    if ( !(outer_index < managed_length))
		goto end_loop_1;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		inner_index = (SI_Long)0L;
		ab_loop_bind_ = max_inner_index;
		element = Nil;
	      next_loop_2:
		if (inner_index >= ab_loop_bind_)
		    goto end_loop_2;
		if (EQ(element_type,Qfloat))
		    element = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
			    (outer_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),outer_index & (SI_Long)1023L));
		else {
		    elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(managed_g2_array,outer_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(managed_g2_array,(outer_index >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),outer_index 
			    & (SI_Long)1023L);
		    temp =  !TRUEP(items_possible_p);
		    if (temp);
		    else if (elt_1) {
			if (SIMPLE_VECTOR_P(elt_1) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
				(SI_Long)2L) {
			    temp = EQ(ISVREF(elt_1,(SI_Long)1L),
				    Qavailable_frame_vector);
			    if (temp);
			    else {
				thing = ISVREF(elt_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(thing) ? 
					EQ(ISVREF(thing,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					: TRUEP(Qnil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
			if (temp);
			else {
			    gensymed_symbol_3 = ISVREF(elt_1,(SI_Long)3L);
			    gensymed_symbol = outer_index + (SI_Long)1L;
			    gensymed_symbol_4 = 
				    FIXNUM_LE(ISVREF(managed_g2_array,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(managed_g2_array,
				    gensymed_symbol + 
				    IFIX(Managed_array_index_offset)) : 
				    ISVREF(ISVREF(managed_g2_array,
				    (gensymed_symbol >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    gensymed_symbol & (SI_Long)1023L);
			    temp = (FIXNUMP(gensymed_symbol_3) ? 
				    (FIXNUMP(gensymed_symbol_4) ? 
				    FIXNUM_EQ(gensymed_symbol_3,
				    gensymed_symbol_4) : TRUEP(Nil)) : 
				    FIXNUMP(gensymed_symbol_4) ? 
				    TRUEP(Nil) : 
				    FIXNUM_EQ(M_CAR(gensymed_symbol_3),
				    M_CAR(gensymed_symbol_4)) && 
				    FIXNUM_EQ(M_CDR(gensymed_symbol_3),
				    M_CDR(gensymed_symbol_4))) ? 
				    (SI_Long)0L != (IFIX(ISVREF(elt_1,
				    (SI_Long)5L)) & (SI_Long)1L) || 
				    ISVREF(array,(SI_Long)24L) : TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    element = temp ? elt_1 : Nil;
		}
		if (SIMPLE_VECTOR_P(element) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > 
			(SI_Long)2L &&  !EQ(ISVREF(element,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(element,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if ( !(temp ?  !TRUEP(serve_item_p(element)) || 
			g2_to_g2_data_interface_p_function(element) || 
			gsi_interface_p_function(element) : TRUEP(Nil))) {
		    result = VALUES_1(Nil);
		    THROW(tag_temp,result);
		}
		incff_1_arg = managed_step_size;
		outer_index = outer_index + incff_1_arg;
		if ( !(outer_index < managed_length))
		    goto end_loop_2;
		inner_index = inner_index + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_1(T);
	    THROW(tag_temp,result);
	    temp_1 = Qnil;
	}
	else
	    temp_1 = CATCH_VALUES();
	POP_CATCH(0);
    }
    return VALUES_1(temp_1);
}

/* EXECUTE-SCHEDULED-REMOTE-PROCEDURE-START */
Object execute_scheduled_remote_procedure_start(scheduled_start,
	    execution_priority)
    Object scheduled_start, execution_priority;
{
    Object reference_serial_number, remote_procedure_declaration;
    Object icp_interface, argument_list, gensymed_symbol, xa, ya;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(166,30);
    reference_serial_number = ISVREF(scheduled_start,(SI_Long)1L);
    remote_procedure_declaration = ISVREF(scheduled_start,(SI_Long)2L);
    icp_interface = ISVREF(scheduled_start,(SI_Long)3L);
    argument_list = ISVREF(scheduled_start,(SI_Long)4L);
    constant_queue_delete(1,ISVREF(scheduled_start,(SI_Long)6L));
    gensymed_symbol = ISVREF(remote_procedure_declaration,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(remote_procedure_declaration) ? 
	    EQ(ISVREF(remote_procedure_declaration,(SI_Long)1L),
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
    if ( !temp ? (SI_Long)0L != (IFIX(ISVREF(remote_procedure_declaration,
	    (SI_Long)5L)) & (SI_Long)1L) : TRUEP(Nil)) {
	gensymed_symbol = ISVREF(icp_interface,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(icp_interface) ? EQ(ISVREF(icp_interface,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(reference_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(reference_serial_number,gensymed_symbol) : 
		    TRUEP(T);
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp ? (SI_Long)0L != (IFIX(ISVREF(icp_interface,(SI_Long)5L)) & 
	    (SI_Long)1L) : TRUEP(Nil)) {
	sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    if (all_elements_ok_for_parallel_rpc_start(icp_interface))
		execute_parallel_remote_procedure_start(remote_procedure_declaration,
			icp_interface,argument_list,execution_priority);
	}
	else
	    execute_remote_procedure_start(remote_procedure_declaration,
		    icp_interface,argument_list,execution_priority,Nil);
	SVREF(scheduled_start,FIX((SI_Long)4L)) = Nil;
    }
    return reclaim_scheduled_remote_procedure_start_1(scheduled_start);
}

/* NON-RESUMABLE-ICP-SOCKET-P */
Object non_resumable_icp_socket_p(icp_socket_qm)
    Object icp_socket_qm;
{
    Object temp;

    x_note_fn_call(166,31);
    temp = icp_socket_qm && icp_connection_open_p(icp_socket_qm) &&  
	    !TRUEP(icp_connection_being_shutdown_qm(icp_socket_qm)) ? 
	    (IFIX(ISVREF(icp_socket_qm,(SI_Long)22L)) >= (SI_Long)17L ? 
	    ISVREF(icp_socket_qm,(SI_Long)53L) : Nil) : Qnil;
    return VALUES_1(temp);
}

/* ADD-INTERFACE-TO-ALIST */
Object add_interface_to_alist(interface_1,alist,key)
    Object interface_1, alist, key;
{
    Object a, ab_loop_list_, temp, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object cdr_new_value;

    x_note_fn_call(166,32);
    a = Nil;
    ab_loop_list_ = alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    a = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CAR(a);
    if (EQUAL(key,temp))
	goto end_1;
    goto next_loop;
  end_loop:
    a = Qnil;
  end_1:;
    if (a) {
	if (key)
	    reclaim_gensym_cons_1(key);
	gensym_push_modify_macro_arg = interface_1;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = CDR(a);
	cdr_new_value = gensym_cons_1(car_1,cdr_1);
	M_CDR(a) = cdr_new_value;
	temp = alist;
    }
    else
	temp = gensym_cons_1(gensym_list_2(key,interface_1),alist);
    return VALUES_1(temp);
}

/* EXECUTE-PARALLEL-REMOTE-PROCEDURE-START */
Object execute_parallel_remote_procedure_start(remote_procedure_declaration,
	    icp_interface,argument_list,execution_priority)
    Object remote_procedure_declaration, icp_interface, argument_list;
    Object execution_priority;
{
    Object socket_alist, descriptions, argument_type_or_class, info;
    Object ab_loop_it_, gensymed_symbol_1, uses_by_handle_p;
    Object sub_class_bit_vector, ab_loopvar_, ab_loopvar__1, element, x2;
    Object icp_socket_qm, temp_1, temp_2, temp_3, array, element_type;
    Object items_possible_p, managed_g2_array, float_or_quantity_p, elt_1;
    Object thing, gensymed_symbol_4, a, ab_loop_list_, key, interface_list;
    Object interface_1, ab_loop_list__1;
    SI_Long description_index, ab_loop_bind_, gensymed_symbol;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, array_length;
    SI_Long managed_step_size, managed_length, max_inner_index, outer_index;
    SI_Long inner_index, incff_1_arg;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(166,33);
    socket_alist = Nil;
    descriptions = 
	    remote_procedure_argument_description_function(remote_procedure_declaration);
    description_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(var_count(descriptions));
    argument_type_or_class = Nil;
    info = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if (description_index >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = description_index * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(descriptions,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(descriptions,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description))
	gensymed_symbol_1 = 
		getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
    argument_type_or_class = gensymed_symbol_1;
    info = var_rpc_info_from_index(descriptions,FIX(description_index));
    ab_loop_it_ = EQ(Qhandle,remote_procedure_item_info_kind(info)) ? T : Nil;
    if (ab_loop_it_) {
	uses_by_handle_p = ab_loop_it_;
	goto end_1;
    }
    description_index = description_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    uses_by_handle_p = Qnil;
  end_1:;
    sub_class_bit_vector = ISVREF(ISVREF(icp_interface,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol_1 = icp_interface;
	ab_loopvar_ = ISVREF(gensymed_symbol_1,(SI_Long)20L);
	ab_loopvar__1 = Nil;
	element = Nil;
	ab_loopvar__1 = ab_loopvar_ ? 
		g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		ab_loopvar_) : Nil;
      next_loop_1:
	if ( !TRUEP(ab_loopvar__1))
	    goto end_loop_1;
	element = ISVREF(ab_loopvar__1,(SI_Long)4L);
	ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	if (SIMPLE_VECTOR_P(element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L &&  
		!EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? TRUEP(serve_item_p(element)) : TRUEP(Nil)) {
	    icp_socket_qm = icp_socket_of_interface_object(element);
	    temp_1 = element;
	    temp_2 = socket_alist;
	    if (non_resumable_icp_socket_p(icp_socket_qm)) {
		temp_3 = ISVREF(icp_socket_qm,(SI_Long)22L);
		temp_3 = gensym_cons_1(temp_3,
			item_references_enabled_p(icp_socket_qm));
	    }
	    else
		temp_3 = Nil;
	    socket_alist = add_interface_to_alist(temp_1,temp_2,temp_3);
	}
	goto next_loop_1;
      end_loop_1:
	goto end_2;
      end_2:;
    }
    else {
	array = icp_interface;
	element_type = ISVREF(array,(SI_Long)21L);
	items_possible_p = 
		g2_list_or_array_element_type_may_contain_item_p(element_type);
	managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	managed_length = array_length * managed_step_size;
	float_or_quantity_p = EQ(element_type,Qfloat) ? T : Nil;
	if (float_or_quantity_p);
	else
	    float_or_quantity_p = EQ(element_type,Qquantity) ? T : Nil;
	max_inner_index = float_or_quantity_p ? (SI_Long)100L : managed_length;
	outer_index = (SI_Long)0L;
	if ( !TRUEP(managed_g2_array))
	    goto end_3;
      next_loop_2:
	if ( !(outer_index < managed_length))
	    goto end_loop_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    inner_index = (SI_Long)0L;
	    ab_loop_bind_ = max_inner_index;
	    element = Nil;
	  next_loop_3:
	    if (inner_index >= ab_loop_bind_)
		goto end_loop_3;
	    if (EQ(element_type,Qfloat))
		element = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
			(outer_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
			outer_index & (SI_Long)1023L));
	    else {
		elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			ISVREF(managed_g2_array,outer_index + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(managed_g2_array,(outer_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L),outer_index & 
			(SI_Long)1023L);
		temp =  !TRUEP(items_possible_p);
		if (temp);
		else if (elt_1) {
		    if (SIMPLE_VECTOR_P(elt_1) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
			    (SI_Long)2L) {
			temp = EQ(ISVREF(elt_1,(SI_Long)1L),
				Qavailable_frame_vector);
			if (temp);
			else {
			    thing = ISVREF(elt_1,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(thing) ? 
				    EQ(ISVREF(thing,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    : TRUEP(Qnil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		    if (temp);
		    else {
			gensymed_symbol_1 = ISVREF(elt_1,(SI_Long)3L);
			gensymed_symbol = outer_index + (SI_Long)1L;
			gensymed_symbol_4 = 
				FIXNUM_LE(ISVREF(managed_g2_array,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(managed_g2_array,gensymed_symbol + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(managed_g2_array,
				(gensymed_symbol >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
			temp = (FIXNUMP(gensymed_symbol_1) ? 
				(FIXNUMP(gensymed_symbol_4) ? 
				FIXNUM_EQ(gensymed_symbol_1,
				gensymed_symbol_4) : TRUEP(Nil)) : 
				FIXNUMP(gensymed_symbol_4) ? TRUEP(Nil) : 
				FIXNUM_EQ(M_CAR(gensymed_symbol_1),
				M_CAR(gensymed_symbol_4)) && 
				FIXNUM_EQ(M_CDR(gensymed_symbol_1),
				M_CDR(gensymed_symbol_4))) ? (SI_Long)0L 
				!= (IFIX(ISVREF(elt_1,(SI_Long)5L)) & 
				(SI_Long)1L) || ISVREF(array,(SI_Long)24L) 
				: TRUEP(Nil);
		    }
		}
		else
		    temp = TRUEP(Nil);
		element = temp ? elt_1 : Nil;
	    }
	    if (SIMPLE_VECTOR_P(element) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(element,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(element,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? TRUEP(serve_item_p(element)) : TRUEP(Nil)) {
		icp_socket_qm = icp_socket_of_interface_object(element);
		temp_1 = element;
		temp_2 = socket_alist;
		if (non_resumable_icp_socket_p(icp_socket_qm)) {
		    temp_3 = ISVREF(icp_socket_qm,(SI_Long)22L);
		    temp_3 = gensym_cons_1(temp_3,
			    item_references_enabled_p(icp_socket_qm));
		}
		else
		    temp_3 = Nil;
		socket_alist = add_interface_to_alist(temp_1,temp_2,temp_3);
	    }
	    incff_1_arg = managed_step_size;
	    outer_index = outer_index + incff_1_arg;
	    if ( !(outer_index < managed_length))
		goto end_loop_3;
	    inner_index = inner_index + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	goto next_loop_2;
      end_loop_2:
	goto end_3;
      end_3:;
    }
    a = Nil;
    ab_loop_list_ = socket_alist;
    key = Nil;
    interface_list = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    a = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    key = CAR(a);
    interface_list = CDR(a);
    if (uses_by_handle_p ||  !TRUEP(key) ||  !TRUEP(CDR(interface_list))) {
	interface_1 = Nil;
	ab_loop_list__1 = interface_list;
      next_loop_5:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_5;
	interface_1 = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	execute_remote_procedure_start(remote_procedure_declaration,
		interface_1,argument_list,execution_priority,T);
	goto next_loop_5;
      end_loop_5:;
    }
    else
	execute_fast_parallel_remote_procedure_start(remote_procedure_declaration,
		argument_list,execution_priority,CAR(key),CDR(key),
		interface_list);
    if (key)
	reclaim_gensym_cons_1(key);
    reclaim_gensym_list_1(a);
    goto next_loop_4;
  end_loop_4:;
    reclaim_gensym_list_1(socket_alist);
    return reclaim_rpc_argument_list(argument_list,Nil);
}

static Object Qtemporary_output;   /* temporary-output */

static Object Qtelewindows;        /* telewindows */

/* EXECUTE-FAST-PARALLEL-REMOTE-PROCEDURE-START */
Object execute_fast_parallel_remote_procedure_start(remote_procedure_declaration,
	    argument_list,execution_priority,icp_version,
	    uses_item_references,interface_list)
    Object remote_procedure_declaration, argument_list, execution_priority;
    Object icp_version, uses_item_references, interface_list;
{
    Object temporary_icp_socket, temporary_output_port;
    Object inhibit_corresponding_icp_object_making, current_icp_port;
    Object current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, head, tail, icp_buffers;
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, interface_1, ab_loop_list_;
    Object icp_socket;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(13);

    x_note_fn_call(166,34);
    temporary_icp_socket = make_icp_socket(Nil,Qtemporary_output,Nil,Nil,
	    Nil,Nil,T,Nil,Current_system_name,Nil);
    temporary_output_port = ISVREF(temporary_icp_socket,(SI_Long)4L);
    SVREF(temporary_icp_socket,FIX((SI_Long)53L)) = T;
    SVREF(temporary_icp_socket,FIX((SI_Long)22L)) = icp_version;
    SVREF(temporary_icp_socket,FIX((SI_Long)21L)) = icp_version;
    SVREF(temporary_icp_socket,FIX((SI_Long)50L)) = uses_item_references;
    inhibit_corresponding_icp_object_making = T;
    PUSH_SPECIAL_WITH_SYMBOL(Inhibit_corresponding_icp_object_making,Qinhibit_corresponding_icp_object_making,inhibit_corresponding_icp_object_making,
	    12);
      current_icp_port = temporary_output_port;
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
				  execute_remote_procedure_start(remote_procedure_declaration,
					  Current_icp_socket,argument_list,
					  execution_priority,T);
				  end_icp_message_group();
			      }
			      if (Profiling_enabled_qm) {
				  gensymed_symbol_3 = 
					  g2ext_unix_time_as_float();
				  gensymed_symbol_4 = 
					  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					  (SI_Long)2L),(SI_Long)0L);
				  gensymed_symbol_5 = gensymed_symbol_3 - 
					  gensymed_symbol_4;
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
    POP_SPECIAL();
    head = ISVREF(temporary_output_port,(SI_Long)12L);
    tail = ISVREF(temporary_output_port,(SI_Long)13L);
    if ( !EQ(head,tail)) {
	temp = ISVREF(head,(SI_Long)1L);
	SVREF(temporary_output_port,FIX((SI_Long)13L)) = head;
	SVREF(head,FIX((SI_Long)1L)) = Nil;
	icp_buffers = temp;
    }
    else
	icp_buffers = Nil;
    outer_with_icp_buffer_coelescing_scope_qm = 
	    With_icp_buffer_coelescing_scope_qm;
    with_icp_buffer_coelescing_scope_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm,Qwith_icp_buffer_coelescing_scope_qm,with_icp_buffer_coelescing_scope_qm,
	    12);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
      interface_1 = Nil;
      ab_loop_list_ = interface_list;
      icp_socket = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      interface_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      icp_socket = icp_socket_of_interface_object(interface_1);
      current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
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
				  send_icp_define_temporary_index_space(ISVREF(temporary_output_port,
					  (SI_Long)8L));
				  end_icp_message_group();
			      }
			      if (Profiling_enabled_qm) {
				  gensymed_symbol_3 = 
					  g2ext_unix_time_as_float();
				  gensymed_symbol_4 = 
					  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					  (SI_Long)2L),(SI_Long)0L);
				  gensymed_symbol_5 = gensymed_symbol_3 - 
					  gensymed_symbol_4;
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
      current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
      icp_buffers_for_message_group = copy_icp_buffer_chain(icp_buffers);
      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		0);
	  transmit_completed_icp_message_group();
	POP_SPECIAL();
      POP_SPECIAL();
      current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
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
				  send_icp_release_temporary_index_space();
				  end_icp_message_group();
			      }
			      if (Profiling_enabled_qm) {
				  gensymed_symbol_3 = 
					  g2ext_unix_time_as_float();
				  gensymed_symbol_4 = 
					  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					  (SI_Long)2L),(SI_Long)0L);
				  gensymed_symbol_5 = gensymed_symbol_3 - 
					  gensymed_symbol_4;
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
      goto next_loop;
    end_loop:;
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
    POP_SPECIAL();
    reclaim_icp_buffer_list(icp_buffers);
    temp_1 = Icp_connection_closed;
    SVREF(temporary_icp_socket,FIX((SI_Long)15L)) = temp_1;
    reclaim_icp_socket(temporary_icp_socket);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_icp_socket_g2_struct;  /* g2-defstruct-structure-name::icp-socket-g2-struct */

static Object string_constant_3;   /* "The ICP interface ~NF was unable to accept network messages to ~
				    *               start ~NF, because it was not connected."
				    */

static Object string_constant_4;   /* "The ICP interface ~NF was unable to accept network messages to ~
				    *               start ~NF.  The socket is ~A."
				    */

static Object string_constant_5;   /* "The remote procedure ~NF could not be started ~
				    *                  because of a problem with its arguments: ~A"
				    */

/* EXECUTE-REMOTE-PROCEDURE-START */
Object execute_remote_procedure_start(remote_procedure_declaration,
	    icp_interface,argument_list,execution_priority,
	    do_not_reclaim_or_modify_argument_list)
    Object remote_procedure_declaration, icp_interface, argument_list;
    Object execution_priority, do_not_reclaim_or_modify_argument_list;
{
    Object interface_is_socket_p, icp_socket_qm, current_computation_frame;
    Object transform_error_message_qm, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, desc, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(8);

    x_note_fn_call(166,35);
    if (do_not_reclaim_or_modify_argument_list)
	argument_list = copy_list_using_eval_conses_1(argument_list);
    interface_is_socket_p = SIMPLE_VECTOR_P(icp_interface) ? 
	    (EQ(ISVREF(icp_interface,(SI_Long)0L),
	    Qg2_defstruct_structure_name_icp_socket_g2_struct) ? T : Nil) :
	     Qnil;
    icp_socket_qm = interface_is_socket_p ? icp_interface : 
	    icp_socket_of_interface_object(icp_interface);
    current_computation_frame = remote_procedure_declaration;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    7);
      transform_error_message_qm = Nil;
      if ( !TRUEP(icp_socket_qm) || FIXNUM_EQ(ISVREF(icp_socket_qm,
	      (SI_Long)15L),Icp_connection_closed)) {
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    write_warning_message_header(FIX((SI_Long)1L));
			    tformat(3,string_constant_3,icp_interface,
				    remote_procedure_declaration);
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
	  reclaim_rpc_argument_list(argument_list,
		  do_not_reclaim_or_modify_argument_list);
      }
      else if ( !TRUEP(icp_connection_open_p(icp_socket_qm)) || 
	      icp_connection_being_shutdown_qm(icp_socket_qm)) {
	  desc = icp_socket_description(icp_socket_qm);
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    write_warning_message_header(FIX((SI_Long)1L));
			    tformat(4,string_constant_4,icp_interface,
				    remote_procedure_declaration,desc);
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
	  reclaim_text_string(desc);
	  reclaim_rpc_argument_list(argument_list,
		  do_not_reclaim_or_modify_argument_list);
      }
      else {
	  temp_1 = argument_list;
	  temp = 
		  remote_procedure_argument_description_function(remote_procedure_declaration);
	  transform_error_message_qm = 
		  transform_rpc_argument_or_result_list(7,
		  remote_procedure_declaration,temp_1,temp,icp_socket_qm, 
		  !TRUEP(interface_is_socket_p) ? icp_interface : Nil,
		  execution_priority,T);
	  if (transform_error_message_qm) {
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
				allocate_byte_vector_16(FIX((SI_Long)2048L 
				+ (SI_Long)3L));
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
			  fill_pointer_for_current_wide_string = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				  2);
			    length_1 = 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			    total_length_of_current_wide_string = 
				    FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				    length_1 - (SI_Long)2L) + 
				    ((UBYTE_16_ISAREF_1(Current_wide_string,
				    length_1 - (SI_Long)1L) & 
				    (SI_Long)8191L) << (SI_Long)16L));
			    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				    1);
			      current_twriting_output_type = Qwide_string;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				      0);
				write_warning_message_header(FIX((SI_Long)1L));
				tformat(3,string_constant_5,
					remote_procedure_declaration,
					transform_error_message_qm);
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
	      reclaim_rpc_argument_list(argument_list,
		      do_not_reclaim_or_modify_argument_list);
	  }
	  else
	      send_rpc_start(ISVREF(icp_socket_qm,(SI_Long)4L),
		      execution_priority,
		      ISVREF(remote_procedure_declaration,(SI_Long)21L),
		      argument_list,do_not_reclaim_or_modify_argument_list);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_6;   /* "The argument ~NF was an item, ~
				    *                       not a value of the required type ~A"
				    */

static Object string_constant_7;   /* "The object argument ~NF was of class ~A, ~
				    *                     not of the required class ~A."
				    */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

static Object array_constant;      /* # */

static Object string_constant_8;   /* " for ~A was not of type integer." */

static Object array_constant_1;    /* # */

static Object string_constant_9;   /* " was not of the required type ~a." */

static Object string_constant_10;  /* "The argument ~A was not of the required type ~A" */

/* REMOTE-PROCEDURE-ARG-TYPE-ERROR-P-1 */
Object remote_procedure_arg_type_error_p_1(type,kind,argument)
    Object type, kind, argument;
{
    Object temp, x2, declared_class, argument_class, gensymed_symbol;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object entry_hash, argument_type, constant_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1;
    char temp_1, fixnum_type_p;
    Declare_special(5);
    Object result;

    x_note_fn_call(166,36);
    if (EQ(type,Qitem_or_datum))
	temp = Nil;
    else {
	if (SIMPLE_VECTOR_P(argument) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(argument)) > (SI_Long)2L && 
		 !EQ(ISVREF(argument,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(argument,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if ( !TRUEP(class_type_specification_p(type)))
		temp = tformat_text_string(3,string_constant_6,argument,type);
	    else {
		declared_class = SECOND(type);
		argument_class = ISVREF(ISVREF(argument,(SI_Long)1L),
			(SI_Long)1L);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(argument_class,
			Class_description_gkbprop);
		temp =  !(gensymed_symbol ? 
			TRUEP(memq_function(declared_class,
			ISVREF(gensymed_symbol,(SI_Long)2L))) : 
			TRUEP(Nil)) ? tformat_text_string(4,
			string_constant_7,argument,argument_class,
			declared_class) : Nil;
	    }
	}
	else {
	    gensymed_symbol = argument;
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
	    if (temp_1) {
		argument_type = evaluation_value_type(argument);
		constant_value = evaluation_value_value(argument);
		fixnum_type_p = EQ(argument_type,Qinteger);
		if (class_type_specification_p(type)) {
		    if ( !(EQ(Qhandle,kind) && fixnum_type_p)) {
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
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
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  twrite_beginning_of_wide_string(array_constant,
					  FIX((SI_Long)20L));
				  print_constant(2,constant_value,
					  argument_type);
				  tformat(2,string_constant_8,type);
				  temp = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    else
			temp = Nil;
		}
		else if ( !(SYMBOLP(type) ? EQ(type,Qdatum) || EQ(type,
			argument_type) || EQ(type,Qnumber) && 
			(EQ(argument_type,Qfloat) || EQ(argument_type,
			Qinteger)) : 
			TRUEP(type_specification_type_p(argument,type)))) {
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
			fill_pointer_for_current_wide_string = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				2);
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
			      twrite_beginning_of_wide_string(array_constant_1,
				      FIX((SI_Long)19L));
			      print_constant(2,constant_value,argument_type);
			      tformat(2,string_constant_9,type);
			      temp = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		else
		    temp = Nil;
	    }
	    else
		temp = tformat_text_string(3,string_constant_10,argument,type);
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_11;  /* "~D arguments were required, but ~D arguments were supplied" */

/* REMOTE-PROCEDURE-ARG-TYPE-ERROR-P */
Object remote_procedure_arg_type_error_p(argument_type_descriptions,
	    argument_list)
    Object argument_type_descriptions, argument_list;
{
    Object count_1, temp, restp, index_1, type, description, kind, rest_arg_p;
    Object argument_list_tail, argument, error_text, ab_loop_iter_flag_;
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(166,37);
    count_1 = var_count(argument_type_descriptions);
    if ((SI_Long)0L == IFIX(count_1))
	temp =  ! !TRUEP(argument_list) ? tformat_text_string(3,
		string_constant_11,count_1,length(argument_list)) : Nil;
    else {
	restp = Nil;
	index_1 = FIX((SI_Long)0L);
	type = Nil;
	description = Nil;
	kind = Nil;
	rest_arg_p = Nil;
	argument_list_tail = argument_list;
	argument = Nil;
	error_text = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	gensymed_symbol = IFIX(index_1) * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(argument_type_descriptions,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(argument_type_descriptions,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(argument_type_descriptions,(gensymed_symbol 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description))
	    gensymed_symbol_1 = 
		    getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
	type = gensymed_symbol_1;
	gensymed_symbol = IFIX(index_1) * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(argument_type_descriptions,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(argument_type_descriptions,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(argument_type_descriptions,(gensymed_symbol 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description)) {
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    description = gensymed_symbol_1;
	}
	else
	    description = Nil;
	kind = getf(description,Kkind,_);
	temp = restp;
	if (temp);
	else
	    temp = getf(description,Kall_remaining,_);
	rest_arg_p = temp;
	if ( !TRUEP(ab_loop_iter_flag_))
	    argument_list_tail = CDR(argument_list_tail);
	argument = CAR(argument_list_tail);
	error_text = remote_procedure_arg_type_error_p_1(type,kind,argument);
	if (error_text) {
	    temp = error_text;
	    goto end_1;
	}
	if ( !TRUEP(argument_list_tail) ||  !TRUEP(rest_arg_p) && 
		FIXNUM_EQ(index_1,FIXNUM_SUB1(count_1)))
	    goto end_loop;
	ab_loop_iter_flag_ = Nil;
	restp = rest_arg_p;
	index_1 = restp ? index_1 : FIXNUM_ADD1(index_1);
	goto next_loop;
      end_loop:
	temp =  !(rest_arg_p || FIXNUM_EQ(length(argument_list),count_1)) ?
		 tformat_text_string(3,string_constant_11,count_1,
		length(argument_list)) : Nil;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

static Object Qunsigned_vector_16;  /* unsigned-vector-16 */

/* MAKE-VECTOR-OF-SOME-EVALUATION-VALUES-FOR-REMOTE-PROCEDURE */
Object make_vector_of_some_evaluation_values_for_remote_procedure(list_1)
    Object list_1;
{
    Object vector_size, arg_vector, evaluation_value_or_frame, ab_loop_list_;
    Object ab_loop_iter_flag_, svref_new_value;
    SI_Long index_1;

    x_note_fn_call(166,38);
    vector_size = length(list_1);
    arg_vector = FIXNUM_GT(vector_size,FIX((SI_Long)0L)) ? 
	    allocate_managed_simple_vector(vector_size) : Nil;
    evaluation_value_or_frame = Nil;
    ab_loop_list_ = list_1;
    index_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    evaluation_value_or_frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    svref_new_value = CONSP(evaluation_value_or_frame) && 
	    EQ(M_CDR(evaluation_value_or_frame),Qunsigned_vector_16) ? 
	    M_CAR(evaluation_value_or_frame) : evaluation_value_or_frame;
    ISVREF(arg_vector,index_1) = svref_new_value;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_2(arg_vector,vector_size);
}

/* REMOTE-PROCEDURE-CALL-AUTHORIZED-P */
Object remote_procedure_call_authorized_p(procedure)
    Object procedure;
{
    x_note_fn_call(166,39);
    return item_remotely_callable_p(procedure);
}

static Object string_constant_12;  /* "Error in remote procedure across interface ~NF: ~a" */

static Object string_constant_13;  /* "Error in remote procedure: ~a" */

/* RECEIVE-REMOTE-PROCEDURE-ERROR */
Object receive_remote_procedure_error(icp_socket,error_name,error_level,
	    error_description,error_arglist)
    Object icp_socket, error_name, error_level, error_description;
    Object error_arglist;
{
    Object interface_qm, gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(166,40);
    interface_qm = ISVREF(icp_socket,(SI_Long)5L);
    if (framep_function(interface_qm)) {
	gensymed_symbol = ISVREF(interface_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(interface_qm) ? EQ(ISVREF(interface_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icp_socket,(SI_Long)6L);
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
	temp = TRUEP(Nil);
    if (temp) {
	Suppress_warning_message_header_qm = T;
	if (FIXNUM_LE(error_level,Warning_message_level))
	    give_warning_1(4,error_level,string_constant_12,interface_qm,
		    error_description);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
    else {
	Suppress_warning_message_header_qm = T;
	if (FIXNUM_LE(error_level,Warning_message_level))
	    give_warning_1(3,error_level,string_constant_13,error_description);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

/* GET-COPY-OF-RPD-SPEC */
Object get_copy_of_rpd_spec(rpd_vector,key)
    Object rpd_vector, key;
{
    Object description, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object gensymed_symbol_1, temp;
    SI_Long index_1, ab_loop_bind_, gensymed_symbol;

    x_note_fn_call(166,41);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(var_count(rpd_vector));
    description = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(rpd_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(rpd_vector,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(rpd_vector,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description)) {
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	description = gensymed_symbol_1;
    }
    else
	description = Nil;
    ab_loopvar__2 = icp_cons_1(getf(description,key,_),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* MAKE-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER-FROM-DECLARATION */
Object make_outgoing_remote_procedure_identifier_from_declaration(declaration)
    Object declaration;
{
    Object return_descriptions, return_included_spec, return_excluded_spec;
    Object return_included_system_attribute_spec;
    Object return_include_all_system_attribute_spec;
    Object return_include_all_system_attribute_except_spec, return_kind_spec;
    Object gensymed_symbol_1, temp, return_varargs_p;
    SI_Long gensymed_symbol;

    x_note_fn_call(166,42);
    return_descriptions = ISVREF(declaration,(SI_Long)25L);
    return_included_spec = get_copy_of_rpd_spec(return_descriptions,
	    Kinclude_attributes);
    return_excluded_spec = get_copy_of_rpd_spec(return_descriptions,
	    Kexclude_attributes);
    return_included_system_attribute_spec = 
	    get_copy_of_rpd_spec(return_descriptions,
	    Kinclude_system_attributes);
    return_include_all_system_attribute_spec = 
	    get_copy_of_rpd_spec(return_descriptions,
	    Kinclude_all_system_attributes);
    return_include_all_system_attribute_except_spec = 
	    get_copy_of_rpd_spec(return_descriptions,
	    Kinclude_all_system_attributes_except);
    return_kind_spec = get_copy_of_rpd_spec(return_descriptions,Kkind);
    if ((SI_Long)0L < IFIX(var_count(return_descriptions))) {
	gensymed_symbol = 
		IFIX(FIXNUM_SUB1(var_count(return_descriptions))) * 
		(SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(return_descriptions,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(return_descriptions,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(return_descriptions,(gensymed_symbol >>  -  
		- (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description)) {
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    temp = gensymed_symbol_1;
	}
	else
	    temp = Nil;
	return_varargs_p = getf(temp,Kall_remaining,_);
    }
    else
	return_varargs_p = Nil;
    temp = 
	    make_outgoing_remote_procedure_identifier_with_info(return_included_spec,
	    return_excluded_spec,return_included_system_attribute_spec,
	    return_include_all_system_attribute_spec,
	    return_include_all_system_attribute_except_spec,
	    return_kind_spec,return_varargs_p);
    reclaim_icp_list_1(return_included_spec);
    reclaim_icp_list_1(return_excluded_spec);
    reclaim_icp_list_1(return_included_system_attribute_spec);
    reclaim_icp_list_1(return_include_all_system_attribute_spec);
    reclaim_icp_list_1(return_include_all_system_attribute_except_spec);
    reclaim_icp_list_1(return_kind_spec);
    return VALUES_1(temp);
}

static Object string_constant_14;  /* "Argument error while calling remote procedure ~NF: ~a" */

static Object string_constant_15;  /* "~NF is not able to receive remote procedure calls to ~NF.  ~
				    *               Either the ICP connection has broken, or the remote system is ~
				    *               not running."
				    */

static Object string_constant_16;  /* "Cannot execute remote procedure call to ~NF across ~NF, ~
				    *               because of a problem in its arguments: ~A"
				    */

/* CALL-REMOTE-PROCEDURE */
Object call_remote_procedure(remote_procedure_declaration,icp_interface,
	    argument_list,calling_code_body)
    Object remote_procedure_declaration, icp_interface, argument_list;
    Object calling_code_body;
{
    Object argument_error_message_qm, icp_socket_qm;
    Object transform_error_message_qm, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(166,43);
    argument_error_message_qm = Nil;
    icp_socket_qm = Nil;
    transform_error_message_qm = Nil;
    argument_error_message_qm = 
	    remote_procedure_arg_type_error_p(ISVREF(remote_procedure_declaration,
	    (SI_Long)24L),argument_list);
    if (argument_error_message_qm) {
	reclaim_rpc_argument_list(argument_list,Nil);
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
		      tformat(3,string_constant_14,
			      remote_procedure_declaration,
			      argument_error_message_qm);
		      reclaim_text_string(argument_error_message_qm);
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
	return make_error_text(text_string,snapshots);
    }
    else {
	icp_socket_qm = icp_socket_of_interface_object(icp_interface);
	if ( !TRUEP(icp_socket_qm) ||  
		!TRUEP(icp_connection_open_p(icp_socket_qm)) || 
		icp_connection_being_shutdown_qm(icp_socket_qm)) {
	    reclaim_rpc_argument_list(argument_list,Nil);
	    return tformat_stack_error_text_string(3,string_constant_15,
		    icp_interface,remote_procedure_declaration);
	}
	else {
	    temp = 
		    remote_procedure_argument_description_function(remote_procedure_declaration);
	    transform_error_message_qm = 
		    transform_rpc_argument_or_result_list(7,
		    remote_procedure_declaration,argument_list,temp,
		    icp_socket_qm,icp_interface,ISVREF(calling_code_body,
		    (SI_Long)10L),T);
	    if (transform_error_message_qm)
		return tformat_stack_error_text_string(4,
			string_constant_16,remote_procedure_declaration,
			icp_interface,transform_error_message_qm);
	    else {
		call_remote_procedure_after_checks(calling_code_body,
			argument_list,icp_socket_qm,
			remote_procedure_declaration,icp_interface);
		return VALUES_1(Nil);
	    }
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(System_defined_rpcs, Qsystem_defined_rpcs);

Object System_defined_rpc_prop = UNBOUND;

Object The_type_description_of_system_rpc_instance = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_system_rpc_instances, Qchain_of_available_system_rpc_instances);

DEFINE_VARIABLE_WITH_SYMBOL(System_rpc_instance_count, Qsystem_rpc_instance_count);

Object Chain_of_available_system_rpc_instances_vector = UNBOUND;

/* SYSTEM-RPC-INSTANCE-STRUCTURE-MEMORY-USAGE */
Object system_rpc_instance_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(166,44);
    temp = System_rpc_instance_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SYSTEM-RPC-INSTANCE-COUNT */
Object outstanding_system_rpc_instance_count()
{
    Object def_structure_system_rpc_instance_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(166,45);
    gensymed_symbol = IFIX(System_rpc_instance_count);
    def_structure_system_rpc_instance_variable = 
	    Chain_of_available_system_rpc_instances;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_system_rpc_instance_variable))
	goto end_loop;
    def_structure_system_rpc_instance_variable = 
	    ISVREF(def_structure_system_rpc_instance_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SYSTEM-RPC-INSTANCE-1 */
Object reclaim_system_rpc_instance_1(system_rpc_instance)
    Object system_rpc_instance;
{
    Object temp, svref_arg_2;

    x_note_fn_call(166,46);
    inline_note_reclaim_cons(system_rpc_instance,Nil);
    temp = ISVREF(Chain_of_available_system_rpc_instances_vector,
	    IFIX(Current_thread_index));
    SVREF(system_rpc_instance,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_system_rpc_instances_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = system_rpc_instance;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SYSTEM-RPC-INSTANCE */
Object reclaim_structure_for_system_rpc_instance(system_rpc_instance)
    Object system_rpc_instance;
{
    x_note_fn_call(166,47);
    return reclaim_system_rpc_instance_1(system_rpc_instance);
}

static Object Qg2_defstruct_structure_name_system_rpc_instance_g2_struct;  /* g2-defstruct-structure-name::system-rpc-instance-g2-struct */

/* MAKE-PERMANENT-SYSTEM-RPC-INSTANCE-STRUCTURE-INTERNAL */
Object make_permanent_system_rpc_instance_structure_internal()
{
    Object def_structure_system_rpc_instance_variable;
    Object defstruct_g2_system_rpc_instance_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(166,48);
    def_structure_system_rpc_instance_variable = Nil;
    atomic_incff_symval(Qsystem_rpc_instance_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_system_rpc_instance_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_system_rpc_instance_variable = the_array;
	SVREF(defstruct_g2_system_rpc_instance_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_system_rpc_instance_g2_struct;
	def_structure_system_rpc_instance_variable = 
		defstruct_g2_system_rpc_instance_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_system_rpc_instance_variable);
}

/* MAKE-SYSTEM-RPC-INSTANCE-1 */
Object make_system_rpc_instance_1(system_rpc_instance_system_rpc,
	    system_rpc_instance_icp_socket,system_rpc_instance_identifier_qm)
    Object system_rpc_instance_system_rpc, system_rpc_instance_icp_socket;
    Object system_rpc_instance_identifier_qm;
{
    Object def_structure_system_rpc_instance_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(166,49);
    def_structure_system_rpc_instance_variable = 
	    ISVREF(Chain_of_available_system_rpc_instances_vector,
	    IFIX(Current_thread_index));
    if (def_structure_system_rpc_instance_variable) {
	svref_arg_1 = Chain_of_available_system_rpc_instances_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_system_rpc_instance_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_system_rpc_instance_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_system_rpc_instance_g2_struct;
    }
    else
	def_structure_system_rpc_instance_variable = 
		make_permanent_system_rpc_instance_structure_internal();
    inline_note_allocate_cons(def_structure_system_rpc_instance_variable,Nil);
    SVREF(def_structure_system_rpc_instance_variable,FIX((SI_Long)1L)) = 
	    system_rpc_instance_system_rpc;
    SVREF(def_structure_system_rpc_instance_variable,FIX((SI_Long)2L)) = 
	    system_rpc_instance_icp_socket;
    SVREF(def_structure_system_rpc_instance_variable,FIX((SI_Long)3L)) = 
	    system_rpc_instance_identifier_qm;
    return VALUES_1(def_structure_system_rpc_instance_variable);
}

static Object Qwrong_number_of_arguments;  /* wrong-number-of-arguments */

static Object string_constant_17;  /* "Error while beginning RPC call to ~ND: wanted ~NV args, got ~NV" */

static Object Qargument_type_mismatch;  /* argument-type-mismatch */

static Object string_constant_18;  /* "Error while beginning RPC call to ~ND: arg ~NV should be of type ~NT" */

/* CALL-SYSTEM-DEFINED-RPC */
Object call_system_defined_rpc(icp_socket,system_rpc,rpc_arg_list,
	    remote_procedure_identifier_qm)
    Object icp_socket, system_rpc, rpc_arg_list;
    Object remote_procedure_identifier_qm;
{
    Object temp, temp_1, argument_list, argument_types, rpc_arg, ab_loop_list_;
    Object lisp_arg, arg_type, ab_loop_iter_flag_, gensymed_symbol_1, thing;
    Object apply_args;
    SI_Long index_1, gensymed_symbol;

    x_note_fn_call(166,50);
    temp = length(rpc_arg_list);
    if ( !FIXNUM_EQ(temp,var_count(ISVREF(system_rpc,(SI_Long)2L)))) {
	temp = ISVREF(system_rpc,(SI_Long)1L);
	temp_1 = length(rpc_arg_list);
	remote_procedure_error(icp_socket,Qwrong_number_of_arguments,
		tformat_text_string(4,string_constant_17,temp,temp_1,
		var_count(ISVREF(system_rpc,(SI_Long)2L))),
		remote_procedure_identifier_qm);
    }
    argument_list = Qnil;
    argument_types = ISVREF(system_rpc,(SI_Long)2L);
    rpc_arg = Nil;
    ab_loop_list_ = rpc_arg_list;
    lisp_arg = Nil;
    index_1 = (SI_Long)0L;
    arg_type = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    rpc_arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    lisp_arg = rpc_arg;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(argument_types,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(argument_types,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(argument_types,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description))
	gensymed_symbol_1 = 
		getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
    arg_type = gensymed_symbol_1;
    argument_list = eval_cons_1(lisp_arg,argument_list);
    if ( !TRUEP(type_specification_type_p(lisp_arg,arg_type))) {
	thing = Nil;
	ab_loop_list_ = argument_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	thing = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	thing = reclaim_managed_number_or_value_function(thing);
	goto next_loop_1;
      end_loop_1:;
	reclaim_eval_list_1(argument_list);
	reclaim_icp_list_1(rpc_arg_list);
	remote_procedure_error(icp_socket,Qargument_type_mismatch,
		tformat_text_string(4,string_constant_18,ISVREF(system_rpc,
		(SI_Long)1L),FIX(index_1),arg_type),
		remote_procedure_identifier_qm);
	return VALUES_1(Nil);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    reclaim_icp_list_1(rpc_arg_list);
    apply_args = nreverse(argument_list);
    temp = ISVREF(system_rpc,(SI_Long)1L);
    APPLY_2(temp,make_system_rpc_instance_1(system_rpc,icp_socket,
	    remote_procedure_identifier_qm),apply_args);
    reclaim_eval_list_1(apply_args);
    return VALUES_1(Qnil);
}

static Object Qsend_icp_resumable_rpc_return_values;  /* send-icp-resumable-rpc-return-values */

static Object Qreclaim_after_rpc_return_values;  /* reclaim-after-rpc-return-values */

/* RETURN-FROM-SYSTEM-DEFINED-RPC */
Object return_from_system_defined_rpc(system_rpc_instance,rpc_value_list)
    Object system_rpc_instance, rpc_value_list;
{
    Object identifier_qm, system_rpc, return_types, evaluation_value;
    Object ab_loop_list_, return_value_type, ab_loop_list__1, socket_1;
    Object output_port, tag, temp, info_list, varargs_p, temp_1;

    x_note_fn_call(166,51);
    identifier_qm = ISVREF(system_rpc_instance,(SI_Long)3L);
    if ( !TRUEP(identifier_qm))
	return VALUES_1(Nil);
    system_rpc = ISVREF(system_rpc_instance,(SI_Long)1L);
    return_types = ISVREF(system_rpc,(SI_Long)3L);
    evaluation_value = Nil;
    ab_loop_list_ = rpc_value_list;
    return_value_type = Nil;
    ab_loop_list__1 = return_types;
  nil:
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    evaluation_value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    return_value_type = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    goto next_loop;
  end_loop:
    socket_1 = ISVREF(system_rpc_instance,(SI_Long)2L);
    output_port = ISVREF(socket_1,(SI_Long)4L);
    tag = ISVREF(identifier_qm,(SI_Long)1L);
    temp = ISVREF(ISVREF(ISVREF(identifier_qm,(SI_Long)8L),(SI_Long)1L),
	    (SI_Long)1L);
    info_list = CDR(temp);
    temp = ISVREF(ISVREF(ISVREF(identifier_qm,(SI_Long)8L),(SI_Long)1L),
	    (SI_Long)1L);
    varargs_p = CAR(temp);
    reclaim_system_rpc_instance_1(system_rpc_instance);
    transform_system_rpc_arguments(socket_1,rpc_value_list,info_list,Nil,
	    varargs_p);
    temp = ISVREF(ISVREF(output_port,(SI_Long)2L),(SI_Long)21L);
    temp_1 = ISVREF(ISVREF(output_port,(SI_Long)2L),(SI_Long)22L);
    if (IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)8L)
	send_or_enqueue_icp_write_task(output_port,FIX((SI_Long)6L),
		SYMBOL_FUNCTION(Qsend_icp_resumable_rpc_return_values),
		icp_list_2(tag,rpc_value_list),
		SYMBOL_FUNCTION(Qreclaim_after_rpc_return_values),
		icp_cons_1(rpc_value_list,Nil));
    else {
	send_icp_rpc_return_values_deferring_objects(output_port,tag,
		rpc_value_list);
	reclaim_after_rpc_return_values(rpc_value_list);
    }
    return VALUES_1(Qnil);
}

/* SYSTEM-RPC-ERROR */
Object system_rpc_error(system_rpc_instance,error_name,error_description)
    Object system_rpc_instance, error_name, error_description;
{
    x_note_fn_call(166,52);
    return remote_procedure_error(ISVREF(system_rpc_instance,(SI_Long)2L),
	    error_name,error_description,ISVREF(system_rpc_instance,
	    (SI_Long)3L));
}

static Object Qfloat_array;        /* float-array */

/* G2-API-TEST-1-SYSTEM-RPC-INTERNAL */
Object g2_api_test_1_system_rpc_internal(rpc_instance,arg1)
    Object rpc_instance, arg1;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, result_list, managed_float;
    double res;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(166,53);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	res = 3.0 * DFLOAT_ISAREF_1(arg1,(SI_Long)0L);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,res);
	result_list = gensym_cons_1(new_float,Nil);
	return_from_system_defined_rpc(rpc_instance,result_list);
	managed_float = CAR(result_list);
	reclaim_managed_simple_float_array_of_length_1(managed_float);
	reclaim_gensym_list_1(result_list);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

static Object string_constant_19;  /* "::" */

/* EVALUATE-PROCEDURE-OR-METHOD-DESIGNATION */
Object evaluate_procedure_or_method_designation(name)
    Object name;
{
    Object current_computation_flags, debugging_reset, temp, symbol_name_1;
    Object position_of_qualifier_qm, qualifying_class, method_declaration_name;
    Declare_special(2);

    x_note_fn_call(166,54);
    current_computation_flags = Current_computation_flags;
    debugging_reset = T;
    PUSH_SPECIAL_WITH_SYMBOL(Debugging_reset,Qdebugging_reset,debugging_reset,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	      0);
	Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
		(SI_Long)16L);
	temp = evaluate_designation(name,Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    if (temp);
    else {
	symbol_name_1 = gensym_symbol_name(name);
	position_of_qualifier_qm = gensym_search_simple(string_constant_19,
		symbol_name_1);
	if (position_of_qualifier_qm) {
	    qualifying_class = intern_gensym_string(1,
		    copy_partial_gensym_string(symbol_name_1,
		    position_of_qualifier_qm));
	    temp = FIX(IFIX(position_of_qualifier_qm) + (SI_Long)2L);
	    method_declaration_name = intern_gensym_string(1,
		    copy_gensym_string_portion(symbol_name_1,temp,
		    gensym_string_length(symbol_name_1)));
	    temp = 
		    get_specific_methods_for_class_or_superior_class(method_declaration_name,
		    qualifying_class);
	    temp = CAR(temp);
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Prefer_kb_procedures_to_system_defined_p, Qprefer_kb_procedures_to_system_defined_p);

/* G2-PREFER-KB-PROCEDURES-TO-SYSTEM-DEFINED */
Object g2_prefer_kb_procedures_to_system_defined(evaluation_truth_value)
    Object evaluation_truth_value;
{
    x_note_fn_call(166,55);
    Prefer_kb_procedures_to_system_defined_p = 
	    evaluation_truth_value_is_true_p(evaluation_truth_value);
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    return VALUES_1(Nil);
}

static Object Kstack_error;        /* :stack-error */

/* G2-PREFER-KB-PROCEDURES-TO-SYSTEM-DEFINED-SYSTEM-RPC-INTERNAL */
Object g2_prefer_kb_procedures_to_system_defined_system_rpc_internal(gensymed_symbol,
	    prefer)
    Object gensymed_symbol, prefer;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(166,56);
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
	    gensymed_symbol_1 = 
		    g2_prefer_kb_procedures_to_system_defined(prefer);
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

static Object Qprocedure;          /* procedure */

static Object Qsystem_defined_rpc;  /* system-defined-rpc */

static Object string_constant_20;  /* "call" */

static Object string_constant_21;  /* "start" */

static Object string_constant_22;  /* "Cannot ~A ~A, since: ~A" */

static Object string_constant_23;  /* "Argument error ~Aing ~A:  ~A" */

static Object string_constant_24;  /* "Cannot ~A ~A, since no procedure by that name exists." */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object string_constant_25;  /* "Cannot ~A ~A, since it named the constant ~NC instead of a procedure." */

static Object string_constant_26;  /* "Cannot ~A ~A, since it names ~A~A, instead of a procedure." */

static Object string_constant_27;  /* "Cannot ~A ~A, since this interface is not authorized to start remote procedure calls." */

static Object string_constant_28;  /* "Cannot ~A ~A, since it is not active or has a status other than OK." */

static Object string_constant_29;  /* "Cannot ~A ~A.  ~A" */

/* CHECK-THAT-REMOTE-PROCEDURE-CAN-BE-STARTED-OR-CALLED */
Object check_that_remote_procedure_can_be_started_or_called(icp_socket,
	    name,argument_list,remote_procedure_identifier_qm)
    Object icp_socket, name, argument_list, remote_procedure_identifier_qm;
{
    Object procedure, method_or_error_string_qm, current_computation_frame;
    Object system_rpc_qm, argument_error_qm, how_invoked, temp;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, sub_class_bit_vector, format_string;
    Object arg1, arg2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(166,57);
    procedure = Nil;
    method_or_error_string_qm = Nil;
    current_computation_frame = Inference_engine_parameters;
    system_rpc_qm =  !(IFIX(ISVREF(icp_socket,(SI_Long)22L)) >= 
	    (SI_Long)8L ? Prefer_kb_procedures_to_system_defined_p && 
	    get_instance_with_name_if_any(Qprocedure,name) : TRUEP(T)) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
	    Qsystem_defined_rpc) : Nil;
    argument_error_qm = Nil;
    how_invoked = remote_procedure_identifier_qm ? string_constant_20 : 
	    string_constant_21;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      if (system_rpc_qm) {
	  procedure = system_rpc_qm;
	  if (Rpc_argument_list_error)
	      result = VALUES_2(string_constant_22,Rpc_argument_list_error);
	  else {
	      temp = method_or_error_string_qm;
	      if (temp);
	      else
		  temp = procedure;
	      procedure = temp;
	      argument_error_qm = 
		      get_procedure_argument_list_error_if_any(procedure,
		      argument_list,icp_socket);
	      if (argument_error_qm)
		  result = VALUES_2(string_constant_23,argument_error_qm);
	      else
		  result = VALUES_1(Nil);
	  }
      }
      else {
	  procedure = evaluate_procedure_or_method_designation(name);
	  if ( !TRUEP(procedure))
	      result = VALUES_1(string_constant_24);
	  else {
	      temp_1 = SIMPLE_VECTOR_P(procedure) ? EQ(ISVREF(procedure,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_temporary_constant_g2_struct) 
		      : TRUEP(Qnil);
	      if (temp_1);
	      else {
		  gensymed_symbol = procedure;
		  temp_1 = FIXNUMP(gensymed_symbol);
		  if (temp_1);
		  else
		      temp_1 = 
			      INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L ? 
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
		      temp_1 = 
			      INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
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
			  key_hash_value = 
				  SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp);
			  MVS_2(result,succ,marked);
			next_loop_2:
			  if ( !TRUEP(marked))
			      goto end_loop_1;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
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
	      }
	      if (temp_1)
		  result = VALUES_2(string_constant_25,procedure);
	      else {
		  sub_class_bit_vector = ISVREF(ISVREF(procedure,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Procedure_class_description,
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
		  if ( !temp_1) {
		      temp_2 = supply_a_or_an(ISVREF(ISVREF(procedure,
			      (SI_Long)1L),(SI_Long)1L));
		      temp = ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)1L);
		      result = VALUES_3(string_constant_26,temp_2,temp);
		  }
		  else if ( 
			  !TRUEP(remote_procedure_call_authorized_p(procedure)))
		      result = VALUES_1(string_constant_27);
		  else {
		      temp = ISVREF(procedure,(SI_Long)8L);
		      if ( !( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
			      (IFIX(ISVREF(procedure,(SI_Long)5L)) & 
			      (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
			      && (SI_Long)0L != (IFIX(ISVREF(procedure,
			      (SI_Long)4L)) & (SI_Long)16777216L) &&  
			      !((SI_Long)0L != (IFIX(ISVREF(procedure,
			      (SI_Long)4L)) & (SI_Long)8192L)))))
			  result = VALUES_1(string_constant_28);
		      else {
			  sub_class_bit_vector = ISVREF(ISVREF(procedure,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Method_declaration_class_description,
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
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_2 = gensymed_symbol_2 << 
				      gensymed_symbol_3;
			      gensymed_symbol_1 = gensymed_symbol_1 & 
				      gensymed_symbol_2;
			      temp_1 = (SI_Long)0L < gensymed_symbol_1;
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  if (temp_1) {
			      method_or_error_string_qm = 
				      get_specific_method_for_arg_list_given_name(name,
				      argument_list,icp_socket);
			      temp_1 = 
				      TRUEP(text_string_p(method_or_error_string_qm));
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  if (temp_1)
			      result = VALUES_2(string_constant_29,
				      method_or_error_string_qm);
			  else if (Rpc_argument_list_error)
			      result = VALUES_2(string_constant_22,
				      Rpc_argument_list_error);
			  else {
			      temp = method_or_error_string_qm;
			      if (temp);
			      else
				  temp = procedure;
			      procedure = temp;
			      argument_error_qm = 
				      get_procedure_argument_list_error_if_any(procedure,
				      argument_list,icp_socket);
			      if (argument_error_qm)
				  result = VALUES_2(string_constant_23,
					  argument_error_qm);
			      else
				  result = VALUES_1(Qnil);
			  }
		      }
		  }
	      }
	  }
      }
      MVS_3(result,format_string,arg1,arg2);
      if (format_string) {
	  remote_procedure_error(icp_socket,Qerror,tformat_text_string(5,
		  format_string,how_invoked,name,arg1,arg2),
		  remote_procedure_identifier_qm);
	  if (SIMPLE_VECTOR_P(procedure) && EQ(ISVREF(procedure,
		  (SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	      reclaim_temporary_constant_1(procedure);
	  gensymed_symbol = procedure;
	  temp_1 = FIXNUMP(gensymed_symbol);
	  if (temp_1);
	  else
	      temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		      (SI_Long)0L ? 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		      (SI_Long)1L : TRUEP(Qnil);
	  if (temp_1);
	  else
	      temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
		      (SI_Long)0L ? 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		      (SI_Long)1L : TRUEP(Qnil);
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
		next_loop_3:
		  if (level < ab_loop_bind_)
		      goto end_loop_3;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_4:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_2,temp);
		  MVS_2(result,succ,marked);
		next_loop_5:
		  if ( !TRUEP(marked))
		      goto end_loop_4;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_2,temp);
		  MVS_2(result,succ,marked);
		  goto next_loop_5;
		end_loop_4:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? TRUEP(ISVREF(curr,(SI_Long)3L)) :
			   TRUEP(Nil)) : TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      reclaim_evaluation_value(procedure);
	  if (argument_error_qm)
	      reclaim_text_string(argument_error_qm);
	  temp = Nil;
      }
      else
	  temp = procedure;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qmethod_declaration;  /* method-declaration */

static Object Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;  /* g2-defstruct-structure-name::receiving-resumable-object-g2-struct */

/* PLAUSIBLE-REMOTE-METHOD-CALL-P */
Object plausible_remote_method_call_p(remote_procedure_name_symbol,
	    rpc_argument_list)
    Object remote_procedure_name_symbol, rpc_argument_list;
{
    Object thing, temp;

    x_note_fn_call(166,58);
    if (get_instance_with_name_if_any(Qmethod_declaration,
	    remote_procedure_name_symbol)) {
	thing = CAR(rpc_argument_list);
	temp = SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct) 
		? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qicp;                /* icp */

static Object Qg2_defstruct_structure_name_system_rpc_g2_struct;  /* g2-defstruct-structure-name::system-rpc-g2-struct */

static Object Qreceive_start_or_call_remote_procedure_1;  /* receive-start-or-call-remote-procedure-1 */

/* RECEIVE-START-OR-CALL-REMOTE-PROCEDURE */
Object receive_start_or_call_remote_procedure(icp_socket,procedure_name,
	    argument_list,remote_procedure_identifier_qm)
    Object icp_socket, procedure_name, argument_list;
    Object remote_procedure_identifier_qm;
{
    Object icp_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object initial_rpc_frame_serial_number, rpc_argument_list_error;
    Object procedure_qm_1, structure_being_reclaimed;
    Object def_structure_schedule_task_variable, svref_new_value, task, ctask;
    Object p, v, q, temp_1;
    char g2_p;
    double aref_new_value;
    Declare_special(2);

    x_note_fn_call(166,59);
    icp_pop_store = Nil;
    cons_1 = argument_list;
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
    argument_list = next_cons;
    initial_rpc_frame_serial_number = icp_pop_store;
    icp_pop_store = Nil;
    cons_1 = argument_list;
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
    argument_list = next_cons;
    rpc_argument_list_error = icp_pop_store;
    PUSH_SPECIAL_WITH_SYMBOL(Rpc_argument_list_error,Qrpc_argument_list_error,rpc_argument_list_error,
	    1);
      procedure_qm_1 = 
	      check_that_remote_procedure_can_be_started_or_called(icp_socket,
	      procedure_name,argument_list,remote_procedure_identifier_qm);
      if ( !TRUEP(procedure_qm_1)) {
	  if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(Rpc_argument_list_error) != 
		  (SI_Long)0L)
	      reclaim_wide_string(Rpc_argument_list_error);
	  reclaim_unprocessed_rpc_argument_list(2,argument_list,
		  initial_rpc_frame_serial_number);
      }
      else if (SIMPLE_VECTOR_P(procedure_qm_1) && EQ(ISVREF(procedure_qm_1,
	      (SI_Long)0L),Qg2_defstruct_structure_name_system_rpc_g2_struct))
	  call_system_defined_rpc(icp_socket,procedure_qm_1,argument_list,
		  remote_procedure_identifier_qm);
      else if (Inside_breakpoint_p) {
	  if (Nil) {
	      if (EQ(Nil,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(Nil,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(Nil);
	      inline_note_reclaim_cons(Nil,Nil);
	      structure_being_reclaimed = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
		SVREF(Nil,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(Nil,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = Nil;
	  }
	  def_structure_schedule_task_variable = 
		  ISVREF(Chain_of_available_schedule_tasks_vector,
		  IFIX(Current_thread_index));
	  if (def_structure_schedule_task_variable) {
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = 
		      ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	      SVREF(temp,svref_arg_2) = svref_new_value;
	      SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) 
		      = Qg2_defstruct_structure_name_schedule_task_g2_struct;
	  }
	  else
	      def_structure_schedule_task_variable = 
		      make_permanent_schedule_task_structure_internal();
	  inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	  SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	  SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	  task = def_structure_schedule_task_variable;
	  temp = ISVREF(task,(SI_Long)1L);
	  aref_new_value = -1.0;
	  DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	  SVREF(task,FIX((SI_Long)4L)) = Highest_system_priority;
	  SVREF(task,FIX((SI_Long)5L)) = Nil;
	  SVREF(task,FIX((SI_Long)9L)) = Nil;
	  SVREF(task,FIX((SI_Long)10L)) = Nil;
	  g2_p =  !TRUEP(Nil);
	  SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	  temp = ISVREF(task,(SI_Long)1L);
	  aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		  Current_real_time,(SI_Long)0L);
	  DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	  SVREF(task,FIX((SI_Long)7L)) = 
		  Qreceive_start_or_call_remote_procedure_1;
	  temp = SYMBOL_FUNCTION(Qreceive_start_or_call_remote_procedure_1);
	  SVREF(task,FIX((SI_Long)8L)) = temp;
	  ISVREF(task,(SI_Long)12L) = FIX((SI_Long)4L);
	  SVREF(task,FIX((SI_Long)13L)) = procedure_qm_1;
	  SVREF(task,FIX((SI_Long)14L)) = argument_list;
	  SVREF(task,FIX((SI_Long)15L)) = icp_socket;
	  SVREF(task,FIX((SI_Long)16L)) = remote_procedure_identifier_qm;
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
      }
      else
	  receive_start_or_call_remote_procedure_1(procedure_qm_1,
		  argument_list,icp_socket,remote_procedure_identifier_qm);
      temp_1 = reclaim_frame_serial_number(initial_rpc_frame_serial_number);
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

static Object Kerror_string;       /* :error-string */

static Object Qrpc_error;          /* rpc-error */

static Object string_constant_30;  /* "Error while beginning RPC start of ~NF: ~NW" */

/* RECEIVE-START-OR-CALL-REMOTE-PROCEDURE-1 */
Object receive_start_or_call_remote_procedure_1(procedure,argument_list,
	    icp_socket,remote_procedure_identifier_qm)
    Object procedure, argument_list, icp_socket;
    Object remote_procedure_identifier_qm;
{
    Object arg_vector, arg_vector_size, current_computation_frame;
    Object remote_procedure_call, new_invocation_or_error_text, new_invocation;
    Declare_special(1);
    Object result;

    x_note_fn_call(166,60);
    result = make_vector_of_some_evaluation_values_for_remote_procedure(argument_list);
    MVS_2(result,arg_vector,arg_vector_size);
    reclaim_icp_list_1(argument_list);
    current_computation_frame = procedure;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      remote_procedure_call = T ? 
	      make_incoming_remote_procedure_call(remote_procedure_identifier_qm,
	      icp_socket) : Nil;
      new_invocation_or_error_text = remote_procedure_call ? 
	      generate_procedure_and_code_body_invocation_in_place(procedure,
	      remote_procedure_call,arg_vector,
	      FIXNUM_SUB1(arg_vector_size),arg_vector_size,Nil,Nil,
	      Kerror_string,Nil,Nil,Nil) : 
	      start_procedure_invocation_in_place(procedure,Nil,Nil,
	      arg_vector,FIXNUM_SUB1(arg_vector_size),arg_vector_size,Nil,
	      Nil,Kerror_string,Nil,Nil);
      if (error_text_p(new_invocation_or_error_text)) {
	  remote_procedure_error(icp_socket,Qrpc_error,
		  tformat_text_string(3,string_constant_30,procedure,
		  new_invocation_or_error_text),
		  remote_procedure_identifier_qm);
	  reclaim_error_text(new_invocation_or_error_text);
	  new_invocation = Nil;
      }
      else
	  new_invocation = new_invocation_or_error_text;
      if (arg_vector)
	  reclaim_managed_simple_vector(arg_vector);
      if (new_invocation) {
	  if (remote_procedure_call) {
	      if (remote_procedure_identifier_qm)
		  SVREF(remote_procedure_identifier_qm,FIX((SI_Long)4L)) = 
			  remote_procedure_call;
	      else
		  register_remote_procedure_call_for_start(remote_procedure_call,
			  icp_socket);
	      wake_up_code_body_invocation(new_invocation);
	  }
	  result = write_major_trace_for_rpc_call_or_start(new_invocation,
		  remote_procedure_identifier_qm);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_remote_procedure_call_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-call-g2-struct */

/* FIND-REMOTE-PROCEDURE-CALL-FOR-CODE-BODY-INVOCATION */
Object find_remote_procedure_call_for_code_body_invocation(code_body_invocation)
    Object code_body_invocation;
{
    Object caller_qm;

    x_note_fn_call(166,61);
    caller_qm = ISVREF(code_body_invocation,(SI_Long)12L);
  next_loop:
    if ( !TRUEP(caller_qm))
	goto end_loop;
    if (SIMPLE_VECTOR_P(caller_qm) && EQ(ISVREF(caller_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct))
	return VALUES_1(caller_qm);
    caller_qm = ISVREF(caller_qm,(SI_Long)12L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-ICP-INTERFACE-FOR-REMOTE-PROCEDURE-CALL */
Object get_icp_interface_for_remote_procedure_call(remote_procedure_call,
	    stack_eval_p)
    Object remote_procedure_call, stack_eval_p;
{
    Object interface_qm, gensymed_symbol, x, y, xa, ya, interface_1;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    char temp;

    x_note_fn_call(166,62);
    interface_qm = ISVREF(remote_procedure_call,(SI_Long)25L);
    if (interface_qm) {
	gensymed_symbol = ISVREF(interface_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(interface_qm) ? EQ(ISVREF(interface_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(remote_procedure_call,(SI_Long)9L);
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
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(interface_qm);
    else {
	interface_1 = 
		find_network_interface_for_icp_socket(ISVREF(remote_procedure_call,
		(SI_Long)24L),stack_eval_p);
	SVREF(remote_procedure_call,FIX((SI_Long)25L)) = interface_1;
	frame_serial_number_setf_arg = ISVREF(interface_1,(SI_Long)3L);
	old = ISVREF(remote_procedure_call,(SI_Long)9L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(remote_procedure_call,FIX((SI_Long)9L)) = svref_new_value;
	return VALUES_1(interface_1);
    }
}

static Object string_constant_31;  /* "The current procedure was not invoked via RPC" */

/* G2-CURRENT-REMOTE-INTERFACE-LISP-SIDE */
Object g2_current_remote_interface_lisp_side()
{
    Object temp, top_of_stack, message_1;

    x_note_fn_call(166,63);
    temp = 
	    find_remote_procedure_call_for_code_body_invocation(Current_computation_instance);
    if (temp);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_31);
	temp = raw_stack_error_named_error(top_of_stack,message_1);
    }
    return get_icp_interface_for_remote_procedure_call(temp,T);
}

static Object string_constant_32;  /* "Calling procedure " */

static Object string_constant_33;  /* "Starting procedure " */

static Object array_constant_2;    /* # */

/* WRITE-MAJOR-TRACE-FOR-RPC-CALL-OR-START */
Object write_major_trace_for_rpc_call_or_start(new_invocation,call_p)
    Object new_invocation, call_p;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(166,64);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  twrite_general_string(call_p ? string_constant_32 : 
			  string_constant_33);
		  write_procedure_invocation_instance_from_slot(ISVREF(new_invocation,
			  (SI_Long)11L),Nil);
		  twrite_beginning_of_wide_string(array_constant_2,
			  FIX((SI_Long)19L));
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* REMOTE-PROCEDURE-ERROR */
Object remote_procedure_error(icp_socket,name,error_string,
	    remote_procedure_identifier_qm)
    Object icp_socket, name, error_string, remote_procedure_identifier_qm;
{
    Object temp;

    x_note_fn_call(166,65);
    temp = remote_procedure_error_1(icp_socket,name,FIX((SI_Long)1L),
	    error_string,remote_procedure_identifier_qm,name);
    return VALUES_1(temp);
}

static Object Qcopy;               /* copy */

static Object Qsend_icp_resumable_rpc_error_to_caller;  /* send-icp-resumable-rpc-error-to-caller */

static Object Qsend_icp_resumable_rpc_error;  /* send-icp-resumable-rpc-error */

static Object Qpropagate_error_to_remote_caller_reclaim;  /* propagate-error-to-remote-caller-reclaim */

/* REMOTE-PROCEDURE-ERROR-1 */
Object remote_procedure_error_1(icp_socket,error_name,error_level,
	    error_message,remote_procedure_identifier_qm,error_1)
    Object icp_socket, error_name, error_level, error_message;
    Object remote_procedure_identifier_qm, error_1;
{
    Object remote_procedure_index_qm, output_port, temp, temp_1;
    Object error_arguments, args, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
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

    x_note_fn_call(166,66);
    if ( !TRUEP(icp_socket)) {
	propagate_error_to_remote_caller_reclaim(error_message,Nil);
	return VALUES_1(Nil);
    }
    remote_procedure_index_qm = remote_procedure_identifier_qm ? 
	    ISVREF(remote_procedure_identifier_qm,(SI_Long)1L) : Nil;
    output_port = ISVREF(icp_socket,(SI_Long)4L);
    temp = ISVREF(icp_socket,(SI_Long)21L);
    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
    if (IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)8L) {
	if (error_1 && SYMBOLP(error_1)) {
	    error_name = error_1;
	    error_1 = Nil;
	}
	if (error_1) {
	    temp = error_1;
	    error_arguments = icp_cons_1(icp_list_4(Qcopy,temp,
		    make_remote_procedure_item_info(Nil,Nil,Nil,T,Nil,Nil),
		    Nil),Nil);
	}
	else {
	    temp = icp_cons_1(Qvalue,error_name);
	    error_arguments = icp_list_2(temp,icp_cons_1(Qvalue,
		    copy_text_string(error_message)));
	}
	args = icp_list_4(error_name,error_level,error_message,
		error_arguments);
	temp = remote_procedure_identifier_qm ? 
		nconc2(icp_list_2(remote_procedure_index_qm,Nil),args) : args;
	return send_or_enqueue_icp_write_task(output_port,FIX((SI_Long)6L),
		remote_procedure_identifier_qm ? 
		SYMBOL_FUNCTION(Qsend_icp_resumable_rpc_error_to_caller) : 
		SYMBOL_FUNCTION(Qsend_icp_resumable_rpc_error),temp,
		SYMBOL_FUNCTION(Qpropagate_error_to_remote_caller_reclaim),
		icp_list_2(error_message,error_arguments));
    }
    else {
	current_icp_port = output_port;
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
				    if (remote_procedure_identifier_qm)
					send_icp_rpc_error_to_caller(remote_procedure_index_qm,
						Nil,error_name,error_level,
						error_message,Nil);
				    else
					send_icp_rpc_error(error_name,
						error_level,error_message,Nil);
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
	return propagate_error_to_remote_caller_reclaim(error_message,Nil);
    }
}

/* PROPAGATE-ERROR-TO-REMOTE-CALLER-RECLAIM */
Object propagate_error_to_remote_caller_reclaim(error_message,error_arguments)
    Object error_message, error_arguments;
{
    Object temp, error_1, x2;
    char temp_1;

    x_note_fn_call(166,67);
    reclaim_text_string(error_message);
    if (error_arguments) {
	if (error_arguments &&  !TRUEP(CDR(error_arguments))) {
	    temp = FIRST(error_arguments);
	    error_1 = SECOND(temp);
	}
	else
	    error_1 = Nil;
	if (SIMPLE_VECTOR_P(error_1) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(error_1)) > (SI_Long)2L &&  
		!EQ(ISVREF(error_1,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(error_1,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? (SI_Long)0L != (IFIX(ISVREF(error_1,(SI_Long)5L)) & 
		(SI_Long)262144L) : TRUEP(Nil))
	    delete_frame(error_1);
	reclaim_transformed_rpc_argument_list(error_arguments,Nil);
    }
    return VALUES_1(Nil);
}

static Object Qremote_procedure_call_start_map;  /* remote-procedure-call-start-map */

static Object Qremove_remote_procedure_calls_from_start_map;  /* remove-remote-procedure-calls-from-start-map */

/* REGISTER-REMOTE-PROCEDURE-CALL-FOR-START */
Object register_remote_procedure_call_for_start(remote_procedure_call,
	    icp_socket)
    Object remote_procedure_call, icp_socket;
{
    Object map_1, index_1, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(166,68);
    map_1 = ISVREF(icp_socket,(SI_Long)41L);
    if ( !TRUEP(map_1)) {
	map_1 = make_index_space_1(Qremote_procedure_call_start_map,
		Qremove_remote_procedure_calls_from_start_map);
	SVREF(icp_socket,FIX((SI_Long)41L)) = map_1;
	enlarge_index_space(map_1,FIX((SI_Long)20L));
    }
    index_1 = assign_index_in_index_space(map_1);
    if (FIXNUM_GE(index_1,ISVREF(map_1,(SI_Long)4L)))
	enlarge_index_space(map_1,index_1);
    svref_arg_1 = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(index_1) >>  -  - 
	    (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    ISVREF(svref_arg_1,svref_arg_2) = remote_procedure_call;
    SVREF(remote_procedure_call,FIX((SI_Long)26L)) = index_1;
    return VALUES_1(Nil);
}

/* DEREGISTER-REMOTE-PROCEDURE-CALL-FOR-START */
Object deregister_remote_procedure_call_for_start(remote_procedure_call)
    Object remote_procedure_call;
{
    Object icp_socket, map_1, index_1, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(166,69);
    icp_socket = ISVREF(remote_procedure_call,(SI_Long)24L);
    if (icp_socket) {
	map_1 = ISVREF(icp_socket,(SI_Long)41L);
	index_1 = ISVREF(remote_procedure_call,(SI_Long)26L);
	if (FIXNUM_GE(index_1,ISVREF(map_1,(SI_Long)4L)))
	    enlarge_index_space(map_1,index_1);
	svref_arg_1 = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(index_1) >>  - 
		 - (SI_Long)10L);
	svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
	deassign_index_in_index_space(index_1,map_1);
	SVREF(remote_procedure_call,FIX((SI_Long)24L)) = Nil;
	ISVREF(remote_procedure_call,(SI_Long)26L) = FIX((SI_Long)-1L);
    }
    return VALUES_1(Nil);
}

/* REMOVE-REMOTE-PROCEDURE-CALLS-FROM-START-MAP */
Object remove_remote_procedure_calls_from_start_map(object,
	    index_space_name,shutdownp)
    Object object, index_space_name, shutdownp;
{
    Object remote_procedure_call;

    x_note_fn_call(166,70);
    if (SIMPLE_VECTOR_P(object) && EQ(ISVREF(object,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct)) {
	remote_procedure_call = object;
	SVREF(remote_procedure_call,FIX((SI_Long)24L)) = Nil;
	ISVREF(remote_procedure_call,(SI_Long)26L) = FIX((SI_Long)-1L);
    }
    return VALUES_1(Nil);
}

static Object string_constant_34;  /* "~A" */

static Object string_constant_35;  /* "~NF" */

/* RETURN-STACK-VALUES-TO-REMOTE-CALLER */
Object return_stack_values_to_remote_caller(remote_procedure_call,stack,
	    top_of_stack,values_on_stack,returning_code_body_invocation)
    Object remote_procedure_call, stack, top_of_stack, values_on_stack;
    Object returning_code_body_invocation;
{
    Object returning_procedure_invocation, returning_procedure;
    Object return_descriptions, value_or_object, svref_new_value;
    Object remote_procedure_identifier, icp_socket, exit_message_qm;
    Object argument_strings_for_trace, return_results_list;
    Object cached_top_of_stack, return_type, return_description, results;
    Object ab_loopvar_, ab_loopvar__1, gensymed_symbol_1;
    Object invalidity_message_qm, string_1, ab_loop_list_, top_of_stack_1;
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, temp_3, temp_4, temp_5;
    Object temp_6, transform_error_message_qm;
    SI_Long index_1, description_index, ab_loop_bind_, gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind__1;
    char temp;
    Declare_special(8);
    Object result;

    x_note_fn_call(166,71);
    if ( !TRUEP(ISVREF(remote_procedure_call,(SI_Long)22L))) {
	returning_procedure_invocation = 
		ISVREF(returning_code_body_invocation,(SI_Long)11L);
	returning_procedure = ISVREF(returning_procedure_invocation,
		(SI_Long)23L);
	return_descriptions = ISVREF(returning_procedure,(SI_Long)25L);
	index_1 = IFIX(FIXNUM_ADD1(FIXNUM_MINUS(top_of_stack,
		values_on_stack)));
	value_or_object = Nil;
	description_index = (SI_Long)0L;
	ab_loop_bind_ = IFIX(var_count(return_descriptions));
	value_or_object = ISVREF(stack,index_1);
      next_loop:
	if (description_index >= ab_loop_bind_)
	    goto end_loop;
	if ( !(FIXNUMP(value_or_object) || SYMBOLP(value_or_object) || 
		SIMPLE_VECTOR_P(value_or_object)))
	    reclaim_if_evaluation_value_1(value_or_object);
	index_1 = index_1 + (SI_Long)1L;
	value_or_object = ISVREF(stack,index_1);
	description_index = description_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	SVREF(returning_code_body_invocation,FIX((SI_Long)12L)) = Nil;
	svref_new_value = 
		delete_proc_element_1(returning_code_body_invocation,
		ISVREF(remote_procedure_call,(SI_Long)13L));
	SVREF(remote_procedure_call,FIX((SI_Long)13L)) = svref_new_value;
	deregister_remote_procedure_call_for_start(remote_procedure_call);
	reclaim_incoming_remote_procedure_call(remote_procedure_call);
    }
    else {
	remote_procedure_identifier = ISVREF(remote_procedure_call,
		(SI_Long)22L);
	returning_procedure_invocation = 
		ISVREF(returning_code_body_invocation,(SI_Long)11L);
	icp_socket = ISVREF(remote_procedure_call,(SI_Long)24L);
	returning_procedure = ISVREF(returning_procedure_invocation,
		(SI_Long)23L);
	return_descriptions = ISVREF(returning_procedure,(SI_Long)25L);
	exit_message_qm = Saved_warning_level && (IFIX(Breakpoint_level) > 
		(SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L) 
		&& ISVREF(Debugging_parameters,(SI_Long)22L) ? ( 
		!TRUEP(in_order_p(returning_procedure)) ? T : Nil) : Qnil;
	argument_strings_for_trace = Nil;
	return_results_list = Nil;
	cached_top_of_stack = top_of_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Cached_top_of_stack,Qcached_top_of_stack,cached_top_of_stack,
		7);
	  index_1 = IFIX(FIXNUM_ADD1(FIXNUM_MINUS(top_of_stack,
		  values_on_stack)));
	  value_or_object = Nil;
	  description_index = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(var_count(return_descriptions));
	  return_type = Nil;
	  return_description = Nil;
	  results = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  value_or_object = ISVREF(stack,index_1);
	next_loop_1:
	  if (description_index >= ab_loop_bind_)
	      goto end_loop_1;
	  gensymed_symbol = description_index * (SI_Long)2L + (SI_Long)1L;
	  gensymed_symbol_1 = FIXNUM_LE(ISVREF(return_descriptions,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(return_descriptions,gensymed_symbol + 
		  IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(return_descriptions,(gensymed_symbol >>  - 
		   - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		  (SI_Long)1023L);
	  if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		  Kgeneral_description))
	      gensymed_symbol_1 = 
		      getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
	  return_type = gensymed_symbol_1;
	  gensymed_symbol = description_index * (SI_Long)2L + (SI_Long)1L;
	  gensymed_symbol_1 = FIXNUM_LE(ISVREF(return_descriptions,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(return_descriptions,gensymed_symbol + 
		  IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(return_descriptions,(gensymed_symbol >>  - 
		   - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		  (SI_Long)1023L);
	  if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		  Kgeneral_description)) {
	      gensymed_symbol_1 = CDR(gensymed_symbol_1);
	      return_description = gensymed_symbol_1;
	  }
	  else
	      return_description = Nil;
	  invalidity_message_qm = 
		  invalid_stack_value_or_object_for_return_to_remote_caller_qm(value_or_object,
		  return_type,return_description);
	  if (invalidity_message_qm) {
	      reclaim_rpc_argument_list(results,Nil);
	      if (exit_message_qm) {
		  string_1 = Nil;
		  ab_loop_list_ = argument_strings_for_trace;
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  string_1 = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  reclaim_text_string(string_1);
		  goto next_loop_2;
		end_loop_2:;
		  reclaim_proc_list_1(argument_strings_for_trace);
	      }
	      top_of_stack_1 = Cached_top_of_stack;
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    tformat(2,string_constant_34,
				    invalidity_message_qm);
			    reclaim_text_string(invalidity_message_qm);
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
	      raw_stack_error_named_error(top_of_stack_1,message_1);
	  }
	  else {
	      if (exit_message_qm) {
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    gensymed_symbol_1 = value_or_object;
			    temp = FIXNUMP(gensymed_symbol_1);
			    if (temp);
			    else
				temp = 
					INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) 
					!= (SI_Long)0L ? 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
					== (SI_Long)1L : TRUEP(Qnil);
			    if (temp);
			    else
				temp = 
					INLINE_LONG_VECTOR_P(gensymed_symbol_1) 
					!= (SI_Long)0L ? 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
					== (SI_Long)1L : TRUEP(Qnil);
			    if (temp);
			    else
				temp = gensymed_symbol_1 ? 
					SYMBOLP(gensymed_symbol_1) : 
					TRUEP(Qnil);
			    if (temp);
			    else
				temp = 
					INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol_1) 
					!= (SI_Long)0L;
			    if (temp);
			    else if (CONSP(gensymed_symbol_1)) {
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				temp = EQ(gensymed_symbol_1,Qtruth_value);
				if (temp);
				else
				    temp = EQ(gensymed_symbol_1,
					    Qiteration_state);
				if (temp);
				else if (SYMBOLP(gensymed_symbol_1)) {
				    skip_list = 
					    CDR(Defined_evaluation_value_types);
				    key_value = gensymed_symbol_1;
				    key_hash_value = 
					    SXHASH_SYMBOL_1(gensymed_symbol_1) 
					    & IFIX(Most_positive_fixnum);
				    bottom_level = (SI_Long)0L;
				    marked = Nil;
				    pred = M_CAR(skip_list);
				    curr = Nil;
				    succ = Nil;
				    level = (SI_Long)31L;
				    ab_loop_bind__1 = bottom_level;
				  next_loop_3:
				    if (level < ab_loop_bind__1)
					goto end_loop_3;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_4:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp_2 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp_2);
				    MVS_2(result,succ,marked);
				  next_loop_5:
				    if ( !TRUEP(marked))
					goto end_loop_4;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp_2 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp_2);
				    MVS_2(result,succ,marked);
				    goto next_loop_5;
				  end_loop_4:
				    entry_hash = ISVREF(curr,(SI_Long)1L);
				    if (IFIX(entry_hash) < key_hash_value 
					    || IFIX(entry_hash) == 
					    key_hash_value &&  
					    !EQ(key_value,ISVREF(curr,
					    (SI_Long)2L))) {
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
				    temp = IFIX(ISVREF(curr,(SI_Long)1L)) 
					    == key_hash_value ? 
					    (EQ(key_value,ISVREF(curr,
					    (SI_Long)2L)) ? 
					    TRUEP(ISVREF(curr,
					    (SI_Long)3L)) : TRUEP(Nil)) : 
					    TRUEP(Nil);
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				write_evaluation_value(1,value_or_object);
			    else
				tformat(2,string_constant_35,value_or_object);
			    temp_2 = copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  argument_strings_for_trace = proc_cons_1(temp_2,
			  argument_strings_for_trace);
	      }
	      ISVREF(stack,index_1) = Nil;
	  }
	  ab_loopvar__1 = eval_cons_1(value_or_object,Nil);
	  if (ab_loopvar_)
	      M_CDR(ab_loopvar_) = ab_loopvar__1;
	  else
	      results = ab_loopvar__1;
	  ab_loopvar_ = ab_loopvar__1;
	  index_1 = index_1 + (SI_Long)1L;
	  value_or_object = ISVREF(stack,index_1);
	  description_index = description_index + (SI_Long)1L;
	  goto next_loop_1;
	end_loop_1:
	  temp_3 = ISVREF(remote_procedure_call,(SI_Long)23L);
	  temp_4 = results;
	  temp_5 = 
		  get_icp_interface_for_remote_procedure_call(remote_procedure_call,
		  T);
	  temp_6 = get_rpc_priority_from_computation_context();
	  temp_2 = ISVREF(ISVREF(ISVREF(remote_procedure_identifier,
		  (SI_Long)8L),(SI_Long)1L),(SI_Long)1L);
	  temp_1 = CDR(temp_2);
	  temp_2 = ISVREF(ISVREF(ISVREF(remote_procedure_identifier,
		  (SI_Long)8L),(SI_Long)1L),(SI_Long)1L);
	  transform_error_message_qm = 
		  transform_rpc_argument_or_result_list(9,temp_3,temp_4,
		  return_descriptions,icp_socket,temp_5,temp_6,Nil,temp_1,
		  CAR(temp_2));
	  if (transform_error_message_qm) {
	      reclaim_rpc_argument_list(results,Nil);
	      if (exit_message_qm) {
		  string_1 = Nil;
		  ab_loop_list_ = argument_strings_for_trace;
		next_loop_6:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_6;
		  string_1 = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  reclaim_text_string(string_1);
		  goto next_loop_6;
		end_loop_6:;
		  reclaim_proc_list_1(argument_strings_for_trace);
	      }
	      top_of_stack_1 = Cached_top_of_stack;
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    tformat(2,string_constant_34,
				    transform_error_message_qm);
			    reclaim_text_string(transform_error_message_qm);
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
	      raw_stack_error_named_error(top_of_stack_1,message_1);
	  }
	  else {
	      if (Saved_warning_level) {
		  if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
			  IFIX(Tracing_message_level) > (SI_Long)0L) && 
			  ISVREF(Debugging_parameters,(SI_Long)22L) &&  
			  !TRUEP(in_order_p(returning_procedure)))
		      issue_tracing_and_breakpoint_exit_message(returning_procedure,
			      exit_message_qm ? 
			      remote_return_exit_message(returning_procedure_invocation,
			      nreverse(argument_strings_for_trace)) : Qnil);
		  Warning_message_level = Saved_warning_level;
		  Tracing_message_level = Saved_tracing_level;
		  Breakpoint_level = Saved_breakpoint_level;
		  Source_stepping_level = Saved_source_stepping_level;
	      }
	      return_results_list = results;
	  }
	  reclaim_rpc_and_invocation_after_rpc_return_values(remote_procedure_call,
		  returning_code_body_invocation);
	  send_rpc_return_values(ISVREF(ISVREF(remote_procedure_call,
		  (SI_Long)24L),(SI_Long)4L),
		  ISVREF(returning_code_body_invocation,(SI_Long)10L),
		  ISVREF(remote_procedure_identifier,(SI_Long)1L),
		  return_results_list);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* RECLAIM-RPC-AND-INVOCATION-AFTER-RPC-RETURN-VALUES */
Object reclaim_rpc_and_invocation_after_rpc_return_values(remote_procedure_call,
	    returning_code_body_invocation)
    Object remote_procedure_call, returning_code_body_invocation;
{
    Object remote_procedure_identifier, svref_new_value;

    x_note_fn_call(166,72);
    remote_procedure_identifier = ISVREF(remote_procedure_call,(SI_Long)22L);
    SVREF(remote_procedure_identifier,FIX((SI_Long)4L)) = Nil;
    SVREF(returning_code_body_invocation,FIX((SI_Long)12L)) = Nil;
    svref_new_value = delete_proc_element_1(returning_code_body_invocation,
	    ISVREF(remote_procedure_call,(SI_Long)13L));
    SVREF(remote_procedure_call,FIX((SI_Long)13L)) = svref_new_value;
    return reclaim_incoming_remote_procedure_call(remote_procedure_call);
}

/* RECLAIM-AFTER-RPC-RETURN-VALUES */
Object reclaim_after_rpc_return_values(return_results_list)
    Object return_results_list;
{
    x_note_fn_call(166,73);
    return reclaim_transformed_rpc_argument_list(return_results_list,Nil);
}

static Object string_constant_36;  /* "Attempting to return an object of class ~A ~
				    *              to a remote procedure caller.  The caller ~
				    *              expects a value of type ~A instead."
				    */

static Object string_constant_37;  /* "Attempting to return an object of class ~A ~
				    *                     to a remote procedure caller.  This object ~
				    *                     is not of the declared class ~A."
				    */

static Object array_constant_3;    /* # */

static Object string_constant_38;  /* " to a remote procedure caller.  The caller ~
				    *                       expects an object of class ~A instead."
				    */

/* INVALID-STACK-VALUE-OR-OBJECT-FOR-RETURN-TO-REMOTE-CALLER? */
Object invalid_stack_value_or_object_for_return_to_remote_caller_qm(value_or_object,
	    return_type,return_description)
    Object value_or_object, return_type, return_description;
{
    Object x2, return_class, class_of_frame, gensymed_symbol;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp, as_handle_p;
    Declare_special(5);
    Object result;

    x_note_fn_call(166,74);
    if (EQ(return_type,Qitem_or_datum))
	return VALUES_1(Nil);
    else if ( !TRUEP(class_type_specification_p(return_type))) {
	if (SIMPLE_VECTOR_P(value_or_object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_or_object)) > 
		(SI_Long)2L &&  !EQ(ISVREF(value_or_object,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(value_or_object,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return tformat_text_string(3,string_constant_36,
		    ISVREF(ISVREF(value_or_object,(SI_Long)1L),
		    (SI_Long)1L),return_type);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (SIMPLE_VECTOR_P(value_or_object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_or_object)) > 
		(SI_Long)2L &&  !EQ(ISVREF(value_or_object,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(value_or_object,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    return_class = SECOND(return_type);
	    class_of_frame = ISVREF(ISVREF(value_or_object,(SI_Long)1L),
		    (SI_Long)1L);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_of_frame,
		    Class_description_gkbprop);
	    if ( !(gensymed_symbol ? TRUEP(memq_function(return_class,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)))
		return tformat_text_string(3,string_constant_37,
			class_of_frame,return_class);
	    else
		return VALUES_1(Nil);
	}
	else {
	    as_handle_p = EQ(Qhandle,getf(return_description,Kkind,_));
	    if ( !(as_handle_p && FIXNUMP(value_or_object))) {
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
			  twrite_beginning_of_wide_string(array_constant_3,
				  FIX((SI_Long)21L));
			  write_evaluation_value(1,value_or_object);
			  tformat(2,string_constant_38,return_type);
			  result = copy_out_current_wide_string();
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
    }
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* REMOTE-RETURN-EXIT-MESSAGE */
Object remote_return_exit_message(procedure_invocation,return_value_strings)
    Object procedure_invocation, return_value_strings;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object string_1, ab_loop_list_, first_time_qm, ab_loop_iter_flag_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(166,75);
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
	      twrite_beginning_of_wide_string(array_constant_4,
		      FIX((SI_Long)18L));
	      string_1 = Nil;
	      ab_loop_list_ = return_value_strings;
	      first_time_qm = T;
	      ab_loop_iter_flag_ = T;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      string_1 = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_iter_flag_))
		  first_time_qm = Nil;
	      if ( !TRUEP(first_time_qm))
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)2L));
	      twrite_general_string(string_1);
	      reclaim_text_string(string_1);
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop;
	    end_loop:;
	      reclaim_proc_list_1(return_value_strings);
	      twrite_beginning_of_wide_string(array_constant_6,
		      FIX((SI_Long)7L));
	      write_procedure_invocation_instance_from_slot(procedure_invocation,
		      Nil);
	      twrite_beginning_of_wide_string(array_constant_7,
		      FIX((SI_Long)20L));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object string_constant_39;  /* "Cannot return results from the remote procedure ~NF, since ~A" */

static Object string_constant_40;  /* "~A values were returned, but the remote procedure declaration ~
				    *                       ~NF declares that ~a values would be returned."
				    */

static Object string_constant_41;  /* "Procedure ~NF is requesting more values than ~NF can return." */

/* RECEIVE-REMOTE-PROCEDURE-VALUES */
Object receive_remote_procedure_values(remote_procedure_identifier,
	    returned_values)
    Object remote_procedure_identifier, returned_values;
{
    Object icp_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object initial_rpc_frame_serial_number, rpc_argument_list_error;
    Object remote_procedure_call, caller, receiving_passed_items_qm;
    Object remote_procedure_declaration, return_descriptions;
    Object formal_return_restp_index, caller_procedure_invocation;
    Object current_computation_frame, calling_environment, position_1, i;
    Object gensymed_symbol_1, temp_1, error_message_qm;
    Object frame_serial_number_setf_arg, old, new_1;
    SI_Long values_count, count_1, gensymed_symbol;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(166,76);
    icp_pop_store = Nil;
    cons_1 = returned_values;
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
    returned_values = next_cons;
    initial_rpc_frame_serial_number = icp_pop_store;
    icp_pop_store = Nil;
    cons_1 = returned_values;
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
    returned_values = next_cons;
    rpc_argument_list_error = icp_pop_store;
    PUSH_SPECIAL_WITH_SYMBOL(Rpc_argument_list_error,Qrpc_argument_list_error,rpc_argument_list_error,
	    1);
      remote_procedure_call = remote_procedure_identifier ? 
	      ISVREF(remote_procedure_identifier,(SI_Long)3L) : Nil;
      caller = remote_procedure_call ? ISVREF(remote_procedure_call,
	      (SI_Long)12L) : Nil;
      if (caller);
      else {
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_receive_remote_procedure_values;
      }
      receiving_passed_items_qm = T;
      remote_procedure_declaration = ISVREF(remote_procedure_call,
	      (SI_Long)23L);
      return_descriptions = ISVREF(remote_procedure_declaration,(SI_Long)25L);
      formal_return_restp_index = Nil;
      caller_procedure_invocation = ISVREF(caller,(SI_Long)11L);
      current_computation_frame = ISVREF(caller_procedure_invocation,
	      (SI_Long)23L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      0);
	calling_environment = ISVREF(caller,(SI_Long)2L);
	position_1 = ISVREF(caller,(SI_Long)5L);
	values_count = IFIX(length(returned_values));
	count_1 = IFIX(ISVREF(caller,(SI_Long)6L));
	temp = delete_proc_element_1(remote_procedure_call,ISVREF(caller,
		(SI_Long)13L));
	SVREF(caller,FIX((SI_Long)13L)) = temp;
	reclaim_outgoing_remote_procedure_identifier_and_index(remote_procedure_identifier);
	reclaim_outgoing_remote_procedure_call(remote_procedure_call);
	i = FIXNUM_SUB1(var_count(return_descriptions));
	if ((SI_Long)0L <= IFIX(i)) {
	    gensymed_symbol = IFIX(i) * (SI_Long)2L + (SI_Long)1L;
	    gensymed_symbol_1 = FIXNUM_LE(ISVREF(return_descriptions,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(return_descriptions,gensymed_symbol + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(return_descriptions,(gensymed_symbol >>  
		    -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L);
	    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		    Kgeneral_description)) {
		gensymed_symbol_1 = CDR(gensymed_symbol_1);
		temp_1 = gensymed_symbol_1;
	    }
	    else
		temp_1 = Nil;
	    temp_2 = TRUEP(getf(temp_1,Kall_remaining,_));
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    formal_return_restp_index = i;
	if (Rpc_argument_list_error)
	    error_message_qm = tformat_text_string(3,string_constant_39,
		    remote_procedure_declaration,Rpc_argument_list_error);
	else if (formal_return_restp_index ? values_count < 
		IFIX(FIXNUM_SUB1(var_count(return_descriptions))) : 
		values_count != IFIX(var_count(return_descriptions)))
	    error_message_qm = tformat_text_string(4,string_constant_40,
		    FIX(values_count),remote_procedure_declaration,
		    var_count(return_descriptions));
	else if (count_1 > values_count)
	    error_message_qm = tformat_text_string(3,string_constant_41,
		    ISVREF(ISVREF(caller,(SI_Long)11L),(SI_Long)23L),
		    remote_procedure_declaration);
	else {
	    if (receiving_passed_items_qm)
		validate_computation_instance_environment(caller,Nil,T);
	    error_message_qm = 
		    receive_remote_procedure_values_1(position_1,
		    FIX(count_1),returned_values,return_descriptions,
		    remote_procedure_declaration,calling_environment);
	}
	reclaim_unprocessed_rpc_argument_list(3,returned_values,
		initial_rpc_frame_serial_number, !TRUEP(error_message_qm) ?
		 FIX(count_1) : Nil);
	if (error_message_qm) {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(Rpc_argument_list_error) 
		    != (SI_Long)0L)
		reclaim_wide_string(Rpc_argument_list_error);
	    signal_code_body_invocation_error(9,caller,Qrpc_error,
		    FIX((SI_Long)1L),error_message_qm,Nil,Nil,Nil,Nil,Nil);
	}
	else {
	    if (receiving_passed_items_qm) {
		frame_serial_number_setf_arg = Current_frame_serial_number;
		old = ISVREF(caller,(SI_Long)9L);
		new_1 = frame_serial_number_setf_arg;
		temp = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) 
			||  !TRUEP(new_1)) ? new_1 : 
			frame_serial_number_setf_helper_1(old,new_1);
		SVREF(caller,FIX((SI_Long)9L)) = temp;
	    }
	    wake_up_code_body_invocation(caller);
	}
	result = reclaim_frame_serial_number(initial_rpc_frame_serial_number);
      POP_SPECIAL();
    POP_SPECIAL();
  end_receive_remote_procedure_values:
    return result;
}

static Object string_constant_42;  /* "The returned value at position ~D, " */

static Object string_constant_43;  /* " was not of the type ~NT, as required by the ~
				    *                           declaration for ~NF."
				    */

/* RECEIVE-REMOTE-PROCEDURE-VALUES-1 */
Object receive_remote_procedure_values_1(position_1,count_1,
	    returned_values,return_descriptions,
	    remote_procedure_declaration,calling_environment)
    Object position_1, count_1, returned_values, return_descriptions;
    Object remote_procedure_declaration, calling_environment;
{
    Object value_or_object, ab_loop_list_, rest_return_p, description_index;
    Object return_type, return_description, restp, kind, ab_loop_iter_flag_;
    Object temp, gensymed_symbol_1, handled_object_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object entry_hash;
    SI_Long index_1, ab_loop_bind_, gensymed_symbol, index_2, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1, key_hash_value, bottom_level;
    SI_Long level;
    char as_handle_p, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(166,77);
    index_1 = IFIX(position_1);
    ab_loop_bind_ = IFIX(FIXNUM_ADD(position_1,count_1));
    value_or_object = Nil;
    ab_loop_list_ = returned_values;
    rest_return_p = Nil;
    description_index = FIX((SI_Long)0L);
    return_type = Nil;
    return_description = Nil;
    restp = Nil;
    kind = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    value_or_object = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_)) {
	temp = rest_return_p;
	if (temp);
	else
	    temp = restp;
	rest_return_p = temp;
	description_index = rest_return_p ? description_index : 
		FIXNUM_ADD1(description_index);
    }
    gensymed_symbol = IFIX(description_index) * (SI_Long)2L + (SI_Long)1L;
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
    gensymed_symbol = IFIX(description_index) * (SI_Long)2L + (SI_Long)1L;
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
    kind = getf(return_description,Kkind,_);
    if (CONSP(value_or_object) && EQ(M_CDR(value_or_object),
	    Qunsigned_vector_16))
	value_or_object = M_CAR(value_or_object);
    if ( !TRUEP(type_specification_type_p(value_or_object,return_type))) {
	as_handle_p = EQ(Qhandle,kind);
	handled_object_qm = as_handle_p && FIXNUMP(value_or_object) ? 
		get_item_from_local_handle(value_or_object,
		Current_icp_socket) : Qnil;
	if (handled_object_qm && 
		type_specification_type_p(handled_object_qm,return_type))
	    value_or_object = handled_object_qm;
	else {
	    index_2 = IFIX(position_1);
	    ab_loop_bind_ = IFIX(FIXNUM_ADD(position_1,count_1));
	  next_loop_1:
	    if (index_2 >= ab_loop_bind_)
		goto end_loop_1;
	    ISVREF(calling_environment,index_2) = Nil;
	    index_2 = index_2 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
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
		      tformat(2,string_constant_42,FIX(index_1 - 
			      IFIX(position_1)));
		      gensymed_symbol_1 = value_or_object;
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
			    next_loop_2:
			      if (level < ab_loop_bind_)
				  goto end_loop_2;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_3:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp);
			      MVS_2(result,succ,marked);
			    next_loop_4:
			      if ( !TRUEP(marked))
				  goto end_loop_3;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp);
			      MVS_2(result,succ,marked);
			      goto next_loop_4;
			    end_loop_3:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
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
			  write_evaluation_value(1,value_or_object);
		      else
			  tformat(2,string_constant_35,value_or_object);
		      tformat(3,string_constant_43,return_type,
			      remote_procedure_declaration);
		      result = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
    ISVREF(calling_environment,index_1) = value_or_object;
    ab_loop_iter_flag_ = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qreceive_remote_procedure_error_for_caller;  /* receive-remote-procedure-error-for-caller */

/* RECEIVE-REMOTE-PROCEDURE-ERROR-FOR-CALLER */
Object receive_remote_procedure_error_for_caller(remote_procedure_identifier_qm,
	    signalling_invocation_qm,error_1,error_level,error_description)
    Object remote_procedure_identifier_qm, signalling_invocation_qm, error_1;
    Object error_level, error_description;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object resumable_objects_qm, remote_procedure_call_qm, caller_qm;
    Object resumable_object, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(166,78);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
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
	  SVREF(temp,svref_arg_2) = Qreceive_remote_procedure_error_for_caller;
      }
      resumable_objects_qm = remote_procedure_identifier_qm ? 
	      ISVREF(remote_procedure_identifier_qm,(SI_Long)5L) : Nil;
      remote_procedure_call_qm = remote_procedure_identifier_qm ? 
	      ISVREF(remote_procedure_identifier_qm,(SI_Long)3L) : Nil;
      caller_qm = remote_procedure_call_qm ? 
	      ISVREF(remote_procedure_call_qm,(SI_Long)12L) : Nil;
      if (resumable_objects_qm) {
	  resumable_object = Nil;
	  ab_loop_list_ = resumable_objects_qm;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  resumable_object = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  g2_reclaim_sending_resumable_object(1,resumable_object);
	  goto next_loop;
	end_loop:;
	  SVREF(remote_procedure_identifier_qm,FIX((SI_Long)5L)) = Nil;
      }
      if (caller_qm)
	  result = propagate_error_to_code_body_invocation(caller_qm,
		  error_1,error_level,copy_text_string(error_description));
      else
	  result = receive_remote_procedure_error(Current_icp_socket,
		  error_1,error_level,error_description,Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_44;  /* "Remote procedure call to " */

static Object string_constant_45;  /* "Remote procedure start to " */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object string_constant_46;  /* " ~a" */

static Object string_constant_47;  /* " for the following reason:~%~a" */

static Object array_constant_10;   /* # */

/* REMOTE-PROCEDURE-CALL-BEING-ABORTED */
Object remote_procedure_call_being_aborted(remote_procedure_call,
	    reason_string_qm,error_1)
    Object remote_procedure_call, reason_string_qm, error_1;
{
    Object remote_procedure_identifier_qm, temp, called_code_body;
    Object called_procedure_invocation, local_host_name_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, svref_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(166,79);
    remote_procedure_identifier_qm = ISVREF(remote_procedure_call,
	    (SI_Long)22L);
    temp = ISVREF(remote_procedure_call,(SI_Long)13L);
    called_code_body = CAR(temp);
    called_procedure_invocation = called_code_body ? 
	    ISVREF(called_code_body,(SI_Long)11L) : Nil;
    local_host_name_qm = get_local_host_name();
    temp = ISVREF(remote_procedure_call,(SI_Long)24L);
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
	      twrite_general_string(remote_procedure_identifier_qm ? 
		      string_constant_44 : string_constant_45);
	      if (called_procedure_invocation)
		  write_procedure_invocation_instance_from_slot(called_procedure_invocation,
			  Nil);
	      else
		  twrite_beginning_of_wide_string(array_constant_8,
			  FIX((SI_Long)38L));
	      twrite_beginning_of_wide_string(array_constant_9,
		      FIX((SI_Long)38L));
	      if (local_host_name_qm)
		  tformat(2,string_constant_46,local_host_name_qm);
	      if (reason_string_qm)
		  tformat(2,string_constant_47,reason_string_qm);
	      else
		  twrite_beginning_of_wide_string(array_constant_10,
			  FIX((SI_Long)1L));
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    remote_procedure_error_1(temp,Qrpc_error,FIX((SI_Long)1L),temp_1,
	    ISVREF(remote_procedure_call,(SI_Long)22L),error_1);
    reclaim_error_text(reason_string_qm);
    if (called_procedure_invocation) {
	SVREF(called_code_body,FIX((SI_Long)12L)) = Nil;
	svref_new_value = delete_proc_element_1(called_code_body,
		ISVREF(remote_procedure_call,(SI_Long)13L));
	SVREF(remote_procedure_call,FIX((SI_Long)13L)) = svref_new_value;
    }
    SVREF(remote_procedure_call,FIX((SI_Long)22L)) = Nil;
    if (remote_procedure_identifier_qm)
	SVREF(remote_procedure_identifier_qm,FIX((SI_Long)4L)) = Nil;
    else
	deregister_remote_procedure_call_for_start(remote_procedure_call);
    return reclaim_incoming_remote_procedure_call(remote_procedure_call);
}

/* ABORT-INCOMING-RPC-CALL */
Object abort_incoming_rpc_call(remote_procedure_call)
    Object remote_procedure_call;
{
    Object temp, base_code_body_invocation, svref_new_value;
    Object base_procedure_invocation;

    x_note_fn_call(166,80);
    temp = ISVREF(remote_procedure_call,(SI_Long)13L);
    base_code_body_invocation = CAR(temp);
    if (base_code_body_invocation) {
	SVREF(base_code_body_invocation,FIX((SI_Long)12L)) = Nil;
	svref_new_value = delete_proc_element_1(base_code_body_invocation,
		ISVREF(remote_procedure_call,(SI_Long)13L));
	SVREF(remote_procedure_call,FIX((SI_Long)13L)) = svref_new_value;
	base_procedure_invocation = ISVREF(base_code_body_invocation,
		(SI_Long)11L);
	if (base_procedure_invocation)
	    abort_procedure_invocation(1,base_procedure_invocation);
    }
    reclaim_incoming_remote_procedure_call(remote_procedure_call);
    return VALUES_1(Nil);
}

/* ABORT-RPC-CALL-AND-RECLAIM-IDENTIFIER */
Object abort_rpc_call_and_reclaim_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object remote_procedure_call;

    x_note_fn_call(166,81);
    remote_procedure_call = ISVREF(remote_procedure_identifier,(SI_Long)4L);
    if (remote_procedure_call)
	abort_incoming_rpc_call(remote_procedure_call);
    reclaim_incoming_remote_procedure_identifier(remote_procedure_identifier);
    return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

static Object string_constant_48;  /* " for the interface ~NF" */

static Object string_constant_49;  /* " has broken.  It was used for the remote call to ~NF." */

/* SIGNAL-ERROR-TO-RPC-CALLER-AND-RECLAIM-IDENTIFIER */
Object signal_error_to_rpc_caller_and_reclaim_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object remote_procedure_call, caller, svref_new_value, text_string;
    Object snapshots, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object interface_qm, gensymed_symbol, x, y, xa, ya;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);

    x_note_fn_call(166,82);
    remote_procedure_call = ISVREF(remote_procedure_identifier,(SI_Long)3L);
    caller = remote_procedure_call ? ISVREF(remote_procedure_call,
	    (SI_Long)12L) : Nil;
    if (remote_procedure_call) {
	if (caller) {
	    svref_new_value = delete_proc_element_1(remote_procedure_call,
		    ISVREF(caller,(SI_Long)13L));
	    SVREF(caller,FIX((SI_Long)13L)) = svref_new_value;
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
			  twrite_beginning_of_wide_string(array_constant_11,
				  FIX((SI_Long)18L));
			  interface_qm = ISVREF(remote_procedure_call,
				  (SI_Long)25L);
			  if (interface_qm) {
			      gensymed_symbol = ISVREF(interface_qm,
				      (SI_Long)3L);
			      temp = SIMPLE_VECTOR_P(interface_qm) ? 
				      EQ(ISVREF(interface_qm,(SI_Long)1L),
				      Qavailable_frame_vector) : TRUEP(Qnil);
			      if (temp);
			      else
				  temp = FIXNUMP(gensymed_symbol) ? 
					  IFIX(gensymed_symbol) == 
					  (SI_Long)-1L : TRUEP(Nil);
			      if (temp);
			      else {
				  x = gensymed_symbol;
				  y = ISVREF(remote_procedure_call,
					  (SI_Long)9L);
				  if (FIXNUMP(y))
				      temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : 
					      TRUEP(T);
				  else if (FIXNUMP(x))
				      temp = TRUEP(Nil);
				  else {
				      xa = M_CAR(y);
				      ya = M_CAR(x);
				      temp = FIXNUM_LT(xa,ya);
				      if (temp);
				      else
					  temp = FIXNUM_EQ(xa,ya) ? 
						  FIXNUM_LT(M_CDR(y),
						  M_CDR(x)) : TRUEP(Qnil);
				  }
			      }
			      temp =  !temp;
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp)
			      tformat(2,string_constant_48,interface_qm);
			  tformat(2,string_constant_49,
				  ISVREF(remote_procedure_call,(SI_Long)23L));
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
	    signal_code_body_invocation_error(9,caller,Qrpc_error,
		    FIX((SI_Long)1L),make_error_text(text_string,
		    snapshots),Nil,Nil,Nil,Nil,Nil);
	}
	reclaim_outgoing_remote_procedure_call(remote_procedure_call);
    }
    reclaim_outgoing_remote_procedure_identifier_and_index(remote_procedure_identifier);
    return VALUES_1(Nil);
}

static Object Qabort_outgoing_remote_procedure_call;  /* abort-outgoing-remote-procedure-call */

/* ABORT-OUTGOING-REMOTE-PROCEDURE-CALL */
Object abort_outgoing_remote_procedure_call(remote_procedure_call)
    Object remote_procedure_call;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object remote_procedure_identifier_qm, icp_socket_qm, code_body_caller_qm;
    Object resumable_objects_qm, resumable_object, ab_loop_list_;
    Object current_icp_port, current_icp_socket, temp_1, disable_resumability;
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
    Declare_special(13);
    Object result;

    x_note_fn_call(166,83);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    12);
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
	  SVREF(temp,svref_arg_2) = Qabort_outgoing_remote_procedure_call;
      }
      remote_procedure_identifier_qm = ISVREF(remote_procedure_call,
	      (SI_Long)22L);
      icp_socket_qm = ISVREF(remote_procedure_call,(SI_Long)24L);
      code_body_caller_qm = ISVREF(remote_procedure_call,(SI_Long)12L);
      if (code_body_caller_qm) {
	  temp = delete_proc_element_1(remote_procedure_call,
		  ISVREF(code_body_caller_qm,(SI_Long)13L));
	  SVREF(code_body_caller_qm,FIX((SI_Long)13L)) = temp;
	  SVREF(remote_procedure_call,FIX((SI_Long)12L)) = Nil;
      }
      if (remote_procedure_identifier_qm)
	  SVREF(remote_procedure_identifier_qm,FIX((SI_Long)3L)) = Nil;
      reclaim_outgoing_remote_procedure_call(remote_procedure_call);
      if (remote_procedure_identifier_qm) {
	  resumable_objects_qm = ISVREF(remote_procedure_identifier_qm,
		  (SI_Long)5L);
	  if (resumable_objects_qm) {
	      resumable_object = Nil;
	      ab_loop_list_ = resumable_objects_qm;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      resumable_object = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      g2_reclaim_sending_resumable_object(1,resumable_object);
	      goto next_loop;
	    end_loop:;
	      SVREF(remote_procedure_identifier_qm,FIX((SI_Long)5L)) = Nil;
	  }
	  if (icp_socket_qm && EQ(ISVREF(icp_socket_qm,(SI_Long)15L),
		  Icp_connection_running)) {
	      current_icp_port = ISVREF(icp_socket_qm,(SI_Long)4L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		      11);
		current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			10);
		  temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			  >= (SI_Long)17L ? ISVREF(Current_icp_socket,
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
			  icp_byte_position_of_start_of_message_series_qm 
				  = Nil;
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
					  temp = 
						  ISVREF(Profiling_enabled_qm,
						  (SI_Long)2L);
					  DFLOAT_ISASET_1(temp,(SI_Long)0L,
						  gensymed_symbol_2);
				      }
				      if (icp_connection_open_p(Current_icp_socket) 
					      &&  
					      !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						  {
					  send_icp_rpc_asynchronous_abort(remote_procedure_identifier_qm);
					  end_icp_message_group();
				      }
				      if (Profiling_enabled_qm) {
					  gensymed_symbol_3 = 
						  g2ext_unix_time_as_float();
					  gensymed_symbol_4 = 
						  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						  (SI_Long)2L),(SI_Long)0L);
					  gensymed_symbol_5 = 
						  gensymed_symbol_3 - 
						  gensymed_symbol_4;
					  temp = 
						  ISVREF(Profiling_enabled_qm,
						  (SI_Long)6L);
					  aref_new_value = 
						  gensymed_symbol_5 + 
						  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						  (SI_Long)6L),(SI_Long)0L);
					  DFLOAT_ISASET_1(temp,(SI_Long)0L,
						  aref_new_value);
					  temp = 
						  ISVREF(Profiling_enabled_qm,
						  (SI_Long)2L);
					  aref_new_value = gensymed_symbol 
						  ? gensymed_symbol_1 + 
						  gensymed_symbol_5 + 
						  (gensymed_symbol_4 - 
						  gensymed_symbol_2) : 
						  gensymed_symbol_3;
					  DFLOAT_ISASET_1(temp,(SI_Long)0L,
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
	      if (EQ(ISVREF(icp_socket_qm,(SI_Long)15L),
		      Icp_connection_running))
		  SVREF(remote_procedure_identifier_qm,FIX((SI_Long)9L)) = T;
	  }
      }
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qreceive_remote_procedure_asynchronous_abort;  /* receive-remote-procedure-asynchronous-abort */

/* RECEIVE-REMOTE-PROCEDURE-ASYNCHRONOUS-ABORT */
Object receive_remote_procedure_asynchronous_abort(icp_socket,
	    remote_procedure_identifier)
    Object icp_socket, remote_procedure_identifier;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object resumable_objects_qm, remote_procedure_call;
    Declare_special(1);
    Object result;

    x_note_fn_call(166,84);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
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
		  Qreceive_remote_procedure_asynchronous_abort;
      }
      resumable_objects_qm = ISVREF(remote_procedure_identifier,(SI_Long)5L);
      if (resumable_objects_qm) {
	  reclaim_receiving_resumable_object(FIRST(resumable_objects_qm));
	  SVREF(remote_procedure_identifier,FIX((SI_Long)5L)) = Nil;
      }
      remote_procedure_call = ISVREF(remote_procedure_identifier,(SI_Long)4L);
      if (remote_procedure_call) {
	  SVREF(remote_procedure_identifier,FIX((SI_Long)4L)) = Nil;
	  result = abort_incoming_rpc_call(remote_procedure_call);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

void g2_rpc1_INIT()
{
    Object temp, temp_1;
    Object remote_procedure_argument_descriptions_evaluation_getter_1;
    Object remote_procedure_name_evaluation_setter_1;
    Object remote_procedure_name_evaluation_getter_1, temp_2;
    Object reclaim_structure_for_scheduled_remote_procedure_start_1;
    Object reclaim_structure_for_system_rpc_instance_1, gensymed_symbol;
    Object AB_package, list_constant_87;
    Object Qg2_current_remote_interface_lisp_side;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2_prefer_kb_procedures_to_system_defined_system_rpc_internal;
    Object Qg2_prefer_kb_procedures_to_system_defined, list_constant_92;
    Object list_constant_91, list_constant_4, Qprefer;
    Object Qg2_api_test_1_system_rpc_internal, Qg2_api_test_1;
    Object list_constant_88, list_constant_90, list_constant_89, Qarg1;
    Object Qsystem_rpc_instance, Qreclaim_structure;
    Object Qoutstanding_system_rpc_instance_count;
    Object Qsystem_rpc_instance_structure_memory_usage, Qutilities2;
    Object string_constant_64, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_63, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qclasses_which_define;
    Object Qdeactivate, Qdeactivate_for_remote_procedure_declaration;
    Object Qactivate, Qactivate_for_remote_procedure_declaration;
    Object Qscheduled_remote_procedure_start;
    Object Qoutstanding_scheduled_remote_procedure_start_count;
    Object Qscheduled_remote_procedure_start_structure_memory_usage;
    Object string_constant_62, string_constant_61, Qslot_value_reclaimer;
    Object Qreclaim_remote_procedure_name_structure_value;
    Object Qremote_procedure_name_structure, Qslot_putter;
    Object Qput_name_in_remote_system, Qslot_value_writer;
    Object Qwrite_remote_procedure_name_from_slot, Qremote_procedure_name;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_remote_procedure_name_for_slot;
    Object Qput_box_translation_and_text_slot_value;
    Object Qput_box_translation_and_text_slot_value_for_remote_procedure_declaration;
    Object Qcompile_remote_procedure_declaration_for_slot;
    Object Qreformat_remote_procedure_declaration_descriptions;
    Object Qencode_remaining_into_remote_procedure_type_2;
    Object Qencode_remaining_into_remote_procedure_type_1, list_constant_86;
    Object list_constant_85, list_constant_84, list_constant_83;
    Object list_constant_82, list_constant_81, Qsimplify_associative_operation;
    Object list_constant_80, list_constant_79;
    Object Qremote_procedure_type_list_1_tail, list_constant_72;
    Object list_constant_71, list_constant_75, list_constant_78;
    Object Qremote_procedure_type, Qremote_procedure_type_list_1;
    Object list_constant_77, list_constant_76, list_constant_73;
    Object list_constant_74, list_constant_70, list_constant_69, Qremaining;
    Object Qall, list_constant_68, list_constant_67, list_constant_66;
    Object list_constant_65, list_constant_64, list_constant_63;
    Object list_constant_62, list_constant_61, list_constant_60;
    Object list_constant_59, list_constant_58, list_constant_57;
    Object list_constant_56, list_constant_55, list_constant_54;
    Object list_constant_53, list_constant_52, list_constant_51;
    Object Qremote_procedure_type_list, list_constant_49, list_constant_48;
    Object Qnil_function, list_constant_50, list_constant_47, Qcp, Qop;
    Object list_constant_46, list_constant_45, list_constant_3;
    Object list_constant_44, list_constant_43, list_constant_42, Qab_structure;
    Object list_constant_41, list_constant_40, list_constant_39;
    Object list_constant_38, list_constant_37, Qtext, list_constant_36;
    Object list_constant_35, Qlong, list_constant_34, list_constant_33;
    Object list_constant_32, list_constant_31, list_constant_30, Qwhole_string;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object Qprocedure_name, list_constant_26, list_constant_25, Qremote;
    Object Qnamed, Qtype_specification_simple_expansion, list_constant_5;
    Object Qab_or, Qremote_procedure_argument_descriptions, list_constant_24;
    Object list_constant_8, list_constant_23, list_constant_22;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object list_constant_18, list_constant_17, list_constant_16;
    Object list_constant_15, list_constant_14, list_constant_13;
    Object list_constant_12, list_constant_11, list_constant_10;
    Object list_constant_9, list_constant_7, list_constant_6, Qreference;
    Object Qby_copy_with_handle, Qno_item, string_constant_60;
    Object string_constant_59, list_constant_2, string_constant_58;
    Object string_constant_57, string_constant_56, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, Qstatement;

    x_note_fn_call(166,85);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qremote_procedure_declaration = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DECLARATION",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    list_constant_2 = STATIC_CONS(Qstatement,Qnil);
    check_if_superior_classes_are_defined(Qremote_procedure_declaration,
	    list_constant_2);
    string_constant_50 = STATIC_STRING("1m1m8v837Ly1l8t");
    string_constant_51 = 
	    STATIC_STRING("1u4z8r83--y83--y837Ly837Ly00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_52 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_53 = 
	    STATIC_STRING("0004z8r83-0y83-0y837Ly837Ly00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_54 = 
	    STATIC_STRING("ion is available at this time)000004z8r83-Fy83-Fy837Ly837Ly00001q1l8l1m8p01l83Cy1l83Uy1l83*-y1m83Dy53MySee comment in class bloc");
    string_constant_55 = 
	    STATIC_STRING("k000004z8r83ry83ry837Ly837Ly00001p1l8o1l8l1n8p837Ly83Gy1l83-5y1l83-3y000004z8r83WAy83WAy837Ly837Ly00001n1l8o1l8l1m8p8369y000004z");
    string_constant_56 = 
	    STATIC_STRING("8r83Yuy83Yuy837Ly837Ly00001n1l8o1l8l1l83Hy000004z8r83dhy83dhy837Ly837Ly00001n1l8o1l8l1l83Cy000004z8r83Zhy83Zhy837Ly837Ly00001n1l");
    string_constant_57 = 
	    STATIC_STRING("8o1l8l1l83Hy000004z8r83Yry83Yry837Ly837Ly00001p1m8p83Ysy1l8o1l8l1l83Cy1l83Ny000004z8r83Yvy83Yvy837Ly837Ly00001p1m8p83Ysy1l8o1l8l");
    string_constant_58 = STATIC_STRING("1l83Cy1l83Ny00000");
    string_constant_59 = 
	    STATIC_STRING("1w8q1o837Ly1l83*ry1m8v837Ly8t1n83--y01m8p83-*y1n83-0y01m8p83-0y1p83-Fy08l1m8p083Cy1q83ry08o8l1n8p837Ly83Gy83-5y1p83WAy08o8l1m8p8");
    string_constant_60 = 
	    STATIC_STRING("369y1p83Yuy08o8l83Hy1p83dhy08o8l83Cy1p83Zhy08o8l83Hy1r83Yry01m8p83Ysy8o8l83Cy83Ny1r83Yvy01m8p83Ysy8o8l83Cy83Ny");
    temp = regenerate_optimized_constant(string_constant_50);
    temp_1 = regenerate_optimized_constant(list(8,string_constant_51,
	    string_constant_52,string_constant_53,string_constant_54,
	    string_constant_55,string_constant_56,string_constant_57,
	    string_constant_58));
    add_class_to_environment(9,Qremote_procedure_declaration,
	    list_constant_2,Nil,temp,Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(LIST_2(string_constant_59,
	    string_constant_60)),Nil);
    Remote_procedure_declaration_class_description = 
	    lookup_global_or_kb_specific_property_value(Qremote_procedure_declaration,
	    Class_description_gkbprop);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qis_class_instance = STATIC_SYMBOL("IS-CLASS-INSTANCE",AB_package);
    Qtype_name = STATIC_SYMBOL("TYPE-NAME",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Kkind = STATIC_SYMBOL("KIND",Pkeyword);
    Kinclude_system_attributes = STATIC_SYMBOL("INCLUDE-SYSTEM-ATTRIBUTES",
	    Pkeyword);
    Kinclude_all_system_attributes = 
	    STATIC_SYMBOL("INCLUDE-ALL-SYSTEM-ATTRIBUTES",Pkeyword);
    Kinclude_all_system_attributes_except = 
	    STATIC_SYMBOL("INCLUDE-ALL-SYSTEM-ATTRIBUTES-EXCEPT",Pkeyword);
    Kinclude_attributes = STATIC_SYMBOL("INCLUDE-ATTRIBUTES",Pkeyword);
    Kexclude_attributes = STATIC_SYMBOL("EXCLUDE-ATTRIBUTES",Pkeyword);
    Qkind = STATIC_SYMBOL("KIND",AB_package);
    Qinclude_all_system_attributes = 
	    STATIC_SYMBOL("INCLUDE-ALL-SYSTEM-ATTRIBUTES",AB_package);
    Qinclude_all_system_attributes_except = 
	    STATIC_SYMBOL("INCLUDE-ALL-SYSTEM-ATTRIBUTES-EXCEPT",AB_package);
    Qincluded_system_attributes = 
	    STATIC_SYMBOL("INCLUDED-SYSTEM-ATTRIBUTES",AB_package);
    Qincluded_user_attributes = STATIC_SYMBOL("INCLUDED-USER-ATTRIBUTES",
	    AB_package);
    Qexcluded_user_attributes = STATIC_SYMBOL("EXCLUDED-USER-ATTRIBUTES",
	    AB_package);
    Qremote_procedure_argument_descriptions = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ARGUMENT-DESCRIPTIONS",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    list_constant_3 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qremote_procedure_argument_descriptions),
	    Qtype_specification_simple_expansion,list_constant_3);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_4 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_11 = STATIC_CONS(Qis_class_instance,list_constant_4);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qtype_name,Qsymbol);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_5 = STATIC_CONS(Qno_item,Qnil);
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    Qby_copy_with_handle = STATIC_SYMBOL("BY-COPY-WITH-HANDLE",AB_package);
    Qreference = STATIC_SYMBOL("REFERENCE",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)4L,Qmember,Qhandle,
	    Qby_copy_with_handle,Qreference);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_6);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qkind,list_constant_7);
    list_constant_14 = STATIC_CONS(Qinclude_all_system_attributes,
	    list_constant_4);
    list_constant_8 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qsymbol,
	    list_constant_8);
    list_constant_10 = STATIC_CONS(list_constant_9,Qnil);
    list_constant_15 = STATIC_CONS(Qincluded_system_attributes,
	    list_constant_10);
    list_constant_16 = STATIC_CONS(Qinclude_all_system_attributes_except,
	    list_constant_10);
    list_constant_17 = STATIC_CONS(Qincluded_user_attributes,list_constant_10);
    list_constant_18 = STATIC_CONS(Qexcluded_user_attributes,list_constant_10);
    list_constant_21 = STATIC_LIST((SI_Long)8L,list_constant_11,
	    list_constant_12,list_constant_13,list_constant_14,
	    list_constant_15,list_constant_16,list_constant_17,
	    list_constant_18);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qand,
	    Qincluded_user_attributes,Qexcluded_user_attributes);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_19);
    list_constant_22 = STATIC_LIST((SI_Long)3L,Qand,Qtype_name,
	    list_constant_20);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_21,list_constant_22);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_23,list_constant_8);
    define_type_specification_explicit_complex_type(Qremote_procedure_argument_descriptions,
	    list_constant_24);
    remote_procedure_argument_descriptions_evaluation_getter_1 = 
	    STATIC_FUNCTION(remote_procedure_argument_descriptions_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qremote_procedure_argument_descriptions,
	    remote_procedure_argument_descriptions_evaluation_getter_1);
    Qremote_procedure_name = STATIC_SYMBOL("REMOTE-PROCEDURE-NAME",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,Qtext);
    set_property_value_function(get_symbol_properties_function(Qremote_procedure_name),
	    Qtype_specification_simple_expansion,list_constant_1);
    define_type_specification_explicit_complex_type(Qremote_procedure_name,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qremote_procedure_name);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    remote_procedure_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(remote_procedure_name_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qremote_procedure_name,
	    remote_procedure_name_evaluation_setter_1);
    remote_procedure_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(remote_procedure_name_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qremote_procedure_name,
	    remote_procedure_name_evaluation_getter_1);
    Qremote_procedure_argument_description = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ARGUMENT-DESCRIPTION",AB_package);
    Qremote_procedure_returned_values_description = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-RETURNED-VALUES-DESCRIPTION",
	    AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qquote,Qdeclare);
    Qremote = STATIC_SYMBOL("REMOTE",AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qquote,Qremote);
    Qprocedure_name = STATIC_SYMBOL("PROCEDURE-NAME",AB_package);
    Qremote_procedure_type_list = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-TYPE-LIST",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qquote,Qnum_eq);
    list_constant_28 = STATIC_LIST((SI_Long)6L,list_constant_25,
	    list_constant_26,Qprocedure_name,Qremote_procedure_type_list,
	    list_constant_27,Qremote_procedure_type_list);
    list_constant_29 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)3L),
	    FIX((SI_Long)4L),FIX((SI_Long)6L));
    list_constant_52 = STATIC_LIST((SI_Long)3L,
	    Qremote_procedure_declaration,list_constant_28,list_constant_29);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qremote_procedure_name,
	    Qwhole_string);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qquote,Qnone);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qremote_procedure_name,
	    list_constant_30);
    Qremote_procedure_type = STATIC_SYMBOL("REMOTE-PROCEDURE-TYPE",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qquote,Qitem_or_value);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qremote_procedure_type,
	    list_constant_31,Qitem_or_datum);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qquote,Qvalue);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qremote_procedure_type,
	    list_constant_32,Qdatum);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qquote,Qquantity);
    list_constant_57 = STATIC_LIST((SI_Long)3L,Qremote_procedure_type,
	    list_constant_33,Qnumber);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qquote,Qinteger);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qremote_procedure_type,
	    list_constant_34);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qquote,Qlong);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qremote_procedure_type,
	    list_constant_35);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qquote,Qfloat);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qremote_procedure_type,
	    list_constant_36);
    list_constant_37 = STATIC_CONS(Qtext,Qnil);
    list_constant_38 = STATIC_CONS(Qquote,list_constant_37);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qremote_procedure_type,
	    list_constant_38);
    list_constant_39 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_40 = STATIC_CONS(Qquote,list_constant_39);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qremote_procedure_type,
	    list_constant_40);
    list_constant_41 = STATIC_CONS(Qquote,list_constant_4);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qremote_procedure_type,
	    list_constant_41);
    list_constant_42 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_43 = STATIC_CONS(Qquote,list_constant_42);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_42);
    list_constant_64 = STATIC_LIST((SI_Long)3L,Qremote_procedure_type,
	    list_constant_43,list_constant_44);
    list_constant_45 = STATIC_CONS(Qquote,list_constant_3);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_3);
    list_constant_65 = STATIC_LIST((SI_Long)3L,Qremote_procedure_type,
	    list_constant_45,list_constant_46);
    Qop = STATIC_SYMBOL("(",AB_package);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qquote,Qop);
    Qcp = STATIC_SYMBOL(")",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qquote,Qcp);
    list_constant_49 = STATIC_CONS(list_constant_47,Qnil);
    list_constant_50 = STATIC_CONS(list_constant_48,list_constant_49);
    Qnil_function = STATIC_SYMBOL("NIL-FUNCTION",AB_package);
    list_constant_66 = STATIC_LIST((SI_Long)4L,Qremote_procedure_type_list,
	    list_constant_50,Qnil,Qnil_function);
    Qremote_procedure_type_list_1 = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-TYPE-LIST-1",AB_package);
    list_constant_51 = STATIC_LIST_STAR((SI_Long)3L,list_constant_48,
	    Qremote_procedure_type_list_1,list_constant_49);
    list_constant_67 = STATIC_LIST((SI_Long)4L,Qremote_procedure_type_list,
	    list_constant_51,FIX((SI_Long)2L),Qcdr);
    list_constant_68 = STATIC_LIST((SI_Long)16L,list_constant_52,
	    list_constant_53,list_constant_54,list_constant_55,
	    list_constant_56,list_constant_57,list_constant_58,
	    list_constant_59,list_constant_60,list_constant_61,
	    list_constant_62,list_constant_63,list_constant_64,
	    list_constant_65,list_constant_66,list_constant_67);
    add_grammar_rules_function(list_constant_68);
    Qall = STATIC_SYMBOL("ALL",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qquote,Qall);
    Qremaining = STATIC_SYMBOL("REMAINING",AB_package);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qquote,Qremaining);
    list_constant_71 = STATIC_CONS(Qremote_procedure_type,Qnil);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)3L,list_constant_69,
	    list_constant_70,list_constant_71);
    Qcm = STATIC_SYMBOL(",",AB_package);
    list_constant_72 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_74 = STATIC_CONS(Qcm,list_constant_72);
    Qencode_remaining_into_remote_procedure_type_1 = 
	    STATIC_SYMBOL("ENCODE-REMAINING-INTO-REMOTE-PROCEDURE-TYPE-1",
	    AB_package);
    list_constant_81 = STATIC_LIST((SI_Long)4L,
	    Qremote_procedure_type_list_1,list_constant_73,
	    list_constant_74,Qencode_remaining_into_remote_procedure_type_1);
    Qremote_procedure_type_list_1_tail = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-TYPE-LIST-1-TAIL",AB_package);
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qquote,Qcm);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)3L,
	    Qremote_procedure_type_list_1_tail,list_constant_75,
	    list_constant_73);
    list_constant_77 = STATIC_LIST((SI_Long)3L,Qcm,FIX((SI_Long)1L),
	    FIX((SI_Long)5L));
    Qencode_remaining_into_remote_procedure_type_2 = 
	    STATIC_SYMBOL("ENCODE-REMAINING-INTO-REMOTE-PROCEDURE-TYPE-2",
	    AB_package);
    list_constant_82 = STATIC_LIST((SI_Long)4L,
	    Qremote_procedure_type_list_1,list_constant_76,
	    list_constant_77,Qencode_remaining_into_remote_procedure_type_2);
    list_constant_83 = STATIC_LIST((SI_Long)2L,
	    Qremote_procedure_type_list_1,Qremote_procedure_type_list_1_tail);
    list_constant_78 = STATIC_LIST((SI_Long)2L,Qcm,FIX((SI_Long)1L));
    list_constant_84 = STATIC_LIST((SI_Long)3L,
	    Qremote_procedure_type_list_1_tail,Qremote_procedure_type,
	    list_constant_78);
    list_constant_79 = STATIC_LIST_STAR((SI_Long)3L,
	    Qremote_procedure_type_list_1_tail,list_constant_75,
	    list_constant_71);
    list_constant_80 = STATIC_LIST_STAR((SI_Long)3L,Qcm,FIX((SI_Long)1L),
	    list_constant_72);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    list_constant_85 = STATIC_LIST((SI_Long)4L,
	    Qremote_procedure_type_list_1_tail,list_constant_79,
	    list_constant_80,Qsimplify_associative_operation);
    list_constant_86 = STATIC_LIST((SI_Long)5L,list_constant_81,
	    list_constant_82,list_constant_83,list_constant_84,
	    list_constant_85);
    add_grammar_rules_function(list_constant_86);
    Kall_remaining = STATIC_SYMBOL("ALL-REMAINING",Pkeyword);
    SET_SYMBOL_FUNCTION(Qencode_remaining_into_remote_procedure_type_1,
	    STATIC_FUNCTION(encode_remaining_into_remote_procedure_type_1,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qencode_remaining_into_remote_procedure_type_2,
	    STATIC_FUNCTION(encode_remaining_into_remote_procedure_type_2,
	    NIL,FALSE,1,1));
    Kgeneral_description = STATIC_SYMBOL("GENERAL-DESCRIPTION",Pkeyword);
    Kas_handle_p = STATIC_SYMBOL("AS-HANDLE-P",Pkeyword);
    Qreformat_remote_procedure_declaration_descriptions = 
	    STATIC_SYMBOL("REFORMAT-REMOTE-PROCEDURE-DECLARATION-DESCRIPTIONS",
	    AB_package);
    temp_2 = adjoin(2,Qreformat_remote_procedure_declaration_descriptions,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_2;
    temp_2 = adjoin(2,Qreformat_remote_procedure_declaration_descriptions,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_2;
    SET_SYMBOL_FUNCTION(Qreformat_remote_procedure_declaration_descriptions,
	    STATIC_FUNCTION(reformat_remote_procedure_declaration_descriptions,
	    NIL,FALSE,0,0));
    Qname_in_remote_system = STATIC_SYMBOL("NAME-IN-REMOTE-SYSTEM",AB_package);
    Quser_supplied_remote_name_qm = 
	    STATIC_SYMBOL("USER-SUPPLIED-REMOTE-NAME\?",AB_package);
    Qcompile_remote_procedure_declaration_for_slot = 
	    STATIC_SYMBOL("COMPILE-REMOTE-PROCEDURE-DECLARATION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_remote_procedure_declaration_for_slot,
	    STATIC_FUNCTION(compile_remote_procedure_declaration_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qremote_procedure_declaration,
	    SYMBOL_FUNCTION(Qcompile_remote_procedure_declaration_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qremote_procedure_declaration,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qput_box_translation_and_text_slot_value_for_remote_procedure_declaration 
	    = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-REMOTE-PROCEDURE-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_remote_procedure_declaration,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_remote_procedure_declaration,
	    NIL,FALSE,3,3));
    Qput_box_translation_and_text_slot_value = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_remote_procedure_declaration);
    set_get(Qremote_procedure_declaration,
	    Qput_box_translation_and_text_slot_value,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp_2 = CONS(Qremote_procedure_declaration,temp);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp_2,
	    Qclasses_which_define);
    string_constant = STATIC_STRING("~(~A~)");
    Qcompile_remote_procedure_name_for_slot = 
	    STATIC_SYMBOL("COMPILE-REMOTE-PROCEDURE-NAME-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_remote_procedure_name_for_slot,
	    STATIC_FUNCTION(compile_remote_procedure_name_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qremote_procedure_name,
	    SYMBOL_FUNCTION(Qcompile_remote_procedure_name_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qremote_procedure_name,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_1 = STATIC_STRING("none");
    Qwrite_remote_procedure_name_from_slot = 
	    STATIC_SYMBOL("WRITE-REMOTE-PROCEDURE-NAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_remote_procedure_name_from_slot,
	    STATIC_FUNCTION(write_remote_procedure_name_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qremote_procedure_name,
	    SYMBOL_FUNCTION(Qwrite_remote_procedure_name_from_slot),
	    Qslot_value_writer);
    Qput_name_in_remote_system = STATIC_SYMBOL("PUT-NAME-IN-REMOTE-SYSTEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_name_in_remote_system,
	    STATIC_FUNCTION(put_name_in_remote_system,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qname_in_remote_system,
	    SYMBOL_FUNCTION(Qput_name_in_remote_system),Qslot_putter);
    Qremote_procedure_name_structure = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-STRUCTURE",AB_package);
    Qreclaim_remote_procedure_name_structure_value = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-NAME-STRUCTURE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_remote_procedure_name_structure_value,
	    STATIC_FUNCTION(reclaim_remote_procedure_name_structure_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qremote_procedure_name_structure,
	    SYMBOL_FUNCTION(Qreclaim_remote_procedure_name_structure_value),
	    Qslot_value_reclaimer);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_scheduled_remote_procedure_start_g2_struct 
	    = STATIC_SYMBOL("SCHEDULED-REMOTE-PROCEDURE-START-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qscheduled_remote_procedure_start = 
	    STATIC_SYMBOL("SCHEDULED-REMOTE-PROCEDURE-START",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_scheduled_remote_procedure_start_g2_struct,
	    Qscheduled_remote_procedure_start,
	    Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qscheduled_remote_procedure_start,
	    Qg2_defstruct_structure_name_scheduled_remote_procedure_start_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_scheduled_remote_procedure_start == UNBOUND)
	The_type_description_of_scheduled_remote_procedure_start = Nil;
    string_constant_61 = 
	    STATIC_STRING("43Dy8m83mfy1n83mfy8n8k1l8n0000001l1n8y83-5hy1o83-Bny83-Bly83-Bmy83-Bkykrk0k0");
    temp = The_type_description_of_scheduled_remote_procedure_start;
    The_type_description_of_scheduled_remote_procedure_start = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_61));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_scheduled_remote_procedure_start_g2_struct,
	    The_type_description_of_scheduled_remote_procedure_start,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qscheduled_remote_procedure_start,
	    The_type_description_of_scheduled_remote_procedure_start,
	    Qtype_description_of_type);
    Qoutstanding_scheduled_remote_procedure_start_count = 
	    STATIC_SYMBOL("OUTSTANDING-SCHEDULED-REMOTE-PROCEDURE-START-COUNT",
	    AB_package);
    Qscheduled_remote_procedure_start_structure_memory_usage = 
	    STATIC_SYMBOL("SCHEDULED-REMOTE-PROCEDURE-START-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_62 = STATIC_STRING("1q83mfy8s83-nly09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_scheduled_remote_procedure_start_count);
    push_optimized_constant(Qscheduled_remote_procedure_start_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_62));
    Qchain_of_available_scheduled_remote_procedure_starts = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SCHEDULED-REMOTE-PROCEDURE-STARTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_scheduled_remote_procedure_starts,
	    Chain_of_available_scheduled_remote_procedure_starts);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_scheduled_remote_procedure_starts,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qscheduled_remote_procedure_start_count = 
	    STATIC_SYMBOL("SCHEDULED-REMOTE-PROCEDURE-START-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscheduled_remote_procedure_start_count,
	    Scheduled_remote_procedure_start_count);
    record_system_variable(Qscheduled_remote_procedure_start_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_scheduled_remote_procedure_starts_vector == UNBOUND)
	Chain_of_available_scheduled_remote_procedure_starts_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qscheduled_remote_procedure_start_structure_memory_usage,
	    STATIC_FUNCTION(scheduled_remote_procedure_start_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_scheduled_remote_procedure_start_count,
	    STATIC_FUNCTION(outstanding_scheduled_remote_procedure_start_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_scheduled_remote_procedure_start_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_scheduled_remote_procedure_start,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qscheduled_remote_procedure_start,
	    reclaim_structure_for_scheduled_remote_procedure_start_1);
    Qactivate_for_remote_procedure_declaration = 
	    STATIC_SYMBOL("ACTIVATE-FOR-REMOTE-PROCEDURE-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_remote_procedure_declaration,
	    STATIC_FUNCTION(activate_for_remote_procedure_declaration,NIL,
	    FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_remote_procedure_declaration);
    set_get(Qremote_procedure_declaration,Qactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qremote_procedure_declaration,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    Qdeactivate_for_remote_procedure_declaration = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-REMOTE-PROCEDURE-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_remote_procedure_declaration,
	    STATIC_FUNCTION(deactivate_for_remote_procedure_declaration,
	    NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_remote_procedure_declaration);
    set_get(Qremote_procedure_declaration,Qdeactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qremote_procedure_declaration,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_2 = 
	    STATIC_STRING("Argument error while starting remote procedure ~NF: ~a.");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qexecute_scheduled_remote_procedure_start = 
	    STATIC_SYMBOL("EXECUTE-SCHEDULED-REMOTE-PROCEDURE-START",
	    AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qexecute_scheduled_remote_procedure_start,
	    STATIC_FUNCTION(execute_scheduled_remote_procedure_start,NIL,
	    FALSE,2,2));
    Qtemporary_output = STATIC_SYMBOL("TEMPORARY-OUTPUT",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qg2_defstruct_structure_name_icp_socket_g2_struct = 
	    STATIC_SYMBOL("ICP-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_3 = 
	    STATIC_STRING("The ICP interface ~NF was unable to accept network messages to ~\n              start ~NF, because it was not connected.");
    string_constant_4 = 
	    STATIC_STRING("The ICP interface ~NF was unable to accept network messages to ~\n              start ~NF.  The socket is ~A.");
    string_constant_5 = 
	    STATIC_STRING("The remote procedure ~NF could not be started ~\n                 because of a problem with its arguments: ~A");
    string_constant_6 = 
	    STATIC_STRING("The argument ~NF was an item, ~\n                      not a value of the required type ~A");
    string_constant_7 = 
	    STATIC_STRING("The object argument ~NF was of class ~A, ~\n                    not of the required class ~A.");
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING(" for ~A was not of type integer.");
    array_constant_1 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    string_constant_9 = STATIC_STRING(" was not of the required type ~a.");
    string_constant_10 = 
	    STATIC_STRING("The argument ~A was not of the required type ~A");
    string_constant_11 = 
	    STATIC_STRING("~D arguments were required, but ~D arguments were supplied");
    Qunsigned_vector_16 = STATIC_SYMBOL("UNSIGNED-VECTOR-16",AB_package);
    string_constant_12 = 
	    STATIC_STRING("Error in remote procedure across interface ~NF: ~a");
    string_constant_13 = STATIC_STRING("Error in remote procedure: ~a");
    string_constant_14 = 
	    STATIC_STRING("Argument error while calling remote procedure ~NF: ~a");
    string_constant_15 = 
	    STATIC_STRING("~NF is not able to receive remote procedure calls to ~NF.  ~\n              Either the ICP connection has broken, or the remote system is ~\n              not running.");
    string_constant_16 = 
	    STATIC_STRING("Cannot execute remote procedure call to ~NF across ~NF, ~\n              because of a problem in its arguments: ~A");
    if (System_defined_rpcs == UNBOUND)
	System_defined_rpcs = Nil;
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    System_defined_rpc_prop = Qsystem_defined_rpc;
    Qg2_defstruct_structure_name_system_rpc_instance_g2_struct = 
	    STATIC_SYMBOL("SYSTEM-RPC-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsystem_rpc_instance = STATIC_SYMBOL("SYSTEM-RPC-INSTANCE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_system_rpc_instance_g2_struct,
	    Qsystem_rpc_instance,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsystem_rpc_instance,
	    Qg2_defstruct_structure_name_system_rpc_instance_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_system_rpc_instance == UNBOUND)
	The_type_description_of_system_rpc_instance = Nil;
    string_constant_63 = 
	    STATIC_STRING("43Dy8m83ncy1n83ncy8n8k1l8n0000001l1n8y83-61y1n83-EDy83-EBy83-ECykok0k0");
    temp = The_type_description_of_system_rpc_instance;
    The_type_description_of_system_rpc_instance = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_63));
    mutate_global_property(Qg2_defstruct_structure_name_system_rpc_instance_g2_struct,
	    The_type_description_of_system_rpc_instance,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsystem_rpc_instance,
	    The_type_description_of_system_rpc_instance,
	    Qtype_description_of_type);
    Qoutstanding_system_rpc_instance_count = 
	    STATIC_SYMBOL("OUTSTANDING-SYSTEM-RPC-INSTANCE-COUNT",AB_package);
    Qsystem_rpc_instance_structure_memory_usage = 
	    STATIC_SYMBOL("SYSTEM-RPC-INSTANCE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_64 = STATIC_STRING("1q83ncy8s83-rry09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_system_rpc_instance_count);
    push_optimized_constant(Qsystem_rpc_instance_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_64));
    Qchain_of_available_system_rpc_instances = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SYSTEM-RPC-INSTANCES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_system_rpc_instances,
	    Chain_of_available_system_rpc_instances);
    record_system_variable(Qchain_of_available_system_rpc_instances,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsystem_rpc_instance_count = STATIC_SYMBOL("SYSTEM-RPC-INSTANCE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsystem_rpc_instance_count,
	    System_rpc_instance_count);
    record_system_variable(Qsystem_rpc_instance_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_system_rpc_instances_vector == UNBOUND)
	Chain_of_available_system_rpc_instances_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsystem_rpc_instance_structure_memory_usage,
	    STATIC_FUNCTION(system_rpc_instance_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_system_rpc_instance_count,
	    STATIC_FUNCTION(outstanding_system_rpc_instance_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_system_rpc_instance_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_system_rpc_instance,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsystem_rpc_instance,
	    reclaim_structure_for_system_rpc_instance_1);
    if (Current_system_rpc_icp_socket_qm == UNBOUND)
	Current_system_rpc_icp_socket_qm = Nil;
    Qwrong_number_of_arguments = STATIC_SYMBOL("WRONG-NUMBER-OF-ARGUMENTS",
	    AB_package);
    string_constant_17 = 
	    STATIC_STRING("Error while beginning RPC call to ~ND: wanted ~NV args, got ~NV");
    Qargument_type_mismatch = STATIC_SYMBOL("ARGUMENT-TYPE-MISMATCH",
	    AB_package);
    string_constant_18 = 
	    STATIC_STRING("Error while beginning RPC call to ~ND: arg ~NV should be of type ~NT");
    Qsend_icp_resumable_rpc_return_values = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-RETURN-VALUES",AB_package);
    Qreclaim_after_rpc_return_values = 
	    STATIC_SYMBOL("RECLAIM-AFTER-RPC-RETURN-VALUES",AB_package);
    Qg2_api_test_1 = STATIC_SYMBOL("G2-API-TEST-1",AB_package);
    Qg2_api_test_1_system_rpc_internal = 
	    STATIC_SYMBOL("G2-API-TEST-1-SYSTEM-RPC-INTERNAL",AB_package);
    Qarg1 = STATIC_SYMBOL("ARG1",AB_package);
    list_constant_88 = STATIC_CONS(Qfloat,Qnil);
    list_constant_89 = STATIC_LIST_STAR((SI_Long)3L,Qarg1,Ktype,
	    list_constant_88);
    list_constant_90 = STATIC_CONS(list_constant_89,Qnil);
    mutate_global_property(Qg2_api_test_1,
	    make_system_rpc_1(Qg2_api_test_1_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_90,
	    Nil,T),list_constant_88),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_api_test_1,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_api_test_1_system_rpc_internal,
	    STATIC_FUNCTION(g2_api_test_1_system_rpc_internal,NIL,FALSE,2,2));
    string_constant_19 = STATIC_STRING("::");
    if (Prefer_kb_procedures_to_system_defined_p == UNBOUND)
	Prefer_kb_procedures_to_system_defined_p = Nil;
    Qg2_prefer_kb_procedures_to_system_defined = 
	    STATIC_SYMBOL("G2-PREFER-KB-PROCEDURES-TO-SYSTEM-DEFINED",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_prefer_kb_procedures_to_system_defined,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_prefer_kb_procedures_to_system_defined,
	    STATIC_FUNCTION(g2_prefer_kb_procedures_to_system_defined,NIL,
	    FALSE,1,1));
    Qg2_prefer_kb_procedures_to_system_defined_system_rpc_internal = 
	    STATIC_SYMBOL("G2-PREFER-KB-PROCEDURES-TO-SYSTEM-DEFINED-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qprefer = STATIC_SYMBOL("PREFER",AB_package);
    list_constant_91 = STATIC_LIST_STAR((SI_Long)3L,Qprefer,Ktype,
	    list_constant_4);
    list_constant_92 = STATIC_CONS(list_constant_91,Qnil);
    mutate_global_property(Qg2_prefer_kb_procedures_to_system_defined,
	    make_system_rpc_1(Qg2_prefer_kb_procedures_to_system_defined_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_92,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_prefer_kb_procedures_to_system_defined,
	    System_defined_rpcs);
    System_defined_rpcs = temp_2;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_prefer_kb_procedures_to_system_defined_system_rpc_internal,
	    STATIC_FUNCTION(g2_prefer_kb_procedures_to_system_defined_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    string_constant_20 = STATIC_STRING("call");
    string_constant_21 = STATIC_STRING("start");
    string_constant_22 = STATIC_STRING("Cannot ~A ~A, since: ~A");
    string_constant_23 = STATIC_STRING("Argument error ~Aing ~A:  ~A");
    string_constant_24 = 
	    STATIC_STRING("Cannot ~A ~A, since no procedure by that name exists.");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_25 = 
	    STATIC_STRING("Cannot ~A ~A, since it named the constant ~NC instead of a procedure.");
    string_constant_26 = 
	    STATIC_STRING("Cannot ~A ~A, since it names ~A~A, instead of a procedure.");
    string_constant_27 = 
	    STATIC_STRING("Cannot ~A ~A, since this interface is not authorized to start remote procedure calls.");
    string_constant_28 = 
	    STATIC_STRING("Cannot ~A ~A, since it is not active or has a status other than OK.");
    string_constant_29 = STATIC_STRING("Cannot ~A ~A.  ~A");
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qg2_defstruct_structure_name_system_rpc_g2_struct = 
	    STATIC_SYMBOL("SYSTEM-RPC-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreceive_start_or_call_remote_procedure_1 = 
	    STATIC_SYMBOL("RECEIVE-START-OR-CALL-REMOTE-PROCEDURE-1",
	    AB_package);
    Kerror_string = STATIC_SYMBOL("ERROR-STRING",Pkeyword);
    Qrpc_error = STATIC_SYMBOL("RPC-ERROR",AB_package);
    string_constant_30 = 
	    STATIC_STRING("Error while beginning RPC start of ~NF: ~NW");
    SET_SYMBOL_FUNCTION(Qreceive_start_or_call_remote_procedure_1,
	    STATIC_FUNCTION(receive_start_or_call_remote_procedure_1,NIL,
	    FALSE,4,4));
    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-CALL-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_current_remote_interface_lisp_side = 
	    STATIC_SYMBOL("G2-CURRENT-REMOTE-INTERFACE-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_current_remote_interface_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_31 = 
	    STATIC_STRING("The current procedure was not invoked via RPC");
    SET_SYMBOL_FUNCTION(Qg2_current_remote_interface_lisp_side,
	    STATIC_FUNCTION(g2_current_remote_interface_lisp_side,NIL,
	    FALSE,0,0));
    string_constant_32 = STATIC_STRING("Calling procedure ");
    string_constant_33 = STATIC_STRING("Starting procedure ");
    array_constant_2 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    Qsend_icp_resumable_rpc_error_to_caller = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-ERROR-TO-CALLER",AB_package);
    Qsend_icp_resumable_rpc_error = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-ERROR",AB_package);
    Qpropagate_error_to_remote_caller_reclaim = 
	    STATIC_SYMBOL("PROPAGATE-ERROR-TO-REMOTE-CALLER-RECLAIM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpropagate_error_to_remote_caller_reclaim,
	    STATIC_FUNCTION(propagate_error_to_remote_caller_reclaim,NIL,
	    FALSE,2,2));
    Qremote_procedure_call_start_map = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-CALL-START-MAP",AB_package);
    Qremove_remote_procedure_calls_from_start_map = 
	    STATIC_SYMBOL("REMOVE-REMOTE-PROCEDURE-CALLS-FROM-START-MAP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qremove_remote_procedure_calls_from_start_map,
	    STATIC_FUNCTION(remove_remote_procedure_calls_from_start_map,
	    NIL,FALSE,3,3));
    string_constant_34 = STATIC_STRING("~A");
    string_constant_35 = STATIC_STRING("~NF");
    SET_SYMBOL_FUNCTION(Qreclaim_after_rpc_return_values,
	    STATIC_FUNCTION(reclaim_after_rpc_return_values,NIL,FALSE,1,1));
    string_constant_36 = 
	    STATIC_STRING("Attempting to return an object of class ~A ~\n             to a remote procedure caller.  The caller ~\n             expects a value of type ~A instead.");
    string_constant_37 = 
	    STATIC_STRING("Attempting to return an object of class ~A ~\n                    to a remote procedure caller.  This object ~\n                    is not of the declared class ~A.");
    array_constant_3 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    string_constant_38 = 
	    STATIC_STRING(" to a remote procedure caller.  The caller ~\n                      expects an object of class ~A instead.");
    array_constant_4 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    string_constant_39 = 
	    STATIC_STRING("Cannot return results from the remote procedure ~NF, since ~A");
    string_constant_40 = 
	    STATIC_STRING("~A values were returned, but the remote procedure declaration ~\n                      ~NF declares that ~a values would be returned.");
    string_constant_41 = 
	    STATIC_STRING("Procedure ~NF is requesting more values than ~NF can return.");
    string_constant_42 = STATIC_STRING("The returned value at position ~D, ");
    string_constant_43 = 
	    STATIC_STRING(" was not of the type ~NT, as required by the ~\n                          declaration for ~NF.");
    Qreceive_remote_procedure_error_for_caller = 
	    STATIC_SYMBOL("RECEIVE-REMOTE-PROCEDURE-ERROR-FOR-CALLER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreceive_remote_procedure_error_for_caller,
	    STATIC_FUNCTION(receive_remote_procedure_error_for_caller,NIL,
	    FALSE,5,5));
    string_constant_44 = STATIC_STRING("Remote procedure call to ");
    string_constant_45 = STATIC_STRING("Remote procedure start to ");
    array_constant_8 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)35L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)36L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)37L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)47L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)57344L);
    string_constant_46 = STATIC_STRING(" ~a");
    string_constant_47 = STATIC_STRING(" for the following reason:~%~a");
    array_constant_10 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_87,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)57344L);
    string_constant_48 = STATIC_STRING(" for the interface ~NF");
    string_constant_49 = 
	    STATIC_STRING(" has broken.  It was used for the remote call to ~NF.");
    Qabort_outgoing_remote_procedure_call = 
	    STATIC_SYMBOL("ABORT-OUTGOING-REMOTE-PROCEDURE-CALL",AB_package);
    SET_SYMBOL_FUNCTION(Qabort_outgoing_remote_procedure_call,
	    STATIC_FUNCTION(abort_outgoing_remote_procedure_call,NIL,FALSE,
	    1,1));
    Qreceive_remote_procedure_asynchronous_abort = 
	    STATIC_SYMBOL("RECEIVE-REMOTE-PROCEDURE-ASYNCHRONOUS-ABORT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreceive_remote_procedure_asynchronous_abort,
	    STATIC_FUNCTION(receive_remote_procedure_asynchronous_abort,
	    NIL,FALSE,2,2));
}
