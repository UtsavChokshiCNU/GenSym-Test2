/* pcgrm.c
 * Input file:  proc-gram.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pcgrm.h"


static Object Qnone;               /* none */

/* COMPILE-CLASS-OF-PROCEDURE-INVOCATION?-FOR-SLOT */
Object compile_class_of_procedure_invocation_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(157,0);
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

static Object Qunreserved_symbol;  /* unreserved-symbol */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* CLASS-OF-PROCEDURE-INVOCATION?-EVALUATION-SETTER */
Object class_of_procedure_invocation_qm_evaluation_setter(evaluation_value,
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

    x_note_fn_call(157,1);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL(Last_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL(Context_of_type_failure,context_of_type_failure,3);
	    PUSH_SPECIAL(Reason_for_type_failure,reason_for_type_failure,2);
	      PUSH_SPECIAL(Type_at_type_failure,type_at_type_failure,1);
		PUSH_SPECIAL(Value_at_type_failure,value_at_type_failure,0);
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
		      goto end_class_of_procedure_invocation_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunreserved_symbol),
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
    else
	result = VALUES_1(Qnone);
  end_class_of_procedure_invocation_qm_evaluation_setter:
    return result;
}

/* CLASS-OF-PROCEDURE-INVOCATION?-EVALUATION-GETTER */
Object class_of_procedure_invocation_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(157,2);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

/* WRITE-CLASS-OF-PROCEDURE-INVOCATION?-FROM-SLOT */
Object write_class_of_procedure_invocation_qm_from_slot(class_qm,
	    gensymed_symbol)
    Object class_qm, gensymed_symbol;
{
    x_note_fn_call(157,3);
    if (class_qm)
	return twrite_symbol(1,class_qm);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

/* FIX-CASE-CHOICE */
Object fix_case_choice(form)
    Object form;
{
    Object label;

    x_note_fn_call(157,4);
    label = FIRST(form);
    if (EQ(label,Qotherwise) || CONSP(label) && memq_function(Qotherwise,
	    label))
	return VALUES_2(Bad_phrase,Qotherwise);
    else if (ATOM(label) || INLINE_DOUBLE_FLOAT_VECTOR_P(label) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(label)) == 
	    (SI_Long)1L)
	return phrase_cons(phrase_cons(label,Nil),CDR(form));
    else
	return phrase_cons(CDR(label),CDR(form));
}

/* NIL-FUNCTION */
Object nil_function(x)
    Object x;
{
    x_note_fn_call(157,5);
    return VALUES_1(Nil);
}

/* COMPILE-PROCEDURE-NAME?-FOR-SLOT */
Object compile_procedure_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(157,6);
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

/* WRITE-PROCEDURE-NAME?-FROM-SLOT */
Object write_procedure_name_qm_from_slot(procedure_name_qm,gensymed_symbol)
    Object procedure_name_qm, gensymed_symbol;
{
    x_note_fn_call(157,7);
    if ( !TRUEP(procedure_name_qm))
	return twrite_symbol(1,Qnone);
    else
	return twrite(procedure_name_qm);
}

/* WRITE-READ-ONLY-PROCEDURE-NAME?-FROM-SLOT */
Object write_read_only_procedure_name_qm_from_slot(procedure_name_qm,
	    gensymed_symbol)
    Object procedure_name_qm, gensymed_symbol;
{
    x_note_fn_call(157,8);
    if ( !TRUEP(procedure_name_qm))
	return twrite_symbol(1,Qnone);
    else
	return twrite(procedure_name_qm);
}

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object Qstandard_or_class_qualified_symbol_qm;  /* standard-or-class-qualified-symbol? */

/* PROCEDURE-NAME?-EVALUATION-SETTER */
Object procedure_name_qm_evaluation_setter(evaluation_value,frame,
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

    x_note_fn_call(157,9);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL(Last_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL(Context_of_type_failure,context_of_type_failure,3);
	    PUSH_SPECIAL(Reason_for_type_failure,reason_for_type_failure,2);
	      PUSH_SPECIAL(Type_at_type_failure,type_at_type_failure,1);
		PUSH_SPECIAL(Value_at_type_failure,value_at_type_failure,0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_2))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_3,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_procedure_name_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstandard_or_class_qualified_symbol_qm),
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
  end_procedure_name_qm_evaluation_setter:
    return result;
}

/* PROCEDURE-NAME?-EVALUATION-GETTER */
Object procedure_name_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(157,10);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstandard_or_class_qualified_symbol_qm),
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

/* READ-ONLY-PROCEDURE-NAME?-EVALUATION-GETTER */
Object read_only_procedure_name_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(157,11);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstandard_or_class_qualified_symbol_qm),
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

/* FIX-PROCEDURE-DEFINITION */
Object fix_procedure_definition(form)
    Object form;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value, item;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object type, local_name, ab_loop_list__1, ab_loopvar__3, ab_loopvar__4;

    x_note_fn_call(157,12);
    if (IFIX(length(form)) == (SI_Long)4L) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	car_new_value = FIRST(form);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = SECOND(form);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = THIRD(form);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = FOURTH(form);
	M_CAR(gensymed_symbol_1) = car_new_value;
	form = gensymed_symbol;
    }
    item = Nil;
    ab_loop_list_ = FOURTH(form);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CAR(item);
    if (SYMBOLP(temp))
	ab_loopvar__2 = phrase_cons(item,Nil);
    else {
	type = SECOND(item);
	local_name = Nil;
	ab_loop_list__1 = CDAR(item);
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	local_name = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loopvar__4 = phrase_cons(phrase_list_2(local_name,type),Nil);
	if (ab_loopvar__4) {
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = last(ab_loopvar__4,_);
	}
	goto next_loop_1;
      end_loop_1:
	goto end_1;
	ab_loopvar__2 = Qnil;
      end_1:;
    }
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    goto end_2;
    ab_loopvar_ = Qnil;
  end_2:;
    M_FOURTH(form) = ab_loopvar_;
    return VALUES_1(form);
}

/* CONVERT-TO-TRUE-LIST */
Object convert_to_true_list(x)
    Object x;
{
    Object y, temp;

    x_note_fn_call(157,13);
    y = x;
  next_loop:
    if (ATOM(y))
	goto end_loop;
    temp = CDR(y);
    if (ATOM(temp) && CDR(y))
	M_CDR(y) = Nil;
    y = CDR(y);
    goto next_loop;
  end_loop:;
    return VALUES_1(x);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object string_constant;     /* "CALL NEXT METHOD is only available within a method" */

/* TEST-CALL-NEXT-METHOD-PARSE */
Object test_call_next_method_parse(next_method_parse)
    Object next_method_parse;
{
    Object frame_qm, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(157,14);
    frame_qm = ISVREF(Current_edit_state,(SI_Long)3L);
    if (frame_qm) {
	if (SIMPLE_VECTOR_P(frame_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_qm)) > (SI_Long)2L && 
		 !EQ(ISVREF(frame_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame_qm,(SI_Long)1L);
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
		    IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(next_method_parse);
    else
	return VALUES_2(Bad_phrase,string_constant);
}

static Object string_constant_1;   /* "1o1n83-9Jy1q83-2Ry1m9k9l1m9k8l1m9k833iy83-2y83lny1o83-qDylpq1n83-9Ky1o1m9k8l1m9k833iy83-2y83lny1n83-qEyno1m83=My83-j3y1n83-j3y1m" */

static Object string_constant_2;   /* "1m9k8l1m9k83ASy1l83-qHy" */

/* EXTEND-PROCEDURE-GRAMMAR */
Object extend_procedure_grammar()
{
    XDeclare_area(1);

    x_note_fn_call(157,15);
    if (PUSH_AREA(Dynamic_area,0)) {
	clear_optimized_constants();
	push_optimized_constant(Qquote);
	push_optimized_constant(Qnum_eq);
	add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_1,
		string_constant_2)));
    }
    POP_AREA(0);
    return VALUES_1(Evaluation_true_value);
}

Object Procedure_function_template_alist = UNBOUND;

/* DEF-PROCEDURE-FUNCTION-TEMPLATE */
Object def_procedure_function_template(template_1)
    Object template_1;
{
    Object gensymed_symbol, gensymed_symbol_1, template_name, template_cons;

    x_note_fn_call(157,16);
    gensymed_symbol = template_1;
    gensymed_symbol_1 = Procedure_function_template_alist;
    template_name = CAR(gensymed_symbol);
    template_cons = gensymed_symbol_1;
  next_loop:
    if ( !TRUEP(template_cons))
	goto end_loop;
    if (EQ(template_name,CAAR(template_cons))) {
	M_CAR(template_cons) = gensymed_symbol;
	return VALUES_1(template_name);
    }
    template_cons = M_CDR(template_cons);
    goto next_loop;
  end_loop:
    Procedure_function_template_alist = CONS(gensymed_symbol,
	    gensymed_symbol_1);
    return VALUES_1(template_name);
    return VALUES_1(Qnil);
}

void proc_gram_INIT()
{
    Object class_of_procedure_invocation_qm_evaluation_setter_1;
    Object class_of_procedure_invocation_qm_evaluation_getter_1;
    Object procedure_name_qm_evaluation_setter_1;
    Object procedure_name_qm_evaluation_getter_1;
    Object read_only_procedure_name_qm_evaluation_getter_1, gensymed_symbol;
    Object list_constant_14, Qother, Qvar_spot, AB_package, list_constant_13;
    Object Qexpression, Qthere_exists_scope, Qthere_exists_literal;
    Object list_constant_12, Qlocal_name_var_spot, Qfailed_to_receive_a_value;
    Object list_constant_11, list_constant_10, Qhas_no_current_value;
    Object Qdesignation, list_constant_9, Qhas_a_current_value;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object Qsimplify_associative_operation, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, Qextend_procedure_grammar;
    Object Qfunction_keeps_procedure_environment_valid_qm, string_constant_54;
    Object string_constant_53, Qtest_call_next_method_parse;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47, Qend;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object Qnil_function, string_constant_42, Qconvert_to_true_list;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, Qsc;
    Object Qproc_local_name_element, Qproc_local_name_declr_1;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object Qfix_procedure_definition, string_constant_27, Qproc_parameter;
    Object Qproc_parameter_list_1, Qread_only_procedure_name_qm;
    Object Qtype_specification_simple_expansion, Qprocedure_name_qm, Qnamed;
    Object list_constant_4, Qab_or, Qslot_value_writer;
    Object Qwrite_read_only_procedure_name_qm_from_slot;
    Object Qwrite_procedure_name_qm_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_procedure_name_qm_for_slot;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, Qtranslate_role_and_preposition;
    Object string_constant_13, Qfix_case_choice, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, string_constant_4;
    Object Qwrite_class_of_procedure_invocation_qm_from_slot;
    Object Qclass_of_procedure_invocation_qm, list_constant_8, list_constant_7;
    Object list_constant_6, Qprocedure_invocation, list_constant_5, Qno_item;
    Object Qcompile_class_of_procedure_invocation_qm_for_slot;
    Object string_constant_3;

    x_note_fn_call(157,17);
    SET_PACKAGE("AB");
    string_constant_3 = 
	    STATIC_STRING("1n1m837xy1m9k83Zy1m837xy1m9k831jy1m837xy83-Gy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_3));
    AB_package = STATIC_PACKAGE("AB");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qclass_of_procedure_invocation_qm = 
	    STATIC_SYMBOL("CLASS-OF-PROCEDURE-INVOCATION\?",AB_package);
    Qcompile_class_of_procedure_invocation_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-CLASS-OF-PROCEDURE-INVOCATION\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_class_of_procedure_invocation_qm_for_slot,
	    STATIC_FUNCTION(compile_class_of_procedure_invocation_qm_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qclass_of_procedure_invocation_qm,
	    SYMBOL_FUNCTION(Qcompile_class_of_procedure_invocation_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qclass_of_procedure_invocation_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_4 = STATIC_CONS(Qno_item,Qnil);
    list_constant_5 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_4,Qnil,
	    Qnil);
    set_property_value_function(get_symbol_properties_function(Qclass_of_procedure_invocation_qm),
	    Qtype_specification_simple_expansion,list_constant_5);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qmember,Qprocedure_invocation);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qunreserved_symbol);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_4,
	    list_constant_6,list_constant_7);
    define_type_specification_explicit_complex_type(Qclass_of_procedure_invocation_qm,
	    list_constant_1);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qclass_of_procedure_invocation_qm);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    class_of_procedure_invocation_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(class_of_procedure_invocation_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qclass_of_procedure_invocation_qm,
	    class_of_procedure_invocation_qm_evaluation_setter_1);
    class_of_procedure_invocation_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(class_of_procedure_invocation_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qclass_of_procedure_invocation_qm,
	    class_of_procedure_invocation_qm_evaluation_getter_1);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_class_of_procedure_invocation_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-CLASS-OF-PROCEDURE-INVOCATION\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_class_of_procedure_invocation_qm_from_slot,
	    STATIC_FUNCTION(write_class_of_procedure_invocation_qm_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qclass_of_procedure_invocation_qm,
	    SYMBOL_FUNCTION(Qwrite_class_of_procedure_invocation_qm_from_slot),
	    Qslot_value_writer);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_4 = 
	    STATIC_STRING("1r1m839my83=xy1m83EZy831Py1m83Eay839my1m83Eay83EZy1o83-9Uy83-jGyl9k1n83-jGy1n83Eay1m9l83vy83Eay1nmln1o83-jGy1n83Eay1m9l83vy83-jG");
    string_constant_5 = STATIC_STRING("y1nmln9m");
    clear_optimized_constants();
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_4,
	    string_constant_5)));
    string_constant_6 = 
	    STATIC_STRING("1m1m83=My83-iWy1n83-iWy1n83*Zy1m9k9l83Eay1n83Ahyln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_6));
    string_constant_7 = 
	    STATIC_STRING("1o1m83EXy83-iqy1m83EXy83-ipy1n83-iqy1o1m9k8312y83EZy1m9k832Sy83=My1n83-YCymo1n83-ipy1q1m9k8312y83EZy1m9k832Sy83=My1m9k8332y83EXy");
    string_constant_8 = STATIC_STRING("1o83-YBymoq");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_7,
	    string_constant_8)));
    Qend = STATIC_SYMBOL("END",AB_package);
    Qfix_case_choice = STATIC_SYMBOL("FIX-CASE-CHOICE",AB_package);
    string_constant_9 = 
	    STATIC_STRING("13Ey1m83=My83-iZy1n83-iZy1q1m9k83-LVy1m9k83-9y83=py1m9k83-Ay1m9k83-Ty83-lCy2m83-LXynq1n83-lCy1m83-Tly1m9k9l1ll1n83-lCy1n83-Tly1m");
    string_constant_10 = 
	    STATIC_STRING("9k83-ay1m9k9l1ll1p83-lCy1o83-LWy1m9k83-ay83-lDy1m9k9l1nmln9m9n1o83-lDy1n83-LWy1m9k83-ay83-lDy1nmln9m1m83-lDy83-Tly1n83-lDy1m83-T");
    string_constant_11 = 
	    STATIC_STRING("ly1m9k83-ayl1m83-lDy83-Tmy1n83-lDy1m83-Tmy1m9k83-ayl1o83-LWy1n83-LZy1m9k83-Py83EXy1mln9o1m83-Tly83-LWy1n83-Tmy1n1m9k83XKy1m9k83-");
    string_constant_12 = 
	    STATIC_STRING("Py83EXy1mln1m83-LZy83-LYy1o83-LZy1n83-LYy1m9k83vy83-LZy1nmln9m1m83-LYy83-Hy1m83-LYy83-6y1m83-LYy83-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qend);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qfix_case_choice);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12)));
    SET_SYMBOL_FUNCTION(Qfix_case_choice,STATIC_FUNCTION(fix_case_choice,
	    NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qfix_case_choice);
    string_constant_13 = 
	    STATIC_STRING("1o1m83=My83-j=y1m83=My83-ijy1n83-j=y1m1m9k83-l=y834Py2l83-l0ym1n83-ijy1n1m9k8357y1m9k8312y83EZy1m83-T3yn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_13));
    Qtranslate_role_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-AND-PREPOSITION",AB_package);
    string_constant_14 = 
	    STATIC_STRING("1y1m83=My83-imy1n83-imy1q1m9k83=Iy83*Zy1m9k9l1m9k838Dy83-ity834Py2m83-U8y1mmpq1n83-ity1m83-Gy1m9k830Iy1m83=byl1n83-ity1n83loy830");
    string_constant_15 = 
	    STATIC_STRING("By1m9k830Iy1n83=bylm1n83-ity1u1m9k83-2y1m9k8319y1m9k83*Iy83=Zy1m9k83ANy1m9k83-qy1m9k83=hy1m9k83-Ty833*y1m9k830Iy1n83=by1m83oOylt");
    string_constant_16 = 
	    STATIC_STRING("1n83-ity1t1m9k83-2y1m9k8319y1m9k83*Iy83=Zy1m9k83-qy1m9k83=hy1m9k83-Ty833*y1m9k830Iy1n83=by1m83fIyls1o83loy1m83-Gy83Y6y1mlm9m1n83");
    string_constant_17 = 
	    STATIC_STRING("loy1m83-Yy1m9k83*Xy1m838Eyl1n83loy1m1m9k83=hy1m9k83-Ty1m834Zy83=hy1n83loy1s1m9k83-2y1m9k8319y1m9k83*Iy83=Zy1m9k83ANy1m9k83-qy1m9");
    string_constant_18 = 
	    STATIC_STRING("k83=hy1m9k83-Ty1m83oOyl1n83loy1r1m9k83-2y1m9k8319y1m9k83*Iy83=Zy1m9k83-qy1m9k83=hy1m9k83-Ty1m83fIyl1n83loy1q1m9k83-2y1m9k8319y1m");
    string_constant_19 = 
	    STATIC_STRING("9k83*Iy1m9k83=ay1m9k83-=Xy1m9k83-Ty1m83-=Xyl1n83loy1q1m9k83-2y1m9k8319y1m9k83*Iy1m9k83=Yy1m9k83A2y1m9k83-Ty1m83A2yl1n83loy1n83-G");
    string_constant_20 = STATIC_STRING("y1m9k8319y1m9k83gMy1m83kjyl");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qtranslate_role_and_preposition);
    add_grammar_rules_function(regenerate_optimized_constant(list(7,
	    string_constant_14,string_constant_15,string_constant_16,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20)));
    string_constant_21 = 
	    STATIC_STRING("1t1m83=My83-iny1n83-iny1q1m9k83=Iy83*Zy1m9k9l83-ixy83-iwy834Py2n83-U9y2lmopq1n83-ixy1n839my83-rry839my1nmln1n83-ixy1p839my83-rry");
    string_constant_22 = 
	    STATIC_STRING("839my1m9k83*uy839my1omlnp1m83-rry1m9k83=3y1n83-rry1m1m9k838Cy1m9k83=3y83-Rky1m83-iwy1m9k830Iy1n83-iwy1n1m9k830Iy1m9k83*Xy1m9k83E");
    string_constant_23 = 
	    STATIC_STRING("Hy83-RVy1n83-iwy1q1m9k830Iy1m9k83*Xy1m9k83EHy1m9k83day1m9k83lIy1m9k83g9y83-RXy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_21,
	    string_constant_22,string_constant_23)));
    string_constant_24 = 
	    STATIC_STRING("1o1m83=My83-ioy1n83-ioy1n1m9k9l1m9k83=3y839Fy1m83-WOyn1m839Fy83-Vy1m839Fy83-6y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qgo);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_24));
    Qnil_function = STATIC_SYMBOL("NIL-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qnil_function,STATIC_FUNCTION(nil_function,NIL,
	    FALSE,1,1));
    Qfix_procedure_definition = STATIC_SYMBOL("FIX-PROCEDURE-DEFINITION",
	    AB_package);
    string_constant_25 = 
	    STATIC_STRING("1t1o834Qy1n834Ry83-j-y83-jCy2mlmn9k1n83-jCy1m83-9Oy83-jDy2llm1m83-jCy83-jDy1n83-jDy1m83-9Ly83YHy1mlm1n83-jDy83YHy1m0l1m8306y834R");
    string_constant_26 = 
	    STATIC_STRING("y1m8306y1m9l83Zy1o83-j-y1m1m9l83-9y1m9l83-Ay09m1o83-j-y1n1m9l83-9y83-j*y1m9l83-Aym9n");
    clear_optimized_constants();
    push_optimized_constant(Qfix_procedure_definition);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnil_function);
    push_optimized_constant(Qcdr);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_25,
	    string_constant_26)));
    Qprocedure_name_qm = STATIC_SYMBOL("PROCEDURE-NAME\?",AB_package);
    Qcompile_procedure_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-PROCEDURE-NAME\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_procedure_name_qm_for_slot,
	    STATIC_FUNCTION(compile_procedure_name_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qprocedure_name_qm,
	    SYMBOL_FUNCTION(Qcompile_procedure_name_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qprocedure_name_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_procedure_name_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-PROCEDURE-NAME\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_procedure_name_qm_from_slot,
	    STATIC_FUNCTION(write_procedure_name_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qprocedure_name_qm,
	    SYMBOL_FUNCTION(Qwrite_procedure_name_qm_from_slot),
	    Qslot_value_writer);
    Qread_only_procedure_name_qm = 
	    STATIC_SYMBOL("READ-ONLY-PROCEDURE-NAME\?",AB_package);
    Qwrite_read_only_procedure_name_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-PROCEDURE-NAME\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_procedure_name_qm_from_slot,
	    STATIC_FUNCTION(write_read_only_procedure_name_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qread_only_procedure_name_qm,
	    SYMBOL_FUNCTION(Qwrite_read_only_procedure_name_qm_from_slot),
	    Qslot_value_writer);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_4,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qprocedure_name_qm),
	    Qtype_specification_simple_expansion,list_constant_3);
    define_type_specification_explicit_complex_type(Qprocedure_name_qm,
	    list_constant_3);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,Qprocedure_name_qm);
    Qstandard_or_class_qualified_symbol_qm = 
	    STATIC_SYMBOL("STANDARD-OR-CLASS-QUALIFIED-SYMBOL\?",AB_package);
    procedure_name_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(procedure_name_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qprocedure_name_qm,
	    procedure_name_qm_evaluation_setter_1);
    procedure_name_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(procedure_name_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qprocedure_name_qm,
	    procedure_name_qm_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qread_only_procedure_name_qm),
	    Qtype_specification_simple_expansion,list_constant_3);
    define_type_specification_explicit_complex_type(Qread_only_procedure_name_qm,
	    list_constant_3);
    read_only_procedure_name_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_procedure_name_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_procedure_name_qm,
	    read_only_procedure_name_qm_evaluation_getter_1);
    Qproc_parameter_list_1 = STATIC_SYMBOL("PROC-PARAMETER-LIST-1",AB_package);
    Qproc_parameter = STATIC_SYMBOL("PROC-PARAMETER",AB_package);
    add_grammar_rules_for_list(2,Qproc_parameter_list_1,Qproc_parameter);
    string_constant_27 = 
	    STATIC_STRING("1o1n83-j+y1n83*Zy1m9k83-Py83EYy1mln1m83EYy1m1m9k83-Gy83-Gy1m83-9Ny1m9k83-hy1m83YIy1m1m9k83-Gy83-Gy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_27));
    SET_SYMBOL_FUNCTION(Qfix_procedure_definition,
	    STATIC_FUNCTION(fix_procedure_definition,NIL,FALSE,1,1));
    string_constant_28 = 
	    STATIC_STRING("1r1m83EYy1m9k83-hy1m83EYy1m9k83-2y1m83EYy1m9k83Gy1m83EYy1m9k832ny1m83EYy1m9k83Sy1m83EYy1m9k9l1m83EYy1m9k83=By");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_28));
    string_constant_29 = 
	    STATIC_STRING("1p1n83EYy1m9k830my83-Hy1n83EYy1m9k83*ly83=oy1n83EYy1m9k8377y83=Ky1n83EYy1m9k830Sy1l830Sy1n83EYy1m9k8s1l8s");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_29));
    string_constant_30 = 
	    STATIC_STRING("1q1m83YIy1m9k83-2y1m83YIy1m9k83Gy1m83YIy1m9k832ny1m83YIy1m9k83Sy1m83YIy1m9k9l1m83YIy1m9k83=By");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_30));
    string_constant_31 = 
	    STATIC_STRING("1v1n83YIy1m9k830Sy1l830Sy1n83YIy1m9k8s1l8s1n83YIy1m9k830my83-Hy1n83-9My1m9k83*ly83=oy1n83-9My1m9k8377y83=Ky1o83-9Oy1n1m9k9l1m9k8");
    string_constant_32 = 
	    STATIC_STRING("3-9y1m9k83-Ayl9m1n83-9Oy1o1m9k9l1m9k83-9y83EYy1m9k83-Ay1ln1o83-9Oy1o1m9k9l1m9k83-9y83-j1y1m9k83-Ayn9n1n83-j1y1n83EYy1m9k83vy83EY");
    string_constant_33 = 
	    STATIC_STRING("y1nmln1o83-j1y1n83EYy1m9k83vy83-j1y1nmln9o1o83-9Ly1m83-iuy1m9k83-ayl9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qnil_function);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_31,
	    string_constant_32,string_constant_33)));
    Qproc_local_name_declr_1 = STATIC_SYMBOL("PROC-LOCAL-NAME-DECLR-1",
	    AB_package);
    Qproc_local_name_element = STATIC_SYMBOL("PROC-LOCAL-NAME-ELEMENT",
	    AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    add_grammar_rules_for_list(3,Qproc_local_name_declr_1,
	    Qproc_local_name_element,Qsc);
    string_constant_34 = 
	    STATIC_STRING("1q1n83-ivy1n83*Zy1m9k83-Py83EYy1mln1n83-ivy1n83-2Sy1m9k83-Py83EYy1mln1n83-ivy1p83*Zy1m9k83-Py83-9Ny1m9k9l83EZy1nlnp1n83-ivy1p83*");
    string_constant_35 = 
	    STATIC_STRING("Zy1m9k83-Py83YIy1m9k9l839my1nlnp1n83-ivy1p83*Zy1m9k83-Py83-9My1m9k9l839my1nlnp1n83-ivy1p83*Zy1m9k83-Py83-9My1m9k9l83EZy1nlnp");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_34,
	    string_constant_35)));
    string_constant_36 = STATIC_STRING("1m1m83EXy83=My1m83=My83YHy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_36));
    Qconvert_to_true_list = STATIC_SYMBOL("CONVERT-TO-TRUE-LIST",AB_package);
    string_constant_37 = 
	    STATIC_STRING("1q1n83YHy1m1m9k83qVy834Py2l83qYym1o834Py1n839Fy1m9k83-Py834Py2l1m83-qgyln9l1o834Py1m83EXy83-iby2llm9l1o834Py1m9k9m09n1o83-iby1m9");
    string_constant_38 = STATIC_STRING("k9m09n1n83-iby1m1m9k83-ay834Pym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qconvert_to_true_list);
    push_optimized_constant(Qend);
    push_optimized_constant(Qnil_function);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_37,
	    string_constant_38)));
    string_constant_39 = 
	    STATIC_STRING("1p1n83YHy1u1m9k83qVy834Py1m9k830Py1m9k9l1m9k83-9y83*Zy1m9k83vy83*Zy1m9k83-Ay834Py1p83-gby2l83qYymqs2l83qYyu1n83YHy1s1m9k83qVy834");
    string_constant_40 = 
	    STATIC_STRING("Py1m9k830Py1m9k9l1m9k83-9y83*Zy1m9k83-Ay834Py1o83-gcy2l83qYymq2l83qYys1m83=My83-j2y1n83-j2y1o1m9k83-nvy839my1m9k83vy839my1n83-nw");
    string_constant_41 = 
	    STATIC_STRING("ymo1n83-j2y1m1m9k83-nvy839my1m83-nxym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qerror);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_39,
	    string_constant_40,string_constant_41)));
    SET_SYMBOL_FUNCTION(Qconvert_to_true_list,
	    STATIC_FUNCTION(convert_to_true_list,NIL,FALSE,1,1));
    string_constant_42 = 
	    STATIC_STRING("1o1m83=My83-j0y1n83-j0y1m9k83Eny1l83-lfy1n83-j0y1m1m9k83Eny83Eay1m83-lfym1n83-j0y1m1m9k83Eny83-9Uy2l83-lfym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_42));
    Qtest_call_next_method_parse = 
	    STATIC_SYMBOL("TEST-CALL-NEXT-METHOD-PARSE",AB_package);
    string_constant_43 = 
	    STATIC_STRING("1z1m83=My83-9Jy1m83=My83-iXy1n83-9Jy1p83-2Ry1m9k9l1m9k833iy83YKy83lny1p83HYylop01n83-9Jy1r83-2Ry1m9k9l1m9k833iy83YKy83lny1m9k83f");
    string_constant_44 = 
	    STATIC_STRING("5y830By1p83HYylopr1o83-iXy1p83-2Ry1m9k9l1m9k833iy1m9k837Fy1m9k834My1m83-LNyl9m1n83-2Ry83*Zy1ll1o83-2Ry83-2Syl9n1n83-2Sy1n83*Zy1m");
    string_constant_45 = 
	    STATIC_STRING("9k83vy83*Zy1nmln1o83-2Sy1n83*Zy1m9k83vy83-2Sy1nmln9o1o83lny1m1m9k83-9y1m9k83-Ay09p1n83lny1n1m9k83-9y83-j7y1m9k83-Ay1lm1o83lny1n1");
    string_constant_46 = 
	    STATIC_STRING("m9k83-9y83-j8y1m9k83-Aym9n1m83-j7y83Eay1n83-j8y1n83-j7y1m9k83vy83-j7y1nmln1o83-j8y1n83-j7y1m9k83vy83-j8y1nmln9o");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qtest_call_next_method_parse);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qnil_function);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_43,
	    string_constant_44,string_constant_45,string_constant_46)));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant = 
	    STATIC_STRING("CALL NEXT METHOD is only available within a method");
    SET_SYMBOL_FUNCTION(Qtest_call_next_method_parse,
	    STATIC_FUNCTION(test_call_next_method_parse,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qtest_call_next_method_parse);
    string_constant_47 = 
	    STATIC_STRING("1t1m83=My83-iay1m83-SYy1m9k9l1n83-SYy1m1m9k83-ay1m9k9l9l1n83-iay1o1m9k83-Mry1m9k831Dy83-idy83-SYy1m83-Msyn1n83-iay1u1m9k83-Mry1m");
    string_constant_48 = 
	    STATIC_STRING("9k831Dy1m9k83-9y1m9k83-rly1m9k83lKy1m9k835+y839my1m9k83-Ay83-idy83-SYy1n83-Msytr1n83-iay1z1m9k83-Mry1m9k831Dy1m9k83-9y1m9k83-rly");
    string_constant_49 = 
	    STATIC_STRING("1m9k83lKy1m9k835+y839my1m9k83-Ay83-idy1m9k83-ay1m9k8312y1m9k83-riy1m9k832Sy83EXy83-SYy1o83-Msytry1n83-idy83-icy1ll1n83-idy1n83-i");
    string_constant_50 = 
	    STATIC_STRING("cy1m9k83-ay83-idy2lln1n83-icy1n83*Zy1m9k9m83Eay1mln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qend);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_47,
	    string_constant_48,string_constant_49,string_constant_50)));
    string_constant_51 = STATIC_STRING("1l1m83=My836Yy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_51));
    string_constant_52 = STATIC_STRING("1l1m83=My83-9Py");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_52));
    string_constant_53 = 
	    STATIC_STRING("1p1m83=My83-9Ky1m83=My83-iYy1n83-9Ky1n1m9k833iy83YKy83lny1p83HYy0mn01n83-9Ky1p1m9k833iy83YKy83lny1m9k83f5y830By1p83HYy0mnp1o83-i");
    string_constant_54 = 
	    STATIC_STRING("Yy1n1m9k833iy1m9k837Fy1m9k834My1l83-LOy9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qtest_call_next_method_parse);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_53,
	    string_constant_54)));
    Qextend_procedure_grammar = STATIC_SYMBOL("EXTEND-PROCEDURE-GRAMMAR",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qextend_procedure_grammar,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_1 = 
	    STATIC_STRING("1o1n83-9Jy1q83-2Ry1m9k9l1m9k8l1m9k833iy83-2y83lny1o83-qDylpq1n83-9Ky1o1m9k8l1m9k833iy83-2y83lny1n83-qEyno1m83=My83-j3y1n83-j3y1m");
    string_constant_2 = STATIC_STRING("1m9k8l1m9k83ASy1l83-qHy");
    SET_SYMBOL_FUNCTION(Qextend_procedure_grammar,
	    STATIC_FUNCTION(extend_procedure_grammar,NIL,FALSE,0,0));
    string_constant_55 = 
	    STATIC_STRING("1m1m83=My83-iey1n83-iey1o1m9k830Iy1m9k83*Xy1m9k83EHy834Py2l83-RWyo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_55));
    string_constant_56 = 
	    STATIC_STRING("1m1m83=My83-ify1n83-ify1r1m9k830Iy1m9k83*Xy1m9k83EHy1m9k83day1m9k83lIy1m9k83g9y834Py2l83-RYyr");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_56));
    string_constant_57 = 
	    STATIC_STRING("1p1m83=My83-ily1n83-ily1q1m9k83=Iy83*Zy1m9k9l1m9k838Dy83-iry834Py2m83-U7y1mmpq1n83-iry1o83-Gy1m9k830Iy1m9k83*Xy1m9k83EHy1m83=byl");
    string_constant_58 = 
	    STATIC_STRING("1n83-iry1p83loy830By1m9k830Iy1m9k83*Xy1m9k83EHy1n83=bylm1n83-iry1q83-Yy1m9k83*Xy830By1m9k830Iy1m9k83*Xy1m9k83EHy1n83=by1m838Eyln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_57,
	    string_constant_58)));
    string_constant_59 = 
	    STATIC_STRING("1p1m83=My83-iky1n83-iky1q1m9k83=Iy83*Zy1m9k9l1m9k838Dy83-isy834Py2m83-U6y1mmpq1n83-isy1r83-Gy1m9k830Iy1m9k83*Xy1m9k83EHy1m9k83da");
    string_constant_60 = 
	    STATIC_STRING("y1m9k83lIy1m9k83g9y1m83=byl1n83-isy1s83loy830By1m9k830Iy1m9k83*Xy1m9k83EHy1m9k83day1m9k83lIy1m9k83g9y1n83=bylm1n83-isy1t83-Yy1m9");
    string_constant_61 = 
	    STATIC_STRING("k83*Xy830By1m9k830Iy1m9k83*Xy1m9k83EHy1m9k83day1m9k83lIy1m9k83g9y1n83=by1m838Eyln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_59,
	    string_constant_60,string_constant_61)));
    string_constant_62 = 
	    STATIC_STRING("1m1m83=My83-iVy1n83-iVy1n1m9k837gy1m9k83-8Jy1m9k83-jIy1l83-Jay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_62));
    string_constant_63 = 
	    STATIC_STRING("1v1m83=My83-j4y1m83=My83-j6y1m83=My83-j5y1n83-j4y1n1m9k83ASy1m9k83=Iy839my1m83-v+yn1n83-j6y1q1m9k83ASy1m9k83day83EZy1m9k83-MKy1m");
    string_constant_64 = 
	    STATIC_STRING("9k9l839my1n83-v=ynq1m83-jEy83-iiy1m83-iiy83-igy1o83-iiy1n83-igy1m9k83=Uy83-iiy1n83=Uyln9m1m83-igy83-ihy1n83-ihy1o83YKy1m9k83-A3y");
    string_constant_65 = 
	    STATIC_STRING("1m9k83=Yy1m9k83*ly1m83-A4yl1n83-j5y1n1m9k83ASy1m9k83day83-jEy1m83-v*yn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_63,
	    string_constant_64,string_constant_65)));
    if (Procedure_function_template_alist == UNBOUND)
	Procedure_function_template_alist = Nil;
    Qhas_a_current_value = STATIC_SYMBOL("HAS-A-CURRENT-VALUE",AB_package);
    Qdesignation = STATIC_SYMBOL("DESIGNATION",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qhas_a_current_value,
	    Qdesignation);
    def_procedure_function_template(list_constant_9);
    Qhas_no_current_value = STATIC_SYMBOL("HAS-NO-CURRENT-VALUE",AB_package);
    list_constant_10 = STATIC_CONS(Qdesignation,Qnil);
    list_constant_11 = STATIC_CONS(Qhas_no_current_value,list_constant_10);
    def_procedure_function_template(list_constant_11);
    Qfailed_to_receive_a_value = STATIC_SYMBOL("FAILED-TO-RECEIVE-A-VALUE",
	    AB_package);
    Qlocal_name_var_spot = STATIC_SYMBOL("LOCAL-NAME-VAR-SPOT",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qfailed_to_receive_a_value,
	    Qlocal_name_var_spot);
    def_procedure_function_template(list_constant_12);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    Qthere_exists_scope = STATIC_SYMBOL("THERE-EXISTS-SCOPE",AB_package);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qthere_exists_literal,
	    Qthere_exists_scope,Qexpression);
    def_procedure_function_template(list_constant_13);
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qvar_spot,Qother);
    def_procedure_function_template(list_constant_14);
}
